// ===========================================================================
// CRezMapTable.cp					
//                       Created: 2003-04-16 22:13:54
//             Last modification: 2004-04-18 16:47:45
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2003-2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

//	Subclass and concrete instantiation of LOutlineTable

#include "CRezMapTable.h"
#include "CRezMapDoc.h"
#include "CRezMap.h"
#include "CRezType.h"
#include "CRezObjItem.h"
#include "CRezObj.h"
#include "CRezTypeItem.h"
#include "CRezMapWindow.h"
#include "CTextHandleStream.h"
#include "RezillaConstants.h"
#include "UDragAndDropUtils.h"
#include "UMessageDialogs.h"
#include "UMiscUtils.h"

#include <LTableMultiGeometry.h>
#include <LOutlineKeySelector.h>
#include <LOutlineRowSelector.h>
#include <LOutlineItem.h>
#include <UAttachments.h>
#include <LDragTask.h>


Boolean		CRezMapTable::sApplyToOthers = false;
MessageT	CRezMapTable::sConflictAction = answer_Do;


// ---------------------------------------------------------------------------
//  ¥ CRezMapTable						Default Constructor		  [public]
// ---------------------------------------------------------------------------

CRezMapTable::CRezMapTable(
	LStream *inStream )
		: LOutlineTable( inStream ), 
		CRezMapDragDrop( UQDGlobals::GetCurrentWindowPort(), this )
{
	// Set the table geometry
	SetTableGeometry(new LTableMultiGeometry(this, kRzilColWidth, 20));
	
	// Set the table selector
	SetTableSelector(new LOutlineRowSelector( this ) );
	
	// We don't set the table storage...
	
// 	// Attach comparators to get the items sorted.
// 	CTypeItemComparator* theTypeComparator = new CTypeItemComparator;
// 	mFirstLevelItems.SetComparator(theTypeComparator);
// 	mFirstLevelItems.SetKeepSorted(true);
		
	// Insert three columns (type, size and name)
	InsertCols( 3, 0, nil, nil, false );
	SetColWidth(250, 3, 3);
	
	// Set up keyboard selection and scrolling.
	AddAttachment(new LOutlineKeySelector(this, msg_AnyMessage));
	AddAttachment(new LKeyScrollAttachment(this));

	// Try to become default commander in the window.
	if (mSuperCommander != nil) {
		mSuperCommander->SetLatentSub(this);
	}
}


// ---------------------------------------------------------------------------
//  ¥ ~CRezMapTable							Destructor				  [public]
// ---------------------------------------------------------------------------
CRezMapTable::~CRezMapTable()
{
	// nothing
}


// ---------------------------------------------------------------------------
//  ¥ FinishCreateSelf												[public]
// ---------------------------------------------------------------------------

void
CRezMapTable::FinishCreateSelf()
{
// 	mModified = false;
}


// ---------------------------------------------------------------------------
//  ¥ DrawSelf												[public]
// ---------------------------------------------------------------------------

void
CRezMapTable::DrawSelf()
{
	// Call inherited
	LOutlineTable::DrawSelf();
	
	// Add a thin white border (the same used by UnhiliteDropArea)
	StColorPenState	savePenState;
	PenState	thePenState;
	Rect		theRect;
	RGBColor	theForeColor = Color_White;
	RGBColor	theBackColor = Color_White;
	thePenState.pnLoc = Point_00;
	thePenState.pnSize.h = kRzilDragHiliteSize;
	thePenState.pnSize.v = kRzilDragHiliteSize;
	thePenState.pnMode = patCopy;
	UQDGlobals::GetBlackPat(&thePenState.pnPat);
	
	CalcLocalFrameRect(theRect);
	::SetPenState(&thePenState);
	::RGBForeColor(&theForeColor);
	::RGBBackColor(&theBackColor);
	::MacFrameRect(&theRect);
	
	ApplyForeAndBackColors();
}


// ---------------------------------------------------------------------------
//  ¥ GetOwnerRefnum												[public]
// ---------------------------------------------------------------------------

short
CRezMapTable::GetOwnerRefnum() 
{ 
	return mRezMap->GetRefnum();
}


