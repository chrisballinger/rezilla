// ===========================================================================
// CColorPopup.h
//                       Created: 2004-12-11 18:57:34
//             Last modification: 2004-12-14 18:57:34
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CColorPopup
#define _H_CColorPopup
#pragma once

#include "CPopupWindow.h"

class CColorPopup : protected CPopupWindow
{
	public:
		static SInt32		DoColorPopup( Point inTopLeft, CTabHandle, SInt32 defaultItem = -1 );
	
	protected:
		CTabHandle			mColorTable;
		
							CColorPopup( CTabHandle inTable );
		virtual				~CColorPopup();
		
		virtual void		Prepare( Point inTopLeft );
		virtual void		DrawInitialState();
		virtual void		DrawOneCell( SInt32 inIndex, Boolean inHilited = false );
};

#endif // _H_CColorPopup
