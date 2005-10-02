// ===========================================================================
// CHexEditorActions.h 
//                       Created: 2003-05-29 21:13:13
//             Last modification: 2005-05-27 09:28:55
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2003-2005
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

	virtual void		InputCharacter(Boolean inOneOfTwoInserted);

protected:
	virtual void		RedoSelf();
	virtual void		UndoSelf();
	
private:
	void				RefreshViews();
	
};





#endif

