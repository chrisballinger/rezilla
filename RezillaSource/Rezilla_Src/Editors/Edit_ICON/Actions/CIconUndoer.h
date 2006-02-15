// ===========================================================================
// CIconUndoer.h
//                       Created: 2004-12-11 18:52:45
//             Last modification: 2004-12-23 15:26:28
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// ===========================================================================

 
#ifndef _H_CIconUndoer
#define _H_CIconUndoer
#pragma once


class CIconUndoer : public LUndoer {
	public:
		virtual void ExecuteSelf( MessageT inMessage, void *ioParam );
};


#endif // _H_CIconUndoer
