// ===========================================================================
// CRezCompare.cp					
// 
//                       Created: 2004-02-29 18:17:07
//             Last modification: 2004-03-02 14:11:01
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CRezCompare.h"
#include "CRezMap.h"
#include "CRezType.h"
#include "CRezObj.h"
#include "CRezillaApp.h"
#include "CCompResultWindow.h"
#include "RezillaConstants.h"
#include "UDialogBoxHandler.h"
#include "UMessageDialogs.h"
#include "UMiscUtils.h"

#include <UStandardDialogs.h>
#include <LBevelButton.h>
#include <LCheckBox.h>
#include <LStaticText.h>

// ---------------------------------------------------------------------------
//  ¥ CRezCompare														[public]
// ---------------------------------------------------------------------------

CRezCompare::CRezCompare(LCommander* inSuper)
		: LCommander( inSuper )
{
	mResultWindow = nil;
    mIgnoreNames = false;
    mIgnoreAttrs = true;
	mIgnoreData = false;
	mOldMap = nil;
	mNewMap = nil;
}


// ---------------------------------------------------------------------------
//  ¥ CRezCompare														[public]
// ---------------------------------------------------------------------------

CRezCompare::CRezCompare(LCommander* inSuper, 
						 CRezMap * inOldMap, 
						 CRezMap * inNewMap)
		: LCommander( inSuper )
{
	mResultWindow = nil;
    mIgnoreNames = false;
    mIgnoreAttrs = true;
	mIgnoreData = false;
	mOldMap = inOldMap;
	mNewMap = inNewMap;
}


// ---------------------------------------------------------------------------
//  ¥ CRezCompare														[public]
// ---------------------------------------------------------------------------

CRezCompare::CRezCompare(LCommander* inSuper, 
						 FSSpec& inOldFileSpec, 
						 FSSpec& inNewFileSpec)
		: LCommander( inSuper )
{
	SInt16 oldFork, newFork;
	short oldRefnum, newRefnum;
	OSErr error;
	
	mResultWindow = nil;
	mIgnoreNames = false;
	mIgnoreAttrs = true;
	mIgnoreData = false;
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
}


// ---------------------------------------------------------------------------------
//  ¥ RunRezCompareDialog
// ---------------------------------------------------------------------------------

void
CRezCompare::RunRezCompareDialog()
{
	SInt32 			itemIndex;
	Boolean			isIgnoreNames = false;
	Boolean 		inRezCompLoop = true;
	
	StDialogBoxHandler	theHandler(rPPob_RezCompDialog, mSuperCommander);
	LDialogBox *		theDialog = theHandler.GetDialog();
	Assert_(theDialog != nil);
	
	LBevelButton * theSetOld = dynamic_cast<LBevelButton *>(theDialog->FindPaneByID( item_RezCompSetOld ));
	ThrowIfNil_(theSetOld);
	
	LBevelButton * theSetNew = dynamic_cast<LBevelButton *>(theDialog->FindPaneByID( item_RezCompSetNew ));
	ThrowIfNil_(theSetNew);
	
	LCheckBox *	theNamesCheckBox = dynamic_cast<LCheckBox *>(theDialog->FindPaneByID( item_RezCompIgnoreNames ));
	ThrowIfNil_(theNamesCheckBox);
	theNamesCheckBox->SetValue(mIgnoreNames);
	
	LCheckBox *	theAttrsCheckBox = dynamic_cast<LCheckBox *>(theDialog->FindPaneByID( item_RezCompIgnoreAttrs ));
	ThrowIfNil_(theAttrsCheckBox);
	theAttrsCheckBox->SetValue(mIgnoreAttrs);
	
	LCheckBox *	theDataCheckBox = dynamic_cast<LCheckBox *>(theDialog->FindPaneByID( item_RezCompIgnoreData ));
	ThrowIfNil_(theDataCheckBox);
	theDataCheckBox->SetValue(mIgnoreData);
	
	LStaticText * theOldStaticText = dynamic_cast<LStaticText *>(theDialog->FindPaneByID( item_RezCompEditOld ));
	ThrowIfNil_(theOldStaticText);

	LStaticText * theNewStaticText = dynamic_cast<LStaticText *>(theDialog->FindPaneByID( item_RezCompEditNew ));
	ThrowIfNil_(theNewStaticText);
	
	//  Note: linking of Listeners and Broadcasters is done in the StDialogBoxHandler constructor
	
	while (inRezCompLoop) {
		
		theDialog->Show();
		
		MessageT theMessage;
		while (true) {
			theMessage = theHandler.DoDialog();
			if (msg_OK == theMessage) {
				// Check that both fileds are not empty
				if (mOldMap == nil || mNewMap == nil) {
					UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("MapsNotSelected"), rPPob_SimpleMessage);
				} else {
					inRezCompLoop = false;
				}
				break;
			} else if (msg_Cancel == theMessage) {
				inRezCompLoop = false;
				break;
			} else if (msg_RezCompSetOld == theMessage || msg_RezCompSetNew == theMessage) {
				// Select the files to compare
				OSErr	error;
				SInt16	theFork;
				short	theRefnum;
				FSSpec	theFSSpec;
				Str255	thePath;
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
					error = CRezillaApp::PreOpen(theFSSpec, theFork, theRefnum);
					
					if (error != noErr) {
						CRezillaApp::ReportOpenForkError(error, &theFSSpec);
					} else {
						switch (theMessage) {
						  case msg_RezCompSetOld:
							if ( UMiscUtils::MakePath(&theFSSpec, thePath, 650) == noErr ) {
								theOldStaticText->SetDescriptor(thePath);
							} 
							LString::CopyPStr(thePath, mOldPath);
							mOldMap = new CRezMap(theRefnum);
							break;
						
						  case msg_RezCompSetNew:
							if ( UMiscUtils::MakePath(&theFSSpec, thePath, 450) == noErr ) {
								theNewStaticText->SetDescriptor(thePath);
							} 
							LString::CopyPStr(thePath, mNewPath);
							mNewMap = new CRezMap(theRefnum);
							break;
						}
					}
				}
				break;  // Breaks out from the inner 'while' but still in the inRezCompLoop 'while'
			}
		}
		
		// If the default button was hit, do the comparison
		if (msg_OK == theMessage) {
			// Retrieve the checkbox settings
			mIgnoreAttrs = theAttrsCheckBox->GetValue();
			mIgnoreNames = theNamesCheckBox->GetValue();
			mIgnoreData = theDataCheckBox->GetValue();
			// Execute a comparison
			DoCompareRezMaps();
		}
	}
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
	CTypeComparator* theComparator = new CTypeComparator;
	TArray<ResType>* theNewTypesArray = new TArray<ResType>( theComparator, true);
	TArray<ResType>* theOldTypesArray = new TArray<ResType>( theComparator, true);
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
}


