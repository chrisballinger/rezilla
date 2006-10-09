// ===========================================================================
// CMENU_EditorDoc.h				
// 
//                       Created: 2005-03-09 17:16:53
//             Last modification: 2006-10-09 16:35:49
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2005, 2006
// All rights reserved.
// ===========================================================================

#ifndef _H_CMENU_EditorDoc
#define _H_CMENU_EditorDoc
#pragma once

#include "CEditorDoc.h"


#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

class	CRezFile;
class	CRezMapTable;
class	CRezObj;
class	CMENU_EditorWindow;


class CMENU_EditorDoc : public CEditorDoc {
	
public:
						CMENU_EditorDoc(LCommander* inSuper,
										CRezMapTable* inSuperMap,
										CRezObj* inRezObj,
										ResType inSubstType,
										Boolean inReadOnly);
						virtual ~CMENU_EditorDoc();

	virtual StringPtr	GetDescriptor( Str255 outDescriptor ) const;

	virtual Boolean		AllowSubRemoval( LCommander* inSub );

	void				SaveXmnuResource(Handle inXmnuHandle);
	

protected:
	CMENU_EditorWindow *		mMenuEditWindow;

	virtual Handle		GetModifiedResource(Boolean &releaseIt);
	
private:
	void			Initialize();
	
};


PP_End_Namespace_PowerPlant

#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
