// ===========================================================================
// CTEXT_EditorWindow.cp					
// 
//                       Created: 2004-06-17 12:46:55
//             Last modification: 2005-01-08 17:16:54
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
	
	// Install the name of the resource if it has one
	LStaticText * theStaticText = dynamic_cast<LStaticText *>(this->FindPaneByID( item_NameStaticText ));
	ThrowIfNil_( theStaticText );
	Str255 * strPtr = dynamic_cast<CTEXT_EditorDoc *>(GetSuperCommander())->GetRezObj()->GetName();
	theStaticText->SetDescriptor(*strPtr);	
	
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
	Str255			theString;
	SInt16			theFontNum;
	SInt32 			theSize = 10, theIndex, theFace = 0;
	LStr255			theLine( "\p" );

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
//	¥ AdjustMenusToSelection										[public]
// ---------------------------------------------------------------------------

// LPane::GetUserCon()

void
CTEXT_EditorWindow::AdjustMenusToSelection()
{
// 	SInt16	theFontNum, theSize;
// 	SInt32	theIndex;
// 	UInt8	i;
// 	Style	theStyle;
// 	Boolean	result;
// 	LStr255	theLine( "\p" );
// 	SInt16	theStart = (**(mContentsView->GetMacTEH())).selStart;
// 	SInt16	theEnd   = (**(mContentsView->GetMacTEH())).selEnd;
// 	
// 	mIsAdjustingMenus = true;
// 	
// 	result = mContentsView->GetFont(theFontNum);
// 	if (result) {
// 		theIndex = UMiscUtils::FontIndexFromFontNum(mFontPopup, theFontNum);
// 		mFontPopup->SetValue(theIndex);
// // 		::MacCheckMenuItem(mFontPopup->GetMacMenuH(), theIndex, 1);
// 	}
// 	
// 	result = mContentsView->GetSize(theSize);
// 	if (result) {
// 		theIndex = UMiscUtils::SizeIndexFromSizeValue(mSizePopup, theSize);
// 		if (theIndex == kLastSizeMenuItem + 2) {
// 			// This is the 'Other' item
// 			Str255	theSizeString;
// 			theLine = "\pOther (" ;
// 			::NumToString( theSize, theSizeString );
// 			// Append the current size
// 			theLine += theSizeString;
// 			theLine += "\p)É";
// 			// Set the menu item text.
// 			::SetMenuItemText( mSizePopup->GetMacMenuH(), kLastSizeMenuItem + 2, theLine );					
// 		} else {
// 			::SetMenuItemText( mSizePopup->GetMacMenuH(), kLastSizeMenuItem + 2, LStr255("\pOtherÉ"));					
// 		}
// 		mSizePopup->SetValue(theIndex);
// // 		::MacCheckMenuItem(mSizePopup->GetMacMenuH(), theIndex, 1);
// 	}
// 	
// 	result = mContentsView->GetStyle(theStyle);
// 	if (result) {
// 		for (i = 0; i < 7; i++) {
// 			::MacCheckMenuItem(mStylePopup->GetMacMenuH(), i+3, theStyle & (1 << i));
// 		}
// 		::MacCheckMenuItem(mStylePopup->GetMacMenuH(), 2, (theStyle == 0));
// 	} else {
// 		// Not a continuous style. Uncheck all items.
// 		for (i = 0; i < 7; i++) {
// 			::MacCheckMenuItem(mStylePopup->GetMacMenuH(), i+3, 0);
// 		}
// 		::MacCheckMenuItem(mStylePopup->GetMacMenuH(), 2, 0);
// 	}
// 	
// 	mStylePopup->SetValue(1);
// 
// 	mIsAdjustingMenus = false;
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


