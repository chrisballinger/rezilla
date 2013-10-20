// ===========================================================================
// CTmplEditorWindow.cp					
// 
//                       Created: 2004-06-12 15:08:01
//             Last modification: 2006-09-18 18:52:35
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes, 2004-2006
// All rights reserved.
// ===========================================================================


#include "CTmplEditorWindow.h"
#include "CTmplEditorDoc.h"
#include "CTmplListItemView.h"
#include "CTmplListButton.h"
#include "CFlagPopup.h"
#include "CTemplatesController.h"
#include "CRezMapTable.h"
#include "CRezMap.h"
#include "CRezObj.h"
#include "CRezillaApp.h"
#include "CRezillaPrefs.h"
#include "CDualDataView.h"
#include "CHexDataSubView.h"
#include "CSingleScrollBar.h"
#include "CTxtDataSubView.h"
#include "CWasteEditView.h"
#include "CColorWell.h"
#include "UMiscUtils.h"
#include "UMessageDialogs.h"
#include "UHexFilters.h"
#include "UCodeTranslator.h"

#include <LScrollBar.h>
#include <LStaticText.h>
#include <LEditText.h>
#include <LTextGroupBox.h>
#include <LCheckBox.h>
#include <LPushButton.h>
#include <LScrollerView.h>
#include <LSeparatorLine.h>
#include <UDrawingState.h>
#include <LArray.h>
#ifndef __MACH__
#include <ControlDefinitions.h>
#endif

#ifndef __MACH__
#include <CFDateFormatter.h>
#endif


#include <stdio.h>
#include <string.h>

// Statics
ResIDT CTmplEditorWindow::sCommentTraitsID = Txtr_MonacoBlueNineCenter;
ResIDT CTmplEditorWindow::sLeftLabelTraitsID = Txtr_GenevaTenBoldLeft;
ResIDT CTmplEditorWindow::sRightLabelTraitsID = Txtr_GenevaTenBoldRight;
ResIDT CTmplEditorWindow::sEditTraitsID = Txtr_MonacoNineDefault;
ResIDT CTmplEditorWindow::sHeaderTraitsID = Txtr_GenevaTenBoldUl;
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
SPaneInfo CTmplEditorWindow::sColorPaneInfo;
SPaneInfo CTmplEditorWindow::sPopupPaneInfo;

// ---------------------------------------------------------------------------
//   CTmplEditorWindow				[public]
// ---------------------------------------------------------------------------

CTmplEditorWindow::CTmplEditorWindow()
{
	SetModelKind(rzom_cTmplWindow);
	mFlipped = false;
}


// ---------------------------------------------------------------------------
//   CTmplEditorWindow				[public]
// ---------------------------------------------------------------------------

CTmplEditorWindow::CTmplEditorWindow(
	const SWindowInfo &inWindowInfo )
		: CEditorWindow( inWindowInfo )
{
	SetModelKind(rzom_cTmplWindow);
	mFlipped = false;
}


// ---------------------------------------------------------------------------
//   CTmplEditorWindow				[public]
// ---------------------------------------------------------------------------

CTmplEditorWindow::CTmplEditorWindow(
	ResIDT		inWINDid,
	UInt32		inAttributes,
	LCommander	*inSuperCommander )
		: CEditorWindow( inWINDid, inAttributes, inSuperCommander )
{
	SetModelKind(rzom_cTmplWindow);
	mFlipped = false;
}


// ---------------------------------------------------------------------------
//   CTmplEditorWindow				[public]
// ---------------------------------------------------------------------------

CTmplEditorWindow::CTmplEditorWindow(
			       LStream *inStream )
		: CEditorWindow( inStream )
{
	SetModelKind(rzom_cTmplWindow);
	mFlipped = false;
}


// ---------------------------------------------------------------------------
//     ~CTmplEditorWindow				[public]
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
//   FinishCreateSelf				[protected]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::FinishCreateSelf()
{	
	mCurrentID			= 1;
	mPaneIndex			= 1;
	mLastID				= 0;
	mListCount			= 0;
	mIndent				= 0;
	mSkipOffset			= 0;
	mListCountMark		= 0;
	mBitSeqInProgress	= false;
	mBitSeqValue		= 0;
	mBitSeqBytesLen		= 0;
	mBitSeqIndex		= 0;
	mFixedCount			= false;
	mYCoord             = kTmplVertSkip;
	mSelectedListItem	= nil;
	mTemplateStream		= nil;
	mRezStream			= nil;
	mOutStream			= nil;
	mRectFormat			= CRezillaApp::sPrefs->GetPrefValue(kPref_templates_rectFormat);
	
	// The main view containing the labels and editing panes
	mContentsView = dynamic_cast<LView *>(this->FindPaneByID(item_EditorContents));
	ThrowIfNil_( mContentsView );
	
	// Set the initial size of the image to mYCoord (= kTmplVertSkip)
	mContentsView->ResizeImageTo(0, mYCoord, false);
	
	// The scroller controlling the contents view
	mContentsScroller = dynamic_cast<LScrollerView *>(this->FindPaneByID(item_EditorScroller));
	ThrowIfNil_( mContentsScroller );
		
// 	// Install the name of the resource if it has one
// 	LStaticText * theStaticText = dynamic_cast<LStaticText *>(this->FindPaneByID( item_NameStaticText ));
// 	ThrowIfNil_( theStaticText );
// 	Str255 * strPtr = dynamic_cast<CTmplEditorDoc *>(GetSuperCommander())->GetRezObj()->GetName();
// 	theStaticText->SetDescriptor(*strPtr);	
	
	// Link to the broadcasters
	UReanimator::LinkListenerToControls( this, this, PPob_TmplEditorWindow );
	
	// Make the window a listener to the prefs object
	CRezillaApp::sPrefs->AddListener(this);

	InitPaneInfos();
	
}
	

// ---------------------------------------------------------------------------
//   Draw
// ---------------------------------------------------------------------------
// After redrawing the entire window, draw a border around a possible
// selected CTmplListItemView.

void
CTmplEditorWindow::Draw( RgnHandle inSuperDrawRgnH )
{
	LWindow::Draw(inSuperDrawRgnH);
	// Draw border if necessary
	if (mSelectedListItem != NULL) {
		mSelectedListItem->DrawBorder();
	} 
}


// ---------------------------------------------------------------------------
//   ListenToMessage											[public]
// ---------------------------------------------------------------------------
// The Plus button stores a pointer to the first list item in its UserCon
// field. The Minus button stores the marker to the beginning of the list
// template. The position four chars before the template stream's marker
// corresponds to the type of the list.

