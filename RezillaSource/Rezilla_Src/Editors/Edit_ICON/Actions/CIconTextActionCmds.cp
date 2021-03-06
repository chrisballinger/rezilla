// ===========================================================================
// CIconTextActionCmds.cp
//                       Created: 2004-12-11 18:57:13
//             Last modification: 2004-12-24 10:16:05
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// ===========================================================================

#include "CIconTextAction.h"
#include "UFontSizeDialog.h"


// ---------------------------------------------------------------------------
// 	FindCommandStatus											[static]
// ---------------------------------------------------------------------------

Boolean
CIconTextAction::FindCommandStatus( 
						const TextTraitsRecord &inTraits,
						CommandT inCommand, Boolean &outEnabled, 
						Boolean &outUsesMark, UInt16 &outMark, 
						Str255 outName, LMenu *inFontMenu )
{
	Boolean			handled = false;

	// First check for font menu. We get only one call for the entire font
	// menu because it's synthetic.
	ResIDT		theMenuID;
	SInt16		theMenuItem;
	Boolean		foundFontItem = false;
	
	if ( LCommander::IsSyntheticCommand( inCommand, theMenuID, theMenuItem ) )
	{
		if ( !inFontMenu || (theMenuID != MENU_IconFonts) ) return( false );
		
		// The font menu is shared between different windows, so we need to
		// uncheck the previous item and check the current one. The easiest
		// way to do this is to just run through the entire menu.
		MenuHandle	fontMenuH = inFontMenu->GetMacMenuH();
		if ( !fontMenuH ) return( false );			// shouldn't happen
		
		outEnabled = true;							// font menu always enabled
		outUsesMark = true;
		outMark = 0;
		outName[0] = 0;
		
		// inTraits has either the fontID, or if it is -1, the font name
		Str255	menuItemName, fontName;
		if ( inTraits.fontNumber == -1 )
			LString::CopyPStr( inTraits.fontName, fontName );
		else
			::GetFontName( inTraits.fontNumber, fontName );
			
		SInt32 numItems = ::CountMenuItems( fontMenuH );
		for ( SInt32 count = 1; count <= numItems; count++ )
		{
			if ( foundFontItem )		// if we found the item already, just uncheck the rest
				::MacCheckMenuItem( fontMenuH, count, false );
			else
			{
				::GetMenuItemText( fontMenuH, count, menuItemName );
				foundFontItem = ::EqualString( menuItemName, fontName, false, true );
				::MacCheckMenuItem( fontMenuH, count, foundFontItem );
			}
		}
				
		return( true );
	}
	
	// 9100-9300 is for font sizes (1..200 pts), 9100 is the "Other size" 
	// item
	if ( (inCommand >= cmd_IconFontSizeBase) && (inCommand <= cmd_IconFontSizeLast) )
	{
		outEnabled = true;							// font menu always enabled
		outUsesMark = true;
		outName[0] = 0;
		
		// Map "0" to default font size
		SInt32 specifiedSize = (inTraits.size == 0) ? ::GetDefFontSize() : inTraits.size;

		// This won't put a checkMark next to "other" if a non-standard
		// size is selected.
		SInt32 fontSize = (SInt32) inCommand - (SInt32) cmd_IconFontSizeBase;
		if ( fontSize == specifiedSize )
			outMark = checkMark;
		else
			outMark = 0;
			
		return( true );
	}
	
	// Otherwise check for style and size menus
	switch( inCommand )
	{
		case cmd_Plain:
			outUsesMark = true;
			outMark = inTraits.style ? 0 : checkMark;
			outEnabled = true;
			handled = true;
			break;
		case cmd_Bold:
			outUsesMark = true;
			outMark = (inTraits.style & bold) ? checkMark : 0;
			outEnabled = true;
			handled = true;
			break;
		case cmd_Italic:
			outUsesMark = true;
			outMark = (inTraits.style & italic) ? checkMark : 0;
			outEnabled = true;
			handled = true;
			break;
		case cmd_Underline:
			outUsesMark = true;
			outMark = (inTraits.style & underline) ? checkMark : 0;
			outEnabled = true;
			handled = true;
			break;
		case cmd_Outline:
			outUsesMark = true;
			outMark = (inTraits.style & outline) ? checkMark : 0;
			outEnabled = true;
			handled = true;
			break;
		case cmd_Shadow:
			outUsesMark = true;
			outMark = (inTraits.style & shadow) ? checkMark : 0;
			outEnabled = true;
			handled = true;
			break;
		case cmd_Condense:
			outUsesMark = true;
			outMark = (inTraits.style & condense) ? checkMark : 0;
			outEnabled = true;
			handled = true;
			break;
		case cmd_Extend:
			outUsesMark = true;
			outMark = (inTraits.style & extend) ? checkMark : 0;
			outEnabled = true;
			handled = true;
			break;
			
		case cmd_JustifyLeft:
			outUsesMark = true;
			outMark = (inTraits.justification == teFlushLeft) ? checkMark : 0;
			outEnabled = true;
			handled = true;
			break;
		case cmd_JustifyCenter:
			outUsesMark = true;
			outMark = (inTraits.justification == teCenter) ? checkMark : 0;
			outEnabled = true;
			handled = true;
			break;
		case cmd_JustifyRight:
			outUsesMark = true;
			outMark = (inTraits.justification == teFlushRight) ? checkMark : 0;
			outEnabled = true;
			handled = true;
			break;
			
		case cmd_FontLarger:
		case cmd_FontSmaller:
			handled = true;
			break;
	}
	
	return( handled );
}



