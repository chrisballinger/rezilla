// ===========================================================================
// UHexFilters.cp					
//                       Created: 2003-05-07 18:35:01
//             Last modification: 2004-10-09 07:11:58
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2003-2004
// All rights reserved.
// ===========================================================================

// Complements to PowerPlant's UKeyFilters utility class to deal 
//  with hexadecimal input and line/offset ranges.

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "UHexFilters.h"
#include "CRezillaPrefs.h"
#include "RezillaConstants.h"

#include <PP_KeyCodes.h>
#ifndef __MACH__
#include <Script.h>
#endif

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   HexadecimalField
// ---------------------------------------------------------------------------
//	Key Filter for Hexadecimal Integer characters
//
//		> Identify delete and cursor keys
//		> Accept hexadecimal numbers (0 to 9, a to f and A to F)
//		> Reject all other printing characters
//		> PassUp all other characters

EKeyStatus
UHexFilters::HexadecimalField(
	const EventRecord&	inKeyEvent)
{
	EKeyStatus	theKeyStatus = keyStatus_PassUp;
	UInt16		theKey		 = (UInt16) inKeyEvent.message;
	UInt16		theChar		 = (UInt16) (theKey & charCodeMask);

	if (UKeyFilters::IsTEDeleteKey(theKey)) {
		theKeyStatus = keyStatus_TEDelete;

	} else if (UKeyFilters::IsTECursorKey(theKey)) {
		theKeyStatus = keyStatus_TECursor;

	} else if (UKeyFilters::IsExtraEditKey(theKey)) {
		theKeyStatus = keyStatus_ExtraEdit;

	} else if (UKeyFilters::IsPrintingChar(theChar)) {

		if (IsHexadecimalChar(theChar)) {
			theKeyStatus = keyStatus_Input;

		} else {
			theKeyStatus = keyStatus_Reject;
		}
	}

	return theKeyStatus;
}


// ---------------------------------------------------------------------------
//   HexadecimalField
// ---------------------------------------------------------------------------
//	Key Filter for Hexadecimal Integer characters
//
//		> Identify delete and cursor keys
//		> Accept hexadecimal numbers (0 to 9, a to f and A to F)
//		> Reject all other printing characters
//		> PassUp all other characters

EKeyStatus
UHexFilters::HexadecimalField(
	TEHandle		/* inMacTEH */,
	UInt16			inKeyCode,
	UInt16&			ioCharCode,
	EventModifiers	/* inModifiers */)
{
	EKeyStatus	theKeyStatus = keyStatus_PassUp;

	if (UKeyFilters::IsTEDeleteKey(inKeyCode)) {
		theKeyStatus = keyStatus_TEDelete;

	} else if (UKeyFilters::IsTECursorKey(inKeyCode)) {
		theKeyStatus = keyStatus_TECursor;

	} else if (UKeyFilters::IsExtraEditKey(inKeyCode)) {
		theKeyStatus = keyStatus_ExtraEdit;

	} else if (UKeyFilters::IsPrintingChar(ioCharCode)) {

		if (IsHexadecimalChar(ioCharCode)) {
			theKeyStatus = keyStatus_Input;

		} else {
			theKeyStatus = keyStatus_Reject;
		}
	}

	return theKeyStatus;
}


// ---------------------------------------------------------------------------
//   HexTemplateField
// ---------------------------------------------------------------------------
//	Key Filter for Hexadecimal Integer characters
//
//		> Identify delete and cursor keys
//		> Accept hexadecimal numbers (0 to 9, a to f and A to F)
//		> Accept letters x or $ (depending on kPref_templates_hexSymbol)
//		> Reject all other printing characters
//		> PassUp all other characters

EKeyStatus
UHexFilters::HexTemplateField(
	const EventRecord&	inKeyEvent)
{
	EKeyStatus	theKeyStatus = keyStatus_PassUp;
	UInt16		theKey		 = (UInt16) inKeyEvent.message;
	UInt16		theChar		 = (UInt16) (theKey & charCodeMask);

	if (UKeyFilters::IsTEDeleteKey(theKey)) {
		theKeyStatus = keyStatus_TEDelete;

	} else if (UKeyFilters::IsTECursorKey(theKey)) {
		theKeyStatus = keyStatus_TECursor;

	} else if (UKeyFilters::IsExtraEditKey(theKey)) {
		theKeyStatus = keyStatus_ExtraEdit;

	} else if (UKeyFilters::IsPrintingChar(theChar)) {

		if (IsHexTemplateChar(theChar)) {
			theKeyStatus = keyStatus_Input;

		} else {
			theKeyStatus = keyStatus_Reject;
		}
	}

	return theKeyStatus;
}


// ---------------------------------------------------------------------------
//   HexTemplateField
// ---------------------------------------------------------------------------
//	Key Filter for Hexadecimal Integer characters
//
//		> Identify delete and cursor keys
//		> Accept hexadecimal numbers (0 to 9, a to f and A to F)
//		> Accept letters x or $ (depending on kPref_templates_hexSymbol)
//		> Reject all other printing characters
//		> PassUp all other characters

