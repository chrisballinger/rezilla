// ===========================================================================
// COffscreen.cp
//                       Created: 2004-12-11 18:52:51
//             Last modification: 2005-01-03 06:47:59
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004, 2005
// All rights reserved.
// ===========================================================================

#include "RezillaConstants.h"
#include "COffscreen.h"
#include "UColorUtils.h"
#include "CSharedPalette.h"
#include "UBitUtils.h"
#include "UIconMisc.h"

#include <PictUtils.h>
#include <UDesktop.h>

#include <stdio.h>

// This clears the flag bits in a pixmap's rowBytes field
#define FixRowBytes( rb )	( (rb) & 0x3FFF )

// This is used just for leak detection
SInt32	COffscreen::sNumBuffers = 0;


// ---------------------------------------------------------------------------
// 	CreateBuffer
// ---------------------------------------------------------------------------
// Erases the buffer to white. Caller may dispose of the color table after
// this call, but not the GDevice (if any).

COffscreen *COffscreen::CreateBuffer( SInt32 inWidth, SInt32 inHeight, SInt32 inDepth,
										CTabHandle inTable, GDHandle inDevice, 
										Boolean inKeepLocal )
{
	return new COffscreen( inWidth, inHeight, inDepth, inTable, inDevice, inKeepLocal );
}


// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------

COffscreen::COffscreen( SInt32 inWidth, SInt32 inHeight, SInt32 inDepth,
										CTabHandle inTable, GDHandle inDevice, 
										Boolean inKeepLocal )
{
	mWorld = nil;
	mWidth = inWidth;
	mHeight = inHeight;
	mDepth = inDepth;
	mRowBytes = 0;						// set below
	mRowArray = nil;
	mPixMap = nil;
	mPalette = nil;

	switch( inDepth )
	{
		case 1:		case 16:	case 32:
			mHasDirectPixels = true;
			break;
		
		case 2:		case 4:		case 8:
			mHasDirectPixels = false;
			break;
			
		default:
			throw( paramErr );
	}
	
	// find the getpixel/setpixel functions	for this depth
	UPixelHelper::GetPixelFunctions( inDepth, &mPixelGetter, &mPixelSetter );
	
	try
	{
		mWorld = COffscreen::CreateGWorld( inWidth, inHeight, inDepth, inTable, 
											inDevice, inKeepLocal, &mRowBytes );
		ThrowIfNil_( mWorld );		
		mPixMap = ::GetGWorldPixMap( mWorld );
		
		this->SetupRowArray();
	}
	catch( ... )
	{
		if ( mWorld ) ::DisposeGWorld( mWorld );
		if ( mRowArray ) ::DisposePtr( (Ptr) mRowArray );
		throw;
	}
	
	++sNumBuffers;
}


// ---------------------------------------------------------------------------
// 	SetupRowArray
// ---------------------------------------------------------------------------
// Requires mPixMap, mHeight, and mRowBytes to be correct. Pixmap bits must
// remain locked at all times or these values will be wrong.

void
COffscreen::SetupRowArray()
{
	mRowArray = (RawPtr*) ::NewPtr( sizeof(RawPtr) * mHeight );
	ThrowIfMemFail_( mRowArray );
	
	RawPtr	rowPtr = (RawPtr) ::GetPixBaseAddr( mPixMap );
	for ( SInt32 count = 0; count < mHeight; count++ )
	{
		mRowArray[ count ] = rowPtr;
		rowPtr += mRowBytes;
	}
}


// ---------------------------------------------------------------------------
// 	CreateGWorld
// ---------------------------------------------------------------------------
// Erases the buffer to white. Leaves the pixels locked. The ColorTable is
// copied, so caller can delete it.

