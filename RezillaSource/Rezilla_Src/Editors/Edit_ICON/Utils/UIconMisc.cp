// ===========================================================================
// UIconMisc.cp
//                       Created: 2004-12-11 18:52:00
//             Last modification: 2004-12-15 13:04:55
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "UIconMisc.h"
#include "UResourceMgr.h"

#include <stdio.h>


// 	Low memory keymap address
#define kKeyMapAddr		0x174



// ---------------------------------------------------------------------------
// 	DisposeHandle
// ---------------------------------------------------------------------------
// 	Disposes of a handle without having to know if it is a resource manager or
// 	memory manager one.

void
UIconMisc::DisposeHandle( void *h )
{
	if ( !h ) return;	
	
	// Assume a resource is purged
	if ( !*(Handle)h )				
	{
		::ReleaseResource( (Handle)h );	
		return;
	}

	Byte flags = ::HGetState( (Handle) h );
	if ( flags & 0x0020 )				/* a resource? */
		::ReleaseResource( (Handle) h );
	else
		::DisposeHandle( (Handle) h );
}


// ---------------------------------------------------------------------------
// 	GetMouseRelativeToPort
// ---------------------------------------------------------------------------

void
UIconMisc::GetMouseRelativeToPort( Point *outPt )
{
	GrafPtr		currentPort;
	Rect		theRect;
	
	GetPort( &currentPort );
	ThrowIfNil_( currentPort );				// should never happen
	
	GetMouse( outPt );
	
	::GetPortBounds(currentPort, &theRect);
	
	outPt->h -= theRect.left;	// repair SetOrigin changes
	outPt->v -= theRect.top;
}


// ---------------------------------------------------------------------------
// 	GetMouseRelativeToView
// ---------------------------------------------------------------------------
// 	A pane's coordinates are relative to the top/left of the view
// 	they are contained in. A view's coordinates are the top/left
// 	of the view itself.

void
UIconMisc::GetMouseRelativeToView( LPane *inPane, Point *outPt )
{
	ThrowIfNil_( inPane );
	inPane->FocusDraw();					// sets port and origin
	GetMouse( outPt );
}


// ---------------------------------------------------------------------------
// 	SetGWorld
// ---------------------------------------------------------------------------

void
UIconMisc::SetGWorld( CGrafPtr inPort, GDHandle inDevice )
{
	ThrowIfNil_( inPort );	// shouldn't happen
	
	::SetGWorld( inPort, inDevice );
	
	// Tell PP the port has changed since it caches it
	LView::OutOfFocus( nil );	
}


// ---------------------------------------------------------------------------
// 	SetPort
// ---------------------------------------------------------------------------
// Sets the current port, invalidates PowerPlant's LPane cache, sets the
// origin to 0,0, the GDevice to the main device, and the clip rect to the
// port rect.

void
UIconMisc::SetPort( GrafPtr inPort )
{
	if ( inPort )
	{
		Rect theRect;

		if ( UQDGlobals::GetCurrentPort() != inPort ) {
			::SetPort( inPort );
		}
		
		// Set the gdevice to the main device (if it isn't already).
		// The Window Mgr requires this when opening windows etc.
		GDHandle mainDevice = ::GetMainDevice();
		if ( GetGDevice() != mainDevice ) {
			::SetGDevice( mainDevice );
		}

		// Since PP changes this all the time	
		::SetOrigin( 0, 0 );
		::GetPortBounds(inPort, &theRect);
		::ClipRect( &theRect );
		
		// Tell PP the port has changed since it caches it
		LView::OutOfFocus( nil );	
	}
}


// ---------------------------------------------------------------------------
// 	IsShiftKey
// ---------------------------------------------------------------------------
// There are probably better ways to do this (OSEventAvail, for example),
// but this way is quick and easy and works from trap patches, etc.

Boolean
UIconMisc::IsShiftKey()
{
	if ( *(UInt8*)(kKeyMapAddr + 7) & 0x01 )
		return( true );
	return( false );
}


// ---------------------------------------------------------------------------
// 	IsOptionKey
// ---------------------------------------------------------------------------

Boolean
UIconMisc::IsOptionKey( void )
{
	if ( *(UInt8*)(kKeyMapAddr + 7) & 0x04 )
		return( true );
	return( false );
}


// ---------------------------------------------------------------------------
// 	ClearMemory
// ---------------------------------------------------------------------------

void
UIconMisc::ClearMemory( void *theBuffer, UInt32 numBytes )
{
	UInt8 *p = (UInt8*) theBuffer;
	
	while( numBytes-- > 0 )
		*p++ = 0;
}


// ---------------------------------------------------------------------------
// 	SetMemory
// ---------------------------------------------------------------------------

void
UIconMisc::SetMemory( void *buffer, UInt8 toWhat, UInt32 numBytes )
{
	UInt8	*p = (UInt8*) buffer;
	
	ThrowIfNil_( p );					// can't hurt to check
	
	while( numBytes-- > 0 )
		*p++ = toWhat;
}


