// ===========================================================================
// CEditorWindow.cp
// 
//                       Created: 2004-06-10 14:50:31
//             Last modification: 2004-08-10 12:20:06
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#include "CEditorWindow.h"
#include "CEditorDoc.h"
#include "RezillaConstants.h"


// ---------------------------------------------------------------------------
//		¥ CEditorWindow				[public]
// ---------------------------------------------------------------------------

CEditorWindow::CEditorWindow()
{
}


// ---------------------------------------------------------------------------
//		¥ CEditorWindow				[public]
// ---------------------------------------------------------------------------

CEditorWindow::CEditorWindow(
	const SWindowInfo &inWindowInfo )
		: LWindow( inWindowInfo )
{
}


// ---------------------------------------------------------------------------
//		¥ CEditorWindow				[public]
// ---------------------------------------------------------------------------

CEditorWindow::CEditorWindow(
	ResIDT		inWINDid,
	UInt32		inAttributes,
	LCommander	*inSuperCommander )
		: LWindow( inWINDid, inAttributes, inSuperCommander )
{
}


// ---------------------------------------------------------------------------
//		¥ CEditorWindow				[public]
// ---------------------------------------------------------------------------

CEditorWindow::CEditorWindow(
			       LStream *inStream )
		: LWindow( inStream )
{
}


// ---------------------------------------------------------------------------
//		¥ ~CEditorWindow				[public]
// ---------------------------------------------------------------------------

CEditorWindow::~CEditorWindow()
{
}


// ---------------------------------------------------------------------------
//		¥ FinishCreateSelf				[protected]
// ---------------------------------------------------------------------------

void
CEditorWindow::FinishCreateSelf()
{}
	

// ---------------------------------------------------------------------------
//		¥ ListenToMessage				[public]
// ---------------------------------------------------------------------------

void
CEditorWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{
	
	switch (inMessage) {
		
		case msg_Close:
		Hide();
		break;
				
		default:
		dynamic_cast<CEditorDoc *>(GetSuperCommander())->ListenToMessage(inMessage, ioParam);
		break;
				
	}
}


// ---------------------------------------------------------------------------
//	¥ FindCommandStatus
// ---------------------------------------------------------------------------
//	Pass back whether a Command is enabled and/or marked (in a Menu)

void
CEditorWindow::FindCommandStatus(
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
		if (mOwnerDoc) {
			mOwnerDoc->FindCommandStatus(inCommand, outEnabled,
												outUsesMark, outMark, outName);
		} 
		break;
	}
}


// ---------------------------------------------------------------------------
//	¥ ObeyCommand							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CEditorWindow::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;

	switch (inCommand) {

		case cmd_Copy: 
		case cmd_Cut: {

			break;
		}

		case cmd_Clear: {

			break;
		}

		case cmd_Paste: {
			
			break;
		}

		case cmd_ActionCut:
		case cmd_ActionPaste:
		case cmd_ActionClear:
		case cmd_ActionTyping: {
			break;
		}

		default:
			cmdHandled = LCommander::ObeyCommand(inCommand, ioParam);
			break;
	}

	return cmdHandled;
}


// ---------------------------------------------------------------------------
//	¥ DoClose
// ---------------------------------------------------------------------------
//	Close the inspector window: hide it but keep it in memory

void
CEditorWindow::DoClose()
{
	Hide();
}


// ---------------------------------------------------------------------------
//  ¥ InstallReadOnlyIcon											[public]
// ---------------------------------------------------------------------------

void
CEditorWindow::InstallReadOnlyIcon() 
{
// 	LIconPane * theIcon = dynamic_cast<LIconPane *>(this->FindPaneByID( item_ReadOnlyIcon ));
// 	ThrowIfNil_( theIcon );
// 	if (mOwnerDoc->IsReadOnly()) {
// 		theIcon->SetIconID(ics8_Locked);
// 	} else {
// 		theIcon->SetIconID(ics8_Unlocked);
// 	}
}


// ---------------------------------------------------------------------------
//	¥ IsDirty														[public]
// ---------------------------------------------------------------------------

Boolean
CEditorWindow::IsDirty()
{
	return false;
}


