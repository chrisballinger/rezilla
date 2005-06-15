// ===========================================================================
// CEditorDoc.h				
// 
//                       Created: 2004-02-23 17:57:59
//             Last modification: 2005-05-14 11:01:55
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003-2005
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
		
	virtual void	DoAEClose( const AppleEvent& inCloseAE );

	Boolean			CanSaveChanges();
	
	virtual void	DoSaveChanges();
	
	virtual void	DoRevert();

	void			SelectMainWindow();

	virtual StringPtr	GetDescriptor( Str255 outDescriptor ) const;

	// AppleEvents
	virtual void	MakeSelfSpecifier(
								AEDesc&			inSuperSpecifier,
								AEDesc&			outSelfSpecifier) const;

	virtual void	GetAEProperty(
								DescType			inProperty,
								const AEDesc&		inRequestedType,
								AEDesc&				outPropertyDesc) const;
	
	void			SetAEProperty(
								DescType		inProperty,
								const AEDesc&	inValue,
								AEDesc&			outAEReply);

	virtual void		GetSubModelByPosition(
								DescType			inModelID,
								SInt32				inPosition,
								AEDesc&				outToken) const;

	SInt32			GetAEPosition();
	
	static SInt32	GetAEPosition(const CEditorDoc * inDoc);
	
	virtual bool	AEPropertyExists(
								DescType		inProperty) const;

	virtual void	HandleAESave( const AppleEvent& inSaveAE );

	// Accessors
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

	virtual LModelObject*	GetModelProperty(
									DescType		inProperty) const;

	virtual Handle	GetModifiedResource(Boolean &releaseIt) = 0;  // Purely virtual
	void			NameNewEditorDoc();
	void			BuildDocumentTitle(Str255 & outTitle, SInt16 whichString);
	void			Register();
	void			Unregister();
};


