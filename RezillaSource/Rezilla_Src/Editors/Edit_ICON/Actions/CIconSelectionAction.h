// ===========================================================================
// CIconSelectionAction.h
//                       Created: 2004-12-11 18:57:08
//             Last modification: 2004-12-14 18:57:08
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
#ifndef _H_CIconSelectionAction
#define _H_CIconSelectionAction

#include "CIconActions.h"
#include "CMarchingAnts.h"


// ---------------------------------------------------------------------------
// 	CIconSelectionAction 
// ---------------------------------------------------------------------------

class CIconSelectionAction : public CIconTrackingPaintAction
{
	public:
							CIconSelectionAction( const SPaintAction & );
		virtual				~CIconSelectionAction();

		virtual void 		HandleMouseDown( const SMouseDownEvent &inEvent );

	protected:
		Point				mMouseDownPt;
		Rect				mMouseDownCellR;
		
		Rect				mPrevDrawnRect;
		Rect				mCurrentSelection;
		CMarchingAnts		mMarchingAnts;	
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

		virtual void		DrawNewRect( const Rect & );
		virtual void		EraseOldRect();
};

#endif // _H_CIconSelectionAction
