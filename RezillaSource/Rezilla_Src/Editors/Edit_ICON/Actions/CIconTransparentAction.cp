// ===========================================================================
// CIconTransparentAction.cp
//                       Created: 2004-12-11 18:52:43
//             Last modification: 2004-12-22 18:23:34
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// ===========================================================================
// The "Make Transparent" action removes every background-colored pixel
// from the current selection. This is especially useful when pasting an
// object into the paint view and you don't want to obscure everything
// beneath it.


#include "RezillaConstants.h"
#include "CIconActions.h"
#include "CIcon_EditorView.h"
#include "CIcon_EditorWindow.h"
#include "COffscreen.h"
#include "CIconSelection.h"
#include "UIconMisc.h"
#include "UColorUtils.h"


// ---------------------------------------------------------------------------
// 	CIconTransparentAction										 [constructor]
// ---------------------------------------------------------------------------

CIconTransparentAction::CIconTransparentAction( const SPaintAction &inAction )
					: CIconAction( inAction, index_UndoTransparent )
{
	this->ThrowIfFileLocked();
};


// ---------------------------------------------------------------------------
// 	CIconTransparentAction::DoIt
// ---------------------------------------------------------------------------

void
CIconTransparentAction::DoIt()
{
	StGWorldSaver		aSaver;
	OSErr				err = noErr;
	Rect				r;
	RgnHandle			oldSelectionRgn = nil, newSelectionRgn = nil;
	Rect				theRect;
	COffscreen			*selectionBuffer = mSettings.theSelection->GetImageBuffer();
	COffscreen			*scratchBuffer = mSettings.scratchBuffer;
	Boolean				deleteScratchBuffer = false;
	
	mSettings.thePaintView->CopyToUndo();

	try
	{
		SInt32	oldWidth = selectionBuffer->GetWidth();
		SInt32	oldHeight = selectionBuffer->GetHeight();
		SetRect( &r, 0, 0, oldWidth, oldHeight );
		
		// Get the background color as an Color32 value -- all compares are
		// in RGB space because that's what the user sees as the color
		// (there could be duplicate rgb values in the color table).

		//selectionBuffer->IndexToRGB( mSettings.theBackColor, &theBackRGB );

		// Get the current selection region and make it 0,0 based
		oldSelectionRgn = mSettings.theSelection->GetCopyOfRegion();
		::GetRegionBounds(oldSelectionRgn, &theRect);
		SInt32 hOffset = theRect.left;
		SInt32 vOffset = theRect.top;
		::OffsetRgn( oldSelectionRgn, -hOffset, -vOffset );
	
		// It's possible for someone to have pasted a selection that is
		// larger than the image size. this means that our scratch buffer
		// is too small for the rotate operations. we'll allocate a bigger
		// scratch buffer if needed.
		if ( (oldWidth > scratchBuffer->GetWidth()) || (oldHeight > scratchBuffer->GetHeight()) )
		{
			scratchBuffer = scratchBuffer->CreateSimilarOffscreen( false /* ??? */, oldWidth, oldHeight );
			deleteScratchBuffer = true;
		}
		
		// Set each pixel in the scratch buffer to black or white.
		// White: pixels that are outside the selection or in the background color
		// Black: pixels within the selection that are not the background color
		scratchBuffer->ResetColors();
		scratchBuffer->EraseToWhite();
		
		PixelValue		blackPixelValue = scratchBuffer->RGBToPixelValue( Color_Black );
		Color32			thePixelColor;
	
		for ( long rowCount = 0; rowCount < oldHeight; rowCount++ )
			for ( long colCount = 0; colCount < oldWidth; colCount++ )
			{
				thePixelColor = selectionBuffer->GetPixelColor( colCount, rowCount );
				
				if ( !UColorUtils::EqualColor32( thePixelColor, mSettings.theBackColor ) )
				{
					Point	pt;
					::SetPt( &pt, colCount, rowCount );
					if ( ::PtInRgn( pt, oldSelectionRgn ) )		// do this faster way ???
						scratchBuffer->SetPixel( colCount, rowCount, blackPixelValue );
				}
			}
		
		// Convert the bitmap into the new selection region
		newSelectionRgn = scratchBuffer->ConvertToRegion();
		
		// Need to copy the original image into the scratch buffer because
		// selectionBuffer will be deleted by SetSelection
		scratchBuffer->CopyFrom( selectionBuffer, &r, &r, srcCopy );
		
		mSettings.theSelection->SetSelection( scratchBuffer, newSelectionRgn );
		mSettings.theSelection->Offset( hOffset, vOffset );
		
		// Redraw the screen & post this action		
		mSettings.thePaintView->HandleCanvasDraw();
		this->PostAsAction();
	}
	catch( ... )
	{
		if ( oldSelectionRgn ) ::DisposeRgn( oldSelectionRgn );
		if ( newSelectionRgn ) ::DisposeRgn( newSelectionRgn );
		if ( deleteScratchBuffer && scratchBuffer )	delete scratchBuffer;
			// delete "this" ?
		throw;
	}

	if ( oldSelectionRgn ) ::DisposeRgn( oldSelectionRgn );
	if ( newSelectionRgn ) ::DisposeRgn( newSelectionRgn );
	if ( deleteScratchBuffer && scratchBuffer )	delete scratchBuffer;
}


