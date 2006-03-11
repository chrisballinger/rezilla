type 'TMPL' {
	array {
		pstring;      		/* Label */
		literal longint;	/* Tag */
	};
};

resource 'TMPL' (1000, "accl") {
	{	/* array: 10 elements */
		/* [1] */
		"Device identifier or device class",
		'TNAM',
		/* [2] */
		"Number of tables for this device",
		'OCNT',
		/* [3] */
		"Mouse acceleration table",
		'LSTC',
		/* [4] */
		"Acceleration provided by this table (fix"
		"ed)",
		'HLNG',
		/* [5] */
		"Number of control points for this device",
		'OCNT',
		/* [6] */
		"Control points sorted by first value",
		'LSTC',
		/* [7] */
		"Device speed (inches per second) (fixed)",
		'HLNG',
		/* [8] */
		"Cursor speed (inches per second) (fixed)",
		'HLNG',
		/* [9] */
		"-----",
		'LSTE',
		/* [10] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1001, "ACfg") {
	{	/* array: 19 elements */
		/* [1] */
		"International sorting",
		'BFLG',
		/* [2] */
		"Enable help tags",
		'BFLG',
		/* [3] */
		"Default Unicode text export",
		'BFLG',
		/* [4] */
		"Reserved",
		'BFLG',
		/* [5] */
		"Browser window button right margin",
		'DWRD',
		/* [6] */
		"Browser window search button gap",
		'DWRD',
		/* [7] */
		"Line gap for small text display",
		'DWRD',
		/* [8] */
		"vCenter tweak for small text display",
		'DWRD',
		/* [9] */
		"Line gap for large text display",
		'DWRD',
		/* [10] */
		"vCenter tweak for large text display",
		'DWRD',
		/* [11] */
		"Browser window minimum width",
		'DWRD',
		/* [12] */
		"Browser window minimum height",
		'DWRD',
		/* [13] */
		"Browser window minimum list width",
		'DWRD',
		/* [14] */
		"Reserved",
		'FWRD',
		/* [15] */
		"Reserved",
		'FLNG',
		/* [16] */
		"Reserved",
		'FLNG',
		/* [17] */
		"Reserved",
		'FLNG',
		/* [18] */
		"Reserved",
		'FLNG',
		/* [19] */
		"Reserved",
		'FLNG'
	}
};

resource 'TMPL' (1002, "actb") {
	{	/* array: 12 elements */
		/* [1] */
		"Alert color seed",
		'HLNG',
		/* [2] */
		"Flags",
		'HWRD',
		/* [3] */
		"Count:",
		'ZCNT',
		/* [4] */
		"List of Colors",
		'LSTC',
		/* [5] */
		"Part code",
		'DWRD',
		/* [6] */
		"Content color=0",
		'CASE',
		/* [7] */
		"Frame color=1",
		'CASE',
		/* [8] */
		"Text color=2",
		'CASE',
		/* [9] */
		"Hilite color=3",
		'CASE',
		/* [10] */
		"Title bar color=4",
		'CASE',
		/* [11] */
		"Color",
		'COLR',
		/* [12] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1003, "acur") {
	{	/* array: 6 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"Filler",
		'FWRD',
		/* [3] */
		"Cursor frames",
		'LSTC',
		/* [4] */
		"'CURS' resource ID for a frame",
		'RSID',
		/* [5] */
		"Filler",
		'FWRD',
		/* [6] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1004, "admn") {
	{	/* array: 4 elements */
		/* [1] */
		"Version",
		'DWRD',
		/* [2] */
		"Latest=-978",
		'CASE',
		/* [3] */
		"Reserved",
		'DLNG',
		/* [4] */
		"Reserved",
		'DLNG'
	}
};

resource 'TMPL' (1005, "aedt") {
	{	/* array: 21 elements */
		/* [1] */
		"Apple Events Dispatch Table",
		'LSTB',
		/* [2] */
		"Event class",
		'TNAM',
		/* [3] */
		"Required class=aevt",
		'CASE',
		/* [4] */
		"Core class=core",
		'CASE',
		/* [5] */
		"Misc class=misc",
		'CASE',
		/* [6] */
		"Event ID",
		'TNAM',
		/* [7] */
		"Open application=oapp",
		'CASE',
		/* [8] */
		"Open document=odoc",
		'CASE',
		/* [9] */
		"Print document=pdoc",
		'CASE',
		/* [10] */
		"Quit application=quit",
		'CASE',
		/* [11] */
		"Close=clos",
		'CASE',
		/* [12] */
		"Count=cnte",
		'CASE',
		/* [13] */
		"Data size=dsiz",
		'CASE',
		/* [14] */
		"Delete=delo",
		'CASE',
		/* [15] */
		"Duplicate=clon",
		'CASE',
		/* [16] */
		"Exists=doex",
		'CASE',
		/* [17] */
		"Make=crel",
		'CASE',
		/* [18] */
		"Move=move",
		'CASE',
		/* [19] */
		"Select=slct",
		'CASE',
		/* [20] */
		"Event reference constant",
		'DLNG',
		/* [21] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1006, "ALRT") {
	{	/* array: 26 elements */
		/* [1] */
		"Bounds rect",
		'RECT',
		/* [2] */
		"DITL ID (Items list)",
		'DWRD',
		/* [3] */
		"The stages are ordered 4, 3, 2, 1",
		'DVDR',
		/* [4] */
		"Stage 4 Bold Outline",
		'WBIT',
		/* [5] */
		"Visible",
		'WBIT',
		/* [6] */
		"Sound number",
		'WB02',
		/* [7] */
		"Stage 3 Bold Outline",
		'WBIT',
		/* [8] */
		"Visible",
		'WBIT',
		/* [9] */
		"Sound number",
		'WB02',
		/* [10] */
		"Stage 2 Bold Outline",
		'WBIT',
		/* [11] */
		"Visible",
		'WBIT',
		/* [12] */
		"Sound number",
		'WB02',
		/* [13] */
		"Stage 1 Bold Outline",
		'WBIT',
		/* [14] */
		"Visible",
		'WBIT',
		/* [15] */
		"Sound number",
		'WB02',
		/* [16] */
		"Alert positioning",
		'HWRD',
		/* [17] */
		"No auto center=$0000",
		'CASE',
		/* [18] */
		"Center on main screen=$280A",
		'CASE',
		/* [19] */
		"Center in parent window=$A80A",
		'CASE',
		/* [20] */
		"Center on parent's screen=$680A",
		'CASE',
		/* [21] */
		"Alert on main screen=$300A",
		'CASE',
		/* [22] */
		"Alert in parent window=$B00A",
		'CASE',
		/* [23] */
		"Alert in parent's screen=$700A",
		'CASE',
		/* [24] */
		"Stagger on main screen=$380A",
		'CASE',
		/* [25] */
		"Stagger in parent window=$B80A",
		'CASE',
		/* [26] */
		"Stagger on parent's screen=$780A",
		'CASE'
	}
};

resource 'TMPL' (1007, "alrx") {
	{	/* array: 29 elements */
		/* [1] */
		"Version",
		'KWRD',
		/* [2] */
		"Latest=1",
		'CASE',
		/* [3] */
		"Original=0",
		'CASE',
		/* [4] */
		"1",
		'KEYB',
		/* [5] */
		"Reserved",
		'LB28',
		/* [6] */
		"Use theme controls",
		'LBIT',
		/* [7] */
		"Alert is movable",
		'LBIT',
		/* [8] */
		"Use control hierarchy",
		'LBIT',
		/* [9] */
		"Use theme background",
		'LBIT',
		/* [10] */
		"Reference constant",
		'DLNG',
		/* [11] */
		"Window type (Classic=0, Theme=1)",
		'BFLG',
		/* [12] */
		"Filler",
		'FBYT',
		/* [13] */
		"Window title (movable only)",
		'PSTR',
		/* [14] */
		"",
		'KEYE',
		/* [15] */
		"0",
		'KEYB',
		/* [16] */
		"Reserved",
		'LB28',
		/* [17] */
		"Use theme controls",
		'LBIT',
		/* [18] */
		"Alert is movable",
		'LBIT',
		/* [19] */
		"Use control hierarchy",
		'LBIT',
		/* [20] */
		"Use theme background",
		'LBIT',
		/* [21] */
		"Reference constant",
		'DLNG',
		/* [22] */
		"Window type (Classic=0, Theme=1)",
		'BFLG',
		/* [23] */
		"Filler",
		'FBYT',
		/* [24] */
		"Filler",
		'FLNG',
		/* [25] */
		"Filler",
		'FLNG',
		/* [26] */
		"Filler",
		'FLNG',
		/* [27] */
		"Filler",
		'FLNG',
		/* [28] */
		"Window title (movable only)",
		'PSTR',
		/* [29] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1008, "ALTI") {
	{	/* array: 1 elements */
		/* [1] */
		"OS X Icon ID",
		'DWRD'
	}
};

resource 'TMPL' (1009, "APPL") {
	{	/* array: 5 elements */
		/* [1] */
		"Applications",
		'LSTB',
		/* [2] */
		"Creator",
		'TNAM',
		/* [3] */
		"Directory ID",
		'DLNG',
		/* [4] */
		"Application name",
		'ESTR',
		/* [5] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1010, "atms") {
	{	/* array: 56 elements */
		/* [1] */
		"Resource for the creation of parameter d"
		"escription atoms",
		'DVDR',
		/* [2] */
		"Root atom count",
		'DLNG',
		/* [3] */
		"List of atoms",
		'LSTB',
		/* [4] */
		"Atom type",
		'TNAM',
		/* [5] */
		"Atom ID",
		'DLNG',
		/* [6] */
		"Children",
		'DLNG',
		/* [7] */
		"No children=0",
		'CASE',
		/* [8] */
		"Count:",
		'LCNT',
		/* [9] */
		"Array atom data",
		'LSTC',
		/* [10] */
		"Data type",
		'KTYP',
		/* [11] */
		"long=long",
		'CASE',
		/* [12] */
		"short=shrt",
		'CASE',
		/* [13] */
		"noMininumFixed=nmiF",
		'CASE',
		/* [14] */
		"noMaximumFixed=nmaF",
		'CASE',
		/* [15] */
		"noMininumDouble=nmiD",
		'CASE',
		/* [16] */
		"noMaximumDouble=nmaD",
		'CASE',
		/* [17] */
		"fixed=fixd",
		'CASE',
		/* [18] */
		"double=doub",
		'CASE',
		/* [19] */
		"string=str ",
		'CASE',
		/* [20] */
		"lstring=lstr",
		'CASE',
		/* [21] */
		"OSType=osty",
		'CASE',
		/* [22] */
		"long",
		'KEYB',
		/* [23] */
		"Data",
		'PSTR',
		/* [24] */
		"",
		'KEYE',
		/* [25] */
		"shrt",
		'KEYB',
		/* [26] */
		"Data",
		'PSTR',
		/* [27] */
		"",
		'KEYE',
		/* [28] */
		"nmiF",
		'KEYB',
		/* [29] */
		"Data",
		'PSTR',
		/* [30] */
		"",
		'KEYE',
		/* [31] */
		"nmaF",
		'KEYB',
		/* [32] */
		"Data",
		'PSTR',
		/* [33] */
		"",
		'KEYE',
		/* [34] */
		"nmiD",
		'KEYB',
		/* [35] */
		"Data",
		'PSTR',
		/* [36] */
		"",
		'KEYE',
		/* [37] */
		"nmaD",
		'KEYB',
		/* [38] */
		"Data",
		'PSTR',
		/* [39] */
		"",
		'KEYE',
		/* [40] */
		"fixd",
		'KEYB',
		/* [41] */
		"Data",
		'PSTR',
		/* [42] */
		"",
		'KEYE',
		/* [43] */
		"doub",
		'KEYB',
		/* [44] */
		"Data",
		'PSTR',
		/* [45] */
		"",
		'KEYE',
		/* [46] */
		"str ",
		'KEYB',
		/* [47] */
		"Data",
		'PSTR',
		/* [48] */
		"",
		'KEYE',
		/* [49] */
		"lstr",
		'KEYB',
		/* [50] */
		"Hex data with initial size",
		'LSHX',
		/* [51] */
		"",
		'KEYE',
		/* [52] */
		"osty",
		'KEYB',
		/* [53] */
		"Data",
		'PSTR',
		/* [54] */
		"",
		'KEYE',
		/* [55] */
		"*****",
		'LSTE',
		/* [56] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1011, "audt") {
	{	/* array: 42 elements */
		/* [1] */
		"Event constants",
		'LSTB',
		/* [2] */
		"Selector",
		'TNAM',
		/* [3] */
		"Mac System Software=mssw",
		'CASE',
		/* [4] */
		"AppleShare=afps",
		'CASE',
		/* [5] */
		"FileShare=fshr",
		'CASE',
		/* [6] */
		"EtherTalk=etlk",
		'CASE',
		/* [7] */
		"Ether3Com=e3cm",
		'CASE',
		/* [8] */
		"EtherSmart=esmt",
		'CASE',
		/* [9] */
		"EtherLC=etlc",
		'CASE',
		/* [10] */
		"EtherSonic=etso",
		'CASE',
		/* [11] */
		"TokenTalk=ttlk",
		'CASE',
		/* [12] */
		"Mac Plus=plus",
		'CASE',
		/* [13] */
		"Mac SE=se  ",
		'CASE',
		/* [14] */
		"Mac SE/30=se30",
		'CASE',
		/* [15] */
		"Mac Portable=port",
		'CASE',
		/* [16] */
		"Mac II=ii  ",
		'CASE',
		/* [17] */
		"Mac IIx=iix ",
		'CASE',
		/* [18] */
		"Mac IIcx=iicx",
		'CASE',
		/* [19] */
		"Mac IIci=iici",
		'CASE',
		/* [20] */
		"Mac IIfx=iifx",
		'CASE',
		/* [21] */
		"Mac Classic=clas",
		'CASE',
		/* [22] */
		"Mac Portable=port",
		'CASE',
		/* [23] */
		"Mac PB 100=ashi",
		'CASE',
		/* [24] */
		"Mac Classic II=aplo",
		'CASE',
		/* [25] */
		"Mac LC=lc  ",
		'CASE',
		/* [26] */
		"Mac IIsi=iisi",
		'CASE',
		/* [27] */
		"Mac PB 140=timl",
		'CASE',
		/* [28] */
		"Mac PB 170=tim ",
		'CASE',
		/* [29] */
		"Mac Q700=spke",
		'CASE',
		/* [30] */
		"Mac Q900=eclp",
		'CASE',
		/* [31] */
		"Mac Q950=ecl3",
		'CASE',
		/* [32] */
		"Mac Q610=Q610",
		'CASE',
		/* [33] */
		"Mac Q650=Q650",
		'CASE',
		/* [34] */
		"Mac Q800=Q800",
		'CASE',
		/* [35] */
		"Mac C610=C610",
		'CASE',
		/* [36] */
		"Mac C650=C650",
		'CASE',
		/* [37] */
		"Power Mac (6100-7100-8100)=pdm ",
		'CASE',
		/* [38] */
		"Value",
		'DLNG',
		/* [39] */
		"Not installed=0",
		'CASE',
		/* [40] */
		"Minimal installation=1",
		'CASE',
		/* [41] */
		"Full installation=2",
		'CASE',
		/* [42] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1012, "avvc") {
	{	/* array: 3 elements */
		/* [1] */
		"Compressors AVI file four cc's",
		'LSTB',
		/* [2] */
		"AVI four cc type",
		'TNAM',
		/* [3] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1013, "avvd") {
	{	/* array: 3 elements */
		/* [1] */
		"Decompressors AVI file four cc's",
		'LSTB',
		/* [2] */
		"AVI four cc type",
		'TNAM',
		/* [3] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1014, "badg") {
	{	/* array: 17 elements */
		/* [1] */
		"Version",
		'KWRD',
		/* [2] */
		"Initial=0",
		'CASE',
		/* [3] */
		"0",
		'KEYB',
		/* [4] */
		"Custom badge resource ID",
		'DWRD',
		/* [5] */
		"Custom badge type",
		'TNAM',
		/* [6] */
		"none=0",
		'CASE',
		/* [7] */
		"Custom badge creator",
		'TNAM',
		/* [8] */
		"none=0",
		'CASE',
		/* [9] */
		"Window badge type",
		'TNAM',
		/* [10] */
		"none=0",
		'CASE',
		/* [11] */
		"Window badge creator",
		'TNAM',
		/* [12] */
		"none=0",
		'CASE',
		/* [13] */
		"Override type",
		'TNAM',
		/* [14] */
		"don't override=0",
		'CASE',
		/* [15] */
		"Override creator",
		'TNAM',
		/* [16] */
		"don't override=0",
		'CASE',
		/* [17] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1015, "bMRM") {
	{	/* array: 19 elements */
		/* [1] */
		"\"Fetch\" resource template",
		'DVDR',
		/* [2] */
		"Enter bMRM",
		'TNAM',
		/* [3] */
		"Enter $A9FF",
		'HWRD',
		/* [4] */
		"Version",
		'HWRD',
		/* [5] */
		"Menu ID",
		'DWRD',
		/* [6] */
		"Menu title",
		'ESTR',
		/* [7] */
		"Menu item number",
		'DWRD',
		/* [8] */
		"Menu item string",
		'ESTR',
		/* [9] */
		"Any files",
		'BBIT',
		/* [10] */
		"Any files created by this APPL",
		'BBIT',
		/* [11] */
		"Following files",
		'BBIT',
		/* [12] */
		"Following files created by this APPL",
		'BBIT',
		/* [13] */
		"Following files and files created by thi"
		"s APPL",
		'BBIT',
		/* [14] */
		"Unused",
		'BB03',
		/* [15] */
		"align",
		'AWRD',
		/* [16] */
		"Count:",
		'OCNT',
		/* [17] */
		"File Types",
		'LSTC',
		/* [18] */
		"File Type",
		'TNAM',
		/* [19] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1016, "BNDL") {
	{	/* array: 11 elements */
		/* [1] */
		"Signature",
		'TNAM',
		/* [2] */
		"Version ID",
		'RSID',
		/* [3] */
		"Count",
		'ZCNT',
		/* [4] */
		"List of types",
		'LSTC',
		/* [5] */
		"Type",
		'TNAM',
		/* [6] */
		"Count",
		'ZCNT',
		/* [7] */
		"List of mappings",
		'LSTC',
		/* [8] */
		"Local ID",
		'DWRD',
		/* [9] */
		"Actual ID",
		'RSID',
		/* [10] */
		"*****",
		'LSTE',
		/* [11] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1017, "brws") {
	{	/* array: 4 elements */
		/* [1] */
		"Version",
		'DLNG',
		/* [2] */
		"Flags",
		'DLNG',
		/* [3] */
		"Browser Mac OS creator code",
		'TNAM',
		/* [4] */
		"Name of plug-ins folder",
		'PSTR'
	}
};

resource 'TMPL' (1018, "bVal") {
	{	/* array: 2 elements */
		/* [1] */
		"\"AfterDark\" resource format",
		'DVDR',
		/* [2] */
		"Button Value - Decimal",
		'DWRD'
	}
};

resource 'TMPL' (1019, "Cals") {
	{	/* array: 8 elements */
		/* [1] */
		"\"AfterDark\" resource format",
		'DVDR',
		/* [2] */
		"Reserved",
		'BB02',
		/* [3] */
		"DoAbout",
		'BBIT',
		/* [4] */
		"DoSelected",
		'BBIT',
		/* [5] */
		"DoClose",
		'BBIT',
		/* [6] */
		"DoDrawFrame",
		'BBIT',
		/* [7] */
		"DoBlank",
		'BBIT',
		/* [8] */
		"DoInitialize",
		'BBIT'
	}
};

resource 'TMPL' (1020, "caps") {
	{	/* array: 139 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"List of Pairs",
		'LSTC',
		/* [3] */
		"Capability",
		'KTYP',
		/* [4] */
		"Abort=ABRT",
		'CASE',
		/* [5] */
		"AppleTalk based=ATLK",
		'CASE',
		/* [6] */
		"Break=BRK ",
		'CASE',
		/* [7] */
		"Channels=CHAN",
		'CASE',
		/* [8] */
		"Close=CLOS",
		'CASE',
		/* [9] */
		"End of Message=EOM ",
		'CASE',
		/* [10] */
		"Kill=KILL",
		'CASE',
		/* [11] */
		"Listen=LSTN",
		'CASE',
		/* [12] */
		"Low Level I/O=LLIO",
		'CASE',
		/* [13] */
		"Minimum memory=MEMM",
		'CASE',
		/* [14] */
		"Open=OPEN",
		'CASE',
		/* [15] */
		"Order=ORDR",
		'CASE',
		/* [16] */
		"Protocol=PROT",
		'CASE',
		/* [17] */
		"Read=READ",
		'CASE',
		/* [18] */
		"Recommended memory=MEMR",
		'CASE',
		/* [19] */
		"Reliability=RELY",
		'CASE',
		/* [20] */
		"Service=SERV",
		'CASE',
		/* [21] */
		"Timeout=TOUT",
		'CASE',
		/* [22] */
		"Write=WRIT",
		'CASE',
		/* [23] */
		"X-Terminal Interface=XTI ",
		'CASE',
		/* [24] */
		"ABRT",
		'KEYB',
		/* [25] */
		"Reserved",
		'LB31',
		/* [26] */
		"Supported",
		'LBIT',
		/* [27] */
		"",
		'KEYE',
		/* [28] */
		"ATLK",
		'KEYB',
		/* [29] */
		"Reserved",
		'LB31',
		/* [30] */
		"Supported",
		'LBIT',
		/* [31] */
		"",
		'KEYE',
		/* [32] */
		"BRK ",
		'KEYB',
		/* [33] */
		"How",
		'TNAM',
		/* [34] */
		"Synchronous only=SYNC",
		'CASE',
		/* [35] */
		"Asynchronous only=ASYN",
		'CASE',
		/* [36] */
		"Both=BOTH",
		'CASE',
		/* [37] */
		"Leave empty if not supported",
		'DVDR',
		/* [38] */
		"",
		'KEYE',
		/* [39] */
		"CHAN",
		'KEYB',
		/* [40] */
		"Reserved",
		'LB23',
		/* [41] */
		"Attention, clean",
		'LBIT',
		/* [42] */
		"Control, clean",
		'LBIT',
		/* [43] */
		"Data, clean",
		'LBIT',
		/* [44] */
		"Attention, no timeout",
		'LBIT',
		/* [45] */
		"Control, no timeout",
		'LBIT',
		/* [46] */
		"Data, no timeout",
		'LBIT',
		/* [47] */
		"Attention",
		'LBIT',
		/* [48] */
		"Control",
		'LBIT',
		/* [49] */
		"Data",
		'LBIT',
		/* [50] */
		"",
		'KEYE',
		/* [51] */
		"CLOS",
		'KEYB',
		/* [52] */
		"How",
		'TNAM',
		/* [53] */
		"Synchronous only=SYNC",
		'CASE',
		/* [54] */
		"Asynchronous only=ASYN",
		'CASE',
		/* [55] */
		"Both=BOTH",
		'CASE',
		/* [56] */
		"Leave empty if not supported",
		'DVDR',
		/* [57] */
		"",
		'KEYE',
		/* [58] */
		"EOM ",
		'KEYB',
		/* [59] */
		"Data",
		'HLNG',
		/* [60] */
		"",
		'KEYE',
		/* [61] */
		"KILL",
		'KEYB',
		/* [62] */
		"Reserved",
		'LB31',
		/* [63] */
		"Supported",
		'LBIT',
		/* [64] */
		"",
		'KEYE',
		/* [65] */
		"LSTN",
		'KEYB',
		/* [66] */
		"How",
		'TNAM',
		/* [67] */
		"Synchronous only=SYNC",
		'CASE',
		/* [68] */
		"Asynchronous only=ASYN",
		'CASE',
		/* [69] */
		"Both=BOTH",
		'CASE',
		/* [70] */
		"Leave empty if not supported",
		'DVDR',
		/* [71] */
		"",
		'KEYE',
		/* [72] */
		"LLIO",
		'KEYB',
		/* [73] */
		"Reserved",
		'LB31',
		/* [74] */
		"Supported",
		'LBIT',
		/* [75] */
		"",
		'KEYE',
		/* [76] */
		"MEMM",
		'KEYB',
		/* [77] */
		"Size",
		'HLNG',
		/* [78] */
		"",
		'KEYE',
		/* [79] */
		"OPEN",
		'KEYB',
		/* [80] */
		"How",
		'TNAM',
		/* [81] */
		"Synchronous only=SYNC",
		'CASE',
		/* [82] */
		"Asynchronous only=ASYN",
		'CASE',
		/* [83] */
		"Both=BOTH",
		'CASE',
		/* [84] */
		"Leave empty if not supported",
		'DVDR',
		/* [85] */
		"",
		'KEYE',
		/* [86] */
		"ORDR",
		'KEYB',
		/* [87] */
		"Reserved",
		'LB31',
		/* [88] */
		"Guaranteed",
		'LBIT',
		/* [89] */
		"",
		'KEYE',
		/* [90] */
		"PROT",
		'KEYB',
		/* [91] */
		"Type",
		'TNAM',
		/* [92] */
		"ISDN=ISDN",
		'CASE',
		/* [93] */
		"TCP=TCP ",
		'CASE',
		/* [94] */
		"ADSP=ADSP",
		'CASE',
		/* [95] */
		"NSP=NSP ",
		'CASE',
		/* [96] */
		"LAT=LAT ",
		'CASE',
		/* [97] */
		"NSPg=NSPg",
		'CASE',
		/* [98] */
		"LATg=LATg",
		'CASE',
		/* [99] */
		"Serial=SERD",
		'CASE',
		/* [100] */
		"Modem=MODM",
		'CASE',
		/* [101] */
		"MacPAD=PAD ",
		'CASE',
		/* [102] */
		"",
		'KEYE',
		/* [103] */
		"READ",
		'KEYB',
		/* [104] */
		"How",
		'TNAM',
		/* [105] */
		"Synchronous only=SYNC",
		'CASE',
		/* [106] */
		"Asynchronous only=ASYN",
		'CASE',
		/* [107] */
		"Both=BOTH",
		'CASE',
		/* [108] */
		"Leave empty if not supported",
		'DVDR',
		/* [109] */
		"",
		'KEYE',
		/* [110] */
		"MEMR",
		'KEYB',
		/* [111] */
		"Size",
		'HLNG',
		/* [112] */
		"",
		'KEYE',
		/* [113] */
		"RELY",
		'KEYB',
		/* [114] */
		"Reserved",
		'LB31',
		/* [115] */
		"Guaranteed",
		'LBIT',
		/* [116] */
		"",
		'KEYE',
		/* [117] */
		"SERV",
		'KEYB',
		/* [118] */
		"Type",
		'TNAM',
		/* [119] */
		"Datagram=DGRM",
		'CASE',
		/* [120] */
		"Stream=STRM",
		'CASE',
		/* [121] */
		"Record=REC ",
		'CASE',
		/* [122] */
		"Record or Stream=RECS",
		'CASE',
		/* [123] */
		"",
		'KEYE',
		/* [124] */
		"TOUT",
		'KEYB',
		/* [125] */
		"Reserved",
		'LB31',
		/* [126] */
		"Supported",
		'LBIT',
		/* [127] */
		"",
		'KEYE',
		/* [128] */
		"WRIT",
		'KEYB',
		/* [129] */
		"How",
		'TNAM',
		/* [130] */
		"Synchronous only=SYNC",
		'CASE',
		/* [131] */
		"Asynchronous only=ASYN",
		'CASE',
		/* [132] */
		"Both=BOTH",
		'CASE',
		/* [133] */
		"Leave empty if not supported",
		'DVDR',
		/* [134] */
		"",
		'KEYE',
		/* [135] */
		"XTI ",
		'KEYB',
		/* [136] */
		"How",
		'TNAM',
		/* [137] */
		"Leave empty if not supported",
		'DVDR',
		/* [138] */
		"",
		'KEYE',
		/* [139] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1021, "CATL") {
	{	/* array: 2 elements */
		/* [1] */
		"Alphabetic sort?",
		'BFLG',
		/* [2] */
		"Current page",
		'PSTR'
	}
};

resource 'TMPL' (1022, "cbnd") {
	{	/* array: 9 elements */
		/* [1] */
		"Count:",
		'ZCNT',
		/* [2] */
		"Types",
		'LSTC',
		/* [3] */
		"Type",
		'TNAM',
		/* [4] */
		"Count:",
		'ZCNT',
		/* [5] */
		"Mappings",
		'LSTC',
		/* [6] */
		"Local ID",
		'DWRD',
		/* [7] */
		"Actual ID",
		'DWRD',
		/* [8] */
		"*****",
		'LSTE',
		/* [9] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1023, "CCIª") {
	{	/* array: 1 elements */
		/* [1] */
		"Description",
		'CSTR'
	}
};

resource 'TMPL' (1024, "ccop") {
	{	/* array: 3 elements */
		/* [1] */
		"Codec compression options",
		'HLNG',
		/* [2] */
		"DefaultOptions=0x00000000",
		'CASE',
		/* [3] */
		"NoQuality=0x00000001",
		'CASE'
	}
};

resource 'TMPL' (1025, "cctb") {
	{	/* array: 22 elements */
		/* [1] */
		"Control color seed",
		'HLNG',
		/* [2] */
		"Flags",
		'HWRD',
		/* [3] */
		"Count:",
		'ZCNT',
		/* [4] */
		"List of Colors",
		'LSTC',
		/* [5] */
		"Part code",
		'DWRD',
		/* [6] */
		"Frame color=0",
		'CASE',
		/* [7] */
		"Body color=1",
		'CASE',
		/* [8] */
		"Text color=2",
		'CASE',
		/* [9] */
		"Thumb color=3",
		'CASE',
		/* [10] */
		"Fill pattern color (reserved)=4",
		'CASE',
		/* [11] */
		"Arrows & scroll bg light=5",
		'CASE',
		/* [12] */
		"Arrows & scroll bg dark=6",
		'CASE',
		/* [13] */
		"Thumb light=7",
		'CASE',
		/* [14] */
		"Thumb dark=8",
		'CASE',
		/* [15] */
		"Hilite light=9",
		'CASE',
		/* [16] */
		"Hilite dark=10",
		'CASE',
		/* [17] */
		"Title bar light=11",
		'CASE',
		/* [18] */
		"Title bar dark=12",
		'CASE',
		/* [19] */
		"Tinge light=13",
		'CASE',
		/* [20] */
		"Tinge dark=14",
		'CASE',
		/* [21] */
		"Color",
		'COLR',
		/* [22] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1026, "cdci") {
	{	/* array: 53 elements */
		/* [1] */
		"Description/name",
		'P020',
		/* [2] */
		"Version",
		'HWRD',
		/* [3] */
		"Revision level",
		'HWRD',
		/* [4] */
		"Vendor",
		'TNAM',
		/* [5] */
		"Apple Computer=appl",
		'CASE',
		/* [6] */
		"Decompression flags",
		'DVDR',
		/* [7] */
		"Reserved",
		'LB10',
		/* [8] */
		"Can recompress image without accumulatin"
		"g errors",
		'LBIT',
		/* [9] */
		"Can warp arbitrarily on decompress",
		'LBIT',
		/* [10] */
		"Can blend on decompress",
		'LBIT',
		/* [11] */
		"Can skew on decompress",
		'LBIT',
		/* [12] */
		"Can flip vertically on decompress",
		'LBIT',
		/* [13] */
		"Can flip horizontally on decompress",
		'LBIT',
		/* [14] */
		"Can rotate on decompress",
		'LBIT',
		/* [15] */
		"Can shrink to quarter size",
		'LBIT',
		/* [16] */
		"Can shrink to half size",
		'LBIT',
		/* [17] */
		"Can stretch to quadruple size exactly",
		'LBIT',
		/* [18] */
		"Can stretch to double size exactly",
		'LBIT',
		/* [19] */
		"Can handle temporal redundancy",
		'LBIT',
		/* [20] */
		"Can mask to clipping regions",
		'LBIT',
		/* [21] */
		"Can shrink to arbitrary size",
		'LBIT',
		/* [22] */
		"Can stretch to arbitrary size",
		'LBIT',
		/* [23] */
		"Can do dither mode",
		'LBIT',
		/* [24] */
		"Can work with 32-bit pixels",
		'LBIT',
		/* [25] */
		"Can work with 16-bit pixels",
		'LBIT',
		/* [26] */
		"Can work with 8-bit pixels",
		'LBIT',
		/* [27] */
		"Can work with 4-bit pixels",
		'LBIT',
		/* [28] */
		"Can work with 2-bit pixels",
		'LBIT',
		/* [29] */
		"Can work with 1-bit pixels",
		'LBIT',
		/* [30] */
		"Compression flags",
		'HLNG',
		/* [31] */
		"Format flags",
		'HLNG',
		/* [32] */
		"Compression accuracy",
		'UBYT',
		/* [33] */
		"Unknown=0",
		'CASE',
		/* [34] */
		"Lowest accuracy=1",
		'CASE',
		/* [35] */
		"Highest accuracy=255",
		'CASE',
		/* [36] */
		"Decompression accuracy",
		'UBYT',
		/* [37] */
		"Unknown=0",
		'CASE',
		/* [38] */
		"Lowest accuracy=1",
		'CASE',
		/* [39] */
		"Highest accuracy=255",
		'CASE',
		/* [40] */
		"Compression speed",
		'UWRD',
		/* [41] */
		"Unknown=0",
		'CASE',
		/* [42] */
		"Decompression speed",
		'UWRD',
		/* [43] */
		"Unknown=0",
		'CASE',
		/* [44] */
		"Compression level",
		'UBYT',
		/* [45] */
		"Unknown=0",
		'CASE',
		/* [46] */
		"No compression=1",
		'CASE',
		/* [47] */
		"100% compression=255",
		'CASE',
		/* [48] */
		"Reserved",
		'FBYT',
		/* [49] */
		"Minimum height (pixels)",
		'DWRD',
		/* [50] */
		"Minimum width",
		'DWRD',
		/* [51] */
		"Decompression pipeline latency",
		'DWRD',
		/* [52] */
		"Compression pipeline latency",
		'DWRD',
		/* [53] */
		"Private data",
		'DLNG'
	}
};

resource 'TMPL' (1027, "cFIG") {
	{	/* array: 29 elements */
		/* [1] */
		"Tool version",
		'DWRD',
		/* [2] */
		"Standard=4",
		'CASE',
		/* [3] */
		"Baud rate",
		'DLNG',
		/* [4] */
		"Data",
		'DWRD',
		/* [5] */
		"Stop",
		'DWRD',
		/* [6] */
		"Parity",
		'DWRD',
		/* [7] */
		"SWHS in",
		'HBYT',
		/* [8] */
		"HWHS in",
		'HBYT',
		/* [9] */
		"XON char",
		'HBYT',
		/* [10] */
		"XOFF char",
		'HBYT',
		/* [11] */
		"Error mask",
		'HBYT',
		/* [12] */
		"Event mask",
		'HBYT',
		/* [13] */
		"SWHS out",
		'HBYT',
		/* [14] */
		"HWHS out",
		'HBYT',
		/* [15] */
		"Portname",
		'P100',
		/* [16] */
		"Flags",
		'HWRD',
		/* [17] */
		"Phone #",
		'P100',
		/* [18] */
		"Rings",
		'DWRD',
		/* [19] */
		"Dial mode",
		'DWRD',
		/* [20] */
		"Carrier",
		'DWRD',
		/* [21] */
		"Config mode",
		'HBYT',
		/* [22] */
		"Retry",
		'HBYT',
		/* [23] */
		"Retry limit",
		'DWRD',
		/* [24] */
		"Retry interval",
		'DWRD',
		/* [25] */
		"Modem flags",
		'HWRD',
		/* [26] */
		"Init string",
		'P100',
		/* [27] */
		"Actual speed",
		'DLNG',
		/* [28] */
		"Ring string",
		'P100',
		/* [29] */
		"Make string",
		'P100'
	}
};

resource 'TMPL' (1028, "cfmt") {
	{	/* array: 12 elements */
		/* [1] */
		"Column1 width",
		'DWRD',
		/* [2] */
		"Column2 width",
		'DWRD',
		/* [3] */
		"Column3 width",
		'DWRD',
		/* [4] */
		"Column4 width",
		'DWRD',
		/* [5] */
		"Column5 width",
		'DWRD',
		/* [6] */
		"Column6 width",
		'DWRD',
		/* [7] */
		"Column1 & 2 gap",
		'DWRD',
		/* [8] */
		"Column2 & 3 gap",
		'DWRD',
		/* [9] */
		"Column3 & 4 gap",
		'DWRD',
		/* [10] */
		"Column4 & 5 gap",
		'DWRD',
		/* [11] */
		"Column5 & 6 gap",
		'DWRD',
		/* [12] */
		"Column6 & 7 gap",
		'DWRD'
	}
};

resource 'TMPL' (1029, "cfrg") {
	{	/* array: 26 elements */
		/* [1] */
		"(private)",
		'HLNG',
		/* [2] */
		"(private)",
		'HLNG',
		/* [3] */
		"cfrg Version",
		'HLNG',
		/* [4] */
		"(private)",
		'HLNG',
		/* [5] */
		"(private)",
		'HLNG',
		/* [6] */
		"(unused)",
		'HLNG',
		/* [7] */
		"(unused)",
		'HLNG',
		/* [8] */
		"Member Count",
		'DLNG',
		/* [9] */
		"List of members",
		'LSTB',
		/* [10] */
		"alignment",
		'ALNG',
		/* [11] */
		"Architecture",
		'TNAM',
		/* [12] */
		"Update level",
		'DLNG',
		/* [13] */
		"Current version",
		'HLNG',
		/* [14] */
		"Old Def version",
		'HLNG',
		/* [15] */
		"App Stack",
		'DLNG',
		/* [16] */
		"App SubDir",
		'DWRD',
		/* [17] */
		"Usage",
		'DBYT',
		/* [18] */
		"Where",
		'DBYT',
		/* [19] */
		"Offset",
		'DLNG',
		/* [20] */
		"Length",
		'DLNG',
		/* [21] */
		"(unused)",
		'HLNG',
		/* [22] */
		"(unused)",
		'HLNG',
		/* [23] */
		"Member size",
		'DWRD',
		/* [24] */
		"Member name",
		'PSTR',
		/* [25] */
		"alignment",
		'ALNG',
		/* [26] */
		"member",
		'LSTE'
	}
};

resource 'TMPL' (1030, "chCd") {
	{	/* array: 5 elements */
		/* [1] */
		"\"Finale\" resource format",
		'DVDR',
		/* [2] */
		"Count:",
		'OCNT',
		/* [3] */
		"Character codes array",
		'LSTC',
		/* [4] */
		"Code",
		'HWRD',
		/* [5] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1031, "chCv") {
	{	/* array: 3 elements */
		/* [1] */
		"\"Finale\" resource format",
		'DVDR',
		/* [2] */
		"Original characters",
		'CSTR',
		/* [3] */
		"Converted characters",
		'CSTR'
	}
};

resource 'TMPL' (1032, "Chnl") {
	{	/* array: 3 elements */
		/* [1] */
		"\"AfterDark\" resource format",
		'DVDR',
		/* [2] */
		"Sound Channel Type",
		'DWRD',
		/* [3] */
		"Sound Volume Level (0-7)",
		'DWRD'
	}
};

resource 'TMPL' (1033, "CHOS") {
	{	/* array: 5 elements */
		/* [1] */
		"Serial device",
		'DWRD',
		/* [2] */
		"Number of reserved rows",
		'DWRD',
		/* [3] */
		"Rows",
		'LSTB',
		/* [4] */
		"Reserved row name",
		'P020',
		/* [5] */
		"****",
		'LSTE'
	}
};

resource 'TMPL' (1034, "chrw") {
	{	/* array: 1 elements */
		/* [1] */
		"Number of characters per 50 pixels",
		'DWRD'
	}
};

resource 'TMPL' (1035, "ckid") {
	{	/* array: 27 elements */
		/* [1] */
		"Checksum",
		'ULNG',
		/* [2] */
		"Location",
		'ULNG',
		/* [3] */
		"Current version",
		'UWRD',
		/* [4] */
		"Checked out by someone",
		'WFLG',
		/* [5] */
		"Branch",
		'UBYT',
		/* [6] */
		"Modify read-only",
		'BFLG',
		/* [7] */
		"History",
		'DWRD',
		/* [8] */
		"History length",
		'DWRD',
		/* [9] */
		"Checkout time",
		'DATE',
		/* [10] */
		"File's modification date",
		'MDAT',
		/* [11] */
		"Project ID1",
		'ULNG',
		/* [12] */
		"Project ID2",
		'ULNG',
		/* [13] */
		"User ID",
		'UWRD',
		/* [14] */
		"File ID",
		'UWRD',
		/* [15] */
		"Revision ID",
		'UWRD',
		/* [16] */
		"RemotePath string",
		'PSTR',
		/* [17] */
		"Filler byte",
		'FBYT',
		/* [18] */
		"UserName string",
		'PSTR',
		/* [19] */
		"Filler byte",
		'FBYT',
		/* [20] */
		"Revision string",
		'PSTR',
		/* [21] */
		"Filler byte",
		'FBYT',
		/* [22] */
		"Filename string",
		'PSTR',
		/* [23] */
		"Filler byte",
		'FBYT',
		/* [24] */
		"Task string",
		'PSTR',
		/* [25] */
		"Filler byte",
		'FBYT',
		/* [26] */
		"Comment data",
		'WSTR',
		/* [27] */
		"Filler byte",
		'FBYT'
	}
};

resource 'TMPL' (1036, "Clmn") {
	{	/* array: 35 elements */
		/* [1] */
		"\"SuitCase\" resource format",
		'DVDR',
		/* [2] */
		"Column Count:",
		'LCNT',
		/* [3] */
		"Columns",
		'LSTC',
		/* [4] */
		"Name",
		'P020',
		/* [5] */
		"Kind",
		'TNAM',
		/* [6] */
		"kInvalidKind =Invl",
		'CASE',
		/* [7] */
		"kIconAndNameKind =IcnN",
		'CASE',
		/* [8] */
		"kIconKind =Icon",
		'CASE',
		/* [9] */
		"kNameKind =Name",
		'CASE',
		/* [10] */
		"kSizeKind =Size",
		'CASE',
		/* [11] */
		"kKindKind =Kind",
		'CASE',
		/* [12] */
		"kCreationDateKind =CDat",
		'CASE',
		/* [13] */
		"kModifiedDateKind =MDat",
		'CASE',
		/* [14] */
		"kVersionKind =Vers",
		'CASE',
		/* [15] */
		"kWhereKind =Wher",
		'CASE',
		/* [16] */
		"kCompressionStateKind =Comp",
		'CASE',
		/* [17] */
		"Data Type",
		'TNAM',
		/* [18] */
		"kInvalidDataType =Invl",
		'CASE',
		/* [19] */
		"kIconAndNameDataType =IcnN",
		'CASE',
		/* [20] */
		"kTextDataType =Text",
		'CASE',
		/* [21] */
		"kIconSuiteDataType =ics8",
		'CASE',
		/* [22] */
		"kBooleanDataType =Bool",
		'CASE',
		/* [23] */
		"kLongWordDataType =Long",
		'CASE',
		/* [24] */
		"Min Width",
		'ULNG',
		/* [25] */
		"Preferred Width",
		'ULNG',
		/* [26] */
		"Justification",
		'ULNG',
		/* [27] */
		"kColumnJustLeft =0",
		'CASE',
		/* [28] */
		"kColumnJustRight =1",
		'CASE',
		/* [29] */
		"kColumnJustCenter =2",
		'CASE',
		/* [30] */
		"Reserved",
		'BB08',
		/* [31] */
		"Reserved",
		'BB05',
		/* [32] */
		"Ellipsize at End",
		'BB01',
		/* [33] */
		"Ignore clicks",
		'BB01',
		/* [34] */
		"Uses hiliting",
		'BB01',
		/* [35] */
		"",
		'LSTE'
	}
};

resource 'TMPL' (1037, "clr#") {
	{	/* array: 5 elements */
		/* [1] */
		"Appearance Color List Resource (ID 384)",
		'DVDR',
		/* [2] */
		"Count:",
		'LCNT',
		/* [3] */
		"Colors list",
		'LSTC',
		/* [4] */
		"Color",
		'COLR',
		/* [5] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1038, "CLSS") {
	{	/* array: 39 elements */
		/* [1] */
		"Class ID",
		'TNAM',
		/* [2] */
		"Parent class ID",
		'TNAM',
		/* [3] */
		"Class data size",
		'DLNG',
		/* [4] */
		"Base class data size",
		'DLNG',
		/* [5] */
		"Count:",
		'OCNT',
		/* [6] */
		"Number of Fields",
		'LSTC',
		/* [7] */
		"Field Name",
		'ESTR',
		/* [8] */
		"Data type",
		'KWRD',
		/* [9] */
		"Boolean=0",
		'CASE',
		/* [10] */
		"Byte=1",
		'CASE',
		/* [11] */
		"Char=2",
		'CASE',
		/* [12] */
		"ID Type=3",
		'CASE',
		/* [13] */
		"Int16=4",
		'CASE',
		/* [14] */
		"Int32=5",
		'CASE',
		/* [15] */
		"Pascal string=6",
		'CASE',
		/* [16] */
		"0",
		'KEYB',
		/* [17] */
		"Default value",
		'BOOL',
		/* [18] */
		"",
		'KEYE',
		/* [19] */
		"1",
		'KEYB',
		/* [20] */
		"Default value",
		'DBYT',
		/* [21] */
		"Filler",
		'FBYT',
		/* [22] */
		"",
		'KEYE',
		/* [23] */
		"2",
		'KEYB',
		/* [24] */
		"Default value",
		'CHAR',
		/* [25] */
		"Filler",
		'FBYT',
		/* [26] */
		"",
		'KEYE',
		/* [27] */
		"3",
		'KEYB',
		/* [28] */
		"Default value",
		'TNAM',
		/* [29] */
		"",
		'KEYE',
		/* [30] */
		"4",
		'KEYB',
		/* [31] */
		"Default value",
		'DWRD',
		/* [32] */
		"",
		'KEYE',
		/* [33] */
		"5",
		'KEYB',
		/* [34] */
		"Default value",
		'DLNG',
		/* [35] */
		"",
		'KEYE',
		/* [36] */
		"6",
		'KEYB',
		/* [37] */
		"Default value",
		'ESTR',
		/* [38] */
		"",
		'KEYE',
		/* [39] */
		"",
		'LSTE'
	}
};

resource 'TMPL' (1039, "cltn") {
	{	/* array: 14 elements */
		/* [1] */
		"Count:",
		'LCNT',
		/* [2] */
		"List of Items",
		'LSTC',
		/* [3] */
		"Tag",
		'TNAM',
		/* [4] */
		"ID",
		'DLNG',
		/* [5] */
		"Printing collection=-28672",
		'CASE',
		/* [6] */
		"Defined attribute bits",
		'DVDR',
		/* [7] */
		"Locked?",
		'WBIT',
		/* [8] */
		"Persistent?",
		'WBIT',
		/* [9] */
		"Reserved",
		'WB14',
		/* [10] */
		"User attribute bits",
		'DVDR',
		/* [11] */
		"Reserved",
		'WB16',
		/* [12] */
		"Text",
		'WSTR',
		/* [13] */
		"Align",
		'AWRD',
		/* [14] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1040, "clut") {
	{	/* array: 9 elements */
		/* [1] */
		"Color table seed",
		'HLNG',
		/* [2] */
		"Ignore values and index ",
		'WB01',
		/* [3] */
		"Use values as palette indices",
		'WB01',
		/* [4] */
		"Reserved",
		'WB14',
		/* [5] */
		"Count:",
		'ZCNT',
		/* [6] */
		"Color table sizes",
		'LSTC',
		/* [7] */
		"Pixel value",
		'DWRD',
		/* [8] */
		"Color",
		'COLR',
		/* [9] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1041, "CMDK") {
	{	/* array: 1 elements */
		/* [1] */
		"Command Keys",
		'PSTR'
	}
};

resource 'TMPL' (1042, "cmdo") {
	{	/* array: 315 elements */
		/* [1] */
		"Commando version",
		'DWRD',
		/* [2] */
		"Latest=8",
		'CASE',
		/* [3] */
		"Count:",
		'OCNT',
		/* [4] */
		"List of Dialogs",
		'LSTC',
		/* [5] */
		"Height of dialog",
		'DWRD',
		/* [6] */
		"Help window text",
		'CSTR',
		/* [7] */
		"Align",
		'AWRD',
		/* [8] */
		"Count:",
		'OCNT',
		/* [9] */
		"List of Items",
		'LSTC',
		/* [10] */
		"Option type",
		'KBYT',
		/* [11] */
		"Not dependent=0",
		'CASE',
		/* [12] */
		"Or=1",
		'CASE',
		/* [13] */
		"And=2",
		'CASE',
		/* [14] */
		"0",
		'KEYB',
		/* [15] */
		"Filler",
		'FBYT',
		/* [16] */
		"",
		'KEYE',
		/* [17] */
		"1",
		'KEYB',
		/* [18] */
		"Count:",
		'BCNT',
		/* [19] */
		"List of OR items",
		'LSTC',
		/* [20] */
		"Item number",
		'DWRD',
		/* [21] */
		"*****",
		'LSTE',
		/* [22] */
		"",
		'KEYE',
		/* [23] */
		"2",
		'KEYB',
		/* [24] */
		"Count:",
		'BCNT',
		/* [25] */
		"List of AND items",
		'LSTC',
		/* [26] */
		"Item number",
		'DWRD',
		/* [27] */
		"*****",
		'LSTE',
		/* [28] */
		"",
		'KEYE',
		/* [29] */
		"Item type",
		'KBYT',
		/* [30] */
		"File's ID=0",
		'CASE',
		/* [31] */
		"Multiple files=1",
		'CASE',
		/* [32] */
		"Check option=2",
		'CASE',
		/* [33] */
		"Radio buttons=3",
		'CASE',
		/* [34] */
		"Regular entry=4",
		'CASE',
		/* [35] */
		"Scrollable option list=5",
		'CASE',
		/* [36] */
		"Box or line=6",
		'CASE',
		/* [37] */
		"Text box=7",
		'CASE',
		/* [38] */
		"Popup menu=8",
		'CASE',
		/* [39] */
		"Nested dialog=9",
		'CASE',
		/* [40] */
		"Text title=10",
		'CASE',
		/* [41] */
		"Redirection=11",
		'CASE',
		/* [42] */
		"Edit popup=12",
		'CASE',
		/* [43] */
		"Tristate buttons=13",
		'CASE',
		/* [44] */
		"List=14",
		'CASE',
		/* [45] */
		"Picture or icon=15",
		'CASE',
		/* [46] */
		"Dummy=16",
		'CASE',
		/* [47] */
		"Do It button=17",
		'CASE',
		/* [48] */
		"Version dialog=18",
		'CASE',
		/* [49] */
		"0",
		'KEYB',
		/* [50] */
		"File kind",
		'DBYT',
		/* [51] */
		"Input file=0",
		'CASE',
		/* [52] */
		"Input file or directory=1",
		'CASE',
		/* [53] */
		"Input or output file=2",
		'CASE',
		/* [54] */
		"Input or output or directory=3",
		'CASE',
		/* [55] */
		"Output file=4",
		'CASE',
		/* [56] */
		"Output file or directory=5",
		'CASE',
		/* [57] */
		"Directory only=6",
		'CASE',
		/* [58] */
		"File type",
		'KWRD',
		/* [59] */
		"Optional file=0",
		'CASE',
		/* [60] */
		"Required file=1",
		'CASE',
		/* [61] */
		"0",
		'KEYB',
		/* [62] */
		"Title bounds",
		'RECT',
		/* [63] */
		"Display bounds",
		'RECT',
		/* [64] */
		"File title",
		'CSTR',
		/* [65] */
		"Default file name",
		'CSTR',
		/* [66] */
		"Option to return before file",
		'CSTR',
		/* [67] */
		"Extension",
		'CSTR',
		/* [68] */
		"Popup help text",
		'CSTR',
		/* [69] */
		"Reserved",
		'BB07',
		/* [70] */
		"Don't dim this item",
		'BB01',
		/* [71] */
		"Popup item #1",
		'CSTR',
		/* [72] */
		"Popup item #2",
		'CSTR',
		/* [73] */
		"Popup item #3",
		'CSTR',
		/* [74] */
		"",
		'KEYE',
		/* [75] */
		"1",
		'KEYB',
		/* [76] */
		"Button bounds",
		'RECT',
		/* [77] */
		"Button title",
		'CSTR',
		/* [78] */
		"Option to return before file",
		'CSTR',
		/* [79] */
		"Button's help text",
		'CSTR',
		/* [80] */
		"",
		'KEYE',
		/* [81] */
		"Additional file information",
		'KBYT',
		/* [82] */
		"No more file info=1",
		'CASE',
		/* [83] */
		"Additional file info=0",
		'CASE',
		/* [84] */
		"1",
		'KEYB',
		/* [85] */
		"",
		'KEYE',
		/* [86] */
		"0",
		'KEYB',
		/* [87] */
		"Option when new file chosen",
		'CSTR',
		/* [88] */
		"Preferred file extension",
		'CSTR',
		/* [89] */
		"No radio buttons=",
		'CASE',
		/* [90] */
		"Filter types=:",
		'CASE',
		/* [91] */
		"Title of Only Files button",
		'CSTR',
		/* [92] */
		"Title of All Files button",
		'CSTR',
		/* [93] */
		"Mac file types",
		'BCNT',
		/* [94] */
		"Align",
		'AWRD',
		/* [95] */
		"¬\"¬\"¬\"¬\"¬\"",
		'LSTC',
		/* [96] */
		"Desired input file type",
		'TNAM',
		/* [97] */
		"All types=$00000000",
		'CASE',
		/* [98] */
		"Text file=TEXT",
		'CASE',
		/* [99] */
		"Object file=OBJ ",
		'CASE',
		/* [100] */
		"Application=APPL",
		'CASE',
		/* [101] */
		"Desk Accessory=DFIL",
		'CASE',
		/* [102] */
		"MPW Tool=MPST",
		'CASE',
		/* [103] */
		"*****",
		'LSTE',
		/* [104] */
		"",
		'KEYE',
		/* [105] */
		"",
		'KEYE',
		/* [106] */
		"1",
		'KEYB',
		/* [107] */
		"Button title",
		'CSTR',
		/* [108] */
		"Button's help text",
		'CSTR',
		/* [109] */
		"Align",
		'AWRD',
		/* [110] */
		"Button bounds",
		'RECT',
		/* [111] */
		"Message",
		'CSTR',
		/* [112] */
		"Option returned before each file",
		'CSTR',
		/* [113] */
		"Multiple files item",
		'KBYT',
		/* [114] */
		"Multiple input files=0",
		'CASE',
		/* [115] */
		"Multiple directories=1",
		'CASE',
		/* [116] */
		"Multiple input files and directories=2",
		'CASE',
		/* [117] */
		"Multiple output files=3",
		'CASE',
		/* [118] */
		"0",
		'KEYB',
		/* [119] */
		"File types",
		'BCNT',
		/* [120] */
		"Align",
		'AWRD',
		/* [121] */
		"¬\"¬\"¬\"¬\"¬\"",
		'LSTC',
		/* [122] */
		"Mac file type",
		'TNAM',
		/* [123] */
		"All types=$00000000",
		'CASE',
		/* [124] */
		"Text file=TEXT",
		'CASE',
		/* [125] */
		"Object file=OBJ ",
		'CASE',
		/* [126] */
		"Application=APPL",
		'CASE',
		/* [127] */
		"Desk Accessory=DFIL",
		'CASE',
		/* [128] */
		"MPW Tool=MPST",
		'CASE',
		/* [129] */
		"*****",
		'LSTE',
		/* [130] */
		"Preferred file extension",
		'CSTR',
		/* [131] */
		"No radio buttons=",
		'CASE',
		/* [132] */
		"Filter types=:",
		'CASE',
		/* [133] */
		"Title of Only Files button",
		'CSTR',
		/* [134] */
		"Title of All Files button",
		'CSTR',
		/* [135] */
		"",
		'KEYE',
		/* [136] */
		"1",
		'KEYB',
		/* [137] */
		"",
		'KEYE',
		/* [138] */
		"2",
		'KEYB',
		/* [139] */
		"",
		'KEYE',
		/* [140] */
		"3",
		'KEYB',
		/* [141] */
		"",
		'KEYE',
		/* [142] */
		"",
		'KEYE',
		/* [143] */
		"2",
		'KEYB',
		/* [144] */
		"Button set",
		'DBYT',
		/* [145] */
		"Not set=0",
		'CASE',
		/* [146] */
		"Set=1",
		'CASE',
		/* [147] */
		"Bounds",
		'RECT',
		/* [148] */
		"Title",
		'CSTR',
		/* [149] */
		"Option returned",
		'CSTR',
		/* [150] */
		"Button help text",
		'CSTR',
		/* [151] */
		"",
		'KEYE',
		/* [152] */
		"3",
		'KEYB',
		/* [153] */
		"Count:",
		'BCNT',
		/* [154] */
		"List of Radio buttons",
		'LSTC',
		/* [155] */
		"Bounds",
		'RECT',
		/* [156] */
		"Title",
		'CSTR',
		/* [157] */
		"Option returned",
		'CSTR',
		/* [158] */
		"Button set",
		'DBYT',
		/* [159] */
		"Not set=0",
		'CASE',
		/* [160] */
		"Set=1",
		'CASE',
		/* [161] */
		"Radio button help text",
		'CSTR',
		/* [162] */
		"Align",
		'AWRD',
		/* [163] */
		"*****",
		'LSTE',
		/* [164] */
		"",
		'KEYE',
		/* [165] */
		"4",
		'KEYB',
		/* [166] */
		"Title",
		'CSTR',
		/* [167] */
		"Align",
		'AWRD',
		/* [168] */
		"Title bounds",
		'RECT',
		/* [169] */
		"Input box bounds",
		'RECT',
		/* [170] */
		"Default value",
		'CSTR',
		/* [171] */
		"Type of case",
		'DBYT',
		/* [172] */
		"Ignore case=0",
		'CASE',
		/* [173] */
		"Keep case=1",
		'CASE',
		/* [174] */
		"Option returned",
		'CSTR',
		/* [175] */
		"Entry help text",
		'CSTR',
		/* [176] */
		"",
		'KEYE',
		/* [177] */
		"5",
		'KEYB',
		/* [178] */
		"Title",
		'CSTR',
		/* [179] */
		"Align",
		'AWRD',
		/* [180] */
		"Title bounds",
		'RECT',
		/* [181] */
		"Input list bounds",
		'RECT',
		/* [182] */
		"Count:",
		'BCNT',
		/* [183] */
		"List of Entries",
		'LSTC',
		/* [184] */
		"Default values",
		'CSTR',
		/* [185] */
		"*****",
		'LSTE',
		/* [186] */
		"Option returned",
		'CSTR',
		/* [187] */
		"Entry help text",
		'CSTR',
		/* [188] */
		"",
		'KEYE',
		/* [189] */
		"6",
		'KEYB',
		/* [190] */
		"Color",
		'DBYT',
		/* [191] */
		"Black=0",
		'CASE',
		/* [192] */
		"Gray=1",
		'CASE',
		/* [193] */
		"Bounds of box or line",
		'RECT',
		/* [194] */
		"",
		'KEYE',
		/* [195] */
		"7",
		'KEYB',
		/* [196] */
		"Color",
		'DBYT',
		/* [197] */
		"Black=0",
		'CASE',
		/* [198] */
		"Gray=1",
		'CASE',
		/* [199] */
		"Bounds of box or line",
		'RECT',
		/* [200] */
		"Text to display",
		'CSTR',
		/* [201] */
		"",
		'KEYE',
		/* [202] */
		"8",
		'KEYB',
		/* [203] */
		"Type of popup",
		'DBYT',
		/* [204] */
		"Window=0",
		'CASE',
		/* [205] */
		"Alias=1",
		'CASE',
		/* [206] */
		"Font=2",
		'CASE',
		/* [207] */
		"Set=3",
		'CASE',
		/* [208] */
		"Bounds of popup line",
		'RECT',
		/* [209] */
		"Popup title",
		'CSTR',
		/* [210] */
		"Option to return",
		'CSTR',
		/* [211] */
		"Help text for text edit part",
		'CSTR',
		/* [212] */
		"Help text for popup part",
		'CSTR',
		/* [213] */
		"",
		'KEYE',
		/* [214] */
		"9",
		'KEYB',
		/* [215] */
		"Which dialog",
		'DBYT',
		/* [216] */
		"Button bounds",
		'RECT',
		/* [217] */
		"Button title",
		'CSTR',
		/* [218] */
		"Button's help text",
		'CSTR',
		/* [219] */
		"",
		'KEYE',
		/* [220] */
		"10",
		'KEYB',
		/* [221] */
		"Style of text title",
		'BORV',
		/* [222] */
		"Plain=0",
		'CASE',
		/* [223] */
		"Bold=1",
		'CASE',
		/* [224] */
		"Italic=2",
		'CASE',
		/* [225] */
		"Underline=4",
		'CASE',
		/* [226] */
		"Outline=8",
		'CASE',
		/* [227] */
		"Shadow=16",
		'CASE',
		/* [228] */
		"Condensed=32",
		'CASE',
		/* [229] */
		"Extended=64",
		'CASE',
		/* [230] */
		"Bounds of title",
		'RECT',
		/* [231] */
		"Font number to use",
		'DWRD',
		/* [232] */
		"System font=0",
		'CASE',
		/* [233] */
		"Font size to use",
		'DWRD',
		/* [234] */
		"System font size=0",
		'CASE',
		/* [235] */
		"Text to display",
		'CSTR',
		/* [236] */
		"",
		'KEYE',
		/* [237] */
		"11",
		'KEYB',
		/* [238] */
		"Type of redirection",
		'DBYT',
		/* [239] */
		"Standard output=0",
		'CASE',
		/* [240] */
		"Diagnostic output=1",
		'CASE',
		/* [241] */
		"Standard input=2",
		'CASE',
		/* [242] */
		"Upper left point",
		'PNT ',
		/* [243] */
		"",
		'KEYE',
		/* [244] */
		"12",
		'KEYB',
		/* [245] */
		"Type of editable popup",
		'DBYT',
		/* [246] */
		"Menu title=0",
		'CASE',
		/* [247] */
		"Menu item=1",
		'CASE',
		/* [248] */
		"Font size=2",
		'CASE',
		/* [249] */
		"Alias=3",
		'CASE',
		/* [250] */
		"Set=4",
		'CASE',
		/* [251] */
		"Title bounds",
		'RECT',
		/* [252] */
		"Bounds of text edit area",
		'RECT',
		/* [253] */
		"Popup title",
		'CSTR',
		/* [254] */
		"Option to return",
		'CSTR',
		/* [255] */
		"Help text for text edit part",
		'CSTR',
		/* [256] */
		"Help text for popup part",
		'CSTR',
		/* [257] */
		"",
		'KEYE',
		/* [258] */
		"13",
		'KEYB',
		/* [259] */
		"Count:",
		'BCNT',
		/* [260] */
		"Option returned",
		'CSTR',
		/* [261] */
		"Align",
		'AWRD',
		/* [262] */
		"List of buttons",
		'LSTC',
		/* [263] */
		"Button bounds",
		'RECT',
		/* [264] */
		"Title",
		'CSTR',
		/* [265] */
		"Text for Clear state",
		'CSTR',
		/* [266] */
		"Text for Don't Touch state",
		'CSTR',
		/* [267] */
		"Text for Set state",
		'CSTR',
		/* [268] */
		"Button help text",
		'CSTR',
		/* [269] */
		"*****",
		'LSTE',
		/* [270] */
		"",
		'KEYE',
		/* [271] */
		"14",
		'KEYB',
		/* [272] */
		"What to display in list",
		'DBYT',
		/* [273] */
		"Volumes=0",
		'CASE',
		/* [274] */
		"Shell variables=1",
		'CASE',
		/* [275] */
		"Windows=2",
		'CASE',
		/* [276] */
		"Aliases=3",
		'CASE',
		/* [277] */
		"Option returned before each file",
		'CSTR',
		/* [278] */
		"List title",
		'CSTR',
		/* [279] */
		"Align",
		'AWRD',
		/* [280] */
		"Bounds of title",
		'RECT',
		/* [281] */
		"Bounds of list selection box",
		'RECT',
		/* [282] */
		"Selection box help text",
		'CSTR',
		/* [283] */
		"",
		'KEYE',
		/* [284] */
		"15",
		'KEYB',
		/* [285] */
		"Type of graphic",
		'DBYT',
		/* [286] */
		"'ICON'=0",
		'CASE',
		/* [287] */
		"'PICT'=1",
		'CASE',
		/* [288] */
		"Resource ID",
		'DWRD',
		/* [289] */
		"Display bounds",
		'RECT',
		/* [290] */
		"",
		'KEYE',
		/* [291] */
		"16",
		'KEYB',
		/* [292] */
		"",
		'KEYE',
		/* [293] */
		"17",
		'KEYB',
		/* [294] */
		"",
		'KEYE',
		/* [295] */
		"18",
		'KEYB',
		/* [296] */
		"Version info",
		'KBYT',
		/* [297] */
		"Use this string=0",
		'CASE',
		/* [298] */
		"In resource=1",
		'CASE',
		/* [299] */
		"0",
		'KEYB',
		/* [300] */
		"Tool version",
		'CSTR',
		/* [301] */
		"",
		'KEYE',
		/* [302] */
		"1",
		'KEYB',
		/* [303] */
		"Resource type of Pascal version string",
		'TNAM',
		/* [304] */
		"Resource ID",
		'RSID',
		/* [305] */
		"",
		'KEYE',
		/* [306] */
		"Version text for help window",
		'CSTR',
		/* [307] */
		"Align",
		'AWRD',
		/* [308] */
		"Dialog ('DLOG') resource ID",
		'RSID',
		/* [309] */
		"No dialog=0",
		'CASE',
		/* [310] */
		"",
		'KEYE',
		/* [311] */
		"Align",
		'AWRD',
		/* [312] */
		"*****",
		'LSTE',
		/* [313] */
		"Align",
		'AWRD',
		/* [314] */
		"*****",
		'LSTE',
		/* [315] */
		"Align",
		'AWRD'
	}
};

resource 'TMPL' (1043, "cmnu") {
	{	/* array: 72 elements */
		/* [1] */
		"Menu ID",
		'DWRD',
		/* [2] */
		"Width",
		'FWRD',
		/* [3] */
		"Height",
		'FWRD',
		/* [4] */
		"Proc ID (MDEF)",
		'RSID',
		/* [5] */
		"Filler",
		'FWRD',
		/* [6] */
		"Enable flags",
		'DVDR',
		/* [7] */
		"Enabled",
		'LBIT',
		/* [8] */
		"Enabled",
		'LBIT',
		/* [9] */
		"Enabled",
		'LBIT',
		/* [10] */
		"Enabled",
		'LBIT',
		/* [11] */
		"Enabled",
		'LBIT',
		/* [12] */
		"Enabled",
		'LBIT',
		/* [13] */
		"Enabled",
		'LBIT',
		/* [14] */
		"Enabled",
		'LBIT',
		/* [15] */
		"Enabled",
		'LBIT',
		/* [16] */
		"Enabled",
		'LBIT',
		/* [17] */
		"Enabled",
		'LBIT',
		/* [18] */
		"Enabled",
		'LBIT',
		/* [19] */
		"Enabled",
		'LBIT',
		/* [20] */
		"Enabled",
		'LBIT',
		/* [21] */
		"Enabled",
		'LBIT',
		/* [22] */
		"Enabled",
		'LBIT',
		/* [23] */
		"Enabled",
		'LBIT',
		/* [24] */
		"Enabled",
		'LBIT',
		/* [25] */
		"Enabled",
		'LBIT',
		/* [26] */
		"Enabled",
		'LBIT',
		/* [27] */
		"Enabled",
		'LBIT',
		/* [28] */
		"Enabled",
		'LBIT',
		/* [29] */
		"Enabled",
		'LBIT',
		/* [30] */
		"Enabled",
		'LBIT',
		/* [31] */
		"Enabled",
		'LBIT',
		/* [32] */
		"Enabled",
		'LBIT',
		/* [33] */
		"Enabled",
		'LBIT',
		/* [34] */
		"Enabled",
		'LBIT',
		/* [35] */
		"Enabled",
		'LBIT',
		/* [36] */
		"Enabled",
		'LBIT',
		/* [37] */
		"Enabled",
		'LBIT',
		/* [38] */
		"Entire menu enabled",
		'LBIT',
		/* [39] */
		"Title",
		'PSTR',
		/* [40] */
		"List of menu items",
		'LSTZ',
		/* [41] */
		"Menu item title",
		'PSTR',
		/* [42] */
		"Divider=-",
		'CASE',
		/* [43] */
		"Icon ID - 256",
		'DBYT',
		/* [44] */
		"None=0",
		'CASE',
		/* [45] */
		"Key equivalent",
		'CHAR',
		/* [46] */
		"Mark character",
		'CHAR',
		/* [47] */
		"Item style",
		'HBYT',
		/* [48] */
		"Align",
		'AWRD',
		/* [49] */
		"MacApp Command number",
		'DWRD',
		/* [50] */
		"noCommand=0",
		'CASE',
		/* [51] */
		"About Application=1",
		'CASE',
		/* [52] */
		"New=10",
		'CASE',
		/* [53] */
		"Open=20",
		'CASE',
		/* [54] */
		"Save=30",
		'CASE',
		/* [55] */
		"Close=31",
		'CASE',
		/* [56] */
		"Save As=32",
		'CASE',
		/* [57] */
		"Save Copy=33",
		'CASE',
		/* [58] */
		"Revert=34",
		'CASE',
		/* [59] */
		"Show Clipboard=35",
		'CASE',
		/* [60] */
		"Quit=36",
		'CASE',
		/* [61] */
		"Undo=101",
		'CASE',
		/* [62] */
		"Cut=103",
		'CASE',
		/* [63] */
		"Copy=104",
		'CASE',
		/* [64] */
		"Paste=105",
		'CASE',
		/* [65] */
		"Clear=106",
		'CASE',
		/* [66] */
		"Select All=110",
		'CASE',
		/* [67] */
		"Typing=120",
		'CASE',
		/* [68] */
		"Style Change=130",
		'CASE',
		/* [69] */
		"Page Setup=176",
		'CASE',
		/* [70] */
		"Print One=177",
		'CASE',
		/* [71] */
		"Print=178",
		'CASE',
		/* [72] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1044, "CNTL") {
	{	/* array: 57 elements */
		/* [1] */
		"Bounds Rect",
		'RECT',
		/* [2] */
		"Value",
		'DWRD',
		/* [3] */
		"Visible",
		'BOOL',
		/* [4] */
		"Maximum value",
		'DWRD',
		/* [5] */
		"Minimum value",
		'DWRD',
		/* [6] */
		"Proc ID",
		'DWRD',
		/* [7] */
		"PushButtonProc=0",
		'CASE',
		/* [8] */
		"CheckBoxProc=1",
		'CASE',
		/* [9] */
		"RadioButtonProc=2",
		'CASE',
		/* [10] */
		"PushButtonProcUseWFont=8",
		'CASE',
		/* [11] */
		"CheckBoxProcUseWFont=9",
		'CASE',
		/* [12] */
		"RadioButtonProcUseWFont=10",
		'CASE',
		/* [13] */
		"ScrollBarProc=16",
		'CASE',
		/* [14] */
		"PopupMenuProc=1008",
		'CASE',
		/* [15] */
		"ControlBevelButtonLargeBevelProc=34",
		'CASE',
		/* [16] */
		"ControlBevelButtonNormalBevelProc=33",
		'CASE',
		/* [17] */
		"ControlBevelButtonSmallBevelProc=32",
		'CASE',
		/* [18] */
		"ControlChasingArrowsProc=112",
		'CASE',
		/* [19] */
		"ControlCheckBoxProc=369",
		'CASE',
		/* [20] */
		"ControlClockDateProc=242",
		'CASE',
		/* [21] */
		"ControlClockTimeProc=240",
		'CASE',
		/* [22] */
		"ControlEditTextInlineInputProc=276",
		'CASE',
		/* [23] */
		"ControlEditTextPasswordProc=274",
		'CASE',
		/* [24] */
		"ControlEditTextProc=272",
		'CASE',
		/* [25] */
		"ControlEditUnicodeTextPasswordProc=914",
		'CASE',
		/* [26] */
		"ControlEditUnicodeTextProc=912",
		'CASE',
		/* [27] */
		"ControlGroupBoxCheckBoxProc=161",
		'CASE',
		/* [28] */
		"ControlGroupBoxPopupButtonProc=162",
		'CASE',
		/* [29] */
		"ControlGroupBoxTextTitleProc=160",
		'CASE',
		/* [30] */
		"ControlIconProc=320",
		'CASE',
		/* [31] */
		"ControlIconRefProc=324",
		'CASE',
		/* [32] */
		"ControlIconSuiteProc=322",
		'CASE',
		/* [33] */
		"ControlImageWellProc=176",
		'CASE',
		/* [34] */
		"ControlListBoxProc=352",
		'CASE',
		/* [35] */
		"ControlLittleArrowsProc=96",
		'CASE',
		/* [36] */
		"ControlPictureProc=304",
		'CASE',
		/* [37] */
		"ControlPlacardProc=224",
		'CASE',
		/* [38] */
		"ControlPopupButtonProc=400",
		'CASE',
		/* [39] */
		"ControlProgressBarProc=80",
		'CASE',
		/* [40] */
		"ControlPushButtonProc=368",
		'CASE',
		/* [41] */
		"ControlRadioButtonProc=370",
		'CASE',
		/* [42] */
		"ControlRadioGroupProc=416",
		'CASE',
		/* [43] */
		"ControlRelevanceBarProc=81",
		'CASE',
		/* [44] */
		"ControlScrollBarLiveProc=386",
		'CASE',
		/* [45] */
		"ControlScrollBarProc=384",
		'CASE',
		/* [46] */
		"ControlScrollTextBoxProc=432",
		'CASE',
		/* [47] */
		"ControlSeparatorLineProc=144",
		'CASE',
		/* [48] */
		"ControlSliderProc=48",
		'CASE',
		/* [49] */
		"ControlStaticTextProc=288",
		'CASE',
		/* [50] */
		"ControlTabLargeProc=128",
		'CASE',
		/* [51] */
		"ControlTabSmallProc=129",
		'CASE',
		/* [52] */
		"ControlTriangleProc=64",
		'CASE',
		/* [53] */
		"ControlUserPaneProc=256",
		'CASE',
		/* [54] */
		"ControlWindowHeaderProc=336",
		'CASE',
		/* [55] */
		"ControlWindowListViewHeaderProc=337",
		'CASE',
		/* [56] */
		"RefCon",
		'DLNG',
		/* [57] */
		"Title",
		'PSTR'
	}
};

resource 'TMPL' (1045, "Colr") {
	{	/* array: 6 elements */
		/* [1] */
		"Version",
		'DBYT',
		/* [2] */
		"Color scheme file format version",
		'DBYT',
		/* [3] */
		"Minimum Kaleidoscope version",
		'HBYT',
		/* [4] */
		"Has accent colors",
		'BOOL',
		/* [5] */
		"Stretch scroll bar thumb from center (fo"
		"r SmartScroll)",
		'BOOL',
		/* [6] */
		"Reserved",
		'HEXD'
	}
};

resource 'TMPL' (1046, "colw") {
	{	/* array: 12 elements */
		/* [1] */
		"Name col default width",
		'DWRD',
		/* [2] */
		"Name col max width",
		'DWRD',
		/* [3] */
		"Name Col min width",
		'DWRD',
		/* [4] */
		"Version col default width",
		'DWRD',
		/* [5] */
		"Version col max width",
		'DWRD',
		/* [6] */
		"Version col min width",
		'DWRD',
		/* [7] */
		"Column3 default width",
		'DWRD',
		/* [8] */
		"Column3 max width",
		'DWRD',
		/* [9] */
		"Column3 min width",
		'DWRD',
		/* [10] */
		"Column4 default width",
		'DWRD',
		/* [11] */
		"Column4 max width",
		'DWRD',
		/* [12] */
		"Column4 min width",
		'DWRD'
	}
};

resource 'TMPL' (1047, "comm") {
	{	/* array: 96 elements */
		/* [1] */
		"Printer connection",
		'KTYP',
		/* [2] */
		"Serial printer line=SPTL",
		'CASE',
		/* [3] */
		"PAP printer line=PPTL",
		'CASE',
		/* [4] */
		"SCSI printer line=sPTL",
		'CASE',
		/* [5] */
		"Printer share=ptsr",
		'CASE',
		/* [6] */
		"Not connected=nops",
		'CASE',
		/* [7] */
		"SPTL",
		'KEYB',
		/* [8] */
		"Output connection parameters",
		'DVDR',
		/* [9] */
		"Output baud rate",
		'DWRD',
		/* [10] */
		"300=380",
		'CASE',
		/* [11] */
		"600=189",
		'CASE',
		/* [12] */
		"1200=94",
		'CASE',
		/* [13] */
		"1800=62",
		'CASE',
		/* [14] */
		"2400=46",
		'CASE',
		/* [15] */
		"3600=30",
		'CASE',
		/* [16] */
		"4800=22",
		'CASE',
		/* [17] */
		"7200=14",
		'CASE',
		/* [18] */
		"9600=10",
		'CASE',
		/* [19] */
		"19200=4",
		'CASE',
		/* [20] */
		"57600=0",
		'CASE',
		/* [21] */
		"Output parity",
		'DWRD',
		/* [22] */
		"None=0",
		'CASE',
		/* [23] */
		"Odd=4096",
		'CASE',
		/* [24] */
		"Even=12288",
		'CASE',
		/* [25] */
		"Output stop bits",
		'DWRD',
		/* [26] */
		"1=16384",
		'CASE',
		/* [27] */
		"1.5=-32768",
		'CASE',
		/* [28] */
		"2=-16384",
		'CASE',
		/* [29] */
		"Output data bits",
		'DWRD',
		/* [30] */
		"5=0",
		'CASE',
		/* [31] */
		"6=2048",
		'CASE',
		/* [32] */
		"7=1024",
		'CASE',
		/* [33] */
		"8=3072",
		'CASE',
		/* [34] */
		"Output handshaking (high word)",
		'HLNG',
		/* [35] */
		"Output handshaking (low word)",
		'HLNG',
		/* [36] */
		"Input connection parameters",
		'DVDR',
		/* [37] */
		"Input baud rate",
		'DWRD',
		/* [38] */
		"300=380",
		'CASE',
		/* [39] */
		"600=189",
		'CASE',
		/* [40] */
		"1200=94",
		'CASE',
		/* [41] */
		"1800=62",
		'CASE',
		/* [42] */
		"2400=46",
		'CASE',
		/* [43] */
		"3600=30",
		'CASE',
		/* [44] */
		"4800=22",
		'CASE',
		/* [45] */
		"7200=14",
		'CASE',
		/* [46] */
		"9600=10",
		'CASE',
		/* [47] */
		"19200=4",
		'CASE',
		/* [48] */
		"57600=0",
		'CASE',
		/* [49] */
		"Input parity",
		'DWRD',
		/* [50] */
		"None=0",
		'CASE',
		/* [51] */
		"Odd=4096",
		'CASE',
		/* [52] */
		"Even=12288",
		'CASE',
		/* [53] */
		"Input stop bits",
		'DWRD',
		/* [54] */
		"1=16384",
		'CASE',
		/* [55] */
		"1.5=-32768",
		'CASE',
		/* [56] */
		"2=-16384",
		'CASE',
		/* [57] */
		"Input data bits",
		'DWRD',
		/* [58] */
		"5=0",
		'CASE',
		/* [59] */
		"6=2048",
		'CASE',
		/* [60] */
		"7=1024",
		'CASE',
		/* [61] */
		"8=3072",
		'CASE',
		/* [62] */
		"Input handshaking (high word)",
		'HLNG',
		/* [63] */
		"Input handshaking (low word)",
		'HLNG',
		/* [64] */
		"",
		'DVDR',
		/* [65] */
		"Serial input buffer size",
		'UWRD',
		/* [66] */
		"Input port name",
		'P040',
		/* [67] */
		"Output port name",
		'P040',
		/* [68] */
		"",
		'KEYE',
		/* [69] */
		"PPTL",
		'KEYB',
		/* [70] */
		"Flow quantum",
		'DWRD',
		/* [71] */
		"Compacted AppleTalk name of printer",
		'C064',
		/* [72] */
		"Open status buffer pointer",
		'HLNG',
		/* [73] */
		"EOF read byte pointer",
		'HLNG',
		/* [74] */
		"EOF write byte pointer",
		'HLNG',
		/* [75] */
		"Most recent network address of printer",
		'HLNG',
		/* [76] */
		"",
		'KEYE',
		/* [77] */
		"sPTL",
		'KEYB',
		/* [78] */
		"Pointer to C routine to release SCSI dev"
		"ice",
		'HLNG',
		/* [79] */
		"SCSI I/O Attributes",
		'HWRD',
		/* [80] */
		"Location of status byte from data transf"
		"er",
		'HLNG',
		/* [81] */
		"SCSI bus number",
		'DWRD',
		/* [82] */
		"Motherboard=0",
		'CASE',
		/* [83] */
		"SCSI device number",
		'DWRD',
		/* [84] */
		"Pointer to C routine that can acquire SC"
		"SI device",
		'HLNG',
		/* [85] */
		"Device type to look for",
		'DWRD',
		/* [86] */
		"Minimum amount of data in response",
		'DWRD',
		/* [87] */
		"Offset from start to look in response da"
		"ta",
		'DWRD',
		/* [88] */
		"String to look for in response data",
		'PSTR',
		/* [89] */
		"",
		'KEYE',
		/* [90] */
		"ptsr",
		'KEYB',
		/* [91] */
		"Compacted AppleTalk name of printer",
		'C064',
		/* [92] */
		"Most recent network address of printer",
		'HLNG',
		/* [93] */
		"",
		'KEYE',
		/* [94] */
		"nops",
		'KEYB',
		/* [95] */
		"'nops': not connected",
		'DVDR',
		/* [96] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1048, "cool") {
	{	/* array: 27 elements */
		/* [1] */
		"Alert type",
		'DWRD',
		/* [2] */
		"Alert=1",
		'CASE',
		/* [3] */
		"Status=2",
		'CASE',
		/* [4] */
		"Icon resource ID",
		'DWRD',
		/* [5] */
		"No icon=-1",
		'CASE',
		/* [6] */
		"Stop=0",
		'CASE',
		/* [7] */
		"Note=1",
		'CASE',
		/* [8] */
		"Caution=2",
		'CASE',
		/* [9] */
		"System size",
		'DWRD',
		/* [10] */
		"Default=0",
		'CASE',
		/* [11] */
		"Default button",
		'DBYT',
		/* [12] */
		"No default title=0",
		'CASE',
		/* [13] */
		"Default action=1",
		'CASE',
		/* [14] */
		"Default title 2=2",
		'CASE',
		/* [15] */
		"Default title 3=3",
		'CASE',
		/* [16] */
		"Cancel button",
		'DBYT',
		/* [17] */
		"None=0",
		'CASE',
		/* [18] */
		"Cancel action=1",
		'CASE',
		/* [19] */
		"Cancel title 2=2",
		'CASE',
		/* [20] */
		"Cancel title 3=3",
		'CASE',
		/* [21] */
		"Text string",
		'WSTR',
		/* [22] */
		"Action button label",
		'PSTR',
		/* [23] */
		"Button 2 label",
		'PSTR',
		/* [24] */
		"Button 3 label",
		'PSTR',
		/* [25] */
		"Font name",
		'PSTR',
		/* [26] */
		"Alert title",
		'PSTR',
		/* [27] */
		"Default=Alert",
		'CASE'
	}
};

resource 'TMPL' (1049, "cpix") {
	{	/* array: 3 elements */
		/* [1] */
		"Compressors supported compress pixel for"
		"mat surfaces",
		'LSTB',
		/* [2] */
		"Type",
		'TNAM',
		/* [3] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1050, "CPPb") {
	{	/* array: 58 elements */
		/* [1] */
		"Object Type",
		'TNAM',
		/* [2] */
		"Object Base Type",
		'TNAM',
		/* [3] */
		"Object Icon ID",
		'DWRD',
		/* [4] */
		"Object Editor PPob",
		'DWRD',
		/* [5] */
		"Object Name",
		'PSTR',
		/* [6] */
		"Reserved (display flags)",
		'BB02',
		/* [7] */
		"Is subclass of LControl?",
		'BBIT',
		/* [8] */
		"Is subclass of LWindow?",
		'BBIT',
		/* [9] */
		"Is subclass of LBroadcaster?",
		'BBIT',
		/* [10] */
		"Is subclass of LCommander?",
		'BBIT',
		/* [11] */
		"Can have subviews",
		'BBIT',
		/* [12] */
		"Wants to be in tool window",
		'BBIT',
		/* [13] */
		"Number of Fields",
		'OCNT',
		/* [14] */
		"",
		'LSTC',
		/* [15] */
		"Field Name",
		'PSTR',
		/* [16] */
		"Field Descriptor ID",
		'TNAM',
		/* [17] */
		"Field Data Type",
		'TNAM',
		/* [18] */
		"Int8=DBYT",
		'CASE',
		/* [19] */
		"Uint8=UBYT",
		'CASE',
		/* [20] */
		"Int16=DWRD",
		'CASE',
		/* [21] */
		"Uint16=UWRD",
		'CASE',
		/* [22] */
		"Int32=DLNG",
		'CASE',
		/* [23] */
		"Uint32=ULNG",
		'CASE',
		/* [24] */
		"Bitfield (1-bit)=BBIT",
		'CASE',
		/* [25] */
		"Str255=PSTR",
		'CASE',
		/* [26] */
		"Str255 (even padded)=ESTR",
		'CASE',
		/* [27] */
		"8-Bit Boolean=BOOL",
		'CASE',
		/* [28] */
		"Type=TNAM",
		'CASE',
		/* [29] */
		"RGB Color=COLR",
		'CASE',
		/* [30] */
		"Has display specification",
		'KWRD',
		/* [31] */
		"No=0",
		'CASE',
		/* [32] */
		"Yes=1",
		'CASE',
		/* [33] */
		"0",
		'KEYB',
		/* [34] */
		"Default value",
		'DWRD',
		/* [35] */
		"",
		'KEYE',
		/* [36] */
		"1",
		'KEYB',
		/* [37] */
		"Default value",
		'DLNG',
		/* [38] */
		"Reserved",
		'LB23',
		/* [39] */
		"Allow <CR> in text",
		'LBIT',
		/* [40] */
		"Do not write to stream",
		'LBIT',
		/* [41] */
		"Use text traits popup",
		'LBIT',
		/* [42] */
		"Do not display",
		'LBIT',
		/* [43] */
		"Use Text/Numeric checkbox",
		'LBIT',
		/* [44] */
		"Use font list popup",
		'LBIT',
		/* [45] */
		"[Font list] Include % fonts",
		'LBIT',
		/* [46] */
		"Use value list popup",
		'LBIT',
		/* [47] */
		"Use radio buttons",
		'LBIT',
		/* [48] */
		"Number of Values",
		'OCNT',
		/* [49] */
		"",
		'LSTC',
		/* [50] */
		"Value",
		'DLNG',
		/* [51] */
		"Pane ID",
		'TNAM',
		/* [52] */
		"Value label",
		'PSTR',
		/* [53] */
		"",
		'LSTE',
		/* [54] */
		"",
		'KEYE',
		/* [55] */
		"",
		'LSTE',
		/* [56] */
		"Width of drag rect",
		'DWRD',
		/* [57] */
		"Height of drag rect",
		'DWRD',
		/* [58] */
		"Default PPob resource",
		'DWRD'
	}
};

resource 'TMPL' (1051, "cpts") {
	{	/* array: 13 elements */
		/* [1] */
		"Type of capture string",
		'KRID',
		/* [2] */
		"Capture/uncapture=-27648",
		'CASE',
		/* [3] */
		"AppleTalk for uncaptured devices=-27646",
		'CASE',
		/* [4] */
		"AppleTalk for captured devices=-27645",
		'CASE',
		/* [5] */
		"-27648",
		'KEYB',
		/* [6] */
		"String",
		'HEXD',
		/* [7] */
		"",
		'KEYE',
		/* [8] */
		"-27646",
		'KEYB',
		/* [9] */
		"String",
		'PSTR',
		/* [10] */
		"",
		'KEYE',
		/* [11] */
		"-27645",
		'KEYB',
		/* [12] */
		"String",
		'PSTR',
		/* [13] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1052, "crst") {
	{	/* array: 8 elements */
		/* [1] */
		"Color space",
		'DLNG',
		/* [2] */
		"Count:",
		'LCNT',
		/* [3] */
		"List of Members",
		'LSTC',
		/* [4] */
		"Component 1",
		'HWRD',
		/* [5] */
		"Component 2",
		'HWRD',
		/* [6] */
		"Component 3",
		'HWRD',
		/* [7] */
		"Component 4",
		'HWRD',
		/* [8] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1053, "CTY#") {
	{	/* array: 10 elements */
		/* [1] */
		"Num cities",
		'ZCNT',
		/* [2] */
		"List of cities",
		'LSTC',
		/* [3] */
		"Number of characters",
		'DWRD',
		/* [4] */
		"Latitude",
		'HLNG',
		/* [5] */
		"Longitude",
		'HLNG',
		/* [6] */
		"GMT differrence",
		'DLNG',
		/* [7] */
		"abc",
		'DLNG',
		/* [8] */
		"City Name",
		'PSTR',
		/* [9] */
		"align",
		'AWRD',
		/* [10] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1054, "CTYP") {
	{	/* array: 237 elements */
		/* [1] */
		"Template for Constructor CWPro4",
		'DVDR',
		/* [2] */
		"Version Number",
		'DWRD',
		/* [3] */
		"CWPro4=1",
		'CASE',
		/* [4] */
		"List of objects",
		'LSTB',
		/* [5] */
		"Object type",
		'KTYP',
		/* [6] */
		"Object data=objd",
		'CASE',
		/* [7] */
		"Begin sub-object list=begs",
		'CASE',
		/* [8] */
		"End sub-object list=ends",
		'CASE',
		/* [9] */
		"User object=user",
		'CASE',
		/* [10] */
		"Class alias=dopl",
		'CASE',
		/* [11] */
		"End of list=end.",
		'CASE',
		/* [12] */
		"objd",
		'KEYB',
		/* [13] */
		"Number of bytes in following data",
		'LSIZ',
		/* [14] */
		"Data type",
		'KTYP',
		/* [15] */
		"Object=obj ",
		'CASE',
		/* [16] */
		"Custom display class info=vpte",
		'CASE',
		/* [17] */
		"Integer attribute=intv",
		'CASE',
		/* [18] */
		"Toolbox boolean attribute=tbxb",
		'CASE',
		/* [19] */
		"Labelled integer attribute=labi",
		'CASE',
		/* [20] */
		"Min/max integer attribute=mimx",
		'CASE',
		/* [21] */
		"Res list attribute=resl",
		'CASE',
		/* [22] */
		"String attribute=pstr",
		'CASE',
		/* [23] */
		"Font string attribute=fstr",
		'CASE',
		/* [24] */
		"RGB color attribute=rgbc",
		'CASE',
		/* [25] */
		"Container attribute=cont",
		'CASE',
		/* [26] */
		"List attribute=list",
		'CASE',
		/* [27] */
		"Bitfield container attribute=bitf",
		'CASE',
		/* [28] */
		"Value label=labl",
		'CASE',
		/* [29] */
		"Null=null",
		'CASE',
		/* [30] */
		"obj ",
		'KEYB',
		/* [31] */
		"",
		'KEYE',
		/* [32] */
		"vpte",
		'KEYB',
		/* [33] */
		"VETypeEntry data",
		'DVDR',
		/* [34] */
		"Class name",
		'PSTR',
		/* [35] */
		"Icon ID",
		'DWRD',
		/* [36] */
		"Abstract class?",
		'BFLG',
		/* [37] */
		"Class ID",
		'TNAM',
		/* [38] */
		"Parent class ID",
		'TNAM',
		/* [39] */
		"Default width",
		'DWRD',
		/* [40] */
		"Default height",
		'DWRD',
		/* [41] */
		"Must be root?",
		'BFLG',
		/* [42] */
		"Default resource ID",
		'DWRD',
		/* [43] */
		"",
		'KEYE',
		/* [44] */
		"intv",
		'KEYB',
		/* [45] */
		"DMAttribute data",
		'DVDR',
		/* [46] */
		"Attribute title",
		'PSTR',
		/* [47] */
		"Attribute key",
		'TNAM',
		/* [48] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [49] */
		"Write to stream?",
		'BFLG',
		/* [50] */
		"Stream selector",
		'TNAM',
		/* [51] */
		"DMIntegerAttribute data",
		'DVDR',
		/* [52] */
		"Default value",
		'DLNG',
		/* [53] */
		"Value size (bits)",
		'UWRD',
		/* [54] */
		"Signed integer?",
		'BFLG',
		/* [55] */
		"Can be text value?",
		'BFLG',
		/* [56] */
		"Always is text value?",
		'BFLG',
		/* [57] */
		"",
		'KEYE',
		/* [58] */
		"tbxb",
		'KEYB',
		/* [59] */
		"DMAttribute data",
		'DVDR',
		/* [60] */
		"Attribute title",
		'PSTR',
		/* [61] */
		"Attribute key",
		'TNAM',
		/* [62] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [63] */
		"Write to stream?",
		'BFLG',
		/* [64] */
		"Stream selector",
		'TNAM',
		/* [65] */
		"DMIntegerAttribute data",
		'DVDR',
		/* [66] */
		"Default value",
		'DLNG',
		/* [67] */
		"Value size (bits)",
		'UWRD',
		/* [68] */
		"Signed integer?",
		'BFLG',
		/* [69] */
		"Can be text value?",
		'BFLG',
		/* [70] */
		"Always is text value?",
		'BFLG',
		/* [71] */
		"Number of bytes (1 or 2)",
		'DWRD',
		/* [72] */
		"",
		'KEYE',
		/* [73] */
		"labi",
		'KEYB',
		/* [74] */
		"DMAttribute data",
		'DVDR',
		/* [75] */
		"Attribute title",
		'PSTR',
		/* [76] */
		"Attribute key",
		'TNAM',
		/* [77] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [78] */
		"Write to stream?",
		'BFLG',
		/* [79] */
		"Stream selector",
		'TNAM',
		/* [80] */
		"DMIntegerAttribute data",
		'DVDR',
		/* [81] */
		"Default value",
		'DLNG',
		/* [82] */
		"Value size (bits)",
		'UWRD',
		/* [83] */
		"Signed integer?",
		'BFLG',
		/* [84] */
		"Can be text value?",
		'BFLG',
		/* [85] */
		"Always is text value?",
		'BFLG',
		/* [86] */
		"DMLabelledIntegerAttribute data",
		'DVDR',
		/* [87] */
		"Labels only?",
		'BFLG',
		/* [88] */
		"",
		'KEYE',
		/* [89] */
		"mimx",
		'KEYB',
		/* [90] */
		"DMAttribute data",
		'DVDR',
		/* [91] */
		"Attribute title",
		'PSTR',
		/* [92] */
		"Attribute key",
		'TNAM',
		/* [93] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [94] */
		"Write to stream?",
		'BFLG',
		/* [95] */
		"Stream selector",
		'TNAM',
		/* [96] */
		"DMIntegerAttribute data",
		'DVDR',
		/* [97] */
		"Default value",
		'DLNG',
		/* [98] */
		"Value size (bits)",
		'UWRD',
		/* [99] */
		"Signed integer?",
		'BFLG',
		/* [100] */
		"Can be text value?",
		'BFLG',
		/* [101] */
		"Always is text value?",
		'BFLG',
		/* [102] */
		"DMMinMaxIntegerAttribute data",
		'DVDR',
		/* [103] */
		"Minimum value",
		'DLNG',
		/* [104] */
		"Maximum value",
		'DLNG',
		/* [105] */
		"",
		'KEYE',
		/* [106] */
		"resl",
		'KEYB',
		/* [107] */
		"DMAttribute data",
		'DVDR',
		/* [108] */
		"Attribute title",
		'PSTR',
		/* [109] */
		"Attribute key",
		'TNAM',
		/* [110] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [111] */
		"Write to stream?",
		'BFLG',
		/* [112] */
		"Stream selector",
		'TNAM',
		/* [113] */
		"DMIntegerAttribute data",
		'DVDR',
		/* [114] */
		"Default value",
		'DLNG',
		/* [115] */
		"Value size (bits)",
		'UWRD',
		/* [116] */
		"Signed integer?",
		'BFLG',
		/* [117] */
		"Can be text value?",
		'BFLG',
		/* [118] */
		"Always is text value?",
		'BFLG',
		/* [119] */
		"DMLabelledIntegerAttribute data",
		'DVDR',
		/* [120] */
		"Labels only?",
		'BFLG',
		/* [121] */
		"DMResListAttribute data",
		'DVDR',
		/* [122] */
		"Resource type",
		'TNAM',
		/* [123] */
		"",
		'KEYE',
		/* [124] */
		"pstr",
		'KEYB',
		/* [125] */
		"DMAttribute data",
		'DVDR',
		/* [126] */
		"Attribute title",
		'PSTR',
		/* [127] */
		"Attribute key",
		'TNAM',
		/* [128] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [129] */
		"Write to stream?",
		'BFLG',
		/* [130] */
		"Stream selector",
		'TNAM',
		/* [131] */
		"DMStringAttribute data",
		'DVDR',
		/* [132] */
		"Default value",
		'PSTR',
		/* [133] */
		"Maximum length (characters)",
		'UWRD',
		/* [134] */
		"Even padded?",
		'BFLG',
		/* [135] */
		"(unused)",
		'BB05',
		/* [136] */
		"Accept CR?",
		'BBIT',
		/* [137] */
		"C style string?",
		'BBIT',
		/* [138] */
		"Odd padded?",
		'BBIT',
		/* [139] */
		"",
		'KEYE',
		/* [140] */
		"fstr",
		'KEYB',
		/* [141] */
		"DMAttribute data",
		'DVDR',
		/* [142] */
		"Attribute title",
		'PSTR',
		/* [143] */
		"Attribute key",
		'TNAM',
		/* [144] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [145] */
		"Write to stream?",
		'BFLG',
		/* [146] */
		"Stream selector",
		'TNAM',
		/* [147] */
		"DMStringAttribute data",
		'DVDR',
		/* [148] */
		"Default value",
		'PSTR',
		/* [149] */
		"Maximum length (characters)",
		'UWRD',
		/* [150] */
		"Even padded?",
		'BFLG',
		/* [151] */
		"(unused)",
		'BB05',
		/* [152] */
		"Accept CR?",
		'BBIT',
		/* [153] */
		"C style string?",
		'BBIT',
		/* [154] */
		"Odd padded?",
		'BBIT',
		/* [155] */
		"DMFontStringAttribute data",
		'DVDR',
		/* [156] */
		"Default font number",
		'DWRD',
		/* [157] */
		"Write font number?",
		'BFLG',
		/* [158] */
		"Include system font?",
		'BFLG',
		/* [159] */
		"Include application font?",
		'BFLG',
		/* [160] */
		"Include hidden fonts?",
		'BFLG',
		/* [161] */
		"",
		'KEYE',
		/* [162] */
		"rgbc",
		'KEYB',
		/* [163] */
		"DMAttribute data",
		'DVDR',
		/* [164] */
		"Attribute title",
		'PSTR',
		/* [165] */
		"Attribute key",
		'TNAM',
		/* [166] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [167] */
		"Write to stream?",
		'BFLG',
		/* [168] */
		"Stream selector",
		'TNAM',
		/* [169] */
		"DMRGBColorAttribute data",
		'DVDR',
		/* [170] */
		"Default value",
		'COLR',
		/* [171] */
		"",
		'KEYE',
		/* [172] */
		"cont",
		'KEYB',
		/* [173] */
		"DMAttribute data",
		'DVDR',
		/* [174] */
		"Attribute title",
		'PSTR',
		/* [175] */
		"Attribute key",
		'TNAM',
		/* [176] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [177] */
		"Write to stream?",
		'BFLG',
		/* [178] */
		"Stream selector",
		'TNAM',
		/* [179] */
		"DMContainerAttribute data",
		'DVDR',
		/* [180] */
		"Is subobject list?",
		'BFLG',
		/* [181] */
		"Member class ID",
		'TNAM',
		/* [182] */
		"",
		'KEYE',
		/* [183] */
		"list",
		'KEYB',
		/* [184] */
		"DMAttribute data",
		'DVDR',
		/* [185] */
		"Attribute title",
		'PSTR',
		/* [186] */
		"Attribute key",
		'TNAM',
		/* [187] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [188] */
		"Write to stream?",
		'BFLG',
		/* [189] */
		"Stream selector",
		'TNAM',
		/* [190] */
		"DMContainerAttribute data",
		'DVDR',
		/* [191] */
		"Is subobject list?",
		'BFLG',
		/* [192] */
		"Member class ID",
		'TNAM',
		/* [193] */
		"DMListAttribute data",
		'DVDR',
		/* [194] */
		"Subitem title",
		'PSTR',
		/* [195] */
		"Number of bytes for count",
		'DLNG',
		/* [196] */
		"unused",
		'BB06',
		/* [197] */
		"Zero based display?",
		'BB01',
		/* [198] */
		"Zero-based count?",
		'BB01',
		/* [199] */
		"",
		'KEYE',
		/* [200] */
		"bitf",
		'KEYB',
		/* [201] */
		"DMAttribute data",
		'DVDR',
		/* [202] */
		"Attribute title",
		'PSTR',
		/* [203] */
		"Attribute key",
		'TNAM',
		/* [204] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [205] */
		"Write to stream?",
		'BFLG',
		/* [206] */
		"Stream selector",
		'TNAM',
		/* [207] */
		"DMContainerAttribute data",
		'DVDR',
		/* [208] */
		"Is subobject list?",
		'BFLG',
		/* [209] */
		"Member class ID",
		'TNAM',
		/* [210] */
		"DMBitfieldAttribute data",
		'DVDR',
		/* [211] */
		"Bitfield size (bytes)",
		'UWRD',
		/* [212] */
		"",
		'KEYE',
		/* [213] */
		"labl",
		'KEYB',
		/* [214] */
		"Value",
		'DLNG',
		/* [215] */
		"Label",
		'PSTR',
		/* [216] */
		"",
		'KEYE',
		/* [217] */
		"null",
		'KEYB',
		/* [218] */
		"",
		'KEYE',
		/* [219] */
		"",
		'KEYB',
		/* [220] */
		"Unknown data",
		'HEXD',
		/* [221] */
		"",
		'KEYE',
		/* [222] */
		"",
		'SKPE',
		/* [223] */
		"",
		'KEYE',
		/* [224] */
		"begs",
		'KEYB',
		/* [225] */
		"",
		'KEYE',
		/* [226] */
		"ends",
		'KEYB',
		/* [227] */
		"",
		'KEYE',
		/* [228] */
		"user",
		'KEYB',
		/* [229] */
		"SuperClass ID for next object",
		'TNAM',
		/* [230] */
		"",
		'KEYE',
		/* [231] */
		"dopl",
		'KEYB',
		/* [232] */
		"Class ID for next object",
		'TNAM',
		/* [233] */
		"",
		'KEYE',
		/* [234] */
		"end.",
		'KEYB',
		/* [235] */
		"This must be last object type in list",
		'DVDR',
		/* [236] */
		"",
		'KEYE',
		/* [237] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1055, "CURS") {
	{	/* array: 3 elements */
		/* [1] */
		"Image bits",
		'H020',
		/* [2] */
		"Mask bits",
		'H020',
		/* [3] */
		"Hot spot",
		'PNT '
	}
};

resource 'TMPL' (1056, "cust") {
	{	/* array: 15 elements */
		/* [1] */
		"Horizontal resolution (dots/inch)",
		'DWRD',
		/* [2] */
		"Vertical resolution (dots/inch)",
		'DWRD',
		/* [3] */
		"Interface driver type",
		'DWRD',
		/* [4] */
		"LaserWriter (default)=0",
		'CASE',
		/* [5] */
		"LaserWriter SC=1",
		'CASE',
		/* [6] */
		"Pattern stretch factor",
		'PNT ',
		/* [7] */
		"Translation settings (for old driver cal"
		"ls to GX driver messages)",
		'DVDR',
		/* [8] */
		"For best representation of QuickDraw, tu"
		"rn all of these off.",
		'DVDR',
		/* [9] */
		"Reserved",
		'WB10',
		/* [10] */
		"Disregard zero-width lines and data",
		'WBIT',
		/* [11] */
		"Allow text line layout to perform subst",
		'WBIT',
		/* [12] */
		"Simple hanging pen geometry",
		'WBIT',
		/* [13] */
		"Simple multiply-only scaling",
		'WBIT',
		/* [14] */
		"Replace line width",
		'WBIT',
		/* [15] */
		"Optimized",
		'WBIT'
	}
};

resource 'TMPL' (1057, "CWid") {
	{	/* array: 47 elements */
		/* [1] */
		"Minimum column width",
		'UWRD',
		/* [2] */
		"Default column width",
		'UWRD',
		/* [3] */
		"Default text justification",
		'DWRD',
		/* [4] */
		"Left=0",
		'CASE',
		/* [5] */
		"Center=1",
		'CASE',
		/* [6] */
		"Right=-1",
		'CASE',
		/* [7] */
		"Force Left=-2",
		'CASE',
		/* [8] */
		"Reserved",
		'FWRD',
		/* [9] */
		"Count:",
		'LCNT',
		/* [10] */
		"Column Records",
		'LSTC',
		/* [11] */
		"Column field",
		'ULNG',
		/* [12] */
		"Name=2",
		'CASE',
		/* [13] */
		"Album=3",
		'CASE',
		/* [14] */
		"Artist=4",
		'CASE',
		/* [15] */
		"Bit Rate=5",
		'CASE',
		/* [16] */
		"Sample Rate=6",
		'CASE',
		/* [17] */
		"Year=7",
		'CASE',
		/* [18] */
		"Genre=8",
		'CASE',
		/* [19] */
		"Kind=9",
		'CASE',
		/* [20] */
		"Date Modified=10",
		'CASE',
		/* [21] */
		"Track #=11",
		'CASE',
		/* [22] */
		"Size=12",
		'CASE',
		/* [23] */
		"Time=13",
		'CASE',
		/* [24] */
		"Stream Status=21",
		'CASE',
		/* [25] */
		"Comment=14",
		'CASE',
		/* [26] */
		"Play Status=1",
		'CASE',
		/* [27] */
		"EQ Preset=17",
		'CASE',
		/* [28] */
		"Date Added=16",
		'CASE',
		/* [29] */
		"Composer=18",
		'CASE',
		/* [30] */
		"Play Count=22",
		'CASE',
		/* [31] */
		"Last Played=23",
		'CASE',
		/* [32] */
		"Disc #=24",
		'CASE',
		/* [33] */
		"My Rating=25",
		'CASE',
		/* [34] */
		"Jingle1=26",
		'CASE',
		/* [35] */
		"Jingle2=32",
		'CASE',
		/* [36] */
		"Jingle3=33",
		'CASE',
		/* [37] */
		"Release Date=34",
		'CASE',
		/* [38] */
		"Beats Per Minute=35",
		'CASE',
		/* [39] */
		"Minimum width",
		'UWRD',
		/* [40] */
		"Default width",
		'UWRD',
		/* [41] */
		"Text justification",
		'DWRD',
		/* [42] */
		"Left=0",
		'CASE',
		/* [43] */
		"Center=1",
		'CASE',
		/* [44] */
		"Right=-1",
		'CASE',
		/* [45] */
		"Force Left=-2",
		'CASE',
		/* [46] */
		"Reserved",
		'FWRD',
		/* [47] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1058, "dale") {
	{	/* array: 4 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"List of C Strings",
		'LSTC',
		/* [3] */
		"String",
		'CSTR',
		/* [4] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1059, "DBnf") {
	{	/* array: 9 elements */
		/* [1] */
		"\"SuitCase\" resource format",
		'DVDR',
		/* [2] */
		"Database file creator",
		'TNAM',
		/* [3] */
		"Database file type",
		'TNAM',
		/* [4] */
		"Name of Suitcase Prefs folder",
		'P020',
		/* [5] */
		"Name of Suitcase Database file",
		'P020',
		/* [6] */
		"Name of Startup set",
		'P020',
		/* [7] */
		"Name of Temporary set",
		'P020',
		/* [8] */
		"Name of untitled set",
		'P020',
		/* [9] */
		"Database version number",
		'ULNG'
	}
};

resource 'TMPL' (1060, "dbug") {
	{	/* array: 12 elements */
		/* [1] */
		"Debug window bounds",
		'RECT',
		/* [2] */
		"Debug Window font resource ID",
		'RSID',
		/* [3] */
		"Application=1",
		'CASE',
		/* [4] */
		"Debug Window font size",
		'DWRD',
		/* [5] */
		"Normal=9",
		'CASE',
		/* [6] */
		"Number of lines",
		'DWRD',
		/* [7] */
		"Normal=120",
		'CASE',
		/* [8] */
		"Width of lines in characters",
		'DWRD',
		/* [9] */
		"Normal=100",
		'CASE',
		/* [10] */
		"Open the Debug Window initially",
		'WBIT',
		/* [11] */
		"Reserved",
		'WB15',
		/* [12] */
		"Debug Window title",
		'PSTR'
	}
};

resource 'TMPL' (1061, "dctb") {
	{	/* array: 12 elements */
		/* [1] */
		"Dialog color seed",
		'HLNG',
		/* [2] */
		"Flags",
		'HWRD',
		/* [3] */
		"Count:",
		'ZCNT',
		/* [4] */
		"List of Colors",
		'LSTC',
		/* [5] */
		"Part code",
		'DWRD',
		/* [6] */
		"Content color=0",
		'CASE',
		/* [7] */
		"Frame color=1",
		'CASE',
		/* [8] */
		"Text color=2",
		'CASE',
		/* [9] */
		"Hilite color=3",
		'CASE',
		/* [10] */
		"Title bar color=4",
		'CASE',
		/* [11] */
		"Color",
		'COLR',
		/* [12] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1062, "dctl") {
	{	/* array: 103 elements */
		/* [1] */
		"Maximum item count",
		'DWRD',
		/* [2] */
		"Count:",
		'ZCNT',
		/* [3] */
		"List of Dialog items",
		'LSTC',
		/* [4] */
		"Item type",
		'KWRD',
		/* [5] */
		"Button=1",
		'CASE',
		/* [6] */
		"Cluster=2",
		'CASE',
		/* [7] */
		"Copies=3",
		'CASE',
		/* [8] */
		"Dialog button=4",
		'CASE',
		/* [9] */
		"Frill=5",
		'CASE',
		/* [10] */
		"Moof=6",
		'CASE',
		/* [11] */
		"OK Button=7",
		'CASE',
		/* [12] */
		"Orientation=8",
		'CASE',
		/* [13] */
		"Page range=9",
		'CASE',
		/* [14] */
		"Paper sizes=10",
		'CASE',
		/* [15] */
		"Scale=11",
		'CASE',
		/* [16] */
		"Toggle=12",
		'CASE',
		/* [17] */
		"2",
		'KEYB',
		/* [18] */
		"Cluster type",
		'DWRD',
		/* [19] */
		"Feed=0",
		'CASE',
		/* [20] */
		"Quality=1",
		'CASE',
		/* [21] */
		"Cover page=2",
		'CASE',
		/* [22] */
		"First page=3",
		'CASE',
		/* [23] */
		"Rest page=4",
		'CASE',
		/* [24] */
		"Head motion=5",
		'CASE',
		/* [25] */
		"Create file=6",
		'CASE',
		/* [26] */
		"User 0=7",
		'CASE',
		/* [27] */
		"User 1=8",
		'CASE',
		/* [28] */
		"User 2=9",
		'CASE',
		/* [29] */
		"",
		'KEYE',
		/* [30] */
		"3",
		'KEYB',
		/* [31] */
		"Item ID",
		'DWRD',
		/* [32] */
		"",
		'KEYE',
		/* [33] */
		"4",
		'KEYB',
		/* [34] */
		"Item ID of cascade button",
		'DWRD',
		/* [35] */
		"Resource ID of 'DLOG'",
		'RSID',
		/* [36] */
		"Resource ID of dialog controller ('dctl'"
		")",
		'RSID',
		/* [37] */
		"",
		'KEYE',
		/* [38] */
		"5",
		'KEYB',
		/* [39] */
		"Item ID",
		'DWRD',
		/* [40] */
		"Kind of frill",
		'DWRD',
		/* [41] */
		"Default=2",
		'CASE',
		/* [42] */
		"Line=0",
		'CASE',
		/* [43] */
		"Version=1",
		'CASE',
		/* [44] */
		"Printer name=3",
		'CASE',
		/* [45] */
		"",
		'KEYE',
		/* [46] */
		"6",
		'KEYB',
		/* [47] */
		"Item ID",
		'DWRD',
		/* [48] */
		"",
		'KEYE',
		/* [49] */
		"7",
		'KEYB',
		/* [50] */
		"Item ID",
		'DWRD',
		/* [51] */
		"Item ID of the \"Print\" string",
		'DWRD',
		/* [52] */
		"Item ID of the \"Save\" string",
		'DWRD',
		/* [53] */
		"",
		'KEYE',
		/* [54] */
		"8",
		'KEYB',
		/* [55] */
		"Item ID of \"portrait\" orientation",
		'DWRD',
		/* [56] */
		"Item ID of \"landscape\" orientation",
		'DWRD',
		/* [57] */
		"Item ID of \"flipped portrait\"",
		'DWRD',
		/* [58] */
		"Item ID of \"flipped landscape\"",
		'DWRD',
		/* [59] */
		"",
		'KEYE',
		/* [60] */
		"9",
		'KEYB',
		/* [61] */
		"Item ID of \"All\" button",
		'DWRD',
		/* [62] */
		"Item ID of the \"Range\" button",
		'DWRD',
		/* [63] */
		"Item ID of the \"from\" edit text",
		'DWRD',
		/* [64] */
		"Item ID of the \"to\" edit text",
		'DWRD',
		/* [65] */
		"",
		'KEYE',
		/* [66] */
		"10",
		'KEYB',
		/* [67] */
		"Item ID of popup",
		'DWRD',
		/* [68] */
		"Item ID of popup radio button",
		'DWRD',
		/* [69] */
		"Reserved",
		'FLNG',
		/* [70] */
		"Reserved",
		'FWRD',
		/* [71] */
		"Count:",
		'OCNT',
		/* [72] */
		"List of Clusters",
		'LSTC',
		/* [73] */
		"Item ID",
		'DWRD',
		/* [74] */
		"*****",
		'LSTE',
		/* [75] */
		"",
		'KEYE',
		/* [76] */
		"11",
		'KEYB',
		/* [77] */
		"Item ID of the edit text",
		'DWRD',
		/* [78] */
		"Item ID of the arrow user item",
		'DWRD',
		/* [79] */
		"Resource ID of 'stab'",
		'RSID',
		/* [80] */
		"",
		'KEYE',
		/* [81] */
		"12",
		'KEYB',
		/* [82] */
		"Item ID",
		'DWRD',
		/* [83] */
		"Reserved",
		'WB03',
		/* [84] */
		"User 2",
		'WBIT',
		/* [85] */
		"User 1",
		'WBIT',
		/* [86] */
		"User 0",
		'WBIT',
		/* [87] */
		"Bidirectional",
		'WBIT',
		/* [88] */
		"Color mode",
		'WBIT',
		/* [89] */
		"Flip vertical",
		'WBIT',
		/* [90] */
		"Flip horizontal",
		'WBIT',
		/* [91] */
		"Invert",
		'WBIT',
		/* [92] */
		"Font substitution",
		'WBIT',
		/* [93] */
		"Text smoothing",
		'WBIT',
		/* [94] */
		"Graphic smoothing",
		'WBIT',
		/* [95] */
		"Bigger pages",
		'WBIT',
		/* [96] */
		"Precise bitmap",
		'WBIT',
		/* [97] */
		"",
		'KEYE',
		/* [98] */
		"1",
		'KEYB',
		/* [99] */
		"Item ID",
		'DWRD',
		/* [100] */
		"Kind of button",
		'DWRD',
		/* [101] */
		"Cancel=0",
		'CASE',
		/* [102] */
		"",
		'KEYE',
		/* [103] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1063, "desC") {
	{	/* array: 9 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"Check boxes",
		'LSTC',
		/* [3] */
		"Checkbox",
		'DWRD',
		/* [4] */
		"*****",
		'LSTE',
		/* [5] */
		"Count:",
		'OCNT',
		/* [6] */
		"Radio buttons",
		'LSTC',
		/* [7] */
		"Rads from",
		'DWRD',
		/* [8] */
		"Rads to",
		'DWRD',
		/* [9] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1064, "deta") {
	{	/* array: 9 elements */
		/* [1] */
		"Aspect template",
		'DVDR',
		/* [2] */
		"Version",
		'DLNG',
		/* [3] */
		"Latest=-976",
		'CASE',
		/* [4] */
		"Drop operation priority",
		'DLNG',
		/* [5] */
		"Drop destination check",
		'WBIT',
		/* [6] */
		"Only if there's a conflict=No",
		'CASE',
		/* [7] */
		"Always check with user=Yes",
		'CASE',
		/* [8] */
		"Is the main aspect",
		'WBIT',
		/* [9] */
		"Reserved",
		'WB14'
	}
};

resource 'TMPL' (1065, "detf") {
	{	/* array: 2 elements */
		/* [1] */
		"Version",
		'DLNG',
		/* [2] */
		"Latest=-976",
		'CASE'
	}
};

resource 'TMPL' (1066, "deti") {
	{	/* array: 18 elements */
		/* [1] */
		"Version",
		'DLNG',
		/* [2] */
		"Info page=-976",
		'CASE',
		/* [3] */
		"Sort order",
		'DLNG',
		/* [4] */
		"Sublist bounds",
		'RECT',
		/* [5] */
		"Don't select first text field",
		'WBIT',
		/* [6] */
		"Reserved",
		'WB15',
		/* [7] */
		"Count:",
		'OCNT',
		/* [8] */
		"List of Header views",
		'LSTC',
		/* [9] */
		"Property 1",
		'DWRD',
		/* [10] */
		"Property 2",
		'DWRD',
		/* [11] */
		"'detv' resource ID",
		'RSID',
		/* [12] */
		"*****",
		'LSTE',
		/* [13] */
		"Count:",
		'OCNT',
		/* [14] */
		"List of Subviews",
		'LSTC',
		/* [15] */
		"Property 1",
		'DWRD',
		/* [16] */
		"Property 2",
		'DWRD',
		/* [17] */
		"'detv' resource ID",
		'RSID',
		/* [18] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1067, "detk") {
	{	/* array: 2 elements */
		/* [1] */
		"Version",
		'DLNG',
		/* [2] */
		"Latest=-976",
		'CASE'
	}
};

resource 'TMPL' (1068, "detn") {
	{	/* array: 1 elements */
		/* [1] */
		"A decimal number",
		'DLNG'
	}
};

resource 'TMPL' (1069, "detp") {
	{	/* array: 4 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"List of properties",
		'LSTC',
		/* [3] */
		"Property number",
		'DWRD',
		/* [4] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1070, "dett") {
	{	/* array: 56 elements */
		/* [1] */
		"Attribute pattern table",
		'DVDR',
		/* [2] */
		"Count:",
		'OCNT',
		/* [3] */
		"List of Attributes",
		'LSTC',
		/* [4] */
		"Count:",
		'OCNT',
		/* [5] */
		"List of Types",
		'LSTC',
		/* [6] */
		"Script region code",
		'SCPC',
		/* [7] */
		"Filler for length",
		'FBYT',
		/* [8] */
		"Type string",
		'P021',
		/* [9] */
		"*****",
		'LSTE',
		/* [10] */
		"Attribute tag",
		'DLNG',
		/* [11] */
		"Match all=0",
		'CASE',
		/* [12] */
		"Use pattern for input processing",
		'WBIT',
		/* [13] */
		"Use pattern for output processing",
		'WBIT',
		/* [14] */
		"Include this attribute in sub-list",
		'WBIT',
		/* [15] */
		"Mark attribute as an alias",
		'WBIT',
		/* [16] */
		"Mark attribute as a record ref",
		'WBIT',
		/* [17] */
		"Reserved",
		'WB11',
		/* [18] */
		"Count:",
		'OCNT',
		/* [19] */
		"List of Patterns",
		'LSTC',
		/* [20] */
		"Element type",
		'TNAM',
		/* [21] */
		"Regionalized string=rstr",
		'CASE',
		/* [22] */
		"Byte=byte",
		'CASE',
		/* [23] */
		"Word=word",
		'CASE',
		/* [24] */
		"Long=long",
		'CASE',
		/* [25] */
		"Pascal string=pstr",
		'CASE',
		/* [26] */
		"Word string=wstr",
		'CASE',
		/* [27] */
		"C string=cstr",
		'CASE',
		/* [28] */
		"Four-character type=type",
		'CASE',
		/* [29] */
		"Block of <extra> bytes=blok",
		'CASE',
		/* [30] */
		"Binary bit=bbit",
		'CASE',
		/* [31] */
		"Align to byte=abyt",
		'CASE',
		/* [32] */
		"Align to word=awrd",
		'CASE',
		/* [33] */
		"Align to long=alng",
		'CASE',
		/* [34] */
		"Begin block=((((",
		'CASE',
		/* [35] */
		"End block=))))",
		'CASE',
		/* [36] */
		"Byte-sized size=bsiz",
		'CASE',
		/* [37] */
		"Word-sized size=wsiz",
		'CASE',
		/* [38] */
		"Long-sized size=lsiz",
		'CASE',
		/* [39] */
		"Pad with zeros=padz",
		'CASE',
		/* [40] */
		"Set main property from extra=p:=p",
		'CASE',
		/* [41] */
		"Main equals extra=equa",
		'CASE',
		/* [42] */
		"Main not equals extra=nteq",
		'CASE',
		/* [43] */
		"Main < extra=less",
		'CASE',
		/* [44] */
		"Main > extra=grea",
		'CASE',
		/* [45] */
		"Main ¬d extra=leeq",
		'CASE',
		/* [46] */
		"Main ¬e extra=greq",
		'CASE',
		/* [47] */
		"Is input and/or output=prop",
		'CASE',
		/* [48] */
		"Set type to extra=styp",
		'CASE',
		/* [49] */
		"Use extra as type of all following binar"
		"y=btyp",
		'CASE',
		/* [50] */
		"Abort pattern processing=abrt",
		'CASE',
		/* [51] */
		"Abort and disable aspect=disa",
		'CASE',
		/* [52] */
		"Enable the aspect=enab",
		'CASE',
		/* [53] */
		"Property number",
		'DWRD',
		/* [54] */
		"Extra",
		'DWRD',
		/* [55] */
		"*****",
		'LSTE',
		/* [56] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1071, "detv") {
	{	/* array: 104 elements */
		/* [1] */
		"Filler",
		'F028',
		/* [2] */
		"Count:",
		'OCNT',
		/* [3] */
		"List of Items",
		'LSTC',
		/* [4] */
		"Bounds",
		'RECT',
		/* [5] */
		"Position flags (autoset by DE)",
		'DLNG',
		/* [6] */
		"Flags",
		'DLNG',
		/* [7] */
		"Property code",
		'DWRD',
		/* [8] */
		"Item type",
		'KLNG',
		/* [9] */
		"Static text from view=7750",
		'CASE',
		/* [10] */
		"Static command text from view=22250",
		'CASE',
		/* [11] */
		"Static text=3250",
		'CASE',
		/* [12] */
		"Edit text=8250",
		'CASE',
		/* [13] */
		"Bitmap=6250",
		'CASE',
		/* [14] */
		"Box=4750",
		'CASE',
		/* [15] */
		"Default button=7250",
		'CASE',
		/* [16] */
		"Button=21000",
		'CASE',
		/* [17] */
		"Check box=21250",
		'CASE',
		/* [18] */
		"Radio button=21500",
		'CASE',
		/* [19] */
		"Menu=5750",
		'CASE',
		/* [20] */
		"Edit Picture=89786",
		'CASE',
		/* [21] */
		"Custom=6750",
		'CASE',
		/* [22] */
		"7750",
		'KEYB',
		/* [23] */
		"Font number",
		'DWRD',
		/* [24] */
		"Font size",
		'DWRD',
		/* [25] */
		"Justification",
		'DWRD',
		/* [26] */
		"Style",
		'DWRD',
		/* [27] */
		"Title",
		'ESTR',
		/* [28] */
		"",
		'KEYE',
		/* [29] */
		"22250",
		'KEYB',
		/* [30] */
		"Font number",
		'DWRD',
		/* [31] */
		"Font size",
		'DWRD',
		/* [32] */
		"Justification",
		'DWRD',
		/* [33] */
		"Style",
		'DWRD',
		/* [34] */
		"Title",
		'ESTR',
		/* [35] */
		"Command",
		'DLNG',
		/* [36] */
		"Value",
		'DWRD',
		/* [37] */
		"",
		'KEYE',
		/* [38] */
		"3250",
		'KEYB',
		/* [39] */
		"Font number",
		'DWRD',
		/* [40] */
		"Font size",
		'DWRD',
		/* [41] */
		"Justification",
		'DWRD',
		/* [42] */
		"Style",
		'DWRD',
		/* [43] */
		"",
		'KEYE',
		/* [44] */
		"8250",
		'KEYB',
		/* [45] */
		"Font number",
		'DWRD',
		/* [46] */
		"Font size",
		'DWRD',
		/* [47] */
		"Justification",
		'DWRD',
		/* [48] */
		"Style",
		'DWRD',
		/* [49] */
		"",
		'KEYE',
		/* [50] */
		"6250",
		'KEYB',
		/* [51] */
		"Size",
		'DWRD',
		/* [52] */
		"",
		'KEYE',
		/* [53] */
		"4750",
		'KEYB',
		/* [54] */
		"Attributes",
		'DWRD',
		/* [55] */
		"",
		'KEYE',
		/* [56] */
		"7250",
		'KEYB',
		/* [57] */
		"Font number",
		'DWRD',
		/* [58] */
		"Font size",
		'DWRD',
		/* [59] */
		"Justification",
		'DWRD',
		/* [60] */
		"Style",
		'DWRD',
		/* [61] */
		"Title",
		'ESTR',
		/* [62] */
		"Command",
		'DLNG',
		/* [63] */
		"",
		'KEYE',
		/* [64] */
		"21000",
		'KEYB',
		/* [65] */
		"Font number",
		'DWRD',
		/* [66] */
		"Font size",
		'DWRD',
		/* [67] */
		"Justification",
		'DWRD',
		/* [68] */
		"Style",
		'DWRD',
		/* [69] */
		"Title",
		'ESTR',
		/* [70] */
		"Command",
		'DLNG',
		/* [71] */
		"",
		'KEYE',
		/* [72] */
		"21250",
		'KEYB',
		/* [73] */
		"Font number",
		'DWRD',
		/* [74] */
		"Font size",
		'DWRD',
		/* [75] */
		"Justification",
		'DWRD',
		/* [76] */
		"Style",
		'DWRD',
		/* [77] */
		"Title",
		'ESTR',
		/* [78] */
		"Command",
		'DLNG',
		/* [79] */
		"",
		'KEYE',
		/* [80] */
		"21500",
		'KEYB',
		/* [81] */
		"Font number",
		'DWRD',
		/* [82] */
		"Font size",
		'DWRD',
		/* [83] */
		"Justification",
		'DWRD',
		/* [84] */
		"Style",
		'DWRD',
		/* [85] */
		"Title",
		'ESTR',
		/* [86] */
		"Command",
		'DLNG',
		/* [87] */
		"Value",
		'DWRD',
		/* [88] */
		"",
		'KEYE',
		/* [89] */
		"5750",
		'KEYB',
		/* [90] */
		"Font number",
		'DWRD',
		/* [91] */
		"Font size",
		'DWRD',
		/* [92] */
		"Justification",
		'DWRD',
		/* [93] */
		"Style",
		'DWRD',
		/* [94] */
		"Title",
		'ESTR',
		/* [95] */
		"Command",
		'DLNG',
		/* [96] */
		"'detm' resource ID",
		'RSID',
		/* [97] */
		"",
		'KEYE',
		/* [98] */
		"94786",
		'KEYB',
		/* [99] */
		"Maximum pixel depth",
		'DWRD',
		/* [100] */
		"",
		'KEYE',
		/* [101] */
		"6750",
		'KEYB',
		/* [102] */
		"User reference",
		'DWRD',
		/* [103] */
		"",
		'KEYE',
		/* [104] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1072, "detw") {
	{	/* array: 6 elements */
		/* [1] */
		"If top of bounds is 0, use standard plac"
		"ement",
		'DVDR',
		/* [2] */
		"If top of bounds is -1, center on screen",
		'DVDR',
		/* [3] */
		"Otherwise, use bounds as absolute placem"
		"ent",
		'DVDR',
		/* [4] */
		"Bounds",
		'RECT',
		/* [5] */
		"Include page selection popup",
		'WBIT',
		/* [6] */
		"Reserved",
		'WB15'
	}
};

resource 'TMPL' (1073, "detx") {
	{	/* array: 6 elements */
		/* [1] */
		"Version",
		'DLNG',
		/* [2] */
		"Latest=-976",
		'CASE',
		/* [3] */
		"Count:",
		'OCNT',
		/* [4] */
		"Extra file types",
		'LSTC',
		/* [5] */
		"File type",
		'TNAM',
		/* [6] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1074, "dflg") {
	{	/* array: 3 elements */
		/* [1] */
		"Version",
		'HLNG',
		/* [2] */
		"Reserved",
		'LB31',
		/* [3] */
		"Async supported",
		'LB01'
	}
};

resource 'TMPL' (1075, "dftb") {
	{	/* array: 49 elements */
		/* [1] */
		"Version",
		'KWRD',
		/* [2] */
		"Latest=0",
		'CASE',
		/* [3] */
		"0",
		'KEYB',
		/* [4] */
		"Count:",
		'OCNT',
		/* [5] */
		"Font styles",
		'LSTC',
		/* [6] */
		"Entry Type",
		'KWRD',
		/* [7] */
		"Skip Item=0",
		'CASE',
		/* [8] */
		"Data Item=1",
		'CASE',
		/* [9] */
		"0",
		'KEYB',
		/* [10] */
		"",
		'KEYE',
		/* [11] */
		"1",
		'KEYB',
		/* [12] */
		"Reserved",
		'WB06',
		/* [13] */
		"Use font name",
		'WBIT',
		/* [14] */
		"Add font size",
		'WBIT',
		/* [15] */
		"Reserved",
		'WBIT',
		/* [16] */
		"Use justification",
		'WBIT',
		/* [17] */
		"Use mode",
		'WBIT',
		/* [18] */
		"Use background color",
		'WBIT',
		/* [19] */
		"Use foreground color",
		'WBIT',
		/* [20] */
		"Use size",
		'WBIT',
		/* [21] */
		"Use face",
		'WBIT',
		/* [22] */
		"Use font",
		'WBIT',
		/* [23] */
		"",
		'DVDR',
		/* [24] */
		"Font number",
		'DWRD',
		/* [25] */
		"System font=0",
		'CASE',
		/* [26] */
		"Big system font=-1",
		'CASE',
		/* [27] */
		"Small system font=-2",
		'CASE',
		/* [28] */
		"Small emphasized system font=-3",
		'CASE',
		/* [29] */
		"Font Size",
		'DWRD',
		/* [30] */
		"Unused",
		'WB09',
		/* [31] */
		"Extended",
		'WBIT',
		/* [32] */
		"Condensed",
		'WBIT',
		/* [33] */
		"Shadow",
		'WBIT',
		/* [34] */
		"Outline",
		'WBIT',
		/* [35] */
		"Underline",
		'WBIT',
		/* [36] */
		"Italic",
		'WBIT',
		/* [37] */
		"Bold",
		'WBIT',
		/* [38] */
		"Text mode",
		'DWRD',
		/* [39] */
		"Justification",
		'DWRD',
		/* [40] */
		"Flush Default=0",
		'CASE',
		/* [41] */
		"Center=1",
		'CASE',
		/* [42] */
		"Flush Right=-1",
		'CASE',
		/* [43] */
		"Flush Left=-2",
		'CASE',
		/* [44] */
		"Foreground color",
		'COLR',
		/* [45] */
		"Background color",
		'COLR',
		/* [46] */
		"Font name",
		'PSTR',
		/* [47] */
		"",
		'KEYE',
		/* [48] */
		"*****",
		'LSTE',
		/* [49] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1076, "DITL") {
	{	/* array: 13 elements */
		/* [1] */
		"Count:",
		'ZCNT',
		/* [2] */
		"List of Items",
		'LSTC',
		/* [3] */
		"Place holder",
		'FLNG',
		/* [4] */
		"Display rect",
		'RECT',
		/* [5] */
		"Disable item",
		'BBIT',
		/* [6] */
		"Picture item",
		'BBIT',
		/* [7] */
		"Icon item",
		'BBIT',
		/* [8] */
		"Edit text item",
		'BBIT',
		/* [9] */
		"Static text item",
		'BBIT',
		/* [10] */
		"This item is a control",
		'BBIT',
		/* [11] */
		"Standard control",
		'BB02',
		/* [12] */
		"Item info",
		'OSTR',
		/* [13] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1077, "dJvU") {
	{	/* array: 7 elements */
		/* [1] */
		"\"Eudora\" resource format",
		'DVDR',
		/* [2] */
		"wType",
		'DWRD',
		/* [3] */
		"Dir Id",
		'DLNG',
		/* [4] */
		"Index",
		'DWRD',
		/* [5] */
		"Volume name",
		'P01F',
		/* [6] */
		"Name",
		'P01F',
		/* [7] */
		"Alias",
		'P01F'
	}
};

resource 'TMPL' (1078, "DLGf") {
	{	/* array: 8 elements */
		/* [1] */
		"\"Finale\" resource format",
		'DVDR',
		/* [2] */
		"'FSty' resource",
		'RSID',
		/* [3] */
		"DLGFONTFLAGS",
		'DBYT',
		/* [4] */
		"Default=0",
		'CASE',
		/* [5] */
		"GrafPort=1",
		'CASE',
		/* [6] */
		"TEFont=2",
		'CASE',
		/* [7] */
		"TEAndGrafPort=3",
		'CASE',
		/* [8] */
		"Filler",
		'FBYT'
	}
};

resource 'TMPL' (1079, "dlgx") {
	{	/* array: 9 elements */
		/* [1] */
		"Version",
		'KWRD',
		/* [2] */
		"Latest=0",
		'CASE',
		/* [3] */
		"0",
		'KEYB',
		/* [4] */
		"Reserved",
		'LB28',
		/* [5] */
		"Use theme controls",
		'LBIT',
		/* [6] */
		"Alert is movable modal",
		'LBIT',
		/* [7] */
		"Use control hierarchy",
		'LBIT',
		/* [8] */
		"Use theme background",
		'LBIT',
		/* [9] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1080, "dlle") {
	{	/* array: 1 elements */
		/* [1] */
		"String for multi-platform things",
		'CSTR'
	}
};

resource 'TMPL' (1081, "DLOG") {
	{	/* array: 28 elements */
		/* [1] */
		"BoundsRect",
		'RECT',
		/* [2] */
		"ProcID",
		'DWRD',
		/* [3] */
		"documentProc=0",
		'CASE',
		/* [4] */
		"dBoxProc=1",
		'CASE',
		/* [5] */
		"plainDBox=2",
		'CASE',
		/* [6] */
		"altDBoxProc=3",
		'CASE',
		/* [7] */
		"noGrowDocProc=4",
		'CASE',
		/* [8] */
		"movableDBoxProc=5",
		'CASE',
		/* [9] */
		"zoomDocProc=8",
		'CASE',
		/* [10] */
		"zoomNoGrow=12",
		'CASE',
		/* [11] */
		"rDocProc=16",
		'CASE',
		/* [12] */
		"Visible",
		'BOOL',
		/* [13] */
		"GoAway",
		'BOOL',
		/* [14] */
		"RefCon",
		'DLNG',
		/* [15] */
		"DITL ID (items list)",
		'RSID',
		/* [16] */
		"Title",
		'PSTR',
		/* [17] */
		"Align",
		'AWRD',
		/* [18] */
		"Dialog positioning",
		'HWRD',
		/* [19] */
		"No auto center=$0000",
		'CASE',
		/* [20] */
		"Center on main screen=$280A",
		'CASE',
		/* [21] */
		"Center in parent window=$A80A",
		'CASE',
		/* [22] */
		"Center on parent's screen=$680A",
		'CASE',
		/* [23] */
		"Alert on main screen=$300A",
		'CASE',
		/* [24] */
		"Alert in parent window=$B00A",
		'CASE',
		/* [25] */
		"Alert in parent's screen=$700A",
		'CASE',
		/* [26] */
		"Stagger on main screen=$380A",
		'CASE',
		/* [27] */
		"Stagger in parent window=$B80A",
		'CASE',
		/* [28] */
		"Stagger on parent's screen=$780A",
		'CASE'
	}
};

resource 'TMPL' (1082, "DRVR") {
	{	/* array: 35 elements */
		/* [1] */
		"Unused (should be 0)",
		'BBIT',
		/* [2] */
		"Lock driver in memory",
		'BBIT',
		/* [3] */
		"Need time for periodic action",
		'BBIT',
		/* [4] */
		"Say goodbye before heap reinit",
		'BBIT',
		/* [5] */
		"Responds to status message",
		'BBIT',
		/* [6] */
		"Responds to control message",
		'BBIT',
		/* [7] */
		"Responds to write message",
		'BBIT',
		/* [8] */
		"Responds to read message",
		'BBIT',
		/* [9] */
		"Reserved (should be 0)",
		'FBYT',
		/* [10] */
		"Driver delay (ticks)",
		'DWRD',
		/* [11] */
		"Desk acc event mask",
		'DVDR',
		/* [12] */
		"Suspend/Resume",
		'WBIT',
		/* [13] */
		"app3Evt",
		'WBIT',
		/* [14] */
		"app2Evt",
		'WBIT',
		/* [15] */
		"app1Evt",
		'WBIT',
		/* [16] */
		"driverEvt",
		'WBIT',
		/* [17] */
		"networkEvt",
		'WBIT',
		/* [18] */
		"(unused)",
		'WBIT',
		/* [19] */
		"activateEvt",
		'WBIT',
		/* [20] */
		"disk insert",
		'WBIT',
		/* [21] */
		"updateEvt",
		'WBIT',
		/* [22] */
		"autoKey",
		'WBIT',
		/* [23] */
		"keyUp",
		'WBIT',
		/* [24] */
		"keyDown",
		'WBIT',
		/* [25] */
		"mouseUp",
		'WBIT',
		/* [26] */
		"mouseDown",
		'WBIT',
		/* [27] */
		"null event",
		'WBIT',
		/* [28] */
		"Driver menu ID",
		'DWRD',
		/* [29] */
		"Offset to DRVRRuntime open (50)",
		'UWRD',
		/* [30] */
		"Offset to DRVRRuntime prime (54)",
		'UWRD',
		/* [31] */
		"Offset to DRVRRuntime control (58)",
		'UWRD',
		/* [32] */
		"Offset to DRVRRuntime status (62)",
		'UWRD',
		/* [33] */
		"Offset to DRVRRuntime close (64)",
		'UWRD',
		/* [34] */
		"Driver name",
		'P020',
		/* [35] */
		"Driver hexadecimal code",
		'HEXD'
	}
};

resource 'TMPL' (1083, "DSAT") {
	{	/* array: 6 elements */
		/* [1] */
		"Alerts",
		'OCNT',
		/* [2] */
		"Definitions list",
		'LSTC',
		/* [3] */
		"Definition ID",
		'DWRD',
		/* [4] */
		"Definition",
		'WSTR',
		/* [5] */
		"*****",
		'LSTE',
		/* [6] */
		"Hexadecimal dump",
		'HEXD'
	}
};

resource 'TMPL' (1084, "DSPC") {
	{	/* array: 271 elements */
		/* [1] */
		"Version Number",
		'KWRD',
		/* [2] */
		"CW10=1",
		'CASE',
		/* [3] */
		"1",
		'KEYB',
		/* [4] */
		"List of objects",
		'LSTB',
		/* [5] */
		"Object type",
		'KTYP',
		/* [6] */
		"Object data=objd",
		'CASE',
		/* [7] */
		"Begin sub-object list=begs",
		'CASE',
		/* [8] */
		"End sub-object list=ends",
		'CASE',
		/* [9] */
		"User object=user",
		'CASE',
		/* [10] */
		"Class alias=dopl",
		'CASE',
		/* [11] */
		"End of list=end.",
		'CASE',
		/* [12] */
		"objd",
		'KEYB',
		/* [13] */
		"Number of bytes in following data",
		'LSIZ',
		/* [14] */
		"Data type",
		'KTYP',
		/* [15] */
		"Object=obj ",
		'CASE',
		/* [16] */
		"Integer attribute=intv",
		'CASE',
		/* [17] */
		"Labelled integer attribute=labi",
		'CASE',
		/* [18] */
		"Min/max integer attribute=mimx",
		'CASE',
		/* [19] */
		"Res list attribute=resl",
		'CASE',
		/* [20] */
		"Resource reference attribute=rerf",
		'CASE',
		/* [21] */
		"String attribute=pstr",
		'CASE',
		/* [22] */
		"Font string attribute=fstr",
		'CASE',
		/* [23] */
		"Name or ordinal attribute=nord",
		'CASE',
		/* [24] */
		"RGB color attribute=rgbc",
		'CASE',
		/* [25] */
		"Container attribute=cont",
		'CASE',
		/* [26] */
		"List attribute=list",
		'CASE',
		/* [27] */
		"Bitfield container attribute=bitf",
		'CASE',
		/* [28] */
		"Value label=labl",
		'CASE',
		/* [29] */
		"Resource container=rsco",
		'CASE',
		/* [30] */
		"View editor type list=vetl",
		'CASE',
		/* [31] */
		"Custom type object=ctmo",
		'CASE',
		/* [32] */
		"Null=null",
		'CASE',
		/* [33] */
		"obj ",
		'KEYB',
		/* [34] */
		"",
		'KEYE',
		/* [35] */
		"intv",
		'KEYB',
		/* [36] */
		"DMAttribute data",
		'DVDR',
		/* [37] */
		"Attribute title",
		'PSTR',
		/* [38] */
		"Attribute key",
		'TNAM',
		/* [39] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [40] */
		"Write to stream?",
		'BFLG',
		/* [41] */
		"Stream selector",
		'TNAM',
		/* [42] */
		"DMIntegerAttribute data",
		'DVDR',
		/* [43] */
		"Default value",
		'DLNG',
		/* [44] */
		"Value size (bits)",
		'UWRD',
		/* [45] */
		"Signed integer?",
		'BFLG',
		/* [46] */
		"Can be text value?",
		'BFLG',
		/* [47] */
		"Always is text value?",
		'BFLG',
		/* [48] */
		"",
		'KEYE',
		/* [49] */
		"labi",
		'KEYB',
		/* [50] */
		"DMAttribute data",
		'DVDR',
		/* [51] */
		"Attribute title",
		'PSTR',
		/* [52] */
		"Attribute key",
		'TNAM',
		/* [53] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [54] */
		"Write to stream?",
		'BFLG',
		/* [55] */
		"Stream selector",
		'TNAM',
		/* [56] */
		"DMIntegerAttribute data",
		'DVDR',
		/* [57] */
		"Default value",
		'DLNG',
		/* [58] */
		"Value size (bits)",
		'UWRD',
		/* [59] */
		"Signed integer?",
		'BFLG',
		/* [60] */
		"Can be text value?",
		'BFLG',
		/* [61] */
		"Always is text value?",
		'BFLG',
		/* [62] */
		"DMLabelledIntegerAttribute data",
		'DVDR',
		/* [63] */
		"Labels only?",
		'BFLG',
		/* [64] */
		"",
		'KEYE',
		/* [65] */
		"mimx",
		'KEYB',
		/* [66] */
		"DMAttribute data",
		'DVDR',
		/* [67] */
		"Attribute title",
		'PSTR',
		/* [68] */
		"Attribute key",
		'TNAM',
		/* [69] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [70] */
		"Write to stream?",
		'BFLG',
		/* [71] */
		"Stream selector",
		'TNAM',
		/* [72] */
		"DMIntegerAttribute data",
		'DVDR',
		/* [73] */
		"Default value",
		'DLNG',
		/* [74] */
		"Value size (bits)",
		'UWRD',
		/* [75] */
		"Signed integer?",
		'BFLG',
		/* [76] */
		"Can be text value?",
		'BFLG',
		/* [77] */
		"Always is text value?",
		'BFLG',
		/* [78] */
		"DMMinMaxIntegerAttribute data",
		'DVDR',
		/* [79] */
		"Minimum value",
		'DLNG',
		/* [80] */
		"Maximum value",
		'DLNG',
		/* [81] */
		"",
		'KEYE',
		/* [82] */
		"resl",
		'KEYB',
		/* [83] */
		"DMAttribute data",
		'DVDR',
		/* [84] */
		"Attribute title",
		'PSTR',
		/* [85] */
		"Attribute key",
		'TNAM',
		/* [86] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [87] */
		"Write to stream?",
		'BFLG',
		/* [88] */
		"Stream selector",
		'TNAM',
		/* [89] */
		"DMIntegerAttribute data",
		'DVDR',
		/* [90] */
		"Default value",
		'DLNG',
		/* [91] */
		"Value size (bits)",
		'UWRD',
		/* [92] */
		"Signed integer?",
		'BFLG',
		/* [93] */
		"Can be text value?",
		'BFLG',
		/* [94] */
		"Always is text value?",
		'BFLG',
		/* [95] */
		"DMLabelledIntegerAttribute data",
		'DVDR',
		/* [96] */
		"Labels only?",
		'BFLG',
		/* [97] */
		"DMResListAttribute data",
		'DVDR',
		/* [98] */
		"Resource type",
		'TNAM',
		/* [99] */
		"",
		'KEYE',
		/* [100] */
		"rerf",
		'KEYB',
		/* [101] */
		"DMAttribute data",
		'DVDR',
		/* [102] */
		"Attribute title",
		'PSTR',
		/* [103] */
		"Attribute key",
		'TNAM',
		/* [104] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [105] */
		"Write to stream?",
		'BFLG',
		/* [106] */
		"Stream selector",
		'TNAM',
		/* [107] */
		"DMIntegerAttribute data",
		'DVDR',
		/* [108] */
		"Default value",
		'DLNG',
		/* [109] */
		"Value size (bits)",
		'UWRD',
		/* [110] */
		"Signed integer?",
		'BFLG',
		/* [111] */
		"Can be text value?",
		'BFLG',
		/* [112] */
		"Always is text value?",
		'BFLG',
		/* [113] */
		"DMResourceRefAttribute data",
		'DVDR',
		/* [114] */
		"Resource type",
		'TNAM',
		/* [115] */
		"",
		'KEYE',
		/* [116] */
		"pstr",
		'KEYB',
		/* [117] */
		"DMAttribute data",
		'DVDR',
		/* [118] */
		"Attribute title",
		'PSTR',
		/* [119] */
		"Attribute key",
		'TNAM',
		/* [120] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [121] */
		"Write to stream?",
		'BFLG',
		/* [122] */
		"Stream selector",
		'TNAM',
		/* [123] */
		"DMStringAttribute data",
		'DVDR',
		/* [124] */
		"Default value",
		'PSTR',
		/* [125] */
		"Maximum length (characters)",
		'UWRD',
		/* [126] */
		"Even padded?",
		'BFLG',
		/* [127] */
		"(unused)",
		'BB03',
		/* [128] */
		"Unicode string?",
		'BBIT',
		/* [129] */
		"Hex entry?",
		'BBIT',
		/* [130] */
		"Accept CR?",
		'BBIT',
		/* [131] */
		"C style string?",
		'BBIT',
		/* [132] */
		"Odd padded?",
		'BBIT',
		/* [133] */
		"",
		'KEYE',
		/* [134] */
		"fstr",
		'KEYB',
		/* [135] */
		"DMAttribute data",
		'DVDR',
		/* [136] */
		"Attribute title",
		'PSTR',
		/* [137] */
		"Attribute key",
		'TNAM',
		/* [138] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [139] */
		"Write to stream?",
		'BFLG',
		/* [140] */
		"Stream selector",
		'TNAM',
		/* [141] */
		"DMStringAttribute data",
		'DVDR',
		/* [142] */
		"Default value",
		'PSTR',
		/* [143] */
		"Maximum length (characters)",
		'UWRD',
		/* [144] */
		"Even padded?",
		'BFLG',
		/* [145] */
		"(unused)",
		'BB03',
		/* [146] */
		"Unicode string?",
		'BBIT',
		/* [147] */
		"Hex entry?",
		'BBIT',
		/* [148] */
		"Accept CR?",
		'BBIT',
		/* [149] */
		"C style string?",
		'BBIT',
		/* [150] */
		"Odd padded?",
		'BBIT',
		/* [151] */
		"DMFontStringAttribute data",
		'DVDR',
		/* [152] */
		"Default font number",
		'DWRD',
		/* [153] */
		"Write font number?",
		'BFLG',
		/* [154] */
		"Include system font?",
		'BFLG',
		/* [155] */
		"Include application font?",
		'BFLG',
		/* [156] */
		"Include hidden fonts?",
		'BFLG',
		/* [157] */
		"",
		'KEYE',
		/* [158] */
		"nord",
		'KEYB',
		/* [159] */
		"DMAttribute data",
		'DVDR',
		/* [160] */
		"Attribute title",
		'PSTR',
		/* [161] */
		"Attribute key",
		'TNAM',
		/* [162] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [163] */
		"Write to stream?",
		'BFLG',
		/* [164] */
		"Stream selector",
		'TNAM',
		/* [165] */
		"DMStringAttribute data",
		'DVDR',
		/* [166] */
		"Default value",
		'PSTR',
		/* [167] */
		"Maximum length (characters)",
		'UWRD',
		/* [168] */
		"Even padded?",
		'BFLG',
		/* [169] */
		"(unused)",
		'BB03',
		/* [170] */
		"Unicode string?",
		'BBIT',
		/* [171] */
		"Hex entry?",
		'BBIT',
		/* [172] */
		"Accept CR?",
		'BBIT',
		/* [173] */
		"C style string?",
		'BBIT',
		/* [174] */
		"Odd padded?",
		'BBIT',
		/* [175] */
		"DMNameOrOrdinalValue data",
		'DVDR',
		/* [176] */
		"Numeric value",
		'DLNG',
		/* [177] */
		"Numeric value size",
		'UWRD',
		/* [178] */
		"Signed integer?",
		'BFLG',
		/* [179] */
		"Is numeric value?",
		'BFLG',
		/* [180] */
		"",
		'KEYE',
		/* [181] */
		"rgbc",
		'KEYB',
		/* [182] */
		"DMAttribute data",
		'DVDR',
		/* [183] */
		"Attribute title",
		'PSTR',
		/* [184] */
		"Attribute key",
		'TNAM',
		/* [185] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [186] */
		"Write to stream?",
		'BFLG',
		/* [187] */
		"Stream selector",
		'TNAM',
		/* [188] */
		"DMRGBColorAttribute data",
		'DVDR',
		/* [189] */
		"Default value",
		'COLR',
		/* [190] */
		"",
		'KEYE',
		/* [191] */
		"cont",
		'KEYB',
		/* [192] */
		"DMAttribute data",
		'DVDR',
		/* [193] */
		"Attribute title",
		'PSTR',
		/* [194] */
		"Attribute key",
		'TNAM',
		/* [195] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [196] */
		"Write to stream?",
		'BFLG',
		/* [197] */
		"Stream selector",
		'TNAM',
		/* [198] */
		"DMContainerAttribute data",
		'DVDR',
		/* [199] */
		"Is subobject list?",
		'BFLG',
		/* [200] */
		"Member class ID",
		'TNAM',
		/* [201] */
		"",
		'KEYE',
		/* [202] */
		"list",
		'KEYB',
		/* [203] */
		"DMAttribute data",
		'DVDR',
		/* [204] */
		"Attribute title",
		'PSTR',
		/* [205] */
		"Attribute key",
		'TNAM',
		/* [206] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [207] */
		"Write to stream?",
		'BFLG',
		/* [208] */
		"Stream selector",
		'TNAM',
		/* [209] */
		"DMContainerAttribute data",
		'DVDR',
		/* [210] */
		"Is subobject list?",
		'BFLG',
		/* [211] */
		"Member class ID",
		'TNAM',
		/* [212] */
		"DMListAttribute data",
		'DVDR',
		/* [213] */
		"Subitem title",
		'PSTR',
		/* [214] */
		"Number of bytes for count",
		'DLNG',
		/* [215] */
		"unused",
		'BB06',
		/* [216] */
		"Zero based display?",
		'BB01',
		/* [217] */
		"Zero-based count?",
		'BB01',
		/* [218] */
		"",
		'KEYE',
		/* [219] */
		"bitf",
		'KEYB',
		/* [220] */
		"DMAttribute data",
		'DVDR',
		/* [221] */
		"Attribute title",
		'PSTR',
		/* [222] */
		"Attribute key",
		'TNAM',
		/* [223] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [224] */
		"Write to stream?",
		'BFLG',
		/* [225] */
		"Stream selector",
		'TNAM',
		/* [226] */
		"DMContainerAttribute data",
		'DVDR',
		/* [227] */
		"Is subobject list?",
		'BFLG',
		/* [228] */
		"Member class ID",
		'TNAM',
		/* [229] */
		"DMBitfieldAttribute data",
		'DVDR',
		/* [230] */
		"Bitfield size (bytes)",
		'UWRD',
		/* [231] */
		"",
		'KEYE',
		/* [232] */
		"labl",
		'KEYB',
		/* [233] */
		"Value",
		'DLNG',
		/* [234] */
		"Label",
		'PSTR',
		/* [235] */
		"",
		'KEYE',
		/* [236] */
		"rsco",
		'KEYB',
		/* [237] */
		"CTYP for resource type",
		'DWRD',
		/* [238] */
		"CTYP for resource",
		'DWRD',
		/* [239] */
		"Resource IDs significant?",
		'BFLG',
		/* [240] */
		"",
		'KEYE',
		/* [241] */
		"vetl",
		'KEYB',
		/* [242] */
		"VECP resource ID",
		'DWRD',
		/* [243] */
		"Class IDs significant?",
		'BFLG',
		/* [244] */
		"",
		'KEYE',
		/* [245] */
		"ctmo",
		'KEYB',
		/* [246] */
		"Object type",
		'PSTR',
		/* [247] */
		"Object type ID",
		'TNAM',
		/* [248] */
		"Parent type ID",
		'TNAM',
		/* [249] */
		"",
		'KEYE',
		/* [250] */
		"null",
		'KEYB',
		/* [251] */
		"",
		'KEYE',
		/* [252] */
		"",
		'KEYB',
		/* [253] */
		"Unknown data",
		'HEXD',
		/* [254] */
		"",
		'KEYE',
		/* [255] */
		"",
		'SKPE',
		/* [256] */
		"",
		'KEYE',
		/* [257] */
		"begs",
		'KEYB',
		/* [258] */
		"",
		'KEYE',
		/* [259] */
		"ends",
		'KEYB',
		/* [260] */
		"",
		'KEYE',
		/* [261] */
		"user",
		'KEYB',
		/* [262] */
		"SuperClass ID for next object",
		'TNAM',
		/* [263] */
		"",
		'KEYE',
		/* [264] */
		"dopl",
		'KEYB',
		/* [265] */
		"Class ID for next object",
		'TNAM',
		/* [266] */
		"",
		'KEYE',
		/* [267] */
		"end.",
		'KEYB',
		/* [268] */
		"This must be last object type in list",
		'DVDR',
		/* [269] */
		"",
		'KEYE',
		/* [270] */
		"*****",
		'LSTE',
		/* [271] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1085, "EDDI") {
	{	/* array: 14 elements */
		/* [1] */
		"\"Resurrection\" resource format",
		'DVDR',
		/* [2] */
		"Format",
		'DWRD',
		/* [3] */
		"latestVersion=0",
		'CASE',
		/* [4] */
		"Vendor name",
		'P020',
		/* [5] */
		"Vendor info",
		'PSTR',
		/* [6] */
		"Flags",
		'DLNG',
		/* [7] */
		"Reserved 1",
		'DLNG',
		/* [8] */
		"Reserved 2",
		'DLNG',
		/* [9] */
		"Reserved 3",
		'DLNG',
		/* [10] */
		"Reserved 4",
		'DLNG',
		/* [11] */
		"Count:",
		'OCNT',
		/* [12] */
		"Supported types",
		'LSTC',
		/* [13] */
		"Res Type",
		'TNAM',
		/* [14] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1086, "EDT#") {
	{	/* array: 34 elements */
		/* [1] */
		"Last modified",
		'DATE',
		/* [2] */
		"Version",
		'KWRD',
		/* [3] */
		"Standard=0",
		'CASE',
		/* [4] */
		"0",
		'KEYB',
		/* [5] */
		"Count:",
		'OCNT',
		/* [6] */
		"List of Editors",
		'LSTC',
		/* [7] */
		"File specification",
		'DVDR',
		/* [8] */
		"Volume ref num",
		'DWRD',
		/* [9] */
		"Parent directory ID",
		'DLNG',
		/* [10] */
		"File name of apprentice",
		'P040',
		/* [11] */
		"Reserved for open file ID",
		'DWRD',
		/* [12] */
		"Closed=-1",
		'CASE',
		/* [13] */
		"Reference count",
		'DWRD',
		/* [14] */
		"Must be=0",
		'CASE',
		/* [15] */
		"Open resource fork automatically?",
		'WFLG',
		/* [16] */
		"True=Automatically",
		'CASE',
		/* [17] */
		"False=Library will do it",
		'CASE',
		/* [18] */
		"Editor information",
		'DVDR',
		/* [19] */
		"Type of editor",
		'TNAM',
		/* [20] */
		"Root=root",
		'CASE',
		/* [21] */
		"File system=fsys",
		'CASE',
		/* [22] */
		"Folder=fold",
		'CASE',
		/* [23] */
		"Type of interface resource",
		'TNAM',
		/* [24] */
		"Standard dialog=DLOG",
		'CASE',
		/* [25] */
		"No interface=$00000000",
		'CASE',
		/* [26] */
		"Interface resource ID",
		'RSID',
		/* [27] */
		"Standard=128",
		'CASE',
		/* [28] */
		"Type of menu resource",
		'TNAM',
		/* [29] */
		"Standard=MENU",
		'CASE',
		/* [30] */
		"No menu(s)=$00000000",
		'CASE',
		/* [31] */
		"Menu resource ID",
		'RSID',
		/* [32] */
		"Standard=128",
		'CASE',
		/* [33] */
		"*****",
		'LSTE',
		/* [34] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1087, "EMap") {
	{	/* array: 16 elements */
		/* [1] */
		"CW Plugin resource format",
		'DVDR',
		/* [2] */
		"Resource version",
		'DWRD',
		/* [3] */
		"Current=1",
		'CASE',
		/* [4] */
		"Count:",
		'OCNT',
		/* [5] */
		"Mappings",
		'LSTC',
		/* [6] */
		"File Type",
		'TNAM',
		/* [7] */
		"none=$00000000",
		'CASE',
		/* [8] */
		"text file=TEXT",
		'CASE',
		/* [9] */
		"Extension",
		'P020',
		/* [10] */
		"none=",
		'CASE',
		/* [11] */
		"Precompile",
		'LBIT',
		/* [12] */
		"Launchable",
		'LBIT',
		/* [13] */
		"Resource File",
		'LBIT',
		/* [14] */
		"Ignored by Make",
		'LBIT',
		/* [15] */
		"Reserved",
		'LB28',
		/* [16] */
		"",
		'LSTE'
	}
};

resource 'TMPL' (1088, "eopt") {
	{	/* array: 6 elements */
		/* [1] */
		"Execute during imaging",
		'LBIT',
		/* [2] */
		"Need device status",
		'LBIT',
		/* [3] */
		"Change page at de-spool page",
		'LBIT',
		/* [4] */
		"Change page at image page",
		'LBIT',
		/* [5] */
		"Change page at render page",
		'LBIT',
		/* [6] */
		"Reserved",
		'LB27'
	}
};

resource 'TMPL' (1089, "epcf") {
	{	/* array: 16 elements */
		/* [1] */
		"Version",
		'HWRD',
		/* [2] */
		"Protocol type",
		'HWRD',
		/* [3] */
		"Upper interface",
		'HLNG',
		/* [4] */
		"Lower interface",
		'HLNG',
		/* [5] */
		"Flags",
		'HLNG',
		/* [6] */
		"My XTI level",
		'HLNG',
		/* [7] */
		"Count:",
		'OCNT',
		/* [8] */
		"Options list",
		'LSTC',
		/* [9] */
		"XTI level of options",
		'HLNG',
		/* [10] */
		"XTI name of options",
		'HLNG',
		/* [11] */
		"Min octets",
		'HWRD',
		/* [12] */
		"Max octets",
		'HWRD',
		/* [13] */
		"Option type",
		'HWRD',
		/* [14] */
		"Option name",
		'PSTR',
		/* [15] */
		"alignment",
		'AWRD',
		/* [16] */
		"-----",
		'LSTE'
	}
};

resource 'TMPL' (1090, "eppc") {
	{	/* array: 4 elements */
		/* [1] */
		"Flags",
		'HLNG',
		/* [2] */
		"Reserved",
		'HLNG',
		/* [3] */
		"Script code",
		'HWRD',
		/* [4] */
		"String",
		'P020'
	}
};

resource 'TMPL' (1091, "EQPS") {
	{	/* array: 25 elements */
		/* [1] */
		"Version (0)",
		'DWRD',
		/* [2] */
		"Name",
		'H200',
		/* [3] */
		"Levels are -1200 to +1200",
		'DVDR',
		/* [4] */
		"Preamp level",
		'DWRD',
		/* [5] */
		"Band 1 level",
		'DWRD',
		/* [6] */
		"Band 2 level",
		'DWRD',
		/* [7] */
		"Band 3 level",
		'DWRD',
		/* [8] */
		"Band 4 level",
		'DWRD',
		/* [9] */
		"Band 5 level",
		'DWRD',
		/* [10] */
		"Band 6 level",
		'DWRD',
		/* [11] */
		"Band 7 level",
		'DWRD',
		/* [12] */
		"Band 8 level",
		'DWRD',
		/* [13] */
		"Band 9 level",
		'DWRD',
		/* [14] */
		"Band 10 level",
		'DWRD',
		/* [15] */
		"Band 1 freq (32)",
		'DWRD',
		/* [16] */
		"Band 2 freq (63)",
		'DWRD',
		/* [17] */
		"Band 3 freq (125)",
		'DWRD',
		/* [18] */
		"Band 4 freq (280)",
		'DWRD',
		/* [19] */
		"Band 5 freq (500)",
		'DWRD',
		/* [20] */
		"Band 6 freq (1K)",
		'DWRD',
		/* [21] */
		"Band 7 freq (2K)",
		'DWRD',
		/* [22] */
		"Band 8 freq (4K)",
		'DWRD',
		/* [23] */
		"Band 9 freq (8K)",
		'DWRD',
		/* [24] */
		"Band 10 freq (16K)",
		'DWRD',
		/* [25] */
		"Reserved",
		'F050'
	}
};

resource 'TMPL' (1092, "EQST") {
	{	/* array: 33 elements */
		/* [1] */
		"eqEnabled",
		'DBYT',
		/* [2] */
		"eqAuto",
		'DBYT',
		/* [3] */
		"Preamp level (-1200 to +1200)",
		'DWRD',
		/* [4] */
		"Level band 32",
		'DWRD',
		/* [5] */
		"Level band 63",
		'DWRD',
		/* [6] */
		"Level band 125",
		'DWRD',
		/* [7] */
		"Level band 280",
		'DWRD',
		/* [8] */
		"Level band 500",
		'DWRD',
		/* [9] */
		"Level band 1K",
		'DWRD',
		/* [10] */
		"Level band 2K",
		'DWRD',
		/* [11] */
		"Level band 4K",
		'DWRD',
		/* [12] */
		"Level band 8K",
		'DWRD',
		/* [13] */
		"Level band 16K",
		'DWRD',
		/* [14] */
		"Reserved",
		'FLNG',
		/* [15] */
		"Reserved",
		'FLNG',
		/* [16] */
		"Reserved",
		'FLNG',
		/* [17] */
		"Reserved",
		'FLNG',
		/* [18] */
		"Reserved",
		'FLNG',
		/* [19] */
		"Reserved",
		'FLNG',
		/* [20] */
		"Reserved",
		'FLNG',
		/* [21] */
		"Reserved",
		'FLNG',
		/* [22] */
		"Reserved",
		'FLNG',
		/* [23] */
		"Reserved",
		'FLNG',
		/* [24] */
		"Reserved",
		'FLNG',
		/* [25] */
		"Reserved",
		'FLNG',
		/* [26] */
		"Reserved",
		'FLNG',
		/* [27] */
		"Reserved",
		'FLNG',
		/* [28] */
		"Reserved",
		'FLNG',
		/* [29] */
		"Reserved",
		'FLNG',
		/* [30] */
		"Reserved",
		'FLNG',
		/* [31] */
		"Reserved",
		'FLNG',
		/* [32] */
		"Reserved",
		'FLNG',
		/* [33] */
		"Reserved",
		'FLNG'
	}
};

resource 'TMPL' (1093, "ErrC") {
	{	/* array: 1 elements */
		/* [1] */
		"Error description",
		'CSTR'
	}
};

resource 'TMPL' (1094, "errs") {
	{	/* array: 8 elements */
		/* [1] */
		"List of errors",
		'LSTB',
		/* [2] */
		"Low error number",
		'DWRD',
		/* [3] */
		"Index field is STR# ID=0",
		'CASE',
		/* [4] */
		"Lowest=-32768",
		'CASE',
		/* [5] */
		"High error number",
		'DWRD',
		/* [6] */
		"Highest=32767",
		'CASE',
		/* [7] */
		"Index of string in STR# or STR# ID",
		'DWRD',
		/* [8] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1095, "EuFl") {
	{	/* array: 4 elements */
		/* [1] */
		"\"Eudora\" resource format",
		'DVDR',
		/* [2] */
		"File types",
		'LSTB',
		/* [3] */
		"File type",
		'TNAM',
		/* [4] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1096, "EuOM") {
	{	/* array: 17 elements */
		/* [1] */
		"\"Eudora\" resource format",
		'DVDR',
		/* [2] */
		"*****",
		'LSTB',
		/* [3] */
		"Content Type",
		'PSTR',
		/* [4] */
		"Content SubType",
		'PSTR',
		/* [5] */
		"Filename suffix",
		'PSTR',
		/* [6] */
		"Creator Code",
		'TNAM',
		/* [7] */
		"Type",
		'TNAM',
		/* [8] */
		"Reserved",
		'HWRD',
		/* [9] */
		"Newline conversion?",
		'BBIT',
		/* [10] */
		"May suppress resource fork?",
		'BBIT',
		/* [11] */
		"Reserved",
		'BB02',
		/* [12] */
		"Suppress x-mac-type/creator",
		'BBIT',
		/* [13] */
		"Reserved",
		'BB03',
		/* [14] */
		"Reserved",
		'HBYT',
		/* [15] */
		"Special Id",
		'HLNG',
		/* [16] */
		"Reserved",
		'H00C',
		/* [17] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1097, "EuRg") {
	{	/* array: 4 elements */
		/* [1] */
		"\"Eudora\" resource format",
		'DVDR',
		/* [2] */
		"File types",
		'LSTB',
		/* [3] */
		"File type",
		'TNAM',
		/* [4] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1098, "exft") {
	{	/* array: 148 elements */
		/* [1] */
		"Count:",
		'LCNT',
		/* [2] */
		"List of Excluded fonts",
		'LSTC',
		/* [3] */
		"Font name type",
		'DBYT',
		/* [4] */
		"Font=1",
		'CASE',
		/* [5] */
		"Family=2",
		'CASE',
		/* [6] */
		"Style=3",
		'CASE',
		/* [7] */
		"Unique=4",
		'CASE',
		/* [8] */
		"Full=5",
		'CASE',
		/* [9] */
		"Version=6",
		'CASE',
		/* [10] */
		"PostScript=7",
		'CASE',
		/* [11] */
		"Trademark=8",
		'CASE',
		/* [12] */
		"Manufacturer=9",
		'CASE',
		/* [13] */
		"Platform type",
		'KBYT',
		/* [14] */
		"Macintosh=2",
		'CASE',
		/* [15] */
		"Unicode=1",
		'CASE',
		/* [16] */
		"Reserved=3",
		'CASE',
		/* [17] */
		"Microsoft=4",
		'CASE',
		/* [18] */
		"Custom=5",
		'CASE',
		/* [19] */
		"2",
		'KEYB',
		/* [20] */
		"Script",
		'DBYT',
		/* [21] */
		"",
		'KEYE',
		/* [22] */
		"1",
		'KEYB',
		/* [23] */
		"Script",
		'DBYT',
		/* [24] */
		"",
		'KEYE',
		/* [25] */
		"3",
		'KEYB',
		/* [26] */
		"Script",
		'DBYT',
		/* [27] */
		"",
		'KEYE',
		/* [28] */
		"4",
		'KEYB',
		/* [29] */
		"Script",
		'DBYT',
		/* [30] */
		"",
		'KEYE',
		/* [31] */
		"5",
		'KEYB',
		/* [32] */
		"Script",
		'DBYT',
		/* [33] */
		"",
		'KEYE',
		/* [34] */
		"Language",
		'DBYT',
		/* [35] */
		"English=0",
		'CASE',
		/* [36] */
		"French=1",
		'CASE',
		/* [37] */
		"German==2",
		'CASE',
		/* [38] */
		"Italian=3",
		'CASE',
		/* [39] */
		"Dutch=4",
		'CASE',
		/* [40] */
		"Swedish=5",
		'CASE',
		/* [41] */
		"Spanish=6",
		'CASE',
		/* [42] */
		"Danish=7",
		'CASE',
		/* [43] */
		"Portuguese=8",
		'CASE',
		/* [44] */
		"Norwegian=9",
		'CASE',
		/* [45] */
		"Hebrew=10",
		'CASE',
		/* [46] */
		"Japanese=11",
		'CASE',
		/* [47] */
		"Arabic=12",
		'CASE',
		/* [48] */
		"Finnish=13",
		'CASE',
		/* [49] */
		"Greek=14",
		'CASE',
		/* [50] */
		"Icelandic=15",
		'CASE',
		/* [51] */
		"Maltese=16",
		'CASE',
		/* [52] */
		"Turkish=17",
		'CASE',
		/* [53] */
		"Croatian=18",
		'CASE',
		/* [54] */
		"TradChinese=19",
		'CASE',
		/* [55] */
		"Urdu=20",
		'CASE',
		/* [56] */
		"Hindi=21",
		'CASE',
		/* [57] */
		"Thai=22",
		'CASE',
		/* [58] */
		"Korean=23",
		'CASE',
		/* [59] */
		"Lithuanian=24",
		'CASE',
		/* [60] */
		"Polish=25",
		'CASE',
		/* [61] */
		"Hungarian=26",
		'CASE',
		/* [62] */
		"Estonian=27",
		'CASE',
		/* [63] */
		"Lettish=28",
		'CASE',
		/* [64] */
		"Latvian=28",
		'CASE',
		/* [65] */
		"Lapponian=29",
		'CASE',
		/* [66] */
		"Lappish=29",
		'CASE',
		/* [67] */
		"Faeroese=30",
		'CASE',
		/* [68] */
		"Farsi=31",
		'CASE',
		/* [69] */
		"Persian=31",
		'CASE',
		/* [70] */
		"Russian=32",
		'CASE',
		/* [71] */
		"SimpChinese=33",
		'CASE',
		/* [72] */
		"Flemish=34",
		'CASE',
		/* [73] */
		"Irish=35",
		'CASE',
		/* [74] */
		"Albanian=36",
		'CASE',
		/* [75] */
		"Romanian=37",
		'CASE',
		/* [76] */
		"Czech=38",
		'CASE',
		/* [77] */
		"Slovak=39",
		'CASE',
		/* [78] */
		"Slovenian=40",
		'CASE',
		/* [79] */
		"Yiddish=41",
		'CASE',
		/* [80] */
		"Serbian=42",
		'CASE',
		/* [81] */
		"Macedonian=43",
		'CASE',
		/* [82] */
		"Bulgarian=44",
		'CASE',
		/* [83] */
		"Ukrainian=45",
		'CASE',
		/* [84] */
		"Byelorussian=46",
		'CASE',
		/* [85] */
		"Uzbek=47",
		'CASE',
		/* [86] */
		"Kazakh=48",
		'CASE',
		/* [87] */
		"Azerbaijani=49",
		'CASE',
		/* [88] */
		"AzerbaijanAr=50",
		'CASE',
		/* [89] */
		"Armenian=51",
		'CASE',
		/* [90] */
		"Georgian=52",
		'CASE',
		/* [91] */
		"Moldavian=53",
		'CASE',
		/* [92] */
		"Kirghiz=54",
		'CASE',
		/* [93] */
		"Tajiki=55",
		'CASE',
		/* [94] */
		"Turkmen=56",
		'CASE',
		/* [95] */
		"Mongolian=57",
		'CASE',
		/* [96] */
		"MongolianCyr=58",
		'CASE',
		/* [97] */
		"Pashto=59",
		'CASE',
		/* [98] */
		"Kurdish=60",
		'CASE',
		/* [99] */
		"Kashmiri=61",
		'CASE',
		/* [100] */
		"Sindhi=62",
		'CASE',
		/* [101] */
		"Tibetan=63",
		'CASE',
		/* [102] */
		"Nepali=64",
		'CASE',
		/* [103] */
		"Sanskrit=65",
		'CASE',
		/* [104] */
		"Marathi=66",
		'CASE',
		/* [105] */
		"Bengali=67",
		'CASE',
		/* [106] */
		"Assamese=68",
		'CASE',
		/* [107] */
		"Gujarati=69",
		'CASE',
		/* [108] */
		"Punjabi=70",
		'CASE',
		/* [109] */
		"Oriya=71",
		'CASE',
		/* [110] */
		"Malayalam=72",
		'CASE',
		/* [111] */
		"Kannada=73",
		'CASE',
		/* [112] */
		"Tamil=74",
		'CASE',
		/* [113] */
		"Telugu=75",
		'CASE',
		/* [114] */
		"Sinhalese=76",
		'CASE',
		/* [115] */
		"Burmese=77",
		'CASE',
		/* [116] */
		"Khmer=78",
		'CASE',
		/* [117] */
		"Lao=79",
		'CASE',
		/* [118] */
		"Vietnamese=80",
		'CASE',
		/* [119] */
		"Indonesian=81",
		'CASE',
		/* [120] */
		"Tagalog=82",
		'CASE',
		/* [121] */
		"MalayRoman=83",
		'CASE',
		/* [122] */
		"MalayArabic=84",
		'CASE',
		/* [123] */
		"Amharic=85",
		'CASE',
		/* [124] */
		"Tigrinya=86",
		'CASE',
		/* [125] */
		"Galla=87",
		'CASE',
		/* [126] */
		"Oromo=87",
		'CASE',
		/* [127] */
		"Somali=88",
		'CASE',
		/* [128] */
		"Swahili=89",
		'CASE',
		/* [129] */
		"Ruanda=90",
		'CASE',
		/* [130] */
		"Rundi=91",
		'CASE',
		/* [131] */
		"Chewa=92",
		'CASE',
		/* [132] */
		"Malagasy=93",
		'CASE',
		/* [133] */
		"Esperanto=94",
		'CASE',
		/* [134] */
		"Welsh=128",
		'CASE',
		/* [135] */
		"Basque=129",
		'CASE',
		/* [136] */
		"Catalan=130",
		'CASE',
		/* [137] */
		"Latin=131",
		'CASE',
		/* [138] */
		"Quechua=132",
		'CASE',
		/* [139] */
		"Guarani=133",
		'CASE',
		/* [140] */
		"Aymara=134",
		'CASE',
		/* [141] */
		"Tatar=135",
		'CASE',
		/* [142] */
		"Uighur=136",
		'CASE',
		/* [143] */
		"Dzongkha=137",
		'CASE',
		/* [144] */
		"JavaneseRom=138",
		'CASE',
		/* [145] */
		"SudaneseRom=139",
		'CASE',
		/* [146] */
		"Font name",
		'WSTR',
		/* [147] */
		"Align",
		'AL08',
		/* [148] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1099, "f2im") {
	{	/* array: 6 elements */
		/* [1] */
		"\"SuitCase\" resource format",
		'DVDR',
		/* [2] */
		"Count:",
		'OCNT',
		/* [3] */
		"File types",
		'LSTC',
		/* [4] */
		"File type",
		'TNAM',
		/* [5] */
		"'ICN#' resource",
		'RSID',
		/* [6] */
		"-----",
		'LSTE'
	}
};

resource 'TMPL' (1100, "faps") {
	{	/* array: 27 elements */
		/* [1] */
		"File Transfer tool capabilities list",
		'DVDR',
		/* [2] */
		"Count:",
		'OCNT',
		/* [3] */
		"List of Pairs",
		'LSTC',
		/* [4] */
		"Pair type",
		'KTYP',
		/* [5] */
		"Batch transfer=BXFR",
		'CASE',
		/* [6] */
		"File types supported=TYPE",
		'CASE',
		/* [7] */
		"Transfer modes=MODE",
		'CASE',
		/* [8] */
		"BXFR",
		'KEYB',
		/* [9] */
		"Support for FTSend/FTReceive",
		'DVDR',
		/* [10] */
		"Reserved",
		'LB31',
		/* [11] */
		"Supported",
		'LB01',
		/* [12] */
		"",
		'KEYE',
		/* [13] */
		"TYPE",
		'KEYB',
		/* [14] */
		"Types of files that can be transferred",
		'DVDR',
		/* [15] */
		"File type",
		'TNAM',
		/* [16] */
		"Text only=TEXT",
		'CASE',
		/* [17] */
		"All types=????",
		'CASE',
		/* [18] */
		"",
		'KEYE',
		/* [19] */
		"MODE",
		'KEYB',
		/* [20] */
		"Mode",
		'TNAM',
		/* [21] */
		"Send only=SEND",
		'CASE',
		/* [22] */
		"Receive only=RECV",
		'CASE',
		/* [23] */
		"Send and receive=BOTH",
		'CASE',
		/* [24] */
		"Send and receive Async='ASYN',",
		'CASE',
		/* [25] */
		"Leave empty if not supported",
		'DVDR',
		/* [26] */
		"",
		'KEYE',
		/* [27] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1101, "fbnd") {
	{	/* array: 9 elements */
		/* [1] */
		"Count:",
		'ZCNT',
		/* [2] */
		"----",
		'LSTC',
		/* [3] */
		"Type",
		'TNAM',
		/* [4] */
		"Count:",
		'ZCNT',
		/* [5] */
		"Map",
		'LSTC',
		/* [6] */
		"Local",
		'DWRD',
		/* [7] */
		"Actual",
		'DWRD',
		/* [8] */
		"****",
		'LSTE',
		/* [9] */
		"****",
		'LSTE'
	}
};

resource 'TMPL' (1102, "FBTN") {
	{	/* array: 7 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"List of buttons",
		'LSTC',
		/* [3] */
		"Icon",
		'H080',
		/* [4] */
		"Type",
		'TNAM',
		/* [5] */
		"Application",
		'ESTR',
		/* [6] */
		"Document",
		'ESTR',
		/* [7] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1103, "FCMT") {
	{	/* array: 2 elements */
		/* [1] */
		"Comment string",
		'PSTR',
		/* [2] */
		"Hexadecimal data",
		'HEXD'
	}
};

resource 'TMPL' (1104, "fctb") {
	{	/* array: 7 elements */
		/* [1] */
		"Seed",
		'HLNG',
		/* [2] */
		"Flags",
		'DWRD',
		/* [3] */
		"Count:",
		'ZCNT',
		/* [4] */
		"List of Colors",
		'LSTC',
		/* [5] */
		"Part code",
		'DWRD',
		/* [6] */
		"Color",
		'COLR',
		/* [7] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1105, "fdes") {
	{	/* array: 46 elements */
		/* [1] */
		"Go Mixed Mode Trap",
		'HWRD',
		/* [2] */
		"Version",
		'HBYT',
		/* [3] */
		"Unused",
		'BBIT',
		/* [4] */
		"Unused",
		'BBIT',
		/* [5] */
		"Unused",
		'BBIT',
		/* [6] */
		"Unused",
		'BBIT',
		/* [7] */
		"Unused",
		'BBIT',
		/* [8] */
		"Unused",
		'BBIT',
		/* [9] */
		"Unused",
		'BBIT',
		/* [10] */
		"Selectors are indexable",
		'BBIT',
		/* [11] */
		"Reserved",
		'FLNG',
		/* [12] */
		"Reserved",
		'FBYT',
		/* [13] */
		"Selector Info",
		'HBYT',
		/* [14] */
		"Routine Count",
		'DWRD',
		/* [15] */
		"Proc info (binary long int)",
		'DLNG',
		/* [16] */
		"Reserved",
		'FBYT',
		/* [17] */
		"ISA",
		'HBYT',
		/* [18] */
		"Filler byte",
		'FBYT',
		/* [19] */
		"Unused",
		'BBIT',
		/* [20] */
		"Unused",
		'BBIT',
		/* [21] */
		"Unused",
		'BBIT',
		/* [22] */
		"Routine is dispatched default",
		'BBIT',
		/* [23] */
		"Dont pass selector",
		'BBIT',
		/* [24] */
		"Use native ISA",
		'BBIT',
		/* [25] */
		"Fragment needs preparing",
		'BBIT',
		/* [26] */
		"Proc descriptor is relative",
		'BBIT',
		/* [27] */
		"Proc descriptor",
		'DLNG',
		/* [28] */
		"Reserved",
		'FLNG',
		/* [29] */
		"Selector",
		'DLNG',
		/* [30] */
		"Proc info (binary long int)",
		'DLNG',
		/* [31] */
		"Reserved",
		'FBYT',
		/* [32] */
		"ISA",
		'HBYT',
		/* [33] */
		"Filler byte",
		'FBYT',
		/* [34] */
		"Unused",
		'BBIT',
		/* [35] */
		"Unused",
		'BBIT',
		/* [36] */
		"Unused",
		'BBIT',
		/* [37] */
		"Routine is dispatched default",
		'BBIT',
		/* [38] */
		"Dont pass selector",
		'BBIT',
		/* [39] */
		"Use native ISA",
		'BBIT',
		/* [40] */
		"Fragment needs preparing",
		'BBIT',
		/* [41] */
		"Proc descriptor is relative",
		'BBIT',
		/* [42] */
		"Proc descriptor",
		'DLNG',
		/* [43] */
		"Reserved",
		'FLNG',
		/* [44] */
		"Selector",
		'DLNG',
		/* [45] */
		"Alignment",
		'ALNG',
		/* [46] */
		"68k code, long align and PPC code",
		'HEXD'
	}
};

resource 'TMPL' (1106, "FDIR") {
	{	/* array: 3 elements */
		/* [1] */
		"*****",
		'LSTB',
		/* [2] */
		"Button DirID",
		'HLNG',
		/* [3] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1107, "FDlg") {
	{	/* array: 14 elements */
		/* [1] */
		"\"Finale\" resource format",
		'DVDR',
		/* [2] */
		"Prompt STR#",
		'DWRD',
		/* [3] */
		"Prompt index",
		'DWRD',
		/* [4] */
		"Action type",
		'DWRD',
		/* [5] */
		"Reserved1",
		'DWRD',
		/* [6] */
		"Reserved2",
		'DWRD',
		/* [7] */
		"Count:",
		'OCNT',
		/* [8] */
		"Types array",
		'LSTC',
		/* [9] */
		"Group",
		'DWRD',
		/* [10] */
		"Reserved",
		'DWRD',
		/* [11] */
		"Type",
		'TNAM',
		/* [12] */
		"Creator",
		'TNAM',
		/* [13] */
		"Extension",
		'TNAM',
		/* [14] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1108, "fdmn") {
	{	/* array: 8 elements */
		/* [1] */
		"Menu ID",
		'DWRD',
		/* [2] */
		"Command code of item to insert after",
		'TNAM',
		/* [3] */
		"This item's command code",
		'TNAM',
		/* [4] */
		"Private flags",
		'HWRD',
		/* [5] */
		"Key equivalent",
		'CHAR',
		/* [6] */
		"None=$00",
		'CASE',
		/* [7] */
		"Align",
		'AWRD',
		/* [8] */
		"Name",
		'PSTR'
	}
};

resource 'TMPL' (1109, "fFIG") {
	{	/* array: 25 elements */
		/* [1] */
		"Tool version",
		'HBYT',
		/* [2] */
		"Revision number",
		'HBYT',
		/* [3] */
		"Mode (Txt=1, Bin, MacB)",
		'DBYT',
		/* [4] */
		"Protocol (Std=1, Long, Sliding, ELP)",
		'DBYT',
		/* [5] */
		"Auto receive",
		'BOOL',
		/* [6] */
		"Use timeout",
		'BOOL',
		/* [7] */
		"Log packets",
		'BOOL',
		/* [8] */
		"8-bit prefix",
		'BOOL',
		/* [9] */
		"Overwrite files",
		'BOOL',
		/* [10] */
		"Std packet size",
		'DLNG',
		/* [11] */
		"Long packet size",
		'DLNG',
		/* [12] */
		"Sliding window size",
		'DLNG',
		/* [13] */
		"Extra long packet size",
		'DLNG',
		/* [14] */
		"Creator name",
		'P01F',
		/* [15] */
		"Creator signature",
		'TNAM',
		/* [16] */
		"Retry limit",
		'DWRD',
		/* [17] */
		"Timeout (Auto=0)",
		'DWRD',
		/* [18] */
		"Mark char (Send)",
		'HBYT',
		/* [19] */
		"Mark char (Recv)",
		'HBYT',
		/* [20] */
		"EOL char (Send)",
		'HBYT',
		/* [21] */
		"EOL char (Recv)",
		'HBYT',
		/* [22] */
		"Pad char (Send)",
		'HBYT',
		/* [23] */
		"Pad char (Recv)",
		'HBYT',
		/* [24] */
		"# of Pad chars (Send)",
		'DWRD',
		/* [25] */
		"# of Pad chars (Recv)",
		'DWRD'
	}
};

resource 'TMPL' (1110, "FHLP") {
	{	/* array: 1 elements */
		/* [1] */
		"Fetch Help Text",
		'CSTR'
	}
};

resource 'TMPL' (1111, "find") {
	{	/* array: 12 elements */
		/* [1] */
		"Find text",
		'ESTR',
		/* [2] */
		"Search text",
		'ESTR',
		/* [3] */
		"5 items",
		'FCNT',
		/* [4] */
		"Fixed count list",
		'LSTC',
		/* [5] */
		"Font number",
		'DWRD',
		/* [6] */
		"System=0",
		'CASE',
		/* [7] */
		"Application=1",
		'CASE',
		/* [8] */
		"Port=2",
		'CASE',
		/* [9] */
		"Font face",
		'DWRD',
		/* [10] */
		"Font size",
		'DWRD',
		/* [11] */
		"Bounds",
		'RECT',
		/* [12] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1112, "finf") {
	{	/* array: 14 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"Fonts list",
		'LSTC',
		/* [3] */
		"Font number",
		'DWRD',
		/* [4] */
		"Font style",
		'WORV',
		/* [5] */
		"Plain=0",
		'CASE',
		/* [6] */
		"Bold=1",
		'CASE',
		/* [7] */
		"Italic=2",
		'CASE',
		/* [8] */
		"Underline=4",
		'CASE',
		/* [9] */
		"Outline=8",
		'CASE',
		/* [10] */
		"Shadow=16",
		'CASE',
		/* [11] */
		"Condensed=32",
		'CASE',
		/* [12] */
		"Extended=64",
		'CASE',
		/* [13] */
		"Font size",
		'DWRD',
		/* [14] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1113, "Flag") {
	{	/* array: 655 elements */
		/* [1] */
		"CW Plugin resource format",
		'DVDR',
		/* [2] */
		"Resource Version",
		'KWRD',
		/* [3] */
		"CWPro3=3",
		'CASE',
		/* [4] */
		"CWPro2=2",
		'CASE',
		/* [5] */
		"CW7=1",
		'CASE',
		/* [6] */
		"3",
		'KEYB',
		/* [7] */
		"Object type",
		'KTYP',
		/* [8] */
		"Panel=Panl",
		'CASE',
		/* [9] */
		"Compiler=Comp",
		'CASE',
		/* [10] */
		"Linker=Link",
		'CASE',
		/* [11] */
		"Version Control=VCS ",
		'CASE',
		/* [12] */
		"Reserved=Appl",
		'CASE',
		/* [13] */
		"Panl",
		'KEYB',
		/* [14] */
		"Earliest supported API Version",
		'DWRD',
		/* [15] */
		"Pro6=10",
		'CASE',
		/* [16] */
		"Pro5=9",
		'CASE',
		/* [17] */
		"Pro4=8",
		'CASE',
		/* [18] */
		"Pro3=7",
		'CASE',
		/* [19] */
		"Pro2=6",
		'CASE',
		/* [20] */
		"CW10=5",
		'CASE',
		/* [21] */
		"CW9=4",
		'CASE',
		/* [22] */
		"CW8=3",
		'CASE',
		/* [23] */
		"Version 2=2",
		'CASE',
		/* [24] */
		"CW7=1",
		'CASE',
		/* [25] */
		"Uses strict API",
		'LBIT',
		/* [26] */
		"Supports byte-swapping",
		'LBIT',
		/* [27] */
		"Supports reading/writing settings",
		'LBIT',
		/* [28] */
		"Uses cross-platform API",
		'LBIT',
		/* [29] */
		"reserved",
		'LB28',
		/* [30] */
		"Family ID",
		'TNAM',
		/* [31] */
		"Project=proj",
		'CASE',
		/* [32] */
		"Front End=fend",
		'CASE',
		/* [33] */
		"Back End=bend",
		'CASE',
		/* [34] */
		"Browser=brow",
		'CASE',
		/* [35] */
		"Editor=edit",
		'CASE',
		/* [36] */
		"Debugger=dbug",
		'CASE',
		/* [37] */
		"Linker=link",
		'CASE',
		/* [38] */
		"Miscellaneous=****",
		'CASE',
		/* [39] */
		"RAD Tools=radt",
		'CASE',
		/* [40] */
		"Latest supported API version",
		'DWRD',
		/* [41] */
		"Pro6=10",
		'CASE',
		/* [42] */
		"Pro5=9",
		'CASE',
		/* [43] */
		"Pro4=8",
		'CASE',
		/* [44] */
		"Pro3=7",
		'CASE',
		/* [45] */
		"Pro2=6",
		'CASE',
		/* [46] */
		"CW10=5",
		'CASE',
		/* [47] */
		"CW9=4",
		'CASE',
		/* [48] */
		"CW8=3",
		'CASE',
		/* [49] */
		"Version 2=2",
		'CASE',
		/* [50] */
		"CW7=1",
		'CASE',
		/* [51] */
		"Prefs data version",
		'DWRD',
		/* [52] */
		"Panel scope",
		'DWRD',
		/* [53] */
		"global=0",
		'CASE',
		/* [54] */
		"project=1",
		'CASE',
		/* [55] */
		"target=2",
		'CASE',
		/* [56] */
		"",
		'KEYE',
		/* [57] */
		"Comp",
		'KEYB',
		/* [58] */
		"Earliest supported API version",
		'DWRD',
		/* [59] */
		"Version 11 (Pro 5)=11",
		'CASE',
		/* [60] */
		"Version 10 (Pro 4)=10",
		'CASE',
		/* [61] */
		"Version 9 (Pro 3)=9",
		'CASE',
		/* [62] */
		"Version 8 (Pro 2)=8",
		'CASE',
		/* [63] */
		"Version 7 (Pro 1)=7",
		'CASE',
		/* [64] */
		"Version 6=6",
		'CASE',
		/* [65] */
		"Version 5=5",
		'CASE',
		/* [66] */
		"CW9=4",
		'CASE',
		/* [67] */
		"CW8=3",
		'CASE',
		/* [68] */
		"Version 2=2",
		'CASE',
		/* [69] */
		"CW7=1",
		'CASE',
		/* [70] */
		"Generates Code",
		'LBIT',
		/* [71] */
		"Generates Resources",
		'LBIT',
		/* [72] */
		"Can Preprocess",
		'LBIT',
		/* [73] */
		"Can Precompile",
		'LBIT',
		/* [74] */
		"Is Pascal",
		'LBIT',
		/* [75] */
		"Can Import",
		'LBIT',
		/* [76] */
		"Can Disassemble",
		'LBIT',
		/* [77] */
		"Persistent",
		'LBIT',
		/* [78] */
		"Allow Duplicate File Names",
		'LBIT',
		/* [79] */
		"Multi Target Aware",
		'LBIT',
		/* [80] */
		"Multiprocessing Aware",
		'LBIT',
		/* [81] */
		"Uses Target Storage",
		'LBIT',
		/* [82] */
		"Has Compiler-Specific Browser Symbols",
		'LBIT',
		/* [83] */
		"Always Reload",
		'LBIT',
		/* [84] */
		"Requires Project Build Started",
		'LBIT',
		/* [85] */
		"Requires Target Build Started",
		'LBIT',
		/* [86] */
		"Requires Subproject Build Started",
		'LBIT',
		/* [87] */
		"Requires File-list Build Started",
		'LBIT',
		/* [88] */
		"",
		'LB14',
		/* [89] */
		"Language Type",
		'TNAM',
		/* [90] */
		"C/C++=c++ ",
		'CASE',
		/* [91] */
		"Pascal=pasc",
		'CASE',
		/* [92] */
		"Rez=rez ",
		'CASE',
		/* [93] */
		"java=java",
		'CASE',
		/* [94] */
		"unknown=????",
		'CASE',
		/* [95] */
		"Latest supported API version",
		'DWRD',
		/* [96] */
		"Version 11 (Pro 5)=11",
		'CASE',
		/* [97] */
		"Version \?10 (Pro 4)=10",
		'CASE',
		/* [98] */
		"Version 9 (Pro 3)=9",
		'CASE',
		/* [99] */
		"Version 8 (Pro 2)=8",
		'CASE',
		/* [100] */
		"Version 7 (Pro 1)=7",
		'CASE',
		/* [101] */
		"Version 6=6",
		'CASE',
		/* [102] */
		"Version 5=5",
		'CASE',
		/* [103] */
		"CW9=4",
		'CASE',
		/* [104] */
		"CW8=3",
		'CASE',
		/* [105] */
		"Version 2=2",
		'CASE',
		/* [106] */
		"CW7=1",
		'CASE',
		/* [107] */
		"",
		'KEYE',
		/* [108] */
		"Link",
		'KEYB',
		/* [109] */
		"Earliest supported API version",
		'DWRD',
		/* [110] */
		"Version 11 (Pro 5)=11",
		'CASE',
		/* [111] */
		"Version 10 (Pro 4)=10",
		'CASE',
		/* [112] */
		"Version 9 (Pro 3)=9",
		'CASE',
		/* [113] */
		"Version 8 (Pro 2)=8",
		'CASE',
		/* [114] */
		"Version 7 (Pro 1)=7",
		'CASE',
		/* [115] */
		"Version 5=5",
		'CASE',
		/* [116] */
		"CW9=4",
		'CASE',
		/* [117] */
		"CW8=3",
		'CASE',
		/* [118] */
		"Version 2=2",
		'CASE',
		/* [119] */
		"CW7=1",
		'CASE',
		/* [120] */
		"Can\0x19t Dissassemble",
		'LBIT',
		/* [121] */
		"Post Linker",
		'LBIT',
		/* [122] */
		"Allow Duplicate File Names",
		'LBIT',
		/* [123] */
		"Multi Target Aware",
		'LBIT',
		/* [124] */
		"Pre Linker",
		'LBIT',
		/* [125] */
		"Uses Target Storage",
		'LBIT',
		/* [126] */
		"Unmangles Names",
		'LBIT',
		/* [127] */
		"Magic Cap Linker",
		'LBIT',
		/* [128] */
		"Always Reload",
		'LBIT',
		/* [129] */
		"Requires Project Build Started",
		'LBIT',
		/* [130] */
		"Requires Target Build Started",
		'LBIT',
		/* [131] */
		"Requires Subproject Build Started",
		'LBIT',
		/* [132] */
		"Requires File-list Build Started",
		'LBIT',
		/* [133] */
		"Requires Target Link Started",
		'LBIT',
		/* [134] */
		"Requires Pre-Run",
		'LBIT',
		/* [135] */
		"GetTargetInfo is Thread Safe",
		'LBIT',
		/* [136] */
		"",
		'LB16',
		/* [137] */
		"reserved(0)",
		'FLNG',
		/* [138] */
		"Latest supported API version",
		'DWRD',
		/* [139] */
		"Version 11 (Pro 5)=11",
		'CASE',
		/* [140] */
		"Version 10 (Pro 4)=10",
		'CASE',
		/* [141] */
		"Version 9 (Pro 3)=9",
		'CASE',
		/* [142] */
		"Version 8 (Pro 2)=8",
		'CASE',
		/* [143] */
		"Version 7 (Pro 1)=7",
		'CASE',
		/* [144] */
		"Version 5=5",
		'CASE',
		/* [145] */
		"CW9=4",
		'CASE',
		/* [146] */
		"CW8=3",
		'CASE',
		/* [147] */
		"Version 2=2",
		'CASE',
		/* [148] */
		"CW7=1",
		'CASE',
		/* [149] */
		"",
		'KEYE',
		/* [150] */
		"VCS ",
		'KEYB',
		/* [151] */
		"Earliest Supported API Version",
		'DWRD',
		/* [152] */
		"Version 8=8",
		'CASE',
		/* [153] */
		"Version 7=7",
		'CASE',
		/* [154] */
		"Version 1=1",
		'CASE',
		/* [155] */
		"Doesn\0x19t Use Pre/PostFileAction on single"
		" file calls",
		'LBIT',
		/* [156] */
		"Doesn\0x19t use Pre/PostFileAction on recurs"
		"ive calls",
		'LBIT',
		/* [157] */
		"Requires events",
		'LBIT',
		/* [158] */
		"Wants Idle requests",
		'LBIT',
		/* [159] */
		"",
		'LB28',
		/* [160] */
		"reserved(0)",
		'FLNG',
		/* [161] */
		"Latest supported API version",
		'DWRD',
		/* [162] */
		"Version 8=8",
		'CASE',
		/* [163] */
		"Version 2=7",
		'CASE',
		/* [164] */
		"Version 1=1",
		'CASE',
		/* [165] */
		"",
		'KEYE',
		/* [166] */
		"Appl",
		'KEYB',
		/* [167] */
		"API Version",
		'DWRD',
		/* [168] */
		"CW7=1",
		'CASE',
		/* [169] */
		"",
		'LB32',
		/* [170] */
		"",
		'KEYE',
		/* [171] */
		"",
		'KEYE',
		/* [172] */
		"2",
		'KEYB',
		/* [173] */
		"Object type",
		'KTYP',
		/* [174] */
		"Panel=Panl",
		'CASE',
		/* [175] */
		"Compiler=Comp",
		'CASE',
		/* [176] */
		"Linker=Link",
		'CASE',
		/* [177] */
		"Version Control=VCS ",
		'CASE',
		/* [178] */
		"Reserved=Appl",
		'CASE',
		/* [179] */
		"Panl",
		'KEYB',
		/* [180] */
		"API Version",
		'KWRD',
		/* [181] */
		"Pro2=6",
		'CASE',
		/* [182] */
		"CW10=5",
		'CASE',
		/* [183] */
		"CW9=4",
		'CASE',
		/* [184] */
		"CW8=3",
		'CASE',
		/* [185] */
		"Version 2=2",
		'CASE',
		/* [186] */
		"CW7=1",
		'CASE',
		/* [187] */
		"6",
		'KEYB',
		/* [188] */
		"Prefs data version",
		'DWRD',
		/* [189] */
		"Uses strict API",
		'WBIT',
		/* [190] */
		"Supports byte-swapping",
		'WBIT',
		/* [191] */
		"reserved",
		'WB14',
		/* [192] */
		"Family ID",
		'TNAM',
		/* [193] */
		"Project=proj",
		'CASE',
		/* [194] */
		"Front End=fend",
		'CASE',
		/* [195] */
		"Back End=bend",
		'CASE',
		/* [196] */
		"Browser=brow",
		'CASE',
		/* [197] */
		"Editor=edit",
		'CASE',
		/* [198] */
		"Debugger=dbug",
		'CASE',
		/* [199] */
		"Linker=link",
		'CASE',
		/* [200] */
		"Miscellaneous=****",
		'CASE',
		/* [201] */
		"",
		'KEYE',
		/* [202] */
		"5",
		'KEYB',
		/* [203] */
		"Prefs data version",
		'DWRD',
		/* [204] */
		"Uses strict API",
		'WBIT',
		/* [205] */
		"reserved",
		'WB15',
		/* [206] */
		"Family ID",
		'TNAM',
		/* [207] */
		"Project=proj",
		'CASE',
		/* [208] */
		"Front End=fend",
		'CASE',
		/* [209] */
		"Back End=bend",
		'CASE',
		/* [210] */
		"Browser=brow",
		'CASE',
		/* [211] */
		"Editor=edit",
		'CASE',
		/* [212] */
		"Debugger=dbug",
		'CASE',
		/* [213] */
		"Linker=link",
		'CASE',
		/* [214] */
		"Miscellaneous=****",
		'CASE',
		/* [215] */
		"",
		'KEYE',
		/* [216] */
		"4",
		'KEYB',
		/* [217] */
		"Prefs data version",
		'DWRD',
		/* [218] */
		"",
		'WB16',
		/* [219] */
		"Family ID",
		'TNAM',
		/* [220] */
		"Project=proj",
		'CASE',
		/* [221] */
		"Front End=fend",
		'CASE',
		/* [222] */
		"Back End=bend",
		'CASE',
		/* [223] */
		"Browser=brow",
		'CASE',
		/* [224] */
		"Editor=edit",
		'CASE',
		/* [225] */
		"Debugger=dbug",
		'CASE',
		/* [226] */
		"Linker=link",
		'CASE',
		/* [227] */
		"Miscellaneous=****",
		'CASE',
		/* [228] */
		"",
		'KEYE',
		/* [229] */
		"3",
		'KEYB',
		/* [230] */
		"Prefs data version",
		'DWRD',
		/* [231] */
		"",
		'WB16',
		/* [232] */
		"Family ID",
		'TNAM',
		/* [233] */
		"Project=proj",
		'CASE',
		/* [234] */
		"Front End=fend",
		'CASE',
		/* [235] */
		"Back End=bend",
		'CASE',
		/* [236] */
		"Browser=brow",
		'CASE',
		/* [237] */
		"Editor=edit",
		'CASE',
		/* [238] */
		"Debugger=dbug",
		'CASE',
		/* [239] */
		"Linker=link",
		'CASE',
		/* [240] */
		"Miscellaneous=****",
		'CASE',
		/* [241] */
		"",
		'KEYE',
		/* [242] */
		"2",
		'KEYB',
		/* [243] */
		"Prefs data version",
		'DWRD',
		/* [244] */
		"",
		'WB16',
		/* [245] */
		"Family ID",
		'TNAM',
		/* [246] */
		"Project=proj",
		'CASE',
		/* [247] */
		"Front End=fend",
		'CASE',
		/* [248] */
		"Back End=bend",
		'CASE',
		/* [249] */
		"Browser=brow",
		'CASE',
		/* [250] */
		"Editor=edit",
		'CASE',
		/* [251] */
		"Debugger=dbug",
		'CASE',
		/* [252] */
		"Linker=link",
		'CASE',
		/* [253] */
		"Miscellaneous=****",
		'CASE',
		/* [254] */
		"",
		'KEYE',
		/* [255] */
		"1",
		'KEYB',
		/* [256] */
		"",
		'LB32',
		/* [257] */
		"",
		'KEYE',
		/* [258] */
		"",
		'KEYE',
		/* [259] */
		"Comp",
		'KEYB',
		/* [260] */
		"Earliest supported API version",
		'DWRD',
		/* [261] */
		"Version 9 (Pro 3)=9",
		'CASE',
		/* [262] */
		"Version 8 (Pro 2)=8",
		'CASE',
		/* [263] */
		"Version 7 (Pro 1)=7",
		'CASE',
		/* [264] */
		"Version 6=6",
		'CASE',
		/* [265] */
		"Version 5=5",
		'CASE',
		/* [266] */
		"CW9=4",
		'CASE',
		/* [267] */
		"CW8=3",
		'CASE',
		/* [268] */
		"Version 2=2",
		'CASE',
		/* [269] */
		"CW7=1",
		'CASE',
		/* [270] */
		"Generates Code",
		'LBIT',
		/* [271] */
		"Generates Resources",
		'LBIT',
		/* [272] */
		"Can Preprocess",
		'LBIT',
		/* [273] */
		"Can Precompile",
		'LBIT',
		/* [274] */
		"Is Pascal",
		'LBIT',
		/* [275] */
		"Can Import",
		'LBIT',
		/* [276] */
		"Can Disassemble",
		'LBIT',
		/* [277] */
		"Persistent",
		'LBIT',
		/* [278] */
		"Allow Duplicate File Names",
		'LBIT',
		/* [279] */
		"Multi Target Aware",
		'LBIT',
		/* [280] */
		"Multiprocessing Aware",
		'LBIT',
		/* [281] */
		"Uses Target Storage",
		'LBIT',
		/* [282] */
		"Has Compiler-Specific Browser Symbols",
		'LBIT',
		/* [283] */
		"Always Reload",
		'LBIT',
		/* [284] */
		"",
		'LB18',
		/* [285] */
		"Language Type",
		'TNAM',
		/* [286] */
		"C/C++=c++ ",
		'CASE',
		/* [287] */
		"Pascal=pasc",
		'CASE',
		/* [288] */
		"Rez=rez ",
		'CASE',
		/* [289] */
		"java=java",
		'CASE',
		/* [290] */
		"unknown=????",
		'CASE',
		/* [291] */
		"Latest supported API version",
		'DWRD',
		/* [292] */
		"Version 9 (Pro 3)=9",
		'CASE',
		/* [293] */
		"Version 8 (Pro 2)=8",
		'CASE',
		/* [294] */
		"Version 7 (Pro 1)=7",
		'CASE',
		/* [295] */
		"Version 6=6",
		'CASE',
		/* [296] */
		"Version 5=5",
		'CASE',
		/* [297] */
		"CW9=4",
		'CASE',
		/* [298] */
		"CW8=3",
		'CASE',
		/* [299] */
		"Version 2=2",
		'CASE',
		/* [300] */
		"CW7=1",
		'CASE',
		/* [301] */
		"",
		'KEYE',
		/* [302] */
		"Link",
		'KEYB',
		/* [303] */
		"API Version",
		'DWRD',
		/* [304] */
		"Version 9 (Pro 3)=9",
		'CASE',
		/* [305] */
		"Version 8 (Pro 2)=8",
		'CASE',
		/* [306] */
		"Version 7 (Pro 1)=7",
		'CASE',
		/* [307] */
		"Version 5=5",
		'CASE',
		/* [308] */
		"CW9=4",
		'CASE',
		/* [309] */
		"CW8=3",
		'CASE',
		/* [310] */
		"Version 2=2",
		'CASE',
		/* [311] */
		"CW7=1",
		'CASE',
		/* [312] */
		"Can\0x19t Dissassemble",
		'LBIT',
		/* [313] */
		"Post Linker",
		'LBIT',
		/* [314] */
		"Allow Duplicate File Names",
		'LBIT',
		/* [315] */
		"Multi Target Aware",
		'LBIT',
		/* [316] */
		"Pre Linker",
		'LBIT',
		/* [317] */
		"Uses Target Storage",
		'LBIT',
		/* [318] */
		"Unmangles Names",
		'LBIT',
		/* [319] */
		"Magic Cap Linker",
		'LBIT',
		/* [320] */
		"Always Reload",
		'LBIT',
		/* [321] */
		"",
		'LB23',
		/* [322] */
		"reserved(0)",
		'FLNG',
		/* [323] */
		"newest supported API Version",
		'DWRD',
		/* [324] */
		"Version 9 (Pro 3)=9",
		'CASE',
		/* [325] */
		"Version 8 (Pro 2)=8",
		'CASE',
		/* [326] */
		"Version 7 (Pro 1)=7",
		'CASE',
		/* [327] */
		"Version 5=5",
		'CASE',
		/* [328] */
		"CW9=4",
		'CASE',
		/* [329] */
		"CW8=3",
		'CASE',
		/* [330] */
		"Version 2=2",
		'CASE',
		/* [331] */
		"CW7=1",
		'CASE',
		/* [332] */
		"",
		'KEYE',
		/* [333] */
		"VCS ",
		'KEYB',
		/* [334] */
		"API Version",
		'KWRD',
		/* [335] */
		"CW10=5",
		'CASE',
		/* [336] */
		"5",
		'KEYB',
		/* [337] */
		"",
		'LB32',
		/* [338] */
		"",
		'KEYE',
		/* [339] */
		"",
		'KEYE',
		/* [340] */
		"Appl",
		'KEYB',
		/* [341] */
		"API Version",
		'DWRD',
		/* [342] */
		"CW7=1",
		'CASE',
		/* [343] */
		"",
		'LB32',
		/* [344] */
		"",
		'KEYE',
		/* [345] */
		"",
		'KEYE',
		/* [346] */
		"1",
		'KEYB',
		/* [347] */
		"Object type",
		'KTYP',
		/* [348] */
		"Panel=Panl",
		'CASE',
		/* [349] */
		"Compiler=Comp",
		'CASE',
		/* [350] */
		"Linker=Link",
		'CASE',
		/* [351] */
		"Version Control=VCS ",
		'CASE',
		/* [352] */
		"Reserved=Appl",
		'CASE',
		/* [353] */
		"Panl",
		'KEYB',
		/* [354] */
		"API Version",
		'KWRD',
		/* [355] */
		"Pro2=6",
		'CASE',
		/* [356] */
		"CW10=5",
		'CASE',
		/* [357] */
		"CW9=4",
		'CASE',
		/* [358] */
		"CW8=3",
		'CASE',
		/* [359] */
		"Version 2=2",
		'CASE',
		/* [360] */
		"CW7=1",
		'CASE',
		/* [361] */
		"6",
		'KEYB',
		/* [362] */
		"Prefs data version",
		'DWRD',
		/* [363] */
		"Uses strict API",
		'WBIT',
		/* [364] */
		"Supports byte-swapping",
		'WBIT',
		/* [365] */
		"reserved",
		'WB14',
		/* [366] */
		"Family ID",
		'TNAM',
		/* [367] */
		"Project=proj",
		'CASE',
		/* [368] */
		"Front End=fend",
		'CASE',
		/* [369] */
		"Back End=bend",
		'CASE',
		/* [370] */
		"Browser=brow",
		'CASE',
		/* [371] */
		"Editor=edit",
		'CASE',
		/* [372] */
		"Debugger=dbug",
		'CASE',
		/* [373] */
		"Linker=link",
		'CASE',
		/* [374] */
		"Miscellaneous=****",
		'CASE',
		/* [375] */
		"",
		'KEYE',
		/* [376] */
		"5",
		'KEYB',
		/* [377] */
		"Prefs data version",
		'DWRD',
		/* [378] */
		"Uses strict API",
		'WBIT',
		/* [379] */
		"reserved",
		'WB15',
		/* [380] */
		"Family ID",
		'TNAM',
		/* [381] */
		"Project=proj",
		'CASE',
		/* [382] */
		"Front End=fend",
		'CASE',
		/* [383] */
		"Back End=bend",
		'CASE',
		/* [384] */
		"Browser=brow",
		'CASE',
		/* [385] */
		"Editor=edit",
		'CASE',
		/* [386] */
		"Debugger=dbug",
		'CASE',
		/* [387] */
		"Linker=link",
		'CASE',
		/* [388] */
		"Miscellaneous=****",
		'CASE',
		/* [389] */
		"",
		'KEYE',
		/* [390] */
		"4",
		'KEYB',
		/* [391] */
		"Prefs data version",
		'DWRD',
		/* [392] */
		"",
		'WB16',
		/* [393] */
		"Family ID",
		'TNAM',
		/* [394] */
		"Project=proj",
		'CASE',
		/* [395] */
		"Front End=fend",
		'CASE',
		/* [396] */
		"Back End=bend",
		'CASE',
		/* [397] */
		"Browser=brow",
		'CASE',
		/* [398] */
		"Editor=edit",
		'CASE',
		/* [399] */
		"Debugger=dbug",
		'CASE',
		/* [400] */
		"Linker=link",
		'CASE',
		/* [401] */
		"Miscellaneous=****",
		'CASE',
		/* [402] */
		"",
		'KEYE',
		/* [403] */
		"3",
		'KEYB',
		/* [404] */
		"Prefs data version",
		'DWRD',
		/* [405] */
		"",
		'WB16',
		/* [406] */
		"Family ID",
		'TNAM',
		/* [407] */
		"Project=proj",
		'CASE',
		/* [408] */
		"Front End=fend",
		'CASE',
		/* [409] */
		"Back End=bend",
		'CASE',
		/* [410] */
		"Browser=brow",
		'CASE',
		/* [411] */
		"Editor=edit",
		'CASE',
		/* [412] */
		"Debugger=dbug",
		'CASE',
		/* [413] */
		"Linker=link",
		'CASE',
		/* [414] */
		"Miscellaneous=****",
		'CASE',
		/* [415] */
		"",
		'KEYE',
		/* [416] */
		"2",
		'KEYB',
		/* [417] */
		"Prefs data version",
		'DWRD',
		/* [418] */
		"",
		'WB16',
		/* [419] */
		"Family ID",
		'TNAM',
		/* [420] */
		"Project=proj",
		'CASE',
		/* [421] */
		"Front End=fend",
		'CASE',
		/* [422] */
		"Back End=bend",
		'CASE',
		/* [423] */
		"Browser=brow",
		'CASE',
		/* [424] */
		"Editor=edit",
		'CASE',
		/* [425] */
		"Debugger=dbug",
		'CASE',
		/* [426] */
		"Linker=link",
		'CASE',
		/* [427] */
		"Miscellaneous=****",
		'CASE',
		/* [428] */
		"",
		'KEYE',
		/* [429] */
		"1",
		'KEYB',
		/* [430] */
		"",
		'LB32',
		/* [431] */
		"",
		'KEYE',
		/* [432] */
		"",
		'KEYE',
		/* [433] */
		"Comp",
		'KEYB',
		/* [434] */
		"API Version",
		'KWRD',
		/* [435] */
		"Version 8=8",
		'CASE',
		/* [436] */
		"Version 7=7",
		'CASE',
		/* [437] */
		"Version 6=6",
		'CASE',
		/* [438] */
		"Version 5=5",
		'CASE',
		/* [439] */
		"CW9=4",
		'CASE',
		/* [440] */
		"CW8=3",
		'CASE',
		/* [441] */
		"Version 2=2",
		'CASE',
		/* [442] */
		"CW7=1",
		'CASE',
		/* [443] */
		"8",
		'KEYB',
		/* [444] */
		"Generates Code",
		'LBIT',
		/* [445] */
		"Generates Resources",
		'LBIT',
		/* [446] */
		"Can Preprocess",
		'LBIT',
		/* [447] */
		"Can Precompile",
		'LBIT',
		/* [448] */
		"Is Pascal",
		'LBIT',
		/* [449] */
		"Can Import",
		'LBIT',
		/* [450] */
		"Can Disassemble",
		'LBIT',
		/* [451] */
		"Persistent",
		'LBIT',
		/* [452] */
		"Allow Duplicate File Names",
		'LBIT',
		/* [453] */
		"Multi Target Aware",
		'LBIT',
		/* [454] */
		"Multiprocessing Aware",
		'LBIT',
		/* [455] */
		"Uses Target Storage",
		'LBIT',
		/* [456] */
		"Has Compiler-Specific Browser Symbols",
		'LBIT',
		/* [457] */
		"",
		'LB19',
		/* [458] */
		"Language Type",
		'TNAM',
		/* [459] */
		"C/C++=c++ ",
		'CASE',
		/* [460] */
		"Pascal=pasc",
		'CASE',
		/* [461] */
		"Rez=rez ",
		'CASE',
		/* [462] */
		"java=java",
		'CASE',
		/* [463] */
		"unknown=????",
		'CASE',
		/* [464] */
		"Latest supported API version",
		'DWRD',
		/* [465] */
		"Version 8=8",
		'CASE',
		/* [466] */
		"Version 7=7",
		'CASE',
		/* [467] */
		"Version 6=6",
		'CASE',
		/* [468] */
		"Version 5=5",
		'CASE',
		/* [469] */
		"CW9=4",
		'CASE',
		/* [470] */
		"CW8=3",
		'CASE',
		/* [471] */
		"Version 2=2",
		'CASE',
		/* [472] */
		"CW7=1",
		'CASE',
		/* [473] */
		"",
		'KEYE',
		/* [474] */
		"7",
		'KEYB',
		/* [475] */
		"Generates Code",
		'LBIT',
		/* [476] */
		"Generates Resources",
		'LBIT',
		/* [477] */
		"Can Preprocess",
		'LBIT',
		/* [478] */
		"Can Precompile",
		'LBIT',
		/* [479] */
		"Is Pascal",
		'LBIT',
		/* [480] */
		"Can Import",
		'LBIT',
		/* [481] */
		"Can Disassemble",
		'LBIT',
		/* [482] */
		"Persistent",
		'LBIT',
		/* [483] */
		"Allow Duplicate File Names",
		'LBIT',
		/* [484] */
		"Multi Target Aware",
		'LBIT',
		/* [485] */
		"Multiprocessing Aware",
		'LBIT',
		/* [486] */
		"",
		'LB21',
		/* [487] */
		"Language Type",
		'TNAM',
		/* [488] */
		"C/C++=c++ ",
		'CASE',
		/* [489] */
		"Pascal=pasc",
		'CASE',
		/* [490] */
		"Rez=rez ",
		'CASE',
		/* [491] */
		"java=java",
		'CASE',
		/* [492] */
		"unknown=????",
		'CASE',
		/* [493] */
		"",
		'KEYE',
		/* [494] */
		"6",
		'KEYB',
		/* [495] */
		"Generates Code",
		'LBIT',
		/* [496] */
		"Generates Resources",
		'LBIT',
		/* [497] */
		"Can Preprocess",
		'LBIT',
		/* [498] */
		"Can Precompile",
		'LBIT',
		/* [499] */
		"Is Pascal",
		'LBIT',
		/* [500] */
		"Can Import",
		'LBIT',
		/* [501] */
		"Can Disassemble",
		'LBIT',
		/* [502] */
		"Persistent",
		'LBIT',
		/* [503] */
		"Allow Duplicate File Names",
		'LBIT',
		/* [504] */
		"Multi Target Aware",
		'LBIT',
		/* [505] */
		"Multiprocessing Aware",
		'LBIT',
		/* [506] */
		"",
		'LB21',
		/* [507] */
		"Language Type",
		'TNAM',
		/* [508] */
		"C/C++=c++ ",
		'CASE',
		/* [509] */
		"Pascal=pasc",
		'CASE',
		/* [510] */
		"Rez=rez ",
		'CASE',
		/* [511] */
		"java=java",
		'CASE',
		/* [512] */
		"unknown=????",
		'CASE',
		/* [513] */
		"",
		'KEYE',
		/* [514] */
		"5",
		'KEYB',
		/* [515] */
		"Generates Code",
		'LBIT',
		/* [516] */
		"Generates Resources",
		'LBIT',
		/* [517] */
		"Can Preprocess",
		'LBIT',
		/* [518] */
		"Can Precompile",
		'LBIT',
		/* [519] */
		"Is Pascal",
		'LBIT',
		/* [520] */
		"Can Import",
		'LBIT',
		/* [521] */
		"Can Disassemble",
		'LBIT',
		/* [522] */
		"Persistent",
		'LBIT',
		/* [523] */
		"",
		'LB24',
		/* [524] */
		"Language Type",
		'TNAM',
		/* [525] */
		"C/C++=c++ ",
		'CASE',
		/* [526] */
		"Pascal=pasc",
		'CASE',
		/* [527] */
		"Rez=rez ",
		'CASE',
		/* [528] */
		"java=java",
		'CASE',
		/* [529] */
		"unknown=????",
		'CASE',
		/* [530] */
		"",
		'KEYE',
		/* [531] */
		"4",
		'KEYB',
		/* [532] */
		"Generates Code",
		'LBIT',
		/* [533] */
		"Generates Resources",
		'LBIT',
		/* [534] */
		"Can Preprocess",
		'LBIT',
		/* [535] */
		"Can Precompile",
		'LBIT',
		/* [536] */
		"Is Pascal",
		'LBIT',
		/* [537] */
		"Can Import",
		'LBIT',
		/* [538] */
		"",
		'LB26',
		/* [539] */
		"Language Type",
		'TNAM',
		/* [540] */
		"C/C++=c++ ",
		'CASE',
		/* [541] */
		"Pascal=pasc",
		'CASE',
		/* [542] */
		"Rez=rez ",
		'CASE',
		/* [543] */
		"java=java",
		'CASE',
		/* [544] */
		"unknown=????",
		'CASE',
		/* [545] */
		"",
		'KEYE',
		/* [546] */
		"3",
		'KEYB',
		/* [547] */
		"Generates Code",
		'LBIT',
		/* [548] */
		"Generates Resources",
		'LBIT',
		/* [549] */
		"Can Preprocess",
		'LBIT',
		/* [550] */
		"Can Precompile",
		'LBIT',
		/* [551] */
		"Is Pascal",
		'LBIT',
		/* [552] */
		"Can Import",
		'LBIT',
		/* [553] */
		"",
		'LB26',
		/* [554] */
		"Language Type",
		'TNAM',
		/* [555] */
		"C/C++=c++ ",
		'CASE',
		/* [556] */
		"Pascal=pasc",
		'CASE',
		/* [557] */
		"Rez=rez ",
		'CASE',
		/* [558] */
		"unknown=????",
		'CASE',
		/* [559] */
		"",
		'KEYE',
		/* [560] */
		"2",
		'KEYB',
		/* [561] */
		"Generates Code",
		'LBIT',
		/* [562] */
		"Generates Resources",
		'LBIT',
		/* [563] */
		"Can Preprocess",
		'LBIT',
		/* [564] */
		"Can Precompile",
		'LBIT',
		/* [565] */
		"Is Pascal",
		'LBIT',
		/* [566] */
		"Can Import",
		'LBIT',
		/* [567] */
		"",
		'LB26',
		/* [568] */
		"Language Type",
		'TNAM',
		/* [569] */
		"C/C++=c++ ",
		'CASE',
		/* [570] */
		"Pascal=pasc",
		'CASE',
		/* [571] */
		"Rez=rez ",
		'CASE',
		/* [572] */
		"unknown=????",
		'CASE',
		/* [573] */
		"",
		'KEYE',
		/* [574] */
		"1",
		'KEYB',
		/* [575] */
		"Generates Code",
		'LBIT',
		/* [576] */
		"Generates Resources",
		'LBIT',
		/* [577] */
		"Can Preprocess",
		'LBIT',
		/* [578] */
		"Can Precompile",
		'LBIT',
		/* [579] */
		"Is Pascal",
		'LBIT',
		/* [580] */
		"Can Import",
		'LBIT',
		/* [581] */
		"",
		'LB26',
		/* [582] */
		"",
		'KEYE',
		/* [583] */
		"",
		'KEYE',
		/* [584] */
		"Link",
		'KEYB',
		/* [585] */
		"API Version",
		'KWRD',
		/* [586] */
		"Version 8=8",
		'CASE',
		/* [587] */
		"Version 7=7",
		'CASE',
		/* [588] */
		"Version 5=5",
		'CASE',
		/* [589] */
		"CW9=4",
		'CASE',
		/* [590] */
		"CW8=3",
		'CASE',
		/* [591] */
		"Version 2=2",
		'CASE',
		/* [592] */
		"CW7=1",
		'CASE',
		/* [593] */
		"8",
		'KEYB',
		/* [594] */
		"Can\0x19t Dissassemble",
		'LBIT',
		/* [595] */
		"Post Linker",
		'LBIT',
		/* [596] */
		"Allow Duplicate File Names",
		'LBIT',
		/* [597] */
		"Multi Target Aware",
		'LBIT',
		/* [598] */
		"Pre Linker",
		'LBIT',
		/* [599] */
		"Uses Target Storage",
		'LBIT',
		/* [600] */
		"Unmangles Names",
		'LBIT',
		/* [601] */
		"Magic Cap Linker",
		'LBIT',
		/* [602] */
		"",
		'LB24',
		/* [603] */
		"reserved(0)",
		'FLNG',
		/* [604] */
		"newest supported API Version",
		'DWRD',
		/* [605] */
		"Version 8=8",
		'CASE',
		/* [606] */
		"Version 7=7",
		'CASE',
		/* [607] */
		"Version 5=5",
		'CASE',
		/* [608] */
		"CW9=4",
		'CASE',
		/* [609] */
		"CW8=3",
		'CASE',
		/* [610] */
		"Version 2=2",
		'CASE',
		/* [611] */
		"CW7=1",
		'CASE',
		/* [612] */
		"",
		'KEYE',
		/* [613] */
		"7",
		'KEYB',
		/* [614] */
		"Can\0x19t Dissassemble",
		'LBIT',
		/* [615] */
		"Post Linker",
		'LBIT',
		/* [616] */
		"Allow Duplicate File Names",
		'LBIT',
		/* [617] */
		"Multi Target Aware",
		'LBIT',
		/* [618] */
		"",
		'LB28',
		/* [619] */
		"",
		'KEYE',
		/* [620] */
		"5",
		'KEYB',
		/* [621] */
		"Can\0x19t Dissassemble",
		'LBIT',
		/* [622] */
		"Post Linker",
		'LBIT',
		/* [623] */
		"Allow Duplicate File Names",
		'LBIT',
		/* [624] */
		"Multi Target Aware",
		'LBIT',
		/* [625] */
		"",
		'LB28',
		/* [626] */
		"",
		'KEYE',
		/* [627] */
		"4",
		'KEYB',
		/* [628] */
		"Can\0x19t Disassemble",
		'LBIT',
		/* [629] */
		"",
		'LB31',
		/* [630] */
		"",
		'KEYE',
		/* [631] */
		"3",
		'KEYB',
		/* [632] */
		"Can\0x19t Disassemble",
		'LBIT',
		/* [633] */
		"",
		'LB31',
		/* [634] */
		"",
		'KEYE',
		/* [635] */
		"2",
		'KEYB',
		/* [636] */
		"Can\0x19t Disassemble",
		'LBIT',
		/* [637] */
		"",
		'LB31',
		/* [638] */
		"",
		'KEYE',
		/* [639] */
		"1",
		'KEYB',
		/* [640] */
		"",
		'LB32',
		/* [641] */
		"",
		'KEYE',
		/* [642] */
		"",
		'KEYE',
		/* [643] */
		"VCS ",
		'KEYB',
		/* [644] */
		"API Version",
		'KWRD',
		/* [645] */
		"CW10=5",
		'CASE',
		/* [646] */
		"5",
		'KEYB',
		/* [647] */
		"",
		'LB32',
		/* [648] */
		"",
		'KEYE',
		/* [649] */
		"",
		'KEYE',
		/* [650] */
		"Appl",
		'KEYB',
		/* [651] */
		"API Version",
		'DWRD',
		/* [652] */
		"CW7=1",
		'CASE',
		/* [653] */
		"",
		'LB32',
		/* [654] */
		"",
		'KEYE',
		/* [655] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1114, "fld#") {
	{	/* array: 18 elements */
		/* [1] */
		"Folders",
		'LSTB',
		/* [2] */
		"Folder type",
		'TNAM',
		/* [3] */
		"Apple Menu Items=amnu",
		'CASE',
		/* [4] */
		"Control Panels=ctrl",
		'CASE',
		/* [5] */
		"Desktop Folder=desk",
		'CASE',
		/* [6] */
		"Extensions=extn",
		'CASE',
		/* [7] */
		"Preferences=pref",
		'CASE',
		/* [8] */
		"PrintMonitor Documents=prnt",
		'CASE',
		/* [9] */
		"Shared Network Trash=empt",
		'CASE',
		/* [10] */
		"Single-user Trash=trsh",
		'CASE',
		/* [11] */
		"Shutdown items=shdf",
		'CASE',
		/* [12] */
		"Startup Items=strt",
		'CASE',
		/* [13] */
		"System Folder=macs",
		'CASE',
		/* [14] */
		"Temporary Items=temp",
		'CASE',
		/* [15] */
		"Version",
		'DWRD',
		/* [16] */
		"Length high byte",
		'FBYT',
		/* [17] */
		"Folder name",
		'OSTR',
		/* [18] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1115, "FLOG") {
	{	/* array: 3 elements */
		/* [1] */
		"File creator for font log",
		'TNAM',
		/* [2] */
		"File type for font log",
		'TNAM',
		/* [3] */
		"Log file name suffix",
		'ESTR'
	}
};

resource 'TMPL' (1116, "flst") {
	{	/* array: 16 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"Fonts",
		'LSTC',
		/* [3] */
		"Font name",
		'PSTR',
		/* [4] */
		"Alignment",
		'AWRD',
		/* [5] */
		"Style",
		'WORV',
		/* [6] */
		"Plain=0",
		'CASE',
		/* [7] */
		"Bold=1",
		'CASE',
		/* [8] */
		"Italic=2",
		'CASE',
		/* [9] */
		"Underline=4",
		'CASE',
		/* [10] */
		"Outline=8",
		'CASE',
		/* [11] */
		"Shadow=16",
		'CASE',
		/* [12] */
		"Condensed=32",
		'CASE',
		/* [13] */
		"Extended=64",
		'CASE',
		/* [14] */
		"Font size",
		'DWRD',
		/* [15] */
		"Font mode",
		'DWRD',
		/* [16] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1117, "fmap") {
	{	/* array: 5 elements */
		/* [1] */
		"The last list item must be a pair of NUL"
		"Ls (don't change it)",
		'DVDR',
		/* [2] */
		"*****",
		'LSTB',
		/* [3] */
		"Type",
		'TNAM',
		/* [4] */
		"Index/OSType",
		'DLNG',
		/* [5] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1118, "Fmly") {
	{	/* array: 15 elements */
		/* [1] */
		"CW Plugin resource format",
		'DVDR',
		/* [2] */
		"Version",
		'DWRD',
		/* [3] */
		"Current=1",
		'CASE',
		/* [4] */
		"Family ID",
		'TNAM',
		/* [5] */
		"Project=proj",
		'CASE',
		/* [6] */
		"Front End=fend",
		'CASE',
		/* [7] */
		"Back End=bend",
		'CASE',
		/* [8] */
		"Browser=brow",
		'CASE',
		/* [9] */
		"Editor=edit",
		'CASE',
		/* [10] */
		"Debugger=dbug",
		'CASE',
		/* [11] */
		"Linker=link",
		'CASE',
		/* [12] */
		"Version Control=vcs ",
		'CASE',
		/* [13] */
		"Miscellaneous=****",
		'CASE',
		/* [14] */
		"RAD Tools=radt",
		'CASE',
		/* [15] */
		"Family Name",
		'P040'
	}
};

resource 'TMPL' (1119, "fmn2") {
	{	/* array: 18 elements */
		/* [1] */
		"Menu name",
		'DWRD',
		/* [2] */
		"Count",
		'DWRD',
		/* [3] */
		"Unused",
		'FWRD',
		/* [4] */
		"Menu ID",
		'DWRD',
		/* [5] */
		"Unused",
		'DWRD',
		/* [6] */
		"Unused",
		'DWRD',
		/* [7] */
		"Unused",
		'DWRD',
		/* [8] */
		"Unused",
		'DWRD',
		/* [9] */
		"Menu item",
		'ESTR',
		/* [10] */
		"Items",
		'LSTB',
		/* [11] */
		"Command",
		'TNAM',
		/* [12] */
		"Flag",
		'DWRD',
		/* [13] */
		"Unused",
		'DWRD',
		/* [14] */
		"Unused",
		'DWRD',
		/* [15] */
		"ShortCut",
		'CHAR',
		/* [16] */
		"Unused",
		'FBYT',
		/* [17] */
		"MenuItem",
		'ESTR',
		/* [18] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1120, "fmnu") {
	{	/* array: 18 elements */
		/* [1] */
		"Auto-initialize",
		'WFLG',
		/* [2] */
		"Count:",
		'ZCNT',
		/* [3] */
		"List of Menu items",
		'LSTC',
		/* [4] */
		"Command code (resource ID for item 1)",
		'TNAM',
		/* [5] */
		"Private flags",
		'DVDR',
		/* [6] */
		"Bit 15",
		'WBIT',
		/* [7] */
		"Bit 14",
		'WBIT',
		/* [8] */
		"Bit 13",
		'WBIT',
		/* [9] */
		"Bits 8-12",
		'WB05',
		/* [10] */
		"Bit 7",
		'WBIT',
		/* [11] */
		"Bit 6",
		'WBIT',
		/* [12] */
		"Bits 1-5",
		'WB05',
		/* [13] */
		"Bit 0",
		'WBIT',
		/* [14] */
		"Key equivalent",
		'CHAR',
		/* [15] */
		"None=$00",
		'CASE',
		/* [16] */
		"Align",
		'AWRD',
		/* [17] */
		"Item name or menu title",
		'ESTR',
		/* [18] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1121, "FOND") {
	{	/* array: 37 elements */
		/* [1] */
		"Proportional or fixed width",
		'WBIT',
		/* [2] */
		"Don't use fractional width table",
		'WBIT',
		/* [3] */
		"Use integer extra width for styles",
		'WBIT',
		/* [4] */
		"Ignore FractEnable ",
		'WBIT',
		/* [5] */
		"Don't adjust char spacing",
		'WBIT',
		/* [6] */
		"Reserved",
		'WB09',
		/* [7] */
		"Has a char width table?",
		'WBIT',
		/* [8] */
		"Has an image height table?",
		'WBIT',
		/* [9] */
		"Family ID",
		'DWRD',
		/* [10] */
		"ASCII code of first char",
		'HWRD',
		/* [11] */
		"ASCII code of last char",
		'HWRD',
		/* [12] */
		"Maximum ascent",
		'DWRD',
		/* [13] */
		"Maximum descent",
		'DWRD',
		/* [14] */
		"Maximum leading",
		'DWRD',
		/* [15] */
		"Maximum width",
		'DWRD',
		/* [16] */
		"Offsets: 0 means \"no tables\"",
		'DVDR',
		/* [17] */
		"Offset to width tables",
		'HLNG',
		/* [18] */
		"Offset to kerning tables",
		'HLNG',
		/* [19] */
		"Offset to style mapping tables",
		'HLNG',
		/* [20] */
		"Unused",
		'HWRD',
		/* [21] */
		"Extra width for Bold",
		'HWRD',
		/* [22] */
		"Extra width for Italic",
		'HWRD',
		/* [23] */
		"Extra width for Underline",
		'HWRD',
		/* [24] */
		"Extra width for Outline",
		'HWRD',
		/* [25] */
		"Extra width for Shadow",
		'HWRD',
		/* [26] */
		"Extra width for Condensed",
		'HWRD',
		/* [27] */
		"Extra width for Extended",
		'HWRD',
		/* [28] */
		"Undefined",
		'HWRD',
		/* [29] */
		"Reserved for International",
		'HLNG',
		/* [30] */
		"Version number",
		'HWRD',
		/* [31] */
		"Count:",
		'ZCNT',
		/* [32] */
		"Font association table",
		'LSTC',
		/* [33] */
		"Font size",
		'DWRD',
		/* [34] */
		"Font style",
		'DWRD',
		/* [35] */
		"Resource ID of FONT",
		'RSID',
		/* [36] */
		"*****",
		'LSTE',
		/* [37] */
		"Tables...",
		'HEXD'
	}
};

resource 'TMPL' (1122, "FONT") {
	{	/* array: 29 elements */
		/* [1] */
		"Reserved (on)",
		'BBIT',
		/* [2] */
		"Do expand font",
		'BBIT',
		/* [3] */
		"Proportional font",
		'BBIT',
		/* [4] */
		"Reserved (on)",
		'BBIT',
		/* [5] */
		"Reserved (off)",
		'BBIT',
		/* [6] */
		"Reserved (off)",
		'BBIT',
		/* [7] */
		"Black font",
		'BBIT',
		/* [8] */
		"Not synthetic",
		'BBIT',
		/* [9] */
		"No 'fctb' resource",
		'BBIT',
		/* [10] */
		"Reserved (off)",
		'BBIT',
		/* [11] */
		"Reserved (off)",
		'BBIT',
		/* [12] */
		"Reserved (off)",
		'BBIT',
		/* [13] */
		"Font depth (first bit)",
		'BBIT',
		/* [14] */
		"Font depth (second bit)",
		'BBIT',
		/* [15] */
		"No char width table",
		'BBIT',
		/* [16] */
		"No image height table",
		'BBIT',
		/* [17] */
		"First char",
		'DWRD',
		/* [18] */
		"Last char",
		'DWRD',
		/* [19] */
		"Width max",
		'DWRD',
		/* [20] */
		"Kern max",
		'DWRD',
		/* [21] */
		"Neg descent",
		'DWRD',
		/* [22] */
		"Font rect width",
		'DWRD',
		/* [23] */
		"Char height",
		'DWRD',
		/* [24] */
		"Offset to off/wid table",
		'DWRD',
		/* [25] */
		"Ascent",
		'DWRD',
		/* [26] */
		"Descent",
		'DWRD',
		/* [27] */
		"Leading",
		'DWRD',
		/* [28] */
		"Row width (in words)",
		'DWRD',
		/* [29] */
		"Font tables",
		'HEXD'
	}
};

resource 'TMPL' (1123, "FREF") {
	{	/* array: 3 elements */
		/* [1] */
		"File type",
		'TNAM',
		/* [2] */
		"Icon local ID",
		'DWRD',
		/* [3] */
		"File name",
		'PSTR'
	}
};

resource 'TMPL' (1124, "FRSV") {
	{	/* array: 12 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"Reserved fonts",
		'LSTC',
		/* [3] */
		"Font family ID",
		'WB09',
		/* [4] */
		"Chicago=0",
		'CASE',
		/* [5] */
		"NewYork=2",
		'CASE',
		/* [6] */
		"Geneva=3",
		'CASE',
		/* [7] */
		"Monaco=4",
		'CASE',
		/* [8] */
		"Times=20",
		'CASE',
		/* [9] */
		"Helvetica=21",
		'CASE',
		/* [10] */
		"Courier=22",
		'CASE',
		/* [11] */
		"Font size",
		'WB07',
		/* [12] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1125, "FSty") {
	{	/* array: 12 elements */
		/* [1] */
		"\"Finale\" resource format",
		'DVDR',
		/* [2] */
		"Font size",
		'DWRD',
		/* [3] */
		"Unused style bits",
		'FBYT',
		/* [4] */
		"Unused",
		'BBIT',
		/* [5] */
		"Extended",
		'BBIT',
		/* [6] */
		"Condensed",
		'BBIT',
		/* [7] */
		"Shadow",
		'BBIT',
		/* [8] */
		"Outline",
		'BBIT',
		/* [9] */
		"Underline",
		'BBIT',
		/* [10] */
		"Italic",
		'BBIT',
		/* [11] */
		"Bold",
		'BBIT',
		/* [12] */
		"Font name",
		'PSTR'
	}
};

resource 'TMPL' (1126, "FTLS") {
	{	/* array: 5 elements */
		/* [1] */
		"\"SuitCase\" resource format",
		'DVDR',
		/* [2] */
		"Count:",
		'LCNT',
		/* [3] */
		"File Types",
		'LSTC',
		/* [4] */
		"Type",
		'TNAM',
		/* [5] */
		"",
		'LSTE'
	}
};

resource 'TMPL' (1127, "FtSz") {
	{	/* array: 1 elements */
		/* [1] */
		"Font size or other pref value",
		'DWRD'
	}
};

resource 'TMPL' (1128, "ftyp") {
	{	/* array: 5 elements */
		/* [1] */
		"\"SuitCase\" resource format",
		'DVDR',
		/* [2] */
		"Count:",
		'LCNT',
		/* [3] */
		"File types",
		'LSTC',
		/* [4] */
		"Type",
		'TNAM',
		/* [5] */
		"-----",
		'LSTE'
	}
};

resource 'TMPL' (1129, "fval") {
	{	/* array: 34 elements */
		/* [1] */
		"Version",
		'DLNG',
		/* [2] */
		"Trash location",
		'PNT ',
		/* [3] */
		"Application font",
		'DWRD',
		/* [4] */
		"Geneva=9",
		'CASE',
		/* [5] */
		"Application font size",
		'DWRD',
		/* [6] */
		"9 pt=9",
		'CASE',
		/* [7] */
		"10 pt=10",
		'CASE',
		/* [8] */
		"11 pt==11",
		'CASE',
		/* [9] */
		"12 pt=12",
		'CASE',
		/* [10] */
		"14 pt=14",
		'CASE',
		/* [11] */
		"18 pt=18",
		'CASE',
		/* [12] */
		"24 pt=24",
		'CASE',
		/* [13] */
		"36 pt=36",
		'CASE',
		/* [14] */
		"Confirm empty trash",
		'WFLG',
		/* [15] */
		"Stagger icons",
		'WFLG',
		/* [16] */
		"Grid icons",
		'WFLG',
		/* [17] */
		"Icon size",
		'DWRD',
		/* [18] */
		"Large=2",
		'CASE',
		/* [19] */
		"Small=1",
		'CASE',
		/* [20] */
		"Show folder sizes",
		'WFLG',
		/* [21] */
		"Show disk info",
		'WFLG',
		/* [22] */
		"Show size",
		'WFLG',
		/* [23] */
		"Show kind",
		'WFLG',
		/* [24] */
		"Show label",
		'WFLG',
		/* [25] */
		"Show date",
		'WFLG',
		/* [26] */
		"Show version",
		'WFLG',
		/* [27] */
		"Show comment",
		'WFLG',
		/* [28] */
		"Sort style",
		'DWRD',
		/* [29] */
		"Date abbreviation",
		'DWRD',
		/* [30] */
		"Reserved",
		'FWRD',
		/* [31] */
		"Min application font size",
		'DWRD',
		/* [32] */
		"Max application font size",
		'DWRD',
		/* [33] */
		"Reserved",
		'FWRD',
		/* [34] */
		"Reserved",
		'FWRD'
	}
};

resource 'TMPL' (1130, "FWID") {
	{	/* array: 17 elements */
		/* [1] */
		"Font type",
		'HWRD',
		/* [2] */
		"First char",
		'DWRD',
		/* [3] */
		"Last char",
		'DWRD',
		/* [4] */
		"Max width",
		'DWRD',
		/* [5] */
		"Max kern",
		'DWRD',
		/* [6] */
		"Negative descent",
		'DWRD',
		/* [7] */
		"Font rect width",
		'DWRD',
		/* [8] */
		"Font rect height",
		'DWRD',
		/* [9] */
		"Offset to offset/width table",
		'HWRD',
		/* [10] */
		"Ascent",
		'DWRD',
		/* [11] */
		"Descent",
		'DWRD',
		/* [12] */
		"Leading",
		'DWRD',
		/* [13] */
		"Row width (in words)",
		'DWRD',
		/* [14] */
		"Char values table",
		'LSTB',
		/* [15] */
		"Char offset",
		'DBYT',
		/* [16] */
		"Char width",
		'DBYT',
		/* [17] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1131, "gdir") {
	{	/* array: 2 elements */
		/* [1] */
		"Type",
		'TNAM',
		/* [2] */
		"Zero terminator",
		'FBYT'
	}
};

resource 'TMPL' (1132, "gmcd") {
	{	/* array: 5 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"List of Resources",
		'LSTC',
		/* [3] */
		"Resource type",
		'TNAM',
		/* [4] */
		"Resource ID",
		'RSID',
		/* [5] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1133, "GNRL") {
	{	/* array: 23 elements */
		/* [1] */
		"Show sys warn",
		'DWRD',
		/* [2] */
		"Open at start",
		'DWRD',
		/* [3] */
		"Pick width",
		'DWRD',
		/* [4] */
		"Pick height",
		'DWRD',
		/* [5] */
		"Types width",
		'DWRD',
		/* [6] */
		"Types height",
		'DWRD',
		/* [7] */
		"Use icon view",
		'DBYT',
		/* [8] */
		"Show size",
		'DBYT',
		/* [9] */
		"Prefs version",
		'DWRD',
		/* [10] */
		"Wind warn lim",
		'DWRD',
		/* [11] */
		"Verify on open",
		'DWRD',
		/* [12] */
		"Auto size",
		'DBYT',
		/* [13] */
		"Stack all windows",
		'DBYT',
		/* [14] */
		"No stack can col",
		'DBYT',
		/* [15] */
		"No show splash",
		'DBYT',
		/* [16] */
		"No zoom rects",
		'DBYT',
		/* [17] */
		"Unused",
		'DBYT',
		/* [18] */
		"Unused",
		'DBYT',
		/* [19] */
		"Unused",
		'DBYT',
		/* [20] */
		"Unused",
		'DWRD',
		/* [21] */
		"Unused",
		'DWRD',
		/* [22] */
		"Unused",
		'DWRD',
		/* [23] */
		"Unused",
		'DWRD'
	}
};

resource 'TMPL' (1134, "GOBJ") {
	{	/* array: 9 elements */
		/* [1] */
		"",
		'LSTB',
		/* [2] */
		"Name",
		'TNAM',
		/* [3] */
		"Kind",
		'TNAM',
		/* [4] */
		"Resource ID",
		'DWRD',
		/* [5] */
		"Rect",
		'RECT',
		/* [6] */
		"Title",
		'P040',
		/* [7] */
		"Text offset",
		'PNT ',
		/* [8] */
		"Text style resource ID",
		'DWRD',
		/* [9] */
		"",
		'LSTE'
	}
};

resource 'TMPL' (1135, "HAlt") {
	{	/* array: 36 elements */
		/* [1] */
		"Version number",
		'KWRD',
		/* [2] */
		"Alrt=1",
		'CASE',
		/* [3] */
		"1",
		'KEYB',
		/* [4] */
		"Alert Type",
		'DWRD',
		/* [5] */
		"Stop Alert=0",
		'CASE',
		/* [6] */
		"Note Alert=1",
		'CASE',
		/* [7] */
		"Caution Alert=2",
		'CASE',
		/* [8] */
		"Plain Alert=3",
		'CASE',
		/* [9] */
		"Error string",
		'PSTR',
		/* [10] */
		"Explanation string",
		'PSTR',
		/* [11] */
		"Is movable?",
		'BOOL',
		/* [12] */
		"Has Help button?",
		'BOOL',
		/* [13] */
		"Default button text",
		'PSTR',
		/* [14] */
		"Cancel button text (leave blank to have "
		"no Cancel button)",
		'PSTR',
		/* [15] */
		"Other button text (leave blank to have n"
		"o Other button)",
		'PSTR',
		/* [16] */
		"Default Button",
		'DWRD',
		/* [17] */
		"OK=1",
		'CASE',
		/* [18] */
		"Cancel=2",
		'CASE',
		/* [19] */
		"Other=3",
		'CASE',
		/* [20] */
		"Cancel Button",
		'DWRD',
		/* [21] */
		"None=0",
		'CASE',
		/* [22] */
		"OK=1",
		'CASE',
		/* [23] */
		"Cancel=2",
		'CASE',
		/* [24] */
		"Other=3",
		'CASE',
		/* [25] */
		"Position",
		'UWRD',
		/* [26] */
		"Default (alert parent window screen)=$00"
		"00",
		'CASE',
		/* [27] */
		"Center on Main Screen=$280A",
		'CASE',
		/* [28] */
		"Alert Position on Main Screen=$300A",
		'CASE',
		/* [29] */
		"Stagger on Main Screen=$380A",
		'CASE',
		/* [30] */
		"Center on Parent Window=$A80A",
		'CASE',
		/* [31] */
		"Alert Position on Parent Window=$B00A",
		'CASE',
		/* [32] */
		"Stagger on Parent Window=$B80A",
		'CASE',
		/* [33] */
		"Center on Parent Window Screen=$680A",
		'CASE',
		/* [34] */
		"Alert Position on Parent Window Screen=$"
		"700A",
		'CASE',
		/* [35] */
		"Stagger on Parent Window Screen=$780A",
		'CASE',
		/* [36] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1136, "hdlg") {
	{	/* array: 142 elements */
		/* [1] */
		"Balloon help version",
		'DWRD',
		/* [2] */
		"Latest=2",
		'CASE',
		/* [3] */
		"Item offset for first message",
		'DWRD',
		/* [4] */
		"Start messages at Item #1=0",
		'CASE',
		/* [5] */
		"Reserved",
		'LB27',
		/* [6] */
		"For 'hwin's, match string anywhere in ti"
		"tle",
		'LB01',
		/* [7] */
		"Create window, restore bits, and cause u"
		"pdate",
		'LB01',
		/* [8] */
		"Don't create window, restore bits, no up"
		"date",
		'LB01',
		/* [9] */
		"Pretend window port origin is set to (0,"
		"0)",
		'LB01',
		/* [10] */
		"Treat resource IDs as sub-IDs for owned "
		"resources of a D/A, etc.",
		'LB01',
		/* [11] */
		"Balloon 'WDEF' resID",
		'RSID',
		/* [12] */
		"Standard balloons=0",
		'CASE',
		/* [13] */
		"Balloon variation code (tip position)",
		'DWRD',
		/* [14] */
		"Along left side at top=0",
		'CASE',
		/* [15] */
		"Along top at left=1",
		'CASE',
		/* [16] */
		"Along top on right=2",
		'CASE',
		/* [17] */
		"Along right side at top=3",
		'CASE',
		/* [18] */
		"Along right side at bottom=4",
		'CASE',
		/* [19] */
		"Along bottom at right=5",
		'CASE',
		/* [20] */
		"Along bottom at left=6",
		'CASE',
		/* [21] */
		"Along left side at bottom=7",
		'CASE',
		/* [22] */
		"Count:",
		'OCNT',
		/* [23] */
		"Number of bytes to next record",
		'SKIP',
		/* [24] */
		"Missing message type",
		'KWRD',
		/* [25] */
		"Skip missing item=256",
		'CASE',
		/* [26] */
		"Use these strings=1",
		'CASE',
		/* [27] */
		"Use 'PICT' resources=2",
		'CASE',
		/* [28] */
		"Use 'STR#' resources=3",
		'CASE',
		/* [29] */
		"Use styled text resources=6",
		'CASE',
		/* [30] */
		"Use 'STR ' resources=7",
		'CASE',
		/* [31] */
		"256",
		'KEYB',
		/* [32] */
		"",
		'KEYE',
		/* [33] */
		"1",
		'KEYB',
		/* [34] */
		"Tip",
		'PNT ',
		/* [35] */
		"Hot rect",
		'RECT',
		/* [36] */
		"Enabled message",
		'PSTR',
		/* [37] */
		"Disabled message",
		'PSTR',
		/* [38] */
		"Checked message",
		'PSTR',
		/* [39] */
		"Other message",
		'PSTR',
		/* [40] */
		"Align",
		'AWRD',
		/* [41] */
		"",
		'KEYE',
		/* [42] */
		"2",
		'KEYB',
		/* [43] */
		"Tip",
		'PNT ',
		/* [44] */
		"Hot rect",
		'RECT',
		/* [45] */
		"Enabled item 'PICT' resID",
		'RSID',
		/* [46] */
		"Disabled item 'PICT' resID",
		'RSID',
		/* [47] */
		"Checked item 'PICT' resID",
		'RSID',
		/* [48] */
		"Other item 'PICT' resID",
		'RSID',
		/* [49] */
		"",
		'KEYE',
		/* [50] */
		"3",
		'KEYB',
		/* [51] */
		"Tip",
		'PNT ',
		/* [52] */
		"Hot rect",
		'RECT',
		/* [53] */
		"Enabled item 'STR#' resID",
		'RSID',
		/* [54] */
		"Which string",
		'DWRD',
		/* [55] */
		"Disabled item 'STR#' resID",
		'RSID',
		/* [56] */
		"Which string",
		'DWRD',
		/* [57] */
		"Checked item 'STR#' resID",
		'RSID',
		/* [58] */
		"Which string",
		'DWRD',
		/* [59] */
		"Other item 'STR#' resID",
		'RSID',
		/* [60] */
		"Which string",
		'DWRD',
		/* [61] */
		"",
		'KEYE',
		/* [62] */
		"6",
		'KEYB',
		/* [63] */
		"Tip",
		'PNT ',
		/* [64] */
		"Hot rect",
		'RECT',
		/* [65] */
		"Enabled item styled 'TEXT' resID",
		'RSID',
		/* [66] */
		"Disabled item styled 'TEXT' resID",
		'RSID',
		/* [67] */
		"Checked item styled 'TEXT' resID",
		'RSID',
		/* [68] */
		"Other item styled 'TEXT' resID",
		'RSID',
		/* [69] */
		"",
		'KEYE',
		/* [70] */
		"7",
		'KEYB',
		/* [71] */
		"Tip",
		'PNT ',
		/* [72] */
		"Hot rect",
		'RECT',
		/* [73] */
		"Enabled item string ('STR ') resID",
		'RSID',
		/* [74] */
		"Disabled item string ('STR ') resID",
		'RSID',
		/* [75] */
		"Checked item string ('STR ') resID",
		'RSID',
		/* [76] */
		"Other item string ('STR ') resID",
		'RSID',
		/* [77] */
		"",
		'KEYE',
		/* [78] */
		"",
		'KEYB',
		/* [79] */
		"Unknown message info",
		'HEXD',
		/* [80] */
		"",
		'KEYE',
		/* [81] */
		"",
		'SKPE',
		/* [82] */
		"Dialog items",
		'LSTC',
		/* [83] */
		"Number of bytes to next record",
		'SKIP',
		/* [84] */
		"Message type",
		'KWRD',
		/* [85] */
		"Use these strings=1",
		'CASE',
		/* [86] */
		"Use 'PICT' resources=2",
		'CASE',
		/* [87] */
		"Use 'STR#' resources=3",
		'CASE',
		/* [88] */
		"Use styled text resources=6",
		'CASE',
		/* [89] */
		"Use 'STR ' resources=7",
		'CASE',
		/* [90] */
		"Skip missing item=256",
		'CASE',
		/* [91] */
		"1",
		'KEYB',
		/* [92] */
		"Tip",
		'PNT ',
		/* [93] */
		"Hot rect",
		'RECT',
		/* [94] */
		"Enabled message",
		'PSTR',
		/* [95] */
		"Disabled message",
		'PSTR',
		/* [96] */
		"Checked message",
		'PSTR',
		/* [97] */
		"Other message",
		'PSTR',
		/* [98] */
		"Align",
		'AWRD',
		/* [99] */
		"",
		'KEYE',
		/* [100] */
		"2",
		'KEYB',
		/* [101] */
		"Tip",
		'PNT ',
		/* [102] */
		"Hot rect",
		'RECT',
		/* [103] */
		"Enabled item 'PICT' resID",
		'RSID',
		/* [104] */
		"Disabled item 'PICT' resID",
		'RSID',
		/* [105] */
		"Checked item 'PICT' resID",
		'RSID',
		/* [106] */
		"Other item 'PICT' resID",
		'RSID',
		/* [107] */
		"",
		'KEYE',
		/* [108] */
		"3",
		'KEYB',
		/* [109] */
		"Tip",
		'PNT ',
		/* [110] */
		"Hot rect",
		'RECT',
		/* [111] */
		"Enabled item 'STR#' resID",
		'RSID',
		/* [112] */
		"Which string",
		'DWRD',
		/* [113] */
		"Disabled item 'STR#' resID",
		'RSID',
		/* [114] */
		"Which string",
		'DWRD',
		/* [115] */
		"Checked item 'STR#' resID",
		'RSID',
		/* [116] */
		"Which string",
		'DWRD',
		/* [117] */
		"Other item 'STR#' resID",
		'RSID',
		/* [118] */
		"Which string",
		'DWRD',
		/* [119] */
		"",
		'KEYE',
		/* [120] */
		"6",
		'KEYB',
		/* [121] */
		"Tip",
		'PNT ',
		/* [122] */
		"Hot rect",
		'RECT',
		/* [123] */
		"Enabled item styled 'TEXT' resID",
		'RSID',
		/* [124] */
		"Disabled item styled 'TEXT' resID",
		'RSID',
		/* [125] */
		"Checked item styled 'TEXT' resID",
		'RSID',
		/* [126] */
		"Other item styled 'TEXT' resID",
		'RSID',
		/* [127] */
		"",
		'KEYE',
		/* [128] */
		"7",
		'KEYB',
		/* [129] */
		"Tip",
		'PNT ',
		/* [130] */
		"Hot rect",
		'RECT',
		/* [131] */
		"Enabled item string ('STR ') resID",
		'RSID',
		/* [132] */
		"Disabled item string ('STR ') resID",
		'RSID',
		/* [133] */
		"Checked item string ('STR ') resID",
		'RSID',
		/* [134] */
		"Other item string ('STR ') resID",
		'RSID',
		/* [135] */
		"",
		'KEYE',
		/* [136] */
		"256",
		'KEYB',
		/* [137] */
		"",
		'KEYE',
		/* [138] */
		"",
		'KEYB',
		/* [139] */
		"Unknown message info",
		'HEXD',
		/* [140] */
		"",
		'KEYE',
		/* [141] */
		"",
		'SKPE',
		/* [142] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1137, "hfdr") {
	{	/* array: 53 elements */
		/* [1] */
		"Balloon help version",
		'DWRD',
		/* [2] */
		"Latest=2",
		'CASE',
		/* [3] */
		"Reserved",
		'LB27',
		/* [4] */
		"For 'hwin's, match string anywhere in ti"
		"tle",
		'LB01',
		/* [5] */
		"Create window, restore bits, and cause u"
		"pdate",
		'LB01',
		/* [6] */
		"Don't create window, restore bits, no up"
		"date",
		'LB01',
		/* [7] */
		"Pretend window port origin is set to (0,"
		"0)",
		'LB01',
		/* [8] */
		"Treat resource IDs as sub-IDs for owned "
		"resources of a D/A, etc.",
		'LB01',
		/* [9] */
		"Balloon 'WDEF' resID",
		'RSID',
		/* [10] */
		"Standard balloons=0",
		'CASE',
		/* [11] */
		"Balloon variation code (tip position)",
		'DWRD',
		/* [12] */
		"Along left side at top=0",
		'CASE',
		/* [13] */
		"Along top at left=1",
		'CASE',
		/* [14] */
		"Along top on right=2",
		'CASE',
		/* [15] */
		"Along right side at top=3",
		'CASE',
		/* [16] */
		"Along right side at bottom=4",
		'CASE',
		/* [17] */
		"Along bottom at right=5",
		'CASE',
		/* [18] */
		"Along bottom at left=6",
		'CASE',
		/* [19] */
		"Along left side at bottom=7",
		'CASE',
		/* [20] */
		"Count:",
		'OCNT',
		/* [21] */
		"Message records",
		'LSTC',
		/* [22] */
		"Number of bytes to next record",
		'SKIP',
		/* [23] */
		"Message type",
		'KWRD',
		/* [24] */
		"Use this string=1",
		'CASE',
		/* [25] */
		"Use 'PICT' resource=2",
		'CASE',
		/* [26] */
		"Use 'STR#' resource=3",
		'CASE',
		/* [27] */
		"Use styled text resources=6",
		'CASE',
		/* [28] */
		"Use 'STR ' resource=7",
		'CASE',
		/* [29] */
		"Skip missing item=256",
		'CASE',
		/* [30] */
		"1",
		'KEYB',
		/* [31] */
		"Help message",
		'PSTR',
		/* [32] */
		"Align",
		'AWRD',
		/* [33] */
		"",
		'KEYE',
		/* [34] */
		"2",
		'KEYB',
		/* [35] */
		"Message 'PICT' resID",
		'RSID',
		/* [36] */
		"",
		'KEYE',
		/* [37] */
		"3",
		'KEYB',
		/* [38] */
		"Message 'STR#' resID",
		'RSID',
		/* [39] */
		"Which string",
		'DWRD',
		/* [40] */
		"",
		'KEYE',
		/* [41] */
		"6",
		'KEYB',
		/* [42] */
		"Message styled 'TEXT' resID",
		'RSID',
		/* [43] */
		"",
		'KEYE',
		/* [44] */
		"7",
		'KEYB',
		/* [45] */
		"Message 'STR ' resID",
		'RSID',
		/* [46] */
		"",
		'KEYE',
		/* [47] */
		"256",
		'KEYB',
		/* [48] */
		"",
		'KEYE',
		/* [49] */
		"",
		'KEYB',
		/* [50] */
		"Unknown message format",
		'HEXD',
		/* [51] */
		"",
		'KEYE',
		/* [52] */
		"",
		'SKPE',
		/* [53] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1138, "hmnu") {
	{	/* array: 179 elements */
		/* [1] */
		"Balloon help version",
		'DWRD',
		/* [2] */
		"Latest=2",
		'CASE',
		/* [3] */
		"Reserved",
		'LB27',
		/* [4] */
		"For 'hwin's, match string anywhere in ti"
		"tle",
		'LB01',
		/* [5] */
		"Create window, restore bits, and cause u"
		"pdate",
		'LB01',
		/* [6] */
		"Don't create window, restore bits, no up"
		"date",
		'LB01',
		/* [7] */
		"Pretend window port origin is set to (0,"
		"0)",
		'LB01',
		/* [8] */
		"Treat resource IDs as owned sub-IDs for "
		"D/As, etc.",
		'LB01',
		/* [9] */
		"Balloon 'WDEF' resID",
		'RSID',
		/* [10] */
		"Standard balloons=0",
		'CASE',
		/* [11] */
		"Balloon variation code (tip position)",
		'DWRD',
		/* [12] */
		"Along left side at top=0",
		'CASE',
		/* [13] */
		"Along top at left=1",
		'CASE',
		/* [14] */
		"Along top on right=2",
		'CASE',
		/* [15] */
		"Along right side at top=3",
		'CASE',
		/* [16] */
		"Along right side at bottom=4",
		'CASE',
		/* [17] */
		"Along bottom at right=5",
		'CASE',
		/* [18] */
		"Along bottom at left=6",
		'CASE',
		/* [19] */
		"Along left side at bottom=7",
		'CASE',
		/* [20] */
		"Count:",
		'OCNT',
		/* [21] */
		"Number of bytes to next record",
		'SKIP',
		/* [22] */
		"Missing message type",
		'KWRD',
		/* [23] */
		"Skip missing item=256",
		'CASE',
		/* [24] */
		"Use these strings=1",
		'CASE',
		/* [25] */
		"Use 'PICT' resources=2",
		'CASE',
		/* [26] */
		"Use 'STR#' resource=3",
		'CASE',
		/* [27] */
		"Use styled text resources=6",
		'CASE',
		/* [28] */
		"Use 'STR ' resources=7",
		'CASE',
		/* [29] */
		"256",
		'KEYB',
		/* [30] */
		"",
		'KEYE',
		/* [31] */
		"1",
		'KEYB',
		/* [32] */
		"Enabled missing message",
		'PSTR',
		/* [33] */
		"Disabled missing message",
		'PSTR',
		/* [34] */
		"Checked missing message",
		'PSTR',
		/* [35] */
		"Other missing message",
		'PSTR',
		/* [36] */
		"Align",
		'AWRD',
		/* [37] */
		"",
		'KEYE',
		/* [38] */
		"2",
		'KEYB',
		/* [39] */
		"Enabled item 'PICT' resID",
		'RSID',
		/* [40] */
		"Disabled item 'PICT' resID",
		'RSID',
		/* [41] */
		"Checked item 'PICT' resID",
		'RSID',
		/* [42] */
		"Other item 'PICT' resID",
		'RSID',
		/* [43] */
		"",
		'KEYE',
		/* [44] */
		"3",
		'KEYB',
		/* [45] */
		"Enabled item 'STR#' resID",
		'RSID',
		/* [46] */
		"Which string",
		'DWRD',
		/* [47] */
		"Disabled item 'STR#' resID",
		'RSID',
		/* [48] */
		"Which string",
		'DWRD',
		/* [49] */
		"Checked item 'STR#' resID",
		'RSID',
		/* [50] */
		"Which string",
		'DWRD',
		/* [51] */
		"Other item 'STR#' resID",
		'RSID',
		/* [52] */
		"Which string",
		'DWRD',
		/* [53] */
		"",
		'KEYE',
		/* [54] */
		"6",
		'KEYB',
		/* [55] */
		"Enabled item styled 'TEXT' resID",
		'RSID',
		/* [56] */
		"Disabled item styled 'TEXT' resID",
		'RSID',
		/* [57] */
		"Checked item styled 'TEXT' resID",
		'RSID',
		/* [58] */
		"Other item styled 'TEXT' resID",
		'RSID',
		/* [59] */
		"",
		'KEYE',
		/* [60] */
		"7",
		'KEYB',
		/* [61] */
		"Enabled item string ('STR ') resID",
		'RSID',
		/* [62] */
		"Disabled item string ('STR ') resID",
		'RSID',
		/* [63] */
		"Checked item string ('STR ') resID",
		'RSID',
		/* [64] */
		"Other item string ('STR ') resID",
		'RSID',
		/* [65] */
		"",
		'KEYE',
		/* [66] */
		"",
		'KEYB',
		/* [67] */
		"Unknown message format",
		'HEXD',
		/* [68] */
		"",
		'KEYE',
		/* [69] */
		"",
		'SKPE',
		/* [70] */
		"Remember that the first message record h"
		"ere is for the menu title",
		'DVDR',
		/* [71] */
		"and subsequent message records are for t"
		"he first and later menu items.",
		'DVDR',
		/* [72] */
		"Item message records",
		'LSTC',
		/* [73] */
		"Number of bytes to next record",
		'SKIP',
		/* [74] */
		"Message record type",
		'KWRD',
		/* [75] */
		"Use these strings=1",
		'CASE',
		/* [76] */
		"Use 'PICT' resources=2",
		'CASE',
		/* [77] */
		"Use 'STR#' resource=3",
		'CASE',
		/* [78] */
		"Use styled text resources=6",
		'CASE',
		/* [79] */
		"Use 'STR ' resources=7",
		'CASE',
		/* [80] */
		"Use named resource type=1024",
		'CASE',
		/* [81] */
		"Skip missing item=256",
		'CASE',
		/* [82] */
		"Compare item=512",
		'CASE',
		/* [83] */
		"1",
		'KEYB',
		/* [84] */
		"Enabled message",
		'PSTR',
		/* [85] */
		"Disabled message",
		'PSTR',
		/* [86] */
		"Checked message",
		'PSTR',
		/* [87] */
		"Other message",
		'PSTR',
		/* [88] */
		"Align",
		'AWRD',
		/* [89] */
		"",
		'KEYE',
		/* [90] */
		"2",
		'KEYB',
		/* [91] */
		"Enabled item 'PICT' resID",
		'RSID',
		/* [92] */
		"Disabled item 'PICT' resID",
		'RSID',
		/* [93] */
		"Checked item 'PICT' resID",
		'RSID',
		/* [94] */
		"Other item 'PICT' resID",
		'RSID',
		/* [95] */
		"",
		'KEYE',
		/* [96] */
		"3",
		'KEYB',
		/* [97] */
		"Enabled item 'STR#' resID",
		'RSID',
		/* [98] */
		"Which string",
		'DWRD',
		/* [99] */
		"Disabled item 'STR#' resID",
		'RSID',
		/* [100] */
		"Which string",
		'DWRD',
		/* [101] */
		"Checked item 'STR#' resID",
		'RSID',
		/* [102] */
		"Which string",
		'DWRD',
		/* [103] */
		"Other item 'STR#' resID",
		'RSID',
		/* [104] */
		"Which string",
		'DWRD',
		/* [105] */
		"",
		'KEYE',
		/* [106] */
		"6",
		'KEYB',
		/* [107] */
		"Enabled item styled 'TEXT' resID",
		'RSID',
		/* [108] */
		"Disabled item styled 'TEXT' resID",
		'RSID',
		/* [109] */
		"Checked item styled 'TEXT' resID",
		'RSID',
		/* [110] */
		"Other item styled 'TEXT' resID",
		'RSID',
		/* [111] */
		"",
		'KEYE',
		/* [112] */
		"7",
		'KEYB',
		/* [113] */
		"Enabled item string ('STR ') resID",
		'RSID',
		/* [114] */
		"Disabled item string ('STR ') resID",
		'RSID',
		/* [115] */
		"Checked item string ('STR ') resID",
		'RSID',
		/* [116] */
		"Other item string ('STR ') resID",
		'RSID',
		/* [117] */
		"",
		'KEYE',
		/* [118] */
		"1024",
		'KEYB',
		/* [119] */
		"For disabled menu items, append '!' to n"
		"ame; for other marks, append mark.",
		'DVDR',
		/* [120] */
		"Type of resource to match name of",
		'TNAM',
		/* [121] */
		"Styled text=TEXT",
		'CASE',
		/* [122] */
		"Picture=PICT",
		'CASE',
		/* [123] */
		"String=STR ",
		'CASE',
		/* [124] */
		"String list=STR#",
		'CASE',
		/* [125] */
		"",
		'KEYE',
		/* [126] */
		"256",
		'KEYB',
		/* [127] */
		"",
		'KEYE',
		/* [128] */
		"512",
		'KEYB',
		/* [129] */
		"Comparison string",
		'ESTR',
		/* [130] */
		"Message type",
		'KWRD',
		/* [131] */
		"Use these strings=1",
		'CASE',
		/* [132] */
		"Use 'PICT' resources=2",
		'CASE',
		/* [133] */
		"Use 'STR#' resource=3",
		'CASE',
		/* [134] */
		"Use styled text resources=6",
		'CASE',
		/* [135] */
		"Use 'STR ' resources=7",
		'CASE',
		/* [136] */
		"Skip missing item=256",
		'CASE',
		/* [137] */
		"1",
		'KEYB',
		/* [138] */
		"Enabled message",
		'PSTR',
		/* [139] */
		"Disabled message",
		'PSTR',
		/* [140] */
		"Checked message",
		'PSTR',
		/* [141] */
		"Other message",
		'PSTR',
		/* [142] */
		"Align",
		'AWRD',
		/* [143] */
		"",
		'KEYE',
		/* [144] */
		"2",
		'KEYB',
		/* [145] */
		"Enabled item 'PICT' resID",
		'RSID',
		/* [146] */
		"Disabled item 'PICT' resID",
		'RSID',
		/* [147] */
		"Checked item 'PICT' resID",
		'RSID',
		/* [148] */
		"Other item 'PICT' resID",
		'RSID',
		/* [149] */
		"",
		'KEYE',
		/* [150] */
		"3",
		'KEYB',
		/* [151] */
		"Enabled item 'STR#' resID",
		'RSID',
		/* [152] */
		"Which string",
		'DWRD',
		/* [153] */
		"Disabled item 'STR#' resID",
		'RSID',
		/* [154] */
		"Which string",
		'DWRD',
		/* [155] */
		"Checked item 'STR#' resID",
		'RSID',
		/* [156] */
		"Which string",
		'DWRD',
		/* [157] */
		"Other item 'STR#' resID",
		'RSID',
		/* [158] */
		"Which string",
		'DWRD',
		/* [159] */
		"",
		'KEYE',
		/* [160] */
		"6",
		'KEYB',
		/* [161] */
		"Enabled item styled 'TEXT' resID",
		'RSID',
		/* [162] */
		"Disabled item styled 'TEXT' resID",
		'RSID',
		/* [163] */
		"Checked item styled 'TEXT' resID",
		'RSID',
		/* [164] */
		"Other item styled 'TEXT' resID",
		'RSID',
		/* [165] */
		"",
		'KEYE',
		/* [166] */
		"7",
		'KEYB',
		/* [167] */
		"Enabled item string ('STR ') resID",
		'RSID',
		/* [168] */
		"Disabled item string ('STR ') resID",
		'RSID',
		/* [169] */
		"Checked item string ('STR ') resID",
		'RSID',
		/* [170] */
		"Other item string ('STR ') resID",
		'RSID',
		/* [171] */
		"",
		'KEYE',
		/* [172] */
		"256",
		'KEYB',
		/* [173] */
		"",
		'KEYE',
		/* [174] */
		"",
		'KEYE',
		/* [175] */
		"",
		'KEYB',
		/* [176] */
		"Unknown message format",
		'HEXD',
		/* [177] */
		"",
		'KEYE',
		/* [178] */
		"",
		'SKPE',
		/* [179] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1139, "hovr") {
	{	/* array: 91 elements */
		/* [1] */
		"Balloon help version",
		'DWRD',
		/* [2] */
		"Latest=2",
		'CASE',
		/* [3] */
		"Reserved",
		'LB27',
		/* [4] */
		"For 'hwin's, match string anywhere in ti"
		"tle",
		'LB01',
		/* [5] */
		"Create window, restore bits, and cause u"
		"pdate",
		'LB01',
		/* [6] */
		"Don't create window, restore bits, no up"
		"date",
		'LB01',
		/* [7] */
		"Pretend window port origin is set to (0,"
		"0)",
		'LB01',
		/* [8] */
		"Treat resource IDs as sub-IDs for owned "
		"resources of a D/A, etc.",
		'LB01',
		/* [9] */
		"Balloon 'WDEF' resID",
		'RSID',
		/* [10] */
		"Standard balloons=0",
		'CASE',
		/* [11] */
		"Balloon variation code (tip position)",
		'DWRD',
		/* [12] */
		"Along left side at top=0",
		'CASE',
		/* [13] */
		"Along top at left=1",
		'CASE',
		/* [14] */
		"Along top on right=2",
		'CASE',
		/* [15] */
		"Along right side at top=3",
		'CASE',
		/* [16] */
		"Along right side at bottom=4",
		'CASE',
		/* [17] */
		"Along bottom at right=5",
		'CASE',
		/* [18] */
		"Along bottom at left=6",
		'CASE',
		/* [19] */
		"Along left side at bottom=7",
		'CASE',
		/* [20] */
		"Count:",
		'OCNT',
		/* [21] */
		"Number of bytes to next record",
		'SKIP',
		/* [22] */
		"Missing message type",
		'KWRD',
		/* [23] */
		"Use this string=1",
		'CASE',
		/* [24] */
		"Use 'PICT' resource=2",
		'CASE',
		/* [25] */
		"Use 'STR#' resource=3",
		'CASE',
		/* [26] */
		"Use styled text resources=6",
		'CASE',
		/* [27] */
		"Use 'STR ' resource=7",
		'CASE',
		/* [28] */
		"Skip missing item=256",
		'CASE',
		/* [29] */
		"1",
		'KEYB',
		/* [30] */
		"Missing message",
		'PSTR',
		/* [31] */
		"Align",
		'AWRD',
		/* [32] */
		"",
		'KEYE',
		/* [33] */
		"2",
		'KEYB',
		/* [34] */
		"Missing message 'PICT' resID",
		'RSID',
		/* [35] */
		"",
		'KEYE',
		/* [36] */
		"3",
		'KEYB',
		/* [37] */
		"Misssing message 'STR#' resID",
		'RSID',
		/* [38] */
		"Which string",
		'DWRD',
		/* [39] */
		"",
		'KEYE',
		/* [40] */
		"6",
		'KEYB',
		/* [41] */
		"Missing message styled 'TEXT' resID",
		'RSID',
		/* [42] */
		"",
		'KEYE',
		/* [43] */
		"7",
		'KEYB',
		/* [44] */
		"Missing message 'STR ' resID",
		'RSID',
		/* [45] */
		"",
		'KEYE',
		/* [46] */
		"256",
		'KEYB',
		/* [47] */
		"",
		'KEYE',
		/* [48] */
		"",
		'KEYB',
		/* [49] */
		"Unknown message format",
		'HEXD',
		/* [50] */
		"",
		'KEYE',
		/* [51] */
		"",
		'SKPE',
		/* [52] */
		"Message 1: Title Bar message",
		'DVDR',
		/* [53] */
		"Message 2: Reserved (should always be Sk"
		"ip Missing Message)",
		'DVDR',
		/* [54] */
		"Message 3: Close Box message",
		'DVDR',
		/* [55] */
		"Message 4: Zoom Box message",
		'DVDR',
		/* [56] */
		"Message 5: Active Application's Inactive"
		" Windows message",
		'DVDR',
		/* [57] */
		"Message 6: Inactive Applications's Inact"
		"ive Windows message",
		'DVDR',
		/* [58] */
		"Message 7: Outside of Modal Dialog or Al"
		"ert Bounds message",
		'DVDR',
		/* [59] */
		"Message records",
		'LSTC',
		/* [60] */
		"Number of bytes to next record",
		'SKIP',
		/* [61] */
		"Message type",
		'KWRD',
		/* [62] */
		"Use this string=1",
		'CASE',
		/* [63] */
		"Use 'PICT' resource=2",
		'CASE',
		/* [64] */
		"Use 'STR#' resource=3",
		'CASE',
		/* [65] */
		"Use styled text resources=6",
		'CASE',
		/* [66] */
		"Use 'STR ' resource=7",
		'CASE',
		/* [67] */
		"Skip missing item=256",
		'CASE',
		/* [68] */
		"1",
		'KEYB',
		/* [69] */
		"Help message",
		'PSTR',
		/* [70] */
		"Align",
		'AWRD',
		/* [71] */
		"",
		'KEYE',
		/* [72] */
		"2",
		'KEYB',
		/* [73] */
		"Message 'PICT' resID",
		'RSID',
		/* [74] */
		"",
		'KEYE',
		/* [75] */
		"3",
		'KEYB',
		/* [76] */
		"Message 'STR#' resID",
		'RSID',
		/* [77] */
		"Which string",
		'DWRD',
		/* [78] */
		"",
		'KEYE',
		/* [79] */
		"6",
		'KEYB',
		/* [80] */
		"Message styled 'TEXT' resID",
		'RSID',
		/* [81] */
		"",
		'KEYE',
		/* [82] */
		"7",
		'KEYB',
		/* [83] */
		"Message 'STR ' resID",
		'RSID',
		/* [84] */
		"",
		'KEYE',
		/* [85] */
		"256",
		'KEYB',
		/* [86] */
		"",
		'KEYE',
		/* [87] */
		"",
		'KEYB',
		/* [88] */
		"Unknown message format",
		'HEXD',
		/* [89] */
		"",
		'KEYE',
		/* [90] */
		"",
		'SKPE',
		/* [91] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1140, "hrct") {
	{	/* array: 114 elements */
		/* [1] */
		"Balloon help version",
		'DWRD',
		/* [2] */
		"Latest=2",
		'CASE',
		/* [3] */
		"Reserved",
		'LB27',
		/* [4] */
		"For 'hwin's, match string anywhere in ti"
		"tle",
		'LB01',
		/* [5] */
		"Create window, restore bits, and cause u"
		"pdate",
		'LB01',
		/* [6] */
		"Don't create window, restore bits, no up"
		"date",
		'LB01',
		/* [7] */
		"Pretend window port origin is set to (0,"
		"0)",
		'LB01',
		/* [8] */
		"Treat resource IDs as sub-IDs for owned "
		"resources of a D/A, etc.",
		'LB01',
		/* [9] */
		"Balloon 'WDEF' resID",
		'RSID',
		/* [10] */
		"Standard balloons=0",
		'CASE',
		/* [11] */
		"Balloon variation code (tip position)",
		'DWRD',
		/* [12] */
		"Along left side at top=0",
		'CASE',
		/* [13] */
		"Along top at left=1",
		'CASE',
		/* [14] */
		"Along top on right=2",
		'CASE',
		/* [15] */
		"Along right side at top=3",
		'CASE',
		/* [16] */
		"Along right side at bottom=4",
		'CASE',
		/* [17] */
		"Along bottom at right=5",
		'CASE',
		/* [18] */
		"Along bottom at left=6",
		'CASE',
		/* [19] */
		"Along left side at bottom=7",
		'CASE',
		/* [20] */
		"Count:",
		'OCNT',
		/* [21] */
		"List of Hot rectangles",
		'LSTC',
		/* [22] */
		"Number of bytes to next record",
		'SKIP',
		/* [23] */
		"Message type",
		'KWRD',
		/* [24] */
		"Use this string=1",
		'CASE',
		/* [25] */
		"Use 'PICT' resource=2",
		'CASE',
		/* [26] */
		"Use 'STR#' resource=3",
		'CASE',
		/* [27] */
		"Use styled text resources=6",
		'CASE',
		/* [28] */
		"Use 'STR ' resource=7",
		'CASE',
		/* [29] */
		"Skip missing item=256",
		'CASE',
		/* [30] */
		"TrackControl string=2049",
		'CASE',
		/* [31] */
		"TrackControl 'PICT' resource=2050",
		'CASE',
		/* [32] */
		"TrackControl 'STR#' resource=2051",
		'CASE',
		/* [33] */
		"TrackControl styled text resources=2054",
		'CASE',
		/* [34] */
		"TrackControl 'STR ' resource=2055",
		'CASE',
		/* [35] */
		"1",
		'KEYB',
		/* [36] */
		"Tip",
		'PNT ',
		/* [37] */
		"Hot rect",
		'RECT',
		/* [38] */
		"Enabled message",
		'ESTR',
		/* [39] */
		"",
		'KEYE',
		/* [40] */
		"2",
		'KEYB',
		/* [41] */
		"Tip",
		'PNT ',
		/* [42] */
		"Hot rect",
		'RECT',
		/* [43] */
		"Message 'PICT' resID",
		'RSID',
		/* [44] */
		"",
		'KEYE',
		/* [45] */
		"3",
		'KEYB',
		/* [46] */
		"Tip",
		'PNT ',
		/* [47] */
		"Hot rect",
		'RECT',
		/* [48] */
		"Message 'STR#' resID",
		'RSID',
		/* [49] */
		"Which string",
		'DWRD',
		/* [50] */
		"",
		'KEYE',
		/* [51] */
		"6",
		'KEYB',
		/* [52] */
		"Tip",
		'PNT ',
		/* [53] */
		"Hot rect",
		'RECT',
		/* [54] */
		"Message styled 'TEXT' resID",
		'RSID',
		/* [55] */
		"",
		'KEYE',
		/* [56] */
		"7",
		'KEYB',
		/* [57] */
		"Tip",
		'PNT ',
		/* [58] */
		"Hot rect",
		'RECT',
		/* [59] */
		"Message string ('STR ') resID",
		'RSID',
		/* [60] */
		"",
		'KEYE',
		/* [61] */
		"256",
		'KEYB',
		/* [62] */
		"Tip (ignored)",
		'PNT ',
		/* [63] */
		"Hot rect (ignored)",
		'RECT',
		/* [64] */
		"",
		'KEYE',
		/* [65] */
		"2049",
		'KEYB',
		/* [66] */
		"Tip",
		'PNT ',
		/* [67] */
		"Hot rect",
		'RECT',
		/* [68] */
		"Enabled control message",
		'PSTR',
		/* [69] */
		"Disabled control message",
		'PSTR',
		/* [70] */
		"Checked control message",
		'PSTR',
		/* [71] */
		"Other control message",
		'PSTR',
		/* [72] */
		"Align",
		'AWRD',
		/* [73] */
		"",
		'KEYE',
		/* [74] */
		"2050",
		'KEYB',
		/* [75] */
		"Tip",
		'PNT ',
		/* [76] */
		"Hot rect",
		'RECT',
		/* [77] */
		"Enabled control 'PICT' resID",
		'RSID',
		/* [78] */
		"Disabled control 'PICT' resID",
		'RSID',
		/* [79] */
		"Checked control 'PICT' resID",
		'RSID',
		/* [80] */
		"Other control 'PICT' resID",
		'RSID',
		/* [81] */
		"",
		'KEYE',
		/* [82] */
		"2051",
		'KEYB',
		/* [83] */
		"Tip",
		'PNT ',
		/* [84] */
		"Hot rect",
		'RECT',
		/* [85] */
		"Enabled control 'STR#' resID",
		'RSID',
		/* [86] */
		"Which string",
		'DWRD',
		/* [87] */
		"Disabled control 'STR#' resID",
		'RSID',
		/* [88] */
		"Which string",
		'DWRD',
		/* [89] */
		"Checked control 'STR#' resID",
		'RSID',
		/* [90] */
		"Which string",
		'DWRD',
		/* [91] */
		"Other control 'STR#' resID",
		'RSID',
		/* [92] */
		"Which string",
		'DWRD',
		/* [93] */
		"",
		'KEYE',
		/* [94] */
		"2054",
		'KEYB',
		/* [95] */
		"Tip",
		'PNT ',
		/* [96] */
		"Hot rect",
		'RECT',
		/* [97] */
		"Enabled control styled 'TEXT' resID",
		'RSID',
		/* [98] */
		"Disabled control styled 'TEXT' resID",
		'RSID',
		/* [99] */
		"Checked control styled 'TEXT' resID",
		'RSID',
		/* [100] */
		"Other control styled 'TEXT' resID",
		'RSID',
		/* [101] */
		"",
		'KEYE',
		/* [102] */
		"2055",
		'KEYB',
		/* [103] */
		"Tip",
		'PNT ',
		/* [104] */
		"Hot rect",
		'RECT',
		/* [105] */
		"Enabled control 'STR ' resID",
		'RSID',
		/* [106] */
		"Disabled control 'STR ' resID",
		'RSID',
		/* [107] */
		"Checked control 'STR ' resID",
		'RSID',
		/* [108] */
		"Other control string 'STR ' resID",
		'RSID',
		/* [109] */
		"",
		'KEYE',
		/* [110] */
		"",
		'KEYB',
		/* [111] */
		"Unknown message format",
		'HEXD',
		/* [112] */
		"",
		'KEYE',
		/* [113] */
		"",
		'SKPE',
		/* [114] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1141, "HTMB") {
	{	/* array: 8 elements */
		/* [1] */
		"Button kind",
		'DWRD',
		/* [2] */
		"Plain Button=0",
		'CASE',
		/* [3] */
		"Popup Button=1",
		'CASE',
		/* [4] */
		"Draggable Button=2",
		'CASE',
		/* [5] */
		"Has secondary popup",
		'BOOL',
		/* [6] */
		"Space above",
		'BOOL',
		/* [7] */
		"Has alternate",
		'BOOL',
		/* [8] */
		"filler",
		'F078'
	}
};

resource 'TMPL' (1142, "hwin") {
	{	/* array: 17 elements */
		/* [1] */
		"Balloon help version",
		'DWRD',
		/* [2] */
		"Latest=2",
		'CASE',
		/* [3] */
		"Reserved",
		'LB27',
		/* [4] */
		"Match In Title Mask",
		'LB01',
		/* [5] */
		"Save Bits Window Mask",
		'LB01',
		/* [6] */
		"Save Bits No Window Mask",
		'LB01',
		/* [7] */
		"Absolute Coords Mask",
		'LB01',
		/* [8] */
		"Use Sub ID Mask",
		'LB01',
		/* [9] */
		"Count:",
		'OCNT',
		/* [10] */
		"List of Static windows",
		'LSTC',
		/* [11] */
		"Resource ID of following help type",
		'RSID',
		/* [12] */
		"Help resource type",
		'TNAM',
		/* [13] */
		"hrct=hrct",
		'CASE',
		/* [14] */
		"hdlg=hdlg",
		'CASE',
		/* [15] */
		"Comparison string length",
		'DWRD',
		/* [16] */
		"WWindow title",
		'ESTR',
		/* [17] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1143, "icl4") {
	{	/* array: 2 elements */
		/* [1] */
		"4-bit large icon no mask",
		'DVDR',
		/* [2] */
		"Image data",
		'H200'
	}
};

resource 'TMPL' (1144, "icl8") {
	{	/* array: 2 elements */
		/* [1] */
		"8-bit large icon no mask",
		'DVDR',
		/* [2] */
		"Image data",
		'H400'
	}
};

resource 'TMPL' (1145, "ICLB") {
	{	/* array: 26 elements */
		/* [1] */
		"\"MacZoop\" resource format",
		'DVDR',
		/* [2] */
		"Hilite Opt (6):",
		'DWRD',
		/* [3] */
		"Reserved",
		'BB02',
		/* [4] */
		"Highlight entire cell except icon",
		'BBIT',
		/* [5] */
		"Invert entire cell except icon",
		'BBIT',
		/* [6] */
		"Invert title text",
		'BBIT',
		/* [7] */
		"Darken icon",
		'BBIT',
		/* [8] */
		"Frame w/ bold box",
		'BBIT',
		/* [9] */
		"align",
		'AWRD',
		/* [10] */
		"H Offset",
		'DWRD',
		/* [11] */
		"V Offset",
		'DWRD',
		/* [12] */
		"Titles ('STR#' ID)",
		'DWRD',
		/* [13] */
		"Titles vis",
		'BBIT',
		/* [14] */
		"Use res name",
		'BBIT',
		/* [15] */
		"Small icons",
		'BBIT',
		/* [16] */
		"Reserved",
		'BB05',
		/* [17] */
		"pad",
		'AWRD',
		/* [18] */
		"Count:",
		'OCNT',
		/* [19] */
		"Icons list",
		'LSTC',
		/* [20] */
		"Icon ID",
		'DWRD',
		/* [21] */
		"Type",
		'DWRD',
		/* [22] */
		"ICON=0",
		'CASE',
		/* [23] */
		"cicn=1",
		'CASE',
		/* [24] */
		"ICN#=2",
		'CASE',
		/* [25] */
		"Title index",
		'DWRD',
		/* [26] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1146, "icm#") {
	{	/* array: 3 elements */
		/* [1] */
		"Mini icon with mask",
		'DVDR',
		/* [2] */
		"Image data",
		'H018',
		/* [3] */
		"Mask data",
		'H018'
	}
};

resource 'TMPL' (1147, "icm4") {
	{	/* array: 2 elements */
		/* [1] */
		"4-bit mini icon no mask",
		'DVDR',
		/* [2] */
		"Image data",
		'H060'
	}
};

resource 'TMPL' (1148, "icm8") {
	{	/* array: 2 elements */
		/* [1] */
		"8-bit mini icon no mask",
		'DVDR',
		/* [2] */
		"Image data",
		'H0C0'
	}
};

resource 'TMPL' (1149, "icmt") {
	{	/* array: 4 elements */
		/* [1] */
		"Version release date",
		'DATE',
		/* [2] */
		"Version Number",
		'ULNG',
		/* [3] */
		"'ICON' resource ID",
		'RSID',
		/* [4] */
		"Comment text",
		'ESTR'
	}
};

resource 'TMPL' (1150, "ICN#") {
	{	/* array: 3 elements */
		/* [1] */
		"Icons list",
		'LSTB',
		/* [2] */
		"Icon data",
		'H080',
		/* [3] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1151, "ICON") {
	{	/* array: 2 elements */
		/* [1] */
		"Black and White Icon",
		'DVDR',
		/* [2] */
		"Image data",
		'H080'
	}
};

resource 'TMPL' (1152, "ICOX") {
	{	/* array: 9 elements */
		/* [1] */
		"",
		'LSTB',
		/* [2] */
		"Name of resource",
		'TNAM',
		/* [3] */
		"Bits per pixel",
		'DWRD',
		/* [4] */
		"Length of resource",
		'DWRD',
		/* [5] */
		"Maximum width",
		'DWRD',
		/* [6] */
		"Maximum height",
		'DWRD',
		/* [7] */
		"Width",
		'DWRD',
		/* [8] */
		"Height",
		'DWRD',
		/* [9] */
		"",
		'LSTE'
	}
};

resource 'TMPL' (1153, "ics#") {
	{	/* array: 3 elements */
		/* [1] */
		"Small icon with mask",
		'DVDR',
		/* [2] */
		"Image data",
		'H020',
		/* [3] */
		"Mask data",
		'H020'
	}
};

resource 'TMPL' (1154, "ics4") {
	{	/* array: 2 elements */
		/* [1] */
		"4-bit small icon no mask",
		'DVDR',
		/* [2] */
		"Image data",
		'H080'
	}
};

resource 'TMPL' (1155, "ics8") {
	{	/* array: 2 elements */
		/* [1] */
		"8-bit small icon no mask",
		'DVDR',
		/* [2] */
		"Image data",
		'H100'
	}
};

resource 'TMPL' (1156, "ICx6") {
	{	/* array: 28 elements */
		/* [1] */
		"",
		'LCNT',
		/* [2] */
		"",
		'LSTC',
		/* [3] */
		"Filler",
		'FBYT',
		/* [4] */
		"Unused",
		'BB05',
		/* [5] */
		"Match MIME type",
		'BBIT',
		/* [6] */
		"Match type/creator",
		'BBIT',
		/* [7] */
		"Match filename extension",
		'BBIT',
		/* [8] */
		"Total length",
		'DWRD',
		/* [9] */
		"Fixed length",
		'DWRD',
		/* [10] */
		"Version",
		'DWRD',
		/* [11] */
		"File type",
		'TNAM',
		/* [12] */
		"File creator",
		'TNAM',
		/* [13] */
		"Post creator",
		'TNAM',
		/* [14] */
		"Filler",
		'FWRD',
		/* [15] */
		"Filler",
		'FBYT',
		/* [16] */
		"Unused",
		'BB02',
		/* [17] */
		"Ignore for outgoing",
		'BBIT',
		/* [18] */
		"Ignore for incoming",
		'BBIT',
		/* [19] */
		"Post process",
		'BBIT',
		/* [20] */
		"Has data fork",
		'BBIT',
		/* [21] */
		"Has resource fork",
		'BBIT',
		/* [22] */
		"Binary",
		'BBIT',
		/* [23] */
		"Extension",
		'PSTR',
		/* [24] */
		"Creator app name",
		'PSTR',
		/* [25] */
		"Post app name",
		'PSTR',
		/* [26] */
		"MIME type",
		'PSTR',
		/* [27] */
		"Entry name",
		'PSTR',
		/* [28] */
		"",
		'LSTE'
	}
};

resource 'TMPL' (1157, "inaa") {
	{	/* array: 50 elements */
		/* [1] */
		"Action Atom format version",
		'KWRD',
		/* [2] */
		"Installer 4.0 or later=2",
		'CASE',
		/* [3] */
		"Installer 3.3 or later=1",
		'CASE',
		/* [4] */
		"Original=0",
		'CASE',
		/* [5] */
		"2",
		'KEYB',
		/* [6] */
		"Reserved",
		'WB12',
		/* [7] */
		"Busy cursor during action",
		'WBIT',
		/* [8] */
		"Continue it=Off",
		'CASE',
		/* [9] */
		"Suspend it=On",
		'CASE',
		/* [10] */
		"Call this procedure before all installs",
		'WBIT',
		/* [11] */
		"Call this procedure when doing a remove",
		'WBIT',
		/* [12] */
		"Call this procedure when doing an instal"
		"l",
		'WBIT',
		/* [13] */
		"Executable (C style) resource type",
		'TNAM',
		/* [14] */
		"Installer function=infn",
		'CASE',
		/* [15] */
		"Procedure=proc",
		'CASE',
		/* [16] */
		"Standard code=CODE",
		'CASE',
		/* [17] */
		"Executable resource ID",
		'RSID',
		/* [18] */
		"RefCon passed to executable resource",
		'DLNG',
		/* [19] */
		"Requested memory (in bytes)",
		'ULNG',
		/* [20] */
		"Action Atom description",
		'ESTR',
		/* [21] */
		"",
		'KEYE',
		/* [22] */
		"1",
		'KEYB',
		/* [23] */
		"Reserved",
		'WB12',
		/* [24] */
		"Busy cursor during action",
		'WBIT',
		/* [25] */
		"Continue it=Off",
		'CASE',
		/* [26] */
		"Suspend it=On",
		'CASE',
		/* [27] */
		"Call this procedure before all installs",
		'WBIT',
		/* [28] */
		"Call this procedure when doing a remove",
		'WBIT',
		/* [29] */
		"Call this procedure when doing an instal"
		"l",
		'WBIT',
		/* [30] */
		"Executable (C style) resource type",
		'TNAM',
		/* [31] */
		"Installer function=infn",
		'CASE',
		/* [32] */
		"Procedure=proc",
		'CASE',
		/* [33] */
		"Standard code=CODE",
		'CASE',
		/* [34] */
		"Executable resource ID",
		'RSID',
		/* [35] */
		"RefCon passed to executable resource",
		'DLNG',
		/* [36] */
		"Action Atom description",
		'ESTR',
		/* [37] */
		"",
		'KEYE',
		/* [38] */
		"0",
		'KEYB',
		/* [39] */
		"Reserved",
		'WB13',
		/* [40] */
		"Call this procedure before all installs",
		'WBIT',
		/* [41] */
		"Call this procedure when doing a remove",
		'WBIT',
		/* [42] */
		"Call this procedure when doing an instal"
		"l",
		'WBIT',
		/* [43] */
		"Executable resource type",
		'TNAM',
		/* [44] */
		"Installer function=infn",
		'CASE',
		/* [45] */
		"Procedure=proc",
		'CASE',
		/* [46] */
		"Standard code=CODE",
		'CASE',
		/* [47] */
		"Execuatable resource ID",
		'RSID',
		/* [48] */
		"RefCon passed to executable resource",
		'DLNG',
		/* [49] */
		"Action Atom description",
		'ESTR',
		/* [50] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1158, "inah") {
	{	/* array: 9 elements */
		/* [1] */
		"Action Handler format version",
		'KWRD',
		/* [2] */
		"Format0=0",
		'CASE',
		/* [3] */
		"0",
		'KEYB',
		/* [4] */
		"Reserved",
		'WB16',
		/* [5] */
		"Type of handler code resource",
		'TNAM',
		/* [6] */
		"Action handler code resource ID",
		'RSID',
		/* [7] */
		"Requested memory (in bytes)",
		'ULNG',
		/* [8] */
		"Optional summary string",
		'ESTR',
		/* [9] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1159, "inat") {
	{	/* array: 39 elements */
		/* [1] */
		"Audit Trail format version",
		'KWRD',
		/* [2] */
		"Format0=0",
		'CASE',
		/* [3] */
		"0",
		'KEYB',
		/* [4] */
		"Target File Spec ('intf') resource ID  ",
		'RSID',
		/* [5] */
		"Selector",
		'TNAM',
		/* [6] */
		"Mac System Software=mssw",
		'CASE',
		/* [7] */
		"AppleShare=afps",
		'CASE',
		/* [8] */
		"FileShare=fshr",
		'CASE',
		/* [9] */
		"EtherTalk=etlk",
		'CASE',
		/* [10] */
		"Ether3Com=e3cm",
		'CASE',
		/* [11] */
		"EtherSmart=esmt",
		'CASE',
		/* [12] */
		"EtherLC=etlc",
		'CASE',
		/* [13] */
		"EtherSonic=etso",
		'CASE',
		/* [14] */
		"TokenTalk=ttlk",
		'CASE',
		/* [15] */
		"Mac Plus=plus",
		'CASE',
		/* [16] */
		"Mac SE=se  ",
		'CASE',
		/* [17] */
		"Mac SE/30=se30",
		'CASE',
		/* [18] */
		"Mac Portable=port",
		'CASE',
		/* [19] */
		"Mac II=ii  ",
		'CASE',
		/* [20] */
		"Mac IIx=iix ",
		'CASE',
		/* [21] */
		"Mac IIcx=iicx",
		'CASE',
		/* [22] */
		"Mac IIci=iici",
		'CASE',
		/* [23] */
		"Mac IIfx=iifx",
		'CASE',
		/* [24] */
		"Mac Classic=clas",
		'CASE',
		/* [25] */
		"Mac Portable=port",
		'CASE',
		/* [26] */
		"Mac PB 100=ashi",
		'CASE',
		/* [27] */
		"Mac Classic II=aplo",
		'CASE',
		/* [28] */
		"Mac LC=lc  ",
		'CASE',
		/* [29] */
		"Mac IIsi=iisi",
		'CASE',
		/* [30] */
		"Mac PB 140=timl",
		'CASE',
		/* [31] */
		"Mac PB 170=tim ",
		'CASE',
		/* [32] */
		"Mac Q700=spke",
		'CASE',
		/* [33] */
		"Mac Q900=eclp",
		'CASE',
		/* [34] */
		"Mac Q950=ecl3",
		'CASE',
		/* [35] */
		"Value",
		'TNAM',
		/* [36] */
		"Not installed=$00000000",
		'CASE',
		/* [37] */
		"Minimal installation=$00000001",
		'CASE',
		/* [38] */
		"Full installation=$00000002",
		'CASE',
		/* [39] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1160, "inbb") {
	{	/* array: 120 elements */
		/* [1] */
		"Boot Block format version",
		'KWRD',
		/* [2] */
		"Standard=0",
		'CASE',
		/* [3] */
		"0",
		'KEYB',
		/* [4] */
		"Reserved",
		'WB07',
		/* [5] */
		"Save system name (off=replace)",
		'WBIT',
		/* [6] */
		"Save shell name (off=replace)",
		'WBIT',
		/* [7] */
		"Save debug 1 name (off=replace)",
		'WBIT',
		/* [8] */
		"Save debug 2 name (off=replace)",
		'WBIT',
		/* [9] */
		"Save screen name (off=replace)",
		'WBIT',
		/* [10] */
		"Save \"hello\" name (off=replace)",
		'WBIT',
		/* [11] */
		"Save scrap name (off=replace)",
		'WBIT',
		/* [12] */
		"Max FCB count (off=replace)",
		'WBIT',
		/* [13] */
		"Max event count (off=replace)",
		'WBIT',
		/* [14] */
		"Boot Block type",
		'KWRD',
		/* [15] */
		"Update=-1",
		'CASE',
		/* [16] */
		"ID=1",
		'CASE',
		/* [17] */
		"Entry=2",
		'CASE',
		/* [18] */
		"Version=3",
		'CASE',
		/* [19] */
		"Page flags=4",
		'CASE',
		/* [20] */
		"System name=5",
		'CASE',
		/* [21] */
		"Shell name=6",
		'CASE',
		/* [22] */
		"Debug 1 name=7",
		'CASE',
		/* [23] */
		"Debug 2 name=8",
		'CASE',
		/* [24] */
		"Screen name=9",
		'CASE',
		/* [25] */
		"Hello name=10",
		'CASE',
		/* [26] */
		"Scrap name=11",
		'CASE',
		/* [27] */
		"Count FCBs=12",
		'CASE',
		/* [28] */
		"Count events=13",
		'CASE',
		/* [29] */
		"128K System heap=14",
		'CASE',
		/* [30] */
		"256K System heap=15",
		'CASE',
		/* [31] */
		"512K System heap=16",
		'CASE',
		/* [32] */
		"System heap extra (obsolete)=18",
		'CASE',
		/* [33] */
		"System heap fract (obsolete)=19",
		'CASE',
		/* [34] */
		"-1",
		'KEYB',
		/* [35] */
		"'boot' resource File Spec ('infs') resou"
		"rce ID",
		'RSID',
		/* [36] */
		"Reserved",
		'WB07',
		/* [37] */
		"System name",
		'WBIT',
		/* [38] */
		"Replace=off",
		'CASE',
		/* [39] */
		"Keep=on",
		'CASE',
		/* [40] */
		"Shell name",
		'WBIT',
		/* [41] */
		"Replace=off",
		'CASE',
		/* [42] */
		"Keep=on",
		'CASE',
		/* [43] */
		"Debug 1 name",
		'WBIT',
		/* [44] */
		"Replace=off",
		'CASE',
		/* [45] */
		"Keep=on",
		'CASE',
		/* [46] */
		"Debug 2 name",
		'WBIT',
		/* [47] */
		"Replace=off",
		'CASE',
		/* [48] */
		"Keep=on",
		'CASE',
		/* [49] */
		"Screen name",
		'WBIT',
		/* [50] */
		"Replace=off",
		'CASE',
		/* [51] */
		"Keep=on",
		'CASE',
		/* [52] */
		"\"Hello\" name",
		'WBIT',
		/* [53] */
		"Replace=off",
		'CASE',
		/* [54] */
		"Keep=on",
		'CASE',
		/* [55] */
		"Scrap name",
		'WBIT',
		/* [56] */
		"Replace=off",
		'CASE',
		/* [57] */
		"Keep=on",
		'CASE',
		/* [58] */
		"Max File Control Block (FCB) count",
		'WBIT',
		/* [59] */
		"Replace=off",
		'CASE',
		/* [60] */
		"Keep=on",
		'CASE',
		/* [61] */
		"Max event count",
		'WBIT',
		/* [62] */
		"Replace=off",
		'CASE',
		/* [63] */
		"Keep=on",
		'CASE',
		/* [64] */
		"",
		'KEYE',
		/* [65] */
		"1",
		'KEYB',
		/* [66] */
		"ID",
		'DWRD',
		/* [67] */
		"",
		'KEYE',
		/* [68] */
		"2",
		'KEYB',
		/* [69] */
		"Entry",
		'DLNG',
		/* [70] */
		"",
		'KEYE',
		/* [71] */
		"3",
		'KEYB',
		/* [72] */
		"Version",
		'DWRD',
		/* [73] */
		"",
		'KEYE',
		/* [74] */
		"4",
		'KEYB',
		/* [75] */
		"Page flags",
		'WB16',
		/* [76] */
		"",
		'KEYE',
		/* [77] */
		"5",
		'KEYB',
		/* [78] */
		"System name",
		'ESTR',
		/* [79] */
		"",
		'KEYE',
		/* [80] */
		"6",
		'KEYB',
		/* [81] */
		"Shell name",
		'ESTR',
		/* [82] */
		"",
		'KEYE',
		/* [83] */
		"7",
		'KEYB',
		/* [84] */
		"Debug 1 name",
		'ESTR',
		/* [85] */
		"",
		'KEYE',
		/* [86] */
		"8",
		'KEYB',
		/* [87] */
		"Debug 2 name",
		'ESTR',
		/* [88] */
		"",
		'KEYE',
		/* [89] */
		"9",
		'KEYB',
		/* [90] */
		"Screen name",
		'ESTR',
		/* [91] */
		"",
		'KEYE',
		/* [92] */
		"10",
		'KEYB',
		/* [93] */
		"\"Hello\" name",
		'ESTR',
		/* [94] */
		"",
		'KEYE',
		/* [95] */
		"11",
		'KEYB',
		/* [96] */
		"Scrap name",
		'ESTR',
		/* [97] */
		"",
		'KEYE',
		/* [98] */
		"12",
		'KEYB',
		/* [99] */
		"Maximum number of files (FCBs)",
		'DWRD',
		/* [100] */
		"",
		'KEYE',
		/* [101] */
		"13",
		'KEYB',
		/* [102] */
		"Maximum number of events",
		'DWRD',
		/* [103] */
		"",
		'KEYE',
		/* [104] */
		"14",
		'KEYB',
		/* [105] */
		"128K System heap size",
		'DLNG',
		/* [106] */
		"",
		'KEYE',
		/* [107] */
		"15",
		'KEYB',
		/* [108] */
		"256K System heap size",
		'DLNG',
		/* [109] */
		"",
		'KEYE',
		/* [110] */
		"16",
		'KEYB',
		/* [111] */
		"512K System heap size",
		'DLNG',
		/* [112] */
		"",
		'KEYE',
		/* [113] */
		"18",
		'KEYB',
		/* [114] */
		"System heap extra",
		'DLNG',
		/* [115] */
		"",
		'KEYE',
		/* [116] */
		"19",
		'KEYB',
		/* [117] */
		"System heap fract",
		'DLNG',
		/* [118] */
		"",
		'KEYE',
		/* [119] */
		"Boot block atom description",
		'ESTR',
		/* [120] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1161, "incd") {
	{	/* array: 1 elements */
		/* [1] */
		"Creation date & time",
		'DATE'
	}
};

resource 'TMPL' (1162, "indm") {
	{	/* array: 37 elements */
		/* [1] */
		"Format version",
		'HWRD',
		/* [2] */
		"Flags (unused)",
		'HWRD',
		/* [3] */
		"Count:",
		'OCNT',
		/* [4] */
		"Machines",
		'LSTC',
		/* [5] */
		"Machine Type",
		'DWRD',
		/* [6] */
		"*****",
		'LSTE',
		/* [7] */
		"Count:",
		'OCNT',
		/* [8] */
		"Processors",
		'LSTC',
		/* [9] */
		"Processor type",
		'DWRD',
		/* [10] */
		"*****",
		'LSTE',
		/* [11] */
		"Count:",
		'OCNT',
		/* [12] */
		"List of MMUs",
		'LSTC',
		/* [13] */
		"MMU type",
		'DWRD',
		/* [14] */
		"*****",
		'LSTE',
		/* [15] */
		"Count:",
		'OCNT',
		/* [16] */
		"Keyboards",
		'LSTC',
		/* [17] */
		"Keyboard type",
		'DWRD',
		/* [18] */
		"*****",
		'LSTE',
		/* [19] */
		"Requires FPU",
		'DBYT',
		/* [20] */
		"Requires Color QD",
		'DBYT',
		/* [21] */
		"Minimal memory (MB)",
		'DWRD',
		/* [22] */
		"Count:",
		'OCNT',
		/* [23] */
		"System resources",
		'LSTC',
		/* [24] */
		"Resource type",
		'TNAM',
		/* [25] */
		"Resource ID",
		'DWRD',
		/* [26] */
		"*****",
		'LSTE',
		/* [27] */
		"System Revision",
		'HLNG',
		/* [28] */
		"Country code",
		'DWRD',
		/* [29] */
		"AppleTalk driver version",
		'DWRD',
		/* [30] */
		"Min. target size (in K)",
		'DLNG',
		/* [31] */
		"Max. target size (in K)",
		'DLNG',
		/* [32] */
		"User function ID",
		'DWRD',
		/* [33] */
		"User description",
		'ESTR',
		/* [34] */
		"Count:",
		'OCNT',
		/* [35] */
		"Packages",
		'LSTC',
		/* [36] */
		"Package ID",
		'DWRD',
		/* [37] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1163, "indo") {
	{	/* array: 19 elements */
		/* [1] */
		"Disk Order resource version",
		'KWRD',
		/* [2] */
		"Latest=1",
		'CASE',
		/* [3] */
		"Original=0",
		'CASE',
		/* [4] */
		"1",
		'KEYB',
		/* [5] */
		"Count:",
		'OCNT',
		/* [6] */
		"List of Source diskettes",
		'LSTC',
		/* [7] */
		"Disk type",
		'DWRD',
		/* [8] */
		"Expect floppy=0",
		'CASE',
		/* [9] */
		"Expect CD-ROM=1",
		'CASE',
		/* [10] */
		"Expect folders on volume=2",
		'CASE',
		/* [11] */
		"Disk or volume name",
		'ESTR',
		/* [12] */
		"*****",
		'LSTE',
		/* [13] */
		"",
		'KEYE',
		/* [14] */
		"0",
		'KEYB',
		/* [15] */
		"Count:",
		'OCNT',
		/* [16] */
		"Diskette or volume names",
		'LSTC',
		/* [17] */
		"Name",
		'ESTR',
		/* [18] */
		"*****",
		'LSTE',
		/* [19] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1164, "inex") {
	{	/* array: 21 elements */
		/* [1] */
		"Atom Extender format version",
		'KWRD',
		/* [2] */
		"Standard=0",
		'CASE',
		/* [3] */
		"0",
		'KEYB',
		/* [4] */
		"Send init message",
		'WBIT',
		/* [5] */
		"Send before message",
		'WBIT',
		/* [6] */
		"Send after message",
		'WBIT',
		/* [7] */
		"Send success message",
		'WBIT',
		/* [8] */
		"Send cancel message",
		'WBIT',
		/* [9] */
		"Busy cursor",
		'WBIT',
		/* [10] */
		"Continue=Off",
		'CASE',
		/* [11] */
		"Suspend=On",
		'CASE',
		/* [12] */
		"Reserved",
		'WB10',
		/* [13] */
		"Executable resource type",
		'TNAM',
		/* [14] */
		"Installer function=infn",
		'CASE',
		/* [15] */
		"Procedure=proc",
		'CASE',
		/* [16] */
		"Standard code=CODE",
		'CASE',
		/* [17] */
		"Executable resource ID",
		'RSID',
		/* [18] */
		"Ref const passed to executable",
		'DLNG',
		/* [19] */
		"Requested memory (in bytes)",
		'ULNG',
		/* [20] */
		"Atom extender description",
		'ESTR',
		/* [21] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1165, "infa") {
	{	/* array: 84 elements */
		/* [1] */
		"File Atom format version",
		'KWRD',
		/* [2] */
		"Latest=1",
		'CASE',
		/* [3] */
		"Original=0",
		'CASE',
		/* [4] */
		"1",
		'KEYB',
		/* [5] */
		"Delete file or resource if \"Remove\" clic"
		"ked",
		'WBIT',
		/* [6] */
		"Delete target before copy",
		'WBIT',
		/* [7] */
		"Copy file or resource to destination",
		'WBIT',
		/* [8] */
		"Reserved",
		'WB03',
		/* [9] */
		"Do it even if file is locked",
		'WBIT',
		/* [10] */
		"Set target file to be locked",
		'WBIT',
		/* [11] */
		"Determine if target is newer",
		'WBIT',
		/* [12] */
		"Use source creation date=off",
		'CASE',
		/* [13] */
		"Use version procedure=on",
		'CASE',
		/* [14] */
		"Ignore atom if source file doesn't exist",
		'WBIT',
		/* [15] */
		"Where is resource fork",
		'WBIT',
		/* [16] */
		"In resource fork=off",
		'CASE',
		/* [17] */
		"In data fork=on",
		'CASE',
		/* [18] */
		"Leave alone if newer version exists",
		'WBIT',
		/* [19] */
		"Keep target file if it already exists",
		'WBIT',
		/* [20] */
		"Only update if target exists",
		'WBIT',
		/* [21] */
		"Apply operation to resource fork",
		'WBIT',
		/* [22] */
		"Apply operation to data fork",
		'WBIT',
		/* [23] */
		"File size (in bytes)",
		'ULNG',
		/* [24] */
		"Finder file attribute flags",
		'DVDR',
		/* [25] */
		"File is an alias",
		'WBIT',
		/* [26] */
		"File is invisible",
		'WBIT',
		/* [27] */
		"File has a bundle ('BNDL')",
		'WBIT',
		/* [28] */
		"File name is locked",
		'WBIT',
		/* [29] */
		"File is a stationery pad",
		'WBIT',
		/* [30] */
		"File has a custom icon",
		'WBIT',
		/* [31] */
		"Reserved",
		'WBIT',
		/* [32] */
		"Bundle has been recorded (inited)",
		'WBIT',
		/* [33] */
		"File has no 'INIT's",
		'WBIT',
		/* [34] */
		"File is shareable",
		'WBIT',
		/* [35] */
		"File requires switch launch",
		'WBIT',
		/* [36] */
		"Reserved",
		'WBIT',
		/* [37] */
		"Label",
		'WB03',
		/* [38] */
		"None=0",
		'CASE',
		/* [39] */
		"Essential=7",
		'CASE',
		/* [40] */
		"Hot=6",
		'CASE',
		/* [41] */
		"In progress=5",
		'CASE',
		/* [42] */
		"Cool=4",
		'CASE',
		/* [43] */
		"Personal=3",
		'CASE',
		/* [44] */
		"Project 1=2",
		'CASE',
		/* [45] */
		"Project 2=1",
		'CASE',
		/* [46] */
		"File is on desktop",
		'WBIT',
		/* [47] */
		"Target File Spec ('intf') resource ID  ",
		'RSID',
		/* [48] */
		"Count:",
		'OCNT',
		/* [49] */
		"Source parts",
		'LSTC',
		/* [50] */
		"Source part file spec ('infs') resource "
		"ID",
		'RSID',
		/* [51] */
		"Delete target only=0",
		'CASE',
		/* [52] */
		"Target part data fork size",
		'ULNG',
		/* [53] */
		"Target part resource fork size",
		'ULNG',
		/* [54] */
		"*****",
		'LSTE',
		/* [55] */
		"Version Number (BCD)",
		'HBYT',
		/* [56] */
		"Revision Number (BCD)",
		'HBYT',
		/* [57] */
		"Revision Stage",
		'HBYT',
		/* [58] */
		"Development=$20",
		'CASE',
		/* [59] */
		"Alpha=$40",
		'CASE',
		/* [60] */
		"Beta=$60",
		'CASE',
		/* [61] */
		"Final=$80",
		'CASE',
		/* [62] */
		"Release=$80",
		'CASE',
		/* [63] */
		"Non-final build number (BCD)",
		'HBYT',
		/* [64] */
		"Version comparison procedure ('invc') re"
		"source ID",
		'RSID',
		/* [65] */
		"None=0",
		'CASE',
		/* [66] */
		"Atom Extender ('inex') resource ID",
		'RSID',
		/* [67] */
		"Atom description",
		'ESTR',
		/* [68] */
		"",
		'KEYE',
		/* [69] */
		"0",
		'KEYB',
		/* [70] */
		"Delete file or resource if \"Remove\" clic"
		"ked",
		'WBIT',
		/* [71] */
		"Delete target before copy",
		'WBIT',
		/* [72] */
		"Copy file or resource to destination",
		'WBIT',
		/* [73] */
		"Reserved",
		'WB08',
		/* [74] */
		"Leave file alone if newer",
		'WBIT',
		/* [75] */
		"Keep existing file (if On, bit 15 should"
		" be Off)",
		'WBIT',
		/* [76] */
		"Update only if target exists",
		'WBIT',
		/* [77] */
		"Apply operation to file's resource fork",
		'WBIT',
		/* [78] */
		"Apply operation to file's data fork",
		'WBIT',
		/* [79] */
		"Target File Spec ('intf') resource ID",
		'RSID',
		/* [80] */
		"Source File Spec ('infs') resource ID",
		'RSID',
		/* [81] */
		"Delete target only=0",
		'CASE',
		/* [82] */
		"File size (in bytes)",
		'ULNG',
		/* [83] */
		"Name of file user sees",
		'ESTR',
		/* [84] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1166, "inff") {
	{	/* array: 206 elements */
		/* [1] */
		"Font Family resource atom flags",
		'DVDR',
		/* [2] */
		"The only diffe between Format 1 and 2 is"
		" the 'FOND' encoding bit",
		'DVDR',
		/* [3] */
		"Font Family Atom format version",
		'KWRD',
		/* [4] */
		"Installer 4.0.3 or later=2",
		'CASE',
		/* [5] */
		"Installer 3.3 or later=1",
		'CASE',
		/* [6] */
		"Original=0",
		'CASE',
		/* [7] */
		"2",
		'KEYB',
		/* [8] */
		"Delete file or resource if remove clicke"
		"d",
		'WBIT',
		/* [9] */
		"Delete target before copy",
		'WBIT',
		/* [10] */
		"Copy file or resource to destination",
		'WBIT',
		/* [11] */
		"Reserved",
		'WB05',
		/* [12] */
		"Source 'FOND' data is in 'iFND' resource",
		'WBIT',
		/* [13] */
		"Target must exist first",
		'WBIT',
		/* [14] */
		"Keep target resource if it already exist"
		"s ",
		'WBIT',
		/* [15] */
		"Update resource only if target exists",
		'WBIT',
		/* [16] */
		"Do it even if resource protected",
		'WBIT',
		/* [17] */
		"Resource need not exist in source",
		'WBIT',
		/* [18] */
		"Find resource by ID (Off=by name)",
		'WBIT',
		/* [19] */
		"Resource name must match",
		'WBIT',
		/* [20] */
		"Target File Spec ('intf') resource ID  ",
		'RSID',
		/* [21] */
		"Source File Spec ('infs') resource ID",
		'RSID',
		/* [22] */
		"Target 'FOND' attributes",
		'DVDR',
		/* [23] */
		"Reserved",
		'WB09',
		/* [24] */
		"SysHeap",
		'WBIT',
		/* [25] */
		"Purgeable",
		'WBIT',
		/* [26] */
		"Locked",
		'WBIT',
		/* [27] */
		"Protected",
		'WBIT',
		/* [28] */
		"Preload",
		'WBIT',
		/* [29] */
		"Changed",
		'WBIT',
		/* [30] */
		"Reserved",
		'WBIT',
		/* [31] */
		"Size (in bytes) of complete family set",
		'DLNG',
		/* [32] */
		"Source 'FOND's resource ID",
		'RSID',
		/* [33] */
		"Type of family",
		'KWRD',
		/* [34] */
		"Entire family=1",
		'CASE',
		/* [35] */
		"Explicit family members=2",
		'CASE',
		/* [36] */
		"1",
		'KEYB',
		/* [37] */
		"",
		'KEYE',
		/* [38] */
		"2",
		'KEYB',
		/* [39] */
		"Count:",
		'OCNT',
		/* [40] */
		"List of Strikes",
		'LSTC',
		/* [41] */
		"Font size",
		'DWRD',
		/* [42] */
		"Unused",
		'WB09',
		/* [43] */
		"Extended",
		'WBIT',
		/* [44] */
		"Condensed",
		'WBIT',
		/* [45] */
		"Shadow",
		'WBIT',
		/* [46] */
		"Outline",
		'WBIT',
		/* [47] */
		"Underline",
		'WBIT',
		/* [48] */
		"Italic",
		'WBIT',
		/* [49] */
		"Bold",
		'WBIT',
		/* [50] */
		"Target font resource type",
		'TNAM',
		/* [51] */
		"Target resource attributes",
		'DVDR',
		/* [52] */
		"Reserved",
		'WB09',
		/* [53] */
		"SysHeap",
		'WBIT',
		/* [54] */
		"Purgeable",
		'WBIT',
		/* [55] */
		"Locked",
		'WBIT',
		/* [56] */
		"Protected",
		'WBIT',
		/* [57] */
		"Preload",
		'WBIT',
		/* [58] */
		"Changed",
		'WBIT',
		/* [59] */
		"Reserved",
		'WBIT',
		/* [60] */
		"Count:",
		'OCNT',
		/* [61] */
		"List of Source parts",
		'LSTC',
		/* [62] */
		"File Spec resource ID ('infs')  ",
		'RSID',
		/* [63] */
		"Resource type",
		'TNAM',
		/* [64] */
		"Resource ID",
		'RSID',
		/* [65] */
		"Size of resource (in bytes)",
		'ULNG',
		/* [66] */
		"Resource name",
		'ESTR',
		/* [67] */
		"*****",
		'LSTE',
		/* [68] */
		"*****",
		'LSTE',
		/* [69] */
		"",
		'KEYE',
		/* [70] */
		"Resource ID of Atom Extender ('inex')",
		'RSID',
		/* [71] */
		"Font family atom description",
		'ESTR',
		/* [72] */
		"Exact font family name",
		'ESTR',
		/* [73] */
		"",
		'KEYE',
		/* [74] */
		"1",
		'KEYB',
		/* [75] */
		"Font Family resource atom flags",
		'DVDR',
		/* [76] */
		"Delete file or resource if remove clicke"
		"d",
		'WBIT',
		/* [77] */
		"Delete target before copy",
		'WBIT',
		/* [78] */
		"Copy file or resource to destination",
		'WBIT',
		/* [79] */
		"Reserved",
		'WB06',
		/* [80] */
		"Target must exist first",
		'WBIT',
		/* [81] */
		"Keep target resource if it already exist"
		"s ",
		'WBIT',
		/* [82] */
		"Update resource only if target exists",
		'WBIT',
		/* [83] */
		"Do it even if resource protected",
		'WBIT',
		/* [84] */
		"Resource need not exist in source",
		'WBIT',
		/* [85] */
		"Find resource by ID (Off=by name)",
		'WBIT',
		/* [86] */
		"Resource name must match",
		'WBIT',
		/* [87] */
		"Target File Spec resource ID ('intf')  ",
		'RSID',
		/* [88] */
		"Source File Spec resource ID ('infs')  ",
		'RSID',
		/* [89] */
		"Target 'FOND' attributes",
		'DVDR',
		/* [90] */
		"Reserved",
		'WB09',
		/* [91] */
		"SysHeap",
		'WBIT',
		/* [92] */
		"Purgeable",
		'WBIT',
		/* [93] */
		"Locked",
		'WBIT',
		/* [94] */
		"Protected",
		'WBIT',
		/* [95] */
		"Preload",
		'WBIT',
		/* [96] */
		"Changed",
		'WBIT',
		/* [97] */
		"Reserved",
		'WBIT',
		/* [98] */
		"Size in bytes of complete family set",
		'DLNG',
		/* [99] */
		"Source 'FOND's resource ID",
		'RSID',
		/* [100] */
		"Type of family",
		'KWRD',
		/* [101] */
		"Entire family=1",
		'CASE',
		/* [102] */
		"Explicit family members=2",
		'CASE',
		/* [103] */
		"1",
		'KEYB',
		/* [104] */
		"",
		'KEYE',
		/* [105] */
		"2",
		'KEYB',
		/* [106] */
		"Count:",
		'OCNT',
		/* [107] */
		"List of Strikes",
		'LSTC',
		/* [108] */
		"Font size",
		'DWRD',
		/* [109] */
		"Unused",
		'WB09',
		/* [110] */
		"Extended",
		'WBIT',
		/* [111] */
		"Condensed",
		'WBIT',
		/* [112] */
		"Shadow",
		'WBIT',
		/* [113] */
		"Outline",
		'WBIT',
		/* [114] */
		"Underline",
		'WBIT',
		/* [115] */
		"Italic",
		'WBIT',
		/* [116] */
		"Bold",
		'WBIT',
		/* [117] */
		"Target font resource type",
		'TNAM',
		/* [118] */
		"Target resource attributes",
		'DVDR',
		/* [119] */
		"Reserved",
		'WB09',
		/* [120] */
		"SysHeap",
		'WBIT',
		/* [121] */
		"Purgeable",
		'WBIT',
		/* [122] */
		"Locked",
		'WBIT',
		/* [123] */
		"Protected",
		'WBIT',
		/* [124] */
		"Preload",
		'WBIT',
		/* [125] */
		"Changed",
		'WBIT',
		/* [126] */
		"Reserved",
		'WBIT',
		/* [127] */
		"Count:",
		'OCNT',
		/* [128] */
		"List of Source parts",
		'LSTC',
		/* [129] */
		"File Spec resource ID ('infs')  ",
		'RSID',
		/* [130] */
		"Resource type",
		'TNAM',
		/* [131] */
		"Resource ID",
		'RSID',
		/* [132] */
		"Size of resource (in bytes)",
		'ULNG',
		/* [133] */
		"Resource name",
		'ESTR',
		/* [134] */
		"*****",
		'LSTE',
		/* [135] */
		"*****",
		'LSTE',
		/* [136] */
		"",
		'KEYE',
		/* [137] */
		"Resource ID of Atom Extender ('inex')",
		'RSID',
		/* [138] */
		"Font family atom description",
		'ESTR',
		/* [139] */
		"Exact font family name",
		'ESTR',
		/* [140] */
		"",
		'KEYE',
		/* [141] */
		"0",
		'KEYB',
		/* [142] */
		"Resource atom flags",
		'DVDR',
		/* [143] */
		"Delete file or resource if remove clicke"
		"d",
		'WBIT',
		/* [144] */
		"Delete target before copy",
		'WBIT',
		/* [145] */
		"Copy file or resource to destination",
		'WBIT',
		/* [146] */
		"Reserved",
		'WB06',
		/* [147] */
		"Target must exist first",
		'WBIT',
		/* [148] */
		"Keep target resource if it already exist"
		"s ",
		'WBIT',
		/* [149] */
		"Update resource only if target exists",
		'WBIT',
		/* [150] */
		"Do it even if resource protected",
		'WBIT',
		/* [151] */
		"Resource need not exist in source",
		'WBIT',
		/* [152] */
		"Find resource by ID (Off=by name)",
		'WBIT',
		/* [153] */
		"Resource name must match",
		'WBIT',
		/* [154] */
		"Target File Spec resource ID ('infs')  ",
		'RSID',
		/* [155] */
		"ID of source file spec ('infs') of FOND",
		'RSID',
		/* [156] */
		"Target 'FOND' attributes",
		'DVDR',
		/* [157] */
		"Reserved",
		'WB09',
		/* [158] */
		"SysHeap",
		'WBIT',
		/* [159] */
		"Purgeable",
		'WBIT',
		/* [160] */
		"Locked",
		'WBIT',
		/* [161] */
		"Protected",
		'WBIT',
		/* [162] */
		"Preload",
		'WBIT',
		/* [163] */
		"Changed",
		'WBIT',
		/* [164] */
		"Reserved",
		'WBIT',
		/* [165] */
		"Size (in bytes) of complete family set",
		'DLNG',
		/* [166] */
		"Source 'FOND's resource ID",
		'RSID',
		/* [167] */
		"Type of family",
		'KWRD',
		/* [168] */
		"Entire family=1",
		'CASE',
		/* [169] */
		"Explicit family members=2",
		'CASE',
		/* [170] */
		"1",
		'KEYB',
		/* [171] */
		"",
		'KEYE',
		/* [172] */
		"2",
		'KEYB',
		/* [173] */
		"Count:",
		'OCNT',
		/* [174] */
		"List of Strikes",
		'LSTC',
		/* [175] */
		"Font size",
		'DWRD',
		/* [176] */
		"Unused",
		'WB09',
		/* [177] */
		"Extended",
		'WBIT',
		/* [178] */
		"Condensed",
		'WBIT',
		/* [179] */
		"Shadow",
		'WBIT',
		/* [180] */
		"Outline",
		'WBIT',
		/* [181] */
		"Underline",
		'WBIT',
		/* [182] */
		"Italic",
		'WBIT',
		/* [183] */
		"Bold",
		'WBIT',
		/* [184] */
		"Target font resource type",
		'TNAM',
		/* [185] */
		"Target resource attributes",
		'DVDR',
		/* [186] */
		"Reserved",
		'WB09',
		/* [187] */
		"SysHeap",
		'WBIT',
		/* [188] */
		"Purgeable",
		'WBIT',
		/* [189] */
		"Locked",
		'WBIT',
		/* [190] */
		"Protected",
		'WBIT',
		/* [191] */
		"Preload",
		'WBIT',
		/* [192] */
		"Changed",
		'WBIT',
		/* [193] */
		"Reserved",
		'WBIT',
		/* [194] */
		"Count:",
		'OCNT',
		/* [195] */
		"List of Source parts",
		'LSTC',
		/* [196] */
		"File Spec ('infs') resource ID",
		'RSID',
		/* [197] */
		"Resource type",
		'TNAM',
		/* [198] */
		"Resource ID",
		'RSID',
		/* [199] */
		"Size of resource (in bytes)",
		'ULNG',
		/* [200] */
		"Resource name",
		'ESTR',
		/* [201] */
		"*****",
		'LSTE',
		/* [202] */
		"*****",
		'LSTE',
		/* [203] */
		"",
		'KEYE',
		/* [204] */
		"Font family atom description",
		'ESTR',
		/* [205] */
		"Exact font family name",
		'ESTR',
		/* [206] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1167, "infm") {
	{	/* array: 9 elements */
		/* [1] */
		"Folder Merge format version",
		'KWRD',
		/* [2] */
		"Standard=0",
		'CASE',
		/* [3] */
		"0",
		'KEYB',
		/* [4] */
		"Reserved",
		'WB16',
		/* [5] */
		"Size of all files in folder",
		'ULNG',
		/* [6] */
		"Target file spec ('intf') resource ID",
		'RSID',
		/* [7] */
		"Source file spec ('infs') resource ID",
		'RSID',
		/* [8] */
		"Folder atom description",
		'ESTR',
		/* [9] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1168, "INFO") {
	{	/* array: 15 elements */
		/* [1] */
		"Color type",
		'DWRD',
		/* [2] */
		"Black & white=0",
		'CASE',
		/* [3] */
		"Color=1",
		'CASE',
		/* [4] */
		"Preferred color depth",
		'DWRD',
		/* [5] */
		"1 bit/pixel=1",
		'CASE',
		/* [6] */
		"2 bits/pixel=2",
		'CASE',
		/* [7] */
		"4 bits/pixel=4",
		'CASE',
		/* [8] */
		"8 bits/pixel=8",
		'CASE',
		/* [9] */
		"16 bits/pixel=16",
		'CASE',
		/* [10] */
		"Speed (1 to 200 frames/sec, or if negati"
		"ve, secs/frame)",
		'DWRD',
		/* [11] */
		"Version",
		'HWRD',
		/* [12] */
		"Latest=$0000",
		'CASE',
		/* [13] */
		"Application signature (creator type)",
		'TNAM',
		/* [14] */
		"Size of largest frame in bytes",
		'DLNG',
		/* [15] */
		"Ignore=0",
		'CASE'
	}
};

resource 'TMPL' (1169, "infr") {
	{	/* array: 18 elements */
		/* [1] */
		"Rule Framework format version",
		'KWRD',
		/* [2] */
		"Standard=0",
		'CASE',
		/* [3] */
		"0",
		'KEYB',
		/* [4] */
		"Count:",
		'OCNT',
		/* [5] */
		"List of Rules",
		'LSTC',
		/* [6] */
		"Which packages to pick",
		'WBIT',
		/* [7] */
		"First only=Off",
		'CASE',
		/* [8] */
		"All=On",
		'CASE',
		/* [9] */
		"Reserved",
		'WB15',
		/* [10] */
		"Count:",
		'OCNT',
		/* [11] */
		"List of Rules",
		'LSTC',
		/* [12] */
		"Rule ('inrl') resource ID",
		'RSID',
		/* [13] */
		"Easy install framework=764",
		'CASE',
		/* [14] */
		"Custom install framework=766",
		'CASE',
		/* [15] */
		"Global install framework=765",
		'CASE',
		/* [16] */
		"*****",
		'LSTE',
		/* [17] */
		"*****",
		'LSTE',
		/* [18] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1170, "infs") {
	{	/* array: 7 elements */
		/* [1] */
		"File type",
		'TNAM',
		/* [2] */
		"File creator",
		'TNAM',
		/* [3] */
		"Creation date",
		'DATE',
		/* [4] */
		"Search for target file if not in given p"
		"ath",
		'WBIT',
		/* [5] */
		"Type and creator must match",
		'WBIT',
		/* [6] */
		"Reserved",
		'WB14',
		/* [7] */
		"Full path",
		'ESTR'
	}
};

resource 'TMPL' (1171, "inpc") {
	{	/* array: 9 elements */
		/* [1] */
		"Package Comment format version",
		'KWRD',
		/* [2] */
		"Standard=1",
		'CASE',
		/* [3] */
		"1",
		'KEYB',
		/* [4] */
		"Date",
		'DATE',
		/* [5] */
		"Version",
		'HLNG',
		/* [6] */
		"RAM size (in bytes)",
		'ULNG',
		/* [7] */
		"'ICON' resource ID",
		'RSID',
		/* [8] */
		"Description ('TEXT') resource ID",
		'RSID',
		/* [9] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1172, "inpk") {
	{	/* array: 27 elements */
		/* [1] */
		"Package format version",
		'KWRD',
		/* [2] */
		"Standard=0",
		'CASE',
		/* [3] */
		"0",
		'KEYB',
		/* [4] */
		"Show package in Customize screen",
		'WBIT',
		/* [5] */
		"Package can be removed",
		'WBIT',
		/* [6] */
		"Don't force restart",
		'WBIT',
		/* [7] */
		"Reserved",
		'WB13',
		/* [8] */
		"Package comment ('inpc') resource ID ",
		'RSID',
		/* [9] */
		"No comment=0",
		'CASE',
		/* [10] */
		"Size of all files and rsrc to be copied",
		'ULNG',
		/* [11] */
		"Package name",
		'ESTR',
		/* [12] */
		"Default=Package Name",
		'CASE',
		/* [13] */
		"Divider=-",
		'CASE',
		/* [14] */
		"Count:",
		'OCNT',
		/* [15] */
		"Package parts",
		'LSTC',
		/* [16] */
		"Part resource type",
		'TNAM',
		/* [17] */
		"Sub-package=inpk",
		'CASE',
		/* [18] */
		"File atom=infa",
		'CASE',
		/* [19] */
		"Resource atom=inra",
		'CASE',
		/* [20] */
		"Font Family atom=inff",
		'CASE',
		/* [21] */
		"Folder Merge atom=infm",
		'CASE',
		/* [22] */
		"Resource Merge atom=inrm",
		'CASE',
		/* [23] */
		"Boot Block atom=inbb",
		'CASE',
		/* [24] */
		"Action atom=inaa",
		'CASE',
		/* [25] */
		"Part resource ID",
		'RSID',
		/* [26] */
		"*****",
		'LSTE',
		/* [27] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1173, "inpr") {
	{	/* array: 22 elements */
		/* [1] */
		"Preference format version",
		'KWRD',
		/* [2] */
		"Standard=0",
		'CASE',
		/* [3] */
		"0",
		'KEYB',
		/* [4] */
		"Target mode",
		'WBIT',
		/* [5] */
		"Use disk=Off",
		'CASE',
		/* [6] */
		"Use folder=On",
		'CASE',
		/* [7] */
		"Allow user to set System disk",
		'WBIT',
		/* [8] */
		"Show selected size in Custom",
		'WBIT',
		/* [9] */
		"Setup function is supplied",
		'WBIT',
		/* [10] */
		"Allow clean install",
		'WBIT',
		/* [11] */
		"Reserved",
		'WB11',
		/* [12] */
		"Type of code resource for Setup Function",
		'TNAM',
		/* [13] */
		"Setup Function code resource ID",
		'RSID',
		/* [14] */
		"Count:",
		'OCNT',
		/* [15] */
		"List of Help pages",
		'LSTC',
		/* [16] */
		"B&W left edge picture ('PICT') resource "
		"ID ",
		'RSID',
		/* [17] */
		"B&W main text ('PICT') resource ID ",
		'RSID',
		/* [18] */
		"8-bit edge picture ('PICT') resource ID ",
		'RSID',
		/* [19] */
		"8-bit main text ('PICT') resource ID ",
		'RSID',
		/* [20] */
		"*****",
		'LSTE',
		/* [21] */
		"If no Setup Function, default folder nam"
		"e",
		'ESTR',
		/* [22] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1174, "inr#") {
	{	/* array: 47 elements */
		/* [1] */
		"Resource Atom List version",
		'KWRD',
		/* [2] */
		"Standard=0",
		'CASE',
		/* [3] */
		"0",
		'KEYB',
		/* [4] */
		"Count:",
		'OCNT',
		/* [5] */
		"List of Resource atoms",
		'LSTC',
		/* [6] */
		"Resource ID (type to be added)",
		'DWRD',
		/* [7] */
		"Delete file or resource if remove clicke"
		"d",
		'WBIT',
		/* [8] */
		"Delete target before copy",
		'WBIT',
		/* [9] */
		"Copy file or resource to destination",
		'WBIT',
		/* [10] */
		"Reserved",
		'WB05',
		/* [11] */
		"Leave alone if newer version",
		'WBIT',
		/* [12] */
		"Target must exist first or be creatable",
		'WBIT',
		/* [13] */
		"Keep target resource if it already exist"
		"s ",
		'WBIT',
		/* [14] */
		"Update resource only if target exists",
		'WBIT',
		/* [15] */
		"Do it even if resource protected",
		'WBIT',
		/* [16] */
		"Resource need not exist in source",
		'WBIT',
		/* [17] */
		"Find resource by ID (Off ==> by name)",
		'WBIT',
		/* [18] */
		"Resource name must match (if bit 1 is Of"
		"f)",
		'WBIT',
		/* [19] */
		"Target resource size in bytes",
		'ULNG',
		/* [20] */
		"Target file spec ('intf') resource ID",
		'RSID',
		/* [21] */
		"Source file spec ('infs') resource ID",
		'RSID',
		/* [22] */
		"Source/target resource type",
		'TNAM',
		/* [23] */
		"Source/target resource ID",
		'RSID',
		/* [24] */
		"Target resource attributes",
		'DVDR',
		/* [25] */
		"Filler",
		'WB09',
		/* [26] */
		"System heap",
		'WBIT',
		/* [27] */
		"Purgeable",
		'WBIT',
		/* [28] */
		"Locked",
		'WBIT',
		/* [29] */
		"Protected",
		'WBIT',
		/* [30] */
		"Preload",
		'WBIT',
		/* [31] */
		"Changed (ignored)",
		'WB01',
		/* [32] */
		"Extension bit (compressed)",
		'WBIT',
		/* [33] */
		"Version Number (BCD)",
		'HBYT',
		/* [34] */
		"Revision Number (BCD)",
		'HBYT',
		/* [35] */
		"Revision Stage",
		'HBYT',
		/* [36] */
		"Development=$20",
		'CASE',
		/* [37] */
		"Alpha=$40",
		'CASE',
		/* [38] */
		"Beta=$60",
		'CASE',
		/* [39] */
		"Final=$80",
		'CASE',
		/* [40] */
		"Release=$80",
		'CASE',
		/* [41] */
		"Non-final build number (BCD)",
		'HBYT',
		/* [42] */
		"Version compare ('invc') resource ID",
		'RSID',
		/* [43] */
		"None=0",
		'CASE',
		/* [44] */
		"Atom Extender ('inex') resource ID",
		'RSID',
		/* [45] */
		"Total target size",
		'ULNG',
		/* [46] */
		"",
		'LSTE',
		/* [47] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1175, "inra") {
	{	/* array: 76 elements */
		/* [1] */
		"Resource Atom format version",
		'KWRD',
		/* [2] */
		"Latest=1",
		'CASE',
		/* [3] */
		"Original=0",
		'CASE',
		/* [4] */
		"1",
		'KEYB',
		/* [5] */
		"Delete file or resource if remove clicke"
		"d",
		'WBIT',
		/* [6] */
		"Delete target before copy",
		'WBIT',
		/* [7] */
		"Copy file or resource to destination",
		'WBIT',
		/* [8] */
		"Reserved",
		'WB05',
		/* [9] */
		"Leave alone if newer version",
		'WBIT',
		/* [10] */
		"Target must exist (or be creatable)",
		'WBIT',
		/* [11] */
		"Keep target resource if already exists ",
		'WBIT',
		/* [12] */
		"Update resource only if target exists",
		'WBIT',
		/* [13] */
		"Do it even if resource protected",
		'WBIT',
		/* [14] */
		"Resource need not exist in source",
		'WBIT',
		/* [15] */
		"Find resource by ID (Off=by name)",
		'WBIT',
		/* [16] */
		"Resource name must match (if bit 1 is Of"
		"f)",
		'WBIT',
		/* [17] */
		"Total target size in bytes",
		'ULNG',
		/* [18] */
		"Target File Spec ('intf') resource ID",
		'RSID',
		/* [19] */
		"Target resource type",
		'TNAM',
		/* [20] */
		"Target resource ID",
		'RSID',
		/* [21] */
		"Target resource attributes",
		'DVDR',
		/* [22] */
		"Filler",
		'WB09',
		/* [23] */
		"System heap",
		'WBIT',
		/* [24] */
		"Purgeable",
		'WBIT',
		/* [25] */
		"Locked",
		'WBIT',
		/* [26] */
		"Protected",
		'WBIT',
		/* [27] */
		"Preload",
		'WBIT',
		/* [28] */
		"Changed (ignored)",
		'WB01',
		/* [29] */
		"Extension bit (compressed)",
		'WBIT',
		/* [30] */
		"Target resource name",
		'ESTR',
		/* [31] */
		"Count:",
		'OCNT',
		/* [32] */
		"List of Source parts",
		'LSTC',
		/* [33] */
		"Source part file spec ('infs') resource "
		"ID",
		'RSID',
		/* [34] */
		"Source part resource type",
		'TNAM',
		/* [35] */
		"Source part resource ID",
		'RSID',
		/* [36] */
		"Target part size",
		'ULNG',
		/* [37] */
		"Source part resource name",
		'ESTR',
		/* [38] */
		"*****",
		'LSTE',
		/* [39] */
		"Version Number (BCD)",
		'HBYT',
		/* [40] */
		"Revision Number (BCD)",
		'HBYT',
		/* [41] */
		"Revision Stage",
		'HBYT',
		/* [42] */
		"Development=$20",
		'CASE',
		/* [43] */
		"Alpha=$40",
		'CASE',
		/* [44] */
		"Beta=$60",
		'CASE',
		/* [45] */
		"Final=$80",
		'CASE',
		/* [46] */
		"Release=$80",
		'CASE',
		/* [47] */
		"Non-final build number (BCD)",
		'HBYT',
		/* [48] */
		"Version compare ('invc') resource ID",
		'RSID',
		/* [49] */
		"None=0",
		'CASE',
		/* [50] */
		"Resource ID of Atom Extender ('inex')",
		'RSID',
		/* [51] */
		"Resource atom status description",
		'ESTR',
		/* [52] */
		"Building File:<target file's name>=",
		'CASE',
		/* [53] */
		"",
		'KEYE',
		/* [54] */
		"0",
		'KEYB',
		/* [55] */
		"Delete file or resource if remove clicke"
		"d",
		'WBIT',
		/* [56] */
		"Delete target before copy",
		'WBIT',
		/* [57] */
		"Copy file or resource to destination",
		'WBIT',
		/* [58] */
		"Reserved",
		'WB06',
		/* [59] */
		"Target must exist (or be creatable)",
		'WBIT',
		/* [60] */
		"Keep target rsrc if already exists ",
		'WBIT',
		/* [61] */
		"Update rsrc only if target exists",
		'WBIT',
		/* [62] */
		"Do it even if rsrc protected",
		'WBIT',
		/* [63] */
		"Resource need not exist in source",
		'WBIT',
		/* [64] */
		"Find resource by ID (Off=by name)",
		'WBIT',
		/* [65] */
		"Resource name must match",
		'WBIT',
		/* [66] */
		"Target File Spec ('intf') resource ID",
		'RSID',
		/* [67] */
		"Source File Spec ('infs') resource ID",
		'RSID',
		/* [68] */
		"Source and target resource type",
		'TNAM',
		/* [69] */
		"Source resource ID",
		'RSID',
		/* [70] */
		"Target resource ID",
		'RSID',
		/* [71] */
		"Doesn't matter=0",
		'CASE',
		/* [72] */
		"Target resource size in bytes",
		'ULNG',
		/* [73] */
		"Resource atom status description",
		'ESTR',
		/* [74] */
		"Building File:<target file's name>=",
		'CASE',
		/* [75] */
		"Target resource name",
		'ESTR',
		/* [76] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1176, "inrf") {
	{	/* array: 10 elements */
		/* [1] */
		"Rule Function format version",
		'KWRD',
		/* [2] */
		"Standard=0",
		'CASE',
		/* [3] */
		"0",
		'KEYB',
		/* [4] */
		"Reserved",
		'WB16',
		/* [5] */
		"Type of rule function code resource",
		'TNAM',
		/* [6] */
		"Resource ID of rule function code",
		'RSID',
		/* [7] */
		"Ref constant to pass to function",
		'DLNG',
		/* [8] */
		"Requested memory in bytes",
		'ULNG',
		/* [9] */
		"Optional summary string",
		'ESTR',
		/* [10] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1177, "inrl") {
	{	/* array: 407 elements */
		/* [1] */
		"Rules format version",
		'KWRD',
		/* [2] */
		"Standard=0",
		'CASE',
		/* [3] */
		"0",
		'KEYB',
		/* [4] */
		"Reserved",
		'WB16',
		/* [5] */
		"Count:",
		'OCNT',
		/* [6] */
		"List of Rules",
		'LSTC',
		/* [7] */
		"Condition",
		'KWRD',
		/* [8] */
		"Always FALSE=-2",
		'CASE',
		/* [9] */
		"Always TRUE=-1",
		'CASE',
		/* [10] */
		"Check Gestalt=1",
		'CASE',
		/* [11] */
		"Check minimum memory=2",
		'CASE',
		/* [12] */
		"Check for existent data fork=3",
		'CASE',
		/* [13] */
		"Check for existent resource fork=4",
		'CASE',
		/* [14] */
		"Check file for existing resource by ID=5",
		'CASE',
		/* [15] */
		"Check file for existing resource by name"
		"=6",
		'CASE',
		/* [16] */
		"Check file version=7",
		'CASE',
		/* [17] */
		"Check file country code=8",
		'CASE',
		/* [18] */
		"Check target volume size=9",
		'CASE',
		/* [19] */
		"Check user function=10",
		'CASE',
		/* [20] */
		"Check all assertions=11",
		'CASE',
		/* [21] */
		"Check any assertions=12",
		'CASE',
		/* [22] */
		"Check more than one assertion=13",
		'CASE',
		/* [23] */
		"Add user description=14",
		'CASE',
		/* [24] */
		"Add packages=15",
		'CASE',
		/* [25] */
		"Add assertion=16",
		'CASE',
		/* [26] */
		"Report volume error=17",
		'CASE',
		/* [27] */
		"Report system error=18",
		'CASE',
		/* [28] */
		"Add audit record=19",
		'CASE',
		/* [29] */
		"Check audit record=20",
		'CASE',
		/* [30] */
		"Check any audit record=21",
		'CASE',
		/* [31] */
		"Add custom items=22",
		'CASE',
		/* [32] */
		"Check all non assertion=23",
		'CASE',
		/* [33] */
		"Check any non assertion=24",
		'CASE',
		/* [34] */
		"Clear assertion=25",
		'CASE',
		/* [35] */
		"Check rule function=26",
		'CASE',
		/* [36] */
		"Check gestalt attributes=27",
		'CASE',
		/* [37] */
		"-2",
		'KEYB',
		/* [38] */
		"",
		'KEYE',
		/* [39] */
		"-1",
		'KEYB',
		/* [40] */
		"",
		'KEYE',
		/* [41] */
		"1",
		'KEYB',
		/* [42] */
		"Gestalt selector",
		'TNAM',
		/* [43] */
		"Addressing mode=addr",
		'CASE',
		/* [44] */
		"Alias Manager=alis",
		'CASE',
		/* [45] */
		"AppendDITL (from CTB) available=ditl",
		'CASE',
		/* [46] */
		"AppleTalk Version=atlk",
		'CASE',
		/* [47] */
		"A/UX Version=a/ux",
		'CASE',
		/* [48] */
		"Apple Events=evnt",
		'CASE',
		/* [49] */
		"Component Manager Version=cpnt",
		'CASE',
		/* [50] */
		"Connection Manager present=conn",
		'CASE',
		/* [51] */
		"CPU Type=proc",
		'CASE',
		/* [52] */
		"CTB Version=ctbv",
		'CASE',
		/* [53] */
		"DataBase Access Manager=dbac",
		'CASE',
		/* [54] */
		"Dictionary Manager=dict",
		'CASE',
		/* [55] */
		"Easy Access=easy",
		'CASE',
		/* [56] */
		"Edition Manager=edtn",
		'CASE',
		/* [57] */
		"Extended Toolbox Trap Table=xttt",
		'CASE',
		/* [58] */
		"File system=file",
		'CASE',
		/* [59] */
		"File transfer manager=fxfr",
		'CASE',
		/* [60] */
		"Floating Point Unit=fpu ",
		'CASE',
		/* [61] */
		"Folder Manager=fold",
		'CASE',
		/* [62] */
		"Font Manager=font",
		'CASE',
		/* [63] */
		"Hardware Attributes=hdwr",
		'CASE',
		/* [64] */
		"Help Manager=help",
		'CASE',
		/* [65] */
		"Icon Utilities=icon",
		'CASE',
		/* [66] */
		"Keyboard Type=kbd ",
		'CASE',
		/* [67] */
		"Logical Page Size=pgsz",
		'CASE',
		/* [68] */
		"Logical RAM Size=lram",
		'CASE',
		/* [69] */
		"Low Memory Size=lmem",
		'CASE',
		/* [70] */
		"Machine icon=micn",
		'CASE',
		/* [71] */
		"Machine Type=mach",
		'CASE',
		/* [72] */
		"Memory Management Unit=mmu ",
		'CASE',
		/* [73] */
		"Miscellaneous Attributes=misc",
		'CASE',
		/* [74] */
		"NBP attributes=nlup",
		'CASE',
		/* [75] */
		"Notification Manager=nmgr",
		'CASE',
		/* [76] */
		"NuBus connector bitmap=sltc",
		'CASE',
		/* [77] */
		"Operating System Attributes=os  ",
		'CASE',
		/* [78] */
		"OS Trap Table=ostt",
		'CASE',
		/* [79] */
		"Parity Attributes=prty",
		'CASE',
		/* [80] */
		"Physical RAM Size=ram ",
		'CASE',
		/* [81] */
		"Power Manager Attributes=powr",
		'CASE',
		/* [82] */
		"Processor Type=proc",
		'CASE',
		/* [83] */
		"PPC Toolbox Attributes=ppc ",
		'CASE',
		/* [84] */
		"QuickDraw Version=qd  ",
		'CASE',
		/* [85] */
		"QuickDraw Features=qdrw",
		'CASE',
		/* [86] */
		"Resource Manager Attributes=rsrc",
		'CASE',
		/* [87] */
		"ROM Size=rom ",
		'CASE',
		/* [88] */
		"ROM Version=romv",
		'CASE',
		/* [89] */
		"Serial attributes=ser",
		'CASE',
		/* [90] */
		"Script Count=src#",
		'CASE',
		/* [91] */
		"Script Manager Version=scri",
		'CASE',
		/* [92] */
		"Sound Manager Attributes=snd ",
		'CASE',
		/* [93] */
		"Standard File attributes=stdf",
		'CASE',
		/* [94] */
		"System Version=sysv",
		'CASE',
		/* [95] */
		"Terminal Manager Version=term",
		'CASE',
		/* [96] */
		"TextEdit Version=te  ",
		'CASE',
		/* [97] */
		"Text Services Manager Version=tsmv",
		'CASE',
		/* [98] */
		"Time Manager Version=tmgr",
		'CASE',
		/* [99] */
		"Toolbox Trap Table=tbtt",
		'CASE',
		/* [100] */
		"Version=vers",
		'CASE',
		/* [101] */
		"Virtual Memory Attributes=vm  ",
		'CASE',
		/* [102] */
		"Count:",
		'OCNT',
		/* [103] */
		"Possible return values",
		'LSTC',
		/* [104] */
		"Result",
		'DLNG',
		/* [105] */
		"Macintosh type: Unknown=0",
		'CASE',
		/* [106] */
		"Mac Plus=4",
		'CASE',
		/* [107] */
		"Mac SE=5",
		'CASE',
		/* [108] */
		"Mac II=6",
		'CASE',
		/* [109] */
		"Mac IIx=7",
		'CASE',
		/* [110] */
		"Mac IIcx=8",
		'CASE',
		/* [111] */
		"Mac SE/30=9",
		'CASE',
		/* [112] */
		"Mac Portable=10",
		'CASE',
		/* [113] */
		"Mac IIci=11",
		'CASE',
		/* [114] */
		"Mac IIfx=13",
		'CASE',
		/* [115] */
		"Mac Classic=17",
		'CASE',
		/* [116] */
		"Mac IIsi=18",
		'CASE',
		/* [117] */
		"Mac LC=19",
		'CASE',
		/* [118] */
		"Mac Quadra 900=20",
		'CASE',
		/* [119] */
		"Mac PowerBook 170=21",
		'CASE',
		/* [120] */
		"Mac Quadra 700=22",
		'CASE',
		/* [121] */
		"Mac Classic II=23",
		'CASE',
		/* [122] */
		"Mac PowerBook 100=24",
		'CASE',
		/* [123] */
		"Mac PowerBook 140=25",
		'CASE',
		/* [124] */
		"Mac Quadra 950=26",
		'CASE',
		/* [125] */
		"Mac LC III=27",
		'CASE',
		/* [126] */
		"Mac PowerBook Duo 210=29",
		'CASE',
		/* [127] */
		"Mac Centris 650=30",
		'CASE',
		/* [128] */
		"Mac PowerBook Duo 230=32",
		'CASE',
		/* [129] */
		"Mac PowerBook 180=33",
		'CASE',
		/* [130] */
		"Mac PowerBook 160=34",
		'CASE',
		/* [131] */
		"Mac Quadra 800=35",
		'CASE',
		/* [132] */
		"Mac Quadra 650=36",
		'CASE',
		/* [133] */
		"Mac LC II=37",
		'CASE',
		/* [134] */
		"Mac PowerBook Duo 250=38",
		'CASE',
		/* [135] */
		"PowerMac 9150=39",
		'CASE',
		/* [136] */
		"Mac IIvi=44",
		'CASE',
		/* [137] */
		"Mac Performa 600=45",
		'CASE',
		/* [138] */
		"Mac IIvx=48",
		'CASE',
		/* [139] */
		"Mac Color Classic=49",
		'CASE',
		/* [140] */
		"Mac PowerBook 165c=50",
		'CASE',
		/* [141] */
		"Mac Centris 610=52",
		'CASE',
		/* [142] */
		"Mac Quadra 610=53",
		'CASE',
		/* [143] */
		"Mac PowerBook 145=54",
		'CASE',
		/* [144] */
		"Mac LC 520=55",
		'CASE',
		/* [145] */
		"Mac Centris 660/AV=60",
		'CASE',
		/* [146] */
		"PowerMac 8100/80=65",
		'CASE',
		/* [147] */
		"Mac PowerBook 180c=71",
		'CASE',
		/* [148] */
		"Mac PowerBook 520 or 540=72",
		'CASE',
		/* [149] */
		"PowerMac 6100/60=75",
		'CASE',
		/* [150] */
		"Mac PowerBook Duo 270c=77",
		'CASE',
		/* [151] */
		"Mac Quadra 840/AV=78",
		'CASE',
		/* [152] */
		"Mac LC 550=80",
		'CASE',
		/* [153] */
		"Mac PowerBook 165=84",
		'CASE',
		/* [154] */
		"Mac TV=88",
		'CASE',
		/* [155] */
		"Mac LC 475=89",
		'CASE',
		/* [156] */
		"Mac LC 575=92",
		'CASE',
		/* [157] */
		"Mac Quadra 605=94",
		'CASE',
		/* [158] */
		"Mac Quadra or LC 630=98",
		'CASE',
		/* [159] */
		"Mac PowerBook Duo 280=102",
		'CASE',
		/* [160] */
		"Mac PowerBook Duo 280c=103",
		'CASE',
		/* [161] */
		"PowerMac 7100/66=112",
		'CASE',
		/* [162] */
		"Mac PowerBook 150=115",
		'CASE',
		/* [163] */
		"CPU Type: Unknown=0",
		'CASE',
		/* [164] */
		"68000=1",
		'CASE',
		/* [165] */
		"68010=2",
		'CASE',
		/* [166] */
		"68020=3",
		'CASE',
		/* [167] */
		"68030=4",
		'CASE',
		/* [168] */
		"68040=5",
		'CASE',
		/* [169] */
		"Memory Management: None=0",
		'CASE',
		/* [170] */
		"AMU=1",
		'CASE',
		/* [171] */
		"68851=2",
		'CASE',
		/* [172] */
		"68030 MMU=3",
		'CASE',
		/* [173] */
		"68040 MMU=4",
		'CASE',
		/* [174] */
		"Floating Point Unit: No FPU=0",
		'CASE',
		/* [175] */
		"68881=1",
		'CASE',
		/* [176] */
		"68882=2",
		'CASE',
		/* [177] */
		"68040FPU=3",
		'CASE',
		/* [178] */
		"Keyboard type: Unknown=0",
		'CASE',
		/* [179] */
		"Mac=1",
		'CASE',
		/* [180] */
		"MacAndPad=2",
		'CASE',
		/* [181] */
		"MacPlusKbd=3",
		'CASE',
		/* [182] */
		"Extended ADB=4",
		'CASE',
		/* [183] */
		"Standard ADB=5",
		'CASE',
		/* [184] */
		"Portable ADB=6",
		'CASE',
		/* [185] */
		"Portable Int'l=7",
		'CASE',
		/* [186] */
		"Standard Int'l ADB=8",
		'CASE',
		/* [187] */
		"Extended Int'l ADB=9",
		'CASE',
		/* [188] */
		"Elmer=10",
		'CASE',
		/* [189] */
		"Elmer Int'l=11",
		'CASE',
		/* [190] */
		"PowerBook ADB=12",
		'CASE',
		/* [191] */
		"PowerBook ISO ADB=13",
		'CASE',
		/* [192] */
		"Adjustable Keypad=14",
		'CASE',
		/* [193] */
		"Adjustable ADB=15",
		'CASE',
		/* [194] */
		"QuickDraw: Original=0",
		'CASE',
		/* [195] */
		"8-bit=256",
		'CASE',
		/* [196] */
		"32-bit=512",
		'CASE',
		/* [197] */
		"Time Manager: Unknown type=0",
		'CASE',
		/* [198] */
		"Standard=1",
		'CASE',
		/* [199] */
		"Revised=2",
		'CASE',
		/* [200] */
		"Extended=3",
		'CASE',
		/* [201] */
		"*****",
		'LSTE',
		/* [202] */
		"",
		'KEYE',
		/* [203] */
		"2",
		'KEYB',
		/* [204] */
		"Minimum memory (in megabytes)",
		'DLNG',
		/* [205] */
		"",
		'KEYE',
		/* [206] */
		"3",
		'KEYB',
		/* [207] */
		"File Spec ('intf') resource ID",
		'RSID',
		/* [208] */
		"",
		'KEYE',
		/* [209] */
		"4",
		'KEYB',
		/* [210] */
		"File Spec ('intf') resource ID",
		'RSID',
		/* [211] */
		"",
		'KEYE',
		/* [212] */
		"5",
		'KEYB',
		/* [213] */
		"File Spec ('intf') resource ID",
		'RSID',
		/* [214] */
		"Type of resource to check for",
		'TNAM',
		/* [215] */
		"System patch type=PTCH",
		'CASE',
		/* [216] */
		"Its resource ID",
		'RSID',
		/* [217] */
		"Mac Plus patch=117",
		'CASE',
		/* [218] */
		"Mac SE patch=630",
		'CASE',
		/* [219] */
		"Mac II patch=376",
		'CASE',
		/* [220] */
		"Mac Portable patch=890",
		'CASE',
		/* [221] */
		"Aurora patch=1660",
		'CASE',
		/* [222] */
		"",
		'KEYE',
		/* [223] */
		"6",
		'KEYB',
		/* [224] */
		"File Spec ('intf') resource ID",
		'RSID',
		/* [225] */
		"Type of resource to check for",
		'TNAM',
		/* [226] */
		"Its resource name",
		'ESTR',
		/* [227] */
		"",
		'KEYE',
		/* [228] */
		"7",
		'KEYB',
		/* [229] */
		"File Spec ('intf') resource ID",
		'RSID',
		/* [230] */
		"Version Number (BCD)",
		'HBYT',
		/* [231] */
		"Revision Number (BCD)",
		'HBYT',
		/* [232] */
		"Revision Stage",
		'HBYT',
		/* [233] */
		"Development=$20",
		'CASE',
		/* [234] */
		"Alpha=$40",
		'CASE',
		/* [235] */
		"Beta=$60",
		'CASE',
		/* [236] */
		"Final=$80",
		'CASE',
		/* [237] */
		"Release=$80",
		'CASE',
		/* [238] */
		"Non-final build number (BCD)",
		'HBYT',
		/* [239] */
		"",
		'KEYE',
		/* [240] */
		"8",
		'KEYB',
		/* [241] */
		"File Spec ('intf') resource ID",
		'RSID',
		/* [242] */
		"Language code",
		'LNGC',
		/* [243] */
		"",
		'KEYE',
		/* [244] */
		"9",
		'KEYB',
		/* [245] */
		"Smallest size this map will use (in Kb)",
		'DLNG',
		/* [246] */
		"Any size (floppy)=0",
		'CASE',
		/* [247] */
		"High density floppy=1400",
		'CASE',
		/* [248] */
		"Hard disk=10000",
		'CASE',
		/* [249] */
		"Largest size disk (in KBytes)",
		'DLNG',
		/* [250] */
		"Any size (hard disk)=0",
		'CASE',
		/* [251] */
		"Floppy=900",
		'CASE',
		/* [252] */
		"High density floppy=1500",
		'CASE',
		/* [253] */
		"",
		'KEYE',
		/* [254] */
		"10",
		'KEYB',
		/* [255] */
		"Executable resource type",
		'TNAM',
		/* [256] */
		"Executable resource ID",
		'RSID',
		/* [257] */
		"RefCon passed to executable resource",
		'DLNG',
		/* [258] */
		"",
		'KEYE',
		/* [259] */
		"11",
		'KEYB',
		/* [260] */
		"Count:",
		'OCNT',
		/* [261] */
		"List of Assertions",
		'LSTC',
		/* [262] */
		"Value",
		'DWRD',
		/* [263] */
		"*****",
		'LSTE',
		/* [264] */
		"",
		'KEYE',
		/* [265] */
		"12",
		'KEYB',
		/* [266] */
		"Count:",
		'OCNT',
		/* [267] */
		"List of Assertions",
		'LSTC',
		/* [268] */
		"Value",
		'DWRD',
		/* [269] */
		"*****",
		'LSTE',
		/* [270] */
		"",
		'KEYE',
		/* [271] */
		"13",
		'KEYB',
		/* [272] */
		"Count:",
		'OCNT',
		/* [273] */
		"List of Assertions",
		'LSTC',
		/* [274] */
		"Value",
		'DWRD',
		/* [275] */
		"*****",
		'LSTE',
		/* [276] */
		"",
		'KEYE',
		/* [277] */
		"14",
		'KEYB',
		/* [278] */
		"Description",
		'ESTR',
		/* [279] */
		"",
		'KEYE',
		/* [280] */
		"15",
		'KEYB',
		/* [281] */
		"Count:",
		'OCNT',
		/* [282] */
		"List of Packages",
		'LSTC',
		/* [283] */
		"'inpk' resource ID",
		'RSID',
		/* [284] */
		"*****",
		'LSTE',
		/* [285] */
		"",
		'KEYE',
		/* [286] */
		"16",
		'KEYB',
		/* [287] */
		"Count:",
		'OCNT',
		/* [288] */
		"List of Assertions",
		'LSTC',
		/* [289] */
		"Value",
		'DWRD',
		/* [290] */
		"*****",
		'LSTE',
		/* [291] */
		"",
		'KEYE',
		/* [292] */
		"17",
		'KEYB',
		/* [293] */
		"Message",
		'ESTR',
		/* [294] */
		"",
		'KEYE',
		/* [295] */
		"18",
		'KEYB',
		/* [296] */
		"Message",
		'ESTR',
		/* [297] */
		"",
		'KEYE',
		/* [298] */
		"19",
		'KEYB',
		/* [299] */
		"File Spec ('intf') resource ID",
		'RSID',
		/* [300] */
		"Resource type",
		'TNAM',
		/* [301] */
		"Resource ID",
		'DLNG',
		/* [302] */
		"",
		'KEYE',
		/* [303] */
		"20",
		'KEYB',
		/* [304] */
		"File Spec ('intf') resource ID",
		'RSID',
		/* [305] */
		"Resource type",
		'TNAM',
		/* [306] */
		"Resource ID",
		'DLNG',
		/* [307] */
		"",
		'KEYE',
		/* [308] */
		"21",
		'KEYB',
		/* [309] */
		"File Spec ('intf') resource ID",
		'RSID',
		/* [310] */
		"Resource type",
		'TNAM',
		/* [311] */
		"Count:",
		'OCNT',
		/* [312] */
		"List of Resources",
		'LSTC',
		/* [313] */
		"Resource ID",
		'DLNG',
		/* [314] */
		"*****",
		'LSTE',
		/* [315] */
		"",
		'KEYE',
		/* [316] */
		"22",
		'KEYB',
		/* [317] */
		"Count:",
		'OCNT',
		/* [318] */
		"List of Packages",
		'LSTC',
		/* [319] */
		"'inpk' resource ID",
		'RSID',
		/* [320] */
		"*****",
		'LSTE',
		/* [321] */
		"",
		'KEYE',
		/* [322] */
		"23",
		'KEYB',
		/* [323] */
		"Count:",
		'OCNT',
		/* [324] */
		"List of Assertions",
		'LSTC',
		/* [325] */
		"Value",
		'DWRD',
		/* [326] */
		"*****",
		'LSTE',
		/* [327] */
		"",
		'KEYE',
		/* [328] */
		"24",
		'KEYB',
		/* [329] */
		"Count:",
		'OCNT',
		/* [330] */
		"List of Assertions",
		'LSTC',
		/* [331] */
		"Value",
		'DWRD',
		/* [332] */
		"*****",
		'LSTE',
		/* [333] */
		"",
		'KEYE',
		/* [334] */
		"25",
		'KEYB',
		/* [335] */
		"Count:",
		'OCNT',
		/* [336] */
		"List of Assertions",
		'LSTC',
		/* [337] */
		"Value",
		'DWRD',
		/* [338] */
		"*****",
		'LSTE',
		/* [339] */
		"",
		'KEYE',
		/* [340] */
		"26",
		'KEYB',
		/* [341] */
		"Rule function ('inrf') resource ID",
		'RSID',
		/* [342] */
		"",
		'KEYE',
		/* [343] */
		"27",
		'KEYB',
		/* [344] */
		"Gestalt selector",
		'TNAM',
		/* [345] */
		"Addressing mode=addr",
		'CASE',
		/* [346] */
		"Alias Manager=alis",
		'CASE',
		/* [347] */
		"AppendDITL (from CTB) available=ditl",
		'CASE',
		/* [348] */
		"AppleTalk Version=atlk",
		'CASE',
		/* [349] */
		"A/UX Version=a/ux",
		'CASE',
		/* [350] */
		"Apple Events=evnt",
		'CASE',
		/* [351] */
		"Component Manager Version=cpnt",
		'CASE',
		/* [352] */
		"Connection Manager present=conn",
		'CASE',
		/* [353] */
		"CPU Type=proc",
		'CASE',
		/* [354] */
		"CTB Version=ctbv",
		'CASE',
		/* [355] */
		"DataBase Access Manager=dbac",
		'CASE',
		/* [356] */
		"Dictionary Manager=dict",
		'CASE',
		/* [357] */
		"Easy Access=easy",
		'CASE',
		/* [358] */
		"Edition Manager=edtn",
		'CASE',
		/* [359] */
		"Extended Toolbox Trap Table=xttt",
		'CASE',
		/* [360] */
		"File system=file",
		'CASE',
		/* [361] */
		"File transfer manager=fxfr",
		'CASE',
		/* [362] */
		"Floating Point Unit=fpu ",
		'CASE',
		/* [363] */
		"Folder Manager=fold",
		'CASE',
		/* [364] */
		"Font Manager=font",
		'CASE',
		/* [365] */
		"Hardware Attributes=hdwr",
		'CASE',
		/* [366] */
		"Help Manager=help",
		'CASE',
		/* [367] */
		"Icon Utilities=icon",
		'CASE',
		/* [368] */
		"Keyboard Type=kbd ",
		'CASE',
		/* [369] */
		"Logical Page Size=pgsz",
		'CASE',
		/* [370] */
		"Logical RAM Size=lram",
		'CASE',
		/* [371] */
		"Low Memory Size=lmem",
		'CASE',
		/* [372] */
		"Machine icon=micn",
		'CASE',
		/* [373] */
		"Machine Type=mach",
		'CASE',
		/* [374] */
		"Memory Management Unit=mmu ",
		'CASE',
		/* [375] */
		"Miscellaneous Attributes=misc",
		'CASE',
		/* [376] */
		"NBP attributes=nlup",
		'CASE',
		/* [377] */
		"Notification Manager=nmgr",
		'CASE',
		/* [378] */
		"NuBus connector bitmap=sltc",
		'CASE',
		/* [379] */
		"Operating System Attributes=os  ",
		'CASE',
		/* [380] */
		"OS Trap Table=ostt",
		'CASE',
		/* [381] */
		"Parity Attributes=prty",
		'CASE',
		/* [382] */
		"Physical RAM Size=ram ",
		'CASE',
		/* [383] */
		"Power Manager Attributes=powr",
		'CASE',
		/* [384] */
		"Processor Type=proc",
		'CASE',
		/* [385] */
		"PPC Toolbox Attributes=ppc ",
		'CASE',
		/* [386] */
		"QuickDraw Version=qd  ",
		'CASE',
		/* [387] */
		"QuickDraw Features=qdrw",
		'CASE',
		/* [388] */
		"Resource Manager Attributes=rsrc",
		'CASE',
		/* [389] */
		"ROM Size=rom ",
		'CASE',
		/* [390] */
		"ROM Version=romv",
		'CASE',
		/* [391] */
		"Serial attributes=ser",
		'CASE',
		/* [392] */
		"Script Count=src#",
		'CASE',
		/* [393] */
		"Script Manager Version=scri",
		'CASE',
		/* [394] */
		"Sound Manager Attributes=snd ",
		'CASE',
		/* [395] */
		"Standard File attributes=stdf",
		'CASE',
		/* [396] */
		"System Version=sysv",
		'CASE',
		/* [397] */
		"Terminal Manager Version=term",
		'CASE',
		/* [398] */
		"TextEdit Version=te  ",
		'CASE',
		/* [399] */
		"Text Services Manager Version=tsmv",
		'CASE',
		/* [400] */
		"Time Manager Version=tmgr",
		'CASE',
		/* [401] */
		"Toolbox Trap Table=tbtt",
		'CASE',
		/* [402] */
		"Version=vers",
		'CASE',
		/* [403] */
		"Virtual Memory Attributes=vm  ",
		'CASE',
		/* [404] */
		"Return value bit mask",
		'HLNG',
		/* [405] */
		"",
		'KEYE',
		/* [406] */
		"*****",
		'LSTE',
		/* [407] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1178, "inrm") {
	{	/* array: 9 elements */
		/* [1] */
		"Resource Merge format version",
		'KWRD',
		/* [2] */
		"Standard=0",
		'CASE',
		/* [3] */
		"0",
		'KEYB',
		/* [4] */
		"Reserved",
		'WB16',
		/* [5] */
		"Total size of all resources",
		'ULNG',
		/* [6] */
		"Target file spec ('intf') resource ID",
		'RSID',
		/* [7] */
		"Source file spec ('infs') resource ID",
		'RSID',
		/* [8] */
		"Atom description",
		'ESTR',
		/* [9] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1179, "insc") {
	{	/* array: 53 elements */
		/* [1] */
		"Format",
		'DWRD',
		/* [2] */
		"Flags",
		'HWRD',
		/* [3] */
		"Script name",
		'ESTR',
		/* [4] */
		"Help",
		'WSTR',
		/* [5] */
		"Align",
		'AWRD',
		/* [6] */
		"Count:",
		'OCNT',
		/* [7] */
		"Files",
		'LSTC',
		/* [8] */
		"File spec",
		'HWRD',
		/* [9] */
		"Type",
		'TNAM',
		/* [10] */
		"Creator",
		'TNAM',
		/* [11] */
		"Creation date",
		'DATE',
		/* [12] */
		"Handle",
		'FLNG',
		/* [13] */
		"Del size",
		'FLNG',
		/* [14] */
		"Add size",
		'FLNG',
		/* [15] */
		"File name",
		'ESTR',
		/* [16] */
		"*****",
		'LSTE',
		/* [17] */
		"Count:",
		'OCNT',
		/* [18] */
		"Resource files",
		'LSTC',
		/* [19] */
		"File spec",
		'HWRD',
		/* [20] */
		"Type",
		'TNAM',
		/* [21] */
		"Creator",
		'TNAM',
		/* [22] */
		"Creation date",
		'DATE',
		/* [23] */
		"Handle",
		'FLNG',
		/* [24] */
		"Del size",
		'FLNG',
		/* [25] */
		"Add size",
		'FLNG',
		/* [26] */
		"To file name",
		'ESTR',
		/* [27] */
		"Count:",
		'OCNT',
		/* [28] */
		"From files",
		'LSTC',
		/* [29] */
		"File spec",
		'HWRD',
		/* [30] */
		"Type",
		'TNAM',
		/* [31] */
		"Creator",
		'TNAM',
		/* [32] */
		"Creation date",
		'DATE',
		/* [33] */
		"Handle",
		'FLNG',
		/* [34] */
		"Del size",
		'FLNG',
		/* [35] */
		"Add size",
		'FLNG',
		/* [36] */
		"From file name",
		'ESTR',
		/* [37] */
		"Count:",
		'OCNT',
		/* [38] */
		"Resources",
		'LSTC',
		/* [39] */
		"Rspec",
		'HWRD',
		/* [40] */
		"Type",
		'TNAM',
		/* [41] */
		"Source ID",
		'DWRD',
		/* [42] */
		"Target ID",
		'DWRD',
		/* [43] */
		"Crc/version",
		'DWRD',
		/* [44] */
		"Filler1 (2 bytes)",
		'FWRD',
		/* [45] */
		"Filler2 (4 bytes)",
		'FLNG',
		/* [46] */
		"Del size",
		'FLNG',
		/* [47] */
		"Add size",
		'FLNG',
		/* [48] */
		"Resource name",
		'ESTR',
		/* [49] */
		"Prev crcs",
		'HWRD',
		/* [50] */
		"-----",
		'LSTE',
		/* [51] */
		"+++++",
		'LSTE',
		/* [52] */
		"*****",
		'LSTE',
		/* [53] */
		"Dump",
		'HEXD'
	}
};

resource 'TMPL' (1180, "insp") {
	{	/* array: 10 elements */
		/* [1] */
		"Search Procedure format version",
		'KWRD',
		/* [2] */
		"Standard=0",
		'CASE',
		/* [3] */
		"0",
		'KEYB',
		/* [4] */
		"Reserved",
		'WB16',
		/* [5] */
		"Type of search code resource",
		'TNAM',
		/* [6] */
		"Resource ID of search code",
		'RSID',
		/* [7] */
		"Ref constant to pass to procedure",
		'DLNG',
		/* [8] */
		"Requested memory in bytes",
		'ULNG',
		/* [9] */
		"Optional summary string",
		'ESTR',
		/* [10] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1181, "insz") {
	{	/* array: 5 elements */
		/* [1] */
		"Script Size format version",
		'KWRD',
		/* [2] */
		"Standard=0",
		'CASE',
		/* [3] */
		"0",
		'KEYB',
		/* [4] */
		"Script sub-heap size in bytes",
		'ULNG',
		/* [5] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1182, "intf") {
	{	/* array: 46 elements */
		/* [1] */
		"Target FileSpec format version",
		'KWRD',
		/* [2] */
		"Installer 4.0 or later=1",
		'CASE',
		/* [3] */
		"Original=0",
		'CASE',
		/* [4] */
		"1",
		'KEYB',
		/* [5] */
		"Search for target file if not in given p"
		"ath",
		'WBIT',
		/* [6] */
		"Type and creator must match",
		'WBIT',
		/* [7] */
		"Reserved",
		'WB14',
		/* [8] */
		"Target file type",
		'TNAM',
		/* [9] */
		"Target file creator",
		'TNAM',
		/* [10] */
		"Finder file attribute flags",
		'DVDR',
		/* [11] */
		"File is an alias",
		'WBIT',
		/* [12] */
		"File is invisible",
		'WBIT',
		/* [13] */
		"File has a bundle ('BNDL')",
		'WBIT',
		/* [14] */
		"File name is locked",
		'WBIT',
		/* [15] */
		"File is a stationery pad",
		'WBIT',
		/* [16] */
		"File has a custom icon",
		'WBIT',
		/* [17] */
		"Reserved",
		'WBIT',
		/* [18] */
		"Bundle has been recorded (inited)",
		'WBIT',
		/* [19] */
		"File has no 'INIT's",
		'WBIT',
		/* [20] */
		"File is shareable",
		'WBIT',
		/* [21] */
		"File requires switch launch",
		'WBIT',
		/* [22] */
		"Reserved",
		'WBIT',
		/* [23] */
		"Label",
		'WB03',
		/* [24] */
		"None=0",
		'CASE',
		/* [25] */
		"Essential=7",
		'CASE',
		/* [26] */
		"Hot=6",
		'CASE',
		/* [27] */
		"In progress=5",
		'CASE',
		/* [28] */
		"Cool=4",
		'CASE',
		/* [29] */
		"Personal=3",
		'CASE',
		/* [30] */
		"Project 1=2",
		'CASE',
		/* [31] */
		"Project 2=1",
		'CASE',
		/* [32] */
		"File is on desktop",
		'WBIT',
		/* [33] */
		"Creation Date of new file",
		'DATE',
		/* [34] */
		"Modification Date of new file",
		'DATE',
		/* [35] */
		"Resource ID of search procedure ('insp')"
		"  ",
		'RSID',
		/* [36] */
		"Target file path",
		'ESTR',
		/* [37] */
		"",
		'KEYE',
		/* [38] */
		"0",
		'KEYB',
		/* [39] */
		"Search for target file if not in given p"
		"ath",
		'WBIT',
		/* [40] */
		"Type and creator must match",
		'WBIT',
		/* [41] */
		"Reserved",
		'WB14',
		/* [42] */
		"Target file type",
		'TNAM',
		/* [43] */
		"Target file creator",
		'TNAM',
		/* [44] */
		"Search procedure ('insp') resource ID",
		'RSID',
		/* [45] */
		"Target file path",
		'ESTR',
		/* [46] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1183, "invc") {
	{	/* array: 9 elements */
		/* [1] */
		"Version Compare format version",
		'KWRD',
		/* [2] */
		"Standard=0",
		'CASE',
		/* [3] */
		"0",
		'KEYB',
		/* [4] */
		"Reserved",
		'WB16',
		/* [5] */
		"Type of comparison code resource",
		'TNAM',
		/* [6] */
		"Comparison code resource ID",
		'RSID',
		/* [7] */
		"Requested memory in bytes",
		'ULNG',
		/* [8] */
		"Optional summary string",
		'ESTR',
		/* [9] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1184, "invs") {
	{	/* array: 14 elements */
		/* [1] */
		"Version format version",
		'KWRD',
		/* [2] */
		"Standard=0",
		'CASE',
		/* [3] */
		"0",
		'KEYB',
		/* [4] */
		"Version number (BCD)",
		'HBYT',
		/* [5] */
		"Revision number (BCD)",
		'HBYT',
		/* [6] */
		"Revision stage",
		'HBYT',
		/* [7] */
		"Development=$20",
		'CASE',
		/* [8] */
		"Alpha=$40",
		'CASE',
		/* [9] */
		"Beta=$60",
		'CASE',
		/* [10] */
		"Final=$80",
		'CASE',
		/* [11] */
		"Release=$80",
		'CASE',
		/* [12] */
		"Non-final build number (BCD)",
		'HBYT',
		/* [13] */
		"Short version string",
		'PSTR',
		/* [14] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1185, "iobm") {
	{	/* array: 9 elements */
		/* [1] */
		"Communications options",
		'DLNG',
		/* [2] */
		"Standard=0",
		'CASE',
		/* [3] */
		"Custom (including SCSI)=1",
		'CASE',
		/* [4] */
		"Number of buffers to allocate",
		'DLNG',
		/* [5] */
		"None=0",
		'CASE',
		/* [6] */
		"Size (in bytes) of each buffer",
		'DLNG',
		/* [7] */
		"Number of I/O requests pending at one ti"
		"me",
		'DLNG',
		/* [8] */
		"Open/close timeout (in ticks)",
		'DLNG',
		/* [9] */
		"Read/write timeout (in ticks)",
		'DLNG'
	}
};

resource 'TMPL' (1186, "isys") {
	{	/* array: 1 elements */
		/* [1] */
		"Resource type of imaging system to selec"
		"t",
		'TNAM'
	}
};

resource 'TMPL' (1187, "ITEM") {
	{	/* array: 260 elements */
		/* [1] */
		"Item type",
		'KBYT',
		/* [2] */
		"Control=0",
		'CASE',
		/* [3] */
		"Static text=1",
		'CASE',
		/* [4] */
		"Frame=2",
		'CASE',
		/* [5] */
		"Line=3",
		'CASE',
		/* [6] */
		"Empty box=4",
		'CASE',
		/* [7] */
		"Filled box=5",
		'CASE',
		/* [8] */
		"Popup box=6",
		'CASE',
		/* [9] */
		"Bold button=7",
		'CASE',
		/* [10] */
		"Icon=8",
		'CASE',
		/* [11] */
		"Color selector=9",
		'CASE',
		/* [12] */
		"Edit text=10",
		'CASE',
		/* [13] */
		"Picture=11",
		'CASE',
		/* [14] */
		"Scroll bar=12",
		'CASE',
		/* [15] */
		"0",
		'KEYB',
		/* [16] */
		"Reserved",
		'BB07',
		/* [17] */
		"Window is object",
		'BB01',
		/* [18] */
		"Item bounds",
		'RECT',
		/* [19] */
		"Other bounds",
		'RECT',
		/* [20] */
		"Reserved",
		'BB07',
		/* [21] */
		"Visible item",
		'BB01',
		/* [22] */
		"Reserved",
		'BB07',
		/* [23] */
		"Enabled item",
		'BB01',
		/* [24] */
		"Reserved",
		'BB07',
		/* [25] */
		"Can hit",
		'BB01',
		/* [26] */
		"Reserved",
		'FBYT',
		/* [27] */
		"'CNTL' resource ID",
		'RSID',
		/* [28] */
		"",
		'KEYE',
		/* [29] */
		"1",
		'KEYB',
		/* [30] */
		"Reserved",
		'BB07',
		/* [31] */
		"Window is object",
		'BB01',
		/* [32] */
		"Item bounds",
		'RECT',
		/* [33] */
		"Other bounds",
		'RECT',
		/* [34] */
		"Reserved",
		'BB07',
		/* [35] */
		"Visible item",
		'BB01',
		/* [36] */
		"Reserved",
		'BB07',
		/* [37] */
		"Enabled item",
		'BB01',
		/* [38] */
		"Reserved",
		'BB07',
		/* [39] */
		"Can hit",
		'BB01',
		/* [40] */
		"Reserved",
		'FBYT',
		/* [41] */
		"Font resource ID",
		'RSID',
		/* [42] */
		"Font size",
		'DWRD',
		/* [43] */
		"Reserved",
		'FBYT',
		/* [44] */
		"Reserved",
		'FBYT',
		/* [45] */
		"Reserved",
		'FBYT',
		/* [46] */
		"Justification",
		'DBYT',
		/* [47] */
		"Left=0",
		'CASE',
		/* [48] */
		"Right=1",
		'CASE',
		/* [49] */
		"Centered=2",
		'CASE',
		/* [50] */
		"Reserved",
		'FBYT',
		/* [51] */
		"Reserved",
		'FBYT',
		/* [52] */
		"Reserved",
		'FBYT',
		/* [53] */
		"Arrow (ignored)",
		'FBYT',
		/* [54] */
		"Text",
		'PSTR',
		/* [55] */
		"",
		'KEYE',
		/* [56] */
		"2",
		'KEYB',
		/* [57] */
		"Reserved",
		'BB07',
		/* [58] */
		"Window is object",
		'BB01',
		/* [59] */
		"Item bounds",
		'RECT',
		/* [60] */
		"Other bounds",
		'RECT',
		/* [61] */
		"Reserved",
		'BB07',
		/* [62] */
		"Visible item",
		'BB01',
		/* [63] */
		"Reserved",
		'BB07',
		/* [64] */
		"Enabled item",
		'BB01',
		/* [65] */
		"Reserved",
		'BB07',
		/* [66] */
		"Can hit",
		'BB01',
		/* [67] */
		"Reserved",
		'FBYT',
		/* [68] */
		"Font resource ID",
		'RSID',
		/* [69] */
		"Font size",
		'DWRD',
		/* [70] */
		"Reserved",
		'FBYT',
		/* [71] */
		"Reserved",
		'FBYT',
		/* [72] */
		"Reserved",
		'FBYT',
		/* [73] */
		"Justification",
		'DBYT',
		/* [74] */
		"Left=0",
		'CASE',
		/* [75] */
		"Right=1",
		'CASE',
		/* [76] */
		"Centered=2",
		'CASE',
		/* [77] */
		"Reserved",
		'FBYT',
		/* [78] */
		"Reserved",
		'FBYT',
		/* [79] */
		"Reserved",
		'FBYT',
		/* [80] */
		"Arrow (ignored)",
		'FBYT',
		/* [81] */
		"Text",
		'PSTR',
		/* [82] */
		"",
		'KEYE',
		/* [83] */
		"3",
		'KEYB',
		/* [84] */
		"Reserved",
		'BB07',
		/* [85] */
		"Window is object",
		'BB01',
		/* [86] */
		"Item bounds",
		'RECT',
		/* [87] */
		"Other bounds",
		'RECT',
		/* [88] */
		"Reserved",
		'BB07',
		/* [89] */
		"Visible item",
		'BB01',
		/* [90] */
		"Reserved",
		'BB07',
		/* [91] */
		"Enabled item",
		'BB01',
		/* [92] */
		"Reserved",
		'BB07',
		/* [93] */
		"Can hit",
		'BB01',
		/* [94] */
		"Reserved",
		'FBYT',
		/* [95] */
		"",
		'KEYE',
		/* [96] */
		"4",
		'KEYB',
		/* [97] */
		"Reserved",
		'BB07',
		/* [98] */
		"Window is object",
		'BB01',
		/* [99] */
		"Item bounds",
		'RECT',
		/* [100] */
		"Other bounds",
		'RECT',
		/* [101] */
		"Reserved",
		'BB07',
		/* [102] */
		"Visible item",
		'BB01',
		/* [103] */
		"Reserved",
		'BB07',
		/* [104] */
		"Enabled item",
		'BB01',
		/* [105] */
		"Reserved",
		'BB07',
		/* [106] */
		"Can hit",
		'BB01',
		/* [107] */
		"Reserved",
		'FBYT',
		/* [108] */
		"",
		'KEYE',
		/* [109] */
		"5",
		'KEYB',
		/* [110] */
		"Reserved",
		'BB07',
		/* [111] */
		"Window is object",
		'BB01',
		/* [112] */
		"Item bounds",
		'RECT',
		/* [113] */
		"Other bounds",
		'RECT',
		/* [114] */
		"Reserved",
		'BB07',
		/* [115] */
		"Visible item",
		'BB01',
		/* [116] */
		"Reserved",
		'BB07',
		/* [117] */
		"Enabled item",
		'BB01',
		/* [118] */
		"Reserved",
		'BB07',
		/* [119] */
		"Can hit",
		'BB01',
		/* [120] */
		"Reserved",
		'FBYT',
		/* [121] */
		"Fill pattern",
		'DBYT',
		/* [122] */
		"White=0",
		'CASE',
		/* [123] */
		"Light gray=1",
		'CASE',
		/* [124] */
		"Gray=2",
		'CASE',
		/* [125] */
		"Dark gray=3",
		'CASE',
		/* [126] */
		"Black=4",
		'CASE',
		/* [127] */
		"Reserved",
		'FBYT',
		/* [128] */
		"",
		'KEYE',
		/* [129] */
		"6",
		'KEYB',
		/* [130] */
		"Reserved",
		'BB07',
		/* [131] */
		"Window is object",
		'BB01',
		/* [132] */
		"Item bounds",
		'RECT',
		/* [133] */
		"Other bounds",
		'RECT',
		/* [134] */
		"Reserved",
		'BB07',
		/* [135] */
		"Visible item",
		'BB01',
		/* [136] */
		"Reserved",
		'BB07',
		/* [137] */
		"Enabled item",
		'BB01',
		/* [138] */
		"Reserved",
		'BB07',
		/* [139] */
		"Can hit",
		'BB01',
		/* [140] */
		"Reserved",
		'FBYT',
		/* [141] */
		"Font resource ID",
		'RSID',
		/* [142] */
		"Font size",
		'DWRD',
		/* [143] */
		"Reserved",
		'FBYT',
		/* [144] */
		"Reserved",
		'FBYT',
		/* [145] */
		"Reserved",
		'FBYT',
		/* [146] */
		"Justification (ignored)",
		'FBYT',
		/* [147] */
		"Reserved",
		'FBYT',
		/* [148] */
		"Reserved",
		'FBYT',
		/* [149] */
		"Reserved",
		'FBYT',
		/* [150] */
		"Kind of arrow",
		'DBYT',
		/* [151] */
		"None=0",
		'CASE',
		/* [152] */
		"Standard=1",
		'CASE',
		/* [153] */
		"Text",
		'PSTR',
		/* [154] */
		"",
		'KEYE',
		/* [155] */
		"7",
		'KEYB',
		/* [156] */
		"Reserved",
		'BB07',
		/* [157] */
		"Window is object",
		'BB01',
		/* [158] */
		"Item bounds",
		'RECT',
		/* [159] */
		"Other bounds",
		'RECT',
		/* [160] */
		"Reserved",
		'BB07',
		/* [161] */
		"Visible item",
		'BB01',
		/* [162] */
		"Reserved",
		'BB07',
		/* [163] */
		"Enabled item",
		'BB01',
		/* [164] */
		"Reserved",
		'BB07',
		/* [165] */
		"Can hit",
		'BB01',
		/* [166] */
		"Reserved",
		'FBYT',
		/* [167] */
		"'CNTL' resource ID",
		'RSID',
		/* [168] */
		"",
		'KEYE',
		/* [169] */
		"8",
		'KEYB',
		/* [170] */
		"Reserved",
		'BB07',
		/* [171] */
		"Window is object",
		'BB01',
		/* [172] */
		"Item bounds",
		'RECT',
		/* [173] */
		"Other bounds",
		'RECT',
		/* [174] */
		"Reserved",
		'BB07',
		/* [175] */
		"Visible item",
		'BB01',
		/* [176] */
		"Reserved",
		'BB07',
		/* [177] */
		"Enabled item",
		'BB01',
		/* [178] */
		"Reserved",
		'BB07',
		/* [179] */
		"Can hit",
		'BB01',
		/* [180] */
		"Reserved",
		'FBYT',
		/* [181] */
		"Handle placeholder",
		'FLNG',
		/* [182] */
		"Handle placeholder",
		'FLNG',
		/* [183] */
		"",
		'KEYE',
		/* [184] */
		"9",
		'KEYB',
		/* [185] */
		"Reserved",
		'BB07',
		/* [186] */
		"Window is object",
		'BB01',
		/* [187] */
		"Item bounds",
		'RECT',
		/* [188] */
		"Other bounds",
		'RECT',
		/* [189] */
		"Reserved",
		'BB07',
		/* [190] */
		"Visible item",
		'BB01',
		/* [191] */
		"Reserved",
		'BB07',
		/* [192] */
		"Enabled item",
		'BB01',
		/* [193] */
		"Reserved",
		'BB07',
		/* [194] */
		"Can hit",
		'BB01',
		/* [195] */
		"Reserved",
		'FBYT',
		/* [196] */
		"Font resource ID",
		'RSID',
		/* [197] */
		"Font size",
		'DWRD',
		/* [198] */
		"Reserved",
		'FBYT',
		/* [199] */
		"Reserved",
		'FBYT',
		/* [200] */
		"Reserved",
		'FBYT',
		/* [201] */
		"Justification",
		'DBYT',
		/* [202] */
		"Left=0",
		'CASE',
		/* [203] */
		"Right=1",
		'CASE',
		/* [204] */
		"Centered=2",
		'CASE',
		/* [205] */
		"Reserved",
		'FBYT',
		/* [206] */
		"Reserved",
		'FBYT',
		/* [207] */
		"Reserved",
		'FBYT',
		/* [208] */
		"Arrow (ignored)",
		'FBYT',
		/* [209] */
		"Text",
		'PSTR',
		/* [210] */
		"",
		'KEYE',
		/* [211] */
		"10",
		'KEYB',
		/* [212] */
		"Reserved",
		'BB07',
		/* [213] */
		"Window is object",
		'BB01',
		/* [214] */
		"Item bounds",
		'RECT',
		/* [215] */
		"Other bounds",
		'RECT',
		/* [216] */
		"Reserved",
		'BB07',
		/* [217] */
		"Visible item",
		'BB01',
		/* [218] */
		"Reserved",
		'BB07',
		/* [219] */
		"Enabled item",
		'BB01',
		/* [220] */
		"Reserved",
		'BB07',
		/* [221] */
		"Can hit",
		'BB01',
		/* [222] */
		"Reserved",
		'FBYT',
		/* [223] */
		"Font resource ID",
		'RSID',
		/* [224] */
		"Font size",
		'DWRD',
		/* [225] */
		"Next TextEdit item number",
		'DWRD',
		/* [226] */
		"Previous TextEdit item number",
		'DWRD',
		/* [227] */
		"Maximum number of characters",
		'DWRD',
		/* [228] */
		"Type of echo",
		'DBYT',
		/* [229] */
		"Letters=0",
		'CASE',
		/* [230] */
		"Bullets=1",
		'CASE',
		/* [231] */
		"Reserved",
		'FBYT',
		/* [232] */
		"",
		'KEYE',
		/* [233] */
		"11",
		'KEYB',
		/* [234] */
		"Reserved",
		'BB07',
		/* [235] */
		"Window is object",
		'BB01',
		/* [236] */
		"Item bounds",
		'RECT',
		/* [237] */
		"Other bounds",
		'RECT',
		/* [238] */
		"Reserved",
		'BB07',
		/* [239] */
		"Visible item",
		'BB01',
		/* [240] */
		"Reserved",
		'BB07',
		/* [241] */
		"Enabled item",
		'BB01',
		/* [242] */
		"Reserved",
		'BB07',
		/* [243] */
		"Can hit",
		'BB01',
		/* [244] */
		"Reserved",
		'FBYT',
		/* [245] */
		"'PICT' resource ID",
		'RSID',
		/* [246] */
		"",
		'KEYE',
		/* [247] */
		"12",
		'KEYB',
		/* [248] */
		"Reserved",
		'BB07',
		/* [249] */
		"Window is object",
		'BB01',
		/* [250] */
		"Item bounds",
		'RECT',
		/* [251] */
		"Other bounds",
		'RECT',
		/* [252] */
		"Reserved",
		'BB07',
		/* [253] */
		"Visible item",
		'BB01',
		/* [254] */
		"Reserved",
		'BB07',
		/* [255] */
		"Enabled item",
		'BB01',
		/* [256] */
		"Reserved",
		'BB07',
		/* [257] */
		"Can hit",
		'BB01',
		/* [258] */
		"Reserved",
		'FBYT',
		/* [259] */
		"'CNTL' resource ID",
		'RSID',
		/* [260] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1188, "itl0") {
	{	/* array: 110 elements */
		/* [1] */
		"Decimal point separator",
		'CHAR',
		/* [2] */
		"US=.",
		'CASE',
		/* [3] */
		"Europe=,",
		'CASE',
		/* [4] */
		"Thousands separator",
		'CHAR',
		/* [5] */
		"US=,",
		'CASE',
		/* [6] */
		"Europe=.",
		'CASE',
		/* [7] */
		"List separator",
		'CHAR',
		/* [8] */
		"US=;",
		'CASE',
		/* [9] */
		"United Kingdom=,",
		'CASE',
		/* [10] */
		"Currency symbol 1",
		'CHAR',
		/* [11] */
		"US=$",
		'CASE',
		/* [12] */
		"United Kingdom=¬£",
		'CASE',
		/* [13] */
		"France=F",
		'CASE',
		/* [14] */
		"Italy=L",
		'CASE',
		/* [15] */
		"Germany=D",
		'CASE',
		/* [16] */
		"Currency symbol 2",
		'CHAR',
		/* [17] */
		"US= ",
		'CASE',
		/* [18] */
		"France=r",
		'CASE',
		/* [19] */
		"Italy=i",
		'CASE',
		/* [20] */
		"Germany=M",
		'CASE',
		/* [21] */
		"Currency symbol 3",
		'CHAR',
		/* [22] */
		"US= ",
		'CASE',
		/* [23] */
		"Italy or Germany=.",
		'CASE',
		/* [24] */
		"Leading unit zero",
		'BBIT',
		/* [25] */
		"Trailing decimal zero",
		'BBIT',
		/* [26] */
		"Negative repres (On=Minus, Off=Paren)",
		'BBIT',
		/* [27] */
		"Currency symbol trails number",
		'BBIT',
		/* [28] */
		"Reserved",
		'BB04',
		/* [29] */
		"Short date format order",
		'DBYT',
		/* [30] */
		"Month/Day/Year=0",
		'CASE',
		/* [31] */
		"Day/Month/Year=1",
		'CASE',
		/* [32] */
		"Year/Month/Day=2",
		'CASE',
		/* [33] */
		"Month/Year/Day=3",
		'CASE',
		/* [34] */
		"Day/Year/Month=4",
		'CASE',
		/* [35] */
		"Year/Day/Month=5",
		'CASE',
		/* [36] */
		"Include century in short date",
		'BBIT',
		/* [37] */
		"Leading 0 in month in short date",
		'BBIT',
		/* [38] */
		"Leading 0 in day in short date",
		'BBIT',
		/* [39] */
		"Reserved",
		'BB05',
		/* [40] */
		"Separator in short date",
		'CHAR',
		/* [41] */
		"US=/",
		'CASE',
		/* [42] */
		"Italy=-",
		'CASE',
		/* [43] */
		"Japan=.",
		'CASE',
		/* [44] */
		"Time cycle for short date",
		'UBYT',
		/* [45] */
		"Twenty four hour=0",
		'CASE',
		/* [46] */
		"Twelve hour (zero cycle)=1",
		'CASE',
		/* [47] */
		"Twelve hour=255",
		'CASE',
		/* [48] */
		"Leading 0 in hours",
		'BBIT',
		/* [49] */
		"Leading 0 in minutes",
		'BBIT',
		/* [50] */
		"Leading 0 in seconds",
		'BBIT',
		/* [51] */
		"Reserved",
		'BB05',
		/* [52] */
		"Morning string with leading space",
		'T004',
		/* [53] */
		"Evening string with leading space",
		'T004',
		/* [54] */
		"Time separator",
		'CHAR',
		/* [55] */
		"Standard=:",
		'CASE',
		/* [56] */
		"Time 1 stuff",
		'CHAR',
		/* [57] */
		"Time 2 stuff",
		'CHAR',
		/* [58] */
		"Time 3 stuff",
		'CHAR',
		/* [59] */
		"Time 4 stuff",
		'CHAR',
		/* [60] */
		"Time 5 stuff",
		'CHAR',
		/* [61] */
		"Time 6 stuff",
		'CHAR',
		/* [62] */
		"Time 7 stuff",
		'CHAR',
		/* [63] */
		"Time 8 stuff",
		'CHAR',
		/* [64] */
		"Measurement system",
		'UBYT',
		/* [65] */
		"Standard=0",
		'CASE',
		/* [66] */
		"Metric=255",
		'CASE',
		/* [67] */
		"Region code",
		'UBYT',
		/* [68] */
		"United States=0",
		'CASE',
		/* [69] */
		"France=1",
		'CASE',
		/* [70] */
		"Britain=2",
		'CASE',
		/* [71] */
		"Germany=3",
		'CASE',
		/* [72] */
		"Italy=4",
		'CASE',
		/* [73] */
		"Netherlands=5",
		'CASE',
		/* [74] */
		"Belgium/Luxembourg=6",
		'CASE',
		/* [75] */
		"Sweden=7",
		'CASE',
		/* [76] */
		"Spain=8",
		'CASE',
		/* [77] */
		"Denmark=9",
		'CASE',
		/* [78] */
		"Portugal=10",
		'CASE',
		/* [79] */
		"French Canada=11",
		'CASE',
		/* [80] */
		"Norway=12",
		'CASE',
		/* [81] */
		"Israel=13",
		'CASE',
		/* [82] */
		"Japan=14",
		'CASE',
		/* [83] */
		"Australia=15",
		'CASE',
		/* [84] */
		"Arabia=16",
		'CASE',
		/* [85] */
		"Finland=17",
		'CASE',
		/* [86] */
		"French Swiss=18",
		'CASE',
		/* [87] */
		"German Swiss=19",
		'CASE',
		/* [88] */
		"Greece=20",
		'CASE',
		/* [89] */
		"Iceland=21",
		'CASE',
		/* [90] */
		"Malta=22",
		'CASE',
		/* [91] */
		"Cyprus=23",
		'CASE',
		/* [92] */
		"Turkey=24",
		'CASE',
		/* [93] */
		"Yugoslavia=25",
		'CASE',
		/* [94] */
		"India=33",
		'CASE',
		/* [95] */
		"Pakistan=34",
		'CASE',
		/* [96] */
		"Lithuania=41",
		'CASE',
		/* [97] */
		"Poland=42",
		'CASE',
		/* [98] */
		"Hungary=43",
		'CASE',
		/* [99] */
		"Estonia=44",
		'CASE',
		/* [100] */
		"Latvia=45",
		'CASE',
		/* [101] */
		"Lapland=46",
		'CASE',
		/* [102] */
		"Faroe Islands=47",
		'CASE',
		/* [103] */
		"Iran=48",
		'CASE',
		/* [104] */
		"Russia=49",
		'CASE',
		/* [105] */
		"Ireland=50",
		'CASE',
		/* [106] */
		"Korea=51",
		'CASE',
		/* [107] */
		"China=52",
		'CASE',
		/* [108] */
		"Taiwan=53",
		'CASE',
		/* [109] */
		"Thailand=54",
		'CASE',
		/* [110] */
		"Version",
		'DBYT'
	}
};

resource 'TMPL' (1189, "itl1") {
	{	/* array: 131 elements */
		/* [1] */
		"Day 1",
		'P010',
		/* [2] */
		"Day 2",
		'P010',
		/* [3] */
		"Day 3",
		'P010',
		/* [4] */
		"Day 4",
		'P010',
		/* [5] */
		"Day 5",
		'P010',
		/* [6] */
		"Day 6",
		'P010',
		/* [7] */
		"Day 7",
		'P010',
		/* [8] */
		"Month 1",
		'P010',
		/* [9] */
		"Month 2",
		'P010',
		/* [10] */
		"Month 3",
		'P010',
		/* [11] */
		"Month 4",
		'P010',
		/* [12] */
		"Month 5",
		'P010',
		/* [13] */
		"Month 6",
		'P010',
		/* [14] */
		"Month 7",
		'P010',
		/* [15] */
		"Month 8",
		'P010',
		/* [16] */
		"Month 9",
		'P010',
		/* [17] */
		"Month 10",
		'P010',
		/* [18] */
		"Month 11",
		'P010',
		/* [19] */
		"Month 12",
		'P010',
		/* [20] */
		"Day name",
		'UBYT',
		/* [21] */
		"Has it=0",
		'CASE',
		/* [22] */
		"Suppress it=255",
		'CASE',
		/* [23] */
		"Long date format",
		'HBYT',
		/* [24] */
		"Day/Month/Year=$00",
		'CASE',
		/* [25] */
		"Month/Day/Year=$FF",
		'CASE',
		/* [26] */
		"Day has leading 0",
		'UBYT',
		/* [27] */
		"No=0",
		'CASE',
		/* [28] */
		"Yes=255",
		'CASE',
		/* [29] */
		"Abbreviation length",
		'UBYT',
		/* [30] */
		"String 0 separating 1st element",
		'T004',
		/* [31] */
		"String 1 separating 1st and 2nd",
		'T004',
		/* [32] */
		"String 2 separating 2nd and 3rd",
		'T004',
		/* [33] */
		"String 3 separating 3rd and 4th",
		'T004',
		/* [34] */
		"String 4 following 4th element",
		'T004',
		/* [35] */
		"Region code",
		'UBYT',
		/* [36] */
		"United States=0",
		'CASE',
		/* [37] */
		"France=1",
		'CASE',
		/* [38] */
		"Britain=2",
		'CASE',
		/* [39] */
		"Germany=3",
		'CASE',
		/* [40] */
		"Italy=4",
		'CASE',
		/* [41] */
		"Netherlands=5",
		'CASE',
		/* [42] */
		"Belgium/Luxembourg=6",
		'CASE',
		/* [43] */
		"Sweden=7",
		'CASE',
		/* [44] */
		"Spain=8",
		'CASE',
		/* [45] */
		"Denmark=9",
		'CASE',
		/* [46] */
		"Portugal=10",
		'CASE',
		/* [47] */
		"French Canada=11",
		'CASE',
		/* [48] */
		"Norway=12",
		'CASE',
		/* [49] */
		"Israel=13",
		'CASE',
		/* [50] */
		"Japan=14",
		'CASE',
		/* [51] */
		"Australia=15",
		'CASE',
		/* [52] */
		"Arabia=16",
		'CASE',
		/* [53] */
		"Finland=17",
		'CASE',
		/* [54] */
		"French Swiss=18",
		'CASE',
		/* [55] */
		"German Swiss=19",
		'CASE',
		/* [56] */
		"Greece=20",
		'CASE',
		/* [57] */
		"Iceland=21",
		'CASE',
		/* [58] */
		"Malta=22",
		'CASE',
		/* [59] */
		"Cyprus=23",
		'CASE',
		/* [60] */
		"Turkey=24",
		'CASE',
		/* [61] */
		"Yugoslavia=25",
		'CASE',
		/* [62] */
		"India=33",
		'CASE',
		/* [63] */
		"Pakistan=34",
		'CASE',
		/* [64] */
		"Lithuania=41",
		'CASE',
		/* [65] */
		"Poland=42",
		'CASE',
		/* [66] */
		"Hungary=43",
		'CASE',
		/* [67] */
		"Estonia=44",
		'CASE',
		/* [68] */
		"Latvia=45",
		'CASE',
		/* [69] */
		"Lapland=46",
		'CASE',
		/* [70] */
		"Faroe Islands=47",
		'CASE',
		/* [71] */
		"Iran=48",
		'CASE',
		/* [72] */
		"Russia=49",
		'CASE',
		/* [73] */
		"Ireland=50",
		'CASE',
		/* [74] */
		"Korea=51",
		'CASE',
		/* [75] */
		"China=52",
		'CASE',
		/* [76] */
		"Taiwan=53",
		'CASE',
		/* [77] */
		"Thailand=54",
		'CASE',
		/* [78] */
		"Version",
		'UBYT',
		/* [79] */
		"First instruction of obsolete sorting ro"
		"utine",
		'KHWD',
		/* [80] */
		"Unextended long-date format=$4E75",
		'CASE',
		/* [81] */
		"Extended long-date format=$A89F",
		'CASE',
		/* [82] */
		"$4E75",
		'KEYB',
		/* [83] */
		"",
		'KEYE',
		/* [84] */
		"$A89F",
		'KEYB',
		/* [85] */
		"Version",
		'HWRD',
		/* [86] */
		"Format",
		'DWRD',
		/* [87] */
		"Original=0",
		'CASE',
		/* [88] */
		"Calendar code",
		'DWRD',
		/* [89] */
		"Gregorian=0",
		'CASE',
		/* [90] */
		"Arabic civil=1",
		'CASE',
		/* [91] */
		"Arabic lunar=2",
		'CASE',
		/* [92] */
		"Japanese=3",
		'CASE',
		/* [93] */
		"Jewish=4",
		'CASE',
		/* [94] */
		"Coptic=5",
		'CASE',
		/* [95] */
		"Persian=6",
		'CASE',
		/* [96] */
		"Offset of Extra Days table",
		'FLNG',
		/* [97] */
		"Length of Extra Days table",
		'FLNG',
		/* [98] */
		"Offset of Extra Months table",
		'FLNG',
		/* [99] */
		"Length of Extra Months table",
		'FLNG',
		/* [100] */
		"Offset to Day Abbrev table",
		'FLNG',
		/* [101] */
		"Length of Day Abbrev table",
		'FLNG',
		/* [102] */
		"Offset to Month Abbrev table",
		'FLNG',
		/* [103] */
		"Length of Month Abbrev table",
		'FLNG',
		/* [104] */
		"Offset to Extra Sep table",
		'FLNG',
		/* [105] */
		"Length of Extra Sep table",
		'FLNG',
		/* [106] */
		"Count:",
		'OCNT',
		/* [107] */
		"Extra days",
		'LSTC',
		/* [108] */
		"Day name",
		'PSTR',
		/* [109] */
		"*****",
		'LSTE',
		/* [110] */
		"Align",
		'AWRD',
		/* [111] */
		"Count:",
		'OCNT',
		/* [112] */
		"Extra months",
		'LSTC',
		/* [113] */
		"Month name",
		'PSTR',
		/* [114] */
		"*****",
		'LSTE',
		/* [115] */
		"Align",
		'AWRD',
		/* [116] */
		"Count:",
		'OCNT',
		/* [117] */
		"Day abbreviations",
		'LSTC',
		/* [118] */
		"Day abbrev.",
		'PSTR',
		/* [119] */
		"*****",
		'LSTE',
		/* [120] */
		"Align",
		'AWRD',
		/* [121] */
		"Count:",
		'OCNT',
		/* [122] */
		"Month abbreviations",
		'LSTC',
		/* [123] */
		"Month abbrev.",
		'PSTR',
		/* [124] */
		"*****",
		'LSTE',
		/* [125] */
		"Align",
		'AWRD',
		/* [126] */
		"Count:",
		'OCNT',
		/* [127] */
		"Extra separators",
		'LSTC',
		/* [128] */
		"Separator",
		'PSTR',
		/* [129] */
		"*****",
		'LSTE',
		/* [130] */
		"Align",
		'AWRD',
		/* [131] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1190, "ITL1") {
	{	/* array: 1 elements */
		/* [1] */
		"Use short dates before system",
		'HWRD'
	}
};

resource 'TMPL' (1191, "itl2") {
	{	/* array: 43 elements */
		/* [1] */
		"Init hook offset",
		'HWRD',
		/* [2] */
		"Fetch hook offset",
		'HWRD',
		/* [3] */
		"Vernier hook offset",
		'HWRD',
		/* [4] */
		"Project hook offset",
		'HWRD',
		/* [5] */
		"Version",
		'HWRD',
		/* [6] */
		"New formats=$FFFF",
		'CASE',
		/* [7] */
		"Exit hook offset",
		'HWRD',
		/* [8] */
		"Type list offset",
		'HWRD',
		/* [9] */
		"Class array offset",
		'HWRD',
		/* [10] */
		"Uppercase list offset",
		'HWRD',
		/* [11] */
		"Lowercase list offset",
		'HWRD',
		/* [12] */
		"Uppercase strip list offset",
		'HWRD',
		/* [13] */
		"Word selection table offset",
		'HWRD',
		/* [14] */
		"Line break table offset",
		'HWRD',
		/* [15] */
		"Offset to strip list",
		'HWRD',
		/* [16] */
		"Version",
		'HWRD',
		/* [17] */
		"Format code",
		'KWRD',
		/* [18] */
		"Extended format (System 7)=1",
		'CASE',
		/* [19] */
		"Old format (6.0.4)=0",
		'CASE',
		/* [20] */
		"1",
		'KEYB',
		/* [21] */
		"Length of init hook",
		'DWRD',
		/* [22] */
		"Length of fetch hook",
		'DWRD',
		/* [23] */
		"Length of vernier hook",
		'DWRD',
		/* [24] */
		"Length of project hook",
		'DWRD',
		/* [25] */
		"Reserved",
		'FWRD',
		/* [26] */
		"Length of exit hook",
		'DWRD',
		/* [27] */
		"Length of type list",
		'DWRD',
		/* [28] */
		"Length of class array",
		'DWRD',
		/* [29] */
		"Length of uppercase list",
		'DWRD',
		/* [30] */
		"Length of lowercase list",
		'DWRD',
		/* [31] */
		"Length of uppercase strip list",
		'DWRD',
		/* [32] */
		"Length of word-selection table",
		'DWRD',
		/* [33] */
		"Length of line-break table",
		'DWRD',
		/* [34] */
		"Length of strip list",
		'DWRD',
		/* [35] */
		"Extra tables",
		'DVDR',
		/* [36] */
		"Offset to script run table",
		'DWRD',
		/* [37] */
		"Missing=0",
		'CASE',
		/* [38] */
		"Length of script run table",
		'DWRD',
		/* [39] */
		"Missing=0",
		'CASE',
		/* [40] */
		"",
		'KEYE',
		/* [41] */
		"0",
		'KEYB',
		/* [42] */
		"",
		'KEYE',
		/* [43] */
		"The rest",
		'HEXD'
	}
};

resource 'TMPL' (1192, "itl4") {
	{	/* array: 37 elements */
		/* [1] */
		"Flags",
		'HWRD',
		/* [2] */
		"Resource type",
		'TNAM',
		/* [3] */
		"Standard=itl4",
		'CASE',
		/* [4] */
		"This token's resource ID",
		'RSID',
		/* [5] */
		"Version",
		'HWRD',
		/* [6] */
		"Format code",
		'DWRD',
		/* [7] */
		"Reserved",
		'FWRD',
		/* [8] */
		"Reserved",
		'FLNG',
		/* [9] */
		"Number of tables",
		'DWRD',
		/* [10] */
		"Standard=8",
		'CASE',
		/* [11] */
		"Offset to token table",
		'DLNG',
		/* [12] */
		"Offset to string copy routine",
		'DLNG',
		/* [13] */
		"Offset to external fetch routine",
		'DLNG',
		/* [14] */
		"Offset to untoken table",
		'DLNG',
		/* [15] */
		"Offset to number parts table",
		'DLNG',
		/* [16] */
		"Offset to whitespace table",
		'DLNG',
		/* [17] */
		"Reserved offset",
		'FLNG',
		/* [18] */
		"Reserved offset",
		'FLNG',
		/* [19] */
		"Reserved length",
		'FWRD',
		/* [20] */
		"Reserved length",
		'FWRD',
		/* [21] */
		"Reserved length",
		'FWRD',
		/* [22] */
		"Length of untoken table",
		'DWRD',
		/* [23] */
		"Length of number parts table",
		'DWRD',
		/* [24] */
		"Length of whitespace table",
		'DWRD',
		/* [25] */
		"Reserved length",
		'FWRD',
		/* [26] */
		"Reserved length",
		'FWRD',
		/* [27] */
		"Character to token mapping table",
		'DVDR',
		/* [28] */
		"256 chars (fixed count)",
		'FCNT',
		/* [29] */
		"List of 256 characters",
		'LSTC',
		/* [30] */
		"Token type",
		'DBYT',
		/* [31] */
		"Unknown=0",
		'CASE',
		/* [32] */
		"Whitespace=1",
		'CASE',
		/* [33] */
		"Alphabetic=4",
		'CASE',
		/* [34] */
		"Numeric=5",
		'CASE',
		/* [35] */
		"Newline=6",
		'CASE',
		/* [36] */
		"*****",
		'LSTE',
		/* [37] */
		"More tables",
		'HEXD'
	}
};

resource 'TMPL' (1193, "itlb") {
	{	/* array: 68 elements */
		/* [1] */
		"'itl0' (Numbers) resource ID",
		'RSID',
		/* [2] */
		"'itl1' (Dates) resource ID",
		'RSID',
		/* [3] */
		"'itl2' (Sorting) resource ID",
		'RSID',
		/* [4] */
		"Reverse right-to-left text when drawing",
		'WBIT',
		/* [5] */
		"Use contextual ligatures",
		'WBIT',
		/* [6] */
		"Use contextual forms",
		'WBIT',
		/* [7] */
		"Reserved",
		'WB04',
		/* [8] */
		"Synchronize keyboard with monostyled Tex"
		"tEdit font",
		'WBIT',
		/* [9] */
		"Uses the WorldScript I extension",
		'WBIT',
		/* [10] */
		"Let Script Manager initialize",
		'WBIT',
		/* [11] */
		"Has alternate digits at $B0",
		'WBIT',
		/* [12] */
		"Doesn't support font forcing",
		'WBIT',
		/* [13] */
		"Is contextual",
		'WBIT',
		/* [14] */
		"Has both upper and lowercase native char"
		"s",
		'WBIT',
		/* [15] */
		"Has only 1-byte chars",
		'WBIT',
		/* [16] */
		"Supports intelligent cut and paste",
		'WBIT',
		/* [17] */
		"'itl4' resource ID",
		'RSID',
		/* [18] */
		"'itl5' resource ID",
		'RSID',
		/* [19] */
		"Not present=0",
		'CASE',
		/* [20] */
		"Language code for script",
		'LNGC',
		/* [21] */
		"Number representation code",
		'DBYT',
		/* [22] */
		"Western=0",
		'CASE',
		/* [23] */
		"Arabic=1",
		'CASE',
		/* [24] */
		"Roman=2",
		'CASE',
		/* [25] */
		"Japanese=3",
		'CASE',
		/* [26] */
		"European=4",
		'CASE',
		/* [27] */
		"Date representation code",
		'DBYT',
		/* [28] */
		"Gregorian=0",
		'CASE',
		/* [29] */
		"Arabic Civil=1",
		'CASE',
		/* [30] */
		"Arabic Lunar=2",
		'CASE',
		/* [31] */
		"Japanese=3",
		'CASE',
		/* [32] */
		"Jewish=4",
		'CASE',
		/* [33] */
		"Coptic=5",
		'CASE',
		/* [34] */
		"Persian=6",
		'CASE',
		/* [35] */
		"'KCHR' (Virtual Key-->Char) resource ID",
		'RSID',
		/* [36] */
		"'kcs8' icon family resource ID",
		'RSID',
		/* [37] */
		"Extended bundle record for font and styl"
		"e information",
		'DVDR',
		/* [38] */
		"Size of script's local record",
		'DLNG',
		/* [39] */
		"Default monospace 'FOND' resource ID",
		'RSID',
		/* [40] */
		"Default monospace font size",
		'DWRD',
		/* [41] */
		"Preferred 'FOND' resource ID",
		'RSID',
		/* [42] */
		"Preferred font size",
		'DWRD',
		/* [43] */
		"Default small 'FOND' resource ID",
		'RSID',
		/* [44] */
		"Default small font size",
		'DWRD',
		/* [45] */
		"Default system 'FOND' resource ID",
		'RSID',
		/* [46] */
		"Default system font size",
		'DWRD',
		/* [47] */
		"Default application 'FOND' resource ID",
		'RSID',
		/* [48] */
		"Default application font size",
		'DWRD',
		/* [49] */
		"Default Help Manager 'FOND' resource ID",
		'RSID',
		/* [50] */
		"Default Help Manager font size",
		'DWRD',
		/* [51] */
		"Valid styles",
		'BORV',
		/* [52] */
		"Plain=0",
		'CASE',
		/* [53] */
		"Bold=1",
		'CASE',
		/* [54] */
		"Italic=2",
		'CASE',
		/* [55] */
		"Underline=4",
		'CASE',
		/* [56] */
		"Outline=8",
		'CASE',
		/* [57] */
		"Shadow=16",
		'CASE',
		/* [58] */
		"Condensed=32",
		'CASE',
		/* [59] */
		"Extended=64",
		'CASE',
		/* [60] */
		"Alias styles",
		'BORV',
		/* [61] */
		"Plain=0",
		'CASE',
		/* [62] */
		"Bold=1",
		'CASE',
		/* [63] */
		"Italic=2",
		'CASE',
		/* [64] */
		"Underline=4",
		'CASE',
		/* [65] */
		"Outline=8",
		'CASE',
		/* [66] */
		"Shadow=16",
		'CASE',
		/* [67] */
		"Condensed=32",
		'CASE',
		/* [68] */
		"Extended=64",
		'CASE'
	}
};

resource 'TMPL' (1194, "itlc") {
	{	/* array: 24 elements */
		/* [1] */
		"System script code",
		'SCPC',
		/* [2] */
		"Keyboard cache size",
		'UWRD',
		/* [3] */
		"Font force flag",
		'HBYT',
		/* [4] */
		"Roman fonts belong to script=$FF",
		'CASE',
		/* [5] */
		"No font force=$00",
		'CASE',
		/* [6] */
		"International force flag",
		'HBYT',
		/* [7] */
		"Intl force=$FF",
		'CASE',
		/* [8] */
		"No intl force=$00",
		'CASE',
		/* [9] */
		"Old keyboard (Mac Plus)",
		'HBYT',
		/* [10] */
		"No old keyboard=$00",
		'CASE',
		/* [11] */
		"Old keyboard=$FF",
		'CASE',
		/* [12] */
		"Always show keyboard icon",
		'BBIT',
		/* [13] */
		"Use dual caret for mixed directional tex"
		"t",
		'BBIT',
		/* [14] */
		"Name tag enabled (internal use only)",
		'BBIT',
		/* [15] */
		"Reserved",
		'BB05',
		/* [16] */
		"Script icon offset",
		'DWRD',
		/* [17] */
		"Menu side for offset",
		'HBYT',
		/* [18] */
		"Right side=$00",
		'CASE',
		/* [19] */
		"Left side=$FF",
		'CASE',
		/* [20] */
		"Reserved (icon data)",
		'FBYT',
		/* [21] */
		"Preferred region code",
		'RGNC',
		/* [22] */
		"Initial sys dir (LTR=Off,RTL=On)",
		'WBIT',
		/* [23] */
		"Reserved",
		'WB15',
		/* [24] */
		"Reserved",
		'F020'
	}
};

resource 'TMPL' (1195, "itlk") {
	{	/* array: 10 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"Entries of key-remap resource",
		'LSTC',
		/* [3] */
		"Keyboard type",
		'DWRD',
		/* [4] */
		"Current modifiers",
		'HBYT',
		/* [5] */
		"Current key code",
		'DBYT',
		/* [6] */
		"Modifiers mask",
		'HBYT',
		/* [7] */
		"Keycode mask",
		'DBYT',
		/* [8] */
		"New modifiers",
		'HBYT',
		/* [9] */
		"New key code",
		'DBYT',
		/* [10] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1196, "ITML") {
	{	/* array: 4 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"List of Items",
		'LSTC',
		/* [3] */
		"'ITEM' resource ID",
		'RSID',
		/* [4] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1197, "JPob") {
	{	/* array: 378 elements */
		/* [1] */
		"Version Number",
		'DWRD',
		/* [2] */
		"CW10=1",
		'CASE',
		/* [3] */
		"List of objects",
		'LSTB',
		/* [4] */
		"Object type",
		'KTYP',
		/* [5] */
		"Object data=objd",
		'CASE',
		/* [6] */
		"Begin sub-object list=begs",
		'CASE',
		/* [7] */
		"End sub-object list=ends",
		'CASE',
		/* [8] */
		"Comment=comm",
		'CASE',
		/* [9] */
		"End of list=end.",
		'CASE',
		/* [10] */
		"objd",
		'KEYB',
		/* [11] */
		"Runtime class name",
		'PSTR',
		/* [12] */
		"Number of bytes in following data",
		'LSIZ',
		/* [13] */
		"Data type",
		'KTYP',
		/* [14] */
		"Component=comp",
		'CASE',
		/* [15] */
		"Container=cont",
		'CASE',
		/* [16] */
		"Panel=panl",
		'CASE',
		/* [17] */
		"Window=wind",
		'CASE',
		/* [18] */
		"Frame=fram",
		'CASE',
		/* [19] */
		"Dialog=dlog",
		'CASE',
		/* [20] */
		"File dialog=fdlg",
		'CASE',
		/* [21] */
		"Button=butn",
		'CASE',
		/* [22] */
		"List=list",
		'CASE',
		/* [23] */
		"Choice=choi",
		'CASE',
		/* [24] */
		"Scrollbar=scrl",
		'CASE',
		/* [25] */
		"Checkbox=chex",
		'CASE',
		/* [26] */
		"Canvas=canv",
		'CASE',
		/* [27] */
		"Label=labl",
		'CASE',
		/* [28] */
		"Text component=tcmp",
		'CASE',
		/* [29] */
		"Text field=tfld",
		'CASE',
		/* [30] */
		"Text area=taea",
		'CASE',
		/* [31] */
		"Null=null",
		'CASE',
		/* [32] */
		"comp",
		'KEYB',
		/* [33] */
		"Component data",
		'DVDR',
		/* [34] */
		"Component name",
		'PSTR',
		/* [35] */
		"Left origin",
		'DLNG',
		/* [36] */
		"Top origin",
		'DLNG',
		/* [37] */
		"Width",
		'DLNG',
		/* [38] */
		"Height",
		'DLNG',
		/* [39] */
		"Foreground color",
		'COLR',
		/* [40] */
		"Background color",
		'COLR',
		/* [41] */
		"Font name",
		'PSTR',
		/* [42] */
		"Font size",
		'DLNG',
		/* [43] */
		"Font style",
		'DLNG',
		/* [44] */
		"Visible",
		'BFLG',
		/* [45] */
		"Enabled",
		'BFLG',
		/* [46] */
		"",
		'KEYE',
		/* [47] */
		"cont",
		'KEYB',
		/* [48] */
		"Component data",
		'DVDR',
		/* [49] */
		"Component name",
		'PSTR',
		/* [50] */
		"Left origin",
		'DLNG',
		/* [51] */
		"Top origin",
		'DLNG',
		/* [52] */
		"Width",
		'DLNG',
		/* [53] */
		"Height",
		'DLNG',
		/* [54] */
		"Foreground color",
		'COLR',
		/* [55] */
		"Background color",
		'COLR',
		/* [56] */
		"Font name",
		'PSTR',
		/* [57] */
		"Font size",
		'DLNG',
		/* [58] */
		"Font style",
		'DLNG',
		/* [59] */
		"Visible",
		'BFLG',
		/* [60] */
		"Enabled",
		'BFLG',
		/* [61] */
		"Container data",
		'DVDR',
		/* [62] */
		"Layout manager class name",
		'PSTR',
		/* [63] */
		"",
		'KEYE',
		/* [64] */
		"panl",
		'KEYB',
		/* [65] */
		"Component data",
		'DVDR',
		/* [66] */
		"Component name",
		'PSTR',
		/* [67] */
		"Left origin",
		'DLNG',
		/* [68] */
		"Top origin",
		'DLNG',
		/* [69] */
		"Width",
		'DLNG',
		/* [70] */
		"Height",
		'DLNG',
		/* [71] */
		"Foreground color",
		'COLR',
		/* [72] */
		"Background color",
		'COLR',
		/* [73] */
		"Font name",
		'PSTR',
		/* [74] */
		"Font size",
		'DLNG',
		/* [75] */
		"Font style",
		'DLNG',
		/* [76] */
		"Visible",
		'BFLG',
		/* [77] */
		"Enabled",
		'BFLG',
		/* [78] */
		"Container data",
		'DVDR',
		/* [79] */
		"Layout manager class name",
		'PSTR',
		/* [80] */
		"",
		'KEYE',
		/* [81] */
		"wind",
		'KEYB',
		/* [82] */
		"Component data",
		'DVDR',
		/* [83] */
		"Component name",
		'PSTR',
		/* [84] */
		"Left origin",
		'DLNG',
		/* [85] */
		"Top origin",
		'DLNG',
		/* [86] */
		"Width",
		'DLNG',
		/* [87] */
		"Height",
		'DLNG',
		/* [88] */
		"Foreground color",
		'COLR',
		/* [89] */
		"Background color",
		'COLR',
		/* [90] */
		"Font name",
		'PSTR',
		/* [91] */
		"Font size",
		'DLNG',
		/* [92] */
		"Font style",
		'DLNG',
		/* [93] */
		"Visible",
		'BFLG',
		/* [94] */
		"Enabled",
		'BFLG',
		/* [95] */
		"Container data",
		'DVDR',
		/* [96] */
		"Layout manager class name",
		'PSTR',
		/* [97] */
		"",
		'KEYE',
		/* [98] */
		"fram",
		'KEYB',
		/* [99] */
		"Component data",
		'DVDR',
		/* [100] */
		"Component name",
		'PSTR',
		/* [101] */
		"Left origin",
		'DLNG',
		/* [102] */
		"Top origin",
		'DLNG',
		/* [103] */
		"Width",
		'DLNG',
		/* [104] */
		"Height",
		'DLNG',
		/* [105] */
		"Foreground color",
		'COLR',
		/* [106] */
		"Background color",
		'COLR',
		/* [107] */
		"Font name",
		'PSTR',
		/* [108] */
		"Font size",
		'DLNG',
		/* [109] */
		"Font style",
		'DLNG',
		/* [110] */
		"Visible",
		'BFLG',
		/* [111] */
		"Enabled",
		'BFLG',
		/* [112] */
		"Container data",
		'DVDR',
		/* [113] */
		"Layout manager class name",
		'PSTR',
		/* [114] */
		"Frame data",
		'DVDR',
		/* [115] */
		"Title",
		'PSTR',
		/* [116] */
		"Menu bar",
		'PSTR',
		/* [117] */
		"Resizable",
		'BFLG',
		/* [118] */
		"Cursor type",
		'DLNG',
		/* [119] */
		"",
		'KEYE',
		/* [120] */
		"dlog",
		'KEYB',
		/* [121] */
		"Component data",
		'DVDR',
		/* [122] */
		"Component name",
		'PSTR',
		/* [123] */
		"Left origin",
		'DLNG',
		/* [124] */
		"Top origin",
		'DLNG',
		/* [125] */
		"Width",
		'DLNG',
		/* [126] */
		"Height",
		'DLNG',
		/* [127] */
		"Foreground color",
		'COLR',
		/* [128] */
		"Background color",
		'COLR',
		/* [129] */
		"Font name",
		'PSTR',
		/* [130] */
		"Font size",
		'DLNG',
		/* [131] */
		"Font style",
		'DLNG',
		/* [132] */
		"Visible",
		'BFLG',
		/* [133] */
		"Enabled",
		'BFLG',
		/* [134] */
		"Container data",
		'DVDR',
		/* [135] */
		"Layout manager class name",
		'PSTR',
		/* [136] */
		"Dialog data",
		'DVDR',
		/* [137] */
		"Resizable",
		'BFLG',
		/* [138] */
		"Modal",
		'BFLG',
		/* [139] */
		"Title",
		'PSTR',
		/* [140] */
		"",
		'KEYE',
		/* [141] */
		"fdlg",
		'KEYB',
		/* [142] */
		"Component data",
		'DVDR',
		/* [143] */
		"Component name",
		'PSTR',
		/* [144] */
		"Left origin",
		'DLNG',
		/* [145] */
		"Top origin",
		'DLNG',
		/* [146] */
		"Width",
		'DLNG',
		/* [147] */
		"Height",
		'DLNG',
		/* [148] */
		"Foreground color",
		'COLR',
		/* [149] */
		"Background color",
		'COLR',
		/* [150] */
		"Font name",
		'PSTR',
		/* [151] */
		"Font size",
		'DLNG',
		/* [152] */
		"Font style",
		'DLNG',
		/* [153] */
		"Visible",
		'BFLG',
		/* [154] */
		"Enabled",
		'BFLG',
		/* [155] */
		"Container data",
		'DVDR',
		/* [156] */
		"Layout manager class name",
		'PSTR',
		/* [157] */
		"Dialog data",
		'DVDR',
		/* [158] */
		"Resizable",
		'BFLG',
		/* [159] */
		"Modal",
		'BFLG',
		/* [160] */
		"Title",
		'PSTR',
		/* [161] */
		"File dialog data",
		'DVDR',
		/* [162] */
		"Mode (load/save)",
		'DLNG',
		/* [163] */
		"Directory",
		'PSTR',
		/* [164] */
		"File",
		'PSTR',
		/* [165] */
		"Filename filter",
		'PSTR',
		/* [166] */
		"",
		'KEYE',
		/* [167] */
		"butn",
		'KEYB',
		/* [168] */
		"Component data",
		'DVDR',
		/* [169] */
		"Component name",
		'PSTR',
		/* [170] */
		"Left origin",
		'DLNG',
		/* [171] */
		"Top origin",
		'DLNG',
		/* [172] */
		"Width",
		'DLNG',
		/* [173] */
		"Height",
		'DLNG',
		/* [174] */
		"Foreground color",
		'COLR',
		/* [175] */
		"Background color",
		'COLR',
		/* [176] */
		"Font name",
		'PSTR',
		/* [177] */
		"Font size",
		'DLNG',
		/* [178] */
		"Font style",
		'DLNG',
		/* [179] */
		"Visible",
		'BFLG',
		/* [180] */
		"Enabled",
		'BFLG',
		/* [181] */
		"Button data",
		'DVDR',
		/* [182] */
		"Label",
		'PSTR',
		/* [183] */
		"",
		'KEYE',
		/* [184] */
		"list",
		'KEYB',
		/* [185] */
		"Component data",
		'DVDR',
		/* [186] */
		"Component name",
		'PSTR',
		/* [187] */
		"Left origin",
		'DLNG',
		/* [188] */
		"Top origin",
		'DLNG',
		/* [189] */
		"Width",
		'DLNG',
		/* [190] */
		"Height",
		'DLNG',
		/* [191] */
		"Foreground color",
		'COLR',
		/* [192] */
		"Background color",
		'COLR',
		/* [193] */
		"Font name",
		'PSTR',
		/* [194] */
		"Font size",
		'DLNG',
		/* [195] */
		"Font style",
		'DLNG',
		/* [196] */
		"Visible",
		'BFLG',
		/* [197] */
		"Enabled",
		'BFLG',
		/* [198] */
		"List data",
		'DVDR',
		/* [199] */
		"Initial items",
		'OCNT',
		/* [200] */
		"",
		'LSTC',
		/* [201] */
		"Text",
		'PSTR',
		/* [202] */
		"",
		'LSTE',
		/* [203] */
		"Multiple selection allowed?",
		'BFLG',
		/* [204] */
		"Visible index",
		'DWRD',
		/* [205] */
		"",
		'KEYE',
		/* [206] */
		"choi",
		'KEYB',
		/* [207] */
		"Component data",
		'DVDR',
		/* [208] */
		"Component name",
		'PSTR',
		/* [209] */
		"Left origin",
		'DLNG',
		/* [210] */
		"Top origin",
		'DLNG',
		/* [211] */
		"Width",
		'DLNG',
		/* [212] */
		"Height",
		'DLNG',
		/* [213] */
		"Foreground color",
		'COLR',
		/* [214] */
		"Background color",
		'COLR',
		/* [215] */
		"Font name",
		'PSTR',
		/* [216] */
		"Font size",
		'DLNG',
		/* [217] */
		"Font style",
		'DLNG',
		/* [218] */
		"Visible",
		'BFLG',
		/* [219] */
		"Enabled",
		'BFLG',
		/* [220] */
		"Choice data",
		'DVDR',
		/* [221] */
		"Initial items",
		'OCNT',
		/* [222] */
		"",
		'LSTC',
		/* [223] */
		"Text",
		'PSTR',
		/* [224] */
		"",
		'LSTE',
		/* [225] */
		"Selected index",
		'DWRD',
		/* [226] */
		"",
		'KEYE',
		/* [227] */
		"scrl",
		'KEYB',
		/* [228] */
		"Component data",
		'DVDR',
		/* [229] */
		"Component name",
		'PSTR',
		/* [230] */
		"Left origin",
		'DLNG',
		/* [231] */
		"Top origin",
		'DLNG',
		/* [232] */
		"Width",
		'DLNG',
		/* [233] */
		"Height",
		'DLNG',
		/* [234] */
		"Foreground color",
		'COLR',
		/* [235] */
		"Background color",
		'COLR',
		/* [236] */
		"Font name",
		'PSTR',
		/* [237] */
		"Font size",
		'DLNG',
		/* [238] */
		"Font style",
		'DLNG',
		/* [239] */
		"Visible",
		'BFLG',
		/* [240] */
		"Enabled",
		'BFLG',
		/* [241] */
		"Scrollbar data",
		'DVDR',
		/* [242] */
		"Value",
		'DLNG',
		/* [243] */
		"Maximum value",
		'DLNG',
		/* [244] */
		"Minimum value",
		'DLNG',
		/* [245] */
		"Visible percent",
		'DLNG',
		/* [246] */
		"Orientation",
		'DLNG',
		/* [247] */
		"Line increment",
		'DLNG',
		/* [248] */
		"Page increment",
		'DLNG',
		/* [249] */
		"",
		'KEYE',
		/* [250] */
		"chex",
		'KEYB',
		/* [251] */
		"Component data",
		'DVDR',
		/* [252] */
		"Component name",
		'PSTR',
		/* [253] */
		"Left origin",
		'DLNG',
		/* [254] */
		"Top origin",
		'DLNG',
		/* [255] */
		"Width",
		'DLNG',
		/* [256] */
		"Height",
		'DLNG',
		/* [257] */
		"Foreground color",
		'COLR',
		/* [258] */
		"Background color",
		'COLR',
		/* [259] */
		"Font name",
		'PSTR',
		/* [260] */
		"Font size",
		'DLNG',
		/* [261] */
		"Font style",
		'DLNG',
		/* [262] */
		"Visible",
		'BFLG',
		/* [263] */
		"Enabled",
		'BFLG',
		/* [264] */
		"Checkbox data",
		'DVDR',
		/* [265] */
		"Label",
		'PSTR',
		/* [266] */
		"State",
		'BFLG',
		/* [267] */
		"",
		'KEYE',
		/* [268] */
		"canv",
		'KEYB',
		/* [269] */
		"Component data",
		'DVDR',
		/* [270] */
		"Component name",
		'PSTR',
		/* [271] */
		"Left origin",
		'DLNG',
		/* [272] */
		"Top origin",
		'DLNG',
		/* [273] */
		"Width",
		'DLNG',
		/* [274] */
		"Height",
		'DLNG',
		/* [275] */
		"Foreground color",
		'COLR',
		/* [276] */
		"Background color",
		'COLR',
		/* [277] */
		"Font name",
		'PSTR',
		/* [278] */
		"Font size",
		'DLNG',
		/* [279] */
		"Font style",
		'DLNG',
		/* [280] */
		"Visible",
		'BFLG',
		/* [281] */
		"Enabled",
		'BFLG',
		/* [282] */
		"",
		'KEYE',
		/* [283] */
		"labl",
		'KEYB',
		/* [284] */
		"Component data",
		'DVDR',
		/* [285] */
		"Component name",
		'PSTR',
		/* [286] */
		"Left origin",
		'DLNG',
		/* [287] */
		"Top origin",
		'DLNG',
		/* [288] */
		"Width",
		'DLNG',
		/* [289] */
		"Height",
		'DLNG',
		/* [290] */
		"Foreground color",
		'COLR',
		/* [291] */
		"Background color",
		'COLR',
		/* [292] */
		"Font name",
		'PSTR',
		/* [293] */
		"Font size",
		'DLNG',
		/* [294] */
		"Font style",
		'DLNG',
		/* [295] */
		"Visible",
		'BFLG',
		/* [296] */
		"Enabled",
		'BFLG',
		/* [297] */
		"Label data",
		'DVDR',
		/* [298] */
		"String",
		'PSTR',
		/* [299] */
		"Alignment",
		'DLNG',
		/* [300] */
		"",
		'KEYE',
		/* [301] */
		"tcmp",
		'KEYB',
		/* [302] */
		"Component data",
		'DVDR',
		/* [303] */
		"Component name",
		'PSTR',
		/* [304] */
		"Left origin",
		'DLNG',
		/* [305] */
		"Top origin",
		'DLNG',
		/* [306] */
		"Width",
		'DLNG',
		/* [307] */
		"Height",
		'DLNG',
		/* [308] */
		"Foreground color",
		'COLR',
		/* [309] */
		"Background color",
		'COLR',
		/* [310] */
		"Font name",
		'PSTR',
		/* [311] */
		"Font size",
		'DLNG',
		/* [312] */
		"Font style",
		'DLNG',
		/* [313] */
		"Visible",
		'BFLG',
		/* [314] */
		"Enabled",
		'BFLG',
		/* [315] */
		"Text component data",
		'DVDR',
		/* [316] */
		"Initial text",
		'PSTR',
		/* [317] */
		"Editable?",
		'BFLG',
		/* [318] */
		"",
		'KEYE',
		/* [319] */
		"tfld",
		'KEYB',
		/* [320] */
		"Component data",
		'DVDR',
		/* [321] */
		"Component name",
		'PSTR',
		/* [322] */
		"Left origin",
		'DLNG',
		/* [323] */
		"Top origin",
		'DLNG',
		/* [324] */
		"Width",
		'DLNG',
		/* [325] */
		"Height",
		'DLNG',
		/* [326] */
		"Foreground color",
		'COLR',
		/* [327] */
		"Background color",
		'COLR',
		/* [328] */
		"Font name",
		'PSTR',
		/* [329] */
		"Font size",
		'DLNG',
		/* [330] */
		"Font style",
		'DLNG',
		/* [331] */
		"Visible",
		'BFLG',
		/* [332] */
		"Enabled",
		'BFLG',
		/* [333] */
		"Text component data",
		'DVDR',
		/* [334] */
		"Initial text",
		'PSTR',
		/* [335] */
		"Editable?",
		'BFLG',
		/* [336] */
		"Text field data",
		'DVDR',
		/* [337] */
		"Rows",
		'DLNG',
		/* [338] */
		"Columns",
		'DLNG',
		/* [339] */
		"",
		'KEYE',
		/* [340] */
		"taea",
		'KEYB',
		/* [341] */
		"Component data",
		'DVDR',
		/* [342] */
		"Component name",
		'PSTR',
		/* [343] */
		"Left origin",
		'DLNG',
		/* [344] */
		"Top origin",
		'DLNG',
		/* [345] */
		"Width",
		'DLNG',
		/* [346] */
		"Height",
		'DLNG',
		/* [347] */
		"Foreground color",
		'COLR',
		/* [348] */
		"Background color",
		'COLR',
		/* [349] */
		"Font name",
		'PSTR',
		/* [350] */
		"Font size",
		'DLNG',
		/* [351] */
		"Font style",
		'DLNG',
		/* [352] */
		"Visible",
		'BFLG',
		/* [353] */
		"Enabled",
		'BFLG',
		/* [354] */
		"Text component data",
		'DVDR',
		/* [355] */
		"Initial text",
		'PSTR',
		/* [356] */
		"Editable?",
		'BFLG',
		/* [357] */
		"Text area data",
		'DVDR',
		/* [358] */
		"Columns",
		'DLNG',
		/* [359] */
		"Echo character",
		'CHAR',
		/* [360] */
		"",
		'KEYE',
		/* [361] */
		"null",
		'KEYB',
		/* [362] */
		"",
		'KEYE',
		/* [363] */
		"",
		'KEYB',
		/* [364] */
		"Unknown data",
		'HEXD',
		/* [365] */
		"",
		'KEYE',
		/* [366] */
		"",
		'SKPE',
		/* [367] */
		"",
		'KEYE',
		/* [368] */
		"begs",
		'KEYB',
		/* [369] */
		"",
		'KEYE',
		/* [370] */
		"ends",
		'KEYB',
		/* [371] */
		"",
		'KEYE',
		/* [372] */
		"comm",
		'KEYB',
		/* [373] */
		"Comment data",
		'LSHX',
		/* [374] */
		"",
		'KEYE',
		/* [375] */
		"end.",
		'KEYB',
		/* [376] */
		"This must be last object type in list",
		'DVDR',
		/* [377] */
		"",
		'KEYE',
		/* [378] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1198, "JTYP") {
	{	/* array: 237 elements */
		/* [1] */
		"Template for Constructor CW10",
		'DVDR',
		/* [2] */
		"Version Number",
		'DWRD',
		/* [3] */
		"CW10=1",
		'CASE',
		/* [4] */
		"*****",
		'LSTB',
		/* [5] */
		"Object type",
		'KTYP',
		/* [6] */
		"Object data=objd",
		'CASE',
		/* [7] */
		"Begin sub-object list=begs",
		'CASE',
		/* [8] */
		"End sub-object list=ends",
		'CASE',
		/* [9] */
		"User object=user",
		'CASE',
		/* [10] */
		"Class alias=dopl",
		'CASE',
		/* [11] */
		"End of list=end.",
		'CASE',
		/* [12] */
		"objd",
		'KEYB',
		/* [13] */
		"Number of bytes in following data",
		'LSIZ',
		/* [14] */
		"Data type",
		'KTYP',
		/* [15] */
		"Object=obj ",
		'CASE',
		/* [16] */
		"Custom component info=vjte",
		'CASE',
		/* [17] */
		"Integer attribute=intv",
		'CASE',
		/* [18] */
		"Labelled integer attribute=labi",
		'CASE',
		/* [19] */
		"Min/max integer attribute=mimx",
		'CASE',
		/* [20] */
		"Res list attribute=resl",
		'CASE',
		/* [21] */
		"Resource reference attribute=rerf",
		'CASE',
		/* [22] */
		"String attribute=pstr",
		'CASE',
		/* [23] */
		"Font string attribute=fstr",
		'CASE',
		/* [24] */
		"RGB color attribute=rgbc",
		'CASE',
		/* [25] */
		"Container attribute=cont",
		'CASE',
		/* [26] */
		"List attribute=list",
		'CASE',
		/* [27] */
		"Bitfield container attribute=bitf",
		'CASE',
		/* [28] */
		"Value label=labl",
		'CASE',
		/* [29] */
		"Null=null",
		'CASE',
		/* [30] */
		"obj ",
		'KEYB',
		/* [31] */
		"",
		'KEYE',
		/* [32] */
		"vjte",
		'KEYB',
		/* [33] */
		"VETypeEntry data",
		'DVDR',
		/* [34] */
		"Class name",
		'PSTR',
		/* [35] */
		"Icon ID",
		'DWRD',
		/* [36] */
		"Abstract class?",
		'BFLG',
		/* [37] */
		"Class ID",
		'TNAM',
		/* [38] */
		"Parent class ID",
		'TNAM',
		/* [39] */
		"Default width",
		'DWRD',
		/* [40] */
		"Default height",
		'DWRD',
		/* [41] */
		"Must be root?",
		'BFLG',
		/* [42] */
		"",
		'KEYE',
		/* [43] */
		"intv",
		'KEYB',
		/* [44] */
		"DMAttribute data",
		'DVDR',
		/* [45] */
		"Attribute title",
		'PSTR',
		/* [46] */
		"Attribute key",
		'TNAM',
		/* [47] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [48] */
		"Write to stream?",
		'BFLG',
		/* [49] */
		"Stream selector",
		'TNAM',
		/* [50] */
		"DMIntegerAttribute data",
		'DVDR',
		/* [51] */
		"Default value",
		'DLNG',
		/* [52] */
		"Value size (bits)",
		'UWRD',
		/* [53] */
		"Signed integer?",
		'BFLG',
		/* [54] */
		"Can be text value?",
		'BFLG',
		/* [55] */
		"Always is text value?",
		'BFLG',
		/* [56] */
		"",
		'KEYE',
		/* [57] */
		"labi",
		'KEYB',
		/* [58] */
		"DMAttribute data",
		'DVDR',
		/* [59] */
		"Attribute title",
		'PSTR',
		/* [60] */
		"Attribute key",
		'TNAM',
		/* [61] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [62] */
		"Write to stream?",
		'BFLG',
		/* [63] */
		"Stream selector",
		'TNAM',
		/* [64] */
		"DMIntegerAttribute data",
		'DVDR',
		/* [65] */
		"Default value",
		'DLNG',
		/* [66] */
		"Value size (bits)",
		'UWRD',
		/* [67] */
		"Signed integer?",
		'BFLG',
		/* [68] */
		"Can be text value?",
		'BFLG',
		/* [69] */
		"Always is text value?",
		'BFLG',
		/* [70] */
		"DMLabelledIntegerAttribute data",
		'DVDR',
		/* [71] */
		"Labels only?",
		'BFLG',
		/* [72] */
		"",
		'KEYE',
		/* [73] */
		"mimx",
		'KEYB',
		/* [74] */
		"DMAttribute data",
		'DVDR',
		/* [75] */
		"Attribute title",
		'PSTR',
		/* [76] */
		"Attribute key",
		'TNAM',
		/* [77] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [78] */
		"Write to stream?",
		'BFLG',
		/* [79] */
		"Stream selector",
		'TNAM',
		/* [80] */
		"DMIntegerAttribute data",
		'DVDR',
		/* [81] */
		"Default value",
		'DLNG',
		/* [82] */
		"Value size (bits)",
		'UWRD',
		/* [83] */
		"Signed integer?",
		'BFLG',
		/* [84] */
		"Can be text value?",
		'BFLG',
		/* [85] */
		"Always is text value?",
		'BFLG',
		/* [86] */
		"DMMinMaxIntegerAttribute data",
		'DVDR',
		/* [87] */
		"Minimum value",
		'DLNG',
		/* [88] */
		"Maximum value",
		'DLNG',
		/* [89] */
		"",
		'KEYE',
		/* [90] */
		"resl",
		'KEYB',
		/* [91] */
		"DMAttribute data",
		'DVDR',
		/* [92] */
		"Attribute title",
		'PSTR',
		/* [93] */
		"Attribute key",
		'TNAM',
		/* [94] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [95] */
		"Write to stream?",
		'BFLG',
		/* [96] */
		"Stream selector",
		'TNAM',
		/* [97] */
		"DMIntegerAttribute data",
		'DVDR',
		/* [98] */
		"Default value",
		'DLNG',
		/* [99] */
		"Value size (bits)",
		'UWRD',
		/* [100] */
		"Signed integer?",
		'BFLG',
		/* [101] */
		"Can be text value?",
		'BFLG',
		/* [102] */
		"Always is text value?",
		'BFLG',
		/* [103] */
		"DMLabelledIntegerAttribute data",
		'DVDR',
		/* [104] */
		"Labels only?",
		'BFLG',
		/* [105] */
		"DMResListAttribute data",
		'DVDR',
		/* [106] */
		"Resource type",
		'TNAM',
		/* [107] */
		"",
		'KEYE',
		/* [108] */
		"rerf",
		'KEYB',
		/* [109] */
		"DMAttribute data",
		'DVDR',
		/* [110] */
		"Attribute title",
		'PSTR',
		/* [111] */
		"Attribute key",
		'TNAM',
		/* [112] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [113] */
		"Write to stream?",
		'BFLG',
		/* [114] */
		"Stream selector",
		'TNAM',
		/* [115] */
		"DMIntegerAttribute data",
		'DVDR',
		/* [116] */
		"Default value",
		'DLNG',
		/* [117] */
		"Value size (bits)",
		'UWRD',
		/* [118] */
		"Signed integer?",
		'BFLG',
		/* [119] */
		"Can be text value?",
		'BFLG',
		/* [120] */
		"Always is text value?",
		'BFLG',
		/* [121] */
		"DMResourceRefAttribute data",
		'DVDR',
		/* [122] */
		"Resource type",
		'TNAM',
		/* [123] */
		"",
		'KEYE',
		/* [124] */
		"pstr",
		'KEYB',
		/* [125] */
		"DMAttribute data",
		'DVDR',
		/* [126] */
		"Attribute title",
		'PSTR',
		/* [127] */
		"Attribute key",
		'TNAM',
		/* [128] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [129] */
		"Write to stream?",
		'BFLG',
		/* [130] */
		"Stream selector",
		'TNAM',
		/* [131] */
		"DMStringAttribute data",
		'DVDR',
		/* [132] */
		"Default value",
		'PSTR',
		/* [133] */
		"Maximum length (characters)",
		'UWRD',
		/* [134] */
		"Even padded?",
		'BFLG',
		/* [135] */
		"(unused)",
		'BB05',
		/* [136] */
		"Accept CR?",
		'BBIT',
		/* [137] */
		"C style string?",
		'BBIT',
		/* [138] */
		"Odd padded?",
		'BBIT',
		/* [139] */
		"",
		'KEYE',
		/* [140] */
		"fstr",
		'KEYB',
		/* [141] */
		"DMAttribute data",
		'DVDR',
		/* [142] */
		"Attribute title",
		'PSTR',
		/* [143] */
		"Attribute key",
		'TNAM',
		/* [144] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [145] */
		"Write to stream?",
		'BFLG',
		/* [146] */
		"Stream selector",
		'TNAM',
		/* [147] */
		"DMStringAttribute data",
		'DVDR',
		/* [148] */
		"Default value",
		'PSTR',
		/* [149] */
		"Maximum length (characters)",
		'UWRD',
		/* [150] */
		"Even padded?",
		'BFLG',
		/* [151] */
		"(unused)",
		'BB05',
		/* [152] */
		"Accept CR?",
		'BBIT',
		/* [153] */
		"C style string?",
		'BBIT',
		/* [154] */
		"Odd padded?",
		'BBIT',
		/* [155] */
		"DMFontStringAttribute data",
		'DVDR',
		/* [156] */
		"Default font number",
		'DWRD',
		/* [157] */
		"Write font number?",
		'BFLG',
		/* [158] */
		"Include system font?",
		'BFLG',
		/* [159] */
		"Include application font?",
		'BFLG',
		/* [160] */
		"Include hidden fonts?",
		'BFLG',
		/* [161] */
		"",
		'KEYE',
		/* [162] */
		"rgbc",
		'KEYB',
		/* [163] */
		"DMAttribute data",
		'DVDR',
		/* [164] */
		"Attribute title",
		'PSTR',
		/* [165] */
		"Attribute key",
		'TNAM',
		/* [166] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [167] */
		"Write to stream?",
		'BFLG',
		/* [168] */
		"Stream selector",
		'TNAM',
		/* [169] */
		"DMRGBColorAttribute data",
		'DVDR',
		/* [170] */
		"Default value",
		'COLR',
		/* [171] */
		"",
		'KEYE',
		/* [172] */
		"cont",
		'KEYB',
		/* [173] */
		"DMAttribute data",
		'DVDR',
		/* [174] */
		"Attribute title",
		'PSTR',
		/* [175] */
		"Attribute key",
		'TNAM',
		/* [176] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [177] */
		"Write to stream?",
		'BFLG',
		/* [178] */
		"Stream selector",
		'TNAM',
		/* [179] */
		"DMContainerAttribute data",
		'DVDR',
		/* [180] */
		"Is subobject list?",
		'BFLG',
		/* [181] */
		"Member class ID",
		'TNAM',
		/* [182] */
		"",
		'KEYE',
		/* [183] */
		"list",
		'KEYB',
		/* [184] */
		"DMAttribute data",
		'DVDR',
		/* [185] */
		"Attribute title",
		'PSTR',
		/* [186] */
		"Attribute key",
		'TNAM',
		/* [187] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [188] */
		"Write to stream?",
		'BFLG',
		/* [189] */
		"Stream selector",
		'TNAM',
		/* [190] */
		"DMContainerAttribute data",
		'DVDR',
		/* [191] */
		"Is subobject list?",
		'BFLG',
		/* [192] */
		"Member class ID",
		'TNAM',
		/* [193] */
		"DMListAttribute data",
		'DVDR',
		/* [194] */
		"Subitem title",
		'PSTR',
		/* [195] */
		"Number of bytes for count",
		'DLNG',
		/* [196] */
		"unused",
		'BB06',
		/* [197] */
		"Zero based display?",
		'BB01',
		/* [198] */
		"Zero-based count?",
		'BB01',
		/* [199] */
		"",
		'KEYE',
		/* [200] */
		"bitf",
		'KEYB',
		/* [201] */
		"DMAttribute data",
		'DVDR',
		/* [202] */
		"Attribute title",
		'PSTR',
		/* [203] */
		"Attribute key",
		'TNAM',
		/* [204] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [205] */
		"Write to stream?",
		'BFLG',
		/* [206] */
		"Stream selector",
		'TNAM',
		/* [207] */
		"DMContainerAttribute data",
		'DVDR',
		/* [208] */
		"Is subobject list?",
		'BFLG',
		/* [209] */
		"Member class ID",
		'TNAM',
		/* [210] */
		"DMBitfieldAttribute data",
		'DVDR',
		/* [211] */
		"Bitfield size (bytes)",
		'UWRD',
		/* [212] */
		"",
		'KEYE',
		/* [213] */
		"labl",
		'KEYB',
		/* [214] */
		"Value",
		'DLNG',
		/* [215] */
		"Label",
		'PSTR',
		/* [216] */
		"",
		'KEYE',
		/* [217] */
		"null",
		'KEYB',
		/* [218] */
		"",
		'KEYE',
		/* [219] */
		"",
		'KEYB',
		/* [220] */
		"Unknown data",
		'HEXD',
		/* [221] */
		"",
		'KEYE',
		/* [222] */
		"",
		'SKPE',
		/* [223] */
		"",
		'KEYE',
		/* [224] */
		"begs",
		'KEYB',
		/* [225] */
		"",
		'KEYE',
		/* [226] */
		"ends",
		'KEYB',
		/* [227] */
		"",
		'KEYE',
		/* [228] */
		"user",
		'KEYB',
		/* [229] */
		"SuperClass ID for next object",
		'TNAM',
		/* [230] */
		"",
		'KEYE',
		/* [231] */
		"dopl",
		'KEYB',
		/* [232] */
		"Class ID for next object",
		'TNAM',
		/* [233] */
		"",
		'KEYE',
		/* [234] */
		"end.",
		'KEYB',
		/* [235] */
		"This must be last object type in list",
		'DVDR',
		/* [236] */
		"",
		'KEYE',
		/* [237] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1199, "Just") {
	{	/* array: 17 elements */
		/* [1] */
		"CW Plugin resource format",
		'DVDR',
		/* [2] */
		"Version",
		'DWRD',
		/* [3] */
		"Current=1",
		'CASE',
		/* [4] */
		"Count:",
		'OCNT',
		/* [5] */
		"Text Items",
		'LSTC',
		/* [6] */
		"Item #",
		'DWRD',
		/* [7] */
		"Justification",
		'DBYT',
		/* [8] */
		"System=0",
		'CASE',
		/* [9] */
		"Left=1",
		'CASE',
		/* [10] */
		"Right=2",
		'CASE',
		/* [11] */
		"Centered=3",
		'CASE',
		/* [12] */
		"Long line behaviour",
		'DBYT',
		/* [13] */
		"Wrap=0",
		'CASE',
		/* [14] */
		"Clip=1",
		'CASE',
		/* [15] */
		"Truncate at end=2",
		'CASE',
		/* [16] */
		"Truncate in middle=3",
		'CASE',
		/* [17] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1200, "KBDN") {
	{	/* array: 1 elements */
		/* [1] */
		"Keyboard name",
		'PSTR'
	}
};

resource 'TMPL' (1201, "KCAP") {
	{	/* array: 16 elements */
		/* [1] */
		"Bounds rect",
		'RECT',
		/* [2] */
		"Text rect",
		'RECT',
		/* [3] */
		"Count",
		'OCNT',
		/* [4] */
		"Shapes and keys",
		'LSTC',
		/* [5] */
		"Shape array count",
		'ZCNT',
		/* [6] */
		"Shape entries",
		'LSTC',
		/* [7] */
		"Shape point",
		'PNT ',
		/* [8] */
		"*****",
		'LSTE',
		/* [9] */
		"Key array count",
		'ZCNT',
		/* [10] */
		"Key entries",
		'LSTC',
		/* [11] */
		"Mask",
		'HBYT',
		/* [12] */
		"0 = Or ; 1 = And",
		'BBIT',
		/* [13] */
		"Key code",
		'BB07',
		/* [14] */
		"Delta",
		'PNT ',
		/* [15] */
		"*****",
		'LSTE',
		/* [16] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1202, "KCHR") {
	{	/* array: 35 elements */
		/* [1] */
		"Version",
		'DWRD',
		/* [2] */
		"Indices $00 - $0F",
		'H010',
		/* [3] */
		"Indices $10 - $1F",
		'H010',
		/* [4] */
		"Indices $20 - $2F",
		'H010',
		/* [5] */
		"Indices $30 - $3F",
		'H010',
		/* [6] */
		"Indices $40 - $4F",
		'H010',
		/* [7] */
		"Indices $50 - $5F",
		'H010',
		/* [8] */
		"Indices $60 - $6F",
		'H010',
		/* [9] */
		"Indices $70 - $7F",
		'H010',
		/* [10] */
		"Indices $80 - $8F",
		'H010',
		/* [11] */
		"Indices $90 - $9F",
		'H010',
		/* [12] */
		"Indices $A0 - $AF",
		'H010',
		/* [13] */
		"Indices $B0 - $BF",
		'H010',
		/* [14] */
		"Indices $C0 - $CF",
		'H010',
		/* [15] */
		"Indices $D0 - $DF",
		'H010',
		/* [16] */
		"Indices $E0 - $EF",
		'H010',
		/* [17] */
		"Indices $F0 - $FF",
		'H010',
		/* [18] */
		"Count:",
		'OCNT',
		/* [19] */
		"List of ASCII Characters",
		'LSTC',
		/* [20] */
		"Non-printable ASCII",
		'H020',
		/* [21] */
		"Printable chars",
		'T05F',
		/* [22] */
		"ASCII 127 (DEL)",
		'H001',
		/* [23] */
		"*****",
		'LSTE',
		/* [24] */
		"Count:",
		'OCNT',
		/* [25] */
		"List of Dead keys",
		'LSTC',
		/* [26] */
		"Table number",
		'DBYT',
		/* [27] */
		"Virtual key code",
		'DBYT',
		/* [28] */
		"Count:",
		'OCNT',
		/* [29] */
		"List of Substitutions",
		'LSTC',
		/* [30] */
		"Completor character",
		'CHAR',
		/* [31] */
		"Substituting character",
		'CHAR',
		/* [32] */
		"*****",
		'LSTE',
		/* [33] */
		"No match character",
		'CHAR',
		/* [34] */
		"16-bit extension",
		'CHAR',
		/* [35] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1203, "kind") {
	{	/* array: 9 elements */
		/* [1] */
		"Application signature",
		'TNAM',
		/* [2] */
		"Region code",
		'RGNC',
		/* [3] */
		"Filler (2 bytes)",
		'FWRD',
		/* [4] */
		"Count:",
		'OCNT',
		/* [5] */
		"Files",
		'LSTC',
		/* [6] */
		"File type",
		'TNAM',
		/* [7] */
		"File name",
		'PSTR',
		/* [8] */
		"align",
		'AWRD',
		/* [9] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1204, "KInf") {
	{	/* array: 6 elements */
		/* [1] */
		"\"SuitCase\" resource format",
		'DVDR',
		/* [2] */
		"Key strings ResID",
		'DWRD',
		/* [3] */
		"Modifier strings Res ID",
		'DWRD',
		/* [4] */
		"Symbol SICNs Res ID",
		'DWRD',
		/* [5] */
		"Modifier SICNs Res ID",
		'DWRD',
		/* [6] */
		"Symbols vertical offset",
		'DWRD'
	}
};

resource 'TMPL' (1205, "KMAP") {
	{	/* array: 135 elements */
		/* [1] */
		"ID ( 2=, 5=)",
		'DWRD',
		/* [2] */
		"Standard keyboard=0",
		'CASE',
		/* [3] */
		"Extended keyboard=2",
		'CASE',
		/* [4] */
		"ISO extended keyboard=5",
		'CASE',
		/* [5] */
		"Version",
		'DWRD',
		/* [6] */
		"A 00",
		'HBYT',
		/* [7] */
		"S 01",
		'HBYT',
		/* [8] */
		"D 02",
		'HBYT',
		/* [9] */
		"F 03",
		'HBYT',
		/* [10] */
		"H 04",
		'HBYT',
		/* [11] */
		"G 05",
		'HBYT',
		/* [12] */
		"Z 06",
		'HBYT',
		/* [13] */
		"X 07",
		'HBYT',
		/* [14] */
		"C 08",
		'HBYT',
		/* [15] */
		"V 09",
		'HBYT',
		/* [16] */
		"0A",
		'HBYT',
		/* [17] */
		"B 0B",
		'HBYT',
		/* [18] */
		"Q 0C",
		'HBYT',
		/* [19] */
		"W 0D",
		'HBYT',
		/* [20] */
		"E 0E",
		'HBYT',
		/* [21] */
		"R 0F",
		'HBYT',
		/* [22] */
		"Y 10",
		'HBYT',
		/* [23] */
		"T 11",
		'HBYT',
		/* [24] */
		"1 12",
		'HBYT',
		/* [25] */
		"2 13",
		'HBYT',
		/* [26] */
		"3 14",
		'HBYT',
		/* [27] */
		"4 15",
		'HBYT',
		/* [28] */
		"6 16",
		'HBYT',
		/* [29] */
		"5 17",
		'HBYT',
		/* [30] */
		"= 18",
		'HBYT',
		/* [31] */
		"9 19",
		'HBYT',
		/* [32] */
		"7 1A",
		'HBYT',
		/* [33] */
		"- 1B",
		'HBYT',
		/* [34] */
		"8 1C",
		'HBYT',
		/* [35] */
		"0 1D",
		'HBYT',
		/* [36] */
		"] 1E",
		'HBYT',
		/* [37] */
		"O (letter oh) 1F",
		'HBYT',
		/* [38] */
		"U 20",
		'HBYT',
		/* [39] */
		"[ 21",
		'HBYT',
		/* [40] */
		"I 22",
		'HBYT',
		/* [41] */
		"P 23",
		'HBYT',
		/* [42] */
		"return 24",
		'HBYT',
		/* [43] */
		"L 25",
		'HBYT',
		/* [44] */
		"J 26",
		'HBYT',
		/* [45] */
		"\" 27",
		'HBYT',
		/* [46] */
		"K 28",
		'HBYT',
		/* [47] */
		"; 29",
		'HBYT',
		/* [48] */
		"\\ 2A",
		'HBYT',
		/* [49] */
		", 2B",
		'HBYT',
		/* [50] */
		"/ 2C",
		'HBYT',
		/* [51] */
		"N 2D",
		'HBYT',
		/* [52] */
		"M 2E",
		'HBYT',
		/* [53] */
		". 2F",
		'HBYT',
		/* [54] */
		"tab 30",
		'HBYT',
		/* [55] */
		"space 31",
		'HBYT',
		/* [56] */
		"` 32",
		'HBYT',
		/* [57] */
		"delete 33",
		'HBYT',
		/* [58] */
		"Unused 34",
		'HBYT',
		/* [59] */
		"esc 35",
		'HBYT',
		/* [60] */
		"control 36 (usual virtual code 3B)",
		'HBYT',
		/* [61] */
		"command 37",
		'HBYT',
		/* [62] */
		"shift 38",
		'HBYT',
		/* [63] */
		"caps lock 39",
		'HBYT',
		/* [64] */
		"option 3A",
		'HBYT',
		/* [65] */
		"left arrow 3B (usual virtual 7B)",
		'HBYT',
		/* [66] */
		"right arrow 3C (usual virtual 7C)",
		'HBYT',
		/* [67] */
		"down arrow 3D (usual virtual 7D)",
		'HBYT',
		/* [68] */
		"up arrow 3E (usual virtual 7E)",
		'HBYT',
		/* [69] */
		"3F",
		'HBYT',
		/* [70] */
		"40",
		'HBYT',
		/* [71] */
		"KP . 41",
		'HBYT',
		/* [72] */
		"42",
		'HBYT',
		/* [73] */
		"KP * 43",
		'HBYT',
		/* [74] */
		"44",
		'HBYT',
		/* [75] */
		"KP + 45",
		'HBYT',
		/* [76] */
		"46",
		'HBYT',
		/* [77] */
		"KP clear 47",
		'HBYT',
		/* [78] */
		"Unused 48,49,4A",
		'H003',
		/* [79] */
		"KP / 4B",
		'HBYT',
		/* [80] */
		"KP enter 4C",
		'HBYT',
		/* [81] */
		"4D",
		'HBYT',
		/* [82] */
		"KP - 4E",
		'HBYT',
		/* [83] */
		"Unused 4F, 50",
		'H002',
		/* [84] */
		"KP = 51",
		'HBYT',
		/* [85] */
		"KP 0 52",
		'HBYT',
		/* [86] */
		"KP 1 53",
		'HBYT',
		/* [87] */
		"KP 2 54",
		'HBYT',
		/* [88] */
		"KP 3 55",
		'HBYT',
		/* [89] */
		"KP 4 56",
		'HBYT',
		/* [90] */
		"KP 5 57",
		'HBYT',
		/* [91] */
		"KP 6 58",
		'HBYT',
		/* [92] */
		"KP 7 59",
		'HBYT',
		/* [93] */
		"5A",
		'HBYT',
		/* [94] */
		"KP 8 5B",
		'HBYT',
		/* [95] */
		"KP 9 5C",
		'HBYT',
		/* [96] */
		"Unused 5D,5E,5F",
		'H003',
		/* [97] */
		"F5 60",
		'HBYT',
		/* [98] */
		"F6 61",
		'HBYT',
		/* [99] */
		"F7 62",
		'HBYT',
		/* [100] */
		"F3 63",
		'HBYT',
		/* [101] */
		"F8 64",
		'HBYT',
		/* [102] */
		"F9 65",
		'HBYT',
		/* [103] */
		"66",
		'HBYT',
		/* [104] */
		"F11 67",
		'HBYT',
		/* [105] */
		"68",
		'HBYT',
		/* [106] */
		"F13 69",
		'HBYT',
		/* [107] */
		"6A",
		'HBYT',
		/* [108] */
		"F14 6B",
		'HBYT',
		/* [109] */
		"6C",
		'HBYT',
		/* [110] */
		"F10 6D",
		'HBYT',
		/* [111] */
		"Unused 6E, 6F,70",
		'H003',
		/* [112] */
		"F15 71",
		'HBYT',
		/* [113] */
		"HELP 72",
		'HBYT',
		/* [114] */
		"HOME 73",
		'HBYT',
		/* [115] */
		"PG UP 74",
		'HBYT',
		/* [116] */
		"DEL RT 75",
		'HBYT',
		/* [117] */
		"F4 76",
		'HBYT',
		/* [118] */
		"END 77",
		'HBYT',
		/* [119] */
		"F2 78",
		'HBYT',
		/* [120] */
		"PG DN 79",
		'HBYT',
		/* [121] */
		"F1 7A",
		'HBYT',
		/* [122] */
		"7B, 7C, 7D, 7E, 7F",
		'H005',
		/* [123] */
		"Count:",
		'OCNT',
		/* [124] */
		"ASCII Character Exceptions",
		'LSTC',
		/* [125] */
		"Raw keycode",
		'HBYT',
		/* [126] */
		"noXor, Xor",
		'BBIT',
		/* [127] */
		"Reserved",
		'BBIT',
		/* [128] */
		"Reserved",
		'BBIT',
		/* [129] */
		"Reserved",
		'BBIT',
		/* [130] */
		"ADB opcode 1",
		'BBIT',
		/* [131] */
		"ADB 2",
		'BBIT',
		/* [132] */
		"ADB 3",
		'BBIT',
		/* [133] */
		"ADB 4",
		'BBIT',
		/* [134] */
		"Data string",
		'PSTR',
		/* [135] */
		"****",
		'LSTE'
	}
};

resource 'TMPL' (1206, "KRNL") {
	{	/* array: 5 elements */
		/* [1] */
		"Use FilterBits?",
		'BOOL',
		/* [2] */
		"Count:",
		'OCNT',
		/* [3] */
		"List of coefficients",
		'LSTC',
		/* [4] */
		"Coefficient",
		'DBYT',
		/* [5] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1207, "KSWP") {
	{	/* array: 32 elements */
		/* [1] */
		"Don't change the last list item, it is a"
		" filler.",
		'DVDR',
		/* [2] */
		"Keyboard swapping array",
		'LSTB',
		/* [3] */
		"Script code or verb",
		'DWRD',
		/* [4] */
		"Roman=0",
		'CASE',
		/* [5] */
		"Japanese=1",
		'CASE',
		/* [6] */
		"TradChinese=2",
		'CASE',
		/* [7] */
		"Korean=3",
		'CASE',
		/* [8] */
		"Arabic=4",
		'CASE',
		/* [9] */
		"Hebrew=5",
		'CASE',
		/* [10] */
		"Greek=6",
		'CASE',
		/* [11] */
		"Cyrillic=7",
		'CASE',
		/* [12] */
		"Thai=21",
		'CASE',
		/* [13] */
		"SimpChinese=25",
		'CASE',
		/* [14] */
		"CentralEuroRoman=29",
		'CASE',
		/* [15] */
		"Rotate=-1",
		'CASE',
		/* [16] */
		"System=-2",
		'CASE',
		/* [17] */
		"Alternate=-3",
		'CASE',
		/* [18] */
		"RotateKybd=-4",
		'CASE',
		/* [19] */
		"ToggleDirection=-9",
		'CASE',
		/* [20] */
		"SetDirLeftRight=-15",
		'CASE',
		/* [21] */
		"SetDirRightLeft=-16",
		'CASE',
		/* [22] */
		"RomanIfOthers=-17",
		'CASE',
		/* [23] */
		"Virtual key code",
		'UBYT',
		/* [24] */
		"Right Control",
		'BBIT',
		/* [25] */
		"Right Option",
		'BBIT',
		/* [26] */
		"Right Shift",
		'BBIT',
		/* [27] */
		"Control",
		'BBIT',
		/* [28] */
		"Option",
		'BBIT',
		/* [29] */
		"Caps Lock",
		'BBIT',
		/* [30] */
		"Shift",
		'BBIT',
		/* [31] */
		"Command",
		'BBIT',
		/* [32] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1208, "Labl") {
	{	/* array: 6 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"Labels",
		'LSTC',
		/* [3] */
		"Index",
		'DLNG',
		/* [4] */
		"RGB color",
		'COLR',
		/* [5] */
		"Name",
		'P020',
		/* [6] */
		"****",
		'LSTE'
	}
};

resource 'TMPL' (1209, "LAYO") {
	{	/* array: 40 elements */
		/* [1] */
		"Font ID",
		'DWRD',
		/* [2] */
		"Font size",
		'DWRD',
		/* [3] */
		"Screen header height",
		'DWRD',
		/* [4] */
		"Top line break",
		'DWRD',
		/* [5] */
		"Bottom line break",
		'DWRD',
		/* [6] */
		"Printing header height",
		'DWRD',
		/* [7] */
		"Printing footer height",
		'DWRD',
		/* [8] */
		"Window rectangle",
		'RECT',
		/* [9] */
		"Line spacing",
		'DWRD',
		/* [10] */
		"Tab stop 1",
		'DWRD',
		/* [11] */
		"Tab stop 2",
		'DWRD',
		/* [12] */
		"Tab stop 3",
		'DWRD',
		/* [13] */
		"Tab stop 4",
		'DWRD',
		/* [14] */
		"Tab stop 5",
		'DWRD',
		/* [15] */
		"Tab stop 6",
		'DWRD',
		/* [16] */
		"Tab stop 7",
		'DWRD',
		/* [17] */
		"Column justification",
		'HBYT',
		/* [18] */
		"Reserved",
		'HBYT',
		/* [19] */
		"Icon horizontal spacing",
		'DWRD',
		/* [20] */
		"Icon vertical spacing",
		'DWRD',
		/* [21] */
		"Icon vertical phase",
		'DWRD',
		/* [22] */
		"Small icon horizontal spacing",
		'DWRD',
		/* [23] */
		"Small icon vertical spacing",
		'DWRD',
		/* [24] */
		"Default view",
		'DBYT',
		/* [25] */
		"Filler",
		'FBYT',
		/* [26] */
		"Text view date",
		'HWRD',
		/* [27] */
		"Use zoom rectangles",
		'BBIT',
		/* [28] */
		"Skip trash warnings",
		'BBIT',
		/* [29] */
		"Always grid drags",
		'BBIT',
		/* [30] */
		"Unused",
		'BB05',
		/* [31] */
		"Icon-text gap",
		'DBYT',
		/* [32] */
		"Sort style",
		'DWRD',
		/* [33] */
		"Watch threshold",
		'DLNG',
		/* [34] */
		"Unused",
		'BB04',
		/* [35] */
		"Use physical icon",
		'BBIT',
		/* [36] */
		"Title click",
		'BBIT',
		/* [37] */
		"Copy inherit",
		'BBIT',
		/* [38] */
		"New folder inherit",
		'BBIT',
		/* [39] */
		"Color style",
		'DBYT',
		/* [40] */
		"Max number of windows",
		'DWRD'
	}
};

resource 'TMPL' (1210, "LBEL") {
	{	/* array: 6 elements */
		/* [1] */
		"\"Resurrection\" resource format",
		'DVDR',
		/* [2] */
		"Count:",
		'OCNT',
		/* [3] */
		"List of entries",
		'LSTC',
		/* [4] */
		"Value",
		'DLNG',
		/* [5] */
		"Label",
		'P020',
		/* [6] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1211, "LBRK") {
	{	/* array: 12 elements */
		/* [1] */
		"\"Eudora\" resource format",
		'DVDR',
		/* [2] */
		"Flags 1",
		'HBYT',
		/* [3] */
		"Flags 2",
		'HBYT',
		/* [4] */
		"Version",
		'HWRD',
		/* [5] */
		"Class table offset",
		'HWRD',
		/* [6] */
		"Aux table offset",
		'HWRD',
		/* [7] */
		"Backward table offset",
		'HWRD',
		/* [8] */
		"Forward table offset",
		'HWRD',
		/* [9] */
		"Do backup minimum",
		'DWRD',
		/* [10] */
		"Table length",
		'HWRD',
		/* [11] */
		"Char types",
		'H100',
		/* [12] */
		"Tables",
		'HEXD'
	}
};

resource 'TMPL' (1212, "ldes") {
	{	/* array: 12 elements */
		/* [1] */
		"Version",
		'KWRD',
		/* [2] */
		"Latest=0",
		'CASE',
		/* [3] */
		"0",
		'KEYB',
		/* [4] */
		"Number of rows",
		'DWRD',
		/* [5] */
		"Number of columns",
		'DWRD',
		/* [6] */
		"Cell height in pixels",
		'DWRD',
		/* [7] */
		"Cell width in pixels",
		'DWRD',
		/* [8] */
		"Has vertical scroll bar",
		'BOOL',
		/* [9] */
		"Has horizontal scroll bar",
		'BOOL',
		/* [10] */
		"'LDEF' resource ID",
		'RSID',
		/* [11] */
		"Has grow space?",
		'BOOL',
		/* [12] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1213, "libi") {
	{	/* array: 9 elements */
		/* [1] */
		"Format version",
		'DLNG',
		/* [2] */
		"Standard=0",
		'CASE',
		/* [3] */
		"Unused",
		'FWRD',
		/* [4] */
		"Unused",
		'FWRD',
		/* [5] */
		"Unused",
		'FWRD',
		/* [6] */
		"Count:",
		'OCNT',
		/* [7] */
		"List of Offsets",
		'LSTC',
		/* [8] */
		"Offset of class/function in global world",
		'HLNG',
		/* [9] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1214, "libr") {
	{	/* array: 50 elements */
		/* [1] */
		"Libraries",
		'LSTB',
		/* [2] */
		"Library ID string",
		'ECST',
		/* [3] */
		"Code resource type",
		'TNAM',
		/* [4] */
		"'libr' template major version",
		'HBYT',
		/* [5] */
		"'libr' template minor version",
		'HBYT',
		/* [6] */
		"Major version",
		'HBYT',
		/* [7] */
		"Minor version",
		'HBYT',
		/* [8] */
		"Development stage",
		'HBYT',
		/* [9] */
		"Release within stage",
		'HBYT',
		/* [10] */
		"Reserved",
		'FBYT',
		/* [11] */
		"Compiler type",
		'HBYT',
		/* [12] */
		"Per client data size",
		'DWRD',
		/* [13] */
		"Default=0",
		'CASE',
		/* [14] */
		"Heap size",
		'DLNG',
		/* [15] */
		"Default=0",
		'CASE',
		/* [16] */
		"Flags for the code resource",
		'DVDR',
		/* [17] */
		"Reserved",
		'LB06',
		/* [18] */
		"Not a 68040",
		'LBIT',
		/* [19] */
		"Not a 68030",
		'LBIT',
		/* [20] */
		"Not a 68020",
		'LBIT',
		/* [21] */
		"Not a 68000",
		'LBIT',
		/* [22] */
		"Doesn't have FPU",
		'LBIT',
		/* [23] */
		"Has FPU",
		'LBIT',
		/* [24] */
		"Not VM Off",
		'LBIT',
		/* [25] */
		"Not VM On",
		'LBIT',
		/* [26] */
		"Not System 6",
		'LBIT',
		/* [27] */
		"Not System 7",
		'LBIT',
		/* [28] */
		"Reserved",
		'LB10',
		/* [29] */
		"Load self",
		'LBIT',
		/* [30] */
		"Force deps",
		'LBIT',
		/* [31] */
		"Load deps",
		'LBIT',
		/* [32] */
		"No segment unload",
		'LBIT',
		/* [33] */
		"Client pool",
		'LBIT',
		/* [34] */
		"Preload",
		'LBIT',
		/* [35] */
		"Count:",
		'OCNT',
		/* [36] */
		"Implemented class IDs",
		'LSTC',
		/* [37] */
		"Reserved",
		'LB29',
		/* [38] */
		"Is function set",
		'LBIT',
		/* [39] */
		"New object",
		'LBIT',
		/* [40] */
		"Preload",
		'LBIT',
		/* [41] */
		"Current version",
		'DWRD',
		/* [42] */
		"Minimum version",
		'DWRD',
		/* [43] */
		"Class ID string",
		'ECST',
		/* [44] */
		"Count:",
		'OCNT',
		/* [45] */
		"List of Parents",
		'LSTC',
		/* [46] */
		"Parent class ID string",
		'CSTR',
		/* [47] */
		"*****",
		'LSTE',
		/* [48] */
		"Align",
		'AWRD',
		/* [49] */
		"*****",
		'LSTE',
		/* [50] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1215, "LIST") {
	{	/* array: 19 elements */
		/* [1] */
		"\"MacZoop\" resource format",
		'DVDR',
		/* [2] */
		"Number of rows",
		'DWRD',
		/* [3] */
		"Number of columns",
		'DWRD',
		/* [4] */
		"\"STR#\" Res ID",
		'RSID',
		/* [5] */
		"None=0",
		'CASE',
		/* [6] */
		"Proc ID",
		'DWRD',
		/* [7] */
		"System LDEF=0",
		'CASE',
		/* [8] */
		"Vertical scrollbar",
		'BBIT',
		/* [9] */
		"Horizontal scrollbar",
		'BBIT',
		/* [10] */
		"Grow box",
		'BBIT',
		/* [11] */
		"Visible",
		'BBIT',
		/* [12] */
		"Keyboard focus?",
		'BBIT',
		/* [13] */
		"White background",
		'BBIT',
		/* [14] */
		"Reserved",
		'BB02',
		/* [15] */
		"align",
		'AWRD',
		/* [16] */
		"RefCon",
		'DLNG',
		/* [17] */
		"Font size",
		'DWRD',
		/* [18] */
		"System Font=0",
		'CASE',
		/* [19] */
		"Font",
		'P064'
	}
};

resource 'TMPL' (1216, "load") {
	{	/* array: 4 elements */
		/* [1] */
		"Load priority",
		'HLNG',
		/* [2] */
		"Load anywhere=$7FFFFFFF",
		'CASE',
		/* [3] */
		"Load first=$00000100",
		'CASE',
		/* [4] */
		"Load last=$FFFFFF00",
		'CASE'
	}
};

resource 'TMPL' (1217, "LOGD") {
	{	/* array: 5 elements */
		/* [1] */
		"Maximum log file size",
		'DLNG',
		/* [2] */
		"Amount preserved if max log size exceede"
		"d",
		'DLNG',
		/* [3] */
		"Log file creator",
		'TNAM',
		/* [4] */
		"Log file type",
		'TNAM',
		/* [5] */
		"Log file name",
		'ESTR'
	}
};

resource 'TMPL' (1218, "look") {
	{	/* array: 8 elements */
		/* [1] */
		"Default looker",
		'DWRD',
		/* [2] */
		"Count:",
		'OCNT',
		/* [3] */
		"List of Lookers",
		'LSTC',
		/* [4] */
		"Name of looker to show user",
		'P022',
		/* [5] */
		"'comm' resource ID",
		'RSID',
		/* [6] */
		"Flags",
		'HWRD',
		/* [7] */
		"NBP type or non-AppleTalk default name",
		'P022',
		/* [8] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1219, "mach") {
	{	/* array: 3 elements */
		/* [1] */
		"Machine type: cdev filtering",
		'HLNG',
		/* [2] */
		"Runs on all Macs=$FFFF0000",
		'CASE',
		/* [3] */
		"Control Panel decides=$0000FFFF",
		'CASE'
	}
};

resource 'TMPL' (1220, "MACS") {
	{	/* array: 2 elements */
		/* [1] */
		"String",
		'PSTR',
		/* [2] */
		"Hexadecimal data",
		'HEXD'
	}
};

resource 'TMPL' (1221, "mapp") {
	{	/* array: 9 elements */
		/* [1] */
		"",
		'LSTB',
		/* [2] */
		"File type",
		'TNAM',
		/* [3] */
		"Extension",
		'PSTR',
		/* [4] */
		"Description",
		'PSTR',
		/* [5] */
		"Mime type",
		'PSTR',
		/* [6] */
		"Binary",
		'BOOL',
		/* [7] */
		"Dummy string",
		'PSTR',
		/* [8] */
		"Dummy long",
		'DLNG',
		/* [9] */
		"",
		'LSTE'
	}
};

resource 'TMPL' (1222, "MBAR") {
	{	/* array: 4 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"List of menu IDs",
		'LSTC',
		/* [3] */
		"Menu resource ID",
		'DWRD',
		/* [4] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1223, "mcfg") {
	{	/* array: 47 elements */
		/* [1] */
		"Importer MIME configuration info",
		'DVDR',
		/* [2] */
		"Resource version",
		'DLNG',
		/* [3] */
		"Version of the component this applies to",
		'DLNG',
		/* [4] */
		"kVersionDoesntMatter=0",
		'CASE',
		/* [5] */
		"Count:",
		'LCNT',
		/* [6] */
		"Array of media types info",
		'LSTC',
		/* [7] */
		"ID of the group this type belongs with",
		'TNAM',
		/* [8] */
		"Stream Group ID=strm",
		'CASE',
		/* [9] */
		"Interactive Group ID=intr",
		'CASE',
		/* [10] */
		"Video Group ID=eyes",
		'CASE',
		/* [11] */
		"Audio Group ID=ears",
		'CASE',
		/* [12] */
		"MPEG Group ID=mpeg",
		'CASE',
		/* [13] */
		"MP3 Group ID=mp3 ",
		'CASE',
		/* [14] */
		"Image Group ID=ogle",
		'CASE',
		/* [15] */
		"Misc Group ID=misc",
		'CASE',
		/* [16] */
		"MIME config flags",
		'TNAM',
		/* [17] */
		"MacOS file type when saved",
		'TNAM',
		/* [18] */
		"MacOS file creator when saved",
		'TNAM',
		/* [19] */
		"Component type",
		'TNAM',
		/* [20] */
		"Component subtype",
		'TNAM',
		/* [21] */
		"Component manufacturer",
		'TNAM',
		/* [22] */
		"Component flags",
		'HLNG',
		/* [23] */
		"Component flags mask",
		'HLNG',
		/* [24] */
		"Any Component Flags Mask=0",
		'CASE',
		/* [25] */
		"Default file extension",
		'TNAM',
		/* [26] */
		"QT file group",
		'TNAM',
		/* [27] */
		"Net Group=net ",
		'CASE',
		/* [28] */
		"Win Group=win ",
		'CASE',
		/* [29] */
		"Mac Group=mac ",
		'CASE',
		/* [30] */
		"Misc Group=????",
		'CASE',
		/* [31] */
		"Count:",
		'LCNT',
		/* [32] */
		"Array of media type synonyms",
		'LSTC',
		/* [33] */
		"Synonym",
		'PSTR',
		/* [34] */
		"*****",
		'LSTE',
		/* [35] */
		"align",
		'ALNG',
		/* [36] */
		"Media type description",
		'PSTR',
		/* [37] */
		"File extension(s)",
		'PSTR',
		/* [38] */
		"Opening application name",
		'PSTR',
		/* [39] */
		"Missing software description",
		'PSTR',
		/* [40] */
		"Vendor info string (copyright, version)",
		'PSTR',
		/* [41] */
		"align",
		'ALNG',
		/* [42] */
		"Count:",
		'LCNT',
		/* [43] */
		"Array of MIME types (eg. audio/mpeg)",
		'LSTC',
		/* [44] */
		"Description",
		'PSTR',
		/* [45] */
		"*****",
		'LSTE',
		/* [46] */
		"align",
		'ALNG',
		/* [47] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1224, "mcky") {
	{	/* array: 8 elements */
		/* [1] */
		"Threshold 1",
		'UBYT',
		/* [2] */
		"Threshold 2",
		'UBYT',
		/* [3] */
		"Threshold 3",
		'UBYT',
		/* [4] */
		"Threshold 4",
		'UBYT',
		/* [5] */
		"Threshold 5",
		'UBYT',
		/* [6] */
		"Threshold 6",
		'UBYT',
		/* [7] */
		"Threshold 7",
		'UBYT',
		/* [8] */
		"Threshold 8",
		'UBYT'
	}
};

resource 'TMPL' (1225, "Mcmd") {
	{	/* array: 44 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"Menu commands",
		'LSTC',
		/* [3] */
		"Command Number",
		'DLNG',
		/* [4] */
		"cmd_Nothing=0",
		'CASE',
		/* [5] */
		"cmd_UseMenuItem=-1",
		'CASE',
		/* [6] */
		"cmd_About=1",
		'CASE',
		/* [7] */
		"cmd_New=2",
		'CASE',
		/* [8] */
		"cmd_Open=3",
		'CASE',
		/* [9] */
		"cmd_Close=4",
		'CASE',
		/* [10] */
		"cmd_Save=5",
		'CASE',
		/* [11] */
		"cmd_SaveAs=6",
		'CASE',
		/* [12] */
		"cmd_Revert=7",
		'CASE',
		/* [13] */
		"cmd_PageSetup=8",
		'CASE',
		/* [14] */
		"cmd_Print=9",
		'CASE',
		/* [15] */
		"cmd_Quit=10",
		'CASE',
		/* [16] */
		"cmd_Undo=11",
		'CASE',
		/* [17] */
		"cmd_Cut=12",
		'CASE',
		/* [18] */
		"cmd_Copy=13",
		'CASE',
		/* [19] */
		"cmd_Paste=14",
		'CASE',
		/* [20] */
		"cmd_Clear=15",
		'CASE',
		/* [21] */
		"cmd_SelectAll=16",
		'CASE',
		/* [22] */
		"cmd_PrintOne=17",
		'CASE',
		/* [23] */
		"cmd_SaveCopyAs=18",
		'CASE',
		/* [24] */
		"cmd_ShowClipboard=19",
		'CASE',
		/* [25] */
		"cmd_FontMenu=250",
		'CASE',
		/* [26] */
		"cmd_SizeMenu=251",
		'CASE',
		/* [27] */
		"cmd_StyleMenu=252",
		'CASE',
		/* [28] */
		"cmd_FontLarger=301",
		'CASE',
		/* [29] */
		"cmd_FontSmaller=302",
		'CASE',
		/* [30] */
		"cmd_FontOther=303",
		'CASE',
		/* [31] */
		"cmd_Plain=401",
		'CASE',
		/* [32] */
		"cmd_Bold=402",
		'CASE',
		/* [33] */
		"cmd_Italic=403",
		'CASE',
		/* [34] */
		"cmd_Underline=404",
		'CASE',
		/* [35] */
		"cmd_Outline=405",
		'CASE',
		/* [36] */
		"cmd_Shadow=406",
		'CASE',
		/* [37] */
		"cmd_Condense=407",
		'CASE',
		/* [38] */
		"cmd_Extend=408",
		'CASE',
		/* [39] */
		"cmd_JustifyDefault=411",
		'CASE',
		/* [40] */
		"cmd_JustifyLeft=412",
		'CASE',
		/* [41] */
		"cmd_JustifyCenter=413",
		'CASE',
		/* [42] */
		"cmd_JustifyRight=414",
		'CASE',
		/* [43] */
		"cmd_JustifyFull=415",
		'CASE',
		/* [44] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1226, "mctb") {
	{	/* array: 12 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"Color menu entries",
		'LSTC',
		/* [3] */
		"Menu ID",
		'DWRD',
		/* [4] */
		"Menu bar=0",
		'CASE',
		/* [5] */
		"mctbLast=-99",
		'CASE',
		/* [6] */
		"Item number (0=menu title)",
		'DWRD',
		/* [7] */
		"Color 1",
		'COLR',
		/* [8] */
		"Color 2",
		'COLR',
		/* [9] */
		"Color 3",
		'COLR',
		/* [10] */
		"Color 4",
		'COLR',
		/* [11] */
		"Reserved",
		'HWRD',
		/* [12] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1227, "mcvs") {
	{	/* array: 25 elements */
		/* [1] */
		"Version",
		'ULNG',
		/* [2] */
		"Flags",
		'LB28',
		/* [3] */
		"Unused",
		'LB03',
		/* [4] */
		"AppleSingle encoded",
		'LBIT',
		/* [5] */
		"RefCon",
		'DLNG',
		/* [6] */
		"FileName string",
		'PSTR',
		/* [7] */
		"Filler byte",
		'FBYT',
		/* [8] */
		"Revision string",
		'PSTR',
		/* [9] */
		"Filler byte",
		'FBYT',
		/* [10] */
		"Conflicts string",
		'PSTR',
		/* [11] */
		"Filler byte",
		'FBYT',
		/* [12] */
		"Options string",
		'PSTR',
		/* [13] */
		"Filler byte",
		'FBYT',
		/* [14] */
		"Tag string",
		'PSTR',
		/* [15] */
		"Filler byte",
		'FBYT',
		/* [16] */
		"Unused string 1",
		'PSTR',
		/* [17] */
		"Filler byte",
		'FBYT',
		/* [18] */
		"Unused string 2",
		'PSTR',
		/* [19] */
		"Filler byte",
		'FBYT',
		/* [20] */
		"Unused string 3",
		'PSTR',
		/* [21] */
		"Filler byte",
		'FBYT',
		/* [22] */
		"Unused string 4",
		'PSTR',
		/* [23] */
		"Filler byte",
		'FBYT',
		/* [24] */
		"Remote path",
		'WSTR',
		/* [25] */
		"Filler byte",
		'FBYT'
	}
};

resource 'TMPL' (1228, "mem!") {
	{	/* array: 5 elements */
		/* [1] */
		"Add to the size of heap space",
		'DLNG',
		/* [2] */
		"Add to heap increment size",
		'DLNG',
		/* [3] */
		"Add to code reserve size",
		'DLNG',
		/* [4] */
		"Add to low space reserve size",
		'DLNG',
		/* [5] */
		"Stack size",
		'DLNG'
	}
};

resource 'TMPL' (1229, "MENA") {
	{	/* array: 5 elements */
		/* [1] */
		"Number of keys",
		'DWRD',
		/* [2] */
		"Flags",
		'DLNG',
		/* [3] */
		"List of keys",
		'LSTB',
		/* [4] */
		"Key",
		'CHAR',
		/* [5] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1230, "MENU") {
	{	/* array: 35 elements */
		/* [1] */
		"MenuID",
		'DWRD',
		/* [2] */
		"Width",
		'FWRD',
		/* [3] */
		"Height",
		'FWRD',
		/* [4] */
		"ID of menu def proc (MDEF)",
		'RSID',
		/* [5] */
		"Filler",
		'FWRD',
		/* [6] */
		"Items 1-31 enable flags",
		'LB31',
		/* [7] */
		"Entire menu enabled",
		'LBIT',
		/* [8] */
		"Title",
		'PSTR',
		/* [9] */
		"Apple=\0x14",
		'CASE',
		/* [10] */
		"Menu items",
		'LSTZ',
		/* [11] */
		"Menu Item Title",
		'PSTR',
		/* [12] */
		"Divider=-",
		'CASE',
		/* [13] */
		"Icon ID - 256 (or 0 for no icon)",
		'DBYT',
		/* [14] */
		"Key equivalent or hier. menu",
		'UBYT',
		/* [15] */
		"No key=0",
		'CASE',
		/* [16] */
		"Hierarchical menu=27",
		'CASE',
		/* [17] */
		"Non system script=28",
		'CASE',
		/* [18] */
		"Using 'ICON'=29",
		'CASE',
		/* [19] */
		"Using 'SICN'=30",
		'CASE',
		/* [20] */
		"Mark char or ID of hier. menu",
		'UBYT',
		/* [21] */
		"No mark=0",
		'CASE',
		/* [22] */
		"Command mark=17",
		'CASE',
		/* [23] */
		"Check mark=18",
		'CASE',
		/* [24] */
		"Diamond mark=19",
		'CASE',
		/* [25] */
		"Apple mark=20",
		'CASE',
		/* [26] */
		"Item Style",
		'BORV',
		/* [27] */
		"Plain=0",
		'CASE',
		/* [28] */
		"Bold=1",
		'CASE',
		/* [29] */
		"Italic=2",
		'CASE',
		/* [30] */
		"Underline=4",
		'CASE',
		/* [31] */
		"Outline=8",
		'CASE',
		/* [32] */
		"Shadow=16",
		'CASE',
		/* [33] */
		"Condensed=32",
		'CASE',
		/* [34] */
		"Extended=64",
		'CASE',
		/* [35] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1231, "mgrp") {
	{	/* array: 11 elements */
		/* [1] */
		"Importer MIME configuration info",
		'DVDR',
		/* [2] */
		"Resource version",
		'DLNG',
		/* [3] */
		"Component version this applies to",
		'DLNG',
		/* [4] */
		"Version does'nt matter=0",
		'CASE',
		/* [5] */
		"Count:",
		'LCNT',
		/* [6] */
		"MIME groups",
		'LSTC',
		/* [7] */
		"Group ID (OSType)",
		'TNAM',
		/* [8] */
		"Name of the grouping",
		'PSTR',
		/* [9] */
		"Description",
		'PSTR',
		/* [10] */
		"alignment",
		'ALNG',
		/* [11] */
		"-----",
		'LSTE'
	}
};

resource 'TMPL' (1232, "MIMA") {
	{	/* array: 13 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"Entries",
		'LSTC',
		/* [3] */
		"Reserved",
		'FBYT',
		/* [4] */
		"Reserved",
		'FBYT',
		/* [5] */
		"Description",
		'P040',
		/* [6] */
		"MIME type",
		'P040',
		/* [7] */
		"Extension",
		'P010',
		/* [8] */
		"File type",
		'TNAM',
		/* [9] */
		"Binary file",
		'BFLG',
		/* [10] */
		"Macintosh file",
		'BFLG',
		/* [11] */
		"Package mask",
		'HWRD',
		/* [12] */
		"Reserved",
		'F020',
		/* [13] */
		"",
		'LSTE'
	}
};

resource 'TMPL' (1233, "MIMD") {
	{	/* array: 9 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"Entries",
		'LSTC',
		/* [3] */
		"Reserved",
		'FBYT',
		/* [4] */
		"Reserved",
		'FBYT',
		/* [5] */
		"MIME type",
		'P040',
		/* [6] */
		"Extension",
		'P010',
		/* [7] */
		"Package mask",
		'HWRD',
		/* [8] */
		"Reserved",
		'F020',
		/* [9] */
		"",
		'LSTE'
	}
};

resource 'TMPL' (1234, "mimp") {
	{	/* array: 6 elements */
		/* [1] */
		"Resource version",
		'HLNG',
		/* [2] */
		"File type",
		'TNAM',
		/* [3] */
		"File type",
		'TNAM',
		/* [4] */
		"File extension",
		'PSTR',
		/* [5] */
		"MIME type",
		'PSTR',
		/* [6] */
		"Description",
		'PSTR'
	}
};

resource 'TMPL' (1235, "mitq") {
	{	/* array: 3 elements */
		/* [1] */
		"Queue size for 3 bit inverse table",
		'ULNG',
		/* [2] */
		"Queue size for 4 bit inverse table",
		'ULNG',
		/* [3] */
		"Queue size for 5 bit inverse table",
		'ULNG'
	}
};

resource 'TMPL' (1236, "MKEY") {
	{	/* array: 7 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"Items",
		'LSTC',
		/* [3] */
		"Menu Command",
		'TNAM',
		/* [4] */
		"Key (None = $00)",
		'CHAR',
		/* [5] */
		"Modifiers",
		'HBYT',
		/* [6] */
		"Glyph",
		'HWRD',
		/* [7] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1237, "mntb") {
	{	/* array: 5 elements */
		/* [1] */
		"Menu table",
		'LSTB',
		/* [2] */
		"Command number",
		'DWRD',
		/* [3] */
		"Menu ID",
		'DWRD',
		/* [4] */
		"Menu item",
		'DWRD',
		/* [5] */
		"",
		'LSTE'
	}
};

resource 'TMPL' (1238, "modm") {
	{	/* array: 22 elements */
		/* [1] */
		"Version",
		'KWRD',
		/* [2] */
		"Standard=1",
		'CASE',
		/* [3] */
		"1",
		'KEYB',
		/* [4] */
		"Reserved",
		'WB12',
		/* [5] */
		"Direct mode (baud buffered)",
		'WBIT',
		/* [6] */
		"Reserved",
		'WBIT',
		/* [7] */
		"Reserved",
		'WBIT',
		/* [8] */
		"Carrier Detect Signal provided",
		'WBIT',
		/* [9] */
		"Initialization String",
		'ESTR',
		/* [10] */
		"Ring Response String",
		'ESTR',
		/* [11] */
		"Preferred Baudrate",
		'DLNG',
		/* [12] */
		"None=0",
		'CASE',
		/* [13] */
		"Preferred Port",
		'ESTR',
		/* [14] */
		"None=",
		'CASE',
		/* [15] */
		"Preferred Handshake",
		'DWRD',
		/* [16] */
		"Any=0",
		'CASE',
		/* [17] */
		"None=1",
		'CASE',
		/* [18] */
		"Xon/Xoff=2",
		'CASE',
		/* [19] */
		"DTR/CTS=3",
		'CASE',
		/* [20] */
		"DTR=4",
		'CASE',
		/* [21] */
		"CTS=5",
		'CASE',
		/* [22] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1239, "mppc") {
	{	/* array: 3 elements */
		/* [1] */
		"Information passed to DRVR",
		'HLNG',
		/* [2] */
		"Override version number",
		'DBYT',
		/* [3] */
		"Reserved",
		'FBYT'
	}
};

resource 'TMPL' (1240, "MPSR") {
	{	/* array: 46 elements */
		/* [1] */
		"Type of data (by resource ID)",
		'KRID',
		/* [2] */
		"Edit state ID=1005",
		'CASE',
		/* [3] */
		"Marker list ID=1007",
		'CASE',
		/* [4] */
		"Window split ID=1008",
		'CASE',
		/* [5] */
		"1005",
		'KEYB',
		/* [6] */
		"Tab size",
		'DWRD',
		/* [7] */
		"Font name",
		'C020',
		/* [8] */
		"Tab char width",
		'DWRD',
		/* [9] */
		"Spaces per tab",
		'DWRD',
		/* [10] */
		"Open rect",
		'RECT',
		/* [11] */
		"Close rect",
		'RECT',
		/* [12] */
		"Last modification date",
		'MDAT',
		/* [13] */
		"Selection start",
		'DLNG',
		/* [14] */
		"Selection end",
		'DLNG',
		/* [15] */
		"Current position",
		'DLNG',
		/* [16] */
		"Auto indent",
		'BFLG',
		/* [17] */
		"Invisibles",
		'BFLG',
		/* [18] */
		"",
		'KEYE',
		/* [19] */
		"1007",
		'KEYB',
		/* [20] */
		"Count",
		'OCNT',
		/* [21] */
		"Markers",
		'LSTC',
		/* [22] */
		"Starting position of mark",
		'DLNG',
		/* [23] */
		"Ending position of mark",
		'DLNG',
		/* [24] */
		"Mark name",
		'PPST',
		/* [25] */
		"*****",
		'LSTE',
		/* [26] */
		"",
		'KEYE',
		/* [27] */
		"1008",
		'KEYB',
		/* [28] */
		"Open rectangle (zoomed out)",
		'RECT',
		/* [29] */
		"Closed rectangle (zoomed in)",
		'RECT',
		/* [30] */
		"Offset of UL corner of LR pane",
		'DLNG',
		/* [31] */
		"*****",
		'LSTB',
		/* [32] */
		"Orientation",
		'DBYT',
		/* [33] */
		"None=0",
		'CASE',
		/* [34] */
		"Row=1",
		'CASE',
		/* [35] */
		"Column=2",
		'CASE',
		/* [36] */
		"Pad",
		'FBYT',
		/* [37] */
		"Unused",
		'WBIT',
		/* [38] */
		"Level 4 pane split count",
		'WB03',
		/* [39] */
		"Level 3 pane split count",
		'WB03',
		/* [40] */
		"Level 2 pane split count",
		'WB03',
		/* [41] */
		"Level 1 pane split count",
		'WB03',
		/* [42] */
		"Level 0 pane split count",
		'WB03',
		/* [43] */
		"Offset from top or left of split",
		'DWRD',
		/* [44] */
		"First character position in the pane",
		'DLNG',
		/* [45] */
		"*****",
		'LSTE',
		/* [46] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1241, "mVal") {
	{	/* array: 2 elements */
		/* [1] */
		"\"AfterDark\" resource format",
		'DVDR',
		/* [2] */
		"Menu item selected - Decimal",
		'DWRD'
	}
};

resource 'TMPL' (1242, "mxbc") {
	{	/* array: 2 elements */
		/* [1] */
		"Background RGB color",
		'COLR',
		/* [2] */
		"Foreground RGB color",
		'COLR'
	}
};

resource 'TMPL' (1243, "mxbi") {
	{	/* array: 3 elements */
		/* [1] */
		"Number of traps recorded",
		'DWRD',
		/* [2] */
		"Number of PC lines shown",
		'DWRD',
		/* [3] */
		"Size of history buffer",
		'DWRD'
	}
};

resource 'TMPL' (1244, "mxbm") {
	{	/* array: 5 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"List of macros",
		'LSTC',
		/* [3] */
		"Macro name",
		'PSTR',
		/* [4] */
		"Expansion",
		'PSTR',
		/* [5] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1245, "mxpr") {
	{	/* array: 16 elements */
		/* [1] */
		"Version",
		'HWRD',
		/* [2] */
		"Never checksum MacsBug code",
		'LBIT',
		/* [3] */
		"Only checksum code on entry",
		'LBIT',
		/* [4] */
		"Don't swap screen if stepping",
		'LBIT',
		/* [5] */
		"Don't auto propagate PPC exceptions",
		'LBIT',
		/* [6] */
		"Use immediate video driver calls",
		'LBIT',
		/* [7] */
		"Don't swap display bit depth",
		'LBIT',
		/* [8] */
		"Don't colorize text",
		'LBIT',
		/* [9] */
		"Relax PPC embedded symbol limits",
		'LBIT',
		/* [10] */
		"Don't use simplified PPC mnemonics",
		'LBIT',
		/* [11] */
		"Reserved",
		'LB21',
		/* [12] */
		"Write-protect MacsBug's code",
		'LBIT',
		/* [13] */
		"Debug - allocate slop from BufPtr",
		'LBIT',
		/* [14] */
		"Reserved long 1",
		'HLNG',
		/* [15] */
		"Reserved long 2",
		'HLNG',
		/* [16] */
		"Reserved long 3",
		'HLNG'
	}
};

resource 'TMPL' (1246, "mxst") {
	{	/* array: 12 elements */
		/* [1] */
		"Version",
		'HWRD',
		/* [2] */
		"A-Trap",
		'HWRD',
		/* [3] */
		"Trap mask",
		'HWRD',
		/* [4] */
		"Selector descriptor",
		'HLNG',
		/* [5] */
		"Count:",
		'OCNT',
		/* [6] */
		"Selectors",
		'LSTC',
		/* [7] */
		"Record size",
		'HWRD',
		/* [8] */
		"Selector flags",
		'HWRD',
		/* [9] */
		"Selector number",
		'HLNG',
		/* [10] */
		"Toolcall name",
		'PSTR',
		/* [11] */
		"align",
		'AWRD',
		/* [12] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1247, "mxwt") {
	{	/* array: 10 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"List of templates",
		'LSTC',
		/* [3] */
		"Template name",
		'PSTR',
		/* [4] */
		"Count:",
		'OCNT',
		/* [5] */
		"List of fields",
		'LSTC',
		/* [6] */
		"Field name",
		'PSTR',
		/* [7] */
		"Type name",
		'PSTR',
		/* [8] */
		"Number of fields of this type",
		'DWRD',
		/* [9] */
		"-----",
		'LSTE',
		/* [10] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1248, "nfnt") {
	{	/* array: 14 elements */
		/* [1] */
		"Font type",
		'HWRD',
		/* [2] */
		"First char",
		'DWRD',
		/* [3] */
		"Last char",
		'DWRD',
		/* [4] */
		"Width max",
		'DWRD',
		/* [5] */
		"Kern max",
		'DWRD',
		/* [6] */
		"NDescent",
		'DWRD',
		/* [7] */
		"Font rect width",
		'DWRD',
		/* [8] */
		"Char height",
		'DWRD',
		/* [9] */
		"OWT Loc",
		'DWRD',
		/* [10] */
		"Ascent",
		'DWRD',
		/* [11] */
		"Descent",
		'DWRD',
		/* [12] */
		"Leading",
		'DWRD',
		/* [13] */
		"Row words",
		'DWRD',
		/* [14] */
		"Font data",
		'HEXD'
	}
};

resource 'TMPL' (1249, "nmKy") {
	{	/* array: 11 elements */
		/* [1] */
		"\"Finale\" resource format",
		'DVDR',
		/* [2] */
		"Key Code - 0",
		'HWRD',
		/* [3] */
		"Key Code - 1",
		'HWRD',
		/* [4] */
		"Key Code - 2",
		'HWRD',
		/* [5] */
		"Key Code - 3",
		'HWRD',
		/* [6] */
		"Key Code - 4",
		'HWRD',
		/* [7] */
		"Key Code - 5",
		'HWRD',
		/* [8] */
		"Key Code - 6",
		'HWRD',
		/* [9] */
		"Key Code - 7",
		'HWRD',
		/* [10] */
		"Key Code - 8",
		'HWRD',
		/* [11] */
		"Key Code - 9",
		'HWRD'
	}
};

resource 'TMPL' (1250, "nrct") {
	{	/* array: 4 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"List of rects",
		'LSTC',
		/* [3] */
		"Rectangle",
		'RECT',
		/* [4] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1251, "Odds") {
	{	/* array: 5 elements */
		/* [1] */
		"Resource ID of Equivalent 'Sods'",
		'DLNG',
		/* [2] */
		"Count:",
		'LCNT',
		/* [3] */
		"List of dot extensions",
		'LSTC',
		/* [4] */
		"Dot extension",
		'PSTR',
		/* [5] */
		"",
		'LSTE'
	}
};

resource 'TMPL' (1252, "open") {
	{	/* array: 7 elements */
		/* [1] */
		"Application signature",
		'TNAM',
		/* [2] */
		"Filler",
		'FWRD',
		/* [3] */
		"File types in order of decreasing prefer"
		"ence",
		'DVDR',
		/* [4] */
		"Count:",
		'OCNT',
		/* [5] */
		"List of Supported file types",
		'LSTC',
		/* [6] */
		"File type",
		'TNAM',
		/* [7] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1253, "osiz") {
	{	/* array: 6 elements */
		/* [1] */
		"Don't open resource file",
		'LBIT',
		/* [2] */
		"Don't accept remote events",
		'LBIT',
		/* [3] */
		"Open with read/write permission",
		'LBIT',
		/* [4] */
		"Reserved",
		'LBIT',
		/* [5] */
		"Osax code in shared libraries",
		'LBIT',
		/* [6] */
		"Reserved",
		'LB27'
	}
};

resource 'TMPL' (1254, "otdr") {
	{	/* array: 10 elements */
		/* [1] */
		"Version (should be 1)",
		'DWRD',
		/* [2] */
		"Device info array",
		'LSTB',
		/* [3] */
		"Creator of preference file or...",
		'TNAM',
		/* [4] */
		"...name of preference file",
		'PSTR',
		/* [5] */
		"alignment",
		'AWRD',
		/* [6] */
		"Device abbreviation if appropriate",
		'PSTR',
		/* [7] */
		"alignment",
		'AWRD',
		/* [8] */
		"Device name",
		'PSTR',
		/* [9] */
		"alignment",
		'AWRD',
		/* [10] */
		"----",
		'LSTE'
	}
};

resource 'TMPL' (1255, "over") {
	{	/* array: 123 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"Messages being overriden",
		'LSTC',
		/* [3] */
		"Universal message ID",
		'DWRD',
		/* [4] */
		"Initialize=0",
		'CASE',
		/* [5] */
		"Shut down=1",
		'CASE',
		/* [6] */
		"Job idle=2",
		'CASE',
		/* [7] */
		"Job status=3",
		'CASE',
		/* [8] */
		"Printing event=4",
		'CASE',
		/* [9] */
		"Job default format dialog=5",
		'CASE',
		/* [10] */
		"Format dialog=6",
		'CASE',
		/* [11] */
		"Job print dialog=7",
		'CASE',
		/* [12] */
		"Filter panel event=8",
		'CASE',
		/* [13] */
		"Handle panel event=9",
		'CASE',
		/* [14] */
		"Parse page range=10",
		'CASE',
		/* [15] */
		"Default job=11",
		'CASE',
		/* [16] */
		"Default format=12",
		'CASE',
		/* [17] */
		"Default paper type=13",
		'CASE',
		/* [18] */
		"Default printer=14",
		'CASE',
		/* [19] */
		"Create spool file=15",
		'CASE',
		/* [20] */
		"Spool page=16",
		'CASE',
		/* [21] */
		"Spool data=17",
		'CASE',
		/* [22] */
		"Spool resource=18",
		'CASE',
		/* [23] */
		"Complete spool file=19",
		'CASE',
		/* [24] */
		"Count pages=20",
		'CASE',
		/* [25] */
		"De-spool page=21",
		'CASE',
		/* [26] */
		"De-spool data=22",
		'CASE',
		/* [27] */
		"De-spool resource=23",
		'CASE',
		/* [28] */
		"Close spool file=24",
		'CASE',
		/* [29] */
		"Start job=25",
		'CASE',
		/* [30] */
		"Finish job=26",
		'CASE',
		/* [31] */
		"Start page=27",
		'CASE',
		/* [32] */
		"Finish page=28",
		'CASE',
		/* [33] */
		"Print page=29",
		'CASE',
		/* [34] */
		"Setup image data=30",
		'CASE',
		/* [35] */
		"Image job=31",
		'CASE',
		/* [36] */
		"Image document=32",
		'CASE',
		/* [37] */
		"Image page=33",
		'CASE',
		/* [38] */
		"Render page=34",
		'CASE',
		/* [39] */
		"Create image file=35",
		'CASE',
		/* [40] */
		"Open connection=36",
		'CASE',
		/* [41] */
		"Close connection=37",
		'CASE',
		/* [42] */
		"Start send page=38",
		'CASE',
		/* [43] */
		"Finish send page=39",
		'CASE',
		/* [44] */
		"Write data=40",
		'CASE',
		/* [45] */
		"Buffer data=41",
		'CASE',
		/* [46] */
		"Dump buffer=42",
		'CASE',
		/* [47] */
		"Free buffer=43",
		'CASE',
		/* [48] */
		"Check status=44",
		'CASE',
		/* [49] */
		"Get device status=45",
		'CASE',
		/* [50] */
		"Fetch tagged data=46",
		'CASE',
		/* [51] */
		"Get DTP menu list=47",
		'CASE',
		/* [52] */
		"DTP menu select=48",
		'CASE',
		/* [53] */
		"DTP menu event filter=49",
		'CASE',
		/* [54] */
		"Job format mode query=50",
		'CASE',
		/* [55] */
		"Write status to DTP window=51",
		'CASE',
		/* [56] */
		"Initialize status alert=52",
		'CASE',
		/* [57] */
		"Handle alert status=53",
		'CASE',
		/* [58] */
		"Handle alert event=54",
		'CASE',
		/* [59] */
		"Clean up start job=55",
		'CASE',
		/* [60] */
		"Clean up start page=56",
		'CASE',
		/* [61] */
		"Clean up open connection=57",
		'CASE',
		/* [62] */
		"Clean up start send page=58",
		'CASE',
		/* [63] */
		"Default desktop printer=59",
		'CASE',
		/* [64] */
		"Capture output device=60",
		'CASE',
		/* [65] */
		"Open connection retry=61",
		'CASE',
		/* [66] */
		"Examine spool file=62",
		'CASE',
		/* [67] */
		"Finish send plane=63",
		'CASE',
		/* [68] */
		"Does paper fit=64",
		'CASE',
		/* [69] */
		"Chooser message=65",
		'CASE',
		/* [70] */
		"Find printer profile=66",
		'CASE',
		/* [71] */
		"Find format profile=67",
		'CASE',
		/* [72] */
		"Set printer profile=68",
		'CASE',
		/* [73] */
		"Set format profile=69",
		'CASE',
		/* [74] */
		"PrOpenDoc=0",
		'CASE',
		/* [75] */
		"PrCloseDoc=1",
		'CASE',
		/* [76] */
		"PrOpenPage=3",
		'CASE',
		/* [77] */
		"PrClosePage=4",
		'CASE',
		/* [78] */
		"PrintDefault=4",
		'CASE',
		/* [79] */
		"PrStlDialog=5",
		'CASE',
		/* [80] */
		"PrJobDialog=6",
		'CASE',
		/* [81] */
		"PrStlInit=7",
		'CASE',
		/* [82] */
		"PrJobInit=8",
		'CASE',
		/* [83] */
		"PrDlgMain=9",
		'CASE',
		/* [84] */
		"PrValidate=10",
		'CASE',
		/* [85] */
		"PrJobMerge=11",
		'CASE',
		/* [86] */
		"PrGeneral=12",
		'CASE',
		/* [87] */
		"ConvertPrinterRecordTo=13",
		'CASE',
		/* [88] */
		"ConvertPrinterRecordFrom=14",
		'CASE',
		/* [89] */
		"PrintRecordToJob=15",
		'CASE',
		/* [90] */
		"Raster Data in=0",
		'CASE',
		/* [91] */
		"Raster Line feed=1",
		'CASE',
		/* [92] */
		"Raster Package bitmap=2",
		'CASE',
		/* [93] */
		"PS Query printer=0",
		'CASE',
		/* [94] */
		"PS Initialize printer=1",
		'CASE',
		/* [95] */
		"PS Reset printer=2",
		'CASE',
		/* [96] */
		"PS Exit server=3",
		'CASE',
		/* [97] */
		"PS Get status text=4",
		'CASE',
		/* [98] */
		"PS Get printer text=5",
		'CASE',
		/* [99] */
		"PS Scan status text=6",
		'CASE',
		/* [100] */
		"PS Scan printer text=7",
		'CASE',
		/* [101] */
		"PS Get document procset list=8",
		'CASE',
		/* [102] */
		"PS Download procset list=9",
		'CASE',
		/* [103] */
		"PS Get printer glyphs information=10",
		'CASE',
		/* [104] */
		"PS Stream font=11",
		'CASE',
		/* [105] */
		"PS Do document header=12",
		'CASE',
		/* [106] */
		"PS Do document setup=13",
		'CASE',
		/* [107] */
		"PS Do document trailer=14",
		'CASE',
		/* [108] */
		"PS Do page setup=15",
		'CASE',
		/* [109] */
		"PS Do select paper type=16",
		'CASE',
		/* [110] */
		"PS Do page trailer=17",
		'CASE',
		/* [111] */
		"PS Eject page=18",
		'CASE',
		/* [112] */
		"PS Process shape=19",
		'CASE',
		/* [113] */
		"Vector Package data=0",
		'CASE',
		/* [114] */
		"Vector Load pens=1",
		'CASE',
		/* [115] */
		"Vectorize shape=2",
		'CASE',
		/* [116] */
		"Reserved",
		'WB04',
		/* [117] */
		"For drivers, the resource ID is an offse"
		"t from -27648",
		'DVDR',
		/* [118] */
		"For extensions, the resource ID is an of"
		"fset from -27136",
		'DVDR',
		/* [119] */
		"Dispatch resource ID",
		'WB12',
		/* [120] */
		"Code offset (start at 4 and add 4 for ea"
		"ch)",
		'HWRD',
		/* [121] */
		"Something",
		'DLNG',
		/* [122] */
		"Usual=-1",
		'CASE',
		/* [123] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1256, "PANE") {
	{	/* array: 51 elements */
		/* [1] */
		"\"MacZoop\" resource format",
		'DVDR',
		/* [2] */
		"Version",
		'KWRD',
		/* [3] */
		"latestVersion=0",
		'CASE',
		/* [4] */
		"0",
		'KEYB',
		/* [5] */
		"Count:",
		'OCNT',
		/* [6] */
		"Item extension",
		'LSTC',
		/* [7] */
		"Has item info",
		'KWRD',
		/* [8] */
		"skipItem=0",
		'CASE',
		/* [9] */
		"dataItem=1",
		'CASE',
		/* [10] */
		"0",
		'KEYB',
		/* [11] */
		"No information for this item",
		'DVDR',
		/* [12] */
		"",
		'KEYE',
		/* [13] */
		"1",
		'KEYB',
		/* [14] */
		"Pane Type",
		'TNAM',
		/* [15] */
		"Push Button=butt",
		'CASE',
		/* [16] */
		"Check Box=chek",
		'CASE',
		/* [17] */
		"Radio Button=radi",
		'CASE',
		/* [18] */
		"Control Resource=cntl",
		'CASE',
		/* [19] */
		"Static Text=stat",
		'CASE',
		/* [20] */
		"Editable Text=edit",
		'CASE',
		/* [21] */
		"Picture=pict",
		'CASE',
		/* [22] */
		"Icon=icon",
		'CASE',
		/* [23] */
		"-=????",
		'CASE',
		/* [24] */
		"Progress Bar=PBAR",
		'CASE',
		/* [25] */
		"List Box=LIST",
		'CASE',
		/* [26] */
		"Scrollable Text Field=TEXT",
		'CASE',
		/* [27] */
		"Icon List Box=ICLB",
		'CASE',
		/* [28] */
		"Color Popup Menu=CPOP",
		'CASE',
		/* [29] */
		"Counter Display=DIGI",
		'CASE',
		/* [30] */
		"Clock Display=CLOC",
		'CASE',
		/* [31] */
		"Tab Box [Panes]=TABS",
		'CASE',
		/* [32] */
		"Dividing Line [Panes]=LINE",
		'CASE',
		/* [33] */
		"Cluster Box [Panes]=CLST",
		'CASE',
		/* [34] */
		"Window Header [Panes]=HEAD",
		'CASE',
		/* [35] */
		"Window Placard [Panes]=PLAC",
		'CASE',
		/* [36] */
		"Popup Menu [Panes]=POPM",
		'CASE',
		/* [37] */
		"Bevel Button [Panes]=BEVL",
		'CASE',
		/* [38] */
		"First param",
		'DLNG',
		/* [39] */
		"Second param",
		'DLNG',
		/* [40] */
		"Pane ID",
		'DLNG',
		/* [41] */
		"Reserved",
		'BB03',
		/* [42] */
		"Align unspecified on center",
		'BBIT',
		/* [43] */
		"Align on right",
		'BBIT',
		/* [44] */
		"Align on bottom",
		'BBIT',
		/* [45] */
		"Align on left",
		'BBIT',
		/* [46] */
		"Align on top",
		'BBIT',
		/* [47] */
		"Pane name",
		'PSTR',
		/* [48] */
		"Ballon help",
		'PSTR',
		/* [49] */
		"",
		'KEYE',
		/* [50] */
		"*****",
		'LSTE',
		/* [51] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1257, "PANI") {
	{	/* array: 12 elements */
		/* [1] */
		"Version",
		'DLNG',
		/* [2] */
		"Options",
		'HLNG',
		/* [3] */
		"Animation Bounces - 0x00000001",
		'DVDR',
		/* [4] */
		"Picture resource ID",
		'DWRD',
		/* [5] */
		"Masking resource ID",
		'DWRD',
		/* [6] */
		"Number of animations",
		'DWRD',
		/* [7] */
		"Ticks between animation",
		'DWRD',
		/* [8] */
		"Pictures per row",
		'DWRD',
		/* [9] */
		"Reserved1",
		'DWRD',
		/* [10] */
		"Reserved2",
		'DWRD',
		/* [11] */
		"Reserved3",
		'DWRD',
		/* [12] */
		"Picture rect",
		'RECT'
	}
};

resource 'TMPL' (1258, "panl") {
	{	/* array: 15 elements */
		/* [1] */
		"Bounds",
		'RECT',
		/* [2] */
		"Visible",
		'BFLG',
		/* [3] */
		"Enabled",
		'BFLG',
		/* [4] */
		"Enum flags",
		'HLNG',
		/* [5] */
		"MatchTypeHow",
		'DWRD',
		/* [6] */
		"Match all=0",
		'CASE',
		/* [7] */
		"Exact match=1",
		'CASE',
		/* [8] */
		"Begins with=2",
		'CASE',
		/* [9] */
		"Ends with=3",
		'CASE',
		/* [10] */
		"Contains=4",
		'CASE',
		/* [11] */
		"Reference constant",
		'DLNG',
		/* [12] */
		"Count:",
		'OCNT',
		/* [13] */
		"List of Resource types",
		'LSTC',
		/* [14] */
		"'rtyp' resource ID",
		'RSID',
		/* [15] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1259, "PAPA") {
	{	/* array: 5 elements */
		/* [1] */
		"Name",
		'PSTR',
		/* [2] */
		"Type",
		'PSTR',
		/* [3] */
		"Zone",
		'PSTR',
		/* [4] */
		"Address Block",
		'HLNG',
		/* [5] */
		"Dump",
		'HEXD'
	}
};

resource 'TMPL' (1260, "PAT ") {
	{	/* array: 1 elements */
		/* [1] */
		"Pattern",
		'H008'
	}
};

resource 'TMPL' (1261, "PAT#") {
	{	/* array: 4 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"Patterns",
		'LSTC',
		/* [3] */
		"Pattern",
		'H008',
		/* [4] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1262, "PBUT") {
	{	/* array: 14 elements */
		/* [1] */
		"Image \"PICT\" Resource ID",
		'RSID',
		/* [2] */
		"Mask \"PICT\" Resource ID",
		'RSID',
		/* [3] */
		"Reserved",
		'LB30',
		/* [4] */
		"Supports Rollover",
		'LB01',
		/* [5] */
		"Has Deep Mask",
		'LB01',
		/* [6] */
		"Fixed left size",
		'UBYT',
		/* [7] */
		"Fixed right size",
		'UBYT',
		/* [8] */
		"Reserved",
		'F004',
		/* [9] */
		"Count:",
		'OCNT',
		/* [10] */
		"Buttons",
		'LSTC',
		/* [11] */
		"Inactive",
		'RECT',
		/* [12] */
		"Active",
		'RECT',
		/* [13] */
		"Pressed",
		'RECT',
		/* [14] */
		"",
		'LSTE'
	}
};

resource 'TMPL' (1263, "pdip") {
	{	/* array: 26 elements */
		/* [1] */
		"PostScript language level",
		'DWRD',
		/* [2] */
		"Original=1",
		'CASE',
		/* [3] */
		"Level 2=2",
		'CASE',
		/* [4] */
		"Device color space",
		'DLNG',
		/* [5] */
		"Render option flag bits",
		'DVDR',
		/* [6] */
		"Reserved",
		'LB24',
		/* [7] */
		"Use level 2 color",
		'LBIT',
		/* [8] */
		"User charpath 1",
		'LBIT',
		/* [9] */
		"Flatten clip path",
		'LBIT',
		/* [10] */
		"Text clips to path",
		'LBIT',
		/* [11] */
		"Portable PostScript",
		'LBIT',
		/* [12] */
		"Bounding boxes option",
		'LBIT',
		/* [13] */
		"Needs comments",
		'LBIT',
		/* [14] */
		"Needs hex",
		'LBIT',
		/* [15] */
		"Path limit",
		'DWRD',
		/* [16] */
		"gsave limit",
		'DWRD',
		/* [17] */
		"Op stack limit",
		'DWRD',
		/* [18] */
		"Font types",
		'DVDR',
		/* [19] */
		"Reserved",
		'LB26',
		/* [20] */
		"Portable stream",
		'LBIT',
		/* [21] */
		"Type 42 GX stream",
		'LBIT',
		/* [22] */
		"Type 42 stream",
		'LBIT',
		/* [23] */
		"Type 3 stream",
		'LBIT',
		/* [24] */
		"Type 1 stream",
		'LBIT',
		/* [25] */
		"TrueType stream",
		'LBIT',
		/* [26] */
		"Printer VM",
		'DLNG'
	}
};

resource 'TMPL' (1264, "Pers") {
	{	/* array: 17 elements */
		/* [1] */
		"\"Eudora\" resource format",
		'DVDR',
		/* [2] */
		"Personality hash",
		'HLNG',
		/* [3] */
		"Version",
		'DWRD',
		/* [4] */
		"Resource ID",
		'DWRD',
		/* [5] */
		"Resource stamp Hi",
		'CHAR',
		/* [6] */
		"Resource stamp Lo",
		'CHAR',
		/* [7] */
		"Name",
		'P01F',
		/* [8] */
		"Password",
		'P01F',
		/* [9] */
		"Dialup password",
		'P01F',
		/* [10] */
		"PopSecure",
		'HBYT',
		/* [11] */
		"Dirty",
		'HBYT',
		/* [12] */
		"Internal use",
		'HLNG',
		/* [13] */
		"Reserved",
		'BB08',
		/* [14] */
		"Reserved",
		'H003',
		/* [15] */
		"Number queued messages",
		'DLNG',
		/* [16] */
		"Check ticks",
		'DLNG',
		/* [17] */
		"Check interval ticks",
		'DLNG'
	}
};

resource 'TMPL' (1265, "pfil") {
	{	/* array: 4 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"Output file formats",
		'LSTC',
		/* [3] */
		"Format popup menu item",
		'PSTR',
		/* [4] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1266, "pfnt") {
	{	/* array: 166 elements */
		/* [1] */
		"Memory usage",
		'DLNG',
		/* [2] */
		"ROM font=0",
		'CASE',
		/* [3] */
		"Character set type",
		'KHLG',
		/* [4] */
		"Adobe=$00000000",
		'CASE',
		/* [5] */
		"Apple=$00010000",
		'CASE',
		/* [6] */
		"Equivalent to Mac=$00020000",
		'CASE',
		/* [7] */
		"Encoded=$00030000",
		'CASE',
		/* [8] */
		"$00000000",
		'KEYB',
		/* [9] */
		"",
		'KEYE',
		/* [10] */
		"$00010000",
		'KEYB',
		/* [11] */
		"Glyph data",
		'LHEX',
		/* [12] */
		"",
		'KEYE',
		/* [13] */
		"$00020000",
		'KEYB',
		/* [14] */
		"",
		'KEYE',
		/* [15] */
		"$00030000",
		'KEYB',
		/* [16] */
		"Platform",
		'DLNG',
		/* [17] */
		"Script",
		'DLNG',
		/* [18] */
		"System script=-1",
		'CASE',
		/* [19] */
		"Current script=-2",
		'CASE',
		/* [20] */
		"Roman=0",
		'CASE',
		/* [21] */
		"Japanese=1",
		'CASE',
		/* [22] */
		"Traditional Chinese=2",
		'CASE',
		/* [23] */
		"Korean=3",
		'CASE',
		/* [24] */
		"Arabic=4",
		'CASE',
		/* [25] */
		"Hebrew=5",
		'CASE',
		/* [26] */
		"Greek=6",
		'CASE',
		/* [27] */
		"Cyrillic=7",
		'CASE',
		/* [28] */
		"Right/Left Symbols=8",
		'CASE',
		/* [29] */
		"Devanagari=9",
		'CASE',
		/* [30] */
		"Gurmukhi=10",
		'CASE',
		/* [31] */
		"Gujarati=11",
		'CASE',
		/* [32] */
		"Oriya=12",
		'CASE',
		/* [33] */
		"Bengali=13",
		'CASE',
		/* [34] */
		"Tamil=14",
		'CASE',
		/* [35] */
		"Telugu=15",
		'CASE',
		/* [36] */
		"Kannada=16",
		'CASE',
		/* [37] */
		"Malayalam=17",
		'CASE',
		/* [38] */
		"Sinhalese=18",
		'CASE',
		/* [39] */
		"Burmese=19",
		'CASE',
		/* [40] */
		"Khmer=20",
		'CASE',
		/* [41] */
		"Thai=21",
		'CASE',
		/* [42] */
		"Laotian=22",
		'CASE',
		/* [43] */
		"Georgian=23",
		'CASE',
		/* [44] */
		"Armenian=24",
		'CASE',
		/* [45] */
		"Simplified Chinese=25",
		'CASE',
		/* [46] */
		"Tibetan=26",
		'CASE',
		/* [47] */
		"Mongolian=27",
		'CASE',
		/* [48] */
		"Geez/Ethiopic=28",
		'CASE',
		/* [49] */
		"East European Roman=29",
		'CASE',
		/* [50] */
		"Vietnamese=30",
		'CASE',
		/* [51] */
		"Extended Arabic=31",
		'CASE',
		/* [52] */
		"Uninterpreted Symbols=32",
		'CASE',
		/* [53] */
		"Language",
		'DLNG',
		/* [54] */
		"English=0",
		'CASE',
		/* [55] */
		"French=1",
		'CASE',
		/* [56] */
		"German==2",
		'CASE',
		/* [57] */
		"Italian=3",
		'CASE',
		/* [58] */
		"Dutch=4",
		'CASE',
		/* [59] */
		"Swedish=5",
		'CASE',
		/* [60] */
		"Spanish=6",
		'CASE',
		/* [61] */
		"Danish=7",
		'CASE',
		/* [62] */
		"Portuguese=8",
		'CASE',
		/* [63] */
		"Norwegian=9",
		'CASE',
		/* [64] */
		"Hebrew=10",
		'CASE',
		/* [65] */
		"Japanese=11",
		'CASE',
		/* [66] */
		"Arabic=12",
		'CASE',
		/* [67] */
		"Finnish=13",
		'CASE',
		/* [68] */
		"Greek=14",
		'CASE',
		/* [69] */
		"Icelandic=15",
		'CASE',
		/* [70] */
		"Maltese=16",
		'CASE',
		/* [71] */
		"Turkish=17",
		'CASE',
		/* [72] */
		"Croatian=18",
		'CASE',
		/* [73] */
		"TradChinese=19",
		'CASE',
		/* [74] */
		"Urdu=20",
		'CASE',
		/* [75] */
		"Hindi=21",
		'CASE',
		/* [76] */
		"Thai=22",
		'CASE',
		/* [77] */
		"Korean=23",
		'CASE',
		/* [78] */
		"Lithuanian=24",
		'CASE',
		/* [79] */
		"Polish=25",
		'CASE',
		/* [80] */
		"Hungarian=26",
		'CASE',
		/* [81] */
		"Estonian=27",
		'CASE',
		/* [82] */
		"Lettish=28",
		'CASE',
		/* [83] */
		"Latvian=28",
		'CASE',
		/* [84] */
		"Lapponian=29",
		'CASE',
		/* [85] */
		"Lappish=29",
		'CASE',
		/* [86] */
		"Faeroese=30",
		'CASE',
		/* [87] */
		"Farsi=31",
		'CASE',
		/* [88] */
		"Persian=31",
		'CASE',
		/* [89] */
		"Russian=32",
		'CASE',
		/* [90] */
		"SimpChinese=33",
		'CASE',
		/* [91] */
		"Flemish=34",
		'CASE',
		/* [92] */
		"Irish=35",
		'CASE',
		/* [93] */
		"Albanian=36",
		'CASE',
		/* [94] */
		"Romanian=37",
		'CASE',
		/* [95] */
		"Czech=38",
		'CASE',
		/* [96] */
		"Slovak=39",
		'CASE',
		/* [97] */
		"Slovenian=40",
		'CASE',
		/* [98] */
		"Yiddish=41",
		'CASE',
		/* [99] */
		"Serbian=42",
		'CASE',
		/* [100] */
		"Macedonian=43",
		'CASE',
		/* [101] */
		"Bulgarian=44",
		'CASE',
		/* [102] */
		"Ukrainian=45",
		'CASE',
		/* [103] */
		"Byelorussian=46",
		'CASE',
		/* [104] */
		"Uzbek=47",
		'CASE',
		/* [105] */
		"Kazakh=48",
		'CASE',
		/* [106] */
		"Azerbaijani=49",
		'CASE',
		/* [107] */
		"AzerbaijanAr=50",
		'CASE',
		/* [108] */
		"Armenian=51",
		'CASE',
		/* [109] */
		"Georgian=52",
		'CASE',
		/* [110] */
		"Moldavian=53",
		'CASE',
		/* [111] */
		"Kirghiz=54",
		'CASE',
		/* [112] */
		"Tajiki=55",
		'CASE',
		/* [113] */
		"Turkmen=56",
		'CASE',
		/* [114] */
		"Mongolian=57",
		'CASE',
		/* [115] */
		"MongolianCyr=58",
		'CASE',
		/* [116] */
		"Pashto=59",
		'CASE',
		/* [117] */
		"Kurdish=60",
		'CASE',
		/* [118] */
		"Kashmiri=61",
		'CASE',
		/* [119] */
		"Sindhi=62",
		'CASE',
		/* [120] */
		"Tibetan=63",
		'CASE',
		/* [121] */
		"Nepali=64",
		'CASE',
		/* [122] */
		"Sanskrit=65",
		'CASE',
		/* [123] */
		"Marathi=66",
		'CASE',
		/* [124] */
		"Bengali=67",
		'CASE',
		/* [125] */
		"Assamese=68",
		'CASE',
		/* [126] */
		"Gujarati=69",
		'CASE',
		/* [127] */
		"Punjabi=70",
		'CASE',
		/* [128] */
		"Oriya=71",
		'CASE',
		/* [129] */
		"Malayalam=72",
		'CASE',
		/* [130] */
		"Kannada=73",
		'CASE',
		/* [131] */
		"Tamil=74",
		'CASE',
		/* [132] */
		"Telugu=75",
		'CASE',
		/* [133] */
		"Sinhalese=76",
		'CASE',
		/* [134] */
		"Burmese=77",
		'CASE',
		/* [135] */
		"Khmer=78",
		'CASE',
		/* [136] */
		"Lao=79",
		'CASE',
		/* [137] */
		"Vietnamese=80",
		'CASE',
		/* [138] */
		"Indonesian=81",
		'CASE',
		/* [139] */
		"Tagalog=82",
		'CASE',
		/* [140] */
		"MalayRoman=83",
		'CASE',
		/* [141] */
		"MalayArabic=84",
		'CASE',
		/* [142] */
		"Amharic=85",
		'CASE',
		/* [143] */
		"Tigrinya=86",
		'CASE',
		/* [144] */
		"Galla=87",
		'CASE',
		/* [145] */
		"Oromo=87",
		'CASE',
		/* [146] */
		"Somali=88",
		'CASE',
		/* [147] */
		"Swahili=89",
		'CASE',
		/* [148] */
		"Ruanda=90",
		'CASE',
		/* [149] */
		"Rundi=91",
		'CASE',
		/* [150] */
		"Chewa=92",
		'CASE',
		/* [151] */
		"Malagasy=93",
		'CASE',
		/* [152] */
		"Esperanto=94",
		'CASE',
		/* [153] */
		"Welsh=128",
		'CASE',
		/* [154] */
		"Basque=129",
		'CASE',
		/* [155] */
		"Catalan=130",
		'CASE',
		/* [156] */
		"Latin=131",
		'CASE',
		/* [157] */
		"Quechua=132",
		'CASE',
		/* [158] */
		"Guarani=133",
		'CASE',
		/* [159] */
		"Aymara=134",
		'CASE',
		/* [160] */
		"Tatar=135",
		'CASE',
		/* [161] */
		"Uighur=136",
		'CASE',
		/* [162] */
		"Dzongkha=137",
		'CASE',
		/* [163] */
		"JavaneseRom=138",
		'CASE',
		/* [164] */
		"SundaneseRom=139",
		'CASE',
		/* [165] */
		"Unspecified=32767",
		'CASE',
		/* [166] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1267, "PgSz") {
	{	/* array: 6 elements */
		/* [1] */
		"\"Finale\" resource format",
		'DVDR',
		/* [2] */
		"Width",
		'DLNG',
		/* [3] */
		"Height",
		'DLNG',
		/* [4] */
		"Menu name",
		'CSTR',
		/* [5] */
		"PostScript command",
		'CSTR',
		/* [6] */
		"Command definition",
		'CSTR'
	}
};

resource 'TMPL' (1268, "picb") {
	{	/* array: 5 elements */
		/* [1] */
		"Version",
		'DWRD',
		/* [2] */
		"'PICT' resource ID",
		'RSID',
		/* [3] */
		"Vertical shift",
		'DWRD',
		/* [4] */
		"Horizontal shift",
		'DWRD',
		/* [5] */
		"Reserved",
		'FLNG'
	}
};

resource 'TMPL' (1269, "PICK") {
	{	/* array: 9 elements */
		/* [1] */
		"Which type",
		'TNAM',
		/* [2] */
		"Use color?",
		'DBYT',
		/* [3] */
		"Picker type",
		'DBYT',
		/* [4] */
		"View by",
		'DBYT',
		/* [5] */
		"Filler byte",
		'FBYT',
		/* [6] */
		"Vert cell size",
		'DWRD',
		/* [7] */
		"Horiz cell size",
		'DWRD',
		/* [8] */
		"LDEF type",
		'TNAM',
		/* [9] */
		"Option String",
		'PSTR'
	}
};

resource 'TMPL' (1270, "PICT") {
	{	/* array: 3 elements */
		/* [1] */
		"Picture size (vers 1)",
		'UWRD',
		/* [2] */
		"Picture frame",
		'RECT',
		/* [3] */
		"Opcodes",
		'HEXD'
	}
};

resource 'TMPL' (1271, "PLGN") {
	{	/* array: 6 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"List of Libraries",
		'LSTC',
		/* [3] */
		"Plug-In Type",
		'TNAM',
		/* [4] */
		"Plug-In SubType",
		'TNAM',
		/* [5] */
		"Library Name",
		'ESTR',
		/* [6] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1272, "PLob") {
	{	/* array: 229 elements */
		/* [1] */
		"Version Number",
		'DWRD',
		/* [2] */
		"CW10=1",
		'CASE',
		/* [3] */
		"*****",
		'LSTB',
		/* [4] */
		"Object type",
		'KTYP',
		/* [5] */
		"Object data=objd",
		'CASE',
		/* [6] */
		"Begin sub-object list=begs",
		'CASE',
		/* [7] */
		"End sub-object list=ends",
		'CASE',
		/* [8] */
		"Comment=comm",
		'CASE',
		/* [9] */
		"End of list=end.",
		'CASE',
		/* [10] */
		"objd",
		'KEYB',
		/* [11] */
		"Number of bytes in following data",
		'LSIZ',
		/* [12] */
		"Data type",
		'KTYP',
		/* [13] */
		"Form=tFRM",
		'CASE',
		/* [14] */
		"Button=tBTN",
		'CASE',
		/* [15] */
		"Repeating Button=tREP",
		'CASE',
		/* [16] */
		"Push Button=tPBN",
		'CASE',
		/* [17] */
		"CheckBox=tCBX",
		'CASE',
		/* [18] */
		"Popup Trigger=tPUT",
		'CASE',
		/* [19] */
		"Selector Trigger=tSLT",
		'CASE',
		/* [20] */
		"Label=tLBL",
		'CASE',
		/* [21] */
		"List=tLST",
		'CASE',
		/* [22] */
		"Field=tFLD",
		'CASE',
		/* [23] */
		"Scrollbar=tSCL",
		'CASE',
		/* [24] */
		"Form Bitmap=tFBM",
		'CASE',
		/* [25] */
		"Table=tTBL",
		'CASE',
		/* [26] */
		"Gadget=tGDT",
		'CASE',
		/* [27] */
		"Grafitti Indicator=tGSI",
		'CASE',
		/* [28] */
		"Group=tGRP",
		'CASE',
		/* [29] */
		"Null=null",
		'CASE',
		/* [30] */
		"tFRM",
		'KEYB',
		/* [31] */
		"Left",
		'DWRD',
		/* [32] */
		"Top",
		'DWRD',
		/* [33] */
		"Width",
		'DWRD',
		/* [34] */
		"Height",
		'DWRD',
		/* [35] */
		"Usable",
		'BOOL',
		/* [36] */
		"Modal",
		'BOOL',
		/* [37] */
		"Save behind",
		'BOOL',
		/* [38] */
		"Unused",
		'DWRD',
		/* [39] */
		"Unused",
		'DWRD',
		/* [40] */
		"Form ID",
		'DWRD',
		/* [41] */
		"Help Rsc ID",
		'DWRD',
		/* [42] */
		"Menu Rsc ID",
		'DWRD',
		/* [43] */
		"Default Button ID",
		'DWRD',
		/* [44] */
		"",
		'FWRD',
		/* [45] */
		"",
		'FWRD',
		/* [46] */
		"Form Title",
		'CSTR',
		/* [47] */
		"PalmOS Version",
		'DWRD',
		/* [48] */
		"",
		'KEYE',
		/* [49] */
		"tBTN",
		'KEYB',
		/* [50] */
		"Button ID",
		'DWRD',
		/* [51] */
		"Left",
		'DWRD',
		/* [52] */
		"Top",
		'DWRD',
		/* [53] */
		"Width",
		'DWRD',
		/* [54] */
		"Height",
		'DWRD',
		/* [55] */
		"Usable",
		'BOOL',
		/* [56] */
		"Left anchor",
		'BOOL',
		/* [57] */
		"Frame",
		'BOOL',
		/* [58] */
		"Non-bold frame",
		'BOOL',
		/* [59] */
		"Font",
		'DBYT',
		/* [60] */
		"Label",
		'CSTR',
		/* [61] */
		"",
		'KEYE',
		/* [62] */
		"tREP",
		'KEYB',
		/* [63] */
		"Button ID",
		'DWRD',
		/* [64] */
		"Left",
		'DWRD',
		/* [65] */
		"Top",
		'DWRD',
		/* [66] */
		"Width",
		'DWRD',
		/* [67] */
		"Height",
		'DWRD',
		/* [68] */
		"Usable",
		'BOOL',
		/* [69] */
		"Left anchor",
		'BOOL',
		/* [70] */
		"Frame",
		'BOOL',
		/* [71] */
		"Non-bold frame",
		'BOOL',
		/* [72] */
		"Font",
		'DBYT',
		/* [73] */
		"Label",
		'CSTR',
		/* [74] */
		"",
		'KEYE',
		/* [75] */
		"tPBN",
		'KEYB',
		/* [76] */
		"Push Button ID",
		'DWRD',
		/* [77] */
		"Left",
		'DWRD',
		/* [78] */
		"Top",
		'DWRD',
		/* [79] */
		"Width",
		'DWRD',
		/* [80] */
		"Height",
		'DWRD',
		/* [81] */
		"Usable",
		'BOOL',
		/* [82] */
		"Group ID",
		'DBYT',
		/* [83] */
		"Font",
		'DBYT',
		/* [84] */
		"Label",
		'CSTR',
		/* [85] */
		"",
		'KEYE',
		/* [86] */
		"tCBX",
		'KEYB',
		/* [87] */
		"Check Box ID",
		'DWRD',
		/* [88] */
		"Left",
		'DWRD',
		/* [89] */
		"Top",
		'DWRD',
		/* [90] */
		"Width",
		'DWRD',
		/* [91] */
		"Height",
		'DWRD',
		/* [92] */
		"Usable",
		'BOOL',
		/* [93] */
		"Selected",
		'BOOL',
		/* [94] */
		"Group ID",
		'DBYT',
		/* [95] */
		"Font",
		'DBYT',
		/* [96] */
		"Label",
		'ECST',
		/* [97] */
		"",
		'KEYE',
		/* [98] */
		"tPUT",
		'KEYB',
		/* [99] */
		"Popup Trigger ID",
		'DWRD',
		/* [100] */
		"Left",
		'DWRD',
		/* [101] */
		"Top",
		'DWRD',
		/* [102] */
		"Width",
		'DWRD',
		/* [103] */
		"Height",
		'DWRD',
		/* [104] */
		"Usable",
		'BOOL',
		/* [105] */
		"Left anchor",
		'BOOL',
		/* [106] */
		"Font",
		'DBYT',
		/* [107] */
		"Label",
		'ECST',
		/* [108] */
		"List ID ",
		'DWRD',
		/* [109] */
		"",
		'KEYE',
		/* [110] */
		"tSLT",
		'KEYB',
		/* [111] */
		"Selector Trigger ID",
		'DWRD',
		/* [112] */
		"Left",
		'DWRD',
		/* [113] */
		"Top",
		'DWRD',
		/* [114] */
		"Width",
		'DWRD',
		/* [115] */
		"Height",
		'DWRD',
		/* [116] */
		"Usable",
		'BOOL',
		/* [117] */
		"Left anchor",
		'BOOL',
		/* [118] */
		"Font",
		'DBYT',
		/* [119] */
		"Label",
		'ECST',
		/* [120] */
		"",
		'KEYE',
		/* [121] */
		"tLBL",
		'KEYB',
		/* [122] */
		"Label ID",
		'DWRD',
		/* [123] */
		"Left",
		'DWRD',
		/* [124] */
		"Top",
		'DWRD',
		/* [125] */
		"Usable",
		'BOOL',
		/* [126] */
		"Font ID",
		'DBYT',
		/* [127] */
		"Text",
		'CSTR',
		/* [128] */
		"",
		'KEYE',
		/* [129] */
		"tLST",
		'KEYB',
		/* [130] */
		"List ID",
		'DWRD',
		/* [131] */
		"Left",
		'DWRD',
		/* [132] */
		"Top",
		'DWRD',
		/* [133] */
		"Width",
		'DWRD',
		/* [134] */
		"Usable",
		'BOOL',
		/* [135] */
		"Font",
		'DBYT',
		/* [136] */
		"Filler1",
		'FBYT',
		/* [137] */
		"Visible Items",
		'DWRD',
		/* [138] */
		"Items",
		'OCNT',
		/* [139] */
		"*****",
		'LSTC',
		/* [140] */
		"Text",
		'CSTR',
		/* [141] */
		"*****",
		'LSTE',
		/* [142] */
		"",
		'KEYE',
		/* [143] */
		"tFLD",
		'KEYB',
		/* [144] */
		"Field ID",
		'DWRD',
		/* [145] */
		"Left",
		'DWRD',
		/* [146] */
		"Top",
		'DWRD',
		/* [147] */
		"Width",
		'DWRD',
		/* [148] */
		"Height",
		'DWRD',
		/* [149] */
		"Usable",
		'BOOL',
		/* [150] */
		"Editable",
		'BOOL',
		/* [151] */
		"Underlined",
		'BOOL',
		/* [152] */
		"Solid Underline",
		'FWRD',
		/* [153] */
		"Single Line",
		'BOOL',
		/* [154] */
		"Dynamic Size",
		'BOOL',
		/* [155] */
		"Left Justified",
		'BOOL',
		/* [156] */
		"Max chars",
		'DWRD',
		/* [157] */
		"Font",
		'DBYT',
		/* [158] */
		"Filler1",
		'FBYT',
		/* [159] */
		"Auto Shift",
		'BOOL',
		/* [160] */
		"Has Scroll Bar",
		'BOOL',
		/* [161] */
		"Numeric",
		'BOOL',
		/* [162] */
		"",
		'KEYE',
		/* [163] */
		"tSCL",
		'KEYB',
		/* [164] */
		"Scroll Bar ID",
		'DWRD',
		/* [165] */
		"Left",
		'DWRD',
		/* [166] */
		"Top",
		'DWRD',
		/* [167] */
		"Width",
		'DWRD',
		/* [168] */
		"Height",
		'DWRD',
		/* [169] */
		"Usable",
		'BOOL',
		/* [170] */
		"Value",
		'DWRD',
		/* [171] */
		"Minimum Value",
		'DWRD',
		/* [172] */
		"Maximum Value",
		'DWRD',
		/* [173] */
		"Page Size",
		'DWRD',
		/* [174] */
		"",
		'KEYE',
		/* [175] */
		"tFBM",
		'KEYB',
		/* [176] */
		"X Position",
		'DWRD',
		/* [177] */
		"y Position",
		'DWRD',
		/* [178] */
		"Bitmap Rsc ID",
		'DWRD',
		/* [179] */
		"Usable",
		'BOOL',
		/* [180] */
		"",
		'KEYE',
		/* [181] */
		"tTBL",
		'KEYB',
		/* [182] */
		"Table ID",
		'DWRD',
		/* [183] */
		"Left",
		'DWRD',
		/* [184] */
		"Top",
		'DWRD',
		/* [185] */
		"Width",
		'DWRD',
		/* [186] */
		"Height",
		'DWRD',
		/* [187] */
		"Editable",
		'BOOL',
		/* [188] */
		"reserved 1",
		'FWRD',
		/* [189] */
		"reserved 2",
		'FWRD',
		/* [190] */
		"reserved 3",
		'FWRD',
		/* [191] */
		"Rows",
		'DWRD',
		/* [192] */
		"Columns",
		'OCNT',
		/* [193] */
		"*****",
		'LSTC',
		/* [194] */
		"Column Width",
		'DWRD',
		/* [195] */
		"*****",
		'LSTE',
		/* [196] */
		"",
		'KEYE',
		/* [197] */
		"tGDT",
		'KEYB',
		/* [198] */
		"Gadget ID",
		'DWRD',
		/* [199] */
		"Left",
		'DWRD',
		/* [200] */
		"Top",
		'DWRD',
		/* [201] */
		"Width",
		'DWRD',
		/* [202] */
		"Height",
		'DWRD',
		/* [203] */
		"Usable",
		'BOOL',
		/* [204] */
		"",
		'KEYE',
		/* [205] */
		"tGSI",
		'KEYB',
		/* [206] */
		"x pos",
		'DWRD',
		/* [207] */
		"y pos",
		'DWRD',
		/* [208] */
		"",
		'KEYE',
		/* [209] */
		"tGRP",
		'KEYB',
		/* [210] */
		"Group ID",
		'DWRD',
		/* [211] */
		"",
		'KEYE',
		/* [212] */
		"null",
		'KEYB',
		/* [213] */
		"",
		'KEYE',
		/* [214] */
		"",
		'KEYB',
		/* [215] */
		"Unknown data",
		'HEXD',
		/* [216] */
		"",
		'KEYE',
		/* [217] */
		"",
		'SKPE',
		/* [218] */
		"",
		'KEYE',
		/* [219] */
		"begs",
		'KEYB',
		/* [220] */
		"",
		'KEYE',
		/* [221] */
		"ends",
		'KEYB',
		/* [222] */
		"",
		'KEYE',
		/* [223] */
		"comm",
		'KEYB',
		/* [224] */
		"Comment data",
		'LSHX',
		/* [225] */
		"",
		'KEYE',
		/* [226] */
		"end.",
		'KEYB',
		/* [227] */
		"This must be last object type in list",
		'DVDR',
		/* [228] */
		"",
		'KEYE',
		/* [229] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1273, "pltt") {
	{	/* array: 25 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"Reserved",
		'FLNG',
		/* [3] */
		"Reserved",
		'FWRD',
		/* [4] */
		"Reserved",
		'FLNG',
		/* [5] */
		"Reserved",
		'FLNG',
		/* [6] */
		"Colors",
		'LSTC',
		/* [7] */
		"Color",
		'COLR',
		/* [8] */
		"Unused",
		'WB02',
		/* [9] */
		"Inhibit on 8-bit color device",
		'WBIT',
		/* [10] */
		"Inhibit on 8-bit gray scale device",
		'WBIT',
		/* [11] */
		"Inhibit on 4-bit color device",
		'WBIT',
		/* [12] */
		"Inhibit on 4-bit gray scale device",
		'WBIT',
		/* [13] */
		"Inhibit on 2-bit color device",
		'WBIT',
		/* [14] */
		"Inhibit on 2-bit gray scale device",
		'WBIT',
		/* [15] */
		"Unused",
		'WB02',
		/* [16] */
		"Black in 1-bit mode",
		'WBIT',
		/* [17] */
		"White in 1-bit mode",
		'WBIT',
		/* [18] */
		"Explicit",
		'WBIT',
		/* [19] */
		"Animated",
		'WBIT',
		/* [20] */
		"Tolerant",
		'WBIT',
		/* [21] */
		"Dithered",
		'WBIT',
		/* [22] */
		"Tolerance value",
		'DWRD',
		/* [23] */
		"Private flags",
		'HWRD',
		/* [24] */
		"Reserved",
		'FLNG',
		/* [25] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1274, "plut") {
	{	/* array: 17 elements */
		/* [1] */
		"Pattern Lookup Table",
		'DVDR',
		/* [2] */
		"Theme brush table is ID 386",
		'DVDR',
		/* [3] */
		"'layo' resource brush table is ID 387",
		'DVDR',
		/* [4] */
		"Color depth",
		'DLNG',
		/* [5] */
		"B/W=1",
		'CASE',
		/* [6] */
		"4 Colors=2",
		'CASE',
		/* [7] */
		"256 Colors=8",
		'CASE',
		/* [8] */
		"Thousands=16",
		'CASE',
		/* [9] */
		"Millions=32",
		'CASE',
		/* [10] */
		"Unknown",
		'DWRD',
		/* [11] */
		"default=42",
		'CASE',
		/* [12] */
		"colors",
		'OCNT',
		/* [13] */
		"colors",
		'LSTC',
		/* [14] */
		"'ppat' ID",
		'RSID',
		/* [15] */
		"Color instead of pattern=0",
		'CASE',
		/* [16] */
		"Associated color",
		'COLR',
		/* [17] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1275, "pnel") {
	{	/* array: 4 elements */
		/* [1] */
		"Panel name",
		'P020',
		/* [2] */
		"Script code",
		'SCPC',
		/* [3] */
		"'ICON' resource ID",
		'RSID',
		/* [4] */
		"'DITL' resource ID",
		'RSID'
	}
};

resource 'TMPL' (1276, "pnot") {
	{	/* array: 4 elements */
		/* [1] */
		"Modification date",
		'DATE',
		/* [2] */
		"Version",
		'HWRD',
		/* [3] */
		"Preview resource type",
		'TNAM',
		/* [4] */
		"Resource ID",
		'RSID'
	}
};

resource 'TMPL' (1277, "POST") {
	{	/* array: 4 elements */
		/* [1] */
		"NumStrings",
		'DWRD',
		/* [2] */
		"Strings",
		'LSTZ',
		/* [3] */
		"Commands",
		'PSTR',
		/* [4] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1278, "ppat") {
	{	/* array: 23 elements */
		/* [1] */
		"Pattern type",
		'DWRD',
		/* [2] */
		"Offset to pixmap",
		'DLNG',
		/* [3] */
		"Offset to data",
		'DLNG',
		/* [4] */
		"Expanded pixel image",
		'FLNG',
		/* [5] */
		"Pattern valid flag",
		'FWRD',
		/* [6] */
		"Expanded pattern",
		'FLNG',
		/* [7] */
		"Old-style pattern",
		'H008',
		/* [8] */
		"Base address",
		'FLNG',
		/* [9] */
		"Row bytes",
		'HWRD',
		/* [10] */
		"Bitmap bounds",
		'RECT',
		/* [11] */
		"PixMap version",
		'DWRD',
		/* [12] */
		"Packing format",
		'DWRD',
		/* [13] */
		"Size of pixel data",
		'DLNG',
		/* [14] */
		"H. resolution",
		'HLNG',
		/* [15] */
		"V. resolution",
		'HLNG',
		/* [16] */
		"Pixel type",
		'DWRD',
		/* [17] */
		"Number of bits in pixel",
		'DWRD',
		/* [18] */
		"Number of components in pixel",
		'DWRD',
		/* [19] */
		"Number of bits per field",
		'DWRD',
		/* [20] */
		"Offset to next plane",
		'DLNG',
		/* [21] */
		"Offset to color table",
		'DLNG',
		/* [22] */
		"Reserved",
		'FLNG',
		/* [23] */
		"Pixel data and color table",
		'HEXD'
	}
};

resource 'TMPL' (1279, "ppcc") {
	{	/* array: 7 elements */
		/* [1] */
		"NBP lookup interval",
		'UBYT',
		/* [2] */
		"NBP lookup count",
		'UBYT',
		/* [3] */
		"NBP maximum lives before deletion",
		'DWRD',
		/* [4] */
		"NBP maximum number of entities",
		'DWRD',
		/* [5] */
		"NBP idle time in ticks between lookups",
		'DWRD',
		/* [6] */
		"PPC maximum number of ports",
		'DWRD',
		/* [7] */
		"PPC idle time in ticks between list port"
		"s",
		'DWRD'
	}
};

resource 'TMPL' (1280, "ppdA") {
	{	/* array: 25 elements */
		/* [1] */
		"Signature",
		'TNAM',
		/* [2] */
		"Version",
		'DWRD',
		/* [3] */
		"dlgDoneTime",
		'DBYT',
		/* [4] */
		"filler",
		'DBYT',
		/* [5] */
		"filler",
		'DBYT',
		/* [6] */
		"filler",
		'DBYT',
		/* [7] */
		"Trigger main",
		'ESTR',
		/* [8] */
		"Count:",
		'OCNT',
		/* [9] */
		"List of options",
		'LSTC',
		/* [10] */
		"Option",
		'ESTR',
		/* [11] */
		"*****",
		'LSTE',
		/* [12] */
		"Target main",
		'ESTR',
		/* [13] */
		"Target option",
		'ESTR',
		/* [14] */
		"Count:",
		'OCNT',
		/* [15] */
		"List of options",
		'LSTC',
		/* [16] */
		"Option",
		'ESTR',
		/* [17] */
		"*****",
		'LSTE',
		/* [18] */
		"Count:",
		'OCNT',
		/* [19] */
		"Constraint list",
		'LSTC',
		/* [20] */
		"Main",
		'ESTR',
		/* [21] */
		"Count:",
		'OCNT',
		/* [22] */
		"Options",
		'LSTC',
		/* [23] */
		"Option",
		'ESTR',
		/* [24] */
		"*****",
		'LSTE',
		/* [25] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1281, "ppdT") {
	{	/* array: 52 elements */
		/* [1] */
		"Signature",
		'TNAM',
		/* [2] */
		"Version",
		'DWRD',
		/* [3] */
		"Count:",
		'OCNT',
		/* [4] */
		"Checkboxes",
		'LSTC',
		/* [5] */
		"item",
		'DWRD',
		/* [6] */
		"Main",
		'ESTR',
		/* [7] */
		"*****",
		'LSTE',
		/* [8] */
		"Count:",
		'OCNT',
		/* [9] */
		"Radio groups",
		'LSTC',
		/* [10] */
		"First item",
		'DWRD',
		/* [11] */
		"Last item",
		'DWRD',
		/* [12] */
		"Main",
		'ESTR',
		/* [13] */
		"Count:",
		'OCNT',
		/* [14] */
		"Options",
		'LSTC',
		/* [15] */
		"Option",
		'ESTR',
		/* [16] */
		"*****",
		'LSTE',
		/* [17] */
		"*****",
		'LSTE',
		/* [18] */
		"Count:",
		'OCNT',
		/* [19] */
		"Menus",
		'LSTC',
		/* [20] */
		"Item",
		'DWRD',
		/* [21] */
		"Main",
		'ESTR',
		/* [22] */
		"Count:",
		'OCNT',
		/* [23] */
		"Options",
		'LSTC',
		/* [24] */
		"Option",
		'ESTR',
		/* [25] */
		"*****",
		'LSTE',
		/* [26] */
		"*****",
		'LSTE',
		/* [27] */
		"Count:",
		'OCNT',
		/* [28] */
		"Pict controls",
		'LSTC',
		/* [29] */
		"Dialog item",
		'DWRD',
		/* [30] */
		"color-off ID",
		'DWRD',
		/* [31] */
		"1-bit-off ID",
		'DWRD',
		/* [32] */
		"color-on ID",
		'DWRD',
		/* [33] */
		"1-bit-on ID",
		'DWRD',
		/* [34] */
		"color-forbidden ID",
		'DWRD',
		/* [35] */
		"1-bit-forbidden ID",
		'DWRD',
		/* [36] */
		"Mask ID",
		'DWRD',
		/* [37] */
		"Enabled",
		'DBYT',
		/* [38] */
		"Forbidden",
		'DBYT',
		/* [39] */
		"Value",
		'DBYT',
		/* [40] */
		"Reserved",
		'DBYT',
		/* [41] */
		"Reserved",
		'DLNG',
		/* [42] */
		"Main",
		'ESTR',
		/* [43] */
		"Option",
		'ESTR',
		/* [44] */
		"*****",
		'LSTE',
		/* [45] */
		"Count:",
		'OCNT',
		/* [46] */
		"Texts",
		'LSTC',
		/* [47] */
		"textFrom",
		'DWRD',
		/* [48] */
		"textTo",
		'DWRD',
		/* [49] */
		"Num params alert ID",
		'DWRD',
		/* [50] */
		"Max text alert ID",
		'DWRD',
		/* [51] */
		"Main",
		'ESTR',
		/* [52] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1282, "PPob") {
	{	/* array: 3820 elements */
		/* [1] */
		"Template for PowerPlant 2.5",
		'DVDR',
		/* [2] */
		"Version Number",
		'DWRD',
		/* [3] */
		"CWPro7=2",
		'CASE',
		/* [4] */
		"List of objects",
		'LSTB',
		/* [5] */
		"Object type",
		'KTYP',
		/* [6] */
		"Object data=objd",
		'CASE',
		/* [7] */
		"Begin sub-object list=begs",
		'CASE',
		/* [8] */
		"End sub-object list=ends",
		'CASE',
		/* [9] */
		"User object=user",
		'CASE',
		/* [10] */
		"Class alias=dopl",
		'CASE',
		/* [11] */
		"End of list=end.",
		'CASE',
		/* [12] */
		"Comment=comm",
		'CASE',
		/* [13] */
		"objd",
		'KEYB',
		/* [14] */
		"Number of bytes in following data",
		'LSIZ',
		/* [15] */
		"Data type",
		'KTYP',
		/* [16] */
		"Window=wind",
		'CASE',
		/* [17] */
		"Dialog=dlog",
		'CASE',
		/* [18] */
		"GrafPortView=gpvw",
		'CASE',
		/* [19] */
		"Pane=pane",
		'CASE',
		/* [20] */
		"View=view",
		'CASE',
		/* [21] */
		"Printout=prnt",
		'CASE',
		/* [22] */
		"Caption=capt",
		'CASE',
		/* [23] */
		"GroupBox=gbox",
		'CASE',
		/* [24] */
		"EditField=edit",
		'CASE',
		/* [25] */
		"ListBox=lbox",
		'CASE',
		/* [26] */
		"Control=cntl",
		'CASE',
		/* [27] */
		"Button=butn",
		'CASE',
		/* [28] */
		"ToggleButton=tbut",
		'CASE',
		/* [29] */
		"CicnButton=cicn",
		'CASE',
		/* [30] */
		"TextButton=txbt",
		'CASE',
		/* [31] */
		"Standard control=sctl",
		'CASE',
		/* [32] */
		"Standard button=pbut",
		'CASE',
		/* [33] */
		"Standard checkbox=cbox",
		'CASE',
		/* [34] */
		"Standard radio button=rbut",
		'CASE',
		/* [35] */
		"Standard popup menu=popm",
		'CASE',
		/* [36] */
		"IconPane=icnp",
		'CASE',
		/* [37] */
		"Scroller=scrl",
		'CASE',
		/* [38] */
		"ActiveScroller=ascr",
		'CASE',
		/* [39] */
		"ScrollerView=sclv",
		'CASE',
		/* [40] */
		"Picture=pict",
		'CASE',
		/* [41] */
		"Placeholder=plac",
		'CASE',
		/* [42] */
		"TextEdit=text",
		'CASE',
		/* [43] */
		"TextEditView=txtv",
		'CASE',
		/* [44] */
		"Table=tabl",
		'CASE',
		/* [45] */
		"TableView=tabv",
		'CASE',
		/* [46] */
		"HierarchyTable=htab",
		'CASE',
		/* [47] */
		"TextHierTable=txht",
		'CASE',
		/* [48] */
		"SmallIconTable=sitb",
		'CASE',
		/* [49] */
		"OutlineTable=otab",
		'CASE',
		/* [50] */
		"ColumnView=colv",
		'CASE',
		/* [51] */
		"TextColumn=colv",
		'CASE',
		/* [52] */
		"OffscreenView=offv",
		'CASE',
		/* [53] */
		"OverlappingView=ovlv",
		'CASE',
		/* [54] */
		"SubOverlapView=solv",
		'CASE',
		/* [55] */
		"RadioGroupView=rgpv",
		'CASE',
		/* [56] */
		"MultiPanelView=mpvw",
		'CASE',
		/* [57] */
		"TabGroupView=tbgv",
		'CASE',
		/* [58] */
		"TabGroup=tabg",
		'CASE',
		/* [59] */
		"RadioGroup=radg",
		'CASE',
		/* [60] */
		"Attachment=atta",
		'CASE',
		/* [61] */
		"BeepAttachment=beep",
		'CASE',
		/* [62] */
		"EraseAttachment=eras",
		'CASE',
		/* [63] */
		"ColorEraseAttachment=cers",
		'CASE',
		/* [64] */
		"BorderAttachment=brda",
		'CASE',
		/* [65] */
		"PaintAttachment=pnta",
		'CASE',
		/* [66] */
		"CmdEnablerAttachment=cena",
		'CASE',
		/* [67] */
		"KeyScrollAttachment=ksca",
		'CASE',
		/* [68] */
		"ContextualMenuAttachment=cmat",
		'CASE',
		/* [69] */
		"WindowThemeAttachment=wtha",
		'CASE',
		/* [70] */
		"BevelButton=bbut",
		'CASE',
		/* [71] */
		"ChasingArrows=carr",
		'CASE',
		/* [72] */
		"CheckBox=chbx",
		'CASE',
		/* [73] */
		"CheckBoxGroupBox=cbgb",
		'CASE',
		/* [74] */
		"Clock=clck",
		'CASE',
		/* [75] */
		"CmdBevelButton=cbbt",
		'CASE',
		/* [76] */
		"DisclosureTriangle=dtri",
		'CASE',
		/* [77] */
		"EditText=etxt",
		'CASE',
		/* [78] */
		"IconControl=ictl",
		'CASE',
		/* [79] */
		"ImageWell=iwel",
		'CASE',
		/* [80] */
		"LittleArrows=larr",
		'CASE',
		/* [81] */
		"PictureControl=picd",
		'CASE',
		/* [82] */
		"Placard=plcd",
		'CASE',
		/* [83] */
		"PopupButton=popb",
		'CASE',
		/* [84] */
		"PopupGroupBox=pgbx",
		'CASE',
		/* [85] */
		"ProgressBar=pbar",
		'CASE',
		/* [86] */
		"PushButton=push",
		'CASE',
		/* [87] */
		"RadioButton=rdbt",
		'CASE',
		/* [88] */
		"ScrollBar=sbar",
		'CASE',
		/* [89] */
		"SeparatorLine=sepl",
		'CASE',
		/* [90] */
		"Slider=slid",
		'CASE',
		/* [91] */
		"StaticText=stxt",
		'CASE',
		/* [92] */
		"TabsControl=tabs",
		'CASE',
		/* [93] */
		"TextGroupBox=tgbx",
		'CASE',
		/* [94] */
		"WindowHeader=winh",
		'CASE',
		/* [95] */
		"GACheckBox=gchk",
		'CASE',
		/* [96] */
		"GAPushButton=gpsh",
		'CASE',
		/* [97] */
		"GARadioButton=grad",
		'CASE',
		/* [98] */
		"GAIconButton=gibt",
		'CASE',
		/* [99] */
		"GACmdIconButton=gcib",
		'CASE',
		/* [100] */
		"GATextButton=gtxb",
		'CASE',
		/* [101] */
		"GACmdTextButton=gctb",
		'CASE',
		/* [102] */
		"GADisclosureTriangle=gdcl",
		'CASE',
		/* [103] */
		"GAIconTextButton=gitb",
		'CASE',
		/* [104] */
		"GACmdIconTextButton=gcit",
		'CASE',
		/* [105] */
		"GAIconButtonPopup=gibp",
		'CASE',
		/* [106] */
		"GAIconSuiteControl=gict",
		'CASE',
		/* [107] */
		"GACmdIconSuiteControl=gcic",
		'CASE',
		/* [108] */
		"GAPopup=gpop",
		'CASE',
		/* [109] */
		"GABox=gabx",
		'CASE',
		/* [110] */
		"GABoxGroup=gbgp",
		'CASE',
		/* [111] */
		"GACaption=gcap",
		'CASE',
		/* [112] */
		"GAColorSwatch=gswt",
		'CASE',
		/* [113] */
		"GADialogBox=gdlb",
		'CASE',
		/* [114] */
		"GAEditField=gedt",
		'CASE',
		/* [115] */
		"GAIconSuite=gicn",
		'CASE',
		/* [116] */
		"GAPrimaryBox=gpbx",
		'CASE',
		/* [117] */
		"GAPrimaryGroup=gpgp",
		'CASE',
		/* [118] */
		"GASecondaryBox=gsbx",
		'CASE',
		/* [119] */
		"GASecondaryGroup=gsgp",
		'CASE',
		/* [120] */
		"GASeparator=gsep",
		'CASE',
		/* [121] */
		"GAFocusBorder=gfbd",
		'CASE',
		/* [122] */
		"GALittleArrows=glar",
		'CASE',
		/* [123] */
		"GATabPanel=gtbp",
		'CASE',
		/* [124] */
		"GAWindowHeader=whdr",
		'CASE',
		/* [125] */
		"GADialog=gdlg",
		'CASE',
		/* [126] */
		"PageController=pctl",
		'CASE',
		/* [127] */
		"GAColorSwatchControl=cswt",
		'CASE',
		/* [128] */
		"Null=null",
		'CASE',
		/* [129] */
		"wind",
		'KEYB',
		/* [130] */
		"'WIND' Resource ID",
		'RSID',
		/* [131] */
		"Window behavior",
		'DWRD',
		/* [132] */
		"Regular=2",
		'CASE',
		/* [133] */
		"Modal=0",
		'CASE',
		/* [134] */
		"Floating=1",
		'CASE',
		/* [135] */
		"Layer",
		'LB03',
		/* [136] */
		"Has close box?",
		'LBIT',
		/* [137] */
		"Has title bar?",
		'LBIT',
		/* [138] */
		"Is resizable?",
		'LBIT',
		/* [139] */
		"Draw size box?",
		'LBIT',
		/* [140] */
		"Is zoomable?",
		'LBIT',
		/* [141] */
		"Visible after creation?",
		'LBIT',
		/* [142] */
		"Enabled?",
		'LBIT',
		/* [143] */
		"Can be target?",
		'LBIT',
		/* [144] */
		"Get select click?",
		'LBIT',
		/* [145] */
		"Hide when suspended?",
		'LBIT',
		/* [146] */
		"Delayed selection?",
		'LBIT',
		/* [147] */
		"Erase when updating?",
		'LBIT',
		/* [148] */
		"Reserved",
		'LB17',
		/* [149] */
		"Mininimum width",
		'DWRD',
		/* [150] */
		"Minimum height",
		'DWRD',
		/* [151] */
		"Maximum width",
		'DWRD',
		/* [152] */
		"Any=-1",
		'CASE',
		/* [153] */
		"Maximum height",
		'DWRD',
		/* [154] */
		"Any=-1",
		'CASE',
		/* [155] */
		"Standard state width",
		'DWRD',
		/* [156] */
		"Default=-1",
		'CASE',
		/* [157] */
		"Standard state height",
		'DWRD',
		/* [158] */
		"Default=-1",
		'CASE',
		/* [159] */
		"User constant",
		'DLNG',
		/* [160] */
		"",
		'KEYE',
		/* [161] */
		"dlog",
		'KEYB',
		/* [162] */
		"Window data",
		'DVDR',
		/* [163] */
		"'WIND' Resource ID",
		'RSID',
		/* [164] */
		"Window behavior",
		'DWRD',
		/* [165] */
		"Modal=0",
		'CASE',
		/* [166] */
		"Floating=1",
		'CASE',
		/* [167] */
		"Regular=2",
		'CASE',
		/* [168] */
		"Layer",
		'LB03',
		/* [169] */
		"Has close box?",
		'LBIT',
		/* [170] */
		"Has title bar?",
		'LBIT',
		/* [171] */
		"Is resizable?",
		'LBIT',
		/* [172] */
		"Draw size box?",
		'LBIT',
		/* [173] */
		"Is zoomable?",
		'LBIT',
		/* [174] */
		"Visible after creation?",
		'LBIT',
		/* [175] */
		"Enabled?",
		'LBIT',
		/* [176] */
		"Can be target?",
		'LBIT',
		/* [177] */
		"Get select click?",
		'LBIT',
		/* [178] */
		"Hide when suspended?",
		'LBIT',
		/* [179] */
		"Delayed selection?",
		'LBIT',
		/* [180] */
		"Erase when updating?",
		'LBIT',
		/* [181] */
		"Reserved",
		'LB17',
		/* [182] */
		"Mininimum width",
		'DWRD',
		/* [183] */
		"Minimum height",
		'DWRD',
		/* [184] */
		"Maximum width",
		'DWRD',
		/* [185] */
		"Any=-1",
		'CASE',
		/* [186] */
		"Maximum height",
		'DWRD',
		/* [187] */
		"Any=-1",
		'CASE',
		/* [188] */
		"Standard state width",
		'DWRD',
		/* [189] */
		"Default=-1",
		'CASE',
		/* [190] */
		"Standard state height",
		'DWRD',
		/* [191] */
		"Default=-1",
		'CASE',
		/* [192] */
		"User constant",
		'DLNG',
		/* [193] */
		"Dialog data",
		'DVDR',
		/* [194] */
		"Default button ID",
		'DLNG',
		/* [195] */
		"Cancel button ID",
		'DLNG',
		/* [196] */
		"",
		'KEYE',
		/* [197] */
		"gpvw",
		'KEYB',
		/* [198] */
		"Pane data",
		'DVDR',
		/* [199] */
		"Pane ID",
		'DLNG',
		/* [200] */
		"Width",
		'DWRD',
		/* [201] */
		"Height",
		'DWRD',
		/* [202] */
		"Visible?",
		'BFLG',
		/* [203] */
		"Enabled?",
		'BFLG',
		/* [204] */
		"Left side bound?",
		'BFLG',
		/* [205] */
		"Top side bound?",
		'BFLG',
		/* [206] */
		"Right side bound?",
		'BFLG',
		/* [207] */
		"Bottom side bound?",
		'BFLG',
		/* [208] */
		"Left in super image",
		'DLNG',
		/* [209] */
		"Top in super image",
		'DLNG',
		/* [210] */
		"User constant",
		'DLNG',
		/* [211] */
		"Superview",
		'DLNG',
		/* [212] */
		"Default=-1",
		'CASE',
		/* [213] */
		"None=0",
		'CASE',
		/* [214] */
		"View data",
		'DVDR',
		/* [215] */
		"Image width",
		'DLNG',
		/* [216] */
		"Image height",
		'DLNG',
		/* [217] */
		"Horizontal scroll position",
		'DLNG',
		/* [218] */
		"Vertical scroll position",
		'DLNG',
		/* [219] */
		"Horizontal scroll unit",
		'DLNG',
		/* [220] */
		"Vertical scroll unit",
		'DLNG',
		/* [221] */
		"Reconcile overhang?",
		'WFLG',
		/* [222] */
		"",
		'KEYE',
		/* [223] */
		"pane",
		'KEYB',
		/* [224] */
		"Pane data",
		'DVDR',
		/* [225] */
		"Pane ID",
		'DLNG',
		/* [226] */
		"Width",
		'DWRD',
		/* [227] */
		"Height",
		'DWRD',
		/* [228] */
		"Visible?",
		'BFLG',
		/* [229] */
		"Enabled?",
		'BFLG',
		/* [230] */
		"Left side bound?",
		'BFLG',
		/* [231] */
		"Top side bound?",
		'BFLG',
		/* [232] */
		"Right side bound?",
		'BFLG',
		/* [233] */
		"Bottom side bound?",
		'BFLG',
		/* [234] */
		"Left in super image",
		'DLNG',
		/* [235] */
		"Top in super image",
		'DLNG',
		/* [236] */
		"User constant",
		'DLNG',
		/* [237] */
		"Superview",
		'DLNG',
		/* [238] */
		"Default=-1",
		'CASE',
		/* [239] */
		"None=0",
		'CASE',
		/* [240] */
		"",
		'KEYE',
		/* [241] */
		"view",
		'KEYB',
		/* [242] */
		"Pane data",
		'DVDR',
		/* [243] */
		"Pane ID",
		'DLNG',
		/* [244] */
		"Width",
		'DWRD',
		/* [245] */
		"Height",
		'DWRD',
		/* [246] */
		"Visible?",
		'BFLG',
		/* [247] */
		"Enabled?",
		'BFLG',
		/* [248] */
		"Left side bound?",
		'BFLG',
		/* [249] */
		"Top side bound?",
		'BFLG',
		/* [250] */
		"Right side bound?",
		'BFLG',
		/* [251] */
		"Bottom side bound?",
		'BFLG',
		/* [252] */
		"Left in super image",
		'DLNG',
		/* [253] */
		"Top in super image",
		'DLNG',
		/* [254] */
		"User constant",
		'DLNG',
		/* [255] */
		"Superview",
		'DLNG',
		/* [256] */
		"Default=-1",
		'CASE',
		/* [257] */
		"None=0",
		'CASE',
		/* [258] */
		"View data",
		'DVDR',
		/* [259] */
		"Image width",
		'DLNG',
		/* [260] */
		"Image height",
		'DLNG',
		/* [261] */
		"Horizontal scroll position",
		'DLNG',
		/* [262] */
		"Vertical scroll position",
		'DLNG',
		/* [263] */
		"Horizontal scroll unit",
		'DLNG',
		/* [264] */
		"Vertical scroll unit",
		'DLNG',
		/* [265] */
		"Reconcile overhang?",
		'WFLG',
		/* [266] */
		"",
		'KEYE',
		/* [267] */
		"prnt",
		'KEYB',
		/* [268] */
		"Width",
		'DWRD',
		/* [269] */
		"Height",
		'DWRD',
		/* [270] */
		"Active?",
		'BFLG',
		/* [271] */
		"Enabled?",
		'BFLG',
		/* [272] */
		"User constant",
		'DLNG',
		/* [273] */
		"Page numbering order",
		'LBIT',
		/* [274] */
		"Across=Off",
		'CASE',
		/* [275] */
		"Down=On",
		'CASE',
		/* [276] */
		"Reserved",
		'LB31',
		/* [277] */
		"",
		'KEYE',
		/* [278] */
		"capt",
		'KEYB',
		/* [279] */
		"Pane data",
		'DVDR',
		/* [280] */
		"Pane ID",
		'DLNG',
		/* [281] */
		"Width",
		'DWRD',
		/* [282] */
		"Height",
		'DWRD',
		/* [283] */
		"Visible?",
		'BFLG',
		/* [284] */
		"Enabled?",
		'BFLG',
		/* [285] */
		"Left side bound?",
		'BFLG',
		/* [286] */
		"Top side bound?",
		'BFLG',
		/* [287] */
		"Right side bound?",
		'BFLG',
		/* [288] */
		"Bottom side bound?",
		'BFLG',
		/* [289] */
		"Left in super image",
		'DLNG',
		/* [290] */
		"Top in super image",
		'DLNG',
		/* [291] */
		"User constant",
		'DLNG',
		/* [292] */
		"Superview",
		'DLNG',
		/* [293] */
		"Default=-1",
		'CASE',
		/* [294] */
		"None=0",
		'CASE',
		/* [295] */
		"Caption data",
		'DVDR',
		/* [296] */
		"Caption text",
		'PSTR',
		/* [297] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [298] */
		"",
		'KEYE',
		/* [299] */
		"gbox",
		'KEYB',
		/* [300] */
		"Pane data",
		'DVDR',
		/* [301] */
		"Pane ID",
		'DLNG',
		/* [302] */
		"Width",
		'DWRD',
		/* [303] */
		"Height",
		'DWRD',
		/* [304] */
		"Visible?",
		'BFLG',
		/* [305] */
		"Enabled?",
		'BFLG',
		/* [306] */
		"Left side bound?",
		'BFLG',
		/* [307] */
		"Top side bound?",
		'BFLG',
		/* [308] */
		"Right side bound?",
		'BFLG',
		/* [309] */
		"Bottom side bound?",
		'BFLG',
		/* [310] */
		"Left in super image",
		'DLNG',
		/* [311] */
		"Top in super image",
		'DLNG',
		/* [312] */
		"User constant",
		'DLNG',
		/* [313] */
		"Superview",
		'DLNG',
		/* [314] */
		"Default=-1",
		'CASE',
		/* [315] */
		"None=0",
		'CASE',
		/* [316] */
		"GroupBox data",
		'DVDR',
		/* [317] */
		"Title",
		'PSTR',
		/* [318] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [319] */
		"",
		'KEYE',
		/* [320] */
		"edit",
		'KEYB',
		/* [321] */
		"Pane data",
		'DVDR',
		/* [322] */
		"Pane ID",
		'DLNG',
		/* [323] */
		"Width",
		'DWRD',
		/* [324] */
		"Height",
		'DWRD',
		/* [325] */
		"Visible?",
		'BFLG',
		/* [326] */
		"Enabled?",
		'BFLG',
		/* [327] */
		"Left side bound?",
		'BFLG',
		/* [328] */
		"Top side bound?",
		'BFLG',
		/* [329] */
		"Right side bound?",
		'BFLG',
		/* [330] */
		"Bottom side bound?",
		'BFLG',
		/* [331] */
		"Left in super image",
		'DLNG',
		/* [332] */
		"Top in super image",
		'DLNG',
		/* [333] */
		"User constant",
		'DLNG',
		/* [334] */
		"Superview",
		'DLNG',
		/* [335] */
		"Default=-1",
		'CASE',
		/* [336] */
		"None=0",
		'CASE',
		/* [337] */
		"Edit field data",
		'DVDR',
		/* [338] */
		"Initial text",
		'PSTR',
		/* [339] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [340] */
		"System font=0",
		'CASE',
		/* [341] */
		"Maximum text size",
		'DWRD',
		/* [342] */
		"Has box around field?",
		'BBIT',
		/* [343] */
		"Word wrap?",
		'BBIT',
		/* [344] */
		"AutoScroll?",
		'BBIT',
		/* [345] */
		"Text Buffering?",
		'BBIT',
		/* [346] */
		"Outline Hilite?",
		'BBIT',
		/* [347] */
		"Inline Input?",
		'BBIT',
		/* [348] */
		"Use Text Services?",
		'BBIT',
		/* [349] */
		"Reserved",
		'BBIT',
		/* [350] */
		"Keystroke filter",
		'DBYT',
		/* [351] */
		"None=0",
		'CASE',
		/* [352] */
		"Integer=1",
		'CASE',
		/* [353] */
		"Alphanumeric=2",
		'CASE',
		/* [354] */
		"Printing char=3",
		'CASE',
		/* [355] */
		"",
		'KEYE',
		/* [356] */
		"lbox",
		'KEYB',
		/* [357] */
		"Pane data",
		'DVDR',
		/* [358] */
		"Pane ID",
		'DLNG',
		/* [359] */
		"Width",
		'DWRD',
		/* [360] */
		"Height",
		'DWRD',
		/* [361] */
		"Visible?",
		'BFLG',
		/* [362] */
		"Enabled?",
		'BFLG',
		/* [363] */
		"Left side bound?",
		'BFLG',
		/* [364] */
		"Top side bound?",
		'BFLG',
		/* [365] */
		"Right side bound?",
		'BFLG',
		/* [366] */
		"Bottom side bound?",
		'BFLG',
		/* [367] */
		"Left in super image",
		'DLNG',
		/* [368] */
		"Top in super image",
		'DLNG',
		/* [369] */
		"User constant",
		'DLNG',
		/* [370] */
		"Superview",
		'DLNG',
		/* [371] */
		"Default=-1",
		'CASE',
		/* [372] */
		"None=0",
		'CASE',
		/* [373] */
		"List box data",
		'DVDR',
		/* [374] */
		"Has horizontal scroll?",
		'BFLG',
		/* [375] */
		"Has vertical scroll?",
		'BFLG',
		/* [376] */
		"Has grow box?",
		'BFLG',
		/* [377] */
		"Has focus box?",
		'BFLG',
		/* [378] */
		"Double-click message",
		'DLNG',
		/* [379] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [380] */
		"'LDEF' ID",
		'RSID',
		/* [381] */
		"textList=0",
		'CASE',
		/* [382] */
		"Count:",
		'OCNT',
		/* [383] */
		"List of Initial items",
		'LSTC',
		/* [384] */
		"Text",
		'PSTR',
		/* [385] */
		"*****",
		'LSTE',
		/* [386] */
		"",
		'KEYE',
		/* [387] */
		"cntl",
		'KEYB',
		/* [388] */
		"Pane data",
		'DVDR',
		/* [389] */
		"Pane ID",
		'DLNG',
		/* [390] */
		"Width",
		'DWRD',
		/* [391] */
		"Height",
		'DWRD',
		/* [392] */
		"Visible?",
		'BFLG',
		/* [393] */
		"Enabled?",
		'BFLG',
		/* [394] */
		"Left side bound?",
		'BFLG',
		/* [395] */
		"Top side bound?",
		'BFLG',
		/* [396] */
		"Right side bound?",
		'BFLG',
		/* [397] */
		"Bottom side bound?",
		'BFLG',
		/* [398] */
		"Left in super image",
		'DLNG',
		/* [399] */
		"Top in super image",
		'DLNG',
		/* [400] */
		"User constant",
		'DLNG',
		/* [401] */
		"Superview",
		'DLNG',
		/* [402] */
		"Default=-1",
		'CASE',
		/* [403] */
		"None=0",
		'CASE',
		/* [404] */
		"Control data",
		'DVDR',
		/* [405] */
		"Message when pushed",
		'DLNG',
		/* [406] */
		"Initial value",
		'DLNG',
		/* [407] */
		"Minimum value",
		'DLNG',
		/* [408] */
		"Maximum value",
		'DLNG',
		/* [409] */
		"",
		'KEYE',
		/* [410] */
		"butn",
		'KEYB',
		/* [411] */
		"Pane data",
		'DVDR',
		/* [412] */
		"Pane ID",
		'DLNG',
		/* [413] */
		"Width",
		'DWRD',
		/* [414] */
		"Height",
		'DWRD',
		/* [415] */
		"Visible?",
		'BFLG',
		/* [416] */
		"Enabled?",
		'BFLG',
		/* [417] */
		"Left side bound?",
		'BFLG',
		/* [418] */
		"Top side bound?",
		'BFLG',
		/* [419] */
		"Right side bound?",
		'BFLG',
		/* [420] */
		"Bottom side bound?",
		'BFLG',
		/* [421] */
		"Left in super image",
		'DLNG',
		/* [422] */
		"Top in super image",
		'DLNG',
		/* [423] */
		"User constant",
		'DLNG',
		/* [424] */
		"Superview",
		'DLNG',
		/* [425] */
		"Default=-1",
		'CASE',
		/* [426] */
		"None=0",
		'CASE',
		/* [427] */
		"Button data",
		'DVDR',
		/* [428] */
		"Message when pushed",
		'DLNG',
		/* [429] */
		"Initial value",
		'DLNG',
		/* [430] */
		"Always=0",
		'CASE',
		/* [431] */
		"Minimum value",
		'DLNG',
		/* [432] */
		"Always=0",
		'CASE',
		/* [433] */
		"Maximum value",
		'DLNG',
		/* [434] */
		"Always=0",
		'CASE',
		/* [435] */
		"Graphics resource type",
		'TNAM',
		/* [436] */
		"Icon Suite=ICN#",
		'CASE',
		/* [437] */
		"Picture=PICT",
		'CASE',
		/* [438] */
		"Black and white icon=ICON",
		'CASE',
		/* [439] */
		"Normal graphic resource ID",
		'RSID',
		/* [440] */
		"Pushed graphic resource ID",
		'RSID',
		/* [441] */
		"",
		'KEYE',
		/* [442] */
		"tbut",
		'KEYB',
		/* [443] */
		"Pane data",
		'DVDR',
		/* [444] */
		"Pane ID",
		'DLNG',
		/* [445] */
		"Width",
		'DWRD',
		/* [446] */
		"Height",
		'DWRD',
		/* [447] */
		"Visible?",
		'BFLG',
		/* [448] */
		"Enabled?",
		'BFLG',
		/* [449] */
		"Left side bound?",
		'BFLG',
		/* [450] */
		"Top side bound?",
		'BFLG',
		/* [451] */
		"Right side bound?",
		'BFLG',
		/* [452] */
		"Bottom side bound?",
		'BFLG',
		/* [453] */
		"Left in super image",
		'DLNG',
		/* [454] */
		"Top in super image",
		'DLNG',
		/* [455] */
		"User constant",
		'DLNG',
		/* [456] */
		"Superview",
		'DLNG',
		/* [457] */
		"Default=-1",
		'CASE',
		/* [458] */
		"None=0",
		'CASE',
		/* [459] */
		"ToggleButton data",
		'DVDR',
		/* [460] */
		"Message when pushed",
		'DLNG',
		/* [461] */
		"Initial value",
		'DLNG',
		/* [462] */
		"Off=0",
		'CASE',
		/* [463] */
		"On=1",
		'CASE',
		/* [464] */
		"Minimum value",
		'DLNG',
		/* [465] */
		"Always=0",
		'CASE',
		/* [466] */
		"Maximum value",
		'DLNG',
		/* [467] */
		"Always=1",
		'CASE',
		/* [468] */
		"Graphics resource type",
		'TNAM',
		/* [469] */
		"Icon Suite=ICN#",
		'CASE',
		/* [470] */
		"Picture=PICT",
		'CASE',
		/* [471] */
		"Black and white icon=ICON",
		'CASE',
		/* [472] */
		"On graphic resource ID",
		'RSID',
		/* [473] */
		"On click graphic resource ID",
		'RSID',
		/* [474] */
		"Off graphic resource ID",
		'RSID',
		/* [475] */
		"Off click graphic resource ID",
		'RSID',
		/* [476] */
		"Transition graphic resource ID",
		'RSID',
		/* [477] */
		"",
		'KEYE',
		/* [478] */
		"cicn",
		'KEYB',
		/* [479] */
		"Pane data",
		'DVDR',
		/* [480] */
		"Pane ID",
		'DLNG',
		/* [481] */
		"Width",
		'DWRD',
		/* [482] */
		"Height",
		'DWRD',
		/* [483] */
		"Visible?",
		'BFLG',
		/* [484] */
		"Enabled?",
		'BFLG',
		/* [485] */
		"Left side bound?",
		'BFLG',
		/* [486] */
		"Top side bound?",
		'BFLG',
		/* [487] */
		"Right side bound?",
		'BFLG',
		/* [488] */
		"Bottom side bound?",
		'BFLG',
		/* [489] */
		"Left in super image",
		'DLNG',
		/* [490] */
		"Top in super image",
		'DLNG',
		/* [491] */
		"User constant",
		'DLNG',
		/* [492] */
		"Superview",
		'DLNG',
		/* [493] */
		"Default=-1",
		'CASE',
		/* [494] */
		"None=0",
		'CASE',
		/* [495] */
		"CicnButton data",
		'DVDR',
		/* [496] */
		"Message when pushed",
		'DLNG',
		/* [497] */
		"Initial value",
		'DLNG',
		/* [498] */
		"Always=0",
		'CASE',
		/* [499] */
		"Minimum value",
		'DLNG',
		/* [500] */
		"Always=0",
		'CASE',
		/* [501] */
		"Maximum value",
		'DLNG',
		/* [502] */
		"Always=0",
		'CASE',
		/* [503] */
		"Normal cicn resource ID",
		'RSID',
		/* [504] */
		"Pushed cicn resource ID",
		'RSID',
		/* [505] */
		"",
		'KEYE',
		/* [506] */
		"txbt",
		'KEYB',
		/* [507] */
		"Pane data",
		'DVDR',
		/* [508] */
		"Pane ID",
		'DLNG',
		/* [509] */
		"Width",
		'DWRD',
		/* [510] */
		"Height",
		'DWRD',
		/* [511] */
		"Visible?",
		'BFLG',
		/* [512] */
		"Enabled?",
		'BFLG',
		/* [513] */
		"Left side bound?",
		'BFLG',
		/* [514] */
		"Top side bound?",
		'BFLG',
		/* [515] */
		"Right side bound?",
		'BFLG',
		/* [516] */
		"Bottom side bound?",
		'BFLG',
		/* [517] */
		"Left in super image",
		'DLNG',
		/* [518] */
		"Top in super image",
		'DLNG',
		/* [519] */
		"User constant",
		'DLNG',
		/* [520] */
		"Superview",
		'DLNG',
		/* [521] */
		"Default=-1",
		'CASE',
		/* [522] */
		"None=0",
		'CASE',
		/* [523] */
		"TextButton data",
		'DVDR',
		/* [524] */
		"Message when pushed",
		'DLNG',
		/* [525] */
		"Initial value",
		'DLNG',
		/* [526] */
		"Unchecked=0",
		'CASE',
		/* [527] */
		"Checked=1",
		'CASE',
		/* [528] */
		"Minimum value",
		'DLNG',
		/* [529] */
		"Always=0",
		'CASE',
		/* [530] */
		"Maximum value",
		'DLNG',
		/* [531] */
		"Always=1",
		'CASE',
		/* [532] */
		"Title",
		'PSTR',
		/* [533] */
		"Text Traits ('Txtr') ID",
		'RSID',
		/* [534] */
		"Selected Text Style",
		'HWRD',
		/* [535] */
		"",
		'KEYE',
		/* [536] */
		"sctl",
		'KEYB',
		/* [537] */
		"Pane data",
		'DVDR',
		/* [538] */
		"Pane ID",
		'DLNG',
		/* [539] */
		"Width",
		'DWRD',
		/* [540] */
		"Height",
		'DWRD',
		/* [541] */
		"Visible?",
		'BFLG',
		/* [542] */
		"Enabled?",
		'BFLG',
		/* [543] */
		"Left side bound?",
		'BFLG',
		/* [544] */
		"Top side bound?",
		'BFLG',
		/* [545] */
		"Right side bound?",
		'BFLG',
		/* [546] */
		"Bottom side bound?",
		'BFLG',
		/* [547] */
		"Left in super image",
		'DLNG',
		/* [548] */
		"Top in super image",
		'DLNG',
		/* [549] */
		"User constant",
		'DLNG',
		/* [550] */
		"Superview",
		'DLNG',
		/* [551] */
		"Default=-1",
		'CASE',
		/* [552] */
		"None=0",
		'CASE',
		/* [553] */
		"Control data",
		'DVDR',
		/* [554] */
		"Value changed message",
		'DLNG',
		/* [555] */
		"Initial value",
		'DLNG',
		/* [556] */
		"Minimum value",
		'DLNG',
		/* [557] */
		"Maximum value",
		'DLNG',
		/* [558] */
		"Standard control data",
		'DVDR',
		/* [559] */
		"Control kind",
		'DWRD',
		/* [560] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [561] */
		"System font=0",
		'CASE',
		/* [562] */
		"Title",
		'PSTR',
		/* [563] */
		"Standard Control RefCon",
		'DLNG',
		/* [564] */
		"",
		'KEYE',
		/* [565] */
		"pbut",
		'KEYB',
		/* [566] */
		"Pane data",
		'DVDR',
		/* [567] */
		"Pane ID",
		'DLNG',
		/* [568] */
		"Width",
		'DWRD',
		/* [569] */
		"Height",
		'DWRD',
		/* [570] */
		"Visible?",
		'BFLG',
		/* [571] */
		"Enabled?",
		'BFLG',
		/* [572] */
		"Left side bound?",
		'BFLG',
		/* [573] */
		"Top side bound?",
		'BFLG',
		/* [574] */
		"Right side bound?",
		'BFLG',
		/* [575] */
		"Bottom side bound?",
		'BFLG',
		/* [576] */
		"Left in super image",
		'DLNG',
		/* [577] */
		"Top in super image",
		'DLNG',
		/* [578] */
		"User constant",
		'DLNG',
		/* [579] */
		"Superview",
		'DLNG',
		/* [580] */
		"Default=-1",
		'CASE',
		/* [581] */
		"None=0",
		'CASE',
		/* [582] */
		"Standard button data",
		'DVDR',
		/* [583] */
		"Message when pushed",
		'DLNG',
		/* [584] */
		"cmd_Nothing=0",
		'CASE',
		/* [585] */
		"cmd_Close=4",
		'CASE',
		/* [586] */
		"msg_OK=900",
		'CASE',
		/* [587] */
		"msg_Cancel=901",
		'CASE',
		/* [588] */
		"Initial value",
		'DLNG',
		/* [589] */
		"Always=0",
		'CASE',
		/* [590] */
		"Minimum value",
		'DLNG',
		/* [591] */
		"Always=0",
		'CASE',
		/* [592] */
		"Maximum value",
		'DLNG',
		/* [593] */
		"Always=0",
		'CASE',
		/* [594] */
		"Push button proc",
		'DWRD',
		/* [595] */
		"Default=0",
		'CASE',
		/* [596] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [597] */
		"System font=0",
		'CASE',
		/* [598] */
		"Title",
		'PSTR',
		/* [599] */
		"Okay=OK",
		'CASE',
		/* [600] */
		"Cancel=Cancel",
		'CASE',
		/* [601] */
		"Continue=Continue",
		'CASE',
		/* [602] */
		"Save=Save",
		'CASE',
		/* [603] */
		"Don't save=Don't save",
		'CASE',
		/* [604] */
		"Standard Control RefCon",
		'DLNG',
		/* [605] */
		"",
		'KEYE',
		/* [606] */
		"cbox",
		'KEYB',
		/* [607] */
		"Pane data",
		'DVDR',
		/* [608] */
		"Pane ID",
		'DLNG',
		/* [609] */
		"Width",
		'DWRD',
		/* [610] */
		"Height",
		'DWRD',
		/* [611] */
		"Visible?",
		'BFLG',
		/* [612] */
		"Enabled?",
		'BFLG',
		/* [613] */
		"Left side bound?",
		'BFLG',
		/* [614] */
		"Top side bound?",
		'BFLG',
		/* [615] */
		"Right side bound?",
		'BFLG',
		/* [616] */
		"Bottom side bound?",
		'BFLG',
		/* [617] */
		"Left in super image",
		'DLNG',
		/* [618] */
		"Top in super image",
		'DLNG',
		/* [619] */
		"User constant",
		'DLNG',
		/* [620] */
		"Superview",
		'DLNG',
		/* [621] */
		"Default=-1",
		'CASE',
		/* [622] */
		"None=0",
		'CASE',
		/* [623] */
		"Standard check box data",
		'DVDR',
		/* [624] */
		"Value changed message",
		'DLNG',
		/* [625] */
		"Initial value",
		'DLNG',
		/* [626] */
		"Unchecked=0",
		'CASE',
		/* [627] */
		"Checked=1",
		'CASE',
		/* [628] */
		"Minimum value",
		'DLNG',
		/* [629] */
		"Always=0",
		'CASE',
		/* [630] */
		"Maximum value",
		'DLNG',
		/* [631] */
		"Always=1",
		'CASE',
		/* [632] */
		"Check box proc",
		'DWRD',
		/* [633] */
		"Default=1",
		'CASE',
		/* [634] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [635] */
		"System font=0",
		'CASE',
		/* [636] */
		"Title",
		'PSTR',
		/* [637] */
		"Standard Control RefCon",
		'DLNG',
		/* [638] */
		"",
		'KEYE',
		/* [639] */
		"rbut",
		'KEYB',
		/* [640] */
		"Pane data",
		'DVDR',
		/* [641] */
		"Pane ID",
		'DLNG',
		/* [642] */
		"Width",
		'DWRD',
		/* [643] */
		"Height",
		'DWRD',
		/* [644] */
		"Visible?",
		'BFLG',
		/* [645] */
		"Enabled?",
		'BFLG',
		/* [646] */
		"Left side bound?",
		'BFLG',
		/* [647] */
		"Top side bound?",
		'BFLG',
		/* [648] */
		"Right side bound?",
		'BFLG',
		/* [649] */
		"Bottom side bound?",
		'BFLG',
		/* [650] */
		"Left in super image",
		'DLNG',
		/* [651] */
		"Top in super image",
		'DLNG',
		/* [652] */
		"User constant",
		'DLNG',
		/* [653] */
		"Superview",
		'DLNG',
		/* [654] */
		"Default=-1",
		'CASE',
		/* [655] */
		"None=0",
		'CASE',
		/* [656] */
		"Standard radio button data",
		'DVDR',
		/* [657] */
		"Value changed message",
		'DLNG',
		/* [658] */
		"Initial value",
		'DLNG',
		/* [659] */
		"Unchecked=0",
		'CASE',
		/* [660] */
		"Checked=1",
		'CASE',
		/* [661] */
		"Minimum value",
		'DLNG',
		/* [662] */
		"Always=0",
		'CASE',
		/* [663] */
		"Maximum value",
		'DLNG',
		/* [664] */
		"Always=1",
		'CASE',
		/* [665] */
		"Radio button proc",
		'DWRD',
		/* [666] */
		"Default=2",
		'CASE',
		/* [667] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [668] */
		"System font=0",
		'CASE',
		/* [669] */
		"Title",
		'PSTR',
		/* [670] */
		"Standard Control RefCon",
		'DLNG',
		/* [671] */
		"",
		'KEYE',
		/* [672] */
		"popm",
		'KEYB',
		/* [673] */
		"Pane data",
		'DVDR',
		/* [674] */
		"Pane ID",
		'DLNG',
		/* [675] */
		"Width",
		'DWRD',
		/* [676] */
		"Height",
		'DWRD',
		/* [677] */
		"Visible?",
		'BFLG',
		/* [678] */
		"Enabled?",
		'BFLG',
		/* [679] */
		"Left side bound?",
		'BFLG',
		/* [680] */
		"Top side bound?",
		'BFLG',
		/* [681] */
		"Right side bound?",
		'BFLG',
		/* [682] */
		"Bottom side bound?",
		'BFLG',
		/* [683] */
		"Left in super image",
		'DLNG',
		/* [684] */
		"Top in super image",
		'DLNG',
		/* [685] */
		"User constant",
		'DLNG',
		/* [686] */
		"Superview",
		'DLNG',
		/* [687] */
		"Default=-1",
		'CASE',
		/* [688] */
		"None=0",
		'CASE',
		/* [689] */
		"Popup menu data",
		'DVDR',
		/* [690] */
		"Value changed message",
		'DLNG',
		/* [691] */
		"Filler",
		'FWRD',
		/* [692] */
		"Filler bit (ignore)",
		'BBIT',
		/* [693] */
		"Title style: Extend",
		'BBIT',
		/* [694] */
		"Title style: Condense",
		'BBIT',
		/* [695] */
		"Title style: Shadow",
		'BBIT',
		/* [696] */
		"Title style: Outline",
		'BBIT',
		/* [697] */
		"Title style: Underline",
		'BBIT',
		/* [698] */
		"Title style: Italic",
		'BBIT',
		/* [699] */
		"Title style: Bold",
		'BBIT',
		/* [700] */
		"Title position",
		'UBYT',
		/* [701] */
		"Left justified=0",
		'CASE',
		/* [702] */
		"Center Justified=1",
		'CASE',
		/* [703] */
		"Right Justified=255",
		'CASE',
		/* [704] */
		"Filler",
		'FWRD',
		/* [705] */
		"Resource ID of 'MENU'",
		'RSID',
		/* [706] */
		"Filler",
		'FWRD',
		/* [707] */
		"Width (in pixels) of title",
		'DWRD',
		/* [708] */
		"Type of popup (procID)",
		'DWRD',
		/* [709] */
		"Standard=1008",
		'CASE',
		/* [710] */
		"Fixed width=1009",
		'CASE',
		/* [711] */
		"Add resource=1012",
		'CASE',
		/* [712] */
		"Fixed and add resource=1013",
		'CASE',
		/* [713] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [714] */
		"System font=0",
		'CASE',
		/* [715] */
		"Title",
		'PSTR',
		/* [716] */
		"None=",
		'CASE',
		/* [717] */
		"Resource type for items",
		'TNAM',
		/* [718] */
		"Initial item choice",
		'DWRD',
		/* [719] */
		"",
		'KEYE',
		/* [720] */
		"icnp",
		'KEYB',
		/* [721] */
		"Pane data",
		'DVDR',
		/* [722] */
		"Pane ID",
		'DLNG',
		/* [723] */
		"Width",
		'DWRD',
		/* [724] */
		"Height",
		'DWRD',
		/* [725] */
		"Visible?",
		'BFLG',
		/* [726] */
		"Enabled?",
		'BFLG',
		/* [727] */
		"Left side bound?",
		'BFLG',
		/* [728] */
		"Top side bound?",
		'BFLG',
		/* [729] */
		"Right side bound?",
		'BFLG',
		/* [730] */
		"Bottom side bound?",
		'BFLG',
		/* [731] */
		"Left in super image",
		'DLNG',
		/* [732] */
		"Top in super image",
		'DLNG',
		/* [733] */
		"User constant",
		'DLNG',
		/* [734] */
		"Superview",
		'DLNG',
		/* [735] */
		"Default=-1",
		'CASE',
		/* [736] */
		"None=0",
		'CASE',
		/* [737] */
		"IconPane data",
		'DVDR',
		/* [738] */
		"Icon ('icn#') ID",
		'RSID',
		/* [739] */
		"",
		'KEYE',
		/* [740] */
		"scrl",
		'KEYB',
		/* [741] */
		"Pane data",
		'DVDR',
		/* [742] */
		"Pane ID",
		'DLNG',
		/* [743] */
		"Width",
		'DWRD',
		/* [744] */
		"Width of SuperView=-1",
		'CASE',
		/* [745] */
		"Height",
		'DWRD',
		/* [746] */
		"Height of SuperView=-1",
		'CASE',
		/* [747] */
		"Visible?",
		'BFLG',
		/* [748] */
		"Enabled?",
		'BFLG',
		/* [749] */
		"Left side bound?",
		'BFLG',
		/* [750] */
		"Top side bound?",
		'BFLG',
		/* [751] */
		"Right side bound?",
		'BFLG',
		/* [752] */
		"Bottom side bound?",
		'BFLG',
		/* [753] */
		"Left in super image",
		'DLNG',
		/* [754] */
		"Top in super image",
		'DLNG',
		/* [755] */
		"User constant",
		'DLNG',
		/* [756] */
		"Superview",
		'DLNG',
		/* [757] */
		"Default=-1",
		'CASE',
		/* [758] */
		"None=0",
		'CASE',
		/* [759] */
		"View data",
		'DVDR',
		/* [760] */
		"Image width",
		'DLNG',
		/* [761] */
		"Image height",
		'DLNG',
		/* [762] */
		"Horizontal scroll position",
		'DLNG',
		/* [763] */
		"Vertical scroll position",
		'DLNG',
		/* [764] */
		"Horizontal scroll unit",
		'DLNG',
		/* [765] */
		"Vertical scroll unit",
		'DLNG',
		/* [766] */
		"Reconcile overhang?",
		'WFLG',
		/* [767] */
		"Scroller data",
		'DVDR',
		/* [768] */
		"Horizontal scroll bar left indent",
		'DWRD',
		/* [769] */
		"No scroll bar=-1",
		'CASE',
		/* [770] */
		"Horizontal scroll bar right indent",
		'DWRD',
		/* [771] */
		"Vertical scroll bar top indent",
		'DWRD',
		/* [772] */
		"No scroll bar=-1",
		'CASE',
		/* [773] */
		"Vertical scroll bar bottom indent",
		'DWRD',
		/* [774] */
		"Scrolling view ID",
		'DLNG',
		/* [775] */
		"",
		'KEYE',
		/* [776] */
		"ascr",
		'KEYB',
		/* [777] */
		"Pane data",
		'DVDR',
		/* [778] */
		"Pane ID",
		'DLNG',
		/* [779] */
		"Width",
		'DWRD',
		/* [780] */
		"Width of SuperView=-1",
		'CASE',
		/* [781] */
		"Height",
		'DWRD',
		/* [782] */
		"Height of SuperView=-1",
		'CASE',
		/* [783] */
		"Visible?",
		'BFLG',
		/* [784] */
		"Enabled?",
		'BFLG',
		/* [785] */
		"Left side bound?",
		'BFLG',
		/* [786] */
		"Top side bound?",
		'BFLG',
		/* [787] */
		"Right side bound?",
		'BFLG',
		/* [788] */
		"Bottom side bound?",
		'BFLG',
		/* [789] */
		"Left in super image",
		'DLNG',
		/* [790] */
		"Top in super image",
		'DLNG',
		/* [791] */
		"User constant",
		'DLNG',
		/* [792] */
		"Superview",
		'DLNG',
		/* [793] */
		"Default=-1",
		'CASE',
		/* [794] */
		"None=0",
		'CASE',
		/* [795] */
		"View data",
		'DVDR',
		/* [796] */
		"Image width",
		'DLNG',
		/* [797] */
		"Image height",
		'DLNG',
		/* [798] */
		"Horizontal scroll position",
		'DLNG',
		/* [799] */
		"Vertical scroll position",
		'DLNG',
		/* [800] */
		"Horizontal scroll unit",
		'DLNG',
		/* [801] */
		"Vertical scroll unit",
		'DLNG',
		/* [802] */
		"Reconcile overhang?",
		'WFLG',
		/* [803] */
		"Scroller data",
		'DVDR',
		/* [804] */
		"Horizontal scroll bar left indent",
		'DWRD',
		/* [805] */
		"No scroll bar=-1",
		'CASE',
		/* [806] */
		"Horizontal scroll bar right indent",
		'DWRD',
		/* [807] */
		"Vertical scroll bar top indent",
		'DWRD',
		/* [808] */
		"No scroll bar=-1",
		'CASE',
		/* [809] */
		"Vertical scroll bar bottom indent",
		'DWRD',
		/* [810] */
		"Scrolling view ID",
		'DLNG',
		/* [811] */
		"",
		'KEYE',
		/* [812] */
		"sclv",
		'KEYB',
		/* [813] */
		"Pane data",
		'DVDR',
		/* [814] */
		"Pane ID",
		'DLNG',
		/* [815] */
		"Width",
		'DWRD',
		/* [816] */
		"Width of SuperView=-1",
		'CASE',
		/* [817] */
		"Height",
		'DWRD',
		/* [818] */
		"Height of SuperView=-1",
		'CASE',
		/* [819] */
		"Visible?",
		'BFLG',
		/* [820] */
		"Enabled?",
		'BFLG',
		/* [821] */
		"Left side bound?",
		'BFLG',
		/* [822] */
		"Top side bound?",
		'BFLG',
		/* [823] */
		"Right side bound?",
		'BFLG',
		/* [824] */
		"Bottom side bound?",
		'BFLG',
		/* [825] */
		"Left in super image",
		'DLNG',
		/* [826] */
		"Top in super image",
		'DLNG',
		/* [827] */
		"User constant",
		'DLNG',
		/* [828] */
		"Superview",
		'DLNG',
		/* [829] */
		"Default=-1",
		'CASE',
		/* [830] */
		"None=0",
		'CASE',
		/* [831] */
		"View data",
		'DVDR',
		/* [832] */
		"Filler",
		'FWRD',
		/* [833] */
		"ScrollBar Thickness",
		'DWRD',
		/* [834] */
		"Normal=16",
		'CASE',
		/* [835] */
		"Floating Window=11",
		'CASE',
		/* [836] */
		"Image height",
		'DLNG',
		/* [837] */
		"Horizontal scroll position",
		'DLNG',
		/* [838] */
		"Vertical scroll position",
		'DLNG',
		/* [839] */
		"Horizontal scroll unit",
		'DLNG',
		/* [840] */
		"Vertical scroll unit",
		'DLNG',
		/* [841] */
		"Reconcile overhang?",
		'WFLG',
		/* [842] */
		"Scroller data",
		'DVDR',
		/* [843] */
		"Horizontal scroll bar left indent",
		'DWRD',
		/* [844] */
		"No scroll bar=-1",
		'CASE',
		/* [845] */
		"Horizontal scroll bar right indent",
		'DWRD',
		/* [846] */
		"Vertical scroll bar top indent",
		'DWRD',
		/* [847] */
		"No scroll bar=-1",
		'CASE',
		/* [848] */
		"Vertical scroll bar bottom indent",
		'DWRD',
		/* [849] */
		"Scrolling view ID",
		'DLNG',
		/* [850] */
		"Live Scrolling?",
		'BFLG',
		/* [851] */
		"",
		'KEYE',
		/* [852] */
		"pict",
		'KEYB',
		/* [853] */
		"Pane data",
		'DVDR',
		/* [854] */
		"Pane ID",
		'DLNG',
		/* [855] */
		"Width",
		'DWRD',
		/* [856] */
		"Height",
		'DWRD',
		/* [857] */
		"Visible?",
		'BFLG',
		/* [858] */
		"Enabled?",
		'BFLG',
		/* [859] */
		"Left side bound?",
		'BFLG',
		/* [860] */
		"Top side bound?",
		'BFLG',
		/* [861] */
		"Right side bound?",
		'BFLG',
		/* [862] */
		"Bottom side bound?",
		'BFLG',
		/* [863] */
		"Left in super image",
		'DLNG',
		/* [864] */
		"Top in super image",
		'DLNG',
		/* [865] */
		"User constant",
		'DLNG',
		/* [866] */
		"Superview",
		'DLNG',
		/* [867] */
		"Default=-1",
		'CASE',
		/* [868] */
		"None=0",
		'CASE',
		/* [869] */
		"View data",
		'DVDR',
		/* [870] */
		"Image width",
		'DLNG',
		/* [871] */
		"Image height",
		'DLNG',
		/* [872] */
		"Horizontal scroll position",
		'DLNG',
		/* [873] */
		"Vertical scroll position",
		'DLNG',
		/* [874] */
		"Horizontal scroll unit",
		'DLNG',
		/* [875] */
		"Vertical scroll unit",
		'DLNG',
		/* [876] */
		"Reconcile overhang?",
		'WFLG',
		/* [877] */
		"Picture data",
		'DVDR',
		/* [878] */
		"Resource ID of 'PICT'",
		'RSID',
		/* [879] */
		"",
		'KEYE',
		/* [880] */
		"plac",
		'KEYB',
		/* [881] */
		"Pane data",
		'DVDR',
		/* [882] */
		"Pane ID",
		'DLNG',
		/* [883] */
		"Width",
		'DWRD',
		/* [884] */
		"Height",
		'DWRD',
		/* [885] */
		"Visible?",
		'BFLG',
		/* [886] */
		"Enabled?",
		'BFLG',
		/* [887] */
		"Left side bound?",
		'BFLG',
		/* [888] */
		"Top side bound?",
		'BFLG',
		/* [889] */
		"Right side bound?",
		'BFLG',
		/* [890] */
		"Bottom side bound?",
		'BFLG',
		/* [891] */
		"Left in super image",
		'DLNG',
		/* [892] */
		"Top in super image",
		'DLNG',
		/* [893] */
		"User constant",
		'DLNG',
		/* [894] */
		"Superview",
		'DLNG',
		/* [895] */
		"Default=-1",
		'CASE',
		/* [896] */
		"None=0",
		'CASE',
		/* [897] */
		"View data",
		'DVDR',
		/* [898] */
		"Image width",
		'DLNG',
		/* [899] */
		"Image height",
		'DLNG',
		/* [900] */
		"Horizontal scroll position",
		'DLNG',
		/* [901] */
		"Vertical scroll position",
		'DLNG',
		/* [902] */
		"Horizontal scroll unit",
		'DLNG',
		/* [903] */
		"Vertical scroll unit",
		'DLNG',
		/* [904] */
		"Reconcile overhang?",
		'WFLG',
		/* [905] */
		"Placeholder data",
		'DVDR',
		/* [906] */
		"Alignment of occupant",
		'DWRD',
		/* [907] */
		"",
		'KEYE',
		/* [908] */
		"text",
		'KEYB',
		/* [909] */
		"Pane data",
		'DVDR',
		/* [910] */
		"Pane ID",
		'DLNG',
		/* [911] */
		"Width",
		'DWRD',
		/* [912] */
		"Height",
		'DWRD',
		/* [913] */
		"Visible?",
		'BFLG',
		/* [914] */
		"Enabled?",
		'BFLG',
		/* [915] */
		"Left side bound?",
		'BFLG',
		/* [916] */
		"Top side bound?",
		'BFLG',
		/* [917] */
		"Right side bound?",
		'BFLG',
		/* [918] */
		"Bottom side bound?",
		'BFLG',
		/* [919] */
		"Left in super image",
		'DLNG',
		/* [920] */
		"Top in super image",
		'DLNG',
		/* [921] */
		"User constant",
		'DLNG',
		/* [922] */
		"Superview",
		'DLNG',
		/* [923] */
		"Default=-1",
		'CASE',
		/* [924] */
		"None=0",
		'CASE',
		/* [925] */
		"View data",
		'DVDR',
		/* [926] */
		"Image width",
		'DLNG',
		/* [927] */
		"Image height",
		'DLNG',
		/* [928] */
		"Horizontal scroll position",
		'DLNG',
		/* [929] */
		"Vertical scroll position",
		'DLNG',
		/* [930] */
		"Horizontal scroll unit",
		'DLNG',
		/* [931] */
		"Vertical scroll unit",
		'DLNG',
		/* [932] */
		"Reconcile overhang?",
		'WFLG',
		/* [933] */
		"Text data",
		'DVDR',
		/* [934] */
		"Multi-style?",
		'WBIT',
		/* [935] */
		"Editable?",
		'WBIT',
		/* [936] */
		"Selectable?",
		'WBIT',
		/* [937] */
		"Word wrap?",
		'WBIT',
		/* [938] */
		"Reserved",
		'WB12',
		/* [939] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [940] */
		"System font=0",
		'CASE',
		/* [941] */
		"Resource ID of 'TEXT'",
		'RSID',
		/* [942] */
		"",
		'KEYE',
		/* [943] */
		"txtv",
		'KEYB',
		/* [944] */
		"Pane data",
		'DVDR',
		/* [945] */
		"Pane ID",
		'DLNG',
		/* [946] */
		"Width",
		'DWRD',
		/* [947] */
		"Height",
		'DWRD',
		/* [948] */
		"Visible?",
		'BFLG',
		/* [949] */
		"Enabled?",
		'BFLG',
		/* [950] */
		"Left side bound?",
		'BFLG',
		/* [951] */
		"Top side bound?",
		'BFLG',
		/* [952] */
		"Right side bound?",
		'BFLG',
		/* [953] */
		"Bottom side bound?",
		'BFLG',
		/* [954] */
		"Left in super image",
		'DLNG',
		/* [955] */
		"Top in super image",
		'DLNG',
		/* [956] */
		"User constant",
		'DLNG',
		/* [957] */
		"Superview",
		'DLNG',
		/* [958] */
		"Default=-1",
		'CASE',
		/* [959] */
		"None=0",
		'CASE',
		/* [960] */
		"View data",
		'DVDR',
		/* [961] */
		"Image width",
		'DLNG',
		/* [962] */
		"Image height",
		'DLNG',
		/* [963] */
		"Horizontal scroll position",
		'DLNG',
		/* [964] */
		"Vertical scroll position",
		'DLNG',
		/* [965] */
		"Horizontal scroll unit",
		'DLNG',
		/* [966] */
		"Vertical scroll unit",
		'DLNG',
		/* [967] */
		"Reconcile overhang?",
		'WFLG',
		/* [968] */
		"TextEditView data",
		'DVDR',
		/* [969] */
		"Multi-style?",
		'WBIT',
		/* [970] */
		"Editable?",
		'WBIT',
		/* [971] */
		"Selectable?",
		'WBIT',
		/* [972] */
		"Word wrap?",
		'WBIT',
		/* [973] */
		"Autoscroll?",
		'WBIT',
		/* [974] */
		"Reserved",
		'WB11',
		/* [975] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [976] */
		"System font=0",
		'CASE',
		/* [977] */
		"Resource ID of 'TEXT'",
		'RSID',
		/* [978] */
		"",
		'KEYE',
		/* [979] */
		"tabl",
		'KEYB',
		/* [980] */
		"Pane data",
		'DVDR',
		/* [981] */
		"Pane ID",
		'DLNG',
		/* [982] */
		"Width",
		'DWRD',
		/* [983] */
		"Height",
		'DWRD',
		/* [984] */
		"Visible?",
		'BFLG',
		/* [985] */
		"Enabled?",
		'BFLG',
		/* [986] */
		"Left side bound?",
		'BFLG',
		/* [987] */
		"Top side bound?",
		'BFLG',
		/* [988] */
		"Right side bound?",
		'BFLG',
		/* [989] */
		"Bottom side bound?",
		'BFLG',
		/* [990] */
		"Left in super image",
		'DLNG',
		/* [991] */
		"Top in super image",
		'DLNG',
		/* [992] */
		"User constant",
		'DLNG',
		/* [993] */
		"Superview",
		'DLNG',
		/* [994] */
		"Default=-1",
		'CASE',
		/* [995] */
		"None=0",
		'CASE',
		/* [996] */
		"View data",
		'DVDR',
		/* [997] */
		"Image width",
		'DLNG',
		/* [998] */
		"Image height",
		'DLNG',
		/* [999] */
		"Horizontal scroll position",
		'DLNG',
		/* [1000] */
		"Vertical scroll position",
		'DLNG',
		/* [1001] */
		"Horizontal scroll unit",
		'DLNG',
		/* [1002] */
		"Vertical scroll unit",
		'DLNG',
		/* [1003] */
		"Reconcile overhang?",
		'WFLG',
		/* [1004] */
		"Table data",
		'DVDR',
		/* [1005] */
		"Number of rows",
		'DLNG',
		/* [1006] */
		"Number of columns",
		'DLNG',
		/* [1007] */
		"Row height",
		'DLNG',
		/* [1008] */
		"Column width",
		'DLNG',
		/* [1009] */
		"Cell data size",
		'DLNG',
		/* [1010] */
		"",
		'KEYE',
		/* [1011] */
		"tabv",
		'KEYB',
		/* [1012] */
		"Pane data",
		'DVDR',
		/* [1013] */
		"Pane ID",
		'DLNG',
		/* [1014] */
		"Width",
		'DWRD',
		/* [1015] */
		"Height",
		'DWRD',
		/* [1016] */
		"Visible?",
		'BFLG',
		/* [1017] */
		"Enabled?",
		'BFLG',
		/* [1018] */
		"Left side bound?",
		'BFLG',
		/* [1019] */
		"Top side bound?",
		'BFLG',
		/* [1020] */
		"Right side bound?",
		'BFLG',
		/* [1021] */
		"Bottom side bound?",
		'BFLG',
		/* [1022] */
		"Left in super image",
		'DLNG',
		/* [1023] */
		"Top in super image",
		'DLNG',
		/* [1024] */
		"User constant",
		'DLNG',
		/* [1025] */
		"Superview",
		'DLNG',
		/* [1026] */
		"Default=-1",
		'CASE',
		/* [1027] */
		"None=0",
		'CASE',
		/* [1028] */
		"View data",
		'DVDR',
		/* [1029] */
		"Image width",
		'DLNG',
		/* [1030] */
		"Image height",
		'DLNG',
		/* [1031] */
		"Horizontal scroll position",
		'DLNG',
		/* [1032] */
		"Vertical scroll position",
		'DLNG',
		/* [1033] */
		"Horizontal scroll unit",
		'DLNG',
		/* [1034] */
		"Vertical scroll unit",
		'DLNG',
		/* [1035] */
		"Reconcile overhang?",
		'WFLG',
		/* [1036] */
		"",
		'KEYE',
		/* [1037] */
		"htab",
		'KEYB',
		/* [1038] */
		"Pane data",
		'DVDR',
		/* [1039] */
		"Pane ID",
		'DLNG',
		/* [1040] */
		"Width",
		'DWRD',
		/* [1041] */
		"Height",
		'DWRD',
		/* [1042] */
		"Visible?",
		'BFLG',
		/* [1043] */
		"Enabled?",
		'BFLG',
		/* [1044] */
		"Left side bound?",
		'BFLG',
		/* [1045] */
		"Top side bound?",
		'BFLG',
		/* [1046] */
		"Right side bound?",
		'BFLG',
		/* [1047] */
		"Bottom side bound?",
		'BFLG',
		/* [1048] */
		"Left in super image",
		'DLNG',
		/* [1049] */
		"Top in super image",
		'DLNG',
		/* [1050] */
		"User constant",
		'DLNG',
		/* [1051] */
		"Superview",
		'DLNG',
		/* [1052] */
		"Default=-1",
		'CASE',
		/* [1053] */
		"None=0",
		'CASE',
		/* [1054] */
		"View data",
		'DVDR',
		/* [1055] */
		"Image width",
		'DLNG',
		/* [1056] */
		"Image height",
		'DLNG',
		/* [1057] */
		"Horizontal scroll position",
		'DLNG',
		/* [1058] */
		"Vertical scroll position",
		'DLNG',
		/* [1059] */
		"Horizontal scroll unit",
		'DLNG',
		/* [1060] */
		"Vertical scroll unit",
		'DLNG',
		/* [1061] */
		"Reconcile overhang?",
		'WFLG',
		/* [1062] */
		"",
		'KEYE',
		/* [1063] */
		"txht",
		'KEYB',
		/* [1064] */
		"Pane data",
		'DVDR',
		/* [1065] */
		"Pane ID",
		'DLNG',
		/* [1066] */
		"Width",
		'DWRD',
		/* [1067] */
		"Height",
		'DWRD',
		/* [1068] */
		"Visible?",
		'BFLG',
		/* [1069] */
		"Enabled?",
		'BFLG',
		/* [1070] */
		"Left side bound?",
		'BFLG',
		/* [1071] */
		"Top side bound?",
		'BFLG',
		/* [1072] */
		"Right side bound?",
		'BFLG',
		/* [1073] */
		"Bottom side bound?",
		'BFLG',
		/* [1074] */
		"Left in super image",
		'DLNG',
		/* [1075] */
		"Top in super image",
		'DLNG',
		/* [1076] */
		"User constant",
		'DLNG',
		/* [1077] */
		"Superview",
		'DLNG',
		/* [1078] */
		"Default=-1",
		'CASE',
		/* [1079] */
		"None=0",
		'CASE',
		/* [1080] */
		"View data",
		'DVDR',
		/* [1081] */
		"Image width",
		'DLNG',
		/* [1082] */
		"Image height",
		'DLNG',
		/* [1083] */
		"Horizontal scroll position",
		'DLNG',
		/* [1084] */
		"Vertical scroll position",
		'DLNG',
		/* [1085] */
		"Horizontal scroll unit",
		'DLNG',
		/* [1086] */
		"Vertical scroll unit",
		'DLNG',
		/* [1087] */
		"Reconcile overhang?",
		'WFLG',
		/* [1088] */
		"",
		'KEYE',
		/* [1089] */
		"sitb",
		'KEYB',
		/* [1090] */
		"Pane data",
		'DVDR',
		/* [1091] */
		"Pane ID",
		'DLNG',
		/* [1092] */
		"Width",
		'DWRD',
		/* [1093] */
		"Height",
		'DWRD',
		/* [1094] */
		"Visible?",
		'BFLG',
		/* [1095] */
		"Enabled?",
		'BFLG',
		/* [1096] */
		"Left side bound?",
		'BFLG',
		/* [1097] */
		"Top side bound?",
		'BFLG',
		/* [1098] */
		"Right side bound?",
		'BFLG',
		/* [1099] */
		"Bottom side bound?",
		'BFLG',
		/* [1100] */
		"Left in super image",
		'DLNG',
		/* [1101] */
		"Top in super image",
		'DLNG',
		/* [1102] */
		"User constant",
		'DLNG',
		/* [1103] */
		"Superview",
		'DLNG',
		/* [1104] */
		"Default=-1",
		'CASE',
		/* [1105] */
		"None=0",
		'CASE',
		/* [1106] */
		"View data",
		'DVDR',
		/* [1107] */
		"Image width",
		'DLNG',
		/* [1108] */
		"Image height",
		'DLNG',
		/* [1109] */
		"Horizontal scroll position",
		'DLNG',
		/* [1110] */
		"Vertical scroll position",
		'DLNG',
		/* [1111] */
		"Horizontal scroll unit",
		'DLNG',
		/* [1112] */
		"Vertical scroll unit",
		'DLNG',
		/* [1113] */
		"Reconcile overhang?",
		'WFLG',
		/* [1114] */
		"",
		'KEYE',
		/* [1115] */
		"otab",
		'KEYB',
		/* [1116] */
		"Pane data",
		'DVDR',
		/* [1117] */
		"Pane ID",
		'DLNG',
		/* [1118] */
		"Width",
		'DWRD',
		/* [1119] */
		"Height",
		'DWRD',
		/* [1120] */
		"Visible?",
		'BFLG',
		/* [1121] */
		"Enabled?",
		'BFLG',
		/* [1122] */
		"Left side bound?",
		'BFLG',
		/* [1123] */
		"Top side bound?",
		'BFLG',
		/* [1124] */
		"Right side bound?",
		'BFLG',
		/* [1125] */
		"Bottom side bound?",
		'BFLG',
		/* [1126] */
		"Left in super image",
		'DLNG',
		/* [1127] */
		"Top in super image",
		'DLNG',
		/* [1128] */
		"User constant",
		'DLNG',
		/* [1129] */
		"Superview",
		'DLNG',
		/* [1130] */
		"Default=-1",
		'CASE',
		/* [1131] */
		"None=0",
		'CASE',
		/* [1132] */
		"View data",
		'DVDR',
		/* [1133] */
		"Image width",
		'DLNG',
		/* [1134] */
		"Image height",
		'DLNG',
		/* [1135] */
		"Horizontal scroll position",
		'DLNG',
		/* [1136] */
		"Vertical scroll position",
		'DLNG',
		/* [1137] */
		"Horizontal scroll unit",
		'DLNG',
		/* [1138] */
		"Vertical scroll unit",
		'DLNG',
		/* [1139] */
		"Reconcile overhang?",
		'WFLG',
		/* [1140] */
		"Text traits",
		'RSID',
		/* [1141] */
		"First level indent",
		'DWRD',
		/* [1142] */
		"",
		'KEYE',
		/* [1143] */
		"colv",
		'KEYB',
		/* [1144] */
		"Pane data",
		'DVDR',
		/* [1145] */
		"Pane ID",
		'DLNG',
		/* [1146] */
		"Width",
		'DWRD',
		/* [1147] */
		"Height",
		'DWRD',
		/* [1148] */
		"Visible?",
		'BFLG',
		/* [1149] */
		"Enabled?",
		'BFLG',
		/* [1150] */
		"Left side bound?",
		'BFLG',
		/* [1151] */
		"Top side bound?",
		'BFLG',
		/* [1152] */
		"Right side bound?",
		'BFLG',
		/* [1153] */
		"Bottom side bound?",
		'BFLG',
		/* [1154] */
		"Left in super image",
		'DLNG',
		/* [1155] */
		"Top in super image",
		'DLNG',
		/* [1156] */
		"User constant",
		'DLNG',
		/* [1157] */
		"Superview",
		'DLNG',
		/* [1158] */
		"Default=-1",
		'CASE',
		/* [1159] */
		"None=0",
		'CASE',
		/* [1160] */
		"View data",
		'DVDR',
		/* [1161] */
		"Image width",
		'DLNG',
		/* [1162] */
		"Image height",
		'DLNG',
		/* [1163] */
		"Horizontal scroll position",
		'DLNG',
		/* [1164] */
		"Vertical scroll position",
		'DLNG',
		/* [1165] */
		"Horizontal scroll unit",
		'DLNG',
		/* [1166] */
		"Vertical scroll unit",
		'DLNG',
		/* [1167] */
		"Reconcile overhang?",
		'WFLG',
		/* [1168] */
		"Column width",
		'DWRD',
		/* [1169] */
		"Row height",
		'DWRD',
		/* [1170] */
		"Use single selector",
		'BFLG',
		/* [1171] */
		"Use drag select",
		'BFLG',
		/* [1172] */
		"Data size",
		'DLNG',
		/* [1173] */
		"Double-click message",
		'DLNG',
		/* [1174] */
		"Selection message",
		'DLNG',
		/* [1175] */
		"",
		'KEYE',
		/* [1176] */
		"txcl",
		'KEYB',
		/* [1177] */
		"Pane data",
		'DVDR',
		/* [1178] */
		"Pane ID",
		'DLNG',
		/* [1179] */
		"Width",
		'DWRD',
		/* [1180] */
		"Height",
		'DWRD',
		/* [1181] */
		"Visible?",
		'BFLG',
		/* [1182] */
		"Enabled?",
		'BFLG',
		/* [1183] */
		"Left side bound?",
		'BFLG',
		/* [1184] */
		"Top side bound?",
		'BFLG',
		/* [1185] */
		"Right side bound?",
		'BFLG',
		/* [1186] */
		"Bottom side bound?",
		'BFLG',
		/* [1187] */
		"Left in super image",
		'DLNG',
		/* [1188] */
		"Top in super image",
		'DLNG',
		/* [1189] */
		"User constant",
		'DLNG',
		/* [1190] */
		"Superview",
		'DLNG',
		/* [1191] */
		"Default=-1",
		'CASE',
		/* [1192] */
		"None=0",
		'CASE',
		/* [1193] */
		"View data",
		'DVDR',
		/* [1194] */
		"Image width",
		'DLNG',
		/* [1195] */
		"Image height",
		'DLNG',
		/* [1196] */
		"Horizontal scroll position",
		'DLNG',
		/* [1197] */
		"Vertical scroll position",
		'DLNG',
		/* [1198] */
		"Horizontal scroll unit",
		'DLNG',
		/* [1199] */
		"Vertical scroll unit",
		'DLNG',
		/* [1200] */
		"Reconcile overhang?",
		'WFLG',
		/* [1201] */
		"Column width",
		'DWRD',
		/* [1202] */
		"Row height",
		'DWRD',
		/* [1203] */
		"Use single selector",
		'BFLG',
		/* [1204] */
		"Use drag select",
		'BFLG',
		/* [1205] */
		"Data size",
		'DLNG',
		/* [1206] */
		"Double-click message",
		'DLNG',
		/* [1207] */
		"Selection message",
		'DLNG',
		/* [1208] */
		"Text Traits",
		'RSID',
		/* [1209] */
		"STR# resource ID",
		'RSID',
		/* [1210] */
		"",
		'KEYE',
		/* [1211] */
		"offv",
		'KEYB',
		/* [1212] */
		"Pane data",
		'DVDR',
		/* [1213] */
		"Pane ID",
		'DLNG',
		/* [1214] */
		"Width",
		'DWRD',
		/* [1215] */
		"Height",
		'DWRD',
		/* [1216] */
		"Visible?",
		'BFLG',
		/* [1217] */
		"Enabled?",
		'BFLG',
		/* [1218] */
		"Left side bound?",
		'BFLG',
		/* [1219] */
		"Top side bound?",
		'BFLG',
		/* [1220] */
		"Right side bound?",
		'BFLG',
		/* [1221] */
		"Bottom side bound?",
		'BFLG',
		/* [1222] */
		"Left in super image",
		'DLNG',
		/* [1223] */
		"Top in super image",
		'DLNG',
		/* [1224] */
		"User constant",
		'DLNG',
		/* [1225] */
		"Superview",
		'DLNG',
		/* [1226] */
		"Default=-1",
		'CASE',
		/* [1227] */
		"None=0",
		'CASE',
		/* [1228] */
		"View data",
		'DVDR',
		/* [1229] */
		"Image width",
		'DLNG',
		/* [1230] */
		"Image height",
		'DLNG',
		/* [1231] */
		"Horizontal scroll position",
		'DLNG',
		/* [1232] */
		"Vertical scroll position",
		'DLNG',
		/* [1233] */
		"Horizontal scroll unit",
		'DLNG',
		/* [1234] */
		"Vertical scroll unit",
		'DLNG',
		/* [1235] */
		"Reconcile overhang?",
		'WFLG',
		/* [1236] */
		"",
		'KEYE',
		/* [1237] */
		"ovlv",
		'KEYB',
		/* [1238] */
		"Pane data",
		'DVDR',
		/* [1239] */
		"Pane ID",
		'DLNG',
		/* [1240] */
		"Width",
		'DWRD',
		/* [1241] */
		"Height",
		'DWRD',
		/* [1242] */
		"Visible?",
		'BFLG',
		/* [1243] */
		"Enabled?",
		'BFLG',
		/* [1244] */
		"Left side bound?",
		'BFLG',
		/* [1245] */
		"Top side bound?",
		'BFLG',
		/* [1246] */
		"Right side bound?",
		'BFLG',
		/* [1247] */
		"Bottom side bound?",
		'BFLG',
		/* [1248] */
		"Left in super image",
		'DLNG',
		/* [1249] */
		"Top in super image",
		'DLNG',
		/* [1250] */
		"User constant",
		'DLNG',
		/* [1251] */
		"Superview",
		'DLNG',
		/* [1252] */
		"Default=-1",
		'CASE',
		/* [1253] */
		"None=0",
		'CASE',
		/* [1254] */
		"View data",
		'DVDR',
		/* [1255] */
		"Image width",
		'DLNG',
		/* [1256] */
		"Image height",
		'DLNG',
		/* [1257] */
		"Horizontal scroll position",
		'DLNG',
		/* [1258] */
		"Vertical scroll position",
		'DLNG',
		/* [1259] */
		"Horizontal scroll unit",
		'DLNG',
		/* [1260] */
		"Vertical scroll unit",
		'DLNG',
		/* [1261] */
		"Reconcile overhang?",
		'WFLG',
		/* [1262] */
		"",
		'KEYE',
		/* [1263] */
		"solv",
		'KEYB',
		/* [1264] */
		"Pane data",
		'DVDR',
		/* [1265] */
		"Pane ID",
		'DLNG',
		/* [1266] */
		"Width",
		'DWRD',
		/* [1267] */
		"Height",
		'DWRD',
		/* [1268] */
		"Visible?",
		'BFLG',
		/* [1269] */
		"Enabled?",
		'BFLG',
		/* [1270] */
		"Left side bound?",
		'BFLG',
		/* [1271] */
		"Top side bound?",
		'BFLG',
		/* [1272] */
		"Right side bound?",
		'BFLG',
		/* [1273] */
		"Bottom side bound?",
		'BFLG',
		/* [1274] */
		"Left in super image",
		'DLNG',
		/* [1275] */
		"Top in super image",
		'DLNG',
		/* [1276] */
		"User constant",
		'DLNG',
		/* [1277] */
		"Superview",
		'DLNG',
		/* [1278] */
		"Default=-1",
		'CASE',
		/* [1279] */
		"None=0",
		'CASE',
		/* [1280] */
		"View data",
		'DVDR',
		/* [1281] */
		"Image width",
		'DLNG',
		/* [1282] */
		"Image height",
		'DLNG',
		/* [1283] */
		"Horizontal scroll position",
		'DLNG',
		/* [1284] */
		"Vertical scroll position",
		'DLNG',
		/* [1285] */
		"Horizontal scroll unit",
		'DLNG',
		/* [1286] */
		"Vertical scroll unit",
		'DLNG',
		/* [1287] */
		"Reconcile overhang?",
		'WFLG',
		/* [1288] */
		"",
		'KEYE',
		/* [1289] */
		"rgpv",
		'KEYB',
		/* [1290] */
		"Pane data",
		'DVDR',
		/* [1291] */
		"Pane ID",
		'DLNG',
		/* [1292] */
		"Width",
		'DWRD',
		/* [1293] */
		"Height",
		'DWRD',
		/* [1294] */
		"Visible?",
		'BFLG',
		/* [1295] */
		"Enabled?",
		'BFLG',
		/* [1296] */
		"Left side bound?",
		'BFLG',
		/* [1297] */
		"Top side bound?",
		'BFLG',
		/* [1298] */
		"Right side bound?",
		'BFLG',
		/* [1299] */
		"Bottom side bound?",
		'BFLG',
		/* [1300] */
		"Left in super image",
		'DLNG',
		/* [1301] */
		"Top in super image",
		'DLNG',
		/* [1302] */
		"User constant",
		'DLNG',
		/* [1303] */
		"Superview",
		'DLNG',
		/* [1304] */
		"Default=-1",
		'CASE',
		/* [1305] */
		"None=0",
		'CASE',
		/* [1306] */
		"View data",
		'DVDR',
		/* [1307] */
		"Image width",
		'DLNG',
		/* [1308] */
		"Image height",
		'DLNG',
		/* [1309] */
		"Horizontal scroll position",
		'DLNG',
		/* [1310] */
		"Vertical scroll position",
		'DLNG',
		/* [1311] */
		"Horizontal scroll unit",
		'DLNG',
		/* [1312] */
		"Vertical scroll unit",
		'DLNG',
		/* [1313] */
		"Reconcile overhang?",
		'WFLG',
		/* [1314] */
		"",
		'KEYE',
		/* [1315] */
		"mpvw",
		'KEYB',
		/* [1316] */
		"Pane data",
		'DVDR',
		/* [1317] */
		"Pane ID",
		'DLNG',
		/* [1318] */
		"Width",
		'DWRD',
		/* [1319] */
		"Height",
		'DWRD',
		/* [1320] */
		"Visible?",
		'BFLG',
		/* [1321] */
		"Enabled?",
		'BFLG',
		/* [1322] */
		"Left side bound?",
		'BFLG',
		/* [1323] */
		"Top side bound?",
		'BFLG',
		/* [1324] */
		"Right side bound?",
		'BFLG',
		/* [1325] */
		"Bottom side bound?",
		'BFLG',
		/* [1326] */
		"Left in super image",
		'DLNG',
		/* [1327] */
		"Top in super image",
		'DLNG',
		/* [1328] */
		"User constant",
		'DLNG',
		/* [1329] */
		"Superview",
		'DLNG',
		/* [1330] */
		"Default=-1",
		'CASE',
		/* [1331] */
		"None=0",
		'CASE',
		/* [1332] */
		"View data",
		'DVDR',
		/* [1333] */
		"Image width",
		'DLNG',
		/* [1334] */
		"Image height",
		'DLNG',
		/* [1335] */
		"Horizontal scroll position",
		'DLNG',
		/* [1336] */
		"Vertical scroll position",
		'DLNG',
		/* [1337] */
		"Horizontal scroll unit",
		'DLNG',
		/* [1338] */
		"Vertical scroll unit",
		'DLNG',
		/* [1339] */
		"Reconcile overhang?",
		'WFLG',
		/* [1340] */
		"MultiPanelView data",
		'DVDR',
		/* [1341] */
		"Count:",
		'OCNT',
		/* [1342] */
		"List of Panels",
		'LSTC',
		/* [1343] */
		"Panel ID ('PPob')",
		'RSID',
		/* [1344] */
		"*****",
		'LSTE',
		/* [1345] */
		"Initial Panel Choice",
		'DWRD',
		/* [1346] */
		"Switch Message",
		'DLNG',
		/* [1347] */
		"Listen to SuperView?",
		'BFLG',
		/* [1348] */
		"",
		'KEYE',
		/* [1349] */
		"tbgv",
		'KEYB',
		/* [1350] */
		"Pane data",
		'DVDR',
		/* [1351] */
		"Pane ID",
		'DLNG',
		/* [1352] */
		"Width",
		'DWRD',
		/* [1353] */
		"Height",
		'DWRD',
		/* [1354] */
		"Visible?",
		'BFLG',
		/* [1355] */
		"Enabled?",
		'BFLG',
		/* [1356] */
		"Left side bound?",
		'BFLG',
		/* [1357] */
		"Top side bound?",
		'BFLG',
		/* [1358] */
		"Right side bound?",
		'BFLG',
		/* [1359] */
		"Bottom side bound?",
		'BFLG',
		/* [1360] */
		"Left in super image",
		'DLNG',
		/* [1361] */
		"Top in super image",
		'DLNG',
		/* [1362] */
		"User constant",
		'DLNG',
		/* [1363] */
		"Superview",
		'DLNG',
		/* [1364] */
		"Default=-1",
		'CASE',
		/* [1365] */
		"None=0",
		'CASE',
		/* [1366] */
		"View data",
		'DVDR',
		/* [1367] */
		"Image width",
		'DLNG',
		/* [1368] */
		"Image height",
		'DLNG',
		/* [1369] */
		"Horizontal scroll position",
		'DLNG',
		/* [1370] */
		"Vertical scroll position",
		'DLNG',
		/* [1371] */
		"Horizontal scroll unit",
		'DLNG',
		/* [1372] */
		"Vertical scroll unit",
		'DLNG',
		/* [1373] */
		"Reconcile overhang?",
		'WFLG',
		/* [1374] */
		"",
		'KEYE',
		/* [1375] */
		"tabg",
		'KEYB',
		/* [1376] */
		"",
		'KEYE',
		/* [1377] */
		"radg",
		'KEYB',
		/* [1378] */
		"Count:",
		'OCNT',
		/* [1379] */
		"List of Radio buttons",
		'LSTC',
		/* [1380] */
		"Pane ID",
		'DLNG',
		/* [1381] */
		"*****",
		'LSTE',
		/* [1382] */
		"",
		'KEYE',
		/* [1383] */
		"atta",
		'KEYB',
		/* [1384] */
		"Message",
		'DLNG',
		/* [1385] */
		"Any=-2",
		'CASE',
		/* [1386] */
		"Event=810",
		'CASE',
		/* [1387] */
		"DrawOrPrint=811",
		'CASE',
		/* [1388] */
		"Click=812",
		'CASE',
		/* [1389] */
		"AdjustCursor=813",
		'CASE',
		/* [1390] */
		"KeyPress=814",
		'CASE',
		/* [1391] */
		"CommandStatus=815",
		'CASE',
		/* [1392] */
		"PostAction=816",
		'CASE',
		/* [1393] */
		"Execute Host",
		'BFLG',
		/* [1394] */
		"Host Owns Me",
		'BFLG',
		/* [1395] */
		"",
		'KEYE',
		/* [1396] */
		"atch",
		'KEYB',
		/* [1397] */
		"Message",
		'DLNG',
		/* [1398] */
		"Any=-2",
		'CASE',
		/* [1399] */
		"Event=810",
		'CASE',
		/* [1400] */
		"DrawOrPrint=811",
		'CASE',
		/* [1401] */
		"Click=812",
		'CASE',
		/* [1402] */
		"AdjustCursor=813",
		'CASE',
		/* [1403] */
		"KeyPress=814",
		'CASE',
		/* [1404] */
		"CommandStatus=815",
		'CASE',
		/* [1405] */
		"PostAction=816",
		'CASE',
		/* [1406] */
		"Execute Host",
		'BFLG',
		/* [1407] */
		"Host Owns Me",
		'BFLG',
		/* [1408] */
		"",
		'KEYE',
		/* [1409] */
		"beep",
		'KEYB',
		/* [1410] */
		"Message",
		'DLNG',
		/* [1411] */
		"Any=-2",
		'CASE',
		/* [1412] */
		"Event=810",
		'CASE',
		/* [1413] */
		"DrawOrPrint=811",
		'CASE',
		/* [1414] */
		"Click=812",
		'CASE',
		/* [1415] */
		"AdjustCursor=813",
		'CASE',
		/* [1416] */
		"KeyPress=814",
		'CASE',
		/* [1417] */
		"CommandStatus=815",
		'CASE',
		/* [1418] */
		"PostAction=816",
		'CASE',
		/* [1419] */
		"Execute Host",
		'BFLG',
		/* [1420] */
		"Host Owns Me",
		'BFLG',
		/* [1421] */
		"",
		'KEYE',
		/* [1422] */
		"eras",
		'KEYB',
		/* [1423] */
		"Message",
		'DLNG',
		/* [1424] */
		"DrawOrPrint=811",
		'CASE',
		/* [1425] */
		"Execute Host",
		'BFLG',
		/* [1426] */
		"Host Owns Me",
		'BFLG',
		/* [1427] */
		"",
		'KEYE',
		/* [1428] */
		"cers",
		'KEYB',
		/* [1429] */
		"Message",
		'DLNG',
		/* [1430] */
		"DrawOrPrint=811",
		'CASE',
		/* [1431] */
		"Execute Host",
		'BFLG',
		/* [1432] */
		"Host Owns Me",
		'BFLG',
		/* [1433] */
		"ColorErase data",
		'DVDR',
		/* [1434] */
		"ForeColor",
		'COLR',
		/* [1435] */
		"BackColor",
		'COLR',
		/* [1436] */
		"",
		'KEYE',
		/* [1437] */
		"brda",
		'KEYB',
		/* [1438] */
		"Message",
		'DLNG',
		/* [1439] */
		"DrawOrPrint=811",
		'CASE',
		/* [1440] */
		"Execute Host",
		'BFLG',
		/* [1441] */
		"Host Owns Me",
		'BFLG',
		/* [1442] */
		"Border data",
		'DVDR',
		/* [1443] */
		"Pen Size",
		'PNT ',
		/* [1444] */
		"Pen Mode",
		'DWRD',
		/* [1445] */
		"Pen Pattern",
		'DWRD',
		/* [1446] */
		"Dark Gray=0",
		'CASE',
		/* [1447] */
		"Light Gray=1",
		'CASE',
		/* [1448] */
		"Gray=2",
		'CASE',
		/* [1449] */
		"Black=3",
		'CASE',
		/* [1450] */
		"White=4",
		'CASE',
		/* [1451] */
		"ForeColor",
		'COLR',
		/* [1452] */
		"BackColor",
		'COLR',
		/* [1453] */
		"",
		'KEYE',
		/* [1454] */
		"pnta",
		'KEYB',
		/* [1455] */
		"Message",
		'DLNG',
		/* [1456] */
		"DrawOrPrint=811",
		'CASE',
		/* [1457] */
		"Execute Host",
		'BFLG',
		/* [1458] */
		"Host Owns Me",
		'BFLG',
		/* [1459] */
		"Paint data",
		'DVDR',
		/* [1460] */
		"Pen Size",
		'PNT ',
		/* [1461] */
		"Pen Mode",
		'DWRD',
		/* [1462] */
		"Pen Pattern",
		'DWRD',
		/* [1463] */
		"Dark Gray=0",
		'CASE',
		/* [1464] */
		"Light Gray=1",
		'CASE',
		/* [1465] */
		"Gray=2",
		'CASE',
		/* [1466] */
		"Black=3",
		'CASE',
		/* [1467] */
		"White=4",
		'CASE',
		/* [1468] */
		"ForeColor",
		'COLR',
		/* [1469] */
		"BackColor",
		'COLR',
		/* [1470] */
		"",
		'KEYE',
		/* [1471] */
		"cena",
		'KEYB',
		/* [1472] */
		"Message",
		'DLNG',
		/* [1473] */
		"CommandStatus=815",
		'CASE',
		/* [1474] */
		"Execute Host",
		'BFLG',
		/* [1475] */
		"Host Owns Me",
		'BFLG',
		/* [1476] */
		"CmdEnabler data",
		'DVDR',
		/* [1477] */
		"Command to Enable",
		'DLNG',
		/* [1478] */
		"",
		'KEYE',
		/* [1479] */
		"ksca",
		'KEYB',
		/* [1480] */
		"Message",
		'DLNG',
		/* [1481] */
		"KeyPress=814",
		'CASE',
		/* [1482] */
		"Execute Host",
		'BFLG',
		/* [1483] */
		"Host Owns Me",
		'BFLG',
		/* [1484] */
		"",
		'KEYE',
		/* [1485] */
		"cmat",
		'KEYB',
		/* [1486] */
		"Message",
		'DLNG',
		/* [1487] */
		"Any=-2",
		'CASE',
		/* [1488] */
		"Execute Host",
		'BFLG',
		/* [1489] */
		"Host Owns Me",
		'BFLG',
		/* [1490] */
		"ContextualMenu data",
		'DVDR',
		/* [1491] */
		"'MENU' ID",
		'RSID',
		/* [1492] */
		"'CURS' ID",
		'RSID',
		/* [1493] */
		"Help Type",
		'ULNG',
		/* [1494] */
		"No Help=0",
		'CASE',
		/* [1495] */
		"Apple Guide =1",
		'CASE',
		/* [1496] */
		"Other Help=2",
		'CASE',
		/* [1497] */
		"Help Item Text",
		'PSTR',
		/* [1498] */
		"Number of Commands",
		'OCNT',
		/* [1499] */
		"****",
		'LSTC',
		/* [1500] */
		"Command Number",
		'DLNG',
		/* [1501] */
		"cmd_Nothing=0",
		'CASE',
		/* [1502] */
		"cmd_About=1",
		'CASE',
		/* [1503] */
		"cmd_New=2",
		'CASE',
		/* [1504] */
		"cmd_Open=3",
		'CASE',
		/* [1505] */
		"cmd_Close=4",
		'CASE',
		/* [1506] */
		"cmd_Save=5",
		'CASE',
		/* [1507] */
		"cmd_SaveAs=6",
		'CASE',
		/* [1508] */
		"cmd_Revert=7",
		'CASE',
		/* [1509] */
		"cmd_PageSetup=8",
		'CASE',
		/* [1510] */
		"cmd_Print=9",
		'CASE',
		/* [1511] */
		"cmd_PrintOne=17",
		'CASE',
		/* [1512] */
		"cmd_Quit=10",
		'CASE',
		/* [1513] */
		"cmd_Undo=11",
		'CASE',
		/* [1514] */
		"cmd_Cut=12",
		'CASE',
		/* [1515] */
		"cmd_Copy=13",
		'CASE',
		/* [1516] */
		"cmd_Paste=14",
		'CASE',
		/* [1517] */
		"cmd_Clear=15",
		'CASE',
		/* [1518] */
		"cmd_SelectAll=16",
		'CASE',
		/* [1519] */
		"****",
		'LSTE',
		/* [1520] */
		"",
		'KEYE',
		/* [1521] */
		"wtha",
		'KEYB',
		/* [1522] */
		"Message",
		'DLNG',
		/* [1523] */
		"FinishCreate=817",
		'CASE',
		/* [1524] */
		"Execute Host",
		'BFLG',
		/* [1525] */
		"Host Owns Me",
		'BFLG',
		/* [1526] */
		"WindowTheme data",
		'DVDR',
		/* [1527] */
		"Active Background Brush",
		'DWRD',
		/* [1528] */
		"Default=0",
		'CASE',
		/* [1529] */
		"Dialog=1",
		'CASE',
		/* [1530] */
		"Alert=3",
		'CASE',
		/* [1531] */
		"Modeless Dialog=5",
		'CASE',
		/* [1532] */
		"Utility Window=7",
		'CASE',
		/* [1533] */
		"Document Window=15",
		'CASE',
		/* [1534] */
		"Inactive Background Brush",
		'DWRD',
		/* [1535] */
		"Default=0",
		'CASE',
		/* [1536] */
		"Dialog=2",
		'CASE',
		/* [1537] */
		"Alert=4",
		'CASE',
		/* [1538] */
		"Modeless Dialog=6",
		'CASE',
		/* [1539] */
		"Utility Window=8",
		'CASE',
		/* [1540] */
		"Document Window=15",
		'CASE',
		/* [1541] */
		"Active Text Color",
		'DWRD',
		/* [1542] */
		"Default=0",
		'CASE',
		/* [1543] */
		"Dialog=1",
		'CASE',
		/* [1544] */
		"Alert=3",
		'CASE',
		/* [1545] */
		"Modeless Dialog=5",
		'CASE',
		/* [1546] */
		"Inactive Text Color",
		'DWRD',
		/* [1547] */
		"Default=0",
		'CASE',
		/* [1548] */
		"Dialog=2",
		'CASE',
		/* [1549] */
		"Alert=4",
		'CASE',
		/* [1550] */
		"Modeless Dialog=6",
		'CASE',
		/* [1551] */
		"",
		'KEYE',
		/* [1552] */
		"bbut",
		'KEYB',
		/* [1553] */
		"Pane data",
		'DVDR',
		/* [1554] */
		"Pane ID",
		'DLNG',
		/* [1555] */
		"Width",
		'DWRD',
		/* [1556] */
		"Height",
		'DWRD',
		/* [1557] */
		"Visible?",
		'BFLG',
		/* [1558] */
		"Enabled?",
		'BFLG',
		/* [1559] */
		"Left side bound?",
		'BFLG',
		/* [1560] */
		"Top side bound?",
		'BFLG',
		/* [1561] */
		"Right side bound?",
		'BFLG',
		/* [1562] */
		"Bottom side bound?",
		'BFLG',
		/* [1563] */
		"Left in super image",
		'DLNG',
		/* [1564] */
		"Top in super image",
		'DLNG',
		/* [1565] */
		"User constant",
		'DLNG',
		/* [1566] */
		"Superview",
		'DLNG',
		/* [1567] */
		"Default=-1",
		'CASE',
		/* [1568] */
		"None=0",
		'CASE',
		/* [1569] */
		"BevelButton data",
		'DVDR',
		/* [1570] */
		"Value changed message",
		'DLNG',
		/* [1571] */
		"Filler",
		'FWRD',
		/* [1572] */
		"'MENU' id",
		'RSID',
		/* [1573] */
		"Filler",
		'FWRD',
		/* [1574] */
		"Offset Contents?",
		'BBIT',
		/* [1575] */
		"MultiValue Menu?",
		'BBIT',
		/* [1576] */
		"Behavior",
		'BB06',
		/* [1577] */
		"PushButton=0",
		'CASE',
		/* [1578] */
		"Toggles=1",
		'CASE',
		/* [1579] */
		"Sticky=2",
		'CASE',
		/* [1580] */
		"Content Type",
		'DBYT',
		/* [1581] */
		"Text Only=0",
		'CASE',
		/* [1582] */
		"Icon Suite Resource=1",
		'CASE',
		/* [1583] */
		"cicn Resource=2",
		'CASE',
		/* [1584] */
		"PICT Resource=3",
		'CASE',
		/* [1585] */
		"Icon Suite Handle=129",
		'CASE',
		/* [1586] */
		"cicn Handle=130",
		'CASE',
		/* [1587] */
		"PICT Handle=131",
		'CASE',
		/* [1588] */
		"Icon Reference=132",
		'CASE',
		/* [1589] */
		"Filler",
		'FWRD',
		/* [1590] */
		"Content Resource ID",
		'DWRD',
		/* [1591] */
		"Filler",
		'FBYT',
		/* [1592] */
		"Proc ID",
		'BB04',
		/* [1593] */
		"BevelButton=2",
		'CASE',
		/* [1594] */
		"Filler bit (ignore)",
		'BBIT',
		/* [1595] */
		"Arrow Direction (Down=0, Right=1)",
		'BBIT',
		/* [1596] */
		"Bevel Size",
		'BB02',
		/* [1597] */
		"Small=0",
		'CASE',
		/* [1598] */
		"Normal=1",
		'CASE',
		/* [1599] */
		"Large=2",
		'CASE',
		/* [1600] */
		"Text Traits ('Txtr') ID",
		'RSID',
		/* [1601] */
		"Title",
		'PSTR',
		/* [1602] */
		"Initial Value",
		'DWRD',
		/* [1603] */
		"Title Placement",
		'DWRD',
		/* [1604] */
		"System Direction=-1",
		'CASE',
		/* [1605] */
		"Normally=0",
		'CASE',
		/* [1606] */
		"Right of Graphic=1",
		'CASE',
		/* [1607] */
		"Left of Graphic=2",
		'CASE',
		/* [1608] */
		"Below Graphic=3",
		'CASE',
		/* [1609] */
		"Above Graphic=4",
		'CASE',
		/* [1610] */
		"Title Alignment",
		'DWRD',
		/* [1611] */
		"Flush Default=0",
		'CASE',
		/* [1612] */
		"Center=1",
		'CASE',
		/* [1613] */
		"Flush Right=-1",
		'CASE',
		/* [1614] */
		"Flush Left=-2",
		'CASE',
		/* [1615] */
		"Title Pixel Offset",
		'DWRD',
		/* [1616] */
		"Graphic Alignment",
		'DWRD',
		/* [1617] */
		"System Direction=-1",
		'CASE',
		/* [1618] */
		"Center=0",
		'CASE',
		/* [1619] */
		"Left=1",
		'CASE',
		/* [1620] */
		"Right=2",
		'CASE',
		/* [1621] */
		"Top=3",
		'CASE',
		/* [1622] */
		"Bottom=4",
		'CASE',
		/* [1623] */
		"Top Left=5",
		'CASE',
		/* [1624] */
		"Bottom Left=6",
		'CASE',
		/* [1625] */
		"Top Right=7",
		'CASE',
		/* [1626] */
		"Bottom Right=8",
		'CASE',
		/* [1627] */
		"Graphic Offset",
		'PNT ',
		/* [1628] */
		"Center Popup Arrow?",
		'BFLG',
		/* [1629] */
		"",
		'KEYE',
		/* [1630] */
		"carr",
		'KEYB',
		/* [1631] */
		"Pane data",
		'DVDR',
		/* [1632] */
		"Pane ID",
		'DLNG',
		/* [1633] */
		"Width",
		'DWRD',
		/* [1634] */
		"Height",
		'DWRD',
		/* [1635] */
		"Visible?",
		'BFLG',
		/* [1636] */
		"Enabled?",
		'BFLG',
		/* [1637] */
		"Left side bound?",
		'BFLG',
		/* [1638] */
		"Top side bound?",
		'BFLG',
		/* [1639] */
		"Right side bound?",
		'BFLG',
		/* [1640] */
		"Bottom side bound?",
		'BFLG',
		/* [1641] */
		"Left in super image",
		'DLNG',
		/* [1642] */
		"Top in super image",
		'DLNG',
		/* [1643] */
		"User constant",
		'DLNG',
		/* [1644] */
		"Superview",
		'DLNG',
		/* [1645] */
		"Default=-1",
		'CASE',
		/* [1646] */
		"None=0",
		'CASE',
		/* [1647] */
		"ChasingArrows data",
		'DVDR',
		/* [1648] */
		"Value changed message",
		'DLNG',
		/* [1649] */
		"Initial value",
		'DLNG',
		/* [1650] */
		"Minimum value",
		'DLNG',
		/* [1651] */
		"Maximum value",
		'DLNG',
		/* [1652] */
		"ChasingArrows Proc",
		'DWRD',
		/* [1653] */
		"Default=112",
		'CASE',
		/* [1654] */
		"Text traits (unused)",
		'DWRD',
		/* [1655] */
		"Title",
		'PSTR',
		/* [1656] */
		"",
		'KEYE',
		/* [1657] */
		"chbx",
		'KEYB',
		/* [1658] */
		"Pane data",
		'DVDR',
		/* [1659] */
		"Pane ID",
		'DLNG',
		/* [1660] */
		"Width",
		'DWRD',
		/* [1661] */
		"Height",
		'DWRD',
		/* [1662] */
		"Visible?",
		'BFLG',
		/* [1663] */
		"Enabled?",
		'BFLG',
		/* [1664] */
		"Left side bound?",
		'BFLG',
		/* [1665] */
		"Top side bound?",
		'BFLG',
		/* [1666] */
		"Right side bound?",
		'BFLG',
		/* [1667] */
		"Bottom side bound?",
		'BFLG',
		/* [1668] */
		"Left in super image",
		'DLNG',
		/* [1669] */
		"Top in super image",
		'DLNG',
		/* [1670] */
		"User constant",
		'DLNG',
		/* [1671] */
		"Superview",
		'DLNG',
		/* [1672] */
		"Default=-1",
		'CASE',
		/* [1673] */
		"None=0",
		'CASE',
		/* [1674] */
		"CheckBox data",
		'DVDR',
		/* [1675] */
		"Value changed message",
		'DLNG',
		/* [1676] */
		"Initial value",
		'DLNG',
		/* [1677] */
		"Unchecked=0",
		'CASE',
		/* [1678] */
		"Checked=1",
		'CASE',
		/* [1679] */
		"Mixed=2",
		'CASE',
		/* [1680] */
		"Minimum value",
		'DLNG',
		/* [1681] */
		"Always=0",
		'CASE',
		/* [1682] */
		"Maximum value",
		'DLNG',
		/* [1683] */
		"Always=2",
		'CASE',
		/* [1684] */
		"Check box proc",
		'DWRD',
		/* [1685] */
		"Default=369",
		'CASE',
		/* [1686] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [1687] */
		"System font=0",
		'CASE',
		/* [1688] */
		"Title",
		'PSTR',
		/* [1689] */
		"",
		'KEYE',
		/* [1690] */
		"cbgb",
		'KEYB',
		/* [1691] */
		"Pane data",
		'DVDR',
		/* [1692] */
		"Pane ID",
		'DLNG',
		/* [1693] */
		"Width",
		'DWRD',
		/* [1694] */
		"Height",
		'DWRD',
		/* [1695] */
		"Visible?",
		'BFLG',
		/* [1696] */
		"Enabled?",
		'BFLG',
		/* [1697] */
		"Left side bound?",
		'BFLG',
		/* [1698] */
		"Top side bound?",
		'BFLG',
		/* [1699] */
		"Right side bound?",
		'BFLG',
		/* [1700] */
		"Bottom side bound?",
		'BFLG',
		/* [1701] */
		"Left in super image",
		'DLNG',
		/* [1702] */
		"Top in super image",
		'DLNG',
		/* [1703] */
		"User constant",
		'DLNG',
		/* [1704] */
		"Superview",
		'DLNG',
		/* [1705] */
		"Default=-1",
		'CASE',
		/* [1706] */
		"None=0",
		'CASE',
		/* [1707] */
		"View data",
		'DVDR',
		/* [1708] */
		"Image width",
		'DLNG',
		/* [1709] */
		"Image height",
		'DLNG',
		/* [1710] */
		"Horizontal scroll position",
		'DLNG',
		/* [1711] */
		"Vertical scroll position",
		'DLNG',
		/* [1712] */
		"Horizontal scroll unit",
		'DLNG',
		/* [1713] */
		"Vertical scroll unit",
		'DLNG',
		/* [1714] */
		"Reconcile overhang?",
		'WFLG',
		/* [1715] */
		"CheckBoxGroupBox data",
		'DVDR',
		/* [1716] */
		"Value changed message",
		'DLNG',
		/* [1717] */
		"Initial value",
		'DLNG',
		/* [1718] */
		"Unchecked=0",
		'CASE',
		/* [1719] */
		"Checked=1",
		'CASE',
		/* [1720] */
		"Minimum value",
		'DLNG',
		/* [1721] */
		"Always=0",
		'CASE',
		/* [1722] */
		"Maximum value",
		'DLNG',
		/* [1723] */
		"Always=1",
		'CASE',
		/* [1724] */
		"Group Kind",
		'DWRD',
		/* [1725] */
		"Primary=161",
		'CASE',
		/* [1726] */
		"Secondary=165",
		'CASE',
		/* [1727] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [1728] */
		"System font=0",
		'CASE',
		/* [1729] */
		"Title",
		'PSTR',
		/* [1730] */
		"",
		'KEYE',
		/* [1731] */
		"clck",
		'KEYB',
		/* [1732] */
		"Pane data",
		'DVDR',
		/* [1733] */
		"Pane ID",
		'DLNG',
		/* [1734] */
		"Width",
		'DWRD',
		/* [1735] */
		"Height",
		'DWRD',
		/* [1736] */
		"Visible?",
		'BFLG',
		/* [1737] */
		"Enabled?",
		'BFLG',
		/* [1738] */
		"Left side bound?",
		'BFLG',
		/* [1739] */
		"Top side bound?",
		'BFLG',
		/* [1740] */
		"Right side bound?",
		'BFLG',
		/* [1741] */
		"Bottom side bound?",
		'BFLG',
		/* [1742] */
		"Left in super image",
		'DLNG',
		/* [1743] */
		"Top in super image",
		'DLNG',
		/* [1744] */
		"User constant",
		'DLNG',
		/* [1745] */
		"Superview",
		'DLNG',
		/* [1746] */
		"Default=-1",
		'CASE',
		/* [1747] */
		"None=0",
		'CASE',
		/* [1748] */
		"Clock data",
		'DVDR',
		/* [1749] */
		"Value changed message",
		'DLNG',
		/* [1750] */
		"Unused=0",
		'CASE',
		/* [1751] */
		"Flags",
		'DLNG',
		/* [1752] */
		"No Flags=0",
		'CASE',
		/* [1753] */
		"Display Only=1",
		'CASE',
		/* [1754] */
		"Live Display Only=3",
		'CASE',
		/* [1755] */
		"Minimum value",
		'DLNG',
		/* [1756] */
		"Always=0",
		'CASE',
		/* [1757] */
		"Maximum value",
		'DLNG',
		/* [1758] */
		"Always=0",
		'CASE',
		/* [1759] */
		"Clock Kind",
		'DWRD',
		/* [1760] */
		"Time=240",
		'CASE',
		/* [1761] */
		"Time with Seconds=241",
		'CASE',
		/* [1762] */
		"Date=242",
		'CASE',
		/* [1763] */
		"Month and Year=243",
		'CASE',
		/* [1764] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [1765] */
		"System font=0",
		'CASE',
		/* [1766] */
		"Title",
		'PSTR',
		/* [1767] */
		"",
		'KEYE',
		/* [1768] */
		"cbbt",
		'KEYB',
		/* [1769] */
		"Pane data",
		'DVDR',
		/* [1770] */
		"Pane ID",
		'DLNG',
		/* [1771] */
		"Width",
		'DWRD',
		/* [1772] */
		"Height",
		'DWRD',
		/* [1773] */
		"Visible?",
		'BFLG',
		/* [1774] */
		"Enabled?",
		'BFLG',
		/* [1775] */
		"Left side bound?",
		'BFLG',
		/* [1776] */
		"Top side bound?",
		'BFLG',
		/* [1777] */
		"Right side bound?",
		'BFLG',
		/* [1778] */
		"Bottom side bound?",
		'BFLG',
		/* [1779] */
		"Left in super image",
		'DLNG',
		/* [1780] */
		"Top in super image",
		'DLNG',
		/* [1781] */
		"User constant",
		'DLNG',
		/* [1782] */
		"Superview",
		'DLNG',
		/* [1783] */
		"Default=-1",
		'CASE',
		/* [1784] */
		"None=0",
		'CASE',
		/* [1785] */
		"BevelButton data",
		'DVDR',
		/* [1786] */
		"Value changed message",
		'DLNG',
		/* [1787] */
		"Filler",
		'FWRD',
		/* [1788] */
		"'MENU' id",
		'RSID',
		/* [1789] */
		"Filler",
		'FWRD',
		/* [1790] */
		"Offset Contents?",
		'BBIT',
		/* [1791] */
		"MultiValue Menu?",
		'BBIT',
		/* [1792] */
		"Behavior",
		'BB06',
		/* [1793] */
		"PushButton=0",
		'CASE',
		/* [1794] */
		"Toggles=1",
		'CASE',
		/* [1795] */
		"Sticky=2",
		'CASE',
		/* [1796] */
		"Content Type",
		'DBYT',
		/* [1797] */
		"Text Only=0",
		'CASE',
		/* [1798] */
		"Icon Suite Resource=1",
		'CASE',
		/* [1799] */
		"cicn Resource=2",
		'CASE',
		/* [1800] */
		"PICT Resource=3",
		'CASE',
		/* [1801] */
		"Icon Suite Handle=129",
		'CASE',
		/* [1802] */
		"cicn Handle=130",
		'CASE',
		/* [1803] */
		"PICT Handle=131",
		'CASE',
		/* [1804] */
		"Icon Reference=132",
		'CASE',
		/* [1805] */
		"Filler",
		'FWRD',
		/* [1806] */
		"Content Resource ID",
		'DWRD',
		/* [1807] */
		"Filler",
		'FBYT',
		/* [1808] */
		"Proc ID",
		'BB04',
		/* [1809] */
		"BevelButton=2",
		'CASE',
		/* [1810] */
		"Filler bit (ignore)",
		'BBIT',
		/* [1811] */
		"Arrow Direction (Down=0, Right=1)",
		'BBIT',
		/* [1812] */
		"Bevel Size",
		'BB02',
		/* [1813] */
		"Small=0",
		'CASE',
		/* [1814] */
		"Normal=1",
		'CASE',
		/* [1815] */
		"Large=2",
		'CASE',
		/* [1816] */
		"Text Traits ('Txtr') ID",
		'RSID',
		/* [1817] */
		"Title",
		'PSTR',
		/* [1818] */
		"Initial Value",
		'DWRD',
		/* [1819] */
		"Title Placement",
		'DWRD',
		/* [1820] */
		"System Direction=-1",
		'CASE',
		/* [1821] */
		"Normally=0",
		'CASE',
		/* [1822] */
		"Right of Graphic=1",
		'CASE',
		/* [1823] */
		"Left of Graphic=2",
		'CASE',
		/* [1824] */
		"Below Graphic=3",
		'CASE',
		/* [1825] */
		"Above Graphic=4",
		'CASE',
		/* [1826] */
		"Title Alignment",
		'DWRD',
		/* [1827] */
		"Flush Default=0",
		'CASE',
		/* [1828] */
		"Center=1",
		'CASE',
		/* [1829] */
		"Flush Right=-1",
		'CASE',
		/* [1830] */
		"Flush Left=-2",
		'CASE',
		/* [1831] */
		"Title Pixel Offset",
		'DWRD',
		/* [1832] */
		"Graphic Alignment",
		'DWRD',
		/* [1833] */
		"System Direction=-1",
		'CASE',
		/* [1834] */
		"Center=0",
		'CASE',
		/* [1835] */
		"Left=1",
		'CASE',
		/* [1836] */
		"Right=2",
		'CASE',
		/* [1837] */
		"Top=3",
		'CASE',
		/* [1838] */
		"Bottom=4",
		'CASE',
		/* [1839] */
		"Top Left=5",
		'CASE',
		/* [1840] */
		"Bottom Left=6",
		'CASE',
		/* [1841] */
		"Top Right=7",
		'CASE',
		/* [1842] */
		"Bottom Right=8",
		'CASE',
		/* [1843] */
		"Graphic Offset",
		'PNT ',
		/* [1844] */
		"Center Popup Arrow?",
		'BFLG',
		/* [1845] */
		"Command",
		'DLNG',
		/* [1846] */
		"",
		'KEYE',
		/* [1847] */
		"dtri",
		'KEYB',
		/* [1848] */
		"Pane data",
		'DVDR',
		/* [1849] */
		"Pane ID",
		'DLNG',
		/* [1850] */
		"Width",
		'DWRD',
		/* [1851] */
		"Height",
		'DWRD',
		/* [1852] */
		"Visible?",
		'BFLG',
		/* [1853] */
		"Enabled?",
		'BFLG',
		/* [1854] */
		"Left side bound?",
		'BFLG',
		/* [1855] */
		"Top side bound?",
		'BFLG',
		/* [1856] */
		"Right side bound?",
		'BFLG',
		/* [1857] */
		"Bottom side bound?",
		'BFLG',
		/* [1858] */
		"Left in super image",
		'DLNG',
		/* [1859] */
		"Top in super image",
		'DLNG',
		/* [1860] */
		"User constant",
		'DLNG',
		/* [1861] */
		"Superview",
		'DLNG',
		/* [1862] */
		"Default=-1",
		'CASE',
		/* [1863] */
		"None=0",
		'CASE',
		/* [1864] */
		"Disclosure Triangle data",
		'DVDR',
		/* [1865] */
		"Value changed message",
		'DLNG',
		/* [1866] */
		"Initial value",
		'DLNG',
		/* [1867] */
		"Up=0",
		'CASE',
		/* [1868] */
		"Down=1",
		'CASE',
		/* [1869] */
		"Minimum value",
		'DLNG',
		/* [1870] */
		"Always=0",
		'CASE',
		/* [1871] */
		"Maximum value",
		'DLNG',
		/* [1872] */
		"Always=1",
		'CASE',
		/* [1873] */
		"Direction",
		'DWRD',
		/* [1874] */
		"Face Right=64",
		'CASE',
		/* [1875] */
		"Face Left=65",
		'CASE',
		/* [1876] */
		"Text traits ID",
		'RSID',
		/* [1877] */
		"Unused=0",
		'CASE',
		/* [1878] */
		"Title",
		'PSTR',
		/* [1879] */
		"",
		'KEYE',
		/* [1880] */
		"etxt",
		'KEYB',
		/* [1881] */
		"Pane data",
		'DVDR',
		/* [1882] */
		"Pane ID",
		'DLNG',
		/* [1883] */
		"Width",
		'DWRD',
		/* [1884] */
		"Height",
		'DWRD',
		/* [1885] */
		"Visible?",
		'BFLG',
		/* [1886] */
		"Enabled?",
		'BFLG',
		/* [1887] */
		"Left side bound?",
		'BFLG',
		/* [1888] */
		"Top side bound?",
		'BFLG',
		/* [1889] */
		"Right side bound?",
		'BFLG',
		/* [1890] */
		"Bottom side bound?",
		'BFLG',
		/* [1891] */
		"Left in super image",
		'DLNG',
		/* [1892] */
		"Top in super image",
		'DLNG',
		/* [1893] */
		"User constant",
		'DLNG',
		/* [1894] */
		"Superview",
		'DLNG',
		/* [1895] */
		"Default=-1",
		'CASE',
		/* [1896] */
		"None=0",
		'CASE',
		/* [1897] */
		"EditText data",
		'DVDR',
		/* [1898] */
		"Value changed message",
		'DLNG',
		/* [1899] */
		"Unused=0",
		'CASE',
		/* [1900] */
		"Initial value",
		'DLNG',
		/* [1901] */
		"Unused=0",
		'CASE',
		/* [1902] */
		"Minimum value",
		'DLNG',
		/* [1903] */
		"Unused=0",
		'CASE',
		/* [1904] */
		"Maximum value",
		'DLNG',
		/* [1905] */
		"Unused=0",
		'CASE',
		/* [1906] */
		"Kind of EditText",
		'DWRD',
		/* [1907] */
		"Normal=272",
		'CASE',
		/* [1908] */
		"Password=274",
		'CASE',
		/* [1909] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [1910] */
		"System font=0",
		'CASE',
		/* [1911] */
		"Initial Text",
		'PSTR',
		/* [1912] */
		"Maximum Characters",
		'DWRD',
		/* [1913] */
		"Has Box",
		'BBIT',
		/* [1914] */
		"Word Wrap",
		'BBIT',
		/* [1915] */
		"Auto Scroll",
		'BBIT',
		/* [1916] */
		"Text Buffering",
		'BBIT',
		/* [1917] */
		"Outline Hilite",
		'BBIT',
		/* [1918] */
		"Inline Input",
		'BBIT',
		/* [1919] */
		"Text Services",
		'BBIT',
		/* [1920] */
		"Filler bit (ignore)",
		'BBIT',
		/* [1921] */
		"Keystroke Filter",
		'DBYT',
		/* [1922] */
		"None=0",
		'CASE',
		/* [1923] */
		"Integer=1",
		'CASE',
		/* [1924] */
		"AlphaNumeric=2",
		'CASE',
		/* [1925] */
		"Printing Character=3",
		'CASE',
		/* [1926] */
		"Negative Integer=4",
		'CASE',
		/* [1927] */
		"Printing Char and CR=5",
		'CASE',
		/* [1928] */
		"",
		'KEYE',
		/* [1929] */
		"ictl",
		'KEYB',
		/* [1930] */
		"Pane data",
		'DVDR',
		/* [1931] */
		"Pane ID",
		'DLNG',
		/* [1932] */
		"Width",
		'DWRD',
		/* [1933] */
		"Height",
		'DWRD',
		/* [1934] */
		"Visible?",
		'BFLG',
		/* [1935] */
		"Enabled?",
		'BFLG',
		/* [1936] */
		"Left side bound?",
		'BFLG',
		/* [1937] */
		"Top side bound?",
		'BFLG',
		/* [1938] */
		"Right side bound?",
		'BFLG',
		/* [1939] */
		"Bottom side bound?",
		'BFLG',
		/* [1940] */
		"Left in super image",
		'DLNG',
		/* [1941] */
		"Top in super image",
		'DLNG',
		/* [1942] */
		"User constant",
		'DLNG',
		/* [1943] */
		"Superview",
		'DLNG',
		/* [1944] */
		"Default=-1",
		'CASE',
		/* [1945] */
		"None=0",
		'CASE',
		/* [1946] */
		"Icon Control data",
		'DVDR',
		/* [1947] */
		"Value changed message",
		'DLNG',
		/* [1948] */
		"Filler",
		'FWRD',
		/* [1949] */
		"Icon Resource ID",
		'DWRD',
		/* [1950] */
		"Minimum value",
		'DLNG',
		/* [1951] */
		"Always=0",
		'CASE',
		/* [1952] */
		"Maximum value",
		'DLNG',
		/* [1953] */
		"Always=0",
		'CASE',
		/* [1954] */
		"Control Kind",
		'WB14',
		/* [1955] */
		"Icon Control=80",
		'CASE',
		/* [1956] */
		"Icon Type",
		'WBIT',
		/* [1957] */
		"Color Icon (cicn)=0",
		'CASE',
		/* [1958] */
		"Icon Suite (iclx)=1",
		'CASE',
		/* [1959] */
		"Has Tracking",
		'WBIT',
		/* [1960] */
		"Text traits ID",
		'DWRD',
		/* [1961] */
		"Unused=0",
		'CASE',
		/* [1962] */
		"Title",
		'PSTR',
		/* [1963] */
		"Icon Alignment",
		'DWRD',
		/* [1964] */
		"None=0",
		'CASE',
		/* [1965] */
		"Center=5",
		'CASE',
		/* [1966] */
		"Center Top=6",
		'CASE',
		/* [1967] */
		"Center Bottom=7",
		'CASE',
		/* [1968] */
		"Center Left=9",
		'CASE',
		/* [1969] */
		"Top Left=10",
		'CASE',
		/* [1970] */
		"Bottom Left=11",
		'CASE',
		/* [1971] */
		"Center Right=13",
		'CASE',
		/* [1972] */
		"Top Right=14",
		'CASE',
		/* [1973] */
		"Bottom Right=15",
		'CASE',
		/* [1974] */
		"",
		'KEYE',
		/* [1975] */
		"iwel",
		'KEYB',
		/* [1976] */
		"Pane data",
		'DVDR',
		/* [1977] */
		"Pane ID",
		'DLNG',
		/* [1978] */
		"Width",
		'DWRD',
		/* [1979] */
		"Height",
		'DWRD',
		/* [1980] */
		"Visible?",
		'BFLG',
		/* [1981] */
		"Enabled?",
		'BFLG',
		/* [1982] */
		"Left side bound?",
		'BFLG',
		/* [1983] */
		"Top side bound?",
		'BFLG',
		/* [1984] */
		"Right side bound?",
		'BFLG',
		/* [1985] */
		"Bottom side bound?",
		'BFLG',
		/* [1986] */
		"Left in super image",
		'DLNG',
		/* [1987] */
		"Top in super image",
		'DLNG',
		/* [1988] */
		"User constant",
		'DLNG',
		/* [1989] */
		"Superview",
		'DLNG',
		/* [1990] */
		"Default=-1",
		'CASE',
		/* [1991] */
		"None=0",
		'CASE',
		/* [1992] */
		"View data",
		'DVDR',
		/* [1993] */
		"Image width",
		'DLNG',
		/* [1994] */
		"Image height",
		'DLNG',
		/* [1995] */
		"Horizontal scroll position",
		'DLNG',
		/* [1996] */
		"Vertical scroll position",
		'DLNG',
		/* [1997] */
		"Horizontal scroll unit",
		'DLNG',
		/* [1998] */
		"Vertical scroll unit",
		'DLNG',
		/* [1999] */
		"Reconcile overhang?",
		'WFLG',
		/* [2000] */
		"ImageWell data",
		'DVDR',
		/* [2001] */
		"Value changed message",
		'DLNG',
		/* [2002] */
		"Filler",
		'FWRD',
		/* [2003] */
		"Content Resource ID",
		'DWRD',
		/* [2004] */
		"Filler",
		'FWRD',
		/* [2005] */
		"Content Type",
		'DWRD',
		/* [2006] */
		"Icon Suite Resource=1",
		'CASE',
		/* [2007] */
		"cicn Resource=2",
		'CASE',
		/* [2008] */
		"PICT Resource=3",
		'CASE',
		/* [2009] */
		"Icon Suite Handle=129",
		'CASE',
		/* [2010] */
		"cicn Handle=130",
		'CASE',
		/* [2011] */
		"PICT Handle=131",
		'CASE',
		/* [2012] */
		"Icon Reference=132",
		'CASE',
		/* [2013] */
		"Maximum value",
		'DLNG',
		/* [2014] */
		"Unused=0",
		'CASE',
		/* [2015] */
		"Control Kind",
		'DWRD',
		/* [2016] */
		"Image Well=176",
		'CASE',
		/* [2017] */
		"Text traits ID",
		'RSID',
		/* [2018] */
		"Unused=0",
		'CASE',
		/* [2019] */
		"Title",
		'PSTR',
		/* [2020] */
		"",
		'KEYE',
		/* [2021] */
		"larr",
		'KEYB',
		/* [2022] */
		"Pane data",
		'DVDR',
		/* [2023] */
		"Pane ID",
		'DLNG',
		/* [2024] */
		"Width",
		'DWRD',
		/* [2025] */
		"Height",
		'DWRD',
		/* [2026] */
		"Visible?",
		'BFLG',
		/* [2027] */
		"Enabled?",
		'BFLG',
		/* [2028] */
		"Left side bound?",
		'BFLG',
		/* [2029] */
		"Top side bound?",
		'BFLG',
		/* [2030] */
		"Right side bound?",
		'BFLG',
		/* [2031] */
		"Bottom side bound?",
		'BFLG',
		/* [2032] */
		"Left in super image",
		'DLNG',
		/* [2033] */
		"Top in super image",
		'DLNG',
		/* [2034] */
		"User constant",
		'DLNG',
		/* [2035] */
		"Superview",
		'DLNG',
		/* [2036] */
		"Default=-1",
		'CASE',
		/* [2037] */
		"None=0",
		'CASE',
		/* [2038] */
		"Little Arrows data",
		'DVDR',
		/* [2039] */
		"Value changed message",
		'DLNG',
		/* [2040] */
		"Initial value",
		'DLNG',
		/* [2041] */
		"Minimum value",
		'DLNG',
		/* [2042] */
		"Maximum value",
		'DLNG',
		/* [2043] */
		"Control Kind",
		'DWRD',
		/* [2044] */
		"Little Arrows=96",
		'CASE',
		/* [2045] */
		"Text traits ID",
		'DWRD',
		/* [2046] */
		"Unused=0",
		'CASE',
		/* [2047] */
		"Title",
		'PSTR',
		/* [2048] */
		"",
		'KEYE',
		/* [2049] */
		"picd",
		'KEYB',
		/* [2050] */
		"Pane data",
		'DVDR',
		/* [2051] */
		"Pane ID",
		'DLNG',
		/* [2052] */
		"Width",
		'DWRD',
		/* [2053] */
		"Height",
		'DWRD',
		/* [2054] */
		"Visible?",
		'BFLG',
		/* [2055] */
		"Enabled?",
		'BFLG',
		/* [2056] */
		"Left side bound?",
		'BFLG',
		/* [2057] */
		"Top side bound?",
		'BFLG',
		/* [2058] */
		"Right side bound?",
		'BFLG',
		/* [2059] */
		"Bottom side bound?",
		'BFLG',
		/* [2060] */
		"Left in super image",
		'DLNG',
		/* [2061] */
		"Top in super image",
		'DLNG',
		/* [2062] */
		"User constant",
		'DLNG',
		/* [2063] */
		"Superview",
		'DLNG',
		/* [2064] */
		"Default=-1",
		'CASE',
		/* [2065] */
		"None=0",
		'CASE',
		/* [2066] */
		"View data",
		'DVDR',
		/* [2067] */
		"Image width",
		'DLNG',
		/* [2068] */
		"Image height",
		'DLNG',
		/* [2069] */
		"Horizontal scroll position",
		'DLNG',
		/* [2070] */
		"Vertical scroll position",
		'DLNG',
		/* [2071] */
		"Horizontal scroll unit",
		'DLNG',
		/* [2072] */
		"Vertical scroll unit",
		'DLNG',
		/* [2073] */
		"Reconcile overhang?",
		'WFLG',
		/* [2074] */
		"Picture Control data",
		'DVDR',
		/* [2075] */
		"Value changed message",
		'DLNG',
		/* [2076] */
		"Filler",
		'FWRD',
		/* [2077] */
		"'PICT' Resource ID",
		'RSID',
		/* [2078] */
		"Minimum value",
		'DLNG',
		/* [2079] */
		"Unused=0",
		'CASE',
		/* [2080] */
		"Maximum value",
		'DLNG',
		/* [2081] */
		"Unused=0",
		'CASE',
		/* [2082] */
		"Control Kind",
		'DWRD',
		/* [2083] */
		"Has Tracking=304",
		'CASE',
		/* [2084] */
		"No Tracking=305",
		'CASE',
		/* [2085] */
		"Text traits ID",
		'DWRD',
		/* [2086] */
		"Unused=0",
		'CASE',
		/* [2087] */
		"Title",
		'PSTR',
		/* [2088] */
		"",
		'KEYE',
		/* [2089] */
		"plcd",
		'KEYB',
		/* [2090] */
		"Pane data",
		'DVDR',
		/* [2091] */
		"Pane ID",
		'DLNG',
		/* [2092] */
		"Width",
		'DWRD',
		/* [2093] */
		"Height",
		'DWRD',
		/* [2094] */
		"Visible?",
		'BFLG',
		/* [2095] */
		"Enabled?",
		'BFLG',
		/* [2096] */
		"Left side bound?",
		'BFLG',
		/* [2097] */
		"Top side bound?",
		'BFLG',
		/* [2098] */
		"Right side bound?",
		'BFLG',
		/* [2099] */
		"Bottom side bound?",
		'BFLG',
		/* [2100] */
		"Left in super image",
		'DLNG',
		/* [2101] */
		"Top in super image",
		'DLNG',
		/* [2102] */
		"User constant",
		'DLNG',
		/* [2103] */
		"Superview",
		'DLNG',
		/* [2104] */
		"Default=-1",
		'CASE',
		/* [2105] */
		"None=0",
		'CASE',
		/* [2106] */
		"View data",
		'DVDR',
		/* [2107] */
		"Image width",
		'DLNG',
		/* [2108] */
		"Image height",
		'DLNG',
		/* [2109] */
		"Horizontal scroll position",
		'DLNG',
		/* [2110] */
		"Vertical scroll position",
		'DLNG',
		/* [2111] */
		"Horizontal scroll unit",
		'DLNG',
		/* [2112] */
		"Vertical scroll unit",
		'DLNG',
		/* [2113] */
		"Reconcile overhang?",
		'WFLG',
		/* [2114] */
		"Placard data",
		'DVDR',
		/* [2115] */
		"Value changed message",
		'DLNG',
		/* [2116] */
		"Unused=0",
		'CASE',
		/* [2117] */
		"Value",
		'DLNG',
		/* [2118] */
		"Unused=0",
		'CASE',
		/* [2119] */
		"Minimum value",
		'DLNG',
		/* [2120] */
		"Unused=0",
		'CASE',
		/* [2121] */
		"Maximum value",
		'DLNG',
		/* [2122] */
		"Unused=0",
		'CASE',
		/* [2123] */
		"Control Kind",
		'DWRD',
		/* [2124] */
		"Placard=224",
		'CASE',
		/* [2125] */
		"Text traits ID",
		'DWRD',
		/* [2126] */
		"Unused=0",
		'CASE',
		/* [2127] */
		"Title",
		'PSTR',
		/* [2128] */
		"",
		'KEYE',
		/* [2129] */
		"popb",
		'KEYB',
		/* [2130] */
		"Pane data",
		'DVDR',
		/* [2131] */
		"Pane ID",
		'DLNG',
		/* [2132] */
		"Width",
		'DWRD',
		/* [2133] */
		"Height",
		'DWRD',
		/* [2134] */
		"Visible?",
		'BFLG',
		/* [2135] */
		"Enabled?",
		'BFLG',
		/* [2136] */
		"Left side bound?",
		'BFLG',
		/* [2137] */
		"Top side bound?",
		'BFLG',
		/* [2138] */
		"Right side bound?",
		'BFLG',
		/* [2139] */
		"Bottom side bound?",
		'BFLG',
		/* [2140] */
		"Left in super image",
		'DLNG',
		/* [2141] */
		"Top in super image",
		'DLNG',
		/* [2142] */
		"User constant",
		'DLNG',
		/* [2143] */
		"Superview",
		'DLNG',
		/* [2144] */
		"Default=-1",
		'CASE',
		/* [2145] */
		"None=0",
		'CASE',
		/* [2146] */
		"Popup Button data",
		'DVDR',
		/* [2147] */
		"Value changed message",
		'DLNG',
		/* [2148] */
		"Filler",
		'FWRD',
		/* [2149] */
		"Title Style Options (Unused=0)",
		'BBIT',
		/* [2150] */
		"Extended",
		'BBIT',
		/* [2151] */
		"Condensed",
		'BBIT',
		/* [2152] */
		"Shadow",
		'BBIT',
		/* [2153] */
		"Outline",
		'BBIT',
		/* [2154] */
		"Underline",
		'BBIT',
		/* [2155] */
		"Italic",
		'BBIT',
		/* [2156] */
		"Bold",
		'BBIT',
		/* [2157] */
		"Title Alignment",
		'DBYT',
		/* [2158] */
		"Left=0",
		'CASE',
		/* [2159] */
		"Center=1",
		'CASE',
		/* [2160] */
		"Right=255",
		'CASE',
		/* [2161] */
		"Filler",
		'FWRD',
		/* [2162] */
		"'MENU' Resource ID",
		'RSID',
		/* [2163] */
		"No Resource=-12345",
		'CASE',
		/* [2164] */
		"Filler",
		'FWRD',
		/* [2165] */
		"Title Width",
		'DWRD',
		/* [2166] */
		"Calculate Width=-1",
		'CASE',
		/* [2167] */
		"Control Kind",
		'WB13',
		/* [2168] */
		"Popup Button=50",
		'CASE',
		/* [2169] */
		"Use Res Menu",
		'WBIT',
		/* [2170] */
		"Filler",
		'WBIT',
		/* [2171] */
		"Unused=0",
		'CASE',
		/* [2172] */
		"Fixed Width",
		'WBIT',
		/* [2173] */
		"Text traits ('Txtr') ID",
		'DWRD',
		/* [2174] */
		"Use System Font=0",
		'CASE',
		/* [2175] */
		"Title",
		'PSTR',
		/* [2176] */
		"ResType for Menu Items",
		'TNAM',
		/* [2177] */
		"Initial Menu Choice",
		'DWRD',
		/* [2178] */
		"",
		'KEYE',
		/* [2179] */
		"pgbx",
		'KEYB',
		/* [2180] */
		"Pane data",
		'DVDR',
		/* [2181] */
		"Pane ID",
		'DLNG',
		/* [2182] */
		"Width",
		'DWRD',
		/* [2183] */
		"Height",
		'DWRD',
		/* [2184] */
		"Visible?",
		'BFLG',
		/* [2185] */
		"Enabled?",
		'BFLG',
		/* [2186] */
		"Left side bound?",
		'BFLG',
		/* [2187] */
		"Top side bound?",
		'BFLG',
		/* [2188] */
		"Right side bound?",
		'BFLG',
		/* [2189] */
		"Bottom side bound?",
		'BFLG',
		/* [2190] */
		"Left in super image",
		'DLNG',
		/* [2191] */
		"Top in super image",
		'DLNG',
		/* [2192] */
		"User constant",
		'DLNG',
		/* [2193] */
		"Superview",
		'DLNG',
		/* [2194] */
		"Default=-1",
		'CASE',
		/* [2195] */
		"None=0",
		'CASE',
		/* [2196] */
		"View data",
		'DVDR',
		/* [2197] */
		"Image width",
		'DLNG',
		/* [2198] */
		"Image height",
		'DLNG',
		/* [2199] */
		"Horizontal scroll position",
		'DLNG',
		/* [2200] */
		"Vertical scroll position",
		'DLNG',
		/* [2201] */
		"Horizontal scroll unit",
		'DLNG',
		/* [2202] */
		"Vertical scroll unit",
		'DLNG',
		/* [2203] */
		"Reconcile overhang?",
		'WFLG',
		/* [2204] */
		"PopupGroupBox data",
		'DVDR',
		/* [2205] */
		"Value changed message",
		'DLNG',
		/* [2206] */
		"Filler",
		'FWRD',
		/* [2207] */
		"Title Style Options (Unused=0)",
		'BBIT',
		/* [2208] */
		"Extended",
		'BBIT',
		/* [2209] */
		"Condensed",
		'BBIT',
		/* [2210] */
		"Shadow",
		'BBIT',
		/* [2211] */
		"Outline",
		'BBIT',
		/* [2212] */
		"Underline",
		'BBIT',
		/* [2213] */
		"Italic",
		'BBIT',
		/* [2214] */
		"Bold",
		'BBIT',
		/* [2215] */
		"Title Alignment",
		'DBYT',
		/* [2216] */
		"Left=0",
		'CASE',
		/* [2217] */
		"Center=1",
		'CASE',
		/* [2218] */
		"Right=255",
		'CASE',
		/* [2219] */
		"Filler",
		'FWRD',
		/* [2220] */
		"'MENU' Resource ID",
		'RSID',
		/* [2221] */
		"No Resource=-12345",
		'CASE',
		/* [2222] */
		"Filler",
		'FWRD',
		/* [2223] */
		"Title Width",
		'DWRD',
		/* [2224] */
		"Calculate Width=-1",
		'CASE',
		/* [2225] */
		"Group Kind",
		'DWRD',
		/* [2226] */
		"Primary=162",
		'CASE',
		/* [2227] */
		"Text traits ('Txtr') ID",
		'DWRD',
		/* [2228] */
		"Use System Font=0",
		'CASE',
		/* [2229] */
		"Title",
		'PSTR',
		/* [2230] */
		"Initial Menu Choice",
		'DWRD',
		/* [2231] */
		"",
		'KEYE',
		/* [2232] */
		"pbar",
		'KEYB',
		/* [2233] */
		"Pane data",
		'DVDR',
		/* [2234] */
		"Pane ID",
		'DLNG',
		/* [2235] */
		"Width",
		'DWRD',
		/* [2236] */
		"Height",
		'DWRD',
		/* [2237] */
		"Visible?",
		'BFLG',
		/* [2238] */
		"Enabled?",
		'BFLG',
		/* [2239] */
		"Left side bound?",
		'BFLG',
		/* [2240] */
		"Top side bound?",
		'BFLG',
		/* [2241] */
		"Right side bound?",
		'BFLG',
		/* [2242] */
		"Bottom side bound?",
		'BFLG',
		/* [2243] */
		"Left in super image",
		'DLNG',
		/* [2244] */
		"Top in super image",
		'DLNG',
		/* [2245] */
		"User constant",
		'DLNG',
		/* [2246] */
		"Superview",
		'DLNG',
		/* [2247] */
		"Default=-1",
		'CASE',
		/* [2248] */
		"None=0",
		'CASE',
		/* [2249] */
		"Progress Bar data",
		'DVDR',
		/* [2250] */
		"Value changed message",
		'DLNG',
		/* [2251] */
		"Initial value",
		'DLNG',
		/* [2252] */
		"Minimum value",
		'DLNG',
		/* [2253] */
		"Maximum value",
		'DLNG',
		/* [2254] */
		"Control Kind",
		'DWRD',
		/* [2255] */
		"ProgressBar=80",
		'CASE',
		/* [2256] */
		"Text traits ID",
		'RSID',
		/* [2257] */
		"Unused=0",
		'CASE',
		/* [2258] */
		"Title",
		'PSTR',
		/* [2259] */
		"Bar Kind (Determinate=0,Barber Pole=1)",
		'BFLG',
		/* [2260] */
		"",
		'KEYE',
		/* [2261] */
		"push",
		'KEYB',
		/* [2262] */
		"Pane data",
		'DVDR',
		/* [2263] */
		"Pane ID",
		'DLNG',
		/* [2264] */
		"Width",
		'DWRD',
		/* [2265] */
		"Height",
		'DWRD',
		/* [2266] */
		"Visible?",
		'BFLG',
		/* [2267] */
		"Enabled?",
		'BFLG',
		/* [2268] */
		"Left side bound?",
		'BFLG',
		/* [2269] */
		"Top side bound?",
		'BFLG',
		/* [2270] */
		"Right side bound?",
		'BFLG',
		/* [2271] */
		"Bottom side bound?",
		'BFLG',
		/* [2272] */
		"Left in super image",
		'DLNG',
		/* [2273] */
		"Top in super image",
		'DLNG',
		/* [2274] */
		"User constant",
		'DLNG',
		/* [2275] */
		"Superview",
		'DLNG',
		/* [2276] */
		"Default=-1",
		'CASE',
		/* [2277] */
		"None=0",
		'CASE',
		/* [2278] */
		"Push Button data",
		'DVDR',
		/* [2279] */
		"Value changed message",
		'DLNG',
		/* [2280] */
		"Initial value",
		'DLNG',
		/* [2281] */
		"Always=0",
		'CASE',
		/* [2282] */
		"Minimum value",
		'DLNG',
		/* [2283] */
		"Always=0",
		'CASE',
		/* [2284] */
		"Maximum value",
		'DLNG',
		/* [2285] */
		"Always=0",
		'CASE',
		/* [2286] */
		"Layout",
		'DWRD',
		/* [2287] */
		"Text Only=368",
		'CASE',
		/* [2288] */
		"Icon on Left=374",
		'CASE',
		/* [2289] */
		"Icon on Right=375",
		'CASE',
		/* [2290] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [2291] */
		"Use System Font=0",
		'CASE',
		/* [2292] */
		"Title",
		'PSTR',
		/* [2293] */
		"Is Default Button",
		'BFLG',
		/* [2294] */
		"",
		'KEYE',
		/* [2295] */
		"rdbt",
		'KEYB',
		/* [2296] */
		"Pane data",
		'DVDR',
		/* [2297] */
		"Pane ID",
		'DLNG',
		/* [2298] */
		"Width",
		'DWRD',
		/* [2299] */
		"Height",
		'DWRD',
		/* [2300] */
		"Visible?",
		'BFLG',
		/* [2301] */
		"Enabled?",
		'BFLG',
		/* [2302] */
		"Left side bound?",
		'BFLG',
		/* [2303] */
		"Top side bound?",
		'BFLG',
		/* [2304] */
		"Right side bound?",
		'BFLG',
		/* [2305] */
		"Bottom side bound?",
		'BFLG',
		/* [2306] */
		"Left in super image",
		'DLNG',
		/* [2307] */
		"Top in super image",
		'DLNG',
		/* [2308] */
		"User constant",
		'DLNG',
		/* [2309] */
		"Superview",
		'DLNG',
		/* [2310] */
		"Default=-1",
		'CASE',
		/* [2311] */
		"None=0",
		'CASE',
		/* [2312] */
		"Radio Button data",
		'DVDR',
		/* [2313] */
		"Value changed message",
		'DLNG',
		/* [2314] */
		"Initial value",
		'DLNG',
		/* [2315] */
		"Off=0",
		'CASE',
		/* [2316] */
		"On=1",
		'CASE',
		/* [2317] */
		"Mixed=2",
		'CASE',
		/* [2318] */
		"Minimum value",
		'DLNG',
		/* [2319] */
		"Always=0",
		'CASE',
		/* [2320] */
		"Maximum value",
		'DLNG',
		/* [2321] */
		"Always=2",
		'CASE',
		/* [2322] */
		"Control Kind",
		'DWRD',
		/* [2323] */
		"Radio Button=370",
		'CASE',
		/* [2324] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [2325] */
		"Use System Font=0",
		'CASE',
		/* [2326] */
		"Title",
		'PSTR',
		/* [2327] */
		"",
		'KEYE',
		/* [2328] */
		"sbar",
		'KEYB',
		/* [2329] */
		"Pane data",
		'DVDR',
		/* [2330] */
		"Pane ID",
		'DLNG',
		/* [2331] */
		"Width",
		'DWRD',
		/* [2332] */
		"Height",
		'DWRD',
		/* [2333] */
		"Visible?",
		'BFLG',
		/* [2334] */
		"Enabled?",
		'BFLG',
		/* [2335] */
		"Left side bound?",
		'BFLG',
		/* [2336] */
		"Top side bound?",
		'BFLG',
		/* [2337] */
		"Right side bound?",
		'BFLG',
		/* [2338] */
		"Bottom side bound?",
		'BFLG',
		/* [2339] */
		"Left in super image",
		'DLNG',
		/* [2340] */
		"Top in super image",
		'DLNG',
		/* [2341] */
		"User constant",
		'DLNG',
		/* [2342] */
		"Superview",
		'DLNG',
		/* [2343] */
		"Default=-1",
		'CASE',
		/* [2344] */
		"None=0",
		'CASE',
		/* [2345] */
		"ScrollBar data",
		'DVDR',
		/* [2346] */
		"Value changed message",
		'DLNG',
		/* [2347] */
		"Initial value",
		'DLNG',
		/* [2348] */
		"Minimum value",
		'DLNG',
		/* [2349] */
		"Maximum value",
		'DLNG',
		/* [2350] */
		"Control Kind",
		'DWRD',
		/* [2351] */
		"Normal=384",
		'CASE',
		/* [2352] */
		"Live Scrolling=386",
		'CASE',
		/* [2353] */
		"Text traits ID",
		'RSID',
		/* [2354] */
		"Unused=0",
		'CASE',
		/* [2355] */
		"Title",
		'PSTR',
		/* [2356] */
		"",
		'KEYE',
		/* [2357] */
		"sepl",
		'KEYB',
		/* [2358] */
		"Pane data",
		'DVDR',
		/* [2359] */
		"Pane ID",
		'DLNG',
		/* [2360] */
		"Width",
		'DWRD',
		/* [2361] */
		"Height",
		'DWRD',
		/* [2362] */
		"Visible?",
		'BFLG',
		/* [2363] */
		"Enabled?",
		'BFLG',
		/* [2364] */
		"Left side bound?",
		'BFLG',
		/* [2365] */
		"Top side bound?",
		'BFLG',
		/* [2366] */
		"Right side bound?",
		'BFLG',
		/* [2367] */
		"Bottom side bound?",
		'BFLG',
		/* [2368] */
		"Left in super image",
		'DLNG',
		/* [2369] */
		"Top in super image",
		'DLNG',
		/* [2370] */
		"User constant",
		'DLNG',
		/* [2371] */
		"Superview",
		'DLNG',
		/* [2372] */
		"Default=-1",
		'CASE',
		/* [2373] */
		"None=0",
		'CASE',
		/* [2374] */
		"Separator Line data",
		'DVDR',
		/* [2375] */
		"Value changed message",
		'DLNG',
		/* [2376] */
		"Unused=0",
		'CASE',
		/* [2377] */
		"Initial value",
		'DLNG',
		/* [2378] */
		"Unused=0",
		'CASE',
		/* [2379] */
		"Minimum value",
		'DLNG',
		/* [2380] */
		"Unused=0",
		'CASE',
		/* [2381] */
		"Maximum value",
		'DLNG',
		/* [2382] */
		"Unused=0",
		'CASE',
		/* [2383] */
		"Control Kind",
		'DWRD',
		/* [2384] */
		"Separator Line=144",
		'CASE',
		/* [2385] */
		"Text traits ID",
		'RSID',
		/* [2386] */
		"Unused=0",
		'CASE',
		/* [2387] */
		"Title",
		'PSTR',
		/* [2388] */
		"",
		'KEYE',
		/* [2389] */
		"slid",
		'KEYB',
		/* [2390] */
		"Pane data",
		'DVDR',
		/* [2391] */
		"Pane ID",
		'DLNG',
		/* [2392] */
		"Width",
		'DWRD',
		/* [2393] */
		"Height",
		'DWRD',
		/* [2394] */
		"Visible?",
		'BFLG',
		/* [2395] */
		"Enabled?",
		'BFLG',
		/* [2396] */
		"Left side bound?",
		'BFLG',
		/* [2397] */
		"Top side bound?",
		'BFLG',
		/* [2398] */
		"Right side bound?",
		'BFLG',
		/* [2399] */
		"Bottom side bound?",
		'BFLG',
		/* [2400] */
		"Left in super image",
		'DLNG',
		/* [2401] */
		"Top in super image",
		'DLNG',
		/* [2402] */
		"User constant",
		'DLNG',
		/* [2403] */
		"Superview",
		'DLNG',
		/* [2404] */
		"Default=-1",
		'CASE',
		/* [2405] */
		"None=0",
		'CASE',
		/* [2406] */
		"Slider data",
		'DVDR',
		/* [2407] */
		"Value changed message",
		'DLNG',
		/* [2408] */
		"Initial value",
		'DLNG',
		/* [2409] */
		"Minimum value",
		'DLNG',
		/* [2410] */
		"Maximum value",
		'DLNG',
		/* [2411] */
		"Control Kind",
		'WB12',
		/* [2412] */
		"Slider=3",
		'CASE',
		/* [2413] */
		"Directional",
		'WBIT',
		/* [2414] */
		"Reverse Direction",
		'WBIT',
		/* [2415] */
		"Has Tick Marks",
		'WBIT',
		/* [2416] */
		"Live Feedback",
		'WBIT',
		/* [2417] */
		"Number of Tick Marks",
		'DWRD',
		/* [2418] */
		"",
		'KEYE',
		/* [2419] */
		"stxt",
		'KEYB',
		/* [2420] */
		"Pane data",
		'DVDR',
		/* [2421] */
		"Pane ID",
		'DLNG',
		/* [2422] */
		"Width",
		'DWRD',
		/* [2423] */
		"Height",
		'DWRD',
		/* [2424] */
		"Visible?",
		'BFLG',
		/* [2425] */
		"Enabled?",
		'BFLG',
		/* [2426] */
		"Left side bound?",
		'BFLG',
		/* [2427] */
		"Top side bound?",
		'BFLG',
		/* [2428] */
		"Right side bound?",
		'BFLG',
		/* [2429] */
		"Bottom side bound?",
		'BFLG',
		/* [2430] */
		"Left in super image",
		'DLNG',
		/* [2431] */
		"Top in super image",
		'DLNG',
		/* [2432] */
		"User constant",
		'DLNG',
		/* [2433] */
		"Superview",
		'DLNG',
		/* [2434] */
		"Default=-1",
		'CASE',
		/* [2435] */
		"None=0",
		'CASE',
		/* [2436] */
		"Separator Line data",
		'DVDR',
		/* [2437] */
		"Value changed message",
		'DLNG',
		/* [2438] */
		"Unused=0",
		'CASE',
		/* [2439] */
		"Initial value",
		'DLNG',
		/* [2440] */
		"Unused=0",
		'CASE',
		/* [2441] */
		"Minimum value",
		'DLNG',
		/* [2442] */
		"Unused=0",
		'CASE',
		/* [2443] */
		"Maximum value",
		'DLNG',
		/* [2444] */
		"Unused=0",
		'CASE',
		/* [2445] */
		"Control Kind",
		'DWRD',
		/* [2446] */
		"Static Text=288",
		'CASE',
		/* [2447] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [2448] */
		"Use System Font=0",
		'CASE',
		/* [2449] */
		"Title",
		'PSTR',
		/* [2450] */
		"",
		'KEYE',
		/* [2451] */
		"tabs",
		'KEYB',
		/* [2452] */
		"Pane data",
		'DVDR',
		/* [2453] */
		"Pane ID",
		'DLNG',
		/* [2454] */
		"Width",
		'DWRD',
		/* [2455] */
		"Height",
		'DWRD',
		/* [2456] */
		"Visible?",
		'BFLG',
		/* [2457] */
		"Enabled?",
		'BFLG',
		/* [2458] */
		"Left side bound?",
		'BFLG',
		/* [2459] */
		"Top side bound?",
		'BFLG',
		/* [2460] */
		"Right side bound?",
		'BFLG',
		/* [2461] */
		"Bottom side bound?",
		'BFLG',
		/* [2462] */
		"Left in super image",
		'DLNG',
		/* [2463] */
		"Top in super image",
		'DLNG',
		/* [2464] */
		"User constant",
		'DLNG',
		/* [2465] */
		"Superview",
		'DLNG',
		/* [2466] */
		"Default=-1",
		'CASE',
		/* [2467] */
		"None=0",
		'CASE',
		/* [2468] */
		"View data",
		'DVDR',
		/* [2469] */
		"Image width",
		'DLNG',
		/* [2470] */
		"Image height",
		'DLNG',
		/* [2471] */
		"Horizontal scroll position",
		'DLNG',
		/* [2472] */
		"Vertical scroll position",
		'DLNG',
		/* [2473] */
		"Horizontal scroll unit",
		'DLNG',
		/* [2474] */
		"Vertical scroll unit",
		'DLNG',
		/* [2475] */
		"Reconcile overhang?",
		'WFLG',
		/* [2476] */
		"TabsControl data",
		'DVDR',
		/* [2477] */
		"Value changed message",
		'DLNG',
		/* [2478] */
		"Filler",
		'FWRD',
		/* [2479] */
		"'tab#' Resource ID",
		'RSID',
		/* [2480] */
		"Minimum",
		'DLNG',
		/* [2481] */
		"Unused=0",
		'CASE',
		/* [2482] */
		"Maximum",
		'DLNG',
		/* [2483] */
		"Unused=0",
		'CASE',
		/* [2484] */
		"Tab Size",
		'DWRD',
		/* [2485] */
		"Large=128",
		'CASE',
		/* [2486] */
		"Small=129",
		'CASE',
		/* [2487] */
		"Text traits ('Txtr') ID",
		'DWRD',
		/* [2488] */
		"Use System Font=0",
		'CASE',
		/* [2489] */
		"Title",
		'PSTR',
		/* [2490] */
		"Initial Tab Choice",
		'DWRD',
		/* [2491] */
		"",
		'KEYE',
		/* [2492] */
		"tgbx",
		'KEYB',
		/* [2493] */
		"Pane data",
		'DVDR',
		/* [2494] */
		"Pane ID",
		'DLNG',
		/* [2495] */
		"Width",
		'DWRD',
		/* [2496] */
		"Height",
		'DWRD',
		/* [2497] */
		"Visible?",
		'BFLG',
		/* [2498] */
		"Enabled?",
		'BFLG',
		/* [2499] */
		"Left side bound?",
		'BFLG',
		/* [2500] */
		"Top side bound?",
		'BFLG',
		/* [2501] */
		"Right side bound?",
		'BFLG',
		/* [2502] */
		"Bottom side bound?",
		'BFLG',
		/* [2503] */
		"Left in super image",
		'DLNG',
		/* [2504] */
		"Top in super image",
		'DLNG',
		/* [2505] */
		"User constant",
		'DLNG',
		/* [2506] */
		"Superview",
		'DLNG',
		/* [2507] */
		"Default=-1",
		'CASE',
		/* [2508] */
		"None=0",
		'CASE',
		/* [2509] */
		"View data",
		'DVDR',
		/* [2510] */
		"Image width",
		'DLNG',
		/* [2511] */
		"Image height",
		'DLNG',
		/* [2512] */
		"Horizontal scroll position",
		'DLNG',
		/* [2513] */
		"Vertical scroll position",
		'DLNG',
		/* [2514] */
		"Horizontal scroll unit",
		'DLNG',
		/* [2515] */
		"Vertical scroll unit",
		'DLNG',
		/* [2516] */
		"Reconcile overhang?",
		'WFLG',
		/* [2517] */
		"TextGroupBox data",
		'DVDR',
		/* [2518] */
		"Value changed message",
		'DLNG',
		/* [2519] */
		"Unused=0",
		'CASE',
		/* [2520] */
		"Value",
		'DLNG',
		/* [2521] */
		"Unused=0",
		'CASE',
		/* [2522] */
		"Minimum",
		'DLNG',
		/* [2523] */
		"Unused=0",
		'CASE',
		/* [2524] */
		"Maximum",
		'DLNG',
		/* [2525] */
		"Unused=0",
		'CASE',
		/* [2526] */
		"Group Kind",
		'DWRD',
		/* [2527] */
		"Primary=160",
		'CASE',
		/* [2528] */
		"Secondary=164",
		'CASE',
		/* [2529] */
		"Text traits ('Txtr') ID",
		'DWRD',
		/* [2530] */
		"Use System Font=0",
		'CASE',
		/* [2531] */
		"Title",
		'PSTR',
		/* [2532] */
		"",
		'KEYE',
		/* [2533] */
		"winh",
		'KEYB',
		/* [2534] */
		"Pane data",
		'DVDR',
		/* [2535] */
		"Pane ID",
		'DLNG',
		/* [2536] */
		"Width",
		'DWRD',
		/* [2537] */
		"Height",
		'DWRD',
		/* [2538] */
		"Visible?",
		'BFLG',
		/* [2539] */
		"Enabled?",
		'BFLG',
		/* [2540] */
		"Left side bound?",
		'BFLG',
		/* [2541] */
		"Top side bound?",
		'BFLG',
		/* [2542] */
		"Right side bound?",
		'BFLG',
		/* [2543] */
		"Bottom side bound?",
		'BFLG',
		/* [2544] */
		"Left in super image",
		'DLNG',
		/* [2545] */
		"Top in super image",
		'DLNG',
		/* [2546] */
		"User constant",
		'DLNG',
		/* [2547] */
		"Superview",
		'DLNG',
		/* [2548] */
		"Default=-1",
		'CASE',
		/* [2549] */
		"None=0",
		'CASE',
		/* [2550] */
		"View data",
		'DVDR',
		/* [2551] */
		"Image width",
		'DLNG',
		/* [2552] */
		"Image height",
		'DLNG',
		/* [2553] */
		"Horizontal scroll position",
		'DLNG',
		/* [2554] */
		"Vertical scroll position",
		'DLNG',
		/* [2555] */
		"Horizontal scroll unit",
		'DLNG',
		/* [2556] */
		"Vertical scroll unit",
		'DLNG',
		/* [2557] */
		"Reconcile overhang?",
		'WFLG',
		/* [2558] */
		"Window Header data",
		'DVDR',
		/* [2559] */
		"Value changed message",
		'DLNG',
		/* [2560] */
		"Unused=0",
		'CASE',
		/* [2561] */
		"Value",
		'DLNG',
		/* [2562] */
		"Unused=0",
		'CASE',
		/* [2563] */
		"Minimum",
		'DLNG',
		/* [2564] */
		"Unused=0",
		'CASE',
		/* [2565] */
		"Maximum",
		'DLNG',
		/* [2566] */
		"Unused=0",
		'CASE',
		/* [2567] */
		"Header Kind",
		'DWRD',
		/* [2568] */
		"Normal=336",
		'CASE',
		/* [2569] */
		"List View=337",
		'CASE',
		/* [2570] */
		"Text traits ID",
		'DWRD',
		/* [2571] */
		"Unused=0",
		'CASE',
		/* [2572] */
		"Title",
		'PSTR',
		/* [2573] */
		"",
		'KEYE',
		/* [2574] */
		"gchk",
		'KEYB',
		/* [2575] */
		"Pane data",
		'DVDR',
		/* [2576] */
		"Pane ID",
		'DLNG',
		/* [2577] */
		"Width",
		'DWRD',
		/* [2578] */
		"Height",
		'DWRD',
		/* [2579] */
		"Visible?",
		'BFLG',
		/* [2580] */
		"Enabled?",
		'BFLG',
		/* [2581] */
		"Left side bound?",
		'BFLG',
		/* [2582] */
		"Top side bound?",
		'BFLG',
		/* [2583] */
		"Right side bound?",
		'BFLG',
		/* [2584] */
		"Bottom side bound?",
		'BFLG',
		/* [2585] */
		"Left in super image",
		'DLNG',
		/* [2586] */
		"Top in super image",
		'DLNG',
		/* [2587] */
		"User constant",
		'DLNG',
		/* [2588] */
		"Superview",
		'DLNG',
		/* [2589] */
		"Default=-1",
		'CASE',
		/* [2590] */
		"None=0",
		'CASE',
		/* [2591] */
		"Standard check box data",
		'DVDR',
		/* [2592] */
		"Value changed message",
		'DLNG',
		/* [2593] */
		"Initial value",
		'DLNG',
		/* [2594] */
		"Unchecked=0",
		'CASE',
		/* [2595] */
		"Checked=1",
		'CASE',
		/* [2596] */
		"Minimum value",
		'DLNG',
		/* [2597] */
		"Always=0",
		'CASE',
		/* [2598] */
		"Maximum value",
		'DLNG',
		/* [2599] */
		"Always=1",
		'CASE',
		/* [2600] */
		"Check box proc",
		'DWRD',
		/* [2601] */
		"Default=1",
		'CASE',
		/* [2602] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [2603] */
		"System font=0",
		'CASE',
		/* [2604] */
		"Title",
		'PSTR',
		/* [2605] */
		"Standard Control RefCon",
		'DLNG',
		/* [2606] */
		"",
		'KEYE',
		/* [2607] */
		"gpsh",
		'KEYB',
		/* [2608] */
		"Pane data",
		'DVDR',
		/* [2609] */
		"Pane ID",
		'DLNG',
		/* [2610] */
		"Width",
		'DWRD',
		/* [2611] */
		"Height",
		'DWRD',
		/* [2612] */
		"Visible?",
		'BFLG',
		/* [2613] */
		"Enabled?",
		'BFLG',
		/* [2614] */
		"Left side bound?",
		'BFLG',
		/* [2615] */
		"Top side bound?",
		'BFLG',
		/* [2616] */
		"Right side bound?",
		'BFLG',
		/* [2617] */
		"Bottom side bound?",
		'BFLG',
		/* [2618] */
		"Left in super image",
		'DLNG',
		/* [2619] */
		"Top in super image",
		'DLNG',
		/* [2620] */
		"User constant",
		'DLNG',
		/* [2621] */
		"Superview",
		'DLNG',
		/* [2622] */
		"Default=-1",
		'CASE',
		/* [2623] */
		"None=0",
		'CASE',
		/* [2624] */
		"Standard button data",
		'DVDR',
		/* [2625] */
		"Message when pushed",
		'DLNG',
		/* [2626] */
		"cmd_Nothing=0",
		'CASE',
		/* [2627] */
		"cmd_Close=4",
		'CASE',
		/* [2628] */
		"msg_OK=900",
		'CASE',
		/* [2629] */
		"msg_Cancel=901",
		'CASE',
		/* [2630] */
		"Initial value",
		'DLNG',
		/* [2631] */
		"Always=0",
		'CASE',
		/* [2632] */
		"Minimum value",
		'DLNG',
		/* [2633] */
		"Always=0",
		'CASE',
		/* [2634] */
		"Maximum value",
		'DLNG',
		/* [2635] */
		"Always=0",
		'CASE',
		/* [2636] */
		"Push button proc",
		'DWRD',
		/* [2637] */
		"Default=0",
		'CASE',
		/* [2638] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [2639] */
		"System font=0",
		'CASE',
		/* [2640] */
		"Title",
		'PSTR',
		/* [2641] */
		"Okay=OK",
		'CASE',
		/* [2642] */
		"Cancel=Cancel",
		'CASE',
		/* [2643] */
		"Standard Control RefCon",
		'DLNG',
		/* [2644] */
		"",
		'KEYE',
		/* [2645] */
		"grad",
		'KEYB',
		/* [2646] */
		"Pane data",
		'DVDR',
		/* [2647] */
		"Pane ID",
		'DLNG',
		/* [2648] */
		"Width",
		'DWRD',
		/* [2649] */
		"Height",
		'DWRD',
		/* [2650] */
		"Visible?",
		'BFLG',
		/* [2651] */
		"Enabled?",
		'BFLG',
		/* [2652] */
		"Left side bound?",
		'BFLG',
		/* [2653] */
		"Top side bound?",
		'BFLG',
		/* [2654] */
		"Right side bound?",
		'BFLG',
		/* [2655] */
		"Bottom side bound?",
		'BFLG',
		/* [2656] */
		"Left in super image",
		'DLNG',
		/* [2657] */
		"Top in super image",
		'DLNG',
		/* [2658] */
		"User constant",
		'DLNG',
		/* [2659] */
		"Superview",
		'DLNG',
		/* [2660] */
		"Default=-1",
		'CASE',
		/* [2661] */
		"None=0",
		'CASE',
		/* [2662] */
		"Standard radio button data",
		'DVDR',
		/* [2663] */
		"Value changed message",
		'DLNG',
		/* [2664] */
		"Initial value",
		'DLNG',
		/* [2665] */
		"Unchecked=0",
		'CASE',
		/* [2666] */
		"Checked=1",
		'CASE',
		/* [2667] */
		"Minimum value",
		'DLNG',
		/* [2668] */
		"Always=0",
		'CASE',
		/* [2669] */
		"Maximum value",
		'DLNG',
		/* [2670] */
		"Always=1",
		'CASE',
		/* [2671] */
		"Radio button proc",
		'DWRD',
		/* [2672] */
		"Default=2",
		'CASE',
		/* [2673] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [2674] */
		"System font=0",
		'CASE',
		/* [2675] */
		"Title",
		'PSTR',
		/* [2676] */
		"Standard Control RefCon",
		'DLNG',
		/* [2677] */
		"",
		'KEYE',
		/* [2678] */
		"gibt",
		'KEYB',
		/* [2679] */
		"Pane data",
		'DVDR',
		/* [2680] */
		"Pane ID",
		'DLNG',
		/* [2681] */
		"Width",
		'DWRD',
		/* [2682] */
		"Height",
		'DWRD',
		/* [2683] */
		"Visible?",
		'BFLG',
		/* [2684] */
		"Enabled?",
		'BFLG',
		/* [2685] */
		"Left side bound?",
		'BFLG',
		/* [2686] */
		"Top side bound?",
		'BFLG',
		/* [2687] */
		"Right side bound?",
		'BFLG',
		/* [2688] */
		"Bottom side bound?",
		'BFLG',
		/* [2689] */
		"Left in super image",
		'DLNG',
		/* [2690] */
		"Top in super image",
		'DLNG',
		/* [2691] */
		"User constant",
		'DLNG',
		/* [2692] */
		"Superview",
		'DLNG',
		/* [2693] */
		"Default=-1",
		'CASE',
		/* [2694] */
		"None=0",
		'CASE',
		/* [2695] */
		"Control data",
		'DVDR',
		/* [2696] */
		"Value changed message",
		'DLNG',
		/* [2697] */
		"Initial value",
		'DLNG',
		/* [2698] */
		"Minimum value",
		'DLNG',
		/* [2699] */
		"Maximum value",
		'DLNG',
		/* [2700] */
		"Icon Button Data",
		'DVDR',
		/* [2701] */
		"Control Mode",
		'DWRD',
		/* [2702] */
		"None=0",
		'CASE',
		/* [2703] */
		"Button=1",
		'CASE',
		/* [2704] */
		"Radio=2",
		'CASE',
		/* [2705] */
		"Switch=3",
		'CASE',
		/* [2706] */
		"Icon Suite ('ICN#') ID",
		'RSID',
		/* [2707] */
		"Icon Size",
		'DWRD',
		/* [2708] */
		"None=0",
		'CASE',
		/* [2709] */
		"Mini=12",
		'CASE',
		/* [2710] */
		"Small=16",
		'CASE',
		/* [2711] */
		"Large=32",
		'CASE',
		/* [2712] */
		"Position",
		'DWRD',
		/* [2713] */
		"None=0",
		'CASE',
		/* [2714] */
		"Top Left=1",
		'CASE',
		/* [2715] */
		"Top Center=2",
		'CASE',
		/* [2716] */
		"Top Right=3",
		'CASE',
		/* [2717] */
		"Right Center=4",
		'CASE',
		/* [2718] */
		"Bottom Right=5",
		'CASE',
		/* [2719] */
		"Bottom Center=6",
		'CASE',
		/* [2720] */
		"Bottom Left=7",
		'CASE',
		/* [2721] */
		"Left Center=8",
		'CASE',
		/* [2722] */
		"Center=9",
		'CASE',
		/* [2723] */
		"Hilite",
		'BFLG',
		/* [2724] */
		"Offset",
		'BFLG',
		/* [2725] */
		"",
		'KEYE',
		/* [2726] */
		"gcib",
		'KEYB',
		/* [2727] */
		"Pane data",
		'DVDR',
		/* [2728] */
		"Pane ID",
		'DLNG',
		/* [2729] */
		"Width",
		'DWRD',
		/* [2730] */
		"Height",
		'DWRD',
		/* [2731] */
		"Visible?",
		'BFLG',
		/* [2732] */
		"Enabled?",
		'BFLG',
		/* [2733] */
		"Left side bound?",
		'BFLG',
		/* [2734] */
		"Top side bound?",
		'BFLG',
		/* [2735] */
		"Right side bound?",
		'BFLG',
		/* [2736] */
		"Bottom side bound?",
		'BFLG',
		/* [2737] */
		"Left in super image",
		'DLNG',
		/* [2738] */
		"Top in super image",
		'DLNG',
		/* [2739] */
		"User constant",
		'DLNG',
		/* [2740] */
		"Superview",
		'DLNG',
		/* [2741] */
		"Default=-1",
		'CASE',
		/* [2742] */
		"None=0",
		'CASE',
		/* [2743] */
		"Control data",
		'DVDR',
		/* [2744] */
		"Value changed message",
		'DLNG',
		/* [2745] */
		"Initial value",
		'DLNG',
		/* [2746] */
		"Minimum value",
		'DLNG',
		/* [2747] */
		"Maximum value",
		'DLNG',
		/* [2748] */
		"Icon Button Data",
		'DVDR',
		/* [2749] */
		"Control Mode",
		'DWRD',
		/* [2750] */
		"None=0",
		'CASE',
		/* [2751] */
		"Button=1",
		'CASE',
		/* [2752] */
		"Radio=2",
		'CASE',
		/* [2753] */
		"Switch=3",
		'CASE',
		/* [2754] */
		"Icon Suite ('ICN#') ID",
		'RSID',
		/* [2755] */
		"Icon Size",
		'DWRD',
		/* [2756] */
		"None=0",
		'CASE',
		/* [2757] */
		"Mini=12",
		'CASE',
		/* [2758] */
		"Small=16",
		'CASE',
		/* [2759] */
		"Large=32",
		'CASE',
		/* [2760] */
		"Position",
		'DWRD',
		/* [2761] */
		"None=0",
		'CASE',
		/* [2762] */
		"Top Left=1",
		'CASE',
		/* [2763] */
		"Top Center=2",
		'CASE',
		/* [2764] */
		"Top Right=3",
		'CASE',
		/* [2765] */
		"Right Center=4",
		'CASE',
		/* [2766] */
		"Bottom Right=5",
		'CASE',
		/* [2767] */
		"Bottom Center=6",
		'CASE',
		/* [2768] */
		"Bottom Left=7",
		'CASE',
		/* [2769] */
		"Left Center=8",
		'CASE',
		/* [2770] */
		"Center=9",
		'CASE',
		/* [2771] */
		"Hilite",
		'BFLG',
		/* [2772] */
		"Offset",
		'BFLG',
		/* [2773] */
		"Cmd Icon Button Data",
		'DVDR',
		/* [2774] */
		"Command Number",
		'DLNG',
		/* [2775] */
		"",
		'KEYE',
		/* [2776] */
		"gtxb",
		'KEYB',
		/* [2777] */
		"Pane data",
		'DVDR',
		/* [2778] */
		"Pane ID",
		'DLNG',
		/* [2779] */
		"Width",
		'DWRD',
		/* [2780] */
		"Height",
		'DWRD',
		/* [2781] */
		"Visible?",
		'BFLG',
		/* [2782] */
		"Enabled?",
		'BFLG',
		/* [2783] */
		"Left side bound?",
		'BFLG',
		/* [2784] */
		"Top side bound?",
		'BFLG',
		/* [2785] */
		"Right side bound?",
		'BFLG',
		/* [2786] */
		"Bottom side bound?",
		'BFLG',
		/* [2787] */
		"Left in super image",
		'DLNG',
		/* [2788] */
		"Top in super image",
		'DLNG',
		/* [2789] */
		"User constant",
		'DLNG',
		/* [2790] */
		"Superview",
		'DLNG',
		/* [2791] */
		"Default=-1",
		'CASE',
		/* [2792] */
		"None=0",
		'CASE',
		/* [2793] */
		"Control data",
		'DVDR',
		/* [2794] */
		"Value changed message",
		'DLNG',
		/* [2795] */
		"Initial value",
		'DLNG',
		/* [2796] */
		"Minimum value",
		'DLNG',
		/* [2797] */
		"Maximum value",
		'DLNG',
		/* [2798] */
		"Standard control data",
		'DVDR',
		/* [2799] */
		"Control kind",
		'DWRD',
		/* [2800] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [2801] */
		"System font=0",
		'CASE',
		/* [2802] */
		"Title",
		'PSTR',
		/* [2803] */
		"Standard Control RefCon",
		'DLNG',
		/* [2804] */
		"",
		'KEYE',
		/* [2805] */
		"gctb",
		'KEYB',
		/* [2806] */
		"Pane data",
		'DVDR',
		/* [2807] */
		"Pane ID",
		'DLNG',
		/* [2808] */
		"Width",
		'DWRD',
		/* [2809] */
		"Height",
		'DWRD',
		/* [2810] */
		"Visible?",
		'BFLG',
		/* [2811] */
		"Enabled?",
		'BFLG',
		/* [2812] */
		"Left side bound?",
		'BFLG',
		/* [2813] */
		"Top side bound?",
		'BFLG',
		/* [2814] */
		"Right side bound?",
		'BFLG',
		/* [2815] */
		"Bottom side bound?",
		'BFLG',
		/* [2816] */
		"Left in super image",
		'DLNG',
		/* [2817] */
		"Top in super image",
		'DLNG',
		/* [2818] */
		"User constant",
		'DLNG',
		/* [2819] */
		"Superview",
		'DLNG',
		/* [2820] */
		"Default=-1",
		'CASE',
		/* [2821] */
		"None=0",
		'CASE',
		/* [2822] */
		"Control data",
		'DVDR',
		/* [2823] */
		"Value changed message",
		'DLNG',
		/* [2824] */
		"Initial value",
		'DLNG',
		/* [2825] */
		"Minimum value",
		'DLNG',
		/* [2826] */
		"Maximum value",
		'DLNG',
		/* [2827] */
		"Standard control data",
		'DVDR',
		/* [2828] */
		"Control kind",
		'DWRD',
		/* [2829] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [2830] */
		"System font=0",
		'CASE',
		/* [2831] */
		"Title",
		'PSTR',
		/* [2832] */
		"Standard Control RefCon",
		'DLNG',
		/* [2833] */
		"Cmd Text Button Data",
		'DVDR',
		/* [2834] */
		"Command Number",
		'DLNG',
		/* [2835] */
		"",
		'KEYE',
		/* [2836] */
		"gdcl",
		'KEYB',
		/* [2837] */
		"Pane data",
		'DVDR',
		/* [2838] */
		"Pane ID",
		'DLNG',
		/* [2839] */
		"Width",
		'DWRD',
		/* [2840] */
		"Height",
		'DWRD',
		/* [2841] */
		"Visible?",
		'BFLG',
		/* [2842] */
		"Enabled?",
		'BFLG',
		/* [2843] */
		"Left side bound?",
		'BFLG',
		/* [2844] */
		"Top side bound?",
		'BFLG',
		/* [2845] */
		"Right side bound?",
		'BFLG',
		/* [2846] */
		"Bottom side bound?",
		'BFLG',
		/* [2847] */
		"Left in super image",
		'DLNG',
		/* [2848] */
		"Top in super image",
		'DLNG',
		/* [2849] */
		"User constant",
		'DLNG',
		/* [2850] */
		"Superview",
		'DLNG',
		/* [2851] */
		"Default=-1",
		'CASE',
		/* [2852] */
		"None=0",
		'CASE',
		/* [2853] */
		"Control data",
		'DVDR',
		/* [2854] */
		"Value changed message",
		'DLNG',
		/* [2855] */
		"Initial value",
		'DLNG',
		/* [2856] */
		"Minimum value",
		'DLNG',
		/* [2857] */
		"Maximum value",
		'DLNG',
		/* [2858] */
		"Direction (Faces Right=0, Faces Left=1)",
		'BFLG',
		/* [2859] */
		"",
		'KEYE',
		/* [2860] */
		"gitb",
		'KEYB',
		/* [2861] */
		"Pane data",
		'DVDR',
		/* [2862] */
		"Pane ID",
		'DLNG',
		/* [2863] */
		"Width",
		'DWRD',
		/* [2864] */
		"Height",
		'DWRD',
		/* [2865] */
		"Visible?",
		'BFLG',
		/* [2866] */
		"Enabled?",
		'BFLG',
		/* [2867] */
		"Left side bound?",
		'BFLG',
		/* [2868] */
		"Top side bound?",
		'BFLG',
		/* [2869] */
		"Right side bound?",
		'BFLG',
		/* [2870] */
		"Bottom side bound?",
		'BFLG',
		/* [2871] */
		"Left in super image",
		'DLNG',
		/* [2872] */
		"Top in super image",
		'DLNG',
		/* [2873] */
		"User constant",
		'DLNG',
		/* [2874] */
		"Superview",
		'DLNG',
		/* [2875] */
		"Default=-1",
		'CASE',
		/* [2876] */
		"None=0",
		'CASE',
		/* [2877] */
		"Control data",
		'DVDR',
		/* [2878] */
		"Value changed message",
		'DLNG',
		/* [2879] */
		"Initial value",
		'DLNG',
		/* [2880] */
		"Minimum value",
		'DLNG',
		/* [2881] */
		"Maximum value",
		'DLNG',
		/* [2882] */
		"Icon Button Data",
		'DVDR',
		/* [2883] */
		"Control Mode",
		'DWRD',
		/* [2884] */
		"None=0",
		'CASE',
		/* [2885] */
		"Button=1",
		'CASE',
		/* [2886] */
		"Radio=2",
		'CASE',
		/* [2887] */
		"Switch=3",
		'CASE',
		/* [2888] */
		"Icon Suite ('ICN#') ID",
		'RSID',
		/* [2889] */
		"Icon Size",
		'DWRD',
		/* [2890] */
		"None=0",
		'CASE',
		/* [2891] */
		"Mini=12",
		'CASE',
		/* [2892] */
		"Small=16",
		'CASE',
		/* [2893] */
		"Large=32",
		'CASE',
		/* [2894] */
		"Position",
		'DWRD',
		/* [2895] */
		"None=0",
		'CASE',
		/* [2896] */
		"Top Left=1",
		'CASE',
		/* [2897] */
		"Top Center=2",
		'CASE',
		/* [2898] */
		"Top Right=3",
		'CASE',
		/* [2899] */
		"Right Center=4",
		'CASE',
		/* [2900] */
		"Bottom Right=5",
		'CASE',
		/* [2901] */
		"Bottom Center=6",
		'CASE',
		/* [2902] */
		"Bottom Left=7",
		'CASE',
		/* [2903] */
		"Left Center=8",
		'CASE',
		/* [2904] */
		"Center=9",
		'CASE',
		/* [2905] */
		"Hilite",
		'BFLG',
		/* [2906] */
		"Offset",
		'BFLG',
		/* [2907] */
		"Icon Text Button Data",
		'DVDR',
		/* [2908] */
		"Title",
		'PSTR',
		/* [2909] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [2910] */
		"System font=0",
		'CASE',
		/* [2911] */
		"",
		'KEYE',
		/* [2912] */
		"gcit",
		'KEYB',
		/* [2913] */
		"Pane data",
		'DVDR',
		/* [2914] */
		"Pane ID",
		'DLNG',
		/* [2915] */
		"Width",
		'DWRD',
		/* [2916] */
		"Height",
		'DWRD',
		/* [2917] */
		"Visible?",
		'BFLG',
		/* [2918] */
		"Enabled?",
		'BFLG',
		/* [2919] */
		"Left side bound?",
		'BFLG',
		/* [2920] */
		"Top side bound?",
		'BFLG',
		/* [2921] */
		"Right side bound?",
		'BFLG',
		/* [2922] */
		"Bottom side bound?",
		'BFLG',
		/* [2923] */
		"Left in super image",
		'DLNG',
		/* [2924] */
		"Top in super image",
		'DLNG',
		/* [2925] */
		"User constant",
		'DLNG',
		/* [2926] */
		"Superview",
		'DLNG',
		/* [2927] */
		"Default=-1",
		'CASE',
		/* [2928] */
		"None=0",
		'CASE',
		/* [2929] */
		"Control data",
		'DVDR',
		/* [2930] */
		"Value changed message",
		'DLNG',
		/* [2931] */
		"Initial value",
		'DLNG',
		/* [2932] */
		"Minimum value",
		'DLNG',
		/* [2933] */
		"Maximum value",
		'DLNG',
		/* [2934] */
		"Icon Button Data",
		'DVDR',
		/* [2935] */
		"Control Mode",
		'DWRD',
		/* [2936] */
		"None=0",
		'CASE',
		/* [2937] */
		"Button=1",
		'CASE',
		/* [2938] */
		"Radio=2",
		'CASE',
		/* [2939] */
		"Switch=3",
		'CASE',
		/* [2940] */
		"Icon Suite ('ICN#') ID",
		'RSID',
		/* [2941] */
		"Icon Size",
		'DWRD',
		/* [2942] */
		"None=0",
		'CASE',
		/* [2943] */
		"Mini=12",
		'CASE',
		/* [2944] */
		"Small=16",
		'CASE',
		/* [2945] */
		"Large=32",
		'CASE',
		/* [2946] */
		"Position",
		'DWRD',
		/* [2947] */
		"None=0",
		'CASE',
		/* [2948] */
		"Top Left=1",
		'CASE',
		/* [2949] */
		"Top Center=2",
		'CASE',
		/* [2950] */
		"Top Right=3",
		'CASE',
		/* [2951] */
		"Right Center=4",
		'CASE',
		/* [2952] */
		"Bottom Right=5",
		'CASE',
		/* [2953] */
		"Bottom Center=6",
		'CASE',
		/* [2954] */
		"Bottom Left=7",
		'CASE',
		/* [2955] */
		"Left Center=8",
		'CASE',
		/* [2956] */
		"Center=9",
		'CASE',
		/* [2957] */
		"Hilite",
		'BFLG',
		/* [2958] */
		"Offset",
		'BFLG',
		/* [2959] */
		"Icon Text Button Data",
		'DVDR',
		/* [2960] */
		"Title",
		'PSTR',
		/* [2961] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [2962] */
		"System font=0",
		'CASE',
		/* [2963] */
		"Command Number",
		'DLNG',
		/* [2964] */
		"",
		'KEYE',
		/* [2965] */
		"gibp",
		'KEYB',
		/* [2966] */
		"Pane data",
		'DVDR',
		/* [2967] */
		"Pane ID",
		'DLNG',
		/* [2968] */
		"Width",
		'DWRD',
		/* [2969] */
		"Height",
		'DWRD',
		/* [2970] */
		"Visible?",
		'BFLG',
		/* [2971] */
		"Enabled?",
		'BFLG',
		/* [2972] */
		"Left side bound?",
		'BFLG',
		/* [2973] */
		"Top side bound?",
		'BFLG',
		/* [2974] */
		"Right side bound?",
		'BFLG',
		/* [2975] */
		"Bottom side bound?",
		'BFLG',
		/* [2976] */
		"Left in super image",
		'DLNG',
		/* [2977] */
		"Top in super image",
		'DLNG',
		/* [2978] */
		"User constant",
		'DLNG',
		/* [2979] */
		"Superview",
		'DLNG',
		/* [2980] */
		"Default=-1",
		'CASE',
		/* [2981] */
		"None=0",
		'CASE',
		/* [2982] */
		"Control data",
		'DVDR',
		/* [2983] */
		"Value changed message",
		'DLNG',
		/* [2984] */
		"Initial value",
		'DLNG',
		/* [2985] */
		"Minimum value",
		'DLNG',
		/* [2986] */
		"Maximum value",
		'DLNG',
		/* [2987] */
		"Icon Button Data",
		'DVDR',
		/* [2988] */
		"Control Mode",
		'DWRD',
		/* [2989] */
		"None=0",
		'CASE',
		/* [2990] */
		"Button=1",
		'CASE',
		/* [2991] */
		"Radio=2",
		'CASE',
		/* [2992] */
		"Switch=3",
		'CASE',
		/* [2993] */
		"Icon Suite ('ICN#') ID",
		'RSID',
		/* [2994] */
		"Icon Size",
		'DWRD',
		/* [2995] */
		"None=0",
		'CASE',
		/* [2996] */
		"Mini=12",
		'CASE',
		/* [2997] */
		"Small=16",
		'CASE',
		/* [2998] */
		"Large=32",
		'CASE',
		/* [2999] */
		"Position",
		'DWRD',
		/* [3000] */
		"None=0",
		'CASE',
		/* [3001] */
		"Top Left=1",
		'CASE',
		/* [3002] */
		"Top Center=2",
		'CASE',
		/* [3003] */
		"Top Right=3",
		'CASE',
		/* [3004] */
		"Right Center=4",
		'CASE',
		/* [3005] */
		"Bottom Right=5",
		'CASE',
		/* [3006] */
		"Bottom Center=6",
		'CASE',
		/* [3007] */
		"Bottom Left=7",
		'CASE',
		/* [3008] */
		"Left Center=8",
		'CASE',
		/* [3009] */
		"Center=9",
		'CASE',
		/* [3010] */
		"Hilite",
		'BFLG',
		/* [3011] */
		"Offset",
		'BFLG',
		/* [3012] */
		"Icon Button Popup Data",
		'DVDR',
		/* [3013] */
		"Popup Menu ('MENU') ID",
		'RSID',
		/* [3014] */
		"Initial Item",
		'DWRD',
		/* [3015] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [3016] */
		"System font=0",
		'CASE',
		/* [3017] */
		"",
		'KEYE',
		/* [3018] */
		"gict",
		'KEYB',
		/* [3019] */
		"Pane data",
		'DVDR',
		/* [3020] */
		"Pane ID",
		'DLNG',
		/* [3021] */
		"Width",
		'DWRD',
		/* [3022] */
		"Height",
		'DWRD',
		/* [3023] */
		"Visible?",
		'BFLG',
		/* [3024] */
		"Enabled?",
		'BFLG',
		/* [3025] */
		"Left side bound?",
		'BFLG',
		/* [3026] */
		"Top side bound?",
		'BFLG',
		/* [3027] */
		"Right side bound?",
		'BFLG',
		/* [3028] */
		"Bottom side bound?",
		'BFLG',
		/* [3029] */
		"Left in super image",
		'DLNG',
		/* [3030] */
		"Top in super image",
		'DLNG',
		/* [3031] */
		"User constant",
		'DLNG',
		/* [3032] */
		"Superview",
		'DLNG',
		/* [3033] */
		"Default=-1",
		'CASE',
		/* [3034] */
		"None=0",
		'CASE',
		/* [3035] */
		"Control data",
		'DVDR',
		/* [3036] */
		"Message when pushed",
		'DLNG',
		/* [3037] */
		"Initial value",
		'DLNG',
		/* [3038] */
		"Minimum value",
		'DLNG',
		/* [3039] */
		"Maximum value",
		'DLNG',
		/* [3040] */
		"Icon Suite Control Data",
		'DVDR',
		/* [3041] */
		"Control Mode",
		'DWRD',
		/* [3042] */
		"None=0",
		'CASE',
		/* [3043] */
		"Button=1",
		'CASE',
		/* [3044] */
		"Radio=2",
		'CASE',
		/* [3045] */
		"Switch=3",
		'CASE',
		/* [3046] */
		"Icon Suite ('ICN#') ID",
		'RSID',
		/* [3047] */
		"Icon Size",
		'DWRD',
		/* [3048] */
		"None=0",
		'CASE',
		/* [3049] */
		"Mini=12",
		'CASE',
		/* [3050] */
		"Small=16",
		'CASE',
		/* [3051] */
		"Large=32",
		'CASE',
		/* [3052] */
		"Position",
		'DWRD',
		/* [3053] */
		"None=0",
		'CASE',
		/* [3054] */
		"Top Left=1",
		'CASE',
		/* [3055] */
		"Top Center=2",
		'CASE',
		/* [3056] */
		"Top Right=3",
		'CASE',
		/* [3057] */
		"Right Center=4",
		'CASE',
		/* [3058] */
		"Bottom Right=5",
		'CASE',
		/* [3059] */
		"Bottom Center=6",
		'CASE',
		/* [3060] */
		"Bottom Left=7",
		'CASE',
		/* [3061] */
		"Left Center=8",
		'CASE',
		/* [3062] */
		"Center=9",
		'CASE',
		/* [3063] */
		"Hilite",
		'BFLG',
		/* [3064] */
		"Click in Icon",
		'BFLG',
		/* [3065] */
		"",
		'KEYE',
		/* [3066] */
		"gcic",
		'KEYB',
		/* [3067] */
		"Pane data",
		'DVDR',
		/* [3068] */
		"Pane ID",
		'DLNG',
		/* [3069] */
		"Width",
		'DWRD',
		/* [3070] */
		"Height",
		'DWRD',
		/* [3071] */
		"Visible?",
		'BFLG',
		/* [3072] */
		"Enabled?",
		'BFLG',
		/* [3073] */
		"Left side bound?",
		'BFLG',
		/* [3074] */
		"Top side bound?",
		'BFLG',
		/* [3075] */
		"Right side bound?",
		'BFLG',
		/* [3076] */
		"Bottom side bound?",
		'BFLG',
		/* [3077] */
		"Left in super image",
		'DLNG',
		/* [3078] */
		"Top in super image",
		'DLNG',
		/* [3079] */
		"User constant",
		'DLNG',
		/* [3080] */
		"Superview",
		'DLNG',
		/* [3081] */
		"Default=-1",
		'CASE',
		/* [3082] */
		"None=0",
		'CASE',
		/* [3083] */
		"Control data",
		'DVDR',
		/* [3084] */
		"Message when pushed",
		'DLNG',
		/* [3085] */
		"Initial value",
		'DLNG',
		/* [3086] */
		"Minimum value",
		'DLNG',
		/* [3087] */
		"Maximum value",
		'DLNG',
		/* [3088] */
		"Icon Suite Control Data",
		'DVDR',
		/* [3089] */
		"Control Mode",
		'DWRD',
		/* [3090] */
		"None=0",
		'CASE',
		/* [3091] */
		"Button=1",
		'CASE',
		/* [3092] */
		"Radio=2",
		'CASE',
		/* [3093] */
		"Switch=3",
		'CASE',
		/* [3094] */
		"Icon Suite ('ICN#') ID",
		'RSID',
		/* [3095] */
		"Icon Size",
		'DWRD',
		/* [3096] */
		"None=0",
		'CASE',
		/* [3097] */
		"Mini=12",
		'CASE',
		/* [3098] */
		"Small=16",
		'CASE',
		/* [3099] */
		"Large=32",
		'CASE',
		/* [3100] */
		"Position",
		'DWRD',
		/* [3101] */
		"None=0",
		'CASE',
		/* [3102] */
		"Top Left=1",
		'CASE',
		/* [3103] */
		"Top Center=2",
		'CASE',
		/* [3104] */
		"Top Right=3",
		'CASE',
		/* [3105] */
		"Right Center=4",
		'CASE',
		/* [3106] */
		"Bottom Right=5",
		'CASE',
		/* [3107] */
		"Bottom Center=6",
		'CASE',
		/* [3108] */
		"Bottom Left=7",
		'CASE',
		/* [3109] */
		"Left Center=8",
		'CASE',
		/* [3110] */
		"Center=9",
		'CASE',
		/* [3111] */
		"Hilite",
		'BFLG',
		/* [3112] */
		"Click in Icon",
		'BFLG',
		/* [3113] */
		"Command Number",
		'DLNG',
		/* [3114] */
		"",
		'KEYE',
		/* [3115] */
		"gpop",
		'KEYB',
		/* [3116] */
		"Pane data",
		'DVDR',
		/* [3117] */
		"Pane ID",
		'DLNG',
		/* [3118] */
		"Width",
		'DWRD',
		/* [3119] */
		"Height",
		'DWRD',
		/* [3120] */
		"Visible?",
		'BFLG',
		/* [3121] */
		"Enabled?",
		'BFLG',
		/* [3122] */
		"Left side bound?",
		'BFLG',
		/* [3123] */
		"Top side bound?",
		'BFLG',
		/* [3124] */
		"Right side bound?",
		'BFLG',
		/* [3125] */
		"Bottom side bound?",
		'BFLG',
		/* [3126] */
		"Left in super image",
		'DLNG',
		/* [3127] */
		"Top in super image",
		'DLNG',
		/* [3128] */
		"User constant",
		'DLNG',
		/* [3129] */
		"Superview",
		'DLNG',
		/* [3130] */
		"Default=-1",
		'CASE',
		/* [3131] */
		"None=0",
		'CASE',
		/* [3132] */
		"Popup menu data",
		'DVDR',
		/* [3133] */
		"Value changed message",
		'DLNG',
		/* [3134] */
		"Filler",
		'FWRD',
		/* [3135] */
		"Filler bit (ignore)",
		'BBIT',
		/* [3136] */
		"Title style: Extend",
		'BBIT',
		/* [3137] */
		"Title style: Condense",
		'BBIT',
		/* [3138] */
		"Title style: Shadow",
		'BBIT',
		/* [3139] */
		"Title style: Outline",
		'BBIT',
		/* [3140] */
		"Title style: Underline",
		'BBIT',
		/* [3141] */
		"Title style: Italic",
		'BBIT',
		/* [3142] */
		"Title style: Bold",
		'BBIT',
		/* [3143] */
		"Title position",
		'UBYT',
		/* [3144] */
		"Left justified=0",
		'CASE',
		/* [3145] */
		"Center Justified=1",
		'CASE',
		/* [3146] */
		"Right Justified=255",
		'CASE',
		/* [3147] */
		"Filler",
		'FWRD',
		/* [3148] */
		"Resource ID of 'MENU'",
		'RSID',
		/* [3149] */
		"Filler",
		'FWRD',
		/* [3150] */
		"Width (in pixels) of title",
		'DWRD',
		/* [3151] */
		"Type of popup (procID)",
		'DWRD',
		/* [3152] */
		"Standard=1008",
		'CASE',
		/* [3153] */
		"Fixed width=1009",
		'CASE',
		/* [3154] */
		"Add resource=1012",
		'CASE',
		/* [3155] */
		"Fixed and add resource=1013",
		'CASE',
		/* [3156] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [3157] */
		"System font=0",
		'CASE',
		/* [3158] */
		"Title",
		'PSTR',
		/* [3159] */
		"None=",
		'CASE',
		/* [3160] */
		"Resource type for items",
		'TNAM',
		/* [3161] */
		"Initial item choice",
		'DWRD',
		/* [3162] */
		"",
		'KEYE',
		/* [3163] */
		"gabx",
		'KEYB',
		/* [3164] */
		"Pane data",
		'DVDR',
		/* [3165] */
		"Pane ID",
		'DLNG',
		/* [3166] */
		"Width",
		'DWRD',
		/* [3167] */
		"Height",
		'DWRD',
		/* [3168] */
		"Visible?",
		'BFLG',
		/* [3169] */
		"Enabled?",
		'BFLG',
		/* [3170] */
		"Left side bound?",
		'BFLG',
		/* [3171] */
		"Top side bound?",
		'BFLG',
		/* [3172] */
		"Right side bound?",
		'BFLG',
		/* [3173] */
		"Bottom side bound?",
		'BFLG',
		/* [3174] */
		"Left in super image",
		'DLNG',
		/* [3175] */
		"Top in super image",
		'DLNG',
		/* [3176] */
		"User constant",
		'DLNG',
		/* [3177] */
		"Superview",
		'DLNG',
		/* [3178] */
		"Default=-1",
		'CASE',
		/* [3179] */
		"None=0",
		'CASE',
		/* [3180] */
		"View data",
		'DVDR',
		/* [3181] */
		"Image width",
		'DLNG',
		/* [3182] */
		"Image height",
		'DLNG',
		/* [3183] */
		"Horizontal scroll position",
		'DLNG',
		/* [3184] */
		"Vertical scroll position",
		'DLNG',
		/* [3185] */
		"Horizontal scroll unit",
		'DLNG',
		/* [3186] */
		"Vertical scroll unit",
		'DLNG',
		/* [3187] */
		"Reconcile overhang?",
		'WFLG',
		/* [3188] */
		"Box Data",
		'DVDR',
		/* [3189] */
		"Filler",
		'FBYT',
		/* [3190] */
		"Title",
		'PSTR',
		/* [3191] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [3192] */
		"System font=0",
		'CASE',
		/* [3193] */
		"Has Border",
		'BFLG',
		/* [3194] */
		"Border Style",
		'DWRD',
		/* [3195] */
		"None=0",
		'CASE',
		/* [3196] */
		"Plain=1",
		'CASE',
		/* [3197] */
		"Bezel=2",
		'CASE',
		/* [3198] */
		"Recessed One=3",
		'CASE',
		/* [3199] */
		"Recessed Two=4",
		'CASE',
		/* [3200] */
		"Embossed One=5",
		'CASE',
		/* [3201] */
		"Embossed Two=6",
		'CASE',
		/* [3202] */
		"Title Position",
		'DWRD',
		/* [3203] */
		"None=0",
		'CASE',
		/* [3204] */
		"Default=1",
		'CASE',
		/* [3205] */
		"Top Right=2",
		'CASE',
		/* [3206] */
		"Top Left Out=3",
		'CASE',
		/* [3207] */
		"Top Right Out=4",
		'CASE',
		/* [3208] */
		"Center Top Out=5",
		'CASE',
		/* [3209] */
		"Center Top=6",
		'CASE',
		/* [3210] */
		"Center Inside=7",
		'CASE',
		/* [3211] */
		"Center Top Inside=8",
		'CASE',
		/* [3212] */
		"Center Bottom Inside=9",
		'CASE',
		/* [3213] */
		"Center Bottom=10",
		'CASE',
		/* [3214] */
		"Center Bottom Out=11",
		'CASE',
		/* [3215] */
		"",
		'KEYE',
		/* [3216] */
		"gbgp",
		'KEYB',
		/* [3217] */
		"Pane data",
		'DVDR',
		/* [3218] */
		"Pane ID",
		'DLNG',
		/* [3219] */
		"Width",
		'DWRD',
		/* [3220] */
		"Height",
		'DWRD',
		/* [3221] */
		"Visible?",
		'BFLG',
		/* [3222] */
		"Enabled?",
		'BFLG',
		/* [3223] */
		"Left side bound?",
		'BFLG',
		/* [3224] */
		"Top side bound?",
		'BFLG',
		/* [3225] */
		"Right side bound?",
		'BFLG',
		/* [3226] */
		"Bottom side bound?",
		'BFLG',
		/* [3227] */
		"Left in super image",
		'DLNG',
		/* [3228] */
		"Top in super image",
		'DLNG',
		/* [3229] */
		"User constant",
		'DLNG',
		/* [3230] */
		"Superview",
		'DLNG',
		/* [3231] */
		"Default=-1",
		'CASE',
		/* [3232] */
		"None=0",
		'CASE',
		/* [3233] */
		"View data",
		'DVDR',
		/* [3234] */
		"Image width",
		'DLNG',
		/* [3235] */
		"Image height",
		'DLNG',
		/* [3236] */
		"Horizontal scroll position",
		'DLNG',
		/* [3237] */
		"Vertical scroll position",
		'DLNG',
		/* [3238] */
		"Horizontal scroll unit",
		'DLNG',
		/* [3239] */
		"Vertical scroll unit",
		'DLNG',
		/* [3240] */
		"Reconcile overhang?",
		'WFLG',
		/* [3241] */
		"Box Data",
		'DVDR',
		/* [3242] */
		"Filler",
		'FBYT',
		/* [3243] */
		"Title",
		'PSTR',
		/* [3244] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [3245] */
		"System font=0",
		'CASE',
		/* [3246] */
		"Has Border",
		'BFLG',
		/* [3247] */
		"Border Style",
		'DWRD',
		/* [3248] */
		"None=0",
		'CASE',
		/* [3249] */
		"Plain=1",
		'CASE',
		/* [3250] */
		"Bezel=2",
		'CASE',
		/* [3251] */
		"Recessed One=3",
		'CASE',
		/* [3252] */
		"Recessed Two=4",
		'CASE',
		/* [3253] */
		"Embossed One=5",
		'CASE',
		/* [3254] */
		"Embossed Two=6",
		'CASE',
		/* [3255] */
		"Title Position",
		'DWRD',
		/* [3256] */
		"None=0",
		'CASE',
		/* [3257] */
		"Default=1",
		'CASE',
		/* [3258] */
		"Top Right=2",
		'CASE',
		/* [3259] */
		"Top Left Out=3",
		'CASE',
		/* [3260] */
		"Top Right Out=4",
		'CASE',
		/* [3261] */
		"Center Top Out=5",
		'CASE',
		/* [3262] */
		"Center Top=6",
		'CASE',
		/* [3263] */
		"Center Inside=7",
		'CASE',
		/* [3264] */
		"Center Top Inside=8",
		'CASE',
		/* [3265] */
		"Center Bottom Inside=9",
		'CASE',
		/* [3266] */
		"Center Bottom=10",
		'CASE',
		/* [3267] */
		"Center Bottom Out=11",
		'CASE',
		/* [3268] */
		"",
		'KEYE',
		/* [3269] */
		"gcap",
		'KEYB',
		/* [3270] */
		"Pane data",
		'DVDR',
		/* [3271] */
		"Pane ID",
		'DLNG',
		/* [3272] */
		"Width",
		'DWRD',
		/* [3273] */
		"Height",
		'DWRD',
		/* [3274] */
		"Visible?",
		'BFLG',
		/* [3275] */
		"Enabled?",
		'BFLG',
		/* [3276] */
		"Left side bound?",
		'BFLG',
		/* [3277] */
		"Top side bound?",
		'BFLG',
		/* [3278] */
		"Right side bound?",
		'BFLG',
		/* [3279] */
		"Bottom side bound?",
		'BFLG',
		/* [3280] */
		"Left in super image",
		'DLNG',
		/* [3281] */
		"Top in super image",
		'DLNG',
		/* [3282] */
		"User constant",
		'DLNG',
		/* [3283] */
		"Superview",
		'DLNG',
		/* [3284] */
		"Default=-1",
		'CASE',
		/* [3285] */
		"None=0",
		'CASE',
		/* [3286] */
		"Caption data",
		'DVDR',
		/* [3287] */
		"Caption text",
		'PSTR',
		/* [3288] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [3289] */
		"",
		'KEYE',
		/* [3290] */
		"gswt",
		'KEYB',
		/* [3291] */
		"Pane data",
		'DVDR',
		/* [3292] */
		"Pane ID",
		'DLNG',
		/* [3293] */
		"Width",
		'DWRD',
		/* [3294] */
		"Height",
		'DWRD',
		/* [3295] */
		"Visible?",
		'BFLG',
		/* [3296] */
		"Enabled?",
		'BFLG',
		/* [3297] */
		"Left side bound?",
		'BFLG',
		/* [3298] */
		"Top side bound?",
		'BFLG',
		/* [3299] */
		"Right side bound?",
		'BFLG',
		/* [3300] */
		"Bottom side bound?",
		'BFLG',
		/* [3301] */
		"Left in super image",
		'DLNG',
		/* [3302] */
		"Top in super image",
		'DLNG',
		/* [3303] */
		"User constant",
		'DLNG',
		/* [3304] */
		"Superview",
		'DLNG',
		/* [3305] */
		"Default=-1",
		'CASE',
		/* [3306] */
		"None=0",
		'CASE',
		/* [3307] */
		"Color Swatch Data",
		'DVDR',
		/* [3308] */
		"Color",
		'COLR',
		/* [3309] */
		"",
		'KEYE',
		/* [3310] */
		"gdlb",
		'KEYB',
		/* [3311] */
		"Window data",
		'DVDR',
		/* [3312] */
		"'WIND' Resource ID",
		'RSID',
		/* [3313] */
		"Window behavior",
		'DWRD',
		/* [3314] */
		"Modal=0",
		'CASE',
		/* [3315] */
		"Floating=1",
		'CASE',
		/* [3316] */
		"Regular=2",
		'CASE',
		/* [3317] */
		"Layer",
		'LB03',
		/* [3318] */
		"Has close box?",
		'LBIT',
		/* [3319] */
		"Has title bar?",
		'LBIT',
		/* [3320] */
		"Is resizable?",
		'LBIT',
		/* [3321] */
		"Draw size box?",
		'LBIT',
		/* [3322] */
		"Is zoomable?",
		'LBIT',
		/* [3323] */
		"Visible after creation?",
		'LBIT',
		/* [3324] */
		"Enabled?",
		'LBIT',
		/* [3325] */
		"Can be target?",
		'LBIT',
		/* [3326] */
		"Get select click?",
		'LBIT',
		/* [3327] */
		"Hide when suspended?",
		'LBIT',
		/* [3328] */
		"Delayed selection?",
		'LBIT',
		/* [3329] */
		"Erase when updating?",
		'LBIT',
		/* [3330] */
		"Reserved",
		'LB17',
		/* [3331] */
		"Mininimum width",
		'DWRD',
		/* [3332] */
		"Minimum height",
		'DWRD',
		/* [3333] */
		"Maximum width",
		'DWRD',
		/* [3334] */
		"Any=-1",
		'CASE',
		/* [3335] */
		"Maximum height",
		'DWRD',
		/* [3336] */
		"Any=-1",
		'CASE',
		/* [3337] */
		"Standard state width",
		'DWRD',
		/* [3338] */
		"Default=-1",
		'CASE',
		/* [3339] */
		"Standard state height",
		'DWRD',
		/* [3340] */
		"Default=-1",
		'CASE',
		/* [3341] */
		"User constant",
		'DLNG',
		/* [3342] */
		"Dialog data",
		'DVDR',
		/* [3343] */
		"Default button ID",
		'DLNG',
		/* [3344] */
		"Cancel button ID",
		'DLNG',
		/* [3345] */
		"",
		'KEYE',
		/* [3346] */
		"gedt",
		'KEYB',
		/* [3347] */
		"Pane data",
		'DVDR',
		/* [3348] */
		"Pane ID",
		'DLNG',
		/* [3349] */
		"Width",
		'DWRD',
		/* [3350] */
		"Height",
		'DWRD',
		/* [3351] */
		"Visible?",
		'BFLG',
		/* [3352] */
		"Enabled?",
		'BFLG',
		/* [3353] */
		"Left side bound?",
		'BFLG',
		/* [3354] */
		"Top side bound?",
		'BFLG',
		/* [3355] */
		"Right side bound?",
		'BFLG',
		/* [3356] */
		"Bottom side bound?",
		'BFLG',
		/* [3357] */
		"Left in super image",
		'DLNG',
		/* [3358] */
		"Top in super image",
		'DLNG',
		/* [3359] */
		"User constant",
		'DLNG',
		/* [3360] */
		"Superview",
		'DLNG',
		/* [3361] */
		"Default=-1",
		'CASE',
		/* [3362] */
		"None=0",
		'CASE',
		/* [3363] */
		"Edit field data",
		'DVDR',
		/* [3364] */
		"Initial text",
		'PSTR',
		/* [3365] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [3366] */
		"System font=0",
		'CASE',
		/* [3367] */
		"Maximum text size",
		'DWRD',
		/* [3368] */
		"Has box around field?",
		'BBIT',
		/* [3369] */
		"Word wrap?",
		'BBIT',
		/* [3370] */
		"AutoScroll?",
		'BBIT',
		/* [3371] */
		"Text Buffering?",
		'BBIT',
		/* [3372] */
		"Outline Hilite?",
		'BBIT',
		/* [3373] */
		"Inline Input?",
		'BBIT',
		/* [3374] */
		"Use Text Services?",
		'BBIT',
		/* [3375] */
		"Reserved",
		'BBIT',
		/* [3376] */
		"Keystroke filter",
		'DBYT',
		/* [3377] */
		"None=0",
		'CASE',
		/* [3378] */
		"Integer=1",
		'CASE',
		/* [3379] */
		"Alphanumeric=2",
		'CASE',
		/* [3380] */
		"Printing char=3",
		'CASE',
		/* [3381] */
		"",
		'KEYE',
		/* [3382] */
		"gicn",
		'KEYB',
		/* [3383] */
		"Pane data",
		'DVDR',
		/* [3384] */
		"Pane ID",
		'DLNG',
		/* [3385] */
		"Width",
		'DWRD',
		/* [3386] */
		"Height",
		'DWRD',
		/* [3387] */
		"Visible?",
		'BFLG',
		/* [3388] */
		"Enabled?",
		'BFLG',
		/* [3389] */
		"Left side bound?",
		'BFLG',
		/* [3390] */
		"Top side bound?",
		'BFLG',
		/* [3391] */
		"Right side bound?",
		'BFLG',
		/* [3392] */
		"Bottom side bound?",
		'BFLG',
		/* [3393] */
		"Left in super image",
		'DLNG',
		/* [3394] */
		"Top in super image",
		'DLNG',
		/* [3395] */
		"User constant",
		'DLNG',
		/* [3396] */
		"Superview",
		'DLNG',
		/* [3397] */
		"Default=-1",
		'CASE',
		/* [3398] */
		"None=0",
		'CASE',
		/* [3399] */
		"Icon Suite Data",
		'DVDR',
		/* [3400] */
		"Icon Suite ('ICN#') ID",
		'RSID',
		/* [3401] */
		"Icon Size",
		'DWRD',
		/* [3402] */
		"None=0",
		'CASE',
		/* [3403] */
		"Mini=12",
		'CASE',
		/* [3404] */
		"Small=16",
		'CASE',
		/* [3405] */
		"Large=32",
		'CASE',
		/* [3406] */
		"Position",
		'DWRD',
		/* [3407] */
		"None=0",
		'CASE',
		/* [3408] */
		"Top Left=1",
		'CASE',
		/* [3409] */
		"Top Center=2",
		'CASE',
		/* [3410] */
		"Top Right=3",
		'CASE',
		/* [3411] */
		"Right Center=4",
		'CASE',
		/* [3412] */
		"Bottom Right=5",
		'CASE',
		/* [3413] */
		"Bottom Center=6",
		'CASE',
		/* [3414] */
		"Bottom Left=7",
		'CASE',
		/* [3415] */
		"Left Center=8",
		'CASE',
		/* [3416] */
		"Center=9",
		'CASE',
		/* [3417] */
		"",
		'KEYE',
		/* [3418] */
		"gpbx",
		'KEYB',
		/* [3419] */
		"Pane data",
		'DVDR',
		/* [3420] */
		"Pane ID",
		'DLNG',
		/* [3421] */
		"Width",
		'DWRD',
		/* [3422] */
		"Height",
		'DWRD',
		/* [3423] */
		"Visible?",
		'BFLG',
		/* [3424] */
		"Enabled?",
		'BFLG',
		/* [3425] */
		"Left side bound?",
		'BFLG',
		/* [3426] */
		"Top side bound?",
		'BFLG',
		/* [3427] */
		"Right side bound?",
		'BFLG',
		/* [3428] */
		"Bottom side bound?",
		'BFLG',
		/* [3429] */
		"Left in super image",
		'DLNG',
		/* [3430] */
		"Top in super image",
		'DLNG',
		/* [3431] */
		"User constant",
		'DLNG',
		/* [3432] */
		"Superview",
		'DLNG',
		/* [3433] */
		"Default=-1",
		'CASE',
		/* [3434] */
		"None=0",
		'CASE',
		/* [3435] */
		"View data",
		'DVDR',
		/* [3436] */
		"Image width",
		'DLNG',
		/* [3437] */
		"Image height",
		'DLNG',
		/* [3438] */
		"Horizontal scroll position",
		'DLNG',
		/* [3439] */
		"Vertical scroll position",
		'DLNG',
		/* [3440] */
		"Horizontal scroll unit",
		'DLNG',
		/* [3441] */
		"Vertical scroll unit",
		'DLNG',
		/* [3442] */
		"Reconcile overhang?",
		'WFLG',
		/* [3443] */
		"Box Data",
		'DVDR',
		/* [3444] */
		"Title",
		'PSTR',
		/* [3445] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [3446] */
		"System font=0",
		'CASE',
		/* [3447] */
		"",
		'KEYE',
		/* [3448] */
		"gpgp",
		'KEYB',
		/* [3449] */
		"Pane data",
		'DVDR',
		/* [3450] */
		"Pane ID",
		'DLNG',
		/* [3451] */
		"Width",
		'DWRD',
		/* [3452] */
		"Height",
		'DWRD',
		/* [3453] */
		"Visible?",
		'BFLG',
		/* [3454] */
		"Enabled?",
		'BFLG',
		/* [3455] */
		"Left side bound?",
		'BFLG',
		/* [3456] */
		"Top side bound?",
		'BFLG',
		/* [3457] */
		"Right side bound?",
		'BFLG',
		/* [3458] */
		"Bottom side bound?",
		'BFLG',
		/* [3459] */
		"Left in super image",
		'DLNG',
		/* [3460] */
		"Top in super image",
		'DLNG',
		/* [3461] */
		"User constant",
		'DLNG',
		/* [3462] */
		"Superview",
		'DLNG',
		/* [3463] */
		"Default=-1",
		'CASE',
		/* [3464] */
		"None=0",
		'CASE',
		/* [3465] */
		"View data",
		'DVDR',
		/* [3466] */
		"Image width",
		'DLNG',
		/* [3467] */
		"Image height",
		'DLNG',
		/* [3468] */
		"Horizontal scroll position",
		'DLNG',
		/* [3469] */
		"Vertical scroll position",
		'DLNG',
		/* [3470] */
		"Horizontal scroll unit",
		'DLNG',
		/* [3471] */
		"Vertical scroll unit",
		'DLNG',
		/* [3472] */
		"Reconcile overhang?",
		'WFLG',
		/* [3473] */
		"Box Data",
		'DVDR',
		/* [3474] */
		"Title",
		'PSTR',
		/* [3475] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [3476] */
		"System font=0",
		'CASE',
		/* [3477] */
		"",
		'KEYE',
		/* [3478] */
		"gsbx",
		'KEYB',
		/* [3479] */
		"Pane data",
		'DVDR',
		/* [3480] */
		"Pane ID",
		'DLNG',
		/* [3481] */
		"Width",
		'DWRD',
		/* [3482] */
		"Height",
		'DWRD',
		/* [3483] */
		"Visible?",
		'BFLG',
		/* [3484] */
		"Enabled?",
		'BFLG',
		/* [3485] */
		"Left side bound?",
		'BFLG',
		/* [3486] */
		"Top side bound?",
		'BFLG',
		/* [3487] */
		"Right side bound?",
		'BFLG',
		/* [3488] */
		"Bottom side bound?",
		'BFLG',
		/* [3489] */
		"Left in super image",
		'DLNG',
		/* [3490] */
		"Top in super image",
		'DLNG',
		/* [3491] */
		"User constant",
		'DLNG',
		/* [3492] */
		"Superview",
		'DLNG',
		/* [3493] */
		"Default=-1",
		'CASE',
		/* [3494] */
		"None=0",
		'CASE',
		/* [3495] */
		"View data",
		'DVDR',
		/* [3496] */
		"Image width",
		'DLNG',
		/* [3497] */
		"Image height",
		'DLNG',
		/* [3498] */
		"Horizontal scroll position",
		'DLNG',
		/* [3499] */
		"Vertical scroll position",
		'DLNG',
		/* [3500] */
		"Horizontal scroll unit",
		'DLNG',
		/* [3501] */
		"Vertical scroll unit",
		'DLNG',
		/* [3502] */
		"Reconcile overhang?",
		'WFLG',
		/* [3503] */
		"Box Data",
		'DVDR',
		/* [3504] */
		"Title",
		'PSTR',
		/* [3505] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [3506] */
		"System font=0",
		'CASE',
		/* [3507] */
		"",
		'KEYE',
		/* [3508] */
		"gsgp",
		'KEYB',
		/* [3509] */
		"Pane data",
		'DVDR',
		/* [3510] */
		"Pane ID",
		'DLNG',
		/* [3511] */
		"Width",
		'DWRD',
		/* [3512] */
		"Height",
		'DWRD',
		/* [3513] */
		"Visible?",
		'BFLG',
		/* [3514] */
		"Enabled?",
		'BFLG',
		/* [3515] */
		"Left side bound?",
		'BFLG',
		/* [3516] */
		"Top side bound?",
		'BFLG',
		/* [3517] */
		"Right side bound?",
		'BFLG',
		/* [3518] */
		"Bottom side bound?",
		'BFLG',
		/* [3519] */
		"Left in super image",
		'DLNG',
		/* [3520] */
		"Top in super image",
		'DLNG',
		/* [3521] */
		"User constant",
		'DLNG',
		/* [3522] */
		"Superview",
		'DLNG',
		/* [3523] */
		"Default=-1",
		'CASE',
		/* [3524] */
		"None=0",
		'CASE',
		/* [3525] */
		"View data",
		'DVDR',
		/* [3526] */
		"Image width",
		'DLNG',
		/* [3527] */
		"Image height",
		'DLNG',
		/* [3528] */
		"Horizontal scroll position",
		'DLNG',
		/* [3529] */
		"Vertical scroll position",
		'DLNG',
		/* [3530] */
		"Horizontal scroll unit",
		'DLNG',
		/* [3531] */
		"Vertical scroll unit",
		'DLNG',
		/* [3532] */
		"Reconcile overhang?",
		'WFLG',
		/* [3533] */
		"Box Data",
		'DVDR',
		/* [3534] */
		"Title",
		'PSTR',
		/* [3535] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [3536] */
		"System font=0",
		'CASE',
		/* [3537] */
		"",
		'KEYE',
		/* [3538] */
		"gsep",
		'KEYB',
		/* [3539] */
		"Pane data",
		'DVDR',
		/* [3540] */
		"Pane ID",
		'DLNG',
		/* [3541] */
		"Width",
		'DWRD',
		/* [3542] */
		"Height",
		'DWRD',
		/* [3543] */
		"Visible?",
		'BFLG',
		/* [3544] */
		"Enabled?",
		'BFLG',
		/* [3545] */
		"Left side bound?",
		'BFLG',
		/* [3546] */
		"Top side bound?",
		'BFLG',
		/* [3547] */
		"Right side bound?",
		'BFLG',
		/* [3548] */
		"Bottom side bound?",
		'BFLG',
		/* [3549] */
		"Left in super image",
		'DLNG',
		/* [3550] */
		"Top in super image",
		'DLNG',
		/* [3551] */
		"User constant",
		'DLNG',
		/* [3552] */
		"Superview",
		'DLNG',
		/* [3553] */
		"Default=-1",
		'CASE',
		/* [3554] */
		"None=0",
		'CASE',
		/* [3555] */
		"",
		'KEYE',
		/* [3556] */
		"gfbd",
		'KEYB',
		/* [3557] */
		"Pane data",
		'DVDR',
		/* [3558] */
		"Pane ID",
		'DLNG',
		/* [3559] */
		"Width",
		'DWRD',
		/* [3560] */
		"Height",
		'DWRD',
		/* [3561] */
		"Visible?",
		'BFLG',
		/* [3562] */
		"Enabled?",
		'BFLG',
		/* [3563] */
		"Left side bound?",
		'BFLG',
		/* [3564] */
		"Top side bound?",
		'BFLG',
		/* [3565] */
		"Right side bound?",
		'BFLG',
		/* [3566] */
		"Bottom side bound?",
		'BFLG',
		/* [3567] */
		"Left in super image",
		'DLNG',
		/* [3568] */
		"Top in super image",
		'DLNG',
		/* [3569] */
		"User constant",
		'DLNG',
		/* [3570] */
		"Superview",
		'DLNG',
		/* [3571] */
		"Default=-1",
		'CASE',
		/* [3572] */
		"None=0",
		'CASE',
		/* [3573] */
		"View data",
		'DVDR',
		/* [3574] */
		"Image width",
		'DLNG',
		/* [3575] */
		"Image height",
		'DLNG',
		/* [3576] */
		"Horizontal scroll position",
		'DLNG',
		/* [3577] */
		"Vertical scroll position",
		'DLNG',
		/* [3578] */
		"Horizontal scroll unit",
		'DLNG',
		/* [3579] */
		"Vertical scroll unit",
		'DLNG',
		/* [3580] */
		"Reconcile overhang?",
		'WFLG',
		/* [3581] */
		"Focus Border Data",
		'DVDR',
		/* [3582] */
		"Inset SubPane ID",
		'DLNG',
		/* [3583] */
		"Commander SubPane ID",
		'DLNG',
		/* [3584] */
		"Paint Face",
		'BFLG',
		/* [3585] */
		"Frame Inset",
		'BFLG',
		/* [3586] */
		"Notch Inset",
		'BFLG',
		/* [3587] */
		"Notch Face",
		'BFLG',
		/* [3588] */
		"Notch Width",
		'DWRD',
		/* [3589] */
		"Can Focus",
		'BFLG',
		/* [3590] */
		"Current Focus",
		'BFLG',
		/* [3591] */
		"",
		'KEYE',
		/* [3592] */
		"glar",
		'KEYB',
		/* [3593] */
		"Pane data",
		'DVDR',
		/* [3594] */
		"Pane ID",
		'DLNG',
		/* [3595] */
		"Width",
		'DWRD',
		/* [3596] */
		"Height",
		'DWRD',
		/* [3597] */
		"Visible?",
		'BFLG',
		/* [3598] */
		"Enabled?",
		'BFLG',
		/* [3599] */
		"Left side bound?",
		'BFLG',
		/* [3600] */
		"Top side bound?",
		'BFLG',
		/* [3601] */
		"Right side bound?",
		'BFLG',
		/* [3602] */
		"Bottom side bound?",
		'BFLG',
		/* [3603] */
		"Left in super image",
		'DLNG',
		/* [3604] */
		"Top in super image",
		'DLNG',
		/* [3605] */
		"User constant",
		'DLNG',
		/* [3606] */
		"Superview",
		'DLNG',
		/* [3607] */
		"Default=-1",
		'CASE',
		/* [3608] */
		"None=0",
		'CASE',
		/* [3609] */
		"Control data",
		'DVDR',
		/* [3610] */
		"Message when pushed",
		'DLNG',
		/* [3611] */
		"Initial value",
		'DLNG',
		/* [3612] */
		"Minimum value",
		'DLNG',
		/* [3613] */
		"Maximum value",
		'DLNG',
		/* [3614] */
		"Click Action",
		'DWRD',
		/* [3615] */
		"Single Click=1",
		'CASE',
		/* [3616] */
		"Delay Continuous=2",
		'CASE',
		/* [3617] */
		"Continuous=3",
		'CASE',
		/* [3618] */
		"Delay for Continuous",
		'DWRD',
		/* [3619] */
		"Delay for Value Change",
		'DWRD',
		/* [3620] */
		"",
		'KEYE',
		/* [3621] */
		"gtbp",
		'KEYB',
		/* [3622] */
		"Pane data",
		'DVDR',
		/* [3623] */
		"Pane ID",
		'DLNG',
		/* [3624] */
		"Width",
		'DWRD',
		/* [3625] */
		"Height",
		'DWRD',
		/* [3626] */
		"Visible?",
		'BFLG',
		/* [3627] */
		"Enabled?",
		'BFLG',
		/* [3628] */
		"Left side bound?",
		'BFLG',
		/* [3629] */
		"Top side bound?",
		'BFLG',
		/* [3630] */
		"Right side bound?",
		'BFLG',
		/* [3631] */
		"Bottom side bound?",
		'BFLG',
		/* [3632] */
		"Left in super image",
		'DLNG',
		/* [3633] */
		"Top in super image",
		'DLNG',
		/* [3634] */
		"User constant",
		'DLNG',
		/* [3635] */
		"Superview",
		'DLNG',
		/* [3636] */
		"Default=-1",
		'CASE',
		/* [3637] */
		"None=0",
		'CASE',
		/* [3638] */
		"View data",
		'DVDR',
		/* [3639] */
		"Image width",
		'DLNG',
		/* [3640] */
		"Image height",
		'DLNG',
		/* [3641] */
		"Horizontal scroll position",
		'DLNG',
		/* [3642] */
		"Vertical scroll position",
		'DLNG',
		/* [3643] */
		"Horizontal scroll unit",
		'DLNG',
		/* [3644] */
		"Vertical scroll unit",
		'DLNG',
		/* [3645] */
		"Reconcile overhang?",
		'WFLG',
		/* [3646] */
		"Tab Panel Data",
		'DVDR',
		/* [3647] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [3648] */
		"System font=0",
		'CASE',
		/* [3649] */
		"Panel Message",
		'DLNG',
		/* [3650] */
		"Count:",
		'OCNT',
		/* [3651] */
		"List of Initial items",
		'LSTC',
		/* [3652] */
		"Text",
		'PSTR',
		/* [3653] */
		"*****",
		'LSTE',
		/* [3654] */
		"Initial Selection",
		'DWRD',
		/* [3655] */
		"Has PlaceHolder",
		'BFLG',
		/* [3656] */
		"Position",
		'DWRD',
		/* [3657] */
		"None=0",
		'CASE',
		/* [3658] */
		"Top Left=1",
		'CASE',
		/* [3659] */
		"Top Center=2",
		'CASE',
		/* [3660] */
		"Top Right=3",
		'CASE',
		/* [3661] */
		"Right Center=4",
		'CASE',
		/* [3662] */
		"Bottom Right=5",
		'CASE',
		/* [3663] */
		"Bottom Center=6",
		'CASE',
		/* [3664] */
		"Bottom Left=7",
		'CASE',
		/* [3665] */
		"Left Center=8",
		'CASE',
		/* [3666] */
		"Center=9",
		'CASE',
		/* [3667] */
		"",
		'KEYE',
		/* [3668] */
		"whdr",
		'KEYB',
		/* [3669] */
		"Pane data",
		'DVDR',
		/* [3670] */
		"Pane ID",
		'DLNG',
		/* [3671] */
		"Width",
		'DWRD',
		/* [3672] */
		"Height",
		'DWRD',
		/* [3673] */
		"Visible?",
		'BFLG',
		/* [3674] */
		"Enabled?",
		'BFLG',
		/* [3675] */
		"Left side bound?",
		'BFLG',
		/* [3676] */
		"Top side bound?",
		'BFLG',
		/* [3677] */
		"Right side bound?",
		'BFLG',
		/* [3678] */
		"Bottom side bound?",
		'BFLG',
		/* [3679] */
		"Left in super image",
		'DLNG',
		/* [3680] */
		"Top in super image",
		'DLNG',
		/* [3681] */
		"User constant",
		'DLNG',
		/* [3682] */
		"Superview",
		'DLNG',
		/* [3683] */
		"Default=-1",
		'CASE',
		/* [3684] */
		"None=0",
		'CASE',
		/* [3685] */
		"View data",
		'DVDR',
		/* [3686] */
		"Image width",
		'DLNG',
		/* [3687] */
		"Image height",
		'DLNG',
		/* [3688] */
		"Horizontal scroll position",
		'DLNG',
		/* [3689] */
		"Vertical scroll position",
		'DLNG',
		/* [3690] */
		"Horizontal scroll unit",
		'DLNG',
		/* [3691] */
		"Vertical scroll unit",
		'DLNG',
		/* [3692] */
		"Reconcile overhang?",
		'WFLG',
		/* [3693] */
		"WindowHeader data",
		'DVDR',
		/* [3694] */
		"Has Adornment?",
		'BFLG',
		/* [3695] */
		"Has Bottom Divider?",
		'BFLG',
		/* [3696] */
		"",
		'KEYE',
		/* [3697] */
		"gdlg",
		'KEYB',
		/* [3698] */
		"Window data",
		'DVDR',
		/* [3699] */
		"'WIND' Resource ID",
		'RSID',
		/* [3700] */
		"Window behavior",
		'DWRD',
		/* [3701] */
		"Modal=0",
		'CASE',
		/* [3702] */
		"Floating=1",
		'CASE',
		/* [3703] */
		"Regular=2",
		'CASE',
		/* [3704] */
		"Layer",
		'LB03',
		/* [3705] */
		"Has close box?",
		'LBIT',
		/* [3706] */
		"Has title bar?",
		'LBIT',
		/* [3707] */
		"Is resizable?",
		'LBIT',
		/* [3708] */
		"Draw size box?",
		'LBIT',
		/* [3709] */
		"Is zoomable?",
		'LBIT',
		/* [3710] */
		"Visible after creation?",
		'LBIT',
		/* [3711] */
		"Enabled?",
		'LBIT',
		/* [3712] */
		"Can be target?",
		'LBIT',
		/* [3713] */
		"Get select click?",
		'LBIT',
		/* [3714] */
		"Hide when suspended?",
		'LBIT',
		/* [3715] */
		"Delayed selection?",
		'LBIT',
		/* [3716] */
		"Erase when updating?",
		'LBIT',
		/* [3717] */
		"Reserved",
		'LB17',
		/* [3718] */
		"Mininimum width",
		'DWRD',
		/* [3719] */
		"Minimum height",
		'DWRD',
		/* [3720] */
		"Maximum width",
		'DWRD',
		/* [3721] */
		"Any=-1",
		'CASE',
		/* [3722] */
		"Maximum height",
		'DWRD',
		/* [3723] */
		"Any=-1",
		'CASE',
		/* [3724] */
		"Standard state width",
		'DWRD',
		/* [3725] */
		"Default=-1",
		'CASE',
		/* [3726] */
		"Standard state height",
		'DWRD',
		/* [3727] */
		"Default=-1",
		'CASE',
		/* [3728] */
		"User constant",
		'DLNG',
		/* [3729] */
		"Dialog data",
		'DVDR',
		/* [3730] */
		"Default button ID",
		'DLNG',
		/* [3731] */
		"Cancel button ID",
		'DLNG',
		/* [3732] */
		"",
		'KEYE',
		/* [3733] */
		"pctl",
		'KEYB',
		/* [3734] */
		"Pane data",
		'DVDR',
		/* [3735] */
		"Pane ID",
		'DLNG',
		/* [3736] */
		"Width",
		'DWRD',
		/* [3737] */
		"Height",
		'DWRD',
		/* [3738] */
		"Visible?",
		'BFLG',
		/* [3739] */
		"Enabled?",
		'BFLG',
		/* [3740] */
		"Left side bound?",
		'BFLG',
		/* [3741] */
		"Top side bound?",
		'BFLG',
		/* [3742] */
		"Right side bound?",
		'BFLG',
		/* [3743] */
		"Bottom side bound?",
		'BFLG',
		/* [3744] */
		"Left in super image",
		'DLNG',
		/* [3745] */
		"Top in super image",
		'DLNG',
		/* [3746] */
		"User constant",
		'DLNG',
		/* [3747] */
		"Superview",
		'DLNG',
		/* [3748] */
		"Default=-1",
		'CASE',
		/* [3749] */
		"None=0",
		'CASE',
		/* [3750] */
		"View data",
		'DVDR',
		/* [3751] */
		"Image width",
		'DLNG',
		/* [3752] */
		"Image height",
		'DLNG',
		/* [3753] */
		"Horizontal scroll position",
		'DLNG',
		/* [3754] */
		"Vertical scroll position",
		'DLNG',
		/* [3755] */
		"Horizontal scroll unit",
		'DLNG',
		/* [3756] */
		"Vertical scroll unit",
		'DLNG',
		/* [3757] */
		"Reconcile overhang?",
		'WFLG',
		/* [3758] */
		"PageController data",
		'DVDR',
		/* [3759] */
		"Text traits ('Txtr') ID",
		'RSID',
		/* [3760] */
		"Controller Message",
		'DLNG',
		/* [3761] */
		"String List ('STR#') ID",
		'RSID',
		/* [3762] */
		"Initial Selection",
		'DWRD',
		/* [3763] */
		"Background Color",
		'COLR',
		/* [3764] */
		"Face Color",
		'COLR',
		/* [3765] */
		"Pushed Text Color",
		'COLR',
		/* [3766] */
		"Has Grouped Arrows?",
		'BFLG',
		/* [3767] */
		"",
		'KEYE',
		/* [3768] */
		"cswt",
		'KEYB',
		/* [3769] */
		"Pane data",
		'DVDR',
		/* [3770] */
		"Pane ID",
		'DLNG',
		/* [3771] */
		"Width",
		'DWRD',
		/* [3772] */
		"Height",
		'DWRD',
		/* [3773] */
		"Visible?",
		'BFLG',
		/* [3774] */
		"Enabled?",
		'BFLG',
		/* [3775] */
		"Left side bound?",
		'BFLG',
		/* [3776] */
		"Top side bound?",
		'BFLG',
		/* [3777] */
		"Right side bound?",
		'BFLG',
		/* [3778] */
		"Bottom side bound?",
		'BFLG',
		/* [3779] */
		"Left in super image",
		'DLNG',
		/* [3780] */
		"Top in super image",
		'DLNG',
		/* [3781] */
		"User constant",
		'DLNG',
		/* [3782] */
		"Superview",
		'DLNG',
		/* [3783] */
		"Default=-1",
		'CASE',
		/* [3784] */
		"None=0",
		'CASE',
		/* [3785] */
		"ColorSwatch data",
		'DVDR',
		/* [3786] */
		"Value changed message",
		'DLNG',
		/* [3787] */
		"Unused=0",
		'CASE',
		/* [3788] */
		"Initial value",
		'DLNG',
		/* [3789] */
		"Unused=0",
		'CASE',
		/* [3790] */
		"Minimum value",
		'DLNG',
		/* [3791] */
		"Unused=0",
		'CASE',
		/* [3792] */
		"Maximum value",
		'DLNG',
		/* [3793] */
		"Unused=0",
		'CASE',
		/* [3794] */
		"Initial Color",
		'COLR',
		/* [3795] */
		"Prompt String",
		'PSTR',
		/* [3796] */
		"",
		'KEYE',
		/* [3797] */
		"null",
		'KEYB',
		/* [3798] */
		"",
		'KEYE',
		/* [3799] */
		"",
		'KEYB',
		/* [3800] */
		"Unknown data",
		'HEXD',
		/* [3801] */
		"",
		'KEYE',
		/* [3802] */
		"",
		'SKPE',
		/* [3803] */
		"",
		'KEYE',
		/* [3804] */
		"begs",
		'KEYB',
		/* [3805] */
		"",
		'KEYE',
		/* [3806] */
		"ends",
		'KEYB',
		/* [3807] */
		"",
		'KEYE',
		/* [3808] */
		"user",
		'KEYB',
		/* [3809] */
		"SuperClass ID for next object",
		'TNAM',
		/* [3810] */
		"",
		'KEYE',
		/* [3811] */
		"dopl",
		'KEYB',
		/* [3812] */
		"Class ID for next object",
		'TNAM',
		/* [3813] */
		"",
		'KEYE',
		/* [3814] */
		"end.",
		'KEYB',
		/* [3815] */
		"This must be last object type in list",
		'DVDR',
		/* [3816] */
		"",
		'KEYE',
		/* [3817] */
		"comm",
		'KEYB',
		/* [3818] */
		"Comment Data",
		'LHEX',
		/* [3819] */
		"",
		'KEYE',
		/* [3820] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1283, "PPRO") {
	{	/* array: 9 elements */
		/* [1] */
		"\"Fetch\" resource template",
		'DVDR',
		/* [2] */
		"Applications",
		'LSTB',
		/* [3] */
		"Type",
		'TNAM',
		/* [4] */
		"Creator",
		'TNAM',
		/* [5] */
		"App creator",
		'TNAM',
		/* [6] */
		"Enabled",
		'BOOL',
		/* [7] */
		"File description",
		'CSTR',
		/* [8] */
		"App name",
		'CSTR',
		/* [9] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1284, "PRC0") {
	{	/* array: 37 elements */
		/* [1] */
		"iPrVersion",
		'DWRD',
		/* [2] */
		"prInfo.iDev",
		'HWRD',
		/* [3] */
		"prInfo.iVRes",
		'DWRD',
		/* [4] */
		"prInfo.iHRes",
		'DWRD',
		/* [5] */
		"prInfo.rPage",
		'RECT',
		/* [6] */
		"rPaper",
		'RECT',
		/* [7] */
		"prStl.wDev",
		'HWRD',
		/* [8] */
		"prStl.iPageV",
		'DWRD',
		/* [9] */
		"prStl.iPageH",
		'DWRD',
		/* [10] */
		"prStl.bPort",
		'DBYT',
		/* [11] */
		"prStl.feed",
		'DBYT',
		/* [12] */
		"prIPT.iDev",
		'HWRD',
		/* [13] */
		"prIPT.iVRes",
		'DWRD',
		/* [14] */
		"prIPT.iHRes",
		'DWRD',
		/* [15] */
		"prIPT.rPage",
		'RECT',
		/* [16] */
		"prXI.iRowBytes",
		'DWRD',
		/* [17] */
		"prXI.iBandV",
		'DWRD',
		/* [18] */
		"prXI.iBandH",
		'DWRD',
		/* [19] */
		"prXI.iDevBytes",
		'DWRD',
		/* [20] */
		"prXI.iBands",
		'DWRD',
		/* [21] */
		"prXI.bPatScale",
		'DBYT',
		/* [22] */
		"prXI.bUlThick",
		'DBYT',
		/* [23] */
		"prXI.UlOffset",
		'DBYT',
		/* [24] */
		"prXI.UlShadow",
		'DBYT',
		/* [25] */
		"prXI.scan",
		'DBYT',
		/* [26] */
		"prXI.bXInfoX",
		'DBYT',
		/* [27] */
		"prJob.iFstPage",
		'DWRD',
		/* [28] */
		"prJob.iLstPage",
		'DWRD',
		/* [29] */
		"prJob.iCopies",
		'DWRD',
		/* [30] */
		"prJob.bJDocLoop",
		'DBYT',
		/* [31] */
		"prJob.fFromUsr",
		'DBYT',
		/* [32] */
		"prJob.pIdleProc",
		'HLNG',
		/* [33] */
		"prJob.pFileName",
		'HLNG',
		/* [34] */
		"prJob.iFileVol",
		'DWRD',
		/* [35] */
		"prJob.bFileVers",
		'DBYT',
		/* [36] */
		"prJob.bJobX",
		'DBYT',
		/* [37] */
		"printX",
		'H026'
	}
};

resource 'TMPL' (1285, "PRC3") {
	{	/* array: 20 elements */
		/* [1] */
		"Number of Buttons",
		'DWRD',
		/* [2] */
		"Button 1 height",
		'DWRD',
		/* [3] */
		"Button 1 width",
		'DWRD',
		/* [4] */
		"Button 2 height",
		'DWRD',
		/* [5] */
		"Button 2 width",
		'DWRD',
		/* [6] */
		"Button 3 height",
		'DWRD',
		/* [7] */
		"Button 3 width",
		'DWRD',
		/* [8] */
		"Button 4 height",
		'DWRD',
		/* [9] */
		"Button 4 width",
		'DWRD',
		/* [10] */
		"Button 5 height",
		'DWRD',
		/* [11] */
		"Button 5 width",
		'DWRD',
		/* [12] */
		"Button 6 height",
		'DWRD',
		/* [13] */
		"Button 6 width",
		'DWRD',
		/* [14] */
		"Button 1 name",
		'PSTR',
		/* [15] */
		"Button 2 name",
		'PSTR',
		/* [16] */
		"Button 3 name",
		'PSTR',
		/* [17] */
		"Button 4 name",
		'PSTR',
		/* [18] */
		"Button 5 name",
		'PSTR',
		/* [19] */
		"Button 6 name",
		'PSTR',
		/* [20] */
		"Data",
		'HEXD'
	}
};

resource 'TMPL' (1286, "PREC") {
	{	/* array: 138 elements */
		/* [1] */
		"Type of resource",
		'KRID',
		/* [2] */
		"Print record=0",
		'CASE',
		/* [3] */
		"Paper types=3",
		'CASE',
		/* [4] */
		"Buttons=4",
		'CASE',
		/* [5] */
		"Calculated paper types=5",
		'CASE',
		/* [6] */
		"Don't know=102",
		'CASE',
		/* [7] */
		"PostScript Dictionary=103",
		'CASE',
		/* [8] */
		"Fonts=104",
		'CASE',
		/* [9] */
		"Font substitutions=105",
		'CASE',
		/* [10] */
		"Message strings=109",
		'CASE',
		/* [11] */
		"0",
		'KEYB',
		/* [12] */
		"iPrVersion",
		'DWRD',
		/* [13] */
		"Printer information",
		'DVDR',
		/* [14] */
		"iDev",
		'HWRD',
		/* [15] */
		"Vertical resolution in dots/inch",
		'DWRD',
		/* [16] */
		"Horizontal resolution in dots/inch",
		'DWRD',
		/* [17] */
		"Bounds of printable page",
		'RECT',
		/* [18] */
		"Physical pape size",
		'RECT',
		/* [19] */
		"Additional device information",
		'DVDR',
		/* [20] */
		"wDev",
		'HBYT',
		/* [21] */
		"ImageWriter=1",
		'CASE',
		/* [22] */
		"LaserWriter=3",
		'CASE',
		/* [23] */
		"Used internally",
		'HBYT',
		/* [24] */
		"Printer info PT",
		'DVDR',
		/* [25] */
		"iPageV",
		'DWRD',
		/* [26] */
		"iPageH",
		'DWRD',
		/* [27] */
		"bPort",
		'DBYT',
		/* [28] */
		"feed",
		'DBYT',
		/* [29] */
		"iDev",
		'HWRD',
		/* [30] */
		"iVRes",
		'DWRD',
		/* [31] */
		"iHRes",
		'DWRD',
		/* [32] */
		"rPage",
		'RECT',
		/* [33] */
		"Additional device information",
		'DVDR',
		/* [34] */
		"iRowBytes",
		'DWRD',
		/* [35] */
		"iBandV",
		'DWRD',
		/* [36] */
		"iBandH",
		'DWRD',
		/* [37] */
		"iDevBytes",
		'DWRD',
		/* [38] */
		"iBands",
		'DWRD',
		/* [39] */
		"bPatScale",
		'DBYT',
		/* [40] */
		"bUlThick",
		'DBYT',
		/* [41] */
		"UlOffset",
		'DBYT',
		/* [42] */
		"UlShadow",
		'DBYT',
		/* [43] */
		"scan",
		'DBYT',
		/* [44] */
		"bXInfoX",
		'DBYT',
		/* [45] */
		"Print job subrecord",
		'DVDR',
		/* [46] */
		"First page to print",
		'DWRD',
		/* [47] */
		"Last page to print",
		'DWRD',
		/* [48] */
		"Number of copies",
		'DWRD',
		/* [49] */
		"Printing method",
		'DBYT',
		/* [50] */
		"Draft=0",
		'CASE',
		/* [51] */
		"Spool=1",
		'CASE',
		/* [52] */
		"fFromUsr",
		'DBYT',
		/* [53] */
		"Background idling procedure",
		'HLNG',
		/* [54] */
		"File name pointer",
		'HLNG',
		/* [55] */
		"Spool file volume reference number",
		'DWRD',
		/* [56] */
		"Spool file version",
		'DBYT',
		/* [57] */
		"bJobX",
		'DBYT',
		/* [58] */
		"printX",
		'H026',
		/* [59] */
		"",
		'KEYE',
		/* [60] */
		"3",
		'KEYB',
		/* [61] */
		"Should be 6 paper types and names",
		'DVDR',
		/* [62] */
		"Count:",
		'OCNT',
		/* [63] */
		"List of Paper types",
		'LSTC',
		/* [64] */
		"(bottom,left) in 1/120th inch",
		'PNT ',
		/* [65] */
		"*****",
		'LSTE',
		/* [66] */
		"Paper type 1 name",
		'PSTR',
		/* [67] */
		"Paper type 2 name",
		'PSTR',
		/* [68] */
		"Paper type 3 name",
		'PSTR',
		/* [69] */
		"Paper type 4 name",
		'PSTR',
		/* [70] */
		"Paper type 5 name",
		'PSTR',
		/* [71] */
		"Paper type 6 name",
		'PSTR',
		/* [72] */
		"",
		'KEYE',
		/* [73] */
		"4",
		'KEYB',
		/* [74] */
		"Number of Buttons",
		'DWRD',
		/* [75] */
		"Button 1 Height",
		'DWRD',
		/* [76] */
		"Button 1 Width",
		'DWRD',
		/* [77] */
		"Button 2 Height",
		'DWRD',
		/* [78] */
		"Button 2 Width",
		'DWRD',
		/* [79] */
		"Button 3 Height",
		'DWRD',
		/* [80] */
		"Button 3 Width",
		'DWRD',
		/* [81] */
		"Button 4 Height",
		'DWRD',
		/* [82] */
		"Button 4 Width",
		'DWRD',
		/* [83] */
		"Button 5 Height",
		'DWRD',
		/* [84] */
		"Button 5 Width",
		'DWRD',
		/* [85] */
		"Button 6 Height",
		'DWRD',
		/* [86] */
		"Button 6 Width",
		'DWRD',
		/* [87] */
		"Button 1 Name",
		'PSTR',
		/* [88] */
		"Button 2 Name",
		'PSTR',
		/* [89] */
		"Button 3 Name",
		'PSTR',
		/* [90] */
		"Button 4 Name",
		'PSTR',
		/* [91] */
		"Button 5 Name",
		'PSTR',
		/* [92] */
		"Button 6 Name",
		'PSTR',
		/* [93] */
		"",
		'KEYE',
		/* [94] */
		"5",
		'KEYB',
		/* [95] */
		"Should be 6 paper types and names",
		'DVDR',
		/* [96] */
		"Count:",
		'OCNT',
		/* [97] */
		"List of Paper types",
		'LSTC',
		/* [98] */
		"(bottom,left) in 1/120th inch",
		'PNT ',
		/* [99] */
		"How to calculate",
		'WFLG',
		/* [100] */
		"Emulation=0",
		'CASE',
		/* [101] */
		"Theoretical=1",
		'CASE',
		/* [102] */
		"*****",
		'LSTE',
		/* [103] */
		"Paper type 1 name",
		'PSTR',
		/* [104] */
		"Paper type 2 name",
		'PSTR',
		/* [105] */
		"Paper type 3 name",
		'PSTR',
		/* [106] */
		"Paper type 4 name",
		'PSTR',
		/* [107] */
		"Paper type 5 name",
		'PSTR',
		/* [108] */
		"Paper type 6 name",
		'PSTR',
		/* [109] */
		"",
		'KEYE',
		/* [110] */
		"102",
		'KEYB',
		/* [111] */
		"Unknown data",
		'HEXS',
		/* [112] */
		"",
		'KEYE',
		/* [113] */
		"103",
		'KEYB',
		/* [114] */
		"Definitions",
		'TXTS',
		/* [115] */
		"",
		'KEYE',
		/* [116] */
		"104",
		'KEYB',
		/* [117] */
		"Count:",
		'OCNT',
		/* [118] */
		"List of Entries",
		'LSTC',
		/* [119] */
		"Field 1",
		'DWRD',
		/* [120] */
		"Field 2",
		'DWRD',
		/* [121] */
		"Font name",
		'ESTR',
		/* [122] */
		"*****",
		'LSTE',
		/* [123] */
		"",
		'KEYE',
		/* [124] */
		"105",
		'KEYB',
		/* [125] */
		"Count:",
		'OCNT',
		/* [126] */
		"List of Substibutions",
		'LSTC',
		/* [127] */
		"Macintosh font name",
		'PSTR',
		/* [128] */
		"Laserwriter font name",
		'PSTR',
		/* [129] */
		"Align",
		'AWRD',
		/* [130] */
		"Field 1",
		'DWRD',
		/* [131] */
		"Field 2",
		'HWRD',
		/* [132] */
		"*****",
		'LSTE',
		/* [133] */
		"",
		'KEYE',
		/* [134] */
		"109",
		'KEYB',
		/* [135] */
		"\"\"\"\"\"",
		'LSTB',
		/* [136] */
		"String",
		'PSTR',
		/* [137] */
		"*****",
		'LSTE',
		/* [138] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1287, "PRF2") {
	{	/* array: 16 elements */
		/* [1] */
		"Create papToDisk file",
		'BBIT',
		/* [2] */
		"Merge setpagedevice calls for improved p"
		"erformance when possible",
		'BBIT',
		/* [3] */
		"Wrap PPD code to avoid errors",
		'BBIT',
		/* [4] */
		"Generate log file for download manager e"
		"rrors and warnings",
		'BBIT',
		/* [5] */
		"Ignore Fonts in printer when printing",
		'BBIT',
		/* [6] */
		"Always generate Type 1 versions of TrueT"
		"ype fonts",
		'BBIT',
		/* [7] */
		"Okay to use OpenTransport PAP",
		'BBIT',
		/* [8] */
		"Reserved",
		'BBIT',
		/* [9] */
		"Reserved",
		'BBIT',
		/* [10] */
		"Reserved",
		'BBIT',
		/* [11] */
		"Reserved",
		'BBIT',
		/* [12] */
		"Reserved",
		'BBIT',
		/* [13] */
		"Reserved",
		'BBIT',
		/* [14] */
		"Reserved",
		'BBIT',
		/* [15] */
		"Reserved",
		'BBIT',
		/* [16] */
		"Reserved",
		'BBIT'
	}
};

resource 'TMPL' (1288, "PRFS") {
	{	/* array: 32 elements */
		/* [1] */
		"Full PPD dialog",
		'BBIT',
		/* [2] */
		"Never send binary data",
		'BBIT',
		/* [3] */
		"Create papToDisk file",
		'BBIT',
		/* [4] */
		"Enable sending compressed data",
		'BBIT',
		/* [5] */
		"Allow print to file (except EPS with pre"
		"view) in background",
		'BBIT',
		/* [6] */
		"Always use 2 pass for print to file",
		'BBIT',
		/* [7] */
		"Do 2 pass foreground printing to printer",
		'BBIT',
		/* [8] */
		"Merge setpagedevice calls for improved p"
		"erformance when possible",
		'BBIT',
		/* [9] */
		"Allow rgb to grayscale conversion on hos"
		"t",
		'BBIT',
		/* [10] */
		"Force DSC compliant PS generation",
		'BBIT',
		/* [11] */
		"Show PostScript Header panel",
		'BBIT',
		/* [12] */
		"Enable Transparent and Masked Image Supp"
		"ort",
		'BBIT',
		/* [13] */
		"Show MediaType in Feed popup",
		'BBIT',
		/* [14] */
		"Wrap PPD code to avoid errors",
		'BBIT',
		/* [15] */
		"Use Symbol font for Euro currency symbol",
		'BBIT',
		/* [16] */
		"Ignore Fonts in Printer When Printing",
		'BBIT',
		/* [17] */
		"Always generate Type 1 Versions of TrueT"
		"ype Fonts",
		'BBIT',
		/* [18] */
		"Use Appearance Manager",
		'BBIT',
		/* [19] */
		"Show Fonts Panel",
		'BBIT',
		/* [20] */
		"Reserved",
		'BBIT',
		/* [21] */
		"Reserved",
		'BBIT',
		/* [22] */
		"Reserved",
		'BBIT',
		/* [23] */
		"Reserved",
		'BBIT',
		/* [24] */
		"Reserved",
		'BBIT',
		/* [25] */
		"Reserved",
		'BBIT',
		/* [26] */
		"Reserved",
		'BBIT',
		/* [27] */
		"Reserved",
		'BBIT',
		/* [28] */
		"Reserved",
		'BBIT',
		/* [29] */
		"Reserved",
		'BBIT',
		/* [30] */
		"Reserved",
		'BBIT',
		/* [31] */
		"Reserved",
		'BBIT',
		/* [32] */
		"Reserved",
		'BBIT'
	}
};

resource 'TMPL' (1289, "prop") {
	{	/* array: 7 elements */
		/* [1] */
		"Enable quality",
		'BFLG',
		/* [2] */
		"Enable paper feed",
		'BFLG',
		/* [3] */
		"Quality",
		'DBYT',
		/* [4] */
		"Rough=0",
		'CASE',
		/* [5] */
		"Final=1",
		'CASE',
		/* [6] */
		"Current=2",
		'CASE',
		/* [7] */
		"Alert before resetting quality",
		'BFLG'
	}
};

resource 'TMPL' (1290, "proz") {
	{	/* array: 3 elements */
		/* [1] */
		"",
		'LSTB',
		/* [2] */
		"Decimal long",
		'DLNG',
		/* [3] */
		"",
		'LSTE'
	}
};

resource 'TMPL' (1291, "PSAP") {
	{	/* array: 1 elements */
		/* [1] */
		"String",
		'WSTR'
	}
};

resource 'TMPL' (1292, "PSLD") {
	{	/* array: 15 elements */
		/* [1] */
		"Picture resource ID",
		'DWRD',
		/* [2] */
		"Masking resource ID",
		'DWRD',
		/* [3] */
		"Number of sliders",
		'DWRD',
		/* [4] */
		"Slider offset",
		'DWRD',
		/* [5] */
		"Options",
		'HLNG',
		/* [6] */
		"Snap to center - 0x00000001",
		'DVDR',
		/* [7] */
		"Dual sided - 0x00000002",
		'DVDR',
		/* [8] */
		"Reversed - 0x00000004",
		'DVDR',
		/* [9] */
		"Thumb inactive rect",
		'RECT',
		/* [10] */
		"Thumb active rect",
		'RECT',
		/* [11] */
		"Thumb pressed rect",
		'RECT',
		/* [12] */
		"Slider rect",
		'RECT',
		/* [13] */
		"Slider drag rect",
		'RECT',
		/* [14] */
		"Fixed left size",
		'DBYT',
		/* [15] */
		"Fixed right size",
		'DBYT'
	}
};

resource 'TMPL' (1293, "pslt") {
	{	/* array: 17 elements */
		/* [1] */
		"Slot orientation is as seen from the fro"
		"nt of the machine",
		'DVDR',
		/* [2] */
		"Count:",
		'OCNT',
		/* [3] */
		"Orientation",
		'DWRD',
		/* [4] */
		"Horizontal form & ascending slots left t"
		"o right=0",
		'CASE',
		/* [5] */
		"Horizontal form & descending slots left "
		"to right=1",
		'CASE',
		/* [6] */
		"Vertical form & ascending slots bottom t"
		"o top=2",
		'CASE',
		/* [7] */
		"Vertical form & descending slots bottom "
		"to top=3",
		'CASE',
		/* [8] */
		"Vertical form & ascending slots top to b"
		"ottom=4",
		'CASE',
		/* [9] */
		"Vertical form & descending slots top to "
		"bottom=5",
		'CASE',
		/* [10] */
		"Horizontal form & ascending slots left t"
		"o right=6",
		'CASE',
		/* [11] */
		"Horizontal form & descending slots left "
		"to right=7",
		'CASE',
		/* [12] */
		"Flags",
		'HLNG',
		/* [13] */
		"Nubus slots",
		'LSTC',
		/* [14] */
		"Nubus slot",
		'DWRD',
		/* [15] */
		"Pseudo-slot",
		'DWRD',
		/* [16] */
		"Closest to the side of box=1",
		'CASE',
		/* [17] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1294, "PTFM") {
	{	/* array: 14 elements */
		/* [1] */
		"Default pane",
		'TNAM',
		/* [2] */
		"Count:",
		'LCNT',
		/* [3] */
		"Entries",
		'LSTC',
		/* [4] */
		"Resource type",
		'TNAM',
		/* [5] */
		"Flags",
		'DLNG',
		/* [6] */
		"Width",
		'DLNG',
		/* [7] */
		"Height",
		'DLNG',
		/* [8] */
		"Depth",
		'DLNG',
		/* [9] */
		"Row bytes",
		'DLNG',
		/* [10] */
		"Sample pane ID",
		'TNAM',
		/* [11] */
		"Mask offset",
		'DLNG',
		/* [12] */
		"Mask row bytes",
		'DLNG',
		/* [13] */
		"Mask sample pane ID",
		'TNAM',
		/* [14] */
		"",
		'LSTE'
	}
};

resource 'TMPL' (1295, "ptyp") {
	{	/* array: 46 elements */
		/* [1] */
		"Paper type name",
		'ESTR',
		/* [2] */
		"Page bounds",
		'DVDR',
		/* [3] */
		"Left",
		'DLNG',
		/* [4] */
		"Top",
		'DLNG',
		/* [5] */
		"Right",
		'DLNG',
		/* [6] */
		"Bottom",
		'DLNG',
		/* [7] */
		"Paper bounds",
		'DVDR',
		/* [8] */
		"Left",
		'DLNG',
		/* [9] */
		"Top",
		'DLNG',
		/* [10] */
		"Right",
		'DLNG',
		/* [11] */
		"Bottom",
		'DLNG',
		/* [12] */
		"Paper's base type",
		'DLNG',
		/* [13] */
		"US Letter=1",
		'CASE',
		/* [14] */
		"US Legal=2",
		'CASE',
		/* [15] */
		"A4 Letter=3",
		'CASE',
		/* [16] */
		"B5 Letter=4",
		'CASE',
		/* [17] */
		"Tabloid=5",
		'CASE',
		/* [18] */
		"Unknown=0",
		'CASE',
		/* [19] */
		"Creator",
		'TNAM',
		/* [20] */
		"Unit of measure",
		'LB08',
		/* [21] */
		"Picas=0",
		'CASE',
		/* [22] */
		"Millimeters=1",
		'CASE',
		/* [23] */
		"Inches=2",
		'CASE',
		/* [24] */
		"Paper style",
		'LB02',
		/* [25] */
		"New=1",
		'CASE',
		/* [26] */
		"Old=2",
		'CASE',
		/* [27] */
		"Old and new=3",
		'CASE',
		/* [28] */
		"Fixed print area",
		'LBIT',
		/* [29] */
		"Is default paper type",
		'LBIT',
		/* [30] */
		"Is default base paper type",
		'LBIT',
		/* [31] */
		"Reserved",
		'LB19',
		/* [32] */
		"Embedded collection",
		'DVDR',
		/* [33] */
		"Count:",
		'LCNT',
		/* [34] */
		"List of Items",
		'LSTC',
		/* [35] */
		"Tag",
		'TNAM',
		/* [36] */
		"ID",
		'DLNG',
		/* [37] */
		"Printing collection=-28672",
		'CASE',
		/* [38] */
		"Defined attribute bits",
		'DVDR',
		/* [39] */
		"Locked?",
		'WBIT',
		/* [40] */
		"Persistent?",
		'WBIT',
		/* [41] */
		"Reserved",
		'WB14',
		/* [42] */
		"User attribute bits",
		'DVDR',
		/* [43] */
		"Reserved",
		'WB16',
		/* [44] */
		"Text",
		'WSTR',
		/* [45] */
		"Align",
		'AWRD',
		/* [46] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1296, "PTYP") {
	{	/* array: 279 elements */
		/* [1] */
		"Template for Constructor CW10",
		'DVDR',
		/* [2] */
		"Version Number",
		'DWRD',
		/* [3] */
		"CW10=1",
		'CASE',
		/* [4] */
		"*****",
		'LSTB',
		/* [5] */
		"Object type",
		'KTYP',
		/* [6] */
		"Object data=objd",
		'CASE',
		/* [7] */
		"Begin sub-object list=begs",
		'CASE',
		/* [8] */
		"End sub-object list=ends",
		'CASE',
		/* [9] */
		"User object=user",
		'CASE',
		/* [10] */
		"Class alias=dopl",
		'CASE',
		/* [11] */
		"End of list=end.",
		'CASE',
		/* [12] */
		"objd",
		'KEYB',
		/* [13] */
		"Number of bytes in following data",
		'LSIZ',
		/* [14] */
		"Data type",
		'KTYP',
		/* [15] */
		"Object=obj ",
		'CASE',
		/* [16] */
		"Pilot Type Entry=vlte",
		'CASE',
		/* [17] */
		"Integer attribute=intv",
		'CASE',
		/* [18] */
		"Labelled integer attribute=labi",
		'CASE',
		/* [19] */
		"Min/max integer attribute=mimx",
		'CASE',
		/* [20] */
		"Res list attribute=resl",
		'CASE',
		/* [21] */
		"Resource Reference Attribute=rerf",
		'CASE',
		/* [22] */
		"Toolbox boolean attribute=tbxb",
		'CASE',
		/* [23] */
		"String attribute=pstr",
		'CASE',
		/* [24] */
		"Font string attribute=fstr",
		'CASE',
		/* [25] */
		"RGB color attribute=rgbc",
		'CASE',
		/* [26] */
		"Container attribute=cont",
		'CASE',
		/* [27] */
		"List attribute=list",
		'CASE',
		/* [28] */
		"Bitfield container attribute=bitf",
		'CASE',
		/* [29] */
		"Value label=labl",
		'CASE',
		/* [30] */
		"Statement=stat",
		'CASE',
		/* [31] */
		"Argument=arg ",
		'CASE',
		/* [32] */
		"Null=null",
		'CASE',
		/* [33] */
		"obj ",
		'KEYB',
		/* [34] */
		"",
		'KEYE',
		/* [35] */
		"vlte",
		'KEYB',
		/* [36] */
		"VETypeEntry data",
		'DVDR',
		/* [37] */
		"Class name",
		'PSTR',
		/* [38] */
		"Icon ID",
		'DWRD',
		/* [39] */
		"Abstract class?",
		'BFLG',
		/* [40] */
		"Class ID",
		'TNAM',
		/* [41] */
		"Parent class ID",
		'TNAM',
		/* [42] */
		"Default width",
		'DWRD',
		/* [43] */
		"Default height",
		'DWRD',
		/* [44] */
		"Must be root?",
		'BFLG',
		/* [45] */
		"",
		'KEYE',
		/* [46] */
		"intv",
		'KEYB',
		/* [47] */
		"DMAttribute data",
		'DVDR',
		/* [48] */
		"Attribute title",
		'PSTR',
		/* [49] */
		"Attribute key",
		'TNAM',
		/* [50] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [51] */
		"Write to stream?",
		'BFLG',
		/* [52] */
		"Stream selector",
		'TNAM',
		/* [53] */
		"DMIntegerAttribute data",
		'DVDR',
		/* [54] */
		"Default value",
		'DLNG',
		/* [55] */
		"Value size (bits)",
		'UWRD',
		/* [56] */
		"Signed integer?",
		'BFLG',
		/* [57] */
		"Can be text value?",
		'BFLG',
		/* [58] */
		"Always is text value?",
		'BFLG',
		/* [59] */
		"",
		'KEYE',
		/* [60] */
		"labi",
		'KEYB',
		/* [61] */
		"DMAttribute data",
		'DVDR',
		/* [62] */
		"Attribute title",
		'PSTR',
		/* [63] */
		"Attribute key",
		'TNAM',
		/* [64] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [65] */
		"Write to stream?",
		'BFLG',
		/* [66] */
		"Stream selector",
		'TNAM',
		/* [67] */
		"DMIntegerAttribute data",
		'DVDR',
		/* [68] */
		"Default value",
		'DLNG',
		/* [69] */
		"Value size (bits)",
		'UWRD',
		/* [70] */
		"Signed integer?",
		'BFLG',
		/* [71] */
		"Can be text value?",
		'BFLG',
		/* [72] */
		"Always is text value?",
		'BFLG',
		/* [73] */
		"DMLabelledIntegerAttribute data",
		'DVDR',
		/* [74] */
		"Labels only?",
		'BFLG',
		/* [75] */
		"",
		'KEYE',
		/* [76] */
		"mimx",
		'KEYB',
		/* [77] */
		"DMAttribute data",
		'DVDR',
		/* [78] */
		"Attribute title",
		'PSTR',
		/* [79] */
		"Attribute key",
		'TNAM',
		/* [80] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [81] */
		"Write to stream?",
		'BFLG',
		/* [82] */
		"Stream selector",
		'TNAM',
		/* [83] */
		"DMIntegerAttribute data",
		'DVDR',
		/* [84] */
		"Default value",
		'DLNG',
		/* [85] */
		"Value size (bits)",
		'UWRD',
		/* [86] */
		"Signed integer?",
		'BFLG',
		/* [87] */
		"Can be text value?",
		'BFLG',
		/* [88] */
		"Always is text value?",
		'BFLG',
		/* [89] */
		"DMMinMaxIntegerAttribute data",
		'DVDR',
		/* [90] */
		"Minimum value",
		'DLNG',
		/* [91] */
		"Maximum value",
		'DLNG',
		/* [92] */
		"",
		'KEYE',
		/* [93] */
		"resl",
		'KEYB',
		/* [94] */
		"DMAttribute data",
		'DVDR',
		/* [95] */
		"Attribute title",
		'PSTR',
		/* [96] */
		"Attribute key",
		'TNAM',
		/* [97] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [98] */
		"Write to stream?",
		'BFLG',
		/* [99] */
		"Stream selector",
		'TNAM',
		/* [100] */
		"DMIntegerAttribute data",
		'DVDR',
		/* [101] */
		"Default value",
		'DLNG',
		/* [102] */
		"Value size (bits)",
		'UWRD',
		/* [103] */
		"Signed integer?",
		'BFLG',
		/* [104] */
		"Can be text value?",
		'BFLG',
		/* [105] */
		"Always is text value?",
		'BFLG',
		/* [106] */
		"DMLabelledIntegerAttribute data",
		'DVDR',
		/* [107] */
		"Labels only?",
		'BFLG',
		/* [108] */
		"DMResListAttribute data",
		'DVDR',
		/* [109] */
		"Resource type",
		'TNAM',
		/* [110] */
		"",
		'KEYE',
		/* [111] */
		"rerf",
		'KEYB',
		/* [112] */
		"DMAttribute data",
		'DVDR',
		/* [113] */
		"Attribute title",
		'PSTR',
		/* [114] */
		"Attribute key",
		'TNAM',
		/* [115] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [116] */
		"Write to stream?",
		'BFLG',
		/* [117] */
		"Stream selector",
		'TNAM',
		/* [118] */
		"DMIntegerAttribute data",
		'DVDR',
		/* [119] */
		"Default value",
		'DLNG',
		/* [120] */
		"Value size (bits)",
		'UWRD',
		/* [121] */
		"Signed integer?",
		'BFLG',
		/* [122] */
		"Can be text value?",
		'BFLG',
		/* [123] */
		"Always is text value?",
		'BFLG',
		/* [124] */
		"DMResourceRefAttribute data",
		'DVDR',
		/* [125] */
		"Resource Type",
		'TNAM',
		/* [126] */
		"",
		'KEYE',
		/* [127] */
		"tbxb",
		'KEYB',
		/* [128] */
		"DMAttribute data",
		'DVDR',
		/* [129] */
		"Attribute title",
		'PSTR',
		/* [130] */
		"Attribute key",
		'TNAM',
		/* [131] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [132] */
		"Write to stream?",
		'BFLG',
		/* [133] */
		"Stream selector",
		'TNAM',
		/* [134] */
		"DMIntegerAttribute data",
		'DVDR',
		/* [135] */
		"Default value",
		'DLNG',
		/* [136] */
		"Value size (bits)",
		'UWRD',
		/* [137] */
		"Signed integer?",
		'BFLG',
		/* [138] */
		"Can be text value?",
		'BFLG',
		/* [139] */
		"Always is text value?",
		'BFLG',
		/* [140] */
		"Number of bytes (1 or 2)",
		'DWRD',
		/* [141] */
		"",
		'KEYE',
		/* [142] */
		"pstr",
		'KEYB',
		/* [143] */
		"DMAttribute data",
		'DVDR',
		/* [144] */
		"Attribute title",
		'PSTR',
		/* [145] */
		"Attribute key",
		'TNAM',
		/* [146] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [147] */
		"Write to stream?",
		'BFLG',
		/* [148] */
		"Stream selector",
		'TNAM',
		/* [149] */
		"DMStringAttribute data",
		'DVDR',
		/* [150] */
		"Default value",
		'PSTR',
		/* [151] */
		"Maximum length (characters)",
		'UWRD',
		/* [152] */
		"Even padded?",
		'BFLG',
		/* [153] */
		"unused",
		'BB04',
		/* [154] */
		"Needs Hex",
		'BB01',
		/* [155] */
		"Accept CR",
		'BB01',
		/* [156] */
		"Write as C String?",
		'BB01',
		/* [157] */
		"Odd padded?",
		'BB01',
		/* [158] */
		"",
		'KEYE',
		/* [159] */
		"fstr",
		'KEYB',
		/* [160] */
		"DMAttribute data",
		'DVDR',
		/* [161] */
		"Attribute title",
		'PSTR',
		/* [162] */
		"Attribute key",
		'TNAM',
		/* [163] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [164] */
		"Write to stream?",
		'BFLG',
		/* [165] */
		"Stream selector",
		'TNAM',
		/* [166] */
		"DMStringAttribute data",
		'DVDR',
		/* [167] */
		"Default value",
		'PSTR',
		/* [168] */
		"Maximum length (characters)",
		'UWRD',
		/* [169] */
		"Even padded?",
		'BFLG',
		/* [170] */
		"unused",
		'BB06',
		/* [171] */
		"Write as C String?",
		'BB01',
		/* [172] */
		"Odd padded?",
		'BB01',
		/* [173] */
		"DMFontStringAttribute data",
		'DVDR',
		/* [174] */
		"Default font number",
		'DWRD',
		/* [175] */
		"Write font number?",
		'BFLG',
		/* [176] */
		"Include system font?",
		'BFLG',
		/* [177] */
		"Include application font?",
		'BFLG',
		/* [178] */
		"Include hidden fonts?",
		'BFLG',
		/* [179] */
		"",
		'KEYE',
		/* [180] */
		"rgbc",
		'KEYB',
		/* [181] */
		"DMAttribute data",
		'DVDR',
		/* [182] */
		"Attribute title",
		'PSTR',
		/* [183] */
		"Attribute key",
		'TNAM',
		/* [184] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [185] */
		"Write to stream?",
		'BFLG',
		/* [186] */
		"Stream selector",
		'TNAM',
		/* [187] */
		"DMRGBColorAttribute data",
		'DVDR',
		/* [188] */
		"Default value",
		'COLR',
		/* [189] */
		"",
		'KEYE',
		/* [190] */
		"cont",
		'KEYB',
		/* [191] */
		"DMAttribute data",
		'DVDR',
		/* [192] */
		"Attribute title",
		'PSTR',
		/* [193] */
		"Attribute key",
		'TNAM',
		/* [194] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [195] */
		"Write to stream?",
		'BFLG',
		/* [196] */
		"Stream selector",
		'TNAM',
		/* [197] */
		"DMContainerAttribute data",
		'DVDR',
		/* [198] */
		"Is subobject list?",
		'BFLG',
		/* [199] */
		"Member class ID",
		'TNAM',
		/* [200] */
		"",
		'KEYE',
		/* [201] */
		"list",
		'KEYB',
		/* [202] */
		"DMAttribute data",
		'DVDR',
		/* [203] */
		"Attribute title",
		'PSTR',
		/* [204] */
		"Attribute key",
		'TNAM',
		/* [205] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [206] */
		"Write to stream?",
		'BFLG',
		/* [207] */
		"Stream selector",
		'TNAM',
		/* [208] */
		"DMContainerAttribute data",
		'DVDR',
		/* [209] */
		"Is subobject list?",
		'BFLG',
		/* [210] */
		"Member class ID",
		'TNAM',
		/* [211] */
		"DMListAttribute data",
		'DVDR',
		/* [212] */
		"Subitem title",
		'PSTR',
		/* [213] */
		"Number of bytes for count",
		'DLNG',
		/* [214] */
		"unused",
		'BB06',
		/* [215] */
		"Zero based display?",
		'BB01',
		/* [216] */
		"Zero-based count?",
		'BB01',
		/* [217] */
		"",
		'KEYE',
		/* [218] */
		"bitf",
		'KEYB',
		/* [219] */
		"DMAttribute data",
		'DVDR',
		/* [220] */
		"Attribute title",
		'PSTR',
		/* [221] */
		"Attribute key",
		'TNAM',
		/* [222] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [223] */
		"Write to stream?",
		'BFLG',
		/* [224] */
		"Stream selector",
		'TNAM',
		/* [225] */
		"DMContainerAttribute data",
		'DVDR',
		/* [226] */
		"Is subobject list?",
		'BFLG',
		/* [227] */
		"Member class ID",
		'TNAM',
		/* [228] */
		"DMBitfieldAttribute data",
		'DVDR',
		/* [229] */
		"Bitfield size (bytes)",
		'UWRD',
		/* [230] */
		"",
		'KEYE',
		/* [231] */
		"labl",
		'KEYB',
		/* [232] */
		"Value",
		'DLNG',
		/* [233] */
		"Label",
		'PSTR',
		/* [234] */
		"",
		'KEYE',
		/* [235] */
		"stat",
		'KEYB',
		/* [236] */
		"DMAttribute data",
		'DVDR',
		/* [237] */
		"Attribute title",
		'PSTR',
		/* [238] */
		"Attribute key",
		'TNAM',
		/* [239] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [240] */
		"Write to stream?",
		'BFLG',
		/* [241] */
		"Stream selector",
		'TNAM',
		/* [242] */
		"DMContainerAttribute data",
		'DVDR',
		/* [243] */
		"Is subobject list?",
		'BFLG',
		/* [244] */
		"Member class ID",
		'TNAM',
		/* [245] */
		"PJStatementAttribute data",
		'DVDR',
		/* [246] */
		"UseKeyForTitle",
		'BFLG',
		/* [247] */
		"",
		'KEYE',
		/* [248] */
		"arg ",
		'KEYB',
		/* [249] */
		"DMAttribute data",
		'DVDR',
		/* [250] */
		"Attribute title",
		'PSTR',
		/* [251] */
		"Attribute key",
		'TNAM',
		/* [252] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [253] */
		"Write to stream?",
		'BFLG',
		/* [254] */
		"Stream selector",
		'TNAM',
		/* [255] */
		"PJArgumentAttribute data",
		'DVDR',
		/* [256] */
		"Is Quoted",
		'BFLG',
		/* [257] */
		"Is Boolean",
		'BFLG',
		/* [258] */
		"",
		'KEYE',
		/* [259] */
		"null",
		'KEYB',
		/* [260] */
		"",
		'KEYE',
		/* [261] */
		"",
		'KEYB',
		/* [262] */
		"Unknown data",
		'HEXD',
		/* [263] */
		"",
		'KEYE',
		/* [264] */
		"",
		'SKPE',
		/* [265] */
		"",
		'KEYE',
		/* [266] */
		"begs",
		'KEYB',
		/* [267] */
		"",
		'KEYE',
		/* [268] */
		"ends",
		'KEYB',
		/* [269] */
		"",
		'KEYE',
		/* [270] */
		"user",
		'KEYB',
		/* [271] */
		"SuperClass ID for next object",
		'TNAM',
		/* [272] */
		"",
		'KEYE',
		/* [273] */
		"dopl",
		'KEYB',
		/* [274] */
		"Class ID for next object",
		'TNAM',
		/* [275] */
		"",
		'KEYE',
		/* [276] */
		"end.",
		'KEYB',
		/* [277] */
		"This must be last object type in list",
		'DVDR',
		/* [278] */
		"",
		'KEYE',
		/* [279] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1297, "puf!") {
	{	/* array: 4 elements */
		/* [1] */
		"",
		'LSTB',
		/* [2] */
		"Decimal byte",
		'DBYT',
		/* [3] */
		"Pascal string",
		'PSTR',
		/* [4] */
		"",
		'LSTE'
	}
};

resource 'TMPL' (1298, "qrsc") {
	{	/* array: 13 elements */
		/* [1] */
		"Version",
		'DWRD',
		/* [2] */
		"'qdef' resource ID",
		'RSID',
		/* [3] */
		"Host, user etc. 'STR#' ID",
		'RSID',
		/* [4] */
		"Current query",
		'DWRD',
		/* [5] */
		"Count:",
		'OCNT',
		/* [6] */
		"List of Queries",
		'LSTC',
		/* [7] */
		"'wstr' resource ID",
		'RSID',
		/* [8] */
		"*****",
		'LSTE',
		/* [9] */
		"Count:",
		'OCNT',
		/* [10] */
		"List of Resources",
		'LSTC',
		/* [11] */
		"Resource type",
		'TNAM',
		/* [12] */
		"Resource ID",
		'DWRD',
		/* [13] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1299, "ramr") {
	{	/* array: 7 elements */
		/* [1] */
		"Amt to indent 1st colum/title",
		'DWRD',
		/* [2] */
		"RAM location title width",
		'DWRD',
		/* [3] */
		"RAM size title width",
		'DWRD',
		/* [4] */
		"RAM type title width",
		'DWRD',
		/* [5] */
		"RAM location data width",
		'DWRD',
		/* [6] */
		"RAM size data width",
		'DWRD',
		/* [7] */
		"RAM type data width",
		'DWRD'
	}
};

resource 'TMPL' (1300, "rdes") {
	{	/* array: 31 elements */
		/* [1] */
		"Go Mixed Mode Trap",
		'HWRD',
		/* [2] */
		"Version",
		'HBYT',
		/* [3] */
		"Unused",
		'BBIT',
		/* [4] */
		"Unused",
		'BBIT',
		/* [5] */
		"Unused",
		'BBIT',
		/* [6] */
		"Unused",
		'BBIT',
		/* [7] */
		"Unused",
		'BBIT',
		/* [8] */
		"Unused",
		'BBIT',
		/* [9] */
		"Unused",
		'BBIT',
		/* [10] */
		"Selectors are indexable",
		'BBIT',
		/* [11] */
		"Reserved",
		'FLNG',
		/* [12] */
		"Reserved",
		'FBYT',
		/* [13] */
		"Selector Info",
		'HBYT',
		/* [14] */
		"Routine Count",
		'DWRD',
		/* [15] */
		"Proc info (binary long int)",
		'DLNG',
		/* [16] */
		"Reserved",
		'FBYT',
		/* [17] */
		"ISA",
		'HBYT',
		/* [18] */
		"Filler byte",
		'FBYT',
		/* [19] */
		"Unused",
		'BBIT',
		/* [20] */
		"Unused",
		'BBIT',
		/* [21] */
		"Unused",
		'BBIT',
		/* [22] */
		"Routine is dispatched default",
		'BBIT',
		/* [23] */
		"Dont pass selector",
		'BBIT',
		/* [24] */
		"Use native ISA",
		'BBIT',
		/* [25] */
		"Fragment needs preparing",
		'BBIT',
		/* [26] */
		"Proc descriptor is relative",
		'BBIT',
		/* [27] */
		"Proc descriptor",
		'DLNG',
		/* [28] */
		"Reserved4",
		'FLNG',
		/* [29] */
		"Selector",
		'DLNG',
		/* [30] */
		"Alignment",
		'ALNG',
		/* [31] */
		"Beginning of Power PC code",
		'HEXD'
	}
};

resource 'TMPL' (1301, "rdpf") {
	{	/* array: 4 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"List of script elements",
		'LSTC',
		/* [3] */
		"String",
		'PSTR',
		/* [4] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1302, "rdws") {
	{	/* array: 1 elements */
		/* [1] */
		"String",
		'WSTR'
	}
};

resource 'TMPL' (1303, "RECT") {
	{	/* array: 1 elements */
		/* [1] */
		"Rectangle",
		'RECT'
	}
};

resource 'TMPL' (1304, "RES!") {
	{	/* array: 2 elements */
		/* [1] */
		"\"Resurrection\" resource format",
		'DVDR',
		/* [2] */
		"Type name",
		'PSTR'
	}
};

resource 'TMPL' (1305, "RES#") {
	{	/* array: 5 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"List of Resources",
		'LSTC',
		/* [3] */
		"Resource type",
		'TNAM',
		/* [4] */
		"Resource ID",
		'RSID',
		/* [5] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1306, "resf") {
	{	/* array: 10 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"Families",
		'LSTC',
		/* [3] */
		"Family Name",
		'PSTR',
		/* [4] */
		"",
		'AWRD',
		/* [5] */
		"Count:",
		'OCNT',
		/* [6] */
		"Fonts",
		'LSTC',
		/* [7] */
		"Point size",
		'DWRD',
		/* [8] */
		"Style",
		'DWRD',
		/* [9] */
		"-----",
		'LSTE',
		/* [10] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1307, "resl") {
	{	/* array: 11 elements */
		/* [1] */
		"Range type",
		'DWRD',
		/* [2] */
		"Usual=1",
		'CASE',
		/* [3] */
		"Min X resolution (dots/inch)",
		'DWRD',
		/* [4] */
		"Max X resolution (dots/inch)",
		'DWRD',
		/* [5] */
		"Min Y resolution (dots/inch)",
		'DWRD',
		/* [6] */
		"Max Y resolution (dots/inch)",
		'DWRD',
		/* [7] */
		"Count:",
		'OCNT',
		/* [8] */
		"List of Resolutions",
		'LSTC',
		/* [9] */
		"Y resolution (dots/inch)",
		'DWRD',
		/* [10] */
		"X resolution (dots/inch)",
		'DWRD',
		/* [11] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1308, "rgb ") {
	{	/* array: 1 elements */
		/* [1] */
		"Color",
		'COLR'
	}
};

resource 'TMPL' (1309, "RID#") {
	{	/* array: 4 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"Resources array",
		'LSTC',
		/* [3] */
		"Resource ID",
		'DWRD',
		/* [4] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1310, "RidL") {
	{	/* array: 4 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"Pane IDs list",
		'LSTC',
		/* [3] */
		"Pane ID",
		'DLNG',
		/* [4] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1311, "RMAP") {
	{	/* array: 8 elements */
		/* [1] */
		"MapTo type",
		'TNAM',
		/* [2] */
		"Just editor?",
		'BOOL',
		/* [3] */
		"Exception count",
		'OCNT',
		/* [4] */
		"Exceptions",
		'LSTC',
		/* [5] */
		"Resource ID",
		'DWRD',
		/* [6] */
		"Map to type",
		'TNAM',
		/* [7] */
		"Just editor?",
		'BOOL',
		/* [8] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1312, "ropt") {
	{	/* array: 28 elements */
		/* [1] */
		"Start page 'wstr' ID",
		'RSID',
		/* [2] */
		"Form feed 'wstr' ID",
		'RSID',
		/* [3] */
		"Forward line feed",
		'DVDR',
		/* [4] */
		"Maximum value",
		'DWRD',
		/* [5] */
		"Number type",
		'DWRD',
		/* [6] */
		"Skip number, send strings only=0",
		'CASE',
		/* [7] */
		"Direct (pad with 0's and send as hex)=1",
		'CASE',
		/* [8] */
		"Convert to ASCII and pad character=2",
		'CASE',
		/* [9] */
		"Minimum width (in chars)",
		'DWRD',
		/* [10] */
		"Pad character",
		'CHAR',
		/* [11] */
		"Space= ",
		'CASE',
		/* [12] */
		"Zero=0",
		'CASE',
		/* [13] */
		"Filler",
		'FBYT',
		/* [14] */
		"Prefix string",
		'P020',
		/* [15] */
		"Postfix string",
		'P020',
		/* [16] */
		"Reverse line feed",
		'DVDR',
		/* [17] */
		"Maximum value",
		'DWRD',
		/* [18] */
		"Number type",
		'DWRD',
		/* [19] */
		"Skip number, send strings only=0",
		'CASE',
		/* [20] */
		"Direct (pad with 0's and send as hex)=1",
		'CASE',
		/* [21] */
		"Convert to ASCII and pad character=2",
		'CASE',
		/* [22] */
		"Minimum width (in chars)",
		'DWRD',
		/* [23] */
		"Pad character",
		'CHAR',
		/* [24] */
		"Space= ",
		'CASE',
		/* [25] */
		"Zero=0",
		'CASE',
		/* [26] */
		"Filler",
		'FBYT',
		/* [27] */
		"Prefix string",
		'P020',
		/* [28] */
		"Postfix string",
		'P020'
	}
};

resource 'TMPL' (1313, "rout") {
	{	/* array: 133 elements */
		/* [1] */
		"Array for folder routing",
		'LSTB',
		/* [2] */
		"Creator",
		'TNAM',
		/* [3] */
		"default=0",
		'CASE',
		/* [4] */
		"File type",
		'TNAM',
		/* [5] */
		"default=0",
		'CASE',
		/* [6] */
		"Target folder",
		'TNAM',
		/* [7] */
		"default=macs",
		'CASE',
		/* [8] */
		"Destination folder",
		'TNAM',
		/* [9] */
		"ALMLocations=fall",
		'CASE',
		/* [10] */
		"ALMModules=walk",
		'CASE',
		/* [11] */
		"ALMPreferences=trip",
		'CASE',
		/* [12] */
		"Appearance=appr",
		'CASE',
		/* [13] */
		"AppleExtras=aex’",
		'CASE',
		/* [14] */
		"AppleMenu=amnu",
		'CASE',
		/* [15] */
		"AppleShareAuthentication=auth",
		'CASE',
		/* [16] */
		"AppleShareSupport=shar",
		'CASE',
		/* [17] */
		"ApplicationSupport=asup",
		'CASE',
		/* [18] */
		"Applications=apps",
		'CASE',
		/* [19] */
		"Assistants=ast’",
		'CASE',
		/* [20] */
		"AudioAlertSounds=alrt",
		'CASE',
		/* [21] */
		"AudioComponents=acmp",
		'CASE',
		/* [22] */
		"AudioPlugIns=aplg",
		'CASE',
		/* [23] */
		"AudioSoundBanks=bank",
		'CASE',
		/* [24] */
		"AudioSounds=asnd",
		'CASE',
		/* [25] */
		"AudioSupport=adio",
		'CASE',
		/* [26] */
		"CachedData=cach",
		'CASE',
		/* [27] */
		"CarbonLibrary=carb",
		'CASE',
		/* [28] */
		"ChewableItems=flnt",
		'CASE',
		/* [29] */
		"ClassicDesktop=sdsk",
		'CASE',
		/* [30] */
		"ColorSync=sync",
		'CASE',
		/* [31] */
		"ColorSyncCMM=ccmm",
		'CASE',
		/* [32] */
		"ColorSyncProfiles=prof",
		'CASE',
		/* [33] */
		"ColorSyncScripting=cscr",
		'CASE',
		/* [34] */
		"Components=cmpd",
		'CASE',
		/* [35] */
		"ContextualMenuItems=cmnu",
		'CASE',
		/* [36] */
		"ControlPanel=ctrl",
		'CASE',
		/* [37] */
		"ControlPanelDisabled=ctrD",
		'CASE',
		/* [38] */
		"ControlStripModules=sdev",
		'CASE',
		/* [39] */
		"CoreServices=csrv",
		'CASE',
		/* [40] */
		"CurrentUser=cusr",
		'CASE',
		/* [41] */
		"CurrentUserRemote=rusr",
		'CASE',
		/* [42] */
		"Desktop=desk",
		'CASE',
		/* [43] */
		"DesktopPictures=dtp’",
		'CASE',
		/* [44] */
		"Developer=devf",
		'CASE',
		/* [45] */
		"DeveloperDocs=ddoc",
		'CASE',
		/* [46] */
		"DeveloperHelp=devh",
		'CASE',
		/* [47] */
		"DirectoryServices=dsrv",
		'CASE',
		/* [48] */
		"DirectoryServicesPlugIns=dplg",
		'CASE',
		/* [49] */
		"DisplayExtensions=dspl",
		'CASE',
		/* [50] */
		"Documentation=info",
		'CASE',
		/* [51] */
		"Documents=docs",
		'CASE',
		/* [52] */
		"DomainLibrary=dlib",
		'CASE',
		/* [53] */
		"DomainTopLevel=dtop",
		'CASE',
		/* [54] */
		"Editors=oded",
		'CASE',
		/* [55] */
		"Extension=extn",
		'CASE',
		/* [56] */
		"ExtensionDisabled=extD",
		'CASE',
		/* [57] */
		"Favorites=favs",
		'CASE',
		/* [58] */
		"FileSystemSupport=fsys",
		'CASE',
		/* [59] */
		"FindByContent=fbcf",
		'CASE',
		/* [60] */
		"FindByContentPlugins=fbcp",
		'CASE',
		/* [61] */
		"FindSupport=fnds",
		'CASE',
		/* [62] */
		"FolderActions=fasf",
		'CASE',
		/* [63] */
		"Fonts=font",
		'CASE',
		/* [64] */
		"Frameworks=fram",
		'CASE',
		/* [65] */
		"GenEditors=’edi",
		'CASE',
		/* [66] */
		"Help=’hlp",
		'CASE',
		/* [67] */
		"ISSDownloads=issd",
		'CASE',
		/* [68] */
		"InstallerLogs=ilgf",
		'CASE',
		/* [69] */
		"InstallerReceipts=rcpt",
		'CASE',
		/* [70] */
		"Internet=int’",
		'CASE',
		/* [71] */
		"InternetPlugIn=’net",
		'CASE',
		/* [72] */
		"InternetSearchSites=issf",
		'CASE',
		/* [73] */
		"InternetSites=site",
		'CASE',
		/* [74] */
		"KernelExtensions=kext",
		'CASE',
		/* [75] */
		"Keychain=kchn",
		'CASE',
		/* [76] */
		"LauncherItems=laun",
		'CASE',
		/* [77] */
		"Locales=’loc",
		'CASE',
		/* [78] */
		"MIDIDrivers=midi",
		'CASE',
		/* [79] */
		"MacOSReadMes=mor’",
		'CASE',
		/* [80] */
		"ModemScripts=’mod",
		'CASE',
		/* [81] */
		"MovieDocuments=mdoc",
		'CASE',
		/* [82] */
		"Multiprocessing=mpxf",
		'CASE',
		/* [83] */
		"MusicDocuments=µdoc",
		'CASE',
		/* [84] */
		"OpenDoc=odod",
		'CASE',
		/* [85] */
		"OpenDocEditors=’odf",
		'CASE',
		/* [86] */
		"OpenDocLibraries=odlb",
		'CASE',
		/* [87] */
		"OpenDocShellPlugIns=odsp",
		'CASE',
		/* [88] */
		"PictureDocuments=pdoc",
		'CASE',
		/* [89] */
		"Preferences=pref",
		'CASE',
		/* [90] */
		"PrintMonitorDocs=prnt",
		'CASE',
		/* [91] */
		"PrinterDescription=ppdf",
		'CASE',
		/* [92] */
		"PrinterDriver=’prd",
		'CASE',
		/* [93] */
		"Printers=impr",
		'CASE',
		/* [94] */
		"PrintingPlugIns=pplg",
		'CASE',
		/* [95] */
		"PrivateFrameworks=pfrm",
		'CASE',
		/* [96] */
		"Public=pubb",
		'CASE',
		/* [97] */
		"QuickTimeComponents=wcmp",
		'CASE',
		/* [98] */
		"QuickTimeExtensions=qtex",
		'CASE',
		/* [99] */
		"RecentApplications=rapp",
		'CASE',
		/* [100] */
		"RecentDocuments=rdoc",
		'CASE',
		/* [101] */
		"RecentServers=rsvr",
		'CASE',
		/* [102] */
		"ScriptingAdditions=’scr",
		'CASE',
		/* [103] */
		"Scripts=scr’",
		'CASE',
		/* [104] */
		"SharedLibraries=’lib",
		'CASE',
		/* [105] */
		"SharedUserData=sdat",
		'CASE',
		/* [106] */
		"Shutdown=shdf",
		'CASE',
		/* [107] */
		"ShutdownItemsDisabled=shdD",
		'CASE',
		/* [108] */
		"SoundSets=snds",
		'CASE',
		/* [109] */
		"SpeakableItems=spki",
		'CASE',
		/* [110] */
		"Speech=spch",
		'CASE',
		/* [111] */
		"Startup=strt",
		'CASE',
		/* [112] */
		"StartupItemsDisabled=strD",
		'CASE',
		/* [113] */
		"Stationery=odst",
		'CASE',
		/* [114] */
		"System=macs",
		'CASE',
		/* [115] */
		"SystemControlPanel=sctl",
		'CASE',
		/* [116] */
		"SystemDesktop=sdsk",
		'CASE',
		/* [117] */
		"SystemExtensionDisabled=macD",
		'CASE',
		/* [118] */
		"SystemPreferences=sprf",
		'CASE',
		/* [119] */
		"SystemSounds=ssnd",
		'CASE',
		/* [120] */
		"SystemTrash=strs",
		'CASE',
		/* [121] */
		"Temporary=temp",
		'CASE',
		/* [122] */
		"TextEncodings=’tex",
		'CASE',
		/* [123] */
		"Themes=thme",
		'CASE',
		/* [124] */
		"Trash=trsh",
		'CASE',
		/* [125] */
		"UserSpecificTmp=utmp",
		'CASE',
		/* [126] */
		"Users=usrs",
		'CASE',
		/* [127] */
		"Utilities=uti’",
		'CASE',
		/* [128] */
		"Voices=fvoc",
		'CASE',
		/* [129] */
		"VolumeRoot=root",
		'CASE',
		/* [130] */
		"VolumeSettings=vsfd",
		'CASE',
		/* [131] */
		"WhereToEmptyTrash=empt",
		'CASE',
		/* [132] */
		"Reserved (set to 0)",
		'FLNG',
		/* [133] */
		"-----",
		'LSTE'
	}
};

resource 'TMPL' (1314, "ROv#") {
	{	/* array: 6 elements */
		/* [1] */
		"Version",
		'DWRD',
		/* [2] */
		"Num of types",
		'ZCNT',
		/* [3] */
		"Types",
		'LSTC',
		/* [4] */
		"Type",
		'TNAM',
		/* [5] */
		"Resource ID",
		'DWRD',
		/* [6] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1315, "rptw") {
	{	/* array: 6 elements */
		/* [1] */
		"Name column width",
		'DWRD',
		/* [2] */
		"Version column width",
		'DWRD',
		/* [3] */
		"Column4 width",
		'DWRD',
		/* [4] */
		"Column4 width",
		'DWRD',
		/* [5] */
		"Column5 width",
		'DWRD',
		/* [6] */
		"Column6 width",
		'DWRD'
	}
};

resource 'TMPL' (1316, "RSCP") {
	{	/* array: 21 elements */
		/* [1] */
		"Resource Spec Current Version (should be"
		" 1)",
		'DWRD',
		/* [2] */
		"Resource Spec Min Compat Vers (should be"
		" 1)",
		'DWRD',
		/* [3] */
		"Count:",
		'OCNT',
		/* [4] */
		"Primary Resource Types",
		'LSTC',
		/* [5] */
		"Primary Type",
		'TNAM',
		/* [6] */
		"",
		'LSTE',
		/* [7] */
		"Count:",
		'OCNT',
		/* [8] */
		"Secondary Resource Types",
		'LSTC',
		/* [9] */
		"Secondary Type",
		'TNAM',
		/* [10] */
		"",
		'LSTE',
		/* [11] */
		"Resource type name",
		'PSTR',
		/* [12] */
		"Resource folder name",
		'PSTR',
		/* [13] */
		"Resource editor class name",
		'PSTR',
		/* [14] */
		"Resource type icon",
		'DWRD',
		/* [15] */
		"Resource folder icon",
		'DWRD',
		/* [16] */
		"Default resource ID - start",
		'DWRD',
		/* [17] */
		"Default Resource ID - end",
		'DWRD',
		/* [18] */
		"Preferred sort sequence",
		'DLNG',
		/* [19] */
		"Create empty folder in project?",
		'BFLG',
		/* [20] */
		"Update resource data when ID changes?",
		'BFLG',
		/* [21] */
		"Default new resource ID",
		'DWRD'
	}
};

resource 'TMPL' (1317, "RSID") {
	{	/* array: 13 elements */
		/* [1] */
		"\"Resurrection\" resource format",
		'DVDR',
		/* [2] */
		"Count:",
		'OCNT',
		/* [3] */
		"Resource types",
		'LSTC',
		/* [4] */
		"Type",
		'TNAM',
		/* [5] */
		"Start ID",
		'DWRD',
		/* [6] */
		"Reserved",
		'WB09',
		/* [7] */
		"System heap",
		'WBIT',
		/* [8] */
		"Purgeable",
		'WBIT',
		/* [9] */
		"Locked",
		'WBIT',
		/* [10] */
		"Protected",
		'WBIT',
		/* [11] */
		"Preload",
		'WBIT',
		/* [12] */
		"RAM Bits",
		'WB02',
		/* [13] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1318, "rst#") {
	{	/* array: 8 elements */
		/* [1] */
		"Size of the following data",
		'WSIZ',
		/* [2] */
		"Count:",
		'OCNT',
		/* [3] */
		"List of Strings",
		'LSTC',
		/* [4] */
		"Script region code",
		'SCPC',
		/* [5] */
		"Long string",
		'WSTR',
		/* [6] */
		"Align",
		'AWRD',
		/* [7] */
		"*****",
		'LSTE',
		/* [8] */
		"",
		'SKPE'
	}
};

resource 'TMPL' (1319, "rstr") {
	{	/* array: 2 elements */
		/* [1] */
		"Script region code",
		'SCPC',
		/* [2] */
		"String",
		'WSTR'
	}
};

resource 'TMPL' (1320, "RTXT") {
	{	/* array: 4 elements */
		/* [1] */
		"TrueType rotated text?",
		'BBIT',
		/* [2] */
		"Text bounding boxes?",
		'BBIT',
		/* [3] */
		"Rotated line layout?",
		'BBIT',
		/* [4] */
		"Unused",
		'BB05'
	}
};

resource 'TMPL' (1321, "RVEW") {
	{	/* array: 2 elements */
		/* [1] */
		"View by",
		'DBYT',
		/* [2] */
		"Show attributes",
		'DBYT'
	}
};

resource 'TMPL' (1322, "RZID") {
	{	/* array: 4 elements */
		/* [1] */
		"Resources",
		'LSTB',
		/* [2] */
		"Resource type",
		'TNAM',
		/* [3] */
		"Associated editor's ID",
		'DLNG',
		/* [4] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1323, "RZLE") {
	{	/* array: 8 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"Editors array",
		'LSTC',
		/* [3] */
		"Editor's name",
		'PSTR',
		/* [4] */
		"Editor's ID",
		'DLNG',
		/* [5] */
		"Array of supported types",
		'LSTB',
		/* [6] */
		"Four-chars-code",
		'TNAM',
		/* [7] */
		"*****",
		'LSTE',
		/* [8] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1324, "RzTA") {
	{	/* array: 4 elements */
		/* [1] */
		"TypeAs array",
		'LSTB',
		/* [2] */
		"Original type",
		'TNAM',
		/* [3] */
		"Substitute type",
		'TNAM',
		/* [4] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1325, "sAbt") {
	{	/* array: 11 elements */
		/* [1] */
		"\"SuitCase\" resource format",
		'DVDR',
		/* [2] */
		"SymAbout 'DLOG' ID (color)",
		'DWRD',
		/* [3] */
		"SymAbout 'DLOG' ID (b/w)",
		'DWRD',
		/* [4] */
		"SymAbout 'STR#' ID",
		'DWRD',
		/* [5] */
		"Auto Open button item",
		'DWRD',
		/* [6] */
		"Product name TETextBox alignment",
		'DWRD',
		/* [7] */
		"Product name font size",
		'DWRD',
		/* [8] */
		"Product name font face",
		'DWRD',
		/* [9] */
		"Frame RGB triplet  ",
		'COLR',
		/* [10] */
		"UpperLeft bevel RGB triplet  ",
		'COLR',
		/* [11] */
		"LowerRight bevel RGB triplet  ",
		'COLR'
	}
};

resource 'TMPL' (1326, "sami") {
	{	/* array: 10 elements */
		/* [1] */
		"Maximum number of directories/slots",
		'DWRD',
		/* [2] */
		"Directory signature (MSAM type)",
		'TNAM',
		/* [3] */
		"Is this an MSAM template?",
		'BFLG',
		/* [4] */
		"Is this a DSAM template?",
		'BFLG',
		/* [5] */
		"Script code",
		'SCPC',
		/* [6] */
		"What to display when user clicks \"Add\"",
		'WSTR',
		/* [7] */
		"Align",
		'AWRD',
		/* [8] */
		"Script code",
		'SCPC',
		/* [9] */
		"New record name",
		'WSTR',
		/* [10] */
		"Align",
		'AWRD'
	}
};

resource 'TMPL' (1327, "scan") {
	{	/* array: 72 elements */
		/* [1] */
		"Owner count",
		'DLNG',
		/* [2] */
		"Scan strings",
		'LSTB',
		/* [3] */
		"String scan type",
		'KWRD',
		/* [4] */
		"Use this string=0",
		'CASE',
		/* [5] */
		"User name=1",
		'CASE',
		/* [6] */
		"Document name=2",
		'CASE',
		/* [7] */
		"Printer name=3",
		'CASE',
		/* [8] */
		"NIL pointer=4",
		'CASE',
		/* [9] */
		"0",
		'KEYB',
		/* [10] */
		"The string",
		'WSTR',
		/* [11] */
		"Align",
		'AWRD',
		/* [12] */
		"",
		'KEYE',
		/* [13] */
		"1",
		'KEYB',
		/* [14] */
		"",
		'KEYE',
		/* [15] */
		"2",
		'KEYB',
		/* [16] */
		"",
		'KEYE',
		/* [17] */
		"3",
		'KEYB',
		/* [18] */
		"",
		'KEYE',
		/* [19] */
		"4",
		'KEYB',
		/* [20] */
		"Length",
		'DWRD',
		/* [21] */
		"",
		'KEYE',
		/* [22] */
		"Replacement string scan type",
		'KWRD',
		/* [23] */
		"Use this string=0",
		'CASE',
		/* [24] */
		"User name=1",
		'CASE',
		/* [25] */
		"Document name=2",
		'CASE',
		/* [26] */
		"Printer name=3",
		'CASE',
		/* [27] */
		"NIL pointer=4",
		'CASE',
		/* [28] */
		"0",
		'KEYB',
		/* [29] */
		"The string",
		'WSTR',
		/* [30] */
		"Align",
		'AWRD',
		/* [31] */
		"",
		'KEYE',
		/* [32] */
		"1",
		'KEYB',
		/* [33] */
		"",
		'KEYE',
		/* [34] */
		"2",
		'KEYB',
		/* [35] */
		"",
		'KEYE',
		/* [36] */
		"3",
		'KEYB',
		/* [37] */
		"",
		'KEYE',
		/* [38] */
		"4",
		'KEYB',
		/* [39] */
		"Length",
		'DWRD',
		/* [40] */
		"",
		'KEYE',
		/* [41] */
		"Offset scan type",
		'KWRD',
		/* [42] */
		"Simple offset=0",
		'CASE',
		/* [43] */
		"Same as previous offset=1",
		'CASE',
		/* [44] */
		"Returned offset=2",
		'CASE',
		/* [45] */
		"Simple repeat=16",
		'CASE',
		/* [46] */
		"Same as previous repeat=17",
		'CASE',
		/* [47] */
		"Returned repeat=18",
		'CASE',
		/* [48] */
		"0",
		'KEYB',
		/* [49] */
		"",
		'KEYE',
		/* [50] */
		"1",
		'KEYB',
		/* [51] */
		"",
		'KEYE',
		/* [52] */
		"2",
		'KEYB',
		/* [53] */
		"",
		'KEYE',
		/* [54] */
		"16",
		'KEYB',
		/* [55] */
		"",
		'KEYE',
		/* [56] */
		"17",
		'KEYB',
		/* [57] */
		"",
		'KEYE',
		/* [58] */
		"18",
		'KEYB',
		/* [59] */
		"",
		'KEYE',
		/* [60] */
		"Action scan type",
		'KWRD',
		/* [61] */
		"No action=0",
		'CASE',
		/* [62] */
		"Simple=1",
		'CASE',
		/* [63] */
		"0",
		'KEYB',
		/* [64] */
		"",
		'KEYE',
		/* [65] */
		"1",
		'KEYB',
		/* [66] */
		"Type",
		'DWRD',
		/* [67] */
		"Normal=0",
		'CASE',
		/* [68] */
		"Non-fatal error=1",
		'CASE',
		/* [69] */
		"Fatal error=2",
		'CASE',
		/* [70] */
		"Alert ('ALRT') resource ID",
		'RSID',
		/* [71] */
		"",
		'KEYE',
		/* [72] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1328, "scop") {
	{	/* array: 4 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"Scopes",
		'LSTC',
		/* [3] */
		"Scope type",
		'TNAM',
		/* [4] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1329, "scrn") {
	{	/* array: 23 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"List of Devices",
		'LSTC',
		/* [3] */
		"sRsrc type",
		'HWRD',
		/* [4] */
		"Nubus slot (card slot+8)",
		'DWRD',
		/* [5] */
		"dCtl Device Base",
		'HLNG',
		/* [6] */
		"sRsrc ID for mode",
		'DWRD',
		/* [7] */
		"FlagMask",
		'HWRD',
		/* [8] */
		"Always=$77FE",
		'CASE',
		/* [9] */
		"Is active",
		'WBIT',
		/* [10] */
		"Reserved",
		'WB03',
		/* [11] */
		"Is main screen",
		'WBIT',
		/* [12] */
		"Reserved",
		'WB10',
		/* [13] */
		"Is color",
		'WBIT',
		/* [14] */
		"'clut' resource ID",
		'RSID',
		/* [15] */
		"Gamma correction table resource ID",
		'RSID',
		/* [16] */
		"Device's global rectangle",
		'RECT',
		/* [17] */
		"Count:",
		'OCNT',
		/* [18] */
		"Control calls",
		'LSTC',
		/* [19] */
		"CsCode",
		'DWRD',
		/* [20] */
		"Parameter block",
		'WSTR',
		/* [21] */
		"Align",
		'AWRD',
		/* [22] */
		"*****",
		'LSTE',
		/* [23] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1330, "scsz") {
	{	/* array: 10 elements */
		/* [1] */
		"Launch to get terminology",
		'WBIT',
		/* [2] */
		"Don't find app by signature",
		'WBIT',
		/* [3] */
		"Always send subject",
		'WBIT',
		/* [4] */
		"Reserved",
		'WB13',
		/* [5] */
		"Min stack size",
		'DLNG',
		/* [6] */
		"Preferred stack size",
		'DLNG',
		/* [7] */
		"Max stack size",
		'DLNG',
		/* [8] */
		"Min heap size",
		'DLNG',
		/* [9] */
		"Preferred heap size",
		'DLNG',
		/* [10] */
		"Max heap size",
		'DLNG'
	}
};

resource 'TMPL' (1331, "sect") {
	{	/* array: 11 elements */
		/* [1] */
		"Version",
		'DBYT',
		/* [2] */
		"Kind",
		'DBYT',
		/* [3] */
		"Mode",
		'DWRD',
		/* [4] */
		"Mod Date",
		'DATE',
		/* [5] */
		"Section ID",
		'DLNG',
		/* [6] */
		"RefCon",
		'DLNG',
		/* [7] */
		"Alias handle",
		'DLNG',
		/* [8] */
		"Sub part",
		'DLNG',
		/* [9] */
		"Next section",
		'DLNG',
		/* [10] */
		"Control block",
		'DLNG',
		/* [11] */
		"Ref num",
		'DLNG'
	}
};

resource 'TMPL' (1332, "sept") {
	{	/* array: 256 elements */
		/* [1] */
		"0x01",
		'BOOL',
		/* [2] */
		"0x02",
		'BOOL',
		/* [3] */
		"0x03",
		'BOOL',
		/* [4] */
		"0x04",
		'BOOL',
		/* [5] */
		"0x05",
		'BOOL',
		/* [6] */
		"0x06",
		'BOOL',
		/* [7] */
		"0x07",
		'BOOL',
		/* [8] */
		"0x08",
		'BOOL',
		/* [9] */
		"0x09",
		'BOOL',
		/* [10] */
		"0x0A",
		'BOOL',
		/* [11] */
		"0x0B",
		'BOOL',
		/* [12] */
		"0x0C",
		'BOOL',
		/* [13] */
		"0x0D",
		'BOOL',
		/* [14] */
		"0x0E",
		'BOOL',
		/* [15] */
		"0x0F",
		'BOOL',
		/* [16] */
		"0x10",
		'BOOL',
		/* [17] */
		"0x11",
		'BOOL',
		/* [18] */
		"0x11",
		'BOOL',
		/* [19] */
		"0x12",
		'BOOL',
		/* [20] */
		"0x13",
		'BOOL',
		/* [21] */
		"0x14",
		'BOOL',
		/* [22] */
		"0x15",
		'BOOL',
		/* [23] */
		"0x16",
		'BOOL',
		/* [24] */
		"0x17",
		'BOOL',
		/* [25] */
		"0x18",
		'BOOL',
		/* [26] */
		"0x19",
		'BOOL',
		/* [27] */
		"0x1A",
		'BOOL',
		/* [28] */
		"0x1B",
		'BOOL',
		/* [29] */
		"0x1C",
		'BOOL',
		/* [30] */
		"0x1D",
		'BOOL',
		/* [31] */
		"0x1E",
		'BOOL',
		/* [32] */
		"0x1F",
		'BOOL',
		/* [33] */
		"0x20",
		'BOOL',
		/* [34] */
		"0x21",
		'BOOL',
		/* [35] */
		"0x22",
		'BOOL',
		/* [36] */
		"0x23",
		'BOOL',
		/* [37] */
		"0x24",
		'BOOL',
		/* [38] */
		"0x25",
		'BOOL',
		/* [39] */
		"0x26",
		'BOOL',
		/* [40] */
		"0x27",
		'BOOL',
		/* [41] */
		"0x28",
		'BOOL',
		/* [42] */
		"0x29",
		'BOOL',
		/* [43] */
		"0x2A",
		'BOOL',
		/* [44] */
		"0x2B",
		'BOOL',
		/* [45] */
		"0x2C",
		'BOOL',
		/* [46] */
		"0x2D",
		'BOOL',
		/* [47] */
		"0x2E",
		'BOOL',
		/* [48] */
		"0x2F",
		'BOOL',
		/* [49] */
		"0x30",
		'BOOL',
		/* [50] */
		"0x31",
		'BOOL',
		/* [51] */
		"0x32",
		'BOOL',
		/* [52] */
		"0x33",
		'BOOL',
		/* [53] */
		"0x34",
		'BOOL',
		/* [54] */
		"0x35",
		'BOOL',
		/* [55] */
		"0x36",
		'BOOL',
		/* [56] */
		"0x37",
		'BOOL',
		/* [57] */
		"0x38",
		'BOOL',
		/* [58] */
		"0x39",
		'BOOL',
		/* [59] */
		"0x3A",
		'BOOL',
		/* [60] */
		"0x3B",
		'BOOL',
		/* [61] */
		"0x3C",
		'BOOL',
		/* [62] */
		"0x3D",
		'BOOL',
		/* [63] */
		"0x3E",
		'BOOL',
		/* [64] */
		"0x3F",
		'BOOL',
		/* [65] */
		"0x40",
		'BOOL',
		/* [66] */
		"0x41",
		'BOOL',
		/* [67] */
		"0x42",
		'BOOL',
		/* [68] */
		"0x43",
		'BOOL',
		/* [69] */
		"0x44",
		'BOOL',
		/* [70] */
		"0x45",
		'BOOL',
		/* [71] */
		"0x46",
		'BOOL',
		/* [72] */
		"0x47",
		'BOOL',
		/* [73] */
		"0x48",
		'BOOL',
		/* [74] */
		"0x49",
		'BOOL',
		/* [75] */
		"0x4A",
		'BOOL',
		/* [76] */
		"0x4B",
		'BOOL',
		/* [77] */
		"0x4C",
		'BOOL',
		/* [78] */
		"0x4D",
		'BOOL',
		/* [79] */
		"0x4E",
		'BOOL',
		/* [80] */
		"0x4F",
		'BOOL',
		/* [81] */
		"0x50",
		'BOOL',
		/* [82] */
		"0x51",
		'BOOL',
		/* [83] */
		"0x52",
		'BOOL',
		/* [84] */
		"0x53",
		'BOOL',
		/* [85] */
		"0x54",
		'BOOL',
		/* [86] */
		"0x55",
		'BOOL',
		/* [87] */
		"0x56",
		'BOOL',
		/* [88] */
		"0x57",
		'BOOL',
		/* [89] */
		"0x58",
		'BOOL',
		/* [90] */
		"0x59",
		'BOOL',
		/* [91] */
		"0x5A",
		'BOOL',
		/* [92] */
		"0x5B",
		'BOOL',
		/* [93] */
		"0x5C",
		'BOOL',
		/* [94] */
		"0x5D",
		'BOOL',
		/* [95] */
		"0x5E",
		'BOOL',
		/* [96] */
		"0x5F",
		'BOOL',
		/* [97] */
		"0x60",
		'BOOL',
		/* [98] */
		"0x61",
		'BOOL',
		/* [99] */
		"0x62",
		'BOOL',
		/* [100] */
		"0x63",
		'BOOL',
		/* [101] */
		"0x64",
		'BOOL',
		/* [102] */
		"0x65",
		'BOOL',
		/* [103] */
		"0x66",
		'BOOL',
		/* [104] */
		"0x67",
		'BOOL',
		/* [105] */
		"0x68",
		'BOOL',
		/* [106] */
		"0x69",
		'BOOL',
		/* [107] */
		"0x6A",
		'BOOL',
		/* [108] */
		"0x6B",
		'BOOL',
		/* [109] */
		"0x6C",
		'BOOL',
		/* [110] */
		"0x6D",
		'BOOL',
		/* [111] */
		"0x6E",
		'BOOL',
		/* [112] */
		"0x6F",
		'BOOL',
		/* [113] */
		"0x70",
		'BOOL',
		/* [114] */
		"0x71",
		'BOOL',
		/* [115] */
		"0x72",
		'BOOL',
		/* [116] */
		"0x73",
		'BOOL',
		/* [117] */
		"0x74",
		'BOOL',
		/* [118] */
		"0x75",
		'BOOL',
		/* [119] */
		"0x76",
		'BOOL',
		/* [120] */
		"0x77",
		'BOOL',
		/* [121] */
		"0x78",
		'BOOL',
		/* [122] */
		"0x79",
		'BOOL',
		/* [123] */
		"0x7A",
		'BOOL',
		/* [124] */
		"0x7B",
		'BOOL',
		/* [125] */
		"0x7C",
		'BOOL',
		/* [126] */
		"0x7D",
		'BOOL',
		/* [127] */
		"0x7E",
		'BOOL',
		/* [128] */
		"0x7F",
		'BOOL',
		/* [129] */
		"0x80",
		'BOOL',
		/* [130] */
		"0x81",
		'BOOL',
		/* [131] */
		"0x82",
		'BOOL',
		/* [132] */
		"0x83",
		'BOOL',
		/* [133] */
		"0x84",
		'BOOL',
		/* [134] */
		"0x85",
		'BOOL',
		/* [135] */
		"0x86",
		'BOOL',
		/* [136] */
		"0x87",
		'BOOL',
		/* [137] */
		"0x88",
		'BOOL',
		/* [138] */
		"0x89",
		'BOOL',
		/* [139] */
		"0x8A",
		'BOOL',
		/* [140] */
		"0x8B",
		'BOOL',
		/* [141] */
		"0x8C",
		'BOOL',
		/* [142] */
		"0x8D",
		'BOOL',
		/* [143] */
		"0x8E",
		'BOOL',
		/* [144] */
		"0x8F",
		'BOOL',
		/* [145] */
		"0x90",
		'BOOL',
		/* [146] */
		"0x91",
		'BOOL',
		/* [147] */
		"0x92",
		'BOOL',
		/* [148] */
		"0x93",
		'BOOL',
		/* [149] */
		"0x94",
		'BOOL',
		/* [150] */
		"0x95",
		'BOOL',
		/* [151] */
		"0x96",
		'BOOL',
		/* [152] */
		"0x97",
		'BOOL',
		/* [153] */
		"0x98",
		'BOOL',
		/* [154] */
		"0x99",
		'BOOL',
		/* [155] */
		"0x9A",
		'BOOL',
		/* [156] */
		"0x9B",
		'BOOL',
		/* [157] */
		"0x9C",
		'BOOL',
		/* [158] */
		"0x9D",
		'BOOL',
		/* [159] */
		"0x9E",
		'BOOL',
		/* [160] */
		"0x9F",
		'BOOL',
		/* [161] */
		"0xA0",
		'BOOL',
		/* [162] */
		"0xA1",
		'BOOL',
		/* [163] */
		"0xA2",
		'BOOL',
		/* [164] */
		"0xA3",
		'BOOL',
		/* [165] */
		"0xA4",
		'BOOL',
		/* [166] */
		"0xA5",
		'BOOL',
		/* [167] */
		"0xA6",
		'BOOL',
		/* [168] */
		"0xA7",
		'BOOL',
		/* [169] */
		"0xA8",
		'BOOL',
		/* [170] */
		"0xA9",
		'BOOL',
		/* [171] */
		"0xAA",
		'BOOL',
		/* [172] */
		"0xAB",
		'BOOL',
		/* [173] */
		"0xAC",
		'BOOL',
		/* [174] */
		"0xAD",
		'BOOL',
		/* [175] */
		"0xAE",
		'BOOL',
		/* [176] */
		"0xAF",
		'BOOL',
		/* [177] */
		"0xB0",
		'BOOL',
		/* [178] */
		"0xB1",
		'BOOL',
		/* [179] */
		"0xB2",
		'BOOL',
		/* [180] */
		"0xB3",
		'BOOL',
		/* [181] */
		"0xB4",
		'BOOL',
		/* [182] */
		"0xB5",
		'BOOL',
		/* [183] */
		"0xB6",
		'BOOL',
		/* [184] */
		"0xB7",
		'BOOL',
		/* [185] */
		"0xB8",
		'BOOL',
		/* [186] */
		"0xB9",
		'BOOL',
		/* [187] */
		"0xBA",
		'BOOL',
		/* [188] */
		"0xBB",
		'BOOL',
		/* [189] */
		"0xBC",
		'BOOL',
		/* [190] */
		"0xBD",
		'BOOL',
		/* [191] */
		"0xBE",
		'BOOL',
		/* [192] */
		"0xBF",
		'BOOL',
		/* [193] */
		"0xC0",
		'BOOL',
		/* [194] */
		"0xC1",
		'BOOL',
		/* [195] */
		"0xC2",
		'BOOL',
		/* [196] */
		"0xC3",
		'BOOL',
		/* [197] */
		"0xC4",
		'BOOL',
		/* [198] */
		"0xC5",
		'BOOL',
		/* [199] */
		"0xC6",
		'BOOL',
		/* [200] */
		"0xC7",
		'BOOL',
		/* [201] */
		"0xC8",
		'BOOL',
		/* [202] */
		"0xC9",
		'BOOL',
		/* [203] */
		"0xCA",
		'BOOL',
		/* [204] */
		"0xCB",
		'BOOL',
		/* [205] */
		"0xCC",
		'BOOL',
		/* [206] */
		"0xCD",
		'BOOL',
		/* [207] */
		"0xCE",
		'BOOL',
		/* [208] */
		"0xCF",
		'BOOL',
		/* [209] */
		"0xD0",
		'BOOL',
		/* [210] */
		"0xD1",
		'BOOL',
		/* [211] */
		"0xD2",
		'BOOL',
		/* [212] */
		"0xD3",
		'BOOL',
		/* [213] */
		"0xD4",
		'BOOL',
		/* [214] */
		"0xD5",
		'BOOL',
		/* [215] */
		"0xD6",
		'BOOL',
		/* [216] */
		"0xD7",
		'BOOL',
		/* [217] */
		"0xD8",
		'BOOL',
		/* [218] */
		"0xD9",
		'BOOL',
		/* [219] */
		"0xDA",
		'BOOL',
		/* [220] */
		"0xDB",
		'BOOL',
		/* [221] */
		"0xDC",
		'BOOL',
		/* [222] */
		"0xDD",
		'BOOL',
		/* [223] */
		"0xDE",
		'BOOL',
		/* [224] */
		"0xDF",
		'BOOL',
		/* [225] */
		"0xE0",
		'BOOL',
		/* [226] */
		"0xE1",
		'BOOL',
		/* [227] */
		"0xE2",
		'BOOL',
		/* [228] */
		"0xE3",
		'BOOL',
		/* [229] */
		"0xE4",
		'BOOL',
		/* [230] */
		"0xE5",
		'BOOL',
		/* [231] */
		"0xE6",
		'BOOL',
		/* [232] */
		"0xE7",
		'BOOL',
		/* [233] */
		"0xE8",
		'BOOL',
		/* [234] */
		"0xE9",
		'BOOL',
		/* [235] */
		"0xEA",
		'BOOL',
		/* [236] */
		"0xEB",
		'BOOL',
		/* [237] */
		"0xEC",
		'BOOL',
		/* [238] */
		"0xED",
		'BOOL',
		/* [239] */
		"0xEE",
		'BOOL',
		/* [240] */
		"0xEF",
		'BOOL',
		/* [241] */
		"0xF0",
		'BOOL',
		/* [242] */
		"0xF1",
		'BOOL',
		/* [243] */
		"0xF2",
		'BOOL',
		/* [244] */
		"0xF3",
		'BOOL',
		/* [245] */
		"0xF4",
		'BOOL',
		/* [246] */
		"0xF5",
		'BOOL',
		/* [247] */
		"0xF6",
		'BOOL',
		/* [248] */
		"0xF7",
		'BOOL',
		/* [249] */
		"0xF8",
		'BOOL',
		/* [250] */
		"0xF9",
		'BOOL',
		/* [251] */
		"0xFA",
		'BOOL',
		/* [252] */
		"0xFB",
		'BOOL',
		/* [253] */
		"0xFC",
		'BOOL',
		/* [254] */
		"0xFD",
		'BOOL',
		/* [255] */
		"0xFE",
		'BOOL',
		/* [256] */
		"0xFF",
		'BOOL'
	}
};

resource 'TMPL' (1333, "SICN") {
	{	/* array: 3 elements */
		/* [1] */
		"Small icons array",
		'LSTB',
		/* [2] */
		"Icon data",
		'H020',
		/* [3] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1334, "sig ") {
	{	/* array: 1 elements */
		/* [1] */
		"Creator type of file",
		'TNAM'
	}
};

resource 'TMPL' (1335, "SIGN") {
	{	/* array: 2 elements */
		/* [1] */
		"Key word",
		'DLNG',
		/* [2] */
		"BNDL resource ID",
		'RSID'
	}
};

resource 'TMPL' (1336, "SINF") {
	{	/* array: 6 elements */
		/* [1] */
		"Internet Config resource format",
		'DVDR',
		/* [2] */
		"Script",
		'SCPC',
		/* [3] */
		"Region",
		'RGNC',
		/* [4] */
		"Language",
		'LNGC',
		/* [5] */
		"Font size",
		'DWRD',
		/* [6] */
		"Font name",
		'PSTR'
	}
};

resource 'TMPL' (1337, "SIZE") {
	{	/* array: 16 elements */
		/* [1] */
		"Save screen (obsolete)",
		'BBIT',
		/* [2] */
		"Accept suspend/resume events",
		'BBIT',
		/* [3] */
		"Disable option (obsolete)",
		'BBIT',
		/* [4] */
		"Can background",
		'BBIT',
		/* [5] */
		"Does activate on FG switch",
		'BBIT',
		/* [6] */
		"Only background",
		'BBIT',
		/* [7] */
		"Get front clicks",
		'BBIT',
		/* [8] */
		"Accept app died events (debuggers)",
		'BBIT',
		/* [9] */
		"32 Bit Compatible",
		'BBIT',
		/* [10] */
		"High level event aware",
		'BBIT',
		/* [11] */
		"Local and remote high level events",
		'BBIT',
		/* [12] */
		"Stationery aware",
		'BBIT',
		/* [13] */
		"Use text edit services",
		'BBIT',
		/* [14] */
		"Reserved",
		'BB03',
		/* [15] */
		"Preferred size (in bytes)",
		'DLNG',
		/* [16] */
		"Minimum size (in bytes)",
		'DLNG'
	}
};

resource 'TMPL' (1338, "Smly") {
	{	/* array: 9 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"List of Smileys",
		'LSTC',
		/* [3] */
		"Smiley (3 characters max)",
		'ESTR',
		/* [4] */
		"Filler (2 bytes)",
		'FWRD',
		/* [5] */
		"Filler (4 bytes)",
		'FLNG',
		/* [6] */
		"Filler (4 bytes)",
		'FLNG',
		/* [7] */
		"Filler (2 bytes)",
		'FWRD',
		/* [8] */
		"Face ID",
		'DWRD',
		/* [9] */
		"-----",
		'LSTE'
	}
};

resource 'TMPL' (1339, "Sods") {
	{	/* array: 9 elements */
		/* [1] */
		"Version",
		'HLNG',
		/* [2] */
		"Default token breaks",
		'PSTR',
		/* [3] */
		"Count:",
		'LCNT',
		/* [4] */
		"List of Keywords",
		'LSTC',
		/* [5] */
		"Keyword",
		'PSTR',
		/* [6] */
		"Keyword class",
		'HLNG',
		/* [7] */
		"Scoping parameter",
		'TNAM',
		/* [8] */
		"Color index",
		'DLNG',
		/* [9] */
		"",
		'LSTE'
	}
};

resource 'TMPL' (1340, "SPLY") {
	{	/* array: 8 elements */
		/* [1] */
		"Playlist name",
		'P100',
		/* [2] */
		"Private",
		'H074',
		/* [3] */
		"Count:",
		'LCNT',
		/* [4] */
		"Filters",
		'LSTC',
		/* [5] */
		"Private",
		'H00C',
		/* [6] */
		"String value",
		'P100',
		/* [7] */
		"Private",
		'H044',
		/* [8] */
		"",
		'LSTE'
	}
};

resource 'TMPL' (1341, "sReq") {
	{	/* array: 6 elements */
		/* [1] */
		"\"AfterDark\" resource format",
		'DVDR',
		/* [2] */
		"Unused",
		'DWRD',
		/* [3] */
		"Unused",
		'BB06',
		/* [4] */
		"Wants to animate palette",
		'BBIT',
		/* [5] */
		"Unused",
		'BBIT',
		/* [6] */
		"Unused",
		'DBYT'
	}
};

resource 'TMPL' (1342, "stab") {
	{	/* array: 5 elements */
		/* [1] */
		"Values in reduction table should be in a"
		"scending order",
		'DVDR',
		/* [2] */
		"Count:",
		'OCNT',
		/* [3] */
		"Reduction values",
		'LSTC',
		/* [4] */
		"Value",
		'DWRD',
		/* [5] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1343, "stat") {
	{	/* array: 20 elements */
		/* [1] */
		"Status owner",
		'TNAM',
		/* [2] */
		"Status",
		'LSTB',
		/* [3] */
		"Status or error type",
		'DWRD',
		/* [4] */
		"No error=0",
		'CASE',
		/* [5] */
		"Non-fatal=1",
		'CASE',
		/* [6] */
		"Fatal error=2",
		'CASE',
		/* [7] */
		"Printer ready=3",
		'CASE',
		/* [8] */
		"User attention=4",
		'CASE',
		/* [9] */
		"User alert=5",
		'CASE',
		/* [10] */
		"Page transmission=6",
		'CASE',
		/* [11] */
		"Open connection=7",
		'CASE',
		/* [12] */
		"Informational status=8",
		'CASE',
		/* [13] */
		"Spooling page=9",
		'CASE',
		/* [14] */
		"End status=10",
		'CASE',
		/* [15] */
		"Percentage status=11",
		'CASE',
		/* [16] */
		"Status internal ID",
		'DWRD',
		/* [17] */
		"Status Alert ('ALRT') resource ID",
		'RSID',
		/* [18] */
		"None=0",
		'CASE',
		/* [19] */
		"Status message",
		'ESTR',
		/* [20] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1344, "STCT") {
	{	/* array: 8 elements */
		/* [1] */
		"\"Fetch\" resource template",
		'DVDR',
		/* [2] */
		"Shortcuts",
		'LSTB',
		/* [3] */
		"Shortcut name",
		'PSTR',
		/* [4] */
		"Machine name",
		'PSTR',
		/* [5] */
		"User name",
		'PSTR',
		/* [6] */
		"Password",
		'PSTR',
		/* [7] */
		"Directory",
		'PSTR',
		/* [8] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1345, "STR ") {
	{	/* array: 2 elements */
		/* [1] */
		"String",
		'PSTR',
		/* [2] */
		"Hexadecimal data",
		'HEXD'
	}
};

resource 'TMPL' (1346, "STR#") {
	{	/* array: 4 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"List of strings",
		'LSTC',
		/* [3] */
		"String",
		'PSTR',
		/* [4] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1347, "stri") {
	{	/* array: 1 elements */
		/* [1] */
		"String used for component info resources",
		'PSTR'
	}
};

resource 'TMPL' (1348, "strn") {
	{	/* array: 1 elements */
		/* [1] */
		"String used for component name resources",
		'PSTR'
	}
};

resource 'TMPL' (1349, "STRT") {
	{	/* array: 6 elements */
		/* [1] */
		"\"Resurrection\" resource format",
		'DVDR',
		/* [2] */
		"Version",
		'KWRD',
		/* [3] */
		"latestVersion=0",
		'CASE',
		/* [4] */
		"0",
		'KEYB',
		/* [5] */
		"'Open' dialog at startup",
		'WFLG',
		/* [6] */
		"0",
		'KEYE'
	}
};

resource 'TMPL' (1350, "styl") {
	{	/* array: 13 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"Character runs",
		'LSTC',
		/* [3] */
		"Offset to start of style run",
		'DLNG',
		/* [4] */
		"Line height",
		'DWRD',
		/* [5] */
		"Usual=16",
		'CASE',
		/* [6] */
		"Font ascent",
		'DWRD',
		/* [7] */
		"Usual=12",
		'CASE',
		/* [8] */
		"Font family number",
		'DWRD',
		/* [9] */
		"Character style",
		'DWRD',
		/* [10] */
		"Size (in points)",
		'DWRD',
		/* [11] */
		"Usual=12",
		'CASE',
		/* [12] */
		"Text color",
		'COLR',
		/* [13] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1351, "SUFX") {
	{	/* array: 9 elements */
		/* [1] */
		"\"Fetch\" resource template",
		'DVDR',
		/* [2] */
		"Suffixes",
		'LSTB',
		/* [3] */
		"Type",
		'TNAM',
		/* [4] */
		"Creator",
		'TNAM',
		/* [5] */
		"Binary",
		'BOOL',
		/* [6] */
		"BinHex",
		'BOOL',
		/* [7] */
		"Suffix",
		'CSTR',
		/* [8] */
		"Description",
		'CSTR',
		/* [9] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1352, "Suit") {
	{	/* array: 11 elements */
		/* [1] */
		"\"SuitCase\" resource format",
		'DVDR',
		/* [2] */
		"Version",
		'UWRD',
		/* [3] */
		"Menu modifiers",
		'UWRD',
		/* [4] */
		"autoLaunch modifiers",
		'UWRD',
		/* [5] */
		"autoLaunch keyCharCode",
		'UWRD',
		/* [6] */
		"Show menus",
		'BFLG',
		/* [7] */
		"Show menus only when modifiers down",
		'BFLG',
		/* [8] */
		"Allow autoLaunch",
		'BFLG',
		/* [9] */
		"Warn before closing items",
		'BFLG',
		/* [10] */
		"Notify when conflicts",
		'BFLG',
		/* [11] */
		"Unused",
		'BFLG'
	}
};

resource 'TMPL' (1353, "sUnt") {
	{	/* array: 6 elements */
		/* [1] */
		"\"AfterDark\" resource format",
		'DVDR',
		/* [2] */
		"Count:",
		'OCNT',
		/* [3] */
		"List of items",
		'LSTC',
		/* [4] */
		"Lower Limit - Decimal",
		'DWRD',
		/* [5] */
		"String Value",
		'PSTR',
		/* [6] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1354, "sVal") {
	{	/* array: 2 elements */
		/* [1] */
		"\"AfterDark\" resource format",
		'DVDR',
		/* [2] */
		"Slider Value - Decimal",
		'DWRD'
	}
};

resource 'TMPL' (1355, "sysz") {
	{	/* array: 1 elements */
		/* [1] */
		"Memory allocated (in bytes)",
		'HLNG'
	}
};

resource 'TMPL' (1356, "tab#") {
	{	/* array: 11 elements */
		/* [1] */
		"Version",
		'KWRD',
		/* [2] */
		"Latest=0",
		'CASE',
		/* [3] */
		"0",
		'KEYB',
		/* [4] */
		"Count:",
		'OCNT',
		/* [5] */
		"Tab info records",
		'LSTC',
		/* [6] */
		"Icon suite resource ID",
		'RSID',
		/* [7] */
		"Tab name",
		'PSTR',
		/* [8] */
		"Reserved",
		'FLNG',
		/* [9] */
		"Reserved",
		'FWRD',
		/* [10] */
		"*****",
		'LSTE',
		/* [11] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1357, "Tabs") {
	{	/* array: 7 elements */
		/* [1] */
		"CW Plugin resource format",
		'DVDR',
		/* [2] */
		"Version",
		'DWRD',
		/* [3] */
		"Current=1",
		'CASE',
		/* [4] */
		"Count:",
		'OCNT',
		/* [5] */
		"Tab Items",
		'LSTC',
		/* [6] */
		"Item #",
		'DWRD',
		/* [7] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1358, "taps") {
	{	/* array: 19 elements */
		/* [1] */
		"Terminal tool capabilities list",
		'DVDR',
		/* [2] */
		"Count:",
		'OCNT',
		/* [3] */
		"List of Pairs",
		'LSTC',
		/* [4] */
		"Pair type",
		'KTYP',
		/* [5] */
		"Terminal searching=SRCH",
		'CASE',
		/* [6] */
		"Terminal file type=TYPE",
		'CASE',
		/* [7] */
		"SRCH",
		'KEYB',
		/* [8] */
		"Support for TMAddSearch",
		'DVDR',
		/* [9] */
		"Reserved",
		'LB31',
		/* [10] */
		"Supported",
		'LB01',
		/* [11] */
		"",
		'KEYE',
		/* [12] */
		"TYPE",
		'KEYB',
		/* [13] */
		"Types of files that can be transferred",
		'DVDR',
		/* [14] */
		"File type",
		'TNAM',
		/* [15] */
		"Graphic terminal=GRFX",
		'CASE',
		/* [16] */
		"Text only=TEXT",
		'CASE',
		/* [17] */
		"Graphics and text=BOTH",
		'CASE',
		/* [18] */
		"",
		'KEYE',
		/* [19] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1359, "Targ") {
	{	/* array: 32 elements */
		/* [1] */
		"CW Plugin resource format",
		'DVDR',
		/* [2] */
		"Version",
		'DWRD',
		/* [3] */
		"Current=1",
		'CASE',
		/* [4] */
		"Count:",
		'OCNT',
		/* [5] */
		"Supported CPUs",
		'LSTC',
		/* [6] */
		"CPU",
		'TNAM',
		/* [7] */
		"PowerPC=ppc ",
		'CASE',
		/* [8] */
		"MC680x0=68k ",
		'CASE',
		/* [9] */
		"i80x86=8086",
		'CASE',
		/* [10] */
		"MIPS=mips",
		'CASE',
		/* [11] */
		"V800=v800",
		'CASE',
		/* [12] */
		"V850=v850",
		'CASE',
		/* [13] */
		"mCore=Core",
		'CASE',
		/* [14] */
		"SH=SH",
		'CASE',
		/* [15] */
		"Java=java",
		'CASE',
		/* [16] */
		"Any=****",
		'CASE',
		/* [17] */
		"*****",
		'LSTE',
		/* [18] */
		"Count:",
		'OCNT',
		/* [19] */
		"Supported Operating Systems",
		'LSTC',
		/* [20] */
		"OS",
		'TNAM',
		/* [21] */
		"MacOS=mac ",
		'CASE',
		/* [22] */
		"Windows=wint",
		'CASE',
		/* [23] */
		"MagicCap=mcap",
		'CASE',
		/* [24] */
		"MIPS=mips",
		'CASE',
		/* [25] */
		"V800=v800",
		'CASE',
		/* [26] */
		"V850=v850",
		'CASE',
		/* [27] */
		"mCore=Core",
		'CASE',
		/* [28] */
		"SH=SH",
		'CASE',
		/* [29] */
		"Be=be  ",
		'CASE',
		/* [30] */
		"NetWare=nlm ",
		'CASE',
		/* [31] */
		"Any=****",
		'CASE',
		/* [32] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1360, "tdat") {
	{	/* array: 9 elements */
		/* [1] */
		"Theme Data (ID 1)",
		'DVDR',
		/* [2] */
		"Resources",
		'LSTB',
		/* [3] */
		"Resource Type",
		'TNAM',
		/* [4] */
		"These two resource IDs are always the sa"
		"me",
		'DVDR',
		/* [5] */
		"Resource ID 1",
		'RSID',
		/* [6] */
		"Resource ID 2",
		'RSID',
		/* [7] */
		"Unknown",
		'LB32',
		/* [8] */
		"Unknown",
		'LB32',
		/* [9] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1361, "TEXT") {
	{	/* array: 1 elements */
		/* [1] */
		"Text",
		'CSTR'
	}
};

resource 'TMPL' (1362, "thg0") {
	{	/* array: 19 elements */
		/* [1] */
		"Initial version of Thing resource",
		'DVDR',
		/* [2] */
		"Type of component",
		'TNAM',
		/* [3] */
		"Subtype",
		'TNAM',
		/* [4] */
		"Manufacturer",
		'TNAM',
		/* [5] */
		"Component flags",
		'HLNG',
		/* [6] */
		"Component flags mask",
		'HLNG',
		/* [7] */
		"Code type",
		'TNAM',
		/* [8] */
		"Code resource ID",
		'RSID',
		/* [9] */
		"Name type",
		'TNAM',
		/* [10] */
		"Name resource ID",
		'RSID',
		/* [11] */
		"Info type",
		'TNAM',
		/* [12] */
		"Info resource ID",
		'RSID',
		/* [13] */
		"Icon type",
		'TNAM',
		/* [14] */
		"Icon resource ID",
		'RSID',
		/* [15] */
		"Type",
		'TNAM',
		/* [16] */
		"Subtype",
		'TNAM',
		/* [17] */
		"Manufacturer",
		'TNAM',
		/* [18] */
		"Component flags",
		'HLNG',
		/* [19] */
		"Component flags mask",
		'HLNG'
	}
};

resource 'TMPL' (1363, "thga") {
	{	/* array: 23 elements */
		/* [1] */
		"Type of component",
		'TNAM',
		/* [2] */
		"Subtype",
		'TNAM',
		/* [3] */
		"Manufacturer",
		'TNAM',
		/* [4] */
		"Component flags",
		'HLNG',
		/* [5] */
		"Component flags mask",
		'HLNG',
		/* [6] */
		"Code type",
		'TNAM',
		/* [7] */
		"Code resource ID",
		'RSID',
		/* [8] */
		"Name type",
		'TNAM',
		/* [9] */
		"Name resource ID",
		'RSID',
		/* [10] */
		"Info type",
		'TNAM',
		/* [11] */
		"Info resource ID",
		'RSID',
		/* [12] */
		"Icon type",
		'TNAM',
		/* [13] */
		"Icon resource ID",
		'RSID',
		/* [14] */
		"Type",
		'TNAM',
		/* [15] */
		"Subtype",
		'TNAM',
		/* [16] */
		"Manufacturer",
		'TNAM',
		/* [17] */
		"Component flags",
		'HLNG',
		/* [18] */
		"Component flags mask",
		'HLNG',
		/* [19] */
		"Resource map type",
		'TNAM',
		/* [20] */
		"Resource map ID",
		'RSID',
		/* [21] */
		"Thing alias flags",
		'DWRD',
		/* [22] */
		"No flags=0",
		'CASE',
		/* [23] */
		"Only this file=1",
		'CASE'
	}
};

resource 'TMPL' (1364, "thn#") {
	{	/* array: 4 elements */
		/* [1] */
		"Component Manager thing load order depen"
		"dency",
		'LSTB',
		/* [2] */
		"Code type",
		'TNAM',
		/* [3] */
		"Code ID",
		'DWRD',
		/* [4] */
		"-----",
		'LSTE'
	}
};

resource 'TMPL' (1365, "thn0") {
	{	/* array: 19 elements */
		/* [1] */
		"Version 0 of Component Manager thing",
		'DVDR',
		/* [2] */
		"Type of component",
		'TNAM',
		/* [3] */
		"Subtype",
		'TNAM',
		/* [4] */
		"Manufacturer",
		'TNAM',
		/* [5] */
		"Component wants to be registered at star"
		"tup",
		'LB01',
		/* [6] */
		"Use fast dispatch when calling component",
		'LB01',
		/* [7] */
		"Reserved",
		'LB06',
		/* [8] */
		"Type flags",
		'LB08',
		/* [9] */
		"Sub-type flags",
		'LB08',
		/* [10] */
		"Manufacturer flags",
		'LB08',
		/* [11] */
		"Component flags mask",
		'HLNG',
		/* [12] */
		"Code resource type",
		'TNAM',
		/* [13] */
		"Code resource ID",
		'RSID',
		/* [14] */
		"Name resource type",
		'TNAM',
		/* [15] */
		"Name resource ID",
		'RSID',
		/* [16] */
		"Info resource type",
		'TNAM',
		/* [17] */
		"Info resource ID",
		'RSID',
		/* [18] */
		"Icon resource type",
		'TNAM',
		/* [19] */
		"Icon resource ID",
		'RSID'
	}
};

resource 'TMPL' (1366, "thn1") {
	{	/* array: 44 elements */
		/* [1] */
		"Version 1 of Component Manager thing",
		'DVDR',
		/* [2] */
		"Type of component",
		'TNAM',
		/* [3] */
		"Subtype",
		'TNAM',
		/* [4] */
		"Manufacturer",
		'TNAM',
		/* [5] */
		"Component wants to be registered at star"
		"tup",
		'LB01',
		/* [6] */
		"Use fast dispatch when calling component",
		'LB01',
		/* [7] */
		"Reserved",
		'LB06',
		/* [8] */
		"Type flags",
		'LB08',
		/* [9] */
		"Sub-type flags",
		'LB08',
		/* [10] */
		"Manufacturer flags",
		'LB08',
		/* [11] */
		"Component flags mask",
		'HLNG',
		/* [12] */
		"Code resource type",
		'TNAM',
		/* [13] */
		"Code resource ID",
		'RSID',
		/* [14] */
		"Name resource type",
		'TNAM',
		/* [15] */
		"Name resource ID",
		'RSID',
		/* [16] */
		"Info resource type",
		'TNAM',
		/* [17] */
		"Info resource ID",
		'RSID',
		/* [18] */
		"Icon resource type",
		'TNAM',
		/* [19] */
		"Icon resource ID",
		'RSID',
		/* [20] */
		"Version of Component",
		'HLNG',
		/* [21] */
		"Registration flags",
		'DVDR',
		/* [22] */
		"Reserved",
		'LB28',
		/* [23] */
		"Has code for multiple platforms",
		'LBIT',
		/* [24] */
		"Use component flags in search",
		'LBIT',
		/* [25] */
		"Call component when un-registered",
		'LBIT',
		/* [26] */
		"Use only latest version",
		'LBIT',
		/* [27] */
		"Resource ID of icon family",
		'RSID',
		/* [28] */
		"Count:",
		'LCNT',
		/* [29] */
		"Component Platform Info records",
		'LSTC',
		/* [30] */
		"Component wants to be registered at star"
		"tup",
		'LB01',
		/* [31] */
		"Use fast dispatch when calling component",
		'LB01',
		/* [32] */
		"Reserved",
		'LB06',
		/* [33] */
		"Type flags",
		'LB08',
		/* [34] */
		"Sub-type flags",
		'LB08',
		/* [35] */
		"Manufacturer flags",
		'LB08',
		/* [36] */
		"Code resource type",
		'TNAM',
		/* [37] */
		"Code resource ID",
		'RSID',
		/* [38] */
		"Platform type (gestaltComponentPlatform)",
		'DWRD',
		/* [39] */
		"68K=1",
		'CASE',
		/* [40] */
		"PowerPC=2",
		'CASE',
		/* [41] */
		"Interpreted=3",
		'CASE',
		/* [42] */
		"Win32=4",
		'CASE',
		/* [43] */
		"PPCNativeEntryPoint=5",
		'CASE',
		/* [44] */
		"-----",
		'LSTE'
	}
};

resource 'TMPL' (1367, "thnd") {
	{	/* array: 8 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"Component dependencies",
		'LSTC',
		/* [3] */
		"Type",
		'TNAM',
		/* [4] */
		"Subtype",
		'TNAM',
		/* [5] */
		"Manufacturer",
		'TNAM',
		/* [6] */
		"Component flags",
		'HLNG',
		/* [7] */
		"Component flags mask",
		'HLNG',
		/* [8] */
		"-----",
		'LSTE'
	}
};

resource 'TMPL' (1368, "thng") {
	{	/* array: 45 elements */
		/* [1] */
		"Type of component",
		'TNAM',
		/* [2] */
		"Subtype",
		'TNAM',
		/* [3] */
		"Manufacturer",
		'TNAM',
		/* [4] */
		"Component wants to be registered at star"
		"tup",
		'LB01',
		/* [5] */
		"Use fast dispatch when calling component",
		'LB01',
		/* [6] */
		"Reserved",
		'LB06',
		/* [7] */
		"Type flags",
		'LB08',
		/* [8] */
		"Sub-type flags",
		'LB08',
		/* [9] */
		"Manufacturer flags",
		'LB08',
		/* [10] */
		"Component flags mask",
		'HLNG',
		/* [11] */
		"Code resource type",
		'TNAM',
		/* [12] */
		"Code resource ID",
		'RSID',
		/* [13] */
		"Name resource type",
		'TNAM',
		/* [14] */
		"Name resource ID",
		'RSID',
		/* [15] */
		"Info resource type",
		'TNAM',
		/* [16] */
		"Info resource ID",
		'RSID',
		/* [17] */
		"Icon resource type",
		'TNAM',
		/* [18] */
		"Icon resource ID",
		'RSID',
		/* [19] */
		"Version of Component",
		'HLNG',
		/* [20] */
		"Registration flags",
		'DVDR',
		/* [21] */
		"Reserved",
		'LB28',
		/* [22] */
		"Has code for multiple platforms",
		'LBIT',
		/* [23] */
		"Use component flags in search",
		'LBIT',
		/* [24] */
		"Call component when un-registered",
		'LBIT',
		/* [25] */
		"Use only latest version",
		'LBIT',
		/* [26] */
		"Resource ID of icon family",
		'RSID',
		/* [27] */
		"Count:",
		'LCNT',
		/* [28] */
		"Component Platform Info records",
		'LSTC',
		/* [29] */
		"Component wants to be registered at star"
		"tup",
		'LB01',
		/* [30] */
		"Use fast dispatch when calling component",
		'LB01',
		/* [31] */
		"Reserved",
		'LB06',
		/* [32] */
		"Type flags",
		'LB08',
		/* [33] */
		"Sub-type flags",
		'LB08',
		/* [34] */
		"Manufacturer flags",
		'LB08',
		/* [35] */
		"Code resource type",
		'TNAM',
		/* [36] */
		"Code resource ID",
		'RSID',
		/* [37] */
		"Platform type (gestaltComponentPlatform)",
		'DWRD',
		/* [38] */
		"68K=1",
		'CASE',
		/* [39] */
		"PowerPC=2",
		'CASE',
		/* [40] */
		"Interpreted=3",
		'CASE',
		/* [41] */
		"Win32=4",
		'CASE',
		/* [42] */
		"PPCNativeEntryPoint=5",
		'CASE',
		/* [43] */
		"-----",
		'LSTE',
		/* [44] */
		"Resource map type",
		'TNAM',
		/* [45] */
		"Resource map ID",
		'RSID'
	}
};

resource 'TMPL' (1369, "thnr") {
	{	/* array: 8 elements */
		/* [1] */
		"Components public resource maps",
		'LSTB',
		/* [2] */
		"Thing resource type",
		'TNAM',
		/* [3] */
		"Thing resource ID",
		'DWRD',
		/* [4] */
		"Unused flags",
		'DWRD',
		/* [5] */
		"Mac resource type",
		'TNAM',
		/* [6] */
		"Mac resource ID",
		'DWRD',
		/* [7] */
		"Flags",
		'DWRD',
		/* [8] */
		"-----",
		'LSTE'
	}
};

resource 'TMPL' (1370, "THUM") {
	{	/* array: 6 elements */
		/* [1] */
		"\"AfterDark\" resource format",
		'DVDR',
		/* [2] */
		"Total animation time (ticks)",
		'DWRD',
		/* [3] */
		"Count:",
		'ZCNT',
		/* [4] */
		"Frames",
		'LSTC',
		/* [5] */
		"Icon resource ID",
		'DWRD',
		/* [6] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1371, "tic#") {
	{	/* array: 6 elements */
		/* [1] */
		"Theme File Icon List (ID 384)",
		'DVDR',
		/* [2] */
		"Count:",
		'LCNT',
		/* [3] */
		"Icon families",
		'LSTC',
		/* [4] */
		"File Type",
		'TNAM',
		/* [5] */
		"'icns' ID",
		'RSID',
		/* [6] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1372, "TMPL") {
	{	/* array: 4 elements */
		/* [1] */
		"List of template fields",
		'LSTB',
		/* [2] */
		"Label",
		'PSTR',
		/* [3] */
		"Type",
		'TNAM',
		/* [4] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1373, "TOOL") {
	{	/* array: 5 elements */
		/* [1] */
		"Tools per row",
		'DWRD',
		/* [2] */
		"Number of rows",
		'DWRD',
		/* [3] */
		"Rows",
		'LSTB',
		/* [4] */
		"Tool cursor ID",
		'DWRD',
		/* [5] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1374, "TPal") {
	{	/* array: 13 elements */
		/* [1] */
		"\"Finale\" resource format",
		'DVDR',
		/* [2] */
		"Draw type",
		'DWRD',
		/* [3] */
		"Cell height",
		'DWRD',
		/* [4] */
		"Cell width",
		'DWRD',
		/* [5] */
		"Resouce ID of tool SICNs",
		'DWRD',
		/* [6] */
		"Resouce ID of tool names",
		'DWRD',
		/* [7] */
		"Base resource ID of icon family resource"
		"s",
		'DWRD',
		/* [8] */
		"Count:",
		'OCNT',
		/* [9] */
		"Tools array",
		'LSTC',
		/* [10] */
		"Tool ID",
		'DWRD',
		/* [11] */
		"Tool icon index",
		'DWRD',
		/* [12] */
		"Tool name index",
		'DWRD',
		/* [13] */
		"****",
		'LSTE'
	}
};

resource 'TMPL' (1375, "tray") {
	{	/* array: 2 elements */
		/* [1] */
		"Tray count",
		'DLNG',
		/* [2] */
		"Usual=1",
		'CASE'
	}
};

resource 'TMPL' (1376, "trsl") {
	{	/* array: 44 elements */
		/* [1] */
		"To convert from all text, set all 16 fol"
		"lowing bits.",
		'DVDR',
		/* [2] */
		"Bit 15",
		'WBIT',
		/* [3] */
		"Bit 14",
		'WBIT',
		/* [4] */
		"Bit 13",
		'WBIT',
		/* [5] */
		"Convert from 2-byte ZhuYinFuHao text",
		'WBIT',
		/* [6] */
		"Korean scripts",
		'DVDR',
		/* [7] */
		"Bit 11",
		'WBIT',
		/* [8] */
		"Bit 10",
		'WBIT',
		/* [9] */
		"Convert from 2-byte Jamo text",
		'WBIT',
		/* [10] */
		"Convert from 2-byte Hangul text",
		'WBIT',
		/* [11] */
		"Japanese scripts",
		'DVDR',
		/* [12] */
		"Convert from 2-byte Hiragana text",
		'WBIT',
		/* [13] */
		"Bit 6",
		'WBIT',
		/* [14] */
		"Convert from 2-byte Katakana text",
		'WBIT',
		/* [15] */
		"Convert from 1-byte Katakana text",
		'WBIT',
		/* [16] */
		"All scripts",
		'DVDR',
		/* [17] */
		"Convert from 2-byte Roman text",
		'WBIT',
		/* [18] */
		"Convert from 1-byte Roman text",
		'WBIT',
		/* [19] */
		"Convert from text native to current scri"
		"pt",
		'WBIT',
		/* [20] */
		"Convert from Roman text",
		'WBIT',
		/* [21] */
		"Target type",
		'DVDR',
		/* [22] */
		"Target becomes uppercase",
		'BBIT',
		/* [23] */
		"Target becomes lowercase",
		'BBIT',
		/* [24] */
		"Reserved",
		'BB06',
		/* [25] */
		"Target format",
		'DBYT',
		/* [26] */
		"Convert to Roman=0",
		'CASE',
		/* [27] */
		"Convert to subscript native to current s"
		"cript=1",
		'CASE',
		/* [28] */
		"Convert to 1-byte Roman text=2",
		'CASE',
		/* [29] */
		"Convert to 2-byte Roman text=3",
		'CASE',
		/* [30] */
		"Convert to 1-byte Katakana text=4",
		'CASE',
		/* [31] */
		"Convert to 2-byte Katakana text=5",
		'CASE',
		/* [32] */
		"Convert to 2-byte Hiragana text=7",
		'CASE',
		/* [33] */
		"Convert to 2-byte Hangul text=8",
		'CASE',
		/* [34] */
		"Convert to 2-byte Jamo text=9",
		'CASE',
		/* [35] */
		"Convert to 2-byte Zhuyinfuhao text=10",
		'CASE',
		/* [36] */
		"Format code",
		'DWRD',
		/* [37] */
		"Reserved",
		'WB14',
		/* [38] */
		"Convert all Roman chars to uppercase bef"
		"ore transliteration",
		'WBIT',
		/* [39] */
		"Convert all 1-byte chars to 2-byte chars"
		" before transliteration",
		'WBIT',
		/* [40] */
		"Extra rules",
		'DVDR',
		/* [41] */
		"Count:",
		'OCNT',
		/* [42] */
		"List of Rules",
		'LSTC',
		/* [43] */
		"Rule (input space output)",
		'BSTR',
		/* [44] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1377, "TTBL") {
	{	/* array: 6 elements */
		/* [1] */
		"\"SuitCase\" resource format",
		'DVDR',
		/* [2] */
		"Character Translation",
		'LSTB',
		/* [3] */
		"From:",
		'CHAR',
		/* [4] */
		"Pad Byte",
		'FBYT',
		/* [5] */
		"To:",
		'P006',
		/* [6] */
		"",
		'LSTE'
	}
};

resource 'TMPL' (1378, "tVal") {
	{	/* array: 2 elements */
		/* [1] */
		"\"AfterDark\" resource format",
		'DVDR',
		/* [2] */
		"String # to display - Decimal",
		'DWRD'
	}
};

resource 'TMPL' (1379, "tvar") {
	{	/* array: 10 elements */
		/* [1] */
		"Theme Variants (must have ID 128)",
		'DVDR',
		/* [2] */
		"Version",
		'DWRD',
		/* [3] */
		"default=0",
		'CASE',
		/* [4] */
		"Index of default variant",
		'DWRD',
		/* [5] */
		"Count:",
		'OCNT',
		/* [6] */
		"Variants",
		'LSTC',
		/* [7] */
		"Name",
		'PSTR',
		/* [8] */
		"'clut' ID:",
		'RSID',
		/* [9] */
		"Color",
		'COLR',
		/* [10] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1380, "TxSt") {
	{	/* array: 12 elements */
		/* [1] */
		"Unused",
		'BBIT',
		/* [2] */
		"Extend",
		'BBIT',
		/* [3] */
		"Condense",
		'BBIT',
		/* [4] */
		"Shadow",
		'BBIT',
		/* [5] */
		"Outline",
		'BBIT',
		/* [6] */
		"Underline",
		'BBIT',
		/* [7] */
		"Italic",
		'BBIT',
		/* [8] */
		"Bold",
		'BBIT',
		/* [9] */
		"Filler",
		'FBYT',
		/* [10] */
		"Font size",
		'DWRD',
		/* [11] */
		"Font color",
		'COLR',
		/* [12] */
		"Font name",
		'PSTR'
	}
};

resource 'TMPL' (1381, "Txtr") {
	{	/* array: 43 elements */
		/* [1] */
		"Size",
		'DWRD',
		/* [2] */
		"Default=0",
		'CASE',
		/* [3] */
		"9=9",
		'CASE',
		/* [4] */
		"10=10",
		'CASE',
		/* [5] */
		"12=12",
		'CASE',
		/* [6] */
		"Style",
		'WORV',
		/* [7] */
		"Plain=0",
		'CASE',
		/* [8] */
		"Bold=1",
		'CASE',
		/* [9] */
		"Italic=2",
		'CASE',
		/* [10] */
		"Underline=4",
		'CASE',
		/* [11] */
		"Outline=8",
		'CASE',
		/* [12] */
		"Shadow=16",
		'CASE',
		/* [13] */
		"Condense=32",
		'CASE',
		/* [14] */
		"Extend=64",
		'CASE',
		/* [15] */
		"Justification",
		'DWRD',
		/* [16] */
		"Flush Default=0",
		'CASE',
		/* [17] */
		"Center=1",
		'CASE',
		/* [18] */
		"Flush Right=-1",
		'CASE',
		/* [19] */
		"Flush Left=-2",
		'CASE',
		/* [20] */
		"Mode",
		'DWRD',
		/* [21] */
		"Copy=0",
		'CASE',
		/* [22] */
		"Or=1",
		'CASE',
		/* [23] */
		"Xor=2",
		'CASE',
		/* [24] */
		"Bic=3",
		'CASE',
		/* [25] */
		"Not Copy=4",
		'CASE',
		/* [26] */
		"Not Or=5",
		'CASE',
		/* [27] */
		"Not Xor=6",
		'CASE',
		/* [28] */
		"Not Bic=7",
		'CASE',
		/* [29] */
		"Blend=32",
		'CASE',
		/* [30] */
		"Add Pin=33",
		'CASE',
		/* [31] */
		"Add Over=34",
		'CASE',
		/* [32] */
		"Sub Pin=35",
		'CASE',
		/* [33] */
		"Transparent=36",
		'CASE',
		/* [34] */
		"Add Max=37",
		'CASE',
		/* [35] */
		"Sub Over=38",
		'CASE',
		/* [36] */
		"Add Min=39",
		'CASE',
		/* [37] */
		"Grayish Text Or=49",
		'CASE',
		/* [38] */
		"Hilite Transfer Mode=50",
		'CASE',
		/* [39] */
		"Dither Copy=64",
		'CASE',
		/* [40] */
		"Color",
		'COLR',
		/* [41] */
		"Font Number",
		'DWRD',
		/* [42] */
		"Use font name=-1",
		'CASE',
		/* [43] */
		"Font name",
		'PSTR'
	}
};

resource 'TMPL' (1382, "TXTs") {
	{	/* array: 2 elements */
		/* [1] */
		"\"Fetch\" resource template",
		'DVDR',
		/* [2] */
		"Text File Creator",
		'TNAM'
	}
};

resource 'TMPL' (1383, "typ#") {
	{	/* array: 4 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"Types list",
		'LSTC',
		/* [3] */
		"Type",
		'TNAM',
		/* [4] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1384, "TYPs") {
	{	/* array: 3 elements */
		/* [1] */
		"\"Fetch\" resource template",
		'DVDR',
		/* [2] */
		"File Type",
		'TNAM',
		/* [3] */
		"File Creator",
		'TNAM'
	}
};

resource 'TMPL' (1385, "url ") {
	{	/* array: 1 elements */
		/* [1] */
		"URL string",
		'CSTR'
	}
};

resource 'TMPL' (1386, "VECP") {
	{	/* array: 6 elements */
		/* [1] */
		"Count:",
		'OCNT',
		/* [2] */
		"List of panes",
		'LSTC',
		/* [3] */
		"Catalog pane type",
		'TNAM',
		/* [4] */
		"Catalog pane icon ID",
		'DWRD',
		/* [5] */
		"Catalog pane label",
		'PSTR',
		/* [6] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1387, "vers") {
	{	/* array: 11 elements */
		/* [1] */
		"Version number",
		'HBYT',
		/* [2] */
		"Revision number",
		'HBYT',
		/* [3] */
		"Revision stage",
		'HBYT',
		/* [4] */
		"Final=$80",
		'CASE',
		/* [5] */
		"Beta=$60",
		'CASE',
		/* [6] */
		"Alpha=$40",
		'CASE',
		/* [7] */
		"Development=$20",
		'CASE',
		/* [8] */
		"Build number",
		'HBYT',
		/* [9] */
		"Language integer",
		'DWRD',
		/* [10] */
		"Abbreviated string",
		'PSTR',
		/* [11] */
		"Get Info string",
		'PSTR'
	}
};

resource 'TMPL' (1388, "VFlg") {
	{	/* array: 2 elements */
		/* [1] */
		"Obey DIV \"align\" tag",
		'LBIT',
		/* [2] */
		"Reserved",
		'LB31'
	}
};

resource 'TMPL' (1389, "view") {
	{	/* array: 909 elements */
		/* [1] */
		"Views",
		'OCNT',
		/* [2] */
		"*****",
		'LSTC',
		/* [3] */
		"Signature of ancestral view",
		'TNAM',
		/* [4] */
		"Root=    ",
		'CASE',
		/* [5] */
		"Identifier for this view",
		'TNAM',
		/* [6] */
		"No ID=    ",
		'CASE',
		/* [7] */
		"Vertical position within parent view",
		'DLNG',
		/* [8] */
		"Horizontal position within parent view",
		'DLNG',
		/* [9] */
		"View height",
		'DLNG',
		/* [10] */
		"View width",
		'DLNG',
		/* [11] */
		"Vertical view handling",
		'WB03',
		/* [12] */
		"Same height as superview=0",
		'CASE',
		/* [13] */
		"Height is relative to superview=1",
		'CASE',
		/* [14] */
		"Height should be one page=2",
		'CASE',
		/* [15] */
		"Fill an exact number of pages=3",
		'CASE',
		/* [16] */
		"Application-specific height=4",
		'CASE',
		/* [17] */
		"Fixed height (no special handling)=5",
		'CASE',
		/* [18] */
		"Horizontal view handling",
		'WB03',
		/* [19] */
		"Same width as superview=0",
		'CASE',
		/* [20] */
		"Width is relative to superview=1",
		'CASE',
		/* [21] */
		"Width should be one page=2",
		'CASE',
		/* [22] */
		"Fill an exact number of pages=3",
		'CASE',
		/* [23] */
		"Application-specific width=4",
		'CASE',
		/* [24] */
		"Fixed width (no special handling)=5",
		'CASE',
		/* [25] */
		"Show view",
		'WBIT',
		/* [26] */
		"Enable view",
		'WBIT',
		/* [27] */
		"Unused",
		'WB08',
		/* [28] */
		"View type",
		'KTYP',
		/* [29] */
		"Include a view=incl",
		'CASE',
		/* [30] */
		"Include view at=inc@",
		'CASE',
		/* [31] */
		"View=view",
		'CASE',
		/* [32] */
		"Default view=dflt",
		'CASE',
		/* [33] */
		"Window=wind",
		'CASE',
		/* [34] */
		"Scroller=scrl",
		'CASE',
		/* [35] */
		"Dialog view=dlog",
		'CASE',
		/* [36] */
		"Control=cntl",
		'CASE',
		/* [37] */
		"Button=butn",
		'CASE',
		/* [38] */
		"Check box=chkb",
		'CASE',
		/* [39] */
		"Radio button=radb",
		'CASE',
		/* [40] */
		"Scroll bar=sbar",
		'CASE',
		/* [41] */
		"Cluster=clus",
		'CASE',
		/* [42] */
		"Icon=icon",
		'CASE',
		/* [43] */
		"Pattern=patn",
		'CASE',
		/* [44] */
		"Picture=pict",
		'CASE',
		/* [45] */
		"Popup Menu=popp",
		'CASE',
		/* [46] */
		"Static text=stat",
		'CASE',
		/* [47] */
		"Edit text=edit",
		'CASE',
		/* [48] */
		"Number text=nmbr",
		'CASE',
		/* [49] */
		"TextEdit=tevw",
		'CASE',
		/* [50] */
		"Grid=grid",
		'CASE',
		/* [51] */
		"Text grid=txtg",
		'CASE',
		/* [52] */
		"Text list=lstg",
		'CASE',
		/* [53] */
		"Other=othr",
		'CASE',
		/* [54] */
		"incl",
		'KEYB',
		/* [55] */
		"Resource ID of 'view' to include",
		'RSID',
		/* [56] */
		"",
		'KEYE',
		/* [57] */
		"inc@",
		'KEYB',
		/* [58] */
		"Resource ID of 'view' to include at",
		'RSID',
		/* [59] */
		"Y offset for sub-views",
		'DLNG',
		/* [60] */
		"X offset for sub-views",
		'DLNG',
		/* [61] */
		"",
		'KEYE',
		/* [62] */
		"view",
		'KEYB',
		/* [63] */
		"Class name",
		'ESTR',
		/* [64] */
		"Usual=TView",
		'CASE',
		/* [65] */
		"",
		'KEYE',
		/* [66] */
		"dflt",
		'KEYB',
		/* [67] */
		"Class name",
		'ESTR',
		/* [68] */
		"Usual=TDefaultView",
		'CASE',
		/* [69] */
		"",
		'KEYE',
		/* [70] */
		"wind",
		'KEYB',
		/* [71] */
		"Class name",
		'ESTR',
		/* [72] */
		"Usual=TWindow",
		'CASE',
		/* [73] */
		"Resource ID of 'WDEF'",
		'WB12',
		/* [74] */
		"Standard system=0",
		'CASE',
		/* [75] */
		"Standard accessory=1",
		'CASE',
		/* [76] */
		"Variation code",
		'WB04',
		/* [77] */
		"Document/accessory=0",
		'CASE',
		/* [78] */
		"Modal dialog=1",
		'CASE',
		/* [79] */
		"Plain frame=2",
		'CASE',
		/* [80] */
		"Shadow frame=3",
		'CASE',
		/* [81] */
		"No grow document=4",
		'CASE',
		/* [82] */
		"Moveable modal=5",
		'CASE',
		/* [83] */
		"Zoomable document=8",
		'CASE',
		/* [84] */
		"No grow, zoomable document=12",
		'CASE',
		/* [85] */
		"Window has GoAway box",
		'WBIT',
		/* [86] */
		"Window is resizeable",
		'WBIT',
		/* [87] */
		"Window is modal",
		'WBIT',
		/* [88] */
		"Window accepts first click",
		'WBIT',
		/* [89] */
		"Free window on closing",
		'WBIT',
		/* [90] */
		"Dispose window on freeing",
		'WBIT',
		/* [91] */
		"Closes document",
		'WBIT',
		/* [92] */
		"Open with document",
		'WBIT',
		/* [93] */
		"Adapt to screen",
		'WBIT',
		/* [94] */
		"Stagger",
		'WBIT',
		/* [95] */
		"Force onto screen",
		'WBIT',
		/* [96] */
		"Centering",
		'WB02',
		/* [97] */
		"Leave as is=0",
		'CASE',
		/* [98] */
		"Horizontally=1",
		'CASE',
		/* [99] */
		"Vertically=2",
		'CASE',
		/* [100] */
		"Both=3",
		'CASE',
		/* [101] */
		"Reserved",
		'WB03',
		/* [102] */
		"ID of target view",
		'TNAM',
		/* [103] */
		"No ID=    ",
		'CASE',
		/* [104] */
		"Window title",
		'ESTR',
		/* [105] */
		"",
		'KEYE',
		/* [106] */
		"scrl",
		'KEYB',
		/* [107] */
		"Class name",
		'ESTR',
		/* [108] */
		"Usual=TScroller",
		'CASE',
		/* [109] */
		"Has vertical scroll bar",
		'DBYT',
		/* [110] */
		"No=0",
		'CASE',
		/* [111] */
		"Yes=1",
		'CASE',
		/* [112] */
		"Has horizontal scroll bar",
		'DBYT',
		/* [113] */
		"No=0",
		'CASE',
		/* [114] */
		"Yes=1",
		'CASE',
		/* [115] */
		"Vertical maximum value",
		'DLNG',
		/* [116] */
		"Horizontal maximum value",
		'DLNG',
		/* [117] */
		"Vertical scroll units",
		'DWRD',
		/* [118] */
		"Horizontal scroll units",
		'DWRD',
		/* [119] */
		"Vertical constraint",
		'DBYT',
		/* [120] */
		"No=0",
		'CASE',
		/* [121] */
		"Yes=1",
		'CASE',
		/* [122] */
		"Horizontal constraint",
		'DBYT',
		/* [123] */
		"No=0",
		'CASE',
		/* [124] */
		"Yes=1",
		'CASE',
		/* [125] */
		"Scroll bar offsets",
		'RECT',
		/* [126] */
		"",
		'KEYE',
		/* [127] */
		"dlog",
		'KEYB',
		/* [128] */
		"Class name",
		'ESTR',
		/* [129] */
		"Usual=TDialogView",
		'CASE',
		/* [130] */
		"ID of default item",
		'TNAM',
		/* [131] */
		"No default=    ",
		'CASE',
		/* [132] */
		"ID of cancel item",
		'TNAM',
		/* [133] */
		"No cancel=    ",
		'CASE',
		/* [134] */
		"",
		'KEYE',
		/* [135] */
		"cntl",
		'KEYB',
		/* [136] */
		"Class name",
		'ESTR',
		/* [137] */
		"Usual=TControl",
		'CASE',
		/* [138] */
		"TControlData",
		'DVDR',
		/* [139] */
		"Line adornment",
		'WB04',
		/* [140] */
		"No lines=0",
		'CASE',
		/* [141] */
		"Frame=15",
		'CASE',
		/* [142] */
		"Along top=1",
		'CASE',
		/* [143] */
		"Along left=2",
		'CASE',
		/* [144] */
		"Along bottom=4",
		'CASE',
		/* [145] */
		"ALong right=8",
		'CASE',
		/* [146] */
		"Pattern fill",
		'WBIT',
		/* [147] */
		"Use oval",
		'WBIT',
		/* [148] */
		"Use RoundRect",
		'WBIT',
		/* [149] */
		"Use Shadow",
		'WBIT',
		/* [150] */
		"Reserved",
		'WB08',
		/* [151] */
		"Pen size",
		'PNT ',
		/* [152] */
		"Control is sizeable",
		'WBIT',
		/* [153] */
		"Control is dimmed",
		'WBIT',
		/* [154] */
		"Control is hilited",
		'WBIT',
		/* [155] */
		"Control dismisses",
		'WBIT',
		/* [156] */
		"Reserved",
		'WB12',
		/* [157] */
		"Control inset",
		'RECT',
		/* [158] */
		"Font style",
		'BORV',
		/* [159] */
		"Plain=0",
		'CASE',
		/* [160] */
		"Bold=1",
		'CASE',
		/* [161] */
		"Italic=2",
		'CASE',
		/* [162] */
		"Underline=4",
		'CASE',
		/* [163] */
		"Outline=8",
		'CASE',
		/* [164] */
		"Shadow=16",
		'CASE',
		/* [165] */
		"Condensed=32",
		'CASE',
		/* [166] */
		"Extended=64",
		'CASE',
		/* [167] */
		"Filler",
		'FBYT',
		/* [168] */
		"Font size",
		'DWRD',
		/* [169] */
		"SystemFont=0",
		'CASE',
		/* [170] */
		"Small applFont=9",
		'CASE',
		/* [171] */
		"Large applFont=12",
		'CASE',
		/* [172] */
		"Font color",
		'COLR',
		/* [173] */
		"Font name",
		'ESTR',
		/* [174] */
		"",
		'KEYE',
		/* [175] */
		"butn",
		'KEYB',
		/* [176] */
		"Class name",
		'ESTR',
		/* [177] */
		"Usual=TButton",
		'CASE',
		/* [178] */
		"TControlData",
		'DVDR',
		/* [179] */
		"Line adornment",
		'WB04',
		/* [180] */
		"No lines=0",
		'CASE',
		/* [181] */
		"Frame=15",
		'CASE',
		/* [182] */
		"Along top=1",
		'CASE',
		/* [183] */
		"Along left=2",
		'CASE',
		/* [184] */
		"Along bottom=4",
		'CASE',
		/* [185] */
		"ALong right=8",
		'CASE',
		/* [186] */
		"Pattern fill",
		'WBIT',
		/* [187] */
		"Use oval",
		'WBIT',
		/* [188] */
		"Use RoundRect",
		'WBIT',
		/* [189] */
		"Use Shadow",
		'WBIT',
		/* [190] */
		"Reserved",
		'WB08',
		/* [191] */
		"Pen size",
		'PNT ',
		/* [192] */
		"Control is sizeable",
		'WBIT',
		/* [193] */
		"Control is dimmed",
		'WBIT',
		/* [194] */
		"Control is hilited",
		'WBIT',
		/* [195] */
		"Control dismisses",
		'WBIT',
		/* [196] */
		"Reserved",
		'WB12',
		/* [197] */
		"Control inset",
		'RECT',
		/* [198] */
		"Font style",
		'BORV',
		/* [199] */
		"Plain=0",
		'CASE',
		/* [200] */
		"Bold=1",
		'CASE',
		/* [201] */
		"Italic=2",
		'CASE',
		/* [202] */
		"Underline=4",
		'CASE',
		/* [203] */
		"Outline=8",
		'CASE',
		/* [204] */
		"Shadow=16",
		'CASE',
		/* [205] */
		"Condensed=32",
		'CASE',
		/* [206] */
		"Extended=64",
		'CASE',
		/* [207] */
		"Filler",
		'FBYT',
		/* [208] */
		"Font size",
		'DWRD',
		/* [209] */
		"SystemFont=0",
		'CASE',
		/* [210] */
		"Small applFont=9",
		'CASE',
		/* [211] */
		"Large applFont=12",
		'CASE',
		/* [212] */
		"Font color",
		'COLR',
		/* [213] */
		"Font name",
		'ESTR',
		/* [214] */
		"TButtonData",
		'DVDR',
		/* [215] */
		"Button title",
		'ESTR',
		/* [216] */
		"",
		'KEYE',
		/* [217] */
		"chkb",
		'KEYB',
		/* [218] */
		"Class name",
		'ESTR',
		/* [219] */
		"Usual=TCheckBox",
		'CASE',
		/* [220] */
		"TControlData",
		'DVDR',
		/* [221] */
		"Line adornment",
		'WB04',
		/* [222] */
		"No lines=0",
		'CASE',
		/* [223] */
		"Frame=15",
		'CASE',
		/* [224] */
		"Along top=1",
		'CASE',
		/* [225] */
		"Along left=2",
		'CASE',
		/* [226] */
		"Along bottom=4",
		'CASE',
		/* [227] */
		"ALong right=8",
		'CASE',
		/* [228] */
		"Pattern fill",
		'WBIT',
		/* [229] */
		"Use oval",
		'WBIT',
		/* [230] */
		"Use RoundRect",
		'WBIT',
		/* [231] */
		"Use Shadow",
		'WBIT',
		/* [232] */
		"Reserved",
		'WB08',
		/* [233] */
		"Pen size",
		'PNT ',
		/* [234] */
		"Control is sizeable",
		'WBIT',
		/* [235] */
		"Control is dimmed",
		'WBIT',
		/* [236] */
		"Control is hilited",
		'WBIT',
		/* [237] */
		"Control dismisses",
		'WBIT',
		/* [238] */
		"Reserved",
		'WB12',
		/* [239] */
		"Control inset",
		'RECT',
		/* [240] */
		"Font style",
		'BORV',
		/* [241] */
		"Plain=0",
		'CASE',
		/* [242] */
		"Bold=1",
		'CASE',
		/* [243] */
		"Italic=2",
		'CASE',
		/* [244] */
		"Underline=4",
		'CASE',
		/* [245] */
		"Outline=8",
		'CASE',
		/* [246] */
		"Shadow=16",
		'CASE',
		/* [247] */
		"Condensed=32",
		'CASE',
		/* [248] */
		"Extended=64",
		'CASE',
		/* [249] */
		"Filler",
		'FBYT',
		/* [250] */
		"Font size",
		'DWRD',
		/* [251] */
		"SystemFont=0",
		'CASE',
		/* [252] */
		"Small applFont=9",
		'CASE',
		/* [253] */
		"Large applFont=12",
		'CASE',
		/* [254] */
		"Font color",
		'COLR',
		/* [255] */
		"Font name",
		'ESTR',
		/* [256] */
		"TCheckboxData",
		'DVDR',
		/* [257] */
		"Initial state",
		'DBYT',
		/* [258] */
		"Off=0",
		'CASE',
		/* [259] */
		"On=1",
		'CASE',
		/* [260] */
		"Filler",
		'FBYT',
		/* [261] */
		"Check box label",
		'ESTR',
		/* [262] */
		"",
		'KEYE',
		/* [263] */
		"radb",
		'KEYB',
		/* [264] */
		"Class name",
		'ESTR',
		/* [265] */
		"Usual=TRadioButton",
		'CASE',
		/* [266] */
		"TControlData",
		'DVDR',
		/* [267] */
		"Line adornment",
		'WB04',
		/* [268] */
		"No lines=0",
		'CASE',
		/* [269] */
		"Frame=15",
		'CASE',
		/* [270] */
		"Along top=1",
		'CASE',
		/* [271] */
		"Along left=2",
		'CASE',
		/* [272] */
		"Along bottom=4",
		'CASE',
		/* [273] */
		"ALong right=8",
		'CASE',
		/* [274] */
		"Pattern fill",
		'WBIT',
		/* [275] */
		"Use oval",
		'WBIT',
		/* [276] */
		"Use RoundRect",
		'WBIT',
		/* [277] */
		"Use Shadow",
		'WBIT',
		/* [278] */
		"Reserved",
		'WB08',
		/* [279] */
		"Pen size",
		'PNT ',
		/* [280] */
		"Control is sizeable",
		'WBIT',
		/* [281] */
		"Control is dimmed",
		'WBIT',
		/* [282] */
		"Control is hilited",
		'WBIT',
		/* [283] */
		"Control dismisses",
		'WBIT',
		/* [284] */
		"Reserved",
		'WB12',
		/* [285] */
		"Control inset",
		'RECT',
		/* [286] */
		"Font style",
		'BORV',
		/* [287] */
		"Plain=0",
		'CASE',
		/* [288] */
		"Bold=1",
		'CASE',
		/* [289] */
		"Italic=2",
		'CASE',
		/* [290] */
		"Underline=4",
		'CASE',
		/* [291] */
		"Outline=8",
		'CASE',
		/* [292] */
		"Shadow=16",
		'CASE',
		/* [293] */
		"Condensed=32",
		'CASE',
		/* [294] */
		"Extended=64",
		'CASE',
		/* [295] */
		"Filler",
		'FBYT',
		/* [296] */
		"Font size",
		'DWRD',
		/* [297] */
		"SystemFont=0",
		'CASE',
		/* [298] */
		"Small applFont=9",
		'CASE',
		/* [299] */
		"Large applFont=12",
		'CASE',
		/* [300] */
		"Font color",
		'COLR',
		/* [301] */
		"Font name",
		'ESTR',
		/* [302] */
		"TRadioData",
		'DVDR',
		/* [303] */
		"Initial state",
		'DBYT',
		/* [304] */
		"Off=0",
		'CASE',
		/* [305] */
		"On=1",
		'CASE',
		/* [306] */
		"Filler",
		'FBYT',
		/* [307] */
		"Radio button label",
		'ESTR',
		/* [308] */
		"",
		'KEYE',
		/* [309] */
		"sbar",
		'KEYB',
		/* [310] */
		"Class name",
		'ESTR',
		/* [311] */
		"Usual=TScrollBar",
		'CASE',
		/* [312] */
		"TControlData",
		'DVDR',
		/* [313] */
		"Line adornment",
		'WB04',
		/* [314] */
		"No lines=0",
		'CASE',
		/* [315] */
		"Frame=15",
		'CASE',
		/* [316] */
		"Along top=1",
		'CASE',
		/* [317] */
		"Along left=2",
		'CASE',
		/* [318] */
		"Along bottom=4",
		'CASE',
		/* [319] */
		"ALong right=8",
		'CASE',
		/* [320] */
		"Pattern fill",
		'WBIT',
		/* [321] */
		"Use oval",
		'WBIT',
		/* [322] */
		"Use RoundRect",
		'WBIT',
		/* [323] */
		"Use Shadow",
		'WBIT',
		/* [324] */
		"Reserved",
		'WB08',
		/* [325] */
		"Pen size",
		'PNT ',
		/* [326] */
		"Control is sizeable",
		'WBIT',
		/* [327] */
		"Control is dimmed",
		'WBIT',
		/* [328] */
		"Control is hilited",
		'WBIT',
		/* [329] */
		"Control dismisses",
		'WBIT',
		/* [330] */
		"Reserved",
		'WB12',
		/* [331] */
		"Control inset",
		'RECT',
		/* [332] */
		"Font style",
		'BORV',
		/* [333] */
		"Plain=0",
		'CASE',
		/* [334] */
		"Bold=1",
		'CASE',
		/* [335] */
		"Italic=2",
		'CASE',
		/* [336] */
		"Underline=4",
		'CASE',
		/* [337] */
		"Outline=8",
		'CASE',
		/* [338] */
		"Shadow=16",
		'CASE',
		/* [339] */
		"Condensed=32",
		'CASE',
		/* [340] */
		"Extended=64",
		'CASE',
		/* [341] */
		"Filler",
		'FBYT',
		/* [342] */
		"Font size",
		'DWRD',
		/* [343] */
		"SystemFont=0",
		'CASE',
		/* [344] */
		"Small applFont=9",
		'CASE',
		/* [345] */
		"Large applFont=12",
		'CASE',
		/* [346] */
		"Font color",
		'COLR',
		/* [347] */
		"Font name",
		'ESTR',
		/* [348] */
		"TScrollBarData",
		'DVDR',
		/* [349] */
		"Initial value",
		'DLNG',
		/* [350] */
		"Minimum value",
		'DLNG',
		/* [351] */
		"Maximum value",
		'DLNG',
		/* [352] */
		"",
		'KEYE',
		/* [353] */
		"clus",
		'KEYB',
		/* [354] */
		"Class name",
		'ESTR',
		/* [355] */
		"Usual=TCluster",
		'CASE',
		/* [356] */
		"TControlData",
		'DVDR',
		/* [357] */
		"Line adornment",
		'WB04',
		/* [358] */
		"Frame=15",
		'CASE',
		/* [359] */
		"No lines=0",
		'CASE',
		/* [360] */
		"Along top=1",
		'CASE',
		/* [361] */
		"Along left=2",
		'CASE',
		/* [362] */
		"Along bottom=4",
		'CASE',
		/* [363] */
		"ALong right=8",
		'CASE',
		/* [364] */
		"Pattern fill",
		'WBIT',
		/* [365] */
		"Use oval",
		'WBIT',
		/* [366] */
		"Use RoundRect",
		'WBIT',
		/* [367] */
		"Use Shadow",
		'WBIT',
		/* [368] */
		"Reserved",
		'WB08',
		/* [369] */
		"Pen size",
		'PNT ',
		/* [370] */
		"Control is sizeable",
		'WBIT',
		/* [371] */
		"Control is dimmed",
		'WBIT',
		/* [372] */
		"Control is hilited",
		'WBIT',
		/* [373] */
		"Control dismisses",
		'WBIT',
		/* [374] */
		"Reserved",
		'WB12',
		/* [375] */
		"Control inset",
		'RECT',
		/* [376] */
		"Font style",
		'BORV',
		/* [377] */
		"Plain=0",
		'CASE',
		/* [378] */
		"Bold=1",
		'CASE',
		/* [379] */
		"Italic=2",
		'CASE',
		/* [380] */
		"Underline=4",
		'CASE',
		/* [381] */
		"Outline=8",
		'CASE',
		/* [382] */
		"Shadow=16",
		'CASE',
		/* [383] */
		"Condensed=32",
		'CASE',
		/* [384] */
		"Extended=64",
		'CASE',
		/* [385] */
		"Filler",
		'FBYT',
		/* [386] */
		"Font size",
		'DWRD',
		/* [387] */
		"SystemFont=0",
		'CASE',
		/* [388] */
		"Small applFont=9",
		'CASE',
		/* [389] */
		"Large applFont=12",
		'CASE',
		/* [390] */
		"Font color",
		'COLR',
		/* [391] */
		"Font name",
		'ESTR',
		/* [392] */
		"TClusterData",
		'DVDR',
		/* [393] */
		"Cluster label",
		'ESTR',
		/* [394] */
		"",
		'KEYE',
		/* [395] */
		"icon",
		'KEYB',
		/* [396] */
		"Class name",
		'ESTR',
		/* [397] */
		"Usual=TIcon",
		'CASE',
		/* [398] */
		"TControlData",
		'DVDR',
		/* [399] */
		"Line adornment",
		'WB04',
		/* [400] */
		"No lines=0",
		'CASE',
		/* [401] */
		"Frame=15",
		'CASE',
		/* [402] */
		"Along top=1",
		'CASE',
		/* [403] */
		"Along left=2",
		'CASE',
		/* [404] */
		"Along bottom=4",
		'CASE',
		/* [405] */
		"ALong right=8",
		'CASE',
		/* [406] */
		"Pattern fill",
		'WBIT',
		/* [407] */
		"Use oval",
		'WBIT',
		/* [408] */
		"Use RoundRect",
		'WBIT',
		/* [409] */
		"Use Shadow",
		'WBIT',
		/* [410] */
		"Reserved",
		'WB08',
		/* [411] */
		"Pen size",
		'PNT ',
		/* [412] */
		"Control is sizeable",
		'WBIT',
		/* [413] */
		"Control is dimmed",
		'WBIT',
		/* [414] */
		"Control is hilited",
		'WBIT',
		/* [415] */
		"Control dismisses",
		'WBIT',
		/* [416] */
		"Reserved",
		'WB12',
		/* [417] */
		"Control inset",
		'RECT',
		/* [418] */
		"Font style",
		'BORV',
		/* [419] */
		"Plain=0",
		'CASE',
		/* [420] */
		"Bold=1",
		'CASE',
		/* [421] */
		"Italic=2",
		'CASE',
		/* [422] */
		"Underline=4",
		'CASE',
		/* [423] */
		"Outline=8",
		'CASE',
		/* [424] */
		"Shadow=16",
		'CASE',
		/* [425] */
		"Condensed=32",
		'CASE',
		/* [426] */
		"Extended=64",
		'CASE',
		/* [427] */
		"Filler",
		'FBYT',
		/* [428] */
		"Font size",
		'DWRD',
		/* [429] */
		"SystemFont=0",
		'CASE',
		/* [430] */
		"Small applFont=9",
		'CASE',
		/* [431] */
		"Large applFont=12",
		'CASE',
		/* [432] */
		"Font color",
		'COLR',
		/* [433] */
		"Font name",
		'ESTR',
		/* [434] */
		"Color preference",
		'DBYT',
		/* [435] */
		"Look for color first=1",
		'CASE',
		/* [436] */
		"Look for B&W first=0",
		'CASE',
		/* [437] */
		"Filler",
		'FBYT',
		/* [438] */
		"TIconData",
		'DVDR',
		/* [439] */
		"Resource ID of 'cicn' or 'ICON'",
		'RSID',
		/* [440] */
		"",
		'KEYE',
		/* [441] */
		"patn",
		'KEYB',
		/* [442] */
		"Class name",
		'ESTR',
		/* [443] */
		"Usual=TPattern",
		'CASE',
		/* [444] */
		"TControlData",
		'DVDR',
		/* [445] */
		"Line adornment",
		'WB04',
		/* [446] */
		"No lines=0",
		'CASE',
		/* [447] */
		"Frame=15",
		'CASE',
		/* [448] */
		"Along top=1",
		'CASE',
		/* [449] */
		"Along left=2",
		'CASE',
		/* [450] */
		"Along bottom=4",
		'CASE',
		/* [451] */
		"ALong right=8",
		'CASE',
		/* [452] */
		"Pattern fill",
		'WBIT',
		/* [453] */
		"Use oval",
		'WBIT',
		/* [454] */
		"Use RoundRect",
		'WBIT',
		/* [455] */
		"Use Shadow",
		'WBIT',
		/* [456] */
		"Reserved",
		'WB08',
		/* [457] */
		"Pen size",
		'PNT ',
		/* [458] */
		"Control is sizeable",
		'WBIT',
		/* [459] */
		"Control is dimmed",
		'WBIT',
		/* [460] */
		"Control is hilited",
		'WBIT',
		/* [461] */
		"Control dismisses",
		'WBIT',
		/* [462] */
		"Reserved",
		'WB12',
		/* [463] */
		"Control inset",
		'RECT',
		/* [464] */
		"Font style",
		'BORV',
		/* [465] */
		"Plain=0",
		'CASE',
		/* [466] */
		"Bold=1",
		'CASE',
		/* [467] */
		"Italic=2",
		'CASE',
		/* [468] */
		"Underline=4",
		'CASE',
		/* [469] */
		"Outline=8",
		'CASE',
		/* [470] */
		"Shadow=16",
		'CASE',
		/* [471] */
		"Condensed=32",
		'CASE',
		/* [472] */
		"Extended=64",
		'CASE',
		/* [473] */
		"Filler",
		'FBYT',
		/* [474] */
		"Font size",
		'DWRD',
		/* [475] */
		"SystemFont=0",
		'CASE',
		/* [476] */
		"Small applFont=9",
		'CASE',
		/* [477] */
		"Large applFont=12",
		'CASE',
		/* [478] */
		"Font color",
		'COLR',
		/* [479] */
		"Font name",
		'ESTR',
		/* [480] */
		"TPatternData",
		'DVDR',
		/* [481] */
		"Color preference",
		'DBYT',
		/* [482] */
		"Look for color first=1",
		'CASE',
		/* [483] */
		"Look for B&W first=0",
		'CASE',
		/* [484] */
		"Filler",
		'FBYT',
		/* [485] */
		"Resource ID of 'ppat' or 'PAT '",
		'RSID',
		/* [486] */
		"",
		'KEYE',
		/* [487] */
		"pict",
		'KEYB',
		/* [488] */
		"Class name",
		'ESTR',
		/* [489] */
		"Usual=TPicture",
		'CASE',
		/* [490] */
		"TControlData",
		'DVDR',
		/* [491] */
		"Line adornment",
		'WB04',
		/* [492] */
		"No lines=0",
		'CASE',
		/* [493] */
		"Frame=15",
		'CASE',
		/* [494] */
		"Along top=1",
		'CASE',
		/* [495] */
		"Along left=2",
		'CASE',
		/* [496] */
		"Along bottom=4",
		'CASE',
		/* [497] */
		"ALong right=8",
		'CASE',
		/* [498] */
		"Pattern fill",
		'WBIT',
		/* [499] */
		"Use oval",
		'WBIT',
		/* [500] */
		"Use RoundRect",
		'WBIT',
		/* [501] */
		"Use Shadow",
		'WBIT',
		/* [502] */
		"Reserved",
		'WB08',
		/* [503] */
		"Pen size",
		'PNT ',
		/* [504] */
		"Control is sizeable",
		'WBIT',
		/* [505] */
		"Control is dimmed",
		'WBIT',
		/* [506] */
		"Control is hilited",
		'WBIT',
		/* [507] */
		"Control dismisses",
		'WBIT',
		/* [508] */
		"Reserved",
		'WB12',
		/* [509] */
		"Control inset",
		'RECT',
		/* [510] */
		"Font style",
		'BORV',
		/* [511] */
		"Plain=0",
		'CASE',
		/* [512] */
		"Bold=1",
		'CASE',
		/* [513] */
		"Italic=2",
		'CASE',
		/* [514] */
		"Underline=4",
		'CASE',
		/* [515] */
		"Outline=8",
		'CASE',
		/* [516] */
		"Shadow=16",
		'CASE',
		/* [517] */
		"Condensed=32",
		'CASE',
		/* [518] */
		"Extended=64",
		'CASE',
		/* [519] */
		"Filler",
		'FBYT',
		/* [520] */
		"Font size",
		'DWRD',
		/* [521] */
		"SystemFont=0",
		'CASE',
		/* [522] */
		"Small applFont=9",
		'CASE',
		/* [523] */
		"Large applFont=12",
		'CASE',
		/* [524] */
		"Font color",
		'COLR',
		/* [525] */
		"Font name",
		'ESTR',
		/* [526] */
		"TPictureData",
		'DVDR',
		/* [527] */
		"Picture ('PICT') resource ID",
		'RSID',
		/* [528] */
		"",
		'KEYE',
		/* [529] */
		"popp",
		'KEYB',
		/* [530] */
		"Class name",
		'ESTR',
		/* [531] */
		"Usual=TPopup",
		'CASE',
		/* [532] */
		"TControlData",
		'DVDR',
		/* [533] */
		"Line adornment",
		'WB04',
		/* [534] */
		"No lines=0",
		'CASE',
		/* [535] */
		"Frame=15",
		'CASE',
		/* [536] */
		"Along top=1",
		'CASE',
		/* [537] */
		"Along left=2",
		'CASE',
		/* [538] */
		"Along bottom=4",
		'CASE',
		/* [539] */
		"ALong right=8",
		'CASE',
		/* [540] */
		"Pattern fill",
		'WBIT',
		/* [541] */
		"Use oval",
		'WBIT',
		/* [542] */
		"Use RoundRect",
		'WBIT',
		/* [543] */
		"Use Shadow",
		'WBIT',
		/* [544] */
		"Reserved",
		'WB08',
		/* [545] */
		"Pen size",
		'PNT ',
		/* [546] */
		"Control is sizeable",
		'WBIT',
		/* [547] */
		"Control is dimmed",
		'WBIT',
		/* [548] */
		"Control is hilited",
		'WBIT',
		/* [549] */
		"Control dismisses",
		'WBIT',
		/* [550] */
		"Reserved",
		'WB12',
		/* [551] */
		"Control inset",
		'RECT',
		/* [552] */
		"Font style",
		'BORV',
		/* [553] */
		"Plain=0",
		'CASE',
		/* [554] */
		"Bold=1",
		'CASE',
		/* [555] */
		"Italic=2",
		'CASE',
		/* [556] */
		"Underline=4",
		'CASE',
		/* [557] */
		"Outline=8",
		'CASE',
		/* [558] */
		"Shadow=16",
		'CASE',
		/* [559] */
		"Condensed=32",
		'CASE',
		/* [560] */
		"Extended=64",
		'CASE',
		/* [561] */
		"Filler",
		'FBYT',
		/* [562] */
		"Font size",
		'DWRD',
		/* [563] */
		"SystemFont=0",
		'CASE',
		/* [564] */
		"Small applFont=9",
		'CASE',
		/* [565] */
		"Large applFont=12",
		'CASE',
		/* [566] */
		"Font color",
		'COLR',
		/* [567] */
		"Font name",
		'ESTR',
		/* [568] */
		"TPopupData",
		'DVDR',
		/* [569] */
		"Resource ID of 'MENU'",
		'RSID',
		/* [570] */
		"Current item",
		'DWRD',
		/* [571] */
		"Left offset",
		'DWRD',
		/* [572] */
		"",
		'KEYE',
		/* [573] */
		"stat",
		'KEYB',
		/* [574] */
		"Class name",
		'ESTR',
		/* [575] */
		"Usual=TStaticText",
		'CASE',
		/* [576] */
		"TControlData",
		'DVDR',
		/* [577] */
		"Line adornment",
		'WB04',
		/* [578] */
		"No lines=0",
		'CASE',
		/* [579] */
		"Frame=15",
		'CASE',
		/* [580] */
		"Along top=1",
		'CASE',
		/* [581] */
		"Along left=2",
		'CASE',
		/* [582] */
		"Along bottom=4",
		'CASE',
		/* [583] */
		"ALong right=8",
		'CASE',
		/* [584] */
		"Pattern fill",
		'WBIT',
		/* [585] */
		"Use oval",
		'WBIT',
		/* [586] */
		"Use RoundRect",
		'WBIT',
		/* [587] */
		"Use Shadow",
		'WBIT',
		/* [588] */
		"Reserved",
		'WB08',
		/* [589] */
		"Pen size",
		'PNT ',
		/* [590] */
		"Control is sizeable",
		'WBIT',
		/* [591] */
		"Control is dimmed",
		'WBIT',
		/* [592] */
		"Control is hilited",
		'WBIT',
		/* [593] */
		"Control dismisses",
		'WBIT',
		/* [594] */
		"Reserved",
		'WB12',
		/* [595] */
		"Control inset",
		'RECT',
		/* [596] */
		"Font style",
		'BORV',
		/* [597] */
		"Plain=0",
		'CASE',
		/* [598] */
		"Bold=1",
		'CASE',
		/* [599] */
		"Italic=2",
		'CASE',
		/* [600] */
		"Underline=4",
		'CASE',
		/* [601] */
		"Outline=8",
		'CASE',
		/* [602] */
		"Shadow=16",
		'CASE',
		/* [603] */
		"Condensed=32",
		'CASE',
		/* [604] */
		"Extended=64",
		'CASE',
		/* [605] */
		"Filler",
		'FBYT',
		/* [606] */
		"Font size",
		'DWRD',
		/* [607] */
		"SystemFont=0",
		'CASE',
		/* [608] */
		"Small applFont=9",
		'CASE',
		/* [609] */
		"Large applFont=12",
		'CASE',
		/* [610] */
		"Font color",
		'COLR',
		/* [611] */
		"Font name",
		'ESTR',
		/* [612] */
		"TStaticTextData",
		'DVDR',
		/* [613] */
		"Justification",
		'DWRD',
		/* [614] */
		"Let system do it (left)=0",
		'CASE',
		/* [615] */
		"Force left=-2",
		'CASE',
		/* [616] */
		"Right justify=-1",
		'CASE',
		/* [617] */
		"Center=1",
		'CASE',
		/* [618] */
		"Initial text value",
		'ESTR',
		/* [619] */
		"",
		'KEYE',
		/* [620] */
		"edit",
		'KEYB',
		/* [621] */
		"Class name",
		'ESTR',
		/* [622] */
		"Usual=TEditText",
		'CASE',
		/* [623] */
		"TControlData",
		'DVDR',
		/* [624] */
		"Line adornment",
		'WB04',
		/* [625] */
		"No lines=0",
		'CASE',
		/* [626] */
		"Frame=15",
		'CASE',
		/* [627] */
		"Along top=1",
		'CASE',
		/* [628] */
		"Along left=2",
		'CASE',
		/* [629] */
		"Along bottom=4",
		'CASE',
		/* [630] */
		"ALong right=8",
		'CASE',
		/* [631] */
		"Pattern fill",
		'WBIT',
		/* [632] */
		"Use oval",
		'WBIT',
		/* [633] */
		"Use RoundRect",
		'WBIT',
		/* [634] */
		"Use Shadow",
		'WBIT',
		/* [635] */
		"Reserved",
		'WB08',
		/* [636] */
		"Pen size",
		'PNT ',
		/* [637] */
		"Control is sizeable",
		'WBIT',
		/* [638] */
		"Control is dimmed",
		'WBIT',
		/* [639] */
		"Control is hilited",
		'WBIT',
		/* [640] */
		"Control dismisses",
		'WBIT',
		/* [641] */
		"Reserved",
		'WB12',
		/* [642] */
		"Control inset",
		'RECT',
		/* [643] */
		"Font style",
		'BORV',
		/* [644] */
		"Plain=0",
		'CASE',
		/* [645] */
		"Bold=1",
		'CASE',
		/* [646] */
		"Italic=2",
		'CASE',
		/* [647] */
		"Underline=4",
		'CASE',
		/* [648] */
		"Outline=8",
		'CASE',
		/* [649] */
		"Shadow=16",
		'CASE',
		/* [650] */
		"Condensed=32",
		'CASE',
		/* [651] */
		"Extended=64",
		'CASE',
		/* [652] */
		"Filler",
		'FBYT',
		/* [653] */
		"Font size",
		'DWRD',
		/* [654] */
		"SystemFont=0",
		'CASE',
		/* [655] */
		"Small applFont=9",
		'CASE',
		/* [656] */
		"Large applFont=12",
		'CASE',
		/* [657] */
		"Font color",
		'COLR',
		/* [658] */
		"Font name",
		'ESTR',
		/* [659] */
		"TStaticTextData",
		'DVDR',
		/* [660] */
		"Justification",
		'DWRD',
		/* [661] */
		"Let system do it (left)=0",
		'CASE',
		/* [662] */
		"Force left=-2",
		'CASE',
		/* [663] */
		"Right justify=-1",
		'CASE',
		/* [664] */
		"Center=1",
		'CASE',
		/* [665] */
		"Initial text value",
		'ESTR',
		/* [666] */
		"TEditTextData",
		'DVDR',
		/* [667] */
		"Maximum number of characters",
		'DWRD',
		/* [668] */
		"Unlimited=255",
		'CASE',
		/* [669] */
		"Accept Down Arrow",
		'LBIT',
		/* [670] */
		"Accept Up Arrow",
		'LBIT',
		/* [671] */
		"Accept Right Arrow",
		'LBIT',
		/* [672] */
		"Accept Left Arrow",
		'LBIT',
		/* [673] */
		"Accept Escape",
		'LBIT',
		/* [674] */
		"Accept ^Z",
		'LBIT',
		/* [675] */
		"^Y",
		'LBIT',
		/* [676] */
		"^X",
		'LBIT',
		/* [677] */
		"^W",
		'LBIT',
		/* [678] */
		"^V",
		'LBIT',
		/* [679] */
		"^U",
		'LBIT',
		/* [680] */
		"^T",
		'LBIT',
		/* [681] */
		"^S",
		'LBIT',
		/* [682] */
		"^R",
		'LBIT',
		/* [683] */
		"^Q",
		'LBIT',
		/* [684] */
		"^P",
		'LBIT',
		/* [685] */
		"^O",
		'LBIT',
		/* [686] */
		"^N",
		'LBIT',
		/* [687] */
		"Accept CarriageReturn",
		'LBIT',
		/* [688] */
		"^L",
		'LBIT',
		/* [689] */
		"^K",
		'LBIT',
		/* [690] */
		"^J",
		'LBIT',
		/* [691] */
		"^I",
		'LBIT',
		/* [692] */
		"Accept BackSpace",
		'LBIT',
		/* [693] */
		"^G",
		'LBIT',
		/* [694] */
		"^F",
		'LBIT',
		/* [695] */
		"^E",
		'LBIT',
		/* [696] */
		"^D",
		'LBIT',
		/* [697] */
		"Accept Enter",
		'LBIT',
		/* [698] */
		"^B",
		'LBIT',
		/* [699] */
		"^A",
		'LBIT',
		/* [700] */
		"Accept Null",
		'LBIT',
		/* [701] */
		"",
		'KEYE',
		/* [702] */
		"nmbr",
		'KEYB',
		/* [703] */
		"Class name",
		'ESTR',
		/* [704] */
		"Usual=TNumberText",
		'CASE',
		/* [705] */
		"TControlData",
		'DVDR',
		/* [706] */
		"Line adornment",
		'WB04',
		/* [707] */
		"No lines=0",
		'CASE',
		/* [708] */
		"Frame=15",
		'CASE',
		/* [709] */
		"Along top=1",
		'CASE',
		/* [710] */
		"Along left=2",
		'CASE',
		/* [711] */
		"Along bottom=4",
		'CASE',
		/* [712] */
		"ALong right=8",
		'CASE',
		/* [713] */
		"Pattern fill",
		'WBIT',
		/* [714] */
		"Use oval",
		'WBIT',
		/* [715] */
		"Use RoundRect",
		'WBIT',
		/* [716] */
		"Use Shadow",
		'WBIT',
		/* [717] */
		"Reserved",
		'WB08',
		/* [718] */
		"Pen size",
		'PNT ',
		/* [719] */
		"Control is sizeable",
		'WBIT',
		/* [720] */
		"Control is dimmed",
		'WBIT',
		/* [721] */
		"Control is hilited",
		'WBIT',
		/* [722] */
		"Control dismisses",
		'WBIT',
		/* [723] */
		"Reserved",
		'WB12',
		/* [724] */
		"Control inset",
		'RECT',
		/* [725] */
		"Font style",
		'BORV',
		/* [726] */
		"Plain=0",
		'CASE',
		/* [727] */
		"Bold=1",
		'CASE',
		/* [728] */
		"Italic=2",
		'CASE',
		/* [729] */
		"Underline=4",
		'CASE',
		/* [730] */
		"Outline=8",
		'CASE',
		/* [731] */
		"Shadow=16",
		'CASE',
		/* [732] */
		"Condensed=32",
		'CASE',
		/* [733] */
		"Extended=64",
		'CASE',
		/* [734] */
		"Filler",
		'FBYT',
		/* [735] */
		"Font size",
		'DWRD',
		/* [736] */
		"SystemFont=0",
		'CASE',
		/* [737] */
		"Small applFont=9",
		'CASE',
		/* [738] */
		"Large applFont=12",
		'CASE',
		/* [739] */
		"Font color",
		'COLR',
		/* [740] */
		"Font name",
		'ESTR',
		/* [741] */
		"TStaticTextData",
		'DVDR',
		/* [742] */
		"Justification",
		'DWRD',
		/* [743] */
		"Let system do it (left)=0",
		'CASE',
		/* [744] */
		"Force left=-2",
		'CASE',
		/* [745] */
		"Right justify=-1",
		'CASE',
		/* [746] */
		"Center=1",
		'CASE',
		/* [747] */
		"Initial text value",
		'ESTR',
		/* [748] */
		"TEditTextData",
		'DVDR',
		/* [749] */
		"Maximum number of characters",
		'DWRD',
		/* [750] */
		"Unlimited=255",
		'CASE',
		/* [751] */
		"Accept Down Arrow",
		'LBIT',
		/* [752] */
		"Accept Up Arrow",
		'LBIT',
		/* [753] */
		"Accept Right Arrow",
		'LBIT',
		/* [754] */
		"Accept Left Arrow",
		'LBIT',
		/* [755] */
		"Accept Escape",
		'LBIT',
		/* [756] */
		"Accept ^Z",
		'LBIT',
		/* [757] */
		"^Y",
		'LBIT',
		/* [758] */
		"^X",
		'LBIT',
		/* [759] */
		"^W",
		'LBIT',
		/* [760] */
		"^V",
		'LBIT',
		/* [761] */
		"^U",
		'LBIT',
		/* [762] */
		"^T",
		'LBIT',
		/* [763] */
		"^S",
		'LBIT',
		/* [764] */
		"^R",
		'LBIT',
		/* [765] */
		"^Q",
		'LBIT',
		/* [766] */
		"^P",
		'LBIT',
		/* [767] */
		"^O",
		'LBIT',
		/* [768] */
		"^N",
		'LBIT',
		/* [769] */
		"Accept CarriageReturn",
		'LBIT',
		/* [770] */
		"^L",
		'LBIT',
		/* [771] */
		"^K",
		'LBIT',
		/* [772] */
		"^J",
		'LBIT',
		/* [773] */
		"^I",
		'LBIT',
		/* [774] */
		"Accept BackSpace",
		'LBIT',
		/* [775] */
		"^G",
		'LBIT',
		/* [776] */
		"^F",
		'LBIT',
		/* [777] */
		"^E",
		'LBIT',
		/* [778] */
		"^D",
		'LBIT',
		/* [779] */
		"Accept Enter",
		'LBIT',
		/* [780] */
		"^B",
		'LBIT',
		/* [781] */
		"^A",
		'LBIT',
		/* [782] */
		"Accept Null",
		'LBIT',
		/* [783] */
		"TNumberTextData",
		'DVDR',
		/* [784] */
		"Initial numeric value",
		'DLNG',
		/* [785] */
		"Minimum value",
		'DLNG',
		/* [786] */
		"Maximum value",
		'DLNG',
		/* [787] */
		"",
		'KEYE',
		/* [788] */
		"tevw",
		'KEYB',
		/* [789] */
		"Class name",
		'ESTR',
		/* [790] */
		"Usual=TTEView",
		'CASE',
		/* [791] */
		"TTEViewData",
		'DVDR',
		/* [792] */
		"Use styled TextEdit",
		'WBIT',
		/* [793] */
		"Use word wrap",
		'WBIT',
		/* [794] */
		"Accept changes",
		'WBIT',
		/* [795] */
		"Free text",
		'WBIT',
		/* [796] */
		"Reserved",
		'WB12',
		/* [797] */
		"Command",
		'DWRD',
		/* [798] */
		"Typing=120",
		'CASE',
		/* [799] */
		"Maximum number of characters",
		'DWRD',
		/* [800] */
		"Unlimited=32767",
		'CASE',
		/* [801] */
		"Inset",
		'RECT',
		/* [802] */
		"Justification",
		'DWRD',
		/* [803] */
		"Let system do it (left)=0",
		'CASE',
		/* [804] */
		"Force left=-2",
		'CASE',
		/* [805] */
		"Right justify=-1",
		'CASE',
		/* [806] */
		"Center=1",
		'CASE',
		/* [807] */
		"Font style",
		'BORV',
		/* [808] */
		"Plain=0",
		'CASE',
		/* [809] */
		"Bold=1",
		'CASE',
		/* [810] */
		"Italic=2",
		'CASE',
		/* [811] */
		"Underline=4",
		'CASE',
		/* [812] */
		"Outline=8",
		'CASE',
		/* [813] */
		"Shadow=16",
		'CASE',
		/* [814] */
		"Condensed=32",
		'CASE',
		/* [815] */
		"Extended=64",
		'CASE',
		/* [816] */
		"Filler",
		'FBYT',
		/* [817] */
		"Font size",
		'DWRD',
		/* [818] */
		"SystemFont=0",
		'CASE',
		/* [819] */
		"Small applFont=9",
		'CASE',
		/* [820] */
		"Large applFont=12",
		'CASE',
		/* [821] */
		"Font color",
		'COLR',
		/* [822] */
		"Font name",
		'ESTR',
		/* [823] */
		"",
		'KEYE',
		/* [824] */
		"grid",
		'KEYB',
		/* [825] */
		"Class name",
		'ESTR',
		/* [826] */
		"Usual=TGridView",
		'CASE',
		/* [827] */
		"TGridViewData",
		'DVDR',
		/* [828] */
		"Number of rows",
		'DWRD',
		/* [829] */
		"Number of columns",
		'DWRD',
		/* [830] */
		"Row height (in pixels)",
		'DWRD',
		/* [831] */
		"Column width (in pixels)",
		'DWRD',
		/* [832] */
		"Row inset",
		'DWRD',
		/* [833] */
		"Column inset",
		'DWRD',
		/* [834] */
		"Adorn rows",
		'WBIT',
		/* [835] */
		"Adorn columns",
		'WBIT',
		/* [836] */
		"Single selection",
		'WBIT',
		/* [837] */
		"Reserved",
		'WB13',
		/* [838] */
		"",
		'KEYE',
		/* [839] */
		"txtg",
		'KEYB',
		/* [840] */
		"Class name",
		'ESTR',
		/* [841] */
		"Usual=TTextGridView",
		'CASE',
		/* [842] */
		"TGridViewData",
		'DVDR',
		/* [843] */
		"Number of rows",
		'DWRD',
		/* [844] */
		"Number of columns",
		'DWRD',
		/* [845] */
		"Row height (in pixels)",
		'DWRD',
		/* [846] */
		"Column width (in pixels)",
		'DWRD',
		/* [847] */
		"Row inset",
		'DWRD',
		/* [848] */
		"Column inset",
		'DWRD',
		/* [849] */
		"Adorn rows",
		'WBIT',
		/* [850] */
		"Adorn columns",
		'WBIT',
		/* [851] */
		"Single selection",
		'WBIT',
		/* [852] */
		"Reserved",
		'WB13',
		/* [853] */
		"TTextGridViewData",
		'DVDR',
		/* [854] */
		"Font style",
		'BORV',
		/* [855] */
		"Plain=0",
		'CASE',
		/* [856] */
		"Bold=1",
		'CASE',
		/* [857] */
		"Italic=2",
		'CASE',
		/* [858] */
		"Underline=4",
		'CASE',
		/* [859] */
		"Outline=8",
		'CASE',
		/* [860] */
		"Shadow=16",
		'CASE',
		/* [861] */
		"Condensed=32",
		'CASE',
		/* [862] */
		"Extended=64",
		'CASE',
		/* [863] */
		"Filler",
		'FBYT',
		/* [864] */
		"Font size",
		'DWRD',
		/* [865] */
		"SystemFont=0",
		'CASE',
		/* [866] */
		"Small applFont=9",
		'CASE',
		/* [867] */
		"Large applFont=12",
		'CASE',
		/* [868] */
		"Font color",
		'COLR',
		/* [869] */
		"Font name",
		'ESTR',
		/* [870] */
		"",
		'KEYE',
		/* [871] */
		"lstg",
		'KEYB',
		/* [872] */
		"Class name",
		'ESTR',
		/* [873] */
		"Usual=TTextListView",
		'CASE',
		/* [874] */
		"TGridViewData",
		'DVDR',
		/* [875] */
		"Number of rows",
		'DWRD',
		/* [876] */
		"Number of columns",
		'DWRD',
		/* [877] */
		"Row height (in pixels)",
		'DWRD',
		/* [878] */
		"Column width (in pixels)",
		'DWRD',
		/* [879] */
		"Row inset",
		'DWRD',
		/* [880] */
		"Column inset",
		'DWRD',
		/* [881] */
		"Adorn rows",
		'WBIT',
		/* [882] */
		"Adorn columns",
		'WBIT',
		/* [883] */
		"Single selection",
		'WBIT',
		/* [884] */
		"Reserved",
		'WB13',
		/* [885] */
		"TTextGridViewData",
		'DVDR',
		/* [886] */
		"Font style",
		'BORV',
		/* [887] */
		"Plain=0",
		'CASE',
		/* [888] */
		"Bold=1",
		'CASE',
		/* [889] */
		"Italic=2",
		'CASE',
		/* [890] */
		"Underline=4",
		'CASE',
		/* [891] */
		"Outline=8",
		'CASE',
		/* [892] */
		"Shadow=16",
		'CASE',
		/* [893] */
		"Condensed=32",
		'CASE',
		/* [894] */
		"Extended=64",
		'CASE',
		/* [895] */
		"Filler",
		'FBYT',
		/* [896] */
		"Font size",
		'DWRD',
		/* [897] */
		"SystemFont=0",
		'CASE',
		/* [898] */
		"Small applFont=9",
		'CASE',
		/* [899] */
		"Large applFont=12",
		'CASE',
		/* [900] */
		"Font color",
		'COLR',
		/* [901] */
		"Font name",
		'ESTR',
		/* [902] */
		"",
		'KEYE',
		/* [903] */
		"othr",
		'KEYB',
		/* [904] */
		"Class name",
		'ESTR',
		/* [905] */
		"Offset to end of unknown view data",
		'SKIP',
		/* [906] */
		"Signature of unknown view",
		'TNAM',
		/* [907] */
		"",
		'SKPE',
		/* [908] */
		"",
		'KEYE',
		/* [909] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1390, "wctb") {
	{	/* array: 20 elements */
		/* [1] */
		"Window color seed",
		'HLNG',
		/* [2] */
		"Flags",
		'HWRD',
		/* [3] */
		"Count:",
		'ZCNT',
		/* [4] */
		"List of Colors",
		'LSTC',
		/* [5] */
		"Part code",
		'DWRD',
		/* [6] */
		"Content color=0",
		'CASE',
		/* [7] */
		"Frame color=1",
		'CASE',
		/* [8] */
		"Text (& button text) color=2",
		'CASE',
		/* [9] */
		"Hilite color=3",
		'CASE',
		/* [10] */
		"Title bar color=4",
		'CASE',
		/* [11] */
		"Title stripes/gray text light=5",
		'CASE',
		/* [12] */
		"Title stripes/gray text dark=6",
		'CASE',
		/* [13] */
		"Title bar background light=7",
		'CASE',
		/* [14] */
		"Title bar background dark=8",
		'CASE',
		/* [15] */
		"Dialog beveled frame light=9",
		'CASE',
		/* [16] */
		"Dialog beveled frame dark=10",
		'CASE',
		/* [17] */
		"Tinge light=11",
		'CASE',
		/* [18] */
		"Tinge dark=12",
		'CASE',
		/* [19] */
		"Color",
		'COLR',
		/* [20] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1391, "WIND") {
	{	/* array: 27 elements */
		/* [1] */
		"BoundsRect",
		'RECT',
		/* [2] */
		"Proc ID",
		'DWRD',
		/* [3] */
		"documentProc=0",
		'CASE',
		/* [4] */
		"dBoxProc=1",
		'CASE',
		/* [5] */
		"plainDBox=2",
		'CASE',
		/* [6] */
		"altDBoxProc=3",
		'CASE',
		/* [7] */
		"noGrowDocProc=4",
		'CASE',
		/* [8] */
		"movableDBoxProc=5",
		'CASE',
		/* [9] */
		"zoomDocProc=8",
		'CASE',
		/* [10] */
		"zoomNoGrow=12",
		'CASE',
		/* [11] */
		"rDocProc=16",
		'CASE',
		/* [12] */
		"Visible",
		'BOOL',
		/* [13] */
		"GoAway",
		'BOOL',
		/* [14] */
		"RefCon",
		'DLNG',
		/* [15] */
		"Title",
		'PSTR',
		/* [16] */
		"Align",
		'AWRD',
		/* [17] */
		"Window placement",
		'HWRD',
		/* [18] */
		"Leave it alone=$0000",
		'CASE',
		/* [19] */
		"Center on main screen=$280A",
		'CASE',
		/* [20] */
		"Center in parent window=$A80A",
		'CASE',
		/* [21] */
		"Center on parent's screen=$680A",
		'CASE',
		/* [22] */
		"Alert on main screen=$300A",
		'CASE',
		/* [23] */
		"Alert in parent window=$B00A",
		'CASE',
		/* [24] */
		"Alert in parent's screen=$700A",
		'CASE',
		/* [25] */
		"Stagger on main screen=$380A",
		'CASE',
		/* [26] */
		"Stagger in parent window=$B80A",
		'CASE',
		/* [27] */
		"Stagger on parent's screen=$780A",
		'CASE'
	}
};

resource 'TMPL' (1392, "WSPC") {
	{	/* array: 4 elements */
		/* [1] */
		"Top",
		'DWRD',
		/* [2] */
		"Left",
		'DWRD',
		/* [3] */
		"Width",
		'DWRD',
		/* [4] */
		"Height",
		'DWRD'
	}
};

resource 'TMPL' (1393, "wstr") {
	{	/* array: 1 elements */
		/* [1] */
		"Query",
		'WSTR'
	}
};

resource 'TMPL' (1394, "WTYP") {
	{	/* array: 283 elements */
		/* [1] */
		"Template for Constructor CW10",
		'DVDR',
		/* [2] */
		"Version Number",
		'DWRD',
		/* [3] */
		"CW10=1",
		'CASE',
		/* [4] */
		"*****",
		'LSTB',
		/* [5] */
		"Object type",
		'KTYP',
		/* [6] */
		"Object data=objd",
		'CASE',
		/* [7] */
		"Begin sub-object list=begs",
		'CASE',
		/* [8] */
		"End sub-object list=ends",
		'CASE',
		/* [9] */
		"User object=user",
		'CASE',
		/* [10] */
		"Class alias=dopl",
		'CASE',
		/* [11] */
		"End of list=end.",
		'CASE',
		/* [12] */
		"objd",
		'KEYB',
		/* [13] */
		"Number of bytes in following data",
		'LSIZ',
		/* [14] */
		"Data type",
		'KTYP',
		/* [15] */
		"Object=obj ",
		'CASE',
		/* [16] */
		"Display class info=vwte",
		'CASE',
		/* [17] */
		"Integer attribute=intv",
		'CASE',
		/* [18] */
		"Labelled integer attribute=labi",
		'CASE',
		/* [19] */
		"Min/max integer attribute=mimx",
		'CASE',
		/* [20] */
		"Res list attribute=resl",
		'CASE',
		/* [21] */
		"Resource reference attribute=rerf",
		'CASE',
		/* [22] */
		"String attribute=pstr",
		'CASE',
		/* [23] */
		"Font string attribute=fstr",
		'CASE',
		/* [24] */
		"Name or ordinal attribute=nord",
		'CASE',
		/* [25] */
		"RGB color attribute=rgbc",
		'CASE',
		/* [26] */
		"Container attribute=cont",
		'CASE',
		/* [27] */
		"List attribute=list",
		'CASE',
		/* [28] */
		"Bitfield container attribute=bitf",
		'CASE',
		/* [29] */
		"Value label=labl",
		'CASE',
		/* [30] */
		"Resource container=rsco",
		'CASE',
		/* [31] */
		"View editor type list=vetl",
		'CASE',
		/* [32] */
		"Custom type object=ctmo",
		'CASE',
		/* [33] */
		"Null=null",
		'CASE',
		/* [34] */
		"obj ",
		'KEYB',
		/* [35] */
		"",
		'KEYE',
		/* [36] */
		"vwte",
		'KEYB',
		/* [37] */
		"VWTypeEntry data",
		'DVDR',
		/* [38] */
		"Class name",
		'PSTR',
		/* [39] */
		"Icon ID",
		'DWRD',
		/* [40] */
		"Abstract class?",
		'BFLG',
		/* [41] */
		"Class ID",
		'TNAM',
		/* [42] */
		"Parent class ID",
		'TNAM',
		/* [43] */
		"Default width",
		'DWRD',
		/* [44] */
		"Default height",
		'DWRD',
		/* [45] */
		"Must be root?",
		'BFLG',
		/* [46] */
		"Default resource ID",
		'DWRD',
		/* [47] */
		"",
		'KEYE',
		/* [48] */
		"intv",
		'KEYB',
		/* [49] */
		"DMAttribute data",
		'DVDR',
		/* [50] */
		"Attribute title",
		'PSTR',
		/* [51] */
		"Attribute key",
		'TNAM',
		/* [52] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [53] */
		"Write to stream?",
		'BFLG',
		/* [54] */
		"Stream selector",
		'TNAM',
		/* [55] */
		"DMIntegerAttribute data",
		'DVDR',
		/* [56] */
		"Default value",
		'DLNG',
		/* [57] */
		"Value size (bits)",
		'UWRD',
		/* [58] */
		"Signed integer?",
		'BFLG',
		/* [59] */
		"Can be text value?",
		'BFLG',
		/* [60] */
		"Always is text value?",
		'BFLG',
		/* [61] */
		"",
		'KEYE',
		/* [62] */
		"labi",
		'KEYB',
		/* [63] */
		"DMAttribute data",
		'DVDR',
		/* [64] */
		"Attribute title",
		'PSTR',
		/* [65] */
		"Attribute key",
		'TNAM',
		/* [66] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [67] */
		"Write to stream?",
		'BFLG',
		/* [68] */
		"Stream selector",
		'TNAM',
		/* [69] */
		"DMIntegerAttribute data",
		'DVDR',
		/* [70] */
		"Default value",
		'DLNG',
		/* [71] */
		"Value size (bits)",
		'UWRD',
		/* [72] */
		"Signed integer?",
		'BFLG',
		/* [73] */
		"Can be text value?",
		'BFLG',
		/* [74] */
		"Always is text value?",
		'BFLG',
		/* [75] */
		"DMLabelledIntegerAttribute data",
		'DVDR',
		/* [76] */
		"Labels only?",
		'BFLG',
		/* [77] */
		"",
		'KEYE',
		/* [78] */
		"mimx",
		'KEYB',
		/* [79] */
		"DMAttribute data",
		'DVDR',
		/* [80] */
		"Attribute title",
		'PSTR',
		/* [81] */
		"Attribute key",
		'TNAM',
		/* [82] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [83] */
		"Write to stream?",
		'BFLG',
		/* [84] */
		"Stream selector",
		'TNAM',
		/* [85] */
		"DMIntegerAttribute data",
		'DVDR',
		/* [86] */
		"Default value",
		'DLNG',
		/* [87] */
		"Value size (bits)",
		'UWRD',
		/* [88] */
		"Signed integer?",
		'BFLG',
		/* [89] */
		"Can be text value?",
		'BFLG',
		/* [90] */
		"Always is text value?",
		'BFLG',
		/* [91] */
		"DMMinMaxIntegerAttribute data",
		'DVDR',
		/* [92] */
		"Minimum value",
		'DLNG',
		/* [93] */
		"Maximum value",
		'DLNG',
		/* [94] */
		"",
		'KEYE',
		/* [95] */
		"resl",
		'KEYB',
		/* [96] */
		"DMAttribute data",
		'DVDR',
		/* [97] */
		"Attribute title",
		'PSTR',
		/* [98] */
		"Attribute key",
		'TNAM',
		/* [99] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [100] */
		"Write to stream?",
		'BFLG',
		/* [101] */
		"Stream selector",
		'TNAM',
		/* [102] */
		"DMIntegerAttribute data",
		'DVDR',
		/* [103] */
		"Default value",
		'DLNG',
		/* [104] */
		"Value size (bits)",
		'UWRD',
		/* [105] */
		"Signed integer?",
		'BFLG',
		/* [106] */
		"Can be text value?",
		'BFLG',
		/* [107] */
		"Always is text value?",
		'BFLG',
		/* [108] */
		"DMLabelledIntegerAttribute data",
		'DVDR',
		/* [109] */
		"Labels only?",
		'BFLG',
		/* [110] */
		"DMResListAttribute data",
		'DVDR',
		/* [111] */
		"Resource type",
		'TNAM',
		/* [112] */
		"",
		'KEYE',
		/* [113] */
		"rerf",
		'KEYB',
		/* [114] */
		"DMAttribute data",
		'DVDR',
		/* [115] */
		"Attribute title",
		'PSTR',
		/* [116] */
		"Attribute key",
		'TNAM',
		/* [117] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [118] */
		"Write to stream?",
		'BFLG',
		/* [119] */
		"Stream selector",
		'TNAM',
		/* [120] */
		"DMIntegerAttribute data",
		'DVDR',
		/* [121] */
		"Default value",
		'DLNG',
		/* [122] */
		"Value size (bits)",
		'UWRD',
		/* [123] */
		"Signed integer?",
		'BFLG',
		/* [124] */
		"Can be text value?",
		'BFLG',
		/* [125] */
		"Always is text value?",
		'BFLG',
		/* [126] */
		"DMResourceRefAttribute data",
		'DVDR',
		/* [127] */
		"Resource type",
		'TNAM',
		/* [128] */
		"",
		'KEYE',
		/* [129] */
		"pstr",
		'KEYB',
		/* [130] */
		"DMAttribute data",
		'DVDR',
		/* [131] */
		"Attribute title",
		'PSTR',
		/* [132] */
		"Attribute key",
		'TNAM',
		/* [133] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [134] */
		"Write to stream?",
		'BFLG',
		/* [135] */
		"Stream selector",
		'TNAM',
		/* [136] */
		"DMStringAttribute data",
		'DVDR',
		/* [137] */
		"Default value",
		'PSTR',
		/* [138] */
		"Maximum length (characters)",
		'UWRD',
		/* [139] */
		"Even padded?",
		'BFLG',
		/* [140] */
		"(unused)",
		'BB03',
		/* [141] */
		"Unicode string?",
		'BBIT',
		/* [142] */
		"Hex entry?",
		'BBIT',
		/* [143] */
		"Accept CR?",
		'BBIT',
		/* [144] */
		"C style string?",
		'BBIT',
		/* [145] */
		"Odd padded?",
		'BBIT',
		/* [146] */
		"",
		'KEYE',
		/* [147] */
		"fstr",
		'KEYB',
		/* [148] */
		"DMAttribute data",
		'DVDR',
		/* [149] */
		"Attribute title",
		'PSTR',
		/* [150] */
		"Attribute key",
		'TNAM',
		/* [151] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [152] */
		"Write to stream?",
		'BFLG',
		/* [153] */
		"Stream selector",
		'TNAM',
		/* [154] */
		"DMStringAttribute data",
		'DVDR',
		/* [155] */
		"Default value",
		'PSTR',
		/* [156] */
		"Maximum length (characters)",
		'UWRD',
		/* [157] */
		"Even padded?",
		'BFLG',
		/* [158] */
		"(unused)",
		'BB03',
		/* [159] */
		"Unicode string?",
		'BBIT',
		/* [160] */
		"Hex entry?",
		'BBIT',
		/* [161] */
		"Accept CR?",
		'BBIT',
		/* [162] */
		"C style string?",
		'BBIT',
		/* [163] */
		"Odd padded?",
		'BBIT',
		/* [164] */
		"DMFontStringAttribute data",
		'DVDR',
		/* [165] */
		"Default font number",
		'DWRD',
		/* [166] */
		"Write font number?",
		'BFLG',
		/* [167] */
		"Include system font?",
		'BFLG',
		/* [168] */
		"Include application font?",
		'BFLG',
		/* [169] */
		"Include hidden fonts?",
		'BFLG',
		/* [170] */
		"",
		'KEYE',
		/* [171] */
		"nord",
		'KEYB',
		/* [172] */
		"DMAttribute data",
		'DVDR',
		/* [173] */
		"Attribute title",
		'PSTR',
		/* [174] */
		"Attribute key",
		'TNAM',
		/* [175] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [176] */
		"Write to stream?",
		'BFLG',
		/* [177] */
		"Stream selector",
		'TNAM',
		/* [178] */
		"DMStringAttribute data",
		'DVDR',
		/* [179] */
		"Default value",
		'PSTR',
		/* [180] */
		"Maximum length (characters)",
		'UWRD',
		/* [181] */
		"Even padded?",
		'BFLG',
		/* [182] */
		"(unused)",
		'BB03',
		/* [183] */
		"Unicode string?",
		'BBIT',
		/* [184] */
		"Hex entry?",
		'BBIT',
		/* [185] */
		"Accept CR?",
		'BBIT',
		/* [186] */
		"C style string?",
		'BBIT',
		/* [187] */
		"Odd padded?",
		'BBIT',
		/* [188] */
		"DMNameOrOrdinalValue data",
		'DVDR',
		/* [189] */
		"Numeric value",
		'DLNG',
		/* [190] */
		"Numeric value size",
		'UWRD',
		/* [191] */
		"Signed integer?",
		'BFLG',
		/* [192] */
		"Is numeric value?",
		'BFLG',
		/* [193] */
		"",
		'KEYE',
		/* [194] */
		"rgbc",
		'KEYB',
		/* [195] */
		"DMAttribute data",
		'DVDR',
		/* [196] */
		"Attribute title",
		'PSTR',
		/* [197] */
		"Attribute key",
		'TNAM',
		/* [198] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [199] */
		"Write to stream?",
		'BFLG',
		/* [200] */
		"Stream selector",
		'TNAM',
		/* [201] */
		"DMRGBColorAttribute data",
		'DVDR',
		/* [202] */
		"Default value",
		'COLR',
		/* [203] */
		"",
		'KEYE',
		/* [204] */
		"cont",
		'KEYB',
		/* [205] */
		"DMAttribute data",
		'DVDR',
		/* [206] */
		"Attribute title",
		'PSTR',
		/* [207] */
		"Attribute key",
		'TNAM',
		/* [208] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [209] */
		"Write to stream?",
		'BFLG',
		/* [210] */
		"Stream selector",
		'TNAM',
		/* [211] */
		"DMContainerAttribute data",
		'DVDR',
		/* [212] */
		"Is subobject list?",
		'BFLG',
		/* [213] */
		"Member class ID",
		'TNAM',
		/* [214] */
		"",
		'KEYE',
		/* [215] */
		"list",
		'KEYB',
		/* [216] */
		"DMAttribute data",
		'DVDR',
		/* [217] */
		"Attribute title",
		'PSTR',
		/* [218] */
		"Attribute key",
		'TNAM',
		/* [219] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [220] */
		"Write to stream?",
		'BFLG',
		/* [221] */
		"Stream selector",
		'TNAM',
		/* [222] */
		"DMContainerAttribute data",
		'DVDR',
		/* [223] */
		"Is subobject list?",
		'BFLG',
		/* [224] */
		"Member class ID",
		'TNAM',
		/* [225] */
		"DMListAttribute data",
		'DVDR',
		/* [226] */
		"Subitem title",
		'PSTR',
		/* [227] */
		"Number of bytes for count",
		'DLNG',
		/* [228] */
		"unused",
		'BB06',
		/* [229] */
		"Zero based display?",
		'BB01',
		/* [230] */
		"Zero-based count?",
		'BB01',
		/* [231] */
		"",
		'KEYE',
		/* [232] */
		"bitf",
		'KEYB',
		/* [233] */
		"DMAttribute data",
		'DVDR',
		/* [234] */
		"Attribute title",
		'PSTR',
		/* [235] */
		"Attribute key",
		'TNAM',
		/* [236] */
		"Display in attribute inspectors?",
		'BFLG',
		/* [237] */
		"Write to stream?",
		'BFLG',
		/* [238] */
		"Stream selector",
		'TNAM',
		/* [239] */
		"DMContainerAttribute data",
		'DVDR',
		/* [240] */
		"Is subobject list?",
		'BFLG',
		/* [241] */
		"Member class ID",
		'TNAM',
		/* [242] */
		"DMBitfieldAttribute data",
		'DVDR',
		/* [243] */
		"Bitfield size (bytes)",
		'UWRD',
		/* [244] */
		"",
		'KEYE',
		/* [245] */
		"labl",
		'KEYB',
		/* [246] */
		"Value",
		'DLNG',
		/* [247] */
		"Label",
		'PSTR',
		/* [248] */
		"",
		'KEYE',
		/* [249] */
		"rsco",
		'KEYB',
		/* [250] */
		"CTYP for resource type",
		'DWRD',
		/* [251] */
		"CTYP for resource",
		'DWRD',
		/* [252] */
		"Resource IDs significant?",
		'BFLG',
		/* [253] */
		"",
		'KEYE',
		/* [254] */
		"vetl",
		'KEYB',
		/* [255] */
		"VECP resource ID",
		'DWRD',
		/* [256] */
		"Class IDs significant?",
		'BFLG',
		/* [257] */
		"",
		'KEYE',
		/* [258] */
		"ctmo",
		'KEYB',
		/* [259] */
		"Object type",
		'PSTR',
		/* [260] */
		"Object type ID",
		'TNAM',
		/* [261] */
		"Parent type ID",
		'TNAM',
		/* [262] */
		"",
		'KEYE',
		/* [263] */
		"null",
		'KEYB',
		/* [264] */
		"",
		'KEYE',
		/* [265] */
		"",
		'KEYB',
		/* [266] */
		"Unknown data",
		'HEXD',
		/* [267] */
		"",
		'KEYE',
		/* [268] */
		"",
		'SKPE',
		/* [269] */
		"",
		'KEYE',
		/* [270] */
		"begs",
		'KEYB',
		/* [271] */
		"",
		'KEYE',
		/* [272] */
		"ends",
		'KEYB',
		/* [273] */
		"",
		'KEYE',
		/* [274] */
		"user",
		'KEYB',
		/* [275] */
		"SuperClass ID for next object",
		'TNAM',
		/* [276] */
		"",
		'KEYE',
		/* [277] */
		"dopl",
		'KEYB',
		/* [278] */
		"Class ID for next object",
		'TNAM',
		/* [279] */
		"",
		'KEYE',
		/* [280] */
		"end.",
		'KEYB',
		/* [281] */
		"This must be last object type in list",
		'DVDR',
		/* [282] */
		"",
		'KEYE',
		/* [283] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1395, "xdtl") {
	{	/* array: 63 elements */
		/* [1] */
		"Count:",
		'ZCNT',
		/* [2] */
		"List of Items",
		'LSTC',
		/* [3] */
		"Item type",
		'KWRD',
		/* [4] */
		"Radio button group=0",
		'CASE',
		/* [5] */
		"Check box=1",
		'CASE',
		/* [6] */
		"Integer edit text=2",
		'CASE',
		/* [7] */
		"Real edit text=3",
		'CASE',
		/* [8] */
		"String edit text=4",
		'CASE',
		/* [9] */
		"Pop up menu=5",
		'CASE',
		/* [10] */
		"0",
		'KEYB',
		/* [11] */
		"Type code for job/format storage",
		'TNAM',
		/* [12] */
		"Numeric code for storage",
		'DLNG',
		/* [13] */
		"Offset (in bytes) into tag item",
		'HWRD',
		/* [14] */
		"Count:",
		'ZCNT',
		/* [15] */
		"List of Buttons",
		'LSTC',
		/* [16] */
		"Corresponding 'DITL' item",
		'DBYT',
		/* [17] */
		"*****",
		'LSTE',
		/* [18] */
		"",
		'KEYE',
		/* [19] */
		"1",
		'KEYB',
		/* [20] */
		"Type code for job/format storage",
		'TNAM',
		/* [21] */
		"Numeric code for storage",
		'DLNG',
		/* [22] */
		"Offset (in bytes) into tag item",
		'HWRD',
		/* [23] */
		"Corresponding 'DITL' item",
		'DBYT',
		/* [24] */
		"Filler",
		'FBYT',
		/* [25] */
		"",
		'KEYE',
		/* [26] */
		"2",
		'KEYB',
		/* [27] */
		"Type code for job/format storage",
		'TNAM',
		/* [28] */
		"Numeric code for storage",
		'DLNG',
		/* [29] */
		"Offset (in bytes) into tag item",
		'HWRD',
		/* [30] */
		"Corresponding 'DITL' item",
		'DBYT',
		/* [31] */
		"Select",
		'BFLG',
		/* [32] */
		"Lower bound",
		'P010',
		/* [33] */
		"Don't care=",
		'CASE',
		/* [34] */
		"Upper bound",
		'P010',
		/* [35] */
		"Don't care=",
		'CASE',
		/* [36] */
		"",
		'KEYE',
		/* [37] */
		"3",
		'KEYB',
		/* [38] */
		"Type code for job/format storage",
		'TNAM',
		/* [39] */
		"Numeric code for storage",
		'DLNG',
		/* [40] */
		"Offset (in bytes) into tag item",
		'HWRD',
		/* [41] */
		"Corresponding 'DITL' item",
		'DBYT',
		/* [42] */
		"Select",
		'BFLG',
		/* [43] */
		"Lower bound",
		'P010',
		/* [44] */
		"Don't care=",
		'CASE',
		/* [45] */
		"Upper bound",
		'P010',
		/* [46] */
		"Don't care=",
		'CASE',
		/* [47] */
		"",
		'KEYE',
		/* [48] */
		"4",
		'KEYB',
		/* [49] */
		"Type code for job/format storage",
		'TNAM',
		/* [50] */
		"Numeric code for storage",
		'DLNG',
		/* [51] */
		"Offset (in bytes) into tag item",
		'HWRD',
		/* [52] */
		"Corresponding 'DITL' item",
		'DBYT',
		/* [53] */
		"Select",
		'BFLG',
		/* [54] */
		"",
		'KEYE',
		/* [55] */
		"5",
		'KEYB',
		/* [56] */
		"Type code for job/format storage",
		'TNAM',
		/* [57] */
		"Numeric code for storage",
		'DLNG',
		/* [58] */
		"Offset (in bytes) into tag item",
		'HWRD',
		/* [59] */
		"Corresponding 'DITL' item",
		'DBYT',
		/* [60] */
		"Filler",
		'FBYT',
		/* [61] */
		"",
		'KEYE',
		/* [62] */
		"Align",
		'AWRD',
		/* [63] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1396, "xMNU") {
	{	/* array: 23 elements */
		/* [1] */
		"Menu title",
		'P100',
		/* [2] */
		"Menu name",
		'TNAM',
		/* [3] */
		"Reserved flag 1",
		'BFLG',
		/* [4] */
		"Reserved flag 2",
		'BFLG',
		/* [5] */
		"Reserved",
		'F04C',
		/* [6] */
		"Count:",
		'OCNT',
		/* [7] */
		"List of items",
		'LSTC',
		/* [8] */
		"",
		'WSIZ',
		/* [9] */
		"Internal Command",
		'TNAM',
		/* [10] */
		"Key",
		'CHAR',
		/* [11] */
		"None=$00",
		'CASE',
		/* [12] */
		"Mark",
		'CHAR',
		/* [13] */
		"Glyph",
		'HWRD',
		/* [14] */
		"External command",
		'TNAM',
		/* [15] */
		"Ref constant",
		'HLNG',
		/* [16] */
		"Modifiers",
		'HBYT',
		/* [17] */
		"Reserved flag 1",
		'BFLG',
		/* [18] */
		"Reserved flag 2",
		'BFLG',
		/* [19] */
		"Key is virtual key code",
		'BFLG',
		/* [20] */
		"Reserved",
		'F048',
		/* [21] */
		"Name",
		'ESTR',
		/* [22] */
		"",
		'SKPE',
		/* [23] */
		"*****",
		'LSTE'
	}
};

resource 'TMPL' (1397, "xmnu") {
	{	/* array: 115 elements */
		/* [1] */
		"Version",
		'KWRD',
		/* [2] */
		"Version Zero=0",
		'CASE',
		/* [3] */
		"Version One=1",
		'CASE',
		/* [4] */
		"0",
		'KEYB',
		/* [5] */
		"Count:",
		'OCNT',
		/* [6] */
		"List of Item extensions",
		'LSTC',
		/* [7] */
		"Entry Type",
		'KWRD',
		/* [8] */
		"Skip Item=0",
		'CASE',
		/* [9] */
		"Data Item=1",
		'CASE',
		/* [10] */
		"0",
		'KEYB',
		/* [11] */
		"",
		'KEYE',
		/* [12] */
		"1",
		'KEYB',
		/* [13] */
		"Command ID",
		'TNAM',
		/* [14] */
		"Reserved",
		'BB04',
		/* [15] */
		"No command key modifier",
		'BBIT',
		/* [16] */
		"Control key modifier",
		'BBIT',
		/* [17] */
		"Option key modifier",
		'BBIT',
		/* [18] */
		"Shift key modifier",
		'BBIT',
		/* [19] */
		"Icon type placeholder",
		'FBYT',
		/* [20] */
		"Icon handle placeholder",
		'FLNG',
		/* [21] */
		"Text encoding",
		'DLNG',
		/* [22] */
		"Current script=-2",
		'CASE',
		/* [23] */
		"System script=-1",
		'CASE',
		/* [24] */
		"Reference constant 1",
		'ULNG',
		/* [25] */
		"Reference constant 2",
		'ULNG',
		/* [26] */
		"Hierarchical 'MENU' ID",
		'RSID',
		/* [27] */
		"None=0",
		'CASE',
		/* [28] */
		"Font ID",
		'DWRD',
		/* [29] */
		"System font=0",
		'CASE',
		/* [30] */
		"Keyboard Glyph",
		'DWRD',
		/* [31] */
		"Natural Glyph=0",
		'CASE',
		/* [32] */
		"Tab Right=2",
		'CASE',
		/* [33] */
		"Tab Left=3",
		'CASE',
		/* [34] */
		"Enter=4",
		'CASE',
		/* [35] */
		"Space=9",
		'CASE',
		/* [36] */
		"Delete Right=10",
		'CASE',
		/* [37] */
		"Return=11",
		'CASE',
		/* [38] */
		"Nonmarking Return=13",
		'CASE',
		/* [39] */
		"Pencil=15",
		'CASE',
		/* [40] */
		"Downward Arrow Dashed=16",
		'CASE',
		/* [41] */
		"Checkmark=18",
		'CASE',
		/* [42] */
		"Diamond=19",
		'CASE',
		/* [43] */
		"Apple Logo Filled=20",
		'CASE',
		/* [44] */
		"Delete Left=23",
		'CASE',
		/* [45] */
		"Left Arrow Dashed=24",
		'CASE',
		/* [46] */
		"Up Arrow Dashed=25",
		'CASE',
		/* [47] */
		"Right Arrow Dashed=26",
		'CASE',
		/* [48] */
		"Escape=27",
		'CASE',
		/* [49] */
		"Clear=28",
		'CASE',
		/* [50] */
		"Blank=97",
		'CASE',
		/* [51] */
		"Page Up=98",
		'CASE',
		/* [52] */
		"Caps Lock=99",
		'CASE',
		/* [53] */
		"Left Arrow=100",
		'CASE',
		/* [54] */
		"Right Arrow=101",
		'CASE',
		/* [55] */
		"Northwest Arrow=102",
		'CASE',
		/* [56] */
		"Help=103",
		'CASE',
		/* [57] */
		"Up Arrow=104",
		'CASE',
		/* [58] */
		"Southeast Arrow=105",
		'CASE',
		/* [59] */
		"Down Arrow=106",
		'CASE',
		/* [60] */
		"Page Down=107",
		'CASE',
		/* [61] */
		"Apple Logo Outline=108",
		'CASE',
		/* [62] */
		"Contextual Menu=109",
		'CASE',
		/* [63] */
		"Power=110",
		'CASE',
		/* [64] */
		"F1=111",
		'CASE',
		/* [65] */
		"F2=112",
		'CASE',
		/* [66] */
		"F3=113",
		'CASE',
		/* [67] */
		"F4=114",
		'CASE',
		/* [68] */
		"F5=115",
		'CASE',
		/* [69] */
		"F6=116",
		'CASE',
		/* [70] */
		"F7=117",
		'CASE',
		/* [71] */
		"F8=118",
		'CASE',
		/* [72] */
		"F9=119",
		'CASE',
		/* [73] */
		"F10=120",
		'CASE',
		/* [74] */
		"F11=121",
		'CASE',
		/* [75] */
		"F12=122",
		'CASE',
		/* [76] */
		"F13=135",
		'CASE',
		/* [77] */
		"F14=136",
		'CASE',
		/* [78] */
		"F15=137",
		'CASE',
		/* [79] */
		"",
		'KEYE',
		/* [80] */
		"*****",
		'LSTE',
		/* [81] */
		"",
		'KEYE',
		/* [82] */
		"1",
		'KEYB',
		/* [83] */
		"Count:",
		'OCNT',
		/* [84] */
		"List of Item extensions",
		'LSTC',
		/* [85] */
		"Entry Type",
		'KWRD',
		/* [86] */
		"Skip Item=0",
		'CASE',
		/* [87] */
		"Data Item=1",
		'CASE',
		/* [88] */
		"0",
		'KEYB',
		/* [89] */
		"",
		'KEYE',
		/* [90] */
		"1",
		'KEYB',
		/* [91] */
		"Command ID",
		'TNAM',
		/* [92] */
		"Reserved",
		'BB04',
		/* [93] */
		"No command key modifier",
		'BBIT',
		/* [94] */
		"Control key modifier",
		'BBIT',
		/* [95] */
		"Option key modifier",
		'BBIT',
		/* [96] */
		"Shift key modifier",
		'BBIT',
		/* [97] */
		"Virtual keycode for command key",
		'HBYT',
		/* [98] */
		"No virtual key=0",
		'CASE',
		/* [99] */
		"Menu item attributes",
		'HLNG',
		/* [100] */
		"No attributes=0",
		'CASE',
		/* [101] */
		"Text encoding",
		'ULNG',
		/* [102] */
		"Current script=-2",
		'CASE',
		/* [103] */
		"System script=-1",
		'CASE',
		/* [104] */
		"Reference constant",
		'ULNG',
		/* [105] */
		"Indent",
		'ULNG',
		/* [106] */
		"No indent=0",
		'CASE',
		/* [107] */
		"Hierarchical 'MENU' ID",
		'RSID',
		/* [108] */
		"None=0",
		'CASE',
		/* [109] */
		"Font ID",
		'DWRD',
		/* [110] */
		"System font=0",
		'CASE',
		/* [111] */
		"Keyboard Glyph",
		'DWRD',
		/* [112] */
		"Natural Glyph=0",
		'CASE',
		/* [113] */
		"",
		'KEYE',
		/* [114] */
		"*****",
		'LSTE',
		/* [115] */
		"",
		'KEYE'
	}
};

resource 'TMPL' (1398, "ZOOM") {
	{	/* array: 21 elements */
		/* [1] */
		"Doing zooming rectangles?",
		'WFLG',
		/* [2] */
		"Custom zooms=1",
		'CASE',
		/* [3] */
		"Nope=0",
		'CASE',
		/* [4] */
		"Governor delay (in ticks)",
		'DWRD',
		/* [5] */
		"Standard=1",
		'CASE',
		/* [6] */
		"Fast as possible=0",
		'CASE',
		/* [7] */
		"Real slow (Shift key)=7",
		'CASE',
		/* [8] */
		"Thickness",
		'DWRD',
		/* [9] */
		"Best=2",
		'CASE',
		/* [10] */
		"Standard=1",
		'CASE',
		/* [11] */
		"Queue length (32 max)",
		'DWRD',
		/* [12] */
		"Standard=4",
		'CASE',
		/* [13] */
		"One rect only=1",
		'CASE',
		/* [14] */
		"Zoom style",
		'DWRD',
		/* [15] */
		"Smart FEZ=4",
		'CASE',
		/* [16] */
		"FEZ=3",
		'CASE',
		/* [17] */
		"One dive=2",
		'CASE',
		/* [18] */
		"Old style=1",
		'CASE',
		/* [19] */
		"None=0",
		'CASE',
		/* [20] */
		"Reserved",
		'FLNG',
		/* [21] */
		"Reserved",
		'FLNG'
	}
};

resource 'TMPL' (1399, "¤DTD") {
	{	/* array: 30 elements */
		/* [1] */
		"Version (should be 1 as of 980622)",
		'HWRD',
		/* [2] */
		"Count:",
		'OCNT',
		/* [3] */
		"DTD Strings",
		'LSTC',
		/* [4] */
		"DTD String",
		'PSTR',
		/* [5] */
		"",
		'LSTE',
		/* [6] */
		"Align",
		'AWRD',
		/* [7] */
		"Tag Count",
		'OCNT',
		/* [8] */
		"Tags",
		'LSTC',
		/* [9] */
		"Tag name",
		'PSTR',
		/* [10] */
		"Align",
		'AWRD',
		/* [11] */
		"Has close tag?",
		'DBYT',
		/* [12] */
		"Can contain text?",
		'DBYT',
		/* [13] */
		"Close tag required?",
		'DBYT',
		/* [14] */
		"Reserved",
		'FBYT',
		/* [15] */
		"Valid container tags (bullet seperated s"
		"tring)",
		'WSTR',
		/* [16] */
		"Align",
		'AWRD',
		/* [17] */
		"Reserved (exceptions to the above)",
		'WSTR',
		/* [18] */
		"Align",
		'AWRD',
		/* [19] */
		"Count:",
		'OCNT',
		/* [20] */
		"Tag attributes",
		'LSTC',
		/* [21] */
		"Attribute name",
		'PSTR',
		/* [22] */
		"Align",
		'AWRD',
		/* [23] */
		"Attribute is required?",
		'DBYT',
		/* [24] */
		"Value is required?",
		'DBYT',
		/* [25] */
		"Value type",
		'DBYT',
		/* [26] */
		"Reserved",
		'FBYT',
		/* [27] */
		"Enumerated values (bullet seperated stri"
		"ng)",
		'WSTR',
		/* [28] */
		"Align",
		'AWRD',
		/* [29] */
		"",
		'LSTE',
		/* [30] */
		"",
		'LSTE'
	}
};

resource 'TMPL' (1400, "µVal") {
	{	/* array: 14 elements */
		/* [1] */
		"\"AfterDark\" resource format",
		'DVDR',
		/* [2] */
		"Sound available",
		'BBIT',
		/* [3] */
		"Reserved",
		'BB04',
		/* [4] */
		"Running under MultiModule",
		'BBIT',
		/* [5] */
		"Can't change color environment",
		'BBIT',
		/* [6] */
		"Main monitor can dim",
		'BBIT',
		/* [7] */
		"All monitors can dim",
		'BBIT',
		/* [8] */
		"All monitors must be CLUT devices",
		'BBIT',
		/* [9] */
		"A monitor must be a CLUT device",
		'BBIT',
		/* [10] */
		"All monitors must be in color mode",
		'BBIT',
		/* [11] */
		"A monitor must be in color mode",
		'BBIT',
		/* [12] */
		"All monitors must be > 1 bit",
		'BBIT',
		/* [13] */
		"A monitor must be > 1 bit",
		'BBIT',
		/* [14] */
		"Must have Color QuickDraw",
		'BBIT'
	}
};