void
CTmplEditorWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{	
	Rect				theFrame;
	CTmplListItemView 	*prevListItemView, *nextListItemView, *currListItemView;
	CTmplListButton 	*theMinusButton, *thePlusButton;
	PaneIDT 			thePaneID, saveID;
	LView				*theContainer, *theView;
	SInt32 				startMark, theHeight;
	ResType				theType;
	int					sublevel = 1;

	saveID = mCurrentID;
	
	switch (inMessage) {
		
		case msg_MinusButton: {
			theMinusButton = (CTmplListButton *) ioParam;
			// ZP bugfix #5: even if the minus and plus buttons are hidden
			// in the case of a fixed count list, we can still receive this
			// message when the user hits delete, so break out if the minus
			// button is hidden.
			if ( !theMinusButton->IsVisible()) break;

			thePaneID = theMinusButton->GetPaneID();
			thePlusButton = dynamic_cast<CTmplListButton *>(this->FindPaneByID(thePaneID + 1));
			ThrowIfNil_(thePlusButton);
			
			startMark = theMinusButton->GetUserCon();
			theContainer = thePlusButton->GetSuperView();
			currListItemView = (CTmplListItemView *) thePlusButton->GetUserCon();
			
			if (currListItemView) {
				// Find the list item to remove: if an item is selected,
				// remove it, otherwise remove the last item in the list
				if (currListItemView != mSelectedListItem) {
					while (currListItemView->mNextItem) {
						currListItemView = currListItemView->mNextItem;
						if (currListItemView == mSelectedListItem) {
							mSelectedListItem = NULL;
							break;
						}
					}
				} else {
					mSelectedListItem = NULL;
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
			
			// Update the value of the counter
			mTemplateStream->SetMarker(startMark-4, streamFrom_Start);
			*mTemplateStream >> theType;
			AdjustCounterField(thePaneID - 1, -1);

			// Adjust all IDs and positions
			AdjustListOfPaneIDs(currListItemView, currListItemView->mFirstItemID, 0, false);
			theContainer->PortToLocalPoint(topLeft(theFrame));
			RecalcPositions(currListItemView, theFrame.top, -theHeight);
			mLastID = mPaneIDs.GetCount();

			// Adjust the chain
			prevListItemView = currListItemView->mPrevItem;
			nextListItemView = currListItemView->mNextItem;
			if (nextListItemView) {
				nextListItemView->mPrevItem = prevListItemView;
			} 
			if (prevListItemView) {
				prevListItemView->mNextItem = nextListItemView;
			} else {
				// We're about to delete the first list item.
				thePlusButton->SetUserCon( (long) nextListItemView);
			}
			
			// Now delete the object
			delete currListItemView;
			
			mContentsView->ResizeImageBy(0, -theHeight, true);
			mContentsView->Refresh();

			// Window has been modified
			SetDirty(true);
			break;
		}
		
		case msg_PlusButton:
			thePlusButton = (CTmplListButton *) ioParam;
			// ZP bugfix #5: see comment with msg_MinusButton
			if ( !thePlusButton->IsVisible()) break;

			thePaneID = thePlusButton->GetPaneID();
			theMinusButton = dynamic_cast<CTmplListButton *>(this->FindPaneByID(thePaneID - 1));
			ThrowIfNil_(theMinusButton);
			
			// Retrieve cached data
			startMark = theMinusButton->GetUserCon();
			theContainer = thePlusButton->GetSuperView();
			currListItemView = (CTmplListItemView *) thePlusButton->GetUserCon();
			
			if (currListItemView) {
				// If an item is selected, the new item will be inserted
				// before it, otherwise it is added at the end of the list
				if (currListItemView != mSelectedListItem) {
					while (currListItemView->mNextItem) {
						if (currListItemView->mNextItem == mSelectedListItem) {
							break;
						}
						currListItemView = currListItemView->mNextItem;
					}
					nextListItemView = currListItemView->mNextItem;
					currListItemView->CalcPortFrameRect(theFrame);
				} else {
					// The first item is selected
					nextListItemView = currListItemView;
					currListItemView = NULL;
					thePlusButton->CalcPortFrameRect(theFrame);
				}
			} else {
				nextListItemView = NULL;
				thePlusButton->CalcPortFrameRect(theFrame);
			}
			
			// Calculate the insertion position of the new list item
			theContainer->PortToLocalPoint(botRight(theFrame));
			mYCoord = theFrame.bottom + kTmplVertSkip;
			if (!currListItemView) {
				mYCoord += kTmplVertSep;
			} 
			prevListItemView = currListItemView;

			mContentsView->Hide();
			
			theView = theContainer;
			while (theView != mContentsView && theView != nil) {
				theView = theView->GetSuperView();
				sublevel++;
			}
			mIndent += kTmplListIndent * sublevel;

			currListItemView = AddListItemView(prevListItemView, nextListItemView, theMinusButton, theContainer);
			if (prevListItemView == nil) {
				thePlusButton->SetUserCon( (long) currListItemView);
			} 
			mYCoord = kTmplVertSep;
			DoParseWithTemplate(startMark, true, currListItemView);
			if (mYCoord < kTmplMinListItemHeight) {
				mYCoord = kTmplMinListItemHeight;
			} 
			currListItemView->ResizeFrameBy(0, mYCoord, false);

			mIndent -= kTmplListIndent * sublevel;

			// Update the value of the counter
			mTemplateStream->SetMarker(startMark-4, streamFrom_Start);
			*mTemplateStream >> theType;
			AdjustCounterField(thePaneID - 2, 1);
			
			// Adjust all IDs and positions
			AdjustListOfPaneIDs(prevListItemView, thePlusButton->GetPaneID(), saveID, true);
			RecalcPositions(currListItemView, theFrame.bottom + kTmplVertSkip, mYCoord + kTmplVertSkip);
			mLastID = mPaneIDs.GetCount();

			mContentsView->ResizeImageBy(0, mYCoord + kTmplVertSkip, false);
			mContentsView->Show();
			mContentsView->Enable();
			mContentsView->Activate();
			if (mSelectedListItem != NULL) {
				mSelectedListItem->DrawBorder();
			} 
			
			// Window has been modified
			SetDirty(true);
			break;
			
			
		case msg_EditorModifiedItem:
		case msg_TmplCasePopup: 
		case msg_PopupEditField: 
			// Window has been modified
			SetDirty(true);
			break;

			
		default:
		CEditorWindow::ListenToMessage(inMessage, ioParam);
		break;
		
	}
}


// ---------------------------------------------------------------------------
//   HandleKeyPress
// ---------------------------------------------------------------------------

Boolean
CTmplEditorWindow::HandleKeyPress(
	const EventRecord&	inKeyEvent)
{
	Boolean		keyHandled	 = true;
	EKeyStatus	theKeyStatus = keyStatus_Input;
	SInt16		theKey		 = (SInt16) (inKeyEvent.message & charCodeMask);
	
	if (inKeyEvent.modifiers & cmdKey) {	// Always pass up when the command
		theKeyStatus = keyStatus_PassUp;	//   key is down
	} else {
		theKeyStatus = UKeyFilters::PrintingCharField(inKeyEvent);
	}

	switch (theKeyStatus) {
		case keyStatus_TEDelete: 
		if (mSelectedListItem != NULL) {
			// The Delete key deletes the currently selected list item, if 
			// no field has the focus. Pass the data via a message to
			// simulate a click on the Minus button. 
			ListenToMessage(msg_MinusButton, (void *) mSelectedListItem->mMinusButton);
		} 
		break;
		
		default: 
		// Enable the Enter key to simulate a click in the Validate button
		// (but not the Return button which is used in text fields and can
		// be pressed inadvertently). IsTarget()
		if (theKey == char_Enter) {
			mOwnerDoc->ListenToMessage(msg_OK, NULL);
		} else if (theKey == '+') {
			// ZP feature #8: if a list item is selected, let the "+" key
			// simulate a click on the Plus Button
			if (mSelectedListItem != NULL) {
				PaneIDT thePaneID = (mSelectedListItem->mMinusButton)->GetPaneID();
				CTmplListButton* thePlusButton = dynamic_cast<CTmplListButton*>(this->FindPaneByID(thePaneID + 1));
				this->ListenToMessage(msg_PlusButton, (void *) thePlusButton);
			}
			// end of ZP feature #8
		}
		// ZP feature #11, part 1: tabbing -- shamelessly copied from LTabGroup.cp
		// Process Tab or Shift-Tab. Pass up if there are any other
		// modifiers keys pressed.
		else if ((theKey == char_Tab) &&
		   ((inKeyEvent.modifiers & (cmdKey + optionKey + controlKey)) == 0)) {
			   if ( CRezillaPrefs::GetPrefValue(kPref_templates_enableTabKey) ) {
				   RotateTarget((inKeyEvent.modifiers & shiftKey) != 0);
			   }
		} else {
			keyHandled = LCommander::HandleKeyPress(inKeyEvent);
		}
		// end of ZP feature #11, part 1
		break;
	}
	
	return keyHandled;
}


// ---------------------------------------------------------------------------
//   RevertContents												  [public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::RevertContents()
{
	RevertWithTemplate();
	SetDirty(false);
}



#pragma mark -

// ---------------------------------------------------------------------------
//   CreateTemplateStream									[protected]
// ---------------------------------------------------------------------------

OSErr
CTmplEditorWindow::CreateTemplateStream()
{
	OSErr		error = noErr;
	Handle		theHandle;
	ResType		theType = mOwnerDoc->GetSubstType();

	if ( CTemplatesController::GetTemplateKind() == tmpl_local) {
		Str255	theName;
		UMiscUtils::OSTypeToPString(theType, theName);	
		error = mOwnerDoc->GetRezMapTable()->GetRezMap()->GetWithName('TMPL', theName, theHandle, true);
		if (error == noErr) {
			// Work with a copy of the handle
			::HandToHand(&theHandle);
		}
	} else {
		theHandle = CTemplatesController::GetTemplateHandle(theType);
	}
	
	if (theHandle == NULL) {
		error = err_TmplGetDataStreamFailed;
	} else {
		mTemplateStream = new LHandleStream(theHandle);	
	}

	return error;
}
 

// ---------------------------------------------------------------------------
//   ParseDataWithTemplate											[public]
// ---------------------------------------------------------------------------

OSErr
CTmplEditorWindow::ParseDataWithTemplate(Handle inHandle)
{
	OSErr		error = noErr;
	SInt32		oldYCoord = mYCoord;
	
	// Get a handle to the template resource and create a stream to parse it
	error = CreateTemplateStream();
	
	if (error == noErr) {
		// Create a stream to parse the data
		mRezStream = new LHandleStream(inHandle);
		mRezStream->SetNativeEndian(mFlipped);

		
		// Parse the template stream
		error = DoParseWithTemplate(0, true, mContentsView);
		
		if (error == noErr) {
			// Check that there is nothing left in the data stream
			if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
				UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("ResourceLongerThanTemplate"), PPob_SimpleMessage);
			} 
			mLastID = mCurrentID - 1;
			mContentsView->ResizeImageBy(0, mYCoord - oldYCoord, true);
			mContentsScroller->AdjustScrollBars();
		} 
	} 	
	
	return error;
}


// ---------------------------------------------------------------------------
//   DoParseWithTemplate											[public]
// ---------------------------------------------------------------------------
// If 'inRezStream' is nil, an empty template is built with default values.

OSErr
CTmplEditorWindow::DoParseWithTemplate(SInt32 inRecursionMark, Boolean inDrawControls, LView * inContainer)
{
	OSErr		error = noErr;
	Str255		theString, countLabel = "\pCount:";
	ResType		theType;
	PaneIDT		theID;

	mTemplateStream->SetMarker(inRecursionMark, streamFrom_Start);
	mFixedCount = false;
	
	while (mTemplateStream->GetMarker() < mTemplateStream->GetLength() 
		   && 
		   error == noErr) {
		*mTemplateStream >> theString;
		*mTemplateStream >> theType;
		
		if (theType == 'OCNT' || theType == 'ZCNT' || theType == 'WCNT' || theType == 'BCNT' 
			|| theType == 'FCNT' || theType == 'LCNT' || theType == 'LZCT') {
			LString::CopyPStr(theString, countLabel);
			mFixedCount = (theType == 'FCNT');
			error = ParseDataForType(theType, theString, inContainer);
		} else if (theType == 'LSTB' || theType == 'LSTC' || theType == 'LSTZ') {
			if (inDrawControls) {
				theID = AddListHeaderField(theString, mListCount, countLabel, inContainer, mFixedCount);
			} else {
				theID = 0;
			}
			error = ParseList(mTemplateStream->GetMarker(), theType, mListCount, inContainer, theID);

			// ZP bugfix #4, part 1: when KEYE is met, this means we're done
			// parsing the keyed section and the remainder should be
			// handled up in the recursion, just as with LSTE. Otherwise,
			// it doesn't work if the keyed section is in a list and there
			// are other items in the template after the list.
		} else if (theType == 'LSTE' || theType == 'KEYE') {
			// end of ZP bugfix #4, part 1

			break;
		} else {
			if (inDrawControls) {
				// Create controls according to the type declared in the template
				error = ParseDataForType(theType, theString, inContainer);
			} 
		}
		// ZP feature #9, part 5: for a RSID to have its type coming from a
		// TNAM, the RSID needs to be immediately after the TNAM, therefore
		// reset mPrevTnam if the type just handled wasn't TNAM.
		// (bd 2006-09-07) There can be CASE tags between TNAM and RSID,
		// but they were consumed in AddEditField.
		if (theType != 'TNAM') mPrevTnam = NULL;
	}

	return error;
}


// ---------------------------------------------------------------------------
//   ParseList													[public]
// ---------------------------------------------------------------------------

