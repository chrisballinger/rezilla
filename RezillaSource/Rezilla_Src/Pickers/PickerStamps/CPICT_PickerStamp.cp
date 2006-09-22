// ===========================================================================
// 	CPICT_PickerStamp.cp
// 
//                       Created : 2006-09-20 18:39:04
//             Last modification : 2006-09-21 09:32:42
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@users.sourceforge.net>
// www : <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2006
// All rights reserved.
// ===========================================================================
// The stamp is the part of a picker view where the image is drawn. The
// StampSize method returns the dimensions of this drawing area.


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CPICT_PickerStamp.h"
#include "CPickerView.h"
#include "UResources.h"

#include <LPane.h>
#include <Icons.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   CPICT_PickerStamp							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CPICT_PickerStamp::CPICT_PickerStamp(
									CPickerView *		inParent,
									const SPaneInfo&	inPaneInfo,
									const SViewInfo&	inViewInfo)
	: CPickerStamp(inParent, inPaneInfo, inViewInfo)
{
}


// ---------------------------------------------------------------------------
//   ~CPICT_PickerStamp							Destructor				  [public]
// ---------------------------------------------------------------------------

CPICT_PickerStamp::~CPICT_PickerStamp()
{
}


// ---------------------------------------------------------------------------
//   StampSize														  [public]
// ---------------------------------------------------------------------------

void
CPICT_PickerStamp::StampSize(ResType inType, SInt16 &outWidth, SInt16 &outHeight)
{
#pragma unused(inType)
	outWidth = 250;
	outHeight = 250;
}


// ---------------------------------------------------------------------------
//   AdjustStampSize												  [public]
// ---------------------------------------------------------------------------

void
CPICT_PickerStamp::AdjustStampSize(Rect inBounds)
{
	SInt16			picHeight, picWidth;
	SInt16			newHeight, newWidth;
	SDimension16	stampSize;
	SPoint32		stampLoc;
	
	picHeight = inBounds.bottom - inBounds.top;
	picWidth = inBounds.right - inBounds.left;
	GetFrameSize(stampSize);
	GetFrameLocation(stampLoc);
	
	if (picHeight > picWidth) {
		newWidth = stampSize.height * picWidth / picHeight;
		ResizeFrameTo(newWidth, stampSize.height, false);
		MoveBy((stampSize.width - newWidth)/2, 0, false);
	} else if (picHeight < picWidth) {
		newHeight = stampSize.width * picHeight / picWidth ;
		ResizeFrameTo(stampSize.width, newHeight, false);
		MoveBy(0, (stampSize.height - newHeight)/2, false);
	} 
}



// ---------------------------------------------------------------------------
//   DrawSelf														  [public]
// ---------------------------------------------------------------------------

void
CPICT_PickerStamp::DrawSelf()
{
	// The resID is the paneID of the PickerView
	ResIDT theID = mParent->GetPaneID();
	short theRefNum = mParent->GetUserCon();
	
	if (theRefNum != kResFileNotOpened) {
		Rect	frame, bounds;
		Handle	thePictureH = NULL;
		StRezRefSaver saver(theRefNum);

		thePictureH = (Handle) ::GetPicture(theID);
		// thePictureH = ::Get1Resource('PICT', theID);
		::HandToHand(&thePictureH);

		if (thePictureH) {
			::QDGetPictureBounds( (PicHandle) thePictureH, &bounds);
			AdjustStampSize(bounds);
			
			FocusDraw();
			CalcLocalFrameRect(frame);
			::DrawPicture( (PicHandle)thePictureH, &frame);
			::DisposeHandle(thePictureH);
		} 
	}
}




PP_End_Namespace_PowerPlant
