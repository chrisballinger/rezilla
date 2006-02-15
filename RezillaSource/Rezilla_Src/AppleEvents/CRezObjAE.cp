// ===========================================================================
// CRezObjAE.cp
// 
//                       Created: 2005-04-09 10:03:39
//             Last modification: 2005-06-05 09:17:42
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// ===========================================================================
//  AppleEvent Object Model Support. These methods are part of the CRezObj 
//  class (inheriting from LModelObject).

#include "CRezMap.h"
#include "CRezObj.h"
#include "CRezType.h"
#include "CRezillaApp.h"
#include "CInspectorWindow.h"
#include "UResources.h"
#include "UMiscUtils.h"
#include "UCodeTranslator.h"
#include "RezillaConstants.h"

#include <LCommander.h>


// ---------------------------------------------------------------------------
//	¥ MakeSelfSpecifier												  [public]
// ---------------------------------------------------------------------------

void
CRezObj::MakeSelfSpecifier(
	AEDesc	&inSuperSpecifier,
	AEDesc	&outSelfSpecifier) const
{
		StAEDescriptor	keyData;
		OSErr			err;

		// Specify by the ID property
		keyData.Assign(mID);

		err = ::CreateObjSpecifier(rzom_cRezObj, &inSuperSpecifier, formUniqueID,
										keyData, false, &outSelfSpecifier);
		ThrowIfOSErr_(err);
}


// ---------------------------------------------------------------------------
//	¥ GetAEProperty
// ---------------------------------------------------------------------------
//	Return a descriptor for the specified Property
//  rzom_pResID			= pID;			// ID ('ID  ')			 
//  rzom_pName			= pName;		// Name ('pnam')
//  rzom_pType			= 'pTYP';		// Type
//  rzom_pSpecifier		= 'pSPE';		// Specifier (type,ID)
//  rzom_pAttributes	= 'pATR';		// Attributes
//  rzom_pSysHeap		= 'pSHP';		// resSysHeap
//  rzom_pPurgeable		= 'pPUR';		// resPurgeable
//  rzom_pLocked		= 'pLOC';		// resLocked
//  rzom_pProtected		= 'pPRO';		// resProtected
//  rzom_pPreload		= 'pPRE';		// resPreload
//  rzom_pChanged		= pIsModified;	// resChanged ('imod')
//  rzom_pDataSize		= 'pSIZ';		// Size of the data
//  rzom_pSizeOnDisk	= 'pDSZ';		// Size on disk
//  rzom_pData			= 'pDAT';		// Data

