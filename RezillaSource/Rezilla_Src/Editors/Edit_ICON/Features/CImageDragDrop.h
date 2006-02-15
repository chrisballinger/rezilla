// ===========================================================================
// CImageDragDrop.h
//                       Created: 2004-12-11 18:57:42
//             Last modification: 2004-12-22 11:25:36
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// ===========================================================================

#ifndef _H_CImageDragDrop
#define _H_CImageDragDrop
#pragma once

class COffscreen;

class CImageDragDrop : public LDragAndDrop {
	public:
							CImageDragDrop( WindowPtr inMacWindow, LPane *inPane );
		
	protected:
		virtual Boolean		ItemIsAcceptable( DragReference, ItemReference );
		virtual void		ReceiveDragItem( DragReference, DragAttributes, ItemReference, Rect & );

		virtual void		HandleDroppedPicture( PicHandle, DragReference = 0, DragAttributes = 0 ) = 0;
		virtual void		HandleDroppedOffscreen( COffscreen *, DragReference = 0, DragAttributes = 0 ) = 0;
		virtual void		HandleDroppedPictureFile( const FSSpec &, DragReference = 0, DragAttributes = 0 );

		virtual void		HiliteDropArea( DragReference );
		virtual void		UnhiliteDropArea( DragReference );
};

#endif // _H_CImageDragDrop