// ---------------------------------------------------------------------------
//  ¥ GetOwnerRefnum												[public]
// ---------------------------------------------------------------------------

void
CRezMapTable::SetOwnerRefnum(short theOwnerRefnum) 
{ 
	mRezMap->SetRefnum(theOwnerRefnum);
}
	

// ---------------------------------------------------------------------------
//  ¥ Populate												[public]
// ---------------------------------------------------------------------------

void
CRezMapTable::Populate(TArray<ResType>* inTypesArray)
{
	TArrayIterator<ResType>	typeIterator(*inTypesArray);
	CRezType * theRezType;
	ResType	theType;
	LOutlineItem *theItem = nil;	
	LOutlineItem *lastItem = nil;

	while (typeIterator.Next(theType)) {
		theRezType = new CRezType(theType, mRezMap);
		theItem = new CRezTypeItem( theRezType );
		InsertItem( theItem, nil, lastItem );
		lastItem = theItem;
	}
}


// ---------------------------------------------------------------------------
//  ¥ TypeExists												[public]
// ---------------------------------------------------------------------------
// Looks in the table to see if the type already exists. This is different 
// from looking in the resource map in memory. A type could have been already 
// added to the rezmap table and not be saved yet.

Boolean
CRezMapTable::TypeExists(ResType inType, CRezTypeItem * & outRezTypeItem)
{
	Boolean existing = false;
	
	LArrayIterator iterator(mFirstLevelItems);
	LOutlineItem *theItem = nil;	
	CRezTypeItem *theRezTypeItem = nil;	
	
	// Iterate among first level items
	while (iterator.Next(&theItem)) {
		theRezTypeItem = dynamic_cast<CRezTypeItem *>(theItem);
		
		if ( theRezTypeItem->GetRezType()->GetType() == inType ) {
			outRezTypeItem = theRezTypeItem;
			existing = true;
			break;
		} 
	}
	
	return existing;
}


// ---------------------------------------------------------------------------
//  ¥ InsertRezTypeItem												[public]
// ---------------------------------------------------------------------------

void
CRezMapTable::InsertRezTypeItem(CRezTypeItem * inRezTypeItem)
{
	ResType			theType, inType = inRezTypeItem->GetRezType()->GetType();
	LOutlineItem *	theItem = nil;	
	CRezTypeItem *	theRezTypeItem = nil;	
	CRezTypeItem *	prevRezTypeItem = nil;	
	Boolean found = false;
	
	// Iterate among first level items
	LArrayIterator iterator(mFirstLevelItems);
	while (iterator.Next(&theItem)) {
		prevRezTypeItem = theRezTypeItem;
		theRezTypeItem = dynamic_cast<CRezTypeItem *>(theItem);
		theType = theRezTypeItem->GetRezType()->GetType();
		
		if ( ::CompareText( (const void *) &theType, (const void *) &inType, 4, 4, nil) >= 0 ) {
			found = true;
			break;
		} 
	}
	if (!found) {
		// We have reached the end of the list
		prevRezTypeItem = theRezTypeItem;
	} 
	InsertItem( inRezTypeItem, nil, prevRezTypeItem );	
}


// ---------------------------------------------------------------------------
//  ¥ InsertRezObjItem												[public]
// ---------------------------------------------------------------------------

void
CRezMapTable::InsertRezObjItem(CRezObjItem * inRezObjItem, CRezTypeItem * inRezTypeItem)
{
	ResType			theID, inID = inRezObjItem->GetRezObj()->GetID();
	LOutlineItem *	theItem = nil;	
	CRezObjItem *	theRezObjItem = nil;	
	CRezObjItem *	prevRezObjItem = nil;	
	Boolean found = false;
	
	// Iterate among subitems of the RezTypeItem
	LArrayIterator iterator( *(inRezTypeItem->GetSubItems()) );
	while (iterator.Next(&theItem)) {
		prevRezObjItem = theRezObjItem;
		theRezObjItem = dynamic_cast<CRezObjItem *>(theItem);
		theID = theRezObjItem->GetRezObj()->GetID();
		
		if ( theID >= inID ) {
			found = true;
			break;
		} 
	}
	if (!found) {
		// We have reached the end of the list
		prevRezObjItem = theRezObjItem;
	} 
	InsertItem( inRezObjItem, inRezTypeItem, prevRezObjItem );	
}


