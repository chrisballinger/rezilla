// ===========================================================================
// CTextFileStream.cp					
// 
//                       Created : 2002-06-09 19:38:34
//             Last modification : 2004-02-29 11:00:55
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@easyconnect.fr>
// www : <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2002-2004
// All rights reserved.
// $Date$
// $Revision$
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
//	¥ WritePString
// ---------------------------------------------------------------------------
//	Write a Pascal string to a Stream as a text string (ie strips the first
//	length byte)
//	Returns the number of bytes written

SInt32
CTextFileStream::WritePString(
	ConstStringPtr	inString)
{
	SInt32	bytesToWrite = inString[0];

	WriteBlock(inString + 1, bytesToWrite);

	return bytesToWrite;
}


// ---------------------------------------------------------------------------
//	¥ WritePStringWithTag
// ---------------------------------------------------------------------------
//	Write a Pascal string enclosed in an xml-like pair of tags
//	Returns the number of bytes written

SInt32
CTextFileStream::WritePStringWithTag(
		ConstStringPtr	inString,
		ConstStringPtr	inTag)
{
	SInt32	bytesToWrite = WritePString("\p<");
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
//	Returns the number of bytes written.

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
//	Returns the number of bytes written

SInt32
CTextFileStream::WriteCStringWithTag(
		const char *inString,
		const char *inTag)
{
	SInt32	bytesToWrite = WriteCString("<");
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
//	Returns the number of bytes written

SInt32
CTextFileStream::WriteSInt32WithTag(
		SInt32 inNum,
		ConstStringPtr inTag)
{
	Str255	tempString;
	::NumToString((long) inNum, tempString);

	return (WritePStringWithTag(tempString,inTag));
}


// ---------------------------------------------------------------------------
//	¥ WriteSInt32WithTag
// ---------------------------------------------------------------------------
//	Write a SInt32 number enclosed in an xml-like pair of tags
//	Returns the number of bytes written

SInt32
CTextFileStream::WriteSInt32WithTag(
		SInt32 inNum,
		const char *inTag)
{
	Str255	tempString;
	::NumToString((long) inNum, tempString);

	SInt32	bytesToWrite = WriteCString("<");
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
//	Returns the number of bytes written

SInt32
CTextFileStream::WriteBooleanWithTag(
		Boolean inBool,
		ConstStringPtr inTag)
{
	if (inBool) {
		return (WritePStringWithTag("\p1",inTag));
	} else {
		return (WritePStringWithTag("\p0",inTag));
	}
}


// ---------------------------------------------------------------------------
//	¥ WriteBooleanWithTag
// ---------------------------------------------------------------------------
//	Write a Boolean value enclosed in an xml-like pair of tags
//	Returns the number of bytes written

SInt32
CTextFileStream::WriteBooleanWithTag(
		Boolean inBool,
		const char *inTag)
{
	SInt32	bytesToWrite ;
	
	if (inBool) {
		bytesToWrite = WriteCStringWithTag("1",inTag);
	} else {
		bytesToWrite = WriteCStringWithTag("0",inTag);
	}

	return bytesToWrite;
}


// ---------------------------------------------------------------------------
//	¥ WriteByChunks
// ---------------------------------------------------------------------------
//	Write a C string to a Stream as a text string cut down into pieces 
//	separated by a specified separator.
//	Returns the number of bytes written.

SInt32
CTextFileStream::WriteByChunks(
		const char *inString, 
		Str255	inSeparator, 
		SInt32	inLen,
		SInt32	inChunkSize)
{
	SInt32	bytesToWrite = inLen;
	SInt32	bytesOffset = 0;
	SInt32	chunksCount = inLen / inChunkSize;
	
	for (SInt32 i = 0; i < chunksCount; i++) {
		bytesToWrite += WritePString(inSeparator);
		WriteBlock(inString + bytesOffset, inChunkSize);
		bytesOffset += inChunkSize;
	}
	if (bytesOffset > inLen) {
		WriteBlock(inString + bytesOffset, inLen - bytesOffset);
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
