// ===========================================================================
// CRezMapDoc.cp					
// 
//                       Created: 2003-04-29 07:11:00
//             Last modification: 2006-10-03 09:11:28
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2003-2006
// All rights reserved.
// ===========================================================================

PP_Begin_Namespace_PowerPlant


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CRezMapDoc.h"
#include "CEditorDoc.h"
#include "CPickerDoc.h"
#include "CRezillaApp.h"
#include "CRezillaPrefs.h"
#include "CRezFile.h"
#include "CEditorsController.h"
#include "CPickersController.h"
#include "CTemplatesController.h"
#include "CPluginsController.h"
#include "CTextFileStream.h"
#include "CXMLFileStream.h"
#include "CRezMap.h"
#include "CRezMapTable.h"
#include "CRezMapWindow.h"
#include "CRezObj.h"
#include "CRezObjItem.h"
#include "CRezType.h"
#include "CRezTypeItem.h"
#include "CInspectorWindow.h"
#include "CHexEditorDoc.h"
#include "CTmplEditorDoc.h"
#include "CWindowMenu.h"
#include "CRezClipboard.h"
#include "CThreeButtonsBox.h"
#include "CRecentItemsMenu.h"
#include "RezillaConstants.h"
#include "UDialogBoxHandler.h"
#include "UMessageDialogs.h"
#include "UCompareUtils.h"
#include "UMiscUtils.h"
#include "URezMapImportExport.h"
#include "UNavigationDialogs.h"
#include "NavServicesCallbacks.h"

#include <LCheckBox.h>
#include <LComparator.h>
#include <LEditText.h>
#include <LFile.h>
#include <LOutlineItem.h>
#include <LOutlineKeySelector.h>
#include <LOutlineRowSelector.h>
#include <LString.h>
#include <LTableMultiGeometry.h>
#include <LTableMultiSelector.h>
#include <LWindow.h>
#include <UScrap.h>
#include <UStandardDialogs.h>

#include <PP_Messages.h>

#include <Scrap.h>
#include <AEInteraction.h>
#include <AERegistry.h>
#include <AEObjects.h>
#include <AEPackObject.h>

// Standard headers
#include <string.h>


extern CWindowMenu * gWindowMenu;

extern const Str15 Rzil_MapExportItems[] = {
	"\pXML",
	"\pTEXT",
	"\pHTML",
	"\pDeRez"
};

// Statics
TArray<CRezMapDoc*>	CRezMapDoc::sRezMapDocList;



// ---------------------------------------------------------------------------
//   CRezMapDoc							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CRezMapDoc::CRezMapDoc(LCommander *inSuper)
	: LDocument( inSuper )
{
	mFork = CRezillaPrefs::GetPrefValue(kPref_general_newFork);
	mRezFile = nil;
	
	Initialize(nil, kResFileNotOpened);
}


// ---------------------------------------------------------------------------
//   CRezMapDoc							Constructor		  [public]
// ---------------------------------------------------------------------------

CRezMapDoc::CRezMapDoc(LCommander *inSuper, 
						 FSSpec * inFileSpec)
	: LDocument( inSuper )
{
	mFork = CRezillaPrefs::GetPrefValue(kPref_general_newFork);
	mRezFile = nil;
	
	Initialize(inFileSpec, kResFileNotOpened);
}


// ---------------------------------------------------------------------------
//   CRezMapDoc							Constructor		  [public]
// ---------------------------------------------------------------------------

CRezMapDoc::CRezMapDoc(LCommander *inSuper, 
						FSSpec * inFileSpec,
						SInt16 inFork, 
						short inRefnum)
	: LDocument( inSuper )
{
	mFork = inFork;
	mRezFile = nil;
	
	Initialize(inFileSpec, inRefnum);
}


// ---------------------------------------------------------------------------
//   CRezMapDoc							Constructor		  [public]
// ---------------------------------------------------------------------------

CRezMapDoc::CRezMapDoc(LCommander *inSuper, 
						CRezFile * inRezFile)
	: LDocument( inSuper )
{
	FSSpec	theFileSpec;
	
	mFork = inRezFile->GetUsedFork();
	mRezFile = inRezFile;
	inRezFile->GetSpecifier(theFileSpec);
	
	Initialize(&theFileSpec, inRezFile->GetRefnum());
}


// ---------------------------------------------------------------------------
//     ~CRezMapDoc							Destructor				  [public]
// ---------------------------------------------------------------------------

CRezMapDoc::~CRezMapDoc()
{	
	if (mUpdateOnClose == false) {
		mRezMap->UnsetFileAttrs(1 << mapChangedBit);
	} 
	
	// CloseFile() is called from the destructor
	if (mRezFile != nil) {
		delete mRezFile;
	} 
	
	if (mTypesArray != nil) {
		delete mTypesArray;
	} 
	
	// Note: mExportStream is deleted in DoExport() immediately after writing

	// Clear the Inspector if it contains info about a resource belonging to this rezmap
	if (CRezillaApp::sInspectorWindow != nil &&
		CRezillaApp::sInspectorWindow->GetRezObjItem() != nil &&
		CRezillaApp::sInspectorWindow->GetRezObjItem()->GetOwnerRezMapTable()->GetOwnerDoc() == this
	) {
		CRezillaApp::sInspectorWindow->ClearValues();
	} 
	
	// Delete the associated editors and pickers with their array
	DeleteEditors(true);
	DeletePickers(true);

	if (mRezMapWindow != nil) {
		// Remove the window from the window menu.
		gWindowMenu->RemoveWindow( mRezMapWindow );
		// Delete the RezMapWindow associated to this document
		delete mRezMapWindow;
	} 
	
	// Caveat: delete the ResMap object _after_ the RezMapWindow. 
	// This is because of the object model: each RezTypeItem of the
	// RezMapTable (which is a subview of the RezMapWindow) contains a
	// RezType object which has to be deleted. This RezType object must
	// be removed as a submodel of the mRezMap object.
	if (mRezMap != nil) {
		delete mRezMap;
	} 
	
	// Unregister from the static RezMapDocs list
	sRezMapDocList.Remove(this);

	// 	// Remove ourselves from the list of listeners to the prefs object
	// 	CRezillaApp::sPrefs->RemoveListener(this);
}


// ---------------------------------------------------------------------------
//   Initialize													  [public]
// ---------------------------------------------------------------------------

void
CRezMapDoc::Initialize(FSSpec * inFileSpecPtr, short inRefnum)
{		
	mUpdateOnClose = false;
	mExportFormat = exportMap_Xml;
	mExportStream = nil;
	mReadOnly = false;
	mOpenedEditors = NULL;
	mOpenedPickers = NULL;
	
	SetModelKind(rzom_cRezMapDoc);
// 	// Let's use the submodels list mechanism. The submodels of a rezmap 
// 	// document are the editors.
// 	SetUseSubModelList(true);
	
	if (mRezFile == nil) {
		if (inFileSpecPtr != nil) {
			mRezFile = new CRezFile(*inFileSpecPtr, inRefnum, mFork);
			SetSpecified(true);
		} else {
			mRezFile = new CRezFile();
		}
	} 
	
	if (inFileSpecPtr != nil) {
		SetSpecified(true);
	} 

	// Register to the static RezMapDocs list
	sRezMapDocList.AddItem(this);

	// Create the CRezMap class instance
	mRezMap = new CRezMap(inRefnum, this);
	
	// Create window for our document.
	mRezMapWindow = dynamic_cast<CRezMapWindow *>(LWindow::CreateWindow( PPob_RezMapWindow, this));
	Assert_( mRezMapWindow != nil );
	
	// The RezMapTable keeps a pointer to the RezMap object
	mRezMapWindow->GetRezMapTable()->SetRezMap(mRezMap);

	// Set name of window
	if ( inFileSpecPtr == nil ) {
		NameNewDoc();
	} else {
		// Set window title to the name of the file.
		mRezMapWindow->SetDescriptor( inFileSpecPtr->name );
	}

	// Initialize the array of resource editors
	mOpenedEditors = new TArray<CEditorDoc *>();
	
	// Initialize the array of resource pickers
	mOpenedPickers = new TArray<CPickerDoc *>();
	
	// Populate the RezTable
	CTypeComparator* theComparator = new CTypeComparator;
	mTypesArray = new TArray<ResType>( theComparator, true);
	mRezMap->GetAllTypes(mTypesArray);
	mRezMapWindow->GetRezMapTable()->Populate(mTypesArray);

	// Link the window to the file's data (icon, creator, type)
	::SetWindowProxyFSSpec(mRezMapWindow->GetMacWindow(), inFileSpecPtr);
	::SetWindowModified(mRezMapWindow->GetMacWindow(), false);
	
// 	// Let's make the document a listener to the prefs object
// 	CRezillaApp::sPrefs->AddListener(this);
		
	// Attach an LUndoer
	AddAttachment( new LUndoer );
	
	// Add the window to the window menu.
	gWindowMenu->InsertWindow( mRezMapWindow );

	// Make the window visible.
	mRezMapWindow->Show();
}


