// ===========================================================================
// UPixelHelper.h
//                       Created: 2004-12-11 18:57:22
//             Last modification: 2004-12-15 13:47:46
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
// 
// (1) This is implemented using static functions rather than virtual ones
// for speed -- pixel lookups tend to be very time sensitive.
// 
// (2) #define PixelDebugIf() below if you want to check for negative or
// nil values.
// 
// (3) These routines will blindly trash memory if you pass in invalid
// pointers, so be very very careful when using them.

#ifndef _H_UPixelHelper
#define _H_UPixelHelper


#include "RezillaConstants.h"

typedef Color32		(*SUPixelGetter)( RawPtr rowPtr, SInt32 h );
typedef void		(*SUPixelSetter)( RawPtr rowPtr, SInt32 h, Color32 inColor );

class UPixelHelper
{
	public:
		static void				GetPixelFunctions( SInt32 inDepth, 
											SUPixelGetter *, SUPixelSetter * );
										
		static Color32			GetColor32( RawPtr rowPtr, SInt32 h );
		static Color32			GetColor16( RawPtr rowPtr, SInt32 h );
		static Color32			GetColor8( RawPtr rowPtr, SInt32 h );
		static Color32			GetColor4( RawPtr rowPtr, SInt32 h );
		static Color32			GetColor2( RawPtr rowPtr, SInt32 h );
		static Color32			GetColor1( RawPtr rowPtr, SInt32 h );
		
		static void				SetColor32( RawPtr rowPtr, SInt32 h, Color32 );
		static void				SetColor16( RawPtr rowPtr, SInt32 h, Color32 );
		static void				SetColor8( RawPtr rowPtr, SInt32 h, Color32 );
		static void				SetColor4( RawPtr rowPtr, SInt32 h, Color32 );
		static void				SetColor2( RawPtr rowPtr, SInt32 h, Color32 );
		static void				SetColor1( RawPtr rowPtr, SInt32 h, Color32 );
};



// ---------------------------------------------------------------------------
// 	Pixel debugging
// 	
// 	The pixel routines normally do no error checking since they are speed critical.
// 	Enable the lower #define to put the error checking code back in
// ---------------------------------------------------------------------------

#define PixelDebugIf( x )
//#define PixelDebugIf( x )	if ( x ) DebugStr("\pPixel Problems" );


// ---------------------------------------------------------------------------
// 	GetColor32
// ---------------------------------------------------------------------------

inline Color32 UPixelHelper::GetColor32( RawPtr rowPtr, SInt32 h )
{
	PixelDebugIf( !rowPtr || (h < 0) );

	return( *( h + (UInt32*) rowPtr ) );
}


// ---------------------------------------------------------------------------
// 	SetColor32
// ---------------------------------------------------------------------------

inline void UPixelHelper::SetColor32( RawPtr rowPtr, SInt32 h, Color32 inColor )
{
	PixelDebugIf( !rowPtr || (h < 0) );

	*( h + (UInt32*) rowPtr ) = inColor;
}


// ---------------------------------------------------------------------------
// 	GetColor16
// ---------------------------------------------------------------------------

inline Color32 UPixelHelper::GetColor16( RawPtr rowPtr, SInt32 h )
{
	PixelDebugIf( !rowPtr || (h < 0) );

	return( *( h + (UInt16*) rowPtr ) );
}


// ---------------------------------------------------------------------------
// 	SetColor16
// ---------------------------------------------------------------------------

inline void UPixelHelper::SetColor16( RawPtr rowPtr, SInt32 h, Color32 inColor )
{
	PixelDebugIf( !rowPtr || (h < 0) || (inColor > 0x0000FFFF) );

	*( h + (UInt16*) rowPtr ) = (UInt16) inColor;
}


// ---------------------------------------------------------------------------
// 	GetColor8
// ---------------------------------------------------------------------------

inline Color32 UPixelHelper::GetColor8( RawPtr rowPtr, SInt32 h )
{
	PixelDebugIf( !rowPtr || (h < 0) );

	return( *( h + (UInt8*) rowPtr ) );
}


// ---------------------------------------------------------------------------
// 	SetColor8
// ---------------------------------------------------------------------------

inline void UPixelHelper::SetColor8( RawPtr rowPtr, SInt32 h, Color32 inColor )
{
	PixelDebugIf( !rowPtr || (h < 0) || (inColor > 255) );

	*( h + (UInt8*) rowPtr ) = (UInt8) inColor;
}


// ---------------------------------------------------------------------------
// 	GetColor4
// ---------------------------------------------------------------------------

inline Color32 UPixelHelper::GetColor4( RawPtr rowPtr, SInt32 h )
{
	PixelDebugIf( !rowPtr || (h < 0) );

	UInt8	theValue;
	
	theValue = *( (UInt8*) rowPtr + (h>>1) );
	if ( h & 1 )
		return( theValue & 0x0F );
	else
		return( (theValue >> 4) & 0x0F );
}


// ---------------------------------------------------------------------------
// 	SetColor4
// ---------------------------------------------------------------------------

inline void UPixelHelper::SetColor4( RawPtr rowPtr, SInt32 h, Color32 inColor )
{
	PixelDebugIf( !rowPtr || (h < 0) || (inColor > 15) );

	UInt8	*bytePtr = (UInt8*) rowPtr + (h>>1);
	UInt8	nibbleValue = (UInt8) inColor;			// get low byte
	
	if ( h & 1 )
		*bytePtr = (*bytePtr & 0xF0) | nibbleValue;
	else
		*bytePtr = (*bytePtr & 0x0F) | (nibbleValue << 4);
}


// ---------------------------------------------------------------------------
// 	GetColor2
// ---------------------------------------------------------------------------

inline Color32 UPixelHelper::GetColor2( RawPtr rowPtr, SInt32 h )
{
	PixelDebugIf( !rowPtr || (h < 0) );

	UInt8			theValue;
	static UInt8	shifts[] = { 6, 4, 2, 0 };
	
	theValue = *( (UInt8*) rowPtr + (h>>2) );
	return( (theValue >> shifts[ h & 0x03 ]) & 0x03 );
}


// ---------------------------------------------------------------------------
// 	SetColor2
// ---------------------------------------------------------------------------

inline void UPixelHelper::SetColor2( RawPtr rowPtr, SInt32 h, Color32 inColor )
{
	PixelDebugIf( !rowPtr || (h < 0) || (inColor > 3) );

	static UInt8	shifts[] = { 6, 4, 2, 0 };

	UInt8	*bytePtr = (UInt8*) rowPtr + (h>>2);
	UInt8	shiftBy = shifts[ h & 0x03 ];
	UInt8	clearMask = ~(0x3 << shiftBy);
	*bytePtr = (*bytePtr & clearMask) | (inColor << shiftBy) ;
}


// ---------------------------------------------------------------------------
// 	GetColor1
// ---------------------------------------------------------------------------

inline Color32 UPixelHelper::GetColor1( RawPtr rowPtr, SInt32 h )
{
	PixelDebugIf( !rowPtr || (h < 0) );

	SInt32 	byteIndex = (h >> 3);
	SInt32	bitNo = h & 0x07;
	UInt8	bitMask = 0x0080 >> bitNo;

	if ( *(byteIndex + (UInt8*)rowPtr) & bitMask )
		return( 1 );
	else
		return( 0 );
}


// ---------------------------------------------------------------------------
// 	SetColor1
// ---------------------------------------------------------------------------

inline void UPixelHelper::SetColor1( RawPtr rowPtr, SInt32 h, Color32 inColor )
{
	PixelDebugIf( !rowPtr || (h < 0) || (inColor > 1) );
	
	SInt32 	byteIndex = (h >> 3);
	SInt32	bitNo = h & 0x07;
	UInt8	bitMask = 0x0080 >> bitNo;

	if ( inColor )
		*( (UInt8*) rowPtr + byteIndex ) |= bitMask;		// set bit
	else
		*( (UInt8*) rowPtr + byteIndex ) &= ~bitMask;		// clear bit
}

#endif // _H_UPixelHelper
