// ===========================================================================
// CHexEditorActions.h 
//                       Created: 2003-05-29 21:13:13
//             Last modification: 2004-02-22 19:30:01
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// ¬© Copyright: Bernard Desgraupes 2003, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================



#ifndef _H_CHexEditorActions
#define _H_CHexEditorActions
#pragma once

#include "CWEViewActions.h"
#include <LAction.h>
#include <TextEdit.h>

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

protected:
	virtual void		RedoSelf();
	virtual void		UndoSelf();
};



#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif


