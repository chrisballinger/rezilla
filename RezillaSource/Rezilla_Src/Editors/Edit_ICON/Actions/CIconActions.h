// ===========================================================================
// CIconActions.h
//                       Created: 2004-12-11 18:52:12
//             Last modification: 2004-12-15 19:05:18
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#pragma once

#include "RezillaConstants.h"
#include "CSnapTo.h"

class CIcon_EditorWindow;
class CIcon_EditorView;
class COffscreen;
class CIconSelection;
class CColorPane;
class CDraggableTargetBox;


// This struct is passed to each paint action's constructor and contains
// the current settings for the paint view.
typedef struct SPaintAction
{
	Color32				theForeColor;
	Color32				theBackColor;
	Pattern				thePattern;
	
	COffscreen			*currentBuffer;	
	COffscreen			*scratchBuffer;

	CIcon_EditorWindow *	thePaintView;
	CIcon_EditorView *		theCanvas;
	CIconSelection *		theSelection;
} SPaintAction;



// ============================================================
// 	CIconAction 
// 	
// 	Superclass to all painting actions. DoIt() is used to perform the paint
// 	action, except for tracking actions which use HandleMouseDown().
// ============================================================

class CIconAction : public LAction {
	public:
							CIconAction( const SPaintAction &, SInt16 inStringIndex = index_UndoGeneric, Boolean isDone = true );
		virtual				~CIconAction();
		
		virtual void		DoIt();

		virtual MessageT	GetActionType();
		virtual Boolean		IsPostable() const;
		
	protected:
		SPaintAction		mSettings;
		MessageT			mActionType;			// used for move cmds only
		Boolean				mAffectsUndoState;		// is it undoable ?
		
		virtual void		RedoSelf();	
		virtual void		UndoSelf();
		virtual void		PostAsAction();	

		virtual Boolean		GetColorUnderPoint( Point inLocal, Color32 *outColor );
		virtual void		ThrowIfFileLocked();
};


// ============================================================
// 	CIconTrackingPaintAction 
// ============================================================

class CIconTrackingPaintAction : public CIconAction {
	public:
							CIconTrackingPaintAction( const SPaintAction &, SInt16 inStringIndex = index_UndoGeneric, Boolean isDone = true );
		virtual				~CIconTrackingPaintAction();
		
		virtual void		HandleMouseDown( const SMouseDownEvent & );
		
	protected:
		SInt32				mMouseDownRow, mMouseDownCol;
		CSnapTo				mSnapTo;
		
		virtual void		MouseInitial( const SMouseDownEvent &, SInt32 newCol, SInt32 newRow );
		
		virtual void		MouseStillDown( const SMouseDownEvent &, 
											Point prevMousePt, Point newMousePt,
											SInt32 prevCol, SInt32 prevRow,
											SInt32 newCol, SInt32 newRow );
											 		
		virtual Boolean		MouseFinal( const SMouseDownEvent &, 
											Point prevMousePt, Point newMousePt,
											SInt32 prevCol, SInt32 prevRow,
											SInt32 newCol, SInt32 newRow );
};



// ============================================================
// 	CIconLassoAction 
// ============================================================
// Defined in CIconLassoAction.h


// ============================================================
// 	CIconEraserAction 
// ============================================================

class CIconEraserAction : public CIconTrackingPaintAction {
	public:
							CIconEraserAction( const SPaintAction & );
		virtual				~CIconEraserAction();

	protected:
		SInt32				mBufferCols, mBufferRows;
		SInt32				mLastColErased, mLastRowErased;
		SInt32				mEraserWidth;
		
		virtual void		MouseInitial( const SMouseDownEvent &, SInt32 newCol, SInt32 newRow );
		
		virtual void		MouseStillDown( const SMouseDownEvent &, 
											Point prevMousePt, Point newMousePt,
											SInt32 prevCol, SInt32 prevRow,
											SInt32 newCol, SInt32 newRow );
};


// ============================================================
// 	CIconPenAction 
// ============================================================

class CIconPenAction : public CIconTrackingPaintAction {
	public:
							CIconPenAction( const SPaintAction & );
		virtual				~CIconPenAction();

