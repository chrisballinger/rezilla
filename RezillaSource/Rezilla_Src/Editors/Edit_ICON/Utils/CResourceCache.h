// ===========================================================================
// CResourceCache.h
//                       Created: 2004-12-11 18:56:46
//             Last modification: 2004-12-14 18:56:46
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// ===========================================================================

#ifndef _H_CResourceCache
#define _H_CResourceCache
#pragma once

#include "PP_Types.h"			// for ResIDT

class CResourceCache
{
	public:
								CResourceCache( SInt32 numElements, OSType inResType, SInt32 resFileID = -1 );
		virtual					~CResourceCache();
							
		virtual Handle			GetResource( ResIDT );
		virtual void			ReleaseResource( Handle& );
		
	protected:
		typedef struct
		{
			Handle				theResource;
			ResIDT				theResID;
		} CacheEntry;		
		
		OSType					mResType;
		SInt32					mResFileID;
		
		SInt32					mNumElements;
		CacheEntry				*mCacheArray;
				
		virtual	SInt32			FindElementByID( ResIDT );
		virtual	SInt32			FindElementByHandle( Handle );
		virtual	void			DisposeElement( SInt32 index );

		// Override these for different types of loads (CCursor, CIconHandle, etc)
		virtual	Handle			LoadRawResource( ResIDT );
		virtual	void			DisposeRawResource( Handle& );
};

#endif // _H_CResourceCache
