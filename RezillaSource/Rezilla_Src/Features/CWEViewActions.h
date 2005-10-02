// ===========================================================================
//	CWEViewActions.h
//	
//                       Created: 2001-09-08 07:05:27
//             Last modification: 2005-05-24 15:58:41
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2001-2005
// All rights reserved.
// $Date$
// $Revision$
//	
// This file is part of the CWasteEditView package vs-1.8
// ===========================================================================


#ifndef _H_CWEViewActions
#define _H_CWEViewActions
#pragma once

#include <LAction.h>
#include <TextEdit.h>

/* #include "CWasteEditView.h" */
#include "WASTE.h"



PP_Begin_Namespace_PowerPlant

class LCommander;
class LPane;
class CWasteEditView;


/************************************************************
*                                                           *
*   Basic class for actions concerning text manipulation    *
*           (cut, paste, clear, typing)                     *
*                                                           *
************************************************************/

class CWETextActions : public LAction {
public:
						CWETextActions(
								SInt16		inDescriptionIndex,
								MessageT	inActionCommand,
								WEReference	inWERef,
								LCommander*	inTextCommander,
								LPane*		inTextPane,
								bool		inAlreadyDone = false);

	virtual				~CWETextActions();

	virtual void		Redo();
	virtual void		Undo();

	virtual Boolean		CanRedo() const;
	virtual Boolean		CanUndo() const;

	virtual	Boolean		IsPostable() const;

protected:
	LCommander*			mTextCommander;
	CWasteEditView*		mWEView;
	WEReference			mWERef;
	MessageT			mActionCommand;

	Handle				mDeletedTextH;
	SInt32				mDeletedTextLen;
	SInt32				mSelStart;
	SInt32				mSelEnd;
	Handle				mDeletedStyleH;

	virtual void		UndoSelf();
};

// ---------------------------------------------------------------------------
//     Classes derived from CWETextActions for each particular action
// ---------------------------------------------------------------------------

class CWEViewCutAction : public CWETextActions {
public:
						CWEViewCutAction(
								WEReference	inWERef,
								LCommander*	inTextCommander,
								LPane*		inTextPane);

	virtual				~CWEViewCutAction() { }

protected:
	virtual void		RedoSelf();
};

// ---------------------------------------------------------------------------

class CWEViewPasteAction : public CWETextActions {
public:
						CWEViewPasteAction(
								WEReference	inWERef,
								LCommander*	inTextCommander,
								LPane*		inTextPane);

	virtual				~CWEViewPasteAction();

protected:
	Handle				mPastedTextH;
	Handle				mPastedStyleH;

	virtual void		RedoSelf();
	virtual void		UndoSelf();
};


// ---------------------------------------------------------------------------

class CWEViewClearAction : public CWETextActions {
public:
						CWEViewClearAction(
								WEReference	inWERef,
								LCommander*	inTextCommander,
								LPane*		inTextPane);

	virtual				~CWEViewClearAction() { }

protected:
	virtual void		RedoSelf();
};

// ---------------------------------------------------------------------------

class CWEViewTypingAction : public CWETextActions {
public:
						CWEViewTypingAction(
								WEReference	inWERef,
								LCommander*	inTextCommander,
								LPane*		inTextPane);

	virtual				~CWEViewTypingAction();

	virtual void		Reset();
	virtual void		InputCharacter();
	virtual void		BackwardErase();
	virtual void		ForwardErase();

protected:
	Handle				mTypedTextH;
	Handle				mTypedStyleH;
	SInt32				mTypingStart;
	SInt32				mTypingEnd;

	virtual void		RedoSelf();
	virtual void		UndoSelf();
};


/****************************************************
*                                                   *
*   Basic class for actions concerning the style    *
*       (font, size, face, align, color)            *
*                                                   *
****************************************************/

class CWEStyleActions : public LAction {
public:
						CWEStyleActions(
								SInt16		inDescriptionIndex,
								LCommander*	inCommander,
								LPane*		inPane,
								bool		inAlreadyDone = false);

	virtual				~CWEStyleActions();

	virtual Boolean		CanRedo() const;
	virtual Boolean		CanUndo() const;

protected:
	LCommander*			mCommander;
	CWasteEditView*		mWEView;

	SInt32				mSelStart;
	SInt32				mSelEnd;
};

// ---------------------------------------------------------------------------
//     Classes derived from CWEStyleActions for each particular action
// ---------------------------------------------------------------------------

class CWEViewFontAction : public CWEStyleActions {
public:
						CWEViewFontAction(
								SInt16		inFont,
								LCommander*	inCommander,
								LPane*		inPane,
								bool		inAlreadyDone = false);

						CWEViewFontAction(
								Str255		inFontName,
								LCommander*	inCommander,
								LPane*		inPane,
								bool		inAlreadyDone = false);

	virtual				~CWEViewFontAction();

protected:
	SInt16				mFont;
	SInt16				mSavedFont;

	virtual	void		RedoSelf();
	virtual void		UndoSelf();
};

// ---------------------------------------------------------------------------

class CWEViewSizeAction : public CWEStyleActions {
public:
						CWEViewSizeAction(
								SInt16		inSize,
								LCommander*	inCommander,
								LPane*		inPane,
								bool		inAlreadyDone = false);

	virtual				~CWEViewSizeAction();

protected:
	SInt16				mSize;
	SInt16				mSavedSize;

	virtual	void		RedoSelf();
	virtual void		UndoSelf();
};

// ---------------------------------------------------------------------------

class CWEViewFaceAction : public CWEStyleActions {
public:
						CWEViewFaceAction(
								Style		inFace,
								bool		inToggle,
								LCommander*	inCommander,
								LPane*		inPane,
								bool		inAlreadyDone = false);

	virtual				~CWEViewFaceAction();

protected:
	Style				mFace;
	Style				mSavedFace;
	bool				mToggle;

	virtual	void		RedoSelf();
	virtual void		UndoSelf();
};

// ---------------------------------------------------------------------------

class CWEViewAlignAction : public CWEStyleActions {
public:
						CWEViewAlignAction(
								WEAlignment	inAlign,
								LCommander*	inCommander,
								LPane*		inPane,
								bool		inAlreadyDone = false);

	virtual				~CWEViewAlignAction();

protected:
	WEAlignment			mAlign;
	WEAlignment			mSavedAlign;

	virtual	void		RedoSelf();
	virtual	void		UndoSelf();
};

// ---------------------------------------------------------------------------

class CWEViewColorAction : public CWEStyleActions {
public:
						CWEViewColorAction(
								const RGBColor&	inColor,
								LCommander*		inCommander,
								LPane*			inPane,
								bool			inAlreadyDone = false);

	virtual				~CWEViewColorAction();

protected:
	RGBColor			mColor;
	RGBColor			mSavedColor;

	virtual	void		RedoSelf();
	virtual	void		UndoSelf();
};

PP_End_Namespace_PowerPlant




#endif

