// ===========================================================================
// CPopupWindow.cp
//                       Created: 2004-12-11 18:53:11
//             Last modification: 2004-12-14 14:38:17
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// ===========================================================================

#include "RezillaConstants.h"
#include "CPopupWindow.h"
#include "UIconMisc.h"


// ---------------------------------------------------------------------------
// 	CPopupWindow											 [constructor]
// ---------------------------------------------------------------------------

CPopupWindow::CPopupWindow()
{
	mItems = 0;
	mRows = mCols = 0;
	mCellWidth = mCellHeight = 0;
	SetRect( &mFirstItemRect, 0, 0, 0, 0 );
}


// ---------------------------------------------------------------------------
// 	CPopupWindow											 [destructor]
// ---------------------------------------------------------------------------

CPopupWindow::~CPopupWindow()
{
}


// ---------------------------------------------------------------------------
// 	CPopupWindow::DoPopup
// ---------------------------------------------------------------------------
// Returns the item number selected (0..n). Returns the default item number
// if nothing is selected. -1 means nothing selected and no default was
// specified.

SInt32
CPopupWindow::DoPopup( Point inTopLeft, SInt32 defaultItem )
{
	SInt32			result = -1;
	WindowPtr		macWindow = nil;
	StGWorldSaver	saveTheWorld;
	
	try
	{
		mDefaultItem = defaultItem;
		this->Prepare( inTopLeft );
		macWindow = this->CreateMacWindow();
		this->DrawInitialState();
		result = this->TrackMouse();
	}
	catch( ... )
	{
		// don't want to throw an error here???
	}
	
	if ( macWindow )
		::DisposeWindow( macWindow );

	return( result );
}


// ---------------------------------------------------------------------------
// 	CPopupWindow::CreateMacWindow
// ---------------------------------------------------------------------------
// 	Sets the current port to the window.

WindowPtr
CPopupWindow::CreateMacWindow()
{
	WindowPtr	theWindow = nil;
	Rect		windowR;
	
	::SetGDevice( GetMainDevice() );
	
	// Move the window so it is completely visible on a single screen. Use
	// the mouse location rather than mWindowRect to determine the screen
	// for two cases:
	// (1) The popup control is at the very bottom of a screen and the
	//     popup window wouldn't be visible at all.
	// (2) The popup control spans two screens. It's cooler to show the
	//     popup window on the same screen as the mouse.

	Point pt;
	::GetMouse( &pt );
	::LocalToGlobal( &pt );
	GDHandle	theDevice = UIconMisc::FindDeviceViaPoint( pt );

	if ( !theDevice )
		theDevice = UIconMisc::FindDeviceViaPoint( topLeft(mWindowRect) );

	UIconMisc::ForceRectToScreen( mWindowRect, &windowR, theDevice );
	
	// Prevent front window from deactivating title - create our window in
	// back and then call BringToFront.
	theWindow = ::NewCWindow( NULL, &windowR, (StringPtr)"", true /* visible */, plainDBox, 
							(WindowPtr) 0, false /* go away */, 0 /* refCon */);
	ThrowIfMemFail_( theWindow );
	::BringToFront( theWindow );
	::SetPortWindowPort( theWindow );
	
	return( theWindow );
}


// ---------------------------------------------------------------------------
// 	CPopupWindow::TrackMouse
// ---------------------------------------------------------------------------

SInt32
CPopupWindow::TrackMouse()
{
	SInt32		currentItem = -1, prevItem = -1;
	Point		pt;
	Boolean		mouseOutside = true;
	
	while( ::StillDown() )
	{
		::GetMouse( &pt );
		currentItem = this->LocalPointToIndex( pt );
		
			// default back to the default item if the mouse is outside the window
		if ( currentItem == -1 )
		{
			mouseOutside = true;
			currentItem = mDefaultItem;
		}
		else
			mouseOutside = false;
		
		if ( currentItem != prevItem )
		{
			this->HiliteItem( prevItem, false );
			this->HiliteItem( currentItem, true );
			prevItem = currentItem;
		}
	}

	if ( !mouseOutside )
		this->FlashItem( currentItem );
		
	return( currentItem );
}


// ---------------------------------------------------------------------------
// 	CPopupWindow::HiliteItem
// ---------------------------------------------------------------------------

void
CPopupWindow::HiliteItem( SInt32 theItem, Boolean inHilited )
{
	this->DrawOneCell( theItem, inHilited );
}

