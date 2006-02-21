// ===========================================================================
// CPluginEditorWindow.cp
// 
//                       Created: 2005-10-02 08:41:52
//             Last modification: 2006-02-21 06:36:12
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
}


// ---------------------------------------------------------------------------
//  FinalizeEditor											[public]
// ---------------------------------------------------------------------------
// // // RezPluginRequirements	plugReq;
// // // 
// // // BlockMoveData(ioParam, &plugReq, sizeof(RezPluginRequirements));
// // // 
// // // // 	= *(RezPluginRequirements*) ioParam;

void
CPluginEditorWindow::FinalizeEditor(CPluginEditorDoc* inEditorDoc, void * ioParam)
{
	SInt32	theAttrs = *((SInt32*) ioParam);
	Boolean	noHeader = false, noFooter = false;
	SInt16	delta = 0;
	
	SetOwnerDoc(inEditorDoc);
	SetSuperModel(inEditorDoc);
	
	if ( (theAttrs & kPlugWinStandardAttributes) == 0 || theAttrs == kPlugWinHasNoAttributes ) {
		LPlacard * theFooterPlacard = dynamic_cast<LPlacard *>(this->FindPaneByID( item_EditorFooter ));
		ThrowIfNil_( theFooterPlacard );
		theFooterPlacard->PutInside(nil);
		noFooter = true;
	} else {
		LPushButton *	thePushButton;
		if ( (theAttrs & kPlugWinHasSaveButton) == 0) {
			thePushButton = dynamic_cast<LPushButton *>(this->FindPaneByID( item_EditorValidate ));
			ThrowIfNil_( thePushButton );
			thePushButton->PutInside(nil);
		}
		if ( (theAttrs & kPlugWinHasCancelButton) == 0) {
			thePushButton = dynamic_cast<LPushButton *>(this->FindPaneByID( item_EditorCancel ));
			ThrowIfNil_( thePushButton );
			thePushButton->PutInside(nil);
		}
		if ( (theAttrs & kPlugWinHasRevertButton) == 0) {
			thePushButton = dynamic_cast<LPushButton *>(this->FindPaneByID( item_EditorRevert ));
			ThrowIfNil_( thePushButton );
			thePushButton->PutInside(nil);
		}
		if ( (theAttrs & kPlugWinHasLockIcon) == 0) {
			LIconPane * theLockIcon = dynamic_cast<LIconPane *>(this->FindPaneByID( item_ReadOnlyIcon ));
			ThrowIfNil_( theLockIcon );
			theLockIcon->PutInside(nil);
		} else {
			InstallReadOnlyIcon();
		}
	}
	
	if ( (theAttrs & kPlugWinHasNameField) == 0 || theAttrs == kPlugWinHasNoAttributes) {
		LWindowHeader * theWindowHeader = dynamic_cast<LWindowHeader *>(this->FindPaneByID( item_EditorHeader ));
		ThrowIfNil_( theWindowHeader );
		theWindowHeader->PutInside(nil);
		noHeader = true;
	} else {
		InstallResourceNameField();
	}
	
	// Redimension scrollbar view if header or footer were removed
	if (noHeader || noFooter) {
		LScrollerView * theScrollerView = dynamic_cast<LScrollerView *>(this->FindPaneByID( item_EditorScroller ));
		ThrowIfNil_( theScrollerView );
		if (noHeader) {
			theScrollerView->MoveBy(0, -kPluginHeaderHeight, false);
			
		} 
		delta += noHeader? kPluginHeaderHeight : 0;
		delta += noFooter? kPluginFooterHeight : 0;
		theScrollerView->ResizeFrameBy(0, delta, false);
	} 
		
	// Add the window to the window menu.
	gWindowMenu->InsertWindow(this);
			
}
	

// ---------------------------------------------------------------------------
//  FinishCreateSelf											[protected]
// ---------------------------------------------------------------------------

void
CPluginEditorWindow::FinishCreateSelf()
{    
	// The main view containing the labels and editing panes
	mContentsView = dynamic_cast<CPluginEditorView *>(this->FindPaneByID(item_EditorContents));
	ThrowIfNil_( mContentsView );
	
	mContentsView->SetOwnerWindow(this);
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


