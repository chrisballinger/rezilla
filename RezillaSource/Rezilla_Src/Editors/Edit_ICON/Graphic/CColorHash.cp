// ===========================================================================
// CColorHash.cp
//                       Created: 2004-12-11 18:51:56
//             Last modification: 2004-12-15 14:04:17
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
// For speed, most of the methods are inline.
// White & Black are put into the first & last elements in the table when a
// color table is built. it is optional whether to force them into the
// table even if they didn't exist previously.

#include "RezillaConstants.h"
#include "CColorHash.h"
#include "UColorUtils.h"


// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------

CColorHash::CColorHash( Boolean forceBW )
{
	for ( SInt32 count = 0; count < kHashArrayLimit; count++ )
		mHashArray[ count ].theColor = kEmptyColorSlot;

	mRecent1.theColor = kEmptyColorSlot;
	mRecent2.theColor = kEmptyColorSlot;
	mUniquePixels = 0;
	mBWCompleted = false;
	
	if ( forceBW )
	{
		this->AddColorToHash( kWhiteColor32 );
		this->AddColorToHash( kBlackColor32 );
	}
}


// ---------------------------------------------------------------------------
// 	Destructor
// ---------------------------------------------------------------------------

CColorHash::~CColorHash()
{
}


// ---------------------------------------------------------------------------
// 	BuildColorTable
// ---------------------------------------------------------------------------

CTabHandle
CColorHash::BuildColorTable( Boolean inMinimal )
{
	CTabHandle	theTable;
	
	this->FixBlackAndWhite( inMinimal );
	
	if ( inMinimal )
		theTable = UColorUtils::NewColorTableByEntries( mUniquePixels );
	else
	{
		// This will round the color table up to the "normal"
		// number of colors rather than the minimal one
		SInt32	depth = UColorUtils::NumColorsToDepth( mUniquePixels );
		theTable = UColorUtils::NewColorTableByDepth( depth );
	}
	
	::HLock( (Handle) theTable );
	CTabPtr		p = *theTable;
	
	// The associated value in mHashArray has the color index
	SInt32  tableCount = 0;

	for ( SInt32 hashCount = 0; hashCount < kHashArrayLimit; hashCount++ )
	{
		Color32		theColor = mHashArray[hashCount].theColor;
		
		if ( theColor != kEmptyColorSlot )
		{
			if ( tableCount++ >= mUniquePixels )
				break;

			SInt32		associatedValue = mHashArray[hashCount].associatedNumber;
			p->ctTable[ associatedValue ].rgb = UColorUtils::Color32ToRGB( theColor );
		}
	}	
	
	::HUnlock( (Handle) theTable );
	return( theTable );
}


// ---------------------------------------------------------------------------
// 	FindAssociatedValue
// ---------------------------------------------------------------------------

SInt32
CColorHash::FindAssociatedValueIndex( SInt32 inAssoc )
{
	for ( long count = 0; count < kHashArrayLimit; count++ )
		if ( (mHashArray[count].theColor != kEmptyColorSlot) && 
			 (mHashArray[count].associatedNumber == inAssoc) )
		{
			return( count );
		}
		
	return -1;
}


// ---------------------------------------------------------------------------
// 	FixBlackAndWhite
// ---------------------------------------------------------------------------
// White needs slot #0 in the color table. Black needs the last slot. We'll
// find whatever colors are currently using those pixel values and swap the
// pixel values whatever black & white have been given.

void
CColorHash::FixBlackAndWhite( Boolean inMinimalTable )
{
	if ( mBWCompleted ) return;			// already fixed it
	
	SInt32	depth = UColorUtils::NumColorsToDepth( mUniquePixels );
	SInt32	maxColorsForDepth = UColorUtils::DepthToNumColors( depth );
	SInt32	blackAssocValue = inMinimalTable ? (mUniquePixels - 1) : (maxColorsForDepth - 1);

	SInt32	whiteIndex, blackIndex, assocIndex;
	
	// If white is in the table, put it at the beginning
	if ( this->GetIndex( kWhiteColor32, &whiteIndex ) )
	{
		assocIndex = this->FindAssociatedValueIndex( 0 );
		if ( (assocIndex != -1) && (assocIndex != whiteIndex) )
		{
				// swap the associated values
			mHashArray[ assocIndex ].associatedNumber = mHashArray[ whiteIndex ].associatedNumber;
			mHashArray[ whiteIndex ].associatedNumber = 0;
		}
	}
	
	// If black is in the table, put it at the end
	if ( this->GetIndex( kBlackColor32, &blackIndex ) )
	{
		assocIndex = this->FindAssociatedValueIndex( blackAssocValue );
		if ( assocIndex == -1 )
		{
			// Nobody is using the desired value for black -- this happens if we
			// don't minimize the table and don't completely fill it.
			// just give black the pixel value it wants
			mHashArray[ blackIndex ].associatedNumber = blackAssocValue;
		}
		else if ( assocIndex != blackIndex )
		{
			// Swap the associated (pixel) values
			mHashArray[ assocIndex ].associatedNumber = mHashArray[ blackIndex ].associatedNumber;
			mHashArray[ blackIndex ].associatedNumber = blackAssocValue;
		}
	}
	
	// Clear the cache since we've changed some values
	mRecent1.theColor = kEmptyColorSlot;
	mRecent2.theColor = kEmptyColorSlot;

	mBWCompleted = true;
}


