// ===========================================================================
// CIcon_EditorWindow.cp
// 
//                       Created: 2004-12-10 17:23:05
//             Last modification: 2004-12-10 17:23:10
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#include "CIcon_EditorDoc.h"
#include "CIcon_EditorWindow.h"
#include "CIcon_EditorView.h"
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
#include <LPopupButton.h>
#include <LScrollerView.h>
#include <UMemoryMgr.h>

#include <stdio.h>


// ---------------------------------------------------------------------------
//		¥ CIcon_EditorWindow				[public]
// ---------------------------------------------------------------------------

CIcon_EditorWindow::CIcon_EditorWindow()
{
}


// ---------------------------------------------------------------------------
//		¥ CIcon_EditorWindow				[public]
// ---------------------------------------------------------------------------

CIcon_EditorWindow::CIcon_EditorWindow(
	const SWindowInfo &inWindowInfo )
		: CEditorWindow( inWindowInfo )
{
}


// ---------------------------------------------------------------------------
//		¥ CIcon_EditorWindow				[public]
// ---------------------------------------------------------------------------

CIcon_EditorWindow::CIcon_EditorWindow(
	ResIDT		inWINDid,
	UInt32		inAttributes,
	LCommander	*inSuperCommander )
		: CEditorWindow( inWINDid, inAttributes, inSuperCommander )
{
}


// ---------------------------------------------------------------------------
//		¥ CIcon_EditorWindow				[public]
// ---------------------------------------------------------------------------

CIcon_EditorWindow::CIcon_EditorWindow(
			       LStream *inStream )
		: CEditorWindow( inStream )
{
}


// ---------------------------------------------------------------------------
//		¥ ~CIcon_EditorWindow				[public]
// ---------------------------------------------------------------------------

CIcon_EditorWindow::~CIcon_EditorWindow()
{
	// Remove the window from the list of listeners to the prefs object
	CRezillaApp::sPrefs->RemoveListener(this);
}


// ---------------------------------------------------------------------------
//		¥ FinishCreateSelf											[protected]
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::FinishCreateSelf()
{	
	
	// The main view containing the labels and editing panes
	mContentsView = dynamic_cast<CIcon_EditorView *>(this->FindPaneByID(item_EditorContents));
	ThrowIfNil_( mContentsView );
	
	mContentsView->SetOwnerWindow(this);
	
	// Should 'this' be a LCommander ?
// 	SwitchTarget(mContentsView);

// 	// The font, size and style popups
// 	mFontPopup = dynamic_cast<LPopupButton *> (this->FindPaneByID( item_TextEditFontMenu ));
// 	ThrowIfNil_( mFontPopup );
// 
// 	mSizePopup = dynamic_cast<LPopupButton *> (this->FindPaneByID( item_TextEditSizeMenu ));
// 	ThrowIfNil_( mSizePopup );
// 
// 	mStylePopup = dynamic_cast<LPopupButton *> (this->FindPaneByID( item_TextEditStyleMenu ));
// 	ThrowIfNil_( mStylePopup );
	
	// The total length field
	mCoordsField = dynamic_cast<LStaticText *> (this->FindPaneByID( item_IconEditCoords ));
	ThrowIfNil_( mCoordsField );
	
	// Link the broadcasters
	UReanimator::LinkListenerToControls( this, this, rPPob_IconEditorWindow );
	
	// Make the window a listener to the prefs object
	CRezillaApp::sPrefs->AddListener(this);

}


// ---------------------------------------------------------------------------
//		¥ ListenToMessage				[public]
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{	
	Str255			theString;
	SInt16			theFontNum;
	SInt32 			theSize = 10, theIndex, theFace = 0;
	LStr255			theLine( "\p" );

	
	switch (inMessage) {
		case msg_TextEditFontMenu:
		break;

		
		case msg_TextEditSizeMenu:
		break;
		
		
		case msg_TextEditStyleMenu:
		break;

		
		default:
		dynamic_cast<CIcon_EditorDoc *>(mOwnerDoc)->ListenToMessage(inMessage, ioParam);
		break;
				
	}
}


// ---------------------------------------------------------------------------
//	¥ FindCommandStatus
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::FindCommandStatus(
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
CIcon_EditorWindow::ObeyCommand(
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
//	¥ InstallBitmap													[public]
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::InstallBitmap(Handle inHandle)
{
	StHandleLocker	lock(inHandle);
// 	mContentsView->SetBitmapHandle(inHandle);
	SetDirty(false);
}


// ---------------------------------------------------------------------------
//	¥ SetCoordsField												[public]
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::SetCoordsField(SInt16 inXCoord, SInt16 inYCoord)
{
}


