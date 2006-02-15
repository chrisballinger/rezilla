// ===========================================================================
// CIconRecolorAction.h
//                       Created: 2004-12-11 18:57:03
//             Last modification: 2004-12-14 18:57:03
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// ===========================================================================

#ifndef _H_CIconRecolorAction
#define _H_CIconRecolorAction

#include "CIconActions.h"

class CIconRecolorAction : public CIconAction
{
	public:
							CIconRecolorAction( const SPaintAction &inAction, CTabHandle inTable );
		virtual				~CIconRecolorAction();
		
		virtual void		DoIt();

	protected:
		CTabHandle			mTable;

		virtual CTabHandle	CreateResizedTable( CTabHandle inSource );
};

#endif // _H_CIconRecolorAction
