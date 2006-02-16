// ===========================================================================
// CTextHandleStream.cp					
// 
//                       Created: 2002-06-15 10:36:17
//             Last modification: 2004-02-22 19:48:21
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2003, 2004
// All rights reserved.
// ===========================================================================
//
// A 'text' handle stream (as opposed to 'binary') : a PString will be copied 
// without its first (length) byte, a C string without the closing null byte.

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CTextHandleStream.h"

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   CTextHandleStream							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CTextHandleStream::CTextHandleStream()
	: LHandleStream()
{
}


// ---------------------------------------------------------------------------
//   CTextHandleStream							Constructor				  [public]
// ---------------------------------------------------------------------------
//	Copies data Handle of the original

CTextHandleStream::CTextHandleStream(
	const LHandleStream&	inOriginal)

	: LHandleStream(inOriginal)
{
}


// ---------------------------------------------------------------------------
//   CTextHandleStream							Constructor				  [public]
// ---------------------------------------------------------------------------
//	Construct from an existing Handle
//	The LHandleStream object assumes ownership of the Handle

CTextHandleStream::CTextHandleStream(
	Handle	inHandle)
	: LHandleStream(inHandle)
{
}


// ---------------------------------------------------------------------------
//     ~CTextHandleStream							Destructor				  [public]
// ---------------------------------------------------------------------------

CTextHandleStream::~CTextHandleStream()
{
}


// ---------------------------------------------------------------------------
//   WritePString
// ---------------------------------------------------------------------------
//	Write a Pascal string to a Stream as a text string (ie strips the first
//	length byte)
//	Returns the number of bytes written

SInt32
CTextHandleStream::WritePString(
	ConstStringPtr	inString)
{
	SInt32	bytesToWrite = inString[0];

	WriteBlock(inString + 1, bytesToWrite);

	return bytesToWrite;
}


// ---------------------------------------------------------------------------
//   WritePStringWithTag
// ---------------------------------------------------------------------------
//	Write a Pascal string enclosed in an xml-like pair of tags
//	Returns the number of bytes written

SInt32
CTextHandleStream::WritePStringWithTag(
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
//   WriteCString
// ---------------------------------------------------------------------------
//	Write a C string to a Stream as a text string (ie strips the ending null-byte)
//	Returns the number of bytes written.

SInt32
CTextHandleStream::WriteCString(
	const char *inString)
{
	// Find length of C string
	SInt32		strLen = 0;
	const char	*s = inString;
	while (*s++ != 0) {
		strLen++;
	}

// 		strLen++;// add the nul terminator
	WriteBlock(inString, strLen);

	return strLen;
}


// ---------------------------------------------------------------------------
//   WriteCStringWithTag
// ---------------------------------------------------------------------------
//	Write a Pascal string enclosed in an xml-like pair of tags
//	Returns the number of bytes written

SInt32
CTextHandleStream::WriteCStringWithTag(
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
//   WriteSInt32WithTag
// ---------------------------------------------------------------------------
//	Write a SInt32 number enclosed in an xml-like pair of tags
//	Returns the number of bytes written

SInt32
CTextHandleStream::WriteSInt32WithTag(
		SInt32 inNum,
		ConstStringPtr inTag)
{
	Str255	tempString;
	::NumToString((long) inNum, tempString);

	return (WritePStringWithTag(tempString,inTag));
}


// ---------------------------------------------------------------------------
//   WriteSInt32WithTag
// ---------------------------------------------------------------------------
//	Write a SInt32 number enclosed in an xml-like pair of tags
//	Returns the number of bytes written

SInt32
CTextHandleStream::WriteSInt32WithTag(
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
//   WriteBooleanWithTag
// ---------------------------------------------------------------------------
//	Write a Boolean value enclosed in an xml-like pair of tags
//	Returns the number of bytes written

SInt32
CTextHandleStream::WriteBooleanWithTag(
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
//   WriteBooleanWithTag
// ---------------------------------------------------------------------------
//	Write a Boolean value enclosed in an xml-like pair of tags
//	Returns the number of bytes written

SInt32
CTextHandleStream::WriteBooleanWithTag(
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
//   operator << (SInt32)
// ---------------------------------------------------------------------------

CTextHandleStream&
CTextHandleStream::operator << (SInt32 inNum)
{
	Str255	thePString;
	char * 	theCString = new char[15];
	::NumToString( (long) inNum, thePString);
	CopyPascalStringToC( thePString, theCString);
	(*this) << theCString;
	return (*this);
}

						
// ---------------------------------------------------------------------------
//   operator << (Boolean)
// ---------------------------------------------------------------------------

CTextHandleStream&
CTextHandleStream::operator << (Boolean inBool)
{
	if (inBool) {
		(*this) << '1';
	} else {
		(*this) << '0';
	}
	return (*this);
}


PP_End_Namespace_PowerPlant
