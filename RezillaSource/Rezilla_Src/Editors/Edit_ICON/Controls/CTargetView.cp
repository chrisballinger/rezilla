// ===========================================================================
// CTargetView.cp
//                       Created: 2004-12-11 18:53:22
//             Last modification: 2005-01-08 07:10:13
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004, 2005
// All rights reserved.
// ===========================================================================

#include "CTargetView.h"
#include "RezillaConstants.h"
#include "UIconMisc.h"

#include <UGAColorRamp.h>


// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------

CTargetView::CTargetView( LStream *inStream ) 
		: LView( inStream )
{
	mHasTarget = false;
}


// ---------------------------------------------------------------------------
// 	Destructor
// ---------------------------------------------------------------------------

CTargetView::~CTargetView()
{
}


// ---------------------------------------------------------------------------
// 	CreateFromStream
// ---------------------------------------------------------------------------

CTargetView * 
CTargetView::CreateFromStream( LStream *inStream )
{
	return new CTargetView( inStream );
}


// ---------------------------------------------------------------------------
// 	SetTarget
// ---------------------------------------------------------------------------

void
CTargetView::SetTarget( Boolean inHasTarget, RedrawOptions inRedraw )
{
	if ( mHasTarget == inHasTarget ) return;
	
	mHasTarget = inHasTarget;
	UIconMisc::RedrawPaneAsIndicated( this, inRedraw );
}


// ---------------------------------------------------------------------------
//	¥ DrawBorder
// ---------------------------------------------------------------------------
//  Border around a Sample pane is outset from the interior by 1 pixel.

void
CTargetView::DrawBorder()
{
	StColorState	saveColors;			// Preserve color state
	StGrafPortSaver	savePort;
	Rect			frame;
	RGBColor		redColor = Color_Red;

	FocusDraw();
	
	CalcLocalFrameRect(frame);
	::MacInsetRect(&frame, 1, 1);
	::RGBForeColor(&redColor);
// // 	::DrawThemeFocusRegion(StRegion(frame), true);
	
	::PenNormal();
	::PenSize(1, 1);
	
	// Draw border around the view
	::RGBForeColor(&redColor);
	::FrameRect( &frame );
}


// ---------------------------------------------------------------------------
//	¥ EraseBorder
// ---------------------------------------------------------------------------

void
CTargetView::EraseBorder()
{
	StColorState	saveColors;			// Preserve color state
	StGrafPortSaver	savePort;
	Rect			frame;
	
	FocusDraw();
	
	CalcLocalFrameRect(frame);
// 	::MacInsetRect(&frame, 1, 1);
	::DrawThemeFocusRegion(StRegion(frame), false);
}




