// ===========================================================================
// CRezMapAE.cp					
// 
//                       Created: 2004-11-30 08:50:37
//             Last modification: 2005-04-09 11:43:57
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
//  AppleEvent Object Model Support. These methods are part of the CRezMap 
//  class (inheriting from LModelObject).

#include "CRezMap.h"
#include "CRezObj.h"
#include "UResources.h"
#include "RezillaConstants.h"

#include <LCommander.h>


// ---------------------------------------------------------------------------
//	¥ MakeSelfSpecifier
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
		err = ::CreateObjSpecifier(rzil_cMap, &inSuperSpecifier, formPropertyID,
										keyData, false, &outSelfSpecifier);
		ThrowIfOSErr_(err);

	} else {
		LModelObject::MakeSelfSpecifier(inSuperSpecifier, outSelfSpecifier);
	}
}



// ---------------------------------------------------------------------------
//	¥ GetAEProperty
// ---------------------------------------------------------------------------
//	Return a descriptor for the specified Property
// rzil_pRefNum			= 'pRFN';		// RefNum
// rzil_pAttributes		= 'pATR';		// Attributes
// rzil_pReadOnly		= 'pRDO';		// mapReadOnly
// rzil_pCompact		= 'pCPT';		// mapCompact
// rzil_pChanged		= pIsModified;	// mapChanged/resChanged ('imod')

void
CRezMap::GetAEProperty(
	DescType		inProperty,
	const AEDesc&	inRequestedType,
	AEDesc&			outPropertyDesc) const
{
	OSErr		error = noErr;
	
	switch (inProperty) {
		
		case rzil_pRefNum:
		error = ::AECreateDesc(typeSInt16, (Ptr) &mRefNum,
									sizeof(short), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
		
		case rzil_pAttributes:
		short		theAttrs;
		GetMapAttributes(theAttrs);
		error = ::AECreateDesc(typeSInt16, (Ptr) &theAttrs,
									sizeof(short), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
		
		case rzil_pReadOnly:
		GetAERezMapAttribute(mapReadOnly, outPropertyDesc);
		break;
		
		case rzil_pCompact:
		GetAERezMapAttribute(mapCompact, outPropertyDesc);
		break;
		
		case rzil_pChanged:
		GetAERezMapAttribute(mapChanged, outPropertyDesc);
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
CRezMap::SetAEProperty(
	DescType		inProperty,
	const AEDesc&	inValue,
	AEDesc&			outAEReply)
{
	switch (inProperty) {

		case rzil_pAttributes:
		short		theAttrs;
		UExtractFromAEDesc::TheSInt16(inValue, theAttrs);
		SetMapAttributes(theAttrs);
		break;
		
		case rzil_pReadOnly:
		SetAERezMapAttribute(inValue, mapReadOnly);
		break;
		
		case rzil_pCompact:
		SetAERezMapAttribute(inValue, mapCompact);
		break;
		
		case rzil_pChanged:
		SetAERezMapAttribute(inValue, mapChanged);
		break;

		default:
			LModelObject::SetAEProperty(inProperty, inValue, outAEReply);
			break;
	}
}


// // ---------------------------------------------------------------------------
// //	¥ SetAEProperty
// // ---------------------------------------------------------------------------
// 
// void
// CRezMap::SetAEProperty(
// 	DescType		inProperty,
// 	const AEDesc&	inValue,
// 	AEDesc&			outAEReply)
// {
// 	switch (inProperty) {
// 
// 		case pName: {
// 			Str255	theName;
// 			UExtractFromAEDesc::ThePString(inValue, theName, sizeof(theName));
// 			SetDescriptor(theName);
// 			break;
// 		}
// 
// 		case pWindowPosition: {
// 			Point	thePosition;
// 			UExtractFromAEDesc::ThePoint(inValue, thePosition);
// 			DoSetPosition(thePosition);
// 			break;
// 		}
// 
// 		case pBounds: {
// 			Rect	theBounds;
// 			UExtractFromAEDesc::TheRect(inValue, theBounds);
// 			DoSetBounds(theBounds);
// 			break;
// 		}
// 
// 		case pIsZoomed: {
// 			Boolean	isZoomed;
// 			UExtractFromAEDesc::TheBoolean(inValue, isZoomed);
// 			DoSetZoom(isZoomed);
// 			break;
// 		}
// 
// 		case pVisible: {
// 			Boolean	makeVisible;
// 			UExtractFromAEDesc::TheBoolean(inValue, makeVisible);
// 			if (makeVisible) {
// 				Show();
// 			} else {
// 				Hide();
// 			}
// 			break;
// 		}
// 
// 		default:
// 			LModelObject::SetAEProperty(inProperty, inValue, outAEReply);
// 			break;
// 	}
// }


// ---------------------------------------------------------------------------
//	¥ GetAERezMapAttribute
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
//	¥ SetAERezMapAttribute
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
//	¥ AEPropertyExists
// ---------------------------------------------------------------------------

bool
CRezMap::AEPropertyExists(
	DescType	inProperty) const
{
	bool	exists = false;

	switch (inProperty) {

		case rzil_pAttributes:
		case rzil_pChanged:
		case rzil_pCompact:
		case rzil_pReadOnly:
		case rzil_pRefNum:
			exists = true;
			break;

		default:
			exists = LModelObject::AEPropertyExists(inProperty);
			break;
	}

	return exists;
}







