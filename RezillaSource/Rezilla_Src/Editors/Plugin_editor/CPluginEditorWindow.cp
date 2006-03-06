// ===========================================================================
// CPluginEditorWindow.cp
// 
//                       Created: 2005-10-02 08:41:52
//             Last modification: 2006-03-06 22:20:38
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2005-2006
// All rights reserved.
// ===========================================================================

#include "CPluginEditorWindow.h"
#include "CPluginEditorDoc.h"
#include "CRezillaPlugin.h"
#include "CRezObj.h"
#include "CWindowMenu.h"
#include "RezillaConstants.h"
#include "UMessageDialogs.h"

#include <LIconPane.h>
#include <LStaticText.h>
#include <LPushButton.h>
#include <LWindowHeader.h>
#include <LPlacard.h>
#include <LScrollerView.h>

extern CWindowMenu * gWindowMenu;

// ---------------------------------------------------------------------------
//  CPluginEditorWindow				[public]
// ---------------------------------------------------------------------------

CPluginEditorWindow::CPluginEditorWindow()
	: CEditorWindow()
{
	SetModelKind(rzom_cPluginWindow);
}


// ---------------------------------------------------------------------------
//  CPluginEditorWindow				[public]
// ---------------------------------------------------------------------------

CPluginEditorWindow::CPluginEditorWindow(
					WindowPtr		inMacWindow,
					LCommander*		inSuperCommander)
		: CEditorWindow(inMacWindow, inSuperCommander)
{
	SetModelKind(rzom_cPluginWindow);
}


// ---------------------------------------------------------------------------
//  CPluginEditorWindow				[public]
// ---------------------------------------------------------------------------

CPluginEditorWindow::CPluginEditorWindow(
				   LStream *inStream )
		: CEditorWindow( inStream )
{
	SetModelKind(rzom_cPluginWindow);
}


// ---------------------------------------------------------------------------
//  ~CPluginEditorWindow				[public]
// ---------------------------------------------------------------------------

CPluginEditorWindow::~CPluginEditorWindow()
{
	RemovePluginMenus();
	
	(*mInterface)->CleanUp(mPlugRef);
}


// ---------------------------------------------------------------------------
//  FinalizeEditor											[public]
// ---------------------------------------------------------------------------


void
CPluginEditorWindow::FinalizeEditor(CPluginEditorDoc* inEditorDoc, void * ioParam)
{
	// Set mOwnerDoc
	SetOwnerDoc(inEditorDoc);
	SetSuperModel(inEditorDoc);
	
	mInterface = dynamic_cast<CPluginEditorDoc *>(mOwnerDoc)->GetPlugin()->GetInterface();
	ThrowIfNil_(mInterface);
			
// 	CFStringRef		theStringRef;
// 	Str255			strPtr;
// 	strPtr = *(theDoc->GetRezObj()->GetName());
// 	theStringRef = CFStringCreateWithPascalString(NULL, strPtr, kCFStringEncodingMacRoman);
// 	CFRelease(theStringRef);		

	// Add the window to the window menu.
	gWindowMenu->InsertWindow(this);
}
	

// ---------------------------------------------------------------------------
//  CreateControls													[public]
// ---------------------------------------------------------------------------

