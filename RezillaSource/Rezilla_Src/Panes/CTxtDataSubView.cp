// ===========================================================================
// CTxtDataSubView.cp 
//                       Created: 2003-05-06 06:04:42
//             Last modification: 2004-06-17 10:01:00
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

#include "CTxtDataSubView.h"
#include "CHexDataSubView.h"
#include "CDualDataView.h"
#include "CSingleScrollBar.h"
#include "CWEViewActions.h"
#include "CHexEditorActions.h"
#include "UCodeTranslator.h"
#include "UHexFilters.h"
#include "RezillaConstants.h"

#include <UDesktop.h>
#include <LScrollBar.h>
#include <UKeyFilters.h>


PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//	¥ CTxtDataSubView						Default Constructor		  [public]
// ---------------------------------------------------------------------------

CTxtDataSubView::CTxtDataSubView()
	: CWasteEditView()
{
	mHexSiblingView = nil;
	mIsSynchronizing = false;
}


// ---------------------------------------------------------------------------
//	¥ CTxtDataSubView						Constructor		  [public]
// ---------------------------------------------------------------------------

CTxtDataSubView::CTxtDataSubView(CHexDataSubView * inSiblingView)
	: CWasteEditView()
{
	mHexSiblingView = inSiblingView;
	mIsSynchronizing = false;
}


// ---------------------------------------------------------------------------
//	¥ CTxtDataSubView						Parameterized Constructor [public]
// ---------------------------------------------------------------------------

CTxtDataSubView::CTxtDataSubView(
	const SPaneInfo&	inPaneInfo,
	const SViewInfo&	inViewInfo,
	UInt16				inTextAttributes,
	ResIDT				inTextTraitsID,
	Boolean				inReadOnly,
	Boolean				inWordWrap,
	Boolean				inSelectable)

	: CWasteEditView(inPaneInfo, inViewInfo, inTextAttributes, 
					 inTextTraitsID, inReadOnly, inWordWrap, inSelectable)
{
}


// ---------------------------------------------------------------------------
//	¥ CTxtDataSubView						Stream Constructor		  [public]
// ---------------------------------------------------------------------------

CTxtDataSubView::CTxtDataSubView(
	LStream*	inStream)
	: CWasteEditView(inStream)
{
	mHexSiblingView = nil;
	mIsSynchronizing = false;
}


// ---------------------------------------------------------------------------
//	¥ ~CTxtDataSubView						Destructor				  [public]
// ---------------------------------------------------------------------------

CTxtDataSubView::~CTxtDataSubView()
{}


#pragma mark -

// ---------------------------------------------------------------------------
//	¥ ClickSelf											[protected, virtual]
// ---------------------------------------------------------------------------

void
CTxtDataSubView::ClickSelf(
	const SMouseDownEvent	&inMouseDown)
{
	SInt32	startPos,	endPos;
	
	mOwnerDualView->SetSelectingAll(false);
	CWasteEditView::ClickSelf(inMouseDown);
	AdjustCursorPos();

	// Synchronize sibling
	WEGetSelection(& startPos, & endPos, mWasteEditRef);
	mHexSiblingView->SyncPositionsWithSibling(PosToCharPos(startPos), 
											  PosToCharPos(endPos));
	// Notify the dual view
	mOwnerDualView->BroadcastMessage(msg_DualViewEdited, this);
}


// ---------------------------------------------------------------------------
//	¥ AdjustCursorPos											[protected, virtual]
// ---------------------------------------------------------------------------

void
CTxtDataSubView::AdjustCursorPos()
{
	SInt32  selStart;
	SInt32  selEnd;
	
	WEGetSelection( & selStart, & selEnd, mWasteEditRef ) ;
	WESetSelection( NearestCharPos(selStart), NearestCharPos(selEnd), mWasteEditRef);
}


// ---------------------------------------------------------------------------
//	¥ NearestCharPos											[protected, virtual]
// ---------------------------------------------------------------------------
// Returns the nearest pos just before a char value

