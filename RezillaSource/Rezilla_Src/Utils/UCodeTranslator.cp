// ===========================================================================
// UCodeTranslator.cp					
// 
//                       Created: 2003-05-04 16:40:47
//             Last modification: 2004-08-16 10:51:21
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

#include "UCodeTranslator.h"
#include "CRezillaPrefs.h"
#include "RezillaConstants.h"

#include <LString.h>
#include <UMemoryMgr.h>

#include <string.h>
#include <stdio.h>

// String used for conversion to Base64 encoding (lxvi = 64)
                   // 0000000000111111111122222222223333333333444444444455555555556666
                   // 0123456789012345678901234567890123456789012345678901234567890123
static char * lxvi = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//	¥ ConvertByteToReadable											[public]
// ---------------------------------------------------------------------------
// 0xF6 (246) is ö and 0xFF (255) is ÿ.
// 0x5E (94) is ö too.

void
UCodeTranslator::ConvertByteToReadable( LDataStream* srcDataStream, LDataStream* trgtDataStream, Boolean inInsertSpace)
{
	UInt8 readChar;
	SInt32 length = srcDataStream->GetLength();
	
	for (UInt32 i = 1; i <= length; i++) {
		*srcDataStream >> readChar;
		if ( readChar == 0x20 ) {
			*trgtDataStream << (char) 0x2E;
		} else if ( readChar <= 0x20 ) {
			*trgtDataStream << (char) 0xFF;
		} else if ( readChar >= 0x7F ) {
			*trgtDataStream << (char) 0xF6;
		} else {
			*trgtDataStream << readChar;
		}
		if (inInsertSpace) {
			*trgtDataStream << (char) 0x20;
		} 
	}
}


// ---------------------------------------------------------------------------
//	¥ ConvertByteToReadable										[public]
// ---------------------------------------------------------------------------

void
UCodeTranslator::ConvertByteToReadable(char* srcString, char* trgtString, Boolean inInsertSpace)
{
	// todo...
}


// // ---------------------------------------------------------------------------
// //	¥ ConvertByteToReadable									[public]
// // ---------------------------------------------------------------------------
// 
// void
// UCodeTranslator::ConvertByteToReadable(char srcChar, char trgtChar )
// {
// }


// ---------------------------------------------------------------------------
//	¥ ConvertByteToSegmentedText								[public]
// ---------------------------------------------------------------------------
// Similar to ConvertByteToReadable but inserts a Carriage Return (0x0D)
// instead of a blank every mSegment input chars.
// 0xF6 (246) is ö and 0xFF (255) is ÿ.
// 0x5E (94) is ö too.

void
UCodeTranslator::ConvertByteToSegmentedText( LDataStream* srcDataStream, LDataStream* trgtDataStream, SInt32 inSegment)
{
	UInt8 readChar;
	SInt32 length = srcDataStream->GetLength();
	
	for (UInt32 i = 1; i <= length; i++) {
		*srcDataStream >> readChar;
		if ( readChar == 0x20 ) {
			*trgtDataStream << (char) 0x2E;
		} else if ( readChar <= 0x20 ) {
			*trgtDataStream << (char) 0xFF;
		} else if ( readChar >= 0x7F ) {
			*trgtDataStream << (char) 0xF6;
		} else {
			*trgtDataStream << readChar;
		}
		*trgtDataStream << ((i % inSegment) ? (char) 0x20 : (char) 0x0D);
	}
}


// ---------------------------------------------------------------------------
//	¥ ConvertByteToSegmentedText									[public]
// ---------------------------------------------------------------------------

void
UCodeTranslator::ConvertByteToSegmentedText(char* srcString, char* trgtString, SInt32 inSegment)
{
	// todo...
}


// ---------------------------------------------------------------------------
//	¥ ConvertByteToSeparatedHex										[public]
// ---------------------------------------------------------------------------
// This function supposes that the src and trgt streams are properly allocated. 
// The size of trgtDataStream should be three times the size of srcDataStream.
// 	char nbsp = (char) 0xCA;	// nbsp

void
UCodeTranslator::ConvertByteToSeparatedHex( LDataStream* srcDataStream, LDataStream* trgtDataStream )
{
	UInt8 readChar;
	char * buffer = new char[3];
	SInt32 length = srcDataStream->GetLength();
	char * formatStr = new char[32];

	if (CRezillaPrefs::GetPrefValue(kPref_templates_hexCase) == hex_uppercase) {
		sprintf(formatStr, "%s.2X %c", "%", 0);
	} else {
		sprintf(formatStr, "%s.2x %c", "%", 0);
	}
	
	for (UInt32 i = 1; i <= length; i++) {
		*srcDataStream >> readChar;
		sprintf(buffer, formatStr, readChar);
		trgtDataStream->WriteBlock(buffer,3);
	}
}


// ---------------------------------------------------------------------------
//	¥ ConvertByteToSeparatedHex										[public]
// ---------------------------------------------------------------------------
// This function supposes that the src and trgt strings are properly allocated. 
// The size of trgtString should be three times the size of srcString.

