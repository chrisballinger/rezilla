// ===========================================================================
// CDualDataView.cp					
// 
//                       Created: 2004-06-16 20:13:56
//             Last modification: 2005-06-15 17:58:34
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2004, 2005
// All rights reserved.
// ===========================================================================


#include "CDualDataView.h"
#include "CHexDataSubView.h"
#include "CHexEditorActions.h"
#include "CHexEditorDoc.h"
#include "CRangeEditText.h"
#include "CRezObj.h"
#include "CRezillaApp.h"
#include "CRezillaPrefs.h"
#include "CRezClipboard.h"
#include "CTxtDataSubView.h"
#include "CWasteEditView.h"
#include "CSingleScrollBar.h"
#include "RezillaConstants.h"
#include "UCodeTranslator.h"
#include "UMessageDialogs.h"

#include <LScrollBar.h>
#include <LStaticText.h>
#include <LIconPane.h>
#include <LTextGroupBox.h>
#include <LUndoer.h>
#include <UExtractFromAEDesc.h>
#include <UAppleEventsMgr.h>
#include <UCursor.h>

#include <AppleHelp.h>


// ---------------------------------------------------------------------------
//		¥ CDualDataView												[public]
// ---------------------------------------------------------------------------

CDualDataView::CDualDataView(
							 LCommander * inSuper,
							 const SPaneInfo&	inPaneInfo,
							 const SViewInfo&	inViewInfo,
							 const DualGeometry& inGeometry,
							 Boolean			inPrimary,
							 ResIDT				inTextTraitsID,
							 ConstStringPtr		inTitle)
: LTextGroupBox(inPaneInfo, inViewInfo, inPrimary, inTextTraitsID, inTitle),
  LCommander(inSuper)
{
	SetGeometry(inGeometry);
	
	Initialize();
}


// ---------------------------------------------------------------------------
//		¥ CDualDataView												[public]
// ---------------------------------------------------------------------------

CDualDataView::CDualDataView(
			       LStream *inStream )
		: LTextGroupBox(inStream)
{
	Initialize();
}


// ---------------------------------------------------------------------------
//		¥ ~CDualDataView											[public]
// ---------------------------------------------------------------------------

CDualDataView::~CDualDataView()
{
	if ( mInMemoryWE != nil ) {
		WEDispose(mInMemoryWE);
		mInMemoryWE = nil;
	}
	// Remove the view from the list of listeners to the prefs object
	CRezillaApp::sPrefs->RemoveListener(this);
}


// ---------------------------------------------------------------------------
//		¥ CDualDataView												[public]
// ---------------------------------------------------------------------------

void
CDualDataView::GetGeometry(DualGeometry& outGeometry) const
{
	BlockMoveData(&mGeometry, &outGeometry, sizeof(DualGeometry));
}


// ---------------------------------------------------------------------------
//		¥ CDualDataView												[public]
// ---------------------------------------------------------------------------

void
CDualDataView::SetGeometry(const DualGeometry& inGeometry)
{
	BlockMoveData(&inGeometry, &mGeometry, sizeof(DualGeometry));
}


// ---------------------------------------------------------------------------
//		¥ Initialize											[protected]
// ---------------------------------------------------------------------------

void
CDualDataView::Initialize()
{	
	OSErr 		error;
	Rect		theRect;
	LongRect	theLongRect;

	mCurrFirstLine = 1;
	mCurrentSubView = hex_nopane;
	mSelectingAll = false;

	// Create the Waste object containing the resource code
	UInt32  initFlags = weDoInhibitRecal + weDoInhibitRedraw;

	// The WE instance is created in the window's frame. It does not matter 
	// since it will never be displayed directly. 
	CalcPortFrameRect(theRect);
	WERectToLongRect( &theRect, &theLongRect) ;
	error = WENew( &theLongRect, &theLongRect, initFlags , &mInMemoryWE);
}


// ---------------------------------------------------------------------------
//		¥ FinishCreateSelf										[protected]
// ---------------------------------------------------------------------------

void
CDualDataView::FinishCreateSelf()
{	
}


// ---------------------------------------------------------------------------
//		¥ InstallSubViews											[public]
// ---------------------------------------------------------------------------

