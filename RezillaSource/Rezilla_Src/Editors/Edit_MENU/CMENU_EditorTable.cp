// ===========================================================================
// CMENU_EditorTable.cp
// 
//                       Created: 2005-03-09 17:16:53
//             Last modification: 2005-03-11 07:21:48
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CMENU_EditorDoc.h"
#include "CMENU_EditorTable.h"
#include "CMENU_EditorWindow.h"
#include "CRezObj.h"
#include "CRezillaPrefs.h"
#include "RezillaConstants.h"
#include "UDragAndDropUtils.h"


PP_Begin_Namespace_PowerPlant
// cmdKey                        = 1 << cmdKeyBit,
// shiftKey                      = 1 << shiftKeyBit,
// alphaLock                     = 1 << alphaLockBit,
// optionKey                     = 1 << optionKeyBit,
// controlKey                    = 1 << controlKeyBit,
// 
// cmdKeyBit                     = 8,    /* command key down?*/
// shiftKeyBit                   = 9,    /* shift key down?*/
// alphaLockBit                  = 10,   /* alpha lock down?*/
// optionKeyBit                  = 11,   /* option key down?*/
// controlKeyBit                 = 12,   /* control key down?*/


// ---------------------------------------------------------------------------------
//  CreateDragAndDropTableStream [static]
// ---------------------------------------------------------------------------------

CMENU_EditorTable *
CMENU_EditorTable::CreateDragAndDropTableStream(
	LStream	*inStream )
{
	return new CMENU_EditorTable( inStream );
}


// ---------------------------------------------------------------------------------
//  CMENU_EditorTable(LStream*)
// ---------------------------------------------------------------------------------

CMENU_EditorTable::CMENU_EditorTable(
	LStream 	*inStream )
		: LTable( inStream ),
		LDragAndDrop( UQDGlobals::GetCurrentWindowPort(), this )
{
	// Initialize the drop row to a bad value.
	mDropRow = -1;
}


// ---------------------------------------------------------------------------
//  ~CMENU_EditorTable						Destructor				  [public]
// ---------------------------------------------------------------------------

CMENU_EditorTable::~CMENU_EditorTable()
{
}



#pragma mark -

// // ---------------------------------------------------------------------------
// //  HandleKeyPress							[public, virtual]
// // ---------------------------------------------------------------------------
// 
// Boolean
// CMENU_EditorTable::HandleKeyPress(
// 	const EventRecord	&inKeyEvent)
// {
// 	Boolean		keyHandled	 = LTextEditView::HandleKeyPress(inKeyEvent);
// 	
// 	return keyHandled;
// }


// ---------------------------------------------------------------------------
// 	FindCommandStatus
// ---------------------------------------------------------------------------

void
CMENU_EditorTable::FindCommandStatus(
	CommandT	inCommand,
	Boolean		&outEnabled,
	Boolean		&outUsesMark,
	UInt16		&outMark,
	Str255		outName)
{
	Boolean		enableIt = false;
	Boolean		handled = false;
// 	ResIDT		theMenuID;
// 	SInt16		theMenuItem;
	Boolean		foundFontItem = false;
	
	try
	{
		
		// Deal with the Style menu 
		if ( (inCommand >= cmd_Plain) && (inCommand <= cmd_Extend) )
		{
			Style theStyle = 0;
// 			GetStyle(theStyle);
			
			// This won't put a checkMark next to "Other size" if a
			// non-standard size is selected.
			if ( inCommand == cmd_Plain ) {
				outMark = theStyle ? 0 : checkMark;
			} else {
				UInt8 i = inCommand - cmd_Plain - 1;
				outMark = (theStyle & (1 << i)) ? checkMark : 0;
			}
			outEnabled = true;
			outUsesMark = true;
			outName[0] = 0;
			return;
		}
				
		
		// Other commands
		switch( inCommand )
		{
				
				
			case cmd_FontLarger:
			case cmd_FontSmaller:
			enableIt = true;
				break;				

			case cmd_FontOther:
			enableIt = true;
			break;

		}
			
		if ( enableIt )
		{
			outEnabled = true;
			outUsesMark = false;
			outMark = 0;
			outName[0] = 0;
		} else {
			mOwnerWindow->FindCommandStatus( inCommand, outEnabled, outUsesMark, outMark, outName );
		}
	}
	catch( ... )
	{
		outEnabled = false;
		outUsesMark = false;
		outMark = 0;
		outName[0] = 0;
	}
}


