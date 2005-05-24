// ===========================================================================
//	CWEViewActions.cp
//	
//                       Created: 2001-09-08 07:05:27
//             Last modification: 2005-05-24 15:58:30
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2001-2004, 2005
// All rights reserved.
// $Date$
// $Revision$
//	
//	Description : CWaste is a class designed to interface between 
//	the Waste Edit text engine (©1993-2000 by Marco Piovanelli)
//  and CodeWarrior's PowerPlant 2.1 library (©1993-2000 Metrowerks Inc.)
//  
// This file is part of the CWasteEditView package vs-1.8
// ===========================================================================
//
//	Undoable Actions associated with a WasteEdit record
//	Reworked for the undo and autoscrolling mechanisms of CWasteEditView

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

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

// Custom headers
#include "WASTE.h"
#include "CWEViewActions.h"
#include "CWasteEditView.h"

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//	¥ CWETextActions					Constructor				  [public]
// ---------------------------------------------------------------------------

CWETextActions::CWETextActions(
	SInt16			inDescriptionIndex,
	CommandT		inActionCommand,
	WEReference		inWERef,
	LCommander*		inTextCommander,
	LPane*			inTextPane,
	bool			inAlreadyDone)

	: LAction(STRx_RedoEdit, inDescriptionIndex, inAlreadyDone)
{
	mActionCommand	= inActionCommand;
	mWERef			= inWERef;
	mTextCommander	= inTextCommander;
	mWEView			= dynamic_cast<CWasteEditView*>(inTextPane);
	ThrowIfNil_(mWEView);

	// Save current selection range and the selected text,
	// which will be deleted when doing the Action.
	WEGetSelection( & mSelStart, & mSelEnd, inWERef);

	mDeletedTextLen	= mSelEnd - mSelStart;
	mDeletedTextH	= ::NewHandle(mDeletedTextLen);

		// If we can't allocate the memory to save the selected
		// text, we don't throw. We still want to "do" the Action,
		// but it won't be undoable. mDeletedTextH being nil will
		// mark this Action as not postable (undoable). When
		// PostAction() is called, this Action will be "done" and
		// then deleted.

	if (mDeletedTextH != nil) {
//     	Handle	hText=static_cast<Handle>(WEGetText(inWERef));
// 		::BlockMoveData(*hText + mSelStart, *mDeletedTextH,
// 							mDeletedTextLen);
		WEStreamRange( mSelStart, mSelEnd, kTypeText, kNilOptions, mDeletedTextH, inWERef);
	}
	
	mDeletedStyleH = ::NewHandle(0);
	
	// Retrieve the style in the selection range
// 	WECopyRange(mSelStart,mSelEnd,mDeletedTextH,mDeletedStyleH,nil,inWERef) ;
	WEStreamRange( mSelStart, mSelEnd, kTypeStyles, kNilOptions, mDeletedStyleH, inWERef);
}


// ---------------------------------------------------------------------------
//	¥ ~CWETextActions					Destructor				  [public]
// ---------------------------------------------------------------------------

CWETextActions::~CWETextActions()
{
	if (mDeletedTextH != nil) {
		::DisposeHandle(mDeletedTextH);
	}

	if (mDeletedStyleH != nil) {
		::DisposeHandle((Handle)mDeletedStyleH);
	}
}


// ---------------------------------------------------------------------------
//	¥ Redo
// ---------------------------------------------------------------------------

void
CWETextActions::Redo()
{
	if (CanRedo()) {
		RedoSelf();
		mTextCommander->ProcessCommand(mActionCommand, this);
	}

	mIsDone = true;
}


// ---------------------------------------------------------------------------
//	¥ Undo
// ---------------------------------------------------------------------------

void
CWETextActions::Undo()
{
	if (CanUndo()) {
		UndoSelf();
		mTextCommander->ProcessCommand(mActionCommand, this);
	}

	mIsDone = false;
}


// ---------------------------------------------------------------------------
//	¥ CanRedo
// ---------------------------------------------------------------------------

Boolean
CWETextActions::CanRedo() const
{
	return (!IsDone() && mTextCommander->IsOnDuty());
}


// ---------------------------------------------------------------------------
//	¥ CanUndo
// ---------------------------------------------------------------------------

Boolean
CWETextActions::CanUndo() const
{
	return (IsDone() && mTextCommander->IsOnDuty());
}


