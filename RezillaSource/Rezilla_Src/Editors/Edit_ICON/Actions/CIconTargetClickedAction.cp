// ===========================================================================
// CIconTargetClickedAction.cp
//                       Created: 2004-12-11 18:57:10
//             Last modification: 2004-12-14 18:57:10
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


CIconTargetClickedAction::CIconTargetClickedAction( const SPaintAction &inAction, CDraggableTargetBox *inTargetHit )
	: CIconAction( inAction, index_UndoGeneric ) 

{
	mAffectsUndoState = false;					// since we're not undoable
	mTargetBoxHit = inTargetHit;
}

CIconTargetClickedAction::~CIconTargetClickedAction()
{
}

void CIconTargetClickedAction::DoIt()
{
	CIcon_EditorWindow 			*thePaintView = mSettings.thePaintView;
	CDraggableTargetBox 	*oldBox = thePaintView->GetTargetBox();
	
	if ( oldBox != mTargetBoxHit )
	{
		//thePaintView->CopyToUndo();
		
		thePaintView->SelectNone();				// commit the current selection

		/*
			clear the current undo action because we can't undo once we
			change buffers to a different sample pane.
		*/
		thePaintView->PostAction( nil );
		
		/*
			change the target box, current image, etc, and return
		*/
		thePaintView->SetTargetBox( mTargetBoxHit, redraw_Later );
		this->PostAsAction();
	}
	else
		delete this;			// just a hoax -- don't screw with the current undo state	
}

