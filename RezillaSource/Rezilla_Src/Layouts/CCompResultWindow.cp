// ===========================================================================
// CHexEditorWindow.cp					
// 
//                       Created: 2004-03-02 14:18:16
//             Last modification: 2004-06-08 18:24:07
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CCompResultWindow.h"
#include "CRezObj.h"
#include "CRezMap.h"
#include "CRezillaApp.h"
#include "CRezillaPrefs.h"
#include "CRezCompare.h"
#include "CRezClipboard.h"
#include "CWindowMenu.h"
#include "CBiDataWE.h"
#include "CSingleScrollBar.h"
#include "CBroadcasterTableView.h"
#include "RezillaConstants.h"
#include "UCodeTranslator.h"
#include "UMiscUtils.h"
#include "UMessageDialogs.h"

#include <LRadioGroupView.h>
#include <LScrollBar.h>
#include <LStaticText.h>
#include <LTextGroupBox.h>
#include <LUndoer.h>
#include <LTableMonoGeometry.h>
#include <LTableSingleSelector.h>
#include <LTableArrayStorage.h>

// Global
extern CWindowMenu * gWindowMenu;


// ---------------------------------------------------------------------------
//		¥ CCompResultWindow				[public]
// ---------------------------------------------------------------------------

CCompResultWindow::CCompResultWindow()
{
}


// ---------------------------------------------------------------------------
//		¥ CCompResultWindow				[public]
// ---------------------------------------------------------------------------

CCompResultWindow::CCompResultWindow(
	const SWindowInfo &inWindowInfo )
		: LWindow( inWindowInfo )
{
}


// ---------------------------------------------------------------------------
//		¥ CCompResultWindow				[public]
// ---------------------------------------------------------------------------

CCompResultWindow::CCompResultWindow(
	ResIDT		inWINDid,
	UInt32		inAttributes,
	LCommander	*inSuperCommander )
		: LWindow( inWINDid, inAttributes, inSuperCommander )
{
}


// ---------------------------------------------------------------------------
//		¥ CCompResultWindow				[public]
// ---------------------------------------------------------------------------

CCompResultWindow::CCompResultWindow(
			       LStream *inStream )
		: LWindow( inStream )
{
}


// ---------------------------------------------------------------------------
//		¥ ~CCompResultWindow				[public]
// ---------------------------------------------------------------------------

CCompResultWindow::~CCompResultWindow()
{
	// Remove self from the window menu.
	gWindowMenu->RemoveWindow(this);
	
	// Remove the window from the list of listeners to the prefs object
	CRezillaApp::sPrefs->RemoveListener(this);
}


// ---------------------------------------------------------------------------
//		¥ FinishCreateSelf				[protected]
// ---------------------------------------------------------------------------

