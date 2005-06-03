// ===========================================================================
// CUtxt_EditorDoc.cp
// 
//                       Created: 2004-12-08 18:21:21
//             Last modification: 2005-06-03 10:51:10
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

PP_Begin_Namespace_PowerPlant


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CUtxt_EditorDoc.h"
#include "CUtxt_EditorWindow.h"
#include "CUtxt_EditorView.h"
#include "RezillaConstants.h"
#include "CRezObj.h"
#include "CRezMap.h"
#include "CRezMapDoc.h"
#include "CRezMapTable.h"
#include "CEditorsController.h"
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
//	¥ CUtxt_EditorDoc							Constructor		  [public]
// ---------------------------------------------------------------------------

CUtxt_EditorDoc::CUtxt_EditorDoc(LCommander* inSuper, 
								 CRezMapTable* inSuperMap,
								 CRezObj* inRezObj,
								 ResType inSubstType,
								 Boolean inReadOnly)
 	: CEditorDoc(inSuper, inSuperMap, inRezObj, inSubstType, inReadOnly)
{
	Initialize();
}


// ---------------------------------------------------------------------------
//	¥ ~CUtxt_EditorDoc							Destructor				  [public]
// ---------------------------------------------------------------------------

CUtxt_EditorDoc::~CUtxt_EditorDoc()
{
	if (mUtxtEditWindow != nil) {
		delete mUtxtEditWindow;
	} 
}


// ---------------------------------------------------------------------------
//	¥ Initialize													  [public]
// ---------------------------------------------------------------------------

void
CUtxt_EditorDoc::Initialize()
{
	// Create window for our document. This sets this doc as the SuperCommander of the window.
	mUtxtEditWindow = dynamic_cast<CUtxt_EditorWindow *>(LWindow::CreateWindow( PPob_UtxtEditorWindow, this ));
	Assert_( mUtxtEditWindow != nil );
	
	SetMainWindow( dynamic_cast<CEditorWindow *>(mUtxtEditWindow) );
	NameNewEditorDoc();
	mUtxtEditWindow->Finalize(this);

	// Install the contents
	if (mRezObj != nil) {
		Handle rezData = mRezObj->GetData();
		
		if (rezData != nil) {
			mUtxtEditWindow->InstallText(rezData);			
		} 
	} 
	
	mUtxtEditWindow->SetLengthField( mUtxtEditWindow->GetContentsView()->GetDataSize() );
	
	// This is the equivalent of SetDirty(false)
	mUtxtEditWindow->GetContentsView()->ResetChangesCount();
	mUtxtEditWindow->SetDirty(false);
	
	// Make the window visible.
	mUtxtEditWindow->Show();
}


// ---------------------------------------------------------------------------
//	¥ GetDescriptor													  [public]
// ---------------------------------------------------------------------------
//	Pass back the name of a Document

StringPtr
CUtxt_EditorDoc::GetDescriptor(
	Str255	outDescriptor) const
{
	if (mUtxtEditWindow != nil) {
		// Use name of its window
		mUtxtEditWindow->GetDescriptor(outDescriptor);
	} else {
		// No window, document name is empty string
		outDescriptor[0] = 0;		
	}

	return outDescriptor;
}


// ---------------------------------------------------------------------------------
//  ¥ FindCommandStatus
// ---------------------------------------------------------------------------------

void
CUtxt_EditorDoc::FindCommandStatus(
	CommandT	inCommand,
	Boolean		&outEnabled,
	Boolean		&outUsesMark,
	UInt16		&outMark,
	Str255		outName )
{
	switch ( inCommand ) {
	
	  default:
			// Call inherited.
		CEditorDoc::FindCommandStatus( inCommand,
				outEnabled, outUsesMark, outMark, outName );
		break;

	}
}


// ---------------------------------------------------------------------------
//	¥ AllowSubRemoval												  [public]
// ---------------------------------------------------------------------------

Boolean
CUtxt_EditorDoc::AllowSubRemoval(
	LCommander*		inSub)
{
	if (inSub == mUtxtEditWindow) {
		AttemptClose(false);
		return false;
	} else {
		return true;
	}
}


// ---------------------------------------------------------------------------
//	¥ AskSaveChanges												  [public]
// ---------------------------------------------------------------------------
//	Ask user whether to save changes before closing the Document.

SInt16
CUtxt_EditorDoc::AskSaveChanges(
	bool /* inQuitting */)
{
	return UMessageDialogs::AskYesNoFromLocalizable(CFSTR("SaveTextEditorWindow"), PPob_AskYesNoMessage);
}


// ---------------------------------------------------------------------------
//  ¥ GetModifiedResource										[protected]
// ---------------------------------------------------------------------------
// (From MacTextEditor.h) The handle passed to TXNGetDataEncoded should not
// be allocated. TXNGetDataEncoded takes care of allocating the dataHandle
// as necessary. However, the caller is responsible for disposing the
// handle.

Handle
CUtxt_EditorDoc::GetModifiedResource(Boolean &releaseIt) 
{
	releaseIt = true;
	return mUtxtEditWindow->GetContentsView()->GetModifiedText();
}


// ---------------------------------------------------------------------------------
//  ¥ SaveStylResource
// ---------------------------------------------------------------------------------
// What's the eqauivalent of TextEdit's StScrpHandle with MLTE ?

void
CUtxt_EditorDoc::SaveStylResource(Handle inStyleHandle)
{
	if (inStyleHandle == NULL) {
		return;
	} else {
		// Open or create a 'styl' resource and save the style handle therein
		CRezObj * stylRezObj = NULL;
		
		CEditorsController::OpenOrCreateWithTypeAndID(mRezMapTable, 'styl', mRezObj->GetID(), &stylRezObj);
		if (stylRezObj != NULL) {
			// Copy to resource's data handle
			stylRezObj->SetData( (Handle) inStyleHandle);
			
			// Mark the resource as modified in the rez map
			stylRezObj->Changed();
			
			// Tell the rezmap doc that there has been a modification
			mRezMapTable->GetOwnerDoc()->SetModified(true);
			// Refresh the view
			stylRezObj->SetSize( ::GetHandleSize( (Handle) inStyleHandle) );
			mRezMapTable->Refresh();
		} 
	}
}



PP_End_Namespace_PowerPlant


