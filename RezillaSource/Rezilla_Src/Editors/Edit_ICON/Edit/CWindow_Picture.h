// ===========================================================================
// CWindow_Picture.h
//                       Created: 2004-12-11 18:56:32
//             Last modification: 2004-12-30 09:38:50
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CWindow_Picture
#define _H_CWindow_Picture
#pragma once

#include "CIcon_EditorWindow.h"

class CRezMap;


class CWindow_Picture : public CIcon_EditorWindow {
	public:
		enum { class_ID = FOUR_CHAR_CODE('PicV') };

									CWindow_Picture( LStream * );
		virtual						~CWindow_Picture();
		
		static CWindow_Picture *	OpenPaintWindow( ResIDT inPPobID, CRezMap *, ResIDT );
		static CWindow_Picture *	CreateFromStream( LStream *inStream );
		
		virtual void				InitializeFromResource( CRezMap *, ResIDT );
		virtual void				InitializeFromBuffer( COffscreen * );
		
		virtual void				SaveAsResource( CRezMap *, ResIDT );
		virtual void				ChangeImageSize( SInt32 inWidth, SInt32 inHeight, Boolean inStretch );
};

#endif // _H_CWindow_Picture
