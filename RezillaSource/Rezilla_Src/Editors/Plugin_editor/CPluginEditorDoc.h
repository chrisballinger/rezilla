// ===========================================================================
// CPluginEditorDoc.h
// 
//                       Created: 2005-10-02 08:41:52
//             Last modification: 2006-02-21 07:12:41
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2005-2006
// All rights reserved.
// ===========================================================================

#pragma once

#include "CEditorDoc.h"

class CRezMapTable;
class CRezObj;
class CPluginEditorWindow;
class CRezillaPlugin;

class CPluginEditorDoc : public CEditorDoc {
public:
					CPluginEditorDoc(
							 LCommander* inSuper, 
							 CRezMapTable* inSuperMap, 
							 CRezObj* inRezObj,
							 ResType inSubstType,
							 Boolean inReadOnly,
							 CRezillaPlugin * inPlugin);
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
	CRezillaPlugin*			GetPlugin() { return mPlugin;}
	CPluginEditorWindow*	GetPluginEditWindow() { return mPluginWindow;}

protected:
	CRezillaPlugin *		mPlugin;
	CPluginEditorWindow *	mPluginWindow;

// 	virtual LModelObject*	GetModelProperty(
// 									DescType		inProperty) const;

	virtual Handle	GetModifiedResource(Boolean &releaseIt);

private:
		void			Initialize();
		
};


