// ===========================================================================
// CMENU_EditorWindow.cp					
// 
//                       Created: 2005-03-09 17:16:53
//             Last modification: 2005-03-11 22:17:36
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
#include "CMenuObject.h"
#include "CRezillaApp.h"
#include "CMenuItem.h"
#include "RezillaConstants.h"
#include "UMessageDialogs.h"

#include <LCheckBox.h>
#include <LEditText.h>
#include <LPopupButton.h>
// #include <LScrollerView.h>
// #include <UMemoryMgr.h>

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
	mHasXmnu = false;

	// The main view containing the labels and editing panes
	mItemsTable = dynamic_cast<CMENU_EditorTable *>(this->FindPaneByID(item_EditorContents));
	ThrowIfNil_( mItemsTable );
	
	mItemsTable->SetOwnerWindow(this);
	
// 	SwitchTarget(mItemsTable);
		
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
//	 FindCommandStatus
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
//	 ObeyCommand							[public, virtual]
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
//	 InstallMenuData													[public]
// ---------------------------------------------------------------------------

OSErr
CMENU_EditorWindow::InstallMenuData(Handle inMenuHandle, Handle inXmnuHandle)
{
	OSErr		error = noErr, ignoreErr = noErr;
	StHandleLocker	menulock(inMenuHandle);

	LHandleStream * theStream = new LHandleStream(inMenuHandle);
	
	if ( theStream->GetLength() == 0 ) {
		// We are creating a new resource
		mMenuObj = new CMenuObject();
	} else {
		mMenuObj = new CMenuObject(theStream);
	}
	
	// Check that all the data have been parsed
	if (theStream->GetMarker() < theStream->GetLength() ) {
		error = err_MoreDataThanExpected;
	} 
	delete theStream;
	theStream = nil;
	
	try {
		if (inXmnuHandle != nil) {
			mHasXmnu = true;
			
			StHandleLocker	xmnulock(inXmnuHandle);
			theStream = new LHandleStream(inXmnuHandle);
			
			TArrayIterator<CMenuItem*> iterator( *(mMenuObj->GetItems()) );
			CMenuItem *	theItem;
			
			while (iterator.Next(theItem)) {
				ignoreErr = theItem->InstallExtendedData(theStream);
			}
			
			delete theStream;
		} 	
	}
	catch (...) {
		if (theStream != nil) {delete theStream;} 
		if (ignoreErr) {
			// todo
		} 
		UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("ParseXmnuRezFailed"), PPob_SimpleMessage);
	}
	
	
	if (error == noErr) {
		InstallMenuValues();
		InstallCurrentItemValues();
		InstallTableValues();
		SetDirty(false);
	} 

	return error;
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


// ---------------------------------------------------------------------------
//	 InstallMenuValues
// ---------------------------------------------------------------------------

void
CMENU_EditorWindow::InstallMenuValues()
{
	Str255		theString;
	ResIDT		theID, theMDEF;
	UInt32		theEnableFlag;
	LEditText * theEditText;
	LCheckBox *	theCheckBox;
	
	mMenuObj->GetValues( theID, theMDEF, theEnableFlag, theString);
	
	theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditMenuTitle ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditMenuID ));
	ThrowIfNil_( theEditText );
	::NumToString( theID, theString);
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditMDEF ));
	ThrowIfNil_( theEditText );
	::NumToString( theMDEF, theString);
	theEditText->SetDescriptor(theString);

	theCheckBox = dynamic_cast<LCheckBox *>(this->FindPaneByID( item_MenuEditMenuEnabled ));
	ThrowIfNil_( theCheckBox );
	theCheckBox->SetValue( (theEnableFlag & 1) );

}


// ---------------------------------------------------------------------------
//	 InstallCurrentItemValues
// ---------------------------------------------------------------------------

void
CMENU_EditorWindow::InstallCurrentItemValues()
{
	ArrayIndexT theIndex = mMenuObj->GetItemIndex();
	
	if (theIndex == 0) {
		ClearItemValues();
	} else {
		InstallItemValuesAtIndex(theIndex);
	}
}


// ---------------------------------------------------------------------------
//	 InstallItemValuesAtIndex
// ---------------------------------------------------------------------------

