// ===========================================================================
// CIconSelectionAction.cp
//                       Created: 2004-12-11 18:52:37
//             Last modification: 2004-12-22 18:17:13
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "RezillaConstants.h"
#include "CIconSelectionAction.h"
#include "CMarchingAnts.h"
#include "CIcon_EditorView.h"
#include "CIcon_EditorWindow.h"
#include "COffscreen.h"
#include "CIconSelection.h"

#include <UDrawingState.h>

// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------

CIconSelectionAction::CIconSelectionAction( const SPaintAction &inAction ) : CIconTrackingPaintAction( inAction )
{
	SetRect( &mPrevDrawnRect, 0, 0, 0, 0 );
	SetRect( &mCurrentSelection, 0, 0, 0, 0 );
	mAffectsUndoState = false;					// since we're not undoable
}


// ---------------------------------------------------------------------------
// 	Destructor
// ---------------------------------------------------------------------------

CIconSelectionAction::~CIconSelectionAction()
{
}


// ---------------------------------------------------------------------------
// 	HandleMouseDown
// ---------------------------------------------------------------------------

void
CIconSelectionAction::HandleMouseDown( const SMouseDownEvent &inEvent )
{
	SInt32	rowHit, colHit;
	
			// if the user clicks within the current selection, we will 
		// instantiate a move tool and kill ourselves.

	if ( mSettings.theCanvas->MapPointToCell( inEvent.whereLocal, &colHit, &rowHit ) )
		if ( mSettings.theSelection->PointInSelection( colHit, rowHit ) )
		{
			CIconMoveAction	*theMover = new CIconMoveAction( mSettings );
			ThrowIfMemFail_( theMover );
			delete this;
			theMover->HandleMouseDown( inEvent );
			return;
		}
	
			// we need to draw in xor mode if there's no space between pixels
		// on the canvas. otherwise, we'll draw in patCopy mode because
		// this flickers less.

	mUseXorMode = (mSettings.theCanvas->GetSpaceBetween() == 0);

			// just do the normal mouse tracking stuff

	CIconTrackingPaintAction::HandleMouseDown( inEvent );
}


// ---------------------------------------------------------------------------
// 	MouseInitial
// ---------------------------------------------------------------------------

void
CIconSelectionAction::MouseInitial( const SMouseDownEvent &inEvent, SInt32 /*newCol*/, SInt32 /*newRow*/ )
{
	mMouseDownPt = inEvent.whereLocal;
	mSettings.thePaintView->SelectNone();
}

/*
	Selection rules (according to tests & conversation with Dave Koziol):
	
	The direction the mouse has moved relative to the first pixel
	  is important when determining if a pixel gets selected or not.
	  
	A pixel doesn't get selected if just clicked on, the mouse must move
	  past one of its boundaries.
	  
	The initial pixel clicked on is tricker. It gets selected only if
	  more than 1/2 of it has been enclosed by the selection rect.
*/


// ---------------------------------------------------------------------------
// 	MouseStillDown
// ---------------------------------------------------------------------------

