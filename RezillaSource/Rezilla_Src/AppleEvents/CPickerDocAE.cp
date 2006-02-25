// ===========================================================================
// CPickerDocAE.cp
// 
//                       Created: 2006-02-24 06:34:27
//             Last modification: 2006-02-24 06:47:57
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================
//  AppleEvent Object Model Support. These methods are part of the CPickerDoc 
//  class (inheriting from LModelObject).

#include "CRezMap.h"
#include "CPickerDoc.h"
#include "CPickerWindow.h"
#include "CRezMapDoc.h"
#include "CRezType.h"
#include "CRezTypeItem.h"
#include "CRezMapTable.h"
#include "UResources.h"
#include "RezillaConstants.h"

#include <LCommander.h>


// ---------------------------------------------------------------------------
//   MakeSelfSpecifier												  [public]
// ---------------------------------------------------------------------------

void
CPickerDoc::MakeSelfSpecifier(
	AEDesc	&inSuperSpecifier,
	AEDesc	&outSelfSpecifier) const
{
	Str255		docName;
	
	GetDescriptor(docName);

	StAEDescriptor	keyData;
	OSErr	err = ::AECreateDesc(typeChar, docName + 1, docName[0], &keyData.mDesc);
	ThrowIfOSErr_(err);
	
	err = ::CreateObjSpecifier(rzom_cPickerDoc, &inSuperSpecifier, formName,
								&keyData.mDesc, false, &outSelfSpecifier);
	ThrowIfOSErr_(err);
}


// ---------------------------------------------------------------------------
//   GetAEProperty
// ---------------------------------------------------------------------------
//	Return a descriptor for the specified Property
//	rzom_pReadOnly		= 'pRDO';	// mapReadOnly
// 	rzom_cRezType		= 'cTYP';	// RezType
// 	rzom_pOwnerMapDoc	= 'pOWM';	// Document's owner rezmap doc
// 	rzom_cRezMapDoc		= 'MapD';	// RezMap document
//  pIndex				= 'pidx';
//  cWindow				= 'cwin';

void
CPickerDoc::GetAEProperty(
	DescType		inProperty,
	const AEDesc&	inRequestedType,
	AEDesc&			outPropertyDesc) const
{
	OSErr	error = noErr;
	
	switch (inProperty) {
		
		case rzom_pReadOnly:
		error = ::AECreateDesc(typeBoolean, (Ptr) &mReadOnly,
									sizeof(Boolean), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
		
		
		case pIndex: {
			// Return the index of this document among the other editor docs
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
		
		
		// Handled in GetModelProperty
// 		case rzom_cRezObj:
// 		break;
		
		
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
	switch (inProperty) {
		
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
CPickerDoc::GetAEPosition(const CPickerDoc * inDoc) {
	SInt32		currPos = 0, result = 0;
	LDocument*	theDoc = nil;
	Boolean		found = false;
	DescType	theKind;

	TArrayIterator<LDocument*> iterator( LDocument::GetDocumentList() );
	while (iterator.Next(theDoc)) {
		theKind = theDoc->GetModelKind();
		if (theKind == rzom_cPickerDoc) {
			currPos++;
			if (theDoc == inDoc) {
				result = currPos;
				break;
			} 
		} 				
		theDoc = nil;
	}

	return result;
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
			if (mMainWindow != nil) {
				PutInToken(mMainWindow, outToken);
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
		theModelObject = dynamic_cast<LModelObject *>(mMainWindow);
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


