// ===========================================================================
// CTEXT_EditorView.h
// 
//                       Created: 2004-06-19 13:23:32k
//             Last modification: 2004-06-19 13:23:49
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CTEXT_EditorView
#define _H_CTEXT_EditorView
#pragma once


#include <LTextEditView.h>


#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

class CTEXT_EditorWindow;

// ---------------------------------------------------------------------------

class CTEXT_EditorView :	public LTextEditView {
public:
	enum { class_ID = FOUR_CHAR_CODE('TXTV') };

							CTEXT_EditorView();
							CTEXT_EditorView(
									const SPaneInfo&	inPaneInfo,
									const SViewInfo&	inViewInfo,
									UInt16				inTextAttributes,
									ResIDT				inTextTraitsID );
							CTEXT_EditorView(
									LStream*			inStream );
	virtual					~CTEXT_EditorView();

	virtual Boolean			HandleKeyPress(
									const EventRecord& 	inKeyEvent);

	virtual Boolean			ObeyCommand(
									CommandT			inCommand,
									void*				ioParam);
	
	virtual void			UserChangedText();
	Boolean					IsDirty() const {return mIsDirty;}
	void					SetDirty( Boolean inDirty ) {mIsDirty = inDirty;}

	CTEXT_EditorWindow*		GetOwnerWindow() { return mOwnerWindow;}
	void					SetOwnerWindow(CTEXT_EditorWindow* inOwnerWindow) {mOwnerWindow = inOwnerWindow;}

	virtual Handle			GetModifiedText();

protected:
		CTEXT_EditorWindow *	mOwnerWindow;
		Boolean					mIsDirty;

	virtual void			ClickSelf(
									const SMouseDownEvent&	inMouseDown);
									

};



PP_End_Namespace_PowerPlant

#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
