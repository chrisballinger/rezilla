// ===========================================================================
//	CHexDataSubView.h
//                       Created: 2003-05-06 06:04:42
//             Last modification: 2003-05-10 17:02:32
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// ¬© Copyright: Bernard Desgraupes 2003
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
// A class to handle Waste views going by pair. Any editing action taken on 
// one of them is reflected in the other one.


#ifndef _H_CHexDataSubView
#define _H_CHexDataSubView
#pragma once

#include "CHexDataWE.h"


#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

class CTxtDataSubView;
class CHexEditorWindow;

// ---------------------------------------------------------------------------

class CHexDataSubView :	public CHexDataWE {
public:
	enum { class_ID = FOUR_CHAR_CODE('HDSV') };

							CHexDataSubView();
							CHexDataSubView(CTxtDataSubView * inSiblingView);
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

	virtual	void			CursorMoved(SInt32 inPos);

	virtual void			UserChangedText();
	virtual void			UserChangedText(
									SInt32			inStartPos,
									SInt32			inEndPos,
									SInt32			inBytesCount);

	void					SyncPositionsWithSibling(SInt32 inStartPos, SInt32 inEndPos);
	void					SyncContentsWithMemory(SInt32 inStartPos, 
													SInt32 inEndPos, 
													SInt32 inBytesCount, 
													SInt32 inLineOffset);
	void					SyncImageWithSibling(SInt32 inHorizDelta,
													SInt32 inVertDelta,
													Boolean inRefresh);

	CTxtDataSubView*		GetSiblingView() { return mTxtSiblingView;}
	void					SetSiblingView(CTxtDataSubView* theSiblingView) {mTxtSiblingView = theSiblingView ;}

	CHexEditorWindow*		GetEditorWindow() { return mEditorWindow;}
	void					SetEditorWindow(CHexEditorWindow* theEditorWindow) {mEditorWindow = theEditorWindow ;}
	
	void					SetSynchronizing(Boolean theIsSynchronizing) {mIsSynchronizing = theIsSynchronizing ;}
	
protected:

		CHexEditorWindow *			mEditorWindow;
		CTxtDataSubView *			mTxtSiblingView;
		Boolean						mIsSynchronizing;

	virtual void			ClickSelf(const SMouseDownEvent & inMouseDown);
	virtual void			BeTarget();
};




PP_End_Namespace_PowerPlant

#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif

