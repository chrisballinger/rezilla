// ===========================================================================
// CAeteProperty.cp
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-01-22 10:41:28
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CAeteProperty.h"
#include "CAeteStream.h"


// ---------------------------------------------------------------------------
//  CAeteProperty												[public]
// ---------------------------------------------------------------------------

CAeteProperty::CAeteProperty()
{
	mName[0] = 0;
	mID = 0;
	mType = 0;
	mDescription[0] = 0;
	mFlags = 0;
}


// ---------------------------------------------------------------------------
//  CAeteProperty												[public]
// ---------------------------------------------------------------------------

CAeteProperty::CAeteProperty(Str255 inName, 
							  OSType inID, 
							  OSType inType, 
							  Str255 inDescription, 
							  UInt16 inFlags)
{
	SetValues( inName, inID, inType, inDescription, inFlags);
}


// ---------------------------------------------------------------------------
//  CAeteProperty												[public]
// ---------------------------------------------------------------------------

CAeteProperty::CAeteProperty(CAeteStream * inStream)
{
	*inStream >> mName;
	inStream->AlignBytes();

	*inStream >> mID;
	*inStream >> mType;
	
	*inStream >> mDescription;
	inStream->AlignBytes();

	*inStream >> mFlags;
}


// ---------------------------------------------------------------------------
//  ~CAeteProperty												[public]
// ---------------------------------------------------------------------------

CAeteProperty::~CAeteProperty()
{
}


// ---------------------------------------------------------------------------
//  InstallDataStream												[public]
// ---------------------------------------------------------------------------

void
CAeteProperty::InstallDataStream()
{
}


// ---------------------------------------------------------------------------
//  SendDataToStream												[public]
// ---------------------------------------------------------------------------

void
CAeteProperty::SendDataToStream(CAeteStream * outStream)
{
}


// ---------------------------------------------------------------------------
//  GetValues												[public]
// ---------------------------------------------------------------------------

void
CAeteProperty::GetValues(Str255 outName, OSType & outID, OSType & outType, 
					   Str255 outDescription, UInt16 & outFlags)
{
	LString::CopyPStr(mName, outName);
	LString::CopyPStr(mDescription, outDescription);
	outID = mID;
	outType = mType;
	outFlags = mFlags;
}
 

// ---------------------------------------------------------------------------
//  SetValues												[public]
// ---------------------------------------------------------------------------

void
CAeteProperty::SetValues(Str255 inName, OSType inID, OSType inType, 
					   Str255 inDescription, UInt16 inFlags)
{
	LString::CopyPStr(inName, mName);
	LString::CopyPStr(inDescription, mDescription);
	mID = inID;
	mType = inType;
	mFlags = inFlags;
}

