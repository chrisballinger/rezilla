// ===========================================================================
// CMENU_EditorWindow.h
// 
//                       Created: 2005-03-09 17:16:53
//             Last modification: 2005-03-15 17:25:14
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#pragma once

#include "CEditorWindow.h"
#include "UResources.h"

#include <LPane.h>
#include <LView.h>
#include <LActiveScroller.h>


class CMENU_EditorDoc;
class CMENU_EditorTable;
class CMenuObject;
class LStaticText;


class CMENU_EditorWindow : public CEditorWindow {
public:
	enum { class_ID = FOUR_CHAR_CODE('MNUW') };

							CMENU_EditorWindow();
							CMENU_EditorWindow( const SWindowInfo &inWindowInfo );
							CMENU_EditorWindow( ResIDT inWINDid,
								UInt32 inAttributes, LCommander *inSuperCommander );
							CMENU_EditorWindow( LStream *inStream );
							~CMENU_EditorWindow();

	virtual void	ListenToMessage( MessageT inMessage,void *ioParam);

	virtual void	FindCommandStatus(
								CommandT	inCommand,
								Boolean&	outEnabled,
								Boolean&	outUsesMark,
								UInt16&		outMark,
								Str255		outName);

	virtual Boolean	ObeyCommand(
							CommandT		inCommand,
							void*			ioParam);

	OSErr			InstallMenuData(Handle inMenuHandle, Handle inXmnuHandle);
	
	virtual Handle			CollectMenuData();

	CMENU_EditorTable *		GetContentsView() const { return mItemsTable;}

	CMenuObject*			GetMenuObj() { return mMenuObj;}

	Boolean			GetHasXmnu() { return mHasXmnu;}
	void			SetHasXmnu(Boolean inHasXmnu) {mHasXmnu = inHasXmnu;}

protected:
	CMenuObject *		mMenuObj;
	CMENU_EditorTable *	mItemsTable;
	Boolean				mHasXmnu;
						
	virtual void	FinishCreateSelf();

private:
	Handle			RetrieveMenuData();
	Handle			RetrieveXmnuData();
	
	void			ClearItemValues();
	void			InstallCurrentItemValues();
	void			InstallItemValuesAtIndex( ArrayIndexT inAtIndex );
	void			InstallMenuValues();
	void			InstallTableValues();
	void			InstallGlyphValue(UInt8 inValue);

};


