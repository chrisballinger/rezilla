// ===========================================================================
// CInspectorWindowAE.cp
// 
//                       Created: 2005-04-26 09:48:48
//             Last modification: 2005-05-14 12:11:16
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
//  AppleEvent Object Model Support. These methods are part of the CInspectorWindow 
//  class (inheriting from LModelObject).

#include "CInspectorWindow.h"
#include "RezillaConstants.h"

#include <LCommander.h>


// ---------------------------------------------------------------------------
//	¥ MakeSelfSpecifier												  [public]
// ---------------------------------------------------------------------------
// Specify by position

void
CInspectorWindow::MakeSelfSpecifier(
	AEDesc	&inSuperSpecifier,
	AEDesc	&outSelfSpecifier) const
{
		StAEDescriptor	keyData;
		OSErr			err;
		SInt32			windowIndex = 1;
		
		keyData.Assign(windowIndex);

		err = ::CreateObjSpecifier(	rzom_cInspector,
									&inSuperSpecifier,
								   formAbsolutePosition,
									keyData,
									false,		// Don't dispose inputs
									&outSelfSpecifier);
		ThrowIfOSErr_(err);
}


// ---------------------------------------------------------------------------
//	¥ GetAEProperty
// ---------------------------------------------------------------------------

void
CInspectorWindow::GetAEProperty(
	DescType		inProperty,
	const AEDesc&	inRequestedType,
	AEDesc&			outPropertyDesc) const
{
	OSErr	error = noErr;
	
	switch (inProperty) {
// 		case rzom_pTypesCount:
// 		break;
// 		
// 		case rzom_pResCount:
// 		break;
		
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
CInspectorWindow::AEPropertyExists(
	DescType	inProperty) const
{
	bool	exists = false;

	switch (inProperty) {
// 		case rzom_pTypesCount:
// 		case rzom_pResCount:
// 		exists = true;
// 		break;
		
		default:
			exists = LWindow::AEPropertyExists(inProperty);
			break;
	}

	return exists;
}


