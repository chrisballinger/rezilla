// ===========================================================================
// CIcon_EditorView.cp
// 
//                       Created: 2004-12-10 17:23:05
//             Last modification: 2005-01-10 18:16:00
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CIcon_EditorDoc.h"
#include "CIcon_EditorView.h"
#include "CIcon_EditorWindow.h"
#include "COffscreen.h"
#include "CRezObj.h"
#include "CIconActions.h"
#include "CRezillaPrefs.h"
#include "UColorUtils.h"
#include "UIconMisc.h"
#include "UResourceMgr.h"


PP_Begin_Namespace_PowerPlant


// Static variables
SInt32 			CIcon_EditorView::sNumWindows = 0;
COffscreen *	CIcon_EditorView::sBigScratchBuffer = nil;


// ---------------------------------------------------------------------------
// 	CIcon_EditorView							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CIcon_EditorView::CIcon_EditorView()
		: LView(), 
			CImageDragDrop( UQDGlobals::GetCurrentWindowPort(), this )
{
	Initialize();
}


// ---------------------------------------------------------------------------
// 	CIcon_EditorView							Parameterized Constructor [public]
// ---------------------------------------------------------------------------

CIcon_EditorView::CIcon_EditorView(
	const SPaneInfo&	inPaneInfo,
	const SViewInfo&	inViewInfo)

	: LView(inPaneInfo, inViewInfo), 
	CImageDragDrop( UQDGlobals::GetCurrentWindowPort(), this )
{
	Initialize();
}


// ---------------------------------------------------------------------------
// 	CIcon_EditorView							Stream Constructor		  [public]
// ---------------------------------------------------------------------------
// Use the Preference interface settings when creating a new TEXT resource.

CIcon_EditorView::CIcon_EditorView(
	LStream*	inStream)

	: LView(inStream), 
	CImageDragDrop( UQDGlobals::GetCurrentWindowPort(), this )
{
	Initialize();
}


// ---------------------------------------------------------------------------
// 	~CIcon_EditorView						Destructor				  [public]
// ---------------------------------------------------------------------------

CIcon_EditorView::~CIcon_EditorView()
{
	if ( (--sNumWindows == 0) && sBigScratchBuffer )
	{
		delete sBigScratchBuffer;
		sBigScratchBuffer = nil;
	}
}


// ---------------------------------------------------------------------------
// 	Initialize
// ---------------------------------------------------------------------------

void
CIcon_EditorView::Initialize()
{
	this->ClearInstanceVariables();

	if ( sNumWindows == 0 )
		sBigScratchBuffer = COffscreen::CreateBuffer( 320, 320, 32 );
	
	++sNumWindows;
}


// ---------------------------------------------------------------------------
// 	ClearInstanceVariables
// ---------------------------------------------------------------------------

void
CIcon_EditorView::ClearInstanceVariables()
{
	mOwnerWindow = nil;
	mCellWidth = 6;
	mSpaceBetween = kIconSpaceBetween;
	mImageHeight = mImageWidth = 0;
	SetRect( &mFirstRect, 0, 0, 0, 0 );
	mHotSpot.h = -1;
	mHotSpot.v = -1;
}


// ---------------------------------------------------------------------------
// 	CreatePaintCanvasFromStream
// ---------------------------------------------------------------------------

CIcon_EditorView *
CIcon_EditorView::CreatePaintCanvasStream( LStream *inStream )
{
	return new CIcon_EditorView( inStream );
}


#pragma mark -

// ---------------------------------------------------------------------------
// 	FinishCreateSelf
// ---------------------------------------------------------------------------

void 
CIcon_EditorView::FinishCreateSelf()
{
	LView::FinishCreateSelf();
	mOwnerWindow = (CIcon_EditorWindow*) this->GetSuperView();
}


// ---------------------------------------------------------------------------
// 	AdjustMouseSelf
// ---------------------------------------------------------------------------

