// ===========================================================================
// CWindow_ColorIcon.cp
//                       Created: 2004-12-11 18:50:11
//             Last modification: 2005-02-06 19:19:45
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CWindow_ColorIcon.h"
#include "CColorTableBuilder.h"
#include "CIcon_EditorWindow.h"
#include "CDraggableTargetView.h"
#include "CRezillaPrefs.h"
#include "CRezObj.h"
#include "CRezMap.h"
#include "COffscreen.h"
#include "RezillaConstants.h"
#include "UColorUtils.h"
#include "UIconMisc.h"
#include "UMiscUtils.h"
#include "UResourceMgr.h"

#include <LStaticText.h>

// ---------------------------------------------------------------------------
// 	OpenPaintWindow
// ---------------------------------------------------------------------------
CWindow_ColorIcon*
CWindow_ColorIcon::OpenPaintWindow( ResIDT inPPobID, CRezMap *inMap, ResIDT inResID )
{
	CWindow_ColorIcon *	theWindow = nil;

	try
	{
		theWindow = (CWindow_ColorIcon*) CIcon_EditorWindow::CreatePaintWindow( inPPobID );
		theWindow->InitializeFromResource( inMap, inResID );
	}
	catch( ... )
	{
		delete theWindow;
		throw;
	}
	
	return( theWindow );
}


// ---------------------------------------------------------------------------
// 	CreatePaintIconStream
// ---------------------------------------------------------------------------
CWindow_ColorIcon *CWindow_ColorIcon::CreatePaintCIconStream( LStream *inStream )
{
	return new CWindow_ColorIcon( inStream );
}


// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------
CWindow_ColorIcon::CWindow_ColorIcon( LStream *inStream ) : CIcon_EditorWindow( inStream )
{
	mColorSample = nil;
	mBWSample = nil;
	mMaskSample = nil;
	mAllowImageResizing = true;
}


// ---------------------------------------------------------------------------
// 	Destructor
// ---------------------------------------------------------------------------
CWindow_ColorIcon::~CWindow_ColorIcon()
{
}


// ---------------------------------------------------------------------------
// 	FinishCreateSelf
// ---------------------------------------------------------------------------
void
CWindow_ColorIcon::FinishCreateSelf()
{
	CIcon_EditorWindow::FinishCreateSelf();

	mColorSample = (CDraggableTargetView*) this->FindPaneByID( ImgType_ColorIcon );
	mBWSample = (CDraggableTargetView*) this->FindPaneByID( ImgType_LargeIcon );
	mMaskSample = (CDraggableTargetView*) this->FindPaneByID( item_IconEditMask );
	ThrowIf_( !mColorSample || !mBWSample || !mMaskSample );

	// Keep track of the sample panes 
	mNumSamplePanes = 3;
	mSamplePaneList[ 0 ] = mColorSample;
	mSamplePaneList[ 1 ] = mBWSample;
	mSamplePaneList[ 2 ] = mMaskSample;

	if ( mSampleWell )
		mSampleWell->GetFrameSize( mInitialSampleWellSize );
	else
	{
		mInitialSampleWellSize.width = 0;
		mInitialSampleWellSize.height = 0;
	}

	// Link the broadcasters
	UReanimator::LinkListenerToBroadcasters( this, this, PPob_CICNEditor );
	// We need to listen to these controls (click and/or drop operations)
	this->BecomeListenerTo( mNumSamplePanes, mSamplePaneList );
}


// ---------------------------------------------------------------------------
// 	InitializeFromResource
// ---------------------------------------------------------------------------
void
CWindow_ColorIcon::InitializeFromResource( CRezMap *inMap, ResIDT inResID )
{
	StGWorldSaver		aSaver;
	StRezRefSaver		aSaver2;
	Boolean				bwIsEmpty;
	
	COffscreen			*colorImage = nil, *bwImage = nil, *maskImage = nil;
	
	this->ParseColorIcon( inMap, inResID, &colorImage, &bwImage, &maskImage, &bwIsEmpty );
	this->InitializeFromBuffers( colorImage, bwImage, maskImage, bwIsEmpty );
}


