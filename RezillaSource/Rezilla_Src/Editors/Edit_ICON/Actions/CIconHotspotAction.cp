// ===========================================================================
// CIconHotspotAction.cp
//                       Created: 2004-12-11 18:52:22
//             Last modification: 2004-12-14 18:52:22
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "RezillaConstants.h"
#include "CIconActions.h"

CIconHotSpotAction::CIconHotSpotAction( const SPaintAction &inSettings )
	: CIconTrackingPaintAction( inSettings, index_UndoHotSpot )
{
	this->ThrowIfFileLocked();
}

CIconHotSpotAction::~CIconHotSpotAction()
{
}

void CIconHotSpotAction::MouseStillDown( const SMouseDownEvent &, 
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
