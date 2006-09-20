// ===========================================================================
// 	CTEXT_PickerStamp.cp
// 
//                       Created : 2006-02-25 17:40:43
//             Last modification : 2006-09-20 09:10:15
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@users.sourceforge.net>
// www : <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2006
// All rights reserved.
// ===========================================================================


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CTEXT_PickerStamp.h"
#include "CPickerView.h"
#include "UResources.h"


PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   CTEXT_PickerStamp							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CTEXT_PickerStamp::CTEXT_PickerStamp(
									 CPickerView *		inParent,
									 const SPaneInfo&	inPaneInfo,
									 const SViewInfo&	inViewInfo)
	: CPickerStamp(inParent, inPaneInfo, inViewInfo)
{
}


// ---------------------------------------------------------------------------
//   ~CTEXT_PickerStamp							Destructor				  [public]
// ---------------------------------------------------------------------------

CTEXT_PickerStamp::~CTEXT_PickerStamp()
{
}


// ---------------------------------------------------------------------------
//   StampSize														  [public]
// ---------------------------------------------------------------------------

void
CTEXT_PickerStamp::StampSize(ResType inType, SInt16 &outWidth, SInt16 &outHeight)
{
#pragma unused(inType)
	outWidth = 80;
	outHeight = 80;
}


// ---------------------------------------------------------------------------
//   DrawSelf														  [public]
// ---------------------------------------------------------------------------

void
CTEXT_PickerStamp::DrawSelf()
{
}


PP_End_Namespace_PowerPlant
