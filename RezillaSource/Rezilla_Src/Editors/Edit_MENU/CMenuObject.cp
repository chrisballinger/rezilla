// ===========================================================================
// CMenuObject.cp
// 
//                       Created: 2005-03-10 09:12:57
//             Last modification: 2005-03-10 18:56:44
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CMenuObject.h"
#include "CMenuItem.h"
#include "RezillaConstants.h"
#include "UMiscUtils.h"

#include <LHandleStream.h>

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
	InstallDataStream(inStream);
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
	} 
}


// ---------------------------------------------------------------------------
//  InstallDataStream												[public]
// ---------------------------------------------------------------------------

void
CMenuObject::InstallDataStream(LHandleStream * inStream)
{
	UInt16		theUInt16, theCount = 0;
	CMenuItem *	theItem;
	
	*inStream >> mID;
	*inStream >> theUInt16;  // Placeholder for width
	*inStream >> theUInt16;  // Placeholder for height
	*inStream >> mMDEF;
	*inStream >> theUInt16;  // Filler
	*inStream >> mEnableFlag;
	*inStream >> mTitle;

	// Get the count of Items. Each item record is at least 5 bytes long.
	while (inStream->GetMarker() < inStream->GetLength() - 4) {
		theItem = new CMenuItem(inStream);
		AddItem(theItem);
		theCount++;
	}

	// Initialize to 1 if there are Items, 0 otherwise
	mItemIndex = (theCount > 0);
}


// ---------------------------------------------------------------------------
//  SendDataToStream												[public]
// ---------------------------------------------------------------------------

void
CMenuObject::SendDataToStream(LHandleStream * outStream)
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
		theItem->SendDataToStream(outStream);
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
// DeleteItem 													[public]
// ---------------------------------------------------------------------------
// Deletes the Item at current index. Returns the new count of
// Items after deletion.

SInt32
CMenuObject::DeleteItem()
{
	RemoveItem(mItemIndex);
	mItemIndex = -1;
	return CountItems();
}
 


