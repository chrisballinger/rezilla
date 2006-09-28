// ===========================================================================
// CIconFamily_PickerStamp.h
// 
//                       Created : 2006-02-25 17:40:43
//             Last modification : 2006-09-28 18:43:54
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@users.sourceforge.net>
// www : <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2006
// All rights reserved.
// ===========================================================================

#ifndef _H_CIconFamily_PickerStamp
#define _H_CIconFamily_PickerStamp
#pragma once

#include "CPickerStamp.h"


#if PP_Uses_Pragma_Import
	#pragma import on
#endif

class CPickerView;
class COffscreen;

PP_Begin_Namespace_PowerPlant

// ---------------------------------------------------------------------------

class CIconFamily_PickerStamp : public CPickerStamp {
public:
						CIconFamily_PickerStamp(
									CPickerView *		inParent,
									const SPaneInfo&	inPaneInfo,
									const SViewInfo&	inViewInfo);

	virtual				~CIconFamily_PickerStamp();

	virtual void		DrawSelf();

	static void			StampSize(ResType inType, SInt16 &outWidth, SInt16 &outHeight);
	
private:	
	void				GetTypeInfo(ResType inType, SInt32 &theWidth, SInt32 &theHeight, 
										 SInt32 &theDepth, SInt32 &theRowBytes, SInt32 &theOffset);
	
	void				DrawBuffer(COffscreen * inBuffer);
	
};


PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
