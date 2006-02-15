// ===========================================================================
// UPopupDrawing.h
//                       Created: 2004-12-11 18:57:39
//             Last modification: 2004-12-31 08:27:58
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// ===========================================================================

#ifndef _H_UPopupDrawing
#define _H_UPopupDrawing
#pragma once


class UPopupDrawing {
public:
		static void		DrawPopupArrow( const Rect &inBounds, 
									   Boolean inHilited, 
									   Boolean inEnabled );
		
		static void		CalculateSwatchArea( const Rect &inBounds, 
											Rect *outSwatchR );
				
protected:
		static void		DoDrawArrow( const Rect &inBounds, 
									SInt16 inDepth, 
									Boolean inHilited, 
									Boolean inEnabled );

		static void		GetArrowColor( SInt16 inDepth, 
									  Boolean inHilited, 
									  Boolean inEnabled,
									  RGBColor *outColor );

};

#endif // _H_UPopupDrawing
