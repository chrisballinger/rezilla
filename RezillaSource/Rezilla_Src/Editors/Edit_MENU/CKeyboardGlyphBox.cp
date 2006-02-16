// ===========================================================================
// CKeyboardGlyphBox.h
// 
//                       Created: 2005-03-14 14:42:07
//             Last modification: 2005-07-04 19:55:59
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// ===========================================================================
// This class is modelled exactly after PP's LThemeTextBox but uses the 
// kTextEncodingMacKeyboardGlyphs encoding to encode the CFString in order 
// to display keyboard glyph symbols (as they appear as command glyphs in 
// menus)

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CKeyboardGlyphBox.h"

#include <LStream.h>
#include <LString.h>
#include <UEnvironment.h>
#include <UTextTraits.h>

#include <CFString.h>
#include <MacTextEditor.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   CKeyboardGlyphBox							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CKeyboardGlyphBox::CKeyboardGlyphBox()
{
	mThemeFontID = kThemeSystemFont;
	mTextTraitsID = 0;
	mDimWhenInactive = true;
	mDimWhenDisabled = true;
}


// ---------------------------------------------------------------------------
//   CKeyboardGlyphBox							Parameterized Constructor [public]
// ---------------------------------------------------------------------------

CKeyboardGlyphBox::CKeyboardGlyphBox(
	const SPaneInfo&	inPaneInfo,
	ConstStringPtr		inString,
	ThemeFontID			inThemeFontID)
	
	: LPane(inPaneInfo),
	  mString(inString, kTextEncodingMacKeyboardGlyphs)
{
	mThemeFontID = inThemeFontID;
	mTextTraitsID = 0;
	mDimWhenInactive = true;
	mDimWhenDisabled = true;
}


// ---------------------------------------------------------------------------
//   CKeyboardGlyphBox							Stream Constructor		  [public]
// ---------------------------------------------------------------------------

CKeyboardGlyphBox::CKeyboardGlyphBox(
	LStream*	inStream)
	
	: LPane(inStream)
{
	LStr255		str;
	Boolean		boolValue;

	*inStream >> (StringPtr) str;
	*inStream >> mTextTraitsID;
	*inStream >> mThemeFontID;
	
	*inStream >> boolValue;
	mDimWhenInactive = boolValue;
	
	*inStream >> boolValue;
	mDimWhenDisabled = boolValue;
	
	mString.Append(str, kTextEncodingMacKeyboardGlyphs);
}


// ---------------------------------------------------------------------------
//     ~CKeyboardGlyphBox						Destructor				  [public]
// ---------------------------------------------------------------------------

CKeyboardGlyphBox::~CKeyboardGlyphBox()
{
}


// ---------------------------------------------------------------------------
//   ActivateSelf												   [protected]
// ---------------------------------------------------------------------------

void
CKeyboardGlyphBox::ActivateSelf()
{
	Refresh();
}


// ---------------------------------------------------------------------------
//   DeactivateSelf											   [protected]
// ---------------------------------------------------------------------------

void
CKeyboardGlyphBox::DeactivateSelf()
{
	Refresh();
}


// ---------------------------------------------------------------------------
//   EnableSelf												   [protected]
// ---------------------------------------------------------------------------

void
CKeyboardGlyphBox::EnableSelf()
{
	Refresh();
}


// ---------------------------------------------------------------------------
//   DisableSelf												   [protected]
// ---------------------------------------------------------------------------

void
CKeyboardGlyphBox::DisableSelf()
{
	Refresh();
}


// ---------------------------------------------------------------------------
//   DrawSelf													   [protected]
// ---------------------------------------------------------------------------

void
CKeyboardGlyphBox::DrawSelf()
{
	Rect	frame;
	
	CalcLocalFrameRect(frame);
	ApplyForeAndBackColors();
	::EraseRect(&frame);

	if (CFM_AddressIsResolved_(::DrawThemeTextBox)) {
	
		if (mThemeFontID == kThemeCurrentPortFont) {
			UTextTraits::SetPortTextTraits(mTextTraitsID);
		}
		
		bool	dimmed = ( (mDimWhenInactive and not IsActive()) or
						   (mDimWhenDisabled and not IsEnabled()) );
	
		ThemeDrawState	drawState = kThemeStateActive;
		
		if (dimmed) {
			drawState = kThemeStateInactive;
		}
		
		SInt16	bitDepth;
		bool	hasColor;
		GetDeviceInfo(bitDepth, hasColor);
		
		RGBColor	textColor;
		
		GetEmbeddedTextColor(bitDepth, hasColor, not dimmed, textColor);
		
		::RGBForeColor(&textColor);

		::DrawThemeTextBox( mString,
							mThemeFontID,
							drawState,
							true,
							&frame,
							teJustLeft,
							nil );
							
	}
}


// ---------------------------------------------------------------------------
//   SetString													   [protected]
// ---------------------------------------------------------------------------
// Allowable values for inString[1] are : 0, 2-31, 97-122, 135-138 (Menus.h)

void
CKeyboardGlyphBox::SetString(StringPtr inString) {
	// Make sure we have only one char
	if (inString[0] == 0) {
		return;
	} else {
		inString[0] = 1;
	}

	LCFString * theString = new LCFString(inString, kTextEncodingMacKeyboardGlyphs);
	if (theString != nil) {
		mString = *theString;
	} 
}


PP_End_Namespace_PowerPlant
