// ===========================================================================
// CTxtDataSubView.cp 
//                       Created : 2003-05-06 06:04:42
//             Last modification : 2003-06-07 15:56:53
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@easyconnect.fr>
// www : <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright : Bernard Desgraupes 2003
// All rights reserved.
// ===========================================================================


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include <LScrollBar.h>
#include <UKeyFilters.h>
#include <Quickdraw.h>
#include <Sound.h>

#include "CTxtDataSubView.h"
#include "CHexDataSubView.h"
#include "CHexEditorWindow.h"
#include "CRezClipboard.h"
#include "CWEViewActions.h"
#include "CHexEditorActions.h"
#include "UCodeTranslator.h"
#include "RezillaConstants.h"

PP_Begin_Namespace_PowerPlant



// ---------------------------------------------------------------------------
//	€ CTxtDataSubView						Default Constructor		  [public]
// ---------------------------------------------------------------------------

CTxtDataSubView::CTxtDataSubView()
	: CTxtDataWE()
{
	mHexSiblingView = nil;
	mIsSynchronizing = false;
}


// ---------------------------------------------------------------------------
//	€ CTxtDataSubView						Constructor		  [public]
// ---------------------------------------------------------------------------

CTxtDataSubView::CTxtDataSubView(CHexDataSubView * inSiblingView)
	: CTxtDataWE()
{
	mHexSiblingView = inSiblingView;
	mIsSynchronizing = false;
}


// ---------------------------------------------------------------------------
//	€ CTxtDataSubView						Stream Constructor		  [public]
// ---------------------------------------------------------------------------

CTxtDataSubView::CTxtDataSubView(
	LStream*	inStream)
	: CTxtDataWE(inStream)
{
	mHexSiblingView = nil;
	mIsSynchronizing = false;
}


// ---------------------------------------------------------------------------
//	€ ~CTxtDataSubView						Destructor				  [public]
// ---------------------------------------------------------------------------

CTxtDataSubView::~CTxtDataSubView()
{}


#pragma mark -

// ---------------------------------------------------------------------------
//	€ ClickSelf											[protected, virtual]
// ---------------------------------------------------------------------------

void
CTxtDataSubView::ClickSelf(
	const SMouseDownEvent	&inMouseDown)
{
	SInt32	startPos,	endPos;
	CTxtDataWE::ClickSelf(inMouseDown);

	// Synchronize sibling
	WEGetSelection(& startPos, & endPos, mWasteEditRef);
	mHexSiblingView->SyncPositionsWithSibling(PosToCharPos(startPos), 
											  PosToCharPos(endPos));
	// Update the window's fields
	mEditorWindow->SetLineValues();
	mEditorWindow->SetOffsetValues();
}


// ---------------------------------------------------------------------------
//	€ HandleKeyPress							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CTxtDataSubView::HandleKeyPress(
	const EventRecord	&inKeyEvent)
{
	Boolean retval;
	UInt16 theChar = (UInt16) (inKeyEvent.message & charCodeMask);
	
	retval = CTxtDataWE::HandleKeyPress(inKeyEvent);
	// Update the window's fields
	mEditorWindow->SetLineValues();
	mEditorWindow->SetOffsetValues();

	return retval;
}


// ---------------------------------------------------------------------------
//	€ ObeyCommand											[public, virtual]
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

	mEditorWindow->SetCurrentSubView(hex_txtpane);
	
	switch (inCommand) {

		case cmd_Copy: {
			Handle txtData;
			SInt32 startPos, endPos;
			WEGetSelection( &startPos, &endPos, mWasteEditRef );
			
			txtData = ::NewHandle(endPos - startPos);
			WEStreamRange(startPos, endPos, kTypeText, 0, txtData, mWasteEditRef) ;
			
			// Strip blanks
			StStripPeriodicalTranslator blankstripper(txtData, 2);
			blankstripper.FilterOutPeriodical();
			
			CRezClipboard::SetScrapContext(scrap_hexeditTxtdata);
			CRezClipboard::GetClipboard()->SetData(ResType_Text, blankstripper.GetOutHandle(), true);
			
			if (txtData != nil) {
				::DisposeHandle(txtData);
			} 
			break;
		}

		case cmd_Paste: 
		case cmd_Cut: 
		case cmd_Clear: {
			mEditorWindow->SetCurrentSubView(hex_txtpane);
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
			cmdHandled = mEditorWindow->ObeyCommand(inCommand, ioParam);
// 			cmdHandled = LCommander::ObeyCommand(inCommand, ioParam);
			break;
	}

	return cmdHandled;
}


