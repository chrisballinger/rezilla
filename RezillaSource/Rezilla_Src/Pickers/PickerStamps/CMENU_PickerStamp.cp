// ===========================================================================
// 	CMENU_PickerStamp.cp
// 
//                       Created : 2006-02-25 17:40:43
//             Last modification : 2006-09-30 06:48:06
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@users.sourceforge.net>
// www : <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2006
// All rights reserved.
// ===========================================================================


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CMENU_PickerStamp.h"
#include "CPickerView.h"
#include "CRezillaApp.h"
#include "CMenuObject.h"
#include "UResources.h"
#include "RezillaConstants.h"

#include <UDrawingState.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   CMENU_PickerStamp							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CMENU_PickerStamp::CMENU_PickerStamp(
									CPickerView *		inParent,
									const SPaneInfo&	inPaneInfo,
									const SViewInfo&	inViewInfo)
	: CPickerStamp(inParent, inPaneInfo, inViewInfo)
{
}


// ---------------------------------------------------------------------------
//   ~CMENU_PickerStamp							Destructor				  [public]
// ---------------------------------------------------------------------------

CMENU_PickerStamp::~CMENU_PickerStamp()
{
}


// ---------------------------------------------------------------------------
//   StampSize														  [public]
// ---------------------------------------------------------------------------

void
CMENU_PickerStamp::StampSize(ResType inType, SInt16 &outWidth, SInt16 &outHeight)
{
#pragma unused(inType)
	outWidth = 160;
	outHeight = 24;
}


// ---------------------------------------------------------------------------
//   DrawSelf														  [public]
// ---------------------------------------------------------------------------

void
CMENU_PickerStamp::DrawSelf()
{
	// The resID is the paneID of the PickerView
	ResIDT		theID = mParent->GetPaneID();
	short		theRefNum = mParent->GetUserCon();
	Str255		theTitle;
	Handle		theResHandle = NULL, thePictureH = NULL;
	Boolean		isAppleMenu = false;
	Rect		frame;

	StTextState	textSaver;
	StRezRefSaver refSaver(theRefNum);
	theResHandle = ::Get1Resource('MENU', theID);
	::HandToHand(&theResHandle);

	theTitle[0] = 0;

	if ( ! CMenuObject::GetMenuTitle(theID, theRefNum, theTitle) ) {
		::NumToString( (long)theID, theTitle);
	} 
	
	// Is it the Apple menu?
	if (theTitle[1] == 0x14) {
		isAppleMenu = true;
		theTitle[0] = 0;
	} 
	
	// Now use Rezilla's refnum
	::UseResFile(CRezillaApp::sSelfRefNum);
	if (isAppleMenu) {
		thePictureH = (Handle) ::GetPicture(PICT_MenuPickerApple);
	} else {
		thePictureH = (Handle) ::GetPicture(PICT_MenuPickerBar);
	}
	::HandToHand(&thePictureH);

	FocusDraw();
	CalcLocalFrameRect(frame);
	
	// Draw the picture
	if (thePictureH) {
		::DrawPicture( (PicHandle)thePictureH, &frame);
		::DisposeHandle(thePictureH);
	} 
	
	// Draw the string
	::MoveTo(frame.left + 20, frame.top + kPickerViewVertMargin + 12);
	::TextFont(systemFont);
	::TextSize(0);
	::TextFace(bold);
	::TextMode(srcOr);
	::DrawString(theTitle);	
	
}



PP_End_Namespace_PowerPlant
