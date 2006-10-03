// ===========================================================================
// CHexDataSubView.cp 
//                       Created: 2003-05-06 06:04:42
//             Last modification: 2005-05-28 14:32:42
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2003-2005
// All rights reserved.
// ===========================================================================


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CHexDataSubView.h"
#include "CTxtDataSubView.h"
#include "CDualDataView.h"
#include "CSingleScrollBar.h"
#include "CWEViewActions.h"
#include "CHexEditorActions.h"
#include "UCodeTranslator.h"
#include "UHexFilters.h"
#include "RezillaConstants.h"

#include <LScrollBar.h>
#include <UDesktop.h>
#include <UKeyFilters.h>
// #include <Quickdraw.h>
// #include <Sound.h>

PP_Begin_Namespace_PowerPlant



// ---------------------------------------------------------------------------
//   CHexDataSubView						Default Constructor		  [public]
// ---------------------------------------------------------------------------

CHexDataSubView::CHexDataSubView()
	: CWasteEditView()
{
	mTxtSiblingView = nil;
	mIsSynchronizing = false;
	mEditingPos = 0;
	mOneOfTwoInserted = false;
}


// ---------------------------------------------------------------------------
//   CHexDataSubView						Default Constructor		  [public]
// ---------------------------------------------------------------------------

CHexDataSubView::CHexDataSubView(CTxtDataSubView * inSiblingView)
	: CWasteEditView()
{
	mTxtSiblingView = inSiblingView;
	mIsSynchronizing = false;
	mEditingPos = 0;
	mOneOfTwoInserted = false;
}


// ---------------------------------------------------------------------------
//   CHexDataSubView						Parameterized Constructor [public]
// ---------------------------------------------------------------------------

CHexDataSubView::CHexDataSubView(
	 LCommander *		inSuper,
	 const SPaneInfo&	inPaneInfo,
	 const SViewInfo&	inViewInfo,
	 UInt16				inTextAttributes,
	 ResIDT				inTextTraitsID,
	 Boolean			inWordWrap,
	 Boolean			inReadOnly,
	 Boolean			inSelectable)

	: CWasteEditView(inSuper, inPaneInfo, inViewInfo, inTextAttributes, 
					 inTextTraitsID, inWordWrap, inReadOnly, inSelectable)
{
	mTxtSiblingView = nil;
	mIsSynchronizing = false;
	mEditingPos = 0;
	mOneOfTwoInserted = false;
}


// ---------------------------------------------------------------------------
//   CHexDataSubView						Stream Constructor		  [public]
// ---------------------------------------------------------------------------

CHexDataSubView::CHexDataSubView(
	LStream*	inStream)
	: CWasteEditView(inStream)
{
	mTxtSiblingView = nil;
	mIsSynchronizing = false;
	mEditingPos = 0;
	mOneOfTwoInserted = false;
}


// ---------------------------------------------------------------------------
//     ~CHexDataSubView						Destructor				  [public]
// ---------------------------------------------------------------------------

CHexDataSubView::~CHexDataSubView()
{}


#pragma mark -

// ---------------------------------------------------------------------------
//   ClickSelf											[protected, virtual]
// ---------------------------------------------------------------------------

void
CHexDataSubView::ClickSelf(
	const SMouseDownEvent	&inMouseDown)
{
	SInt32 startPos, endPos;

	mOwnerDualView->SetSelectingAll(false);
	CWasteEditView::ClickSelf(inMouseDown);
	AdjustCursorPos();

	// Synchronize sibling
	GetCurrHexPos(startPos, endPos);
	mTxtSiblingView->SyncPositionsWithSibling(startPos, endPos);

	// Synchronize in-memory WE
	WESetSelection(startPos, endPos, mOwnerDualView->GetInMemoryWE());

	// Notify the dual view's listeners
	mOwnerDualView->BroadcastMessage(msg_DualViewEdited, this);
}



// ---------------------------------------------------------------------------
//   AdjustCursorPos											[protected, virtual]
// ---------------------------------------------------------------------------

