// ===========================================================================
// CTmplEditorWindow.cp					
// 
//                       Created: 2004-06-12 15:08:01
//             Last modification: 2004-08-16 15:10:59
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
#include "CTemplatesController.h"
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

#ifdef RZIL_PantherOrGreater
#include <CFDateFormatter.h>
#endif


#include <stdio.h>
#include <string.h>

// Statics
ResIDT CTmplEditorWindow::sCommentTraitsID = Txtr_MonacoBlueNineCenter;
ResIDT CTmplEditorWindow::sLeftLabelTraitsID = Txtr_GenevaTenBoldUlLeft;
ResIDT CTmplEditorWindow::sRightLabelTraitsID = Txtr_GenevaTenBoldUlRight;
ResIDT CTmplEditorWindow::sEditTraitsID = Txtr_GenevaTen;
ResIDT CTmplEditorWindow::sHeaderTraitsID = Txtr_GenevaTenBold;
SPaneInfo CTmplEditorWindow::sEditPaneInfo;
SPaneInfo CTmplEditorWindow::sStaticPaneInfo;
SPaneInfo CTmplEditorWindow::sRgvPaneInfo;
SPaneInfo CTmplEditorWindow::sRadioPaneInfo;
SPaneInfo CTmplEditorWindow::sCheckPaneInfo;
SPaneInfo CTmplEditorWindow::sRectLabelInfo;
SPaneInfo CTmplEditorWindow::sRectPaneInfo;
SPaneInfo CTmplEditorWindow::sScrollPaneInfo;
SPaneInfo CTmplEditorWindow::sTgbPaneInfo;
SPaneInfo CTmplEditorWindow::sWastePaneInfo;
SPaneInfo CTmplEditorWindow::sPushPaneInfo;
SPaneInfo CTmplEditorWindow::sListItemInfo;
SPaneInfo CTmplEditorWindow::sSeparatorPaneInfo;
SPaneInfo CTmplEditorWindow::sBevelPaneInfo;


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
	mSkipOffset			= 0;
	mBitSeqInProgress	= false;
	mBitSeqValue		= 0;
	mBitSeqBytesLen		= 0;
	mBitSeqIndex		= 0;
	mIsDirty			= false;
	mYCoord             = kTmplVertSkip;
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

	InitPaneInfos();
}
	

// ---------------------------------------------------------------------------
//		¥ InitPaneInfos												[static]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::InitPaneInfos()
{
	// Label fields basic values
	sStaticPaneInfo.paneID			= 0;
	sStaticPaneInfo.height			= kTmplLabelHeight;
	sStaticPaneInfo.visible			= true;
	sStaticPaneInfo.enabled			= true;
	sStaticPaneInfo.bindings.left	= true;
	sStaticPaneInfo.bindings.top	= false;
	sStaticPaneInfo.bindings.right	= false;
	sStaticPaneInfo.bindings.bottom = false;
	sStaticPaneInfo.userCon			= 0;
	
	// Edit fields basic values
	sEditPaneInfo.paneID			= 0;
	sEditPaneInfo.height			= kTmplEditHeight;
	sEditPaneInfo.visible			= true;
	sEditPaneInfo.enabled			= true;
	sEditPaneInfo.bindings.left		= true;
	sEditPaneInfo.bindings.top		= false;
	sEditPaneInfo.bindings.right	= true;
	sEditPaneInfo.bindings.bottom	= false;
	sEditPaneInfo.userCon			= 0;

	// Radio group view basic values
	sRgvPaneInfo.paneID				= 0;
	sRgvPaneInfo.width				= kTmplRgvWidth;
	sRgvPaneInfo.height				= kTmplRgvHeight;
	sRgvPaneInfo.visible			= true;
	sRgvPaneInfo.enabled			= true;
	sRgvPaneInfo.bindings.left		= true;
	sRgvPaneInfo.bindings.top		= false;
	sRgvPaneInfo.bindings.right		= false;
	sRgvPaneInfo.bindings.bottom	= false;
	sRgvPaneInfo.userCon			= 0;
	
	// Radio buttons basic values
	sRadioPaneInfo.paneID			= 0;
	sRadioPaneInfo.width			= kTmplRadioWidth;
	sRadioPaneInfo.height			= kTmplRadioHeight;
	sRadioPaneInfo.visible			= true;
	sRadioPaneInfo.enabled			= true;
	sRadioPaneInfo.bindings.left	= true;
	sRadioPaneInfo.bindings.top		= false;
	sRadioPaneInfo.bindings.right	= false;
	sRadioPaneInfo.bindings.bottom	= false;
	sRadioPaneInfo.userCon			= 0;

	// Check boxes basic values
	sCheckPaneInfo.paneID			= 0;
	sCheckPaneInfo.width			= kTmplCheckWidth;
	sCheckPaneInfo.height			= kTmplCheckHeight;
	sCheckPaneInfo.visible			= true;
	sCheckPaneInfo.enabled			= true;
	sCheckPaneInfo.bindings.left	= true;
	sCheckPaneInfo.bindings.top		= false;
	sCheckPaneInfo.bindings.right	= false;
	sCheckPaneInfo.bindings.bottom	= false;
	sCheckPaneInfo.userCon			= 0;

	// Rectangle labels basic values
	sRectLabelInfo.paneID			= 0;
	sRectLabelInfo.width			= kTmplRectWidth;
	sRectLabelInfo.height			= kTmplRectHeight;
	sRectLabelInfo.visible			= true;
	sRectLabelInfo.enabled			= true;
	sRectLabelInfo.bindings.left	= true;
	sRectLabelInfo.bindings.top		= false;
	sRectLabelInfo.bindings.right	= false;
	sRectLabelInfo.bindings.bottom	= false;
	sRectLabelInfo.userCon			= 0;

	// Rectangle edit basic values
	sRectPaneInfo.width				= kTmplRectWidth;
	sRectPaneInfo.height			= kTmplEditHeight;
	sRectPaneInfo.visible			= true;
	sRectPaneInfo.enabled			= true;
	sRectPaneInfo.bindings.left		= true;
	sRectPaneInfo.bindings.top		= false;
	sRectPaneInfo.bindings.right	= false;
	sRectPaneInfo.bindings.bottom	= false;
	sRectPaneInfo.userCon			= 0;
	
	// Active scrollers basic values
	sScrollPaneInfo.paneID			= 0;
	sScrollPaneInfo.visible			= true;
	sScrollPaneInfo.enabled			= true;
	sScrollPaneInfo.bindings.left	= false;
	sScrollPaneInfo.bindings.top	= true;
	sScrollPaneInfo.bindings.right	= true;
	sScrollPaneInfo.bindings.bottom	= true;
	sScrollPaneInfo.userCon			= 0;

	// Text group box for text views basic values
	sTgbPaneInfo.height				= kTmplTextHeight;
	sTgbPaneInfo.visible			= true;
	sTgbPaneInfo.enabled			= true;
	sTgbPaneInfo.bindings.left		= true;
	sTgbPaneInfo.bindings.top		= false;
	sTgbPaneInfo.bindings.right		= true;
	sTgbPaneInfo.bindings.bottom	= false;
	sTgbPaneInfo.userCon			= 0;

	// Text views basic values
	sWastePaneInfo.paneID			= 0;
	sWastePaneInfo.visible			= true;
	sWastePaneInfo.enabled			= true;
	sWastePaneInfo.bindings.left	= true;
	sWastePaneInfo.bindings.top		= true;
	sWastePaneInfo.bindings.right	= true;
	sWastePaneInfo.bindings.bottom	= true;
	sWastePaneInfo.userCon			= 0;
	
	// Push buttons basic values
	sPushPaneInfo.width				= kTmplPushWidth;
	sPushPaneInfo.height			= kTmplPushHeight;
	sPushPaneInfo.visible			= true;
	sPushPaneInfo.enabled			= true;
	sPushPaneInfo.bindings.left		= false;
	sPushPaneInfo.bindings.top		= false;
	sPushPaneInfo.bindings.right	= false;
	sPushPaneInfo.bindings.bottom	= false;
	sPushPaneInfo.userCon			= 0;
	
	// List item views basic values
	sListItemInfo.height			= 0;
	sListItemInfo.visible			= true;
	sListItemInfo.enabled			= true;
	sListItemInfo.bindings.left		= true;
	sListItemInfo.bindings.top		= false;
	sListItemInfo.bindings.right	= true;
	sListItemInfo.bindings.bottom	= false;
	sListItemInfo.userCon			= 0;
	
	// Separator horizontal line basic values
	sSeparatorPaneInfo.paneID			= 0;
	sSeparatorPaneInfo.height			= kTmplSeparatorHeight;
	sSeparatorPaneInfo.visible			= true;
	sSeparatorPaneInfo.enabled			= true;
	sSeparatorPaneInfo.bindings.left	= true;
	sSeparatorPaneInfo.bindings.top		= false;
	sSeparatorPaneInfo.bindings.right	= true;
	sSeparatorPaneInfo.bindings.bottom = false;
	sSeparatorPaneInfo.userCon			= 0;
	
	// Popup button fields basic values
	sBevelPaneInfo.width			= kTmplBevelWidth;
	sBevelPaneInfo.height			= kTmplBevelHeight;
	sBevelPaneInfo.visible			= true;
	sBevelPaneInfo.enabled			= true;
	sBevelPaneInfo.bindings.left	= false;
	sBevelPaneInfo.bindings.top		= false;
	sBevelPaneInfo.bindings.right	= true;
	sBevelPaneInfo.bindings.bottom 	= false;
	sBevelPaneInfo.userCon			= 0;
}


