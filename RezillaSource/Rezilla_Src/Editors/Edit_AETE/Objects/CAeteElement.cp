// ===========================================================================
// CAeteElement.cp
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-02-04 06:06:00
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CAeteElement.h"
#include "CAeteStream.h"
#include "RezillaConstants.h"


// ---------------------------------------------------------------------------
//  CAeteElement													[public]
// ---------------------------------------------------------------------------

CAeteElement::CAeteElement(OSType inID)
{
	mID = inID;
	mKeyFormIndex = 0;
}


// ---------------------------------------------------------------------------
//  CAeteElement													[public]
// ---------------------------------------------------------------------------

CAeteElement::CAeteElement(CAeteStream * inStream)
{
	InstallDataStream(inStream);
}


// ---------------------------------------------------------------------------
//  ~CAeteElement													[public]
// ---------------------------------------------------------------------------

CAeteElement::~CAeteElement()
{
}


// ---------------------------------------------------------------------------
//  AddKeyForm														[public]
// ---------------------------------------------------------------------------

ArrayIndexT
CAeteElement::AddKeyForm( OSType inKey )
{
	return ( mKeyForms.AddItem(inKey) );
}


// ---------------------------------------------------------------------------
//  RemoveKeyForm													[public]
// ---------------------------------------------------------------------------

void
CAeteElement::RemoveKeyForm( ArrayIndexT inAtIndex )
{
	mKeyForms.RemoveItemsAt(1, inAtIndex);
}


// ---------------------------------------------------------------------------
//  InstallDataStream												[public]
// ---------------------------------------------------------------------------

void
CAeteElement::InstallDataStream(CAeteStream * inStream)
{
	UInt16	theCount, i;
	OSType	theType;

	*inStream >> mID;

	*inStream >> theCount;
	for (i = 0 ; i < theCount; i++) {
		*inStream >> theType;
		AddKeyForm(theType);
	}

	// Initialize to 1 if there are parameters, 0 otherwise
	mKeyFormIndex = (theCount > 0);
}


// ---------------------------------------------------------------------------
//  SendDataToStream												[public]
// ---------------------------------------------------------------------------

void
CAeteElement::SendDataToStream(CAeteStream * outStream)
{
	*outStream << mID;
	
	// KeyForms data
	*outStream << (UInt16) mKeyForms.GetCount();

	TArrayIterator<OSType> iterator( mKeyForms );
	OSType 	theKeyForm;
	
	while (iterator.Next(theKeyForm)) {
		*outStream << theKeyForm;
	}
}


// ---------------------------------------------------------------------------
//  NewKeyForm													[public]
// ---------------------------------------------------------------------------
// Returns the new count of KeyForms after addition. This is also the
// index of the new KeyForm.

SInt32
CAeteElement::NewKeyForm()
{	
	AddKeyForm();
	return CountKeyForms();
}
 

// ---------------------------------------------------------------------------
// DeleteKeyForm 													[public]
// ---------------------------------------------------------------------------
// Deletes the KeyForm at current index. Returns the new count of
// KeyForms after deletion.

SInt32
CAeteElement::DeleteKeyForm()
{
	RemoveKeyForm(mKeyFormIndex);
	mKeyFormIndex = -1;
	return CountKeyForms();
}
 
// SInt32
// CAeteElement::DeleteKeyForm()
// {
// 	SInt32	count;
// 	RemoveKeyForm(mKeyFormIndex);
// 	count = CountKeyForms();
// 	mKeyFormIndex = (count > 0);
// 	return count;
// }
 

// ---------------------------------------------------------------------------
// GetCurrentKeyForm 												[public]
// ---------------------------------------------------------------------------

Boolean
CAeteElement::GetCurrentKeyForm(OSType & outKeyForm)
{
	Boolean	found = false;
	if ( mKeyForms.FetchItemAt(mKeyFormIndex, outKeyForm) ) {
		found = true;
	} 
	
	return found;
}


// ---------------------------------------------------------------------------
// SetCurrentKeyForm 												[public]
// ---------------------------------------------------------------------------

void
CAeteElement::SetCurrentKeyForm(OSType inKeyForm)
{
	mKeyForms.AssignItemsAt(1, mKeyFormIndex, inKeyForm);
}

