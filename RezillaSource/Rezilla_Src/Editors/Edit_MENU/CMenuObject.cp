// ===========================================================================
// CMenuObject.cp
// 
//                       Created: 2005-03-10 09:12:57
//             Last modification: 2005-03-10 09:48:01
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
	mEnabled = false;
}


// ---------------------------------------------------------------------------
//  CMenuObject												[public]
// ---------------------------------------------------------------------------

CMenuObject::CMenuObject(Str255	inTitle,
					   ResIDT	inID,
					   ResIDT	inMDEF,
					   Boolean	inEnabled)
{
	SetValues(inTitle, inID, inMDEF, inEnabled);
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
CMenuObject::AddItem(Str255	inName,
					OSType	inKeyword, 
					OSType	inType, 
					Str255	inDescription, 
					UInt16	inFlags)
{
	mItems.AddItem( new CMenuItem( inName, inKeyword, inType,
											inDescription, inFlags) );
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
	UInt16		theCount, i;
	CMenuItem *	theItem;
	
	*inStream >> mTitle;
	*inStream >> mID;
	*inStream >> mMDEF;
	*inStream >> mEnabled;

	// Get the count of Items
	*inStream >> theCount;
	for (i = 0 ; i < theCount; i++) {
		theItem = new CMenuItem(inStream);
		AddItem(theItem);
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
	*outStream << mTitle;
	*outStream << mID;
	*outStream << mMDEF;
	*outStream << mEnabled;
	
	// Items data
// 	*outStream << (UInt16) mItems.GetCount();

	TArrayIterator<CMenuItem*> iterator( mItems );
	CMenuItem *	theItem;
	
	while (iterator.Next(theItem)) {
		theItem->SendDataToStream(outStream);
	}
}


// ---------------------------------------------------------------------------
//  GetValues												[public]
// ---------------------------------------------------------------------------

void
CMenuObject::GetValues(Str255 & outTitle, ResIDT & outID,
					   ResIDT & outMDEF, Boolean & outEnabled)
{
	LString::CopyPStr(mTitle, outTitle);
	outID = mID;
	outMDEF = mMDEF;
	outEnabled = mEnabled;
}
 

// ---------------------------------------------------------------------------
//  SetValues												[public]
// ---------------------------------------------------------------------------

void
CMenuObject::SetValues(Str255 inTitle, ResIDT inID,
					   ResIDT inMDEF, Boolean inEnabled)
{
	LString::CopyPStr(inTitle, mTitle);
	mID = inID;
	mMDEF = inMDEF;
	mEnabled = inEnabled;
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
 


