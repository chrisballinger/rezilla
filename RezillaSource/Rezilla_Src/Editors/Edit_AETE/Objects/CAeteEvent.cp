// ===========================================================================
// CAeteEvent.cp
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-01-20 15:01:04
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

void
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
}


// ---------------------------------------------------------------------------
//  ~CAeteEvent												[public]
// ---------------------------------------------------------------------------

void
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
						ResType	inKeyword, 
						ResType	inType, 
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


