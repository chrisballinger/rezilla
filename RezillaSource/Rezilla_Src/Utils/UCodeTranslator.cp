// ===========================================================================
// UCodeTranslator.cp					
// 
// © 2002, Bernard Desgraupes, All rights reserved.
//                       Created : 2003-05-04 16:40:47
//             Last modification : 2003-06-02 18:58:13
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@easyconnect.fr>
// www : <http://webperso.easyconnect.fr/bdesgraupes/>
// ===========================================================================


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "UCodeTranslator.h"

#include <LString.h>
#include <UMemoryMgr.h>

// #include <regex.h>
#include <string.h>
#include <stdio.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//	€ ConvertAsciiToReadable											[public]
// ---------------------------------------------------------------------------
// 0xF6 (246) is – and 0xFF (255) is .
// 0x5E (94) is – too.

void
UCodeTranslator::ConvertAsciiToReadable( LDataStream* srcDataStream, LDataStream* trgtDataStream )
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
		*trgtDataStream << (char) 0x20;
	}
}


// ---------------------------------------------------------------------------
//	€ ConvertAsciiToReadable										[public]
// ---------------------------------------------------------------------------

void
UCodeTranslator::ConvertAsciiToReadable(char* srcString, char* trgtString )
{
}


// // ---------------------------------------------------------------------------
// //	€ ConvertAsciiToReadable									[public]
// // ---------------------------------------------------------------------------
// 
// void
// UCodeTranslator::ConvertAsciiToReadable(char srcChar, char trgtChar )
// {
// }


// ---------------------------------------------------------------------------
//	€ ConvertAsciiToHex												[public]
// ---------------------------------------------------------------------------
// This function supposes that the src and trgt streams are properly allocated. 
// The size of trgtDataStream should be three times the size of srcDataStream.
// 	char nbsp = (char) 0xCA;	// nbsp

void
UCodeTranslator::ConvertAsciiToHex( LDataStream* srcDataStream, LDataStream* trgtDataStream )
{
	UInt8 readChar;
	char * buffer = new char[3];
	SInt32 length = srcDataStream->GetLength();
	
	for (UInt32 i = 1; i <= length; i++) {
		*srcDataStream >> readChar;
		sprintf(buffer, "%.2x ", readChar);
		trgtDataStream->WriteBlock(buffer,3);
	}
}


// ---------------------------------------------------------------------------
//	€ ConvertAsciiToHex												[public]
// ---------------------------------------------------------------------------
// This function supposes that the src and trgt strings are properly allocated. 
// The size of trgtString should be three times the size of srcString.

void
UCodeTranslator::ConvertAsciiToHex(char* srcString, char* trgtString )
{
	char * buffer = new char[3];
	SInt32 pos = 0;
	
	do {
		sprintf(buffer, "%.2x ", (UInt8) *srcString);
		::BlockMoveData(buffer, trgtString + pos, 3);
		pos += 3;
	} while (*srcString++);
}


// ---------------------------------------------------------------------------
//	€ ConvertHexToCode												[public]
// ---------------------------------------------------------------------------
// This function converts a stream of hex data to their UInt8 values. If the 
// size of the srcDataStream is odd, the last char is discarded. 

void
UCodeTranslator::ConvertHexToCode( LDataStream* srcDataStream, LDataStream* trgtDataStream )
{
	UInt8 readChar;
	UInt8 val1 = 0;
	UInt8 val2 = 0;
	SInt32 length = srcDataStream->GetLength() ;
	UInt8 result;
	
	for (UInt32 i = 1; i <= length; i += 2) {
		*srcDataStream >> readChar;
		if (readChar != 0x30) {
			val1 = ConvertHexToValue(readChar);
		}
		*srcDataStream >> readChar;
		if (readChar != 0x30) {
			val2 = ConvertHexToValue(readChar);
		}
		*trgtDataStream << (UInt8) (16 * val1 + val2);
	}
}


// ---------------------------------------------------------------------------
//	€ ConvertHexToValue												[public]
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
//	€ ConvertHexToCode												[public]
// ---------------------------------------------------------------------------

