// ===========================================================================
// CIconDropperAction.cp
//                       Created: 2004-12-11 18:52:17
//             Last modification: 2005-01-02 15:44:19
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "RezillaConstants.h"
#include "CIconActions.h"
#include "CIcon_EditorView.h"
#include "CColorPane.h"
#include "UIconMisc.h"
#include "UMiscUtils.h"


// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------

CIconDropperAction::CIconDropperAction( const SPaintAction &inAction, CColorPane *inForePane, CColorPane *inBackPane ) 
					: CIconTrackingPaintAction( inAction )
{
	mForePane = inForePane;
	mBackPane = inBackPane;
	mAffectsUndoState = false;				// since we're not undoable
}


// ---------------------------------------------------------------------------
// 	Destructor
// ---------------------------------------------------------------------------

CIconDropperAction::~CIconDropperAction()
{
}


// ---------------------------------------------------------------------------
// 	HandleMouseDown
// ---------------------------------------------------------------------------

void
CIconDropperAction::HandleMouseDown( const SMouseDownEvent &inEvent )
{
	Point			pt;
	Color32			newColor;
	StGWorldSaver	aGWorldSaver;

		// get the initial color
	if ( this->GetColorUnderPoint( inEvent.whereLocal, &newColor ) )
		this->ChangeColor( newColor, (inEvent.macEvent.modifiers & shiftKey) ? true : false );
		
		// loop until the mouse is released
	while( StillDown() )
	{
		UIconMisc::GetMouseRelativeToView( mSettings.theCanvas, &pt );	
		
		if ( this->GetColorUnderPoint( pt, &newColor ) )
			this->ChangeColor( newColor, UMiscUtils::IsShiftKey() );
	}
	
		// delete this object (since mAffectsUndoState == false)
	this->PostAsAction();	
}


// ---------------------------------------------------------------------------
// 	ChangeColor
// ---------------------------------------------------------------------------

void
CIconDropperAction::ChangeColor( Color32 inColor, Boolean isShiftDown )
{
	if ( !mForePane || !mBackPane ) return;			// shouldn't happen
	
	if ( isShiftDown )
		mBackPane->SetColor( inColor, redraw_Now );
	else if ( mForePane ) 
		mForePane->SetColor( inColor, redraw_Now );
}

// #ifdef PREV_VERSION
// 
// // ---------------------------------------------------------------------------
// // 	ChangeColor
// // ---------------------------------------------------------------------------
// 
// void CIconDropperAction::ChangeColor( ColorIndex inColor, Boolean isShiftDown )
// {
// 	if ( isShiftDown )
// 	{
// 		if ( mBackPane ) 
// 			mBackPane->SetColor( inColor, true  );
// 	}
// 	else if ( mForePane ) 
// 		mForePane->SetColor( inColor, true  );
// }


