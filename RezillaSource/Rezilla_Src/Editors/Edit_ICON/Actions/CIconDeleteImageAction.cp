// ===========================================================================
// CIconDeleteImageAction.cp
//                       Created: 2004-12-11 18:56:54
//             Last modification: 2004-12-14 18:56:54
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CIconActions.h"
#include "CDraggableTargetBox.h"


// ============================================================
// 	Constructor
// ============================================================

CIconDeleteImageAction::CIconDeleteImageAction( const SPaintAction &inAction )
	: CIconAction( inAction, index_UndoDeleteImage )
{
	this->ThrowIfFileLocked();
	mTargetBox = inAction.thePaintView->GetTargetBox();
}


// ============================================================
// 	Destructor
// ============================================================

CIconDeleteImageAction::~CIconDeleteImageAction()
{
}


// ============================================================
// 	DoIt
// ============================================================

void CIconDeleteImageAction::DoIt()
{
	if ( !mTargetBox || !mTargetBox->IsUsed() )				// shouldn't happen
	{
		delete this;
		return;
	}
	
	this->RedoSelf();
	
	/*
		note:
		can't call the normal "PostAsAction" here because it redraws
		the sample pane and that triggers it to be used again.
	*/
	mSettings.thePaintView->SetChangedFlag( true );
	mSettings.thePaintView->PostAction( this );			
}


// ============================================================
// 	RedoSelf
// 	
// 	Description:
// 	This deletes the target box.
// ============================================================

void CIconDeleteImageAction::RedoSelf()
{
	if ( !mTargetBox ) return;
	
	mSettings.thePaintView->CopyToUndo();
	mSettings.thePaintView->SelectNone();
	
	/*
		erase the image in the main buffer and target box.
		note that mSettings.theImageBuffer may no longer be correct here, so be
		   sure to get the correct one from the paint view.
	*/
	COffscreen	*imageBuffer = mSettings.thePaintView->GetImageBuffer();
	imageBuffer->EraseToWhite();
	mTargetBox->CopyBufferFrom( imageBuffer, redraw_Dont );

	/*
		the target is now unused
	*/
	mTargetBox->SetUsedFlag( false, redraw_Now );
	
		// update the screen
	mSettings.thePaintView->HandleCanvasDraw();
}