// ---------------------------------------------------------------------------
//	¥ IsPostable
// ---------------------------------------------------------------------------

Boolean
CWETextActions::IsPostable() const
{
		// Action is not postable (undoable) if we could not
		// allocate space to store the text that was deleted

	return (mDeletedTextH != nil);
}


// ---------------------------------------------------------------------------
//	¥ UndoSelf
// ---------------------------------------------------------------------------

void
CWETextActions::UndoSelf()
{
	StFocusAndClipIfHidden	focus(mWEView);
	// Restore deleted text
	WESetSelection(mSelStart, mSelStart, mWERef);
	StHandleLocker	lock(mDeletedTextH);
	mWEView->Insert(*mDeletedTextH, mDeletedTextLen, mDeletedStyleH);
	// Restore original selection
	WESetSelection(mSelStart, mSelEnd, mWERef);
}


#pragma mark -

// ---------------------------------------------------------------------------
//	¥ CWEViewCutAction						Constructor				  [public]
// ---------------------------------------------------------------------------

CWEViewCutAction::CWEViewCutAction(
	WEReference		inWERef,
	LCommander*		inTextCommander,
	LPane*			inTextPane)

	: CWETextActions(str_Cut, cmd_ActionCut, inWERef,
							inTextCommander, inTextPane)
{
}


// ---------------------------------------------------------------------------
//	¥ RedoSelf
// ---------------------------------------------------------------------------

void
CWEViewCutAction::RedoSelf()
{
	StFocusAndClipIfHidden	focus(mWEView);

	LongRect theOldRect;
	WEGetDestRect(&theOldRect,mWERef);

	WESetSelection(mSelStart, mSelEnd, mWERef);
	WEDelete(mWERef);

	// Put deleted text on clipboard
	UScrap::SetData(ResType_Text, mDeletedTextH);
	
	// Add style info to clipboard
	if (mDeletedStyleH != nil) {		
		UScrap::SetData(ResType_TextStyle, (Handle) mDeletedStyleH, false);
	}

	mWEView->ForceAutoScroll(theOldRect);
}

#pragma mark -

// ---------------------------------------------------------------------------
//	¥ CWEViewPasteAction					Constructor				  [public]
// ---------------------------------------------------------------------------

CWEViewPasteAction::CWEViewPasteAction(
	WEReference		inWERef,
	LCommander*		inTextCommander,
	LPane*			inTextPane)

	: CWETextActions(str_Paste, cmd_ActionPaste, inWERef,
							inTextCommander, inTextPane)
{
	// Get text from clipboard
	StHandleBlock	textH(Size_Zero);
	UScrap::GetData(ResType_Text, textH);

	// Get style from clipboard
	StHandleBlock	styleH(Size_Zero);
	SInt32			styleSize = UScrap::GetData(ResType_TextStyle, styleH);

	// Getting info from clipboard succeeded. Store Handles.
	mPastedTextH  = textH.Release();

	mPastedStyleH = nil;				// If there is no style data, we
										//   must use a nil Handle rather
										//   than a zero-sized Handle
	if (styleSize > 0) {
		mPastedStyleH = styleH.Release();
	}
}


// ---------------------------------------------------------------------------
//	¥ ~CWEViewPasteAction					Destructor				  [public]
// ---------------------------------------------------------------------------

CWEViewPasteAction::~CWEViewPasteAction()
{
	if (mPastedTextH != nil) {
		::DisposeHandle(mPastedTextH);
	}

	if (mPastedStyleH != nil) {
		::DisposeHandle(mPastedStyleH);
	}
}


// ---------------------------------------------------------------------------
//	¥ RedoSelf
// ---------------------------------------------------------------------------

void
CWEViewPasteAction::RedoSelf()
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
CWEViewPasteAction::UndoSelf()
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
//	¥ CWEViewClearAction					Constructor				  [public]
// ---------------------------------------------------------------------------

CWEViewClearAction::CWEViewClearAction(
	WEReference		inWERef,
	LCommander*		inTextCommander,
	LPane*			inTextPane)

	: CWETextActions(str_Clear, cmd_ActionClear, inWERef,
							inTextCommander, inTextPane)
{
}


// ---------------------------------------------------------------------------
//	¥ RedoSelf
// ---------------------------------------------------------------------------

