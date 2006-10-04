// ===========================================================================
// CTextFileStream.cp					
// 
//                       Created : 2002-06-09 19:38:34
//             Last modification : 2006-10-01 12:27:46
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@users.sourceforge.net>
// www : <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2002-2006
// All rights reserved.
// ===========================================================================
//	A text file (as opposed to binary) which uses a Stream to 
//	access its data fork. Takes care of writing PStrings and CStrings as 
// simple text (ie without length byte or null byte).

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CTextFileStream.h"

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   CTextFileStream							Default Constructor		  [public]
// ---------------------------------------------------------------------------
//	Default encoding is kCFStringEncodingMacRoman

CTextFileStream::CTextFileStream()
{
	mEncoding = kCFStringEncodingMacRoman;
}


// ---------------------------------------------------------------------------
//   CTextFileStream							Constructor				  [public]
// ---------------------------------------------------------------------------
// From CFString.h:
// kCFStringEncodingMacRoman		= 0,
// kCFStringEncodingWindowsLatin1	= 0x0500,
// kCFStringEncodingISOLatin1		= 0x0201,
// kCFStringEncodingNextStepLatin	= 0x0B01,
// kCFStringEncodingASCII			= 0x0600,
// kCFStringEncodingUnicode			= 0x0100,
// kCFStringEncodingUTF8			= 0x08000100,
// kCFStringEncodingNonLossyASCII	= 0x0BFF

CTextFileStream::CTextFileStream(
								 const FSSpec&	inFileSpec,
								 UInt32			inEncoding)

	: LFileStream(inFileSpec)
{
	mEncoding = inEncoding;
}


// ---------------------------------------------------------------------------
//     ~CTextFileStream							Destructor				  [public]
// ---------------------------------------------------------------------------

CTextFileStream::~CTextFileStream()
{
}


// ---------------------------------------------------------------------------
//   WritePString
// ---------------------------------------------------------------------------
// Write a Pascal string to a file stream as a text string (of which the
// first length byte is stripped) in UTF-8 with standard XML entities.
// Return the number of bytes written.
//	
// In kCFStringEncodingMacRoman encoding, don't go through the CFString
// stuff in order to speed things up.
   
SInt32
CTextFileStream::WritePString(ConstStringPtr inString)
{
	SInt32		bytesToWrite = 0;
	
	if (mEncoding == kCFStringEncodingMacRoman) {
		bytesToWrite = WritePStringNoEnc(inString);
	} else {
		CFStringRef	theStr;
		
		theStr = ::CFStringCreateWithPascalString(kCFAllocatorDefault, inString, kCFStringEncodingMacRoman);
		
		if (theStr) {
			bytesToWrite = WriteCoreString(theStr);
			::CFRelease(theStr);
		} 
	}
	
	return bytesToWrite;
}


// ---------------------------------------------------------------------------
//   WriteCString
// ---------------------------------------------------------------------------
// Write a C string to a file stream as a text string (ie strips the ending
// null-byte) in UTF-8 with standard XML entities. Return the number of
// bytes written.
//	
// In kCFStringEncodingMacRoman encoding, don't go through the CFString
// stuff in order to speed things up.

SInt32
CTextFileStream::WriteCString(
	const char *inString)
{
	SInt32		bytesToWrite = 0;
	
	if (mEncoding == kCFStringEncodingMacRoman) {
		bytesToWrite = WriteCStringNoEnc(inString);
	} else {
		CFStringRef	theStr;
		
		theStr = ::CFStringCreateWithCString(kCFAllocatorDefault, inString, kCFStringEncodingMacRoman);
		
		if (theStr) {
			bytesToWrite = WriteCoreString(theStr);
			::CFRelease(theStr);
		} 
	}
	
	return bytesToWrite;
}


// ---------------------------------------------------------------------------
//   WriteCoreString
// ---------------------------------------------------------------------------
//	Write a CFString to a file stream as a text string in mEncoding.
//	Return the number of bytes written.

SInt32
CTextFileStream::WriteCoreString(CFStringRef inStr)
{
	SInt32		bytesToWrite = 0;
	UInt8 *		buffer;
	CFIndex 	numChars, usedBufLen = 0;
	CFIndex		theLen;
	
	if (inStr) {
		theLen = ::CFStringGetLength(inStr);

		// Call CFStringGetBytes with NULL buffer to get the size of the buffer
		numChars = ::CFStringGetBytes(inStr, CFRangeMake(0, theLen),
						 mEncoding, '?', false, NULL, 0, &usedBufLen);
	
		buffer = (UInt8*) malloc(usedBufLen);
		
		if (buffer) {
			numChars = ::CFStringGetBytes(inStr, CFRangeMake(0, theLen),
							 mEncoding, '?', false, buffer, usedBufLen, &usedBufLen);
			
			bytesToWrite += usedBufLen;
			WriteBlock(buffer, usedBufLen);
			free(buffer);
		} 
	} 
	
	return bytesToWrite;
}


