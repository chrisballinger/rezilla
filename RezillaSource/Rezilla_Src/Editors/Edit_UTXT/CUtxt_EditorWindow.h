// ===========================================================================
// CUtxt_EditorWindow.h
// 
//                       Created: 2004-12-08 18:21:21
//             Last modification: 2004-12-09 07:37:15
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#pragma once

#include "CEditorWindow.h"
#include "UResources.h"

// #include <LPane.h>
// #include <LView.h>
// #include <LActiveScroller.h>


class CUtxt_EditorDoc;
class CRezObj;
class CUtxt_EditorView;
class LStaticText;
class LPopupButton;


class CUtxt_EditorWindow : public CEditorWindow {
public:
	enum { class_ID = 'UTXW' };

							CUtxt_EditorWindow();
							CUtxt_EditorWindow( const SWindowInfo &inWindowInfo );
							CUtxt_EditorWindow( ResIDT inWINDid,
								UInt32 inAttributes, LCommander *inSuperCommander );
							CUtxt_EditorWindow( LStream *inStream );
							~CUtxt_EditorWindow();

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

	virtual void			ActivateSelf();
	virtual void			DeactivateSelf();

	void			InstallText(Handle inTextHandle);

	void			SetLengthField();
				
// 	void			AdjustMenusToSelection();
	
	CUtxt_EditorView *	GetContentsView() const { return mContentsView;}

	virtual Boolean		GetHasStyleResource() { return mHasStyleResource;}
	void				SetHasStyleResource(Boolean inHasStyleResource) {mHasStyleResource = inHasStyleResource;}

protected:
	CUtxt_EditorView *	mContentsView;
	Boolean				mHasStyleResource;
	Boolean				mIsAdjustingMenus;
	LPopupButton *		mSizePopup;
	LPopupButton *		mStylePopup;
	LStaticText *		mLengthField;

	virtual void	FinishCreateSelf();
	
private:

};


