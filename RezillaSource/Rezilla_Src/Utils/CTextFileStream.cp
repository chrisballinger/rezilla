// ===========================================================================
// CTextFileStream.cp					
// 
//                       Created : 2002-06-09 19:38:34
//             Last modification : 2005-02-08 15:24:45
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@users.sourceforge.net>
// www : <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2002-2005
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
//	¥ CTextFileStream							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CTextFileStream::CTextFileStream()
{
}


// ---------------------------------------------------------------------------
//	¥ CTextFileStream							Constructor				  [public]
// ---------------------------------------------------------------------------
//	Construct a FileStream from a Toolbox File System Specification

CTextFileStream::CTextFileStream(
	const FSSpec&	inFileSpec)

	: LFileStream(inFileSpec)
{
}


// ---------------------------------------------------------------------------
//	¥ CTextFileStream							Constructor				  [public]
// ---------------------------------------------------------------------------
//	Construct a FileStream from an Alias
//
//	outWasChanged indicates if the AliasHandle was changed during resolution
//	inFromFile is a File Specifier for the starting point for a relative
//		search. If nil, an absolute search is performed

CTextFileStream::CTextFileStream(
	AliasHandle		inAlias,
	Boolean&		outWasChanged,
	FSSpec*			inFromFile)

	: LFileStream(inAlias, outWasChanged, inFromFile)
{
}


// ---------------------------------------------------------------------------
//	¥ ~CTextFileStream							Destructor				  [public]
// ---------------------------------------------------------------------------

CTextFileStream::~CTextFileStream()
{
}


// ---------------------------------------------------------------------------
//	¥ WriteOSType
// ---------------------------------------------------------------------------
//	Write a Pascal string to a Stream as a text string (ie strips the first
//	length byte)
//	Return the number of bytes written

SInt32
CTextFileStream::WriteOSType(OSType inType)
{
	char theType[4];
	SInt32	bytesToWrite = 4;

	*(OSType*)theType = inType;

	WriteBlock(theType, 4);

	return bytesToWrite;
}


// ---------------------------------------------------------------------------
//	¥ WriteOSTypeWithTag
// ---------------------------------------------------------------------------
//	Write an OSType to a Stream as a text string.
//	Return the number of bytes written.

SInt32
CTextFileStream::WriteOSTypeWithTag(
		OSType inType,
		ConstStringPtr inTag, 
		UInt8 indent)
{
	SInt32	bytesToWrite = 0;
	for (UInt8 i = 0; i < indent; i++) {
		WriteBlock("\t", 1);
	}
	bytesToWrite += indent;
	
	bytesToWrite += WritePString("\p<");
	bytesToWrite += WritePString(inTag);
	bytesToWrite += WritePString("\p>");
	
	bytesToWrite += WriteOSType(inType);
	
	bytesToWrite += WritePString("\p</");
	bytesToWrite += WritePString(inTag);
	bytesToWrite += WritePString("\p>\r");

	return bytesToWrite;
}


// ---------------------------------------------------------------------------
//	¥ WriteOSTypeWithTag
// ---------------------------------------------------------------------------
//	Write an OSType to a Stream as a text string.
//	Return the number of bytes written.

SInt32
CTextFileStream::WriteOSTypeWithTag(
		OSType inType,
		const char *inTag, 
		UInt8 indent)
{
	SInt32	bytesToWrite = 0;
	for (UInt8 i = 0; i < indent; i++) {
		WriteBlock("\t", 1);
	}
	bytesToWrite += indent;

	bytesToWrite += WriteCString("<");
	bytesToWrite += WriteCString(inTag);
	bytesToWrite += WriteCString(">");
	
	bytesToWrite += WriteOSType(inType);
	
	bytesToWrite += WriteCString("</");
	bytesToWrite += WriteCString(inTag);
	bytesToWrite += WriteCString(">\r");

	return bytesToWrite;
}


// ---------------------------------------------------------------------------
//	¥ WritePString
// ---------------------------------------------------------------------------
//	Write a Pascal string to a Stream as a text string (ie strips the first
//	length byte)
//	Return the number of bytes written

SInt32
CTextFileStream::WritePString(ConstStringPtr inString)
{
	SInt32	bytesToWrite = 0;
	bytesToWrite += inString[0];

	WriteBlock(inString + 1, bytesToWrite);

	return bytesToWrite;
}


// ---------------------------------------------------------------------------
//	¥ WritePStringWithTag
// ---------------------------------------------------------------------------
//	Write a Pascal string enclosed in an xml-like pair of tags
//	Return the number of bytes written

SInt32
CTextFileStream::WritePStringWithTag(
		ConstStringPtr inString,
		ConstStringPtr inTag, 
		UInt8 indent)
{
	SInt32	bytesToWrite = 0;
	for (UInt8 i = 0; i < indent; i++) {
		WriteBlock("\t", 1);
	}
	bytesToWrite += indent;
	bytesToWrite += WritePString("\p<");
	bytesToWrite += WritePString(inTag);
	bytesToWrite += WritePString("\p>");
	bytesToWrite += WritePString(inString);
	bytesToWrite += WritePString("\p</");
	bytesToWrite += WritePString(inTag);
	bytesToWrite += WritePString("\p>\r");

	return bytesToWrite;
}


