// ===========================================================================
// CSTRx_EditorWindow.cp					
// 
//                       Created: 2005-08-31 18:26:24
//             Last modification: 2005-09-04 06:09:00
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CSTRx_EditorDoc.h"
#include "CSTRx_EditorWindow.h"
#include "CIndexedEditField.h"
#include "CRezObj.h"
#include "RezillaConstants.h"
#include "UMessageDialogs.h"

#include <LEditText.h>
#include <LStaticText.h>
#include <LTabGroupView.h>

#include <stdio.h>

SPaneInfo CSTRx_EditorWindow::sPaneInfo;
SViewInfo CSTRx_EditorWindow::sViewInfo;

// ---------------------------------------------------------------------------
//  CSTRx_EditorWindow				[public]
// ---------------------------------------------------------------------------

CSTRx_EditorWindow::CSTRx_EditorWindow()
{
}


// ---------------------------------------------------------------------------
//  CSTRx_EditorWindow				[public]
// ---------------------------------------------------------------------------

CSTRx_EditorWindow::CSTRx_EditorWindow(
	const SWindowInfo &inWindowInfo )
		: CEditorWindow( inWindowInfo )
{
}


// ---------------------------------------------------------------------------
//  CSTRx_EditorWindow				[public]
// ---------------------------------------------------------------------------

CSTRx_EditorWindow::CSTRx_EditorWindow(
	ResIDT		inWINDid,
	UInt32		inAttributes,
	LCommander	*inSuperCommander )
		: CEditorWindow( inWINDid, inAttributes, inSuperCommander )
{
}


// ---------------------------------------------------------------------------
//  CSTRx_EditorWindow				[public]
// ---------------------------------------------------------------------------

CSTRx_EditorWindow::CSTRx_EditorWindow(
			       LStream *inStream )
		: CEditorWindow( inStream )
{
}


// ---------------------------------------------------------------------------
//  ~CSTRx_EditorWindow				[public]
// ---------------------------------------------------------------------------

CSTRx_EditorWindow::~CSTRx_EditorWindow()
{	
	if (mOutStream != nil) {
		delete mOutStream;
	} 
}


// ---------------------------------------------------------------------------
// FinishCreateSelf												[protected]
// ---------------------------------------------------------------------------

void
CSTRx_EditorWindow::FinishCreateSelf()
{	
	mOutStream = nil;
	
	// The main view containing the editing fields
	mContentsView = dynamic_cast<LView *>(this->FindPaneByID(item_EditorContents));
	ThrowIfNil_( mContentsView );

// 	mTGV = dynamic_cast<LTabGroupView *>(this->FindPaneByID( item_TabGroup ));
// 	ThrowIfNil_( mTGV );
	
	// View info
	sViewInfo.imageSize.width	= sViewInfo.imageSize.height	= 0 ;
	sViewInfo.scrollPos.h		= sViewInfo.scrollPos.v			= 0;
	sViewInfo.scrollUnit.h		= sViewInfo.scrollUnit.v		= kStrxHeight;
	sViewInfo.reconcileOverhang	= false;
	
	// Pane info
	sPaneInfo.left				= 0;
	sPaneInfo.height			= kStrxHeight;
	sPaneInfo.visible			= true;
	sPaneInfo.enabled			= true;
	sPaneInfo.bindings.left		= true;
	sPaneInfo.bindings.top		= false;
	sPaneInfo.bindings.right	= true;
	sPaneInfo.bindings.bottom 	= false;
	sPaneInfo.userCon			= 0;
	sPaneInfo.paneID			= 0;
	sPaneInfo.superView			= mContentsView;

	// Link the broadcasters
	UReanimator::LinkListenerToControls( this, this, PPob_MenuEditorWindow );
	
}


// ---------------------------------------------------------------------------
//  ListenToMessage													[public]
// ---------------------------------------------------------------------------

