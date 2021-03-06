// ===========================================================================
// CHexEditorActions.h 
//                       Created: 2003-05-29 21:13:13
//             Last modification: 2005-05-27 09:28:55
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2003-2005
// All rights reserved.
// ===========================================================================



#ifndef _H_CHexEditorActions
#define _H_CHexEditorActions
#pragma once

#include "CWEViewActions.h"
#include <LAction.h>
#ifndef __MACH__
#include <TextEdit.h>
#endif

/* #include "CWasteEditView.h" */
#include "WASTE.h"

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

class LCommander;
class LPane;
class CWasteEditView;

// ---------------------------------------------------------------------------
// Basic class for actions concerning text manipulation (cut, paste, type etc.)

// ---------------------------------------------------------------------------
// Classes derived from CWETextActions for each particular action
// ---------------------------------------------------------------------------

class CHexEditorCutAction : public CWEViewCutAction {
public:
						CHexEditorCutAction(
								WEReference	inWERef,
								LCommander*	inTextCommander,
								LPane*		inTextPane);

	virtual				~CHexEditorCutAction() { }

protected:
	virtual void		RedoSelf();
};

// ---------------------------------------------------------------------------

class CHexEditorPasteAction : public CWEViewPasteAction {
public:
						CHexEditorPasteAction(
								WEReference	inWERef,
								LCommander*	inTextCommander,
								LPane*		inTextPane);

	virtual				~CHexEditorPasteAction();

protected:
	virtual void		RedoSelf();
	virtual void		UndoSelf();
};


// ---------------------------------------------------------------------------

class CHexEditorClearAction : public CWEViewClearAction {
public:
						CHexEditorClearAction(
								WEReference	inWERef,
								LCommander*	inTextCommander,
								LPane*		inTextPane);

	virtual				~CHexEditorClearAction() { }

protected:
	virtual void		RedoSelf();
};

// ---------------------------------------------------------------------------

class CHexEditorTypingAction : public CWEViewTypingAction {
public:
						CHexEditorTypingAction(
								WEReference	inWERef,
								LCommander*	inTextCommander,
								LPane*		inTextPane);

	virtual				~CHexEditorTypingAction();

	virtual void		InsertCharacter(Boolean inOneOfTwoInserted);

protected:
	virtual void		RedoSelf();
	virtual void		UndoSelf();
	
private:
	void				RefreshViews();
	
};



#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif

