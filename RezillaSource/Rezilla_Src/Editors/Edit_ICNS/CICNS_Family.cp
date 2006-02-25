// ===========================================================================
// CICNS_Family.cp
// 
//                       Created: 2006-02-23 15:12:16
//             Last modification: 2006-02-23 15:12:20
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
	mName[0] = 0;
	mDescription[0] = 0;
	mID = 0;
	mLevel = 0;
	mVersion = 0;
	mMemberIndex = 0;
	mClassIndex = 0;
	mCompOpIndex = 0;
	mEnumerationIndex = 0;
}


// ---------------------------------------------------------------------------
//  CICNS_Family												[public]
// ---------------------------------------------------------------------------

CICNS_Family::CICNS_Family(Str255	inName,
					 Str255	inDescription,
					 OSType	inID, 
					 UInt16	inLevel,
					 UInt16	inVersion)
{
	SetValues( inName, inDescription, inID, inLevel, inVersion);
	mMemberIndex = 0;
	mClassIndex = 0;
	mCompOpIndex = 0;
	mEnumerationIndex = 0;
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
	TArrayIterator<CICNS_Member*> iterarorEv(mMembers, LArrayIterator::from_End);
	CICNS_Member *	theMember;
	while (iterarorEv.Previous(theMember)) {
		mMembers.RemoveItemsAt(1, iterarorEv.GetCurrentIndex());
		delete theMember;
	}

	TArrayIterator<CAeteClass*> iteratorCl(mClasses, LArrayIterator::from_End);
	CAeteClass *	theClass;
	while (iteratorCl.Previous(theClass)) {
		mClasses.RemoveItemsAt(1, iteratorCl.GetCurrentIndex());
		delete theClass;
	}

	TArrayIterator<CAeteCompOp*> iteratorCo(mCompOps, LArrayIterator::from_End);
	CAeteCompOp *	theCompOp;
	while (iteratorCo.Previous(theCompOp)) {
		mCompOps.RemoveItemsAt(1, iteratorCo.GetCurrentIndex());
		delete theCompOp;
	}

	TArrayIterator<CAeteEnumeration*> iteratorEn(mEnumerations, LArrayIterator::from_End);
	CAeteEnumeration *	theEnum;
	while (iteratorEn.Previous(theEnum)) {
		mEnumerations.RemoveItemsAt(1, iteratorEn.GetCurrentIndex());
		delete theEnum;
	}
}


// ---------------------------------------------------------------------------
//  AddMember												[public]
// ---------------------------------------------------------------------------

void
CICNS_Family::AddMember()
{
	mMembers.AddItem( new CICNS_Member() );
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
CICNS_Family::AddMember(
				   Str255	inName,
				   Str255	inDescription,
				   OSType	inClass, 
				   OSType	inID,
				   OSType	inReplyType,
				   Str255	inReplyDescription,
				   UInt16	inReplyFlags,
				   OSType	inDirectType,
				   Str255	inDirectDescription,
				   UInt16	inDirectFlags)
{
	mMembers.AddItem( new CICNS_Member( inName, inDescription, inClass, inID,
									inReplyType, inReplyDescription, inReplyFlags, 
									inDirectType, inDirectDescription, inDirectFlags) );
}


// ---------------------------------------------------------------------------
//  AddMember												[public]
// ---------------------------------------------------------------------------

OSErr
CICNS_Family::AddMember(CFXMLTreeRef inTreeNode)
{
	OSErr	error = noErr;
	CICNS_Member * theMember = new CICNS_Member();
	mMembers.AddItem(theMember);
	error = theMember->GetDataFromXml(inTreeNode);
	return error;
}


// ---------------------------------------------------------------------------
//  RemoveMember												[public]
// ---------------------------------------------------------------------------

void
CICNS_Family::RemoveMember( ArrayIndexT inAtIndex )
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
	UInt16				theCount, i;
	CICNS_Member *		theMember;
	CAeteClass *		theClass;
	CAeteCompOp *		theCompOp;
	CAeteEnumeration *	theEnumeration;
	
	*inStream >> mName;
	*inStream >> mDescription;
	inStream->AlignBytesRead();
	
	*inStream >> mID;
	*inStream >> mLevel;
	*inStream >> mVersion;
	
	// Get the count of events
	*inStream >> theCount;
	for (i = 0 ; i < theCount; i++) {
		theMember = new CICNS_Member(inStream);
		AddMember(theMember);
	}
	mMemberIndex = (theCount > 0);

	// Get the count of classes
	*inStream >> theCount;
	for (i = 0 ; i < theCount; i++) {
		theClass = new CAeteClass(inStream);
		AddClass(theClass);
	}
	mClassIndex = (theCount > 0);

	// Get the count of comparison operators
	*inStream >> theCount;
	for (i = 0 ; i < theCount; i++) {
		theCompOp = new CAeteCompOp(inStream);
		AddCompOp(theCompOp);
	}
	mCompOpIndex = (theCount > 0);

	// Get the count of enumerations
	*inStream >> theCount;
	for (i = 0 ; i < theCount; i++) {
		theEnumeration = new CAeteEnumeration(inStream);
		AddEnumeration(theEnumeration);
	}
	mEnumerationIndex = (theCount > 0);
}


