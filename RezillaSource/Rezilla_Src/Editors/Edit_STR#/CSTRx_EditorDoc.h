// ===========================================================================
// CSTRx_EditorDoc.h				
// 
//                       Created: 2005-08-31 18:26:24
//             Last modification: 2006-10-09 16:35:14
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2005-2006
// All rights reserved.
// ===========================================================================

#ifndef _H_CSTRx_EditorDoc
#define _H_CSTRx_EditorDoc
#pragma once

#include "CEditorDoc.h"


#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

class	CRezFile;
class	CRezMapTable;
class	CRezObj;
class	CSTRx_EditorWindow;


class CSTRx_EditorDoc : public CEditorDoc {
	
public:
						CSTRx_EditorDoc(LCommander* inSuper,
										CRezMapTable* inSuperMap,
										CRezObj* inRezObj,
										ResType inSubstType,
										Boolean inReadOnly);
						virtual ~CSTRx_EditorDoc();

	virtual StringPtr	GetDescriptor( Str255 outDescriptor ) const;

#if PP_Uses_CFDescriptor
	virtual CFStringRef	CopyCFDescriptor() const;
#endif

	virtual Boolean		AllowSubRemoval( LCommander* inSub );
	

protected:
	CSTRx_EditorWindow *		mStrxEditWindow;

	virtual Handle		GetModifiedResource(Boolean &releaseIt);

private:
	void			Initialize();
	
};


PP_End_Namespace_PowerPlant

#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
