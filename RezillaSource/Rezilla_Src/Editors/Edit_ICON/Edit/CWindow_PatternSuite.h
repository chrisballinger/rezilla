// ===========================================================================
// CWindow_PatternSuite.h
//                       Created: 2005-01-09 10:38:27
//             Last modification: 2005-02-17 17:47:24
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
class CPatternTargetView;
class CRezObj;


class CWindow_PatternSuite : public CSuite_Window {
	public:
		enum { class_ID = FOUR_CHAR_CODE('PaSV') };

								CWindow_PatternSuite( LStream * );
		virtual					~CWindow_PatternSuite();
		
		static CWindow_PatternSuite *	OpenPaintWindow( CRezObj * inRezObj, ResIDT inPPobID );
		static CWindow_PatternSuite *	CreateFromStream( LStream *inStream );
		
		virtual void		SaveAsResource( CRezMap *inMap, ResIDT inID);
	
		SInt32				GetZoomFactor( SInt32, SInt32, Boolean *outShowGrid );
			
		void				SwitchToNthBitmap( SInt32 inBitmapIndex );
		
	protected:
		TArray<Pattern>			mPatternsArray;
		CPatternTargetView *	mSample;

		virtual void		FinishCreateSelf();
				
		virtual void		ParseBitmapSuite( Handle inHandle, COffscreen **outBW  );

		virtual ArrayIndexT	AddNewBitmap();
		virtual ArrayIndexT	AddNewBitmap( SInt32 inAfterIndex );
		virtual void		RemoveBitmap( SInt32 inBitmapIndex );
		virtual void		SetNthBitmap( SInt32 inBitmapIndex );
		virtual void		ImageToNthBitmap( SInt32 inBitmapIndex );

};

#endif // _H_CWindow_PatternSuite
