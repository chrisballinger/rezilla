// ===========================================================================
// CIconOvalAction.cp
//                       Created: 2004-12-11 18:52:27
//             Last modification: 2004-12-14 15:17:57
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "RezillaConstants.h"
#include "CIconActions.h"

#include <UDrawingState.h>

// ============================================================
// 	Constructor
// ============================================================

CIconOvalAction::CIconOvalAction( const SPaintAction &inAction, Boolean inFill ) : 
		CIconRectAction( inAction, inFill, index_UndoOval )
{
}


// ============================================================
// 	Destructor
// ============================================================

CIconOvalAction::~CIconOvalAction()
{
}



// ============================================================
// 	CIconOvalAction::DrawShape
// ============================================================

void CIconOvalAction::DrawShape( const Rect &r )
{
	if ( mFilled )
	{
		::PenPat( &mSettings.thePattern );
		::PaintOval( &r );
	}
	else
		::FrameOval( &r );
}

