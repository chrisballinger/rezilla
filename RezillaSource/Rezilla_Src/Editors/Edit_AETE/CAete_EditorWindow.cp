// ===========================================================================
// CAete_EditorWindow.cp
// 
//                       Created: 2004-07-01 08:42:37
//             Last modification: 2005-01-21 14:45:53
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2004-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#include "CAete_EditorWindow.h"
#include "CAete_EditorDoc.h"
#include "CRezillaApp.h"
#include "RezillaConstants.h"
#include "CAete.h"
#include "CAeteSuite.h"
#include "CAeteStream.h"

// PP headers
#include <LPageController.h>
#include <LMultiPanelView.h>
#include <LSlider.h>
#include <LStaticText.h>
#include <LPopupButton.h>
#include <LWindow.h>


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

// Statics
LMenu *		CAete_EditorWindow::sAeteMenu = nil;


// ---------------------------------------------------------------------------
//  CAete_EditorWindow										[public]
// ---------------------------------------------------------------------------

CAete_EditorWindow::CAete_EditorWindow()
		: CEditorWindow()
{
}


// ---------------------------------------------------------------------------
//  CAete_EditorWindow										[public]
// ---------------------------------------------------------------------------

CAete_EditorWindow::CAete_EditorWindow(
	const SWindowInfo &inWindowInfo )
		: CEditorWindow( inWindowInfo )
{
}


// ---------------------------------------------------------------------------
//  CAete_EditorWindow										[public]
// ---------------------------------------------------------------------------

CAete_EditorWindow::CAete_EditorWindow(
	ResIDT		inWINDid,
	UInt32		inAttributes,
	LCommander	*inSuperCommander )
		: CEditorWindow( inWINDid, inAttributes, inSuperCommander )
{
}


// ---------------------------------------------------------------------------
//  CAete_EditorWindow										[public]
// ---------------------------------------------------------------------------

CAete_EditorWindow::CAete_EditorWindow(
			       LStream *inStream )
		: CEditorWindow( inStream )
{
}


// ---------------------------------------------------------------------------
//  ~CAete_EditorWindow										[public]
// ---------------------------------------------------------------------------

CAete_EditorWindow::~CAete_EditorWindow()
{
	if (mAete) {
		delete mAete;
	} 
}


// ---------------------------------------------------------------------------
//  FinishCreateSelf											[protected]
// ---------------------------------------------------------------------------
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

void
CAete_EditorWindow::FinishCreateSelf()
{    
	mAete = nil;
	mCurrentPanel = mpv_AeteEvents;
	
	mSuitesPopup = dynamic_cast<LPopupButton *> (this->FindPaneByID( item_AeteSuitePopup ));
	ThrowIfNil_( mSuitesPopup );
	
	mController = dynamic_cast<LPageController *> (this->FindPaneByID( item_AetePanelController ));
	ThrowIfNil_( mController );
			
	mMultiPanel = dynamic_cast<LMultiPanelView *> (this->FindPaneByID( item_AeteMultiPanelView ));
	ThrowIfNil_( mMultiPanel );
	
	mMainSlider = dynamic_cast<LSlider *> (this->FindPaneByID( item_AeteItemSlider ));
	ThrowIfNil_( mMainSlider );

	mIndicator = dynamic_cast<LStaticText *> (this->FindPaneByID( item_AeteItemIndicator ));
	ThrowIfNil_( mIndicator );
	
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
	outEnabled = true;
	outUsesMark = false;
	outMark = 0;
	outName[0] = 0;
	
	switch (inCommand) {
		case cmd_AeteAddSuite:
		break;

		case cmd_AeteRemoveSuite:
		break;

		case cmd_AeteAddItem:
		break;

		case cmd_AeteRemoveItem:
		break;

		case cmd_AeteAddParameter:
		break;

		case cmd_AeteRemoveParameter:
		break;

		case cmd_AeteAddProperty:
		break;

		case cmd_AeteRemoveProperty:
		break;

		case cmd_AeteAddElement:
		break;

		case cmd_AeteRemoveElement:
		break;

		case cmd_AeteAddKeyForm:
		break;

		case cmd_AeteRemoveKeyForm:
		break;

		case cmd_AeteAddEnumerator:
		break;

		case cmd_AeteRemoveEnumerator:
		break;

		case cmd_AeteImport:
		break;

		case cmd_AeteExport:
		break;

		default:
		CEditorWindow::FindCommandStatus(inCommand, outEnabled,
									  outUsesMark, outMark, outName);
		break;
	}
}


// ---------------------------------------------------------------------------
// 	PutOnDuty
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::PutOnDuty(LCommander *inNewTarget)
{
	LWindow::PutOnDuty(inNewTarget);

	// Put up our menus when on duty
	if ( !sAeteMenu )
	{
		sAeteMenu = new LMenu( MENU_AeteTerminology );
		ThrowIfNil_( sAeteMenu );
	}
	
	// Update the menu bar
	LMenuBar *	theBar = LMenuBar::GetCurrentMenuBar();
	theBar->InstallMenu( sAeteMenu, MENU_OpenedWindows );	
}


// ---------------------------------------------------------------------------
// 	TakeOffDuty
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::TakeOffDuty()
{		
	LWindow::TakeOffDuty();
	
	LMenuBar *	theBar = LMenuBar::GetCurrentMenuBar();
	if ( sAeteMenu )
		theBar->RemoveMenu( sAeteMenu );
}


// ---------------------------------------------------------------------------
//  ListenToMessage										[public]
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
//  InstallAete														[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::InstallAete(Handle inHandle) 
{
	StHandleLocker lock(inHandle);
	
	CAeteStream * theStream = new CAeteStream(inHandle);
	
	mAete = new CAete(theStream);
	delete theStream;
	
	FillSuitePopup();
	InstallSuiteValues();
	InstallPanelValues();
}


// ---------------------------------------------------------------------------
//  FillSuitePopup													[public]
// ---------------------------------------------------------------------------
// Note: LMenuController::AppendMenu() takes care of updating the
// MenuMinMax values whereas a direct call to ToolBox's ::AppendMenu()
// does not.

void
CAete_EditorWindow::FillSuitePopup()
{
	MenuRef    theMenuH = mSuitesPopup->GetMacMenuH();
	ThrowIfNil_(theMenuH);
	
	TArrayIterator<CAeteSuite*>	iterator( *mAete->GetSuites() );
	CAeteSuite *	theSuite;
	Str255			theString;

	while (iterator.Next(theSuite)) {
		theSuite->GetName(theString);
		
		if ( theString[0] ) {
			mSuitesPopup->AppendMenu(theString);
		} else {
			mSuitesPopup->AppendMenu("\p<unnamed suite>");
		}
	}
	mSuitesPopup->SetMacMenuH(theMenuH);
}


// ---------------------------------------------------------------------------
//  InstallSuiteValues												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::InstallSuiteValues()
{
}


// ---------------------------------------------------------------------------
//  InstallPanelValues												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::InstallPanelValues()
{
}


