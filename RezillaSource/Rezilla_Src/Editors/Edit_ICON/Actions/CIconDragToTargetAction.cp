// ===========================================================================
// CIconDragToTargetAction.cp
//                       Created: 2004-12-11 18:52:15
//             Last modification: 2004-12-22 16:32:23
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "RezillaConstants.h"
#include "CIconDragToTargetAction.h"
#include "CIcon_EditorView.h"
#include "CIcon_EditorWindow.h"
#include "COffscreen.h"
#include "UGraphicConversion.h"
#include "UMessageDialogs.h"


// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------

CIconDragToTargetAction::CIconDragToTargetAction( 
								const SPaintAction &inAction, 
								SImageDropOnTargetBox *inDropInfo )
	: CIconAction( inAction, index_UndoDrag )
{
	mDropInfo = *inDropInfo;
}


// ---------------------------------------------------------------------------
// 	Destructor
// ---------------------------------------------------------------------------

CIconDragToTargetAction::~CIconDragToTargetAction()
{
}


// ---------------------------------------------------------------------------
// 	DoIt
// ---------------------------------------------------------------------------
// This doesn't fully undo -- undoing would involve a two-step process of
// undoing the new image *and* reverting the previous image as well.
// This will deallocate any pictures passed in, but not offscreen buffers
// because they are probably in use within the editor.
// We not delete the picture or passed offscreen buffer -- this is handled
// by the drag & drop code.

void
CIconDragToTargetAction::DoIt()
{
	CIcon_EditorWindow 			*thePaintView = mSettings.thePaintView;
	CDraggableTargetBox 	*oldBox = thePaintView->GetTargetBox();
	CDraggableTargetBox	*newBox = mDropInfo.thePane;
	COffscreen				*downSampledBuffer = nil, *sourceBuffer = nil;
	Boolean					deleteSourceBuffer = false;
	
	try
	{
		if ( thePaintView->GetLockFlag() )
			Throw_( err_IconFileLocked );
			
		// If a picture was dropped, draw it into a buffer
		if ( mDropInfo.theBuffer )
			sourceBuffer = mDropInfo.theBuffer;
		else
		{
			sourceBuffer = UGraphicConversion::PictureToOffscreen( mDropInfo.thePicture );
			deleteSourceBuffer = true;
		}
		
		// Allocate a buffer with the same depth & color table as the pane
		// the image was dropped on. this will map colors to the pane's
		// depth & color table, plus scale the image.
		COffscreen *paneBuffer = mDropInfo.thePane->GetBuffer();
		ThrowIfNil_( paneBuffer );
		downSampledBuffer = paneBuffer->CreateSimilarOffscreen();
		
		if ( newBox->IsMask() )
			this->GenerateMask( sourceBuffer, downSampledBuffer );
		else
			downSampledBuffer->CopyFrom( sourceBuffer );
	
		// Commit the current selection
		thePaintView->SelectNone();				// commit the current selection
		thePaintView->PostAction( nil );		// in case of error -- can't undo anything right now

		// Change the current sample pane: this is needed up here in order
		// to use CopyToUndo. This may change the current buffer, so don't
		// use mSettings.currentBuffer, etc after this point.
		if ( newBox != oldBox )
			thePaintView->SetTargetBox( mDropInfo.thePane, redraw_Later );
		
		thePaintView->CopyToUndo();
	
		// Copy to the main image. mSettings.currentBuffer can't be used.
		COffscreen *latestImageBuffer = mSettings.thePaintView->GetImageBuffer();
		if ( latestImageBuffer )
			latestImageBuffer->CopyFrom( downSampledBuffer );
		
// 		#ifdef NOT_NEEDED
// 		// This erases the old marching ants (if any) as well as displaying
// 		// the new selection
// 		thePaintView->HandleCanvasDraw();
		
		// Do a refresh rather than a draw here because the canvas might've
		// changed size and we needed to post an update event anyway. this
		// prevents drawing twice.
		mSettings.theCanvas->Refresh();
		
		// Now we're done
		this->PostAsAction();
	}
	catch( long inErr )
	{
		if ( deleteSourceBuffer ) delete sourceBuffer;
		delete downSampledBuffer;
		
		// We can't display errors during drag & drop, so we'll postpone it
		// until idle time
		UMessageDialogs::DisplayPostponedError(CFSTR("ErrorWithIconEditor"), inErr );
	}
	catch( ... )
	{
		// Somebody threw something we didn't understand...
		UMessageDialogs::DisplayPostponedError(CFSTR("ErrorWithIconEditor"), err_IconGeneric );
	}
	
	if ( deleteSourceBuffer ) delete sourceBuffer;
	delete downSampledBuffer;
}



// ---------------------------------------------------------------------------
// 	GenerateMask
// ---------------------------------------------------------------------------

void
CIconDragToTargetAction::GenerateMask(	COffscreen *inSource, 
												COffscreen *inDest )
{
	SInt32			sourceWidth = inSource->GetWidth();
	SInt32			sourceHeight = inSource->GetHeight();
	SInt32			destWidth = inDest->GetWidth();
	SInt32			destHeight = inDest->GetHeight();
	
	Boolean			createdTempBuffer = false;
	COffscreen		*sourceBuffer;
	BitMap			aBitMap;
	
	// If the incoming buffer isn't 1-bit or the correct size, create a
	// temp buffer that is more useful to us. Note that rather than just
	// using CopyBits(), this will map all colors other than the background
	// color to black.
	if ( (inSource->GetDepth() != 1) || (sourceWidth != destWidth) || (sourceHeight != destHeight) )
	{
		sourceBuffer = COffscreen::CreateBuffer( destWidth, destHeight, 1 );
		createdTempBuffer = true;
		sourceBuffer->CopyFromAndDownSample( inSource, kWhiteColor32, kBlackColor32 );
	}
	else
		sourceBuffer = inSource;
	
	// The extra braces below are needed because StHandleLocker will
	// restore the handle flags and the buffer _may_ be deleted in the code
	// just below this block.
	{
		// Get the pixmaps and lock them and their bits

		PixMapHandle		sourceMap = sourceBuffer->GetPixMap();
		StHandleLocker		lock1( (Handle) sourceMap );

		PixMapHandle		destMap = inDest->GetPixMap();
		StHandleLocker		lock2( (Handle) destMap );

		// CalcCMask is too stupid to take a pixmap as the 2nd parameter.
		// We'll setup a bitmap structure and use it instead.
		// (apparently, the hi bits of rowBytes screw it up 'cause it doesn't work)
		aBitMap.bounds = (**destMap).bounds;
		aBitMap.baseAddr = ::GetPixBaseAddr( destMap );
		aBitMap.rowBytes = (**destMap).rowBytes & 0x3FFF;

		// Call CalcCMask to calculate the interior pixels black
		RGBColor	seedRGB = { 0, 0, 0 };
		Rect		r;
		SetRect( &r, 0, 0, destWidth, destHeight );
		::CalcCMask( (BitMap*) *sourceMap, &aBitMap, &r, &r, &seedRGB, nil, 0 );
	}
	
	// Cleanup
	if ( createdTempBuffer && sourceBuffer )
		delete sourceBuffer;
}

