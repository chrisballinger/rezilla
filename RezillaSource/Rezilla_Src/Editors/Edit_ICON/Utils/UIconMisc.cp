// ===========================================================================
// UIconMisc.cp
//                       Created: 2004-12-11 18:52:00
//             Last modification: 2006-09-27 12:09:38
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004-2006
// All rights reserved.
// ===========================================================================

#include "RezillaConstants.h"
#include "CRezillaApp.h"
#include "CRezObj.h"
#include "CRezMap.h"
#include "UIconMisc.h"
#include "UResourceMgr.h"
#include "UResources.h"
#include "UColorUtils.h"

#include <stdio.h>


// ---------------------------------------------------------------------------
// 	GetDefaultBitmap
// ---------------------------------------------------------------------------
// Get an empty default (blank) icon. Note that inType is not necessarily 
// the same as the type of inResObj. 

OSErr
UIconMisc::GetDefaultBitmap(CRezObj * inResObj, ResType inType)
{	
	OSErr	error;
	if ( inResObj ) {
		Handle	theHandle = NULL;
		
		error = UResources::GetResourceInMap( CRezillaApp::GetSelfRefNum(), inType, IconEditor_EmptyDefaults, theHandle, true );
		
		if (error == noErr && theHandle != NULL) {
			::DetachResource(theHandle);
			inResObj->SetData(theHandle);
			::DisposeHandle(theHandle);
		} 
	}
	return error;
}


// ---------------------------------------------------------------------------
// 	GetBitmapResource
// ---------------------------------------------------------------------------
// This will try to find a bitmap resource in a rez map. It the resource 
// has no data (null data size), it means that it is a newly created bitmap: 
// in that case, return an empty default (blank icon).

CRezObj *
UIconMisc::GetBitmapResource(CRezMap *inMap, ResType inType, short inID, 
							  Boolean loadIt)
{
	CRezObj *	theRes = NULL;
	
	theRes = inMap->FindResource( inType, inID, loadIt );
	if ( theRes && theRes->GetSize() == 0 ) {
			GetDefaultBitmap( theRes, inType);
	}
	
	return theRes;
}


// ---------------------------------------------------------------------------
//   GetIconInfoForType										 [static, public]
// ---------------------------------------------------------------------------

void
UIconMisc::GetIconInfoForType(ResType inType, SInt32 &outWidth, SInt32 &outHeight, 
									 SInt32 &outDepth, SInt32 &outRowBytes, SInt32 &outOffset)
{
	switch (inType) {
		case 'icl8':
		outWidth = 32;
		outHeight = 32;
		outDepth = 8;
		outRowBytes = 32;
		outOffset = 0;
		break;

		case 'icl4':
		outWidth = 32;
		outHeight = 32;
		outDepth = 4;
		outRowBytes = 16;
		outOffset = 0;
		break;

		case 'ICN#':
		outWidth = 32;
		outHeight = 32;
		outDepth = 1;
		outRowBytes = 4;
		outOffset = 128;
		break;

		case 'ics8':
		outWidth = 16;
		outHeight = 16;
		outDepth = 8;
		outRowBytes = 16;
		outOffset = 0;
		break;

		case 'ics4':
		outWidth = 16;
		outHeight = 16;
		outDepth = 4;
		outRowBytes = 8;
		outOffset = 0;
		break;

		case 'ics#':
		outWidth = 16;
		outHeight = 16;
		outDepth = 1;
		outRowBytes = 2;
		outOffset = 32;
		break;

		case 'icm8':
		outWidth = 16;
		outHeight = 12;
		outDepth = 8;
		outRowBytes = 16;
		outOffset = 0;
		break;

		case 'icm4':
		outWidth = 16;
		outHeight = 12;
		outDepth = 4;
		outRowBytes = 8;
		outOffset = 0;
		break;

		case 'icm#':
		outWidth = 16;
		outHeight = 12;
		outDepth = 1;
		outRowBytes = 2;
		outOffset = 24;
		break;
		
	}
}


// ---------------------------------------------------------------------------
//   GetIconInfoForType										 [static, public]
// ---------------------------------------------------------------------------
// ImgType_Cursor				= FOUR_CHAR_CODE('CURS'),
// ImgType_ColorCursor			= FOUR_CHAR_CODE('crsr')

Boolean
UIconMisc::GetCursorInfoForType(ResType inType, Handle inResHandle, 
								SInt32 &outWidth, SInt32 &outHeight, 
								SInt32 &outDepth, SInt32 &outRowBytes, 
								CTabHandle &outTable, UInt8* &outData)
{
	Boolean gotData = false;
	
	if (inType == ImgType_Cursor) {
		if ( ::GetHandleSize( (Handle) inResHandle) != kBWCursorBytes ) {
			goto done;
		}
		outWidth = kCursorWidth;
		outHeight = kCursorHeight;
		outDepth = 1;
		outRowBytes = kBWCursorRowBytes;
		outTable = NULL;
		outData = (UInt8*) *inResHandle;
		gotData = true;
	} else if (inType == ImgType_ColorCursor) {
		PixMapPtr		cMap;
		CCrsrHandle		h = (CCrsrHandle) inResHandle;
		UInt8			*p;

		// Do some validity check
		p = (UInt8*) *h;
		
		if ( (UInt16) ::CFSwapInt16BigToHost((**h).crsrType) != (UInt16) 0x8001 )
			goto done;
		
		if ( ::GetHandleSize( (Handle) h ) < sizeof(CCrsr) )
			goto done;
	
		// Get some info about the cursor
		cMap = (PixMapPtr) (p + ::CFSwapInt32BigToHost((SInt32) (**h).crsrMap));

		if ( cMap->pixelType != 0 )
			goto done;

		outWidth = ::CFSwapInt16BigToHost(cMap->bounds.right) - ::CFSwapInt16BigToHost(cMap->bounds.left);
		outHeight = ::CFSwapInt16BigToHost(cMap->bounds.bottom) - ::CFSwapInt16BigToHost(cMap->bounds.top);
		outDepth = ::CFSwapInt16BigToHost(cMap->pixelSize);
		outRowBytes = ::CFSwapInt16BigToHost(cMap->rowBytes) & 0x3FFF;
		outData = p + ::CFSwapInt32BigToHost((SInt32) (**h).crsrData);

		if ( (outWidth != kCursorWidth) || (outHeight != kCursorHeight) )
			goto done;
		
		if ( (outDepth != 1) && (outDepth != 2) && (outDepth != 4) && (outDepth != 8) )
			goto done;
		
		if ( cMap->pmTable == 0 ) {
			outTable = UColorUtils::NewColorTableByDepth( outDepth );
		} else {
			outTable = UColorUtils::NewColorTableFromPtr( outDepth, p + ::CFSwapInt32BigToHost((SInt32) cMap->pmTable), true );
		}
		gotData = true;
	} 

done:
	return gotData;
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

		// Set the gdevice to the main device (if it isn't already).
		// The Window Mgr requires this when opening windows etc.
		GDHandle mainDevice = ::GetMainDevice();
		if ( GetGDevice() != mainDevice ) {
			::SetGDevice( mainDevice );
		}

		if ( UQDGlobals::GetCurrentPort() != inPort ) {
			::SetPort( inPort );
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

