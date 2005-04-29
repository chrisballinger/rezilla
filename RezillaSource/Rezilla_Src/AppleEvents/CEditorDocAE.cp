// ===========================================================================
// CEditorDocAE.cp
// 
//                       Created: 2005-04-09 10:03:39
//             Last modification: 2005-04-29 10:53:44
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
#include "CRezObj.h"
#include "CRezMapTable.h"
#include "UResources.h"
#include "RezillaConstants.h"

#include <LCommander.h>


// ---------------------------------------------------------------------------
//	¥ MakeSelfSpecifier												  [public]
// ---------------------------------------------------------------------------

void
CEditorDoc::MakeSelfSpecifier(
	AEDesc	&inSuperSpecifier,
	AEDesc	&outSelfSpecifier) const
{
	DescType	docClass;
	Str255		docName;
	GetDescriptor(docName);

	StAEDescriptor	keyData;
	OSErr	err = ::AECreateDesc(typeChar, docName + 1, docName[0], &keyData.mDesc);
	ThrowIfOSErr_(err);

	switch (mKind) {
		case editor_kindGui:
		docClass = rzom_cGuiEditDoc;
		break;

		case editor_kindTmpl:
		docClass = rzom_cTmplEditDoc;
		break;

		case editor_kindHex:
		docClass = rzom_cHexEditDoc;
		break;

	}
	
	err = ::CreateObjSpecifier(rzom_cEditorDoc, &inSuperSpecifier, formName,
								&keyData.mDesc, false, &outSelfSpecifier);
	ThrowIfOSErr_(err);
}


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
		
		
		// Handled in GetModelProperty
// 		case cWindow: {
// 			// Return as window 1 of this editor document
// 			AEDesc 			docSpec;
// 			StAEDescriptor	keyData;
// 			SInt32			index = 1;
// 
// 			MakeSpecifier(docSpec);
// 
// 			keyData.Assign(index);
// 			error = ::CreateObjSpecifier( cWindow, &docSpec, formAbsolutePosition,
// 									keyData, false, &outPropertyDesc);
// 			ThrowIfOSErr_(error);
// 			break;
// 		}
		
		
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
		
		
		// Handled in GetModelProperty
// 		case rzom_cRezObj:
// 		break;
		
		
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


// ---------------------------------------------------------------------------
//	¥ AEPropertyExists
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
//	¥ GetAEPosition
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


// ---------------------------------------------------------------------------
//	¥ GetSubModelByPosition											  [public]
// ---------------------------------------------------------------------------

void
CEditorDoc::GetSubModelByPosition(
	DescType		inModelID,
	SInt32			inPosition,
	AEDesc&			outToken) const
{
	switch (inModelID) {

		case cWindow: 
		if (inPosition == 1) {
			if (mMainWindow != nil) {
				PutInToken(mMainWindow, outToken);
			} else {
				ThrowOSErr_(errAENoSuchObject);
			}
			break;
		} 

		// Fall through...

		default:
			LModelObject::GetSubModelByPosition(inModelID, inPosition, outToken);
			break;
	}
}


// ---------------------------------------------------------------------------
//	¥ GetModelProperty
// ---------------------------------------------------------------------------
//	Return a ModelObject object for 'cwin' property

LModelObject*
CEditorDoc::GetModelProperty(DescType inProperty) const
{
	LModelObject* theModelObject = nil;

	switch (inProperty) {

		case rzom_cEditorWindow:
		case cWindow:
		theModelObject = dynamic_cast<LModelObject *>(mMainWindow);
		break;
		

		case rzom_cRezObj:
		theModelObject = dynamic_cast<LModelObject *>(mRezObj);
		break;


		default:
		theModelObject = LModelObject::GetModelProperty(inProperty);
			break;
	}

	return theModelObject;
}

		