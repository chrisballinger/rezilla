// ===========================================================================
// CSTRx_PickerStamp.h
// 
//                       Created : 2006-02-25 17:40:43
//             Last modification : 2006-02-25 17:40:50
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@users.sourceforge.net>
// www : <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2006
// All rights reserved.
// ===========================================================================

#ifndef _H_CSTRx_PickerStamp
#define _H_CSTRx_PickerStamp
#pragma once

#include "CPickerStamp.h"


#if PP_Uses_Pragma_Import
	#pragma import on
#endif

class CPickerWindow;

PP_Begin_Namespace_PowerPlant

// ---------------------------------------------------------------------------

class CSTRx_PickerStamp : public CPickerStamp {
public:
						CSTRx_PickerStamp(
									const SPaneInfo&	inPaneInfo,
									const SViewInfo&	inViewInfo);

	virtual				~CSTRx_PickerStamp();

	virtual void		DrawSelf();

	static void			StampSize(ResType inType, SInt16 &outWidth, SInt16 &outHeight);

protected:
	
private:
// 	void				InitPickerStamp(ResIDT inID);

};

PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
