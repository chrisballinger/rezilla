// ===========================================================================
// CTmplEditorWindow.cp					
// 
//                       Created: 2004-06-12 15:08:01
//             Last modification: 2004-08-01 22:54:24
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#include "CTmplEditorWindow.h"
#include "CTmplEditorDoc.h"
#include "CTmplListItemView.h"
#include "CTmplListButton.h"
#include "CTmplBevelButton.h"
#include "CRezEditor.h"
#include "CRezObj.h"
#include "CRezillaApp.h"
#include "CRezillaPrefs.h"
#include "CDualDataView.h"
#include "CHexDataSubView.h"
#include "CSingleScrollBar.h"
#include "CTxtDataSubView.h"
#include "CWasteEditView.h"
#include "UMiscUtils.h"
#include "UMessageDialogs.h"
#include "UHexFilters.h"
#include "UCodeTranslator.h"

#include <LScrollBar.h>
#include <LStaticText.h>
#include <LIconPane.h>
#include <LEditText.h>
#include <LTextGroupBox.h>
#include <LCheckBox.h>
#include <LPushButton.h>
#include <LScrollerView.h>
// #include <LBevelButton.h>
#include <LSeparatorLine.h>
#include <UDrawingState.h>
#include <LArray.h>

#include <ControlDefinitions.h>
// #include <LMenuController.h>

#include <stdio.h>
#include <string.h>


// ---------------------------------------------------------------------------
//		¥ CTmplEditorWindow				[public]
// ---------------------------------------------------------------------------

CTmplEditorWindow::CTmplEditorWindow()
{
}


// ---------------------------------------------------------------------------
//		¥ CTmplEditorWindow				[public]
// ---------------------------------------------------------------------------

CTmplEditorWindow::CTmplEditorWindow(
	const SWindowInfo &inWindowInfo )
		: CEditorWindow( inWindowInfo )
{
}


// ---------------------------------------------------------------------------
//		¥ CTmplEditorWindow				[public]
// ---------------------------------------------------------------------------

CTmplEditorWindow::CTmplEditorWindow(
	ResIDT		inWINDid,
	UInt32		inAttributes,
	LCommander	*inSuperCommander )
		: CEditorWindow( inWINDid, inAttributes, inSuperCommander )
{
}


// ---------------------------------------------------------------------------
//		¥ CTmplEditorWindow				[public]
// ---------------------------------------------------------------------------

CTmplEditorWindow::CTmplEditorWindow(
			       LStream *inStream )
		: CEditorWindow( inStream )
{
}


// ---------------------------------------------------------------------------
//		¥ ~CTmplEditorWindow				[public]
// ---------------------------------------------------------------------------

CTmplEditorWindow::~CTmplEditorWindow()
{
	if (mTemplateStream != nil) {
		delete mTemplateStream;
	} 
	if (mRezStream != nil) {
		delete mRezStream;
	} 
	if (mOutStream != nil) {
		delete mOutStream;
	} 

	// Remove the window from the list of listeners to the prefs object
	CRezillaApp::sPrefs->RemoveListener(this);
}


// ---------------------------------------------------------------------------
//		¥ FinishCreateSelf				[protected]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::FinishCreateSelf()
{	
	mCurrentID			= 1;
	mLastID				= 0;
	mItemsCount			= 0;
	mIndent				= 0;
	mYCoord             = kTmplVertSkip;
	mLeftLabelTraitsID	= Txtr_GenevaTenBoldUlLeft;
	mRightLabelTraitsID	= Txtr_GenevaTenBoldUlRight;
	mEditTraitsID		= Txtr_GenevaTen;
	mHeaderTraitsID		= Txtr_GenevaTenBold;
	mTemplateStream		= nil;
	mRezStream			= nil;
	mOutStream			= nil;
	
	// The main view containing the labels and editing panes
	mContentsView = dynamic_cast<LView *>(this->FindPaneByID(item_EditorContents));
	ThrowIfNil_( mContentsView );
	
	// Set the initial size of the image to mYCoord (= kTmplVertSkip)
	mContentsView->ResizeImageTo(0, mYCoord, false);
	
	// The scroller controlling the contents view
	mContentsScroller = dynamic_cast<LScrollerView *>(this->FindPaneByID(item_EditorScroller));
	ThrowIfNil_( mContentsScroller );
		
	// Install the name of the resource if it has one
	LStaticText * theStaticText = dynamic_cast<LStaticText *>(this->FindPaneByID( item_NameStaticText ));
	ThrowIfNil_( theStaticText );
	Str255 * strPtr = dynamic_cast<CTmplEditorDoc *>(GetSuperCommander())->GetRezObj()->GetName();
	theStaticText->SetDescriptor(*strPtr);	
	
	// Link the broadcasters
	UReanimator::LinkListenerToControls( this, this, rRidL_TmplEditorWindow );
	
	// Make the window a listener to the prefs object
	CRezillaApp::sPrefs->AddListener(this);

	// Label fields basic values
	mStaticPaneInfo.paneID			= 0;
	mStaticPaneInfo.height			= kTmplLabelHeight;
	mStaticPaneInfo.visible			= true;
	mStaticPaneInfo.enabled			= true;
	mStaticPaneInfo.bindings.left	= true;
	mStaticPaneInfo.bindings.top	= false;
	mStaticPaneInfo.bindings.right	= false;
	mStaticPaneInfo.bindings.bottom = false;
	mStaticPaneInfo.userCon			= 0;
	
	// Edit fields basic values
	mEditPaneInfo.paneID			= 0;
	mEditPaneInfo.height			= kTmplEditHeight;
	mEditPaneInfo.visible			= true;
	mEditPaneInfo.enabled			= true;
	mEditPaneInfo.bindings.left		= true;
	mEditPaneInfo.bindings.top		= false;
	mEditPaneInfo.bindings.right	= true;
	mEditPaneInfo.bindings.bottom	= false;
	mEditPaneInfo.userCon			= 0;

	// Radio group view basic values
	mRgvPaneInfo.paneID				= 0;
	mRgvPaneInfo.width				= kTmplRgvWidth;
	mRgvPaneInfo.height				= kTmplRgvHeight;
	mRgvPaneInfo.visible			= true;
	mRgvPaneInfo.enabled			= true;
	mRgvPaneInfo.bindings.left		= true;
	mRgvPaneInfo.bindings.top		= false;
	mRgvPaneInfo.bindings.right		= false;
	mRgvPaneInfo.bindings.bottom	= false;
	mRgvPaneInfo.userCon			= 0;
	
	// Radio buttons basic values
	mRadioPaneInfo.paneID			= 0;
	mRadioPaneInfo.width			= kTmplRadioWidth;
	mRadioPaneInfo.height			= kTmplRadioHeight;
	mRadioPaneInfo.visible			= true;
	mRadioPaneInfo.enabled			= true;
	mRadioPaneInfo.bindings.left	= true;
	mRadioPaneInfo.bindings.top		= false;
	mRadioPaneInfo.bindings.right	= false;
	mRadioPaneInfo.bindings.bottom	= false;
	mRadioPaneInfo.userCon			= 0;

	// Check boxes basic values
	mCheckPaneInfo.paneID			= 0;
	mCheckPaneInfo.width			= kTmplCheckWidth;
	mCheckPaneInfo.height			= kTmplCheckHeight;
	mCheckPaneInfo.visible			= true;
	mCheckPaneInfo.enabled			= true;
	mCheckPaneInfo.bindings.left	= true;
	mCheckPaneInfo.bindings.top		= false;
	mCheckPaneInfo.bindings.right	= false;
	mCheckPaneInfo.bindings.bottom	= false;
	mCheckPaneInfo.userCon			= 0;

	// Rectangle labels basic values
	mRectLabelInfo.paneID			= 0;
	mRectLabelInfo.width			= kTmplRectWidth;
	mRectLabelInfo.height			= kTmplRectHeight;
	mRectLabelInfo.visible			= true;
	mRectLabelInfo.enabled			= true;
	mRectLabelInfo.bindings.left	= true;
	mRectLabelInfo.bindings.top		= false;
	mRectLabelInfo.bindings.right	= false;
	mRectLabelInfo.bindings.bottom	= false;
	mRectLabelInfo.userCon			= 0;

	// Rectangle edit basic values
	mRectPaneInfo.width				= kTmplRectWidth;
	mRectPaneInfo.height			= kTmplEditHeight;
	mRectPaneInfo.visible			= true;
	mRectPaneInfo.enabled			= true;
	mRectPaneInfo.bindings.left		= true;
	mRectPaneInfo.bindings.top		= false;
	mRectPaneInfo.bindings.right	= false;
	mRectPaneInfo.bindings.bottom	= false;
	mRectPaneInfo.userCon			= 0;
	
	// Active scrollers basic values
	mScrollPaneInfo.paneID			= 0;
	mScrollPaneInfo.visible			= true;
	mScrollPaneInfo.enabled			= true;
	mScrollPaneInfo.bindings.left	= false;
	mScrollPaneInfo.bindings.top	= true;
	mScrollPaneInfo.bindings.right	= true;
	mScrollPaneInfo.bindings.bottom	= true;
	mScrollPaneInfo.userCon			= 0;

	// Text group box for text views basic values
	mTgbPaneInfo.height				= kTmplTextHeight;
	mTgbPaneInfo.visible			= true;
	mTgbPaneInfo.enabled			= true;
	mTgbPaneInfo.bindings.left		= true;
	mTgbPaneInfo.bindings.top		= false;
	mTgbPaneInfo.bindings.right		= true;
	mTgbPaneInfo.bindings.bottom	= false;
	mTgbPaneInfo.userCon			= 0;

	// Text views basic values
	mWastePaneInfo.paneID			= 0;
	mWastePaneInfo.visible			= true;
	mWastePaneInfo.enabled			= true;
	mWastePaneInfo.bindings.left	= true;
	mWastePaneInfo.bindings.top		= false;
	mWastePaneInfo.bindings.right	= true;
	mWastePaneInfo.bindings.bottom	= true;
	mWastePaneInfo.userCon			= 0;
	
	// Push buttons basic values
	mPushPaneInfo.width				= kTmplPushWidth;
	mPushPaneInfo.height			= kTmplPushHeight;
	mPushPaneInfo.visible			= true;
	mPushPaneInfo.enabled			= true;
	mPushPaneInfo.bindings.left		= false;
	mPushPaneInfo.bindings.top		= false;
	mPushPaneInfo.bindings.right	= false;
	mPushPaneInfo.bindings.bottom	= false;
	mPushPaneInfo.userCon			= 0;
	
	// List item views basic values
	mListItemInfo.height			= 0;
	mListItemInfo.visible			= true;
	mListItemInfo.enabled			= true;
	mListItemInfo.bindings.left		= true;
	mListItemInfo.bindings.top		= false;
	mListItemInfo.bindings.right	= true;
	mListItemInfo.bindings.bottom	= false;
	mListItemInfo.userCon			= 0;
	
	// Separator horizontal line basic values
	mSeparatorPaneInfo.paneID			= 0;
	mSeparatorPaneInfo.height			= kTmplSeparatorHeight;
	mSeparatorPaneInfo.visible			= true;
	mSeparatorPaneInfo.enabled			= true;
	mSeparatorPaneInfo.bindings.left	= true;
	mSeparatorPaneInfo.bindings.top		= false;
	mSeparatorPaneInfo.bindings.right	= true;
	mSeparatorPaneInfo.bindings.bottom = false;
	mSeparatorPaneInfo.userCon			= 0;
	
	// Popup button fields basic values
	mBevelPaneInfo.width			= kTmplBevelWidth;
	mBevelPaneInfo.height			= kTmplBevelHeight;
	mBevelPaneInfo.visible			= true;
	mBevelPaneInfo.enabled			= true;
	mBevelPaneInfo.bindings.left	= false;
	mBevelPaneInfo.bindings.top		= false;
	mBevelPaneInfo.bindings.right	= true;
	mBevelPaneInfo.bindings.bottom 	= false;
	mBevelPaneInfo.userCon			= 0;

}
	

