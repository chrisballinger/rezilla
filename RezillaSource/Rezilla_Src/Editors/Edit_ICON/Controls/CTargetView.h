// ===========================================================================
// CTargetView.h
//                       Created: 2004-12-11 18:57:50
//             Last modification: 2005-01-08 07:10:03
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004, 2005
// All rights reserved.
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
		
		virtual void		SetTarget( Boolean inHasTarget, RedrawOptions inRedraw );
		
		virtual void		DrawBorder();
		virtual void		EraseBorder();

	protected:
		Boolean				mHasTarget;
		
};


#endif // _H_CTargetView
