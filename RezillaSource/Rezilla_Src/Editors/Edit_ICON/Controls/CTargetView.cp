// ===========================================================================
// CTargetView.cp
//                       Created: 2004-12-11 18:53:22
//             Last modification: 2004-12-16 22:23:22
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CTargetView.h"
#include "UGAColorRamp.h"
#include "UIconMisc.h"


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
CTargetView::SetTarget( Boolean inTarget, ERedrawOptions inRedraw )
{
	if ( mHasTarget == inTarget ) return;
	
	mHasTarget = inTarget;
	UIconMisc::RedrawPaneAsIndicated( this, inRedraw );
}


// ---------------------------------------------------------------------------
// 	GetBackgroundColor
// ---------------------------------------------------------------------------
// 	Returns the superview's background color.

void
CTargetView::GetBackgroundColor( RGBColor *outColor )
{
	StColorPenState		thePenState;		// save/restore pen state
	
	this->ApplyForeAndBackColors();
	::GetBackColor( outColor );
}


// ---------------------------------------------------------------------------
// 	DrawTargettedFrame
// ---------------------------------------------------------------------------

void
CTargetView::DrawTargettedFrame( const Rect &inBorderRect, Boolean inColor )
{
	StColorPenState		thePenState;
	thePenState.Normalize();

	if ( !mHasTarget )
	{
		RGBColor	backColor;
		if ( inColor )
			this->GetBackgroundColor( &backColor );
		else
			backColor = UGAColorRamp::GetWhiteColor();
		::RGBForeColor( &backColor );
	}
	
	::PenSize( 2, 2 );
	::FrameRect( &inBorderRect );
}

