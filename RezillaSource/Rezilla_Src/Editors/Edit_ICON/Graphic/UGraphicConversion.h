// ===========================================================================
// UGraphicConversion.h
//                       Created: 2004-12-11 18:52:47
//             Last modification: 2004-12-18 07:40:14
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_UGraphicConversion
#define _H_UGraphicConversion
#pragma once

class COffscreen;
class CRezMap;

class UGraphicConversion
{
	public:
	
	static PicHandle		OffscreenToPicture( COffscreen *inBuffer, RgnHandle = nil );
	static void				OffscreenToClipboard( COffscreen *, RgnHandle = nil );

	static PicHandle 		GetPictFromClipboard();
	static RgnHandle 		GetRegionFromClipboard();

	static PicHandle		GetPictFromFile( const FSSpec & );

	static COffscreen *		PictureToOffscreen( PicHandle inPict );
	
	static void					SaveOffscreenAsResource( 
										CRezMap *, ResType inResType, ResIDT inResID,
										COffscreen *inBuffer, SInt32 rowBytes = -1,
										COffscreen *maskBuffer = nil, SInt32 maskOffset = 0,
										SInt32 maskRowBytes = -1 );
};

#endif // _H_UGraphicConversion