void
CRezObj::GetAEProperty(
	DescType		inProperty,
	const AEDesc&	inRequestedType,
	AEDesc&			outPropertyDesc) const
{
	OSErr	error = noErr;
	
	switch (inProperty) {
		
		case pName: 
		error = ::AECreateDesc(typeChar, (Ptr) mName + 1,
							StrLength(mName), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
		

		case rzom_pType: 
		case rzom_cRezType: {
			Str255 name;
			UMiscUtils::OSTypeToPString(mType, name);
			error = ::AECreateDesc(typeChar, (Ptr) name + 1,
								StrLength(name), &outPropertyDesc);
			ThrowIfOSErr_(error);
			break;
		}

		
		case rzom_pResID:
		error = ::AECreateDesc(typeSInt16, (Ptr) &mID,
									sizeof(short), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
		
		
		case pIndex: {
		SInt32 position = 0;
		error = GetIndexInType(position);
		if (error == noErr) {
			error = ::AECreateDesc(typeSInt32, (Ptr) &position,
										sizeof(SInt32), &outPropertyDesc);	
		} 
		ThrowIfOSErr_(error);
		break;
		}

		case rzom_pSpecifier: {
			Str255 name;
			if (outPropertyDesc.descriptorType == typeNull) {
				error = ::AECreateList(nil, 0, false, &outPropertyDesc);
				ThrowIfOSErr_(error);
			}
			UMiscUtils::OSTypeToPString(mType, name);
			error = ::AEPutPtr(&outPropertyDesc, 1, typeChar, (Ptr) name + 1, StrLength(name));
			ThrowIfOSErr_(error);
			error = ::AEPutPtr(&outPropertyDesc, 2, typeSInt16, (Ptr) &mID, sizeof(SInt16));
			ThrowIfOSErr_(error);
			break;
		}
		
			
		case rzom_pDataSize: 
		error = ::AECreateDesc(typeSInt32, (Ptr) &mSize,
									sizeof(SInt32), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
		
		
		case rzom_pSizeOnDisk: {
			SInt32 theSize = 0;
			GetSizeOnDisk(theSize);
			error = ::AECreateDesc(typeSInt32, (Ptr) &theSize,
										sizeof(SInt32), &outPropertyDesc);
			ThrowIfOSErr_(error);
			break;
		}
		
		
		case rzom_pAttributes: {
			short const	theAttrs = GetAttributes();
			error = ::AECreateDesc(typeSInt16, (Ptr) &theAttrs,
										sizeof(short), &outPropertyDesc);
			ThrowIfOSErr_(error);
			break;
		}
		
		case rzom_pSysHeap:
		GetAERezObjAttribute(resSysHeap, outPropertyDesc);
		break;
		
		
		case rzom_pPurgeable:
		GetAERezObjAttribute(resPurgeable, outPropertyDesc);
		break;
		
		
		case rzom_pLocked:
		GetAERezObjAttribute(resLocked, outPropertyDesc);
		break;
		
		
		case rzom_pProtected:
		GetAERezObjAttribute(resProtected, outPropertyDesc);
		break;
		
		
		case rzom_pPreload:
		GetAERezObjAttribute(resPreload, outPropertyDesc);
		break;
		
		
		case rzom_pChanged:
		GetAERezObjAttribute(resChanged, outPropertyDesc);
		break;
		
		
		case rzom_pData: 
		GetAEResourceData(outPropertyDesc);
		break;
		
		
		default:
		LModelObject::GetAEProperty(inProperty, inRequestedType,
									outPropertyDesc);
		break;
	}
}


// ---------------------------------------------------------------------------
//	¥ SetAEProperty
// ---------------------------------------------------------------------------

void
CRezObj::SetAEProperty(
	DescType		inProperty,
	const AEDesc&	inValue,
	AEDesc&			outAEReply)
{
	OSErr error;
	
	switch (inProperty) {

		case pName: {
			Str255	theName;
			UExtractFromAEDesc::ThePString(inValue, theName, sizeof(theName));
			SetName(&theName);
			break;
		}

		case rzom_pAttributes: {
			short	theAttrs;
			UExtractFromAEDesc::TheSInt16(inValue, theAttrs);
			SetAttributesInMap(theAttrs);
			break;
		}
		
		case rzom_pSysHeap:
		SetAERezObjAttribute(inValue, resSysHeap);
		break;
		
		case rzom_pPurgeable:
		SetAERezObjAttribute(inValue, resPurgeable);
		break;
		
		case rzom_pLocked:
		SetAERezObjAttribute(inValue, resLocked);
		break;
		
		case rzom_pProtected:
		SetAERezObjAttribute(inValue, resProtected);
		break;
		
		case rzom_pPreload:
		SetAERezObjAttribute(inValue, resPreload);
		break;
		
		case rzom_pChanged:
		SetAERezObjAttribute(inValue, resChanged);
		break;
		
		// (2005-06-11) Disabled this. It is useful only with the
		// ReadPartialResource and WritePartialResource functions which are
		// not supported in Rezilla.
// 		case rzom_pSizeOnDisk: {
// 			UInt32		theSize;
// 			UExtractFromAEDesc::TheUInt32(inValue, theSize);
// 			error = SetSizeOnDisk(theSize);
// 			ThrowIfOSErr_(error);
// 			break;
// 		}
		
		case rzom_pData:
		SetAEResourceData(inValue);
		break;		
		
		default:
			LModelObject::SetAEProperty(inProperty, inValue, outAEReply);
			break;
	}
}


// ---------------------------------------------------------------------------
//	¥ GetAERezObjAttribute
// ---------------------------------------------------------------------------

void
CRezObj::GetAERezObjAttribute(
	short		inFlag,
	AEDesc&		outPropertyDesc) const
{
	Boolean attrIsSet = HasAttribute(inFlag);
	
	OSErr error = ::AECreateDesc(typeBoolean, (Ptr) &attrIsSet,
								sizeof(Boolean), &outPropertyDesc);
	ThrowIfOSErr_(error);
}


// ---------------------------------------------------------------------------
//	¥ SetAERezObjAttribute
// ---------------------------------------------------------------------------

void
CRezObj::SetAERezObjAttribute(const AEDesc& inValue, short inFlag)
{
	short	theAttrs;
	Boolean	setIt;
	
	UExtractFromAEDesc::TheBoolean(inValue, setIt);
	GetAttributesFromMap(theAttrs);

	if (setIt) {
		theAttrs |= inFlag;
	} else {
		theAttrs &= ~inFlag;
	}
	SetAttributesInMap(theAttrs);
}


// ---------------------------------------------------------------------------
//	¥ GetAEResourceData
// ---------------------------------------------------------------------------
// The data are specified in hexadecimal notation unless it is a TEXT or a
// STR# resource, in which case the text of the resource is returned directly
// (as a single string or a list of strings respectively).

void
CRezObj::GetAEResourceData(AEDesc& outPropertyDesc) const
{
	OSErr error;
	
	if (mType == 'TEXT') {
		error = ::AECreateDesc(typeChar, (Ptr) *mData, mSize, &outPropertyDesc);
	} else if (mType == 'STR#') {
		LHandleStream * theStream = new LHandleStream(mData);
		if ( theStream->GetLength() == 0 ) {
			return;
		} 
		
		UInt16	count, index;
		Str255	theString;

		error = ::AECreateList(NULL, 0, false, &outPropertyDesc);
		ThrowIfOSErr_(error);
		
		*theStream >> count;
		
		for (index = 1; index <= count && error == noErr; index++) {
			*theStream >> theString;
			
			StAEDescriptor	keyData;
			error = ::AECreateDesc(typeChar, theString + 1, theString[0], &keyData.mDesc);
			error = ::AEPutDesc(&outPropertyDesc, index, &keyData.mDesc);
		}
		
		theStream->DetachDataHandle();
		delete theStream;
	} else {
		StByteToHexTranslator hexTranslator(mData);
		hexTranslator.Convert();
		error = ::AECreateDesc(typeChar, (Ptr) *(hexTranslator.GetOutHandle()),
							   hexTranslator.GetOutSize(), &outPropertyDesc);
	}
	ThrowIfOSErr_(error);
}


// ---------------------------------------------------------------------------
//	¥ SetAEResourceData
// ---------------------------------------------------------------------------
// The data are specified in hexadecimal notation unless it is a TEXT or a
// STR# resource, in which case the text of the resource is passed directly
// (as a single string or a list of strings respectively).

void
CRezObj::SetAEResourceData(const AEDesc& inValue)
{
	OSErr	error;
	
	if (mType == 'STR#') {
		SInt32		numStrings;
		UInt16		count, index;
		Str255		theString;
		char		buffer[256];
		AEKeyword	theKey;
		Size		actualSize;
		DescType	returnedType;
		
		error = ::AECountItems(&inValue, &numStrings);  // Check typeAEList ?
		ThrowIfOSErr_(error);
		count = numStrings;
		
		LHandleStream * theStream = new LHandleStream();
		ThrowIfNil_(theStream);
		
		*theStream << count;
		
		for (index = 1; index <= count; index++) {
			error = ::AEGetNthPtr(&inValue, index, typeChar, &theKey, &returnedType, 
							 (Ptr) buffer, 255, &actualSize);
			ThrowIfOSErr_(error);
			buffer[actualSize] = 0;
			CopyCStringToPascal(buffer, theString);				 
			*theStream << theString;
		}
		SetData( theStream->GetDataHandle() );
		delete theStream;		
	} else {
		Size	theSize = ::AEGetDescDataSize(&inValue);
		Handle	dataH = NewHandle(theSize);
		 
		if (dataH != nil) {
			error = ::AEGetDescData(&inValue, *dataH, theSize);
			ThrowIfOSErr_(error);
			if (mType == 'TEXT') {
				SetData( dataH );
			} else  {
				StHexToByteTranslator translator(dataH);
				translator.Convert();
				SetData( translator.GetOutHandle() );
			}
			::DisposeHandle(dataH);
		} 
	}
}


// ---------------------------------------------------------------------------
//	¥ AEPropertyExists
// ---------------------------------------------------------------------------

bool
CRezObj::AEPropertyExists(
	DescType	inProperty) const
{
	bool	exists = false;

	switch (inProperty) {

		case pName: 
		case pIndex:
		case rzom_pResID:
		case rzom_pType: 
		case rzom_pDataSize:
		case rzom_pSizeOnDisk:
		case rzom_pAttributes:
		case rzom_pChanged:
		case rzom_pLocked:
		case rzom_pPreload:
		case rzom_pProtected:
		case rzom_pPurgeable:
		case rzom_pSysHeap:
		case rzom_pData:
			exists = true;
			break;

		default:
			exists = LModelObject::AEPropertyExists(inProperty);
			break;
	}

	return exists;
}


// ---------------------------------------------------------------------------
//	¥ HandleAppleEvent												  [public]
// ---------------------------------------------------------------------------

void
CRezObj::HandleAppleEvent(
	const AppleEvent&	inAppleEvent,
	AppleEvent&			outAEReply,
	AEDesc&				outResult,
	long				inAENumber)
{	
	switch (inAENumber) {
		
		case aeRzil_Edit:
		case aeRzil_Inspect:
		case ae_Clone:
		case ae_Delete: {
			// Pass up to the owner CRezType
			CRezType * theRezType = dynamic_cast<CRezType*>(mSuperModel);
			if (theRezType != nil) {
				theRezType->HandleResourceEvent(inAppleEvent, outAEReply, outResult, this, inAENumber);	
			} 
			break;
		}
				
		case ae_GetDataSize: {
			SInt32 theLong = mSize;
			::AEPutParamPtr(&outAEReply, keyAEResult, typeSInt32, &theLong, sizeof(SInt32));
			break;
		}
				
		default:
		// 		mSuperModel->HandleAppleEvent(inAppleEvent, outAEReply, outResult, inAENumber);
		LModelObject::HandleAppleEvent(inAppleEvent, outAEReply, outResult, inAENumber);
		break;
	}
}





