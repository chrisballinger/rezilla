// ===========================================================================
// CICNS_EditorDoc.cp
// 
//                       Created: 2006-02-23 15:12:16
//             Last modification: 2006-09-11 11:32:54
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================

PP_Begin_Namespace_PowerPlant


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CICNS_EditorDoc.h"
#include "CICNS_EditorWindow.h"
#include "CIcon_EditorView.h"
#include "CEditorsController.h"
#include "RezillaConstants.h"
#include "CRezMap.h"
#include "CRezMapTable.h"
#include "CRezMapDoc.h"
#include "CRezFile.h"
#include "CRezObj.h"
#include "CRezillaPrefs.h"
#include "UCodeTranslator.h"
#include "UDialogBoxHandler.h"
#include "UMessageDialogs.h"
#include "UMiscUtils.h"

#include <LWindow.h>
#include <LFile.h>
#include <UNavigationDialogs.h>
#include <UStandardDialogs.h>
#include <LRadioGroupView.h>
#include <LCheckBox.h>
#include <LEditField.h>
#include <LDataStream.h>

#include <LString.h>
#include <PP_Messages.h>



// ---------------------------------------------------------------------------
//  CICNS_EditorDoc							Constructor		  [public]
// ---------------------------------------------------------------------------

CICNS_EditorDoc::CICNS_EditorDoc(LCommander* inSuper, 
								 CRezMapTable* inSuperMap,
								 CRezObj* inRezObj,
								 ResType inSubstType,
								 Boolean inReadOnly)
 	: CEditorDoc(inSuper, inSuperMap, inRezObj, inSubstType, inReadOnly)
{
	Initialize();
}


// ---------------------------------------------------------------------------
//  ~CICNS_EditorDoc							Destructor		  [public]
// ---------------------------------------------------------------------------

CICNS_EditorDoc::~CICNS_EditorDoc()
{
	if (mIcnsEditWindow != nil) {
		delete mIcnsEditWindow;
	} 
}


// ---------------------------------------------------------------------------
//  Initialize													[public]
// ---------------------------------------------------------------------------

void
CICNS_EditorDoc::Initialize()
{
	OSErr error = noErr;
	
	mIconRef = NULL;
	mIconIsEmpty = true;

	// Create a window for our document and set this doc as its SuperCommander
	mIcnsEditWindow = dynamic_cast<CICNS_EditorWindow *>(LWindow::CreateWindow( PPob_IcnsEditorWindow, this ));
	Assert_( mIcnsEditWindow != nil );
	
	SetMainWindow( dynamic_cast<CEditorWindow *>(mIcnsEditWindow) );
	NameNewEditorDoc();
	mIcnsEditWindow->FinalizeEditor(this);
	
	try {
		// Install the data
		if (mRezObj != nil) {
			Handle rezData = mRezObj->GetData();
			// Work with a copy of the handle
			::HandToHand(&rezData);
			
			if (rezData != NULL) {
				if ( ::GetHandleSize(rezData) > 8 ) {
					mIconIsEmpty = false;
				} 
				error = mIcnsEditWindow->InstallResourceData(rezData);			
			} else {
				error = memFullErr;
			}
			ThrowIfError_(error);
			
		}		
	} catch (...) {
		delete this;
		if (error == err_MoreDataThanExpected) {
			UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("ResourceLongerThanExpected"), PPob_SimpleMessage);
		} else if (error != userCanceledErr) {
			UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("ErrorWhileParsingResource"), error);
		} 
		return;
	}
	
	// Make the window visible
	mIcnsEditWindow->Show();
}


// ---------------------------------------------------------------------------
//  RegisterIcon													  [private]
// ---------------------------------------------------------------------------
// From Icon.h: consider using RegisterIconRefFromResource() if possible,
// since the data registered using RegisterIconRefFromFamily() cannot be
// purged.

OSErr
CICNS_EditorDoc::RegisterIcon()
{
	OSErr error;
	const FSSpec theFSSpec = mRezMapTable->GetOwnerDoc()->GetRezFile()->GetFileSpec();
	error = RegisterIconRefFromResource(kRezillaSig, kIconFamilyType, &theFSSpec, mRezObj->GetID(), &mIconRef);
	return error;	
}


// ---------------------------------------------------------------------------
//  UnregisterIcon													  [private]
// ---------------------------------------------------------------------------

OSErr
CICNS_EditorDoc::UnregisterIcon()
{
	OSErr error = noErr;
	if (mIconRef != NULL) {
		error = ::ReleaseIconRef(mIconRef);
		mIconRef = NULL;		
	} 
	return error;
}


// ---------------------------------------------------------------------------
//  GetDescriptor													  [public]
// ---------------------------------------------------------------------------
//	Pass back the name of a Document

StringPtr
CICNS_EditorDoc::GetDescriptor(
	Str255	outDescriptor) const
{
	if (mIcnsEditWindow != nil) {
		// Use name of its window
		mIcnsEditWindow->GetDescriptor(outDescriptor);
	} else {
		// No window, document name is empty string
		outDescriptor[0] = 0;		
	}

	return outDescriptor;
}


