// ===========================================================================
// CNewRezChooser.h
// 
//                       Created: 2006-10-07 07:20:12
//             Last modification: 2006-10-07 11:10:20
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================

#ifndef _H_CNewRezChooser
#define _H_CNewRezChooser

#include "UResources.h"

#include <LMenu.h>

class CRezMap;

class CNewRezChooser : public LWindow {
public:
							CNewRezChooser(CRezMap * inOwnerMap);
							~CNewRezChooser();

	OSErr				RunDialog();
	
	void				GetChosenValues(ResType &inType, short &inID, Str255 &inName, short &inAttrs);

protected:
	CRezMap *		mOwnerMap;
	ResType			mType;
	short 			mID;
	Str255			mName;
	short			mAttrs;
	
};



#endif  // _H_CNewRezChooser
