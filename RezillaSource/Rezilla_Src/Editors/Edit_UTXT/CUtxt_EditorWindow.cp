// ===========================================================================
// CUtxt_EditorWindow.cp					
// 
//                       Created: 2004-12-08 18:21:21
//             Last modification: 2005-01-08 21:49:00
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#include "CUtxt_EditorDoc.h"
#include "CUtxt_EditorWindow.h"
#include "CUtxt_EditorView.h"
#include "CRezillaApp.h"
#include "CRezillaPrefs.h"
#include "CRezObj.h"
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
//		¥ CUtxt_EditorWindow				[public]
// ---------------------------------------------------------------------------

CUtxt_EditorWindow::CUtxt_EditorWindow()
{
}


// ---------------------------------------------------------------------------
//		¥ CUtxt_EditorWindow				[public]
// ---------------------------------------------------------------------------

CUtxt_EditorWindow::CUtxt_EditorWindow(
	const SWindowInfo &inWindowInfo )
		: CEditorWindow( inWindowInfo )
{
}


// ---------------------------------------------------------------------------
//		¥ CUtxt_EditorWindow										[public]
// ---------------------------------------------------------------------------

CUtxt_EditorWindow::CUtxt_EditorWindow(
	ResIDT		inWINDid,
	UInt32		inAttributes,
	LCommander	*inSuperCommander )
		: CEditorWindow( inWINDid, inAttributes, inSuperCommander )
{
}


// ---------------------------------------------------------------------------
//		¥ CUtxt_EditorWindow										[public]
// ---------------------------------------------------------------------------

CUtxt_EditorWindow::CUtxt_EditorWindow(
			       LStream *inStream )
		: CEditorWindow( inStream )
{
}


// ---------------------------------------------------------------------------
//		¥ ~CUtxt_EditorWindow										[public]
// ---------------------------------------------------------------------------

CUtxt_EditorWindow::~CUtxt_EditorWindow()
{
	// Remove the window from the list of listeners to the prefs object
	CRezillaApp::sPrefs->RemoveListener(this);
}


// ---------------------------------------------------------------------------
//		¥ FinishCreateSelf											[protected]
// ---------------------------------------------------------------------------

void
CUtxt_EditorWindow::FinishCreateSelf()
{		
	// The main view containing the labels and editing panes
	mContentsView = dynamic_cast<CUtxt_EditorView *>(this->FindPaneByID(item_EditorContents));
	ThrowIfNil_( mContentsView );
	
	mContentsView->SetOwnerWindow(this);
	
	SwitchTarget(mContentsView);

// 	// The size and style popups
// 	mSizePopup = dynamic_cast<LPopupButton *> (this->FindPaneByID( item_UtxtEditSizeMenu ));
// 	ThrowIfNil_( mSizePopup );
// 
// 	mStylePopup = dynamic_cast<LPopupButton *> (this->FindPaneByID( item_UtxtEditStyleMenu ));
// 	ThrowIfNil_( mStylePopup );
// 	
	// The total length field
	mLengthField = dynamic_cast<LStaticText *> (this->FindPaneByID( item_UtxtEditLength ));
	ThrowIfNil_( mLengthField );
	
	// Link the broadcasters
	UReanimator::LinkListenerToControls(this, this, PPob_UtxtEditorWindow );
	
	// Make the window a listener to the prefs object
	CRezillaApp::sPrefs->AddListener(this);

}