// ---------------------------------------------------------------------------
//   ObeyCommand									[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CRezMapDoc::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;	// Assume we'll handle the command
	
	switch (inCommand) {
		
		case cmd_Close: 
		AttemptClose(false);
		break;
		
		case cmd_Save:
		SendSelfAE(kAECoreSuite, kAESave, ExecuteAE_No);
		DoSave();
		break;

		case cmd_SaveAs: {
			FSSpec	theFSSpec;
			AskSaveAs(theFSSpec, RecordAE_Yes);
			break;
		}

		case cmd_Revert: 
		if (AskConfirmRevert()) {
			SendSelfAE(kAEMiscStandards, kAERevert, ExecuteAE_No);
			DoRevert();
		}
			break;

		case cmd_Import: {
			// Import must be done in an empty rezmap
			short	theCount;
			mRezMap->CountAllTypes(theCount);
			
			if (theCount > 0 ) {
				FSSpec	theFSSpec;
				Boolean openOK = UNavigationDialogs::AskOpenOneFile(fileType_Default, theFSSpec, 
																	kNavAllFilesInPopup
																	+ kNavDontAutoTranslate
																	+ kNavSupportPackages
																	+ kNavAllowOpenPackages);
				
				if (openOK) {
					DoImport(theFSSpec);
				} 
			} else {
				UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("ImportOnlyInEmptyMap"), PPob_SimpleMessage);
			}
			break;
		}

		case cmd_Export: {
			AskExportAs();
			break;
		}

		case cmd_NewRez: {
			CRezObjItem * theRezObjItem = NewResDialog();
			if (theRezObjItem != NULL) {
				mRezMapWindow->RecalcCountFields();
				// Select the newly created item 
				mRezMapWindow->GetRezMapTable()->UnselectAllCells();
				TryEdit(theRezObjItem, cmd_EditRez);
			} 
			break;
		}
		
		case cmd_GetRezInfo: {
			CRezMapTable * theRezMapTable = mRezMapWindow->GetRezMapTable();
			TableIndexT theIndex = theRezMapTable->GetTableSelector()->GetFirstSelectedRow();
			CRezObjItem * theRezObjItem = dynamic_cast<CRezObjItem *>(theRezMapTable->FindItemForRow(theIndex));
			if (theRezObjItem != nil) {
				CRezillaApp::sInspectorWindow->Show();
				CRezillaApp::sInspectorWindow->InstallValues(theRezObjItem);
				// Bring the window to the front.
				UDesktop::SelectDeskWindow( CRezillaApp::sInspectorWindow );
			}
			break;		
		}
		
		case cmd_RemoveRez:
		case cmd_Clear:
		case cmd_DuplicateRez: {
			LArray* theArray = new LArray( sizeof(LOutlineItem*) );
			
			mRezMapWindow->GetRezMapTable()->GetAllSelectedRezObjItems(theArray);
			LArrayIterator iterator(*theArray);
			CRezObjItem *theItem = nil;	
			while (iterator.Next(&theItem)) {				
				switch (inCommand) {		
					case cmd_RemoveRez:
					case cmd_Clear: 
						RemoveResource( theItem );
						break;		
					
					case cmd_DuplicateRez: 
						DuplicateResource( theItem->GetRezObj() );
						break;
				}
			}

			delete theArray;
			break;
		}
		
		case cmd_EditRez:
		case cmd_TmplEditRez:
		case cmd_HexEditRez:
		case cmd_EditWithPlugin:
		case cmd_EditRezAsType: {
			ResType asType = 0;
			LArray* theArray = new LArray( sizeof(LOutlineItem*) );
			int		countEdited = 0;
			UInt32	countItems;
			
			mRezMapWindow->GetRezMapTable()->GetAllSelectedRezObjItems(theArray);
			countItems = theArray->GetCount();
			LArrayIterator iterator(*theArray);
			CRezObjItem * theItem = nil;
			
			if (inCommand == cmd_EditRezAsType && ! UMiscUtils::SelectType(asType) ) {
					break;
			} 
			
			while (iterator.Next(&theItem)) {
				countEdited += TryEdit(theItem, inCommand, asType);
			}

			if (countEdited != 0) {
				WarnEdited(theItem->GetRezObj()->GetType(), (countItems == 1), countEdited);
			}

			delete theArray;
			break;
		}
		
		case cmd_Copy: 
		case cmd_Cut: {
			StClipboardContext	scrapContext(scrap_rezmap);
			
			LArray* theArray = new LArray( sizeof(LOutlineItem*) );
			mRezMapWindow->GetRezMapTable()->GetAllSelectedRezObjItems(theArray);
			
			if ( theArray != nil ) {
				CRezClipboard::GetClipboard()->SetData(kRezillaClipType, (Ptr) theArray,
													   theArray->GetCount(), 
													   true);
				if (inCommand == cmd_Cut) {
					LArrayIterator iterator(*theArray);
					CRezObjItem *theItem = nil;	
					while (iterator.Next(&theItem)) {
						RemoveResource(theItem);
					}
				} 
			} 
			break;
		}

		case cmd_Paste: {
			StClipboardContext	scrapContext(scrap_rezmap);
			
			CRezClipboard::GetClipboard()->GetData(kRezillaClipType, nil);
			// The call to GetData() ensures that CRezClipboard::ImportSelf() is 
			// called appropriately, but GetDataSelf() is empty and all the work 
			// is done by the following:
			PasteRezMap( CRezClipboard::GetScrapRezMap() );
			break;
		}

		case cmd_ActionCut:
		case cmd_ActionPaste:
		case cmd_ActionClear:
		case cmd_ActionTyping: {
			break;
		}

		default: {
// 			cmdHandled = GetSuperCommander()->ObeyCommand(inCommand, ioParam);
			cmdHandled = LDocument::ObeyCommand(inCommand, ioParam);
			break;
		}
	}
	
	return cmdHandled;
}


// ---------------------------------------------------------------------------------
//  TryEdit															[public]
// ---------------------------------------------------------------------------------

int
CRezMapDoc::TryEdit(CRezObjItem * inRezObjItem, CommandT inCommand, ResType asType)
{	
	short		theID = inRezObjItem->GetRezObj()->GetID();
	ResType		theType = inRezObjItem->GetRezObj()->GetType();
	ResType		substType = theType;
	int			countEdited = 0;
	
	// Is this resource already edited ?
	CEditorDoc * theRezEditor = GetRezEditor(theType, theID);
	if (theRezEditor != nil) {
		if ((theRezEditor->GetKind() != editor_kindTmpl && inCommand == cmd_TmplEditRez) 
			|| (theRezEditor->GetKind() != editor_kindHex && inCommand == cmd_HexEditRez)) {
			 countEdited++;
		 } 
		 theRezEditor->SelectMainWindow();
		 return countEdited;
	} else {
		if (asType != 0) {
			theType = asType;
			substType = asType;
		} 
		
		DoEdit(inRezObjItem, inCommand, theType, &substType);
	}
	
	return countEdited;
}


// ---------------------------------------------------------------------------------
//  DoEdit															[public]
// ---------------------------------------------------------------------------------

void
CRezMapDoc::DoEdit(CRezObjItem * inRezObjItem, CommandT inCommand, ResType inType, ResType * substTypePtr)
{	
	switch (inCommand) {		
		case cmd_EditRez:
		case cmd_EditRezAsType:
		if ( CEditorsController::HasEditorForType(inType, substTypePtr) ) {
			// call the appropriate editor
			CEditorsController::InvokeCustomEditor(this, inRezObjItem, *substTypePtr);
			break;
		} // else fall through to plugin editing...
		
		case cmd_EditWithPlugin:
		if ( CPluginsController::HasPluginForType(inType, substTypePtr) ) {
			// call the right plugin
			CPluginsController::InvokePluginEditor(this, inRezObjItem, *substTypePtr);
			break;
		} // else fall through to template editing...
		
		case cmd_TmplEditRez:
		case cmd_TmplEditAsRez:
		if ( CTemplatesController::HasTemplateForType(inType, substTypePtr, mRezMap) ) {
			new CTmplEditorDoc(this, mRezMapWindow->GetRezMapTable(), inRezObjItem->GetRezObj(), *substTypePtr, mReadOnly);
			break;
		} else {
			if (inCommand == cmd_TmplEditRez) {
				UMessageDialogs::AlertWithType(CFSTR("NoTemplateForThisType"), inType);
				break;
			} 
			// else fall through to hexadecimal editing...
		}

		case cmd_HexEditRez:
		new CHexEditorDoc(this, mRezMapWindow->GetRezMapTable(), inRezObjItem->GetRezObj(), inType, mReadOnly);
		break;
	}
}


// ---------------------------------------------------------------------------------
//  WarnEdited															[public]
// ---------------------------------------------------------------------------------

void
CRezMapDoc::WarnEdited(ResType inType, Boolean singleItem, int countEdited)
{	
	if (singleItem) {
		switch (inType) {
		  case ResType_ExtendedMenu:
		  UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("XmnuEditedInMenuEditor"), PPob_SimpleMessage);
			break;
			
		  default:
		  UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("ThisResourceEditedInOtherMode"), PPob_SimpleMessage);
			break;
		}
	} else {
		UMessageDialogs::AlertWithValue(CFSTR("SomeResourcesEditedInOtherMode"), countEdited);
	}
}


// ---------------------------------------------------------------------------------
//  TryOpenPicker															[public]
// ---------------------------------------------------------------------------------

Boolean
CRezMapDoc::TryOpenPicker(CRezTypeItem * inRezTypeItem)
{
	ResType		theType = inRezTypeItem->GetRezType()->GetType();
	Boolean		result = true;
	
	// Does this type already have an opened picker ?
	CPickerDoc * theRezPicker = GetTypePicker(theType);
	if (theRezPicker != nil) {
		theRezPicker->SelectPickerWindow();
	} else if ( CPickersController::HasPickerForType(theType) ) {
		// call the appropriate picker
		CPickersController::InvokeCustomPicker(this, inRezTypeItem);
	} else {
		result = false;
	}
	
	return result;
}