void
CDualDataView::InstallSubViews(CHexDataSubView * inHexDataWE, 
								CTxtDataSubView * inTxtDataWE, 
								CSingleScrollBar * inScroller,
								Boolean inReadOnly)
{
	mHexView = inHexDataWE;
	mTxtView = inTxtDataWE;
	mScroller = inScroller;
	
	mHexView->SetOwnerDualView(this);
	mTxtView->SetOwnerDualView(this);
	
// 	mHexView->SetSuperCommander(this);
// 	mTxtView->SetSuperCommander(this);
	
	mHexView->SetSiblingView(mTxtView);
	mTxtView->SetSiblingView(mHexView);

	mHexView->SetReadOnly(inReadOnly);
	mTxtView->SetReadOnly(inReadOnly);

	SetDirty(false);

	DeclareListeners();
}
 

// ---------------------------------------------------------------------------
//		¥ DeclareListeners										[protected]
// ---------------------------------------------------------------------------

void
CDualDataView::DeclareListeners()
{
	// The view must listen to the scroller's message
	mScroller->AddListener(this);
	// Make the view a listener to the prefs object
	CRezillaApp::sPrefs->AddListener(this);
}


// ---------------------------------------------------------------------------
//		¥ ListenToMessage				[public]
// ---------------------------------------------------------------------------

void
CDualDataView::ListenToMessage( MessageT inMessage, void *ioParam ) 
{	
#pragma unused(ioParam)
	
	switch (inMessage) {
		
		case msg_HexScroller:
			mCurrFirstLine = mScroller->GetValue();
			InstallContentsFromLine(mCurrFirstLine);
			break;

		case msg_StylePrefsChanged: {
			TextTraitsRecord theTraits = CRezillaPrefs::GetStyleElement( CRezillaPrefs::prefsType_Curr );
			ResizeDataPanes();
			UpdatePaneCounts();
			mHexView->ApplyStyleValues(theTraits.size, theTraits.fontNumber);
			mTxtView->ApplyStyleValues(theTraits.size, theTraits.fontNumber);
			mCurrFirstLine = 1;
			InstallContentsFromLine(mCurrFirstLine);
			mScroller->SetValue(0);
			SetMaxScrollerValue();				
			break;
		}
	}
}


