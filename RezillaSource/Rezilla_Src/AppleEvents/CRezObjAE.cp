// ===========================================================================
// CRezObjAE.cp
// 
//                       Created: 2005-04-09 10:03:39
//             Last modification: 2005-04-09 10:03:58
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
#include "UResources.h"
#include "RezillaConstants.h"

#include <LCommander.h>



// ---------------------------------------------------------------------------
//	¥ GetAEProperty
// ---------------------------------------------------------------------------
//	Return a descriptor for the specified Property
//  rzil_pResID			= pID;			// ID ('ID  ')			 
//  rzil_pName			= pName;		// Name ('pnam')
//  rzil_pType			= 'pTYP';		// Type
//  rzil_pSpecifier		= 'pSPE';		// Specifier (type,ID)
//  rzil_pSysHeap		= 'pSHP';		// resSysHeap
//  rzil_pPurgeable		= 'pPUR';		// resPurgeable
//  rzil_pLocked		= 'pLOC';		// resLocked
//  rzil_pProtected		= 'pPRO';		// resProtected
//  rzil_pPreload		= 'pPRE';		// resPreload
//  rzil_pChanged		= pIsModified;	// resChanged ('imod')
//  rzil_pDataSize		= 'pSIZ';		// Size of the data
//  rzil_pSizeOnDisk	= 'pDSZ';		// Size on disk
//  rzil_pData			= pContents;	// Data ('pcnt', was 'pDAT')

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

		case rzil_pType: 
		error = ::AECreateDesc(typeType, &mType,
							 sizeof(ResType), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;

		case rzil_pResID:
		error = ::AECreateDesc(typeSInt16, (Ptr) &mID,
									sizeof(short), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
		
		case rzil_pAttributes:
		short const	theAttrs = GetAttributes();
		error = ::AECreateDesc(typeSInt16, (Ptr) &theAttrs,
									sizeof(short), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
		
		case rzil_pSysHeap:
		GetAERezObjAttribute(resSysHeap, outPropertyDesc);
		break;
		
		case rzil_pPurgeable:
		GetAERezObjAttribute(resPurgeable, outPropertyDesc);
		break;
		
		case rzil_pLocked:
		GetAERezObjAttribute(resLocked, outPropertyDesc);
		break;
		
		case rzil_pProtected:
		GetAERezObjAttribute(resProtected, outPropertyDesc);
		break;
		
		case rzil_pPreload:
		GetAERezObjAttribute(resPreload, outPropertyDesc);
		break;
		
		case rzil_pChanged:
		GetAERezObjAttribute(resChanged, outPropertyDesc);
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
	switch (inProperty) {

		case pName: {
			Str255	theName;
			UExtractFromAEDesc::ThePString(inValue, theName, sizeof(theName));
// 			SetDescriptor(theName);
			break;
		}

		case rzil_pResID: {
			short		theID;
			UExtractFromAEDesc::TheSInt16(inValue, theID);
// 			SetID(theID);
			break;
		}
		
		case rzil_pAttributes: {
			short	theAttrs;
			UExtractFromAEDesc::TheSInt16(inValue, theAttrs);
// 			SetAttributesInMap(theAttrs);
			break;
		}
		
		case rzil_pSysHeap:
		SetAERezObjAttribute(inValue, resSysHeap);
		break;
		
		case rzil_pPurgeable:
		SetAERezObjAttribute(inValue, resPurgeable);
		break;
		
		case rzil_pLocked:
		SetAERezObjAttribute(inValue, resLocked);
		break;
		
		case rzil_pProtected:
		SetAERezObjAttribute(inValue, resProtected);
		break;
		
		case rzil_pPreload:
		SetAERezObjAttribute(inValue, resPreload);
		break;
		
		case rzil_pChanged:
		SetAERezObjAttribute(inValue, resChanged);
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
		case rzil_pAttributes:
		case rzil_pChanged:
		case rzil_pLocked:
		case rzil_pPreload:
		case rzil_pProtected:
		case rzil_pPurgeable:
		case rzil_pResID:
		case rzil_pSysHeap:
		case rzil_pType: 
			exists = true;
			break;

		default:
			exists = LModelObject::AEPropertyExists(inProperty);
			break;
	}

	return exists;
}