// ---------------------------------------------------------------------------------
//  NameNewDoc
// ---------------------------------------------------------------------------------

void
CRezMapDoc::NameNewDoc()
{
	// Start with the default name ("untitled rez map [1]")
	LStr255		theTitle(STRx_DefaultDocTitles, index_RezMapUntitled);
	
	// Check if an existing window has this name. If so,
	// append a count and keep incrementing the
	// count until we find a unique name.
	long	num = 1;
	while (UWindows::FindNamedWindow(theTitle) != nil) {
		theTitle.Assign(STRx_DefaultDocTitles, index_RezMapUntitledX);
		++num;
		theTitle += "\p [";
		theTitle += num;
		theTitle += "\p]";
	}		
	
	mRezMapWindow->SetDescriptor(theTitle);		// Finally, set window title
}


// ---------------------------------------------------------------------------------
//  IsModified
// ---------------------------------------------------------------------------------
// The Resource Manager sets the mapChanged attribute for the resource fork
// when you call the ChangedResource, the AddResource, or the RemoveResource
// function. 

Boolean
CRezMapDoc::IsModified()
{
	// Ask the RezMapTable
	short theResFileAttrs;
	Boolean docModified;
	
	mRezMapWindow->GetRezMapTable()->GetRezMap()->GetMapAttributes(theResFileAttrs);
	
	docModified = (mIsModified  || (theResFileAttrs & mapChangedBit) );
	return docModified;
}


// ---------------------------------------------------------------------------
//   SetModified													  [public]
// ---------------------------------------------------------------------------

void
CRezMapDoc::SetModified(Boolean	inModified)
{
	LDocument::SetModified(inModified);
	::SetWindowModified(mRezMapWindow->GetMacWindow(), inModified);	
}


// ---------------------------------------------------------------------------
//   GetDescriptor													  [public]
// ---------------------------------------------------------------------------
//	Pass back the name of a Document

StringPtr
CRezMapDoc::GetDescriptor(
	Str255	outDescriptor) const
{
	if (mRezMapWindow != nil) {	// No File, use name of its Window
		mRezMapWindow->GetDescriptor(outDescriptor);

	} else {						// No File and No Window
		outDescriptor[0] = 0;		//   Document name is empty string
	}

	return outDescriptor;
}


// ---------------------------------------------------------------------------
//  GetRefnum												[public]
// ---------------------------------------------------------------------------

short
CRezMapDoc::GetRefnum() 
{ 
	return mRezMap->GetRefnum();
}


// ---------------------------------------------------------------------------
//  SetRefnum												[public]
// ---------------------------------------------------------------------------

void
CRezMapDoc::SetRefnum(short inRefnum) 
{ 
	mRezMap->SetRefnum(inRefnum);
}
	

// ---------------------------------------------------------------------------
//   UsesFileSpec													  [public]
// ---------------------------------------------------------------------------
//	Returns whether the Document's File has the given FSSpec

Boolean
CRezMapDoc::UsesFileSpec(
	const FSSpec&	inFileSpec) const
{
	Boolean usesFS = false;

	if (mRezFile != nil) {
		usesFS = mRezFile->UsesSpecifier(inFileSpec);
	}

	return usesFS;
}


// ---------------------------------------------------------------------------
//   AttemptClose													  [public]
// ---------------------------------------------------------------------------
//	Try to close an edited resource map.

void
CRezMapDoc::AttemptClose(
	Boolean	inRecordIt)
{
	Boolean		closeIt = true;
	SInt32		saveOption = kAENo;
	FSSpec		fileSpec = {0, 0, "\p"};		// Invalid specifier

	// Check all the editor windows related to this rezmap. Ask what to do
	// if some of them are modified.
	if (! IsModified() && ! CheckEditorsUnmodified(false) ) {
		SInt16		answer;
		answer = UMessageDialogs::AskIfFromLocalizable(CFSTR("ConfirmCloseModifiedEditedRes"), PPob_AskIfMessage);
		if (answer == answer_Cancel) {
			return;
		}
	} 

	// By default, don't update when closing
	mUpdateOnClose = false;
	
	if (IsModified()) {
		if (mReadOnly) {
			UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("CantSaveReadOnly"), PPob_SimpleMessage);
		} else {
			SInt16 answer = AskSaveChanges(SaveWhen_Closing);

			if (answer == answer_Save) {
				if (IsSpecified()) {
					// Inspect the edited resources and interrupt the
					// operation if some of them are modified.
					if (! CheckEditorsUnmodified(false) ) {
						UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("ValidateEditedResBeforeSave"), PPob_SimpleMessage);
						return;
					} 			
					DoSave();
					saveOption = kAEYes;
				} else {
					closeIt = AskSaveAs(fileSpec, RecordAE_No);
					saveOption = kAEYes;
				}
			} else if (answer == answer_Cancel) {
				closeIt = false;
			} 
		}
	}

	if (closeIt) {
		if (inRecordIt) {
			try {
				SendAEClose(saveOption, fileSpec, ExecuteAE_No);
			}
			catch (...) { }
		}

		Close();
	}
}


// ---------------------------------------------------------------------------
//   AskSaveChanges												  [public]
// ---------------------------------------------------------------------------
//	Ask user whether to save changes before closing the Document or
//	quitting the Application

SInt16
CRezMapDoc::AskSaveChanges(
	bool /* inQuitting */)
{
// 	MakeCurrent();
	return UMessageDialogs::AskYesNoFromLocalizable(CFSTR("SaveRezMapWindow"), PPob_AskYesNoMessage);
}


// ---------------------------------------------------------------------------
//   DoAEClose														  [public]
// ---------------------------------------------------------------------------
//	Close a Document in response to a "close" AppleEvent

void
CRezMapDoc::DoAEClose(
	const AppleEvent&	inCloseAE)
{
	OSErr		err;
	DescType	theType;
	Size		theSize;

	// Optional "saveOption" parameter.
	// Default value is "yes".

	SInt32	saveOption = kAEYes;
	err = ::AEGetParamPtr(&inCloseAE, keyAESaveOptions,
				typeEnumeration, &theType, &saveOption,
				sizeof(SInt32), &theSize);

	bool	saveIt   = false;
	bool	closeIt  = true;
	mUpdateOnClose = false;

	if (saveOption == kAEAsk) {
		SInt16	saveAnswer = answer_DontSave;

		if (IsModified()) {
			UAppleEventsMgr::InteractWithUser(Throw_Yes);
			saveAnswer = AskSaveChanges(SaveWhen_Closing);
		}

		if (saveAnswer == answer_Save) {
			saveIt = true;
		} else if (saveAnswer == answer_Cancel) {
			// Abort the close
			closeIt = false;
		}

	} else if (saveOption == kAEYes) {
		saveIt = true;
	}

	if (saveIt) {
		// Save to existing file
		DoSave();
	} 

	if (closeIt) {
		// Finally, close the document
		Close();
	} else {							
		// User canceling the close means the AppleEvent failed
		ThrowOSErr_(userCanceledErr);
	}
}


// ---------------------------------------------------------------------------------
//  DoAESaveMap
// ---------------------------------------------------------------------------------
// Called when doing a SaveAs

void
CRezMapDoc::DoAESaveMap(
				FSSpec&	inFileSpec,
				SInt16	inFork)
{
	OSErr			error;
	SInt16			oldFork = mRezFile->GetUsedFork(), useFork = inFork;
	CRezMapTable*	theRezMapTable = mRezMapWindow->GetRezMapTable();
	
	if (inFork == fork_samefork) {
		useFork = oldFork;
	} 
	
	// Make a new file object
	CRezFile * theNewFile = new CRezFile( inFileSpec, kResFileNotOpened, useFork );
	ThrowIfNil_(theNewFile);
		
	// Make new resource file on disk
	error = theNewFile->CreateNewFile();
	if (error == noErr) {
		// Open the resource file. This sets the new refnum in the new
		// CRezFile object.
		error = theNewFile->OpenFile(fsRdWrPerm);
		
		if (error == noErr) {
			// Write out the data
			theNewFile->CopyFromRezMap(mRezMap);
			
			// Delete the old CRezFile. This closes the old rez map.
			delete mRezFile;
			mRezFile = theNewFile;
			
			// Delete the old RezMap and create a new one
			delete mRezMap;
			mRezMap = new CRezMap( theNewFile->GetRefnum(), this );

			// Set window title to the name of the file.
			mRezMapWindow->SetDescriptor(inFileSpec.name);
			
			// Register to the Recent Items menu
			CRezillaApp::GetRecentItemsAttachment()->AddFile(inFileSpec, true);
			
			// Document has a specified file
			SetSpecified(true);
			
			// Mark as unmodified
			mRezMap->Update();
			SetModified(false);
			
			if (mRezFile->GetUsedFork() != oldFork) {
				mRezMapWindow->InstallWhichForkField();
			} 
			
			// Rebuild the RezMapTable and redraw
			theRezMapTable->RemoveAllItems();
			theRezMapTable->Populate(mTypesArray);
			mRezMapWindow->Refresh();
			
		} else {
			UMessageDialogs::AlertWithValue(CFSTR("CantOpenRezFileForWriting"), error);
			return;
		}
	} else {
		UMessageDialogs::AlertWithValue(CFSTR("CantCreateNewRezFile"), error);
		return;
	}
	
	mRezMapWindow->Refresh();
}