void
CSTRx_EditorWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{		
	switch (inMessage) {		
		
// 		case msg_DragMoveAction: 
// 		ArrayIndexT	oldIndex = mMenuObj->GetItemIndex();
// 		ArrayIndexT	newIndex = *(ArrayIndexT *) ioParam;
// 		mMenuObj->GetItems()->MoveItem(oldIndex, newIndex);
// 		mMenuObj->SetItemIndex(newIndex);
// 		SetDirty(true);
// 		break;
		
						
		case msg_MinusButton: {
			if (mIndexedFields.GetCount() == 0) {return;} 
			if (DeleteSelected() > 0) {
				RecalcAllPositions();
			} else {
				// If no item selected, delete the last one
				CIndexedEditField *	theField;
				if ( mIndexedFields.FetchItemAt(mIndexedFields.GetCount(), theField) ) {
					theField->Hide();
					mIndexedFields.RemoveItemsAt(1, mIndexedFields.GetCount());
				} 
			}
			mContentsView->ResizeImageTo(0, mIndexedFields.GetCount() * kStrxHeight, false);
			SetDirty(true);
			Refresh();
			break;
		}
				
		case msg_PlusButton: {
			UInt16 index = GetFirstSelected();
			mContentsView->Deactivate();
			mContentsView->Hide();
			InsertStringItemAtIndex(index, "\p");
			mContentsView->ResizeImageTo(0, mIndexedFields.GetCount() * kStrxHeight, false);
			SetDirty(true);
			mContentsView->Show();
			mContentsView->Enable();
			mContentsView->Activate();
			break;
		}
		

		default:
		dynamic_cast<CSTRx_EditorDoc *>(mOwnerDoc)->ListenToMessage(inMessage, ioParam);
		break;
				
	}
}


// ---------------------------------------------------------------------------
//	 FindCommandStatus
// ---------------------------------------------------------------------------

void
CSTRx_EditorWindow::FindCommandStatus(
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
//	 ObeyCommand							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CSTRx_EditorWindow::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;
	
	switch (inCommand) {

		default:
			cmdHandled = LCommander::ObeyCommand(inCommand, ioParam);
			break;
	}

	return cmdHandled;
}


// ---------------------------------------------------------------------------
//	 InstallResourceData											[public]
// ---------------------------------------------------------------------------

OSErr
CSTRx_EditorWindow::InstallResourceData(Handle inHandle)
{
	OSErr		error = noErr, ignoreErr = noErr;
	UInt16		numItems = 0;
	StHandleLocker	locker(inHandle);
	
	LHandleStream * theStream = new LHandleStream(inHandle);
	
	if ( theStream->GetLength() == 0 ) {
		// We are creating a new resource
	} else {
		*theStream >> numItems;
		
		for (UInt16 i = 1; i <= numItems; i++) {
			Str255		theString;
			if ( theStream->GetMarker() < theStream->GetLength() ) {
				*theStream >> theString;
				AddStringItem(theString);
			}
		}
		
		// Check that all the data have been parsed
		if ( theStream->GetMarker() < theStream->GetLength() ) {
			error = err_MoreDataThanExpected;
		} 
	}
	
	delete theStream;
	
	if (error == noErr) {
		// Adjust the size of the image
		mContentsView->ResizeImageTo(0, numItems * kStrxHeight, false);
		SetDirty(false);
	} 
	
	return error;
}


// ---------------------------------------------------------------------------
//  AddStringItem													[public]
// ---------------------------------------------------------------------------

void
CSTRx_EditorWindow::AddStringItem(Str255 inString)
{
	InsertStringItemAtIndex(0, inString);
}


// ---------------------------------------------------------------------------
//  InsertStringItemAtIndex											[public]
// ---------------------------------------------------------------------------

void
CSTRx_EditorWindow::InsertStringItemAtIndex(UInt16 index, Str255 inString)
{
	SDimension16	frameSize;
	UInt16			maxIndex = mIndexedFields.GetCount() + 1;
	
	if (index == 0) {
		index = maxIndex;
	} 
	mContentsView->GetFrameSize(frameSize);

	// Pane info
	sPaneInfo.top	= (index - 1) * kStrxHeight;
	sPaneInfo.width	= frameSize.width;
	
	CIndexedEditField * theField = new CIndexedEditField(sPaneInfo, sViewInfo, index, inString);
	if (index == maxIndex) {
		mIndexedFields.AddItem(theField);
	} else {
		mIndexedFields.InsertItemsAt(1, index, theField);
		RecalcPositionsFrom(index + 1);
	}
}


// ---------------------------------------------------------------------------
//  RecalcPositionsFrom												  [public]
// ---------------------------------------------------------------------------

void
CSTRx_EditorWindow::RecalcPositionsFrom(UInt16 index)
{
	CIndexedEditField * theField;
		
	for (UInt16 i = index; i <= mIndexedFields.GetCount(); i++) {
		if ( mIndexedFields.FetchItemAt(i, theField) ) {
			theField->SetIndexField(i);
			theField->MoveBy(0, kStrxHeight, false);
		} 
	}	
}


