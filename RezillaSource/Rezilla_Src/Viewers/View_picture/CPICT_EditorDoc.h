// ===========================================================================
// CPICT_EditorDoc.h				
// 
//                       Created: 2004-12-06 14:54:09
//             Last modification: 2006-10-09 16:30:59
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2004-2005, 2006
// All rights reserved.
// ===========================================================================

#ifndef _H_CPICT_EditorDoc
#define _H_CPICT_EditorDoc
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

class CPICT_EditorDoc : public CEditorDoc {
	
public:
						CPICT_EditorDoc(LCommander* inSuper,
										CRezMapTable* inSuperMap,
										CRezObj* inRezObj,
										ResType inSubstType,
										Boolean inReadOnly);
						virtual ~CPICT_EditorDoc();

	virtual void		FindCommandStatus( CommandT inCommand,
							Boolean &outEnabled, Boolean &outUsesMark,
							UInt16 &outMark, Str255 outName );

	virtual StringPtr	GetDescriptor( Str255 outDescriptor ) const;

#if PP_Uses_CFDescriptor
	virtual CFStringRef	CopyCFDescriptor() const;
#endif

	virtual Boolean		AllowSubRemoval( LCommander* inSub );
	virtual SInt16		AskSaveChanges( bool inQuitting );
	
protected:
	CPICT_EditorWindow *		mPictWindow;
	
	virtual Handle		GetModifiedResource(Boolean &releaseIt);
	
private:
	void			Initialize();

};


PP_End_Namespace_PowerPlant

#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
