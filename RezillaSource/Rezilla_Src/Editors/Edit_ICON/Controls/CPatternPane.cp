// ===========================================================================
// CPatternPane.cp
//                       Created: 2004-12-11 18:53:08
//             Last modification: 2004-12-17 19:45:28
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CPatternPane.h"
#include "CPatternPopup.h"
#include "CRezillaApp.h"
#include "UColorUtils.h"
#include "UIconMisc.h"
#include "UPopupDrawing.h"
#include "UResources.h"


// ---------------------------------------------------------------------------
// 	CPatternPane
// ---------------------------------------------------------------------------

CPatternPane::CPatternPane( LStream *inStream ) : LPane( inStream )
{
	mForeColor = Color_Black;
	mBackColor = Color_White;
	mCurrentIndex = 0;
	mPatternListH = nil;
	
	// The refCon is formatted as follows:
	//    the low word has the PAT# resource id (-1 if no default).
	//    the high word has 0 -> application file, 1 -> system file
	SInt32		theRefCon = this->GetUserCon();
	ResIDT		theResID = LoWord( theRefCon );
	SInt16	theFileID;
	
	if ( theResID != -1 )
	{
		if ( HiWord( theRefCon ) == 0 )
			theFileID = CRezillaApp::GetOwnRefNum();
		else
			theFileID = kSystemResFile;
			
		this->SetPatternList( theFileID, theResID, redraw_Dont );
	}	
}


// ---------------------------------------------------------------------------
// 	CreateColorStream
// ---------------------------------------------------------------------------

CPatternPane *CPatternPane::CreateFromStream( LStream *inStream )
{
	return new CPatternPane( inStream );
}



// ---------------------------------------------------------------------------
// 	Destructor
// ---------------------------------------------------------------------------

CPatternPane::~CPatternPane()
{
	UIconMisc::DisposeHandle( mPatternListH );
}


// ---------------------------------------------------------------------------
// 	GetPatternIndex
// ---------------------------------------------------------------------------

SInt32
CPatternPane::GetPatternIndex()
{
	return( mCurrentIndex );
}


// ---------------------------------------------------------------------------
// 	SetPatternIndex
// ---------------------------------------------------------------------------

void
CPatternPane::SetPatternIndex( SInt32 inIndex, ERedrawOptions inRedraw )
{
	if ( inIndex != mCurrentIndex )
	{
		mCurrentIndex = inIndex;
		UIconMisc::RedrawPaneAsIndicated( this, inRedraw );
	}
	
	this->BroadcastMessage( this->GetPaneID(), (void*) inIndex );
}


// ---------------------------------------------------------------------------
// 	GetCurrentPattern
// ---------------------------------------------------------------------------

void
CPatternPane::GetCurrentPattern( Pattern *outPattern )
{
	ThrowIfNil_( mPatternListH );
	ThrowIf_( (mCurrentIndex < 0) || (mCurrentIndex >= (**mPatternListH).numPatterns) );

	*outPattern = (**mPatternListH).patterns[ mCurrentIndex ];
}


// ---------------------------------------------------------------------------
// 	SetPatternList
// ---------------------------------------------------------------------------

void
CPatternPane::SetPatternList( SInt16 inFileID, ResIDT inResID, ERedrawOptions inRedraw )
{
	Handle		theHandle = NULL;
	
	OSErr error = UResources::GetResourceInMap( inFileID, 'PAT#', inResID, theHandle, false);
	
	this->SetPatternList( (SPatternListH) theHandle, inRedraw );
}


// ---------------------------------------------------------------------------
// 	SetPatternList
// ---------------------------------------------------------------------------

void
CPatternPane::SetPatternList( SPatternListH inHandle, ERedrawOptions inRedraw )
{
	if ( inHandle )
		inHandle = (SPatternListH) UIconMisc::DuplicateHandle( (Handle) inHandle );
	
		// get rid of old pattern list (if any)
	if ( mPatternListH )
		UIconMisc::DisposeHandle( mPatternListH );
		
		// save the new list
	mPatternListH = inHandle;

		// change the current pattern to number 0 -- this will broadcast our new value
	this->SetPatternIndex( 0, redraw_Dont );
	
		// redraw if needed
	UIconMisc::RedrawPaneAsIndicated( this, inRedraw );
}


