// ===========================================================================
// CIconTargetClickedAction.cp
//                       Created: 2004-12-11 18:57:10
//             Last modification: 2004-12-22 18:19:46
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "RezillaConstants.h"
#include "CIconTargetClickedAction.h"
#include "CIcon_EditorWindow.h"


// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------

CIconTargetClickedAction::CIconTargetClickedAction( const SPaintAction &inAction, CDraggableTargetView *inTargetHit )
	: CIconAction( inAction, index_UndoGeneric ) 

{
	mAffectsUndoState = false;			// since we're not undoable
	mTargetViewHit = inTargetHit;
}


// ---------------------------------------------------------------------------
// 	Destructor
// ---------------------------------------------------------------------------

CIconTargetClickedAction::~CIconTargetClickedAction()
{
}


// ---------------------------------------------------------------------------
// 	DoIt
// ---------------------------------------------------------------------------

void
CIconTargetClickedAction::DoIt()
{
	CIcon_EditorWindow 			*thePaintView = mSettings.thePaintView;
	CDraggableTargetView 	*oldBox = thePaintView->GetTargetView();
	
	if ( oldBox != mTargetViewHit )
	{
		//thePaintView->CopyToUndo();
		
		thePaintView->SelectNone();				// commit the current selection

		// Clear the current undo action because we can't undo once we
		// change buffers to a different sample pane.
		thePaintView->PostAction( nil );
		
		// Change the target box, current image, etc, and return
		thePaintView->SetTargetView( mTargetViewHit, redraw_Later );
		this->PostAsAction();
	}
	else
		delete this;			// just a hoax -- don't screw with the current undo state	
}