// #ifdef OLDWAY
// 
// // ---------------------------------------------------------------------------
// // 	CPopupWindow::HiliteItem
// // ---------------------------------------------------------------------------
// 
// void CPopupWindow::HiliteItem( SInt32 theItem, Boolean inHilited )
// {
// 	Rect	r;
// 
// 	if ( !this->GetItemRect( theItem, &r ) )
// 		return;
// 		
// 	--r.top;
// 	--r.left;
// 	
// 	if ( inHilited )
// 	{
// 		::RGBForeColor( &Color_Black );
// 		::FrameRect( &r );
// 	
// 		::RGBForeColor( &Color_White );
// 		::InsetRect( &r, 2, 2 );
// 		::FrameRect( &r );
// 	}
// 	else
// 	{
// 		::RGBForeColor( &Color_White );
// 		::FrameRect( &r );
// 		::RGBForeColor( &Color_Black );
// 		
// 			// since the hilite destroyed a bit of the cell, redraw it
// 		this->DrawOneCell( theItem );
// 	}
// 	
// }
// 
// 
// #ifdef OLDWAY
// 
// // ---------------------------------------------------------------------------
// // 	CPopupWindow::HiliteItem
// // ---------------------------------------------------------------------------
// 
// void CPopupWindow::HiliteItem( SInt32 theItem, Boolean /* hiliteIt */ )
// {
// 	Rect	r;
// 	
// 	if ( !this->GetItemRect( theItem, &r ) )
// 		return;
// 	
// 	::RGBForeColor( &Color_Black );
// 	::PenMode( patXor );
// 	::PenSize( 2, 2 );
// 	::FrameRect( &r );
// }



// ---------------------------------------------------------------------------
// 	CPopupWindow::LocalPointToIndex
// ---------------------------------------------------------------------------

SInt32
CPopupWindow::LocalPointToIndex( Point pt )
{
	SInt32		index;
	GrafPtr		theGrafPort;
	Rect		theRect;
	
	::GetPort( &theGrafPort );
	GetPortBounds(theGrafPort, &theRect);
	if ( !theGrafPort || !PtInRect( pt, &theRect ) )
		return( -1 );
		
	if ( (mCellWidth == 0) || (mCellHeight == 0) )
		return( -1 );
	
	SInt32	colNo = (pt.h - mFirstItemRect.left) / mCellWidth;
	if ( (colNo < 0) || (colNo > mCols) ) return( -1 );
	
	SInt32	rowNo = (pt.v - mFirstItemRect.top) / mCellHeight;
	if ( (rowNo < 0) || (rowNo > mRows) ) return( -1 );
	
	index = colNo + rowNo * mCols;
	
	// If mouse is within popup, but not over an item (last row)
	if ( (index < 0) || (index >= mItems) )
		index = -1;
		
	return( index );
}


// ---------------------------------------------------------------------------
// 	CPopupWindow::GetItemRect
// ---------------------------------------------------------------------------

Boolean
CPopupWindow::GetItemRect( SInt32 inItem, Rect *outR )
{
	if ( (inItem < 0) || (inItem >= mItems) || (mCols == 0) || (mRows == 0) )
		return( false );
		
	SInt32 whichCol = inItem % mCols;
	SInt32 whichRow = inItem / mCols;
	
	outR->left = mFirstItemRect.left + whichCol * mCellWidth;
	outR->right = outR->left + mCellWidth - 1;
	outR->top = mFirstItemRect.top + whichRow * mCellHeight;
	outR->bottom = outR->top + mCellHeight - 1;
	
	return( true );
}


// ---------------------------------------------------------------------------
// 	CPopupWindow::FlashItem
// ---------------------------------------------------------------------------

void
CPopupWindow::FlashItem( SInt32 theItem )
{
	Rect		r;
	SInt32		numFlashes;
	Boolean		hiliteIt = false;
	UInt32		dummy;
	
	if ( !GetItemRect( theItem, &r ) )
		return;
		
	// We need to loop twice for each flash, plus 1 extra time to unhilite 
	// it initially, so kFlashCount must be odd.
	numFlashes = kFlashCount;
	while( numFlashes-- > 0 )
	{
		this->HiliteItem( theItem, hiliteIt );
		hiliteIt = !hiliteIt;
		Delay( 4, &dummy );
	}
}

