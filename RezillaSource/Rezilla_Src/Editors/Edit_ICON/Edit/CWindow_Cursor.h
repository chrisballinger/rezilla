// ===========================================================================
// CWindow_Cursor.h
//                       Created: 2004-12-11 18:56:26
//             Last modification: 2004-12-18 00:03:48
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CWindow_Cursor
#define _H_CWindow_Cursor
#pragma once

#include "CIcon_EditorWindow.h"

class COffscreen;
class CDraggableTargetView;
class CRezMap;


class CWindow_Cursor : public CIcon_EditorWindow {
	public:
		enum { class_ID = FOUR_CHAR_CODE('CrsV') };

		static CWindow_Cursor*		OpenPaintWindow( ResIDT inPPobID, CRezMap *, ResType, ResIDT );
		static CWindow_Cursor*		CreateFromStream( LStream *inStream );
		
									CWindow_Cursor( LStream * );
		virtual						~CWindow_Cursor();
		virtual void				FinishCreateSelf();
		
		virtual void				InitializeFromResource( CRezMap *, ResType, ResIDT );		
		virtual void				SaveAsResource( CRezMap *, ResIDT );

	protected:
		CDraggableTargetView 		*mColorSample, 
									*mBWSample, 
									*mMaskSample;
		ResType						mResourceType;
		Point						mUndoHotSpot;
		
		void 						ParseBWCursor( CRezMap *, ResIDT, COffscreen **outBW,
													COffscreen **outMask, Point *outHotSpot );

		void						ParseColorCursor( CRezMap *, ResIDT, COffscreen **outColor,
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
