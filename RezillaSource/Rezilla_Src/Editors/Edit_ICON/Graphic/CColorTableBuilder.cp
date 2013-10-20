// ===========================================================================
// CColorTableBuilder.cp
//                       Created: 2004-12-11 18:52:47
//             Last modification: 2004-12-17 11:30:04
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// ===========================================================================
// 
// Strategy:
// Apple's Picture Utilities can build us a ColorTable based on a PixMap.
// But they use only 5 bits of each RGB pixel to generate their histograms
// and this will reduce the color fidelity of our images.
// 
// Instead, we will first scan the pixmap and see how many unique colors
// are used. If that number will fit in the color table for the desired
// buffer depth, then we can use a color table full of exact values.
// CColorHash will be used to build this table and to convert from Color32
// values in the source buffer to indexes in the destination.
// 
// If the source image uses more colors than the table can handle, we'll
// use the Picture Utilities to generate the table and CopyBits() to
// downsample.
// 
// Notes:
// This code only works on 32-bit offscreens right now. It would be fairly
// easy to modify for other depths, but it would take a little work do so
// without slowing down the routine.

#include "RezillaConstants.h"
#include "COffscreen.h"
#include "CColorTableBuilder.h"
#include "CColorHash.h"
#include "UColorUtils.h"

#ifndef __MACH__
#include <PictUtils.h>
#endif


// ---------------------------------------------------------------------------
// 	DownSampleBuffer (static routine)
/// ---------------------------------------------------------------------------
// 	Returns nil instead of allocating a 32-bit buffer since we would
// 	just be wasting RAM. This only happens if inMaxDepth is 32.

COffscreen *CColorTableBuilder::DownSampleBuffer( COffscreen *inSource, SInt32 inMaxDepth,
													Boolean inIncludeBW, Boolean inMinimizeTable, 
													Boolean inLargerInverse )
{
	COffscreen				*destBuffer = nil;
	CColorTableBuilder		*helper = nil;
	
	try
	{
		helper = new CColorTableBuilder( inIncludeBW );
		ThrowIfMemFail_( helper );
		
		helper->SetBuffer( inSource );
		helper->SetIncludeBW( inIncludeBW );				// prob not necessary anymore
		helper->SetMinimizeTable( inMinimizeTable );
		helper->SetLargerInverseTable( inLargerInverse );
	
		destBuffer = helper->CreateDownSampledBuffer( inMaxDepth );
	}
	catch( ... )
	{
		delete helper;
		delete destBuffer;
		throw;
	}
	
	delete( helper );
	return( destBuffer );
}



// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------

CColorTableBuilder::CColorTableBuilder( Boolean inIncludeBW )
{
	mBuffer = nil;
	mIncludeBW = inIncludeBW;
	mMinimizeTable = true;
	mPictUtilMethod = 0;				// default Apple method
	mScanIsDone = false;
	mLargerInverseTable = false;
	mUseCopyBits = false;

	mColorHash = new CColorHash( inIncludeBW );
	ThrowIfMemFail_( mColorHash );
}


// ---------------------------------------------------------------------------
// 	Destructor
// ---------------------------------------------------------------------------

CColorTableBuilder::~CColorTableBuilder()
{
	delete mColorHash;
}


// ---------------------------------------------------------------------------
// 	SetBuffer
// ---------------------------------------------------------------------------

void
CColorTableBuilder::SetBuffer( COffscreen *inBuffer )
{
	mBuffer = inBuffer;
}


// ---------------------------------------------------------------------------
// 	SetIncludeBW
// ---------------------------------------------------------------------------

void
CColorTableBuilder::SetIncludeBW( Boolean inBW )
{
	mIncludeBW = inBW;
}


// ---------------------------------------------------------------------------
// 	SetMinimizeTable
// ---------------------------------------------------------------------------

void
CColorTableBuilder::SetMinimizeTable( Boolean inMinimizeTable )
{
	mMinimizeTable = inMinimizeTable;
}


// ---------------------------------------------------------------------------
// 	SetPictUtilMethod
// ---------------------------------------------------------------------------

void
CColorTableBuilder::SetPictUtilMethod( short inMethod )
{
	mPictUtilMethod = inMethod;
}


// ---------------------------------------------------------------------------
// 	SetLargerInverseTable
// ---------------------------------------------------------------------------

void
CColorTableBuilder::SetLargerInverseTable( Boolean inValue )
{
	mLargerInverseTable = inValue;
}


// ---------------------------------------------------------------------------
// 	CountUniqueColors
// ---------------------------------------------------------------------------

SInt32
CColorTableBuilder::GetColorCount()
{
	this->DoScan();
	return( mColorHash->GetColorCount() );
}


// ---------------------------------------------------------------------------
// 	GetColorTable
// ---------------------------------------------------------------------------
// 	Caller is responsible for getting rid of the table (using
// 	::DisposeCTable).

