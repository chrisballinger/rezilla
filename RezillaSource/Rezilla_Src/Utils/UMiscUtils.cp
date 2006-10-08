// ===========================================================================
// UMiscUtils.cp
//                       Created: 2003-05-13 20:06:23
//             Last modification: 2006-10-05 18:16:07
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2003-2006
// All rights reserved.
// ===========================================================================


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CRezType.h"
#include "CRezillaApp.h"
#include "CRezTypeChooser.h"
#include "RezillaConstants.h"
#include "UMiscUtils.h"
#include "UMessageDialogs.h"
#include "UCodeTranslator.h"

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
//   PStringToOSType											[static]
// ---------------------------------------------------------------------------

void
UMiscUtils::PStringToOSType(Str255 inString, OSType & outType)
{
	char theStr[5];
	UInt8 len = inString[0];
	if (len > 4) {
		len = 4;
		inString[0] = 4;
	} else if (len > 0 && len < 4) {
		// ZP bugfix #6: if the string is three chars or less, it should be
		// padded with spaces and not zeroes
		// (bd 2006-10-05) Padding should occur only if non-zero length in
		// order to preserve the convention that an empty string means a
		// null type. This is important in the Aete editor for instance.
		UMiscUtils::PaddType(inString);
		// end of ZP bugfix 6
	} 
	CopyPascalStringToC(inString, theStr);
	outType = *(OSType*) theStr;
}


// ---------------------------------------------------------------------------
//   OSTypeToPString											[static]
// ---------------------------------------------------------------------------

void
UMiscUtils::OSTypeToPString(OSType inType, Str255 & outString)
{
	char theType[5];
	theType[4] = 0;
	*(OSType*)theType = inType;
	CopyCStringToPascal(theType, outString);	
}


// ---------------------------------------------------------------------------
//   HexNumStringToDecimal											[static]
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


// ---------------------------------------------------------------------------
//   VersionStringFromValue											[static]
// ---------------------------------------------------------------------------
// Get a string from a version number in 'vers' resource format

void
UMiscUtils::VersionStringFromValue(UInt32 inVersion, Str255 & outString)
{
	UInt8	ver1, ver2, ver3, ver4, ver5;
	Str255	tempString;
	LStr255	theString("\p");
	
	ver1 = ((UInt8 *)&inVersion)[0];
	ver1 = (((ver1 & 0xF0 ) >> 4) * 10) + (ver1 & 0x0F);
	ver2 = (((UInt8 *)&inVersion)[1] & 0xF0) >> 4;
	ver3 = (((UInt8 *)&inVersion)[1] & 0x0F);
	ver4 = ((UInt8 *)&inVersion)[2];
	ver5 = ((UInt8 *)&inVersion)[3];
	::NumToString((long) ver1, tempString);
	theString += tempString ;
	::NumToString((long) ver2, tempString);
	theString += "\p." ;
	theString += tempString ;
	if (ver3) {
		::NumToString((long) ver3, tempString);
		theString += "\p." ;
		theString += tempString ;
	}
	switch (ver4) {
	  case 0x20:
		theString += "\pd" ;
		break;
		
	  case 0x40:
	  theString += "\pa" ;
		break;
		
	  case 0x60:
	  theString += "\pb" ;
		break;
		
	  default:
		break;
	}
	if (ver5) {
		::NumToString((long) ver5, tempString);
		theString += tempString ;
	}
	LString::CopyPStr(theString, outString);
}


// ------------------------------------------------------------------------------
//      HFSNameToUnicodeName										[static]
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
//   MakePath												[static]
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
//   CopyFSSpec											[static]
// ---------------------------------------------------------------------------

void
UMiscUtils::CopyFSSpec(FSSpec& srcFileSpec, FSSpec& trgtFileSpec)
{
	trgtFileSpec.vRefNum = srcFileSpec.vRefNum;
	trgtFileSpec.parID = srcFileSpec.parID;
	LString::CopyPStr(srcFileSpec.name, trgtFileSpec.name);
}


