// ===========================================================================
// CPluginEditorDoc.cp
// 
//                       Created: 2005-10-02 08:41:52
//             Last modification: 2006-02-22 00:23:03
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
	
	mKind = editor_kindPlug;
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
	
	// Ask the plugin its initial requirements
	RezPlugInfo			plugInfo;
	RezHostInfo 		hostInfo;
	
	plugInfo.error = noErr;
	
	if ( (*interface)->AcceptResource(interface, mRezObj->GetType(), mRezObj->GetID(), rezData, &plugInfo) ) {
		// Create a window for our document and set this doc as its the SuperCommander
		mPluginWindow = CreatePluginWindow(plugInfo.winattrs, plugInfo.winbounds);
		Assert_( mPluginWindow != nil );
		
		mPluginWindow->SetPlugRef(plugInfo.plugref);
		
		SetMainWindow( dynamic_cast<CEditorWindow *>(mPluginWindow) );
		NameNewEditorDoc();
		mPluginWindow->FinalizeEditor(this, &(plugInfo.winattrs));
		
		// Create the plugin menus
		hostInfo.menucount = mPlugin->CreateMenus(plugInfo.menucount, plugInfo.menuIDs);
		
		// Fill the reply structure
		hostInfo.winref = mPluginWindow->GetMacWindow();
		
		MenuRef * theMenuRefs = (MenuRef *) malloc( sizeof(MenuRef) * hostInfo.menucount);
		if (theMenuRefs != NULL) {
			TArray<LMenu*>* menusListPtr = mPlugin->GetMenusList();

			TArrayIterator<LMenu*> iterator(*menusListPtr);
			LMenu *	theMenu;
			int 	i = 0;
			while (iterator.Next(theMenu)) {
				theMenuRefs[i] = theMenu->GetMacMenuH();
				i++;
			}
			hostInfo.menurefs = theMenuRefs;
		}
		
		mPluginWindow->GetContentsRect(hostInfo.contents);
	} else {
		error = plugInfo.error;
	}
	
	if (error == noErr) {
		// Now pass the info struct to the plugin for editing
		error = (*interface)->EditResource((RezPlugRef) this, hostInfo);
	}
	
	if (error != noErr) {
		if (error != userCanceledErr) {
			ReportPluginError(CFSTR("ErrorUsingPluginEditor"), error);
		} 
		delete this;
		return;
	} 
	
	// Make the window visible.
	mPluginWindow->Show();
	
	// Enable all the subpanes
	mPluginWindow->Enable();
	mPluginWindow->Activate();

	SwitchTarget(mPluginWindow);
	
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
//   GetModifiedResource											[public]
// ---------------------------------------------------------------------------

Handle
CPluginEditorDoc::GetModifiedResource(Boolean &releaseIt) 
{
	Handle	theHandle = NULL;
	OSErr	error = noErr;

	SRezillaPluginInterface** interface = mPlugin->GetInterface();
	theHandle = (*interface)->ReturnResource(mPluginWindow->GetPlugRef(), &releaseIt, &error);

	if ( error != noErr ) {
		ReportPluginError(CFSTR("ErrorSavingPluginWindow"), error);
	} 
	
	return theHandle;
}

 
// ---------------------------------------------------------------------------
//   CreatePluginWindow												[public]
// ---------------------------------------------------------------------------
// Create the plugin window in compositing mode

CPluginEditorWindow *
CPluginEditorDoc::CreatePluginWindow(SInt32 inPlugAttrs, Rect inWinbounds) 
{
	WindowRef				winRef;
	WindowAttributes		winAttrs = kWindowCloseBoxAttribute | kWindowCompositingAttribute;
	CPluginEditorWindow *	thePluginWindow = nil;

	if (inPlugAttrs & kPlugWinHasCollapseBox) {
		winAttrs |= kWindowFullZoomAttribute | kWindowCollapseBoxAttribute;
	}
	
	if (inPlugAttrs & kPlugWinIsResizable) {
		winAttrs |= kWindowResizableAttribute;
	}
	
	::CreateNewWindow(kDocumentWindowClass, winAttrs, &inWinbounds, &winRef);
	
	// Make a CPluginEditorWindow object out of the WindowRef
	thePluginWindow = new CPluginEditorWindow(winRef, this);
	
	return thePluginWindow;
}

 
// ---------------------------------------------------------------------------
//   ReportPluginError												[public]
// ---------------------------------------------------------------------------
// Create the plugin window in compositing mode

void
CPluginEditorDoc::ReportPluginError(CFStringRef inCFStringRef, SInt32 inError) 
{
	if (inError >= plugErr_Generic && inError < plugErr_LastError) {
		UMessageDialogs::DescribeError(inCFStringRef, inError);
	} else {
		UMessageDialogs::AlertWithValue(inCFStringRef, inError);
	}
}

 

PP_End_Namespace_PowerPlant