void 
CIcon_EditorView::AdjustMouseSelf( Point inPortPt, const EventRecord &inMacEvent, RgnHandle /* outMouseRgn */ )
{
	if ( !mOwnerWindow ) return;
	
	PortToLocalPoint( inPortPt );
	SInt32	totalCellWidth = mCellWidth + mSpaceBetween;
	SInt32	rightSide = mFirstRect.left + mImageWidth * totalCellWidth;
	SInt32	bottomSide = mFirstRect.top + mImageHeight * totalCellWidth;
	
	if ( (inPortPt.h >= mFirstRect.left) && (inPortPt.v >= mFirstRect.top) 
			&& (inPortPt.h < rightSide) && (inPortPt.v < bottomSide) )
	{
		mOwnerWindow->AdjustCursorInCanvas( inPortPt, inMacEvent );
	}
	else
		UCursor::SetArrow();
}


// ---------------------------------------------------------------------------
// 	ClickSelf
// ---------------------------------------------------------------------------

void 
CIcon_EditorView::ClickSelf(const SMouseDownEvent &inMouseDown)
{
	if ( mOwnerWindow )
		mOwnerWindow->HandleMouseDownInCanvas( inMouseDown );
}


// ---------------------------------------------------------------------------
// 	HandleKeyPress							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CIcon_EditorView::HandleKeyPress(
	const EventRecord	&inKeyEvent)
{
	Boolean		keyHandled	 = true;
// 	LView::HandleKeyPress(inKeyEvent);
	
	if (UKeyFilters::PrintingCharField(inKeyEvent) == keyStatus_TECursor) {
// 		mOwnerWindow->AdjustMenusToSelection();
	} 
	mOwnerWindow->SetCoordsField(0, 0);   // todo: insert right coords
	return keyHandled;
}


// ---------------------------------------------------------------------------
// 	ObeyCommand							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CIcon_EditorView::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;

	switch (inCommand) {

		case cmd_Cut: 
		case cmd_Paste: 
		case cmd_Clear: 
// 		LTextEditView::ObeyCommand(inCommand, ioParam);
		mOwnerWindow->SetCoordsField(0, 0);   // todo: insert right coords
		break;

		default:
			cmdHandled = dynamic_cast<CIcon_EditorWindow *>(mOwnerWindow)->ObeyCommand(inCommand, ioParam);
			break;
	}

	return cmdHandled;
}


// ---------------------------------------------------------------------------
// 	UserChangedBitmap						[public, virtual]
// ---------------------------------------------------------------------------
//	Bitmap has changed as a result of user action

void
CIcon_EditorView::UserChangedBitmap()
{
	if ( ! mOwnerWindow->IsDirty() ) {
		// Set the update menus flag.
		LCommander::SetUpdateCommandStatus( true );
		
		// Set the dirty flag.
		mOwnerWindow->SetDirty( true );
	}
}


// ---------------------------------------------------------------------------
//  ¥ GetModifiedBitmap										[public]
// ---------------------------------------------------------------------------

Handle
CIcon_EditorView::GetModifiedBitmap() 
{
	Handle	outTextHandle = NULL;
	
	return outTextHandle;
}


// ---------------------------------------------------------------------------
// 	DrawSelf
// ---------------------------------------------------------------------------

void 
CIcon_EditorView::DrawSelf()
{
	if ( mOwnerWindow )
		mOwnerWindow->HandleCanvasDraw();
}


// ---------------------------------------------------------------------------
// 	HasHotSpot
// ---------------------------------------------------------------------------

Boolean 
CIcon_EditorView::HasHotSpot()
{
	if ( (mHotSpot.h == -1) || (mHotSpot.v == -1) )
		return( false );
	return( true );
}


// ---------------------------------------------------------------------------
// 	GetHotSpot
// ---------------------------------------------------------------------------

Point 
CIcon_EditorView::GetHotSpot()
{
	return( mHotSpot );
}


// ---------------------------------------------------------------------------
// 	SetHotSpot
// ---------------------------------------------------------------------------
// 	Set to -1,-1 to remove it (this is never done, though).
// 	Does not redraw.

