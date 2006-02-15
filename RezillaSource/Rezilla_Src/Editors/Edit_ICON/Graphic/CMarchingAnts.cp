// ===========================================================================
// CMarchingAnts.cp
//                       Created: 2004-12-11 18:52:50
//             Last modification: 2004-12-23 23:40:08
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// ===========================================================================

#include "CMarchingAnts.h"
#include "RezillaConstants.h"


// Statics
Pattern	CMarchingAnts::sAntPattern = {  0xF8, 0xF1, 0xE3, 0xC7, 0x8F, 0x1F, 0x3E, 0x7C };
UInt32	CMarchingAnts::sNextMarchTime = 0;


// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------

CMarchingAnts::CMarchingAnts()
{
	mDelay = kDefaultMarchInterval;
}


// ---------------------------------------------------------------------------
// 	GetDelay
// ---------------------------------------------------------------------------

UInt32
CMarchingAnts::GetDelay()
{
	return( mDelay );
}


// ---------------------------------------------------------------------------
// 	SetDelay
// ---------------------------------------------------------------------------

void
CMarchingAnts::SetDelay( UInt32 inDelay )
{
	mDelay = inDelay;		// will take effect next time we draw
}



// ---------------------------------------------------------------------------
// 	TimeToDraw
// ---------------------------------------------------------------------------

Boolean
CMarchingAnts::TimeToDraw()
{
	return( (UInt32) TickCount() > sNextMarchTime );
}


// ---------------------------------------------------------------------------
// 	GetPattern
// ---------------------------------------------------------------------------

void
CMarchingAnts::GetPattern( Pattern *outPattern )
{
	*outPattern = sAntPattern;
}


// ---------------------------------------------------------------------------
// 	IncrementPattern
// ---------------------------------------------------------------------------

void
CMarchingAnts::IncrementPattern()
{
	unsigned char	lastRow = sAntPattern.pat[7];
	for (SInt16 i = 7; i > 0; i--) 
		sAntPattern.pat[i] = sAntPattern.pat[i - 1];
	sAntPattern.pat[0] = lastRow;

	sNextMarchTime = (UInt32) TickCount() + mDelay;
}

