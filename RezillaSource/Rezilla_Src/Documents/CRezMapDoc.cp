// ===========================================================================
// CRezMapDoc.cp					
// 
//                       Created: 2003-04-29 07:11:00
//             Last modification: 2005-01-30 19:26:44
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

PP_Begin_Namespace_PowerPlant


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CRezMapDoc.h"
#include "CRezillaApp.h"
#include "CRezillaPrefs.h"
#include "CRezFile.h"
#include "CEditorsController.h"
#include "CTemplatesController.h"
#include "CTextFileStream.h"
#include "CRezMap.h"
#include "CRezMapTable.h"
#include "CRezMapWindow.h"
#include "CRezObj.h"
#include "CRezObjItem.h"
#include "CRezType.h"
#include "CRezTypeItem.h"
#include "CRezTypePicker.h"
#include "CInspectorWindow.h"
#include "CHexEditorDoc.h"
#include "CTmplEditorDoc.h"
#include "CWindowMenu.h"
#include "CRezClipboard.h"
#include "CRecentItemsMenu.h"
#include "RezillaConstants.h"
#include "UDialogBoxHandler.h"
#include "UMessageDialogs.h"
#include "UCompareUtils.h"
#include "UMiscUtils.h"
#include "URezExporter.h"
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




// ---------------------------------------------------------------------------
//	¥ CRezMapDoc							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CRezMapDoc::CRezMapDoc(LCommander *inSuper)
	: LDocument( inSuper )
{
	mFork = CRezillaPrefs::GetPrefValue(kPref_general_newFork);
	mRezFile = nil;
	
	Initialize(nil, kResFileNotOpened);
}


// ---------------------------------------------------------------------------
//	¥ CRezMapDoc							Constructor		  [public]
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
//	¥ CRezMapDoc							Constructor		  [public]
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
//	¥ CRezMapDoc							Constructor		  [public]
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
//	¥ ~CRezMapDoc							Destructor				  [public]
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
	
	if (mRezMap != nil) {
		delete mRezMap;
	} 
	
	if (mTypesArray != nil) {
		delete mTypesArray;
	} 
	
	// Note: mFileStream is deleted in DoAEExport()

	// Unregister from the static RezMapDocs list
	CRezillaApp::sRezMapDocList.Remove(this);

	// Clear the Inspector if it contains info about a resource belonging to this rezmap
	if (CRezillaApp::sInspectorWindow != nil &&
		CRezillaApp::sInspectorWindow->GetRezObjItem() != nil &&
		CRezillaApp::sInspectorWindow->GetRezObjItem()->GetOwnerRezMapTable()->GetOwnerDoc() == this
	) {
		CRezillaApp::sInspectorWindow->ClearValues();
	} 
	
	// Delete the RezEditors associated to this document
	if (mOpenedEditors != nil) {
		TArrayIterator<CEditorDoc *> iterator(*mOpenedEditors, LArrayIterator::from_End);
		CEditorDoc* theRezEditor = nil;
		while (iterator.Previous(theRezEditor)) {
			 delete theRezEditor;
		}
		
		delete mOpenedEditors;
	} 

	if (mRezMapWindow != nil) {
		// Remove the window from the window menu.
		gWindowMenu->RemoveWindow( mRezMapWindow );
		// Delete the RezMapWindow associated to this document
		delete mRezMapWindow;
	} 
	
	// 	// Remove ourselves from the list of listeners to the prefs object
	// 	CRezillaApp::sPrefs->RemoveListener(this);
}


// ---------------------------------------------------------------------------
//	¥ Initialize													  [public]
// ---------------------------------------------------------------------------

