// ===========================================================================
// CWindow_PatternSuite.h
//                       Created: 2005-01-09 10:38:27
//             Last modification: 2005-01-09 14:09:02
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

#include "CIcon_EditorWindow.h"

class CRezMap;
class LSlider;
class LStaticText;
class LPushButton;
class CPatternTargetView;

// 		struct Pattern {
// 		  UInt8               pat[8];
// 		};
// 		typedef struct Pattern     Pattern;
// 		typedef Pattern *          PatPtr;
// 		typedef PatPtr *           PatHandle;

// ----------------------------------------------------------------------------


class CWindow_PatternSuite : public CIcon_EditorWindow {
	public:
		enum { class_ID = FOUR_CHAR_CODE('PaSV') };

								CWindow_PatternSuite( LStream * );
		virtual					~CWindow_PatternSuite();
		
		static CWindow_PatternSuite *	OpenPaintWindow( ResIDT inPPobID, CRezMap *inMap, ResIDT inID);
		static CWindow_PatternSuite *	CreateFromStream( LStream *inStream );
		
		virtual void		ListenToMessage(MessageT inMessage, void *ioParam);

		virtual void		InitializeFromResource( CRezMap *inMap, ResIDT inID);
		virtual void		SaveAsResource( CRezMap *inMap, ResIDT inID);
	
		SInt32				GetZoomFactor( SInt32, SInt32, Boolean *outShowGrid );
			
	protected:
		SInt32					mCurrentIndex;
		SInt32					mTotalCount;
		TArray<Pattern>			mPatternsArray;
		CPatternTargetView *	mBWSample;
		LSlider *				mSlider;
		LStaticText *			mCountField;
		LPushButton *			mPlusButton;
		LPushButton *			mMinusButton;
		
		virtual void		FinishCreateSelf();
				
		void				ParseBWPatternSuite( Handle inHandle, COffscreen **outBW  );

		void				SetCountField( SInt32 inCurrIndex, SInt32 inTotalCount );
		void				AdjustSlider();
		
		void				SetNthPattern( SInt32 inPatternIndex );
		void				AddNewPattern();
		void				AddNewPattern( SInt32 inAfterIndex );
		void				RemovePattern( SInt32 inPatternIndex );
		void				BitmapToNthPattern( SInt32 inPatternIndex );

};

#endif // _H_CWindow_PatternSuite
