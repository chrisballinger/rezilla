// ===========================================================================
// CDragTable.cp
// 
//                       Created: 2005-03-09 17:16:53
//             Last modification: 2006-09-21 18:05:50
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2005-2006
// All rights reserved.
// ===========================================================================

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CMENU_EditorDoc.h"
#include "CDragTable.h"
#include "CMENU_EditorWindow.h"
#include "CMenuObject.h"
#include "CRezillaPrefs.h"
#include "RezillaConstants.h"
#include "UDragAndDropUtils.h"

#include <UTextTraits.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------------
//  CreateDnDTableStream [static]
// ---------------------------------------------------------------------------------

CDragTable *
CDragTable::CreateDnDTableStream(
	LStream	*inStream )
{
	return new CDragTable( inStream );
}


// ---------------------------------------------------------------------------------
//  CDragTable(LStream*)
// ---------------------------------------------------------------------------------

CDragTable::CDragTable(
	LStream 	*inStream )
		: LTable( inStream ),
		LDragAndDrop( UQDGlobals::GetCurrentWindowPort(), this )
{
	// Initialize the drop row to a bad value.
	mDropRow = -1;
	inStream->ReadData(&mTxtrID, sizeof(mTxtrID));
}


// ---------------------------------------------------------------------------
//  ~CDragTable						Destructor				  [public]
// ---------------------------------------------------------------------------

CDragTable::~CDragTable()
{
}



#pragma mark -

// ---------------------------------------------------------------------------
//  HandleKeyPress											[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CDragTable::HandleKeyPress(
	const EventRecord	&inKeyEvent)
{
	Boolean		keyHandled	= true;
	LControl*	keyButton	= nil;
	UInt8		theChar		= (UInt8) (inKeyEvent.message & charCodeMask);
	
	if (inKeyEvent.modifiers & cmdKey) {
		keyHandled = LCommander::HandleKeyPress(inKeyEvent);
	} else if (mRows > 0) {
		TableCellT	theCell;
		SInt32		theValue;
		
		GetSelectedCell( theCell );
		theValue = theCell.row;
		
		switch (theChar) {
			case char_UpArrow:
			--theValue;
			if (theValue == 0) {theValue = mRows;} 
			break;
			
			case char_DownArrow:
			++theValue;
			if (theValue > mRows) {theValue = 1;} 
			break;
			
			case char_PageUp:
			--theValue;
			if (theValue == 0) {return keyHandled;} 
			break;
			
			case char_PageDown:
			++theValue;
			if (theValue > mRows) {return keyHandled;} 
			break;
			
			case char_Home:
			theValue = 1;
			break;
			
			case char_End:
			theValue = mRows;
			break;
		}
		
		theCell.row = theValue;
		SelectCell(theCell);
		BroadcastMessage(msg_MenuTableClicked,this);
	}
	
	return keyHandled;
}

// ---------------------------------------------------------------------------------
//   Click
// ---------------------------------------------------------------------------------

void
CDragTable::Click(
	SMouseDownEvent	&inMouseDown )
{
	// In order to support dragging from an inactive window, we must
	// explicitly test for delaySelect and the presence of Drag and Drop.
	if ( inMouseDown.delaySelect ) {

		// Convert to a local point.
		PortToLocalPoint( inMouseDown.whereLocal );
		
		// Execute click attachments.
		if ( ExecuteAttachments( msg_Click, &inMouseDown ) ) {
			// Handle the actual click event.
			ClickSelf( inMouseDown );
		}
	
	} else {
		// Call inherited for default behavior.	
		LTable::Click( inMouseDown );
		SwitchTarget(this);
	}
}


// ---------------------------------------------------------------------------------
//   ClickCell
// ---------------------------------------------------------------------------------

void
CDragTable::ClickCell(
	const TableCellT		&inCell,
	const SMouseDownEvent	&inMouseDown )
{
	// Call inherited
	LTable::ClickCell( inCell, inMouseDown );

	if ( ::WaitMouseMoved( inMouseDown.macEvent.where ) ) {

		// Get the selected cell
		TableCellT	theCell;
		GetSelectedCell( theCell );
		
		if ( IsValidCell( theCell ) ) {
		
			FocusDraw();
			
			// Get the cell frame
			Rect	theCellFrame;
			FetchLocalCellFrame( theCell, theCellFrame );
	
			// Get the cell data
			Str255	theString;
			GetCellData( theCell, theString );
			
			// Create the drag task
			LDragTask	theDragTask( inMouseDown.macEvent, theCellFrame,
							1, 'TEXT', &theString[1], StrLength(theString), 0 );
			
			// Invalidate LView's focus cache. The port may have changed
			// during the drag.
			LView::OutOfFocus( nil );
		
			// Check for a drop in the trash
			if ( UDragAndDropUtils::DroppedInTrash(
				theDragTask.GetDragReference() ) ) {
			
				// Delete the cell and refresh the list
				RemoveRows( 1, theCell.row );
				Refresh();

			}

		}

	} else {
		// Tell the window
		BroadcastMessage(msg_MenuTableClicked,this);
	}
}