// ---------------------------------------------------------------------------
// 	DuplicateHandle
// ---------------------------------------------------------------------------

Handle
UIconMisc::DuplicateHandle( Handle source )
{
	ThrowIf_ ( !source || !*source );
	
	SInt32 numBytes = GetHandleSize( source );
	Handle result = NewHandle( numBytes );
	ThrowIfMemFail_( result );
	
	BlockMoveData( *source, *result, numBytes );
	return( result );
}


// ---------------------------------------------------------------------------
// 	GetTopView
// ---------------------------------------------------------------------------

LView *
UIconMisc::GetTopView( LPane *inPane )
{
	LView	*theView, *superView;
	
	ThrowIfNil_( inPane );

	// If the pane has no superview, it might be the top view itself so
	// we'll just return it.
	theView = (LView*) inPane;
	while( true )
	{
		superView = theView->GetSuperView();
		if ( !superView )
			break;
		else
			theView = superView;
	}
	return theView;
}


// ---------------------------------------------------------------------------
// 	FindSiblingPaneByID
// ---------------------------------------------------------------------------

LPane *
UIconMisc::FindSiblingPaneByID( LPane *inPane, PaneIDT inPaneID )
{
	ThrowIfNil_( inPane );
	
	LView *topView = UIconMisc::GetTopView( inPane );
	ThrowIfNil_( topView );
	
	return( topView->FindPaneByID( inPaneID ) );
}


// ---------------------------------------------------------------------------
// 	GetWindowGlobalBounds
// ---------------------------------------------------------------------------

void
UIconMisc::GetWindowGlobalBounds( WindowPtr inWindow, Rect &oRect )
{
	StGWorldSaver	aSaver;

	::GetWindowPortBounds(inWindow, &oRect);
	::LocalToGlobal( (Point*) &oRect );
	::LocalToGlobal( 1 + (Point*) &oRect );
}


// ---------------------------------------------------------------------------
// 	LinkListenerToControls
// ---------------------------------------------------------------------------
// 	This is the same as the UReanimator method, but this will work with any
// 	broadcaster instead of just LControl.

void
UIconMisc::LinkListenerToControls(
		LListener	*inListener,
		LView		*inControlContainer,
		ResIDT		inResListID)
{
	#pragma options align=mac68k

	typedef struct {
		SInt16	numberOfItems;
		PaneIDT	itemID[1];
	} SResList, *SResListP;

	#pragma options align=reset

	StResource	idList('RidL', inResListID);
	HLockHi(idList.mResourceH);
	SResListP	resListP = (SResListP) *idList.mResourceH;
	
	for (SInt16 i = 0; i < resListP->numberOfItems; i++) 
	{
		LPane* thePane = inControlContainer->FindPaneByID(resListP->itemID[i] ) ;
		LBroadcaster 	*theBroad = dynamic_cast<LBroadcaster*>(thePane);
		if (theBroad != nil) {
			theBroad->AddListener( inListener );
		}
	}
}


// ---------------------------------------------------------------------------
// 	RedrawPaneAsIndicated
// ---------------------------------------------------------------------------

void
UIconMisc::RedrawPaneAsIndicated( LPane *inPane, RedrawOptions inOptions )
{
	if ( inOptions == redraw_Now )
		inPane->Draw( nil );
	else if ( inOptions == redraw_Later )
		inPane->Refresh();
}


// ---------------------------------------------------------------------------
// 	CreatePPWindow
/// ---------------------------------------------------------------------------
// 	Safer way to create a window.

LWindow *
UIconMisc::CreatePPWindow( ResIDT inWindowID )
{
	StGWorldSaver			aSaver;
	LWindow 				*theWindow = nil;
	
	// Create the window
	::SetGDevice( GetMainDevice() );				// bug in Mac toolbox requires this
	theWindow = LWindow::CreateWindow( inWindowID, LCommander::GetTopCommander() );
	return( theWindow );
}


// ---------------------------------------------------------------------------
// 	ForceRectToScreen
/// ---------------------------------------------------------------------------
// 	Pulls a rectangle to the screen it's on.

void
UIconMisc::ForceRectToScreen( const Rect &inRect, Rect *outRect, GDHandle inScreen )
{
	GDHandle	theDevice = nil;
	Rect		deviceR, tempR;
		
	*outRect = inRect;
	
	// Figure out which screen to use
	if ( inScreen )
		theDevice = inScreen;
	else
		theDevice = UWindows::FindDominantDevice( inRect );
		
	if ( !theDevice )
		theDevice = ::GetMainDevice();
	if ( !theDevice )
		return;						// shouldn't happen
	
	deviceR = (**theDevice).gdRect;
	if ( theDevice == ::GetMainDevice() )
		deviceR.top += ::GetMBarHeight();
	
	// See if it is completely within a single monitor rectangle
	::SectRect( &deviceR, &inRect, &tempR );
	if ( !::EqualRect( &tempR, &inRect ) )
	{
		// Move it as needed
		if ( inRect.left < deviceR.left )
			::OffsetRect( outRect, deviceR.left - inRect.left, 0 );
		else if ( inRect.right > deviceR.right )
			::OffsetRect( outRect, deviceR.right - inRect.right, 0 );
			
		if ( inRect.top < deviceR.top )
			::OffsetRect( outRect, 0, deviceR.top - inRect.top );
		else if ( inRect.bottom > deviceR.bottom )
			::OffsetRect( outRect, 0, deviceR.bottom - inRect.bottom );
	}
}