// ---------------------------------------------------------------------------
//		¥ ListenToMessage				[public]
// ---------------------------------------------------------------------------
// The Plus button stores a pointer to the first list item in its UserCon
// field. The Minus button stores the marker to the beginning of the list
// template. The position four chars before the template stream's marker
// corresponds to the type of the list.

void
CTmplEditorWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{	
	Rect				theFrame;
	CTmplListItemView 	*prevListItemView, *currListItemView;
	CTmplListButton 	*theMinusButton, *thePlusButton;
	PaneIDT 			thePaneID, oldLastID, newFirstID;
	LView				*theContainer, *theView;
	SInt32 				startMark, theHeight;
	ResType				theType;
	int					sublevel = 1;

	oldLastID = mCurrentID;
	
	switch (inMessage) {
		
		case msg_TmplMinusButton:
			theMinusButton = (CTmplListButton *) ioParam;
			thePaneID = theMinusButton->GetPaneID();
			thePlusButton = dynamic_cast<CTmplListButton *>(this->FindPaneByID(thePaneID + 1));
			ThrowIfNil_(thePlusButton);
			
			startMark = theMinusButton->GetUserCon();
			theContainer = thePlusButton->GetSuperView();
			currListItemView = (CTmplListItemView *) thePlusButton->GetUserCon();
			
			if (currListItemView) {
				// Find the last list item
				while (currListItemView->mNextItem) {
					currListItemView = currListItemView->mNextItem;
				}
				currListItemView->CalcPortFrameRect(theFrame);
				theHeight = theFrame.bottom - theFrame.top + kTmplVertSkip;
			} else {
				// There is no list item: nothing to remove.
				return;
			}
			
			// Find the list item in the list of subpanes of the container view
			// and remove it
			ArrayIndexT theIndex = theContainer->GetSubPanes().FetchIndexOf(currListItemView);
			if (theIndex != LArray::index_Bad) {
				theContainer->GetSubPanes().RemoveItemsAt(1, theIndex);
			} 
			
			// Update the value of the counter in the case of an LSTC list
			mTemplateStream->SetMarker(startMark-4, streamFrom_Start);
			*mTemplateStream >> theType;
			
			if (theType == 'LSTC') {
				AdjustCounterField(thePaneID - 1, -1);
			} 

			// Adjust all IDs and positions
			RenumberSubPanes(mContentsView, currListItemView->mLastItemID, currListItemView->mFirstItemID, false);
			theContainer->PortToLocalPoint(topLeft(theFrame));
			RecalcPositions(currListItemView, theFrame.top, -theHeight);
			
			// Now delete the object
			prevListItemView = currListItemView->mPrevItem;
			if (prevListItemView) {
				prevListItemView->mNextItem = currListItemView->mNextItem;
			} else {
				// We're about to delete the first list item.
				thePlusButton->SetUserCon(nil);
			}
			
			delete currListItemView;
			
			mContentsView->ResizeImageBy(0, -theHeight, true);
			mContentsView->Refresh();
			break;
		
		
		case msg_TmplPlusButton:
			thePlusButton = (CTmplListButton *) ioParam;
			thePaneID = thePlusButton->GetPaneID();
			theMinusButton = dynamic_cast<CTmplListButton *>(this->FindPaneByID(thePaneID - 1));
			ThrowIfNil_(theMinusButton);
			
			// Retrieve cached data
			startMark = theMinusButton->GetUserCon();
			theContainer = thePlusButton->GetSuperView();
			currListItemView = (CTmplListItemView *) thePlusButton->GetUserCon();
			
			if (currListItemView) {
				// Find the last list item
				while (currListItemView->mNextItem) {
					currListItemView = currListItemView->mNextItem;
				}
				currListItemView->CalcPortFrameRect(theFrame);
				newFirstID = currListItemView->mLastItemID + 1;
			} else {
				thePlusButton->CalcPortFrameRect(theFrame);
				newFirstID = thePlusButton->GetPaneID() + 1;
			}
			
			// Calculate the insertion position of the new list item
			theContainer->PortToLocalPoint(botRight(theFrame));
			mYCoord = theFrame.bottom + kTmplVertSkip;
			prevListItemView = currListItemView;

			mContentsView->Hide();
			
			theView = theContainer;
			while (theView != mContentsView && theView != nil) {
				theView = theView->GetSuperView();
				sublevel++;
			}
			mIndent += kTmplListIndent * sublevel;

			currListItemView = AddListItemView(prevListItemView, theContainer);
			if (prevListItemView == nil) {
				thePlusButton->SetUserCon( (long) currListItemView);
			} 
			mYCoord = kTmplVertSep;
			DoParseWithTemplate(startMark, true, currListItemView);
			currListItemView->mLastItemID = mCurrentID - 1;
// 			mYCoord += kTmplVertSkip;
			currListItemView->ResizeFrameBy(0, mYCoord, false);

			mIndent -= kTmplListIndent * sublevel;

			// Update the value of the counter in the case of an LSTC list
			mTemplateStream->SetMarker(startMark-4, streamFrom_Start);
			*mTemplateStream >> theType;
			if (theType == 'LSTC') {
				AdjustCounterField(thePaneID - 2, 1);
			} 
			
			// Adjust all IDs and positions
			RenumberSubPanes(mContentsView, oldLastID, newFirstID, true);
			RecalcPositions(currListItemView, theFrame.bottom + kTmplVertSkip, mYCoord + kTmplVertSkip);
			
			mContentsView->ResizeImageBy(0, mYCoord + kTmplVertSkip, true);
			mContentsView->Show();
			mContentsView->Enable();
			mContentsView->Activate();
			break;
			
			
		case msg_TmplCasePopup:
		STmplBevelInfo theBevelInfo = *((STmplBevelInfo *) ioParam);								
// 		theBevelInfo.menuChoice
// 		theBevelInfo.selfPtr

		break;
		
		
		default:
			dynamic_cast<CTmplEditorDoc *>(GetSuperCommander())->ListenToMessage(inMessage, ioParam);
			break;
		
	}
}


// ---------------------------------------------------------------------------
//	¥ AdjustCounterField
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AdjustCounterField(PaneIDT inPaneID, SInt32 inDelta) {
	LStaticText *	theCounterText;
	Str255	numStr;
	long	theLong;
	
	theCounterText = dynamic_cast<LStaticText *>(this->FindPaneByID(inPaneID));
	theCounterText->GetDescriptor(numStr);	
	::StringToNum( numStr, &theLong);
	theLong += inDelta;
	if (theLong < 0) {
		theLong = 0;
	} 
	::NumToString(theLong, numStr);
	theCounterText->SetDescriptor(numStr);	
}


// ---------------------------------------------------------------------------
//	¥ RenumberSubPanes
// ---------------------------------------------------------------------------
// If a new list item has been inserted, its subpanes are numbered from
// (inOldLastID) to (mCurrentID - 1). The argument (inNewFirstID) is the ID
// which should normally be affected to the first numbered subpane of the new 
// list item. So there are three possibilities when a subpane is visited:
// - if its ID is < (inNewFirstID), leave it unchanged
// - if its value is >= (inNewFirstID) and < (inOldLastID), increase it by 
//   (mCurrentID - inOldLastID)
// - if its value is >= (inOldLastID), decrease it by (inOldLastID - inNewFirstID)
// 
// If a list item has been deleted, all the IDs of its subpanes will be
// removed. They are numbered between inNewFirstID and inOldLastID
// inclusive. There are two possibilities:
// - if an ID is < (inNewFirstID), leave it unchanged
// - otherwise, decrease it by (inOldLastID - inNewFirstID + 1)
//   Note that the IDs between inNewFirstID and inOldLastID won't be found since 
//   the object has already been removed from the list of subpanes. Last
//   mCurrentID has to be adjusted likewise.

void
CTmplEditorWindow::RenumberSubPanes(LView * inView, PaneIDT inOldLastID, PaneIDT inNewFirstID, Boolean adding) 
{
	PaneIDT	theID;
	LView *	theView;
	
	if (adding) {
		// We've been inserting a list item
		TArrayIterator<LPane *> iterator( inView->GetSubPanes() );
		LPane	* theSub;
		while (iterator.Next(theSub)) {
			theID = theSub->GetPaneID();
			if (theID) {
				if (theID < inNewFirstID) {
					// Do nothing
				} else if (theID < inOldLastID) {
					theID += mCurrentID - inOldLastID;
					theSub->SetPaneID(theID);
				} else {
					theID -= inOldLastID - inNewFirstID;
					theSub->SetPaneID(theID);
				}
			} 
			theView = dynamic_cast<LView *>(theSub);
			if (theView) {
				RenumberSubPanes(theView, inOldLastID, inNewFirstID, adding);
			} 
		}
		
	} else {
		
		// We've been removing a list item
		TArrayIterator<LPane *> iterator( inView->GetSubPanes() );
		LPane	* theSub;
		while (iterator.Next(theSub)) {
			theID = theSub->GetPaneID();
			if (theID) {
				if (theID < inNewFirstID) {
					// Do nothing
				} else if (theID > inOldLastID) {
					theID -= inOldLastID - inNewFirstID + 1;
					theSub->SetPaneID(theID);
				}
			} 
			theView = dynamic_cast<LView *>(theSub);
			if (theView) {
				RenumberSubPanes(theView, inOldLastID, inNewFirstID, adding);
			} 
		}
	}
}


