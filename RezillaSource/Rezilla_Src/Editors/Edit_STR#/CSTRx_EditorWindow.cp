// ===========================================================================
// CSTRx_EditorWindow.cp					
// 
//                       Created: 2005-08-31 18:26:24
//             Last modification: 2006-09-18 19:53:08
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2005-2006
// All rights reserved.
// ===========================================================================

#include "CSTRx_EditorDoc.h"
#include "CSTRx_EditorWindow.h"
#include "CIndexedEditField.h"
#include "CRezObj.h"
#include "RezillaConstants.h"
#include "UMessageDialogs.h"
#include "UDragAndDropUtils.h"

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
		: LDragAndDrop( UQDGlobals::GetCurrentWindowPort(), this )
{
	// Initialize the drop index to a bad value
	mDropIndex = -1;
}


// ---------------------------------------------------------------------------
//  CSTRx_EditorWindow				[public]
// ---------------------------------------------------------------------------

CSTRx_EditorWindow::CSTRx_EditorWindow(
	const SWindowInfo &inWindowInfo )
		: CEditorWindow( inWindowInfo ),
		LDragAndDrop( UQDGlobals::GetCurrentWindowPort(), this )
{
	// Initialize the drop index to a bad value
	mDropIndex = -1;
}


// ---------------------------------------------------------------------------
//  CSTRx_EditorWindow				[public]
// ---------------------------------------------------------------------------

CSTRx_EditorWindow::CSTRx_EditorWindow(
	ResIDT		inWINDid,
	UInt32		inAttributes,
	LCommander	*inSuperCommander )
		: CEditorWindow( inWINDid, inAttributes, inSuperCommander ),
		LDragAndDrop( UQDGlobals::GetCurrentWindowPort(), this )
{
	// Initialize the drop index to a bad value
	mDropIndex = -1;
}


// ---------------------------------------------------------------------------
//  CSTRx_EditorWindow				[public]
// ---------------------------------------------------------------------------

CSTRx_EditorWindow::CSTRx_EditorWindow(
			       LStream *inStream )
		: CEditorWindow( inStream ),
		LDragAndDrop( UQDGlobals::GetCurrentWindowPort(), this )
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


// ---------------------------------------------------------------------------------
//  Click
// ---------------------------------------------------------------------------------

void
CSTRx_EditorWindow::Click(
	SMouseDownEvent	&inMouseDown )
{
	// In order to support dragging from an inactive window, we must
	// explicitly test for delaySelect
	if ( inMouseDown.delaySelect ) {
		// Convert to a local point
		PortToLocalPoint( inMouseDown.whereLocal );
		
		// Execute click attachments
		if ( ExecuteAttachments( msg_Click, &inMouseDown ) ) {		
			// Handle the actual click event
			ClickSelf( inMouseDown );
		}
	} else {
		// Call inherited for default behavior
		LWindow::Click( inMouseDown );
	}
}


// ---------------------------------------------------------------------------
//  ListenToMessage													[public]
// ---------------------------------------------------------------------------

