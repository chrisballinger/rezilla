// ===========================================================================
// CWindow_IconSuite.h
//                       Created: 2005-01-10 21:23:57
//             Last modification: 2005-02-17 17:50:58
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004-2005
// All rights reserved.
// ===========================================================================

#ifndef _H_CWindow_IconSuite
#define _H_CWindow_IconSuite
#pragma once

#include "CSuite_Window.h"

class CRezMap;
class CDraggableTargetView;
class CRezObj;

typedef short		SICN[16];
typedef SICN *		SICN_Ptr;
typedef SICN_Ptr *	SICN_Hand;


class CWindow_IconSuite : public CSuite_Window {
	public:
		enum { class_ID = FOUR_CHAR_CODE('SICW') };

								CWindow_IconSuite( LStream * );
		virtual					~CWindow_IconSuite();
		
		static CWindow_IconSuite *	OpenPaintWindow( CRezObj * inRezObj, ResIDT inPPobID );
		static CWindow_IconSuite *	CreateFromStream( LStream *inStream );
		
		virtual void		SaveAsResource( CRezMap *inMap, ResIDT inID);
	
		SInt32				GetZoomFactor( SInt32 inImageWidth, SInt32 inImageHeight, Boolean *outShowGrid );
			
	protected:
		TArray<SICN>			mBitmapsArray;
		CDraggableTargetView *	mSample;
					
		virtual void		FinishCreateSelf();
				
		virtual void		ParseBitmapSuite( Handle inHandle );

		virtual ArrayIndexT	AddNewBitmap();
		virtual ArrayIndexT	AddNewBitmap( SInt32 inAfterIndex );
		virtual void		RemoveBitmap( SInt32 inBitmapIndex );
		virtual void		SetNthBitmap( SInt32 inBitmapIndex );
		virtual void		ImageToNthBitmap( SInt32 inBitmapIndex );
		
		COffscreen *		IconToOffscreen( const SICN * inIcon );
		
};

#endif // _H_CWindow_IconSuite
