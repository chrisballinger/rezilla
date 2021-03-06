// ===========================================================================
// CMenuObject.cp
// 
//                       Created: 2005-03-10 09:12:57
//             Last modification: 2006-09-30 06:31:46
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes, 2005-2006
// All rights reserved.
// ===========================================================================

#include "CMenuObject.h"
#include "CMenuItem.h"
#include "RezillaConstants.h"
#include "UMiscUtils.h"
#include "UResources.h"

#include <LHandleStream.h>
#include <UResourceMgr.h>

// ---------------------------------------------------------------------------
//  CMenuObject												[public]
// ---------------------------------------------------------------------------

CMenuObject::CMenuObject()
{
	mTitle[0] = 0;
	mID = 0;
	mMDEF = 0;
	mEnableFlag = false;
}


// ---------------------------------------------------------------------------
//  CMenuObject												[public]
// ---------------------------------------------------------------------------

CMenuObject::CMenuObject(ResIDT	inID,
						ResIDT	inMDEF,
						UInt32	inEnableFlag,
						Str255	inTitle)
{
	SetValues(inID, inMDEF, inEnableFlag, inTitle);
	mItemIndex = 0;	
}


// ---------------------------------------------------------------------------
//  CMenuObject												[public]
// ---------------------------------------------------------------------------

CMenuObject::CMenuObject(LHandleStream * inStream)
{
	InstallData(inStream);
}


// ---------------------------------------------------------------------------
//  ~CMenuObject												[public]
// ---------------------------------------------------------------------------

CMenuObject::~CMenuObject()
{
	TArrayIterator<CMenuItem*> iteraror(mItems, LArrayIterator::from_End);
	CMenuItem *	theItem;
	while (iteraror.Previous(theItem)) {
		mItems.RemoveItemsAt(1, iteraror.GetCurrentIndex());
		delete theItem;
	}
}


// ---------------------------------------------------------------------------
//  CMenuObject												[static, public]
// ---------------------------------------------------------------------------

Boolean	
CMenuObject::GetMenuTitle(short inID, short inRefnum, Str255 outString)
{
//	Boolean 		result = false;
	Str255			theTitle;
	Handle			theResHandle = NULL;
	
	StRezRefSaver refSaver(inRefnum);
	theResHandle = ::Get1Resource('MENU', inID);
	::HandToHand(&theResHandle);

	theTitle[0] = 0;

	if (theResHandle != NULL) {
		LHandleStream * theStream = new LHandleStream(theResHandle);
		theStream->SetNativeEndian(UResFlip::HasFlipper('MENU'));
		
		if (theStream) {
			if (theStream->GetLength() > 14) {
				// The menu title is at position 14 in the resource
				theStream->SetMarker(14, streamFrom_Start);
				try {
					*theStream >> theTitle;
				} catch (...) {
					theTitle[0] = 0;
				}
			} 
			delete theStream;
		}
	}
	LString::CopyPStr(theTitle, outString);

	return (theTitle[0] != 0);
}


// ---------------------------------------------------------------------------
//  AddItem												[public]
// ---------------------------------------------------------------------------

void
CMenuObject::AddItem()
{
	mItems.AddItem( new CMenuItem() );
}


// ---------------------------------------------------------------------------
//  AddItem												[public]
// ---------------------------------------------------------------------------

void
CMenuObject::AddItem(CMenuItem * inItem)
{
	mItems.AddItem(inItem);
}


// ---------------------------------------------------------------------------
//  AddItem												[public]
// ---------------------------------------------------------------------------

void
CMenuObject::AddItem(Str255 inTitle, 
						UInt8 inIconID, 
						UInt8 inShortcut, 
						UInt8 inMark, 
						Style inStyle)
{
	mItems.AddItem( new CMenuItem( inTitle, inIconID, inShortcut,
								  inMark, inStyle) );
}


// ---------------------------------------------------------------------------
//  RemoveItem												[public]
// ---------------------------------------------------------------------------

void
CMenuObject::RemoveItem( ArrayIndexT inAtIndex )
{
	CMenuItem *	theItem;
	if ( mItems.FetchItemAt( inAtIndex, theItem) ) {
		if (theItem != NULL) {
			delete theItem;
		} 
		mItems.RemoveItemsAt(1, inAtIndex);
		SInt32 theCount = CountItems();
		if (mItemIndex > inAtIndex) {
			mItemIndex--;
		} 
		if (mItemIndex > theCount) {
			mItemIndex = theCount;
		} 
	} 
}


// ---------------------------------------------------------------------------
//  InstallData												[public]
// ---------------------------------------------------------------------------