// ---------------------------------------------------------------------------
//  ¥ HasSelection												[public]
// ---------------------------------------------------------------------------

Boolean
CRezMapTable::HasSelection()
{
	return ( mTableSelector->GetFirstSelectedRow() != 0);
}


// ---------------------------------------------------------------------------
//  ¥ HasSelectedRezTypeItems												[public]
// ---------------------------------------------------------------------------
// Returns true if there is at least one RezTypeItem selected.

Boolean
CRezMapTable::HasSelectedRezTypeItems()
{
	Boolean oneIsSelected = false;
	
	// Iterate among first level items<LOutlineItem*>
	LArrayIterator	iterator(mFirstLevelItems);
	LOutlineItem *theItem = nil;	
	
	while (iterator.Next(&theItem)) {
		if ( GetTableSelector()->CellIsSelected( theItem->FindRowForItem() ) ) {
			oneIsSelected = true;
			break;
		} 
	}
	return oneIsSelected;
}


// ---------------------------------------------------------------------------
//  ¥ CountSelectedRezTypeItems										[public]
// ---------------------------------------------------------------------------
// Returns the count of all the selected RezTypeItem's.
	
UInt32
CRezMapTable::CountSelectedRezTypeItems()
{
	UInt32 count = 0;

	// Iterate among first level items
	LArrayIterator iterator(mFirstLevelItems);
	LOutlineItem *theItem = nil;	
	
	while (iterator.Next(&theItem)) {
		if ( GetTableSelector()->CellIsSelected( theItem->FindRowForItem() ) ) {
			count += 1;
		} 
	}
	return count;
}


// ---------------------------------------------------------------------------
//  ¥ GetSelectedRezTypeItems										[public]
// ---------------------------------------------------------------------------
// Stores the selected RezTypeItem's in the LArray provided. Returns the 
// number of elements found.
	
UInt32
CRezMapTable::GetSelectedRezTypeItems(LArray* & outArray)
{
	UInt32 count = 0;

	// Iterate among first level items
	LArrayIterator iterator(mFirstLevelItems);
	LOutlineItem *theItem = nil;	
	
	while (iterator.Next(&theItem)) {
		if ( GetTableSelector()->CellIsSelected( theItem->FindRowForItem() ) ) {
			outArray->AddItem(&theItem);
			count += 1;
		} 
	}
	return count;
}


// ---------------------------------------------------------------------------
//  ¥ HasSelectedRezObjItems										[public]
// ---------------------------------------------------------------------------
// Returns true if there is at least one RezObjItem selected.

Boolean
CRezMapTable::HasSelectedRezObjItems()
{
	Boolean oneIsSelected = false;
	
	// Iterate among first level items
	LArrayIterator rezTypeIterator(mFirstLevelItems);
	LOutlineItem *theRezTypeItem = nil;	
	LOutlineItem *theRezObjItem = nil;	
	
	while (rezTypeIterator.Next(&theRezTypeItem)) {
		if (theRezTypeItem->IsExpanded()) {
			// Now iterate among sub items of this RezTypeItem
			LArrayIterator rezObjIterator( *(theRezTypeItem->GetSubItems()) );
			
			while (rezObjIterator.Next(&theRezObjItem)) {
				if ( GetTableSelector()->CellIsSelected( theRezObjItem->FindRowForItem() ) ) {
					oneIsSelected = true;
					return oneIsSelected;
				} 
			}
		}
	}
	
	return oneIsSelected;
}


// ---------------------------------------------------------------------------
//  ¥ CountAllSelectedRezObjItems										[public]
// ---------------------------------------------------------------------------
// Returns the count of all the selected RezObjItem's.
	
UInt32
CRezMapTable::CountAllSelectedRezObjItems()
{
	UInt32 count = 0;
	
	// Iterate among first level items
	LArrayIterator rezTypeIterator(mFirstLevelItems);
	LOutlineItem *theRezTypeItem = nil;	
	LOutlineItem *theRezObjItem = nil;	
	
	while (rezTypeIterator.Next(&theRezTypeItem)) {
		if (theRezTypeItem->IsExpanded()) {
			// Now iterate among sub items of this RezTypeItem
			LArrayIterator rezObjIterator( *(theRezTypeItem->GetSubItems()) );
			
			while (rezObjIterator.Next(&theRezObjItem)) {
				if ( GetTableSelector()->CellIsSelected( theRezObjItem->FindRowForItem() ) ) {
					count += 1;
				} 
			}
		} 
	}
	return count;
}


