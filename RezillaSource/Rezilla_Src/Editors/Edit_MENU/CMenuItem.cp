// ===========================================================================
// CMenuItem.cp
// 
//                       Created: 2005-03-10 09:12:57
//             Last modification: 2005-03-10 09:56:17
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CMenuItem.h"
#include "RezillaConstants.h"
#include "UMiscUtils.h"

#include <LString.h>
#include <LHandleStream.h>

// ---------------------------------------------------------------------------
//  CMenuItem												[public]
// ---------------------------------------------------------------------------

CMenuItem::CMenuItem()
{
	mName[0] = 0;
	mKeyword = 0;
	mType = 0;
	mDescription[0] = 0;
	mFlags = 0;
}


// ---------------------------------------------------------------------------
//  CMenuItem												[public]
// ---------------------------------------------------------------------------

CMenuItem::CMenuItem(Str255	inName,
							OSType	inKeyword, 
							OSType	inType, 
							Str255	inDescription, 
							UInt16	inFlags)
{
	SetValues( inName, inKeyword, inType, inDescription, inFlags);
}


// ---------------------------------------------------------------------------
//  CMenuItem												[public]
// ---------------------------------------------------------------------------

CMenuItem::CMenuItem(LHandleStream * inStream)
{
	InstallDataStream(inStream);
}


// ---------------------------------------------------------------------------
//  ~CMenuItem												[public]
// ---------------------------------------------------------------------------

CMenuItem::~CMenuItem()
{
}


// ---------------------------------------------------------------------------
//  InstallDataStream												[public]
// ---------------------------------------------------------------------------

void
CMenuItem::InstallDataStream(LHandleStream * inStream)
{
	*inStream >> mName;

	*inStream >> mKeyword;
	*inStream >> mType;
	
	*inStream >> mDescription;

	*inStream >> mFlags;
}


// ---------------------------------------------------------------------------
//  SendDataToStream												[public]
// ---------------------------------------------------------------------------

void
CMenuItem::SendDataToStream(LHandleStream * outStream)
{
	*outStream << mName;
	*outStream << mKeyword;
	*outStream << mType;
	*outStream << mDescription;
	*outStream << mFlags;
}


// ---------------------------------------------------------------------------
//  GetValues												[public]
// ---------------------------------------------------------------------------

void
CMenuItem::GetValues(Str255 outName, OSType & outKeyword, OSType & outType, 
					   Str255 outDescription, UInt16 & outFlags)
{
	LString::CopyPStr(mName, outName);
	LString::CopyPStr(mDescription, outDescription);
	outKeyword = mKeyword;
	outType = mType;
	outFlags = mFlags;
}
 

// ---------------------------------------------------------------------------
//  SetValues												[public]
// ---------------------------------------------------------------------------

void
CMenuItem::SetValues(Str255 inName, OSType inKeyword, OSType inType, 
					   Str255 inDescription, UInt16 inFlags)
{
	LString::CopyPStr(inName, mName);
	LString::CopyPStr(inDescription, mDescription);
	mKeyword = inKeyword;
	mType = inType;
	mFlags = inFlags;
}




