// ===========================================================================
// CHexEditorWindow.cp					
// 
//                       Created: 2004-03-02 14:18:16
//             Last modification: 2004-03-02 14:26:17
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
#include "CRezillaApp.h"
#include "CRezCompare.h"
#include "CRezClipboard.h"
#include "CWindowMenu.h"
#include "CWasteEditView.h"
#include "CBroadcasterTableView.h"
#include "RezillaConstants.h"
#include "UCodeTranslator.h"
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
	mOldHexDataWE = dynamic_cast<CWasteEditView *> (FindPaneByID( item_CompResultOldHex ));
	ThrowIfNil_(mOldHexDataWE);
			
	mNewHexDataWE = dynamic_cast<CWasteEditView *> (FindPaneByID( item_CompResultNewHex ));
	ThrowIfNil_(mNewHexDataWE);
	
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
	
	// Populate the tables
	
	
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
	SInt32 theRangeStart, theRangeEnd;
	SInt32 lineStart, lineEnd;
	
	switch (inMessage) {
		
		case msg_Close:
		Hide();
		break;
		

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



// ---------------------------------------------------------------------------
//	¥ DisplayBothSelections											[protected]
// ---------------------------------------------------------------------------

void
CCompResultWindow::DisplayBothSelections(SInt32 inStart, SInt32 inEnd)
{
}


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
// 	ListHandle theListH = mCategoriesListBox->GetMacListH();
// 	Cell theCell = {0,0};
// 
// 	::LSetDrawingMode(false, theListH);
// 	for (SInt16 theIndex = 0; theIndex < 4; theIndex++) {
// 		LStr255 theString(categoryNames[theIndex]);
// 		Str255	theNumStr;
// 		::NumToString( inCatNum[theIndex], theNumStr );
// 		theString += theNumStr ;
// 		mCategoriesListBox->SelectOneCell(theCell);
// 		mCategoriesListBox->SetDescriptor(theString);
// 		++theCell.v;
// 	}
// 	::LSetDrawingMode(true, theListH);
// 	mCategoriesListBox->Refresh();
// 	
// 	char	theStatus[255];
// 	sprintf(theStatus,"%i events - %i classes - %i comparison operators - %i enumerations", 
// 			inCatNum[0], inCatNum[1], inCatNum[2], inCatNum[3]);
// 	mWindow->DisplayStatus(theStatus);
}



