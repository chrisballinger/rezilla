// ===========================================================================
// Rezilla_misc.r
//                       Created: 2004-02-28 22:51:23
//             Last modification: 2004-12-28 12:35:50
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2003-2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include <Dialogs.r>

// Rezilla Icon family info type
type 'RzII' {
	literal longint;	/* defaultPane */
	longint = $$CountOf(EntriesList);
	wide array EntriesList {
		literal longint;	/* rezType */
		longint;            /* flags */
		longint;            /* width */
		longint;            /* height */
		longint;            /* depth */
		longint;            /* rowBytes */
		literal longint;	/* samplePaneID */
		longint;            /* maskOffset */
		longint;            /* maskRowBytes */
		literal longint;	/* maskSamplePaneID */
	};
};

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


// These icon family information resources (cf type definition above) must
// have the same ID as the corresponding PPob resources
// (PPob_IconSuiteEditor and PPob_ICONEditor). They are used by the
// CWindow_Family class constructor.
resource 'RzII' (10600, "Family view info") {
	'icl8',
	{	/* array EntriesList: 9 elements */
/* [1] */	'icl8', 0, 32, 32, 8, 32, 'icl8', 0, 0, '????',
/* [2] */	'icl4', 0, 32, 32, 4, 16, 'icl4', 0, 0, '????',
/* [3] */	'ICN#', 0, 32, 32, 1, 4, 'ICN#', 128, 4, 'MSK1',
/* [4] */	'ics8', 0, 16, 16, 8, 16, 'ics8', 0, 0, '????',
/* [5] */	'ics4', 0, 16, 16, 4, 8, 'ics4', 0, 0, '????',
/* [6] */	'ics#', 0, 16, 16, 1, 2, 'ics#', 32, 2, 'MSK2',
/* [7] */	'icm8', 0, 16, 12, 8, 16, 'icm8', 0, 0, '????',
/* [8] */	'icm4', 0, 16, 12, 4, 8, 'icm4', 0, 0, '????',
/* [9] */	'icm#', 0, 16, 12, 1, 2, 'icm#', 24, 2, 'MSK3'
	}
};


resource 'RzII' (10602, "Icon view info") {
	'ICON',
	{	/* array EntriesList: 1 elements */
/* [1] */		'ICON', 0, 32, 32, 1, 4, 'ICON', 0, 0, '????'
	}
};


// Template for the 'RzII' resource type
resource 'TMPL' (1000, "RzII", purgeable) {
	{
		"Rezilla icon family info", 'DVDR',
		"Default pane",				'TNAM',
		"Count:",					'LCNT',
		"Icons",					'LSTC',
		"Rez type",					'TNAM',
		"Flags",					'DLNG',
		"Width",					'DLNG',
		"Height",					'DLNG',
		"Depth",					'DLNG',
		"Row bytes",				'DLNG',
		"Sample pane ID",			'TNAM',
		"Mask offset",				'DLNG',
		"Mask row bytes",			'DLNG',
		"Mask sample pane ID",		'TNAM',
		"*****",					'LSTE'
	}
};

