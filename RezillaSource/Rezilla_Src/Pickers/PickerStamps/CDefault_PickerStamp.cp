// ===========================================================================
// 	CDefault_PickerStamp.cp
// 
//                       Created : 2006-09-20 18:39:04
//             Last modification : 2006-09-21 09:32:42
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@users.sourceforge.net>
// www : <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2006
// All rights reserved.
// ===========================================================================
// The stamp is the part of a picker view where the image is drawn. The
// StampSize method returns the dimensions of this drawing area.


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CDefault_PickerStamp.h"
#include "CPickerView.h"
#include "UResources.h"

#include <LPane.h>
#include <Icons.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   CDefault_PickerStamp							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CDefault_PickerStamp::CDefault_PickerStamp(
									CPickerView *		inParent,
									const SPaneInfo&	inPaneInfo,
									const SViewInfo&	inViewInfo)
	: CPickerStamp(inParent, inPaneInfo, inViewInfo)
{
}


// ---------------------------------------------------------------------------
//   ~CDefault_PickerStamp							Destructor				  [public]
// ---------------------------------------------------------------------------

CDefault_PickerStamp::~CDefault_PickerStamp()
{
}


// ---------------------------------------------------------------------------
//   StampSize														  [public]
// ---------------------------------------------------------------------------

void
CDefault_PickerStamp::StampSize(ResType inType, SInt16 &outWidth, SInt16 &outHeight)
{
#pragma unused(inType)
	outWidth = 60;
	outHeight = 60;
}


// ---------------------------------------------------------------------------
//   DrawSelf														  [public]
// ---------------------------------------------------------------------------

void
CDefault_PickerStamp::DrawSelf()
{
	CPickerStamp::DrawSelf();	
}




PP_End_Namespace_PowerPlant
