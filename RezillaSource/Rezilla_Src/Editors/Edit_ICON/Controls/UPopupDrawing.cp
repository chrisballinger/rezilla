// ===========================================================================
// UPopupDrawing.cp
//                       Created: 2004-12-11 18:53:10
//             Last modification: 2004-12-14 14:59:40
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

const SInt16 gsPopup_ArrowHeight	= 	3;	// 4 Actual height of the arrow
const SInt16 gsPopup_ArrowWidth		= 	5;	// 7 Actual width of the arrow at widest


// ---------------------------------------------------------------------------
// 	DrawPopup
// ---------------------------------------------------------------------------

void
UPopupDrawing::DrawPopup( const Rect &inBounds, Boolean inHilited, Boolean inEnabled )
{
	SInt16				theDepth;
	StDeviceLoop		theLoop( inBounds );
	
	// Don't draw on the swatch area because it flickers
	Rect				swatchR;
	CalculateSwatchArea( inBounds, &swatchR );
	StClipRgnState		savedClip( swatchR );
	
	
	StColorPenState		savedPenState;	
	savedPenState.Normalize();

	while( theLoop.NextDepth( theDepth ) )
	{
		if ( theDepth < 4 )
		{
			if ( inHilited )
				DrawPopupHilitedBW( inBounds );
			else if ( inEnabled )
				DrawPopupNormalBW( inBounds );
			else
				DrawPopupDimmedBW( inBounds );
		}
		else
		{
			if ( inHilited )
				DrawPopupHilitedColor( inBounds );
			else if ( inEnabled )
				DrawPopupNormalColor( inBounds );
			else
				DrawPopupDimmedColor( inBounds );
		}
	}
}


// ---------------------------------------------------------------------------
// 	DrawPopupNormalBW
// ---------------------------------------------------------------------------

void
UPopupDrawing::DrawPopupNormalBW( const Rect &inBounds )
{
	Rect	localFrame = inBounds;
	
	// Needed to unhilite us (when we switch from hilited -> not)
	::EraseRect( &localFrame );
	
	// Draw the frame...
	RGBColor 	colorArray[4];
	colorArray[0] = UGAColorRamp::GetBlackColor();
	colorArray[1] = UGAColorRamp::GetBlackColor();
	colorArray[2] = UGAColorRamp::GetBlackColor();
	colorArray[3] = UGAColorRamp::GetBlackColor();
	UGraphicUtils::AngledCornerFrame( localFrame, colorArray, 2 );

	// ...and the arrow
	DrawPopupArrow( inBounds, 1, false, true );
}


// ---------------------------------------------------------------------------
// 	DrawPopupNormalColor
// ---------------------------------------------------------------------------

