// ===========================================================================
// CTmplEditorWindow.cp					
// 
//                       Created: 2004-06-12 15:08:01
//             Last modification: 2004-09-23 10:13:26
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
#include <LIconPane.h>
#include <LEditText.h>
#include <LTextGroupBox.h>
#include <LCheckBox.h>
#include <LPushButton.h>
#include <LScrollerView.h>
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
SPaneInfo CTmplEditorWindow::sColorPaneInfo;


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
	mListCountMark		= 0;
	mBitSeqInProgress	= false;
	mBitSeqValue		= 0;
	mBitSeqBytesLen		= 0;
	mBitSeqIndex		= 0;
	mBitSeqMax			= 0;
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
			mCurrentID -= currListItemView->mLastItemID - currListItemView->mFirstItemID + 1;
			mLastID = mCurrentID;
			
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
				mYCoord += kTmplVertSkip;
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
			mLastID = mCurrentID;

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
			STmplBevelInfo	theBevelInfo = *((STmplBevelInfo *) ioParam);								
			LEditText *		theEditText;
			CTmplBevelButton *	theBevel;
			SInt32			firstMark, currMark;
			Str255			theString;
			Str255 * 		rightPtr;
			ResType			theType;
			SInt16			i, choice;
			
			choice = theBevelInfo.menuChoice;
			theBevel = dynamic_cast<CTmplBevelButton *>(theBevelInfo.selfPtr);
			if (theBevel != NULL) {
				theEditText = (LEditText *) theBevel->GetUserCon();
				
				firstMark = theEditText->GetUserCon();
				currMark = mTemplateStream->GetMarker();
				mTemplateStream->SetMarker(firstMark, streamFrom_Start);

				for ( i = 0; i < choice ; i++) {
					*mTemplateStream >> theString;
					*mTemplateStream >> theType;
				}

				if ( SplitCaseValue(theString, &rightPtr) ) {
					theEditText->SetDescriptor(*rightPtr);
				} 
				mTemplateStream->SetMarker(currMark, streamFrom_Start);
			}
			
			// Window has been modified
			SetDirty(true);
			break;
		}
		
		
		case msg_TmplPopupField: {
			STmplBevelInfo	theBevelInfo = *((STmplBevelInfo *) ioParam);								
			CTmplBevelButton *	theBevel;
			LEditText *		theEditText;
			Str255			theString;
			Str255 * 		rightPtr;
			SInt16			choice;
			ResIDT			resID;
			
			choice = theBevelInfo.menuChoice;
			theBevel = dynamic_cast<CTmplBevelButton *>(theBevelInfo.selfPtr);
			if (theBevel != NULL) {
				theEditText = (LEditText *) theBevel->GetUserCon();
				resID = (ResIDT) theEditText->GetUserCon();
				
				GetIndString(theString, resID, choice);
				if ( SplitCaseValue(theString, &rightPtr) ) {
					theEditText->SetDescriptor(*rightPtr);
				} 
			} 
			
			// Window has been modified
			SetDirty(true);
			break;
		}
		
		
		default:
			dynamic_cast<CTmplEditorDoc *>(GetSuperCommander())->ListenToMessage(inMessage, ioParam);
			break;
		
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


#pragma mark -

// ---------------------------------------------------------------------------
//	¥ CreateTemplateStream									[protected]
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
		mOwnerDoc->GetRezMapTable()->GetRezMap()->GetWithName('TMPL', theName, theHandle, true);
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
//	¥ ParseDataWithTemplate											[public]
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
		
		// Parse the template stream
		error = DoParseWithTemplate(0, true, mContentsView);
		
		if (error == noErr) {
			// Check that there is nothing left in the data stream
			if (mRezStream->GetMarker() < mRezStream->GetLength() ) {
				UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("ResourceLongerThanTemplate"), rPPob_SimpleMessage);
			} 
			mLastID = mCurrentID;
			mContentsView->ResizeImageBy(0, mYCoord - oldYCoord, true);
			mContentsScroller->AdjustScrollBars();
		} 
	} else {
// 		UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("CouldNotGetTemplateData"), rPPob_SimpleMessage);
	}	
	
	return error;
}


