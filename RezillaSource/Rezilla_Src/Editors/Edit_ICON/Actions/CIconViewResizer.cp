// ===========================================================================
// CIconViewResizer.cp
//                       Created: 2004-12-11 18:52:34
//             Last modification: 2004-12-22 18:29:24
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "RezillaConstants.h"
#include "CIconViewResizer.h"
#include "CIcon_EditorWindow.h"
#include "UIconMisc.h"
#include "CDraggableTargetView.h"


// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------

CIconViewResizer::CIconViewResizer()
{
	mPaintView = nil;
	mImageBuffer = nil;
	mNumSamplePanes = 0;
}


// ---------------------------------------------------------------------------
// 	Initialize
// ---------------------------------------------------------------------------

void
CIconViewResizer::Initialize( CIcon_EditorWindow *pv )
{
	// Keep track of the window size & position
	mPaintView = pv;
	UIconMisc::GetWindowGlobalBounds( pv->GetMacWindow(), mWindowBounds );
	
	// Keep track of the original image buffer
	COffscreen *sourceBuffer = pv->GetImageBuffer();
	ThrowIfNil_( sourceBuffer );

	mImageBuffer = sourceBuffer->CreateSimilarOffscreen();
	mImageBuffer->CopyFrom( sourceBuffer );
	
	// Keep track of the sample well position & size
	this->GetPaneInfoByID( item_IconSampleWell, false,  &mSampleWellInfo );
	
	// Keep track of all of the current sample panes
	mNumSamplePanes = pv->GetSamplePaneCount();
	for ( SInt32 count = 1; count <= mNumSamplePanes; count++ )
	{
		CDraggableTargetView	*aTarget = pv->GetNthSamplePane( count );
		ThrowIfNil_( aTarget );
		this->GetPaneInfo( (LPane*) aTarget, true, &mSamplePaneInfo[ count - 1 ] );
	}
}


// ---------------------------------------------------------------------------
// 	RestoreWindowState 
// ---------------------------------------------------------------------------
// It is *very* important to allocate all of the buffers first, before
// irrevocably changing the paint view state. We don't want to leave things
// in a weird state if we run out of memory.

void
CIconViewResizer::RestoreWindowState()
{
	if ( !mPaintView ) return;
	
	try
	{
		mPaintView->ImageSizeChangeUndone( mImageBuffer->GetWidth(), mImageBuffer->GetHeight() );
		
		// This will change the scratch buffer, undo buffer, image buffer,
		// canvas size, etc. everything but the sample pane size.
		mPaintView->SetImage( mImageBuffer, resize_Canvas );
		
		// Restore other panes to the saved state
		this->SetPaneInfo( mSampleWellInfo );

		for ( SInt32 count = 0; count < mNumSamplePanes; count++ )
			this->SetPaneInfo( mSamplePaneInfo[ count ] );

		// Resize the window itself. User may have moved it, so resize it
		// in its current place, not where it was originally.
		Rect	r;
		UIconMisc::GetWindowGlobalBounds( mPaintView->GetMacWindow(), r );
		r.right = r.left + (mWindowBounds.right - mWindowBounds.left);
		r.bottom = r.top + (mWindowBounds.bottom - mWindowBounds.top);
		mPaintView->DoSetBounds( r );
	}
	catch( ... )
	{
		COffscreen *prevBuffer = mPaintView->GetImageBuffer();
		if ( prevBuffer )
			mPaintView->ImageSizeChangeUndone( prevBuffer->GetWidth(), prevBuffer->GetHeight() );
		throw;
	}

	// Redraw everything
	mPaintView->Refresh();
}


// ---------------------------------------------------------------------------
// 	Destructor 
// ---------------------------------------------------------------------------

CIconViewResizer::~CIconViewResizer()
{
	if ( mImageBuffer ) {
		delete mImageBuffer;
		mImageBuffer = nil;
	}
}


// ---------------------------------------------------------------------------
// 	DeleteAllBuffers
// ---------------------------------------------------------------------------

void
CIconViewResizer::DeleteAllBuffers()
{
	if ( mImageBuffer && (mPaintView->GetImageBuffer() != mImageBuffer) )	// can't hurt to check
	{
		delete mImageBuffer;
		mImageBuffer = nil;
	}
	
	for ( SInt32 count = 0; count < mNumSamplePanes; count++ ) {
		// Some sample panes can't be resized, so their buffers may not
		// have changed. Don't delete the buffers if they are in use.
		SSavedPaneInfo &info = mSamplePaneInfo[ count ];
		if ( info.buffer )
		{
			CDraggableTargetView	*aTarget = dynamic_cast<CDraggableTargetView*>( info.thePane );
			if ( aTarget && (aTarget->GetBuffer() != info.buffer) )
				delete info.buffer;
		}
	}
}


// ---------------------------------------------------------------------------
// 	GetPaneInfoByID
// ---------------------------------------------------------------------------

void
CIconViewResizer::GetPaneInfoByID( PaneIDT inPaneID, Boolean isTargetView, SSavedPaneInfo *outInfo )
{
	this->GetPaneInfo( mPaintView->FindPaneByID( inPaneID ), isTargetView, outInfo );
}


// ---------------------------------------------------------------------------
// 	GetPaneInfo
// ---------------------------------------------------------------------------

void
CIconViewResizer::GetPaneInfo( LPane *inPane, Boolean isTargetView, SSavedPaneInfo *outInfo )
{
	outInfo->thePane = inPane;
	if ( !inPane ) return;				// no sample well in the PICT editor, for example
	
	SDimension16	frameSize;
	SPoint32		frameLocation;
	
	inPane->GetFrameSize( frameSize );
	inPane->GetFrameLocation( frameLocation );
	
	outInfo->top = frameLocation.v;
	outInfo->left = frameLocation.h;
	outInfo->width = frameSize.width;
	outInfo->height = frameSize.height;
	
	if ( isTargetView ) {
		CDraggableTargetView *theTarget = dynamic_cast<CDraggableTargetView*>( inPane );
		ThrowIfNil_( theTarget );
		
		outInfo->buffer = theTarget->GetBuffer();
	}
	else
		outInfo->buffer = nil;
}


// ---------------------------------------------------------------------------
// 	SetPaneInfo
// ---------------------------------------------------------------------------

void
CIconViewResizer::SetPaneInfo( SSavedPaneInfo &info )
{
	if ( !info.thePane ) return;		// no sample well in the PICT editor
	
	// Resize and move the pane back where it belongs
	info.thePane->ResizeFrameTo( info.width, info.height, false );
	
	SPoint32	frameLocation;
	info.thePane->GetFrameLocation( frameLocation );
	info.thePane->MoveBy( info.left - frameLocation.h, info.top - frameLocation.v, false );

	// Set the buffer if it's a target pane
	if ( info.buffer ) {
		CDraggableTargetView *theTarget = dynamic_cast<CDraggableTargetView*>( info.thePane );
		ThrowIfNil_( theTarget );
		theTarget->SetRawBuffer( info.buffer );
	}
}