void
UCodeTranslator::ConvertByteToSeparatedHex(char* srcString, char* trgtString )
{
	char * buffer = new char[3];
	SInt32 pos = 0;
	char * formatStr = new char[32];

	if (CRezillaPrefs::GetPrefValue(kPref_templates_hexCase) == hex_uppercase) {
		sprintf(formatStr, "%s.2X %c", "%", 0);
	} else {
		sprintf(formatStr, "%s.2x %c", "%", 0);
	}
	
	do {
		sprintf(buffer, formatStr, (UInt8) *srcString);
		::BlockMoveData(buffer, trgtString + pos, 3);
		pos += 3;
	} while (*srcString++);
}


// ---------------------------------------------------------------------------
//	¥ ConvertByteToSegmentedHex										[public]
// ---------------------------------------------------------------------------
// Similar to ConvertByteToSeparatedHex but inserts a Carriage Return
// instead of a blank every mSegment input chars.
// This function supposes that the src and trgt streams are properly allocated. 
// The size of trgtDataStream should be three times the size of srcDataStream.

void
UCodeTranslator::ConvertByteToSegmentedHex( LDataStream* srcDataStream, LDataStream* trgtDataStream, SInt32 inSegment)
{
	UInt8 readChar;
	char * buffer = new char[3];
	SInt32 length = srcDataStream->GetLength();
	char * formatStr = new char[32];

	if (CRezillaPrefs::GetPrefValue(kPref_templates_hexCase) == hex_uppercase) {
		sprintf(formatStr, "%s.2X%c", "%", 0);
	} else {
		sprintf(formatStr, "%s.2x%c", "%", 0);
	}
	
	for (UInt32 i = 1; i <= length; i++) {
		*srcDataStream >> readChar;
		sprintf(buffer, formatStr, readChar);
		trgtDataStream->WriteBlock(buffer,2);
		*trgtDataStream << ((i % inSegment) ? (char) 0x20 : (char) 0x0D);
	}
}


// ---------------------------------------------------------------------------
//	¥ ConvertByteToSegmentedHex										[public]
// ---------------------------------------------------------------------------
// Similar to ConvertByteToSeparatedHex but inserts a Carriage Return
// instead of a blank every mSegment input chars.
// This function supposes that the src and trgt strings are properly allocated. 
// The size of trgtString should be three times the size of srcString.

void
UCodeTranslator::ConvertByteToSegmentedHex(char* srcString, char* trgtString, SInt32 inSegment)
{
	char * buffer = new char[3];
	SInt32 pos = 0;
	SInt32 period = 3 * inSegment;
	char * formatStr = new char[32];

	if (CRezillaPrefs::GetPrefValue(kPref_templates_hexCase) == hex_uppercase) {
		sprintf(formatStr, "%s.2X%ss%c", "%", "%", 0);
	} else {
		sprintf(formatStr, "%s.2x%ss%c", "%", "%", 0);
	}
	
	do {
		sprintf(buffer, formatStr, (UInt8) *srcString, ((pos % period) ? (char) 0x20 : (char) 0x0D));
		::BlockMoveData(buffer, trgtString + pos, 3);
		pos += 3;
	} while (*srcString++);
}


// ---------------------------------------------------------------------------
//	¥ ConvertByteToHex												[public]
// ---------------------------------------------------------------------------
// This function supposes that the src and trgt streams are properly allocated. 
// The size of trgtDataStream should be twice the size of srcDataStream.
// 	char nbsp = (char) 0xCA;	// nbsp

void
UCodeTranslator::ConvertByteToHex( LDataStream* srcDataStream, LDataStream* trgtDataStream )
{
	UInt8 readChar;
	char * buffer = new char[2];
	SInt32 length = srcDataStream->GetLength();
	char * formatStr = new char[32];

	if (CRezillaPrefs::GetPrefValue(kPref_templates_hexCase) == hex_uppercase) {
		sprintf(formatStr, "%s.2X%c", "%", 0);
	} else {
		sprintf(formatStr, "%s.2x%c", "%", 0);
	}
	
	for (UInt32 i = 1; i <= length; i++) {
		*srcDataStream >> readChar;
		sprintf(buffer, formatStr, readChar);
		trgtDataStream->WriteBlock(buffer,2);
	}
}


// ---------------------------------------------------------------------------
//	¥ ConvertByteToHex												[public]
// ---------------------------------------------------------------------------
// This function supposes that the src and trgt strings are properly allocated. 
// The size of trgtString should be twice the size of srcString.

void
UCodeTranslator::ConvertByteToHex(char* srcString, char* trgtString )
{
	char * buffer = new char[2];
	SInt32 pos = 0;
	char * formatStr = new char[32];

	if (CRezillaPrefs::GetPrefValue(kPref_templates_hexCase) == hex_uppercase) {
		sprintf(formatStr, "%s.2X%c", "%", 0);
	} else {
		sprintf(formatStr, "%s.2x%c", "%", 0);
	}
	
	
	do {
		sprintf(buffer, formatStr, (UInt8) *srcString);
		::BlockMoveData(buffer, trgtString + pos, 2);
		pos += 2;
	} while (*srcString++);
}


