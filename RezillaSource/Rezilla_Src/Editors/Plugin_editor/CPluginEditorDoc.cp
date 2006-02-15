// ===========================================================================
// CPluginEditorDoc.cp
// 
//                       Created: 2005-10-02 08:41:52
//             Last modification: 2005-10-02 09:21:41
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// ===========================================================================

PP_Begin_Namespace_PowerPlant


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CRezillaApp.h"
#include "CPluginEditorDoc.h"
#include "CPluginEditorWindow.h"
#include "CRezillaPlugin.h"

#include "CRezFile.h"
#include "CRezMapDoc.h"
#include "CRezMapTable.h"
#include "CRezObj.h"
#include "CRezObjItem.h"
#include "RezillaConstants.h"
#include "UMessageDialogs.h"
#include "UMiscUtils.h"


// #include <LString.h>
// #include <UStandardDialogs.h>

// // Standard headers
// #include <string.h>


// ---------------------------------------------------------------------------
//	¥ CPluginEditorDoc								Constructor		  [public]
// ---------------------------------------------------------------------------

CPluginEditorDoc::CPluginEditorDoc(LCommander* inSuper, 
						   CRezMapTable* inSuperMap, 
						   CRezObj* inRezObj,
						   ResType inSubstType,
						   Boolean inReadOnly)
	: CEditorDoc(inSuper, inSuperMap, inRezObj, inSubstType, inReadOnly)
{
	Initialize();
}


// ---------------------------------------------------------------------------
//	¥ ~CPluginEditorDoc							Destructor				  [public]
// ---------------------------------------------------------------------------

CPluginEditorDoc::~CPluginEditorDoc()
{
	if (mPluginWindow != nil) {
		delete mPluginWindow;
	} 
}


// ---------------------------------------------------------------------------
//	¥ Initialize													  [public]
// ---------------------------------------------------------------------------

void
CPluginEditorDoc::Initialize()
{
	OSErr error;
	
	mKind = editor_kindTmpl;
	SetModelKind(rzom_cTmplEditDoc);

	// Create window for our document. This sets this doc as the SuperCommander of the window.
	mPluginWindow = dynamic_cast<CPluginEditorWindow *>(LWindow::CreateWindow( PPob_PluginEditorWindow, this ));
	Assert_( mPluginWindow != nil );
	
	SetMainWindow( dynamic_cast<CEditorWindow *>(mPluginWindow) );
	NameNewEditorDoc();
	mPluginWindow->FinalizeEditor(this);

	// Install the contents according to the TMPL
	if (mRezObj != nil) {
		Handle rezData = mRezObj->GetData();
		if (rezData != nil) {
			// Work with a copy of the handle
			::HandToHand(&rezData);
			
			try {
// 				error = mPluginWindow->ParseDataWithTemplate(rezData);						
			} catch (...) {
				error = err_ExceptionParsingTemplate;
			}
		} 
	} 
	
	if (error != noErr) {
		if (error == err_ExceptionParsingTemplate) {
			UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("TemplateParsingException"), PPob_SimpleMessage);
		} else if (error != userCanceledErr) {
			UMessageDialogs::DescribeError(CFSTR("ErrorParsingWithTemplate"), error);
		} 
		delete this;
		return;
	} 

// 	// Make the window visible.
// 	mPluginWindow->Show();
// 	// Enable all the subpanes
// 	mPluginWindow->GetContentsView()->Enable();
}


// ---------------------------------------------------------------------------
//	¥ ObeyCommand									[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CPluginEditorDoc::ObeyCommand(
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
//  ¥ FindCommandStatus
// ---------------------------------------------------------------------------------

void
CPluginEditorDoc::FindCommandStatus(
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
		LString::CopyPStr( "\pFind�", outName);
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
//  ¥ ListenToMessage													[public]
// ---------------------------------------------------------------------------

void
CPluginEditorDoc::ListenToMessage( MessageT inMessage, void * /* ioParam */) 
{
	switch (inMessage) {
		case msg_EditorValidate:
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
//	¥ AllowSubRemoval												  [public]
// ---------------------------------------------------------------------------

Boolean
CPluginEditorDoc::AllowSubRemoval(
	LCommander* /* inSub */)
{
	return true;
}


// ---------------------------------------------------------------------------
//	¥ AskSaveChanges												  [public]
// ---------------------------------------------------------------------------
//	Ask user whether to save changes before closing the Document or
//	quitting the Application.

SInt16
CPluginEditorDoc::AskSaveChanges(
	bool /* inQuitting */)
{
	return UMessageDialogs::AskYesNoFromLocalizable(CFSTR("SaveModifiedResource"), PPob_AskYesNoMessage);
}


// ---------------------------------------------------------------------------
//	¥ GetDescriptor													  [public]
// ---------------------------------------------------------------------------
//	Pass back the name of a Document

StringPtr
CPluginEditorDoc::GetDescriptor(
	Str255	outDescriptor) const
{
	if (mPluginWindow != nil) {
		// Use name of its window
		mPluginWindow->GetDescriptor(outDescriptor);
	} else {
		// No window, document name is empty string
		outDescriptor[0] = 0;		
	}

	return outDescriptor;
}


// ---------------------------------------------------------------------------
//  ¥ GetModifiedResource										[public]
// ---------------------------------------------------------------------------
// The returned handle should not be released by the caller so leave
// releaseIt to false (its default).

Handle
CPluginEditorDoc::GetModifiedResource(Boolean &releaseIt) 
{
	Handle theHandle = NULL;
	OSErr error =noErr;

// 	mPluginWindow->RetrieveDataWithTemplate();

	if ( error != noErr ) {
		UMessageDialogs::DescribeError(CFSTR("ErrorWhileSavingTemplateWindow"), error);
	} else {
// 		if (mPluginWindow->GetOutStream() != NULL) {
// 			theHandle = mPluginWindow->GetOutStream()->GetDataHandle();
// 		} 
	}
	
	return theHandle;
}

 

PP_End_Namespace_PowerPlant


