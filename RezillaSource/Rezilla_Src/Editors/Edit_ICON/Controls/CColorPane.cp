// ===========================================================================
// CColorPane.cp
//                       Created: 2004-12-11 18:53:05
//             Last modification: 2004-12-14 14:59:13
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CColorPane.h"
#include "CColorPopup.h"
#include "CColorUtils.h"
#include "UIconMisc.h"
#include "UPopupDrawing.h"


// ============================================================
// 	CColorPane
// ============================================================

CColorPane::CColorPane( LStream *inStream ) : LPane( inStream )
{
	RGBColor	anRGB;
	
	mColorTable = nil;	
	mClippedRgn = nil;
	
	/*
		read in the default color and whether we clip (from the PPob resource).
		note: Constructor for CW10 used the userCon field for the color -- CW11
				uses the stream data instead.
	*/
	inStream->ReadData( &anRGB, sizeof(RGBColor) );
	mCurrentColor = CColorUtils::RGBToColor32( anRGB );
	
	inStream->ReadData( &mClipsToSibblings, sizeof(mClipsToSibblings) );
	inStream->ReadData( &mUsePickerOption, sizeof(mUsePickerOption) );
}


// ============================================================
// 	CreateColorStream
// ============================================================

CColorPane *CColorPane::CreateFromStream( LStream *inStream )
{
	return new CColorPane( inStream );
}



// ============================================================
// 	FinishCreateSelf
// ============================================================

void CColorPane::FinishCreateSelf()
{
		// (note: this is non-dynamic, but ok since we don't move panes around)
	this->CalcClipRegionForOverlap();
}


// ============================================================
// 	Destructor
// ============================================================

CColorPane::~CColorPane()
{
	if ( mClippedRgn )
		::DisposeRgn( mClippedRgn );
		
	this->DisposeCurrentTable();
}


// ============================================================
// 	CColorPane::CalcClipRegionForOverlap
// ============================================================

void CColorPane::CalcClipRegionForOverlap()
{
	// see if we are behind any other views and set our clip region

	Rect		ourRect, peerRect, dummyRect;
	RgnHandle	peerRgn = nil;
	
		// assume we don't clip at all -- get our entire region	
	mClippedRgn = ::NewRgn();
	ThrowIfMemFail_( mClippedRgn );

	peerRgn = ::NewRgn();
	ThrowIfMemFail_( peerRgn );
	
	CalcPortFrameRect( ourRect );
	::RectRgn( mClippedRgn, &ourRect );

	LView	*parentView = this->GetSuperView();

	if ( mClipsToSibblings )
	{
			// iterate through our parent view's list of panes
			// should we make this a recursive search ???
		LPane	*peerItem;
		
		LArrayIterator	anIterator( parentView->GetSubPanes() );
		
			// loop until we're done with the list or (more likely) we hit ourselves
			// since we draw on top of everything after us
		while( anIterator.Next( &peerItem ) && (peerItem != this) )
		{
			peerItem->CalcPortFrameRect( peerRect );
			if ( ::SectRect( &ourRect, &peerRect, &dummyRect ) )
			{
				::RectRgn( peerRgn, &peerRect );
				::DiffRgn( mClippedRgn, peerRgn, mClippedRgn );
			}
		}
	}
	
		// when we draw, the origin is the top/left of our superview,
		//  so offset the region accordingly
	parentView->CalcPortFrameRect( dummyRect );
	::OffsetRgn( mClippedRgn, -dummyRect.left, -dummyRect.top );
	::DisposeRgn( peerRgn );
}


// ============================================================
// 	SetColor
// ============================================================

void CColorPane::SetColor( Color32 inColor, ERedrawOptions inRedrawHow )
{
	/*
		only redraw if we need to (prevents flicker)
	*/
	if ( !CColorUtils::EqualColor32( inColor, mCurrentColor ) )
	{
		mCurrentColor = inColor;

		if ( inRedrawHow == redraw_Now )
			this->DrawSwatch();				// prevent flicker -- just redraw swatch
		else
			UIconMisc::RedrawPaneAsIndicated( this, inRedrawHow );

		this->BroadcastMessage( this->GetPaneID(), (void*) inColor );
	}
}