// ---------------------------------------------------------------------------------
//  ¥ CompareTypes
// ---------------------------------------------------------------------------------

void
CRezCompare::CompareTypes(ResType inType)
{
	TArray<short>* theOldRezIDArray = new TArray<short>();
	TArray<short>* theNewRezIDArray = new TArray<short>();
	TArrayIterator<short>	oldIterator(*theOldRezIDArray);
	TArrayIterator<short>	newIterator(*theNewRezIDArray);
	CRezType	*theOldRezType, *theNewRezType;
	short		theID;
	SInt16		result;

	theOldRezType = new CRezType(inType, mOldMap);
	theOldRezType->GetAllRezIDs(theOldRezIDArray);
	theNewRezType = new CRezType(inType, mNewMap);
	theNewRezType->GetAllRezIDs(theNewRezIDArray);
	
	while (oldIterator.Next(theID)) {
		if (not theNewRezIDArray->ContainsItem(theID) ) {
			// The old ID is not in the new map, just add it to mOnlyInOldList
			AddResourceToArray(inType, theID, list_OnlyInOld);
		} else {
			// It is in both maps, compare the corresponding resources, then remove the ID 
			// from the new map's list
			CompareTwoResources(theOldRezType, theNewRezType, theID, &result);
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
}


// ---------------------------------------------------------------------------------
//  ¥ CompareTwoResources
// ---------------------------------------------------------------------------------

void
CRezCompare::CompareTwoResources(CRezType * inOldRezType, CRezType * inNewRezType, 
								 short inID, SInt16 * outCompResult)
{
	CRezObj		*theOldRezObj, *theNewRezObj;
	Handle		oldRezHandle, newRezHandle;
	
	theOldRezObj = new CRezObj(inOldRezType, inID);
	theNewRezObj = new CRezObj(inNewRezType, inID);

	if (!mIgnoreData && (theOldRezObj->GetSize() != theNewRezObj->GetSize())) {
		// Compare the sizes of the handles
		*outCompResult = compare_sizeDiff;
	} else if (!mIgnoreNames && ! UMiscUtils::CompareStr255(theOldRezObj->GetName(), theNewRezObj->GetName())) {
		// Compare the names
		*outCompResult = compare_nameDiff;
	} else if (!mIgnoreAttrs && (theOldRezObj->GetAttributes() != theNewRezObj->GetAttributes())) {
		// Compare the flags
		*outCompResult = compare_flagDiff;
	}  else if (BlockCompare(*(theOldRezObj->GetData()), *(theNewRezObj->GetData()), theOldRezObj->GetSize()) != 0) {
		// Compare the data
		*outCompResult = compare_dataDiff;
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
	mResultWindow = dynamic_cast<CCompResultWindow *>(LWindow::CreateWindow( rPPob_RezCompWindow, this ));
	Assert_( mResultWindow != nil );

	// Populate the tables
	mResultWindow->FillTableView(mOnlyInOldList, list_OnlyInOld);
	mResultWindow->FillTableView(mOnlyInNewList, list_OnlyInNew);
	mResultWindow->FillTableView(mDifferingList, list_Differing);		
}



