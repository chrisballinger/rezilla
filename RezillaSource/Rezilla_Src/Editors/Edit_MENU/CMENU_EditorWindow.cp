// ===========================================================================
// CMENU_EditorWindow.cp					
// 
//                       Created: 2005-03-09 17:16:53
//             Last modification: 2005-03-09 17:16:57
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CMENU_EditorDoc.h"
#include "CMENU_EditorWindow.h"
#include "CMENU_EditorTable.h"
#include "CRezObj.h"
#include "CRezillaApp.h"
#include "CRezMap.h"
#include "CRezillaPrefs.h"
#include "RezillaConstants.h"
#include "UMiscUtils.h"
#include "UMessageDialogs.h"
#include "UHexFilters.h"
#include "UCodeTranslator.h"

#include <LScrollBar.h>
#include <LStaticText.h>
#include <LEditText.h>
#include <LScrollerView.h>
#include <UMemoryMgr.h>

#include <stdio.h>



// ---------------------------------------------------------------------------
//  CMENU_EditorWindow				[public]
// ---------------------------------------------------------------------------

CMENU_EditorWindow::CMENU_EditorWindow()
{
}


// ---------------------------------------------------------------------------
//  CMENU_EditorWindow				[public]
// ---------------------------------------------------------------------------

CMENU_EditorWindow::CMENU_EditorWindow(
	const SWindowInfo &inWindowInfo )
		: CEditorWindow( inWindowInfo )
{
}


// ---------------------------------------------------------------------------
//  CMENU_EditorWindow				[public]
// ---------------------------------------------------------------------------

CMENU_EditorWindow::CMENU_EditorWindow(
	ResIDT		inWINDid,
	UInt32		inAttributes,
	LCommander	*inSuperCommander )
		: CEditorWindow( inWINDid, inAttributes, inSuperCommander )
{
}


// ---------------------------------------------------------------------------
//  CMENU_EditorWindow				[public]
// ---------------------------------------------------------------------------

CMENU_EditorWindow::CMENU_EditorWindow(
			       LStream *inStream )
		: CEditorWindow( inStream )
{
}


// ---------------------------------------------------------------------------
//  ~CMENU_EditorWindow				[public]
// ---------------------------------------------------------------------------

CMENU_EditorWindow::~CMENU_EditorWindow()
{	
// 	// Remove the window from the list of listeners to the prefs object
// 	CRezillaApp::sPrefs->RemoveListener(this);
}


// ---------------------------------------------------------------------------
// FinishCreateSelf											[protected]
// ---------------------------------------------------------------------------

void
CMENU_EditorWindow::FinishCreateSelf()
{	
	// The main view containing the labels and editing panes
	mItemsTable = dynamic_cast<CMENU_EditorTable *>(this->FindPaneByID(item_EditorContents));
	ThrowIfNil_( mItemsTable );
	
	mItemsTable->SetOwnerWindow(this);
	
// 	SwitchTarget(mItemsTable);
	
	// The total length field
	mLengthField = dynamic_cast<LStaticText *> (this->FindPaneByID( item_TextEditLength ));
	ThrowIfNil_( mLengthField );
	
	// Link the broadcasters
	UReanimator::LinkListenerToControls( this, this, PPob_TextEditorWindow );
	
// 	// Make the window a listener to the prefs object
// 	CRezillaApp::sPrefs->AddListener(this);

}


// ---------------------------------------------------------------------------
//  ListenToMessage				[public]
// ---------------------------------------------------------------------------

void
CMENU_EditorWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{	
	switch (inMessage) {
		
		default:
		dynamic_cast<CMENU_EditorDoc *>(mOwnerDoc)->ListenToMessage(inMessage, ioParam);
		break;
				
	}
}


// ---------------------------------------------------------------------------
//	¥ FindCommandStatus
// ---------------------------------------------------------------------------

void
CMENU_EditorWindow::FindCommandStatus(
	CommandT	inCommand,
	Boolean		&outEnabled,
	Boolean		&outUsesMark,
	UInt16		&outMark,
	Str255		outName)
{
	switch (inCommand) {
		
		default:
		CEditorWindow::FindCommandStatus(inCommand, outEnabled,
									  outUsesMark, outMark, outName);
		break;
	}
}


// ---------------------------------------------------------------------------
//	¥ ObeyCommand							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CMENU_EditorWindow::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;
	
	switch (inCommand) {

		default:
			cmdHandled = LCommander::ObeyCommand(inCommand, ioParam);
			break;
	}

	return cmdHandled;
}


// ---------------------------------------------------------------------------
//	¥ InstallMenuData													[public]
// ---------------------------------------------------------------------------

void
CMENU_EditorWindow::InstallMenuData(Handle inMenuHandle, Handle inXmnuHandle)
{
// 	StHandleLocker	lock(inTextHandle);
// 	mItemsTable->SetTextHandle(inTextHandle, inScrapHandle);
	SetDirty(false);
}


// ---------------------------------------------------------------------------
//  ¥ CollectMenuData										[public]
// ---------------------------------------------------------------------------

Handle
CMENU_EditorWindow::CollectMenuData() 
{
	Handle	menuHandle = RetrieveMenuData();
	Handle	xmnuHandle = RetrieveXmnuData();
		
	dynamic_cast<CMENU_EditorDoc *>(mOwnerDoc)->SaveXmnuResource(xmnuHandle);

	return menuHandle;
}


// ---------------------------------------------------------------------------
//  ¥ RetrieveMenuData										[public]
// ---------------------------------------------------------------------------

Handle
CMENU_EditorWindow::RetrieveMenuData() 
{
	Handle	menuHandle = NULL;

	return menuHandle;
}


// ---------------------------------------------------------------------------
//  ¥ RetrieveXmnuData										[public]
// ---------------------------------------------------------------------------

Handle
CMENU_EditorWindow::RetrieveXmnuData() 
{
	Handle	xmnuHandle = NULL;

	return xmnuHandle;
}






