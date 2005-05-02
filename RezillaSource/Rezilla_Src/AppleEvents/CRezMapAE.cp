// ===========================================================================
// CRezMapAE.cp					
// 
//                       Created: 2004-11-30 08:50:37
//             Last modification: 2005-05-02 18:52:16
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
//  AppleEvent Object Model Support. These methods are part of the CRezMap 
//  class (inheriting from LModelObject).

#include "CRezMap.h"
#include "CRezType.h"
#include "CRezObj.h"
#include "CRezMapDoc.h"
#include "UResources.h"
#include "RezillaConstants.h"

#include <LCommander.h>


// ---------------------------------------------------------------------------
//	 MakeSelfSpecifier
// ---------------------------------------------------------------------------
//	Make an Object Specifier for a RezMap

void
CRezMap::MakeSelfSpecifier(
	AEDesc&	inSuperSpecifier,
	AEDesc&	outSelfSpecifier) const
{
	if (mSuperModel == nil) {
		OSErr	err;
		StAEDescriptor	keyData;
		keyData.Assign(mRefNum);

		// Make ospec for the rezmap
		err = ::CreateObjSpecifier(rzom_cRezMap, &inSuperSpecifier, formUniqueID,
										keyData, false, &outSelfSpecifier);
		ThrowIfOSErr_(err);

	} else {
		LModelObject::MakeSelfSpecifier(inSuperSpecifier, outSelfSpecifier);
	}
}



// ---------------------------------------------------------------------------
//	 GetAEProperty
// ---------------------------------------------------------------------------
//	Return a descriptor for the specified Property
// rzom_pRefNum			= 'pRFN';		// RefNum
// rzom_pAttributes		= 'pATR';		// Attributes
// rzom_pReadOnly		= 'pRDO';		// mapReadOnly
// rzom_pCompact		= 'pCPT';		// mapCompact
// rzom_pChanged		= pIsModified;	// mapChanged/resChanged ('imod')

