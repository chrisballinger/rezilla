// ===========================================================================
// CTmplEditorDoc.h				
// 
//                       Created: 2004-06-12 10:06:22
//             Last modification: 2004-06-12 07:53:08
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CTmplEditorDoc
#define _H_CTmplEditorDoc
#pragma once

#include "CEditorDoc.h"


#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

class	CRezFile;
class	CRezMapTable;
class	CRezObj;
class	CTmplEditorWindow;


// ---------------------------------------------------------------------------

class CTmplEditorDoc : public CEditorDoc {
	
public:
						CTmplEditorDoc(LCommander* inSuper, 
									  CRezMapTable* inSuperMap, 
									  CRezObj* inRezObj,
									  Boolean inReadOnly);
						virtual ~CTmplEditorDoc();

	virtual void		FindCommandStatus( CommandT inCommand,
							Boolean &outEnabled, Boolean &outUsesMark,
							UInt16 &outMark, Str255 outName );

	virtual Boolean		ObeyCommand(
							CommandT			inCommand,
							void*				ioParam = nil);	

// 	virtual void		ListenToMessage(
// 							MessageT		inMessage,
// 							void*			ioParam);

	virtual Boolean		IsModified();
	
	virtual StringPtr	GetDescriptor( Str255 outDescriptor ) const;

	virtual Boolean		AllowSubRemoval( LCommander* inSub );
	virtual SInt16		AskSaveChanges( bool inQuitting );

	
protected:
	CTmplEditorWindow *		mTmplEditWindow;
	
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
