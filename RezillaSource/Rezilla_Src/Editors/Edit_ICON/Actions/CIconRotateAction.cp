// ===========================================================================
// CIconRotateAction.cp
//                       Created: 2004-12-11 18:52:35
//             Last modification: 2005-01-02 15:44:12
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
// This code does only +/- 90 degree rotation. I started work on arbitrary
// rotation code but didn't finish it.
// 	
// Rotating a Region structure requires drawing it into a 1-bit buffer,
// rotating the pixels, and then calling BitMapToRegion() on the buffer.
// There isn't a better way to do this because the Region structure is not
// documented. (Remember, the lasso selects non-rectangular areas)


#include "RezillaConstants.h"
#include "CIconActions.h"
#include "CIcon_EditorView.h"
#include "CIcon_EditorWindow.h"
#include "COffscreen.h"
#include "CIconSelection.h"
#include "UColorUtils.h"
#include "UIconMisc.h"
#include "UMiscUtils.h"


// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------

CIconRotateAction::CIconRotateAction( const SPaintAction &inAction, SInt32 degrees )
				: CIconAction( inAction, index_UndoRotate )
{
	this->ThrowIfFileLocked();
	mDegrees = degrees;
}


// ---------------------------------------------------------------------------
// 	DoIt
// ---------------------------------------------------------------------------

void
CIconRotateAction::DoIt()
{
	SInt32			oldWidth, oldHeight;
	SInt32			newWidth, newHeight;
	OSErr			err = noErr;
	Boolean			deleteScratchBuffer = false;
	StGWorldSaver	aSaver;
	
	COffscreen		*oldBuffer = mSettings.theSelection->GetImageBuffer();
	COffscreen		*scratchBuffer = mSettings.scratchBuffer;
	COffscreen		*newBuffer = nil, *maskBuffer = nil;
	
	// Get a copy of the selection region, offset to 0,0
	RgnHandle		selectionRgn = mSettings.theSelection->GetCopyOfRegion();
	Rect			oldSelRect;
	
	::GetRegionBounds(selectionRgn, &oldSelRect);
	::OffsetRgn( selectionRgn, -oldSelRect.left, -oldSelRect.top );		// because it's relative to the paint view

	// Copy the current image & selection area to the undo buffer
	mSettings.thePaintView->CopyToUndo();
	
	// Do the rotation
	try
	{
		oldWidth = oldBuffer->GetWidth();
		oldHeight = oldBuffer->GetHeight();
		
		// Since we only do 90 degree rotations...this calculation is easy
		newWidth = oldHeight;
		newHeight = oldWidth;
		
		// It's possible for someone to have pasted a selection that is
		// larger than the image size. this means that our scratch buffer
		// is too small for the rotate operations. we'll allocate a bigger
		// scratch buffer if needed.
		if ( (oldWidth > scratchBuffer->GetWidth()) || (oldHeight > scratchBuffer->GetHeight()) )
		{
			scratchBuffer = scratchBuffer->CreateSimilarOffscreen( false /* ??? */, oldWidth, oldHeight );
			deleteScratchBuffer = true;
		}
		
		// Draw the selection region into the scratch buffer so we can rotate it
		scratchBuffer->BeginDrawing();
			scratchBuffer->EraseToWhite();
			::PaintRgn( selectionRgn );
		scratchBuffer->EndDrawing();

			// don't need this one anymore
		::DisposeRgn( selectionRgn );
		selectionRgn = nil;
		
		// Allocate a 1-bit deep mask buffer and rotate the selection into
		// it (BitMapToRegion requires a 1-bit buffer)
		maskBuffer = COffscreen::CreateBuffer( newWidth, newHeight, 1 );
		this->TransformTheBits( scratchBuffer, maskBuffer, oldWidth, oldHeight );
		
		// We no longer need our temporary scratch buffer, so get rid of it before we run out of ram
		if ( deleteScratchBuffer && scratchBuffer )
		{
			delete scratchBuffer;
			scratchBuffer = nil;
		}
		
		// Create the new selection region based on this mask
		selectionRgn = maskBuffer->ConvertToRegion();
		
		// Don't need this anymore -- we might need the memory below
		delete maskBuffer;
		maskBuffer = nil;

		// Allocate a new selection buffer
		newBuffer = oldBuffer->CreateSimilarOffscreen( false /* ??? */, newWidth, newHeight );
		this->TransformTheBits( oldBuffer, newBuffer, oldWidth, oldHeight );

		// Change the current selection.
		// Keep the center point where it was before.
		mSettings.theSelection->SetSelection( newBuffer, selectionRgn );	// it will duplicate the offscreen here
		
		SInt32	oldSelCenterH = (oldSelRect.right + oldSelRect.left) / 2;
		SInt32	oldSelCenterV = (oldSelRect.top + oldSelRect.bottom) / 2;
		mSettings.theSelection->Offset( oldSelCenterH - newWidth/2, oldSelCenterV - newHeight / 2 );
		
		// If it's offscreen -- move it on ?
	}
	catch( ... )
	{
		if ( newBuffer ) delete newBuffer;
		if ( maskBuffer ) delete maskBuffer;
		if ( deleteScratchBuffer && scratchBuffer )
			delete scratchBuffer;
		( (Handle) selectionRgn );
		// Dispose of "this" here ???
		throw;
	}

	if ( newBuffer ) delete newBuffer;
	if ( maskBuffer ) delete maskBuffer;
	if ( deleteScratchBuffer && scratchBuffer )
		delete scratchBuffer;
	( (Handle) selectionRgn );

	mSettings.thePaintView->HandleCanvasDraw();
	this->PostAsAction();
}




