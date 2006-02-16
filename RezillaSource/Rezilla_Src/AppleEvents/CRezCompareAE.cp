// ===========================================================================
// CRezCompareAE.cp
// 
//                       Created: 2005-05-12 07:51:22
//             Last modification: 2005-05-13 21:37:16
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// ===========================================================================
//  AppleEvent Object Model Support. These methods are part of the CRezCompare 
//  class (inheriting from LModelObject).

#include "CRezCompare.h"
#include "CRezillaApp.h"
#include "CCompResultWindow.h"
#include "UMiscUtils.h"
#include "RezillaConstants.h"

#include <LCommander.h>


// ---------------------------------------------------------------------------
//	 MakeSelfSpecifier
// ---------------------------------------------------------------------------
//	Make an Object Specifier for a RezMaps comparison object

void
CRezCompare::MakeSelfSpecifier(
	AEDesc&	inSuperSpecifier,
	AEDesc&	outSelfSpecifier) const
{
		OSErr			err;
		StAEDescriptor	keyData;
		SInt32			position = GetAEPosition(this);
		
		keyData.Assign(position);

		// Make ospec for the rezmap
		err = ::CreateObjSpecifier(rzom_cMapsComp, &inSuperSpecifier, formAbsolutePosition,
										keyData, false, &outSelfSpecifier);
		ThrowIfOSErr_(err);

}



// ---------------------------------------------------------------------------
//	 GetAEProperty
// ---------------------------------------------------------------------------
//	Return a descriptor for the specified Property
//	rzom_pCompCriteria		= 'pCRI';	// Comparison criteria
// 	rzom_pIgnoreName		= 'IgnN';	// IgnoreNameDiff
// 	rzom_pIgnoreAttrs		= 'IgnA';	// IgnoreAttrsDiff
// 	rzom_pIgnoreData		= 'IgnD';	// IgnoreDataDiff
// 	rzom_pOnlyInOld			= 'OldR';	// Only in old map resources (list)
// 	rzom_pOnlyInNew			= 'NewR';	// Only in new map resources (list)
// 	rzom_pDiffering			= 'Diff';	// In both but different (list)
// 	rzom_pIdentical			= 'Iden';	// In both and identical (list)

void
CRezCompare::GetAEProperty(
	DescType		inProperty,
	const AEDesc&	inRequestedType,
	AEDesc&			outPropertyDesc) const
{
	OSErr		error = noErr;
	
	switch (inProperty) {
		
		case rzom_pCompCriteria:
		AEDescList listDesc;
		// Third parameter must be true to create an AERecord
		error = ::AECreateList(NULL, 0, true, &listDesc);
		ThrowIfOSErr_(error);
		
		error = ::AEPutParamPtr(&listDesc, rzom_pIgnoreName, typeBoolean,
						&mIgnoreNames, sizeof(Boolean));
		ThrowIfOSErr_(error);
		error = ::AEPutParamPtr(&listDesc, rzom_pIgnoreAttrs, typeBoolean,
						&mIgnoreAttrs, sizeof(Boolean));
		ThrowIfOSErr_(error);
		error = ::AEPutParamPtr(&listDesc, rzom_pIgnoreData, typeBoolean,
						&mIgnoreData, sizeof(Boolean));
		ThrowIfOSErr_(error);
		
		error = AECoerceDesc(&listDesc, typeAERecord, &outPropertyDesc);
		::AEDisposeDesc(&listDesc);
		break;

		
		case rzom_pIgnoreName:
		error = ::AECreateDesc(typeBoolean, (Ptr) &mIgnoreNames,
									sizeof(Boolean), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;

		
		case rzom_pIgnoreAttrs:
		error = ::AECreateDesc(typeBoolean, (Ptr) &mIgnoreAttrs,
									sizeof(Boolean), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;

		
		case rzom_pIgnoreData:
		error = ::AECreateDesc(typeBoolean, (Ptr) &mIgnoreData,
									sizeof(Boolean), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;

		
		case rzom_pDiffering:
		GetAECompareList( mDifferingList, outPropertyDesc);
		break;

		
		case rzom_pIdentical:
		GetAECompareList( mIdenticalList, outPropertyDesc);
		break;

		
		case rzom_pOnlyInNew:
		GetAECompareList( mOnlyInNewList, outPropertyDesc);
		break;

		
		case rzom_pOnlyInOld:
		GetAECompareList( mOnlyInOldList, outPropertyDesc);
		break;

		
		default:
		LModelObject::GetAEProperty(inProperty, inRequestedType,
									outPropertyDesc);
		break;
	}
}


// ---------------------------------------------------------------------------
//	 GetAEProperty
// ---------------------------------------------------------------------------

void
CRezCompare::GetAECompareList(
	TArray<CRezTypId *> inList, 
	AEDesc&			outPropertyDesc) const
{
	CRezTypId *	theTypId = NULL;
	ResType		theType;
	short		theID;
	long		index = 1;
	OSErr		error = noErr;
	AEDescList	listDesc;
	Str255		name;
	
	error = ::AECreateList(NULL, 0, false, &listDesc);
	
	TArrayIterator<CRezTypId*> iterator(inList);
	
	while (iterator.Next(theTypId) && error == noErr) {
		AEDescList subDesc;
		
		error = ::AECreateList(NULL, 0, false, &subDesc);
		
		theType = theTypId->mType;
		UMiscUtils::OSTypeToPString(theType, name);
		error = ::AEPutPtr(&subDesc, 1, typeChar, (Ptr) name + 1, StrLength(name));
		
		theID = theTypId->mID;
		error = ::AEPutPtr(&subDesc, 2, typeSInt16, (Ptr) &theID, sizeof(SInt16));
		
		error = ::AEPutDesc(&listDesc, index, &subDesc);
		
		index++;
		
		::AEDisposeDesc(&subDesc);
	}
	
	error = ::AECoerceDesc(&listDesc, typeAEList, &outPropertyDesc);
	::AEDisposeDesc(&listDesc);
	
	
	::AEDisposeDesc(&listDesc);
	ThrowIfOSErr_(error);
}
	

// ---------------------------------------------------------------------------
//	 AEPropertyExists
// ---------------------------------------------------------------------------

bool
CRezCompare::AEPropertyExists(
	DescType	inProperty) const
{
	bool	exists = false;

	switch (inProperty) {

		case rzom_pCompCriteria:
		case rzom_pIgnoreName:
		case rzom_pIgnoreAttrs:
		case rzom_pIgnoreData:
		case rzom_pOnlyInOld:
		case rzom_pOnlyInNew:
		case rzom_pDiffering:
		case rzom_pIdentical:
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
CRezCompare::GetAEPosition(const CRezCompare * inComp) {
	
	WindowPtr	windowP = ::GetWindowList();
	LWindow*	ppWindow = nil;
	CCompResultWindow * compWindow;
	SInt32		position = 0, count = 0;
	
	while (windowP) {
		ppWindow = LWindow::FetchWindowObject(windowP);
		
		if (ppWindow != nil && ppWindow->GetModelKind() == rzom_cCompWindow) {
			count++;
			compWindow = dynamic_cast<CCompResultWindow*>(ppWindow);

			if (compWindow && compWindow->GetRezCompare() == inComp) {
				position = count;
				break;
			} 
		} 
		windowP = MacGetNextWindow(windowP);
	}
	
	if (position == 0) {
		ThrowOSErr_(errAENoSuchObject);
	}
	
	return position;
}

