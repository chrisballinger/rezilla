// ===========================================================================
// CTmplListItemView.h
// 
//                       Created: 2004-06-27 14:13:08
//             Last modification: 2004-10-12 13:40:56
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// ===========================================================================

#ifndef _H_CTmplListItemView
#define _H_CTmplListItemView
#pragma once

#include <LTextGroupBox.h>

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

class CTmplEditorWindow;
class CTmplListButton;

// ---------------------------------------------------------------------------

class CTmplListItemView : public LTextGroupBox {
public:
	enum { class_ID = FOUR_CHAR_CODE('TLIV') };
												
						CTmplListItemView(const SPaneInfo& inPaneInfo,
										  const SViewInfo& inViewInfo,
										  CTmplEditorWindow * inOwnerWindow,
										  Boolean inPrimary = true);
								
						CTmplListItemView( LStream * inStream);
						
								
	virtual				~CTmplListItemView();

	virtual void		Draw( RgnHandle inSuperDrawRgnH );
	
	virtual void		DrawBorder();
	virtual void		EraseBorder();

	virtual void		Click( SMouseDownEvent& inMouseDown );
	
	Boolean				GetIsSelected() { return mIsSelected;}
	void				SetIsSelected(Boolean inIsSelected) {mIsSelected = inIsSelected;}

	CTmplListItemView *	mPrevItem;
	CTmplListItemView *	mNextItem;
	PaneIDT				mFirstItemID;
	CTmplListButton *	mMinusButton;

protected:
	Boolean				mIsSelected;
	CTmplEditorWindow *	mOwnerWindow;
	

private:
		void		InitList();

};

PP_End_Namespace_PowerPlant

#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
