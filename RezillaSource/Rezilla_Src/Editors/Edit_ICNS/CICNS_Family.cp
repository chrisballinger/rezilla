// ===========================================================================
// CICNS_Family.cp
// 
//                       Created: 2006-02-23 15:12:16
//             Last modification: 2006-02-25 22:16:43
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================
// The data contained in an icns resource can be (see Icons.h):
// 
// 	    /* The following icon types can only be used as an icon element */
// 	    /* inside a 'icns' icon family */
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
// 	    /* The following icon types can be used as a resource type */
// 	    /* or as an icon element type inside a 'icns' icon family */
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
// 	    /*  Icon Variants */
// 	    /* These can be used as an element of an 'icns' icon family */
// 	    /* or as a parameter to GetIconRefVariant */
// 	    enum {
// 	      kTileIconVariant              = FOUR_CHAR_CODE('tile'),
// 	      kRolloverIconVariant          = FOUR_CHAR_CODE('over'),
// 	      kDropIconVariant              = FOUR_CHAR_CODE('drop'),
// 	      kOpenIconVariant              = FOUR_CHAR_CODE('open'),
// 	      kOpenDropIconVariant          = FOUR_CHAR_CODE('odrp')
// 	    };

#include "CICNS_Family.h"
#include "CICNS_Stream.h"
#include "CICNS_Member.h"
#include "RezillaConstants.h"
#include "UMiscUtils.h"


// ---------------------------------------------------------------------------
//  CICNS_Family												[public]
// ---------------------------------------------------------------------------

CICNS_Family::CICNS_Family()
{
	mIconType = 'icns';
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

CICNS_Family::CICNS_Family(CICNS_Stream * inStream)
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

void
CICNS_Family::AddMember(OSType inType)
{
	mMembers.AddItem( new CICNS_Member(inType) );
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
CICNS_Family::AddMember(OSType inType, SInt32 inSize, Handle inHandle)
{
	mMembers.AddItem( new CICNS_Member(inType, inSize, inHandle) );
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
//  InstallDataStream												[public]
// ---------------------------------------------------------------------------

void
CICNS_Family::InstallDataStream(CICNS_Stream * inStream)
{
	CICNS_Member *	theMember;
	SInt32			theSize;
	
	*inStream >> mIconType;
	
	// Next comes the total size of the resource, including the previous
	// OSType and this SInt32. This must be the same value as
	// inStream->GetLength(). Should we warn if this is not the case or
	// just repair silently?
	*inStream >> theSize;

	while (inStream->GetMarker() < inStream->GetLength()) {
		theMember = new CICNS_Member(inStream);
		AddMember(theMember);
	}
}


// ---------------------------------------------------------------------------
//  SendDataToStream												[public]
// ---------------------------------------------------------------------------

void
CICNS_Family::SendDataToStream(CICNS_Stream * outStream)
{
	TArrayIterator<CICNS_Member*> iterator( mMembers );
	CICNS_Member *	theMember;
	SInt32			theSize = 8;
	
	*outStream << mIconType;
	*outStream << theSize;

	while (iterator.Next(theMember)) {
		theMember->SendDataToStream(outStream);
	}
	
	// Rectify the value of the total size
	if (outStream->GetLength() > 8) {
		outStream->SetMarker(4, streamFrom_Start);
		*outStream << outStream->GetLength();
	} 
}


// ---------------------------------------------------------------------------
//  GetCurrentIndex												[public]
// ---------------------------------------------------------------------------

ArrayIndexT
CICNS_Family::GetCurrentIndex()
{
	return 0;
}
 

// ---------------------------------------------------------------------------
//  SetCurrentIndex												[public]
// ---------------------------------------------------------------------------

void
CICNS_Family::SetCurrentIndex(ArrayIndexT inIndex)
{}
 

// ---------------------------------------------------------------------------
//  AdjustCurrentIndex												[public]
// ---------------------------------------------------------------------------

void
CICNS_Family::AdjustCurrentIndex()
{
	if ( GetCurrentIndex() == 0 ) {
		SetCurrentIndex( (CountMembers() > 0) );
	} else if ( GetCurrentIndex() > CountMembers() ) {
		SetCurrentIndex( CountMembers() );
	} 
}
 

// ---------------------------------------------------------------------------
//	 FindIconForType											 [public]
// ---------------------------------------------------------------------------

CICNS_Member *
CICNS_Family::FindIconForType(OSType inType) const
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