void
UPopupDrawing::DrawPopupNormalColor( const Rect &inBounds )
{
	// Get the frame for the control
	Rect	localFrame = inBounds;

	// Draw the frame for the control outside of everything else
	// the frame is draw in the foregorund color
	UGraphicUtils::NoCornerPixelFrame( localFrame );

	// First make sure the face of the control is drawn
	::InsetRect( &localFrame, 1, 1 );
	::RGBForeColor( &UGAColorRamp::GetColor(2) );
	::PaintRect( &localFrame );
	
	// Start by rendering the bevelled edges of the sides facing the light
	// source
	RGBColor colorArray[3];
	colorArray[0] = UGAColorRamp::GetColor(2);
	colorArray[1] = Color_White;
	UGraphicUtils::BevelledEdge( localFrame, rectEdges_TopLeft, colorArray, 2 );
	
	// Render the shadow bevels
	colorArray[0] = UGAColorRamp::GetColor(8);
	colorArray[1] = UGAColorRamp::GetColor(6);
	UGraphicUtils::BevelledEdge( localFrame, rectEdges_BottomRight, colorArray, 2 );
	
	// Take care of the corner details 
	// TOP LEFT
	colorArray[0] = Color_White;
	colorArray[1] = Color_White;
	UGraphicUtils::PaintCornerPixels( localFrame, rectCorners_TopLeft, colorArray, 2 );
	
	// TOP RIGHT
	colorArray[0] = UGAColorRamp::GetColor(2);
	colorArray[1] = UGAColorRamp::GetColor(2);
	UGraphicUtils::PaintCornerPixels( localFrame, rectCorners_TopRight, colorArray, 2 );
	
	// BOTTOM RIGHT
	colorArray[0] = Color_Black;
	colorArray[1] = UGAColorRamp::GetColor(8);
	colorArray[2] = UGAColorRamp::GetColor(6);
	UGraphicUtils::PaintCornerPixels( localFrame, rectCorners_BottomRight, colorArray, 3 );
	
	// BOTTOM LEFT
	colorArray[0] = UGAColorRamp::GetColor(2);
	colorArray[1] = UGAColorRamp::GetColor(2);
	UGraphicUtils::PaintCornerPixels( localFrame, rectCorners_BottomLeft, colorArray, 2 );

	//	Draw the frame around the color swatch
	Rect		swatchR;
	CalculateSwatchArea( inBounds, &swatchR );
	::InsetRect( &swatchR, -1, -1 );
	
	// Dark Shadow top and left
	::RGBForeColor( &UGAColorRamp::GetColor(8) );
	::MoveTo( swatchR.left, swatchR.bottom - 2 );
	::LineTo( swatchR.left, swatchR.top );
	::LineTo( swatchR.right - 2, swatchR.top );
	
	// Light shadow bottom and Right
	::RGBForeColor( &UGAColorRamp::GetWhiteColor() );
	::MoveTo( swatchR.left + 1, swatchR.bottom - 1 );
	::LineTo( swatchR.right - 1, swatchR.bottom - 1 );
	::LineTo( swatchR.right - 1, swatchR.top + 1 );

		// finally, draw the arrow
	DrawPopupArrow( inBounds, 8, false, true );
}


// ---------------------------------------------------------------------------
// 	DrawPopupHilitedBW
// ---------------------------------------------------------------------------

void
UPopupDrawing::DrawPopupHilitedBW( const Rect &inBounds )
{
	Rect		localFrame = inBounds;
	
	::InsetRect( &localFrame, 1, 1 );
	::InvertRect( &localFrame );

	DrawPopupArrow( inBounds, 1, true, true );
}


// ---------------------------------------------------------------------------
// 	DrawPopupHilitedColor
// ---------------------------------------------------------------------------

