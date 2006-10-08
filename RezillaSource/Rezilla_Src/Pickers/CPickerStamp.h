// ===========================================================================
// CPickerStamp.h				
// 
//                       Created: 2006-02-24 09:49:42
//             Last modification: 2006-10-08 10:29:12
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

class CPickerView;

PP_Begin_Namespace_PowerPlant

// ---------------------------------------------------------------------------

class CPickerStamp : public LView {
public:
							CPickerStamp(
								CPickerView *		inParent,
								const SPaneInfo&	inPaneInfo,
								const SViewInfo&	inViewInfo);
							virtual	~CPickerStamp();

	virtual void		DrawSelf();
	
	virtual void 		ClickSelf( const SMouseDownEvent & );

protected:
	CPickerView *		mParent;

};


PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif  // _H_CPickerStamp
