// ===========================================================================
// CIconDragToTargetAction.h
//                       Created: 2004-12-11 18:56:55
//             Last modification: 2004-12-14 18:56:55
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CIconDragToTargetAction
#define _H_CIconDragToTargetAction

#include "CIconActions.h"
#include "CDraggableTargetView.h"


// ---------------------------------------------------------------------------
// 	CIconDragToTargetAction
// ---------------------------------------------------------------------------

class CIconDragToTargetAction : public CIconAction
{
	public:
								CIconDragToTargetAction( const SPaintAction &inAction, 
														SImageDropOnTargetView * );
		virtual					~CIconDragToTargetAction();
		virtual void			DoIt();
		
	protected:
		SImageDropOnTargetView	mDropInfo;
		
		virtual void			GenerateMask( COffscreen *inSource, COffscreen *inDest );
};

#endif // _H_CIconDragToTargetAction
