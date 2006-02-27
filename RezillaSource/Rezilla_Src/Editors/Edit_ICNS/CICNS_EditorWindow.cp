// ===========================================================================
// CICNS_EditorWindow.cp					
// 
//                       Created: 2006-02-23 15:12:16
//             Last modification: 2006-02-27 07:28:32
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================

#include "CICNS_EditorDoc.h"
#include "CICNS_EditorWindow.h"
#include "CICNS_Family.h"
#include "CICNS_Member.h"
#include "CICNS_Stream.h"
#include "CRezObj.h"
#include "RezillaConstants.h"
#include "UMessageDialogs.h"
#include "UDragAndDropUtils.h"
#include "UMiscUtils.h"

#include <LPopupButton.h>
#include <LStaticText.h>

#include <stdio.h>

// SPaneInfo CICNS_EditorWindow::sPaneInfo;
// SViewInfo CICNS_EditorWindow::sViewInfo;


// 	// View info
// 	sViewInfo.imageSize.width	= sViewInfo.imageSize.height	= 0 ;
// 	sViewInfo.scrollPos.h		= sViewInfo.scrollPos.v			= 0;
// 	sViewInfo.scrollUnit.h		= sViewInfo.scrollUnit.v		= kStrxHeight;
// 	sViewInfo.reconcileOverhang	= false;
// 	
// 	// Pane info
// 	sPaneInfo.left				= 0;
// 	sPaneInfo.height			= kStrxHeight;
// 	sPaneInfo.visible			= true;
// 	sPaneInfo.enabled			= true;
// 	sPaneInfo.bindings.left		= true;
// 	sPaneInfo.bindings.top		= false;
// 	sPaneInfo.bindings.right	= true;
// 	sPaneInfo.bindings.bottom 	= false;
// 	sPaneInfo.userCon			= 0;
// 	sPaneInfo.paneID			= 0;
// 	sPaneInfo.superView			= mContentsView;


// ---------------------------------------------------------------------------
//  CICNS_EditorWindow				[public]
// ---------------------------------------------------------------------------

CICNS_EditorWindow::CICNS_EditorWindow()
		: LDragAndDrop( UQDGlobals::GetCurrentWindowPort(), this )
{
	// Initialize the drop index to a bad value
	mDropIndex = -1;
	mCurrentIndex = 0;
}


// ---------------------------------------------------------------------------
//  CICNS_EditorWindow				[public]
// ---------------------------------------------------------------------------

CICNS_EditorWindow::CICNS_EditorWindow(
			       LStream *inStream )
		: CEditorWindow( inStream ),
		LDragAndDrop( UQDGlobals::GetCurrentWindowPort(), this )
{
	mDropIndex = -1;
	mCurrentIndex = 0;
}


// ---------------------------------------------------------------------------
//  ~CICNS_EditorWindow				[public]
// ---------------------------------------------------------------------------

CICNS_EditorWindow::~CICNS_EditorWindow()
{	
	if (mOutStream != nil) {
		delete mOutStream;
	} 
}


// ---------------------------------------------------------------------------
// FinishCreateSelf												[protected]
// ---------------------------------------------------------------------------

void
CICNS_EditorWindow::FinishCreateSelf()
{	
	mOutStream = nil;
	
	// The main view containing the editing fields
	mContentsView = dynamic_cast<LView *>(this->FindPaneByID(item_EditorContents));
	ThrowIfNil_( mContentsView );

	mTypeField = dynamic_cast<LStaticText *>(this->FindPaneByID(item_IcnsTypeField));
	ThrowIfNil_( mTypeField );

	mSizeField = dynamic_cast<LStaticText *>(this->FindPaneByID(item_IcnsSizeField));
	ThrowIfNil_( mSizeField );

	mIconPopup = dynamic_cast<LPopupButton *>(this->FindPaneByID(item_IcnsIconPopup));
	ThrowIfNil_( mIconPopup );

	// Fill the menu
	FillPopup();

	// Link the broadcasters
	UReanimator::LinkListenerToControls( this, this, PPob_IcnsEditorWindow );
}


// ---------------------------------------------------------------------------------
//  Click
// ---------------------------------------------------------------------------------

