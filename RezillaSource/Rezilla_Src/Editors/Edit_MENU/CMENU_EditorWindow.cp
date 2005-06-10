// ===========================================================================
// CMENU_EditorWindow.cp					
// 
//                       Created: 2005-03-09 17:16:53
//             Last modification: 2005-06-10 09:21:18
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
#include "CStaticEditCombo.h"
#include "CKeyboardGlyphBox.h"
#include "CMenuObject.h"
#include "CRezillaApp.h"
#include "CRezMapTable.h"
#include "CRezMap.h"
#include "CRezObj.h"
#include "CMenuItem.h"
#include "RezillaConstants.h"
#include "UMessageDialogs.h"
#include "UCompareUtils.h"

#include <LCheckBox.h>
#include <LEditText.h>
#include <LStaticText.h>
#include <LPopupButton.h>
#include <LTabGroupView.h>

#include <stdio.h>

// Statics
Str31	CMENU_EditorWindow::sMarkCharStr;
Str31	CMENU_EditorWindow::sSubmenuIDStr;
Str31	CMENU_EditorWindow::sIconIDStr;
Str31	CMENU_EditorWindow::sScriptCodeStr;


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
	if (mOutStream != nil) {
		delete mOutStream;
	} 
	if (mMenuObj != nil) {
		delete mMenuObj;
	} 
}


// ---------------------------------------------------------------------------
// FinishCreateSelf											[protected]
// ---------------------------------------------------------------------------

void
CMENU_EditorWindow::FinishCreateSelf()
{	
	mHasXmnu = false;
	mNeedsXmnu = false;
	mInstallValue = false;
	mMenuObj = nil;
	mOutStream = nil;
	
	// The main view containing the labels and editing panes
	mItemsTable = dynamic_cast<CMENU_EditorTable *>(this->FindPaneByID(item_EditorContents));
	ThrowIfNil_( mItemsTable );
	
	mItemsTable->SetOwnerWindow(this);
	
	// Add a single column.
	mItemsTable->InsertCols( 1, 0, nil );
	
	// Item's property popup
	mPopup = dynamic_cast<LPopupButton *>(this->FindPaneByID( item_MenuEditPropertyPopup ));
	ThrowIfNil_( mPopup );

	// Edit fields
	mItemTitleField = dynamic_cast<LEditText *>(this->FindPaneByID(item_MenuEditItemTitle));
	ThrowIfNil_( mItemTitleField );

	mIconIdField = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditIconID ));
	ThrowIfNil_( mIconIdField );
	
	mShortcutField = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditShortcut ));
	ThrowIfNil_( mShortcutField );

	mMarkCharField = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditMarkChar ));
	ThrowIfNil_( mMarkCharField );
	
	mTGV = dynamic_cast<LTabGroupView *>(this->FindPaneByID( item_MenuEditItemGroupVIew ));
	ThrowIfNil_( mTGV );

	mMarkCharLabel = dynamic_cast<LStaticText *>(this->FindPaneByID( item_MenuEditMarkChar + kMenuEditLabelOffset ));
	ThrowIfNil_( mMarkCharLabel );
	
	mIconIdLabel = dynamic_cast<LStaticText *>(this->FindPaneByID( item_MenuEditIconID + kMenuEditLabelOffset ));
	ThrowIfNil_( mIconIdLabel );

	// Link the broadcasters
	UReanimator::LinkListenerToControls( this, this, PPob_MenuEditorWindow );
	
	// Listen to the table
	mItemsTable->AddListener(this);
	TableCellT	theCell = {1,1};
	mItemsTable->SelectCell(theCell);
	
	// Listen to the item title field
	mItemTitleField->AddListener(this);

	// Listen to the glyph popup
	CPopupEditField * theEditField = dynamic_cast<CPopupEditField *>(this->FindPaneByID( item_MenuEditGlyphField ));
	ThrowIfNil_( theEditField );
	theEditField->GetPopup()->AddListener(this);
	
	// Editor fields labels. Load these once only.
	if ( sMarkCharStr[0] == 0 )
	{
		::GetIndString(sMarkCharStr, STRx_MenuEditorLabels, indx_MenuMarkChar);
		::GetIndString(sSubmenuIDStr, STRx_MenuEditorLabels, indx_MenuSubID);
		::GetIndString(sIconIDStr, STRx_MenuEditorLabels, indx_MenuIconID);
		::GetIndString(sScriptCodeStr, STRx_MenuEditorLabels, indx_MenuScriptCode);
	}

}