// ---------------------------------------------------------------------------
//	¥ ConvertHexToByte												[public]
// ---------------------------------------------------------------------------
// This function converts a stream of hex data to their UInt8 values. If the 
// size of the srcDataStream is odd, the last char is discarded. 

void
UCodeTranslator::ConvertHexToByte( LDataStream* srcDataStream, LDataStream* trgtDataStream )
{
	UInt8 readChar;
	UInt8 val1;
	UInt8 val2;
	SInt32 length = srcDataStream->GetLength() ;
	UInt8 result;
	
	// The number of hex digits must be even. If not, omit the last one.
	if (length % 2) {
		length -= 1;
	} 
	for (UInt32 i = 1; i <= length; i += 2) {
		*srcDataStream >> readChar;
		if (readChar != 0x30) {
			val1 = ConvertHexToValue(readChar);
		} else {
			val1 = 0;
		}
		
		*srcDataStream >> readChar;
		if (readChar != 0x30) {
			val2 = ConvertHexToValue(readChar);
		} else {
			val2 = 0;
		}
		*trgtDataStream << (UInt8) (16 * val1 + val2);
	}
}


// ---------------------------------------------------------------------------
//	¥ ConvertHexToByte												[public]
// ---------------------------------------------------------------------------

void
UCodeTranslator::ConvertHexToByte(char* srcString, char* trgtString)
{
	SInt32	theLength = strlen(srcString);

	LDataStream inStream(srcString, theLength);
	LDataStream outStream(trgtString, theLength/2);
	ConvertHexToByte(&inStream, &outStream);
	trgtString[theLength/2] = 0;
}


// ---------------------------------------------------------------------------
//	¥ ConvertHexToValue												[public]
// ---------------------------------------------------------------------------

UInt8
UCodeTranslator::ConvertHexToValue(UInt8 inHex)
{
	UInt8 val = 0;
	if (inHex > 48 && inHex < 59) {
		val = inHex - 48;
	} else if (inHex > 64 && inHex < 71) {
		val = inHex - 55;
	} else if (inHex > 96 && inHex < 103) {
		val = inHex - 87;
	}
	return val;
}


// ---------------------------------------------------------------------------
//	¥ StripBlanks													[public]
// ---------------------------------------------------------------------------
// Returns the number of copied bytes.

SInt32
UCodeTranslator::StripBlanks( LDataStream* srcDataStream, LDataStream* trgtDataStream )
{
	UInt8 readChar;
	SInt32 length = srcDataStream->GetLength();
	SInt32 count = 0;
	
	for (UInt32 i = 1; i <= length; i++) {
		*srcDataStream >> readChar;
		if ( readChar != 0x20 ) {
			*trgtDataStream << readChar;
			count++;
		}
	}
	return count;
}


// ---------------------------------------------------------------------------
//	¥ StripBlanks													[public]
// ---------------------------------------------------------------------------
// This function supposes that the src and trgt strings are properly allocated. 
// The size of trgtString should be at least the size of srcString. Returns 
// the number of copied bytes.

SInt32
UCodeTranslator::StripBlanks(char* srcString, char* trgtString )
{
	SInt32 pos = 0;
	
	do {
		if (*srcString != 0x20) {
			trgtString[pos] = *srcString;
			pos += 1;
		} 
	} while (*srcString++);
	
	return pos;
}


// ---------------------------------------------------------------------------
//	¥ StripPeriodical												[public]
// ---------------------------------------------------------------------------
// Strips one char every n chars out of the stream. Returns the number of copied bytes.

SInt32
UCodeTranslator::StripPeriodical( LDataStream* srcDataStream, LDataStream* trgtDataStream, UInt16 inPeriod)
{
	UInt8 readChar;
	SInt32 length = srcDataStream->GetLength();
	SInt32 count = 0;
	
	for (UInt32 i = 1; i <= length; i++) {
		*srcDataStream >> readChar;
		if ( i % inPeriod ) {
			*trgtDataStream << readChar;
			count++;
		}
	}
	return count;
}


// ---------------------------------------------------------------------------
//	¥ ConvertByteToBase64												[public]
// ---------------------------------------------------------------------------
// This function supposes that the src and trgt streams are properly allocated. 
// The size of trgtDataStream should be 4/3 the size of srcDataStream + 4 
// if srcDataStream'length is not divisible by 3.
// 	0xfc	11111100
// 	0x03	00000011
// 	0x0f	00001111
// 	0x3f	00111111

