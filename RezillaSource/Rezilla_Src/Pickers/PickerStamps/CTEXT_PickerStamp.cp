// ===========================================================================
// 	CTEXT_PickerStamp.cp
// 
//                       Created : 2006-02-25 17:40:43
//             Last modification : 2006-09-27 09:15:56
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@users.sourceforge.net>
// www : <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2006
// All rights reserved.
// ===========================================================================


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CTEXT_PickerStamp.h"
#include "CPickerView.h"
#include "UResources.h"
#include "RezillaConstants.h"
#include "CStaticClickThrough.h"

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   CTEXT_PickerStamp							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CTEXT_PickerStamp::CTEXT_PickerStamp(
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
//   ~CTEXT_PickerStamp							Destructor				  [public]
// ---------------------------------------------------------------------------

CTEXT_PickerStamp::~CTEXT_PickerStamp()
{
}


// ---------------------------------------------------------------------------
//   StampSize														  [public]
// ---------------------------------------------------------------------------

void
CTEXT_PickerStamp::StampSize(ResType inType, SInt16 &outWidth, SInt16 &outHeight)
{
#pragma unused(inType)
	outWidth = 120;
	outHeight = 120;
}


// ---------------------------------------------------------------------------
//   DrawSelf														  [public]
// ---------------------------------------------------------------------------

void
CTEXT_PickerStamp::DrawSelf()
{
	if (mStaticField != NULL) {
		// The resID is the paneID of the PickerView
		ResIDT	theID = mParent->GetPaneID();
		short	theRefNum = mParent->GetUserCon();
		Str255	theString = "\p";
		Size	theSize;
		Handle	theTextHandle = NULL;
		StRezRefSaver saver(theRefNum);
		
		theTextHandle = ::Get1Resource('TEXT', theID);
		::HandToHand(&theTextHandle);
		
		if (theTextHandle != NULL) {
			theSize = ::GetHandleSize(theTextHandle);
			if (theSize > 255) {
				theSize = 255;
			} 
			BlockMoveData(*theTextHandle, theString+1, theSize);
			theString[0] = theSize;
			mStaticField->SetDescriptor(theString);
			::DisposeHandle(theTextHandle);
		} 
	} 
}


PP_End_Namespace_PowerPlant
