// ===========================================================================
// UMiscUtils.cp					
//                       Created: 2003-05-13 20:06:23
//             Last modification: 2004-03-05 07:10:30
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2003-2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CRezType.h"
#include "UMiscUtils.h"
#include "FullPath.h"

#include <PP_KeyCodes.h>

// #include <Script.h>
#include <LComparator.h>
#include <Drag.h>


PP_Begin_Namespace_PowerPlant



// ---------------------------------------------------------------------------
//  ¥ PStringToOSType
// ---------------------------------------------------------------------------

void
UMiscUtils::PStringToOSType(Str255 inString, OSType & outType)
{
	char * theStr = new char[5];
	CopyPascalStringToC(inString, theStr);	
	theStr[4] = 0;
	outType = *(OSType*) theStr;
}


// ---------------------------------------------------------------------------
//  ¥ OSTypeToPString
// ---------------------------------------------------------------------------

void
UMiscUtils::OSTypeToPString(OSType inType, Str255 & outString)
{
	char * theType = new char[5];
	theType[4] = 0;
	*(OSType*)theType = inType;
	CopyCStringToPascal(theType, outString);	
}


// ------------------------------------------------------------------------------
//  ¥  HFSNameToUnicodeName
// ------------------------------------------------------------------------------
// Borrowed and adapted from MoreFilesX.c

OSErr
UMiscUtils::HFSNameToUnicodeName(
	ConstStr31Param hfsName,
	HFSUniStr255 *unicodeName)
{
	ByteCount			unicodeByteLength;
	OSStatus			result;
	UnicodeMapping		uMapping;
	TextToUnicodeInfo	tuInfo;
	ByteCount			pascalCharsRead;
	TextEncoding 		textEncodingHint = kTextEncodingMacRoman;
	
	// Make sure output is valid in case we get errors or there's nothing to convert
	unicodeName->length = 0;
	
	uMapping.unicodeEncoding = ::CreateTextEncoding(kTextEncodingUnicodeV2_0,
												  kUnicodeCanonicalDecompVariant, kUnicode16BitFormat);
	uMapping.otherEncoding = ::GetTextEncodingBase(textEncodingHint);
	uMapping.mappingVersion = kUnicodeUseHFSPlusMapping;
	
	result = ::CreateTextToUnicodeInfo(&uMapping, &tuInfo);
	
	result = ::ConvertFromTextToUnicode(tuInfo, hfsName[0], &hfsName[1],
									  0, 0, NULL, 0, NULL, sizeof(unicodeName->unicode),
									  &pascalCharsRead, &unicodeByteLength, unicodeName->unicode);
	
	// Convert from byte count to char count
	unicodeName->length = unicodeByteLength / sizeof(UniChar);
	return result;
}


// ---------------------------------------------------------------------------
//	¥ MakePath										[private]
// ---------------------------------------------------------------------------

OSErr
UMiscUtils::MakePath(FSSpec* inFileSpec, Str255 outPath, short inWidth)
{
	short pathLength;
	Handle pathHndl = NULL;
	char * pathName;
	OSErr err = ::FSpGetFullPath(inFileSpec, &pathLength, &pathHndl);
	if (err == noErr) {
		HLock(pathHndl);
		pathName = new char[pathLength + 1];
		BlockMoveData(*pathHndl, pathName, pathLength);
		pathName[pathLength] = 0;
		HUnlock(pathHndl);
		DisposeHandle(pathHndl);			
		::TruncText(inWidth, pathName, &pathLength, truncMiddle) ;
		// On output pathLength has the new length
		pathName[pathLength] = 0;
		CopyCStringToPascal(pathName, outPath);	
	} 
	return err;
}


// ---------------------------------------------------------------------------
//	¥ CopyFSSpec										[private]
// ---------------------------------------------------------------------------

void
UMiscUtils::CopyFSSpec(FSSpec& srcFileSpec, FSSpec& trgtFileSpec)
{
	trgtFileSpec.vRefNum = srcFileSpec.vRefNum;
	trgtFileSpec.parID = srcFileSpec.parID;
	LString::CopyPStr(srcFileSpec.name, trgtFileSpec.name);
}