void
UCodeTranslator::ConvertByteToBase64(LDataStream* srcDataStream, LDataStream* trgtDataStream )
{
	UInt8 * buffer = new UInt8[3];
	SInt32 length = srcDataStream->GetLength();
	SInt32 triadCount = length / 3;
	UInt8 theChar;
	
	for (UInt32 i = 1; i <= triadCount; i++) {
		*srcDataStream >> buffer[0];
		*srcDataStream >> buffer[1];
		*srcDataStream >> buffer[2];
		
		theChar = (buffer[0] & 0xfc) >> 2;
		*trgtDataStream << lxvi[theChar];
		
		theChar = ((buffer[0] & 0x03) << 4) | (buffer[1] >> 4);
		*trgtDataStream << lxvi[theChar];
		
		theChar = ((buffer[1] & 0x0f) << 2) | (buffer[2] >> 6);
		*trgtDataStream << lxvi[theChar];
		
		theChar=buffer[2] & 0x3f;
		*trgtDataStream << lxvi[theChar];
	}
	// Now handle the rest
	switch (length % 3) {
		case 1:
		*srcDataStream >> buffer[0];
		buffer[1] = 0;
		buffer[2] = 0;
		theChar = (buffer[0] & 0xfc) >> 2;
		*trgtDataStream << lxvi[theChar];
		
		theChar = ((buffer[0] & 0x03) << 4) | (buffer[1] >> 4);
		*trgtDataStream << lxvi[theChar];
		
		*trgtDataStream << kFillChar;
		*trgtDataStream << kFillChar;
		break;
		
		case 2:
		*srcDataStream >> buffer[0];
		*srcDataStream >> buffer[1];
		buffer[2] = 0;
		theChar = (buffer[0] & 0xfc) >> 2;
		*trgtDataStream << lxvi[theChar];
		
		theChar = ((buffer[0] & 0x03) << 4) | (buffer[1] >> 4);
		*trgtDataStream << lxvi[theChar];
		
		theChar = ((buffer[1] & 0x0f) << 2) | (buffer[2] >> 6);
		*trgtDataStream << lxvi[theChar];
		
		*trgtDataStream << kFillChar;
		break;
	}
}


// ---------------------------------------------------------------------------
//	¥ ConvertByteToBase64												[public]
// ---------------------------------------------------------------------------
// This function supposes that the src and trgt strings are properly allocated. 
// The size of trgtString should be twice the size of srcString.


// 	SInt32	theLength = strlen(srcString);
// 
// 	LDataStream inStream(srcString, theLength);
// 	LDataStream outStream(trgtString, theLength/2);
// 	ConvertHexToByte(&inStream, &outStream);
// 	trgtString[theLength/2] = 0;
void
UCodeTranslator::ConvertByteToBase64(char* srcString, char* trgtString )
{
	// todo...
}


// ---------------------------------------------------------------------------
//	¥ ConvertBase64ToByte												[public]
// ---------------------------------------------------------------------------
// This function supposes that the src and trgt streams are properly allocated. 
// The size of srcDataStream should be a multiple of 4.
// The size of trgtDataStream should be 3/4 the size of srcDataStream.
// 	0x03	00000011
// 	0x0f	00001111
// 	0xf0	11110000
// 	0xc0	11000000

void
UCodeTranslator::ConvertBase64ToByte(LDataStream* srcDataStream, LDataStream* trgtDataStream )
{
	UInt8 * buffer = new UInt8[4];
	SInt32 length = srcDataStream->GetLength();
	SInt32 quadrupleCount = length / 4;
	UInt8 readChar, outChar;
	SInt32 trgtLen;
	
	// Handle chunks of 4 chars up to the next to last.
	for (UInt32 i = 1; i < quadrupleCount; i++) {
		*srcDataStream >> readChar;
		buffer[0] = ConvertToNumber(readChar);
		*srcDataStream >> readChar;
		buffer[1] = ConvertToNumber(readChar);
		*srcDataStream >> readChar;
		buffer[2] = ConvertToNumber(readChar);
		*srcDataStream >> readChar;
		buffer[3] = ConvertToNumber(readChar);
		
		outChar = (buffer[0] << 2) | (buffer[1] >> 4);
		*trgtDataStream << outChar;
		
		outChar = (buffer[1] << 4) | (buffer[2] >> 2);
		*trgtDataStream << outChar;
		
		outChar = (buffer[2] << 6) | buffer[3];
		*trgtDataStream << outChar;
	}
	// Handle the last chunk: it can be of the form xxxx, xxx= or xx==.
	*srcDataStream >> readChar;
	buffer[0] = ConvertToNumber(readChar);
	*srcDataStream >> readChar;
	buffer[1] = ConvertToNumber(readChar);
	
	outChar = (buffer[0] << 2) | (buffer[1] >> 4);
	*trgtDataStream << outChar;
	
	*srcDataStream >> readChar;
	if (readChar != '=') {
		buffer[2] = ConvertToNumber(readChar);
		outChar = (buffer[1] << 4) | (buffer[2] >> 2);
		*trgtDataStream << outChar;
	} else {
		// Adjust the length of the target stream
		trgtLen = (*trgtDataStream).GetLength();
		(*trgtDataStream).SetLength(trgtLen - 2);
		return;
	}
	
	*srcDataStream >> readChar;
	if (readChar != '=') {
		buffer[3] = ConvertToNumber(readChar);
		outChar = (buffer[2] << 6) | buffer[3];
		*trgtDataStream << outChar;
	} else {
		// Adjust the length of the target stream
		trgtLen = (*trgtDataStream).GetLength();
		(*trgtDataStream).SetLength(trgtLen - 1);
		return;
	}
}


// ---------------------------------------------------------------------------
//	¥ ConvertBase64ToByte												[public]
// ---------------------------------------------------------------------------
// This function supposes that the src and trgt strings are properly allocated. 
// The size of srcString should be a multiple of 4.
// The size of trgtString should be 3/4 the size of srcDataStream.

