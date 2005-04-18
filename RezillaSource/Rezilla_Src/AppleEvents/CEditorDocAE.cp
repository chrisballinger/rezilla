// ===========================================================================
// CRezObjAE.cp
// 
//                       Created: 2005-04-09 10:03:39
//             Last modification: 2005-04-17 15:58:50
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
//	rzom_pReadOnly		= 'pRDO';	// mapReadOnly
// 	rzom_cRezObj		= 'cRSC';	// RezObj
// 	rzom_pKind			= 'pKND';	// Kind
// 	rzom_pOwnerMapDoc	= 'pOWM';	// Document's owner rezmap doc
// 	rzom_cRezMapDoc		= 'MapD';	// RezMap document
//  pIndex				= 'pidx';
//  cWindow				= 'cwin';

void
CRezObj::GetAEProperty(
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
			// Return the index of this document among the other rezmap docs
			SInt32		position = 0;
			LDocument *	theDoc = nil;
			Boolean found = false;
			
			TArrayIterator<LDocument*> iterator( LDocument::GetDocumentList() );
			while (iterator.Next(theDoc)) {
				if (theDoc->GetModelKind() == rzom_cRezMapDoc) {
					position++;
					if (theDoc == this) {
						found = true;
						break;
					} 
				} 				
				theDoc = nil;
			}
			if (found) {
				error = ::AECreateDesc(typeSInt32, (Ptr) &position,
											sizeof(SInt32), &outPropertyDesc);
			} else {
				error = errAENoSuchObject;
			}
			ThrowIfOSErr_(error);
			break;
		}
		
		
		case 'cwin': {
			// Returns the window by index (in stack order)
			AEDesc superSpec;
			superSpec.descriptorType = typeNull;
			superSpec.dataHandle = nil;
			StAEDescriptor	keyData;
			SInt32	index = UWindows::FindWindowIndex( mRezMapWindow->GetMacWindow() );

			keyData.Assign(index);
			error = ::CreateObjSpecifier( cWindow, &superSpec, formAbsolutePosition,
									keyData, false, &outPropertyDesc);
			ThrowIfOSErr_(error);
			break;
		}
		
		
		case rzom_pRefNum:
		short		theRefNum = mRezMap->GetRefnum();
		error = ::AECreateDesc(typeSInt16, (Ptr) &theRefNum,
									sizeof(short), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
		

		case rzom_pKind:
		ResType	theType = rzom_eIsUnknownFork;
		if (mFork == fork_rezfork) {
			theType = rzom_eIsRsrcFork;
		} else if (mFork == fork_datafork) {
			theType = rzom_eIsDataFork;
		} 
		error = ::AECreateDesc(typeEnumerated, (Ptr) &theType,
									sizeof(ResType), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
		
		
		case rzom_cRezMapDoc:
		case rzom_pOwnerMapDoc:  {
			// Returns the map described by its refnum
			AEDesc superSpec;
			superSpec.descriptorType = typeNull;
			superSpec.dataHandle = nil;
			StAEDescriptor	keyData;
			keyData.Assign(mRezMap->GetRefnum());
			error = ::CreateObjSpecifier( rzom_cRezMap, &superSpec, formUniqueID,
									keyData, false, &outPropertyDesc);
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
//	¥ SetAEProperty
// ---------------------------------------------------------------------------
// All the RezMapDoc properties are readOnly

void
CRezObj::SetAEProperty(
	DescType		inProperty,
	const AEDesc&	inValue,
	AEDesc&			outAEReply)
{
	switch (inProperty) {
		
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
// CRezObj::GetAERezObjAttribute(
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
// CRezObj::SetAERezObjAttribute(const AEDesc& inValue, short inFlag)
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

		case pIndex:
		case rzom_pKind:
		case rzom_pReadOnly:
		case cWindow:
		case rzom_cRezObj:
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







