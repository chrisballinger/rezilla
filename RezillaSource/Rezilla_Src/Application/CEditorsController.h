// ===========================================================================
// CEditorsController.h				
// 
//                       Created: 2004-06-11 10:48:38
//             Last modification: 2004-08-10 11:33:08
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#pragma once

#include "UResources.h"
#include <CFPropertyList.h>

class	CRezMapTable;
class	CRezObj;

class CEditorsController {
public:
						CEditorsController();
						~CEditorsController();
	
	static Boolean	FindSubstitutionType(ResType inType, ResType * outType);

	static Boolean	HasEditorForType(ResType inType, ResType * substType);
	static void		InvokeCustomEditor(LCommander* inSuper, 
						   CRezMapTable* inSuperMap, 
						   CRezObj* inRezObj,
						   Boolean inReadOnly);
	static OSErr	OpenOrCreateWithTypeAndID(
							CRezMapTable* inSuperMap, 
							ResType inType, 
							short inID, 
							CRezObj** outRezObj);

	OSErr			RegisterEditor();


	static CFPropertyListRef	sAsTypeDictionary;

protected:	

	void			BuildAsTypeDictionary();
	void			Unregister();
};