OSErr
CTmplEditorWindow::ParseList(SInt32 inStartMark, ResType inType, SInt32 inCount, 
							 LView * inContainer, PaneIDT inCountPaneID)
{
	OSErr	error = noErr;
	SInt32	outYCoord = mYCoord;

	CTmplListItemView * prevListItemView = nil;
	CTmplListItemView * currListItemView = nil;
	CTmplListButton * thePlusButton = nil;
	CTmplListButton * theMinusButton = nil;
	LView * theContainer = inContainer;
	SInt32	listCount;
	Boolean drawCtrl;

	if (inCountPaneID) {
		theMinusButton = dynamic_cast<CTmplListButton *>(this->FindPaneByID(inCountPaneID + 1));
		ThrowIfNil_(theMinusButton);
		thePlusButton = dynamic_cast<CTmplListButton *>(this->FindPaneByID(inCountPaneID + 2));		
		ThrowIfNil_(thePlusButton);
	} 
	mIndent += kTmplListIndent;
	
	switch (inType) {
		case 'LSTB':
		case 'LSTZ': 
		listCount = 0;
		drawCtrl = true;
		
		if ( EndOfList(inType, &error) ) {
			if (error == noErr) {
				drawCtrl = false;
			} else {
				return error;
			}
		} 
		do {
			if (drawCtrl) {
				listCount++;
				currListItemView = AddListItemView(prevListItemView, NULL, theMinusButton, inContainer);
				prevListItemView = currListItemView;
				theContainer = currListItemView;
				if (thePlusButton->GetUserCon() == nil) {
					thePlusButton->SetUserCon( (long) currListItemView);
				} 
				mYCoord = kTmplVertSep;
			}
			error = DoParseWithTemplate(inStartMark, drawCtrl, theContainer);
			if (error != noErr) {
				return error;
			} 
			if (drawCtrl) {
				if (mYCoord < kTmplMinListItemHeight) {
					mYCoord = kTmplMinListItemHeight;
				} 
				currListItemView->ResizeFrameBy(0, mYCoord, false);
				outYCoord += mYCoord + kTmplVertSkip;
				mYCoord = outYCoord;
			} 
		} while (! EndOfList(inType, &error) );
		if (error && !drawCtrl) {
			// If we create a new resource, the previous call to EndOfList() 
			// will report an error since we are positioned at the end of
			// the RezStream. Ignore it: a malformed resource would already
			// have been detected by the first call to EndOfList() above.
			error = noErr;
		} 
		if (error == noErr && inCountPaneID != 0) {
			AdjustCounterField(inCountPaneID, listCount);
		} 
		break;
		
		case 'LSTC':
		if (inCount == 0) {
			error = DoParseWithTemplate(inStartMark, false, theContainer);
		} else {
			for (short i = 0 ; i < inCount && error == noErr; i++) {
				currListItemView = AddListItemView(prevListItemView, NULL, theMinusButton, inContainer);
				prevListItemView = currListItemView;
				theContainer = currListItemView;
				if (thePlusButton->GetUserCon() == nil) {
					thePlusButton->SetUserCon( (long) currListItemView);
				} 
				mYCoord = kTmplVertSep;
				error = DoParseWithTemplate(inStartMark, true, theContainer);
				if (mYCoord < kTmplMinListItemHeight) {
					mYCoord = kTmplMinListItemHeight;
				} 
				currListItemView->ResizeFrameBy(0, mYCoord, false);
				outYCoord += mYCoord + kTmplVertSkip;
				mYCoord = outYCoord;
			}
		}
		break;
		
	}
	
	mIndent -= kTmplListIndent;
	mYCoord += kTmplVertSep;
	
	return error;
}


// ---------------------------------------------------------------------------
//   EndOfList													[public]
// ---------------------------------------------------------------------------

Boolean
CTmplEditorWindow::EndOfList(ResType inType, OSErr * outError)
{
	Boolean result = false;

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
		if ( mRezStream->GetMarker() >= mRezStream->GetLength() - 1 ) {
			UInt8	theChar;
			
			result = true;
			// An LSTZ list must be terminated by a NULL
			if ( mRezStream->GetLength() > 0 ) {
				if (mRezStream->GetMarker() == mRezStream->GetLength() - 1) {
					*mRezStream >> theChar;
					if (theChar != 0) {
						*outError = err_TmplZeroListEndingWithNonNull;
					}
				} else {
					*outError = err_TmplZeroListNotTerminated;
				}
			}
		} 
		break;
		
	}
	return result;
}


// ---------------------------------------------------------------------------
//   ParseKeyedSection												[private]
// ---------------------------------------------------------------------------

OSErr
CTmplEditorWindow::ParseKeyedSection(ResType inType, Str255 inLabelString, LView * inContainer)
{
	OSErr		error = noErr;
	Str255		keyString;
	SInt32		sectionStart;
	
	// Get the key value
	if (mRezStream->GetMarker() < mRezStream->GetLength()) {
		KeyValueToString(inType, keyString);
		// Skip all the CASE statements
		SkipNextKeyCases(0);
	} else {
		error = SelectKeyValueFromKeyCases(inLabelString, keyString);
		if (error == noErr) {
			error = KeyStringToValue(inType, keyString);
		}
		if (error != noErr) {
			return error;
		}
	}
	
	// Store the current ID
	mKeyIDs.AddItem(mCurrentID);
	
	// Find the corresponding KEYB tag
	error = FindKeyStartForValue(inType, keyString, &sectionStart);
	
	if (error == noErr) {
		// Parse the section
		LStr255		caseString(inLabelString);
		caseString += "\p: ";
		caseString.Append(keyString);
		AddStaticField(inType, caseString, inContainer, sLeftLabelTraitsID, 0, true);
		mYCoord += kTmplLabelVertSkip;
		error = DoParseWithTemplate(sectionStart, true, inContainer);
	} 

	// NB: the following KEYB-KEYE segments in the template stream (remaining
	// cases) will be skipped when met by the ParseDataForType() function.
	
	return error;
}


// ---------------------------------------------------------------------------
//   ParseDataForType												[private]
// ---------------------------------------------------------------------------

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
	SInt32	theSInt32 = 0, theLength, reqLength;
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
		mListCount = theUInt8;
		break;

		case 'BFLG':
		// Boolean (one byte: 0x01 for true, 0x00 for false)
		if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
			*mRezStream >> theBool;
		} 
		AddStaticField(inType, inLabelString, inContainer);
		AddCheckField( theBool, inType, inContainer);		
		break;

		case 'BORV':
		// Binary byte made of the OR of base-2 values
		if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
			*mRezStream >> theUInt8;
		} 
		AddStaticField(inType, inLabelString, inContainer);
		AddFlagPopup(inType, inLabelString, theUInt8, inContainer);
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
		break;

		case 'CASE':
		// Switch with predefined values. These tags are consumed by 
		// AddEditField() or AddFlagPopup() but are not handled by 
		// AddBooleanField() for instance. Just ignore.
		// // error = err_TmplIsolatedCaseTag;
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

		case 'COLR': {
			// QuickDraw color RGB triplet
			RGBColor theRGB = {0,0,0};
			if (mRezStream->GetMarker() < mRezStream->GetLength() - 5) {
				*mRezStream >> theRGB.red;
				*mRezStream >> theRGB.green;
				*mRezStream >> theRGB.blue;
			} 
			AddStaticField(inType, inLabelString, inContainer);
			AddColorPane(inContainer, &theRGB);		
			break;
		}

		// ZP feature #1, part 1
		//    15-bit (WCOL) and 32-bit (LCOL) color fields
		case 'WCOL': {
			// big-engian 15-bit XRRRRRGGGGGBBBBB color, that fits in a Word.
			// This is a special field to specify a color, that's used in the
			// Nova engine when there's only room for 16 bits, as in the ModVal
			// field of the oŸtf resource (namely, for paint outfits).
			// The X bit is ignored when read, and set to 0 when written.
			// Since it is the very general 16 bit color format, it can
			// concievably be used by other stuff.
			RGBColor theRGB;
			UInt16 theWord=0, redVal, greenVal, blueVal;
			if (mRezStream->GetMarker() < mRezStream->GetLength() - 1) {
				*mRezStream >> theWord;
			}
			// I need to do a few calculations on the value to turn it into
			// a RGBColor, for it to be given to AddColorPane().

			// Note: might be better to put as an utility func, perhaps later.
			redVal=(theWord>>10)&0x1F;
			greenVal=(theWord>>5)&0x1F;
			blueVal=(theWord)&0x1F;
			theRGB.red = redVal<<11 | redVal<<6 | redVal<<1 | redVal>>4;
			theRGB.green = greenVal<<11 | greenVal<<6 | greenVal<<1 | greenVal>>4;
			theRGB.blue = blueVal<<11 | blueVal<<6 | blueVal<<1 | blueVal>>4;

			AddStaticField(inType, inLabelString, inContainer);
			AddColorPane(inContainer, &theRGB);
			break;
		}

		case 'LCOL': {
			// big-engian 32-bit XXXXXXXXRRRRRRRRGGGGGGGGBBBBBBBB color.
			// Same as above, used by Nova. The 8 X bits (the first byte) are
			// ignored when read, and set to 0 when written.
			RGBColor theRGB;
			UInt8 byte1=0, byte2=0, byte3=0;
			if (mRezStream->GetMarker() < mRezStream->GetLength() - 3) {
				*mRezStream >> byte3; // dump it.
				*mRezStream >> byte1;
				*mRezStream >> byte2;
				*mRezStream >> byte3;
			}
			// I need to do a few calculations on the value to turn it into
			// a RGBColor, for it to be given to AddColorPane().

			// Note: might be better to put as an utility func, perhaps later.
			theRGB.red = byte1<<8 | byte1;
			theRGB.green = byte2<<8 | byte2;
			theRGB.blue = byte3<<8 | byte3;

			AddStaticField(inType, inLabelString, inContainer);
			AddColorPane(inContainer, &theRGB);
			break;
		}
		// end of first part of ZP feature 1	

		case 'CSTR':
		// C string. This should be either characters followed by a null or all
		// the chars until the end of the stream if there is no null byte.
		AddStaticField(inType, inLabelString, inContainer, sLeftLabelTraitsID);
		mYCoord += kTmplLabelVertSkip;
		AddWasteField(inType, inContainer);
 		break;

		case 'DATE':
		case 'MDAT':
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
		AddEditField(numStr, inType, 11, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_NegativeInteger), inContainer);
		break;

		case 'DVDR':
		// Insert a comment. Add a vertical skip as AddStaticField doesn't.
		mYCoord += kTmplDividerSep;
		AddStaticField(inType, inLabelString, inContainer, sCommentTraitsID);
		mYCoord += sEditPaneInfo.height + kTmplDividerSep;
		break;

		case 'DWRD':
		// Signed decimal word
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 1) {
			*mRezStream >> theSInt16;
		} 
		::NumToString( (long) theSInt16, numStr);
		AddStaticField(inType, inLabelString, inContainer);
		AddEditField(numStr, inType, 6, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_NegativeInteger), inContainer);
		break;

		case 'ECST':
		// Even-padded C string (padded with nulls)
		AddStaticField(inType, inLabelString, inContainer, sLeftLabelTraitsID);
		mYCoord += kTmplLabelVertSkip;
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
		if (inType != 'FBYT' || CRezillaPrefs::GetPrefValue(kPref_templates_displayFillers) ) {
			AddStaticField(inType, inLabelString, inContainer);
		} 
		AddEditField(theString, inType, 2 + CRezillaPrefs::GetPrefValue(kPref_templates_hexSymbol), 0, 
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
				::StringToNum( inLabelString, &theLong);
				mListCount = theLong;
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
		if (inType != 'FLNG' || CRezillaPrefs::GetPrefValue(kPref_templates_displayFillers) ) {
			AddStaticField(inType, inLabelString, inContainer);
		} 
		AddEditField(theString, inType, 8 + CRezillaPrefs::GetPrefValue(kPref_templates_hexSymbol), 0, 
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
		if (inType != 'FWRD' || CRezillaPrefs::GetPrefValue(kPref_templates_displayFillers) ) {
			AddStaticField(inType, inLabelString, inContainer);
		} 
		AddEditField(theString, inType, 4 + CRezillaPrefs::GetPrefValue(kPref_templates_hexSymbol), 0, 
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
		mYCoord += kTmplLabelVertSkip;
		AddHexDumpField(inType, inContainer, mSkipOffset);	// add mSkipOffset argument.
		break;

		case 'KBYT':
		case 'KHBT':
		case 'KHLG':
		case 'KHWD':
		case 'KLNG':
		case 'KRID':
		case 'KTYP':
		case 'KWRD':
		case 'KCHR':
		case 'KUBT':
		case 'KULG':
		case 'KUWD':
		// Keyed lists switches
		error = ParseKeyedSection(inType, inLabelString, inContainer);
		break;
		
		case 'KEYB':
		// Beginning of keyed segment. This is normally a segment
		// corresponding to remaining cases just after the matching segment. 
		error = FindMatchingKeyEnd(&theSInt32);
		break;

		case 'KEYE':
		// End of keyed segment. We should never reach here.
		break;

		case 'LBIT':
		// Binary bit within a long
		AddBitField(inType, inLabelString, 1, 4, inContainer);
		break;

		case 'LCNT':
		// One-based long count
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 3) {
			*mRezStream >> theUInt32;
		} 
		if (theUInt32 < 0xffff) {
			mListCount = theUInt32;
		} else {
			error = err_TmplListCountTooBig;
		}
		break;

		case 'LFLG':
		// Long Boolean flag in low-order bit (four bytes: 0x00000001 for true,
		// 0x00000000 for false)
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 3) {
			*mRezStream >> theUInt32;
		} 
		AddStaticField(inType, inLabelString, inContainer);
		AddBooleanField( (Boolean) theUInt32, inType, tmpl_titleYesNo, inContainer);		
		break;

		case 'LORV':
		// Binary long made of the OR of base-2 values
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 3) {
			*mRezStream >> theUInt32;
		} 
		AddStaticField(inType, inLabelString, inContainer);
		AddFlagPopup(inType, inLabelString, theUInt32, inContainer);
		break;

		case 'LSIZ':
		case 'LSKP':
		// Offset to SKPE in long (LSIZ:exclusive or LSKP:inclusive)
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 3) {
			*mRezStream >> theUInt32;
		}
		mSkipOffset = theUInt32;
