// ===========================================================================
// CWindow_PatternSuite.cp
//                       Created: 2005-01-09 10:38:27
//             Last modification: 2005-01-11 08:46:03
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CWindow_PatternSuite.h"
#include "CDraggableTargetView.h"
#include "CIcon_EditorDoc.h"
#include "CIcon_EditorWindow.h"
#include "CSuiteSlider.h"
#include "CWindow_Pattern.h"
#include "CPatternTargetView.h"
#include "COffscreen.h"
#include "CRezMap.h"
#include "CRezObj.h"
#include "CRezillaApp.h"
#include "RezillaConstants.h"
#include "UGraphicConversion.h"
#include "UIconMisc.h"
#include "UMiscUtils.h"
#include "UResourceMgr.h"

#include <LStaticText.h>
#include <LPushButton.h>

// ---------------------------------------------------------------------------
// 	OpenPaintWindow
// ---------------------------------------------------------------------------
CWindow_PatternSuite*
CWindow_PatternSuite::OpenPaintWindow( ResIDT inPPobID, CRezMap *inMap, ResType inResType, ResIDT inResID )
{
	CWindow_PatternSuite *	theWindow = nil;

	try
	{
		theWindow = (CWindow_PatternSuite*) CIcon_EditorWindow::CreatePaintWindow( inPPobID );
		theWindow->InitializeFromResource( inMap, inResType, inResID );
	}
	catch( ... )
	{
		delete theWindow;
		throw;
	}
	
	return( theWindow );
}


// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------
CWindow_PatternSuite::CWindow_PatternSuite( LStream *inStream ) 
		: CSuite_Window( inStream )
{
}


// ---------------------------------------------------------------------------
// 	Destructor
// ---------------------------------------------------------------------------
CWindow_PatternSuite::~CWindow_PatternSuite()
{
}


// ---------------------------------------------------------------------------
// 	CreateFromStream
// ---------------------------------------------------------------------------
CWindow_PatternSuite *
CWindow_PatternSuite::CreateFromStream( LStream *inStream )
{
	return new CWindow_PatternSuite( inStream );
}


// ---------------------------------------------------------------------------
// 	SaveAsResource
// ---------------------------------------------------------------------------

void
CWindow_PatternSuite::SaveAsResource( CRezMap *inMap, ResIDT inResID )
{
	// Store the current pattern's data.
	BitmapToNthPattern(mCurrentIndex);
	
	Size totalSize = mTotalCount * sizeof(Pattern);
	Handle	srcHandle = mPatternsArray.GetItemsHandle();
	// First two bytes to store the patterns count
	Handle	outHandle = ::NewHandle(totalSize + 2);
	ThrowIfMemFail_( outHandle );
	
	try
	{
		StHandleLocker	srcLocker(srcHandle);
		StHandleLocker	outLocker(outHandle);
		
		**(UInt16 **) outHandle = mTotalCount;
		::BlockMoveData( *srcHandle, (*outHandle) + 2, totalSize );
		
		CRezObj * theResource = inMap->FindResource( ImgType_PatternSuite, inResID, false );
		ThrowIfNil_( theResource );
		theResource->SetData( outHandle );
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
CWindow_PatternSuite::GetZoomFactor( SInt32, SInt32, Boolean *outShowGrid )
{
	return CIcon_EditorWindow::GetZoomFactor( kDefaultPatternWidth, kDefaultPatternHeight, outShowGrid );
}


// ---------------------------------------------------------------------------
// 	ParseBitmapSuite
// ---------------------------------------------------------------------------

void
CWindow_PatternSuite::ParseBitmapSuite( Handle inHandle, COffscreen **outBW  )
{
	Size		theSize = GetHandleSize(inHandle);
	SInt32		offset;	
	Pattern *	p;
	
	StHandleLocker	locker( (Handle) inHandle );

	mTotalCount = **(UInt16 **) inHandle;
	if (mTotalCount * 8 + 2 != theSize) {
		Throw_( err_IconCorruptedResource );
	} 
	mCurrentIndex = 1;
	
	p = (Pattern *) (*inHandle + 2);
	
	for ( offset = 0; offset < mTotalCount; offset++ ) {
		mPatternsArray.AddItem( *(p + offset) );
	}
	
	*outBW = CWindow_Pattern::BWPatternToOffscreen(*p);
}


// ---------------------------------------------------------------------------
// 	SetNthBitmap
// ---------------------------------------------------------------------------

void
CWindow_PatternSuite::SetNthBitmap( SInt32 inPatternIndex )
{
	Pattern pat;

	if ( mPatternsArray.FetchItemAt(inPatternIndex, pat) ) {
		COffscreen * bwImage = CWindow_Pattern::BWPatternToOffscreen(pat);
		this->SetImage( bwImage, resize_None, redraw_Later );
		mCurrentSamplePane = mSample;	
		mSample->SetTarget( true, redraw_Dont );
	
		mSample->SetBuffer( bwImage, redraw_Now );
		// It belongs to the sample pane now
		bwImage = nil;	

		mCurrentIndex = inPatternIndex;
	}
}


// ---------------------------------------------------------------------------
// 	AddNewBitmap
// ---------------------------------------------------------------------------

ArrayIndexT
CWindow_PatternSuite::AddNewBitmap()
{
	Pattern	pat = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	ArrayIndexT index;
	
	index = mPatternsArray.AddItem(pat);
	mTotalCount++;
	mSlider->SetMaxValue(mTotalCount);
	return index;
}


// ---------------------------------------------------------------------------
// 	AddNewBitmap
// ---------------------------------------------------------------------------

ArrayIndexT
CWindow_PatternSuite::AddNewBitmap( SInt32 inAtIndex )
{
	Pattern	pat = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	ArrayIndexT index;
	
	index = mPatternsArray.InsertItemsAt(1, inAtIndex, pat);
	mTotalCount++;
	mSlider->SetMaxValue(mTotalCount);
	return index;
}


// ---------------------------------------------------------------------------
// 	RemoveBitmap
// ---------------------------------------------------------------------------

void
CWindow_PatternSuite::RemoveBitmap( SInt32 inPatternIndex )
{
	Pattern	pat;
	
	if ( mPatternsArray.FetchItemAt(inPatternIndex, pat) ) {
		mPatternsArray.RemoveItemsAt(1, inPatternIndex);
		mTotalCount--;
		mSlider->SetMaxValue(mTotalCount);
	}
	
	if (mCurrentIndex > mTotalCount) {
		mCurrentIndex = mTotalCount;
	} 
}

// ---------------------------------------------------------------------------
// 	BitmapToNthPattern
// ---------------------------------------------------------------------------

void
CWindow_PatternSuite::BitmapToNthPattern( SInt32 inPatternIndex )
{
	if (mCurrentIndex <= 0 || mCurrentIndex > mTotalCount) {
		return;
	} 
	
	Pattern	pat;
	COffscreen	*bwBuffer = mSample->GetBuffer();
	ThrowIfNil_( bwBuffer );

	bwBuffer->CopyToRawData( (UInt8*) &pat, kBWPatternRowBytes );

	mPatternsArray.AssignItemsAt(1, inPatternIndex, pat);	
}