// ---------------------------------------------------------------------------
// 	InitializeFromBuffers
// ---------------------------------------------------------------------------
// 	This call takes control of all buffers

void
CWindow_ColorIcon::InitializeFromBuffers( COffscreen *colorImage, COffscreen *bwImage, 
										 COffscreen *maskImage, Boolean bwIsEmpty )
{
	try
	{
		// Resize the sample panes if necessary
		SInt32 	iconWidth = colorImage->GetWidth();
		SInt32	iconHeight = colorImage->GetHeight();
		
		// The sample pane PPob's are sized as though the icon was 32x32
		this->ResizeSampleWell( iconWidth, iconHeight );	
		
		// Setup the main image buffers. This may trigger a resize of the
		// canvas, change of window size, etc
		this->SetImage( colorImage, resize_All );

		// Setup the sample buffers. We set the buffer ptr to nil because
		// it doesn't belong to us once the call succeeds.
		mColorSample->SetBuffer( colorImage, redraw_Dont );
		colorImage = nil;
		mColorSample->SetTarget( true, redraw_Dont );
		mCurrentSamplePane = mColorSample;
		
		mBWSample->SetBuffer( bwImage, redraw_Dont );
		bwImage = nil;
		if ( bwIsEmpty )
			mBWSample->SetUsedFlag( false, redraw_Dont );
		
		mMaskSample->SetBuffer( maskImage, redraw_Dont );
		maskImage = nil;
							
	//	this->RedrawSampleView();
	}
	catch( ... )
	{
		delete colorImage;
		delete bwImage;
		delete maskImage;
	}
}