// ---------------------------------------------------------------------------
//	¥ WriteCString
// ---------------------------------------------------------------------------
//	Write a C string to a Stream as a text string (ie strips the ending null-byte)
//	Return the number of bytes written.

SInt32
CTextFileStream::WriteCString(
	const char *inString)
{
	// Find length of C string
	SInt32		strLen = 0;
	const char	*s = inString;
	while (*s++ != 0) {
		strLen++;
	}

	WriteBlock(inString, strLen);

	return strLen;
}


// ---------------------------------------------------------------------------
//	¥ WriteCStringWithTag
// ---------------------------------------------------------------------------
//	Write a Pascal string enclosed in an xml-like pair of tags
//	Return the number of bytes written

SInt32
CTextFileStream::WriteCStringWithTag(
		const char *inString,
		const char *inTag, 
		UInt8 indent)
{
	SInt32	bytesToWrite = 0;
	for (UInt8 i = 0; i < indent; i++) {
		WriteBlock("\t", 1);
	}
	bytesToWrite += indent;
	bytesToWrite += WriteCString("<");
	bytesToWrite += WriteCString(inTag);
	bytesToWrite += WriteCString(">");
	bytesToWrite += WriteCString(inString);
	bytesToWrite += WriteCString("</");
	bytesToWrite += WriteCString(inTag);
	bytesToWrite += WriteCString(">\r");

	return bytesToWrite;
}


// ---------------------------------------------------------------------------
//	¥ WriteSInt32WithTag
// ---------------------------------------------------------------------------
//	Write a SInt32 number enclosed in an xml-like pair of tags
//	Return the number of bytes written

SInt32
CTextFileStream::WriteSInt32WithTag(
		SInt32 inNum,
		ConstStringPtr inTag, 
		UInt8 indent)
{
	Str255	tempString;
	::NumToString((long) inNum, tempString);

	return (WritePStringWithTag(tempString, inTag, indent));
}


// ---------------------------------------------------------------------------
//	¥ WriteSInt32WithTag
// ---------------------------------------------------------------------------
//	Write a SInt32 number enclosed in an xml-like pair of tags
//	Return the number of bytes written

SInt32
CTextFileStream::WriteSInt32WithTag(
		SInt32 inNum,
		const char *inTag, 
		UInt8 indent)
{
	Str255	tempString;
	SInt32	bytesToWrite = 0;
	for (UInt8 i = 0; i < indent; i++) {
		WriteBlock("\t", 1);
	}
	bytesToWrite += indent;
	::NumToString((long) inNum, tempString);
	bytesToWrite += WriteCString("<");
	bytesToWrite += WriteCString(inTag);
	bytesToWrite += WriteCString(">");
	bytesToWrite += WritePString(tempString);
	bytesToWrite += WriteCString("</");
	bytesToWrite += WriteCString(inTag);
	bytesToWrite += WriteCString(">\r");

	return bytesToWrite;
}


// ---------------------------------------------------------------------------
//	¥ WriteBooleanWithTag
// ---------------------------------------------------------------------------
//	Write a Boolean value enclosed in an xml-like pair of tags
//	Return the number of bytes written

SInt32
CTextFileStream::WriteBooleanWithTag(
		Boolean inBool,
		ConstStringPtr inTag, 
		UInt8 indent)
{
	if (inBool) {
		return (WritePStringWithTag("\p1", inTag, indent));
	} else {
		return (WritePStringWithTag("\p0", inTag, indent));
	}
}


// ---------------------------------------------------------------------------
//	¥ WriteBooleanWithTag
// ---------------------------------------------------------------------------
//	Write a Boolean value enclosed in an xml-like pair of tags
//	Return the number of bytes written

SInt32
CTextFileStream::WriteBooleanWithTag(
		Boolean inBool,
		const char *inTag, 
		UInt8 indent)
{
	SInt32	bytesToWrite ;
	
	if (inBool) {
		bytesToWrite = WriteCStringWithTag("1", inTag, indent);
	} else {
		bytesToWrite = WriteCStringWithTag("0", inTag, indent);
	}

	return bytesToWrite;
}


// ---------------------------------------------------------------------------
//	¥ WriteByChunks
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
		bytesToWrite += WritePString(inPrefix);
		WriteBlock(inString + bytesOffset, inChunkSize);
		bytesToWrite += WritePString(inSuffix);
		bytesOffset += inChunkSize;
	}
	if (bytesOffset < inLen) {
		bytesToWrite += WritePString(inPrefix);
		WriteBlock(inString + bytesOffset, inLen - bytesOffset);
		bytesToWrite += WritePString(inSuffix);
	} 

	return bytesToWrite;
}


// ---------------------------------------------------------------------------
//	¥ operator << (SInt32)
// ---------------------------------------------------------------------------

CTextFileStream&
CTextFileStream::operator << (SInt32 inNum)
{
	Str255	tempString;
	::NumToString((long) inNum, tempString);
	(*this) << tempString;
	return (*this);
}

						
// ---------------------------------------------------------------------------
//	¥ operator << (Boolean)
// ---------------------------------------------------------------------------

CTextFileStream&
CTextFileStream::operator << (Boolean inBool)
{
	if (inBool) {
		(*this) << '1';
	} else {
		(*this) << '0';
	}
	return (*this);
}


PP_End_Namespace_PowerPlant
