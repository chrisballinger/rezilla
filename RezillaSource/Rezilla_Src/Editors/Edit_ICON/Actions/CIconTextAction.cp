// ===========================================================================
// CIconTextAction.cp
//                       Created: 2004-12-11 18:52:42
//             Last modification: 2004-12-27 10:32:12
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
// We draw the text into a 1-bit gworld that has a TextEdit record attached
// to it. We then blit and colorize this gworld to the image buffer and
// then to the canvas. TextEdit provides support for languages like Arabic
// where each new character can affect the look of previous characters.
// Don't try this by hand unless you have a month to kill.

#include "CIconTextAction.h"
#include "CIcon_EditorView.h"
#include "CIcon_EditorWindow.h"
#include "COffscreen.h"
#include "CIconSelection.h"
#include "UIconMisc.h"


static pascal void MyCaretHook( const Rect *, TEPtr );

static CaretHookUPP		sCaretUPP = nil;


// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------

CIconTextAction::CIconTextAction( const SPaintAction &inAction ) : 
	CIconTrackingPaintAction( inAction, index_UndoText )
{
	this->ThrowIfFileLocked();
	
	if ( !sCaretUPP )
	{
		sCaretUPP = NewCaretHookUPP( MyCaretHook );
		ThrowIfMemFail_( sCaretUPP );
	}
	
	mText = nil;
	mTextBuffer = nil;
	mImageBuffer = nil;
	mUndoBuffer = nil;
	mImageHeight = 0;
	mImageWidth = 0;
	
	mDrawnInsertionPoint = false;
	mNextInsertionTime = 0;
	
	// The paint view needs to know when we go away (listens for msg_TextActionDied)
	this->AddListener( mSettings.thePaintView );
}


// ---------------------------------------------------------------------------
// 	Destructor
// ---------------------------------------------------------------------------
// Let the PaintView know we died -- it won't know in the case of
// Constructor-wide commands like Save.
// We can't rely on the generic "broadcastDied" message because by the time
// it is sent, the object is no longer a text action and the paintview
// won't recognize it.
// This may cause the paintview to call us to erase the insertion point.
// This isn't a very good C++ practice (we can't be subclassed completely).

CIconTextAction::~CIconTextAction()
{
	this->BroadcastMessage( msg_TextActionDied, this );
	
	if ( mText ) 
	{
		::TEDispose( mText );
		mText = nil;
	}
	
	if ( mTextBuffer )
	{
		delete mTextBuffer;
		mTextBuffer = nil;
	}
}


// ---------------------------------------------------------------------------
// 	UndoSelf
// ---------------------------------------------------------------------------

void
CIconTextAction::UndoSelf()
{
	this->CloseEditSession();
	CIconTrackingPaintAction::UndoSelf();
}


// ---------------------------------------------------------------------------
// 	HandleMouseDown
// ---------------------------------------------------------------------------

