// ===========================================================================
// CMENU_EditorWindow.cp					
// 
//                       Created: 2005-03-09 17:16:53
//             Last modification: 2005-03-17 09:33:40
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
#include "CPopupEditField.h"
#include "CKeyboardGlyphBox.h"
#include "CMenuObject.h"
#include "CRezillaApp.h"
#include "CMenuItem.h"
#include "RezillaConstants.h"
#include "UMessageDialogs.h"
#include "UCompareUtils.h"

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
	mNeedsXmnu = false;

	// The main view containing the labels and editing panes
	mItemsTable = dynamic_cast<CMENU_EditorTable *>(this->FindPaneByID(item_EditorContents));
	ThrowIfNil_( mItemsTable );
	
	mItemsTable->SetOwnerWindow(this);
	
	// Add a single column.
	mItemsTable->InsertCols( 1, 0, nil );
			
	// Link the broadcasters
	UReanimator::LinkListenerToControls( this, this, PPob_MenuEditorWindow );
	
	// Listen to the table
	mItemsTable->AddListener(this);
	TableCellT	theCell = {1,1};
	mItemsTable->SelectCell(theCell);
	
	// Listen to the glyph popup
	CPopupEditField * theEditText = dynamic_cast<CPopupEditField *>(this->FindPaneByID( item_MenuEditGlyphField ));
	ThrowIfNil_( theEditText );
	theEditText->GetPopup()->AddListener(this);
	
}


// ---------------------------------------------------------------------------
//  ListenToMessage				[public]
// ---------------------------------------------------------------------------

void
CMENU_EditorWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{	
	// If the message comes from one of the extended fields, an xmnu 
	// resource will be necessary
	if (!mNeedsXmnu && inMessage >= PPob_MenuEditorWindow + item_MenuEditCmdModifier
					&& inMessage <= PPob_MenuEditorWindow + item_MenuEditGlyphField) {
		mNeedsXmnu = true;
	} 
	
	switch (inMessage) {
		case msg_MenuEditGlyphPopup: {
			Str255		theString;
			SInt32 		theValue = 0;
			
			LEditText * theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(item_MenuEditGlyphField));
			ThrowIfNil_( theEditText );
			theEditText->GetDescriptor(theString);
			::StringToNum( theString, &theValue);
			InstallKeyboardGlyph( (UInt8) theValue);
			break;
		}
		
				
		case msg_MenuEditGlyphField: 
		if (ioParam == NULL) {
			InstallKeyboardGlyph(0);
		} else {
			ListenToMessage(msg_MenuEditGlyphPopup, ioParam);
		}
		break;
			
		
		case msg_MenuTableClicked: {
			TableCellT theCell;
			ArrayIndexT theIndex = mMenuObj->GetItemIndex();
		
			mItemsTable->GetSelectedCell(theCell);
			if (theCell.row != theIndex) {
				RetrieveItemValues(theIndex);
				InstallItemValues(theCell.row);
				mMenuObj->SetItemIndex(theCell.row);
			} 
			break;
		}
		
		
		case msg_DragMoveAction: 
		ArrayIndexT	oldIndex = mMenuObj->GetItemIndex();
		ArrayIndexT	newIndex = *(ArrayIndexT *) ioParam;
		mMenuObj->GetItems()->MoveItem(oldIndex, newIndex);
		mMenuObj->SetItemIndex(newIndex);
		break;
		
		
		case msg_MenuEditItemTitle: {
			LEditText *	theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(item_MenuEditItemTitle));
			Str255		theTitle;
			TableCellT	theCell;
			theEditText->GetDescriptor(theTitle);
			mItemsTable->GetSelectedCell(theCell);
			mItemsTable->SetCellData( theCell, theTitle );
			break;
		}
				
		case msg_MinusButton: {
			ArrayIndexT theIndex = mMenuObj->GetItemIndex();
			mItemsTable->RemoveSelectedRow();
			mMenuObj->RemoveItem(theIndex);
			break;
		}
				
		case msg_PlusButton: 
		break;
				
		case msg_MenuEditPropertyPopup: 
		break;
				
		case msg_MenuEditStylePopup: 
		break;
				
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
//	 InstallResourceData											[public]
// ---------------------------------------------------------------------------

OSErr
CMENU_EditorWindow::InstallResourceData(Handle inMenuHandle, Handle inXmnuHandle)
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
			UInt16 theVal;
			
			mHasXmnu = true;
			mNeedsXmnu = true;
			
			StHandleLocker	xmnulock(inXmnuHandle);
			theStream = new LHandleStream(inXmnuHandle);
			
			// First two words represent the version (should be 0) and the 
			// list count (OCNT)
			*theStream >> theVal;
			*theStream >> theVal;
			
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
		InstallCurrentValues();
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
//	 InstallCurrentValues
// ---------------------------------------------------------------------------

void
CMENU_EditorWindow::InstallCurrentValues()
{
	ArrayIndexT theIndex = mMenuObj->GetItemIndex();
	
	if (theIndex == 0) {
		ClearItemValues();
	} else {
		InstallItemValues(theIndex);
	}
}


