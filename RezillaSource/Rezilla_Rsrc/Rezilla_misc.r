// ===========================================================================
// Rezilla_misc.r
//                       Created: 2004-02-28 22:51:23
//             Last modification: 2004-11-18 14:30:58
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2003-2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include <Dialogs.r>

// From "PP Copy & Customize.rsrc"
resource 'ALRT' (204, "Low Memory Warning", locked, preload) {
	{104, 130, 205, 488},
	204,
	{	/* array: 4 elements */
		/* [1] */
		OK, visible, silent,
		/* [2] */
		OK, visible, silent,
		/* [3] */
		OK, visible, silent,
		/* [4] */
		OK, visible, silent
	},
	alertPositionMainScreen
};


resource 'DITL' (204, locked, preload) {
	{	/* array DITLarray: 2 elements */
		/* [1] */
		{71, 288, 91, 348},
		Button {
			enabled,
			"OK"
		},
		/* [2] */
		{10, 75, 58, 348},
		StaticText {
			disabled,
			"Memory is getting full. Please try to al"
			"leviate the problem by closing some docu"
			"ments. "
		}
	}
};
// End "PP Copy & Customize.rsrc"

