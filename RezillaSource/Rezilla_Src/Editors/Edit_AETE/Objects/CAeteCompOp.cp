// ===========================================================================
// CAeteCompOp.cp
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-01-30 21:00:31
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CAeteCompOp.h"
#include "CAeteStream.h"
#include "RezillaConstants.h"


// ---------------------------------------------------------------------------
//  CAeteCompOp												[public]
// ---------------------------------------------------------------------------

CAeteCompOp::CAeteCompOp()
{
	mName[0] = 0;
	mType = 0;
	mDescription[0] = 0;
}


// ---------------------------------------------------------------------------
//  CAeteCompOp												[public]
// ---------------------------------------------------------------------------

CAeteCompOp::CAeteCompOp(Str255 inName, 
						 OSType inType, 
						 Str255 inDescription)
{
	SetValues( inName, inType, inDescription);
}


// ---------------------------------------------------------------------------
//  CAeteCompOp												[public]
// ---------------------------------------------------------------------------

CAeteCompOp::CAeteCompOp(CAeteStream * inStream)
{
	InstallDataStream(inStream);
}


// ---------------------------------------------------------------------------
//  ~CAeteCompOp												[public]
// ---------------------------------------------------------------------------

CAeteCompOp::~CAeteCompOp()
{
}


// ---------------------------------------------------------------------------
//  InstallDataStream												[public]
// ---------------------------------------------------------------------------

void
CAeteCompOp::InstallDataStream(CAeteStream * inStream)
{
	*inStream >> mName;
	inStream->AlignBytesRead();

	*inStream >> mType;
	
	*inStream >> mDescription;
	inStream->AlignBytesRead();
}


// ---------------------------------------------------------------------------
//  SendDataToStream												[public]
// ---------------------------------------------------------------------------

void
CAeteCompOp::SendDataToStream(CAeteStream * outStream)
{
	*outStream << mName;
	outStream->AlignBytesWrite();
	*outStream << mType;
	*outStream << mDescription;
	outStream->AlignBytesWrite();
}


// ---------------------------------------------------------------------------
//  GetValues												[public]
// ---------------------------------------------------------------------------

void
CAeteCompOp::GetValues(Str255 outName, OSType & outType, Str255 outDescription)
{
	LString::CopyPStr(mName, outName);
	LString::CopyPStr(mDescription, outDescription);
	outType = mType;
}
 

// ---------------------------------------------------------------------------
//  SetValues												[public]
// ---------------------------------------------------------------------------

void
CAeteCompOp::SetValues(Str255 inName, OSType inType, Str255 inDescription)
{
	LString::CopyPStr(inName, mName);
	LString::CopyPStr(inDescription, mDescription);
	mType = inType;
}


