// ===========================================================================
// CICNS_Member.cp
// 
//                       Created: 2006-02-23 15:12:16
//             Last modification: 2006-03-13 15:56:04
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================

#include "CICNS_Member.h"
#include "RezillaConstants.h"
#include "UMiscUtils.h"

#include <LHandleStream.h>


// ---------------------------------------------------------------------------
//  CICNS_Member													[public]
// ---------------------------------------------------------------------------
// inSize should be the size of inHandle

CICNS_Member::CICNS_Member(OSType inType, Handle inHandle)
{
	mModified = false;
	SetValues(inType, inHandle);
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
CICNS_Member::GetValues(OSType & outType, Handle & outHandle)
{
	outType = mType;
	outHandle = mIconData;
}
 

// ---------------------------------------------------------------------------
//  SetValues														[public]
// ---------------------------------------------------------------------------

void
CICNS_Member::SetValues(OSType inType, Handle inHandle)
{
	mType = inType;
	
	if (inHandle == nil) {
		mIconData = NewHandle(0);
	} else {
		mIconData = inHandle;
	}
}