// ---------------------------------------------------------------------------------
//   DrawCell
// ---------------------------------------------------------------------------------

void
CDragTable::DrawCell(
	const TableCellT	&inCell)
{
	// Get the cell frame.
	Rect	theCellFrame;
	if ( FetchLocalCellFrame( inCell, theCellFrame ) ) {
	
		// Get the cell data.
		Str255	theString;
		GetCellData( inCell, theString );
	
		// Setup for drawing.
// 		::TextFont( systemFont );
// 		::TextSize( 12 );
// 		::TextFace(mOwnerWindow->GetMenuObj()->GetStyleAtIndex(inCell.row));
		UTextTraits::SetPortTextTraits(mTxtrID);
		
		// Draw the string.
		MoveTo( theCellFrame.left + 4, theCellFrame.bottom - 3 );
		DrawString( theString );
	
	}
}


// ---------------------------------------------------------------------------------
//   UnhiliteCell
// ---------------------------------------------------------------------------------

void
CDragTable::UnhiliteCell(
	const TableCellT	&inCell )
{
	if ( IsActive() ) {
	
		// Call inherited
		LTable::UnhiliteCell( inCell );
	
	} else {

		// Validate the cell and get the cell frame.
		Rect	theCellFrame;
		if ( IsValidCell( inCell ) &&
			FetchLocalCellFrame( inCell, theCellFrame ) ) {

			// Undo the background selection hiliting.
			UDrawingUtils::SetHiliteModeOn();
			StColorPenState::Normalize();
			::PenMode( srcXor );
			::FrameRect( &theCellFrame );

		}
	}
}


// ---------------------------------------------------------------------------------
//   ActivateSelf
// ---------------------------------------------------------------------------------

void
CDragTable::ActivateSelf()
{
	// Our selection hiliting works a little bit differently,
	// so we'll invalidate the selected cell instead of
	// redrawing the hiliting immediately.
	RefreshCell( mSelectedCell );
}


// ---------------------------------------------------------------------------------
//   DeactivateSelf
// ---------------------------------------------------------------------------------

void
CDragTable::DeactivateSelf()
{
	// Our selection hiliting works a little bit differently,
	// so we'll invalidate the selected cell instead of
	// redrawing the hiliting immediately.
	RefreshCell( mSelectedCell );
}


// ---------------------------------------------------------------------------------
//   RefreshCell
// ---------------------------------------------------------------------------------

void
CDragTable::RefreshCell(
	const TableCellT	&inCell )
{
	Rect	theCellFrame;
	if ( FocusDraw() && IsValidCell( inCell ) &&
		FetchLocalCellFrame( inCell, theCellFrame ) ) {
		
		// Convert to port coordinates.
		LocalToPortPoint( topLeft(theCellFrame) );
		LocalToPortPoint( botRight(theCellFrame) );
		
		// Invalidate the cell.
		InvalPortRect( &theCellFrame );
	
	}	
}


// ---------------------------------------------------------------------------------
//   ItemIsAcceptable
// ---------------------------------------------------------------------------------

Boolean
CDragTable::ItemIsAcceptable(
	DragReference	inDragRef,
	ItemReference	inItemRef )
{
	// Make sure the table is enabled and
	// there's text in the drag data.
	FlavorFlags	theFlags;
	return IsEnabled() && (::GetFlavorFlags( inDragRef,
		inItemRef, 'TEXT', &theFlags ) == noErr);
}


// ---------------------------------------------------------------------------------
//   ReceiveDragItem
// ---------------------------------------------------------------------------------

