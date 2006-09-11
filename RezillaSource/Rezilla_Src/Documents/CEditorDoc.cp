// ===========================================================================
// CEditorDoc.cp
// 
//                       Created: 2003-05-04 19:16:00
//             Last modification: 2005-06-11 15:31:17
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2003-2005
// All rights reserved.
// ===========================================================================

PP_Begin_Namespace_PowerPlant


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CRezillaApp.h"
#include "CInspectorWindow.h"
#include "CEditorDoc.h"
#include "CEditorWindow.h"
#include "CRezFile.h"
#include "CRezMapDoc.h"
#include "CRezMapTable.h"
#include "CRezObj.h"
#include "CRezObjItem.h"
#include "RezillaConstants.h"
#include "UMessageDialogs.h"
#include "UMiscUtils.h"


#include <LString.h>
#include <UStandardDialogs.h>

// // Standard headers
// #include <string.h>


// ---------------------------------------------------------------------------
//   CEditorDoc									Constructor		  [public]
// ---------------------------------------------------------------------------

CEditorDoc::CEditorDoc(LCommander* inSuper, 
						   CRezMapTable* inSuperMap, 
						   CRezObj* inRezObj,
						   ResType inSubstType,
						   Boolean inReadOnly)
 	: LDocument(inSuper)
{
	// Share the same CRezObj as the RezObjItem and increment its 
	// refcount. The inRezObj argument should never be NULL.
// 	mRezObj = new CRezObj(*inRezObj);
	mRezObj = inRezObj;
	mRezObj->IncrRefCount();

	mRezMapTable = inSuperMap;
	mMainWindow = nil;
	mSubstType = inSubstType;
	mReadOnly = inReadOnly;
	mKind = editor_kindGui;
	
	// Consider by default that it is an interface doc. Hex and tmpl docs 
	// will override this.
	SetModelKind(rzom_cGuiEditDoc);
	// The owner RezMapDoc is the super model
	SetSuperModel( dynamic_cast<LModelObject *>(inSuper) );

	RegisterDoc();
}


// ---------------------------------------------------------------------------
//     ~CEditorDoc							Destructor				  [public]
// ---------------------------------------------------------------------------

CEditorDoc::~CEditorDoc()
{
	UnregisterDoc();
	if (mRezObj != nil) {
		mRezObj->DecrRefCount();
		if (mRezObj->GetRefCount() == 0) {
			delete mRezObj;
		} 
	}
}


// ---------------------------------------------------------------------------------
//   NameNewEditorDoc
// ---------------------------------------------------------------------------------

void
CEditorDoc::NameNewEditorDoc()
{
	Str255 theTitle;
	
	// Build the title
	BuildDocumentTitle(theTitle, index_EditorDocUntitled);
	// Set window title
	if (mMainWindow != nil) {
		mMainWindow->SetDescriptor(theTitle);
	}
}


// ---------------------------------------------------------------------------------
//   BuildDocumentTitle
// ---------------------------------------------------------------------------------

void
CEditorDoc::BuildDocumentTitle(Str255 & outTitle, SInt16 whichString)
{
	FSSpec	theFileSpec;
	mRezMapTable->GetOwnerDoc()->GetRezFile()->GetSpecifier(theFileSpec);
	LStr255 theTitle(theFileSpec.name);
	theTitle.Append("\p - '");
	
	if ( mRezObj != nil ) {
		Str255 theString;

		UMiscUtils::OSTypeToPString(mRezObj->GetType(), theString);	
		theTitle.Append(theString);
		theTitle.Append("\p' #");
		::NumToString(mRezObj->GetID(), theString);
		theTitle.Append(theString);
	} else {
		// Start with the default name ("untitled [1]")
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
//   ObeyCommand									[public, virtual]
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
				
		default: 
		cmdHandled = LDocument::ObeyCommand(inCommand, ioParam);
		break;
	}
	
	return cmdHandled;
}


