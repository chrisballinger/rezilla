// ===========================================================================
// CIconSelection.h
//                       Created: 2004-12-11 18:57:49
//             Last modification: 2004-12-14 18:57:49
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CIconSelection
#define _H_CIconSelection
#pragma once

class COffscreen;
class CIconSelection;

class CIconSelection {
	public:
								CIconSelection();
		virtual					~CIconSelection();

			// getting the region		
		virtual RgnHandle		GetRegion();
		virtual RgnHandle		GetCopyOfRegion();

			// changing the region
		virtual void			SelectAll( COffscreen * );
		virtual void			SelectNone();
		
		virtual void			SetSelection( COffscreen *, RgnHandle );
		virtual void			SetSelection( COffscreen *, const Rect & );
		virtual void			SetSelection( CIconSelection * );
		
			// change the region, but do not affect the bits
		virtual void			SetRawSelection( RgnHandle );
		
			// copy/paste
		virtual void			CopyToClipboard();
		virtual void			PasteFromClipboard( COffscreen *parentOffscreen );
		virtual void			PastePicture( COffscreen *parentOffscreen, PicHandle, RgnHandle = nil );
		virtual void 			PasteOffscreenBuffer( COffscreen *inParentBuffer, COffscreen *inBuffer, RgnHandle = nil );
		
			// display
		virtual void			DrawInto( COffscreen * );
		
			// this is used by flip & rotation code
		virtual COffscreen		*GetImageBuffer();
				
			// misc
		virtual Boolean			IsEmpty();
		virtual Boolean			PointInSelection( SInt32 left, SInt32 top );
		virtual void			Offset( SInt32 dh, SInt32 dv );
		virtual void			MoveTo( SInt32 h, SInt32 v );
		
	protected:
		COffscreen				*mSelectionBuffer;
		RgnHandle				mRegion;
		
		void					DisposeBuffer();
};

#endif // _H_CIconSelection