void
CIconTextAction::HandleMouseDown( const SMouseDownEvent &inEvent )
{
	StGWorldSaver	aWorldSaver;
	Rect			destR, sourceR;
	CIcon_EditorWindow		*thePaintView = mSettings.thePaintView;
	GrafPtr			aSparePort = USparePort::GetSparePort();
	SInt32			initialH, initialV;
	
	// Get the initial cell hit by the user
	if ( !mSettings.theCanvas->MapPointToCell( inEvent.whereLocal, &initialH, &initialV ) )
		return;								// missed it by *that* much
	
	// Save the image & undo buffers 'cause we need them just about everywhere
	mImageBuffer = mSettings.thePaintView->GetImageBuffer();
	mUndoBuffer = mSettings.thePaintView->GetUndoBuffer();
	SInt32	mImageWidth = mImageBuffer->GetWidth();
	SInt32	mImageHeight = mImageBuffer->GetHeight();

	// Get the text traits from the paint view and then the font information
	thePaintView->GetTextTraits( &mTextTraits );
	UIconMisc::SetPort( aSparePort );
	UTextTraits::SetPortTextTraits( &mTextTraits );
	::GetFontInfo( &mFontInfo );
	
	// Find the rectangle we are drawing in relative to the paint image buffer. 
	mTextTop = MAX( 0, initialV - mFontInfo.ascent + 1 );	// no negatives allowed
	
	switch( mTextTraits.justification )
	{
		case teForceLeft:
		case teFlushDefault:				// shouldn't happen (paint view changes this)
			::SetRect( &destR, initialH, mTextTop, mImageWidth, mImageHeight );
			break;
		case teJustRight:
			::SetRect( &destR, 0, mTextTop, initialH, mImageHeight );
			break;
		case teJustCenter:
			SInt32 centerWidth = MIN( initialH, mImageWidth - initialH );
			::SetRect( &destR, initialH - centerWidth, mTextTop, initialH + centerWidth, mImageHeight );
			break;
	}
	
	short textAreaWidth = destR.right - destR.left;
	short textAreaHeight = destR.bottom - destR.top;
	
	// Find the rectangle we are drawing in relative to text buffer
	::SetRect( &sourceR, 0, 0, textAreaWidth, textAreaHeight );
	mTextLeft = destR.left;
	
	// Allocate a 1-bit buffer the same size as the text area
	mTextBuffer = COffscreen::CreateBuffer( textAreaWidth, textAreaHeight, 1 );

	// Draw into our offscreen in black always, since it's only 1-bit
	// (we'll colorize the text when we blit it to the image buffer later on).
	TextTraitsRecord copyOfTraits = mTextTraits;
	copyOfTraits.color = Color_Black;
	
	// Create the text edit record
	mTextBuffer->BeginDrawing();
		
	UTextTraits::SetPortTextTraits( &copyOfTraits );
	mText = ::TENew( &sourceR, &sourceR );
	ThrowIfMemFail_( mText );

	// This will set the alignment (not part of the port text style)		
	UTextTraits::SetTETextTraits( &copyOfTraits, mText );
	
	// and we draw the caret ourself
	(**mText).caretHook = sCaretUPP;

	mTextBuffer->EndDrawing();
	
	// We're undoable, so copy the current image to the undo buffer
	mSettings.thePaintView->CopyToUndo();

	// Post us to the undo queue and let the paintview know we're active.
	// The order of this is important.
	this->PostAsAction();	
	mSettings.thePaintView->SetTextAction( this );
}


// ---------------------------------------------------------------------------
// 	HandleKeyDown
// ---------------------------------------------------------------------------

void
CIconTextAction::HandleKeyDown( const EventRecord &inEvent )
{
	StGWorldSaver		aSaver;
	Boolean				isArrowKey = false;
	Rect				rBefore, rAfter;
	
	if ( !mText || !mTextBuffer ) return;
	
	UInt8 theChar = inEvent.message & charCodeMask;

	// Erase the old insertion point or we get junk on the screen (esp left arrow key)
	this->DrawInsertionPoint( false );
	
	// If an arrow key was hit, be sure to draw the insertion point at the
	// bottom of this function or user won't be able to see it until they
	// release the key.
	if ( (theChar == char_LeftArrow) || (theChar == char_RightArrow)
			|| (theChar == char_UpArrow) || (theChar == char_DownArrow) )
		isArrowKey = true;
	
	// Get the size of the area we've already drawn into. This is needed
	// for the backspace key when the user deletes a CR.
	this->GetRectRelativeToImageBuffer( &rBefore );
	
	// Restore the main buffer to virgin status
	this->RestoreMainBufferFromUndoBuffer();
	
	// Tell TextEdit to do its thing
	mTextBuffer->BeginDrawing();
		::TEKey( theChar, mText );
	mTextBuffer->EndDrawing();
	
	// Copy the text buffer back to the main image buffer
	this->CopyTextBufferToMainBuffer();

	// Update the portion of the canvas/screen that needs it. this may be
	// one extra line of text if the user deleted a CR.
	this->GetRectRelativeToImageBuffer( &rAfter );
	rAfter.bottom = MAX( rAfter.bottom, rBefore.bottom );
	this->CopyMainBufferToCanvas( &rAfter );

	// In case of repeating arrow keys, draw the insertion point now. For
	// any other key, the paint view has been modified (this is needed when
	// the user saves while editing text).
	if ( isArrowKey )
		this->DrawInsertionPoint( true );
	else
		mSettings.thePaintView->SetDirty( true );
}


