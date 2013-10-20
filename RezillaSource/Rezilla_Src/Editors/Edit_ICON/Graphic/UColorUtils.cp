// ===========================================================================
// UColorUtils.cp
//                       Created: 2004-12-11 18:52:48
//             Last modification: 2005-01-07 09:16:18
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004, 2005
// All rights reserved.
// ===========================================================================

#include "RezillaConstants.h"
#include "UColorUtils.h"
#include "UMemoryMgr.h"
#include "UResources.h"
#include "CRezillaApp.h"


// ---------------------------------------------------------------------------
// 	DepthToNumColors
// ---------------------------------------------------------------------------

SInt32
UColorUtils::DepthToNumColors( SInt32 inDepth )
{
	SInt32	outColors;
	
	switch( inDepth )
	{
		case 1:
			outColors = 2;
			break;
		case 2:
		case 34:
			outColors = 4;
			break;
		case 4:
		case 36:
			outColors = 16;
			break;
		case 8:
		case 40:
			outColors = 256;
			break;
		case 16:
			outColors = 0x00010000;		// 2^16 = 65536
			break;
		case 32:
			outColors = 0x01000000;		// 2^24 = 16+ million
			break;
			
		default:
			throw( paramErr );
	}
	
	return( outColors );
}


// ---------------------------------------------------------------------------
// 	NumColorsToDepth
// ---------------------------------------------------------------------------

SInt32
UColorUtils::NumColorsToDepth( SInt32 inColors )
{
	if ( inColors <= 2 )	return( 1 );
	if ( inColors <= 4 )	return( 2 );
	if ( inColors <= 16 )	return( 4 );
	if ( inColors <= 256 )	return( 8 );
	
	return( 32 );		// 16-bit isn't as accurate, so return 32 instead
}


// ---------------------------------------------------------------------------
// 	CalcRGBDistance
// ---------------------------------------------------------------------------
// 	Returns the sum of the squares of the differences in the red, green, &
// 	blue components of the passed colors

double
UColorUtils::CalcRGBDistance( const RGBColor &x, const RGBColor &y )
{
		// note: we use doubles to prevent overflow
	double temp1 = (double) x.red - y.red;
	double temp2 = (double) x.green - y.green;
	double temp3 = (double) x.blue - y.blue;
	
	return( temp1 * temp1 + temp2 * temp2 + temp3 * temp3 );
}


// ---------------------------------------------------------------------------
// 	IsColorInTable
// ---------------------------------------------------------------------------
// 	Returns true if the passed RGBColor is in the color table. Also returns
// 	the index (0..255). If the color is not in the table, we return the
// 	closest color index.

Boolean
UColorUtils::IsColorInTable( CTabHandle inTable, const RGBColor &inColor, UInt8 *outIndex )
{
	// Validate parameters
	if ( outIndex ) *outIndex = 0;					// in case of error
	if ( !inTable || !*inTable ) return( false );
	
	// Lock the table down and prepare to scan it
	StHandleLocker		locker( (Handle) inTable );
	SInt32				numItems = (**inTable).ctSize + 1;
	ColorSpecPtr		colorArray = (**inTable).ctTable;
	
	// First try for an exact match
	SInt32 count;
	for ( count = 0; count < numItems; count++ )
		if ( UColorUtils::EqualRGB( inColor, colorArray[count].rgb ) )
		{
			if ( outIndex ) *outIndex = count;
			return( true );
		}
	
	// No exact match -- find the closest color
	SInt32 		bestIndex = 0;
	double		bestValue = 0;			// lowest value is best
	double		newValue;
	
	for ( count = 0; count < numItems; count++ )
	{
		newValue = CalcRGBDistance( inColor, colorArray[count].rgb );
		
		if ( (count == 0) || (newValue < bestValue) )
		{
			bestValue = newValue;
			bestIndex = count;
		}
	}

	if ( outIndex ) *outIndex = bestIndex;
	return( false );
}


// ---------------------------------------------------------------------------
// 	NewColorTableByEntries
// ---------------------------------------------------------------------------
// 	The RGB values are not set, except for black & white.

