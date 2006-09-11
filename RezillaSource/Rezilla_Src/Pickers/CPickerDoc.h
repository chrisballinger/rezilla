// ===========================================================================
// CPickerDoc.h				
// 
//                       Created: 2006-02-23 15:12:16
//             Last modification: 2006-03-16 12:30:49
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================

#ifndef _H_CPickerDoc
#define _H_CPickerDoc
// #pragma once

#include <LWindow.h>
#include "UResources.h"

class CRezMapTable;
class CRezObj;
class CRezTypeItem;
class CPickerWindow;

class CPickerDoc : public LDocument, public LListener {
public:
					CPickerDoc(LCommander* inSuper, 
							   CRezMapTable* inSuperMap, 
							   CRezTypeItem* inRezTypeItem,
							   Boolean inReadOnly);
					~CPickerDoc();

	virtual void	FindCommandStatus(
								CommandT	inCommand,
								Boolean&	outEnabled,
								Boolean&	outUsesMark,
								UInt16&		outMark,
								Str255		outName);

	virtual Boolean	ObeyCommand(
							CommandT		inCommand,
							void*			ioParam);

	virtual void	ListenToMessage(
							MessageT		inMessage,
							void*			ioParam);

	virtual Boolean	AllowSubRemoval( LCommander* inSub );

	virtual void	AttemptClose( Boolean inRecordIt );
		
	virtual void	DoAEClose( const AppleEvent& inCloseAE );
	
	void			SelectPickerWindow();

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

	virtual void	GetSubModelByPosition(
								DescType			inModelID,
								SInt32				inPosition,
								AEDesc&				outToken) const;

	SInt32			GetAEPosition();
	
	static SInt32	GetAEPosition(const CPickerDoc * inDoc);
	
	virtual bool	AEPropertyExists(
								DescType		inProperty) const;

	virtual void	HandleAESave( const AppleEvent& inSaveAE );

	
	// Accessors
	CRezTypeItem *	GetRezTypeItem() { return mRezTypeItem; }
	
	CRezMapTable*	GetRezMapTable() { return mRezMapTable;}

	Boolean			IsReadOnly() { return mReadOnly;}
	void			SetReadOnly(Boolean inReadOnlyDoc) {mReadOnly = inReadOnlyDoc;}

	CPickerWindow*	GetPickerWindow() { return mPickerWindow;}
	void			SetPickerWindow(CPickerWindow* inPickerWindow) {mPickerWindow = inPickerWindow;}

protected:
	CRezTypeItem *			mRezTypeItem;
	CRezMapTable *			mRezMapTable;
	CPickerWindow *			mPickerWindow;
	Boolean					mReadOnly;

	virtual LModelObject*	GetModelProperty(
									DescType		inProperty) const;


	void			BuildDocumentTitle(Str255 & outTitle, SInt16 whichString);

	void			RegisterDoc();
	void			UnregisterDoc();
	
};


#endif  // _H_CPickerDoc