void 
CIcon_EditorView::SetHotSpot( Point inHotSpot )
{
	if ( EqualPt( inHotSpot, mHotSpot ) )
		return;
	
	mHotSpot = inHotSpot;
}


// ---------------------------------------------------------------------------
// 	DrawHotSpot
// ---------------------------------------------------------------------------

void 
CIcon_EditorView::DrawHotSpot( COffscreen *inSourceBuffer )
{
	StGWorldSaver		aSaver;
	Rect				r;
	
	if ( this->GetPixelRect( mHotSpot.h, mHotSpot.v, &r, false ) )
	{
		this->FocusDraw();
		Color32 theColor = inSourceBuffer->GetPixelColor( mHotSpot.h, mHotSpot.v );
		this->DrawHotSpotSelf( theColor, r );
	}
}


// ---------------------------------------------------------------------------
// 	DrawHotSpotSelf
// ---------------------------------------------------------------------------

void 
CIcon_EditorView::DrawHotSpotSelf( Color32 inPixelColor, const Rect &inRect )
{
	// Make sure the pattern and mode are correct
	StColorPenState		thePenState;
	thePenState.Normalize();
	
	// If the source pixel is light, draw the hot spot in black.
	// If the source pixel is dark, draw the hot spot in white.
	HSLColor	pixelHSL;
	RGBColor	pixelRGB = UColorUtils::Color32ToRGB( inPixelColor );
	::RGB2HSL( &pixelRGB, &pixelHSL );
	if ( pixelHSL.lightness > 0x8000 )
	{
		::RGBForeColor( &Color_Black );
		::RGBBackColor( &Color_White );
	}
	else
	{
		::RGBForeColor( &Color_White );
		::RGBBackColor( &Color_Black );
	}
	
	// Draw the target
	
	Rect r = inRect;		// since we modify it
	
	if ( (r.right - r.left < 12) || (r.bottom - r.top < 12) )
	{
		::PenSize( 1, 1 );
		::FrameOval( &r );
		::InsetRect( &r, 2, 2 );
		::FrameOval( &r );
	}
	else
	{
		::PenSize( 2, 2 );
		::FrameOval( &r );
		::InsetRect( &r, 4, 4 );
		::FrameOval( &r );
	}
}


// ---------------------------------------------------------------------------
// 	GetPixelRect
// ---------------------------------------------------------------------------
// 	Returns the rectangle for a given pixel, relative to either the
// 	superview or the pixelArea. Does not include any boundary whitespace.

Boolean 
CIcon_EditorView::GetPixelRect( SInt32 inHoriz, SInt32 inVert, Rect *outRect, 
								Boolean inPixelAreaRelative )
{
	SetRect( outRect, 0, 0, 0, 0 );			// in case of error
	
	if ( (inHoriz < 0) || (inHoriz >= mImageWidth) ) return( false );
	if ( (inVert < 0 ) || (inVert >= mImageHeight) ) return( false );
	
	SInt32	totalCellWidth = mCellWidth + mSpaceBetween;
	
	*outRect = mFirstRect;
	::OffsetRect( outRect, inHoriz * totalCellWidth, inVert * totalCellWidth );
	
	if ( inPixelAreaRelative )
		::OffsetRect( outRect, kIconSideMargin-mPixelArea.left, kIconSideMargin-mPixelArea.top );
	
	return( true );
}


// ---------------------------------------------------------------------------
// 	MapPointToCell
// ---------------------------------------------------------------------------
// 	inPoint is in local coordinates (0,0 at top/left of superview). Returns
// 	true if point is within the canvas. If point is outside the canvas,
// 	outH & outV will contain values outside the canvas. this is useful for
// 	continuing to track the mouse while it's down.