// 		mOffsetTypes.AddItem(inType);
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
		mYCoord += kTmplLabelVertSkip;
		AddWasteField(inType, inContainer);
		break;

		case 'LSTZ':
		// List Zero. Terminated by a 0 byte (as in 'MENU' resources).
		break;
		
		case 'LZCT':
		// Zero-based long count. We put a limit to 0xffff elements (not
		// even sure there could be that much controls). A value  0xffffffff
		// means 0 items in fact.
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 3) {
			*mRezStream >> theUInt32;
			if (theUInt32 < 0xffff || theUInt32 == 0xffffffff) {
				mListCount = theUInt32 + 1;
			} else {
				error = err_TmplListCountTooBig;
			}
		} else {
			mListCount = 0;
		}
		break;

		case 'OCNT':
		case 'WCNT':
		// One-based Count. Terminated by a one-based word count that starts 
		// the sequence (as in 'STR#' resources).
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 1) {
			*mRezStream >> theUInt16;
		} 
		mListCount = theUInt16;
		break;

		case 'OCST':
		// Odd-padded C string (padded with nulls)
		AddStaticField(inType, inLabelString, inContainer, sLeftLabelTraitsID);
		mYCoord += kTmplLabelVertSkip;
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
				error = err_TmplExpectedEvenLengthString;
				break;
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
		case 'P100':
		// Pascal string
		if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
			*mRezStream >> theString;
		} else {
			theString[0] = 0;
		}
		AddStaticField(inType, inLabelString, inContainer);
		AddEditField(theString, inType, 255, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_PrintingChar), inContainer);
		if (inType == 'P100') {
			mRezStream->SetMarker(255 - theString[0], streamFrom_Marker);
		} 
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

		case 'RSID':
		// ZP feature #9, part 2:
		// Resource ID (SInt16), the type is either in the label or in a previous TNAM.
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 1) {
			*mRezStream >> theSInt16;
		} 
		::NumToString( (long) theSInt16, numStr);
		AddStaticField(inType, inLabelString, inContainer);
		AddRSIDField(numStr, inType, inLabelString, 6, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_NegativeInteger), inContainer);
		break;

		case 'SEPA':
		// Separator.
		AddSeparatorLine(inContainer);
		break;

		case 'SKPE':
		mSkipOffset = 0;
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
		case 'BB08':
		// Unsigned decimal byte
		if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
			*mRezStream >> theUInt8;
		} 
		::NumToString( (long) theUInt8, numStr);
		AddStaticField(inType, inLabelString, inContainer);
		AddEditField(numStr, inType, 3, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_Integer), inContainer);
		break;

		case 'ULNG':
		// Unsigned decimal long word
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 3) {
			*mRezStream >> theUInt32;
		} 
		::NumToString( (long) theUInt32, numStr);
		AddStaticField(inType, inLabelString, inContainer);
		AddEditField(numStr, inType, 10, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_Integer), inContainer);
		break;

		case 'UWRD':
		// Unsigned decimal word
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 1) {
			*mRezStream >> theUInt16;
		} 
		::NumToString( (long) theUInt16, numStr);
		AddStaticField(inType, inLabelString, inContainer);
		AddEditField(numStr, inType, 5, 0, 
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

		case 'WORV':
		// Binary word made of the OR of base-2 values
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 1) {
			*mRezStream >> theUInt16;
		} 
		AddStaticField(inType, inLabelString, inContainer);
		AddFlagPopup(inType, inLabelString, theUInt16, inContainer);
		break;

		case 'WSIZ':
		case 'WSKP':
		case 'SKIP':
		// Offset to SKPE in word (WSIZ:exclusive or WSKP/SKIP:inclusive)
		// SKIP is a synonym of WSKP.
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 1) {
			*mRezStream >> theUInt16;
		} 
// 		mOffsetTypes.AddItem(inType);
		break;

		case 'WSTR':
		// Same as LSTR, but a word rather than a long word
		AddStaticField(inType, inLabelString, inContainer, sLeftLabelTraitsID);
		mYCoord += kTmplLabelVertSkip;
		AddWasteField(inType, inContainer);
 		break;

		case 'ZCNT':
		// Zero-based Count. Terminated by a zero-based word count that starts 
		// the sequence (as in 'DITL' resources).
		if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
			*mRezStream >> theUInt16;
			mListCount = theUInt16 + 1;
		} else {
			mListCount = 0;
		}
		break;

	  default:
	  UMiscUtils::OSTypeToPString(inType, typeStr);
	  // Handle Hnnn, Cnnn, P0nn, BB0n etc cases here or unrecognized type
	  if ( (inType >> 24 == 'H' || inType >> 24 == 'C' || inType >> 24 == 'F' || inType >> 24 == 'T') 
		  && 
		   UMiscUtils::IsValidHexadecimal( (Ptr) typeStr + 2, 3) ) {
			  
		   UMiscUtils::HexNumStringToDecimal(&inType, &reqLength);

		  // Hnnn: a 3-digit hex number; displays $nnn bytes in hex format.
		  // Cnnn: a C string that is $nnn hex bytes long (the last byte is always a 0, 
		  //       so the string itself occupies the first $nnn-1 bytes.)
		  // Fnnn: an uneditable filler hexadecimal string that is $nnn hex bytes long 
		  // Tnnn: a text string with fixed padding that is $nnn hex bytes long 
			
		   Boolean isNotFiller = (inType >> 24 != 'F');
		   if ( isNotFiller || 
			   CRezillaPrefs::GetPrefValue(kPref_templates_displayFillers) ) {
					AddStaticField(inType, inLabelString, inContainer, sLeftLabelTraitsID, reqLength, isNotFiller);
					mYCoord += kTmplLabelVertSkip;
			} 
			
			if (inType >> 24 == 'H' || inType >> 24 == 'F') {
				AddHexDumpField(inType, inContainer, reqLength);
			} else {
				AddWasteField(inType, inContainer, reqLength);
			}
				
		} else if ( inType >> 16 == 'P0' && UMiscUtils::IsValidHexadecimal( (Ptr) typeStr + 3, 2)) {
					
		  // P0nn: a Pascal string that is nn hex bytes long. 
		  // 		The length byte is included in $nn, so the string itself
		  // 		occupies in fact $nn-1 bytes and the overall length in the
		  // 		resource is $nn bytes: this is Resourcerer's convention; in
		  // 		ResEdit's specification, the length byte is not included.
		  // 		So what is declared as P010 in Resourcerer would be P00F in
		  // 		ResEdit. We here use Resourcerer"s because it is more
		  // 		consistent with the Cnn, Hnnn, Tnnn types.
		  UMiscUtils::HexNumStringToDecimal(&inType, &theLength);
		  if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
			  *mRezStream >> theString;
			  if (theString[0] >= theLength) {
				  error = err_TmplNotExpectedSize;
				  break;
			  } 
			  // The overall length is theLength, so skip the remaining bytes
			  mRezStream->SetMarker(theLength - theString[0] - 1, streamFrom_Marker);	
		  } else {
			  theString[0] = 0;
		  }
		  AddStaticField(inType, inLabelString, inContainer, sRightLabelTraitsID, theLength);
		  AddEditField(theString, inType, theLength, 0, 
					   UKeyFilters::SelectTEKeyFilter(keyFilter_PrintingChar), inContainer);
					   
	  } else if ( IsValidBitField(inType, typeStr, bitCount, bytesLen) ) {
		  
		  AddBitField(inType, inLabelString, bitCount, bytesLen, inContainer);
		  
	  } else {
		  // Unrecognized type
		  UMessageDialogs::AlertWithType(CFSTR("UnknownTemplateTag"), inType);
		  error = err_TmplUnrecognizedTag;
	  }
	  break;
	}

	return error;
}


