// ===========================================================================
// CAeteProperty.cp
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-01-21 09:19:48
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
							  OSType inId, 
							  OSType inType, 
							  Str255 inDescription, 
							  UInt16 inFlags)
{
	LString::CopyPStr(inName, mName);
	LString::CopyPStr(inDescription, mDescription);
	mID = inId;
	mType = inType;
	mFlags = inFlags;
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


