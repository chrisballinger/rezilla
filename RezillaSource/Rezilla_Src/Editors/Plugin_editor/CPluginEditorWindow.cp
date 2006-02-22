// ===========================================================================
// CPluginEditorWindow.cp
// 
//                       Created: 2005-10-02 08:41:52
//             Last modification: 2006-02-22 10:48:06
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
	
	(*mInterface)->CleanUp((RezPlugRef) this);
}


// ---------------------------------------------------------------------------
//  FinalizeEditor											[public]
// ---------------------------------------------------------------------------

void
CPluginEditorWindow::FinalizeEditor(CPluginEditorDoc* inEditorDoc, void * ioParam)
{
	SInt32				theAttrs = *((SInt32*) ioParam);
	SPaneInfo			pi;
	SViewInfo			vi;
	SDimension16		frameSize;

	// Set mOwnerDoc
	SetOwnerDoc(inEditorDoc);
	SetSuperModel(inEditorDoc);
	
	mInterface = dynamic_cast<CPluginEditorDoc *>(mOwnerDoc)->GetPlugin()->GetInterface();
	ThrowIfNil_(mInterface);
		
	mHasHeader = false;
	mHasFooter = false;
	GetFrameSize(frameSize);

	pi.paneID			= item_EditorHeader;
	pi.width			= frameSize.width;
	pi.height			= kPluginHeaderHeight;
	pi.visible			= true;
	pi.enabled			= true;
	pi.bindings.left	= true;
	pi.bindings.top		= true;
	pi.bindings.right	= true;
	pi.bindings.bottom	= false;
	pi.left				= 0;
	pi.top				= 0;
	pi.userCon			= 0;
	pi.superView		= this;

	vi.imageSize.width		= pi.width;
	vi.imageSize.height		= pi.height;
	vi.scrollPos.h			= vi.scrollPos.v	= 0;
	vi.scrollUnit.h			= vi.scrollUnit.v	= 10;
	vi.reconcileOverhang	= false;

	if ( theAttrs != kPlugWinHasNoAttributes && (theAttrs & kPlugWinHasNameField) != 0 ) {
		// Create a header
		LWindowHeader * theHeader = new LWindowHeader(pi, vi);
		ThrowIfNil_(theHeader);

		pi.paneID			= item_NameStaticText;
		pi.width			-= 2 * kEditHorizMargin;
		pi.height			-= kEditNameHeight;
		pi.left				= kEditHorizMargin;
		pi.top				= kEditVertMargin;
		pi.superView		= theHeader;
		
		LStaticText * theStaticText = new LStaticText(pi, "\p", Txtr_GenevaNine);
		ThrowIfNil_(theStaticText);

		mHasHeader = true;
		InstallResourceNameField();
	} 
	
	if ( theAttrs != kPlugWinHasNoAttributes && (theAttrs & kPlugWinStandardAttributes) != 0 ) {
		LPushButton *	thePushButton;
		LPlacard * 		theFooter;
		
		// Create a header
		pi.paneID			= item_EditorFooter;
		pi.width			= frameSize.width;
		pi.height			= kPluginFooterHeight;
		pi.bindings.top		= false;
		pi.bindings.bottom	= true;
		pi.left				= 0;
		pi.top				= frameSize.height - kPluginFooterHeight;
		pi.superView		= this;

		theFooter = new LPlacard(pi, vi);
		ThrowIfNil_(theFooter);

		pi.width			= kEditButtonWidth;
		pi.height			= kEditButtonHeight;
		pi.bindings.top		= true;
		pi.top				= kEditButtonTop;
		pi.left				= frameSize.width;
		pi.superView		= theFooter;

		if ( (theAttrs & kPlugWinHasSaveButton) != 0) {
			pi.paneID			= item_EditorValidate;
			pi.bindings.left	= false;
			pi.bindings.right	= true;
			pi.left				= frameSize.width - kEditValidButtonRight;
			thePushButton = new LPushButton(pi, msg_OK, "\pSave");
			ThrowIfNil_(thePushButton);
		}
		if ( (theAttrs & kPlugWinHasCancelButton) != 0) {
			pi.paneID			= item_EditorCancel;
			pi.bindings.left	= false;
			pi.bindings.right	= true;
			pi.left				= frameSize.width - kEditCancelButtonRight;
			thePushButton = new LPushButton(pi, msg_OK, "\pCancel");
			ThrowIfNil_(thePushButton);
		}
		if ( (theAttrs & kPlugWinHasRevertButton) != 0) {
			pi.paneID			= item_EditorRevert;
			pi.bindings.left	= true;
			pi.bindings.right	= false;
			pi.left				= kEditRevertButtonLeft;
			thePushButton = new LPushButton(pi, msg_OK, "\pRevert");
			ThrowIfNil_(thePushButton);
		}
		if ( (theAttrs & kPlugWinHasLockIcon) != 0) {
			pi.paneID			= item_ReadOnlyIcon;
			pi.width			= kEditLockIconSize;
			pi.height			= kEditLockIconSize;
			pi.bindings.left	= true;
			pi.bindings.right	= false;
			pi.left				= 9;
			LIconPane * theLockIcon = new LIconPane(pi, 0);
			ThrowIfNil_( theLockIcon );
			
			InstallReadOnlyIcon();
		} 
		
		mHasFooter = true;
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

		case cmd_Copy: 
		case cmd_Cut: {
			break;
		}

		case cmd_Clear: {
			break;
		}

		case cmd_Paste: {
			break;
		}

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