Boolean 
CIcon_EditorView::MapPointToCell( Point inPoint, SInt32 *outH, SInt32 *outV, Boolean roundNegsDown )
{
	SInt32	dh = inPoint.h - mFirstRect.left;
	SInt32	dv = inPoint.v - mFirstRect.top;
	SInt32	totalCellWidth = mCellWidth + mSpaceBetween;
	
	*outH = dh / totalCellWidth;
	*outV = dv / totalCellWidth;

// 	#ifdef MARQUEE_FIX_NO_GOOD_HERE
// 	if ( mSpaceBetween == 0 )
// 	{
// 		++*outH;
// 		++*outV;
// 	}
	
	if ( roundNegsDown )
	{
		// Negative pixels should round to the left, not to zero (needed
		// for PTSelectionAction to select the zero'th pixel)
		if ( dh < 0 )
			--*outH;
			
		if ( dv < 0 )
			--*outV;
	}
	
	return ( 	(inPoint.h >= mPixelArea.left) &&
				(inPoint.h <= mPixelArea.right) &&
				(inPoint.v >= mPixelArea.top) &&
				(inPoint.v <= mPixelArea.bottom) &&
				(*outH >= 0) && (*outH < mImageWidth) &&
				(*outV >= 0) && (*outV < mImageHeight) 
			);
}


// ---------------------------------------------------------------------------
// 	MapRectToCanvas
// ---------------------------------------------------------------------------
// 	Given a rectangle in the source image (0,0-32,32 for icons), this
// 	function returns a rectangle in the canvas that encloses those pixels.
// 	The area is in the white space between pixels (if there is any).
// 	Parameters:
// 	    inRect	- relative to pixmap (0,0 is top left)
// 	    outrect	- in PP local coords (relative to superview).

void 
CIcon_EditorView::MapRectToCanvas( const Rect &inRect, Rect *outRect )
{
	ThrowIfNil_( outRect );

	if ( ::EmptyRect( &inRect ) )
	{
		::SetRect( outRect, 0, 0, 0, 0 );
		return;
	}
	
	SInt32	totalCellWidth = mCellWidth + mSpaceBetween;
	
	outRect->left = mFirstRect.left + inRect.left * totalCellWidth;
	outRect->right = mFirstRect.left + inRect.right * totalCellWidth;
	outRect->top = mFirstRect.top + inRect.top * totalCellWidth;
	outRect->bottom = mFirstRect.top + inRect.bottom * totalCellWidth;
	
	// We want the returned rect to be _outside_ the pixels
	--outRect->left;
	--outRect->top;
}


// ---------------------------------------------------------------------------
// 	MapRegionToCanvas
// ---------------------------------------------------------------------------
// 	Returns a fat-bitted region mapped from the passed selection region.
// 	Parameters:
// 	    inRgn 	- relative to pixmap (0,0 is top left)
// 	    outRgn	- in PP local coords (relative to the canvas since we're an LView).

void 
CIcon_EditorView::MapRegionToCanvas( RgnHandle inRgn, RgnHandle outRgn )
{
	ThrowIfNil_( inRgn );
	ThrowIfNil_( outRgn );				// should never happen
	
	// This is a hack, but MapRgn() always seemed to be one pixel off when
	// we selected a rectangle using the CSelectionAction class. It
	// prevents flicker by *not* having the CSelectionAction class erase
	// it's final rectangle, but then the selection region must line up
	// exactly and we were one pixel off.
	if ( ::IsRegionRectangular(inRgn) )		// just a rect?
	{
		Rect	inRect, outRect;
		
		::GetRegionBounds(inRgn, &inRect);
		this->MapRectToCanvas( inRect, &outRect );
		::RectRgn( outRgn, &outRect );
		return;
	} else {
		Rect		sourceR;
		::SetRect( &sourceR, 0, 0, mImageWidth, mImageHeight );

		::CopyRgn( inRgn, outRgn );
		::MapRgn( outRgn, &sourceR, &mPixelArea );
	}
}


// ---------------------------------------------------------------------------
// 	DrawOnePixel
// ---------------------------------------------------------------------------