void
CICNS_EditorWindow::Click(
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
CICNS_EditorWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{		
	switch (inMessage) {
						
		case msg_IcnsIconPopup: 
		if ( SelectIconAtIndex(mIconPopup->GetValue()) ) {
			SetDirty(true);
			Refresh();
		} 
		break;
		
		
		case cmd_Clear:
		DeleteIconAtIndex(mCurrentIndex);
		break;
		
		
		case msg_EditorModifiedItem:
		SetDirty(true);
		break;
		
		
		default:
		dynamic_cast<CICNS_EditorDoc *>(mOwnerDoc)->ListenToMessage(inMessage, ioParam);
		break;
				
	}
}


// ---------------------------------------------------------------------------
//	 FillPopup														[public]
// ---------------------------------------------------------------------------

void
CICNS_EditorWindow::FillPopup() 
{
	SInt16	count;
	StResource	stringListH(FOUR_CHAR_CODE('STR#'), STRx_IcnsMembers, false, false);
	
	// Empty the menu
	mIconPopup->DeleteAllMenuItems();
	
	// First item is blank
	mIconPopup->AppendMenu("\p ");
	mIconTypes.AddItem( (OSType) 0);

	if ((stringListH.mResourceH != nil)) {
		count = * (SInt16*) *stringListH.mResourceH;

		if ( count > 0 ) {
			Str255		itemStr;
			
			for ( SInt16 i = 1; i <= count; i++ ) {
				// Get the string from the list resource
				::GetIndString( itemStr, STRx_IcnsMembers, i );
				// Append it to the menu
				AppendTypeToMenu(itemStr);
			}
		}
	}	

	mIconPopup->SetMinValue(0);
	mIconPopup->SetMaxValue(count+1);
	Refresh();
}


// ---------------------------------------------------------------------------
//	 AppendTypeToMenu
// ---------------------------------------------------------------------------

void
CICNS_EditorWindow::AppendTypeToMenu(Str255 inString)
{
	Str255 *	rightPtr;
	OSType		theType;
	
	// Ignore empty items
	if ( inString[0] ) {
		if ( UMiscUtils::SplitCaseValue(inString, &rightPtr) ) {
			UMiscUtils::PStringToOSType(*rightPtr, theType);
			if ( ::EqualString(inString, "\p-", true, false) ) {
				// This is a separator line
				theType = 0;
			}  
			mIconTypes.AddItem(theType);
			mIconPopup->AppendMenu(inString);
		}
	}
}


// ---------------------------------------------------------------------------
//	 UpdatePopupStyle													  [public]
// ---------------------------------------------------------------------------

void
CICNS_EditorWindow::UpdatePopupStyle() 
{
	MenuRef			theMenuH = mIconPopup->GetMacMenuH();
	SInt32			index;
	OSType			theType;
	CICNS_Member *	theMember;
	
	UInt16 theCount = ::CountMenuItems( theMenuH );
	
	for (index = 1; index <= theCount; index++) {	
		if ( mIconTypes.FetchItemAt(index, theType) && theType != 0) {
			theMember = mIcnsFamily->FindIconForType(theType);
			if (theMember == nil) {
				::SetItemStyle(theMenuH, index, italic);
			} else {
				// Set the current index to the first existing member
				if (mCurrentIndex == 0) {
					mCurrentIndex = index;
				} 
				::SetItemStyle(theMenuH, index, normal);
				::MacCheckMenuItem(theMenuH, index, (index == mCurrentIndex));
			}
		}
	}
}


// ---------------------------------------------------------------------------
//  SelectIconAtIndex												[private]
// ---------------------------------------------------------------------------

Boolean
CICNS_EditorWindow::SelectIconAtIndex(ArrayIndexT inMenuIndex)
{
	OSType			theType;
	Str255			theString;
	CICNS_Member *	theMember = nil;
	MenuRef			theMenuH = mIconPopup->GetMacMenuH();
	
	if ( mIconTypes.FetchItemAt(inMenuIndex, theType) ) {
		theMember = mIcnsFamily->FindIconForType(theType);
		if (theMember == nil) {
			theMember = CreateIcon(inMenuIndex, theType);
		} 
	}
	
	if (theMember != nil) {
		InstallIcon(inMenuIndex, theMember);
		return true;
	} else {
		return false;
	}
}


// ---------------------------------------------------------------------------
//  InstallIcon														[private]
// ---------------------------------------------------------------------------

void
CICNS_EditorWindow::InstallIcon(ArrayIndexT inMenuIndex, CICNS_Member * inMember)
{
	MenuRef			theMenuH = mIconPopup->GetMacMenuH();
	::MacCheckMenuItem(theMenuH, mCurrentIndex, 0);
	SetCurrentIndex(inMenuIndex);
	::MacCheckMenuItem(theMenuH, inMenuIndex, 1);
	UpdateInfoFields(inMember->GetType(), inMember->GetIconSize());
	
}


// ---------------------------------------------------------------------------
//  CreateIcon														[private]
// ---------------------------------------------------------------------------

CICNS_Member *
CICNS_EditorWindow::CreateIcon(ArrayIndexT inMenuIndex, OSType inType)
{
	Str255 			theString;
	CICNS_Member *	theMember = nil;
	MenuRef			theMenuH = mIconPopup->GetMacMenuH();
	
	// Ask to create a new member
	GetMenuItemText(theMenuH, inMenuIndex, theString);
	if ( UMessageDialogs::AskIfWithString(CFSTR("ConfirmCreateIcnsMember"), theString) == true) {
		theMember = new CICNS_Member(inType);
		if (theMember) {
			mIcnsFamily->AddMember(theMember);
			::SetItemStyle(theMenuH, inMenuIndex, normal);
		} else {
			UMessageDialogs::AskIfWithString(CFSTR("CreatingIcnsMemberFailed"), theString);
		}
	} else {
		// Reset the menu at its current index
		mIconPopup->SetValue(mCurrentIndex);
	}	
	
	return theMember;
}




// ---------------------------------------------------------------------------
//  DeleteIconAtIndex												[private]
// ---------------------------------------------------------------------------

void
CICNS_EditorWindow::DeleteIconAtIndex(ArrayIndexT index)
{
	MenuRef			theMenuH = mIconPopup->GetMacMenuH();
	
	mIcnsFamily->DeleteMember(index);
	::MacCheckMenuItem(theMenuH, mCurrentIndex, 0);
	::SetItemStyle(theMenuH, index, italic);
	SetCurrentIndex(0);
}


// ---------------------------------------------------------------------------
//  UpdateInfoFields												[private]
// ---------------------------------------------------------------------------

void
CICNS_EditorWindow::UpdateInfoFields(OSType inType, SInt32 inSize)
{
	Str255 theString;
	UMiscUtils::OSTypeToPString(inType, theString);
	mTypeField->SetDescriptor(theString);
	::NumToString(inSize, theString);
	mSizeField->SetDescriptor(theString);
}


// ---------------------------------------------------------------------------
//	 InstallResourceData											[public]
// ---------------------------------------------------------------------------

OSErr
CICNS_EditorWindow::InstallResourceData(Handle inHandle)
{
	OSErr		error = noErr, ignoreErr = noErr;
	UInt16		numItems = 0;
	StHandleLocker	locker(inHandle);
	
	CICNS_Stream * theStream = new CICNS_Stream(inHandle);
	
	if ( theStream->GetLength() == 0 ) {
		// We are creating a new resource
	} else {
		if ( theStream->GetMarker() < theStream->GetLength() ) {
			mIcnsFamily = new CICNS_Family(theStream);
		}
		
		// Check that all the data have been parsed
		if ( theStream->GetMarker() < theStream->GetLength() ) {
			error = err_MoreDataThanExpected;
		} 
	}
	
	delete theStream;
	
	if (error == noErr) {
		UpdatePopupStyle();
		
// 		mContentsView->ResizeImageTo(0, numItems * kStrxHeight, false);
// 		InstallIcon(1);
	} 
	
	if (error == noErr) {
		// Adjust the size of the image
// 		mContentsView->ResizeImageTo(0, numItems * kStrxHeight, false);
		SetDirty(false);
	} 
	
	return error;
}


// ---------------------------------------------------------------------------
//  CollectResourceData												[public]
// ---------------------------------------------------------------------------

Handle
CICNS_EditorWindow::CollectResourceData() 
{
	Handle	theHandle = NULL;
	
	try {
		if (mOutStream != nil) {delete mOutStream;} 

		mOutStream = new CICNS_Stream();	
		ThrowIfNil_(mOutStream);

		mIcnsFamily->SendDataToStream(mOutStream);
		
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
CICNS_EditorWindow::RevertContents()
{
	OSErr error = noErr;
	
	// Delete the panes
	mContentsView->DeleteAllSubPanes();
// 	// Reset the array
// 	mIndexedFields.RemoveAllItemsAfter(0);

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
CICNS_EditorWindow::ItemIsAcceptable(
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
CICNS_EditorWindow::ReceiveDragItem(
	DragReference	inDragRef,
	DragAttributes	inDragAttrs,
	ItemReference	inItemRef,
	Rect			&inItemBounds )
{
// #pragma unused( inDragAttrs, inItemBounds )
// 	
// 	FlavorFlags	theFlags;
// 	ThrowIfOSErr_( ::GetFlavorFlags( inDragRef, inItemRef, 'TEXT', &theFlags ) );
// 	
// 	// Get the data
// 	Size	theDataSize = 255;
// 	Str255	theString;
// 	ThrowIfOSErr_( ::GetFlavorData( inDragRef, inItemRef,'TEXT', &theString[1], &theDataSize, 0 ) );
// 	
// 	// Get the data size and set the string length
// 	ThrowIfOSErr_( ::GetFlavorDataSize( inDragRef, inItemRef, 'TEXT', &theDataSize ) );
// 	theString[0] = theDataSize;
// 	
// 	if ( UDragAndDropUtils::CheckIfViewIsAlsoSender(inDragRef) ) {
// 		CIndexedEditField *	theField;
// 		UInt16	oldRow, oldIndex, newIndex;
// 
// 		if (!UDragAndDropUtils::CheckForOptionKey(inDragRef) ) {
// 			// No option key, it is a move operation
// 
// 			// Get the original index
// 			Point	thePoint;
// 			::GetDragOrigin(inDragRef, &thePoint);
// 			GlobalToPortPoint(thePoint);
// 			GetIndexFromPoint(thePoint, oldIndex, oldRow);
// 			
// 			// If item k is dropped on dropIndex k-1 (just above itself) or 
// 			// k (just below itself) it means that it remains in its 
// 			// original position.
// 			if ( mDropIndex != oldIndex-1 && mDropIndex != oldIndex ) {
// 				// Operate on the fields array
// 				if ( mIndexedFields.FetchItemAt(oldIndex, theField) ) {
// 					// Delete the old data
// 					mIndexedFields.RemoveItemsAt(1, oldIndex);
// 					// Add the new data
// 					if ( mDropIndex == -1 ) {
// 						mIndexedFields.AddItem(theField);
// 					} else {
// 						newIndex = mDropIndex;
// 						if ( newIndex < oldRow ) {
// 							// Adjust for deleted row
// 							newIndex += 1;
// 						}
// 						mIndexedFields.InsertItemsAt(1, newIndex, theField);
// 					}
// 				} 
// 				RecalcPositionsInRange(oldIndex, newIndex);
// 			}
// 		} else {
// 			// It is a copy operation
// 			if ( mDropIndex == -1 ) {
// 				newIndex = 0;
// 			} else {
// 				newIndex = mDropIndex + 1;
// 			}
// 			CreateItemAtIndex(newIndex, theString, 1);
// 			RecalcPositionsInRange(newIndex + 1, mIndexedFields.GetCount());
// 		}
// 	} else {
// 		// The drag comes from outside
// 		CreateItemAtIndex(mDropIndex + 1, theString, 1);		
// 		RecalcPositionsInRange(mDropIndex + 1, mIndexedFields.GetCount());
// 	}
// 
// 	Refresh();
// 	SetDirty(true);
}


// ---------------------------------------------------------------------------------
//  EnterDropArea
// ---------------------------------------------------------------------------------

void
CICNS_EditorWindow::EnterDropArea(
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
CICNS_EditorWindow::LeaveDropArea(
	DragReference	inDragRef )
{
// 	// Undo dividing line drawing
// 	DrawDividingLine( mDropIndex );
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
CICNS_EditorWindow::InsideDropArea(
	DragReference	inDragRef )
{
	// Call inherited
	LDragAndDrop::InsideDropArea( inDragRef );

// 	if ( FocusDraw() ) {
// 
// 		// Get the mouse location and convert to port coordinates
// 		Point	thePoint;
// 		::GetDragMouse( inDragRef, &thePoint, nil );
// 		GlobalToPortPoint( thePoint );
// 
// 		// Get the dividing line point
// 		UInt16	theItemIndex, theDropIndex;
// 		GetIndexFromPoint( thePoint, theItemIndex, theDropIndex );
// 		
// 		if ( mDropIndex != theDropIndex ) {
// 			if ( mDropIndex >= 0 ) {
// 				// Undo the previous line (drawing uses patXor mode)
// 				DrawDividingLine( mDropIndex );
// 			}
// 			
// 			// Update the drop index and draw the new dividing line
// 			mDropIndex = theDropIndex;
// 			DrawDividingLine( mDropIndex );
// 		}
// 	}
}


// ---------------------------------------------------------------------------------
//  HiliteDropArea
// ---------------------------------------------------------------------------------

void
CICNS_EditorWindow::HiliteDropArea(
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


