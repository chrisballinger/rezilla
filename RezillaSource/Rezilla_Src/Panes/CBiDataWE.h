// ===========================================================================
//	CBiDataWE.h
//                       Created: 2004-03-21 12:08:32
//             Last modification: 2004-06-08 20:07:21
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CBiDataWE
#define _H_CBiDataWE
#pragma once

#include "CWasteEditView.h"

#include <stdio.h>

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

class CCompResultWindow;

// ---------------------------------------------------------------------------

class CBiDataWE : public CWasteEditView {
public:
	enum { class_ID = FOUR_CHAR_CODE('BiWV') };

	enum {	
		bidata_hexType = 1,
		bidata_txtType
	};
							CBiDataWE();
							CBiDataWE(
									const CBiDataWE&	inOriginal );
							CBiDataWE(
									LStream*			inStream );
	virtual					~CBiDataWE();

	virtual Boolean			HandleKeyPress(
									const EventRecord& 	inKeyEvent);

	virtual	OSErr			Insert(	const void*			inText,
									SInt32				inLength,
									StScrpHandle		inStyleH = nil,
									Boolean				inRefresh = false );

	virtual	OSErr			Insert(
                                   Str255       inString,
                                   Boolean      inRefresh );

	virtual	void			InsertContents(Handle inHandle);
	
	virtual	void			InsertContents(
								  const void * inPtr, 
								  SInt32 inByteCount);
	
	void					GetCurrCharPos(SInt32 & outCharSelStart, SInt32 & outCharSelEnd);
	SInt32					PosToCharPos(SInt32 inPos);
	SInt32					CharPosToPos(SInt32 inCharPos);
	SInt32					CharPosToLine(SInt32 inCharPos);

	void					GetCurrHexPos(SInt32 & outHexSelStart, SInt32 & outHexSelEnd);
	SInt32					PosToHexPos(SInt32 inPos);
	SInt32					HexPosToPos(SInt32 inHexPos);

	virtual SInt16			GetDataType() { return mDataType;}
	void					SetDataType(SInt16 inDataType) {mDataType = inDataType;}

	virtual CCompResultWindow*	GetCompareWindow() { return mCompareWindow;}
	void						SetCompareWindow(CCompResultWindow* inCompareWindow) {mCompareWindow = inCompareWindow;}

protected:
			SInt16				mDataType;
			CCompResultWindow *	mCompareWindow;
};




PP_End_Namespace_PowerPlant

#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