// ---------------------------------------------------------------------------
// 	SetColors
// ---------------------------------------------------------------------------

void
CPatternPane::SetColors( Color32 inFore, Color32 inBack, ERedrawOptions inRedraw )
{
	mForeColor = UColorUtils::Color32ToRGB( inFore );
	mBackColor = UColorUtils::Color32ToRGB( inBack );
	UIconMisc::RedrawPaneAsIndicated( this, inRedraw );
}


// ---------------------------------------------------------------------------
// 	DrawSelf
// ---------------------------------------------------------------------------

void
CPatternPane::DrawSelf()
{
	Rect	r, swatchR;
	
	CalcLocalFrameRect( r );
	UPopupDrawing::DrawPopup( r, false /* not hilited */, IsEnabled() );

	UPopupDrawing::CalculateSwatchArea( r, &swatchR );
	this->DrawSwatchSelf( swatchR );
}


// ---------------------------------------------------------------------------
// 	ClickSelf
// ---------------------------------------------------------------------------

void
CPatternPane::ClickSelf( const SMouseDownEvent & )
{
	if ( !mPatternListH ) return;
	
	Rect	r;
	Point	pt;

	// Find the bottom/left of the control
	this->CalcPortFrameRect( r );
	this->PortToGlobalPoint( topLeft(r) );
	this->PortToGlobalPoint( botRight(r) );
	pt.h = r.left;
	pt.v = r.bottom;
	
	// Hilite the control
	this->DrawPopup( true /* hilited */, true /* enabled */ );

	// Show the popup & track the user's actions
	SInt32 newIndex = CPatternPopup::DoPatternPopup( pt, mPatternListH, mCurrentIndex,
										mForeColor, mBackColor );

	// ColorIndex is only a Byte and newColor may be -1, so watch out
	if ( newIndex != -1 )
		this->SetPatternIndex( newIndex );

	// Unhilite the control
	this->DrawPopup( false /* not hilited */, true /* enabled */ );
}


// ---------------------------------------------------------------------------
// 	DrawPopup
// ---------------------------------------------------------------------------

void
CPatternPane::DrawPopup( Boolean inHilited, Boolean inEnabled )
{
	Rect	localR, swatchR;

	this->FocusDraw();
	this->CalcLocalFrameRect( localR );
	
	UPopupDrawing::DrawPopup( localR, inHilited, inEnabled );
	
	UPopupDrawing::CalculateSwatchArea( localR, &swatchR );
	this->DrawSwatchSelf( swatchR );
}


// ---------------------------------------------------------------------------
// 	DrawSwatch
// ---------------------------------------------------------------------------

void
CPatternPane::DrawSwatch()
{
	Rect	localR, swatchR;
	
	this->FocusDraw();
	this->CalcLocalFrameRect( localR );

	UPopupDrawing::CalculateSwatchArea( localR, &swatchR );	
	this->DrawSwatchSelf( swatchR );
}


// ---------------------------------------------------------------------------
// 	DrawSwatchSelf
// ---------------------------------------------------------------------------

void
CPatternPane::DrawSwatchSelf( const Rect &swatchR )
{
	if ( !mPatternListH || (mCurrentIndex < 0) || (mCurrentIndex >= (**mPatternListH).numPatterns) ) return;
	
	StColorPenState		oldPenState;
	oldPenState.Normalize();
	
	StHandleLocker		aLock( (Handle) mPatternListH );
	
	::PenNormal();
	::RGBForeColor( &mForeColor );
	::RGBBackColor( &mBackColor );
	::PenPat( &(**mPatternListH).patterns[ mCurrentIndex ] );
	::PaintRect( &swatchR );
}
	