// ---------------------------------------------------------------------------
//		¥ ListenToMessage											[public]
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

			// Window has been modified
			SetDirty(true);

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
			
			// Window has been modified
			SetDirty(true);
			
			break;
			
			
		case msg_TmplModifiedItem:
		SetDirty(true);
		break;
		
		
		case msg_TmplCasePopup: {
			register char *	p;
			STmplBevelInfo	theBevelInfo = *((STmplBevelInfo *) ioParam);								
			LEditText *		theEditText;
			CTmplBevelButton *	theBevel;
			SInt32			firstMark, currMark;
			Str255			theString;
			char 			charString[256];
			ResType			theType;
			SInt16			i, choice;
			SInt32			len;
			
			choice = theBevelInfo.menuChoice;
			theBevel = dynamic_cast<CTmplBevelButton *>(theBevelInfo.selfPtr);
			theEditText = (LEditText *) theBevel->GetUserCon();
			
			firstMark = theEditText->GetUserCon();
			currMark = mTemplateStream->GetMarker();
			mTemplateStream->SetMarker(firstMark, streamFrom_Start);

			for ( i = 0; i < choice ; i++) {
				*mTemplateStream >> theString;
				*mTemplateStream >> theType;
			}
			CopyPascalStringToC(theString, charString);
			p = strrchr((char *) charString, '=');
			if (p != nil) {
				len = (p - (char *) charString) + 1;
				CopyCStringToPascal(charString + len, theString);
				theEditText->SetDescriptor(theString);
			} 
			mTemplateStream->SetMarker(currMark, streamFrom_Start);
			break;
		}
		
		
		case msg_TmplPopupField: {
			register char *	p;
			STmplBevelInfo	theBevelInfo = *((STmplBevelInfo *) ioParam);								
			CTmplBevelButton *	theBevel;
			LEditText *		theEditText;
			Str255			theString;
			char 			charString[256];
			SInt16			choice;
			SInt32			len;
			ResIDT			resID;
			
			choice = theBevelInfo.menuChoice;
			theBevel = dynamic_cast<CTmplBevelButton *>(theBevelInfo.selfPtr);
			theEditText = (LEditText *) theBevel->GetUserCon();
			resID = (ResIDT) theEditText->GetUserCon();
			
			GetIndString(theString, resID, choice);
			CopyPascalStringToC(theString, charString);
			p = strrchr((char *) charString, '=');
			if (p != nil) {
				len = (p - (char *) charString) + 1;
				CopyCStringToPascal(charString + len, theString);
				theEditText->SetDescriptor(theString);
			} 
			break;
		}
		
		
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
	if (!mIsDirty) {
		// The mWasteFieldsList contains all the Waste views. Check if they
		// are modified.
		TArrayIterator<CWasteEditView *> iterator(mWasteFieldsList);
		CWasteEditView *	theWasteView = nil;
		
		while (iterator.Next(theWasteView)) {
			mIsDirty = theWasteView->IsDirty();
			if (mIsDirty) {
				break;
			} 
		}
	} 

	return mIsDirty;
}


#pragma mark -