// ---------------------------------------------------------------------------------
//  DoSave
// ---------------------------------------------------------------------------------

void
CRezMapDoc::DoSave()
{
	OSErr error;

	try {
		error = mRezMap->Update();
	}
	catch (...) {}
	
	if (error != noErr) {
		UMessageDialogs::DescribeError(CFSTR("ErrorSavingRezMapDoc"), error);
	} else {
		// Mark the document as non modified
		SetModified(false);
	}
}


// ---------------------------------------------------------------------------
//   CheckEditorsUnmodified										[public]
// ---------------------------------------------------------------------------

Boolean
CRezMapDoc::CheckEditorsUnmodified(Boolean closeAll)
{
	Boolean unmodified = true;
	
	if (mOpenedEditors != nil) {
		TArrayIterator<CEditorDoc *> iterator(*mOpenedEditors, LArrayIterator::from_End);
		CEditorDoc* theRezEditor = nil;
		while (iterator.Previous(theRezEditor)) {
			if ( theRezEditor->IsModified() ) {
				theRezEditor->SelectMainWindow();
				unmodified = false;
				break;
			} else if (closeAll) {
				delete theRezEditor;
				mOpenedEditors->RemoveItemsAt(1, iterator.GetCurrentIndex());
			}
		}
	} 
			
	return unmodified;
}
 

// ---------------------------------------------------------------------------
//   AskSaveAs														  [public]
// ---------------------------------------------------------------------------
//	Ask the user to save a Document and give it a name
//	Returns false if the user cancels the operation

Boolean
CRezMapDoc::AskSaveAs(
	FSSpec&		outFSSpec,
	Boolean		inRecordIt)
{
	Boolean		saveOK = false;
	bool		replacing;

	if ( DesignateOutFile(outFSSpec, replacing) ) {
		// Try to close all the editor windows related to this rezmap.
		// Interrupt the operation if some of them are modified.
		if (! CheckEditorsUnmodified(true) ) {
			UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("ValidateEditedResBeforeSaveAs"), PPob_SimpleMessage);
		} else {
			if (replacing && UsesFileSpec(outFSSpec)) {
				// User chose to replace the file with one of the same
				// name. Consider this is the same thing as a regular save 
				// even if the dest fork has been chosen to a different fork.
				if (inRecordIt) {
					SendSelfAE(kAECoreSuite, kAESave, ExecuteAE_No);
				}

				DoSave();
				saveOK = true;

			} else {

				if (inRecordIt) {
					try {
						SendAESaveAs(outFSSpec, fileType_Default, ExecuteAE_No);
					} catch (...) { }
				}

				if (replacing) {
					// Delete existing file
					OSErr error = ::FSpDelete(&outFSSpec);
					if (error) {
						UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("CouldNotDeleteExistingFile"), PPob_SimpleMessage);
						return saveOK;
					} 
				}

				DoAESaveMap(outFSSpec, mFork);
				saveOK = true;
			}
		}		
	}

	return saveOK;
}


// ---------------------------------------------------------------------------
//   DoRevert														  [public]
// ---------------------------------------------------------------------------
//	Revert a Document to its last saved version

void
CRezMapDoc::DoRevert()
{
	FSSpec		theFSSpec;
	short		theRefNum;
	SInt16		theFork;
	OSErr		error;
	
	// Delete all the editors and pickers
	DeleteEditors(false); 
	DeletePickers(false); 

	// Set the changedMap attribute to false (mapChanged = 2^mapChangedBit)
	mRezMap->UnsetFileAttrs(mapChanged);

	// Close...
	mRezFile->GetSpecifier(theFSSpec);
	mRezFile->CloseFile();
	// ... and reopen the rezfile
	error = dynamic_cast<CRezillaApp *>(GetSuperCommander())->PreOpen(theFSSpec, theFork, theRefNum, mFork);

	if (error == noErr) {
		if (mRezFile != nil) {
			delete mRezFile;
		} 
		mRezFile = new CRezFile(theFSSpec, theRefNum, mFork);
	} else {
		dynamic_cast<CRezillaApp *>(GetSuperCommander())->ReportOpenForkError(error, &theFSSpec);
		return;
	}
	
	// Delete the RezMap object and create a new one
	if (mRezMap != nil) {
		delete mRezMap;
	} 
	mRezMap = new CRezMap(theRefNum, this);
	
	// Rebuild the rez map table
	CRezMapTable* theRezMapTable = mRezMapWindow->GetRezMapTable();

	theRezMapTable->SetRezMap(mRezMap);
	theRezMapTable->RemoveAllItems();
	if (mTypesArray != nil) {
		delete mTypesArray;
	} 
	CTypeComparator* theComparator = new CTypeComparator;
	mTypesArray = new TArray<ResType>( theComparator, true);
	mRezMap->GetAllTypes(mTypesArray);
	theRezMapTable->Populate(mTypesArray);

	// Redraw
	mRezMapWindow->Refresh();
	
	// Mark the document as non modified
	SetModified(false);
}


// ---------------------------------------------------------------------------
//   AskConfirmRevert												  [public]
// ---------------------------------------------------------------------------

bool
CRezMapDoc::AskConfirmRevert()
{
	return UMessageDialogs::AskIfFromLocalizable(CFSTR("ConfirmRevert"), PPob_AskIfMessage);
}


// ---------------------------------------------------------------------------
//   DesignateOutFile								[public static]
// ---------------------------------------------------------------------------

Boolean
CRezMapDoc::DesignateOutFile( FSSpec& outFileSpec, bool & outReplacing)
{
	bool	openOK = false;
	Str255	theString;
	
	mFork = fork_samefork;
	
	// Deactivate the desktop.
	::UDesktop::Deactivate();
	
	// Browse for a document
	UNavigationDialogs::CNavFileDesignator designator;
	
	// File designator setup
	designator.SetEventFilterProc(Rzil_SaveAsNavEventFilterUPP);
	designator.SetOptionFlags(kNavDontAutoTranslate);
	designator.SetUserData( (void *) &mFork);

	// Retrieve strings from STR# resource
	GetIndString(theString, STRx_NavStrings, index_RezillaAppName);
	designator.SetClientName(theString);
	GetIndString(theString, STRx_NavStrings, index_SaveRezFileAs);
	designator.SetMessage(theString);
	GetIndString(theString, STRx_NavStrings, index_SaveUntitledRsrc);
	designator.SetSavedFileName(theString);
	
	openOK = designator.AskDesignateFile();

	if (openOK) {
		designator.GetFileSpec(outFileSpec);
		outReplacing = designator.IsReplacing();
	}

    // Activate the desktop.
    ::UDesktop::Activate();

	return openOK;
}


// ---------------------------------------------------------------------------
//   AskExportAs													  [public]
// ---------------------------------------------------------------------------
//	Ask the user to export a Document and give it a name
//	Returns false if the user cancels the operation

Boolean
CRezMapDoc::AskExportAs()
{
	Boolean		saveOK = false;
	bool		replacing;
	FSSpec		theFSSpec;

	if ( DesignateExportFile(theFSSpec, replacing) ) {

		if (replacing) {
			// Delete existing file
			OSErr error = ::FSpDelete(&theFSSpec);
			if (error) {
				UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("CouldNotDeleteExistingFile"), PPob_SimpleMessage);
				return saveOK;
			} 
		}

		DoExport(theFSSpec);
		saveOK = true;
	}

	return saveOK;
}


// ---------------------------------------------------------------------------
//   DesignateExportFile								[public static]
// ---------------------------------------------------------------------------

Boolean
CRezMapDoc::DesignateExportFile( FSSpec& outFileSpec, bool & outReplacing)
{
	bool	openOK = false;
	Str255	theString;
	FSSpec	theFileSpec;
	UInt8	theCount = sizeof(Rzil_MapExportItems)/sizeof(Str15);
	
	mExportFormat = exportMap_Xml;
	
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
			BlockMoveData(Rzil_MapExportItems[theIndex], (*theNavMenuItemSpecPtr).menuItemName, Rzil_MapExportItems[theIndex][0] + 1);
		}
	}

	// Deactivate the desktop.
	::UDesktop::Deactivate();
	
	// Browse for a document
	UNavigationDialogs::CNavFileDesignator designator;
	
	// File designator setup
	designator.SetEventFilterProc(Rzil_ExportMapEventFilterUPP);
	designator.SetPopupExtension(theMenuItemHandle);
	designator.SetOptionFlags(kNavDontAutoTranslate);
	designator.SetUserData( (void *) &mExportFormat);

	// Retrieve strings from STR# resource
	GetIndString(theString, STRx_NavStrings, index_RezillaAppName);
	designator.SetClientName(theString);
	GetIndString(theString, STRx_NavStrings, index_ExportMapAs);
	designator.SetMessage(theString);
	// Build a default name from the name of the map
	mRezFile->GetSpecifier(theFileSpec);
	designator.SetSavedFileName(theFileSpec.name);
	
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
//  DoImport
// ---------------------------------------------------------------------------------

