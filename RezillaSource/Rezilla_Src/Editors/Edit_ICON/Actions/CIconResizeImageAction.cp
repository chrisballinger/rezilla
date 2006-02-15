// ===========================================================================
// CIconResizeImageAction.cp
//                       Created: 2004-12-11 18:52:32
//             Last modification: 2005-01-13 21:22:02
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004, 2005
// All rights reserved.
// ===========================================================================

#include "CIconResizeImageAction.h"
#include "CIcon_EditorWindow.h"
#include "COffscreen.h"
#include "UResizeDialog.h"


// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------

CIconResizeImageAction::CIconResizeImageAction( const SPaintAction &inSettings ) :
	CIconAction( inSettings, index_UndoResize )
{
	this->ThrowIfFileLocked();
	mCancelledResize = true;
}


// ---------------------------------------------------------------------------
// 	Destructor
// ---------------------------------------------------------------------------

CIconResizeImageAction::~CIconResizeImageAction()
{
	if ( mCancelledResize )
		return;
	
	if ( this->IsDone() )
		mBeforeState.DeleteAllBuffers();
	else
		mAfterState.DeleteAllBuffers();
}


// ---------------------------------------------------------------------------
// 	DoIt
// ---------------------------------------------------------------------------

void
CIconResizeImageAction::DoIt()
{
	CIcon_EditorWindow	*pv = mSettings.thePaintView;
	COffscreen			*cb = mSettings.currentBuffer;
	SInt32				newWidth, newHeight;
	
	// Ask the user for a new height & width 
	Boolean okHit = UResizeDialog::DoResizeDialog(
						cb->GetWidth(), pv->GetMinImageWidth(), pv->GetMaxImageWidth(),
						cb->GetHeight(), pv->GetMinImageHeight(), pv->GetMaxImageHeight(),
						&newWidth, &newHeight );

	if ( !okHit || ((newWidth == cb->GetWidth()) && (newHeight == cb->GetHeight())) )
	{
		delete this;
		return;
	}
	
	// Clear the selection so we don't have to save it. Clear the current
	// action as well.
	pv->SelectNone();
	pv->PostAction( nil );
	
	// Save off the current state of the window (this includes sample pane
	// location, canvas size, etc, etc)
	mCancelledResize = false;
	mBeforeState.Initialize( pv );
	
	// Do the resize operation
	pv->ChangeImageSize( newWidth, newHeight, false );
	
	// Save off the current state of the window
	mAfterState.Initialize( pv );
	
	// and we're undoable
	this->PostAsAction();
}


// ---------------------------------------------------------------------------
// 	UndoSelf
// ---------------------------------------------------------------------------

void
CIconResizeImageAction::UndoSelf()
{
	mBeforeState.RestoreWindowState();
}


// ---------------------------------------------------------------------------
// 	RedoSelf
// ---------------------------------------------------------------------------

void
CIconResizeImageAction::RedoSelf()
{
	mAfterState.RestoreWindowState();
}

