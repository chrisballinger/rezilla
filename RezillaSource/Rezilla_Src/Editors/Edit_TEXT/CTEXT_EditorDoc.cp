// ===========================================================================
// CTEXT_EditorDoc.cp
// 
//                       Created: 2004-06-17 12:46:55
//             Last modification: 2006-10-09 16:44:14
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2004-2006
// All rights reserved.
// ===========================================================================

PP_Begin_Namespace_PowerPlant


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CTEXT_EditorDoc.h"
#include "CTEXT_EditorWindow.h"
#include "CTEXT_EditorView.h"
#include "CEditorsController.h"
#include "RezillaConstants.h"
#include "CRezMap.h"
#include "CRezMapTable.h"
#include "CRezMapDoc.h"
#include "CRezObj.h"
#include "CRezillaPrefs.h"
#include "UCodeTranslator.h"
#include "UDialogBoxHandler.h"
#include "UMessageDialogs.h"
#include "UMiscUtils.h"

#include <LWindow.h>
#include <LFile.h>
#include <UStandardDialogs.h>
#include <LRadioGroupView.h>
#include <LCheckBox.h>
#include <LEditField.h>
#include <LDataStream.h>

#include <LString.h>
#include <PP_Messages.h>

// // Standard headers
// #include <string.h>




// ---------------------------------------------------------------------------
//   CTEXT_EditorDoc							Constructor		  [public]
// ---------------------------------------------------------------------------

CTEXT_EditorDoc::CTEXT_EditorDoc(LCommander* inSuper, 
								 CRezMapTable* inSuperMap,
								 CRezObj* inRezObj,
								 ResType inSubstType,
								 Boolean inReadOnly)
 	: CEditorDoc(inSuper, inSuperMap, inRezObj, inSubstType, inReadOnly)
{
	Initialize();
}


// ---------------------------------------------------------------------------
//     ~CTEXT_EditorDoc							Destructor				  [public]
// ---------------------------------------------------------------------------

CTEXT_EditorDoc::~CTEXT_EditorDoc()
{
	if (mTextEditWindow != nil) {
		delete mTextEditWindow;
	} 
}


// ---------------------------------------------------------------------------
//   Initialize													  [private]
// ---------------------------------------------------------------------------

void
CTEXT_EditorDoc::Initialize()
{
// 	mSearchString[0] = 0;
// 	mMatchStart = 0;
// 	mMatchEnd = 0;
// 	mSearchWhichPane = item_FindInHexRadio;
// 	mIgnoreCase = true;
	
	// Create a window for our document and set this doc as its SuperCommander
	mTextEditWindow = dynamic_cast<CTEXT_EditorWindow *>(LWindow::CreateWindow( PPob_TextEditorWindow, this ));
	Assert_( mTextEditWindow != nil );
	
	SetMainWindow( dynamic_cast<CEditorWindow *>(mTextEditWindow) );
	NameNewEditorDoc();
	mTextEditWindow->FinalizeEditor(this);

	// Install the contents according to the TMPL
	if (mRezObj != nil) {
		Handle rezData = mRezObj->GetData();
		
		if (rezData != nil) {
			Handle			theScrapHandle = NULL;
			CRezMap *		theRezMap = mRezMapTable->GetRezMap();

			// Look for a 'styl' resource with same ID
			OSErr error = theRezMap->GetWithID(ResType_TextStyle, mRezObj->GetID(), theScrapHandle, false);
			
			if (error == noErr) {
				mTextEditWindow->SetHasStyleResource(true);
			}
			mTextEditWindow->InstallText(rezData, (StScrpHandle) theScrapHandle);			
		} 
	} 
	
	mTextEditWindow->SetLengthField();
	
	// Make the window visible.
	mTextEditWindow->Show();
}


// ---------------------------------------------------------------------------
//   GetDescriptor													  [public]
// ---------------------------------------------------------------------------
//	Pass back the name of a Document

StringPtr
CTEXT_EditorDoc::GetDescriptor(
	Str255	outDescriptor) const
{
	if (mTextEditWindow != nil) {
		// Use name of its window
		mTextEditWindow->GetDescriptor(outDescriptor);
	} else {
		// No window, document name is empty string
		outDescriptor[0] = 0;		
	}

	return outDescriptor;
}


#if PP_Uses_CFDescriptor
// ---------------------------------------------------------------------------
//   CopyCFDescriptor												  [public]
// ---------------------------------------------------------------------------

CFStringRef
CTEXT_EditorDoc::CopyCFDescriptor() const
{
	CFStringRef		docName = nil;
	if (mTextEditWindow != nil) {
		docName = mTextEditWindow->CopyCFDescriptor();
	}
	return docName;
}
#endif


// ---------------------------------------------------------------------------
//   AllowSubRemoval												  [public]
// ---------------------------------------------------------------------------

Boolean
CTEXT_EditorDoc::AllowSubRemoval(
	LCommander*		inSub)
{
	if (inSub == mTextEditWindow) {
		AttemptClose(false);
		return false;
	} else {
		return true;
	}
}


// ---------------------------------------------------------------------------
//   AskSaveChanges												  [public]
// ---------------------------------------------------------------------------
//	Ask user whether to save changes before closing the Document.

SInt16
CTEXT_EditorDoc::AskSaveChanges(
	bool /* inQuitting */)
{
	return UMessageDialogs::AskYesNoFromLocalizable(CFSTR("SaveTextEditorWindow"), PPob_AskYesNoMessage);
}


// ---------------------------------------------------------------------------
//   GetModifiedResource										[protected]
// ---------------------------------------------------------------------------
// The returned handle should not be released by the caller so leave
// releaseIt to false (its default).

Handle
CTEXT_EditorDoc::GetModifiedResource(Boolean &releaseIt) 
{
#pragma unused(releaseIt)
	
	return mTextEditWindow->GetContentsView()->GetModifiedText();
}


// ---------------------------------------------------------------------------------
//   SaveStylResource
// ---------------------------------------------------------------------------------

void
CTEXT_EditorDoc::SaveStylResource(StScrpHandle	inScrapHandle)
{
	// Open or create a 'styl' resource and save the StScrpHandle therein
	CRezObj * stylRezObj = NULL;
	
	CEditorsController::OpenOrCreateWithTypeAndID(mRezMapTable, ResType_TextStyle, mRezObj->GetID(), &stylRezObj);
	if (stylRezObj != NULL) {
		// Copy to resource's data handle
		stylRezObj->SetData( (Handle) inScrapHandle);

		// Mark the resource as modified in the rez map
		stylRezObj->Changed();

		// Tell the rezmap doc that there has been a modification
		mRezMapTable->GetOwnerDoc()->SetModified(true);
		// Refresh the view
		stylRezObj->SetSize( ::GetHandleSize( (Handle) inScrapHandle) );
		mRezMapTable->Refresh();
	} 
}



PP_End_Namespace_PowerPlant