void
CRezMapDoc::DoImport(FSSpec inFileSpec)
{
	OSErr error = noErr;
	
	StRezMapImporter importer(this, inFileSpec);
	
	error = importer.ReadXml();
	
	if (error == noErr) {
		SetModified(true);
	} else {
		UMessageDialogs::DescribeError(CFSTR("ErrorImportingRezMapFromXml"), error);
	}
}


// ---------------------------------------------------------------------------------
//  DoExport
// ---------------------------------------------------------------------------------

void
CRezMapDoc::DoExport(
	FSSpec	&inFileSpec)
{
	OSErr	err = noErr;
	
	// Make a new file object
	if (mExportFormat == exportMap_Xml || mExportFormat == exportMap_Html) {
		// UTF-8 output and escaped entities
		mExportStream = new CXMLFileStream(inFileSpec);
	} else {
		// MacRoman output
		mExportStream = new CTextFileStream(inFileSpec, kCFStringEncodingMacRoman);
	}
	
	if (mExportStream != nil) {		
		// Make new file on disk
		mExportStream->CreateNewDataFile( (OSType) CRezillaPrefs::GetPrefValue(kPref_export_editorSig), 'TEXT' );
		
		// Open the data fork.
		mExportStream->OpenDataFork( fsWrPerm );
		
		// Write out the data.
		WriteOutExport(mExportFormat);
		
		// Close the data fork.
		mExportStream->CloseDataFork();
		
		// Free memory which we don't need anymore
		delete mExportStream;
		mExportStream = nil;
	} 
}


// ---------------------------------------------------------------------------------
//  WriteOutExport
// ---------------------------------------------------------------------------------

void
CRezMapDoc::WriteOutExport(SInt16 inExportFormat)
{	
	StRezMapExporter	exporter(mExportStream);
	switch ( inExportFormat ) {
		case exportMap_Xml:
		// In XML output, binary data are always Base64 encoded
		exporter.WriteOutXml(mRezMap, 
							 CRezillaPrefs::GetPrefValue(kPref_export_includeBinary),
							 export_Base64Enc);
		break;
		
		case exportMap_Text:
		exporter.WriteOutText(mRezMap, 
							 CRezillaPrefs::GetPrefValue(kPref_export_includeBinary),
							 CRezillaPrefs::GetPrefValue(kPref_export_dataEncoding));
		break;
		
		case exportMap_Html:
		// In HTML output, binary data are not included, so the encoding is irrelevant
		exporter.WriteOutHtml(mRezMap, false, 0);
		break;

		case exportMap_Derez:
		exporter.WriteOutDerez(mRezMap);
		break;
	}
	
}


// ---------------------------------------------------------------------------------
//  FindCommandStatus
// ---------------------------------------------------------------------------------

void
CRezMapDoc::FindCommandStatus(
	CommandT	inCommand,
	Boolean		&outEnabled,
	Boolean		&outUsesMark,
	UInt16		&outMark,
	Str255		outName )
{

	switch ( inCommand ) {
	
		case cmd_Close:
		outEnabled = true;
		break;
								
		case cmd_Save:
		outEnabled = !mReadOnly && (IsModified() or not IsSpecified());
		break;

		case cmd_Find:
// 			LString::CopyPStr( "\pFind in Map...", outName);
// 			outEnabled = true;
			outEnabled = false;
			break;
								
		case cmd_Import:
		LString::CopyPStr( "\pImport Map...", outName);
		outEnabled = false;
		break;
		
		case cmd_Export:
		LString::CopyPStr( "\pExport Map...", outName);
		outEnabled = true;
		break;
			
		case cmd_EditRez:
		case cmd_EditRezAsType:
		case cmd_EditWithPlugin:
		case cmd_TmplEditRez:
		case cmd_HexEditRez:
		case cmd_GetRezInfo:
		outEnabled = HasSelection();
		break;		
		
		case cmd_Revert:
		outEnabled = IsModified();
		break;
								
		case cmd_Copy:
			outEnabled = HasSelection();
			break;

		case cmd_Cut:
		case cmd_Clear:
		case cmd_RemoveRez:
		case cmd_DuplicateRez:
		outEnabled = ( !mReadOnly && HasSelection() );
		break;

		case cmd_Paste:
		case cmd_NewRez:
		outEnabled = !mReadOnly ;
		break;
		
// 		case cmd_SelectAll:	{		// Check if the rezmap is not empty
// 			short theCount;
// 			mRezMap->CountAllTypes(theCount);
// 			outEnabled = (theCount > 0 );
// 			break;
// 		}

	  default:
		{
			// Call inherited
			LDocument::FindCommandStatus( inCommand,
				outEnabled, outUsesMark, outMark, outName );
		}
		break;

	}
}


// ---------------------------------------------------------------------------
//   AllowSubRemoval												  [public]
// ---------------------------------------------------------------------------

Boolean
CRezMapDoc::AllowSubRemoval(
	LCommander*		inSub)
{
	if (inSub == mRezMapWindow) {
		AttemptClose(true);
		return false;
	} else {
		return true;
	}
}


// ---------------------------------------------------------------------------
//  ListenToMessage				[public]
// ---------------------------------------------------------------------------

void
CRezMapDoc::ListenToMessage( MessageT inMessage, void *ioParam ) 
{
#pragma unused(ioParam)

	switch (inMessage) {
		
		case msg_StylePrefsChanged: {
			break;
		}
	}
}


// ---------------------------------------------------------------------------
//  HasSelection												[public]
// ---------------------------------------------------------------------------

Boolean
CRezMapDoc::HasSelection()
{
	return mRezMapWindow->GetRezMapTable()->HasSelection();
}


// ---------------------------------------------------------------------------
//  GetFirstSelected												[public]
// ---------------------------------------------------------------------------

TableIndexT
CRezMapDoc::GetFirstSelected()
{
	LTableSelector * theSelector = mRezMapWindow->GetRezMapTable()->GetTableSelector();
	return theSelector->GetFirstSelectedRow();
}


// ---------------------------------------------------------------------------
//	 GetRezTypeAtIndex
// ---------------------------------------------------------------------------

CRezType *
CRezMapDoc::GetRezTypeAtIndex(SInt32 inPosition) const
{
	CRezType *		theRezType = nil;
	LOutlineItem *	theItem = nil;	
	SInt32			count = 1;
	LArrayIterator	rezTypeIterator( mRezMapWindow->GetRezMapTable()->GetFirstLevelItems() );
	
	while (rezTypeIterator.Next(&theItem)) {
		if (count == inPosition) {
			theRezType = dynamic_cast<CRezTypeItem *>(theItem)->GetRezType();
			break;
		} 
		count++;
	}

	return theRezType;
}


// ---------------------------------------------------------------------------
//	 GetIndexForType
// ---------------------------------------------------------------------------

SInt32
CRezMapDoc::GetIndexForType(ResType inType) const
{
	CRezType *		theRezType = nil;
	LOutlineItem *	theItem = nil;
	Boolean			found = false;
	SInt32			position = 0, count = 1;
	LArrayIterator	rezTypeIterator( mRezMapWindow->GetRezMapTable()->GetFirstLevelItems() );
	
	while (rezTypeIterator.Next(&theItem)) {
		theRezType = dynamic_cast<CRezTypeItem *>(theItem)->GetRezType();
		if (theRezType->GetType() == inType) {
			found = true;
			break;
		} 
		count++;
	}

	if (found) {
		position = count;
	} 
	return position;
}


// ---------------------------------------------------------------------------
//	 GetRezTypeByName
// ---------------------------------------------------------------------------

CRezType *
CRezMapDoc::GetRezTypeByName(Str255 inName) const
{
	ResType		theType;
	
	UMiscUtils::PStringToOSType(inName, theType);

	return GetRezTypeByType(theType);
}


// ---------------------------------------------------------------------------
//	 GetRezTypeByType
// ---------------------------------------------------------------------------

CRezType *
CRezMapDoc::GetRezTypeByType(ResType inType) const
{
	CRezType *		theRezType = nil;
	LOutlineItem *	theItem = nil;	
	LArrayIterator	rezTypeIterator( mRezMapWindow->GetRezMapTable()->GetFirstLevelItems() );
	
	while (rezTypeIterator.Next(&theItem)) {
		theRezType = dynamic_cast<CRezTypeItem *>(theItem)->GetRezType();
		
		if (theRezType->GetType() == inType) {
			break;
		} 
		theRezType = nil;
	}

	return theRezType;
}


// ---------------------------------------------------------------------------
//  NewResDialog												[public]
// ---------------------------------------------------------------------------
// Note: Linking Listeners and Broadcasters is done in the StDialogBoxHandler constructor