// ---------------------------------------------------------------------------
//	¥ ObeyCommand							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CDualDataView::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;
	SInt32		theStartPos, theEndPos;

	if ( mInMemoryWE == nil )
		return cmdHandled;

	switch (inCommand) {

		case cmd_Copy: 
		case cmd_Cut: {
// 			PostAction( new CHexEditorCutAction(InMemoryWasteRef, this, this));
			Handle txtData = nil;
			SInt32 trueStartPos, trueEndPos;
			UInt16 thePeriod;
			WEReference subPaneWERef;
			
			if (mSelectingAll) {
				// If selectAll has been previously invoked
				trueStartPos = 0;
				trueEndPos = ::WEGetTextLength(mInMemoryWE);
				mCurrFirstLine = 1;
				
				// Put deleted text on clipboard
				txtData = ::NewHandle(trueEndPos - trueStartPos);
				WEStreamRange(trueStartPos, trueEndPos, kTypeText, 0, txtData, mInMemoryWE);
				
				switch (mCurrentSubView) {
					case hex_hexpane:
					if (txtData != nil) {
						StByteToHexTranslator hextranslator(txtData);
						hextranslator.Convert();
						UScrap::SetData(ResType_Text, hextranslator.GetOutHandle());
					}
					break;
					
					case hex_txtpane:
					if (txtData != nil) {
						StByteToTextTranslator txttranslator(txtData);
						txttranslator.Convert();
						UScrap::SetData(ResType_Text, txttranslator.GetOutHandle());
					}
					break;
				}
								
			} else {
				// Selection has been made only in the visible part of the resource
			    switch (mCurrentSubView) {
				    case hex_hexpane:
				    thePeriod = 3;
				    mHexView->GetSelectionRange(theStartPos, theEndPos);
				    trueStartPos = mHexView->PosToHexPos(theStartPos);
				    trueEndPos = mHexView->PosToHexPos(theEndPos);
				    subPaneWERef = mHexView->GetWasteRef();
				    break;
				    
				    case hex_txtpane:
				    thePeriod = 2;
				    mTxtView->GetSelectionRange(theStartPos, theEndPos);
				    trueStartPos = mTxtView->PosToCharPos(theStartPos);
				    trueEndPos = mTxtView->PosToCharPos(theEndPos);
				    subPaneWERef = mTxtView->GetWasteRef();
				    break;
			    }
			    
			    // Put deleted text on clipboard
			    txtData = ::NewHandle(theEndPos - theStartPos);
			    WEStreamRange(theStartPos, theEndPos, kTypeText, 0, txtData, subPaneWERef) ;
			    StStripPeriodicalTranslator blankstripper(txtData, thePeriod);
			    blankstripper.FilterOutPeriodical();
			    UScrap::SetData(ResType_Text, blankstripper.GetOutHandle());
			    
			    // Add offset from the start of file
			    SInt32 delta = (mCurrFirstLine - 1) * mBytesPerLine;
			    trueStartPos += delta;
			    trueEndPos += delta;
			}
			
			if (inCommand == cmd_Cut) {
				// Delete the text in the in-memory Waste struct
				WESetSelection(trueStartPos, trueEndPos, mInMemoryWE);
				WEDelete(mInMemoryWE);
				
				InstallContentsFromLine(mCurrFirstLine);
				SetMaxScrollerValue();
				
				SetDirty(true);
				mSelectingAll = false;
			} 
			
			if (txtData != nil) {
				::DisposeHandle(txtData);
			} 
			break;
		}

		case cmd_Clear: {
// 			PostAction( new CHexEditorCutAction(InMemoryWasteRef, this, mHexView));
			
			if (mSelectingAll) {
				// If selectAll has been previously invoked
				theStartPos = 0;
				theEndPos = ::WEGetTextLength(mInMemoryWE);
				mCurrFirstLine = 1;
				mSelectingAll = false;
			} else {
				switch (mCurrentSubView) {
					case hex_hexpane:
					mHexView->GetSelectionRange(theStartPos, theEndPos);
					theStartPos = mHexView->PosToHexPos(theStartPos);
					theEndPos = mHexView->PosToHexPos(theEndPos);
					break;
					
					case hex_txtpane:
					mTxtView->GetSelectionRange(theStartPos, theEndPos);
					theStartPos = mTxtView->PosToCharPos(theStartPos);
					theEndPos = mTxtView->PosToCharPos(theEndPos);
					break;
				}
				
				// Add offset from the start of file
				SInt32 delta = (mCurrFirstLine - 1) * mBytesPerLine;
				theStartPos += delta;
				theEndPos += delta;
			}
			
			// Delete the text in the in-memory Waste struct
			WESetSelection(theStartPos, theEndPos, mInMemoryWE);
			WEDelete(mInMemoryWE);
			InstallContentsFromLine(mCurrFirstLine);
			SetMaxScrollerValue();
			
			SetDirty(true);
			break;
		}

		case cmd_Paste: {
// 			PostAction( new CHexEditorPasteAction(mInMemoryWE, this, this) );
			StHandleBlock	scrapDataH(Size_Zero);
			SInt32 dataSize = UScrap::GetData(ResType_Text, scrapDataH);
			if (dataSize == 0) {
				return cmdHandled;
			} 
			if (mCurrentSubView == hex_hexpane) {
				// Check if scrap contains valid hex data
				if( ! CRezClipboard::ContentsIsValidHex()) {
					UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("InvalidHexDataInScrap"), PPob_SimpleMessage);
					return cmdHandled;
				}
				// If so, convert it to byte code
				StHexToByteTranslator translator(scrapDataH);
				translator.Convert();
				dataSize = translator.GetOutSize();
				scrapDataH = translator.GetOutHandle();
			} 
						
			if (mSelectingAll) {
				// If selectAll has been previously invoked
				theStartPos = 0;
				theEndPos = ::WEGetTextLength(mInMemoryWE);
				mCurrFirstLine = 1;
								
				mSelectingAll = false;
			} else {
				switch (mCurrentSubView) {
					case hex_hexpane:
					// Get the selection range
					mHexView->GetSelectionRange(theStartPos, theEndPos);
					theStartPos = mHexView->PosToHexPos(theStartPos);
					theEndPos = mHexView->PosToHexPos(theEndPos);
					break;
					
					case hex_txtpane:
					// Get the selection range
					mTxtView->GetSelectionRange(theStartPos, theEndPos);
					theStartPos = mTxtView->PosToCharPos(theStartPos);
					theEndPos = mTxtView->PosToCharPos(theEndPos);
					break;
				}
				
				SInt32 delta = (mCurrFirstLine - 1) * mBytesPerLine;
				theStartPos += delta;
				theEndPos += delta;
			}
			
			// Set the selection range in memory
			WESetSelection(theStartPos, theEndPos, mInMemoryWE);
			
			StHandleLocker lockit(scrapDataH);
			WEPut( kCurrentSelection, kCurrentSelection, *scrapDataH, dataSize, kTextEncodingMultiRun,
						kNilOptions, 0, nil, nil, mInMemoryWE);
			InstallContentsFromLine(mCurrFirstLine);
			SetMaxScrollerValue();

			SetDirty(true);
			break;
		}

		case cmd_ActionCut:
		case cmd_ActionPaste:
		case cmd_ActionClear: {
			break;
		}
		
		case cmd_ActionTyping:
			InstallContentsFromLine(mCurrFirstLine);
			break;


		default:
			cmdHandled = LCommander::ObeyCommand(inCommand, ioParam);
			break;
	}

	return cmdHandled;
}


