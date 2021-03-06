// ===========================================================================
// CTmplEditorDoc.h				
// 
//                       Created: 2004-06-12 10:06:22
//             Last modification: 2006-10-09 16:32:26
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes, 2004-2006
// All rights reserved.
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
									   ResType inSubstType,
									   Boolean inReadOnly);
						virtual ~CTmplEditorDoc();

	virtual StringPtr	GetDescriptor( Str255 outDescriptor ) const;

#if PP_Uses_CFDescriptor
	virtual CFStringRef	CopyCFDescriptor() const;
#endif

	virtual Boolean		AllowSubRemoval( LCommander* inSub );
	virtual SInt16		AskSaveChanges( bool inQuitting );

	
protected:
	CTmplEditorWindow *		mTmplEditWindow;
	
	virtual Handle		GetModifiedResource(Boolean &releaseIt);

private:
	void			Initialize();

};


PP_End_Namespace_PowerPlant

#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
