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


// // ---------------------------------------------------------------------------
// //	¥ MakeSelfSpecifier
// // ---------------------------------------------------------------------------
// //	Make an Object Specifier for a Window
// 
// void
// CRezObj::MakeSelfSpecifier(
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


// // ---------------------------------------------------------------------------
// //	¥ SetAEProperty
// // ---------------------------------------------------------------------------
// 
// void
// CRezObj::SetAEProperty(
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
//	¥ GetAERezObjAttribute
// ---------------------------------------------------------------------------

void
CRezObj::GetAERezObjAttribute(
	short		inAttribute,
	AEDesc&		outPropertyDesc) const
{
	Boolean attrIsSet = HasAttribute(inAttribute);
	
	OSErr error = ::AECreateDesc(typeBoolean, (Ptr) &attrIsSet,
								sizeof(Boolean), &outPropertyDesc);
	ThrowIfOSErr_(error);
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


// // ---------------------------------------------------------------------------
// //	¥ AEPropertyExists
// // ---------------------------------------------------------------------------
// 
// bool
// CRezObj::AEPropertyExists(
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