SInt32
CTxtDataSubView::NearestCharPos(SInt32 inPos)
{
	return (inPos + (inPos % 2));
}


// ---------------------------------------------------------------------------
//	¥ GetCurrCharPos											[public]
// ---------------------------------------------------------------------------

void
CTxtDataSubView::GetCurrCharPos(SInt32 & outCharSelStart, SInt32 & outCharSelEnd)
{
	SInt32  selStart;
	SInt32  selEnd;
	WEGetSelection( & selStart, & selEnd, mWasteEditRef ) ;
	outCharSelStart = PosToCharPos(selStart);
	outCharSelEnd = PosToCharPos(selEnd);
}


// ---------------------------------------------------------------------------
//	¥ PosToCharPos											[protected, virtual]
// ---------------------------------------------------------------------------

SInt32
CTxtDataSubView::PosToCharPos(SInt32 inPos)
{
	SInt32  rest = inPos % 2;
	return ( inPos - rest )/2 ;
}


// ---------------------------------------------------------------------------
//	¥ CharPosToPos											[protected, virtual]
// ---------------------------------------------------------------------------

SInt32
CTxtDataSubView::CharPosToPos(SInt32 inCharPos)
{
	return (2 * inCharPos);
}


// ---------------------------------------------------------------------------
//	¥ CharPosToLine											[protected, virtual]
// ---------------------------------------------------------------------------

SInt32
CTxtDataSubView::CharPosToLine(SInt32 inCharPos)
{
	SInt32 bytesPerline = mOwnerDualView->GetPaneCount(count_BytesPerLine);
	SInt32 theRest = inCharPos % bytesPerline;
	
	return (((inCharPos - theRest) / bytesPerline) + 1);
}


// ---------------------------------------------------------------------------
//	¥ GetCurrLine											[public]
// ---------------------------------------------------------------------------

SInt32
CTxtDataSubView::GetCurrLine()
{
	SInt32 theCharSelStart, theCharSelEnd;
	
	GetCurrCharPos(theCharSelStart, theCharSelEnd);
	
	return CharPosToLine(theCharSelStart);
}


// ---------------------------------------------------------------------------
//	¥ GetCurrLines											[public]
// ---------------------------------------------------------------------------

void
CTxtDataSubView::GetCurrLines(SInt32 & outFirstLine, SInt32 & outLastLine)
{
	SInt32 theCharSelStart, theCharSelEnd;
	
	GetCurrCharPos(theCharSelStart, theCharSelEnd);
	
	outFirstLine = CharPosToLine(theCharSelStart);
	outLastLine = CharPosToLine(theCharSelEnd);
}


#pragma mark -

