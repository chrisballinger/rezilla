// ===========================================================================
// File: "CThreeButtonsBox.cp"
//                        Created: 2005-03-09 05:43:35
//              Last modification: 2005-03-09 06:03:14
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2005
// All rights reserved.
// ===========================================================================
//	This is the same as PowerPlant's LDialogBox but with therre buttons
//	(Cancel, Don't, OK) instead of two to implement AskYesNo dialogs.

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CThreeButtonsBox.h"

#include <LControl.h>
#include <LStream.h>

#include <PP_KeyCodes.h>
#include <PP_Messages.h>
#include <UEnvironment.h>
#include <UKeyFilters.h>

#include <ControlDefinitions.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//	¥ CThreeButtonsBox							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CThreeButtonsBox::CThreeButtonsBox()
{
	mDefaultButtonID = PaneIDT_Undefined;
	mCancelButtonID  = PaneIDT_Undefined;
	mDontButtonID    = PaneIDT_Undefined;
}


// ---------------------------------------------------------------------------
//	¥ CThreeButtonsBox							Constructor				  [public[
// ---------------------------------------------------------------------------
//	Construct ThreeButtonsBox from the data in a struct

CThreeButtonsBox::CThreeButtonsBox(
	const SWindowInfo&	inWindowInfo)

	: LWindow(inWindowInfo)
{
	mDefaultButtonID = PaneIDT_Undefined;
	mCancelButtonID  = PaneIDT_Undefined;
	mDontButtonID    = PaneIDT_Undefined;
}


// ---------------------------------------------------------------------------
//	¥ CThreeButtonsBox							Constructor				  [pulbic]
// ---------------------------------------------------------------------------
//	Construct a ThreeButtonsBox from a WIND Resource with the specified attributes
//	and SuperCommander
//
//	Side Effect: Created window becomes the current port

CThreeButtonsBox::CThreeButtonsBox(
	ResIDT			inWINDid,
	UInt32			inAttributes,
	LCommander*		inSuper)

	: LWindow(inWINDid, inAttributes, inSuper)
{
	mDefaultButtonID = PaneIDT_Undefined;
	mCancelButtonID  = PaneIDT_Undefined;
	mDontButtonID    = PaneIDT_Undefined;
}


// ---------------------------------------------------------------------------
//	¥ CThreeButtonsBox							Constructor				  [public]
// ---------------------------------------------------------------------------

CThreeButtonsBox::CThreeButtonsBox(
	LCommander*		inSuperCommander,
	const Rect&		inGlobalBounds,
	ConstStringPtr	inTitle,
	SInt16			inProcID,
	UInt32			inAttributes,
	WindowPtr		inBehind,
	PaneIDT			inDefaultButtonID,
	PaneIDT			inCancelButtonID,
	PaneIDT			inDontButtonID)

	: LWindow(inSuperCommander, inGlobalBounds, inTitle, inProcID,
					inAttributes, inBehind)
{
	mDefaultButtonID = inDefaultButtonID;
	mCancelButtonID	 = inCancelButtonID;
	mDontButtonID    = inDontButtonID;
}


// ---------------------------------------------------------------------------
//	¥ CThreeButtonsBox							Stream Constructor		  [public]
// ---------------------------------------------------------------------------

CThreeButtonsBox::CThreeButtonsBox(
	LStream*	inStream)

	: LWindow(inStream)
{
	*inStream >> mDefaultButtonID;
	*inStream >> mCancelButtonID;
	*inStream >> mDontButtonID;
}


// ---------------------------------------------------------------------------
//	¥ ~CThreeButtonsBox							Destructor				  [public]
// ---------------------------------------------------------------------------

CThreeButtonsBox::~CThreeButtonsBox()
{
}


// ---------------------------------------------------------------------------
//	¥ FinishCreateSelf											   [protected]
// ---------------------------------------------------------------------------

