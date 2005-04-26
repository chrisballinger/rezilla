// ===========================================================================
// CEditorDocAE.cp
// 
//                       Created: 2005-04-09 10:03:39
//             Last modification: 2005-04-26 10:16:35
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
//  AppleEvent Object Model Support. These methods are part of the CEditorDoc 
//  class (inheriting from LModelObject).

#include "CRezMap.h"
#include "CEditorDoc.h"
#include "CEditorWindow.h"
#include "CRezMapDoc.h"
#include "CRezMapTable.h"
#include "UResources.h"
#include "RezillaConstants.h"

#include <LCommander.h>


// ---------------------------------------------------------------------------
//	� GetAEProperty
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
CEditorDoc::GetAEProperty(
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
			// Return the index of this document among the other editor docs
			SInt32	position = GetAEPosition(this);
			if (position > 0) {
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
			StAEDescriptor	keyData;
			SInt32	index = UWindows::FindWindowIndex( mMainWindow->GetMacWindow() );

			superSpec.descriptorType = typeNull;
			superSpec.dataHandle = nil;
			keyData.Assign(index);
			error = ::CreateObjSpecifier( cWindow, &superSpec, formAbsolutePosition,
									keyData, false, &outPropertyDesc);
			ThrowIfOSErr_(error);
			break;
		}
		
		
		case rzom_pKind:
		// EditorDoc serves as a default kind
		ResType	theType = rzom_eEditorDoc;
		if (mKind == editor_kindGui) {
			theType = rzom_eGuiEditor;
		} else if (mKind == editor_kindTmpl) {
			theType = rzom_eTmplEditor;
		} else if (mKind == editor_kindHex) {
			theType = rzom_eHexEditor;
		}
		error = ::AECreateDesc(typeEnumerated, (Ptr) &theType,
									sizeof(ResType), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
		
		
		case rzom_cRezMapDoc:
		case rzom_pOwnerMapDoc:  {
			// Returns the owner rezmap doc by index
			AEDesc superSpec;
			StAEDescriptor keyData;
			SInt32 position = CRezMapDoc::GetAEPosition(mRezMapTable->GetOwnerDoc());
			
			superSpec.descriptorType = typeNull;
			superSpec.dataHandle = nil;
			keyData.Assign(position);
			error = ::CreateObjSpecifier( rzom_cRezMapDoc, &superSpec, formAbsolutePosition,
									keyData, false, &outPropertyDesc);
			ThrowIfOSErr_(error);
			break;
		}
		
		
		case rzom_cRezObj:
		
		break;
		
		
		default:
		LDocument::GetAEProperty(inProperty, inRequestedType,
									outPropertyDesc);
		break;
	}
}


// ---------------------------------------------------------------------------
//	� SetAEProperty
// ---------------------------------------------------------------------------
// All the RezMapDoc properties are readOnly

void
CEditorDoc::SetAEProperty(
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
// //	� GetModelName
// // ---------------------------------------------------------------------------
// //	Return the name of a Window as an AppleEvent model object
// 
// StringPtr
// CEditorDoc::GetModelName(
// 	Str255	outModelName) const
// {
// 	return GetDescriptor(outModelName);
// }


// ---------------------------------------------------------------------------
//	� AEPropertyExists
// ---------------------------------------------------------------------------

bool
CEditorDoc::AEPropertyExists(
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


// ---------------------------------------------------------------------------
//	� GetAEPosition
// ---------------------------------------------------------------------------

SInt32
CEditorDoc::GetAEPosition(const CEditorDoc * inDoc) {
	SInt32		currPos = 0, result = 0;
	LDocument*	theDoc = nil;
	Boolean		found = false;
	DescType	theKind;

	TArrayIterator<LDocument*> iterator( LDocument::GetDocumentList() );
	while (iterator.Next(theDoc)) {
		theKind = theDoc->GetModelKind();
		if (theKind == rzom_cEditorDoc 
			|| theKind == rzom_cGuiEditDoc 
			|| theKind == rzom_cTmplEditDoc 
			|| theKind == rzom_cHexEditDoc) {
			currPos++;
			if (theDoc == inDoc) {
				result = currPos;
				break;
			} 
		} 				
		theDoc = nil;
	}

	return result;
}
