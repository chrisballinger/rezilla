// ===========================================================================
// CRezCompare.cp					
// 
//                       Created: 2004-02-29 18:17:07
//             Last modification: 2005-05-12 09:44:48
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CRezCompare.h"
#include "CRezMap.h"
#include "CRezType.h"
#include "CRezObj.h"
#include "CRezillaApp.h"
#include "CRezillaPrefs.h"
#include "CCompResultWindow.h"
#include "CThreeButtonsBox.h"
#include "RezillaConstants.h"
#include "UDialogBoxHandler.h"
#include "UMessageDialogs.h"
#include "UCompareUtils.h"
#include "UMiscUtils.h"

#include <UStandardDialogs.h>
#include <LBevelButton.h>
#include <LCheckBox.h>
#include <LStaticText.h>

// Static variables
FSSpec	CRezCompare::sOldFSSpec = {0, 0, "\p"};		// Invalid specifiers
FSSpec	CRezCompare::sNewFSSpec = {0, 0, "\p"};	
Boolean	CRezCompare::sIgnoreNames = false;
Boolean	CRezCompare::sIgnoreAttrs = true;
Boolean	CRezCompare::sIgnoreData = false;


// ---------------------------------------------------------------------------
//  ¥ CRezCompare														[public]
// ---------------------------------------------------------------------------

CRezCompare::CRezCompare(LCommander* inSuper)
		: LCommander( inSuper ), LModelObject(NULL, rzom_cMapsComp)
{
	mResultWindow = nil;
	mOldMap = nil;
	mNewMap = nil;
}


// ---------------------------------------------------------------------------
//  ¥ CRezCompare														[public]
// ---------------------------------------------------------------------------

CRezCompare::CRezCompare(LCommander* inSuper, 
						 CRezMap * inOldMap, 
						 CRezMap * inNewMap)
		: LCommander( inSuper ), LModelObject(NULL, rzom_cMapsComp)
{
	mResultWindow = nil;
	mOldMap = inOldMap;
	mNewMap = inNewMap;
}


// ---------------------------------------------------------------------------
//  ¥ CRezCompare														[public]
// ---------------------------------------------------------------------------

CRezCompare::CRezCompare(LCommander* inSuper, 
						 FSSpec& inOldFileSpec, 
						 FSSpec& inNewFileSpec)
		: LCommander( inSuper ), LModelObject(NULL, rzom_cMapsComp)
{
	SInt16 oldFork, newFork;
	short oldRefnum, newRefnum;
	OSErr error;
	
	mResultWindow = nil;
	error = CRezillaApp::PreOpen(inOldFileSpec, oldFork, oldRefnum);
	if (error != noErr) {
		CRezillaApp::ReportOpenForkError(error, &inOldFileSpec);
		mOldMap = nil;
	} else {
		mOldMap = new CRezMap(oldRefnum);
	}
	error = CRezillaApp::PreOpen(inNewFileSpec, newFork, newRefnum);
	if (error != noErr) {
		CRezillaApp::ReportOpenForkError(error, &inNewFileSpec);
		mNewMap = nil;
	} else {
		mNewMap = new CRezMap(newRefnum);
	}
}


// ---------------------------------------------------------------------------
//  ¥ ~CRezCompare														[public]
// ---------------------------------------------------------------------------

CRezCompare::~CRezCompare()
{
	if (mOldMap != nil) { delete mOldMap; } 
	if (mNewMap != nil) { delete mNewMap; } 

	DeleteList(mOnlyInOldList);
	DeleteList(mOnlyInNewList);
	DeleteList(mDifferingList);
	DeleteList(mIdenticalList);
	
	if (mResultWindow != nil) {
		delete mResultWindow;
	} else {
		// Unregister from the super commander (which is CRezillaApp itself) 
		SwitchTarget( GetSuperCommander() );
		SetSuperCommander(nil);
	}	
}


// ---------------------------------------------------------------------------
//	¥ DeleteList
// ---------------------------------------------------------------------------

void
CRezCompare::DeleteList(TArray<CRezTypId *>	inList)
{
	TArrayIterator<CRezTypId*> iterator(inList, LArrayIterator::from_End);
	CRezTypId *	theTypId = NULL;
	
	while (iterator.Previous(theTypId)) {
		inList.RemoveItemsAt(1, iterator.GetCurrentIndex());
		delete theTypId;
	}
}



// ---------------------------------------------------------------------------
//	¥ AllowSubRemoval
// ---------------------------------------------------------------------------

Boolean
CRezCompare::AllowSubRemoval(
	LCommander*		inSub)
{
	if (inSub == mResultWindow) {		
		delete this;
		return false;
	} else {
		return true;
	}
}