GWorldPtr
COffscreen::CreateGWorld( SInt32 inWidth, SInt32 inHeight, SInt32 inDepth,
							CTabHandle inTable, GDHandle inDevice, Boolean inKeepLocal,
							SInt32 *outRowBytes )
{
	ThrowIf_( (inWidth <= 0) || (inHeight <= 0) );

	StGWorldSaver		aSaver;					// save/restore GWorld
	GWorldPtr			theWorld = nil;
	OSErr				err = noErr;
	Rect				r;
	GWorldFlags			flags;
	
	// Set up the variables for the NewGWorld call
	::SetRect( &r, 0, 0, inWidth, inHeight );
	flags = useTempMem | (inDevice ? noNewDevice : 0) | (inKeepLocal ? keepLocal : 0);

	// Allocate the GWorld in multifinder memory. If memory is full, use
	// the current heap instead.
	err = ::NewGWorld( &theWorld, inDepth, &r, inTable, inDevice, flags );
	if ( (err == memFullErr) || (err == cTempMemErr) || (err == cNoMemErr) )
	{
		flags &= ~useTempMem;
		err = ::NewGWorld( &theWorld, inDepth, &r, inTable, inDevice, flags );
	}

	ThrowIfOSErr_( err );
	ThrowIfMemFail_( theWorld );			// shouldn't happen

	// Force the GWorld to white
	PixMapHandle thePixMap = ::GetGWorldPixMap( theWorld );
	Rect theRect;

	::LockPixels( thePixMap );
	::SetGWorld( theWorld, nil );
	::RGBForeColor( &Color_Black );
	::RGBBackColor( &Color_White );
	::EraseRect( GetPortBounds(theWorld, &theRect) );
	
	if ( outRowBytes )
		*outRowBytes = FixRowBytes( (**thePixMap).rowBytes );

			// return the GWorld to the caller

	return( theWorld );
}



// ---------------------------------------------------------------------------
// 	COffscreen											 [destructor]
// ---------------------------------------------------------------------------

COffscreen::~COffscreen()
{
	if ( mRowArray )
	{
		::DisposePtr( (Ptr) mRowArray );
		mRowArray = nil;
	}

	if ( mWorld )
	{
		// Quickdraw isn't smart enough to notice when you destroy the
		// current gworld and it crashes if you do so. We'll prevent this.
		CGrafPtr	theCurrentPort;
		GDHandle	theCurrentDevice;
		LWindow *	theWindow;
		
		::GetGWorld( &theCurrentPort, &theCurrentDevice );
		if ( theCurrentPort == mWorld )
		{
			LView::OutOfFocus( nil );
			
			::SetGDevice( GetMainDevice() );
			
			theWindow = UDesktop::FetchTopRegular();
			if (theWindow) {
				::SetPortWindowPort( theWindow->GetMacWindow() );
			}
		}
	
		// Dispose of the gworld
		::DisposeGWorld( mWorld );
		mWorld = nil;
	}
	
	if ( mPalette )
	{
		mPalette->DecrementRefCount();
		mPalette = nil;
	}
	
	--sNumBuffers;
}


// ---------------------------------------------------------------------------
// 	GetColorTable
// ---------------------------------------------------------------------------

CTabHandle
COffscreen::GetColorTable()
{
	return( (**this->GetPixMap()).pmTable );
}


// ---------------------------------------------------------------------------
// 	GetPixel
// ---------------------------------------------------------------------------
// 	The pixel value can be either an index to a color table (2,4,8 bits)
// 	or a direct color (1,16,32 bits).

Color32
COffscreen::GetPixel( SInt32 h, SInt32 v )
{
	if ( (h < 0) || (h >= mWidth) || (v < 0) || (v >= mHeight) )
		throw( paramErr );
	
	return( this->RawGetPixel( this->RawGetRowPtr(v), h ) );
}


// ---------------------------------------------------------------------------
// 	SetPixel
// ---------------------------------------------------------------------------

void
COffscreen::SetPixel( SInt32 h, SInt32 v, PixelValue inPixel )
{
	if ( (h < 0) || (h >= mWidth) || (v < 0) || (v >= mHeight) )
		throw( paramErr );
	
	this->RawSetPixel( this->RawGetRowPtr(v), h, inPixel );
}


// ---------------------------------------------------------------------------
// 	GetPixelColor
// ---------------------------------------------------------------------------
// This differs from GetPixel() in that GetPixel() returns the value from
// the offscreen, which may be an index to a color, while this function
// converts that index into a real Color32.

