// ===========================================================================
// CTargetView.h
//                       Created: 2004-12-11 18:57:50
//             Last modification: 2004-12-28 10:01:47
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CTargetView
#define _H_CTargetView
#pragma once

#include "RezillaConstants.h"


#include <LBroadcaster.h>
#include <LView.h>


class CTargetView : public LView, public LBroadcaster {
	public:
		enum { class_ID = FOUR_CHAR_CODE('TgVw') };
		
							CTargetView( LStream * );
		virtual				~CTargetView();
	
		static CTargetView *	CreateFromStream( LStream *inStream );
		
		virtual void		SetTarget( Boolean inTarget, ERedrawOptions inRedraw );
		
	protected:
		Boolean				mHasTarget;
		
		virtual void		DrawTargettedFrame( const Rect &inBorderRect, Boolean inColor = true );

		virtual void		GetBackgroundColor( RGBColor *outColor );
};


#endif // _H_CTargetView
