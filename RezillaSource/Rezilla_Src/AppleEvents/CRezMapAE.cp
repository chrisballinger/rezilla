// ===========================================================================
// CRezMapAE.cp					
// 
//                       Created: 2004-11-30 08:50:37
//             Last modification: 2005-05-16 22:34:12
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
#include "CRezObjItem.h"
#include "CRezMapDoc.h"
#include "UMiscUtils.h"
#include "UCodeTranslator.h"
#include "UCompareUtils.h"
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
		
		case rzom_pTypesList: {
			if (outPropertyDesc.descriptorType == typeNull) {
				error = ::AECreateList(nil, 0, false, &outPropertyDesc);
				ThrowIfOSErr_(error);
			}
			
			ResType		theType;
			UInt16		index = 1;
			CTypeComparator* typeComparator = new CTypeComparator;
			TArray<ResType>* typesArray = new TArray<ResType>( typeComparator, true);
			TArrayIterator<ResType>	iterator(*typesArray);
			
			GetAllTypes(typesArray);
			
			while (iterator.Next(theType)) {
				Str255			name;
				StAEDescriptor	keyData;
				
				UMiscUtils::OSTypeToPString(theType, name);
				
				error = ::AECreateDesc(typeChar, name + 1, name[0], &keyData.mDesc);
				error = ::AEPutDesc(&outPropertyDesc, index, &keyData.mDesc);
				index++;
			}
			
			if (typesArray != nil) { delete typesArray; } 
			break; 
		}
			
		
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


// ---------------------------------------------------------------------------
//	¥ GetModelTokenSelf
// ---------------------------------------------------------------------------
//	Intercept the Type-ID specifier case: in this case inModelID should be
//	rzom_cRezObj and inKeyForm should be formAbsolutePosition ('indx').
//	Otherwise call the inherited method.

void
CRezMap::GetModelTokenSelf(
	DescType		inModelID,
	DescType		inKeyForm,
	const AEDesc&	inKeyData,
	AEDesc&			outToken) const
{
	if (inModelID == rzom_cRezObj) {
		ThrowIfNot_(inKeyForm == formAbsolutePosition);
		
		// inKeyData should be a two elements list whose first element is 
		// the required type and the second is the required ID
		OSErr		error;
		char		buffer[256];
		Str255		typName;
		SInt32		numArgs;
		AEKeyword	theKey;
		DescType	theType;
		Size		theSize;
		StAEDescriptor	idDesc;

		error = ::AECountItems(&inKeyData, &numArgs);
		ThrowIfOSErr_(error);
		ThrowIfNot_(numArgs >= 2);
		
		error = ::AEGetNthPtr(&inKeyData, 1, typeChar, &theKey, &theType, 
						 (Ptr) buffer, sizeof(buffer), &theSize);
		ThrowIfOSErr_(error);
		buffer[theSize] = 0;
		CopyCStringToPascal(buffer, typName);				 
		
		error = ::AEGetNthDesc(&inKeyData, 2, typeSInt32, &theKey, idDesc);
		ThrowIfOSErr_(error);
		
		CRezType * theRezType = theRezType = mOwnerDoc->GetRezTypeByName(typName);
		
		if (theRezType != nil) {
			theRezType->GetSubModelByUniqueID(rzom_cRezObj, idDesc, outToken);
		} else {
			ThrowOSErr_(errAENoSuchObject);
		}
	} else {
		LModelObject::GetModelTokenSelf(inModelID, inKeyForm, inKeyData, outToken);
	}
}


// // ---------------------------------------------------------------------------
// //	¥ HandleAppleEvent												  [public]
// // ---------------------------------------------------------------------------
// 
// void
// CRezMap::HandleAppleEvent(
// 	const AppleEvent&	inAppleEvent,
// 	AppleEvent&			outAEReply,
// 	AEDesc&				outResult,
// 	long				inAENumber)
// {	
// 	switch (inAENumber) {
// 		
// 		default:
// // 		mOwnerDoc->HandleAppleEvent(inAppleEvent, outAEReply, outResult, inAENumber);
// 		LModelObject::HandleAppleEvent(inAppleEvent, outAEReply, outResult, inAENumber);
// 		break;
// 	}
// }


