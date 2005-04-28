// ===========================================================================
// CEditorWindowAE.cp
// 
//                       Created: 2005-04-26 10:05:20
//             Last modification: 2005-04-28 14:12:43
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
//  AppleEvent Object Model Support. These methods are part of the CEditorWindow 
//  class (inheriting from LModelObject).

#include "CEditorWindow.h"
#include "CEditorDoc.h"
#include "RezillaConstants.h"

#include <LCommander.h>


// ---------------------------------------------------------------------------
//	¥ MakeSelfSpecifier												  [public]
// ---------------------------------------------------------------------------

void
CEditorWindow::MakeSelfSpecifier(
	AEDesc	&inSuperSpecifier,
	AEDesc	&outSelfSpecifier) const
{
		DescType		winClass;
		DescType		keyForm;
		StAEDescriptor	keyData;
		OSErr			err;

		// Specify by position
		SInt32	windowIndex = 1;
		keyForm = formAbsolutePosition;
		keyData.Assign(windowIndex);

		switch ( mOwnerDoc->GetKind() ) {
			case editor_kindGui:
			winClass = rzom_cGuiWindow;
			break;

			case editor_kindTmpl:
			winClass = rzom_cTmplWindow;
			break;

			case editor_kindHex:
			winClass = rzom_cHexWindow;
			break;
		}

		err = ::CreateObjSpecifier(	rzom_cEditorWindow,
									&inSuperSpecifier,
									keyForm,
									keyData,
									false,		// Don't dispose inputs
									&outSelfSpecifier);
		ThrowIfOSErr_(err);
}



// ---------------------------------------------------------------------------
//	¥ GetAEProperty
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
		
		case rzom_pKind:
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
		
		
		default:
		LWindow::GetAEProperty(inProperty, inRequestedType,
									outPropertyDesc);
		break;
	}
}


// // ---------------------------------------------------------------------------
// //	¥ SetAEProperty
// // ---------------------------------------------------------------------------
// // All the RezMapDoc properties are readOnly
// 
// void
// CEditorWindow::SetAEProperty(
// 	DescType		inProperty,
// 	const AEDesc&	inValue,
// 	AEDesc&			outAEReply)
// {
// 	switch (inProperty) {
// 		
// 		default:
// 			LWindow::SetAEProperty(inProperty, inValue, outAEReply);
// 			break;
// 	}
// }


// ---------------------------------------------------------------------------
//	¥ AEPropertyExists
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


