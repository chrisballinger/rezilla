// ===========================================================================
// CAeteProperty.cp
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-01-20 14:25:39
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CAeteProperty.h"
#include "CAeteStream.h"


// ---------------------------------------------------------------------------
//  CAeteProperty												[public]
// ---------------------------------------------------------------------------

void
CAeteProperty::CAeteProperty(CAeteStream * inStream)
{
	*inStream >> mName;
	inStream->AlignBytes();

	*inStream >> mID;
	*inStream >> mType;
	
	*inStream >> mDescription;
	inStream->AlignBytes();

	*inStream >> mFlags;
}


// ---------------------------------------------------------------------------
//  ~CAeteProperty												[public]
// ---------------------------------------------------------------------------

void
CAeteProperty::~CAeteProperty()
{
}


// ---------------------------------------------------------------------------
//  InstallDataStream												[public]
// ---------------------------------------------------------------------------

void
CAeteProperty::InstallDataStream()
{
}


// ---------------------------------------------------------------------------
//  SendDataToStream												[public]
// ---------------------------------------------------------------------------

void
CAeteProperty::SendDataToStream(CAeteStream * outStream)
{
}