EKeyStatus
UHexFilters::HexTemplateField(
	TEHandle		/* inMacTEH */,
	UInt16			inKeyCode,
	UInt16&			ioCharCode,
	EventModifiers	/* inModifiers */)
{
	EKeyStatus	theKeyStatus = keyStatus_PassUp;

	if (UKeyFilters::IsTEDeleteKey(inKeyCode)) {
		theKeyStatus = keyStatus_TEDelete;

	} else if (UKeyFilters::IsTECursorKey(inKeyCode)) {
		theKeyStatus = keyStatus_TECursor;

	} else if (UKeyFilters::IsExtraEditKey(inKeyCode)) {
		theKeyStatus = keyStatus_ExtraEdit;

	} else if (UKeyFilters::IsPrintingChar(ioCharCode)) {

		if (IsHexTemplateChar(ioCharCode)) {
			theKeyStatus = keyStatus_Input;

		} else {
			theKeyStatus = keyStatus_Reject;
		}
	}

	return theKeyStatus;
}


// ---------------------------------------------------------------------------
//   IntegerRangeField
// ---------------------------------------------------------------------------
//	Key Filter for Hexadecimal Integer characters
//
//		> Identify delete and cursor keys
//		> Accept integer numbers (0 to 9) or dash
//		> Reject all other printing characters
//		> PassUp all other characters

EKeyStatus
UHexFilters::IntegerRangeField(
	const EventRecord&	inKeyEvent)
{
	EKeyStatus	theKeyStatus = keyStatus_PassUp;
	UInt16		theKey		 = (UInt16) inKeyEvent.message;
	UInt16		theChar		 = (UInt16) (theKey & charCodeMask);

	if (UKeyFilters::IsTEDeleteKey(theKey)) {
		theKeyStatus = keyStatus_TEDelete;

	} else if (UKeyFilters::IsTECursorKey(theKey)) {
		theKeyStatus = keyStatus_TECursor;

	} else if (UKeyFilters::IsExtraEditKey(theKey)) {
		theKeyStatus = keyStatus_ExtraEdit;

	} else if (UKeyFilters::IsPrintingChar(theChar)) {

		if (IsIntegerRangeChar(theChar)) {
			theKeyStatus = keyStatus_Input;

		} else {
			theKeyStatus = keyStatus_Reject;
		}
	}

	return theKeyStatus;
}


// ---------------------------------------------------------------------------
//   IntegerRangeField
// ---------------------------------------------------------------------------
//	Key Filter for Hexadecimal Integer characters
//
//		> Identify delete and cursor keys
//		> Accept integer numbers (0 to 9) or dash
//		> Reject all other printing characters
//		> PassUp all other characters

EKeyStatus
UHexFilters::IntegerRangeField(
	TEHandle		/* inMacTEH */,
	UInt16			inKeyCode,
	UInt16&			ioCharCode,
	EventModifiers	/* inModifiers */)
{
	EKeyStatus	theKeyStatus = keyStatus_PassUp;

	if (UKeyFilters::IsTEDeleteKey(inKeyCode)) {
		theKeyStatus = keyStatus_TEDelete;

	} else if (UKeyFilters::IsTECursorKey(inKeyCode)) {
		theKeyStatus = keyStatus_TECursor;

	} else if (UKeyFilters::IsExtraEditKey(inKeyCode)) {
		theKeyStatus = keyStatus_ExtraEdit;

	} else if (UKeyFilters::IsPrintingChar(ioCharCode)) {

		if (IsIntegerRangeChar(ioCharCode)) {
			theKeyStatus = keyStatus_Input;

		} else {
			theKeyStatus = keyStatus_Reject;
		}
	}

	return theKeyStatus;
}


#pragma mark -


// ---------------------------------------------------------------------------
//   IsLeftRightArrowKey
// ---------------------------------------------------------------------------

bool
UHexFilters::IsLeftRightArrowKey(
	UInt16	inKey)
{
	Boolean	isArrow = false;

	switch (inKey & charCodeMask) {

		case char_LeftArrow:
		case char_RightArrow:
			isArrow = true;
			break;
	}

	return isArrow;
}


// ---------------------------------------------------------------------------
//   IsUpDownArrowKey
// ---------------------------------------------------------------------------
// 		case char_Home:
// 		case char_End:
// 		case char_PageUp:
// 		case char_PageDown:

bool
UHexFilters::IsUpDownArrowKey(
	UInt16	inKey)
{
	Boolean	isArrow = false;

	switch (inKey & charCodeMask) {

		case char_UpArrow:
		case char_DownArrow:
			isArrow = true;
			break;
	}

	return isArrow;
}


// ---------------------------------------------------------------------------
//   IsHexadecimalChar
// ---------------------------------------------------------------------------

bool
UHexFilters::IsHexadecimalChar(UInt16 inChar)
{
	return  (((inChar >= '0') && (inChar <= '9'))  ||	
			((inChar >= 'a') && (inChar <= 'f'))  ||
		    ((inChar >= 'A') && (inChar <= 'F')));
}


// ---------------------------------------------------------------------------
//   IsHexTemplateChar
// ---------------------------------------------------------------------------
// UInt16 val = (CRezillaPrefs::GetPrefValue(kPref_templates_hexSymbol) == hex_Symb0x) ? 'x':'$';

bool
UHexFilters::IsHexTemplateChar(UInt16 inChar)
{
	return  (IsHexadecimalChar(inChar) || (inChar ==  'x') || (inChar ==  '$'));
}


// ---------------------------------------------------------------------------
//   IsIntegerRangeChar
// ---------------------------------------------------------------------------

bool
UHexFilters::IsIntegerRangeChar(UInt16 inChar)
{
	return  (((inChar >= '0') && (inChar <= '9'))  ||	
			(inChar >= '-'));
}


PP_End_Namespace_PowerPlant
