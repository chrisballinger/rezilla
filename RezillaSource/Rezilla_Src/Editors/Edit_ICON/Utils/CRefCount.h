// ===========================================================================
// CRefCount.h
//                       Created: 2004-12-11 18:52:05
//             Last modification: 2004-12-15 10:30:19
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#pragma once

class CRefCount
{
	public:
							CRefCount();
		virtual				~CRefCount();
		
		virtual void	IncrementRefCount();
		virtual void	DecrementRefCount();
		
	protected:
		UInt32			mRefCount;
};

