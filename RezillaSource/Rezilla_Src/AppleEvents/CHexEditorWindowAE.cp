// ===========================================================================
// CHexEditorWindowAE.cp
// 
//                       Created: 2005-04-28 23:45:11
//             Last modification: 2005-06-02 11:32:37
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
//	¥ GetModelProperty
// ---------------------------------------------------------------------------
//	Return a ModelObject object for 'HexP' and 'TxtP' properties
//	Currently not implemented

LModelObject*
CHexEditorWindow::GetModelProperty(DescType inProperty) const
{
	LModelObject* theModelObject = nil;

	switch (inProperty) {

// 		case rzom_cHexPane:
// 		case rzom_cTxtPane: 
// 		break;
		
		default:
		theModelObject = LModelObject::GetModelProperty(inProperty);
			break;
	}

	return theModelObject;
}

		