// ---------------------------------------------------------------------------
// 	FindDeviceViaPoint
// ---------------------------------------------------------------------------

GDHandle
UIconMisc::FindDeviceViaPoint( Point inGlobalPt )
{
	GDHandle		theDevice = ::GetDeviceList();
	
	while( theDevice ) {
		if ( UDrawingUtils::IsActiveScreenDevice( theDevice ) )
		{
			Rect	deviceR = (**theDevice).gdRect;
		
			if ( ::PtInRect( inGlobalPt, &deviceR ) )
				return( theDevice );
		}
		
		theDevice = ::GetNextDevice( theDevice );
	}
	
	return( nil );
}



/******************************
*                             *
*      URegionMisc CLASS      *
*                             *
******************************/

// ---------------------------------------------------------------------------
// 	NewRegionFromRect
// ---------------------------------------------------------------------------

RgnHandle
URegionMisc::NewRegionFromRect( const Rect &r )
{
	RgnHandle	result = URegionMisc::NewRegion();
	
	::RectRgn( result, &r );
	return( result );
}


// ---------------------------------------------------------------------------
// 	NewRegionFromRect
// ---------------------------------------------------------------------------

RgnHandle
URegionMisc::NewRegionFromRect( SInt32 left, SInt32 top, SInt32 right, SInt32 bottom )
{
	Rect	r;
	SetRect( &r, left, top, right, bottom );
	return( URegionMisc::NewRegionFromRect( r ) );
}


// ---------------------------------------------------------------------------
// 	NewRegionFromPolygon
// ---------------------------------------------------------------------------

RgnHandle
URegionMisc::NewRegionFromPolygon( PolyHandle inPoly )
{
	StGWorldSaver		aSaver;
	
	UIconMisc::SetPort( USparePort::GetSparePort() );
	RgnHandle	result = ::NewRgn();
	ThrowIfMemFail_( result );
	
	::OpenRgn();
	if ( inPoly && *inPoly )
		::FramePoly( inPoly );
	::CloseRgn( result );
	
	return( result );
}


// ---------------------------------------------------------------------------
// 	NewRegionFromRegion
// ---------------------------------------------------------------------------

RgnHandle
URegionMisc::NewRegionFromRegion( RgnHandle source )
{
	RgnHandle	result = URegionMisc::NewRegion();

	CopyRgn( source, result );
	return( result );
}


// ---------------------------------------------------------------------------
// 	NewRegion
// ---------------------------------------------------------------------------

RgnHandle
URegionMisc::NewRegion()
{
	RgnHandle	result = ::NewRgn();
	ThrowIfMemFail_( result );
	return( result );
}


// ---------------------------------------------------------------------------
// 	DisposeRegion
// ---------------------------------------------------------------------------

void
URegionMisc::DisposeRegion( RgnHandle &inRegion )
{
	if ( inRegion )
	{
		::DisposeRgn( inRegion );
		inRegion = nil;
	}
}



/***********************
*                      *
*   USparePort CLASS   *
*                      *
***********************/

// Static variables
Boolean		USparePort::sInitted = false;
GrafPtr		USparePort::sPortPtr = nil;


// ---------------------------------------------------------------------------
// 	GetSparePort
// ---------------------------------------------------------------------------

GrafPtr
USparePort::GetSparePort()
{
	if ( !sInitted ) {
		sPortPtr = ::CreateNewPort();
		ThrowIfNil_(sPortPtr);
		sInitted = true;
	}

	return sPortPtr;
}


// ---------------------------------------------------------------------------
// 	Cleanup
// ---------------------------------------------------------------------------

void
USparePort::Cleanup()
{
	if ( sInitted ) {
		::DisposePort( sPortPtr );
		sInitted = false;
	}
}



/**************************
*                         *
*   StGWorldSaver CLASS   *
*                         *
**************************/

// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------

StGWorldSaver::StGWorldSaver()
{
	::GetGWorld( &mPort, &mDevice );
}


// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------

StGWorldSaver::StGWorldSaver( GWorldPtr inWorld )
{
	::GetGWorld( &mPort, &mDevice );
	UIconMisc::SetGWorld( inWorld, nil );
}


// ---------------------------------------------------------------------------
// 	Destructor
// ---------------------------------------------------------------------------

StGWorldSaver::~StGWorldSaver()
{
	if ( mPort ) {
		UIconMisc::SetGWorld( mPort, mDevice );
	}
}

