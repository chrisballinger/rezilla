// ===========================================================================
// CRezCompare.cp					
// 
//                       Created: 2004-02-29 18:17:07
//             Last modification: 2004-02-29 18:17:12
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
#include "CRezillaApp.h"
#include "UDialogBoxHandler.h"
#include "RezillaConstants.h"

#include <UStandardDialogs.h>
#include <LBevelButton.h>
#include <LCheckBox.h>
#include <LStaticText.h>

// ---------------------------------------------------------------------------
//  ¥ CRezCompare														[public]
// ---------------------------------------------------------------------------

CRezCompare::CRezCompare(LCommander* inSuper)
{
	mSuperCommander = inSuper;
    mIgnoreNames = false;
    mIgnoreAttrs = true;
	mOldMap = nil;
	mNewMap = nil;
}


// ---------------------------------------------------------------------------
//  ¥ CRezCompare														[public]
// ---------------------------------------------------------------------------

CRezCompare::CRezCompare(LCommander* inSuper, 
						 CRezMap * inOldMap, 
						 CRezMap * inNewMap)
{
	mSuperCommander = inSuper;
    mIgnoreNames = false;
    mIgnoreAttrs = true;
	mOldMap = inOldMap;
	mNewMap = inNewMap;
}


// ---------------------------------------------------------------------------
//  ¥ CRezCompare														[public]
// ---------------------------------------------------------------------------

CRezCompare::CRezCompare(LCommander* inSuper, 
						 FSSpec& inOldFileSpec, 
						 FSSpec& inNewFileSpec)
{
	SInt16 oldFork, newFork;
	short oldRefnum, newRefnum;
	OSErr error;
	
	mSuperCommander = inSuper;
    mIgnoreNames = false;
    mIgnoreAttrs = true;
	error = CRezillaApp::PreOpen(inOldFileSpec, oldFork, oldRefnum);
	ThrowIfError_(error);
	mOldMap = new CRezMap(oldRefnum);
	error = CRezillaApp::PreOpen(inNewFileSpec, newFork, newRefnum);
	ThrowIfError_(error);
	mNewMap = new CRezMap(newRefnum);
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
			if (msg_OK == theMessage || msg_Cancel == theMessage) {
				inRezCompLoop = false;
				break;
			} else if (msg_RezCompSetOld == theMessage || msg_RezCompSetNew == theMessage) {
				break;  // Breaks out from the inner 'while' but still in the inRezCompLoop 'while'
			} else {
// 				switch (theMessage) {
// 					
// 					case msg_FindInHexRadio:
// 					case msg_FindInTxtRadio:
// 					if (whichPaneRadioID == item_FindInHexRadio) {
// 						theCheckBox->Disable();
// 						isIgnoreNames = false;
// 					} else {
// 						theCheckBox->Enable();
// 						isIgnoreNames = theCheckBox->GetValue();
// 					}
// 					break;
// 					
// 					case msg_FindIgnoreCase:
// 					isIgnoreNames = theCheckBox->GetValue();
// 					break;
// 				}	
			}
		}
		
		// If Search button was hit, retrieve the search string
		if (msg_OK == theMessage) {
// 			theStaticText->GetDescriptor(mSearchString);
// 			mIgnoreCase = theCheckBox->GetValue();
// 			mSearchWhichPane = theRGV->GetCurrentRadioID();
// 			if (mSearchString[0] == 0) {
// 				return;
// 			} 
// 			FindInPane(mSearchWhichPane, mIgnoreCase, false);
		}
	}
}





