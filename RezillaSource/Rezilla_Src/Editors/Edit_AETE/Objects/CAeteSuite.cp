// ===========================================================================
// CAeteSuite.cp
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-01-21 06:58:53
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
	mCurrEventIndex = (theCount > 0);

	// Get the count of classes
	*inStream >> theCount;
	for (i = 0 ; i < theCount; i++) {
		theClass = new CAeteClass(inStream);
		AddClass(theClass);
	}
	mCurrClassIndex = (theCount > 0);

	// Get the count of comparison operators
	*inStream >> theCount;
	for (i = 0 ; i < theCount; i++) {
		theCompOp = new CAeteCompOp(inStream);
		AddCompOp(theCompOp);
	}
	mCurrCompOpIndex = (theCount > 0);

	// Get the count of enumerations
	*inStream >> theCount;
	for (i = 0 ; i < theCount; i++) {
		theEnumeration = new CAeteEnumeration(inStream);
		AddEnumeration(theEnumeration);
	}
	mCurrEnumerationIndex = (theCount > 0);

}


// ---------------------------------------------------------------------------
//  ~CAeteSuite												[public]
// ---------------------------------------------------------------------------

CAeteSuite::~CAeteSuite()
{
}


// ---------------------------------------------------------------------------
//  AddEvent												[public]
// ---------------------------------------------------------------------------

void
CAeteSuite::AddEvent(CAeteEvent * inEvent)
{
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
CAeteSuite::AddClass(CAeteClass * inClass)
{
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
CAeteSuite::AddCompOp(CAeteCompOp * inCompOp)
{
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
CAeteSuite::AddEnumeration(CAeteEnumeration * inEnum)
{
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


