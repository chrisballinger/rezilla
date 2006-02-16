// ===========================================================================
// CPICT_EditorView.h
// 
//                       Created: 2004-12-06 14:54:09
//             Last modification: 2005-03-07 19:32:23
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2004, 2005
// All rights reserved.
// ===========================================================================
//	Displays a 'PICT' resource


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CPICT_EditorView.h"
#include "CPICT_EditorWindow.h"
#include "RezillaConstants.h"

#include <LStream.h>
#include <UDrawingState.h>

PP_Begin_Namespace_PowerPlant

// dynamic_cast<CPICT_EditorDoc *>(mOwnerWindow->GetOwnerDoc())-> ;


// ---------------------------------------------------------------------------
//   CPICT_EditorView								Stream Constructor [public]
// ---------------------------------------------------------------------------

CPICT_EditorView::CPICT_EditorView(
	LStream*	inStream)

	: LView(inStream)
{
	mHasFrame = false;
	mPictureH = nil;
}


// ---------------------------------------------------------------------------
//   CPICT_EditorView								Constructor		  [public]
// ---------------------------------------------------------------------------

CPICT_EditorView::CPICT_EditorView(
	ResIDT	inPictureID)			// 'PICT' Resource ID
{
	mHasFrame = false;
	mPictureH = ::GetPicture(inPictureID);
	AdaptPicture();
}


// ---------------------------------------------------------------------------
//	~CPICT_EditorView								Destructor		  [public]
// ---------------------------------------------------------------------------

CPICT_EditorView::~CPICT_EditorView()
{
	if (mPictureH != nil) {
		::DisposeHandle( (Handle) mPictureH);
	}
}


// ---------------------------------------------------------------------------
//   AdaptPicture													 [private]
// ---------------------------------------------------------------------------
//	Assumes mPictureH is set. If the PICT handle exists, set the Image size
//	to the size of the picture.

void
CPICT_EditorView::AdaptPicture()
{
	mRefreshAllWhenResized = false;
	
	if (mPictureH != nil) {
		Rect	picFrame = (**mPictureH).picFrame;
		ResizeImageTo(picFrame.right - picFrame.left,
					  picFrame.bottom - picFrame.top, false);
	} 
}


// ---------------------------------------------------------------------------
//   ErasePicture													 [private]
// ---------------------------------------------------------------------------

void
CPICT_EditorView::ErasePicture()
{
	Rect	theFrame;
	CalcLocalFrameRect(theFrame);
	ApplyForeAndBackColors();
	::EraseRect(&theFrame);
}


// ---------------------------------------------------------------------------
//   SetPictureH													[public]
// ---------------------------------------------------------------------------
void
CPICT_EditorView::SetPictureH(PicHandle inPictureH) 
{
	if (mPictureH != nil) {
		::DisposeHandle( (Handle) mPictureH);	
	}

	mPictureH = inPictureH;
	ErasePicture();
	AdaptPicture();
	mOwnerWindow->Refresh();
}


// ---------------------------------------------------------------------------
//   DrawSelf													   [protected]
// ---------------------------------------------------------------------------
// Draw the picture. If the Picture handle exists, draw it. Otherwise, fill
// the Frame with a light gray pattern and a one-pixel border.

void
CPICT_EditorView::DrawSelf()
{
	if (mPictureH != nil) {

		SDimension32	imageSize;
		GetImageSize(imageSize);

		Rect	pictureBounds;
		pictureBounds.left   = 0;
		pictureBounds.top    = 0;
		pictureBounds.right  = (SInt16) imageSize.width;
		pictureBounds.bottom = (SInt16) imageSize.height;

		::DrawPicture(mPictureH, &pictureBounds);
		
	} else {
		Rect	frame;
		CalcLocalFrameRect(frame);
		::PenNormal();

		Pattern		ltGrayPat;
		::MacFillRect(&frame, UQDGlobals::GetLightGrayPat(&ltGrayPat));

		::MacFrameRect(&frame);
	}
}


// ---------------------------------------------------------------------------
//   Click
// ---------------------------------------------------------------------------
//	Handle a click inside the picture view by alternately drawing or 
//	erasing a border around the image.

void
CPICT_EditorView::Click(
	SMouseDownEvent	&inMouseDown)
{
#pragma unused (inMouseDown)
	
	if (mPictureH == nil) { return; } 
	
	if (mHasFrame) {
		mHasFrame = false;
	} else {
		mHasFrame = true;
	}
	DrawBorder(mHasFrame);
}



// ---------------------------------------------------------------------------
//   DrawBorder
// ---------------------------------------------------------------------------
//  Border around a picture is outset from the interior by 1 pixel.

void
CPICT_EditorView::DrawBorder(Boolean inVisibility)
{
	StColorState	saveColors;			// Preserve color state
	StGrafPortSaver	savePort;
	RGBColor		theColor;
	SDimension32	imageSize;
	Rect			pictureBounds;

	if (inVisibility) {
		theColor = Color_Red;
	} else {
		theColor = Color_White;
	}
	
	GetImageSize(imageSize);

	pictureBounds.left   = 0;
	pictureBounds.top    = 0;
	pictureBounds.right  = (SInt16) imageSize.width;
	pictureBounds.bottom = (SInt16) imageSize.height;
	
	FocusDraw();
	
	// Adjust the parameters
	::MacInsetRect(&pictureBounds, 1, 1);
	::RGBForeColor(&theColor);	
	::PenNormal();
	::PenSize(1, 1);
	
	// Draw border around the view
	::RGBForeColor(&theColor);
	::FrameRect( &pictureBounds );
}



PP_End_Namespace_PowerPlant