// ---------------------------------------------------------------------------
//  ¥ GetAllSelectedRezObjItems										[public]
// ---------------------------------------------------------------------------
// Stores all the selected RezObjItem's in the LArray provided. Returns the 
// number of elements found.
	
UInt32
CRezMapTable::GetAllSelectedRezObjItems(LArray* & outArray)
{
	UInt32 count = 0;
	
	// Iterate among first level items
	LArrayIterator rezTypeIterator(mFirstLevelItems);
	LOutlineItem *theRezTypeItem = nil;	
	LOutlineItem *theRezObjItem = nil;	
	
	while (rezTypeIterator.Next(&theRezTypeItem)) {
		if (theRezTypeItem->IsExpanded()) {
			// Now iterate among sub items of this RezTypeItem
			LArrayIterator rezObjIterator( *(theRezTypeItem->GetSubItems()) );
			
			while (rezObjIterator.Next(&theRezObjItem)) {
				if ( GetTableSelector()->CellIsSelected( theRezObjItem->FindRowForItem() ) ) {
					outArray->AddItem(&theRezObjItem);
					count += 1;
				} 
			}
		} 
	}
	return count;
}


// ---------------------------------------------------------------------------
//  ¥ GetFirstSelectedRezObjItem										[public]
// ---------------------------------------------------------------------------
// Stores the first selected RezObjItem in the LArray provided. Returns the 
// number of elements found.
	
void
CRezMapTable::GetFirstSelectedRezObjItem(CRezObjItem* & outRezObjItem)
{
	UInt32 count = 0;
	
	// Iterate among first level items
	LArrayIterator rezTypeIterator(mFirstLevelItems);
	LOutlineItem *theRezTypeItem = nil;	
	LOutlineItem *theRezObjItem = nil;	
	
	while (rezTypeIterator.Next(&theRezTypeItem)) {
		if (theRezTypeItem->IsExpanded()) {
			// Now iterate among sub items of this RezTypeItem
			LArrayIterator rezObjIterator( *(theRezTypeItem->GetSubItems()) );
			
			while (rezObjIterator.Next(&theRezObjItem)) {
				if ( GetTableSelector()->CellIsSelected( theRezObjItem->FindRowForItem() ) ) {
					outRezObjItem = dynamic_cast<CRezObjItem*>(theRezObjItem) ;
					return;
				} 
			}
		} 
	}
	return;
}


// ---------------------------------------------------------------------------
//  ¥ GetRezObjItem											[public]
// ---------------------------------------------------------------------------
// Stores all the selected RezObjItem's in the LArray provided. Returns the 
// number of elements found.
	
CRezObjItem *
CRezMapTable::GetRezObjItem(ResType inType, short inID)
{	
	CRezObjItem * outRezObjItem = nil;
	
	// Iterate among first level items
	LArrayIterator rezTypeIterator(mFirstLevelItems);
	LOutlineItem *theRezTypeItem = nil;	
	LOutlineItem *theRezObjItem = nil;	
	
	while (rezTypeIterator.Next(&theRezTypeItem)) {
		
		if (theRezTypeItem->IsExpanded() && dynamic_cast<CRezTypeItem*>(theRezTypeItem)->GetRezType()->GetType() == inType) {
			// Now iterate among sub items of this RezTypeItem
			LArrayIterator rezObjIterator( *(theRezTypeItem->GetSubItems()) );
			
			while (rezObjIterator.Next(&theRezObjItem)) {
				outRezObjItem = dynamic_cast<CRezObjItem*>(theRezObjItem);
				if (outRezObjItem->GetRezObj()->GetID() == inID) {
					return outRezObjItem;
				} 
			}
		} 
	}
	return outRezObjItem;
}


// ---------------------------------------------------------------------------
//  ¥ ExpandAll										[public]
// ---------------------------------------------------------------------------
	