// ---------------------------------------------------------------------------
// 	Idle
// ---------------------------------------------------------------------------

void
CIconTextAction::Idle()
{
	if ( !mText ) return;
	if ( mNextInsertionTime > (UInt32) TickCount() ) return;
	
	this->DrawInsertionPoint( !mDrawnInsertionPoint );
	mNextInsertionTime = ((UInt32)TickCount()) + ::GetCaretTime();
}


// ---------------------------------------------------------------------------
// 	CloseEditSession
// ---------------------------------------------------------------------------

void
CIconTextAction::CloseEditSession()
{
	if ( mText )
	{
		this->DrawInsertionPoint( false );	// kill the insertion point
		
		::TEDispose( mText );
		mText = nil;
	}

	if ( mTextBuffer )
	{
		delete mTextBuffer;
		mTextBuffer = nil;
	}
}


// ---------------------------------------------------------------------------
// 	ChangeTextTraits
// ---------------------------------------------------------------------------

void
CIconTextAction::ChangeTextTraits( const TextTraitsRecord &inTraits )
{
	StGWorldSaver	aSaver;
	Rect			bigR = { -1000, -1000, 3000, 3000 };
	
	if ( !mText || !mTextBuffer ) return;

	// Erase the insertion point -- its size may change
	this->DrawInsertionPoint( false );	

	// Restore the image buffer to its initial state
	this->RestoreMainBufferFromUndoBuffer();
	
	// Change the textedit record and our internal variables
	mTextTraits = inTraits;

	// We always draw in black since our text buffer is only 1-bit
	TextTraitsRecord copyOfTraits = mTextTraits;
	copyOfTraits.color = Color_Black;

	mTextBuffer->BeginDrawing();
		UTextTraits::SetPortTextTraits( &copyOfTraits );
		::GetFontInfo( &mFontInfo );
		UTextTraits::SetTETextTraits( &copyOfTraits, mText, nil ); 
		::TECalText( mText );
		::TEUpdate( &bigR, mText );
	mTextBuffer->EndDrawing();
	
	// Overlay the text into the main image buffer
	this->CopyTextBufferToMainBuffer();
	
	// Redraw the entire canvas -- this covers all possible text changes
	Rect r;
	::SetRect( &r, 0, 0, mImageBuffer->GetWidth(), mImageBuffer->GetHeight() );
	this->CopyMainBufferToCanvas( &r );
	
	// Tell the paint view we've changed
	mSettings.thePaintView->SetDirty( true );
}



// ---------------------------------------------------------------------------
// 	RestoreMainBufferFromUndoBuffer
// ---------------------------------------------------------------------------
// 	Restores the main buffer from the undo buffer. For speed, only copies
// 	the currently used portion of the buffer.

void
CIconTextAction::RestoreMainBufferFromUndoBuffer()
{
	if ( !mText || !mImageBuffer || !mUndoBuffer ) return;

	Rect r;
	this->GetRectRelativeToImageBuffer( &r );
	mImageBuffer->CopyFrom( mUndoBuffer, &r, &r );
}


// ---------------------------------------------------------------------------
// 	CopyTextBufferToMainBuffer
// ---------------------------------------------------------------------------

void
CIconTextAction::CopyTextBufferToMainBuffer()
{
	if ( !mText || !mImageBuffer || !mTextBuffer ) return;

	Rect sourceR, destR;
	this->GetRectRelativeToImageBuffer( &destR );
	this->GetRectRelativeToTextBuffer( &sourceR );
	this->CopyAndColorize( mTextBuffer, mImageBuffer, sourceR, destR, mTextTraits.color );
}


