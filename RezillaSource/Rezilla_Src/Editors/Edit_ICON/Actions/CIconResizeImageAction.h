// ===========================================================================
// CIconResizeImageAction.h
//                       Created: 2004-12-11 18:57:04
//             Last modification: 2004-12-14 18:57:04
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
#include "CIconActions.h"
#include "CResizer.h"

class CIconResizeImageAction : public CIconAction
{
	public:
							CIconResizeImageAction( const SPaintAction & );
		virtual 			~CIconResizeImageAction();
		
		virtual void		DoIt();
		
	protected:
		CResizer			mBeforeState, mAfterState;
		Boolean				mCancelledResize;
		virtual void		UndoSelf();
		virtual void		RedoSelf();
};

