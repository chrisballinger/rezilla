// ===========================================================================
// CColorTableChoice.h
//                       Created: 2004-12-11 18:56:24
//             Last modification: 2004-12-29 08:42:43
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// ===========================================================================

#ifndef _H_CColorTableChoice
#define _H_CColorTableChoice

class CIcon_EditorWindow;


class CColorTableChoice {
	public:
						CColorTableChoice( CIcon_EditorWindow *, Boolean inUsesIconColors );
						~CColorTableChoice();
					
		Boolean			FindCommandStatus( SInt32 inDepth, CommandT inCommand, 
										Boolean &outEnabled, Boolean &outUsesMark, 
										UInt16 &outMark, Str255 outName );
										
		Boolean			ObeyCommand( SInt32 inDepth, CommandT inCommand );
		void			ImageChanged( SInt32 inNewDepth );
		CTabHandle		GetCurrentTable();
		void			ChangePopupColorTables( ResIDT inResID );
	
	protected:
		CommandT			mTableCommands[ 33 ];	// uses the bit depth as an index
		CTabHandle			mCurrentTable;
		CIcon_EditorWindow	*mPaintWindow;
		
		void			InitTableCommands( Boolean inIconColors );
		Boolean			MapCommandToTableID( CommandT, ResIDT * );
		void			DisposeCurrentTable();
};

#endif // _H_CColorTableChoice
