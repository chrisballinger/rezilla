// ===========================================================================
// CColorPane.cp
//                       Created: 2004-12-11 18:53:05
//             Last modification: 2005-06-28 20:07:40
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004-2005
// All rights reserved.
// ===========================================================================

#include "CColorPane.h"
#include "CColorPopup.h"
#include "UColorUtils.h"
#include "UIconMisc.h"
#include "UMiscUtils.h"
#include "UPopupDrawing.h"


// ---------------------------------------------------------------------------
// 	CColorPane
// ---------------------------------------------------------------------------

CColorPane::CColorPane( LStream *inStream ) 
		: LBevelButton( inStream )
{
	RGBColor	theRGB;
//	inStream->ReadData( &theRGB, sizeof(RGBColor) );
	*inStream >> theRGB.red;
	*inStream >> theRGB.green;
	*inStream >> theRGB.blue;
	
	mCurrentColor = UColorUtils::RGBToColor32( theRGB );
	
//	inStream->ReadData( &mClipsToSiblings, sizeof(mClipsToSiblings) );
	*inStream >> mClipsToSiblings;
//	inStream->ReadData( &mUsePickerOption, sizeof(mUsePickerOption) );
	*inStream >> mUsePickerOption;
	
	mColorTable = nil;	
	mClippedRgn = nil;
}


// ---------------------------------------------------------------------------
// 	CreateColorStream
// ---------------------------------------------------------------------------

CColorPane *CColorPane::CreateFromStream( LStream *inStream )
{
	return new CColorPane( inStream );
}



// ---------------------------------------------------------------------------
// 	FinishCreateSelf
// ---------------------------------------------------------------------------

void
CColorPane::FinishCreateSelf()
{
	// This is non-dynamic, but ok since we don't move panes around
	this->CalcClipRegionForOverlap();
}


// ---------------------------------------------------------------------------
// 	Destructor
// ---------------------------------------------------------------------------

CColorPane::~CColorPane()
{
	if ( mClippedRgn )
		::DisposeRgn( mClippedRgn );
		
	this->DisposeCurrentTable();
}


// ---------------------------------------------------------------------------
// 	CColorPane::CalcClipRegionForOverlap
// ---------------------------------------------------------------------------

void
CColorPane::CalcClipRegionForOverlap()
{
	// See if we are behind any other views and set our clip region
	Rect		ourRect, peerRect, dummyRect;
	RgnHandle	peerRgn = nil;
	
	// Assume we don't clip at all -- get our entire region	
	mClippedRgn = ::NewRgn();
	ThrowIfMemFail_( mClippedRgn );

	peerRgn = ::NewRgn();
	ThrowIfMemFail_( peerRgn );
	
	CalcPortFrameRect( ourRect );
	::RectRgn( mClippedRgn, &ourRect );

	LView	*parentView = this->GetSuperView();

	if ( mClipsToSiblings )
	{
		// Iterate through our parent view's list of panes
		LPane	*peerItem;
		
		LArrayIterator	anIterator( parentView->GetSubPanes() );
		
		// Loop until we're done with the list.
		// Beware of the invisible control pane with ID PaneIDT_Unspecified
		// if the superview is an LControlView.
		while( anIterator.Next( &peerItem ) )
		{
			if ((peerItem == this) || (peerItem->GetPaneID() == PaneIDT_Unspecified)) {
				continue;
			} 
			peerItem->CalcPortFrameRect( peerRect );
			if ( ::SectRect( &ourRect, &peerRect, &dummyRect ) ) {
				::RectRgn( peerRgn, &peerRect );
				::DiffRgn( mClippedRgn, peerRgn, mClippedRgn );
			}
		}
	}
	
	// When we draw, the origin is the top/left of our superview, so offset
	// the region accordingly
	parentView->CalcPortFrameRect( dummyRect );
	::OffsetRgn( mClippedRgn, -dummyRect.left, -dummyRect.top );
	::DisposeRgn( peerRgn );
}


// ---------------------------------------------------------------------------
// 	SetColor
// ---------------------------------------------------------------------------

