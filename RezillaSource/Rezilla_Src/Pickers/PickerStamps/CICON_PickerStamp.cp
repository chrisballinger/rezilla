// ===========================================================================
// 	CICON_PickerStamp.cp
// 
//                       Created : 2006-02-25 17:40:43
//             Last modification : 2006-09-20 08:18:59
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

#include "CICON_PickerStamp.h"
#include "CPickerView.h"
#include "UResources.h"

#include <Icons.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   CICON_PickerStamp							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CICON_PickerStamp::CICON_PickerStamp(
									CPickerView *		inParent,
									const SPaneInfo&	inPaneInfo,
									const SViewInfo&	inViewInfo)
	: CPickerStamp(inParent, inPaneInfo, inViewInfo)
{
}


// ---------------------------------------------------------------------------
//   ~CICON_PickerStamp							Destructor				  [public]
// ---------------------------------------------------------------------------

CICON_PickerStamp::~CICON_PickerStamp()
{
}


// ---------------------------------------------------------------------------
//   StampSize														  [public]
// ---------------------------------------------------------------------------
// f the destination rectangle is not 32 by 32 pixels, the PlotIcon
// function stretches or shrinks the icon to fit.

void
CICON_PickerStamp::StampSize(ResType inType, SInt16 &outWidth, SInt16 &outHeight)
{
#pragma unused(inType)
	outWidth = 32;
	outHeight = 32;
}


// ---------------------------------------------------------------------------
//   DrawSelf														  [public]
// ---------------------------------------------------------------------------
// GetIcon: Gets a handle to an icon resource of type 'ICON'. When you are
// finished using a handle obtained from this function, use the
// ReleaseResource function to release the memory occupied by the icon
// resource data.
// PlotIconHandle: Draws an icon of resource type 'ICON' or 'ICN#' to which
// you have a handle.
// PlotIco: This function does not allow you to specify any transforms or alignment.
// The PlotIcon function uses the QuickDraw function CopyBits with the
// srcCopy transfer mode. To plot an icon of resource type 'ICON' with a
// specified transform and alignment, use the PlotIconHandle function.

void
CICON_PickerStamp::DrawSelf()
{
	// The resID is the paneID of the PickerView
	ResIDT theID = mParent->GetPaneID();
	short theRefNum = mParent->GetUserCon();;
	
	if (theRefNum != kResFileNotOpened) {
		Rect	frame;
		Handle	theIconHandle = NULL;
		
		FocusDraw();
		CalcLocalFrameRect(frame);
		StRezRefSaver saver(theRefNum);
		theIconHandle = GetIcon(theID);
		if (theIconHandle) {
// 			::PlotIcon(&frame, theIconHandle);
			::PlotIconHandle(&frame, kAlignAbsoluteCenter, 
					 mParent->IsSelected() ? kTransformSelected : kTransformNone, theIconHandle);
			::ReleaseResource(theIconHandle);
		} 
	}
}


PP_End_Namespace_PowerPlant