void
CCompResultWindow::FinishCreateSelf()
{	
	LStaticText * theStaticText;
	LStr255		optionString("\p");

	mDisplayDataFormat = CRezillaPrefs::GetPrefValue(kPref_compare_dataDisplayAs);
	mActiveTable = compare_undefinedTbl;
	
	// The RezCompare owner was passed in the inSuperCommander argument
	mRezCompare = dynamic_cast<CRezCompare *>(GetSuperCommander());
	// Now set the SuperCommander to be CRezillaApp itself
	SetSuperCommander(mRezCompare->GetSuperCommander());
	
	// Build the hex editing elements
	mOldRezDataWE = dynamic_cast<CBiDataWE *> (FindPaneByID( item_CompResultOldHex ));
	ThrowIfNil_(mOldRezDataWE);
			
	mOldRezDataWE->SetCompareWindow(this);

	mNewRezDataWE = dynamic_cast<CBiDataWE *> (FindPaneByID( item_CompResultNewHex ));
	ThrowIfNil_(mNewRezDataWE);
	
	mNewRezDataWE->SetCompareWindow(this);

	// Use the style specified in the preferences an calculate the capacities of the editing panes
	TextTraitsRecord theTraits = CRezillaPrefs::GetStyleElement( CRezillaPrefs::prefsType_Curr );
	ResizeDataPanes();
	UpdatePaneCounts();
	mOldRezDataWE->ApplyStyleValues( theTraits.size, theTraits.fontNumber);
	mNewRezDataWE->ApplyStyleValues( theTraits.size, theTraits.fontNumber);
	
	// Cache a pointer to the scrollbar separating the data panes
	mScroller = dynamic_cast<CSingleScrollBar *> (FindPaneByID( item_CompResultScroller ));
	ThrowIfNil_(mScroller);
	mScroller->SetLinesPerPage(GetPaneCount(count_LinesPerPane) - 1);
	
	// Build the table elements
		// Left table
	mOnlyOldTable = dynamic_cast<CBroadcasterTableView *> (FindPaneByID( item_CompResultOnlyOldTbl ));
	ThrowIfNil_(mOnlyOldTable);
	// Set Geometry and Selector TableView members.
	mOnlyOldTable->SetTableGeometry(new LTableMonoGeometry(mOnlyOldTable, kCompTableWidth, kCompTableHeight));
	mOnlyOldTable->SetTableSelector(new LTableSingleSelector(mOnlyOldTable));
	mOnlyOldTable->SetTableStorage(new LTableArrayStorage(mOnlyOldTable, sizeof(Str255)));
	mOnlyOldTable->InsertCols(1, 0);

		// Center table
	mDifferTable = dynamic_cast<CBroadcasterTableView *> (FindPaneByID( item_CompResultDifferingTbl ));
	ThrowIfNil_(mDifferTable);
	// Set Geometry and Selector TableView members
	mDifferTable->SetTableGeometry(new LTableMonoGeometry(mDifferTable, kCompTableWidth, kCompTableHeight));
	mDifferTable->SetTableSelector(new LTableSingleSelector(mDifferTable));
	mDifferTable->SetTableStorage(new LTableArrayStorage(mDifferTable, sizeof(Str255)));
	mDifferTable->InsertCols(1, 0);
	mDifferTable->SetFaceStyle(italic);

		// Right table
	mOnlyNewTable = dynamic_cast<CBroadcasterTableView *> (FindPaneByID( item_CompResultOnlyNewTbl ));
	ThrowIfNil_(mOnlyNewTable);
	// Set Geometry and Selector TableView members
	mOnlyNewTable->SetTableGeometry(new LTableMonoGeometry(mOnlyNewTable, kCompTableWidth, kCompTableHeight));
	mOnlyNewTable->SetTableSelector(new LTableSingleSelector(mOnlyNewTable));
	mOnlyNewTable->SetTableStorage(new LTableArrayStorage(mOnlyNewTable, sizeof(Str255)));
	mOnlyNewTable->InsertCols(1, 0);
	
	// Static text fields
	theStaticText = dynamic_cast<LStaticText *>(FindPaneByID( item_CompResultOldStatic ));
	ThrowIfNil_(theStaticText);
	theStaticText->SetDescriptor(mRezCompare->GetOldPath());

	theStaticText = dynamic_cast<LStaticText *>(FindPaneByID( item_CompResultNewStatic ));
	ThrowIfNil_(theStaticText);
	theStaticText->SetDescriptor(mRezCompare->GetNewPath());
	
	theStaticText = dynamic_cast<LStaticText *>(FindPaneByID( item_CompResultIgnStatic ));
	ThrowIfNil_(theStaticText);
	if (CRezCompare::sIgnoreNames + CRezCompare::sIgnoreAttrs + CRezCompare::sIgnoreData == 0) {
		optionString.Assign("\pno options");
	} else {
		SInt8 count = 0;
		optionString.Assign("\pignoring ");
		if (CRezCompare::sIgnoreNames) {
			optionString += "\pname";
			count++;
		}		
		if (CRezCompare::sIgnoreAttrs) {
			optionString += count ? "\p, " : "\p ";
			optionString += "\pattribute";
			count++;
		}		
		if (CRezCompare::sIgnoreData) {
			optionString += count ? "\p, " : "\p ";
			optionString += "\pdata";
		}		
		optionString += "\p differences";
	}	
	
	theStaticText->SetDescriptor(optionString);
	
	LRadioGroupView * theRGV = dynamic_cast<LRadioGroupView *>(this->FindPaneByID( item_CompResultShowAsRgbx ));
	ThrowIfNil_(theRGV);
	theRGV->SetCurrentRadioID( CRezillaPrefs::GetPrefValue( kPref_compare_dataDisplayAs ) + item_CompResultShowAsRgbx );
	
	// Link the broadcasters.
    UReanimator::LinkListenerToControls( this, this, rRidL_RezCompWindow );
	
	// Let the window listen to the tables and to the scroller
	mOnlyOldTable->AddListener(this);	
	mDifferTable->AddListener(this);	
	mOnlyNewTable->AddListener(this);	
	mScroller->AddListener(this);	

	// Make the window a listener to the prefs object
	CRezillaApp::sPrefs->AddListener(this);
	
	// Attach an LUndoer to each of the subpanes
	mOldRezDataWE->AddAttachment( new LUndoer );
	mNewRezDataWE->AddAttachment( new LUndoer );

	// Name the window
	NameNewCompWindow();

	// Add self to the windows menu
	gWindowMenu->InsertWindow(this);

	// Make the window visible
	Show();
}


