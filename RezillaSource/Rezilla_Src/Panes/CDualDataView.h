// ===========================================================================
// CDualDataView.h
// 
//                       Created: 2004-06-16 20:13:56
//             Last modification: 2005-06-15 17:58:23
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2004, 2005
// All rights reserved.
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

struct DualGeometry	{
	SInt16	hinst;	// Horinzontal inset
	SInt16	vinst;	// Vertical inset
	SInt16	hsep;	// Horisontal interpanes space
	SInt16	scrlw;	// Scrollbar width
};

enum
{	
	hex_nopane = 0,
	hex_hexpane,
	hex_txtpane
};

class CDualDataView : public LTextGroupBox, public LCommander {
public:
	enum { class_ID = FOUR_CHAR_CODE('DuVw') };

							CDualDataView(
								LStream*		inStream);
							CDualDataView(
										  LCommander *		inSuper,
										  const SPaneInfo&	inPaneInfo,
										  const SViewInfo&	inViewInfo,
										  const DualGeometry& inGeometry,
										  Boolean			inPrimary = true,
										  ResIDT			inTextTraitsID = 0,
										  ConstStringPtr	inTitle = Str_Empty);
							~CDualDataView();

	virtual void	ListenToMessage( MessageT inMessage,void *ioParam);

	virtual Boolean	ObeyCommand(
							CommandT			inCommand,
							void*				ioParam);

	void			InstallBackStoreData(Handle inHandle);
	void			InstallBackStoreData(const void * inPtr, SInt32 inByteCount);

	virtual void	InstallHexContents(Handle inHandle);
	virtual void	InstallHexContents(const void * inPtr, SInt32 inByteCount);

	virtual void	InstallTextContents(Handle inHandle);
	virtual void	InstallTextContents(const void * inPtr, SInt32 inByteCount);
	
	virtual SInt32	InstallContentsFromLine(SInt32 inFromLine);
	
	Boolean			IsDirty();
	virtual void	SetDirty(Boolean inDirty);
	
	virtual void	SetMaxScrollerValue();

	SInt32			HexLineCount();
	SInt32			PosToLine(SInt32 inPos);
	
	void			DisplayBothSelections(SInt32 inStart, SInt32 inEnd);

// 	virtual void	ResetBounds();
	virtual void	AdaptToNewSurroundings();

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
	
	void			CalcPanesPositions(SInt32 & hexLeft, 
									   SInt16 & hexWidth, 
									   SInt16 & hexHeight, 
									   SInt32 & txtLeft, 
									   SInt16 & txtWidth, 
									   SInt16 & txtHeight);
	
	// Accessors
	virtual SInt32		GetCurrFirstLine() { return mCurrFirstLine;}
	void				SetCurrFirstLine(SInt32 theCurrFirstLine) {mCurrFirstLine = theCurrFirstLine ;}

	virtual SInt32		GetCurrentSubView() { return mCurrentSubView;}
	void				SetCurrentSubView(SInt32 inCurrentSubView) {mCurrentSubView = inCurrentSubView;}

	WEReference		GetInMemoryWE() { return mInMemoryWE;}
	void			SetInMemoryWE(WEReference inInMemoryWE) {mInMemoryWE = inInMemoryWE;}

	virtual CHexDataSubView*	GetHexView() { return mHexView;}
	void						SetHexView(CHexDataSubView* inHexDataWE) {mHexView = inHexDataWE;}

	virtual CTxtDataSubView*	GetTxtView() { return mTxtView;}
	void						SetTxtView(CTxtDataSubView* inTxtDataWE) {mTxtView = inTxtDataWE;}

	virtual CSingleScrollBar*	GetScroller() { return mScroller;}
	void						SetScroller(CSingleScrollBar* inScroller) {mScroller = inScroller;}
	
	virtual Boolean		GetSelectingAll() { return mSelectingAll;}
	void				SetSelectingAll(Boolean inSelectingAll) {mSelectingAll = inSelectingAll;}

	void			GetGeometry(DualGeometry& outGeometry) const;
	void			SetGeometry(const DualGeometry& inGeometry);
	
	WindowRef		GetWindowRef() { return mWindowRef;}
	void			SetWindowRef(WindowRef inWindowRef) {mWindowRef = inWindowRef;}


protected:
	CHexDataSubView *	mHexView;
	CTxtDataSubView *	mTxtView;
	CSingleScrollBar *	mScroller;
	WindowRef			mWindowRef;
	WEReference			mInMemoryWE;
	SInt32				mLinesPerPane;
	SInt32				mBytesPerLine;
	SInt32				mCurrFirstLine;
	SInt32				mCurrLocalOffset;
	SInt32				mCurrentSubView;
	DualGeometry		mGeometry;
	Boolean				mSelectingAll;
	
	virtual void		FinishCreateSelf();
	void				Initialize();
	void				DeclareListeners();
};


