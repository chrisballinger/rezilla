// ===========================================================================
// CPickerDoc.cp
// 
//                       Created: 2006-02-23 15:12:16
//             Last modification: 2006-03-19 11:58:46
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================

PP_Begin_Namespace_PowerPlant

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CRezillaApp.h"
#include "CInspectorWindow.h"
#include "CPickerDoc.h"
#include "CPickerWindow.h"
#include "CPickerView.h"
#include "CRezMapDoc.h"
#include "CRezFile.h"
#include "CRezMapTable.h"
#include "CRezTypeItem.h"
#include "CRezObjItem.h"
#include "CRezType.h"
#include "RezillaConstants.h"
#include "UMessageDialogs.h"
#include "UMiscUtils.h"

#include <LString.h>
#include <UStandardDialogs.h>


// ---------------------------------------------------------------------------
//   CPickerDoc									Constructor		  [public]
// ---------------------------------------------------------------------------

CPickerDoc::CPickerDoc(LCommander* inSuper, 
						   CRezMapTable* inSuperMap, 
						   CRezTypeItem* inRezTypeItem,
						   Boolean inReadOnly)
 	: LDocument(inSuper)
{
	mRezTypeItem = inRezTypeItem;
	mRezMapTable = inSuperMap;
	mReadOnly = inReadOnly;
	
	// Set the AE model object
	SetModelKind(rzom_cPickerDoc);
	
	// The owner RezMapDoc is the super model
	SetSuperModel( dynamic_cast<LModelObject *>(inSuper) );
}


// ---------------------------------------------------------------------------
//     ~CPickerDoc							Destructor				  [public]
// ---------------------------------------------------------------------------

CPickerDoc::~CPickerDoc()
{
	if (mPickerWindow != nil) {
		delete mPickerWindow;
	} 
	Unregister();
}


// ---------------------------------------------------------------------------------
//   BuildDocumentTitle
// ---------------------------------------------------------------------------------

void
CPickerDoc::BuildDocumentTitle(Str255 & outTitle, SInt16 whichString)
{
	FSSpec	theFileSpec;
	mRezMapTable->GetOwnerDoc()->GetRezFile()->GetSpecifier(theFileSpec);
	LStr255 theTitle(theFileSpec.name);
	theTitle.Append("\p - '");
	
	if ( mRezTypeItem != nil ) {
		Str255 theString;

		UMiscUtils::OSTypeToPString(mRezTypeItem->GetRezType()->GetType(), theString);	
		theTitle.Append(theString);
		theTitle.Append("\p' Picker");
	} else {
		// Start with the default name ("Picker [1]")
		theTitle.Assign(STRx_DefaultDocTitles, whichString);
		// If an existing window has this name, append a count and
		// keep incrementing the count until we find a unique name.
		long	num = 1;
		while (UWindows::FindNamedWindow(theTitle) != nil) {
			theTitle.Assign(STRx_DefaultDocTitles, whichString + 1);
			++num;
			theTitle += "\p [";
			theTitle += num;
			theTitle += "\p]";
		}		
	}
	LString::CopyPStr(theTitle, outTitle);
}


// ---------------------------------------------------------------------------------
//   FindCommandStatus
// ---------------------------------------------------------------------------------

void
CPickerDoc::FindCommandStatus(
	CommandT	inCommand,
	Boolean		&outEnabled,
	Boolean		&outUsesMark,
	UInt16		&outMark,
	Str255		outName )
{
	switch ( inCommand ) {
	
		case cmd_Save:
		case cmd_SaveAs:
		case cmd_Import:
		case cmd_Export:
		case cmd_FindNext:
		outEnabled = false;
		break;

		case cmd_Find:
		LString::CopyPStr( "\pFind...", outName);
		outEnabled = false;
		break;

		case cmd_Close : 
		outEnabled = true;
		break;
				
		case cmd_Paste:
		outEnabled = not mReadOnly;
		break;
		
		case cmd_Clear:
		case cmd_Cut:
		outEnabled = ( not mReadOnly && mPickerWindow->GetSelectedView() != NULL);
		break;

		default:
		// Call inherited.
		LDocument::FindCommandStatus( inCommand,
				outEnabled, outUsesMark, outMark, outName );
		break;

	}
}


