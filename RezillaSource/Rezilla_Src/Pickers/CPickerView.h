// ===========================================================================
// CPickerView.h				
// 
//                       Created: 2006-02-24 09:49:42
//             Last modification: 2006-03-19 14:48:54
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2006
// All rights reserved.
// ===========================================================================

#ifndef _H_CPickerView
#define _H_CPickerView
//#pragma once

#include <LView.h>
#include <LStaticText.h>

#if PP_Uses_Pragma_Import
	#pragma import on
#endif




class CPickerWindow;

PP_Begin_Namespace_PowerPlant

// ---------------------------------------------------------------------------

class CPickerView : public LView {
public:
						CPickerView(ResIDT inID);

	virtual				~CPickerView();

	virtual void		DrawSelf();

	virtual void 		ClickSelf( const SMouseDownEvent & );

	void				SetIDField(ResIDT inID);

	void				DrawBorder(Boolean isSelected);
	
	CPickerWindow*		GetOwnerWindow() { return mOwnerWindow;}
	void				SetOwnerWindow(CPickerWindow* inOwnerWindow) {mOwnerWindow = inOwnerWindow;}

	Boolean				IsSelected() { return mIsSelected;}
	void				SetIsSelected(Boolean inIsSelected) {mIsSelected = inIsSelected;}

protected:
	CPickerWindow *		mOwnerWindow;
	LStaticText *		mIDField;
	Boolean				mIsSelected;
	
private:
	void				InitPickerView(SInt16 inStampWidth, SInt16 inStampHeight, ResIDT inID);

};

PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif  // _H_CPickerView