void
CHexDataSubView::AdjustCursorPos()
{
	SInt32  selStart;
	SInt32  selEnd;
	
	WEGetSelection( & selStart, & selEnd, mWERef ) ;
	WESetSelection( NearestHexPos(selStart), NearestHexPos(selEnd), mWERef);
}


// ---------------------------------------------------------------------------
//   NearestHexPos											[protected, virtual]
// ---------------------------------------------------------------------------
// Returns the nearest pos just before a hexadecimal value

SInt32
CHexDataSubView::NearestHexPos(SInt32 inPos)
{
	SInt32  rest = inPos % 3;
	SInt32  thePos = inPos;

	if (rest == 1) {
		thePos -= 1;
	} else if (rest == 2) {
		thePos += 1;
	} 
	return thePos;
}


// ---------------------------------------------------------------------------
//   GetCurrHexPos											[public]
// ---------------------------------------------------------------------------

void
CHexDataSubView::GetCurrHexPos(SInt32 & outHexSelStart, SInt32 & outHexSelEnd)
{
	SInt32  selStart;
	SInt32  selEnd;
	WEGetSelection( & selStart, & selEnd, mWERef ) ;
	outHexSelStart = PosToHexPos(selStart);
	outHexSelEnd = PosToHexPos(selEnd);
}


// ---------------------------------------------------------------------------
//   PosToHexPos											[protected, virtual]
// ---------------------------------------------------------------------------

SInt32
CHexDataSubView::PosToHexPos(SInt32 inPos)
{
	SInt32  rest = inPos % 3;
	return ( inPos - rest )/3 ;
}


// ---------------------------------------------------------------------------
//   HexPosToPos											[protected, virtual]
// ---------------------------------------------------------------------------

SInt32
CHexDataSubView::HexPosToPos(SInt32 inHexPos)
{
	return (3 * inHexPos);
}


// ---------------------------------------------------------------------------
//   HexPosToLine											[protected, virtual]
// ---------------------------------------------------------------------------

SInt32
CHexDataSubView::HexPosToLine(SInt32 inHexPos)
{
	SInt32 bytesPerline = mOwnerDualView->GetPaneCount(count_BytesPerLine);
	SInt32 theRest = inHexPos % bytesPerline;
	
	return (((inHexPos - theRest) / bytesPerline) + 1);
}


// ---------------------------------------------------------------------------
//   GetCurrLine											[public]
// ---------------------------------------------------------------------------

SInt32
CHexDataSubView::GetCurrLine()
{
	SInt32 theHexSelStart, theHexSelEnd;
	
	GetCurrHexPos(theHexSelStart, theHexSelEnd);
	
	return HexPosToLine(theHexSelStart);
}


// ---------------------------------------------------------------------------
//   GetCurrLines											[public]
// ---------------------------------------------------------------------------

void
CHexDataSubView::GetCurrLines(SInt32 & outFirstLine, SInt32 & outLastLine)
{
	SInt32 theHexSelStart, theHexSelEnd;
	
	GetCurrHexPos(theHexSelStart, theHexSelEnd);
	
	outFirstLine = HexPosToLine(theHexSelStart);
	outLastLine = HexPosToLine(theHexSelEnd);
}