CRezObjItem *
CRezMapDoc::NewResDialog()
{
	LCheckBox *		theCheckBox;
	LEditText *		theTypeField;
	LEditText *		theIDField;
	LEditText *		theNameField;
	ResType			theType;
	short 			theID;
	long			theLong;
	Boolean			isModified, inLoop;
	Str255			theString;
	short			theAttrs = 0;
	CRezObjItem *	theRezObjItem = NULL;
	
	StDialogBoxHandler	theHandler(PPob_NewRezDialog, this);
	CThreeButtonsBox *	theDialog = theHandler.GetDialog();
	Assert_(theDialog != nil);
	
	theTypeField = dynamic_cast<LEditText *>(theDialog->FindPaneByID( item_NewType ));
	ThrowIfNil_(theTypeField);
	
	theIDField = dynamic_cast<LEditText *>(theDialog->FindPaneByID( item_NewID ));
	ThrowIfNil_(theIDField);
	
	theNameField = dynamic_cast<LEditText *>(theDialog->FindPaneByID( item_NewName ));
	ThrowIfNil_(theNameField);
	
	inLoop = true;
	
	if (inLoop) {
		theDialog->Show();
		
		MessageT theMessage;
		while (true) {
			theMessage = theHandler.DoDialog();
			if (msg_OK == theMessage || msg_Cancel == theMessage) {
				inLoop = false;
				break;
			} else {
				switch (theMessage) {
					
					case msg_NewType:
					case msg_NewID:
					case msg_NewName:
					case msg_NewSysHeap:
					case msg_NewPurgeable:
					case msg_NewLocked:
					case msg_NewProtected:
					case msg_NewPreload:
					isModified = true;
					break;
					
					case msg_NewUniqueID:
					theTypeField->GetDescriptor(theString);
					if (theString[0]) {
						// ZP bugfix #3: PStringToOSType instead of StringToNum
						UMiscUtils::PStringToOSType(theString, theType);
						mRezMap->UniqueID(theType, theID);
						::NumToString(theID, theString);
						theIDField->SetDescriptor(theString);
					} else {
						UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("NoTypeSpecified"), PPob_SimpleMessage);
					}
					break;
				}	
			}
		}
		
		// if Create button hit, retrieve the options
		if (msg_OK == theMessage) {
			theTypeField->GetDescriptor(theString);
			// Do we really have a type
			if (theString[0]) {
				UMiscUtils::PStringToOSType(theString, theType);
				
				theIDField->GetDescriptor(theString);
				// Do we really have an ID
				if (theString[0]) {
					::StringToNum(theString, &theLong);
					theID = (short) theLong;
					
					// Get the name
					theNameField->GetDescriptor(theString);
					
					// Retrieve the attributes
					theCheckBox = dynamic_cast<LCheckBox *>(theDialog->FindPaneByID( item_NewSysHeap ));
					ThrowIfNil_(theCheckBox);
					if (theCheckBox->GetValue()) {
						theAttrs |= resSysHeap;
					} 
					theCheckBox = dynamic_cast<LCheckBox *>(theDialog->FindPaneByID( item_NewPurgeable ));
					ThrowIfNil_(theCheckBox);
					if (theCheckBox->GetValue()) {
						theAttrs |= resPurgeable;
					} 
					theCheckBox = dynamic_cast<LCheckBox *>(theDialog->FindPaneByID( item_NewLocked ));
					ThrowIfNil_(theCheckBox);
					if (theCheckBox->GetValue()) {
						theAttrs |= resLocked;
					} 
					theCheckBox = dynamic_cast<LCheckBox *>(theDialog->FindPaneByID( item_NewProtected ));
					ThrowIfNil_(theCheckBox);
					if (theCheckBox->GetValue()) {
						theAttrs |= resProtected;
					} 
					theCheckBox = dynamic_cast<LCheckBox *>(theDialog->FindPaneByID( item_NewPreload ));
					ThrowIfNil_(theCheckBox);
					if (theCheckBox->GetValue()) {
						theAttrs |= resPreload;
					} 
					
					theRezObjItem = NewResource(theType, theID, &theString, theAttrs);
					SetModified(true);

				} else {
					UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("NoIDSpecified"), PPob_SimpleMessage);
					inLoop = true;
				}
			} else {
				UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("NoTypeSpecified"), PPob_SimpleMessage);
				inLoop = true;
			}
		}
	}
	return theRezObjItem;
}


// ---------------------------------------------------------------------------
//  NewResource														[public]
// ---------------------------------------------------------------------------

CRezObjItem *
CRezMapDoc::NewResource(ResType inType, short inID, Str255* inName, short inAttrs)
{
 	Boolean		replacing = false, applyToOthers = false;
	
	if ( mRezMap->HasResourceWithTypeAndId(inType, inID) ) {
		// Note: the applyToOthers argument is not relevant here. Ignore it.
		SInt16 answer = UMessageDialogs::AskSolveUidConflicts(inType, inID, applyToOthers, false);
		
		switch (answer) {
			case answer_Do:
			// Unique ID
			mRezMap->UniqueID(inType, inID, inID + 1);
			break;
			
			case answer_Dont:
			// Replace existing
			replacing = true;
			break;
			
			case answer_Cancel:
			return nil;
		}
	} 
	
	return DoCreateResource(inType, inID, inName, inAttrs, replacing);
}


// ---------------------------------------------------------------------------
//  DoCreateResource												[public]
// ---------------------------------------------------------------------------

CRezObjItem *
CRezMapDoc::DoCreateResource(ResType inType, short inID, Str255* inName, short inAttrs, Boolean inReplace)
{
	CRezTypeItem *	theRezTypeItem;
	CRezObjItem 	*oldRezObjItem, *newRezObjItem = NULL;
	CRezType *		theRezType;
	
	if ( ! mRezMapWindow->GetRezMapTable()->TypeExists(inType, theRezTypeItem) ) {
		// If the type does not already exist, create a new ResTypeItem
		theRezType = new CRezType(inType, mRezMap);
		theRezTypeItem = new CRezTypeItem( theRezType );
		mRezMapWindow->GetRezMapTable()->InsertRezTypeItem( theRezTypeItem );
	} else {
		theRezType = theRezTypeItem->GetRezType();
	}
	
	// Expand the RezType item now. If we expand too late, the pointer to
	// the RezObj item after expansion will not be the same as the one we
	// obtain with "new CRezObjItem" and the view will not redraw correctly
	// after validation of the edited new resource (size displayed as 0).
	if ( ! theRezTypeItem->IsExpanded() ) {
		theRezTypeItem->Expand();
	}

	if ( theRezTypeItem->ExistsItemForID(inID, oldRezObjItem) ) {
		// Found a rez obj item: remove it from the table and from the map
		// in memory. The second argument tells not to remove the RezTypeItem.
		RemoveResource(oldRezObjItem, false);
	} else {
		if (inReplace) {
			// Just remove the resource from memory
			CRezObj theRezObj(theRezType, inID );
			theRezObj.Remove();
		}
	} 
	
	// Now create a new RezObjItem
	newRezObjItem = new CRezObjItem( theRezType, inID, inName);
	ThrowIfNil_(newRezObjItem);
		
	// Add the resource to the resource map (err -194 = addResFailed)
	newRezObjItem->GetRezObj()->Add();
	
	// Set the attributes
	newRezObjItem->GetRezObj()->SetAttributesInMap(inAttrs);

	// Install the item in the table
	mRezMapWindow->GetRezMapTable()->InsertRezObjItem( newRezObjItem, theRezTypeItem );

	// Notify the type picker
	CPickerDoc * thePicker = GetTypePicker( theRezType->GetType() );
	if (thePicker != NULL) {
		thePicker->ListenToMessage(msg_RezObjCreated, &inID);
	} 

	// Redraw the window
	mRezMapWindow->Refresh();
	
	return newRezObjItem;
}


// ---------------------------------------------------------------------------
//  DuplicateResource												[public]
// ---------------------------------------------------------------------------

CRezObj *
CRezMapDoc::DuplicateResource(CRezObj * inRezObj)
{
	CRezTypeItem * theRezTypeItem;
	Str255 theName;
	
	if (mReadOnly) {
		return nil;
	} 
	
	ResType theType = inRezObj->GetType();
	short theAttrs = inRezObj->GetAttributes();
	
	LStr255 newName( *(inRezObj->GetName()) );
	newName += "\p copy";
	LString::CopyPStr(newName, theName);
	
	// Get an UID above the current ID
	short theID;
	mRezMap->UniqueID(theType, theID, inRezObj->GetID() + 1);
	
	// The type necessarily exists since we duplicate an existing resource. 
	// This call finds the corresponding RezTypeItem
	mRezMapWindow->GetRezMapTable()->TypeExists(theType, theRezTypeItem);
		
	// Now create a new RezObjItem
	CRezObjItem *theRezObjItem = new CRezObjItem( theRezTypeItem->GetRezType(), theID, &theName);
	ThrowIfNil_(theRezObjItem);
	
	// Add the resource to the resource map
	theRezObjItem->GetRezObj()->Add();
	
	// Copy the attributes of the duplicated resource
	theRezObjItem->GetRezObj()->SetAttributesInMap(theAttrs);
	
	// Copy the data handle
	Handle srcHandle = inRezObj->GetData();
	theRezObjItem->GetRezObj()->SetData( srcHandle );

	// Update the size field
	theRezObjItem->GetRezObj()->SetSize( ::GetHandleSize( srcHandle ) );
	
	// Mark the resource as modified in the rez map
	theRezObjItem->GetRezObj()->Changed();
	
	// Refresh the view
	if ( theRezTypeItem->IsExpanded() ) {
		// Install the item in the table
		mRezMapWindow->GetRezMapTable()->InsertRezObjItem( theRezObjItem, theRezTypeItem );
	} else {
		theRezTypeItem->Expand();
	}

	// Update the resource count field
	mRezMapWindow->SetRezCountField( mRezMapWindow->GetRezCountField() + 1 );

	// Document has been modified
	SetModified(true);

	// Redraw
	mRezMapWindow->Refresh();
	
	// Return the duplicated resource
	return theRezObjItem->GetRezObj();
}


