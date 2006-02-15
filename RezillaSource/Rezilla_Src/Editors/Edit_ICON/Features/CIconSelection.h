// ===========================================================================
// CIconSelection.h
//                       Created: 2004-12-11 18:57:49
//             Last modification: 2004-12-14 18:57:49
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
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

			// Getting the region		
		virtual RgnHandle		GetRegion();
		virtual RgnHandle		GetCopyOfRegion();

			// Changing the region
		virtual void			SelectAll( COffscreen * );
		virtual void			SelectNone();
		
		virtual void			SetSelection( COffscreen *, RgnHandle );
		virtual void			SetSelection( COffscreen *, const Rect & );
		virtual void			SetSelection( CIconSelection * );
		
			// Change the region, but do not affect the bits
		virtual void			SetRawSelection( RgnHandle );
		
			// Copy/paste
		virtual void			CopyToClipboard();
		virtual void			PasteFromClipboard( COffscreen *parentOffscreen );
		virtual void			PastePicture( COffscreen *parentOffscreen, PicHandle, RgnHandle = nil );
		virtual void 			PasteOffscreenBuffer( COffscreen *inParentBuffer, COffscreen *inBuffer, RgnHandle = nil );
		
			// Display
		virtual void			DrawInto( COffscreen * );
		
			// Used by flip & rotation code
		virtual COffscreen		*GetImageBuffer();
				
			// Misc
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
