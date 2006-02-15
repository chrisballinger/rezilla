// ===========================================================================
//	CTxtDataSubView.h
//                       Created: 2003-05-06 06:04:42
//             Last modification: 2005-05-23 11:37:55
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2003-2004, 2005
// All rights reserved.
// ===========================================================================
// A class to handle Waste views going by pair. Any editing action taken on 
// one of them is reflected in the other one.


#ifndef _H_CTxtDataSubView
#define _H_CTxtDataSubView
#pragma once

#include "CWasteEditView.h"

#include <stdio.h>

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

class CHexDataSubView;
class CDualDataView;

// ---------------------------------------------------------------------------

class CTxtDataSubView :	public CWasteEditView {
public:
	enum { class_ID = FOUR_CHAR_CODE('TDSV') };

							CTxtDataSubView();
							CTxtDataSubView(CHexDataSubView * inSiblingView);
							CTxtDataSubView(
											LCommander *		inSuper,
											const SPaneInfo&	inPaneInfo,
											const SViewInfo&	inViewInfo,
											UInt16				inTextAttributes,
											ResIDT				inTextTraitsID,
											Boolean				inWordWrap = false,
											Boolean				inReadOnly = false,
											Boolean				inSelectable = true);
							CTxtDataSubView(LStream * inStream );
	virtual					~CTxtDataSubView();

	virtual Boolean			ObeyCommand(
									CommandT			inCommand,
									void*				ioParam);
	
	virtual Boolean			HandleKeyPress(
									const EventRecord& 	inKeyEvent);
	
	virtual void			ScrollImageBy(
									SInt32				inLeftDelta,
									SInt32				inTopDelta,
									Boolean				inRefresh);

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
		
	void					GetCurrCharPos(SInt32 & outCharSelStart, SInt32 & outCharSelEnd);
	SInt32					NearestCharPos(SInt32 inPos);
	SInt32					PosToCharPos(SInt32 inPos);
	SInt32					CharPosToPos(SInt32 inCharPos);
	SInt32					CharPosToLine(SInt32 inCharPos);
	SInt32					GetCurrLine();
	void					GetCurrLines(SInt32 & outfirstLine, SInt32 & outlastLine);
		
	CHexDataSubView*		GetSiblingView() { return mHexSiblingView;}
	void					SetSiblingView(CHexDataSubView* theSiblingView) {mHexSiblingView = theSiblingView ;}

	CDualDataView*			GetOwnerDualView() { return mOwnerDualView;}
	void					SetOwnerDualView(CDualDataView* theOwnerDualView) {mOwnerDualView = theOwnerDualView ;}
	
	void					SetSynchronizing(Boolean theIsSynchronizing) {mIsSynchronizing = theIsSynchronizing ;}

protected:

		CDualDataView *				mOwnerDualView;
		CHexDataSubView *			mHexSiblingView;
		Boolean						mIsSynchronizing;
		WELineBreakUPP				mLineBreakUPP;
		WEWordBreakUPP				mWordBreakUPP;

	virtual void            AdjustCursorPos();
	virtual void			ClickSelf(const SMouseDownEvent&	inMouseDown);
};


PP_End_Namespace_PowerPlant

#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
