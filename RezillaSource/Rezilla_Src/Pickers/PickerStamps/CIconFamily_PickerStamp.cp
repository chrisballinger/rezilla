// ===========================================================================
// 	CIconFamily_PickerStamp.cp
// 
//                       Created : 2006-02-25 17:40:43
//             Last modification : 2006-09-22 11:55:29
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
#include "CPickerWindow.h"
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
//   GetTypeInfo													  [private]
// ---------------------------------------------------------------------------

void
CIconFamily_PickerStamp::GetTypeInfo(ResType inType, SInt32 &outWidth, SInt32 &outHeight, 
									 SInt32 &outDepth, SInt32 &outRowBytes, SInt32 &outOffset)
{
	switch (inType) {
		case 'icl8':
		outWidth = 32;
		outHeight = 32;
		outDepth = 8;
		outRowBytes = 32;
		outOffset = 0;
		break;

		case 'icl4':
		outWidth = 32;
		outHeight = 32;
		outDepth = 4;
		outRowBytes = 16;
		outOffset = 0;
		break;

		case 'ICN#':
		outWidth = 32;
		outHeight = 32;
		outDepth = 1;
		outRowBytes = 4;
		outOffset = 128;
		break;

		case 'ics8':
		outWidth = 16;
		outHeight = 16;
		outDepth = 8;
		outRowBytes = 16;
		outOffset = 0;
		break;

		case 'ics4':
		outWidth = 16;
		outHeight = 16;
		outDepth = 4;
		outRowBytes = 8;
		outOffset = 0;
		break;

		case 'ics#':
		outWidth = 16;
		outHeight = 16;
		outDepth = 1;
		outRowBytes = 2;
		outOffset = 32;
		break;

		case 'icm8':
		outWidth = 16;
		outHeight = 12;
		outDepth = 8;
		outRowBytes = 16;
		outOffset = 0;
		break;

		case 'icm4':
		outWidth = 16;
		outHeight = 12;
		outDepth = 4;
		outRowBytes = 8;
		outOffset = 0;
		break;

		case 'icm#':
		outWidth = 16;
		outHeight = 12;
		outDepth = 1;
		outRowBytes = 2;
		outOffset = 24;
		break;
		
	}
}


// ---------------------------------------------------------------------------
//   DrawSelf														  [public]
// ---------------------------------------------------------------------------
// kAlignAbsoluteCenter  kTransformSelected
// CTabHandle		theTable = UColorUtils::GetColorTable( inDepth );

void
CIconFamily_PickerStamp::DrawSelf()
{
	// The resID is the paneID of the PickerView
	ResIDT theID = mParent->GetPaneID();
	short theRefNum = mParent->GetUserCon();
	ResType		theType = mParent->GetOwnerWindow()->GetType();
	
	if (theRefNum != kResFileNotOpened) {
		Rect	frame;
		FocusDraw();
		CalcLocalFrameRect(frame);
		StRezRefSaver saver(theRefNum);		
		
// 		DrawBuffer();
		
	}
}


PP_End_Namespace_PowerPlant