// ---------------------------------------------------------------------------
//   HandleKeyPress							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CHexDataSubView::HandleKeyPress(
	const EventRecord	&inKeyEvent)
{
	Boolean		keyHandled	 = true;
	EKeyStatus	theKeyStatus = keyStatus_Input;
	SInt16		theKey		 = (SInt16) (inKeyEvent.message & charCodeMask);
	LCommander*	theTarget	 = GetTarget();

	if (inKeyEvent.modifiers & cmdKey) {	// Always pass up when the
		theKeyStatus = keyStatus_PassUp;	// command key is down
	} else {
		theKeyStatus = UHexFilters::HexadecimalField(inKeyEvent);
	}

	if ((theKeyStatus == keyStatus_PassUp) && (theKey == ' ')) {
		// Accept space char anyway
		theKeyStatus = keyStatus_Input;
	}

	if (mReadOnly) {
		// Disallow editing
		theKeyStatus = keyStatus_PassUp;
	}

	SInt32	lineCount = WECountLines(mWERef);
	LongRect	oldDestRect ;
	WEGetDestRect(&oldDestRect,mWERef);

	SInt32	theSelStart;
	SInt32	theSelEnd;
	WEGetSelection( & theSelStart, & theSelEnd, mWERef);
	
	StFocusAndClipIfHidden	focus(this);

	switch (theKeyStatus) {
		
		case keyStatus_Input: {
			if (mTypingAction == nil) {
				// The TypingAction is directly wired to the in-memory WE
				mTypingAction = new CHexEditorTypingAction( mOwnerDualView->GetInMemoryWE(), this, this);
				PostAction(mTypingAction);
			}
			
			if (mTypingAction != nil) {
				try {
					dynamic_cast<CHexEditorTypingAction*>(mTypingAction)->InsertCharacter(mOneOfTwoInserted);
				} catch(...) {
					PostAction(nil);
				}
			}
			
			char * buffer = new char[3];
			
			if (!mOneOfTwoInserted) {
				sprintf(buffer, "0%.1x ", UCodeTranslator::HexToValue(theKey));
				Insert(buffer,3);
				mEditingPos = theSelStart + 3;
				mOneOfTwoInserted = true;
			} else {
				if (mEditingPos == theSelStart) {
					WESetSelection( mEditingPos - 3, mEditingPos - 2, mWERef);
					WEDelete(mWERef);
					WESetSelection( mEditingPos - 2, mEditingPos - 2, mWERef);
					sprintf(buffer, "%.1x", UCodeTranslator::HexToValue(theKey));
					Insert(buffer,1);
					WESetSelection( mEditingPos, mEditingPos, mWERef);
					theSelStart -= 3;
				} 
				mOneOfTwoInserted = false;
			}
			// 			ForceAutoScroll(oldDestRect);
			UserChangedText(theSelStart, theSelEnd, 3);
			break;
		}
		
	  
		case keyStatus_TEDelete: {
			if (theSelStart != theSelEnd) {
				// If there is a selection, the delete key is equivalent to
				// a Clear command
				ObeyCommand(cmd_Clear, NULL);
				return keyHandled;
			} else {
				if (mTypingAction == nil) {
					mTypingAction = new CHexEditorTypingAction(mWERef, this, this);
					PostAction(mTypingAction);
				}
				
				if (mTypingAction != nil) {
					try {
						mTypingAction->BackwardErase();
					} catch (...) {
						PostAction(nil);
					}
				}
				
				if (theSelStart == theSelEnd) {
					theSelStart -= 3;
					WESetSelection( theSelStart, theSelEnd, mWERef );
				}
				WEDelete(mWERef);
				UserChangedText(theSelStart, theSelEnd, 0);
				mOneOfTwoInserted = false;
			}
			
			break;
		}
		
		case keyStatus_TECursor: {
			if (theSelStart != theSelEnd) {
				if (theKey == char_RightArrow || theKey == char_DownArrow) {
					WESetSelection( theSelEnd, theSelEnd, mWERef);
				} else {
					WESetSelection( theSelStart, theSelStart, mWERef);
				}
			} else {
				
				switch (theKey) {
					case char_LeftArrow:
					theSelStart -= 3;
					break;
					
					case char_RightArrow:
					theSelStart += 3;
					break;
					
					case char_DownArrow:
					theSelStart += HexPosToPos(mOwnerDualView->GetPaneCount(count_BytesPerLine));
					break;
					
					case char_UpArrow:
					theSelStart -= HexPosToPos(mOwnerDualView->GetPaneCount(count_BytesPerLine));
					break;
				}
				if (theSelStart >= 0 && PosToHexPos(theSelStart) <= mOwnerDualView->GetPaneCount(count_BytesPerPane)) {
					WESetSelection( theSelStart, theSelStart, mWERef);
				}
				CursorMoved(theSelStart);
			}
			mOneOfTwoInserted = false;
			break;
		}

		case keyStatus_ExtraEdit: {
			if (theKey == char_FwdDelete) {

				if (theSelStart < WEGetTextLength(mWERef)) {
					if (mTypingAction == nil) {
						mTypingAction = new CHexEditorTypingAction(mWERef, this, this);
						PostAction(mTypingAction);
					}

					if (mTypingAction != nil) {
						try {
							mTypingAction->ForwardErase();
						} catch (...) {
							PostAction(nil);
						}
					}

					if (theSelStart == theSelEnd) {
						theSelEnd += 3;
						WESetSelection(theSelStart,theSelEnd, mWERef);
					}

					WEDelete(mWERef);
// 					ForceAutoScroll(oldDestRect);
					UserChangedText(theSelStart, theSelEnd, 0);
				}
			} else {
				keyHandled = LCommander::HandleKeyPress(inKeyEvent);
			}
			mOneOfTwoInserted = false;
			break;
		}

		case keyStatus_Reject: {
			::SysBeep(1);
			break;
		}

		case keyStatus_PassUp: {
			keyHandled = LCommander::HandleKeyPress(inKeyEvent);
			break;
		}
	}

	if ((theTarget == GetTarget()) && (lineCount != WECountLines(mWERef))) {
		AdjustImageToText();
	}

	// Notify the dual view
	mOwnerDualView->BroadcastMessage(msg_DualViewEdited, this);

	return keyHandled;
}


