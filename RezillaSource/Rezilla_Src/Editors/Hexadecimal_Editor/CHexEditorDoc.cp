// ===========================================================================
// CHexEditorDoc.cp					
// 
//                       Created: 2003-05-04 19:16:00
//             Last modification: 2005-09-05 06:51:25
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

#include "CHexEditorDoc.h"
#include "CHexEditorWindow.h"
#include "RezillaConstants.h"
#include "CRezFile.h"
#include "CRezMap.h"
#include "CRezMapDoc.h"
#include "CRezObj.h"
#include "CRezMapTable.h"
#include "CRezMapWindow.h"
#include "CDualDataView.h"
#include "CHexDataSubView.h"
#include "CTxtDataSubView.h"
#include "CThreeButtonsBox.h"
#include "CRezillaApp.h"
#include "UCodeTranslator.h"
#include "UDialogBoxHandler.h"
#include "UMessageDialogs.h"
#include "UMiscUtils.h"

#include <LWindow.h>
#include <LFile.h>
#include <UStandardDialogs.h>
#include <LRadioGroupView.h>
#include <LCheckBox.h>
#include <LEditField.h>

#include <LString.h>
#include <PP_Messages.h>

#include <AEInteraction.h>
#include <AERegistry.h>
#include <AEObjects.h>
#include <AEPackObject.h>

// Standard headers
#include <string.h>



// ---------------------------------------------------------------------------
//	¥ CHexEditorDoc							Constructor		  [public]
// ---------------------------------------------------------------------------
// 	: CEditorController( inSuperMap )

CHexEditorDoc::CHexEditorDoc(LCommander* inSuper, 
								 CRezMapTable* inSuperMap,
								 CRezObj* inRezObj,
								 ResType inSubstType,
								 Boolean inReadOnly)
 	: CEditorDoc(inSuper, inSuperMap, inRezObj, inSubstType, inReadOnly)
{
	Initialize();
}


// ---------------------------------------------------------------------------
//	¥ ~CHexEditorDoc							Destructor				  [public]
// ---------------------------------------------------------------------------

CHexEditorDoc::~CHexEditorDoc()
{
	if (mHexEditWindow != nil) {
		delete mHexEditWindow;
	} 
}


// ---------------------------------------------------------------------------
//	¥ Initialize													  [public]
// ---------------------------------------------------------------------------

void
CHexEditorDoc::Initialize()
{
	mSearchString[0] = 0;
	mMatchStart = 0;
	mMatchEnd = 0;
	mSearchWhichPane = item_FindInHexRadio;
	mIgnoreCase = true;
	mKind = editor_kindHex;

	SetModelKind(rzom_cHexEditDoc);

	// Create window for our document.
	mHexEditWindow = dynamic_cast<CHexEditorWindow *>(LWindow::CreateWindow( PPob_HexEditorWindow, this ));
	Assert_( mHexEditWindow != nil );
	
	SetMainWindow( dynamic_cast<CEditorWindow *>(mHexEditWindow) );
	NameNewEditorDoc();
	mHexEditWindow->FinalizeEditor(this);

	// Install the hex and text panes contents
	if (mRezObj != nil) {
		Handle rezData = mRezObj->GetData();
		
		if (rezData != nil) {
			mHexEditWindow->InstallResourceData(rezData);
		} 
	} 
		
	// Make the window visible.
	mHexEditWindow->Show();
}


// ---------------------------------------------------------------------------
//	¥ ObeyCommand									[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CHexEditorDoc::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;	// Assume we'll handle the command
	
	switch (inCommand) {
		
		case cmd_Close : 
		AttemptClose(false);
		break;
				
		case cmd_Find:
		RunFindDialog();
		break;
				
		case cmd_FindNext:
		FindInPane(mSearchWhichPane, mIgnoreCase, true);
		break;
				
		default: {
			cmdHandled = LDocument::ObeyCommand(inCommand, ioParam);
			break;
		}
	}
	
	return cmdHandled;
}


