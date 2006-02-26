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
#include "CICNS_Stream.h"
#include "RezillaConstants.h"
#include "UMiscUtils.h"


// ---------------------------------------------------------------------------
//  CICNS_Member													[public]
// ---------------------------------------------------------------------------
// The minimal size of an icon member 
// is 8 = sizeof(OSType) + sizeof(SInt32)

CICNS_Member::CICNS_Member(OSType inType)
{
	mType = inType;
	mIconSize = 0;
	mIconData = nil;	
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
//  CICNS_Member													[public]
// ---------------------------------------------------------------------------

CICNS_Member::CICNS_Member(CICNS_Stream * inStream)
{
	mIconSize = 0;
	mIconData = nil;	
	InstallDataStream(inStream);
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
//  InstallDataStream												[public]
// ---------------------------------------------------------------------------

void
CICNS_Member::InstallDataStream(CICNS_Stream * inStream)
{
	SInt32 theSize;
	
	*inStream >> mType;
	*inStream >> theSize;

	if (theSize > 8) {
		mIconSize = theSize - 8;
	} 
	
	mIconData = NewHandle(mIconSize);
	if (mIconData) {
		inStream->GetBytes(*mIconData, mIconSize);
	} 
}


// ---------------------------------------------------------------------------
//  SendDataToStream												[public]
// ---------------------------------------------------------------------------

void
CICNS_Member::SendDataToStream(CICNS_Stream * outStream)
{
	*outStream << mType;
	*outStream << (mIconSize + 8);
	
	if (mIconData) {
		outStream->PutBytes(*mIconData, mIconSize);
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

	::SetHandleSize(outHandle, mIconSize);
	OSErr error = ::MemError();
	if (error == noErr) {
		::BlockMoveData(*mIconData, *outHandle, mIconSize);
	}
}
 

// ---------------------------------------------------------------------------
//  SetValues														[public]
// ---------------------------------------------------------------------------

void
CICNS_Member::SetValues(OSType inType, SInt32 inSize, Handle inHandle)
{
	mType = inType;
	mIconSize = inSize;
	
	if (mIconData == nil) {
		mIconData = NewHandle(mIconSize);
	} else {
		::SetHandleSize(mIconData, inSize);
	}
	
	OSErr error = ::MemError();
	if (error == noErr) {
		::BlockMoveData(*inHandle, *mIconData, inSize);
	}
}



