// ===========================================================================
// UResizeDialog.h
//                       Created: 2004-12-11 18:57:30
//             Last modification: 2004-12-11 18:57:30
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

class UResizeDialog {
	public:
		static Boolean	DoResizeDialog( SInt32 inWidth, SInt32 inMinWidth, SInt32 inMaxWidth,
										SInt32 inHeight, SInt32 inMinHeight, SInt32 inMaxHeight,
										SInt32 *outWidth, SInt32 *outHeight );

	protected:
		static void		ShowResizeError( SInt32 inMinWidth, SInt32 inMaxWidth,
										 SInt32 inMinHeight, SInt32 inMaxHeight );
};