// ------------------------------------------------------------------------------
//  ¥  GetTypeFromScrap
// ------------------------------------------------------------------------------

OSErr
UMiscUtils::GetTypeFromScrap(ResType & outType)
{
	OSErr error = noErr;
	ScrapRef	scrap;
    ScrapFlavorInfo info;
    UInt32  infoCount = 1;
	
	::GetCurrentScrap(&scrap);
	error = ::GetScrapFlavorInfoList(scrap, &infoCount, &info);		
    outType = info.flavorType;

	return error;
}


// ---------------------------------------------------------------------------
//	¥ IsValidHexadecimal										  
// ---------------------------------------------------------------------------

Boolean 
UMiscUtils::IsValidHexadecimal(Ptr inPtr, ByteCount inByteCount)
{
    Boolean onlyHex = true;
    UInt8 readChar;

	LDataStream theDataStream(inPtr, inByteCount);
    
    for (UInt32 i = 1; i <= inByteCount; i++) {
	theDataStream >> readChar;
	if ( (readChar < 0x30)
	    || (readChar > 0x39 && readChar < 0x41)
	    || (readChar > 0x46 && readChar < 0x61)
	    || (readChar > 0x66) ) {
	    onlyHex = false;
	    break;
	}
    } 
    
    return onlyHex;
}


// ---------------------------------------------------------------------------
//	¥ IsValidHexadecimal										  
// ---------------------------------------------------------------------------

Boolean 
UMiscUtils::IsValidHexadecimal(Handle inHandle)
{
    StHandleLocker locker(inHandle);
    
    return UMiscUtils::IsValidHexadecimal(*inHandle, ::GetHandleSize(inHandle) );
}


// ---------------------------------------------------------------------------
//	¥ CompareStr255										  
// ---------------------------------------------------------------------------

SInt16 
UMiscUtils::CompareStr255(Str255 * leftString, Str255 * rightString)
{
	return LString::CompareBytes((*leftString) + 1, (*rightString) + 1, (*leftString)[0], (*rightString)[0]);
}


// ---------------------------------------------------------------------------
//	¥ GetDragFileData										  
// ---------------------------------------------------------------------------
// If the flavour data is an HFSFlavor structure, retrieve it.

Boolean 
UMiscUtils::GetDragFileData(DragReference inDragRef, ItemReference inItemRef, HFSFlavor& fileData)
{
	Size size;
	OSErr err = ::GetFlavorDataSize(inDragRef, inItemRef, flavorTypeHFS, &size);
	
	return (err == noErr 
			&& size == sizeof(HFSFlavor) 
			&& ::GetFlavorData(inDragRef, inItemRef, 
							flavorTypeHFS, &fileData, &size, 0) == noErr);
}



// ================================================================
//  ¥  Class CTypeComparator
// ================================================================
// String comparator class to build tables sorted alphabetically

CTypeComparator::CTypeComparator() {}

CTypeComparator::~CTypeComparator() {}

SInt32
CTypeComparator::Compare(
	const void*		inItemOne,
	const void*		inItemTwo,
	UInt32			inSizeOne,
	UInt32			inSizeTwo) const
{
#pragma unused(inSizeOne, inSizeTwo)

	return ::CompareText(inItemOne, inItemTwo, 4, 4, nil);
}



// ================================================================
//  ¥  Class CTypeItemComparator
// ================================================================
// String comparator class to build tables sorted alphabetically

CTypeItemComparator::CTypeItemComparator() {}

CTypeItemComparator::~CTypeItemComparator() {}

SInt32
CTypeItemComparator::Compare(
	void*		inItemOne,
	void*		inItemTwo,
	UInt32		inSizeOne,
	UInt32		inSizeTwo) const
{
#pragma unused(inSizeOne, inSizeTwo)

	CRezType* rezTypeOne = static_cast<CRezType *>(inItemOne);
	CRezType* rezTypeTwo = static_cast<CRezType *>(inItemTwo);
	
	return ::CompareText( (void*) rezTypeOne->GetType(), (void*) rezTypeTwo->GetType(), 4, 4, nil);
}


PP_End_Namespace_PowerPlant
