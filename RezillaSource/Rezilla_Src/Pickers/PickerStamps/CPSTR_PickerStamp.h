// ===========================================================================
// CPSTR_PickerStamp.h
// 
//                       Created : 2006-11-28 15:21:52
//             Last modification : 2006-11-28 15:40:02
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@users.sourceforge.net>
// www : <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2006
// All rights reserved.
// ===========================================================================

#ifndef _H_CPSTR_PickerStamp
#define _H_CPSTR_PickerStamp
#pragma once

#include "CPickerStamp.h"
#include <LStaticText.h>


#if PP_Uses_Pragma_Import
	#pragma import on
#endif

class CPickerView;
class CStaticClickThrough;

PP_Begin_Namespace_PowerPlant

// ---------------------------------------------------------------------------

class CPSTR_PickerStamp : public CPickerStamp {
public:
						CPSTR_PickerStamp(
									CPickerView *		inParent,
									const SPaneInfo&	inPaneInfo,
									const SViewInfo&	inViewInfo);

	virtual				~CPSTR_PickerStamp();

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
