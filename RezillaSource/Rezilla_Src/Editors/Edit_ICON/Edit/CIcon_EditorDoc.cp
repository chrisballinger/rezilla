// ===========================================================================
// CIcon_EditorDoc.cp
// 
//                       Created: 2004-12-11 23:33:03
//             Last modification: 2004-12-11 23:33:06
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

PP_Begin_Namespace_PowerPlant


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CIcon_EditorDoc.h"
#include "CIcon_EditorWindow.h"
#include "CIcon_EditorView.h"
#include "CEditorsController.h"
#include "RezillaConstants.h"
#include "CRezMap.h"
#include "CRezMapTable.h"
#include "CRezMapDoc.h"
#include "CRezObj.h"
#include "CRezillaPrefs.h"
#include "CWindowMenu.h"
#include "UCodeTranslator.h"
#include "UDialogBoxHandler.h"
#include "UMessageDialogs.h"
#include "UMiscUtils.h"
// #include "CRezFile.h"
// #include "CRezillaApp.h"

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


extern CWindowMenu * gWindowMenu;


// ---------------------------------------------------------------------------
//	¥ CIcon_EditorDoc							Constructor		  [public]
// ---------------------------------------------------------------------------

CIcon_EditorDoc::CIcon_EditorDoc(LCommander* inSuper, 
								 CRezMapTable* inSuperMap,
								 CRezObj* inRezObj,
								 ResType inSubstType,
								 Boolean inReadOnly)
 	: CEditorDoc(inSuper, inSuperMap, inRezObj, inSubstType, inReadOnly)
{
	Initialize();
}


// ---------------------------------------------------------------------------
//	¥ ~CIcon_EditorDoc							Destructor				  [public]
// ---------------------------------------------------------------------------

CIcon_EditorDoc::~CIcon_EditorDoc()
{
	if (mIconEditWindow != nil) {
		// Remove the window from the window menu.
		gWindowMenu->RemoveWindow( mIconEditWindow );
		delete mIconEditWindow;
	} 
}


// ---------------------------------------------------------------------------
//	¥ Initialize													  [public]
// ---------------------------------------------------------------------------

void
CIcon_EditorDoc::Initialize()
{
	
	// Create window for our document. This sets this doc as the SuperCommander of the window.
	mIconEditWindow = dynamic_cast<CIcon_EditorWindow *>(LWindow::CreateWindow( rPPob_IconEditorWindow, this ));
	Assert_( mIconEditWindow != nil );
	
	mIconEditWindow->SetOwnerDoc(this);
	mIconEditWindow->InstallReadOnlyIcon();
	SetMainWindow( dynamic_cast<CEditorWindow *>(mIconEditWindow) );

	NameNewEditorDoc();
	
	// Add the window to the window menu.
	gWindowMenu->InsertWindow( mIconEditWindow );
		
	// Install the contents according to the TMPL
	if (mRezObj != nil) {
		Handle rezData = mRezObj->GetData();
		
		if (rezData != nil) {
			mIconEditWindow->InstallBitmap(rezData);			
		} 
	} 
		
	// Make the window visible.
	mIconEditWindow->Show();
}


// ---------------------------------------------------------------------------
//	¥ GetDescriptor													  [public]
// ---------------------------------------------------------------------------
//	Pass back the name of a Document

StringPtr
CIcon_EditorDoc::GetDescriptor(
	Str255	outDescriptor) const
{
	if (mIconEditWindow != nil) {
		// Use name of its window
		mIconEditWindow->GetDescriptor(outDescriptor);
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
CIcon_EditorDoc::FindCommandStatus(
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
CIcon_EditorDoc::AllowSubRemoval(
	LCommander*		inSub)
{
	if (inSub == mIconEditWindow) {
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
CIcon_EditorDoc::AskSaveChanges(
	bool /* inQuitting */)
{
	return UMessageDialogs::AskYesNoFromLocalizable(CFSTR("SaveTextEditorWindow"), rPPob_AskYesNoMessage);
}


// ---------------------------------------------------------------------------
//  ¥ GetModifiedResource										[protected]
// ---------------------------------------------------------------------------

Handle
CIcon_EditorDoc::GetModifiedResource() 
{
	return mIconEditWindow->GetContentsView()->GetModifiedBitmap();
}


// ---------------------------------------------------------------------------------
//  ¥ SaveStylResource
// ---------------------------------------------------------------------------------

void
CIcon_EditorDoc::SaveStylResource(StScrpHandle	inScrapHandle)
{
	// Open or create a 'styl' resource and save the StScrpHandle therein
	CRezObj * stylRezObj = NULL;
	
	CEditorsController::OpenOrCreateWithTypeAndID(mRezMapTable, 'styl', mRezObj->GetID(), &stylRezObj);
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


// ---------------------------------------------------------------------------------
//  ¥ NameNewEditorDoc
// ---------------------------------------------------------------------------------

void
CIcon_EditorDoc::NameNewEditorDoc()
{
	Str255 theTitle;
	
	// Build the title
	BuildDocumentTitle(theTitle, index_TEXTEditUntitled);
	// Set window title
	mIconEditWindow->SetDescriptor(theTitle);
}


PP_End_Namespace_PowerPlant


