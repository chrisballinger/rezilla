// ===========================================================================
// CHexDataSubView.cp 
//                       Created: 2003-05-06 06:04:42
//             Last modification: 2004-06-17 01:24:29
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2003-2004
// All rights reserved.
// $Date$
// $Revision$
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
//	¥ CHexDataSubView						Default Constructor		  [public]
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
//	¥ CHexDataSubView						Default Constructor		  [public]
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
//	¥ CHexDataSubView						Stream Constructor		  [public]
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
//	¥ ~CHexDataSubView						Destructor				  [public]
// ---------------------------------------------------------------------------

CHexDataSubView::~CHexDataSubView()
{}


#pragma mark -

// ---------------------------------------------------------------------------
//	¥ ClickSelf											[protected, virtual]
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
	WEGetSelection(& startPos, & endPos, mWasteEditRef);
	mTxtSiblingView->SyncPositionsWithSibling(PosToHexPos(startPos), PosToHexPos(endPos));
	
	// Notify the dual view
	mOwnerDualView->BroadcastMessage(msg_DualViewEdited, this);
}



// ---------------------------------------------------------------------------
//	¥ AdjustCursorPos											[protected, virtual]
// ---------------------------------------------------------------------------

void
CHexDataSubView::AdjustCursorPos()
{
	SInt32  selStart;
	SInt32  selEnd;
	
	WEGetSelection( & selStart, & selEnd, mWasteEditRef ) ;
	WESetSelection( NearestHexPos(selStart), NearestHexPos(selEnd), mWasteEditRef);
}


// ---------------------------------------------------------------------------
//	¥ NearestHexPos											[protected, virtual]
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
//	¥ GetCurrHexPos											[public]
// ---------------------------------------------------------------------------

void
CHexDataSubView::GetCurrHexPos(SInt32 & outHexSelStart, SInt32 & outHexSelEnd)
{
	SInt32  selStart;
	SInt32  selEnd;
	WEGetSelection( & selStart, & selEnd, mWasteEditRef ) ;
	outHexSelStart = PosToHexPos(selStart);
	outHexSelEnd = PosToHexPos(selEnd);
}


// ---------------------------------------------------------------------------
//	¥ PosToHexPos											[protected, virtual]
// ---------------------------------------------------------------------------

SInt32
CHexDataSubView::PosToHexPos(SInt32 inPos)
{
	SInt32  rest = inPos % 3;
	return ( inPos - rest )/3 ;
}


// ---------------------------------------------------------------------------
//	¥ HexPosToPos											[protected, virtual]
// ---------------------------------------------------------------------------

SInt32
CHexDataSubView::HexPosToPos(SInt32 inHexPos)
{
	return (3 * inHexPos);
}


// ---------------------------------------------------------------------------
//	¥ HexPosToLine											[protected, virtual]
// ---------------------------------------------------------------------------

SInt32
CHexDataSubView::HexPosToLine(SInt32 inHexPos)
{
	SInt32 bytesPerline = mOwnerDualView->GetPaneCount(count_BytesPerLine);
	SInt32 theRest = inHexPos % bytesPerline;
	
	return (((inHexPos - theRest) / bytesPerline) + 1);
}


// ---------------------------------------------------------------------------
//	¥ GetCurrLine											[public]
// ---------------------------------------------------------------------------

SInt32
CHexDataSubView::GetCurrLine()
{
	SInt32 theHexSelStart, theHexSelEnd;
	
	GetCurrHexPos(theHexSelStart, theHexSelEnd);
	
	return HexPosToLine(theHexSelStart);
}