Color32
COffscreen::GetPixelColor( SInt32 h, SInt32 v )
{
	return this->PixelValueToColor32( this->GetPixel( h, v ) );
}


// ---------------------------------------------------------------------------
// 	GetPixelRGB
// ---------------------------------------------------------------------------

RGBColor
COffscreen::GetPixelRGB( SInt32 h, SInt32 v )
{
	return this->PixelValueToRGB( this->GetPixel( h, v ) );
}


// ---------------------------------------------------------------------------
// 	RawGetPixelColor
// ---------------------------------------------------------------------------

Color32
COffscreen::RawGetPixelColor( RawPtr inRowPtr, SInt32 h )
{
	PixelValue	thePixel = this->RawGetPixel( inRowPtr, h );
	
	if ( mDepth == 32 )
		return( thePixel );
		
	return( this->PixelValueToColor32( thePixel ) );
}


// ---------------------------------------------------------------------------
// 	RawSetPixelColor
// ---------------------------------------------------------------------------

void
COffscreen::RawSetPixelColor( RawPtr inRowPtr, SInt32 h, Color32 inColor )
{
	if ( mDepth == 32 )
	{
		this->RawSetPixel( inRowPtr, h, inColor );		// already in 32-bit format
	}
	else
	{
		PixelValue thePixel = this->Color32ToPixelValue( inColor );
		this->RawSetPixel( inRowPtr, h, thePixel );
	}
}


// ---------------------------------------------------------------------------
// 	PixelValueToColor32
// ---------------------------------------------------------------------------

Color32
COffscreen::PixelValueToColor32( PixelValue thePixelValue )
{
	if ( mDepth == 32 )
		return( thePixelValue );			// already in the correct format
	
	RGBColor	theColor = this->PixelValueToRGB( thePixelValue );
	return( UColorUtils::RGBToColor32( theColor ) );
}


// ---------------------------------------------------------------------------
// 	Color32ToPixelValue
// ---------------------------------------------------------------------------

PixelValue
COffscreen::Color32ToPixelValue( Color32 theColor32 )
{
	if ( mDepth == 32 )
		return( theColor32 );			// already in the correct format
	
	RGBColor	theRGB = UColorUtils::Color32ToRGB( theColor32 );
	return this->RGBToPixelValue( theRGB );
}


// ---------------------------------------------------------------------------
// 	PixelValueToRGB
// ---------------------------------------------------------------------------
// 	Doesn't check for out-of-bounds conditions.

RGBColor
COffscreen::PixelValueToRGB( PixelValue thePixelValue )
{
	switch( mDepth )
	{
		case 1:
			return thePixelValue ? Color_Black : Color_White;
		case 16:
			return UColorUtils::Color16ToRGB( thePixelValue );
		case 32:
			return UColorUtils::Color32ToRGB( thePixelValue );
		
		default:
			CTabHandle	theTable = this->GetColorTable();
			return( (**theTable).ctTable[ thePixelValue ].rgb );
	}
}


// ---------------------------------------------------------------------------
// 	RGBToPixelValue
// ---------------------------------------------------------------------------
// 	For b&w, everything that's not white becomes black (ie, no luminance
// 	matching).

PixelValue
COffscreen::RGBToPixelValue( const RGBColor &inColor )
{
	/*
		the direct buffers are easiest
	*/
	switch( mDepth )
	{
		case 1:
			return( UColorUtils::EqualRGB(inColor, Color_White) ? 0 : 1 );
			break;
		case 16:
			return UColorUtils::RGBToColor16( inColor );
			break;
		case 32:
			return UColorUtils::RGBToColor32( inColor );
			break;
	}

	// 	For indexed buffers, scan the color table for an exact match first.
	// 	if not found, let Quickdraw use the inverse table and find a close
	// 	match. Inverse tables aren't very accurate at times.
	// 	
	// 	We'll check specifically for black & white first because it's
	// 	possible for them to be in the color table in more than one place.
	// 	We'll return the "preferred" position for each.
	CTabHandle	theTable = this->GetColorTable();
	SInt32		tableEntries = (**theTable).ctSize + 1;
	
	if ( UColorUtils::EqualRGB( inColor, Color_White ) )
		return( 0 );
	
	if ( UColorUtils::EqualRGB( inColor, Color_Black ) )
		return( tableEntries - 1 );
		
	for ( SInt32 count = 0; count < tableEntries; count++ )
	{
		RGBColor	tempColor = (**theTable).ctTable[ count ].rgb;
		if ( UColorUtils::EqualRGB( tempColor, inColor ) )
			return( count );
	}
	
	// Not in the table -- let Quickdraw search
	{
		// Set the GDevice where the inverse table is
		StSaveAndDraw		aSaver( this );
		return( ::Color2Index( &inColor ) );
	}
}