// ---------------------------------------------------------------------------
//   ObeyCommand							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CHexDataSubView::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;
	
	if ( mWERef == nil )
		return cmdHandled;

	LongRect	oldDestRect ;
	WEGetDestRect(&oldDestRect,mWERef);

	switch (inCommand) {

		case cmd_Copy: 
		case cmd_Cut: 
		case cmd_Clear:
		case cmd_Paste:  {
			mOwnerDualView->SetCurrentSubView(hex_hexpane);
			cmdHandled = mOwnerDualView->ObeyCommand(inCommand, ioParam);
			break;
		}

		case cmd_ActionCut:
		case cmd_ActionPaste:
		case cmd_ActionClear: {
			break;
		}

		case cmd_ActionTyping: {
			mOneOfTwoInserted = false;
			cmdHandled = mOwnerDualView->ObeyCommand(inCommand, ioParam);
			break;
		}

		case cmd_ActionDeleted: {
			if (mTypingAction == static_cast<CHexEditorTypingAction*>(ioParam)) {
				mTypingAction = nil;
			}
			mOneOfTwoInserted = false;
			break;
		}

		case msg_TabSelect: {
			if (!IsEnabled()) {
				cmdHandled = false;
				break;
			} // else FALL THRU to SelectAll()
		}

		case cmd_SelectAll: {
			mOwnerDualView->SetSelectingAll(true);
			SelectAll();
			mTxtSiblingView->SelectAll();
			AdjustImageToText();
			ForceAutoScroll(oldDestRect);
			break;
		}

		default:
			cmdHandled = mOwnerDualView->ObeyCommand(inCommand, ioParam);
			break;
	}

	return cmdHandled;
}


// ---------------------------------------------------------------------------
//   ScrollImageBy											[public, virtual]
// ---------------------------------------------------------------------------
//	Scroll the Text

void
CHexDataSubView::ScrollImageBy(
	SInt32		inHorizDelta,
	SInt32		inVertDelta,
	Boolean		inRefresh)
{
	CWasteEditView::ScrollImageBy(inHorizDelta, inVertDelta, inRefresh);

	if (!mIsSynchronizing) {
		mTxtSiblingView->SetSynchronizing(true);
		mTxtSiblingView->ScrollImageBy(inHorizDelta, inVertDelta, inRefresh);
	} 
	
	SetSynchronizing(false);
}


// ---------------------------------------------------------------------------
//   CursorMoved							[public, virtual]
// ---------------------------------------------------------------------------

