// ===========================================================================
// CAeteSuite.cp
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-01-22 09:35:55
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
	UInt16				theCount, i;
	CAeteEvent *		theEvent;
	CAeteClass *		theClass;
	CAeteCompOp *		theCompOp;
	CAeteEnumeration *	theEnumeration;
	
	*inStream >> mName;
	*inStream >> mDescription;
	inStream->AlignBytes();
	
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

	TArrayIterator<CAeteCompOp*> iteratorCo(mCompOperators, LArrayIterator::from_End);
	CAeteCompOp *	theCompOp;
	while (iteratorCo.Previous(theCompOp)) {
		mCompOperators.RemoveItemsAt(1, iteratorCo.GetCurrentIndex());
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
	mCompOperators.AddItem( new CAeteCompOp() );
}


// ---------------------------------------------------------------------------
//  AddCompOp												[public]
// ---------------------------------------------------------------------------

void
CAeteSuite::AddCompOp(CAeteCompOp * inCompOp)
{
	mCompOperators.AddItem(inCompOp);
}


// ---------------------------------------------------------------------------
//  AddCompOp												[public]
// ---------------------------------------------------------------------------

void
CAeteSuite::AddCompOp(Str255 inName, 
					 OSType inType, 
					 Str255 inDescription)
{
	mCompOperators.AddItem( new CAeteCompOp( inName, inType, inDescription) );
}


// ---------------------------------------------------------------------------
//  RemoveCompOp												[public]
// ---------------------------------------------------------------------------

void
CAeteSuite::RemoveCompOp( ArrayIndexT inAtIndex )
{
	CAeteCompOp *	theCompOp;
	if ( mCompOperators.FetchItemAt( inAtIndex, theCompOp) ) {
		if (theCompOp != NULL) {
			delete theCompOp;
		} 
		mCompOperators.RemoveItemsAt(1, inAtIndex);
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
CAeteSuite::InstallDataStream()
{
}


// ---------------------------------------------------------------------------
//  SendDataToStream												[public]
// ---------------------------------------------------------------------------

void
CAeteSuite::SendDataToStream(CAeteStream * outStream)
{
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