// ---------------------------------------------------------------------------
// 	BeginDrawing
// ---------------------------------------------------------------------------

void
COffscreen::BeginDrawing()
{
	::SetGWorld( mWorld, nil );

	LView::OutOfFocus( nil );
}


// ---------------------------------------------------------------------------
// 	EndDrawing
// ---------------------------------------------------------------------------
// This used to unlock the pixels, but now we leave them locked because
// it's faster and simplifies the code a lot.

void
COffscreen::EndDrawing()
{
}


// ---------------------------------------------------------------------------
// 	CopyTo
// ---------------------------------------------------------------------------
// May change the fore/back color. destR is in port-relative coordinates.

void
COffscreen::CopyTo( GrafPtr inDestPort, const Rect *inDestR, 
						 const Rect *inSourceR, SInt16 inMode, 
						 RgnHandle inMaskRgn )
{
	StGWorldSaver		aSaver;
	const BitMap		*sourceBits, *destBits;
	Rect				sourceR;
	
	ThrowIfNil_( inDestPort );
	
	this->BeginDrawing();
	this->ResetColorsSelf();		// don't want copybits to colorize

	// This forces origin to 0,0, gdevice to main, unclips
	UIconMisc::SetPort( inDestPort );	
	sourceBits = ::GetPortBitMapForCopyBits(mWorld);
	destBits = ::GetPortBitMapForCopyBits(inDestPort);

	if ( inSourceR )
		sourceR = *inSourceR;
	else
		SetRect( &sourceR, 0, 0, mWidth, mHeight );
	
	if ( !inDestR ) {
		::GetPortBounds(inDestPort, (Rect *) inDestR);
	}
	
	// We don't want to colorize the image, so set black & white colors
	RGBForeColor( &Color_Black );
	RGBBackColor( &Color_White );

	CopyBits( sourceBits, destBits, &sourceR, inDestR, inMode, inMaskRgn );
	this->EndDrawing();
}


// ---------------------------------------------------------------------------
// 	CopyTo
// ---------------------------------------------------------------------------
// 	May change the fore/back color.

void
COffscreen::CopyTo( COffscreen *inDest, const Rect *inDestR, 
						 const Rect *inSourceR, SInt16 inMode, 
						 RgnHandle inMaskRgn )
{
	StGWorldSaver		aSaver;
	const BitMap		*sourceBits, *destBits;
	Rect				sourceR, destR;
	GWorldPtr			destWorld;
	
	ThrowIfNil_( inDest );
	
	// Prevent CopyBits from colorizing
	this->BeginDrawing();
	this->ResetColorsSelf();
	
	// Port & device should be the destination when using CopyBits
	inDest->BeginDrawing();	
	inDest->ResetColorsSelf();

	destWorld = inDest->GetGWorld();
	ThrowIfNil_( destWorld );

	sourceBits = ::GetPortBitMapForCopyBits(mWorld);
	destBits = ::GetPortBitMapForCopyBits(destWorld);

	if ( inSourceR )
		sourceR = *inSourceR;
	else
		SetRect( &sourceR, 0, 0, mWidth, mHeight );
	
	if ( inDestR ) {
		destR = *inDestR;	
	} else {
		::GetPortBounds(destWorld, &destR);
	}

	::CopyBits( sourceBits, destBits, &sourceR, &destR, inMode, inMaskRgn );
	
	inDest->EndDrawing();
	this->EndDrawing();
}


