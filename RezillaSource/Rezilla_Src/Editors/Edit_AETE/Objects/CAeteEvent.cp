// ===========================================================================
// CAeteEvent.cp
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-01-21 07:26:48
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CAeteEvent.h"
#include "CAeteStream.h"
#include "CAeteParameter.h"


// ---------------------------------------------------------------------------
//  CAeteEvent												[public]
// ---------------------------------------------------------------------------

CAeteEvent::CAeteEvent()
{
	mName[0] = 0;
	mDescription[0] = 0;
	mClass = 0;
	mID = 0;
	mFlags = 0;
	mCurrParameterIndex = 0;	
}


// ---------------------------------------------------------------------------
//  CAeteEvent												[public]
// ---------------------------------------------------------------------------

CAeteEvent::CAeteEvent(	Str255	inName,
						Str255	inDescription,
						OSType	inClass, 
						OSType	inID,
						UInt16	inFlags)
{
	LString::CopyPStr(inName, mName);
	LString::CopyPStr(inDescription, mDescription);
	mClass = inClass;
	mID = inID;
	mFlags = inFlags;
	mCurrParameterIndex = 0;	
}


// ---------------------------------------------------------------------------
//  CAeteEvent												[public]
// ---------------------------------------------------------------------------

CAeteEvent::CAeteEvent(CAeteStream * inStream)
{
	UInt16	theCount, i;
	OSType	theType;
	Str255	theName, theDescr;
	CAeteParameter *	theParameter;
	
	*inStream >> mName;
	inStream->AlignBytes();

	*inStream >> mDescription;
	inStream->AlignBytes();
	
	*inStream >> mClass;
	*inStream >> mID;

	*inStream >> mFlags;

	// Get the count of parameters
	*inStream >> theCount;
	for (i = 0 ; i < theCount; i++) {
		theParameter = new CAeteParameter(inStream);
		AddParameter(theParameter);
	}

	// Initialize to 1 if there are parameters, 0 otherwise
	mCurrParameterIndex = (theCount > 0);
}


// ---------------------------------------------------------------------------
//  ~CAeteEvent												[public]
// ---------------------------------------------------------------------------

CAeteEvent::~CAeteEvent()
{
	TArrayIterator<CAeteParameter*> iteraror(mParameters, LArrayIterator::from_End);
	CAeteParameter *	theParam;
	while (iteraror.Previous(theParam)) {
		mParameters.RemoveItemsAt(1, iteraror.GetCurrentIndex());
		delete theParam;
	}
}


// ---------------------------------------------------------------------------
//  AddParameter												[public]
// ---------------------------------------------------------------------------

void
CAeteEvent::AddParameter()
{
	mParameters.AddItem( new CAeteParameter() );
}


// ---------------------------------------------------------------------------
//  AddParameter												[public]
// ---------------------------------------------------------------------------

void
CAeteEvent::AddParameter(CAeteParameter * inParameter)
{
	mParameters.AddItem(inParameter);
}


// ---------------------------------------------------------------------------
//  AddParameter												[public]
// ---------------------------------------------------------------------------

void
CAeteEvent::AddParameter(Str255	inName,
						OSType	inKeyword, 
						OSType	inType, 
						Str255	inDescription, 
						UInt16	inFlags)
{
	mParameters.AddItem( new CAeteParameter( inName, inKeyword, inType,
											inDescription, inFlags) );
}


// ---------------------------------------------------------------------------
//  RemoveParameter												[public]
// ---------------------------------------------------------------------------

void
CAeteEvent::RemoveParameter( ArrayIndexT inAtIndex )
{
	CAeteParameter *	theParameter;
	if ( mParameters.FetchItemAt( inAtIndex, theParameter) ) {
		if (theParameter != NULL) {
			delete theParameter;
		} 
		mParameters.RemoveItemsAt(1, inAtIndex);
	} 
}


// ---------------------------------------------------------------------------
//  InstallDataStream												[public]
// ---------------------------------------------------------------------------

void
CAeteEvent::InstallDataStream()
{
}


// ---------------------------------------------------------------------------
//  SendDataToStream												[public]
// ---------------------------------------------------------------------------

void
CAeteEvent::SendDataToStream(CAeteStream * outStream)
{
}


