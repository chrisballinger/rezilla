// ===========================================================================
// CImageDragDrop.cp
//                       Created: 2004-12-11 18:57:41
//             Last modification: 2004-12-22 11:28:29
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CImageDragDrop.h"
#include "COffscreen.h"
#include "RezillaConstants.h"
#include "COffscreenDragTask.h"			// for DragFlavor_Offscreen
#include "UIconMisc.h"
#include "UGraphicConversion.h"


// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------

CImageDragDrop::CImageDragDrop( WindowPtr inMacWindow, LPane *inPane )
			: LDragAndDrop( inMacWindow, inPane )
{
}


// ---------------------------------------------------------------------------
// 	ItemIsAcceptable
// ---------------------------------------------------------------------------

Boolean
CImageDragDrop::ItemIsAcceptable( DragReference inDragRef, ItemReference inItemRef )
{
	OSErr				err = noErr;
	FlavorFlags			theFlags;
	HFSFlavor			hfsInfo;
	PromiseHFSFlavor	promiseInfo;
	
	// do we need to check the flags for anything ???
	// is the promise code correct ???
	
	err = ::GetFlavorFlags( inDragRef, inItemRef, DragFlavor_Offscreen, &theFlags );
	if ( !err ) return( true );
	
	err = ::GetFlavorFlags( inDragRef, inItemRef, ImgType_Picture, &theFlags );
	if ( !err ) return( true );
	
	long numBytes = sizeof( hfsInfo );
	err = ::GetFlavorData( inDragRef, inItemRef, flavorTypeHFS, (void*) &hfsInfo, &numBytes, 0 );
	if ( !err && (hfsInfo.fileType == ImgType_Picture) ) return( true );
	
	numBytes = sizeof( promiseInfo );
	err = ::GetFlavorData( inDragRef, inItemRef, flavorTypePromiseHFS, (void*) &promiseInfo, &numBytes, 0 );
	if ( !err && (promiseInfo.fileType == ImgType_Picture) ) return( true );

	return( false );
}



// ---------------------------------------------------------------------------
// 	ReceiveDragItem
// ---------------------------------------------------------------------------

void
CImageDragDrop::ReceiveDragItem( DragReference inDragRef, DragAttributes inAttribs,
										ItemReference inItemRef, Rect & )
{
	OSErr			err = noErr;
	long			numBytes;
	StGWorldSaver	aSaver;
	
	// First see if we get a COffscreen (internal drag)
	err = ::GetFlavorDataSize( inDragRef, inItemRef, DragFlavor_Offscreen, &numBytes );
	if ( !err && (numBytes == sizeof(COffscreen*)) )
	{
		COffscreen		*draggedBuffer = nil;
		
		err = ::GetFlavorData( inDragRef, inItemRef, DragFlavor_Offscreen, &draggedBuffer, &numBytes, 0 );
		if ( err ) return;
		
		this->HandleDroppedOffscreen( draggedBuffer, inDragRef, inAttribs );
		return;
	}
	
	// Next check for a PICT
	err = ::GetFlavorDataSize( inDragRef, inItemRef, ImgType_Picture, &numBytes );
	if ( !err && (numBytes >= sizeof(Picture)) )
	{
		PicHandle thePict = (PicHandle) ::NewHandle( numBytes );
		ThrowIfMemFail_( thePict );

		HLock( (Handle) thePict );
		err = ::GetFlavorData( inDragRef, inItemRef, ImgType_Picture, (void*) *thePict, &numBytes, 0 );
		if ( err )
		{
			UIconMisc::DisposeHandle( (Handle) thePict );
			Throw_( err );
		}
		
		HUnlock( (Handle) thePict );
		
		this->HandleDroppedPicture( thePict, inDragRef, inAttribs );
		UIconMisc::DisposeHandle( thePict );
		return;
	}	
	
	// Next check for a PICT file
	HFSFlavor			hfsInfo;
	numBytes = sizeof( hfsInfo );
	err = ::GetFlavorData( inDragRef, inItemRef, flavorTypeHFS, (void*) &hfsInfo, &numBytes, 0 );
	if ( !err )
		this->HandleDroppedPictureFile( hfsInfo.fileSpec, inDragRef, inAttribs );
		
	if ( err )
		Throw_( err );
}


// ---------------------------------------------------------------------------
// 	HandleDroppedPictureFile
// ---------------------------------------------------------------------------

void
CImageDragDrop::HandleDroppedPictureFile( const FSSpec &inSpec, DragReference inDragRef,
												DragAttributes inAttribs )
{
	PicHandle		thePict = nil;
	
	try
	{
		thePict = UGraphicConversion::GetPictFromFile( inSpec );
		this->HandleDroppedPicture( thePict, inDragRef, inAttribs );
	}
	catch( ... )
	{
		UIconMisc::DisposeHandle( (Handle) thePict );
		throw;
	}
	
	UIconMisc::DisposeHandle( (Handle) thePict );
}


// ---------------------------------------------------------------------------
// 	HiliteDropArea
// ---------------------------------------------------------------------------
// Hilites the drag area by drawing a few xor-ed rectangles around mPane.
// The default hiliting doesn't show up very well at all for our panes so
// this one is somewhat thicker and drawn outside of the pane itself.

void
CImageDragDrop::HiliteDropArea( DragReference )
{
	Rect	r;
	mPane->CalcLocalFrameRect( r );	

	StColorPenState			thePen;
	thePen.Normalize();
	::PenMode( patXor );

	//RGBColor	aGray = { 56797, 56797, 56797 };
	RGBColor	aGray = { 0xFFFF, 0xFFFF, 0xFFFF };
	RGBForeColor( &aGray );
	
	// Don't want any clipping since we draw outside of the pane	
	Rect	bigClipR = { -15000, -15000, 15000, 15000 };
	StClipRgnState	aClip( bigClipR );		// want to draw outside of the pane too
	
	// Draw some rectangles
	#define kThickness		3
	for ( long count = 0; count < kThickness; count++ )
	{
		::FrameRect( &r );
		::InsetRect( &r, -1, -1 );
	}
}


// ---------------------------------------------------------------------------
// 	UnhiliteDropArea
// ---------------------------------------------------------------------------

void
CImageDragDrop::UnhiliteDropArea( DragReference inDragRef )
{
	this->HiliteDropArea( inDragRef );		// since it xors
}