// ---------------------------------------------------------------------------
// 	CopyFrom
// ---------------------------------------------------------------------------

void
COffscreen::CopyFrom( COffscreen *inSource, const Rect *destR,
							const Rect *sourceR, SInt16 xferMode,
							RgnHandle inMaskRgn )
{
	ThrowIfNil_( inSource );
	
	inSource->CopyTo( this, destR, sourceR, xferMode, inMaskRgn );
}


// ---------------------------------------------------------------------------
// 	ResetColors
// ---------------------------------------------------------------------------

void
COffscreen::ResetColors()
{
	StSaveAndDraw		aDraw( this );
	
	this->ResetColorsSelf();
}


// ---------------------------------------------------------------------------
// 	ResetColorsSelf
// ---------------------------------------------------------------------------
// Sets foreground to black, background to white. For speed, use this call
// instead of ResetColors. This one doesn't set the gdevice, etc.

void
COffscreen::ResetColorsSelf()
{
	::RGBForeColor( &Color_Black );
	::RGBBackColor( &Color_White );
}


// ---------------------------------------------------------------------------
// 	CreateSimilarOffscreen
// ---------------------------------------------------------------------------

COffscreen *
COffscreen::CreateSimilarOffscreen( Boolean inUseSameDevice, SInt32 newWidth, SInt32 newHeight )
{
	StGWorldSaver		aSaver;
	COffscreen			*theNewBuffer = nil;
	
		// if no width/height specified, make it the exact same size as our buffer
	if ( newWidth < 0 ) newWidth = mWidth;
	if ( newHeight < 0 ) newHeight = mHeight;
	
	try
	{
		GDHandle theDevice = inUseSameDevice ? ::GetGWorldDevice(mWorld) : nil;
		theNewBuffer = COffscreen::CreateBuffer( newWidth, newHeight, mDepth, 
												this->GetColorTable(), theDevice );
		
		if ( mPalette )
			theNewBuffer->AssignPalette( mPalette );
			
		if ( mPalette )
			mPalette->AttachToPort( (GrafPtr) theNewBuffer->GetGWorld() );		// let it share our palette
	}
	catch( ... )
	{
		delete theNewBuffer;
		throw;
	}

	return theNewBuffer;
}


// ---------------------------------------------------------------------------
// 	GetPalette
// ---------------------------------------------------------------------------

CSharedPalette *COffscreen::GetPalette()
{
	return mPalette;
}


// ---------------------------------------------------------------------------
// 	AssignPalette
// ---------------------------------------------------------------------------
// 	Caller can destroy the color table once this call returns.

void
COffscreen::AssignPalette( CTabHandle inTable )
{
	ThrowIfNil_( inTable );
	ThrowIfNil_( mWorld );

	CSharedPalette *aNewPalette = new CSharedPalette( inTable, (GrafPtr) mWorld );
	
		// kill the old palette
	if ( mPalette )		
		mPalette->DecrementRefCount();
	
	mPalette = aNewPalette;
}


// ---------------------------------------------------------------------------
// 	AssignPalette
// ---------------------------------------------------------------------------
// Caller should not destroy the passed palette, but may decrement its
// reference count by one.

void
COffscreen::AssignPalette( CSharedPalette *inPalette )
{
	ThrowIfNil_( mWorld );

	// Kill the old palette
	if ( mPalette )		
	{
		mPalette->DecrementRefCount();
		mPalette = nil;
	}
	
	if ( inPalette ) {
		inPalette->AttachToPort( (GrafPtr) mWorld );
	} else {
		WindowRef theWindow = ::GetWindowFromPort((GrafPtr) mWorld);
		::NSetPalette( theWindow, nil, pmNoUpdates );
	}
	
	mPalette = inPalette;
}


// ---------------------------------------------------------------------------
// 	ConvertToRegion
// ---------------------------------------------------------------------------

