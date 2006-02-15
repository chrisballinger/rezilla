// ===========================================================================
// CWindow_Cursor.h
//                       Created: 2004-12-11 18:56:26
//             Last modification: 2005-02-17 17:52:39
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004-2005
// All rights reserved.
// ===========================================================================

#ifndef _H_CWindow_Cursor
#define _H_CWindow_Cursor
#pragma once

#include "CIcon_EditorWindow.h"

class COffscreen;
class CDraggableTargetView;
class CRezMap;
class CRezObj;


class CWindow_Cursor : public CIcon_EditorWindow {
	public:
		enum { class_ID = FOUR_CHAR_CODE('CrsV') };

		static CWindow_Cursor*		OpenPaintWindow( CRezObj * inRezObj, ResIDT inPPobID );
		static CWindow_Cursor*		CreateFromStream( LStream *inStream );
		
									CWindow_Cursor( LStream * );
		virtual						~CWindow_Cursor();
		virtual void				FinishCreateSelf();
		
		virtual void				InitializeFromResource(CRezObj * inRezObj);		
		virtual void				SaveAsResource( CRezMap *inMap, ResIDT inResID );

	protected:
		CDraggableTargetView 		*mColorSample, 
									*mBWSample, 
									*mMaskSample;
		ResType						mResourceType;
		Point						mUndoHotSpot;
		
		void 						ParseBWCursor( CRezObj * inRezObj, COffscreen **outBW,
													COffscreen **outMask, Point *outHotSpot );

		void						ParseColorCursor( CRezObj * inRezObj, COffscreen **outColor,
												COffscreen **outBW, COffscreen **outMask,
												Point *outHotSpot);

		Handle						CreateBWCursor( COffscreen *inBW, COffscreen *inMask,
										Point inHotSpot );

		Handle 						CreateColorCursor( COffscreen *inColor, COffscreen *inBW, 
										COffscreen *inMask, Point inHotSpot );
										
		virtual void				SwapUndoState();
		virtual void				CopyToUndo();
};

#endif // _H_CWindow_Cursor
