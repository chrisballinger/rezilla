// ===========================================================================
// CAeteElement.cp
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-01-20 09:35:10
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

void
CAeteElement::CAeteElement(CAeteStream * inStream)
{
}


// ---------------------------------------------------------------------------
//  ~CAeteElement													[public]
// ---------------------------------------------------------------------------

void
CAeteElement::~CAeteElement()
{
}


// ---------------------------------------------------------------------------
//  AddKeyForm														[public]
// ---------------------------------------------------------------------------

ArrayIndexT
CAeteElement::AddKeyForm( OSType inKey)
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


