// ===========================================================================
// CAeteClass.cp
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-01-21 07:27:26
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

CAeteClass::CAeteClass(CAeteStream * inStream)
{
	UInt16	theCount, i;
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
	// Initialize to 1 if there are parameters, 0 otherwise
	mCurrPropertyIndex = (theCount > 0);

	// Get the count of elements
	*inStream >> theCount;
	for (i = 0 ; i < theCount; i++) {
		theElement = new CAeteElement(inStream);
		AddElement(theElement);
	}
	// Initialize to 1 if there are parameters, 0 otherwise
	mCurrElementIndex = (theCount > 0);
}


// ---------------------------------------------------------------------------
//  ~CAeteClass												[public]
// ---------------------------------------------------------------------------

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
						OSType	inID, 
						OSType	inType, 
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
	CAeteProperty *	theProperty;
	if ( mProperties.FetchItemAt( inAtIndex, theProperty) ) {
		if (theProperty != NULL) {
			delete theProperty;
		} 
		mProperties.RemoveItemsAt(1, inAtIndex);
	} 
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
	CAeteElement *	theElement;
	if ( mElements.FetchItemAt( inAtIndex, theElement) ) {
		if (theElement != NULL) {
			delete theElement;
		} 
		mElements.RemoveItemsAt(1, inAtIndex);
	} 
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