// ---------------------------------------------------------------------------
//  SendDataToStream												[public]
// ---------------------------------------------------------------------------

void
CICNS_Family::SendDataToStream(CICNS_Stream * outStream)
{
	*outStream << mName;
	*outStream << mDescription;
	outStream->AlignBytesWrite();
	
	*outStream << mID;
	*outStream << mLevel;
	*outStream << mVersion;
	
	// Members data
	*outStream << (UInt16) mMembers.GetCount();

	TArrayIterator<CICNS_Member*> iterEv( mMembers );
	CICNS_Member *	theMember;
	
	while (iterEv.Next(theMember)) {
		theMember->SendDataToStream(outStream);
	}

	// Classes data
	*outStream << (UInt16) mClasses.GetCount();

	TArrayIterator<CAeteClass*> iterCl( mClasses );
	CAeteClass *	theClass;
	
	while (iterCl.Next(theClass)) {
		theClass->SendDataToStream(outStream);
	}

	// CompOps data
	*outStream << (UInt16) mCompOps.GetCount();

	TArrayIterator<CAeteCompOp*> iterCo( mCompOps );
	CAeteCompOp *	theCompOp;
	
	while (iterCo.Next(theCompOp)) {
		theCompOp->SendDataToStream(outStream);
	}

	// Enumerations data
	*outStream << (UInt16) mEnumerations.GetCount();

	TArrayIterator<CAeteEnumeration*> iterEn( mEnumerations );
	CAeteEnumeration *	theEnumeration;
	
	while (iterEn.Next(theEnumeration)) {
		theEnumeration->SendDataToStream(outStream);
	}
}


// ---------------------------------------------------------------------------
//   GetName											[public, virtual]
// ---------------------------------------------------------------------------

StringPtr
CICNS_Family::GetName(
	Str255	outName ) const
{
	return LString::CopyPStr( mName, outName);
}


// ---------------------------------------------------------------------------
//  GetValues												[public]
// ---------------------------------------------------------------------------

void
CICNS_Family::GetValues(Str255 outName, Str255 outDescription, OSType & outID, 
							  UInt16 & outLevel, UInt16 & outVersion)
{
	LString::CopyPStr(mName, outName);
	LString::CopyPStr(mDescription, outDescription);
	outID = mID;
	outLevel = mLevel;
	outVersion = mVersion;
}
 

// ---------------------------------------------------------------------------
//  SetValues												[public]
// ---------------------------------------------------------------------------

