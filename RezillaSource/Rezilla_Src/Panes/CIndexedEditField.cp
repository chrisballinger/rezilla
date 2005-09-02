// ===========================================================================
// CIndexedEditField.cp
// 
//                       Created: 2005-09-01 09:14:05
//             Last modification: 2005-09-01 09:14:09
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CIndexedEditField.h"
#include "RezillaConstants.h"

#include <LString.h>
#include <UKeyFilters.h>

// // Standard headers
// #include <string.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   CIndexedEditField							Stream Constructor		  [public]
// ---------------------------------------------------------------------------

CIndexedEditField::CIndexedEditField(
	LStream*	inStream)

	: LView(inStream)
{
	Str255 theString;
	
	*inStream >> mIndex;
	*inStream >> theString;
	
	Initialize(theString);
}


// ---------------------------------------------------------------------------
//   CIndexedEditField							Parameterized Constructor [public]
// ---------------------------------------------------------------------------

CIndexedEditField::CIndexedEditField(	
								const SPaneInfo& inPaneInfo,
								const SViewInfo& inViewInfo,
								UInt16 index,
								Str255 inString)

	: LView(inPaneInfo, inViewInfo)
{
	mIndex = index;
	Initialize(inString);
}


// ---------------------------------------------------------------------------
//   ~CIndexedEditField							Destructor				  [public]
// ---------------------------------------------------------------------------

CIndexedEditField::~CIndexedEditField()
{
}


// ---------------------------------------------------------------------------
//   Initialize
// ---------------------------------------------------------------------------
// 		PlaceInSuperImageAt(inPaneInfo.left, inPaneInfo.top, false);

void 
CIndexedEditField::Initialize(Str255 inString)
{
	SPaneInfo	pi;
	Str255		theString;
	Rect		frame;
	
	mSelected = false;
	CalcLocalFrameRect(frame);

	// Static field basic values
	pi.width			= kStrxIndexWidth;
	pi.height			= kStrxHeight;
	pi.visible			= true;
	pi.enabled			= true;
	pi.bindings.left	= false;
	pi.bindings.top		= false;
	pi.bindings.right	= false;
	pi.bindings.bottom 	= false;
	pi.userCon			= 0;
	pi.left				= kStrxSepWidth;
	pi.top				= 2;
	pi.paneID			= 0;
	pi.superView		= this;

	::NumToString(mIndex + 1, theString);
	mStaticText = new LStaticText(pi, theString, 0);
	
	// Edit field basic values
	pi.top				-= 2;
	pi.left				+= kStrxIndexWidth + kStrxSepWidth;
	pi.width			= frame.right - pi.left;
	pi.bindings.right	= true;
	
	mEditText = new LEditText(pi, this, inString, Txtr_MonacoNineDefault, msg_Nothing, 255, 0, 
							  UKeyFilters::SelectTEKeyFilter(keyFilter_PrintingChar));						  
	mEditText->SetDescriptor(inString);  
							  
}


// ---------------------------------------------------------------------------
//   FinishCreateSelf											[protected]
// ---------------------------------------------------------------------------

void
CIndexedEditField::FinishCreateSelf()
{
}



#pragma mark -

// ---------------------------------------------------------------------------
//   Click
// ---------------------------------------------------------------------------

void 
CIndexedEditField::Click(SMouseDownEvent &inMouseDown)
{	
	if (mSelected) {
		mEditText->Click(inMouseDown);
	} else {
		SwapPanes();
	}
}


// ---------------------------------------------------------------------------
//   HandleKeyPress												  [public]
// ---------------------------------------------------------------------------

Boolean
CIndexedEditField::HandleKeyPress(
	const EventRecord&	inKeyEvent)
{
	Boolean		keyHandled = true;

	if (mSelected) {
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

void
CIndexedEditField::SwapPanes()
{
	Boolean		keyHandled = true;
	Str255		theTitle;

	if (mSelected) {
		mEditText->GetDescriptor(theTitle);
		mEditText->Hide();
		if ( ! ::EqualString(theTitle, mCurrentTitle, true, false) ) {
			BroadcastMessage(msg_MenuTitleModified);
		} 
		mSelected = false;
		SetDescriptor(theTitle);
		mStaticText->Show();
	} else {
		mStaticText->GetDescriptor(theTitle);
		mStaticText->Hide();
		mSelected = true;
		SetDescriptor(theTitle);
		mEditText->Show();
		SwitchTarget(mEditText);
	}
}


// ---------------------------------------------------------------------------
//	¥ GetDescriptor													  [public]
// ---------------------------------------------------------------------------

StringPtr
CIndexedEditField::GetDescriptor(
	Str255	outDescriptor) const
{
	if (mSelected) {
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
CIndexedEditField::SetDescriptor(
	ConstStringPtr	inDescriptor)
{
	if (mSelected) {
		mEditText->SetDescriptor(inDescriptor);
	} else {
		mStaticText->SetDescriptor(inDescriptor);
	}
	LString::CopyPStr(inDescriptor, mCurrentTitle);
}



PP_End_Namespace_PowerPlant