void
CMenuObject::InstallData(LHandleStream * inStream)
{
	UInt8		theUInt8;
	UInt16		theUInt16, theCount = 0;
	CMenuItem *	theItem;
	
	*inStream >> mID;
	*inStream >> theUInt16;  // Placeholder for width
	*inStream >> theUInt16;  // Placeholder for height
	*inStream >> mMDEF;
	*inStream >> theUInt16;  // Filler
	*inStream >> mEnableFlag;
	*inStream >> mTitle;

	// Get the count of Items. Each item record is at least 5 bytes long +
	// the last NULL.
	while (inStream->GetMarker() < inStream->GetLength() - 5) {
		theItem = new CMenuItem(inStream);
		AddItem(theItem);
		theCount++;
	}

	// The last item in the resource should be a NULL (LSTZ list).
	*inStream >> theUInt8;
	if (theUInt8 != 0x00) {
		// Should we signal the error ?
	} 

	// Initialize to 1 if there are Items, 0 otherwise
	mItemIndex = (theCount > 0);
}


// ---------------------------------------------------------------------------
//  SendData												[public]
// ---------------------------------------------------------------------------

void
CMenuObject::SendData(LHandleStream * outStream)
{
	*outStream << mID;
	*outStream << (UInt16) 0;
	*outStream << (UInt16) 0;
	*outStream << mMDEF;
	*outStream << (UInt16) 0;
	*outStream << mEnableFlag;
	*outStream << mTitle;

	// Items data
	TArrayIterator<CMenuItem*> iterator( mItems );
	CMenuItem *	theItem;
	
	while (iterator.Next(theItem)) {
		theItem->SendData(outStream);
	}
	
	// Ending NULL byte (LSTZ list)
	*outStream << (UInt8) 0;
}


// ---------------------------------------------------------------------------
//  GetValues												[public]
// ---------------------------------------------------------------------------

void
CMenuObject::GetValues( ResIDT & outID, ResIDT & outMDEF, 
					   UInt32 & outEnableFlag, Str255 & outTitle)
{
	outID = mID;
	outMDEF = mMDEF;
	outEnableFlag = mEnableFlag;
	LString::CopyPStr(mTitle, outTitle);
}
 

// ---------------------------------------------------------------------------
//  SetValues												[public]
// ---------------------------------------------------------------------------

void
CMenuObject::SetValues(ResIDT inID, ResIDT inMDEF, 
					   UInt32 inEnableFlag, Str255 inTitle)
{
	mID = inID;
	mMDEF = inMDEF;
	mEnableFlag = inEnableFlag;
	LString::CopyPStr(inTitle, mTitle);
}


// ---------------------------------------------------------------------------
//  GetTitle												[public]
// ---------------------------------------------------------------------------

void
CMenuObject::GetTitle(Str255 & outTitle)
{
	LString::CopyPStr(mTitle, outTitle);
}
 

// ---------------------------------------------------------------------------
//  SetTitle												[public]
// ---------------------------------------------------------------------------

void
CMenuObject::SetTitle(Str255 inTitle)
{
	LString::CopyPStr(inTitle, mTitle);
}


// ---------------------------------------------------------------------------
//  NewItem													[public]
// ---------------------------------------------------------------------------
// Returns the new count of Items after addition. This is also the
// index of the new Item.

SInt32
CMenuObject::NewItem()
{	
	AddItem();
	return CountItems();
}
 

// ---------------------------------------------------------------------------
//  NewItem												[public]
// ---------------------------------------------------------------------------

SInt32
CMenuObject::NewItem(TableIndexT inAfterRow)
{
	SInt32 theCount;
	AddItem();
	theCount = mItems.GetCount();
	mItems.MoveItem(theCount, inAfterRow + 1);
	return theCount;
}


// ---------------------------------------------------------------------------
// DeleteItem 													[public]
// ---------------------------------------------------------------------------
// Deletes the Item at current index. Returns the new count of
// Items after deletion.

SInt32
CMenuObject::DeleteItem()
{
	RemoveItem(mItemIndex);
// 	mItemIndex = -1;
	return CountItems();
}
 

// ---------------------------------------------------------------------------
//  GetStyleAtIndex												[public]
// ---------------------------------------------------------------------------

Style
CMenuObject::GetStyleAtIndex( ArrayIndexT inAtIndex )
{
	Style theStyle = 0;
	CMenuItem *	theItem;
	if ( mItems.FetchItemAt( inAtIndex, theItem) ) {
		theStyle = theItem->GetStyle();
	} 
	
	return theStyle;
}
 

// ---------------------------------------------------------------------------
//  SetStyleAtIndex												[public]
// ---------------------------------------------------------------------------

void
CMenuObject::SetStyleAtIndex(Style theStyle, ArrayIndexT inAtIndex )
{
	CMenuItem *	theItem;
	if ( mItems.FetchItemAt( inAtIndex, theItem) ) {
		theItem->SetStyle(theStyle);
	} 
}
 


