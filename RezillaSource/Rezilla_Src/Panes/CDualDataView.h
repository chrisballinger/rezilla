// ===========================================================================
// CDualDataView.h
// 
//                       Created: 2004-06-16 20:13:56
//             Last modification: 2004-06-17 01:17:15
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
#include "WASTE.h"

#include <LTextGroupBox.h>
#include <LCommander.h>

class CHexEditorDoc;
class CHexDataSubView;
class CTxtDataSubView;
class CRezObj;
class CSingleScrollBar;

enum
{	
	hex_nopane = 0,
	hex_hexpane,
	hex_txtpane
};

class CDualDataView : public LTextGroupBox, LCommander {
public:
	enum { class_ID = 'DuVw' };

							CDualDataView(
								LStream*		inStream);
							CDualDataView(
								const SPaneInfo&	inPaneInfo,
								const SViewInfo&	inViewInfo,
								Boolean				inPrimary = true,
								ResIDT				inTextTraitsID = 0,
								ConstStringPtr		inTitle = Str_Empty);
							~CDualDataView();

	virtual void	ListenToMessage( MessageT inMessage,void *ioParam);

	virtual Boolean	ObeyCommand(
							CommandT			inCommand,
							void*				ioParam);

	virtual void	InstallBackStoreData(Handle inHandle);

	virtual void	InstallHexContents(Handle inHandle);
	virtual void	InstallHexContents(const void * inPtr, SInt32 inByteCount);

	virtual void	InstallTextContents(Handle inHandle);
	virtual void	InstallTextContents(const void * inPtr, SInt32 inByteCount);
	
	virtual SInt32	InstallContentsFromLine(SInt32 inFromLine);
	
	Boolean			IsDirty();
	
	virtual void	SetMaxScrollerValue();

	SInt32			HexLineCount();
	SInt32			PosToLine(SInt32 inPos);
	
	void			DisplayBothSelections(SInt32 inStart, SInt32 inEnd);

	virtual void	ResetBounds();

	SInt32			CountLines();
	SInt32			GetPaneCount(SInt16 whichValue);
	void			GetCurrLines(SInt32 & outfirstLine, SInt32 & outlastLine);
	void			GetCurrHexPos(SInt32 & outHexSelStart, SInt32 & outHexSelEnd);

	void			GetAbsoluteRange(SInt32 & outStart, SInt32 & outEnd);

	void			InstallSubViews(CHexDataSubView * inHexDataWE, 
								CTxtDataSubView * inTxtDataWE, 
								CSingleScrollBar * inScroller,
								Boolean inReadOnly);
	
	void			ResizeDataPanes();
	void			UpdatePaneCounts();
	
	// Accessors
	virtual SInt32		GetCurrFirstLine() { return mCurrFirstLine;}
	void				SetCurrFirstLine(SInt32 theCurrFirstLine) {mCurrFirstLine = theCurrFirstLine ;}

	virtual SInt32		GetCurrentSubView() { return mCurrentSubView;}
	void				SetCurrentSubView(SInt32 inCurrentSubView) {mCurrentSubView = inCurrentSubView;}

	WEReference		GetInMemoryWasteRef() { return mInMemoryWasteRef;}
	void			SetInMemoryWasteRef(WEReference inInMemoryWasteRef) {mInMemoryWasteRef = inInMemoryWasteRef;}

	virtual CHexDataSubView*	GetHexView() { return mHexView;}
	void						SetHexView(CHexDataSubView* inHexDataWE) {mHexView = inHexDataWE;}

	virtual CTxtDataSubView*	GetTxtView() { return mTxtView;}
	void						SetTxtView(CTxtDataSubView* inTxtDataWE) {mTxtView = inTxtDataWE;}

	virtual CSingleScrollBar*	GetScroller() { return mScroller;}
	void						SetScroller(CSingleScrollBar* inScroller) {mScroller = inScroller;}
	
	virtual Boolean		GetSelectingAll() { return mSelectingAll;}
	void				SetSelectingAll(Boolean inSelectingAll) {mSelectingAll = inSelectingAll;}

protected:
	CHexDataSubView *	mHexView;
	CTxtDataSubView *	mTxtView;
	CSingleScrollBar *	mScroller;
	WEReference			mInMemoryWasteRef;
	SInt32				mLinesPerPane;
	SInt32				mBytesPerLine;
	SInt32				mCurrFirstLine;
	SInt32				mCurrLocalOffset;
	SInt32				mCurrentSubView;
	Boolean				mSelectingAll;
	
	virtual void		FinishCreateSelf();
	void				Initialize();
};


