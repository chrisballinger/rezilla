// ===========================================================================
// CIconSelection.cp
//                       Created: 2004-12-11 18:53:20
//             Last modification: 2004-12-15 07:21:07
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "COffscreen.h"
#include "CIconSelection.h"
#include "UGraphicConversion.h"
#include "UIconMisc.h"


// ============================================================
// 	Constructor
// ============================================================

CIconSelection::CIconSelection()
{
	mSelectionBuffer = nil;
	mRegion = URegionMisc::NewRegion();
}


// ============================================================
// 	Destructor
// ============================================================

CIconSelection::~CIconSelection()
{
	this->DisposeBuffer();
	URegionMisc::DisposeRegion( mRegion );
}


// ============================================================
// 	DisposeBuffer
// ============================================================

void CIconSelection::DisposeBuffer()
{
	if ( mSelectionBuffer )
	{
		delete mSelectionBuffer;
		mSelectionBuffer = nil;
	}
}


// ============================================================
// 	SelectAll
// ============================================================

void CIconSelection::SelectAll( COffscreen *inBuffer )
{
	Rect	r;
	SetRect( &r, 0, 0, inBuffer->GetWidth(), inBuffer->GetHeight() );
	this->SetSelection( inBuffer, r );
}


// ============================================================
// 	SelectNone
// ============================================================

void CIconSelection::SelectNone()
{
	::SetEmptyRgn( mRegion );
	this->DisposeBuffer();
}


// ============================================================
// 	SetSelection
// ============================================================

void CIconSelection::SetSelection( COffscreen *inBuffer, const Rect &inRect )
{
	RgnHandle	theRgn = URegionMisc::NewRegionFromRect( inRect );
	this->SetSelection( inBuffer, theRgn );
	URegionMisc::DisposeRegion( theRgn );
}


// ============================================================
// 	SetSelection
// ============================================================
// 	Copy the region and allocate a new selection buffer.

void CIconSelection::SetSelection( COffscreen *inBuffer, RgnHandle inRegion )
{
	ThrowIfNil_( inBuffer );
	ThrowIfNil_( inRegion );
		
	Rect	sourceR, destR, bounds;
	SInt32	newWidth, newHeight;
	
	GetRegionBounds(inRegion, &bounds);
	newWidth = bounds.right - bounds.left;
	newHeight = bounds.bottom - bounds.top;

	if ( (newWidth <= 0) || (newHeight <= 0) )
	{
		this->SelectNone();
		return;
	}
	
	try
	{
		this->DisposeBuffer();
		
		// Make a copy of the region
		this->SetRawSelection( inRegion );
		
		// Create a new offscreen buffer and copy the image
		sourceR = bounds;
		SetRect( &destR, 0, 0, newWidth, newHeight );
		mSelectionBuffer = inBuffer->CreateSimilarOffscreen( false, newWidth, newHeight );
		
		mSelectionBuffer->CopyFrom( inBuffer, &destR, &sourceR );
	}
	catch( ... )
	{
		this->SelectNone();		// if an error occurs, force no selection or things get weird
		throw;
	}
}


// ============================================================
// 	SetSelection
// ============================================================

void CIconSelection::SetSelection( CIconSelection *inSource )
{
	if ( inSource->IsEmpty() )
	{
		this->SelectNone();
		return;
	}
	
	try
	{
		this->DisposeBuffer();
		
		COffscreen 		*sourceBuffer = inSource->mSelectionBuffer;
		
		mSelectionBuffer = sourceBuffer->CreateSimilarOffscreen( false );
		mSelectionBuffer->CopyFrom( sourceBuffer );
		
		this->SetRawSelection( inSource->GetRegion() );
	}
	catch( ... )
	{
		this->SelectNone();		// if an error occurs, force no selection or things get weird
		throw;
	}
}



// ============================================================
// 	SetRawSelection
// 	
// 	Description:
// 	Copies the region into the internal region structure.
// 	Does not affect the offscreen bitmap at all.
// ============================================================

void CIconSelection::SetRawSelection( RgnHandle inRgn )
{
	if ( !inRgn )
		::SetEmptyRgn( mRegion );
	else
	{
		::CopyRgn( inRgn, mRegion );
		ThrowIfOSErr_( QDError() );
	}
}



// ============================================================
// 	DrawInto
// ============================================================

void CIconSelection::DrawInto( COffscreen *destBuffer )
{
	if ( !mSelectionBuffer || this->IsEmpty() ) return;
	
	Rect		sourceR, destR;

	GetRegionBounds(mRegion, &destR);
	sourceR = destR;
	OffsetRect( &sourceR, -sourceR.left, -sourceR.top );	// move offset to 0,0
		
	mSelectionBuffer->CopyTo( destBuffer, &destR, &sourceR, srcCopy, mRegion );
}


// ============================================================
// 	GetImageBuffer
// ============================================================

COffscreen *CIconSelection::GetImageBuffer()
{
	return( mSelectionBuffer );
}


// ============================================================
// 	CopyToClipboard
// ============================================================

void CIconSelection::CopyToClipboard()
{
	if ( !mSelectionBuffer || this->IsEmpty() ) return;
	
	UGraphicConversion::OffscreenToClipboard( mSelectionBuffer, mRegion );
}


// ============================================================
// 	PasteFromClipboard
// ============================================================

