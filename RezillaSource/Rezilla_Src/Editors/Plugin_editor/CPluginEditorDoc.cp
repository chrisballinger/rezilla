// ===========================================================================
// CPluginEditorDoc.cp
// 
//                       Created: 2005-10-02 08:41:52
//             Last modification: 2006-02-21 07:12:32
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2005-2006
// All rights reserved.
// ===========================================================================

PP_Begin_Namespace_PowerPlant


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CRezillaApp.h"
#include "RezillaPluginInterface.h"
#include "CPluginEditorDoc.h"
#include "CPluginEditorWindow.h"
#include "CPluginEditorView.h"
#include "CRezillaPlugin.h"
#include "CRezFile.h"
#include "CRezMapDoc.h"
#include "CRezMapTable.h"
#include "CRezMap.h"
#include "CRezObj.h"
#include "CRezObjItem.h"
#include "RezillaConstants.h"
#include "UMessageDialogs.h"
#include "UMiscUtils.h"


// ---------------------------------------------------------------------------
//   CPluginEditorDoc								Constructor		  [public]
// ---------------------------------------------------------------------------

CPluginEditorDoc::CPluginEditorDoc(
						   LCommander * inSuper, 
						   CRezMapTable * inSuperMap, 
						   CRezObj* inRezObj,
						   ResType inSubstType,
						   Boolean inReadOnly,
						   CRezillaPlugin * inPlugin)
	: CEditorDoc(inSuper, inSuperMap, inRezObj, inSubstType, inReadOnly)
{
	mPlugin = inPlugin;
	Initialize();
}


// ---------------------------------------------------------------------------
//     ~CPluginEditorDoc							Destructor				  [public]
// ---------------------------------------------------------------------------

CPluginEditorDoc::~CPluginEditorDoc()
{
	if (mPluginWindow != nil) {
		delete mPluginWindow;
	} 
}


// ---------------------------------------------------------------------------
//   Initialize													  [public]
// ---------------------------------------------------------------------------

void
CPluginEditorDoc::Initialize()
{
	OSErr	error = noErr;
	Handle	rezData;
	
	ThrowIfNil_(mPlugin);
	
	mKind = editor_kindPlugin;
	SetModelKind(rzom_cPlugEditDoc);

	// Check if the plugin has already been loaded. If not, load it.
	if (! mPlugin->IsLoaded() ) {
		try {
			error = mPlugin->Load();
		} catch (...) {
			error = err_PluginLoadFailed;
		}
	} 
	
	SRezillaPluginInterface** interface = mPlugin->GetInterface();
	ThrowIfNil_(interface);
	
	// Install the contents according to the TMPL
	if (mRezObj != nil) {
		rezData = mRezObj->GetData();
		if (rezData != nil) {
			// Work with a copy of the handle
			::HandToHand(&rezData);
		} 
	} 
	
	// Ask the plugin its requirements
	RezPluginRequirements	plugReq;
	RezPluginInfo 			rpi;
	plugReq.error = noErr;
	
	if ( (*interface)->AcceptResource(interface, mRezObj->GetType(), mRezObj->GetID(), rezData, &plugReq) ) {
		// Create a window for our document. This sets this doc as the SuperCommander of the window.
		mPluginWindow = dynamic_cast<CPluginEditorWindow *>(LWindow::CreateWindow( PPob_PluginEditorWindow, this ));
		Assert_( mPluginWindow != nil );
		
		mPluginWindow->MoveWindowTo(plugReq.winbounds.top, plugReq.winbounds.left);
		mPluginWindow->ResizeWindowTo(plugReq.winbounds.right - plugReq.winbounds.left,
									 plugReq.winbounds.bottom - plugReq.winbounds.top);
		
		SetMainWindow( dynamic_cast<CEditorWindow *>(mPluginWindow) );
		NameNewEditorDoc();
		mPluginWindow->FinalizeEditor(this, &(plugReq.winattrs));
		
		// Create the plugin menus
		rpi.menucount = mPlugin->CreateMenus(plugReq.menucount, plugReq.menuIDs);
		
		// Fill the reply structure
		rpi.plugref = (RezPlugRef) this;
		rpi.winref = mPluginWindow->GetMacWindow();
		
		MenuRef * theMenuRefs = (MenuRef *) malloc( sizeof(MenuRef) * rpi.menucount);
		if (theMenuRefs != NULL) {
			TArray<LMenu*>* menusListPtr = mPlugin->GetMenusList();

			TArrayIterator<LMenu*> iterator(*menusListPtr);
			LMenu *	theMenu;
			int 	i = 0;
			while (iterator.Next(theMenu)) {
				theMenuRefs[i] = theMenu->GetMacMenuH();
				i++;
			}
			rpi.menurefs = theMenuRefs;
		} 
	} else {
		error = plugReq.error;
	}
	
	if (error != noErr) {
		if (error == err_ExceptionParsingTemplate) {
			UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("TemplateParsingException"), PPob_SimpleMessage);
		} else if (error != userCanceledErr) {
			UMessageDialogs::DescribeError(CFSTR("ErrorEditingWithPlugin"), error);
		} 
		delete this;
		return;
	} 
	
	// Now pass the info struct to the plugin for editing
	(*interface)->EditResource(interface, rpi);
	
	// Make the window visible.
	mPluginWindow->Show();
	
	// Enable all the subpanes
	mPluginWindow->GetContentsView()->Enable();
}


// ---------------------------------------------------------------------------
//   ObeyCommand									[public, virtual]
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
//   FindCommandStatus
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
		LString::CopyPStr( "\pFindÉ", outName);
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
//   AllowSubRemoval												  [public]
// ---------------------------------------------------------------------------

Boolean
CPluginEditorDoc::AllowSubRemoval(
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
CPluginEditorDoc::AskSaveChanges(
	bool /* inQuitting */)
{
	return UMessageDialogs::AskYesNoFromLocalizable(CFSTR("SaveModifiedResource"), PPob_AskYesNoMessage);
}


// ---------------------------------------------------------------------------
//   GetDescriptor													  [public]
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
//   GetModifiedResource										[public]
// ---------------------------------------------------------------------------
// The returned handle should not be released by the caller so leave
// releaseIt to false (its default).

Handle
CPluginEditorDoc::GetModifiedResource(Boolean &releaseIt) 
{
	Handle	theHandle = NULL;
	OSErr	error = noErr;

	SRezillaPluginInterface** interface = mPlugin->GetInterface();
	theHandle = (*interface)->ReturnResource(interface, &releaseIt, &error);

	if ( error != noErr ) {
		UMessageDialogs::DescribeError(CFSTR("ErrorSavingPluginWindow"), error);
	} 
	
	return theHandle;
}

 

PP_End_Namespace_PowerPlant


