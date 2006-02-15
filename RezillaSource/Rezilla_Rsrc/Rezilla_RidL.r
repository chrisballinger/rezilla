// ===========================================================================
// Rezilla_RidL.r
//                       Created: 2004-12-28 08:17:46
//             Last modification: 2005-02-23 09:05:37
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004, 2005
// All rights reserved.
// ===========================================================================

// Resource ID List (long integers)
type 'RidL' {
	integer = $$CountOf(ResourceIDList);
	wide array ResourceIDList {
		longint;
	};
};


// RidL_ToolList
resource 'RidL' (300, "Icon editor broadcasters (tools)") {
	{	/* array ResourceIDList: 18 elements */
/* [1]  tLAS */		1951154515,
/* [2]  tSEL */		1951614284,
/* [3]  tTXT */		1951684692,
/* [4]  tPEN */		1951417678,
/* [5]  tERA */		1950700097,
/* [6]  tBUC */		1950504259,
/* [7]  tDRO */		1950634575,
/* [8]  tLIN */		1951156558,
/* [9]  tREC */		1951548739,
/* [10] tFRC */		1950765635,
/* [11] tRRC */		1951552067,
/* [12] tFRR */		1950765650,
/* [13] tOVL */		1951356492,
/* [14] tFOV */		1950764886,
/* [15] tHOT */		1950895956,
/* [16] tPAT */		1951416660,
/* [17] tBCL */		1950499660,
/* [18] tFCL */		1950761804
	}
};


resource 'RidL' (301, "Icon editor broadcasters (cicn)") {
	{	/* array ResourceIDList: 3 elements */
/* [1] cicn */	1667851118,
/* [2] ICON */	1229147982,
/* [3] MASK */	1296126795
	}
};


resource 'RidL' (302, "Icon editor broadcasters (icon family)") {
	{	/*  array ResourceIDList: 12 elements */
/* [1]  icl8 */	1768123448,
/* [2]  icl4 */	1768123444,
/* [3]  ICN# */	1229147683,
/* [4]  MSK1 */	1297304369,
/* [5]  ics8 */	1768125240,
/* [6]  ics4 */	1768125236,
/* [7]  ics# */	1768125219,
/* [8]  MSK2 */	1297304370,
/* [9]  icm8 */	1768123704,
/* [10] icm4 */	1768123700,
/* [11] icm# */	1768123683,
/* [12] MSK3 */	1297304371
	}
};