// ---------------------------------------------------------------------------
//  RemoveResource												[public]
// ---------------------------------------------------------------------------
// "The RemoveResource function does not dispose of the handle you  pass  into
// it; to do so you must call the Memory Manager function DisposeHandle  after
// calling RemoveResource. You should  dispose  the  handle  if  you  want  to
// release the memory before updating or closing the resource fork.
// 
// If you've removed a  resource,  the  Resource  Manager  writes  the  entire
// resource map when it updates the resource fork, and all changes made to the
// resource map become permanent. If  you  want  any  of  the  changes  to  be
// temporary, you should restore the original information before the  Resource
// Manager updates the resource fork."

void
CRezMapDoc::RemoveResource(CRezObjItem* inRezObjItem, Boolean deleteTypeItem)
{
	if (mReadOnly) {
		return;
	} 
	
	short		theCount;
	OSErr		error;
	CRezObj *	theRezObj = inRezObjItem->GetRezObj();
	ResType		theType = theRezObj->GetType();
	short		theID = theRezObj->GetID();
	
	// If an editing window is opened for this resource, close it
	CEditorDoc * theRezEditor = GetRezEditor( theType, theID );
	if (theRezEditor != nil) {
		theRezEditor->SetModified(false);
		delete theRezEditor;
	} 
	// Notify the type picker
	CPickerDoc * thePicker = GetTypePicker(theType);
	if (thePicker != NULL) {
		thePicker->ListenToMessage(msg_RezObjDeleted, &theID);
	} 
	
	// Remove the resource from the rez map: if the resProtected flag is on, 
	// turn it off (otherwise error rmvResFailed)
	if (theRezObj->HasAttribute(resProtected)) {
		theRezObj->ToggleOneAttribute(resProtected);
	}
	theRezObj->Remove();
	
	// Remove the item from the table
	LOutlineItem* theSuperItem =  inRezObjItem->GetSuperItem();
	mRezMapWindow->GetRezMapTable()->RemoveItem(inRezObjItem);
	
	//CAVEAT: from now on, don't invoke theRezObj anymore, it's just been deleted.
	
	// Update the resource count field
	mRezMapWindow->SetRezCountField( mRezMapWindow->GetRezCountField() - 1 );

	// If there are no more resources of this type, remove the type item
	if (deleteTypeItem) {
		error = mRezMap->CountForType(theType, theCount);
		if (theCount == 0) {
			if (thePicker != NULL) {
				thePicker->ListenToMessage(msg_RezTypeDeleted, NULL);
			} 
			mRezMapWindow->GetRezMapTable()->RemoveItem(theSuperItem);
			// Update the types count field
			mRezMapWindow->SetTypeCountField( mRezMapWindow->GetTypeCountField() - 1 );
		}
	} 
	
	// Document has been modified
	SetModified(true);
}


// ---------------------------------------------------------------------------
//  PasteRezMap												[public]
// ---------------------------------------------------------------------------

void
CRezMapDoc::PasteRezMap(CRezMap * srcRezMap)
{
	short		numTypes, numResources;
    ResType 	theType;
	short		theID, theAttrs;
	short		theSrcRefNum;
	Handle		theRezHandle;
	OSErr		error = noErr;
	Boolean		applyToOthers = false;
	SInt16		answer;
	MessageT 	theAction = answer_Do;
	CRezObj *	theRezObj;
	
	if (mReadOnly) {
		::SysBeep(3);
		return;
	} 
	
	if (srcRezMap == NULL) {
		return;
	} 
	
	theSrcRefNum = srcRezMap->GetRefnum();
	
	error = srcRezMap->CountAllTypes(numTypes);
	if (error != noErr || numTypes == 0) {return;}
	
	for (UInt16 i = 1; i <= numTypes; i++ ) {
		
		// Read in each data type
		srcRezMap->GetTypeAtIndex(i, theType );
		error = srcRezMap->CountForType( theType, numResources);
		if (error != noErr) {continue;}

		for (UInt16 j = 1; j <= numResources; j++) {
			// Get the data handle
			error = srcRezMap->GetResourceAtIndex(theType, j, theRezHandle);
			
			if (error == noErr) {
				// Make a rez object out of it
				try {
					Boolean replace = false;
					
					theRezObj = new CRezObj(theRezHandle, theSrcRefNum);
					theAttrs = theRezObj->GetAttributes();
					theID = theRezObj->GetID();
					
					if ( mRezMap->HasResourceWithTypeAndId(theType, theID)) {
						if (!applyToOthers) {
							answer = UMessageDialogs::AskSolveUidConflicts(theType, theID, applyToOthers);
							theAction = answer;
						} else {
							answer = theAction;
						}
						switch (answer) {
							case answer_Do:
							mRezMap->UniqueID(theType, theID, theID + 1);
							break;
							
							case answer_Dont:
							replace = true;
							break;
							
							case answer_Cancel:
							return;
						}
					} 
					PasteResource(theType, theID, theRezHandle, theRezObj->GetName(), theAttrs, replace);			
					
					delete theRezObj;
				} catch (...) { }
			} 
		}
	}
}


// ---------------------------------------------------------------------------
//  PasteResource												[public]
// ---------------------------------------------------------------------------

void
CRezMapDoc::PasteResource(ResType inType, short inID, Handle inHandle, 
						  Str255* inName, short inAttrs, Boolean replaceExisting)
{
	CRezTypeItem *	theRezTypeItem;
	CRezType *		theRezType;
	CRezObjItem *	theRezObjItem;

	if (mReadOnly) {
		return;
	} 
	
	// Bug #10 reported by ZPedro: previously, if one attempted to paste a
	// resource and overwrote an existing resource, the code would crash if
	// the overwritten resource was the only one of its type, because the
	// existing resource was first deleted, causing the CRezTypeItem to be
	// destroyed as well, and then the code attempted to use a pointer to
	// the deleted object to insert the new resource. Crash.
	// 
	// (bd 2006-09-05) fixed this by adding a second argument to
	// RemoveResource() specifying whether or not to delete the
	// CRezTypeItem. This fixes it also in DoCreateResource() where the
	// same situation can occur.

	// Find if there is already a CRezTypeItem for the specified type. If not, create one. 
	if ( ! mRezMapWindow->GetRezMapTable()->TypeExists(inType, theRezTypeItem) ) {
		// If the type does not already exist, create a new ResTypeItem
		theRezType = new CRezType(inType, mRezMap);
		theRezTypeItem = new CRezTypeItem( theRezType );
		mRezMapWindow->GetRezMapTable()->InsertRezTypeItem( theRezTypeItem );
		// Update the types count field
		mRezMapWindow->SetTypeCountField( mRezMapWindow->GetTypeCountField() + 1 );
	} else {
		theRezType = theRezTypeItem->GetRezType();
		if ( ! theRezTypeItem->IsExpanded() ) {
			theRezTypeItem->Expand();
		}
		if (replaceExisting) {
			// Remove the corresponding entry from the table if it is visible
			theRezObjItem = mRezMapWindow->GetRezMapTable()->GetRezObjItem(inType, inID);
			if (theRezObjItem) {
				// The second argument tells not to remove the RezTypeItem
				RemoveResource(theRezObjItem, false);
			} 
		} 
	}

	// Now create a new RezObjItem
	theRezObjItem = new CRezObjItem( theRezTypeItem->GetRezType(), inID, inName);
	ThrowIfNil_(theRezObjItem);

	// Copy the data to the mData handle
	theRezObjItem->GetRezObj()->SetData( inHandle );
	
	// Set mSize
	theRezObjItem->GetRezObj()->SetSize( ::GetHandleSize(inHandle) );

	// Add the resource to the resource map
	theRezObjItem->GetRezObj()->Add();
	
	// Copy the attributes of the duplicated resource
	theRezObjItem->GetRezObj()->SetAttributesInMap(inAttrs);
	
	// Mark the resource as modified in the rez map
	theRezObjItem->GetRezObj()->Changed();
	
	// Document has been modified
	SetModified(true);

	// Refresh the view
	if ( theRezTypeItem->IsExpanded() ) {
		// Install the item in the table
		mRezMapWindow->GetRezMapTable()->InsertRezObjItem( theRezObjItem, theRezTypeItem );
	} else {
		theRezTypeItem->Expand();
	}
	// Update the resource count field
	mRezMapWindow->SetRezCountField( mRezMapWindow->GetRezCountField() + 1 );
	// Redraw
	mRezMapWindow->Refresh();
}


// ---------------------------------------------------------------------------
//  GetRezEditor												[public]
// ---------------------------------------------------------------------------
// ResType is an unsigned long

CEditorDoc *
CRezMapDoc::GetRezEditor(ResType inType, short inID, Boolean exact)
{
	CEditorDoc * result = nil;	
	TArrayIterator<CEditorDoc *> iterator(*mOpenedEditors);
	CEditorDoc*	theRezEditor = nil;
	
	// The CRezMapDoc class maintains a list of all opened CEditorDocs
	while (iterator.Next(theRezEditor)) {
		if (CEditorsController::TypesCorrespond( inType, theRezEditor->GetRezObj()->GetType(), exact) 
			&& 
			inID == theRezEditor->GetRezObj()->GetID() ) {
			result = theRezEditor;
			break;
		} 
	}
	
	return result;
}


// ---------------------------------------------------------------------------
//  DeleteEditors												[public]
// ---------------------------------------------------------------------------
// Delete all the editor windows depending from this rezmap and reset the array

