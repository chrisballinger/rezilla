// ===========================================================================
// CICNS_Family.cp
// 
//                       Created: 2006-02-23 15:12:16
//             Last modification: 2006-11-09 20:01:53
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================
// The data contained in an icns resource can be (see Icons.h):
// 
// The following icon types can only be used as an icon element inside a
// 'icns' icon family
// 	    enum {
// 	      kThumbnail32BitData           = FOUR_CHAR_CODE('it32'),
// 	      kThumbnail8BitMask            = FOUR_CHAR_CODE('t8mk')
// 	    };
// 
// 	    enum {
// 	      kHuge1BitMask                 = FOUR_CHAR_CODE('ich#'),
// 	      kHuge4BitData                 = FOUR_CHAR_CODE('ich4'),
// 	      kHuge8BitData                 = FOUR_CHAR_CODE('ich8'),
// 	      kHuge32BitData                = FOUR_CHAR_CODE('ih32'),
// 	      kHuge8BitMask                 = FOUR_CHAR_CODE('h8mk')
// 	    };
// 
// The following icon types can be used as a resource type or as an icon
// element type inside a 'icns' icon family
// 	    enum {
// 	      kLarge1BitMask                = FOUR_CHAR_CODE('ICN#'),
// 	      kLarge4BitData                = FOUR_CHAR_CODE('icl4'),
// 	      kLarge8BitData                = FOUR_CHAR_CODE('icl8'),
// 	      kLarge32BitData               = FOUR_CHAR_CODE('il32'),
// 	      kLarge8BitMask                = FOUR_CHAR_CODE('l8mk'),
// 	      kSmall1BitMask                = FOUR_CHAR_CODE('ics#'),
// 	      kSmall4BitData                = FOUR_CHAR_CODE('ics4'),
// 	      kSmall8BitData                = FOUR_CHAR_CODE('ics8'),
// 	      kSmall32BitData               = FOUR_CHAR_CODE('is32'),
// 	      kSmall8BitMask                = FOUR_CHAR_CODE('s8mk'),
// 	      kMini1BitMask                 = FOUR_CHAR_CODE('icm#'),
// 	      kMini4BitData                 = FOUR_CHAR_CODE('icm4'),
// 	      kMini8BitData                 = FOUR_CHAR_CODE('icm8')
// 	    };
// 
// Icon Variants
// These can be used as an element of an 'icns' icon family or as a
// parameter to GetIconRefVariant
// 	    enum {
// 	      kTileIconVariant              = FOUR_CHAR_CODE('tile'),
// 	      kRolloverIconVariant          = FOUR_CHAR_CODE('over'),
// 	      kDropIconVariant              = FOUR_CHAR_CODE('drop'),
// 	      kOpenIconVariant              = FOUR_CHAR_CODE('open'),
// 	      kOpenDropIconVariant          = FOUR_CHAR_CODE('odrp')
// 	    };

#include "CICNS_Family.h"
#include "CICNS_Member.h"
#include "RezillaConstants.h"
#include "UMiscUtils.h"
#include "UMessageDialogs.h"

#include <LHandleStream.h>

// ---------------------------------------------------------------------------
//  CICNS_Family												[public]
// ---------------------------------------------------------------------------

CICNS_Family::CICNS_Family()
{
	mIconType = kIconFamilyType;
}


// ---------------------------------------------------------------------------
//  CICNS_Family												[public]
// ---------------------------------------------------------------------------

CICNS_Family::CICNS_Family(OSType inType)
{
	mIconType = inType;
}


// ---------------------------------------------------------------------------
//  CICNS_Family												[public]
// ---------------------------------------------------------------------------

CICNS_Family::CICNS_Family(LHandleStream * inStream)
{
	InstallDataStream(inStream);
}


// ---------------------------------------------------------------------------
//  ~CICNS_Family												[public]
// ---------------------------------------------------------------------------

CICNS_Family::~CICNS_Family()
{
	TArrayIterator<CICNS_Member*> iteraror(mMembers, LArrayIterator::from_End);
	CICNS_Member *	theMember;
	while (iteraror.Previous(theMember)) {
		mMembers.RemoveItemsAt(1, iteraror.GetCurrentIndex());
		delete theMember;
	}
}


// ---------------------------------------------------------------------------
//  AddMember												[public]
// ---------------------------------------------------------------------------

CICNS_Member *
CICNS_Family::AddMember(OSType inType)
{
	CICNS_Member *	theMember = new CICNS_Member(inType);
	mMembers.AddItem(theMember);
	return theMember;
}


