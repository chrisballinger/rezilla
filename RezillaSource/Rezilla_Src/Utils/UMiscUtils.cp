// ===========================================================================
// UMiscUtils.cp					
//                       Created: 2003-05-13 20:06:23
//             Last modification: 2004-10-14 09:16:48
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
#include <UTextTraits.h>

#include <stdio.h>
#include <string.h>
#include "regex.h"


PP_Begin_Namespace_PowerPlant



// ---------------------------------------------------------------------------
//  • PStringToOSType											[static]
// ---------------------------------------------------------------------------

void
UMiscUtils::PStringToOSType(Str255 inString, OSType & outType)
{
	char * theStr = new char[5];
	UInt8 len = inString[0];
	if (len > 4) {
		len = 4;
	} 
	CopyPascalStringToC(inString, theStr);
	for (SInt8 i = 4; i >= len; i--) {
		theStr[i] = 0;
	}
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


// ---------------------------------------------------------------------------
//  • HexNumStringToDecimal											[static]
// ---------------------------------------------------------------------------
// Used to calculate the $nnn hexadecimal values in Hnnn, Cnnn, Tnnn 
// template tags.

void
UMiscUtils::HexNumStringToDecimal(ResType * inTypePtr, SInt32 * outNum)
{
	char str[4];
	char * p = (char *) inTypePtr;
	sprintf(str, "%c%c%c%c", *(p+1), *(p+2), *(p+3), 0);
	::LowercaseText(str, 3, (ScriptCode)0);
	sscanf(str, "%3x", outNum);
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


// ------------------------------------------------------------------------------
//  •  PaddTypeIfNecessary										[static]
// ------------------------------------------------------------------------------
// If a type is shorter than 4 chars, padd it with spaces.

void
UMiscUtils::PaddTypeIfNecessary(Str255 inTypeStr)
{
	if (inTypeStr[0] != 4) {
		for (UInt8 i = 4; i > inTypeStr[0]; i--) {
			inTypeStr[i] = ' ';
		}
		inTypeStr[0] = 4;
	} 
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
//	• BuildDateString												[static]
// ---------------------------------------------------------------------------

Boolean 
UMiscUtils::BuildDateString(UInt32 inTime, Str255 inString)
{
	Boolean result = false;
	
#ifdef RZIL_PantherOrGreater
		CFAbsoluteTime absTime;
		CFStringRef dateRef;
		
		if (inTime != 0) {
			absTime = CFDateGetAbsoluteTime(inTime);
		} else {
			absTime = CFAbsoluteTimeGetCurrent();
		}
		// kCFDateFormatterNoStyle, kCFDateFormatterShortStyle, kCFDateFormatterMediumStyle, 
		// kCFDateFormatterLongStyle, kCFDateFormatterFullStyle
		CFDateFormatterRef formatter = CFDateFormatterCreate(kCFAllocatorDefault, NULL, 
										  kCFDateFormatterShortStyle, kCFDateFormatterLongStyle);
		if (formatter) {
			// 		absTime += kCFAbsoluteTimeIntervalSince1970;
			dateRef = CFDateFormatterCreateStringWithAbsoluteTime(kCFAllocatorDefault, formatter, absTime);
			CFRelease(formatter);
			if (dateRef) {
				CFStringGetPascalString(dateRef, inString, sizeof(inString), kCFStringEncodingMacRoman);
				CFRelease(dateRef);
			} 
		}
		
#else
		Str255      dateStr, timeStr;
		LStr255     datimStr("\p");
		// shortDate, longDate, abbrevDate
		DateString(inTime, shortDate, dateStr, NULL);
		TimeString(inTime, true, timeStr, NULL);
		datimStr += dateStr;
		datimStr += "\p - ";
		datimStr += timeStr;
		LString::CopyPStr(datimStr, inString);
#endif
	
	return result;
}


// ---------------------------------------------------------------------------
//	• ParseDateString												[static]
// ---------------------------------------------------------------------------


Boolean 
UMiscUtils::ParseDateString(Str255 inString, SInt32 * outAbsTime)
{
	Boolean result = false;

#ifdef RZIL_PantherOrGreater

	CFAbsoluteTime	absTime;
	CFStringRef		dateRef;
	CFDateFormatterRef formatter;
	
	formatter = CFDateFormatterCreate(kCFAllocatorDefault, NULL, 
									  kCFDateFormatterShortStyle, kCFDateFormatterLongStyle);
	if (formatter) {
		dateRef = CFStringCreateWithPascalString(NULL, numStr, kCFStringEncodingMacRoman);
		if (dateRef) {
			if (CFDateFormatterGetAbsoluteTimeFromString(formatter, dateRef, NULL, outAbsTime)) {
				// *outAbsTime -= kCFAbsoluteTimeIntervalSince1970;
				result = true;
			}
			CFRelease(dateRef);
		} 
		CFRelease(formatter);
	}
	
#else
	
	OSErr error = noErr;
	struct re_pattern_buffer regex;
	struct re_registers regs;
	const char *		s;
	long				lengthUsed;
	LStr255				subString("\p");
	Size				dataSize;
	const char * 		thepattern = " *([0-9]{1,2}/[0-9]{1,2}/[0-9]{1,2}) *- *([0-9]{1,2}:[0-9]{1,2}:[0-9]{1,2})";
	int 				startpos = 0;
	StringToDateStatus	dateStatus, timeStatus;
	
	// Get the contents of the edit field
	dataSize = inString[0] ;
	char * theBuffer = new char[dataSize+1];
	theBuffer[dataSize] = 0;
	::CopyPascalStringToC( inString, theBuffer );			
	
	// Compile the regexp
	memset(&regex, '\0', sizeof(regex));
	regs.start = regs.end = NULL;
	regs.num_regs = 0;
	
	::re_set_syntax(RE_SYNTAX_POSIX_EXTENDED);
	
	s = ::re_compile_pattern( thepattern, strlen(thepattern), &regex);
	// Error if re_compile_pattern returned non-NULL value
	ThrowIfNot_(s == NULL);
	
	if ( ::re_search(&regex, theBuffer, dataSize, startpos, dataSize, &regs) >= 0 ) {
		LongDateRec		dateTimeRec;
		LongDateTime	longDate;
		DateCacheRecord	cache;
		
		error = ::InitDateCache(&cache);
		
		// Convert date to num
		dateStatus = ::StringToDate(theBuffer + regs.start[1], regs.end[1] - regs.start[1], &cache, &lengthUsed, &dateTimeRec);
		// Convert time to num
		timeStatus = ::StringToTime(theBuffer + regs.start[2], regs.end[2] - regs.start[2], &cache, &lengthUsed, &dateTimeRec);
		result = ( dateStatus <= longDateFound && timeStatus <= longDateFound );
		
		::LongDateToSeconds(&dateTimeRec, &longDate);
		*outAbsTime = (SInt32) longDate;
		
	}
	regfree(&regex);
	
#endif
	
	return result;
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
//	• SetTypeAndCreator										[static]
// ---------------------------------------------------------------------------

void 
UMiscUtils::SetTypeAndCreator(FSSpec inFSSpec, OSType inType, OSType inCreator)
{
	HFileInfo	param;
	OSErr		error;

	param.ioCompletion	= NULL;
	param.ioFDirIndex	= 0;
	param.ioVRefNum		= inFSSpec.vRefNum;
	param.ioNamePtr		= inFSSpec.name;
	param.ioDirID		= inFSSpec.parID;
	
	error = ::PBGetCatInfoSync((CInfoPBPtr)&param);
	if ( inType != (OSType)0x00000000 ) {
		param.ioFlFndrInfo.fdType = inType;
	}
	if ( inCreator != (OSType)0x00000000 ) {
		param.ioFlFndrInfo.fdCreator = inCreator;
	}
	// ioDirID gets clobbered
	param.ioDirID = inFSSpec.parID;
	error = ::PBHSetFInfoSync((HParmBlkPtr)&param);
}


// ---------------------------------------------------------------------------
//	• HasExtension													[static]
// ---------------------------------------------------------------------------

Boolean 
UMiscUtils::HasExtension(FSSpec * inFSSpec, char * inExtension)
{
	Boolean	hasExtension = false;
	
	CFURLRef nameUrl = CFURLCreateWithBytes(kCFAllocatorDefault, 
											(const UInt8 * ) inFSSpec->name + 1, inFSSpec->name[0], 
											kCFStringEncodingMacRoman, NULL);
	if (nameUrl) {
		CFStringRef fileExtRef = CFURLCopyPathExtension(nameUrl);
		if (fileExtRef) {
			CFStringRef inExtRef = CFStringCreateWithCString(kCFAllocatorDefault, inExtension, kCFStringEncodingMacRoman);
			if (inExtRef) {
				hasExtension = (CFStringCompare(fileExtRef, inExtRef, kCFCompareCaseInsensitive) == 0);
				CFRelease(inExtRef);
			} 
			CFRelease(fileExtRef);
		} 
		CFRelease(nameUrl);
	} 
	
	return hasExtension;
}


#pragma mark -

// ---------------------------------------------------------------------------
//	• FontSizeExists											[static]
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
//	• FontIndexFromFontNum											[static]
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
//	• SizeIndexFromSizeValue											[static]
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


// ---------------------------------------------------------------------------
//	• MetricsFromTraits											[static]
// ---------------------------------------------------------------------------
// 	CRezillaApp::sBasics.charWidth = CharWidth('0');

void
UMiscUtils::MetricsFromTraits(ConstTextTraitsPtr inTextTraits)
{
	FontInfo metrics;
	
	UTextTraits::SetPortTextTraits( inTextTraits );
	::GetFontInfo( &metrics );
		
	CRezillaApp::sBasics.charWidth = metrics.widMax;
	CRezillaApp::sBasics.charHeight = metrics.ascent + metrics.descent + metrics.leading;
}


// ---------------------------------------------------------------------------
//	• MetricsFromTraits											[static]
// ---------------------------------------------------------------------------

void
UMiscUtils::MetricsFromTraits(ResIDT inTraitsID)
{
	TextTraitsRecord	traitsRec;

	UTextTraits::LoadTextTraits(inTraitsID, traitsRec);
	MetricsFromTraits(&traitsRec);
}


#pragma mark -


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
