// ===========================================================================
// CUtxt_EditorDoc.h
// 
//                       Created: 2004-12-08 18:21:21
//             Last modification: 2004-12-09 07:37:40
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
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


// ---------------------------------------------------------------------------

class CUtxt_EditorDoc : public CEditorDoc {
	
public:
						CUtxt_EditorDoc(LCommander* inSuper,
										CRezMapTable* inSuperMap,
										CRezObj* inRezObj,
										ResType inSubstType,
										Boolean inReadOnly);
						virtual ~CUtxt_EditorDoc();

	virtual void		FindCommandStatus( CommandT inCommand,
							Boolean &outEnabled, Boolean &outUsesMark,
							UInt16 &outMark, Str255 outName );

	virtual StringPtr	GetDescriptor( Str255 outDescriptor ) const;

	virtual Boolean		AllowSubRemoval( LCommander* inSub );
	virtual SInt16		AskSaveChanges( bool inQuitting );

// 	void				SaveStylResource(StScrpHandle inScrapHandle);
// 	
	static  LMenu *		GetUnicodeFontsMenu() { return sUnicodeFontsMenu;}
	static void			SetUnicodeFontsMenu(LMenu * inMenu) {sUnicodeFontsMenu = inMenu;}

	static LMenu *		sUnicodeFontsMenu;
	
protected:
	CUtxt_EditorWindow *		mUtxtEditWindow;
	
	virtual Handle		GetModifiedResource();

private:
	void				Initialize();
	void				NameNewEditorDoc();
};


PP_End_Namespace_PowerPlant

#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
