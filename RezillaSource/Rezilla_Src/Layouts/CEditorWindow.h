// ===========================================================================
// CEditorWindow.h				
// 
//                       Created: 2004-06-10 14:44:33
//             Last modification: 2006-02-21 15:31:33
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2004-2006
// All rights reserved.
// ===========================================================================

#pragma once

#include "UResources.h"

#include <LWindow.h>

class CEditorDoc;
class CRezObj;


class CEditorWindow : public LWindow, public LListener {
public:
	enum { class_ID = FOUR_CHAR_CODE('EdiW') };

							CEditorWindow();
							CEditorWindow( const SWindowInfo &inWindowInfo );
							CEditorWindow(
							    ResIDT inWINDid,
								UInt32 inAttributes, LCommander *inSuperCommander );
							CEditorWindow(
								WindowPtr	inMacWindow,
								LCommander*	inSuperCommander);
							CEditorWindow( LStream *inStream );
							~CEditorWindow();

	virtual void	ListenToMessage( MessageT inMessage,void *ioParam);

	virtual void	FindCommandStatus(
								CommandT			inCommand,
								Boolean&			outEnabled,
								Boolean&			outUsesMark,
								UInt16&				outMark,
								Str255				outName);

	virtual Boolean	ObeyCommand(
							CommandT			inCommand,
							void*				ioParam);

	virtual void	FinalizeEditor(CEditorDoc* inEditorDoc, void * ioParam = NULL);

	virtual void	RevertContents();
	
	virtual Boolean	IsDirty();

	virtual void	SetDirty(Boolean inDirty);

	void			InstallReadOnlyIcon();

	void			InstallResourceNameField();

	// AppleEvents
	virtual void	MakeSelfSpecifier(
								AEDesc&			inSuperSpecifier,
								AEDesc&			outSelfSpecifier) const;

	virtual void	GetAEProperty(
								DescType			inProperty,
								const AEDesc&		inRequestedType,
								AEDesc&				outPropertyDesc) const;
	
// 	void			SetAEProperty(
// 								DescType		inProperty,
// 								const AEDesc&	inValue,
// 								AEDesc&			outAEReply);

	virtual bool	AEPropertyExists(
								DescType		inProperty) const;

	// Accessors
	virtual CEditorDoc*		GetOwnerDoc() { return mOwnerDoc;}
	void					SetOwnerDoc(CEditorDoc* theOwnerDoc) {mOwnerDoc = theOwnerDoc ;}

protected:
	CEditorDoc *		mOwnerDoc;
	Boolean				mIsDirty;

};