void
CMENU_EditorWindow::InstallItemValuesAtIndex( ArrayIndexT inAtIndex )
{
	CMenuItem * theItem;
	if (mMenuObj->GetItems()->FetchItemAt(inAtIndex, theItem)) {
		Str255			theString;
		UInt8			i, theIconID, theShortcut, theMark, theStyle;
		UInt32			theEnableFlag;
		MenuRef			theMenuH;
		LEditText * 	theEditText;
		LCheckBox *		theCheckBox;
		LPopupButton *	thePopup;
		Boolean			enableIt;

		theItem->GetValues(theString, theIconID, theShortcut, theMark, theStyle);
		
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditItemTitle ));
		ThrowIfNil_( theEditText );
		theEditText->SetDescriptor(theString);

		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditIconID ));
		ThrowIfNil_( theEditText );
		::NumToString( theIconID, theString);
		theEditText->SetDescriptor(theString);

		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditShortcut ));
		ThrowIfNil_( theEditText );
		::NumToString( theShortcut, theString);
		theEditText->SetDescriptor(theString);

		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditMarkChar ));
		ThrowIfNil_( theEditText );
		::NumToString( theMark, theString);
		theEditText->SetDescriptor(theString);

		theCheckBox = dynamic_cast<LCheckBox *>(this->FindPaneByID( item_MenuEditItemEnabled ));
		ThrowIfNil_( theCheckBox );
		theEnableFlag = mMenuObj->GetEnableFlag();
		// Bits 1Ð31 indicate if the corresponding menu item is disabled or
		// enabled, and bit 0 indicates whether the menu is enabled or
		// disabled. The Menu Manager automatically enables menu items
		// greater than 31 when a menu is created.
		enableIt = (inAtIndex < 32) ? ( (theEnableFlag & (1 << inAtIndex)) > 0) : 1;
		theCheckBox->SetValue(enableIt);
		
		// Style popup
//   normal       = 0,
//   bold         = 1,
//   italic       = 2,
//   underline    = 4,
//   outline      = 8,
//   shadow       = 0x10,
//   condense     = 0x20,
//   extend       = 0x40

		thePopup = dynamic_cast<LPopupButton *>(this->FindPaneByID( item_MenuEditStylePopup ));
		ThrowIfNil_(thePopup);
		theMenuH = thePopup->GetMacMenuH();
		if (theStyle == 0) {
			::MacCheckMenuItem(theMenuH, 2, 1 );
			for ( i = 0; i < 7; i++) {
				::MacCheckMenuItem(theMenuH, i + 2, 0 );
			}
		} else {
			::MacCheckMenuItem(theMenuH, 2, 0);
			for ( i = 0; i < 7; i++) {
				::MacCheckMenuItem(theMenuH, i + 2, ( (theStyle & (1 << i)) > 0 ) );
			}
		}
		
		if (mHasXmnu) {
			UInt8	theMods;
			SInt32	theEncoding, theRefcon1, theRefcon2;
			SInt16	theFontID, theGlyph;
			
			theItem->GetExtendedValues(theMods, theEncoding,
									   theRefcon1, theRefcon2, 
									   theFontID, theGlyph);
			
			theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditEncoding ));
			ThrowIfNil_( theEditText );
			::NumToString( theEncoding, theString);
			theEditText->SetDescriptor(theString);

			theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditRefcon1 ));
			ThrowIfNil_( theEditText );
			::NumToString( theRefcon1, theString);
			theEditText->SetDescriptor(theString);

			theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditRefcon2 ));
			ThrowIfNil_( theEditText );
			::NumToString( theRefcon2, theString);
			theEditText->SetDescriptor(theString);

			theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditFontID ));
			ThrowIfNil_( theEditText );
			::NumToString( theFontID, theString);
			theEditText->SetDescriptor(theString);

			theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditGlyph ));
			ThrowIfNil_( theEditText );
			::NumToString( theGlyph, theString);
			theEditText->SetDescriptor(theString);

			// Modifiers. If bit 3 is on, it means that command key is _not_ used.
			theCheckBox = dynamic_cast<LCheckBox *>(this->FindPaneByID( item_MenuEditCmdModifier ));
			ThrowIfNil_( theCheckBox );
			theCheckBox->SetValue( ((theMods & 8) == 0) );

			theCheckBox = dynamic_cast<LCheckBox *>(this->FindPaneByID( item_MenuEditCtrlModifier ));
			ThrowIfNil_( theCheckBox );
			theCheckBox->SetValue( ((theMods & 4) > 0) );

			theCheckBox = dynamic_cast<LCheckBox *>(this->FindPaneByID( item_MenuEditOptModifier ));
			ThrowIfNil_( theCheckBox );
			theCheckBox->SetValue( ((theMods & 2) > 0) );

			theCheckBox = dynamic_cast<LCheckBox *>(this->FindPaneByID( item_MenuEditShiftModifier ));
			ThrowIfNil_( theCheckBox );
			theCheckBox->SetValue( ((theMods & 1) > 0) );	
			
		} 
	} 
}


// ---------------------------------------------------------------------------
//	 ClearItemValues
// ---------------------------------------------------------------------------

void
CMENU_EditorWindow::ClearItemValues()
{
}


// ---------------------------------------------------------------------------
//	 InstallTableValues
// ---------------------------------------------------------------------------

void
CMENU_EditorWindow::InstallTableValues()
{
}



