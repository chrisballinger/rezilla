// ===========================================================================
// CAeteSuite.cp
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-02-04 06:06:20
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CAeteSuite.h"
#include "CAeteStream.h"
#include "CAeteEvent.h"
#include "CAeteClass.h"
#include "CAeteCompOp.h"
#include "CAeteEnumeration.h"
#include "RezillaConstants.h"
#include "UMiscUtils.h"


// ---------------------------------------------------------------------------
//  CAeteSuite												[public]
// ---------------------------------------------------------------------------

CAeteSuite::CAeteSuite()
{
	mName[0] = 0;
	mDescription[0] = 0;
	mID = 0;
	mLevel = 0;
	mVersion = 0;
	mEventIndex = 0;
	mClassIndex = 0;
	mCompOpIndex = 0;
	mEnumerationIndex = 0;
}


// ---------------------------------------------------------------------------
//  CAeteSuite												[public]
// ---------------------------------------------------------------------------

CAeteSuite::CAeteSuite(Str255	inName,
					 Str255	inDescription,
					 OSType	inID, 
					 UInt16	inLevel,
					 UInt16	inVersion)
{
	SetValues( inName, inDescription, inID, inLevel, inVersion);
	mEventIndex = 0;
	mClassIndex = 0;
	mCompOpIndex = 0;
	mEnumerationIndex = 0;
}


// ---------------------------------------------------------------------------
//  CAeteSuite												[public]
// ---------------------------------------------------------------------------

CAeteSuite::CAeteSuite(CAeteStream * inStream)
{
	InstallDataStream(inStream);
}


// ---------------------------------------------------------------------------
//  ~CAeteSuite												[public]
// ---------------------------------------------------------------------------

