// ===========================================================================
// CStaticEditCombo.cp
// 
//                       Created: 2005-03-17 09:36:42
//             Last modification: 2005-03-17 09:36:42
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
// A static text which allows for editing when clicked upon. Useful, for
// instance, for the menu title in a menu editor: if the user clicks on the
// title, it is replaced by an edit field. When the Return or the Enter key
// is pressed, the string is validated and we switch back to the static
// text.


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CStaticEditCombo.h"
#include "RezillaConstants.h"

#include <LString.h>

// // Standard headers
// #include <string.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//	¥ CStaticEditCombo							Stream Constructor		  [public]
// ---------------------------------------------------------------------------

CStaticEditCombo::CStaticEditCombo(
	LStream*	inStream,
	ClassIDT	inImpID)

	: LEditText(inStream, inImpID)
{
	InitCombo();
}


// ---------------------------------------------------------------------------
//	¥ CStaticEditCombo							Parameterized Constructor [public]
// ---------------------------------------------------------------------------

CStaticEditCombo::CStaticEditCombo(
	const SPaneInfo&	inPaneInfo,
	LCommander*			inSuperCommander,
	ConstStringPtr		inInitialText,
	ResIDT				inTextTraitsID,
	MessageT			inMessage,
	SInt16				inMaxChars,
	UInt8				inAttributes,
	TEKeyFilterFunc		inKeyFilter,
	bool				inPasswordField,
	ClassIDT			inImpID)

	: LEditText(inPaneInfo, inSuperCommander, inInitialText, 
				inTextTraitsID, inMessage, inMaxChars, inAttributes, 
				inKeyFilter, inPasswordField, inImpID)
{
	InitCombo();
}


// ---------------------------------------------------------------------------
//	¥ ~CStaticEditCombo							Destructor				  [public]
// ---------------------------------------------------------------------------

CStaticEditCombo::~CStaticEditCombo()
{
}


// ---------------------------------------------------------------------------
//	¥ InitCombo
// ---------------------------------------------------------------------------

void 
CStaticEditCombo::InitCombo()
{
	SPaneInfo	pi;
	
	pi.paneID = 0;
	pi.width = mFrameSize.width;
	pi.height = mFrameSize.height;
	pi.visible = true;
	pi.enabled = true;
	pi.bindings = mFrameBinding;
	pi.left = mFrameLocation.h;
	pi.top = mFrameLocation.v;
	pi.userCon = 0;
	pi.superView = mSuperView;

	Str255		theTitle;
	this->GetDescriptor(theTitle);
	this->Hide();
	
	mStaticText = new LStaticText(pi, theTitle, 0);
	// 		PlaceInSuperImageAt(inPaneInfo.left, inPaneInfo.top, false);

	mStaticText->SetDescriptor(theTitle);
	mStaticText->Show();
	
	mIsEditing = false;
}


// // ---------------------------------------------------------------------------
// // FinishCreateSelf											[protected]
// // ---------------------------------------------------------------------------
// 
// void
// CStaticEditCombo::FinishCreateSelf()
// {
// }



#pragma mark -

// ---------------------------------------------------------------------------
//	¥  ClickSelf
// ---------------------------------------------------------------------------

void 
CStaticEditCombo::ClickSelf(const SMouseDownEvent &inMouseDown)
{
// #pragma unused(inMouseDown)
	
	if (mIsEditing) {
		LEditText::ClickSelf(inMouseDown);
	} else {
		Str255	theTitle;
		mStaticText->GetDescriptor(theTitle);
		mStaticText->Hide();
		this->SetDescriptor(theTitle);
		this->Show();
		mIsEditing = true;
	}
}


// ---------------------------------------------------------------------------
//	¥ HandleKeyPress												  [public]
// ---------------------------------------------------------------------------

Boolean
CStaticEditCombo::HandleKeyPress(
	const EventRecord&	inKeyEvent)
{
	Boolean		keyHandled = true;

	if (mIsEditing) {
		UInt16		theChar = (UInt16) (inKeyEvent.message & charCodeMask);

		if ( (theChar == char_Enter) || (theChar == char_Return) ) {
			Str255	theTitle;
			this->GetDescriptor(theTitle);
			this->Hide();
			mStaticText->SetDescriptor(theTitle);
			mStaticText->Show();
			mIsEditing = false;
		} else {
			keyHandled = LEditText::HandleKeyPress(inKeyEvent);
		}
		
	} 

	return keyHandled;
}




PP_End_Namespace_PowerPlant