// ---------------------------------------------------------------------------
//	¥ DoParseWithTemplate											[public]
// ---------------------------------------------------------------------------
// If 'inRezStream' is nil, an empty template is built with default values.

OSErr
CTmplEditorWindow::DoParseWithTemplate(SInt32 inRecursionMark, Boolean inDrawControls, LView * inContainer)
{
	OSErr		error = noErr;
	Str255		theString, countLabel;
	ResType		theType;

	mTemplateStream->SetMarker(inRecursionMark, streamFrom_Start);

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
				AddListHeaderField(theType, theString, mItemsCount, countLabel, inContainer, mFixedCount);
			}
			error = ParseList(mTemplateStream->GetMarker(), theType, mItemsCount, inContainer);
		} else if (theType == 'LSTE') {
			break;
		} else {
			if (inDrawControls) {
				// Create controls according to the type declared in the template
				error = ParseDataForType(theType, theString, inContainer);
			} 
		}
	}

	return error;
}


// ---------------------------------------------------------------------------
//	¥ ParseList													[public]
// ---------------------------------------------------------------------------

OSErr
CTmplEditorWindow::ParseList(SInt32 inStartMark, ResType inType, SInt32 inCount, LView * inContainer)
{
	OSErr	error = noErr;

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
			error = DoParseWithTemplate(inStartMark, drawCtrl, theContainer);
			if (drawCtrl) {
				currListItemView->mLastItemID = mCurrentID - 1;
				currListItemView->ResizeFrameBy(0, mYCoord, false);
				outYCoord += mYCoord + kTmplVertSkip;
				mYCoord = outYCoord;
			} 
		} while (! EndOfList(inType) );
		
		break;
		
		case 'LSTC':
		if (inCount == 0) {
			error = DoParseWithTemplate(inStartMark, false, theContainer);
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
				error = DoParseWithTemplate(inStartMark, true, theContainer);
				currListItemView->mLastItemID = mCurrentID - 1;
				currListItemView->ResizeFrameBy(0, mYCoord, false);
				outYCoord += mYCoord + kTmplVertSkip;
				mYCoord = outYCoord;
			}
		}
		break;
		
	}
	
	mIndent -= kTmplListIndent;
	
	return error;
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
//	¥ ParseKeyedSection												[private]
// ---------------------------------------------------------------------------

OSErr
CTmplEditorWindow::ParseKeyedSection(ResType inType, Str255 inLabelString, LView * inContainer)
{
	OSErr		error = noErr;
	Str255		keyString;
	SInt32		sectionStart;
	Boolean		inDrawControls;
	
	// Get the key value
	if (mRezStream->GetMarker() < mRezStream->GetLength()) {
		KeyValueToString(inType, keyString);
		inDrawControls = true;
		// Skip all the CASE statements
		SkipNextKeyCases();
	} else {
		if ( ! SelectValueFromKeyCases(inLabelString) ) {
			error = err_TmplCreateEmptyNewAborted;
			return error;
		} 
		inDrawControls = false;
	}
	
	// Find the corresponding KEYB tag
	error = FindKeyStartForValue(keyString, &sectionStart);
	
	if (error == noErr) {
		// Parse the section
		error = DoParseWithTemplate(sectionStart, inDrawControls, inContainer);
	} 

	// NB: the following KEYB-KEYE segments (remaining cases) will be skipped  
	// when met by the ParseDataForType() function.
	
	return error;
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
// 		mOffsetTypesList.AddItem(inType);
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

		case 'COLR': {
			// QuickDraw color RGB triplet
			RGBColor theRGB = {0,0,0};
			if (mRezStream->GetMarker() < mRezStream->GetLength() - 5) {
				*mRezStream >> theRGB.red;
				*mRezStream >> theRGB.green;
				*mRezStream >> theRGB.blue;
			} 
			AddStaticField(inType, inLabelString, inContainer);
			AddColorPane(inType, inContainer, &theRGB);		
			break;
		}
		
		case 'CSTR':
		// C string. This should be either characters followed by a null or all
		// the chars until the end of the stream if there is no null byte.
		AddStaticField(inType, inLabelString, inContainer, sLeftLabelTraitsID);
		mYCoord += kTmplLabelHeight + kTmplVertSkip;
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
		AddEditField(numStr, inType, 6, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_NegativeInteger), inContainer);
		break;

		case 'DVDR':
		// Insert a comment. Add a vertical skip as AddStaticField doesn't.
		mYCoord += kTmplVertSep;
		AddStaticField(inType, inLabelString, inContainer, sCommentTraitsID);
		mYCoord += sEditPaneInfo.height + kTmplVertSep;
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
		if (inType != 'FBYT' || CRezillaPrefs::GetPrefValue(kPref_editors_dispFillers) ) {
			AddStaticField(inType, inLabelString, inContainer);
		} 
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
		if (inType != 'FLNG' || CRezillaPrefs::GetPrefValue(kPref_editors_dispFillers) ) {
			AddStaticField(inType, inLabelString, inContainer);
		} 
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
		if (inType != 'FWRD' || CRezillaPrefs::GetPrefValue(kPref_editors_dispFillers) ) {
			AddStaticField(inType, inLabelString, inContainer);
		} 
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
		ParseKeyedSection(inType, inLabelString, inContainer);
		break;
		
		case 'KEYB':
		// Beginning of keyed segment. This is normally a segment
		// corresponding to remaining cases just after the matching segment. 
		// We must skip it.
		error = FindMatchingKeyEnd(&theSInt32);
		break;

		case 'KEYE':
		// End of keyed segment. We shoould never reach here.
		error = err_TmplUnexpectedTag;
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
// 		mOffsetTypesList.AddItem(inType);
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

		case 'SEPA':
		// Separator.
		AddSeparatorLine(inContainer);
		break;

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
		case 'SKIP':
		// Offset to SKPE in word (WSIZ:exclusive or WSKP/SKIP:inclusive)
		// SKIP is a synonym of WSKP.
		if (mRezStream->GetMarker() < mRezStream->GetLength() - 1) {
			*mRezStream >> theUInt16;
		} 