// ------------------------------------------------------------------------------
//      SelectType													[static]
// ------------------------------------------------------------------------------

Boolean
UMiscUtils::SelectType(ResType & outType)
{
	Boolean result = false;
	CRezTypeChooser * rezChooser = new CRezTypeChooser();

	if (rezChooser != NULL) {
		if (rezChooser->RunDialog() == noErr) {
			outType = rezChooser->GetChosenType();
			result = true;
		} 
		delete rezChooser;
	} else {
		UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("TypeChooserNotAvailable"), PPob_SimpleMessage);
	}
	
	return result;
}


// ------------------------------------------------------------------------------
//      GetTypeFromScrap										[static]
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
//   PaddType															[static]
// ------------------------------------------------------------------------------
// If a type is shorter than 4 chars, padd it with spaces.

void
UMiscUtils::PaddType(Str255 inTypeStr)
{
	if (inTypeStr[0] != 4) {
		for (UInt8 i = 4; i > inTypeStr[0]; i--) {
			inTypeStr[i] = ' ';
		}
		inTypeStr[0] = 4;
	} 
}


// ---------------------------------------------------------------------------
//   IsValidHexadecimal													[static]				  
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
//   IsValidHexadecimal													[static]
// ---------------------------------------------------------------------------

Boolean 
UMiscUtils::IsValidHexadecimal(Handle inHandle)
{
    StHandleLocker locker(inHandle);
    
    return UMiscUtils::IsValidHexadecimal(*inHandle, ::GetHandleSize(inHandle) );
}


// ---------------------------------------------------------------------------
//   IsValidHexadecimalAndWhitespace								[static]
// ---------------------------------------------------------------------------
// ZP feature #4, part 4: a new more tolerant checker for pasted hex data.
// Does not bark at line feeds, carriage returns, tabs, and spaces.

Boolean
UMiscUtils::IsValidHexadecimalAndWhitespace(Ptr inPtr, ByteCount inByteCount)
{
    Boolean onlyHex = true;
    UInt8 readChar;
	LDataStream theDataStream(inPtr, inByteCount);
	for (UInt32 i = 1; i <= inByteCount; i++) {
		theDataStream >> readChar;
		if ( ((readChar < 0x30)
		      || (readChar > 0x39 && readChar < 0x41)
			  || (readChar > 0x46 && readChar < 0x61)
		      || (readChar > 0x66))
	        && (readChar!='\n') && (readChar!=0x0D)
			&& (readChar!='\t') && (readChar!=' ') ) {
					onlyHex = false;
					break;
				}
			}
			    return onlyHex;
}


// ---------------------------------------------------------------------------
//   IsValidHexadecimalAndWhitespace								[static]
// ---------------------------------------------------------------------------
Boolean
UMiscUtils::IsValidHexadecimalAndWhitespace(Handle inHandle)
{
    StHandleLocker locker(inHandle);
	return UMiscUtils::IsValidHexadecimalAndWhitespace(*inHandle, ::GetHandleSize(inHandle) );
}
// end of ZP feature 4, part 4


// ---------------------------------------------------------------------------
// 	IsShiftKey
// ---------------------------------------------------------------------------
// There are probably better ways to do this (OSEventAvail, for example),
// but this way is quick and easy and works from trap patches, etc.

Boolean
UMiscUtils::IsShiftKey()
{
	UInt32 modifiers;
	
#ifdef REZILLA_MACH_O
	modifiers = GetCurrentEventKeyModifiers();
#else
	EventRecord		ev;
	EventAvail(everyEvent, &ev);
	modifiers = ev.modifiers;
#endif
	return( (modifiers & shiftKey) != 0 );
}


// ---------------------------------------------------------------------------
// 	IsOptionKey
// ---------------------------------------------------------------------------

