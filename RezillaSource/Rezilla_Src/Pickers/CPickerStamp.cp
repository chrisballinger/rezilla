// ===========================================================================
// CPickerStamp.cp					
// 
//                       Created: 2006-02-24 09:49:42
//             Last modification: 2006-03-15 19:15:42
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2006
// All rights reserved.
// ===========================================================================


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CPickerStamp.h"
#include "CPickerWindow.h"
#include "RezillaConstants.h"

#include <LStream.h>
#include <PP_Constants.h>

#include <Icons.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   CPickerStamp							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CPickerStamp::CPickerStamp(
	const SPaneInfo&	inPaneInfo,
	const SViewInfo&	inViewInfo)
	: LView(inPaneInfo, inViewInfo)
{
// 	InitPickerStamp(inWidth, inHeight, inID);
}


// ---------------------------------------------------------------------------
//     ~CPickerStamp							Destructor				  [public]
// ---------------------------------------------------------------------------

CPickerStamp::~CPickerStamp()
{
}


// ---------------------------------------------------------------------------
//   InitPickerStamp
// ---------------------------------------------------------------------------

void 
CPickerStamp::InitPickerStamp(SInt16 inWidth, SInt16 inHeight, ResIDT inID)
{
	ResizeFrameTo(inWidth, inHeight, false);
	ResizeImageTo(inWidth, inHeight, false);
}


// ---------------------------------------------------------------------------
// 	ClickSelf
// ---------------------------------------------------------------------------

void
CPickerStamp::ClickSelf( const SMouseDownEvent & inEvent)
{
	GetSuperView()->ClickSelf(inEvent);
}


// ---------------------------------------------------------------------------
//   DrawSelf														  [public]
// ---------------------------------------------------------------------------

void
CPickerStamp::DrawSelf()
{}


PP_End_Namespace_PowerPlant
