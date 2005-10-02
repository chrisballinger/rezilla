// ===========================================================================
// CMENU_EditorDoc.h				
// 
//                       Created: 2005-03-09 17:16:53
//             Last modification: 2005-03-23 09:07:59
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CMENU_EditorDoc
#define _H_CMENU_EditorDoc
#pragma once

#include "CEditorDoc.h"




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

	virtual void		FindCommandStatus( CommandT inCommand,
							Boolean &outEnabled, Boolean &outUsesMark,
							UInt16 &outMark, Str255 outName );

	virtual StringPtr	GetDescriptor( Str255 outDescriptor ) const;

	virtual Boolean		AllowSubRemoval( LCommander* inSub );

	void				SaveXmnuResource(Handle inXmnuHandle);
	

protected:
	CMENU_EditorWindow *		mMenuEditWindow;

	virtual Handle		GetModifiedResource(Boolean &releaseIt);

private:
	void				Initialize();
};


PP_End_Namespace_PowerPlant



#endif