Boolean
UMiscUtils::IsOptionKey( void )
{
	UInt32 modifiers;
	
#ifdef REZILLA_MACH_O
	modifiers = GetCurrentEventKeyModifiers();
#else
	EventRecord		ev;
	EventAvail(everyEvent, &ev);
	modifiers = ev.modifiers;
#endif
	return( (modifiers & optionKey) != 0 );
}


// ---------------------------------------------------------------------------
// 	GetValueFromXml
// ---------------------------------------------------------------------------

void
UMiscUtils::GetValueFromXml(CFXMLTreeRef inTreeRef, SInt32 & outValue)
{
	CFXMLTreeRef    valueTree;
	CFXMLNodeRef    valueNode;
	CFStringRef		nodeString;

	outValue = 0;
	
	valueTree = ::CFTreeGetFirstChild(inTreeRef);
	if (valueTree) {
		valueNode = ::CFXMLTreeGetNode(valueTree);
		if (valueNode) {
			nodeString = ::CFXMLNodeGetString(valueNode);
			if (nodeString) {
				outValue = ::CFStringGetIntValue(nodeString);
			} 
		} 
	} 
}


// ---------------------------------------------------------------------------
// 	GetBooleanFromXml
// ---------------------------------------------------------------------------

Boolean
UMiscUtils::GetBooleanFromXml(CFXMLTreeRef inTreeRef)
{
	CFXMLTreeRef    valueTree;
	CFXMLNodeRef    valueNode;
	CFStringRef		nodeString;
	Boolean			theBool = false;
	SInt32			theValue = 0;
	
	valueTree = ::CFTreeGetFirstChild(inTreeRef);
	if (valueTree) {
		valueNode = ::CFXMLTreeGetNode(valueTree);
		if (valueNode) {
			nodeString = ::CFXMLNodeGetString(valueNode);
			if (nodeString) {
				theBool = ( ::CFStringGetIntValue(nodeString) != 0);
			} 
		} 
	} 
	
	return theBool;
}


// ---------------------------------------------------------------------------
// 	GetStringFromXml
// ---------------------------------------------------------------------------
// The XML parser splits strings at every entity. CFShow shows that the
// entity nodes receive an ID 10 (kCFXMLNodeTypeEntityReference). So we
// substitute entities manually here. Of course, this should be the job of
// the parser but kCFXMLParserReplacePhysicalEntities is not implemented
// yet (neither in Panther, nor in Tiger).

void
UMiscUtils::GetStringFromXml(CFXMLTreeRef inTreeRef, Str255 & outString)
{
	CFXMLTreeRef		valueTree;
	CFXMLNodeRef		valueNode;
	CFStringRef			nodeString;
	CFXMLNodeTypeCode	theCode;
	CFIndex				theCount, theIndex;
	CFMutableStringRef	currStr;

	outString[0] = 0;
	currStr = CFStringCreateMutable(kCFAllocatorDefault, 0);

	if (currStr) {
		theCount = CFTreeGetChildCount(inTreeRef);
		for (theIndex = 0; theIndex < theCount; theIndex++) {
			valueTree = ::CFTreeGetChildAtIndex(inTreeRef, theIndex);
			if (valueTree) {
				valueNode = ::CFXMLTreeGetNode(valueTree);
				if (valueNode) {
					nodeString = ::CFXMLNodeGetString(valueNode);
					if (nodeString) {
						theCode = ::CFXMLNodeGetTypeCode(valueNode);
						if (theCode == kCFXMLNodeTypeText) {
							::CFStringAppend(currStr, nodeString);
						} else if (theCode == kCFXMLNodeTypeEntityReference) {
							if ( ! CFStringCompare( nodeString, CFSTR("amp"), 0) ) {
								::CFStringAppendCString(currStr, "&", kCFStringEncodingUTF8);
							} else if ( ! CFStringCompare( nodeString, CFSTR("apos"), 0) ) {
								::CFStringAppendCString(currStr, "'", kCFStringEncodingUTF8);
							} else if ( ! CFStringCompare( nodeString, CFSTR("gt"), 0) ) {
								::CFStringAppendCString(currStr, ">", kCFStringEncodingUTF8);
							} else if ( ! CFStringCompare( nodeString, CFSTR("lt"), 0) ) {
								::CFStringAppendCString(currStr, "<", kCFStringEncodingUTF8);
							} else if ( ! CFStringCompare( nodeString, CFSTR("quot"), 0) ) {
								::CFStringAppendCString(currStr, "\"", kCFStringEncodingUTF8);
							} 
						} 
					}
				}
			}
		}
		
		::CFStringGetPascalString(currStr, outString, sizeof(Str255), kCFStringEncodingMacRoman);
		::CFRelease(currStr);
	} 
}