// ---------------------------------------------------------------------------
//	¥ CreateTemplateStream									[protected]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::CreateTemplateStream()
{
	Handle theHandle = CTemplatesController::GetTemplateHandle( mOwnerDoc->GetSubstType() );
	if (theHandle == NULL) {
		UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("CouldNotGetTemplateData"), rPPob_SimpleMessage);
// 		UMessageDialogs::AlertForType(CFSTR("CouldNotGetTemplateDataForType"), mOwnerDoc->GetSubstType());
	} 
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
		
		if (theType == 'OCNT' || theType == 'WCNT' || theType == 'ZCNT' 
			|| theType == 'FCNT' || theType == 'LCNT' || theType == 'LZCT') {
			LString::CopyPStr(theString, countLabel);
			mFixedCount = (theType == 'FCNT');
			ParseDataForType(theType, theString, inContainer);
		} else if (theType == 'LSTB' || theType == 'LSTC' || theType == 'LSTZ') {
			if (inDrawControls) {
				AddListHeaderField(theType, theString, mItemsCount, countLabel, inContainer, mFixedCount);
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
	char 	formatString[16];
	Str255	numStr, typeStr, theString;
	SInt8	theSInt8 = 0;
	SInt16	theSInt16 = 0;
	SInt32	theSInt32 = 0, theLength;
	UInt8	theUInt8 = 0;
	UInt16	theUInt16 = 0, bitCount = 0, bytesLen = 0;
	UInt32	theUInt32 = 0;
	long	theLong;
	Boolean	theBool = 0;
	OSType	theOSType;
	
	theString[0] = 0;
	numStr[0] = 0;
		
	switch (inType) {
		case 'ALNG':
		// Long align
		AlignBytesRead(4);
		break;

		case 'AL08':
		// Align to 8-byte boundary
		AlignBytesRead(8);
		break;

		case 'AL16':
		// Align to 16-byte boundary
		AlignBytesRead(16);
		break;

		case 'AWRD':
		// Word align
		AlignBytesRead(2);
		break;

		case 'ALRT':
		// Post an alert with description string
		break;

		case 'BBIT':
		// Binary bit within a byte
		AddBitField(inType, inLabelString, 1, 1, inContainer);
		break;

		case 'BCNT':
		// Byte Count for LSTC lists
		if (mRezStream->GetMarker() < mRezStream->GetLength()) {
			*mRezStream >> theUInt8;
		} 
		mItemsCount = theUInt8;
		break;

		case 'BFLG':
		// Boolean (one byte: 0x01 for true, 0x00 for false)
		if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
			*mRezStream >> theBool;
		} 
		AddStaticField(inType, inLabelString, inContainer);
		AddCheckField( theBool, inType, inContainer);		
		break;

		case 'BOOL':
		// Boolean (two bytes: 0x0100 for true, 0x0000 for false)
		if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
			*mRezStream >> theBool;
		} 
		AddStaticField(inType, inLabelString, inContainer);
		AddBooleanField( theBool, inType, tmpl_titleYesNo, inContainer);		
		// BOOL template type is two bytes long, so let's consume one more byte
		if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
			*mRezStream >> theBool;
		} 
		break;

		case 'BSIZ':
		case 'BSKP':
		// Offset to SKPE in byte (BSIZ:exclusive or BSKP:inclusive)
		if (mRezStream->GetMarker() < mRezStream->GetLength()) {
			*mRezStream >> theUInt8;
		} 
		mOffsetTypesList.AddItem(inType);
		break;

		case 'CASE':
		// Switch with predefined values. Remember the position mark of the
		// first CASE in the template stream
		theSInt32 = mTemplateStream->GetMarker() - inLabelString[0] - 5;
		AddCasePopup(inType, inLabelString, theSInt32, inContainer);		
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
		AddStaticField(inType, inLabelString, inContainer);
		AddEditField(theString, inType, 1, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_PrintingChar), inContainer);
		break;

		case 'CSTR':
		// C string. This should be either characters followed by a null or all
		// the chars until the end of the stream if there is no null byte.
		AddStaticField(inType, inLabelString, inContainer, sLeftLabelTraitsID);
		mYCoord += kTmplLabelHeight + kTmplVertSkip;
		AddWasteField(inType, inContainer);
 		break;

		case 'DATE':
		// Date/Time
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 3) {
			*mRezStream >> theSInt32;
		} 
		UMiscUtils::BuildDateString(theSInt32, theString);
		AddStaticField(inType, inLabelString, inContainer);
		AddEditField(theString, inType, 255, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_PrintingChar), inContainer);
		break;

		case 'DBYT':
		// Signed decimal byte
		if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
			*mRezStream >> theSInt8;
		} 
		::NumToString( (long) theSInt8, numStr);
		AddStaticField(inType, inLabelString, inContainer);
		AddEditField(numStr, inType, 4, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_NegativeInteger), inContainer);
		break;

		case 'DLNG':
		// Signed decimal long word
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 3) {
			*mRezStream >> theSInt32;
		} 
		::NumToString( (long) theSInt32, numStr);
		AddStaticField(inType, inLabelString, inContainer);
		AddEditField(numStr, inType, 6, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_NegativeInteger), inContainer);
		break;

		case 'DVDR':
		// Divider
		AddSeparatorLine(inContainer);
		break;

		case 'DWRD':
		case 'RSID':
		// Signed decimal word
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 1) {
			*mRezStream >> theSInt16;
		} 
		::NumToString( (long) theSInt16, numStr);
		AddStaticField(inType, inLabelString, inContainer);
		AddEditField(numStr, inType, 11, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_NegativeInteger), inContainer);
		break;

		case 'ECST':
		// Even-padded C string (padded with nulls)
		AddStaticField(inType, inLabelString, inContainer, sLeftLabelTraitsID);
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
		AddStaticField(inType, inLabelString, inContainer);
		AddEditField(theString, inType, 255, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_PrintingChar), inContainer);
		
		break;

		case 'FBYT':
		case 'HBYT':
		// Hex byte
		if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
			*mRezStream >> theUInt8;
		} 
		BuildFormatString(formatString, 2);
		sprintf(charString, formatString, theUInt8, NULL);
		CopyCStringToPascal(charString, theString);
		AddStaticField(inType, inLabelString, inContainer);
		AddEditField(theString, inType, 2 + CRezillaPrefs::GetPrefValue(kPref_editors_hexSymbol), 0, 
					 &UHexFilters::HexTemplateField, inContainer);
		break;

		case 'FCNT': {
			// Fixed count of list items (0 bytes). The count should be the
			// beginning of the label string
			register UInt8 *	p;
			p = inLabelString + 1;
			while ((*p >= '0') && (*p <= '9')) {
				p++;
			}
			if (p != inLabelString + 1 ) {
				inLabelString[0] = p - inLabelString - 1;
				::StringToNum( theString, &theLong);
				mItemsCount = theLong;
			} else {
				error = err_TmplWrongFixedCount;
			}
			break;
		}

		case 'FLNG':
		case 'HLNG':
		// Hex long word
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 3) {
			*mRezStream >> theUInt32;
		} 
		BuildFormatString(formatString, 8);
		sprintf(charString, formatString, theUInt32, NULL);
		CopyCStringToPascal(charString, theString);
		AddStaticField(inType, inLabelString, inContainer);
		AddEditField(theString, inType, 8 + CRezillaPrefs::GetPrefValue(kPref_editors_hexSymbol), 0, 
					 &UHexFilters::HexTemplateField, inContainer);
		break;

		case 'FWRD':
		case 'HWRD':
		// Hex word
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 1) {
			*mRezStream >> theUInt16;
		} 
		BuildFormatString(formatString, 4);
		sprintf(charString, formatString, theUInt16, NULL);
		CopyCStringToPascal(charString, theString);
		AddStaticField(inType, inLabelString, inContainer);
		AddEditField(theString, inType, 4 + CRezillaPrefs::GetPrefValue(kPref_editors_hexSymbol), 0, 
					 &UHexFilters::HexTemplateField, inContainer);
		break;

		case 'HEXD':
		case 'BHEX':
		case 'BSHX':
		case 'LHEX':
		case 'LSHX':
		case 'WHEX':
		case 'WSHX':
		// Hex dump of remaining bytes in resource (this can only be the last type in a resource)
		AddStaticField(inType, inLabelString, inContainer, sLeftLabelTraitsID);
		mYCoord += kTmplLabelHeight + kTmplVertSkip;
		AddHexDumpField(inType, inContainer);
		break;

		case 'LABL':
		// Insert a comment
		AddStaticField(inType, inLabelString, inContainer, sCommentTraitsID);
		break;

		case 'LBIT':
		// Binary bit within a long
		AddBitField(inType, inLabelString, 1, 4, inContainer);
		break;

		case 'LCNT':
		// One-based long count
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 1) {
			*mRezStream >> theUInt32;
		} 
		if (theUInt32 < 0xffff) {
			mItemsCount = theUInt32;
		} else {
			error = err_TmplListCountTooBig;
		}
		break;

		case 'LFLG':
		// Long Boolean flag in low-order bit (four bytes: 0x00000001 for true,
		// 0x00000000 for false)
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 1) {
			*mRezStream >> theUInt32;
		} 
		AddStaticField(inType, inLabelString, inContainer);
		AddBooleanField( (Boolean) theUInt32, inType, tmpl_titleYesNo, inContainer);		
		break;

		case 'LSIZ':
		case 'LSKP':
		// Offset to SKPE in long (LSIZ:exclusive or LSKP:inclusive)
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 3) {
			*mRezStream >> theUInt32;
		} 
		mOffsetTypesList.AddItem(inType);
		break;

		case 'LNGC':
		case 'RGNC':
		case 'SCPC': {
			// A language, region or script code
			ResIDT resID;
			
			if (mRezStream->GetMarker() < mRezStream->GetLength() - 1) {
				*mRezStream >> theUInt16;
			} 
			::NumToString( (long) theUInt16, numStr);

			switch (inType) {
				case 'LNGC':
				resID = STRx_LanguageCodes;
				break;

				case 'RGNC':
				resID = STRx_RegionCodes;
				break;

				case 'SCPC':
				resID =STRx_ScriptCodes ;
				break;
			}
			
			AddStaticField(inType, inLabelString, inContainer);
			AddEditPopup(numStr, inType, 6, kTmplPopupFieldWidth, 0, 
						 UKeyFilters::SelectTEKeyFilter(keyFilter_NegativeInteger), resID, inContainer);
			break;
		}

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
		// Long string (long  length followed by the characters)
		AddStaticField(inType, inLabelString, inContainer, sLeftLabelTraitsID);
		mYCoord += kTmplLabelHeight + kTmplVertSkip;
		AddWasteField(inType, inContainer);
		break;

		case 'LSTZ':
		// List Zero. Terminated by a 0 byte (as in 'MENU' resources).
		break;
		
		case 'LZCT':
		// Zero-based long count
		if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
			*mRezStream >> theUInt32;
			if (theUInt32 < 0xfffe) {
				mItemsCount = theUInt32 + 1;
			} else {
				error = err_TmplListCountTooBig;
			}
		} else {
			mItemsCount = 0;
		}
		break;

		case 'OCNT':
		case 'WCNT':
		// One-based Count. Terminated by a one-based word count that starts 
		// the sequence (as in 'STR#' resources).
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 1) {
			*mRezStream >> theUInt16;
		} 
		mItemsCount = theUInt16;
		break;

		case 'OCST':
		// Odd-padded C string (padded with nulls)
		AddStaticField(inType, inLabelString, inContainer, sLeftLabelTraitsID);
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
		AddStaticField(inType, inLabelString, inContainer);
		AddEditField(theString, inType, 255, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_PrintingChar), inContainer);
		break;

		case 'PNT ': {
			// An 4-byte point
			SInt16 theX = 0, theY = 0;
			if (mRezStream->GetMarker() < mRezStream->GetLength() - 3) {
				*mRezStream >> theX;
				*mRezStream >> theY;
			} 
			mYCoord += kTmplRectVertSkip;
			AddStaticField(inType, inLabelString, inContainer);
			mYCoord -= kTmplRectVertSkip;
			AddPointField(theX, theY, inType, 6, 0, 
						 UKeyFilters::SelectTEKeyFilter(keyFilter_NegativeInteger), inContainer);
			break;
		}

		case 'PPST':
		// Pascal string padded to even length (needed for MPSR 1007 resources)
		if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
			*mRezStream >> theString;
			theLength = theString[0];
			if (theLength % 2) {
				// Look at the last byte: if it is 0, the string was padded and 
				// theLength should be decremented
				if ( theString[theLength] == 0) {
					theString[0] = theLength - 1;
				}
			} else {
				// theLength should never be even
				error = err_TmplWrongEvenValue;
			}
		} else {
			theString[0] = 0;
		}
		AddStaticField(inType, inLabelString, inContainer);
		AddEditField(theString, inType, 255, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_PrintingChar), inContainer);
		break;

		case 'BSTR':
		case 'PSTR':
		// Pascal string
		if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
			*mRezStream >> theString;
		} else {
			theString[0] = 0;
		}
		AddStaticField(inType, inLabelString, inContainer);
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
			AddStaticField(inType, inLabelString, inContainer);
			mYCoord -= kTmplRectVertSkip;
			AddRectField(theTop, theLeft, theBottom, theRight, inType, 6, 0, 
						 UKeyFilters::SelectTEKeyFilter(keyFilter_NegativeInteger), inContainer);
			break;
		}

		case 'SKPE':
		// End of Skip or Sizeof. Do nothing.
		break;

		case 'TNAM':
		// Type name (four characters, like OSType and ResType)
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 3) {
			*mRezStream >> theOSType;
			UMiscUtils::OSTypeToPString(theOSType, theString);
		} else {
			theString[0] = 0;
		}
		AddStaticField(inType, inLabelString, inContainer);
		AddEditField(theString, inType, 4, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_PrintingChar), inContainer);
		break;

		case 'UBYT':
		// Unsigned decimal byte
		if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
			*mRezStream >> theUInt8;
		} 
		::NumToString( (long) theUInt8, numStr);
		AddStaticField(inType, inLabelString, inContainer);
		AddEditField(numStr, inType, 4, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_Integer), inContainer);
		break;

		case 'ULNG':
		// Unsigned decimal long word
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 3) {
			*mRezStream >> theUInt32;
		} 
		::NumToString( (long) theUInt32, numStr);
		AddStaticField(inType, inLabelString, inContainer);
		AddEditField(numStr, inType, 6, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_Integer), inContainer);
		break;

		case 'UWRD':
		// Unsigned decimal word
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 1) {
			*mRezStream >> theUInt16;
		} 
		::NumToString( (long) theUInt16, numStr);
		AddStaticField(inType, inLabelString, inContainer);
		AddEditField(numStr, inType, 11, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_Integer), inContainer);
		break;

		case 'WBIT':
		// Binary bit within a word
		AddBitField(inType, inLabelString, 1, 2, inContainer);
		break;

		case 'WFLG':
		// Word Boolean flag in low-order bit (two bytes: 0x0001 for true, 0x0000 for false)
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 1) {
			*mRezStream >> theUInt16;
		} 
		AddStaticField(inType, inLabelString, inContainer);
		AddBooleanField( (Boolean) theUInt16, inType, tmpl_titleYesNo, inContainer);		
		break;

		case 'WSIZ':
		case 'WSKP':
		// Offset to SKPE in word (WSIZ:exclusive or WSKP:inclusive)
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 1) {
			*mRezStream >> theUInt16;
		} 
		mOffsetTypesList.AddItem(inType);
		break;

		case 'WSTR':
		// Same as LSTR, but a word rather than a long word
		AddStaticField(inType, inLabelString, inContainer, sLeftLabelTraitsID);
		mYCoord += kTmplLabelHeight + kTmplVertSkip;
		AddWasteField(inType, inContainer);
 		break;

		case 'ZCNT':
		// Zero-based Count. Terminated by a zero-based word count that starts 
		// the sequence (as in 'DITL' resources).
		if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
			*mRezStream >> theUInt16;
			mItemsCount = theUInt16 + 1;
		} else {
			mItemsCount = 0;
		}
		break;

	  default:
	  UMiscUtils::OSTypeToPString(inType, typeStr);
	  // Handle Hnnn, Cnnn, P0nn, BB0n etc cases here or unrecognized type
	  if (inType >> 24 == 'H' && UMiscUtils::IsValidHexadecimal( (Ptr) typeStr + 2, 3) ) {
		  
		  // Hnnn: a 3-digit hex number; displays nnn bytes in hex format.
		  AddStaticField(inType, inLabelString, inContainer, sLeftLabelTraitsID);
		  mYCoord += kTmplLabelHeight + kTmplVertSkip;
		  AddHexDumpField(inType, inContainer);
		  
	  } else if (inType >> 24 == 'C' && UMiscUtils::IsValidHexadecimal( (Ptr) typeStr + 2, 3) ) {
		  
		  // Cnnn: a C string that is nnn hex bytes long (the last byte is always a 0, 
		  // so the string itself occupies the first nnn-1 bytes.)
		  AddStaticField(inType, inLabelString, inContainer, sLeftLabelTraitsID);
		  mYCoord += kTmplLabelHeight + kTmplVertSkip;
		  AddWasteField(inType, inContainer);
		  
	  } else if ( inType >> 16 == 'P0' && UMiscUtils::IsValidHexadecimal( (Ptr) typeStr + 3, 2)) {
		  
		  // P0nn: a Pascal string that is nn hex bytes long (the length byte is not included in nn, 
		  // so the string occupies the entire specified length.)
		  SInt32 length = 255;
		  if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
			  SInt32 length;
			  char str[3];
			  char * p = (char*) &inType;
			  sprintf(str, "%c%c%c", *(p+2), *(p+3), 0);
			  ::LowercaseText(str, 2, (ScriptCode)0);
			  sscanf(str, "%2x", &length);

			  *mRezStream >> theString;
			  if (theString[0] > length) {
				  theString[0] = length;
			  } 
		  } else {
			theString[0] = 0;
		}
		AddStaticField(inType, inLabelString, inContainer);
		AddEditField(theString, inType, length, 0, 
					   UKeyFilters::SelectTEKeyFilter(keyFilter_PrintingChar), inContainer);
					   
	  } else if ( IsValidBitField(inType, typeStr, bitCount, bytesLen) ) {
		  
		  AddBitField(inType, inLabelString, bitCount, bytesLen, inContainer);
		  
	  } else {
		  // Unrecognized type
		  UMessageDialogs::AlertForType(CFSTR("UnknownTemplateTag"), inType);
	  }
	  break;
	}

	return error;
}


