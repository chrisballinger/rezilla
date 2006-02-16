// ===========================================================================
// CSingleScrollBar.cp					
// 
//                       Created: 2004-03-19 13:49:48
//             Last modification: 2004-03-20 07:25:40
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// ===========================================================================

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CSingleScrollBar.h"
#include <LControlImp.h>
#include <PP_Messages.h>
#include <UDrawingState.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   CSingleScrollBar							Stream Constructor		  [public]
// ---------------------------------------------------------------------------

CSingleScrollBar::CSingleScrollBar(
	LStream*	inStream,
	ClassIDT	inImpID)

	: LScrollBar(inStream, inImpID)
{
	mLinesPerPage = 1;
}


// ---------------------------------------------------------------------------
//   CSingleScrollBar							Parameterized Constructor [public]
// ---------------------------------------------------------------------------

CSingleScrollBar::CSingleScrollBar(
	const SPaneInfo&	inPaneInfo,
	MessageT			inValueMessage,
	SInt32				inValue,
	SInt32				inMinValue,
	SInt32				inMaxValue,
	bool				inLiveScrolling,
	ClassIDT			inImpID)

	: LScrollBar(inPaneInfo, inValueMessage, inValue, inMinValue,
					inMaxValue, inLiveScrolling, inImpID)
{
	mLinesPerPage = 1;
}


// ---------------------------------------------------------------------------
//     ~CSingleScrollBar							Destructor				  [public]
// ---------------------------------------------------------------------------

CSingleScrollBar::~CSingleScrollBar()
{
}


// ---------------------------------------------------------------------------
//   DoTrackAction													  [public]
// ---------------------------------------------------------------------------

void
CSingleScrollBar::DoTrackAction(
	SInt16	inHotSpot,
	SInt32	inValue)
{
	if (inHotSpot >= kControlIndicatorPart) {	// Thumb is being dragged
		LControl::SetValue(inValue);			// Synch PP's value with Control Mgr value
	} else {
		switch (inHotSpot) {				// Determine how much to scroll

			case kControlUpButtonPart:		// Scroll up one unit
				--inValue;
				break;

			case kControlDownButtonPart:	// Scroll down one unit
				++inValue;
				break;

			case kControlPageUpPart:		// Scroll up by Frame height
											//   less one unit of overlap
				inValue -= mLinesPerPage;
				break;

			case kControlPageDownPart:		// Scroll down by Frame height
											//   less one unit of overlap
				inValue += mLinesPerPage;
				break;
		}
		// Caveat: here call SetValue (i-e LControlPane::SetValue) 
		// and not LControl::SetValue
		SetValue(inValue);
	}
}



PP_End_Namespace_PowerPlant
