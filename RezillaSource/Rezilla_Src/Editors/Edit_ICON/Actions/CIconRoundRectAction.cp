// ===========================================================================
// CIconRoundRectAction.cp
//                       Created: 2004-12-11 18:52:36
//             Last modification: 2004-12-14 15:18:25
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

// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------

CIconRoundRectAction::CIconRoundRectAction( const SPaintAction &inAction, Boolean inFill ) : 
		CIconRectAction( inAction, inFill, index_UndoRoundRect )
{
}


// ---------------------------------------------------------------------------
// 	Destructor
// ---------------------------------------------------------------------------

CIconRoundRectAction::~CIconRoundRectAction()
{
}



// ---------------------------------------------------------------------------
// 	CIconRoundRectAction::DrawShape
// ---------------------------------------------------------------------------

void CIconRoundRectAction::DrawShape( const Rect &r )
{
	#define kOvalWidth		10
	#define kOvalHeight		10
		
	if ( mFilled )
	{
		::PenPat( &mSettings.thePattern );
		::PaintRoundRect( &r, kOvalWidth, kOvalHeight );
	}
	else
		::FrameRoundRect( &r, kOvalWidth, kOvalHeight );
}