	protected:
		Color32				mPenColor;
		SInt32				mLastRowPainted, mLastColPainted;
		SInt32				mBufferCols, mBufferRows;
		
		virtual void		MouseInitial( const SMouseDownEvent &, SInt32 newCol, SInt32 newRow );
		
		virtual void		MouseStillDown( const SMouseDownEvent &, 
											Point prevMousePt, Point newMousePt,
											SInt32 prevCol, SInt32 prevRow,
											SInt32 newCol, SInt32 newRow );
};


// ============================================================
// 	CIconDropperAction 
// ============================================================

class CIconDropperAction : public CIconTrackingPaintAction {
	public:
						CIconDropperAction( const SPaintAction &, CColorPane *, CColorPane * );
		virtual			~CIconDropperAction();
		
		virtual void	HandleMouseDown( const SMouseDownEvent & );
		
	protected:
		CColorPane	 	*mForePane, *mBackPane;
		
		virtual void	ChangeColor( Color32, Boolean isShiftDown = false );
};


// ============================================================
// 	CIconBucketAction 
// ============================================================

class CIconBucketAction : public CIconTrackingPaintAction {
	public:
						CIconBucketAction( const SPaintAction & );
		virtual			~CIconBucketAction();
		void 			HandleMouseDown( const SMouseDownEvent &inEvent );
};


// ============================================================
// 	CIconLineAction 
// ============================================================

class CIconLineAction : public CIconTrackingPaintAction {
	public:
							CIconLineAction( const SPaintAction & );
		virtual				~CIconLineAction();

	protected:
		Boolean				mScratchBufferHasImage;
		
		virtual void		MouseStillDown( const SMouseDownEvent &, 
											Point prevMousePt, Point newMousePt,
											SInt32 prevCol, SInt32 prevRow,
											SInt32 newCol, SInt32 newRow );
											 		
		virtual Boolean		MouseFinal( const SMouseDownEvent &, 
											Point prevMousePt, Point newMousePt,
											SInt32 prevCol, SInt32 prevRow,
											SInt32 newCol, SInt32 newRow );
};


// ============================================================
// 	CIconRectAction 
// ============================================================
// 	This stuff is used for RoundRects and Ovals too.

class CIconRectAction : public CIconTrackingPaintAction {
	public:
						CIconRectAction( const SPaintAction &, Boolean isFilled, ResIDT = index_UndoRect );
		virtual			~CIconRectAction();
		
	protected:
		Boolean				mFilled;
		Boolean				mScratchBufferHasImage;
		
		virtual void		MouseStillDown( const SMouseDownEvent &, 
											Point prevMousePt, Point newMousePt,
											SInt32 prevCol, SInt32 prevRow,
											SInt32 newCol, SInt32 newRow );
											 		
		virtual Boolean		MouseFinal( const SMouseDownEvent &, 
											Point prevMousePt, Point newMousePt,
											SInt32 prevCol, SInt32 prevRow,
											SInt32 newCol, SInt32 newRow );
											
		virtual void		DrawShape( const Rect &r );
};


// ============================================================
// 	CIconRoundRectAction
// ============================================================

class CIconRoundRectAction : public CIconRectAction {
	public:
							CIconRoundRectAction( const SPaintAction &, Boolean isFilled );
		virtual				~CIconRoundRectAction();

	protected:
		virtual void		DrawShape( const Rect &r );
};


// ============================================================
// 	CIconOvalAction 
// ============================================================

class CIconOvalAction : public CIconRectAction {
	public:
							CIconOvalAction( const SPaintAction &, Boolean isFilled );
		virtual				~CIconOvalAction();

	protected:
		virtual void		DrawShape( const Rect &r );
};


// ============================================================
// 	CIconEraseAllAction 
// ============================================================

class CIconEraseAllAction : public CIconAction {
	public:
						CIconEraseAllAction( const SPaintAction & );
		virtual			~CIconEraseAllAction();
		virtual void	DoIt();
};


// ============================================================
// 	CIconMoveAction 
// ============================================================

class CIconMoveAction : public CIconTrackingPaintAction {
	public:
							CIconMoveAction( const SPaintAction & );
		virtual 			~CIconMoveAction();
		
