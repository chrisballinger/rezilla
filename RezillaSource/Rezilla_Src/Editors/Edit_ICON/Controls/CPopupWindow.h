// ===========================================================================
// CPopupWindow.h
//                       Created: 2004-12-11 18:53:13
//             Last modification: 2004-12-14 18:53:13
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#pragma once

	// note: items are numbered from 0..n-1, -1 indicates "nothing hit"
	
class CPopupWindow {
	public:
							CPopupWindow();
		virtual				~CPopupWindow();
	
	protected:
		Rect				mWindowRect;				// in global coords
		SInt32				mItems;
		SInt32				mRows, mCols;
		Rect				mFirstItemRect;
		SInt32				mDefaultItem;
		SInt32				mCellWidth, mCellHeight;
		
			// override these	
		virtual void		Prepare( Point inTopLeft ) = 0;	
		virtual void		DrawInitialState() = 0;
		virtual void		DrawOneCell( SInt32 inIndex, Boolean inHilited = false ) = 0;
	
			// probably don't need to override these
		virtual	SInt32		DoPopup( Point inTopLeft, SInt32 defaultItem );
		
		virtual SInt32		TrackMouse();
		virtual SInt32		LocalPointToIndex( Point pt );
		virtual Boolean		GetItemRect( SInt32 itemNo, Rect *r );
		virtual void		HiliteItem( SInt32 inItem, Boolean hiliteIt = true );
		virtual void		FlashItem( SInt32 inItem );
		
// 		virtual WindowPtr	CreateMacWindow( WindowRecord *inStorage = nil );
		virtual WindowPtr	CreateMacWindow();
};

