// ===========================================================================
// CIconEditActions.h
//                       Created: 2004-12-11 18:56:58
//             Last modification: 2004-12-15 19:18:39
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CIconEditActions
#define _H_CIconEditActions
#pragma once

#include "CIconActions.h"


class CIconCutAction : public CIconAction {
	public:
						CIconCutAction( const SPaintAction & );
		virtual			~CIconCutAction();
		
		virtual void	DoIt();
};


class CIconCopyAction : public CIconAction {
	public:
						CIconCopyAction( const SPaintAction & );
		virtual			~CIconCopyAction();

		virtual void	DoIt();
};


class CIconPasteAction : public CIconAction {
	public:
						CIconPasteAction( const SPaintAction & );
		virtual			~CIconPasteAction();

		virtual void	DoIt();
};


class CIconClearAction : public CIconAction {
	public:
						CIconClearAction( const SPaintAction & );
		virtual			~CIconClearAction();

		virtual void	DoIt();
};

#endif // _H_CIconEditActions
