// ===========================================================================
// UCodeTranslator.h					
// 
// Â© 2002, Bernard Desgraupes, All rights reserved.
//                       Created: 2003-05-04 16:40:47
//             Last modification: 2004-02-22 19:49:55
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// Â© Copyright: Bernard Desgraupes 2003, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#ifndef _H_UCodeTranslator
#define _H_UCodeTranslator
#pragma once

#include <LFileStream.h>


#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant


enum Hextype {
	hextype__undefined = 0,
	hextype__ascii,
	hextype__hex,
	hextype__text,
	hextype__incoherent
};



// ---------------------------------------------------------------------------

class UCodeTranslator {
public:
	
	static void		ConvertAsciiToReadable( LDataStream* srcDataStream, LDataStream* trgtDataStream );

	static void		ConvertAsciiToReadable( char* srcString, char* trgtString );

	static void		ConvertBytesToSeparateHex( LDataStream* srcDataStream, LDataStream* trgtDataStream );

	static void		ConvertBytesToSeparateHex( char* srcString, char* trgtString );

	static void		ConvertBytesToHex( LDataStream* srcDataStream, LDataStream* trgtDataStream );

	static void		ConvertBytesToHex( char* srcString, char* trgtString );

	static void		ConvertHexToCode(LDataStream* srcDataStream, LDataStream* trgtDataStream );

	static void		ConvertHexToCode( char* srcString, char* trgtString );

	static SInt32	StripBlanks(LDataStream* srcDataStream, LDataStream* trgtDataStream );

	static SInt32	StripBlanks( char* srcString, char* trgtString );

	static SInt32	StripPeriodical( LDataStream* srcDataStream, LDataStream* trgtDataStream, UInt16 inPeriod);
	
	static UInt8	ConvertHexToValue(UInt8 inHex);

};


// ===========================================================================
//	¥ Stack-based classes
// ===========================================================================

// ---------------------------------------------------------------------------
//  ¥ class StHexTranslator
// ---------------------------------------------------------------------------
class StHexTranslator {
public:
						StHexTranslator( Handle	inHandle );
						StHexTranslator(const void * inPtr, SInt32 inByteCount);
						~StHexTranslator();

	void			ConvertToHex();

	virtual Handle	GetOutHandle() { return mOutHandle;}

	virtual Size	GetOutSize() { return mOutSize;}

private:
	Handle	mInHandle;
	Handle	mOutHandle;
	Size	mInSize;
	Size	mOutSize;

};


// ---------------------------------------------------------------------------
//  ¥ class StHexToCodeTranslator
// ---------------------------------------------------------------------------
class StHexToCodeTranslator {
public:
						StHexToCodeTranslator( Handle	inHandle );
						~StHexToCodeTranslator();

	void			HexToCode();

	virtual Handle	GetOutHandle() { return mOutHandle;}

	virtual Size	GetOutSize() { return mOutSize;}

private:
	Handle	mInHandle;
	Handle	mOutHandle;
	Size	mInSize;
	Size	mOutSize;

};


// ---------------------------------------------------------------------------
//  ¥ class StReadableTranslator
// ---------------------------------------------------------------------------
class StReadableTranslator {
public:
						StReadableTranslator( Handle	inHandle );
						StReadableTranslator(const void * inPtr, SInt32 inByteCount);
						~StReadableTranslator();

	void				FilterReadable();

	virtual Handle		GetOutHandle() { return mOutHandle;}

	virtual Size		GetOutSize() { return mOutSize;}

	Handle	mInHandle;
	Handle	mOutHandle;
	Size	mInSize;
	Size	mOutSize;
};


// ---------------------------------------------------------------------------
//  ¥ class StStripBlanksTranslator
// ---------------------------------------------------------------------------
class StStripBlanksTranslator {
public:
						StStripBlanksTranslator( Handle	inHandle );
						~StStripBlanksTranslator();

	void				FilterOutBlanks();

	virtual Handle		GetOutHandle() { return mOutHandle;}

	virtual Size		GetOutSize() { return mSize;}

	Handle	mInHandle;
	Handle	mOutHandle;
	Size	mSize;
};


// ---------------------------------------------------------------------------
//  ¥ class StStripPeriodicalTranslator
// ---------------------------------------------------------------------------
class StStripPeriodicalTranslator {
public:
						StStripPeriodicalTranslator( Handle	inHandle, UInt16 inPeriod );
						~StStripPeriodicalTranslator();

	void				FilterOutPeriodical();

	virtual Handle		GetOutHandle() { return mOutHandle;}

	virtual Size		GetOutSize() { return mSize;}

	Handle	mInHandle;
	Handle	mOutHandle;
	Size	mSize;
	UInt16	mPeriod;
};





PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif

