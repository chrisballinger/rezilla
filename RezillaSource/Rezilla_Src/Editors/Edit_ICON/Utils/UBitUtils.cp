// ===========================================================================
// UBitUtils.cp
//                       Created: 2004-12-11 18:51:53
//             Last modification: 2004-12-15 10:12:58
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "UBitUtils.h"


// ---------------------------------------------------------------------------
// 	GetBit
// ---------------------------------------------------------------------------
// Returns 0..1

UInt8
UBitUtils::GetBit( void *firstByte, SInt32 flagNo )
{
	SInt32 	byteIndex = (flagNo >> 3);
	SInt32	bitNo = flagNo & 0x07;
	UInt8	bitMask = 0x0080 >> bitNo;

	if ( *(byteIndex + (UInt8*)firstByte) & bitMask )
		return( 1 );
	else
		return( 0 );
}


// ---------------------------------------------------------------------------
// 	SetBit
// ---------------------------------------------------------------------------

void
UBitUtils::SetBit( void *firstByte, SInt32 flagNo, UInt8 inValue )
{
	ThrowIf_( inValue >= 2 );

	SInt32 	byteIndex = (flagNo >> 3);
	SInt32	bitNo = flagNo & 0x07;
	UInt8	bitMask = 0x0080 >> bitNo;

	if ( inValue )
		*( (UInt8*) firstByte + byteIndex ) |= bitMask;		// set bit
	else
		*( (UInt8*) firstByte + byteIndex ) &= ~bitMask;	// clear bit
}


// ---------------------------------------------------------------------------
// 	GetNibble
// ---------------------------------------------------------------------------
// 	Returns 0..15

UInt8
UBitUtils::GetNibble( void *firstByte, SInt32 nibbleNo )
{
	UInt8	theValue;
	
	theValue = *( (UInt8*) firstByte + (nibbleNo>>1) );
	if ( nibbleNo & 1 )
		return( theValue & 0x0F );
	else
		return( (theValue >> 4) & 0x0F );
}


// ---------------------------------------------------------------------------
// 	SetNibble
// ---------------------------------------------------------------------------
// nibbleValue is 0..15

void
UBitUtils::SetNibble( void *firstByte, SInt32 nibbleNo, UInt8 nibbleValue )
{
	ThrowIf_( nibbleValue >= 16 );

	UInt8	*bytePtr = (UInt8*) firstByte + (nibbleNo>>1);
		
	if ( nibbleNo & 1 )
		*bytePtr = (*bytePtr & 0xF0) | nibbleValue;
	else
		*bytePtr = (*bytePtr & 0x0F) | (nibbleValue << 4);
}


// ---------------------------------------------------------------------------
// 	GetTwoBits
// ---------------------------------------------------------------------------
// Returns 0..3

UInt8
UBitUtils::GetTwoBits( void *firstByte, SInt32 index )
{
	UInt8			theValue;
	static UInt8	shifts[] = { 6, 4, 2, 0 };
	
	theValue = *( (UInt8*) firstByte + (index>>2) );
	return( (theValue >> shifts[ index & 0x03 ]) & 0x03 );
}


// ---------------------------------------------------------------------------
// 	SetTwoBits
// ---------------------------------------------------------------------------
// nibbleValue is 0..3

void
UBitUtils::SetTwoBits( void *firstByte, SInt32 index, UInt8 inValue )
{
	static UInt8	shifts[] = { 6, 4, 2, 0 };

	ThrowIf_( inValue >= 4 );

	UInt8	*bytePtr = (UInt8*) firstByte + (index>>2);
	UInt8	shiftBy = shifts[ index & 0x03 ];
	UInt8	clearMask = ~(0x3 << shiftBy);
	*bytePtr = (*bytePtr & clearMask) | (inValue << shiftBy) ;
}
