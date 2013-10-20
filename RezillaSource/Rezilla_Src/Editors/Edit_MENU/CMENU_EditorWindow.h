// ===========================================================================
// CMENU_EditorWindow.h
// 
//                       Created: 2005-03-09 17:16:53
//             Last modification: 2006-09-18 19:52:06
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2005-2006
// All rights reserved.
// ===========================================================================

#pragma once

#include "CEditorWindow.h"
#include "UResources.h"

#include <LPane.h>
#include <LView.h>
#include <LActiveScroller.h>


class CMENU_EditorTable;
class CMenuObject;
class LStaticText;
class LPopupButton;
class LEditText;
class LHandleStream;
class LTabGroupView;


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

	OSErr			InstallResourceData(Handle inMenuHandle, Handle inXmnuHandle);
	
	virtual Handle			CollectMenuData();

	virtual void			RevertContents();

	CMENU_EditorTable *		GetContentsView() const { return mItemsTable;}

	CMenuObject*			GetMenuObj() { return mMenuObj;}

	Boolean			GetHasXmnu() { return mHasXmnu;}
	void			SetHasXmnu(Boolean inHasXmnu) {mHasXmnu = inHasXmnu;}

protected:
	CMenuObject *		mMenuObj;
	CMENU_EditorTable *	mItemsTable;
	LPopupButton *		mPopup;
	LEditText 			*mItemTitleField,
						*mIconIdField,
						*mShortcutField,
						*mMarkCharField;
	LStaticText 		*mMarkCharLabel,
						*mIconIdLabel;
	LTabGroupView *		mTGV;
	LHandleStream *		mOutStream;
	Boolean				mHasXmnu,
						mNeedsXmnu,
						mInstallValue;
	bool 				mMENUFlipped, mXmnuFlipped;
	
	static Str31		sMarkCharStr, 
						sSubmenuIDStr, 
						sIconIDStr, 
						sScriptCodeStr;

	virtual void	FinishCreateSelf();

private:	
	void			ClearItemValues();
	
	void			InstallCurrentValues();
	void			InstallItemValues( ArrayIndexT inAtIndex );
	void			InstallMenuValues();
	void			InstallTableValues();
	void			InstallKeyboardGlyph(UInt8 inValue);
	
	void			RetrieveCurrentValues();
	void			RetrieveMenuValues();
	void			RetrieveItemValues( ArrayIndexT inAtIndex );

	void			HandlePropertyPopup(SInt32 inIndex);
	void			HandleEnableState(SInt32 inIndex);
	
};


