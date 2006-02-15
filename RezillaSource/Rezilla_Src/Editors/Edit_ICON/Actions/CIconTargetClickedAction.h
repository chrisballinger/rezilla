// ===========================================================================
// CIconTargetClickedAction.h
//                       Created: 2004-12-11 18:57:10
//             Last modification: 2004-12-15 19:17:47
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// ===========================================================================
#ifndef _H_CIconTargetClickedAction
#define _H_CIconTargetClickedAction

#include "CIconActions.h"


class CDraggableTargetView;

class CIconTargetClickedAction : public CIconAction
{
	public:
								CIconTargetClickedAction( const SPaintAction &inAction, 
														CDraggableTargetView * );
		virtual					~CIconTargetClickedAction();
		
		virtual void			DoIt();
		
	protected:
		CDraggableTargetView	*mTargetViewHit;
};

#endif // _H_CIconTargetClickedAction