#pragma mark -

// ---------------------------------------------------------------------------
//   RetrieveDataWithTemplate								[public]
// ---------------------------------------------------------------------------
// ZP bugfix #9, part 1: 
// here is a minimal set of actions to reproduce it:
//  - modify something in the resource (anything, just to save)
//  - hit the save button
//  - insert a new list item and fill in the fields
//  - save, close the window, reopen the resource, and check the damage.
// Damage being namely that the data in the new list item is wrong, coming
// from the wrong fields. It is all mCurrentID's fault. Basically it is
// expected when creating a new list item that it is the next unused pane
// ID, but during retrieval it is used as a local var, and when done it is
// the ID of the last field (which may not even be the last used ID). Hence
// the bug.
// After some time thinking about it, I ended up deciding that I would replace
// every occurence of mCurrentID in the retrieving part by a new local var,
// thePaneID, and that mCurrentID would be honored as a true global (for the
// template window) state, only modified by stuff which adds new fields, and not
// a convenience variable.
// I first thought mCurrentID was (illegitimately) used for retrieval only in this
// file, but WriteOutKeyValue() used it as well, so I had to add the Pane ID as a
// new argument (both in WriteOutKeyValue and RetrieveKeyedSection).
// I did not bracket every search-and-replace of mCurrentID by thePaneID
// with my usual comments. I did only for the declarations of thePaneID.
// end of ZP bugfix #9, part 1

OSErr
CTmplEditorWindow::RetrieveDataWithTemplate()
{
	OSErr	error = noErr;

	if (mOutStream != nil) {
		delete mOutStream;
	} 
	mOutStream = new LHandleStream( ::NewHandle(0) );
	mOutStream->SetNativeEndian(mFlipped);
	
	// Reinitialize variables
	// Removed reinitialisation of mCurrentID (see comment above)
	// // mCurrentID 			= 1;
	mPaneIndex 			= 1;
	mListCount 			= 0;
	mBitSeqInProgress	= false;
	mBitSeqValue		= 0;
	mBitSeqBytesLen		= 0;
	mBitSeqIndex		= 0;

	// Parse the template stream
	error = DoRetrieveWithTemplate(0, true);
	
	return error;
}


// ---------------------------------------------------------------------------
//   DoRetrieveWithTemplate													[private]
// ---------------------------------------------------------------------------

OSErr
CTmplEditorWindow::DoRetrieveWithTemplate(SInt32 inRecursionMark, Boolean inReadControls)
{
	OSErr	error = noErr;
	Str255		theString;
	ResType		theType;
	
	mTemplateStream->SetMarker(inRecursionMark, streamFrom_Start);
	
	while (mTemplateStream->GetMarker() < mTemplateStream->GetLength() 
		   &&
		   error == noErr) {
		*mTemplateStream >> theString;
		*mTemplateStream >> theType;
		
		if (theType == 'OCNT' || theType == 'ZCNT' || theType == 'WCNT' || theType == 'BCNT' 
			|| theType == 'FCNT' || theType == 'LCNT' || theType == 'LZCT') {
			error = RetrieveDataForType(theType);
		} else if (theType == 'LSTB' || theType == 'LSTC' || theType == 'LSTZ') {
			RetrieveCountValue();
			// Skip the count field, and the Plus and Minus buttons
			mPaneIndex += 3;
			error = RetrieveList(mTemplateStream->GetMarker(), theType, mListCount);

			// ZP bugfix #4, part 2: see comment in DoParseWithTemplate()
		} else if (theType == 'LSTE' || theType == 'KEYE') {
			// end of ZP bugfix 4, part 2
			
			break;
		} else {
			if (inReadControls) {
				// Read controls according to the type declared in the template
				error = RetrieveDataForType(theType);
			}
		}
	}
	
	return error;
}


// ---------------------------------------------------------------------------
//   RetrieveList													[public]
// ---------------------------------------------------------------------------

OSErr
CTmplEditorWindow::RetrieveList(SInt32 inStartMark, ResType inType, SInt32 inCount)
{
	OSErr	error = noErr;
	
	switch (inType) {
		case 'LSTB':
		case 'LSTZ': {
			Boolean readCtrl = (mPaneIndex <= mLastID);
			
			do {
				error = DoRetrieveWithTemplate(inStartMark, readCtrl);
			} while (mPaneIndex <= mLastID && error == noErr);
			
			// An LSTZ list is terminated by a NULL
			if (inType == 'LSTZ') {
				*mOutStream << (UInt8) 0x00;
			} 
			break;
		}
		
		case 'LSTC':
		if (inCount == 0) {
			error = DoRetrieveWithTemplate(inStartMark, false);
		} else {
			mListCount = 0;
			for (short i = 0 ; i < inCount; i++) {
				error = DoRetrieveWithTemplate(inStartMark, true);
				if (error != noErr) {
					break;
				} 
			}
		}
		break;
		
	}
	return error;
}


// ---------------------------------------------------------------------------
//   RetrieveKeyedSection											[public]
// ---------------------------------------------------------------------------

OSErr
CTmplEditorWindow::RetrieveKeyedSection(ResType inType, PaneIDT inPaneID)
{
	OSErr		error = noErr;
	SInt32		sectionStart;
	ArrayIndexT	index;
	
	// Retrieve and write the key value
	error = WriteOutKeyValue(inType, inPaneID, &index);
		
	if (error == noErr) {
		// Get the corresponding position in the template
		if ( mKeyMarks.FetchItemAt(index, sectionStart) ) {
			mKeyMarks.RemoveItemsAt(1, index);
		} else {
			error = err_TmplCantFindKeyPosition;
		}
		
		if (error == noErr) {
			// Parse the section
			error = DoRetrieveWithTemplate(sectionStart, true);
		}
	} 

	return error;
}


