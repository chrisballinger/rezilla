// ===========================================================================
// CAeteCompOp.cp
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-01-20 14:02:09
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CAeteCompOp.h"
#include "CAeteStream.h"


// ---------------------------------------------------------------------------
//  CAeteCompOp												[public]
// ---------------------------------------------------------------------------

CAeteCompOp::CAeteCompOp(CAeteStream * inStream)
{
	*inStream >> mName;
	inStream->AlignBytes();

	*inStream >> mType;
	
	*inStream >> mDescription;
	inStream->AlignBytes();
}


// ---------------------------------------------------------------------------
//  ~CAeteCompOp												[public]
// ---------------------------------------------------------------------------

CAeteCompOp::~CAeteCompOp()
{
}


// ---------------------------------------------------------------------------
//  InstallDataStream												[public]
// ---------------------------------------------------------------------------

void
CAeteCompOp::InstallDataStream()
{
}


// ---------------------------------------------------------------------------
//  SendDataToStream												[public]
// ---------------------------------------------------------------------------

void
CAeteCompOp::SendDataToStream(CAeteStream * outStream)
{
}