void
UCodeTranslator::ConvertBase64ToByte(char* srcString, char* trgtString )
{
	// todo...
}


// ---------------------------------------------------------------------------
//	¥ ConvertToNumber												[public]
// ---------------------------------------------------------------------------

int
UCodeTranslator::ConvertToNumber(UInt8 inByte)
{
	if (inByte >= 'A' && inByte <= 'Z')
		return (inByte - 'A');

	if (inByte >= 'a' && inByte <= 'z')
		return (inByte - 'a' + 26);

	if (inByte >= '0' && inByte <= '9')
		return (inByte - '0' + 52);

	if (inByte == '+')
		return (62);

	if (inByte == '/')
		return (63);

	return (-1);
}



// ===========================================================================
//	¥ Stack-based classes
// ===========================================================================

// =====================================
//  CLASS StSepHexTranslator
// =====================================

// ---------------------------------------------------------------------------
//	¥ StSepHexTranslator							Constructor			  [public]
// ---------------------------------------------------------------------------

StSepHexTranslator::StSepHexTranslator(Handle inHandle)
{
	mInHandle = inHandle;
	mInSize = ::GetHandleSize(inHandle);
	mOutSize = 3 * mInSize;
	mOutHandle = ::NewHandle( mOutSize );
	ThrowIfNil_(mOutHandle);
}


// ---------------------------------------------------------------------------
//	¥ StSepHexTranslator							Constructor			  [public]
// ---------------------------------------------------------------------------

StSepHexTranslator::StSepHexTranslator(const void * inPtr, SInt32 inByteCount)
{
	mInHandle = ::NewHandle(inByteCount);
	mInSize = inByteCount;
	BlockMoveData(inPtr, *mInHandle, inByteCount);
	mOutSize = 3 * mInSize;
	mOutHandle = ::NewHandle( mOutSize );
	ThrowIfNil_(mOutHandle);
}


// ---------------------------------------------------------------------------
//	¥ ~StSepHexTranslator						Destructor				  [public]
// ---------------------------------------------------------------------------

StSepHexTranslator::~StSepHexTranslator()
{
	// It should not be nil, but who knows...
	if (mOutHandle != nil) {
		::DisposeHandle(mOutHandle);
	} 
}


// ---------------------------------------------------------------------------
//	¥ Convert													[public]
// ---------------------------------------------------------------------------

void
StSepHexTranslator::Convert()
{
	StHandleLocker locker(mInHandle);
	
	LDataStream inStream(*mInHandle, mInSize);
	LDataStream outStream(*mOutHandle, mOutSize);
	
	UCodeTranslator::ConvertByteToSeparatedHex(&inStream, &outStream);
}


// =====================================
//  CLASS StSegmHexTranslator
// =====================================

// ---------------------------------------------------------------------------
//	¥ StSegmHexTranslator							Constructor			  [public]
// ---------------------------------------------------------------------------

StSegmHexTranslator::StSegmHexTranslator(Handle inHandle, SInt32 inSegment)
{
	mSegment = inSegment;
	mInHandle = inHandle;
	mInSize = ::GetHandleSize(inHandle);
	mOutSize = 3 * mInSize;
	mOutHandle = ::NewHandle( mOutSize );
	ThrowIfNil_(mOutHandle);
}


// ---------------------------------------------------------------------------
//	¥ StSegmHexTranslator							Constructor			  [public]
// ---------------------------------------------------------------------------

StSegmHexTranslator::StSegmHexTranslator(const void * inPtr, SInt32 inByteCount, SInt32 inSegment)
{
	mSegment = inSegment;
	mInHandle = ::NewHandle(inByteCount);
	mInSize = inByteCount;
	BlockMoveData(inPtr, *mInHandle, inByteCount);
	mOutSize = 3 * mInSize;
	mOutHandle = ::NewHandle( mOutSize );
	ThrowIfNil_(mOutHandle);
}


// ---------------------------------------------------------------------------
//	¥ ~StSegmHexTranslator						Destructor				  [public]
// ---------------------------------------------------------------------------

StSegmHexTranslator::~StSegmHexTranslator()
{
	// It should not be nil, but who knows...
	if (mOutHandle != nil) {
		::DisposeHandle(mOutHandle);
	} 
}


// ---------------------------------------------------------------------------
//	¥ Convert													[public]
// ---------------------------------------------------------------------------

void
StSegmHexTranslator::Convert()
{
	StHandleLocker locker(mInHandle);
	
	LDataStream inStream(*mInHandle, mInSize);
	LDataStream outStream(*mOutHandle, mOutSize);
	
	UCodeTranslator::ConvertByteToSegmentedHex(&inStream, &outStream, mSegment);
}


// =====================================
//  CLASS StByteToHexTranslator
// =====================================

// ---------------------------------------------------------------------------
//	¥ StByteToHexTranslator							Constructor			  [public]
// ---------------------------------------------------------------------------

StByteToHexTranslator::StByteToHexTranslator(Handle inHandle)
{
	mInHandle = inHandle;
	mInSize = ::GetHandleSize(inHandle);
	mOutSize = 2 * mInSize;
	mOutHandle = ::NewHandle(mOutSize);
	ThrowIfNil_(mOutHandle);
}


