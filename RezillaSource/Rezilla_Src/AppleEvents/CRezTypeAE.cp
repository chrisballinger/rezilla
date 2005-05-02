// ===========================================================================
// CRezTypeAE.cp
// 
//                       Created: 2005-04-09 10:03:39
//             Last modification: 2005-05-02 17:41:06
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
//  AppleEvent Object Model Support. These methods are part of the CRezType 
//  class (inheriting from LModelObject).

#include "CRezMap.h"
#include "CRezType.h"
#include "CRezMapDoc.h"
#include "UMiscUtils.h"
#include "RezillaConstants.h"

#include <LCommander.h>



// ---------------------------------------------------------------------------
//	¥ MakeSelfSpecifier												  [public]
// ---------------------------------------------------------------------------

void
CRezType::MakeSelfSpecifier(
	AEDesc	&inSuperSpecifier,
	AEDesc	&outSelfSpecifier) const
{
		StAEDescriptor	keyData;
		OSErr			err;
		Str255			name;

		// Specify by name
		GetModelName(name);
		keyData.Assign(name);

		err = ::CreateObjSpecifier(rzom_cRezType, &inSuperSpecifier, formName,
										keyData, false, &outSelfSpecifier);
		ThrowIfOSErr_(err);
}


// ---------------------------------------------------------------------------
//	¥ GetAEProperty
// ---------------------------------------------------------------------------
//	Return a descriptor for the specified Property
//  rzom_pName			= pName;		// Name ('pnam')

void
CRezType::GetAEProperty(
	DescType		inProperty,
	const AEDesc&	inRequestedType,
	AEDesc&			outPropertyDesc) const
{
	OSErr	error = noErr;
	
	switch (inProperty) {
		
		case pIndex: {
			// Return the index of this type in the rezmap doc
			SInt32	position = mOwnerMap->GetOwnerDoc()->GetIndexForType(mType);
			if (position > 0) {
				error = ::AECreateDesc(typeSInt32, (Ptr) &position,
											sizeof(SInt32), &outPropertyDesc);
			} else {
				error = errAENoSuchObject;
			}
			ThrowIfOSErr_(error);
			break;
		}
		

		case pName: 
		Str255	name;
		GetModelName(name);
		error = ::AECreateDesc(typeChar, (Ptr) name + 1,
							StrLength(name), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;

		
		case pID: 
		error = ::AECreateDesc(typeUInt32, &mType,
							sizeof(UInt32), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;

		
		default:
		LModelObject::GetAEProperty(inProperty, inRequestedType,
									outPropertyDesc);
		break;
	}
}


// ---------------------------------------------------------------------------
//	¥ GetModelName
// ---------------------------------------------------------------------------
//	Return the name of a Window as an AppleEvent model object(Str255&) 

StringPtr
CRezType::GetModelName(
	Str255	outModelName) const
{
	Str255	name;
	UMiscUtils::OSTypeToPString(mType, name);
	LString::CopyPStr(name, outModelName);
	return outModelName;
}


// ---------------------------------------------------------------------------
//	¥ AEPropertyExists
// ---------------------------------------------------------------------------

bool
CRezType::AEPropertyExists(
	DescType	inProperty) const
{
	bool	exists = false;

	switch (inProperty) {

		case pIndex:
		case pName:
		case pID:
			exists = true;
			break;

		default:
			exists = LModelObject::AEPropertyExists(inProperty);
			break;
	}

	return exists;
}







