// ===========================================================================
// CIcon_EditorView.h
// 
//                       Created: 2004-12-10 17:23:05
//             Last modification: 2005-01-02 15:01:07
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
// mPixelArea:		in PP "local" coords, relative to the containing view this is
//           		where we blit pixels to. Does not include top & left
//					margins, but does include bottom & right ones (so all rows &
// 					columns are the same size)
// mFirstRect:		in PP "local" coords - does not include spacing on any side
// mHotSpot:		this is -1,-1 for most images, but used for cursors
// mCellWidth:		cell width & height (in pixels), not including spacing
// mSpaceBetween:	number of pixels in between rows & columns
// mImageWidth:		width of source image (pixels)
// mImageHeight:	height of source image (pixels)
// sBigScratchBuffer	single buffer for all of the canvas panes
// ---------------------------------------------------------------------------

#ifndef _H_CIcon_EditorView
#define _H_CIcon_EditorView
#pragma once

#include "RezillaConstants.h"
#include "CImageDragDrop.h"

#include <LTextEditView.h>




PP_Begin_Namespace_PowerPlant

class CIcon_EditorWindow;
class COffscreen;



class CIcon_EditorView :	public LView, public CImageDragDrop {
public:
	enum { class_ID = FOUR_CHAR_CODE('ICNV') };

							CIcon_EditorView();
							CIcon_EditorView(
											 const SPaneInfo&	inPaneInfo,
											 const SViewInfo&	inViewInfo);
							CIcon_EditorView(
									LStream*			inStream );
	virtual					~CIcon_EditorView();

	static CIcon_EditorView *		CreatePaintCanvasStream( LStream * );
	
	virtual Boolean			HandleKeyPress(
									const EventRecord& 	inKeyEvent);

	virtual Boolean			ObeyCommand(
									CommandT			inCommand,
									void*				ioParam);
	
	virtual void			UserChangedBitmap();

	virtual void			FinishCreateSelf();
	
	virtual void	 		Reinitialize( 
								COffscreen *	inOffscreen, 
								RedrawOptions 	inRedraw = redraw_Later,
								SInt32	inResize = resize_Canvas );
								
	virtual void			DrawSelf();
	virtual void			DrawFrom( COffscreen *, const Rect *subArea = nil );
	
	virtual void			AdjustMouseSelf( Point inPortPt, const EventRecord &inMacEvent, RgnHandle outMouseRgn );
	virtual void			ClickSelf( const SMouseDownEvent & );
	
	virtual Boolean			GetPixelRect( SInt32 inHoriz, SInt32 inVert, Rect *, 
											Boolean inPixelAreaRelative = true );
	virtual void			GetInsideDrawingRect( Rect * );
	virtual SInt32			GetSpaceBetween();
	
	virtual Boolean			MapPointToCell( Point inPoint, SInt32 *outH, SInt32 *outV, 
											Boolean roundNegsDown = false);
	virtual void			DrawOnePixel( SInt32 inHoriz, SInt32 inVert, COffscreen * );

	virtual void			MapRectToCanvas( const Rect &, Rect *outRect );
	virtual void			MapRegionToCanvas( RgnHandle inRegion, RgnHandle outRgn );
	
	virtual void			SetHotSpot( Point pt );
	virtual Boolean			HasHotSpot();
	virtual Point			GetHotSpot();
	
	virtual void			MoveSamplePanes( SInt16 dh, SInt16 dv, Boolean inRedraw );

	CIcon_EditorWindow*		GetOwnerWindow() { return mOwnerWindow;}
	void					SetOwnerWindow(CIcon_EditorWindow* inOwnerWindow) {mOwnerWindow = inOwnerWindow;}

	virtual Handle			GetModifiedBitmap();

protected:
		CIcon_EditorWindow *	mOwnerWindow;
		SInt32					mCellWidth;
		SInt32					mSpaceBetween;	
		SInt32					mImageWidth, mImageHeight;
		Rect					mPixelArea;
		Rect					mFirstRect;
		Point					mHotSpot;

		static COffscreen *		sBigScratchBuffer;	
		static SInt32			sNumWindows;

	// Drag & Drop
	virtual Boolean			ItemIsAcceptable( DragReference inDragRef, ItemReference inItemRef );
	virtual void			HandleDroppedPicture( PicHandle, DragReference, DragAttributes  );
	virtual void			HandleDroppedOffscreen( COffscreen *, DragReference, DragAttributes );

	virtual void			DrawHotSpot( COffscreen *inSourceBuffer );
	virtual void			DrawHotSpotSelf( Color32 inPixelColor, const Rect &inRect );
	
	virtual void			DrawPortionOfBuffer( 
								COffscreen *inSource, const Rect &inSourceR, 
								GrafPtr inDest, const Rect &inDestR );
									
private:
	void					ClearInstanceVariables();
	void					Initialize();
};



PP_End_Namespace_PowerPlant



#endif // _H_CIcon_EditorView
