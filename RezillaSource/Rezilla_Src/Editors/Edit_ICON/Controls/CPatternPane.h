// ===========================================================================
// CPatternPane.h
//                       Created: 2004-12-11 18:57:36
//             Last modification: 2004-12-28 18:28:29
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CPatternPane
#define _H_CPatternPane
#pragma once

#include "RezillaConstants.h"		// just for RedrawOptions
#include "CPatternPopup.h"			// for SPatternListH

/* public LPane, public LBroadcaster */
#include <LBevelButton.h>

class CPatternPane : public LBevelButton
{
	public:
		enum { class_ID = FOUR_CHAR_CODE('PatP') };

								CPatternPane( LStream * );
		virtual					~CPatternPane();
		static	CPatternPane *	CreateFromStream( LStream * );
		
		virtual SInt32			GetPatternIndex();
		virtual void			SetPatternIndex( SInt32 inIndex, RedrawOptions = redraw_Later );
		virtual void			GetCurrentPattern( Pattern * );
		
		virtual void			SetPatternList( SPatternListH inHandle, RedrawOptions = redraw_Later );
		virtual void 			SetPatternList( SInt16 inFileID, ResIDT inResID, RedrawOptions = redraw_Later );
		virtual void 			SetColors( Color32, Color32, RedrawOptions = redraw_Later );

		virtual void			DrawSelf();
		virtual void 			ClickSelf( const SMouseDownEvent & );
	
	protected:
		RGBColor				mForeColor, mBackColor;
		SInt32					mCurrentIndex;
		SPatternListH			mPatternListH;

		virtual void			DrawPopup( Boolean inHilited, Boolean inEnabled );
		virtual void			DrawSwatchSelf( const Rect &swatchR );
		virtual void			DrawSwatch();

};

#endif // _H_CPatternPane
