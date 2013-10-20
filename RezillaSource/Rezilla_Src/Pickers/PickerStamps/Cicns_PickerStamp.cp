// ===========================================================================
// 	Cicns_PickerStamp.cp
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

#include "Cicns_PickerStamp.h"
#include "CPickerView.h"
#include "UResources.h"

#ifndef __MACH__
#include <Icons.h>
#endif

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   Cicns_PickerStamp							Default Constructor		  [public]
// ---------------------------------------------------------------------------

Cicns_PickerStamp::Cicns_PickerStamp(
									CPickerView *		inParent,
									const SPaneInfo&	inPaneInfo,
									const SViewInfo&	inViewInfo)
	: CPickerStamp(inParent, inPaneInfo, inViewInfo)
{
}


// ---------------------------------------------------------------------------
//   ~Cicns_PickerStamp							Destructor				  [public]
// ---------------------------------------------------------------------------

Cicns_PickerStamp::~Cicns_PickerStamp()
{
}


// ---------------------------------------------------------------------------
//   StampSize														  [public]
// ---------------------------------------------------------------------------

void
Cicns_PickerStamp::StampSize(ResType inType, SInt16 &outWidth, SInt16 &outHeight)
{
#pragma unused(inType)
	outWidth = 128;
	outHeight = 128;
}


// ---------------------------------------------------------------------------
//   DrawSelf														  [public]
// ---------------------------------------------------------------------------

void
Cicns_PickerStamp::DrawSelf()
{
	// The resID is the paneID of the PickerView
	ResIDT theID = mParent->GetPaneID();
	short theRefNum = mParent->GetUserCon();
	
	if (theRefNum != kResFileNotOpened) {
		Rect	frame;
		Handle	theIconHandle = NULL;
		StRezRefSaver saver(theRefNum);
		
		theIconHandle = ::Get1Resource(kIconFamilyType, theID);
		::HandToHand(&theIconHandle);

		if (theIconHandle) {
			IconRef		theIconRef;
			
			FocusDraw();
			CalcLocalFrameRect(frame);
			::GetIconRefFromIconFamilyPtr(*(IconFamilyHandle)theIconHandle, ::GetHandleSize(theIconHandle), &theIconRef);
			::PlotIconRef(&frame, kAlignAbsoluteCenter, mParent->IsSelected() ? kTransformSelected : kTransformNone, kIconServicesNormalUsageFlag, theIconRef);
			::ReleaseIconRef(theIconRef);
			::DisposeHandle(theIconHandle);
		} 
	}
}


PP_End_Namespace_PowerPlant
