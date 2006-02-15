// ===========================================================================
// CIconDragImageAction.cp
//                       Created: 2004-12-11 18:52:14
//             Last modification: 2004-12-22 15:51:56
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// ===========================================================================

#include "CIconActions.h"
#include "COffscreenDragTask.h"
#include "CIcon_EditorView.h"
#include "CIcon_EditorWindow.h"
#include "COffscreen.h"
#include "CIconSelection.h"


// ---------------------------------------------------------------------------
// 	CIconDragImageAction										[constructor]
// ---------------------------------------------------------------------------

CIconDragImageAction::CIconDragImageAction( const SPaintAction &inAction, SDragImageInfo *info )
		: CIconAction( inAction, index_UndoDrag )
{
	this->ThrowIfFileLocked();
	mDragInfo = *info;
}


// ---------------------------------------------------------------------------
// 	DoIt
// ---------------------------------------------------------------------------

void
CIconDragImageAction::DoIt()
{
	CIcon_EditorWindow	*thePaintView = mSettings.thePaintView;
	CIconSelection		*theSelection = mSettings.theSelection;
	COffscreen 			*currentBuffer = mSettings.currentBuffer;
	
	if ( !thePaintView || !theSelection || !currentBuffer ) return;

	thePaintView->CopyToUndo();
	
	switch( mDragInfo.imageType )
	{
		case ImgType_Picture:
			thePaintView->SelectNone();
			thePaintView->ChangeTool( tool_Selection );
			theSelection->PastePicture( currentBuffer, (PicHandle) mDragInfo.data );
			
			mSettings.theCanvas->Refresh();		// can't redraw now because we'll mess with the drag hilite
			
			this->PostAsAction();
			break;

		case DragFlavor_Offscreen:
			thePaintView->SelectNone();
			thePaintView->ChangeTool( tool_Selection );
			theSelection->PasteOffscreenBuffer( currentBuffer, (COffscreen*) mDragInfo.data );
			
			mSettings.theCanvas->Refresh();		// can't redraw now because we'll mess with the drag hilite
			
			this->PostAsAction();
			break;
	}
}