void
CRezMapTable::ExpandAll() {
	// Iterate among first level items
	LArrayIterator rezTypeIterator(mFirstLevelItems);
	LOutlineItem *theRezTypeItem = nil;	
	LOutlineItem *theRezObjItem = nil;	
	
	while (rezTypeIterator.Next(&theRezTypeItem)) {
		theRezTypeItem->Expand();
	} 
}


// ---------------------------------------------------------------------------
//  ¥ CollapseAll										[public]
// ---------------------------------------------------------------------------
	
void
CRezMapTable::CollapseAll() {
	// Iterate among first level items
	LArrayIterator rezTypeIterator(mFirstLevelItems);
	LOutlineItem *theRezTypeItem = nil;	
	LOutlineItem *theRezObjItem = nil;	
	
	while (rezTypeIterator.Next(&theRezTypeItem)) {
		theRezTypeItem->Collapse();
	} 
}
	

// ---------------------------------------------------------------------------
//  ¥ GetOwnerDoc										[public]
// ---------------------------------------------------------------------------
	
CRezMapDoc *
CRezMapTable::GetOwnerDoc()
{
	CRezMapDoc * theOwnerDoc = GetOwnerWindow()->GetOwnerDoc();
	return theOwnerDoc;
}


// ---------------------------------------------------------------------------
//  ¥ GetOwnerWindow										[public]
// ---------------------------------------------------------------------------
	
CRezMapWindow *
CRezMapTable::GetOwnerWindow()
{
	CRezMapWindow *theRezMapWindow = dynamic_cast<CRezMapWindow*>( GetSuperCommander() );
	return theRezMapWindow;
}


// ---------------------------------------------------------------------------
//  ¥ Click													[protected]
// ---------------------------------------------------------------------------
// If no cell is hit by the click, try drag selection.
// In order to support dragging from an inactive window,
// we must explicitly test for delaySelect and the
// presence of Drag and Drop.

void
CRezMapTable::Click(
	SMouseDownEvent&	inMouseDown)
{
	if ( inMouseDown.delaySelect && DragAndDropIsPresent() ) {

		// Convert to a local point.
		PortToLocalPoint( inMouseDown.whereLocal );
		
		// Execute click attachments.
		if ( ExecuteAttachments( msg_Click, &inMouseDown ) ) {
		
			// Handle the actual click event.
			ClickSelf( inMouseDown );

		}
	
	} else {
		// Call inherited for default behavior.	
		LOutlineTable::Click( inMouseDown );
	}
}


// ---------------------------------------------------------------------------
//		* TrackDrag												[protected]
// ---------------------------------------------------------------------------
//	Called by LOutlineItem::TrackDrag when a drag is detected from
//	within the content area of an item. 

