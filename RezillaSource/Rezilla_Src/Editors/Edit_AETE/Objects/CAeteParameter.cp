// ===========================================================================
// CAeteParameter.cp
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-01-20 14:57:13
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CAeteParameter.h"
#include "CAeteStream.h"


// ---------------------------------------------------------------------------
//  CAeteParameter												[public]
// ---------------------------------------------------------------------------

void
CAeteParameter::CAeteParameter(CAeteStream * inStream)
{
	*inStream >> mName;
	inStream->AlignBytes();

	*inStream >> mKeyword;
	*inStream >> mType;
	
	*inStream >> mDescription;
	inStream->AlignBytes();

	*inStream >> mFlags;
}


// ---------------------------------------------------------------------------
//  ~CAeteParameter												[public]
// ---------------------------------------------------------------------------

void
CAeteParameter::~CAeteParameter()
{
}


// ---------------------------------------------------------------------------
//  InstallDataStream												[public]
// ---------------------------------------------------------------------------

void
CAeteParameter::InstallDataStream()
{
}


// ---------------------------------------------------------------------------
//  SendDataToStream												[public]
// ---------------------------------------------------------------------------

void
CAeteParameter::SendDataToStream(CAeteStream * outStream)
{
}


