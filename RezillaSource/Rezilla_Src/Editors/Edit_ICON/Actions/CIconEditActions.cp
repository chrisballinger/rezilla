// ===========================================================================
// CIconEditActions.cp
//                       Created: 2004-12-11 18:52:17
//             Last modification: 2004-12-14 18:52:17
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


// ---------------------------------------------------------------------------
// 	CutAction Constructor
// ---------------------------------------------------------------------------

CIconCutAction::CIconCutAction( const SPaintAction &inSettings )
				: CIconAction( inSettings, index_UndoCut, true )
{
	this->ThrowIfFileLocked();
}


// ---------------------------------------------------------------------------
// 	CutAction Destructor
// ---------------------------------------------------------------------------

CIconCutAction::~CIconCutAction()
{
}


// ---------------------------------------------------------------------------
// 	CutAction::DoIt
// ---------------------------------------------------------------------------

void CIconCutAction::DoIt()
{
	StGWorldSaver		aSaver;
	
	if ( mSettings.theSelection->IsEmpty() )		// shouldn't happen
	{
		delete this;
		return;
	}
	
	mSettings.thePaintView->CopyToUndo();
	
	mSettings.theSelection->CopyToClipboard();
	mSettings.theSelection->SelectNone();		// note: bypassing paint view
	mSettings.thePaintView->HandleCanvasDraw();
	
	this->PostAsAction();
}

	// ------------------ CIconCopyAction --------------------

// ---------------------------------------------------------------------------
// 	CopyAction Constructor
// ---------------------------------------------------------------------------

CIconCopyAction::CIconCopyAction( const SPaintAction &inSettings )
				: CIconAction( inSettings, index_UndoGeneric, true )
{
	mAffectsUndoState = false;
}


// ---------------------------------------------------------------------------
// 	CopyAction Destructor
// ---------------------------------------------------------------------------

CIconCopyAction::~CIconCopyAction()
{
}


// ---------------------------------------------------------------------------
// 	CopyAction::DoIt
// ---------------------------------------------------------------------------

void CIconCopyAction::DoIt()
{
	mSettings.theSelection->CopyToClipboard();
	this->PostAsAction();		// will delete this object (mAffectsUndoState == false)
}

	// ------------------ CIconPasteAction --------------------

// ---------------------------------------------------------------------------
// 	CIconPasteAction Constructor
// ---------------------------------------------------------------------------

CIconPasteAction::CIconPasteAction( const SPaintAction &inSettings )
				: CIconAction( inSettings, index_UndoPaste, true )
{
	this->ThrowIfFileLocked();
}


// ---------------------------------------------------------------------------
// 	CIconPasteAction Destructor
// ---------------------------------------------------------------------------

CIconPasteAction::~CIconPasteAction()
{
}


// ---------------------------------------------------------------------------
// 	CIconPasteAction::DoIt
// ---------------------------------------------------------------------------

void CIconPasteAction::DoIt()
{
	mSettings.thePaintView->CopyToUndo();
	
	mSettings.thePaintView->CommitSelection();	// 8/29/96 ebs fix
	mSettings.thePaintView->ChangeTool( Tool_Selection );
	mSettings.theSelection->PasteFromClipboard( mSettings.currentBuffer );
	
		// this erases the old marching ants as well as displaying
		// the new selection
	mSettings.thePaintView->HandleCanvasDraw();
	
	this->PostAsAction();
}

	// ------------------ CIconClearAction --------------------

// ---------------------------------------------------------------------------
// 	CIconClearAction Constructor
// ---------------------------------------------------------------------------

CIconClearAction::CIconClearAction( const SPaintAction &inSettings )
				: CIconAction( inSettings, index_UndoClear, true )
{
	this->ThrowIfFileLocked();
}


// ---------------------------------------------------------------------------
// 	CIconClearAction Destructor
// ---------------------------------------------------------------------------

CIconClearAction::~CIconClearAction()
{
}


// ---------------------------------------------------------------------------
// 	CIconClearAction::DoIt
// ---------------------------------------------------------------------------

void CIconClearAction::DoIt()
{
	if ( mSettings.theSelection->IsEmpty() )		// shouldn't happen
	{
		delete this;
		return;
	}

	mSettings.thePaintView->CopyToUndo();
	
	mSettings.theSelection->SelectNone();		// note: bypassing paint view
	mSettings.thePaintView->HandleCanvasDraw();	
	this->PostAsAction();
}

