// ===========================================================================
// CPICT_EditorWindow.cp					
// 
//                       Created: 2004-12-06 14:54:09
//             Last modification: 2004-12-06 23:25:36
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#include "CPICT_EditorDoc.h"
#include "CPICT_EditorWindow.h"
#include "CPICT_EditorView.h"
#include "CRezObj.h"
#include "CRezillaApp.h"
#include "CRezMapTable.h"
#include "CRezMap.h"
#include "CRezillaPrefs.h"
#include "RezillaConstants.h"
#include "UMiscUtils.h"
#include "UMessageDialogs.h"

#include <LScrollBar.h>
#include <LStaticText.h>
// #include <LEditText.h>
#include <LPicture.h>
#include <LScrollerView.h>
#include <UMemoryMgr.h>

#include <stdio.h>


// ---------------------------------------------------------------------------
//		¥ CPICT_EditorWindow				[public]
// ---------------------------------------------------------------------------

CPICT_EditorWindow::CPICT_EditorWindow()
{
}


// ---------------------------------------------------------------------------
//		¥ CPICT_EditorWindow				[public]
// ---------------------------------------------------------------------------

CPICT_EditorWindow::CPICT_EditorWindow(
	const SWindowInfo &inWindowInfo )
		: CEditorWindow( inWindowInfo )
{
}


// ---------------------------------------------------------------------------
//		¥ CPICT_EditorWindow				[public]
// ---------------------------------------------------------------------------

CPICT_EditorWindow::CPICT_EditorWindow(
	ResIDT		inWINDid,
	UInt32		inAttributes,
	LCommander	*inSuperCommander )
		: CEditorWindow( inWINDid, inAttributes, inSuperCommander )
{
}


// ---------------------------------------------------------------------------
//		¥ CPICT_EditorWindow				[public]
// ---------------------------------------------------------------------------

CPICT_EditorWindow::CPICT_EditorWindow(
			       LStream *inStream )
		: CEditorWindow( inStream )
{
}


// ---------------------------------------------------------------------------
//		¥ ~CPICT_EditorWindow				[public]
// ---------------------------------------------------------------------------

CPICT_EditorWindow::~CPICT_EditorWindow()
{
}


// ---------------------------------------------------------------------------
//		¥ FinishCreateSelf											[protected]
// ---------------------------------------------------------------------------

void
CPICT_EditorWindow::FinishCreateSelf()
{	
	// The main view containing the picture
	mContentsView = dynamic_cast<CPICT_EditorView *>(this->FindPaneByID(item_EditorContents));
	ThrowIfNil_( mContentsView );
	
	mContentsView->SetOwnerWindow(this);
	
// 	// Link the broadcasters
// 	UReanimator::LinkListenerToControls( this, this, rRidL_TextEditorWindow );
}


// ---------------------------------------------------------------------------
//		¥ ListenToMessage				[public]
// ---------------------------------------------------------------------------

void
CPICT_EditorWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{	

	switch (inMessage) {
			
		default:
		dynamic_cast<CPICT_EditorDoc *>(mOwnerDoc)->ListenToMessage(inMessage, ioParam);
		break;
				
	}
}


// ---------------------------------------------------------------------------
//	¥ FindCommandStatus
// ---------------------------------------------------------------------------

void
CPICT_EditorWindow::FindCommandStatus(
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
CPICT_EditorWindow::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;
	
	switch (inCommand) {
		case cmd_Cut: {
				break;
			}
		
			case cmd_Copy: {
				break;
			}

			case cmd_Paste: {
				break;
			}

		default:
			cmdHandled = LCommander::ObeyCommand(inCommand, ioParam);
			break;
	}

	return cmdHandled;
}


// ---------------------------------------------------------------------------
//	¥ InstallPict													[public]
// ---------------------------------------------------------------------------

void
CPICT_EditorWindow::InstallPict(Handle inPictHandle)
{
	StHandleLocker	lock(inPictHandle);
	mContentsView->SetPictureH( (PicHandle) inPictHandle);
	SetDirty(false);
}


// ---------------------------------------------------------------------------
//	¥ SetSizeFields												[public]
// ---------------------------------------------------------------------------

void
CPICT_EditorWindow::SetSizeFields(Rect inRect)
{
	LStaticText * theStaticText;
	Str255	theString;

	// The picture dimensions
	theStaticText = dynamic_cast<LStaticText *> (this->FindPaneByID( item_PictEditWidth ));
	ThrowIfNil_( theStaticText );
	::NumToString( inRect.right - inRect.left, theString);
	theStaticText->SetDescriptor(theString);

	theStaticText = dynamic_cast<LStaticText *> (this->FindPaneByID( item_PictEditHeight ));
	ThrowIfNil_( theStaticText );
	::NumToString( inRect.bottom - inRect.top, theString);
	theStaticText->SetDescriptor(theString);
	
}


