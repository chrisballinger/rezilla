// ===========================================================================
// CHexEditorWindow.cp					
// 
//                       Created: 2004-03-02 14:18:16
//             Last modification: 2004-03-02 14:26:17
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#include "CCompResultWindow.h"
#include "CRezObj.h"
#include "CRezillaApp.h"
#include "CRezClipboard.h"
#include "CWindowMenu.h"
#include "RezillaConstants.h"
#include "UCodeTranslator.h"
#include "UMessageDialogs.h"

#include <LScrollBar.h>
#include <LStaticText.h>
#include <LUndoer.h>

// Global
extern CWindowMenu * gWindowMenu;


// ---------------------------------------------------------------------------
//		¥ CCompResultWindow				[public]
// ---------------------------------------------------------------------------

CCompResultWindow::CCompResultWindow()
{
}


// ---------------------------------------------------------------------------
//		¥ CCompResultWindow				[public]
// ---------------------------------------------------------------------------

CCompResultWindow::CCompResultWindow(
	const SWindowInfo &inWindowInfo )
		: LWindow( inWindowInfo )
{
}


// ---------------------------------------------------------------------------
//		¥ CCompResultWindow				[public]
// ---------------------------------------------------------------------------

CCompResultWindow::CCompResultWindow(
	ResIDT		inWINDid,
	UInt32		inAttributes,
	LCommander	*inSuperCommander )
		: LWindow( inWINDid, inAttributes, inSuperCommander )
{
}


// ---------------------------------------------------------------------------
//		¥ CCompResultWindow				[public]
// ---------------------------------------------------------------------------

CCompResultWindow::CCompResultWindow(
			       LStream *inStream )
		: LWindow( inStream )
{
}


// ---------------------------------------------------------------------------
//		¥ ~CCompResultWindow				[public]
// ---------------------------------------------------------------------------

CCompResultWindow::~CCompResultWindow()
{
	// Remove self from the window menu.
	gWindowMenu->RemoveWindow(this);
}


// ---------------------------------------------------------------------------
//		¥ FinishCreateSelf				[protected]
// ---------------------------------------------------------------------------

void
CCompResultWindow::FinishCreateSelf()
{	

// 	// Let the window listen to the text edit fields
// 	mLineField->AddListener(this);	
// 	mOffsetField->AddListener(this);	
// 	mScroller->AddListener(this);	
// 
// 	// Attach an LUndoer to each of the subpanes
// 	mHexDataWE->AddAttachment( new LUndoer );
// 	mTxtDataWE->AddAttachment( new LUndoer );

	// Add self to the window menu.
	gWindowMenu->InsertWindow(this);
}


// ---------------------------------------------------------------------------
//		¥ ListenToMessage				[public]
// ---------------------------------------------------------------------------

void
CCompResultWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{
	SInt32 theRangeStart, theRangeEnd;
	SInt32 lineStart, lineEnd;
	
	switch (inMessage) {
		
		case msg_Close:
		Hide();
		break;
		

// 		default:
// 		GetSuperCommander()->ListenToMessage(inMessage, ioParam);
// 		break;
				
	}
}


// ---------------------------------------------------------------------------
//	¥ FindCommandStatus
// ---------------------------------------------------------------------------
//	Pass back whether a Command is enabled and/or marked (in a Menu)

void
CCompResultWindow::FindCommandStatus(
	CommandT	inCommand,
	Boolean		&outEnabled,
	Boolean		&outUsesMark,
	UInt16		&outMark,
	Str255		outName)
{
	switch (inCommand) {

// 		case cmd_EditRez:
// 		case cmd_RemoveRez:
// 		case cmd_DuplicateRez:
// 		outEnabled = false;
// 			break;		
		
		default:
			LCommander::FindCommandStatus(inCommand, outEnabled,
									outUsesMark, outMark, outName);
			break;
	}
}


// ---------------------------------------------------------------------------
//	¥ ObeyCommand							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CCompResultWindow::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;

// 	CHexEditorDoc * theOwnerDoc = dynamic_cast<CHexEditorDoc *>( GetSuperCommander() );
// 	ThrowIfNil_(theOwnerDoc);
	
	switch (inCommand) {

		case cmd_Cut: {}

		case cmd_Paste: {}

		case cmd_Clear: {}

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
CCompResultWindow::DoClose()
{
	Hide();
}



// ---------------------------------------------------------------------------
//	¥ DisplayBothSelections											[protected]
// ---------------------------------------------------------------------------

void
CCompResultWindow::DisplayBothSelections(SInt32 inStart, SInt32 inEnd)
{
}


// ---------------------------------------------------------------------------
//	¥ IsDirty														[public]
// ---------------------------------------------------------------------------

Boolean
CCompResultWindow::IsDirty()
{
/* 	return (mHexDataWE->IsDirty() || mTxtDataWE->IsDirty()); */
    return true;
}