void
CDragTable::ReceiveDragItem(
	DragReference	inDragRef,
	DragAttributes	inDragAttrs,
	ItemReference	inItemRef,
	Rect			&inItemBounds )
{
#pragma unused( inDragAttrs, inItemBounds )

	FlavorFlags	theFlags;
	ThrowIfOSErr_( ::GetFlavorFlags( inDragRef, 
		inItemRef, 'TEXT', &theFlags ) );

	// Get the data.
	Size	theDataSize = 255;
	Str255	theString;
	ThrowIfOSErr_( ::GetFlavorData( inDragRef, inItemRef,
		'TEXT', &theString[1], &theDataSize, 0 ) );
	
	// Get the data size and set the string length.
	ThrowIfOSErr_( ::GetFlavorDataSize( inDragRef,
		inItemRef, 'TEXT', &theDataSize ) );
	theString[0] = theDataSize;

	// if it's a move operation (in sender and no option key)
	if ( UDragAndDropUtils::CheckIfViewIsAlsoSender( inDragRef ) &&
		!UDragAndDropUtils::CheckForOptionKey( inDragRef ) ) {
	
		// Get the selected cell.
		TableCellT	theSelectedCell;
		GetSelectedCell( theSelectedCell );
		
		if ( mDropRow != theSelectedCell.row ) {
		
			// Delete the old data.
			if ( IsValidCell( theSelectedCell ) ) {

				// Delete the original cell.
				RemoveRows( 1, theSelectedCell.row );
			
			}

			// Add the new data.
			TableIndexT	theRow;
			if ( mDropRow == -1 ) {
				theRow = LArray::index_Last;
			} else {
				theRow = mDropRow;
				if ( theRow > theSelectedCell.row ) {
					// Adjust for deleted row.
					theRow -= 1;
				}
			}
			InsertRows( 1, theRow, theString );
			
			// Select the new cell, but without calling
			// SelectCell to avoid immediate drawing.
			mSelectedCell.row = theRow + 1;
		
			// Tell the window
			BroadcastMessage(msg_DragMoveAction, &mDropRow);
		}

	} else { // it's a copy operation

		// Add the new data.
		TableIndexT	theRow;
		if ( mDropRow == -1 ) {
			theRow = LArray::index_Last;
		} else {
			theRow = mDropRow;
		}
		InsertRows( 1, theRow, theString );

		// Select the new cell, but without calling
		// SelectCell to avoid immediate drawing.
		mSelectedCell.row = theRow + 1;

		// Tell the window
		BroadcastMessage(msg_DragCopyAction, &mDropRow);

	}
	
	// Invalidate the table.
	Refresh();
}


// ---------------------------------------------------------------------------------
//   EnterDropArea
// ---------------------------------------------------------------------------------

void
CDragTable::EnterDropArea(
	DragReference	inDragRef,
	Boolean			inDragHasLeftSender )
{
	// Call inherited
	LDragAndDrop::EnterDropArea( inDragRef, inDragHasLeftSender );

	// Invalidate the last drop cell.
	mDropRow = -1;
}


// ---------------------------------------------------------------------------------
//   LeaveDropArea
// ---------------------------------------------------------------------------------

void
CDragTable::LeaveDropArea(
	DragReference	inDragRef )
{
	// Undo dividing line drawing.
	DrawDividingLine( mDropRow );

	// Invalidate the last drop cell.
	mDropRow = -1;

	// Call inherited
	LDragAndDrop::LeaveDropArea( inDragRef );
}


// ---------------------------------------------------------------------------------
//   InsideDropArea
// ---------------------------------------------------------------------------------

void
CDragTable::InsideDropArea(
	DragReference	inDragRef )
{
	// Call inherited
	LDragAndDrop::InsideDropArea( inDragRef );

	// Focus.
	if ( FocusDraw() ) {

		// Get the mouse location and
		// convert to port coordinates.
		Point	thePoint;
		::GetDragMouse( inDragRef, &thePoint, nil );
		GlobalToPortPoint( thePoint );

		// Get the dividing line point.
		TableIndexT	theRow;
		GetDividingLineGivenPoint( thePoint, theRow );
		
		if ( mDropRow != theRow ) {
		
			if ( mDropRow >= 0 ) {
			
				// Undo the previous dividing line.
				DrawDividingLine( mDropRow );
			
			}
			
			// Update the drop cell and
			// draw the new dividing line.
			mDropRow = theRow;
			DrawDividingLine( mDropRow );
		
		}

	}
}


// ---------------------------------------------------------------------------------
//   HiliteDropArea
// ---------------------------------------------------------------------------------

