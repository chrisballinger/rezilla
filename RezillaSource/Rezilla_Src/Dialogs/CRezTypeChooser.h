// ===========================================================================
// CRezTypeChooser.h
// 
//                       Created: 2004-08-12 15:59:49
//             Last modification: 2004-11-19 07:10:27
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// ===========================================================================

#ifndef _H_CRezTypeChooser
#define _H_CRezTypeChooser

#include "UResources.h"

#include <LMenu.h>



class CRezTypeChooser : public LWindow {
public:
							CRezTypeChooser();
							~CRezTypeChooser();

	OSErr			RunDialog();
	
	ResType			GetChosenType() { return sChosenType;}

protected:
	static ResType		sChosenType;

	LMenu *				mTypesMenu;
	
};



#endif  // _H_CRezTypeChooser
