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
	
	mSample = (CPatternTargetView *) this->FindPaneByID( item_IconEditBWSample );
	ThrowIfNil_( mSample );
	mSamplePaneList[ mNumSamplePanes++ ] = mSample;
	
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
//	¥ HandleKeyPress												  [public]
// ---------------------------------------------------------------------------
// The PageUp and PageDown arrows move the slider by 1 unit (recall that
// the simple arrow keys are used by the Text tool to nudge the selection
// in the canvas). The Home key moves the slider to the min value, the End
// key to the max value. Pressing the + or - key together with the Command
// key simulate the plus and minus buttons.

Boolean
CWindow_PatternSuite::HandleKeyPress(
	const EventRecord&	inKeyEvent)
{
	Boolean		keyHandled	= true;
	LControl*	keyButton	= nil;
	UInt8		theChar		= (UInt8) (inKeyEvent.message & charCodeMask);
	
	if (inKeyEvent.modifiers & cmdKey) {
		if ( theChar == 0x2B) {
			// The + char
			keyButton = dynamic_cast<LControl*>(mPlusButton);		
		} else if ( theChar == 0x2D ) {
			// The - char
			keyButton = dynamic_cast<LControl*>(mMinusButton);		
		} 
	} else {
		SInt32 theValue;
		theValue = mSlider->GetValue();
		
		if (theChar == char_PageDown) {
			if (theValue > 1) {
				--theValue;
			} 
		} else if (theChar == char_PageUp) {
			if (theValue < mTotalCount) {
				++theValue;
			} 
		} else if ( theChar == char_Home ) {
			theValue = 1;
		} else if ( theChar == char_End ) {
			theValue = mTotalCount;
		}
		
		mSlider->SetValue(theValue);
		SetNthPattern(theValue);
	}
	
	if (keyButton != nil) {
		keyButton->SimulateHotSpotClick(kControlButtonPart);
	} else {
		keyHandled = CIcon_EditorWindow::HandleKeyPress(inKeyEvent);
	}
	
	return keyHandled;
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
		
		// Parse the resource to build the patterns array
		this->ParseBWPatternSuite( h, &bwImage );
		
		SetNthPattern(1);

		mSlider->SetValue(mCurrentIndex);
		mSlider->SetMinValue(1);
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
// 	ParseBWPatternSuite
// ---------------------------------------------------------------------------

void
CWindow_PatternSuite::ParseBWPatternSuite( Handle inHandle, COffscreen **outBW  )
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
// 	SwitchToNthPattern
// ---------------------------------------------------------------------------

void
CWindow_PatternSuite::SwitchToNthPattern( SInt32 inPatternIndex )
{
	if (mCurrentIndex == inPatternIndex) {
		return;
	} 

	// Store the state of the current pattern
	BitmapToNthPattern(mCurrentIndex);
	
	// Set the new pattern
	SetNthPattern(inPatternIndex);
}


// ---------------------------------------------------------------------------
// 	SetNthPattern
// ---------------------------------------------------------------------------

void
CWindow_PatternSuite::SetNthPattern( SInt32 inPatternIndex )
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
// 	AddNewPattern
// ---------------------------------------------------------------------------

ArrayIndexT
CWindow_PatternSuite::AddNewPattern()
{
	Pattern	pat = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	ArrayIndexT index;
	
	index = mPatternsArray.AddItem(pat);
	mTotalCount++;
	mSlider->SetMaxValue(mTotalCount);
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
	mSlider->SetMaxValue(mTotalCount);
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