// ---------------------------------------------------------------------------
//  ListenToMessage													[public]
// ---------------------------------------------------------------------------

void
CMENU_EditorWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{	
	// If the message comes from one of the extended fields, an xmnu 
	// resource will be necessary
	if (!mNeedsXmnu && inMessage >= PPob_MenuEditorWindow + item_MenuEditCmdModifier
					&& inMessage <= PPob_MenuEditorWindow + item_MenuEditGlyphField) {
		mNeedsXmnu = true;
		SetDirty(true);
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
			SetDirty(true);
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
		SetDirty(true);
		break;
		
		
		case msg_MenuEditItemTitle: {
			Str255		theTitle;
			TableCellT	theCell;
			mItemTitleField->GetDescriptor(theTitle);
			mItemsTable->GetSelectedCell(theCell);
			mItemsTable->SetCellData( theCell, theTitle );
			mItemsTable->Refresh();
			SetDirty(true);
			break;
		}
				
		case msg_MinusButton: {
			ArrayIndexT theIndex = mMenuObj->GetItemIndex();
			mItemsTable->RemoveSelectedRow();
			mMenuObj->RemoveItem(theIndex);
			InstallCurrentValues();
			mItemsTable->Refresh();
			SetDirty(true);
			break;
		}
				
		case msg_PlusButton: {
			Str255		theString = "\p";
			TableCellT	theCell = {0,1};
			ArrayIndexT	theIndex = mMenuObj->GetItemIndex();
			// Add in the table
			mItemsTable->InsertRows(1, theIndex, theString);
			theCell.row = theIndex + 1;
			mItemsTable->SelectCell(theCell);
			// Add in the menu object
			mMenuObj->NewItem(theIndex);
			mMenuObj->SetItemIndex(theIndex + 1);
			ClearItemValues();
			mPopup->SetValue(kind_MenuNoProperty);
			mItemsTable->Refresh();
			SetDirty(true);
			break;
		}
				
		case msg_MenuEditPropertyPopup:  {
			HandlePropertyPopup( mPopup->GetValue() );
			break;
		}
				
		case msg_MenuEditStylePopup: {
			SInt32			i, itemIndex;
			UInt8			theStyle = 0;
			MenuRef			theMenuH;
			LPopupButton *	thePopup = dynamic_cast<LPopupButton *>(this->FindPaneByID( item_MenuEditStylePopup ));
			ThrowIfNil_(thePopup);
			itemIndex = thePopup->GetValue();
			theMenuH = thePopup->GetMacMenuH();
			if (itemIndex < 3) {
				return;
			} else if (itemIndex == 3) {
				::MacCheckMenuItem(theMenuH, 3, 1);
				for ( i = 0; i < 7; i++) {
					::MacCheckMenuItem(theMenuH, i + 4, 0 );
				}
			} else {
				CharParameter	markChar;
				::GetItemMark(theMenuH, itemIndex, &markChar);
				::MacCheckMenuItem(theMenuH, 3, 0);
				::MacCheckMenuItem(theMenuH, itemIndex, (markChar == 0) );
				for ( i = 0; i < 7; i++) {
					::GetItemMark( theMenuH, i+4, &markChar);
					theStyle |= (markChar == 0) ? 0:(1 << i);
				}
			}
			thePopup->SetValue(1);
			mMenuObj->SetStyleAtIndex(theStyle, mMenuObj->GetItemIndex());
			mItemsTable->Refresh();
			SetDirty(true);
			break;
		}
				
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
	
	if (mMenuObj->GetMDEF() != 0) {
		UMessageDialogs::AlertWithValue(CFSTR("MenuResourceDeclaresMDEF"), mMenuObj->GetMDEF());
		error = userCanceledErr;
	} 
	
	if (error == noErr) {
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
			UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("ParseXmnuRezFailed"), PPob_SimpleMessage);
		}
		
		InstallMenuValues();
		InstallCurrentValues();
		InstallTableValues();
		SwitchTarget(mItemsTable);
		SetDirty(false);
	} 

	return error;
}