// ---------------------------------------------------------------------------
//	¥ InstallBackStoreData										[protected]
// ---------------------------------------------------------------------------

void
CDualDataView::InstallBackStoreData(Handle inHandle)
{
	InstallBackStoreData(*inHandle, ::GetHandleSize(inHandle));
}


// ---------------------------------------------------------------------------
//	¥ InstallBackStoreData										[protected]
// ---------------------------------------------------------------------------
// kTextEncodingUnknown raises an error -9473 (weInvalidTextEncodingErr)

void
CDualDataView::InstallBackStoreData(const void * inPtr, SInt32 inByteCount)
{
	WEPut( 0, 0, inPtr, inByteCount, kTextEncodingMultiRun,
				kNilOptions, 0, nil, nil, mInMemoryWE);
}


// ---------------------------------------------------------------------------
//	¥ InstallHexContents											[protected]
// ---------------------------------------------------------------------------

void
CDualDataView::InstallHexContents(Handle inHandle)
{
	mHexView->InsertContents(inHandle);
}


// ---------------------------------------------------------------------------
//	¥ InstallHexContents											[protected]
// ---------------------------------------------------------------------------

void
CDualDataView::InstallHexContents(const void * inPtr, SInt32 inByteCount)
{
	mHexView->InsertContents(inPtr, inByteCount);
}


// ---------------------------------------------------------------------------
//	¥ InstallTextContents											[protected]
// ---------------------------------------------------------------------------

void
CDualDataView::InstallTextContents(Handle inHandle)
{
	mTxtView->InsertContents(inHandle);
}


// ---------------------------------------------------------------------------
//	¥ InstallTextContents											[protected]
// ---------------------------------------------------------------------------

void
CDualDataView::InstallTextContents(const void * inPtr, SInt32 inByteCount)
{
	mTxtView->InsertContents(inPtr, inByteCount);
}


// ---------------------------------------------------------------------------
//	¥ InstallContentsFromLine											[public]
// ---------------------------------------------------------------------------

SInt32
CDualDataView::InstallContentsFromLine(SInt32 inFromLine)
{
	SInt32 remainingChars, charOffset;
	SInt32 maxFirstLine = HexLineCount() - mLinesPerPane + 1;
	SInt32 bytesPerPaneCount = GetPaneCount(count_BytesPerPane);

	if (maxFirstLine <= 0) {
		maxFirstLine = 1;
	} 
	
	if (inFromLine > maxFirstLine) {
		inFromLine = maxFirstLine;
	} 
	
	Handle theHandle = WEGetText(mInMemoryWE);
	charOffset = (inFromLine - 1) * mBytesPerLine;
	remainingChars = WEGetTextLength(mInMemoryWE) - charOffset;

	if (remainingChars > bytesPerPaneCount) {
		remainingChars = bytesPerPaneCount;
	} 
	
	InstallHexContents( (*theHandle) + charOffset, remainingChars);
	InstallTextContents( (*theHandle) + charOffset, remainingChars);
	
	// Notify to the dual view's listeners
	BroadcastMessage(msg_DualViewEdited, this);

	return charOffset ;
}


// ---------------------------------------------------------------------------
//	¥ GetAbsoluteRange											[protected]
// ---------------------------------------------------------------------------

void
CDualDataView::GetAbsoluteRange(SInt32 & outStart, SInt32 & outEnd)
{
	mHexView->GetSelectionRange(outStart, outEnd);
	SInt32 delta = (mCurrFirstLine - 1) * mBytesPerLine;
	outStart = mHexView->PosToHexPos(outStart) + delta;
	outEnd = mHexView->PosToHexPos(outEnd) + delta;
}


// ---------------------------------------------------------------------------
//  ¥ HexLineCount														[public]
// ---------------------------------------------------------------------------

SInt32
CDualDataView::HexLineCount() 
{
	SInt32 byteCount = WEGetTextLength(mInMemoryWE);
	SInt32 lineCount = 0;
	if (byteCount) {
		lineCount = byteCount / mBytesPerLine;
		lineCount += (byteCount % mBytesPerLine == 0) ? 0:1 ;
	} 
	return lineCount;
}


