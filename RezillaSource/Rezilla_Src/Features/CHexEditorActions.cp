// ===========================================================================
// CHexEditorActions.cp 
//                       Created: 2003-05-29 21:13:13
//             Last modification: 2004-02-22 19:30:07
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2003, 2004
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
	WEGetDestRect(&theOldRect,mMacWERef);

	WESetSelection(mSelStart, mSelEnd, mMacWERef);
	WEDelete(mMacWERef);

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
	translator.ConvertToHex();
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
// 	if (mPastedTextH != nil) {
// 		::DisposeHandle(mPastedTextH);
// 	}
// 
// 	if (mPastedStyleH != nil) {
// 		::DisposeHandle(mPastedStyleH);
// 	}
}


// ---------------------------------------------------------------------------
//	¥ RedoSelf
// ---------------------------------------------------------------------------

void
CHexEditorPasteAction::RedoSelf()
{
	StFocusAndClipIfHidden	focus(mWEView);

	LongRect theOldRect;
	WEGetDestRect(&theOldRect,mMacWERef);

	if (mSelStart != mSelEnd) {
		WESetSelection(mSelStart, mSelEnd, mMacWERef);
	}

	WEDelete(mMacWERef);
	StHandleLocker	lock(mPastedTextH);
	mWEView->Insert(*mPastedTextH, ::GetHandleSize(mPastedTextH),
						(StScrpHandle) mPastedStyleH);

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
	WEGetDestRect(&theOldRect,mMacWERef);
	// Delete text that was pasted
	WESetSelection(mSelStart, mSelStart + ::GetHandleSize(mPastedTextH), mMacWERef);
	WEDelete(mMacWERef);
	// Restore text deleted by the paste
	StHandleLocker	lock(mDeletedTextH);
	mWEView->Insert(*mDeletedTextH, mDeletedTextLen, mDeletedStyleH);
	// Restore selection
	WESetSelection(mSelStart, mSelEnd, mMacWERef);

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
	WEGetDestRect(&theOldRect,mMacWERef);
	WESetSelection(mSelStart, mSelEnd, mMacWERef);
	WEDelete(mMacWERef);

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
// 		// Notify TextCommander that Action is being deleted.
// 		// The TextCommander usually stores a reference to a
// 		// TypingAction in order to add/remove characters
// 		// as the user performs a typing sequence.
// 
// 	mTextCommander->ProcessCommand(cmd_ActionDeleted, this);
// 
// 	if (mTypedTextH != nil) {
// 		::DisposeHandle(mTypedTextH);
// 	}
// 
// 	if (mTypedStyleH != nil) {
// 		::DisposeHandle(mTypedStyleH);
// 	}
}


// ---------------------------------------------------------------------------
//	¥ RedoSelf
// ---------------------------------------------------------------------------
//	Redo a TypingAction by restoring the last typing sequence

void
CHexEditorTypingAction::RedoSelf()
{
	StFocusAndClipIfHidden	focus(mWEView);

	LongRect theOldRect;
	WEGetDestRect(&theOldRect,mMacWERef);
									// Delete original text
	WESetSelection(mTypingStart, mTypingStart + mDeletedTextLen, mMacWERef);
	WEDelete(mMacWERef);
									// Insert typing run
	StHandleLocker	lock(mTypedTextH);
	mWEView->Insert(*mTypedTextH, (mTypingEnd - mTypingStart), (StScrpHandle)mTypedStyleH);

	mWEView->ForceAutoScroll(theOldRect);
}


// ---------------------------------------------------------------------------
//	¥ UndoSelf
// ---------------------------------------------------------------------------
//	Undo a TypingAction by restoring the text and selection that
//	existed before the current typing sequence started

void
CHexEditorTypingAction::UndoSelf()
{
	StFocusAndClipIfHidden	focus(mWEView);
	LongRect theOldRect;
	WEGetDestRect(&theOldRect,mMacWERef);
	// Save current typing run
	if (mTypedTextH == nil) {
		mTypedTextH = ::NewHandle(mTypingEnd - mTypingStart);
		ThrowIfMemFail_(mTypedTextH);
	} else {
		::SetHandleSize(mTypedTextH, mTypingEnd - mTypingStart);
		ThrowIfMemError_();
	}
	
// 	Handle	hText=static_cast<Handle>(WEGetText(mMacWERef));
// 
// 	::BlockMoveData(*hText + mTypingStart, *mTypedTextH,
// 						mTypingEnd - mTypingStart);

	// Delete current typing run
	WESetSelection(mTypingStart, mTypingEnd, mMacWERef);

	if (mTypedStyleH != nil) {
		::DisposeHandle(mTypedStyleH);
	}

	// We need a StScrpHandle. Retrieve the style in the typed range.
	WECopyRange(mTypingStart,mTypingEnd,mTypedTextH,(StScrpHandle) mTypedStyleH,nil,mMacWERef) ;

	WEDelete(mMacWERef);
	// Restore original text
	StHandleLocker	lock(mDeletedTextH);
	mWEView->Insert(*mDeletedTextH, mDeletedTextLen, mDeletedStyleH);

	// Restore original selection
	WESetSelection(mSelStart, mSelEnd, mMacWERef);

	mWEView->ForceAutoScroll(theOldRect);
}



PP_End_Namespace_PowerPlant
