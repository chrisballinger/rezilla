// ===========================================================================
// CRezTypeChooser.h
// 
//                       Created: 2004-08-12 15:59:49
//             Last modification: 2005-03-09 06:55:56
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2004, 2005
// All rights reserved.
// ===========================================================================


#include "CRezTypeChooser.h"
#include "CEditorDoc.h"
#include "CTemplatesController.h"
#include "CThreeButtonsBox.h"
#include "RezillaConstants.h"
#include "UDialogBoxHandler.h"
#include "UMessageDialogs.h"
#include "UMiscUtils.h"

#include <LEditText.h>
#include <LPopupButton.h>

ResType CRezTypeChooser::sChosenType = 0;


// ---------------------------------------------------------------------------
//   CRezTypeChooser				[public]
// ---------------------------------------------------------------------------

CRezTypeChooser::CRezTypeChooser()
{
}


// ---------------------------------------------------------------------------
//   ~CRezTypeChooser				[public]
// ---------------------------------------------------------------------------

CRezTypeChooser::~CRezTypeChooser()
{
}


// ---------------------------------------------------------------------------
//   FinishCreateSelf				[protected]
// ---------------------------------------------------------------------------

void
CRezTypeChooser::FinishCreateSelf()
{
}


// ---------------------------------------------------------------------------------
//   RunDialog
// ---------------------------------------------------------------------------------

OSErr
CRezTypeChooser::RunDialog()
{
	Boolean 		inPickerLoop = true;
	Str255			theString, theTypeStr;
	SInt32 			itemIndex;
	OSErr			error = noErr;
	CFStringRef		theTypeRef;

	StDialogBoxHandler	theHandler(PPob_RezTypeChooser, this);
	CThreeButtonsBox *	theDialog = theHandler.GetDialog();
	Assert_(theDialog != nil);
	
	LEditText * theEditField = dynamic_cast<LEditText *>(theDialog->FindPaneByID( item_TypeChooserField ));
	ThrowIfNil_(theEditField);
	
	LPopupButton * theTypesMenu = dynamic_cast<LPopupButton *>(theDialog->FindPaneByID( item_TypeChooserMenu ));
	ThrowIfNil_(theTypesMenu);
	
	// Install the static value
	UMiscUtils::OSTypeToPString(sChosenType, theTypeStr);
	theEditField->SetDescriptor(theTypeStr);
	
	// Populate the popup button
	CFIndex theCount = ::CFArrayGetCount(CTemplatesController::sAllTypesArray);
	for ( CFIndex i = 0; i < theCount; i++ ) {
		theTypeRef = (CFStringRef) ::CFArrayGetValueAtIndex(CTemplatesController::sAllTypesArray, i);
		if ( ::CFStringGetPascalString(theTypeRef, theString, sizeof(theString), NULL) ) {
			theTypesMenu->InsertMenuItem(theString, i+1, true);
		}
	}
	
	SwitchTarget(theEditField);
	
	//  Note: linking of Listeners and Broadcasters is done in the StDialogBoxHandler constructor
	
	while (inPickerLoop) {
		MessageT theMessage;
		
		theDialog->Show();
		
		while (true) {
			theMessage = theHandler.DoDialog();
			
			if (msg_OK == theMessage) {
				theEditField->GetDescriptor(theTypeStr);
				// Check that both fields are not empty
				if ( !theTypeStr[0] ) {
					UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("TypeFieldIsEmpty"), PPob_SimpleMessage);
				} else {
					break;
				}
			} else if (msg_Cancel == theMessage) {
				error = userCanceledErr;
				inPickerLoop = false;
				break;
			} else if (msg_TypeChooserMenu == theMessage) {
				// Retrieve the menu item and write it in the edit field
				itemIndex = theTypesMenu->GetValue();
				::GetMenuItemText( theTypesMenu->GetMacMenuH(), theTypesMenu->GetValue(), theString );
				theEditField->SetDescriptor(theString);
				break;  // Breaks out from the inner 'while' but still in the inPickerLoop 'while'
			} else if (msg_TypeChooserField == theMessage) {
				// If something is typed, set the popup to its first
				// element (the empty string).
				theTypesMenu->SetValue(0);
				break;  // Breaks out from the inner 'while' but still in the inPickerLoop 'while'
			}
		}
		
		// If the default button was hit, try to open the rezmaps
		if (msg_OK == theMessage) {
			UMiscUtils::PaddTypeIfNecessary(theTypeStr);
			UMiscUtils::PStringToOSType(theTypeStr, sChosenType);
			// Now get out of the outer 'while'
			inPickerLoop = false;
		} 
	}
	return error;
}