// ---------------------------------------------------------------------------------
//   FindCommandStatus
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
								
		case cmd_Copy:
		outEnabled = true;
		break;
		
		case cmd_Clear:
		case cmd_Cut:
		case cmd_Paste:
		outEnabled = not mReadOnly;
		break;

	  default:
		// Call inherited.
		LDocument::FindCommandStatus( inCommand,
				outEnabled, outUsesMark, outMark, outName );
		break;

	}
}


// ---------------------------------------------------------------------------
//   ListenToMessage													[public]
// ---------------------------------------------------------------------------

void
CEditorDoc::ListenToMessage( MessageT inMessage, void * /* ioParam */) 
{
	switch (inMessage) {
		case msg_EditorSave:
		if ( CanSaveChanges() ) {
			DoSaveChanges();
		} 
		break;
		
		case msg_EditorCancel:
		Close();
		break;
		
		case msg_EditorRevert:
		if ( UMessageDialogs::AskIfFromLocalizable(CFSTR("ConfirmRevert"), PPob_AskIfMessage) == true) {
			DoRevert();
		}
		break;
				
		default:
		break;
		
	}
}


// ---------------------------------------------------------------------------
//   CanSaveChanges												  [public]
// ---------------------------------------------------------------------------
// Deals with the resProtected attribute

Boolean
CEditorDoc::CanSaveChanges()
{
	Boolean canSave = true;
	SInt16 	answer;
	
	if (mRezObj->HasAttribute(resProtected)) {
		answer = UMessageDialogs::AskYesNoFromLocalizable(CFSTR("AskRemoveProtectedBit"), PPob_AskYesNoMessage);
		if (answer == answer_Do) {
			mRezObj->ToggleOneAttribute(resProtected);
		} else if (answer == answer_Cancel) {
			canSave = false;
		} 
	}

	return canSave;
}


// ---------------------------------------------------------------------------
//   AllowSubRemoval												  [public]
// ---------------------------------------------------------------------------

Boolean
CEditorDoc::AllowSubRemoval(
	LCommander* /* inSub */)
{
	return true;
}


// ---------------------------------------------------------------------------
//   AskSaveChanges												  [public]
// ---------------------------------------------------------------------------
//	Ask user whether to save changes before closing the Document or
//	quitting the Application.

SInt16
CEditorDoc::AskSaveChanges(
	bool /* inQuitting */)
{
	return UMessageDialogs::AskYesNoFromLocalizable(CFSTR("SaveModifiedResource"), PPob_AskYesNoMessage);
}


// ---------------------------------------------------------------------------
//   AttemptClose													  [public]
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
	
	if (IsModified() && !mReadOnly) {
		
		answer = AskSaveChanges(SaveWhen_Closing);
		
		if (answer == answer_Save) {
			if ( CanSaveChanges() ) {
				DoSaveChanges();
			} 
		} else if (answer == answer_Cancel) {
			closeIt = false;
		}
	}

	if (closeIt) {
		Close();
	}
}


// ---------------------------------------------------------------------------
//   DoAEClose														  [public]
// ---------------------------------------------------------------------------
// Close a Document in response to a "close" AppleEvent. Optional "file"
// parameter is ignored but check for optional "saveOption" parameter.
// Default value is "ask".

void
CEditorDoc::DoAEClose(
	const AppleEvent&	inCloseAE)
{
	OSErr		err;
	DescType	theType;
	Size		theSize;
	bool		saveIt = false;
	bool		closeIt = true;
	SInt32		saveOption = kAEAsk;

	// Optional "saveOption" parameter
	err = ::AEGetParamPtr(&inCloseAE, keyAESaveOptions,
				typeEnumeration, &theType, &saveOption,
				sizeof(SInt32), &theSize);

	if (saveOption == kAEAsk) {
		SInt16	saveAnswer = answer_DontSave;

		if (IsModified()) {
			UAppleEventsMgr::InteractWithUser(Throw_Yes);
			saveAnswer = AskSaveChanges(SaveWhen_Closing);
		}

		if (saveAnswer == answer_Save) {
			saveIt = true;
		} else if (saveAnswer == answer_Cancel) {
			closeIt = false;				// Abort the close
		}

	} else if (saveOption == kAEYes) {
		saveIt = true;
	}

	if ( saveIt ) {
		UAppleEventsMgr::InteractWithUser(Throw_Yes);
		if ( CanSaveChanges() ) {
			DoSaveChanges();
		} else {
			closeIt = false;				// Abort the close
		}		
	}

	if (closeIt) {
		// Finally, close the document
		Close();
	} else {
		// User canceling the close means the AppleEvent failed
		ThrowOSErr_(userCanceledErr);
	}
}