// ---------------------------------------------------------------------------
//   WritePStringNoEnc
// ---------------------------------------------------------------------------
// Write a Pascal string to a stream as a MacRoman text string. Return the
// number of bytes written.

SInt32
CTextFileStream::WritePStringNoEnc(ConstStringPtr inString)
{
	SInt32	bytesToWrite = inString[0];
	WriteBlock(inString + 1, bytesToWrite);
	return bytesToWrite;
}


// ---------------------------------------------------------------------------
//   WriteCStringNoEnc
// ---------------------------------------------------------------------------
// Write a C string to a stream as a MacRoman text string (ie strips the
// ending null-byte). Return the number of bytes written.

SInt32
CTextFileStream::WriteCStringNoEnc(
	const char *inString)
{
	SInt32	bytesToWrite = strlen(inString);
	WriteBlock(inString, bytesToWrite);
	return bytesToWrite;
}


// ---------------------------------------------------------------------------
//   WriteOSType
// ---------------------------------------------------------------------------
//	Write a Pascal string to a Stream as a text string (ie strips the first
//	length byte)
//	Return the number of bytes written

SInt32
CTextFileStream::WriteOSType(OSType inType)
{
	char theType[5];
	*(OSType*)theType = inType;
	theType[4] = 0;

	return (WriteCString(theType));
}


// ---------------------------------------------------------------------------
//   WriteSInt32
// ---------------------------------------------------------------------------
//	Write a SInt32 number as text
//	Return the number of bytes written

SInt32
CTextFileStream::WriteSInt32(SInt32 inNum)
{
	Str255	tempString;
	::NumToString(inNum, tempString);

	return ( WritePStringNoEnc(tempString) );
}


// ---------------------------------------------------------------------------
//   WriteSInt16
// ---------------------------------------------------------------------------
//	Write a SInt16 number as text
//	Return the number of bytes written

SInt32
CTextFileStream::WriteSInt16(SInt16 inNum)
{
	return ( WriteSInt32( (SInt32)inNum) );
}


// ---------------------------------------------------------------------------
//   WriteBoolean
// ---------------------------------------------------------------------------
//	Write a Boolean value as text
//	Return the number of bytes written

SInt32
CTextFileStream::WriteBoolean(Boolean inBool)
{
	if (inBool) {
		return (WritePStringNoEnc("\p1"));
	} else {
		return (WritePStringNoEnc("\p0"));
	}
}


// ---------------------------------------------------------------------------
//   WriteByChunks
// ---------------------------------------------------------------------------
//	Write a C string to a Stream as a text string cut down into pieces 
//	separated by a specified separator.
//	Return the number of bytes written.

SInt32
CTextFileStream::WriteByChunks(
		const char *inString, 
		Str255	inPrefix, 
		Str255	inSuffix, 
		SInt32	inLen,
		SInt32	inChunkSize)
{
	SInt32	bytesToWrite = 0;
	bytesToWrite += inLen;
	SInt32	bytesOffset = 0;
	SInt32	chunksCount = inLen / inChunkSize;
	
	for (SInt32 i = 0; i < chunksCount; i++) {
		bytesToWrite += WritePStringNoEnc(inPrefix);
		WriteBlock(inString + bytesOffset, inChunkSize);
		bytesToWrite += WritePStringNoEnc(inSuffix);
		bytesOffset += inChunkSize;
	}
	if (bytesOffset < inLen) {
		bytesToWrite += WritePStringNoEnc(inPrefix);
		WriteBlock(inString + bytesOffset, inLen - bytesOffset);
		bytesToWrite += WritePStringNoEnc(inSuffix);
	} 

	return bytesToWrite;
}


// ---------------------------------------------------------------------------
//   operator << (SInt32)
// ---------------------------------------------------------------------------

CTextFileStream&
CTextFileStream::operator << (SInt32 inNum)
{
	this->WriteSInt32(inNum);
	return (*this);
}

						
// ---------------------------------------------------------------------------
//   operator << (SInt16)
// ---------------------------------------------------------------------------

CTextFileStream&
CTextFileStream::operator << (SInt16 inNum)
{
	this->WriteSInt16(inNum);
	return (*this);
}

						
// ---------------------------------------------------------------------------
//   operator << (Boolean)
// ---------------------------------------------------------------------------

CTextFileStream&
CTextFileStream::operator << (Boolean inBool)
{
	this->WriteBoolean(inBool);
	return (*this);
}


PP_End_Namespace_PowerPlant
