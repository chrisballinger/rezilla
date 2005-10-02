// ===========================================================================
// CTmplEditorDoc.h				
// 
//                       Created: 2004-06-12 10:06:22
//             Last modification: 2005-01-09 09:07:38
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2004, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CTmplEditorDoc
#define _H_CTmplEditorDoc
#pragma once

#include "CEditorDoc.h"

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
									   ResType inSubstType,
									   Boolean inReadOnly);
						virtual ~CTmplEditorDoc();

	virtual void		FindCommandStatus( CommandT inCommand,
							Boolean &outEnabled, Boolean &outUsesMark,
							UInt16 &outMark, Str255 outName );
	
	virtual StringPtr	GetDescriptor( Str255 outDescriptor ) const;

	virtual Boolean		AllowSubRemoval( LCommander* inSub );
	virtual SInt16		AskSaveChanges( bool inQuitting );

	
protected:
	CTmplEditorWindow *		mTmplEditWindow;
	
	virtual Handle		GetModifiedResource(Boolean &releaseIt);

private:
	void				Initialize();
};


PP_End_Namespace_PowerPlant



#endif
