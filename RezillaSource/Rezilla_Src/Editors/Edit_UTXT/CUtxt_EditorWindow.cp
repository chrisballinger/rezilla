// ===========================================================================
// CUtxt_EditorWindow.cp					
// 
//                       Created: 2004-12-08 18:21:21
//             Last modification: 2004-12-09 23:10:30
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
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
#include <LPopupButton.h>
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

	// The size and style popups
	mSizePopup = dynamic_cast<LPopupButton *> (this->FindPaneByID( item_UtxtEditSizeMenu ));
	ThrowIfNil_( mSizePopup );

	mStylePopup = dynamic_cast<LPopupButton *> (this->FindPaneByID( item_UtxtEditStyleMenu ));
	ThrowIfNil_( mStylePopup );
	
	// The total length field
	mLengthField = dynamic_cast<LStaticText *> (this->FindPaneByID( item_UtxtEditLength ));
	ThrowIfNil_( mLengthField );
	
	// Link the broadcasters
	UReanimator::LinkListenerToControls( this, this, rRidL_TextEditorWindow );
	
	// Make the window a listener to the prefs object
	CRezillaApp::sPrefs->AddListener(this);

}


// ---------------------------------------------------------------------------
//		¥ ListenToMessage				[public]
// ---------------------------------------------------------------------------

void
CUtxt_EditorWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{	
	Str255			theString;
	SInt32 			theSize = 10, theIndex, theFace = 0;
	LStr255			theLine( "\p" );

	switch (inMessage) {
		case msg_UtxtEditFontMenu:
// 		// Get the name of the font.
// 		::GetMenuItemText( mFontPopup->GetMacMenuH(), mFontPopup->GetValue(), theString );
// 		mContentsView->SetFontName(theString);
		break;

		
		case msg_UtxtEditSizeMenu:
		// Get the value of the item.
		theIndex = mSizePopup->GetValue();
		::GetMenuItemText( mSizePopup->GetMacMenuH(), mSizePopup->GetValue(), theString );
		::StringToNum( theString, &theSize );
		mContentsView->SetFontSize(theSize);
		break;
		
		
		case msg_UtxtEditStyleMenu:
		// Get the values of all the items
		theIndex = mStylePopup->GetValue();
		mContentsView->ProcessCommand(cmd_Plain + theIndex - 2, NULL);
		break;
		
			
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
		case cmd_Plain:
			mContentsView->SetFontStyle(normal);
			for (UInt8 i = 0; i < 7; i++) {
				::MacCheckMenuItem(mStylePopup->GetMacMenuH(), i+3, 0);
			}
			break;
		
		case cmd_Bold:
		case cmd_Italic:
		case cmd_Underline: {
// 			Style theStyle;
// 			UInt8 i = inCommand - cmd_Plain - 1;
// 			mContentsView->GetStyle(theStyle);
// 			theStyle ^= (1 << i);
// 			mContentsView->SetFontStyle(theStyle);
// 			for (i = 0; i < 7; i++) {
// 				::MacCheckMenuItem(mStylePopup->GetMacMenuH(), i+3, theStyle & (1 << i));
// 			}
// 			::MacCheckMenuItem(mStylePopup->GetMacMenuH(), 2, (theStyle == 0));
			break;
		}

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