void
CRezMapDoc::Initialize(FSSpec * inFileSpec, short inRefnum)
{		
	mUpdateOnClose = true;
	mExportFormat = exportMap_Xml;
	mFileStream   = nil;
	mReadOnly = false;
	
	SetModelKind(rzil_cRezMapDoc);

	if (mRezFile == nil) {
		if (inFileSpec != nil) {
			mRezFile = new CRezFile(*inFileSpec, inRefnum, mFork);
			SetSpecified(true);
		} else {
			mRezFile = new CRezFile();
		}
	} 
	
	if (inFileSpec != nil) {
		SetSpecified(true);
	} 

	mRezFile->SetOwnerDoc(this);
	
	// Register to the static RezMapDocs list
	CRezillaApp::sRezMapDocList.AddItem(this);

	// Create the CRezMap class instance
	mRezMap = new CRezMap(inRefnum);
	
	// Create window for our document.
	mRezMapWindow = dynamic_cast<CRezMapWindow *>(LWindow::CreateWindow( PPob_RezMapWindow, this));
	Assert_( mRezMapWindow != nil );

	// Make this document the supercommander of the RezMapWindow
// 	mRezMapWindow->SetSuperCommander(this);
// 	mRezMapWindow->SetOwnerDoc(this);
	
	// The RezMapTable keeps a pointer to the RezMap object
	mRezMapWindow->GetRezMapTable()->SetRezMap(mRezMap);

	// Set name of window
	if ( inFileSpec == nil ) {
		NameNewDoc();
	} else {
		// Set window title to the name of the file.
		mRezMapWindow->SetDescriptor( inFileSpec->name );
	}

	// Initialize the array of edited resources
	mOpenedEditors = new TArray<CEditorDoc *>();
	
	// Populate the RezTable
	CTypeComparator* theComparator = new CTypeComparator;
	mTypesArray = new TArray<ResType>( theComparator, true);
	mRezMap->GetAllTypes(mTypesArray);
	mRezMapWindow->GetRezMapTable()->Populate(mTypesArray);

	// Link the window to the file's data (icon, creator, type)
	::SetWindowProxyFSSpec(mRezMapWindow->GetMacWindow(), inFileSpec);
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
//	¥ ObeyCommand									[public, virtual]
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

		case cmd_ExportMap: {
			FSSpec	theFSSpec;
			AskExportAs(theFSSpec, RecordAE_Yes);
			break;
		}

		case cmd_NewRez: 
		CRezObjItem * theRezObjItem = NewResDialog();
		if (theRezObjItem != NULL) {
			mRezMapWindow->RecalcCountFields();
			// Select the newly created item 
			mRezMapWindow->GetRezMapTable()->UnselectAllCells();
			TryEdit(theRezObjItem, cmd_EditRez);
		} 
		break;
		
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
		case cmd_EditRezAsType: {
			ResType asType = 0;
			LArray* theArray = new LArray( sizeof(LOutlineItem*) );
			int		countEdited = 0;
			UInt32	countItems;
			
			mRezMapWindow->GetRezMapTable()->GetAllSelectedRezObjItems(theArray);
			countItems = theArray->GetCount();
			LArrayIterator iterator(*theArray);
			CRezObjItem * theItem = nil;
			
			if (inCommand == cmd_EditRezAsType) {
				CRezTypePicker * rezPicker = new CRezTypePicker();
				if (rezPicker != NULL) {
					if (rezPicker->RunDialog() == noErr) {
						asType = rezPicker->GetChosenType();
					} 
					delete rezPicker;
				} 
			} 
			
			while (iterator.Next(&theItem)) {
				countEdited += TryEdit(theItem, inCommand, asType);
			}

			if (countEdited != 0) {
				if (countEdited == 1 && countItems == 1) {
						UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("ThisResourceEditedInOtherMode"), PPob_SimpleMessage);
				} else {
					UMessageDialogs::AlertWithValue(CFSTR("SomeResourcesEditedInOtherMode"), countEdited);
				}
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
// 			if (mReadOnly) {
// 			}
			break;
		}

		case cmd_ActionDeleted: {
// 			if (mTypingAction == static_cast<CHexEditorTypingAction*>(ioParam)) {
// 				mTypingAction = nil;
// 			}
			break;
		}

		default: {
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
			
			// call the right GUI editor
			CEditorsController::InvokeCustomEditor(this, inRezObjItem, *substTypePtr);
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
//	¥ SetModified													  [public]
// ---------------------------------------------------------------------------

void
CRezMapDoc::SetModified(Boolean	inModified)
{
	LDocument::SetModified(inModified);
	::SetWindowModified(mRezMapWindow->GetMacWindow(), inModified);	
}


// ---------------------------------------------------------------------------
//	¥ GetDescriptor													  [public]
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
//  GetOwnerRefnum												[public]
// ---------------------------------------------------------------------------

short
CRezMapDoc::GetRefnum() 
{ 
	return mRezMap->GetRefnum();
}


// ---------------------------------------------------------------------------
//  GetOwnerRefnum												[public]
// ---------------------------------------------------------------------------

void
CRezMapDoc::SetRefnum(short inRefnum) 
{ 
	mRezMap->SetRefnum(inRefnum);
}
	

// ---------------------------------------------------------------------------
//	¥ UsesFileSpec													  [public]
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
//	¥ HasExportSpec													  [public]
// ---------------------------------------------------------------------------
//	Returns whether the Document's FileStream corresponds to the given FSSpec

Boolean
CRezMapDoc::HasExportSpec(
	const FSSpec&	inFileSpec) const
{
	Boolean usesFS = false;

	if (mFileStream != nil) {
		usesFS = mFileStream->UsesSpecifier(inFileSpec);
	}

	return usesFS;
}


// ---------------------------------------------------------------------------
//	¥ AttemptClose													  [public]
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
			} else {
				mUpdateOnClose = false;
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
//	¥ AskSaveChanges												  [public]
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


// ---------------------------------------------------------------------------------
//  DoAESave
// ---------------------------------------------------------------------------------
// Called when doing a SaveAs.

void
CRezMapDoc::DoAESave(
	FSSpec	&inFileSpec)
{
	OSErr error;
	SInt16 oldFork = mRezFile->GetUsedFork();
	CRezMapTable* theRezMapTable = mRezMapWindow->GetRezMapTable();
	
	if (mFork == fork_samefork) {
		mFork = mRezFile->GetUsedFork();
	} 
	
	// Make a new file object
	CRezFile * theNewFile = new CRezFile( inFileSpec, kResFileNotOpened, mFork );
	ThrowIfNil_(theNewFile);
	
	theNewFile->SetOwnerDoc(this);
	
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
			mRezMap = new CRezMap( theNewFile->GetRefnum() );

			// Set window title to the name of the file.
			mRezMapWindow->SetDescriptor(inFileSpec.name);
			
			// Register to the Recent Items menu
			CRezillaApp::GetRecentItemsAttachment()->AddFile(inFileSpec, true);
			
			// Document has a specified file
			SetSpecified(true);
			
			// Mark as unmodified
			SetModified(false);
			
			if (mRezFile->GetUsedFork() != oldFork) {
				mRezMapWindow->InstallWhichForkField();
			} 
			
			// Rebuild the RezMapTable and redraw
			theRezMapTable->SetOwnerRefnum( mRezMap->GetRefnum() );
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
}


// ---------------------------------------------------------------------------------
//  DoSave
// ---------------------------------------------------------------------------------

void
CRezMapDoc::DoSave()
{
	OSErr error;

	error = mRezMap->Update();
	
	if (error != noErr) {
		UMessageDialogs::ErrorWithString(CFSTR("ErrorSavingRezMapDoc"), error);
	} else {
		// Mark the document as non modified
		SetModified(false);
	}
}


// ---------------------------------------------------------------------------
//	¥ CheckEditorsUnmodified										[public]
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
//	¥ AskSaveAs														  [public]
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
				// name. This is the same thing as a regular save.
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

				if (replacing) {		// Delete existing file
					ThrowIfOSErr_(::FSpDelete(&outFSSpec));
				}

				DoAESave(outFSSpec);
				saveOK = true;
			}
		}		
	}

	return saveOK;
}


