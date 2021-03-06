// ===========================================================================
// UIconMisc.h
//                       Created: 2004-12-11 18:52:00
//             Last modification: 2006-09-27 12:08:07
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004-2006
// All rights reserved.
// ===========================================================================

#ifndef _H_UIconMisc
#define _H_UIconMisc
#pragma once

#include "RezillaConstants.h"

class CRezMap;
class CRezObj;

class UIconMisc {
	public:

		static OSErr		GetDefaultBitmap(CRezObj * inResObj, 
											 ResType inType);

		static CRezObj *	GetBitmapResource(CRezMap * inMap, 
											   ResType inType, 
											   short inID, 
											   Boolean loadIt);

		static void			GetIconInfoForType(ResType inType, SInt32 &outWidth, SInt32 &outHeight, 
										 SInt32 &outDepth, SInt32 &outRowBytes, SInt32 &outOffset);

		static Boolean		GetCursorInfoForType(ResType inType, Handle inResHandle, 
								SInt32 &outWidth, SInt32 &outHeight, 
								SInt32 &outDepth, SInt32 &outRowBytes, 
								CTabHandle &outTable, UInt8* &outData);

		static void			GetWindowGlobalBounds( WindowPtr inWindow, Rect & );
		
		//  PowerPlant
		static void			SetPort( GrafPtr );
		static void			SetGWorld( CGrafPtr, GDHandle );
		
		static void			GetMouseRelativeToPort( Point * );
		static void			GetMouseRelativeToView( LPane *, Point * );
		
		static LView*		GetTopView( LPane *inPane );

		static void 		LinkListenerToControls( LListener *, LView *, ResIDT );
		static void			RedrawPaneAsIndicated( LPane *, RedrawOptions );
		
		static GDHandle		FindDeviceViaPoint( Point inGlobalPt );
		static void			ForceRectToScreen( const Rect &inRect, Rect *outRect, GDHandle inScreen = nil );
			
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
