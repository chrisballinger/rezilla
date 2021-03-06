// ===========================================================================
// CPickerWindow.cp
// 
//                       Created: 2006-02-23 15:12:16
//             Last modification: 2006-10-15 06:56:45
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================


#include "CPickerWindow.h"
#include "CPickerDoc.h"
#include "CPickerView.h"
#include "CRezObj.h"
#include "CWindowMenu.h"
#include "UCompareUtils.h"
#include "RezillaConstants.h"

#include <LIconPane.h>
#include <LStaticText.h>

extern CWindowMenu * gWindowMenu;


// ---------------------------------------------------------------------------
//  CPickerWindow													[public]
// ---------------------------------------------------------------------------

CPickerWindow::CPickerWindow()
{
	Initialize();
}


// ---------------------------------------------------------------------------
//  CPickerWindow													[public]
// ---------------------------------------------------------------------------

CPickerWindow::CPickerWindow(
	const SWindowInfo &inWindowInfo )
		: LWindow( inWindowInfo )
{
	Initialize();
}


// ---------------------------------------------------------------------------
//  CPickerWindow													[public]
// ---------------------------------------------------------------------------

CPickerWindow::CPickerWindow(
	ResIDT		inWINDid,
	UInt32		inAttributes,
	LCommander	*inSuperCommander )
		: LWindow( inWINDid, inAttributes, inSuperCommander )
{
	Initialize();
}


// ---------------------------------------------------------------------------
//  CPickerWindow													[public]
// ---------------------------------------------------------------------------

CPickerWindow::CPickerWindow(
					WindowPtr		inMacWindow,
					LCommander*		inSuperCommander)
		: LWindow(inMacWindow, inSuperCommander)
{
	Initialize();
}


// ---------------------------------------------------------------------------
//  CPickerWindow													[public]
// ---------------------------------------------------------------------------

CPickerWindow::CPickerWindow(
			       LStream *inStream )
		: LWindow( inStream )
{
	Initialize();
}


// ---------------------------------------------------------------------------
//  ~CPickerWindow													[public]
// ---------------------------------------------------------------------------

CPickerWindow::~CPickerWindow()
{
	// Delete the Picker views
	TArrayIterator<CPickerView*> iterator(*mViewList, LArrayIterator::from_End);
	CPickerView	* theView;
	while (iterator.Previous(theView)) {
		mViewList->RemoveItemsAt(1, iterator.GetCurrentIndex());
		delete theView;
	}
	
	if (mViewList != nil) {
		delete mViewList;
	} 

	// Remove the window from the window menu.
	gWindowMenu->RemoveWindow(this);
}


// ---------------------------------------------------------------------------
//  Initialize													[private]
// ---------------------------------------------------------------------------

void
CPickerWindow::Initialize()
{
	mOwnerDoc = nil;
	mSelectedView = nil;
	
	SetModelKind(rzom_cPickerWindow);
	SetStampSize(kPickerDefaultStampWidth, kPickerDefaultStampHeight);
	
	// Initialize the PickerViews list
	CPickerViewComparator* theComparator = new CPickerViewComparator();
	mViewList = new TArray<CPickerView *>( theComparator, true);
}
	

// ---------------------------------------------------------------------------
// FinishCreateSelf												[protected]
// ---------------------------------------------------------------------------

void
CPickerWindow::FinishCreateSelf()
{	
	mType = 0;

	// The main view containing the CPickerViews
	mContentsView = dynamic_cast<LView *>(this->FindPaneByID(item_EditorContents));
	ThrowIfNil_( mContentsView );

	mRezCountField = dynamic_cast<LStaticText *>(this->FindPaneByID(item_PickerRezCountField));
	ThrowIfNil_( mRezCountField );
}


// ---------------------------------------------------------------------------
//  FinalizePicker													[public]
// ---------------------------------------------------------------------------

void
CPickerWindow::FinalizePicker(CPickerDoc* inPickerDoc, void * ioParam)
{
#pragma unused(ioParam)
	
	SetOwnerDoc(inPickerDoc);
	InstallReadOnlyIcon();

	SetSuperModel(inPickerDoc);
	
	// Add the window to the window menu.
	gWindowMenu->InsertWindow(this);
}
	