// ---------------------------------------------------------------------------
//   DoSaveChanges													[public]
// ---------------------------------------------------------------------------
// The callee should set the shouldWeRelease variable to tell us if the 
// handle we receive should be released here.

void
CEditorDoc::DoSaveChanges() 
{
	Boolean shouldWeRelease = false;
	Handle theHandle = GetModifiedResource(shouldWeRelease);
	
	if (theHandle != NULL) {
		// Copy to resource's data handle
		mRezObj->SetData(theHandle);
		
		// Note: the resource is marked as modified in SetData()
		
		if (shouldWeRelease) {
			::DisposeHandle(theHandle);
		} 
	} 
	
	// Tell the rezmap doc that there has been a modification
	mRezMapTable->GetOwnerDoc()->SetModified(true);
	
	// The editor window is not dirty anymore. This will also set 
	// mModified to false.
	mMainWindow->SetDirty(false);
	
	// Refresh the view
	// Note: the size of the resource is updated in SetData()
	mRezMapTable->Refresh();
	
	// Update the inspector if its info concerns the RezObj
	if (CRezillaApp::sInspectorWindow != nil
		&& CRezillaApp::sInspectorWindow->GetRezObjItem() != nil 
		&& CRezillaApp::sInspectorWindow->GetRezObjItem()->GetRezObj() == mRezObj) {
		CRezillaApp::sInspectorWindow->InstallValues(mRezObj);
	} 		
	
}


// ---------------------------------------------------------------------------
//   GetDescriptor													  [public]
// ---------------------------------------------------------------------------
//	Pass back the name of a Document

StringPtr
CEditorDoc::GetDescriptor(
	Str255	outDescriptor) const
{
	if (mMainWindow != nil) {
		// Use name of its window
		mMainWindow->GetDescriptor(outDescriptor);
	} else {
		// No window, document name is empty string
		outDescriptor[0] = 0;		
	}

	return outDescriptor;
}


// ---------------------------------------------------------------------------
//   GetModifiedResource											[public]
// ---------------------------------------------------------------------------
// Note: it is a purely virtual member function. Define in every 
// subclasses. For instance:
// 
// 			Handle
// 			CEditorDoc::GetModifiedResource(Boolean & /* releaseIt */) 
// 			{
// 				return NULL;
// 			}


// ---------------------------------------------------------------------------
//   DoRevert														[public]
// ---------------------------------------------------------------------------
//	Revert a Document to its last saved version

void
CEditorDoc::DoRevert()
{
	if (mMainWindow != nil) {
		mMainWindow->RevertContents();
	} 
}


// ---------------------------------------------------------------------------------
//   Register
// ---------------------------------------------------------------------------------

void
CEditorDoc::RegisterDoc()
{
	mRezMapTable->GetOwnerDoc()->GetOpenedEditors()->AddItem(this);
}


// ---------------------------------------------------------------------------------
//   Unregister
// ---------------------------------------------------------------------------------

void
CEditorDoc::UnregisterDoc()
{
	mRezMapTable->GetOwnerDoc()->GetOpenedEditors()->Remove(this);
}


// ---------------------------------------------------------------------------------
//   SelectMainWindow
// ---------------------------------------------------------------------------------

void
CEditorDoc::SelectMainWindow()
{
	if (mMainWindow != nil) {
		mMainWindow->Select();
	} 
}
 

PP_End_Namespace_PowerPlant


