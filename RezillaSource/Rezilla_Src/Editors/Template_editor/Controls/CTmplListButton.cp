// ===========================================================================
// CTmplListButton.cp
// 
//                       Created: 2004-06-28 08:48:08
//             Last modification: 2004-06-28 08:48:22
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// ===========================================================================
// Subclass only to broadcast the pointer to "this" instead of the value of
// the control.

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CTmplListButton.h"
#include <LControlImp.h>
#include <LStream.h>
#include <LView.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   CTmplListButton							Stream Constructor		  [public]
// ---------------------------------------------------------------------------

CTmplListButton::CTmplListButton(
	LStream*	inStream,
	ClassIDT	inImpID)

	: LPushButton(inStream, inImpID)
{}


// ---------------------------------------------------------------------------
//   CTmplListButton							Parameterized Constructor [public]
// ---------------------------------------------------------------------------

CTmplListButton::CTmplListButton(
	const SPaneInfo&	inPaneInfo,
	MessageT			inValueMessage,
	ConstStringPtr		inTitle,
	SInt16				inKind,
	ResIDT				inTextTraitsID,
	SInt16				inCicnID,
	ClassIDT			inImpID)

	: LPushButton(inPaneInfo, inValueMessage, inTitle, inKind,
						inTextTraitsID, inCicnID, inImpID)
{}


// ---------------------------------------------------------------------------
//     ~CTmplListButton							Destructor				  [public]
// ---------------------------------------------------------------------------

CTmplListButton::~CTmplListButton()
{
}


// ---------------------------------------------------------------------------
//   BroadcastValueMessage										   [protected]
// ---------------------------------------------------------------------------
//	Send our value message with our value as the parameter

void
CTmplListButton::BroadcastValueMessage()
{
	if (mValueMessage != msg_Nothing) {
		BroadcastMessage(mValueMessage, this);
	}
}



PP_End_Namespace_PowerPlant