// ---------------------------------------------------------------------------
//	¥ GetCurrLines											[public]
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
//	¥ HandleKeyPress							[public, virtual]
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

	SInt32	lineCount = WECountLines(mWasteEditRef);
	LongRect	oldDestRect ;
	WEGetDestRect(&oldDestRect,mWasteEditRef);

	SInt32	theSelStart;
	SInt32	theSelEnd;
	WEGetSelection( & theSelStart, & theSelEnd, mWasteEditRef);
	
	StFocusAndClipIfHidden	focus(this);

	switch (theKeyStatus) {
		
		case keyStatus_Input: {
			if (mTypingAction == nil) {
				mTypingAction = new CHexEditorTypingAction(mWasteEditRef, this, this);
				PostAction(mTypingAction);
			}
			
			if (mTypingAction != nil) {
				try {
					mTypingAction->InputCharacter();
				} catch(...) {
					PostAction(nil);
				}
			}
			
			char * buffer = new char[3];
			
			if (!mOneOfTwoInserted) {
				sprintf(buffer, "0%.1x ", UCodeTranslator::ConvertHexToValue(theKey));
				Insert(buffer,3);
				mEditingPos = theSelStart + 3;
				mOneOfTwoInserted = true;
			} else {
				if (mEditingPos == theSelStart) {
					WESetSelection( mEditingPos - 3, mEditingPos - 2, mWasteEditRef);
					WEDelete(mWasteEditRef);
					WESetSelection( mEditingPos - 2, mEditingPos - 2, mWasteEditRef);
					sprintf(buffer, "%.1x", UCodeTranslator::ConvertHexToValue(theKey));
					Insert(buffer,1);
					WESetSelection( mEditingPos, mEditingPos, mWasteEditRef);
					theSelStart -= 3;
				} 
				mOneOfTwoInserted = false;
			}
// 			ForceAutoScroll(oldDestRect);
			UserChangedText(theSelStart, theSelEnd, 3);
			break;
		}
		
	  
		case keyStatus_TEDelete: {
				if (mTypingAction == nil) {
					mTypingAction = new CHexEditorTypingAction(mWasteEditRef, this, this);
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
					WESetSelection( theSelStart, theSelEnd, mWasteEditRef ) ;
				}
				WEDelete(mWasteEditRef);
				UserChangedText(theSelStart, theSelEnd, 0);
				mOneOfTwoInserted = false;
			break;
		}
		
		case keyStatus_TECursor: {
			if (theSelStart != theSelEnd) {
				if (theKey == char_RightArrow || theKey == char_DownArrow) {
					WESetSelection( theSelEnd, theSelEnd, mWasteEditRef);
				} else {
					WESetSelection( theSelStart, theSelStart, mWasteEditRef);
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
					WESetSelection( theSelStart, theSelStart, mWasteEditRef);
				}
				CursorMoved(theSelStart);
			}
			mOneOfTwoInserted = false;
			break;
		}

		case keyStatus_ExtraEdit: {
			if (theKey == char_FwdDelete) {

				if (theSelStart < WEGetTextLength(mWasteEditRef)) {
					if (mTypingAction == nil) {
						mTypingAction = new CHexEditorTypingAction(mWasteEditRef, this, this);
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
						WESetSelection(theSelStart,theSelEnd, mWasteEditRef);
					}

					WEDelete(mWasteEditRef);
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

	if ((theTarget == GetTarget()) && (lineCount != WECountLines(mWasteEditRef))) {
		AdjustImageToText();
	}

	// Notify the dual view
	mOwnerDualView->BroadcastMessage(msg_DualViewEdited, this);

	return keyHandled;
}


// ---------------------------------------------------------------------------
//	¥ ObeyCommand							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CHexDataSubView::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;
	
	if ( mWasteEditRef == nil )
		return cmdHandled;

	LongRect	oldDestRect ;
	WEGetDestRect(&oldDestRect,mWasteEditRef);

	switch (inCommand) {

		case cmd_Copy: 
		case cmd_Cut: 
		case cmd_Clear:
		case cmd_Paste:  {
			mOwnerDualView->SetCurrentSubView(hex_hexpane);
			cmdHandled = mOwnerDualView->ObeyCommand(inCommand, ioParam);
			break;
		}

		case cmd_ActionDeleted: {
			if (mTypingAction == static_cast<CHexEditorTypingAction*>(ioParam)) {
				mTypingAction = nil;
			}
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
			AdjustImageToText();
			ForceAutoScroll(oldDestRect);
			break;
		}

		default:
			cmdHandled = LCommander::ObeyCommand(inCommand, ioParam);
			break;
	}

	return cmdHandled;
}


// ---------------------------------------------------------------------------
//	¥ ScrollImageBy											[public, virtual]
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
//	¥ CursorMoved							[public, virtual]
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
//	¥ Insert								[public, virtual]
// ---------------------------------------------------------------------------
//	Will optionally recalculate, autoscroll, and refresh the text if desired.

OSErr
CHexDataSubView::Insert(
					   const void*		inText,
					   SInt32			inLength,
					   StScrpHandle		inStyleH,
					   Boolean			inRefresh )
{
	LongRect	oldDestRect ;
	OSErr		err;
	
	StFocusAndClipIfHidden	focus(this);

	WEGetDestRect(&oldDestRect,mWasteEditRef);
	
	if ( !mMonoStyled && (inStyleH != nil) ) {
		err = WEInsert(inText, inLength, (StScrpHandle) inStyleH, nil, mWasteEditRef ) ;
	} else {
		err = WEInsert(inText, inLength, nil, nil, mWasteEditRef);
	}
	
	// Force a redraw. The WasteEdit internals are updated, so we need to
	// reflect this fact.
	if ( inRefresh ) {
		AdjustImageToText();
		ForceAutoScroll( oldDestRect );
		Refresh();
	}
	return err;
}


// ---------------------------------------------------------------------------
//	¥ Insert								[public, virtual]
// ---------------------------------------------------------------------------

OSErr
CHexDataSubView::Insert(
					   Str255 		inString,
					   Boolean		inRefresh )
{
	char * theStr = new char[256];
	CopyPascalStringToC(inString,theStr);	
	return Insert(theStr, inRefresh);
}


// ---------------------------------------------------------------------------
//	¥ InsertContents								[public, virtual]
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
	WESetSelection(0, 0, mWasteEditRef);
}


// ---------------------------------------------------------------------------
//	¥ InsertContents								[public, virtual]
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
	WESetSelection(0, 0, mWasteEditRef);
}


