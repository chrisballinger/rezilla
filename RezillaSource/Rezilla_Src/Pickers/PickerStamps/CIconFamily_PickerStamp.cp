// ===========================================================================
// 	CIconFamily_PickerStamp.cp
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

#include "CIconFamily_PickerStamp.h"
#include "CPickerView.h"
#include "UResources.h"

#include <Icons.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   CIconFamily_PickerStamp							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CIconFamily_PickerStamp::CIconFamily_PickerStamp(
									CPickerView *		inParent,
									const SPaneInfo&	inPaneInfo,
									const SViewInfo&	inViewInfo)
	: CPickerStamp(inParent, inPaneInfo, inViewInfo)
{
}


// ---------------------------------------------------------------------------
//   ~CIconFamily_PickerStamp							Destructor				  [public]
// ---------------------------------------------------------------------------

CIconFamily_PickerStamp::~CIconFamily_PickerStamp()
{
}


// ---------------------------------------------------------------------------
//   StampSize														  [public]
// ---------------------------------------------------------------------------

void
CIconFamily_PickerStamp::StampSize(ResType inType, SInt16 &outWidth, SInt16 &outHeight)
{
	switch (inType) {
		case 'ics#':
		case 'ics4':
		case 'ics8':
		// 16x16 small icons
		outWidth = 16;
		outHeight = 16;
		break;
		
		case 'ICN#':
		case 'icl4':
		case 'icl8':
		// 32x32 large icons
		outWidth = 32;
		outHeight = 32;
		break;
		
		case 'icm#':
		case 'icm4':
		case 'icm8':
		// 16x12 medium icons
		outWidth = 16;
		outHeight = 12;
		break;
		
		default:
		break;
		
	}
}


// ---------------------------------------------------------------------------
//   DrawSelf														  [public]
// ---------------------------------------------------------------------------
// kAlignAbsoluteCenter  kTransformSelected

void
CIconFamily_PickerStamp::DrawSelf()
{
	// The resID is the paneID of the PickerView
	ResIDT theID = mParent->GetPaneID();
	short theRefNum = mParent->GetUserCon();
	
	if (theRefNum != kResFileNotOpened) {
		Rect	frame;
		FocusDraw();
		CalcLocalFrameRect(frame);
		StRezRefSaver saver(theRefNum);		
		::PlotIconID(&frame, kAlignAbsoluteCenter, 
					 mParent->IsSelected() ? kTransformSelected : kTransformNone, 
					 theID);
	}
}


PP_End_Namespace_PowerPlant
