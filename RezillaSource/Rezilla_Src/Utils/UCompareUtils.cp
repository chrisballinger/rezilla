// ===========================================================================
// UCompareUtils.cp	
// 				
//                       Created: 2005-01-02 15:16:34
//             Last modification: 2006-03-18 11:49:21
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2005, 2006
// All rights reserved.
// ===========================================================================


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CRezType.h"
#include "CPickerView.h"
#include "CRezillaApp.h"
#include "RezillaConstants.h"
#include "UCompareUtils.h"

#include <PP_KeyCodes.h>

#include <LPopupButton.h>
#include <LComparator.h>
#ifndef __MACH__
#include <Drag.h>
#endif
#include <UTextTraits.h>

#include <stdio.h>
#include <string.h>
#include "regex.h"


PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   CompareStr255												[static]
// ---------------------------------------------------------------------------

SInt16 
UCompareUtils::CompareStr255(Str255 * leftString, Str255 * rightString)
{
	return LString::CompareBytes((*leftString) + 1, (*rightString) + 1, (*leftString)[0], (*rightString)[0]);
}


// ---------------------------------------------------------------------------
//   HandlesAreIdentical												[static]
// ---------------------------------------------------------------------------

Boolean 
UCompareUtils::HandlesAreIdentical(const Handle leftHndl, const Handle rightHndl)
{
	Boolean result = true;
	Size leftSize = GetHandleSize(leftHndl);
	Size rightSize = GetHandleSize(rightHndl);
	
	if( leftSize != rightSize ) {
		 result = false;
	} else {
		SInt8 leftState = HGetState(leftHndl);
		SInt8 rightState = HGetState(rightHndl);
		HLock(leftHndl);
		HLock(rightHndl);
		
		char *l = *leftHndl;
		char *r = *rightHndl;
		for ( UInt16 i = 0; i < leftSize; i++ ) {
			if ( *l++ != *r++ ) {
				result = false;
				break;
			}
		}
		HSetState(leftHndl, leftState);
		HSetState(rightHndl, rightState);
	}
	return result;
}


// ---------------------------------------------------------------------------
//   HasExtension													[static]
// ---------------------------------------------------------------------------

Boolean 
UCompareUtils::HasExtension(FSSpec * inFSSpec, char * inExtension)
{
	Boolean	hasExtension = false;
	
	CFURLRef nameUrl = CFURLCreateWithBytes(kCFAllocatorDefault, 
											(const UInt8 * ) inFSSpec->name + 1, inFSSpec->name[0], 
											kCFStringEncodingMacRoman, NULL);
	if (nameUrl) {
		CFStringRef fileExtRef = CFURLCopyPathExtension(nameUrl);
		if (fileExtRef) {
			CFStringRef inExtRef = CFStringCreateWithCString(kCFAllocatorDefault, inExtension, kCFStringEncodingMacRoman);
			if (inExtRef) {
				hasExtension = (CFStringCompare(fileExtRef, inExtRef, kCFCompareCaseInsensitive) == 0);
				CFRelease(inExtRef);
			} 
			CFRelease(fileExtRef);
		} 
		CFRelease(nameUrl);
	} 
	
	return hasExtension;
}


#pragma mark -


// ================================================================
//      Class CTypeComparator
// ================================================================
// String comparator class to build tables sorted alphabetically

CTypeComparator::CTypeComparator() {}

CTypeComparator::~CTypeComparator() {}

SInt32
CTypeComparator::Compare(
	const void*		inItemOne,
	const void*		inItemTwo,
	UInt32			inSizeOne,
	UInt32			inSizeTwo) const
{
#pragma unused(inSizeOne, inSizeTwo)

	return ::CompareText(inItemOne, inItemTwo, 4, 4, nil);
}



// ================================================================
//      Class CTypeItemComparator
// ================================================================
// String comparator class to build tables sorted alphabetically

CTypeItemComparator::CTypeItemComparator() {}

CTypeItemComparator::~CTypeItemComparator() {}

SInt32
CTypeItemComparator::Compare(
							 const void*	inItemOne,
							 const void*	inItemTwo,
							 UInt32			inSizeOne,
							 UInt32			inSizeTwo) const
{
#pragma unused(inSizeOne, inSizeTwo)	
	ResType	typeOne = (*(CRezType **) inItemOne)->GetType();
	ResType	typeTwo = (*(CRezType **) inItemTwo)->GetType();
	return ::CompareText( &typeOne, &typeTwo, 4, 4, nil);
}


// ================================================================
//      Class CPickerViewComparator
// ================================================================
// String comparator class to build picker windows sorted numerically

CPickerViewComparator::CPickerViewComparator() {}

CPickerViewComparator::~CPickerViewComparator() {}

SInt32
CPickerViewComparator::Compare(
							   const void*	inItemOne,
							   const void*	inItemTwo,
							   UInt32		inSizeOne,
							   UInt32		inSizeTwo) const
{
#pragma unused(inSizeOne, inSizeTwo)
	
	CPickerView* pickerOne = *(CPickerView **) inItemOne;
	CPickerView* pickerTwo = *(CPickerView **) inItemTwo;
	
	return ( pickerOne->GetPaneID() - pickerTwo->GetPaneID() );
}


PP_End_Namespace_PowerPlant
