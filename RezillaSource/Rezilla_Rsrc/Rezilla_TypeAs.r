// ===========================================================================
// Rezilla_TypeAs.r
//                       Created: 2005-09-22 10:44:39
//             Last modification: 2005-02-23 09:05:37
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004, 2005
// All rights reserved.
// ===========================================================================

// List of substitution types
type 'RzTA' {
	wide array {
		literal longint;		/* Original type */
		literal longint;		/* Substitute type */
	};
};


// RidL_ToolList
resource 'RzTA' (0, "List of substitution types") {
	{	/* array: 27 elements */
		/* [1] */
		'68k!', 'mem!',
		/* [2] */
		'actb', 'wctb',
		/* [3] */
		'aeut', 'aete',
		/* [4] */
		'CMNU', 'cmnu',
		/* [5] */
		'dctb', 'wctb',
		/* [6] */
		'DLIM', 'RECT',
		/* [7] */
		'DRVW', 'DRVR',
		/* [8] */
		'fbnd', 'cbnd',
		/* [9] */
		'fctb', 'clut',
		/* [10] */
		'itl0', 'INTL',
		/* [11] */
		'kcl4', 'icl4',
		/* [12] */
		'kcl8', 'icl8',
		/* [13] */
		'KCN#', 'ICN#',
		/* [14] */
		'kcs#', 'ics#',
		/* [15] */
		'kcs4', 'ics4',
		/* [16] */
		'kcs8', 'ics8',
		/* [17] */
		'MBOR', 'MBAR',
		/* [18] */
		'NFNT', 'FONT',
		/* [19] */
		'plst', 'TEXT',
		/* [20] */
		'ppc!', 'mem!',
		/* [21] */
		'RGB ', 'rgb ',
		/* [22] */
		'siow', 'STR ',
		/* [23] */
		'tbnd', 'cbnd',
		/* [24] */
		'thar', 'thnr',
		/* [25] */
		'trk#', 'src#',
		/* [26] */
		'wind', 'flac',
		/* [27] */
		'WLIM', 'RECT'
	}
};

