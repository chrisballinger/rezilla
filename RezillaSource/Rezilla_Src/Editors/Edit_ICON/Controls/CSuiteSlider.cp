// ===========================================================================
// CSuiteSlider.cp					
//                       Created: 2005-01-10 09:03:25
//             Last modification: 2005-01-10 09:38:30
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
// Subclass the LSlider class to override the HotSpotResult function
// and update the bitmap view after the slider has been tracked.


#include "CSuiteSlider.h"
#include "CWindow_PatternSuite.h"

#include <LControlImp.h>
#include <LStream.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//	¥ CSuiteSlider							Stream Constructor		  [public]
// ---------------------------------------------------------------------------

CSuiteSlider::CSuiteSlider(
	LStream*	inStream)
	: LSlider(inStream)
{
	mOwnerWindow = nil;
}


// ---------------------------------------------------------------------------
//	¥ ~CSuiteSlider							Destructor				  [public]
// ---------------------------------------------------------------------------

CSuiteSlider::~CSuiteSlider()
{
}


// ---------------------------------------------------------------------------
//	¥ DoTrackAction													  [public]
// ---------------------------------------------------------------------------

void
CSuiteSlider::DoTrackAction(
	SInt16	/* inHotSpot */,
	SInt32	inValue)
{
	LControl::SetValue(inValue);
}


// ---------------------------------------------------------------------------
//	¥ HotSpotResult													  [public]
// ---------------------------------------------------------------------------
//	Perform result of clicking and releasing mouse inside a HotSpot

void
CSuiteSlider::HotSpotResult(
	SInt16	/* inHotSpot */)
{
	if (mOwnerWindow != NULL) {
		mOwnerWindow->SwitchToNthPattern(mValue);
	} 
}


PP_End_Namespace_PowerPlant
