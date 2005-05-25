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
	  case item_HexDataWE: {
		  StSepHexTranslator translator(mPastedTextH);
		  translator.Convert();
		  mPastedTextH = translator.GetOutHandle();
		  
		  break;
	  }
	  
		
	  case item_TxtDataWE: {
		  break;
	  }
		
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


// // ---------------------------------------------------------------------------
// //	¥ RedoSelf
// // ---------------------------------------------------------------------------
// //	We must call the parent's class Insert method (i-e 
// //	CWasteEditView::Insert instead of ) otherwise the 
// //	mTypedTextH input is converted to hexadecimal or readable
// 
// void
// CHexEditorTypingAction::RedoSelf()
// {
// 	StFocusAndClipIfHidden	focus(mWEView);
// 
// 	LongRect theOldRect;
// 	WEGetDestRect(&theOldRect,mWERef);
// 									
// 	// Delete original text
// 	WESetSelection(mTypingStart, mTypingStart + mDeletedTextLen, mWERef);
// 	WEDelete(mWERef);
// 									
// 	// Insert typing run
// 	StHandleLocker	lock(mTypedTextH);
// 	mWEView->Insert(*mTypedTextH, (mTypingEnd - mTypingStart), mTypedStyleH);
// // 	CWasteEditView::Insert(*mTypedTextH, (mTypingEnd - mTypingStart), mTypedStyleH);
// 
// 	mWEView->ForceAutoScroll(theOldRect);
// }
// 
// 
// // ---------------------------------------------------------------------------
// //	¥ UndoSelf
// // ---------------------------------------------------------------------------
// //	Undo a TypingAction by restoring the text and selection that
// //	existed before the current typing sequence started
// 
// void
// CHexEditorTypingAction::UndoSelf()
// {
// 	StFocusAndClipIfHidden	focus(mWEView);
// 	LongRect theOldRect;
// 	WEGetDestRect(&theOldRect,mWERef);
// 	
// 	// Save current typing run
// 	if (mTypedTextH == nil) {
// 		mTypedTextH = ::NewHandle(mTypingEnd - mTypingStart);
// 		ThrowIfMemFail_(mTypedTextH);
// 	} else {
// 		::SetHandleSize(mTypedTextH, mTypingEnd - mTypingStart);
// 		ThrowIfMemError_();
// 	}
// 	
// 	WEStreamRange( mTypingStart, mTypingEnd, kTypeText, kNilOptions, mTypedTextH, mWERef);
// 
// 	// Delete current typing run
// 	WESetSelection(mTypingStart, mTypingEnd, mWERef);
// 
// 	if (mTypedStyleH != nil) {
// 		::DisposeHandle(mTypedStyleH);
// 	}
// 	
// 	mTypedStyleH = ::NewHandle(0);
// 
// 	// Retrieve the style in the typed range
// 	WEStreamRange( mTypingStart, mTypingEnd, kTypeStyles, kNilOptions, mTypedStyleH, mWERef);
// 
// 	// Delete the selection
// 	WEDelete(mWERef);
// 	
// 	// Restore original text
// 	StHandleLocker	lock(mDeletedTextH);
// 	mWEView->Insert(*mDeletedTextH, mDeletedTextLen, mDeletedStyleH);
// 
// 	// Restore original selection
// 	WESetSelection(mSelStart, mSelEnd, mWERef);
// 
// 	mWEView->ForceAutoScroll(theOldRect);
// }


// ---------------------------------------------------------------------------
//	¥ InputCharacter
// ---------------------------------------------------------------------------
//	Handle an input character typing action
//
//	This is an overloaded version of this method: the inOneOfTwoInserted
//	argument concerns hex data sub views in which typing a hex code is a
//	two steps process. If we are typing the second byte of a two bytes hex,
//	there is no change for the typing end.

void
CHexEditorTypingAction::InputCharacter(Boolean inOneOfTwoInserted)
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
		mTypingEnd += ( mWEView->GetPaneID() == item_HexDataWE ) ? 3:2 ;
	} 
}


// ---------------------------------------------------------------------------
//	¥ BackwardErase
// ---------------------------------------------------------------------------
//	Handle Backward Delete typing action

void
CHexEditorTypingAction::BackwardErase()
{
	SInt32	selStart, selEnd;
	SInt32	numChar = ( mWEView->GetPaneID() == item_HexDataWE ) ? 3:2;
	
	WEGetSelection( & selStart, & selEnd, mWERef);
	Handle	hText=static_cast<Handle>(WEGetText(mWERef));
	
	if ( (mTypingEnd != selStart) ||
		 (mTypingEnd != selEnd) ) {
									// Selection has changed. Start a
		Reset();					//   fresh typing sequence

		if (mDeletedTextLen == 0) {
								// No selected text, save the 2 or 3 character
								//   that will be deleted
			::SetHandleSize(mDeletedTextH, numChar);
			mDeletedTextLen = numChar;
			mTypingStart -= numChar;
			**mDeletedTextH = *(*hText + mTypingStart);

		} else {					// Selection being deleted. Increment end
			mTypingEnd += numChar;	//   to counteract decrement done on the
									//   last line of this function.
		}

	} else if (mTypingStart >= selStart) {
									// Deleting before beginning of typing
		::SetHandleSize(mDeletedTextH, mDeletedTextLen + numChar);
		ThrowIfMemError_();

		::BlockMoveData(*mDeletedTextH, *mDeletedTextH + numChar, mDeletedTextLen);
		mDeletedTextLen += numChar;
		mTypingStart = selStart - numChar;
		**mDeletedTextH = *(*hText + mTypingStart);
	}

	mTypingEnd -= numChar;
}


// ---------------------------------------------------------------------------
//	¥ ForwardErase
// ---------------------------------------------------------------------------
//	Handle Forward Delete typing action

void
CHexEditorTypingAction::ForwardErase()
{
	SInt32	selStart, selEnd;
	SInt32	numChar = ( mWEView->GetPaneID() == item_HexDataWE ) ? 3:2;

	WEGetSelection( & selStart, & selEnd, mWERef);
	Handle	hText = static_cast<Handle>(WEGetText(mWERef));
	
	if ( (mTypingEnd != selStart) ||
		 (mTypingEnd != selEnd) ) {
									// Selection has changed. Start a
		Reset();					//   fresh typing sequence

		if (mSelStart == mSelEnd) {
									// Selection is a single insertion point
									// Select next character
			::SetHandleSize(mDeletedTextH, numChar);
			ThrowIfMemError_();
			
			**mDeletedTextH = *(*hText + mSelStart);
			mDeletedTextLen = numChar;
		}

	} else {						// Selection hasn't changed
									// Select next character
		::SetHandleSize(mDeletedTextH, mDeletedTextLen + numChar);
		ThrowIfMemError_();

		*(*mDeletedTextH + mDeletedTextLen) = *(*hText + mTypingEnd);
		mDeletedTextLen += numChar;
	}
}



PP_End_Namespace_PowerPlant
