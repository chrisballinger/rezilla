// ===========================================================================
// CWindow_Picture.h
//                       Created: 2004-12-11 18:56:32
//             Last modification: 2005-02-17 18:09:37
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CWindow_Picture
#define _H_CWindow_Picture
#pragma once

#include "CIcon_EditorWindow.h"

class CRezMap;
class CRezObj;


class CWindow_Picture : public CIcon_EditorWindow {
	public:
		enum { class_ID = FOUR_CHAR_CODE('PicV') };

									CWindow_Picture( LStream * );
		virtual						~CWindow_Picture();
		
		static CWindow_Picture *	OpenPaintWindow(CRezObj * inRezObj, ResIDT inPPobID );
		static CWindow_Picture *	CreateFromStream( LStream *inStream );
		
		virtual void				FinishCreateSelf();
		
		virtual void				InitializeFromResource(CRezObj * inRezObj);
		virtual void				InitializeFromBuffer( COffscreen * );
		
		virtual void				SaveAsResource( CRezMap *, ResIDT );
		virtual void				ChangeImageSize( SInt32 inWidth, SInt32 inHeight, Boolean inStretch );
};

#endif // _H_CWindow_Picture
