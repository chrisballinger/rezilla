// ===========================================================================
// CPluginEditorWindow.cp
// 
//                       Created: 2005-10-02 08:41:52
//             Last modification: 2006-02-18 11:23:46
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2005-2006
// All rights reserved.
// ===========================================================================


#include "CPluginEditorWindow.h"
#include "RezillaPluginInterface.h"
#include "CPluginEditorDoc.h"
#include "CRezObj.h"
#include "CWindowMenu.h"
#include "RezillaConstants.h"

#include <LIconPane.h>
#include <LStaticText.h>
#include <LPushButton.h>
#include <LWindowHeader.h>
#include <LPlacard.h>

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
	RemovePluginMenu();
}


// ---------------------------------------------------------------------------
//  FinalizeEditor											[public]
// ---------------------------------------------------------------------------

void
CPluginEditorWindow::FinalizeEditor(CPluginEditorDoc* inEditorDoc, void * ioParam)
{
	RezPluginRequirements	plugReq = *(RezPluginRequirements*) ioParam;
	SInt32	theAttrs = plugReq.winattrs;
	
	SetOwnerDoc(inEditorDoc);
	SetSuperModel(inEditorDoc);
	
	if ( (theAttrs & kPlugWinStandardAttributes) == 0 || theAttrs == kPlugWinHasNoAttributes ) {
		LPlacard * theFooterPlacard = dynamic_cast<LPlacard *>(this->FindPaneByID( item_FooterPlacard ));
		ThrowIfNil_( theFooterPlacard );
		theFooterPlacard->PutInside(nil);
	} else {
		if ( (theAttrs & kPlugWinHasSaveButton) == 0) {
			LPushButton * theOkButton = dynamic_cast<LPushButton *>(this->FindPaneByID( item_EditorValidate ));
			ThrowIfNil_( theOkButton );
			theOkButton->PutInside(nil);
		}
		if ( (theAttrs & kPlugWinHasCancelButton) == 0) {
			LPushButton * theCancelButton = dynamic_cast<LPushButton *>(this->FindPaneByID( item_EditorCancel ));
			ThrowIfNil_( theCancelButton );
			theCancelButton->PutInside(nil);
		}
		if ( (theAttrs & kPlugWinHasRevertButton) == 0) {
			LPushButton * theRevertButton = dynamic_cast<LPushButton *>(this->FindPaneByID( item_EditorRevert ));
			ThrowIfNil_( theRevertButton );
			theRevertButton->PutInside(nil);
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
		LWindowHeader * theWindowHeader = dynamic_cast<LWindowHeader *>(this->FindPaneByID( item_WindowHeader ));
		ThrowIfNil_( theWindowHeader );
		theWindowHeader->PutInside(nil);
	} else {
		InstallResourceNameField();
		InstallPluginNameField();
	}
	
	// Add the window to the window menu.
	gWindowMenu->InsertWindow(this);
	
	if (plugReq.menucount > 0) {
		int i;
		for (i = 0; i < plugReq.menucount; i++) {
			CreatePluginMenu( plugReq.menuIDs[i] );	
		}
	} 
			
}
	

// ---------------------------------------------------------------------------
//  FinishCreateSelf											[protected]
// ---------------------------------------------------------------------------

void
CPluginEditorWindow::FinishCreateSelf()
{    
	
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
// 		cmdHandled = LCommander::ObeyCommand(inCommand, ioParam);
		cmdHandled = mOwnerDoc->ObeyCommand(inCommand, ioParam);
		break;
	}

	return cmdHandled;
}


// ---------------------------------------------------------------------------
// 	PutOnDuty
// ---------------------------------------------------------------------------

void
CPluginEditorWindow::PutOnDuty(LCommander *inNewTarget)
{
	LWindow::PutOnDuty(inNewTarget);

	// Put up our menus when on duty
// // 	if ( !sPluginMenu )
// // 	{
// // 		sPluginMenu = new LMenu( MENU_PluginEditor );
// // 		ThrowIfNil_( sPluginMenu );
// // 	}
// // 	
// // 	// Update the menu bar
// // 	LMenuBar *	theBar = LMenuBar::GetCurrentMenuBar();
// // 	theBar->InstallMenu( sPluginMenu, MENU_OpenedWindows );	
}


// ---------------------------------------------------------------------------
// 	TakeOffDuty
// ---------------------------------------------------------------------------

void
CPluginEditorWindow::TakeOffDuty()
{		
	LWindow::TakeOffDuty();
	RemovePluginMenu();
}


// ---------------------------------------------------------------------------
// 	RemovePluginMenu
// ---------------------------------------------------------------------------

void
CPluginEditorWindow::RemovePluginMenu()
{
// // 	LMenuBar *	theBar = LMenuBar::GetCurrentMenuBar();
// // 	if ( sPluginMenu ) {
// // 		theBar->RemoveMenu( sPluginMenu );
// // 	}
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


// ---------------------------------------------------------------------------
//   InstallPluginNameField											[public]
// ---------------------------------------------------------------------------

void
CPluginEditorWindow::InstallPluginNameField() 
{
// 	// Install the name of the plugin used to edit this resource
// 	LStaticText * theStaticText = dynamic_cast<LStaticText *>(this->FindPaneByID( item_PluginNameField ));
// 	if (theStaticText != nil) {
// 		CPluginEditorDoc * theDoc = dynamic_cast<CPluginEditorDoc *>(GetSuperCommander());
// 		if (theDoc != nil) {
// 			Str255 * strPtr = theDoc->GetRezObj()->GetName();
// 			theStaticText->SetDescriptor(*strPtr);	
// 		} 
// 	} 
}


// ---------------------------------------------------------------------------
//   CreatePluginMenu											[public]
// ---------------------------------------------------------------------------

void
CPluginEditorWindow::CreatePluginMenu(MenuID inMenuID)
{
}