void
UCodeTranslator::ConvertHexToCode(char* srcString, char* trgtString)
{
	SInt32	theLength = strlen(srcString);

	LDataStream inStream(srcString, theLength);
	LDataStream outStream(trgtString, theLength/2);
	ConvertHexToCode(&inStream, &outStream);
	trgtString[theLength/2] = 0;
}


// ---------------------------------------------------------------------------
//	€ StripBlanks													[public]
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
//	€ StripBlanks													[public]
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
//	€ StripPeriodical												[public]
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



// ===========================================================================
//	€ Stack-based classes
// ===========================================================================

// =====================================
//  CLASS StHexTranslator
// =====================================

// ---------------------------------------------------------------------------
//	€ StHexTranslator							Constructor			  [public]
// ---------------------------------------------------------------------------

StHexTranslator::StHexTranslator(Handle inHandle)
{
	mInHandle = inHandle;
	mInSize = ::GetHandleSize(inHandle);
	mOutSize = 3 * mInSize;
	mOutHandle = ::NewHandle( mOutSize );
	ThrowIfNil_(mOutHandle);
}


// ---------------------------------------------------------------------------
//	€ StHexTranslator							Constructor			  [public]
// ---------------------------------------------------------------------------

StHexTranslator::StHexTranslator(const void * inPtr, SInt32 inByteCount)
{
	mInHandle = ::NewHandle(inByteCount);
	mInSize = inByteCount;
	BlockMoveData(inPtr, *mInHandle, inByteCount);
	mOutSize = 3 * mInSize;
	mOutHandle = ::NewHandle( mOutSize );
	ThrowIfNil_(mOutHandle);
}


// ---------------------------------------------------------------------------
//	€ ~StHexTranslator						Destructor				  [public]
// ---------------------------------------------------------------------------

StHexTranslator::~StHexTranslator()
{
	// It should not be nil, but who knows...
	if (mOutHandle != nil) {
		::DisposeHandle(mOutHandle);
	} 
}


// ---------------------------------------------------------------------------
//	 ConvertToHex													[public]
// ---------------------------------------------------------------------------

void
StHexTranslator::ConvertToHex()
{
	StHandleLocker locker(mInHandle);
	
	LDataStream inStream(*mInHandle, mInSize);
	LDataStream outStream(*mOutHandle, mOutSize);
	
	UCodeTranslator::ConvertAsciiToHex(&inStream, &outStream);
}




// =====================================
//  CLASS StHexToCodeTranslator
// =====================================

// ---------------------------------------------------------------------------
//	€ StHexToCodeTranslator							Constructor		  [public]
// ---------------------------------------------------------------------------

StHexToCodeTranslator::StHexToCodeTranslator(Handle inHandle)
{
	mInHandle = inHandle;
	mInSize = ::GetHandleSize(inHandle);
	mOutSize = mInSize/2;
	mOutHandle = ::NewHandle( mOutSize );
	ThrowIfNil_(mOutHandle);
}


// ---------------------------------------------------------------------------
//	€ ~StHexToCodeTranslator						Destructor		  [public]
// ---------------------------------------------------------------------------

StHexToCodeTranslator::~StHexToCodeTranslator()
{
	// It should not be nil, but who knows...
	if (mOutHandle != nil) {
		::DisposeHandle(mOutHandle);
	} 
}


// ---------------------------------------------------------------------------
//	 HexToCode														[public]
// ---------------------------------------------------------------------------

void
StHexToCodeTranslator::HexToCode()
{
	StHandleLocker locker(mInHandle);
	
	LDataStream inStream(*mInHandle, mInSize);
	LDataStream outStream(*mOutHandle, mOutSize);
// 	inStream.SetMarker(0L,streamFrom_Start);
	
	UCodeTranslator::ConvertHexToCode(&inStream, &outStream);
}


// =====================================
//  CLASS StReadableTranslator
// =====================================

// ---------------------------------------------------------------------------
//	€ StReadableTranslator					Constructor			  [public]
// ---------------------------------------------------------------------------