void
CThreeButtonsBox::FinishCreateSelf()
{
	LWindow::FinishCreateSelf();
	
	SetDefaultTag(mDefaultButtonID, true);
	SetCancelTag(mCancelButtonID, true);
}


#pragma mark -

// ---------------------------------------------------------------------------
//	¥ SetDefaultButton												  [public]
// ---------------------------------------------------------------------------
//	Specify the PaneID of the default button of a ThreeButtonsBox. The default
//	button must be an LControl that handles the data tag
//	kControlPushButtonDefaultTag.
//
//	Use PaneIDT_Undefined to specify no default button
//
//	Keyboard equivalents (Return and Enter) simulate a click inside the
//	default button.

void
CThreeButtonsBox::SetDefaultButton(
	PaneIDT	inButtonID)
{
	if (inButtonID != mDefaultButtonID) {
	
			// There can only be one default button. Turn off default
			// state for existing default button, then turn it on
			// for the new default button.
	
		SetDefaultTag(mDefaultButtonID, false);
		SetDefaultTag(inButtonID, true);
		
		mDefaultButtonID = inButtonID;
	}
}


// ---------------------------------------------------------------------------
//	¥ SetCancelButton												  [public]
// ---------------------------------------------------------------------------
//	Specify the PaneID of the cancel button of a ThreeButtonsBox. The cancel
//	button must be derived from LControl.
//
//	Use PaneIDT_Undefined to specify no cancel button
//
//	Keyboard equivalents (Escape and Command-Period) simulate a click inside
//	the cancel button.

void
CThreeButtonsBox::SetCancelButton(
	PaneIDT	inButtonID)
{
	if (inButtonID != mCancelButtonID) {
	
			// There can only be one cancel button. Turn off cancel
			// state for existing cancel button, then turn it on
			// for the new cancel button.
	
		SetCancelTag(mCancelButtonID, false);
		SetCancelTag(inButtonID, true);
		
		mCancelButtonID = inButtonID;
	}
}


// ---------------------------------------------------------------------------
//	¥ SetDontButton												  [public]
// ---------------------------------------------------------------------------
//	Specify the PaneID of the Don't/No button of a ThreeButtonsBox. The
//	Don't/No button must be derived from LControl.
//
//	Use PaneIDT_Undefined to specify no Don't/No button
//
//	Keyboard equivalents (cmd-D or cmd-N) simulate a click inside
//	the Don't/No button.

void
CThreeButtonsBox::SetDontButton(
	PaneIDT	inButtonID)
{
	if (inButtonID != mDontButtonID) {
		mDontButtonID = inButtonID;
	}
}


// ---------------------------------------------------------------------------
//	¥ SetDefaultTag												   [protected]
// ---------------------------------------------------------------------------
//	Set whether or not a Button is the default one
//
//	PaneID must be for a LControl object that handles the
//	kControlPushButtonDefaultTag data tag.
//
//	Used internally. Clients should call SetDefaultButton().

void
CThreeButtonsBox::SetDefaultTag(
	PaneIDT		inButtonID,
	Boolean		inBeDefault)
{
	if (inButtonID != PaneIDT_Undefined) {
	
		LControl*	theButton = dynamic_cast<LControl*>
											(FindPaneByID(inButtonID));
		if (theButton != nil) {
			theButton->SetDataTag(0, kControlPushButtonDefaultTag,
										sizeof(Boolean), (Ptr) &inBeDefault);
										
			if (inBeDefault) {
				theButton->AddListener(this);
			}
		}
		
		SignalIf_( theButton == nil );
	}
}


// ---------------------------------------------------------------------------
//	¥ SetCancelTag												   [protected]
// ---------------------------------------------------------------------------
//	Set whether or not a Button is the cancel one
//
//	PaneID must be for a LControl object that handles the
//	kControlPushButtonDefaultTag data tag
//
//	Used internally. Clients should call SetCancelButton().

