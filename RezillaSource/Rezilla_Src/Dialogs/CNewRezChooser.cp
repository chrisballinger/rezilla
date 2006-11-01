// ===========================================================================
// CNewRezChooser.h
// 
//                       Created: 2006-10-07 07:20:12
//             Last modification: 2006-10-07 11:10:15
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================


#include "CNewRezChooser.h"
#include "CRezMap.h"
#include "CThreeButtonsBox.h"
#include "RezillaConstants.h"
#include "UDialogBoxHandler.h"
#include "UMessageDialogs.h"
#include "UMiscUtils.h"
#include "UResources.h"

#include <LEditText.h>
#include <LCheckBox.h>
#include <LString.h>


// ---------------------------------------------------------------------------------
//   CNewRezChooser															[public]
// ---------------------------------------------------------------------------------

CNewRezChooser::CNewRezChooser(CRezMap * inOwnerMap)
{
	mOwnerMap = inOwnerMap;
	mType = 0;
	mID = 0;
	mName[0] = 0;
	mAttrs = 0;
}


// ---------------------------------------------------------------------------------
//   ~CNewRezChooser														[public]
// ---------------------------------------------------------------------------------

CNewRezChooser::~CNewRezChooser()
{
}


// ---------------------------------------------------------------------------------
//   GetChosenValues														[public]
// ---------------------------------------------------------------------------------

void
CNewRezChooser::GetChosenValues(ResType &inType, short &inID, Str255 &inName, short &inAttrs)
{
	inType = mType;
	inID = mID;
	inAttrs = mAttrs;
	LString::CopyPStr(mName, inName);
	
}

// ---------------------------------------------------------------------------------
//   RunDialog																[public]
// ---------------------------------------------------------------------------------

OSErr
CNewRezChooser::RunDialog()
{
	OSErr			error = noErr;
	LCheckBox *		theCheckBox;
	LEditText *		theTypeField;
	LEditText *		theIDField;
	LEditText *		theNameField;
	long			theLong;
	Str255			theString;
	Boolean			isModified, inLoop;
	
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
			if (msg_OK == theMessage) {
				inLoop = false;
				break;
			} else if (msg_Cancel == theMessage) {
				error = userCanceledErr;
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
						UMiscUtils::PStringToOSType(theString, mType);
						if (mOwnerMap) {
							mOwnerMap->UniqueID(mType, mID);
						} else {
							UResources::UniqueID(mType, mID);
						}
						::NumToString(mID, theString);
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
				UMiscUtils::PStringToOSType(theString, mType);
				
				theIDField->GetDescriptor(theString);
				// Do we really have an ID
				if (theString[0]) {
					::StringToNum(theString, &theLong);
					mID = (short) theLong;
					
					// Get the name
					theNameField->GetDescriptor(mName);
					
					// Retrieve the attributes
					theCheckBox = dynamic_cast<LCheckBox *>(theDialog->FindPaneByID( item_NewSysHeap ));
					ThrowIfNil_(theCheckBox);
					if (theCheckBox->GetValue()) {
						mAttrs |= resSysHeap;
					} 
					theCheckBox = dynamic_cast<LCheckBox *>(theDialog->FindPaneByID( item_NewPurgeable ));
					ThrowIfNil_(theCheckBox);
					if (theCheckBox->GetValue()) {
						mAttrs |= resPurgeable;
					} 
					theCheckBox = dynamic_cast<LCheckBox *>(theDialog->FindPaneByID( item_NewLocked ));
					ThrowIfNil_(theCheckBox);
					if (theCheckBox->GetValue()) {
						mAttrs |= resLocked;
					} 
					theCheckBox = dynamic_cast<LCheckBox *>(theDialog->FindPaneByID( item_NewProtected ));
					ThrowIfNil_(theCheckBox);
					if (theCheckBox->GetValue()) {
						mAttrs |= resProtected;
					} 
					theCheckBox = dynamic_cast<LCheckBox *>(theDialog->FindPaneByID( item_NewPreload ));
					ThrowIfNil_(theCheckBox);
					if (theCheckBox->GetValue()) {
						mAttrs |= resPreload;
					} 
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
	return error;
}