void 
CIcon_EditorView::DrawOnePixel( SInt32 inHoriz, SInt32 inVert, COffscreen *inBuffer )
{
	Rect	r;
	
	if ( this->GetPixelRect( inHoriz, inVert, &r, false ) )
	{
		Color32		thePixelColor = inBuffer->GetPixelColor( inHoriz, inVert );
		
		this->FocusDraw();
		UColorUtils::SetForeColor32( thePixelColor );
		::PaintRect( &r );	

		if ( (mHotSpot.h == inHoriz) && (mHotSpot.v == inVert) )
			this->DrawHotSpot( inBuffer );
	}
}


// ---------------------------------------------------------------------------
// 	GetInsideDrawingRect
// ---------------------------------------------------------------------------
// 	Used by the paint view to clip when drawing a selection area.

void 
CIcon_EditorView::GetInsideDrawingRect( Rect *outRect )
{
	*outRect = mPixelArea;

	if ( this->GetSpaceBetween() == 0 ) {
		++outRect->right;
		++outRect->bottom;
	}
	
}


// ---------------------------------------------------------------------------
// 	ItemIsAcceptable
// ---------------------------------------------------------------------------

Boolean 
CIcon_EditorView::ItemIsAcceptable( DragReference inDragRef, ItemReference inItemRef )
{
	if ( mOwnerWindow->GetLockFlag() )
		return( false );
	
	return( CImageDragDrop::ItemIsAcceptable( inDragRef, inItemRef ) );
}


// ---------------------------------------------------------------------------
// 	HandleDroppedPicture
// ---------------------------------------------------------------------------

void 
CIcon_EditorView::HandleDroppedPicture( PicHandle inPict, DragReference inDragRef, DragAttributes inAttribs )
{
	if ( mOwnerWindow )
	{
		SDragImageInfo	dragInfo;
		dragInfo.imageType = ImgType_Picture;
		dragInfo.data = (void*) inPict;
		dragInfo.dragRef = inDragRef;
		dragInfo.dragAttribs = inAttribs;
		
		mOwnerWindow->ObeyCommand( cmd_IconDragImage, &dragInfo );	
	}
}


// ---------------------------------------------------------------------------
// 	HandleDroppedOffscreen
// ---------------------------------------------------------------------------

void 
CIcon_EditorView::HandleDroppedOffscreen( COffscreen *inOffscreen, DragReference inDragRef, DragAttributes inAttribs )
{
	if ( mOwnerWindow )
	{
		SDragImageInfo	dragInfo;
		dragInfo.imageType = DragFlavor_Offscreen;
		dragInfo.data = (void*) inOffscreen;
		dragInfo.dragRef = inDragRef;
		dragInfo.dragAttribs = inAttribs;
		
		mOwnerWindow->ObeyCommand( cmd_IconDragImage, &dragInfo );	
	}
}


// ---------------------------------------------------------------------------
// 	Reinitialize
// ---------------------------------------------------------------------------
// 	Change canvas settings.

