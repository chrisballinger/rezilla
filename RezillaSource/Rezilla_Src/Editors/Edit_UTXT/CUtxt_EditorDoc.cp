// ===========================================================================
// CUtxt_EditorDoc.cp
// 
//                       Created: 2004-12-08 18:21:21
//             Last modification: 2004-12-27 14:43:26
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

#include "CUtxt_EditorDoc.h"
#include "CUtxt_EditorWindow.h"
#include "CUtxt_EditorView.h"
#include "RezillaConstants.h"
#include "CRezObj.h"
#include "CRezMap.h"
#include "CRezMapTable.h"
#include "CWindowMenu.h"
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

extern CWindowMenu * gWindowMenu;


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
		// Remove the window from the window menu.
		gWindowMenu->RemoveWindow( mUtxtEditWindow );
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
	
	mUtxtEditWindow->SetOwnerDoc(this);
	mUtxtEditWindow->InstallResourceNameField();
	mUtxtEditWindow->InstallReadOnlyIcon();
	SetMainWindow( dynamic_cast<CEditorWindow *>(mUtxtEditWindow) );

	NameNewEditorDoc();
	
	// Add the window to the window menu.
	gWindowMenu->InsertWindow( mUtxtEditWindow );
		
	// Install the contents according to the TMPL
	if (mRezObj != nil) {
		Handle rezData = mRezObj->GetData();
		
		if (rezData != nil) {
			Handle			theScrapHandle = NULL;
			StResource		initialStyleRes;
			CRezMap *		theRezMap = mRezMapTable->GetRezMap();

			mUtxtEditWindow->InstallText(rezData);			
		} 
	} 
	
// 	mUtxtEditWindow->AdjustMenusToSelection();
	mUtxtEditWindow->SetLengthField();
	
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

Handle
CUtxt_EditorDoc::GetModifiedResource() 
{
	return mUtxtEditWindow->GetContentsView()->GetModifiedText();
}



PP_End_Namespace_PowerPlant


