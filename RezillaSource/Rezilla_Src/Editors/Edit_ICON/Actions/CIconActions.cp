// ===========================================================================
// CIconActions.cp
//                       Created: 2004-12-11 18:52:10
//             Last modification: 2004-12-15 19:02:35
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CIconActions.h"
#include "CIconSelection.h"
#include "CColorPane.h"
#include "CSnapTo.h"
#include "CIcon_EditorWindow.h"
#include "CIcon_EditorView.h"
#include "COffscreen.h"
#include "CDraggableTargetView.h"
#include "UIconMisc.h"


// ---------------------------------------------------------------------------
// 	CIconAction											 [constructor]
// ---------------------------------------------------------------------------

CIconAction::CIconAction( const SPaintAction &inSettings, SInt16 inStringIndex, Boolean inDone ) : 
	LAction( STRx_PaintUndo, inStringIndex, inDone )
{
	mSettings = inSettings;
	mActionType = 0;
	mAffectsUndoState = true;	// assume undoable
}


// ---------------------------------------------------------------------------
// 	CIconAction											 [destructor]
// ---------------------------------------------------------------------------

CIconAction::~CIconAction()
{
}


// ---------------------------------------------------------------------------
// 	RedoSelf
// ---------------------------------------------------------------------------

void
CIconAction::RedoSelf()
{
	mSettings.thePaintView->SwapUndoState();
}


// ---------------------------------------------------------------------------
// 	UndoSelf
// ---------------------------------------------------------------------------

void
CIconAction::UndoSelf()
{
	mSettings.thePaintView->SwapUndoState();
}


// ---------------------------------------------------------------------------
// 	PostAsAction
// ---------------------------------------------------------------------------

void
CIconAction::PostAsAction()
{
	if ( mSettings.thePaintView )
	{
			// all undo-able actions set the changed flag
		if ( this->IsPostable() )
		{
			mSettings.thePaintView->SetChangedFlag( true );	
			mSettings.thePaintView->RedrawSampleView();
		}
	
			// note: PostAction might delete "this"
		mSettings.thePaintView->PostAction( this );
	}
}


// ---------------------------------------------------------------------------
// 	GetColorUnderPoint
// ---------------------------------------------------------------------------

Boolean
CIconAction::GetColorUnderPoint( Point inLocal, Color32 *outColor )
{
	SInt32		h, v;
	
	if ( mSettings.theCanvas && mSettings.theCanvas->MapPointToCell( inLocal, &h, &v ) )
	{
		*outColor = mSettings.currentBuffer->GetPixelColor( h, v );
		return( true );
	}
	
	return( false );
}


// ---------------------------------------------------------------------------
// 	DoIt
// ---------------------------------------------------------------------------

void
CIconAction::DoIt()
{
	Throw_( paramErr );			// this should never be called
}


// ---------------------------------------------------------------------------
// 	GetActionType
// ---------------------------------------------------------------------------

MessageT
CIconAction::GetActionType()
{
	return( mActionType );
}


// ---------------------------------------------------------------------------
// 	IsPostable
// ---------------------------------------------------------------------------

Boolean
CIconAction::IsPostable() const
{
	return( mAffectsUndoState );
}


// ---------------------------------------------------------------------------
// 	ThrowIfFileLocked
// ---------------------------------------------------------------------------

void
CIconAction::ThrowIfFileLocked()
{
	if ( mSettings.thePaintView && mSettings.thePaintView->GetLockFlag() )
		Throw_( err_IconFileLocked );
}



/*************************************
*                                    *
*   CIconTrackingPaintAction CLASS   *
*                                    *
*************************************/

// ---------------------------------------------------------------------------
// 	CIconTrackingPaintAction											 [constructor]
// ---------------------------------------------------------------------------

CIconTrackingPaintAction::CIconTrackingPaintAction( const SPaintAction &inAction, SInt16 inStringIndex, Boolean isDone )
									: CIconAction( inAction, inStringIndex, isDone )
{
}


// ---------------------------------------------------------------------------
// 	CIconTrackingPaintAction									 [destructor]
// ---------------------------------------------------------------------------

CIconTrackingPaintAction::~CIconTrackingPaintAction()
{
}


// ---------------------------------------------------------------------------
// 	HandleMouseDown
// ---------------------------------------------------------------------------

void
CIconTrackingPaintAction::HandleMouseDown( const SMouseDownEvent &inMouseDown )
{
	Point				newMousePt, prevMousePt;
	SInt32				prevRow = -1, prevCol = -1, newRow = -1, newCol = -1;
	StGWorldSaver		aSaver;						// save/restore gdevice & port
	
			// see where the mouse went down within the canvas
	
	if ( !mSettings.theCanvas->MapPointToCell( inMouseDown.whereLocal, &mMouseDownCol, &mMouseDownRow ) )
		return;			// missed it
	
			// prepare for drawing
	
	mSettings.currentBuffer->ResetPen();
	mSettings.scratchBuffer->ResetPen();
	
	mSettings.theCanvas->FocusDraw();
	prevMousePt = inMouseDown.whereLocal;
	if ( mAffectsUndoState )
		mSettings.thePaintView->CopyToUndo();
	
			// this lets the subclass know the mouse went down
	
	this->MouseInitial( inMouseDown, mMouseDownCol, mMouseDownRow );
	
			// loop until the mouse is released
	
	while( StillDown() )
	{
				// Get the current mouse location, relative to the superview of the canvas

		UIconMisc::GetMouseRelativeToView( mSettings.theCanvas, &newMousePt );

				// convert this into a col/row within the bitmap

		mSettings.theCanvas->MapPointToCell( newMousePt, &newCol, &newRow );

				// if the shift key is down, snap to the 45 or 90 degrees

		mSnapTo.SnapTo( mMouseDownCol, mMouseDownRow, newCol, newRow, &newCol, &newRow );		
		
				// Call the subclass to handle the tool tracking
	
		this->MouseStillDown( inMouseDown, prevMousePt, newMousePt, prevCol, prevRow, newCol, newRow );

				// prepare for next loop
	
		prevMousePt = newMousePt;
		prevRow = newRow;
		prevCol = newCol;
	}
	
			// Send a final call to the subclass

	mAffectsUndoState = this->MouseFinal( inMouseDown, prevMousePt, newMousePt, prevCol, prevRow, newCol, newRow );

			// this will post the action if undoable, or just delete the object

	this->PostAsAction();
}


// ---------------------------------------------------------------------------
// 	MouseInitial
// ---------------------------------------------------------------------------

void
CIconTrackingPaintAction::MouseInitial( const SMouseDownEvent &, SInt32, SInt32 )
{
}


// ---------------------------------------------------------------------------
// 	MouseStillDown
// ---------------------------------------------------------------------------

void
CIconTrackingPaintAction::MouseStillDown( const SMouseDownEvent &, 
											Point, Point,
											SInt32, SInt32,
											SInt32, SInt32 )
{
}

// ---------------------------------------------------------------------------
// 	MouseFinal
// ---------------------------------------------------------------------------
// 	Returns: true -> can undo, false -> can't undo

Boolean
CIconTrackingPaintAction::MouseFinal( const SMouseDownEvent &, 
											Point, Point,
											SInt32, SInt32,
											SInt32, SInt32 )
{
	return( true );				// default to "undoable"
}