CAeteSuite::~CAeteSuite()
{
	TArrayIterator<CAeteEvent*> iterarorEv(mEvents, LArrayIterator::from_End);
	CAeteEvent *	theEvent;
	while (iterarorEv.Previous(theEvent)) {
		mEvents.RemoveItemsAt(1, iterarorEv.GetCurrentIndex());
		delete theEvent;
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
//  AddEvent												[public]
// ---------------------------------------------------------------------------

void
CAeteSuite::AddEvent()
{
	mEvents.AddItem( new CAeteEvent() );
}


// ---------------------------------------------------------------------------
//  AddEvent												[public]
// ---------------------------------------------------------------------------

void
CAeteSuite::AddEvent(CAeteEvent * inEvent)
{
	mEvents.AddItem(inEvent);
}


// ---------------------------------------------------------------------------
//  AddEvent												[public]
// ---------------------------------------------------------------------------

void
CAeteSuite::AddEvent(
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
	mEvents.AddItem( new CAeteEvent( inName, inDescription, inClass, inID,
									inReplyType, inReplyDescription, inReplyFlags, 
									inDirectType, inDirectDescription, inDirectFlags) );
}


// ---------------------------------------------------------------------------
//  AddEvent												[public]
// ---------------------------------------------------------------------------

void
CAeteSuite::AddEvent(CFXMLTreeRef inTreeNode)
{
	CAeteEvent * theEvent = new CAeteEvent();
	mEvents.AddItem(theEvent);
	theEvent->GetDataFromXml(inTreeNode);
}


// ---------------------------------------------------------------------------
//  RemoveEvent												[public]
// ---------------------------------------------------------------------------

void
CAeteSuite::RemoveEvent( ArrayIndexT inAtIndex )
{
	CAeteEvent *	theEvent;
	if ( mEvents.FetchItemAt( inAtIndex, theEvent) ) {
		if (theEvent != NULL) {
			delete theEvent;
		} 
		mEvents.RemoveItemsAt(1, inAtIndex);
	} 
}


// ---------------------------------------------------------------------------
//  AddClass												[public]
// ---------------------------------------------------------------------------

void
CAeteSuite::AddClass()
{
	mClasses.AddItem( new CAeteClass() );
}


// ---------------------------------------------------------------------------
//  AddClass												[public]
// ---------------------------------------------------------------------------

void
CAeteSuite::AddClass(CAeteClass * inClass)
{
	mClasses.AddItem(inClass);
}


// ---------------------------------------------------------------------------
//  AddClass												[public]
// ---------------------------------------------------------------------------

void
CAeteSuite::AddClass(Str255	inName,
							OSType	inID,
							Str255	inDescription)
{
	mClasses.AddItem( new CAeteClass( inName, inID, inDescription) );
}


// ---------------------------------------------------------------------------
//  AddClass												[public]
// ---------------------------------------------------------------------------

void
CAeteSuite::AddClass(CFXMLTreeRef inTreeNode)
{
	CAeteClass * theClass = new CAeteClass();
	mClasses.AddItem(theClass);
	theClass->GetDataFromXml(inTreeNode);
}


// ---------------------------------------------------------------------------
//  RemoveClass												[public]
// ---------------------------------------------------------------------------

void
CAeteSuite::RemoveClass( ArrayIndexT inAtIndex )
{
	CAeteClass *	theClass;
	if ( mClasses.FetchItemAt( inAtIndex, theClass) ) {
		if (theClass != NULL) {
			delete theClass;
		} 
		mClasses.RemoveItemsAt(1, inAtIndex);
	} 
}


// ---------------------------------------------------------------------------
//  AddCompOp												[public]
// ---------------------------------------------------------------------------

void
CAeteSuite::AddCompOp()
{
	mCompOps.AddItem( new CAeteCompOp() );
}


// ---------------------------------------------------------------------------
//  AddCompOp												[public]
// ---------------------------------------------------------------------------

void
CAeteSuite::AddCompOp(CAeteCompOp * inCompOp)
{
	mCompOps.AddItem(inCompOp);
}


// ---------------------------------------------------------------------------
//  AddCompOp												[public]
// ---------------------------------------------------------------------------

void
CAeteSuite::AddCompOp(Str255 inName, 
					 OSType inType, 
					 Str255 inDescription)
{
	mCompOps.AddItem( new CAeteCompOp( inName, inType, inDescription) );
}


// ---------------------------------------------------------------------------
//  AddCompOp												[public]
// ---------------------------------------------------------------------------

void
CAeteSuite::AddCompOp(CFXMLTreeRef inTreeNode)
{
	CAeteCompOp * theCompOp = new CAeteCompOp();
	mCompOps.AddItem(theCompOp);
	theCompOp->GetDataFromXml(inTreeNode);
}


// ---------------------------------------------------------------------------
//  RemoveCompOp												[public]
// ---------------------------------------------------------------------------

void
CAeteSuite::RemoveCompOp( ArrayIndexT inAtIndex )
{
	CAeteCompOp *	theCompOp;
	if ( mCompOps.FetchItemAt( inAtIndex, theCompOp) ) {
		if (theCompOp != NULL) {
			delete theCompOp;
		} 
		mCompOps.RemoveItemsAt(1, inAtIndex);
	} 
}


// ---------------------------------------------------------------------------
//  AddEnumeration												[public]
// ---------------------------------------------------------------------------

void
CAeteSuite::AddEnumeration()
{
	mEnumerations.AddItem( new CAeteEnumeration() );
}


// ---------------------------------------------------------------------------
//  AddEnumeration												[public]
// ---------------------------------------------------------------------------

void
CAeteSuite::AddEnumeration(CAeteEnumeration * inEnum)
{
	mEnumerations.AddItem(inEnum);
}


// ---------------------------------------------------------------------------
//  AddEnumeration												[public]
// ---------------------------------------------------------------------------

void
CAeteSuite::AddEnumeration(OSType inID)
{
	mEnumerations.AddItem( new CAeteEnumeration(inID) );
}


// ---------------------------------------------------------------------------
//  AddEnumeration												[public]
// ---------------------------------------------------------------------------

void
CAeteSuite::AddEnumeration(CFXMLTreeRef inTreeNode)
{
	CAeteEnumeration * theEnum = new CAeteEnumeration();
	mEnumerations.AddItem(theEnum);
	theEnum->GetDataFromXml(inTreeNode);
}


// ---------------------------------------------------------------------------
//  RemoveEnumeration												[public]
// ---------------------------------------------------------------------------

void
CAeteSuite::RemoveEnumeration( ArrayIndexT inAtIndex )
{
	CAeteEnumeration *	theEnumeration;
	if ( mEnumerations.FetchItemAt( inAtIndex, theEnumeration) ) {
		if (theEnumeration != NULL) {
			delete theEnumeration;
		} 
		mEnumerations.RemoveItemsAt(1, inAtIndex);
	} 
}


// ---------------------------------------------------------------------------
//  InstallDataStream												[public]
// ---------------------------------------------------------------------------

void
CAeteSuite::InstallDataStream(CAeteStream * inStream)
{
	UInt16				theCount, i;
	CAeteEvent *		theEvent;
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
		theEvent = new CAeteEvent(inStream);
		AddEvent(theEvent);
	}
	mEventIndex = (theCount > 0);

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
CAeteSuite::SendDataToStream(CAeteStream * outStream)
{
	*outStream << mName;
	*outStream << mDescription;
	outStream->AlignBytesWrite();
	
	*outStream << mID;
	*outStream << mLevel;
	*outStream << mVersion;
	
	// Events data
	*outStream << (UInt16) mEvents.GetCount();

	TArrayIterator<CAeteEvent*> iterEv( mEvents );
	CAeteEvent *	theEvent;
	
	while (iterEv.Next(theEvent)) {
		theEvent->SendDataToStream(outStream);
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
//	¥ GetName											[public, virtual]
// ---------------------------------------------------------------------------

StringPtr
CAeteSuite::GetName(
	Str255	outName ) const
{
	return LString::CopyPStr( mName, outName);
}


// ---------------------------------------------------------------------------
//  GetValues												[public]
// ---------------------------------------------------------------------------

void
CAeteSuite::GetValues(Str255 outName, Str255 outDescription, OSType & outID, 
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
CAeteSuite::SetValues(Str255 inName, Str255 inDescription, OSType inID, 
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
CAeteSuite::GetCurrentIndex(SInt8 inKind)
{
	ArrayIndexT index = LArray::index_Bad;
	
	switch (inKind) {
		case kind_AeteEvent:
		index = this->GetEventIndex();
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
CAeteSuite::SetCurrentIndex(SInt8 inKind, ArrayIndexT inIndex)
{
	switch (inKind) {
		case kind_AeteEvent:
		this->SetEventIndex(inIndex);
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
CAeteSuite::GetCurrentCount(SInt8 inKind)
{
	SInt32 count = 0;
	
	switch (inKind) {
		case kind_AeteEvent:
		count = this->CountEvents();
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
//  NewItem															[public]
// ---------------------------------------------------------------------------
// Returns the new count of items after addition. This is also the index 
// of the new item.

SInt32
CAeteSuite::NewItem(SInt8 inKind)
{	
	switch (inKind) {
		case kind_AeteEvent:
		AddEvent();
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
CAeteSuite::DeleteItem(SInt8 inKind)
{
	SInt32 count = 0;
	
	switch (inKind) {
		case kind_AeteEvent:
		RemoveEvent(mEventIndex);
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
CAeteSuite::GetDataFromXml(CFXMLTreeRef inTreeNode)
{
	OSErr			error = noErr;
	int             childCount, subCount;
	CFXMLTreeRef    xmlTree, subTree;
	CFXMLNodeRef    xmlNode, subNode;
	int             index, subIndex;
	SInt32			theLong;
	
	childCount = CFTreeGetChildCount(inTreeNode);
	for (index = 0; index < childCount; index++) {
		xmlTree = CFTreeGetChildAtIndex(inTreeNode, index);
		xmlNode = CFXMLTreeGetNode(xmlTree);

		if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("SuiteName"), 0) ) {
			UMiscUtils::GetStringFromXml(xmlTree, mName);
		} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("SuiteDescription"), 0) ) {
			UMiscUtils::GetStringFromXml(xmlTree, mDescription);
		} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("SuiteID"), 0) ) {
			UMiscUtils::GetOSTypeFromXml(xmlTree, mID);
		} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("SuiteLevel"), 0) ) {
			UMiscUtils::GetValueFromXml(xmlTree, theLong);
			mLevel = theLong;
		}  else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("SuiteVersion"), 0) ) {
			UMiscUtils::GetValueFromXml(xmlTree, theLong);
			mVersion = theLong;
		} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("ArrayEvents"), 0) ) {
			subCount = CFTreeGetChildCount(xmlTree);
			for (subIndex = 0; subIndex < subCount; subIndex++) {
				subTree = CFTreeGetChildAtIndex(xmlTree, subIndex);
				subNode = CFXMLTreeGetNode(subTree);
				if ( ! CFStringCompare( CFXMLNodeGetString(subNode), CFSTR("Event"), 0) ) {
					AddEvent(subTree);
				}
			}
		} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("ArrayClasses"), 0) ) {
			subCount = CFTreeGetChildCount(xmlTree);
			for (subIndex = 0; subIndex < subCount; subIndex++) {
				subTree = CFTreeGetChildAtIndex(xmlTree, subIndex);
				subNode = CFXMLTreeGetNode(subTree);
				if ( ! CFStringCompare( CFXMLNodeGetString(subNode), CFSTR("Class"), 0) ) {
					AddClass(subTree);
				}
			}
		} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("ArrayComparisonOps"), 0) ) {
			subCount = CFTreeGetChildCount(xmlTree);
			for (subIndex = 0; subIndex < subCount; subIndex++) {
				subTree = CFTreeGetChildAtIndex(xmlTree, subIndex);
				subNode = CFXMLTreeGetNode(subTree);
				if ( ! CFStringCompare( CFXMLNodeGetString(subNode), CFSTR("ComparisonOp"), 0) ) {
					AddCompOp(subTree);
				}
			}
		} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("ArrayEnumerations"), 0) ) {
			subCount = CFTreeGetChildCount(xmlTree);
			for (subIndex = 0; subIndex < subCount; subIndex++) {
				subTree = CFTreeGetChildAtIndex(xmlTree, subIndex);
				subNode = CFXMLTreeGetNode(subTree);
				if ( ! CFStringCompare( CFXMLNodeGetString(subNode), CFSTR("Enumeration"), 0) ) {
					AddEnumeration(subTree);
				}
			}
		} 



	}
	
	return error;
}