// ---------------------------------------------------------------------------
//	 InstallItemValues
// ---------------------------------------------------------------------------
//   normal       = 0,
//   bold         = 1,
//   italic       = 2,
//   underline    = 4,
//   outline      = 8,
//   shadow       = 0x10,
//   condense     = 0x20,
//   extend       = 0x40

void
CMENU_EditorWindow::InstallItemValues( ArrayIndexT inAtIndex )
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
		::NumToString(theIconID, theString);
		theEditText->SetDescriptor(theString);

		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditShortcut ));
		ThrowIfNil_( theEditText );
		::NumToString(theShortcut, theString);
		theEditText->SetDescriptor(theString);

		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditMarkChar ));
		ThrowIfNil_( theEditText );
		::NumToString(theMark, theString);
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
		thePopup = dynamic_cast<LPopupButton *>(this->FindPaneByID( item_MenuEditStylePopup ));
		ThrowIfNil_(thePopup);
		theMenuH = thePopup->GetMacMenuH();
		if (theStyle == 0) {
			::MacCheckMenuItem(theMenuH, 2, 1 );
			for ( i = 0; i < 7; i++) {
				::MacCheckMenuItem(theMenuH, i + 3, 0 );
			}
		} else {
			::MacCheckMenuItem(theMenuH, 2, 0);
			for ( i = 0; i < 7; i++) {
				::MacCheckMenuItem(theMenuH, i + 3, ( (theStyle & (1 << i)) > 0 ) );
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
			::NumToString(theEncoding, theString);
			theEditText->SetDescriptor(theString);

			theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditRefcon1 ));
			ThrowIfNil_( theEditText );
			::NumToString(theRefcon1, theString);
			theEditText->SetDescriptor(theString);

			theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditRefcon2 ));
			ThrowIfNil_( theEditText );
			::NumToString(theRefcon2, theString);
			theEditText->SetDescriptor(theString);

			theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditFontID ));
			ThrowIfNil_( theEditText );
			::NumToString(theFontID, theString);
			theEditText->SetDescriptor(theString);

			theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditGlyphField ));
			ThrowIfNil_( theEditText );
			::NumToString(theGlyph, theString);
			theEditText->SetDescriptor(theString);

			// Modifiers. If bit 3 is on, it means that command key is _not_ used.
			theCheckBox = dynamic_cast<LCheckBox *>(this->FindPaneByID( item_MenuEditCmdModifier ));
			ThrowIfNil_( theCheckBox );
			theCheckBox->SetValue( ((theMods & 8) == 0) );
			enableIt = ((theMods & 8) == 0);
			
			theCheckBox = dynamic_cast<LCheckBox *>(this->FindPaneByID( item_MenuEditCtrlModifier ));
			ThrowIfNil_( theCheckBox );
			theCheckBox->SetValue( ((theMods & 4) > 0) );
			enableIt = ((theMods & 4) > 0);

			theCheckBox = dynamic_cast<LCheckBox *>(this->FindPaneByID( item_MenuEditOptModifier ));
			ThrowIfNil_( theCheckBox );
			theCheckBox->SetValue( ((theMods & 2) > 0) );
			enableIt = ((theMods & 2) > 0);

			theCheckBox = dynamic_cast<LCheckBox *>(this->FindPaneByID( item_MenuEditShiftModifier ));
			ThrowIfNil_( theCheckBox );
			theCheckBox->SetValue( ((theMods & 1) > 0) );	
			enableIt = ((theMods & 1) > 0);
		
		} 
	} 
}


// ---------------------------------------------------------------------------
//	 RetrieveCurrentValues
// ---------------------------------------------------------------------------

void
CMENU_EditorWindow::RetrieveCurrentValues()
{
	ArrayIndexT theIndex = mMenuObj->GetItemIndex();
	
	if (theIndex != LArray::index_Bad) {
		RetrieveItemValues(theIndex);
	}
}


// ---------------------------------------------------------------------------
//	 RetrieveItemValues
// ---------------------------------------------------------------------------