void 
CIcon_EditorView::Reinitialize( COffscreen *	inOffscreen, 
								RedrawOptions 	inRedraw,
								SInt32	inResize )
{
	ThrowIfNil_( inOffscreen );
	ThrowIfNil_( mOwnerWindow );
	
	Rect		localFrame;
	SInt32		numHGridlines, numVGridlines;
	SInt32		imageWidth = inOffscreen->GetWidth();
	SInt32		imageHeight = inOffscreen->GetHeight();

	// These are new values for our instance variables: we change the real
	// instance variables only if everything was successful so we don't get
	// caught in a funny state.
	COffscreen	*	scratchBuffer = nil;
	SInt32			cellWidth, spaceBetween;
	Rect			pixelArea, firstRect;
	Boolean			showGridlines;
	
	// Find the cell width & space between rows/columns
	cellWidth = mOwnerWindow->GetZoomFactor( imageWidth, imageHeight, &showGridlines );
	spaceBetween = showGridlines ? kIconSpaceBetween : 0;
	
	// Find the number of rows of white lines we need
	if ( spaceBetween == 0 )
	{
		numHGridlines = 0;
		numVGridlines = 0;
	}
	else
	{
		numHGridlines = imageHeight + 1;
		numVGridlines = imageWidth + 1;
	}
	
	CalcLocalFrameRect( localFrame );
	
	// Resize the pane if needed
	if ( inResize & resize_Canvas )
	{
		SInt32	neededWidth = (numVGridlines * spaceBetween) + (cellWidth * imageWidth);
		SInt32	neededHeight = (numHGridlines * spaceBetween) + (cellWidth * imageHeight);
		SInt32	currentWidth = localFrame.right - localFrame.left;
		SInt32	currentHeight = localFrame.bottom - localFrame.top;

		// No gridline mode still requires one pixel of border space on each side
		if ( spaceBetween == 0 )
		{
			neededWidth += 2;
			neededHeight += 2;
		}
	
		SInt16	dh = neededWidth - currentWidth;
		SInt16	dv = neededHeight - currentHeight;
		if ( (dh != 0) || (dv != 0) )
		{
			LView * super = GetSuperView();
			if ( super ) {
				super->ResizeFrameBy( dh, dv, inRedraw == redraw_Later );
			}
// 			this->ResizeFrameBy( dh, dv, inRedraw == redraw_Later );

			if ( inResize & resize_MoveSamples )
				this->MoveSamplePanes( dh, dv, inRedraw == redraw_Later );

			if ( inResize & resize_Window )
			{
				mOwnerWindow->ResizeWindowIfNeeded();
			}
			
			CalcLocalFrameRect( localFrame );			// this may have been changed
		}
	
	}
	
	// Calculate the new pixel location information
	pixelArea.left = localFrame.left;
	pixelArea.right = pixelArea.left + (numVGridlines * spaceBetween) + (cellWidth * imageWidth);
	pixelArea.top = localFrame.top;
	pixelArea.bottom = pixelArea.top + (numHGridlines * spaceBetween) + (cellWidth * imageHeight);
	
	// The first pixel is drawn here
	firstRect.left = pixelArea.left + kIconSideMargin;
	firstRect.right = firstRect.left + cellWidth;
	firstRect.top = pixelArea.top + kIconSideMargin;
	firstRect.bottom = firstRect.top + cellWidth;

	// Everything was successful, so update our instance variables
	mCellWidth = cellWidth;
	mSpaceBetween = spaceBetween;
	mPixelArea = pixelArea;
	mFirstRect = firstRect;
	mImageWidth = imageWidth;
	mImageHeight = imageHeight;
	
	// Redraw as desired
	UIconMisc::RedrawPaneAsIndicated( this, inRedraw );
}


// ---------------------------------------------------------------------------
// 	MoveSamplePanes
// ---------------------------------------------------------------------------

void 
CIcon_EditorView::MoveSamplePanes( SInt16 dh, SInt16 /*dv*/, Boolean inRedraw )
{
	LPane *samplePane = mOwnerWindow->FindPaneByID( item_IconSampleWell );
	if ( samplePane ) {
		samplePane->MoveBy( dh, 0, inRedraw );
	}
}


// ---------------------------------------------------------------------------
// 	DrawFrom
// ---------------------------------------------------------------------------