void
CRezMapDoc::DeleteEditors(Boolean deleteArray)
{
	if (mOpenedEditors != nil) {
		TArrayIterator<CEditorDoc *> iterator(*mOpenedEditors, LArrayIterator::from_End);
		CEditorDoc* theRezEditor = nil;
		while (iterator.Previous(theRezEditor)) {
			mOpenedEditors->RemoveItemsAt(1, iterator.GetCurrentIndex());
			delete theRezEditor;
		}
		if (deleteArray) {
			delete mOpenedEditors;
		} 
	} 
}


// ---------------------------------------------------------------------------
//  GetTypePicker												[public]
// ---------------------------------------------------------------------------

CPickerDoc *
CRezMapDoc::GetTypePicker(ResType inType)
{
	CPickerDoc * result = nil;	
	TArrayIterator<CPickerDoc *> iterator(*mOpenedPickers);
	CPickerDoc*	theTypePicker = nil;
	
	// The CRezMapDoc class maintains a list of all opened CPickerDocs
	while (iterator.Next(theTypePicker)) {
		if (inType == theTypePicker->GetRezTypeItem()->GetRezType()->GetType() ) {
			result = theTypePicker;
			break;
		} 
	}
	
	return result;
}


// ---------------------------------------------------------------------------
//  DeletePickers												[public]
// ---------------------------------------------------------------------------
// Delete all the picker windows depending from this rezmap and reset the array

void
CRezMapDoc::DeletePickers(Boolean deleteArray)
{
	if (mOpenedPickers != nil) {
		TArrayIterator<CPickerDoc *> iterator(*mOpenedPickers, LArrayIterator::from_End);
		CPickerDoc* theRezPicker = nil;
		while (iterator.Previous(theRezPicker)) {
			mOpenedPickers->RemoveItemsAt(1, iterator.GetCurrentIndex());
			delete theRezPicker;
		}
		if (deleteArray) {
			delete mOpenedPickers;
		} 
	} 
}


// ---------------------------------------------------------------------------
//  GetRezMapFromXml													[public]
// ---------------------------------------------------------------------------
// // Rezilla DTD
// // 
// // 			<!ELEMENT RezMap (
// // 					RezMapName,
// // 					RezMapFlags,
// // 					TypesArray
// // 					)
// // 			>
// // 
// // 			<!ELEMENT TypesArray (Type)*>
// // 
// // 			<!ELEMENT Type (
// // 					TypeCode,
// // 					ResourcesArray
// // 					)
// // 			>
// // 
// // 			<!ELEMENT ResourcesArray (Resource*)>
// // 
// // 			<!ELEMENT Resource (
// // 					ResourceName, 
// // 					ResourceID, 
// // 					ResourceFlags, 
// // 					ResourceSize?, 
// // 					ResourceData?
// // 					)
// // 			>

OSErr
CRezMapDoc::GetRezMapFromXml(CFXMLTreeRef inTreeRef)
{
	OSErr			error = noErr;
	int             docCount, typCount;
	CFXMLTreeRef    docTree, typTree;
	CFXMLNodeRef    docNode, typNode;
	int             docIndex, typIndex;
	SInt32			theLong;
	short			mapAttrs;
	
	docCount = CFTreeGetChildCount(inTreeRef);
	for (docIndex = 0; docIndex < docCount; docIndex++) {
		docTree = CFTreeGetChildAtIndex(inTreeRef, docIndex);
		if (docTree) {
			docNode = CFXMLTreeGetNode(docTree);
			if (docNode) {
				if ( ! CFStringCompare( CFXMLNodeGetString(docNode), CFSTR("RezMapName"), 0) ) {
					// Ignore			
				} else if ( ! CFStringCompare( CFXMLNodeGetString(docNode), CFSTR("RezMapFlags"), 0) ) {
					// This value will be set at the end
					UMiscUtils::GetValueFromXml(docTree, theLong);
					mapAttrs = theLong;
				} else if ( ! CFStringCompare( CFXMLNodeGetString(docNode), CFSTR("TypesArray"), 0) ) {
					typCount = CFTreeGetChildCount(docTree);
					for (typIndex = 0; typIndex < typCount; typIndex++) {
						typTree = CFTreeGetChildAtIndex(docTree, typIndex);
						if (typTree) {
							typNode = CFXMLTreeGetNode(typTree);
							if (typNode) {
								if ( ! CFStringCompare( CFXMLNodeGetString(typNode), CFSTR("Type"), 0) ) {
									error = GetTypeFromXml(typTree);
									if (error != noErr) { break; } 
								}
							} 
						} 
					}
				} else {
					// // CFShow(CFXMLNodeGetString(docNode));
					error = err_ImportUnknownRezMapTag;	
				} 

				if (error != noErr) { break; } 
			} 
		} 
	}

	if (error == noErr) {
		mRezMap->SetMapAttributes(mapAttrs);
	} 
	
	return error;
}


OSErr
CRezMapDoc::GetTypeFromXml(CFXMLTreeRef inTreeRef)
{
	OSErr			error = noErr;
	int             typCount, resCount;
	CFXMLTreeRef    typTree, resTree;
	CFXMLNodeRef    typNode, resNode;
	int             typIndex, resIndex;
	Boolean			gotType = false;
	ResType			theType;
	
	typCount = CFTreeGetChildCount(inTreeRef);
	for (typIndex = 0; typIndex < typCount; typIndex++) {
		typTree = CFTreeGetChildAtIndex(inTreeRef, typIndex);
		if (typTree) {
			typNode = CFXMLTreeGetNode(typTree);
			if (typNode) {
				if ( ! CFStringCompare( CFXMLNodeGetString(typNode), CFSTR("TypeCode"), 0) ) {
					error = UMiscUtils::GetOSTypeFromXml(typTree, theType);
					if (error != noErr) { break; } 
					gotType = true;
				} else if ( ! CFStringCompare( CFXMLNodeGetString(typNode), CFSTR("ResourcesArray"), 0) ) {
					// At this point, we must have the type
					if (!gotType) {
						error = err_ImportMissingResourceType;
					} else {
						resCount = CFTreeGetChildCount(typTree);
						for (resIndex = 0; resIndex < resCount; resIndex++) {
							resTree = CFTreeGetChildAtIndex(typTree, resIndex);
							if (resTree) {
								resNode = CFXMLTreeGetNode(resTree);
								if (resNode) {
									if ( ! CFStringCompare( CFXMLNodeGetString(resNode), CFSTR("Resource"), 0) ) {
										error = GetResourceFromXml(resTree, theType);
										if (error != noErr) { break; } 
									}
								} 
							} 
						}
					}
				} else {
					// // CFShow(CFXMLNodeGetString(typNode));
					error = err_ImportUnknownRezMapTag;	
				} 

				if (error != noErr) { break; } 
			} 
		} 
	}
	
	return error;
}


OSErr
CRezMapDoc::GetResourceFromXml(CFXMLTreeRef inTreeRef, ResType inType)
{
	OSErr			error = noErr;
	int             theCount;
	CFXMLTreeRef    theTree;
	CFXMLNodeRef    theNode;
	int             theIndex;
	Boolean			gotID = false;
	SInt32			theLong;
	short			theID;
	Str255			theName;
	short			theAttrs;
	Handle			theHandle = NULL;
	
	theCount = CFTreeGetChildCount(inTreeRef);
	for (theIndex = 0; theIndex < theCount; theIndex++) {
		theTree = CFTreeGetChildAtIndex(inTreeRef, theIndex);
		if (theTree) {
			theNode = CFXMLTreeGetNode(theTree);
			if (theNode) {
				if ( ! CFStringCompare( CFXMLNodeGetString(theNode), CFSTR("ResourceName"), 0) ) {
					UMiscUtils::GetStringFromXml(theTree, theName);
				} else if ( ! CFStringCompare( CFXMLNodeGetString(theNode), CFSTR("ResourceID"), 0) ) {
					UMiscUtils::GetValueFromXml(theTree, theLong);
					theID = (short) theLong;				
					gotID = true;
				} else if ( ! CFStringCompare( CFXMLNodeGetString(theNode), CFSTR("ResourceFlags"), 0) ) {
					UMiscUtils::GetValueFromXml(theTree, theLong);
					theAttrs = (short) theLong;				
				} else if ( ! CFStringCompare( CFXMLNodeGetString(theNode), CFSTR("ResourceSize"), 0) ) {
					// Ignore
				} else if ( ! CFStringCompare( CFXMLNodeGetString(theNode), CFSTR("ResourceData"), 0) ) {
					error = UMiscUtils::GetBinaryFromXml(theTree, &theHandle);				
				} else {
					// // CFShow(CFXMLNodeGetString(theNode));
					error = err_ImportUnknownRezMapTag;	
				} 

				if (error != noErr) { break; } 
			} 
		} 
	}
	
	if (!gotID) {
		error = err_ImportMissingResourceID;	
	} else if ( mRezMap->HasResourceWithTypeAndId(inType, theID) ) {
		error = err_ImportConflictingResourceID;	
	} else {
		CRezObjItem * theRezObjItem = DoCreateResource(inType, theID, &theName, theAttrs, false);
		if (theHandle) {
			if (theRezObjItem) {
				CRezObj * theRezObj = theRezObjItem->GetRezObj();
				if (theRezObj) {
					theRezObj->SetData(theHandle);
				} 
			} 
			::DisposeHandle(theHandle);
		} 
	}
	
	return error;
}



PP_End_Namespace_PowerPlant