void
CMENU_EditorWindow::RetrieveItemValues( ArrayIndexT inAtIndex )
{
	CMenuItem * theItem;
	if (mMenuObj->GetItems()->FetchItemAt(inAtIndex, theItem)) {
		Str255			theString, theTitle;
		UInt8			i, theIconID, theShortcut, theMark, theStyle = 0;
		SInt32 			theLong;
		UInt32			theEnableFlag;
		CharParameter	markChar;
		MenuRef			theMenuH;
		LEditText * 	theEditText;
		LCheckBox *		theCheckBox;
		LPopupButton *	thePopup;
		Boolean			enableIt;
		
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditItemTitle ));
		ThrowIfNil_( theEditText );
		theEditText->GetDescriptor(theTitle);

		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditIconID ));
		ThrowIfNil_( theEditText );
		theEditText->GetDescriptor(theString);
		::StringToNum(theString, &theLong);
		theIconID = theLong;
		
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditShortcut ));
		ThrowIfNil_( theEditText );
		theEditText->GetDescriptor(theString);
		::StringToNum(theString, &theLong);
		theShortcut = theLong;

		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditMarkChar ));
		ThrowIfNil_( theEditText );
		theEditText->GetDescriptor(theString);
		::StringToNum(theString, &theLong);
		theMark = theLong;

		if (inAtIndex < 32) {
			theCheckBox = dynamic_cast<LCheckBox *>(this->FindPaneByID( item_MenuEditItemEnabled ));
			ThrowIfNil_( theCheckBox );
			theEnableFlag = mMenuObj->GetEnableFlag();
			// Bits 1Ð31 indicate if the corresponding menu item is disabled or enabled. 
			enableIt = theCheckBox->GetValue();
			if (enableIt) {
				theEnableFlag |=  (1 << inAtIndex);
			} else {
				theEnableFlag ^=  (1 << inAtIndex);
			}
		} 
		
		// Style popup
		thePopup = dynamic_cast<LPopupButton *>(this->FindPaneByID( item_MenuEditStylePopup ));
		ThrowIfNil_(thePopup);
		theMenuH = thePopup->GetMacMenuH();
		::GetItemMark( theMenuH, 2, &markChar);
		if (markChar == 0) {
			for ( i = 0; i < 7; i++) {
				::GetItemMark( theMenuH, i+3, &markChar);
				theStyle |= (markChar == 0) ? 0:(1 << i);
			}
		} 
		
		theItem->SetValues(theTitle, theIconID, theShortcut, theMark, theStyle);

		if (mHasXmnu) {
			UInt8	theMods = 0;
			SInt32	theEncoding, theRefcon1, theRefcon2;
			SInt16	theFontID, theGlyph;
			
			theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditEncoding ));
			ThrowIfNil_( theEditText );
			theEditText->GetDescriptor(theString);
			::StringToNum(theString, &theEncoding);

			theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditRefcon1 ));
			ThrowIfNil_( theEditText );
			theEditText->GetDescriptor(theString);
			::StringToNum(theString, &theRefcon1);

			theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditRefcon2 ));
			ThrowIfNil_( theEditText );
			theEditText->GetDescriptor(theString);
			::StringToNum(theString, &theRefcon2);

			theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditFontID ));
			ThrowIfNil_( theEditText );
			theEditText->GetDescriptor(theString);
			::StringToNum(theString, &theLong);
			theFontID = theLong;

			theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditGlyphField ));
			ThrowIfNil_( theEditText );
			theEditText->GetDescriptor(theString);
			::StringToNum(theString, &theLong);
			theGlyph = theLong;

			// Modifiers. If bit 3 is on, it means that command key is _not_ used.
			theCheckBox = dynamic_cast<LCheckBox *>(this->FindPaneByID( item_MenuEditCmdModifier ));
			ThrowIfNil_( theCheckBox );
			theMods |= theCheckBox->GetValue() ? 0:8 ;

			theCheckBox = dynamic_cast<LCheckBox *>(this->FindPaneByID( item_MenuEditCtrlModifier ));
			ThrowIfNil_( theCheckBox );
			theMods |= theCheckBox->GetValue() ? 4:0 ;

			theCheckBox = dynamic_cast<LCheckBox *>(this->FindPaneByID( item_MenuEditOptModifier ));
			ThrowIfNil_( theCheckBox );
			theMods |= theCheckBox->GetValue() ? 2:0;

			theCheckBox = dynamic_cast<LCheckBox *>(this->FindPaneByID( item_MenuEditShiftModifier ));
			ThrowIfNil_( theCheckBox );
			theMods |= theCheckBox->GetValue() ? 1:0;
			
			theItem->SetExtendedValues(theMods, theEncoding,
									   theRefcon1, theRefcon2, 
									   theFontID, theGlyph);
			
		} 
	} 
}


// ---------------------------------------------------------------------------
//	 InstallKeyboardGlyph
// ---------------------------------------------------------------------------

void
CMENU_EditorWindow::InstallKeyboardGlyph(UInt8 inValue)
{
	Str255		theString;
	
	CKeyboardGlyphBox * theGlyphBox = dynamic_cast<CKeyboardGlyphBox *>(this->FindPaneByID(item_MenuEditGlyphBox));
	ThrowIfNil_( theGlyphBox );
	theString[0] = 1;
	theString[1] = inValue;
	theGlyphBox->SetString(theString);
	theGlyphBox->Draw(nil);		
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
	SInt32	i = 1, theCount = mMenuObj->CountItems();
	TableCellT	theCell;
	Str255	theString;

	theCell.col = 1;
	
	// Add rows for the items.
	mItemsTable->InsertRows( theCount, 0, nil );
	
	TArrayIterator<CMenuItem*> iterator( *(mMenuObj->GetItems()) );
	CMenuItem *	theItem;
	
	while (iterator.Next(theItem)) {
		theItem->GetTitle(theString);
		
		// Set the cell data.
		theCell.row = i++;
		mItemsTable->SetCellData( theCell, theString );
	}
}


