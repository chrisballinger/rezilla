// ===========================================================================
// CHexEditorWindowAE.cp
// 
//                       Created: 2005-04-28 23:45:11
//             Last modification: 2005-04-28 23:45:11
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
//  AppleEvent Object Model Support. These methods are part of the CHexEditorWindow 
//  class (inheriting from LModelObject).

#include "CHexEditorWindow.h"
#include "RezillaConstants.h"

#include <LCommander.h>



// ---------------------------------------------------------------------------
//	¥ GetAEProperty
// ---------------------------------------------------------------------------
//	Return a descriptor for the specified Property
// 	rzom_cHexPane		= 'HexP';	// Hexadecimal pane
// 	rzom_cTxtPane		= 'TxtP';	// Text pane
// 	
// 	As of version 1.0.6, removed from Rezilla's aete resource. Might be in a future release.

void
CHexEditorWindow::GetAEProperty(
	DescType		inProperty,
	const AEDesc&	inRequestedType,
	AEDesc&			outPropertyDesc) const
{
	OSErr	error = noErr;
	
	switch (inProperty) {
// 		case rzom_cHexPane:
// 		case rzom_cTxtPane: {
// 			// Return datapane by index: 1 for hex pane, 2 for text pane
// 			AEDesc 			winSpec;
// 			StAEDescriptor	keyData;
// 			SInt32			index = (inProperty == rzom_cHexPane) ? 1:2;
// 
// 			MakeSpecifier(winSpec);
// 
// 			keyData.Assign(index);
// 			error = ::CreateObjSpecifier( rzom_cDataPane, &winSpec, formAbsolutePosition,
// 									keyData, false, &outPropertyDesc);
// 			ThrowIfOSErr_(error);
// 			break;
// 		}
		
		
		default:
		LWindow::GetAEProperty(inProperty, inRequestedType,
									outPropertyDesc);
		break;
	}
}


// ---------------------------------------------------------------------------
//	¥ AEPropertyExists
// ---------------------------------------------------------------------------

bool
CHexEditorWindow::AEPropertyExists(
	DescType	inProperty) const
{
	bool	exists = false;

	switch (inProperty) {

// 		case rzom_cHexPane: 
// 		case rzom_cTxtPane:
// 			exists = true;
// 			break;

		default:
			exists = LModelObject::AEPropertyExists(inProperty);
			break;
	}

	return exists;
}


// ---------------------------------------------------------------------------
//	¥ GetModelProperty
// ---------------------------------------------------------------------------
//	Return a ModelObject object for 'HexP' and 'TxtP' properties

LModelObject*
CHexEditorWindow::GetModelProperty(DescType inProperty) const
{
	LModelObject* theModelObject = nil;

	switch (inProperty) {

// 		case rzom_cHexPane:
// 		case rzom_cTxtPane: 
// 		theModelObject = dynamic_cast<LModelObject *>(mMainWindow);
// 		break;
		
		default:
		theModelObject = LModelObject::GetModelProperty(inProperty);
			break;
	}

	return theModelObject;
}

		




