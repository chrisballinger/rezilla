// ===========================================================================
// CWindow_PatternSuite.cp
//                       Created: 2005-01-09 10:38:27
//             Last modification: 2005-01-10 08:18:44
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
CWindow_PatternSuite::OpenPaintWindow( ResIDT inPPobID, CRezMap *inMap, ResIDT inResID )
{
	CWindow_PatternSuite *	theWindow = nil;

	try
	{
		theWindow = (CWindow_PatternSuite*) CIcon_EditorWindow::CreatePaintWindow( inPPobID );
		theWindow->InitializeFromResource( inMap, inResID );
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
		: CIcon_EditorWindow( inStream )
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
// 	FinishCreateSelf
// ---------------------------------------------------------------------------

void
CWindow_PatternSuite::FinishCreateSelf()
{
	CIcon_EditorWindow::FinishCreateSelf();

	mSlider = dynamic_cast<CSuiteSlider *>(this->FindPaneByID( item_IconSuiteSlider ));
	ThrowIfNil_( mSlider );

	mSlider->SetOwnerWindow(this);
	
	mBWSample = (CPatternTargetView *) this->FindPaneByID( item_IconEditBWSample );
	ThrowIfNil_( mBWSample );
	mSamplePaneList[ mNumSamplePanes++ ] = mBWSample;
	
	mCountField = (LStaticText *) this->FindPaneByID( item_IconCountField );
	ThrowIfNil_( mCountField );

	mPlusButton = (LPushButton *) this->FindPaneByID( item_PlusButton );
	ThrowIfNil_( mPlusButton );

	mMinusButton = (LPushButton *) this->FindPaneByID( item_MinusButton );
	ThrowIfNil_( mMinusButton );

	mSlider->AddListener(this);
	mPlusButton->AddListener(this);
	mMinusButton->AddListener(this);
	
	// We need to listen to the sample pane (click and/or drop operations)
	this->BecomeListenerTo( mNumSamplePanes, mSamplePaneList );
}


// ---------------------------------------------------------------------------
//  ListenToMessage												[public]
// ---------------------------------------------------------------------------

void
CWindow_PatternSuite::ListenToMessage( MessageT inMessage, void *ioParam ) 
{
	switch( inMessage )
	{
		case msg_IconSuiteSlider:
		SInt32 val = mSlider->GetValue();
		SetCountField(val, mTotalCount);
		break;
		
		case msg_PlusButton:
		ArrayIndexT index = AddNewPattern();
		SetNthPattern(index);
		AdjustSlider();
		break;
		
		case msg_MinusButton:
		RemovePattern(mCurrentIndex);
		SetNthPattern(mCurrentIndex);
		AdjustSlider();
		break;
		
		default:
		CIcon_EditorWindow::ListenToMessage(inMessage, ioParam);
		break;
	}
}


// ---------------------------------------------------------------------------
// 	InitializeFromResource
// ---------------------------------------------------------------------------

void
CWindow_PatternSuite::InitializeFromResource( CRezMap *inMap, ResIDT inResID )
{
	StGWorldSaver		worldSaver;
	StRezRefSaver		refSaver;

	COffscreen			*bwImage = nil;
	Handle				h = nil;
	
	try
	{	
		// Get the raw resource handle
		CRezObj * theRes = inMap->FindResource( ImgType_PatternSuite, inResID, true );
		ThrowIfNil_( theRes );
		h = theRes->GetData();
		ThrowIfNil_( h );
		
		// Draw the pattern(s) into bitmaps
		this->ParseBWPatternSuite( h, &bwImage );
		
		this->SetImage( bwImage, resize_None, redraw_Later );
		mBWSample->SetTarget( true, redraw_Dont );
	
		mBWSample->SetBuffer( bwImage, redraw_Dont );
		bwImage = nil;			// because it belongs to the sample pane now

		mSlider->SetValue(mCurrentIndex);
		mSlider->SetMaxValue(mTotalCount);
		AdjustSlider();
		
	}
	catch( ... )
	{
		delete( bwImage );
		( h );
		throw;
	}
	
	( h );
}


// ---------------------------------------------------------------------------
// 	SaveAsResource
// ---------------------------------------------------------------------------

void
CWindow_PatternSuite::SaveAsResource( CRezMap *inMap, ResIDT inResID )
{
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
// 	ParseBWPatternSuite
// ---------------------------------------------------------------------------

void
CWindow_PatternSuite::ParseBWPatternSuite( Handle inHandle, COffscreen **outBW  )
{
	Size	theSize = GetHandleSize(inHandle);
	SInt32	offset;
	
	Pattern * p;
	
	StHandleLocker	locker( (Handle) inHandle );

	mTotalCount = theSize / 8;
	mCurrentIndex = 1;
	
	p = (Pattern *) *inHandle;
	
	for ( offset = 0; offset < mTotalCount; offset++ )
	{
		mPatternsArray.AddItem( *(p + offset) );
	}
	
	*outBW = CWindow_Pattern::BWPatternToOffscreen(*p);
}


// ---------------------------------------------------------------------------
// 	SetCountField
// ---------------------------------------------------------------------------

void
CWindow_PatternSuite::SetCountField( SInt32 inCurrIndex, SInt32 inTotalCount )
{
	Str255	theString;
	LStr255	theLine("\p");
	
	::NumToString( inCurrIndex, theString);
	theLine.Append(theString);
	theLine += "\p/";
	::NumToString( inTotalCount, theString);
	theLine.Append(theString);
	mCountField->SetDescriptor(theLine);
}


// ---------------------------------------------------------------------------
// 	AdjustSlider
// ---------------------------------------------------------------------------

void
CWindow_PatternSuite::AdjustSlider()
{
	if (mTotalCount <= 1) {
		mSlider->Hide();
	} else {
		mSlider->Show();
	}
	mSlider->SetValue(mCurrentIndex);
	SetCountField(mCurrentIndex, mTotalCount);
}


// ---------------------------------------------------------------------------
// 	SetNthPattern
// ---------------------------------------------------------------------------

void
CWindow_PatternSuite::SetNthPattern( SInt32 inPatternIndex )
{
	if (mCurrentIndex == inPatternIndex) {
		return;
	} 
	Pattern pat;

	// Store the state of the current pattern
	BitmapToNthPattern(mCurrentIndex);
	
	// Switch to the new pattern
	if ( mPatternsArray.FetchItemAt(inPatternIndex, pat) ) {
		COffscreen * bwImage = CWindow_Pattern::BWPatternToOffscreen(pat);
		this->SetImage( bwImage, resize_None, redraw_Later );
		mBWSample->SetTarget( true, redraw_Dont );
	
		mBWSample->SetBuffer( bwImage, redraw_Dont );
		// It belongs to the sample pane now
		bwImage = nil;	

		mCurrentIndex = inPatternIndex;
	}
}


// ---------------------------------------------------------------------------
// 	AddNewPattern
// ---------------------------------------------------------------------------

ArrayIndexT
CWindow_PatternSuite::AddNewPattern()
{
	Pattern	pat = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	ArrayIndexT index;
	
	index = mPatternsArray.AddItem(pat);
	mTotalCount++;
	return index;
}


// ---------------------------------------------------------------------------
// 	AddNewPattern
// ---------------------------------------------------------------------------

ArrayIndexT
CWindow_PatternSuite::AddNewPattern( SInt32 inAtIndex )
{
	Pattern	pat = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	ArrayIndexT index;
	
	index = mPatternsArray.InsertItemsAt(1, inAtIndex, pat);
	mTotalCount++;
	return index;
}


// ---------------------------------------------------------------------------
// 	RemovePattern
// ---------------------------------------------------------------------------

void
CWindow_PatternSuite::RemovePattern( SInt32 inPatternIndex )
{
	Pattern	pat;
	
	if ( mPatternsArray.FetchItemAt(inPatternIndex, pat) ) {
		mPatternsArray.RemoveItemsAt(1, inPatternIndex);
		mTotalCount--;
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
	COffscreen	*bwBuffer = mBWSample->GetBuffer();
	ThrowIfNil_( bwBuffer );

	bwBuffer->CopyToRawData( (UInt8*) &pat, kBWPatternRowBytes );

	mPatternsArray.AssignItemsAt(1, inPatternIndex, pat);	
}