void
CPluginEditorWindow::CreateControls(SInt32 inPlugAttrs)
{
	SDimension16		frameSize;
	WindowRef			winRef = GetMacWindow();
	Rect				boundsRect;
	ControlRef			ctrlRef, headRef, footRef;
	ControlID			ctrlID;
	OSStatus			error;
	HIViewRef			contentView = NULL;

	ctrlID.signature = kRezillaSig;
	
	mHasHeader = false;
	mHasFooter = false;

	GetFrameSize(frameSize);
	HIViewFindByID(HIViewGetRoot(winRef), kHIViewWindowContentID, &contentView);
	ThrowIfNil_(contentView);

	if ( inPlugAttrs != kPluginWinHasNoAttributes && (inPlugAttrs & kPluginWinHasNameField) != 0 ) {		
		// Create a header
		boundsRect.top		= 0;
		boundsRect.bottom	= kPluginHeaderHeight;
		boundsRect.left		= 0;
		boundsRect.right	= frameSize.width;

		error = CreateWindowHeaderControl(winRef, &boundsRect, false, &headRef);
		ThrowIfOSErr_(error);
		
		mHasHeader = true;
		
		HIViewAddSubview(contentView, headRef);
		HIViewSetVisible(headRef, true);
		
		// Create the name field
		boundsRect.top		= kEditVertMargin;
		boundsRect.bottom	= boundsRect.top + kEditNameHeight;
		boundsRect.left		= kEditHorizMargin;
		boundsRect.right	= frameSize.width - kEditHorizMargin;
	
		error = CreateStaticTextControl(NULL, &boundsRect, NULL, NULL, &ctrlRef);
		ThrowIfOSErr_(error);
		
		ctrlID.id = item_NameStaticText;
		SetControlID(ctrlRef, &ctrlID);
		HIViewAddSubview(headRef, ctrlRef);
		HIViewSetVisible(ctrlRef, true);			  
	}	
	
	if ( inPlugAttrs != kPluginWinHasNoAttributes && (inPlugAttrs & kPluginWinStandardAttributes) != 0 ) {
		// Create a footer
		boundsRect.top		= frameSize.height - kPluginFooterHeight;
		boundsRect.bottom	= frameSize.height;
		boundsRect.left		= 0;
		boundsRect.right	= frameSize.width;
		
		error = CreatePlacardControl(winRef, &boundsRect, &footRef);
		ThrowIfOSErr_(error);
		
		mHasFooter = true;
		
		HIViewAddSubview(contentView, footRef);
		HIViewSetVisible(footRef, true);

		boundsRect.top			= kEditButtonTop;
		boundsRect.bottom		= boundsRect.bottom + kEditButtonHeight ;
		if ( (inPlugAttrs & kPluginWinHasSaveButton) != 0) {
			// Create a Save button
			boundsRect.left		= frameSize.width - kEditValidButtonRight;
			boundsRect.right	= boundsRect.left + kEditButtonWidth;

			error = CreatePushButtonControl(NULL, &boundsRect, CFSTR("Save"), &ctrlRef);
			ThrowIfOSErr_(error);
			
			ctrlID.id = kHICommandOK;
			SetControlID(ctrlRef, &ctrlID);
			HIViewAddSubview(footRef, ctrlRef);
			HIViewSetVisible(ctrlRef, true);
		}
		if ( (inPlugAttrs & kPluginWinHasCancelButton) != 0) {
			// Create a Cancel button
			boundsRect.left		= frameSize.width - kEditCancelButtonRight;
			boundsRect.right	= boundsRect.left + kEditButtonWidth;

			error = CreatePushButtonControl(NULL, &boundsRect, CFSTR("Cancel"), &ctrlRef);
			ThrowIfOSErr_(error);
		
			ctrlID.id = kHICommandCancel;
			SetControlID(ctrlRef, &ctrlID);
			HIViewAddSubview(footRef, ctrlRef);
			HIViewSetVisible(ctrlRef, true);
		}
		if ( (inPlugAttrs & kPluginWinHasRevertButton) != 0) {
			// Create a Revert button
			boundsRect.left		= kEditRevertButtonLeft;
			boundsRect.right	= boundsRect.left + kEditButtonWidth;

			error = CreatePushButtonControl(NULL, &boundsRect, CFSTR("Revert"), &ctrlRef);
			ThrowIfOSErr_(error);
		
			ctrlID.id = kHICommandRevert;
			SetControlID(ctrlRef, &ctrlID);
			HIViewAddSubview(footRef, ctrlRef);
			HIViewSetVisible(ctrlRef, true);
		}
		if ( (inPlugAttrs & kPluginWinHasLockIcon) != 0) {
			// Create a Locked/Unlocked icon
// 			OSStatus 
// 			CreateIconControl(
// 			  WindowRef                         inWindow,            /* can be NULL */
// 			  const Rect *                      inBoundsRect,
// 			  const ControlButtonContentInfo *  inIconContent,
// 			  Boolean                           inDontTrack,
// 			  ControlRef *                      outControl)
		
		
		} 
	}
		
	// Add the window to the window menu.
	gWindowMenu->InsertWindow(this);
}
	

