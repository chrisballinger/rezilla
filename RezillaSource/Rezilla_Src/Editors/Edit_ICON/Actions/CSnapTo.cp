// ===========================================================================
// CSnapTo.cp
//                       Created: 2004-12-11 18:52:39
//             Last modification: 2005-01-02 15:43:36
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004, 2005
// All rights reserved.
// ===========================================================================

#include "CSnapTo.h"
#include "CIconActions.h"
#include "UMiscUtils.h"

//#include <math.h>
#ifndef __MACH__
#include <fp.h>
#endif

#define pi 3.141592653589793238462643


// ---------------------------------------------------------------------------
// 	CSnapTo											 [constructor]
// ---------------------------------------------------------------------------

CSnapTo::CSnapTo()
{
	mSnappingHorizontal = false;
	mHaveMovedSinceMouseDown = false;
	mSnapAngle = kSnapToRect;
}


// ---------------------------------------------------------------------------
// 	SetAngle
// ---------------------------------------------------------------------------

void
CSnapTo::SetAngle( ESnapTo inAngle )
{
	mSnapAngle = inAngle;
}


// ---------------------------------------------------------------------------
// 	SnapTo
// ---------------------------------------------------------------------------
// 	This routine maxes out at 32K because we use Point structures in the
// 	call. We should probably fix this, but since QuickDraw maxes out at 32K
// 	anyway, this isn't a big deal.

void
CSnapTo::SnapTo(SInt32 origH, SInt32 origV, SInt32 newH, SInt32 newV, 
						SInt32 *outH, SInt32 *outV )
{
	Point	origPt = { origV, origH };
	Point	newPt =  { newV, newH };
	
	this->SnapToPoint( origPt, newPt, &newPt );
	*outH = newPt.h;
	*outV = newPt.v;
}


// ---------------------------------------------------------------------------
// 	SnapToPoint
// ---------------------------------------------------------------------------

void
CSnapTo::SnapToPoint( Point startPt, Point currentPt, Point *outPt )
{
	*outPt = currentPt;
	
	switch( mSnapAngle )
	{
		case kSnapTo45:
			this->SnapTo45( startPt, currentPt, outPt );
			break;
			
		case kSnapTo90:
			this->SnapTo90( startPt, currentPt, outPt );
			break;
			
		case kSnapToRect:
			this->SnapToRect( startPt, currentPt, outPt );
			break;
	}
}


// ---------------------------------------------------------------------------
// 	SnapTo90
// ---------------------------------------------------------------------------
// 	This is used by the pen, eraser, and move tools. These tools snap to a
// 	vertical or horizontal line, but only if the shift key was down at the
// 	initial mouseDown event.

void
CSnapTo::SnapTo90( Point startPt, Point currentPt, Point *outPt )
{
	*outPt = currentPt;					// assume no change
	
	//if ( !UMiscUtils::IsShiftKey() ) return;		// we go by initial click only

	if ( !mHaveMovedSinceMouseDown )
	{
		if ( EqualPt( startPt, currentPt ) )
			return;
			
		// See which direction we've moved in most
		if ( ABS(startPt.h - currentPt.h) >= ABS(startPt.v - currentPt.v) )
			mSnappingHorizontal = true;
		else
			mSnappingHorizontal = false;
						
		mHaveMovedSinceMouseDown = true;
	}
	
	if ( mSnappingHorizontal )
		outPt->v = startPt.v;
	else
		outPt->h = startPt.h;
}



// ---------------------------------------------------------------------------
// 	SnapToRect
// ---------------------------------------------------------------------------
// 	This is used by the rectangle tools (rect, oval, roundrect) and the
// 	rectangular selection tool.

void
CSnapTo::SnapToRect( Point startPt, Point currentPt, Point *outPt )
{
	// Assume no change in point
	*outPt = currentPt;
	
	if ( !UMiscUtils::IsShiftKey() ) return;

	// See how far we've moved in each direction
	long	dh = currentPt.h - startPt.h;
	long	dv = currentPt.v - startPt.v;
	long	absDH = ABS( dh );
	long	absDV = ABS( dv );
	
	// Use the bigger of the width or height
	if ( absDH > absDV )
	{
		if ( dv > 0 )
			outPt->v = startPt.v + absDH;
		else
			outPt->v = startPt.v - absDH;
	}
	else
	{
		if ( dh > 0 )
			outPt->h = startPt.h + absDV;
		else
			outPt->h = startPt.h - absDV;
	}
}


// ---------------------------------------------------------------------------
// 	SnapTo45
// ---------------------------------------------------------------------------
// 	Snaps to a 45 degree angle if the shift key is down.
// 	This is used by the Line tool.

void
CSnapTo::SnapTo45( Point startPt, Point currentPt, Point *outPt )
{
	// Assume no change in point
	*outPt = currentPt;
	
	if ( !UMiscUtils::IsShiftKey() ) return;
	
	// Radian/degree conversions (I like degrees, C library likes radians)
	#define TO_RAD( deg )	( (deg) / 180.0 * pi )
	#define TO_DEG( rad )	( (rad) / pi * 180.0 )

	// See how far we've moved in each direction
	long	dh = currentPt.h - startPt.h;
	long	dv = startPt.v - currentPt.v;		// opposite since plus is down, not up
	
	// No need for any calculations if we're already at 90 degrees
	if ( (dh == 0) || (dv == 0) ) 
		return;

	// Use whichever coordinate is longer as the h/v length
	long	maxHV = MAX( ABS(dh), ABS(dv) );
	
	// Get the angle between the starting point and the current point.
	// Force it positive if it is less than zero (easier to deal with).
	double angle = atan2( (double)dv, (double)dh );		// returns value between +- pi
	
	if ( angle < 0 )
		angle += 2 * pi;				// same angle, just 360 degrees bigger
		
			// round angle to nearest 45 degrees

	const double	k22inRads = TO_RAD( 22.5 );
	const double	k45inRads = TO_RAD( 45.0 );
	
	angle = TO_DEG( k45inRads * floor( (angle + k22inRads) / k45inRads ) );
	
	// Fix the coordinates depending on which of 8 angles we are gridding to
	switch( (long) (angle + 0.5) )
	{
		case 0:
		case 360:
			outPt->v = startPt.v;
			break;
		case 45:
			outPt->v = startPt.v - maxHV;
			outPt->h = startPt.h + maxHV;
			break;
		case 90:
			outPt->h = startPt.h;
			break;
		case 135:
			outPt->v = startPt.v - maxHV;
			outPt->h = startPt.h - maxHV;
			break;
		case 180:
			outPt->v = startPt.v;
			break;
		case 225:
			outPt->v = startPt.v + maxHV;
			outPt->h = startPt.h - maxHV;
			break;
		case 270:
			outPt->h = startPt.h;
			break;
		case 315:
			outPt->v = startPt.v + maxHV;
			outPt->h = startPt.h + maxHV;
			break;
		default:
			DebugStr( LStr255("Bad value in MapTo45") );
	}
}