// ---------------------------------------------------------------------------
//	¥ RecalcPositions
// ---------------------------------------------------------------------------
// If a new list item has been inserted, its first level subpanes must be
// repositioned. Their top pos must be increased by the height of the
// inserted list item. Then one must propagate to the containing view
// repeatedly until we reach the root contents view.

void
CTmplEditorWindow::RecalcPositions(LView * inView, SInt32 inVertPos, SInt32 inPosDelta) 
{
	Rect	theFrame;
	PaneIDT	theID;
	LPane *	theSub;
	SInt32	thePos = inVertPos;
	LView *	theContainer = inView->GetSuperView();
	
	while (theContainer != nil) {
		TArrayIterator<LPane *> iterator( theContainer->GetSubPanes() );
		while (iterator.Next(theSub)) {
			theSub->CalcPortFrameRect(theFrame);
			theContainer->PortToLocalPoint(topLeft(theFrame));

			if (theSub != inView && theFrame.top >= thePos) {
				theSub->MoveBy(0, inPosDelta, false);
			} 
		}
		if (theContainer == mContentsView) {
			break;
		} 
		theContainer->ResizeFrameBy(0, inPosDelta, false);
		theContainer->CalcPortFrameRect(theFrame);
		theContainer = theContainer->GetSuperView();
		if (theContainer != nil) {
			theContainer->PortToLocalPoint(topLeft(theFrame));
			// Increase by one pixel to ensure that the container won't
			// move itself
			thePos = theFrame.top + 1;
		} 
	}
}


// ---------------------------------------------------------------------------
//	¥ FindCommandStatus
// ---------------------------------------------------------------------------
//	Pass back whether a Command is enabled and/or marked (in a Menu)

void
CTmplEditorWindow::FindCommandStatus(
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
//	¥ ObeyCommand							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CTmplEditorWindow::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;
	
	switch (inCommand) {

		case cmd_Copy: 
		case cmd_Cut: 
		case cmd_Clear:
		case cmd_Paste:
		break;

		case cmd_ActionCut:
		case cmd_ActionPaste:
		case cmd_ActionClear:
		case cmd_ActionTyping:
			break;

		default:
			cmdHandled = LCommander::ObeyCommand(inCommand, ioParam);
			break;
	}

	return cmdHandled;
}


// ---------------------------------------------------------------------------
//  ¥ InstallReadOnlyIcon											[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::InstallReadOnlyIcon() 
{
	LIconPane * theIcon = dynamic_cast<LIconPane *>(this->FindPaneByID( item_ReadOnlyIcon ));
	ThrowIfNil_( theIcon );
	if (mOwnerDoc->IsReadOnly()) {
		theIcon->SetIconID(ics8_Locked);
	} else {
		theIcon->SetIconID(ics8_Unlocked);
	}
}


// ---------------------------------------------------------------------------
//	¥ IsDirty														[public]
// ---------------------------------------------------------------------------

Boolean
CTmplEditorWindow::IsDirty()
{
	return false;
}

#pragma mark -

// ---------------------------------------------------------------------------
//	¥ CreateTemplateStream									[protected]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::CreateTemplateStream()
{
	Handle theHandle = CRezEditor::GetTemplateHandle( mOwnerDoc->GetRezObj()->GetType() );
	mTemplateStream = new LHandleStream(theHandle);	
}
 

// ---------------------------------------------------------------------------
//	¥ ParseDataWithTemplate											[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::ParseDataWithTemplate(Handle inHandle)
{
	SInt32		oldYCoord = mYCoord;
	
	// Get a handle to the template resource and create a stream to parse it
	CreateTemplateStream();
	
	// Create a stream to parse the data
	mRezStream = new LHandleStream(inHandle);	
	
	// Parse the template stream
	DoParseWithTemplate(0, true, mContentsView);

	mLastID = mCurrentID;

	mContentsView->ResizeImageBy(0, mYCoord - oldYCoord, true);
	mContentsScroller->AdjustScrollBars();
}


// ---------------------------------------------------------------------------
//	¥ DoParseWithTemplate											[public]
// ---------------------------------------------------------------------------
// If 'inRezStream' is nil, an empty template is built with default values.

void
CTmplEditorWindow::DoParseWithTemplate(SInt32 inRecursionMark, Boolean inDrawControls, LView * inContainer)
{
	Str255		theString, countLabel;
	ResType		theType;

	mTemplateStream->SetMarker(inRecursionMark, streamFrom_Start);

	while (mTemplateStream->GetMarker() < mTemplateStream->GetLength() ) {
		*mTemplateStream >> theString;
		*mTemplateStream >> theType;
		
		if (theType == 'OCNT' || theType == 'ZCNT') {
			LString::CopyPStr(theString, countLabel);
			ParseDataForType(theType, theString, inContainer);
		} else if (theType == 'LSTB' || theType == 'LSTC' || theType == 'LSTZ') {
			if (inDrawControls) {
				AddListHeaderField(theType, theString, mItemsCount, countLabel, inContainer);
			}
			ParseList(mTemplateStream->GetMarker(), theType, mItemsCount, inContainer);
		} else if (theType == 'LSTE') {
			break;
		} else {
			if (inDrawControls) {
				// Create controls according to the type declared in the template
				ParseDataForType(theType, theString, inContainer);
			} 
		}
	}
}


// ---------------------------------------------------------------------------
//	¥ ParseList													[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::ParseList(SInt32 inStartMark, ResType inType, SInt32 inCount, LView * inContainer)
{
	mIndent += kTmplListIndent;
	
	CTmplListItemView * prevListItemView = nil;
	CTmplListItemView * currListItemView = nil;
	SInt32		outYCoord = mYCoord;
	
	CTmplListButton * thePlusButton = dynamic_cast<CTmplListButton *>(this->FindPaneByID(mCurrentID - 1));
	LView * theContainer = inContainer;

	switch (inType) {
		case 'LSTB':
		case 'LSTZ':
		Boolean drawCtrl = (mRezStream->GetMarker() < mRezStream->GetLength());
		mYCoord = outYCoord;
		do {
			if (drawCtrl) {
				currListItemView = AddListItemView(prevListItemView, inContainer);
				prevListItemView = currListItemView;
				theContainer = currListItemView;
				if (thePlusButton->GetUserCon() == nil) {
					thePlusButton->SetUserCon( (long) currListItemView);
				} 
			}
			mYCoord = kTmplVertSep;
			DoParseWithTemplate(inStartMark, drawCtrl, theContainer);
			currListItemView->mLastItemID = mCurrentID - 1;
			if (drawCtrl) {
				currListItemView->ResizeFrameBy(0, mYCoord, false);
				outYCoord += mYCoord + kTmplVertSkip;
				mYCoord = outYCoord;
			} 
		} while (! EndOfList(inType) );
		
		break;
		
		case 'LSTC':
		if (inCount == 0) {
			DoParseWithTemplate(inStartMark, false, theContainer);
		} else {
			mYCoord = outYCoord;
			for (short i = 0 ; i < inCount; i++) {
				currListItemView = AddListItemView(prevListItemView, inContainer);
				prevListItemView = currListItemView;
				theContainer = currListItemView;
				if (thePlusButton->GetUserCon() == nil) {
					thePlusButton->SetUserCon( (long) currListItemView);
				} 
				mYCoord = kTmplVertSep;
				DoParseWithTemplate(inStartMark, true, theContainer);
				currListItemView->mLastItemID = mCurrentID - 1;
				currListItemView->ResizeFrameBy(0, mYCoord, false);
				outYCoord += mYCoord + kTmplVertSkip;
				mYCoord = outYCoord;
			}
		}
		break;
		
	}
	
	mIndent -= kTmplListIndent;
}


// ---------------------------------------------------------------------------
//	¥ EndOfList													[public]
// ---------------------------------------------------------------------------

Boolean
CTmplEditorWindow::EndOfList(ResType inType)
{
	Boolean result = false;
	UInt8	theChar;

	switch (inType) {
		case 'LSTB':
		if (mRezStream->GetMarker() >= mRezStream->GetLength() ) {
			result = true;
		} 
		break;
		
		case 'LSTC':
		result = true;
		break;
		
		case 'LSTZ':
		if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
			*mRezStream >> theChar;
			if (theChar == 0) {
				result = true;
			} else {
				mRezStream->SetMarker(-1, streamFrom_Marker);
			}
		} else {
			result = true;
		}
		break;
		
	}
	return result;
}


// ---------------------------------------------------------------------------
//	¥ ParseDataForType												[public]
// ---------------------------------------------------------------------------

// TODO:
//   - add error checking: insufficient data, required null bytes
//   - insert in try blocks and catch exceptions

