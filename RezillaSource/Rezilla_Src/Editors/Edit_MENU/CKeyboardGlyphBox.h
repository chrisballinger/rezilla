// ===========================================================================
// CKeyboardGlyphBox.h
// 
//                       Created: 2005-03-14 14:42:07
//             Last modification: 2005-03-14 14:42:14
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CKeyboardGlyphBox
#define _H_CKeyboardGlyphBox
#pragma once

#include <LPane.h>
#include <LCFString.h>
#include <Appearance.h>



PP_Begin_Namespace_PowerPlant

// ---------------------------------------------------------------------------

class CKeyboardGlyphBox : public LPane {
public:
	enum { class_ID = FOUR_CHAR_CODE('KGBx') };
	
						CKeyboardGlyphBox();
						
						CKeyboardGlyphBox(
								const SPaneInfo&	inPaneInfo,
								ConstStringPtr		inString,
								ThemeFontID			inThemeFontID);
								
						CKeyboardGlyphBox( LStream* inStream );
								
	virtual				~CKeyboardGlyphBox();
	
	LCFString			GetString() { return mString;}
 	void				SetString(StringPtr inString);

protected:
	virtual void		ActivateSelf();
	
	virtual void		DeactivateSelf();
	
	virtual void		EnableSelf();
	
	virtual void		DisableSelf();

	virtual void		DrawSelf();
	
protected:
	LCFString			mString;
	ThemeFontID			mThemeFontID;
	ResIDT				mTextTraitsID;
	bool				mDimWhenInactive;
	bool				mDimWhenDisabled;
};

PP_End_Namespace_PowerPlant





#endif