// ============================================================
// 	GetColor
// ============================================================

Color32 CColorPane::GetColor()
{
	return( mCurrentColor );
}


// ============================================================
// 	GetColorTable
// ============================================================

CTabHandle CColorPane::GetColorTable()
{
	return( mColorTable );
}


// ============================================================
// 	SetColorTable
// 	
// 	Note:
// 	Nil is ok if you want to disassociate a table with this pane.
// ============================================================

void CColorPane::SetColorTable( CTabHandle inTable, Boolean inChangeColorToo, ERedrawOptions inRedrawHow )
{
	Handle	copyOfTable = inTable ? UIconMisc::DuplicateHandle((Handle)inTable) : nil;

	this->DisposeCurrentTable();
	mColorTable = (CTabHandle) copyOfTable;
	
		// change the currently displayed color if it's not in the
		// new table
	if ( mColorTable && inChangeColorToo )
	{
		UInt8		newIndex;
		RGBColor 	oldRGB = CColorUtils::Color32ToRGB( mCurrentColor );

		if ( !CColorUtils::IsColorInTable( mColorTable, oldRGB, &newIndex ) )
		{
			RGBColor	newRGB = (**mColorTable).ctTable[ newIndex ].rgb;
			this->SetColor( CColorUtils::RGBToColor32(newRGB), inRedrawHow );
		}
	}
}


// ============================================================
// 	DisposeCurrentTable
// ============================================================

void CColorPane::DisposeCurrentTable()
{
	if ( mColorTable )
	{
		::DisposeCTable( mColorTable );
		mColorTable = nil;
	}
}


// ============================================================
// 	DrawSelf
// 	
// 	Note:
// 	ColorPanes often overlap. This wouldn't be a problem except that we need
// 	to redraw the pane outside of the event loop if the application tells us
// 	to change our color (while the dropper tool is being used, for example).
// 	
// 	So we clip.
// ============================================================

void CColorPane::DrawSelf()
{
	Rect				r, swatchR;
	StClipRgnState		aClipObject( mClippedRgn );		// clip us to prevent overlap
	
	CalcLocalFrameRect( r );
	UPopupDrawing::DrawPopup( r, false /* not hilited */, IsEnabled() );

	UPopupDrawing::CalculateSwatchArea( r, &swatchR );
	this->DrawSwatchSelf( swatchR );
}



// ============================================================
// 	ClickSelf
// ============================================================

void CColorPane::ClickSelf( const SMouseDownEvent &inEvent )
{
	Rect		portR, localR;
	Point		pt;
	Color32		colorChosen;
	
	this->CalcPortFrameRect( portR );
	this->CalcLocalFrameRect( localR );

		// find the bottom/left of the control in global coordinates
	this->PortToGlobalPoint( topLeft(portR) );
	this->PortToGlobalPoint( botRight(portR) );
	pt.h = portR.left;
	pt.v = portR.bottom;

		// hilite the control
	this->DrawPopup( true /* hilited */, true /* enabled */ );
	
		// prepare for drawing, clip to prevent overlap with other color pane
	this->FocusDraw();
	StClipRgnState		aClipObject( mClippedRgn );	
	
	if ( !mColorTable || (mUsePickerOption && (inEvent.macEvent.modifiers & optionKey)) )
	{
		if ( this->DoAppleColorPicker( &colorChosen ) )
			this->SetColor( colorChosen, redraw_Dont );
	}
	else
	{
			// show the popup & track the user's actions
		SInt32	defaultItem = this->GetColorIndex( mCurrentColor );
		SInt32	newColorIndex = CColorPopup::DoColorPopup( pt, mColorTable, defaultItem );
		
			// save the new value (broadcast, redraw, etc)
			// note: ColorIndex is only a Byte and newColor may be -1, so watch out
		if ( newColorIndex != -1 )
		{
				// convert newColorIndex to a Color32
			RGBColor	colorChosenRGB = (**mColorTable).ctTable[ newColorIndex ].rgb;
			colorChosen = CColorUtils::RGBToColor32( colorChosenRGB );

			this->SetColor( colorChosen, redraw_Dont );
		}
	}

		// unhilite the control
	this->DrawPopup( false /* not hilited */, true /* enabled */ );
}


