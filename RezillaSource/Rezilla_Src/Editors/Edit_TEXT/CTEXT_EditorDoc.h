// ===========================================================================
// CTEXT_EditorDoc.h				
// 
//                       Created: 2004-06-17 12:46:55
//             Last modification: 2004-06-20 09:57:25
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
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


// ---------------------------------------------------------------------------

class CTEXT_EditorDoc : public CEditorDoc {
	
public:
						CTEXT_EditorDoc(LCommander* inSuper, 
									  CRezMapTable* inSuperMap, 
									  CRezObj* inRezObj,
									  Boolean inReadOnly);
						virtual ~CTEXT_EditorDoc();

	virtual void		FindCommandStatus( CommandT inCommand,
							Boolean &outEnabled, Boolean &outUsesMark,
							UInt16 &outMark, Str255 outName );

	virtual Boolean		ObeyCommand(
							CommandT			inCommand,
							void*				ioParam = nil);	

	virtual Boolean		IsModified();
	
	virtual StringPtr	GetDescriptor( Str255 outDescriptor ) const;

	virtual Boolean		AllowSubRemoval( LCommander* inSub );
	virtual SInt16		AskSaveChanges( bool inQuitting );

	void				SaveStylResource(StScrpHandle inScrapHandle);
	
protected:
	CTEXT_EditorWindow *		mTextEditWindow;
	
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