RgnHandle
COffscreen::ConvertToRegion()
{
	RgnHandle			theRgn = nil;
	COffscreen			*tempBuffer = nil;
	
	ThrowIfNil_( mWorld );

	try
	{	
		// Apple's BitmapToRegion only works on a 1-bit buffer, so if we're
		// not a 1-bit buffer, we'll create a temporary one and use it.
		if ( mDepth == 1 )
		{
			theRgn = ::NewRgn();
			ThrowIfMemFail_( theRgn );
			
			PixMapHandle		thePixMap = this->GetPixMap();
			StHandleLocker		lock2( (Handle) thePixMap );

			OSErr err = ::BitMapToRegion( theRgn, ::GetPortBitMapForCopyBits(mWorld) );
			ThrowIfOSErr_( err );
		}
		else
		{
			tempBuffer = COffscreen::CreateBuffer( mWidth, mHeight, 1 );
			tempBuffer->CopyFrom( this );
			theRgn = tempBuffer->ConvertToRegion();
		}
	}
	catch( ... )
	{
		if ( theRgn ) ::DisposeRgn( theRgn );
		if ( tempBuffer ) delete( tempBuffer );
		throw;
	}
	
	if ( tempBuffer ) delete( tempBuffer );
	return( theRgn );
}


// ---------------------------------------------------------------------------
// 	EraseToWhite
// ---------------------------------------------------------------------------

void
COffscreen::EraseToWhite()
{
	StSaveAndDraw		saver( this );		// set port, etc
	StColorPenState		aPenState;
	Rect 				theRect;

	aPenState.Normalize();
	::RGBBackColor( &Color_White );
   ::EraseRect( GetPortBounds(mWorld, &theRect) );
}


// ---------------------------------------------------------------------------
// 	CopyFromRawData
// ---------------------------------------------------------------------------
// Copies data row-by-row into this offscreen buffer. This is useful when
// the rowBytes value of the source is not the same as our buffer. Depth,
// height, & width should be the same. RowBytes can be different.

void
COffscreen::CopyFromRawData( UInt8 *sourceData, SInt32 sourceRowBytes )
{
	sourceRowBytes = FixRowBytes( sourceRowBytes );		// in case the high 2 bits are set
	
		// never overstep our buffer or we'll trash memory
	sourceRowBytes = MIN( sourceRowBytes, mRowBytes );
	
		// move each row individually
	for ( SInt32 count = 0; count < mHeight; count++ )
	{
		::BlockMoveData( sourceData, mRowArray[count], sourceRowBytes );
		sourceData += sourceRowBytes;
	}
}


// ---------------------------------------------------------------------------
// 	CopyToRawData
// ---------------------------------------------------------------------------
// Copies data row-by-row from this offscreen buffer. This is useful when
// the rowBytes value of the destination is not the same as our buffer.
// Depth, height, & width should be the same. RowBytes can be different.

void
COffscreen::CopyToRawData( UInt8 *destData, SInt32 destRowBytes )
{
	destRowBytes = FixRowBytes( destRowBytes );	// in case the high 2 bits are set
	
		// don't overstep caller's buffer bounds if we have a bigger rowBytes
	destRowBytes = MIN( destRowBytes, mRowBytes );
	
	for ( SInt32 count = 0; count < mHeight; count++ )
	{
		::BlockMoveData( mRowArray[count], destData, destRowBytes );
		destData += destRowBytes;
	}
}


// ---------------------------------------------------------------------------
// 	CopyFromAndDownSample
// ---------------------------------------------------------------------------
// Copies the passed source buffer into our buffer, replacing every pixel
// that doesn't match inMatchColor to inDestColor. (Useful for masks &
// lassos). This routine can probably be replaced by CopyBits & a custom
// searchproc.

