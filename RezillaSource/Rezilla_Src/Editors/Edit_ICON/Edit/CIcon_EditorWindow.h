// ===========================================================================
// CIcon_EditorWindow.h
// 
//                       Created: 2004-12-10 17:23:05
//             Last modification: 2004-12-10 17:23:10
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


class CIcon_EditorDoc;
class CIcon_EditorView;
class CRezObj;
class LPopupButton;
class LStaticText;


class CIcon_EditorWindow : public CEditorWindow {
public:
	enum { class_ID = 'ICNW' };

							CIcon_EditorWindow();
							CIcon_EditorWindow( const SWindowInfo &inWindowInfo );
							CIcon_EditorWindow( ResIDT inWINDid,
								UInt32 inAttributes, LCommander *inSuperCommander );
							CIcon_EditorWindow( LStream *inStream );
							~CIcon_EditorWindow();

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

	void			InstallBitmap(Handle inTextHandle);
	
	void			SetCoordsField(SInt16 inXCoord, SInt16 inYCoord);
	

	CIcon_EditorView *		GetContentsView() const { return mContentsView;}

protected:
	CIcon_EditorView *	mContentsView;
// 	LPopupButton *		mFontPopup;
// 	LPopupButton *		mSizePopup;
// 	LPopupButton *		mStylePopup;
	LStaticText *		mCoordsField;

	/* 
	 * mUnitWidth
	 * mUnitHeigth
	 */

	virtual void	FinishCreateSelf();
	
private:

};


