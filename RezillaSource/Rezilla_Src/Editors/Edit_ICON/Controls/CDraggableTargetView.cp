// ===========================================================================
// CDraggableTargetView.cp
//                       Created: 2004-12-11 18:53:16
//             Last modification: 2005-01-08 11:49:01
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "COffscreen.h"
#include "CColorCursorCache.h"
#include "UIconMisc.h"
#include "CDraggableTargetView.h"
#include "RezillaConstants.h"
#include "COffscreenDragTask.h"

#include <UDrawingState.h>

// UserCon flags (stored in userCon of pane)
const UInt32	targetFlag_IsMask		= 0x0001;
const UInt32	targetFlag_CanDelete	= 0x0002;


// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------

CDraggableTargetView::CDraggableTargetView( LStream *inStream )
		: CTargetView( inStream ), 
		CImageDragDrop( UQDGlobals::GetCurrentWindowPort(), this )
{
	mCursorCache = CColorCursorCache::GetCurrentCache();
	mBuffer = nil;
	mIsUsed = true;						// assume we're not deleted

	UInt32	refCon = this->GetUserCon();
	mIsMask = (refCon & targetFlag_IsMask) ? true : false;
	mCanBeDeleted = (refCon & targetFlag_CanDelete) ? true : false;
	
	// These are for resizing support
	this->GetFrameSize( mInitialPaneSize );
	this->GetFrameLocation( mInitialPaneLocation );
	mMinPaneSize.width = kIconMinTargetWidth;
	mMinPaneSize.height = kIconMinTargetHeight;
	
	mDropEnabled = true;
}


// ---------------------------------------------------------------------------
// 	Destructor
// ---------------------------------------------------------------------------

CDraggableTargetView::~CDraggableTargetView()
{
	if ( mBuffer )
		delete mBuffer;
}


// ---------------------------------------------------------------------------
// 	CreateFromStream
// ---------------------------------------------------------------------------

CDraggableTargetView *
CDraggableTargetView::CreateFromStream( LStream *inStream )
{
	return new CDraggableTargetView( inStream );
}


// ---------------------------------------------------------------------------
// 	AdjustMouseSelf
// ---------------------------------------------------------------------------

void 
CDraggableTargetView::AdjustMouseSelf( Point, const EventRecord &, RgnHandle )
{
	if ( mCursorCache && mBuffer )
		mCursorCache->SetColorCursor( CURS_HandFingers );
}


// ---------------------------------------------------------------------------
// 	ClickSelf
// ---------------------------------------------------------------------------

void
CDraggableTargetView::ClickSelf( const SMouseDownEvent &inMouseDown )
{
	// If Drag&Drop isn't present or the user just clicks the mouse quickly
	// without moving it, broadcast a message
	if ( !LDragAndDrop::DragAndDropIsPresent() ) {
		this->BroadcastMessage( msg_TargetViewClicked, this );
		return;
	}

	// Wait for mouse to move a little -- if it doesn't, broadcast
	if ( !::WaitMouseMoved( inMouseDown.macEvent.where ) ) {
		this->BroadcastMessage( msg_TargetViewClicked, this );
		return;
	}
	
	// The user moved the mouse while it was down... perform a drag
	// operation
	if ( mBuffer ) {
		Rect	localR;
		
		this->FocusDraw();
		this->CalcLocalFrameRect( localR );
		COffscreenDragTask	theDragTask( inMouseDown.macEvent, localR, mBuffer );
	}
}


// ---------------------------------------------------------------------------
// 	SetBuffer
// ---------------------------------------------------------------------------
// Once this call is made, this object takes complete control of the buffer.

void
CDraggableTargetView::SetBuffer( COffscreen *inBuffer, RedrawOptions inRedraw )
{
	if ( mBuffer == inBuffer ) return;		// drag to ourselves
	
		// delete current buffer (if any)
	if ( mBuffer ) delete mBuffer;
	mBuffer = inBuffer;
	this->RedrawBufferAsIndicated( inRedraw );
}


// ---------------------------------------------------------------------------
// 	SetRawBuffer
// ---------------------------------------------------------------------------
// Most callers will use the SetBuffer() call instead.

