// ===========================================================================
// CCompResultWindow.h				
// 
//                       Created: 2004-03-02 14:18:16
//             Last modification: 2004-06-06 21:35:34
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
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
	enum { class_ID = 'RcrW' };

	enum {	
		compare_undefinedTbl = 0,
		compare_onlyinOldTbl,
		compare_onlyinNewTbl,
		compare_differTbl
	};

	enum {	
		compare_displayAsHex = 0,
		compare_displayAsTxt
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

	void			DoClose();

	virtual Boolean	ObeyCommand(
							CommandT			inCommand,
							void*				ioParam);

	Boolean			IsDirty();
	
	void			FillTableView( TArray<CRezTypId *> inList, SInt16 inWhichList);
	
	virtual void	DoSetBounds(const Rect& inBounds);

	SInt32			GetPaneCount(SInt16 whichValue);
	
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
	SInt32					mBytesPerPane;
	
	void				NameNewCompWindow();
	virtual void		SetMaxScrollerValue();
	SInt32				LineCount();
	virtual void		FinishCreateSelf();
	void				InsertContentsFromLine(SInt32 inFromLine);
	void				EraseHexPanes();
	void				ResizeDataPanes();
	void				UpdatePaneCounts();
};