CTabHandle
UColorUtils::NewColorTableByEntries( SInt32 inNumEntries )
{
	CTabHandle theTable = (CTabHandle) ::NewHandleClear( sizeof(ColorTable) + (inNumEntries - 1) * sizeof(ColorSpec) );
	ThrowIfMemFail_( theTable );
	
	StHandleLocker	aLock( (Handle) theTable );
	CTabPtr			p = *theTable;
	
	p->ctSeed = ::GetCTSeed();
	p->ctFlags = 0;								// hi bit = 0 for pixmaps, 1 for gdevices
	p->ctSize = inNumEntries - 1;
	
	// Put b&w in the table or quickdraw gets mad
	p->ctTable[ 0 ].rgb = Color_White;
	p->ctTable[ p->ctSize ].rgb = Color_Black;
	
	// Might as well set the value fields while we're here in case they are
	// ever used
	for ( SInt32 count = 0; count < inNumEntries; count++ )
		p->ctTable[ count ].value = count;

	return( theTable );
}


// ---------------------------------------------------------------------------
// 	NewColorTableByDepth
// ---------------------------------------------------------------------------
// 	The RGB values are not set, except for black & white.

CTabHandle
UColorUtils::NewColorTableByDepth( SInt32 depth )
{
	CTabHandle	theTable;
	SInt32		numEntries;
	
	// Direct color requires some special attention
	if ( (depth == 16) || (depth == 32) )
	{
		theTable = (CTabHandle) ::NewHandleClear( sizeof( ColorTable ) - sizeof(ColorSpec) );
		ThrowIfMemFail_( theTable );
		
		(**theTable).ctSeed = depth;
		(**theTable).ctSize = -1;
		return( theTable );
	}
	
	// Now handle 1,2,4,8 bit tables.
	// Note: 34, 36, 40 are grayscale versions of 2, 4, 8.
	switch( depth )
	{
		case 1:
			numEntries = 2;		
			break;
		case 2:  case 34:
			numEntries = 4;		
			break;
		case 4:	 case 36:
			numEntries = 16;	
			break;
		case 8:  case 40:
			numEntries = 256;	
			break;
		default:
			throw( paramErr );
	}
	
	theTable = UColorUtils::NewColorTableByEntries( numEntries );
	return( theTable );
}


// ---------------------------------------------------------------------------
// 	GetColorTable
// ---------------------------------------------------------------------------
// 	Same as the toolbox GetCTable(), with 3 differences:
// 	(1) We change the current resource file to the application to avoid
// 		grabbing tables out of documents.
// 	(2) We work on 32-bit and 16-bit depths, returning dummy tables
// 		rather than nil.
// 	(3) We throw an error rather than returning nil.
// 	
// 	Note: ctID is typically the bit-depth of the buffer you want
// 	      a color table for.

CTabHandle
UColorUtils::GetColorTable( SInt32 ctID )
{
	StRezRefSaver	aSaver;
	::UseResFile( CRezillaApp::GetSelfRefNum() );
	
	CTabHandle	theTable = nil;
	if ( (ctID == 32) || (ctID == 16) )
	{
		theTable = UColorUtils::NewColorTableByDepth( ctID );
	}
	else
	{
		theTable = ::GetCTable( ctID );
		ThrowIfResFail_( theTable );
	}
	
	return( theTable );
}


// ---------------------------------------------------------------------------
// 	FixColorTableBW
// ---------------------------------------------------------------------------

void
UColorUtils::FixColorTableBW( CTabHandle aTable, Boolean inAddToTableIfNeeded )
{
	StHandleLocker	lock1( (Handle) aTable );
	CTabPtr			p = *aTable;
	Boolean			blackDone = false, whiteDone = false;

	// See if black & white are already where they belong
	if ( UColorUtils::EqualRGB( Color_Black, p->ctTable[ p->ctSize ].rgb ) )
		blackDone = true;
	
	if ( UColorUtils::EqualRGB( Color_White, p->ctTable[ 0 ].rgb ) )
		whiteDone = true;
	
	// Loop through the table and find black & white. Note that we ignore
	// the first & last positions in the for loop.
	for ( SInt32 count = 1; count < p->ctSize; count++ )
	{
		if ( whiteDone && blackDone ) return;
	
		if ( !blackDone )
		{
			if ( UColorUtils::EqualRGB( p->ctTable[ count ].rgb, Color_Black ) )
			{
				p->ctTable[ count ].rgb = p->ctTable[ p->ctSize ].rgb;
				p->ctTable[ p->ctSize ].rgb = Color_Black;
				blackDone = true;
			}
		}
		
		if ( !whiteDone )
		{
			if ( UColorUtils::EqualRGB( p->ctTable[ count ].rgb, Color_White ) )
			{
				p->ctTable[ count ].rgb = p->ctTable[ 0 ].rgb;
				p->ctTable[ 0 ].rgb = Color_White;
				whiteDone = true;
			}
		}
	}
	
	// Black and white weren't in the table. If the color wanted us to,
	// force the colors into it.
	if ( !whiteDone && inAddToTableIfNeeded )
		p->ctTable[ 0 ].rgb = Color_White;

	if ( !blackDone && inAddToTableIfNeeded )
		p->ctTable[ p->ctSize ].rgb = Color_Black;
}