void
CDraggableTargetView::SetRawBuffer( COffscreen *inBuffer )
{
	mBuffer = inBuffer;
}


// ---------------------------------------------------------------------------
// 	RedrawBufferAsIndicated
// ---------------------------------------------------------------------------
// Redraws just the buffer area of the pane either right now or by posting
// an update event. This is useful for preventing flicker -- it doesn't
// redraw the pane frame or title.

void
CDraggableTargetView::RedrawBufferAsIndicated( RedrawOptions inRedraw )
{
	StGWorldSaver		aSaver;
	StColorPenState		save2;
	save2.Normalize();
	
	if ( inRedraw == redraw_Now )
	{
		this->DrawBuffer();	
	}
	else if ( (inRedraw == redraw_Later) && mBuffer )
	{
		Rect	portR;
		this->GetCenteredBufferArea( mBuffer->GetWidth(), mBuffer->GetHeight(), nil, &portR );
		this->InvalPortRect( &portR );
	}
}


// ---------------------------------------------------------------------------
// 	CopyBufferFrom
// ---------------------------------------------------------------------------

void
CDraggableTargetView::CopyBufferFrom( COffscreen *inBuffer, RedrawOptions inRedraw )
{
	if ( !mBuffer ) return;
	mBuffer->CopyFrom( inBuffer );

	this->SetUsedFlag( true, redraw_Dont );		// we have an image -- not empty any more	
	this->RedrawBufferAsIndicated( inRedraw );
}


// ---------------------------------------------------------------------------
// 	GetBuffer
// ---------------------------------------------------------------------------

COffscreen *CDraggableTargetView::GetBuffer()
{
	return mBuffer;
}


// ---------------------------------------------------------------------------
// 	DrawSelf
// ---------------------------------------------------------------------------

void
CDraggableTargetView::DrawSelf()
{
	CTargetView::DrawSelf();
	this->DrawBuffer();
	if (mHasTarget) {
		DrawBorder();
	} else {
		EraseBorder();
	}
}


// ---------------------------------------------------------------------------
// 	DrawBuffer
// ---------------------------------------------------------------------------

void
CDraggableTargetView::DrawBuffer()
{	
	StGWorldSaver		aSaver;
	StColorPenState		aPenState;
	
	if ( !mBuffer ) return;
	
	GrafPtr		macPort = this->GetMacPort();
	Rect		localR, portR;
	
	if ( !macPort ) return;
	this->GetCenteredBufferArea( mBuffer->GetWidth(), mBuffer->GetHeight(), &localR, &portR );
	
	if ( this->IsUsed() )
		mBuffer->CopyTo( macPort, &portR );
	else
	{
		Pattern aPat;
		
		this->FocusDraw();
		aPenState.Normalize();
		::PenPat( UQDGlobals::GetLightGrayPat(&aPat) );
		::PaintRect( &localR );
	}
}


// ---------------------------------------------------------------------------
// 	HandleDroppedOffscreen
// ---------------------------------------------------------------------------

void
CDraggableTargetView::HandleDroppedOffscreen( 	COffscreen *inBuffer, 
													DragReference inDragRef, 
													DragAttributes inDragAttribs )
{
	SImageDropOnTargetView		info;
	
	info.thePicture = nil;
	info.theBuffer = inBuffer;
	info.thePane = this;
	info.theDragRef = inDragRef;
	info.theDragAttribs = inDragAttribs;
	
	this->BroadcastMessage( msg_ImageDroppedOnTargetView, &info );
}


// ---------------------------------------------------------------------------
// 	HandleDroppedPicture
// ---------------------------------------------------------------------------

void
CDraggableTargetView::HandleDroppedPicture( 	PicHandle inPicture, 
													DragReference inDragRef, 
													DragAttributes inDragAttribs )
{
	SImageDropOnTargetView		info;
	
	info.thePicture = inPicture;
	info.theBuffer = nil;
	info.thePane = this;
	info.theDragRef = inDragRef;
	info.theDragAttribs = inDragAttribs;
	
	this->BroadcastMessage( msg_ImageDroppedOnTargetView, &info );
}


