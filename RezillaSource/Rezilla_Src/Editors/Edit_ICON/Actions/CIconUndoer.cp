// ===========================================================================
// CIconUndoer.cp
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
// 
// This class is the same as LUndoer, but it supports one additional
// message of use to the Icon Editor: "Get Last Command".
// 
// This allows the Icon Editor to query the previous command to see if it
// is a "Move" command, since multiple move commands undo to the very first
// one, not the most recent one.
	
#include "CIconUndoer.h"


void CIconUndoer::ExecuteSelf( MessageT inMessage, void *ioParam )
{
	if ( inMessage == cmd_GetLastCommand )
	{
		*(LAction**) ioParam = mAction;
		return;
	}
	
	LUndoer::ExecuteSelf( inMessage, ioParam );
}