CTabHandle
CColorTableBuilder::GetColorTable( SInt32 inMaxDepth, SInt32 *outDepth )
{
	// Find out how much depth we need to display all of the pixels correctly
	SInt32 	uniqueColors = this->GetColorCount();
	SInt32	depthForActualColors = UColorUtils::NumColorsToDepth( uniqueColors );

	// Limit the destination depth depending on inMaxDepth
	switch( inMaxDepth )
	{
		case 1:
			// In fact we only call this with depths of 8 or 32-bits
			*outDepth = 1;
			return( UColorUtils::GetColorTable( 1 ) );		// 1-bit -> no thinking
		
		case 2:
			*outDepth = MIN( 2, depthForActualColors );
			break;

		case 4:
			*outDepth = MIN( 4, depthForActualColors );
			break;

		case 8:		
			*outDepth = MIN( 8, depthForActualColors );
			break;
		
		case 16:
			*outDepth = MIN( 16, depthForActualColors );
			if ( *outDepth == 32 )
				*outDepth = 16;
			break;
					
		case 32:
			*outDepth = MIN( 32, depthForActualColors );
			break;
					
		default:
			throw( paramErr );
	}
	
	// For 16 & 32-bit pixmaps, we'll use CopyBits but there's no need
	// to build up a color table or anything.
	if ( (*outDepth == 16) || (*outDepth == 32) )
	{
		mUseCopyBits = true;
		return( UColorUtils::GetColorTable( *outDepth ) );
	}
	
	// If there are too many colors in the image, call Apple's Pict Utils
	// to create a color table for us. Otherwise, just generate a table
	// from mColorArray.
	SInt32 			maxColors = UColorUtils::DepthToNumColors( *outDepth );
	CTabHandle		theTable = nil;

	if ( uniqueColors > maxColors )
	{
		PictInfo	info;
		short 		flags = returnColorTable | ( mIncludeBW ? 0 : suppressBlackAndWhite );
		
		OSErr err = ::GetPixMapInfo( 
								mBuffer->GetPixMap(), 		// the bits
								&info, 						// results go here
								flags, 						// from above
								maxColors, 					// number of colors in output table (incl b&w)				
								mPictUtilMethod, 			// Pict Util method to use (0 = default)
								0 );						// version

		theTable = info.theColorTable;
		
		// We need to use CopyBits since we didn't generate the color table
		// and can't use the hash lookup
		mUseCopyBits = true;
	}
	else
	{
		theTable = mColorHash->BuildColorTable( mMinimizeTable );
		mUseCopyBits = false;
	}
	
	return( theTable );
}


// ---------------------------------------------------------------------------
// 	DoScan
// ---------------------------------------------------------------------------

void
CColorTableBuilder::DoScan()
{
	if ( mScanIsDone ) return;
	ThrowIfNil_( mBuffer );

	RawPtr		rowPtr;
	SInt32		height = mBuffer->GetHeight();
	SInt32		width = mBuffer->GetWidth();
	
	if ( mIncludeBW )
	{
		mColorHash->AddColorToHash( kWhiteColor32 );
		mColorHash->AddColorToHash( kBlackColor32 );
	}
	
	for ( SInt32 rowCount = 0; rowCount < height; rowCount++ )
	{
		rowPtr = mBuffer->RawGetRowPtr( rowCount );
		
		for ( SInt32 colCount = 0; colCount < width; colCount++ )
		{
			Color32		theColor = mBuffer->RawGetPixelColor( rowPtr, colCount );
			mColorHash->AddColorToHash( theColor );
		}
	}
	
	mScanIsDone = true;
}


// ---------------------------------------------------------------------------
// 	CreateDownSampledBuffer
// ---------------------------------------------------------------------------
// Returns nil instead of a 32-bit buffer. This only happens if inMaxDepth
// is 32.

COffscreen *CColorTableBuilder::CreateDownSampledBuffer( SInt32 inMaxDepth )
{
	this->DoScan();

	SInt32			depth;	
	SInt32			width = mBuffer->GetWidth();
	SInt32			height = mBuffer->GetHeight();
	RawPtr			sourceRow, destRow;
	COffscreen		*destBuffer = nil;
	CTabHandle		theTable = nil;
	
	try
	{
		// Get the depth & color table
		theTable = this->GetColorTable( inMaxDepth, &depth );
		
		// No need to allocate 32-bit buffers -- waste of RAM because
		// the source buffer can be used instead of this one
		if ( depth == 32 )
		{
			::DisposeCTable( theTable );
			return( nil );
		}
		
		// Allocate the buffer to downsample into
		destBuffer = COffscreen::CreateBuffer( width, height, depth, theTable );
		
		// If we had too many colors to do an exact match, use CopyBits
		// instead of the color hash.
		if ( mUseCopyBits )
		{
			if ( mLargerInverseTable && (depth < 16) )
				destBuffer->IncreaseInverseTableSize();
			
			destBuffer->CopyFrom( mBuffer );
		}
		else
		{			
			for ( SInt32 rowCount = 0; rowCount < height; rowCount++ )
			{
				sourceRow = mBuffer->RawGetRowPtr( rowCount );
				destRow = destBuffer->RawGetRowPtr( rowCount );
				
				for ( SInt32 colCount = 0; colCount < width; colCount++ )
				{
					Color32		sourceColor = mBuffer->RawGetPixelColor( sourceRow, colCount );
					PixelValue 	destPixel = mColorHash->LookupAssociatedNumber( sourceColor );
					destBuffer->SetPixel( colCount, rowCount, destPixel );
				}
			}
		}
	}
	catch( ... )
	{
		delete destBuffer;
		if ( theTable ) ::DisposeCTable( theTable );
		throw;
	}
	
	if ( theTable ) ::DisposeCTable( theTable );
	return( destBuffer );
}

