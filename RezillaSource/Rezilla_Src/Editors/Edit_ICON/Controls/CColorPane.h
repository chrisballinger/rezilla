// ===========================================================================
// CColorPane.h
//                       Created: 2004-12-11 18:57:33
//             Last modification: 2004-12-14 18:57:33
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#pragma once

#include "RezillaConstants.h"		// just for ERedrawOptions

class CColorPane : public LPane, public LBroadcaster
{
	public:
		enum { class_ID = 'PTCL' };
		
								CColorPane( LStream * );
		virtual					~CColorPane();
		virtual void			FinishCreateSelf();
		static	CColorPane *	CreateFromStream( LStream * );
		
			// get/set color
		virtual Color32			GetColor();
		virtual void			SetColor( Color32, ERedrawOptions = redraw_Later );

			// get/set color table
		virtual CTabHandle		GetColorTable();
		virtual void			SetColorTable( CTabHandle, Boolean inChangeColorToo = true, ERedrawOptions = redraw_Later );
		virtual void			AllowPickerOption( Boolean inOption );
		
		virtual void			DrawSelf();
		virtual void			ClickSelf( const SMouseDownEvent & );
		virtual Boolean 		PointIsInFrame( SInt32 inHoriz, SInt32 inVert ) const;
		
		virtual void			DrawSwatch();
		
	protected:
		Color32					mCurrentColor;
		CTabHandle				mColorTable;
		RgnHandle				mClippedRgn;
		Boolean					mClipsToSibblings;
		Boolean					mUsePickerOption;
		
		virtual void			CalcClipRegionForOverlap();
		virtual void			DrawPopup( Boolean inHilited, Boolean inEnabled );
		virtual void			DrawSwatchSelf( const Rect &swatchR );
		
		virtual SInt32			GetColorIndex( Color32 );
		virtual Boolean			DoAppleColorPicker( Color32 *outColor );
		virtual void			DisposeCurrentTable();
};