// ---------------------------------------------------------------------------
//	¥ HandleCreateElementEvent
// ---------------------------------------------------------------------------
// This function handles the "make new" event in order to create a new
// resource in the map. Properties can be set using the "with properties"
// parameter: the type must be specified in this AERecord. Thus one can
// write in AppleScript:
//   make new resource of map 1 with properties {type:"TEXT", ID:129, attributes:8}
//  
// The optional "with data" parameter is also supported. For instance:
//   make new resource of map 1 with properties {type:"TEXT"} with data "Hello Rezilla!"
//   
// If the ID is not specified, an unique ID is attributed. If it does 
// exist, the new resource will replace the existing one.

LModelObject*
CRezMap::HandleCreateElementEvent(
	DescType			inElemClass,
	DescType			inInsertPosition,
	LModelObject*		inTargetObject,
	const AppleEvent&	inAppleEvent,
	AppleEvent&			outAEReply)
{
#pragma unused (inInsertPosition, inTargetObject, outAEReply)
	
	OSErr 			error, ignoreErr;
	AEDesc			propDesc;
	DescType		returnedType;
	Size			actualSize;
	OSType			theType;
	SInt16			theID = 0, theAttrs = 0;
	Str255			typeStr, nameStr;
	Boolean			isReadOnly = false;
	SInt16			theFork = fork_datafork;
	CRezObj *		rezObj;
	CRezObjItem *	rezObjItem;

	if (inElemClass != rzom_cRezObj) {
		ThrowOSErr_(errAEUnknownObjectType);
	} 

	// Extract the "with properties" parameter which contains property
	// values. Here, this parameter is required because it must contain the
	// type of the new resource.
	error = ::AEGetParamDesc(&inAppleEvent, keyAEPropData, typeAERecord, &propDesc);
	ThrowIfOSErr_(error);

	// Look for some properties. We support "type", "ID", "name",
	// "attributes" keywords (resp. rzom_pType, rzom_pResID, rzom_pName,
	// rzom_pAttributes). The type is required, the others are optional.
	error = ::AEGetParamPtr(&propDesc, rzom_pType, typeChar, &returnedType,
							typeStr, sizeof(Str255), &actualSize);
	ThrowIfOSErr_(error);
	UMiscUtils::PStringToOSType(typeStr, theType);

	ignoreErr = ::AEGetParamPtr(&propDesc, rzom_pResID, typeSInt16, &returnedType,
								&theID, sizeof(OSType), &actualSize);
	if (ignoreErr != noErr) {
		UniqueID(theType, theID);
	} 
	
	ignoreErr = ::AEGetParamPtr(&propDesc, rzom_pName, typeChar, &returnedType,
							nameStr, sizeof(Str255), &actualSize);
	if (ignoreErr != noErr) {
		nameStr[0] = 0;
	} 

	ignoreErr = ::AEGetParamPtr(&propDesc, rzom_pAttributes, typeSInt16, &returnedType,
								&theAttrs, sizeof(SInt16), &actualSize);

	// Create a new resource in the RezMapDoc
	rezObjItem = mOwnerDoc->DoCreateResource(theType, theID, &nameStr, theAttrs, true);
	ThrowIfNil_(rezObjItem);
	
	mOwnerDoc->SetModified(true);
	rezObj = rezObjItem->GetRezObj();
	rezObj->SetAttributesInMap(theAttrs);
	
	// Look for a possible "with data" parameter containing initial data
	// for the resource. This data is expected to be in hexadecimal format
	// except in the case of a TEXT resource where the text is passed
	// directly.
	AEDesc	valueDesc;
	ignoreErr = AEGetParamDesc(&inAppleEvent, keyAEData, typeWildCard, &valueDesc);
	if (ignoreErr != noErr) {
		Size theSize = ::AEGetDescDataSize(&valueDesc);
		Handle dataH = NewHandle(theSize);
		if (dataH != nil) {
			ignoreErr = ::AEGetDescData(&valueDesc, *dataH, theSize);
			if (theType == 'TEXT') {
				rezObj->SetData( dataH );
			} else {
				StHexToByteTranslator translator(dataH);
				translator.Convert();
				rezObj->SetData( translator.GetOutHandle() );
			}
			::DisposeHandle(dataH);
		} 
	} 
	
	if (valueDesc.descriptorType != typeNull) ::AEDisposeDesc(&valueDesc);
	if (propDesc.descriptorType != typeNull) ::AEDisposeDesc(&propDesc);
	
	return (LModelObject*) rezObj;
}


