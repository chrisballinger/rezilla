// ===========================================================================
// CPatternPopup.cp
//                       Created: 2004-12-11 18:57:37
//             Last modification: 2004-12-14 14:08:01
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CPatternPopup.h"
#include "RezillaConstants.h"

#include <UDrawingState.h>


// ---------------------------------------------------------------------------
// 	CPatternPopup::DoPatternPopup
// ---------------------------------------------------------------------------
// This is the main (and only) entry point into the Pattern Popup code. It
// opens the popup window, handles user selection, and returns the item
// chosen by the user (0..n-1) or -1 if nothing.

SInt32
CPatternPopup::DoPatternPopup( Point inTopLeft, SPatternListH inPatterns, SInt32 defaultItem,
										const RGBColor &inFore, const RGBColor &inBack )
{
	CPatternPopup	thePopup( inPatterns, inFore, inBack );		// note: object on stack
	
	return( thePopup.DoPopup( inTopLeft, defaultItem ) );
}


// ---------------------------------------------------------------------------
// 	CPatternPopup											 [constructor]
// ---------------------------------------------------------------------------

CPatternPopup::CPatternPopup( SPatternListH inPatterns, const RGBColor &inFore, const RGBColor &inBack )
{
	mPatternList = inPatterns;
	mForeColor = inFore;
	mBackColor = inBack;
}


// ---------------------------------------------------------------------------
// 	CPatternPopup											 [destructor]
// ---------------------------------------------------------------------------

CPatternPopup::~CPatternPopup()
{
}


// ---------------------------------------------------------------------------
// 	Prepare
// ---------------------------------------------------------------------------
// 	Must set: mItems, mRows, mCols, mFirstitemRect, mCellWidth, 
// 	mCellHeight, mWindowRect.

void
CPatternPopup::Prepare( Point inTopLeft )
{
	ThrowIfNil_( mPatternList );
	
	mItems = (**mPatternList).numPatterns;
	
	mCols = MIN( mItems, 16 );				// MAX of 16 items across
	mRows = 1 + (mItems - 1) / mCols;

	mCellWidth = 16;
	mCellHeight = 16;
	SetRect( &mFirstItemRect, 1, 1, mCellWidth+1, mCellHeight+1 );
	
	mWindowRect.left = inTopLeft.h;
	mWindowRect.right = mWindowRect.left + mCols * mCellWidth + 2;
	mWindowRect.top = inTopLeft.v;
	mWindowRect.bottom = mWindowRect.top + mRows * mCellHeight + 2;
}


// ---------------------------------------------------------------------------
// 	CPatternPopup::DrawInitialState
// ---------------------------------------------------------------------------

void
CPatternPopup::DrawInitialState()
{
	ThrowIfNil_( mPatternList );
	
	StColorPenState		aPenState;
	aPenState.Normalize();

	for ( SInt32 count = 0; count < mItems; count++ )
		this->DrawOneCell( count );
}


// ---------------------------------------------------------------------------
// 	CPatternPopup::DrawOneCell
// ---------------------------------------------------------------------------

void
CPatternPopup::DrawOneCell( SInt32 inIndex, Boolean inHilited )
{
	Rect		r, itemR;

	if ( !mPatternList ) return;
	
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
	
	// Draw the pattern swatch itself
	Pattern aPat = (**mPatternList).patterns[ inIndex ];
	::PenPat( &aPat );
	::RGBForeColor( &mForeColor );
	::RGBBackColor( &mBackColor );
	::InsetRect( &itemR, 1, 1 );
	::PaintRect( &itemR );

	// Leave the pattern as black, color as black
	::PenPat( UQDGlobals::GetBlackPat(&aPat) );
	::RGBForeColor( &Color_Black );
	::RGBBackColor( &Color_White );
}