void
CSTRx_EditorWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{		
	switch (inMessage) {
						
		case msg_MinusButton: {
			if (mIndexedFields.GetCount() == 0) {return;} 
			if (DeleteSelectedItems() > 0) {
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
			UInt16	index = GetFirstSelected();
			SInt32 	theVal = 1;
			if ( ::GetCurrentEventKeyModifiers() & optionKey) {
				if ( ! UMessageDialogs::GetOneValue(this, CFSTR("HowManyItems"), PPob_GetValueDialog, 
											   item_PromptField, item_ValueField, theVal) 
					|| theVal == 0) {
					return;
				}
			}			
			CreateItemAtIndex(index, "\p", theVal);
			SetDirty(true);
			break;
		}
		

		case msg_EditorModifiedItem:
		SetDirty(true);
		break;
		
		
		default:
		dynamic_cast<CSTRx_EditorDoc *>(mOwnerDoc)->ListenToMessage(inMessage, ioParam);
		break;
				
	}
}


// ---------------------------------------------------------------------------
//   HandleKeyPress												  [public]
// ---------------------------------------------------------------------------
// Tab switches the Target to the next edit field in the window, Shift-Tab
// to the previous item. All other keystrokes are ignored.

Boolean
CSTRx_EditorWindow::HandleKeyPress(
	const EventRecord&	inKeyEvent)
{
	Boolean	keyHandled = true;
	UInt16	theChar = (UInt16) (inKeyEvent.message & charCodeMask);
	
	if (theChar == char_Tab) {
		ArrayIndexT			index;
		CIndexedEditField *	theField;
		LCommander *		currTabTarget = GetTarget();

		if (currTabTarget == nil) {	
			index = 1;
		} else {
			LEditText * theEditText = dynamic_cast<LEditText *>(currTabTarget);
			if (theEditText != nil) {
				theField = dynamic_cast<CIndexedEditField *>(theEditText->GetSuperView());
				// Find the index of the field
				index = mIndexedFields.FetchIndexOf(theField);
				if (index != LArray::index_Bad) {
					// Switch to next index (if shift, go backwards)
					if ((inKeyEvent.modifiers & shiftKey) != 0) {
						if (index == 1) {
							index = mIndexedFields.GetCount();
						} else {
							index--;
						}
					} else {
						if (index == mIndexedFields.GetCount()) {
							index = 1;
						} else {
							index++;
						}
					}
				}
			} 
		}
		if ( mIndexedFields.FetchItemAt(index, theField) ) {
			SwitchTarget(theField->GetEditText());
		} 
	}
	
	return keyHandled;
}


// ---------------------------------------------------------------------------
//	 InstallResourceData											[public]
// ---------------------------------------------------------------------------
//	 ITML	RSID (eq DWRD)
//	 MBAR	DWRD
//	 RID#	DWRD
//	 Mcmd	DLNG
//	 RidL	DLNG
//	 typ#	TNAM

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
			SInt16		theSInt16;
			long		theLong;

			if ( theStream->GetMarker() < theStream->GetLength() ) {
				switch (mOwnerDoc->GetSubstType()) {
					case 'STR#':
					*theStream >> theString;
					break;
					
					case 'MBAR':
					*theStream >> theSInt16;
					::NumToString( (long) theSInt16, theString);
					break;
					
					case 'Mcmd':
					case 'RidL':
					*theStream >> theLong;
					::NumToString( theLong, theString);
					break;
					
				}
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
//  CreateItemAtIndex												[public]
// ---------------------------------------------------------------------------

void
CSTRx_EditorWindow::CreateItemAtIndex(UInt16 index, Str255 inString, SInt32 inHowMany)
{
	mContentsView->Deactivate();
	mContentsView->Hide();
	for (SInt32 i = 0; i < inHowMany; i++) {
		InsertStringItemAtIndex(index, inString);
	}	
	RecalcPositionsInRange(index + 1, mIndexedFields.GetCount());
	mContentsView->ResizeImageTo(0, mIndexedFields.GetCount() * kStrxHeight, false);
	mContentsView->Show();
	mContentsView->Enable();
	mContentsView->Activate();
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
	
	ResType theType = GetOwnerDoc()->GetSubstType();
	SInt16			maxChar;
	TEKeyFilterFunc	filter;
	
	switch (mOwnerDoc->GetSubstType()) {
		case 'STR#':
		maxChar = 255;
		filter = UKeyFilters::SelectTEKeyFilter(keyFilter_PrintingCharAndCR);
		break;
		
		case 'MBAR':
		case 'Mcmd':
		case 'RidL':
		maxChar = 6;
		filter = UKeyFilters::SelectTEKeyFilter(keyFilter_NegativeInteger);
		break;
		
	}
	
	CIndexedEditField * theField = new CIndexedEditField(this, sPaneInfo, sViewInfo, index, inString, maxChar, filter);
	if (index == maxIndex) {
		mIndexedFields.AddItem(theField);
	} else {
		mIndexedFields.InsertItemsAt(1, index, theField);
	}
}


// ---------------------------------------------------------------------------
//  RecalcPositionAtIndex											[private]
// ---------------------------------------------------------------------------

void
CSTRx_EditorWindow::RecalcPositionAtIndex(UInt16 index)
{
	CIndexedEditField * theField;

	if ( mIndexedFields.FetchItemAt(index, theField) ) {
		SInt32	oldPos, newPos;
		Rect	theFrame;
		
		theField->SetIndexField(index);
		theField->CalcPortFrameRect(theFrame);
		mContentsView->PortToLocalPoint(topLeft(theFrame));
		oldPos = theFrame.top;
		newPos = (index - 1) * kStrxHeight;
		theField->MoveBy(0, newPos - oldPos, false);
	} 
}


// ---------------------------------------------------------------------------
//  RecalcAllPositions												[private]
// ---------------------------------------------------------------------------

void
CSTRx_EditorWindow::RecalcAllPositions()
{
	RecalcPositionsInRange(1, mIndexedFields.GetCount());
}


// ---------------------------------------------------------------------------
//  RecalcPositionsInRange											[private]
// ---------------------------------------------------------------------------
// All indices between inStart and inEnd (inclusive)

void
CSTRx_EditorWindow::RecalcPositionsInRange(UInt16 inStart, UInt16 inEnd)
{
	if (inStart > inEnd) {
		UInt16 pos = inEnd;
		inEnd = inStart;
		inStart = pos;
	} 
	for (UInt16 i = inStart; i <= inEnd; i++) {
		RecalcPositionAtIndex(i);
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
//  DeleteSelectedItems												  [public]
// ---------------------------------------------------------------------------

UInt16
CSTRx_EditorWindow::DeleteSelectedItems()
{
	UInt16 count = 0, index;
	CIndexedEditField * theField;
	
	for (index = mIndexedFields.GetCount(); index > 0 ; index--) {
		if ( mIndexedFields.FetchItemAt(index, theField) && theField->IsSelected() ) {
			// Just hide the pane. Destructor will take care of deleting 
			// the object when the window is closed.
			theField->Hide();
			mIndexedFields.RemoveItemsAt(1, index);
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
	long	theLong;
	
	try {
		if (mOutStream != nil) {delete mOutStream;} 

		mOutStream = new LHandleStream();	
		ThrowIfNil_(mOutStream);

		*mOutStream << numStrings;

		TArrayIterator<CIndexedEditField*> iterator(mIndexedFields);
		CIndexedEditField *	theField;

		while (iterator.Next(theField)) {
			theField->GetDescriptor(theString);

			switch (mOwnerDoc->GetSubstType()) {
				case 'STR#':
				*mOutStream << theString;
				break;
				
				case 'MBAR':
				::StringToNum( theString, &theLong);
				*mOutStream << (SInt16) theLong;
				break;
				
				case 'Mcmd':
				case 'RidL':
				::StringToNum( theString, &theLong);
				*mOutStream << theLong;
				break;
				
			}
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



#pragma mark -


// // Drag and Drop code
// // ==================

// ---------------------------------------------------------------------------------
//  ItemIsAcceptable
// ---------------------------------------------------------------------------------

Boolean
CSTRx_EditorWindow::ItemIsAcceptable(
	DragReference	inDragRef,
	ItemReference	inItemRef )
{
	// Make sure there's text in the drag data
	FlavorFlags	theFlags;
	Boolean acceptable = (::GetFlavorFlags( inDragRef, inItemRef, 'TEXT', &theFlags ) == noErr);
	return acceptable;
}


// ---------------------------------------------------------------------------------
//  ReceiveDragItem
// ---------------------------------------------------------------------------------		

void
CSTRx_EditorWindow::ReceiveDragItem(
	DragReference	inDragRef,
	DragAttributes	inDragAttrs,
	ItemReference	inItemRef,
	Rect			&inItemBounds )
{
#pragma unused( inDragAttrs, inItemBounds )
	
	FlavorFlags	theFlags;
	ThrowIfOSErr_( ::GetFlavorFlags( inDragRef, inItemRef, 'TEXT', &theFlags ) );
	
	// Get the data
	Size	theDataSize = 255;
	Str255	theString;
	ThrowIfOSErr_( ::GetFlavorData( inDragRef, inItemRef,'TEXT', &theString[1], &theDataSize, 0 ) );
	
	// Get the data size and set the string length
	ThrowIfOSErr_( ::GetFlavorDataSize( inDragRef, inItemRef, 'TEXT', &theDataSize ) );
	theString[0] = theDataSize;
	
	if ( UDragAndDropUtils::CheckIfViewIsAlsoSender(inDragRef) ) {
		CIndexedEditField *	theField;
		UInt16	oldRow, oldIndex, newIndex;

		if (!UDragAndDropUtils::CheckForOptionKey(inDragRef) ) {
			// No option key, it is a move operation

			// Get the original index
			Point	thePoint;
			::GetDragOrigin(inDragRef, &thePoint);
			GlobalToPortPoint(thePoint);
			GetIndexFromPoint(thePoint, oldIndex, oldRow);
			
			// If item k is dropped on dropIndex k-1 (just above itself) or 
			// k (just below itself) it means that it remains in its 
			// original position.
			if ( mDropIndex != oldIndex-1 && mDropIndex != oldIndex ) {
				// Operate on the fields array
				if ( mIndexedFields.FetchItemAt(oldIndex, theField) ) {
					// Delete the old data
					mIndexedFields.RemoveItemsAt(1, oldIndex);
					// Add the new data
					if ( mDropIndex == -1 ) {
						mIndexedFields.AddItem(theField);
					} else {
						newIndex = mDropIndex;
						if ( newIndex < oldRow ) {
							// Adjust for deleted row
							newIndex += 1;
						}
						mIndexedFields.InsertItemsAt(1, newIndex, theField);
					}
				} 
				RecalcPositionsInRange(oldIndex, newIndex);
			}
		} else {
			// It is a copy operation
			if ( mDropIndex == -1 ) {
				newIndex = 0;
			} else {
				newIndex = mDropIndex + 1;
			}
			CreateItemAtIndex(newIndex, theString, 1);
			RecalcPositionsInRange(newIndex + 1, mIndexedFields.GetCount());
		}
	} else {
		// The drag comes from outside
		CreateItemAtIndex(mDropIndex + 1, theString, 1);		
		RecalcPositionsInRange(mDropIndex + 1, mIndexedFields.GetCount());
	}

	Refresh();
	SetDirty(true);
}


// ---------------------------------------------------------------------------------
//  EnterDropArea
// ---------------------------------------------------------------------------------

void
CSTRx_EditorWindow::EnterDropArea(
	DragReference	inDragRef,
	Boolean			inDragHasLeftSender )
{
	// Call inherited
	LDragAndDrop::EnterDropArea( inDragRef, inDragHasLeftSender );
	// Invalidate the last drop index
	mDropIndex = -1;
}


// ---------------------------------------------------------------------------------
//  LeaveDropArea
// ---------------------------------------------------------------------------------

void
CSTRx_EditorWindow::LeaveDropArea(
	DragReference	inDragRef )
{
	// Undo dividing line drawing
	DrawDividingLine( mDropIndex );
	// Invalidate the last drop index
	mDropIndex = -1;
	// Call inherited
	LDragAndDrop::LeaveDropArea( inDragRef );
}


// ---------------------------------------------------------------------------------
//  InsideDropArea
// ---------------------------------------------------------------------------------
// If there are n items, mDropIndex has its value between 0 and n. If
// mDropIndex equals k, it means that the dropped item will be between the
// items currently at positions k and k+1.

void
CSTRx_EditorWindow::InsideDropArea(
	DragReference	inDragRef )
{
	// Call inherited
	LDragAndDrop::InsideDropArea( inDragRef );

	if ( FocusDraw() ) {

		// Get the mouse location and convert to port coordinates
		Point	thePoint;
		::GetDragMouse( inDragRef, &thePoint, nil );
		GlobalToPortPoint( thePoint );

		// Get the dividing line point
		UInt16	theItemIndex, theDropIndex;
		GetIndexFromPoint( thePoint, theItemIndex, theDropIndex );
		
		if ( mDropIndex != theDropIndex ) {
			if ( mDropIndex >= 0 ) {
				// Undo the previous line (drawing uses patXor mode)
				DrawDividingLine( mDropIndex );
			}
			
			// Update the drop index and draw the new dividing line
			mDropIndex = theDropIndex;
			DrawDividingLine( mDropIndex );
		}
	}
}


// ---------------------------------------------------------------------------------
//  HiliteDropArea
// ---------------------------------------------------------------------------------

void
CSTRx_EditorWindow::HiliteDropArea(
	DragReference	inDragRef )
{
	// Get the frame rect
	Rect	theRect;
	CalcLocalFrameRect( theRect );

	// Show the drag hilite in the drop area
	RgnHandle	theRgnH = ::NewRgn();
	::RectRgn( theRgnH, &theRect );
	::ShowDragHilite( inDragRef, theRgnH, true );
	::DisposeRgn( theRgnH );
}


// ---------------------------------------------------------------------------------
//  GetIndexFromPoint
// ---------------------------------------------------------------------------------
// One must distinguish the index of the item in the list and the drop 
// index. On output, outItemIndex gives the real index of the item in the 
// list (between 1 and n) and outDropRow gives the drop index (between 0 
// and n). The drop index tells where to draw the dividing line and where 
// to insert the item. 

void
CSTRx_EditorWindow::GetIndexFromPoint(
	  const Point	&inPortPoint,
	  UInt16		&outItemIndex,
	  UInt16		&outDropRow )
{
	// Convert to local coordinates
	Point	theLocalPoint = inPortPoint;
	mContentsView->PortToLocalPoint( theLocalPoint );
	
	// Convert to image coordinates
	SPoint32	theImagePoint;
	mContentsView->LocalToImagePoint( theLocalPoint, theImagePoint );
	
	// Calculate the item index given the image point
	outItemIndex = (theImagePoint.v - 1) / kStrxHeight + 1;
	outDropRow = outItemIndex;
	
	// Calculate the item's midpoint
	SInt32	theMidPoint = (outItemIndex - 1) * kStrxHeight + kStrxHeight / 2;

	if ( theImagePoint.v < theMidPoint ) {
		// The point is less than the midpoint, so use the previous index
		outDropRow -= 1;
	}
	
	// Constrain to the range of items (0 means "insert at the beginning")
	if ( outDropRow < 0 ) {
		outDropRow = 0;
	} else if ( outDropRow > mIndexedFields.GetCount() ) {
		outDropRow = mIndexedFields.GetCount();
	}
}


// ---------------------------------------------------------------------------------
//  DrawDividingLine
// ---------------------------------------------------------------------------------

void
CSTRx_EditorWindow::DrawDividingLine( UInt16 inRow )
{
	if (inRow == -1) {return;} 
	
	// Focus the pane and get the table and cell frames
	Rect	theFrame;
	
	if ( FocusDraw() && mContentsView->CalcPortFrameRect(theFrame) ) {
		// Save the draw state
		StColorPenState	theDrawState;

		// Save the clip region state and clip the list view rect
		StClipRgnState	theClipState( theFrame );

		// Setup the color and pen state
		::ForeColor( blackColor );
		::PenMode( patXor );
		::PenSize( 2, 2 );

		// Calculate the dividing line position + theFrame.top
		SPoint32	theImagePoint;
		Point		thePoint;
		theImagePoint.v = inRow * kStrxHeight;
		theImagePoint.h = theFrame.left + kStrxIndexWidth;

		mContentsView->ImageToLocalPoint(theImagePoint, thePoint);
		mContentsView->LocalToPortPoint(thePoint);
		
		// Draw the line
		::MoveTo( thePoint.h, thePoint.v );
		::LineTo( thePoint.h + theFrame.right - theFrame.left - kStrxIndexWidth, thePoint.v );
	}
}

