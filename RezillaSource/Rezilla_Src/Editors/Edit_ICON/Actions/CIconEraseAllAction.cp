// ===========================================================================
// CIconEraseAllAction.cp
//                       Created: 2004-12-11 18:52:19
//             Last modification: 2004-12-22 16:44:19
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// ===========================================================================

#include "RezillaConstants.h"
#include "CIconActions.h"
#include "CIcon_EditorView.h"
#include "CIcon_EditorWindow.h"
#include "COffscreen.h"
#include "UIconMisc.h"


// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------

CIconEraseAllAction::CIconEraseAllAction( const SPaintAction &inAction ) : CIconAction( inAction, index_UndoEraseAll )
{
	this->ThrowIfFileLocked();
}


// ---------------------------------------------------------------------------
// 	Destructor
// ---------------------------------------------------------------------------

CIconEraseAllAction::~CIconEraseAllAction()
{
}


// ---------------------------------------------------------------------------
// 	DoIt
// ---------------------------------------------------------------------------

void
CIconEraseAllAction::DoIt()
{
	Rect			r;
	COffscreen		*imageBuffer = mSettings.currentBuffer;
	StGWorldSaver	aSaver;
	
		// copy the current image & selection region to the undo area
	mSettings.thePaintView->CopyToUndo();

		// erase the image buffer to the background color
	imageBuffer->BeginDrawing();

	StColorPenState		aPenState;
	aPenState.Normalize();
	
	//PmForeColor( mSettings.theForeColor );
	//PmBackColor( mSettings.theBackColor );
	imageBuffer->SetForeColor( mSettings.theForeColor );
	imageBuffer->SetBackColor( mSettings.theBackColor );
	SetRect( &r, 0, 0, imageBuffer->GetWidth(), imageBuffer->GetHeight() );
	EraseRect( &r );

		// update the screen
	mSettings.theCanvas->DrawFrom( imageBuffer );
	imageBuffer->EndDrawing();
	
		// post the action for undo support
	this->PostAsAction();
}

