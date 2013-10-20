// ===========================================================================
// CUtxt_EditorDoc.h
// 
//                       Created: 2004-12-08 18:21:21
//             Last modification: 2006-10-09 16:34:10
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2004-2006
// All rights reserved.
// ===========================================================================

#ifndef _H_CUtxt_EditorDoc
#define _H_CUtxt_EditorDoc
#pragma once

#include "CEditorDoc.h"


#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

class LMenu;
class CRezFile;
class CRezMapTable;
class CRezObj;
class CUtxt_EditorWindow;


class CUtxt_EditorDoc : public CEditorDoc {
	
public:
						CUtxt_EditorDoc(LCommander* inSuper,
										CRezMapTable* inSuperMap,
										CRezObj* inRezObj,
										ResType inSubstType,
										Boolean inReadOnly);
						virtual ~CUtxt_EditorDoc();

// 	virtual Boolean		IsModified();

	virtual StringPtr	GetDescriptor( Str255 outDescriptor ) const;

#if PP_Uses_CFDescriptor
	virtual	CFStringRef	CopyCFDescriptor() const;
#endif

	virtual Boolean		AllowSubRemoval( LCommander* inSub );
	virtual SInt16		AskSaveChanges( bool inQuitting );
	
	void				SaveStylResource(Handle inStyleHandle);

protected:
	CUtxt_EditorWindow *		mUtxtEditWindow;
	
	virtual Handle		GetModifiedResource(Boolean &releaseIt);
	
private:
	void			Initialize();
	
};


PP_End_Namespace_PowerPlant

#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
