// ===========================================================================
// CColorPane.h
//                       Created: 2004-12-11 18:57:33
//             Last modification: 2005-06-28 20:07:33
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004-2005
// All rights reserved.
// ===========================================================================

#ifndef _H_CColorPane
#define _H_CColorPane
#pragma once

#include "RezillaConstants.h"		// just for RedrawOptions
#include <LBevelButton.h>
/* public LPane, public LBroadcaster  */

class CColorPane : public LBevelButton {
	public:
		enum { class_ID = FOUR_CHAR_CODE('ColP') };
		
								CColorPane( LStream * );
		virtual					~CColorPane();
		virtual void			FinishCreateSelf();
		static	CColorPane *	CreateFromStream( LStream * );
		
			// get/set color
		virtual Color32			GetColor();
		virtual void			SetColor( Color32, RedrawOptions = redraw_Later );

			// get/set color table
		virtual CTabHandle		GetColorTable();
		virtual void			SetColorTable( CTabHandle, Boolean inChangeColorToo = true, RedrawOptions = redraw_Later );
		virtual void			AllowPickerOption( Boolean inOption );
		virtual void			UnsetColorTable() { mColorTable = nil; }
		
		virtual void			DrawSelf();
		virtual void			ClickSelf( const SMouseDownEvent & );
		virtual Boolean 		PointIsInFrame( SInt32 inHoriz, SInt32 inVert ) const;
		
		virtual void			DrawSwatch();
		
	protected:
		Color32					mCurrentColor;
		CTabHandle				mColorTable;
		RgnHandle				mClippedRgn;
		Boolean					mClipsToSiblings;
		Boolean					mUsePickerOption;
		
		virtual void			CalcClipRegionForOverlap();
		virtual void			DrawPopup( Boolean inHilited, Boolean inEnabled );
		virtual void			DrawSwatchSelf( const Rect &swatchR );
		
		virtual SInt32			GetColorIndex( Color32 );
		virtual Boolean			DoAppleColorPicker( Color32 *outColor );
		virtual void			DisposeCurrentTable();
};

#endif // _H_CColorPane
