// ===========================================================================
// UPopupDrawing.cp
//                       Created: 2004-12-11 18:53:10
//             Last modification: 2004-12-31 08:27:41
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "UPopupDrawing.h"
#include "RezillaConstants.h"
#include "UGAColorRamp.h"

#include <UGraphicUtils.h>
#include <UDrawingState.h>

const SInt16 kPopupArrowHeight = 3;
const SInt16 kPopupArrowWidth = 5;


// ---------------------------------------------------------------------------
// 	DrawPopup
// ---------------------------------------------------------------------------

void
UPopupDrawing::DrawPopupArrow( const Rect &inBounds, Boolean inHilited, Boolean inEnabled )
{
	SInt16				theDepth;
	StDeviceLoop		theLoop( inBounds );
	
// 	// Don't draw on the swatch area because it flickers
// 	Rect				swatchR;
// 	CalculateSwatchArea( inBounds, &swatchR );
// 	StClipRgnState		savedClip( swatchR );
	
	StColorPenState		savedPenState;	
	savedPenState.Normalize();

	while( theLoop.NextDepth( theDepth ) )
	{
		if ( theDepth < 4 )
		{
			if ( inHilited )
				DoDrawArrow( inBounds, 1, true, true );
			else if ( inEnabled )
				DoDrawArrow( inBounds, 1, false, true );
			else
				DoDrawArrow( inBounds, 1, false, false );
		}
		else
		{
			if ( inHilited )
				DoDrawArrow( inBounds, 8, true, true );
			else if ( inEnabled )
				DoDrawArrow( inBounds, 8, false, true );
			else
				DoDrawArrow( inBounds, 8, false, false );
		}
	}
}


// ---------------------------------------------------------------------------
// 	DoDrawArrow
// ---------------------------------------------------------------------------

void
UPopupDrawing::DoDrawArrow( const Rect &inBounds, SInt16 inDepth, 
									Boolean inHilited, Boolean inEnabled )
{
	// Find the color to draw the arrow in
	RGBColor	theColor;
	GetArrowColor( inDepth, inHilited, inEnabled, &theColor );
	
	// Figure out where to draw the lines
	SInt16	height = inBounds.bottom - inBounds.top;	
	SInt16	startV = inBounds.top + ((height - kPopupArrowHeight) / 2) + 2;
	SInt16	leftEdge = inBounds.right - kPopupArrowWidth - 6;
	SInt16	rightEdge = leftEdge + kPopupArrowWidth - 1;
	
	// Draw the arrow
	::RGBForeColor( &theColor );
	for ( SInt16 count = 0; count < kPopupArrowHeight; count++ )
	{
		::MoveTo( leftEdge + count, startV + count );
		::LineTo( rightEdge - count, startV + count );
	}
}


// ---------------------------------------------------------------------------
// 	GetArrowColor
// ---------------------------------------------------------------------------

void
UPopupDrawing::GetArrowColor(SInt16 inDepth,
						   Boolean inHilited, 
						   Boolean inEnabled,
						   RGBColor *outColor )
{
	if ( inDepth < 4 ) {
		// Black & white
		*outColor = inHilited ? Color_White : Color_Black;
	}
	else {
		// Color
		if ( inHilited ) {
			*outColor = Color_White;
		} else {
			*outColor = inEnabled ? Color_Black : UGAColorRamp::GetColor( 7 );
		}
	}
}


// ---------------------------------------------------------------------------
// 	CalculateSwatchArea
// ---------------------------------------------------------------------------

void
UPopupDrawing::CalculateSwatchArea( const Rect &inBounds, Rect *outBounds )
{
	*outBounds = inBounds;
	outBounds->right -= (kPopupArrowWidth + 6 + 4);
	outBounds->left += 5;
	outBounds->top += 5;
	outBounds->bottom -= 5;
}

