// ===========================================================================
// CSnd_EditorDoc.h				
// 
//                       Created: 2004-12-07 07:22:47
//             Last modification: 2006-10-09 16:30:49
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2004-2005, 2006
// All rights reserved.
// ===========================================================================

#ifndef _H_CSnd_EditorDoc
#define _H_CSnd_EditorDoc
#pragma once

#include "CEditorDoc.h"


#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

class	CRezFile;
class	CRezMapTable;
class	CRezObj;
class	CPICT_EditorWindow;


// ---------------------------------------------------------------------------

class CSnd_EditorDoc : public CEditorDoc {
	
public:
						CSnd_EditorDoc(LCommander* inSuper,
										CRezMapTable* inSuperMap,
										CRezObj* inRezObj,
										ResType inSubstType,
										Boolean inReadOnly);
						virtual ~CSnd_EditorDoc();

	void				Play(Handle inSoundH);
	
protected:

private:
	virtual Handle		GetModifiedResource(Boolean &releaseIt);
	void				Initialize();
	
};


PP_End_Namespace_PowerPlant

#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
