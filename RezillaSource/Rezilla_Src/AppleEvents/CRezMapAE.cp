// ===========================================================================
// CRezMapAE.cp					
// 
//                       Created: 2004-11-30 08:50:37
//             Last modification: 2004-11-29 06:25:11
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
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


// // ---------------------------------------------------------------------------
// //	¥ MakeSelfSpecifier
// // ---------------------------------------------------------------------------
// //	Make an Object Specifier for a Window
// 
// void
// CRezMap::MakeSelfSpecifier(
// 	AEDesc&	inSuperSpecifier,
// 	AEDesc&	outSelfSpecifier) const
// {
// 	if (mSuperModel == nil) {
// 
// 			// For Windows, we often use an "abbreviated" container
// 			// hierarchy where the SuperModel of a Window is null
// 			// rather than being the Application.
// 
// 		DescType		keyForm;
// 		StAEDescriptor	keyData;
// 		OSErr			err;
// 
// 			// Specify by name if the Window's model object name
// 			// is not empty
// 
// 		Str255	name;
// 		GetModelName(name);
// 
// 		if (name[0] != 0) {
// 			keyForm = formName;
// 			keyData.Assign(name);
// 
// 		} else {			// Specify by position in the window list
// 
// 			SInt32	windowIndex = UWindows::FindWindowIndex(mMacWindowP);
// 
// 			keyForm = formAbsolutePosition;
// 			keyData.Assign(windowIndex);
// 		}
// 
// 		err = ::CreateObjSpecifier(	cWindow,
// 									&inSuperSpecifier,
// 									keyForm,
// 									keyData,
// 									false,		// Don't dispose inputs
// 									&outSelfSpecifier);
// 		ThrowIfOSErr_(err);
// 
// 	} else {
// 		LModelObject::MakeSelfSpecifier(inSuperSpecifier, outSelfSpecifier);
// 	}
// }



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
	short		inAttribute,
	AEDesc&		outPropertyDesc) const
{
	Boolean		attrIsSet;
	short		theAttrs;
	OSErr		error;
	
	GetMapAttributes(theAttrs);
	attrIsSet = ((theAttrs & inAttribute) > 0);
	
	error = ::AECreateDesc(typeBoolean, (Ptr) &attrIsSet,
								sizeof(Boolean), &outPropertyDesc);
	ThrowIfOSErr_(error);
}


// // ---------------------------------------------------------------------------
// //	¥ GetModelName
// // ---------------------------------------------------------------------------
// //	Return the name of a Window as an AppleEvent model object
// 
// StringPtr
// CRezMap::GetModelName(
// 	Str255	outModelName) const
// {
// 	return GetDescriptor(outModelName);
// }


// // ---------------------------------------------------------------------------
// //	¥ AEPropertyExists
// // ---------------------------------------------------------------------------
// 
// bool
// CRezMap::AEPropertyExists(
// 	DescType	inProperty) const
// {
// 	bool	exists = false;
// 
// 	switch (inProperty) {
// 
// 		case pName:
// 		case pWindowPosition:
// 		case pBounds:
// 		case pIndex:
// 		case pIsZoomed:
// 		case pHasCloseBox:
// 		case pHasTitleBar:
// 		case pIsFloating:
// 		case pIsModal:
// 		case pIsResizable:
// 		case pIsZoomable:
// 		case pVisible:
// 			exists = true;
// 			break;
// 
// 		default:
// 			exists = LModelObject::AEPropertyExists(inProperty);
// 			break;
// 	}
// 
// 	return exists;
// }







