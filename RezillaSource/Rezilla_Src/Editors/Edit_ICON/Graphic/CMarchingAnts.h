// ===========================================================================
// CMarchingAnts.h
//                       Created: 2004-12-11 18:57:19
//             Last modification: 2004-12-14 18:57:19
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// ===========================================================================

#ifndef _H_CMarchingAnts
#define _H_CMarchingAnts
#pragma once

class CMarchingAnts {
	public:
							CMarchingAnts();
							
		virtual Boolean		TimeToDraw();
		virtual void		GetPattern( Pattern * );
		virtual void		IncrementPattern();
		
		virtual UInt32		GetDelay();
		virtual void		SetDelay( UInt32 inTicks );
		
	protected:
		UInt32				mDelay;
		static Pattern		sAntPattern;
		static UInt32		sNextMarchTime;
};

#endif // _H_CMarchingAnts
