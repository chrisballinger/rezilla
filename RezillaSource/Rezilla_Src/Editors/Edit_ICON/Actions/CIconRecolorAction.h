// ===========================================================================
// CIconRecolorAction.h
//                       Created: 2004-12-11 18:57:03
//             Last modification: 2004-12-14 18:57:03
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
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

