// ===========================================================================
// CWindow_Pattern.cp
//                       Created: 2004-12-11 18:50:21
//             Last modification: 2005-02-17 17:29:37
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#include "CWindow_Pattern.h"
#include "CColorTableBuilder.h"
#include "CIcon_EditorWindow.h"
#include "CPatternTargetView.h"
#include "CRezObj.h"
#include "CRezMap.h"
#include "CEditorDoc.h"
#include "UColorUtils.h"
#include "COffscreen.h"
#include "UIconMisc.h"
#include "UMiscUtils.h"
#include "UResourceMgr.h"
#include "RezillaConstants.h"

#include <LStaticText.h>

// ---------------------------------------------------------------------------
// 	OpenPaintWindow
// ---------------------------------------------------------------------------

CWindow_Pattern *
CWindow_Pattern::OpenPaintWindow( CRezObj * inRezObj, ResIDT inPPobID )
{
	CWindow_Pattern *	theWindow = nil;

	try
	{
		theWindow = (CWindow_Pattern*) CIcon_EditorWindow::CreatePaintWindow( inPPobID );
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

CWindow_Pattern *CWindow_Pattern::CreateFromStream( LStream *inStream )
{
	return new CWindow_Pattern( inStream );
}


// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------

CWindow_Pattern::CWindow_Pattern( LStream *inStream )
		: CIcon_EditorWindow( inStream )
{
	mColorSample = nil;
	mBWSample = nil;
	mResourceType = 0;		// don't have this yet
	mPixPatWidth = 0;
	mPixPatHeight = 0;
	mPrefersIconColors = false;
	
	// The canvas overlaps the b&w pattern if we set the minimum
	// width/height to less than 8x8. but since ResEdit has an 8x8 minimum
	// anyway and nobody is likely to care, we'll have one too.
	mMinImageWidth = 8;
	mMinImageHeight = 8;
}


// ---------------------------------------------------------------------------
// 	Destructor
// ---------------------------------------------------------------------------

CWindow_Pattern::~CWindow_Pattern()
{
		// close the file ???
}


// ---------------------------------------------------------------------------
// 	FinishCreateSelf
// ---------------------------------------------------------------------------

void
CWindow_Pattern::FinishCreateSelf()
{
	CIcon_EditorWindow::FinishCreateSelf();

	mBWSample = (CPatternTargetView*) this->FindPaneByID( item_IconEditBWSample );
	ThrowIfNil_( mBWSample );
	mSamplePaneList[ mNumSamplePanes++ ] = mBWSample;
	
	mColorSample = (CPatternTargetView*) this->FindPaneByID( ImgType_PixPat );
	if ( mColorSample )
		mSamplePaneList[ mNumSamplePanes++ ] = mColorSample;

	if ( mSampleWell )
		mSampleWell->GetFrameSize( mInitialSampleWellSize );
	else
	{
		mInitialSampleWellSize.width = 0;
		mInitialSampleWellSize.height = 0;
	}

	// Link the broadcasters
	UReanimator::LinkListenerToBroadcasters( this, this, PPob_PatternEditor );
	this->BecomeListenerTo( mNumSamplePanes, mSamplePaneList );
}


// ---------------------------------------------------------------------------
// 	InitializeFromResource
// ---------------------------------------------------------------------------

void
CWindow_Pattern::InitializeFromResource(CRezObj * inRezObj)
{
	StGWorldSaver		aSaver;
	StRezRefSaver		aSaver2;

	COffscreen			*colorImage = nil, *bwImage = nil;
	Handle				h = nil;
	
	mResourceType = inRezObj->GetType();
	
	try
	{
		ThrowIfNil_( inRezObj );
	
		// Get an empty default icon if the size is 0
		if (inRezObj->GetSize() == 0) {
			UIconMisc::GetDefaultBitmap(inRezObj, mResourceType, true );	
		} 
		
		// Get the raw resource handle
		h = inRezObj->GetData();
		ThrowIfNil_( h );
		
		// Draw the pattern(s) into bitmaps
		switch( mResourceType )
		{
			case ImgType_PixPat:
				this->ParseColorPattern( h, &colorImage, &bwImage );
				mAllowImageResizing = true;
				break;
			case ImgType_Pattern:
				this->ParseBWPattern( h, &bwImage );
				break;
			default:
				throw( err_IconUnknownDataType );
		}
		
		// Resize the sample well if the color pattern is bigger than 8x8
		if ( colorImage )
		{
			SInt32	width = colorImage->GetWidth();
			SInt32	height = colorImage->GetHeight();
			
			// Save these _now_ because SetImage() will trigger a call to
			// GetZoomFactor()
			mPixPatWidth = width;
			mPixPatHeight = height;
			
			this->ResizeSampleWell( width, height );
			
			this->SetImage( colorImage, resize_All, redraw_Later );

			mColorSample->SetBuffer( colorImage, redraw_Dont );
			colorImage = nil;		// because it belongs to the sample pane now
			mColorSample->SetTarget( true, redraw_Dont );
			
			mCurrentSamplePane = mColorSample;
		}
		else
		{
			this->SetImage( bwImage, resize_All, redraw_Later );
			mCurrentSamplePane = mBWSample;	
			mBWSample->SetTarget( true, redraw_Dont );
		}
		
		mBWSample->SetBuffer( bwImage, redraw_Dont );
		bwImage = nil;			// because it belongs to the sample pane now

	}
	catch( ... )
	{
		if ( bwImage ) delete( bwImage );
		if ( colorImage ) delete( colorImage );
		( h );
		throw;
	}
	
	( h );
}


// ---------------------------------------------------------------------------
// 	ResizeSampleWell
// ---------------------------------------------------------------------------
// 	Only the color pattern size can change.

void
CWindow_Pattern::ResizeSampleWell( SInt32 inPatternWidth, SInt32 inPatternHeight )
{
	if ( mResourceType != ImgType_PixPat ) return;

	SDimension16	initialColorSize;
	SDimension16	minColorSize;
	SInt32			dh = inPatternWidth - 8;		// since samples are sized for 8+8 initially
	SInt32			dv = inPatternHeight - 8;
	LStaticText *	theLabel;

	mColorSample->GetInitialPaneSize( &initialColorSize );
	mColorSample->GetMinPaneSize( &minColorSize );

	// Sample panes grow in a 1:1 ratio with the icon, but never grow
	// smaller than a certain size.
	SInt32 			newPaneWidth = MAX( minColorSize.width, initialColorSize.width + 2 * dh );
	SInt32			newPaneHeight = MAX( minColorSize.height, initialColorSize.height + 2 * dv );
	
	mColorSample->ResizeFrameTo( newPaneWidth, newPaneHeight, true );
	
	// Otherwise boxes overlap...
	if ( dv < 0 )
		dv = 0;
		
	// Otherwise the right side gets cutoff on small cicns
	if ( dh < 0 )
		dh = 0;

	// The b&w must be moved down so it doesn't overlap the color one
	SPoint32		initialLoc, currentLoc;
	mBWSample->GetInitialPaneLocation( &initialLoc );
	mBWSample->GetFrameLocation( currentLoc );
	mBWSample->MoveBy( 0, initialLoc.v + 2 * dv - currentLoc.v, true );

	// Move the labels too
	theLabel = dynamic_cast<LStaticText *> (this->FindPaneByID( item_IconLabelName1 ));
	if (theLabel) {
		theLabel->MoveBy( 0, initialLoc.v + 2 * dv - currentLoc.v, true );
	} 

	theLabel = dynamic_cast<LStaticText *> (this->FindPaneByID( item_IconLabelName2 ));
	if (theLabel) {
		theLabel->MoveBy( 0, initialLoc.v + 2 * dv - currentLoc.v, true );
	} 

	// The sample well contains both samples and needs to be resized
	// accordingly. Never allow it to get tiny or things may get cut-off.
	// The numbers should probably be read from a resource.
	if ( mSampleWell )
		mSampleWell->ResizeFrameTo( MAX( 50, mInitialSampleWellSize.width + 2 * dh ),
									MAX( 140, mInitialSampleWellSize.height + 3 * dv),
									true );
}


// ---------------------------------------------------------------------------
// 	SaveAsResource
// ---------------------------------------------------------------------------

void
CWindow_Pattern::SaveAsResource( CRezMap *inMap, ResIDT inResID )
{
#pragma unused(inMap, inResID)

	Handle		h = nil;
	
	ThrowIfNil_( mBWSample );
	COffscreen	*bwBuffer = mBWSample->GetBuffer();

	try
	{
		switch( mResourceType )
		{
			case ImgType_Pattern:
				h = this->CreateBWPattern( bwBuffer );
				break;
			
			case ImgType_PixPat:
				ThrowIfNil_( mColorSample );
				h = this->CreateColorPattern( mColorSample->GetBuffer(), bwBuffer );
				break;
			
			default:
				throw( err_IconInvalidImageFormat );
		}

		CRezObj *	theRes = mOwnerDoc->GetRezObj();
		ThrowIfNil_( theRes );
		theRes->SetData( h );

	}
	catch( ... )
	{
		( h );
		throw;
	}
	
	( h );
	this->SetDirty( false );
}


// ---------------------------------------------------------------------------
// 	ParseColorPattern
// ---------------------------------------------------------------------------

void
CWindow_Pattern::ParseColorPattern( Handle inPattern, COffscreen **outColor,
												COffscreen **outBW )
{
	// See IM V-79 for details

	StGWorldSaver		save1;
	StHandleLocker		save2( inPattern );
	PixPatPtr			p = (PixPatPtr) *inPattern;
	CTabHandle			theTable = nil;
	COffscreen			*tempColorBuffer = nil, *colorBuffer = nil, *bwBuffer = nil;

	try
	{	
		if ( p->patType != 1 )
			throw( err_IconInvalidImageFormat );
			
		// First handle the b&w pattern
		bwBuffer = this->BWPatternToOffscreen( p->pat1Data );

		// Now the color pattern
		PixMapPtr			theMap = (PixMapPtr)( *inPattern + (SInt32) p->patMap );
		UInt8 *				theData = (UInt8*)( *inPattern + (SInt32) p->patData );
		
		SInt32				depth = theMap->pixelSize;
		SInt32				width = theMap->bounds.right - theMap->bounds.left;
		SInt32				height = theMap->bounds.bottom - theMap->bounds.top;
		SInt32				rowBytes = theMap->rowBytes & 0x3FFF;		// clear flags
		
		if ( (depth != 1) && (depth != 2) && (depth != 4) && (depth != 8) )
			throw( err_IconInvalidImageDepth );
		
		if ( (width <= 3) || (width > 64) || (height <= 3) || (height > 64) )
			throw( err_IconInvalidImageSize );
		
		theTable = UColorUtils::NewColorTableFromPtr( depth, (UInt8*)( *inPattern + (SInt32)theMap->pmTable) );
		tempColorBuffer = COffscreen::CreateBuffer( width, height, depth, theTable );
		tempColorBuffer->CopyFromRawData( theData, rowBytes );

		// Now switch to a 32-bit buffer
		colorBuffer = COffscreen::CreateBuffer( width, height, 32 );
		colorBuffer->CopyFrom( tempColorBuffer );
	}
	catch( ... )
	{
		delete colorBuffer;
		delete bwBuffer;
		delete tempColorBuffer;
		if ( theTable )
			::DisposeCTable( theTable );
		throw;
	}
	
	*outColor = colorBuffer;
	*outBW = bwBuffer;

	if ( theTable )
		::DisposeCTable( theTable );
	delete tempColorBuffer;
}


// ---------------------------------------------------------------------------
// 	BWPatternToOffscreen
// ---------------------------------------------------------------------------
COffscreen *CWindow_Pattern::BWPatternToOffscreen( const Pattern &inPattern )
{
	StGWorldSaver	save1;
	CTabHandle		theTable = nil;
	COffscreen		*theBuffer = nil;
	
	try
	{
		theTable = UColorUtils::GetColorTable( 1 );
		
		theBuffer = COffscreen::CreateBuffer( kDefaultPatternWidth, kDefaultPatternHeight, 1, theTable );
		//theBuffer->AssignPalette( theTable );		
		
		theBuffer->BeginDrawing();
			Rect		r;
			::SetRect( &r, 0, 0, kDefaultPatternWidth, kDefaultPatternHeight);
			::PenPat( &inPattern );
			::PaintRect( &r );
			::PenNormal();
		theBuffer->EndDrawing();
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
// 	ParseBWPattern
// ---------------------------------------------------------------------------

void
CWindow_Pattern::ParseBWPattern( Handle inPattern, COffscreen **outBW  )
{
	Pattern		thePattern = **(Pattern**) inPattern;
	*outBW = this->BWPatternToOffscreen( thePattern );
}


// ---------------------------------------------------------------------------
// 	CreateBWPattern
// ---------------------------------------------------------------------------

Handle
CWindow_Pattern::CreateBWPattern( COffscreen *inBuffer )
{
	Handle h = ::NewHandle( sizeof( Pattern ) );
	ThrowIfMemFail_( h );
	
	StHandleLocker	lock( h );
	inBuffer->CopyToRawData( (UInt8*) *h, kBWPatternRowBytes );
	return( h );
}


// ---------------------------------------------------------------------------
// 	CreateColorPattern
// ---------------------------------------------------------------------------

Handle
CWindow_Pattern::CreateColorPattern( COffscreen *inColor, COffscreen *inBW )
{
	Handle			h = nil;
	Boolean			deleteBuffer = false;

	try
	{
		// Downsample the color buffer to a more reasonable depth
		if ( inColor->GetDepth() >= 16 )
		{
			inColor = CColorTableBuilder::DownSampleBuffer( 
											inColor, 
											8,				// max depth
											false, 			// don't force b&w into table
											true, 			// minimize table
											true );			// use larger inverse table
			ThrowIfNil_( inColor );							// shouldn't happen
			deleteBuffer = true;							// since we created it
		}
		
		// Get the color table from the color buffer
		CTabHandle	sourceTable = inColor->GetColorTable();
		ThrowIfNil_( sourceTable );
		SInt32		colorTableBytes = ::GetHandleSize( (Handle) sourceTable );

		// Do some calculations
		SInt32		depth = inColor->GetDepth();
		SInt32		width = inColor->GetWidth();
		SInt32		height = inColor->GetHeight();
	
		SInt32		pixelRowBytes = UColorUtils::CalcRowBytes( width, depth );
		SInt32		pixelBytes = pixelRowBytes * height;
		SInt32		totalBytes = sizeof( PixPat ) + sizeof( PixMap ) + colorTableBytes + pixelBytes;

		SInt32		offsetToPixmap = sizeof(PixPat);
		SInt32		offsetToPixelData = sizeof(PixPat) + sizeof(PixMap);
		SInt32		offsetToColorTable = sizeof(PixPat) + sizeof(PixMap) + pixelBytes;

		// Allocate the pixpat
		h = ::NewHandleClear( totalBytes ); 
		ThrowIfMemFail_( h );
		::HLock( h );
		
		// Fill up the structure (note: fields are already zeroed)
		PixPatPtr	p = (PixPatPtr) *h;
		PixMapPtr	theMap = (PixMapPtr)( *h + offsetToPixmap );
		CTabPtr		destTable = (CTabPtr)( *h + offsetToColorTable );
		
		p->patType = 1;
		p->patMap = (PixMapHandle) offsetToPixmap;
		p->patData = (Handle) offsetToPixelData;
		p->patXValid = -1;
		
		theMap->rowBytes = 0x8000 + pixelRowBytes;
		::SetRect( &theMap->bounds, 0, 0, width, height );
		theMap->hRes = 0x00480000;
		theMap->vRes = 0x00480000;
		theMap->pixelSize = depth;
		theMap->cmpCount = 1;
		theMap->cmpSize = depth;
		theMap->pmTable = (CTabHandle) offsetToColorTable;
		
		inBW->CopyToRawData( (UInt8*) &p->pat1Data, kBWPatternRowBytes );
		inColor->CopyToRawData( (UInt8*) (*h + offsetToPixelData), pixelRowBytes );
		::BlockMoveData( *sourceTable, destTable, colorTableBytes );
		destTable->ctFlags = 0;					// 0 for pixmaps, 0x8000 for devices
	}
	catch( ... )
	{
		if ( deleteBuffer && inColor )
			delete inColor;
		( h );
		throw;
	}
	
	if ( deleteBuffer && inColor )
		delete inColor;
	::HUnlock( h );
	return( h );
}


// ---------------------------------------------------------------------------
// 	GetZoomFactor
// ---------------------------------------------------------------------------
// 	Patterns are always zoomed for the biggest image -- either the b&w
// 	pattern or the color one. We don't want to change zoom factors
// 	everytime the user clicks on a different target box.

SInt32
CWindow_Pattern::GetZoomFactor( SInt32, SInt32, Boolean *outShowGrid )
{
	return CIcon_EditorWindow::GetZoomFactor( MAX(mPixPatWidth, kDefaultPatternWidth), 
									   MAX(mPixPatHeight, kDefaultPatternHeight), 
									   outShowGrid );
}


// ---------------------------------------------------------------------------
// 	ChangeImageSize
// ---------------------------------------------------------------------------
// 	Affects only the pixpat, _not_ the black & white pattern.

void
CWindow_Pattern::ChangeImageSize( SInt32 inWidth, SInt32 inHeight, Boolean inStretch )
{
	ThrowIf_( (inWidth < mMinImageWidth) || (inHeight < mMinImageHeight) );
	ThrowIf_( (inWidth > mMaxImageWidth) || (inHeight > mMaxImageHeight) );
	ThrowIf_( mResourceType != ImgType_PixPat );
	ThrowIfNil_( mColorSample );
	ThrowIfNil_( mCurrentImage );
	
	SInt32			savedWidth = mPixPatWidth;		// in case of error...
	SInt32			savedHeight = mPixPatHeight;
	Boolean			changedSize = true;
	COffscreen		*newBuffer = nil;
	Rect			destR;
	
	try
	{
		// Create a new buffer -- same depth as current one, but new size
		newBuffer = mCurrentImage->CreateSimilarOffscreen( false, inWidth, inHeight );
		
		// Copy the image from the old buffer into the new one
		if ( inStretch )
			::SetRect( &destR, 0, 0, inWidth, inHeight );
		else
			::SetRect( &destR, 0, 0, mCurrentImage->GetWidth(), mCurrentImage->GetHeight() );
		
		newBuffer->CopyFrom( mCurrentImage, &destR );
		
		// Resize the pixpat sample pane
		this->ResizeSampleWell( inWidth, inHeight );
		changedSize = true;
		
		// Keep track of the changed size. do this before SetImage()
		// because it may call GetZoomFactor.
		mPixPatWidth = inWidth;
		mPixPatHeight = inHeight;

		// Set the current buffer -- this can trigger all sorts of things
		// (canvas resize, etc)
		this->SetImage( newBuffer, resize_All, redraw_Later );
		
		// Change the sample pane's buffer.
		// (1) The sample pane will own the buffer after this call (don't
		// delete it)
		// (2) The previous sample pane buffer will be saved away by the
		// PTResizer object

		mColorSample->SetRawBuffer( newBuffer );
	}
	catch( ... )
	{
		// Restore things to the way they were before we were called
		mPixPatWidth = savedWidth;
		mPixPatHeight = savedHeight;

		if ( changedSize )
			this->ResizeSampleWell( mPixPatWidth, mPixPatHeight );
	
		delete newBuffer;
		throw;
	}
}


// ---------------------------------------------------------------------------
// 	ImageSizeChangeUndone
// ---------------------------------------------------------------------------
// 	The panes and image will be restored automatically, we just need to keep
// 	track of the image size.

void
CWindow_Pattern::ImageSizeChangeUndone( SInt32 inWidth, SInt32 inHeight )
{
	mPixPatWidth = inWidth;
	mPixPatHeight = inHeight;
}


// ---------------------------------------------------------------------------
// 	FindCommandStatus
// ---------------------------------------------------------------------------
// 	We override this because we only allow the pixpat to be resized, not
// 	the b&w pattern.

void
CWindow_Pattern::FindCommandStatus( CommandT inCommand, Boolean &outEnabled, 
									Boolean &outUsesMark, UInt16 &outMark, 
									Str255 outName )
{
	if ( inCommand != cmd_IconResizeImage )
	{
		CIcon_EditorWindow::FindCommandStatus( inCommand, outEnabled, outUsesMark, outMark, outName );
		return;
	}
	
	outUsesMark = false;

	if ( (mResourceType != ImgType_PixPat) || (this->GetTargetView() == mBWSample) )
		outEnabled = false;
	else
		outEnabled = true;
}