void
CDragTable::HiliteDropArea(
	DragReference	inDragRef )
{
	// Get the frame rect.
	Rect	theRect;
	CalcLocalFrameRect( theRect );

	// Show the drag hilite in the drop area.
	RgnHandle	theRgnH = ::NewRgn();
	::RectRgn( theRgnH, &theRect );
	::ShowDragHilite( inDragRef, theRgnH, true );
	::DisposeRgn( theRgnH );
}


// ---------------------------------------------------------------------------------
//   GetDividingLineGivenPoint
// ---------------------------------------------------------------------------------

void
CDragTable::GetDividingLineGivenPoint(
	const Point		&inPortPoint,
	TableIndexT		&outRow )
{
	Boolean	isValid = false;

	// Convert to local coordinates.
	Point	theLocalPoint = inPortPoint;
	PortToLocalPoint( theLocalPoint );
	
	// Convert to image coordinates.
	SPoint32	theImagePoint;
	LocalToImagePoint( theLocalPoint, theImagePoint );
	
	// Calculate the cell index given the image point.
	outRow = (theImagePoint.v - 1) / mRowHeight + 1;
	
	// Calculate the cell midpoint.
	SInt32	theMidPoint = (outRow - 1) * mRowHeight + mRowHeight / 2;

	if ( theImagePoint.v < theMidPoint ) {
	
		// The point is less than the midpoint,
		// so use the previous cell index.
		outRow -= 1;
	
	}
	
	// Constrain it to the range of cells.
	// Note: zero is used to mean "insert at the beginning".
	if ( outRow < 0 ) {
		outRow = 0;
	} else if ( outRow > mRows ) {
		outRow = mRows;
	}
}


// ---------------------------------------------------------------------------------
//   DrawDividingLine
// ---------------------------------------------------------------------------------

void
CDragTable::DrawDividingLine(
	TableIndexT	inRow )
{
	// Setup the target cell.
	TableCellT	theCell;
	theCell.row = inRow;
	theCell.col = 1;

	// Focus the pane and get the table and cell frames.
	Rect	theFrame;
	if ( FocusDraw() && CalcLocalFrameRect( theFrame ) ) {

		// Save the draw state.
		StColorPenState	theDrawState;

		// Save the clip region state and clip the list view rect.
		StClipRgnState	theClipState( theFrame );

		// Setup the color and pen state.
		::ForeColor( blackColor );
		::PenMode( patXor );
		::PenSize( 2, 2 );

		// Calculate the dividing line position.		
		Point	thePoint;
		thePoint.v = inRow * mRowHeight;
		thePoint.h = 0;

		// Draw the line.
		::MoveTo( thePoint.h, thePoint.v-1 );
		::LineTo( thePoint.h + mColWidth, thePoint.v-1 );
	
	}
}


// ---------------------------------------------------------------------------------
//   DrawSeparator
// ---------------------------------------------------------------------------------

void
CDragTable::DrawSeparator(
	TableIndexT	inRow )
{
	// Setup the cell.
	TableCellT	theCell;
	theCell.row = inRow;
	theCell.col = 1;

	// Focus the pane and get the table and cell frames.
	Rect	theFrame;
	if ( FocusDraw() && CalcLocalFrameRect( theFrame ) ) {

		// Save the draw state.
		StColorPenState	theDrawState;

		// Save the clip region state and clip the list view rect.
		StClipRgnState	theClipState( theFrame );

		// Setup the color and pen state.
		::ForeColor( blackColor );
		::PenMode( patXor );
		::PenSize( 1, 1 );

		// Calculate the dividing line position.		 + mRowHeight/2 
		Point	thePoint;
		thePoint.v = inRow * mRowHeight;
		thePoint.h = 0;

		// Draw the line.
		::MoveTo( thePoint.h, thePoint.v-1 );
		::LineTo( thePoint.h + mColWidth, thePoint.v-1 );
	
	}
}


// ---------------------------------------------------------------------------
//	 RemoveSelectedRow
// ---------------------------------------------------------------------------
// Removes one row from the table and takes care of hiliting another one.

void
CDragTable::RemoveSelectedRow()
{
	TableCellT theCell;
	TableIndexT	theRow;

	GetSelectedCell(theCell);
	theRow = theCell.row;
	RemoveRows(1, theRow);
	if (theRow > mRows) {
		// We removed the last row
		theRow = mRows;
	} 
	
	mSelectedCell.row = theRow;
}




PP_End_Namespace_PowerPlant
