// ===========================================================================
// UDialogBoxHandler.cp				
// 
//                       Created: 2002-05-09 18:35:37
//             Last modification: 2004-11-23 11:05:09
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2003-2004
// All rights reserved.
// ===========================================================================
// StDialogBoxHandler is derived from StDialogHandler
//	Manages events while a dialog box is active
//
//	Typical use is for creating a "one shot" moveable modal dialog box
//	where you want the dialog box to handle all user interaction until
//	the dialog box closes.


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CRezillaApp.h"
#include "UDialogBoxHandler.h"
#include "UResources.h"
#include "CThreeButtonsBox.h"

#include <LControl.h>
#include <LEditField.h>
#include <LPeriodical.h>
#include <LUndoer.h>
#include <PP_KeyCodes.h>
#include <PP_Messages.h>
#include <PP_Resources.h>
#include <UDesktop.h>
#include <UDrawingState.h>
#include <UEventMgr.h>
#include <UReanimator.h>

#include <ControlDefinitions.h>


PP_Begin_Namespace_PowerPlant

// ---------------------------------------------------------------------------
//	¥ StDialogBoxHandler						Constructor				  [public]
// ---------------------------------------------------------------------------
//	Create new Dialog window from a PPob

StDialogBoxHandler::StDialogBoxHandler(
	ResIDT			inDialogResID,		// 'PPob' and 'RidL' Resource ID
	LCommander*		inSuper)

	: LCommander(inSuper)
{
	mDialog = dynamic_cast<CThreeButtonsBox*>(LWindow::CreateWindow(inDialogResID, this));

	UReanimator::LinkListenerToBroadcasters(this, mDialog, inDialogResID);

	InitDialogHandler();
}


// ---------------------------------------------------------------------------
//	¥ StDialogBoxHandler						Constructor				  [public]
// ---------------------------------------------------------------------------
//	Take ownership of a CThreeButtonsBox to use as a moveable modal dialog box
//
//	If you wish to set up a Broadcaster/Listener relationship between
//	the Controls in the Window (such as the OK and Cancel buttons) and the
//	DialogHandler, you must do so explicitly.

StDialogBoxHandler::StDialogBoxHandler(
	CThreeButtonsBox*		inWindow,			// Window to use for dialog
	LCommander*				inSuper)

	: LCommander(inSuper)
{
	mDialog = inWindow;
	inWindow->SetSuperCommander(this);

	InitDialogHandler();
}


// ---------------------------------------------------------------------------
//	¥ InitDialogHandler						Initializer			   [protected]
// ---------------------------------------------------------------------------

void
StDialogBoxHandler::InitDialogHandler()
{
		// Create and add an Undoer. It's OK if this fails. We
		// just go on without undo support.

	LUndoer*	theUndoer = nil;

	try {
		theUndoer = new LUndoer;
		mDialog->AddAttachment(theUndoer);
	}

	catch (...) {
		delete theUndoer;
	}

	mMessage   = msg_Nothing;
	mSleepTime = 6;
}


// ---------------------------------------------------------------------------
//	¥ ~StDialogBoxHandler						Destructor				 [private]
// ---------------------------------------------------------------------------

StDialogBoxHandler::~StDialogBoxHandler()
{
	delete mDialog;
}


// ---------------------------------------------------------------------------
//	¥ DoDialog														  [public]
// ---------------------------------------------------------------------------
//	Handle an Event for a dialog box
//
//	Call this function repeatedly to handle events. If the event triggers
//	a Broadcaster to broadcast a message, the last such message heard by
//	the DialogHandler is returned. Otherwise, this function returns
//	msg_Nothing.

MessageT
StDialogBoxHandler::DoDialog()
{
	EventRecord macEvent;

	StRezRefSaver saver(CRezillaApp::sOwnRefNum);

	if (IsOnDuty()) {
		UEventMgr::GetMouseAndModifiers(macEvent);
		AdjustCursor(macEvent);
	}

	SetUpdateCommandStatus(false);
	mMessage = msg_Nothing;

	Boolean gotEvent = ::WaitNextEvent(everyEvent, &macEvent,
										mSleepTime, mMouseRgn);

	// Let Attachments process the event. Continue with normal
	// event dispatching unless suppressed by an Attachment.

	if (LEventDispatcher::ExecuteAttachments(msg_Event, &macEvent)) {
		if (gotEvent) {
			DispatchEvent(macEvent);
		} else {
			UseIdleTime(macEvent);
		}
	}

	// Repeaters get time after every event
	LPeriodical::DevoteTimeToRepeaters(macEvent);

	// Update status of menu items
	if (IsOnDuty() && GetUpdateCommandStatus()) {
		UpdateMenus();
	}

	return mMessage;
}


// ---------------------------------------------------------------------------
//	¥ AllowSubRemoval												  [public]
// ---------------------------------------------------------------------------

Boolean
StDialogBoxHandler::AllowSubRemoval(
	LCommander*		inSub)
{
	Boolean allow = true;

	if (inSub == (dynamic_cast<LCommander*>(mDialog))) {
									// Dialog is trying to close itself
		mDialog->Hide();			// Just hide it now
		allow = false;				// And don't let it delete itself
		mMessage = msg_Cancel;		// Our destructor will delete it
	}

	return(allow);
}


// ---------------------------------------------------------------------------
//	¥ FindCommandStatus												  [public]
// ---------------------------------------------------------------------------
//	Pass back the status of a Command

void
StDialogBoxHandler::FindCommandStatus(
	CommandT		inCommand,
	Boolean&		outEnabled,
	Boolean&		/* outUsesMark */,
	UInt16&			/* outMark */,
	Str255			/* outName */)
{
		// Don't enable any commands except the synthetic one for the
		// Apple Menu as a whole. This function purposely does not
		// call the inherited FindCommandStatus, thereby suppressing
		// commands that are handled by SuperCommanders. Only those
		// commands enabled by SubCommanders will be active.
		//
		// This is usually what you want for a moveable modal dialog.
		// Commands such as "New", "Open" and "Quit" that are handled
		// by the Applcation are disabled, but items within the dialog
		// can enable commands. For example, an EditField would enable
		// items in the "Edit" menu.

	outEnabled = (inCommand == SyntheticCommandForMenu_(MENU_Apple));
}


// ---------------------------------------------------------------------------
//	¥ ListenToMessage												  [public]
// ---------------------------------------------------------------------------
// Store message. DoDialog() will return this value.

void
StDialogBoxHandler::ListenToMessage(
	MessageT	inMessage,
	void*		/* ioParam */)
{
	mMessage = inMessage;		
}


PP_End_Namespace_PowerPlant
