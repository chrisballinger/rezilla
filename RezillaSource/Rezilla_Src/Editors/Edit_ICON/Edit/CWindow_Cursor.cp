// ===========================================================================
// CWindow_Cursor.cp
//                       Created: 2004-12-11 18:50:15
//             Last modification: 2004-12-30 09:44:07
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
// 	Cursor structure is:
// 		BW Image Bits (16 bits per row x 16 rows = 32 bytes)
// 		Mask Image Bits (same)
// 		HotSpot (Point)
// 		
// 	Color cursor structure: (see also IM V-78):
// 		CCrsr structure (see Quickdraw.h)
// 		PixMap
// 		Color Pixel Data
// 		Color Table Data
// ===========================================================================

#include "CWindow_Cursor.h"
#include "CColorTableBuilder.h"
#include "CDraggableTargetView.h"
#include "CIconActions.h"
#include "CIcon_EditorView.h"
#include "CIcon_EditorWindow.h"
#include "CRezObj.h"
#include "CRezMap.h"
#include "COffscreen.h"
#include "RezillaConstants.h"
#include "UColorUtils.h"
#include "UIconMisc.h"
#include "UResourceMgr.h"


// ---------------------------------------------------------------------------
// 	OpenPaintWindow
// ---------------------------------------------------------------------------
CWindow_Cursor*
CWindow_Cursor::OpenPaintWindow( ResIDT inPPobID, CRezMap *inMap, ResType inResType, ResIDT inResID )
{
	CWindow_Cursor *	theWindow = nil;

	try
	{
		theWindow = (CWindow_Cursor*) CIcon_EditorWindow::CreatePaintWindow( inPPobID );
		theWindow->InitializeFromResource( inMap, inResType, inResID );
	}
	catch( ... )
	{
		delete theWindow;
		throw;
	}
	
	return( theWindow );
}


// ---------------------------------------------------------------------------
// 	CreateFromStream
// ---------------------------------------------------------------------------
CWindow_Cursor *CWindow_Cursor::CreateFromStream( LStream *inStream )
{
	return new CWindow_Cursor( inStream );
}


// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------
CWindow_Cursor::CWindow_Cursor( LStream *inStream ) : CIcon_EditorWindow( inStream )
{
	mColorSample = nil;
	mBWSample = nil;
	mMaskSample = nil;
	mResourceType = 0;
	mPrefersIconColors = false;
}


// ---------------------------------------------------------------------------
// 	Destructor
// ---------------------------------------------------------------------------
CWindow_Cursor::~CWindow_Cursor()
{
}


// ---------------------------------------------------------------------------
// 	FinishCreateSelf
// ---------------------------------------------------------------------------
void
CWindow_Cursor::FinishCreateSelf()
{
	CIcon_EditorWindow::FinishCreateSelf();

	// crsr - has mColorSample, mBWSample, mMaskSample
	// CURS - has mBWSample & mMaskSample
	mColorSample = (CDraggableTargetView*) this->FindPaneByID( ImgType_ColorCursor );
	mBWSample = (CDraggableTargetView*) this->FindPaneByID( ImgType_Cursor );
	mMaskSample = (CDraggableTargetView*) this->FindPaneByID( item_IconEditMask );

	ThrowIfNil_( mBWSample );
	ThrowIfNil_( mMaskSample );

	// Keep track of the sample panes
	mNumSamplePanes = 0;
	if ( mColorSample )
		mSamplePaneList[ mNumSamplePanes++ ] = mColorSample;
	mSamplePaneList[ mNumSamplePanes++ ] = mBWSample;
	mSamplePaneList[ mNumSamplePanes++ ] = mMaskSample;

	// We need to listen to the sample panes (click and/or drop operations)
	this->BecomeListenerTo( mNumSamplePanes, mSamplePaneList );
}


