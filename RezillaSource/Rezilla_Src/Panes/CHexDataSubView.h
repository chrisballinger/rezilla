// ===========================================================================
//	CHexDataSubView.h
//                       Created: 2003-05-06 06:04:42
//             Last modification: 2005-05-23 11:38:10
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2003-2004, 2005
// All rights reserved.
// ===========================================================================
// A class to handle Waste views going by pair. Any editing action taken on 
// one of them is reflected in the other one.


#ifndef _H_CHexDataSubView
#define _H_CHexDataSubView
#pragma once

#include "CWasteEditView.h"

#include <stdio.h>


#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

class CTxtDataSubView;
class CDualDataView;

// ---------------------------------------------------------------------------

class CHexDataSubView :	public CWasteEditView {
public:
	enum { class_ID = FOUR_CHAR_CODE('HDSV') };

							CHexDataSubView();
							CHexDataSubView(CTxtDataSubView * inSiblingView);
							CHexDataSubView(
											LCommander *		inSuper,
											const SPaneInfo&	inPaneInfo,
											const SViewInfo&	inViewInfo,
											UInt16				inTextAttributes,
											ResIDT				inTextTraitsID,
											Boolean				inWordWrap = false,
											Boolean				inReadOnly = false,
											Boolean				inSelectable = true);
							CHexDataSubView(LStream * inStream );
	virtual					~CHexDataSubView();

	virtual Boolean			ObeyCommand(
									CommandT			inCommand,
									void*				ioParam);

	virtual Boolean			HandleKeyPress(
									const EventRecord& 	inKeyEvent);
	
	virtual void			ScrollImageBy(	SInt32			inHorizDelta,
									SInt32			inVertDelta,
									Boolean			inRefresh);

	virtual	void			InsertContents(Handle inHandle);
	
	virtual	void			InsertContents(
								  const void * inPtr, 
								  SInt32 inByteCount);
	
	virtual	void			CursorMoved(SInt32 inPos);

	virtual void			UserChangedText();
	virtual void			UserChangedText(
									SInt32			inStartPos,
									SInt32			inEndPos,
									SInt32			inBytesCount);

	virtual void			SetDirty(Boolean inDirty);

	void					SyncPositionsWithSibling(SInt32 inStartPos, SInt32 inEndPos);
	void					SyncContentsWithMemory(SInt32 inStartPos, 
													SInt32 inEndPos, 
													SInt32 inBytesCount, 
													SInt32 inLineOffset);

	void					GetCurrHexPos(SInt32 & outHexSelStart, SInt32 & outHexSelEnd);
	SInt32					NearestHexPos(SInt32 inPos);
	SInt32					PosToHexPos(SInt32 inPos);
	SInt32					HexPosToPos(SInt32 inHexPos);
	SInt32					HexPosToLine(SInt32 inHexPos);
	SInt32					GetCurrLine();
	void					GetCurrLines(SInt32 & outfirstLine, SInt32 & outlastLine);
		
	CTxtDataSubView*		GetSiblingView() { return mTxtSiblingView;}
	void					SetSiblingView(CTxtDataSubView* theSiblingView) {mTxtSiblingView = theSiblingView ;}

	CDualDataView*			GetOwnerDualView() { return mOwnerDualView;}
	void					SetOwnerDualView(CDualDataView* theOwnerDualView) {mOwnerDualView = theOwnerDualView ;}
	
	void					SetSynchronizing(Boolean theIsSynchronizing) {mIsSynchronizing = theIsSynchronizing ;}

	SInt32		mEditingPos;
	Boolean		mOneOfTwoInserted;

protected:

		CDualDataView *				mOwnerDualView;
		CTxtDataSubView *			mTxtSiblingView;
		Boolean						mIsSynchronizing;

	virtual void            AdjustCursorPos();
	virtual void			ClickSelf(const SMouseDownEvent & inMouseDown);
};




PP_End_Namespace_PowerPlant

#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