// ---------------------------------------------------------------------------
//   RetrieveDataForType											[private]
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
	SInt32	theSInt32, theLength, reqLength, currMark, oldMark;
	UInt8	theUInt8 = 0;
	UInt16	theUInt16 = 0, bitCount = 0, bytesLen = 0;
	UInt32	theUInt32 = 0;
	SInt8	i;
	OSType	theOSType;
	ResType	theType;
	LRadioGroupView *	theRGV;
	LEditText *			theEditText;
	LCheckBox *			theCheckBox;
	CWasteEditView *	theWasteEdit;
	CFlagPopup *		theFlagPopup;
	PaneIDT			theCurrentRadioID;
	Handle			theHandle;
	StHandleLocker	locker(nil);
	CFStringRef		formatStr = NULL, messageStr = NULL;
	// ZP bugfix #9, part 2: replacement of mCurrentID by thePaneID
	PaneIDT			thePaneID;
	// end of ZP bugfix #9, part 2

	formatString[0] = 0;
	
	mPaneIDs.FetchItemAt(mPaneIndex, thePaneID);
	
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
		error = RetrieveBitField(1, 1);
		break;

		case 'BCNT':
		// Byte count for LSTC lists. Reserve a space for the count. It
		// will be filled later when the LSTC tag is met.
		mListCountMark = mOutStream->GetMarker();
		mCountType = inType;
		*mOutStream << (UInt8) 0x00;
		break;

		case 'BFLG':
		// Boolean (one byte: 0x01 for true, 0x00 for false)
		theCheckBox = dynamic_cast<LCheckBox *>(this->FindPaneByID(thePaneID));
		*mOutStream << (UInt8) theCheckBox->GetValue();
		mPaneIndex++;
		break;

		case 'BOOL':
		// Boolean (two bytes: 0x0100 for true, 0x0000 for false)
		theRGV = dynamic_cast<LRadioGroupView *>(this->FindPaneByID(thePaneID));
		theCurrentRadioID = theRGV->GetCurrentRadioID();
		if ( (theCurrentRadioID - thePaneID) % 2 ) {
			*mOutStream << (UInt16) 0x0100;
		} else {
			*mOutStream << (UInt16) 0x0000;
		}
		// The RGV and both radiobuttons have an ID. That makes three.
		mPaneIndex += 3;
		break;

		case 'BORV':
		// Binary byte made of the OR of base-2 values
		theFlagPopup = dynamic_cast<CFlagPopup *>(this->FindPaneByID(thePaneID));
		*mOutStream << (UInt8) theFlagPopup->GetFlagValue();
		// Skip the CASE tags with arg 1 in order to avoid an error if
		// there are no CASEs.
		SkipNextKeyCases(1);
		mPaneIndex++;
		break;

		case 'BSIZ':
		case 'BSKP':
		// Offset to SKPE in byte (BSIZ:exclusive or BSKP:inclusive)
		// Cache the current type and position
		mOffsetTypes.AddItem(inType);
		mOffsetMarks.AddItem(mOutStream->GetMarker());
		// Temporarily fill with null to create the place holder
		*mOutStream << (UInt8) 0x00;
		break;

		case 'CASE':
		// Bug 1241475: DO NOT increment the current pane ID to skip the case popup 
		// because the popup was not registered in mPaneIDs. 
		// // mPaneIndex++;
		// Skip the following CASE statements
		error = SkipNextKeyCases(1);
		break;

		case 'CHAR':
		// A single character
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(thePaneID));
		theEditText->GetDescriptor(theString);
		if (theString[0] == 0) {
			*mOutStream << (UInt8) 0x00;
		} else {
			*mOutStream << (UInt8) theString[1];
		}
		mPaneIndex++;
		IncrementIfCases(theEditText);
		break;

		case 'COLR': {
			// QuickDraw color RGB triplet
			RGBColor theRGB;
			CColorWell * colorWell = dynamic_cast<CColorWell *>(this->FindPaneByID(thePaneID));
			ThrowIfNil_( colorWell );
			colorWell->GetColor(theRGB);
			*mOutStream << theRGB.red;
			*mOutStream << theRGB.green;
			*mOutStream << theRGB.blue;
			mPaneIndex++;
			break;
		}

		// ZP feature #1, part 2
		case 'WCOL': {
			// big-engian 15-bit XRRRRRGGGGGBBBBB color, that fits in a Word
			RGBColor theRGB;
			UInt16 theWord, redVal, greenVal, blueVal;
			CColorWell * colorWell = dynamic_cast<CColorWell *>(this->FindPaneByID(thePaneID));
			ThrowIfNil_( colorWell );
			colorWell->GetColor(theRGB);
			redVal = (theRGB.red>>11)&0x1F;
			greenVal = (theRGB.green>>11)&0x1F;
			blueVal = (theRGB.blue>>11)&0x1F;
			theWord = (redVal<<10) | (greenVal<<5) | blueVal;
			*mOutStream << theWord;
			mPaneIndex++;
			break;
		}

		case 'LCOL': {
			// big-engian 32-bit XXXXXXXXRRRRRRRRGGGGGGGGBBBBBBBB color
			RGBColor theRGB;
			UInt8 redVal, greenVal, blueVal;
			CColorWell * colorWell = dynamic_cast<CColorWell *>(this->FindPaneByID(thePaneID));
			ThrowIfNil_( colorWell );
			colorWell->GetColor(theRGB);
			redVal = (theRGB.red>>8)&0xFF;
			greenVal = (theRGB.green>>8)&0xFF;
			blueVal = (theRGB.blue>>8)&0xFF;
			*mOutStream << (UInt8)0;
			*mOutStream << redVal;
			*mOutStream << greenVal;
			*mOutStream << blueVal;
			mPaneIndex++;
			break;
		}
		// End of second part of ZP feature 1

		case 'CSTR':
		// C string
		theWasteEdit = dynamic_cast<CWasteEditView *>(this->FindPaneByID(thePaneID));
		theHandle = theWasteEdit->GetTextHandle();
		theLength = theWasteEdit->GetTextLength();

		locker.Adopt(theHandle);
		mOutStream->PutBytes(*theHandle, theLength);		
		// End with a NULL byte
		*mOutStream << (UInt8) 0x00;
		mPaneIndex++;
		break;

		case 'DATE':
		case 'MDAT':
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(thePaneID));
		theEditText->GetDescriptor(numStr);	
		if ( ! UMiscUtils::ParseDateString(numStr, &theSInt32)) {
			error = err_TmplParseDateFailed;
		} 
		*mOutStream << theSInt32;
		mPaneIndex++;
		IncrementIfCases(theEditText);
		break;
		
		case 'DBYT':
		// Decimal byte
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(thePaneID));
		theEditText->GetDescriptor(numStr);	
		::StringToNum( numStr, &theLong);
		*mOutStream << (SInt8) theLong;
		mPaneIndex++;
		IncrementIfCases(theEditText);
		break;

		case 'DLNG':
		// Decimal long word
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(thePaneID));
		theEditText->GetDescriptor(numStr);	
		::StringToNum( numStr, &theLong);
		*mOutStream << (SInt32) theLong;
		mPaneIndex++;
		IncrementIfCases(theEditText);
		break;

		case 'DVDR':
		// It is a comment. Just skip it.
		break;

		case 'DWRD':
		// Decimal word
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(thePaneID));
		theEditText->GetDescriptor(numStr);	
		::StringToNum( numStr, &theLong);
		*mOutStream << (SInt16) theLong;
		mPaneIndex++;
		IncrementIfCases(theEditText);
		break;

		case 'ECST':
		// Even-padded C string (padded with nulls)
		theWasteEdit = dynamic_cast<CWasteEditView *>(this->FindPaneByID(thePaneID));
		theHandle = theWasteEdit->GetTextHandle();
		theLength = theWasteEdit->GetTextLength();

		locker.Adopt(theHandle);
		mOutStream->PutBytes(*theHandle, theLength);		
		// End with a NULL byte
		*mOutStream << (UInt8) 0x00;
		// Pad with a NULL byte if total length with ending NULL is odd
		if (theLength % 2 == 0) {
			*mOutStream << (UInt8) 0x00;
		} 
		mPaneIndex++;
		break;

		case 'ESTR':
		// Pascal string padded to even length (needed for DITL resources)
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(thePaneID));
		theEditText->GetDescriptor(theString);	
		*mOutStream << theString;
		if (theString[0] % 2 == 0) {
			// if the length is even, pad the string with a NULL byte.
			*mOutStream << (UInt8) 0x00;
		} 
		mPaneIndex++;
		IncrementIfCases(theEditText);
		break;

		case 'FBYT':
		case 'HBYT':
		// Hex byte
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(thePaneID));
		theEditText->GetDescriptor(numStr);	
		CopyPascalStringToC(numStr, charString);
		::LowercaseText(charString, strlen(charString), (ScriptCode)0);
		error = BuildScanString(charString, formatString, 2);
		if (error == noErr) {
			sscanf(charString, formatString, &theLong);
			*mOutStream << (UInt8) theLong;
			mPaneIndex++;
			IncrementIfCases(theEditText);
		} 
		break;

		case 'FCNT':
		// One-based fixed count for LSTC lists. No space to reserve. The
		// count is hardcoded in the label of the template, not in the
		// resource it self.
		mListCountMark = mOutStream->GetMarker();
		mCountType = inType;
		break;

		case 'HEXD':
		case 'BHEX':
		case 'BSHX':
		case 'LHEX':
		case 'LSHX':
		case 'WHEX':
		case 'WSHX': {
			// Hex dump of following bytes
			CDualDataView * theTGB = dynamic_cast<CDualDataView *>(this->FindPaneByID(thePaneID));
			WEReference theWE = theTGB->GetInMemoryWE();
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
			mPaneIndex++;
			break;
		}
		
		case 'FLNG':
		case 'HLNG':
		// Hex long word
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(thePaneID));
		theEditText->GetDescriptor(numStr);	
		CopyPascalStringToC(numStr, charString);
		::LowercaseText(charString, strlen(charString), (ScriptCode)0);
		error = BuildScanString(charString, formatString, 8);
		if (error == noErr) {
			sscanf(charString, formatString, &theLong);
			*mOutStream << (UInt32) theLong;
			mPaneIndex++;
			IncrementIfCases(theEditText);
		}
		break;

		case 'FWRD':
		case 'HWRD':
		// Hex word
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(thePaneID));
		theEditText->GetDescriptor(numStr);	
		CopyPascalStringToC(numStr, charString);
		::LowercaseText(charString, strlen(charString), (ScriptCode)0);
		error = BuildScanString(charString, formatString, 4);
		if (error == noErr) {
			sscanf(charString, formatString, &theLong);
			*mOutStream << (UInt16) theLong;
			mPaneIndex++;
			IncrementIfCases(theEditText);
		}
		break;

		case 'KBYT':
		case 'KHBT':
		case 'KHLG':
		case 'KHWD':
		case 'KLNG':
		case 'KRID':
		case 'KTYP':
		case 'KWRD':
		case 'KCHR':
		case 'KUBT':
		case 'KULG':
		case 'KUWD':
		// Keyed sections switches
		error = RetrieveKeyedSection(inType, thePaneID);
		break;
		
		case 'KEYB':
		// Beginning of keyed segment. Just skip it.
		error = FindMatchingKeyEnd(&theSInt32);
		break;

		case 'KEYE':
		// End of keyed segment
		break;

		case 'LBIT':
		// Binary bit within a long
		error = RetrieveBitField(1, 4);
		break;

		case 'LCNT':
		// One-based long count for LSTC lists. Reserve a space for the count. It
		// will be filled later when the LSTC tag is met.
		mListCountMark = mOutStream->GetMarker();
		mCountType = inType;
		*mOutStream << (UInt32) 0x00000000;
		break;

		case 'LFLG':
		// Long Boolean flag in low-order bit (four bytes: 0x00000001 for true,
		// 0x00000000 for false)
		theRGV = dynamic_cast<LRadioGroupView *>(this->FindPaneByID(thePaneID));
		theCurrentRadioID = theRGV->GetCurrentRadioID();
		if ( (theCurrentRadioID - thePaneID) % 2 ) {
			*mOutStream << (UInt32) 0x00000001;
		} else {
			*mOutStream << (UInt32) 0x00000000;
		}
		// The RGV and both radiobuttons have an ID. That makes three.
		mPaneIndex += 3;
		break;

		case 'LORV':
		// Binary long made of the OR of base-2 values
		theFlagPopup = dynamic_cast<CFlagPopup *>(this->FindPaneByID(thePaneID));
		*mOutStream << (UInt32) theFlagPopup->GetFlagValue();
		SkipNextKeyCases(1);
		mPaneIndex++;
		break;

		case 'LSIZ':
		case 'LSKP':
		// Offset to SKPE in long (LSIZ:exclusive or LSKP:inclusive)
		// Cache the current type and position
		mOffsetTypes.AddItem(inType);
		mOffsetMarks.AddItem(mOutStream->GetMarker());
		// Temporarily fill with null to create the place holder
		*mOutStream << 0L;
		break;

		case 'LNGC':
		case 'RGNC':
		case 'SCPC': 
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(thePaneID));
		theEditText->GetDescriptor(numStr);	
		::StringToNum( numStr, &theLong);
		*mOutStream << (SInt16) theLong;
		// Skip the field and the bevel popup button
		mPaneIndex += 2;
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
		theWasteEdit = dynamic_cast<CWasteEditView *>(this->FindPaneByID(thePaneID));
		theHandle = theWasteEdit->GetTextHandle();
		theLength = theWasteEdit->GetTextLength();
		*mOutStream << (UInt32) theLength;

		locker.Adopt(theHandle);
		mOutStream->PutBytes(*theHandle, theLength);
		mPaneIndex++;
		break;

		case 'LSTZ':
		// List Zero. Terminated by a 0 byte (as in 'MENU' resources).
		break;
		
		case 'LZCT':
		// Zero-based count for LSTC lists. Reserve a space for the count. It
		// will be filled later when the LSTC tag is met.
		mListCountMark = mOutStream->GetMarker();
		mCountType = inType;
		*mOutStream << (UInt32) 0x00000000;
		break;

		case 'OCNT':
		case 'WCNT':
		// One-based count for LSTC lists. Reserve a space for the count. It
		// will be filled later when the LSTC tag is met.
		mListCountMark = mOutStream->GetMarker();
		mCountType = inType;
		*mOutStream << (UInt16) 0x0000;
		break;

		case 'OCST':
		// Odd-padded C string (padded with nulls)
		theWasteEdit = dynamic_cast<CWasteEditView *>(this->FindPaneByID(thePaneID));
		theHandle = theWasteEdit->GetTextHandle();
		theLength = theWasteEdit->GetTextLength();

		locker.Adopt(theHandle);
		mOutStream->PutBytes(*theHandle, theLength);		
		// End with a NULL byte
		*mOutStream << (UInt8) 0x00;
		// Pad with a NULL byte if total length with ending NULL is odd
		if (theLength % 2 == 1) {
			*mOutStream << (UInt8) 0x00;
		} 
		mPaneIndex++;
		break;

		case 'OSTR':
		// Pascal string padded to odd length (needed for DITL resources)
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(thePaneID));
		theEditText->GetDescriptor(theString);	
		*mOutStream << theString;
		if (theString[0] % 2) {
			// if the length is odd, pad the string with a NULL byte.
			*mOutStream << (UInt8) 0x00;
		} 
		mPaneIndex++;
		IncrementIfCases(theEditText);
		break;

		case 'PNT ':
		// An 4-byte point
		for (i = 0; i < 2; i++) {
			theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(thePaneID));
			theEditText->GetDescriptor(numStr);	
			::StringToNum( numStr, &theLong);
			*mOutStream << (SInt16) theLong;
			mPaneIndex++;
			mPaneIDs.FetchItemAt(mPaneIndex, thePaneID);
		}
		break;

		case 'PPST': 
		// Pascal string padded to even length (including the pad)
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(thePaneID));
		theEditText->GetDescriptor(theString);
		theLength = theString[0];
		if (theLength % 2 == 0) {
			// if the length is even, pad the string with a NULL byte.
			theString[0] = theLength + 1;
			theString[theLength + 1] = 0;
		} 
		*mOutStream << theString;
		mPaneIndex++;
		IncrementIfCases(theEditText);
		break;

		case 'PSTR':
		case 'P100':
		case 'BSTR':
		// Pascal string
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(thePaneID));
		theEditText->GetDescriptor(theString);	
		*mOutStream << theString;
		if (inType == 'P100') {
			// Pad with null bytes
			for (theSInt32 = 0; theSInt32 < 255 - theString[0]; theSInt32++) {
				*mOutStream << (UInt8) 0x00;
			}
		} 
		mPaneIndex++;
		IncrementIfCases(theEditText);
		break;

		case 'RECT':
		// An 8-byte rectangle
		if (mRectFormat == rect_TLBR) {
			// 'top, left, bottom, right' format
			for (i = 0; i < 4; i++) {
				theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(thePaneID));
				theEditText->GetDescriptor(numStr);	
				::StringToNum( numStr, &theLong);
				*mOutStream << (SInt16) theLong;
				mPaneIndex++;
				mPaneIDs.FetchItemAt(mPaneIndex, thePaneID);
			}
		} else {
			// 'top, left, width, height' format
			long theVal[4];
			
			for (i = 0; i < 4; i++) {
				theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(thePaneID));
				theEditText->GetDescriptor(numStr);	
				::StringToNum( numStr, &theVal[i]);
				mPaneIndex++;
				mPaneIDs.FetchItemAt(mPaneIndex, thePaneID);
			}
			*mOutStream << (SInt16) theVal[0];
			*mOutStream << (SInt16) theVal[1];
			*mOutStream << (SInt16) (theVal[0] + theVal[3]);
			*mOutStream << (SInt16) (theVal[1] + theVal[2]);
		}
		break;

		case 'RSID':
		// Resource ID is a decimal word
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(thePaneID));
		theEditText->GetDescriptor(numStr);	
		::StringToNum( numStr, &theLong);
		*mOutStream << (SInt16) theLong;
		// RSID fields always have a popup
		mPaneIndex += 2;
		break;

		case 'SEPA':
		// Separator. Just skip it.
		break;

		case 'SKPE':
		// End of Skip or Sizeof.
		currMark = mOutStream->GetMarker();
		if (mOffsetTypes.RemoveLastItem(theType) && mOffsetMarks.RemoveLastItem(oldMark)) {
			theLength = currMark - oldMark;
			mOutStream->SetMarker(oldMark, streamFrom_Start);
			switch (theType) {
				case 'BSIZ':
				theLength -= 1;
				*mOutStream << (UInt8) theLength;
				break;
				
				case 'BSKP':
				*mOutStream << (UInt8) theLength;
				break;
				
				case 'LSIZ':
				theLength -= 4;
				*mOutStream << (UInt32) theLength;
				break;
				
				case 'LSKP':
				*mOutStream << (UInt32) theLength;
				break;
				
				case 'WSIZ':
				theLength -= 2;
				*mOutStream << (UInt16) theLength;
				break;
				
				case 'WSKP':
				case 'SKIP':
				*mOutStream << (UInt16) theLength;
				break;
				
			}
			mOutStream->SetMarker(currMark, streamFrom_Start);
		} 
		break;

		case 'TNAM':
		// Type name (four characters, like OSType and ResType)
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(thePaneID));
		theEditText->GetDescriptor(theString);	
		UMiscUtils::PStringToOSType(theString, theOSType);
		*mOutStream << theOSType;
		mPaneIndex++;
		IncrementIfCases(theEditText);
		break;

		case 'UBYT':
		case 'BB08':
		// Unsigned decimal byte
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(thePaneID));
		theEditText->GetDescriptor(numStr);	
		::StringToNum( numStr, &theLong);
		*mOutStream << (UInt8) theLong;
		mPaneIndex++;
		IncrementIfCases(theEditText);
		break;

		case 'ULNG':
		// Unsigned decimal long word
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(thePaneID));
		theEditText->GetDescriptor(numStr);	
		::StringToNum( numStr, &theLong);
		*mOutStream << (UInt32) theLong;
		mPaneIndex++;
		IncrementIfCases(theEditText);
		break;

		case 'UWRD':
		// Unsigned decimal word
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(thePaneID));
		theEditText->GetDescriptor(numStr);	
		::StringToNum( numStr, &theLong);
		*mOutStream << (UInt16) theLong;
		mPaneIndex++;
		IncrementIfCases(theEditText);
		break;

		case 'WBIT':
		// Binary bit within a word
		error = RetrieveBitField(1, 2);
		break;

		case 'WFLG':
		// Word Boolean flag in low-order bit (two bytes: 0x0001 for true, 0x0000 for false)
		theRGV = dynamic_cast<LRadioGroupView *>(this->FindPaneByID(thePaneID));
		theCurrentRadioID = theRGV->GetCurrentRadioID();
		if ( (theCurrentRadioID - thePaneID) % 2 ) {
			*mOutStream << (UInt16) 0x0001;
		} else {
			*mOutStream << (UInt16) 0x0000;
		}
		// The RGV and both radiobuttons have an ID. That makes three.
		mPaneIndex += 3;
		break;

		case 'WORV':
		// Binary word made of the OR of base-2 values
		theFlagPopup = dynamic_cast<CFlagPopup *>(this->FindPaneByID(thePaneID));
		*mOutStream << (UInt16) theFlagPopup->GetFlagValue();
		SkipNextKeyCases(1);
		mPaneIndex++;
		break;

		case 'WSIZ':
		case 'WSKP':
		case 'SKIP':
		// Offset to SKPE in word (WSIZ:exclusive or WSKP/SKIP:inclusive)
		// Cache the current type and position
		mOffsetTypes.AddItem(inType);
		mOffsetMarks.AddItem(mOutStream->GetMarker());
		// Temporarily fill with null to create the place holder
		*mOutStream << (UInt16) 0x0000;
		break;

		case 'WSTR':
		// Same as LSTR, but a word rather than a long word
		theWasteEdit = dynamic_cast<CWasteEditView *>(this->FindPaneByID(thePaneID));
		theHandle = theWasteEdit->GetTextHandle();
		theLength = theWasteEdit->GetTextLength();
		*mOutStream << (UInt16) theLength;

		locker.Adopt(theHandle);
		mOutStream->PutBytes(*theHandle, theLength);
		mPaneIndex++;
		break;

		case 'ZCNT':
		// Zero-based count for LSTC lists. Reserve a space for the count. It
		// will be filled later when the LSTC tag is met.
		mListCountMark = mOutStream->GetMarker();
		mCountType = inType;
		*mOutStream << (UInt16) 0x0000;
		break;

	  default:
	  UMiscUtils::OSTypeToPString(inType, typeStr);
	  // Handle Hnnn, Cnnn, P0nn, BB0n etc cases here or unrecognized type
	  if (inType >> 24 == 'H') {
		  
		  // Hnnn: a 3-digit hex number; displays $nnn bytes in hex format
		  CDualDataView * theTGB = dynamic_cast<CDualDataView *>(this->FindPaneByID(thePaneID));
		  WEReference theWE = theTGB->GetInMemoryWE();
		  theHandle = static_cast<Handle>(::WEGetText(theWE));
		  theLength = ::WEGetTextLength(theWE);
		  UMiscUtils::HexNumStringToDecimal(&inType, &reqLength);

		  // We want exactly $nnn bytes
		  if (theLength != reqLength) {
			  error = err_TmplNotExpectedSize;
			  break;
		  } 
		  
		  locker.Adopt(theHandle);
		  mOutStream->PutBytes(*theHandle, reqLength);
		  mPaneIndex++;
		  
	  } else if (inType >> 24 == 'F') {
		  
		  // Fnnn: a 3-digit hex number; fills with $nnn bytes in hex format
		  CDualDataView * theTGB = dynamic_cast<CDualDataView *>(this->FindPaneByID(thePaneID));
		  WEReference theWE = theTGB->GetInMemoryWE();
		  theHandle = static_cast<Handle>(::WEGetText(theWE));
		  theLength = ::WEGetTextLength(theWE);
		  UMiscUtils::HexNumStringToDecimal(&inType, &reqLength);

		  // Truncate if we have more.
		  if (theLength > reqLength) {
			  theLength = reqLength;
		  } 
		  
		  locker.Adopt(theHandle);
		  mOutStream->PutBytes(*theHandle, theLength);
		  if (theLength < reqLength) {
			  // Pad with null bytes
			  for (theSInt32 = 0; theSInt32 < reqLength - theLength; theSInt32++) {
				  *mOutStream << (UInt8) 0x00;
			  }
		  } 
		  mPaneIndex++;
		  
	  } else if (inType >> 24 == 'C') {
		  
		  // Cnnn: a C string that is $nnn hex bytes long (the last byte is always a 0, 
		  // so the string itself occupies the first $nnn-1 bytes).
		  theWasteEdit = dynamic_cast<CWasteEditView *>(this->FindPaneByID(thePaneID));
		  theHandle = theWasteEdit->GetTextHandle();
		  theLength = theWasteEdit->GetTextLength();
		  UMiscUtils::HexNumStringToDecimal(&inType, &reqLength);

		  // Truncate if we have more.
		  if (theLength >= reqLength) {
			  theLength = reqLength - 1;
		  } 
		  
		  locker.Adopt(theHandle);
		  mOutStream->PutBytes(*theHandle, theLength);
		  if (theLength < reqLength) {
			  // Pad with null bytes
			  for (theSInt32 = 0; theSInt32 < reqLength - theLength - 1; theSInt32++) {
				  *mOutStream << (UInt8) 0x00;
			  }
		  } 
		  // Now the ending NULL byte
		  *mOutStream << (UInt8) 0x00;
		  mPaneIndex++;
		  
	  } else if (inType >> 24 == 'T') {
		  
		  // Tnnn: a text string with fixed padding that is $nnn hex bytes long 
		  theWasteEdit = dynamic_cast<CWasteEditView *>(this->FindPaneByID(thePaneID));
		  theHandle = theWasteEdit->GetTextHandle();
		  theLength = theWasteEdit->GetTextLength();
		  UMiscUtils::HexNumStringToDecimal(&inType, &reqLength);

		  // Truncate if we have more.
		  if (theLength > reqLength) {
			  theLength = reqLength;
		  } 
		  		  
		  locker.Adopt(theHandle);
		  mOutStream->PutBytes(*theHandle, theLength);		
		  if (theLength < reqLength) {
			  // Pad with null bytes
			  for (theSInt32 = 0; theSInt32 < reqLength - theLength; theSInt32++) {
				  *mOutStream << (UInt8) 0x00;
			  }
		  } 
		  mPaneIndex++;

	  } else if ( inType >> 16 == 'P0') {
		  
		  // P0nn: a Pascal string that is $nn hex bytes long. The length byte 
		  // is included in $nn, so the string itself occupies $nn-1 bytes.
		  theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(thePaneID));
		  theEditText->GetDescriptor(theString);	
		  theLength = theString[0];
		  UMiscUtils::HexNumStringToDecimal(&inType, &reqLength);

		  if (theLength >= reqLength) {
			  // Don't error. Just truncate it.
			  theString[0] = reqLength - 1;
		  }
		  *mOutStream << theString;
		  if (theLength < reqLength) {
			  // Pad with null bytes
			  for (theSInt32 = 0; theSInt32 < reqLength - theLength - 1; theSInt32++) {
				  *mOutStream << (UInt8) 0x00;
			  }
		  } 
		  mPaneIndex++;
		  IncrementIfCases(theEditText);

	  } else if ( IsValidBitField(inType, typeStr, bitCount, bytesLen) ) {
		  
		  error = RetrieveBitField(bitCount, bytesLen);
		  
	  } else {
		  // Unrecognized type
		  UMessageDialogs::AlertWithType(CFSTR("UnknownTemplateType"), inType);
		  error = err_TmplUnrecognizedTag;
	  }
	  break;
	}

	return error;
}