void
UPopupDrawing::DrawPopupHilitedColor( const Rect &inBounds )
{
	Rect localFrame = inBounds;
	
	// Draw the frame for the control outside of everything else
	// the frame is draw in the foregorund color
	UGraphicUtils::NoCornerPixelFrame( localFrame );

	// Paint the face of the button first
	::InsetRect( &localFrame, 1, 1 );
	::RGBForeColor( &UGAColorRamp::GetColor(5) );
	::PaintRect( &localFrame );
	
	// Start by rendering the bevelled edges of the sides facing the light
	// source
	RGBColor colorArray[2];
	colorArray[0] = UGAColorRamp::GetColor(9);
	colorArray[1] = UGAColorRamp::GetColor(7);
	UGraphicUtils::BevelledEdge( localFrame, rectEdges_TopLeft, colorArray, 2 );
	
	// Render the shadow bevels
	colorArray[0] = UGAColorRamp::GetColor(1);
	colorArray[1] = UGAColorRamp::GetColor(3);
	UGraphicUtils::BevelledEdge( localFrame, rectEdges_BottomRight, colorArray, 2 );
	
	// Take care of the corener details 
	// TOP LEFT
	::InsetRect( &localFrame, 1, 1 );
	colorArray[0] = UGAColorRamp::GetColor(9);
	colorArray[1] = UGAColorRamp::GetColor(7);
	UGraphicUtils::PaintCornerPixels( localFrame, rectCorners_TopLeft, colorArray, 2 );
	::InsetRect( &localFrame, -1, -1 );
	
	// TOP RIGHT
	colorArray[0] = UGAColorRamp::GetColor(5);
	colorArray[1] = UGAColorRamp::GetColor(5);
	UGraphicUtils::PaintCornerPixels( localFrame, rectCorners_TopRight, colorArray, 2 );
	
	// BOTTOM RIGHT
	::InsetRect( &localFrame, 1, 1 );
	colorArray[0] = UGAColorRamp::GetColor(1);
	colorArray[1] = UGAColorRamp::GetColor(3);
	UGraphicUtils::PaintCornerPixels( localFrame, rectCorners_BottomRight, colorArray, 2 );
	::InsetRect( &localFrame, -1, -1 );
	
	// BOTTOM LEFT
	colorArray[0] = UGAColorRamp::GetColor(5);
	colorArray[1] = UGAColorRamp::GetColor(5);
	UGraphicUtils::PaintCornerPixels( localFrame, rectCorners_BottomLeft, colorArray, 2 );

	//	Draw the frame around the color swatch
	Rect		swatchR;
	CalculateSwatchArea( inBounds, &swatchR );
	::InsetRect( &swatchR, -1, -1 );
	
	// Dark Shadow top and left
	::RGBForeColor( &UGAColorRamp::GetColor(9) );
	::MoveTo( swatchR.left, swatchR.bottom - 2 );
	::LineTo( swatchR.left, swatchR.top );
	::LineTo( swatchR.right - 2, swatchR.top );
	
	// Light shadow bottom and Right
	::RGBForeColor( &UGAColorRamp::GetColor(3) );
	::MoveTo( swatchR.left + 1, swatchR.bottom - 1 );
	::LineTo( swatchR.right - 1, swatchR.bottom - 1 );
	::LineTo( swatchR.right - 1, swatchR.top + 1 );
	
	// Finally, the popup arrow
	DrawPopupArrow( inBounds, 8, true, true );
}


// ---------------------------------------------------------------------------
// 	DrawPopupDimmedBW
// ---------------------------------------------------------------------------

void
UPopupDrawing::DrawPopupDimmedBW( const Rect &inBounds )
{
	// Get the frame for the control
	Rect	localFrame = inBounds;
	
	// Before we draw anything we need to erase the control in case we
	// we had previously been hilited
	::RGBBackColor( &Color_White );
	::EraseRect( &localFrame );
		
	// Draw the frame for the control outside of everything else
	// the frame is draw in the foreground color
	Pattern aPat;
	::PenPat( UQDGlobals::GetGrayPat(&aPat) );
	UGraphicUtils::NoCornerPixelFrame( localFrame );

	// and the arrow
	DrawPopupArrow( inBounds, 1, false, false );
}


// ---------------------------------------------------------------------------
// 	DrawPopupDimmedColor
// ---------------------------------------------------------------------------