void CIconSelection::PasteFromClipboard( COffscreen *inParentBuffer )
{
	PicHandle		thePict = nil;
	RgnHandle		theRegion = nil;
	
	try
	{
		// Read the picture and (optional) region from the clipboard
		thePict = UGraphicConversion::GetPictFromClipboard();
		theRegion = UGraphicConversion::GetRegionFromClipboard();
		
		// If the region is entirely off-image, move it back
		Rect r = { 0, 0, inParentBuffer->GetHeight(), inParentBuffer->GetWidth() };
		if ( theRegion && !::RectInRgn( &r, theRegion ) ) {
			Rect	bounds;
			GetRegionBounds(theRegion, &bounds);
			::OffsetRgn( theRegion, -bounds.left, -bounds.top );
		}
			
		// Paste it
		this->PastePicture( inParentBuffer, thePict, theRegion );
	}
	catch( ... )
	{
		UIconMisc::DisposeHandle( thePict );
		UIconMisc::DisposeHandle( theRegion );
		throw;
	}

	UIconMisc::DisposeHandle( thePict );
	UIconMisc::DisposeHandle( theRegion );
}


// ============================================================
// 	PastePicture
// ============================================================

void CIconSelection::PastePicture( COffscreen *inParentBuffer, PicHandle inPict, RgnHandle inRegion )
{
	ThrowIfNil_( inParentBuffer );
	ThrowIfNil_( inPict );
	
	this->SelectNone();

	try
	{
			// note: this is after SelectNone() because it might destroy a gworld
		StGWorldSaver	aSaver;
		Rect			r;
		
				// width & height of our buffer match the picture

		SInt32	width = (**inPict).picFrame.right - (**inPict).picFrame.left;
		SInt32	height = (**inPict).picFrame.bottom - (**inPict).picFrame.top;

				// create an offscreen gworld using the paint view's gworld as 
		// a base (use same depth, ctable)

		mSelectionBuffer = inParentBuffer->CreateSimilarOffscreen( false /* device???*/, width, height );

				// image the picture into the offscreen buffer

		mSelectionBuffer->BeginDrawing();
				// should we erase to the background color instead of white? no.
			SetRect( &r, 0, 0, width, height );
			DrawPicture( inPict, &r );
		mSelectionBuffer->EndDrawing();

				// restore the selection area from the clipboard
		// -- if none, use the entire picture frame

		if ( inRegion )
			this->SetRawSelection( inRegion );
		else
		{
			RgnHandle tempRgn = URegionMisc::NewRegionFromRect( r );
			this->SetRawSelection( tempRgn );
			URegionMisc::DisposeRegion( tempRgn );
		}
	}
	catch( ... )
	{
		this->SelectNone();
		throw;
	}
}


// ============================================================
// 	PasteOffscreenBuffer
// ============================================================

void CIconSelection::PasteOffscreenBuffer( COffscreen *inParentBuffer, COffscreen *inBuffer, RgnHandle inRegion )
{
	ThrowIfNil_( inParentBuffer );
	ThrowIfNil_( inBuffer );
	
	this->SelectNone();

	try
	{
			// note: this is after SelectNone() because it might destroy a gworld
		StGWorldSaver	aSaver;
		
				// width & height of our buffer match the picture

		SInt32	width = inBuffer->GetWidth();
		SInt32	height = inBuffer->GetHeight();

				// create an offscreen gworld using the paint view's gworld as 
		// a base (use same depth, ctable)

		mSelectionBuffer = inParentBuffer->CreateSimilarOffscreen( false /* device???*/, width, height );

				// image the picture into the offscreen buffer

		mSelectionBuffer->CopyFrom( inBuffer );

				// restore the selection area from the clipboard
		// -- if none, use the entire picture frame

		if ( inRegion )
			this->SetRawSelection( inRegion );
		else
		{
			RgnHandle tempRgn = URegionMisc::NewRegionFromRect( 0, 0, width, height );
			this->SetRawSelection( tempRgn );
			URegionMisc::DisposeRegion( tempRgn );
		}
	}
	catch( ... )
	{
		this->SelectNone();
		throw;
	}
}


// ============================================================
// 	IsEmpty
// ============================================================

Boolean CIconSelection::IsEmpty()
{
	if ( !mRegion || EmptyRgn(mRegion) )
		return( true );
	else
		return( false );
}


// ============================================================
// 	Offset
// 
// 	Note:
// 	Does not affect the image.
// ============================================================

void CIconSelection::Offset( SInt32 dh, SInt32 dv )
{
	::OffsetRgn( mRegion, dh, dv );
}


// ============================================================
// 	MoveTo
// 
// 	Note:
// 	Does not affect the image.
// ============================================================

void CIconSelection::MoveTo( SInt32 left, SInt32 top )
{
	Rect	bounds;

	GetRegionBounds(mRegion, &bounds);
	this->Offset( left - bounds.left, top - bounds.top );
}


// ============================================================
// 	GetRegion
// ============================================================

RgnHandle CIconSelection::GetRegion()
{
	return( mRegion );
}


// ============================================================
// 	GetCopyOfRegion
// ============================================================

RgnHandle CIconSelection::GetCopyOfRegion()
{
	return URegionMisc::NewRegionFromRegion( mRegion );
}



// ============================================================
// 	PointInSelection
// ============================================================

Boolean CIconSelection::PointInSelection( SInt32 h, SInt32 v )
{
	// if ( this->IsEmpty() ) return( false );
	
	Point	pt;
	SetPt( &pt, h, v );
	return( PtInRgn( pt, mRegion ) );
}

