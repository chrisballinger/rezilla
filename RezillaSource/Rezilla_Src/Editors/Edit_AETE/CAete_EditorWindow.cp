// ===========================================================================
// CAete_EditorWindow.cp
// 
//                       Created: 2004-07-01 08:42:37
//             Last modification: 2005-01-20 22:39:51
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2004, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#include "CAete_EditorWindow.h"
#include "CAete_EditorDoc.h"
#include "CRezillaApp.h"
#include "RezillaConstants.h"
// #include "CAppleScript.h"

// PP headers
#include <LStaticText.h>
#include <LPopupButton.h>

// Standard headers
// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>
// #include <stdarg.h>

// static const Str255 categoryNames[] = {
// 	"\pSuites: ",
// 	"\pEvents: ",
// 	"\pClasses: ",
// 	"\pComparison Ops: ",
// 	"\pEnumerations: "
// };


// ---------------------------------------------------------------------------
//		¥ CAete_EditorWindow										[public]
// ---------------------------------------------------------------------------

CAete_EditorWindow::CAete_EditorWindow()
		: CEditorWindow()
{
}


// ---------------------------------------------------------------------------
//		¥ CAete_EditorWindow										[public]
// ---------------------------------------------------------------------------

CAete_EditorWindow::CAete_EditorWindow(
	const SWindowInfo &inWindowInfo )
		: CEditorWindow( inWindowInfo )
{
}


// ---------------------------------------------------------------------------
//		¥ CAete_EditorWindow										[public]
// ---------------------------------------------------------------------------

CAete_EditorWindow::CAete_EditorWindow(
	ResIDT		inWINDid,
	UInt32		inAttributes,
	LCommander	*inSuperCommander )
		: CEditorWindow( inWINDid, inAttributes, inSuperCommander )
{
}


// ---------------------------------------------------------------------------
//		¥ CAete_EditorWindow										[public]
// ---------------------------------------------------------------------------

CAete_EditorWindow::CAete_EditorWindow(
			       LStream *inStream )
		: CEditorWindow( inStream )
{
}


// ---------------------------------------------------------------------------
//		¥ ~CAete_EditorWindow										[public]
// ---------------------------------------------------------------------------

CAete_EditorWindow::~CAete_EditorWindow()
{
}


// ---------------------------------------------------------------------------
//		¥ FinishCreateSelf											[protected]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::FinishCreateSelf()
{    
//     mContentsScroller = dynamic_cast<LScrollerView *>(this->FindPaneByID( item_EditorScroller ));
//     ThrowIfNil_(mContentsScroller);
// 	
//     mContentsView = dynamic_cast<LView *>(this->FindPaneByID( item_EditorContents ));
//     ThrowIfNil_(mContentsView);

	mSuitesPopup = dynamic_cast<LPopupButton *> (this->FindPaneByID( item_AeteSuitesPopup ));
	ThrowIfNil_( mSuitesPopup );
	
// 	mCategoriesListBox = dynamic_cast<CCategoriesListBox *> (this->FindPaneByID( item_AeteCategories ));
// 	ThrowIfNil_( mCategoriesListBox );
			
// 	ListHandle theListH = mCategoriesListBox->GetMacListH();
// 	Cell theCell = {0,0};
// 	::LAddColumn(1, 0, theListH);
// 	for (SInt16 theIndex = 0; theIndex < 4; theIndex++) {
// 		::LAddRow(1,theCell.v,theListH);
// 		++theCell.v;
// 	}
// 
// 	// Build the table elements
// 	mDictTermsTable = dynamic_cast<CBroadcasterTableView *> (mAeteEditWindow->FindPaneByID( item_AeteTermsTable ));
// 	ThrowIfNil_( mDictTermsTable );
// 	
// 	// Set Geometry and Selector TableView members.
// 	mDictTermsTable->SetTableGeometry(new LTableMonoGeometry(mDictTermsTable, kAeteTableWidth, kAeteTableHeight));
// 	mDictTermsTable->SetTableSelector(new LTableSingleSelector(mDictTermsTable));
// 	mDictTermsTable->SetTableStorage(new LTableArrayStorage(mDictTermsTable, sizeof(Str255)));
// 
// 	mDictTermsTable->InsertCols(1, 0);

	// Link the broadcasters
	UReanimator::LinkListenerToControls( this, this, PPob_AeteEditorWindow );
	
// 	// Make the DictDoc a listener of mCategoriesListBox
// 	mCategoriesListBox->AddListener(this);
// 	mDictTermsTable->AddListener(this);
	
// 	mAeteStreamsArrayPtr = new TArray<CAeteStream*>();

//     SwitchTarget(mContentsView);
}


// ---------------------------------------------------------------------------
//	¥ FindCommandStatus
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::FindCommandStatus(
	CommandT	inCommand,
	Boolean		&outEnabled,
	Boolean		&outUsesMark,
	UInt16		&outMark,
	Str255		outName)
{
	switch (inCommand) {
		
		default:
		CEditorWindow::FindCommandStatus(inCommand, outEnabled,
									  outUsesMark, outMark, outName);
		break;
	}
}


// ---------------------------------------------------------------------------
//		¥ ListenToMessage				[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{
#pragma unused( ioParam )

	switch (inMessage) {
		
// 	  case msg_DictSaveButton:
// 		ObeyCommand(cmd_SaveDict,nil);
// 		break;
				
		
	}
}


// ---------------------------------------------------------------------------
//		¥ InstallAete											[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::InstallAete(Handle inHandle) 
{
}


// ---------------------------------------------------------------------------
//		¥ EmptyContents											[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::EmptyContents()
{
}


