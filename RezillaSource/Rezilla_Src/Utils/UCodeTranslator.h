// ===========================================================================
// UCodeTranslator.h					
// 
//                       Created: 2003-05-04 16:40:47
//             Last modification: 2004-03-23 23:00:09
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2003-2004
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

// Filling character used at the end of a Base64 encoded string.
const char kFillChar = '=';



// ---------------------------------------------------------------------------

class UCodeTranslator {
public:
	
	static void		ConvertByteToReadable( LDataStream* srcDataStream, LDataStream* trgtDataStream, Boolean inInsertSpace);

	static void		ConvertByteToReadable( char* srcString, char* trgtString, Boolean inInsertSpace);

	static void		ConvertByteToSeparatedHex( LDataStream* srcDataStream, LDataStream* trgtDataStream );

	static void		ConvertByteToSeparatedHex( char* srcString, char* trgtString );

	static void		ConvertByteToHex( LDataStream* srcDataStream, LDataStream* trgtDataStream );

	static void		ConvertByteToHex( char* srcString, char* trgtString );

	static void		ConvertHexToByte( LDataStream* srcDataStream, LDataStream* trgtDataStream );

	static void		ConvertHexToByte( char* srcString, char* trgtString );

	static void		ConvertByteToBase64( LDataStream* srcDataStream, LDataStream* trgtDataStream );

	static void		ConvertByteToBase64( char* srcString, char* trgtString );

	static void		ConvertBase64ToByte( LDataStream* srcDataStream, LDataStream* trgtDataStream );

	static void		ConvertBase64ToByte( char* srcString, char* trgtString );

	static SInt32	StripBlanks( LDataStream* srcDataStream, LDataStream* trgtDataStream );

	static SInt32	StripBlanks( char* srcString, char* trgtString );

	static SInt32	StripPeriodical( LDataStream* srcDataStream, LDataStream* trgtDataStream, UInt16 inPeriod);
	
	static UInt8	ConvertHexToValue(UInt8 inHex);
	
	static int		ConvertToNumber(UInt8 inByte);

};


// ===========================================================================
//	¥ Stack-based classes
// ===========================================================================

// ---------------------------------------------------------------------------
//  ¥ class StSepHexTranslator
// ---------------------------------------------------------------------------
class StSepHexTranslator {
public:
						StSepHexTranslator( Handle	inHandle );
						StSepHexTranslator(const void * inPtr, SInt32 inByteCount);
						~StSepHexTranslator();

	void			Convert();

	virtual Handle	GetOutHandle() { return mOutHandle;}

	virtual Size	GetOutSize() { return mOutSize;}

private:
	Handle	mInHandle;
	Handle	mOutHandle;
	Size	mInSize;
	Size	mOutSize;

};


// ---------------------------------------------------------------------------
//  ¥ class StByteToHexTranslator
// ---------------------------------------------------------------------------
class StByteToHexTranslator {
public:
						StByteToHexTranslator( Handle	inHandle );
						StByteToHexTranslator(const void * inPtr, SInt32 inByteCount);
						~StByteToHexTranslator();

	void			Convert();

	virtual Handle	GetOutHandle() { return mOutHandle;}

	virtual Size	GetOutSize() { return mOutSize;}

private:
	Handle	mInHandle;
	Handle	mOutHandle;
	Size	mInSize;
	Size	mOutSize;

};


// ---------------------------------------------------------------------------
//  ¥ class StHexToByteTranslator
// ---------------------------------------------------------------------------
class StHexToByteTranslator {
public:
						StHexToByteTranslator( Handle	inHandle );
						~StHexToByteTranslator();

	void			Convert();

	virtual Handle	GetOutHandle() { return mOutHandle;}

	virtual Size	GetOutSize() { return mOutSize;}

private:
	Handle	mInHandle;
	Handle	mOutHandle;
	Size	mInSize;
	Size	mOutSize;

};


// ---------------------------------------------------------------------------
//  ¥ class StByteToBase64Translator
// ---------------------------------------------------------------------------
class StByteToBase64Translator {
public:
						StByteToBase64Translator( Handle	inHandle );
						StByteToBase64Translator(const void * inPtr, SInt32 inByteCount);
						~StByteToBase64Translator();

	void			Convert();

	virtual Handle	GetOutHandle() { return mOutHandle;}

	virtual Size	GetOutSize() { return mOutSize;}

private:
	Handle	mInHandle;
	Handle	mOutHandle;
	Size	mInSize;
	Size	mOutSize;

};


// ---------------------------------------------------------------------------
//  ¥ class StBase64ToByteTranslator
// ---------------------------------------------------------------------------
class StBase64ToByteTranslator {
public:
						StBase64ToByteTranslator( Handle	inHandle );
						StBase64ToByteTranslator(const void * inPtr, SInt32 inByteCount);
						~StBase64ToByteTranslator();

	void			Convert();

	virtual Handle	GetOutHandle() { return mOutHandle;}

	virtual Size	GetOutSize() { return mOutSize;}

private:
	Handle	mInHandle;
	Handle	mOutHandle;
	Size	mInSize;
	Size	mOutSize;

};


// ---------------------------------------------------------------------------
//  ¥ class StSepTextTranslator
// ---------------------------------------------------------------------------
class StSepTextTranslator {
public:
						StSepTextTranslator( Handle	inHandle );
						StSepTextTranslator(const void * inPtr, SInt32 inByteCount);
						~StSepTextTranslator();

	void				Convert();

	virtual Handle		GetOutHandle() { return mOutHandle;}

	virtual Size		GetOutSize() { return mOutSize;}

	Handle	mInHandle;
	Handle	mOutHandle;
	Size	mInSize;
	Size	mOutSize;
};


// ---------------------------------------------------------------------------
//  ¥ class StByteToTextTranslator
// ---------------------------------------------------------------------------
class StByteToTextTranslator {
public:
						StByteToTextTranslator( Handle	inHandle );
						StByteToTextTranslator(const void * inPtr, SInt32 inByteCount);
						~StByteToTextTranslator();

	void				Convert();

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