// ---------------------------------------------------------------------------
//   RetrieveBitField											[private]
// ---------------------------------------------------------------------------

OSErr
CTmplEditorWindow::RetrieveBitField(UInt16 inBitCount, UInt16 inBytesLen)
{
	OSErr	error = noErr;
	long	theLong;
	Str255	numStr;
	// ZP bugfix #9, part 3: replacement of mCurrentID by thePaneID
	PaneIDT	thePaneID;
	// end of ZP bugfix #9, part 3
	
	mPaneIDs.FetchItemAt(mPaneIndex, thePaneID);
	
	if (!mBitSeqInProgress) {
		mBitSeqInProgress = true;
		mBitSeqBytesLen = inBytesLen;
		mBitSeqIndex = mBitSeqBytesLen * 8 - 1;
		mBitSeqValue = 0;
	} 
	
	if (inBitCount == 1) {
		LCheckBox * theCheckBox = dynamic_cast<LCheckBox *>(this->FindPaneByID(thePaneID));
		mBitSeqValue |= theCheckBox->GetValue() ? 1 << mBitSeqIndex : 0 ;
		mBitSeqIndex--;
	} else {
		LEditText * theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(thePaneID));
		theEditText->GetDescriptor(numStr);	
		::StringToNum( numStr, &theLong);
		
		// ZP bugfix #11: when LB31 is used, inBitCount is 31 and
		// 1<<31 evaluates to the most negative int and this inequality is
		// always false. I fixed by forcing unsigned evaluation.
		if ((unsigned long)theLong >= (unsigned long)(1 << inBitCount)) {
			error = err_TmplValueTooLargeInBitsField;
			goto DONE;
		} 
		mBitSeqValue |= theLong << (mBitSeqIndex - inBitCount + 1);
		mBitSeqIndex -= inBitCount;
	}
	
	mPaneIndex++;
	
	if (mBitSeqIndex < 0) {
		mBitSeqInProgress = false;
		switch (mBitSeqBytesLen) {
			case 1:
			*mOutStream << (SInt8) mBitSeqValue;
			break;
			
			case 2:
			*mOutStream << (SInt16) mBitSeqValue;
			break;
			
			case 4:
			*mOutStream << mBitSeqValue;
			break;
		}
	} 
	