// ---------------------------------------------------------------------------
// 	GetOSTypeFromXml
// ---------------------------------------------------------------------------

OSErr
UMiscUtils::GetOSTypeFromXml(CFXMLTreeRef inTreeRef, OSType & outType)
{
	OSErr	error = noErr;
	Str255	theString;
	
	GetStringFromXml(inTreeRef, theString);
	if (theString[0] != 0 && theString[0] != 4) {
		error = err_ImportInvalidOSType;
	} 
	if (error == noErr) {
		PStringToOSType( theString, outType);	
	} 
	
	return error;
}


// ---------------------------------------------------------------------------
// 	GetFlagsFromXml
// ---------------------------------------------------------------------------

OSErr
UMiscUtils::GetFlagsFromXml(CFXMLTreeRef inTreeRef, UInt16 & outFlags)
{
	OSErr			error = noErr;
	int             childCount;
	CFXMLTreeRef    xmlTree;
	CFXMLNodeRef    xmlNode;
	CFStringRef		nodeString;
	int             index;
	Boolean			theBool;

	outFlags = 0;

	childCount = CFTreeGetChildCount(inTreeRef);
	for (index = 0; index < childCount; index++) {
		xmlTree = CFTreeGetChildAtIndex(inTreeRef, index);
		if (xmlTree) {
			xmlNode = CFXMLTreeGetNode(xmlTree);
			if (xmlNode) {
				theBool = UMiscUtils::GetBooleanFromXml(xmlTree);
				nodeString = ::CFXMLNodeGetString(xmlNode);
				if (nodeString) {
					if ( ! CFStringCompare( nodeString, CFSTR("ChangeState"), 0) ) {
						outFlags |= theBool ? (1 << kAEUTChangesState): 0;
					} else if ( ! CFStringCompare( nodeString, CFSTR("DirectParamIsReference"), 0) ) {
						outFlags |= theBool ? (1 << kAEUTDirectParamIsReference): 0;
					} else if ( ! CFStringCompare( nodeString, CFSTR("EnumIsExclusive"), 0) ) {
						outFlags |= theBool ? (1 << kAEUTEnumListIsExclusive): 0;
					} else if ( ! CFStringCompare( nodeString, CFSTR("EnumsAreTypes"), 0) ) {
						outFlags |= theBool ? (1 << kAEUTEnumsAreTypes): 0;
					} else if ( ! CFStringCompare( nodeString, CFSTR("IsApostrophe"), 0) ) {
						outFlags |= theBool ? (1 << kAEUTApostrophe): 0;
					} else if ( ! CFStringCompare( nodeString, CFSTR("IsEnumerated"), 0) ) {
						outFlags |= theBool ? (1 << kAEUTEnumerated): 0;
					} else if ( ! CFStringCompare( nodeString, CFSTR("IsFeminine"), 0) ) {
						outFlags |= theBool ? (1 << kAEUTFeminine): 0;
					} else if ( ! CFStringCompare( nodeString, CFSTR("IsListOfItems"), 0) ) {
						outFlags |= theBool ? (1 << kAEUTlistOfItems): 0;
					} else if ( ! CFStringCompare( nodeString, CFSTR("IsMasculine"), 0) ) {
						outFlags |= theBool ? (1 << kAEUTMasculine): 0;
					} else if ( ! CFStringCompare( nodeString, CFSTR("IsOptional"), 0) ) {
						outFlags |= theBool ? (1 << kAEUTOptional): 0;
					} else if ( ! CFStringCompare( nodeString, CFSTR("IsReadWrite"), 0) ) {
						outFlags |= theBool ? (1 << kAEUTReadWrite): 0;
					} else if ( ! CFStringCompare( nodeString, CFSTR("LabeledParam"), 0) ) {
						outFlags |= theBool ? (1 << aeut_LabeledParam): 0;
					} else if ( ! CFStringCompare( nodeString, CFSTR("NonVerbEvent"), 0) ) {
						outFlags |= theBool ? (1 << aeut_NonVerbEvent ): 0;
					} else if ( ! CFStringCompare( nodeString, CFSTR("NotDirectParamIsTarget"), 0) ) {
						outFlags |= theBool ? (1 << kAEUTNotDirectParamIsTarget ): 0;
					} else if ( ! CFStringCompare( nodeString, CFSTR("ParamIsReference"), 0) ) {
						outFlags |= theBool ? (1 << kAEUTParamIsReference): 0;
					} else if ( ! CFStringCompare( nodeString, CFSTR("ParamIsTarget"), 0) ) {
						outFlags |= theBool ? (1 << kAEUTParamIsTarget): 0;
					} else if ( ! CFStringCompare( nodeString, CFSTR("Plural"), 0) ) {
						outFlags |= theBool ? (1 << kAEUTPlural): 0;
					} else if ( ! CFStringCompare( nodeString, CFSTR("PropertyIsReference"), 0) ) {
						outFlags |= theBool ? (1 << kAEUTPropertyIsReference): 0;
					} else if ( ! CFStringCompare( nodeString, CFSTR("ReplyIsReference"), 0) ) {
						outFlags |= theBool ? (1 << kAEUTReplyIsReference): 0;
					} else if ( ! CFStringCompare( nodeString, CFSTR("TightBindingFunction"), 0) ) {
						outFlags |= theBool ? (1 << kAEUTTightBindingFunction): 0;
					} else if ( ! CFStringCompare( nodeString, CFSTR("Reserved"), 0) ) {
						// Ignore
					} else {
						// CFShow(nodeString);
						error = err_ImportUnknownFlagsTag;	
					}
					
					if (error != noErr) { break; } 
				} 
			}
		}
	}
	
	return error;
}


