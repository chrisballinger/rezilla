// ===========================================================================
// UMiscUtils.cp					
//                       Created: 2003-05-13 20:06:23
//             Last modification: 2004-06-09 09:54:36
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
#include "CRezillaApp.h"
#include "RezillaConstants.h"
#include "UMiscUtils.h"

#include <PP_KeyCodes.h>

#include <LPopupButton.h>
#include <LComparator.h>
#include <Drag.h>

#include <string.h>


PP_Begin_Namespace_PowerPlant



// ---------------------------------------------------------------------------
//  • PStringToOSType											[static]
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
//  • OSTypeToPString											[static]
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
//  •  HFSNameToUnicodeName										[static]
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
//	• MakePath												[static]
// ---------------------------------------------------------------------------

OSErr
UMiscUtils::MakePath(FSSpec* inFileSpec, Str255 outPath, short inWidth)
{
	FSRef		theFSRef;
	short 		pathLength;
	char 		pathName[256];
	OSErr		error;
	
	error = FSpMakeFSRef(inFileSpec, &theFSRef);
	error = FSRefMakePath(&theFSRef, (UInt8 *) pathName, 255);	
	pathName[255] = 0;
	if (error == noErr) {
		pathLength = strlen(pathName);
		::TruncText(inWidth, pathName, &pathLength, truncMiddle) ;
		CopyCStringToPascal(pathName, outPath);
	}
	return error;
}


// ---------------------------------------------------------------------------
//	• CopyFSSpec											[static]
// ---------------------------------------------------------------------------

void
UMiscUtils::CopyFSSpec(FSSpec& srcFileSpec, FSSpec& trgtFileSpec)
{
	trgtFileSpec.vRefNum = srcFileSpec.vRefNum;
	trgtFileSpec.parID = srcFileSpec.parID;
	LString::CopyPStr(srcFileSpec.name, trgtFileSpec.name);
}


// ------------------------------------------------------------------------------
//  •  GetTypeFromScrap										[static]
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
//	• IsValidHexadecimal										[static]				  
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
//	• IsValidHexadecimal										[static]
// ---------------------------------------------------------------------------

Boolean 
UMiscUtils::IsValidHexadecimal(Handle inHandle)
{
    StHandleLocker locker(inHandle);
    
    return UMiscUtils::IsValidHexadecimal(*inHandle, ::GetHandleSize(inHandle) );
}


// ---------------------------------------------------------------------------
//	• CompareStr255												[static]
// ---------------------------------------------------------------------------

SInt16 
UMiscUtils::CompareStr255(Str255 * leftString, Str255 * rightString)
{
	return LString::CompareBytes((*leftString) + 1, (*rightString) + 1, (*leftString)[0], (*rightString)[0]);
}


// ---------------------------------------------------------------------------
//	• IdenticalHandles												[static]
// ---------------------------------------------------------------------------

Boolean 
UMiscUtils::HandlesAreIdentical(const Handle leftHndl, const Handle rightHndl)
{
	Boolean result = true;
	Size leftSize = GetHandleSize(leftHndl);
	Size rightSize = GetHandleSize(rightHndl);
	
	if( leftSize != rightSize ) {
		 result = false;
	} else {
		SInt8 leftState = HGetState(leftHndl);
		SInt8 rightState = HGetState(rightHndl);
		HLock(leftHndl);
		HLock(rightHndl);
		
		char *l = *leftHndl;
		char *r = *rightHndl;
		for ( UInt16 i = 0; i < leftSize; i++ ) {
			if ( *l++ != *r++ ) {
				result = false;
				break;
			}
		}
		HSetState(leftHndl, leftState);
		HSetState(rightHndl, rightState);
	}
	return result;
}


// ---------------------------------------------------------------------------
//	• GetDragFileData										[static]
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


// ---------------------------------------------------------------------------
//	• FontSizeExists											[private]
// ---------------------------------------------------------------------------
// The 'inPopup' argument is a pointer to a Font popup menu.