DONE:	
	return error;
}


// ---------------------------------------------------------------------------
//   RetrieveCountValue											[private]
// ---------------------------------------------------------------------------

OSErr
CTmplEditorWindow::RetrieveCountValue()
{
	OSErr	error = noErr;
	SInt32	saveMark;
	long	theLong;
	Str255	theString;
	UInt8	theUInt8 = 0;
	UInt16	theUInt16 = 0;
	UInt32	theUInt32 = 0;
	LStaticText	*	theStaticText;
	// ZP bugfix #9, part 4: replacement of mCurrentID by thePaneID
	PaneIDT	thePaneID;
	// end of ZP bugfix #9, part 4

	mPaneIDs.FetchItemAt(mPaneIndex, thePaneID);
	
	saveMark = mOutStream->GetMarker();
	mOutStream->SetMarker(mListCountMark, streamFrom_Start);
	
	theStaticText = dynamic_cast<LStaticText *>(this->FindPaneByID(thePaneID));
	theStaticText->GetDescriptor(theString);	
	::StringToNum( theString, &theLong);
	
	switch (mCountType) {
		
		case 'BCNT':
		// Byte count for LSTC lists
		*mOutStream << (UInt8) theLong;
		if (theLong > 7) {
			theLong = 7;
		} 
		mListCount = (UInt16) theLong;
		break;
		
		case 'FCNT':
		// Do nothing. The count is hardcoded in the label of the FCNT tag 
		// and the Plus/Minus buttons are hidden
		mListCount = (UInt16) theLong;
		break;
		
		case 'LCNT':
		// One-based long count for LSTC lists
		mListCount = (UInt16) theLong;
		if (theLong < 0xffff) {
			theUInt32 = (UInt32) theLong;
		} else {
			error = err_TmplListCountTooBig;
		}
		*mOutStream << theUInt32;
		break;
		
		case 'LZCT':
		// Zero-based count for LSTC lists
		mListCount = (UInt16) theLong;
		if (theLong < 0xffff) {
			if (!theLong) {
				theUInt32 = 0xffffffff;
			} else {
				theUInt32 = theLong - 1;
			}
			*mOutStream << theUInt32;
		} else {
			error = err_TmplListCountTooBig;
		}
		break;
		
		case 'OCNT':
		case 'WCNT':
		// One-based count for LSTC lists
		mListCount = (UInt16) theLong;
		*mOutStream << mListCount;
		break;
		
		case 'ZCNT':
		// Zero-based count for LSTC lists
		mListCount = (UInt16) theLong;
		if (!theLong) {
			theUInt16 = 0xffff;
		} else {
			theUInt16 = (UInt16) --theLong;
		}
		*mOutStream << theUInt16;
		break;
		
	}
	
	mOutStream->SetMarker(saveMark, streamFrom_Start);
	return error;
}


// ---------------------------------------------------------------------------
//   RevertWithTemplate											[public]
// ---------------------------------------------------------------------------

OSErr
CTmplEditorWindow::RevertWithTemplate()
{
	OSErr			error = noErr;
	SInt32			oldYCoord;
	SDimension32	theSize;
	
	mContentsView->GetImageSize(theSize);
	oldYCoord = theSize.height;
	
	// Delete all the sub panes in the contents view
	mContentsView->DeleteAllSubPanes();
	
	// Reset the variables
	mCurrentID			= 1;
	mPaneIndex			= 1;
	mLastID				= 0;
	mListCount			= 0;
	mIndent				= 0;
	mSkipOffset			= 0;
	mListCountMark		= 0;
	mBitSeqInProgress	= false;
	mBitSeqValue		= 0;
	mBitSeqBytesLen		= 0;
	mBitSeqIndex		= 0;
	mFixedCount			= false;
	mYCoord             = kTmplVertSkip;
	
	// Reset the arrays
	mPaneIDs.RemoveAllItemsAfter(0);
	mOffsetTypes.RemoveAllItemsAfter(0);
	mOffsetMarks.RemoveAllItemsAfter(0);
	mKeyValues.RemoveAllItemsAfter(0);
	mKeyMarks.RemoveAllItemsAfter(0);
	mKeyIDs.RemoveAllItemsAfter(0);
	
	mRezStream->SetMarker(0, streamFrom_Start);

	mContentsView->Hide();

	// Parse the template stream
	error = DoParseWithTemplate(0, true, mContentsView);
	
	if (error == noErr) {
		// Check that there is nothing left in the data stream
		if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
			UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("ResourceLongerThanTemplate"), PPob_SimpleMessage);
		} 
		mLastID = mCurrentID - 1;
		mContentsView->ResizeImageBy(0, mYCoord - oldYCoord, true);
		mContentsScroller->AdjustScrollBars();
// 		mContentsView->Refresh();
	} 
	
	mContentsView->Show();
	mContentsView->Enable();
	mContentsView->Activate();
	Refresh();

	return  error;
}
 