// ---------------------------------------------------------------------------
//  ObeyCommand												[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CPickerDoc::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean			cmdHandled = true, sendToRezmapDoc = false;
	CPickerView*	theView = mPickerWindow->GetSelectedView();
	ResType			theType = mRezTypeItem->GetRezType()->GetType();
	ResType			asType = theType;
	CRezMapDoc *	rezmapDoc = mRezMapTable->GetOwnerDoc();

	if (inCommand == cmd_Close) {
		AttemptClose(false);
	} else if (inCommand == cmd_Paste || inCommand == cmd_NewRez) {
		sendToRezmapDoc = true;
	} else if (theView != NULL) {
		// Find the corresponding RezObjItem in the RezMapDoc
		CRezObjItem *	theRezObjItem = mRezMapTable->GetRezObjItem(theType, theView->GetPaneID(), true);
		ThrowIfNil_(theRezObjItem);
		
		switch (inCommand) {

			case cmd_Copy: 
			case cmd_Cut: 
			STableCell	cell;
			cell.col = 1;
			cell.row = theRezObjItem->FindRowForItem();
			mRezMapTable->UnselectAllCells();
			mRezMapTable->SelectCell(cell);
			sendToRezmapDoc = true;
			break;
	
			case cmd_RemoveRez:
			case cmd_Clear: 
			rezmapDoc->RemoveResource( theRezObjItem );
			break;		
			
			case cmd_EditRez:
			case cmd_EditRezAsType:
			case cmd_EditWithPlugin:
			case cmd_TmplEditRez:
			case cmd_HexEditRez:		
			if (inCommand == cmd_EditRezAsType && ! UMiscUtils::SelectType(asType) ) {
				return cmdHandled;
			} 
			rezmapDoc->TryEdit(theRezObjItem, inCommand, asType);
			break;
		
			case cmd_GetRezInfo: 
			CRezillaApp::sInspectorWindow->Show();
			CRezillaApp::sInspectorWindow->InstallValues(theRezObjItem);
			// Bring the window to the front.
			UDesktop::SelectDeskWindow( CRezillaApp::sInspectorWindow );
			break;		
			
			default:
			cmdHandled = false;
			break;

		}
	} 
	
	if (sendToRezmapDoc) {
		// Forward to the RezMapDoc and let it handle this
		cmdHandled = rezmapDoc->ObeyCommand(inCommand, ioParam);	
	} 
	if (cmdHandled == false) {
		cmdHandled = LDocument::ObeyCommand(inCommand, ioParam);
	} 

	return cmdHandled;
}


// ---------------------------------------------------------------------------
//   ListenToMessage													[public]
// ---------------------------------------------------------------------------

void
CPickerDoc::ListenToMessage( MessageT inMessage, void * ioParam) 
{
	switch (inMessage) {
				
		default:
		break;
		
	}
}


// ---------------------------------------------------------------------------
//   AllowSubRemoval												  [public]
// ---------------------------------------------------------------------------

Boolean
CPickerDoc::AllowSubRemoval(
	LCommander* /* inSub */)
{
	return true;
}


// ---------------------------------------------------------------------------
//   AttemptClose													  [public]
// ---------------------------------------------------------------------------
//	Close an opened picker

void
CPickerDoc::AttemptClose(
	Boolean	/* inRecordIt */)
{
	Close();
}


// ---------------------------------------------------------------------------
//   DoAEClose														  [public]
// ---------------------------------------------------------------------------
// Close a Picker in response to a "close" AppleEvent. Optional "file"
// and "saveOption" parameters are ignored.

void
CPickerDoc::DoAEClose(
	const AppleEvent&	/* inCloseAE */)
{
	Close();
}


// ---------------------------------------------------------------------------
//   GetDescriptor													  [public]
// ---------------------------------------------------------------------------
//	Pass back the name of a Document. This is overriden in the TPickerDoc 
//	template class.

StringPtr
CPickerDoc::GetDescriptor(
	Str255	outDescriptor) const
{
	outDescriptor[0] = 0;		
	return outDescriptor;
}


// ---------------------------------------------------------------------------------
//   SelectPickerWindow
// ---------------------------------------------------------------------------------

void
CPickerDoc::SelectPickerWindow()
{
	if (mPickerWindow != nil) {
		mPickerWindow->Select();
	} 
}
 

// ---------------------------------------------------------------------------------
//   Register
// ---------------------------------------------------------------------------------

void
CPickerDoc::Register()
{
	mRezMapTable->GetOwnerDoc()->GetOpenedPickers()->AddItem(this);
}


// ---------------------------------------------------------------------------------
//   Unregister
// ---------------------------------------------------------------------------------

void
CPickerDoc::Unregister()
{
	mRezMapTable->GetOwnerDoc()->GetOpenedPickers()->Remove(this);
}


PP_End_Namespace_PowerPlant


