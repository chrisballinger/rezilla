// ===========================================================================
// CDoubleClickButton.h
// 
//                       Created: 2005-01-01 20:40:10
//             Last modification: 2005-01-01 20:53:27
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#ifndef _H_CDoubleClickButton
#define _H_CDoubleClickButton
#pragma once


#if PP_Uses_Pragma_Import
	#pragma import on
#endif

#include <LBevelButton.h>

class CDoubleClickButton;


PP_Begin_Namespace_PowerPlant

// ---------------------------------------------------------------------------

class	CDoubleClickButton : public LBevelButton {
public:
	enum { class_ID		= FOUR_CHAR_CODE('Dcbb'),
		   imp_class_ID	= FOUR_CHAR_CODE('ibbt') };

						CDoubleClickButton(
								LStream*		inStream,
								ClassIDT		inImpID = imp_class_ID);

						CDoubleClickButton(
								const SPaneInfo	&inPaneInfo,
								MessageT		inValueMessage,
								MessageT		inDblClickMessage,
								SInt16			inBevelProc,
								SInt16			inBehavior,
								SInt16			inContentType,
								SInt16			inContentResID,
								ResIDT			inTextTraits,
								ConstStringPtr	inTitle,
								SInt16			inInitialValue,
								SInt16			inTitlePlacement,
								SInt16			inTitleAlignment,
								SInt16			inTitleOffset,
								SInt16			inGraphicAlignment,
								Point			inGraphicOffset,
								ClassIDT		inImpID = imp_class_ID);

						CDoubleClickButton(
								const SPaneInfo	&inPaneInfo,
								MessageT		inValueMessage,
								MessageT		inDblClickMessage,
								SInt16			inBevelProc,
								ResIDT			inMenuID,
								SInt16			inMenuPlacement,
								SInt16			inContentType,
								SInt16			inContentResID,
								ResIDT			inTextTraits,
								ConstStringPtr	inTitle,
								SInt16			inInitialValue,
								SInt16			inTitlePlacement,
								SInt16			inTitleAlignment,
								SInt16			inTitleOffset,
								SInt16			inGraphicAlignment,
								Point			inGraphicOffset,
								Boolean			inCenterPopupGlyph,
								ClassIDT		inImpID = imp_class_ID);

	virtual				~CDoubleClickButton();


	MessageT			GetDoubleClickMessage() const { return mDoubleClickMessage; }
	void				SetDoubleClickMessage(MessageT inMessage) { mDoubleClickMessage = inMessage; }
	
protected:
	MessageT		mDoubleClickMessage;

	virtual void		ClickSelf(const SMouseDownEvent	&inMouseDown);

};



PP_End_Namespace_PowerPlant

#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
