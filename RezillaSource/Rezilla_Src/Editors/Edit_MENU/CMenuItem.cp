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
	mTitle[0] = 0;
	mIconID = 0;
	mShortcut = 0;
	mMark = 0;
	mStyle = 0;
}


// ---------------------------------------------------------------------------
//  CMenuItem												[public]
// ---------------------------------------------------------------------------

CMenuItem::CMenuItem(Str255	inTitle,
							UInt8	inIconID, 
							UInt8	inShortcut, 
							UInt8	inMark, 
							UInt8	inStyle)
{
	SetValues( inTitle, inIconID, inShortcut, inMark, inStyle);
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
	*inStream >> mTitle;
	*inStream >> mIconID;
	*inStream >> mShortcut;
	*inStream >> mMark;
	*inStream >> mStyle;
}


// ---------------------------------------------------------------------------
//  SendDataToStream												[public]
// ---------------------------------------------------------------------------

void
CMenuItem::SendDataToStream(LHandleStream * outStream)
{
	*outStream << mTitle;
	*outStream << mIconID;
	*outStream << mShortcut;
	*outStream << mMark;
	*outStream << mStyle;
}


// ---------------------------------------------------------------------------
//  GetValues												[public]
// ---------------------------------------------------------------------------

void
CMenuItem::GetValues(Str255 outTitle, UInt8 & outIconID, UInt8 & outShortcut, 
					   UInt8 outMark, UInt8 & outStyle)
{
	LString::CopyPStr(mTitle, outTitle);
	outIconID = mIconID;
	outShortcut = mShortcut;
	outMark = mMark;
	outStyle = mStyle;
}
 

// ---------------------------------------------------------------------------
//  SetValues												[public]
// ---------------------------------------------------------------------------

void
CMenuItem::SetValues(Str255 inTitle, UInt8 inIconID, UInt8 inShortcut, 
					   UInt8 inMark, UInt8 inStyle)
{
	LString::CopyPStr(inTitle, mTitle);
	mIconID = inIconID;
	mShortcut = inShortcut;
	mMark = inMark;
	mStyle = inStyle;
}




