// ===========================================================================
// CHexEditorWindow.cp					
// 
//                       Created: 2004-03-02 14:18:16
//             Last modification: 2004-03-05 14:58:25
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
#include "CRezCompare.h"
#include "CRezClipboard.h"
#include "CWindowMenu.h"
#include "CHexDataWE.h"
#include "CBroadcasterTableView.h"
#include "RezillaConstants.h"
#include "UCodeTranslator.h"
#include "UMiscUtils.h"
#include "UMessageDialogs.h"

#include <LScrollBar.h>
#include <LStaticText.h>
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
}


// ---------------------------------------------------------------------------
//		¥ FinishCreateSelf				[protected]
// ---------------------------------------------------------------------------

void
CCompResultWindow::FinishCreateSelf()
{	
	LStaticText * theStaticText;
	
	// The RezCompare owner was passed in the inSuperCommander argument
	mRezCompare = dynamic_cast<CRezCompare *>(GetSuperCommander());
	// Now set the SuperCommander to be CRezillaApp itself
	SetSuperCommander(mRezCompare->GetSuperCommander());
	
	// Build the hex editing elements
	mOldHexDataWE = dynamic_cast<CHexDataWE *> (FindPaneByID( item_CompResultOldHex ));
	ThrowIfNil_(mOldHexDataWE);
			
	mNewHexDataWE = dynamic_cast<CHexDataWE *> (FindPaneByID( item_CompResultNewHex ));
	ThrowIfNil_(mNewHexDataWE);
	
	// Cache a pointer to the scrollbar separating the hex panes
	mScroller = dynamic_cast<LScrollBar *> (FindPaneByID( item_CompResultScroller ));
	
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
	
	theStaticText = dynamic_cast<LStaticText *>(FindPaneByID( item_CompResultOldStatic ));
	ThrowIfNil_(theStaticText);
	theStaticText->SetDescriptor(mRezCompare->GetOldPath());

	theStaticText = dynamic_cast<LStaticText *>(FindPaneByID( item_CompResultNewStatic ));
	ThrowIfNil_(theStaticText);
	theStaticText->SetDescriptor(mRezCompare->GetNewPath());
	
	// Link the broadcasters.
    UReanimator::LinkListenerToControls( this, this, rRidL_RezCompWindow );
	
	// Let the window listen to the tables
	mOnlyOldTable->AddListener(this);	
	mDifferTable->AddListener(this);	
	mOnlyNewTable->AddListener(this);	

	// Attach an LUndoer to each of the subpanes
	mOldHexDataWE->AddAttachment( new LUndoer );
	mNewHexDataWE->AddAttachment( new LUndoer );

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
// 	SInt32 theRangeStart, theRangeEnd;
// 	SInt32 lineStart, lineEnd;
	
	switch (inMessage) {
		
		case msg_Close:
		Hide();
		break;
		
		case msg_CompResultScroller:
		break;
		
	  case msg_CompResultDifferingTbl: {
		Handle	oldHandle, newHandle;
	    CRezTypId * theTypid;
	  
		STableCell theCell = mDifferTable->GetFirstSelectedCell();		
		mRezCompare->GetDifferingList()->FetchItemAt( theCell.row, theTypid);
		
		mRezCompare->GetOldMap()->GetWithID(theTypid->mType, theTypid->mID, oldHandle, false);
		mRezCompare->GetNewMap()->GetWithID(theTypid->mType, theTypid->mID, newHandle, false);
		
		mOldHexDataWE->InsertHexContents( *oldHandle, ::GetHandleSize(oldHandle));
		mNewHexDataWE->InsertHexContents( *newHandle, ::GetHandleSize(newHandle));
		
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
		{
			outEnabled = false;
		}
		break;

		case cmd_Close:
		{
			outEnabled = true;
		}
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
		break;

		case cmd_Paste:
		break;

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


// ---------------------------------------------------------------------------
//	¥ DoClose
// ---------------------------------------------------------------------------
//	Close the inspector window: hide it but keep it in memory

void
CCompResultWindow::DoClose()
{
	Hide();
}



// // ---------------------------------------------------------------------------
// //	¥ DisplayBothSelections											[protected]
// // ---------------------------------------------------------------------------
// 
// void
// CCompResultWindow::DisplayBothSelections(SInt32 inStart, SInt32 inEnd)
// {
// }


// ---------------------------------------------------------------------------
//	¥ IsDirty														[public]
// ---------------------------------------------------------------------------

Boolean
CCompResultWindow::IsDirty()
{
/* 	return (mHexDataWE->IsDirty() || mTxtDataWE->IsDirty()); */
    return true;
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
	SInt32 linesPerPane, theLineCount;
	SDimension16	theSize;

	// How many lines fit in the hex panes
	mOldHexDataWE->GetFrameSize(theSize);
	linesPerPane = theSize.height / mOldHexDataWE->GetLineHeight();

	theLineCount = HexLineCount(linesPerPane) - linesPerPane + 1;
	
	if (theLineCount < 0) {
		theLineCount = 0;
	} 
	mScroller->SetMaxValue(theLineCount);
}


// ---------------------------------------------------------------------------
//	¥ HexLineCount										[protected]
// ---------------------------------------------------------------------------
// Find the max number of lines among the two panes

SInt32
CCompResultWindow::HexLineCount(SInt32 inLinesPerPane) 
{
	SInt32 oldByteCount = WEGetTextLength( mOldHexDataWE->GetWasteRef() );
	SInt32 newByteCount = WEGetTextLength( mNewHexDataWE->GetWasteRef() );
	SInt32 oldLineCount = 0;
	SInt32 newLineCount = 0;

	if (oldByteCount) {
		oldLineCount = oldByteCount / inLinesPerPane;
		oldLineCount += (oldByteCount % kRzilHexPerLine == 0) ? 0:1 ;
	} 
	if (newByteCount) {
		newLineCount = newByteCount / inLinesPerPane;
		newLineCount += (newByteCount % kRzilHexPerLine == 0) ? 0:1 ;
	} 
	return ((oldLineCount > newLineCount) ? oldLineCount:newLineCount );
}