// ---------------------------------------------------------------------------
// 	GetCenteredBufferArea
// ---------------------------------------------------------------------------
// Returns a rectangle centered on mBorderRect, in port coordinates (for
// CopyBits).

void
CDraggableTargetView::GetCenteredBufferArea( SInt32 inWidth, SInt32 inHeight, 
												Rect *outLocalRect, Rect *outPortRect )
{
	Rect	borderR;
	this->CalcLocalFrameRect( borderR );
	
	SInt32	paneWidth = borderR.right - borderR.left;
	SInt32	paneHeight = borderR.bottom - borderR.top;	

	Rect	localR;
	localR.left = borderR.left + (paneWidth - inWidth)/2;
	localR.right = localR.left + inWidth;
	localR.top = borderR.top + (paneHeight - inHeight)/2;
	localR.bottom = localR.top + inHeight;
		
	if ( outLocalRect )
		*outLocalRect = localR;
		
	if ( outPortRect )
	{
		*outPortRect = localR;
		LocalToPortPoint( topLeft(*outPortRect) );
		LocalToPortPoint( botRight(*outPortRect) );
	}
}


#pragma mark -

// ---------------------------------------------------------------------------
// 	IsMask
// ---------------------------------------------------------------------------

Boolean
CDraggableTargetView::IsMask()
{
	return mIsMask;
}


// ---------------------------------------------------------------------------
// 	SetMask
// ---------------------------------------------------------------------------

void
CDraggableTargetView::SetMask( Boolean inMask )
{
	mIsMask = inMask;
}


// ---------------------------------------------------------------------------
// 	IsUsed
// ---------------------------------------------------------------------------

Boolean
CDraggableTargetView::IsUsed()
{
	return( mIsUsed );
}


// ---------------------------------------------------------------------------
// 	SetUsedFlag
// ---------------------------------------------------------------------------

void
CDraggableTargetView::SetUsedFlag( Boolean inUsed, RedrawOptions inRedraw )
{
	if ( mIsUsed == inUsed ) return;
	
	mIsUsed = inUsed;
	this->RedrawBufferAsIndicated( inRedraw );
}


// ---------------------------------------------------------------------------
// 	CanBeDeleted
// ---------------------------------------------------------------------------

Boolean
CDraggableTargetView::CanBeDeleted()
{
	return( mCanBeDeleted );
}


// ---------------------------------------------------------------------------
// 	SetCanBeDeleted
// ---------------------------------------------------------------------------

void
CDraggableTargetView::SetCanBeDeletedFlag( Boolean inValue )
{
	mCanBeDeleted = inValue;
}


// ---------------------------------------------------------------------------
// 	GetInitialPaneSize
// ---------------------------------------------------------------------------

void
CDraggableTargetView::GetInitialPaneSize( SDimension16 *outSize )
{
	*outSize = mInitialPaneSize;
}


// ---------------------------------------------------------------------------
// 	GetMinPaneSize
// ---------------------------------------------------------------------------

void
CDraggableTargetView::GetMinPaneSize( SDimension16 *outSize )
{
	*outSize = mMinPaneSize;
}


// ---------------------------------------------------------------------------
// 	GetInitialPaneLocation
// ---------------------------------------------------------------------------

void
CDraggableTargetView::GetInitialPaneLocation( SPoint32 *outLoc )
{
	*outLoc = mInitialPaneLocation;
}


// ---------------------------------------------------------------------------
// 	ItemIsAcceptable
// ---------------------------------------------------------------------------

Boolean
CDraggableTargetView::ItemIsAcceptable( DragReference inDragRef, ItemReference inItemRef )
{
	if ( !mDropEnabled )
		return( false );
	
	return( CImageDragDrop::ItemIsAcceptable( inDragRef, inItemRef ) );
}


// ---------------------------------------------------------------------------
// 	GetDropEnable
// ---------------------------------------------------------------------------

Boolean
CDraggableTargetView::GetDropEnable()
{
	return( mDropEnabled );
}


// ---------------------------------------------------------------------------
// 	GetDropEnable
// ---------------------------------------------------------------------------

void
CDraggableTargetView::SetDropEnable( Boolean inEnable )
{
	mDropEnabled = inEnable;
}
