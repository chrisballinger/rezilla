// ===========================================================================
// CPatternTargetView.h
//                       Created: 2004-12-11 18:57:47
//             Last modification: 2004-12-27 11:44:16
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CPatternTargetView
#define _H_CPatternTargetView
#pragma once

#include "CDraggableTargetView.h"

class CPatternTargetView : public CDraggableTargetView {
	public:
		enum { class_ID = FOUR_CHAR_CODE('PTBx') };
		
										CPatternTargetView( LStream * );
		virtual							~CPatternTargetView();
		static CPatternTargetView *		CreateFromStream( LStream * );
	
	protected:
		virtual void					DrawBuffer();
};


#endif // _H_CPatternTargetView
