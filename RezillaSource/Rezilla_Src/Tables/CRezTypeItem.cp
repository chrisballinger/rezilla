// ===========================================================================
// CRezTypeItem.cp				
//                       Created: 2003-04-18 09:34:02
//             Last modification: 2006-02-24 00:16:07
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2003-2005, 2006
// All rights reserved.
// ===========================================================================
// A concrete LOutlineItem for items of type "resource category"


#include "CRezTypeItem.h"
#include "CRezObjItem.h"
#include "CRezObj.h"
#include "CRezType.h"
#include "CRezMapDoc.h"
#include "CRezMapWindow.h"
#include "CRezMapTable.h"
#include "CEditorDoc.h"
#include "RezillaConstants.h"
#include "UResources.h"
#include "UMiscUtils.h"


#include <LOutlineItem.h>
#include <LOutlineTable.h>
#include <LOutlineRowSelector.h>
#include <UGAColorRamp.h>



// ---------------------------------------------------------------------------
//   CRezTypeItem							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CRezTypeItem::CRezTypeItem(CRezType * inRezType)
{
	mRezType = inRezType;
	mIconH = nil;
}


// ---------------------------------------------------------------------------
//     ~CRezTypeItem							Destructor				  [public]
// ---------------------------------------------------------------------------

CRezTypeItem::~CRezTypeItem()
{
	if ( mIconH != nil ) {
		::DisposeIconSuite(mIconH, true);
	}
	// Delete the RezObjItems first to respect the ModelObjects hierarchy:
	// the RezType object is the superModel of the RezObjs associated
	// with these RezObjItem objects.
	if ( IsExpanded() ) {
		Collapse();
	}
	// Then delete the RezType object
	if ( mRezType != nil ) {
		delete mRezType;
	}
}


// ---------------------------------------------------------------------------
//   GetDrawContentsSelf
// ---------------------------------------------------------------------------
// Determine what is to be drawn in a given column

void
CRezTypeItem::GetDrawContentsSelf(
	const STableCell&		inCell,
	SOutlineDrawContents&	ioDrawContents)
{

	switch (inCell.col)
	{
		case 1:
		{
			Str255 theString;
			UMiscUtils::OSTypeToPString(mRezType->GetType(), theString);	
	
			ioDrawContents.outShowSelection = false;
			ioDrawContents.outHasIcon = false;
// 			ioDrawContents.outIconSuite = mIconH;
			ioDrawContents.outTextTraits.style |= bold;
			
			LString::CopyPStr(theString, ioDrawContents.outTextString);
			
			break;
		}
		
		case 2:
		case 3:
		{
			ioDrawContents.outShowSelection = false;
			ioDrawContents.outHasIcon = false;
			ioDrawContents.outTextTraits.style = 0;
			
			LString::CopyPStr("\p", ioDrawContents.outTextString);
			
			break;
		}
	}
}


// ---------------------------------------------------------------------------
//   CanExpand
// ---------------------------------------------------------------------------
// by default, rows are not expanders.. but since this is a directory
// and we're showing hierarchy, of course we need to be able to expand.
// So we must make sure the table is aware of that fact.

Boolean
CRezTypeItem::CanExpand() const
{	
	return true;
}


// ---------------------------------------------------------------------------
//   DrawRowAdornments
// ---------------------------------------------------------------------------
// Just to be cute, draw an adornment of a gray background

void
CRezTypeItem::DrawRowAdornments(
	const Rect&		inLocalRowRect )
{
	ShadeRow(UGAColorRamp::GetColor(colorRamp_Gray2), inLocalRowRect);
}


// ---------------------------------------------------------------------------
//   ExpandSelf
// ---------------------------------------------------------------------------

void
CRezTypeItem::ExpandSelf()
{
	short			theID;	
	CRezObj *		theRezObj = nil;
	CRezMapTable *	table = dynamic_cast<CRezMapTable*>(mOutlineTable);
	CRezMapDoc *	theDoc = table->GetOwnerWindow()->GetOwnerDoc();
	CEditorDoc *	theEditor;
	ResType			theType = mRezType->GetType();
	
	TArray<short>*	theIdArray = new TArray<short>();
	mRezType->GetAllRezIDs(theIdArray);

	TArrayIterator<short>	idIterator(*theIdArray);
	while (idIterator.Next(theID)) {
		// If there is an editor corresponding to this resource, share its
		// own CRezObj, otherwise create a new one. The former situation
		// can happen if an editor has been opened from a CRezObjItem and
		// then the containing CRezTypeItem was collapsed and subsequently
		// re-expanded. Third argument is true because we want an exact 
		// correspondance.
		theEditor = theDoc->GetRezEditor(theType, theID, true);
		
		if (theEditor != nil) {
			theRezObj = theEditor->GetRezObj();
		} else {
			theRezObj = new CRezObj(mRezType, theID);
		}
		CRezObjItem *	theItem = new CRezObjItem(theRezObj);
		CRezTypeItem *	theTypeItem = table->GetRezTypeItem(theType, false);
		table->InsertRezObjItem(theItem, theTypeItem);
	}
	delete theIdArray;
}