// ---------------------------------------------------------------------------
//		¥ ListenToMessage				[public]
// ---------------------------------------------------------------------------

void
CCompResultWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{
#pragma unused(ioParam)
	CRezTypId * theTypid;
	STableCell theCell;
	
	switch (inMessage) {
		
		case msg_Close:
		Hide();
		break;
		
		case msg_CompResultScroller: 
		InsertContentsFromLine(mScroller->GetValue() + 1);
		break;
		
		case msg_CompResultOnlyOldTbl: {
			mActiveTable = compare_onlyinOldTbl;
			mOnlyNewTable->UnselectAllCells();
			mDifferTable->UnselectAllCells();
			
			theCell = mOnlyOldTable->GetFirstSelectedCell();		
			mRezCompare->GetOnlyInOldList()->FetchItemAt( theCell.row, theTypid);
			
			mRezCompare->GetOldMap()->GetWithID(theTypid->mType, theTypid->mID, mOldData, false);
			if (mOldData == nil) {
				return;
			}
			
			EraseHexPanes();
			InsertContentsFromLine(1);
			SetMaxScrollerValue();
			break;
		}
		
		case msg_CompResultOnlyNewTbl: {
			mActiveTable = compare_onlyinNewTbl;
			mOnlyOldTable->UnselectAllCells();
			mDifferTable->UnselectAllCells();
			
			theCell = mOnlyNewTable->GetFirstSelectedCell();		
			mRezCompare->GetOnlyInNewList()->FetchItemAt( theCell.row, theTypid);
			
			mRezCompare->GetNewMap()->GetWithID(theTypid->mType, theTypid->mID, mNewData, false);
			if (mNewData == nil) {
				return;
			} 
			
			EraseHexPanes();
			InsertContentsFromLine(1);
			SetMaxScrollerValue();
			break;
		}
		
		case msg_CompResultDifferingTbl: {
			mActiveTable = compare_differTbl;
			mOnlyOldTable->UnselectAllCells();
			mOnlyNewTable->UnselectAllCells();
			
			theCell = mDifferTable->GetFirstSelectedCell();		
			mRezCompare->GetDifferingList()->FetchItemAt( theCell.row, theTypid);
			
			mRezCompare->GetOldMap()->GetWithID(theTypid->mType, theTypid->mID, mOldData, false);
			mRezCompare->GetNewMap()->GetWithID(theTypid->mType, theTypid->mID, mNewData, false);
			if (mOldData == nil || mNewData == nil) {
				return;
			} 
			
			EraseHexPanes();
			InsertContentsFromLine(1);			
			SetMaxScrollerValue();
			break;
		}
		
		case msg_CompResultHexRadio: {
			LStdRadioButton * theRadio = dynamic_cast<LStdRadioButton *> (FindPaneByID( item_CompResultHexRadio ));
			ThrowIfNil_(theRadio);
			mDisplayDataFormat = theRadio->GetValue() ?  compare_displayAsHex : compare_displayAsTxt ;
			if (mActiveTable == compare_onlyinOldTbl) {
				ListenToMessage(msg_CompResultOnlyOldTbl, ioParam);
			} else if (mActiveTable == compare_onlyinNewTbl) {
				ListenToMessage(msg_CompResultOnlyNewTbl, ioParam);
			} else if (mActiveTable == compare_differTbl) {
				ListenToMessage(msg_CompResultDifferingTbl, ioParam);
			} 
			break;
		}
		
		case msg_StylePrefsChanged: {
			TextTraitsRecord theTraits = CRezillaPrefs::GetStyleElement( CRezillaPrefs::prefsType_Curr );
			ResizeDataPanes();
			UpdatePaneCounts();
			mOldRezDataWE->ApplyStyleValues( theTraits.size, theTraits.fontNumber);
			mNewRezDataWE->ApplyStyleValues( theTraits.size, theTraits.fontNumber);
			InsertContentsFromLine(1);
			mScroller->SetValue(0);
			SetMaxScrollerValue();				
			break;
		}
		
		// 		default:
		// 		GetSuperCommander()->ListenToMessage(inMessage, ioParam);
		// 		break;
		
	}
}


