// ===========================================================================
// CHexDataSubView.cp 
//                       Created: 2003-05-06 06:04:42
//             Last modification: 2003-06-07 15:57:01
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2003
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include <LScrollBar.h>
#include <UKeyFilters.h>
#include <Quickdraw.h>
#include <Sound.h>

#include "CHexDataSubView.h"
#include "CTxtDataSubView.h"
#include "CHexEditorWindow.h"
#include "CRezClipboard.h"
#include "CWEViewActions.h"
#include "CHexEditorActions.h"
#include "UCodeTranslator.h"
#include "RezillaConstants.h"

PP_Begin_Namespace_PowerPlant



// ---------------------------------------------------------------------------
//	¥ CHexDataSubView						Default Constructor		  [public]
// ---------------------------------------------------------------------------

CHexDataSubView::CHexDataSubView()
	: CHexDataWE()
{
	mTxtSiblingView = nil;
	mIsSynchronizing = false;
}


// ---------------------------------------------------------------------------
//	¥ CHexDataSubView						Default Constructor		  [public]
// ---------------------------------------------------------------------------

CHexDataSubView::CHexDataSubView(CTxtDataSubView * inSiblingView)
	: CHexDataWE()
{
	mTxtSiblingView = inSiblingView;
	mIsSynchronizing = false;
}


// ---------------------------------------------------------------------------
//	¥ CHexDataSubView						Stream Constructor		  [public]
// ---------------------------------------------------------------------------

CHexDataSubView::CHexDataSubView(
	LStream*	inStream)
	: CHexDataWE(inStream)
{
	mTxtSiblingView = nil;
	mIsSynchronizing = false;
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
	CHexDataWE::ClickSelf(inMouseDown);

	// Synchronize sibling
	WEGetSelection(& startPos, & endPos, mWasteEditRef);
	mTxtSiblingView->SyncPositionsWithSibling(PosToHexPos(startPos), 
											  PosToHexPos(endPos));
	// Update the window's fields
	mEditorWindow->SetLineValues();
	mEditorWindow->SetOffsetValues();
}


