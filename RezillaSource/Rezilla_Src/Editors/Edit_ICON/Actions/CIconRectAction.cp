// ===========================================================================
// CIconRectAction.cp
//                       Created: 2004-12-11 18:52:31
//             Last modification: 2004-12-14 15:18:09
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "RezillaConstants.h"
#include "CIconActions.h"

#include <UDrawingState.h>

// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------

CIconRectAction::CIconRectAction( const SPaintAction &inAction, Boolean inFill, ResIDT inUndoIndex ) : 
		CIconTrackingPaintAction( inAction, inUndoIndex )
{
	this->ThrowIfFileLocked();

	mFilled = inFill;
	mScratchBufferHasImage = false;			// nothing drawn into scratch buffer yet
}


// ---------------------------------------------------------------------------
// 	Destructor
// ---------------------------------------------------------------------------

CIconRectAction::~CIconRectAction()
{
}


// ---------------------------------------------------------------------------
// 	CIconRectAction::MouseStillDown
// ---------------------------------------------------------------------------

void CIconRectAction::MouseStillDown( const SMouseDownEvent &, 
									Point /*prevMousePt*/, Point /*newMousePt*/,
									SInt32 prevCol, SInt32 prevRow,
									SInt32 newCol, SInt32 newRow )
{
	if ( (newCol == prevCol) && (newRow == prevRow) ) 
		return;

	COffscreen 	*theImageBuffer = mSettings.currentBuffer;
	COffscreen 	*theScratchBuffer = mSettings.scratchBuffer;
	Rect			r;
	
		// put the virgin image into the scratch buffer
	theScratchBuffer->CopyFrom( theImageBuffer );

		// modify the image buffer by drawing into it
	theScratchBuffer->BeginDrawing();
	
	theScratchBuffer->SetForeColor( mSettings.theForeColor );
	theScratchBuffer->SetBackColor( mSettings.theBackColor );
	
	r.top = MIN( mMouseDownRow, newRow );
	r.bottom = 1 + MAX( mMouseDownRow, newRow );
	r.left = MIN( mMouseDownCol, newCol );
	r.right = 1 + MAX( mMouseDownCol, newCol );
	
		// this will draw the rectangle, oval, or round-rect into the buffer
	this->DrawShape( r );
	
		// indicate that we've drawn something into the buffer
	mScratchBufferHasImage = true;	
	
		// draw the image on the screen
		// for speed, only update the required portion -- the union of the
		// new rectangle and the old one
	Rect	unionR;
	
	unionR.top = MIN( r.top, prevRow );
	unionR.bottom = MAX( r.bottom, prevRow + 1 );
	unionR.left = MIN( r.left, prevCol );
	unionR.right = MAX( r.right, prevCol + 1 );

	mSettings.theCanvas->DrawFrom( theScratchBuffer, &unionR );
	theScratchBuffer->EndDrawing();
}


// ---------------------------------------------------------------------------
// 	CIconRectAction::DrawShape
// ---------------------------------------------------------------------------

void CIconRectAction::DrawShape( const Rect &r )
{
	if ( mFilled )
	{
		PenPat( &mSettings.thePattern );
		PaintRect( &r );
	}
	else
		FrameRect( &r );
}


// ---------------------------------------------------------------------------
// 	CIconRectAction::MouseFinal
// ---------------------------------------------------------------------------

Boolean CIconRectAction::MouseFinal( const SMouseDownEvent &, 
								Point, Point,
								SInt32, SInt32,
								SInt32, SInt32 )
{
	if ( mScratchBufferHasImage )
	{
		mSettings.currentBuffer->CopyFrom( mSettings.scratchBuffer );
		return( true );				// can undo
	}
	
	return( false );				// can't undo
}