// ---------------------------------------------------------------------------
//	¥ FindCommandStatus
// ---------------------------------------------------------------------------
//	Pass back whether a Command is enabled and/or marked (in a Menu)

void
CCompResultWindow::FindCommandStatus(
	CommandT	inCommand,
	Boolean		&outEnabled,
	Boolean		&outUsesMark,
	UInt16		&outMark,
	Str255		outName)
{
	switch (inCommand) {
		
		case cmd_Save:
		case cmd_SaveAs:
		case cmd_Cut:
		case cmd_Paste:
		case cmd_Clear:
		case cmd_SelectAll: 
		outEnabled = false;
		break;
		
		case cmd_Close:
		case cmd_Copy:
		outEnabled = true;
		break;
		
		default:
		LCommander::FindCommandStatus(inCommand, outEnabled,
									  outUsesMark, outMark, outName);
		break;
	}
}


// ---------------------------------------------------------------------------
//	¥ ObeyCommand							[public, virtual]
// ---------------------------------------------------------------------------
// Cut, Paste and Clear are disabled.

Boolean
CCompResultWindow::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;

// 	CHexEditorDoc * theOwnerDoc = dynamic_cast<CHexEditorDoc *>( GetSuperCommander() );
// 	ThrowIfNil_(theOwnerDoc);
	
	switch (inCommand) {

		case cmd_Cut:
		case cmd_Paste:
		case cmd_Clear:
		break;

		case cmd_Close:
		delete this;
		break;
				
		default:
			cmdHandled = LCommander::ObeyCommand(inCommand, ioParam);
			break;
	}

	return cmdHandled;
}


// ---------------------------------------------------------------------------------
//  ¥ NameNewCompWindow
// ---------------------------------------------------------------------------------

void
CCompResultWindow::NameNewCompWindow()
{
	// Start with the default name ("untitled rez map [1]")
	LStr255		theTitle(STRx_DefaultDocTitles, index_CompWinUntitled);
	// If an existing window has this name, append a count and
	// keep incrementing the count until we find a unique name.
	long	num = 1;
	while (UWindows::FindNamedWindow(theTitle) != nil) {
		theTitle.Assign(STRx_DefaultDocTitles, index_CompWinUntitledX);
		++num;
		theTitle += "\p [";
		theTitle += num;
		theTitle += "\p]";
	}		
	
	// Finally, set window title
	SetDescriptor(theTitle);
}


// ---------------------------------------------------------------------------
//	¥ DoClose
// ---------------------------------------------------------------------------
//	Close the inspector window: hide it but keep it in memory

void
CCompResultWindow::DoClose()
{
	Hide();
}


// ---------------------------------------------------------------------------
//	¥ IsDirty														[public]
// ---------------------------------------------------------------------------

Boolean
CCompResultWindow::IsDirty()
{
/* 	return (mOldRezDataWE->IsDirty() || mNewRezDataWE->IsDirty()); */
    return false;
}


// ---------------------------------------------------------------------------
//	¥ FillTableView														[public]
// ---------------------------------------------------------------------------

void
CCompResultWindow::FillTableView( TArray<CRezTypId *> inList, SInt16 inWhichList)
{
	SInt32 		theCount;
	TableIndexT	theRows, theCols;
	STableCell	cell(0,1);
	Str255		tempString;
	LStr255		thePString;
	TableIndexT	thePos = 0;
	CRezTypId *	theTypId;
	CBroadcasterTableView * theTable;
	
	switch (inWhichList) {
		case CRezCompare::list_OnlyInOld :
		theTable = mOnlyOldTable;
		break;
		
		case CRezCompare::list_OnlyInNew :
		theTable = mOnlyNewTable;
		break;
		
		case CRezCompare::list_Differing :
		theTable = mDifferTable;
		break;
		
	}
	
	theCount = inList.GetCount() ;
	theTable->GetTableSize(theRows, theCols);
	if (theRows < theCount) {
		theTable->InsertRows(theCount-theRows, theRows, nil, 0, Refresh_Yes);
	} else if (theRows > theCount) {
		theTable->RemoveRows(theRows-theCount, theCount+1, Refresh_Yes);
	}
	
	TArrayIterator<CRezTypId*> iterator(inList);	
	
	for (SInt16 i = 1; i <= theCount; ++i) {
		iterator.Next(theTypId);
		thePString = "\p";
		cell.row = i;
		UMiscUtils::OSTypeToPString(theTypId->mType, tempString);
		thePString += tempString;
		::NumToString(theTypId->mID, tempString);
		thePString += "\p ";
		thePString += tempString;
		theTable->SetCellData(cell, thePString, sizeof(Str255));
	}
	
	STableCell	topCell(0,1);
	STableCell	botCell(theCount,1);
	theTable->RefreshCellRange(topCell, botCell);
}


