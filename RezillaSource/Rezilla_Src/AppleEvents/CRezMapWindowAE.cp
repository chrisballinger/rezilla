// ===========================================================================
// CRezMapWindowAE.cp
// 
//                       Created: 2005-04-26 09:48:48
//             Last modification: 2005-05-14 12:19:51
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// ===========================================================================
//  AppleEvent Object Model Support. These methods are part of the CRezMapWindow 
//  class (inheriting from LModelObject).

#include "CRezMapWindow.h"
#include "RezillaConstants.h"

#include <LCommander.h>


// ---------------------------------------------------------------------------
//   GetAEProperty
// ---------------------------------------------------------------------------

void
CRezMapWindow::GetAEProperty(
	DescType		inProperty,
	const AEDesc&	inRequestedType,
	AEDesc&			outPropertyDesc) const
{
	OSErr	error = noErr;
	SInt32	count;
	
	switch (inProperty) {
		case rzom_pTypesCount:
		count = GetCountTypeField();
		error = ::AECreateDesc(typeSInt32, (Ptr) &count,
									sizeof(SInt32), &outPropertyDesc);	
		ThrowIfOSErr_(error);
		break;
		
		case rzom_pResCount:
		count = GetCountRezField();
		error = ::AECreateDesc(typeSInt32, (Ptr) &count,
									sizeof(SInt32), &outPropertyDesc);	
		ThrowIfOSErr_(error);
		break;
		
		default:
		LWindow::GetAEProperty(inProperty, inRequestedType, outPropertyDesc);
		break;
	}
}


// ---------------------------------------------------------------------------
//   AEPropertyExists
// ---------------------------------------------------------------------------

bool
CRezMapWindow::AEPropertyExists(
	DescType	inProperty) const
{
	bool	exists = false;

	switch (inProperty) {
		case rzom_pTypesCount:
		case rzom_pResCount:
		exists = true;
		break;
		
		default:
			exists = LWindow::AEPropertyExists(inProperty);
			break;
	}

	return exists;
}


