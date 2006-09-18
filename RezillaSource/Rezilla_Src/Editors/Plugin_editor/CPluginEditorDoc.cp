// ===========================================================================
// CPluginEditorDoc.cp
// 
//                       Created: 2005-10-02 08:41:52
//             Last modification: 2006-03-08 09:15:31
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

#include <UCursor.h>

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
	if (mMenuRefs != nil) {
		free(mMenuRefs);
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
	
	mAttributes = 0;
	mMenuRefs = NULL;
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
	
	SPluginEditorInterface** interface = mPlugin->GetInterface();
	ThrowIfNil_(interface);
	
	// Install the contents
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
	
	UCursor::SetWatch();		// May take a little while
	
	plugInfo.error = noErr;
	
	if ( (*interface)->AcceptResource(interface, mRezObj->GetType(), mRezObj->GetID(), rezData, &plugInfo) ) {
		mAttributes = plugInfo.attributes;
		
		// Create a window for our document and set this doc as its SuperCommander
		mPluginWindow = CreatePluginWindow(plugInfo.attributes, plugInfo.winbounds);
		Assert_( mPluginWindow != nil );
		
		// See LWindow::CreateWindow()
		SetDefaultCommander(this);
		SetDefaultAttachable(nil);

		mPluginWindow->SetPlugRef(plugInfo.plugref);
		
		SetMainWindow( dynamic_cast<CEditorWindow *>(mPluginWindow) );
		NameNewEditorDoc();
		mPluginWindow->FinalizeEditor(this, NULL);
		
		// Create the plugin menus
		hostInfo.menucount = mPlugin->CreateMenus(plugInfo.menucount, plugInfo.menuIDs);
		
		// Fill the reply structure
		hostInfo.bundleref = ::CFPlugInGetBundle( mPlugin->GetPluginRef() );
		hostInfo.winref = mPluginWindow->GetMacWindow();
		hostInfo.readonly = IsReadOnly();
		if (mRezObj != nil) {
			hostInfo.refnum = mRezObj->GetOwnerRefnum();
		} else {
			hostInfo.refnum = kResFileNotOpened;
		}
		
		if (hostInfo.menucount > 0) {
			mMenuRefs = (MenuRef *) malloc( sizeof(MenuRef) * hostInfo.menucount);
			if (mMenuRefs != NULL) {
				TArray<LMenu*>* menusListPtr = mPlugin->GetMenusList();

				TArrayIterator<LMenu*> iterator(*menusListPtr);
				LMenu *	theMenu;
				int 	i = 0;
				while (iterator.Next(theMenu)) {
					mMenuRefs[i] = theMenu->GetMacMenuH();
					i++;
				}
			}
		} 
		hostInfo.menurefs = mMenuRefs;

		mPluginWindow->GetContentsRect(hostInfo.editrect);
	} else {
		error = plugInfo.error;
	}
	
	if (error == noErr) {
		// Now pass the info struct to the plugin for editing
		error = (*interface)->EditResource(plugInfo.plugref, hostInfo);
	}
	
	if (error != noErr) {
		if (error != userCanceledErr) {
			ReportPluginError(CFSTR("ErrorUsingPluginEditor"), error);
		} 
		delete this;
		return;
	} 
	
// 	// Attach an LUndoer
// 	AddAttachment( new LUndoer );
	
	// Make the window visible.
	mPluginWindow->Show();
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
				
		default: 
// 		cmdHandled = GetSuperCommander()->ObeyCommand(inCommand, ioParam);
		cmdHandled = CEditorDoc::ObeyCommand(inCommand, ioParam);
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
			outEnabled = false;
		break;

		case cmd_Import:
		LString::CopyPStr( "\pImport...", outName);
		outEnabled = HasAttribute(kPluginSupportImport);
		break;
				
		case cmd_Export:
		LString::CopyPStr( "\pExport...", outName);
		outEnabled = HasAttribute(kPluginSupportExport);
		break;
				
		case cmd_Revert:
		outEnabled = HasAttribute(kPluginEditorHasRevertButton);
		break;
				
		case cmd_Close : 
		outEnabled = true;
		break;
								
		case cmd_Cut:
		outEnabled = ( !mReadOnly && HasAttribute(kPluginSupportCut));
		break;

		case cmd_Copy:
		outEnabled = HasAttribute(kPluginSupportCopy);
		break;
		
		case cmd_Paste:
		outEnabled = ( !mReadOnly && HasAttribute(kPluginSupportPaste));
		break;

		case cmd_Clear:
		outEnabled = ( !mReadOnly && HasAttribute(kPluginSupportClear));
		break;

		case cmd_SelectAll:
		outEnabled = ( !mReadOnly && HasAttribute(kPluginSupportSelectAll));
		break;		
		
		case cmd_Find:
		LString::CopyPStr( "\pFind...", outName);
		outEnabled = HasAttribute(kPluginSupportFind);
		break;

		case cmd_FindNext:
		outEnabled = HasAttribute(kPluginSupportFindNext);
		break;

		default:
		// Call inherited
		CEditorDoc::FindCommandStatus( inCommand,
				outEnabled, outUsesMark, outMark, outName );
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

	SPluginEditorInterface** interface = mPlugin->GetInterface();
	theHandle = (*interface)->ReturnResource(mPluginWindow->GetPlugRef(), &releaseIt, &error);

	if ( error != noErr ) {
		ReportPluginError(CFSTR("ErrorSavingPluginWindow"), error);
	} 
	
	return theHandle;
}

 
// ---------------------------------------------------------------------------
//   CreatePluginWindow												[public]
// ---------------------------------------------------------------------------
// Create the plugin window in compositing mode (kWindowCompositingAttribute) 
// and enable the standard Carbon events (kWindowStandardHandlerAttribute)

CPluginEditorWindow *
CPluginEditorDoc::CreatePluginWindow(SInt32 inPlugAttrs, Rect inWinbounds) 
{
	WindowRef				winRef;
	WindowAttributes		winAttrs = kWindowCloseBoxAttribute 
									| kWindowStandardHandlerAttribute 
									| kWindowCompositingAttribute;
	CPluginEditorWindow *	thePluginWindow = nil;
	OSStatus				error;
	EventTypeSpec			winSpec[] = { {kEventClassCommand, kEventCommandProcess},
									  {kEventClassWindow, kEventWindowClose},
									  {kEventClassWindow, kEventWindowBoundsChanged},
									  {kEventClassWindow, kEventWindowActivated},
									  {kEventClassWindow, kEventWindowDeactivated} };

	if (inPlugAttrs & kPluginWinHasCollapseBox) {
		winAttrs |= kWindowFullZoomAttribute | kWindowCollapseBoxAttribute;
	}
	
	if (inPlugAttrs & kPluginWinIsResizable) {
		winAttrs |= kWindowResizableAttribute;
	}
	
	::CreateNewWindow(kDocumentWindowClass, winAttrs, &inWinbounds, &winRef);
	
	// Make a CPluginEditorWindow object out of the WindowRef
	thePluginWindow = new CPluginEditorWindow(winRef, this);
	
	error = InstallWindowEventHandler(winRef, 
									  NewEventHandlerUPP(CPluginEditorWindow::WindowEventHandler),
									  GetEventTypeCount(winSpec), winSpec, 
									  (void *) thePluginWindow, NULL);
	
	thePluginWindow->CreateControls(inPlugAttrs);
		
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


