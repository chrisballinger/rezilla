// ===========================================================================
// CPluginEditorWindow.h				
// 
//                       Created: 2005-10-02 08:41:52
//             Last modification: 2006-02-17 22:47:04
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2005-2006
// All rights reserved.
// ===========================================================================

#pragma once

#include "CEditorWindow.h"

class CPluginEditorDoc;
class CPluginMenu;


class CPluginEditorWindow : public CEditorWindow {
public:
	enum { class_ID = FOUR_CHAR_CODE('PluW') };

							CPluginEditorWindow();
							CPluginEditorWindow( const SWindowInfo &inWindowInfo );
							CPluginEditorWindow( ResIDT inWINDid,
								UInt32 inAttributes, LCommander *inSuperCommander );
							CPluginEditorWindow( LStream *inStream );
							~CPluginEditorWindow();

	virtual void	FindCommandStatus(
								CommandT			inCommand,
								Boolean&			outEnabled,
								Boolean&			outUsesMark,
								UInt16&				outMark,
								Str255				outName);

	virtual Boolean	ObeyCommand(
							CommandT			inCommand,
							void*				ioParam);

	virtual void	ListenToMessage( MessageT inMessage,void *ioParam);

	virtual void	FinalizeEditor(CPluginEditorDoc* inEditorDoc, void * ioParam = NULL);

	virtual void	RevertContents();
	
	void			InstallPluginNameField();

protected:
	TArray<LMenu*>		mPluginMenu;


	virtual void		FinishCreateSelf();
	virtual void		PutOnDuty(LCommander *inNewTarget);
	virtual void		TakeOffDuty();
	void				RemovePluginMenu();
	void				CreatePluginMenu(MenuID inMenuID);
	
};


