// ===========================================================================
// CIconLineAction.cp
//                       Created: 2004-12-11 18:52:25
//             Last modification: 2004-12-14 18:52:25
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



// ---------------------------------------------------------------------------
// 	CIconLineAction Constructor
// ---------------------------------------------------------------------------

CIconLineAction::CIconLineAction( const SPaintAction &inAction ) : 
		CIconTrackingPaintAction( inAction, index_UndoLine )
{
	this->ThrowIfFileLocked();
	mScratchBufferHasImage = false;				// no image drawn to scratch buffer yet
	mSnapTo.SetAngle( CSnapTo::kSnapTo45 );		// snap to 45 deg angle if shift key is down
}


// ---------------------------------------------------------------------------
// 	CIconLineAction Destructor
// ---------------------------------------------------------------------------

CIconLineAction::~CIconLineAction()
{
}


// ---------------------------------------------------------------------------
// 	Min3
// ---------------------------------------------------------------------------

static SInt32 Min3( SInt32 a, SInt32 b, SInt32 c )
{
	if ( a < b )
		return( (a < c) ? a : c );
	else
		return( (b < c) ? b : c );
}


// ---------------------------------------------------------------------------
// 	Max3
// ---------------------------------------------------------------------------

static SInt32 Max3( SInt32 a, SInt32 b, SInt32 c )
{
	if ( a > b )
		return( (a > c) ? a : c );
	else
		return( (b > c) ? b : c );
}



// ---------------------------------------------------------------------------
// 	CIconLineAction::MouseStillDown
// ---------------------------------------------------------------------------

void CIconLineAction::MouseStillDown( const SMouseDownEvent &, 
									Point /*prevMousePt*/, Point /*newMousePt*/,
									SInt32 prevCol, SInt32 prevRow,
									SInt32 newCol, SInt32 newRow )
{
	if ( (newCol == prevCol) && (newRow == prevRow) ) 
		return;

	COffscreen *theImageBuffer = mSettings.currentBuffer;
	COffscreen *theScratchBuffer = mSettings.scratchBuffer;

		// put the virgin image into the scratch buffer
	theScratchBuffer->CopyFrom( theImageBuffer );

		// modify the buffer by drawing into it
	theScratchBuffer->BeginDrawing();
	
	::PenNormal();
	
	theScratchBuffer->SetForeColor( mSettings.theForeColor );
	theScratchBuffer->SetBackColor( mSettings.theBackColor );
	
	::MoveTo( mMouseDownCol, mMouseDownRow );
	::LineTo( newCol, newRow );
	
		// draw the image on the screen -- only the changed area for speed
	Rect	updateR;
	updateR.left = Min3( mMouseDownCol, newCol, prevCol );
	updateR.right = 1 + Max3( mMouseDownCol, newCol, prevCol );
	updateR.top = Min3( mMouseDownRow, newRow, prevRow );
	updateR.bottom = 1 + Max3( mMouseDownRow, newRow, prevRow );
	
	mSettings.theCanvas->DrawFrom( theScratchBuffer, &updateR );
	mScratchBufferHasImage = true;
	
	theScratchBuffer->EndDrawing();
}


// ---------------------------------------------------------------------------
// 	CIconLineAction::MouseFinal
// ---------------------------------------------------------------------------

Boolean CIconLineAction::MouseFinal( const SMouseDownEvent &, 
								Point, Point,
								SInt32, SInt32,
								SInt32, SInt32 )
{
	if ( mScratchBufferHasImage )
	{
		mSettings.currentBuffer->CopyFrom( mSettings.scratchBuffer );
		return( true );		// can undo
	}
	
	return( false );		// can't undo since no line was drawn
}


