// ===========================================================================
// CHexEditorActions.cp 
//                       Created: 2003-05-29 21:13:13
//             Last modification: 2005-05-24 15:58:23
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2003-2004, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

// Custom headers
#include "WASTE.h"
#include "CHexEditorActions.h"
#include "CWasteEditView.h"
#include "RezillaConstants.h"
#include "UCodeTranslator.h"

// PowerPlant headers
#include <LCommander.h>
#include <LPane.h>
#include <PP_KeyCodes.h>
#include <PP_Messages.h>
#include <PP_Resources.h>
#include <UMemoryMgr.h>
#include <UScrap.h>

// Universal headers
#include <Fonts.h>

PP_Begin_Namespace_PowerPlant


#pragma mark -

// ---------------------------------------------------------------------------
//	¥ CHexEditorCutAction						Constructor				  [public]
// ---------------------------------------------------------------------------

CHexEditorCutAction::CHexEditorCutAction(
	WEReference		inWERef,
	LCommander*		inTextCommander,
	LPane*			inTextPane)

	: CWEViewCutAction(inWERef, inTextCommander, inTextPane)
{
}


// ---------------------------------------------------------------------------
//	¥ RedoSelf
// ---------------------------------------------------------------------------

void
CHexEditorCutAction::RedoSelf()
{
	StFocusAndClipIfHidden	focus(mWEView);

	LongRect theOldRect;
	WEGetDestRect(&theOldRect,mWERef);

	WESetSelection(mSelStart, mSelEnd, mWERef);
	WEDelete(mWERef);

	// Strip blanks from deleted text
	UInt16 thePeriod = ( mWEView->GetPaneID() == item_HexDataWE ) ? 3:2 ;
	StStripPeriodicalTranslator blankstripper(mDeletedTextH, thePeriod);
	blankstripper.FilterOutPeriodical();
	
	// Put deleted text on clipboard
	UScrap::SetData(ResType_Text, blankstripper.GetOutHandle());
	
	mWEView->ForceAutoScroll(theOldRect);
}

#pragma mark -

// ---------------------------------------------------------------------------
//	¥ CHexEditorPasteAction					Constructor				  [public]
// ---------------------------------------------------------------------------

CHexEditorPasteAction::CHexEditorPasteAction(
	WEReference		inWERef,
	LCommander*		inTextCommander,
	LPane*			inTextPane)

	: CWEViewPasteAction(inWERef, inTextCommander, inTextPane)
{
	// Convert mPastedTextH
	PaneIDT thePaneID = mWEView->GetPaneID();

	switch (thePaneID) {
	  case item_HexDataWE:
	StSepHexTranslator translator(mPastedTextH);
	translator.Convert();
	mPastedTextH = translator.GetOutHandle();
	  
		break;
		
	  case item_TxtDataWE:
		break;
		
	}
	
	
}


// ---------------------------------------------------------------------------
//	¥ ~CHexEditorPasteAction					Destructor				  [public]
// ---------------------------------------------------------------------------

CHexEditorPasteAction::~CHexEditorPasteAction()
{
}


// ---------------------------------------------------------------------------
//	¥ RedoSelf
// ---------------------------------------------------------------------------

void
CHexEditorPasteAction::RedoSelf()
{
	StFocusAndClipIfHidden	focus(mWEView);

	LongRect theOldRect;
	WEGetDestRect(&theOldRect,mWERef);

	if (mSelStart != mSelEnd) {
		WESetSelection(mSelStart, mSelEnd, mWERef);
	}

	WEDelete(mWERef);
	StHandleLocker	lock(mPastedTextH);
	mWEView->Insert(*mPastedTextH, ::GetHandleSize(mPastedTextH), mPastedStyleH);

	mWEView->ForceAutoScroll(theOldRect);
}


// ---------------------------------------------------------------------------
//	¥ UndoSelf
// ---------------------------------------------------------------------------

void
CHexEditorPasteAction::UndoSelf()
{
	StFocusAndClipIfHidden	focus(mWEView);

	LongRect theOldRect;
	WEGetDestRect(&theOldRect,mWERef);
	// Delete text that was pasted
	WESetSelection(mSelStart, mSelStart + ::GetHandleSize(mPastedTextH), mWERef);
	WEDelete(mWERef);
	// Restore text deleted by the paste
	StHandleLocker	lock(mDeletedTextH);
	mWEView->Insert(*mDeletedTextH, mDeletedTextLen, mDeletedStyleH);
	// Restore selection
	WESetSelection(mSelStart, mSelEnd, mWERef);

	mWEView->ForceAutoScroll(theOldRect);
}


#pragma mark -

// ---------------------------------------------------------------------------
//	¥ CHexEditorClearAction					Constructor				  [public]
// ---------------------------------------------------------------------------

CHexEditorClearAction::CHexEditorClearAction(
	WEReference		inWERef,
	LCommander*		inTextCommander,
	LPane*			inTextPane)

	: CWEViewClearAction(inWERef, inTextCommander, inTextPane)
{
}


// ---------------------------------------------------------------------------
//	¥ RedoSelf
// ---------------------------------------------------------------------------

void
CHexEditorClearAction::RedoSelf()
{
	StFocusAndClipIfHidden	focus(mWEView);

	LongRect theOldRect;
	WEGetDestRect(&theOldRect,mWERef);
	WESetSelection(mSelStart, mSelEnd, mWERef);
	WEDelete(mWERef);

	mWEView->ForceAutoScroll(theOldRect);
}


#pragma mark -

// ---------------------------------------------------------------------------
//	¥ CHexEditorTypingAction					Constructor				  [public]
// ---------------------------------------------------------------------------

CHexEditorTypingAction::CHexEditorTypingAction(
	WEReference		inWERef,
	LCommander*		inTextCommander,
	LPane*			inTextPane)

	: CWEViewTypingAction(inWERef, inTextCommander, inTextPane)
{
}


// ---------------------------------------------------------------------------
//	¥ ~CHexEditorTypingAction					Destructor				  [public]
// ---------------------------------------------------------------------------

CHexEditorTypingAction::~CHexEditorTypingAction()
{
}


// ---------------------------------------------------------------------------
//	¥ RedoSelf
// ---------------------------------------------------------------------------
//	Redo a TypingAction by restoring the last typing sequence

void
CHexEditorTypingAction::RedoSelf()
{
	CWEViewTypingAction::RedoSelf();
}


// ---------------------------------------------------------------------------
//	¥ UndoSelf
// ---------------------------------------------------------------------------
//	Undo a TypingAction by restoring the text and selection that
//	existed before the current typing sequence started

void
CHexEditorTypingAction::UndoSelf()
{
	CWEViewTypingAction::UndoSelf();
}



PP_End_Namespace_PowerPlant