// ---------------------------------------------------------------------------
// 	CalcRowBytes
// ---------------------------------------------------------------------------
// 	This will return the minimum number of rowBytes, rounded to an even
// 	number, not the most optimal for speed.

UInt16
UColorUtils::CalcRowBytes( SInt32 width, SInt32 depth )
{
	UInt16	rowBytes = 0;
	
	switch( depth )
	{
		case 1:
			rowBytes = (width + 7) >> 3;
			break;
		case 2:
			rowBytes = (width + 3) >> 2;
			break;
		case 4:
			rowBytes = (width + 1) >> 1;
			break;
		case 8:
			rowBytes = width;
			break;
		case 16:
			rowBytes = width << 1;
			break;
		case 24:
		case 32:
			rowBytes = width << 2;
			break;
	}

	if ( rowBytes & 1 )						// must always be even
		++rowBytes;

	return( rowBytes );
}



// ---------------------------------------------------------------------------
// 	CalcPixmpaRowBytes
// ---------------------------------------------------------------------------

UInt16
UColorUtils::CalcPixmapRowBytes( SInt32 width, SInt32 depth )
{
		// the high bit of a pixmap's rowBytes field must be set for
		// color QD to distinguish a pixmap from a bitmap (see TN 120)
	UInt16 rowBytes = UColorUtils::CalcRowBytes( width, depth );
	return( rowBytes | 0x8000 );
}


// ---------------------------------------------------------------------------
// 	NewColorTableFromPtr
// ---------------------------------------------------------------------------
// 	This is needed because Quickdraw requires a full-sized color table but
// 	the various image resources (cicn, ppat, etc) sometimes have minimized
// 	color tables.

CTabHandle
UColorUtils::NewColorTableFromPtr( SInt32 depth, UInt8 *sourceData, bool convert )
{
	CTabHandle	theTable;
	CTabPtr		sourceTable = (CTabPtr) sourceData;
	SInt32		numEntries;
		
	theTable = UColorUtils::NewColorTableByDepth( depth );
	SInt32		sourceSize = (convert ? ::CFSwapInt16BigToHost(sourceTable->ctSize) : sourceTable->ctSize) + 1;
	numEntries = MIN( sourceSize, (**theTable).ctSize + 1 );

	for ( SInt32 count = 0; count < numEntries; count++ ) {
		if (convert) {
			(**theTable).ctTable[count].value = ::CFSwapInt16BigToHost(sourceTable->ctTable[count].value);
			(**theTable).ctTable[count].rgb.red = ::CFSwapInt16BigToHost(sourceTable->ctTable[count].rgb.red);
			(**theTable).ctTable[count].rgb.green = ::CFSwapInt16BigToHost(sourceTable->ctTable[count].rgb.green);
			(**theTable).ctTable[count].rgb.blue = ::CFSwapInt16BigToHost(sourceTable->ctTable[count].rgb.blue);
		} else {
			(**theTable).ctTable[count] = sourceTable->ctTable[count];
		}
	}
	
	return( theTable );
}


// ---------------------------------------------------------------------------
// 	Color32ToRGB
// ---------------------------------------------------------------------------
// 	See IM VI p. 17-7+ for more info. 
// 	Each component is duplicated in both the high and low byte of the
// 	output RGB component. This way, 0xFFFF remains 0xFFFF, 0x0000 remains
// 	0x0000 and everything in between scales.

