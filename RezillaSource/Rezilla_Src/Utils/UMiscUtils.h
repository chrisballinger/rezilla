// ===========================================================================
// UMiscUtils.h					
//                       Created: 2003-05-13 20:06:23
//             Last modification: 2006-10-03 11:03:04
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2003-2006
// All rights reserved.
// ===========================================================================

#ifndef _H_UMiscUtils
#define _H_UMiscUtils
#pragma once

#include <PP_Prefix.h>
#include <Carbon.h>

class LPopupButton;

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
// MiscUtils: just as it says...

class UMiscUtils {

public:
	static void		PStringToOSType(Str255 inString, OSType & outType);
	static void		OSTypeToPString(OSType inType, Str255 & outString);
	static OSErr	GetTypeFromScrap(ResType & outType);
	static void		PaddTypeIfNecessary(Str255 inTypeStr);
	static Boolean	SelectType(ResType & outType);
	
	static OSErr	HFSNameToUnicodeName(ConstStr31Param hfsName, HFSUniStr255 *unicodeName);
	static OSErr	MakePath(FSSpec* inFileSpec, Str255 outPath, short inWidth);
	static Boolean	GetDragFileData(DragReference inDragRef, ItemReference inItemRef, HFSFlavor& fileData);

	static Boolean	IsValidHexadecimal(Handle inHandle);
	static Boolean	IsValidHexadecimal(Ptr inPtr, ByteCount inByteCount);
	static Boolean	IsValidHexadecimalAndWhitespace(Handle inHandle);
	static Boolean	IsValidHexadecimalAndWhitespace(Ptr inPtr, ByteCount inByteCount);
	
	static Boolean	BuildDateString(UInt32 inTime, Str255 inString);
	static Boolean	ParseDateString(Str255 inString, SInt32 * outAbsTime);
	static Boolean	SplitCaseValue(Str255 inString, Str255 ** outRightPtr);
	static void		HexNumStringToDecimal(ResType * inTypePtr, SInt32 * outNum);
	static void		VersionStringFromValue(UInt32 inVersion, Str255 & outString);

	static void		CopyFSSpec(FSSpec& srcFileSpec, FSSpec& trgtFileSpec);
	static void		MetricsFromTraits(ConstTextTraitsPtr inTextTraits);
	static void		MetricsFromTraits(ResIDT inTraitsID);
	static Boolean	FontSizeExists(LPopupButton * inPopup, SInt32 inSize, SInt32 &outItemIndex);
	static SInt32	FontIndexFromFontNum(LPopupButton * inPopup, SInt16 inFNum);
	static SInt32	SizeIndexFromSizeValue(LPopupButton * inPopup, SInt16 inSize);
	static void 	SetTypeAndCreator(FSSpec inFSSpec, OSType inType, OSType inCreator);

	static void		ClearMemory( void *, UInt32 inNumBytes );
	static void		SetMemory( void *p, UInt8 toWhat, UInt32 numBytes );
	static Handle	DuplicateHandle( Handle source );
	static void		DisposeHandle( void *h );

	static Boolean	IsShiftKey();
	static Boolean	IsOptionKey();
	
	static void		GetValueFromXml(CFXMLTreeRef inTreeRef, SInt32 & outValue);
	static Boolean	GetBooleanFromXml(CFXMLTreeRef inTreeRef);
	static void		GetStringFromXml(CFXMLTreeRef inTreeRef, Str255 & outString);
	static OSErr	GetOSTypeFromXml(CFXMLTreeRef inTreeRef, OSType & outType);
	static OSErr	GetFlagsFromXml(CFXMLTreeRef inTreeRef, UInt16 & outFlags);
	static OSErr	GetBinaryFromXml(CFXMLTreeRef inTreeRef, Handle * outHandPtr);

	static Boolean	LookForOSTypeInString(Str255 inString, OSType& outType);
};





PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
