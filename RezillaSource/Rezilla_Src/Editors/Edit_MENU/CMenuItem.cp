// ===========================================================================
// CMenuItem.cp
// 
//                       Created: 2005-03-10 09:12:57
//             Last modification: 2005-03-11 16:42:27
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
//  CMenuItem													[public]
// ---------------------------------------------------------------------------

CMenuItem::CMenuItem()
{
	SetValues( "\p", 0, 0, 0, 0);
	InitExtendedData();
}


// ---------------------------------------------------------------------------
//  CMenuItem													[public]
// ---------------------------------------------------------------------------

CMenuItem::CMenuItem(Str255	inTitle,
					UInt8	inIconID, 
					UInt8	inShortcut, 
					UInt8	inMark, 
					UInt8	inStyle)
{
	SetValues( inTitle, inIconID, inShortcut, inMark, inStyle);
	InitExtendedData();
}


// ---------------------------------------------------------------------------
//  CMenuItem													[public]
// ---------------------------------------------------------------------------

CMenuItem::CMenuItem(LHandleStream * inStream)
{
	InstallData(inStream);
	InitExtendedData();
}


// ---------------------------------------------------------------------------
//  ~CMenuItem													[public]
// ---------------------------------------------------------------------------

CMenuItem::~CMenuItem()
{
}


// ---------------------------------------------------------------------------
//  InstallData											[public]
// ---------------------------------------------------------------------------

void
CMenuItem::InstallData(LHandleStream * inStream)
{
	*inStream >> mTitle;
	*inStream >> mIconID;
	*inStream >> mShortcut;
	*inStream >> mMark;
	*inStream >> mStyle;
}


// ---------------------------------------------------------------------------
//  SendData											[public]
// ---------------------------------------------------------------------------

void
CMenuItem::SendData(LHandleStream * outStream)
{
	*outStream << mTitle;
	*outStream << mIconID;
	*outStream << mShortcut;
	*outStream << mMark;
	*outStream << mStyle;
}


// ---------------------------------------------------------------------------
//  InitExtendedData											[public]
// ---------------------------------------------------------------------------

void
CMenuItem::InitExtendedData()
{
	mEntryType = 0;
	mCommandID = 0;
	mModifiers = 0;
	mIconType = 0;
	mIconHandle = 0;
	mEncoding = 0;
	mRefcon1 = 0;
	mRefcon2 = 0;
	mSubmenuID = 0;
	mFontID = 0;
	mSubstituteGlyph = 0;
}


// ---------------------------------------------------------------------------
//  InstallExtendedData									[public]
// ---------------------------------------------------------------------------

OSErr
CMenuItem::InstallExtendedData(LHandleStream * inStream)
{
	OSErr		error = noErr;
	
	*inStream >> mEntryType;
	
	// Check that the entry type corresponds to the MENU data
	// 0 means separator
	
	if (mEntryType) {
		*inStream >> mCommandID;
		*inStream >> mModifiers;
		*inStream >> mIconType;
		*inStream >> mIconHandle;
		*inStream >> mEncoding;
		*inStream >> mRefcon1;
		*inStream >> mRefcon2;
		*inStream >> mSubmenuID;
		*inStream >> mFontID;
		*inStream >> mSubstituteGlyph;
	} 
	
	return error;
}


// ---------------------------------------------------------------------------
//  SendData												[public]
// ---------------------------------------------------------------------------

void
CMenuItem::SendExtendedData(LHandleStream * outStream)
{
	*outStream << mEntryType;
	if (mEntryType) {
		*outStream << mCommandID;
		*outStream << mModifiers;
		*outStream << mIconType;
		*outStream << mIconHandle;
		*outStream << mEncoding;
		*outStream << mRefcon1;
		*outStream << mRefcon2;
		*outStream << mSubmenuID;
		*outStream << mFontID;
		*outStream << mSubstituteGlyph;
	}
}


// ---------------------------------------------------------------------------
//  GetValues														[public]
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
//  SetValues														[public]
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




