// ===========================================================================
// CSharedPalette.h
//                       Created: 2004-12-11 18:52:59
//             Last modification: 2004-12-14 18:52:59
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#pragma once

#include "CRefCountMixin.h"


// ============================================================
// 	CSharedPalette
// ============================================================

class CSharedPalette : public CRefCountMixin
{
	public:
								CSharedPalette( CTabHandle, GrafPtr inPort = nil, short inUpdates = pmNoUpdates );
		virtual					~CSharedPalette();
		virtual PaletteHandle	GetPalette();
		
		virtual void			AttachToPort( GrafPtr inPort, short inUpdates = pmNoUpdates );
		
	protected:
		PaletteHandle			mPaletteH;
};