// ---------------------------------------------------------------------------
//	¥ HandleKeyPress							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CHexDataSubView::HandleKeyPress(
	const EventRecord	&inKeyEvent)
{	
	Boolean retval;
	UInt16 theChar = (UInt16) (inKeyEvent.message & charCodeMask);
	
	retval = CHexDataWE::HandleKeyPress(inKeyEvent);
	// Update the window's fields
	mEditorWindow->SetLineValues();
	mEditorWindow->SetOffsetValues();

	return retval;
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

		case cmd_Copy: {
			Handle txtData;
			SInt32 startPos, endPos;
			WEGetSelection( &startPos, &endPos, mWasteEditRef );
			
			txtData = ::NewHandle(endPos - startPos);
			WEStreamRange(startPos, endPos, kTypeText, 0, txtData, mWasteEditRef) ;
			
			// Strip blanks
			StStripPeriodicalTranslator blankstripper(txtData, 3);
			blankstripper.FilterOutPeriodical();
			
			CRezClipboard::SetScrapContext(scrap_hexeditHexdata);
			CRezClipboard::GetClipboard()->SetData(ResType_Text, blankstripper.GetOutHandle(), true);
			
			if (txtData != nil) {
				::DisposeHandle(txtData);
			} 
			break;
		}

		case cmd_Paste: 
		case cmd_Cut: 
		case cmd_Clear: {
			mEditorWindow->SetCurrentSubView(hex_hexpane);
			cmdHandled = mEditorWindow->ObeyCommand(inCommand, ioParam);
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
	SInt32 firstLine = mEditorWindow->GetCurrFirstLine();
	SInt32 lastLine = mEditorWindow->HexLineCount();
	SInt32 newHexPos, newTxtPos;
	
	if (inPos < 0) {
		if (firstLine <= 1) return;
		firstLine -= 1;
		// Sync the scrollbar: this provokes a redraw because 
		// the scrollbar emits its message.
		mEditorWindow->GetScroller()->SetValue(firstLine);
		// Update the cursor's pos
		newHexPos = HexPosToPos(kRzilHexEditBytesPerLine) + inPos;
		DisplaySelectionRange( newHexPos, newHexPos);
	} else if (PosToHexPos(inPos) > kRzilHexEditBytesPerPane) {
		if (firstLine > lastLine - kRzilHexEditLineCount) return;
		firstLine += 1;
		// Sync the scrollbar: this provokes a redraw because 
		// the scrollbar emits its message.
		mEditorWindow->GetScroller()->SetValue(firstLine);
		// Update the cursor's pos
		newHexPos = inPos - HexPosToPos(kRzilHexEditBytesPerLine);
		DisplaySelectionRange( newHexPos, newHexPos);
	} else {
		newHexPos = inPos;
	}
	// Sync the sibling
	newTxtPos = mTxtSiblingView->CharPosToPos( PosToHexPos(newHexPos) );
	mTxtSiblingView->DisplaySelectionRange(newTxtPos, newTxtPos);
	// Update the window's fields
	mEditorWindow->SetLineValues();
	mEditorWindow->SetOffsetValues();
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
	
	SInt32 firstLine = mEditorWindow->GetCurrFirstLine();
	SInt32 oldLineCount = mEditorWindow->HexLineCount();
	
	// Synchronize in-memory Waste
	SyncContentsWithMemory(inStartPos, inEndPos, inBytesCount, firstLine);
	
	SInt32 newLineCount = mEditorWindow->HexLineCount();
	
	// If the cursor was at the beginning of the frame and we moved back, bring the 
	// previous line (if any) in view.
	if (inStartPos < 0) {
		if (firstLine > 1) {
			firstLine -= 1;
			mEditorWindow->SetCurrFirstLine(firstLine);
			inStartPos += HexPosToPos(kRzilHexEditBytesPerLine);
		} else {
			inStartPos = 0;
		}
	} 
	// If the cursor was at the end of the frame and we insert chars, bring the 
	// next line in view. Create it if necessary.
	if ( inStartPos == HexPosToPos(kRzilHexEditBytesPerPane) && inBytesCount > 0) {
		firstLine += 1;
		mEditorWindow->SetCurrFirstLine(firstLine);
		inStartPos -= HexPosToPos(kRzilHexEditBytesPerLine);
		if (mOneOfTwoInserted) {
			mEditingPos = inStartPos + inBytesCount;
		} 
	} 
	// Redraw accordingly
	if (oldLineCount == newLineCount) {
		// Redraw subviews
		mEditorWindow->InstallContentsFromLine(firstLine);
	} else if (oldLineCount < newLineCount) {
		// Update the scrollbar's max value
		mEditorWindow->SetMaxScrollerValue();
		// Provoke a redraw of the subviews
		mEditorWindow->GetScroller()->SetValue(firstLine);
	} else {
		// Update the scrollbar's max value. Since it is smaller, 
		// the scrollbar provokes a redraw.
		mEditorWindow->SetMaxScrollerValue();
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
	SInt32 startOffset = (inLineOffset - 1) * kRzilHexEditBytesPerLine + PosToHexPos(inStartPos);
	SInt32 endOffset = (inLineOffset - 1) * kRzilHexEditBytesPerLine + PosToHexPos(inEndPos);

	WEReference we = mEditorWindow->GetInMemoryWasteRef();
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
		StHexToCodeTranslator translator(blankstripper.GetOutHandle());
		translator.HexToCode();
		WEInsert(*translator.GetOutHandle(), translator.GetOutSize(), nil, nil, we);
	
		if (txtData != nil) {
			::DisposeHandle(txtData);
		} 
	} 
}


// ---------------------------------------------------------------------------
//	¥ SyncImageWithSibling
// ---------------------------------------------------------------------------

void
CHexDataSubView::SyncImageWithSibling(SInt32		inHorizDelta,
										SInt32		inVertDelta,
										Boolean		inRefresh)
{
	mIsSynchronizing = true;
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