// ---------------------------------------------------------------------------
//	¥ IsValidBitField													[public]
// ---------------------------------------------------------------------------
// BB0n  	BB01 to BB07	Bit field within a byte
// LBnn  	LB01 to LB31	Bit field within a long
// WBnn  	WB01 to WB16	Bit field within a word

Boolean
CTmplEditorWindow::IsValidBitField(OSType inType, Str255 inStr, 
								   UInt16 & ioBitsCount, UInt16 & ioBytesLen)
{
	Boolean isValid = false;
	long	theLong;
	
	if (inType >> 8 == 'BB0') {
		if (inStr[4] > '0' && inStr[4] < '8') {
			ioBitsCount = inStr[4] - '0';
			ioBytesLen = 1;
			isValid = true;
		} 
	} else {
		if ( ((inStr[3] >= '0') && (inStr[3] <= '9')) && ((inStr[4] > '0') && (inStr[4] < 8)) ) {
			inStr[2] = 2;
			::StringToNum( inStr + 2, &theLong);
			if (inType >> 16 == 'LB' && theLong <= 32) {
				ioBitsCount = theLong;
				ioBytesLen = 4;
				isValid = true;				
			} else if (inType >> 16 == 'WB' && theLong <= 16) {
				ioBitsCount = theLong;
				ioBytesLen = 2;
				isValid = true;
			} 
		} 
	}
	
	return isValid;
}


// ---------------------------------------------------------------------------
//	¥ BuildFormatString													[public]
// ---------------------------------------------------------------------------


void
CTmplEditorWindow::BuildFormatString(char * ioString, UInt8 inLength)
{
	if (CRezillaPrefs::GetPrefValue(kPref_editors_hexSymbol) == hex_Symb0x) {
		if (CRezillaPrefs::GetPrefValue(kPref_editors_hexCase) == hex_uppercase) {
			sprintf(ioString, "0x%s.%dX%sc%c", "%", inLength, "%", 0);
		} else {
			sprintf(ioString, "0x%s.%dx%sc%c", "%", inLength, "%", 0);
		}
	} else {
		if (CRezillaPrefs::GetPrefValue(kPref_editors_hexCase) == hex_uppercase) {
			sprintf(ioString, "$%s.%dX%sc%c", "%", inLength, "%", 0);
		} else {
			sprintf(ioString, "$%s.%dx%sc%c", "%", inLength, "%", 0);
		}
	}
}


// ---------------------------------------------------------------------------
//	¥ BuildScanString													[public]
// ---------------------------------------------------------------------------

OSErr
CTmplEditorWindow::BuildScanString(char * inString, char * ioFormat, UInt8 inLength)
{
	OSErr error = noErr;
	
	if (inString[0] == '$') {
		sprintf(ioFormat, "$%s%dx%c", "%", inLength, 0);
	} else if (inString[0] == '0' && inString[1] == 'x') {
		sprintf(ioFormat, "0x%s%dx%c", "%", inLength, 0);		
	} else {
		// alert
		error = err_TmplMalformedHexValue;
	}
	return error;
}


#pragma mark -

// ---------------------------------------------------------------------------
//	¥ AddStaticField													[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddStaticField(OSType inType, Str255 inLabel, LView * inContainer, ResIDT inTextTraitsID)
{
	sStaticPaneInfo.left		= kTmplLeftMargin;
	sStaticPaneInfo.top			= mYCoord;
	sStaticPaneInfo.superView	= inContainer;
	
	if (inType == 'LABL') {
		SDimension16	theFrame;
		inContainer->GetFrameSize(theFrame);
		sStaticPaneInfo.width = theFrame.width - kTmplLeftMargin * 2;
	} else {
		sStaticPaneInfo.width = kTmplLabelWidth;
	}

	LStaticText * theStaticText = new LStaticText(sStaticPaneInfo, inLabel, inTextTraitsID);
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

	sEditPaneInfo.left		= kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep;
	sEditPaneInfo.width		= theFrame.width - kTmplLeftMargin * 2 - kTmplLabelWidth - kTmplHorizSep - kTmplHorizSkip;
	sEditPaneInfo.top		= mYCoord - 3;
	sEditPaneInfo.paneID	= mCurrentID;
	sEditPaneInfo.superView	= inContainer;

	LEditText * theEditText = new LEditText(sEditPaneInfo, this, inValue, sEditTraitsID, 
											msg_TmplModifiedItem, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);

	// Store the template's type in the userCon field
	theEditText->SetUserCon(inType);
	
	// Let the window listen to this field
	theEditText->AddListener(this);

	// Advance the counters
	mYCoord += sEditPaneInfo.height + kTmplVertSep;
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
	
	sRgvPaneInfo.left		= kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep;
	sRgvPaneInfo.top		= mYCoord - 2;
	sRgvPaneInfo.paneID		= mCurrentID;
	sRgvPaneInfo.superView	= inContainer;

	LRadioGroupView * theRGV = new LRadioGroupView(sRgvPaneInfo, theViewInfo);
	ThrowIfNil_(theRGV);

	// Store the template's type in the userCon field
	theRGV->SetUserCon(inType);
	
	mCurrentID++;

	// Create two radiobuttons in this group
	//     "Yes/On" radiobutton
	sRadioPaneInfo.left			= 0;
	sRadioPaneInfo.top			= 0;
	sRadioPaneInfo.paneID		= mCurrentID;
	sRadioPaneInfo.superView	= theRGV;

	theRadio = new LStdRadioButton(sRadioPaneInfo, msg_TmplModifiedItem, 
								   inValue, sLeftLabelTraitsID, (UInt8 *)(inTitleType ? "\pOn":"\pYes"));
	ThrowIfNil_(theRadio);
	
	// Add to the radio-group
	theRGV->AddRadio(theRadio);
	
	// Let the window listen to this button
	theRadio->AddListener(this);
	
	mCurrentID++;

	//     "No/Off" radiobutton
	sRadioPaneInfo.left += kTmplRadioWidth + kTmplHorizSep;
	sRadioPaneInfo.paneID = mCurrentID;

	theRadio = new LStdRadioButton(sRadioPaneInfo, msg_TmplModifiedItem, 
								   1 - inValue, sLeftLabelTraitsID, (UInt8 *)(inTitleType ? "\pOff":"\pNo"));
	ThrowIfNil_(theRadio);
	
	// Add to the radio-group
	theRGV->AddRadio(theRadio);
	
	// Let the window listen to this button
	theRadio->AddListener(this);

	theRGV->SetCurrentRadioID( inValue ?  mCurrentID - 1 : mCurrentID );
	
	// Advance the counters
	mYCoord += sRgvPaneInfo.height + kTmplVertSep;
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//	¥ AddBitField											[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddBitField(OSType inType,
							   Str255 inLabel,
							   UInt16 inBitCount, 
							   UInt16 inBytesLen,
							   LView * inContainer)
{
	UInt16	i, val;
	Str255	numStr;
	
	if (!mBitSeqInProgress) {
		mBitSeqInProgress = true;
		// High bit first.
		mBitSeqIndex = mBitSeqBytesLen * 8 - 1;
		mBitSeqBytesLen = inBytesLen;
		if (mRezStream->GetMarker() < mRezStream->GetLength() - mBitSeqBytesLen + 1) {
			*mRezStream >> mBitSeqValue;
		} else {
			mBitSeqValue = 0;
		}
	} 
	
	
	if (inBitCount == 1) {
		AddStaticField(inType, inLabel, inContainer);
		AddCheckField( ((mBitSeqValue & 1 << mBitSeqIndex) > 0), inType, inContainer);	
		mBitSeqIndex--;
	} else {
		// Add the bits count to the label
		LStr255 theLabel(inLabel);
		theLabel += "\p (";
		::NumToString( (long) inBitCount, numStr);
		theLabel += numStr;
		theLabel += "\p bits)";
		AddStaticField(inType, theLabel, inContainer);
		
		// Build the value
		val = 0;
		for (i = 0; i < inBitCount ; i++) {
			val |= mBitSeqValue & 1 << mBitSeqIndex;
			mBitSeqIndex--;
		}
		::NumToString( (long) val, numStr);
		AddEditField(numStr, inType, 4, 0, UKeyFilters::SelectTEKeyFilter(keyFilter_Integer), inContainer);
	}
	
	if (mBitSeqIndex < 0) {
		mBitSeqInProgress = false;
	} 
}


