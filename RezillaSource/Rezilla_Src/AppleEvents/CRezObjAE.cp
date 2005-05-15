// ===========================================================================
// CRezObjAE.cp
// 
//                       Created: 2005-04-09 10:03:39
//             Last modification: 2005-05-14 07:08:30
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
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
//  rzom_pSysHeap		= 'pSHP';		// resSysHeap
//  rzom_pPurgeable		= 'pPUR';		// resPurgeable
//  rzom_pLocked		= 'pLOC';		// resLocked
//  rzom_pProtected		= 'pPRO';		// resProtected
//  rzom_pPreload		= 'pPRE';		// resPreload
//  rzom_pChanged		= pIsModified;	// resChanged ('imod')
//  rzom_pDataSize		= 'pSIZ';		// Size of the data
//  rzom_pSizeOnDisk	= 'pDSZ';		// Size on disk
//  rzom_pData			= pContents;	// Data ('pcnt', was 'pDAT')

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
		case rzom_cRezType: 
		Str255 name;
		UMiscUtils::OSTypeToPString(mType, name);
		error = ::AECreateDesc(typeChar, (Ptr) name + 1,
							StrLength(name), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;

		
		case rzom_pResID:
		error = ::AECreateDesc(typeSInt16, (Ptr) &mID,
									sizeof(short), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
		
		
		case pIndex:
		SInt32 position = 0;
		error = GetIndexInType(position);
		if (error == noErr) {
			error = ::AECreateDesc(typeSInt32, (Ptr) &position,
										sizeof(SInt32), &outPropertyDesc);	
		} 
		ThrowIfOSErr_(error);
		break;
		

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
		
		
		case rzom_pAttributes:
		short const	theAttrs = GetAttributes();
		error = ::AECreateDesc(typeSInt16, (Ptr) &theAttrs,
									sizeof(short), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
		

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
		
		
		case pContents: {
			StByteToHexTranslator translator(mData);
			translator.Convert();
			error = ::AECreateDesc(typeChar, (Ptr) *(translator.GetOutHandle()),
								 translator.GetOutSize(), &outPropertyDesc);
			ThrowIfOSErr_(error);
			break;
		}
		
		
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
	switch (inProperty) {

		case pName: {
			Str255	theName;
			UExtractFromAEDesc::ThePString(inValue, theName, sizeof(theName));
// 			SetDescriptor(theName);
			break;
		}

		case rzom_pResID: {
			short		theID;
			UExtractFromAEDesc::TheSInt16(inValue, theID);
// 			SetID(theID);
			break;
		}
		
		case rzom_pAttributes: {
			short	theAttrs;
			UExtractFromAEDesc::TheSInt16(inValue, theAttrs);
// 			SetAttributesInMap(theAttrs);
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
		
		case pContents: {
// 			StByteToHexTranslator translator(mData);
// 			translator.Convert();
// 			error = ::AECreateDesc(typeChar, (Ptr) *(translator.GetOutHandle()),
// 								 translator.GetOutSize(), &outPropertyDesc);
// 			ThrowIfOSErr_(error);
			break;
		}
		
		
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
	short		theAttrs;
	Boolean		setIt;
	
	UExtractFromAEDesc::TheBoolean(inValue, setIt);
	GetAttributesFromMap(theAttrs);

	if (setIt) {
		theAttrs &= inFlag;
	} else {
		theAttrs &= ~inFlag;
	}
	SetAttributesInMap(theAttrs);
}


// // ---------------------------------------------------------------------------
// //	¥ GetModelName
// // ---------------------------------------------------------------------------
// //	Return the name of a Window as an AppleEvent model object
// 
// StringPtr
// CRezObj::GetModelName(
// 	Str255	outModelName) const
// {
// 	return GetDescriptor(outModelName);
// }


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
		case rzom_pData:
		case rzom_pAttributes:
		case rzom_pChanged:
		case rzom_pLocked:
		case rzom_pPreload:
		case rzom_pProtected:
		case rzom_pPurgeable:
		case rzom_pSysHeap:
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
		case ae_Clone:
		case ae_Delete:
		CRezType * theRezType = dynamic_cast<CRezType*>(mSuperModel);
		if (theRezType != nil) {
			theRezType->HandleResourceEvent(inAppleEvent, outAEReply, outResult, this, inAENumber);	
		} 
		break;
		
		
		case aeRzil_Inspect:
		CRezillaApp::sInspectorWindow->InstallValues(this);
		break;
		
		
		default:
		// 		mSuperModel->HandleAppleEvent(inAppleEvent, outAEReply, outResult, inAENumber);
		LModelObject::HandleAppleEvent(inAppleEvent, outAEReply, outResult, inAENumber);
		break;
	}
}