void
CICNS_Family::SetValues(Str255 inName, Str255 inDescription, OSType inID, 
							  UInt16 inLevel, UInt16 inVersion)
{
	LString::CopyPStr(inName, mName);
	LString::CopyPStr(inDescription, mDescription);
	mID = inID;
	mLevel = inLevel;
	mVersion = inVersion;
}


// ---------------------------------------------------------------------------
//  GetCurrentIndex												[public]
// ---------------------------------------------------------------------------

ArrayIndexT
CICNS_Family::GetCurrentIndex(SInt8 inKind)
{
	ArrayIndexT index = LArray::index_Bad;
	
	switch (inKind) {
		case kind_AeteMember:
		index = this->GetMemberIndex();
		break;
		
		case kind_AeteClass:
		index = this->GetClassIndex();
		break;
		
		case kind_AeteCompOp:
		index = this->GetCompOpIndex();
		break;
		
		case kind_AeteEnum:
		index = this->GetEnumerationIndex();
		break;
	}	
	return index;
}
 

// ---------------------------------------------------------------------------
//  SetCurrentIndex												[public]
// ---------------------------------------------------------------------------

void
CICNS_Family::SetCurrentIndex(SInt8 inKind, ArrayIndexT inIndex)
{
	switch (inKind) {
		case kind_AeteMember:
		this->SetMemberIndex(inIndex);
		break;
		
		case kind_AeteClass:
		this->SetClassIndex(inIndex);
		break;
		
		case kind_AeteCompOp:
		this->SetCompOpIndex(inIndex);
		break;
		
		case kind_AeteEnum:
		this->SetEnumerationIndex(inIndex);
		break;
	}	
}
 

// ---------------------------------------------------------------------------
//  GetCurrentCount												[public]
// ---------------------------------------------------------------------------

SInt32
CICNS_Family::GetCurrentCount(SInt8 inKind)
{
	SInt32 count = 0;
	
	switch (inKind) {
		case kind_AeteMember:
		count = this->CountMembers();
		break;
		
		case kind_AeteClass:
		count = this->CountClasses();
		break;
		
		case kind_AeteCompOp:
		count = this->CountCompOps();
		break;
		
		case kind_AeteEnum:
		count = this->CountEnumerations();
		break;
	}	
	return count;
}
 

// ---------------------------------------------------------------------------
//  AdjustCurrentIndex												[public]
// ---------------------------------------------------------------------------

void
CICNS_Family::AdjustCurrentIndex(SInt8 inKind)
{
	if ( GetCurrentIndex(inKind) == 0 ) {
		SetCurrentIndex(inKind, (GetCurrentCount(inKind) > 0));
	} else if ( GetCurrentIndex(inKind) > GetCurrentCount(inKind) ) {
		SetCurrentIndex(inKind, GetCurrentCount(inKind));
	} 
}
 

// ---------------------------------------------------------------------------
//  NewItem															[public]
// ---------------------------------------------------------------------------
// Returns the new count of items after addition. This is also the index 
// of the new item.

SInt32
CICNS_Family::NewItem(SInt8 inKind)
{	
	switch (inKind) {
		case kind_AeteMember:
		AddMember();
		break;
		
		case kind_AeteClass:
		AddClass();
		break;
		
		case kind_AeteCompOp:
		AddCompOp();
		break;
		
		case kind_AeteEnum:
		AddEnumeration();
		break;
	}
	
	return GetCurrentCount(inKind);
}
 

// ---------------------------------------------------------------------------
// DeleteItem 														[public]
// ---------------------------------------------------------------------------
// Deletes the item at current index. Returns the new count of items after
// deletion.

SInt32
CICNS_Family::DeleteItem(SInt8 inKind)
{
	SInt32 count = 0;
	
	switch (inKind) {
		case kind_AeteMember:
		RemoveMember(mMemberIndex);
		break;
		
		case kind_AeteClass:
		RemoveClass(mClassIndex);
		break;
		
		case kind_AeteCompOp:
		RemoveCompOp(mCompOpIndex);
		break;
		
		case kind_AeteEnum:
		RemoveEnumeration(mEnumerationIndex);
		break;
	}	
	
	SetCurrentIndex(inKind, -1);
	return GetCurrentCount(inKind);
}
 

