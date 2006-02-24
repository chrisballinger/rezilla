// ===========================================================================
// CEditorWindow.cp
// 
//                       Created: 2004-06-10 14:50:31
//             Last modification: 2006-02-21 15:31:46
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2004-2006
// All rights reserved.
// ===========================================================================


#include "CEditorWindow.h"
#include "CEditorDoc.h"
#include "CRezObj.h"
#include "CWindowMenu.h"
#include "RezillaConstants.h"

#include <LIconPane.h>
#include <LStaticText.h>

extern CWindowMenu * gWindowMenu;


// ---------------------------------------------------------------------------
//  CEditorWindow				[public]
// ---------------------------------------------------------------------------

CEditorWindow::CEditorWindow()
{
	mIsDirty = false;
	mOwnerDoc = nil;
	SetModelKind(rzom_cGuiWindow);	// This is overriden in the case of 
	                              	// template, plugin or hexadecimal
	                              	// windows. This way we don't have to
	                              	// bother setting the kind in every
	                              	// custom editor.
}


// ---------------------------------------------------------------------------
//  CEditorWindow				[public]
// ---------------------------------------------------------------------------

CEditorWindow::CEditorWindow(
	const SWindowInfo &inWindowInfo )
		: LWindow( inWindowInfo )
{
	mIsDirty = false;
	mOwnerDoc = nil;
	SetModelKind(rzom_cGuiWindow);
}


// ---------------------------------------------------------------------------
//  CEditorWindow				[public]
// ---------------------------------------------------------------------------

CEditorWindow::CEditorWindow(
	ResIDT		inWINDid,
	UInt32		inAttributes,
	LCommander	*inSuperCommander )
		: LWindow( inWINDid, inAttributes, inSuperCommander )
{
	mIsDirty = false;
	mOwnerDoc = nil;
	SetModelKind(rzom_cGuiWindow);
}


// ---------------------------------------------------------------------------
//  CPluginEditorWindow				[public]
// ---------------------------------------------------------------------------

CEditorWindow::CEditorWindow(
					WindowPtr		inMacWindow,
					LCommander*		inSuperCommander)
		: LWindow(inMacWindow, inSuperCommander)
{
}


// ---------------------------------------------------------------------------
//  CEditorWindow				[public]
// ---------------------------------------------------------------------------

CEditorWindow::CEditorWindow(
			       LStream *inStream )
		: LWindow( inStream )
{
	mIsDirty = false;
	mOwnerDoc = nil;
	SetModelKind(rzom_cGuiWindow);
}


// ---------------------------------------------------------------------------
//  ~CEditorWindow				[public]
// ---------------------------------------------------------------------------

CEditorWindow::~CEditorWindow()
{
	// Remove the window from the window menu.
	gWindowMenu->RemoveWindow(this);
}


// ---------------------------------------------------------------------------
//  FinalizeEditor											[public]
// ---------------------------------------------------------------------------

void
CEditorWindow::FinalizeEditor(CEditorDoc* inEditorDoc, void * ioParam)
{
#pragma unused(ioParam)
	
	SetOwnerDoc(inEditorDoc);
	InstallResourceNameField();
	InstallReadOnlyIcon();

	SetSuperModel(inEditorDoc);
	
	// Add the window to the window menu.
	gWindowMenu->InsertWindow(this);
}
	

// ---------------------------------------------------------------------------
//  ListenToMessage									[public]
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
//  FindCommandStatus
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
		case cmd_EditWithPlugin:
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
//  ObeyCommand							[public, virtual]
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
//  RevertContents												  [public]
// ---------------------------------------------------------------------------
// Override in subclasses to redraw the contents view with the last saved 
// data.

void
CEditorWindow::RevertContents()
{
	SetDirty(false);
}


// ---------------------------------------------------------------------------
//   InstallReadOnlyIcon											[public]
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
//   InstallResourceNameField											[public]
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
//  IsDirty														[public]
// ---------------------------------------------------------------------------

Boolean
CEditorWindow::IsDirty()
{
	return mIsDirty;
}


// ---------------------------------------------------------------------------
//  SetDirty														[public]
// ---------------------------------------------------------------------------

void
CEditorWindow::SetDirty(Boolean inDirty) 
{
	mIsDirty = inDirty;
	mOwnerDoc->SetModified(inDirty);
	::SetWindowModified(mMacWindowP, inDirty);	
}