void
CThreeButtonsBox::SetCancelTag(
	PaneIDT		inButtonID,
	Boolean		inBeCancel)
{
	if (inButtonID != PaneIDT_Undefined) {
	
		LControl*	theButton = dynamic_cast<LControl*>
											(FindPaneByID(inButtonID));
		if (theButton != nil) {
		
				// The kControlPushButtonCancelTag is supported
				// in Appearance 1.1 or later
		
			if (UEnvironment::HasFeature(env_HasAppearance11)) {
				theButton->SetDataTag(0, kControlPushButtonCancelTag,
										sizeof(Boolean), (Ptr) &inBeCancel);
			}
										
			if (inBeCancel) {
				theButton->AddListener(this);
			}
		}
		
		SignalIf_( theButton == nil );
	}
}


// ---------------------------------------------------------------------------
//	¥ SetDontTag
// ---------------------------------------------------------------------------
// There is no tag for a Don't/No button (ie no sound associated) so there
// is no SetDontTag() function.



#pragma mark -

// ---------------------------------------------------------------------------
//	¥ HandleKeyPress												  [public]
// ---------------------------------------------------------------------------
//	ThreeButtonsBox handles keyboard equivalents for hitting the Default and
//	Cancel Buttons.
//
//		Default Button: Enter, Return
//		Cancel Button:  Escape, Command-Period
//		Dont Button:    cmd-D, cmd-N

Boolean
CThreeButtonsBox::HandleKeyPress(
	const EventRecord&	inKeyEvent)
{
	Boolean		keyHandled	= true;
	LControl*	keyButton	= nil;
	UInt8		theChar		= (UInt8) (inKeyEvent.message & charCodeMask);

	if ( (theChar == char_Enter) || (theChar == char_Return) ) {
	
		if (mDefaultButtonID != PaneIDT_Undefined) {
			keyButton = dynamic_cast<LControl*>(FindPaneByID(mDefaultButtonID));
		}

	} else if ( UKeyFilters::IsEscapeKey(inKeyEvent) ||
				UKeyFilters::IsCmdPeriod(inKeyEvent) ) {
				
		if (mCancelButtonID != PaneIDT_Undefined) {
			keyButton = dynamic_cast<LControl*>(FindPaneByID(mCancelButtonID));
		}
		
	} else if ( ((theChar == 'd') || (theChar == 'n')) && (inKeyEvent.modifiers & cmdKey)) {
		
		if (mDontButtonID != PaneIDT_Undefined) {
			keyButton = dynamic_cast<LControl*>(FindPaneByID(mDontButtonID));
		}

	}	

	if (keyButton != nil) {
		keyButton->SimulateHotSpotClick(kControlButtonPart);
	} else {
		keyHandled = LWindow::HandleKeyPress(inKeyEvent);
	}

	return keyHandled;
}


// ---------------------------------------------------------------------------
//	¥ ListenToMessage												  [public]
// ---------------------------------------------------------------------------
//	Respond to messages from Broadcasters
//
//	ThreeButtonsBox responds to the cmd_Close message by deleting itself.
//
//	Also, negative message numbers are relayed to ProcessCommand().
//	This allows subclasses of ThreeButtonsBox to handle messages as commands.
//	Or, if you don't want to subclass ThreeButtonsBox, the SuperCommander
//	of the ThreeButtonsBox will receive the messages as commands.

void
CThreeButtonsBox::ListenToMessage(
	MessageT	inMessage,
	void*		ioParam)
{
	if (inMessage == cmd_Close) {
		DoClose();

	} else if (inMessage < 0) {
									// Relay message to supercommander
		if (GetSuperCommander() != nil) {
			SThreeButtonsResponse	theResponse;
			theResponse.dialogBox = this;
			theResponse.messageParam = ioParam;
			ProcessCommand(inMessage, &theResponse);
		}
	}
}


PP_End_Namespace_PowerPlant