void 
CIcon_EditorView::DrawFrom( COffscreen *inBuffer, const Rect *inSourceRect )
{
	StGWorldSaver		aSaver;
	Rect				sourceR, offscreenR, windowR, tempDestR;
	
	if ( !inBuffer ) return;
	
	// Get ready to draw
	SInt32 	totalCellWidth = mCellWidth + mSpaceBetween;
	SInt32 	totalCellHeight = totalCellWidth;
	
	// Figure out where everything comes from and goes.
	// The source is 0,0 relative and _not_ fatbits.
	if ( inSourceRect )
	{
		// Make sure we pin sourceRect to the buffer
		sourceR.left = MAX( 0, inSourceRect->left );
		sourceR.right = MIN( mImageWidth, inSourceRect->right );
		sourceR.top = MAX( 0, inSourceRect->top );
		sourceR.bottom = MIN( mImageHeight, inSourceRect->bottom );
	}
	else
		::SetRect( &sourceR, 0, 0, mImageWidth, mImageHeight );
		
	// The offscreen is 0,0-relative and fatbits
	offscreenR.left = sourceR.left * totalCellWidth;
	offscreenR.right = sourceR.right * totalCellWidth + kIconSideMargin;
	offscreenR.top = sourceR.top * totalCellHeight;
	offscreenR.bottom = sourceR.bottom * totalCellHeight + kIconSideMargin;
	
	// The window area is port relative and fatbits
	windowR = offscreenR;
	::OffsetRect( &windowR, mPixelArea.left, mPixelArea.top );
	LocalToPortPoint( topLeft( windowR ) );
	LocalToPortPoint( botRight( windowR ) );
	
	// If we're not drawing gridlines, we can just CopyBits directly to the
	// screen. This is much faster than copying twice (once to our
	// offscreen buffer, once to the screen).
	if ( mSpaceBetween == 0 )
	{
		// Make sure when we draw we overwrite the right/bottom pixel since
		// the drawing code is often used to overwrite the selection marquee.
		this->FocusDraw();
		::RGBForeColor( &Color_White );
		::MoveTo( mPixelArea.right, mPixelArea.top );
		::Line( 0, mPixelArea.bottom - mPixelArea.top );
		::MoveTo( 0, mPixelArea.bottom );
		::Line( mPixelArea.right - mPixelArea.left, 0 );
	
		// The window rect is one pixel too big (it includes the side margin)
		tempDestR = windowR;
		tempDestR.right -= kIconSideMargin;
		tempDestR.bottom -= kIconSideMargin;

		inBuffer->CopyTo( this->GetMacPort(), &tempDestR, &sourceR );

		if ( this->HasHotSpot() && ::PtInRect( mHotSpot, &sourceR ) )
			this->DrawHotSpot( inBuffer );
		return;
	}
	
	// We are drawing gridlines, so we must copy the image into the big
	// scratch buffer first. This stretches the image into fatbits. It's
	// possible that our scratch buffer isn't big enough, so we might have
	// to call CopyBits more than once.
	SInt32		scratchWidth = sBigScratchBuffer->GetWidth();
	SInt32		scratchHeight = sBigScratchBuffer->GetHeight();
	
	SInt32		sourceWidth = sourceR.right - sourceR.left;
	SInt32		sourceHeight = sourceR.bottom - sourceR.top;
	
	SInt32		destWidth = sourceWidth * totalCellWidth + kIconSideMargin;
	SInt32		destHeight = sourceHeight * totalCellHeight + kIconSideMargin;
	
	SInt32		hLoops = 1 + (destWidth - 1) / scratchWidth;
	SInt32		vLoops = 1 + (destHeight - 1) / scratchHeight;
	
	SInt32		destIncH = (destWidth - kIconSideMargin) / hLoops;
	SInt32		destIncV = (destHeight - kIconSideMargin) / vLoops;
	
	SInt32		sourceIncH = sourceWidth / hLoops;
	SInt32		sourceIncV = sourceHeight / vLoops;
	
	GrafPtr		macPort = this->GetMacPort();
	
	Rect		sourcePortion, destPortion;
	
	for ( SInt32 vCount = 0; vCount < vLoops; vCount++ )
	{
		sourcePortion.top = sourceR.top + vCount * sourceIncV;
		sourcePortion.bottom = MIN( sourceR.bottom, sourcePortion.top + sourceIncV );

		destPortion.top = windowR.top + vCount * destIncV;
		destPortion.bottom = MIN( windowR.bottom, destPortion.top + destIncV );
		
		for ( SInt32 hCount = 0; hCount < hLoops; hCount++ )
		{
			sourcePortion.left = sourceR.left + hCount * sourceIncH;
			sourcePortion.right = MIN( sourceR.right, sourcePortion.left + sourceIncH );

			destPortion.left = windowR.left + hCount * destIncH;
			destPortion.right = MIN( windowR.right, destPortion.left + destIncH );
			
			this->DrawPortionOfBuffer( inBuffer, sourcePortion, macPort, destPortion );
		}
	}

	// Draw the hotspot
	if ( this->HasHotSpot() && ::PtInRect( mHotSpot, &sourceR ) )
		this->DrawHotSpot( inBuffer );
	
}


