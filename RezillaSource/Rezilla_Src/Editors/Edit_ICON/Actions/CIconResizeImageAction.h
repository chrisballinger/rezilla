// ===========================================================================
// CIconResizeImageAction.h
//                       Created: 2004-12-11 18:57:04
//             Last modification: 2004-12-23 23:54:37
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CIconResizeImageAction
#define _H_CIconResizeImageAction

#include "CIconActions.h"
#include "CIconViewResizer.h"

class CIconResizeImageAction : public CIconAction {
	public:
							CIconResizeImageAction( const SPaintAction & );
		virtual 			~CIconResizeImageAction();
		
		virtual void		DoIt();
		
	protected:
		CIconViewResizer	mBeforeState, mAfterState;
		Boolean				mCancelledResize;
		virtual void		UndoSelf();
		virtual void		RedoSelf();
};

#endif // _H_CIconResizeImageAction
