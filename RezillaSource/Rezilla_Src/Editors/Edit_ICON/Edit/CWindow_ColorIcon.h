// ===========================================================================
// CWindow_ColorIcon.h
//                       Created: 2004-12-11 18:56:23
//             Last modification: 2005-02-17 11:19:34
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004-2005
// All rights reserved.
// ===========================================================================

#ifndef _H_CWindow_ColorIcon
#define _H_CWindow_ColorIcon
#pragma once

#include "CIcon_EditorWindow.h"

class COffscreen;
class CDraggableTargetView;
class CRezMap;
class CRezObj;

class CWindow_ColorIcon : public CIcon_EditorWindow {
	public:
		enum { class_ID = FOUR_CHAR_CODE('IcnV') };

		static CWindow_ColorIcon *	OpenPaintWindow(CRezObj * inRezObj, ResIDT inPPobID );
		static CWindow_ColorIcon *	CreatePaintCIconStream( LStream *inStream );
		
									CWindow_ColorIcon( LStream * );
		virtual						~CWindow_ColorIcon();
		
		virtual void				FinishCreateSelf();
		
		virtual void				InitializeFromResource(CRezObj * inRezObj);
		virtual void				InitializeFromBuffers( 
											COffscreen *inColor, COffscreen *inBW, 
											COffscreen *inMask, Boolean bwIsEmpty );
		
		virtual void				SaveAsResource( CRezMap *inMap, ResIDT inResID );
		
		virtual void				ChangeImageSize( SInt32 inWidth, SInt32 inHeight, Boolean inStretch );
		
												
	protected:
		CDraggableTargetView *		mColorSample;
		CDraggableTargetView *		mBWSample;
		CDraggableTargetView *		mMaskSample;
		SDimension16				mInitialSampleWellSize;

		void						ParseColorIcon(CRezObj * inRezObj,
												   COffscreen **outColor, COffscreen **outBW, 
												   COffscreen **outMask, Boolean *outBWEmpty );
										
		Handle 						CreateColorIcon( COffscreen *inColor, COffscreen *inBW, 
										COffscreen *inMask );
										
		virtual void				ResizeSampleWell( SInt32 inIconWidth, SInt32 inIconHeight );
};

#endif // _H_CWindow_ColorIcon
