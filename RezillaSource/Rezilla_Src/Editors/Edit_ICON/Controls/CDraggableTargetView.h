// ===========================================================================
// CDraggableTargetView.h
//                       Created: 2004-12-11 18:57:45
//             Last modification: 2004-12-23 00:01:07
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CDraggableTargetView
#define _H_CDraggableTargetView
#pragma once

#include "CTargetView.h"
#include "CImageDragDrop.h"
#include <LBroadcaster.h>


class COffscreen;
class CColorCursorCache;
class CDraggableTargetView;

typedef struct
{
	// One of these two will have the image
	PicHandle				thePicture;
	COffscreen				*theBuffer;
	
	// The pane it was dropped on
	CDraggableTargetView	*thePane;
	
	// Drag info
	DragReference			theDragRef;
	DragAttributes			theDragAttribs;
} SImageDropOnTargetView;



// ---------------------------------------------------------------------------
// CDraggableTargetView is a subclass of CTargetView which is a subclass of
// LTextGroupBox, a LControlView inheriting from LView, LBroadcaster,
// and LListener.

class CDraggableTargetView : public CTargetView, 
							public CImageDragDrop {
	public:
		enum { class_ID = FOUR_CHAR_CODE('DTVw') };
		
								CDraggableTargetView( LStream * );
		virtual					~CDraggableTargetView();
		
		static CDraggableTargetView *	CreateFromStream( LStream * );
		
		virtual void			AdjustMouseSelf( Point, const EventRecord &, RgnHandle );
		virtual void 			ClickSelf( const SMouseDownEvent &inMouseDown );
		virtual void			DrawSelf();
		virtual void			RedrawBufferAsIndicated( ERedrawOptions inRedraw );

		virtual void			SetBuffer( COffscreen *, ERedrawOptions );
		virtual void			SetRawBuffer( COffscreen * );
		virtual void			CopyBufferFrom( COffscreen *, ERedrawOptions );
		virtual COffscreen *	GetBuffer();
		
		virtual Boolean			IsMask();
		virtual void			SetMask( Boolean );
		
		virtual Boolean			IsUsed();
		virtual void			SetUsedFlag( Boolean, ERedrawOptions );
		
		virtual Boolean			CanBeDeleted();
		virtual void			SetCanBeDeletedFlag( Boolean );

		virtual Boolean			GetDropEnable();
		virtual void			SetDropEnable( Boolean );
		
		// These help us resize the pane
		virtual void			GetInitialPaneSize( SDimension16 * );
		virtual void			GetMinPaneSize( SDimension16 * );
		virtual void			GetInitialPaneLocation( SPoint32 * );
		
	protected:
		COffscreen *			mBuffer;
		CColorCursorCache *		mCursorCache;
		Boolean					mIsMask;
		Boolean					mIsUsed;
		Boolean					mCanBeDeleted;
		Boolean					mDropEnabled;
		SDimension16			mMinPaneSize;
		SDimension16			mInitialPaneSize;
		SPoint32				mInitialPaneLocation;

		virtual void			DrawBuffer();

		virtual Boolean			ItemIsAcceptable( DragReference inDragRef, ItemReference inItemRef );
		virtual void			HandleDroppedPicture( PicHandle inPicture, DragReference, DragAttributes );
		virtual void			HandleDroppedOffscreen( COffscreen *, DragReference, DragAttributes );
		
		virtual void			GetCenteredBufferArea( 	SInt32 inWidth, SInt32 inHeight, 
													 	Rect *outLocalRect, Rect *outPortRect );
};


#endif // _H_CDraggableTargetView
