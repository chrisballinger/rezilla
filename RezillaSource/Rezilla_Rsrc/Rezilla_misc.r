// ===========================================================================
// Rezilla_misc.r
//                       Created: 2004-02-28 22:51:23
//             Last modification: 2006-03-10 16:39:03
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2003-2004, 2006
// All rights reserved.
// ===========================================================================

#include <Carbon/Carbon.r>


type 'TMPL' {
	array {
		pstring;      		/* Label */
		literal longint;	/* Tag */
	};
};


// PP Customization (from "PP Copy & Customize.rsrc")
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
// End of PP Customization



// Used by the PatternPane in the Icon editor
resource 'PAT#' (1000, sysheap, purgeable) {
	{	/* array PatArray: 39 elements */
/* [1] */		$"FFFF FFFF FFFF FFFF",
/* [2] */		$"DDFF 77FF DDFF 77FF",
/* [3] */		$"DD77 DD77 DD77 DD77",
/* [4] */		$"AA55 AA55 AA55 AA55",
/* [5] */		$"55AA 55AA 55AA 55AA",
/* [6] */		$"55FF 55FF 55FF 55FF",
/* [7] */		$"AAAA AAAA AAAA AAAA",
/* [8] */		$"EEDD BB77 EEDD BB77",
/* [9] */		$"8888 8888 8888 8888",
/* [10] */		$"B130 031B D8C0 0C8D",
/* [11] */		$"8010 0220 0108 4004",
/* [12] */		$"FF88 8888 FF88 8888",
/* [13] */		$"FF80 8080 FF08 0808",
/* [14] */		$"80",
/* [15] */		$"8040 2000 0204 08",
/* [16] */		$"8244 3944 8201 0101",
/* [17] */		$"F874 2247 8F17 2271",
/* [18] */		$"55A0 4040 550A 0404",
/* [19] */		$"2050 8888 8888 0502",
/* [20] */		$"BF00 BFBF B0B0 B0B0",
/* [21] */		$"",
/* [22] */		$"8000 0800 8000 08",
/* [23] */		$"8800 2200 8800 22",
/* [24] */		$"8822 8822 8822 8822",
/* [25] */		$"AA00 AA00 AA00 AA",
/* [26] */		$"FF00 FF00 FF00 FF",
/* [27] */		$"1122 4488 1122 4488",
/* [28] */		$"FF00 0000 FF",
/* [29] */		$"0102 0408 1020 4080",
/* [30] */		$"AA00 8000 8800 80",
/* [31] */		$"FF80 8080 8080 8080",
/* [32] */		$"081C 22C1 8001 0204",
/* [33] */		$"8814 2241 8800 AA",
/* [34] */		$"40A0 0000 040A",
/* [35] */		$"0384 4830 0C02 0101",
/* [36] */		$"8080 413E 0808 14E3",
/* [37] */		$"1020 54AA FF02 0408",
/* [38] */		$"7789 8F8F 7798 F8F8",
/* [39] */		$"0008 142A 552A 1408"
	}
};

