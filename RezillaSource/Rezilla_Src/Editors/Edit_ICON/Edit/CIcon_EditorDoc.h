// ===========================================================================
// CIcon_EditorDoc.h				
// 
//                       Created: 2004-12-11 23:33:03
//             Last modification: 2005-01-09 09:06:16
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CIcon_EditorDoc
#define _H_CIcon_EditorDoc
#pragma once

#include "CEditorDoc.h"




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

	virtual void		FindCommandStatus( CommandT inCommand,
							Boolean &outEnabled, Boolean &outUsesMark,
							UInt16 &outMark, Str255 outName );

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



#endif // _H_CIcon_EditorDoc
