// ===========================================================================
// CPluginEditorWindow.cp
// 
//                       Created: 2005-10-02 08:41:52
//             Last modification: 2006-02-21 17:21:03
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2005-2006
// All rights reserved.
// ===========================================================================

#include "CPluginEditorWindow.h"
#include "RezillaPluginInterface.h"
#include "CPluginEditorDoc.h"
#include "CPluginEditorView.h"
#include "CRezillaPlugin.h"
#include "CRezObj.h"
#include "CWindowMenu.h"
#include "RezillaConstants.h"

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
}


// ---------------------------------------------------------------------------
//  CPluginEditorWindow				[public]
// ---------------------------------------------------------------------------

CPluginEditorWindow::CPluginEditorWindow(
	const SWindowInfo &inWindowInfo )
		: CEditorWindow( inWindowInfo )
{
}


// ---------------------------------------------------------------------------
//  CPluginEditorWindow				[public]
// ---------------------------------------------------------------------------

CPluginEditorWindow::CPluginEditorWindow(
	ResIDT		inWINDid,
	UInt32		inAttributes,
	LCommander	*inSuperCommander )
		: CEditorWindow( inWINDid, inAttributes, inSuperCommander )
{
}


// ---------------------------------------------------------------------------
//  CPluginEditorWindow				[public]
// ---------------------------------------------------------------------------

CPluginEditorWindow::CPluginEditorWindow(
					WindowPtr		inMacWindow,
					LCommander*		inSuperCommander)
		: CEditorWindow(inMacWindow, inSuperCommander)
{
}


// ---------------------------------------------------------------------------
//  CPluginEditorWindow				[public]
// ---------------------------------------------------------------------------

CPluginEditorWindow::CPluginEditorWindow(
				   LStream *inStream )
		: CEditorWindow( inStream )
{
}


// ---------------------------------------------------------------------------
//  ~CPluginEditorWindow				[public]
// ---------------------------------------------------------------------------

CPluginEditorWindow::~CPluginEditorWindow()
{
	RemovePluginMenus();
	
	SRezillaPluginInterface** interface = dynamic_cast<CPluginEditorDoc *>(mOwnerDoc)->GetPlugin()->GetInterface();
	(*interface)->CleanUp(interface);
}


// ---------------------------------------------------------------------------
//  FinalizeEditor											[public]
// ---------------------------------------------------------------------------

void
CPluginEditorWindow::FinalizeEditor(CPluginEditorDoc* inEditorDoc, void * ioParam)
{
	SInt32				theAttrs = *((SInt32*) ioParam);
	Boolean				hasHeader = false, hasFooter = false;
	SPaneInfo			pi;
	SViewInfo			vi;
	SDimension16		frameSize;

	SetOwnerDoc(inEditorDoc);
	SetSuperModel(inEditorDoc);
	
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
		LWindowHeader * theWindowHeader = new LWindowHeader(pi, vi);
		ThrowIfNil_(theWindowHeader);

		pi.paneID			= item_NameStaticText;
		pi.width			-= 20;
		pi.height			-= 10;
		pi.left				= 10;
		pi.top				= 5;
		pi.superView		= theWindowHeader;
		
		LStaticText * theStaticText = new LStaticText(pi, "\p", Txtr_GenevaNine);
		ThrowIfNil_(theStaticText);

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
		ThrowIfNil_( theFooter );

		pi.width			= 65;
		pi.height			= 20;
		pi.bindings.top		= true;
		pi.top				= 9;
		pi.left				= frameSize.width;
		pi.superView		= theFooter;

		if ( (theAttrs & kPlugWinHasSaveButton) != 0) {
			pi.paneID			= item_EditorValidate;
			pi.bindings.left	= false;
			pi.bindings.right	= true;
			pi.left				= frameSize.width - 86;
			thePushButton = new LPushButton(pi, msg_OK, "\pSave");
			ThrowIfNil_( thePushButton );
		}
		if ( (theAttrs & kPlugWinHasCancelButton) != 0) {
			pi.paneID			= item_EditorCancel;
			pi.bindings.left	= false;
			pi.bindings.right	= true;
			pi.left				= frameSize.width - 164;
			thePushButton = new LPushButton(pi, msg_OK, "\pCancel");
			ThrowIfNil_( thePushButton );
		}
		if ( (theAttrs & kPlugWinHasRevertButton) != 0) {
			pi.paneID			= item_EditorRevert;
			pi.bindings.left	= true;
			pi.bindings.right	= false;
			pi.left				= 28;
			thePushButton = new LPushButton(pi, msg_OK, "\pRevert");
			ThrowIfNil_( thePushButton );
		}
		if ( (theAttrs & kPlugWinHasLockIcon) != 0) {
			pi.paneID			= item_ReadOnlyIcon;
			pi.bindings.left	= true;
			pi.bindings.right	= false;
			pi.left				= 9;
			LIconPane * theLockIcon = new LIconPane(pi, 0);
			ThrowIfNil_( theLockIcon );
			
			InstallReadOnlyIcon();
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
				SRezillaPluginInterface** interface = dynamic_cast<CPluginEditorDoc *>(mOwnerDoc)->GetPlugin()->GetInterface();
				(*interface)->HandleMenu(theMenuH, theMenuItem);
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
	
	SRezillaPluginInterface** interface = dynamic_cast<CPluginEditorDoc *>(mOwnerDoc)->GetPlugin()->GetInterface();
	(*interface)->HandleKeyDown(&inKeyEvent);
	return keyHandled;
}


// ---------------------------------------------------------------------------
//   Click
// ---------------------------------------------------------------------------

void
CPluginEditorWindow::Click(
	SMouseDownEvent	&inMouseDown)
{
	SRezillaPluginInterface** interface = dynamic_cast<CPluginEditorDoc *>(mOwnerDoc)->GetPlugin()->GetInterface();
	(*interface)->HandleClick(&inMouseDown.macEvent, inMouseDown.whereLocal);
}


// ---------------------------------------------------------------------------
//   Refresh
// ---------------------------------------------------------------------------

void
CPluginEditorWindow::Refresh()
{
	LView::Refresh();
	
	SRezillaPluginInterface** interface = dynamic_cast<CPluginEditorDoc *>(mOwnerDoc)->GetPlugin()->GetInterface();
	(*interface)->Refresh(interface);
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
}


// ---------------------------------------------------------------------------
// 	TakeOffDuty
// ---------------------------------------------------------------------------

void
CPluginEditorWindow::TakeOffDuty()
{		
	LWindow::TakeOffDuty();
	RemovePluginMenus();
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
// Override in subclasses to redraw the contents view with the last saved 
// data.

void
CPluginEditorWindow::RevertContents()
{
	SetDirty(false);
}


// // void DrawWindow(WindowRef window)
// // {
// // 	Rect		tempRect;
// // 	GrafPtr		curPort;
// // 	
// // 	GetPort(&curPort);
// // 	SetPort(GetWindowPort(window));
// // 	BeginUpdate(window);
// // 	EraseRect(GetWindowPortBounds(window, &tempRect));
// // 	DrawControls(window);
// // 	DrawGrowIcon(window);
// // 	EndUpdate(window);
// // 	SetPort(curPort);
// // }