// ---------------------------------------------------------------------------
//  ListenToMessage													[public]
// ---------------------------------------------------------------------------

void
CPickerWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{
	
	switch (inMessage) {
		
		case msg_Close:
		Hide();
		break;
				
		case msg_PickerViewSingleClick: {
			CPickerView * theView = (CPickerView*) ioParam;
			if (theView == NULL) {return;} 
			if (mSelectedView == theView) {
				mSelectedView->DrawBorder(false);
				mSelectedView = NULL;
			} else {
				if (mSelectedView) {
					mSelectedView->DrawBorder(false);
				} 
				mSelectedView = theView;
				mSelectedView->DrawBorder(true);
			}
			break;
		}
				
		case msg_PickerViewDoubleClick:
		ObeyCommand(cmd_EditRez, NULL);
		break;
				
		default:
		dynamic_cast<CPickerDoc *>(GetSuperCommander())->ListenToMessage(inMessage, ioParam);
		break;
				
	}
}


// ---------------------------------------------------------------------------
//  FindCommandStatus
// ---------------------------------------------------------------------------
//	Pass back whether a Command is enabled and/or marked (in a Menu)

void
CPickerWindow::FindCommandStatus(
	CommandT	inCommand,
	Boolean		&outEnabled,
	Boolean		&outUsesMark,
	UInt16		&outMark,
	Str255		outName)
{
	switch (inCommand) {
		
		case cmd_Copy:
		case cmd_EditRez:
		case cmd_EditRezAsType:
		case cmd_EditWithPlugin:
		case cmd_TmplEditRez:
		case cmd_HexEditRez:
		case cmd_RemoveRez:
		case cmd_DuplicateRez:
		case cmd_GetRezInfo: 
		outEnabled = (mSelectedView != NULL);
		break;		
		
		default:
		if (mOwnerDoc) {
			mOwnerDoc->FindCommandStatus(inCommand, outEnabled,
												outUsesMark, outMark, outName);
		} else {
			LCommander::FindCommandStatus(inCommand, outEnabled,
												outUsesMark, outMark, outName);
		}
		break;
	}
}


// ---------------------------------------------------------------------------
//  ObeyCommand												[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CPickerWindow::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	if (mOwnerDoc != NULL) {
		return (mOwnerDoc->ObeyCommand(inCommand, ioParam));
	} else {
		return (LCommander::ObeyCommand(inCommand, ioParam));
	}
}


// ---------------------------------------------------------------------------
//   HandleKeyPress												  [public]
// ---------------------------------------------------------------------------

Boolean
CPickerWindow::HandleKeyPress(
	const EventRecord&	inKeyEvent)
{
	Boolean		keyHandled	= true;
	LControl*	keyButton	= nil;
	UInt8		theChar		= (UInt8) (inKeyEvent.message & charCodeMask);
	
	if (inKeyEvent.modifiers & cmdKey) {
		return keyHandled;
	} 
	
	if (theChar == char_LeftArrow) {
		this->RotateSelection( -1, 0 );
	} else if (theChar == char_RightArrow) {
		this->RotateSelection( 1, 0 );
	} else if (theChar == char_UpArrow) {
		this->RotateSelection( 0, -1 );
	} else if (theChar == char_DownArrow) {
		this->RotateSelection( 0, 1 );
	} else if (theChar == char_Backspace || theChar == char_Clear) {
		mOwnerDoc->ObeyCommand(cmd_RemoveRez, NULL);
	} else {
		keyHandled = LWindow::HandleKeyPress(inKeyEvent);
	}
	
	return keyHandled;
}


// ---------------------------------------------------------------------------
// DrawSelf
// ---------------------------------------------------------------------------

void
CPickerWindow::DrawSelf()
{
	LWindow::DrawSelf();
	if (mSelectedView) {
		mSelectedView->DrawBorder(true);
	} 
}


// ---------------------------------------------------------------------------
// 	RotateSelection
// ---------------------------------------------------------------------------