// ---------------------------------------------------------------------------
//	¥ DoRevert														  [public]
// ---------------------------------------------------------------------------
//	Revert a Document to its last saved version

void
CRezMapDoc::DoRevert()
{
	FSSpec		theFSSpec;
	short		theRefNum;
	SInt16		theFork;
	OSErr		error;
	
	// Delete all the editor windows depending from this rezmap and reset the array
    if (mOpenedEditors != nil) {
        TArrayIterator<CEditorDoc *> iterator(*mOpenedEditors, LArrayIterator::from_End);
        CEditorDoc* theRezEditor = nil;
        while (iterator.Previous(theRezEditor)) {
			mOpenedEditors->RemoveItemsAt(1, iterator.GetCurrentIndex());
			delete theRezEditor;
        }
    } 
	
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
		mRezFile->SetOwnerDoc(this);
	} else {
		dynamic_cast<CRezillaApp *>(GetSuperCommander())->ReportOpenForkError(error, &theFSSpec);
		return;
	}
	
	// Delete the RezMap object and create a new one
	if (mRezMap != nil) {
		delete mRezMap;
	} 
	mRezMap = new CRezMap(theRefNum);
	
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
//	¥ AskConfirmRevert												  [public]
// ---------------------------------------------------------------------------
//	Ask user to confirm discarding changes and reverting to the last
//	saved version of the RezMapDoc

