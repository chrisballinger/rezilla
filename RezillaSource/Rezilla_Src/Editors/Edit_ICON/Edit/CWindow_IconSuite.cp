// ===========================================================================
// CWindow_IconSuite.cp
//                       Created: 2005-01-10 21:23:57
//             Last modification: 2005-02-17 17:51:18
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CWindow_IconSuite.h"
#include "CDraggableTargetView.h"
#include "CIcon_EditorDoc.h"
#include "CIcon_EditorWindow.h"
#include "CSuiteSlider.h"
#include "CWindow_Pattern.h"
#include "COffscreen.h"
#include "CRezMap.h"
#include "CRezObj.h"
#include "CRezillaApp.h"
#include "RezillaConstants.h"
#include "UGraphicConversion.h"
#include "UColorUtils.h"
#include "UIconMisc.h"
#include "UMiscUtils.h"
#include "UResourceMgr.h"

#include <LStaticText.h>
#include <LPushButton.h>

// ---------------------------------------------------------------------------
// 	OpenPaintWindow
// ---------------------------------------------------------------------------
CWindow_IconSuite*
CWindow_IconSuite::OpenPaintWindow( CRezObj * inRezObj, ResIDT inPPobID )
{
	CWindow_IconSuite *	theWindow = nil;

	try
	{
		theWindow = (CWindow_IconSuite*) CIcon_EditorWindow::CreatePaintWindow( inPPobID );
		theWindow->InitializeFromResource(inRezObj);
	}
	catch( ... )
	{
		if (theWindow) { delete theWindow; } 
		throw;
	}
	
	return( theWindow );
}


// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------
CWindow_IconSuite::CWindow_IconSuite( LStream *inStream ) 
		: CSuite_Window( inStream )
{
}


// ---------------------------------------------------------------------------
// 	Destructor
// ---------------------------------------------------------------------------
CWindow_IconSuite::~CWindow_IconSuite()
{
}


// ---------------------------------------------------------------------------
// 	CreateFromStream
// ---------------------------------------------------------------------------
CWindow_IconSuite *
CWindow_IconSuite::CreateFromStream( LStream *inStream )
{
	return new CWindow_IconSuite( inStream );
}


// ---------------------------------------------------------------------------
// 	FinishCreateSelf
// ---------------------------------------------------------------------------

void
CWindow_IconSuite::FinishCreateSelf()
{
	CSuite_Window::FinishCreateSelf();

	mSample = (CDraggableTargetView *) this->FindPaneByID( ImgType_IconSuite );
	ThrowIfNil_( mSample );
	mSamplePaneList[ mNumSamplePanes++ ] = mSample;
	
	// Link the broadcasters
	UReanimator::LinkListenerToBroadcasters( this, this, PPob_IconSuiteEditor );
	// We need to listen to the sample pane (click and/or drop operations)
	this->BecomeListenerTo( mNumSamplePanes, mSamplePaneList );
}


// ---------------------------------------------------------------------------
// 	SaveAsResource
// ---------------------------------------------------------------------------

void
CWindow_IconSuite::SaveAsResource( CRezMap *inMap, ResIDT inResID )
{
#pragma unused(inMap, inResID)

	// Store the current pattern's data.
	ImageToNthBitmap(mCurrentIndex);
	
	Size totalSize = mTotalCount * sizeof(SICN);
	Handle	srcHandle = mBitmapsArray.GetItemsHandle();
	
	// This is a simple array. The count of items is not stored.
	Handle	outHandle = ::NewHandle(totalSize);
	ThrowIfMemFail_( outHandle );
		
	try
	{
		StHandleLocker	srcLocker(srcHandle);
		StHandleLocker	outLocker(outHandle);
		
		::BlockMoveData( *srcHandle, (*outHandle), totalSize );
		
		CRezObj *	theRes = mOwnerDoc->GetRezObj();
		ThrowIfNil_( theRes );
		theRes->SetData( outHandle );

	}
	catch( ... )
	{
		::DisposeHandle(outHandle);
		throw;
	}

	::DisposeHandle(outHandle);
	this->SetDirty( false );
}


// ---------------------------------------------------------------------------
// 	GetZoomFactor
// ---------------------------------------------------------------------------

SInt32
CWindow_IconSuite::GetZoomFactor( SInt32, SInt32, Boolean *outShowGrid )
{
	return CIcon_EditorWindow::GetZoomFactor( kDefaultPatternWidth, kDefaultPatternHeight, outShowGrid );
}


// ---------------------------------------------------------------------------
// 	ParseBitmapSuite
// ---------------------------------------------------------------------------