// ---------------------------------------------------------------------------
// 	Initialize
// ---------------------------------------------------------------------------
void
CWindow_Cursor::InitializeFromResource( CRezMap *inMap, ResType inResType, ResIDT inResID )
{
	StGWorldSaver		aSaver;
	StRezRefSaver		aSaver2;

	COffscreen			*colorImage = nil, *bwImage = nil, *maskImage = nil;
	Point				theHotSpot;
	
	switch( inResType )
	{
		case ImgType_Cursor:
			this->ParseBWCursor( inMap, inResID, &bwImage, &maskImage, &theHotSpot );
			mResourceType = inResType;
			break;
			
		case ImgType_ColorCursor:
			this->ParseColorCursor( inMap, inResID, &colorImage, &bwImage, &maskImage, &theHotSpot );
			mResourceType = inResType;
			ThrowIfNil_( mColorSample );
			break;
			
		default:
			throw( err_IconInvalidImageFormat );
			break;
	}
	
	try
	{
		mCanvas->SetHotSpot( theHotSpot );
	
		// Set the image for the paint view. If we don't have a color one,
		// use the b&w.
		if ( colorImage )
		{
			this->SetImage( colorImage, resize_All );
			mCurrentSamplePane = mColorSample;
			mColorSample->SetTarget( true, redraw_Dont );
		}
		else
		{
			this->SetImage( bwImage, resize_All );
			mCurrentSamplePane = mBWSample;
			mBWSample->SetTarget( true, redraw_Dont );
			mBWSample->SetUsedFlag( true, redraw_Dont );
		}
	}
	catch( ... )
	{
		delete colorImage;
		delete bwImage;
		delete maskImage;
		throw;
	}

	// Give each of the sample panes their image
	if ( mColorSample && colorImage )
		mColorSample->SetBuffer( colorImage, redraw_Dont );
	mBWSample->SetBuffer( bwImage, redraw_Dont );
	mMaskSample->SetBuffer( maskImage, redraw_Dont );	

	// Need to redraw the sample view (if we've already been initted anyway)
	this->RedrawSampleView();
}



// ---------------------------------------------------------------------------
// 	ParseBWCursor
// ---------------------------------------------------------------------------
void
CWindow_Cursor::ParseBWCursor( CRezMap *inMap, ResIDT inResID,
						COffscreen **outBW, COffscreen **outMask, 
						Point *outHotSpot )
{
	CursHandle		h = nil;
	COffscreen		*bw = nil, *mask = nil;
	
	try
	{
		// Get the raw resource handle
		CRezObj * theRes = inMap->FindResource( ImgType_Cursor, inResID, false );
		ThrowIfNil_( theRes );
		h = (CursHandle) theRes->GetData();
		ThrowIfNil_( h );
		::HLock( (Handle) h );

		// 2 rowBytes x 16 rows x 2 images + sizeof(Point)
		if ( ::GetHandleSize( (Handle) h ) != kBWCursorBytes )
			throw( err_IconCorruptedResource );
		
		// Create the bw bitmap
		bw = COffscreen::CreateBuffer( kCursorWidth, kCursorHeight, 1 );
		ThrowIfMemFail_( bw );
		//bw->AssignPalette( oneBitTable );
		bw->CopyFromRawData( (UInt8*) &(**h).data, kBWCursorRowBytes );

		// Create the mask bitmap
		mask = COffscreen::CreateBuffer( kCursorWidth, kCursorHeight, 1 );
		ThrowIfMemFail_( bw );
		mask->CopyFromRawData( (UInt8*) &(**h).mask, kBWCursorRowBytes );

		// Return stuff to the caller
		*outBW = bw;
		*outMask = mask;
		*outHotSpot = (**h).hotSpot;
	}
	catch( ... )
	{
		UIconMisc::DisposeHandle( h );
		if ( bw ) delete ( bw );
		if ( mask ) delete( mask );
		throw;
	}
	
	UIconMisc::DisposeHandle( h );
}



// ---------------------------------------------------------------------------
// 	ParseColorCursor
// ---------------------------------------------------------------------------
// 	See description of CCrsr structure above.

