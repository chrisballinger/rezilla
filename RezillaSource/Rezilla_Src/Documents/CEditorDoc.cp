// ===========================================================================
// CEditorDoc.cp
// 
//                       Created: 2003-05-04 19:16:00
//             Last modification: 2004-07-01 18:12:36
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003-2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

PP_Begin_Namespace_PowerPlant


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CEditorDoc.h"
#include "CRezFile.h"
#include "CRezMapDoc.h"
#include "CRezMapTable.h"
#include "CRezObj.h"
#include "RezillaConstants.h"
#include "UMessageDialogs.h"
#include "UMiscUtils.h"


#include <LString.h>
#include <UStandardDialogs.h>

// // Standard headers
// #include <string.h>


// ---------------------------------------------------------------------------
//	¥ CEditorDoc							Constructor		  [public]
// ---------------------------------------------------------------------------

CEditorDoc::CEditorDoc(LCommander* inSuper, 
						   CRezMapTable* inSuperMap, 
						   CRezObj* inRezObj,
						   Boolean inReadOnly)
 	: LDocument(inSuper)
{
	mRezObj = inRezObj;
	mRezMapTable = inSuperMap;
	mMainWindow = nil;
	mReadOnly = inReadOnly;
	mKind = editor_kindGui;
	Register();
}


// ---------------------------------------------------------------------------
//	¥ ~CEditorDoc							Destructor				  [public]
// ---------------------------------------------------------------------------

CEditorDoc::~CEditorDoc()
{
	Unregister();
}


// ---------------------------------------------------------------------------------
//  ¥ BuildDocumentTitle
// ---------------------------------------------------------------------------------

void
CEditorDoc::BuildDocumentTitle(Str255 & outTitle, SInt16 whichString)
{
	FSSpec	theFileSpec;
	mRezMapTable->GetOwnerDoc()->GetRezFile()->GetSpecifier(theFileSpec);
	LStr255 theTitle(theFileSpec.name);
	theTitle.Append("\p Ñ '");
	
	if ( mRezObj != nil ) {
		Str255 theString;

		UMiscUtils::OSTypeToPString(mRezObj->GetType(), theString);	
		theTitle.Append(theString);
		theTitle.Append("\p'  #");
		::NumToString(mRezObj->GetID(), theString);
		theTitle.Append(theString);
	} else {
		// Start with the default name ("untitled rez [1]")
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


// ---------------------------------------------------------------------------
//	¥ ObeyCommand									[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CEditorDoc::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;	// Assume we'll handle the command
	
	switch (inCommand) {
		
		case cmd_Close : 
		AttemptClose(false);
		break;
				
		case cmd_Find:
		break;
				
		case cmd_FindNext:
		break;
				
		default: {
			cmdHandled = LDocument::ObeyCommand(inCommand, ioParam);
			break;
		}
	}
	
	return cmdHandled;
}


// ---------------------------------------------------------------------------------
//  ¥ FindCommandStatus
// ---------------------------------------------------------------------------------

void
CEditorDoc::FindCommandStatus(
	CommandT	inCommand,
	Boolean		&outEnabled,
	Boolean		&outUsesMark,
	UInt16		&outMark,
	Str255		outName )
{
	switch ( inCommand ) {
	
		case cmd_Save:
		case cmd_SaveAs:
		case cmd_ExportMap:
		case cmd_FindNext:
			outEnabled = false;
		break;

		case cmd_Find:
		LString::CopyPStr( "\pFindÉ", outName);
		outEnabled = false;
		break;

		case cmd_Close : 
		outEnabled = true;
		break;
								
	  default:
		// Call inherited.
		LDocument::FindCommandStatus( inCommand,
				outEnabled, outUsesMark, outMark, outName );
		break;

	}
}


// ---------------------------------------------------------------------------
//  ¥ ListenToMessage													[public]
// ---------------------------------------------------------------------------

void
CEditorDoc::ListenToMessage( MessageT inMessage, void *ioParam ) 
{
	switch (inMessage) {
		
		default:
		break;
		
	}
}


// ---------------------------------------------------------------------------------
//  ¥ IsModified
// ---------------------------------------------------------------------------------

Boolean
CEditorDoc::IsModified()
{
	mIsModified = false;
	return mIsModified;
}


// ---------------------------------------------------------------------------
//	¥ AllowSubRemoval												  [public]
// ---------------------------------------------------------------------------

Boolean
CEditorDoc::AllowSubRemoval(
	LCommander*		inSub)
{
	return true;
}


// ---------------------------------------------------------------------------
//	¥ AskSaveChanges												  [public]
// ---------------------------------------------------------------------------
//	Ask user whether to save changes before closing the Document or
//	quitting the Application

SInt16
CEditorDoc::AskSaveChanges(
	bool /* inQuitting */)
{
	return UMessageDialogs::AskYesNoFromLocalizable(CFSTR("SaveModifiedResource"), rPPob_AskYesNoMessage);
}



// ---------------------------------------------------------------------------
//	¥ AttemptClose													  [public]
// ---------------------------------------------------------------------------
//	Try to close an edited resource.
//
//	The Document might not close if it is modified and the user cancels
//	the operation when asked whether to save the changes.

void
CEditorDoc::AttemptClose(
	Boolean	/* inRecordIt */)
{
	Boolean		closeIt = true;
	SInt16 		answer;
	
	if (IsModified()) {
		
		answer = AskSaveChanges(SaveWhen_Closing);
		
		if (answer == answer_Save) {
			DoSaveChanges();
		} else if (answer == answer_Cancel) {
			closeIt = false;
		}
	}

	if (closeIt) {
		Close();
	}
}


// ---------------------------------------------------------------------------
//  ¥ DoSaveChanges													[public]
// ---------------------------------------------------------------------------

void
CEditorDoc::DoSaveChanges() 
{
	Handle theHandle = GetModifiedResource();
	
	// Copy to resource's data handle
	mRezObj->SetData(theHandle);

	// Mark the resource as modified in the rez map
	mRezObj->Changed();

	// Tell the rezmap doc that there has been a modification
	mRezMapTable->GetOwnerDoc()->SetModified(true);
	// Refresh the view
	mRezObj->SetSize( ::GetHandleSize(theHandle) );
	mRezMapTable->Refresh();
}


// ---------------------------------------------------------------------------
//  ¥ GetModifiedResource										[public]
// ---------------------------------------------------------------------------
// Override in subclasses to collect the proper modified data.

Handle
CEditorDoc::GetModifiedResource() 
{
	return mRezObj->GetData();
}


// ---------------------------------------------------------------------------------
//  ¥ Register
// ---------------------------------------------------------------------------------

void
CEditorDoc::Register()
{
	mRezMapTable->GetOwnerDoc()->GetOpenedEditors()->AddItem(this);
}


// ---------------------------------------------------------------------------------
//  ¥ Unregister
// ---------------------------------------------------------------------------------

void
CEditorDoc::Unregister()
{
	mRezMapTable->GetOwnerDoc()->GetOpenedEditors()->Remove(this);
}


// ---------------------------------------------------------------------------------
//  ¥ SelectMainWindow
// ---------------------------------------------------------------------------------

void
CEditorDoc::SelectMainWindow()
{
	if (mMainWindow != nil) {
		mMainWindow->Select();
	} 
}
 


PP_End_Namespace_PowerPlant