void
CWindow_IconSuite::ParseBitmapSuite( Handle inHandle, COffscreen **outBW  )
{
	Size		theSize = GetHandleSize(inHandle);
	SInt32		offset;	
	SICN *		p;
	
	if (theSize > 0) {
		if (theSize % 32) {
			Throw_( err_IconCorruptedResource );
		} 
		
		StHandleLocker	locker( (Handle) inHandle );
		
		mTotalCount = theSize / 32;
		
		p = (SICN *) *inHandle;
		
		for ( offset = 0; offset < mTotalCount; offset++ ) {
			mBitmapsArray.AddItem( *(p + offset) );
		}
		
		*outBW = IconToOffscreen(p);
	} else {
		mTotalCount = 0;
		AddNewBitmap();
	}
	
	mCurrentIndex = 1;
}


// ---------------------------------------------------------------------------
// 	IconToOffscreen
// ---------------------------------------------------------------------------

COffscreen *
CWindow_IconSuite::IconToOffscreen( const SICN * inIcon )
{
	StGWorldSaver	save1;
	CTabHandle		theTable = nil;
	COffscreen		*theBuffer = nil;
	
	try
	{
		theTable = UColorUtils::GetColorTable( 1 );
		
		theBuffer = COffscreen::CreateBuffer( kDefaultIconWidth, kDefaultIconWidth, 1, theTable );
		//theBuffer->AssignPalette( theTable );		
		
		theBuffer->CopyFromRawData( (UInt8*) inIcon, kBWIconRowBytes );
	}
	catch( ... )
	{
		if ( theBuffer ) delete( theBuffer );
		if ( theTable ) ::DisposeCTable( theTable );
		throw;
	}
	
	if ( theTable ) ::DisposeCTable( theTable );
	return( theBuffer );
}


// ---------------------------------------------------------------------------
// 	SetNthBitmap
// ---------------------------------------------------------------------------

void
CWindow_IconSuite::SetNthBitmap( SInt32 inBitmapIndex )
{
	SICN icon;

	if ( mBitmapsArray.FetchItemAt(inBitmapIndex, icon) ) {
		COffscreen * bwImage = IconToOffscreen(&icon);
		this->SetImage( bwImage, resize_All, redraw_Later );
		mCurrentSamplePane = mSample;	
		mSample->SetTarget( true, redraw_Dont );
	
		mSample->SetBuffer( bwImage, redraw_Now );
		// It belongs to the sample pane now
		bwImage = nil;	

		mCurrentIndex = inBitmapIndex;
	}
}


// ---------------------------------------------------------------------------
// 	AddNewBitmap
// ---------------------------------------------------------------------------

ArrayIndexT
CWindow_IconSuite::AddNewBitmap()
{
	SICN	icon = { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
					0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 };
					
	ArrayIndexT index;
	
	index = mBitmapsArray.AddItem(icon);
	mTotalCount++;
	mSlider->SetMaxValue(mTotalCount);
	return index;
}


// ---------------------------------------------------------------------------
// 	AddNewBitmap
// ---------------------------------------------------------------------------

ArrayIndexT
CWindow_IconSuite::AddNewBitmap( SInt32 inAtIndex )
{
	SICN	icon = { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
					0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 };
	ArrayIndexT index;
	
	index = mBitmapsArray.InsertItemsAt(1, inAtIndex, icon);
	mTotalCount++;
	mSlider->SetMaxValue(mTotalCount);
	return index;
}


// ---------------------------------------------------------------------------
// 	RemoveBitmap
// ---------------------------------------------------------------------------

void
CWindow_IconSuite::RemoveBitmap( SInt32 inBitmapIndex )
{
	SICN	icon;
	
	if ( mBitmapsArray.FetchItemAt(inBitmapIndex, icon) ) {
		mBitmapsArray.RemoveItemsAt(1, inBitmapIndex);
		mTotalCount--;
		mSlider->SetMaxValue(mTotalCount);
	}
	
	if (mCurrentIndex > mTotalCount) {
		mCurrentIndex = mTotalCount;
	} 
}

// ---------------------------------------------------------------------------
// 	ImageToNthBitmap
// ---------------------------------------------------------------------------

void
CWindow_IconSuite::ImageToNthBitmap( SInt32 inBitmapIndex )
{
	if (mCurrentIndex <= 0 || mCurrentIndex > mTotalCount) {
		return;
	} 
	
	SICN	icon;
	COffscreen	*bwBuffer = mSample->GetBuffer();
	ThrowIfNil_( bwBuffer );

	bwBuffer->CopyToRawData( (UInt8*) &icon, kBWIconRowBytes );

	mBitmapsArray.AssignItemsAt(1, inBitmapIndex, icon);	
}