// ---------------------------------------------------------------------------
//	¥ CountLines								[public]
// ---------------------------------------------------------------------------

SInt32
CDualDataView::CountLines()
{
	return mHexView->CountLines();
}


// ---------------------------------------------------------------------------
//	¥ GetCurrLines											[public]
// ---------------------------------------------------------------------------

void
CDualDataView::GetCurrLines(SInt32 & outFirstLine, SInt32 & outLastLine)
{
	mHexView->GetCurrLines(outFirstLine, outLastLine);
}


// ---------------------------------------------------------------------------
//	¥ GetCurrHexPos											[public]
// ---------------------------------------------------------------------------

void
CDualDataView::GetCurrHexPos(SInt32 & outHexSelStart, SInt32 & outHexSelEnd)
{
	mHexView->GetCurrHexPos(outHexSelStart, outHexSelEnd);
}


// ---------------------------------------------------------------------------
//	¥ SetMaxScrollerValue										[protected]
// ---------------------------------------------------------------------------

void
CDualDataView::SetMaxScrollerValue()
{
	SInt32 theLineCount = HexLineCount() - mLinesPerPane + 1;
	
	if (theLineCount < 0) {
		theLineCount = 0;
	} 
	mScroller->SetMaxValue(theLineCount);
}


// ---------------------------------------------------------------------------
//	¥ DisplayBothSelections											[protected]
// ---------------------------------------------------------------------------

void
CDualDataView::DisplayBothSelections(SInt32 inStart, SInt32 inEnd)
{
	SInt32 startOffset = (mCurrFirstLine-1) * mBytesPerLine;
	SInt32 endOffset = startOffset + GetPaneCount(count_BytesPerPane);
	SInt32 oldFirstLine = mCurrFirstLine;

	if ( inStart < startOffset || inStart > endOffset ) {
		// inStart is out of the displayed area
		mCurrFirstLine = PosToLine(inStart);
	} else if ( inEnd > endOffset ) {
		// inEnd is below the frame. Move the first displayed line up as much as 
		// possible (inStart must not go above the frame) 
		SInt32 linesBefore = (inStart - startOffset)/mBytesPerLine;
		SInt32 linesAfter = (inEnd - endOffset)/mBytesPerLine + 1;
		mCurrFirstLine += (linesAfter - linesBefore) ? linesBefore : linesAfter ;
	}
	// Don't go too far
	SInt32 maxFirstLine = HexLineCount() - mLinesPerPane + 1;
	if (maxFirstLine <= 0) {
		maxFirstLine = 1;
	} 
	if (mCurrFirstLine > maxFirstLine) {
		mCurrFirstLine = maxFirstLine;
	} 
	if (mCurrFirstLine != oldFirstLine) {
		InstallContentsFromLine(mCurrFirstLine);
		mScroller->SetValue(mCurrFirstLine);
	} 

	// Calc the relative positions
	SInt32 delta = (mCurrFirstLine - 1) * mBytesPerLine;
	SInt32 relStartPos = inStart - delta;
	SInt32 relEndPos = inEnd - delta;

	// Hilite the selections
	mHexView->DisplaySelectionRange(mHexView->HexPosToPos(relStartPos), 
								  mHexView->HexPosToPos(relEndPos));
	mTxtView->DisplaySelectionRange(mTxtView->CharPosToPos(relStartPos), 
								  mTxtView->CharPosToPos(relEndPos));
}


// ---------------------------------------------------------------------------
//	¥ PosToLine											[protected, virtual]
// ---------------------------------------------------------------------------

SInt32
CDualDataView::PosToLine(SInt32 inPos)
{
	SInt32 theRest = inPos % mBytesPerLine;
	
	return (((inPos - theRest) / mBytesPerLine) + 1);
}


// ---------------------------------------------------------------------------
//	¥ IsDirty														[public]
// ---------------------------------------------------------------------------

Boolean
CDualDataView::IsDirty()
{
	return (mHexView->IsDirty() || mTxtView->IsDirty());
}


// ---------------------------------------------------------------------------
//  SetDirty														[public]
// ---------------------------------------------------------------------------

void
CDualDataView::SetDirty(Boolean inDirty) 
{
	mHexView->SetDirty(inDirty);
	mTxtView->SetDirty(inDirty);
}