// ---------------------------------------------------------------------------------
//  ¥ RunRezCompareDialog
// ---------------------------------------------------------------------------------

OSErr
CRezCompare::RunRezCompareDialog()
{
	Boolean			isIgnoreNames = false;
	Boolean 		inRezCompLoop = true;
	OSErr			error = noErr;
	SInt16			theFork;
	short			oldRefNum, newRefNum;
	FSSpec			theFSSpec;
	FSSpec			nilFSSpec = {0, 0, "\p"};		// Invalid specifiers	

	StDialogBoxHandler	theHandler(PPob_RezCompDialog, mSuperCommander);
	CThreeButtonsBox *	theDialog = theHandler.GetDialog();
	Assert_(theDialog != nil);
	
	LBevelButton * theSetOld = dynamic_cast<LBevelButton *>(theDialog->FindPaneByID( item_RezCompSetOld ));
	ThrowIfNil_(theSetOld);
	
	LBevelButton * theSetNew = dynamic_cast<LBevelButton *>(theDialog->FindPaneByID( item_RezCompSetNew ));
	ThrowIfNil_(theSetNew);
	
	LCheckBox *	theNamesCheckBox = dynamic_cast<LCheckBox *>(theDialog->FindPaneByID( item_RezCompIgnoreNames ));
	ThrowIfNil_(theNamesCheckBox);
	theNamesCheckBox->SetValue(sIgnoreNames);
	
	LCheckBox *	theAttrsCheckBox = dynamic_cast<LCheckBox *>(theDialog->FindPaneByID( item_RezCompIgnoreAttrs ));
	ThrowIfNil_(theAttrsCheckBox);
	theAttrsCheckBox->SetValue(sIgnoreAttrs);
	
	LCheckBox *	theDataCheckBox = dynamic_cast<LCheckBox *>(theDialog->FindPaneByID( item_RezCompIgnoreData ));
	ThrowIfNil_(theDataCheckBox);
	theDataCheckBox->SetValue(sIgnoreData);
	
	LStaticText * theOldStaticText = dynamic_cast<LStaticText *>(theDialog->FindPaneByID( item_RezCompEditOld ));
	ThrowIfNil_(theOldStaticText);
	
	LStaticText * theNewStaticText = dynamic_cast<LStaticText *>(theDialog->FindPaneByID( item_RezCompEditNew ));
	ThrowIfNil_(theNewStaticText);
	
	//  Note: linking of Listeners and Broadcasters is done in the StDialogBoxHandler constructor

	if ( ! LFile::EqualFileSpec(sOldFSSpec, nilFSSpec) && UMiscUtils::MakePath(&sOldFSSpec, mOldPath, 650) == noErr ) {
		theOldStaticText->SetDescriptor(mOldPath);
	} 
	if ( ! LFile::EqualFileSpec(sNewFSSpec, nilFSSpec) && UMiscUtils::MakePath(&sNewFSSpec, mNewPath, 650) == noErr ) {
		theNewStaticText->SetDescriptor(mNewPath);
	} 
	
	while (inRezCompLoop) {
		
		theDialog->Show();
		
		MessageT theMessage;
		while (true) {
			
			theMessage = theHandler.DoDialog();
			
			if (msg_OK == theMessage) {
				Str255		theOldPath, theNewPath;
				theOldStaticText->GetDescriptor(theOldPath);
				theNewStaticText->GetDescriptor(theNewPath);
				// Check that both fields are not empty
				if ( !theOldPath[0] || !theNewPath[0] ) {
					UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("MapsNotSelected"), PPob_SimpleMessage);
				} else {
					break;
				}
			} else if (msg_Cancel == theMessage) {
				inRezCompLoop = false;
				break;
			} else if (msg_RezCompSetOld == theMessage || msg_RezCompSetNew == theMessage) {
				// Select the files to compare
				LFileTypeList fileTypes(fileTypes_All);
				PP_StandardDialogs::LFileChooser chooser;
				NavDialogOptions * options = chooser.GetDialogOptions();
				
				if (options != nil) {
					options->dialogOptionFlags = kNavNoTypePopup 
					+ kNavDontAutoTranslate 
					+ kNavSelectAllReadableItem 
					+ kNavSupportPackages 
					+ kNavAllowOpenPackages;
				}
				
				if ( chooser.AskChooseOneFile(fileTypes, theFSSpec) ) {
					switch (theMessage) {
						case msg_RezCompSetOld:
						if ( UMiscUtils::MakePath(&theFSSpec, mOldPath, 650) == noErr ) {
							theOldStaticText->SetDescriptor(mOldPath);
						} 
						UMiscUtils::CopyFSSpec(theFSSpec, sOldFSSpec);
						break;
						
						case msg_RezCompSetNew:
						if ( UMiscUtils::MakePath(&theFSSpec, mNewPath, 650) == noErr ) {
							theNewStaticText->SetDescriptor(mNewPath);
						} 
						UMiscUtils::CopyFSSpec(theFSSpec, sNewFSSpec);
						break;
					}
				}
				break;  // Breaks out from the inner 'while' but still in the inRezCompLoop 'while'
			}
		}
		
		// If the default button was hit, try to open the rezmaps
		if (msg_OK == theMessage) {
			if (mOldMap == nil) {
				error = CRezillaApp::PreOpen(sOldFSSpec, theFork, oldRefNum);
				if (error != noErr) {
					CRezillaApp::ReportOpenForkError(error, &sOldFSSpec);
				} else {
					mOldMap = new CRezMap(oldRefNum);
				}
			} 
			if (mNewMap == nil) {
				error = CRezillaApp::PreOpen(sNewFSSpec, theFork, newRefNum);
				if (error != noErr) {
					CRezillaApp::ReportOpenForkError(error, &sNewFSSpec);
				} else {
					mNewMap = new CRezMap(newRefNum);
				}
			} 
			if (mOldMap != nil && mNewMap != nil) {
				// Retrieve the checkbox settings
				sIgnoreAttrs = theAttrsCheckBox->GetValue();
				sIgnoreNames = theNamesCheckBox->GetValue();
				sIgnoreData = theDataCheckBox->GetValue();
				// Keep a copy of the criteria (for AE properties)
				mIgnoreNames = sIgnoreNames;
				mIgnoreAttrs = sIgnoreAttrs;
				mIgnoreData = sIgnoreData;
				// Execute a comparison
				DoCompareRezMaps();
				// Now get out of the outer 'while'
				inRezCompLoop = false;
			}
		} else {
			error = userCanceledErr;
		}
	}
	return error;
}