void
CHexDataSubView::CursorMoved(SInt32 inPos)
{
	SInt32 firstLine = mOwnerDualView->GetCurrFirstLine();
	SInt32 lastLine = mOwnerDualView->HexLineCount();
	SInt32 newHexPos, newTxtPos;
	
	if (inPos < 0) {
		if (firstLine <= 1) return;
		firstLine -= 1;
		// Sync the scrollbar: this provokes a redraw because 
		// the scrollbar emits its message.
		mOwnerDualView->GetScroller()->SetValue(firstLine);
		// Update the cursor's pos
		newHexPos = HexPosToPos(mOwnerDualView->GetPaneCount(count_BytesPerLine)) + inPos;
		DisplaySelectionRange( newHexPos, newHexPos);
	} else if (PosToHexPos(inPos) > mOwnerDualView->GetPaneCount(count_BytesPerPane)) {
		if (firstLine > lastLine - mOwnerDualView->GetPaneCount(count_LinesPerPane)) return;
		firstLine += 1;
		// Sync the scrollbar: this provokes a redraw because 
		// the scrollbar emits its message.
		mOwnerDualView->GetScroller()->SetValue(firstLine);
		// Update the cursor's pos
		newHexPos = inPos - HexPosToPos(mOwnerDualView->GetPaneCount(count_BytesPerLine));
		DisplaySelectionRange( newHexPos, newHexPos);
	} else {
		newHexPos = inPos;
	}
	// Sync the sibling
	newTxtPos = mTxtSiblingView->CharPosToPos( PosToHexPos(newHexPos) );
	mTxtSiblingView->DisplaySelectionRange(newTxtPos, newTxtPos);
// 	// Notify the dual view
// 	mOwnerDualView->BroadcastMessage(msg_DualViewEdited, this);
}


// ---------------------------------------------------------------------------
//   InsertContents								[public, virtual]
// ---------------------------------------------------------------------------

void
CHexDataSubView::InsertContents(Handle inHandle)
{
	StSegmHexTranslator translator(inHandle, mOwnerDualView->GetPaneCount(count_BytesPerLine) );
	translator.Convert();
	
	// Empty the Waste edit
	DeleteAll();
	// Put the contents in the hex view and clear the dirty flag.
	SetTextHandle( translator.GetOutHandle() );
	WESetSelection(0, 0, mWERef);
}


// ---------------------------------------------------------------------------
//   InsertContents								[public, virtual]
// ---------------------------------------------------------------------------

void
CHexDataSubView::InsertContents(const void * inPtr, SInt32 inByteCount)
{
	StSegmHexTranslator translator(inPtr, inByteCount, mOwnerDualView->GetPaneCount(count_BytesPerLine));
	translator.Convert();
	
	// Empty the Waste edit
	DeleteAll();
	// Put the contents in the hex view and clear the dirty flag.
	SetTextHandle( translator.GetOutHandle() );
	WESetSelection(0, 0, mWERef);
}


// ---------------------------------------------------------------------------
//   UserChangedText						[public, virtual]
// ---------------------------------------------------------------------------
//	Text of WasteEdit has changed as a result of user action

void
CHexDataSubView::UserChangedText()
{
	CWasteEditView::UserChangedText();
}


// ---------------------------------------------------------------------------
//   UserChangedText						[public, virtual]
// ---------------------------------------------------------------------------
//	Text of WasteEdit has changed as a result of user action