		virtual void		MoveTo( SInt32 left, SInt32 top );
		virtual void		Move( SInt32 dh, SInt32 dv );
		
	protected:
		SInt32				mHOffsetWithinSelection;
		SInt32				mVOffsetWithinSelection;
		
		Boolean				mHaveMovedSinceMouseDown;
		Boolean				mSnappingHorizontal;

		virtual void		MoveToSelf( SInt32 left, SInt32 top );
		virtual void		MouseInitial( const SMouseDownEvent &, SInt32 newCol, SInt32 newRow );

		virtual void		MouseStillDown( const SMouseDownEvent &, 
											Point prevMousePt, Point newMousePt,
											SInt32 prevCol, SInt32 prevRow,
											SInt32 newCol, SInt32 newRow );
								
		virtual Boolean		MouseFinal( const SMouseDownEvent &, 
											Point prevMousePt, Point newMousePt,
											SInt32 prevCol, SInt32 prevRow,
											SInt32 newCol, SInt32 newRow );
											
		virtual void		PostAsAction();	
};


// ============================================================
// 	CIconRotateAction 
// ============================================================

class CIconRotateAction : public CIconAction {
	public:
							CIconRotateAction( const SPaintAction &, SInt32 degrees );
		virtual void		DoIt();
		
	protected:
		SInt32				mDegrees;
		
		virtual void		TransformTheBits( COffscreen *inSource, COffscreen *inDest,
											  SInt32 sourceWidth, SInt32 sourceHeight );
};


// ============================================================
// 	CIconTransparentAction 
// ============================================================

class CIconTransparentAction : public CIconAction {
	public:
							CIconTransparentAction( const SPaintAction & );
		virtual void		DoIt();
};


// ============================================================
// 	CTransformAction 
// ============================================================

class CTransformAction : public CIconAction {
	public:
							CTransformAction( const SPaintAction &, SInt16 inStringIndex );
		
		virtual void		DoIt();
		
	protected:
		virtual RgnHandle	CalcNewSelectionRegion();
		virtual void		TransformTheBits( COffscreen * ) = 0;
};


// ============================================================
// 	CFlipVerticalAction 
// ============================================================

class CFlipVerticalAction : public CTransformAction {
	public:
							CFlipVerticalAction( const SPaintAction & );
		
	protected:
		virtual void		TransformTheBits( COffscreen * );
};


// ============================================================
// 	CFlipHorizontalAction 
// ============================================================

class CFlipHorizontalAction : public CTransformAction {
	public:
							CFlipHorizontalAction( const SPaintAction & );
		
	protected:
		virtual void		TransformTheBits( COffscreen * );
};


// ============================================================
// 	CDragPictureAction 
// ============================================================

typedef struct SDragImageInfo
{
	ResType				imageType;		// DragFlavor_Offscreen or ImageType_Picture
	void				*data;			// COffscreen * or Picture handle
	DragReference		dragRef;
	DragAttributes		dragAttribs;
} SDragImageInfo;


class CIconDragImageAction : public CIconAction {
	public:
							CIconDragImageAction( const SPaintAction &, SDragImageInfo * );
		virtual void		DoIt();
		
	protected:
		SDragImageInfo		mDragInfo;
};


// ============================================================
// 	CIconHotspotAction 
// ============================================================

class CIconHotSpotAction : public CIconTrackingPaintAction {
	public:
							CIconHotSpotAction( const SPaintAction & );
		virtual				~CIconHotSpotAction();
	
	protected:
		virtual void		MouseStillDown( const SMouseDownEvent &, 
											Point prevMousePt, Point newMousePt,
											SInt32 prevCol, SInt32 prevRow,
											SInt32 newCol, SInt32 newRow );
};


// ============================================================
// 	CIconDeleteImageAction 
// ============================================================

class CIconDeleteImageAction : public CIconAction {
	public:
								CIconDeleteImageAction( const SPaintAction & );
		virtual					~CIconDeleteImageAction();
		virtual void			DoIt();
		
	protected:
		CDraggableTargetBox *	mTargetBox;
		virtual void			RedoSelf();
};