// ---------------------------------------------------------------------------
//  CollectMenuData										[public]
// ---------------------------------------------------------------------------

Handle
CMENU_EditorWindow::CollectMenuData() 
{
	// Retrieve the contents of the current panel
	RetrieveMenuValues();
	RetrieveCurrentValues();
	
	// First deal with the extended data
	Boolean saveXmnu = mHasXmnu;
	
	if ( !mHasXmnu && mNeedsXmnu ) {
		SInt16 answer = UMessageDialogs::AskIfFromLocalizable(CFSTR("SaveXmnuData"), PPob_AskIfMessage);
		if (answer == answer_Do) {
			saveXmnu = true;
		}
	} 
	if (saveXmnu) {
		try {
			Handle xmnuHandle = NULL;
			
			if (mOutStream != nil) {delete mOutStream;} 
			
			mOutStream = new LHandleStream();	
			ThrowIfNil_(mOutStream);
			
			// First two words represent the version (should be 0) and the 
			// list count (OCNT)
			*mOutStream << (UInt16) 0;
			*mOutStream << (UInt16) mMenuObj->CountItems();
			
			TArrayIterator<CMenuItem*> iterator( *(mMenuObj->GetItems()) );
			CMenuItem *	theItem;
			
			while (iterator.Next(theItem)) {
				theItem->SendExtendedData(mOutStream);
			}
			
			xmnuHandle = mOutStream->GetDataHandle();
			dynamic_cast<CMENU_EditorDoc *>(mOwnerDoc)->SaveXmnuResource(xmnuHandle);
		}
		catch (...) {
			UMessageDialogs::AlertWithType(CFSTR("SavingResourceFailed"), ResType_ExtendedMenu);
		}
		mHasXmnu = true;
	} 

	// Now retrieve the main data
	Handle	menuHandle = NULL;

	try {
		if (mOutStream != nil) {delete mOutStream;} 

		mOutStream = new LHandleStream();	
		ThrowIfNil_(mOutStream);

		mMenuObj->SendData(mOutStream);
		menuHandle = mOutStream->GetDataHandle();
	}
	catch (...) {
// 		UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("SaveMenuRezFailed"), PPob_SimpleMessage);
	}
	
	return menuHandle;
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
	
	CStaticEditCombo * theCombo = dynamic_cast<CStaticEditCombo *>(this->FindPaneByID( item_MenuEditMenuTitle ));
	ThrowIfNil_( theCombo );
	theCombo->SetDescriptor(theString);

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
	
	InstallItemValues(theIndex);
}


// ---------------------------------------------------------------------------
//	 InstallItemValues
// ---------------------------------------------------------------------------
// If inAtIndex is 0, this proc sets all the item controls to default 
// values but does not modify the property popup. To set it to none, call 
// explicitly mPopup->SetValue(kind_MenuNoProperty).

