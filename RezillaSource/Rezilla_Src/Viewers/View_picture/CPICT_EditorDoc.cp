// ===========================================================================
// CPICT_EditorDoc.cp
// 
//                       Created: 2004-12-06 14:54:09
//             Last modification: 2004-12-06 20:36:29
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

#include "CPICT_EditorDoc.h"
#include "CPICT_EditorWindow.h"
#include "CPICT_EditorView.h"
#include "RezillaConstants.h"
#include "CRezObj.h"
#include "CWindowMenu.h"
#include "UCodeTranslator.h"
#include "UDialogBoxHandler.h"
#include "UMessageDialogs.h"
#include "UMiscUtils.h"

#include <LWindow.h>
#include <UStandardDialogs.h>
#include <LRadioGroupView.h>

#include <LString.h>
#include <PP_Messages.h>

// // Standard headers
// #include <string.h>


extern CWindowMenu * gWindowMenu;


// ---------------------------------------------------------------------------
//	¥ CPICT_EditorDoc							Constructor		  [public]
// ---------------------------------------------------------------------------

CPICT_EditorDoc::CPICT_EditorDoc(LCommander* inSuper, 
								 CRezMapTable* inSuperMap,
								 CRezObj* inRezObj,
								 ResType inSubstType,
								 Boolean inReadOnly)
 	: CEditorDoc(inSuper, inSuperMap, inRezObj, inSubstType, inReadOnly)
{
	Initialize();
}


// ---------------------------------------------------------------------------
//	¥ ~CPICT_EditorDoc							Destructor			  [public]
// ---------------------------------------------------------------------------

CPICT_EditorDoc::~CPICT_EditorDoc()
{
	if (mPictWindow != nil) {
		// Remove the window from the window menu.
		gWindowMenu->RemoveWindow( mPictWindow );
		delete mPictWindow;
	} 
}


// ---------------------------------------------------------------------------
//	¥ Initialize													  [public]
// ---------------------------------------------------------------------------

void
CPICT_EditorDoc::Initialize()
{
	// Create window for our document. This sets this doc as the SuperCommander of the window.
	mPictWindow = dynamic_cast<CPICT_EditorWindow *>(LWindow::CreateWindow( PPob_PictEditorWindow, this ));
	Assert_( mPictWindow != nil );
	
	mPictWindow->SetOwnerDoc(this);
	mPictWindow->InstallReadOnlyIcon();
	SetMainWindow( dynamic_cast<CEditorWindow *>(mPictWindow) );

	NameNewEditorDoc();
	
	// Add the window to the window menu.
	gWindowMenu->InsertWindow( mPictWindow );
		
	// Install the contents
	if (mRezObj != nil) {
		Handle rezData = mRezObj->GetData();
		
		if (rezData != nil) {			
			// Work with a copy of the handle
			::HandToHand(&rezData);
			mPictWindow->InstallPict(rezData);
			
			// Don't mark as modified
			mPictWindow->SetDirty(false);
		} 
	} 
		
	// Make the window visible.
	mPictWindow->Show();
}


// ---------------------------------------------------------------------------
//	¥ GetDescriptor													  [public]
// ---------------------------------------------------------------------------
//	Pass back the name of a Document

StringPtr
CPICT_EditorDoc::GetDescriptor(
	Str255	outDescriptor) const
{
	if (mPictWindow != nil) {
		// Use name of its window
		mPictWindow->GetDescriptor(outDescriptor);
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
CPICT_EditorDoc::FindCommandStatus(
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
CPICT_EditorDoc::AllowSubRemoval(
	LCommander*		inSub)
{
	if (inSub == mPictWindow) {
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
CPICT_EditorDoc::AskSaveChanges(
	bool /* inQuitting */)
{
	return UMessageDialogs::AskYesNoFromLocalizable(CFSTR("SavePictEditorWindow"), PPob_AskYesNoMessage);
}


// ---------------------------------------------------------------------------
//  ¥ GetModifiedResource										[protected]
// ---------------------------------------------------------------------------

Handle
CPICT_EditorDoc::GetModifiedResource() 
{
	return (Handle) mPictWindow->GetContentsView()->GetPictureH();
}


// ---------------------------------------------------------------------------------
//  ¥ NameNewEditorDoc
// ---------------------------------------------------------------------------------

void
CPICT_EditorDoc::NameNewEditorDoc()
{
	Str255 theTitle;
	
	// Build the title
	BuildDocumentTitle(theTitle, index_TEXTEditUntitled);
	// Set window title
	mPictWindow->SetDescriptor(theTitle);
}


PP_End_Namespace_PowerPlant


