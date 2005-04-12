// ===========================================================================
// CRezMapDocAE.cp
// 
//                       Created: 2005-04-09 10:03:39
//             Last modification: 2005-04-12 14:18:47
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
//  AppleEvent Object Model Support. These methods are part of the CRezMapDoc 
//  class (inheriting from LModelObject).

#include "CRezMap.h"
#include "CRezMapDoc.h"
#include "UResources.h"
#include "RezillaConstants.h"

#include <LCommander.h>



// ---------------------------------------------------------------------------
//	¥ GetAEProperty
// ---------------------------------------------------------------------------
//	Return a descriptor for the specified Property
// 	rzom_pRezMap		= 'pMAP';	// RezMap
// 	rzom_pRefNum		= 'pRFN';	// RefNum
// 	rzom_pRezFork		= 'pFRK';	// ResFork
// 	rzom_pRezFile		= 'pFIL';	// ResFile

void
CRezMapDoc::GetAEProperty(
	DescType		inProperty,
	const AEDesc&	inRequestedType,
	AEDesc&			outPropertyDesc) const
{
	OSErr	error = noErr;
	
	switch (inProperty) {
		
		case rzom_pRezMap: 
// 		error = ::AECreateDesc(typeChar, (Ptr) mName + 1,
// 							StrLength(mName), &outPropertyDesc);
// 		ThrowIfOSErr_(error);
		break;

		case rzom_pRefNum:
// 		error = ::AECreateDesc(typeSInt16, (Ptr) &mID,
// 									sizeof(short), &outPropertyDesc);
// 		ThrowIfOSErr_(error);
		break;
		
		case rzom_pRezFork:
// 		short const	theAttrs = GetAttributes();
// 		error = ::AECreateDesc(typeSInt16, (Ptr) &theAttrs,
// 									sizeof(short), &outPropertyDesc);
// 		ThrowIfOSErr_(error);
		break;
		
		case rzom_pRezFile:
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
CRezMapDoc::SetAEProperty(
	DescType		inProperty,
	const AEDesc&	inValue,
	AEDesc&			outAEReply)
{
	switch (inProperty) {

		case rzom_pRezMap: {
// 			Str255	theName;
// 			UExtractFromAEDesc::ThePString(inValue, theName, sizeof(theName));
// // 			SetDescriptor(theName);
			break;
		}

		case rzom_pRefNum: {
// 			short		theID;
// 			UExtractFromAEDesc::TheSInt16(inValue, theID);
// // 			SetID(theID);
			break;
		}
		
		case rzom_pRezFork: {
// 			short	theAttrs;
// 			UExtractFromAEDesc::TheSInt16(inValue, theAttrs);
// // 			SetAttributesInMap(theAttrs);
			break;
		}
		
		case rzom_pRezFile:
		break;
				
		default:
			LModelObject::SetAEProperty(inProperty, inValue, outAEReply);
			break;
	}
}


// // ---------------------------------------------------------------------------
// //	¥ GetAERezObjAttribute
// // ---------------------------------------------------------------------------
// 
// void
// CRezMapDoc::GetAERezObjAttribute(
// 	short		inFlag,
// 	AEDesc&		outPropertyDesc) const
// {
// 	Boolean attrIsSet = HasAttribute(inFlag);
// 	
// 	OSErr error = ::AECreateDesc(typeBoolean, (Ptr) &attrIsSet,
// 								sizeof(Boolean), &outPropertyDesc);
// 	ThrowIfOSErr_(error);
// }
// 
// 
// // ---------------------------------------------------------------------------
// //	¥ SetAERezObjAttribute
// // ---------------------------------------------------------------------------
// 
// void
// CRezMapDoc::SetAERezObjAttribute(const AEDesc& inValue, short inFlag)
// {
// 	short		theAttrs;
// 	Boolean		setIt;
// 	
// 	UExtractFromAEDesc::TheBoolean(inValue, setIt);
// 	GetAttributesFromMap(theAttrs);
// 
// 	if (setIt) {
// 		theAttrs &= inFlag;
// 	} else {
// 		theAttrs &= ~inFlag;
// 	}
// 	SetAttributesInMap(theAttrs);
// }


// // ---------------------------------------------------------------------------
// //	¥ GetModelName
// // ---------------------------------------------------------------------------
// //	Return the name of a Window as an AppleEvent model object
// 
// StringPtr
// CRezMapDoc::GetModelName(
// 	Str255	outModelName) const
// {
// 	return GetDescriptor(outModelName);
// }


// ---------------------------------------------------------------------------
//	¥ AEPropertyExists
// ---------------------------------------------------------------------------

bool
CRezMapDoc::AEPropertyExists(
	DescType	inProperty) const
{
	bool	exists = false;

	switch (inProperty) {

		case rzom_pRefNum:
		case rzom_pRezFile:
		case rzom_pRezFork:
		case rzom_pRezMap: 
			exists = true;
			break;

		default:
			exists = LModelObject::AEPropertyExists(inProperty);
			break;
	}

	return exists;
}