void
CMENU_EditorWindow::InstallItemValues( ArrayIndexT inAtIndex )
{
	CMenuItem *		theItem;
	Str255			theString;
	UInt8			i, theIconID = 0, theShortcut = 0, theMark = 0, theStyle = 0, theMods = 0;
	SInt16			theFontID = 0, theGlyph = 0;
	SInt32			theEncoding = 0, theRefcon1 = 0, theRefcon2 = 0, theKind = 0;
	UInt32			theEnableFlag;
	MenuRef			theMenuH;
	LEditText * 	theEditText;
	LCheckBox *		theCheckBox;
	LPopupButton *	thePopup;
	Boolean			enableIt = false;
	
	if (inAtIndex == 0) {
		theString[0] = 0;
		mMenuObj->SetStyleAtIndex(0, mMenuObj->GetItemIndex());
	} else if (mMenuObj->GetItems()->FetchItemAt(inAtIndex, theItem)) {
		theItem->GetValues(theString, theIconID, theShortcut, theMark, theStyle);
	} else {
		return;
	}
	
	mItemTitleField->SetDescriptor(theString);
	
	if (theString[0] && theString[1] == '-') {
		theKind = kind_MenuIsSeparator;
	} 

	::NumToString(theIconID, theString);
	mIconIdField->SetDescriptor(theString);

	::NumToString(theShortcut, theString);
	mShortcutField->SetDescriptor(theString);

	::NumToString(theMark, theString);
	mMarkCharField->SetDescriptor(theString);

	theCheckBox = dynamic_cast<LCheckBox *>(this->FindPaneByID( item_MenuEditItemEnabled ));
	ThrowIfNil_( theCheckBox );
	theEnableFlag = mMenuObj->GetEnableFlag();
	// Bits 1Ð31 indicate if the corresponding menu item is disabled or
	// enabled, and bit 0 indicates whether the menu is enabled or
	// disabled. The Menu Manager automatically enables menu items
	// greater than 31 when a menu is created.
	if (inAtIndex != 0) {
		enableIt = (inAtIndex < 32) ? ( (theEnableFlag & (1 << inAtIndex)) > 0) : 1;
	}
	theCheckBox->SetValue(enableIt);
	
	// Style popup. 'Plain' is item 3.
	thePopup = dynamic_cast<LPopupButton *>(this->FindPaneByID( item_MenuEditStylePopup ));
	ThrowIfNil_(thePopup);
	theMenuH = thePopup->GetMacMenuH();
	if (theStyle == 0) {
		::MacCheckMenuItem(theMenuH, 3, 1 );
		for ( i = 0; i < 7; i++) {
			::MacCheckMenuItem(theMenuH, i + 4, 0 );
		}
	} else {
		::MacCheckMenuItem(theMenuH, 3, 0);
		for ( i = 0; i < 7; i++) {
			::MacCheckMenuItem(theMenuH, i + 4, ( (theStyle & (1 << i)) > 0 ) );
		}
	}
	
	// Extended data
	if (inAtIndex == 0) {
		theString[0] = 0;
	} else {
		theItem->GetExtendedValues(theMods, theEncoding,
								   theRefcon1, theRefcon2, 
								   theFontID, theGlyph);
	}
	
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
	InstallKeyboardGlyph(theGlyph);

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

	if (theShortcut == 0x1b) {
		theKind = kind_MenuHasSubmenu;
	} else if (theShortcut == 0x1c) {
		theKind = kind_MenuNonSystemScript;
	} else if (theShortcut == 0x1d) {
		theKind = kind_MenuUsesICON;
	} else if (theShortcut == 0x1e) {
		theKind = kind_MenuUsesSICN;
	} else if (theIconID != 0 && theShortcut == 0) {
		theKind = kind_MenuUsesCicn;
	} 
	
	if (theKind != 0) {
		mInstallValue = true;
		mPopup->SetValue(theKind);
		mInstallValue = false;
	} else if (inAtIndex != 0) {
		mPopup->SetValue(kind_MenuNoProperty);
	}
}


// ---------------------------------------------------------------------------
//	 RetrieveMenuValues
// ---------------------------------------------------------------------------

