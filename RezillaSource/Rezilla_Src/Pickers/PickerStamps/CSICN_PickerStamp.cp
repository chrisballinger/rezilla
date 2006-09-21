// ===========================================================================
// 	CSICN_PickerStamp.cp
// 
//                       Created : 2006-02-25 17:40:43
//             Last modification : 2006-09-20 18:34:45
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

#include "CSICN_PickerStamp.h"
#include "CPickerView.h"
#include "UResources.h"

#include <Icons.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   CSICN_PickerStamp							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CSICN_PickerStamp::CSICN_PickerStamp(
									CPickerView *		inParent,
									const SPaneInfo&	inPaneInfo,
									const SViewInfo&	inViewInfo)
	: CPickerStamp(inParent, inPaneInfo, inViewInfo)
{
}


// ---------------------------------------------------------------------------
//   ~CSICN_PickerStamp							Destructor				  [public]
// ---------------------------------------------------------------------------

CSICN_PickerStamp::~CSICN_PickerStamp()
{
}


// ---------------------------------------------------------------------------
//   StampSize														  [public]
// ---------------------------------------------------------------------------
// f the destination rectangle is not 32 by 32 pixels, the PlotIcon
// function stretches or shrinks the icon to fit.

void
CSICN_PickerStamp::StampSize(ResType inType, SInt16 &outWidth, SInt16 &outHeight)
{
#pragma unused(inType)
	outWidth = 16;
	outHeight = 16;
}


// ---------------------------------------------------------------------------
//   DrawSelf														  [public]
// ---------------------------------------------------------------------------
// PlotSICNHandle: Draws a small icon of resource type 'SICN' to which you
// have a handle. You can obtain a handle to the icon using GetResource or
// other Resource Manager functions.
// 
// Note: Only 'SICN' resources with a single member Ñ- or with two members,
// the second of which is a mask for the first Ñ- plot correctly. So the
// strategy is to copy the first bitmap of the family in a new handle.

void
CSICN_PickerStamp::DrawSelf()
{
	// The resID is the paneID of the PickerView
	ResIDT theID = mParent->GetPaneID();
	short theRefNum = mParent->GetUserCon();
	
	if (theRefNum != kResFileNotOpened) {
		Rect	frame;
		Handle	theIconHandle = ::NewHandleClear(32), theResHandle = NULL;
		StRezRefSaver saver(theRefNum);

		FocusDraw();
		CalcLocalFrameRect(frame);
		theResHandle = ::Get1Resource('SICN', theID);
		::HandToHand(&theResHandle);

		if (theIconHandle && theResHandle) {
			if ( ::GetHandleSize(theResHandle) >= 32) {
				::BlockMoveData(*theResHandle, *theIconHandle, 32);
			} 
			::PlotSICNHandle(&frame, kAlignAbsoluteCenter, 
					 mParent->IsSelected() ? kTransformSelected : kTransformNone, theIconHandle);
		} 
		
		if (theResHandle) ::ReleaseResource(theResHandle);
		if (theIconHandle) ::DisposeHandle(theIconHandle);
	}
}



PP_End_Namespace_PowerPlant
