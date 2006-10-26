// ===========================================================================
// CPickerDocAE.cp
// 
//                       Created: 2006-02-24 06:34:27
//             Last modification: 2006-10-12 14:22:13
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================
//  AppleEvent Object Model Support. These methods are part of the CPickerDoc 
//  class (inheriting from LModelObject).

#include "CRezMap.h"
#include "RezillaConstants.h"
#include "CPickerDoc.h"
#include "CPickerWindow.h"
#include "CPickerView.h"
#include "CRezMapDoc.h"
#include "CRezType.h"
#include "CRezTypeItem.h"
#include "CRezMapTable.h"
#include "UResources.h"
#include "UMiscUtils.h"

#include <LCommander.h>


// ---------------------------------------------------------------------------
//   MakeSelfSpecifier												  [public]
// ---------------------------------------------------------------------------

void
CPickerDoc::MakeSelfSpecifier(
	AEDesc	&inSuperSpecifier,
	AEDesc	&outSelfSpecifier) const
{
	Str255		theString;
	ResType		theType = mRezTypeItem->GetRezType()->GetType();
	OSErr		err;
	StAEDescriptor	keyData;

	UMiscUtils::OSTypeToPString(theType, theString);
	err = ::AECreateDesc(typeChar, theString + 1, theString[0], &keyData.mDesc);
	ThrowIfOSErr_(err);
	
	err = ::CreateObjSpecifier(rzom_cPickerDoc, &inSuperSpecifier, formName,
								&keyData.mDesc, false, &outSelfSpecifier);
	ThrowIfOSErr_(err);
}


// ---------------------------------------------------------------------------
//   GetAEProperty
// ---------------------------------------------------------------------------
//	Return a descriptor for the specified Property
//  rzom_pName			= pName;	// Name ('pnam')
//  pIndex				= 'pidx';
//	rzom_pReadOnly		= 'pRDO';	// Read only
//  cWindow				= 'cwin';	// Picker's window
// 	rzom_cRezType		= 'cTYP';	// RezType
// 	rzom_pOwnerMapDoc	= 'pOWM';	// Document's owner rezmap doc
// 	rzom_cRezMapDoc		= 'MapD';	// ditto
// 	rzom_pSelectedID	= 'pSEL';	// Selected resource