// ---------------------------------------------------------------------------------
//  ¥ DoCompareRezMaps
// ---------------------------------------------------------------------------------

void
CRezCompare::DoCompareRezMaps()
{
    ThrowIfNil_(mOldMap);
    ThrowIfNil_(mNewMap);
    
	ResType		theOldType, theNewType;
	CTypeComparator* theOldComparator = new CTypeComparator;
	CTypeComparator* theNewComparator = new CTypeComparator;
	TArray<ResType>* theOldTypesArray = new TArray<ResType>( theOldComparator, true);
	TArray<ResType>* theNewTypesArray = new TArray<ResType>( theNewComparator, true);
	TArrayIterator<ResType>	typeOldIterator(*theOldTypesArray);
	TArrayIterator<ResType>	typeNewIterator(*theNewTypesArray);

	// Populate the arrays
	mOldMap->GetAllTypes(theOldTypesArray);
	mNewMap->GetAllTypes(theNewTypesArray);
	
	while (typeOldIterator.Next(theOldType)) {
		if (not theNewTypesArray->ContainsItem(theOldType) ) {
			// The old type is not in the new map, just add all its resources to mOnlyInOldList
			AddTypeToArray(theOldType, list_OnlyInOld);
		} else {
			// It is in both maps, compare the lists of resources for this type, then remove the 
			// type from the new map's list
			CompareTypes(theOldType);
			theNewTypesArray->Remove(theOldType);
		}
	}
	// All types remaining in the new map's list belong to mOnlyInNewList
	while (typeNewIterator.Next(theNewType)) {
		AddTypeToArray(theNewType, list_OnlyInNew);
	}
	
	// Each array takes care of deleting its comparator
	if (theNewTypesArray != nil) { delete theNewTypesArray; } 
	if (theOldTypesArray != nil) { delete theOldTypesArray; } 
}


// ---------------------------------------------------------------------------------
//  ¥ CompareTypes
// ---------------------------------------------------------------------------------

void
CRezCompare::CompareTypes(ResType inType)
{
	short		theID;
	SInt16		result;
	TArray<short>* theOldRezIDArray = new TArray<short>();
	TArray<short>* theNewRezIDArray = new TArray<short>();
	TArrayIterator<short>	oldIterator(*theOldRezIDArray);
	TArrayIterator<short>	newIterator(*theNewRezIDArray);

	CRezType theOldRezType(inType, mOldMap);
	theOldRezType.GetAllRezIDs(theOldRezIDArray);
	CRezType theNewRezType(inType, mNewMap);
	theNewRezType.GetAllRezIDs(theNewRezIDArray);
	
	while (oldIterator.Next(theID)) {
		if (not theNewRezIDArray->ContainsItem(theID) ) {
			// The old ID is not in the new map, just add it to mOnlyInOldList
			AddResourceToArray(inType, theID, list_OnlyInOld);
		} else {
			// It is in both maps, compare the corresponding resources, then remove the ID 
			// from the new map's list
			CompareTwoResources(&theOldRezType, &theNewRezType, theID, &result);
			if (result) {
				AddResourceToArray(inType, theID, list_Differing);
			} 
			theNewRezIDArray->Remove(theID);
		}
	}
	// All IDs remaining in the new map's list belong to mOnlyInNewList
	while (newIterator.Next(theID)) {
		AddResourceToArray(inType, theID, list_OnlyInNew);
	}

	if (theOldRezIDArray != nil) { delete theOldRezIDArray; } 
	if (theNewRezIDArray != nil) { delete theNewRezIDArray; } 
}