// ---------------------------------------------------------------------------
// 	ParseColorIcon
// ---------------------------------------------------------------------------
void
CWindow_ColorIcon::ParseColorIcon( CRezMap *inMap, ResIDT inResID,
						COffscreen **outColor, COffscreen **outBW, 
						COffscreen **outMask, Boolean *outBWEmpty )
{
	PixMapPtr		cMap;
	BitMapPtr		bwMap, maskMap;
	SInt32			depth, width, height, handleSize;
	UInt8			*sourceData;
	CTabHandle		theTable = nil, oneBitTable = nil;
	COffscreen		*cBuffer = nil, *bwBuffer = nil, *maskBuffer = nil;
	Handle			h = nil;
	CRezObj 		*theRes = nil;

	try
	{
		// Get the raw resource handle
		theRes = inMap->FindResource( ImgType_ColorIcon, inResID, true );
		ThrowIfNil_( theRes );
		h = theRes->GetData();
		ThrowIfNil_( h );
		::HLock( h );
		
		handleSize = ::GetHandleSize( h );
		if ( handleSize < sizeof(PixMap) + 2 * sizeof(BitMap) )
			Throw_( err_IconCorruptedResource );
		
		// Get some info about the icon
		cMap = (PixMapPtr) *h;
		maskMap = (BitMap*)( *h + sizeof(PixMap) );
		bwMap = (BitMap*)( *h + sizeof(PixMap) + sizeof(BitMap) );
		
		depth = cMap->pixelSize;
		this->ThrowIfInvalidDepth( depth );

		width = cMap->bounds.right - cMap->bounds.left;
		height = cMap->bounds.bottom - cMap->bounds.top;
		if ( (width < this->GetMinImageWidth()) 
			|| (width > this->GetMaxImageWidth()) 
			|| (height < this->GetMinImageHeight()) 
			|| (height > this->GetMaxImageHeight()) ) 
				Throw_( err_IconInvalidImageSize );

		// This isn't really necessary, but it can't hurt to check
		if ( (width != maskMap->bounds.right - maskMap->bounds.left) 
			|| (height != maskMap->bounds.bottom - maskMap->bounds.top) 
			|| (width != bwMap->bounds.right - bwMap->bounds.left) 
			|| (height != bwMap->bounds.bottom - bwMap->bounds.top) )
			Throw_( err_IconCorruptedResource );
		
		// Allocate the mask
		sourceData = (UInt8*)( *h + sizeof(PixMap) + 2 * sizeof(BitMap) + sizeof(SInt32) );
		maskBuffer = COffscreen::CreateBuffer( width, height, 1 );
		if ( maskMap->rowBytes != 0 )
		{
			maskBuffer->CopyFromRawData( sourceData, maskMap->rowBytes );
			sourceData += maskMap->rowBytes * height;
		}
		
		// Allocate the bw bitmap
		bwBuffer = COffscreen::CreateBuffer( width, height, 1 );
		if ( bwMap->rowBytes != 0 )
		{
			bwBuffer->CopyFromRawData( sourceData, bwMap->rowBytes );
			sourceData += bwMap->rowBytes * height;
			*outBWEmpty = false;
		}
		else
			*outBWEmpty = true;
		
		// Allocate the color table. note that the resource may have a
		// minimal color table and QuickDraw doesn't work with anything but
		// a full-sized one.
		theTable = UColorUtils::NewColorTableFromPtr( depth, sourceData );
		sourceData += sizeof(ColorTable) + (((CTabPtr)sourceData)->ctSize) * sizeof(ColorSpec);
		
		// Allocate the color bitmap
		cBuffer = COffscreen::CreateBuffer( width, height, depth, theTable );
		SInt32	rowBytes = cMap->rowBytes & 0x3FFF;			// clear flag bits
		if ( rowBytes != 0 )
			cBuffer->CopyFromRawData( sourceData, rowBytes );
		
		if ( ! CRezillaPrefs::GetPrefValue(kPref_editors_use8BitIcons) )
		{
			COffscreen *directBuffer = COffscreen::CreateBuffer( width, height, 32 );
			directBuffer->CopyFrom( cBuffer );
			
			delete cBuffer;
			cBuffer = directBuffer;
		}

		delete theRes;
	}
	catch( ... )
	{
		if ( theRes ) delete( theRes );
		if ( maskBuffer ) delete( maskBuffer );
		if ( bwBuffer ) delete( bwBuffer );
		if ( cBuffer ) delete( cBuffer );
		if ( theTable ) ::DisposeCTable( theTable );
		( h );
		throw;
	}
	
	// Return buffers to caller
	*outColor = cBuffer;
	*outBW = bwBuffer;
	*outMask = maskBuffer;
	
	// Don't need the color table because the offscreen makes a copy of it
	if ( theTable ) ::DisposeCTable( theTable );
	( h );
}



// ---------------------------------------------------------------------------
// 	SaveAsResource
// ---------------------------------------------------------------------------

void
CWindow_ColorIcon::SaveAsResource( CRezMap *inMap, ResIDT inResID )
{
	ThrowIf_( !mColorSample || !mBWSample || !mMaskSample );
	
	CRezObj 	*theRes = nil;
	COffscreen	*colorBuffer = mColorSample->GetBuffer();
	COffscreen	*bwBuffer = mBWSample->GetBuffer();
	COffscreen	*maskBuffer = mMaskSample->GetBuffer();
	ThrowIf_( !colorBuffer || !bwBuffer || !maskBuffer );

	Handle	h = this->CreateColorIcon( 
					colorBuffer, 
					mBWSample->IsUsed() ? bwBuffer : nil, 
					maskBuffer );
	
	try
	{
		theRes = inMap->FindResource( ImgType_ColorIcon, inResID, 
													false /* loadIt */, 
													true  /* createIt */ );
		ThrowIfNil_( theRes );
		theRes->SetData( h );
		
		delete theRes;
	}
	catch( ... )
	{
		if ( theRes ) delete( theRes );
		( h );
		throw;
	}
	
	this->SetDirty( false );
	( h );
}


