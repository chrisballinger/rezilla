// ===========================================================================
// 	CBroadcasterTableView.h			
// 
//                       Created : 2002-05-14 20:00:17
//             Last modification : 2004-03-02 08:35:55
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@easyconnect.fr>
// www : <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2002-2003, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CBroadcasterTableView
#define _H_CBroadcasterTableView
#pragma once



#include <LTableView.h>

#if PP_Uses_Pragma_Import
	#pragma import on
#endif


class CBroadcasterTableView : 	public LTableView,
							public LBroadcaster {
public:
	enum				{ class_ID = FOUR_CHAR_CODE('BTbv') };
	
						CBroadcasterTableView(
								LStream				*inStream);
	virtual				~CBroadcasterTableView();
	
	virtual StyleParameter		GetFaceStyle() { return mFaceStyle;}
	void				SetFaceStyle(StyleParameter inFaceStyle) {mFaceStyle = inFaceStyle;}

protected:
	MessageT		mValueMessage;
	StyleParameter	mFaceStyle;
	
	virtual void		ClickCell(
								const STableCell&		inCell,
								const SMouseDownEvent&	inMouseDown);

	virtual void		DrawCell(
								const STableCell	&inCell,
								const Rect			&inLocalRect);
									
	virtual void		HiliteCellActively(
								const STableCell	&inCell,
								Boolean				inHilite);
	virtual void		HiliteCellInactively(
								const STableCell	&inCell,
								Boolean				inHilite);


};

#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif