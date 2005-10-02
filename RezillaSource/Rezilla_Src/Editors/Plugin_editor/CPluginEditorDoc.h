// ===========================================================================
// CPluginEditorDoc.h
// 
//                       Created: 2005-10-02 08:41:52
//             Last modification: 2005-10-02 08:42:01
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#pragma once

#include "CEditorDoc.h"

class CRezMapTable;
class CRezObj;
class CPluginEditorWindow;
class CRezillaPlugin;

class CPluginEditorDoc : public CEditorDoc {
public:
					CPluginEditorDoc(LCommander* inSuper, 
							   CRezMapTable* inSuperMap, 
							   CRezObj* inRezObj,
							   ResType inSubstType,
							   Boolean inReadOnly);
					~CPluginEditorDoc();

	virtual void	FindCommandStatus(
								CommandT			inCommand,
								Boolean&			outEnabled,
								Boolean&			outUsesMark,
								UInt16&				outMark,
								Str255				outName);

	virtual Boolean	ObeyCommand(
							CommandT			inCommand,
							void*				ioParam);
	
	virtual void	ListenToMessage(
							MessageT		inMessage,
							void*			ioParam);

	virtual Boolean	AllowSubRemoval( LCommander* inSub );
	virtual SInt16	AskSaveChanges( bool inQuitting );

	virtual StringPtr	GetDescriptor( Str255 outDescriptor ) const;

	// Accessors
	CRezillaPlugin*				GetPlugin() { return mPlugin;}
	CPluginEditorWindow*		GetAeteEditWindow() { return mPluginWindow;}

protected:
	CRezillaPlugin *		mPlugin;
	CPluginEditorWindow *	mPluginWindow;

	virtual LModelObject*	GetModelProperty(
									DescType		inProperty) const;

	virtual Handle	GetModifiedResource(Boolean &releaseIt) = 0;  // Purely virtual

private:
		void				Initialize();
};


