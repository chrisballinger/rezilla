// ===========================================================================
// UMiscUtils.h					
//                       Created: 2003-05-13 20:06:23
//             Last modification: 2004-03-05 07:05:19
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2003, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#ifndef _H_UMiscUtils
#define _H_UMiscUtils
#pragma once

#include <PP_Prefix.h>
// #include <UKeyFilters.h>

#include <Carbon.h>


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
	static OSErr	HFSNameToUnicodeName(ConstStr31Param hfsName, HFSUniStr255 *unicodeName);
	static OSErr	GetTypeFromScrap(ResType & outType);
	static OSErr	MakePath(FSSpec* inFileSpec, Str255 outPath, short inWidth);
	static Boolean	GetDragFileData(DragReference inDragRef, ItemReference inItemRef, HFSFlavor& fileData);
	static Boolean	IsValidHexadecimal(Handle inHandle);
	static Boolean	IsValidHexadecimal(Ptr inPtr, ByteCount inByteCount);
	static SInt16	CompareStr255(Str255 * leftString, Str255 * rightString);
	static void		CopyFSSpec(FSSpec& srcFileSpec, FSSpec& trgtFileSpec);
};



// ================================================================
//  ¥  Comparator classes
// ================================================================

// ---------------------------------------------------------------------------
// String comparator class to build tables of types sorted alphabetically

class	LComparator;

class CTypeComparator : public LComparator {
public:

						CTypeComparator();
	virtual				~CTypeComparator();

	virtual SInt32		Compare(
								const void*			inItemOne,
								const void* 		inItemTwo,
								UInt32				inSizeOne,
								UInt32				inSizeTwo) const;

};



// ---------------------------------------------------------------------------
// String comparator class to build outline tables of typeItems 
// sorted alphabetically

class CTypeItemComparator : public LComparator {
public:

						CTypeItemComparator();
	virtual				~CTypeItemComparator();

	virtual SInt32		Compare(
								void*		inItemOne,
								void* 		inItemTwo,
								UInt32		inSizeOne,
								UInt32		inSizeTwo) const;

};





PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
