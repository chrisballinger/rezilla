// ===========================================================================
// CTEXT_EditorWindow.cp					
// 
//                       Created: 2004-06-17 12:46:55
//             Last modification: 2004-06-20 10:00:06
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#include "CTEXT_EditorDoc.h"
#include "CTEXT_EditorWindow.h"
#include "CTEXT_EditorView.h"
#include "CRezEditor.h"
#include "CRezObj.h"
#include "CRezillaApp.h"
#include "CRezMapTable.h"
#include "CRezMap.h"
#include "CRezillaPrefs.h"
#include "CDualDataView.h"
#include "CHexDataSubView.h"
#include "CSingleScrollBar.h"
#include "CTxtDataSubView.h"
#include "CWasteEditView.h"
#include "RezillaConstants.h"
#include "UMiscUtils.h"
#include "UMessageDialogs.h"
#include "UHexFilters.h"
#include "UCodeTranslator.h"

#include <LScrollBar.h>
#include <LStaticText.h>
#include <LIconPane.h>
#include <LEditText.h>
#include <LPopupButton.h>
#include <LScrollerView.h>
#include <UMemoryMgr.h>

#include <stdio.h>


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
	
	// The font, size and style popups
	mFontPopup = dynamic_cast<LPopupButton *> (this->FindPaneByID( item_TextEditFontMenu ));
	ThrowIfNil_( mFontPopup );

	mSizePopup = dynamic_cast<LPopupButton *> (this->FindPaneByID( item_TextEditSizeMenu ));
	ThrowIfNil_( mSizePopup );

	mStylePopup = dynamic_cast<LPopupButton *> (this->FindPaneByID( item_TextEditStyleMenu ));
	ThrowIfNil_( mStylePopup );
	
	// The total length field
	mLengthField = dynamic_cast<LStaticText *> (this->FindPaneByID( item_TextEditLength ));
	ThrowIfNil_( mLengthField );
	
	// Link the broadcasters
	UReanimator::LinkListenerToControls( this, this, rRidL_TextEditorWindow );
	
	// Make the window a listener to the prefs object
	CRezillaApp::sPrefs->AddListener(this);

}
// SetItemMark(
//   MenuRef         theMenu,
//   short           item,
//   CharParameter   markChar)

// SetItemMark(curr->menu, i, '¥');
// // CharParameter markChar = 0;
// // GetItemMark(mr, i, &markChar);


// ---------------------------------------------------------------------------
//		¥ InstallDefaults											[public]
// ---------------------------------------------------------------------------

void
CTEXT_EditorWindow::InstallDefaults()
{
	// Retrieve the default font and size
	TextTraitsRecord theTraits = CRezillaApp::sPrefs->GetStyleElement( CRezillaPrefs::prefsType_Curr );
	
	UTextTraits::SetTETextTraits(&theTraits, mContentsView->GetMacTEH());

	// Set the style elements
// 	mContentsView->SelectAll();
// 	mContentsView->SetFont(theTraits.fontNumber);
// 	mContentsView->SetSize(theTraits.size);
// 	mContentsView->SetSelectionRange(0,0);
	
	// Install preference values in the popups
	mFontPopup->SetValue( UMiscUtils::FontIndexFromFontNum(mFontPopup, theTraits.fontNumber) );
	mSizePopup->SetValue( UMiscUtils::SizeIndexFromSizeValue(mSizePopup, theTraits.size) );
	
	// Check the 'plain' style item
	::MacCheckMenuItem(mStylePopup->GetMacMenuH(), 2, 1);
}
 


// ---------------------------------------------------------------------------
//		¥ ListenToMessage				[public]
// ---------------------------------------------------------------------------
// 		  normal                        = 0,
// 		  bold                          = 1,
// 		  italic                        = 2,
// 		  underline                     = 4,
// 		  outline                       = 8,
// 		  shadow                        = 0x10,
// 		  condense                      = 0x20,
// 		  extend                        = 0x40