// ---------------------------------------------------------------------------
//	€ ScrollImageBy											[public, virtual]
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
//	€ CursorMoved							[public, virtual]
// ---------------------------------------------------------------------------

void
CTxtDataSubView::CursorMoved(SInt32 inPos)
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
		newTxtPos = CharPosToPos(kRzilHexPerLine) + inPos;
		DisplaySelectionRange( newTxtPos, newTxtPos);
	} else if (PosToCharPos(inPos) > kRzilHexPerPane) {
		if (firstLine > lastLine - kRzilHexLineCount) return;
		firstLine += 1;
		// Sync the scrollbar: this provokes a redraw because 
		// the scrollbar emits its message.
		mEditorWindow->GetScroller()->SetValue(firstLine);
		// Update the cursor's pos
		newTxtPos = inPos - CharPosToPos(kRzilHexPerLine);
		DisplaySelectionRange( newTxtPos, newTxtPos);
	} else {
		newTxtPos = inPos;
	}
	// Sync the sibling
	newHexPos = mHexSiblingView->HexPosToPos( PosToCharPos(newTxtPos) );
	mHexSiblingView->DisplaySelectionRange(newHexPos, newHexPos);
	// Update the window's fields
	mEditorWindow->SetLineValues();
	mEditorWindow->SetOffsetValues();
}


// ---------------------------------------------------------------------------
//	€ UserChangedText						[public, virtual]
// ---------------------------------------------------------------------------
//	Text of WasteEdit has changed as a result of user action

void
CTxtDataSubView::UserChangedText()
{
	CWasteEditView::UserChangedText();
}


// ---------------------------------------------------------------------------
//	€ UserChangedText						[public, virtual]
// ---------------------------------------------------------------------------
//	Text of WasteEdit has changed as a result of user action

void
CTxtDataSubView::UserChangedText(
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
			inStartPos += CharPosToPos(kRzilHexPerLine);
		} else {
			inStartPos = 0;
		}
	} 
	// If the cursor was at the end of the frame and we insert chars, bring the 
	// next line in view. Create it if necessary.
	if ( inStartPos == CharPosToPos(kRzilHexPerPane) && inBytesCount > 0) {
		firstLine += 1;
		mEditorWindow->SetCurrFirstLine(firstLine);
		inStartPos -= CharPosToPos(kRzilHexPerLine);
	} 

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
	mHexSiblingView->SyncPositionsWithSibling(PosToCharPos(newPos), PosToCharPos(newPos));
}


// ---------------------------------------------------------------------------
//	€ SyncPositionsWithSibling
// ---------------------------------------------------------------------------

void
CTxtDataSubView::SyncPositionsWithSibling(SInt32 inStartPos, SInt32 inEndPos)
{
	DisplaySelectionRange(CharPosToPos(inStartPos), CharPosToPos(inEndPos));
}


// ---------------------------------------------------------------------------
//	€ SyncContentsWithMemory
// ---------------------------------------------------------------------------

void
CTxtDataSubView::SyncContentsWithMemory(SInt32 inStartPos, 
										SInt32 inEndPos, 
										SInt32 inBytesCount, 
										SInt32 inLineOffset)
{
	SInt32 startOffset = (inLineOffset - 1) * kRzilHexPerLine + PosToCharPos(inStartPos);
	SInt32 endOffset = (inLineOffset - 1) * kRzilHexPerLine + PosToCharPos(inEndPos);

	WEReference we = mEditorWindow->GetInMemoryWasteRef();
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


// ---------------------------------------------------------------------------
//	€ SyncImageWithSibling
// ---------------------------------------------------------------------------

void
CTxtDataSubView::SyncImageWithSibling(SInt32 inHorizDelta,
									  SInt32 inVertDelta,
									  Boolean inRefresh)
{
	mIsSynchronizing = true;
}





PP_End_Namespace_PowerPlant