void
CWEViewClearAction::RedoSelf()
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
//	¥ CWEViewTypingAction					Constructor				  [public]
// ---------------------------------------------------------------------------

CWEViewTypingAction::CWEViewTypingAction(
	WEReference		inWERef,
	LCommander*		inTextCommander,
	LPane*			inTextPane)

	: CWETextActions(str_Typing, cmd_ActionTyping, inWERef,
							inTextCommander, inTextPane, true)
{
	mTypedTextH  = nil;
	mTypedStyleH = nil;
	mTypingStart = mTypingEnd = mSelStart;
}


// ---------------------------------------------------------------------------
//	¥ ~CWEViewTypingAction					Destructor				  [public]
// ---------------------------------------------------------------------------

CWEViewTypingAction::~CWEViewTypingAction()
{
		// Notify TextCommander that Action is being deleted.
		// The TextCommander usually stores a reference to a
		// TypingAction in order to add/remove characters
		// as the user performs a typing sequence.

	mTextCommander->ProcessCommand(cmd_ActionDeleted, this);

	if (mTypedTextH != nil) {
		::DisposeHandle(mTypedTextH);
	}

	if (mTypedStyleH != nil) {
		::DisposeHandle(mTypedStyleH);
	}
}


// ---------------------------------------------------------------------------
//	¥ Reset
// ---------------------------------------------------------------------------
//	Re-initialize state of TypingAction

void
CWEViewTypingAction::Reset()
{
	mIsDone = true;

	if (mDeletedTextH != nil) {			// Clear store of deleted text
		::DisposeHandle(mDeletedTextH);
	}
	if (mDeletedStyleH != nil) {
		::DisposeHandle((Handle)mDeletedStyleH);
	}

	if (mTypedTextH != nil) {			// New typing sequence is starting
		::DisposeHandle(mTypedTextH);	//   so delete saved text
		mTypedTextH = nil;
	}
	if (mTypedStyleH != nil) {
		::DisposeHandle(mTypedStyleH);
		mTypedStyleH = nil;
	}

	// Save current selection state
	WEGetSelection( & mSelStart, & mSelEnd, mWERef);

	mDeletedTextLen = mSelEnd - mSelStart;

	mTypingStart = mTypingEnd = mSelStart;

	LCommander::SetUpdateCommandStatus(true);

	// Save currently selected text, which will be deleted when the next
	// character is typed
	mDeletedTextH = ::NewHandle(mDeletedTextLen);
	ThrowIfMemFail_(mDeletedTextH);
	
	WEStreamRange( mSelStart, mSelEnd, kTypeText, kNilOptions, mDeletedTextH, mWERef);
// 	Handle	hText=static_cast<Handle>(WEGetText(mWERef));
// 	::BlockMoveData(*hText + mSelStart, *mDeletedTextH,
// 					mDeletedTextLen);
	
	mDeletedStyleH = ::NewHandle(0);

	// Retrieve the style in the selection range.
	// 	WECopyRange(mSelStart,mSelEnd,mDeletedTextH,mDeletedStyleH,nil,inWERef) ;
	WEStreamRange( mSelStart, mSelEnd, kTypeStyles, kNilOptions, mDeletedStyleH, mWERef);
}


// ---------------------------------------------------------------------------
//	¥ InputCharacter
// ---------------------------------------------------------------------------
//	Handle an input character typing action
//
//	This function does not actually put any character into the text. It
//	just saves state for undoing the typing. You should call TEKey()
//	afterwards.

void
CWEViewTypingAction::InputCharacter()
{
	SInt32	selStart;
	SInt32	selEnd;
	WEGetSelection( & selStart, & selEnd, mWERef);
	if ( (mTypingEnd != selStart) ||
		 (mTypingEnd != selEnd) ||
		 (mTypingEnd == mTypingStart) ||
		 !IsDone() ) {
									// Selection has changed. Start a
		Reset();					//   fresh typing sequence
	}

	mTypingEnd += 1;
}


// ---------------------------------------------------------------------------
//	¥ BackwardErase
// ---------------------------------------------------------------------------
//	Handle Backward Delete typing action
//
//	Backward delete erases the current selection if one or more characters
//	is selected. If the selection is a single insertion point, then
//	backward delete erases the one character before the insertion point.
//
//	This function does not actually erase any text. It just saves state
//	for undoing the action. You should call WEKey() with a backspace
//	character afterwards.