void
CTEXT_EditorWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{	
	Str255			theString;
	SInt16			theFontNum;
	SInt32 			theSize = 10, theIndex, theFace = 0;
	LStr255			theLine( "\p" );

	if (mIsAdjustingMenus) {
		return;
	} 
	
	switch (inMessage) {
		case msg_TextEditFontMenu:
		// Get the name of the font.
		::GetMenuItemText( mFontPopup->GetMacMenuH(), mFontPopup->GetValue(), theString );
		::GetFNum(theString, &theFontNum);
		mContentsView->SetFont(theFontNum);
		break;

		
		case msg_TextEditSizeMenu:
		// Get the value of the item.
		theIndex = mSizePopup->GetValue();
		if (theIndex == kLastSizeMenuItem + 2) {
			// This is the 'Other' item
			if (UModalDialogs::AskForOneNumber(this, rPPob_OtherSize, item_OtherSizeField, theSize)) {
				if (theSize == 0) {theSize = 10;}
				// If they match, no need to use 'Other' item
				if (UMiscUtils::FontSizeExists(mSizePopup, theSize, theIndex)) {
					mSizePopup->SetValue(theIndex);
					::SetMenuItemText( mSizePopup->GetMacMenuH(), kLastSizeMenuItem + 2, LStr255("\pOtherÉ"));					
				} else {
					// Modify the text of the 'Other' item.
					Str255	theSizeString;
					theLine = "\pOther (" ;
					::NumToString( theSize, theSizeString );
					// Append the current size
					theLine += theSizeString;
					theLine += "\p)É";
					// Set the menu item text.
					::SetMenuItemText( mSizePopup->GetMacMenuH(), kLastSizeMenuItem + 2, theLine );					
				}
			}
		} else {
			::GetMenuItemText( mSizePopup->GetMacMenuH(), mSizePopup->GetValue(), theString );
			::StringToNum( theString, &theSize );
			::SetMenuItemText( mSizePopup->GetMacMenuH(), kLastSizeMenuItem + 2, LStr255("\pOtherÉ"));					
		}
		mContentsView->SetSize(theSize);
		break;
		
		
		case msg_TextEditStyleMenu:
		// Get the values of all the items
		theIndex = mStylePopup->GetValue();
		mContentsView->ProcessCommand(cmd_Plain + theIndex - 2, NULL);
		break;
		
			
		default:
		dynamic_cast<CTEXT_EditorDoc *>(GetSuperCommander())->ListenToMessage(inMessage, ioParam);
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
		
		case cmd_EditRez:
		case cmd_TmplEditRez:
		case cmd_HexEditRez:
		case cmd_RemoveRez:
		case cmd_DuplicateRez:
		outEnabled = false;
		break;		
		
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
		case cmd_Plain:
			mContentsView->SetStyle(normal);
			for (UInt8 i = 0; i < 7; i++) {
				::MacCheckMenuItem(mStylePopup->GetMacMenuH(), i+3, 0);
			}
			break;
		
		case cmd_Bold:
		case cmd_Italic:
		case cmd_Underline:
		case cmd_Outline:
		case cmd_Shadow:
		case cmd_Condense:
		case cmd_Extend: {
			Style theStyle;
			UInt8 i = inCommand - cmd_Plain - 1;
			mContentsView->GetStyle(theStyle);
			theStyle ^= (1 << i);
			mContentsView->SetStyle(theStyle);
			for (i = 0; i < 7; i++) {
				::MacCheckMenuItem(mStylePopup->GetMacMenuH(), i+3, theStyle & (1 << i));
			}
			::MacCheckMenuItem(mStylePopup->GetMacMenuH(), 2, (theStyle == 0));
			break;
		}

		default:
			cmdHandled = LCommander::ObeyCommand(inCommand, ioParam);
			break;
	}

	return cmdHandled;
}


// ---------------------------------------------------------------------------
//  ¥ InstallReadOnlyIcon											[public]
// ---------------------------------------------------------------------------

