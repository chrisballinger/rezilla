// ===========================================================================
// CAeteEnumeration.cp
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-01-21 06:32:01
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CAeteEnumeration.h"
#include "CAeteStream.h"


// ---------------------------------------------------------------------------
//  CAeteEnumeration												[public]
// ---------------------------------------------------------------------------

CAeteEnumeration::CAeteEnumeration(CAeteStream * inStream)
{
	UInt16	theCount, i;
	OSType	theType;
	Str255	theName, theDescr;
	
	*inStream >> mEnumerationID;
	*inStream >> theCount;
	for (i = 0 ; i < theCount; i++) {
		*inStream >> theName;
		inStream->AlignBytes();

		*inStream >> theType;
		
		*inStream >> theDescr;
		inStream->AlignBytes();
		
		AddEnumerator(theName, theType, theDescr);
	}

	// Initialize to 1 if there are parameters, 0 otherwise
	mCurrEnumeratorIndex = (theCount > 0);
}


// ---------------------------------------------------------------------------
//  ~CAeteEnumeration												[public]
// ---------------------------------------------------------------------------

CAeteEnumeration::~CAeteEnumeration()
{
}


// ---------------------------------------------------------------------------
//  AddEnumerator												[public]
// ---------------------------------------------------------------------------

ArrayIndexT
CAeteEnumeration::AddEnumerator(Str255 inName, OSType inType, Str255 inDescription)
{
	AeteEnumerator	numerator;
	
	numerator.type = inType;
	LString::CopyPStr(inName, numerator.name);
	LString::CopyPStr(inDescription, numerator.description);
	
	return ( mEnumerators.AddItem(numerator) );
}


// ---------------------------------------------------------------------------
//  RemoveEnumerator												[public]
// ---------------------------------------------------------------------------

void
CAeteEnumeration::RemoveEnumerator( ArrayIndexT inAtIndex )
{
	mEnumerators.RemoveItemsAt(1, inAtIndex);
}


// ---------------------------------------------------------------------------
//  InstallDataStream												[public]
// ---------------------------------------------------------------------------

void
CAeteEnumeration::InstallDataStream()
{
}


// ---------------------------------------------------------------------------
//  SendDataToStream												[public]
// ---------------------------------------------------------------------------

void
CAeteEnumeration::SendDataToStream(CAeteStream * outStream)
{
}


