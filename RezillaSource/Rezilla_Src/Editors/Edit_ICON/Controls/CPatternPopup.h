// ===========================================================================
// CPatternPopup.h
//                       Created: 2004-12-11 18:57:38
//             Last modification: 2004-12-14 14:13:17
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#pragma once

#include "RezillaConstants.h"
#include "CPopupWindow.h"

#pragma options align=mac68k

typedef struct SPatternList
{
	short		numPatterns;
	Pattern		patterns[1];
} SPatternList, *SPatternListP, **SPatternListH;

#pragma options align=reset


class CPatternPopup : protected CPopupWindow {
	public:
		static SInt32		DoPatternPopup( Point inTopLeft, SPatternListH, 
											SInt32 defaultItem = -1, 
											const RGBColor &inForeColor = Color_Black, 
											const RGBColor &inBackColor = Color_White );
	
	protected:
		SPatternListH		mPatternList;
		RGBColor			mForeColor, mBackColor;
	
							CPatternPopup( SPatternListH, 
											const RGBColor &inForeColor = Color_Black, 
											const RGBColor &inBackColor = Color_White );
		virtual				~CPatternPopup();
		
		virtual void		Prepare( Point inTopLeft );
		virtual void		DrawInitialState();
		virtual void		DrawOneCell( SInt32 inIndex, Boolean inHilited = false );
};
