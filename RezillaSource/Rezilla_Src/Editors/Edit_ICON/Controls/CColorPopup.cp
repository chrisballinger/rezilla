// ===========================================================================
// CColorPopup.cp
//                       Created: 2004-12-11 18:53:07
//             Last modification: 2004-12-14 14:08:18
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CColorPopup.h"
#include "RezillaConstants.h"

#include <math.h>


// ---------------------------------------------------------------------------
// 	CColorPopup::DoColorPopup
// ---------------------------------------------------------------------------
// This is the main (and only) entry point into the Color Popup code. It
// opens the popup window, handles user selection, and returns the item
// chosen by the user (0..n-1) or -1 if nothing.

SInt32
CColorPopup::DoColorPopup( Point inTopLeft, CTabHandle inTable, SInt32 defaultItem )
{
	CColorPopup		thePopup( inTable );		// note: object on stack
	
	return( thePopup.DoPopup( inTopLeft, defaultItem ) );
}


// ---------------------------------------------------------------------------
// 	CColorPopup											 [constructor]
// ---------------------------------------------------------------------------

CColorPopup::CColorPopup( CTabHandle inTable )
{
	mColorTable = inTable;
}


// ---------------------------------------------------------------------------
// 	CColorPopup											 [destructor]
// ---------------------------------------------------------------------------

CColorPopup::~CColorPopup()
{
}


// ---------------------------------------------------------------------------
// 	CColorPopup::Prepare
// ---------------------------------------------------------------------------
// 	Must set: mItems, mRows, mCols, mFirstitemRect, mCellWidth,
// 	mCellHeight, mWindowRect

void
CColorPopup::Prepare( Point inTopLeft )
{
	ThrowIfNil_( mColorTable );
	
	mItems = (**mColorTable).ctSize + 1;
	
	// Give the popup a nice rectangular look
	// mCols = ((SInt32) sqrt( mItems )) * 2;

	if ( mItems <= 16 )
		mCols = MIN( mItems, 8 );
	else if ( mItems <= 36 )
		mCols = MIN( mItems, 12 );
	else
		mCols = MIN( mItems, 32 );
	
	mRows = 1 + (mItems - 1) / mCols;

	if ( mItems <= 36 )
	{
		mCellWidth = 21;		// includes space between cells
		mCellHeight = 21;
	}
	else
	{
		mCellWidth = 11;
		mCellHeight = 11;
	}
	
	::SetRect( &mFirstItemRect, kColorMargins, kColorMargins, 
				kColorMargins + mCellWidth, kColorMargins + mCellHeight );
	
	mWindowRect.left = inTopLeft.h + 3;
	mWindowRect.right = mWindowRect.left + kColorMargins * 2 + mCols * mCellWidth;
	mWindowRect.top = inTopLeft.v;
	mWindowRect.bottom = mWindowRect.top + kColorMargins * 2 + mRows * mCellHeight;
}


// ---------------------------------------------------------------------------
// 	CColorPopup::DrawInitialState
// ---------------------------------------------------------------------------

void
CColorPopup::DrawInitialState()
{
	for ( SInt32 count = 0; count < mItems; count++ )
		this->DrawOneCell( count );
}


// ---------------------------------------------------------------------------
// 	CColorPopup::DrawOneCell
// ---------------------------------------------------------------------------

void
CColorPopup::DrawOneCell( SInt32 inIndex, Boolean inHilited )
{
	Rect		r, itemR;

	if ( !mColorTable ) return;

	if ( !this->GetItemRect( inIndex, &itemR ) )
		return;
	r = itemR;

	if ( inHilited )
	{
		::RGBForeColor( &Color_White );
		::FrameRect( &r );
		
		::RGBForeColor( &Color_Black );
		::InsetRect( &r, -1, -1 );
		::FrameRect( &r );
	}
	else
	{
		::RGBForeColor( &Color_Black );
		::FrameRect( &r );
		
		::RGBForeColor( &Color_White );
		::InsetRect( &r, -1, -1 );
		::FrameRect( &r );
	}
	
	// Draw the color swatch itself
	RGBColor	theRGB = (**mColorTable).ctTable[ inIndex ].rgb;
	::RGBForeColor( &theRGB );
	::InsetRect( &itemR, 1, 1 );
	::PaintRect( &itemR );
}