void
CPickerWindow::RotateSelection( SInt32 dh, SInt32 dv )
{
	ArrayIndexT	currIndex, trgtIndex;
	
	if (!mSelectedView) {
		// If no selection, select the first view
		trgtIndex = 1;
	} else {
		mSelectedView->DrawBorder(false); 
		currIndex = mViewList->FetchIndexOf(mSelectedView);
		
		if (currIndex != LArray::index_Bad) {
			if (dh == 1) {
				trgtIndex = currIndex + 1;
			} else if (dh == -1) {
				trgtIndex = currIndex - 1;
			} else {
				SInt16	viewsPerRow = CalcViewsPerRow();
				if (dv == 1) {
					trgtIndex = currIndex + viewsPerRow;
				} else if (dv == -1) {
					trgtIndex = currIndex - viewsPerRow;
				} 
			}
			if (trgtIndex <= 0) {
				trgtIndex = mViewList->GetCount();
			} 
			if (trgtIndex > mViewList->GetCount()) {
				trgtIndex = 1;
			} 
		}
	}
	if (! mViewList->FetchItemAt(trgtIndex, mSelectedView)) {
		mSelectedView = NULL;
	} else {
		// Scroll the contents view if necessary
		Rect			frameRect, visRect;

		mSelectedView->CalcPortFrameRect(frameRect);
		mSelectedView->CalcPortExposedRect(visRect);
		if (not ::EqualRect(&frameRect,&visRect)) {
			mContentsView->PortToLocalPoint(topLeft(frameRect));
			mContentsView->ScrollImageTo(0, frameRect.top - kPickerWindowVertOffset, true);
		}
		mSelectedView->DrawBorder(true); 
	}
}


// ---------------------------------------------------------------------------
//   InstallReadOnlyIcon											[public]
// ---------------------------------------------------------------------------

void
CPickerWindow::InstallReadOnlyIcon() 
{
	LIconPane * theIcon = dynamic_cast<LIconPane *>(this->FindPaneByID( item_ReadOnlyIcon ));
	if (theIcon != NULL) {
		if (mOwnerDoc->IsReadOnly()) {
			theIcon->SetIconID(ics8_Locked);
		} else {
			theIcon->SetIconID(ics8_Unlocked);
		}
	} 
}


// ---------------------------------------------------------------------------
//   DoSetBounds
// ---------------------------------------------------------------------------

void
CPickerWindow::DoSetBounds(
	const Rect&		inBounds)
{
	LWindow::DoSetBounds(inBounds);
	RecalcLayout();
}


// ---------------------------------------------------------------------------
//   RecalcLayout
// ---------------------------------------------------------------------------

void
CPickerWindow::RecalcLayout()
{
	int					currCol = 0, currRow = 0;
	SDimension16		frameSize;
	SPoint32			viewLoc;
	CPickerView *		theView;
	TArrayIterator<CPickerView*> iterator(*mViewList);
	SInt16				theWidth, theHeight;
	
	theWidth = mStampWidth + 2 * kPickerViewHorizMargin;
	theHeight = mStampHeight + 2 * kPickerViewVertMargin + kPickerViewIDFieldHeight;
	
	if (theWidth < kPickerViewMinWidth) {
		theWidth = kPickerViewMinWidth;
	} 
	if (theHeight < kPickerViewMinHeight) {
		theHeight = kPickerViewMinHeight;
	} 
	
	theWidth += kPickerViewHorizSkip;
	theHeight += kPickerViewVertSkip;

	mContentsView->GetFrameSize(frameSize);

	while (iterator.Next(theView)) {
		if (currCol != 0 && (theWidth * (currCol + 1) + kPickerWindowHorizOffset > frameSize.width) ) {
			currCol = 0;
			currRow++;
		} 
		viewLoc.h = theWidth * currCol + kPickerWindowHorizOffset;
		viewLoc.v = theHeight * currRow + kPickerWindowVertOffset;
		
		theView->PlaceInSuperImageAt(viewLoc.h, viewLoc.v, Refresh_No);
		currCol++;
	}
	
	// Resize the contents view to get the vertical scrollbar right
	mContentsView->ResizeImageTo(frameSize.width, viewLoc.v + theHeight, false);
	
	Refresh();
}


// ---------------------------------------------------------------------------
//   CalcViewsPerRow
// ---------------------------------------------------------------------------

SInt16
CPickerWindow::CalcViewsPerRow()
{
	SDimension16	frameSize;
	SInt16			theWidth, theNum;
	
	theWidth = mStampWidth + 2 * kPickerViewHorizMargin;
	if (theWidth < kPickerViewMinWidth) {
		theWidth = kPickerViewMinWidth;
	} 
	theWidth += kPickerViewHorizSkip;

	mContentsView->GetFrameSize(frameSize);

	theNum = (frameSize.width - kPickerWindowHorizOffset) / theWidth;
	if (theNum == 0) {
		theNum = 1;
	} 

	return theNum;
}


// ---------------------------------------------------------------------------
//   GetRezCountField											[public]
// ---------------------------------------------------------------------------

long
CPickerWindow::GetRezCountField() const
{
	long result;
	Str255 theString;
	
	mRezCountField->GetDescriptor(theString);
	::StringToNum(theString, &result);
	return result;
}


// ---------------------------------------------------------------------------
//   SetRezCountField											[public]
// ---------------------------------------------------------------------------

void
CPickerWindow::SetRezCountField(long inCount) 
{
	Str255 theString;
	::NumToString(inCount, theString);
	mRezCountField->SetDescriptor(theString);
}


// ---------------------------------------------------------------------------
//   IncrRezCountField											[public]
// ---------------------------------------------------------------------------
// in can be < 0 to decrement the RezCountField

void
CPickerWindow::IncrRezCountField(long inDelta) 
{
	long count = GetRezCountField();
	count += inDelta;
	if (count < 0) {
		count = 0;
	} 
	SetRezCountField(count);
}


// ---------------------------------------------------------------------------
//   GetStampSize													[public]
// ---------------------------------------------------------------------------

void
CPickerWindow::GetStampSize(SInt16 &outWidth, SInt16 &outHeight) 
{
	outWidth = mStampWidth;
	outHeight = mStampHeight;
}


// ---------------------------------------------------------------------------
//   SetStampSize													[public]
// ---------------------------------------------------------------------------

void
CPickerWindow::SetStampSize(SInt16 inWidth, SInt16 inHeight) 
{
	mStampWidth = inWidth;
	mStampHeight = inHeight;
}


// ---------------------------------------------------------------------------
//   AddPickerView
// ---------------------------------------------------------------------------

void
CPickerWindow::AddPickerView( CPickerView* inView )
{
	mViewList->InvalidateSort();
	mViewList->AddItem(inView);
}


// ---------------------------------------------------------------------------
//   RemovePickerView
// ---------------------------------------------------------------------------

void
CPickerWindow::RemovePickerView( CPickerView* inView )
{
	mViewList->Remove(inView);
}


// ---------------------------------------------------------------------------
//   DeletePickerView
// ---------------------------------------------------------------------------

void
CPickerWindow::DeletePickerView( short inID )
{
	CPickerView *	theView = FindPickerView(inID);
	DeletePickerView(theView);
}


// ---------------------------------------------------------------------------
//   DeletePickerView
// ---------------------------------------------------------------------------

void
CPickerWindow::DeletePickerView( CPickerView* inView )
{
	if (inView) {
		RemovePickerView(inView);
		if (mSelectedView == inView) {
			mSelectedView = NULL;
		} 
		delete inView;
		RecalcLayout();
	}
}


// ---------------------------------------------------------------------------
//   FindPickerView
// ---------------------------------------------------------------------------

CPickerView *
CPickerWindow::FindPickerView( short inID ) 
{
	TArrayIterator<CPickerView*> iterator(*mViewList);
	CPickerView		*theView = NULL, *currView;

	while (iterator.Next(currView)) {
		if (currView->GetPaneID() == inID) {
			theView = currView;
			break;
		} 
	}
	
	return theView;
}

