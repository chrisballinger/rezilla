// ===========================================================================
// CIconUndoer.h
//                       Created: 2004-12-11 18:52:45
//             Last modification: 2004-12-14 18:52:45
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

 
#pragma once

const CommandT		cmd_GetLastCommand		= 'LCMD';


class CIconUndoer : public LUndoer
{
	public:
		virtual void ExecuteSelf( MessageT inMessage, void *ioParam );
};

