// ===========================================================================
// CIconDragImageAction.cp
//                       Created: 2004-12-11 18:52:14
//             Last modification: 2004-12-17 23:06:18
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

// #include "RezillaConstants.h"
#include "CIconActions.h"
#include "COffscreenDragTask.h"


CIconDragImageAction::CIconDragImageAction( const SPaintAction &inAction, SDragImageInfo *info )
		: CIconAction( inAction, index_UndoDrag )
{
	this->ThrowIfFileLocked();
	mDragInfo = *info;
}


// ---------------------------------------------------------------------------
// 	DoIt
// ---------------------------------------------------------------------------
void CIconDragImageAction::DoIt()
{
	CIcon_EditorWindow			*thePaintView = mSettings.thePaintView;
	CIconSelection	*theSelection = mSettings.theSelection;
	COffscreen 		*currentBuffer = mSettings.currentBuffer;
	
	if ( !thePaintView || !theSelection || !currentBuffer ) return;

	thePaintView->CopyToUndo();
	
	switch( mDragInfo.imageType )
	{
		case img_Picture:
			thePaintView->SelectNone();
			thePaintView->ChangeTool( Tool_Selection );
			theSelection->PastePicture( currentBuffer, (PicHandle) mDragInfo.data );
			
			mSettings.theCanvas->Refresh();		// can't redraw now because we'll mess with the drag hilite
			
			this->PostAsAction();
			break;

		case DragFlavor_Offscreen:
			thePaintView->SelectNone();
			thePaintView->ChangeTool( Tool_Selection );
			theSelection->PasteOffscreenBuffer( currentBuffer, (COffscreen*) mDragInfo.data );
			
			mSettings.theCanvas->Refresh();		// can't redraw now because we'll mess with the drag hilite
			
			this->PostAsAction();
			break;
	}
}

