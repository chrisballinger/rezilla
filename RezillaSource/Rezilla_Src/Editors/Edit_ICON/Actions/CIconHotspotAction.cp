// ===========================================================================
// CIconHotspotAction.cp
//                       Created: 2004-12-11 18:52:22
//             Last modification: 2004-12-14 18:52:22
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// ===========================================================================

#include "RezillaConstants.h"
#include "CIconActions.h"
#include "CIcon_EditorView.h"
// #include "CIcon_EditorWindow.h"
#include "COffscreen.h"


// ---------------------------------------------------------------------------
// 	CIconHotSpotAction											 [constructor]
// ---------------------------------------------------------------------------

CIconHotSpotAction::CIconHotSpotAction( const SPaintAction &inSettings )
	: CIconTrackingPaintAction( inSettings, index_UndoHotSpot )
{
	this->ThrowIfFileLocked();
}


// ---------------------------------------------------------------------------
// 	CIconHotSpotAction											 [destructor]
// ---------------------------------------------------------------------------

CIconHotSpotAction::~CIconHotSpotAction()
{
}


// ---------------------------------------------------------------------------
// 	MouseStillDown
// ---------------------------------------------------------------------------

void 
CIconHotSpotAction::MouseStillDown( const SMouseDownEvent &, 
										Point, Point,
										SInt32, SInt32,
										SInt32 newCol, SInt32 newRow )
{
	CIcon_EditorView *		theCanvas = mSettings.theCanvas;
	COffscreen *	theBuffer = mSettings.currentBuffer;

	Point	oldSpot = theCanvas->GetHotSpot();
	
	if ( ((oldSpot.h != newCol) || (oldSpot.v != newRow)) &&
			(newCol >= 0) && (newCol < theBuffer->GetWidth()) &&
		 	(newRow >= 0) && (newRow < theBuffer->GetHeight()) )
	{
		Point	newSpot = { newRow, newCol };
		theCanvas->SetHotSpot( newSpot );
		
			// canvas doesn't redraw automatically, so do so here
		theCanvas->DrawOnePixel( oldSpot.h, oldSpot.v, theBuffer );
		theCanvas->DrawOnePixel( newSpot.h, newSpot.v, theBuffer );
	}
}
