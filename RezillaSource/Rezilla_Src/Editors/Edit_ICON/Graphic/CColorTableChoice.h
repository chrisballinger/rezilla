// ===========================================================================
// CColorTableChoice.h
//                       Created: 2004-12-11 18:56:24
//             Last modification: 2004-12-16 07:18:31
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CColorTableChoice
#define _H_CColorTableChoice

class PTPaintView;


class CColorTableChoice {
	public:
						CColorTableChoice( PTPaintView *, Boolean inUsesIconColors );
						~CColorTableChoice();
					
		Boolean			FindCommandStatus( SInt32 inDepth, CommandT inCommand, 
										Boolean &outEnabled, Boolean &outUsesMark, 
										UInt16 &outMark, Str255 outName );
										
		Boolean			ObeyCommand( SInt32 inDepth, CommandT inCommand );
		void			ImageChanged( SInt32 inNewDepth );
		CTabHandle		GetCurrentTable();
	
	protected:
		CommandT		mTableCommands[ 33 ];	// we use the bit depth as an index
		
		CTabHandle		mCurrentTable;
		PTPaintView		*mPaintView;
		
		void			InitTableCommands( Boolean inIcon );
		Boolean			MapCommandToTableID( CommandT, ResIDT * );
		void			ChangePopupColorTables( ResIDT inResID );
		void			DisposeCurrentTable();
};

#endif // _H_CColorTableChoice
