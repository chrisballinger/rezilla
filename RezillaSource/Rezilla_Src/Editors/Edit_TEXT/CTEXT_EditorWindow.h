// ===========================================================================
// CTEXT_EditorWindow.h
// 
//                       Created: 2004-06-17 12:46:55
//             Last modification: 2005-01-27 18:11:58
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004-2005
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
class LStaticText;


class CTEXT_EditorWindow : public CEditorWindow {
public:
	enum { class_ID = FOUR_CHAR_CODE('TXTW') };

							CTEXT_EditorWindow();
							CTEXT_EditorWindow( const SWindowInfo &inWindowInfo );
							CTEXT_EditorWindow( ResIDT inWINDid,
								UInt32 inAttributes, LCommander *inSuperCommander );
							CTEXT_EditorWindow( LStream *inStream );
							~CTEXT_EditorWindow();

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

	void			InstallText(Handle inTextHandle, StScrpHandle inScrapHandle);

	void			SetLengthField();
	
	CTEXT_EditorView *		GetContentsView() const { return mContentsView;}

	virtual Boolean		GetHasStyleResource() { return mHasStyleResource;}
	void				SetHasStyleResource(Boolean inHasStyleResource) {mHasStyleResource = inHasStyleResource;}

	static LMenu		*sTextFontMenu, 
						*sTextSizeMenu, 
						*sTextStyleMenu;

protected:
	CTEXT_EditorView *	mContentsView;
	Boolean				mHasStyleResource;
	Boolean				mIsAdjustingMenus;
	LStaticText *		mLengthField;
						
	virtual void	FinishCreateSelf();
	virtual void	PutOnDuty(LCommander *inNewTarget);
	virtual void	TakeOffDuty();
	virtual void	RemoveTextMenus();

private:

};