// ---------------------------------------------------------------------------
// 	GetBinaryFromXml
// ---------------------------------------------------------------------------

OSErr
UMiscUtils::GetBinaryFromXml(CFXMLTreeRef inTreeRef, Handle * outHandPtr)
{
	OSErr			error = noErr;
	CFXMLTreeRef    valueTree;
	CFXMLNodeRef    valueNode;
	CFStringRef		nodeString;
	Handle			inHandle = NULL, outHandle = NULL;
	CFIndex			usedBufLen;
	
	valueTree = ::CFTreeGetFirstChild(inTreeRef);
	if (valueTree) {
		valueNode = ::CFXMLTreeGetNode(valueTree);
		if (valueNode) {
			nodeString = ::CFXMLNodeGetString(valueNode);
			if (nodeString) {
				// Extract the Base64 string
				CFIndex	theLen = ::CFStringGetLength(nodeString);
				inHandle = ::NewHandle(theLen);

				if (inHandle != NULL) {
					::CFStringGetBytes(nodeString, CFRangeMake(0, theLen), kCFStringEncodingMacRoman, '?', 
											 false, (UInt8*)*inHandle, theLen, &usedBufLen);
					
					// Strip the space characters
					StStripWhitespaceTranslator stripper(inHandle);
					stripper.FilterOutWhitespace();
					
					// Convert the Base64 data to bytes
					StBase64ToByteTranslator translator(stripper.GetOutHandle());
					try {
						translator.Convert();
					}
					catch (...) {
						error = err_InvalidBase64Data;
						goto done;
					}
				
					outHandle = translator.GetOutHandle();
					// Get a copy of the handle because the translator is a
					// stack-based class and the handle will be deleted
					// when exiting this function
					HandToHand(&outHandle);
				} 
			}
		} 
	} 
	
done:
	if (inHandle) ::DisposeHandle(inHandle);

	*outHandPtr = outHandle;
	
	return error;
}


