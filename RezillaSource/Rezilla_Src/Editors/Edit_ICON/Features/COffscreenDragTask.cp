// ===========================================================================
// COffscreenDragTask.cp
//                       Created: 2004-12-11 18:53:14
//             Last modification: 2004-12-14 18:53:14
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// ===========================================================================

#include "COffscreenDragTask.h"
#include "COffscreen.h"
#include "UGraphicConversion.h"
#include "RezillaConstants.h"

#ifndef __MACH__
#include <Drag.h>
#endif


// ============================================================
// 	Constructor
// 	
// 	This is the only routine you need to call.
// ============================================================

COffscreenDragTask::COffscreenDragTask( const EventRecord &inEvent, const Rect &inRect, COffscreen *inOffscreen )
						: LDragTask( inEvent )
{
	DragSendDataUPP		sendUPP = nil;
	long				err = noErr;
	
	try
	{
		// Add the rectangle to the drag ref, or a pixmap is even better
		Rect	globalRect = inRect;
		::LocalToGlobal(&topLeft(globalRect));
		::LocalToGlobal(&botRight(globalRect));
		AddRectDragItem( (ItemReference) inOffscreen, globalRect );
		
		// Add the flavors to the drag ref. Don't translate the offscreen
		// to a PICT unless a receiver requests it.
		err = ::AddDragItemFlavor( mDragRef, (ItemReference) inOffscreen, DragFlavor_Offscreen, &inOffscreen, sizeof(inOffscreen), flavorSenderOnly );	
		ThrowIfOSErr_( err );
		
		err = ::AddDragItemFlavor( mDragRef, (ItemReference) inOffscreen, ImgType_Picture, nil, 0, 0 );	
		ThrowIfOSErr_( err );
		
		// Add a sendproc that can translate the offscreen to a PICT
		sendUPP = ::NewDragSendDataUPP( SendProc );
		ThrowIfMemFail_( sendUPP );
		
		err = ::SetDragSendProc( mDragRef, sendUPP, nil );
		ThrowIfOSErr_( err );
	
		// Do the drag
		err = ::TrackDrag( mDragRef, &mEventRecord, mDragRegion );
	}
	catch( ... )
	{
		if ( sendUPP ) {
			::DisposeDragSendDataUPP( sendUPP );
		}
		throw;
	}
	
	if ( sendUPP ) {
		::DisposeDragSendDataUPP( sendUPP );
	}
}


// ============================================================
// 	Destructor
// ============================================================

COffscreenDragTask::~COffscreenDragTask()
{
}


// ============================================================
// 	SendProc
// ============================================================

pascal OSErr
COffscreenDragTask::SendProc( FlavorType inFlavor, void * /*inRefCon*/, ItemReference inItemRef, DragReference inDragRef )

{
	long	err = noErr;
	
	if ( inFlavor != ImgType_Picture )
	{
		return( noTypeErr );
	}

	try
	{
		// Convert the offscreen to a PICT
		PicHandle thePict = UGraphicConversion::OffscreenToPicture( (COffscreen*) inItemRef, nil );
		
		// Set the drag item to the data
		::HLock( (Handle) thePict );
		err = ::SetDragItemFlavorData( inDragRef, inItemRef, inFlavor, (void*) *thePict, 
						::GetHandleSize( (Handle) thePict ), 0 );
						
		// Cleanup
		::KillPicture( thePict );
	}
	catch( long anErr )
	{
		// Don't throw error out of callback -- bad things happen
		err = anErr;
	}
	
	return( err );
}

