// ===========================================================================
// CIconResizeImageAction.cp
//                       Created: 2004-12-11 18:52:32
//             Last modification: 2004-12-14 18:52:32
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CIconResizeImageAction.h"
#include "CResizeDialog.h"


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

void CIconResizeImageAction::DoIt()
{
	CIcon_EditorWindow		*pv = mSettings.thePaintView;
	COffscreen		*cb = mSettings.currentBuffer;
	SInt32			newWidth, newHeight;
	
			// ask the user for a new height & width 

	Boolean okHit = PTResizeDialog::DoResizeDialog(
						cb->GetWidth(), pv->GetMinImageWidth(), pv->GetMaxImageWidth(),
						cb->GetHeight(), pv->GetMinImageHeight(), pv->GetMaxImageHeight(),
						&newWidth, &newHeight );

	if ( !okHit || ((newWidth == cb->GetWidth()) && (newHeight == cb->GetHeight())) )
	{
		delete this;
		return;
	}
	
			// we're memory hungry enough -- clear the selection so we don't
		// have to save it. 
		// 
		// clear the current action as well.

	pv->SelectNone();
	pv->PostAction( nil );
	
			// save off the current state of the window
		// (this includes sample pane location, canvas size, etc, etc)

	mCancelledResize = false;
	mBeforeState.Initialize( pv );
	
			// do the resize operation

	pv->ChangeImageSize( newWidth, newHeight, false );
	
			// save off the current state of the window

	mAfterState.Initialize( pv );
	
			// and we're undoable

	this->PostAsAction();
}


// ---------------------------------------------------------------------------
// 	UndoSelf
// ---------------------------------------------------------------------------

void CIconResizeImageAction::UndoSelf()
{
	mBeforeState.RestoreWindowState();
}


// ---------------------------------------------------------------------------
// 	RedoSelf
// ---------------------------------------------------------------------------

void CIconResizeImageAction::RedoSelf()
{
	mAfterState.RestoreWindowState();
}

