// ===========================================================================
//	CTxtDataSubView.h
//                       Created: 2003-05-06 06:04:42
//             Last modification: 2003-05-29 10:06:26
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


#ifndef _H_CTxtDataSubView
#define _H_CTxtDataSubView
#pragma once

#include "CTxtDataWE.h"


#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

class CHexDataSubView;
class CHexEditorWindow;

// ---------------------------------------------------------------------------

class CTxtDataSubView :	public CTxtDataWE {
public:
	enum { class_ID = FOUR_CHAR_CODE('TDSV') };

							CTxtDataSubView();
							CTxtDataSubView(CHexDataSubView * inSiblingView);
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
		
	CHexDataSubView*		GetSiblingView() { return mHexSiblingView;}
	void					SetSiblingView(CHexDataSubView* theSiblingView) {mHexSiblingView = theSiblingView ;}

	CHexEditorWindow*		GetEditorWindow() { return mEditorWindow;}
	void					SetEditorWindow(CHexEditorWindow* theEditorWindow) {mEditorWindow = theEditorWindow ;}
	
	void					SetSynchronizing(Boolean theIsSynchronizing) {mIsSynchronizing = theIsSynchronizing ;}

protected:

		CHexEditorWindow *			mEditorWindow;
		CHexDataSubView *			mHexSiblingView;
		Boolean						mIsSynchronizing;
		WELineBreakUPP				mLineBreakUPP;
		WEWordBreakUPP				mWordBreakUPP;

	virtual void			ClickSelf(
									const SMouseDownEvent&	inMouseDown);
};


PP_End_Namespace_PowerPlant

#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif

