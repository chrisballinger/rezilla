// ===========================================================================
// CSuite_Window.cp
//                       Created: 2005-01-10 21:23:57
//             Last modification: 2006-10-06 07:28:46
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004-2006
// All rights reserved.
// ===========================================================================

#include "CSuite_Window.h"
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
#include "CIconSelection.h"
#include "RezillaConstants.h"
#include "UGraphicConversion.h"
#include "UIconMisc.h"
#include "UMiscUtils.h"
#include "UResourceMgr.h"
#include "UMessageDialogs.h"

#include <LStaticText.h>
#include <LPushButton.h>

// ---------------------------------------------------------------------------
// 	OpenPaintWindow
// ---------------------------------------------------------------------------
CSuite_Window*
CSuite_Window::OpenPaintWindow( CRezObj * inRezObj, ResIDT inPPobID )
{
	CSuite_Window *	theWindow = nil;

	try
	{
		theWindow = (CSuite_Window*) CIcon_EditorWindow::CreatePaintWindow( inPPobID );
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
CSuite_Window::CSuite_Window( LStream *inStream ) 
		: CIcon_EditorWindow( inStream )
{
}


// ---------------------------------------------------------------------------
// 	Destructor
// ---------------------------------------------------------------------------
CSuite_Window::~CSuite_Window()
{
}


// ---------------------------------------------------------------------------
// 	CreateFromStream
// ---------------------------------------------------------------------------
CSuite_Window *
CSuite_Window::CreateFromStream( LStream *inStream )
{
	return new CSuite_Window( inStream );
}


// ---------------------------------------------------------------------------
// 	InitializeFromResource
// ---------------------------------------------------------------------------
void
CSuite_Window::InitializeFromResource(CRezObj * inRezObj)
{
	StGWorldSaver		worldSaver;
	StRezRefSaver		refSaver;

	COffscreen			*bwImage = nil;
	Handle				h = nil;
	ResType				resType = inRezObj->GetType();
	
	try
	{	
		ThrowIfNil_( inRezObj );

		// Get an empty default icon if the size is 0
		if (inRezObj->GetSize() == 0) {
			UIconMisc::GetDefaultBitmap(inRezObj, resType);	
		} 
		
		// Get the raw resource handle
		h = inRezObj->GetData();
		ThrowIfNil_( h );
		
		// Parse the resource to build the patterns array
// 		ParseBitmapSuite( h, &bwImage );
		ParseBitmapSuite( h );
		
		SetNthBitmap(1);

		mSlider->SetValue(mCurrentIndex);
		mSlider->SetMinValue(1);
		mSlider->SetMaxValue(mTotalCount);
		AdjustSlider();

	}
	catch( ... )
	{
		if ( bwImage ) delete( bwImage );
		( h );
		throw;
	}
	
	( h );
}


// ---------------------------------------------------------------------------
// 	SaveAsResource
// ---------------------------------------------------------------------------
void
CSuite_Window::SaveAsResource( CRezMap *inMap, ResIDT inResID )
{
#pragma unused(inMap, inResID)
}


// ---------------------------------------------------------------------------
// 	FinishCreateSelf
// ---------------------------------------------------------------------------

void
CSuite_Window::FinishCreateSelf()
{
	// Call the inherited method
	CIcon_EditorWindow::FinishCreateSelf();
	
	mTotalCount = 0;

	mSlider = dynamic_cast<CSuiteSlider *>(this->FindPaneByID( item_IconSuiteSlider ));
	ThrowIfNil_( mSlider );

	mSlider->SetOwnerWindow(this);
	
	mCountField = (LStaticText *) this->FindPaneByID( item_IconCountField );
	ThrowIfNil_( mCountField );

	mPlusButton = (LPushButton *) this->FindPaneByID( item_PlusButton );
	ThrowIfNil_( mPlusButton );

	mMinusButton = (LPushButton *) this->FindPaneByID( item_MinusButton );
	ThrowIfNil_( mMinusButton );

	mSlider->AddListener(this);
	mPlusButton->AddListener(this);
	mMinusButton->AddListener(this);

}


// ---------------------------------------------------------------------------
//  ListenToMessage												[public]
// ---------------------------------------------------------------------------

void
CSuite_Window::ListenToMessage( MessageT inMessage, void *ioParam ) 
{
	switch( inMessage )
	{
		case msg_IconSuiteSlider: {
			SInt32 val = mSlider->GetValue();
			SetCountField(val, mTotalCount);
			break;
		}
		
		case msg_PlusButton: {
			ImageToNthBitmap(mCurrentIndex);
			ArrayIndexT index = AddNewBitmap();
			SetNthBitmap(index);
			AdjustSlider();
			SetDirty(true);
			break;
		}
		
		case msg_MinusButton:
		RemoveBitmap(mCurrentIndex);
		SetNthBitmap(mCurrentIndex);
		AdjustSlider();
		SetDirty(true);
		break;
		
		default:
		CIcon_EditorWindow::ListenToMessage(inMessage, ioParam);
		break;
	}
}


// ---------------------------------------------------------------------------
//   HandleKeyPress												  [public]
// ---------------------------------------------------------------------------
// The PageUp/RightArrow and PageDown/LeftArrow keys move the slider by 1
// unit. But recall that the simple arrow keys are used by the paint view
// to nudge the selection in the canvas, so RightArrow and LeftArrow move
// the slider only when there is no selection. The Home key moves the
// slider to the min value, the End key to the max value. Pressing the "+"
// or the "-" key together with the Command key simulate the Plus and Minus
// buttons respectively.

Boolean
CSuite_Window::HandleKeyPress(
	const EventRecord&	inKeyEvent)
{
	Boolean		keyHandled	= false;
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
		Boolean acceptArrows = ( mCurrentImage != nil && mCurrentSelection != nil 
								&& mCurrentSelection->IsEmpty() );		 
		SInt32 theValue, oldValue;
		oldValue = mSlider->GetValue();
		theValue = oldValue;
		
		if (theChar == char_PageDown || (acceptArrows && theChar == char_LeftArrow)) {
			if (theValue > 1) {
				--theValue;
			} 
		} else if (theChar == char_PageUp || (acceptArrows && theChar == char_RightArrow)) {
			if (theValue < mTotalCount) {
				++theValue;
			} 
		} else if ( theChar == char_Home ) {
			theValue = 1;
		} else if ( theChar == char_End ) {
			theValue = mTotalCount;
		} else {
			keyHandled = false;
		}

		if (theValue != oldValue) {
			mSlider->SetValue(theValue);
			SetNthBitmap(theValue);	
		} 
	}
	
	if (keyButton != nil) {
		keyButton->SimulateHotSpotClick(kControlButtonPart);
		keyHandled = true;
	} 
	
	if (!keyHandled) {
		keyHandled = CIcon_EditorWindow::HandleKeyPress(inKeyEvent);
	}
	
	return keyHandled;
}


// ---------------------------------------------------------------------------
// 	ParseBitmapSuite
// ---------------------------------------------------------------------------

void
CSuite_Window::ParseBitmapSuite( Handle /* inHandle */ )
{
	// Subclasses must override
}


// ---------------------------------------------------------------------------
// 	SetCountField
// ---------------------------------------------------------------------------

void
CSuite_Window::SetCountField( SInt32 inCurrIndex, SInt32 inTotalCount )
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
CSuite_Window::AdjustSlider()
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
// 	SwitchToNthBitmap
// ---------------------------------------------------------------------------

void
CSuite_Window::SwitchToNthBitmap( SInt32 inBitmapIndex )
{
	if (mCurrentIndex == inBitmapIndex) {
		return;
	} 

	// Store the state of the current pattern
	ImageToNthBitmap(mCurrentIndex);
	
	// Set the new pattern
	SetNthBitmap(inBitmapIndex);
}


// ---------------------------------------------------------------------------
// 	SetNthBitmap
// ---------------------------------------------------------------------------

void
CSuite_Window::SetNthBitmap( SInt32 /* inBitmapIndex */ )
{
// Subclasses must override
}


// ---------------------------------------------------------------------------
// 	AddNewBitmap
// ---------------------------------------------------------------------------

ArrayIndexT
CSuite_Window::AddNewBitmap()
{
	ArrayIndexT index = 0;

// Subclasses must override
	
	return index;
}


// ---------------------------------------------------------------------------
// 	AddNewBitmap
// ---------------------------------------------------------------------------

ArrayIndexT
CSuite_Window::AddNewBitmap( SInt32 /* inAtIndex */ )
{
	ArrayIndexT index = 0;
	
// Subclasses must override

	return index;
}


// ---------------------------------------------------------------------------
// 	RemoveBitmap
// ---------------------------------------------------------------------------

void
CSuite_Window::RemoveBitmap( SInt32 /* inBitmapIndex */ )
{
// Subclasses must override
}


// ---------------------------------------------------------------------------
// 	ImageToNthBitmap
// ---------------------------------------------------------------------------

void
CSuite_Window::ImageToNthBitmap( SInt32 /* inBitmapIndex */ )
{
// Subclasses must override
}



