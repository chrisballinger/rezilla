// ===========================================================================
// CAeteClass.cp
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-01-20 14:48:32
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CAeteClass.h"
#include "CAeteStream.h"
#include "CAeteProperty.h"
#include "CAeteElement.h"


// ---------------------------------------------------------------------------
//  CAeteClass												[public]
// ---------------------------------------------------------------------------

void
CAeteClass::CAeteClass(CAeteStream * inStream)
{
	UInt16	theCount, i;
	OSType	theType;
	Str255	theName, theDescr;
	CAeteProperty *	theProperty;
	CAeteElement *	theElement;
	
	*inStream >> mName;
	inStream->AlignBytes();

	*inStream >> mID;
	
	*inStream >> mDescription;
	inStream->AlignBytes();
	
	// Get the count of properties
	*inStream >> theCount;
	for (i = 0 ; i < theCount; i++) {
		theProperty = new CAeteProperty(inStream);
		AddProperty(theProperty);
	}

	// Get the count of elements
	*inStream >> theCount;
	for (i = 0 ; i < theCount; i++) {
		theElement = new CAeteElement(inStream);
		AddElement(theElement);
	}
}


// ---------------------------------------------------------------------------
//  ~CAeteClass												[public]
// ---------------------------------------------------------------------------

void
CAeteClass::~CAeteClass()
{
}


// ---------------------------------------------------------------------------
//  AddProperty												[public]
// ---------------------------------------------------------------------------

void
CAeteClass::AddProperty( CAeteProperty * inProperty )
{
}


// ---------------------------------------------------------------------------
//  AddProperty												[public]
// ---------------------------------------------------------------------------

void
CAeteClass::AddProperty(Str255	inName,
						ResType	inID, 
						ResType	inType, 
						Str255	inDescription, 
						UInt16	inFlags)
{
}


// ---------------------------------------------------------------------------
//  RemoveProperty												[public]
// ---------------------------------------------------------------------------

void
CAeteClass::RemoveProperty( ArrayIndexT inAtIndex )
{
}


// ---------------------------------------------------------------------------
//  AddElement												[public]
// ---------------------------------------------------------------------------

void
CAeteClass::AddElement( CAeteElement * inElement )
{
}


// ---------------------------------------------------------------------------
//  AddElement												[public]
// ---------------------------------------------------------------------------

void
CAeteClass::AddElement( OSType inKeyForms[] )
{
}


// ---------------------------------------------------------------------------
//  AddElement												[public]
// ---------------------------------------------------------------------------

void
CAeteClass::AddElement()
{
}


// ---------------------------------------------------------------------------
//  RemoveElement												[public]
// ---------------------------------------------------------------------------

void
CAeteClass::RemoveElement( ArrayIndexT inAtIndex )
{
}


// ---------------------------------------------------------------------------
//  InstallDataStream												[public]
// ---------------------------------------------------------------------------

void
CAeteClass::InstallDataStream()
{
}


// ---------------------------------------------------------------------------
//  SendDataToStream												[public]
// ---------------------------------------------------------------------------

void
CAeteClass::SendDataToStream(CAeteStream * outStream)
{
}


