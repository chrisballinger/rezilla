// ===========================================================================
// UPopupDrawing.h
//                       Created: 2004-12-11 18:57:39
//             Last modification: 2004-12-14 14:59:55
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
#pragma once

class UPopupDrawing {
	public:
		// These are the only calls you'll usually need to make
		static void			DrawPopup( const Rect &inBounds, Boolean inHilited, Boolean inEnabled );
		static void			CalculateSwatchArea( const Rect &inBounds, Rect *outSwatchR );
		
		// These are the specific drawing routines
		static void			DrawPopupNormalBW( const Rect &inBounds );
		static void			DrawPopupNormalColor( const Rect &inBounds );
	
		static void			DrawPopupHilitedBW( const Rect &inBounds );
		static void			DrawPopupHilitedColor( const Rect &inBounds );
		
		static void			DrawPopupDimmedBW( const Rect &inBounds );
		static void			DrawPopupDimmedColor( const Rect &inBounds );
		
	protected:
		static void			DrawPopupArrow( const Rect &inBounds, SInt16 inDepth, 
											Boolean inHilited, Boolean inEnabled );

		static void			GetArrowColor( SInt16 inDepth, 
											Boolean inHilited, Boolean inEnabled,
											RGBColor *outColor );

};