Boolean
UMiscUtils::FontSizeExists(LPopupButton * inPopup, SInt32 inSize, SInt32 &outItemIndex)
{
	OSErr	itemMatches = 0;
	SInt16	i;
	Str255	theMenuText;
	SInt32	theMenuSize;
	
	// See if inSize matches some menu item
	for ( i= kFirstSizeMenuItem ; i<= kLastSizeMenuItem ; i++ ) {
		::GetMenuItemText( inPopup->GetMacMenuH(), i, theMenuText );
		::StringToNum( theMenuText, &theMenuSize );
		if ( inSize == theMenuSize)
		{
			itemMatches = true;
			outItemIndex = i;
			break;
		}	
	}
	
	return itemMatches;
}


// ---------------------------------------------------------------------------
//	• FontIndexFromFontNum											[private]
// ---------------------------------------------------------------------------
// The 'inPopup' argument is a pointer to a Font popup menu.

SInt32
UMiscUtils::FontIndexFromFontNum(LPopupButton * inPopup, SInt16 inFNum) 
{
	SInt32	i;
	SInt16	theFontNum;
	Str255	theMenuText;
	Boolean foundIt = false;
	MenuRef	theMenuRef = inPopup->GetMacMenuH();
	
	// See if inFNum matches some menu item
	for ( i = 1 ; i<= ::CountMenuItems(theMenuRef) ; i++ ) {
		::GetMenuItemText( theMenuRef, i, theMenuText );
		::GetFNum(theMenuText,&theFontNum);
		if ( inFNum == theFontNum) {
			foundIt = true;
			break;
		}	
	}
	if (!foundIt) {
		// Put the OS Application font
		return ::GetAppFont();
	}
	
	return i;
}


// ---------------------------------------------------------------------------
//	• SizeIndexFromSizeValue											[private]
// ---------------------------------------------------------------------------
// The 'inPopup' argument is a pointer to a Size popup menu.

SInt32
UMiscUtils::SizeIndexFromSizeValue(LPopupButton * inPopup, SInt16 inSize) 
{
	SInt32	i, theSize;
	Str255	theSizeString;
	Boolean foundIt = false;
	MenuRef	theMenuRef = inPopup->GetMacMenuH();
	
	// See if inSize matches some menu item. Don't look at the last item.
	for ( i = 1 ; i< ::CountMenuItems(theMenuRef) ; i++ ) {
		::GetMenuItemText( theMenuRef, i, theSizeString );
		::StringToNum( theSizeString, &theSize );
		if ( inSize == theSize) {
			foundIt = true;
			break;
		}	
	}
	if (!foundIt) {
		// Put the value in the 'Other' item
		LStr255	theLine( "\pOther (" );
		::NumToString( inSize, theSizeString );
		theLine += theSizeString;
		theLine += "\p)…";
		// Set the menu item text.
		::SetMenuItemText( inPopup->GetMacMenuH(), kLastSizeMenuItem + 2, theLine );					
		return (kLastSizeMenuItem + 2);
	} else {
		::SetMenuItemText( inPopup->GetMacMenuH(), kLastSizeMenuItem + 2, LStr255("\pOther…"));					
	}
	
	return i;
}


// 
// // ---------------------------------------------------------------------------
// //	• GetStyleFromMenu											[private]
// // ---------------------------------------------------------------------------
// // The 'inPopup' argument is a pointer to a Style popup.
// 
// SInt16
// UMiscUtils::GetStyleFromMenu(LPopupButton * inPopup)
// {
// }
 
 


// ---------------------------------------------------------------------------
//	• MetricsFromTraits											[private]
// ---------------------------------------------------------------------------
void
UMiscUtils::MetricsFromTraits(ConstTextTraitsPtr inTextTraits)
{
	FontInfo metrics;
	
	UTextTraits::SetPortTextTraits( inTextTraits );
	::GetFontInfo( &metrics );
		
	CRezillaApp::sBasics.charWidth = metrics.widMax;
// 	CRezillaApp::sBasics.charWidth = CharWidth('0');
	CRezillaApp::sBasics.charHeight = metrics.ascent + metrics.descent + metrics.leading;
}


// ================================================================
//  •  Class CTypeComparator
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
//  •  Class CTypeItemComparator
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