// ---------------------------------------------------------------------------------
//  ¥ CompareTwoResources
// ---------------------------------------------------------------------------------

void
CRezCompare::CompareTwoResources(CRezType * inOldRezType, CRezType * inNewRezType, 
								 short inID, SInt16 * outCompResult)
{
	CRezObj theOldRezObj(inOldRezType, inID);
	CRezObj theNewRezObj(inNewRezType, inID);

	// Compare the sizes of the handles
	if (!sIgnoreData && (theOldRezObj.GetSize() != theNewRezObj.GetSize())) {
		*outCompResult = compare_sizeDiff;
		return;
	}
	// Compare the names
	if (!sIgnoreNames && UCompareUtils::CompareStr255(theOldRezObj.GetName(), theNewRezObj.GetName()) != 0) {
		*outCompResult = compare_nameDiff;
		return;
	}
	// Compare the flags
	if (!sIgnoreAttrs && (theOldRezObj.GetAttributes() != theNewRezObj.GetAttributes())) {
		*outCompResult = compare_flagDiff;
		return;
	}
	// Compare the data
	if (!sIgnoreData && BlockCompare(*(theOldRezObj.GetData()), *(theNewRezObj.GetData()), theOldRezObj.GetSize()) != 0) {
		*outCompResult = compare_dataDiff;
	} else {
		*outCompResult = compare_noDiff;
	}
}


// ---------------------------------------------------------------------------------
//  ¥ AddTypeToArray
// ---------------------------------------------------------------------------------

void
CRezCompare::AddTypeToArray(ResType inType, SInt16 inWhichList)
{
	TArray<short>* theRezIDArray = new TArray<short>();
	TArrayIterator<short>	iterator(*theRezIDArray);
	CRezType * theRezType;
	short theID;
	
		switch (inWhichList) {
			case list_OnlyInOld:
			theRezType = new CRezType(inType, mOldMap);
			theRezType->GetAllRezIDs(theRezIDArray);
			while (iterator.Next(theID)) {
				mOnlyInOldList.AddItem( new CRezTypId(inType, theID) );
			}
			break;
			
			case list_OnlyInNew:
			theRezType = new CRezType(inType, mNewMap);
			theRezType->GetAllRezIDs(theRezIDArray);
			while (iterator.Next(theID)) {
				mOnlyInNewList.AddItem( new CRezTypId(inType, theID) );
			}
			break;
		}
}


// ---------------------------------------------------------------------------------
//  ¥ AddResourceToArray
// ---------------------------------------------------------------------------------

void
CRezCompare::AddResourceToArray(ResType inType, short inID, SInt16 inWhichList)
{
	switch (inWhichList) {
	  case list_OnlyInOld:
		mOnlyInOldList.AddItem( new CRezTypId(inType, inID) );
		break;
		
	  case list_OnlyInNew:
		mOnlyInNewList.AddItem( new CRezTypId(inType, inID) );
		break;
		
	  case list_Differing:
		mDifferingList.AddItem( new CRezTypId(inType, inID) );
		break;
	}
}


// ---------------------------------------------------------------------------------
//  ¥ HasDifferences
// ---------------------------------------------------------------------------------

Boolean
CRezCompare::HasDifferences()
{
    return ( (mOnlyInOldList.GetCount() 
			+ mOnlyInNewList.GetCount()
			+ mDifferingList.GetCount()) > 0);
}


// ---------------------------------------------------------------------------------
//  ¥ DisplayResults
// ---------------------------------------------------------------------------------

void
CRezCompare::DisplayResults()
{	
	// Create window for the results
	mResultWindow = dynamic_cast<CCompResultWindow *>(LWindow::CreateWindow( PPob_RezCompWindow, this ));
	Assert_( mResultWindow != nil );

	// Populate the tables
	mResultWindow->FillTableView(mOnlyInOldList, list_OnlyInOld);
	mResultWindow->FillTableView(mOnlyInNewList, list_OnlyInNew);
	mResultWindow->FillTableView(mDifferingList, list_Differing);		
}