// ---------------------------------------------------------------------------------
//  ¥ RunFindDialog
// ---------------------------------------------------------------------------------

void
CHexEditorDoc::RunFindDialog()
{
	Boolean			isIgnoreCase = false;
	PaneIDT			whichPaneRadioID = item_FindInHexRadio;
	Boolean 		inPrefsLoop = true;
	
	StDialogBoxHandler	theHandler(PPob_FindDialog, this);
	CThreeButtonsBox *	theDialog = theHandler.GetDialog();
	Assert_(theDialog != nil);
	
	LRadioGroupView * theRGV = dynamic_cast<LRadioGroupView *>(theDialog->FindPaneByID( item_FindInPaneRGV ));
	ThrowIfNil_(theRGV);
	theRGV->SetCurrentRadioID(mSearchWhichPane);
	
	LCheckBox *	theCheckBox = dynamic_cast<LCheckBox *>(theDialog->FindPaneByID( item_FindIgnoreCase ));
	ThrowIfNil_(theCheckBox);
	theCheckBox->SetValue(mIgnoreCase);
	
	LEditField * theEditField = dynamic_cast<LEditField *>(theDialog->FindPaneByID( item_FindSearchField ));
	ThrowIfNil_(theEditField);

	theEditField->SetDescriptor(mSearchString);
	SwitchTarget(theEditField);

	if (mSearchWhichPane == item_FindInTxtRadio) {
		theCheckBox->Enable();
	}
	
	//  Note: linking of Listeners and Broadcasters is done in the StDialogBoxHandler constructor
	
	while (inPrefsLoop) {
		
		theDialog->Show();
		
		MessageT theMessage;
		while (true) {
			theMessage = theHandler.DoDialog();
			if (msg_OK == theMessage || msg_Cancel == theMessage) {
				inPrefsLoop = false;
				break;
			} else {
				switch (theMessage) {
					
					case msg_FindInHexRadio:
					case msg_FindInTxtRadio:
					whichPaneRadioID = theRGV->GetCurrentRadioID();
					if (whichPaneRadioID == item_FindInHexRadio) {
						theCheckBox->Disable();
						isIgnoreCase = false;
					} else {
						theCheckBox->Enable();
						isIgnoreCase = theCheckBox->GetValue();
					}
					break;
					
					case msg_FindIgnoreCase:
					isIgnoreCase = theCheckBox->GetValue();
					break;
				}	
			}
		}
		
		// If Search button was hit, retrieve the search string
		if (msg_OK == theMessage) {
			theEditField->GetDescriptor(mSearchString);
			mIgnoreCase = theCheckBox->GetValue();
			mSearchWhichPane = theRGV->GetCurrentRadioID();
			if (mSearchString[0] == 0) {
				return;
			} 
			FindInPane(mSearchWhichPane, mIgnoreCase, false);
		}
	}
}


// ---------------------------------------------------------------------------------
//  ¥ FindInPane
// ---------------------------------------------------------------------------------

