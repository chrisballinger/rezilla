// ===========================================================================
// CColorCursorCache.h
//                       Created: 2004-12-11 18:56:39
//             Last modification: 2004-12-14 18:56:39
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// ===========================================================================

#ifndef _H_CColorCursorCache
#define _H_CColorCursorCache
#pragma once

#include "CResourceCache.h"


class CColorCursorCache : public CResourceCache {
	public:
									CColorCursorCache( SInt32 numElements, SInt32 resFileID = -1 );
		virtual 					~CColorCursorCache();
	
		static CColorCursorCache *	GetCurrentCache();
		
		virtual CCrsrHandle			GetColorCursor( ResIDT );
		virtual void				DisposeColorCursor( CCrsrHandle& );
		virtual Boolean				SetColorCursor( ResIDT );
		
	protected:
		virtual Handle				LoadRawResource( ResIDT );
		virtual void				DisposeRawResource( Handle& );
		
		static CColorCursorCache	*sCurrentCache;
};

#endif // _H_CColorCursorCache
