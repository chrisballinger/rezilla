// ===========================================================================
// CAete_EditorDoc.cp
// 
//                       Created: 2004-07-01 08:42:37
//             Last modification: 2005-09-05 06:52:57
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2004-2005
// All rights reserved.
// ===========================================================================

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CRezillaApp.h"
#include "RezillaConstants.h"
#include "CAete_EditorDoc.h"
#include "CAete_EditorWindow.h"
#include "CTextFileStream.h"
#include "CRezillaPrefs.h"
#include "CAeteSuite.h"
#include "CAeteStream.h"
#include "CRezObj.h"
#include "UMessageDialogs.h"
#include "UAeteTranslator.h"
#include "UNavigationDialogs.h"
#include "NavServicesCallbacks.h"

#include <PP_Messages.h>

#include <LArray.h>
#include <LWindow.h>
#include <LString.h>
#include <LStaticText.h>
#include <LPopupButton.h>
#include <LTableMonoGeometry.h>
#include <LTableSingleSelector.h>
#include <LTableArrayStorage.h>

#include <AEInteraction.h>
#include <AERegistry.h>
#include <AEObjects.h>
#include <AEPackObject.h>
#include <CFString.h>
#include <Lists.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>


PP_Begin_Namespace_PowerPlant

extern const Str15 Rzil_AeteExportItems[] = {
	"\pXML",
	"\pDeRez",
	"\pSdef",
	"\pTEXT",
	"\pHTML"
};


// ---------------------------------------------------------------------------
//   CAete_EditorDoc						Default Constructor		  [public]
// ---------------------------------------------------------------------------

CAete_EditorDoc::CAete_EditorDoc(LCommander* inSuper,
								CRezMapTable* inSuperMap,
								CRezObj* inRezObj,
								ResType inSubstType,
								Boolean inReadOnly)
	: CEditorDoc(inSuper, inSuperMap, inRezObj, inSubstType, inReadOnly)
{
	Initialize();
}


// ---------------------------------------------------------------------------
//     ~CAete_EditorDoc						Destructor				  [public]
// ---------------------------------------------------------------------------

CAete_EditorDoc::~CAete_EditorDoc()
{
	if (mOutStream != nil) {
		delete mOutStream;
	} 

	if (mAeteEditWindow != nil) {
		delete mAeteEditWindow;
	} 
}


// ---------------------------------------------------------------------------
//   Initialize							Default Constructor		  [public]
// ---------------------------------------------------------------------------

void
CAete_EditorDoc::Initialize()
{
	OSErr error;

	mOutStream = nil;
	
	// Create window for our document
	mAeteEditWindow = dynamic_cast<CAete_EditorWindow *>(LWindow::CreateWindow( PPob_AeteEditorWindow, this ));
	Assert_( mAeteEditWindow != nil );
	
	SetMainWindow( dynamic_cast<CEditorWindow *>(mAeteEditWindow) );
	NameNewEditorDoc();
	mAeteEditWindow->FinalizeEditor(this);

	try {
		// Install the contents
		if (mRezObj != nil) {
			Handle rezData = mRezObj->GetData();

			if (rezData != nil) {
				// Work with a copy of the handle
				::HandToHand(&rezData);
				error = mAeteEditWindow->InstallAete(rezData);
				ThrowIfOSErr_(error);
			} 
		} 
	} catch (...) {
		if (error == err_MoreDataThanExpected) {
			UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("ResourceLongerThanExpected"), PPob_SimpleMessage);
		} else if (error != userCanceledErr) {
			UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("DataParsingException"), PPob_SimpleMessage);
		} 
		delete this;
		return;
	}
	
	// Make the window visible
	mAeteEditWindow->Show();
}


// ---------------------------------------------------------------------------
//   GetDescriptor													  [public]
// ---------------------------------------------------------------------------
//	Pass back the name of a Document

StringPtr
CAete_EditorDoc::GetDescriptor(
	Str255	outDescriptor) const
{
	if (mAeteEditWindow != nil) {
		// Use name of its window
		mAeteEditWindow->GetDescriptor(outDescriptor);
	} else {
		// No window, document name is empty string
		outDescriptor[0] = 0;		
	}

	return outDescriptor;
}


// ---------------------------------------------------------------------------
//   AllowSubRemoval												  [public]
// ---------------------------------------------------------------------------

Boolean
CAete_EditorDoc::AllowSubRemoval(
	LCommander*		inSub)
{
	if (inSub == mAeteEditWindow) {
		AttemptClose(false);
		return false;
	} else {
		return true;
	}
}


// ---------------------------------------------------------------------------------
//  FindCommandStatus
// ---------------------------------------------------------------------------------

