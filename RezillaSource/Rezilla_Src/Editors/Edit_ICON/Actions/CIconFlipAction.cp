// ===========================================================================
// CIconFlipAction.cp
//                       Created: 2004-12-11 18:52:22
//             Last modification: 2004-12-22 16:50:29
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
// 
// Flipping a Region structure requires drawing it into a 1-bit buffer,
// flipping the pixels, and then calling BitMapToRegion() on the buffer.
// There isn't a better way to do this because the Region structure is not
// documented. (Remember, the lasso isn't rectangular, so we can't assume
// the region doesn't change).

#include "RezillaConstants.h"
#include "CIconActions.h"
#include "CIcon_EditorView.h"
#include "CIcon_EditorWindow.h"
#include "COffscreen.h"
#include "CIconSelection.h"
#include "UIconMisc.h"


// ---------------------------------------------------------------------------
// 	CIconTransformAction										 [constructor]
// ---------------------------------------------------------------------------

CIconTransformAction::CIconTransformAction( const SPaintAction &inAction, SInt16 inStringIndex )
					: CIconAction( inAction, inStringIndex )
{
	this->ThrowIfFileLocked();
}


// ---------------------------------------------------------------------------
// 	CIconTransformAction::DoIt
// ---------------------------------------------------------------------------

void
CIconTransformAction::DoIt()
{
	RgnHandle		newSelectionRgn = nil;
	StGWorldSaver	aSaver;
	
	try
	{
			// flip the selection region and store into newSelectionRgn
		newSelectionRgn = this->CalcNewSelectionRegion();
		if ( !newSelectionRgn ) return;
		
			// copy the current image & selection rgn to the undo area
		mSettings.thePaintView->CopyToUndo();
		
			// transform the bits in the image selection buffer
		this->TransformTheBits( mSettings.theSelection->GetImageBuffer() );
	
			// change the selection region
			// note: we are just changing the region and bypassing the paintview
			//       rather than storing new pixels in the selection buffer
		if ( newSelectionRgn )
			mSettings.theSelection->SetRawSelection( newSelectionRgn );
		
			// redraw the canvas (erases old selection box, etc)
		mSettings.thePaintView->HandleCanvasDraw();
		
			// make sure user can undo us
		this->PostAsAction();
	}
	catch(...)
	{
		if ( newSelectionRgn )
			::DisposeRgn( newSelectionRgn );
		throw;
	}
		
	if ( newSelectionRgn )
		::DisposeRgn( newSelectionRgn );
}


// ---------------------------------------------------------------------------
// 	CIconTransformAction::CalcNewSelectionRegion
// ---------------------------------------------------------------------------

RgnHandle
CIconTransformAction::CalcNewSelectionRegion()
{
	SInt32			width, height;
	SInt32			hOffset, vOffset;
	Rect			theRect;
	COffscreen		*oneBitBuffer = nil;
	RgnHandle		origRgn = nil, maskRgn = nil;
	OSErr			err = noErr;
	
	if ( mSettings.theSelection->IsEmpty() ) return( nil );		// shouldn't happen
	
	origRgn = mSettings.theSelection->GetCopyOfRegion();

	try
	{
		GetRegionBounds(origRgn, &theRect);
		hOffset = theRect.left;
		vOffset = theRect.top;
		OffsetRgn( origRgn, -hOffset, -vOffset );	// 'cause it's relative to paintview, not selection
	
		width = theRect.right;
		height = theRect.bottom;
		
			// draw the selection region into a 1-bit deep buffer
		oneBitBuffer = COffscreen::CreateBuffer( width, height, 1 );
		oneBitBuffer->BeginDrawing();
			PaintRgn( origRgn );
		oneBitBuffer->EndDrawing();
		
			// transform the buffer just like it was the image buffer
		this->TransformTheBits( oneBitBuffer );
		
			// convert the bitmap to a region
		maskRgn = oneBitBuffer->ConvertToRegion();
		
			// put the offset back the way it was before the xform
		OffsetRgn( maskRgn, hOffset, vOffset );
	}
	catch( ... )
	{
		if ( oneBitBuffer ) delete( oneBitBuffer );
		if ( origRgn ) ::DisposeRgn( origRgn );
		if ( maskRgn ) ::DisposeRgn( maskRgn );
		throw;
	}
	
	if ( oneBitBuffer ) delete( oneBitBuffer );
	if ( origRgn ) ::DisposeRgn( origRgn );
	return( maskRgn );
}


// ---------------------- Horizontal ------------------------


// ---------------------------------------------------------------------------
// 	CFlipHorizontalAction											 [constructor]
// ---------------------------------------------------------------------------

CFlipHorizontalAction::CFlipHorizontalAction( const SPaintAction &inAction )
						: CIconTransformAction( inAction, index_UndoFlip )
{
}


// ---------------------------------------------------------------------------
// 	CFlipHorizontalAction::TransformTheBits
// ---------------------------------------------------------------------------

void
CFlipHorizontalAction::TransformTheBits( COffscreen *theBuffer )
{
	Color32				leftPixel, rightPixel;
	SInt32				colsToSwap;
	SInt32				leftCol, rightCol;
	
	SInt32				bufferWidth = theBuffer->GetWidth();
	SInt32				bufferHeight = theBuffer->GetHeight();
	
		// the column counter only has to loop for 1/2 the pixels since
		// we swap 2 pixels with each loop. If the number is odd, the
		// middle pixel doesn't change
	colsToSwap = bufferWidth / 2;

	for ( long rowCount = 0; rowCount < bufferHeight; rowCount++ )
	{
		for ( 	leftCol = 0, rightCol = bufferWidth - 1; 
				leftCol < colsToSwap; 
				leftCol++, rightCol-- )
		{
			leftPixel = theBuffer->GetPixel( leftCol, rowCount );
			rightPixel = theBuffer->GetPixel( rightCol, rowCount );
			theBuffer->SetPixel( leftCol, rowCount, rightPixel );
			theBuffer->SetPixel( rightCol, rowCount, leftPixel );
		}
	}
}



// ---------------------- Vertical ------------------------


// ---------------------------------------------------------------------------
// 	CFlipVerticalAction											 [constructor]
// ---------------------------------------------------------------------------

CFlipVerticalAction::CFlipVerticalAction( const SPaintAction &inAction )
						: CIconTransformAction( inAction, index_UndoFlip )
{
}


// ---------------------------------------------------------------------------
// 	CFlipVerticalAction::TransformTheBits
// ---------------------------------------------------------------------------

void
CFlipVerticalAction::TransformTheBits( COffscreen *theBuffer )
{
	Color32				topPixel, bottomPixel;
	SInt32				rowsToSwap;
	SInt32				topRow, bottomRow;
	
	SInt32				bufferWidth = theBuffer->GetWidth();
	SInt32				bufferHeight = theBuffer->GetHeight();
	
		// the row counter only has to loop for 1/2 the pixels since
		// we swap 2 pixels with each loop. If the number is odd, the
		// middle row doesn't change
	rowsToSwap = bufferHeight / 2;

	for ( 	topRow = 0, bottomRow = bufferHeight - 1;
			topRow < rowsToSwap;
			topRow++, bottomRow-- )
	{
		for ( long colCount = 0; colCount < bufferWidth; colCount++ )
		{
			topPixel = theBuffer->GetPixel( colCount, topRow );
			bottomPixel = theBuffer->GetPixel( colCount, bottomRow );
			theBuffer->SetPixel( colCount, topRow, bottomPixel );
			theBuffer->SetPixel( colCount, bottomRow, topPixel );
		}
	}
}
