// ===========================================================================
// CRezTypeItem.cp				
//                       Created: 2003-04-18 09:34:02
//             Last modification: 2004-03-26 00:36:05
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2003-2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
// A concrete LOutlineItem for items of type "resource category"


#include "CRezTypeItem.h"
#include "CRezObjItem.h"
#include "CRezObj.h"
#include "CRezType.h"
#include "CRezMapTable.h"
#include "RezillaConstants.h"
#include "UResources.h"
#include "UMiscUtils.h"

// #include "GetFileIcon.h"
// #include "SendFinderOpen.h"

#include <LOutlineItem.h>
#include <LOutlineTable.h>
#include <LOutlineRowSelector.h>
#include <UGAColorRamp.h>



// ---------------------------------------------------------------------------
//	¥ CRezTypeItem							Default Constructor		  [public]
// ---------------------------------------------------------------------------
// 		LLongComparator* theIDComparator = new LLongComparator;
// 		mSubItems->SetComparator(theIDComparator);

CRezTypeItem::CRezTypeItem(ResType type)
{
	mRezType = new CRezType(type);
	mIconH = nil;
}


// ---------------------------------------------------------------------------
//	¥ CRezTypeItem							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CRezTypeItem::CRezTypeItem(CRezType * inRezType)
{
	mRezType = inRezType;
	mIconH = nil;
}


// ---------------------------------------------------------------------------
//	¥ ~CRezTypeItem							Destructor				  [public]
// ---------------------------------------------------------------------------

CRezTypeItem::~CRezTypeItem()
{
	if ( mIconH != nil ) {
		::DisposeIconSuite(mIconH, true);
	}
}


// ---------------------------------------------------------------------------
//	¥ GetDrawContentsSelf
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
//	¥ CanExpand
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
//	¥ DrawRowAdornments
// ---------------------------------------------------------------------------
// Just to be cute, draw an adornment of a gray background

void
CRezTypeItem::DrawRowAdornments(
	const Rect&		inLocalRowRect )
{
	ShadeRow(UGAColorRamp::GetColor(colorRamp_Gray2), inLocalRowRect);
}


// ---------------------------------------------------------------------------
//	¥ ExpandSelf
// ---------------------------------------------------------------------------

void
CRezTypeItem::ExpandSelf()
{
	short		theID;	
	CRezObj *	theRezObj = nil;
	LOutlineItem *theItem = nil;
	LOutlineItem *lastItem = nil;

	LLongComparator* theIDComparator = new LLongComparator;
	TArray<short>* theIdArray = new TArray<short>(theIDComparator, true);
	TArrayIterator<short>	idIterator(*theIdArray);
	mRezType->GetAllRezIDs(theIdArray);

	while (idIterator.Next(theID)) {
		theRezObj = new CRezObj(mRezType, theID);
		theItem = new CRezObjItem(theRezObj);
		mOutlineTable->InsertItem( theItem, this, lastItem );
		lastItem = theItem;
	}
}


// ---------------------------------------------------------------------------
//	¥ DoubleClick
// ---------------------------------------------------------------------------
// send an open document AppleEvent to the Finder to open this
// given directory

void
CRezTypeItem::DoubleClick(
	const STableCell&			/* inCell */,
	const SMouseDownEvent&		inMouseDown,
	const SOutlineDrawContents&	/* inDrawContents */,
	Boolean						/* inHitText */)
{
	if (IsExpanded()) {
		Collapse();
	} else {
		if (inMouseDown.macEvent.modifiers & optionKey) {
// 			DeepExpand();
		} else {
			Expand();
		}
	}
}


// ---------------------------------------------------------------------------
//	¥ GetOwnerRefnum
// ---------------------------------------------------------------------------

short
CRezTypeItem::GetOwnerRefnum()
{
	CRezMapTable *theRezMapTable = dynamic_cast<CRezMapTable*>(mOutlineTable);

	return theRezMapTable->GetOwnerRefnum();
}


// ---------------------------------------------------------------------------
//	¥ GetOwnerRezMapTable
// ---------------------------------------------------------------------------

CRezMapTable *
CRezTypeItem::GetOwnerRezMapTable()
{
	CRezMapTable *theRezMapTable = dynamic_cast<CRezMapTable*>(mOutlineTable);
	return theRezMapTable;
}


// ---------------------------------------------------------------------------
//  ¥ GetSelectedRezObjItems										[public]
// ---------------------------------------------------------------------------
// Stores the selected RezObjItem's in the LArray provided. Returns the 
// number of elements found.
	
UInt32
CRezTypeItem::GetSelectedRezObjItems(LArray* & outArray)
{
	UInt32 count = 0;

	// Iterate among sub items of this RezTypeItem
	LArrayIterator iterator(*mSubItems);
	LOutlineItem *theItem = nil;	
	
	while (iterator.Next(&theItem)) {
		if ( mOutlineTable->GetTableSelector()->CellIsSelected( theItem->FindRowForItem() ) ) {
			outArray->AddItem(theItem);
			count += 1;
		} 
	}
	return count;
}


// ---------------------------------------------------------------------------
//	¥ TrackDisclosureTriangle									   [protected]
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
//  ¥ ExistsItemForID												[public]
// ---------------------------------------------------------------------------
// Looks in the table to see if the ID already exists. This is different 
// from looking in the resource map in memory. An ID could have been already 
// added to the rezmap table and not be saved yet.

Boolean
CRezTypeItem::ExistsItemForID(short inID, CRezObjItem * & outRezObjItem)
{
	Boolean existing = false;
	CRezObjItem *theRezObjItem = nil;	
	
	if ( IsExpanded() ) {
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


