// ===========================================================================
// 	CSTRx_PickerStamp.cp
// 
//                       Created : 2006-02-25 17:40:43
//             Last modification : 2006-09-30 06:32:09
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
#include "CPickerWindow.h"
#include "CPickerView.h"
#include "CStaticClickThrough.h"
#include "CMenuObject.h"
#include "UResources.h"
#include "UMiscUtils.h"
#include "RezillaConstants.h"

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

	mStaticField = new CStaticClickThrough(pi, "\p", Txtr_MonacoNineBlue);

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
	switch (inType) {
		case 'STR#':
		outWidth = 120;
		outHeight = 120;
		break;
		
		case 'RID#':
		outWidth = 60;
		outHeight = 120;
		break;	
		
		case 'RidL':
		outWidth = 75;
		outHeight = 120;
		break;	
		
		case 'Mcmd':
		case 'MBAR':
		outWidth = 100;
		outHeight = 120;
		break;					
	}
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
		ResType	theType = mParent->GetOwnerWindow()->GetType();
		short	theRefNum = mParent->GetUserCon();
		LStr255	theText("\p");
		Str255	theLine, theCountStr;
		UInt16	i, theCount = 0, numStrings = 0, maxNum = 9;
		StRezRefSaver saver(theRefNum);
		SInt16	theSInt16;
		SInt32	theSInt32;
		
		Handle theStrHandle = ::Get1Resource(theType, theID);
		::HandToHand(&theStrHandle);
		
		if (theStrHandle != NULL) {
			LHandleStream * theStream = new LHandleStream(theStrHandle);
			Boolean			truncated;
			
			if (::GetHandleSize(theStrHandle) > 2) {
				*theStream >> numStrings;
				theCount = numStrings;
			} 
			
			if (theType == 'Mcmd') {
				if ( CMenuObject::GetMenuTitle(theID, theRefNum, theLine) ) {
					theText += theLine;
				} else {
					theText += "\pn/a";
				}
				theText += "\p\r";
				maxNum--;
			} 
			if (theCount > maxNum) {
				theCount = maxNum;
			} 

			for (i = 1; i <= theCount; i++) {
				truncated = false;
				
				switch (theType) {
					case 'STR#':
					*theStream >> theLine;
					break;
					
					case 'MBAR':
					*theStream >> theSInt16;
					if ( ! CMenuObject::GetMenuTitle(theSInt16, theRefNum, theLine) ) {
						::NumToString( (long)theSInt16, theLine);
					} 
					break;
					
					case 'RID#':
					*theStream >> theSInt16;
					::NumToString( (long)theSInt16, theLine);
					break;
					
					case 'Mcmd':
					case 'RidL':
					*theStream >> theSInt32;
					if (theSInt32 > '    ') {
						// If the value is big enough, assume it is the decimal
						// value of an OSType and display this type in quotes
						Str255	typeStr;
						theLine[0] = 0;
						UMiscUtils::OSTypeToPString( (OSType)theSInt32, typeStr);
						PLstrcat(theLine, "\p'");
						PLstrcat(theLine, typeStr);
						PLstrcat(theLine, "\p'");
					} else {
						::NumToString(theSInt32, theLine);
					}
					break;					
				}
				
				if (theLine[0] > 17) {
					theLine[0] = 17;
					truncated = true;
				} 
				::NumToString(i, theCountStr);
				theText += theCountStr;
				theText += "\p- ";

				theText += theLine;
				if (truncated) {
					theText += "\pÉ";
				} 
				theText += "\p\r";
			}
			if (numStrings > maxNum) {
				theText += "\pÉ";
			} 
			
			mStaticField->SetDescriptor(theText);			
			delete theStream;
		} 
	} 
}



PP_End_Namespace_PowerPlant