void
COffscreen::CopyFromAndDownSample( COffscreen *inSource, 
										 Color32 inMatchColor,
										 Color32 inDestColor )
{
	StGWorldSaver		save1;
	COffscreen *		tempBuffer = nil;
	
	// If the source & dest aren't the same size, we need to shrink/expand
	// the bitmap into a temporary buffer before proceeding. We don't want
	// to let CopyBits downsample the colors because its default searchProc
	// chooses which pixels map to black based on luminence.
	SInt32	width = this->GetWidth();
	SInt32	height = this->GetHeight();
	
	if ( (width != inSource->GetWidth()) || (height != inSource->GetHeight()) )
	{
		tempBuffer = inSource->CreateSimilarOffscreen( true, width, height );
		tempBuffer->CopyFrom( inSource );		// shrink/expand the pixels -- don't color resample
		inSource = tempBuffer;
	}
	
	// Erase the destination to white since we don't set every pixel in the loop below
	this->EraseToWhite();
	
	// Downsample the scratch buffer -- copy from source to dest, setting
	// all pixels in dest to black except where the source is the same as
	// the background.
	Color32			sourceColor;	
	PixelValue 		destPixel = this->Color32ToPixelValue( inDestColor );
	
	for ( long rowCount = 0; rowCount < height; rowCount++ )
		for ( long colCount = 0; colCount < width; colCount++ )
		{
			sourceColor = inSource->GetPixelColor( colCount, rowCount );
			if ( !UColorUtils::EqualColor32( sourceColor, inMatchColor ) )
				this->SetPixel( colCount, rowCount, destPixel );
		}
		
	if ( tempBuffer )
		delete tempBuffer;
}


// ---------------------------------------------------------------------------
// 	ResetPen
// ---------------------------------------------------------------------------

void
COffscreen::ResetPen()
{
	StSaveAndDraw	aSaver( this );
	
	this->ResetColorsSelf();			// fore & back color
	::PenNormal();						// pattern, mode, pensize
}


// ---------------------------------------------------------------------------
// 	SetForeColor
// ---------------------------------------------------------------------------

void
COffscreen::SetForeColor( Color32 inColor )
{
	StSaveAndDraw	aSaver( this );
	
	RGBColor	theRGB = UColorUtils::Color32ToRGB( inColor );
	::RGBForeColor( &theRGB );
}


// ---------------------------------------------------------------------------
// 	SetBackColor
// ---------------------------------------------------------------------------

void
COffscreen::SetBackColor( Color32 inColor )
{
	StSaveAndDraw	aSaver( this );
	
	RGBColor	theRGB = UColorUtils::Color32ToRGB( inColor );
	::RGBBackColor( &theRGB );
}


// ---------------------------------------------------------------------------
// 	SetForePixelValue
// ---------------------------------------------------------------------------

void
COffscreen::SetForePixelValue( PixelValue inColor )
{
	StSaveAndDraw	aSaver( this );
	
	// This is more exact than using RGBForeColor
	if ( mPalette )
	{
		::PmForeColor( inColor );
		return;
	}
	
	RGBColor	theRGB = this->PixelValueToRGB( inColor );
	::RGBForeColor( &theRGB );
}


// ---------------------------------------------------------------------------
// 	SetBackPixelValue
// ---------------------------------------------------------------------------

void
COffscreen::SetBackPixelValue( PixelValue inColor )
{
	StSaveAndDraw	save( this );
	
	// This is more exact than using RGBForeColor
	if ( mPalette )
	{
		::PmBackColor( inColor );
		return;
	}
	
	RGBColor	theRGB = this->PixelValueToRGB( inColor );
	::RGBBackColor( &theRGB );
}


// ---------------------------------------------------------------------------
// 	IsErased
// ---------------------------------------------------------------------------

Boolean
COffscreen::IsErased()
{
	for ( SInt32 rowCount = 0; rowCount < mHeight; rowCount++ )
	{
		for ( SInt32 colCount = 0; colCount < mWidth; colCount++ )
		{
			Color32 thePixelColor = this->GetPixelColor( colCount, rowCount );
			if ( !UColorUtils::EqualColor32( thePixelColor, kWhiteColor32 ) )
				return( false );
		}
	}
	
	return( true );
}


// ---------------------------------------------------------------------------
// 	IncreaseInverseTableSize
// ---------------------------------------------------------------------------
// Increases the size of the gworld.gdevice's inverse table to 5-bits of
// resolution. This increases the size from 4K to 32K, but improves the
// color matching quality (from RGB -> index value).

