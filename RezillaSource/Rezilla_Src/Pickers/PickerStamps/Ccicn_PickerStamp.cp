// ===========================================================================
// 	Ccicn_PickerStamp.cp
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

#include "Ccicn_PickerStamp.h"
#include "CPickerView.h"
#include "UResources.h"

#ifndef __MACH__
#include <Icons.h>
#endif

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   Ccicn_PickerStamp							Default Constructor		  [public]
// ---------------------------------------------------------------------------

Ccicn_PickerStamp::Ccicn_PickerStamp(
									CPickerView *		inParent,
									const SPaneInfo&	inPaneInfo,
									const SViewInfo&	inViewInfo)
	: CPickerStamp(inParent, inPaneInfo, inViewInfo)
{
}


// ---------------------------------------------------------------------------
//   ~Ccicn_PickerStamp							Destructor				  [public]
// ---------------------------------------------------------------------------

Ccicn_PickerStamp::~Ccicn_PickerStamp()
{
}


// ---------------------------------------------------------------------------
//   StampSize														  [public]
// ---------------------------------------------------------------------------

void
Ccicn_PickerStamp::StampSize(ResType inType, SInt16 &outWidth, SInt16 &outHeight)
{
#pragma unused(inType)
	outWidth = 48;
	outHeight = 48;
}


// ---------------------------------------------------------------------------
//   DrawSelf														  [public]
// ---------------------------------------------------------------------------
// GetCIcon: Gets a handle to a color icon of resource type 'cicn'.
// When you are finished with a handle obtained from this function, use the
// DisposeCIcon function to release the memory occupied by the color icon
// structure.

void
Ccicn_PickerStamp::DrawSelf()
{
	// The resID is the paneID of the PickerView
	ResIDT theID = mParent->GetPaneID();
	short theRefNum = mParent->GetUserCon();
	
	if (theRefNum != kResFileNotOpened) {
		Rect	frame;
		CIconHandle	theIconHandle = NULL;
		
		FocusDraw();
		CalcLocalFrameRect(frame);
		StRezRefSaver saver(theRefNum);
		theIconHandle = ::GetCIcon(theID);
		if (theIconHandle) {
			::PlotCIconHandle(&frame, kAlignAbsoluteCenter, 
					 mParent->IsSelected() ? kTransformSelected : kTransformNone, theIconHandle);
			::DisposeCIcon(theIconHandle);
		} 
	}
}


PP_End_Namespace_PowerPlant
