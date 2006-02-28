// ===========================================================================
// File: "RezSamplePlugin_MENU.r"
//                        Created: 2006-02-22 11:56:51
//              Last modification: 2006-02-22 11:56:51
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2006
// All rights reserved.
// ===========================================================================

#include <Carbon/Carbon.r>

resource 'MENU' (500, "Sample plugin menu") {
	0,
	textMenuProc,
	0x3,
	enabled,
	"Sample",
	{	/* array: 2 elements */
		/* [1] */
		"Reverse string", noIcon, noKey, noMark, plain,
		/* [2] */
		"Rotate string", noIcon, noKey, noMark, plain
	}
};

