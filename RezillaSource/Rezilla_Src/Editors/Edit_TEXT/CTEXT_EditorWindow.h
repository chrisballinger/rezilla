// ===========================================================================
// CTEXT_EditorWindow.h
// 
//                       Created: 2004-06-17 12:46:55
//             Last modification: 2004-06-19 13:57:47
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

#include <LPane.h>
#include <LView.h>
#include <LActiveScroller.h>


class CTEXT_EditorDoc;
class CTEXT_EditorView;
class CRezObj;
class LPopupButton;
class LStaticText;


class CTEXT_EditorWindow : public CEditorWindow {
public:
	enum { class_ID = 'TXTW' };

							CTEXT_EditorWindow();
							CTEXT_EditorWindow( const SWindowInfo &inWindowInfo );
							CTEXT_EditorWindow( ResIDT inWINDid,
								UInt32 inAttributes, LCommander *inSuperCommander );
							CTEXT_EditorWindow( LStream *inStream );
							~CTEXT_EditorWindow();

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

	void			InstallText(Handle inTextHandle, StScrpHandle inScrapHandle);
	Handle			ReadValues();
	void			SetLengthField();
	
	Boolean			IsDirty();
		
	void			InstallDefaults();
	void			InstallReadOnlyIcon();
	void			AdjustMenusToSelection();
	
	CTEXT_EditorView *		GetContentsView() const { return mContentsView;}

// 	virtual SInt32		GetCurrentSubView() { return mCurrentSubView;}
// 	void				SetCurrentSubView(SInt32 inCurrentSubView) {mCurrentSubView = inCurrentSubView;}

protected:
	CTEXT_EditorView *	mContentsView;
	LActiveScroller *	mContentsScroller;
	Boolean				mHasStyleResource;
	Boolean				mIsAdjustingMenus;
	LPopupButton *		mFontPopup;
	LPopupButton *		mSizePopup;
	LPopupButton *		mStylePopup;
	LStaticText *		mLengthField;
	

	virtual void	FinishCreateSelf();
	
private:

};