// ---------------------------------------------------------------------------
// 	AddColorToHash
// ---------------------------------------------------------------------------

inline void
CColorHash::AddColorToHash( Color32 inColor )
{
	inColor &= 0x00FFFFFF;			// clear hi byte because kEmptyColorSlot might conflict
	
	// check the recent ones for speed first
	if ( IsRecentOne( inColor ) != kInvalidAssociate )
		return;
	
	// find the slot number
	SInt32		index;
	
	if ( GetIndex( inColor, &index ) )
	{
			// already in table, but keep as a recent one for speed
		this->AddToRecentOne( inColor, mHashArray[index].associatedNumber );
	}
	else
	{
		// not in table yet -- put it there
		mHashArray[ index ].theColor = inColor;
		mHashArray[ index ].associatedNumber = mUniquePixels;

		// keep track of recent ones
		this->AddToRecentOne( inColor, mUniquePixels++ );
		
		// and we're "dirty" now (B&W in wrong place)
		mBWCompleted = false;
	}
}


// ---------------------------------------------------------------------------
// 	IsRecentOne
// ---------------------------------------------------------------------------
// 	This is used both for lookups and adding elements to the array.
// inline ?

SInt32
CColorHash::IsRecentOne( Color32 inColor )
{
	if ( mRecent1.theColor == inColor )
		return( mRecent1.associatedNumber );
	
	if ( mRecent2.theColor == inColor )
		return( mRecent2.associatedNumber );
		
	return( kInvalidAssociate );
}


// ---------------------------------------------------------------------------
// 	AddToRecentOne
// ---------------------------------------------------------------------------
// inline ?

void
CColorHash::AddToRecentOne( Color32 inColor, SInt32 inAssociate )
{
	mRecent2 = mRecent1;
	mRecent1.theColor = inColor;
	mRecent1.associatedNumber = inAssociate;
}


// ---------------------------------------------------------------------------
// 	LookupAssociatedNumber
// ---------------------------------------------------------------------------

SInt32
CColorHash::LookupAssociatedNumber( Color32 inColor )
{
	SInt32	associatedNumber;
	SInt32	theIndex;
	
	inColor &= 0x00FFFFFF;
	
	associatedNumber = this->IsRecentOne( inColor );
	if ( associatedNumber != kInvalidAssociate ) return( associatedNumber );
	
	if ( this->GetIndex( inColor, &theIndex ) )
	{
		associatedNumber = mHashArray[ theIndex ].associatedNumber;

		// Keep track of recent ones for speed 
		this->AddToRecentOne( inColor, associatedNumber );
		
		// Return the requested number
		return( associatedNumber );
	}
	
	return( kInvalidAssociate );
}


// ---------------------------------------------------------------------------
// 	GetHashStartingPoint
// ---------------------------------------------------------------------------
// inline ?

SInt32
CColorHash::GetHashStartingPoint( Color32 inColor )
{
	// Start searching the color list based on a hash formula.
	// (the low 3 bits will tend to change rapidly, so use the
	// low 3 bits of red & green + the low 2 bits of blue as an
	// 8-bit index). 
	SInt32 hashStartingPoint = 
						( ((inColor & 0x000F0000) >> 10)	|
						  ((inColor & 0x00000700) >> 5) 	|
						  (inColor & 0x00000007) );
						  
	return( MIN( hashStartingPoint, kHashArrayLimit-1 ) );
}


// ---------------------------------------------------------------------------
// 	GetIndex
// ---------------------------------------------------------------------------
// inline ?

Boolean
CColorHash::GetIndex( Color32 inColor, SInt32 *outIndex )
{
	SInt32	hashStartingPoint = this->GetHashStartingPoint( inColor );
	SInt32	hashCount = hashStartingPoint;

	do
	{
		if ( hashCount >= kHashArrayLimit ) 
			hashCount = 0;					// wrap around to start of list
	
		// if we find an empty slot...
		if ( mHashArray[ hashCount ].theColor == kEmptyColorSlot )
		{
			*outIndex = hashCount;
			return( false );
		}
		
		// if it's already in the list...
		if ( mHashArray[ hashCount ].theColor == inColor )
		{
			*outIndex = hashCount;
			return( true );
		}

		++hashCount;
	} while( hashCount != hashStartingPoint );
	
	// Table is full -- this shouldn't happen
	throw( paramErr );
	return false;
}
