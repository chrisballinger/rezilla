// ===========================================================================
// CIconTargetClickedAction.h
//                       Created: 2004-12-11 18:57:10
//             Last modification: 2004-12-15 19:17:47
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
#ifndef _H_CIconTargetClickedAction
#define _H_CIconTargetClickedAction

#include "CIconActions.h"


class CDraggableTargetBox;

class CIconTargetClickedAction : public CIconAction
{
	public:
								CIconTargetClickedAction( const SPaintAction &inAction, 
														CDraggableTargetBox * );
		virtual					~CIconTargetClickedAction();
		
		virtual void			DoIt();
		
	protected:
		CDraggableTargetBox	*mTargetBoxHit;
};

#endif // _H_CIconTargetClickedAction
