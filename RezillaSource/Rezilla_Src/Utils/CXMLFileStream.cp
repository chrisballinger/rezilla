// ===========================================================================
// CXMLFileStream.cp					
// 
//                       Created : 2006-09-29 17:28:30
//             Last modification : 2006-10-01 11:55:59
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@users.sourceforge.net>
// www : <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2006
// All rights reserved.
// ===========================================================================
//	A text file (as opposed to binary) which uses a Stream to 
//	access its data fork. Takes care of writing PStrings and CStrings as 
// simple text (ie without length byte or null byte).


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CXMLFileStream.h"

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   CXMLFileStream							Default Constructor		  [public]
// ---------------------------------------------------------------------------
//	Default encoding is kCFStringEncodingUTF8

CXMLFileStream::CXMLFileStream()
{
	mEncoding = kCFStringEncodingUTF8;
	mEncodeTags = false;
}


// ---------------------------------------------------------------------------
//   CXMLFileStream							Constructor				  [public]
// ---------------------------------------------------------------------------

CXMLFileStream::CXMLFileStream(
							   const FSSpec&	inFileSpec,
							   UInt32			inEncoding,
							   Boolean			inEncodeTags)

	: CTextFileStream(inFileSpec, inEncoding)
{
	mEncodeTags = inEncodeTags;
}


// ---------------------------------------------------------------------------
//     ~CXMLFileStream							Destructor				  [public]
// ---------------------------------------------------------------------------

CXMLFileStream::~CXMLFileStream()
{
}


// ---------------------------------------------------------------------------
//   WriteTag
// ---------------------------------------------------------------------------
//	Return the number of bytes written

SInt32
CXMLFileStream::WriteTag(const char *inName, UInt32 inKind, Boolean addNewLine, UInt8 indent)
{
	SInt32	bytesToWrite = 0;
	for (UInt8 i = 0; i < indent; i++) {
		WriteBlock("\t", 1);
	}
	bytesToWrite += indent;
	
	if (inKind != tag_close) {
		bytesToWrite += WriteCStringNoEnc("<");
	} else {
		bytesToWrite += WriteCStringNoEnc("</");
	}
	
	// Don't waste time encoding tags if they are known to be Ascii
	if (mEncodeTags) {
		bytesToWrite += WriteCString(inName);
	} else {
		bytesToWrite += WriteCStringNoEnc(inName);
	}
	
	if (inKind != tag_empty) {
		bytesToWrite += WriteCStringNoEnc(">");
	} else {
		bytesToWrite += WriteCStringNoEnc("/>");
	}
	if (addNewLine) {
		WriteBlock("\r", 1);
		bytesToWrite++;
	} 
	
	return bytesToWrite;
}


// ---------------------------------------------------------------------------
//   WriteTag
// ---------------------------------------------------------------------------
//	Return the number of bytes written

SInt32
CXMLFileStream::WriteTag(ConstStringPtr inName, UInt32 inKind, Boolean addNewLine, UInt8 indent)
{
	char nameStr[256];	
	CopyPascalStringToC(inName, nameStr);
	return ( WriteTag(nameStr, inKind, addNewLine, indent) );
}


// ---------------------------------------------------------------------------
//   WriteCoreString
// ---------------------------------------------------------------------------
// Write a CFString to a file stream as a text string in mEncoding with
// standard XML entities. Return the number of bytes written.
// 
// Note: 
// CFXMLCreateStringByEscapingEntities is a PITA. It stops converting
// the string at the last found entity and does not return the remaining
// characters. In particular, if the original string did not contain any
// entities, CFXMLCreateStringByEscapingEntities returns an empty string!
// <shame>The trick here is to add a > char at the end of the string and
// strip it once the string is converted</shame>.

SInt32
CXMLFileStream::WriteCoreString(CFStringRef	inStr)
{
	SInt32		bytesToWrite = 0;
	UInt8 *		buffer;
	CFIndex 	theLen, numChars, usedBufLen = 0;
	CFStringRef	escStr;
	CFMutableStringRef	tmpStr;	

	if (inStr) {
		tmpStr = ::CFStringCreateMutableCopy(kCFAllocatorDefault, 0, inStr);

		if (tmpStr) {	
			::CFStringAppendCString(tmpStr, ">", 0);
		
			escStr = ::CFXMLCreateStringByEscapingEntities( kCFAllocatorDefault, tmpStr, (CFDictionaryRef)NULL );
			::CFRelease(tmpStr);

			if (escStr) {
				theLen = ::CFStringGetLength(escStr);

				// Call CFStringGetBytes with NULL buffer to get the size of the buffer
				numChars = ::CFStringGetBytes(escStr, CFRangeMake(0, theLen),
								 mEncoding, '?', false, NULL, 0, &usedBufLen);
			
				buffer = (UInt8*) malloc(usedBufLen);
				
				if (buffer) {
					// Trim the last four chars corresponding to the appended > char (converted to &gt;)
					numChars = ::CFStringGetBytes(escStr, CFRangeMake(0, theLen),
									 mEncoding, '?', false, buffer, usedBufLen - 4, &usedBufLen);
					
					bytesToWrite += usedBufLen;
					WriteBlock(buffer, usedBufLen);
					free(buffer);
				} 
				::CFRelease(escStr);
			} 
		} 
	} 
	
	return bytesToWrite;
}


