// ===========================================================================
// UIconMisc.h
//                       Created: 2004-12-11 18:52:00
//             Last modification: 2004-12-21 19:14:35
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_UIconMisc
#define _H_UIconMisc
#pragma once

#include "RezillaConstants.h"


class UIconMisc {
	public:

		//  Memory
		static void			ClearMemory( void *, UInt32 inNumBytes );
		static void			SetMemory( void *p, UInt8 toWhat, UInt32 numBytes );
		static Handle		DuplicateHandle( Handle source );
		static void			DisposeHandle( void *h );
		
		//  Mac stuff
		static Boolean		IsShiftKey();
		static Boolean		IsOptionKey();
		static void			GetWindowGlobalBounds( WindowPtr inWindow, Rect & );
		
		//  PowerPlant
		static void			SetPort( GrafPtr );
		static void			SetGWorld( CGrafPtr, GDHandle );
		
		static void			GetMouseRelativeToPort( Point * );
		static void			GetMouseRelativeToView( LPane *, Point * );
		
		static LView*		GetTopView( LPane *inPane );
		static LPane*		FindSiblingPaneByID( LPane *, PaneIDT );

		static void 		LinkListenerToControls( LListener *, LView *, ResIDT );
		static void			RedrawPaneAsIndicated( LPane *, RedrawOptions );
		static LWindow*		CreatePPWindow( ResIDT inWindowID );
		
		static GDHandle		FindDeviceViaPoint( Point inGlobalPt );
		static void			ForceRectToScreen( const Rect &inRect, Rect *outRect, GDHandle inScreen = nil );

// 		//  Regions
// public:
// 		static RgnHandle	NewRegionFromRect( const Rect &r );
// 		static RgnHandle	NewRegionFromRect( SInt32 left, SInt32 top, SInt32 right, SInt32 bottom );
// 		static RgnHandle	NewRegionFromPolygon( PolyHandle inPoly );
// 		static RgnHandle	NewRegionFromRegion( RgnHandle );
// 		static RgnHandle	NewRegion();
// 		static void			DisposeRegion( RgnHandle & );
			
protected:
		static Handle		GetHandleFromClipboard();
};



/*****************
*                *
*   USparePort   *
*                *
*****************/
class USparePort {
	public:
		static GrafPtr	GetSparePort();
		static void		Cleanup();

	protected:
		static GrafPtr		sPortPtr;
		static Boolean		sInitted;
};


/********************
*                   *
*   StGWorldSaver   *
*                   *
********************/
class StGWorldSaver {
	public:
						StGWorldSaver();
						StGWorldSaver( GWorldPtr inWorld );
		virtual			~StGWorldSaver();
		
	protected:
		CGrafPtr		mPort;
		GDHandle		mDevice;
};


/******************
*                 *
*   URegionMisc   *
*                 *
******************/
class URegionMisc {
public:
		static RgnHandle	NewRegionFromRect( const Rect &r );
		static RgnHandle	NewRegionFromRect( SInt32 left, SInt32 top, SInt32 right, SInt32 bottom );
		static RgnHandle	NewRegionFromPolygon( PolyHandle inPoly );
		static RgnHandle	NewRegionFromRegion( RgnHandle );
		static RgnHandle	NewRegion();
		static void			DisposeRegion( RgnHandle & );
};

#endif // _H_UIconMisc