// ---------------------------------------------------------------------------
//   BuildDateString												[static]
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
//   ParseDateString												[static]
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
	
	if (theBuffer != nil) {
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
		delete theBuffer;
	} 
	
#endif
	
	return result;
}


// ---------------------------------------------------------------------------
//   SplitCaseValue												[static]
// ---------------------------------------------------------------------------
// This function makes two adjacent Pascal strings out of one. It is used 
// in popup menus to handle CASE values. For instance:
//         9abcde=fgh will become 5abcde3fgh.
// On output, it stores a pointer to the RH string. If splitting was successful, 
// the function returns true.

Boolean
UMiscUtils::SplitCaseValue(Str255 inString, Str255 ** outRightPtr)
{
	Boolean split = false;

	if (inString[0]) {
		register char *	p;
		char 	str[256];
		SInt32	len;
		
		CopyPascalStringToC(inString, str);
		p = strrchr((char *) str, '=');
		if (p != nil) {
			split = true;
			len = p - (char *) str;
			inString[len+1] = inString[0] - len - 1;
			inString[0] = len;
			*outRightPtr = (Str255 *) &inString[len+1];
		} 
	}	
	return split;
}


// ---------------------------------------------------------------------------
//   GetDragFileData										[static]
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
//   SetTypeAndCreator										[static]
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



#pragma mark -

// ---------------------------------------------------------------------------
//   FontSizeExists											[static]
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
//   FontIndexFromFontNum											[static]
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
//   SizeIndexFromSizeValue											[static]
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
		theLine += "\p)É";
		// Set the menu item text.
		::SetMenuItemText( inPopup->GetMacMenuH(), kLastSizeMenuItem + 2, theLine );					
		return (kLastSizeMenuItem + 2);
	} else {
		::SetMenuItemText( inPopup->GetMacMenuH(), kLastSizeMenuItem + 2, LStr255("\pOtherÉ"));					
	}
	
	return i;
}


// ---------------------------------------------------------------------------
//   MetricsFromTraits											[static]
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
//   MetricsFromTraits											[static]
// ---------------------------------------------------------------------------

void
UMiscUtils::MetricsFromTraits(ResIDT inTraitsID)
{
	TextTraitsRecord	traitsRec;

	UTextTraits::LoadTextTraits(inTraitsID, traitsRec);
	MetricsFromTraits(&traitsRec);
}


#pragma mark -


// ---------------------------------------------------------------------------
// 	ClearMemory
// ---------------------------------------------------------------------------

void
 UMiscUtils::ClearMemory( void *theBuffer, UInt32 numBytes )
{
	UInt8 *p = (UInt8*) theBuffer;
	
	while( numBytes-- > 0 )
		*p++ = 0;
}


// ---------------------------------------------------------------------------
// 	SetMemory
// ---------------------------------------------------------------------------

void
 UMiscUtils::SetMemory( void *buffer, UInt8 toWhat, UInt32 numBytes )
{
	UInt8	*p = (UInt8*) buffer;
	
	ThrowIfNil_( p );					// can't hurt to check
	
	while( numBytes-- > 0 )
		*p++ = toWhat;
}


// ---------------------------------------------------------------------------
// 	DuplicateHandle
// ---------------------------------------------------------------------------

