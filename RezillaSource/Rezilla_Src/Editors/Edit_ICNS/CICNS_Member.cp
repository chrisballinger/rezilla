// ===========================================================================
// CICNS_Member.cp
// 
//                       Created: 2006-02-23 15:12:16
//             Last modification: 2006-02-26 12:03:47
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================
// 	type 'icns' {
// 		iconFamilyBegin:
// 			literal longint = 'icns';
// 			unsigned longint = (iconFamilyEnd - iconFamilyBegin) >> 3;
// 			array elementArray {
// 				literal longint;
// 				elementBegin:
// 					longint =   (elementEnd[$$ArrayIndex(elementArray)] 
// 						- elementBegin[$$ArrayIndex(elementArray)] >> 3) + 4;
// 					hex string;
// 				elementEnd:
// 			};
// 		iconFamilyEnd:
// 	};
			 

#include "CICNS_Member.h"
#include "RezillaConstants.h"
#include "UMiscUtils.h"

#include <LHandleStream.h>

// ---------------------------------------------------------------------------
//  CICNS_Member													[public]
// ---------------------------------------------------------------------------

CICNS_Member::CICNS_Member(OSType inType)
{
	SetValues(inType, 0, NULL);
}


// ---------------------------------------------------------------------------
//  CICNS_Member													[public]
// ---------------------------------------------------------------------------
// inSize should be the size of inHandle

CICNS_Member::CICNS_Member(OSType inType, SInt32 inSize, Handle inHandle)
{
	SetValues(inType, inSize, inHandle);
}


// ---------------------------------------------------------------------------
//  ~CICNS_Member													[public]
// ---------------------------------------------------------------------------

CICNS_Member::~CICNS_Member()
{
	if (mIconData != nil) {
		DisposeHandle(mIconData);
	} 
}


// ---------------------------------------------------------------------------
//  GetValues														[public]
// ---------------------------------------------------------------------------

void
CICNS_Member::GetValues(OSType & outType, SInt32 & outSize, Handle & outHandle)
{
	outType = mType;
	outSize = mIconSize;
	outHandle = mIconData;
}
 

// ---------------------------------------------------------------------------
//  SetValues														[public]
// ---------------------------------------------------------------------------

void
CICNS_Member::SetValues(OSType inType, SInt32 inSize, Handle inHandle)
{
	mType = inType;
	mIconSize = inSize;
	
	if (inHandle == nil) {
		mIconData = NewHandle(0);
	} else {
		mIconData = inHandle;
	}
}



