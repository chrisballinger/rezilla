// ===========================================================================
// CCompResultWindow.h				
// 
//                       Created: 2004-03-02 14:18:16
//             Last modification: 2005-05-12 07:20:12
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2004, 2005
// All rights reserved.
// ===========================================================================

#pragma once

#include <LWindow.h>
#include <LListener.h>

class CRezObj;
class CRezCompare;
class CRezTypId;
class CBiDataWE;
class CSingleScrollBar;
class CBroadcasterTableView;

enum
{	
	compare_oldhexpane = 0,
	compare_newhexpane
};

// 'RcrW': Rez comparison result window

class CCompResultWindow : public LWindow, public LListener {
public:
	enum { class_ID = FOUR_CHAR_CODE('RcrW') };

	enum {	
		compare_undefinedTbl = 0,
		compare_onlyinOldTbl,
		compare_onlyinNewTbl,
		compare_differTbl
	};

							CCompResultWindow();
							CCompResultWindow( const SWindowInfo &inWindowInfo );
							CCompResultWindow( ResIDT inWINDid,
								UInt32 inAttributes, LCommander *inSuperCommander );
							CCompResultWindow( LStream *inStream );
							~CCompResultWindow();

	virtual void	ListenToMessage( MessageT inMessage,void *ioParam);

	virtual void	FindCommandStatus(
								CommandT			inCommand,
								Boolean&			outEnabled,
								Boolean&			outUsesMark,
								UInt16&				outMark,
								Str255				outName);

// 	void			DoClose();

	Boolean			IsDirty();
	
	void			FillTableView( TArray<CRezTypId *> inList, SInt16 inWhichList);
	
	virtual void	DoSetBounds(const Rect& inBounds);

	SInt32			GetPaneCount(SInt16 whichValue);
	
	CRezCompare*	GetRezCompare() { return mRezCompare;}

	
protected:
	CRezCompare *			mRezCompare;
	CBiDataWE *				mOldRezDataWE;
	CBiDataWE *				mNewRezDataWE;
	Handle					mOldData;
	Handle					mNewData;
	CSingleScrollBar *		mScroller;
	CBroadcasterTableView *	mOnlyOldTable;
	CBroadcasterTableView *	mOnlyNewTable;
	CBroadcasterTableView *	mDifferTable;
	SInt16					mActiveTable;
	SInt16					mDisplayDataFormat;
	SInt32					mLinesPerPane;
	SInt32					mHexBytesPerLine;
	SInt32					mTxtBytesPerLine;

	void				NameNewCompWindow();
	virtual void		SetMaxScrollerValue();
	SInt32				LineCount();
	virtual void		FinishCreateSelf();
	void				InsertContentsFromLine(SInt32 inFromLine);
	void				EraseHexPanes();
	void				ResizeDataPanes();
	void				UpdatePaneCounts();
};


