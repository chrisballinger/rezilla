// ===========================================================================
// CTEXT_EditorWindow.cp					
// 
//                       Created: 2004-06-17 12:46:55
//             Last modification: 2005-01-27 18:11:38
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CTEXT_EditorDoc.h"
#include "CTEXT_EditorWindow.h"
#include "CTEXT_EditorView.h"
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

// Statics
LMenu *		CTEXT_EditorWindow::sTextFontMenu = nil;
LMenu *		CTEXT_EditorWindow::sTextSizeMenu = nil;
LMenu *		CTEXT_EditorWindow::sTextStyleMenu = nil;


// ---------------------------------------------------------------------------
//		¥ CTEXT_EditorWindow				[public]
// ---------------------------------------------------------------------------

CTEXT_EditorWindow::CTEXT_EditorWindow()
{
}


// ---------------------------------------------------------------------------
//		¥ CTEXT_EditorWindow				[public]
// ---------------------------------------------------------------------------

CTEXT_EditorWindow::CTEXT_EditorWindow(
	const SWindowInfo &inWindowInfo )
		: CEditorWindow( inWindowInfo )
{
}


// ---------------------------------------------------------------------------
//		¥ CTEXT_EditorWindow				[public]
// ---------------------------------------------------------------------------

CTEXT_EditorWindow::CTEXT_EditorWindow(
	ResIDT		inWINDid,
	UInt32		inAttributes,
	LCommander	*inSuperCommander )
		: CEditorWindow( inWINDid, inAttributes, inSuperCommander )
{
}


// ---------------------------------------------------------------------------
//		¥ CTEXT_EditorWindow				[public]
// ---------------------------------------------------------------------------

CTEXT_EditorWindow::CTEXT_EditorWindow(
			       LStream *inStream )
		: CEditorWindow( inStream )
{
}


// ---------------------------------------------------------------------------
//		¥ ~CTEXT_EditorWindow				[public]
// ---------------------------------------------------------------------------

CTEXT_EditorWindow::~CTEXT_EditorWindow()
{
	this->RemoveTextMenus();
	
	// Remove the window from the list of listeners to the prefs object
	CRezillaApp::sPrefs->RemoveListener(this);
}


// ---------------------------------------------------------------------------
//		¥ FinishCreateSelf											[protected]
// ---------------------------------------------------------------------------

void
CTEXT_EditorWindow::FinishCreateSelf()
{	
	mHasStyleResource = false;
	mIsAdjustingMenus = false;
	
	// The main view containing the labels and editing panes
	mContentsView = dynamic_cast<CTEXT_EditorView *>(this->FindPaneByID(item_EditorContents));
	ThrowIfNil_( mContentsView );
	
	mContentsView->SetOwnerWindow(this);
	
	SwitchTarget(mContentsView);
	
	// The total length field
	mLengthField = dynamic_cast<LStaticText *> (this->FindPaneByID( item_TextEditLength ));
	ThrowIfNil_( mLengthField );
	
	// Link the broadcasters
	UReanimator::LinkListenerToControls( this, this, PPob_TextEditorWindow );
	
	// Make the window a listener to the prefs object
	CRezillaApp::sPrefs->AddListener(this);

}


// ---------------------------------------------------------------------------
// 	PutOnDuty
// ---------------------------------------------------------------------------

void
CTEXT_EditorWindow::PutOnDuty(LCommander *inNewTarget)
{
	LWindow::PutOnDuty(inNewTarget);

	// Put up our menus when on duty
	{
		if ( !sTextFontMenu )
		{
			sTextFontMenu = new LMenu( MENU_TextFonts );
			ThrowIfNil_( sTextFontMenu );

			MenuHandle	macH = sTextFontMenu->GetMacMenuH();
			if ( macH ) {
				::AppendResMenu( macH, 'FONT' );
			}
		}
		
		if ( !sTextSizeMenu )
		{
			sTextSizeMenu = new LMenu( MENU_TextSize );
			ThrowIfNil_( sTextSizeMenu );
		}
		
		if ( !sTextStyleMenu )
		{
			sTextStyleMenu = new LMenu( MENU_TextStyle );
			ThrowIfNil_( sTextStyleMenu );
		}
	}
	
	// Update the menu bar
	LMenuBar	*theBar = LMenuBar::GetCurrentMenuBar();
	theBar->InstallMenu( sTextFontMenu, MENU_OpenedWindows );	
	theBar->InstallMenu( sTextSizeMenu, MENU_OpenedWindows );
	theBar->InstallMenu( sTextStyleMenu, MENU_OpenedWindows );
}


// ---------------------------------------------------------------------------
// 	TakeOffDuty
// ---------------------------------------------------------------------------

void
CTEXT_EditorWindow::TakeOffDuty()
{		
	LWindow::TakeOffDuty();
	this->RemoveTextMenus();
}


// ---------------------------------------------------------------------------
// 	RemoveTextMenus
// ---------------------------------------------------------------------------

void
CTEXT_EditorWindow::RemoveTextMenus()
{
	LMenuBar	*theBar = LMenuBar::GetCurrentMenuBar();
	
	if ( sTextFontMenu )
		theBar->RemoveMenu( sTextFontMenu );
	
	if ( sTextSizeMenu )
		theBar->RemoveMenu( sTextSizeMenu );
		
	if ( sTextStyleMenu )
		theBar->RemoveMenu( sTextStyleMenu );
}


// ---------------------------------------------------------------------------
//		¥ ListenToMessage				[public]
// ---------------------------------------------------------------------------

void
CTEXT_EditorWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{	
	if (mIsAdjustingMenus) {
		return;
	} 
	
	switch (inMessage) {
		
		default:
		dynamic_cast<CTEXT_EditorDoc *>(mOwnerDoc)->ListenToMessage(inMessage, ioParam);
		break;
				
	}
}


// ---------------------------------------------------------------------------
//	¥ FindCommandStatus
// ---------------------------------------------------------------------------

void
CTEXT_EditorWindow::FindCommandStatus(
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
CTEXT_EditorWindow::ObeyCommand(
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
//	¥ InstallText													[public]
// ---------------------------------------------------------------------------

void
CTEXT_EditorWindow::InstallText(Handle inTextHandle, StScrpHandle inScrapHandle)
{
	StHandleLocker	lock(inTextHandle);
	mContentsView->SetTextHandle(inTextHandle, inScrapHandle);
	SetDirty(false);
}


// ---------------------------------------------------------------------------
//	¥ SetLengthField												[public]
// ---------------------------------------------------------------------------

void
CTEXT_EditorWindow::SetLengthField()
{
	Str255	theString;
	SInt32	theLength = ::GetHandleSize( ::TEGetText(mContentsView->GetMacTEH()) );
	::NumToString( theLength, theString);
	mLengthField->SetDescriptor(theString);
}


