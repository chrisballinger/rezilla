// ===========================================================================
// CSnapTo.h
//                       Created: 2004-12-11 18:52:40
//             Last modification: 2004-12-14 18:52:40
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#ifndef _H_CSnapTo
#define _H_CSnapTo
#pragma once

class CSnapTo {
	public:
		enum ESnapTo { kDontSnap, kSnapTo45, kSnapTo90, kSnapToRect };
		
					CSnapTo();
	
		void		SetAngle( ESnapTo angle );
		
		void 		SnapToPoint( Point startPt, Point currentPt, Point *outPt );	
		void		SnapTo( SInt32 origH, SInt32 origV, SInt32 newH, SInt32 newV, 
							SInt32 *outH, SInt32 *outV );
		
	protected:
		Boolean		mSnappingHorizontal;
		Boolean		mHaveMovedSinceMouseDown;
		ESnapTo		mSnapAngle;
		
		void		SnapTo45( Point startPt, Point currentPt, Point *outPt );
		void		SnapTo90( Point startPt, Point currentPt, Point *outPt );
		void		SnapToRect( Point startPt, Point currentPt, Point *outPt );
};

#endif // _H_CSnapTo
