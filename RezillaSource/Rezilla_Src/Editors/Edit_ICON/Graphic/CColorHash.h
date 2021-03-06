// ===========================================================================
// CColorHash.h
//                       Created: 2004-12-11 18:56:40
//             Last modification: 2004-12-14 18:56:40
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// ===========================================================================

#ifndef _H_CColorHash
#define _H_CColorHash

#include "RezillaConstants.h"

// Most of these routines are inline because they are called for every
// pixel in large buffers. This is one area where the overhead of a virtual
// method might really be noticeable.


class CColorHash {
	public:
								CColorHash( Boolean forceBW = false );
		virtual					~CColorHash();
	
		inline		void		AddColorToHash( Color32 );				
		SInt32					LookupAssociatedNumber( Color32 );
		inline 		SInt32		GetColorCount() { return mUniquePixels; };
		
					CTabHandle	BuildColorTable( Boolean inMinimizeTable = true );
					void		FixBlackAndWhite( Boolean inMinimizeTable = true );
				
	protected:

		#define kHashArrayLimit		12000
		#define kEmptyColorSlot		0xFFFFFFFF		// bad because hi byte is set
		#define kInvalidAssociate	-1
		
		typedef struct
		{
			Color32		theColor;
			SInt32		associatedNumber;
		} HashEntry;
		
		
		HashEntry				mHashArray[ kHashArrayLimit ];
		HashEntry				mRecent1, mRecent2;
		SInt32					mUniquePixels;
		Boolean					mBWCompleted;
	
		inline 		SInt32		GetHashStartingPoint( Color32 );
		inline 		Boolean		GetIndex( Color32, SInt32 *outIndex );
		
		inline 		SInt32		IsRecentOne( Color32 );
		inline 		void		AddToRecentOne( Color32, SInt32 inAssociate );
					SInt32 		FindAssociatedValueIndex( SInt32 inAssoc );
};


#endif // _H_CColorHash
