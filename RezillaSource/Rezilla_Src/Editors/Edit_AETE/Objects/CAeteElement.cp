// ===========================================================================
// CAeteElement.cp
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-01-21 06:40:03
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
CAeteElement::InstallDataStream()
{
}


// ---------------------------------------------------------------------------
//  SendDataToStream												[public]
// ---------------------------------------------------------------------------

void
CAeteElement::SendDataToStream(CAeteStream * outStream)
{
}