OSErr
CHexEditorDoc::FindInPane(PaneIDT inWhichPane, 
						  Boolean isIgnoreCase,
						  Boolean findingNext)
{
	OSErr		error = noErr;
	Str255		theSearchString;
	SInt32		theStartPos, theEndPos;
	char * 		keyString = new char[256];
	Size 		searchStrLen = mSearchString[0];
	
	WEReference	we = mHexEditWindow->GetDualView()->GetInMemoryWE();
	::CopyPascalStringToC(mSearchString, keyString);

	// Start searching: from the start of the current selection if the user chose Find
	// and from the next position if the user chose FindNext
	mHexEditWindow->GetDualView()->GetAbsoluteRange(theStartPos, theEndPos);
	
	if (inWhichPane == item_FindInHexRadio) {
		// Check that we have valid hexadecimal data
		if ( ! UMiscUtils::IsValidHexadecimal(keyString, searchStrLen)) {
			UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("InvalidHexDataInString"), PPob_SimpleMessage);
			return error;
		} else if ( searchStrLen % 2 ) {
			UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("HexStringMustBeEven"), PPob_SimpleMessage);
			return error;
		} else {
			Handle	theHandle = ::WEGetText(we);
			Size	theSize = ::GetHandleSize(theHandle);
			int		i = findingNext ? theStartPos + 1 : theStartPos;
			int		result = 1;
			
			// Convert hexdata to byte codes
			UCodeTranslator::ConvertHexToByte(keyString, keyString);
			StHandleLocker locker(theHandle);
			searchStrLen /= 2;
			
			// Naive algorithm. Use memcmp() for bytecode comparison in
			// order not to be annoyed with null bytes.
			while ( result &&  i <=  theSize - searchStrLen ) {
				result = ::memcmp( *theHandle + i, keyString, searchStrLen);
				i++;
			}
			
			if ( !result ) {
				mMatchStart = i - 1;
				mMatchEnd = mMatchStart + searchStrLen;
			} else {
				error = weTextNotFoundErr;
			}
		}
	} else {
		LString::CopyPStr(mSearchString, theSearchString);
		error = ::WEFind(keyString, theSearchString[0], kTextEncodingMacRoman, 
			   isIgnoreCase ? weFindCaseInsensitive : 0 , findingNext ? theStartPos + 1 : theStartPos, 
			   ::WEGetTextLength(we), &mMatchStart, &mMatchEnd, we) ;
	}
	
	if ( error ) {
		// weTextNotFoundErr = -9474 (search string not found)
		::SysBeep(3);
	} else {
		mHexEditWindow->DisplayBothSelections(mMatchStart, mMatchEnd);
	}
	return error;
}


// ---------------------------------------------------------------------------------
//  ¥ IsModified
// ---------------------------------------------------------------------------------

Boolean
CHexEditorDoc::IsModified()
{
	// Document has changed if the text views are dirty
	mIsModified = mHexEditWindow->IsDirty();
	return mIsModified;
}


// ---------------------------------------------------------------------------
//	¥ GetDescriptor													  [public]
// ---------------------------------------------------------------------------
//	Pass back the name of a Document

StringPtr
CHexEditorDoc::GetDescriptor(
	Str255	outDescriptor) const
{
	if (mHexEditWindow != nil) {
		// Use name of its window
		mHexEditWindow->GetDescriptor(outDescriptor);
	} else {
		// No window, document name is empty string
		outDescriptor[0] = 0;		
	}

	return outDescriptor;
}


// ---------------------------------------------------------------------------------
//  ¥ FindCommandStatus
// ---------------------------------------------------------------------------------

void
CHexEditorDoc::FindCommandStatus(
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
			outEnabled = false;
		break;
								
		case cmd_Find:
			LString::CopyPStr( "\pFindÉ", outName);
			outEnabled = true;
			break;
								
		case cmd_FindNext:
			outEnabled = (mSearchString[0] > 0);
			break;
								
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
CHexEditorDoc::AllowSubRemoval(
	LCommander*		inSub)
{
	if (inSub == mHexEditWindow) {
		AttemptClose(false);
		return false;
	} else {
		return true;
	}
}


// ---------------------------------------------------------------------------
//	¥ AskSaveChanges												  [public]
// ---------------------------------------------------------------------------
//	Ask user whether to save changes before closing the Document or
//	quitting the Application

SInt16
CHexEditorDoc::AskSaveChanges(
	bool /* inQuitting */)
{
	return UMessageDialogs::AskYesNoFromLocalizable(CFSTR("SaveHexWindow"), PPob_AskYesNoMessage);
}



// ---------------------------------------------------------------------------
//  ¥ GetModifiedResource										[public]
// ---------------------------------------------------------------------------
// The returned handle should not be released by the caller so leave
// releaseIt to false (its default).

Handle
CHexEditorDoc::GetModifiedResource(Boolean &releaseIt) 
{
#pragma unused(releaseIt)
	
	return WEGetText(mHexEditWindow->GetDualView()->GetInMemoryWE());
}



PP_End_Namespace_PowerPlant


