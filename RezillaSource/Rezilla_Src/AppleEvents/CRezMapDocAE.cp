// ===========================================================================
// CRezMapDocAE.cp
// 
//                       Created: 2005-04-09 10:03:39
//             Last modification: 2005-04-17 10:17:51
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
//  AppleEvent Object Model Support. These methods are part of the CRezMapDoc 
//  class (inheriting from LModelObject).

#include "CRezMap.h"
#include "CRezMapDoc.h"
#include "CRezFile.h"
#include "CRezMapWindow.h"
#include "UResources.h"
#include "RezillaConstants.h"

#include <LCommander.h>



// ---------------------------------------------------------------------------
//	¥ GetAEProperty
// ---------------------------------------------------------------------------
//	Return a descriptor for the specified Property
//	rzom_pReadOnly		= 'pRDO';	// mapReadOnly
// 	rzom_cRezMap		= 'cMAP';	// RezMap
// 	rzom_pRefNum		= 'pRFN';	// RefNum
// 	rzom_pRezFork		= 'pFRK';	// ResFork
// 	rzom_pRezFile		= 'pFIL';	// ResFile
//  pIndex				= 'pidx';
//  cWindow				= 'cwin';

void
CRezMapDoc::GetAEProperty(
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
			// Return the index of this document among the other rezmap docs
			SInt32		position = 0;
			LDocument *	theDoc = nil;
			Boolean found = false;
			
			TArrayIterator<LDocument*> iterator( LDocument::GetDocumentList() );
			while (iterator.Next(theDoc)) {
				if (theDoc->GetModelKind() == rzom_cRezMapDoc) {
					position++;
					if (theDoc == this) {
						found = true;
						break;
					} 
				} 				
				theDoc = nil;
			}
			if (found) {
				error = ::AECreateDesc(typeSInt32, (Ptr) &position,
											sizeof(SInt32), &outPropertyDesc);
			} else {
				error = errAENoSuchObject;
			}
			ThrowIfOSErr_(error);
			break;
		}
		
		
		case 'cwin': {
			// Returns the window by index (in stack order)
			AEDesc superSpec;
			superSpec.descriptorType = typeNull;
			superSpec.dataHandle = nil;
			StAEDescriptor	keyData;
			SInt32	index = UWindows::FindWindowIndex( mRezMapWindow->GetMacWindow() );

			keyData.Assign(index);
			error = ::CreateObjSpecifier( cWindow, &superSpec, formAbsolutePosition,
									keyData, false, &outPropertyDesc);
			ThrowIfOSErr_(error);
			break;
		}
		
		
		case rzom_pRefNum:
		short		theRefNum = mRezMap->GetRefnum();
		error = ::AECreateDesc(typeSInt16, (Ptr) &theRefNum,
									sizeof(short), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
		

		case rzom_pRezFork:
		ResType	theType = rzom_eIsUnknownFork;
		if (mFork == fork_rezfork) {
			theType = rzom_eIsRsrcFork;
		} else if (mFork == fork_datafork) {
			theType = rzom_eIsDataFork;
		} 
		error = ::AECreateDesc(typeEnumerated, (Ptr) &theType,
									sizeof(ResType), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
		
		
		case rzom_cRezMap:  {
			// Returns the map described by its refnum
			AEDesc superSpec;
			superSpec.descriptorType = typeNull;
			superSpec.dataHandle = nil;
			StAEDescriptor	keyData;
			keyData.Assign(mRezMap->GetRefnum());
			error = ::CreateObjSpecifier( rzom_cRezMap, &superSpec, formUniqueID,
									keyData, false, &outPropertyDesc);
			ThrowIfOSErr_(error);
			break;
		}

		
		case rzom_pRezFile:
		FSSpec theFSS = mRezFile->GetFileSpec();
		error = ::AECreateDesc(typeFSS, (Ptr) &theFSS,
									sizeof(FSSpec), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
		
		
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
CRezMapDoc::SetAEProperty(
	DescType		inProperty,
	const AEDesc&	inValue,
	AEDesc&			outAEReply)
{
	switch (inProperty) {				
		default:
			LDocument::SetAEProperty(inProperty, inValue, outAEReply);
			break;
	}
}


// ---------------------------------------------------------------------------
//	¥ AEPropertyExists
// ---------------------------------------------------------------------------

bool
CRezMapDoc::AEPropertyExists(
	DescType	inProperty) const
{
	bool	exists = false;

	switch (inProperty) {

		case cWindow:
		case pIndex:
		case rzom_pReadOnly:
		case rzom_pRefNum:
		case rzom_pRezFile:
		case rzom_pRezFork:
		case rzom_cRezMap: 
			exists = true;
			break;

		default:
			exists = LDocument::AEPropertyExists(inProperty);
			break;
	}

	return exists;
}


// ---------------------------------------------------------------------------
//	¥ GetAEPosition
// ---------------------------------------------------------------------------

SInt32
CRezMapDoc::GetAEPosition() {
	SInt32	currPos = 0, result = 0;
	LDocument*	theDoc = nil;
	Boolean found = false;
	
	TArrayIterator<LDocument*> iterator( LDocument::GetDocumentList() );
	while (iterator.Next(theDoc)) {
		if (theDoc->GetModelKind() == rzom_cRezMapDoc) {
			currPos++;
			if (theDoc == this) {
				result = currPos;
				break;
			} 
		} 				
		theDoc = nil;
	}

	return result;
}