// ---------------------------------------------------------------------------
// 	CopyMainBufferToCanvas
// ---------------------------------------------------------------------------

void
CIconTextAction::CopyMainBufferToCanvas( Rect *inDestR )
{
	if ( !mText || !mImageBuffer || !mTextBuffer ) return;
	
	Rect	r;
	
	if ( inDestR )
		r = *inDestR;
	else
		this->GetRectRelativeToImageBuffer( &r );

	mSettings.theCanvas->DrawFrom( mImageBuffer, &r );
	mSettings.thePaintView->RedrawSampleView();
}


// ---------------------------------------------------------------------------
// 	CopyAndColorize
// ---------------------------------------------------------------------------

void
CIconTextAction::CopyAndColorize( COffscreen *inSource, COffscreen *inDest,
									const Rect &inSourceR, const Rect &inDestR,
									RGBColor &inRGBColor )
{
	Rect sourceR, destR;
 
 	try
 	{
		// Pin the source & dest rectangles to the actual buffer size so we
		// don't overstep the bounds.
		sourceR.left = MAX( 0, inSourceR.left );
		sourceR.right = MIN( inSource->GetWidth(), inSourceR.right );
		sourceR.top = MAX( 0, inSourceR.top );
		sourceR.bottom = MIN( inSource->GetHeight(), inSourceR.bottom );
		
		destR.left = MAX( 0, inDestR.left );
		destR.right = MIN( inDest->GetWidth(), inDestR.right );
		destR.top = MAX( 0, inDestR.top );
		destR.bottom = MIN( inDest->GetHeight(), inDestR.bottom );
		
		// Find the pixel value for the color we want
		PixelValue 	destPixel = inDest->RGBToPixelValue( inRGBColor );

		// Loop through the source and set the appropriate pixels in the dest
		SInt32		numRows = MIN( sourceR.bottom - sourceR.top, destR.bottom - destR.top );
		SInt32		numCols = MIN( sourceR.right - sourceR.left, destR.right - destR.left );
		
		for ( SInt32 rowCount = 0; rowCount < numRows; rowCount++ )
		{
			RawPtr	sourceRow = inSource->RawGetRowPtr( sourceR.top + rowCount );
			RawPtr	destRow = inDest->RawGetRowPtr( destR.top + rowCount );
			SInt32 	sourceCol = sourceR.left;
			SInt32 	destCol = destR.left;

			for ( SInt32 colCount = 0; colCount < numCols; colCount++ )
			{
				if ( inSource->RawGetPixel( sourceRow, sourceCol ) )
					inDest->RawSetPixel( destRow, destCol, destPixel );
					
				++sourceCol;
				++destCol;
			}
		}
	}
	catch( ... )
	{
	
	}
}


// ---------------------------------------------------------------------------
// 	GetRectRelativeToTextBuffer
// ---------------------------------------------------------------------------

Boolean
CIconTextAction::GetRectRelativeToTextBuffer( Rect *outR )
{
	if ( !mText || !mImageBuffer )
	{
		::SetRect( outR, 0, 0, 0, 0 );
		return( false );
	}
	
		// this gives us the left/right and top of the text buffer
	*outR = (**mText).destRect;

		// and this gives us the bottom
	outR->bottom = outR->top + this->CalcTextAreaHeight();

	::OffsetRect( outR, -outR->left, -outR->top );		// make sure it's 0,0-based
	return( ::EmptyRect( outR ) );
}


// ---------------------------------------------------------------------------
// 	CalcTextAreaHeight
// ---------------------------------------------------------------------------

