// ===========================================================================
// CRefCount.cp
//                       Created: 2004-12-11 18:52:03
//             Last modification: 2004-12-15 10:28:44
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CRefCount.h"


// ============================================================
// 	Constructor
// ============================================================

CRefCount::CRefCount()
{
	// Since someone created us
	mRefCount = 1;
}


// ============================================================
// 	Destructor
// ============================================================

CRefCount::~CRefCount()
{
}


// ============================================================
// 	IncrementRefCount
// ============================================================

void CRefCount::IncrementRefCount()
{
	++mRefCount;
}


// ============================================================
// 	DecrementRefCount
// ============================================================
// 	Deletes the object if the count goes to zero.

void CRefCount::DecrementRefCount()
{
	--mRefCount;
	if ( mRefCount == 0 )
		delete this;
}