// ---------------------------------------------------------------------------
// 	CreateColorIcon
// ---------------------------------------------------------------------------
// Given 3 offscreen buffers (color, bw, and mask), this routine creates a
// block of memory in the same form as a 'cicn' resource. The color image
// will be downsampled to 8-bit if necessary.
// 		
// See IM V-80 for more details on the resource format.
// The format of a cicn is:
// 		Color PixMap
// 		Mask BitMap
// 		BW BitMap
// 		4-byte reserved field
// 		[mask pixel data]
// 		[bw pixel data (optional)]
// 		[color table]
// 		[color pixel data]

Handle
CWindow_ColorIcon::CreateColorIcon( COffscreen *inColor, COffscreen *inBW, 
										COffscreen *inMask )
{
	Handle			h = nil;						// the handle we're returning
	CTabHandle		theTable = nil;					// the color table for the output cicn
	Boolean			deleteBuffer = false;

	try
	{		
		// Downsample the source buffer to 8 bits or less because cicn's
		// can't be 16 or 32-bits.
		if ( inColor->GetDepth() >= 16 )
		{
			inColor = CColorTableBuilder::DownSampleBuffer( 
											inColor, 
											8,				// max depth
											false, 			// don't force b&w into table
											true, 			// minimize table
											true );			// use larger inverse table
			ThrowIfNil_( inColor );					// shouldn't happen
			deleteBuffer = true;					// since we created it
		}

		theTable = inColor->GetColorTable();

		SInt32		width = inColor->GetWidth();
		SInt32		height = inColor->GetHeight();
		SInt32		depth = inColor->GetDepth();
		SInt32 		colorTableBytes = ::GetHandleSize( (Handle) theTable );
		
		Rect		r;
		SetRect( &r, 0, 0, width, height );

		// Gather up information on the color icon portion. Note that the
		// output rowBytes is probably less than the buffer's since ColorQD
		// likes to pad ram buffers by several bytes per row.
		PixMap		colorMap;
		SInt32		colorRowBytes = UColorUtils::CalcRowBytes( width, depth );
		SInt32		colorBytes = colorRowBytes * height;		
		
		colorMap.baseAddr = nil;
		colorMap.rowBytes = colorRowBytes | 0x8000;		// hi bit -> pixmap, not bitmap
		colorMap.bounds = r;
		colorMap.pmVersion = 0;
		colorMap.packType = 0;
		colorMap.packSize = 0;
		colorMap.hRes = 0x00480000;						// 72 dpi
		colorMap.vRes = 0x00480000;
		colorMap.pixelType = chunky;
		colorMap.pixelSize = depth;
		colorMap.cmpCount = 1;
		colorMap.cmpSize = depth;
		colorMap.pixelFormat = k32RGBAPixelFormat;		// Not sure: cf values in QuickDraw.h
		colorMap.pmTable = 0;
		colorMap.pmExt = NULL;
		
		// Gather up information on the mask portion
		BitMap	maskMap;	
		SInt32	maskRowBytes = UColorUtils::CalcRowBytes( width, 1 );
		SInt32	maskBytes = maskRowBytes * height;

		maskMap.rowBytes = maskRowBytes;
		maskMap.bounds = r;
		maskMap.baseAddr = nil;
		
		// Gather up information on the BW icon portion (if the image is
		// entirely white, save space by not storing this)
		BitMap	bwMap;	
		SInt32	bwRowBytes = inBW ? maskRowBytes : 0;		// may be deleted
		SInt32	bwBytes = bwRowBytes * height;

		bwMap.baseAddr = nil;
		bwMap.bounds = r;
		bwMap.rowBytes = bwRowBytes;

		
		// Build the cicn resource
		SInt32 totalBytes = 	sizeof(PixMap) + 2 * sizeof(BitMap) +
							sizeof(SInt32) + maskBytes + bwBytes + 
							colorTableBytes + colorBytes;
		
		h = ::NewHandleClear( totalBytes );
		ThrowIfMemFail_( h );

		::HLock( h );
		UInt8	*p = (UInt8*) *h;
		
		// Put the PixMap, Mask BitMap, and BW BitMap into the block
		BlockMoveData( &colorMap, p, sizeof(colorMap) );
		p += sizeof( colorMap );
		
		BlockMoveData( &maskMap, p, sizeof(maskMap) );
		p += sizeof( maskMap );
		
		BlockMoveData( &bwMap, p, sizeof(bwMap) );
		p += sizeof( bwMap ) + sizeof(SInt32);			// past reserved field too
		
		// Put the raw image data from the mask and bw icon into the block
		inMask->CopyToRawData( p, maskRowBytes );
		p += maskBytes;
		
		if ( bwBytes != 0 )
		{
			inBW->CopyToRawData( p, bwRowBytes );
			p += bwBytes;
		}

		// Put the color table and raw color pixels into the block
		if ( colorTableBytes > 0 )
		{
			BlockMoveData( *theTable, p, colorTableBytes );
			p += colorTableBytes;
		}

		inColor->CopyToRawData( p, colorRowBytes );
			
		// Return the now-completed color icon
		::HUnlock( h );
		
	}
	catch( ... )
	{
		if ( deleteBuffer && inColor )
			delete( inColor );
	
		if ( h ) ::DisposeHandle( h );
		throw;
	}
	
	return( h );
}