void
CColorPane::SetColor( Color32 inColor, RedrawOptions inRedrawHow )
{
	// Only redraw if we need to (prevents flicker)
	if ( !UColorUtils::EqualColor32( inColor, mCurrentColor ) )
	{
		mCurrentColor = inColor;

		if ( inRedrawHow == redraw_Now ) {
			this->DrawSwatch();
		} else {
			UIconMisc::RedrawPaneAsIndicated( this, inRedrawHow );
		}

		// The message is the same as the pane ID
		this->BroadcastMessage( this->GetPaneID(), (void*) inColor );
	}
}


// ---------------------------------------------------------------------------
// 	GetColor
// ---------------------------------------------------------------------------

Color32
CColorPane::GetColor()
{
	return( mCurrentColor );
}


// ---------------------------------------------------------------------------
// 	GetColorTable
// ---------------------------------------------------------------------------

CTabHandle
CColorPane::GetColorTable()
{
	return( mColorTable );
}


// ---------------------------------------------------------------------------
// 	SetColorTable
// ---------------------------------------------------------------------------
// 	Nil is ok if you want to disassociate a table with this pane.

void
CColorPane::SetColorTable( CTabHandle inTable, Boolean inChangeColorToo, RedrawOptions inRedrawHow )
{
	if (mColorTable == inTable) {
		return;
	} 
	
	this->DisposeCurrentTable();
	mColorTable = inTable;
	
	// Change the currently displayed color if it's not in the new table
	if ( mColorTable && inChangeColorToo )
	{
		UInt8		newIndex;
		RGBColor 	oldRGB = UColorUtils::Color32ToRGB( mCurrentColor );

		if ( !UColorUtils::IsColorInTable( mColorTable, oldRGB, &newIndex ) )
		{
			RGBColor	newRGB = (**mColorTable).ctTable[ newIndex ].rgb;
			this->SetColor( UColorUtils::RGBToColor32(newRGB), inRedrawHow );
		}
	}
}


// ---------------------------------------------------------------------------
// 	DisposeCurrentTable
// ---------------------------------------------------------------------------

void
CColorPane::DisposeCurrentTable()
{
	if ( mColorTable )
	{
		::DisposeCTable( mColorTable );
		mColorTable = nil;
	}
}


// ---------------------------------------------------------------------------
// 	DrawSelf
// ---------------------------------------------------------------------------
// 	ColorPanes often overlap. This wouldn't be a problem except that we
// 	need to redraw the pane outside of the event loop if the application
// 	tells us to change our color (while the dropper tool is being used, for
// 	example). So we clip.

void
CColorPane::DrawSelf()
{
	Rect	localR, swatchR;
	StClipRgnState		aClipObject( mClippedRgn );
	
	// Call inherited
	LBevelButton::DrawSelf();
	
	// Don't draw on overlapped popup, so clip us
	CalcLocalFrameRect( localR );
	UPopupDrawing::DrawPopupArrow( localR, false /* not hilited */, IsEnabled() );
	
	UPopupDrawing::CalculateSwatchArea( localR, &swatchR );
	this->DrawSwatchSelf( swatchR );
}



// ---------------------------------------------------------------------------
// 	ClickSelf
// ---------------------------------------------------------------------------

void
CColorPane::ClickSelf( const SMouseDownEvent &inEvent )
{
	Rect		portR, localR;
	Point		pt;
	Color32		colorChosen;
	
	this->CalcPortFrameRect( portR );
	this->CalcLocalFrameRect( localR );

	// Find the bottom/left of the control in global coordinates
	this->PortToGlobalPoint( topLeft(portR) );
	this->PortToGlobalPoint( botRight(portR) );
	pt.h = portR.left;
	pt.v = portR.bottom;

	// Hilite the control
	this->DrawPopup( true /* hilited */, true /* enabled */ );
	
	// Prepare for drawing, clip to prevent overlap with other color pane
	this->FocusDraw();
	StClipRgnState		aClipObject( mClippedRgn );	
	
	if ( !mColorTable || (mUsePickerOption && (inEvent.macEvent.modifiers & optionKey)) )
	{
		if ( this->DoAppleColorPicker( &colorChosen ) )
			this->SetColor( colorChosen, redraw_Dont );
	}
	else
	{
		// Show the popup & track the user's actions
		SInt32	defaultItem = this->GetColorIndex( mCurrentColor );
		SInt32	newColorIndex = CColorPopup::DoColorPopup( pt, mColorTable, defaultItem );
		
		// Save the new value (broadcast, redraw, etc). ColorIndex is only
		// a Byte and newColor may be -1, so watch out.
		if ( newColorIndex != -1 ) {
			// Convert newColorIndex to a Color32
			RGBColor	colorChosenRGB = (**mColorTable).ctTable[ newColorIndex ].rgb;
			colorChosen = UColorUtils::RGBToColor32( colorChosenRGB );

			this->SetColor( colorChosen, redraw_Dont );
		}
	}

	// Unhilite the control
	this->DrawPopup( false /* not hilited */, true /* enabled */ );
}


