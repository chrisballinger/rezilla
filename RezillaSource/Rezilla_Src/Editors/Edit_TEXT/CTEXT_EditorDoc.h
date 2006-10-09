// ===========================================================================
// CTEXT_EditorDoc.h				
// 
//                       Created: 2004-06-17 12:46:55
//             Last modification: 2006-10-09 16:34:35
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2004-2006
// All rights reserved.
// ===========================================================================

#ifndef _H_CTEXT_EditorDoc
#define _H_CTEXT_EditorDoc
#pragma once

#include "CEditorDoc.h"


#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

class	CRezFile;
class	CRezMapTable;
class	CRezObj;
class	CTEXT_EditorWindow;


class CTEXT_EditorDoc : public CEditorDoc {
	
public:
						CTEXT_EditorDoc(LCommander* inSuper,
										CRezMapTable* inSuperMap,
										CRezObj* inRezObj,
										ResType inSubstType,
										Boolean inReadOnly);
						virtual ~CTEXT_EditorDoc();

	virtual StringPtr	GetDescriptor( Str255 outDescriptor ) const;

	virtual Boolean		AllowSubRemoval( LCommander* inSub );
	virtual SInt16		AskSaveChanges( bool inQuitting );

	void				SaveStylResource(StScrpHandle inScrapHandle);
	
protected:
	CTEXT_EditorWindow *		mTextEditWindow;
	
	virtual Handle		GetModifiedResource(Boolean &releaseIt);
	
private:
	void			Initialize();

};


PP_End_Namespace_PowerPlant

#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
