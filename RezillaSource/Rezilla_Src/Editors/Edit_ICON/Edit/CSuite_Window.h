// ===========================================================================
// CSuite_Window.h
//                       Created: 2005-01-10 21:23:57
//             Last modification: 2005-01-10 21:24:09
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CSuite_Window
#define _H_CSuite_Window
#pragma once

#include "CIcon_EditorWindow.h"

class LStaticText;
class LPushButton;
class CRezMap;
class CSuiteSlider;
class CPatternTargetView;


class CSuite_Window : public CIcon_EditorWindow {
	public:
		enum { class_ID = FOUR_CHAR_CODE('SuiV') };

								CSuite_Window( LStream * );
		virtual					~CSuite_Window();
		
		static CSuite_Window *	OpenPaintWindow( ResIDT inPPobID, CRezMap *inMap, ResType inResType, ResIDT inResID );
		static CSuite_Window *	CreateFromStream( LStream *inStream );
		
		virtual void		ListenToMessage(MessageT inMessage, void *ioParam);

		virtual Boolean		HandleKeyPress( const EventRecord&	inKeyEvent);

		virtual void		InitializeFromResource( CRezMap *inMap, ResType inResType, ResIDT inResID );
		virtual void		SaveAsResource( CRezMap *inMap, ResIDT inID);
				
		void				SwitchToNthBitmap( SInt32 inBitmapIndex );
		
	protected:
		UInt16					mCurrentIndex;
		UInt16					mTotalCount;
		CPatternTargetView *	mSample;
		CSuiteSlider *			mSlider;
		LStaticText *			mCountField;
		LPushButton *			mPlusButton;
		LPushButton *			mMinusButton;
		
		virtual void		FinishCreateSelf();
				
		void				ParseBitmapSuite( Handle inHandle, COffscreen **outBW  );

		void				SetCountField( SInt32 inCurrIndex, SInt32 inTotalCount );
		void				AdjustSlider();
		
		ArrayIndexT			AddNewBitmap();
		ArrayIndexT			AddNewBitmap( SInt32 inAfterIndex );
		void				RemoveBitmap( SInt32 inBitmapIndex );
		void				SetNthBitmap( SInt32 inBitmapIndex );
		void				ImageToNthBitmap( SInt32 inBitmapIndex );

};

#endif // _H_CSuite_Window