void
CIconSelectionAction::MouseStillDown( const SMouseDownEvent &, 
										Point, Point currentPt,
										SInt32 /*prevCol*/, SInt32 /*prevRow*/,
										SInt32 /*newCol*/, SInt32 /*newRow*/ )
{
	COffscreen		*theImageBuffer = mSettings.currentBuffer;
	COffscreen		*theScratchBuffer = mSettings.scratchBuffer;
	Rect			r, rectToDraw, clipR;
	CIcon_EditorView		*theCanvas = mSettings.theCanvas;
	SInt32			h1, h2, v1, v2;
	Boolean			movingDown, movingRight;
	
			// 1/2 of the cell area is a good amount of slop

	Rect tempR;
	theCanvas->GetPixelRect( 0, 0, &tempR );
	SInt16 slop = MAX( 0, (tempR.right - tempR.left) / 2 );

			// find the cell range that has been hit

	SInt32 	initialCellH, initialCellV;
	SInt32	currentCellH, currentCellV;
	Rect	initialCellR, currentCellR;
	
	theCanvas->MapPointToCell( mMouseDownPt, &initialCellH, &initialCellV, true );
	theCanvas->MapPointToCell( currentPt, &currentCellH, &currentCellV );
	theCanvas->GetPixelRect( initialCellH, initialCellV, &initialCellR, false );
	theCanvas->GetPixelRect( currentCellH, currentCellV, &currentCellR, false );
	
			// find the cell range that should be hilited

	if ( (initialCellH == currentCellH) || (initialCellV == currentCellV) )
	{
		h1 = 0; h2 = 0;			// mouse has to move outside cell to select anything
		v1 = 0; v2 = 0;
	}
	else
	{
		if ( currentCellH > initialCellH )		// moving right
		{
			movingRight = true;
			h1 = initialCellH;
			h2 = currentCellH;
			
			if ( mMouseDownPt.h + slop > initialCellR.right )
				++h1;
		}
		else									// left
		{
			movingRight = false;
			h1 = currentCellH + 1;
			h2 = initialCellH + 1;
			
			if ( mMouseDownPt.h - slop < initialCellR.left )
				--h2;
		}
		
		if ( currentCellV > initialCellV )		// moving down
		{
			movingDown = true;
			v1 = initialCellV;
			v2 = currentCellV;
			
			if ( mMouseDownPt.v + slop > initialCellR.bottom )
				++v1;
		}
		else									// up
		{
			movingDown = false;
			v1 = currentCellV + 1;
			v2 = initialCellV + 1;
			
			if ( mMouseDownPt.v - slop < initialCellR.top )
				--v2;
		}
	}
	
			// snap to a rectangle if the shift key is down
		// (need to handle all 4 combinations of left/right/up/down)

	SInt32 &tempH1 = movingRight ? h1 : h2;
	SInt32 &tempH2 = movingRight ? h2 : h1;
	SInt32 &tempV1 = movingDown ? v1 : v2;
	SInt32 &tempV2 = movingDown ? v2 : v1;
	
	mSnapTo.SnapTo( tempH1, tempV1, tempH2, tempV2, &tempH2, &tempV2 );
	
			// never extend a selection beyond the buffer (except by 1 pixel since
		// we need to enclose the selection)

	r.left = MAX( 0, h1 );
	r.right = MIN( 1 + mSettings.currentBuffer->GetWidth(), h2 );
	r.top = MAX( 0, v1 );
	r.bottom = MIN( 1 + mSettings.currentBuffer->GetHeight(), v2 );

			// prepare to draw the selection

	theCanvas->MapRectToCanvas( r, &rectToDraw );

	theCanvas->FocusDraw();
	StColorPenState		aSaver;
	aSaver.Normalize();
	
	theCanvas->GetInsideDrawingRect( &clipR );
	StClipRgnState	saveSetAndRestore( clipR );

			// even if the rect hasn't changed, we may have to march the ants

	if ( ::EqualRect( &rectToDraw, &mPrevDrawnRect ) ) 
	{
		if ( mMarchingAnts.TimeToDraw() )
		{
			if ( mUseXorMode )				// less flicker if we don't erase (drawing on top anyway)
				this->EraseOldRect();
			this->DrawNewRect( rectToDraw );
		}

		mCurrentSelection = r;
		return;
	}
	
			// mouse has moved, so erase the old rect and draw the new one

	this->EraseOldRect();
	this->DrawNewRect( rectToDraw );
	
	mCurrentSelection = r;					// in source coords -- not canvas
}


// ---------------------------------------------------------------------------
// 	EraseOldRect
// ---------------------------------------------------------------------------

void
CIconSelectionAction::EraseOldRect()
{
	StColorPenState		aPenState;
	aPenState.Normalize();
	
	if ( EmptyRect( &mPrevDrawnRect ) )
		return;
	
	if ( mUseXorMode )
	{
		Pattern		thePattern;
		mMarchingAnts.GetPattern( &thePattern );
		::PenPat( &thePattern );
		::PenMode( patXor );
		::RGBForeColor( &Color_Black );
		::RGBForeColor( &Color_White );
		::FrameRect( &mPrevDrawnRect );
	}
	else
	{
		::RGBForeColor( &Color_White );
		::FrameRect( &mPrevDrawnRect );
	}		
}


// ---------------------------------------------------------------------------
// 	DrawNewRect
// ---------------------------------------------------------------------------

void
CIconSelectionAction::DrawNewRect( const Rect &inRect )
{
	StColorPenState		aPenState;
	aPenState.Normalize();

	if ( mMarchingAnts.TimeToDraw() )
		mMarchingAnts.IncrementPattern();
	
	Pattern		thePattern;
	mMarchingAnts.GetPattern( &thePattern );
	::PenPat( &thePattern );

	if ( mUseXorMode )
		::PenMode( patXor );
	::FrameRect( &inRect );
	
	mPrevDrawnRect = inRect;
}


// ---------------------------------------------------------------------------
// 	MouseFinal
// ---------------------------------------------------------------------------

Boolean
CIconSelectionAction::MouseFinal( const SMouseDownEvent &, 
									Point, Point,
									SInt32, SInt32,
									SInt32, SInt32 )
{
		// don't select anything outside the current image
	mCurrentSelection.top = MAX( 0, mCurrentSelection.top );
	mCurrentSelection.bottom = MIN( mSettings.currentBuffer->GetHeight(), mCurrentSelection.bottom );
	mCurrentSelection.left = MAX( 0, mCurrentSelection.left );
	mCurrentSelection.right = MIN( mSettings.currentBuffer->GetWidth(), mCurrentSelection.right );
	
	if ( !EmptyRect( &mCurrentSelection ) )
	{
			// set the current selection
		mSettings.thePaintView->SetSelection( mCurrentSelection );
	}
	
	return( false );				// not an undoable action
}