void
CRezMapTable::TrackDrag(
	const STableCell&		/* inCell */,
	const SMouseDownEvent&	inMouseDown)
{
	StRegion		outlineRgn, tempRgn;
	Rect			theCellFrame;
	STableCell		theCell;
	Rect			itemBounds;
	void * 			thePtr;
	ItemReference	itemCount = 1;
	OSErr			error;
	Str255			theString;
	CTextHandleStream*	textDataStream = new CTextHandleStream();
	
	sApplyToOthers = false;
	sConflictAction = answer_Do;

	// Get the selected rows to build the outline region
	LArray* theArray = new LArray( sizeof(LOutlineItem*) );
	
	GetAllSelectedRezObjItems(theArray);
	LArrayIterator iterator(*theArray);
	CRezObjItem *theRezObjItem = nil;
	
	// Focus.
	FocusDraw();
	
	// Create the drag task.
	LDragTask	theDragTask( inMouseDown.macEvent );
	DragReference	theDragRef = theDragTask.GetDragReference();
	
	while (iterator.Next(&theRezObjItem)) {
		// Get the frame of the first cell in the row.
		theCell.SetCell( FindRowForItem(theRezObjItem), 1);
		GetLocalCellRect( theCell, theCellFrame );
		::LocalToGlobal(&topLeft(theCellFrame));
		::LocalToGlobal(&botRight(theCellFrame));
		// Cumulate the outline region
		tempRgn = theCellFrame;
		::MacInsetRect(&theCellFrame, 1, 1);
		tempRgn -= theCellFrame;
		outlineRgn += tempRgn;
		// Add the item to the drag
		thePtr = (void *) theRezObjItem;
		error = ::AddDragItemFlavor(theDragRef, itemCount, kRzilDragFlavor, 
									&thePtr, sizeof(CRezObjItem*),
									flavorSenderOnly);
		error = ::SetDragItemBounds(theDragRef, itemCount, &theCellFrame);

		// Cumulate TEXT information
		UMiscUtils::OSTypeToPString(theRezObjItem->GetRezObj()->GetType(), theString);
		*textDataStream << theString;
		*textDataStream << (char) 0x09;
		::NumToString(theRezObjItem->GetRezObj()->GetID(), theString);
		*textDataStream << theString;
		*textDataStream << (char) 0x09;
		::NumToString(theRezObjItem->GetRezObj()->GetSize(), theString);
		*textDataStream << theString;
		*textDataStream << (char) 0x09;
		*textDataStream << *(theRezObjItem->GetRezObj()->GetName());
		*textDataStream << (char) 0x0D;
		
		itemCount++;
	} 
	
	// Store the TEXT information in the first item
	Handle theHandle = textDataStream->GetDataHandle();
	if (theHandle != nil) {
		StHandleLocker locker(theHandle);
		thePtr = (void *) *theHandle;
		error = ::AddDragItemFlavor(theDragRef, 1, 'TEXT', 
									*(textDataStream->GetDataHandle()), 
									textDataStream->GetMarker(), 0L );
	} 
	error = ::TrackDrag(theDragRef, &inMouseDown.macEvent, outlineRgn);
	
	// Invalidate LView's focus cache. The port may have changed during the drag.
	LView::OutOfFocus( nil );
	
	// Check for a drop in the trash.
	if (error == noErr && UDragAndDropUtils::DroppedInTrash( theDragRef ) ) {
		// Delete the row and refresh the list.
		GetOwnerDoc()->RemoveResource(theRezObjItem);
		Refresh();
	}
	
	if (theArray != nil) {
		delete theArray;
	} 
}


// ---------------------------------------------------------------------------
//	¥ ItemIsAcceptable										  [protected]
// ---------------------------------------------------------------------------
// If flavor is of type flavorTypeHFS, accept only TEXT files. Otherwise, 
// any flavor is accepted: a resource of the same type as the flavor will be 
// created.

Boolean 
CRezMapTable::ItemIsAcceptable(DragReference inDragRef, ItemReference inItemRef)
{
	FlavorFlags	theFlags;
	Boolean isDirectory = false;
	
	if ( GetOwnerDoc()->GetReadOnlyDoc() ) {
		return false;
	} 
	
	if (::GetFlavorFlags(inDragRef, inItemRef, flavorTypeHFS, &theFlags) == noErr)
	{
		CInfoPBRec theInfo;
		HFSFlavor fileData;
		UMiscUtils::GetDragFileData(inDragRef, inItemRef, fileData);
		theInfo.hFileInfo.ioCompletion = nil;
		theInfo.hFileInfo.ioVRefNum = fileData.fileSpec.vRefNum;
		theInfo.hFileInfo.ioDirID = fileData.fileSpec.parID;
		theInfo.hFileInfo.ioNamePtr = fileData.fileSpec.name;
		theInfo.hFileInfo.ioFDirIndex = 0;
		
		ThrowIfOSErr_(::PBGetCatInfoSync( &theInfo ));
		if ( theInfo.hFileInfo.ioFlAttrib & ioDirMask ) {
			// It's a directory
			return false;
		} else { 
			return (fileData.fileType == 'TEXT');
		}
	}
	
	return true;
}


// ---------------------------------------------------------------------------
//	¥ ReceiveDragItem										  [protected]
// ---------------------------------------------------------------------------