OSErr
CTmplEditorWindow::ParseDataForType(ResType inType, Str255 inLabelString, LView * inContainer)
{
	OSErr	error = noErr;
	char	theChar = 0;
	char 	charString[256];
	Str255	numStr, theString;
	SInt8	theSInt8 = 0;
	SInt16	theSInt16 = 0;
	SInt32	theSInt32 = 0, theLength;
	SInt8	theUInt8 = 0;
	UInt16	theUInt16 = 0;
	UInt32	theUInt32 = 0;
	Boolean	theBool = 0;
	OSType	theOSType;
	SInt8	i;
		
	switch (inType) {
		case 'ALNG':
		// Long align
		AlignBytesRead(4);
		break;

		case 'AWRD':
		// Word align
		AlignBytesRead(2);
		break;

		case 'BBIT':
		// Binary bit (there must be 8 or an even multiple of 8 of these).
		// High bit first.
		if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
			*mRezStream >> theChar;
		} 
		// Edit the first bit
		AddStaticField(inLabelString, inContainer);
		AddCheckField( ((theChar & 1<<7) > 0), inType, inContainer);	
		for (i = 6; i >= 0 ; i--) {
			// Consume the next 7 pairs in the template to get the
			// corresponding labels.
			*mTemplateStream >> theString;
			*mTemplateStream >> theOSType;
			AddStaticField(theString, inContainer);
			AddCheckField( ((theChar & (1 << i)) > 0), inType, inContainer);	
		}
		break;

		case 'BFLG':
		// Boolean (one byte: 0x01 for true, 0x00 for false)
		if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
			*mRezStream >> theBool;
		} 
		AddStaticField(inLabelString, inContainer);
		AddCheckField( theBool, inType, inContainer);		
		break;

		case 'BOOL':
		// Boolean (two bytes: 0x0100 for true, 0x0000 for false)
		if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
			*mRezStream >> theBool;
		} 
		AddStaticField(inLabelString, inContainer);
		AddBooleanField( theBool, inType, tmpl_titleYesNo, inContainer);		
		// BOOL template type is two bytes long, so let's consume one more byte
		if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
			*mRezStream >> theBool;
		} 
		break;

		case 'CASE':
		// Switch with predefined values
		AddPopupField(inType, inLabelString, inContainer);		
		break;

		case 'CHAR':
		// A single character
		if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
			*mRezStream >> theChar;
			theString[0] = 1;
			theString[1] = theChar;
		} else {
			theString[0] = 0;
		}
		AddStaticField(inLabelString, inContainer);
		AddEditField(theString, inType, 1, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_PrintingChar), inContainer);
		break;

		case 'CSTR':
		// C string. This should be either characters followed by a null or all
		// the chars until the end of the stream if there is no null byte.
		AddStaticField(inLabelString, inContainer, mLeftLabelTraitsID);
		mYCoord += kTmplLabelHeight + kTmplVertSkip;
		AddWasteField(inType, inContainer);
 		break;

		case 'DBYT':
		// Decimal byte
		if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
			*mRezStream >> theUInt8;
		} 
		::NumToString( (long) theUInt8, numStr);
		AddStaticField(inLabelString, inContainer);
		AddEditField(numStr, inType, 3, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_Integer), inContainer);
		break;

		case 'DLNG':
		// Decimal long word
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 3) {
			*mRezStream >> theUInt32;
		} 
		::NumToString( (long) theUInt32, numStr);
		AddStaticField(inLabelString, inContainer);
		AddEditField(numStr, inType, 5, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_Integer), inContainer);
		break;

		case 'DWRD':
		// Decimal word
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 1) {
			*mRezStream >> theUInt16;
		} 
		::NumToString( (long) theUInt16, numStr);
		AddStaticField(inLabelString, inContainer);
		AddEditField(numStr, inType, 10, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_Integer), inContainer);
		break;

		case 'ECST':
		// Even-padded C string (padded with nulls)
		AddStaticField(inLabelString, inContainer, mLeftLabelTraitsID);
		mYCoord += kTmplLabelHeight + kTmplVertSkip;
		// Padding is handled there
		AddWasteField(inType, inContainer);
		break;

		case 'ESTR':
		// Pascal string padded to even length (needed for DITL resources)
		if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
			*mRezStream >> theString;
			theLength = theString[0];
			if (theLength % 2 == 0) {
				// if the length is even, the string has been padded. So skip the next char.
				if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
					*mRezStream >> theChar;
				}
			} 
		} else {
			theString[0] = 0;
		}
		AddStaticField(inLabelString, inContainer);
		AddEditField(theString, inType, 255, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_PrintingChar), inContainer);
		
		break;

		case 'FBYT':
		// Byte fill (with 0)
		if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
			mRezStream->SetMarker(1, streamFrom_Marker);
		} 
		break;

		case 'FLNG':
		// Long fill (with 0)
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 3) {
			mRezStream->SetMarker(4, streamFrom_Marker);
		} 
		break;

		case 'FWRD':
		// Word fill (with 0)
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 1) {
			mRezStream->SetMarker(2, streamFrom_Marker);
		} 
		break;

		case 'HBYT':
		// Hex byte
		if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
			*mRezStream >> theChar;
		} 
		sprintf(charString, "$%.2x%c", theChar, NULL);
		CopyCStringToPascal(charString, theString);
		AddStaticField(inLabelString, inContainer);
		AddEditField(theString, inType, 2, 0, 
					 &UHexFilters::HexadecimalField, inContainer);
		break;

		case 'HEXD':
		// Hex dump of remaining bytes in resource (this can only be the last type in a resource)
		AddStaticField(inLabelString, inContainer, mLeftLabelTraitsID);
		mYCoord += kTmplLabelHeight + kTmplVertSkip;
		AddHexDumpField(inType, inContainer);
		break;

		case 'HLNG':
		// Hex long word
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 3) {
			*mRezStream >> theUInt32;
		} 
		sprintf(charString, "$%.8x%c", theUInt32, NULL);
		CopyCStringToPascal(charString, theString);
		AddStaticField(inLabelString, inContainer);
		AddEditField(theString, inType, 8, 0, 
					 &UHexFilters::HexadecimalField, inContainer);
		break;

		case 'HWRD':
		// Hex word
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 1) {
			*mRezStream >> theUInt16;
		} 
		sprintf(charString, "$%.4x%c", theUInt16, NULL);
		CopyCStringToPascal(charString, theString);
		AddStaticField(inLabelString, inContainer);
		AddEditField(theString, inType, 4, 0, 
					 &UHexFilters::HexadecimalField, inContainer);
		break;

		case 'LSTB':
		// List Begin. Ends at the end of the resource.
		break;

		case 'LSTC':
		// List Count. Terminated by a zero-based word count that starts 
		// the sequence (as in 'DITL' resources).
		break;

		case 'LSTE':
		// List end. Handled in DoParseWithTemplate().
		break;

		case 'LSTR':
		// Long string (length long followed by the characters)
		AddStaticField(inLabelString, inContainer, mLeftLabelTraitsID);
		mYCoord += kTmplLabelHeight + kTmplVertSkip;
		AddWasteField(inType, inContainer);
		break;

		case 'LSTZ':
		// List Zero. Terminated by a 0 byte (as in 'MENU' resources).
		break;
		
		case 'OCNT':
		// One Count. Terminated by a one-based word count that starts 
		// the sequence (as in 'STR#' resources).
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 1) {
			*mRezStream >> theUInt16;
		} 
		mItemsCount = theUInt16;
		break;

		case 'OCST':
		// Odd-padded C string (padded with nulls)
		AddStaticField(inLabelString, inContainer, mLeftLabelTraitsID);
		mYCoord += kTmplLabelHeight + kTmplVertSkip;
		// Padding is handled there
		AddWasteField(inType, inContainer);
		break;

		case 'OSTR':
		// Pascal string padded to odd length (needed for DITL resources)
		if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
			*mRezStream >> theString;
			theLength = theString[0];
			if (theLength % 2) {
				// if the length is odd, the string has been padded. So skip the next char.
				if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
					*mRezStream >> theChar;
				}
			} 
		} else {
			theString[0] = 0;
		}
		AddStaticField(inLabelString, inContainer);
		AddEditField(theString, inType, 255, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_PrintingChar), inContainer);
		break;

		case 'PSTR':
		// Pascal string
		if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
			*mRezStream >> theString;
		} else {
			theString[0] = 0;
		}
		AddStaticField(inLabelString, inContainer);
		AddEditField(theString, inType, 255, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_PrintingChar), inContainer);
		break;

		case 'RECT': {
			// An 8-byte rectangle
			SInt16 theTop = 0, theLeft = 0, theBottom = 0, theRight = 0;
			if (mRezStream->GetMarker() < mRezStream->GetLength() - 7) {
				*mRezStream >> theTop;
				*mRezStream >> theLeft;
				*mRezStream >> theBottom;
				*mRezStream >> theRight;
			} 
			mYCoord += kTmplRectVertSkip;
			AddStaticField(inLabelString, inContainer);
			mYCoord -= kTmplRectVertSkip;
			AddRectField(theTop, theLeft, theBottom, theRight, inType, 5, 0, 
						 UKeyFilters::SelectTEKeyFilter(keyFilter_Integer), inContainer);
			break;
		}

		case 'TNAM':
		// Type name (four characters, like OSType and ResType)
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 3) {
			*mRezStream >> theOSType;
			UMiscUtils::OSTypeToPString(theOSType, theString);
		} else {
			theString[0] = 0;
		}
		AddStaticField(inLabelString, inContainer);
		AddEditField(theString, inType, 4, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_PrintingChar), inContainer);
		break;

		case 'WSTR':
		// Same as LSTR, but a word rather than a long word
		AddStaticField(inLabelString, inContainer, mLeftLabelTraitsID);
		mYCoord += kTmplLabelHeight + kTmplVertSkip;
		AddWasteField(inType, inContainer);
 		break;

		case 'ZCNT':
		// Zero Count. Terminated by a zero-based word count that starts 
		// the sequence (as in 'DITL' resources).
		if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
			*mRezStream >> theUInt16;
			mItemsCount = theUInt16 + 1;
		} else {
			mItemsCount = 0;
		}
		break;

	  default:
	  // Handle Hnnn, Cnnn, P0nn cases here or unrecognized type
	  if (inType >> 24 == 'H') {
		  // Hnnn A 3-digit hex number; displays nnn bytes in hex format
		  // 0xfff = 4095
		  AddStaticField(inLabelString, inContainer, mLeftLabelTraitsID);
		  mYCoord += kTmplLabelHeight + kTmplVertSkip;
		  AddHexDumpField(inType, inContainer);
	  } else if (inType >> 24 == 'C') {
		  // Cnnn A C string that is nnn hex bytes long (The last byte is always a 0, so the string itself occupies the first nnn-1 bytes.)
		  AddStaticField(inLabelString, inContainer, mLeftLabelTraitsID);
		  mYCoord += kTmplLabelHeight + kTmplVertSkip;
		  AddWasteField(inType, inContainer);
	  } else if ( inType >> 16 == 'P0') {
		  SInt32 length = 255;
		  Str255 numStr;
		  // P0nn A Pascal string that is nn hex bytes long (The length byte is not included in nn, so the string occupies the entire specified length.)
		  if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
			  SInt32 length;
			  char str[3];
			  char * p = (char*) &inType;
			  sprintf(str, "%c%c%c", *(p+2), *(p+3), 0);
			  sscanf(str, "%2x", &length);

			  *mRezStream >> theString;
			  if (theString[0] > length) {
				  theString[0] = length;
			  } 
		  } else {
			theString[0] = 0;
		}
		AddStaticField(inLabelString, inContainer);
		AddEditField(theString, inType, length, 0, 
					   UKeyFilters::SelectTEKeyFilter(keyFilter_PrintingChar), inContainer);	  	
	  } else {
		  // Unrecognized type
		  UMessageDialogs::AlertForType(CFSTR("UnknownTemplateType"), inType);
	  }
	  break;
	}

	return error;
}


#pragma mark -

// ---------------------------------------------------------------------------
//	¥ AddStaticField													[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddStaticField(Str255 inLabel, LView * inContainer, ResIDT inTextTraitsID)
{
	mStaticPaneInfo.left		= kTmplLeftMargin;
	mStaticPaneInfo.top			= mYCoord;
	mStaticPaneInfo.width		= kTmplLabelWidth;
	mStaticPaneInfo.superView	= inContainer;

	LStaticText * theStaticText = new LStaticText(mStaticPaneInfo, inLabel, inTextTraitsID);
	ThrowIfNil_(theStaticText);
}