// ---------------------------------------------------------------------------
//	¥ SetMaxScrollerValue										[protected]
// ---------------------------------------------------------------------------

void
CCompResultWindow::SetMaxScrollerValue()
{
	SInt32 theLineDelta = LineCount() - GetPaneCount(count_LinesPerPane) + 1;
	
	if (theLineDelta < 0) {
		theLineDelta = 0;
	} 
	mScroller->SetMaxValue(theLineDelta);
}


// ---------------------------------------------------------------------------
//	¥ LineCount										[protected]
// ---------------------------------------------------------------------------
// Find the max number of lines among the two panes

SInt32
CCompResultWindow::LineCount() 
{
	SInt32 bytesPerLineCount = GetPaneCount(count_BytesPerLine);
	SInt32 oldLineCount = 0;
	SInt32 newLineCount = 0;

	if (mActiveTable != compare_onlyinNewTbl) {
		SInt32 oldByteCount = ::GetHandleSize(mOldData);
		if (oldByteCount) {
			oldLineCount = oldByteCount / bytesPerLineCount;
			oldLineCount += (oldByteCount % bytesPerLineCount == 0) ? 0:1 ;
		} 
	}
	
	if (mActiveTable != compare_onlyinOldTbl) {
		SInt32 newByteCount = ::GetHandleSize(mNewData);
		if (newByteCount) {
			newLineCount = newByteCount / bytesPerLineCount;
			newLineCount += (newByteCount % bytesPerLineCount == 0) ? 0:1 ;
		} 
	}

	if (mActiveTable == compare_onlyinOldTbl) {
		return oldLineCount;
	} else if (mActiveTable == compare_onlyinNewTbl) {
		return newLineCount;
	} else {
		return ((oldLineCount > newLineCount) ? oldLineCount:newLineCount);
	}
}


// ---------------------------------------------------------------------------
//	¥ InsertContentsFromLine										[protected]
// ---------------------------------------------------------------------------
// All the counts in this proc are counts of bytes in the resource data. 
// InsertContents() takes care of converting the bytes to their (hex or char)+space representation.

void
CCompResultWindow::InsertContentsFromLine(SInt32 inFromLine)
{
	SInt32 remainingChars;
	SInt32 charOffset = (inFromLine - 1) * GetPaneCount(count_BytesPerLine);
	SInt32 bytesPerPaneCount = GetPaneCount(count_BytesPerPane);
	
	mOldRezDataWE->SetDataType(mDisplayDataFormat);
	mNewRezDataWE->SetDataType(mDisplayDataFormat);
	
	if (mActiveTable != compare_onlyinNewTbl) {
		// Left pane
		SInt32 oldByteCount = ::GetHandleSize(mOldData);
		remainingChars = oldByteCount - charOffset;
		
		if (remainingChars > bytesPerPaneCount) {
			remainingChars = bytesPerPaneCount;
		} 
		if (remainingChars < 0) {
			remainingChars = 0;
			mOldRezDataWE->InsertContents( (*mOldData), remainingChars);
		} else {
			mOldRezDataWE->InsertContents( (*mOldData) + charOffset, remainingChars);
		}
		
	} 	
	
	if (mActiveTable != compare_onlyinOldTbl) {
		// Right pane
		SInt32 newByteCount = ::GetHandleSize(mNewData);
		remainingChars = newByteCount - charOffset;
		
		if (remainingChars > bytesPerPaneCount) {
			remainingChars = bytesPerPaneCount;
		} 
		if (remainingChars < 0) {
			remainingChars = 0;
			mNewRezDataWE->InsertContents( (*mNewData), remainingChars);
		} else {
			mNewRezDataWE->InsertContents( (*mNewData) + charOffset, remainingChars);
		}
	} 	
}