// ---------------------------------------------------------------------------
//  AddMember												[public]
// ---------------------------------------------------------------------------

void
CICNS_Family::AddMember(CICNS_Member * inMember)
{
	mMembers.AddItem(inMember);
}


// ---------------------------------------------------------------------------
//  AddMember												[public]
// ---------------------------------------------------------------------------

void
CICNS_Family::AddMember(OSType inType, Handle inHandle)
{
	mMembers.AddItem( new CICNS_Member(inType, inHandle) );
}


// ---------------------------------------------------------------------------
//  DeleteMember												[public]
// ---------------------------------------------------------------------------

void
CICNS_Family::DeleteMember( ArrayIndexT inAtIndex )
{
	CICNS_Member *	theMember;
	if ( mMembers.FetchItemAt( inAtIndex, theMember) ) {
		if (theMember != NULL) {
			delete theMember;
		} 
		mMembers.RemoveItemsAt(1, inAtIndex);
	} 
}


// ---------------------------------------------------------------------------
//  DeleteMember												[public]
// ---------------------------------------------------------------------------

void
CICNS_Family::DeleteMember(CICNS_Member * inMember)
{
	if (inMember != NULL) {
		ArrayIndexT	index = mMembers.FetchIndexOf(inMember);
		delete inMember;
		mMembers.RemoveItemsAt(1, index);
	} 
}




// ---------------------------------------------------------------------------
//  InstallDataStream												[public]
// ---------------------------------------------------------------------------
// noIconDataAvailableErr = -2582

void
CICNS_Family::InstallDataStream(LHandleStream * inStream)
{
	OSErr				error = noErr;
	CICNS_Member *		theMember;
	SInt32				theSize;
	OSType				theType;
	Handle				theHandle;
	IconFamilyHandle	theIconFamilyHandle = (IconFamilyHandle) inStream->GetDataHandle();

	if ( inStream->GetLength() < 8 ) {
		mIconType = kIconFamilyType;
		return;
	} 
	
	*inStream >> mIconType;
	// Next comes the total size of the resource, including the previous
	// OSType and this SInt32. This must be the same value as
	// inStream->GetLength(). Should we warn if this is not the case or
	// just repair silently?
	*inStream >> theSize;

	while (inStream->GetMarker() < inStream->GetLength()) {		
		*inStream >> theType;
		*inStream >> theSize;
		
		theHandle = NewHandle(0);
		error = GetIconFamilyData( theIconFamilyHandle, theType, theHandle);
		
		theMember = new CICNS_Member(theType, theHandle);
		AddMember(theMember);
		
		inStream->SetMarker(theSize - 8, streamFrom_Marker);
	}
}


// ---------------------------------------------------------------------------
//  RetrieveData												[public]
// ---------------------------------------------------------------------------

OSErr
CICNS_Family::RetrieveData(IconFamilyHandle & outIconFamilyH)
{
	OSErr				error = noErr;
	CICNS_Member *		theMember;
	TArrayIterator<CICNS_Member*> iterator( mMembers );
	UInt32				oldSize, newSize, failures = 0;	

	// Allocate memory for the handle. It will be released in DoSaveChanges().
	outIconFamilyH = (IconFamilyHandle) NewHandle( 8 );
	if (outIconFamilyH == NULL) {
		return memFullErr;
	} 
	
	(**outIconFamilyH).resourceType = kIconFamilyType;
	(**outIconFamilyH).resourceSize = 8;
	oldSize = 8;

	while (iterator.Next(theMember)) {
		error = ::SetIconFamilyData(outIconFamilyH, theMember->GetType(), theMember->GetIconData());
		newSize = (**outIconFamilyH).resourceSize;		
		if (error != noErr) {
			break;
		} 
		if (oldSize == newSize) {
			failures++;
		} else {
			oldSize = newSize;
		}
	}
	if (failures > 0) {
		UMessageDialogs::AlertWithValue(CFSTR("SavingIcnsMembersFailure"), failures);
	} 
	return error;
}


// ---------------------------------------------------------------------------
//	 FindMember											 [public]
// ---------------------------------------------------------------------------

CICNS_Member *
CICNS_Family::FindMember(OSType inType) const
{
	TArrayIterator<CICNS_Member*> iterator( mMembers );
	CICNS_Member	*theMember = NULL, *currMember;
	
	while (iterator.Next(currMember)) {
		if (currMember->GetType() == inType) {
			theMember = currMember;
			break;
		} 
	}
	
	return theMember;
}