// ---------------------------------------------------------------------------
//	¥ AddCheckField											[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddCheckField(Boolean inValue,
								   OSType inType,
								   LView * inContainer)
{
	sCheckPaneInfo.left			= kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep;;
	sCheckPaneInfo.top			= mYCoord - 2;
	sCheckPaneInfo.paneID		= mCurrentID;
	sCheckPaneInfo.superView	= inContainer;

	LCheckBox * theCheck = new LCheckBox(sCheckPaneInfo, msg_TmplModifiedItem, inValue);
	ThrowIfNil_(theCheck);
		
	// Store the template's type in the userCon field
	theCheck->SetUserCon(inType);
	
	// Let the window listen to this button
	theCheck->AddListener(this);

	// Advance the counters
	mYCoord += sCheckPaneInfo.height + kTmplVertSep;
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
	SInt32		oldPos, newPos, nextPos, theLength;
	Handle		theHandle;
	char 		theChar;
	SViewInfo	theViewInfo;
	SDimension16	theFrame;
	
	inContainer->GetFrameSize(theFrame);

	theViewInfo.imageSize.width		= theViewInfo.imageSize.height	= 0 ;
	theViewInfo.scrollPos.h			= theViewInfo.scrollPos.v		= 0;
	theViewInfo.scrollUnit.h		= theViewInfo.scrollUnit.v		= 1;
	theViewInfo.reconcileOverhang	= false;
	
	sTgbPaneInfo.paneID				= 0;
	sTgbPaneInfo.top				= mYCoord;
	sTgbPaneInfo.left				= kTmplTextMargin;
	sTgbPaneInfo.width				= theFrame.width - kTmplTextMargin * 2;
	sTgbPaneInfo.superView			= inContainer;

	LTextGroupBox * theTGB = new LTextGroupBox(sTgbPaneInfo, theViewInfo, false);
	ThrowIfNil_(theTGB);

	sScrollPaneInfo.left			= kTmplTextInset;
	sScrollPaneInfo.top				= kTmplTextInset;
	sScrollPaneInfo.width			= sTgbPaneInfo.width - kTmplTextInset * 2;
	sScrollPaneInfo.height			= sTgbPaneInfo.height - kTmplTextInset * 2;
	sScrollPaneInfo.bindings.left	= true;
	sScrollPaneInfo.paneID			= 0;
	sScrollPaneInfo.superView		= theTGB;

	LScrollerView * theScroller = new LScrollerView(sScrollPaneInfo, theViewInfo, 0, 15, 0, 15, 16, NULL, true);
	ThrowIfNil_(theScroller);

	sWastePaneInfo.left				= 0;
	sWastePaneInfo.top				= 0;
	sWastePaneInfo.width			= sScrollPaneInfo.width - 15;
	sWastePaneInfo.height			= sScrollPaneInfo.height - 15;
	sWastePaneInfo.bindings.left	= true;
	sWastePaneInfo.bindings.right	= true;
	sWastePaneInfo.paneID			= mCurrentID;
	sWastePaneInfo.superView		= theScroller;

	// Make the Waste edit writable, not wrapping, selectable
	CWasteEditView * theWasteEdit = new CWasteEditView(sWastePaneInfo, theViewInfo, 0, sEditTraitsID);
	ThrowIfNil_(theWasteEdit);

	// Add to the mWasteFieldsList
	mWasteFieldsList.AddItem(theWasteEdit);
	
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
			nextPos = mRezStream->GetMarker();
		break;

		case 'LSTR': {
			UInt32		theUInt32 = 0;
			// Long string (long  length followed by the characters)
			if (mRezStream->GetMarker() < theLength - 3) {
				*mRezStream >> theUInt32;
			}
			oldPos += 4;
			newPos = oldPos + theUInt32;
			nextPos = newPos;
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
			nextPos = newPos;
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
			nextPos = mRezStream->GetMarker();
		break;

		default:
		if (inType >> 24 == 'C') {
			// Cnnn: a C string that is nnn hex bytes long (The last byte is always a 0, 
			// so the string itself occupies the first nnn-1 bytes.)
			SInt32 length;
			char str[4];
			char * p = (char*) &inType;
			sprintf(str, "%c%c%c%c", *(p+1), *(p+2), *(p+3), 0);
			::LowercaseText(str, 3, (ScriptCode)0);
			sscanf(str, "%3x", &length);

			nextPos = oldPos + length;
			newPos = nextPos - 1;
			// Look for a NULL byte in this range
			while (mRezStream->GetMarker() <= nextPos ) {
				*mRezStream >> theChar;
				if (theChar == 0) {
					newPos = mRezStream->GetMarker() - 1;
					break;
				}
			}
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
	mRezStream->SetMarker(nextPos, streamFrom_Start);
	mYCoord += sTgbPaneInfo.height + kTmplVertSep;
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//	¥ AddHexDumpField													[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddHexDumpField(OSType inType, LView * inContainer)
{
	SInt32		oldPos, newPos, nextPos, theLength;
	Handle		theHandle;
	SViewInfo	theViewInfo;
	SDimension16	theFrame;

	inContainer->GetFrameSize(theFrame);
	mOwnerDoc = dynamic_cast<CTmplEditorDoc*>(GetSuperCommander());

	theViewInfo.imageSize.width		= theViewInfo.imageSize.height	= 0 ;
	theViewInfo.scrollPos.h			= theViewInfo.scrollPos.v		= 0;
	theViewInfo.scrollUnit.h		= theViewInfo.scrollUnit.v		= 1;
	theViewInfo.reconcileOverhang	= false;
	
	sTgbPaneInfo.top				= mYCoord;
	sTgbPaneInfo.left				= kTmplTextMargin;
	sTgbPaneInfo.width				= theFrame.width - kTmplTextMargin * 2;
	sTgbPaneInfo.paneID				= mCurrentID;
	sTgbPaneInfo.superView			= inContainer;
	CDualDataView * theTGB = new CDualDataView(sTgbPaneInfo, theViewInfo, false);
	ThrowIfNil_(theTGB);

	// Make the single vertical scroll bar
	sScrollPaneInfo.left			= sTgbPaneInfo.width - kTmplTextInset - kTmplScrollWidth;
	sScrollPaneInfo.top				= kTmplTextInset;
	sScrollPaneInfo.width			= kTmplScrollWidth;
	sScrollPaneInfo.height			= sTgbPaneInfo.height - kTmplTextInset * 2;
	sScrollPaneInfo.bindings.left	= false;
	sScrollPaneInfo.paneID			= 0;
	sScrollPaneInfo.superView		= theTGB;

	CSingleScrollBar * theScroller = new CSingleScrollBar(sScrollPaneInfo, msg_HexScroller, 0, 0, 0, true);
	ThrowIfNil_(theScroller);

	// Make the Waste edit panes: they are, by default, selectable with 
	// wrapping on (so that the image size is recalculated automatically 
	// when the frame size changes). The read only property is set 
	// by InstallSubViews() below.
	sWastePaneInfo.left				= kTmplTextInset;
	sWastePaneInfo.top				= kTmplTextInset;
	sWastePaneInfo.width			= kTmplHexPaneWidth;
	sWastePaneInfo.height			= sScrollPaneInfo.height;
	sWastePaneInfo.bindings.left	= false;
	sWastePaneInfo.bindings.right	= false;
	sWastePaneInfo.paneID			= 0;
	sWastePaneInfo.superView		= theTGB;

	CHexDataSubView * theHexWE = new CHexDataSubView(sWastePaneInfo, theViewInfo, 0, sEditTraitsID);
	ThrowIfNil_(theHexWE);

	sWastePaneInfo.left				= kTmplTxtPaneLeft;
	sWastePaneInfo.width			= kTmplTxtPaneWidth;
	
	CTxtDataSubView * theTxtWE = new CTxtDataSubView(sWastePaneInfo, theViewInfo, 0, sEditTraitsID);
	ThrowIfNil_(theTxtWE);
	
	// Add to the mWasteFieldsList
	mWasteFieldsList.AddItem(theHexWE);
	mWasteFieldsList.AddItem(theTxtWE);
	
	// Install the subpanes and the scroller in the dual view
	theTGB->InstallSubViews(theHexWE, theTxtWE, theScroller, mOwnerDoc->IsReadOnly() );

	// Adjust to the style specified in the preferences
	TextTraitsRecord theTraits = CRezillaPrefs::GetStyleElement( CRezillaPrefs::prefsType_Curr );
	theTGB->ResizeDataPanes();
	theTGB->UpdatePaneCounts();
	theHexWE->ApplyStyleValues( theTraits.size, theTraits.fontNumber);
	theTxtWE->ApplyStyleValues( theTraits.size, theTraits.fontNumber);
	
	// Store the template's type in the userCon field
	theTGB->SetUserCon(inType);
	
	// Insert the text
	theLength = mRezStream->GetLength();
	oldPos = mRezStream->GetMarker();

	switch (inType) {
		case 'HEXD':
		// This is always the last code in a template. Go to the end of the
		// resource data.
		newPos = theLength;
		break;
		
		case 'BHEX': {
			UInt32		theUInt8 = 0;
			// ByteLength Hex Dump
			if (mRezStream->GetMarker() < theLength) {
				*mRezStream >> theUInt8;
			}
			oldPos += 1;
			newPos = oldPos + theUInt8;
			nextPos = newPos;
			break;
		}
		
		case 'BSHX': {
			UInt32		theUInt8 = 0;
			// (ByteLength - 1) Hex Dump
			if (mRezStream->GetMarker() < theLength) {
				*mRezStream >> theUInt8;
			}
			if (theUInt8 < 1) {
				theUInt8 = 1;
			} 
			oldPos += 1;
			newPos = oldPos + theUInt8 - 1;
			nextPos = newPos;
			break;
		}
		
		case 'LHEX': {
			UInt32		theUInt32 = 0;
			// LongLength Hex Dump
			if (mRezStream->GetMarker() < theLength - 3) {
				*mRezStream >> theUInt32;
			}
			oldPos += 4;
			newPos = oldPos + theUInt32;
			nextPos = newPos;
			break;
		}
		
		case 'LSHX': {
			UInt32		theUInt32 = 0;
			// (LongLength - 4) Hex Dump
			if (mRezStream->GetMarker() < theLength - 3) {
				*mRezStream >> theUInt32;
			}
			if (theUInt32 < 4) {
				theUInt32 = 4;
			} 
			oldPos += 4;
			newPos = oldPos + theUInt32 - 4;
			nextPos = newPos;
			break;
		}
		
		case 'WHEX': {
			UInt16		theUInt16 = 0;
			// WordLength Hex Dump
			if (mRezStream->GetMarker() < theLength - 1) {
				*mRezStream >> theUInt16;
			}
			oldPos += 2;
			newPos = oldPos + theUInt16;
			nextPos = newPos;
			break;
		}
		
		case 'WSHX': {
			UInt16		theUInt16 = 0;
			// (WordLength - 2) Hex Dump
			if (mRezStream->GetMarker() < theLength - 1) {
				*mRezStream >> theUInt16;
			}
			if (theUInt16 < 2) {
				theUInt16 = 2;
			} 
			oldPos += 2;
			newPos = oldPos + theUInt16 - 2;
			nextPos = newPos;
			break;
		}
		
		default:
		if (inType >> 24 == 'H') {
			// Hnnn: a 3-digit hex number; displays nnn bytes in hex format
			SInt32 numbytes;
			char str[4];
			char * p = (char*) &inType;
			sprintf(str, "%c%c%c%c", *(p+1), *(p+2), *(p+3), 0);
			::LowercaseText(str, 3, (ScriptCode)0);
			sscanf(str, "%3x", &numbytes);
			newPos = oldPos + numbytes;
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
	theTGB->InstallBackStoreData((*theHandle) + oldPos , newPos - oldPos);
	theTGB->SetMaxScrollerValue();
	theTGB->InstallContentsFromLine(1);
	HUnlock(theHandle);

	WESetSelection(0, 0, theTGB->GetInMemoryWasteRef());

	// Advance the counters
	mRezStream->SetMarker(newPos, streamFrom_Start);
	mYCoord += sTgbPaneInfo.height + kTmplVertSep;
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//	¥ AddPointField													[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddPointField(SInt16 inX, 
								SInt16 inY, 
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

	sRectLabelInfo.top			= mYCoord;
	sRectLabelInfo.left 		= kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep;
	sRectLabelInfo.superView	= inContainer;

	sRectPaneInfo.top		= mYCoord + kTmplRectHeight;
	sRectPaneInfo.left		= sRectLabelInfo.left;
	sRectPaneInfo.superView	= inContainer;

	// X coord
	theStaticText = new LStaticText(sRectLabelInfo, "\pHoriz", sEditTraitsID);
	ThrowIfNil_(theStaticText);
	sRectPaneInfo.paneID = mCurrentID;
	::NumToString( (long) inX, numStr);
	theEditText = new LEditText(sRectPaneInfo, this, numStr, sEditTraitsID, 
								msg_TmplModifiedItem, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);
	theEditText->SetUserCon(inType);
	// Let the window listen to this field
	theEditText->AddListener(this);
	mCurrentID++;

	// Y coord
	sRectLabelInfo.left += kTmplRectWidth + kTmplHorizSep;
	theStaticText = new LStaticText(sRectLabelInfo, "\pVert", sEditTraitsID);
	ThrowIfNil_(theStaticText);
	sRectPaneInfo.left += kTmplRectWidth + kTmplHorizSep;
	sRectPaneInfo.paneID = mCurrentID;
	::NumToString( (long) inY, numStr);
	theEditText = new LEditText(sRectPaneInfo, this, numStr, sEditTraitsID, 
								msg_TmplModifiedItem, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);
	theEditText->SetUserCon(inType);
	// Let the window listen to this field
	theEditText->AddListener(this);
	mCurrentID++;

	// Advance the counters
	mYCoord += (kTmplRectHeight * 2) + kTmplVertSep + kTmplVertSep;
}


// ---------------------------------------------------------------------------
//	¥ AddRectField													[public]
// ---------------------------------------------------------------------------

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

	sRectLabelInfo.top			= mYCoord;
	sRectLabelInfo.left 		= kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep;
	sRectLabelInfo.superView	= inContainer;

	sRectPaneInfo.top		= mYCoord + kTmplRectHeight;
	sRectPaneInfo.left		= sRectLabelInfo.left;
	sRectPaneInfo.superView	= inContainer;

	// Top
	theStaticText = new LStaticText(sRectLabelInfo, "\pTop", sEditTraitsID);
	ThrowIfNil_(theStaticText);
	sRectPaneInfo.paneID = mCurrentID;
	::NumToString( (long) inTop, numStr);
	theEditText = new LEditText(sRectPaneInfo, this, numStr, sEditTraitsID, 
								msg_TmplModifiedItem, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);
	theEditText->SetUserCon(inType);
	// Let the window listen to this field
	theEditText->AddListener(this);
	mCurrentID++;

	// Left
	sRectLabelInfo.left += kTmplRectWidth + kTmplHorizSep;
	theStaticText = new LStaticText(sRectLabelInfo, "\pLeft", sEditTraitsID);
	ThrowIfNil_(theStaticText);
	sRectPaneInfo.left += kTmplRectWidth + kTmplHorizSep;
	sRectPaneInfo.paneID = mCurrentID;
	::NumToString( (long) inLeft, numStr);
	theEditText = new LEditText(sRectPaneInfo, this, numStr, sEditTraitsID, 
								msg_TmplModifiedItem, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);
	theEditText->SetUserCon(inType);
	// Let the window listen to this field
	theEditText->AddListener(this);
	mCurrentID++;

	// Bottom
	sRectLabelInfo.left += kTmplRectWidth + kTmplHorizSep;
	theStaticText = new LStaticText(sRectLabelInfo, "\pBottom", sEditTraitsID);
	ThrowIfNil_(theStaticText);
	sRectPaneInfo.left += kTmplRectWidth + kTmplHorizSep;
	sRectPaneInfo.paneID = mCurrentID;
	::NumToString( (long) inBottom, numStr);
	theEditText = new LEditText(sRectPaneInfo, this, numStr, sEditTraitsID, 
								msg_TmplModifiedItem, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);
	theEditText->SetUserCon(inType);
	// Let the window listen to this field
	theEditText->AddListener(this);
	mCurrentID++;

	// Right
	sRectLabelInfo.left += kTmplRectWidth + kTmplHorizSep;
	theStaticText = new LStaticText(sRectLabelInfo, "\pRight", sEditTraitsID);
	ThrowIfNil_(theStaticText);
	sRectPaneInfo.left += kTmplRectWidth + kTmplHorizSep;
	sRectPaneInfo.paneID = mCurrentID;
	::NumToString( (long) inRight, numStr);
	theEditText = new LEditText(sRectPaneInfo, this, numStr, sEditTraitsID, 
								msg_TmplModifiedItem, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);
	theEditText->SetUserCon(inType);
	// Let the window listen to this field
	theEditText->AddListener(this);
	mCurrentID++;

	// Advance the counters
	mYCoord += (kTmplRectHeight * 2) + kTmplVertSep + kTmplVertSep;
}


// ---------------------------------------------------------------------------
//	¥ AddListHeaderField											[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddListHeaderField(OSType inType, 
									  Str255 inLabel, 
									  short inCount, 
									  Str255 inCountLabel, 
									  LView * inContainer, 
									  Boolean isFixedCount)
{
	Str255			numStr;
	LStaticText *	theStaticText;
	CTmplListButton *	thePushButton;
	
	// This is the label of the list (usually "*****")
	sStaticPaneInfo.left		= kTmplLeftMargin;
	sStaticPaneInfo.top			= mYCoord;
	sStaticPaneInfo.width		= kTmplLabelWidth;
	sStaticPaneInfo.superView	= inContainer;

	theStaticText = new LStaticText(sStaticPaneInfo, inLabel, sHeaderTraitsID);
	ThrowIfNil_(theStaticText);

	if (inType == 'LSTC') {
		mYCoord += kTmplEditHeight;
		// This is the label of the OCNT, ZCNT or FCNT counts
		sStaticPaneInfo.top		= mYCoord;
		sStaticPaneInfo.width	= kTmplLabelWidth;
		theStaticText = new LStaticText(sStaticPaneInfo, inCountLabel, sRightLabelTraitsID);
		ThrowIfNil_(theStaticText);
		
		// This is the value of the OCNT, ZCNT or FCNT counts
		sStaticPaneInfo.left 	+= sStaticPaneInfo.width + kTmplHorizSep;
		sStaticPaneInfo.width	= kTmplCountWidth;
		sStaticPaneInfo.paneID 	= mCurrentID;
		::NumToString( (long) inCount, numStr);
		theStaticText = new LStaticText(sStaticPaneInfo, numStr, sHeaderTraitsID);
		ThrowIfNil_(theStaticText);
		
		sStaticPaneInfo.paneID = 0;
		mCurrentID++;
	}
	
	sPushPaneInfo.top		= sStaticPaneInfo.top - 3;
	sPushPaneInfo.left		= sStaticPaneInfo.left + sStaticPaneInfo.width + kTmplHorizSep;
	sPushPaneInfo.paneID	= mCurrentID;
	sPushPaneInfo.superView	= inContainer;
	
	thePushButton = new CTmplListButton(sPushPaneInfo, msg_TmplMinusButton, "\p-");
	ThrowIfNil_(thePushButton);
	// Store the current position in the template stream
	thePushButton->SetUserCon( mTemplateStream->GetMarker());
	// Let the window listen to this button
	thePushButton->AddListener(this);
	if (isFixedCount) {
		thePushButton->Disable();
	} 
	mCurrentID++;
	
	sPushPaneInfo.left		+= kTmplCountWidth + kTmplHorizSep;
	sPushPaneInfo.paneID	= mCurrentID;
	thePushButton = new CTmplListButton(sPushPaneInfo, msg_TmplPlusButton, "\p+");
	ThrowIfNil_(thePushButton);
	// The UserCon field will contain a pointer to the first ListItemView. Initialize with nil.
	thePushButton->SetUserCon(nil);
	// Let the window listen to this button
	thePushButton->AddListener(this);
	if (isFixedCount) {
		thePushButton->Disable();
	} 

	mCurrentID++;

	// Advance the counters
	mYCoord += sStaticPaneInfo.height + kTmplVertSep + kTmplVertSkip;
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

	sListItemInfo.paneID			= 0;
	sListItemInfo.top				= mYCoord;
	sListItemInfo.left				= kTmplTextMargin + mIndent;
	sListItemInfo.width				= theFrame.width - sListItemInfo.left - kTmplHorizSep;
	sListItemInfo.superView			= inContainer;
	
	CTmplListItemView * theLIV = new CTmplListItemView(sListItemInfo, theViewInfo, false);
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
	sSeparatorPaneInfo.left			= kTmplLabelWidth + kTmplLeftMargin;
	sSeparatorPaneInfo.top			= mYCoord;
	sSeparatorPaneInfo.width		= theFrame.width - kTmplLabelWidth - kTmplLeftMargin * 2;
	sSeparatorPaneInfo.superView	= inContainer;

	LSeparatorLine * theSeparator = new LSeparatorLine(sSeparatorPaneInfo);
	ThrowIfNil_(theSeparator);
	
	// Advance the counters
	mYCoord += sSeparatorPaneInfo.height + kTmplVertSep;
}


// ---------------------------------------------------------------------------
//	¥ AddCasePopup													[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddCasePopup(ResType inType, Str255 inLabel, SInt32 inStartMark, LView * inContainer)
{
	register char *	p;
	SDimension16	theFrame;
	SInt16			index = 1;
	ResType			theType;
	SInt32			currMark, theLength = mTemplateStream->GetLength();
	Str255			theString;
	char 			charString[256];

	inContainer->GetFrameSize(theFrame);
	sBevelPaneInfo.left			= theFrame.width - sBevelPaneInfo.width - 5;
	sBevelPaneInfo.top			= mYCoord - sEditPaneInfo.height -kTmplVertSep -1;
	sBevelPaneInfo.paneID		= mCurrentID;
	sBevelPaneInfo.superView	= inContainer;

	CTmplBevelButton * theBevelButton = new CTmplBevelButton(sBevelPaneInfo, msg_TmplCasePopup, kControlBevelButtonSmallBevelProc,
													 rMENU_TemplateCases, kControlBevelButtonMenuOnBottom, 
													 kControlContentTextOnly, 0, 0, Str_Empty, 1, 
													 kControlBevelButtonPlaceNormally, teFlushDefault, 0, 
													 kControlBevelButtonAlignCenter, Point_00, true);													 
	ThrowIfNil_(theBevelButton);

	// Let the window listen to this menu
	theBevelButton->AddListener(this);
	
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
	// Store the position mark of the first CASE in the userCon of the edit field
	theEditText->SetUserCon(inStartMark);
	
	// Advance the counters. mYCoord has already been increased by the edit field
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//	¥ AddEditPopup													[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddEditPopup(Str255 inValue, 
								OSType inType,
								SInt16 inMaxChars, 
								SInt16 inWidth,
								UInt8 inAttributes,
								TEKeyFilterFunc inKeyFilter, 
								ResIDT inResourceID,
								LView * inContainer)
{
	register char *	p;
	SDimension16	theFrame;
	SInt16			index = 1;
	SInt32			theLength = mTemplateStream->GetLength();
	Str255			theString;
	char 			charString[256];

	inContainer->GetFrameSize(theFrame);

	sEditPaneInfo.left		= kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep;
	sEditPaneInfo.width		= inWidth;
	sEditPaneInfo.top		= mYCoord - 3;
	sEditPaneInfo.paneID	= mCurrentID;
	sEditPaneInfo.superView	= inContainer;

	LEditText * theEditText = new LEditText(sEditPaneInfo, this, inValue, sEditTraitsID, 
											msg_TmplModifiedItem, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);

	// Store the template's type in the userCon field
	theEditText->SetUserCon(inType);
	
	// Let the window listen to this field
	theEditText->AddListener(this);

	// Incr the pane ID
	mCurrentID++;

	// Now build the popup
	sBevelPaneInfo.left			= sEditPaneInfo.left + inWidth + kTmplHorizSep;
	sBevelPaneInfo.top			= sEditPaneInfo.top + 2;
	sBevelPaneInfo.paneID		= mCurrentID;
	sBevelPaneInfo.superView	= inContainer;

	CTmplBevelButton * theBevelButton = new CTmplBevelButton(sBevelPaneInfo, msg_TmplPopupField, kControlBevelButtonSmallBevelProc,
													 rMENU_TemplateCases, kControlBevelButtonMenuOnBottom, 
													 kControlContentTextOnly, 0, 0, Str_Empty, 1, 
													 kControlBevelButtonPlaceNormally, teFlushDefault, 0, 
													 kControlBevelButtonAlignCenter, Point_00, true);													 
	ThrowIfNil_(theBevelButton);

	// Let the window listen to this menu
	theBevelButton->AddListener(this);
	
	// Populate the popup with the items from the STR# resource with ID inResourceID
	while (true) {
		GetIndString(theString, inResourceID, index);
		if (theString[0]) {
			CopyPascalStringToC(theString, charString);
			p = strrchr((char *) charString, '=');
			if (p != nil) {
				theString[0] = p - (char *) charString;
				theBevelButton->InsertMenuItem(theString, index, true);
			} 
			index++;
		} else {
			break;
		}
	} 
	
	// Store a pointer to the associated edit field
	theBevelButton->SetUserCon( (long) theEditText);
	// Store the STR# resource ID in the userCon of the edit field
	theEditText->SetUserCon(inResourceID);
	
	// Advance the counters
	mYCoord += sEditPaneInfo.height + kTmplVertSep;
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
		
		if (theType == 'OCNT' || theType == 'WCNT' || theType == 'ZCNT' 
			|| theType == 'FCNT' || theType == 'LCNT' || theType == 'LZCT') {
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
	char 	formatString[16];
	long	theLong;
	Str255	numStr, typeStr, theString;
	SInt32	theLength, reqLength, currMark, oldMark;
	UInt8	theUInt8 = 0;
	UInt16	theUInt16 = 0, bitCount = 0, bytesLen = 0;;
	UInt32	theUInt32 = 0;
	SInt8	i;
	OSType	theOSType;
	ResType	theType;
	LRadioGroupView *	theRGV;
	LStaticText	*		theStaticText;
	LEditText *			theEditText;
	LCheckBox *			theCheckBox;
	CWasteEditView *	theWasteEdit;
	PaneIDT			theCurrentRadioID;
	Handle			theHandle;
	StHandleLocker	locker(nil);
	CFStringRef		formatStr = NULL, messageStr = NULL;

	formatString[0] = 0;
	
	switch (inType) {
		case 'ALNG':
		// Long align
		AlignBytesWrite(4);
		break;

		case 'AL08':
		// Align to 8-byte boundary
		AlignBytesWrite(8);
		break;

		case 'AL16':
		// Align to 16-byte boundary
		AlignBytesWrite(16);
		break;

		case 'AWRD':
		// Word align
		AlignBytesWrite(2);
		break;

		case 'ALRT':
		// Posted an alert. Just skip.
		break;

		case 'BBIT':
		// Binary bit within a byte
		RetrieveBitField(1, 1);
		break;

		case 'BCNT':
		// Byte count for LSTC lists
		theStaticText = dynamic_cast<LStaticText *>(this->FindPaneByID(mCurrentID));
		theStaticText->GetDescriptor(theString);	
		::StringToNum( theString, &theLong);
		*mOutStream << (UInt8) theLong;
		if (theLong > 7) {
			theLong = 7;
		} 
		mItemsCount = (UInt16) theLong;
		mCurrentID++;
		break;

		case 'BFLG':
		// Boolean (one byte: 0x01 for true, 0x00 for false)
		theCheckBox = dynamic_cast<LCheckBox *>(this->FindPaneByID(mCurrentID));
		*mOutStream << (UInt8) theCheckBox->GetValue();
		mCurrentID++;
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
		// The RGV and both radiobuttons have an ID. That makes three.
		mCurrentID += 3;
		break;

		case 'BSIZ':
		case 'BSKP':
		// Offset to SKPE in byte (BSIZ:exclusive or BSKP:inclusive)
		// Cache the current position
		mOffsetMarksList.AddItem(mOutStream->GetMarker());
		// Temporarily fill with null to create the place holder
		*mOutStream << (UInt8) 0x00;
		break;

		case 'CASE':
		// Increment the current pane ID to skip the case popup
		mCurrentID++;
		// Skip the next CASE statements
		currMark = mTemplateStream->GetMarker();
		theLength = mTemplateStream->GetLength();
		while (currMark < theLength) {
			*mTemplateStream >> theString;
			*mTemplateStream >> theType;
			if (theType != inType) {
				// We went too far. Reposition the stream marker.
				mTemplateStream->SetMarker(currMark, streamFrom_Start);
				break;
			} 
			currMark = mTemplateStream->GetMarker();
		}
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

		case 'DATE':
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(numStr);	
		if ( ! UMiscUtils::ParseDateString(numStr, &theUInt32)) {
			error = err_TmplParseDateFailed;
		} 
		*mOutStream << theUInt32;
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

		case 'DVDR':
		// Divider line. Just skip it.
		break;

		case 'DWRD':
		case 'RSID':
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
		case 'HBYT':
		// Hex byte
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(numStr);	
		CopyPascalStringToC(numStr, charString);
		::LowercaseText(charString, strlen(charString), (ScriptCode)0);
		error = BuildScanString(charString, formatString, 2);
		sscanf(charString, formatString, &theLong);
		*mOutStream << (UInt8) theLong;
		mCurrentID++;
		break;

		case 'HEXD':
		case 'BHEX':
		case 'BSHX':
		case 'LHEX':
		case 'LSHX':
		case 'WHEX':
		case 'WSHX': 
		// Hex dump of following bytes
		CDualDataView * theTGB = dynamic_cast<CDualDataView *>(this->FindPaneByID(mCurrentID));
		WEReference theWE = theTGB->GetInMemoryWasteRef();
		theLength = ::WEGetTextLength(theWE);
		theHandle = static_cast<Handle>(::WEGetText(theWE));
		locker.Adopt(theHandle);
		
		switch (inType) {
			case 'BHEX': {
				if (theLength > 0xff) {
					theLength = 0xff;
				} 
				*mOutStream << (UInt8) theLength;
				break;
			}
			
			case 'BSHX': {
				if (theLength >= 0xff) {
					theLength = 0xfe;
				} 
				*mOutStream << (UInt8) (theLength + 1);
				break;
			}
			
			case 'LHEX': {
				if (theLength > 0xffffffff) {
					theLength = 0xffffffff;
				} 
				*mOutStream << (UInt32) theLength;
				break;
			}
			
			case 'LSHX': {
				if (theLength >= 0xffffffff) {
					theLength = 0xfffffffb;
				} 
				*mOutStream << (UInt32) (theLength + 4);
				break;
			}
			
			case 'WHEX': {
				if (theLength > 0xffff) {
					theLength = 0xffff;
				} 
				*mOutStream << (UInt16) theLength;
				break;
			}
			
			case 'WSHX': {
				if (theLength >= 0xffff) {
					theLength = 0xfffd;
				} 
				*mOutStream << (UInt16) (theLength + 2);
				break;
			}
		}	
		
		mOutStream->PutBytes(*theHandle, theLength);
		mCurrentID++;
		break;

		case 'FLNG':
		case 'HLNG':
		// Hex long word
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(numStr);	
		CopyPascalStringToC(numStr, charString);
		::LowercaseText(charString, strlen(charString), (ScriptCode)0);
		error = BuildScanString(charString, formatString, 8);
		sscanf(charString, formatString, &theLong);
		*mOutStream << (UInt32) theLong;
		mCurrentID++;
		break;

		case 'FWRD':
		case 'HWRD':
		// Hex word
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(numStr);	
		CopyPascalStringToC(numStr, charString);
		::LowercaseText(charString, strlen(charString), (ScriptCode)0);
		error = BuildScanString(charString, formatString, 4);
		sscanf(charString, formatString, &theLong);
		*mOutStream << (UInt16) theLong;
		mCurrentID++;
		break;

		case 'LABL':
		// It is a comment. Just skip it.
		break;

		case 'LBIT':
		// Binary bit within a long
		RetrieveBitField(1, 4);
		break;

		case 'LCNT':
		// One-based long count for LSTC lists
		theStaticText = dynamic_cast<LStaticText *>(this->FindPaneByID(mCurrentID));
		theStaticText->GetDescriptor(theString);	
		::StringToNum( theString, &theLong);
		if (theLong < 0xffff) {
			mItemsCount = theLong;
		} else {
			error = err_TmplListCountTooBig;
		}
		*mOutStream << theLong;
		mCurrentID++;
		break;

		case 'LFLG':
		// Long Boolean flag in low-order bit (four bytes: 0x00000001 for true,
		// 0x00000000 for false)
		theRGV = dynamic_cast<LRadioGroupView *>(this->FindPaneByID(mCurrentID));
		theCurrentRadioID = theRGV->GetCurrentRadioID();
		if ( (theCurrentRadioID - mCurrentID) % 2 ) {
			*mOutStream << (UInt32) 0x00000001;
		} else {
			*mOutStream << (UInt32) 0x00000000;
		}
		// The RGV and both radiobuttons have an ID. That makes three.
		mCurrentID += 3;
		break;

		case 'LSIZ':
		case 'LSKP':
		// Offset to SKPE in long (LSIZ:exclusive or LSKP:inclusive)
		// Cache the current position
		mOffsetMarksList.AddItem(mOutStream->GetMarker());
		// Temporarily fill with null to create the place holder
		*mOutStream << 0L;
		break;

		case 'LNGC':
		case 'RGNC':
		case 'SCPC': 
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(numStr);	
		::StringToNum( numStr, &theLong);
		*mOutStream << (SInt16) theLong;
		// Skip the field and bevel popup button
		mCurrentID += 2;
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
		// Long string (long  length followed by the characters)
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
		
		case 'LZCT':
		// Zero-based count for LSTC lists
		theStaticText = dynamic_cast<LStaticText *>(this->FindPaneByID(mCurrentID));
		theStaticText->GetDescriptor(theString);	
		::StringToNum( theString, &theLong);
		mItemsCount = (UInt16) theLong;
		if (theLong < 0xffff) {
			if (!theLong) {
				theUInt16 = 0xffff;
			} else {
				theUInt16 = (UInt16) --theLong;
			}
			*mOutStream << theUInt16;
		} else {
			error = err_TmplListCountTooBig;
		}
		mCurrentID++;
		break;

		case 'OCNT':
		case 'FCNT':
		case 'WCNT':
		// One-based count for LSTC lists
		theStaticText = dynamic_cast<LStaticText *>(this->FindPaneByID(mCurrentID));
		theStaticText->GetDescriptor(theString);	
		::StringToNum( theString, &theLong);
		mItemsCount = (UInt16) theLong;
		if (inType != 'FCNT') {
			*mOutStream << mItemsCount;
		} 
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

		case 'PNT ':
		// An 4-byte point
		for (i = 0; i < 2; i++) {
			theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
			theEditText->GetDescriptor(numStr);	
			::StringToNum( numStr, &theLong);
			*mOutStream << (SInt16) theLong;
			mCurrentID++;
		}
		break;

		case 'PPST': 
		// Pascal string padded to even length (including the padd)
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(theString);
		theLength = theString[0];
		if (theLength % 2 == 0) {
			// if the length is even, padd the string with a NULL byte.
			theString[0] = theLength + 1;
			theString[theLength] = 0;
		} 
		*mOutStream << theString;
		mCurrentID++;
		break;

		case 'PSTR':
		case 'BSTR':
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

		case 'SKPE':
		// End of Skip or Sizeof.
		currMark = mOutStream->GetMarker();
		if (mOffsetTypesList.RemoveLastItem(theType) && mOffsetMarksList.RemoveLastItem(oldMark)) {
			theLength = currMark - oldMark;
			mOutStream->SetMarker(oldMark, streamFrom_Start);
			switch (theType) {
				case 'BSIZ':
				theLength -= 1;
				*mOutStream << (UInt8) theLength;;
				break;
				
				case 'BSKP':
				*mOutStream << (UInt8) theLength;;
				break;
				
				case 'LSIZ':
				theLength -= 4;
				*mOutStream << (UInt32) theLength;;
				break;
				
				case 'LSKP':
				*mOutStream << (UInt32) theLength;;
				break;
				
				case 'WSIZ':
				theLength -= 2;
				*mOutStream << (UInt16) theLength;;
				break;
				
				case 'WSKP':
				*mOutStream << (UInt16) theLength;;
				break;
				
			}
			mOutStream->SetMarker(currMark, streamFrom_Start);
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

		case 'UBYT':
		// Unsigned decimal byte
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(numStr);	
		::StringToNum( numStr, &theLong);
		*mOutStream << (UInt8) theLong;
		mCurrentID++;
		break;

		case 'ULNG':
		// Unsigned decimal long word
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(numStr);	
		::StringToNum( numStr, &theLong);
		*mOutStream << (UInt32) theLong;
		mCurrentID++;
		break;

		case 'UWRD':
		// Unsigned decimal word
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(numStr);	
		::StringToNum( numStr, &theLong);
		*mOutStream << (UInt16) theLong;
		mCurrentID++;
		break;

		case 'WBIT':
		// Binary bit within a word
		RetrieveBitField(1, 2);
		break;

		case 'WFLG':
		// Word Boolean flag in low-order bit (two bytes: 0x0001 for true, 0x0000 for false)
		theRGV = dynamic_cast<LRadioGroupView *>(this->FindPaneByID(mCurrentID));
		theCurrentRadioID = theRGV->GetCurrentRadioID();
		if ( (theCurrentRadioID - mCurrentID) % 2 ) {
			*mOutStream << (UInt16) 0x0001;
		} else {
			*mOutStream << (UInt16) 0x0000;
		}
		// The RGV and both radiobuttons have an ID. That makes three.
		mCurrentID += 3;
		break;

		case 'WSIZ':
		case 'WSKP':
		// Offset to SKPE in word (WSIZ:exclusive or WSKP:inclusive)
		// Cache the current position
		mOffsetMarksList.AddItem(mOutStream->GetMarker());
		// Temporarily fill with null to create the place holder
		*mOutStream << (UInt16) 0x0000;;
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
		// Zero-based count for LSTC lists
		theStaticText = dynamic_cast<LStaticText *>(this->FindPaneByID(mCurrentID));
		theStaticText->GetDescriptor(theString);	
		::StringToNum( theString, &theLong);
		mItemsCount = (UInt16) theLong;
		if (!theLong) {
			theUInt16 = 0xffff;
		} else {
			theUInt16 = (UInt16) --theLong;
		}
		*mOutStream << theUInt16;
		mCurrentID++;
		break;

	  default:
	  UMiscUtils::OSTypeToPString(inType, typeStr);
	  // Handle Hnnn, Cnnn, P0nn, BB0n etc cases here or unrecognized type
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

	  } else if ( IsValidBitField(inType, typeStr, bitCount, bytesLen) ) {
		  
		  RetrieveBitField(bitCount, bytesLen);
		  
	  } else {
		  // Unrecognized type
		  UMessageDialogs::AlertForType(CFSTR("UnknownTemplateType"), inType);
	  }
	  break;
	}

	return error;
}


// ---------------------------------------------------------------------------
//	¥ RetrieveBitField											[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::RetrieveBitField(UInt16 inBitCount, UInt16 inBytesLen)
{
	UInt16	i, val;
	long	theLong;
	Str255	numStr;
	
	if (!mBitSeqInProgress) {
		mBitSeqInProgress = true;
		// High bit first.
		mBitSeqIndex = mBitSeqBytesLen * 8 - 1;
		mBitSeqBytesLen = inBytesLen;
		mBitSeqValue = 0;
	} 
	
	if (inBitCount == 1) {
		LCheckBox * theCheckBox = dynamic_cast<LCheckBox *>(this->FindPaneByID(mCurrentID));
		mBitSeqValue |= theCheckBox->GetValue() ? 1 << mBitSeqIndex : 0 ;
		mBitSeqIndex--;
	} else {
		LEditText * theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(numStr);	
		::StringToNum( numStr, &theLong);
		
		for (i = inBitCount - 1; i >= 0 ; i--) {
			val = theLong & 1 << i;
			mBitSeqValue |= val ? 1 << mBitSeqIndex : 0 ;
			mBitSeqIndex--;
		}		
	}
	
	mCurrentID++;
	
	if (mBitSeqIndex < 0) {
		mBitSeqInProgress = false;
		*mOutStream << mBitSeqValue;
	} 
}


