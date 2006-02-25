// ===========================================================================
// CPickerWindowAE.cp
// 
//                       Created: 2006-02-25 09:51:30
//             Last modification: 2006-02-25 09:51:39
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================
//  AppleEvent Object Model Support. These methods are part of the CPickerWindow 
//  class (inheriting from LModelObject).

#include "CPickerWindow.h"
#include "CPickerDoc.h"
#include "RezillaConstants.h"

#include <LCommander.h>


// ---------------------------------------------------------------------------
//   MakeSelfSpecifier												  [public]
// ---------------------------------------------------------------------------

void
CPickerWindow::MakeSelfSpecifier(
	AEDesc	&inSuperSpecifier,
	AEDesc	&outSelfSpecifier) const
{
	DescType		keyForm;
	StAEDescriptor	keyData;
	OSErr			err;
	
	// Specify by position
	SInt32	windowIndex = mOwnerDoc->GetSuperModel()->GetPositionOfSubModel(rzom_cPickerWindow, this);
	keyForm = formAbsolutePosition;
	keyData.Assign(windowIndex);
	
	err = ::CreateObjSpecifier(	rzom_cPickerWindow,
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

void
CPickerWindow::GetAEProperty(
	DescType		inProperty,
	const AEDesc&	inRequestedType,
	AEDesc&			outPropertyDesc) const
{
	OSErr	error = noErr;
	
	switch (inProperty) {
		
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
CPickerWindow::AEPropertyExists(
	DescType	inProperty) const
{
	bool	exists = false;

	switch (inProperty) {

		default:
			exists = LWindow::AEPropertyExists(inProperty);
			break;
	}

	return exists;
}


