// ===========================================================================
// CTEXT_PickerStamp.h				
// 
//                       Created : 2006-02-25 17:40:43
//             Last modification : 2006-09-21 10:19:55
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@users.sourceforge.net>
// www : <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2006
// All rights reserved.
// ===========================================================================

#ifndef _H_CTEXT_PickerStamp
#define _H_CTEXT_PickerStamp
#pragma once

#include "CPickerStamp.h"


#if PP_Uses_Pragma_Import
	#pragma import on
#endif

class CPickerView;
class CStaticClickThrough;

PP_Begin_Namespace_PowerPlant

// ---------------------------------------------------------------------------

class CTEXT_PickerStamp : public CPickerStamp {
public:
						CTEXT_PickerStamp(
									CPickerView *		inParent,
									const SPaneInfo&	inPaneInfo,
									const SViewInfo&	inViewInfo);

	virtual				~CTEXT_PickerStamp();

	virtual void		DrawSelf();

	static void			StampSize(ResType inType, SInt16 &outWidth, SInt16 &outHeight);

private:
	CStaticClickThrough *	mStaticField;

};


PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
