// ===========================================================================
// CIconDeleteImageAction.cp
//                       Created: 2004-12-11 18:56:54
//             Last modification: 2004-12-22 15:50:18
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CIconActions.h"
#include "CIcon_EditorView.h"
#include "CIcon_EditorWindow.h"
#include "COffscreen.h"
#include "CDraggableTargetView.h"


// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------

CIconDeleteImageAction::CIconDeleteImageAction( const SPaintAction &inAction )
	: CIconAction( inAction, index_UndoDeleteImage )
{
	this->ThrowIfFileLocked();
	mTargetView = inAction.thePaintView->GetTargetView();
}


// ---------------------------------------------------------------------------
// 	Destructor
// ---------------------------------------------------------------------------

CIconDeleteImageAction::~CIconDeleteImageAction()
{
}


// ---------------------------------------------------------------------------
// 	DoIt
// ---------------------------------------------------------------------------

void
CIconDeleteImageAction::DoIt()
{
	if ( !mTargetView || !mTargetView->IsUsed() )				// shouldn't happen
	{
		delete this;
		return;
	}
	
	this->RedoSelf();
	
	// Can't call the normal "PostAsAction" here because it redraws the
	// sample pane and that triggers it to be used again.
	mSettings.thePaintView->PostAction( this );			
}


// ---------------------------------------------------------------------------
// 	RedoSelf
// ---------------------------------------------------------------------------
// 	This deletes the target box.

void
CIconDeleteImageAction::RedoSelf()
{
	if ( !mTargetView ) return;
	
	mSettings.thePaintView->CopyToUndo();
	mSettings.thePaintView->SelectNone();
	
	// Erase the image in the main buffer and target box. Note that
	// mSettings.theImageBuffer may no longer be correct here, so be sure
	// to get the correct one from the paint view.
	COffscreen	*imageBuffer = mSettings.thePaintView->GetImageBuffer();
	imageBuffer->EraseToWhite();
	mTargetView->CopyBufferFrom( imageBuffer, redraw_Dont );

	// The target is now unused
	mTargetView->SetUsedFlag( false, redraw_Now );
	
	// Update the screen
	mSettings.thePaintView->HandleCanvasDraw();
}