// ---------------------------------------------------------------------------
//  GetDataFromXml												[public]
// ---------------------------------------------------------------------------

OSErr
CICNS_Family::GetDataFromXml(CFXMLTreeRef inTreeNode)
{
	OSErr			error = noErr;
	int             childCount;
	CFXMLTreeRef    xmlTree;
	CFXMLNodeRef    xmlNode;
	int             index;
	SInt32			theLong;
	Boolean			gotArrayMembers = false, 
					gotArrayClasses = false, 
					gotArrayCompOps = false, 
					gotArrayEnums = false;
	
	childCount = CFTreeGetChildCount(inTreeNode);
	for (index = 0; index < childCount; index++) {
		xmlTree = CFTreeGetChildAtIndex(inTreeNode, index);
		if (xmlTree) {
			xmlNode = CFXMLTreeGetNode(xmlTree);
			if (xmlNode) {
				if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("SuiteName"), 0) ) {
					UMiscUtils::GetStringFromXml(xmlTree, mName);
				} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("SuiteDescription"), 0) ) {
					UMiscUtils::GetStringFromXml(xmlTree, mDescription);
				} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("SuiteID"), 0) ) {
					error = UMiscUtils::GetOSTypeFromXml(xmlTree, mID);
				} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("SuiteLevel"), 0) ) {
					UMiscUtils::GetValueFromXml(xmlTree, theLong);
					mLevel = theLong;
				}  else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("SuiteVersion"), 0) ) {
					UMiscUtils::GetValueFromXml(xmlTree, theLong);
					mVersion = theLong;
				} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("ArrayMembers"), 0) ) {
					error = GetArrayFromXml(xmlTree, kind_AeteMember);
				} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("ArrayClasses"), 0) ) {
					error = GetArrayFromXml(xmlTree, kind_AeteClass);
				} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("ArrayComparisonOps"), 0) ) {
					error = GetArrayFromXml(xmlTree, kind_AeteCompOp);
				} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("ArrayEnumerations"), 0) ) {
					error = GetArrayFromXml(xmlTree, kind_AeteEnum);
				} else {
					CFShow(CFXMLNodeGetString(xmlNode));
					error = err_ImportUnknownAeteSuiteTag;	
				}
				
				if (error != noErr) { break; } 
			} 
		} 
	}

	return error;
}


// ---------------------------------------------------------------------------
//  GetArrayFromXml												[public]
// ---------------------------------------------------------------------------

OSErr
CICNS_Family::GetArrayFromXml(CFXMLTreeRef inTreeRef, SInt8 inKind)
{
	OSErr			error = noErr;
	int             childCount;
	CFXMLTreeRef    xmlTree;
	CFXMLNodeRef    xmlNode;
	int             index;

	childCount = CFTreeGetChildCount(inTreeRef);
	for (index = 0; index < childCount; index++) {
		xmlTree = CFTreeGetChildAtIndex(inTreeRef, index);
		if (xmlTree) {
			xmlNode = CFXMLTreeGetNode(xmlTree);
			if (xmlNode) {
				switch (inKind) {
					case kind_AeteMember:
					if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("Member"), 0) ) {
						error = AddMember(xmlTree);
					}
					break;
					
					case kind_AeteClass:
					if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("Class"), 0) ) {
						error = AddClass(xmlTree);
					}
					break;
					
					case kind_AeteCompOp:
					if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("ComparisonOp"), 0) ) {
						error = AddCompOp(xmlTree);
					}
					break;
					
					case kind_AeteEnum:
					if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("Enumeration"), 0) ) {
						error = AddEnumeration(xmlTree);
					}
					break;
				}	
			} 			
		} 
		if (error != noErr) { break; } 
	}
	AdjustCurrentIndex(inKind);

	return error;
}