void
CWindow_Cursor::ParseColorCursor( CRezMap *inMap, ResIDT inResID,
						COffscreen **outColor, COffscreen **outBW, 
						COffscreen **outMask, Point *outHotSpot )
{
	PixMapPtr		cMap;
	SInt32			depth, width, height;
	CTabHandle		theTable = nil, oneBitTable = nil;
	COffscreen		*cBuffer = nil, *bwBuffer = nil, *maskBuffer = nil, *tempBuffer = nil;
	CCrsrHandle		h = nil;
	UInt8			*p;
	
	try
	{
		// Get the raw resource handle. This isn't the usual way of loading
		// color cursors, so the fields will be raw and not filled in (as
		// when GetCCursor is used).
		CRezObj * theRes = inMap->FindResource( ImgType_ColorCursor, inResID, false );
		ThrowIfNil_( theRes );
		h = (CCrsrHandle) theRes->GetData();
		ThrowIfNil_( h );
		::HLock( (Handle) h );
		p = (UInt8*) *h;
		
				// validate the handle a little bit

		if ( (UInt16) (**h).crsrType != (UInt16) 0x8001 )	// cast *is* needed - crsrType is signed
			throw( err_IconInvalidImageFormat );
		
		if ( ::GetHandleSize( (Handle) h ) < sizeof(CCrsr) )
			throw( err_IconCorruptedResource );
	
				// get some info about the cursor

		cMap = (PixMapPtr) (p + (SInt32) (**h).crsrMap);

		if ( cMap->pixelType != 0 )
			throw( err_IconInvalidImageFormat );

		width = cMap->bounds.right - cMap->bounds.left;
		height = cMap->bounds.bottom - cMap->bounds.top;
		depth = cMap->pixelSize;
		
		if ( (width != kCursorWidth) || (height != kCursorHeight) )
			throw( err_IconInvalidImageSize );
		
		if ( (depth != 1) && (depth != 2) && (depth != 4) && (depth != 8) )
			throw( err_IconInvalidImageDepth );
		
				// create the bwBuffer and maskBuffer

		bwBuffer = COffscreen::CreateBuffer( kCursorWidth, kCursorHeight, 1 );
		ThrowIfMemFail_( bwBuffer );
		bwBuffer->CopyFromRawData( (UInt8*) &(**h).crsr1Data, kBWCursorRowBytes );

		maskBuffer = COffscreen::CreateBuffer( kCursorWidth, kCursorHeight, 1 );
		ThrowIfMemFail_( maskBuffer );
		maskBuffer->CopyFromRawData( (UInt8*) &(**h).crsrMask, kBWCursorRowBytes );

				// allocate the color table. note that the resource may have a minimal
		// color table and QuickDraw doesn't work with anything but a full-sized one.

		if ( cMap->pmTable == 0 )			// probably won't happen, but can't hurt to check
			theTable = UColorUtils::NewColorTableByDepth( depth );
		else
			theTable = UColorUtils::NewColorTableFromPtr( depth, p + (SInt32) cMap->pmTable );
				
				// allocate the color bitmap

		tempBuffer = COffscreen::CreateBuffer( width, height, depth, theTable );
		SInt32	rowBytes = cMap->rowBytes & 0x3FFF;			// clear flag bits
		if ( rowBytes != 0 )
			tempBuffer->CopyFromRawData( p + (SInt32) (**h).crsrData, rowBytes );

				// now switch it to a 32-bit offscreen

		cBuffer = COffscreen::CreateBuffer( width, height, 32 );
		cBuffer->CopyFrom( tempBuffer );
	}
	catch( ... )
	{
		delete maskBuffer;
		delete bwBuffer;
		delete cBuffer;
		delete tempBuffer;
		if ( theTable ) ::DisposeCTable( theTable );
		UIconMisc::DisposeHandle( h );
	}
	
		// return buffers and info to the caller
	*outColor = cBuffer;
	*outBW = bwBuffer;
	*outMask = maskBuffer;
	*outHotSpot = (**h).crsrHotSpot;

		// don't need the color table because the offscreen makes a copy of it
	if ( theTable ) ::DisposeCTable( theTable );
	UIconMisc::DisposeHandle( h );
	delete tempBuffer;
}


// ---------------------------------------------------------------------------
// 	SaveAsResource
// ---------------------------------------------------------------------------
void
CWindow_Cursor::SaveAsResource( CRezMap *inMap, ResIDT inResID )
{
	Handle		h = nil;
	
	ThrowIf_( !mBWSample || !mMaskSample );
	COffscreen	*bwBuffer = mBWSample->GetBuffer();
	COffscreen	*maskBuffer = mMaskSample->GetBuffer();

	Point	theHotSpot = mCanvas->GetHotSpot();
	
	try
	{
		switch( mResourceType )
		{
			case ImgType_Cursor:
				h = this->CreateBWCursor( bwBuffer, maskBuffer, theHotSpot );
				break;
			
			case ImgType_ColorCursor:
				ThrowIfNil_( mColorSample );
				h = this->CreateColorCursor( mColorSample->GetBuffer(), bwBuffer, maskBuffer, theHotSpot );
				break;
			
			default:
				throw( err_IconInvalidImageFormat );
		}

		CRezObj * theResource = inMap->FindResource( mResourceType, inResID, true );
		ThrowIfNil_( theResource );
		theResource->SetData( h );
	}
	catch( ... )
	{
		UIconMisc::DisposeHandle( h );
		throw;
	}
	
	this->SetChangedFlag( false );
	UIconMisc::DisposeHandle( h );
}


// ---------------------------------------------------------------------------
// 	CreateBWCursor
// ---------------------------------------------------------------------------
Handle
CWindow_Cursor::CreateBWCursor( COffscreen *inImage, COffscreen *inMask, Point inHotSpot )
{
	CursHandle	h = (CursHandle) ::NewHandleClear( kBWCursorBytes );
	ThrowIfMemFail_( h );
	StHandleLocker	lock1( (Handle) h );
	
	if ( inImage )
		inImage->CopyToRawData( (UInt8*) &(**h).data, kBWCursorRowBytes );
		
	if ( inMask )
		inMask->CopyToRawData( (UInt8*) &(**h).mask, kBWCursorRowBytes );
		
	(**h).hotSpot = inHotSpot;
	return( (Handle) h );
}


