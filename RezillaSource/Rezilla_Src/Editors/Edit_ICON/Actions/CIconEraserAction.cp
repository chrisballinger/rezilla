// ===========================================================================
// CIconEraserAction.cp
//                       Created: 2004-12-11 18:52:20
//             Last modification: 2004-12-14 18:52:20
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "RezillaConstants.h"
#include "CIconActions.h"

// 	One of these two should be #defined
#define USE_LINES_FOR_ERASER
//#define USE_RECTS_FOR_ERASER


// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------

CIconEraserAction::CIconEraserAction( const SPaintAction &inAction ) : 
		CIconTrackingPaintAction( inAction, index_UndoEraser )
{
	const UInt32	kCursorWidth	= 14;
	
	this->ThrowIfFileLocked();

	mLastRowErased = mLastColErased = -1;			// nothing painted yet
	mEraserWidth = 1;								// 1 pixel (changed below)
	
			// the number of pixels the eraser erases depends on the
		// current zoom level

	Rect	pixelR;
	mSettings.theCanvas->GetPixelRect( 0, 0, &pixelR );
	
	SInt32	cellWidth = pixelR.right - pixelR.left;
	if ( cellWidth != 0 )
		mEraserWidth = MAX( 1, kCursorWidth / cellWidth );
}


// ---------------------------------------------------------------------------
// 	Destructor
// ---------------------------------------------------------------------------

CIconEraserAction::~CIconEraserAction()
{
}


// ---------------------------------------------------------------------------
// 	MouseInitial
// 	
// 	Notes:
// 	Determines whether we will be drawing in the foreground or background
// 	  color.
// ---------------------------------------------------------------------------

void CIconEraserAction::MouseInitial( const SMouseDownEvent &inEvent, SInt32 /* newCol */, SInt32 /* newRow */ )
{
	if ( inEvent.macEvent.modifiers & shiftKey )
		mSnapTo.SetAngle( CSnapTo::kSnapTo90 );
	else
		mSnapTo.SetAngle( CSnapTo::kDontSnap );

	mBufferCols = mSettings.currentBuffer->GetWidth();
	mBufferRows = mSettings.currentBuffer->GetHeight();
}


// ---------------------------------------------------------------------------
// 	MouseStillDown
// ---------------------------------------------------------------------------

void CIconEraserAction::MouseStillDown( const SMouseDownEvent &, 
											Point /*prevMousePt*/, Point /*newMousePt*/,
											SInt32 prevCol, SInt32 prevRow,
											SInt32 newCol, SInt32 newRow )
{
	if ( (newCol == prevCol) && (newRow == prevRow) )
		return;
	
	COffscreen	*		theImageBuffer = mSettings.currentBuffer;
	SInt32				halfWidth = mEraserWidth / 2;
	
	if ( (newCol < -halfWidth) || (newCol >= mBufferCols + halfWidth) ||
	     (newRow < -halfWidth) || (newRow >= mBufferRows + halfWidth) )	// far offscreen ?
	{
		mLastRowErased = -1;
		mLastColErased = -1;
	}
	else
	{
			// if we didn't draw recently, start with a single point
		if ( (mLastRowErased == -1) || (mLastColErased == -1) )
		{
			mLastRowErased = newRow;
			mLastColErased = newCol;
		}

			// draw the pen stroke into the buffer (as a line)
		theImageBuffer->BeginDrawing();
		
		#ifdef USE_LINES_FOR_ERASER
			theImageBuffer->SetForeColor( mSettings.theBackColor );
			::PenSize( mEraserWidth, mEraserWidth );
			::MoveTo( mLastColErased, mLastRowErased );
			::LineTo( newCol, newRow );
		
		
		#ifdef USE_RECTS_FOR_ERASER
		
			// this makes the eraser more accurately hit the pixels
			newRow -= halfWidth/2;
			newCol -= halfWidth/2;
		
			theImageBuffer->SetBackColor( mSettings.theBackColor );
			Rect	r;
			r.left = newCol;
			r.right = newCol + mEraserWidth;
			r.top = newRow;
			r.bottom = newRow + mEraserWidth;
			::EraseRect( &r );
		
		
		theImageBuffer->EndDrawing();
		
			// copy the buffer to the screen (only the portion drawn for speed)
		Rect	subRect;
		subRect.left = MIN( mLastColErased, newCol );
		subRect.right = 1 + MAX( mLastColErased, newCol );
		subRect.top = MIN( mLastRowErased, newRow );
		subRect.bottom = 1 + MAX( mLastRowErased, newRow );
		
			// this box is a little too big, but it doesn't really matter
		::InsetRect( &subRect, -mEraserWidth, -mEraserWidth );
		//subRect.top -= mEraserWidth;
		//subRect.left -= mEraserWidth;
		
			// pin the rectangle to the image size
		subRect.left = MAX( 0, subRect.left );
		subRect.right = MIN( subRect.right, mBufferCols + 1 );
		subRect.top = MAX( 0, subRect.top );
		subRect.bottom = MIN( subRect.bottom, mBufferRows + 1 );
		
		mSettings.theCanvas->DrawFrom( theImageBuffer, &subRect);

		mLastRowErased = newRow;
		mLastColErased = newCol;
	}
}

#ifdef PREV_VERSION

// ---------------------------------------------------------------------------
// 	MouseStillDown
// ---------------------------------------------------------------------------

void CIconEraserAction::MouseStillDown( const SMouseDownEvent &, 
											Point /*prevMousePt*/, Point /*newMousePt*/,
											SInt32 prevCol, SInt32 prevRow,
											SInt32 newCol, SInt32 newRow )
{
	if ( (newCol == prevCol) && (newRow == prevRow) )
		return;
	
	COffscreen	*		theImageBuffer = mSettings.currentBuffer;
	SInt32				halfWidth = mEraserWidth / 2;
	
	if ( (newCol < -halfWidth) || (newCol >= mBufferCols + halfWidth) ||
	     (newRow < -halfWidth) || (newRow >= mBufferRows + halfWidth) )	// far offscreen ?
	{
		mLastRowErased = -1;
		mLastColErased = -1;
	}
	else
	{
		if ( (mLastRowErased == -1) || (mLastColErased == -1) )
		{
			mLastRowErased = newRow;
			mLastColErased = newCol;
		}

			// draw the pen stroke into the buffer (as a line)
		theImageBuffer->BeginDrawing();
		theImageBuffer->SetForeColor( mSettings.theBackColor );
		//StColorPenState		aPenState;
		//::PmForeColor( mSettings.theBackColor );
			::PenSize( mEraserWidth, mEraserWidth );
			::MoveTo( mLastColErased, mLastRowErased );
			::LineTo( newCol, newRow );
		theImageBuffer->EndDrawing();
		
			// copy the buffer to the screen (only the portion drawn for speed)
		Rect	subRect;
		subRect.left = MIN( mLastColErased, newCol );
		subRect.right = 1 + MAX( mLastColErased, newCol );
		subRect.top = MIN( mLastRowErased, newRow );
		subRect.bottom = 1 + MAX( mLastRowErased, newRow );
		::InsetRect( &subRect, -halfWidth, -halfWidth );
		
			// pin the rectangle to the image size
		subRect.left = MAX( 0, subRect.left );
		subRect.right = MIN( subRect.right, mBufferCols + 1 );
		subRect.top = MAX( 0, subRect.top );
		subRect.bottom = MIN( subRect.bottom, mBufferRows + 1 );
		
		mSettings.theCanvas->DrawFrom( theImageBuffer, &subRect);

		mLastRowErased = newRow;
		mLastColErased = newCol;
	}
}