// 		mOffsetTypesList.AddItem(inType);
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
	  if ( (inType >> 24 == 'H' || inType >> 24 == 'C' || inType >> 24 == 'F' || inType >> 24 == 'T') 
		  && 
		   UMiscUtils::IsValidHexadecimal( (Ptr) typeStr + 2, 3) ) {
			  
		  // Hnnn: a 3-digit hex number; displays $nnn bytes in hex format.
		  // Cnnn: a C string that is $nnn hex bytes long (the last byte is always a 0, 
		  //       so the string itself occupies the first $nnn-1 bytes.)
		  // Fnnn: an uneditable filler hexadecimal string that is $nnn hex bytes long 
		  // Tnnn: a text string with fixed padding that is $nnn hex bytes long 

		   if (inType >> 24 != 'F' || 
			   CRezillaPrefs::GetPrefValue(kPref_editors_dispFillers) ) {
					AddStaticField(inType, inLabelString, inContainer, sLeftLabelTraitsID);
					mYCoord += kTmplLabelHeight + kTmplVertSkip;
			} 
				
			if (inType >> 24 == 'H' || inType >> 24 == 'F') {
				AddHexDumpField(inType, inContainer);
			} else {
				AddWasteField(inType, inContainer);
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
		  AddStaticField(inType, inLabelString, inContainer);
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
//	¥ RetrieveDataWithTemplate								[public]
// ---------------------------------------------------------------------------

OSErr
CTmplEditorWindow::RetrieveDataWithTemplate()
{
	OSErr	error = noErr;

	if (mOutStream != nil) {
		delete mOutStream;
	} 
	mOutStream = new LHandleStream( ::NewHandle(0) );
	mCurrentID = 1;

	mItemsCount = 0;
	
	// Reinitialize the bit sequence globals
	mBitSeqInProgress	= false;
	mBitSeqValue		= 0;
	mBitSeqBytesLen		= 0;
	mBitSeqIndex		= 0;
	mBitSeqMax			= 0;

	// Parse the template stream
	error = DoRetrieveWithTemplate(0, true);
	
	return error;
}


// ---------------------------------------------------------------------------
//	¥ DoRetrieveWithTemplate													[public]
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
			if (theType == 'LSTC') {
				RetrieveCountValue();
			} 
			// Skip the Plus and Minus buttons
			mCurrentID += 2;
			error = RetrieveList(mTemplateStream->GetMarker(), theType, mItemsCount);
		} else if (theType == 'LSTE') {
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
//	¥ RetrieveList													[public]
// ---------------------------------------------------------------------------

OSErr
CTmplEditorWindow::RetrieveList(SInt32 inStartMark, ResType inType, SInt32 inCount)
{
	OSErr	error = noErr;
	
	switch (inType) {
		case 'LSTB':
		case 'LSTZ':
		Boolean readCtrl = (mCurrentID < mLastID);
		do {
			error = DoRetrieveWithTemplate(inStartMark, readCtrl);
		} while (mCurrentID < mLastID && error == noErr);
		// An LSTZ list is terminated by a NULL
		if (inType == 'LSTZ') {
			*mOutStream << (UInt8) 0x00;
		} 
		break;
		
		case 'LSTC':
		if (inCount == 0) {
			error = DoRetrieveWithTemplate(inStartMark, false);
		} else {
			mItemsCount = 0;
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
//	¥ RetrieveKeyedSection											[public]
// ---------------------------------------------------------------------------

OSErr
CTmplEditorWindow::RetrieveKeyedSection(ResType inType)
{
	OSErr		error = noErr;
	Str255		keyString;
	SInt32		sectionStart;
	
	// Get the key value
	KeyValueToString(inType, keyString);
	
	// Skip all the CASE statements
	SkipNextKeyCases();
	
	// Find the corresponding KEYB tag
	FindKeyStartForValue(keyString, &sectionStart);
	
	// Parse the section
	error = DoRetrieveWithTemplate(sectionStart, true);

	return error;
}


// ---------------------------------------------------------------------------
//	¥ RetrieveDataForType											[public]
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
		error = RetrieveBitField(1, 1);
		break;

		case 'BCNT':
		// Byte count for LSTC lists. Reserve a space for the count. It
		// will be filled later when the LSTC tag is met.
		*mOutStream << (UInt8) 0x00;
		mListCountMark = mOutStream->GetMarker();
		mCountType = inType;
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
		// Cache the current type and position
		mOffsetTypesList.AddItem(inType);
		mOffsetMarksList.AddItem(mOutStream->GetMarker());
		// Temporarily fill with null to create the place holder
		*mOutStream << (UInt8) 0x00;
		break;

		case 'CASE':
		// Increment the current pane ID to skip the case popup
		mCurrentID++;
		// Skip the following CASE statements
		error = SkipNextKeyCases();
		break;

		case 'CHAR':
		// A single character
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(theString);
		if (theString[0] == 0) {
			*mOutStream << (UInt8) 0x00;
		} else {
			*mOutStream << (UInt8) theString[1];
		}
		mCurrentID++;
		break;

		case 'COLR': {
			// QuickDraw color RGB triplet
			RGBColor theRGB;
			CColorWell * colorWell = dynamic_cast<CColorWell *>(this->FindPaneByID(mCurrentID));
			ThrowIfNil_( colorWell );
			colorWell->GetColor(theRGB);
			*mOutStream << theRGB.red;
			*mOutStream << theRGB.green;
			*mOutStream << theRGB.blue;
			mCurrentID++;
			break;
		}
		
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
		case 'MDAT':
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(numStr);	
		if ( ! UMiscUtils::ParseDateString(numStr, &theSInt32)) {
			error = err_TmplParseDateFailed;
		} 
		*mOutStream << theSInt32;
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

		case 'DVDR':
		// It is a comment. Just skip it.
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
		if (error == noErr) {
			sscanf(charString, formatString, &theLong);
			*mOutStream << (UInt8) theLong;
			mCurrentID++;
		} 
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
		if (error == noErr) {
			sscanf(charString, formatString, &theLong);
			*mOutStream << (UInt32) theLong;
			mCurrentID++;
		}
		break;

		case 'FWRD':
		case 'HWRD':
		// Hex word
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(numStr);	
		CopyPascalStringToC(numStr, charString);
		::LowercaseText(charString, strlen(charString), (ScriptCode)0);
		error = BuildScanString(charString, formatString, 4);
		if (error == noErr) {
			sscanf(charString, formatString, &theLong);
			*mOutStream << (UInt16) theLong;
			mCurrentID++;
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
		error = RetrieveKeyedSection(inType);
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
		*mOutStream << (UInt32) 0x00000000;
		mListCountMark = mOutStream->GetMarker();
		mCountType = inType;
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
		// Cache the current type and position
		mOffsetTypesList.AddItem(inType);
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
		// Skip the field and the bevel popup button
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
		// Zero-based count for LSTC lists. Reserve a space for the count. It
		// will be filled later when the LSTC tag is met.
		*mOutStream << (UInt32) 0x00000000;
		mListCountMark = mOutStream->GetMarker();
		mCountType = inType;
		break;

		case 'OCNT':
		case 'FCNT':
		case 'WCNT':
		// One-based count for LSTC lists. Reserve a space for the count. It
		// will be filled later when the LSTC tag is met.
		*mOutStream << (UInt16) 0x0000;
		mListCountMark = mOutStream->GetMarker();
		mCountType = inType;
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
			theString[theLength + 1] = 0;
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

		case 'SEPA':
		// Separator. Just skip it.
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
		error = RetrieveBitField(1, 2);
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
		case 'SKIP':
		// Offset to SKPE in word (WSIZ:exclusive or WSKP/SKIP:inclusive)
		// Cache the current type and position
		mOffsetTypesList.AddItem(inType);
		mOffsetMarksList.AddItem(mOutStream->GetMarker());
		// Temporarily fill with null to create the place holder
		*mOutStream << (UInt16) 0x0000;
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
		// Zero-based count for LSTC lists. Reserve a space for the count. It
		// will be filled later when the LSTC tag is met.
		*mOutStream << (UInt16) 0x0000;
		mListCountMark = mOutStream->GetMarker();
		mCountType = inType;
		break;

	  default:
	  UMiscUtils::OSTypeToPString(inType, typeStr);
	  // Handle Hnnn, Cnnn, P0nn, BB0n etc cases here or unrecognized type
	  if (inType >> 24 == 'H') {
		  
		  // Hnnn: a 3-digit hex number; displays $nnn bytes in hex format
		  CDualDataView * theTGB = dynamic_cast<CDualDataView *>(this->FindPaneByID(mCurrentID));
		  WEReference theWE = theTGB->GetInMemoryWasteRef();
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
		  mCurrentID++;
		  
	  } else if (inType >> 24 == 'F') {
		  
		  // Fnnn: a 3-digit hex number; fills with $nnn bytes in hex format
		  CDualDataView * theTGB = dynamic_cast<CDualDataView *>(this->FindPaneByID(mCurrentID));
		  WEReference theWE = theTGB->GetInMemoryWasteRef();
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
			  // Padd with null bytes
			  for (theSInt32 = 0; theSInt32 < reqLength - theLength; theSInt32++) {
				  *mOutStream << (UInt8) 0x00;
			  }
		  } 
		  mCurrentID++;
		  
	  } else if (inType >> 24 == 'C') {
		  
		  // Cnnn: a C string that is $nnn hex bytes long (the last byte is always a 0, 
		  // so the string itself occupies the first $nnn-1 bytes).
		  theWasteEdit = dynamic_cast<CWasteEditView *>(this->FindPaneByID(mCurrentID));
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
			  // Padd with null bytes
			  for (theSInt32 = 0; theSInt32 < reqLength - theLength - 1; theSInt32++) {
				  *mOutStream << (UInt8) 0x00;
			  }
		  } 
		  // Now the ending NULL byte
		  *mOutStream << (UInt8) 0x00;
		  mCurrentID++;
		  
	  } else if (inType >> 24 == 'T') {
		  
		  // Tnnn: a text string with fixed padding that is $nnn hex bytes long 
		  theWasteEdit = dynamic_cast<CWasteEditView *>(this->FindPaneByID(mCurrentID));
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
			  // Padd with null bytes
			  for (theSInt32 = 0; theSInt32 < reqLength - theLength; theSInt32++) {
				  *mOutStream << (UInt8) 0x00;
			  }
		  } 
		  mCurrentID++;

	  } else if ( inType >> 16 == 'P0') {
		  
		  // P0nn: a Pascal string that is $nn hex bytes long. The length byte 
		  // is included in $nn, so the string itself occupies $nn-1 bytes.
		  theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		  theEditText->GetDescriptor(theString);	
		  theLength = theString[0];
		  UMiscUtils::HexNumStringToDecimal(&inType, &reqLength);

		  if (theLength >= reqLength) {
			  // Don't error. Just truncate it.
			  theString[0] = reqLength - 1;
		  }
		  *mOutStream << theString;
		  if (theLength < reqLength) {
			  // Padd with null bytes
			  for (theSInt32 = 0; theSInt32 < reqLength - theLength - 1; theSInt32++) {
				  *mOutStream << (UInt8) 0x00;
			  }
		  } 
		  mCurrentID++;

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
//	¥ RetrieveBitField											[public]
// ---------------------------------------------------------------------------

OSErr
CTmplEditorWindow::RetrieveBitField(UInt16 inBitCount, UInt16 inBytesLen)
{
	OSErr	error = noErr;
	SInt8	i;
	UInt32	val;
	long	theLong;
	Str255	numStr;
	
	if (!mBitSeqInProgress) {
		mBitSeqInProgress = true;
		mBitSeqBytesLen = inBytesLen;
		mBitSeqMax = mBitSeqBytesLen * 8 - 1;
		mBitSeqIndex = 0;
		mBitSeqValue = 0;
	} 
	
	if (inBitCount == 1) {
		LCheckBox * theCheckBox = dynamic_cast<LCheckBox *>(this->FindPaneByID(mCurrentID));
		mBitSeqValue |= theCheckBox->GetValue() ? 1 << mBitSeqIndex : 0 ;
		mBitSeqIndex++;
	} else {
		LEditText * theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(numStr);	
		::StringToNum( numStr, &theLong);
		
		if (theLong >= (1 << inBitCount)) {
			error = err_TmplValueTooLargeInBitsField;
			goto DONE;
		} 
		for (i = 0; i < inBitCount ; i++) {
			val = theLong & (1 << i);
			mBitSeqValue |= val ? (1 << mBitSeqIndex) : 0 ;
			mBitSeqIndex++;
		}		
	}
	
	mCurrentID++;
	
	if (mBitSeqIndex > mBitSeqMax) {
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
//	¥ RetrieveCountValue											[public]
// ---------------------------------------------------------------------------

OSErr
CTmplEditorWindow::RetrieveCountValue()
{
	OSErr	error = noErr;
	SInt32	currMark;
	long	theLong;
	Str255	theString;
	UInt8	theUInt8 = 0;
	UInt16	theUInt16 = 0;
	UInt32	theUInt32 = 0;
	LStaticText	*	theStaticText;

	currMark = mOutStream->GetMarker();
	mOutStream->SetMarker(mListCountMark, streamFrom_Start);
	
	theStaticText = dynamic_cast<LStaticText *>(this->FindPaneByID(mCurrentID));
	theStaticText->GetDescriptor(theString);	
	::StringToNum( theString, &theLong);
	
	switch (mCountType) {
		
		case 'BCNT':
		// Byte count for LSTC lists
		*mOutStream << (UInt8) theLong;
		if (theLong > 7) {
			theLong = 7;
		} 
		mItemsCount = (UInt16) theLong;
		break;
		
		case 'LCNT':
		// One-based long count for LSTC lists
		if (theLong < 0xffff) {
			mItemsCount = theLong;
		} else {
			error = err_TmplListCountTooBig;
		}
		*mOutStream << theLong;
		break;
		
		case 'LZCT':
		// Zero-based count for LSTC lists
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
		break;
		
		case 'OCNT':
		case 'FCNT':
		case 'WCNT':
		// One-based count for LSTC lists
		mItemsCount = (UInt16) theLong;
		if (mCountType != 'FCNT') {
			*mOutStream << mItemsCount;
		} 
		break;
		
		case 'ZCNT':
		// Zero-based count for LSTC lists
		mItemsCount = (UInt16) theLong;
		if (!theLong) {
			theUInt16 = 0xffff;
		} else {
			theUInt16 = (UInt16) --theLong;
		}
		*mOutStream << theUInt16;
		break;
		
	}
	
	mCurrentID++;
	mOutStream->SetMarker(currMark, streamFrom_Start);
	return error;
}