// ---------------------------------------------------------------------------
// 	ResizeSampleWell
// ---------------------------------------------------------------------------
void
CWindow_ColorIcon::ResizeSampleWell( SInt32 inIconWidth, SInt32 inIconHeight )
{
	SDimension16	initialSampleSize;
	SDimension16	minSampleSize;
	SInt32			dh = inIconWidth - 32;		// since samples are sized for 32x32 initially
	SInt32			dv = inIconHeight - 32;
	LStaticText *	theLabel;

	mColorSample->GetInitialPaneSize( &initialSampleSize );
	mColorSample->GetMinPaneSize( &minSampleSize );

	// Sample panes grow in a 1:1 ratio with the icon, but never grow
	// smaller than a certain size.
	SInt32 			newPaneWidth = MAX( minSampleSize.width, initialSampleSize.width + dh );
	SInt32			newPaneHeight = MAX( minSampleSize.height, initialSampleSize.height + dv );
	
	mColorSample->ResizeFrameTo( newPaneWidth, newPaneHeight, true );
	mBWSample->ResizeFrameTo( newPaneWidth, newPaneHeight, true );
	mMaskSample->ResizeFrameTo( newPaneWidth, newPaneHeight, true );
	
	// The b&w and mask panes must be moved down so things don't overlap
	SPoint32		initialLoc, currentLoc;
	
	// Otherwise boxes overlap...
	if ( dv < -16 )
		dv = -16;
		
	// Otherwise the right side gets cutoff on small cicns
	if ( dh < -16 )
		dh = -16;
	
	mBWSample->GetInitialPaneLocation( &initialLoc );
	mBWSample->GetFrameLocation( currentLoc );
	mBWSample->MoveBy( 0, initialLoc.v + dv - currentLoc.v, true );
	
	mMaskSample->GetInitialPaneLocation( &initialLoc );
	mMaskSample->GetFrameLocation( currentLoc );
	mMaskSample->MoveBy( 0, initialLoc.v + 2 * dv - currentLoc.v, true );

	// Move the three labels too
	theLabel = dynamic_cast<LStaticText *> (this->FindPaneByID( item_IconLabelName1 ));
	if (theLabel) {
		theLabel->MoveBy( 0, initialLoc.v + 2 * dv - currentLoc.v, true );
	} 

	theLabel = dynamic_cast<LStaticText *> (this->FindPaneByID( item_IconLabelName2 ));
	if (theLabel) {
		theLabel->MoveBy( 0, initialLoc.v + 2 * dv - currentLoc.v, true );
	} 

	theLabel = dynamic_cast<LStaticText *> (this->FindPaneByID( item_IconLabelName3 ));
	if (theLabel) {
		theLabel->MoveBy( 0, initialLoc.v + 2 * dv - currentLoc.v, true );
	} 
	
	// The sample well contains all three sample icons (color, bw, mask)
	// and needs to be resized accordingly. Never allow it to get tiny or
	// things may get cut-off. The numbers should probably be read from a
	// resource.
	if ( mSampleWell )
		mSampleWell->ResizeFrameTo( MAX( 50, mInitialSampleWellSize.width + dh ),
									MAX( 140, mInitialSampleWellSize.height + 3 * dv),
									true );
}