void
CPickerDoc::GetAEProperty(
	DescType		inProperty,
	const AEDesc&	inRequestedType,
	AEDesc&			outPropertyDesc) const
{
	OSErr		error = noErr;
	ResType		theType;
	Str255		theString;

	switch (inProperty) {
		
		case rzom_pName: 
		// The "name" of the picker is its type so that one can simply
		// write in AppleScript:
		//     plugin "MENU" of map document 1
		theType = mRezTypeItem->GetRezType()->GetType();
		UMiscUtils::OSTypeToPString(theType, theString);
		error = ::AECreateDesc(typeChar, (Ptr) theString + 1, theString[0], &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
		

		case rzom_pReadOnly:
		error = ::AECreateDesc(typeBoolean, (Ptr) &mReadOnly,
									sizeof(Boolean), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
		
		
		case pIndex: {
			// Return the index of this document among the other pickers
			// for the same rezmap doc
			SInt32	position = GetAEPosition(this);
			if (position > 0) {
				error = ::AECreateDesc(typeSInt32, (Ptr) &position,
											sizeof(SInt32), &outPropertyDesc);
			} else {
				error = errAENoSuchObject;
			}
			ThrowIfOSErr_(error);
			break;
		}
				
		
		case rzom_cRezMapDoc:
		case rzom_pOwnerMapDoc:  {
			// Returns the owner rezmap doc by index
			AEDesc superSpec;
			StAEDescriptor keyData;
			SInt32 position = CRezMapDoc::GetAEPosition(mRezMapTable->GetOwnerDoc());
			
			superSpec.descriptorType = typeNull;
			superSpec.dataHandle = nil;
			keyData.Assign(position);
			error = ::CreateObjSpecifier( rzom_cRezMapDoc, &superSpec, formAbsolutePosition,
									keyData, false, &outPropertyDesc);
			ThrowIfOSErr_(error);
			break;
		}
		
		
		// Note: rzom_cRezType and rzom_cPickerWindow are handled in GetModelProperty
// 		case rzom_cRezType:
// 		break;
		
// 		case rzom_cPickerWindow:
// 		break;
				
		
		case rzom_pSelectedID: {
			// Return the index of this document among the other pickers
			// for the same rezmap doc

			CPickerView* theSelView = mPickerWindow->GetSelectedView();
			if (theSelView) {
				short	theID = (short) theSelView->GetPaneID();
				::NumToString(theID, theString);
			} else {
				theString[0] = 0;
			}
			error = ::AECreateDesc(typeChar, (Ptr) theString + 1, theString[0], &outPropertyDesc);
			ThrowIfOSErr_(error);
			break;
		}
				
		
		default:
		LDocument::GetAEProperty(inProperty, inRequestedType,
									outPropertyDesc);
		break;
	}
}


// ---------------------------------------------------------------------------
//   SetAEProperty
// ---------------------------------------------------------------------------
// The CPickerDoc properties are readOnly. Pass up to the LDocument class.

void
CPickerDoc::SetAEProperty(
	DescType		inProperty,
	const AEDesc&	inValue,
	AEDesc&			outAEReply)
{
	Str255		theString;

	switch (inProperty) {
		case rzom_pSelectedID: {
			CPickerView* theSelView;
			long		theLong;
			short		theID;
			
			// Return the index of this document among the other pickers
			// for the same rezmap doc
			UExtractFromAEDesc::ThePString(inValue, theString, sizeof(theString));
			if (theString[0] == 0) {
				theSelView = NULL;
			} else {
				::StringToNum(theString, &theLong);
				theID = theLong;
				theSelView = dynamic_cast<CPickerView*>(mPickerWindow->GetContentsView()->FindPaneByID(theID));
			}
			mPickerWindow->SetSelectedView(theSelView);
			mPickerWindow->Refresh();
			break;
		}
		
		
		default:
		LDocument::SetAEProperty(inProperty, inValue, outAEReply);
		break;
	}
}


// ---------------------------------------------------------------------------
//   AEPropertyExists
// ---------------------------------------------------------------------------

bool
CPickerDoc::AEPropertyExists(
	DescType	inProperty) const
{
	bool	exists = false;

	switch (inProperty) {

		case pIndex:
		case rzom_pReadOnly:
		case cWindow:
		case rzom_cRezType:
		case rzom_cRezMapDoc:
		case rzom_pOwnerMapDoc: 
			exists = true;
			break;

		default:
			exists = LModelObject::AEPropertyExists(inProperty);
			break;
	}

	return exists;
}


// ---------------------------------------------------------------------------
//   GetAEPosition
// ---------------------------------------------------------------------------

SInt32
CPickerDoc::GetAEPosition(const CPickerDoc * inPicker) const
{
	SInt32		position = 1;
	CPickerDoc	*thePicker = NULL, *currPicker;
	TArray<CPickerDoc *>* pickersList = mRezMapTable->GetOwnerDoc()->GetOpenedPickers();

	TArrayIterator<CPickerDoc*> iterator(*pickersList);
	while (iterator.Next(currPicker)) {
		if (inPicker == currPicker) {
			thePicker = currPicker;
			break;
		} 
		position++;
	}
	if (!thePicker) {
		ThrowOSErr_(errAENoSuchObject);
	} 
	return position;
}


// ---------------------------------------------------------------------------
//   GetSubModelByPosition											  [public]
// ---------------------------------------------------------------------------

void
CPickerDoc::GetSubModelByPosition(
	DescType		inModelID,
	SInt32			inPosition,
	AEDesc&			outToken) const
{
	switch (inModelID) {

		case cWindow: 
		case rzom_cPickerWindow: 
		if (inPosition == 1) {
			if (mPickerWindow != nil) {
				PutInToken(mPickerWindow, outToken);
			} else {
				ThrowOSErr_(errAENoSuchObject);
			}
			break;
		} 

		// Fall through...

		default:
			LModelObject::GetSubModelByPosition(inModelID, inPosition, outToken);
			break;
	}
}


// ---------------------------------------------------------------------------
//   GetModelProperty
// ---------------------------------------------------------------------------
//	Return a ModelObject object for 'cwin' property

LModelObject*
CPickerDoc::GetModelProperty(DescType inProperty) const
{
	LModelObject* theModelObject = nil;

	switch (inProperty) {

		case rzom_cPickerWindow:
		case cWindow:
		theModelObject = dynamic_cast<LModelObject *>(mPickerWindow);
		break;
		

		case rzom_cRezType:
		theModelObject = dynamic_cast<LModelObject *>(mRezTypeItem->GetRezType());
		break;


		default:
		theModelObject = LModelObject::GetModelProperty(inProperty);
			break;
	}

	return theModelObject;
}


// ---------------------------------------------------------------------------
//   HandleAESave													  [public]
// ---------------------------------------------------------------------------
//	Respond to "Save" AppleEvent

void
CPickerDoc::HandleAESave(
	const AppleEvent&	/* inSaveAE */)
{
	// A picker has no notion of saved document. This means 
	// the AppleEvent failed.
	ThrowOSErr_(userCanceledErr);
}