void
CWEViewTypingAction::BackwardErase()
{
	SInt32	selStart;
	SInt32	selEnd;
	WEGetSelection( & selStart, & selEnd, mWERef);
	Handle	hText=static_cast<Handle>(WEGetText(mWERef));
	
	if ( (mTypingEnd != selStart) ||
		 (mTypingEnd != selEnd) ) {
									// Selection has changed. Start a
		Reset();					//   fresh typing sequence

		if (mDeletedTextLen == 0) {
								// No selected text, save the one character
								//   that will be deleted
			::SetHandleSize(mDeletedTextH, 1);
			mDeletedTextLen = 1;
			mTypingStart -= 1;
			**mDeletedTextH = *(*hText + mTypingStart);

		} else {				// Selection being deleted. Increment end
			mTypingEnd += 1;	//   to counteract decrement done on the
								//   last line of this function.
		}

	} else if (mTypingStart >= selStart) {
									// Deleting before beginning of typing
		::SetHandleSize(mDeletedTextH, mDeletedTextLen + 1);
		ThrowIfMemError_();

		::BlockMoveData(*mDeletedTextH, *mDeletedTextH + 1, mDeletedTextLen);
		mDeletedTextLen += 1;
		mTypingStart = selStart - 1;
		**mDeletedTextH = *(*hText + mTypingStart);
	}

	mTypingEnd -= 1;
}


// ---------------------------------------------------------------------------
//	¥ ForwardErase
// ---------------------------------------------------------------------------
//	Handle Forward Delete typing action
//
//	Forward delete erases the current selection if one or more characters
//	is selected. If the selection is a single insertion point, then
//	forward delete erases the one character after the insertion point.
//
//	This function does not actually erase any text. It just saves state
//	for undoing the action. Afterwards, you should select the next
//	character if the selection is empty and call WEDelete().

void
CWEViewTypingAction::ForwardErase()
{
	SInt32	selStart;
	SInt32	selEnd;
	WEGetSelection( & selStart, & selEnd, mWERef);
	Handle	hText=static_cast<Handle>(WEGetText(mWERef));
	
	if ( (mTypingEnd != selStart) ||
		 (mTypingEnd != selEnd) ) {
									// Selection has changed. Start a
		Reset();					//   fresh typing sequence

		if (mSelStart == mSelEnd) {
									// Selection is a single insertion point
									// Select next character
			::SetHandleSize(mDeletedTextH, 1);
			ThrowIfMemError_();
			
			**mDeletedTextH = *(*hText + mSelStart);
			mDeletedTextLen = 1;
		}

	} else {						// Selection hasn't changed
									// Select next character
		::SetHandleSize(mDeletedTextH, mDeletedTextLen + 1);
		ThrowIfMemError_();

		*(*mDeletedTextH + mDeletedTextLen) =
				*(*hText + mTypingEnd);
		mDeletedTextLen += 1;
	}
}


// ---------------------------------------------------------------------------
//	¥ RedoSelf
// ---------------------------------------------------------------------------
//	Redo a TypingAction by restoring the last typing sequence

void
CWEViewTypingAction::RedoSelf()
{
	StFocusAndClipIfHidden	focus(mWEView);

	LongRect theOldRect;
	WEGetDestRect(&theOldRect,mWERef);
									// Delete original text
	WESetSelection(mTypingStart, mTypingStart + mDeletedTextLen, mWERef);
	WEDelete(mWERef);
									// Insert typing run
	StHandleLocker	lock(mTypedTextH);
	mWEView->Insert(*mTypedTextH, (mTypingEnd - mTypingStart), mTypedStyleH);

	mWEView->ForceAutoScroll(theOldRect);
}


// ---------------------------------------------------------------------------
//	¥ UndoSelf
// ---------------------------------------------------------------------------
//	Undo a TypingAction by restoring the text and selection that
//	existed before the current typing sequence started