// ---------------------------------------------------------------------------------
//   Click
// ---------------------------------------------------------------------------------

void
CMENU_EditorTable::Click(
	SMouseDownEvent	&inMouseDown )
{
	if ( inMouseDown.delaySelect && DragAndDropIsPresent() ) {

		// In order to support dragging from an inactive window,
		// we must explicitly test for delaySelect and the
		// presence of Drag and Drop.

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
	
	}
}


// ---------------------------------------------------------------------------------
//   ClickCell
// ---------------------------------------------------------------------------------

void
CMENU_EditorTable::ClickCell(
	const TableCellT		&inCell,
	const SMouseDownEvent	&inMouseDown )
{
	// Call inherited.
	LTable::ClickCell( inCell, inMouseDown );

	if ( DragAndDropIsPresent() &&
		::WaitMouseMoved( inMouseDown.macEvent.where ) ) {

		// Get the selected cell.
		TableCellT	theCell;
		GetSelectedCell( theCell );
		
		if ( IsValidCell( theCell ) ) {
		
			// Focus.
			FocusDraw();
			
			// Get the cell frame.
			Rect	theCellFrame;
			FetchLocalCellFrame( theCell, theCellFrame );
	
			// Get the cell data.
			Str255	theString;
			GetCellData( theCell, theString );
			
			// Create the drag task.
			LDragTask	theDragTask( inMouseDown.macEvent, theCellFrame,
							1, 'TEXT', &theString[1], StrLength(theString), 0 );
			
			// Invalidate LView's focus cache.
			// The port may have changed during the drag.
			LView::OutOfFocus( nil );
		
			// Check for a drop in the trash.
			if ( UDragAndDropUtils::DroppedInTrash(
				theDragTask.GetDragReference() ) ) {
			
				// Delete the cell and refresh the list.
				RemoveRows( 1, theCell.row );
				Refresh();

			}

		}

	}
}


// ---------------------------------------------------------------------------------
//   DrawCell
// ---------------------------------------------------------------------------------

void
CMENU_EditorTable::DrawCell(
	const TableCellT	&inCell)
{
	// Get the cell frame.
	Rect	theCellFrame;
	if ( FetchLocalCellFrame( inCell, theCellFrame ) ) {
	
		// Get the cell data.
		Str255	theString;
		GetCellData( inCell, theString );
	
		// Setup for drawing.
		::TextFont( kFontIDGeneva );
		::TextSize( 9 );

		// Draw the string.
		MoveTo( theCellFrame.left + 4, theCellFrame.bottom - 3 );
		DrawString( theString );
	
	}
}


// ---------------------------------------------------------------------------------
//   UnhiliteCell
// ---------------------------------------------------------------------------------

void
CMENU_EditorTable::UnhiliteCell(
	const TableCellT	&inCell )
{
	if ( IsActive() ) {
	
		// Call inherited.
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
CMENU_EditorTable::ActivateSelf()
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
CMENU_EditorTable::DeactivateSelf()
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
CMENU_EditorTable::RefreshCell(
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
CMENU_EditorTable::ItemIsAcceptable(
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
CMENU_EditorTable::ReceiveDragItem(
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

	}
	
	// Invalidate the table.
	Refresh();
}


// ---------------------------------------------------------------------------------
//   EnterDropArea
// ---------------------------------------------------------------------------------

void
CMENU_EditorTable::EnterDropArea(
	DragReference	inDragRef,
	Boolean			inDragHasLeftSender )
{
	// Call inherited.
	LDragAndDrop::EnterDropArea( inDragRef, inDragHasLeftSender );

	// Invalidate the last drop cell.
	mDropRow = -1;
}


// ---------------------------------------------------------------------------------
//   LeaveDropArea
// ---------------------------------------------------------------------------------

void
CMENU_EditorTable::LeaveDropArea(
	DragReference	inDragRef )
{
	// Undo dividing line drawing.
	DrawDividingLine( mDropRow );

	// Invalidate the last drop cell.
	mDropRow = -1;

	// Call inherited.
	LDragAndDrop::LeaveDropArea( inDragRef );
}


// ---------------------------------------------------------------------------------
//   InsideDropArea
// ---------------------------------------------------------------------------------

void
CMENU_EditorTable::InsideDropArea(
	DragReference	inDragRef )
{
	// Call inherited.
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
CMENU_EditorTable::HiliteDropArea(
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
CMENU_EditorTable::GetDividingLineGivenPoint(
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
CMENU_EditorTable::DrawDividingLine(
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



PP_End_Namespace_PowerPlant
