// ===========================================================================
// CEditorWindow.cp
// 
//                       Created: 2004-06-10 14:50:31
//             Last modification: 2005-04-10 08:23:32
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#include "CEditorWindow.h"
#include "CEditorDoc.h"
#include "CRezObj.h"
#include "RezillaConstants.h"

#include <LIconPane.h>
#include <LStaticText.h>

// ---------------------------------------------------------------------------
//		¥ CEditorWindow				[public]
// ---------------------------------------------------------------------------

CEditorWindow::CEditorWindow()
{
	mIsDirty = false;
	SetModelKind(rzom_cEditorWindow);
}


// ---------------------------------------------------------------------------
//		¥ CEditorWindow				[public]
// ---------------------------------------------------------------------------

CEditorWindow::CEditorWindow(
	const SWindowInfo &inWindowInfo )
		: LWindow( inWindowInfo )
{
	mIsDirty = false;
	SetModelKind(rzom_cEditorWindow);
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
	mIsDirty = false;
	SetModelKind(rzom_cEditorWindow);
}


// ---------------------------------------------------------------------------
//		¥ CEditorWindow				[public]
// ---------------------------------------------------------------------------

CEditorWindow::CEditorWindow(
			       LStream *inStream )
		: LWindow( inStream )
{
	mIsDirty = false;
	SetModelKind(rzom_cEditorWindow);
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
{
 	InstallResourceNameField();
	InstallReadOnlyIcon();
}
	

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
		case cmd_EditRezAsType:
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
		} else {
			LCommander::FindCommandStatus(inCommand, outEnabled,
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
// 		cmdHandled = LCommander::ObeyCommand(inCommand, ioParam);
		cmdHandled = mOwnerDoc->ObeyCommand(inCommand, ioParam);
		break;
	}

	return cmdHandled;
}


// ---------------------------------------------------------------------------
//	¥ RevertContents												  [public]
// ---------------------------------------------------------------------------
// Override in subclasses to redraw the contents view with the last saved 
// data.

void
CEditorWindow::RevertContents()
{
	SetDirty(false);
}


// ---------------------------------------------------------------------------
//  ¥ InstallReadOnlyIcon											[public]
// ---------------------------------------------------------------------------

void
CEditorWindow::InstallReadOnlyIcon() 
{
	LIconPane * theIcon = dynamic_cast<LIconPane *>(this->FindPaneByID( item_ReadOnlyIcon ));
	if (theIcon != NULL) {
		if (mOwnerDoc->IsReadOnly()) {
			theIcon->SetIconID(ics8_Locked);
		} else {
			theIcon->SetIconID(ics8_Unlocked);
		}
	} 
}


// ---------------------------------------------------------------------------
//  ¥ InstallResourceNameField											[public]
// ---------------------------------------------------------------------------

void
CEditorWindow::InstallResourceNameField() 
{
	// Install the name of the resource if it has one
	LStaticText * theStaticText = dynamic_cast<LStaticText *>(this->FindPaneByID( item_NameStaticText ));
	if (theStaticText != nil) {
		CEditorDoc * theDoc = dynamic_cast<CEditorDoc *>(GetSuperCommander());
		if (theDoc != nil) {
			Str255 * strPtr = theDoc->GetRezObj()->GetName();
			theStaticText->SetDescriptor(*strPtr);	
		} 
	} 
}


// ---------------------------------------------------------------------------
//	¥ IsDirty														[public]
// ---------------------------------------------------------------------------

Boolean
CEditorWindow::IsDirty()
{
	return mIsDirty;
}


// ---------------------------------------------------------------------------
//	¥ SetDirty														[public]
// ---------------------------------------------------------------------------

void
CEditorWindow::SetDirty(Boolean inDirty) 
{
	mIsDirty = inDirty;
	mOwnerDoc->SetModified(inDirty);
	::SetWindowModified(mMacWindowP, inDirty);	
}
