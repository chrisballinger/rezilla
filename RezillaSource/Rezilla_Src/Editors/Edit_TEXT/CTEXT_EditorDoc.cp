// ===========================================================================
// CTEXT_EditorDoc.cp
// 
//                       Created: 2004-06-17 12:46:55
//             Last modification: 2004-06-19 15:31:45
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

#include "CTEXT_EditorDoc.h"
#include "CTEXT_EditorWindow.h"
#include "CTEXT_EditorView.h"
#include "RezillaConstants.h"
#include "CRezFile.h"
#include "CRezMap.h"
#include "CRezMapTable.h"
#include "CRezMapDoc.h"
#include "CRezObj.h"
#include "CRezillaApp.h"
#include "CRezillaPrefs.h"
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
//	¥ CTEXT_EditorDoc							Constructor		  [public]
// ---------------------------------------------------------------------------
// 	: CEditorController( inSuperMap )

CTEXT_EditorDoc::CTEXT_EditorDoc(LCommander* inSuper, 
						   CRezMapTable* inSuperMap, 
						   CRezObj* inRezObj,
						   Boolean inReadOnly)
 	: CEditorDoc(inSuper, inSuperMap, inRezObj, inReadOnly)
{
	Initialize();
}


// ---------------------------------------------------------------------------
//	¥ ~CTEXT_EditorDoc							Destructor				  [public]
// ---------------------------------------------------------------------------

CTEXT_EditorDoc::~CTEXT_EditorDoc()
{
	if (mTextEditWindow != nil) {
		// Remove the window from the window menu.
		gWindowMenu->RemoveWindow( mTextEditWindow );
		delete mTextEditWindow;
	} 
}


// ---------------------------------------------------------------------------
//	¥ Initialize													  [public]
// ---------------------------------------------------------------------------

void
CTEXT_EditorDoc::Initialize()
{
// 	mSearchString[0] = 0;
// 	mMatchStart = 0;
// 	mMatchEnd = 0;
// 	mSearchWhichPane = item_FindInHexRadio;
// 	mIgnoreCase = true;
	
	// Create window for our document.
	mTextEditWindow = dynamic_cast<CTEXT_EditorWindow *>(LWindow::CreateWindow( rPPob_TextEditorWindow, this ));
	Assert_( mTextEditWindow != nil );
	
	mTextEditWindow->SetSuperCommander(this);
	mTextEditWindow->SetOwnerDoc(this);
	mTextEditWindow->InstallReadOnlyIcon();

	NameNewEditorDoc();
	
	// Add the window to the window menu.
	gWindowMenu->InsertWindow( mTextEditWindow );
	
	mTextEditWindow->InstallDefaults();
	
	// Install the contents according to the TMPL
	if (mRezObj != nil) {
		Handle rezData = mRezObj->GetData();
		
		if (rezData != nil) {
			StScrpHandle	theScrapHandle = NULL;
			StResource		initialStyleRes;
			CRezMap *		theRezMap = mRezMapTable->GetRezMap();

			// Look for a 'styl' resource with same ID
			Boolean hasStyle = theRezMap->HasResourceWithTypeAndId( ResType_TextStyle, mRezObj->GetID()) ;
			if (hasStyle) {
				initialStyleRes.GetResource(ResType_TextStyle, mRezObj->GetID(), false, true);
				theScrapHandle = (StScrpHandle) initialStyleRes.mResourceH;
			}
						
			mTextEditWindow->InstallText(rezData, theScrapHandle);						
		} 
	} 
	
	mTextEditWindow->SetLengthField();
	
	// Make the window visible.
	mTextEditWindow->Show();
}


// ---------------------------------------------------------------------------
//	¥ ObeyCommand									[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CTEXT_EditorDoc::ObeyCommand(
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
CTEXT_EditorDoc::IsModified()
{
	// Document has changed if the text views are dirty
	mIsModified = mTextEditWindow->IsDirty();
	return mIsModified;
}


// ---------------------------------------------------------------------------
//	¥ GetDescriptor													  [public]
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


// ---------------------------------------------------------------------------------
//  ¥ FindCommandStatus
// ---------------------------------------------------------------------------------

void
CTEXT_EditorDoc::FindCommandStatus(
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
//	¥ AskSaveChanges												  [public]
// ---------------------------------------------------------------------------
//	Ask user whether to save changes before closing the Document or
//	quitting the Application

SInt16
CTEXT_EditorDoc::AskSaveChanges(
	bool /* inQuitting */)
{
	return UMessageDialogs::AskYesNoFromLocalizable(CFSTR("SaveTemplateWindow"), rPPob_AskYesNoMessage);
}



// ---------------------------------------------------------------------------
//  ¥ GetModifiedResource										[public]
// ---------------------------------------------------------------------------

Handle
CTEXT_EditorDoc::GetModifiedResource() 
{
	return mTextEditWindow->ReadValues();
}


// ---------------------------------------------------------------------------------
//  ¥ NameNewEditorDoc
// ---------------------------------------------------------------------------------

void
CTEXT_EditorDoc::NameNewEditorDoc()
{
	Str255 theTitle;
	
	// Build the title
	BuildDocumentTitle(theTitle, index_TmplEditUntitled);
	// Set window title
	mTextEditWindow->SetDescriptor(theTitle);
}


// // ---------------------------------------------------------------------------
// //  ¥ ListenToMessage													[public]
// // ---------------------------------------------------------------------------
// 
// void
// CTEXT_EditorDoc::ListenToMessage( MessageT inMessage, void *ioParam ) 
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


