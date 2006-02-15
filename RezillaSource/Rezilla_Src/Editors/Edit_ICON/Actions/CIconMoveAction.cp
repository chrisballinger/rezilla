// ===========================================================================
// CIconMoveAction.cp
//                       Created: 2004-12-11 18:52:26
//             Last modification: 2004-12-22 17:19:55
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// ===========================================================================
// 
// (1)	This can be called one of two ways:
// 		HandleMouseDown (MouseInitial, MouseStillDown, MouseFinal)
// 		Move or MoveTo 
// 	The former is for the mouse, the latter is for the arrow keys
// 	
// (2) This is a bit tricky to keep track of, but does what is
// 	expected of a move tool in a paint program.
// 		  
// 	When a selection is made, the area underneath the selection
// 	is erased to the background color right away. The selection
// 	then floats above this area. If the selection is cut, cleared,
// 	or moved, the backround color shows up. If the selection is
// 	set to none, it replaces the background color.
// 	
// 	This works with moving the selection 1 pixel at a time
// 	via the keyboard too. Only the initial selection area gets
// 	erased. 
// 	
// (3)	Option-drags duplicate the selection. Since we had previously
// 	erased the area to the background color, we "unerase" it by
// 	copying the selection buffer back into the image before starting
// 	the drag.
// 	
// (4) Unlike most other actions, undoing a move undoes all of the
// 	previous moves as well. For example, if the user hits the
// 	up arrow key 4 times and then selects Undo, we restore the
// 	initial state rather than the most recent one.

#include "RezillaConstants.h"
#include "CIconActions.h"
#include "CIconUndoer.h"					// for msg_GetLastCommand
#include "CIcon_EditorView.h"
#include "CIcon_EditorWindow.h"
#include "COffscreen.h"
#include "CIconSelection.h"
#include "UIconMisc.h"


// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------

CIconMoveAction::CIconMoveAction( const SPaintAction &inAction )
				: CIconTrackingPaintAction( inAction, index_UndoMove )
{
	this->ThrowIfFileLocked();

	// Paint view looks at this to see if a move is already in progress
	mActionType = cmd_IconMoveSelection;	
	
	// If previous action was also a move, this particular one will not be
	// undoable because that one will be remembered instead.
	LAction		*lastAction = nil;
	mSettings.thePaintView->ProcessCommand( msg_GetLastCommand, &lastAction );
	
	// Constructor LActions don't have the GetActionType() method, so the
	// dynamic case below is necessary. If ourLastAction is nil, it isn't a
	// CIconAction.
	CIconAction	*ourLastAction = dynamic_cast<CIconAction*>( lastAction );
	if ( ourLastAction && (ourLastAction->GetActionType() == cmd_IconMoveSelection) 
		&& ourLastAction->IsDone() ) {
			// We're not undoable
			mAffectsUndoState = false;
		}
}


// ---------------------------------------------------------------------------
// 	Destructor
// ---------------------------------------------------------------------------

CIconMoveAction::~CIconMoveAction()
{
}


// ---------------------------------------------------------------------------
// 	Move
// ---------------------------------------------------------------------------

void
CIconMoveAction::Move( SInt32 dh, SInt32 dv )
{
	if ( mSettings.theSelection->IsEmpty() )
	{
		delete this;
		return;
	}
	
	Rect		theRect;
	RgnHandle	selRgn = mSettings.theSelection->GetRegion();
	GetRegionBounds(selRgn, &theRect);
	this->MoveTo( theRect.left + dh, theRect.top + dv );
}


// ---------------------------------------------------------------------------
// 	MoveTo
// ---------------------------------------------------------------------------

