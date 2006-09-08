// ===========================================================================
// CPluginEditorWindow.cp
// 
//                       Created: 2005-10-02 08:41:52
//             Last modification: 2006-03-09 13:10:46
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

// 	// Remove the window from the window menu.
// 	gWindowMenu->RemoveWindow(this);
}


// ---------------------------------------------------------------------------
//  FinalizeEditor											[public]
// ---------------------------------------------------------------------------


void
CPluginEditorWindow::FinalizeEditor(CPluginEditorDoc* inEditorDoc, void * ioParam)
{
#pragma unused(ioParam)
	char	theStr[256];
	OSErr	error;
	
	// Set mOwnerDoc
	SetOwnerDoc(inEditorDoc);
	SetSuperModel(inEditorDoc);
	
	mInterface = dynamic_cast<CPluginEditorDoc *>(mOwnerDoc)->GetPlugin()->GetInterface();
	ThrowIfNil_(mInterface);
			
	::CopyPascalStringToC(*(inEditorDoc->GetRezObj()->GetName()), (char*) theStr);
	error = ::SetControlData(mNameRef, kControlNoPart, kControlStaticTextTextTag, strlen(theStr), theStr);
// 	::Draw1Control(mNameRef);
	::HIViewSetNeedsDisplay(mNameRef, true);
	
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
	ControlRef			ctrlRef;
	ControlID			ctrlID;
	OSStatus			error;
	HIViewRef			contentView = NULL;

	ctrlID.signature = kRezillaSig;
	
	mHeaderRef = NULL;
	mNameRef = NULL;
	mFooterRef = NULL;
	mSaveRef = NULL;	
	mCancelRef = NULL;
	mRevertRef = NULL;
	
	GetFrameSize(frameSize);
	HIViewFindByID(HIViewGetRoot(winRef), kHIViewWindowContentID, &contentView);
	ThrowIfNil_(contentView);

	if ( inPlugAttrs != kPluginNoAttributes && (inPlugAttrs & kPluginEditorHasNameField) != 0 ) {		
		ControlFontStyleRec		cfsr;

		// Create a header
		boundsRect.top		= 0;
		boundsRect.bottom	= kPluginHeaderHeight;
		boundsRect.left		= 0;
		boundsRect.right	= frameSize.width;

		error = CreateWindowHeaderControl(winRef, &boundsRect, false, &mHeaderRef);
		ThrowIfOSErr_(error);
				
		HIViewAddSubview(contentView, mHeaderRef);
		HIViewSetVisible(mHeaderRef, true);
		
		// Create the name field
		boundsRect.top		= kEditorVertTextMargin;
		boundsRect.bottom	= boundsRect.top + kEditorNameHeight;
		boundsRect.left		= kEditorHorizTextMargin;
		boundsRect.right	= frameSize.width - kEditorHorizTextMargin;
	
		error = CreateStaticTextControl(NULL, &boundsRect, NULL, NULL, &mNameRef);
		ThrowIfOSErr_(error);
		
		cfsr.flags = kControlUseFontMask + kControlUseSizeMask;
		::GetFNum("\pGeneva", &cfsr.font);
		cfsr.size = 9;
		error = ::SetControlData(mNameRef, kControlNoPart, kControlStaticTextStyleTag, 
								 sizeof(ControlFontStyleRec), &cfsr);

		ctrlID.id = item_NameStaticText;
		SetControlID(mNameRef, &ctrlID);
		HIViewAddSubview(mHeaderRef, mNameRef);
		HIViewSetVisible(mNameRef, true);			  
	}	
	
	if ( inPlugAttrs != kPluginNoAttributes && (inPlugAttrs & kPluginEditorStandardControls) != 0 ) {
		
		// Create a footer
		boundsRect.top		= frameSize.height - kPluginFooterHeight;
		boundsRect.bottom	= frameSize.height;
		boundsRect.left		= 0;
		boundsRect.right	= frameSize.width;
		
		error = CreatePlacardControl(winRef, &boundsRect, &mFooterRef);
		ThrowIfOSErr_(error);
				
		HIViewAddSubview(contentView, mFooterRef);
		HIViewSetVisible(mFooterRef, true);

		boundsRect.top			= kEditorButtonTop;
		boundsRect.bottom		= boundsRect.top + kEditorButtonHeight ;
		if ( (inPlugAttrs & kPluginEditorHasSaveButton) != 0) {
			Boolean	flag = true;
			
			// Create a Save button
			boundsRect.left		= frameSize.width - kEditorSaveRightPos;
			boundsRect.right	= boundsRect.left + kEditorButtonWidth;

			error = CreatePushButtonControl(NULL, &boundsRect, CFSTR("Save"), &mSaveRef);
			ThrowIfOSErr_(error);

			// Make it the default button
			SetControlData(mSaveRef, kControlEntireControl, kControlPushButtonDefaultTag,
						   sizeof(flag), &flag);
			
			ctrlID.id = kHICommandOK;
			SetControlID(mSaveRef, &ctrlID);
			SetControlCommandID(mSaveRef, kHICommandOK);
			HIViewAddSubview(mFooterRef, mSaveRef);
			HIViewSetVisible(mSaveRef, true);
		}
		if ( (inPlugAttrs & kPluginEditorHasCancelButton) != 0) {
			// Create a Cancel button
			boundsRect.left		= frameSize.width - kEditorCancelRightPos;
			boundsRect.right	= boundsRect.left + kEditorButtonWidth;

			error = CreatePushButtonControl(NULL, &boundsRect, CFSTR("Cancel"), &mCancelRef);
			ThrowIfOSErr_(error);
		
			ctrlID.id = kHICommandCancel;
			SetControlID(mCancelRef, &ctrlID);
			SetControlCommandID(mCancelRef, kHICommandCancel);
			HIViewAddSubview(mFooterRef, mCancelRef);
			HIViewSetVisible(mCancelRef, true);
		}
		if ( (inPlugAttrs & kPluginEditorHasRevertButton) != 0) {
			// Create a Revert button
			boundsRect.left		= kEditorRevertLeftPos;
			boundsRect.right	= boundsRect.left + kEditorButtonWidth;

			error = CreatePushButtonControl(NULL, &boundsRect, CFSTR("Revert"), &mRevertRef);
			ThrowIfOSErr_(error);
		
			ctrlID.id = kHICommandRevert;
			SetControlID(mRevertRef, &ctrlID);
			SetControlCommandID(mRevertRef, kHICommandRevert);
			HIViewAddSubview(mFooterRef, mRevertRef);
			HIViewSetVisible(mRevertRef, true);
		}
		if ( (inPlugAttrs & kPluginEditorHasLockIcon) != 0) {
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
}
	

// ---------------------------------------------------------------------------
//  MoveControls													[public]
// ---------------------------------------------------------------------------
// 		OSStatus HIViewMoveBy(
// 		  HIViewRef   inView,
// 		  float       inDX,
// 		  float       inDY)
// 
// 
// 		OSStatus HIViewSetFrame(
// 		HIViewRef       inView,
// 		const HIRect *  inRect)
// 
// 
// 		OSStatus HIViewGetFrame(
// 		  HIViewRef   inView,
// 		  HIRect *    outRect)
// 		OSStatus 
// 		GetWindowBounds(
// 		  WindowRef          window,
// 		  WindowRegionCode   regionCode,
// 		  Rect *             globalBounds);
// kWindowContentRgn
// kWindowGlobalPortRgn
// kWindowStructureRgn
// 			hiBounds.origin.x	= ;
// 			hiBounds.origin.y	= ;
// 			hiBounds.size.height	= ;

void
CPluginEditorWindow::AdaptControlsToWindowBounds()
{
	WindowRef		winRef = GetMacWindow();
	SInt16			widthDelta, heightDelta;
	Rect			oldBounds, newBounds;
	HIRect			hiBounds;
	SInt16			oldWidth, newWidth;
	SInt16			oldHeight, newHeight;

	GetGlobalBounds(oldBounds);
 
	::GetWindowBounds(winRef, kWindowGlobalPortRgn, &newBounds);
	
	oldWidth = (oldBounds.right - oldBounds.left);
	oldHeight = (oldBounds.bottom - oldBounds.top);
	newWidth = (newBounds.right - newBounds.left);
	newHeight = (newBounds.bottom - newBounds.top);

	if (mHeaderRef != NULL) {
		if (newWidth != oldWidth) {
			// Resize the header and the name field
			HIViewGetFrame(mHeaderRef, &hiBounds);
			hiBounds.size.width	+= newWidth - oldWidth;
			HIViewSetFrame(mHeaderRef, &hiBounds);
			HIViewGetFrame(mNameRef, &hiBounds);
			hiBounds.size.width	+= newWidth - oldWidth;
			HIViewSetFrame(mNameRef, &hiBounds);
		} 
	
	} 
	
	if (mFooterRef != NULL) {
		if (newHeight != oldHeight) {
			// Reposition the footer
			HIViewMoveBy(mFooterRef, 0, newHeight - oldHeight);
		} 
		if (newWidth != oldWidth) {
			// Resize the footer
			HIViewGetFrame(mFooterRef, &hiBounds);
			hiBounds.size.width	+= newWidth - oldWidth;
			HIViewSetFrame(mFooterRef, &hiBounds);

			// Reposition the Cancel and Save buttons
			HIViewMoveBy(mCancelRef, newWidth - oldWidth, 0);
			HIViewMoveBy(mSaveRef, newWidth - oldWidth, 0);
		} 
	} 

	// Update the LWindow values
	DoSetBounds(newBounds);
	
	// Pass the deltas to the plugin so that it can adapt its own views
	(*mInterface)->ResizeBy(mPlugRef, newWidth - oldWidth, newHeight - oldHeight);
}


// ---------------------------------------------------------------------------
//  ListenToMessage									[public]
// ---------------------------------------------------------------------------

void
CPluginEditorWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{
	switch (inMessage) {

		case msg_ForwardToPlugin:
		EventRef event = (EventRef) ioParam;
//		(*mInterface)->HandleEvent(mPlugRef, event);
		break;
		
		case msg_Close:
		dynamic_cast<CPluginEditorDoc *>(GetSuperCommander())->AttemptClose(false);
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
		case cmd_Import:
		(*mInterface)->HandleCommand(mPlugRef, kPluginCommandImport);
		break;

		case cmd_Export:
		(*mInterface)->HandleCommand(mPlugRef, kPluginCommandExport);
		break;

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
	(*mInterface)->HandleClick(mPlugRef, &inMouseDown.macEvent, inMouseDown.whereLocal);
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
#pragma unused(inMacEvent)

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
	
	outRect.top = (mHeaderRef != nil) ? kPluginHeaderHeight : 0;
	outRect.left = 0;
	
	outRect.right = frameSize.width;
	outRect.bottom = frameSize.height;
	if (mFooterRef != nil) {
		outRect.bottom -= kPluginFooterHeight;
	}
}


// ---------------------------------------------------------------------------
//   ResizeWindowBy
// ---------------------------------------------------------------------------
//	Change the size of the window by the specified number of pixels and 
//	notify the plugin

void
CPluginEditorWindow::ResizeWindowBy(
	SInt16	inWidthDelta,
	SInt16	inHeightDelta)
{
	Rect	theBounds;
	GetGlobalBounds(theBounds);

	theBounds.right += inWidthDelta;
	theBounds.bottom += inHeightDelta;
	
	if (theBounds.right - theBounds.left < kPluginWindowMinWidth) {
		theBounds.right = theBounds.left + kPluginWindowMinWidth;
	} 
	if (theBounds.bottom - theBounds.top < kPluginWindowMinHeight) {
		theBounds.bottom = theBounds.top + kPluginWindowMinHeight;
	} 
	
	DoSetBounds(theBounds);
	
	(*mInterface)->ResizeBy(mPlugRef, inWidthDelta, inHeightDelta);
}


// ---------------------------------------------------------------------------
//   WindowEventHandler										[public] [static]
// ---------------------------------------------------------------------------

pascal OSStatus 
CPluginEditorWindow::WindowEventHandler(
					EventHandlerCallRef myHandler, 
					EventRef event, 
					void * userData)
{
	OSStatus 	result = eventNotHandledErr;
	UInt32		eventKind = GetEventKind(event);
	HICommand	command;
	
	CPluginEditorWindow * plugWin = dynamic_cast<CPluginEditorWindow*>((LWindow*) userData);

	if (plugWin != NULL) {
		switch (eventKind) {
			case kEventWindowClose:
			plugWin->ListenToMessage(msg_Close, NULL);
			result = noErr;
			break;
			
			case kEventWindowBoundsChanged:
			plugWin->AdaptControlsToWindowBounds();
			result = noErr;
			break;
			
			case kEventWindowActivated:
			plugWin->PutOnDuty(NULL);
			result = noErr;
			break;
			
			case kEventWindowDeactivated:
			plugWin->TakeOffDuty();
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
				
				default:
				plugWin->ListenToMessage(msg_ForwardToPlugin, event);
				result = noErr;
				break;
			}
		}
	} 

	return result;
}