void
CTEXT_EditorWindow::InstallReadOnlyIcon() 
{
	LIconPane * theIcon = dynamic_cast<LIconPane *>(this->FindPaneByID( item_ReadOnlyIcon ));
	ThrowIfNil_( theIcon );
	if (mOwnerDoc->IsReadOnly()) {
		theIcon->SetIconID(ics8_Locked);
	} else {
		theIcon->SetIconID(ics8_Unlocked);
	}
}


// ---------------------------------------------------------------------------
//	¥ IsDirty														[public]
// ---------------------------------------------------------------------------

Boolean
CTEXT_EditorWindow::IsDirty()
{
	return mContentsView->IsDirty();
}


// ---------------------------------------------------------------------------
//	¥ InstallText														[public]
// ---------------------------------------------------------------------------

void
CTEXT_EditorWindow::InstallText(Handle inTextHandle, StScrpHandle inScrapHandle)
{
	StHandleLocker	lock(inTextHandle);
	mContentsView->Insert(*inTextHandle, ::GetHandleSize(inTextHandle), inScrapHandle, true);
	mContentsView->SetDirty(false);
}


// ---------------------------------------------------------------------------
//	¥ AdjustMenusToSelection										[public]
// ---------------------------------------------------------------------------

// LPane::GetUserCon()

void
CTEXT_EditorWindow::AdjustMenusToSelection()
{
	SInt16	theFontNum, theSize;
	SInt32	theIndex;
	UInt8	i;
	Style	theStyle;
	Boolean	result;
	LStr255	theLine( "\p" );
	SInt16	theStart = (**(mContentsView->GetMacTEH())).selStart;
	SInt16	theEnd   = (**(mContentsView->GetMacTEH())).selEnd;
	
	mIsAdjustingMenus = true;
	
	result = mContentsView->GetFont(theFontNum);
	if (result) {
		theIndex = UMiscUtils::FontIndexFromFontNum(mFontPopup, theFontNum);
		mFontPopup->SetValue(theIndex);
// 		::MacCheckMenuItem(mFontPopup->GetMacMenuH(), theIndex, 1);
	}
	
	result = mContentsView->GetSize(theSize);
	if (result) {
		theIndex = UMiscUtils::SizeIndexFromSizeValue(mSizePopup, theSize);
		if (theIndex == kLastSizeMenuItem + 2) {
			// This is the 'Other' item
			Str255	theSizeString;
			theLine = "\pOther (" ;
			::NumToString( theSize, theSizeString );
			// Append the current size
			theLine += theSizeString;
			theLine += "\p)É";
			// Set the menu item text.
			::SetMenuItemText( mSizePopup->GetMacMenuH(), kLastSizeMenuItem + 2, theLine );					
		} else {
			::SetMenuItemText( mSizePopup->GetMacMenuH(), kLastSizeMenuItem + 2, LStr255("\pOtherÉ"));					
		}
		mSizePopup->SetValue(theIndex);
// 		::MacCheckMenuItem(mSizePopup->GetMacMenuH(), theIndex, 1);
	}
	
	result = mContentsView->GetStyle(theStyle);
	if (result) {
		for (i = 0; i < 7; i++) {
			::MacCheckMenuItem(mStylePopup->GetMacMenuH(), i+3, theStyle & (1 << i));
		}
		::MacCheckMenuItem(mStylePopup->GetMacMenuH(), 2, (theStyle == 0));
	} else {
		// Not a continuous style. Uncheck all items.
		for (i = 0; i < 7; i++) {
			::MacCheckMenuItem(mStylePopup->GetMacMenuH(), i+3, 0);
		}
		::MacCheckMenuItem(mStylePopup->GetMacMenuH(), 2, 0);
	}
	
	mStylePopup->SetValue(1);

	mIsAdjustingMenus = false;
}


// ---------------------------------------------------------------------------
//	¥ ReadValues													[public]
// ---------------------------------------------------------------------------

// LPane::GetUserCon()

Handle
CTEXT_EditorWindow::ReadValues()
{
	Handle theHandle = nil;
	
	
	return theHandle;
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