// ---------------------------------------------------------------------------
// 	ToggleBit
// ---------------------------------------------------------------------------

static void ToggleBit( SInt16 &ioByte, SInt16 inBit )
{
	if ( ioByte & inBit )
		ioByte &= ~inBit;
	else
		ioByte |= inBit;
}


// ---------------------------------------------------------------------------
// 	ObeyCommand											[static]
// ---------------------------------------------------------------------------

Boolean
CIconTextAction::ObeyCommand( 	CIcon_EditorWindow *,
									CIconTextAction *inTextAction,
									MessageT inCommand, 
									TextTraitsRecord *ioRec,
									Boolean *outChanged )
{
	Boolean		handled = false;
	Boolean		changed = false;

	// First check for font menu
	ResIDT	theMenuID;
	SInt16	theMenuItem;
	
	if ( LCommander::IsSyntheticCommand( inCommand, theMenuID, theMenuItem ) )
	{
		if ( theMenuID == MENU_IconFonts )
		{
			MenuHandle	fontMenuH = ::GetMenuHandle( theMenuID );
			if ( fontMenuH )
			{
				::GetMenuItemText( fontMenuH, theMenuItem, ioRec->fontName );
				ioRec->fontNumber = -1;			// invalidate the font id
				changed = true;
			}
		
			handled = true;
		}
	}

	// Now for the font size
	if ( !handled && (inCommand >= cmd_IconFontSizeBase) && (inCommand <= cmd_IconFontSizeLast) )
	{
		if ( inCommand == cmd_IconOtherFontSize )
		{
			if ( UFontSizeDialog::DoSizeDialog( ioRec->size, &ioRec->size ) )
				changed = true;
		}
		else
		{
			ioRec->size = (SInt32) inCommand - (SInt32) cmd_IconFontSizeBase;
			changed = true;
		}	
		
		handled = true;
	}

	// Check the other text commands
	if ( !handled )
		switch( inCommand )
		{
			case cmd_Plain:
				if ( ioRec->style != 0 )
				{
					ioRec->style = 0;
					changed = true;
				}
				handled = true;
				break;
			case cmd_Bold:
				ToggleBit( ioRec->style, bold );
				changed = true;
				handled = true;
				break;
			case cmd_Italic:
				ToggleBit( ioRec->style, italic );
				changed = true;
				handled = true;
				break;
			case cmd_Underline:
				ToggleBit( ioRec->style, underline );
				changed = true;
				handled = true;
				break;
			case cmd_Outline:
				ToggleBit( ioRec->style, outline );
				changed = true;
				handled = true;
				break;
			case cmd_Shadow:
				ToggleBit( ioRec->style, shadow );
				changed = true;
				handled = true;
				break;
			case cmd_Condense:
				ToggleBit( ioRec->style, condense );
				changed = true;
				handled = true;
				break;
			case cmd_Extend:
				ToggleBit( ioRec->style, extend );
				changed = true;
				handled = true;
				break;
				
			case cmd_JustifyLeft:
				if ( ioRec->justification != teJustLeft )
				{
					ioRec->justification = teJustLeft;
					changed = true;
				}
				handled = true;
				break;
			case cmd_JustifyCenter:
				if ( ioRec->justification != teJustCenter )
				{
					ioRec->justification = teJustCenter;
					changed = true;
				}
				handled = true;
				break;
			case cmd_JustifyRight:
				if ( ioRec->justification != teJustRight )
				{
					ioRec->justification = teJustRight;
					changed = true;
				}
				handled = true;
				break;
				
			case cmd_FontLarger:
				if ( ioRec->size < 1024 )		// clip to arbitrarily high number
				{
					++ioRec->size;
					changed = true;
				}
				handled = true;
				break;
				
			case cmd_FontSmaller:
				if ( ioRec->size > 4 )			// clip to arbitrarily low number
				{
					--ioRec->size;
					changed = true;
				}
				handled = true;
				break;
				
			case cmd_FontOther:
				break;
				
		}
	
	if ( outChanged ) *outChanged = changed;

	// This will redraw the text in the new font/size/style
	if ( changed && inTextAction )
		inTextAction->ChangeTextTraits( *ioRec );
	
	return( handled );
}