StReadableTranslator::StReadableTranslator(Handle inHandle)
{
	mInHandle = inHandle;
	mInSize = ::GetHandleSize(inHandle);
	mOutSize = 2 * mInSize;
	mOutHandle = ::NewHandle( mOutSize );
	OSErr err = MemError();
	ThrowIfNil_(mOutHandle);
}


// ---------------------------------------------------------------------------
//	€ StReadableTranslator					Constructor			  [public]
// ---------------------------------------------------------------------------

StReadableTranslator::StReadableTranslator(const void * inPtr, SInt32 inByteCount)
{
	mInHandle = ::NewHandle(inByteCount);
	mInSize = inByteCount;
	BlockMoveData(inPtr, *mInHandle, inByteCount);
	mOutSize = 2 * mInSize;
	mOutHandle = ::NewHandle( mOutSize );
	OSErr err = MemError();
	ThrowIfNil_(mOutHandle);
}


// ---------------------------------------------------------------------------
//	€ ~StReadableTranslator					Destructor			  [public]
// ---------------------------------------------------------------------------

StReadableTranslator::~StReadableTranslator()
{
	// It should not be nil, but who knows...
	if (mOutHandle != nil) {
		::DisposeHandle(mOutHandle);
	} 
}


// ---------------------------------------------------------------------------
//	€ FilterReadable													[public]
// ---------------------------------------------------------------------------

void
StReadableTranslator::FilterReadable()
{
	StHandleLocker locker(mInHandle);
	
	LDataStream inStream(*mInHandle, mInSize);
	LDataStream outStream(*mOutHandle, mOutSize);
	
	UCodeTranslator::ConvertAsciiToReadable(&inStream, &outStream);
}




// =====================================
//  CLASS StStripBlanksTranslator
// =====================================

// ---------------------------------------------------------------------------
//	€ StStripBlanksTranslator					Constructor			  [public]
// ---------------------------------------------------------------------------

StStripBlanksTranslator::StStripBlanksTranslator(Handle inHandle)
{
	mInHandle = inHandle;
	mSize = ::GetHandleSize(inHandle);
	mOutHandle = ::NewHandle(mSize);
	ThrowIfNil_(mOutHandle);
}


// ---------------------------------------------------------------------------
//	€ ~StStripBlanksTranslator					Destructor			  [public]
// ---------------------------------------------------------------------------

StStripBlanksTranslator::~StStripBlanksTranslator()
{
	// It should not be nil, but who knows...
	if (mOutHandle != nil) {
		::DisposeHandle(mOutHandle);
	} 
}


// ---------------------------------------------------------------------------
//	€ StripAscii													[public]
// ---------------------------------------------------------------------------

void
StStripBlanksTranslator::FilterOutBlanks()
{
	StHandleLocker locker(mInHandle);
	
	LDataStream inStream(*mInHandle, mSize);
	LDataStream outStream(*mOutHandle, mSize);
	
	mSize = UCodeTranslator::StripBlanks(&inStream, &outStream);
	::SetHandleSize(mOutHandle, mSize);
// 	err = MemError();
}




// =====================================
//  CLASS StStripPeriodicalTranslator
// =====================================

// ---------------------------------------------------------------------------
//	€ StStripPeriodicalTranslator					Constructor			  [public]
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
//	€ ~StStripPeriodicalTranslator					Destructor			  [public]
// ---------------------------------------------------------------------------

StStripPeriodicalTranslator::~StStripPeriodicalTranslator()
{
	// It should not be nil, but who knows...
	if (mOutHandle != nil) {
		::DisposeHandle(mOutHandle);
	} 
}


// ---------------------------------------------------------------------------
//	€ StripAscii													[public]
// ---------------------------------------------------------------------------

void
StStripPeriodicalTranslator::FilterOutPeriodical()
{
	StHandleLocker locker(mInHandle);
	
	LDataStream inStream(*mInHandle, mSize);
	LDataStream outStream(*mOutHandle, mSize);
	
	mSize = UCodeTranslator::StripPeriodical(&inStream, &outStream, mPeriod);
	::SetHandleSize(mOutHandle, mSize);
// 	err = MemError();
}




PP_End_Namespace_PowerPlant