// ---------------------------------------------------------------------------
//   WritePStringEnclosed
// ---------------------------------------------------------------------------
//	Write a Pascal string enclosed in an xml-like pair of tags
//	Return the number of bytes written

SInt32
CXMLFileStream::WritePStringEnclosed(
		ConstStringPtr inString,
		ConstStringPtr inTag, 
		UInt8 indent)
{
	SInt32	bytesToWrite = 0;
	for (UInt8 i = 0; i < indent; i++) {
		WriteBlock("\t", 1);
	}
	bytesToWrite += indent;

	bytesToWrite += WriteTag(inTag, tag_open, false);
	bytesToWrite += WritePString(inString);
	bytesToWrite += WriteTag(inTag, tag_close);

	return bytesToWrite;
}


// ---------------------------------------------------------------------------
//   WriteCStringEnclosed
// ---------------------------------------------------------------------------
//	Write a Pascal string enclosed in an xml-like pair of tags
//	Return the number of bytes written

SInt32
CXMLFileStream::WriteCStringEnclosed(
		const char *inString,
		const char *inTag, 
		UInt8 indent)
{
	SInt32	bytesToWrite = 0;
	for (UInt8 i = 0; i < indent; i++) {
		WriteBlock("\t", 1);
	}
	bytesToWrite += indent;
	bytesToWrite += WriteTag(inTag, tag_open, false);
	bytesToWrite += WriteCString(inString);
	bytesToWrite += WriteTag(inTag, tag_close);

	return bytesToWrite;
}


// ---------------------------------------------------------------------------
//   WriteOSTypeEnclosed
// ---------------------------------------------------------------------------
//	Write an OSType to a Stream as a text string.
//	Return the number of bytes written.

SInt32
CXMLFileStream::WriteOSTypeEnclosed(
		OSType inType,
		ConstStringPtr inTag, 
		UInt8 indent)
{
	SInt32	bytesToWrite = 0;
	for (UInt8 i = 0; i < indent; i++) {
		WriteBlock("\t", 1);
	}
	bytesToWrite += indent;
	
	bytesToWrite += WriteTag(inTag, tag_open, false);
	bytesToWrite += WriteOSType(inType);
	bytesToWrite += WriteTag(inTag, tag_close);

	return bytesToWrite;
}


// ---------------------------------------------------------------------------
//   WriteOSTypeEnclosed
// ---------------------------------------------------------------------------
//	Write an OSType to a Stream as a text string.
//	Return the number of bytes written.

SInt32
CXMLFileStream::WriteOSTypeEnclosed(
		OSType inType,
		const char *inTag, 
		UInt8 indent)
{
	SInt32	bytesToWrite = 0;
	for (UInt8 i = 0; i < indent; i++) {
		WriteBlock("\t", 1);
	}
	bytesToWrite += indent;

	bytesToWrite += WriteTag(inTag, tag_open, false);
	bytesToWrite += WriteOSType(inType);
	bytesToWrite += WriteTag(inTag, tag_close);

	return bytesToWrite;
}


// ---------------------------------------------------------------------------
//   WriteSInt32Enclosed
// ---------------------------------------------------------------------------

SInt32
CXMLFileStream::WriteSInt32Enclosed(
		const SInt32 inValue,
		const char *inTag, 
		UInt8 indent)
{
	SInt32	bytesToWrite = 0;
	for (UInt8 i = 0; i < indent; i++) {
		WriteBlock("\t", 1);
	}
	bytesToWrite += indent;

	bytesToWrite += WriteTag(inTag, tag_open, false);
	bytesToWrite += WriteSInt32(inValue);
	bytesToWrite += WriteTag(inTag, tag_close);

	return bytesToWrite;
}


// ---------------------------------------------------------------------------
//   WriteSInt16Enclosed
// ---------------------------------------------------------------------------

SInt32
CXMLFileStream::WriteSInt16Enclosed(
		const SInt16 inValue,
		const char *inTag, 
		UInt8 indent)
{
	return ( WriteSInt32Enclosed( (SInt32)inValue, inTag, indent) );
}


// ---------------------------------------------------------------------------
//   WriteBooleanEnclosed
// ---------------------------------------------------------------------------
//	Write a Boolean value enclosed in an xml-like pair of tags
//	Returns the number of bytes written

SInt32
CXMLFileStream::WriteBooleanEnclosed(
		Boolean inBool,
		ConstStringPtr inTag, 
		UInt8 indent)
{
	if (inBool) {
		return (WritePStringEnclosed("\p1", inTag, indent));
	} else {
		return (WritePStringEnclosed("\p0", inTag, indent));
	}
}


// ---------------------------------------------------------------------------
//   WriteBooleanEnclosed
// ---------------------------------------------------------------------------
//	Write a Boolean value enclosed in an xml-like pair of tags
//	Returns the number of bytes written

SInt32
CXMLFileStream::WriteBooleanEnclosed(
		Boolean inBool,
		const char *inTag, 
		UInt8 indent)
{
	if (inBool) {
		return (WriteCStringEnclosed("1", inTag, indent));
	} else {
		return (WriteCStringEnclosed("0", inTag, indent));
	}
}




PP_End_Namespace_PowerPlant
