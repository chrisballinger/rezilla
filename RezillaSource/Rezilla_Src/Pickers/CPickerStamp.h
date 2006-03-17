// ===========================================================================
// CPickerStamp.h				
// 
//                       Created: 2006-02-24 09:49:42
//             Last modification: 2006-03-15 19:15:50
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2006
// All rights reserved.
// ===========================================================================

#ifndef _H_CPickerStamp
#define _H_CPickerStamp
//#pragma once

#include <LView.h>



#if PP_Uses_Pragma_Import
	#pragma import on
#endif

class CPickerWindow;

PP_Begin_Namespace_PowerPlant

// ---------------------------------------------------------------------------

class CPickerStamp : public LView {
public:
							CPickerStamp(
								const SPaneInfo&	inPaneInfo,
								const SViewInfo&	inViewInfo);
							virtual	~CPickerStamp();

	virtual void		DrawSelf();

	virtual void 		ClickSelf( const SMouseDownEvent & );

	// This is a purely virtual function. Each subclass must define it: it
	// is used to calculate the dimensions of the PickerView.
	static void			StampSize(ResType inType, SInt16 &outWidth, SInt16 &outHeight);

protected:
	
private:
	void				InitPickerStamp(SInt16 inWidth, SInt16 inHeight, ResIDT inID);

};


PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif  // _H_CPickerStamp