void
CAete_EditorDoc::FindCommandStatus(
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
//   ObeyCommand							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CAete_EditorDoc::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;
	OSErr		error = noErr;
	
	if (inCommand == cmd_AeteExport) {
		FSSpec	theFSSpec;
		SInt16	exportFormat;
		Boolean	replacing;

		if ( DesignateExportFile(theFSSpec, replacing, exportFormat) ) {
			if (replacing) {
				// Delete existing file
				error = ::FSpDelete(&theFSSpec);
				if (error) {
					UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("CouldNotDeleteExistingFile"), PPob_SimpleMessage);
					return cmdHandled;
				} 
			}

			DoExport(theFSSpec, exportFormat);
		}		
	} else if (inCommand == cmd_AeteImport) {
		FSSpec	theFSSpec;

		Boolean openOK = UNavigationDialogs::AskOpenOneFile('TEXT', theFSSpec, 
												kNavNoTypePopup 
												+ kNavDontAutoTranslate
												+ kNavSupportPackages
												+ kNavAllowOpenPackages);
		
		if (openOK) {
			error = mAeteEditWindow->ImportAete(theFSSpec);
		} 
		
	} else {
		cmdHandled = CEditorDoc::ObeyCommand(inCommand, ioParam);
	}
	
	return cmdHandled;
}
	

// ---------------------------------------------------------------------------
//  GetModifiedResource										[protected]
// ---------------------------------------------------------------------------
// The returned handle should be released by the caller.

Handle
CAete_EditorDoc::GetModifiedResource(Boolean &releaseIt) 
{
	if (mOutStream != nil) {
		delete mOutStream;
	} 
	
	mOutStream = new CAeteStream();	
	mAeteEditWindow->RetrieveAete(mOutStream);
	releaseIt = false;
	
	return mOutStream->GetDataHandle();
}


// ---------------------------------------------------------------------------
//   DesignateExportFile								[public static]
// ---------------------------------------------------------------------------

Boolean
CAete_EditorDoc::DesignateExportFile( FSSpec & outFileSpec, Boolean & outReplacing, SInt16 & outExportFormat)
{
	bool	openOK = false;
	Str255	theString;
	UInt8	theCount = sizeof(Rzil_AeteExportItems)/sizeof(Str15);

	outExportFormat = exportAete_Xml;
	
	// Build the forks popup
	NavMenuItemSpecHandle	theMenuItemHandle ;
	NavMenuItemSpecPtr		theNavMenuItemSpecPtr;
	
	theMenuItemHandle = (NavMenuItemSpec**) NewHandleClear( theCount * sizeof(NavMenuItemSpec) );
	if (theMenuItemHandle != NULL) {
		for (SInt16 theIndex = 0; theIndex < theCount; theIndex++) {
			theNavMenuItemSpecPtr = *theMenuItemHandle + theIndex;
			(*theNavMenuItemSpecPtr).version = kNavMenuItemSpecVersion;
			(*theNavMenuItemSpecPtr).menuCreator = FOUR_CHAR_CODE('Rzil');
			(*theNavMenuItemSpecPtr).menuType = 'TEXT';
			BlockMoveData(Rzil_AeteExportItems[theIndex], (*theNavMenuItemSpecPtr).menuItemName, Rzil_AeteExportItems[theIndex][0] + 1);
		}
	}

	// Deactivate the desktop.
	::UDesktop::Deactivate();
	
	// Browse for a document
	UNavigationDialogs::CNavFileDesignator designator;
	
	// File designator setup
	designator.SetEventFilterProc(Rzil_ExportAeteEventFilterUPP);
	designator.SetPopupExtension(theMenuItemHandle);
	designator.SetOptionFlags(kNavDontAutoTranslate);
	designator.SetUserData( (void *) &outExportFormat);

	// Retrieve strings from STR# resource
	GetIndString(theString, STRx_NavStrings, index_RezillaAppName);
	designator.SetClientName(theString);
	GetIndString(theString, STRx_NavStrings, index_ExportMapAs);
	designator.SetMessage(theString);
	// Build a default name from the name of the map
	designator.SetSavedFileName("\pAete.xml");
	
	openOK = designator.AskDesignateFile();

	if (openOK) {
		designator.GetFileSpec(outFileSpec);
		outReplacing = designator.IsReplacing();
	}

	// Activate the desktop.
	::UDesktop::Activate();

	return openOK;
}


// ---------------------------------------------------------------------------------
//  DoExport
// ---------------------------------------------------------------------------------

void
CAete_EditorDoc::DoExport(FSSpec & inFileSpec, SInt16 inFormat)
{
	StAeteExporter exporter(mAeteEditWindow->GetAete(), inFileSpec, inFormat);
	
	exporter.SetRezObj(mRezObj);
	exporter.WriteOut();
}




PP_End_Namespace_PowerPlant