// ---------------------------------------------------------------------------
//	¥ AddEditField														[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddEditField(Str255 inValue, 
								OSType inType,
								SInt16 inMaxChars, 
								UInt8 inAttributes,
								TEKeyFilterFunc inKeyFilter, 
								LView * inContainer)
{
	SDimension16	theFrame;
	inContainer->GetFrameSize(theFrame);

	mEditPaneInfo.left		= kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep;
	mEditPaneInfo.width		= theFrame.width - kTmplLeftMargin * 2 - kTmplLabelWidth - kTmplHorizSep - kTmplHorizSkip;
	mEditPaneInfo.top		= mYCoord - 3;
	mEditPaneInfo.paneID	= mCurrentID;
	mEditPaneInfo.superView	= inContainer;

	LEditText * theEditText = new LEditText(mEditPaneInfo, this, inValue, mEditTraitsID, 
											msg_TmplModified, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);

	// Store the template's type in the userCon field
	theEditText->SetUserCon(inType);
	
	// Advance the counters
	mYCoord += mEditPaneInfo.height + kTmplVertSep;
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//	¥ AddBooleanField											[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddBooleanField(Boolean inValue,
								   OSType inType,
								   SInt16 inTitleType, 
								   LView * inContainer)
{
	LStdRadioButton * theRadio;
	SViewInfo	theViewInfo;
	theViewInfo.imageSize.width		= theViewInfo.imageSize.height	= 0 ;
	theViewInfo.scrollPos.h			= theViewInfo.scrollPos.v		= 0;
	theViewInfo.scrollUnit.h		= theViewInfo.scrollUnit.v		= 1;
	theViewInfo.reconcileOverhang	= false;
	
	mRgvPaneInfo.left		= kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep;
	mRgvPaneInfo.top		= mYCoord - 2;
	mRgvPaneInfo.paneID		= mCurrentID;
	mRgvPaneInfo.superView	= inContainer;

	LRadioGroupView * theRGV = new LRadioGroupView(mRgvPaneInfo, theViewInfo);
	ThrowIfNil_(theRGV);

	// Store the template's type in the userCon field
	theRGV->SetUserCon(inType);
	
	mCurrentID++;

	// Create two radiobuttons in this group
	//     "Yes/On" radiobutton
	mRadioPaneInfo.left			= 0;
	mRadioPaneInfo.top			= 0;
	mRadioPaneInfo.paneID		= mCurrentID;
	mRadioPaneInfo.superView	= theRGV;

	theRadio = new LStdRadioButton(mRadioPaneInfo, msg_TmplModified, 
								   inValue, mLeftLabelTraitsID, (UInt8 *)(inTitleType ? "\pOn":"\pYes"));
	ThrowIfNil_(theRadio);
	
	theRGV->AddRadio(theRadio);
	
	mCurrentID++;

	//     "No/Off" radiobutton
	mRadioPaneInfo.left += kTmplRadioWidth + kTmplHorizSep;
	mRadioPaneInfo.paneID = mCurrentID;

	theRadio = new LStdRadioButton(mRadioPaneInfo, msg_TmplModified, 
								   1 - inValue, mLeftLabelTraitsID, (UInt8 *)(inTitleType ? "\pOff":"\pNo"));
	ThrowIfNil_(theRadio);
	
	theRGV->AddRadio(theRadio);

	theRGV->SetCurrentRadioID( inValue ?  mCurrentID - 1 : mCurrentID );
	
	// Advance the counters
	mYCoord += mRgvPaneInfo.height + kTmplVertSep;
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//	¥ AddCheckField											[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddCheckField(Boolean inValue,
								   OSType inType,
								   LView * inContainer)
{
	mCheckPaneInfo.left			= kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep;;
	mCheckPaneInfo.top			= mYCoord - 2;
	mCheckPaneInfo.paneID		= mCurrentID;
	mCheckPaneInfo.superView	= inContainer;

	LCheckBox * theCheck = new LCheckBox(mCheckPaneInfo, msg_TmplModified, inValue);
	ThrowIfNil_(theCheck);
		
	// Advance the counters
	mYCoord += mCheckPaneInfo.height + kTmplVertSep;
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//	¥ AddWasteField													[public]
// ---------------------------------------------------------------------------
// C string. This should be either characters followed by a null or all
// the chars until the end of the stream if there is no null byte.
// LTextGroupBox::LTextGroupBox(
// 	const SPaneInfo&	inPaneInfo,
// 	const SViewInfo&	inViewInfo,
// 	Boolean				inPrimary,
// 	ResIDT				inTextTraitsID,
// 	ConstStringPtr		inTitle,
// 	ClassIDT			inImpID)

void
CTmplEditorWindow::AddWasteField(OSType inType, LView * inContainer)
{
	SInt32		oldPos, newPos, maxPos, theLength;
	Handle		theHandle;
	char 		theChar;
	SViewInfo	theViewInfo;
	SDimension16	theFrame;
	
	inContainer->GetFrameSize(theFrame);

	theViewInfo.imageSize.width		= theViewInfo.imageSize.height	= 0 ;
	theViewInfo.scrollPos.h			= theViewInfo.scrollPos.v		= 0;
	theViewInfo.scrollUnit.h		= theViewInfo.scrollUnit.v		= 1;
	theViewInfo.reconcileOverhang	= false;
	
	mTgbPaneInfo.paneID				= 0;
	mTgbPaneInfo.top				= mYCoord;
	mTgbPaneInfo.left				= kTmplTextMargin;
	mTgbPaneInfo.width				= theFrame.width - kTmplTextMargin * 2;
	mTgbPaneInfo.superView			= inContainer;

	LTextGroupBox * theTGB = new LTextGroupBox(mTgbPaneInfo, theViewInfo, false);
	ThrowIfNil_(theTGB);

	mScrollPaneInfo.left			= kTmplTextInset;
	mScrollPaneInfo.top				= kTmplTextInset;
	mScrollPaneInfo.width			= mTgbPaneInfo.width - kTmplTextInset * 2;
	mScrollPaneInfo.height			= mTgbPaneInfo.height - kTmplTextInset * 2;
	mScrollPaneInfo.bindings.left	= true;
	mScrollPaneInfo.paneID			= 0;
	mScrollPaneInfo.superView		= theTGB;

	LScrollerView * theScroller = new LScrollerView(mScrollPaneInfo, theViewInfo, 0, 15, 0, 15, 16, NULL, true);
	ThrowIfNil_(theScroller);

	mWastePaneInfo.left				= 0;
	mWastePaneInfo.top				= 0;
	mWastePaneInfo.width			= mScrollPaneInfo.width - 15;
	mWastePaneInfo.height			= mScrollPaneInfo.height - 15;
	mWastePaneInfo.paneID			= mCurrentID;
	mWastePaneInfo.superView		= theScroller;

	// Make the Waste edit writable, not wrapping, selectable
	CWasteEditView * theWasteEdit = new CWasteEditView(mWastePaneInfo, theViewInfo, 0, mEditTraitsID);
	ThrowIfNil_(theWasteEdit);

	theScroller->InstallView(theWasteEdit);
	
	// Store the template's type in the userCon field
	theWasteEdit->SetUserCon(inType);
	theLength = mRezStream->GetLength();
	
	// Insert the text
	oldPos = mRezStream->GetMarker();
	switch (inType) {
		case 'CSTR':
			// Is there a NULL byte marking the end of the string?
			newPos = theLength;
			while (mRezStream->GetMarker() < theLength ) {
				*mRezStream >> theChar;
				if (theChar == 0) {
					// Don't take the ending NULL
					newPos = mRezStream->GetMarker() - 1;
					break;
				} 
			}
		break;

		case 'LSTR': {
			UInt32		theUInt32 = 0;
			// Long string (length long followed by the characters)
			if (mRezStream->GetMarker() < theLength - 3) {
				*mRezStream >> theUInt32;
			}
			oldPos += 4;
			newPos = oldPos + theUInt32;
			break;
		}
		
		case 'WSTR': {
			UInt16		theUInt16 = 0;
			// Same as LSTR, but a word rather than a long word
			if (mRezStream->GetMarker() < theLength - 1) {
				*mRezStream >> theUInt16;
			}
			oldPos += 2;
			newPos = oldPos + theUInt16;
			break;
		}

		case 'ECST':
		case 'OCST':
			// Is there a NULL byte marking the end of the string?
			newPos = theLength;
			while (mRezStream->GetMarker() < theLength ) {
				*mRezStream >> theChar;
				if (theChar == 0) {
					newPos = mRezStream->GetMarker();
					// If the total length, including ending NULL, is odd
					// (with ESTR) or even (with OSTR), the string is padded, 
					// so skip one byte.
					if ( (newPos < theLength) && ( 
						   ( (newPos - oldPos) % 2 && (inType = 'ECST') ) 
						   ||
						   ( (newPos - oldPos) % 2 == 0 && (inType = 'OCST') ) )) {
					   // Skip one byte.
					   if (mRezStream->GetMarker() < theLength ) {
						   *mRezStream >> theChar;
					   }
					} 
					// Don't take the ending NULL
					newPos--;
					break;
				} 
			}
		break;

		default:
		if (inType >> 24 == 'C') {
			// Cnnn: a C string that is nnn hex bytes long (The last byte is always a 0, 
			// so the string itself occupies the first nnn-1 bytes.)
			SInt32 length;
			char str[4];
			char * p = (char*) &inType;
			sprintf(str, "%c%c%c%c", *(p+1), *(p+2), *(p+3), 0);
			sscanf(str, "%3x", &length);

			maxPos = oldPos + length;
			newPos = maxPos - 1;
			// Look for a NULL byte in this range
			while (mRezStream->GetMarker() <= maxPos ) {
				*mRezStream >> theChar;
				if (theChar == 0) {
					newPos = mRezStream->GetMarker() - 1;
					mRezStream->SetMarker(maxPos, streamFrom_Start);
					break;
				}
			}
// 			// Skip the ending byte
// 			if (mRezStream->GetMarker() < theLength ) {
// 				*mRezStream >> theChar;
// 			}
		}
	}

	if (oldPos > theLength) {
		oldPos = theLength;
	} 
	if (newPos > theLength) {
		newPos = theLength;
	} 
	if (newPos < oldPos) {
		newPos = oldPos;
	} 
	
	theHandle = mRezStream->GetDataHandle();
	HLock(theHandle);
	theWasteEdit->Insert( (*theHandle) + oldPos , newPos - oldPos, NULL, true);
	HUnlock(theHandle);
	
	// Advance the counters
	mYCoord += mTgbPaneInfo.height + kTmplVertSep;
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//	¥ AddHexDumpField													[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddHexDumpField(OSType inType, LView * inContainer)
{
	SInt32		oldPos, newPos, theLength;
	Handle		theHandle;
	SViewInfo	theViewInfo;
	SDimension16	theFrame;

	inContainer->GetFrameSize(theFrame);
	mOwnerDoc = dynamic_cast<CTmplEditorDoc*>(GetSuperCommander());

	theViewInfo.imageSize.width		= theViewInfo.imageSize.height	= 0 ;
	theViewInfo.scrollPos.h			= theViewInfo.scrollPos.v		= 0;
	theViewInfo.scrollUnit.h		= theViewInfo.scrollUnit.v		= 1;
	theViewInfo.reconcileOverhang	= false;
	
	mTgbPaneInfo.top				= mYCoord;
	mTgbPaneInfo.left				= kTmplTextMargin;
	mTgbPaneInfo.width				= theFrame.width - kTmplTextMargin * 2;
	mTgbPaneInfo.paneID				= mCurrentID;
	mTgbPaneInfo.superView			= inContainer;
	CDualDataView * theTGB = new CDualDataView(mTgbPaneInfo, theViewInfo, false);
	ThrowIfNil_(theTGB);

	// Make the single vertical scroll bar
	mScrollPaneInfo.left			= mTgbPaneInfo.width - kTmplTextInset - kTmplScrollWidth;
	mScrollPaneInfo.top				= kTmplTextInset;
	mScrollPaneInfo.width			= kTmplScrollWidth;
	mScrollPaneInfo.height			= mTgbPaneInfo.height - kTmplTextInset * 2;
	mScrollPaneInfo.bindings.left	= false;
	mScrollPaneInfo.paneID			= 0;
	mScrollPaneInfo.superView		= theTGB;

	CSingleScrollBar * theScroller = new CSingleScrollBar(mScrollPaneInfo, 'HScr', 0, 0, 0, true);
	ThrowIfNil_(theScroller);

	// Make the Waste edit panes (no wrapping, selectable). The read only
	// property is set by InstallSubViews() below.
	mWastePaneInfo.left				= kTmplTextInset;
	mWastePaneInfo.top				= kTmplTextInset;
	mWastePaneInfo.width			= kTmplHexPaneWidth;
	mWastePaneInfo.height			= mScrollPaneInfo.height;
	mWastePaneInfo.paneID			= 0;
	mWastePaneInfo.superView		= theTGB;

	CHexDataSubView * theHexWE = new CHexDataSubView(mWastePaneInfo, theViewInfo, 0, mEditTraitsID);
	ThrowIfNil_(theHexWE);

	mWastePaneInfo.left				= kTmplTxtPaneLeft;
	mWastePaneInfo.width			= kTmplTxtPaneWidth;
	
	CTxtDataSubView * theTxtWE = new CTxtDataSubView(mWastePaneInfo, theViewInfo, 0, mEditTraitsID);
	ThrowIfNil_(theTxtWE);
	
	// Install the subpanes and the scroller in the dual view
	theTGB->InstallSubViews(theHexWE, theTxtWE, theScroller, mOwnerDoc->IsReadOnly() );

	// Adjust to the style specified in the preferences
	TextTraitsRecord theTraits = CRezillaApp::sPrefs->GetStyleElement( CRezillaPrefs::prefsType_Curr );
	theTGB->ResizeDataPanes();
	theTGB->UpdatePaneCounts();
	theHexWE->ApplyStyleValues( theTraits.size, theTraits.fontNumber);
	theTxtWE->ApplyStyleValues( theTraits.size, theTraits.fontNumber);
	
	// Store the template's type in the userCon field
	theTGB->SetUserCon(inType);
	
	// Insert the text
	theLength = mRezStream->GetLength();
	oldPos = mRezStream->GetMarker();
	if (inType == 'HEXD') {
		newPos = theLength;
	} else if (inType >> 24 == 'H') {
	  // Hnnn: a 3-digit hex number; displays nnn bytes in hex format
		SInt32 length;
		char str[4];
		char * p = (char*) &inType;
		sprintf(str, "%c%c%c%c", *(p+1), *(p+2), *(p+3), 0);
		sscanf(str, "%3x", &length);
		newPos = oldPos + length;
	}
	
	if (oldPos > theLength) {
		oldPos = theLength;
	} 
	if (newPos > theLength) {
		newPos = theLength;
	} 
	if (newPos < oldPos) {
		newPos = oldPos;
	} 
	
	theHandle = mRezStream->GetDataHandle();
	HLock(theHandle);
	theTGB->InstallBackStoreData((*theHandle) + oldPos , newPos - oldPos);
	theTGB->SetMaxScrollerValue();
	theTGB->InstallContentsFromLine(1);
	HUnlock(theHandle);

	WESetSelection(0, 0, theTGB->GetInMemoryWasteRef());
	
	// Advance the counters
	mYCoord += mTgbPaneInfo.height + kTmplVertSep;
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//	¥ AddRectField													[public]
// ---------------------------------------------------------------------------
// Rectangle text group box basic values

void
CTmplEditorWindow::AddRectField(SInt16 inTop, 
								SInt16 inLeft, 
								SInt16 inBottom, 
								SInt16 inRight, 
								OSType inType,
								SInt16 inMaxChars, 
								UInt8 inAttributes,
								TEKeyFilterFunc inKeyFilter,
								LView * inContainer)
{
	Str255	numStr;
	LEditText * theEditText;
	LStaticText * theStaticText;
	SViewInfo	theViewInfo;
	theViewInfo.imageSize.width		= theViewInfo.imageSize.height	= 0 ;
	theViewInfo.scrollPos.h			= theViewInfo.scrollPos.v		= 0;
	theViewInfo.scrollUnit.h		= theViewInfo.scrollUnit.v		= 1;
	theViewInfo.reconcileOverhang	= false;

	mRectLabelInfo.top			= mYCoord;
	mRectLabelInfo.left 		= kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep;
	mRectLabelInfo.superView	= inContainer;

	mRectPaneInfo.top		= mYCoord + kTmplRectHeight;
	mRectPaneInfo.left		= mRectLabelInfo.left;
	mRectPaneInfo.superView	= inContainer;

	// Top
	theStaticText = new LStaticText(mRectLabelInfo, "\pTop", mEditTraitsID);
	ThrowIfNil_(theStaticText);
	mRectPaneInfo.paneID = mCurrentID;
	::NumToString( (long) inTop, numStr);
	theEditText = new LEditText(mRectPaneInfo, this, numStr, mEditTraitsID, 
								msg_TmplModified, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);
	theEditText->SetUserCon(inType);
	mCurrentID++;

	// Left
	mRectLabelInfo.left += kTmplRectWidth + kTmplHorizSep;
	theStaticText = new LStaticText(mRectLabelInfo, "\pLeft", mEditTraitsID);
	ThrowIfNil_(theStaticText);
	mRectPaneInfo.left += kTmplRectWidth + kTmplHorizSep;
	mRectPaneInfo.paneID = mCurrentID;
	::NumToString( (long) inLeft, numStr);
	theEditText = new LEditText(mRectPaneInfo, this, numStr, mEditTraitsID, 
								msg_TmplModified, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);
	theEditText->SetUserCon(inType);
	mCurrentID++;

	// Bottom
	mRectLabelInfo.left += kTmplRectWidth + kTmplHorizSep;
	theStaticText = new LStaticText(mRectLabelInfo, "\pBottom", mEditTraitsID);
	ThrowIfNil_(theStaticText);
	mRectPaneInfo.left += kTmplRectWidth + kTmplHorizSep;
	mRectPaneInfo.paneID = mCurrentID;
	::NumToString( (long) inBottom, numStr);
	theEditText = new LEditText(mRectPaneInfo, this, numStr, mEditTraitsID, 
								msg_TmplModified, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);
	theEditText->SetUserCon(inType);
	mCurrentID++;

	// Right
	mRectLabelInfo.left += kTmplRectWidth + kTmplHorizSep;
	theStaticText = new LStaticText(mRectLabelInfo, "\pRight", mEditTraitsID);
	ThrowIfNil_(theStaticText);
	mRectPaneInfo.left += kTmplRectWidth + kTmplHorizSep;
	mRectPaneInfo.paneID = mCurrentID;
	::NumToString( (long) inRight, numStr);
	theEditText = new LEditText(mRectPaneInfo, this, numStr, mEditTraitsID, 
								msg_TmplModified, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);
	theEditText->SetUserCon(inType);
	mCurrentID++;

	// Advance the counters
	mYCoord += (kTmplRectHeight * 2) + kTmplVertSep + kTmplVertSep;
}


// ---------------------------------------------------------------------------
//	¥ AddListHeaderField											[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddListHeaderField(OSType inType, Str255 inLabel, short inCount, Str255 inCountLabel, LView * inContainer)
{
	Str255			numStr;
	LStaticText *	theStaticText;
	CTmplListButton *	thePushButton;
	
	// This is the label of the list (usually "*****")
	mStaticPaneInfo.left		= kTmplLeftMargin;
	mStaticPaneInfo.top			= mYCoord;
	mStaticPaneInfo.width		= kTmplLabelWidth;
	mStaticPaneInfo.superView	= inContainer;

	theStaticText = new LStaticText(mStaticPaneInfo, inLabel, mHeaderTraitsID);
	ThrowIfNil_(theStaticText);

	if (inType == 'LSTC') {
		mYCoord += kTmplEditHeight;
		// This is the label of the OCNT or ZCNT count
// 		mStaticPaneInfo.left 	= mIndent;
		mStaticPaneInfo.top		= mYCoord;
		mStaticPaneInfo.width	= kTmplLabelWidth;
		theStaticText = new LStaticText(mStaticPaneInfo, inCountLabel, mRightLabelTraitsID);
		ThrowIfNil_(theStaticText);
		
		// This is the value of the OCNT or ZCNT count
		mStaticPaneInfo.left 	+= mStaticPaneInfo.width + kTmplHorizSep;
		mStaticPaneInfo.width	= kTmplCountWidth;
		mStaticPaneInfo.paneID 	= mCurrentID;
		::NumToString( (long) inCount, numStr);
		theStaticText = new LStaticText(mStaticPaneInfo, numStr, mHeaderTraitsID);
		ThrowIfNil_(theStaticText);
		
		mStaticPaneInfo.paneID = 0;
		mCurrentID++;
	}
	
	mPushPaneInfo.top		= mStaticPaneInfo.top - 3;
	mPushPaneInfo.left		= mStaticPaneInfo.left + mStaticPaneInfo.width + kTmplHorizSep;
	mPushPaneInfo.paneID	= mCurrentID;
	mPushPaneInfo.superView	= inContainer;
	
	thePushButton = new CTmplListButton(mPushPaneInfo, msg_TmplMinusButton, "\p-");
	ThrowIfNil_(thePushButton);
	// Store the current position in the template stream
	thePushButton->SetUserCon( mTemplateStream->GetMarker());
	// Let the window listen to this button
	thePushButton->AddListener(this);

	mCurrentID++;
	
	mPushPaneInfo.left		+= kTmplCountWidth + kTmplHorizSep;
	mPushPaneInfo.paneID	= mCurrentID;
	thePushButton = new CTmplListButton(mPushPaneInfo, msg_TmplPlusButton, "\p+");
	ThrowIfNil_(thePushButton);
	// The UserCon field will contain a pointer to the first ListItemView. Initialize with nil.
	thePushButton->SetUserCon(nil);
	// Let the window listen to this button
	thePushButton->AddListener(this);

	mCurrentID++;

	// Advance the counters
	mYCoord += mStaticPaneInfo.height + kTmplVertSep + kTmplVertSkip;
}
 

// ---------------------------------------------------------------------------
//	¥ AddListItemView											[public]
// ---------------------------------------------------------------------------

CTmplListItemView *
CTmplEditorWindow::AddListItemView(CTmplListItemView * inPrevListItemView, LView * inContainer)
{
	SDimension16	theFrame;
	
	SViewInfo	theViewInfo;
	theViewInfo.imageSize.width		= theViewInfo.imageSize.height	= 0 ;
	theViewInfo.scrollPos.h			= theViewInfo.scrollPos.v		= 0;
	theViewInfo.scrollUnit.h		= theViewInfo.scrollUnit.v		= 1;
	theViewInfo.reconcileOverhang	= false;
	
	inContainer->GetFrameSize(theFrame);

	mListItemInfo.paneID			= 0;
	mListItemInfo.top				= mYCoord;
	mListItemInfo.left				= kTmplTextMargin + mIndent;
	mListItemInfo.width				= theFrame.width - mListItemInfo.left - kTmplHorizSep;
	mListItemInfo.superView			= inContainer;
	
	CTmplListItemView * theLIV = new CTmplListItemView(mListItemInfo, theViewInfo, false);
	ThrowIfNil_(theLIV);

	theLIV->mPrevItem = inPrevListItemView;
	if (inPrevListItemView != nil) {
		inPrevListItemView->mNextItem = theLIV;
	} 

	theLIV->mFirstItemID = mCurrentID;

	return theLIV;
}


// ---------------------------------------------------------------------------
//	¥ AddSeparatorLine											[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddSeparatorLine(LView * inContainer)
{
	SDimension16	theFrame;

	inContainer->GetFrameSize(theFrame);
	mSeparatorPaneInfo.left			= kTmplLabelWidth + kTmplLeftMargin;
	mSeparatorPaneInfo.top			= mYCoord;
	mSeparatorPaneInfo.width		= theFrame.width - kTmplLabelWidth - kTmplLeftMargin * 2;
	mSeparatorPaneInfo.superView	= inContainer;

	LSeparatorLine * theSeparator = new LSeparatorLine(mSeparatorPaneInfo);
	ThrowIfNil_(theSeparator);
	
	// Advance the counters
	mYCoord += mSeparatorPaneInfo.height + kTmplVertSep;
}


// ---------------------------------------------------------------------------
//	¥ AddPopupField													[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddPopupField(ResType inType, Str255 inLabel, LView * inContainer)
{
	register char *	p;
	SDimension16	theFrame;
	SInt16			index = 1;
	ResType			theType;
	SInt32			currMark, theLength = mTemplateStream->GetLength();
	Str255			theString;
	char 			charString[256];

	inContainer->GetFrameSize(theFrame);
	mBevelPaneInfo.left			= theFrame.width - mBevelPaneInfo.width - 2;
	mBevelPaneInfo.top			= mYCoord - mEditPaneInfo.height -kTmplVertSep -1;
	mSeparatorPaneInfo.paneID	= mCurrentID;
	mBevelPaneInfo.superView	= inContainer;

	CTmplBevelButton * theBevelButton = new CTmplBevelButton(mBevelPaneInfo, msg_TmplCasePopup, kControlBevelButtonSmallBevelProc,
													 rMENU_TemplateCases, kControlBevelButtonMenuOnBottom, 
													 kControlContentTextOnly, 0, 0, Str_Empty, 1, 
													 kControlBevelButtonPlaceNormally, teFlushDefault, 0, 
													 kControlBevelButtonAlignCenter, Point_00, true);													 
	ThrowIfNil_(theBevelButton);

	// Populate the popup with all the successive cases
	CopyPascalStringToC(inLabel, charString);
	p = strrchr((char *) charString, '=');
	if (p != nil) {
		inLabel[0] = p - (char *) charString;
		theBevelButton->InsertMenuItem(inLabel, index, true);
	} 
	currMark = mTemplateStream->GetMarker();
	while (currMark < theLength) {
		*mTemplateStream >> theString;
		*mTemplateStream >> theType;
		if (theType != inType) {
			// We went too far. Reposition the stream marker.
			mTemplateStream->SetMarker(currMark, streamFrom_Start);
			break;
		} 
		currMark = mTemplateStream->GetMarker();
		index++;
		CopyPascalStringToC(theString, charString);
		p = strrchr((char *) charString, '=');
		if (p != nil) {
			theString[0] = p - (char *) charString;
			theBevelButton->InsertMenuItem(theString, index, true);
		} 
	}
	
	// Store a pointer to the associated edit field
	LEditText * theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID - 1));
	theBevelButton->SetUserCon( (long) theEditText);
	
	// Advance the counters. mYCoord has already been increased by the edit field
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//	¥ AlignBytesRead											[public]
// ---------------------------------------------------------------------------

ExceptionCode
CTmplEditorWindow::AlignBytesRead(UInt8 inStep)
{
	ExceptionCode	err = noErr;
	
	SInt32 theSInt32 = mRezStream->GetMarker();
	SInt32 theRest = theSInt32 % inStep;

	if (theRest != 0) {
		if (theSInt32 + theRest > mRezStream->GetLength()) {
			err = writErr;
		} else {
			mRezStream->SetMarker(theRest, streamFrom_Marker);
		}
	}
	
	return err;
}


// ---------------------------------------------------------------------------
//	¥ AlignBytesWrite											[public]
// ---------------------------------------------------------------------------

ExceptionCode
CTmplEditorWindow::AlignBytesWrite(UInt8 inStep)
{
	ExceptionCode	err = noErr;
	
	SInt32 theSInt32 = mOutStream->GetMarker();
	SInt32 theRest = theSInt32 % inStep;

	if (theRest != 0) {	
		for (UInt8 i = theRest; i < 4; i++) {
				*mOutStream << (UInt8) 0x00;
			}
		}
	
	return err;
}


#pragma mark -

// ---------------------------------------------------------------------------
//	¥ RetrieveDataWithTemplate								[public]
// ---------------------------------------------------------------------------

Handle
CTmplEditorWindow::RetrieveDataWithTemplate()
{
	if (mOutStream != nil) {
		delete mOutStream;
	} 
	mOutStream = new LHandleStream();
	mCurrentID = 1;

	mItemsCount = 0;
	
	// Parse the template stream
	DoRetrieveWithTemplate(0);
	
	return mOutStream->GetDataHandle();
}


// // 	//	Dissociate the data Handle from a HandleStream.
// // 	//
// // 	//	Creates a new, empty data Handle and passes back the existing Handle.
// // 	//	Caller assumes ownership of the Handle.
// // 
// // 	Handle
// // 	LHandleStream::DetachDataHandle()


// ---------------------------------------------------------------------------
//	¥ DoRetrieveWithTemplate													[public]
// ---------------------------------------------------------------------------
// // // SInt32
// // // LPane::GetUserCon() const
// // // GetPaneID()

void
CTmplEditorWindow::DoRetrieveWithTemplate(SInt32 inRecursionMark)
{
	Str255		theString;
	ResType		theType;
	
	mTemplateStream->SetMarker(inRecursionMark, streamFrom_Start);

	while (mTemplateStream->GetMarker() < mTemplateStream->GetLength() ) {
		*mTemplateStream >> theString;
		*mTemplateStream >> theType;
		
		if (theType == 'OCNT' || theType == 'ZCNT') {
			RetrieveDataForType(theType);
		} else if (theType == 'LSTB' || theType == 'LSTC' || theType == 'LSTZ') {
			// Skip the Plus and Minus buttons
			mCurrentID += 2;
			RetrieveList(mTemplateStream->GetMarker(), theType, mItemsCount);
		} else if (theType == 'LSTE') {
			break;
		} else {
			// Create controls according to the type declared in the template
			RetrieveDataForType(theType);
		}
	}
}


// ---------------------------------------------------------------------------
//	¥ RetrieveList													[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::RetrieveList(SInt32 inStartMark, ResType inType, SInt32 inCount)
{
	switch (inType) {
		case 'LSTB':
		case 'LSTZ':
		do {
			DoRetrieveWithTemplate(inStartMark);
		} while (mCurrentID < mLastID);
		break;
		
		case 'LSTC':
		if (inCount != 0) {
			mItemsCount = 0;
			for (short i = 0 ; i < inCount; i++) {
				DoRetrieveWithTemplate(inStartMark);
			}
		}
		break;
		
	}
}


// ---------------------------------------------------------------------------
//	¥ RetrieveDataForType												[public]
// ---------------------------------------------------------------------------


OSErr
CTmplEditorWindow::RetrieveDataForType(ResType inType)
{
	OSErr	error = noErr;
	char	theChar = 0;
	char 	charString[256];
	long	theLong;
	Str255	numStr, theString;
	SInt32	theLength, reqLength;
	UInt16	theUInt16 = 0;
	UInt32	theUInt32 = 0;
	OSType	theOSType;
	SInt8	i;	
	LRadioGroupView *	theRGV;
	LStaticText	*		theStaticText;
	LEditText *			theEditText;
	LCheckBox *			theCheckBox;
	CWasteEditView *	theWasteEdit;
	PaneIDT			theCurrentRadioID;
	Handle			theHandle;
	StHandleLocker	locker(nil);
	CFStringRef		formatStr = NULL, messageStr = NULL;

	switch (inType) {
		case 'ALNG':
		// Long align
		AlignBytesWrite(4);
		break;

		case 'AWRD':
		// Word align
		AlignBytesWrite(2);
		break;

		case 'BBIT':
		// Binary bit (there must be 8 or an even multiple of 8 of these).
		theCheckBox = dynamic_cast<LCheckBox *>(this->FindPaneByID(mCurrentID));
		theChar |= theCheckBox->GetValue() ? 1<<7 : 0 ;
		mCurrentID++;
		// Consume similarly the next 7 controls in the template
		for (i = 6; i >= 0 ; i--) {
			*mTemplateStream >> theString;
			*mTemplateStream >> theOSType;
			
			theCheckBox = dynamic_cast<LCheckBox *>(this->FindPaneByID(mCurrentID));
			theChar |= theCheckBox->GetValue() ? 1<<i : 0 ;
			mCurrentID++;
		}
		*mOutStream << theChar;
		break;

		case 'BOOL':
		// Boolean (two bytes: 0x0100 for true, 0x0000 for false)
		theRGV = dynamic_cast<LRadioGroupView *>(this->FindPaneByID(mCurrentID));
		theCurrentRadioID = theRGV->GetCurrentRadioID();
		if ( (theCurrentRadioID - mCurrentID) % 2 ) {
			*mOutStream << (UInt16) 0x0100;
		} else {
			*mOutStream << (UInt16) 0x0000;
		}
		// The RGV and both radiobuttons have an ID
		mCurrentID += 3;
		break;

		case 'CHAR':
		// A single character
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(theString);		
		*mOutStream << (char) (theString + 1);
		mCurrentID++;
		break;

		case 'CSTR':
		// C string
		theWasteEdit = dynamic_cast<CWasteEditView *>(this->FindPaneByID(mCurrentID));
		theHandle = theWasteEdit->GetTextHandle();
		theLength = theWasteEdit->GetTextLength();

		locker.Adopt(theHandle);
		mOutStream->PutBytes(*theHandle, theLength);		
		// End with a NULL byte
		*mOutStream << (UInt8) 0x00;
		mCurrentID++;
		break;

		case 'DBYT':
		// Decimal byte
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(numStr);	
		::StringToNum( numStr, &theLong);
		*mOutStream << (SInt8) theLong;
		mCurrentID++;
		break;

		case 'DLNG':
		// Decimal long word
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(numStr);	
		::StringToNum( numStr, &theLong);
		*mOutStream << (SInt32) theLong;
		mCurrentID++;
		break;

		case 'DWRD':
		// Decimal word
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(numStr);	
		::StringToNum( numStr, &theLong);
		*mOutStream << (SInt16) theLong;
		mCurrentID++;
		break;

		case 'ECST':
		// Even-padded C string (padded with nulls)
		theWasteEdit = dynamic_cast<CWasteEditView *>(this->FindPaneByID(mCurrentID));
		theHandle = theWasteEdit->GetTextHandle();
		theLength = theWasteEdit->GetTextLength();

		locker.Adopt(theHandle);
		mOutStream->PutBytes(*theHandle, theLength);		
		// End with a NULL byte
		*mOutStream << (UInt8) 0x00;
		// Padd with a NULL byte if total length with ending NULL is odd
		if (theLength % 2 == 0) {
			*mOutStream << (UInt8) 0x00;
		} 
		mCurrentID++;
		break;

		case 'ESTR':
		// Pascal string padded to even length (needed for DITL resources)
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(theString);	
		*mOutStream << theString;
		if (theString[0] % 2 == 0) {
			// if the length is even, padd the string with a NULL byte.
			*mOutStream << (UInt8) 0x00;
		} 
		mCurrentID++;
		break;

		case 'FBYT':
		// Byte fill (with 0)
		*mOutStream << (SInt8) 0;
		break;

		case 'FLNG':
		// Long fill (with 0)
		*mOutStream << (SInt32) 0;
		break;

		case 'FWRD':
		// Word fill (with 0)
		*mOutStream << (SInt16) 0;
		break;

		case 'HBYT':
		// Hex byte
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(numStr);	
		CopyPascalStringToC(theString, charString);
		sscanf(charString, "$%2x", &theChar);
		*mOutStream << theChar;
		mCurrentID++;
		break;

		case 'HEXD':
		// Hex dump of remaining bytes in resource (this can only be the last type in a resource)
		CDualDataView * theTGB = dynamic_cast<CDualDataView *>(this->FindPaneByID(mCurrentID));
		WEReference theWE = theTGB->GetInMemoryWasteRef();
		theHandle = static_cast<Handle>(::WEGetText(theWE));
		theLength = ::WEGetTextLength(theWE);
		
		locker.Adopt(theHandle);
		mOutStream->PutBytes(*theHandle, theLength);
		mCurrentID++;
		break;

		case 'HLNG':
		// Hex long word
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(numStr);	
		CopyPascalStringToC(theString, charString);
		sscanf(charString, "$%8x", &theUInt32);
		*mOutStream << theChar;
		mCurrentID++;
		break;

		case 'HWRD':
		// Hex word
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(numStr);	
		CopyPascalStringToC(theString, charString);
		sscanf(charString, "$%4x", &theUInt16);
		*mOutStream << theChar;
		mCurrentID++;
		break;

		case 'LSTB':
		// List Begin. Ends at the end of the resource.
		break;

		case 'LSTC':
		// List Count. Terminated by a zero-based word count that starts 
		// the sequence (as in 'DITL' resources).
		break;

		case 'LSTE':
		// List end. Handled in DoRetrieveWithTemplate().
		break;

		case 'LSTR':
		// Long string (length long followed by the characters)
		theWasteEdit = dynamic_cast<CWasteEditView *>(this->FindPaneByID(mCurrentID));
		theHandle = theWasteEdit->GetTextHandle();
		theLength = theWasteEdit->GetTextLength();
		*mOutStream << (UInt32) theLength;

		locker.Adopt(theHandle);
		mOutStream->PutBytes(*theHandle, theLength);
		mCurrentID++;
		break;

		case 'LSTZ':
		// List Zero. Terminated by a 0 byte (as in 'MENU' resources).
		break;
		
		case 'OCNT':
		// One count for LSTC lists
		theStaticText = dynamic_cast<LStaticText *>(this->FindPaneByID(mCurrentID));
		theStaticText->GetDescriptor(theString);	
		::StringToNum( theString, &theLong);
		mItemsCount = (UInt16) theLong;
		*mOutStream << mItemsCount;
		mCurrentID++;
		break;

		case 'OCST':
		// Odd-padded C string (padded with nulls)
		theWasteEdit = dynamic_cast<CWasteEditView *>(this->FindPaneByID(mCurrentID));
		theHandle = theWasteEdit->GetTextHandle();
		theLength = theWasteEdit->GetTextLength();

		locker.Adopt(theHandle);
		mOutStream->PutBytes(*theHandle, theLength);		
		// End with a NULL byte
		*mOutStream << (UInt8) 0x00;
		// Padd with a NULL byte if total length with ending NULL is odd
		if (theLength % 2 == 1) {
			*mOutStream << (UInt8) 0x00;
		} 
		mCurrentID++;
		break;

		case 'OSTR':
		// Pascal string padded to odd length (needed for DITL resources)
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(theString);	
		*mOutStream << theString;
		if (theString[0] % 2) {
			// if the length is odd, padd the string with a NULL byte.
			*mOutStream << (UInt8) 0x00;
		} 
		mCurrentID++;
		break;

		case 'PSTR':
		// Pascal string
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(theString);	
		*mOutStream << theString;
		mCurrentID++;
		break;

		case 'RECT':
		// An 8-byte rectangle
		for (i = 0; i < 4; i++) {
			theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
			theEditText->GetDescriptor(numStr);	
			::StringToNum( numStr, &theLong);
			*mOutStream << (SInt16) theLong;
			mCurrentID++;
		}
		break;

		case 'TNAM':
		// Type name (four characters, like OSType and ResType)
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(theString);	
		UMiscUtils::PStringToOSType(theString, theOSType);
		*mOutStream << theOSType;
		mCurrentID++;
		break;

		case 'WSTR':
		// Same as LSTR, but a word rather than a long word
		theWasteEdit = dynamic_cast<CWasteEditView *>(this->FindPaneByID(mCurrentID));
		theHandle = theWasteEdit->GetTextHandle();
		theLength = theWasteEdit->GetTextLength();
		*mOutStream << (UInt16) theLength;

		locker.Adopt(theHandle);
		mOutStream->PutBytes(*theHandle, theLength);
		mCurrentID++;
		break;

		case 'ZCNT':
		// Zero count for LSTC lists
		theStaticText = dynamic_cast<LStaticText *>(this->FindPaneByID(mCurrentID));
		theStaticText->GetDescriptor(theString);	
		::StringToNum( theString, &theLong);
		if (!theLong) {
			mItemsCount = 0xffff;
		} else {
			mItemsCount = (UInt16) --theLong;
		}
		*mOutStream << mItemsCount;
		mCurrentID++;
		break;

	  default:
	  // Handle Hnnn, Cnnn, P0nn cases here or unrecognized type
	  if (inType >> 24 == 'H') {
		  // Hnnn: a 3-digit hex number; displays nnn bytes in hex format
		  CDualDataView * theTGB = dynamic_cast<CDualDataView *>(this->FindPaneByID(mCurrentID));
		  WEReference theWE = theTGB->GetInMemoryWasteRef();
		  theHandle = static_cast<Handle>(::WEGetText(theWE));
		  theLength = ::WEGetTextLength(theWE);
		  reqLength = inType << 8 & 0xffffff00;

		  if (theLength < reqLength) {
			  UMessageDialogs::AlertForValue(CFSTR("StringShorterThanRequired"), reqLength);
		  } else {
			  locker.Adopt(theHandle);
			  mOutStream->PutBytes(*theHandle, reqLength);
		  }
		  mCurrentID++;
		  
	  } else if (inType >> 24 == 'C') {
		  // Cnnn: a C string that is nnn hex bytes long (The last byte is always a 0, so the string itself occupies the first nnn-1 bytes.)
		  theWasteEdit = dynamic_cast<CWasteEditView *>(this->FindPaneByID(mCurrentID));
		  theHandle = theWasteEdit->GetTextHandle();
		  theLength = theWasteEdit->GetTextLength();
		  reqLength = (inType << 8 & 0xffffff00) - 1;

		  if (theLength < reqLength) {
			  UMessageDialogs::AlertForValue(CFSTR("StringShorterThanRequired"), reqLength);
		  } else {
			  locker.Adopt(theHandle);
			  mOutStream->PutBytes(*theHandle, reqLength);		
			  // End with a NULL byte
			  *mOutStream << (UInt8) 0x00;
		  }
		  mCurrentID++;

	  } else if ( inType >> 16 == 'P0') {
		  // P0nn: a Pascal string that is nn hex bytes long (The length byte is not included in nn, so the string occupies the entire specified length.)
		  theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		  theEditText->GetDescriptor(theString);	
		  theLength = theString[0];
		  reqLength = inType << 16 & 0xffff0000;

		  if (theLength < reqLength) {
			  UMessageDialogs::AlertForValue(CFSTR("StringShorterThanRequired"), reqLength);
		  } else {
			  theString[0] = reqLength;
			  *mOutStream << theString;
		  }
		  mCurrentID++;

	  } else {
		  // Unrecognized type
		  UMessageDialogs::AlertForType(CFSTR("UnknownTemplateType"), inType);
	  }
	  break;
	}

	return error;
}


