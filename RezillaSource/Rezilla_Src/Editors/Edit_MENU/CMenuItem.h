// ===========================================================================
// CMenuItem.h
// 
//                       Created: 2005-03-10 09:12:57
//             Last modification: 2005-06-09 17:12:04
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CMenuItem
#define _H_CMenuItem
#pragma once

typedef struct	SMenuItemInfo {
	Str255		title;
	UInt8		iconID;
	UInt8		shortcut;
	UInt8		mark;
	UInt8		style;
	SInt16		entrytype;
	SInt32		commandID;
	UInt8		modifiers;
	UInt8		icontype;
	UInt32		iconhandle;
	SInt32		encoding;
	SInt32		refcon1;
	SInt32		refcon2;
	ResIDT		submenuID;
	SInt16		fontID;
	SInt16		glyph;
} SMenuItemInfo;


class LHandleStream;

class CMenuItem {

public:
				CMenuItem();
				CMenuItem(Str255	inTitle,
							UInt8	inIconID, 
							UInt8	inShortcut, 
							UInt8	inMark, 
							UInt8	inStyle);
				CMenuItem(LHandleStream * inStream);
				~CMenuItem();

		void		InstallData(LHandleStream * inStream);
		void		SendData(LHandleStream * outStream);
		
		OSErr		InstallExtendedData(LHandleStream * inStream);
		void		SendExtendedData(LHandleStream * outStream);
				
		void		GetValues(Str255 outTitle, UInt8 & outIconID, UInt8 & outShortcut, 
					   UInt8 & outMark, UInt8 & outStyle);
		
		void 		SetValues(Str255 inTitle, UInt8 inIconID, UInt8 inShortcut, 
					   UInt8 inMark, UInt8 inStyle);

		void		GetExtendedValues(UInt8 & outModifiers, SInt32 & outEncoding,
							   SInt32 & outRefcon1, SInt32 & outRefcon2, 
							   SInt16 & outFontID, SInt16 & outSubstituteGlyph );
		
		void		SetExtendedValues(UInt8 inModifiers, SInt32 inEncoding, SInt32 inRefcon1, 
							   SInt32 inRefcon2, SInt16 inFontID, SInt16 inSubstituteGlyph );

		void		GetTitle(Str255 outTitle);
		void 		SetTitle(Str255 inTitle);

		UInt8		GetStyle() { return mStyle;}
		void		SetStyle(UInt8 inStyle) {mStyle = inStyle;}

protected:
		// Basic info from 'MENU'
		Str255		mTitle;
		UInt8		mIconID;
		UInt8		mShortcut;
		UInt8		mMark;
		UInt8		mStyle;
		// Extended info from 'xmnu'
		SInt32		mCommandID;			// a four char code
		UInt8		mModifiers;			// bits 3-0: no-cmd (8), ctrl (4), opt (2), shift (1)
		UInt8		mIconType;			// Icon type placeholder
		UInt32		mIconHandle;		// Icon handle placeholder
		SInt32		mEncoding;			// Current script=-2 (fffffffe)/ system script=-1
		SInt32		mRefcon1;			// a four char code
		SInt32		mRefcon2;			// a four char code
		ResIDT		mSubmenuID;			// Hierarchical 'MENU' ID
		SInt16		mFontID;			// System font is 0
		SInt16		mSubstituteGlyph;	// 0 for natural glyph
		
		
private:
		void		InitExtendedData();

};


#endif