// ---------------------------------------------------------------------------
// 	ChangeImageSize
// ---------------------------------------------------------------------------
// 	Affects all three buffers: color, bw, mask

void
CWindow_ColorIcon::ChangeImageSize( SInt32 inWidth, SInt32 inHeight, Boolean inStretch )
{
	ThrowIf_( (inWidth < mMinImageWidth) || (inHeight < mMinImageHeight) );
	ThrowIf_( (inWidth > mMaxImageWidth) || (inHeight > mMaxImageHeight) );
	ThrowIf_( !mColorSample || !mBWSample || !mMaskSample );
	ThrowIfNil_( mCurrentImage );
	
	SInt32			oldWidth = mCurrentImage->GetWidth();
	SInt32			oldHeight = mCurrentImage->GetHeight();
	Boolean			changedSize = true;
	Rect			destR;

	COffscreen		*newColor = nil, *newBW = nil, *newMask = nil;
		
	try
	{
		// Either stretch the image or put it at the top/left of the destination
		if ( inStretch )
			::SetRect( &destR, 0, 0, inWidth, inHeight );
		else
			::SetRect( &destR, 0, 0, mCurrentImage->GetWidth(), mCurrentImage->GetHeight() );
		
		// Create new buffers for the 3 sample panes
		newColor = mColorSample->GetBuffer()->CreateSimilarOffscreen( false, inWidth, inHeight );
		newColor->CopyFrom( mColorSample->GetBuffer(), &destR );
			
		newBW = COffscreen::CreateBuffer( inWidth, inHeight, 1 );
		newBW->CopyFrom( mBWSample->GetBuffer(), &destR );
		
		newMask = COffscreen::CreateBuffer( inWidth, inHeight, 1 );
		newMask->CopyFrom( mMaskSample->GetBuffer(), &destR );

		// Resize the sample panes
		this->ResizeSampleWell( inWidth, inHeight );
		changedSize = true;
		
		// Set the current buffer -- this can trigger all sorts of things
		// (canvas resize, etc)
		COffscreen *newBuffer;
		CDraggableTargetView *curTarget = this->GetTargetView();
		if ( curTarget == mColorSample )
			newBuffer = newColor;
		else if ( curTarget == mBWSample )
			newBuffer = newBW;
		else
			newBuffer = newMask;
			
		this->SetImage( newBuffer, resize_All, redraw_Later );
		
		// Change the sample panes' buffers.
		// (1) The sample panes will own the buffer after the call (don't
		//    delete them)
		// (2) The previous sample pane buffer will be saved away by the
		//     CIconViewResizer object
		mColorSample->SetRawBuffer( newColor );
		mBWSample->SetRawBuffer( newBW );
		mMaskSample->SetRawBuffer( newMask );
	}
	catch( ... )
	{
		if ( changedSize )
			this->ResizeSampleWell( oldWidth, oldHeight );
	
		delete newColor;
		delete newBW;
		delete newMask;
		throw;
	}
}