RGBColor
UColorUtils::Color32ToRGB( Color32 inColor )
{
	RGBColor	theRGB;
	
	Color32 temp1 = inColor & 0x00FF0000;			// clear other colors
	theRGB.red = (temp1 >> 8) | (temp1 >> 16 );
	
	Color32 temp2 = inColor & 0x0000FF00;
	theRGB.green = (temp2) | (temp2 >> 8);
	
	Color32 temp3 = inColor & 0x000000FF;
	theRGB.blue = (temp3 << 8) | (temp3);
	
	return( theRGB );
}


// ---------------------------------------------------------------------------
// 	Color16ToRGB
// ---------------------------------------------------------------------------
// 	See IM VI p. 17-9 for more info (or above routine). Each component is
// 	mapped 3 times into the destination and then the high bit is mapped one
// 	additional time into the low bit.

RGBColor
UColorUtils::Color16ToRGB( Color32 inColor )
{
	// For each component, we'll first shift it to the rightmost position
	// in the temp variable and then clear the other component fields. then
	// we duplicate the component 3 times in the destination and tack on
	// the high bit into the destination's low bit. 
	// Note: this could be sped up by eliminating the first shift in each
	// area and changing the shift values.
	RGBColor	theRGB;
	
	Color32 temp1 = (inColor >> 10) & 0x001F;	
	theRGB.red = (temp1 << 1) | (temp1 << 6) | (temp1 << 11) | (temp1 >> 4);
	
	Color32 temp2 = (inColor >> 5) & 0x001F;
	theRGB.green = (temp2 << 1) | (temp2 << 6) | (temp2 << 11) | (temp2 >> 4);
	
	Color32 temp3 = inColor & 0x001F;
	theRGB.green = (temp3 << 1) | (temp3 << 6) | (temp3 << 11) | (temp3 >> 4);
	
	return( theRGB );
}


// ---------------------------------------------------------------------------
// 	RGBToColor32
// ---------------------------------------------------------------------------

Color32
UColorUtils::RGBToColor32( const RGBColor &inRGB )
{
	Color32		redComp = inRGB.red;		// put in long (2-byte int problem)
	
	return( (	(redComp << 8) & 0x00FF0000) 	|
				(inRGB.green & 0x0000FF00) 		|
				((inRGB.blue >> 8) & 0x000000FF) );
}


// ---------------------------------------------------------------------------
// 	RGBToColor16
// ---------------------------------------------------------------------------

Color32
UColorUtils::RGBToColor16( const RGBColor &inRGB )
{
	return( ((inRGB.red >> 1) & 0x00007C00) 	|
			((inRGB.green >> 6) & 0x000003E0)	|
			((inRGB.blue >> 11) & 0x0000001F) );
}


// ---------------------------------------------------------------------------
// 	EqualRGB
// ---------------------------------------------------------------------------

Boolean
UColorUtils::EqualRGB( const RGBColor &x, const RGBColor &y )
{
	return (x.red == y.red) && (x.green == y.green) && (x.blue == y.blue);
}


// ---------------------------------------------------------------------------
// 	EqualColor32
// ---------------------------------------------------------------------------

Boolean
UColorUtils::EqualColor32( Color32 x, Color32 y )
{
	// Ignore hi byte
	return( (x & 0x00FFFFFF) == (y & 0x00FFFFFF) );
}


// ---------------------------------------------------------------------------
// 	EqualColor16
// ---------------------------------------------------------------------------

Boolean
UColorUtils::EqualColor16( Color32 x, Color32 y )
{
	// Ignore hi bit
	return( (x & 0x7FFF) == (y & 0x7FFF) );
}


// ---------------------------------------------------------------------------
// 	SetForeColor32
// ---------------------------------------------------------------------------
// 	Is there a more exact way of doing this than using RGBForeColor???

void
UColorUtils::SetForeColor32( Color32 inColor )
{
	RGBColor	theRGB = UColorUtils::Color32ToRGB( inColor );
	::RGBForeColor( &theRGB );
}


// ---------------------------------------------------------------------------
// 	SetBackColor32
// ---------------------------------------------------------------------------
// 	Is there a more exact way of doing this than using RGBBackColor???

void
UColorUtils::SetBackColor32( Color32 inColor )
{
	RGBColor	theRGB = UColorUtils::Color32ToRGB( inColor );
	::RGBBackColor( &theRGB );
}