// ---------------------------------------------------------------------------
//	¥ StByteToHexTranslator							Constructor			  [public]
// ---------------------------------------------------------------------------

StByteToHexTranslator::StByteToHexTranslator(const void * inPtr, SInt32 inByteCount)
{
	mInHandle = ::NewHandle(inByteCount);
	mInSize = inByteCount;
	BlockMoveData(inPtr, *mInHandle, inByteCount);
	mOutSize = 2 * mInSize;
	mOutHandle = ::NewHandle(mOutSize);
	ThrowIfNil_(mOutHandle);
}


// ---------------------------------------------------------------------------
//	¥ ~StByteToHexTranslator						Destructor				  [public]
// ---------------------------------------------------------------------------

StByteToHexTranslator::~StByteToHexTranslator()
{
	// It should not be nil, but who knows...
	if (mOutHandle != nil) {
		::DisposeHandle(mOutHandle);
	} 
}


// ---------------------------------------------------------------------------
//	¥ Convert													[public]
// ---------------------------------------------------------------------------

void
StByteToHexTranslator::Convert()
{
	StHandleLocker locker(mInHandle);
	
	LDataStream inStream(*mInHandle, mInSize);
	LDataStream outStream(*mOutHandle, mOutSize);
	
	UCodeTranslator::ConvertByteToHex(&inStream, &outStream);
}


// =====================================
//  CLASS StHexToByteTranslator
// =====================================

// ---------------------------------------------------------------------------
//	¥ StHexToByteTranslator							Constructor		  [public]
// ---------------------------------------------------------------------------

StHexToByteTranslator::StHexToByteTranslator(Handle inHandle)
{
	mInHandle = inHandle;
	mInSize = ::GetHandleSize(inHandle);
	mOutSize = mInSize/2;
	mOutHandle = ::NewHandle(mOutSize);
	ThrowIfNil_(mOutHandle);
}


// ---------------------------------------------------------------------------
//	¥ ~StHexToByteTranslator						Destructor		  [public]
// ---------------------------------------------------------------------------

StHexToByteTranslator::~StHexToByteTranslator()
{
	// It should not be nil, but who knows...
	if (mOutHandle != nil) {
		::DisposeHandle(mOutHandle);
	} 
}


// ---------------------------------------------------------------------------
//	¥ Convert														[public]
// ---------------------------------------------------------------------------

void
StHexToByteTranslator::Convert()
{
	StHandleLocker locker(mInHandle);
	
	LDataStream inStream(*mInHandle, mInSize);
	LDataStream outStream(*mOutHandle, mOutSize);
// 	inStream.SetMarker(0L,streamFrom_Start);
	
	UCodeTranslator::ConvertHexToByte(&inStream, &outStream);
}


// =====================================
//  CLASS StByteToBase64Translator
// =====================================

// ---------------------------------------------------------------------------
//	¥ StByteToBase64Translator					Constructor			  [public]
// ---------------------------------------------------------------------------

StByteToBase64Translator::StByteToBase64Translator(Handle inHandle)
{
	mInHandle = inHandle;
	mInSize = ::GetHandleSize(inHandle);
	mOutSize = (mInSize / 3) * 4;
	mOutSize += ((mInSize % 3) > 0) ? 4:0;
	mOutHandle = ::NewHandle(mOutSize);
	ThrowIfNil_(mOutHandle);
}


// ---------------------------------------------------------------------------
//	¥ StByteToBase64Translator					Constructor			  [public]
// ---------------------------------------------------------------------------

StByteToBase64Translator::StByteToBase64Translator(const void * inPtr, SInt32 inByteCount)
{
	mInHandle = ::NewHandle(inByteCount);
	mInSize = inByteCount;
	BlockMoveData(inPtr, *mInHandle, inByteCount);
	mOutSize = (mInSize / 3) * 4;
	mOutSize += ((mInSize % 3) > 0) ? 4:0;
	mOutHandle = ::NewHandle(mOutSize);
	ThrowIfNil_(mOutHandle);
}


// ---------------------------------------------------------------------------
//	¥ ~StByteToBase64Translator				Destructor				  [public]
// ---------------------------------------------------------------------------

StByteToBase64Translator::~StByteToBase64Translator()
{
	// It should not be nil, but who knows...
	if (mOutHandle != nil) {
		::DisposeHandle(mOutHandle);
	} 
}


// ---------------------------------------------------------------------------
//	¥ Convert													[public]
// ---------------------------------------------------------------------------

void
StByteToBase64Translator::Convert()
{
	StHandleLocker locker(mInHandle);
	
	LDataStream inStream(*mInHandle, mInSize);
	LDataStream outStream(*mOutHandle, mOutSize);
	
	UCodeTranslator::ConvertByteToBase64(&inStream, &outStream);
}


// =====================================
//  CLASS StBase64ToByteTranslator
// =====================================

// ---------------------------------------------------------------------------
//	¥ StBase64ToByteTranslator					Constructor			  [public]
// ---------------------------------------------------------------------------