// ---------------------------------------------------------------------------
// 	DoAppleColorPicker
// ---------------------------------------------------------------------------

Boolean
CColorPane::DoAppleColorPicker( Color32 *outColor )
{
	Point		pt = { -1, -1 };			// picker will choose location
	RGBColor	currentRGB = UColorUtils::Color32ToRGB( mCurrentColor );
	RGBColor	newRGB;
	Boolean		colorChanged = false;
	
	UDesktop::Deactivate();
	
	if ( ::GetColor( pt, (StringPtr)"", &currentRGB, &newRGB ) )
		if ( !UColorUtils::EqualRGB( currentRGB, newRGB ) )
		{
			*outColor = UColorUtils::RGBToColor32( newRGB );
			colorChanged = true;
		}

	UDesktop::Activate();
	return( colorChanged );
}


// ---------------------------------------------------------------------------
// 	DrawPopup
// ---------------------------------------------------------------------------

void
CColorPane::DrawPopup( Boolean inHilited, Boolean inEnabled )
{
	Rect	localR, swatchR;

	this->FocusDraw();
	this->CalcLocalFrameRect( localR );
	
	StClipRgnState	aClip( mClippedRgn );		// don't draw on overlapped popup
	
	// Call inherited
	LBevelButton::DrawSelf();
	
	UPopupDrawing::DrawPopupArrow( localR, inHilited, inEnabled );
	
	UPopupDrawing::CalculateSwatchArea( localR, &swatchR );
	this->DrawSwatchSelf( swatchR );
}


// ---------------------------------------------------------------------------
// 	DrawSwatch
// ---------------------------------------------------------------------------

void
CColorPane::DrawSwatch()
{
	Rect	localR, swatchR;
	
	this->FocusDraw();
	this->CalcLocalFrameRect( localR );

	StClipRgnState	aClip( mClippedRgn );		// don't draw on overlapped popup
	UPopupDrawing::CalculateSwatchArea( localR, &swatchR );
	
	this->DrawSwatchSelf( swatchR );
}


// ---------------------------------------------------------------------------
// 	DrawSwatchSelf
// ---------------------------------------------------------------------------

void
CColorPane::DrawSwatchSelf( const Rect &swatchR )
{
	RGBColor swatchRGB = UColorUtils::Color32ToRGB( mCurrentColor );
	
	::PenNormal();
	::RGBForeColor( &swatchRGB );
	::PaintRect( &swatchR );
}


// ---------------------------------------------------------------------------
// 	PointIsInFrame
// ---------------------------------------------------------------------------
// 	This is here because the user can click in the overlapped portion of 2
// 	panes and PP selects the wrong one by default. Incoming points are in
// 	port coordinates. mClippedRgn is in local (superview relative)
// 	coordinates.

Boolean
CColorPane::PointIsInFrame( SInt32 inHoriz, SInt32 inVert) const
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


// ---------------------------------------------------------------------------
// 	GetColorIndex
// ---------------------------------------------------------------------------

SInt32
CColorPane::GetColorIndex( Color32 inColor )
{
	if ( !mColorTable ) return( -1 );
	
	RGBColor	theRGB = UColorUtils::Color32ToRGB( inColor );
	UInt8		index;
	
	if ( UColorUtils::IsColorInTable( mColorTable, theRGB, &index ) )
		return( index );
	
	return( -1 );
}


// ---------------------------------------------------------------------------
// 	AllowPickerOption
// ---------------------------------------------------------------------------

void
CColorPane::AllowPickerOption( Boolean inOption )
{
	mUsePickerOption = inOption;
}

