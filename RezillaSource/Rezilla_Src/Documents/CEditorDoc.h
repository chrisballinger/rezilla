// ===========================================================================
// CEditorDoc.h				
// 
//                       Created: 2004-02-23 17:57:59
//             Last modification: 2004-11-08 07:27:52
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003-2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#pragma once

#include <LWindow.h>
#include "UResources.h"

class CRezMapTable;
class CRezObj;
class CEditorWindow;

class CEditorDoc : public LDocument, public LListener {
public:
					CEditorDoc(LCommander* inSuper, 
							   CRezMapTable* inSuperMap, 
							   CRezObj* inRezObj,
							   ResType inSubstType,
							   Boolean inReadOnly);
					~CEditorDoc();

	virtual void	FindCommandStatus(
								CommandT			inCommand,
								Boolean&			outEnabled,
								Boolean&			outUsesMark,
								UInt16&				outMark,
								Str255				outName);

	virtual Boolean	ObeyCommand(
							CommandT			inCommand,
							void*				ioParam);
	
	virtual void		ListenToMessage(
							MessageT		inMessage,
							void*			ioParam);

	virtual Boolean	AllowSubRemoval( LCommander* inSub );

	virtual SInt16	AskSaveChanges( bool inQuitting );

	virtual void	AttemptClose( Boolean inRecordIt );
	
	Boolean			CanSaveChanges();
	
	virtual void	DoSaveChanges();
	
	virtual void	DoRevert();

	void			SelectMainWindow();

	CRezObj *		GetRezObj() { return mRezObj; }
	
	CRezMapTable*	GetRezMapTable() { return mRezMapTable;}

	ResType			GetSubstType() { return mSubstType;}
	void			SetSubstType(ResType inSubstType) {mSubstType = inSubstType;}
	
	SInt16			GetKind() { return mKind;}
	void			SetKind(SInt16 inKind) {mKind = inKind;}

	Boolean			IsReadOnly() { return mReadOnly;}
	void			SetReadOnly(Boolean inReadOnlyDoc) {mReadOnly = inReadOnlyDoc;}

	CEditorWindow*	GetMainWindow() { return mMainWindow;}
	void			SetMainWindow(CEditorWindow* inMainWindow) {mMainWindow = inMainWindow;}

protected:
	CRezObj *				mRezObj;
	CRezMapTable *			mRezMapTable;
	CEditorWindow *			mMainWindow;
	ResType					mSubstType;
	Boolean					mReadOnly;
	SInt16					mKind;

	virtual Handle	GetModifiedResource();
	void			BuildDocumentTitle(Str255 & outTitle, SInt16 whichString);
	void			Register();
	void			Unregister();
};