StBase64ToByteTranslator::StBase64ToByteTranslator(Handle inHandle)
{
	mInHandle = inHandle;
	mInSize = ::GetHandleSize(inHandle);
	mOutSize = (mInSize / 4) * 3;
	mOutHandle = ::NewHandle(mOutSize);
	ThrowIfNil_(mOutHandle);
}


// ---------------------------------------------------------------------------
//	¥ StBase64ToByteTranslator					Constructor			  [public]
// ---------------------------------------------------------------------------

StBase64ToByteTranslator::StBase64ToByteTranslator(const void * inPtr, SInt32 inByteCount)
{
	mInHandle = ::NewHandle(inByteCount);
	mInSize = inByteCount;
	BlockMoveData(inPtr, *mInHandle, inByteCount);
	mOutSize = (mInSize / 4) * 3;
	mOutHandle = ::NewHandle(mOutSize);
	ThrowIfNil_(mOutHandle);
}


// ---------------------------------------------------------------------------
//	¥ ~StBase64ToByteTranslator				Destructor				  [public]
// ---------------------------------------------------------------------------

StBase64ToByteTranslator::~StBase64ToByteTranslator()
{
	// It should not be nil, but who knows...
	if (mOutHandle != nil) {
		::DisposeHandle(mOutHandle);
	} 
}


// ---------------------------------------------------------------------------
//	¥ Convert													[public]
// ---------------------------------------------------------------------------

void
StBase64ToByteTranslator::Convert()
{
	StHandleLocker locker(mInHandle);
	
	LDataStream inStream(*mInHandle, mInSize);
	LDataStream outStream(*mOutHandle, mOutSize);
	
	UCodeTranslator::ConvertBase64ToByte(&inStream, &outStream);
}


// =====================================
//  CLASS StSepTextTranslator
// =====================================

// ---------------------------------------------------------------------------
//	¥ StSepTextTranslator					Constructor			  [public]
// ---------------------------------------------------------------------------

StSepTextTranslator::StSepTextTranslator(Handle inHandle)
{
	mInHandle = inHandle;
	mInSize = ::GetHandleSize(inHandle);
	mOutSize = 2 * mInSize;
	mOutHandle = ::NewHandle( mOutSize );
	ThrowIfMemError_();
}


// ---------------------------------------------------------------------------
//	¥ StSepTextTranslator					Constructor			  [public]
// ---------------------------------------------------------------------------

StSepTextTranslator::StSepTextTranslator(const void * inPtr, SInt32 inByteCount)
{
	mInHandle = ::NewHandle(inByteCount);
	mInSize = inByteCount;
	BlockMoveData(inPtr, *mInHandle, inByteCount);
	mOutSize = 2 * mInSize;
	mOutHandle = ::NewHandle( mOutSize );
	ThrowIfMemError_();
}


// ---------------------------------------------------------------------------
//	¥ ~StSepTextTranslator					Destructor			  [public]
// ---------------------------------------------------------------------------

StSepTextTranslator::~StSepTextTranslator()
{
	// It should not be nil, but who knows...
	if (mOutHandle != nil) {
		::DisposeHandle(mOutHandle);
	} 
}


// ---------------------------------------------------------------------------
//	¥ Convert													[public]
// ---------------------------------------------------------------------------

void
StSepTextTranslator::Convert()
{
	StHandleLocker locker(mInHandle);
	
	LDataStream inStream(*mInHandle, mInSize);
	LDataStream outStream(*mOutHandle, mOutSize);
	
	UCodeTranslator::ConvertByteToReadable(&inStream, &outStream, true);
}


// =====================================
//  CLASS StSegmTextTranslator
// =====================================

// ---------------------------------------------------------------------------
//	¥ StSegmTextTranslator					Constructor			  [public]
// ---------------------------------------------------------------------------

StSegmTextTranslator::StSegmTextTranslator(Handle inHandle, SInt32 inSegment)
{
	mSegment = inSegment;
	mInHandle = inHandle;
	mInSize = ::GetHandleSize(inHandle);
	mOutSize = 2 * mInSize;
	mOutHandle = ::NewHandle( mOutSize );
	ThrowIfMemError_();
}


// ---------------------------------------------------------------------------
//	¥ StSegmTextTranslator					Constructor			  [public]
// ---------------------------------------------------------------------------

StSegmTextTranslator::StSegmTextTranslator(const void * inPtr, SInt32 inByteCount, SInt32 inSegment)
{
	mSegment = inSegment;
	mInHandle = ::NewHandle(inByteCount);
	mInSize = inByteCount;
	BlockMoveData(inPtr, *mInHandle, inByteCount);
	mOutSize = 2 * mInSize;
	mOutHandle = ::NewHandle( mOutSize );
	ThrowIfMemError_();
}


// ---------------------------------------------------------------------------
//	¥ ~StSegmTextTranslator					Destructor			  [public]
// ---------------------------------------------------------------------------

StSegmTextTranslator::~StSegmTextTranslator()
{
	// It should not be nil, but who knows...
	if (mOutHandle != nil) {
		::DisposeHandle(mOutHandle);
	} 
}


// ---------------------------------------------------------------------------
//	¥ Convert													[public]
// ---------------------------------------------------------------------------