Handle
 UMiscUtils::DuplicateHandle( Handle source )
{
	ThrowIf_ ( !source || !*source );
	
	SInt32 numBytes = GetHandleSize( source );
	Handle result = NewHandle( numBytes );
	ThrowIfMemFail_( result );
	
	BlockMoveData( *source, *result, numBytes );
	return( result );
}


// ---------------------------------------------------------------------------
// 	DisposeHandle
// ---------------------------------------------------------------------------
// 	Disposes of a handle without having to know if it is a resource manager or
// 	memory manager one.

void
 UMiscUtils::DisposeHandle( void *h )
{
	if ( !h ) return;	
	
	// Assume a resource is purged
	if ( !*(Handle)h )				
	{
		::ReleaseResource( (Handle)h );	
		return;
	}

	Byte flags = ::HGetState( (Handle) h );
	if ( flags & 0x0020 )				/* a resource? */
		::ReleaseResource( (Handle) h );
	else
		::DisposeHandle( (Handle) h );
}

// ---------------------------------------------------------------------------
//  LookForOSTypeInString
// ---------------------------------------------------------------------------
//  Searches for a group of four chars (or less) between two quotes (') in
//  the string. Used in ZP feature #9: improve RSID.

// Boolean UMiscUtils::LookForOSTypeInString(Str255 inString, OSType& outType)
// {
// 	struct re_pattern_buffer regex;
// 	struct re_registers regs;
// 	const char *		comp;
// 	LStr255				subString("\p");
// 	const char * 		pattern = "'([^']{1,4})'";
// // 	const char * 		pattern = "([0-9]+)(-[0-9]*)?";
// 	int					len = inString[0], start = 0;
// 	char				buffer[256];
// 	Boolean				result;
// 	
// 	::CopyPascalStringToC(inString, buffer);
// 	
// 	// Initialize the regex
// 	memset(&regex, '\0', sizeof(regex));
// 	regs.start = regs.end = NULL;
// 	regs.num_regs = 0;
// 	
// 	// Compile the regexp. Failure if re_compile_pattern 
// 	// returns non-NULL value.
// 	::re_set_syntax(RE_SYNTAX_POSIX_EXTENDED);
// 	comp = ::re_compile_pattern( pattern, strlen(pattern), &regex);
// 
// 	if (comp != NULL && ::re_search(&regex, buffer, len, start, len, &regs) >= 0 ) {
// 		subString.Assign( buffer + regs.start[1], regs.end[1] - regs.start[1]);
// 		PStringToOSType(subString, outType);
// 		result = true;
// 	} else {
// 		// Though luck, found nothing. Output a type that is known 
// 		// to be invalid, then return false.
// 		outType = 0;
// 		result = false;
// 	}
// 	regfree(&regex);
// 	
// 	return result;
// }

Boolean UMiscUtils::LookForOSTypeInString(Str255 inString, OSType& outType)
{
	UInt8 length = inString[0], i, len;
	unsigned char temp[5];
	
	for (i=1; i<=length-2; i++) {
		if (inString[i] == '\'') { 
			// Yep, that's a single, escaped quote.
			// the second quote may be anywhere from two to five chars
			// later. Indeed, the template writer should be able to write
			// 'snd' in the label and have it work. two- and one-char length
			// res types are not common, but still exist too.
			len = 0;
			if (inString[i+2] == '\'') {
				len = 1;
			} else if ((i<=length-3) && inString[i+3] == '\'') {
				len = 2;
			} else if ((i<=length-4) && inString[i+4] == '\'') {
				len = 3;
			} else if ((i<=length-5) && inString[i+5] == '\'') {
				len = 4;
			}
			
			if (len) { // found it
				temp[0]=len;
				memcpy(&(temp[1]), &(inString[i+1]), len);
				PStringToOSType(temp, outType);
				return true;
			}
		}
	}
	
	// Though luck, found nothing.
	// output a type that's known to be invalid, then return false.
	outType = 0;
	return false;
}


PP_End_Namespace_PowerPlant
