// ===========================================================================
// CWindow_PatternSuite.h
//                       Created: 2005-01-09 10:38:27
//             Last modification: 2005-01-11 08:03:28
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CWindow_PatternSuite
#define _H_CWindow_PatternSuite
#pragma once

#include "CSuite_Window.h"

class CRezMap;


class CWindow_PatternSuite : public CSuite_Window {
	public:
		enum { class_ID = FOUR_CHAR_CODE('PaSV') };

								CWindow_PatternSuite( LStream * );
		virtual					~CWindow_PatternSuite();
		
		static CWindow_PatternSuite *	OpenPaintWindow( ResIDT inPPobID, CRezMap *inMap, ResType inResType, ResIDT inResID );
		static CWindow_PatternSuite *	CreateFromStream( LStream *inStream );
		
		virtual void		SaveAsResource( CRezMap *inMap, ResIDT inID);
	
		SInt32				GetZoomFactor( SInt32, SInt32, Boolean *outShowGrid );
			
		void				SwitchToNthBitmap( SInt32 inPatternIndex );
		
	protected:
		TArray<Pattern>			mPatternsArray;
		
		void				ParseBitmapSuite( Handle inHandle, COffscreen **outBW  );

		ArrayIndexT			AddNewBitmap();
		ArrayIndexT			AddNewBitmap( SInt32 inAfterIndex );
		void				RemoveBitmap( SInt32 inPatternIndex );
		void				SetNthBitmap( SInt32 inPatternIndex );
		void				BitmapToNthPattern( SInt32 inPatternIndex );

};

#endif // _H_CWindow_PatternSuite