// // ---------------------------------------------------------------------------
// // 	PutOnDuty
// // ---------------------------------------------------------------------------
// 
// void
// CUtxt_EditorWindow::PutOnDuty(LCommander *inNewTarget)
// {
// 	LWindow::PutOnDuty(inNewTarget);
// 
// 	// Put up our menus when on duty
// 	{
// 		if (LMLTEPane::sTXNFontMenuObject != NULL) {
// 			OSStatus 	status;
// 			MenuHandle	fontMenuH;
// 			
// 			status = ::TXNPrepareFontMenu(mTXNObject, sTXNFontMenuObject );
// 			status = ::TXNGetFontMenuHandle(sTXNFontMenuObject, &fontMenuH);
// 		
// 		} 
// 		
// 		if ( !sUtxtSizeMenu )
// 		{
// 			sUtxtSizeMenu = new LMenu( MENU_UnicodeSize );
// 			ThrowIfNil_( sUtxtSizeMenu );
// 		}
// 		
// 		if ( !sUtxtStyleMenu )
// 		{
// 			sUtxtStyleMenu = new LMenu( MENU_UnicodeStyle );
// 			ThrowIfNil_( sUtxtStyleMenu );
// 		}
// 	}
// 	
// 	// Update the menu bar
// 	LMenuBar	*theBar = LMenuBar::GetCurrentMenuBar();
// // 	theBar->InstallMenu( sUtxtFontMenu, MENU_OpenedWindows );	
// 	theBar->InstallMenu( sUtxtSizeMenu, MENU_OpenedWindows );
// 	theBar->InstallMenu( sUtxtStyleMenu, MENU_OpenedWindows );
// 	::MacInsertMenu(fontMenuH, MENU_OpenedWindows);
// }
// 
// 
// // ---------------------------------------------------------------------------
// // 	TakeOffDuty
// // ---------------------------------------------------------------------------
// 
// void
// CUtxt_EditorWindow::TakeOffDuty()
// {		
// 	LWindow::TakeOffDuty();
// 	this->RemoveTextMenus();
// }
// 
// 
// // ---------------------------------------------------------------------------
// // 	RemoveTextMenus
// // ---------------------------------------------------------------------------
// 
// void
// CUtxt_EditorWindow::RemoveTextMenus()
// {
// 	LMenuBar	*theBar = LMenuBar::GetCurrentMenuBar();
// 	
// // 	if ( sTextFontMenu )
// // 		theBar->RemoveMenu( sUtxtFontMenu );
// 	
// 	// 	::MacDeleteMenu(MENU_UnicodeFonts);
// 	// 	// Force redraw of MenuBar
// 	// 	::InvalMenuBar();
// 
// 	if ( sUtxtSizeMenu )
// 		theBar->RemoveMenu( sUtxtSizeMenu );
// 		
// 	if ( sUtxtStyleMenu )
// 		theBar->RemoveMenu( sUtxtStyleMenu );
// }
// 
// 
// ---------------------------------------------------------------------------
//		¥ ListenToMessage				[public]
// ---------------------------------------------------------------------------

void
CUtxt_EditorWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{	
	switch (inMessage) {
// 		case msg_UtxtEditSizeMenu:
// 		// Get the value of the item.
// 		theIndex = mSizePopup->GetValue();
// 		::GetMenuItemText( mSizePopup->GetMacMenuH(), mSizePopup->GetValue(), theString );
// 		::StringToNum( theString, &theSize );
// 		mContentsView->SetFontSize(theSize);
// 		break;
// 		
// 		case msg_UtxtEditStyleMenu:
// 		// Get the values of all the items
// 		theIndex = mStylePopup->GetValue();
// 		ObeyCommand(cmd_Plain + theIndex - 2, NULL);
// 		break;
			
		default:
		dynamic_cast<CUtxt_EditorDoc *>(mOwnerDoc)->ListenToMessage(inMessage, ioParam);
		break;
				
	}
}


// ---------------------------------------------------------------------------
//	¥ FindCommandStatus
// ---------------------------------------------------------------------------

void
CUtxt_EditorWindow::FindCommandStatus(
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
CUtxt_EditorWindow::ObeyCommand(
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
CUtxt_EditorWindow::InstallText(Handle inTextHandle)
{
	StHandleLocker	lock(inTextHandle);
	mContentsView->SetTextPtr(*inTextHandle, ::GetHandleSize(inTextHandle));
	SetDirty(false);
}


// ---------------------------------------------------------------------------
//	¥ SetLengthField												[public]
// ---------------------------------------------------------------------------

void
CUtxt_EditorWindow::SetLengthField()
{
	Str255	theString;
	Size	theLength = 0;
	Handle	dataH  = nil;
	OSStatus status = ::TXNGetDataEncoded(mContentsView->GetTextObject(),
												 kTXNStartOffset, kTXNEndOffset,
												 &dataH, kTXNUnicodeTextData);
	
	if (status == noErr  &&  dataH != nil) {
		theLength = (Size) (::GetHandleSize(dataH) / sizeof(UniChar));
		::DisposeHandle(dataH);
	}

	::NumToString( theLength, theString);
	mLengthField->SetDescriptor(theString);
}