// ---------------------------------------------------------------------------
//  ListenToMessage									[public]
// ---------------------------------------------------------------------------

void
CPluginEditorWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{
	
	switch (inMessage) {
		
		case msg_Close:
		Hide();
		break;
				
		default:
		dynamic_cast<CPluginEditorDoc *>(GetSuperCommander())->ListenToMessage(inMessage, ioParam);
		break;
				
	}
}


// ---------------------------------------------------------------------------
//  FindCommandStatus
// ---------------------------------------------------------------------------
//	Pass back whether a Command is enabled and/or marked (in a Menu)

void
CPluginEditorWindow::FindCommandStatus(
	CommandT	inCommand,
	Boolean		&outEnabled,
	Boolean		&outUsesMark,
	UInt16		&outMark,
	Str255		outName)
{
	outEnabled = true;

	switch (inCommand) {
		
		case cmd_EditRez:
		case cmd_EditRezAsType:
		case cmd_EditWithPlugin:
		case cmd_TmplEditRez:
		case cmd_HexEditRez:
		case cmd_RemoveRez:
		case cmd_DuplicateRez:
		outEnabled = false;
		break;		
		
		default:
		if (mOwnerDoc) {
			mOwnerDoc->FindCommandStatus(inCommand, outEnabled,
												outUsesMark, outMark, outName);
		} else {
			LCommander::FindCommandStatus(inCommand, outEnabled,
												outUsesMark, outMark, outName);
		}
		break;
	}
}


// ---------------------------------------------------------------------------
//  ObeyCommand							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CPluginEditorWindow::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;
	ResIDT		theMenuID;
	SInt16		theMenuItem;

	if ( LCommander::IsSyntheticCommand( inCommand, theMenuID, theMenuItem ) ) {
		if ( IsPluginMenu(theMenuID) ) {
			MenuHandle	theMenuH = ::GetMenuHandle( theMenuID );
			if ( theMenuH ) {
				(*mInterface)->HandleMenu(mPlugRef, theMenuH, theMenuItem);
			}
		}
		return true;
	}

	switch (inCommand) {

		case cmd_Cut:
		(*mInterface)->HandleCommand(mPlugRef, kPluginCommandCut);
		break;

		case cmd_Copy:
		(*mInterface)->HandleCommand(mPlugRef, kPluginCommandCopy);
		break;
		
		case cmd_Paste:
		(*mInterface)->HandleCommand(mPlugRef, kPluginCommandPaste);
		break;

		case cmd_Clear:
		(*mInterface)->HandleCommand(mPlugRef, kPluginCommandClear);
		break;

		case cmd_SelectAll:
		(*mInterface)->HandleCommand(mPlugRef, kPluginCommandSelectAll);
		break;		
		
		case cmd_Find:
		(*mInterface)->HandleCommand(mPlugRef, kPluginCommandFind);
		break;

		case cmd_FindNext:
		(*mInterface)->HandleCommand(mPlugRef, kPluginCommandFindNext);
		break;

		case cmd_ActionCut:
		case cmd_ActionPaste:
		case cmd_ActionClear:
		case cmd_ActionTyping: {
			break;
		}

		default:
		cmdHandled = mOwnerDoc->ObeyCommand(inCommand, ioParam);
		break;
	}

	return cmdHandled;
}