void
UPopupDrawing::DrawPopupDimmedColor( const Rect &inBounds )
{
	// Get the frame for the control
	Rect	localFrame = inBounds;

	// Draw the frame for the control outside of everything else
	// the frame is draw in the foregorund color
	::RGBForeColor( &UGAColorRamp::GetColor(5) );
	UGraphicUtils::NoCornerPixelFrame( localFrame );

	// First make sure the face of thecontrol is drawn
	::InsetRect( &localFrame, 1, 1 );
	::RGBForeColor( &UGAColorRamp::GetColor(1) );
	::PaintRect( &localFrame );
	
	// Start by rendering the bevelled edges of the sides facing the light
	// source
	RGBColor colorArray[2];
	colorArray[0] = Color_White;
	UGraphicUtils::BevelledEdge( localFrame, rectEdges_TopLeft, colorArray, 1 );
	
	// Render the shadow bevels
	colorArray[0] = UGAColorRamp::GetColor(3);
	UGraphicUtils::BevelledEdge( localFrame, rectEdges_BottomRight, colorArray, 1 );
	
	// Take care of the corner details 
	// TOP LEFT
	colorArray[0] = Color_White;
	UGraphicUtils::PaintCornerPixels( localFrame, rectCorners_TopLeft, colorArray, 1 );
	
	// TOP RIGHT
	colorArray[0] = UGAColorRamp::GetColor(1);
	UGraphicUtils::PaintCornerPixels( localFrame, rectCorners_TopRight, colorArray, 1 );
	
	// BOTTOM RIGHT
	colorArray[0] = UGAColorRamp::GetColor(5);
	colorArray[1] = UGAColorRamp::GetColor(3);
	UGraphicUtils::PaintCornerPixels( localFrame, rectCorners_BottomRight, colorArray, 2 );
	
	// BOTTOM LEFT
	colorArray[0] = UGAColorRamp::GetColor(1);
	UGraphicUtils::PaintCornerPixels( localFrame, rectCorners_BottomLeft, colorArray, 1 );

	//	Draw the frame around the color swatch
	Rect		swatchR;
	CalculateSwatchArea( inBounds, &swatchR );
	::InsetRect( &swatchR, -1, -1 );
	
	// Dark Shadow top and left
	::RGBForeColor( &UGAColorRamp::GetColor(3) );
	::MoveTo( swatchR.left, swatchR.bottom - 2 );
	::LineTo( swatchR.left, swatchR.top );
	::LineTo( swatchR.right - 2, swatchR.top );
	
	// Light shadow bottom and Right
	::RGBForeColor( &UGAColorRamp::GetWhiteColor() );
	::MoveTo( swatchR.left + 1, swatchR.bottom - 1 );
	::LineTo( swatchR.right - 1, swatchR.bottom - 1 );
	::LineTo( swatchR.right - 1, swatchR.top + 1 );
	
	// And the arrow
	DrawPopupArrow( inBounds, 8, false, false );
}



// ---------------------------------------------------------------------------
// 	DrawPopupArrow
// ---------------------------------------------------------------------------

void
UPopupDrawing::DrawPopupArrow( const Rect &inBounds, SInt16 inDepth, 
									Boolean inHilited, Boolean inEnabled )
{
	// Find the color to draw the arrow in
	RGBColor	theColor;
	GetArrowColor( inDepth, inHilited, inEnabled, &theColor );
	
	// Figure out where to draw the lines
	SInt16		height = inBounds.bottom - inBounds.top;	
	SInt16		startV = inBounds.top + ((height - gsPopup_ArrowHeight) / 2) + 2; // 1
	SInt16		leftEdge = inBounds.right - gsPopup_ArrowWidth - 6;
	SInt16		rightEdge = leftEdge + gsPopup_ArrowWidth - 1;
	
	// Draw the arrow
	::RGBForeColor( &theColor );
	for ( SInt16 count = 0; count < gsPopup_ArrowHeight; count++ )
	{
		::MoveTo( leftEdge + count, startV + count );
		::LineTo( rightEdge - count, startV + count );
	}
}


// ---------------------------------------------------------------------------
// 	GetArrowColor
// ---------------------------------------------------------------------------

void
UPopupDrawing::GetArrowColor( SInt16 inDepth, 
									Boolean inHilited, Boolean inEnabled,
									RGBColor *outColor )
{
	if ( inDepth < 4 )							// bw
	{
		*outColor = inHilited ? Color_White : Color_Black;
	}
	else										// color
	{
		if ( inHilited )
			*outColor = Color_White;
		else
			*outColor = inEnabled ? Color_Black : UGAColorRamp::GetColor( 7 );
	}
}


// ---------------------------------------------------------------------------
// 	CalculateSwatchArea
// ---------------------------------------------------------------------------

void
UPopupDrawing::CalculateSwatchArea( const Rect &inBounds, Rect *outBounds )
{
	*outBounds = inBounds;
	outBounds->right -= (gsPopup_ArrowWidth + 6 + 4); // was + 3
	outBounds->left += 5;
	outBounds->top += 5;
	outBounds->bottom -= 5;
}

