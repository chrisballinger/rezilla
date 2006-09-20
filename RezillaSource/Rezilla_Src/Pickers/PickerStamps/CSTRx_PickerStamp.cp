// ===========================================================================
// 	CSTRx_PickerStamp.cp
// 
//                       Created : 2006-02-25 17:40:43
//             Last modification : 2006-09-20 08:50:41
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@users.sourceforge.net>
// www : <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2006
// All rights reserved.
// ===========================================================================


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CSTRx_PickerStamp.h"
#include "CPickerView.h"
#include "UResources.h"


PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   CSTRx_PickerStamp							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CSTRx_PickerStamp::CSTRx_PickerStamp(
									CPickerView *		inParent,
									const SPaneInfo&	inPaneInfo,
									const SViewInfo&	inViewInfo)
	: CPickerStamp(inParent, inPaneInfo, inViewInfo)
{
}


// ---------------------------------------------------------------------------
//   ~CSTRx_PickerStamp							Destructor				  [public]
// ---------------------------------------------------------------------------

CSTRx_PickerStamp::~CSTRx_PickerStamp()
{
}


// ---------------------------------------------------------------------------
//   StampSize														  [public]
// ---------------------------------------------------------------------------

void
CSTRx_PickerStamp::StampSize(ResType inType, SInt16 &outWidth, SInt16 &outHeight)
{
#pragma unused(inType)
	outWidth = 120;
	outHeight = 120;
}


// ---------------------------------------------------------------------------
//   DrawSelf														  [public]
// ---------------------------------------------------------------------------

void
CSTRx_PickerStamp::DrawSelf()
{
}


PP_End_Namespace_PowerPlant