// ---------------------------------------------------------------------------
//	¥ UserChangedText						[public, virtual]
// ---------------------------------------------------------------------------
//	Text of WasteEdit has changed as a result of user action

void
CHexDataSubView::UserChangedText()
{
	CWasteEditView::UserChangedText();
}


// ---------------------------------------------------------------------------
//	¥ UserChangedText						[public, virtual]
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
//	¥ SyncContentsWithMemory
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

	WEReference we = mOwnerDualView->GetInMemoryWasteRef();
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
		WEInsert(*translator.GetOutHandle(), translator.GetOutSize(), nil, nil, we);
	
		if (txtData != nil) {
			::DisposeHandle(txtData);
		} 
	} 
}


// ---------------------------------------------------------------------------
//	¥ BeTarget								[protected, virtual]
// ---------------------------------------------------------------------------
//	WasteEdit is becoming the Target

void
CHexDataSubView::BeTarget()
{
	StFocusAndClipIfHidden	focus(this);

	WEActivate(mWasteEditRef);		// Show active selection

	StartIdling();					// Idle time used to flash the cursor

	Rect	theFrame;
	CalcLocalFrameRect(theFrame);
	
	
	
	
	
// 	StColorPenState	savePenState;		// Will save and restore pen state
// 	Rect	theFrame;
// 	CalcLocalFrameRect(theFrame);
// 	RGBColor	Color_Some	= { 65535, 0, 65535 };
// 	PenState		thePenState;
// 	thePenState.pnLoc = Point_00;
// 	thePenState.pnSize.h = 2;
// 	thePenState.pnSize.v = 2;
// 	thePenState.pnMode = patCopy;
// 	UQDGlobals::GetBlackPat(&thePenState.pnPat);
// 	RGBColor theForeColor = Color_Some;
// 	RGBColor theBackColor = Color_White;
// 
// 	ThemeDrawState	state = kThemeStateInactive;
// 	if (IsActive() && IsEnabled()) {
// 		state = kThemeStateActive;
// 	}
// 
// 	::MacInsetRect(&theFrame, 3, 3);
// 	
// 	::SetPenState(&thePenState);
// 	::RGBForeColor(&theForeColor);
// 	::RGBBackColor(&theBackColor);
// // 	::MacFrameRect(&theFrame);
// // 	if (((CWasteEditView*) mControlPane)->HasFocusRing()) {
// 		::DrawThemeEditTextFrame(&theFrame, state);
// 		::DrawThemeFocusRegion(StRegion(theFrame), true);
// // 		DrawFocusBorder(frame, true);
// 
// // 	} else {
// // 		::DrawThemeFocusRegion(StRegion(theFrame), false);
// // // 		DrawFocusBorder(frame, false);
// // 		::DrawThemeEditTextFrame(&theFrame, state);
// // 	}
	
	sWasteEditViewP = nil;
	if ( mAutoScroll ) {
		sWasteEditViewP = this;		// Ensure we autoscroll correctly
	}
}


PP_End_Namespace_PowerPlant
