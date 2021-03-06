// ===========================================================================
// CEditorsController.h				
// 
//                       Created: 2004-06-11 10:48:38
//             Last modification: 2006-02-23 15:54:42
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2004-2006
// All rights reserved.
// ===========================================================================

#pragma once

#include "UResources.h"
#ifndef __MACH__
#include <CFPropertyList.h>
#endif

class CRezMapDoc;
class CRezMapTable;
class CRezObjItem;
class CRezObj;

class CEditorsController {
public:
						CEditorsController();
						~CEditorsController();
	
	static Boolean	FindSubstitutionType(ResType inType, ResType * outType);

	static Boolean	HasEditorForType(ResType inType, ResType * substType);

	static void		InvokeCustomEditor(CRezMapDoc* inRezMapDoc, 
									   CRezObjItem * inRezObjItem,
									   ResType inUseType);

	static OSErr	OpenOrCreateWithTypeAndID(
							CRezMapTable* inSuperMap, 
							ResType inType, 
							short inID, 
							CRezObj** outRezObj);
	
	static Boolean	TypesCorrespond(ResType inType1, 
									ResType inType2, 
									Boolean exact);

	static CFMutableDictionaryRef	sAsTypeDictionary;

protected:	

	void			BuildAsTypeDictionary();
};


