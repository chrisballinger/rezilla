// ===========================================================================
// CBroadcasterTableView.cp					
// 
//                       Created : 2002-05-14 20:00:17
//             Last modification : 2004-03-02 10:28:40
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@users.sourceforge.net>
// www : <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2002-2004
// All rights reserved.
// ===========================================================================

#include "CBroadcasterTableView.h"


// ---------------------------------------------------------------------------
//		¥ CBroadcasterTableView
// ---------------------------------------------------------------------------
//	Constructor

CBroadcasterTableView::CBroadcasterTableView(
	LStream		*inStream)
		: LTableView(inStream)
{
	// The flags set in Constructor 
	*inStream >> mValueMessage;
	*inStream >> mUseDragSelect;
	*inStream >> mCustomHilite;
	*inStream >> mDeferAdjustment;
	
	mFaceStyle = normal;
}


// ---------------------------------------------------------------------------
//		¥ ~CBroadcasterTableView
// ---------------------------------------------------------------------------
//	Destructor

CBroadcasterTableView::~CBroadcasterTableView()
{
}


// ---------------------------------------------------------------------------
//		¥ DrawCell
// ---------------------------------------------------------------------------

void
CBroadcasterTableView::DrawCell(
	const STableCell	&inCell,
	const Rect			&inLocalRect)
{
	TextFont(1);
	TextSize(9);
	TextFace(mFaceStyle);
	
	Str255	theString;
	UInt32	dataSize = sizeof(Str255);
	GetCellData(inCell, &theString, dataSize);
	
	::MoveTo(inLocalRect.left + 4, inLocalRect.top + 12);
	::DrawString(theString);	
}


// ---------------------------------------------------------------------------
//		¥ HiliteCellActively
// ---------------------------------------------------------------------------
//	Draw or undraw active hiliting for a Cell

void
CBroadcasterTableView::HiliteCellActively(
	const STableCell	&inCell,
	Boolean				inHilite)
{
	LTableView::HiliteCellActively(inCell, inHilite);
	return;
	
	Rect	cellFrame;
	if (GetLocalCellRect(inCell, cellFrame) && FocusExposed()) {
		
		TextFont(1);
		TextSize(9);
		TextFace(0);
		
		Str255	theString;
		UInt32	dataSize = sizeof(theString);
		GetCellData(inCell, &theString, dataSize);
		
		::MoveTo(cellFrame.left + 4, cellFrame.bottom - 4);
		
		if (inHilite) {
			TextFace(outline);
		}
		
		::EraseRect(&cellFrame);
		::DrawString(theString);	
	}
}


// ---------------------------------------------------------------------------
//		¥ HiliteCellInactively
// ---------------------------------------------------------------------------
//	Draw or undraw inactive hiliting for a Cell

void
CBroadcasterTableView::HiliteCellInactively(
	const STableCell	&inCell,
	Boolean				inHilite)
{
	LTableView::HiliteCellInactively(inCell, inHilite);
	return;

	Rect	cellFrame;
	if (GetLocalCellRect(inCell, cellFrame) && FocusExposed()) {

		TextFont(1);
		TextSize(9);
		TextFace(0);
		
		Str255	theString;
		UInt32	dataSize = sizeof(theString);
		GetCellData(inCell, &theString, dataSize);
		
		::MoveTo(cellFrame.left + 4, cellFrame.bottom - 4);
		
		if (inHilite) {
			TextFace(bold);
		}
		
		::EraseRect(&cellFrame);
		::DrawString(theString);	
	}
}


// ---------------------------------------------------------------------------
//	¥ ClickCell
// ---------------------------------------------------------------------------
//	Handle a mouse click within the specified Cell

void
CBroadcasterTableView::ClickCell(
	const STableCell&		/* inCell */,
	const SMouseDownEvent&	/* inMouseDown */)
{
	BroadcastMessage(mValueMessage,this);
}


