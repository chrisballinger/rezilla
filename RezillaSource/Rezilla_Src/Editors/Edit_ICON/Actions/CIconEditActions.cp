// ===========================================================================
// CIconEditActions.cp
//                       Created: 2004-12-11 18:52:17
//             Last modification: 2004-12-22 16:42:51
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "RezillaConstants.h"
#include "CIconActions.h"
#include "CIconEditActions.h"
#include "CIcon_EditorWindow.h"
#include "CIconSelection.h"
#include "UIconMisc.h"


/*********************
*                    *
*   CIconCutAction   *
*                    *
*********************/
// ---------------------------------------------------------------------------
// 	CIconCutAction											 [constructor]
// ---------------------------------------------------------------------------

CIconCutAction::CIconCutAction( const SPaintAction &inSettings )
				: CIconAction( inSettings, index_UndoCut, true )
{
	this->ThrowIfFileLocked();
}


// ---------------------------------------------------------------------------
// 	CIconCutAction 											 [destructor]
// ---------------------------------------------------------------------------

CIconCutAction::~CIconCutAction()
{
}


// ---------------------------------------------------------------------------
// 	DoIt
// ---------------------------------------------------------------------------

void
CIconCutAction::DoIt()
{
	StGWorldSaver		aSaver;
	
	if ( mSettings.theSelection->IsEmpty() )	// shouldn't happen
	{
		delete this;
		return;
	}
	
	mSettings.thePaintView->CopyToUndo();
	
	mSettings.theSelection->CopyToClipboard();
	mSettings.theSelection->SelectNone();		// bypassing paint view
	mSettings.thePaintView->HandleCanvasDraw();
	
	this->PostAsAction();
}



/**********************
*                     *
*   CIconCopyAction   *
*                     *
**********************/
// ---------------------------------------------------------------------------
// 	CIconCopyAction												 [constructor]
// ---------------------------------------------------------------------------

CIconCopyAction::CIconCopyAction( const SPaintAction &inSettings )
				: CIconAction( inSettings, index_UndoGeneric, true )
{
	mAffectsUndoState = false;
}


// ---------------------------------------------------------------------------
// 	CIconCopyAction 											 [destructor]
// ---------------------------------------------------------------------------

CIconCopyAction::~CIconCopyAction()
{
}


// ---------------------------------------------------------------------------
// 	DoIt
// ---------------------------------------------------------------------------

void
CIconCopyAction::DoIt()
{
	mSettings.theSelection->CopyToClipboard();
	this->PostAsAction();		// will delete this object (mAffectsUndoState == false)
}



/***********************
*                      *
*   CIconPasteAction   *
*                      *
***********************/
// ---------------------------------------------------------------------------
// 	CIconPasteAction											 [constructor]
// ---------------------------------------------------------------------------

CIconPasteAction::CIconPasteAction( const SPaintAction &inSettings )
				: CIconAction( inSettings, index_UndoPaste, true )
{
	this->ThrowIfFileLocked();
}


// ---------------------------------------------------------------------------
// 	CIconPasteAction 											 [destructor]
// ---------------------------------------------------------------------------

CIconPasteAction::~CIconPasteAction()
{
}


// ---------------------------------------------------------------------------
// 	DoIt
// ---------------------------------------------------------------------------

void
CIconPasteAction::DoIt()
{
	mSettings.thePaintView->CopyToUndo();
	
	mSettings.thePaintView->CommitSelection();
	mSettings.thePaintView->ChangeTool( tool_Selection );
	mSettings.theSelection->PasteFromClipboard( mSettings.currentBuffer );
	
	// This erases the old marching ants as well as displaying the new
	// selection
	mSettings.thePaintView->HandleCanvasDraw();
	
	this->PostAsAction();
}


/***********************
*                      *
*   CIconClearAction   *
*                      *
***********************/
// ---------------------------------------------------------------------------
// 	CIconClearAction											 [constructor]
// ---------------------------------------------------------------------------

CIconClearAction::CIconClearAction( const SPaintAction &inSettings )
				: CIconAction( inSettings, index_UndoClear, true )
{
	this->ThrowIfFileLocked();
}


// ---------------------------------------------------------------------------
// 	CIconClearAction 											 [destructor]
// ---------------------------------------------------------------------------

CIconClearAction::~CIconClearAction()
{
}


// ---------------------------------------------------------------------------
// 	DoIt
// ---------------------------------------------------------------------------

void
CIconClearAction::DoIt()
{
	if ( mSettings.theSelection->IsEmpty() )	// shouldn't happen
	{
		delete this;
		return;
	}

	mSettings.thePaintView->CopyToUndo();
	
	mSettings.theSelection->SelectNone();		// bypassing paint view
	mSettings.thePaintView->HandleCanvasDraw();	
	this->PostAsAction();
}

