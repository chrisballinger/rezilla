// ===========================================================================
// CWindow_Picture.cp
//                       Created: 2004-12-11 18:50:22
//             Last modification: 2005-02-17 18:09:23
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004-2005
// All rights reserved.
// ===========================================================================


#include "CWindow_Picture.h"
#include "CIcon_EditorWindow.h"
#include "UGraphicConversion.h"
#include "COffscreen.h"
#include "CRezObj.h"
#include "CRezMap.h"
#include "RezillaConstants.h"
#include "UIconMisc.h"
#include "UMiscUtils.h"
#include "UResourceMgr.h"


// ---------------------------------------------------------------------------
// 	OpenPaintWindow
// ---------------------------------------------------------------------------
CWindow_Picture*
CWindow_Picture::OpenPaintWindow(CRezObj * inRezObj, ResIDT inPPobID )
{
	CWindow_Picture *	theWindow = nil;
	
	try
	{
		theWindow = (CWindow_Picture*) CIcon_EditorWindow::CreatePaintWindow( inPPobID );
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
// 	CreateFromStream
// ---------------------------------------------------------------------------
CWindow_Picture *CWindow_Picture::CreateFromStream( LStream *inStream )
{
	return new CWindow_Picture( inStream );
}


// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------
CWindow_Picture::CWindow_Picture( LStream *inStream ) : CIcon_EditorWindow( inStream )
{
	mAllowImageResizing = true;
	mMaxImageWidth = 1024;				// too big ???
	mMaxImageHeight = 1024;
	mPrefersIconColors = false;
}


// ---------------------------------------------------------------------------
// 	Destructor
// ---------------------------------------------------------------------------
CWindow_Picture::~CWindow_Picture()
{
}


// ---------------------------------------------------------------------------
// 	FinishCreateSelf
// ---------------------------------------------------------------------------
void
CWindow_Picture::FinishCreateSelf()
{
	// Call the inherited method
	CIcon_EditorWindow::FinishCreateSelf();

	// Link the broadcasters
	UReanimator::LinkListenerToBroadcasters( this, this, PPob_PictEditor );
}


// ---------------------------------------------------------------------------
// 	InitializeFromResource
// ---------------------------------------------------------------------------

void
CWindow_Picture::InitializeFromResource(CRezObj * /* inRezObj */)
{
// 	StGWorldSaver		aSaver;
// 	StRezRefSaver		aSaver2;
// 
// 	COffscreen			*theBuffer = nil;
// 	PicHandle			thePict = nil;
// #if 0
// 	try
// 	{
// 		ThrowIfNil_( inRezObj );
// 	
// 		// Get an empty default icon if the size is 0
// 		if (inRezObj->GetSize() == 0) {
// 			UIconMisc::GetDefaultBitmap(inRezObj, mResourceType, true );	
// 		} 
// 		
// 		if ( !inRezObj ) throw( resNotFound );
// 		thePict = (PicHandle) inRezObj->GetResData();
// 		if ( !thePict ) throw( resNotFound );
// 		
// 		theBuffer = UGraphicConversion::PictureToOffscreen( thePict );
// 		this->InitializeFromBuffer( theBuffer );
// 		
// 	}
// 	catch( ... )
// 	{
// 		if ( theBuffer ) delete( theBuffer );
// 		( thePict );
// 		throw;
// 	}
// 	
// 	delete theBuffer;
// 	( thePict );
// 	#endif
}


// ---------------------------------------------------------------------------
// 	InitializeFromBuffer
// ---------------------------------------------------------------------------
void
CWindow_Picture::InitializeFromBuffer( COffscreen *inBuffer )
{	
	this->SetImage( inBuffer, resize_All );
}


// ---------------------------------------------------------------------------
// 	SaveAsResource
// ---------------------------------------------------------------------------

void
CWindow_Picture::SaveAsResource( CRezMap *inMap, ResIDT inResID )
{
#pragma unused(inMap, inResID)

	COffscreen	*theBuffer = this->GetCombinedBuffer();
	if ( !theBuffer ) return;
		
// 	Handle h = nil;
// #if 0
// 	try
// 	{
// 		h = (Handle) UGraphicConversion::OffscreenToPicture( theBuffer );
// 		CRezObj *	theRes = mOwnerDoc->GetRezObj();
// 		ThrowIfNil_( theRes );
// 		theRes->SetResData( h );
// 	}
// 	catch( ... )
// 	{
// 		( h );
// 		throw;
// 	}
// 	
// 	( h );
// 	this->SetDirty( false );
//  #endif
}


// ---------------------------------------------------------------------------
// 	ChangeImageSize
// ---------------------------------------------------------------------------
void
CWindow_Picture::ChangeImageSize( SInt32 inWidth, SInt32 inHeight, Boolean inStretch )
{
	ThrowIf_( (inWidth < mMinImageWidth) || (inHeight < mMinImageHeight) );
	ThrowIf_( (inWidth > mMaxImageWidth) || (inHeight > mMaxImageHeight) );
	ThrowIfNil_( mCurrentImage );
	
	Rect		destR;
	COffscreen *newBuffer = mCurrentImage->CreateSimilarOffscreen( false, inWidth, inHeight );
	
	try
	{
		if ( inStretch )
			::SetRect( &destR, 0, 0, inWidth, inHeight );
		else
			::SetRect( &destR, 0, 0, mCurrentImage->GetWidth(), mCurrentImage->GetHeight() );
		
		newBuffer->CopyFrom( mCurrentImage, &destR );
		this->SetImage( newBuffer, resize_All, redraw_Later );
	}
	catch( ... )
	{
		delete newBuffer;
		throw;
	}
	
	delete newBuffer;
}