// ---------------------------------------------------------------------------
// 	CreateColorCursor
// 	
// 	Note:
// 	See description of CCrsr structure above.
// ---------------------------------------------------------------------------
Handle
CWindow_Cursor::CreateColorCursor( COffscreen *inColor, COffscreen *inBW, 
										COffscreen *inMask, Point inHotSpot )
{
	Handle			h = nil;
	COffscreen		*downSampledBuffer = nil;
	Boolean			deleteBuffer = false;
	
	ThrowIf_( !inColor || !inBW || !inMask );
	
	try
	{
				// downsample the color buffer to a more reasonable depth

		if ( inColor->GetDepth() >= 16 )
		{
			inColor = CColorTableBuilder::DownSampleBuffer( 
											inColor, 
											8,				// max depth
											false, 			// don't force b&w into table
											true, 			// minimize table
											true );			// use larger inverse table
			ThrowIfNil_( inColor );							// shouldn't happen
			deleteBuffer = true;							// since we created it
		}
	
				// Get the color table from the color buffer

		CTabHandle	sourceTable = inColor->GetColorTable();
		ThrowIfNil_( sourceTable );
		SInt32		colorTableBytes = ::GetHandleSize( (Handle) sourceTable );
		
				// do some calculations

		SInt32		depth = inColor->GetDepth();
		SInt32		pixelRowBytes = UColorUtils::CalcRowBytes( kCursorWidth, depth );
		SInt32		pixelBytes = pixelRowBytes * kCursorHeight;
		SInt32		totalBytes = sizeof( CCrsr) + sizeof( PixMap ) + colorTableBytes + pixelBytes;

		SInt32		offsetToPixmap = sizeof(CCrsr);
		SInt32		offsetToPixelData = sizeof(CCrsr) + sizeof(PixMap);
		SInt32		offsetToColorTable = sizeof(CCrsr) + sizeof(PixMap) + pixelBytes;
		
				// Allocate the cursor

		h = ::NewHandleClear( totalBytes ); 
		ThrowIfMemFail_( h );
		::HLock( h );
		
		CCrsr 	*p = (CCrsr *) *h;
		PixMap 	*theMap = (PixMap*) (*h + offsetToPixmap);
		
				// Fill up the structure (note: fields are already zeroed)

		p->crsrType = 0x8001;						// magic number for cursors
		p->crsrMap = (PixMapHandle) offsetToPixmap;
		p->crsrData = (Handle) offsetToPixelData;
		
		inBW->CopyToRawData( (UInt8*) &p->crsr1Data, kBWCursorRowBytes );
		inMask->CopyToRawData( (UInt8*) &p->crsrMask, kBWCursorRowBytes );
		p->crsrHotSpot = inHotSpot;
		
		theMap->rowBytes = 0x8000 + pixelRowBytes;
		::SetRect( &theMap->bounds, 0, 0, kCursorWidth, kCursorHeight );
		theMap->hRes = 0x00480000;
		theMap->vRes = 0x00480000;
		theMap->pixelSize = depth;
		theMap->cmpCount = 1;
		theMap->cmpSize = depth;
		theMap->pmTable = (CTabHandle) offsetToColorTable;

		inColor->CopyToRawData( (UInt8*)( *h + offsetToPixelData ), pixelRowBytes );
		
		CTabPtr	destTable = (CTabPtr) (*h + offsetToColorTable);
		BlockMoveData( *sourceTable, destTable, colorTableBytes );
		destTable->ctFlags = 0;					// 0 for pixmaps, 0x8000 for devices
	}
	catch( ... )
	{
		if ( deleteBuffer && inColor )
			delete inColor;
		UIconMisc::DisposeHandle( h );
		throw;
	}
	
	if ( deleteBuffer && inColor )
		delete inColor;
	::HUnlock( h );
	return( h );
}



// ---------------------------------------------------------------------------
// 	CopyToUndo
// ---------------------------------------------------------------------------
void
CWindow_Cursor::CopyToUndo()
{
	CIcon_EditorWindow::CopyToUndo();
	mUndoHotSpot = mCanvas->GetHotSpot();
}


// ---------------------------------------------------------------------------
// 	SwapUndoState
// ---------------------------------------------------------------------------
void
CWindow_Cursor::SwapUndoState()
{
	Point	tempPt = mUndoHotSpot;
	
	mUndoHotSpot = mCanvas->GetHotSpot();
	mCanvas->SetHotSpot( tempPt );
	
	CIcon_EditorWindow::SwapUndoState();
}

