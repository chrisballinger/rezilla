// ===========================================================================
// CWindow_Pattern.h
//                       Created: 2004-12-11 18:56:30
//             Last modification: 2005-01-09 08:17:08
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CWindow_Pattern
#define _H_CWindow_Pattern
#pragma once

#include "CIcon_EditorWindow.h"

class COffscreen;
class CPatternTargetView;
class CRezMap;


class CWindow_Pattern : public CIcon_EditorWindow {
	public:
		enum { class_ID = FOUR_CHAR_CODE('PatV') };

									CWindow_Pattern( LStream * );
		virtual						~CWindow_Pattern();

		static CWindow_Pattern *	OpenPaintWindow( ResIDT inPPobID, CRezMap *, ResType, ResIDT );
		static CWindow_Pattern *	CreateFromStream( LStream *inStream );
		
		virtual void				FinishCreateSelf();
		
		virtual void				InitializeFromResource( CRezMap *, ResType, ResIDT );
		virtual void				SaveAsResource( CRezMap *, ResIDT );
		
		virtual SInt32				GetZoomFactor( SInt32, SInt32, Boolean *outShowGrid );

		virtual void				ChangeImageSize( SInt32 inWidth, SInt32 inHeight, Boolean inStretch );
		virtual void				ImageSizeChangeUndone( SInt32 inWidth, SInt32 inHeight );
		
		virtual void 				FindCommandStatus( CommandT inCommand, Boolean &outEnabled, 
									Boolean &outUsesMark, UInt16 &outMark, 
									Str255 outName );
		
		static COffscreen *			BWPatternToOffscreen( const Pattern & );

	protected:
		CPatternTargetView *		mColorSample;
		CPatternTargetView *		mBWSample;
		ResType						mResourceType;
		SInt32						mPixPatWidth, mPixPatHeight;
		
		SDimension16				mInitialSampleWellSize;
		
		void						ParseColorPattern( Handle inPattern, COffscreen **outColor,
												COffscreen **outBW );
		
		void						ParseBWPattern( Handle inPattern, COffscreen **outBW );
		
		Handle						CreateColorPattern( COffscreen *inColor, COffscreen *inBW );
		Handle						CreateBWPattern( COffscreen *inBW );
									
		virtual void				ResizeSampleWell( SInt32 newPatternWidth, SInt32 newPatternHeight );

};

#endif // _H_CWindow_Pattern
