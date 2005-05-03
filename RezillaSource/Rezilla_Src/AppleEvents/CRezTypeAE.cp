// ===========================================================================
// CRezTypeAE.cp
// 
//                       Created: 2005-04-09 10:03:39
//             Last modification: 2005-05-02 17:41:06
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
//  AppleEvent Object Model Support. These methods are part of the CRezType 
//  class (inheriting from LModelObject).

#include "CRezMap.h"
#include "CRezType.h"
#include "CRezObj.h"
#include "CRezMapDoc.h"
#include "UMiscUtils.h"
#include "RezillaConstants.h"

#include <LCommander.h>



// ---------------------------------------------------------------------------
//	¥ MakeSelfSpecifier												  [public]
// ---------------------------------------------------------------------------

void
CRezType::MakeSelfSpecifier(
	AEDesc	&inSuperSpecifier,
	AEDesc	&outSelfSpecifier) const
{
		StAEDescriptor	keyData;
		OSErr			err;
		Str255			name;

		// Specify by name
		GetModelName(name);
		keyData.Assign(name);

		err = ::CreateObjSpecifier(rzom_cRezType, &inSuperSpecifier, formName,
										keyData, false, &outSelfSpecifier);
		ThrowIfOSErr_(err);
}


// ---------------------------------------------------------------------------
//	¥ GetAEProperty
// ---------------------------------------------------------------------------
//	Return a descriptor for the specified Property
//  rzom_pName			= pName;		// Name ('pnam')

void
CRezType::GetAEProperty(
	DescType		inProperty,
	const AEDesc&	inRequestedType,
	AEDesc&			outPropertyDesc) const
{
	OSErr	error = noErr;
	
	switch (inProperty) {
		
		case pIndex: {
			// Return the index of this type in the rezmap doc
			SInt32	position = mOwnerMap->GetOwnerDoc()->GetIndexForType(mType);
			if (position > 0) {
				error = ::AECreateDesc(typeSInt32, (Ptr) &position,
											sizeof(SInt32), &outPropertyDesc);
			} else {
				error = errAENoSuchObject;
			}
			ThrowIfOSErr_(error);
			break;
		}
		

		case pName: 
		Str255	name;
		GetModelName(name);
		error = ::AECreateDesc(typeChar, (Ptr) name + 1,
							StrLength(name), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;

		
		case pID: 
		error = ::AECreateDesc(typeUInt32, &mType,
							sizeof(UInt32), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;

		
		default:
		LModelObject::GetAEProperty(inProperty, inRequestedType,
									outPropertyDesc);
		break;
	}
}


// ---------------------------------------------------------------------------
//	 CountSubModels												  [public]
// ---------------------------------------------------------------------------
// Had to modify the prototypes for CountAllTypes and CountAllResources by
// adding a 'const' to make the compiler happy.

SInt32
CRezType::CountSubModels(
	DescType	inModelID) const
{
	SInt32	result = 0;
	short	count = 0;
	
	switch (inModelID) {
		
		case rzom_cRezObj: 
		if (CountResources(count) == noErr) {
			result = count;
		}
		break;

		default:
		result = LModelObject::CountSubModels(inModelID);
		break;
	}

	return result;
}


// ---------------------------------------------------------------------------
//	 GetSubModelByPosition											  [public]
// ---------------------------------------------------------------------------

void
CRezType::GetSubModelByPosition(
	DescType		inModelID,
	SInt32			inPosition,
	AEDesc&			outToken) const
{
	switch (inModelID) {
		
		case rzom_cRezObj:
		CRezObj *	theRezObj = nil;
		Handle		theHandle;
		OSErr		error;
	
		error = GetResourceAtIndex( (short) inPosition, theHandle, true);
		if (error == noErr) {
			theRezObj = new CRezObj( theHandle, mOwnerMap->GetRefnum());
		} 
			
		if (theRezObj != nil) {
			// cast is needed because of constness
			theRezObj->SetSuperModel( (CRezType *) this);
			PutInToken(theRezObj, outToken);
		} else {
			ThrowOSErr_(errAENoSuchObject);
		}
		break;
		
		
		default:
		LModelObject::GetSubModelByPosition(inModelID, inPosition,
											outToken);
		break;
	}
}


// ---------------------------------------------------------------------------
//	 GetSubModelByName												  [public]
// ---------------------------------------------------------------------------
//	Pass back a token to a SubModel specified by name

void
CRezType::GetSubModelByName(
	DescType		inModelID,
	Str255			inName,
	AEDesc&			outToken) const
{
	switch (inModelID) {

		case rzom_cRezObj:
		CRezObj *	theRezObj = nil;
		Handle		theHandle;
		OSErr		error;
	
		error = GetWithName(inName, theHandle);
		if (error == noErr) {
			theRezObj = new CRezObj( theHandle, mOwnerMap->GetRefnum());
		} 
			
		if (theRezObj != nil) {
			// cast is needed because of constness
			theRezObj->SetSuperModel( (CRezType *) this);
			PutInToken(theRezObj, outToken);
		} else {
			ThrowOSErr_(errAENoSuchObject);
		}
		break;
		

		default:
			LModelObject::GetSubModelByName(inModelID, inName, outToken);
			break;
	}
}


// ---------------------------------------------------------------------------
//	 GetSubModelByUniqueID
// ---------------------------------------------------------------------------
//	Pass back a Token for the SubModel with the specified unique ID: this
//	is the type as an unsigned long.

void
CRezType::GetSubModelByUniqueID(
	DescType		inModelID,
	const AEDesc	&inKeyData,
	AEDesc			&outToken) const
{
	if (inModelID == rzom_cRezObj) {
		CRezObj *	theRezObj = nil;
		Handle		theHandle;
		short		theID;
		OSErr		error;
		
		error = ::AEGetDescData(&inKeyData, &theID, sizeof(short));
		ThrowIfOSErr_(error);

		error = GetWithID(theID, theHandle);
		if (error == noErr) {
			theRezObj = new CRezObj( theHandle, mOwnerMap->GetRefnum());
		} 
			
		if (theRezObj != nil) {
			// cast is needed because of constness
			theRezObj->SetSuperModel( (CRezType *) this);
			PutInToken(theRezObj, outToken);
		} else {
			ThrowOSErr_(errAENoSuchObject);
		}
	}
}


// ---------------------------------------------------------------------------
//	¥ GetModelName
// ---------------------------------------------------------------------------
//	Return the name of a Window as an AppleEvent model object(Str255&) 

StringPtr
CRezType::GetModelName(
	Str255	outModelName) const
{
	Str255	name;
	UMiscUtils::OSTypeToPString(mType, name);
	LString::CopyPStr(name, outModelName);
	return outModelName;
}


// ---------------------------------------------------------------------------
//	¥ AEPropertyExists
// ---------------------------------------------------------------------------

bool
CRezType::AEPropertyExists(
	DescType	inProperty) const
{
	bool	exists = false;

	switch (inProperty) {

		case pIndex:
		case pName:
		case pID:
			exists = true;
			break;

		default:
			exists = LModelObject::AEPropertyExists(inProperty);
			break;
	}

	return exists;
}