void
CWEViewTypingAction::UndoSelf()
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
// 	WECopyRange(mTypingStart,mTypingEnd,mTypedTextH,(StScrpHandle) mTypedStyleH,nil,mWERef) ;
	WEStreamRange( mTypingStart, mTypingEnd, kTypeStyles, kNilOptions, mTypedStyleH, mWERef);

	WEDelete(mWERef);
	// Restore original text
	StHandleLocker	lock(mDeletedTextH);
	mWEView->Insert(*mDeletedTextH, mDeletedTextLen, mDeletedStyleH);

	// Restore original selection
	WESetSelection(mSelStart, mSelEnd, mWERef);

	mWEView->ForceAutoScroll(theOldRect);
}


#pragma mark -

// ---------------------------------------------------------------------------
//	¥ CWEStyleActions					Constructor				  [public]
// ---------------------------------------------------------------------------
// 	A "base" class for the style actions (font, size, style/face, align/just,
//	color) to encapsulate some common functionality.

CWEStyleActions::CWEStyleActions(
	SInt16			inDescriptionIndex,
	LCommander*		inCommander,
	LPane*			inPane,
	bool			inAlreadyDone)

	: LAction(STRx_RedoStyle, inDescriptionIndex, inAlreadyDone)
{
	mCommander	= inCommander;
	mWEView		= dynamic_cast<CWasteEditView *>(inPane);
	ThrowIfNil_(mWEView);

	WEGetSelection( & mSelStart, & mSelEnd, mWEView->GetWasteRef());
}


// ---------------------------------------------------------------------------
//	¥ CWEStyleActions					Destructor				  [public]
// ---------------------------------------------------------------------------

CWEStyleActions::~CWEStyleActions()
{
}


// ---------------------------------------------------------------------------
//	¥ CanRedo
// ---------------------------------------------------------------------------

Boolean
CWEStyleActions::CanRedo() const
{
	// Call inherited and ensure the commander is on duty.
	return LAction::CanRedo() && mCommander->IsOnDuty();
}


// ---------------------------------------------------------------------------
//	¥ CanUndo
// ---------------------------------------------------------------------------

Boolean
CWEStyleActions::CanUndo() const
{
	// Call inherited and ensure the commander is on duty.
	return LAction::CanUndo() && mCommander->IsOnDuty();
}


#pragma mark -

// ---------------------------------------------------------------------------
//	¥ CWEViewFontAction						Constructor				  [public]
// ---------------------------------------------------------------------------

CWEViewFontAction::CWEViewFontAction(
	SInt16			inFont,
	LCommander*		inCommander,
	LPane*			inPane,
	bool			inAlreadyDone)

	: CWEStyleActions(str_Font, inCommander, inPane, inAlreadyDone)
{
	mFont = inFont;

	mWEView->GetFont(mSavedFont);			// Save the current font
}


// ---------------------------------------------------------------------------
//	¥ CWEViewFontAction						Constructor				  [public]
// ---------------------------------------------------------------------------

CWEViewFontAction::CWEViewFontAction(
	Str255			inFontName,
	LCommander*		inCommander,
	LPane*			inPane,
	bool			inAlreadyDone )

	: CWEStyleActions(str_Font, inCommander, inPane, inAlreadyDone)
{
	::GetFNum(inFontName, &mFont);			// Get font number from name

	mWEView->GetFont(mSavedFont);			// Save the current font
}


// ---------------------------------------------------------------------------
//	¥ ~CWEViewFontAction					Destructor				  [public]
// ---------------------------------------------------------------------------

CWEViewFontAction::~CWEViewFontAction()
{
}


// ---------------------------------------------------------------------------
//	¥ UndoSelf
// ---------------------------------------------------------------------------

void
CWEViewFontAction::UndoSelf()
{
	WEReference theWERef = mWEView->GetWasteRef();
	LongRect 			theOldRect;
	WEGetDestRect(&theOldRect,theWERef);

	TextStyle theStyle;
	theStyle.tsFont = mSavedFont;

	WESetSelection( mSelStart, mSelEnd, theWERef );
	WESetStyle( weDoFont, &theStyle, theWERef );

	mWEView->AlignWERects();
	mWEView->AdjustImageToText();
	mWEView->ForceAutoScroll(theOldRect);
	mWEView->Refresh();

}

// ---------------------------------------------------------------------------
//	¥ RedoSelf
// ---------------------------------------------------------------------------