SInt32
CIconTextAction::CalcTextAreaHeight()
{
	if ( !mText ) return( 0 );

	SInt32 lineHeight = mFontInfo.ascent + mFontInfo.descent + mFontInfo.leading;
	SInt32 result = lineHeight * MAX( 1, (**mText).nLines );
	
	// This fixes an old bug in textedit (nLines is sometimes incorrect)
	SInt32 numBytes = (**mText).teLength;
	if ( (numBytes > 0) && ((*(**mText).hText)[numBytes-1] == char_Return) )
		result += lineHeight;

	return( result );
}


// ---------------------------------------------------------------------------
// 	GetRectRelativeToImageBuffer
// ---------------------------------------------------------------------------

Boolean
CIconTextAction::GetRectRelativeToImageBuffer( Rect *outR )
{
	this->GetRectRelativeToTextBuffer( outR );	// will be 0,0-based here
	::OffsetRect( outR, mTextLeft, mTextTop );
	return( ::EmptyRect( outR ) );
}


// ---------------------------------------------------------------------------
// 	DrawInsertionPoint
// ---------------------------------------------------------------------------
// 	Draws or erases the insertion point.

void
CIconTextAction::DrawInsertionPoint( Boolean inDraw )
{
	StGWorldSaver		aSaver;
	CIcon_EditorView 			*theCanvas = mSettings.theCanvas;
	
	if ( !mText ) return;					// we're closed

	Rect sourceR, destR;
	this->GetInsertionPoint( &sourceR );
	::OffsetRect( &sourceR, mTextLeft, mTextTop );	// make it rel to image
	theCanvas->MapRectToCanvas( sourceR, &destR );

	theCanvas->FocusDraw();
	
	if ( inDraw )
	{
		StColorPenState		penSaver;
		penSaver.Normalize();				// selection always drawn in black
		
		// Clip inside the canvas a bit or we don't always clean up well
		Rect		r;
		theCanvas->GetInsideDrawingRect( &r );
		StClipRgnState	saveSetAndRestore( r );

		::MoveTo( destR.left, destR.bottom );
		::LineTo( destR.left, destR.top );
		mDrawnInsertionPoint = true;
	}
	else
	{
		RgnHandle tempRgn = ::NewRgn();
		if ( !tempRgn ) return;
		
		::InsetRect( &destR, -2, -2 );		// make sure we hit the insertion point
		theCanvas->LocalToPortPoint( topLeft( destR ) );
		theCanvas->LocalToPortPoint( botRight( destR ) );
		::RectRgn( tempRgn, &destR );
		theCanvas->Draw( tempRgn );
		::DisposeRgn( tempRgn );

		mDrawnInsertionPoint = false;
	}
}


// ---------------------------------------------------------------------------
// 	GetInsertionPoint
// ---------------------------------------------------------------------------
// 	Returns a rectangle which indicates where the insertion point is (rel to text).
// 	Returns false if no insertion point can be drawn.

Boolean
CIconTextAction::GetInsertionPoint( Rect *outR )
{
	if ( !mText )
	{
		::SetRect( outR, 0, 0, 0, 0 );
		return( false );
	}
	
	short selStart = (**mText).selStart;
	Point pt = ::TEGetPoint( selStart, mText );
	
	// Bug in textedit (since 1984) - add lineHeight if the last char is a return
	if ( selStart == (**mText).teLength )
		if ( ((*(**mText).hText)[selStart-1] == char_Return) )
			pt.v += mFontInfo.ascent + mFontInfo.descent + mFontInfo.leading;

	outR->left = pt.h;
	outR->right = pt.h + 1;			// canvas doesn't like zero-width rectangles
	outR->bottom = pt.v - mFontInfo.descent;
	outR->top = outR->bottom - mFontInfo.ascent;
	return( true );
}


// ---------------------------------------------------------------------------
// 	MyCaretHook
// ---------------------------------------------------------------------------
// 	If we don't put a dummy caret hook in the TERecord, sometimes the caret
// 	gets drawn into our offscreen buffer and never erased, leaving trails
// 	on the screen when the arrow keys are used.

static pascal void MyCaretHook( const Rect *, TEPtr )		// CFM version
{
}


