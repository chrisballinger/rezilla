// ===========================================================================
// CWindow_IconSuite.h
//                       Created: 2005-01-10 21:23:57
//             Last modification: 2005-01-11 08:01:15
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CWindow_IconSuite
#define _H_CWindow_IconSuite
#pragma once

#include "CSuite_Window.h"

class CRezMap;
class CDraggableTargetView;

typedef short		SICN[16];
typedef SICN *		SICN_Ptr;
typedef SICN_Ptr *	SICN_Hand;


class CWindow_IconSuite : public CSuite_Window {
	public:
		enum { class_ID = FOUR_CHAR_CODE('IcSV') };

								CWindow_IconSuite( LStream * );
		virtual					~CWindow_IconSuite();
		
		static CWindow_IconSuite *	OpenPaintWindow( ResIDT inPPobID, CRezMap *inMap, ResType inResType, ResIDT inResID );
		static CWindow_IconSuite *	CreateFromStream( LStream *inStream );
		
		virtual void		SaveAsResource( CRezMap *inMap, ResIDT inID);
	
		SInt32				GetZoomFactor( SInt32, SInt32, Boolean *outShowGrid );
			
	protected:
		TArray<SICN>			mBitmapsArray;
		CDraggableTargetView *	mSample;
					
		virtual void		FinishCreateSelf();
				
		virtual void		ParseBitmapSuite( Handle inHandle, COffscreen **outBW  );

		virtual ArrayIndexT	AddNewBitmap();
		virtual ArrayIndexT	AddNewBitmap( SInt32 inAfterIndex );
		virtual void		RemoveBitmap( SInt32 inBitmapIndex );
		virtual void		SetNthBitmap( SInt32 inBitmapIndex );
		virtual void		ImageToNthBitmap( SInt32 inBitmapIndex );
		
		COffscreen *		IconToOffscreen( const SICN * inIcon );
		
};

#endif // _H_CWindow_IconSuite