// ---------------------------------------------------------------------------
//	¥ HandleKeyPress							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CTxtDataSubView::HandleKeyPress(
	const EventRecord	&inKeyEvent)
{
	Boolean		keyHandled	 = true;
	EKeyStatus	theKeyStatus = keyStatus_Input;
	SInt16		theKey		 = (SInt16) (inKeyEvent.message & charCodeMask);
	LCommander*	theTarget	 = GetTarget();

	if (inKeyEvent.modifiers & cmdKey) {	// Always pass up when the
		theKeyStatus = keyStatus_PassUp;	// command key is down
	} else {

		theKeyStatus = UKeyFilters::PrintingCharField(inKeyEvent);
	}

// 	if ((theKeyStatus == keyStatus_PassUp) && (theKey == char_Return)) {
// 		theKeyStatus = keyStatus_Input;		// Special case for Return key
// 	}

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
			
			WEKey(theKey,inKeyEvent.modifiers, mWasteEditRef);
			WEKey(' ',inKeyEvent.modifiers, mWasteEditRef);			
			UserChangedText(theSelStart, theSelEnd, 2);
			break;
		}
		
	  
		case keyStatus_TEDelete: {

			if (theSelEnd > 0) {
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
				
				if (theSelStart == theSelEnd && theSelStart >= 2) {
					theSelStart -= 2;
					WESetSelection( theSelStart, theSelEnd, mWasteEditRef ) ;
				}
				WEDelete(mWasteEditRef);
				ForceAutoScroll(oldDestRect);
				UserChangedText(theSelStart, theSelEnd, 0);
			}
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
					theSelStart -= 2;
					break;
					
					case char_RightArrow:
					theSelStart += 2;
					break;
					
					case char_DownArrow:
					theSelStart += CharPosToPos(mOwnerDualView->GetPaneCount(count_BytesPerLine));
					break;
					
					case char_UpArrow:
					theSelStart -= CharPosToPos(mOwnerDualView->GetPaneCount(count_BytesPerLine));
					break;
				}
				if (theSelStart >= 0 && PosToCharPos(theSelStart) <= mOwnerDualView->GetPaneCount(count_BytesPerPane)) {
					WESetSelection( theSelStart, theSelStart, mWasteEditRef);
				}
				CursorMoved(theSelStart);
			}
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
						theSelEnd += 2;
						WESetSelection(theSelStart,theSelEnd, mWasteEditRef);
					}

					WEDelete(mWasteEditRef);
					ForceAutoScroll(oldDestRect);
					UserChangedText(theSelStart, theSelEnd, 0);
				}
			} else {
				keyHandled = LCommander::HandleKeyPress(inKeyEvent);
			}
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
//	¥ ObeyCommand											[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CTxtDataSubView::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;
	
	if ( mWasteEditRef == nil )
		return cmdHandled;

	LongRect	oldDestRect ;
	WEGetDestRect(&oldDestRect,mWasteEditRef);

	mOwnerDualView->SetCurrentSubView(hex_txtpane);
	
	switch (inCommand) {

		case cmd_Copy: 
		case cmd_Cut: 
		case cmd_Clear:
		case cmd_Paste:  {
			mOwnerDualView->SetCurrentSubView(hex_txtpane);
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
			mHexSiblingView->SelectAll();
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
//	¥ ScrollImageBy											[public, virtual]
// ---------------------------------------------------------------------------
//	Scroll the Text

void
CTxtDataSubView::ScrollImageBy(
	SInt32		inHorizDelta,
	SInt32		inVertDelta,
	Boolean		inRefresh)
{
	CWasteEditView::ScrollImageBy(inHorizDelta, inVertDelta, inRefresh);

	if (!mIsSynchronizing) {
		mHexSiblingView->SetSynchronizing(true);
		mHexSiblingView->ScrollImageBy(inHorizDelta, inVertDelta, inRefresh);
	} 

	SetSynchronizing(false);
}


// ---------------------------------------------------------------------------
//	¥ Insert								[public, virtual]
// ---------------------------------------------------------------------------
//	Will optionally recalculate, autoscroll, and refresh the text if desired.

OSErr
CTxtDataSubView::Insert(
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
CTxtDataSubView::Insert(
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
CTxtDataSubView::InsertContents(Handle inHandle)
{
	StSegmTextTranslator translator(inHandle, mOwnerDualView->GetPaneCount(count_BytesPerLine) );
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
CTxtDataSubView::InsertContents(const void * inPtr, SInt32 inByteCount)
{
	StSegmTextTranslator translator(inPtr, inByteCount, mOwnerDualView->GetPaneCount(count_BytesPerLine));
	translator.Convert();
	
	// Empty the Waste edit
	DeleteAll();
	// Put the contents in the hex view and clear the dirty flag.
	SetTextHandle( translator.GetOutHandle() );
	WESetSelection(0, 0, mWasteEditRef);
}


// ---------------------------------------------------------------------------
//	¥ CursorMoved							[public, virtual]
// ---------------------------------------------------------------------------

void
CTxtDataSubView::CursorMoved(SInt32 inPos)
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
		newTxtPos = CharPosToPos(mOwnerDualView->GetPaneCount(count_BytesPerLine)) + inPos;
		DisplaySelectionRange( newTxtPos, newTxtPos);
	} else if (PosToCharPos(inPos) > mOwnerDualView->GetPaneCount(count_BytesPerPane)) {
		if (firstLine > lastLine - mOwnerDualView->GetPaneCount(count_LinesPerPane)) return;
		firstLine += 1;
		// Sync the scrollbar: this provokes a redraw because 
		// the scrollbar emits its message.
		mOwnerDualView->GetScroller()->SetValue(firstLine);
		// Update the cursor's pos
		newTxtPos = inPos - CharPosToPos(mOwnerDualView->GetPaneCount(count_BytesPerLine));
		DisplaySelectionRange( newTxtPos, newTxtPos);
	} else {
		newTxtPos = inPos;
	}
	// Sync the sibling
	newHexPos = mHexSiblingView->HexPosToPos( PosToCharPos(newTxtPos) );
	mHexSiblingView->DisplaySelectionRange(newHexPos, newHexPos);
// 	// Notify the dual view
// 	mOwnerDualView->BroadcastMessage(msg_DualViewEdited, this);
}


// ---------------------------------------------------------------------------
//	¥ UserChangedText						[public, virtual]
// ---------------------------------------------------------------------------
//	Text of WasteEdit has changed as a result of user action

void
CTxtDataSubView::UserChangedText()
{
	CWasteEditView::UserChangedText();
}


// ---------------------------------------------------------------------------
//	¥ UserChangedText						[public, virtual]
// ---------------------------------------------------------------------------
//	Text of WasteEdit has changed as a result of user action

void
CTxtDataSubView::UserChangedText(
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
			inStartPos += CharPosToPos(mOwnerDualView->GetPaneCount(count_BytesPerLine));
		} else {
			inStartPos = 0;
		}
	} 
	// If the cursor was at the end of the frame and we insert chars, bring the 
	// next line in view. Create it if necessary.
	if ( inStartPos == CharPosToPos(mOwnerDualView->GetPaneCount(count_BytesPerPane)) && inBytesCount > 0) {
		firstLine += 1;
		mOwnerDualView->SetCurrFirstLine(firstLine);
		inStartPos -= CharPosToPos(mOwnerDualView->GetPaneCount(count_BytesPerLine));
	} 

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
	mHexSiblingView->SyncPositionsWithSibling(PosToCharPos(newPos), PosToCharPos(newPos));
}


// ---------------------------------------------------------------------------
//	¥ SyncPositionsWithSibling
// ---------------------------------------------------------------------------

void
CTxtDataSubView::SyncPositionsWithSibling(SInt32 inStartPos, SInt32 inEndPos)
{
	DisplaySelectionRange(CharPosToPos(inStartPos), CharPosToPos(inEndPos));
}


// ---------------------------------------------------------------------------
//	¥ SyncContentsWithMemory
// ---------------------------------------------------------------------------

void
CTxtDataSubView::SyncContentsWithMemory(SInt32 inStartPos, 
										SInt32 inEndPos, 
										SInt32 inBytesCount, 
										SInt32 inLineOffset)
{
	SInt32 bytesPerLine = mOwnerDualView->GetPaneCount(count_BytesPerLine);
	SInt32 startOffset = (inLineOffset - 1) * bytesPerLine + PosToCharPos(inStartPos);
	SInt32 endOffset = (inLineOffset - 1) * bytesPerLine + PosToCharPos(inEndPos);

	WEReference we = mOwnerDualView->GetInMemoryWasteRef();
	WESetSelection( startOffset, endOffset, we );
	WEDelete(we);

	if (inBytesCount != 0) {
		Handle txtData;
		txtData = ::NewHandle(inBytesCount);
		WEStreamRange(inStartPos, inStartPos + inBytesCount, kTypeText, 0, txtData, GetWasteRef()) ;
		
		// Strip blanks
		StStripPeriodicalTranslator blankstripper(txtData, 2);
		blankstripper.FilterOutPeriodical();
		WEInsert(*blankstripper.GetOutHandle(), blankstripper.GetOutSize(), nil, nil, we);
	
		if (txtData != nil) {
			::DisposeHandle(txtData);
		} 
	} 
}




PP_End_Namespace_PowerPlant