// ---------------------------------------------------------------------------
//   HandleKeyPress							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CPluginEditorWindow::HandleKeyPress(
	const EventRecord	&inKeyEvent)
{
	Boolean		keyHandled	 = true;
	// Let the plugin handle the keystroke
	(*mInterface)->HandleKeyDown(mPlugRef, &inKeyEvent);
	return keyHandled;
}


// ---------------------------------------------------------------------------
//   Click
// ---------------------------------------------------------------------------

void
CPluginEditorWindow::Click(
	SMouseDownEvent	&inMouseDown)
{
	// Check if a SubPane of this window is hit
	LPushButton * clickedPane = dynamic_cast<LPushButton*>(FindDeepSubPaneContaining(inMouseDown.wherePort.h, inMouseDown.wherePort.v));

	if (clickedPane != nil) {
		
		switch (clickedPane->GetPaneID()) {
			case item_EditorSave:
			clickedPane->BroadcastMessage(msg_EditorSave);
			break;
			
			case item_EditorCancel:
			clickedPane->BroadcastMessage(msg_EditorCancel);
			break;
			
			case item_EditorRevert:
			clickedPane->BroadcastMessage(msg_EditorRevert);
			break;
			
			default:
			clickedPane->Click(inMouseDown);
			break;
		
		}
	} else {						
		// No SubPane hit, pass to plugin
		(*mInterface)->HandleClick(mPlugRef, &inMouseDown.macEvent, inMouseDown.whereLocal);
	}
}


// ---------------------------------------------------------------------------
//   Refresh
// ---------------------------------------------------------------------------

void
CPluginEditorWindow::Refresh()
{
	LView::Refresh();
	
	(*mInterface)->Refresh(mPlugRef);
}


// ---------------------------------------------------------------------------
// 	PutOnDuty
// ---------------------------------------------------------------------------

void
CPluginEditorWindow::PutOnDuty(LCommander *inNewTarget)
{
	LWindow::PutOnDuty(inNewTarget);

	// Put up our menus when on duty
	LMenuBar *	theBar = LMenuBar::GetCurrentMenuBar();
	TArray<LMenu*>* menusListPtr = dynamic_cast<CPluginEditorDoc *>(mOwnerDoc)->GetPlugin()->GetMenusList();

	TArrayIterator<LMenu*> iterator(*menusListPtr);
	LMenu	*theMenu;
	while (iterator.Next(theMenu)) {
		// Update the menu bar
		theBar->InstallMenu( theMenu, MENU_OpenedWindows );	
	}
	// To query the plugin about modifications
	this->StartIdling();
}


// ---------------------------------------------------------------------------
// 	TakeOffDuty
// ---------------------------------------------------------------------------

void
CPluginEditorWindow::TakeOffDuty()
{		
	LWindow::TakeOffDuty();
	RemovePluginMenus();
	
	this->StopIdling();
}


// ---------------------------------------------------------------------------
// 	RemovePluginMenus
// ---------------------------------------------------------------------------

void
CPluginEditorWindow::RemovePluginMenus()
{
	LMenuBar *	theBar = LMenuBar::GetCurrentMenuBar();
	TArray<LMenu*>* menusListPtr = dynamic_cast<CPluginEditorDoc *>(mOwnerDoc)->GetPlugin()->GetMenusList();

	TArrayIterator<LMenu*> iterator(*menusListPtr);
	LMenu	*theMenu;
	while (iterator.Next(theMenu)) {
		// Update the menu bar
		theBar->RemoveMenu(theMenu);	
	}
}


// ---------------------------------------------------------------------------
//  SpendTime
// ---------------------------------------------------------------------------

void
CPluginEditorWindow::SpendTime(const EventRecord& inMacEvent)
{	
	Boolean modified = (*mInterface)->IsModified(mPlugRef);
	SetDirty(modified);
}


// ---------------------------------------------------------------------------
// 	IsPluginMenu
// ---------------------------------------------------------------------------

