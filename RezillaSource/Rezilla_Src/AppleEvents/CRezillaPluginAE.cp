// ===========================================================================
// CRezillaPluginAE.cp
// 
//                       Created: 2006-09-27 20:13:22
//             Last modification: 2006-09-28 08:09:29
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================
//  AppleEvent Object Model Support. These methods are part of the CRezillaPlugin 
//  class (inheriting from LModelObject).

#include "CRezillaPlugin.h"
#include "CRezMap.h"
#include "CRezType.h"
#include "CRezillaApp.h"
#include "CPluginsController.h"
#include "UResources.h"
#include "UMiscUtils.h"
#include "UCodeTranslator.h"
#include "RezillaConstants.h"

#include <LCommander.h>
#include <LArray.h>


// ---------------------------------------------------------------------------
//   MakeSelfSpecifier												  [public]
// ---------------------------------------------------------------------------

void
CRezillaPlugin::MakeSelfSpecifier(
	AEDesc	&inSuperSpecifier,
	AEDesc	&outSelfSpecifier) const
{
	StAEDescriptor	keyData;
	OSErr			err;
	Str255			theString;
	
	if ( ::CFStringGetPascalString( mName, theString, sizeof(theString), NULL) ) {
		err = ::AECreateDesc(typeChar, theString + 1, theString[0], &keyData.mDesc);
		if (err == noErr) {
			err = ::CreateObjSpecifier(rzom_cPlugin, &inSuperSpecifier, formName,
									   &keyData.mDesc, false, &outSelfSpecifier);
		} 
	} else {
		SInt32 position = GetAEPosition(this);
		keyData.Assign(position);
		err = ::CreateObjSpecifier(rzom_cPlugin, &inSuperSpecifier, formAbsolutePosition,
								   keyData, false, &outSelfSpecifier);
	}
	ThrowIfOSErr_(err);
}


// ---------------------------------------------------------------------------
//   GetAEProperty
// ---------------------------------------------------------------------------
//	Return a descriptor for the specified Property
//  rzom_pName			= pName;		// Name ('pnam')
//  rzom_pVersion		= pVersion;		// Version ('vers')	
//  rzom_pType			= 'pTYP';		// Type
//  rzom_pCreator		= 'pCRE';		// Creator
//  rzom_pLoaded		= 'pLDD';		// Loaded
//  rzom_pSupportTypes	= 'pSuT';		// Supported types
//  pIndex				= 'pidx';		// Index

void
CRezillaPlugin::GetAEProperty(
	DescType		inProperty,
	const AEDesc&	inRequestedType,
	AEDesc&			outPropertyDesc) const
{
	OSErr	error = noErr;
	Str255	theString;
	
	switch (inProperty) {
		
		case pName: 
		if ( ::CFStringGetPascalString( mName, theString, sizeof(theString), NULL) ) {
			error = ::AECreateDesc(typeChar, (Ptr) theString + 1, theString[0], &outPropertyDesc);
		} else {
			error = err_PluginGetInfoFailed;
		}
		ThrowIfOSErr_(error);
		break;
		

		case rzom_pVersion:
		UMiscUtils::VersionStringFromValue(mPluginVersion, theString);
		error = ::AECreateDesc(typeChar, (Ptr) theString + 1, theString[0], &outPropertyDesc);
		break;
		
		
		case rzom_pType: 
		case rzom_cRezType:
		UMiscUtils::OSTypeToPString(mPluginType, theString);
		error = ::AECreateDesc(typeChar, (Ptr) theString + 1, theString[0], &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
	

		case rzom_pCreator:
		UMiscUtils::OSTypeToPString(mPluginCreator, theString);
		error = ::AECreateDesc(typeChar, (Ptr) theString + 1, theString[0], &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
		
		
		case pIndex: {
			SInt32 position = GetAEPosition(this);
			error = ::AECreateDesc(typeSInt32, (Ptr) &position, sizeof(SInt32), &outPropertyDesc);	
			ThrowIfOSErr_(error);
			break;
		}
		
		
		case rzom_pLoaded:
		error = ::AECreateDesc(typeBoolean, (Ptr) &mIsLoaded,
									sizeof(Boolean), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
		
		
		case rzom_pSupportTypes: {
			if (outPropertyDesc.descriptorType == typeNull) {
				error = ::AECreateList(nil, 0, false, &outPropertyDesc);
				ThrowIfOSErr_(error);
			}
			
			ResType		theType;
			UInt16		index = 1;
			TArrayIterator<ResType>	iterator(mEditTypes);
			
			while (iterator.Next(theType)) {
				Str255			name;
				StAEDescriptor	keyData;
				
				UMiscUtils::OSTypeToPString(theType, name);
				error = ::AECreateDesc(typeChar, name + 1, name[0], &keyData.mDesc);
				error = ::AEPutDesc(&outPropertyDesc, index, &keyData.mDesc);
				index++;
			}
			break; 
		}
		
		
		default:
		LModelObject::GetAEProperty(inProperty, inRequestedType,
									outPropertyDesc);
		break;
	}
}


// ---------------------------------------------------------------------------
//   AEPropertyExists
// ---------------------------------------------------------------------------

bool
CRezillaPlugin::AEPropertyExists(DescType inProperty) const
{
	bool	exists = false;

	switch (inProperty) {
		case rzom_pName:
		case rzom_pVersion:
		case rzom_pType:
		case rzom_pCreator:
		case rzom_pLoaded:
		case rzom_pSupportTypes:
			exists = true;
			break;

		default:
			exists = LModelObject::AEPropertyExists(inProperty);
			break;
	}

	return exists;
}


// ---------------------------------------------------------------------------
//   GetAEPosition
// ---------------------------------------------------------------------------

SInt32
CRezillaPlugin::GetAEPosition(const CRezillaPlugin * inPlugin) 
{
	SInt32			position = 1;
	CRezillaPlugin	*thePlugin = NULL, *currPlugin;
	
	TArrayIterator<CRezillaPlugin*> iterator(CPluginsController::sPluginsList);
	while (iterator.Next(currPlugin)) {
		if (inPlugin == currPlugin) {
			thePlugin = currPlugin;
			break;
		} 
		position++;
	}
	if (!thePlugin) {
		ThrowOSErr_(errAENoSuchObject);
	} 
	return position;
}

