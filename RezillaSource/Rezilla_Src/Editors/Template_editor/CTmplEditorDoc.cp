// ===========================================================================
// CTmplEditorDoc.cp					
// 
//                       Created: 2004-06-12 10:06:22
//             Last modification: 2004-06-12 15:16:01
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
						   Boolean inReadOnly)
 	: CEditorDoc(inSuper, inSuperMap, inRezObj, inReadOnly)
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
// 	// Remove ourselves from the list of listeners to the prefs object
// 	CRezillaApp::sPrefs->RemoveListener(this);
}


// ---------------------------------------------------------------------------
//	¥ Initialize													  [public]
// ---------------------------------------------------------------------------

void
CTmplEditorDoc::Initialize()
{
// 	mSearchString[0] = 0;
// 	mMatchStart = 0;
// 	mMatchEnd = 0;
// 	mSearchWhichPane = item_FindInHexRadio;
// 	mIgnoreCase = true;
	
	// Create window for our document.
	mTmplEditWindow = dynamic_cast<CTmplEditorWindow *>(LWindow::CreateWindow( rPPob_TmplEditorWindow, this ));
	Assert_( mTmplEditWindow != nil );
	
	mTmplEditWindow->SetSuperCommander(this);
	mTmplEditWindow->SetOwnerDoc(this);
	mTmplEditWindow->InstallReadOnlyIcon();

	NameNewEditorDoc();
	
	// Add the window to the window menu.
	gWindowMenu->InsertWindow( mTmplEditWindow );
	
	// Install the contents according to the TMPL
	if (mRezObj != nil) {
		Handle rezData = mRezObj->GetData();
		
		if (rezData != nil) {
			mTmplEditWindow->ParseWithTemplate(rezData);						
		} 
	} 
	
	// Make the window visible.
	mTmplEditWindow->Show();
	
// 	mTmplEditWindow->GetContentsView()->Activate();
}


// ---------------------------------------------------------------------------
//	¥ ObeyCommand									[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CTmplEditorDoc::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;	// Assume we'll handle the command
	
	switch (inCommand) {
		
		case cmd_Close : 
		AttemptClose(false);
		break;
				
		default: {
			cmdHandled = LDocument::ObeyCommand(inCommand, ioParam);
			break;
		}
	}
	
	return cmdHandled;
}


// ---------------------------------------------------------------------------------
//  ¥ IsModified
// ---------------------------------------------------------------------------------

Boolean
CTmplEditorDoc::IsModified()
{
	// Document has changed if the text views are dirty
	mIsModified = mTmplEditWindow->IsDirty();
	return mIsModified;
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
	
		case cmd_Save:
		case cmd_SaveAs:
		case cmd_ExportMap:
			outEnabled = false;
		break;
								
	  default:
		{
			// Call inherited.
			LDocument::FindCommandStatus( inCommand,
				outEnabled, outUsesMark, outMark, outName );
		}
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
	return UMessageDialogs::AskYesNoFromLocalizable(CFSTR("SaveTemplateWindow"), rPPob_AskYesNoMessage);
}



// ---------------------------------------------------------------------------
//  ¥ GetModifiedResource										[public]
// ---------------------------------------------------------------------------

Handle
CTmplEditorDoc::GetModifiedResource() 
{
	return mTmplEditWindow->ReadValues();
}


// // ---------------------------------------------------------------------------
// //  ¥ ListenToMessage													[public]
// // ---------------------------------------------------------------------------
// 
// void
// CTmplEditorDoc::ListenToMessage( MessageT inMessage, void *ioParam ) 
// {
// 	switch (inMessage) {
// 		case msg_StylePrefsChanged: {
// 		 
// 			break;
// 		
// 	}
// }
// 
// 

PP_End_Namespace_PowerPlant