bool
CRezMapDoc::AskConfirmRevert()
{
	return UMessageDialogs::AskIfFromLocalizable(CFSTR("ConfirmRevertRezMapDoc"), PPob_AskIfMessage);
}


// ---------------------------------------------------------------------------
//	¥ DesignateOutFile								[public static]
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
//	¥ AskExportAs														  [public]
// ---------------------------------------------------------------------------
//	Ask the user to export a Document and give it a name
//	Returns false if the user cancels the operation

Boolean
CRezMapDoc::AskExportAs(
	FSSpec&		outFSSpec,
	Boolean		inRecordIt)
{
	Boolean		saveOK = false;
	bool		replacing;

	if ( DesignateExportFile(outFSSpec, replacing) ) {

		if (replacing && HasExportSpec(outFSSpec)) {
									// User chose to replace the file with
									//   one of the same name. This is the
									//   same thing as a regular save.
			if (inRecordIt) {
				SendSelfAE(kAECoreSuite, kAESave, ExecuteAE_No);
			}

			DoExport();
			saveOK = true;

		} else {

			if (inRecordIt) {
				try {
// 					SendAEExport(outFSSpec, mExportFormat, ExecuteAE_No);
				} catch (...) { }
			}

			if (replacing) {		// Delete existing file
				ThrowIfOSErr_(::FSpDelete(&outFSSpec));
			}

			DoAEExport(outFSSpec);
			saveOK = true;
		}
	}

	return saveOK;
}


// ---------------------------------------------------------------------------
//	¥ DesignateExportFile								[public static]
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
//  DoAEExport
// ---------------------------------------------------------------------------------

void
CRezMapDoc::DoAEExport(
	FSSpec	&inFileSpec)
{
	OSErr	err = noErr;

	// Delete the existing file object.
	if (mFileStream != nil) {
		delete mFileStream;
	} 
	
	// Make a new file object.
	mFileStream = new CTextFileStream( inFileSpec );
	
	if (mFileStream != nil) {
		// Get the proper file type.
		OSType	theFileType = 'TEXT';
		
		// Make new file on disk (we use TextEdit's creator).
		mFileStream->CreateNewDataFile( (OSType) CRezillaPrefs::GetPrefValue(kPref_export_editorSig), theFileType );
		
		// Write out the data.
		DoExport();
		
		// Free memory which we don't need anymore
		delete mFileStream;
	}	
}


// ---------------------------------------------------------------------------------
//  DoExport
// ---------------------------------------------------------------------------------

void
CRezMapDoc::DoExport()
{
	// Open the data fork.
	mFileStream->OpenDataFork( fsWrPerm );
	
	WriteOutExport(mExportFormat);
	
	// Close the data fork.
	mFileStream->CloseDataFork();
}


// ---------------------------------------------------------------------------------
//  WriteOutExport
// ---------------------------------------------------------------------------------

