// ===========================================================================
// COffscreen.h
//                       Created: 2004-12-11 18:52:53
//             Last modification: 2005-01-03 06:34:57
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_COffscreen
#define _H_COffscreen
#pragma once

#include "RezillaConstants.h"
#include "UPixelHelper.h"

#include <QDOffscreen.h>	

class COffscreen;
class CSharedPalette;

#define SU_BUFFER_LEAK_CHECK	


class COffscreen {
	public:
		static COffscreen *	CreateBuffer( SInt32 inWidth, SInt32 inHeight, SInt32 inDepth,
												CTabHandle inTable = nil, 
												GDHandle inDevice = nil,
												Boolean inKeepLocal = true );

		static GWorldPtr		CreateGWorld( SInt32 inWidth, SInt32 inHeight, SInt32 inDepth,
												CTabHandle inTable = nil, 
												GDHandle inDevice = nil,
												Boolean inKeepLocal = true,
												SInt32 *outRowBytes = nil );

		virtual					~COffscreen();
		
		// getting buffer info
		virtual SInt32			GetWidth();
		virtual SInt32			GetHeight();
		virtual SInt32			GetDepth();
	
		virtual SInt32			GetRowBytes();
		virtual CTabHandle		GetColorTable();
		virtual GWorldPtr		GetGWorld();
		virtual PixMapHandle	GetPixMap();
		
		virtual Boolean			HasDirectPixels();
		
		// Getting & setting pixels
		virtual PixelValue		GetPixel( SInt32 h, SInt32 v );
		virtual void			SetPixel( SInt32 h, SInt32 v, PixelValue );
		
		virtual Color32			GetPixelColor( SInt32 h, SInt32 v );
		virtual RGBColor		GetPixelRGB( SInt32 h, SInt32 v );
		
		// Converting between pixel values and colors
		virtual Color32 		PixelValueToColor32( PixelValue thePixelValue );
		virtual PixelValue		Color32ToPixelValue( Color32 );
		virtual RGBColor		PixelValueToRGB( PixelValue thePixelValue );
		virtual PixelValue		RGBToPixelValue( const RGBColor & );
		
		// Low-level calls available for speedy pixel access
		virtual void			SetForeColor( Color32 );
		virtual void			SetBackColor( Color32 );
		virtual void			SetForePixelValue( PixelValue );
		virtual void			SetBackPixelValue( PixelValue );
		
		// Low-level calls available for speedy pixel access
		virtual RawPtr			RawGetRowPtr( SInt32 v );
		virtual PixelValue		RawGetPixel( RawPtr inRowPtr, SInt32 h );
		virtual void			RawSetPixel( RawPtr inRowPtr, SInt32 h, PixelValue inPixel );
		
		virtual void			RawSetPixelColor( RawPtr inRowPtr, SInt32 h, Color32 inColor );
		virtual Color32			RawGetPixelColor( RawPtr inRowPtr, SInt32 h );
	
		// For drawing to
		virtual void			BeginDrawing();
		virtual void			EndDrawing();
	
		// Palette & Color Table Stuff
		virtual void			AssignPalette( CTabHandle );
		virtual void			AssignPalette( CSharedPalette * );
		virtual CSharedPalette	*GetPalette();
		
		// Handy utilities
		virtual void			ResetPen();
		virtual void			ResetColors();
		virtual void			EraseToWhite();
		virtual Boolean			IsErased();
		
		// Copying buffers
		virtual void			CopyTo( GrafPtr, const Rect *destR = nil, 
										const Rect *sourceR = nil, SInt16 xferMode = srcCopy, 
										RgnHandle inMaskRgn = nil );
		
		virtual void			CopyTo( COffscreen *, const Rect *destR = nil, 
										const Rect *sourceR = nil, SInt16 xferMode = srcCopy,
										RgnHandle inMaskRgn = nil );
		
		virtual void			CopyFrom( COffscreen *, const Rect *destR = nil,
										const Rect *sourceR = nil, SInt16 xferMode = srcCopy,
										RgnHandle inMaskRgn = nil );

		virtual void			CopyFromRawData( RawPtr sourceData, SInt32 sourceRowBytes );
		virtual void			CopyToRawData( RawPtr destData, SInt32 destRowBytes );

		virtual void 			CopyFromAndDownSample( COffscreen *inSource, 
														Color32 inMatchColor = kWhiteColor32,
														Color32 inDestColor = kBlackColor32 );
		
		// Misc
		virtual COffscreen		*CreateSimilarOffscreen( Boolean inUseSameDevice = false,
										SInt32 newWidth = -1, SInt32 newHeight = -1 );
		virtual void			IncreaseInverseTableSize();
		
		virtual RgnHandle		ConvertToRegion();
		virtual void			DebugShowInWindow();
		
		static SInt32			GetBufferCount();			// leak detection

		
	protected:
		GWorldPtr				mWorld;
		SInt32					mWidth, mHeight, mDepth, mRowBytes;
		Boolean					mHasDirectPixels;
		RawPtr					*mRowArray;			// pointers to each row of pixmap
		PixMapHandle			mPixMap;

		// This is used for leak detection
		static SInt32			sNumBuffers;
		
		// Pointers to functions for getting/setting pixel values
		FPixelGetter			mPixelGetter;
		FPixelSetter			mPixelSetter;
	
		CSharedPalette	*		mPalette;
		
								COffscreen( SInt32 inWidth, SInt32 inHeight, SInt32 inDepth,
												CTabHandle inTable, GDHandle inDevice,
												Boolean inKeepLocal );

		virtual void			ResetColorsSelf();
		virtual void			SetupRowArray();
};



/**************************
*                         *
*   StSaveAndDraw class   *
*                         *
**************************/

class StSaveAndDraw
{
	public:
					StSaveAndDraw( COffscreen * );
		virtual 	~StSaveAndDraw();
	
	protected:
		CGrafPtr	mOldPort;
		GDHandle	mOldDevice;
};


/*********************************
*                                *
*   StBufferLeakDetector class   *
*                                *
*********************************/

class StBufferLeakDetector
{
	public:
					StBufferLeakDetector();
		virtual 	~StBufferLeakDetector();
	
	protected:
		SInt32		mNumBuffers;
};


/*************************
*                        *
*   COffscreen inlines   *
*                        *
*************************/
inline SInt32 COffscreen::GetWidth()
{
	return( mWidth );
}

inline SInt32 COffscreen::GetHeight()
{
	return( mHeight );
}

inline SInt32 COffscreen::GetDepth()
{
	return( mDepth );
}

inline GWorldPtr COffscreen::GetGWorld()
{
	return( mWorld );
}

inline SInt32 COffscreen::GetRowBytes()
{
	return( mRowBytes );
}

inline PixMapHandle COffscreen::GetPixMap()
{
	return( mPixMap );
}

inline RawPtr COffscreen::RawGetRowPtr( SInt32 v )
{
	return( mRowArray[ v ] );
}

inline PixelValue COffscreen::RawGetPixel( RawPtr inRowPtr, SInt32 h )
{
	return( (*mPixelGetter)( inRowPtr, h ) );
}

inline void COffscreen::RawSetPixel( RawPtr inRowPtr, SInt32 h, PixelValue inColor )
{
	(*mPixelSetter)( inRowPtr, h, inColor );
}

inline Boolean COffscreen::HasDirectPixels()
{
	return( mHasDirectPixels );
}

#endif // _H_COffscreen
