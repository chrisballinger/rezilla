// ===========================================================================
// CPatternTargetView.cp
//                       Created: 2004-12-11 18:53:17
//             Last modification: 2004-12-14 15:19:20
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "COffscreen.h"
#include "UIconMisc.h"
#include "CPatternTargetView.h"

#include <UDrawingState.h>

// ---------------------------------------------------------------------------
// 	CreateFromStream
// ---------------------------------------------------------------------------

CPatternTargetView *CPatternTargetView::CreateFromStream( LStream *inStream )
{
	return new CPatternTargetView( inStream );
}


// ---------------------------------------------------------------------------
// 	Constructor (LStream *)
// ---------------------------------------------------------------------------

CPatternTargetView::CPatternTargetView( LStream *inStream ) :
	CDraggableTargetView( inStream )
{
}


// ---------------------------------------------------------------------------
// 	Destructor
// ---------------------------------------------------------------------------

CPatternTargetView::~CPatternTargetView()
{
}


// ---------------------------------------------------------------------------
// 	DrawSelf
// ---------------------------------------------------------------------------

void
CPatternTargetView::DrawBuffer()
{
	StGWorldSaver		aSaver;
	StColorPenState		aPenState;
	aPenState.Normalize();
	
	if ( !mBuffer ) return;
	Rect  sourceR, portR, destR, borderR, localR;
	
	GrafPtr	destPort = this->GetMacPort();
	if ( !destPort ) return;
	
	this->CalcLocalFrameRect( borderR );

	SInt32	destWidth = borderR.right - borderR.left - 12;
	SInt32	destHeight = borderR.bottom - borderR.top - 12;
	
	SInt32	imageWidth = mBuffer->GetWidth();
	SInt32	imageHeight = mBuffer->GetHeight();
	if ( (imageWidth == 0) || (imageHeight == 0) ) return;
	::SetRect( &sourceR, 0, 0, imageWidth, imageHeight );
	
	this->GetCenteredBufferArea( destWidth, destHeight, &localR, &portR );

	if ( !this->IsUsed() )
	{
		Pattern aPat;

		this->FocusDraw();
		aPenState.Normalize();
		::PenPat( UQDGlobals::GetLightGrayPat(&aPat) );
		::PaintRect( &localR );
		return;
	}
	
	// Find out how many rows & columns to draw to fill in the space for
	// the pattern. Round upward to the next whole number and clip to
	// prevent overdrawing the area we're drawing to.
	SInt32 numRows = destHeight / imageHeight;
	if ( destHeight % imageHeight ) ++numRows;
	
	SInt32 numCols = destWidth / imageWidth;
	if ( destWidth % imageWidth ) ++numCols;
	
	// The CopyTo() method below clears the clip region, so the only way to
	// clip is to pass a mask region to CopyTo.
	RgnHandle	maskRgn = nil;
	
	try
	{	
		maskRgn = URegionMisc::NewRegionFromRect( portR );
		for ( SInt32 rowCount = 0; rowCount < numRows; rowCount++ )
		{
			destR.left = portR.left;
			destR.right = destR.left + imageWidth;
			destR.top = portR.top + imageHeight * rowCount;
			destR.bottom = destR.top + imageHeight;
		
			for ( SInt32 colCount = 0; colCount < numCols; colCount++ )
			{
				mBuffer->CopyTo( destPort, &destR, nil, srcCopy, maskRgn );
				::OffsetRect( &destR, imageWidth, 0 );
			}
		}
	}
	catch( ... )
	{
		// Don't throw errors because it would cause an infinite recursion
	}
	
	URegionMisc::DisposeRegion( maskRgn );
}