// ============================================================
// 	DoAppleColorPicker
// ============================================================

Boolean CColorPane::DoAppleColorPicker( Color32 *outColor )
{
	Point		pt = { -1, -1 };			// picker will choose location
	RGBColor	currentRGB = CColorUtils::Color32ToRGB( mCurrentColor );
	RGBColor	newRGB;
	Boolean		colorChanged = false;
	
	UDesktop::Deactivate();
	
	if ( ::GetColor( pt, (StringPtr)"", &currentRGB, &newRGB ) )
		if ( !CColorUtils::EqualRGB( currentRGB, newRGB ) )
		{
			*outColor = CColorUtils::RGBToColor32( newRGB );
			colorChanged = true;
		}

	UDesktop::Activate();
	return( colorChanged );
}


// ============================================================
// 	DrawPopup
// ============================================================

void CColorPane::DrawPopup( Boolean inHilited, Boolean inEnabled )
{
	Rect	localR, swatchR;

	this->FocusDraw();
	this->CalcLocalFrameRect( localR );
	
	StClipRgnState	aClip( mClippedRgn );		// don't draw on overlapped popup
	
	UPopupDrawing::DrawPopup( localR, inHilited, inEnabled );
	
	UPopupDrawing::CalculateSwatchArea( localR, &swatchR );
	this->DrawSwatchSelf( swatchR );
}


// ============================================================
// 	DrawSwatch
// ============================================================

void CColorPane::DrawSwatch()
{
	Rect	localR, swatchR;
	
	this->FocusDraw();
	this->CalcLocalFrameRect( localR );

	StClipRgnState	aClip( mClippedRgn );		// don't draw on overlapped popup
	UPopupDrawing::CalculateSwatchArea( localR, &swatchR );
	
	this->DrawSwatchSelf( swatchR );
}


// ============================================================
// 	DrawSwatchSelf
// ============================================================

void CColorPane::DrawSwatchSelf( const Rect &swatchR )
{
	RGBColor swatchRGB = CColorUtils::Color32ToRGB( mCurrentColor );
	
	::PenNormal();
	::RGBForeColor( &swatchRGB );
	::PaintRect( &swatchR );
}


// ============================================================
// 	PointIsInFrame
// 	
// 	Notes:
// 	This is here because the user can click in the overlapped portion of 2
// 	  panes and PP selects the wrong one by default.
// 	Incoming points are in port coordinates.
// 	mClippedRgn is in local (superview relative) coordinates.
// ============================================================

Boolean CColorPane::PointIsInFrame( SInt32 inHoriz, SInt32 inVert) const
{
	Point	pt = { inVert, inHoriz };
	
	if ( LPane::PointIsInFrame( inHoriz, inVert ) )
	{
		PortToLocalPoint( pt );	
		if ( ::PtInRgn( pt, mClippedRgn ) )
			return( true );
	}
	
	return( false );
}


// ============================================================
// 	GetColorIndex
// ============================================================

SInt32 CColorPane::GetColorIndex( Color32 inColor )
{
	if ( !mColorTable ) return( -1 );
	
	RGBColor	theRGB = CColorUtils::Color32ToRGB( inColor );
	UInt8		index;
	
	if ( CColorUtils::IsColorInTable( mColorTable, theRGB, &index ) )
		return( index );
	
	return( -1 );
}


// ============================================================
// 	AllowPickerOption
// ============================================================

void CColorPane::AllowPickerOption( Boolean inOption )
{
	mUsePickerOption = inOption;
}

