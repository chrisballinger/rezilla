// ===========================================================================
// CIcon_EditorDoc.h				
// 
//                       Created: 2004-12-11 23:33:03
//             Last modification: 2006-11-17 13:08:12
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2004-2006
// All rights reserved.
// ===========================================================================

#ifndef _H_CIcon_EditorDoc
#define _H_CIcon_EditorDoc
#pragma once

#include "CEditorDoc.h"


#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

class	CRezFile;
class	CRezMapTable;
class	CRezObj;
class	CIcon_EditorWindow;


// ---------------------------------------------------------------------------

class CIcon_EditorDoc : public CEditorDoc {
	
public:
						CIcon_EditorDoc(LCommander* inSuper,
										CRezMapTable* inSuperMap,
										CRezObj* inRezObj,
										ResType inSubstType,
										Boolean inReadOnly);
						virtual ~CIcon_EditorDoc();

	virtual StringPtr	GetDescriptor( Str255 outDescriptor ) const;

	virtual Boolean		AllowSubRemoval( LCommander* inSub );
	virtual SInt16		AskSaveChanges( bool inQuitting );
	
protected:
	CIcon_EditorWindow *		mIconEditWindow;

	virtual Handle		GetModifiedResource(Boolean &releaseIt);

private:
	void				Initialize();

};


PP_End_Namespace_PowerPlant

#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif // _H_CIcon_EditorDoc