// ---------------------------------------------------------------------------
// 	TransformTheBits
// ---------------------------------------------------------------------------
// This won't work if the destination is a different depth than the source
// since we use pixel indices rather than RGB values. We *will* work with
// 1-bit destinations, however, since we need this ability.

void
CIconRotateAction::TransformTheBits( COffscreen *source, COffscreen *dest, 
										SInt32 sourceWidth, SInt32 sourceHeight )
{
	SInt32				sourceRow, destRow, sourceCol, destCol;
	SInt32				destWidth = sourceHeight;
	SInt32				destHeight = sourceWidth;
	
	if ( source->GetDepth() != dest->GetDepth() )		// 1-bit case only
	{
		Color32		thePixelColor;
		
		if ( mDegrees == 90 )
		{
			for ( destRow = 0; destRow < destHeight; destRow++ )
			{
				sourceCol = sourceWidth - destRow - 1;
			
				for ( destCol = 0; destCol < destWidth; destCol++ )
				{
					sourceRow = destCol;
					thePixelColor = source->GetPixelColor( sourceCol, sourceRow );
					if ( !UColorUtils::EqualColor32( thePixelColor, kWhiteColor32 ) )
						dest->SetPixel( destCol, destRow, 1 );
				}
			}
		}
		else if ( mDegrees == -90 )
		{
			for ( destRow = 0; destRow < destHeight; destRow++ )
			{
				sourceCol = destRow;
			
				for ( destCol = 0; destCol < destWidth; destCol++ )
				{
					sourceRow = sourceHeight - destCol - 1;
	
					thePixelColor = source->GetPixelColor( sourceCol, sourceRow );
					if ( !UColorUtils::EqualColor32( thePixelColor, kWhiteColor32 ) )
						dest->SetPixel( destCol, destRow, 1 );
				}
			}
		}
	}
	else
	{
		PixelValue		thePixel;
	
		if ( mDegrees == 90 )
		{
			for ( destRow = 0; destRow < destHeight; destRow++ )
			{
				sourceCol = sourceWidth - destRow - 1;
			
				for ( destCol = 0; destCol < destWidth; destCol++ )
				{
					sourceRow = destCol;
					thePixel = source->GetPixel( sourceCol, sourceRow );
					dest->SetPixel( destCol, destRow, thePixel );
				}
			}
		}
		else if ( mDegrees == -90 )
		{
			for ( destRow = 0; destRow < destHeight; destRow++ )
			{
				sourceCol = destRow;
			
				for ( destCol = 0; destCol < destWidth; destCol++ )
				{
					sourceRow = sourceHeight - destCol - 1;
					thePixel = source->GetPixel( sourceCol, sourceRow );
					dest->SetPixel( destCol, destRow, thePixel );
				}
			}
		}
	}
}