void
CHexDataSubView::UserChangedText(
	SInt32 inStartPos,
	SInt32 inEndPos,
	SInt32 inBytesCount)
{
	CWasteEditView::UserChangedText();
	
	SInt32 firstLine = mOwnerDualView->GetCurrFirstLine();
	SInt32 oldLineCount = mOwnerDualView->HexLineCount();
	
	// Synchronize in-memory Waste
	SyncContentsWithMemory(inStartPos, inEndPos, inBytesCount, firstLine);
	
	SInt32 newLineCount = mOwnerDualView->HexLineCount();
	
	// If the cursor was at the beginning of the frame and we moved back, bring the 
	// previous line (if any) in view.
	if (inStartPos < 0) {
		if (firstLine > 1) {
			firstLine -= 1;
			mOwnerDualView->SetCurrFirstLine(firstLine);
			inStartPos += HexPosToPos(mOwnerDualView->GetPaneCount(count_BytesPerLine));
		} else {
			inStartPos = 0;
		}
	} 
	// If the cursor was at the end of the frame and we insert chars, bring the 
	// next line in view. Create it if necessary.
	if ( inStartPos == HexPosToPos(mOwnerDualView->GetPaneCount(count_BytesPerPane)) && inBytesCount > 0) {
		firstLine += 1;
		mOwnerDualView->SetCurrFirstLine(firstLine);
		inStartPos -= HexPosToPos(mOwnerDualView->GetPaneCount(count_BytesPerLine));
		if (mOneOfTwoInserted) {
			mEditingPos = inStartPos + inBytesCount;
		} 
	} 
	// Redraw accordingly
	if (oldLineCount == newLineCount) {
		// Redraw subviews
		mOwnerDualView->InstallContentsFromLine(firstLine);
	} else if (oldLineCount < newLineCount) {
		// Update the scrollbar's max value
		mOwnerDualView->SetMaxScrollerValue();
		// Provoke a redraw of the subviews
		mOwnerDualView->GetScroller()->SetValue(firstLine);
	} else {
		// Update the scrollbar's max value. Since it is smaller, 
		// the scrollbar provokes a redraw.
		mOwnerDualView->SetMaxScrollerValue();
	}
	// Re-position the cursor
	SInt32 newPos = inStartPos + inBytesCount;
	DisplaySelectionRange(newPos, newPos);
	// Synchronize sibling
	mTxtSiblingView->SyncPositionsWithSibling(PosToHexPos(newPos), PosToHexPos(newPos));
	// Set the window dirty
	SetDirty(true);
}


// ---------------------------------------------------------------------------
//  SetDirty														[public]
// ---------------------------------------------------------------------------

void
CHexDataSubView::SetDirty(Boolean inDirty) 
{
	mIsDirty = inDirty;
	::SetWindowModified(mOwnerDualView->GetWindowRef(), inDirty);
}


// ---------------------------------------------------------------------------
//	 SyncPositionsWithSibling
// ---------------------------------------------------------------------------

void
CHexDataSubView::SyncPositionsWithSibling(SInt32 inStartPos, SInt32 inEndPos)
{
	DisplaySelectionRange(HexPosToPos(inStartPos), HexPosToPos(inEndPos));
}


// ---------------------------------------------------------------------------
//   SyncContentsWithMemory
// ---------------------------------------------------------------------------

void
CHexDataSubView::SyncContentsWithMemory(SInt32 inStartPos, 
										SInt32 inEndPos, 
										SInt32 inBytesCount, 
										SInt32 inLineOffset)
{
	SInt32 bytesPerLine = mOwnerDualView->GetPaneCount(count_BytesPerLine);
	SInt32 startOffset = (inLineOffset - 1) * bytesPerLine + PosToHexPos(inStartPos);
	SInt32 endOffset = (inLineOffset - 1) * bytesPerLine + PosToHexPos(inEndPos);

	WEReference we = mOwnerDualView->GetInMemoryWE();
	WESetSelection( startOffset, endOffset, we );
	WEDelete(we);

	if (inBytesCount != 0) {
		Handle txtData;
		txtData = ::NewHandle(inBytesCount);
		WEStreamRange(inStartPos, inStartPos + inBytesCount, kTypeText, 0, txtData, GetWasteRef()) ;
		
		// Strip blanks
		StStripPeriodicalTranslator blankstripper(txtData, 3);
		blankstripper.FilterOutPeriodical();
		// Convert ascii code to hex code
		StHexToByteTranslator translator(blankstripper.GetOutHandle());
		translator.Convert();
		WEPut( kCurrentSelection, kCurrentSelection, *translator.GetOutHandle(), translator.GetOutSize(), kTextEncodingMultiRun,
					kNilOptions, 0, nil, nil, we);
	
		if (txtData != nil) {
			::DisposeHandle(txtData);
		} 
	} 
}


PP_End_Namespace_PowerPlant