// ---------------------------------------------------------------------------
// 	DrawPortionOfBuffer
// ---------------------------------------------------------------------------
// 	We actually draw 1 pixel of border outside of the inDestR parameter (right/bottom).

void 
CIcon_EditorView::DrawPortionOfBuffer( COffscreen *inSource, const Rect &inSourceR, 
									GrafPtr inDest, const Rect &inDestR )
{
	SInt32 	totalCellWidth = mCellWidth + mSpaceBetween;
	SInt32 	totalCellHeight = totalCellWidth;
	SInt32	sourceWidth = inSourceR.right - inSourceR.left;
	SInt32	sourceHeight = inSourceR.bottom - inSourceR.top;
	
	Rect	bufferR;
	
	// Expand the source image into the offscreen buffer
	bufferR.left = 0;
	bufferR.right = totalCellWidth * sourceWidth;
	bufferR.top = 0;
	bufferR.bottom = totalCellHeight * sourceHeight;
	
	sBigScratchBuffer->CopyFrom( inSource, &bufferR, &inSourceR );

	// Draw the horizontal gridlines.
	//     (1) we are drawing into an offscreen, so draw relative to 0,0
	//     (2) we draw one more gridline than pixel
	sBigScratchBuffer->BeginDrawing();
	
	RGBForeColor( &Color_White );
	
	SInt32 v = bufferR.top;
	for ( SInt32 rowCount = inSourceR.top; rowCount <= inSourceR.bottom; rowCount++ )
	{
		::MoveTo( bufferR.left, v );
		::LineTo( bufferR.right, v );
		v += totalCellWidth;
	}
	
	// Draw the vertical gridlines.
	SInt32 h = bufferR.left;
	for ( SInt32 colCount = inSourceR.left; colCount <= inSourceR.right; colCount++ )
	{
		::MoveTo( h, bufferR.top );
		::LineTo( h, bufferR.bottom );
		h += totalCellWidth;
	}

	// Overlay the hotspot (if any)
	if ( (mHotSpot.h >= inSourceR.left) && (mHotSpot.h < inSourceR.right) &&
		 (mHotSpot.v >= inSourceR.top)  && (mHotSpot.v < inSourceR.bottom) )
	{
		Rect	hotSpotR;
		
		// Get the rectangle and offset it to it hits our offscreen buffer
		// in the correct spot
		this->GetPixelRect( mHotSpot.h, mHotSpot.v, &hotSpotR, false );
		//::OffsetRect( &hotSpotR, -inDestR.left, -inDestR.top );
		
		Color32 theColor = inSource->GetPixelColor( mHotSpot.h, mHotSpot.v );
		this->DrawHotSpotSelf( theColor, hotSpotR );
	}
			
	sBigScratchBuffer->EndDrawing();

	// Copy the gridlined image to the screen.
	// The one extra pixel in the source & destination is for the right/bottom gridline.
	++bufferR.right;
	++bufferR.bottom;
	Rect	tempDestR = inDestR;
	++tempDestR.right;
	++tempDestR.bottom;
	
	sBigScratchBuffer->CopyTo( inDest, &tempDestR, &bufferR );
}


// ---------------------------------------------------------------------------
// 	GetSpaceBetween
// ---------------------------------------------------------------------------

SInt32 
CIcon_EditorView::GetSpaceBetween()
{
	return( mSpaceBetween );
}




PP_End_Namespace_PowerPlant