void
CRezMapDoc::WriteOutExport(SInt16 inExportFormat)
{	
	StRezExporter	exporter(mFileStream);
	switch ( inExportFormat ) {
		case exportMap_Xml:
		exporter.WriteOutXml(mRezMap, 
							 CRezillaPrefs::GetPrefValue(kPref_export_formatDtd),
							 CRezillaPrefs::GetPrefValue(kPref_export_includeBinary),
							 CRezillaPrefs::GetPrefValue(kPref_export_dataEncoding));
		break;
		
		case exportMap_Text:
		exporter.WriteOutText(mRezMap, 
							 CRezillaPrefs::GetPrefValue(kPref_export_includeBinary),
							 CRezillaPrefs::GetPrefValue(kPref_export_dataEncoding));
		break;
		
		case exportMap_Html:
		exporter.WriteOutHtml(mRezMap, 
							 CRezillaPrefs::GetPrefValue(kPref_export_includeBinary),
							 CRezillaPrefs::GetPrefValue(kPref_export_dataEncoding));
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
// 			LString::CopyPStr( "\pFind in MapÉ", outName);
// 			outEnabled = true;
			outEnabled = false;
			break;
								
		case cmd_ExportMap:
			outEnabled = true;
			break;
		
		case cmd_EditRez:
		case cmd_EditRezAsType:
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
	LDialogBox *		theDialog = theHandler.GetDialog();
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
						::StringToNum(theString, (long *) &theType);
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
					
					theRezObjItem = CreateNewRes(theType, theID, &theString, theAttrs);
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
//  CreateNewRes												[public]
// ---------------------------------------------------------------------------

CRezObjItem *
CRezMapDoc::CreateNewRes(ResType inType, short inID, Str255* inName, short inAttrs)
{
	CRezTypeItem * theRezTypeItem;
	CRezObjItem *oldRezObjItem, *newRezObjItem = NULL;
	CRezType * theRezType;
	Boolean replacing = false, applyToOthers = false;
	
	if ( mRezMap->ResourceExists(inType, inID) ) {
		SInt16 answer = UMessageDialogs::AskSolveUidConflicts(inType, inID, applyToOthers, false);
		
		switch (answer) {
			case answer_Do:
			// Unique ID
			mRezMap->UniqueID(inType, inID);
			break;
			
			case answer_Dont:
			// Replace existing
			replacing = true;
			break;
			
			case answer_Cancel:
			return newRezObjItem;
			break;
		}
	} 
	
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

	if (replacing) {
		if ( theRezTypeItem->ExistsItemForID(inID, oldRezObjItem) ) {
			// Found a rez obj item: remove it from the table (and from the map in memory)
			RemoveResource(oldRezObjItem);
		} else {
			// Just remove the resource from memory
			CRezObj * theRezObj = new CRezObj(theRezType, inID );
			theRezObj->Remove();
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

	// Redraw the window
	mRezMapWindow->Refresh();
	
	return newRezObjItem;
}


// ---------------------------------------------------------------------------
//  GetRezEditor												[public]
// ---------------------------------------------------------------------------
// ResType is an unsigned long

CEditorDoc *
CRezMapDoc::GetRezEditor(ResType inType, short inID)
{
	CEditorDoc * result = nil;	
	TArrayIterator<CEditorDoc *> iterator(*mOpenedEditors);
	CEditorDoc*	theRezEditor = nil;
	
	// The CRezMapDoc class maintains a list of all opened CEditorDoc's
	while (iterator.Next(theRezEditor)) {
		if (inType == theRezEditor->GetRezObj()->GetType() && inID == theRezEditor->GetRezObj()->GetID() ) {
			result = theRezEditor;
			break;
		} 
	}
	
	return result;
}


// ---------------------------------------------------------------------------
//  DuplicateResource												[public]
// ---------------------------------------------------------------------------

void
CRezMapDoc::DuplicateResource(CRezObj* inRezObj)
{
	CRezTypeItem * theRezTypeItem;
	Str255 theName;
	
	if (mReadOnly) {
		return;
	} 
	
	ResType theType = inRezObj->GetType();
	short theAttrs = inRezObj->GetAttributes();
	
	LStr255 newName( *(inRezObj->GetName()) );
	newName += "\p copy";
	LString::CopyPStr(newName, theName);
	
	// Get an UID
	short theID;
	mRezMap->UniqueID(theType, theID);
	
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

	// Update the resources count field
	mRezMapWindow->SetCountRezField( mRezMapWindow->GetCountRezField() + 1 );

	// Document has been modified
	SetModified(true);

	// Redraw
	mRezMapWindow->Refresh();
}


// ---------------------------------------------------------------------------
//  RemoveResource												[public]
// ---------------------------------------------------------------------------
// "The RemoveResource function does not dispose of the handle you  pass  into
// it; to do so you must call the Memory Manager function DisposeHandle  after
// calling RemoveResource. You should  dispose  the  handle  if  you  want  to
// release the memory before updating or closing the resource fork.
// 
// If youÕve removed a  resource,  the  Resource  Manager  writes  the  entire
// resource map when it updates the resource fork, and all changes made to the
// resource map become permanent. If  you  want  any  of  the  changes  to  be
// temporary, you should restore the original information before the  Resource
// Manager updates the resource fork."

void
CRezMapDoc::RemoveResource(CRezObjItem* inRezObjItem)
{
	short theCount;
	OSErr error;

	if (mReadOnly) {
		return;
	} 
	
	CRezObj * theRezObj = inRezObjItem->GetRezObj();
	
	// If an editing window is opened for this resource, close it
	CEditorDoc * theRezEditor = GetRezEditor( theRezObj->GetType(), theRezObj->GetID() );
	if (theRezEditor != nil) {
		theRezEditor->SetModified(false);
		delete theRezEditor;
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
	
	// Update the resources count field
	mRezMapWindow->SetCountRezField( mRezMapWindow->GetCountRezField() - 1 );

	// If there are no more resources of this type, remove the type item
	error = mRezMap->CountForType(theRezObj->GetType(), theCount);
	if (theCount == 0) {
		mRezMapWindow->GetRezMapTable()->RemoveItem(theSuperItem);
		// Update the types count field
		mRezMapWindow->SetCountTypeField( mRezMapWindow->GetCountTypeField() - 1 );
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
					
					if ( mRezMap->ResourceExists(theType, theID)) {
						if (!applyToOthers) {
							answer = UMessageDialogs::AskSolveUidConflicts(theType, theID, applyToOthers);
							theAction = answer;
						} else {
							answer = theAction;
						}
						switch (answer) {
							case answer_Do:
							mRezMap->UniqueID(theType, theID);
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
	
	// Find if there is already a CRezTypeItem for the specified type. If not, create one. 
	if ( ! mRezMapWindow->GetRezMapTable()->TypeExists(inType, theRezTypeItem) ) {
		// If the type does not already exist, create a new ResTypeItem
		theRezType = new CRezType(inType, mRezMap);
		theRezTypeItem = new CRezTypeItem( theRezType );
		mRezMapWindow->GetRezMapTable()->InsertRezTypeItem( theRezTypeItem );
		// Update the types count field
		mRezMapWindow->SetCountTypeField( mRezMapWindow->GetCountTypeField() + 1 );
	} else {
		theRezType = theRezTypeItem->GetRezType();
		if ( ! theRezTypeItem->IsExpanded() ) {
			theRezTypeItem->Expand();
		}
		if (replaceExisting) {
			// Remove the corresponding entry from the table if it is visible
			theRezObjItem = mRezMapWindow->GetRezMapTable()->GetRezObjItem(inType, inID);
			if (theRezObjItem) {
				RemoveResource(theRezObjItem);
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
	// Update the resources count field
	mRezMapWindow->SetCountRezField( mRezMapWindow->GetCountRezField() + 1 );
	// Redraw
	mRezMapWindow->Refresh();
}


// ---------------------------------------------------------------------------
//  UpdateRefNum												[public]
// ---------------------------------------------------------------------------
// Takes care of updating the refnum in all the sub objects which store a 
// copy of this value:
// 1- the rezmap object in CRezMapDoc
// 2- the copy of this rezmap object in CRezMapTable
// 3- all the RezObj objects created by a RezObjItem (ie by second level lines
//   in the RezMapTable)

void
CRezMapDoc::UpdateRefNum(short newRefNum)
{
	// 1-
	SetRefnum(newRefNum);
	// 2-
	mRezMapWindow->GetRezMapTable()->SetOwnerRefnum(newRefNum);
	// 3- Iterate among first level items
	LArrayIterator rezTypeIterator( mRezMapWindow->GetRezMapTable()->GetFirstLevelItems() );
	LOutlineItem *theRezTypeItem = nil;	
	LOutlineItem *theRezObjItem = nil;	
	
	while (rezTypeIterator.Next(&theRezTypeItem)) {
		// Now iterate among sub items of this RezTypeItem if it is expanded
		if (theRezTypeItem->IsExpanded()) {
			LArrayIterator rezObjIterator( *(theRezTypeItem->GetSubItems()) );
			while (rezObjIterator.Next(&theRezObjItem)) {
				dynamic_cast<CRezObjItem *>(theRezObjItem)->GetRezObj()->SetOwnerRefnum(newRefNum);				
			}
		} 
	}
}


PP_End_Namespace_PowerPlant