void
COffscreen::IncreaseInverseTableSize()
{
	ThrowIfNil_( mWorld );

	GDHandle	theDevice = ::GetGWorldDevice( mWorld );
	SInt32		newSeed = ::GetCTSeed();
	
	if ( (**theDevice).gdResPref < 5 )
	{
			// no good way to get error code, so check for enough RAM first
		SInt32	totalMem, contigMem;
		::PurgeSpace( &totalMem, &contigMem );
		if ( (UInt32)contigMem < 35000 ) throw( memFullErr );
	
		(**theDevice).gdResPref = 5;
		(**(**theDevice).gdITable).iTabSeed = newSeed;
		::GDeviceChanged( theDevice );
	}	
}


// ---------------------------------------------------------------------------
// 	GetBufferCount
// ---------------------------------------------------------------------------

SInt32
COffscreen::GetBufferCount()
{
	return sNumBuffers;
}


// ---------------------------------------------------------------------------
// 	DebugShowInWindow
// ---------------------------------------------------------------------------

void
COffscreen::DebugShowInWindow()
{
	StGWorldSaver	aSaver;
	Rect			r, tempR;
	WindowPtr		theWindow = nil;
	OSErr			err = noErr;
	GDHandle		maxDevice;

	SetRect( &r, 0, 0, this->GetWidth(), this->GetHeight() );
	
	SetGDevice( GetMainDevice() );
	theWindow = NewCWindow( nil, &r, (StringPtr)"", false, plainDBox, (WindowPtr) -1, false, 0);
	if ( !theWindow ) { err = memFullErr; goto DONE; }

	SetRect( &tempR, -20000, -20000, 20000, 20000 );
	maxDevice = GetMaxDevice( &tempR );
	if ( maxDevice )
		MoveWindow( theWindow, (**maxDevice).gdRect.left + 10, (**maxDevice).gdRect.top + 50, false );
	ShowWindow( theWindow );

	{
		StHandleLocker		lock2( (Handle) mPixMap );
		const BitMap	*destBits;

		destBits = ::GetPortBitMapForCopyBits( ::GetWindowPort(theWindow) );
		SetPortWindowPort( theWindow );
		CopyBits( (BitMap*) *mPixMap, destBits, &r, &r, srcCopy, nil );
	}
	
	EventRecord		anEvent;
	while( !GetNextEvent( mDownMask, &anEvent ) )
		;
	
	DONE:
	if ( err )
		SysBeep( 5 );
	if ( theWindow )
		DisposeWindow( theWindow );
}


/********************
*                   *
*   StSaveAndDraw   *
*                   *
********************/
// ---------------------------------------------------------------------------
// 	StSaveAndDraw											 [constructor]
// ---------------------------------------------------------------------------

StSaveAndDraw::StSaveAndDraw( COffscreen *inBuffer )
{
	::GetGWorld( &mOldPort, &mOldDevice );
	inBuffer->BeginDrawing();
}


// ---------------------------------------------------------------------------
// 	StSaveAndDraw											 [destructor]
// ---------------------------------------------------------------------------

StSaveAndDraw::~StSaveAndDraw()
{
	::SetGWorld( mOldPort, mOldDevice );
}


/***************************
*                          *
*   StBufferLeakDetector   *
*                          *
***************************/
// ---------------------------------------------------------------------------
// 	StBufferLeakDetector									 [constructor]
// ---------------------------------------------------------------------------

StBufferLeakDetector::StBufferLeakDetector()
{
	mNumBuffers = COffscreen::GetBufferCount();
}


// ---------------------------------------------------------------------------
// 	StBufferLeakDetector									 [destructor]
// ---------------------------------------------------------------------------

StBufferLeakDetector::~StBufferLeakDetector()
{
	SInt32	finalBuffers = COffscreen::GetBufferCount();
	char	buffer[ 256 ];
	Str255	theString;

	if ( finalBuffers > mNumBuffers )
	{
		sprintf( buffer, "buffers before=%ld  after=%ld", mNumBuffers, finalBuffers );
		CopyCStringToPascal(buffer, theString);
		DebugStr(theString);
	}
}