void
CMENU_EditorWindow::RetrieveMenuValues()
{
	Str255		titleStr, numStr;
	SInt32 		theLong;
	ResIDT		theID, theMDEF;
	UInt32		theEnableFlag;
	LEditText * theEditText;
	LCheckBox *	theCheckBox;
	
	CStaticEditCombo * theCombo = dynamic_cast<CStaticEditCombo *>(this->FindPaneByID( item_MenuEditMenuTitle ));
	ThrowIfNil_( theCombo );
	theCombo->GetDescriptor(titleStr);

	theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditMenuID ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(numStr);
	::StringToNum(numStr, &theLong);
	theID = theLong;

	theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditMDEF ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(numStr);
	::StringToNum(numStr, &theLong);
	theMDEF = theLong;

	theCheckBox = dynamic_cast<LCheckBox *>(this->FindPaneByID( item_MenuEditMenuEnabled ));
	ThrowIfNil_( theCheckBox );
	theEnableFlag = mMenuObj->GetEnableFlag();
	if (theCheckBox->GetValue()) {
		theEnableFlag |= (1 << 0);
	} else {
		theEnableFlag &= ~(1 << 0);
	}
	
	mMenuObj->SetValues( theID, theMDEF, theEnableFlag, titleStr);
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
		UInt8			theMods = 0;
		SInt32			theEncoding, theRefcon1, theRefcon2;
		SInt16			theFontID, theGlyph;
		
		if (inAtIndex == 0) {
			return;
		} 
		
		mItemTitleField->GetDescriptor(theTitle);

		mIconIdField->GetDescriptor(theString);
		::StringToNum(theString, &theLong);
		theIconID = theLong;
		
		mShortcutField->GetDescriptor(theString);
		::StringToNum(theString, &theLong);
		theShortcut = theLong;

		mMarkCharField->GetDescriptor(theString);
		::StringToNum(theString, &theLong);
		theMark = theLong;

		if (inAtIndex < 32) {
			theCheckBox = dynamic_cast<LCheckBox *>(this->FindPaneByID( item_MenuEditItemEnabled ));
			ThrowIfNil_( theCheckBox );
			theEnableFlag = mMenuObj->GetEnableFlag();
			// Bits 1Ð31 indicate if the corresponding menu item is disabled or enabled. 
			enableIt = theCheckBox->GetValue();
			if (enableIt) {
				theEnableFlag |= (1 << inAtIndex);
			} else {
				theEnableFlag &= ~(1 << inAtIndex);
			}
			mMenuObj->SetEnableFlag(theEnableFlag);
		} 
		
		// Style popup
		thePopup = dynamic_cast<LPopupButton *>(this->FindPaneByID( item_MenuEditStylePopup ));
		ThrowIfNil_(thePopup);
		theMenuH = thePopup->GetMacMenuH();
		::GetItemMark( theMenuH, 3, &markChar);
		if (markChar == 0) {
			for ( i = 0; i < 7; i++) {
				::GetItemMark( theMenuH, i+4, &markChar);
				theStyle |= (markChar == 0) ? 0:(1 << i);
			}
		} 
		
		theItem->SetValues(theTitle, theIconID, theShortcut, theMark, theStyle);

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
	InstallItemValues(0);
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


// ---------------------------------------------------------------------------
//	 HandlePropertyPopup
// ---------------------------------------------------------------------------

void
CMENU_EditorWindow::HandlePropertyPopup(SInt32 inIndex) 
{
	Str255			theString;

	HandleEnableState(kind_MenuAllEnabled);
		
	if (!mInstallValue) {

		switch (inIndex) {
			case kind_MenuIsSeparator:
			ClearItemValues();
			mItemTitleField->SetDescriptor("\p-");
			// This will update the table
			ListenToMessage(msg_MenuEditItemTitle, NULL);
			break;

			case kind_MenuHasSubmenu:
			// Empty and disable the IconID field.
			mIconIdField->SetDescriptor("\p");
			// The shortcut field receives the value $1B
			::NumToString(0x1b, theString);
			mShortcutField->SetDescriptor(theString);
			//  mMarkCharField->SetDescriptor("\p");
			SwitchTarget(mMarkCharField);
			break;

			case kind_MenuUsesCicn:
			mShortcutField->SetDescriptor("\p");
			SwitchTarget(mIconIdField);
			break;

			case kind_MenuUsesICON:
			::NumToString(0x1d, theString);
			mShortcutField->SetDescriptor(theString);
			SwitchTarget(mIconIdField);
			break;

			case kind_MenuUsesSICN:
			::NumToString(0x1e, theString);
			mShortcutField->SetDescriptor(theString);
			SwitchTarget(mIconIdField);
			break;

			case kind_MenuNonSystemScript:
			::NumToString(0x1c, theString);
			mShortcutField->SetDescriptor(theString);
			SwitchTarget(mIconIdField);
			break;
		}		
		
		SetDirty(true);
	} 

	HandleEnableState(inIndex);
	Refresh();
	
}


// ---------------------------------------------------------------------------
//	 HandleEnableState
// ---------------------------------------------------------------------------

void
CMENU_EditorWindow::HandleEnableState(SInt32 inIndex) 
{
	switch (inIndex) {
		case kind_MenuAllEnabled:
		mTGV->Enable();
		mShortcutField->Enable();
		mIconIdField->Enable();
		mMarkCharField->Enable();
		// Reset the labels
		if (inIndex != kind_MenuHasSubmenu) {
			mMarkCharLabel->SetDescriptor(sMarkCharStr);
		}
		if (inIndex != kind_MenuNonSystemScript) {
			mIconIdLabel->SetDescriptor(sIconIDStr);
		}
		break;

		case kind_MenuIsSeparator:
		mTGV->Disable();
		break;

		case kind_MenuHasSubmenu:
		mIconIdField->Disable();
		mShortcutField->Disable();
		// The marking char field is renamed and should specify the ID of the submenu
		mMarkCharLabel->SetDescriptor(sSubmenuIDStr);
		break;

		case kind_MenuUsesCicn:
		case kind_MenuUsesICON:
		case kind_MenuUsesSICN:
		mShortcutField->Disable();
		break;

		case kind_MenuNonSystemScript:
		mShortcutField->Disable();
		// The iconID field is renamed and should receive the code of the script
		mIconIdLabel->SetDescriptor(sScriptCodeStr);
		break;
	}		
	
}


// ---------------------------------------------------------------------------
//  RevertContents												  [public]
// ---------------------------------------------------------------------------

void
CMENU_EditorWindow::RevertContents()
{
	OSErr error = noErr;
	
	// Reinitialize members
	mNeedsXmnu = false;
	mInstallValue = false;
	if (mOutStream != nil) {
		delete mOutStream;
	} 
	if (mMenuObj != nil) {
		delete mMenuObj;
		mMenuObj = nil;
	} 

	// Remove the items from the table
	TableIndexT	theRows, theCols;
	mItemsTable->GetTableSize(theRows, theCols);
	mItemsTable->RemoveRows(theRows, 1);

	CRezObj * theRezObj = mOwnerDoc->GetRezObj();
	// Reinstall the contents
	if (theRezObj != nil) {
		Handle rezData = theRezObj->GetData();
		
		try {
			if (rezData != nil) {
				Handle		xmnuData = NULL;
				CRezMap *	theRezMap = mOwnerDoc->GetRezMapTable()->GetRezMap();
				
				if (mHasXmnu) {
					theRezMap->GetWithID(ResType_ExtendedMenu, theRezObj->GetID(), xmnuData, true);
					if (xmnuData != nil) {
						::HandToHand(&xmnuData);
					} 
				} 
				
				// Work with a copy of the handle
				::HandToHand(&rezData);
				error = InstallResourceData(rezData, xmnuData);			
			} 
			ThrowIfError_(error);			
		} catch (...) {
			UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("DataParsingException"), PPob_SimpleMessage);
			return;
		}
	} 
	
	Refresh();
	SetDirty(false);
}

