// ===========================================================================
// CAeteEnumeration.cp
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-01-26 06:55:45
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

CAeteEnumeration::CAeteEnumeration(OSType inID)
{
	mEnumerationID = inID;
	mEnumeratorIndex = 0;
}


// ---------------------------------------------------------------------------
//  CAeteEnumeration												[public]
// ---------------------------------------------------------------------------

CAeteEnumeration::CAeteEnumeration(CAeteStream * inStream)
{
	InstallDataStream(inStream);
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
CAeteEnumeration::AddEnumerator()
{
	AeteEnumerator	numerator;
	
	numerator.type = 0;
	numerator.name[0] = 0;
	numerator.description[0] = 0;
	
	return ( mEnumerators.AddItem(numerator) );
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
//  GetEnumerator												[public]
// ---------------------------------------------------------------------------

Boolean
CAeteEnumeration::GetEnumerator(ArrayIndexT inAtIndex, AeteEnumerator & outEnumerator)
{
	return mEnumerators.FetchItemAt(inAtIndex, outEnumerator);
}


// ---------------------------------------------------------------------------
//  SetEnumerator												[public]
// ---------------------------------------------------------------------------

void
CAeteEnumeration::SetEnumerator(ArrayIndexT inAtIndex, AeteEnumerator inEnumerator)
{
	RemoveEnumerator(inAtIndex);
	mEnumerators.InsertItemsAt(1, inAtIndex, inEnumerator);
}

	
// ---------------------------------------------------------------------------
//  InstallDataStream												[public]
// ---------------------------------------------------------------------------

void
CAeteEnumeration::InstallDataStream(CAeteStream * inStream)
{
	UInt16	theCount, i;
	OSType	theType;
	Str255	theName, theDescr;
	
	*inStream >> mEnumerationID;
	*inStream >> theCount;
	for (i = 0 ; i < theCount; i++) {
		*inStream >> theName;
		inStream->AlignBytesRead();

		*inStream >> theType;
		
		*inStream >> theDescr;
		inStream->AlignBytesRead();
		
		AddEnumerator(theName, theType, theDescr);
	}

	// Initialize to 1 if there are parameters, 0 otherwise
	mEnumeratorIndex = (theCount > 0);
}


// ---------------------------------------------------------------------------
//  SendDataToStream												[public]
// ---------------------------------------------------------------------------

void
CAeteEnumeration::SendDataToStream(CAeteStream * outStream)
{
	*outStream << mEnumerationID;
	
	// KeyForms data
	*outStream << (UInt16) mEnumerators.GetCount();
	
	TArrayIterator<AeteEnumerator> iterator( mEnumerators );
	AeteEnumerator 	numerator;
	
	while (iterator.Next(numerator)) {
		*outStream << numerator.name;
		outStream->AlignBytesWrite();
		*outStream << numerator.type;
		*outStream << numerator.description;
		outStream->AlignBytesWrite();
	}
	
}


