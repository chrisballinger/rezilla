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
}


// ---------------------------------------------------------------------------
//  AddParameter												[public]
// ---------------------------------------------------------------------------

void
CAeteEvent::AddParameter(CAeteParameter * inParameter)
{
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