// ---------------------------------------------------------------------------
//	¥ AdaptToNewSurroundings
// ---------------------------------------------------------------------------

void
CDualDataView::AdaptToNewSurroundings()
{
	CalcRevealedRect();
	ResizeDataPanes();
	UpdatePaneCounts();
	mCurrFirstLine = 1;
	InstallContentsFromLine(mCurrFirstLine);
	mScroller->SetValue(0);
	SetMaxScrollerValue();				
}


// ---------------------------------------------------------------------------
//	¥ ResizeDataPanes												[public]
// ---------------------------------------------------------------------------

void
CDualDataView::ResizeDataPanes()
{
	SInt16			hexWidth, hexHeight, txtWidth, txtHeight;
	SInt32			hexLeft, txtLeft;
	
	CalcPanesPositions(hexLeft, hexWidth, hexHeight, txtLeft, txtWidth, txtHeight);
	
	// LHS pane (hexadecimal representation)
	mHexView->ResizeFrameTo(hexWidth, hexHeight, false);
	
	// RHS pane (readable representation)	
	mTxtView->ResizeFrameTo(txtWidth, txtHeight, false);
	mTxtView->PlaceInSuperImageAt(mGeometry.hinst + hexWidth + mGeometry.hsep, mGeometry.vinst, false);
}


// ---------------------------------------------------------------------------
//	¥ CalcPanesPositions										[private]
// ---------------------------------------------------------------------------
// 	Formulas:
// 	Width
// 	If nc is the number of chars per line:
// 		fract = (TGBXw - extraW) / (CHARw x 5)
// 		nc = E(fract)
// 	==>  
// 		HDSVw = nc x CHARw x 3
// 		TDSVw = nc x CHARw x 2
// 
// 	Height:
// 	If nl is the number of lines in each panel:
// 		fract = (TGBXh - extraH) / CHARh
// 		nl = E(fract)
// 	==>  
// 		HDSVh = TDSVh = nl x CHARh
// 
// 	We also have the following proportions:	
// 		HDSVw = 3/5 (TGBXw - extraW)
// 		TDSVw = 2/5 (TGBXw - extraW)

void
CDualDataView::CalcPanesPositions(SInt32 & hexLeft, SInt16 & hexWidth, SInt16 & hexHeight, 
								  SInt32 & txtLeft, SInt16 & txtWidth, SInt16 & txtHeight)
{
	SInt16			numChar, numLine, extraWidth, extraHeight;
	SDimension16	frame;
	
	GetFrameSize(frame);
	extraWidth = mGeometry.hinst * 3 + mGeometry.hsep + mGeometry.scrlw;
	extraHeight = mGeometry.vinst * 2;

	numChar = (frame.width - extraWidth) / (CRezillaApp::sBasics.charWidth * 5);
	numLine = (frame.height - extraHeight) / CRezillaApp::sBasics.charHeight;

	// Hex pane
	hexWidth = numChar * CRezillaApp::sBasics.charWidth * 3;
	hexHeight = numLine * CRezillaApp::sBasics.charHeight;
	hexLeft = mGeometry.hinst;
	
	// Txt pane (readable representation)
	txtWidth = numChar * CRezillaApp::sBasics.charWidth * 2;
	txtHeight = hexHeight;
	txtLeft = hexLeft + hexWidth + mGeometry.hsep;
}


// ---------------------------------------------------------------------------
//	¥ GetPaneCount													[public]
// ---------------------------------------------------------------------------
// Return various capacities.

SInt32
CDualDataView::GetPaneCount(SInt16 whichValue)
{
	SInt32			result = 0;
	
	switch (whichValue) {
		case count_LinesPerPane:
		result = mLinesPerPane;
		break;
		
		case count_BytesPerLine:
		result = mBytesPerLine;
		break;
		
		case count_BytesPerPane:
		result = mLinesPerPane * mBytesPerLine;
		break;
		
	}
	return result;
}


// ---------------------------------------------------------------------------
//	¥ UpdatePaneCounts												[public]
// ---------------------------------------------------------------------------
// 	mBytesPerLine is a count of virtual bytes which have to be multiplied
// 	by 3 (two hex digits + space) in hex representation or by 2 in text
// 	representation (one char + space)

void
CDualDataView::UpdatePaneCounts()
{
	SDimension16	theSize;
	
	mHexView->GetFrameSize(theSize);
	mLinesPerPane = theSize.height / CRezillaApp::sBasics.charHeight;
	mBytesPerLine = theSize.width / (CRezillaApp::sBasics.charWidth * 3);
}

