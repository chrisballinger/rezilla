// ===========================================================================
// CHexEditorDoc.h				
// 
//                       Created: 2003-05-04 19:16:00
//             Last modification: 2006-10-09 16:33:41
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2003-2005, 2006
// All rights reserved.
// ===========================================================================

#ifndef _H_CHexEditorDoc
#define _H_CHexEditorDoc
#pragma once

#include "CEditorDoc.h"


#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

class	CRezFile;
class	CRezMapTable;
class	CRezObj;
class	CHexEditorWindow;


// ---------------------------------------------------------------------------

class CHexEditorDoc : public CEditorDoc {
	
public:
						CHexEditorDoc(LCommander* inSuper, 
									 CRezMapTable* inSuperMap,
									 CRezObj* inRezObj,
									 ResType inSubstType,
									 Boolean inReadOnly);
						virtual ~CHexEditorDoc();

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

protected:
	CHexEditorWindow *		mHexEditWindow;
	Str255					mSearchString;
	SInt32					mMatchStart;
	SInt32					mMatchEnd;
	PaneIDT					mSearchWhichPane;
	Boolean					mIgnoreCase;
	
	virtual Handle		GetModifiedResource(Boolean &releaseIt);
	void				RunFindDialog();
	void				Initialize();

private:
	OSErr				FindInPane(PaneIDT inWhichPane, 
									Boolean isIgnoreCase,
									Boolean findingNext);
};


PP_End_Namespace_PowerPlant

#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