void
CWEViewFontAction::RedoSelf()
{
	WEReference theWERef = mWEView->GetWasteRef();
	LongRect theOldRect;
	WEGetDestRect(&theOldRect,theWERef);

	TextStyle theStyle;
	theStyle.tsFont = mFont;

	WESetSelection(mSelStart, mSelEnd, theWERef);
	WESetStyle( weDoFont, &theStyle, theWERef );

	mWEView->AlignWERects();
	mWEView->AdjustImageToText();
	mWEView->ForceAutoScroll(theOldRect);
	mWEView->Refresh();
}

#pragma mark-

// ---------------------------------------------------------------------------
//	¥ CWEViewSizeAction						Constructor				  [public]
// ---------------------------------------------------------------------------

CWEViewSizeAction::CWEViewSizeAction(
	SInt16			inSize,
	LCommander*		inCommander,
	LPane*			inPane,
	bool			inAlreadyDone)

	: CWEStyleActions(str_Size, inCommander, inPane, inAlreadyDone)
{
	mSize = inSize;

	mWEView->GetSize( mSavedSize );
}


// ---------------------------------------------------------------------------
//	¥ ~CWEViewSizeAction					Destructor				  [public]
// ---------------------------------------------------------------------------

CWEViewSizeAction::~CWEViewSizeAction()
{
}


// ---------------------------------------------------------------------------
//	¥ UndoSelf
// ---------------------------------------------------------------------------

void
CWEViewSizeAction::UndoSelf()
{
	WEReference theWERef = mWEView->GetWasteRef();
	LongRect theOldRect;
	WEGetDestRect(&theOldRect,theWERef);

	TextStyle theStyle;
	theStyle.tsSize = mSavedSize;

	WESetSelection(mSelStart, mSelEnd, theWERef);
	WESetStyle( weDoSize, &theStyle, theWERef );

	mWEView->AlignWERects();
	mWEView->AdjustImageToText();
	mWEView->ForceAutoScroll(theOldRect);
	mWEView->Refresh();
}


// ---------------------------------------------------------------------------
//	¥ RedoSelf
// ---------------------------------------------------------------------------

void
CWEViewSizeAction::RedoSelf()
{
	WEReference theWERef = mWEView->GetWasteRef();
	LongRect theOldRect;
	WEGetDestRect(&theOldRect,theWERef);

	TextStyle theStyle;
	theStyle.tsSize = mSize;

	WESetSelection(mSelStart, mSelEnd, theWERef);
	WESetStyle( weDoSize, &theStyle, theWERef );

	mWEView->AlignWERects();
	mWEView->AdjustImageToText();
	mWEView->ForceAutoScroll(theOldRect);
	mWEView->Refresh();
}


#pragma mark-

// ---------------------------------------------------------------------------
//	¥ CWEViewFaceAction						Constructor				  [public]
// ---------------------------------------------------------------------------

CWEViewFaceAction::CWEViewFaceAction(
	Style			inFace,
	bool			inToggle,
	LCommander*		inCommander,
	LPane*			inPane,
	bool			inAlreadyDone)

	: CWEStyleActions(str_Face, inCommander, inPane, inAlreadyDone)
{
	mFace	= inFace;
	mToggle = inToggle;

	mWEView->GetStyle(mSavedFace);
}


// ---------------------------------------------------------------------------
//	¥ ~CWEViewFaceAction					Destructor				  [public]
// ---------------------------------------------------------------------------

CWEViewFaceAction::~CWEViewFaceAction()
{
}


// ---------------------------------------------------------------------------
//	¥ UndoSelf
// ---------------------------------------------------------------------------

void
CWEViewFaceAction::UndoSelf()
{
	WEReference theWERef = mWEView->GetWasteRef();
	LongRect theOldRect;
	WEGetDestRect(&theOldRect,theWERef);

	SInt16 theMode = weDoFace;
	TextStyle theStyle;

	if (mToggle) {
		theStyle.tsFace = mFace;
		theMode			+= weDoToggleFace;
	} else {
		theStyle.tsFace = mSavedFace;
	}

	WESetSelection(mSelStart, mSelEnd, theWERef);
	WESetStyle(theMode, &theStyle, theWERef);

	mWEView->AlignWERects();
	mWEView->AdjustImageToText();
	mWEView->ForceAutoScroll(theOldRect);
	mWEView->Refresh();
}


// ---------------------------------------------------------------------------
//	¥ RedoSelf
// ---------------------------------------------------------------------------

