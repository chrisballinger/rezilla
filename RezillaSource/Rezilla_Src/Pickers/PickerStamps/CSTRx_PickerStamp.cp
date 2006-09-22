// ===========================================================================
// 	CSTRx_PickerStamp.cp
// 
//                       Created : 2006-02-25 17:40:43
//             Last modification : 2006-09-21 10:19:40
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@users.sourceforge.net>
// www : <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2006
// All rights reserved.
// ===========================================================================


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CSTRx_PickerStamp.h"
#include "CPickerView.h"
#include "UResources.h"
#include "RezillaConstants.h"
#include "CStaticClickThrough.h"

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   CSTRx_PickerStamp							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CSTRx_PickerStamp::CSTRx_PickerStamp(
									CPickerView *		inParent,
									const SPaneInfo&	inPaneInfo,
									const SViewInfo&	inViewInfo)
	: CPickerStamp(inParent, inPaneInfo, inViewInfo)
{
	SPaneInfo	pi;
	Rect		frame;

	CalcLocalFrameRect(frame);

	// Static field basic values
	pi.paneID			= 0;
	pi.left				= 0;
	pi.top				= 0;
	pi.width			= frame.right - frame.left;
	pi.height			= frame.bottom - frame.top;
	pi.visible			= true;
	pi.enabled			= true;
	pi.bindings.left	= false;
	pi.bindings.top		= false;
	pi.bindings.right	= false;
	pi.bindings.bottom 	= false;
	pi.userCon			= 0;
	pi.superView		= this;

	mStaticField = new CStaticClickThrough(pi, "\p", Txtr_MonacoNineGray);

}


// ---------------------------------------------------------------------------
//   ~CSTRx_PickerStamp							Destructor				  [public]
// ---------------------------------------------------------------------------

CSTRx_PickerStamp::~CSTRx_PickerStamp()
{
}


// ---------------------------------------------------------------------------
//   StampSize														  [public]
// ---------------------------------------------------------------------------

void
CSTRx_PickerStamp::StampSize(ResType inType, SInt16 &outWidth, SInt16 &outHeight)
{
#pragma unused(inType)
	outWidth = 120;
	outHeight = 120;
}


// ---------------------------------------------------------------------------
//   DrawSelf														  [public]
// ---------------------------------------------------------------------------

void
CSTRx_PickerStamp::DrawSelf()
{
	if (mStaticField != NULL) {
		// The resID is the paneID of the PickerView
		ResIDT	theID = mParent->GetPaneID();
		short	theRefNum = mParent->GetUserCon();
		LStr255	theText("\p");
		Str255	theLine;
		UInt16	i, theCount = 0;
		StRezRefSaver saver(theRefNum);
		
		Handle theStrHandle = ::Get1Resource('STR#', theID);
		::HandToHand(&theStrHandle);
		
		if (theStrHandle != NULL) {
			LHandleStream * theStream = new LHandleStream(theStrHandle);
			Boolean			truncated;
			
			if (::GetHandleSize(theStrHandle) > 2) {
				*theStream >> theCount;
				if (theCount > 10) {
					theCount = 10;
				} 
			} 
			
			for (i = 1; i <= theCount; i++) {
				truncated = false;
				*theStream >> theLine;
				if (theLine[0] == 0) {
					// Skip empty strings
					continue;
				} 
				if (theLine[0] > 20) {
					theLine[0] = 20;
					truncated = true;
				} 
				theText += theLine;
				if (truncated) {
					theText += "\pÉ";
				} 
				theText += "\p\r";
			}
			
			mStaticField->SetDescriptor(theText);			
			delete theStream;
		} 
	} 
}



PP_End_Namespace_PowerPlant