// ---------------------------------------------------------------------------
//  RecalcAllPositions												  [public]
// ---------------------------------------------------------------------------

void
CSTRx_EditorWindow::RecalcAllPositions()
{
	UInt16	index = 1;
	SInt32	oldPos, newPos;
	Rect	theFrame;
	
	TArrayIterator<CIndexedEditField*> iterator(mIndexedFields);
	CIndexedEditField *	theField;

	while (iterator.Next(theField)) {
		theField->SetIndexField(index);
		
		theField->CalcPortFrameRect(theFrame);
		mContentsView->PortToLocalPoint(topLeft(theFrame));

		oldPos = theFrame.top;
		newPos = (index - 1) * kStrxHeight;
		theField->MoveBy(0, newPos - oldPos, false);
		index++;
	}
}


// ---------------------------------------------------------------------------
//  GetFirstSelected												  [public]
// ---------------------------------------------------------------------------

UInt16
CSTRx_EditorWindow::GetFirstSelected()
{
	UInt16 result = 0, index = 0;
	TArrayIterator<CIndexedEditField*> iterator(mIndexedFields);
	CIndexedEditField *	theField;

	while (iterator.Next(theField)) {
		index++;
		if ( theField->IsSelected() ) {
			result = index;
			break;
		} 
	}
	
	return result;
}


// ---------------------------------------------------------------------------
//  DeleteSelected												  [public]
// ---------------------------------------------------------------------------

UInt16
CSTRx_EditorWindow::DeleteSelected()
{
	UInt16 count = 0;

	TArrayIterator<LPane*> iterator(mContentsView->GetSubPanes(), LArrayIterator::from_End);
	LPane *				theSub;
	CIndexedEditField *	theField;
	ArrayIndexT			theIndex;
	
	while (iterator.Previous(theSub)) {
		theField = dynamic_cast<CIndexedEditField*>(theSub);
		if ( theField != nil && theField->IsSelected() ) {
// 			mContentsView->GetSubPanes().RemoveItemsAt(1, iterator.GetCurrentIndex());
// 			delete theSub;
			theSub->Hide();			
			theIndex = mIndexedFields.FetchIndexOf(theField);
			if (theIndex != LArray::index_Bad) {
				mIndexedFields.RemoveItemsAt(1, theIndex);
			} 
			count++;
		} 
	}
	
	return count;
}


// ---------------------------------------------------------------------------
//  CollectResourceData												[public]
// ---------------------------------------------------------------------------
// Retrieve the contents of the current panel

Handle
CSTRx_EditorWindow::CollectResourceData() 
{
	Handle	theHandle = NULL;
	Str255	theString;
	UInt16	numStrings = mIndexedFields.GetCount();
	
	try {
		if (mOutStream != nil) {delete mOutStream;} 

		mOutStream = new LHandleStream();	
		ThrowIfNil_(mOutStream);

		*mOutStream << numStrings;

		TArrayIterator<CIndexedEditField*> iterator(mIndexedFields);
		CIndexedEditField *	theField;

		while (iterator.Next(theField)) {
			theField->GetDescriptor(theString);
			*mOutStream << theString;
		}
		theHandle = mOutStream->GetDataHandle();
	}
	catch (...) {
// 		UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("SaveStringsFailed"), PPob_SimpleMessage);
	}
	
	return theHandle;
}


// ---------------------------------------------------------------------------
//  RevertContents												  [public]
// ---------------------------------------------------------------------------

void
CSTRx_EditorWindow::RevertContents()
{
	OSErr error = noErr;
	
	// Delete the panes
	mContentsView->DeleteAllSubPanes();
	// Reset the array
	mIndexedFields.RemoveAllItemsAfter(0);

	mContentsView->Hide();
	
	// Reinstall the strings
	CRezObj * theRezObj = mOwnerDoc->GetRezObj();
	if (theRezObj != nil) {
		Handle rezData = theRezObj->GetData();
		
		try {
			if (rezData != nil) {
				// Work with a copy of the handle
				::HandToHand(&rezData);
				error = InstallResourceData(rezData);			
			} 
			ThrowIfError_(error);			
		} catch (...) {
			UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("DataParsingException"), PPob_SimpleMessage);
			return;
		}
	} 
	
	mContentsView->Show();
	mContentsView->Enable();
	Refresh();
	SetDirty(false);
}