void 
CRezMapTable::ReceiveDragItem(DragReference inDragRef, 
							 DragAttributes inDragAttrs, 
							 ItemReference inItemRef, 
							 Rect & inItemBounds)
{
	FlavorFlags theFlags;
	OSErr 		error;
	ResType		theType;
	short 		theID;
	Size 		theSize;
	UInt16		index;
	SInt16		answer;
	void * 		theAdr;
	CRezObjItem	*newRezObjItem, *oldRezObjItem;
	
	if (::GetFlavorFlags(inDragRef, inItemRef, kRzilDragFlavor, &theFlags) == noErr) {
		// Data coming from inside the application: pointer to the sending rezmap table.
		error = ::GetFlavorDataSize(inDragRef, inItemRef, kRzilDragFlavor, &theSize);
		
		error = ::GetFlavorData(inDragRef, inItemRef, kRzilDragFlavor, &theAdr, &theSize, 0);
		newRezObjItem = (CRezObjItem *) NewPtr( sizeof(CRezObjItem) );
		BlockMoveData( theAdr, (void *) newRezObjItem, sizeof(CRezObjItem));
		
		if (error == noErr && newRezObjItem != nil) {
			Boolean replace = false;
			// Check for conflicting IDs
			CRezObj * theRezObj = newRezObjItem->GetRezObj();
			theType = theRezObj->GetType();
			theID = theRezObj->GetID();
			if ( mRezMap->ResourceExists(theType, theID) ) {
				if (!sApplyToOthers) {
					answer = UMessageDialogs::AskSolveUidConflicts(theType, theID, sApplyToOthers);
					sConflictAction = answer;
				} else {
					answer = sConflictAction;
				}
				switch (answer) {
					case answer_Do:
					mRezMap->UniqueID(theType, theID);;
					break;
					
					case answer_Dont:
					replace = true;
					break;
					
					case answer_Cancel:
					return;
				}
			}
			GetOwnerDoc()->PasteResource(theType, theID, 
										 theRezObj->GetData(), 
										 theRezObj->GetName(), 
										 theRezObj->GetAttributes(),
										 replace);			
		 }
		 
		 if (newRezObjItem != nil) {
			 ::DisposePtr( (char*) newRezObjItem);
		 } 
		 
	 } else if (::GetFlavorFlags(inDragRef, inItemRef, flavorTypeHFS, &theFlags) == noErr) {
		 // Drag from the Finder
		 // What to do ?
	 } else {
		 UInt16      theFlavorsCount;
		 error = ::CountDragItemFlavors(inDragRef, inItemRef, &theFlavorsCount);
		 if (error == noErr) {
			 for (index = 1; index <= theFlavorsCount; index++) {
				 error = ::GetFlavorType(inDragRef, inItemRef, index, &theType);
				 error = ::GetFlavorDataSize(inDragRef, inItemRef, theType, &theSize);
				 
				 if (theType == 'TEXT' && theSize > 32*1024) {
					 theSize = 32*1024;  // kMaxChars
				 } 
				 
				 if (error == noErr) {
					 Handle theHandle = ::NewHandle(theSize);
					 error = ::GetFlavorData(inDragRef, inItemRef, theType, *theHandle, &theSize, 0);
					 
					 if (error == noErr) {
						 mRezMap->UniqueID(theType, theID);
						 GetOwnerDoc()->PasteResource(theType, theID, theHandle, nil, 0, false);			
					 }
					 
					 if (theHandle != nil) {
						 ::DisposeHandle(theHandle);
					 } 
				 }
			 }
		 }
	 }
 }


// ---------------------------------------------------------------------------
//  ¥ RemoveAllItems										[public]
// ---------------------------------------------------------------------------
// Stores all the selected RezObjItem's in the LArray provided. Returns the 
// number of elements found.
	
void
CRezMapTable::RemoveAllItems()
{	
	// Iterate among first level items
	LArrayIterator rezTypeIterator(mFirstLevelItems);
	LOutlineItem *theRezTypeItem = nil;	
	LOutlineItem *theRezObjItem = nil;	
	
	while (rezTypeIterator.Next(&theRezTypeItem)) {
		if (theRezTypeItem->IsExpanded()) {
			// Now iterate among sub items of this RezTypeItem
			LArrayIterator rezObjIterator( *(theRezTypeItem->GetSubItems()) );
			while (rezObjIterator.Next(&theRezObjItem)) {
				RemoveItem(theRezObjItem, false, false);
			}
		} 
		RemoveItem(theRezTypeItem, false, false);
	}
}



