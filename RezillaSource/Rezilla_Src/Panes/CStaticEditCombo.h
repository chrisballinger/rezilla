// ===========================================================================
// CStaticEditCombo.h
// 
//                       Created: 2005-03-17 09:36:42
//             Last modification: 2005-03-17 09:36:42
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CStaticEditCombo
#define _H_CStaticEditCombo
#pragma once

#include <LStaticText.h>
#include <LEditText.h>

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

class	LString;

// ---------------------------------------------------------------------------

class CStaticEditCombo : public LEditText {
public:
	enum { class_ID		= FOUR_CHAR_CODE('SEtx'),
		   imp_class_ID	= FOUR_CHAR_CODE('ietx') };

						CStaticEditCombo(
								LStream*		inStream,
								ClassIDT		inImpID = imp_class_ID);

						CStaticEditCombo(
								const SPaneInfo&	inPaneInfo,
								LCommander*			inSuperCommander,
								ConstStringPtr		inInitialText,
								ResIDT				inTextTraitsID,
								MessageT			inMessage,
								SInt16				inMaxChars,
								UInt8				inAttributes,
								TEKeyFilterFunc		inKeyFilter,
								bool				inPasswordField = false,
								ClassIDT			inImpID = imp_class_ID);

	virtual				~CStaticEditCombo();

	virtual Boolean		HandleKeyPress( const EventRecord& inKeyEvent );
	
	
protected:
	LStaticText *			mStaticText;
	Boolean					mIsEditing;

	virtual void		ClickSelf(const SMouseDownEvent &inMouseDown);
	
private:
	void				InitCombo();
};

PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
