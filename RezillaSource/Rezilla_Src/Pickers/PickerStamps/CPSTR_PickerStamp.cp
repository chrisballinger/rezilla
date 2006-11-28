// ===========================================================================
// 	CPSTR_PickerStamp.cp
// 
//                       Created : 2006-11-28 15:21:58
//             Last modification : 2006-11-28 15:39:54
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@users.sourceforge.net>
// www : <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2006
// All rights reserved.
// ===========================================================================

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CPSTR_PickerStamp.h"
#include "CPickerWindow.h"
#include "CPickerView.h"
#include "CStaticClickThrough.h"
#include "CMenuObject.h"
#include "UResources.h"
#include "UMiscUtils.h"
#include "RezillaConstants.h"

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   CPSTR_PickerStamp							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CPSTR_PickerStamp::CPSTR_PickerStamp(
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
//   ~CPSTR_PickerStamp							Destructor				  [public]
// ---------------------------------------------------------------------------

CPSTR_PickerStamp::~CPSTR_PickerStamp()
{
}


// ---------------------------------------------------------------------------
//   StampSize														  [public]
// ---------------------------------------------------------------------------
// case 'STR ':
// case 'PStr':

void
CPSTR_PickerStamp::StampSize(ResType inType, SInt16 &outWidth, SInt16 &outHeight)
{
#pragma unused(inType)
	outWidth = 120;
	outHeight = 60;
}


// ---------------------------------------------------------------------------
//   DrawSelf														  [public]
// ---------------------------------------------------------------------------

void
CPSTR_PickerStamp::DrawSelf()
{
	if (mStaticField != NULL) {
		// The resID is the paneID of the PickerView
		ResIDT	theID = mParent->GetPaneID();
		ResType	theType = mParent->GetOwnerWindow()->GetType();
		short	theRefNum = mParent->GetUserCon();
		LStr255	theText("\p");
		Str255	theLine;
		StRezRefSaver saver(theRefNum);
		
		Handle theStrHandle = ::Get1Resource(theType, theID);
		::HandToHand(&theStrHandle);
		
		if (theStrHandle != NULL) {
			LHandleStream * theStream = new LHandleStream(theStrHandle);
			Boolean			truncated = false;
			
			if (theStream->GetLength() == 0) {
				theText += "\p\r\r    <empty string>";
			} else {
				try {
					*theStream >> theLine;
					if (theLine[0] > 90) {
						theLine[0] = 90;
						truncated = true;
					} 

					theText += theLine;
					if (truncated) {
						theText += "\p…";
					} 
				}
				catch (...) {
					theText += "\p\r\r   <invalid string>";
				}
			}
			
			mStaticField->SetDescriptor(theText);			
			delete theStream;
		} 
	} 
}



PP_End_Namespace_PowerPlant
