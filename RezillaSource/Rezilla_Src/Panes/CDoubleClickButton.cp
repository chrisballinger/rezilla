// ===========================================================================
// CDoubleClickButton.cp
// 
//                       Created: 2005-01-01 20:40:10
//             Last modification: 2005-01-01 20:54:28
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
// Subclass only to broadcast a specific message when the button receives 
// a double-click.

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CDoubleClickButton.h"

#include <LControlImp.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//	¥ CDoubleClickButton						Stream Constructor		  [public]
// ---------------------------------------------------------------------------

CDoubleClickButton::CDoubleClickButton(
	LStream*	inStream,
	ClassIDT	inImpID)

	: LBevelButton(inStream, inImpID)
{}


// ---------------------------------------------------------------------------
//	¥ CDoubleClickButton							Parameterized Constructor [public]
// ---------------------------------------------------------------------------
//	Constructor for a BevelButton with no menu

CDoubleClickButton::CDoubleClickButton(
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
		ClassIDT		inImpID)

	: LBevelButton(inPaneInfo, inValueMessage, inBevelProc, inBehavior,
	inContentType, inContentResID, inTextTraits, inTitle, inInitialValue,
	inTitlePlacement, inTitleAlignment, inTitleOffset, inGraphicAlignment,
	inGraphicOffset, inImpID)
{
	mDoubleClickMessage = inDblClickMessage;
}


// ---------------------------------------------------------------------------
//	¥ CDoubleClickButton						Parameterized Constructor [public]
// ---------------------------------------------------------------------------
//	Constructor for a BevelButton with a Menu

CDoubleClickButton::CDoubleClickButton(
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
		ClassIDT		inImpID)

	: LBevelButton(inPaneInfo, inValueMessage, inBevelProc, inMenuID,
	inMenuPlacement, inContentType, inContentResID, inTextTraits, inTitle,
	inInitialValue, inTitlePlacement, inTitleAlignment, inTitleOffset,
	inGraphicAlignment, inGraphicOffset, inCenterPopupGlyph, inImpID)
{
	mDoubleClickMessage = inDblClickMessage;
}


// ---------------------------------------------------------------------------
//	¥ ~CDoubleClickButton						Destructor				  [public]
// ---------------------------------------------------------------------------

CDoubleClickButton::~CDoubleClickButton()
{
}


#pragma mark -


// ---------------------------------------------------------------------------
//	¥ ClickSelf
// ---------------------------------------------------------------------------
//	Broadcast message for a double-click on the button

void
CDoubleClickButton::ClickSelf( const SMouseDownEvent& inMouseDown )
{
	if (GetClickCount() == 1) {
		// Call inherited
		LBevelButton::ClickSelf(inMouseDown);
	} else if (GetClickCount() == 2) {
		if (mDoubleClickMessage != msg_Nothing) {
			BroadcastMessage(mDoubleClickMessage, (void*) this);
		}
	}
}



PP_End_Namespace_PowerPlant