void
CWEViewFaceAction::RedoSelf()
{
	// set to mFace, if toggle, toggle, else SetStyle

	WEReference theWERef = mWEView->GetWasteRef();
	LongRect theOldRect;
	WEGetDestRect(&theOldRect,theWERef);

	TextStyle theStyle;
	theStyle.tsFace = mFace;

	SInt16 theMode = weDoFace;

	if (mToggle) {
		theMode += weDoToggleFace;
	}

	WESetSelection(mSelStart, mSelEnd, theWERef);
	WESetStyle( theMode, &theStyle, theWERef );

	mWEView->AlignWERects();
	mWEView->AdjustImageToText();
	mWEView->ForceAutoScroll(theOldRect);
	mWEView->Refresh();

}

#pragma mark -

// ---------------------------------------------------------------------------
//	¥ CWEViewAlignAction					Constructor				  [public]
// ---------------------------------------------------------------------------

CWEViewAlignAction::CWEViewAlignAction(
	WEAlignment		inAlign,
	LCommander*		inCommander,
	LPane*			inPane,
	bool			inAlreadyDone)

	: CWEStyleActions(str_Alignment, inCommander, inPane, inAlreadyDone)
{
	mAlign		= inAlign;
	mSavedAlign = mWEView->GetAlignment();
// WESetAlignment(inAlign,mWERef);
}


// ---------------------------------------------------------------------------
//	¥ ~CWEViewAlignAction					Destructor				  [public]
// ---------------------------------------------------------------------------

CWEViewAlignAction::~CWEViewAlignAction()
{
}


// ---------------------------------------------------------------------------
//	¥ UndoSelf
// ---------------------------------------------------------------------------

void
CWEViewAlignAction::UndoSelf()
{
	WEReference theWERef = mWEView->GetWasteRef();
	LongRect theOldRect;
	WEGetDestRect(&theOldRect,theWERef);

	WESetAlignment( mSavedAlign, theWERef );

	mWEView->AlignWERects();
	mWEView->AdjustImageToText();
	mWEView->ForceAutoScroll(theOldRect);
	mWEView->Refresh();

}

// ---------------------------------------------------------------------------
//	¥ RedoSelf
// ---------------------------------------------------------------------------

void
CWEViewAlignAction::RedoSelf()
{
	WEReference theWERef = mWEView->GetWasteRef();
	LongRect theOldRect;
	WEGetDestRect(&theOldRect,theWERef);

	WESetAlignment( mAlign, theWERef );

	mWEView->AlignWERects();
	mWEView->AdjustImageToText();
	mWEView->ForceAutoScroll(theOldRect);
	mWEView->Refresh();
}

#pragma mark -

// ---------------------------------------------------------------------------
//	¥ CWEViewColorAction					Constructor				  [public]
// ---------------------------------------------------------------------------

CWEViewColorAction::CWEViewColorAction(
	const RGBColor&		inColor,
	LCommander*			inCommander,
	LPane*				inPane,
	bool				inAlreadyDone)

	: CWEStyleActions(str_Color, inCommander, inPane, inAlreadyDone)
{
	mColor = inColor;
	mWEView->GetColor(mSavedColor);
}


// ---------------------------------------------------------------------------
//	¥ ~CWEViewColorAction					Destructor				  [public]
// ---------------------------------------------------------------------------

CWEViewColorAction::~CWEViewColorAction()
{
}


// ---------------------------------------------------------------------------
//	¥ UndoSelf
// ---------------------------------------------------------------------------

void
CWEViewColorAction::UndoSelf()
{
	TextStyle theStyle;
	theStyle.tsColor = mSavedColor;

	WEReference theWERef = mWEView->GetWasteRef();
	WESetSelection(mSelStart, mSelEnd, theWERef);
	WESetStyle(weDoColor, &theStyle, theWERef);

	mWEView->Refresh();
}

// ---------------------------------------------------------------------------
//	¥ RedoSelf
// ---------------------------------------------------------------------------

void
CWEViewColorAction::RedoSelf()
{
	TextStyle theStyle;
	theStyle.tsColor = mColor;

	WEReference theWERef = mWEView->GetWasteRef();
	WESetSelection(mSelStart, mSelEnd, theWERef);
	WESetStyle(weDoColor, &theStyle, theWERef);

	mWEView->Refresh();
}


PP_End_Namespace_PowerPlant
