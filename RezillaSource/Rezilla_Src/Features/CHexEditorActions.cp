// ===========================================================================
// CHexEditorActions.cp 
//                       Created: 2003-05-29 21:13:13
//             Last modification: 2005-05-27 09:28:46
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2003-2005
// All rights reserved.
// ===========================================================================


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

// Custom headers
#include "WASTE.h"
#include "CHexEditorActions.h"
#include "CWasteEditView.h"
#include "CDualDataView.h"
#include "CHexDataSubView.h"
#include "CTxtDataSubView.h"
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
#ifndef __MACH__
#include <Fonts.h>
#endif

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   CHexEditorCutAction						Constructor				  [public]
// ---------------------------------------------------------------------------

CHexEditorCutAction::CHexEditorCutAction(
	WEReference		inWERef,
	LCommander*		inTextCommander,
	LPane*			inTextPane)

	: CWEViewCutAction(inWERef, inTextCommander, inTextPane)
{
}


// ---------------------------------------------------------------------------
//   RedoSelf
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
//   CHexEditorPasteAction					Constructor				  [public]
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
	  case item_HexDataWE: {
		  StSepHexTranslator translator(mPastedTextH);
		  translator.Convert();
		  mPastedTextH = translator.GetOutHandle();
		  
		  break;
	  }
	  
		
	  case item_TxtDataWE: {
		  StSepTextTranslator translator(mPastedTextH);
		  translator.Convert();
		  mPastedTextH = translator.GetOutHandle();
		  
		  break;
	  }
		
	}
}


// ---------------------------------------------------------------------------
//     ~CHexEditorPasteAction					Destructor				  [public]
// ---------------------------------------------------------------------------

CHexEditorPasteAction::~CHexEditorPasteAction()
{
}


// ---------------------------------------------------------------------------
//   RedoSelf
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
//   UndoSelf
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
//   CHexEditorClearAction					Constructor				  [public]
// ---------------------------------------------------------------------------

CHexEditorClearAction::CHexEditorClearAction(
	WEReference		inWERef,
	LCommander*		inTextCommander,
	LPane*			inTextPane)

	: CWEViewClearAction(inWERef, inTextCommander, inTextPane)
{
}


// ---------------------------------------------------------------------------
//   RedoSelf
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
//   CHexEditorTypingAction					Constructor				  [public]
// ---------------------------------------------------------------------------

CHexEditorTypingAction::CHexEditorTypingAction(
	WEReference		inWERef,
	LCommander*		inTextCommander,
	LPane*			inTextPane)

	: CWEViewTypingAction(inWERef, inTextCommander, inTextPane)
{
// 	// Change the default meaning of mWERef. It now designates the
// 	// in-memory Waste edit structure.
// 	switch ( mWEView->GetPaneID() ) {
// 		case item_HexDataWE:
// 		mWERef = dynamic_cast<CHexDataSubView*>(mWEView)->GetOwnerDualView()->GetInMemoryWE();
// 		break;
// 		
// 		case item_TxtDataWE:
// 		mWERef = dynamic_cast<CTxtDataSubView*>(mWEView)->GetOwnerDualView()->GetInMemoryWE();
// 		break;
// 		
// 	}
// 	
// 	// The initialization done in the CWETextActions parent class must be
// 	// entirely redone because we act upon the in-memory WE
// 	Reset();
}


// ---------------------------------------------------------------------------
//     ~CHexEditorTypingAction					Destructor				  [public]
// ---------------------------------------------------------------------------

CHexEditorTypingAction::~CHexEditorTypingAction()
{
}


// ---------------------------------------------------------------------------
//   InsertCharacter
// ---------------------------------------------------------------------------
//	Handle an input character typing action
//
//	This is an overloaded version of this method: the inOneOfTwoInserted
//	argument concerns hex data sub views in which typing a hex code is a
//	two steps process. If we are typing the second byte of a two bytes hex,
//	there is no change for the typing end.