Boolean
CPluginEditorWindow::IsPluginMenu(ResIDT inMenuID)
{
	Boolean isPluginMenu = false;
	
	TArray<LMenu*>* menusListPtr = dynamic_cast<CPluginEditorDoc *>(mOwnerDoc)->GetPlugin()->GetMenusList();

	TArrayIterator<LMenu*> iterator(*menusListPtr);
	LMenu	*theMenu;
	while (iterator.Next(theMenu)) {
		if (theMenu->GetMenuID() == inMenuID) {
			isPluginMenu = true;
			break;
		} 	
	}
	return isPluginMenu;
}


// ---------------------------------------------------------------------------
//  RevertContents												  [public]
// ---------------------------------------------------------------------------

void
CPluginEditorWindow::RevertContents()
{
	OSErr error = noErr;
	
	// Reinstall the strings
	CRezObj * theRezObj = mOwnerDoc->GetRezObj();
	if (theRezObj != nil) {
		Handle rezData = theRezObj->GetData();
		
		try {
			if (rezData != nil) {
				// Work with a copy of the handle
				::HandToHand(&rezData);
				error = (*mInterface)->RevertResource(mPlugRef, rezData);
			} 
			ThrowIfError_(error);			
		} catch (...) {
			dynamic_cast<CPluginEditorDoc *>(mOwnerDoc)->ReportPluginError(CFSTR("ErrorUsingPluginEditor"), error);
			return;
		}
	} 
	
	SetDirty(false);
}


// ---------------------------------------------------------------------------
//  GetContentsRect												  [public]
// ---------------------------------------------------------------------------

void
CPluginEditorWindow::GetContentsRect(
	Rect	&outRect) const
{
	SDimension16	frameSize;
	GetFrameSize(frameSize);
	
	outRect.top = mHasHeader ? kPluginHeaderHeight : 0;
	outRect.left = 0;
	
	outRect.right = frameSize.width;
	outRect.bottom = frameSize.height;
	if (mHasFooter) {
		outRect.bottom -= kPluginFooterHeight;
	}
}


// ---------------------------------------------------------------------------
//   ResizeWindowBy
// ---------------------------------------------------------------------------
//	Change the size of a Window by the specified number of pixels

void
CPluginEditorWindow::ResizeWindowBy(
	SInt16	inWidthDelta,
	SInt16	inHeightDelta)
{
	Rect	theBounds;
	GetGlobalBounds(theBounds);

	theBounds.right += inWidthDelta;
	theBounds.bottom += inHeightDelta;
	DoSetBounds(theBounds);
	
	(*mInterface)->ResizeBy(mPlugRef, inWidthDelta, inHeightDelta);
}


// ---------------------------------------------------------------------------
//   WindowEventHandler										[public] [static]
// ---------------------------------------------------------------------------

pascal OSStatus 
CPluginEditorWindow::WindowEventHandler(EventHandlerCallRef myHandler, 
		EventRef event, void *userData)
{
	OSStatus 	result = eventNotHandledErr;
	UInt32		eventKind = GetEventKind(event);
	HICommand	command;
	
	CPluginEditorWindow * plugWin = (CPluginEditorWindow*) userData;
	
	switch (eventKind) {
		case kEventWindowClose:
		plugWin->ListenToMessage(msg_Close, NULL);
		result = noErr;
		break;
		
		case kEventCommandProcess:
		GetEventParameter(event, kEventParamDirectObject, typeHICommand, NULL, sizeof(HICommand), 
						  NULL, &command);
		switch (command.commandID) {
			
			case kHICommandOK:
			plugWin->ListenToMessage(msg_EditorSave, NULL);
			result = noErr;
			break;
		
			case kHICommandCancel:
			plugWin->ListenToMessage(msg_EditorCancel, NULL);
			result = noErr;
			break;
			
			case kHICommandRevert:
			plugWin->ListenToMessage(msg_EditorRevert, NULL);
			result = noErr;
			break;
		}
	}
	return result;
}