void
CRezMap::GetAEProperty(
	DescType		inProperty,
	const AEDesc&	inRequestedType,
	AEDesc&			outPropertyDesc) const
{
	OSErr		error = noErr;
	
	switch (inProperty) {
		
		case rzom_pRefNum:
		error = ::AECreateDesc(typeSInt16, (Ptr) &mRefNum,
									sizeof(short), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
		
		case rzom_pAttributes:
		short		theAttrs;
		GetMapAttributes(theAttrs);
		error = ::AECreateDesc(typeSInt16, (Ptr) &theAttrs,
									sizeof(short), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
		
		case rzom_pReadOnly:
		GetAERezMapAttribute(mapReadOnly, outPropertyDesc);
		break;
		
		case rzom_pCompact:
		GetAERezMapAttribute(mapCompact, outPropertyDesc);
		break;
		
		case rzom_pChanged:
		GetAERezMapAttribute(mapChanged, outPropertyDesc);
		break;
		
		default:
		LModelObject::GetAEProperty(inProperty, inRequestedType,
									outPropertyDesc);
		break;
	}
}


// ---------------------------------------------------------------------------
//	 SetAEProperty
// ---------------------------------------------------------------------------

void
CRezMap::SetAEProperty(
	DescType		inProperty,
	const AEDesc&	inValue,
	AEDesc&			outAEReply)
{
	switch (inProperty) {

		case rzom_pAttributes:
		short		theAttrs;
		UExtractFromAEDesc::TheSInt16(inValue, theAttrs);
		SetMapAttributes(theAttrs);
		break;
		
		case rzom_pReadOnly:
		SetAERezMapAttribute(inValue, mapReadOnly);
		break;
		
		case rzom_pCompact:
		SetAERezMapAttribute(inValue, mapCompact);
		break;
		
		case rzom_pChanged:
		SetAERezMapAttribute(inValue, mapChanged);
		break;

		default:
			LModelObject::SetAEProperty(inProperty, inValue, outAEReply);
			break;
	}
}


// // ---------------------------------------------------------------------------
// //	 SetAEProperty
// // ---------------------------------------------------------------------------
// 
// void
// CRezMap::SetAEProperty(
// 	DescType		inProperty,
// 	const AEDesc&	inValue,
// 	AEDesc&			outAEReply)
// {}


// ---------------------------------------------------------------------------
//	 GetAERezMapAttribute
// ---------------------------------------------------------------------------

void
CRezMap::GetAERezMapAttribute(
	short		inFlag,
	AEDesc&		outPropertyDesc) const
{
	Boolean		attrIsSet;
	short		theAttrs;
	OSErr		error;
	
	GetMapAttributes(theAttrs);
	attrIsSet = ((theAttrs & inFlag) > 0);
	
	error = ::AECreateDesc(typeBoolean, (Ptr) &attrIsSet,
								sizeof(Boolean), &outPropertyDesc);
	ThrowIfOSErr_(error);
}


// ---------------------------------------------------------------------------
//	 SetAERezMapAttribute
// ---------------------------------------------------------------------------

void
CRezMap::SetAERezMapAttribute(const AEDesc& inValue, short inFlag)
{
	short		theAttrs;
	Boolean		setIt;
	
	UExtractFromAEDesc::TheBoolean(inValue, setIt);
	GetMapAttributes(theAttrs);

	if (setIt) {
		theAttrs &= inFlag;
	} else {
		theAttrs &= ~inFlag;
	}
	SetMapAttributes(theAttrs);
}


// ---------------------------------------------------------------------------
//	 AEPropertyExists
// ---------------------------------------------------------------------------

bool
CRezMap::AEPropertyExists(
	DescType	inProperty) const
{
	bool	exists = false;

	switch (inProperty) {

		case rzom_pAttributes:
		case rzom_pChanged:
		case rzom_pCompact:
		case rzom_pReadOnly:
		case rzom_pRefNum:
			exists = true;
			break;

		default:
			exists = LModelObject::AEPropertyExists(inProperty);
			break;
	}

	return exists;
}


// ---------------------------------------------------------------------------
//	 CountSubModels												  [public]
// ---------------------------------------------------------------------------
// Had to modify the prototypes for CountAllTypes and CountAllResources by
// adding a 'const' to make the compiler happy.

SInt32
CRezMap::CountSubModels(
	DescType	inModelID) const
{
	SInt32	result = 0;
	short	count;
	
	switch (inModelID) {

		case rzom_cRezType:
		if (CountAllTypes(count) == noErr) {
			result = count;
		}
		break;
		
		
		case rzom_cRezObj: 
		if (CountAllResources(count) == noErr) {
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
CRezMap::GetSubModelByPosition(
	DescType		inModelID,
	SInt32			inPosition,
	AEDesc&			outToken) const
{
	switch (inModelID) {
		
		case rzom_cRezType:
		CRezType * theRezType = nil;
		
		if (mOwnerDoc != nil) {
			theRezType = mOwnerDoc->GetRezTypeAtIndex(inPosition);
		} 
		if (theRezType != nil) {
			PutInToken(theRezType, outToken);
		} else {
			ThrowOSErr_(errAENoSuchObject);
		}
		break;
		
		
		case rzom_cRezObj: 
// 		CRezObj * theRezObj = GetRezObjAtIndex(inPosition);
// 		if (theRezObj != nil) {
// 			PutInToken(theRezObj, outToken);
// 		} else {
// 			ThrowOSErr_(errAENoSuchObject);
// 		}
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
CRezMap::GetSubModelByName(
	DescType		inModelID,
	Str255			inName,
	AEDesc&			outToken) const
{
	switch (inModelID) {

		case rzom_cRezType:
		CRezType * theRezType = nil;
		
		if (mOwnerDoc != nil) {
			theRezType = mOwnerDoc->GetRezTypeByName(inName);
		} 
		if (theRezType != nil) {
			PutInToken(theRezType, outToken);
		} else {
			ThrowOSErr_(errAENoSuchObject);
		}
		break;
		
		
		case rzom_cRezObj: 
// 		CRezObj * theRezObj = GetRezObjAtIndex(inPosition);
// 		if (theRezObj != nil) {
// 			PutInToken(theRezObj, outToken);
// 		} else {
// 			ThrowOSErr_(errAENoSuchObject);
// 		}
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
CRezMap::GetSubModelByUniqueID(
	DescType		inModelID,
	const AEDesc	&inKeyData,
	AEDesc			&outToken) const
{
	if (inModelID == rzom_cRezType) {
		CRezType *	theRezType = nil;
		ResType		uniqueID;

		ThrowIfOSErr_( ::AEGetDescData(&inKeyData, &uniqueID, sizeof(ResType)) );
		
		if (mOwnerDoc != nil) {
			theRezType = mOwnerDoc->GetRezTypeByType(uniqueID);
		} 
		if (theRezType != nil) {
			PutInToken(theRezType, outToken);
		} else {
			ThrowOSErr_(errAENoSuchObject);
		}
	}
}


// // ---------------------------------------------------------------------------
// //	 GetPositionOfSubModel											  [public]
// // ---------------------------------------------------------------------------
// //	Return the position (1 = first) of a SubModel within an Application
// 
// SInt32
// CRezMap::GetPositionOfSubModel(
// 	DescType				inModelID,
// 	const LModelObject*		inSubModel) const
// {
// 	SInt32	position;
// 
// 	switch (inModelID) {
// 
// 		case rzom_cRezType: 
// // 		const ResType theType = dynamic_cast<CRezType *>(inSubModel)->GetType();
// // 		position = mOwnerDoc->GetIndexForType(theType);
// 		break;
// 		
// 		
// 		default:
// 		position = LModelObject::GetPositionOfSubModel(inModelID, inSubModel);
// 		break;
// 	}
// 
// 	return position;
// }


// ---------------------------------------------------------------------------
// //	 GetAllSubModels
// // ---------------------------------------------------------------------------
// //	Pass back a Token list for all SubModels of the specified type
// 
// void
// CRezMap::GetAllSubModels(
// 	DescType		inModelID,
// 	AEDesc			&outToken) const
// {
// 	OSErr error;
// 	
// 	if (inModelID == rzom_cRezMap) {
// 		if (outToken.descriptorType == typeNull) {
// 			error = ::AECreateList(nil, 0, false, &outToken);
// 			ThrowIfOSErr_(error);
// 		}
// 
// 		TArrayIterator<CRezMap*> iterator( CRezMap::GetRezMapList() );
// 		CRezMap *	theMap = nil;
// 
// 		while (iterator.Next(theMap)) {
// 			StAEDescriptor	subToken;
// 			PutInToken(theMap, outToken);					
// 			error = ::AEPutDesc(&outToken, 0, subToken);
// 			ThrowIfOSErr_(error);			
// 			theMap = nil;
// 		}
// 	} else {
// 		LModelObject::GetAllSubModels(inModelID, outToken);
// 	}
// }



// ---------------------------------------------------------------------------
//	 GetRezTypeAtIndex
// ---------------------------------------------------------------------------

CRezType *
CRezMap::GetRezTypeAtIndex(SInt32 inPosition) const
{
	CRezType * theRezType = nil;
	CRezMapDoc * theDoc = GetOwnerDoc();
	
	if (theDoc != nil) {
		theRezType = theDoc->GetRezTypeAtIndex(inPosition);
	} 
	
	return theRezType;
}


// // ---------------------------------------------------------------------------
// //	 GetOwnerDoc
// // ---------------------------------------------------------------------------
// 
// CRezMapDoc *
// CRezMap::GetOwnerDoc() const
// {
// 	CRezMapDoc * theDoc = nil;
// 	TArrayIterator<CRezMapDoc*> iterator( CRezMapDoc::GetRezMapDocList() );
// 
// 	while (iterator.Next(theDoc)) {
// 		if (theDoc->GetRezMap()->GetRefnum() == mRefNum) {
// 			break;
// 		}
// 	}
// 	
// 	return theDoc;
// }