// ---------------------------------------------------------------------------------
//   FindCommandStatus
// ---------------------------------------------------------------------------------

void
CICNS_EditorDoc::FindCommandStatus(
	CommandT	inCommand,
	Boolean		&outEnabled,
	Boolean		&outUsesMark,
	UInt16		&outMark,
	Str255		outName )
{
	switch ( inCommand ) {
	
		case cmd_Import:
		case cmd_Export:
			outEnabled = true;
		break;

	  default:
			// Call inherited.
		CEditorDoc::FindCommandStatus( inCommand,
				outEnabled, outUsesMark, outMark, outName );
		break;

	}
}


// ---------------------------------------------------------------------------
//   ObeyCommand									[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CICNS_EditorDoc::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;	// Assume we'll handle the command
	
	switch (inCommand) {
		
		case cmd_Import:
		if ( !mIconIsEmpty ) {
			UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("CantImportOnExistingICNS"), PPob_SimpleMessage);
		} else {
			ImportICNS();
		}
		break;

		case cmd_Export:
		ExportICNS();
		break;
				
		default: 
		cmdHandled = LDocument::ObeyCommand(inCommand, ioParam);
		break;
	}
	
	return cmdHandled;
}


// ---------------------------------------------------------------------------
//  AllowSubRemoval												  [public]
// ---------------------------------------------------------------------------

Boolean
CICNS_EditorDoc::AllowSubRemoval(
	LCommander*		inSub)
{
	if (inSub == mIcnsEditWindow) {
		AttemptClose(false);
		return false;
	} else {
		return true;
	}
}


// ---------------------------------------------------------------------------
//   GetModifiedResource											[protected]
// ---------------------------------------------------------------------------

Handle
CICNS_EditorDoc::GetModifiedResource(Boolean &releaseIt) 
{
	IconFamilyHandle	iconFamilyH = NULL;
	mIcnsEditWindow->CollectResourceData(iconFamilyH);	
	releaseIt = true;
	return (Handle)iconFamilyH;
}


// ---------------------------------------------------------------------------
//  ImportICNS													  [public]
// ---------------------------------------------------------------------------

void
CICNS_EditorDoc::ImportICNS()
{
	FSSpec	theFSSpec;
	OSErr	error;

	Boolean openOK = UNavigationDialogs::AskOpenOneFile(fileType_Default, theFSSpec, 
														kNavAllFilesInPopup
														+ kNavDontAutoTranslate
														+ kNavSupportPackages
														+ kNavAllowOpenPackages);
	
	if (openOK) {
		IconFamilyHandle	iconFamilyH = NULL;
		error = ReadIconFile(&theFSSpec, &iconFamilyH);
		if (iconFamilyH == NULL || error != noErr) {
			UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("InvalidIcnsData"), PPob_SimpleMessage);
		} else {
			error = mIcnsEditWindow->ImportData( (Handle)iconFamilyH);
		}
	} 
}


// ---------------------------------------------------------------------------
//  ExportICNS													  [public]
// ---------------------------------------------------------------------------

void
CICNS_EditorDoc::ExportICNS()
{
	FSSpec	theFSSpec;
	bool	replacing;
	bool	saveIt = false;
	bool	exportIt = true;
	OSErr	error;
	SInt16	saveAnswer = answer_DontSave;
	
	if (IsModified()) {
		saveAnswer = AskSaveChanges(SaveWhen_Closing);
		if (saveAnswer == answer_Save) {
			saveIt = true;
		} else if (saveAnswer == answer_Cancel) {
			exportIt = false;				// Abort the export
		}
	}
	
	if ( saveIt ) {
		if ( CanSaveChanges() ) {
			DoSaveChanges();
		} else {
			exportIt = false;				// Abort the export
		}		
	}
	
	if (exportIt) {
		if ( PP_StandardDialogs::AskSaveFile("\pUntitled.icns", fileType_Default,
											 theFSSpec, replacing) ) {
			if (replacing) {
				// Delete existing file
				error = ::FSpDelete(&theFSSpec);
				if (error) {
					UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("CouldNotDeleteExistingFile"), PPob_SimpleMessage);
					return;
				} 
			}
			
			DoExport(theFSSpec);
		}		
	} 
}


// ---------------------------------------------------------------------------------
//  DoExport
// ---------------------------------------------------------------------------------

void
CICNS_EditorDoc::DoExport(FSSpec inFileSpec)
{
	IconFamilyHandle	iconFamilyH = NULL;
	OSErr error = mIcnsEditWindow->CollectResourceData(iconFamilyH);	
	if (iconFamilyH != NULL && error == noErr) {
		error = WriteIconFile(iconFamilyH, &inFileSpec);
		::DisposeHandle( (Handle)iconFamilyH);
	} 
	if (error != noErr) {
		UMessageDialogs::ErrorMessageFromLocalizable(CFSTR("ExportError"), error, PPob_SimpleMessage);
	} 
}




PP_End_Namespace_PowerPlant
