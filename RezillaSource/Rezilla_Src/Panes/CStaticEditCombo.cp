// ===========================================================================
// CStaticEditCombo.cp
// 
//                       Created: 2005-03-17 09:36:42
//             Last modification: 2005-03-20 17:48:28
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
// A view containing both a static text and an edit text field. Useful, for
// instance, for the menu title in a menu editor: if the user clicks on the
// static title, it is replaced by an edit field. When the Return or the
// Enter key is pressed, the string is validated and we switch back to the
// static text.


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CStaticEditCombo.h"
#include "RezillaConstants.h"

#include <LString.h>
#include <UKeyFilters.h>

// // Standard headers
// #include <string.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   CStaticEditCombo							Stream Constructor		  [public]
// ---------------------------------------------------------------------------

CStaticEditCombo::CStaticEditCombo(
	LStream*	inStream)

	: LView(inStream)
{
	InitCombo();
}


// ---------------------------------------------------------------------------
//   CStaticEditCombo							Parameterized Constructor [public]
// ---------------------------------------------------------------------------

CStaticEditCombo::CStaticEditCombo(	
								const SPaneInfo&	inPaneInfo,
								const SViewInfo&	inViewInfo)

	: LView(inPaneInfo, inViewInfo)
{
	InitCombo();
}


// ---------------------------------------------------------------------------
//   ~CStaticEditCombo							Destructor				  [public]
// ---------------------------------------------------------------------------

CStaticEditCombo::~CStaticEditCombo()
{
}


// ---------------------------------------------------------------------------
//   InitCombo
// ---------------------------------------------------------------------------
// 		PlaceInSuperImageAt(inPaneInfo.left, inPaneInfo.top, false);

void 
CStaticEditCombo::InitCombo()
{
	SPaneInfo	pi;
	
	pi.paneID = 0;
	pi.width = mFrameSize.width;
	pi.height = mFrameSize.height;
	pi.visible = false;
	pi.enabled = true;
	pi.bindings = mFrameBinding;
// 	pi.left = mFrameLocation.h;
// 	pi.top = mFrameLocation.v;
	pi.left = 0;
	pi.top = 0;
	pi.userCon = 0;
	pi.superView = this;

	mStaticText = new LStaticText(pi, "\p", 0);
	
	pi.top -= 2;
	mEditText = new LEditText(pi, this, "\p", Txtr_MonacoNineDefault, msg_Nothing, 255, 0, 
							  UKeyFilters::SelectTEKeyFilter(keyFilter_PrintingChar));
							  
}


// ---------------------------------------------------------------------------
//   FinishCreateSelf											[protected]
// ---------------------------------------------------------------------------

void
CStaticEditCombo::FinishCreateSelf()
{
	mIsEditing = false;
// 	Str255		theTitle;
// 	this->GetDescriptor(theTitle);
	mEditText->Hide();
	
// 	mStaticText->SetDescriptor(theTitle);
	mStaticText->Show();
}



#pragma mark -

// ---------------------------------------------------------------------------
//   Click
// ---------------------------------------------------------------------------

void 
CStaticEditCombo::Click(SMouseDownEvent &inMouseDown)
{	
	if (mIsEditing) {
		mEditText->Click(inMouseDown);
	} else {
		SwapPanes();
	}
}


// ---------------------------------------------------------------------------
//   HandleKeyPress												  [public]
// ---------------------------------------------------------------------------

Boolean
CStaticEditCombo::HandleKeyPress(
	const EventRecord&	inKeyEvent)
{
	Boolean		keyHandled = true;

	if (mIsEditing) {
		UInt16	theChar = (UInt16) (inKeyEvent.message & charCodeMask);

		if ( (theChar == char_Enter) || (theChar == char_Return) ) {
			SwapPanes();
		} else {
			keyHandled = mEditText->HandleKeyPress(inKeyEvent);
		}
	} 

	return keyHandled;
}


// ---------------------------------------------------------------------------
//   SwapPanes												  [public]
// ---------------------------------------------------------------------------
// 			GetSuperView()->GetSubPanes().SwapItems(1,2);

void
CStaticEditCombo::SwapPanes()
{
	Boolean		keyHandled = true;
	Str255	theTitle;

	if (mIsEditing) {
		mEditText->GetDescriptor(theTitle);
		mEditText->Hide();
		mStaticText->SetDescriptor(theTitle);
		mStaticText->Show();
		mIsEditing = false;
	} else {
		mStaticText->GetDescriptor(theTitle);
		mStaticText->Hide();
		mEditText->SetDescriptor(theTitle);
		mEditText->Show();
		SwitchTarget(mEditText);
		mIsEditing = true;
	}
}


// ---------------------------------------------------------------------------
//	¥ GetDescriptor													  [public]
// ---------------------------------------------------------------------------

StringPtr
CStaticEditCombo::GetDescriptor(
	Str255	outDescriptor) const
{
	if (mIsEditing) {
		mEditText->GetDescriptor(outDescriptor);
	} else {
		mStaticText->GetDescriptor(outDescriptor);
	}
	return outDescriptor;
}


// ---------------------------------------------------------------------------
//	¥ SetDescriptor													  [public]
// ---------------------------------------------------------------------------

void
CStaticEditCombo::SetDescriptor(
	ConstStringPtr	inDescriptor)
{
	if (mIsEditing) {
		mEditText->SetDescriptor(inDescriptor);
	} else {
		mStaticText->SetDescriptor(inDescriptor);
	}
}



PP_End_Namespace_PowerPlant