void
CIconMoveAction::MoveTo( SInt32 left, SInt32 top )
{
	if ( mSettings.theSelection->IsEmpty() )
	{
		delete this;
		return;
	}

	StGWorldSaver	aSaver;
	CIcon_EditorWindow		*thePaintView = mSettings.thePaintView;		// put in local since "this" may go away

	if ( mAffectsUndoState )
		thePaintView->CopyToUndo();
	
	this->MoveToSelf( left, top );
	this->PostAsAction();		// may destroy "this" (so don't use instance vars anymore)
	
	// In the case where the user saves while a move is in progress (using
	// the arrow keys), this flag wasn't being set.
	thePaintView->SetDirty( true );
}


// ---------------------------------------------------------------------------
// 	MoveToSelf
// ---------------------------------------------------------------------------

void
CIconMoveAction::MoveToSelf( SInt32 left, SInt32 top )
{
	// Move the selection region (internal change -- no visuals involved)
	mSettings.theSelection->MoveTo( left, top );
	
	// Copy the "real" image to the scratch buffer
	mSettings.currentBuffer->CopyTo( mSettings.scratchBuffer );
	
	// Draw the selection buffer on top
	mSettings.theSelection->DrawInto( mSettings.scratchBuffer );

	// Blit the combination to the canvas
	mSettings.theCanvas->DrawFrom( mSettings.scratchBuffer );
}


// ---------------------------------------------------------------------------
// 	MouseInitial
// ---------------------------------------------------------------------------

void
CIconMoveAction::MouseInitial( const SMouseDownEvent &inEvent, SInt32 newCol, SInt32 newRow )
{
	Rect		theRect;
	RgnHandle	selectionRgn = mSettings.theSelection->GetRegion();
	
	ThrowIfNil_( selectionRgn );			// shouldn't happen
	
	GetRegionBounds(selectionRgn, &theRect);
	mHOffsetWithinSelection = newCol - theRect.left;
	mVOffsetWithinSelection = newRow - theRect.top;

	if ( inEvent.macEvent.modifiers & shiftKey )
		mSnapTo.SetAngle( CSnapTo::kSnapTo90 );
	else
		mSnapTo.SetAngle( CSnapTo::kDontSnap );
	
	// Option-drag duplicates the current selection. the area underneath
	// the selection has already been erased, so we'll "unerase" it.
	if ( inEvent.macEvent.modifiers & optionKey )
		mSettings.theSelection->DrawInto( mSettings.currentBuffer );	
}


// ---------------------------------------------------------------------------
// 	MouseStillDown
// ---------------------------------------------------------------------------

void
CIconMoveAction::MouseStillDown( const SMouseDownEvent &, 
									Point /*prevMousePt*/, Point /*newMousePt*/,
									SInt32 prevCol, SInt32 prevRow,
									SInt32 newCol, SInt32 newRow )
{
	if ( (newCol == prevCol) && (newRow == prevRow) )
		return;

	this->MoveToSelf( newCol - mHOffsetWithinSelection, newRow - mVOffsetWithinSelection );
}


// ---------------------------------------------------------------------------
// 	PostAsAction
// ---------------------------------------------------------------------------

void
CIconMoveAction::PostAsAction()
{
	// The move action is a bit different than other actions in that it may
	// not be "undoable" but still modifies the image. this is because we
	// undo back to the first move rather than the latest one. since it
	// still modifies the image, we need to update the sample icons. (If
	// we're postable/undoable, the sample view is automatically redrawn
	// anyway, do don't bother to do it twice).
	CIcon_EditorWindow *thePaintView = this->IsPostable() ? nil : mSettings.thePaintView;
	
	// This call may destroy "this", so don't use instance variables afterwards
	CIconTrackingPaintAction::PostAsAction();
	
	if ( thePaintView )
		thePaintView->RedrawSampleView();
}


// ---------------------------------------------------------------------------
// 	MouseFinal
// ---------------------------------------------------------------------------

Boolean
CIconMoveAction::MouseFinal( const SMouseDownEvent &, 
								Point, Point,
								SInt32, SInt32,
								SInt32, SInt32 )
{
	// Whether we can undo depends on whether we copied ourselves into the
	// undo buffer when we were created (if the previous action was
	// anything but a move action).
	return( mAffectsUndoState );
}


