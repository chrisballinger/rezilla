// ===========================================================================
// CIconLassoAction.h
//                       Created: 2004-12-11 18:57:00
//             Last modification: 2004-12-14 18:57:00
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CIconActions.h"
#include "CMarchingAnts.h"

class CIconLassoAction : public CIconTrackingPaintAction
{
	public:
						CIconLassoAction( const SPaintAction & );
		virtual			~CIconLassoAction();
		
		virtual void 	HandleMouseDown( const SMouseDownEvent &inEvent );
		virtual void	DoIt();			// for "lasso all"
		
	protected:
		#define kMaxPoints	5000
		SInt32				mNumPoints;
		Point				*mPointArray;
		
		SInt32				mImageWidth, mImageHeight;
		Rect				mTopLeftPixelRect;
		SInt32				mCellWidth, mSpaceBetweenCells, mTotalCellWidth;
		CMarchingAnts		mMarchingAnts;	
		//Boolean				mAntsDrawn;
		Boolean				mUseXorMode;

		virtual void		MouseInitial( const SMouseDownEvent &, SInt32 newCol, SInt32 newRow );

		virtual void		MouseStillDown( const SMouseDownEvent &, 
											Point prevMousePt, Point newMousePt,
											SInt32 prevCol, SInt32 prevRow,
											SInt32 newCol, SInt32 newRow );
											 		
		virtual Boolean		MouseFinal( const SMouseDownEvent &, 
											Point prevMousePt, Point newMousePt,
											SInt32 prevCol, SInt32 prevRow,
											SInt32 newCol, SInt32 newRow );

		virtual void		FindClosestNode( const Point &, SInt32 *outH, SInt32 *outV );
		
		virtual Boolean 	AddPointToArray( SInt32 newCol, SInt32 newRow );
		virtual void		RemovePointFromArray();
		
			// drawing the array as the user moves the mouse
		//virtual void		XorArray();
		//virtual void		XorOneSegment( SInt32 inSegmentNo );
		
		virtual void		DrawSegment( SInt32 inSegmentNo );
		virtual void		DrawArray();
		virtual void		AnimateArray();
		
			// after the mouse is releases, these are used
		virtual RgnHandle	ConvertArrayToRegion();
		virtual void		RestrictRegion( RgnHandle );
		virtual Boolean		IsArrayLinear();
		virtual void		CopyAndDownSample( COffscreen *src, COffscreen *dst, RgnHandle selRgn );
};

