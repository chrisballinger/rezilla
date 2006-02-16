// ===========================================================================
// CEditorWindowAE.cp
// 
//                       Created: 2005-04-26 10:05:20
//             Last modification: 2005-06-12 18:45:01
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// ===========================================================================
//  AppleEvent Object Model Support. These methods are part of the CEditorWindow 
//  class (inheriting from LModelObject).

#include "CEditorWindow.h"
#include "CEditorDoc.h"
#include "RezillaConstants.h"

#include <LCommander.h>


// ---------------------------------------------------------------------------
//   MakeSelfSpecifier												  [public]
// ---------------------------------------------------------------------------

void
CEditorWindow::MakeSelfSpecifier(
	AEDesc	&inSuperSpecifier,
	AEDesc	&outSelfSpecifier) const
{
	DescType		keyForm;
	StAEDescriptor	keyData;
	OSErr			err;
	
	// Specify by position
	SInt32	windowIndex = mOwnerDoc->GetSuperModel()->GetPositionOfSubModel(rzom_cEditorWindow, this);
	keyForm = formAbsolutePosition;
	keyData.Assign(windowIndex);
	
	err = ::CreateObjSpecifier(	rzom_cEditorWindow,
							   &inSuperSpecifier,
							   keyForm,
							   keyData,
							   false,		// Don't dispose inputs
							   &outSelfSpecifier);
	ThrowIfOSErr_(err);
}


// ---------------------------------------------------------------------------
//   GetAEProperty
// ---------------------------------------------------------------------------
//	Return a descriptor for the specified Property
// 	rzom_pKind			= 'pKND';	// Kind

void
CEditorWindow::GetAEProperty(
	DescType		inProperty,
	const AEDesc&	inRequestedType,
	AEDesc&			outPropertyDesc) const
{
	OSErr	error = noErr;
	
	switch (inProperty) {
		
		case rzom_pKind: {
		// EditorDoc serves as a default kind
		ResType	theType = rzom_eEditorDoc;
		SInt16 theKind = mOwnerDoc->GetKind();

		if (theKind == editor_kindGui) {
			theType = rzom_eGuiEditor;
		} else if (theKind == editor_kindTmpl) {
			theType = rzom_eTmplEditor;
		} else if (theKind == editor_kindHex) {
			theType = rzom_eHexEditor;
		}
		error = ::AECreateDesc(typeEnumerated, (Ptr) &theType,
									sizeof(ResType), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
		}
		
		default:
		LWindow::GetAEProperty(inProperty, inRequestedType,
									outPropertyDesc);
		break;
	}
}


// ---------------------------------------------------------------------------
//   AEPropertyExists
// ---------------------------------------------------------------------------

bool
CEditorWindow::AEPropertyExists(
	DescType	inProperty) const
{
	bool	exists = false;

	switch (inProperty) {

		case rzom_pKind:
			exists = true;
			break;

		default:
			exists = LWindow::AEPropertyExists(inProperty);
			break;
	}

	return exists;
}