void
StSegmTextTranslator::Convert()
{
	StHandleLocker locker(mInHandle);
	
	LDataStream inStream(*mInHandle, mInSize);
	LDataStream outStream(*mOutHandle, mOutSize);
	
	UCodeTranslator::ConvertByteToSegmentedText(&inStream, &outStream, mSegment);
}


// =====================================
//  CLASS StByteToTextTranslator
// =====================================

// ---------------------------------------------------------------------------
//	¥ StByteToTextTranslator					Constructor			  [public]
// ---------------------------------------------------------------------------

StByteToTextTranslator::StByteToTextTranslator(Handle inHandle)
{
	mInHandle = inHandle;
	mInSize = ::GetHandleSize(inHandle);
	mOutSize = mInSize;
	mOutHandle = ::NewHandle( mOutSize );
	ThrowIfMemError_();
}


// ---------------------------------------------------------------------------
//	¥ StByteToTextTranslator					Constructor			  [public]
// ---------------------------------------------------------------------------

StByteToTextTranslator::StByteToTextTranslator(const void * inPtr, SInt32 inByteCount)
{
	mInHandle = ::NewHandle(inByteCount);
	mInSize = inByteCount;
	BlockMoveData(inPtr, *mInHandle, inByteCount);
	mOutSize = mInSize;
	mOutHandle = ::NewHandle( mOutSize );
	ThrowIfMemError_();
}


// ---------------------------------------------------------------------------
//	¥ ~StByteToTextTranslator					Destructor			  [public]
// ---------------------------------------------------------------------------

StByteToTextTranslator::~StByteToTextTranslator()
{
	// It should not be nil, but who knows...
	if (mOutHandle != nil) {
		::DisposeHandle(mOutHandle);
	} 
}


// ---------------------------------------------------------------------------
//	¥ Convert													[public]
// ---------------------------------------------------------------------------

void
StByteToTextTranslator::Convert()
{
	StHandleLocker locker(mInHandle);
	
	LDataStream inStream(*mInHandle, mInSize);
	LDataStream outStream(*mOutHandle, mOutSize);
	
	UCodeTranslator::ConvertByteToReadable(&inStream, &outStream, false);
}


// =====================================
//  CLASS StStripBlanksTranslator
// =====================================

// ---------------------------------------------------------------------------
//	¥ StStripBlanksTranslator					Constructor			  [public]
// ---------------------------------------------------------------------------

StStripBlanksTranslator::StStripBlanksTranslator(Handle inHandle)
{
	mInHandle = inHandle;
	mSize = ::GetHandleSize(inHandle);
	mOutHandle = ::NewHandle(mSize);
	ThrowIfNil_(mOutHandle);
}


// ---------------------------------------------------------------------------
//	¥ ~StStripBlanksTranslator					Destructor			  [public]
// ---------------------------------------------------------------------------

StStripBlanksTranslator::~StStripBlanksTranslator()
{
	// It should not be nil, but who knows...
	if (mOutHandle != nil) {
		::DisposeHandle(mOutHandle);
	} 
}


// ---------------------------------------------------------------------------
//	¥ StripAscii													[public]
// ---------------------------------------------------------------------------

void
StStripBlanksTranslator::FilterOutBlanks()
{
	StHandleLocker locker(mInHandle);
	
	LDataStream inStream(*mInHandle, mSize);
	LDataStream outStream(*mOutHandle, mSize);
	
	mSize = UCodeTranslator::StripBlanks(&inStream, &outStream);
	::SetHandleSize(mOutHandle, mSize);
	ThrowIfMemError_();
}




// =====================================
//  CLASS StStripPeriodicalTranslator
// =====================================

// ---------------------------------------------------------------------------
//	¥ StStripPeriodicalTranslator					Constructor			  [public]
// ---------------------------------------------------------------------------

StStripPeriodicalTranslator::StStripPeriodicalTranslator(Handle inHandle, UInt16 inPeriod)
{
	mInHandle = inHandle;
	mPeriod = inPeriod;
	mSize = ::GetHandleSize(inHandle);
	mOutHandle = ::NewHandle(mSize);
	ThrowIfNil_(mOutHandle);
}


// ---------------------------------------------------------------------------
//	¥ ~StStripPeriodicalTranslator					Destructor			  [public]
// ---------------------------------------------------------------------------

StStripPeriodicalTranslator::~StStripPeriodicalTranslator()
{
	// It should not be nil, but who knows...
	if (mOutHandle != nil) {
		::DisposeHandle(mOutHandle);
	} 
}


// ---------------------------------------------------------------------------
//	¥ StripAscii													[public]
// ---------------------------------------------------------------------------

void
StStripPeriodicalTranslator::FilterOutPeriodical()
{
	StHandleLocker locker(mInHandle);
	
	LDataStream inStream(*mInHandle, mSize);
	LDataStream outStream(*mOutHandle, mSize);
	
	mSize = UCodeTranslator::StripPeriodical(&inStream, &outStream, mPeriod);
	::SetHandleSize(mOutHandle, mSize);
	ThrowIfMemError_();
}




PP_End_Namespace_PowerPlant
