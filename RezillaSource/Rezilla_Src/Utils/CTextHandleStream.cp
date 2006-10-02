// ===========================================================================
// CTextHandleStream.cp					
// 
//                       Created: 2002-06-15 10:36:17
//             Last modification: 2006-10-01 12:11:49
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2003-2006
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
//   WriteSInt32
// ---------------------------------------------------------------------------
//	Write a SInt32 number enclosed in an xml-like pair of tags
//	Returns the number of bytes written

SInt32
CTextHandleStream::WriteSInt32(SInt32 inNum)
{
	Str255	tempString;
	::NumToString(inNum, tempString);

	return ( WritePString(tempString) );
}


// ---------------------------------------------------------------------------
//   WriteSInt16
// ---------------------------------------------------------------------------
//	Write a SInt16 number enclosed in an xml-like pair of tags
//	Returns the number of bytes written

SInt32
CTextHandleStream::WriteSInt16(SInt16 inNum)
{
	return ( WriteSInt32( (SInt32)inNum) );
}



// ---------------------------------------------------------------------------
//   operator << (SInt32)
// ---------------------------------------------------------------------------

CTextHandleStream&
CTextHandleStream::operator << (SInt32 inNum)
{
	Str255	thePString;
	::NumToString( (long) inNum, thePString);
	(*this) << thePString;
	return (*this);
}

						
// ---------------------------------------------------------------------------
//   operator << (SInt16)
// ---------------------------------------------------------------------------

CTextHandleStream&
CTextHandleStream::operator << (SInt16 inNum)
{
	(*this) << (SInt32)inNum;
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
