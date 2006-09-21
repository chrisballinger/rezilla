// ===========================================================================
// CPickerStamp.cp					
// 
//                       Created: 2006-02-24 09:49:42
//             Last modification: 2006-09-20 08:35:48
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
	   CPickerView *	inParent,
	   const SPaneInfo&	inPaneInfo,
	   const SViewInfo&	inViewInfo)
	: LView(inPaneInfo, inViewInfo)
{
	mParent = inParent;
}


// ---------------------------------------------------------------------------
//     ~CPickerStamp							Destructor				  [public]
// ---------------------------------------------------------------------------

CPickerStamp::~CPickerStamp()
{
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
// Install a generic drawing when no dedicated subclass is available: if
// the resource has a name, display it, otherwise display a generic icon
// 
// 			Rect	frame;
// 			CalcLocalFrameRect(frame);
// 			::PenNormal();
// 
// 			Pattern		ltGrayPat;
// 			::MacFillRect(&frame, UQDGlobals::GetLightGrayPat(&ltGrayPat));
// 
// 			::MacFrameRect(&frame);

void
CPickerStamp::DrawSelf()
{
	short theID = GetSuperView()->GetPaneID();
	Rect	frame;
	CalcLocalFrameRect(frame);
	StColorPenState::Normalize();
	

}


PP_End_Namespace_PowerPlant