void
CHexEditorTypingAction::InsertCharacter(Boolean inOneOfTwoInserted)
{
	SInt32	selStart, selEnd;
	
	WEGetSelection( & selStart, & selEnd, mWERef);
	
	if ( (mTypingEnd != selStart) ||
		 (mTypingEnd != selEnd) ||
		 (mTypingEnd == mTypingStart) ||
		 !IsDone() ) {
									// Selection has changed. Start a
		Reset();					//   fresh typing sequence
	}
	if (!inOneOfTwoInserted) {
		mTypingEnd += 1;
	} 
}


// ---------------------------------------------------------------------------
//   RedoSelf
// ---------------------------------------------------------------------------
//	Redo a TypingAction by restoring the last typing sequence

void
CHexEditorTypingAction::RedoSelf()
{
	StFocusAndClipIfHidden	focus(mWEView);

	LongRect theOldRect;
	WEGetDestRect(&theOldRect,mWERef);
									
	// Delete original text
	WESetSelection(mTypingStart, mTypingStart + mDeletedTextLen, mWERef);
	WEDelete(mWERef);
									
	// Insert typing run in the in-memory WE
	StHandleLocker	lock(mTypedTextH);
	
	WEPut( mTypingStart, mTypingStart, *mTypedTextH, (mTypingEnd - mTypingStart), kTextEncodingMultiRun,
				kNilOptions, 0, nil, nil, mWERef);

// 	RefreshViews();
	mWEView->ForceAutoScroll(theOldRect);
}


// ---------------------------------------------------------------------------
//   UndoSelf
// ---------------------------------------------------------------------------
//	Undo a TypingAction by restoring the text and selection that
//	existed before the current typing sequence started

void
CHexEditorTypingAction::UndoSelf()
{
	StFocusAndClipIfHidden	focus(mWEView);
	LongRect theOldRect;
	WEGetDestRect(&theOldRect,mWERef);
	
	// Save current typing run
	if (mTypedTextH == nil) {
		mTypedTextH = ::NewHandle(mTypingEnd - mTypingStart);
		ThrowIfMemFail_(mTypedTextH);
	} else {
		::SetHandleSize(mTypedTextH, mTypingEnd - mTypingStart);
		ThrowIfMemError_();
	}
	
	WEStreamRange( mTypingStart, mTypingEnd, kTypeText, kNilOptions, mTypedTextH, mWERef);

	// Delete current typing run
	WESetSelection(mTypingStart, mTypingEnd, mWERef);

	if (mTypedStyleH != nil) {
		::DisposeHandle(mTypedStyleH);
	}
	
	mTypedStyleH = ::NewHandle(0);

	// Retrieve the style in the typed range
	WEStreamRange( mTypingStart, mTypingEnd, kTypeStyles, kNilOptions, mTypedStyleH, mWERef);

	// Delete the selection
	WEDelete(mWERef);
	
	// Restore original text in the in-memory WE
	StHandleLocker	lock(mDeletedTextH);
	WEPut( mTypingStart, mTypingStart, *mDeletedTextH, mDeletedTextLen, kTextEncodingMultiRun,
				kNilOptions, 0, nil, nil, mWERef);

	// Refresh and restore original selection
// 	RefreshViews();
	WESetSelection(mSelStart, mSelEnd, mWERef);

	mWEView->ForceAutoScroll(theOldRect);
}


// ---------------------------------------------------------------------------
//   RefreshViews
// ---------------------------------------------------------------------------

void
CHexEditorTypingAction::RefreshViews()
{
	CDualDataView *	theDual;
	
	switch ( mWEView->GetPaneID() ) {
		case item_HexDataWE:
		theDual = dynamic_cast<CHexDataSubView*>(mWEView)->GetOwnerDualView();
		break;
		
		case item_TxtDataWE:
		theDual = dynamic_cast<CTxtDataSubView*>(mWEView)->GetOwnerDualView();
		break;
	}
	SInt32 firstLine = theDual->GetCurrFirstLine();
	theDual->InstallContentsFromLine(firstLine);
}




PP_End_Namespace_PowerPlant