// ---------------------------------------------------------------------------
//   SingleClick												   [protected]
// ---------------------------------------------------------------------------
// Since version 1.1, a single click on a RezTypeItem does nothing. See 
// double click below.

void
CRezTypeItem::SingleClick(
	const STableCell&			/* inCell */,
	const SMouseDownEvent&		/* inMouseDown */,
	const SOutlineDrawContents&	/* inDrawContents */,
	Boolean						/* inHitText */)
{
}


// ---------------------------------------------------------------------------
//   DoubleClick
// ---------------------------------------------------------------------------
// Since version 1.1, a double click on a RezTypeItem tries to open a
// resource picker if it exists, otherwise it collapses/expands the item 
// alternatively.

void
CRezTypeItem::DoubleClick(
	const STableCell&			/* inCell */,
	const SMouseDownEvent&		/* inMouseDown */,
	const SOutlineDrawContents&	/* inDrawContents */,
	Boolean						/* inHitText */)
{
	CRezMapTable *theRezMapTable = GetOwnerRezMapTable();
	if (theRezMapTable && theRezMapTable->GetOwnerDoc()->TryOpenPicker(this) == false) {
		if (IsExpanded()) {
			Collapse();
		} else {
			Expand();
		}
	} 
}


// ---------------------------------------------------------------------------
//   GetOwnerRezMapTable
// ---------------------------------------------------------------------------

CRezMapTable *
CRezTypeItem::GetOwnerRezMapTable()
{
	CRezMapTable *theRezMapTable = dynamic_cast<CRezMapTable*>(mOutlineTable);
	return theRezMapTable;
}


// ---------------------------------------------------------------------------
//   GetSelectedRezObjItems										[public]
// ---------------------------------------------------------------------------
// Stores the selected RezObjItem's in the LArray provided. Returns the 
// number of elements found.
	
UInt32
CRezTypeItem::GetSelectedRezObjItems(LArray* & outArray)
{
	UInt32 count = 0;

	// Iterate among sub items of this RezTypeItem
	if (mSubItems != nil) {
		LArrayIterator iterator(*mSubItems);
		LOutlineItem *theItem = nil;	
		
		while (iterator.Next(&theItem)) {
			if ( mOutlineTable->GetTableSelector()->CellIsSelected( theItem->FindRowForItem() ) ) {
				outArray->AddItem(theItem);
				count += 1;
			} 
		}
	} 
	return count;
}


// ---------------------------------------------------------------------------
//   TrackDisclosureTriangle									   [protected]
// ---------------------------------------------------------------------------
//	Called by ClickCell whenever a mouse-down is detected within the
//	disclosure triangle. Tracks the mouse movement until mouse-up and
//	expands or collapses this item as appropriate.

void
CRezTypeItem::TrackDisclosureTriangle(
	const SMouseDownEvent& inMouseDown)
{
	LOutlineItem::TrackDisclosureTriangle(inMouseDown);
	if (inMouseDown.macEvent.modifiers & optionKey) {
		if ( IsExpanded() ) {
			GetOwnerRezMapTable()->ExpandAll();
		} else {
			GetOwnerRezMapTable()->CollapseAll();
		}
	}
}


// ---------------------------------------------------------------------------
//   ExistsItemForID												[public]
// ---------------------------------------------------------------------------
// Looks in the table to see if the ID already exists. This is different 
// from looking in the resource map in memory. An ID could have been already 
// added to the rezmap table and not be saved yet.

Boolean
CRezTypeItem::ExistsItemForID(short inID, CRezObjItem * & outRezObjItem)
{
	Boolean existing = false;
	CRezObjItem *theRezObjItem = nil;	
	
	if ( IsExpanded() && mSubItems != nil) {
		LArrayIterator iterator(*mSubItems);
		LOutlineItem *theItem = nil;	
		
		// Iterate among subitems
		while (iterator.Next(&theItem)) {
			theRezObjItem = dynamic_cast<CRezObjItem *>(theItem);
			
			if ( theRezObjItem->GetRezObj()->GetID() == inID ) {
				outRezObjItem = theRezObjItem;
				existing = true;
				break;
			} 
		}
	}
	
	return existing;
}


