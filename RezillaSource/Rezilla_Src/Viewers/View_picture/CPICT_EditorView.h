// ===========================================================================
// CPICT_EditorView.h
// 
//                       Created: 2004-12-06 14:54:09
//             Last modification: 2004-12-07 14:38:09
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#ifndef _H_CPICT_EditorView
#define _H_CPICT_EditorView
#pragma once

#include <LView.h>

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

class CPICT_EditorWindow;

// ---------------------------------------------------------------------------

class CPICT_EditorView : public LView {
public:
	enum { class_ID = FOUR_CHAR_CODE('PICV') };

			
						CPICT_EditorView( LStream *inStream );
								
						CPICT_EditorView( ResIDT inPictureID );

	virtual				~CPICT_EditorView();

	PicHandle		GetPictureH() { return mPictureH;}
	void			SetPictureH(PicHandle inPictureH);

	CPICT_EditorWindow*	GetOwnerWindow() { return mOwnerWindow;}
	void				SetOwnerWindow(CPICT_EditorWindow* inOwnerWindow) {mOwnerWindow = inOwnerWindow;}

protected:
	PicHandle				mPictureH;
	CPICT_EditorWindow *	mOwnerWindow;
	
	virtual void		DrawSelf();

private:
	void				ErasePicture();
	void				AdaptPicture();
};

PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
