// ===========================================================================
// UBitUtils.h
//                       Created: 2004-12-11 18:51:53
//             Last modification: 2004-12-14 18:51:53
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

	
class UBitUtils
{
	public:
		static UInt8		GetBit( void *firstByte, SInt32 bitNo );
		static void			SetBit( void *firstByte, SInt32 bitNo, UInt8 inValue );

		static UInt8		GetNibble( void *firstByte, SInt32 nibbleNo );
		static void			SetNibble( void *firstByte, SInt32 nibbleNo, UInt8 inValue );
		
		static UInt8		GetTwoBits( void *firstByte, SInt32 index );
		static void			SetTwoBits( void *firstByte, SInt32 index, UInt8 inValue );
};

