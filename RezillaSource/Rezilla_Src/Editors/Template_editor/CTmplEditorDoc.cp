// ===========================================================================
// CTmplEditorDoc.cp					
// 
//                       Created: 2004-06-12 10:06:22
//             Last modification: 2005-01-02 15:28:56
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

PP_Begin_Namespace_PowerPlant


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CTmplEditorDoc.h"
#include "CTmplEditorWindow.h"
#include "RezillaConstants.h"
#include "CRezFile.h"
#include "CRezMap.h"
#include "CRezMapDoc.h"
#include "CRezObj.h"
#include "CRezillaApp.h"
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
//	¥ CTmplEditorDoc							Constructor		  [public]
// ---------------------------------------------------------------------------
// 	: CEditorController( inSuperMap )

CTmplEditorDoc::CTmplEditorDoc(LCommander* inSuper, 
							   CRezMapTable* inSuperMap, 
							   CRezObj* inRezObj,
							   ResType inSubstType,
							   Boolean inReadOnly)
 	: CEditorDoc(inSuper, inSuperMap, inRezObj, inSubstType, inReadOnly)
{
	Initialize();
}


// ---------------------------------------------------------------------------
//	¥ ~CTmplEditorDoc							Destructor				  [public]
// ---------------------------------------------------------------------------

CTmplEditorDoc::~CTmplEditorDoc()
{
	if (mTmplEditWindow != nil) {
		// Remove the window from the window menu.
		gWindowMenu->RemoveWindow( mTmplEditWindow );
		delete mTmplEditWindow;
	} 
}


// ---------------------------------------------------------------------------
//	¥ Initialize													  [public]
// ---------------------------------------------------------------------------

void
CTmplEditorDoc::Initialize()
{
	OSErr error;
	
	mKind = editor_kindTmpl;

	// Create window for our document. This sets this doc as the SuperCommander of the window.
	mTmplEditWindow = dynamic_cast<CTmplEditorWindow *>(LWindow::CreateWindow( PPob_TmplEditorWindow, this ));
	Assert_( mTmplEditWindow != nil );
	
	mTmplEditWindow->SetOwnerDoc(this);
	mTmplEditWindow->InstallResourceNameField();
	mTmplEditWindow->InstallReadOnlyIcon();
	SetMainWindow( dynamic_cast<CEditorWindow *>(mTmplEditWindow) );

	NameNewEditorDoc();
	
	// Add the window to the window menu.
	gWindowMenu->InsertWindow( mTmplEditWindow );
	
	// Install the contents according to the TMPL
	if (mRezObj != nil) {
		Handle rezData = mRezObj->GetData();
		if (rezData != nil) {
			// Work with a copy of the handle
			::HandToHand(&rezData);
			
			try {
				error = mTmplEditWindow->ParseDataWithTemplate(rezData);						
			} catch (...) {
				error = err_ExceptionParsingTemplate;
			}
		} 
	} 
	
	if (error != noErr) {
		if (error == err_ExceptionParsingTemplate) {
			UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("TemplateParsingException"), PPob_SimpleMessage);
		} else if (error != userCanceledErr) {
			UMessageDialogs::ErrorWithString(CFSTR("ErrorParsingWithTemplate"), error);
		} 
		delete this;
		return;
	} 

	// Make the window visible.
	mTmplEditWindow->Show();
	// Enable all the subpanes
	mTmplEditWindow->GetContentsView()->Enable();
}


// ---------------------------------------------------------------------------
//	¥ GetDescriptor													  [public]
// ---------------------------------------------------------------------------
//	Pass back the name of a Document

StringPtr
CTmplEditorDoc::GetDescriptor(
	Str255	outDescriptor) const
{
	if (mTmplEditWindow != nil) {
		// Use name of its window
		mTmplEditWindow->GetDescriptor(outDescriptor);
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
CTmplEditorDoc::FindCommandStatus(
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
CTmplEditorDoc::AllowSubRemoval(
	LCommander*		inSub)
{
	if (inSub == mTmplEditWindow) {
		AttemptClose(false);
		return false;
	} else {
		return true;
	}
}


// ---------------------------------------------------------------------------
//	¥ AskSaveChanges												  [public]
// ---------------------------------------------------------------------------
//	Ask user whether to save changes before closing the Document or
//	quitting the Application

SInt16
CTmplEditorDoc::AskSaveChanges(
	bool /* inQuitting */)
{
	return UMessageDialogs::AskYesNoFromLocalizable(CFSTR("SaveTemplateWindow"), PPob_AskYesNoMessage);
}



// ---------------------------------------------------------------------------
//  ¥ GetModifiedResource										[public]
// ---------------------------------------------------------------------------
// The returned handle should not be released by the caller so leave
// releaseIt to false (its default).

Handle
CTmplEditorDoc::GetModifiedResource(Boolean &releaseIt) 
{
	Handle theHandle = NULL;
	OSErr error = mTmplEditWindow->RetrieveDataWithTemplate();

	if ( error != noErr ) {
		UMessageDialogs::ErrorWithString(CFSTR("ErrorWhileSavingTemplateWindow"), error);
	} else {
		if (mTmplEditWindow->GetOutStream() != NULL) {
			theHandle = mTmplEditWindow->GetOutStream()->GetDataHandle();
		} 
	}
	
	return theHandle;
}


PP_End_Namespace_PowerPlant


