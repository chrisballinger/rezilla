// ===========================================================================
// CUtxt_EditorView.h
// 
//                       Created: 2004-12-08 18:21:21
//             Last modification: 2004-12-09 07:10:07
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CUtxt_EditorView
#define _H_CUtxt_EditorView
#pragma once


#include <LTextEditView.h>
#include <LMLTEPane.h>


#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

class CUtxt_EditorWindow;

// ---------------------------------------------------------------------------

class CUtxt_EditorView :	public LMLTEPane {
public:
	enum { class_ID = FOUR_CHAR_CODE('UTXV') };

								CUtxt_EditorView();
								CUtxt_EditorView( LStream* inStream );
		virtual					~CUtxt_EditorView();

	virtual Boolean			HandleKeyPress(
									const EventRecord& 	inKeyEvent);

	virtual Boolean			ObeyCommand(
									CommandT			inCommand,
									void*				ioParam);
	
// 	virtual void			UserChangedText();

	CUtxt_EditorWindow*		GetOwnerWindow() { return mOwnerWindow;}
	void					SetOwnerWindow(CUtxt_EditorWindow* inOwnerWindow) {mOwnerWindow = inOwnerWindow;}

	virtual Handle			GetModifiedText();

protected:
		CUtxt_EditorWindow *	mOwnerWindow;

// 	virtual void			ClickSelf(
// 									const SMouseDownEvent&	inMouseDown);
									

};



PP_End_Namespace_PowerPlant

#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
