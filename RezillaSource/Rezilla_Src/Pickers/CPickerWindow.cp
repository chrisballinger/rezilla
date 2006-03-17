// ===========================================================================
// CPickerWindow.cp
// 
//                       Created: 2006-02-23 15:12:16
//             Last modification: 2006-03-16 08:38:41
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
#include "RezillaConstants.h"

#include <LIconPane.h>
#include <LStaticText.h>

extern CWindowMenu * gWindowMenu;


// ---------------------------------------------------------------------------
//  CPickerWindow													[public]
// ---------------------------------------------------------------------------

CPickerWindow::CPickerWindow()
{
	Init();
}


// ---------------------------------------------------------------------------
//  CPickerWindow													[public]
// ---------------------------------------------------------------------------

CPickerWindow::CPickerWindow(
	const SWindowInfo &inWindowInfo )
		: LWindow( inWindowInfo )
{
	Init();
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
	Init();
}


// ---------------------------------------------------------------------------
//  CPickerWindow													[public]
// ---------------------------------------------------------------------------

CPickerWindow::CPickerWindow(
					WindowPtr		inMacWindow,
					LCommander*		inSuperCommander)
		: LWindow(inMacWindow, inSuperCommander)
{
	Init();
}


// ---------------------------------------------------------------------------
//  CPickerWindow													[public]
// ---------------------------------------------------------------------------

CPickerWindow::CPickerWindow(
			       LStream *inStream )
		: LWindow( inStream )
{
	Init();
}


// ---------------------------------------------------------------------------
//  ~CPickerWindow													[public]
// ---------------------------------------------------------------------------

CPickerWindow::~CPickerWindow()
{
	// Remove the window from the window menu.
	gWindowMenu->RemoveWindow(this);
}


// ---------------------------------------------------------------------------
//  Init													[public]
// ---------------------------------------------------------------------------

void
CPickerWindow::Init()
{
	mOwnerDoc = nil;
	mSelectedView = nil;
	SetModelKind(rzom_cPickerWindow);
	SetStampSize(kPickerDefaultStampWidth, kPickerDefaultStampHeight);
}
	

// ---------------------------------------------------------------------------
// FinishCreateSelf												[protected]
// ---------------------------------------------------------------------------

void
CPickerWindow::FinishCreateSelf()
{	
	// The main view containing the CPickerViews
	mContentsView = dynamic_cast<LView *>(this->FindPaneByID(item_EditorContents));
	ThrowIfNil_( mContentsView );
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
				
		case msg_PickerViewSingleClick:
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
				
		case msg_PickerViewDoubleClick:
		Hide();
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
		
		case cmd_EditRez:
		case cmd_EditRezAsType:
		case cmd_EditWithPlugin:
		case cmd_TmplEditRez:
		case cmd_HexEditRez:
		case cmd_RemoveRez:
		case cmd_DuplicateRez:
		outEnabled = false;
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
	Boolean		cmdHandled = true;

	switch (inCommand) {

		case cmd_Copy: 
		case cmd_Cut: {
			break;
		}

		case cmd_Clear: {
			break;
		}

		case cmd_Paste: {
			break;
		}

		case cmd_ActionCut:
		case cmd_ActionPaste:
		case cmd_ActionClear:
		case cmd_ActionTyping: {
			break;
		}

		default:
		cmdHandled = mOwnerDoc->ObeyCommand(inCommand, ioParam);
		break;
	}

	return cmdHandled;
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
	SPoint32			stampLoc;
	CPickerView *		theView;
	TArrayIterator<CPickerView*> iterator(mViewList);
	SInt16				theWidth, theHeight;
	
	theWidth = mStampWidth + 2 * kPickerViewHorizMargin 
				+ kPickerViewHorizSkip;
	theHeight = mStampHeight + 2 * kPickerViewVertMargin 
				+ kPickerViewIDFieldHeight 
				+ kPickerViewVertSkip;
	
	mContentsView->GetFrameSize(frameSize);

	while (iterator.Next(theView)) {
		if (currCol != 0 && (theWidth * (currCol + 1) > frameSize.width) ) {
			currCol = 0;
			currRow++;
		} 
		stampLoc.h = theWidth * currCol;
		stampLoc.v = theHeight * currRow;
		
		theView->PlaceInSuperFrameAt(stampLoc.h, stampLoc.v, Refresh_No);
		currCol++;
	}
	
	// Resize the contents view to get the vertical scrollbar right
	mContentsView->ResizeImageTo(frameSize.width, stampLoc.v + theHeight, false);
	
	Refresh();
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