// ---------------------------------------------------------------------------
//	¥ EraseHexPanes										[protected]
// ---------------------------------------------------------------------------

void
CCompResultWindow::EraseHexPanes()
{
	mOldRezDataWE->DeleteAll();
	mNewRezDataWE->DeleteAll();

	mScroller->SetMaxValue(0);
}


// ---------------------------------------------------------------------------
//	¥ DoSetBounds
// ---------------------------------------------------------------------------

void
CCompResultWindow::DoSetBounds(
	const Rect&		inBounds)
{
	LWindow::DoSetBounds(inBounds);
	ResizeDataPanes();
	UpdatePaneCounts();
	InsertContentsFromLine(1);
	mScroller->SetValue(0);
	SetMaxScrollerValue();				
}


// ---------------------------------------------------------------------------
//	¥ ResizeDataPanes												[public]
// ---------------------------------------------------------------------------
// 	Formulas:
// 	Width
// 	The number of chars should be a multiple of 6
// in order to group them by two or by three.
// If nc is the number of chars per line:
// 		fract = (TGBXw - 29) / (CHARw x 12)
// 		nc = E(fract)
// 	==>  
// 		HDSVw = TDSVw = nc x CHARw x 6
// 
// 	Height:
// 	If nl is the number of lines in each panel:
// 		fract = TGBXh / CHARh
// 		nl = E(fract)
// 	==>  
// 		HDSVh = TDSVh = nl x CHARh

void
CCompResultWindow::ResizeDataPanes()
{
	SDimension16	theSize;
	SInt16			theWidth, theHeight;
	SInt16			numChar, numLine;
	
	LTextGroupBox * theTGBX = dynamic_cast<LTextGroupBox *>(this->FindPaneByID( item_CompResultEditGroupBox ));
	ThrowIfNil_( theTGBX );
	theTGBX->GetFrameSize(theSize);
	numChar = (theSize.width - kRzilResCompExtraWidth) / (CRezillaApp::sBasics.charWidth * 12);
	numLine = (theSize.height - kRzilResCompExtraHeight) / CRezillaApp::sBasics.charHeight;
	
	// Left and right panes (hexadecimal and readable representations) have
	// the same dimensions. 
	theWidth = numChar * CRezillaApp::sBasics.charWidth * 6;
	theHeight = numLine * CRezillaApp::sBasics.charHeight;
	mOldRezDataWE->ResizeFrameTo(theWidth, theHeight, true);
	mNewRezDataWE->ResizeFrameTo(theWidth, theHeight, true);
}


// ---------------------------------------------------------------------------
//	¥ GetPaneCount												[public]
// ---------------------------------------------------------------------------
// Return various capacities.

SInt32
CCompResultWindow::GetPaneCount(SInt16 whichValue)
{
	SInt32			result = 0;
	
	switch (whichValue) {
		case count_LinesPerPane:
		result = mLinesPerPane;
		break;
		
		case count_BytesPerLine:
		switch (mDisplayDataFormat) {
			case compare_displayAsHex:
			result = mHexBytesPerLine;
			break;
			
			case compare_displayAsTxt:
			result = mTxtBytesPerLine;
			break;
		}
		break;
		
		case count_BytesPerPane:
		switch (mDisplayDataFormat) {
			case compare_displayAsHex:
			result = mLinesPerPane * mHexBytesPerLine;
			break;
			
			case compare_displayAsTxt:
			result = mLinesPerPane * mTxtBytesPerLine;
			break;
		}
		break;
		
	}
	return result;
}


// ---------------------------------------------------------------------------
//	¥ UpdatePaneCounts												[public]
// ---------------------------------------------------------------------------
// 	mBytesPerLine is a count of virtual bytes which has to be multiplied
// 	by 3 (two hex digits + space) in hex representation or by 2 in text
// 	representation (one char + space)

void
CCompResultWindow::UpdatePaneCounts()
{
	SDimension16	theSize;
	
	mOldRezDataWE->GetFrameSize(theSize);
	mLinesPerPane = theSize.height / CRezillaApp::sBasics.charHeight;
	mHexBytesPerLine = theSize.width / (CRezillaApp::sBasics.charWidth * 3);
	mTxtBytesPerLine = theSize.width / (CRezillaApp::sBasics.charWidth * 2);
}

