#include <Carbon/Carbon.r>

resource 'MBAR' (128, "Standard") {
	{	/* array MenuArray: 5 elements */
		/* [1] */
		128,
		/* [2] */
		129,
		/* [3] */
		130,
		/* [4] */
		133,
		/* [5] */
		255
	}
};

resource 'MBAR' (129, "Aqua") {
	{	/* array MenuArray: 5 elements */
		/* [1] */
		128,
		/* [2] */
		132,
		/* [3] */
		130,
		/* [4] */
		133,
		/* [5] */
		255
	}
};

resource 'MENU' (128, "Apple Menu") {
	128,
	textMenuProc,
	allEnabled,
	enabled,
	apple,
	{	/* array: 1 elements */
		/* [1] */
		"About Rezilla…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (129, "File Menu") {
	129,
	textMenuProc,
	0x7FFFFA1F,
	enabled,
	"File",
	{	/* array: 12 elements */
		/* [1] */
		"New Resource Map", noIcon, "N", noMark, plain,
		/* [2] */
		"Open…", noIcon, "O", noMark, plain,
		/* [3] */
		"Recent Items", noIcon, hierarchicalMenu, "å", plain,
		/* [4] */
		"Close", noIcon, "W", noMark, plain,
		/* [5] */
		"Revert", noIcon, noKey, noMark, plain,
		/* [6] */
		"-", noIcon, noKey, noMark, plain,
		/* [7] */
		"Save", noIcon, "S", noMark, plain,
		/* [8] */
		"Save As…", noIcon, noKey, noMark, plain,
		/* [9] */
		"-", noIcon, noKey, noMark, plain,
		/* [10] */
		"Export…", noIcon, noKey, noMark, plain,
		/* [11] */
		"-", noIcon, noKey, noMark, plain,
		/* [12] */
		"Quit", noIcon, "Q", noMark, plain
	}
};

resource 'MENU' (130, "Edit Menu") {
	130,
	textMenuProc,
	0x7FFFFB7D,
	enabled,
	"Edit",
	{	/* array: 12 elements */
		/* [1] */
		"Undo", noIcon, "Z", noMark, plain,
		/* [2] */
		"-", noIcon, noKey, noMark, plain,
		/* [3] */
		"Cut", noIcon, "X", noMark, plain,
		/* [4] */
		"Copy", noIcon, "C", noMark, plain,
		/* [5] */
		"Paste", noIcon, "V", noMark, plain,
		/* [6] */
		"Clear", noIcon, noKey, noMark, plain,
		/* [7] */
		"Select All", noIcon, "A", noMark, plain,
		/* [8] */
		"-", noIcon, noKey, noMark, plain,
		/* [9] */
		"Find…", noIcon, "F", noMark, plain,
		/* [10] */
		"Find Next", noIcon, "G", noMark, plain,
		/* [11] */
		"-", noIcon, noKey, noMark, plain,
		/* [12] */
		"Compare Resource Maps…", noIcon, "K", noMark, plain
	}
};

resource 'MENU' (131, "Plugins Menu") {
	131,
	textMenuProc,
	allEnabled,
	enabled,
	"Plugins",
	{	/* array: 2 elements */
		/* [1] */
		"Plugins Info", noIcon, "B", noMark, plain,
		/* [2] */
		"Type Editors Table", noIcon, "T", noMark, plain
	}
};

resource 'MENU' (132, "File Menu Aqua") {
	132,
	textMenuProc,
	0x7FFFFE1F,
	enabled,
	"File",
	{	/* array: 10 elements */
		/* [1] */
		"New Resource Map", noIcon, "N", noMark, plain,
		/* [2] */
		"Open…", noIcon, "O", noMark, plain,
		/* [3] */
		"Recent Items", noIcon, hierarchicalMenu, "å", plain,
		/* [4] */
		"Close", noIcon, "W", noMark, plain,
		/* [5] */
		"Revert", noIcon, noKey, noMark, plain,
		/* [6] */
		"-", noIcon, noKey, noMark, plain,
		/* [7] */
		"Save", noIcon, "S", noMark, plain,
		/* [8] */
		"Save As…", noIcon, noKey, noMark, plain,
		/* [9] */
		"-", noIcon, noKey, noMark, plain,
		/* [10] */
		"Export…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (140, "Recent Items Menu") {
	140,
	textMenuProc,
	allEnabled,
	enabled,
	"Menu",
	{	/* array: 0 elements */
	}
};

resource 'MENU' (250, "Text Font") {
	250,
	textMenuProc,
	allEnabled,
	enabled,
	"Font",
	{	/* array: 0 elements */
	}
};

resource 'MENU' (251, "Text Size") {
	251,
	textMenuProc,
	0x7FFFFDFF,
	enabled,
	"Size",
	{	/* array: 11 elements */
		/* [1] */
		"6 pt", noIcon, noKey, noMark, plain,
		/* [2] */
		"8 pt", noIcon, noKey, noMark, plain,
		/* [3] */
		"9 pt", noIcon, noKey, noMark, plain,
		/* [4] */
		"10 pt", noIcon, noKey, noMark, plain,
		/* [5] */
		"12 pt", noIcon, noKey, noMark, plain,
		/* [6] */
		"14 pt", noIcon, noKey, noMark, plain,
		/* [7] */
		"18 pt", noIcon, noKey, noMark, plain,
		/* [8] */
		"24 pt", noIcon, noKey, noMark, plain,
		/* [9] */
		"36 pt", noIcon, noKey, noMark, plain,
		/* [10] */
		"-", noIcon, noKey, noMark, plain,
		/* [11] */
		"Other…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (252, "Text Style") {
	252,
	textMenuProc,
	0x7FFFFEFF,
	enabled,
	"Style",
	{	/* array: 10 elements */
		/* [1] */
		"Plain", noIcon, noKey, noMark, plain,
		/* [2] */
		"Bold", noIcon, noKey, noMark, 1,
		/* [3] */
		"Italic", noIcon, noKey, noMark, 2,
		/* [4] */
		"Underline", noIcon, noKey, noMark, 4,
		/* [5] */
		"Outline", noIcon, noKey, noMark, 8,
		/* [6] */
		"Shadow", noIcon, noKey, noMark, 16,
		/* [7] */
		"Condense", noIcon, noKey, noMark, 32,
		/* [8] */
		"Extend", noIcon, noKey, noMark, 64,
		/* [9] */
		"-", noIcon, noKey, noMark, plain,
		/* [10] */
		"Wrap text", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (150, "Template CASE Menu") {
	150,
	textMenuProc,
	allEnabled,
	enabled,
	"Menu",
	{	/* array: 0 elements */
	}
};

resource 'MENU' (253, "Types") {
	253,
	textMenuProc,
	allEnabled,
	enabled,
	"Types",
	{	/* array: 1 elements */
		/* [1] */
		"   ", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (254, "Empty Font") {
	254,
	textMenuProc,
	allEnabled,
	enabled,
	"Font",
	{	/* array: 0 elements */
	}
};

resource 'MENU' (255, "Unicode Font") {
	255,
	textMenuProc,
	allEnabled,
	enabled,
	"Font",
	{	/* array: 0 elements */
	}
};

resource 'MENU' (256, "Unicode Size") {
	256,
	textMenuProc,
	0x7FFFFDFF,
	enabled,
	"Size",
	{	/* array: 12 elements */
		/* [1] */
		"9 pt", noIcon, noKey, noMark, plain,
		/* [2] */
		"10 pt", noIcon, noKey, noMark, plain,
		/* [3] */
		"11 pt", noIcon, noKey, noMark, plain,
		/* [4] */
		"12 pt", noIcon, noKey, noMark, plain,
		/* [5] */
		"14 pt", noIcon, noKey, noMark, plain,
		/* [6] */
		"16 pt", noIcon, noKey, noMark, plain,
		/* [7] */
		"18 pt", noIcon, noKey, noMark, plain,
		/* [8] */
		"24 pt", noIcon, noKey, noMark, plain,
		/* [9] */
		"36 pt", noIcon, noKey, noMark, plain,
		/* [10] */
		"-", noIcon, noKey, noMark, plain,
		/* [11] */
		"Smaller", noIcon, "-", noMark, plain,
		/* [12] */
		"Larger", noIcon, "+", noMark, plain
	}
};

resource 'MENU' (257, "Unicode Style") {
	257,
	textMenuProc,
	allEnabled,
	enabled,
	"Style",
	{	/* array: 4 elements */
		/* [1] */
		"Plain", noIcon, noKey, noMark, plain,
		/* [2] */
		"Bold", noIcon, noKey, noMark, 1,
		/* [3] */
		"Italic", noIcon, noKey, noMark, 2,
		/* [4] */
		"Underline", noIcon, noKey, noMark, 4
	}
};

resource 'MENU' (300, "Icon Actions") {
	300,
	textMenuProc,
	0x7FFFFF5B,
	enabled,
	"Actions",
	{	/* array: 10 elements */
		/* [1] */
		"Flip Vertical", noIcon, "V", noMark, plain,
		/* [2] */
		"Flip Horizontal", noIcon, "H", noMark, plain,
		/* [3] */
		"-", noIcon, noKey, noMark, plain,
		/* [4] */
		"Rotate Right", noIcon, "R", noMark, plain,
		/* [5] */
		"Rotate Left", noIcon, "L", noMark, plain,
		/* [6] */
		"-", noIcon, noKey, noMark, plain,
		/* [7] */
		"Make Transparent", noIcon, "T", noMark, plain,
		/* [8] */
		"-", noIcon, noKey, noMark, plain,
		/* [9] */
		"Delete Image", noIcon, noKey, noMark, plain,
		/* [10] */
		"Set Image Size…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (301, "Icon Colors") {
	301,
	textMenuProc,
	0x7FFFFF7F,
	enabled,
	"Colors",
	{	/* array: 11 elements */
		/* [1] */
		"Icon Colors", noIcon, noKey, noMark, plain,
		/* [2] */
		"256 Colors", noIcon, noKey, noMark, plain,
		/* [3] */
		"256 Grays", noIcon, noKey, noMark, plain,
		/* [4] */
		"16 Colors", noIcon, noKey, noMark, plain,
		/* [5] */
		"16 Grays", noIcon, noKey, noMark, plain,
		/* [6] */
		"4 Grays", noIcon, noKey, noMark, plain,
		/* [7] */
		"Use Color Picker", noIcon, noKey, noMark, plain,
		/* [8] */
		"-", noIcon, noKey, noMark, plain,
		/* [9] */
		"Select Black & White", noIcon, noKey, noMark, plain,
		/* [10] */
		"Swap Selected Colors", noIcon, noKey, noMark, plain,
		/* [11] */
		"Apply Current Table", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (303, "Icon Style") {
	303,
	textMenuProc,
	0x7FFDFEFF,
	enabled,
	"Style",
	{	/* array: 21 elements */
		/* [1] */
		"Plain", noIcon, noKey, noMark, plain,
		/* [2] */
		"Bold", noIcon, noKey, noMark, 1,
		/* [3] */
		"Italic", noIcon, noKey, noMark, 2,
		/* [4] */
		"Underline", noIcon, noKey, noMark, 4,
		/* [5] */
		"Outline", noIcon, noKey, noMark, 8,
		/* [6] */
		"Shadow", noIcon, noKey, noMark, 16,
		/* [7] */
		"Condense", noIcon, noKey, noMark, 32,
		/* [8] */
		"Extend", noIcon, noKey, noMark, 64,
		/* [9] */
		"-", noIcon, noKey, noMark, plain,
		/* [10] */
		"9 pt", noIcon, noKey, noMark, plain,
		/* [11] */
		"10 pt", noIcon, noKey, noMark, plain,
		/* [12] */
		"12 pt", noIcon, noKey, noMark, plain,
		/* [13] */
		"14 pt", noIcon, noKey, noMark, plain,
		/* [14] */
		"18 pt", noIcon, noKey, noMark, plain,
		/* [15] */
		"24 pt", noIcon, noKey, noMark, plain,
		/* [16] */
		"36 pt", noIcon, noKey, noMark, plain,
		/* [17] */
		"Other...", noIcon, noKey, noMark, plain,
		/* [18] */
		"-", noIcon, noKey, noMark, plain,
		/* [19] */
		"Left Justified", noIcon, noKey, noMark, plain,
		/* [20] */
		"Centered", noIcon, noKey, noMark, plain,
		/* [21] */
		"Right Justified", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (302, "Icon Font") {
	302,
	textMenuProc,
	allEnabled,
	enabled,
	"Font",
	{	/* array: 0 elements */
	}
};

resource 'MENU' (133, "Resources Menu") {
	133,
	textMenuProc,
	0x7FFFFB5D,
	enabled,
	"Resources",
	{	/* array: 12 elements */
		/* [1] */
		"New Resource…", noIcon, "N", noMark, plain,
		/* [2] */
		"-", noIcon, noKey, noMark, plain,
		/* [3] */
		"Edit", noIcon, "E", noMark, plain,
		/* [4] */
		"Template Editor", noIcon, "E", noMark, plain,
		/* [5] */
		"Hexadecimal Editor", noIcon, "E", noMark, plain,
		/* [6] */
		"-", noIcon, noKey, noMark, plain,
		/* [7] */
		"Edit as Type…", noIcon, "E", noMark, plain,
		/* [8] */
		"-", noIcon, noKey, noMark, plain,
		/* [9] */
		"Remove", noIcon, noKey, noMark, plain,
		/* [10] */
		"Duplicate", noIcon, "D", noMark, plain,
		/* [11] */
		"-", noIcon, noKey, noMark, plain,
		/* [12] */
		"Get Info", noIcon, "I", noMark, plain
	}
};

resource 'MENU' (160, "Aete Menu") {
	160,
	textMenuProc,
	0x7FEDB6DB,
	enabled,
	"Terminology",
	{	/* array: 23 elements */
		/* [1] */
		"Add Suite", noIcon, noKey, noMark, plain,
		/* [2] */
		"Remove Suite", noIcon, noKey, noMark, plain,
		/* [3] */
		"-", noIcon, noKey, noMark, plain,
		/* [4] */
		"Add Item", noIcon, noKey, noMark, plain,
		/* [5] */
		"Remove Item", noIcon, noKey, noMark, plain,
		/* [6] */
		"-", noIcon, noKey, noMark, plain,
		/* [7] */
		"Add Parameter", noIcon, noKey, noMark, plain,
		/* [8] */
		"Remove Parameter", noIcon, noKey, noMark, plain,
		/* [9] */
		"-", noIcon, noKey, noMark, plain,
		/* [10] */
		"Add Property", noIcon, noKey, noMark, plain,
		/* [11] */
		"Remove Property", noIcon, noKey, noMark, plain,
		/* [12] */
		"-", noIcon, noKey, noMark, plain,
		/* [13] */
		"Add Element", noIcon, noKey, noMark, plain,
		/* [14] */
		"Remove Element", noIcon, noKey, noMark, plain,
		/* [15] */
		"-", noIcon, noKey, noMark, plain,
		/* [16] */
		"Add Key Form", noIcon, noKey, noMark, plain,
		/* [17] */
		"Remove Key Form", noIcon, noKey, noMark, plain,
		/* [18] */
		"-", noIcon, noKey, noMark, plain,
		/* [19] */
		"Add Enumerator", noIcon, noKey, noMark, plain,
		/* [20] */
		"Remove Enumerator", noIcon, noKey, noMark, plain,
		/* [21] */
		"-", noIcon, noKey, noMark, plain,
		/* [22] */
		"Import Terminology…", noIcon, noKey, noMark, plain,
		/* [23] */
		"Export Terminology…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (163, "Event other param  options") {
	163,
	textMenuProc,
	allEnabled,
	enabled,
	"OtherParam",
	{	/* array: 12 elements */
		/* [1] */
		"Options", noIcon, noKey, noMark, 1,
		/* [2] */
		"Is optional", noIcon, noKey, noMark, plain,
		/* [3] */
		"Is list of items", noIcon, noKey, noMark, plain,
		/* [4] */
		"Is enumerated", noIcon, noKey, noMark, plain,
		/* [5] */
		"Enums are types", noIcon, noKey, noMark, plain,
		/* [6] */
		"Enum list doesn't repeat", noIcon, noKey, noMark, plain,
		/* [7] */
		"Is reference (not value)", noIcon, noKey, noMark, plain,
		/* [8] */
		"Param is target", noIcon, noKey, noMark, plain,
		/* [9] */
		"Labeled param name", noIcon, noKey, noMark, plain,
		/* [10] */
		"Feminine", noIcon, noKey, noMark, plain,
		/* [11] */
		"Masculine", noIcon, noKey, noMark, plain,
		/* [12] */
		"Plural", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (164, "Class property options") {
	164,
	textMenuProc,
	allEnabled,
	enabled,
	"Property",
	{	/* array: 11 elements */
		/* [1] */
		"Options", noIcon, noKey, noMark, 1,
		/* [2] */
		"Is list of items", noIcon, noKey, noMark, plain,
		/* [3] */
		"Is enumerated", noIcon, noKey, noMark, plain,
		/* [4] */
		"Is writable", noIcon, noKey, noMark, plain,
		/* [5] */
		"Enums are types", noIcon, noKey, noMark, plain,
		/* [6] */
		"Enum list doesn't repeat", noIcon, noKey, noMark, plain,
		/* [7] */
		"Is reference (not value)", noIcon, noKey, noMark, plain,
		/* [8] */
		"Apostrophe", noIcon, noKey, noMark, plain,
		/* [9] */
		"Feminine", noIcon, noKey, noMark, plain,
		/* [10] */
		"Masculine", noIcon, noKey, noMark, plain,
		/* [11] */
		"Plural", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (162, "Event reply's options") {
	162,
	textMenuProc,
	allEnabled,
	enabled,
	"Reply",
	{	/* array: 9 elements */
		/* [1] */
		"Options", noIcon, noKey, noMark, 1,
		/* [2] */
		"Is optional", noIcon, noKey, noMark, plain,
		/* [3] */
		"Is list of items", noIcon, noKey, noMark, plain,
		/* [4] */
		"Is enumerated", noIcon, noKey, noMark, plain,
		/* [5] */
		"Tight binding function", noIcon, noKey, noMark, plain,
		/* [6] */
		"Enums are types", noIcon, noKey, noMark, plain,
		/* [7] */
		"Enum list doesn't repeat", noIcon, noKey, noMark, plain,
		/* [8] */
		"Is reference (not value)", noIcon, noKey, noMark, plain,
		/* [9] */
		"Non verb event", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (161, "Event direct param options") {
	161,
	textMenuProc,
	allEnabled,
	enabled,
	"DirParam",
	{	/* array: 9 elements */
		/* [1] */
		"Options", noIcon, noKey, noMark, 1,
		/* [2] */
		"Is optional", noIcon, noKey, noMark, plain,
		/* [3] */
		"Is list of items", noIcon, noKey, noMark, plain,
		/* [4] */
		"Is enumerated", noIcon, noKey, noMark, plain,
		/* [5] */
		"Changes state", noIcon, noKey, noMark, plain,
		/* [6] */
		"Enums are types", noIcon, noKey, noMark, plain,
		/* [7] */
		"Enum list doesn't repeat", noIcon, noKey, noMark, plain,
		/* [8] */
		"Is reference (not value)", noIcon, noKey, noMark, plain,
		/* [9] */
		"Is not target", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (305, "Icns Types") {
	305,
	textMenuProc,
	0x7FFDFEFF,
	enabled,
	"Icns types",
	{	/* array: 30 elements */
		/* [1] */
		"Thumbnail 32 Bit Data ('it32')", noIcon, noKey, noMark, plain,
		/* [2] */
		"Thumbnail 8 Bit Mask ('t8mk')", noIcon, noKey, noMark, plain,
		/* [3] */
		"-", noIcon, noKey, noMark, plain,
		/* [4] */
		"Huge 1 Bit Mask ('ich#')", noIcon, noKey, noMark, plain,
		/* [5] */
		"Huge 4 Bit Data ('ich4')", noIcon, noKey, noMark, plain,
		/* [6] */
		"Huge 8 Bit Data ('ich8')", noIcon, noKey, noMark, plain,
		/* [7] */
		"Huge 32 Bit Data ('ih32')", noIcon, noKey, noMark, plain,
		/* [8] */
		"Huge 8 Bit Mask ('h8mk')", noIcon, noKey, noMark, plain,
		/* [9] */
		"-", noIcon, noKey, noMark, plain,
		/* [10] */
		"Large 1 Bit Mask ('ICN#')", noIcon, noKey, noMark, plain,
		/* [11] */
		"Large 4 Bit Data ('icl4')", noIcon, noKey, noMark, plain,
		/* [12] */
		"Large 8 Bit Data ('icl8')", noIcon, noKey, noMark, plain,
		/* [13] */
		"Large 32 Bit Data ('il32')", noIcon, noKey, noMark, plain,
		/* [14] */
		"Large 8 Bit Mask ('l8mk')", noIcon, noKey, noMark, plain,
		/* [15] */
		"-", noIcon, noKey, noMark, plain,
		/* [16] */
		"Small 1 Bit Mask ('ics#')", noIcon, noKey, noMark, plain,
		/* [17] */
		"Small 4 Bit Data ('ics4')", noIcon, noKey, noMark, plain,
		/* [18] */
		"Small 8 Bit Data ('ics8')", noIcon, noKey, noMark, plain,
		/* [19] */
		"Small 32 Bit Data ('is32')", noIcon, noKey, noMark, plain,
		/* [20] */
		"Small 8 Bit Mask ('s8mk')", noIcon, noKey, noMark, plain,
		/* [21] */
		"-", noIcon, noKey, noMark, plain,
		/* [22] */
		"Mini 1 Bit Mask ('icm#')", noIcon, noKey, noMark, plain,
		/* [23] */
		"Mini 4 Bit Data ('icm4')", noIcon, noKey, noMark, plain,
		/* [24] */
		"Mini 8 Bit Data ('icm8')", noIcon, noKey, noMark, plain,
		/* [25] */
		"-", noIcon, noKey, noMark, plain,
		/* [26] */
		"Tile Icon Variant ('tile')", noIcon, noKey, noMark, plain,
		/* [27] */
		"Rollover Icon Variant ('over')", noIcon, noKey, noMark, plain,
		/* [28] */
		"Drop Icon Variant ('drop')", noIcon, noKey, noMark, plain,
		/* [29] */
		"Open Icon Variant ('open')", noIcon, noKey, noMark, plain,
		/* [30] */
		"Open Drop Icon Variant ('odrp')", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (258, "Menu item Style") {
	258,
	textMenuProc,
	0x7FFFFFFD,
	enabled,
	"",
	{	/* array: 10 elements */
		/* [1] */
		"Style", noIcon, noKey, noMark, plain,
		/* [2] */
		"-", noIcon, noKey, noMark, plain,
		/* [3] */
		"Plain", noIcon, noKey, noMark, plain,
		/* [4] */
		"Bold", noIcon, noKey, noMark, 1,
		/* [5] */
		"Italic", noIcon, noKey, noMark, 2,
		/* [6] */
		"Underline", noIcon, noKey, noMark, 4,
		/* [7] */
		"Outline", noIcon, noKey, noMark, 8,
		/* [8] */
		"Shadow", noIcon, noKey, noMark, 16,
		/* [9] */
		"Condense", noIcon, noKey, noMark, 32,
		/* [10] */
		"Extend", noIcon, noKey, noMark, 64
	}
};

resource 'MENU' (259, "Menu item property") {
	259,
	textMenuProc,
	allEnabled,
	enabled,
	"",
	{	/* array: 7 elements */
		/* [1] */
		"none", noIcon, noKey, noMark, plain,
		/* [2] */
		"is separator line", noIcon, noKey, noMark, plain,
		/* [3] */
		"has submenu", noIcon, noKey, noMark, plain,
		/* [4] */
		"uses 'cicn' icon", noIcon, noKey, noMark, plain,
		/* [5] */
		"uses 'ICON' icon", noIcon, noKey, noMark, plain,
		/* [6] */
		"uses 'SICN' icon", noIcon, noKey, noMark, plain,
		/* [7] */
		"uses non system script", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (260, "Empty Popup") {
	260,
	textMenuProc,
	allEnabled,
	enabled,
	"Empty",
	{	/* array: 0 elements */
	}
};

resource 'MENU' (261, "Preferences Font Size") {
	261,
	textMenuProc,
	0x7FFFFDFF,
	enabled,
	"Size",
	{	/* array: 11 elements */
		/* [1] */
		"6", noIcon, noKey, noMark, plain,
		/* [2] */
		"8", noIcon, noKey, noMark, plain,
		/* [3] */
		"9", noIcon, noKey, noMark, plain,
		/* [4] */
		"10", noIcon, noKey, noMark, plain,
		/* [5] */
		"12", noIcon, noKey, noMark, plain,
		/* [6] */
		"14", noIcon, noKey, noMark, plain,
		/* [7] */
		"18", noIcon, noKey, noMark, plain,
		/* [8] */
		"24", noIcon, noKey, noMark, plain,
		/* [9] */
		"36", noIcon, noKey, noMark, plain,
		/* [10] */
		"-", noIcon, noKey, noMark, plain,
		/* [11] */
		"Other…", noIcon, noKey, noMark, plain
	}
};

data 'Mcmd' (128, "Apple Menu") {
	$"0001 0000 0001"                                     /* ...... */
};

data 'Mcmd' (129, "File Menu") {
	$"000C 0000 0002 0000 0003 0000 03EA 0000"            /* .............Í.. */
	$"0004 0000 0007 0000 0000 0000 0005 0000"            /* ................ */
	$"0006 0000 0000 0000 03E9 0000 0000 0000"            /* .........È...... */
	$"000A"                                               /* .¬ */
};

data 'Mcmd' (130, "Edit Menu") {
	$"000C 0000 000B 0000 0000 0000 000C 0000"            /* ................ */
	$"000D 0000 000E 0000 000F 0000 0010 0000"            /* ................ */
	$"0000 0000 044D 0000 044E 0000 0000 0000"            /* .....M...N...... */
	$"044F"                                               /* .O */
};

data 'Mcmd' (131, "Plugins Menu") {
	$"0002 6252 7352 6564 5442"                           /* ..bRsRedTB */
};

data 'Mcmd' (132, "File Menu Aqua") {
	$"000A 0000 0002 0000 0003 0000 03EA 0000"            /* .¬...........Í.. */
	$"0004 0000 0007 0000 0000 0000 0005 0000"            /* ................ */
	$"0006 0000 0000 0000 03E9"                           /* .........È */
};

data 'Mcmd' (251, "Text Size") {
	$"000B 0000 057E 0000 0580 0000 0581 0000"            /* .....~...Ä...Å.. */
	$"0582 0000 0584 0000 0586 0000 058A 0000"            /* .Ç...Ñ...Ü...ä.. */
	$"0590 0000 059C 0000 0000 0000 012F"                 /* .ê...ú......./ */
};

data 'Mcmd' (252, "Text Style") {
	$"000A 0000 0191 0000 0192 0000 0193 0000"            /* .¬...ë...í...ì.. */
	$"0194 0000 0195 0000 0196 0000 0197 0000"            /* .î...ï...ñ...ó.. */
	$"0198 0000 0000 0000 05D2"                           /* .ò.......“ */
};

data 'Mcmd' (256, "Unicode Size") {
	$"000C 0000 05E5 0000 05E6 0000 05E7 0000"            /* .....Â...Ê...Á.. */
	$"05E8 0000 05EA 0000 05EC 0000 05EE 0000"            /* .Ë...Í...Ï...Ó.. */
	$"05F4 0000 0600 0000 0000 0000 012E 0000"            /* .Ù.............. */
	$"012D"                                               /* .- */
};

data 'Mcmd' (257, "Unicode Style") {
	$"0004 0000 0191 0000 0192 0000 0193 0000"            /* .....ë...í...ì.. */
	$"0194"                                               /* .î */
};

data 'Mcmd' (300, "Icon Actions") {
	$"000A 464C 5056 464C 5048 0000 0000 524F"            /* .¬FLPVFLPH....RO */
	$"5452 524F 544C 0000 0000 5452 414E 0000"            /* TRROTL....TRAN.. */
	$"0000 4445 4C49 5253 5A49"                           /* ..DELIRSZI */
};

data 'Mcmd' (301, "Icon Colors") {
	$"000B 434C 5431 434C 5432 434C 5433 434C"            /* ..CLT1CLT2CLT3CL */
	$"5434 434C 5435 434C 5436 434C 5437 0000"            /* T4CLT5CLT6CLT7.. */
	$"0000 7442 6E57 7453 5750 5257 4354"                 /* ..tBnWtSWPRWCT */
};

data 'Mcmd' (303, "Icon Style") {
	$"0015 0000 0191 0000 0192 0000 0193 0000"            /* .....ë...í...ì.. */
	$"0194 0000 0195 0000 0196 0000 0197 0000"            /* .î...ï...ñ...ó.. */
	$"0198 FFFF FFFF 0000 2395 0000 2396 0000"            /* .òˇˇˇˇ..#ï..#ñ.. */
	$"2398 0000 239A 0000 239E 0000 23A4 0000"            /* #ò..#ö..#û..#§.. */
	$"23B0 0000 238C FFFF FFFF 0000 019C 0000"            /* #∞..#åˇˇˇˇ...ú.. */
	$"019D 0000 019E"                                     /* .ù...û */
};

data 'Mcmd' (133, "Resources Menu") {
	$"000C 0000 04B1 0000 0000 0000 04B2 0000"            /* .....±.......≤.. */
	$"04B3 0000 04B4 0000 0000 0000 04B5 0000"            /* .≥...¥.......µ.. */
	$"0000 0000 04BA 0000 04BB 0000 0000 0000"            /* .....∫...ª...... */
	$"04BF"                                               /* .ø */
};

data 'Mcmd' (160, "Aete Menu") {
	$"0017 0000 0641 0000 0642 0000 0000 0000"            /* .....A...B...... */
	$"0643 0000 0644 0000 0000 0000 0645 0000"            /* .C...D.......E.. */
	$"0646 0000 0000 0000 0647 0000 0648 0000"            /* .F.......G...H.. */
	$"0000 0000 0649 0000 064A 0000 0000 0000"            /* .....I...J...... */
	$"064B 0000 064C 0000 0000 0000 064D 0000"            /* .K...L.......M.. */
	$"064E 0000 0000 0000 0655 0000 0656"                 /* .N.......U...V */
};

data 'Mcmd' (258, "Menu item Style") {
	$"000A 0000 0000 0000 0000 0000 0191 0000"            /* .¬...........ë.. */
	$"0192 0000 0193 0000 0194 0000 0195 0000"            /* .í...ì...î...ï.. */
	$"0196 0000 0197 0000 0198"                           /* .ñ...ó...ò */
};

resource 'PICT' (128, "Rezilla banner") {
	7106,
	{0, 0, 79, 239},
	$"0011 02FF 0C00 FFFE 0000 0048 0000 0048"
	$"0000 0000 0000 004F 00EF 0000 0000 001E"
	$"0001 000A 0000 0000 0300 0400 0098 80F0"
	$"0000 0000 004F 00EF 0000 0000 0000 0000"
	$"0048 0000 0048 0000 0000 0008 0001 0008"
	$"0000 0008 002F F3DC 002F F814 0000 04B7"
	$"0000 002C 0000 FFFF FFFF FFFF 0001 0000"
	$"0000 6666 0002 DDDD DDDD DDDD 0003 8888"
	$"8888 8888 0004 6666 6666 CCCC 0005 1111"
	$"1111 1111 0006 3333 3333 9999 0007 3333"
	$"3333 6666 0008 3333 3333 3333 0009 3333"
	$"6666 9999 000A 2222 2222 2222 000B 4444"
	$"4444 4444 000C EEEE EEEE EEEE 000D 6666"
	$"6666 9999 000E AAAA AAAA AAAA 000F 6666"
	$"3333 9999 0010 9999 9999 9999 0011 6666"
	$"6666 FFFF 0012 0000 3333 3333 0013 6666"
	$"3333 CCCC 0014 7777 7777 7777 0015 CCCC"
	$"CCCC CCCC 0016 3333 6666 CCCC 0017 3333"
	$"0000 6666 0018 0000 0000 2222 0019 6666"
	$"6666 6666 001A BBBB BBBB BBBB 001B 0000"
	$"0000 3333 001C 6666 9999 FFFF 001D 5555"
	$"5555 5555 001E 0000 0000 4444 001F 9999"
	$"9999 FFFF 0020 3333 0000 3333 0021 9999"
	$"6666 FFFF 0022 6666 3333 6666 0023 6666"
	$"9999 CCCC 0024 0000 3333 6666 0025 3333"
	$"6666 6666 0026 3333 3333 CCCC 0027 0000"
	$"0000 1111 0028 0000 1111 0000 0029 9999"
	$"CCCC FFFF 002A 1111 0000 0000 002B 0000"
	$"0000 5555 002C 0000 0000 0000 0000 0000"
	$"004F 00EF 0000 0000 004F 00EF 0000 0481"
	$"0091 0004 8100 9100 0481 0091 0004 8100"
	$"9100 0481 0091 0004 8100 9100 0481 0091"
	$"0004 8100 9100 0481 0091 0004 8100 9100"
	$"0481 0091 0004 8100 9100 0481 0091 0004"
	$"8100 9100 0481 0091 0004 8100 9100 2AF4"
	$"0012 0203 0405 0506 0704 0807 0907 0A08"
	$"070B 0503 0C81 00FB 0004 020D 060A 0EF3"
	$"0004 020F 090A 0ECF 0039 F500 0210 0707"
	$"FE04 0E09 0706 0711 0607 1213 0907 0807"
	$"1210 9300 090E 0A0A 0907 0607 110B 0CF4"
	$"0005 1007 090F 0714 F400 0510 0906 0D07"
	$"14D0 0040 F600 1615 060A 160F 0904 1709"
	$"0407 040B 0607 0918 0704 090F 1619 9700"
	$"0C0C 1905 0F09 0417 0904 0704 0B08 F400"
	$"061A 1B1C 0707 1C1A F500 061A 0704 0D06"
	$"0D1A D100 46F6 0018 1D0D 1E1F 0904 0A0A"
	$"0409 0706 0A07 0704 0D16 0706 0404 1C0B"
	$"0C9A 000E 1A0D 1E1F 0904 0A0A 0409 0706"
	$"0A07 1AF5 0007 020D 1106 0704 180C F600"
	$"0702 0709 0609 0707 0CD2 004A F700 1A15"
	$"0707 0F1C 0A06 0406 0407 070F 0907 0407"
	$"0704 0604 0D06 071B 0D15 9D00 100C 0B07"
	$"070F 1C0A 0604 0604 0707 0F09 0708 F400"
	$"0706 0908 0706 0A0A 0CF6 0007 0704 0720"
	$"0704 0A0C D300 4CF7 001B 0807 0609 0607"
	$"1109 0706 0509 0706 0A09 0604 0907 0604"
	$"0D06 0911 0715 9F00 120C 0404 0706 0906"
	$"0711 0907 0605 0907 060A 0919 F500 070D"
	$"0607 0404 0921 0AF6 00FE 0704 041C 0406"
	$"0AD3 0052 F800 071A 070D 1207 2216 0DFD"
	$"0711 1F11 0907 1308 160F 0404 1C07 0706"
	$"0408 0615 A000 0803 1C07 0D12 0722 160D"
	$"FD07 061F 1109 0713 0815 F700 0915 0606"
	$"0D09 0706 0406 10F8 0009 1506 0406 2313"
	$"0D07 0710 D400 55F8 0015 0B1B 0718 1C06"
	$"2206 0709 0704 060A 2009 1F04 1104 090D"
	$"FE07 050D 0604 0412 15A1 0013 140D 1B07"
	$"181C 0622 0607 0907 0406 0A20 091F 0403"
	$"F700 091A 0F09 0406 0707 090D 1DF8 0009"
	$"1A21 2406 1F09 0707 041D D400 55F8 00FE"
	$"071C 0911 0704 0707 0608 0604 0407 041C"
	$"0707 0806 0406 0707 160D 0908 0606 15A2"
	$"0000 02FE 070F 0911 0704 0707 0608 0604"
	$"0407 041C 0715 F700 0914 060D 060D 0704"
	$"1F06 08F8 0009 1416 0A0D 0607 0704 0608"
	$"D400 55F8 0000 06FE 0715 0D24 0709 0411"
	$"0A0E 0000 0E1F 0706 0806 0406 0707 0921"
	$"FE07 0309 0911 0CA2 0000 19FE 070D 0D24"
	$"0709 0411 0A04 160D 1E1F 0708 F600 090B"
	$"0911 0609 0716 2007 08F8 0003 0B07 0709"
	$"FE07 0211 2508 D400 53F9 000B 0C07 0806"
	$"0D16 0F1C 0D07 0614 FC00 1015 0607 0904"
	$"0907 0704 0607 0609 040F 040A A100 100B"
	$"060D 160F 1C0D 0706 1204 0A04 2511 0A0C"
	$"F600 090A 0F04 2507 060F 0907 08F8 0009"
	$"0A04 0906 0407 090D 1708 D400 52F9 000B"
	$"1A09 0407 040F 1C07 1E0D 0615 FB00 1015"
	$"070F 0709 0406 0D12 110D 0604 0707 0F10"
	$"A200 0F0C 0A04 0F1C 071E 0D06 071F 1C06"
	$"070A 0CF5 0009 0407 070F 120D 0907 0408"
	$"F800 091F 0707 0407 0706 0712 08D4 0050"
	$"F900 0A1A 0406 0604 2506 0706 0408 F900"
	$"0815 0904 0416 0807 060D FE07 0306 0709"
	$"0AA1 000D 0C0A 2506 0706 0408 1104 0920"
	$"0A0C F500 0A15 0706 0709 2004 0604 0608"
	$"F900 0A15 0906 0D07 0607 0716 0408 D400"
	$"4CF9 000A 1A08 0709 0F16 2216 0B06 09F8"
	$"0001 1504 FE07 0904 0906 0712 0704 0706"
	$"09A0 000A 0C0A 2216 0B06 0921 0907 14F3"
	$"000A 1A07 0407 0609 110D 0607 08F9 000A"
	$"1A04 0A06 0409 061F 0F07 08D4 0052 F900"
	$"0A1A 0407 1109 0607 0D06 0D08 F700 0D15"
	$"070A 0406 0707 061F 040D 0609 0FBB 0001"
	$"0C0E FA1A 0110 02EF 0007 1405 060D 0623"
	$"030C F200 0A03 040D 0609 0F04 0906 0D08"
	$"F900 0A03 0706 1C04 070F 0712 0408 D400"
	$"57F9 000A 1A07 071F 1707 0609 0404 08F6"
	$"000C 1506 1C07 1123 0406 0906 0707 05C4"
	$"0017 1A0E 0A19 0A08 041C 2009 1B0A 0416"
	$"0704 0407 090D 1709 0A0E DC00 0A1D 0906"
	$"0707 160D 0F09 041D F900 021D 0706 FE07"
	$"0416 0D06 111D D400 7BF9 000A 0312 0406"
	$"0704 0D04 1607 08F5 000B 1D0F 090D 0607"
	$"0713 0809 0708 EC00 0C02 1D0B 0904 1B0D"
	$"0920 120A 0A0E EB00 1C0E 0A08 0508 0907"
	$"0406 0904 0607 0511 0D1C 1122 0716 060D"
	$"0426 1207 070D DC00 0A07 1308 0907 0406"
	$"0904 0614 F900 0A07 0D06 0D04 0904 1B0D"
	$"0914 F000 0C0C 1908 0607 0713 0809 0708"
	$"0B15 F200 85F9 000A 140F 0407 1609 0F16"
	$"0707 0BF5 000B 1416 0407 0607 1C09 1309"
	$"0703 EE00 110C 190F 0907 060D 2706 0D16"
	$"0F04 0716 0519 0CEF 001D 0B06 071C 0913"
	$"0907 0407 0D06 0807 041C 0704 0824 0707"
	$"0605 0508 0704 0416 DD00 0B10 1C09 1309"
	$"0704 070D 0608 10FA 000B 1004 160F 0907"
	$"060D 2706 0D10 F100 0E1A 1604 0706 071C"
	$"0913 0907 0407 0D08 F300 8CF9 000A 1409"
	$"0907 0D04 0608 0709 14F5 000B 140D 0F09"
	$"0407 0D07 0720 060C EF00 1302 0707 0907"
	$"0706 0904 1F07 0709 0907 0D04 0605 1AF1"
	$"001E 1009 0407 0D07 0720 060D 0907 0706"
	$"2704 0407 0406 2007 070D 111F 070F 1607"
	$"15DE 000C 0C07 0D07 0720 060D 0907 0706"
	$"02FB 000C 0C16 0707 0907 0706 0904 1F07"
	$"02F2 0010 141C 0D0F 0904 070D 0707 2006"
	$"0D09 0707 1DF4 008E F900 0A1A 060F 1607"
	$"0708 060D 0614 F500 0A0A 0609 0F07 1213"
	$"0707 041D EF00 150C 0407 0704 0F07 0D06"
	$"0604 0607 060F 1607 0708 060D 10F3 0011"
	$"1509 0F07 1213 0707 040D 2607 0704 040A"
	$"0406 FD07 081C 1F16 090A 1B16 0403 DD00"
	$"0B14 1213 0707 040D 2607 0704 1DFA 000B"
	$"1404 0707 040F 070D 0606 041D F300 140C"
	$"0B13 0406 090F 0712 1307 0704 0D26 0707"
	$"0404 0A02 F600 9FF9 000A 1A08 0907 070A"
	$"161F 0607 14F6 000B 1D07 120A 0706 0409"
	$"0704 090C F000 080C 0A0D 0709 0F09 0716"
	$"FE07 0B09 2008 0907 070A 161F 0607 1AF5"
	$"001E 1512 0A07 0604 0907 0409 0604 0D07"
	$"0609 2404 0707 1604 0609 0404 0706 121F"
	$"05EF 0005 1507 0604 090E F500 0C02 0604"
	$"0907 0409 0604 0D07 0602 FB00 0802 1F0D"
	$"0709 0F09 0716 FE07 0002 F400 160C 0A06"
	$"0707 120A 0706 0409 0704 0906 040D 0706"
	$"0924 0410 F700 9EF8 0009 1707 090F 1F04"
	$"0607 0D14 F700 011D 06FD 0405 090F 041C"
	$"0A0E EF00 1819 1107 0704 0707 060D 0706"
	$"0D1B 1217 0709 0F1F 0406 070D 060C F700"
	$"010C 0AFE 041A 090F 041C 0A06 0409 1E08"
	$"0406 0F1C 0704 0D07 0904 060A 0706 0F11"
	$"14F0 0006 1007 0D06 0707 08F5 000B 1909"
	$"0F04 1C0A 0604 091E 0814 FA00 0B19 1107"
	$"0704 0707 060D 0706 14F3 0003 1D06 0806"
	$"FD04 0F09 0F04 1C0A 0604 091E 0804 060F"
	$"1C07 02F8 009C F800 0909 110D 1109 0507"
	$"0907 14F8 0001 1D07 FE04 0616 1120 1C07"
	$"0708 EF00 190C 0907 0709 0604 0608 2407"
	$"0D12 0704 0911 0D11 0905 0709 0707 19F7"
	$"0006 0304 0416 1120 1CFC 0713 0A0F 0904"
	$"0909 0707 0D06 1204 0F06 0D06 0809 0702"
	$"F100 0210 0709 FE07 0106 0BF5 0002 0520"
	$"1CFC 0703 0A0F 090C FA00 0B05 0707 0906"
	$"0406 0824 070D 0CF3 0002 1604 07FE 0403"
	$"1611 201C FC07 080A 0F09 0409 0907 0719"
	$"F800 A3F9 0002 1A06 0DFD 0703 0607 0614"
	$"F900 0C1D 0906 0807 090F 251E 0A27 121A"
	$"EF00 0510 0406 0607 09FE 0707 0606 0706"
	$"1F07 060D FD07 0506 0706 2306 10F8 001E"
	$"0A07 090F 251E 0A27 1207 0416 1F04 0609"
	$"0F06 0907 0706 0F09 060D 0609 0704 1DF1"
	$"0008 1A07 0607 0623 0604 03F6 000B 0225"
	$"1E0A 2712 0704 161F 041D FA00 0502 0406"
	$"0607 09FE 0702 0606 1DF2 0017 2109 0608"
	$"0709 0F25 1E0A 2712 0704 161F 0406 090F"
	$"0609 070A F800 A6F9 0006 1A04 1607 0713"
	$"09FE 0400 14FA 0002 1D1C 06FE 0706 1728"
	$"270A 161F 08EE 0004 1904 1208 0DFE 070C"
	$"110F 2504 0707 0302 0000 150B 09FE 0403"
	$"0709 071A F900 1E07 0717 2827 0E1A 0304"
	$"0B04 0D0B 1409 031A 1002 0000 0F09 0D1C"
	$"0404 0707 041A F100 0108 09FE 0403 0709"
	$"0702 F600 0B1A 270A 161F 0406 040D 0607"
	$"0EFA 0004 1A2C 1208 0DFE 0703 110F 250E"
	$"F200 0108 06FE 0712 1728 100E 0C00 1503"
	$"040D 0607 090F 041F 0707 09F8 0091 F900"
	$"0A1A 0407 0904 090F 160D 0414 FB00 0D14"
	$"0407 0512 0707 2526 041F 0416 10EE 000C"
	$"0506 2216 1309 111F 0908 0605 03FB 0009"
	$"0C0F 160D 0407 0404 0602 FA00 0405 0725"
	$"0B02 F200 0915 060D 0607 1B0A 2009 05F1"
	$"0008 1A09 0F16 0D04 0704 05F5 000A 0304"
	$"1F04 1620 0904 0604 04F9 000A 0306 2216"
	$"1309 111F 0908 06F1 0004 020B 1205 10F9"
	$"0001 1A06 FE04 0524 0706 0704 04F8 0080"
	$"F900 061A 0906 060D 071C FE07 0014 FC00"
	$"0110 0FFE 0708 111F 0904 0708 0607 05EE"
	$"000C 1506 0F16 0409 0704 070A 0706 02F9"
	$"0000 1CFE 0704 0913 0908 1DE7 000A 0C0A"
	$"0906 0A07 0906 0906 10F1 0002 1D07 1CFE"
	$"0702 0913 1DF5 000A 1408 0607 0807 0416"
	$"0404 08F9 000A 140F 1604 0907 0407 0A07"
	$"08E3 0001 0404 FE07 0404 0904 0407 F800"
	$"81F9 000A 0E0F 0409 1307 0D07 1604 08FD"
	$"000E 1007 0711 0D16 0706 0607 0806 0409"
	$"0EEE 000B 1D04 250F 090F 160D 0716 0B0C"
	$"F900 091A 0D07 1604 0409 0707 09E8 000A"
	$"0C0A 0407 0706 070D 090F 0AF0 0008 1307"
	$"0D07 1604 0409 14F5 000A 1D06 0409 0607"
	$"0407 0906 0BF9 000A 1D25 0F09 0F16 0D07"
	$"160D 0BE3 0009 0906 0904 0604 0F16 0608"
	$"F800 82F9 000A 1409 160F 2506 0D16 2106"
	$"08FE 000E 1012 060D 1C06 080D 0608 0706"
	$"0907 1AEE 000A 1507 0406 1606 0404 0706"
	$"0BF7 0009 0B0D 1621 060F 0706 0621 E900"
	$"0B0C 0A04 0707 0404 0704 060A 0CF1 0009"
	$"1A25 060D 1621 060F 071A F500 0A08 0907"
	$"0607 071C 040F 0714 F900 0A08 0616 0604"
	$"0407 0607 2614 E300 090F 0704 0A06 2506"
	$"0D04 08F8 0084 F900 1B14 0404 0707 0426"
	$"0D09 0709 1515 0B24 0804 0907 0506 090F"
	$"0623 070A 0CEE 000B 0C0A 0416 2207 090D"
	$"0707 090C F800 0A1A 0426 0D09 0709 060D"
	$"0D0B EA00 0B15 0906 0907 0906 090F 0707"
	$"0CF0 0009 1407 0426 0D09 0709 0615 F500"
	$"0A08 0F16 070A 1104 0625 0610 F900 0A08"
	$"2207 090D 0707 0904 0410 E400 0A1A 2506"
	$"071B 0706 0906 0908 F800 91F9 000B 1407"
	$"0D1E 071C 0716 0D07 070D FE07 0B16 070D"
	$"0604 1104 0709 070B 0CED 000B 1907 160D"
	$"0707 0407 0606 0A10 F900 0B0C 071C 0716"
	$"0D07 070D 0707 15EB 000B 1504 0707 060D"
	$"060D 1309 0915 EF00 0814 071C 0716 0D07"
	$"070D F400 0A0A 090D 070F 0907 0A07 0702"
	$"F900 0A0A 0707 0407 0606 0A06 0D02 F200"
	$"0A02 0B0A 0407 0907 1B09 0D1A FE00 0A08"
	$"0707 090F 1C04 0707 0608 F800 93F9 0007"
	$"0B06 0920 0921 090F FE07 0E24 0A04 070F"
	$"061C 0406 2507 070F 090C ED00 0F0E 0607"
	$"0F12 0709 0F24 1D04 1123 0609 0EFE 0006"
	$"1503 0509 2109 0FFE 0702 240A 03EB 0000"
	$"15FE 0707 060D 060D 1604 0D15 EE00 0414"
	$"0921 090F FE07 0024 F400 0907 0607 0712"
	$"0F04 1604 11F8 0009 1207 090F 241D 0411"
	$"2306 F200 1210 0406 2507 070F 0907 0607"
	$"0705 1003 1604 1104 FD07 0206 0D19 F800"
	$"93F9 0018 081C 0F25 0604 070A 2407 0611"
	$"0409 0716 0D06 0707 0D06 0707 06ED 000F"
	$"0C06 0907 0706 060F 160D 131C 0707 0D11"
	$"FD07 0B1C 0F25 0604 070A 2407 0611 19EB"
	$"000B 1507 0409 040D 061C 0607 0D15 ED00"
	$"0814 0604 070A 2407 0611 F400 0107 0DFE"
	$"0404 1109 0607 08F8 0009 0606 0F16 0D13"
	$"1C07 070D F300 0A19 0607 070D 0607 0706"
	$"070D FE04 0C11 0906 0708 0707 0409 040D"
	$"0614 F800 95F9 0019 0811 0707 0424 2009"
	$"1F04 0407 070F 0709 040D 0706 0709 0704"
	$"0D15 EE00 0E14 0D06 090D 0709 1C07 0607"
	$"050D 0606 FE07 0C04 0711 0707 0424 2009"
	$"1F04 040E EB00 0B15 0904 0420 0607 0406"
	$"1D07 10EC 0008 1404 2420 091F 0404 07F4"
	$"0004 0604 1C07 06FE 0701 0904 F800 0907"
	$"091C 0706 0706 0D06 06F4 000E 1004 0D07"
	$"0607 0907 040D 0604 1C07 06FE 0709 0904"
	$"0904 0420 0607 041A F800 91F9 0007 0804"
	$"0706 0407 0D11 FE07 0E19 1506 070D 1124"
	$"1325 0604 071C 1E19 EE00 0605 0707 0F07"
	$"060D FE07 1209 1502 1007 0A08 0509 0704"
	$"0706 0407 0D11 0510 EA00 0B15 0407 1107"
	$"0708 0904 2506 10EB 0004 1404 070D 11FD"
	$"07F4 0009 0D06 0612 0411 0D09 0F04 F800"
	$"0106 0DFE 0704 090B 1107 07F5 001B 020D"
	$"1124 1325 0604 071C 1E0A 0B15 0000 0B0D"
	$"090F 0407 1107 0708 0904 F700 7DF9 0014"
	$"0407 160B 0706 1622 0609 090C 000C 1613"
	$"0D0D 0907 06FD 0700 05EE 00FE 0707 0407"
	$"0607 0406 0A11 D900 0B15 0409 0704 1206"
	$"070F 0607 10EA 0008 1D07 0616 2206 0909"
	$"06F4 0009 1F04 0704 090F 0704 0409 F800"
	$"0506 0704 060A 11FE 0700 16F5 000A 1913"
	$"0D0D 0907 0607 070B 02FC 000B 0A07 0404"
	$"0907 0412 0607 0F0E F700 81F9 000A 0607"
	$"0806 0904 0F09 0911 08FE 000C 1A09 0706"
	$"0806 0404 0707 0406 10EF 000A 0706 0709"
	$"060B 0629 0F09 06DA 000B 1509 0607 0609"
	$"0F1C 0609 0414 E900 0808 0904 0F09 0911"
	$"0F0D F400 0A06 0507 0722 1604 0906 070C"
	$"F900 0A0B 0629 0F09 0607 0907 070C F700"
	$"090C 0F09 0706 0806 0404 08FB 000B 1516"
	$"0409 0607 0609 0F1C 0608 F600 81F9 000A"
	$"0906 0604 0407 090F 0904 1DFD 000C 1407"
	$"0706 0D09 2007 0904 041C 0CF0 000A 0425"
	$"0406 0707 1F04 1220 09DB 000B 1504 0706"
	$"0D06 0407 0609 0F08 E800 0808 0407 090F"
	$"0904 0706 F400 0A05 1C07 0706 0704 0706"
	$"0D1A F900 0A05 1F04 1220 0907 0409 071A"
	$"F700 0914 090F 0707 060D 0920 0EFB 000B"
	$"1007 0407 060D 0604 0706 0910 F600 82F9"
	$"000A 040D 110D 0707 0D06 0D06 14FC 000B"
	$"0B12 0406 0625 1104 0409 071D F000 0B07"
	$"0A06 0707 0616 071B 0406 15DD 000C 0C0A"
	$"0607 0D12 0D06 0704 0604 0CE8 0008 0507"
	$"070D 060D 0612 21F4 000A 0807 0A06 090D"
	$"0607 0D12 03F9 000A 0816 071B 0406 0D07"
	$"070F 03F7 0009 0A13 2506 1204 0606 2502"
	$"FB00 0B1A 0D06 070D 120D 0607 0406 0CF6"
	$"0081 F900 0A06 120D 0606 0904 0607 0D14"
	$"FC00 0C0C 0A09 070F 0604 0913 0707 061A"
	$"F100 0B06 1B0D 090D 0707 090F 090A 1ADE"
	$"000C 1511 0407 0607 2011 0B09 0F07 02E7"
	$"0008 0606 0904 0607 0D06 23F4 000A 1907"
	$"060D 1104 0706 0720 0BF9 0006 1907 090F"
	$"090A 06FE 0400 0BF7 0008 0608 060D 0409"
	$"070F 06FA 000A 1A04 0706 0720 110B 090F"
	$"0BF5 0083 F900 0A0F 1604 040D 0407 0607"
	$"2614 FB00 0B15 2511 0609 072A 090F 0706"
	$"08F1 000B 0804 1109 0F04 091C 0706 0403"
	$"DF00 0C10 1C04 070D 0604 0D09 0707 0A0C"
	$"F700 FD1A F400 0804 0D04 0706 0726 0D06"
	$"F400 0A0E 0706 1C04 070D 0604 0D05 F900"
	$"0A0E 091C 0706 0418 0704 0605 F700 0807"
	$"0D06 0409 2511 0609 F900 0507 0D06 040D"
	$"09FE 0700 14F5 0095 F900 0A08 0709 0406"
	$"0407 0D1E 0D03 FA00 0B10 0A2A 0A26 0D04"
	$"0609 040F 1AF2 000B 0311 0D0A 1108 0706"
	$"0A06 071D E000 1D10 040F 0907 0409 0F06"
	$"070A 0503 0A0A 0404 090D 0408 080A 1108"
	$"0706 0A0A 0CF6 0009 0406 0407 0D1E 0D07"
	$"071A F500 0B02 0904 0F09 0704 090F 0607"
	$"15FA 000B 0207 060A 0607 0806 0707 0415"
	$"F800 090A 0704 0407 060A 2A0A 0CFB 000A"
	$"0C07 0409 0F06 070A 0406 1AF5 0097 F900"
	$"0A08 0F04 0907 0706 240D 071A F900 0A1D"
	$"0911 1F09 2404 0F06 1608 F200 0C15 0D06"
	$"0709 0707 0607 0907 0602 E200 1E10 0F06"
	$"160D 0704 0604 0908 0504 071C 0411 0F07"
	$"0906 0D06 0709 0707 0607 090A F600 0909"
	$"0707 0624 0D07 0706 1AF4 000A 0506 160D"
	$"0704 0604 0908 19F9 000A 0506 0709 0706"
	$"0904 1F07 19F8 001A 1404 0907 070D 0709"
	$"111F 0924 040F 0B14 0507 0406 0409 0806"
	$"0407 0CF5 0097 F900 0A08 0604 2009 061D"
	$"0704 241A F900 0B0C 041F 0607 0709 0704"
	$"0607 1AF2 000C 1D07 1B0D 0604 0407 0F1C"
	$"070A 0CE4 000B 1009 0704 0607 061C 0F06"
	$"0724 FD04 1007 0709 0413 090A 071B 0D06"
	$"0404 070F 1C14 F700 0920 0906 1D07 0424"
	$"0D06 1AF4 000A 1904 0607 061C 0F06 0724"
	$"05F9 000A 1904 070F 1C07 0404 0712 05F8"
	$"0016 0206 0707 0607 0404 1F06 0707 0907"
	$"0406 0706 1C0F 0607 24FE 04F4 009B F900"
	$"0308 0709 06FE 0403 0709 070C F800 0A10"
	$"0712 070F 0404 090D 0408 F100 0C1D 0913"
	$"0904 2506 0907 0A11 051A E700 220C 0B0F"
	$"0404 090D 0409 0D07 0907 071F 0706 0607"
	$"0407 0724 2226 0709 1309 0425 0609 071D"
	$"F700 0008 FE04 0507 0907 0607 1AF4 000B"
	$"0209 0D04 090D 0709 0707 1F10 FA00 0B02"
	$"2506 0907 0A11 0424 0D04 10F8 0002 140D"
	$"16FE 0412 0607 1207 0F04 0409 0D04 090D"
	$"0709 0707 1F07 08F4 009A F900 0908 0904"
	$"0706 0707 0606 07F6 000A 0804 111C 0707"
	$"060D 2B0F 10F1 000D 1D04 060A 0707 040D"
	$"1604 0720 0510 EA00 230C 0A11 1C07 0706"
	$"0D2B 0F09 040A 0604 1607 0D0A 0716 060D"
	$"0D09 0707 0404 060A 0707 040A 0CF7 0009"
	$"0806 0707 0606 0704 091A F300 0A0A 0D2B"
	$"0F09 040A 0604 1605 F900 0A0A 0704 0D16"
	$"0407 2009 0605 F800 180C 0A25 0609 0F09"
	$"2004 111C 0707 060D 2B0F 0904 0A06 0416"
	$"0719 F400 9BF9 0009 080F 090F 0907 060D"
	$"0D04 F600 0A15 0904 0A07 0406 0707 0405"
	$"F000 0710 061C 1704 1C01 0DFE 0704 040F"
	$"0919 0CED 0021 0B09 040A 0704 0607 0704"
	$"0607 0607 0907 0811 061C 0F0D 0707 0604"
	$"0704 0806 1C17 0414 F500 0914 0907 060D"
	$"0D04 0920 1AF3 000B 0307 0704 0607 0607"
	$"0907 0814 FA00 0403 041C 010D FE07 0304"
	$"0F09 14F8 0017 1511 0404 2407 0409 040A"
	$"0704 0607 0704 0607 0607 0907 080E F400"
	$"9BF9 0009 0804 0609 0F09 0607 0708 F500"
	$"0A19 0906 0907 0D24 071C 0710 F000 1010"
	$"0708 110F 0B06 0716 0704 2511 0D07 040E"
	$"EF00 2009 0F09 0609 070D 2407 1C07 090D"
	$"0604 0604 0609 0F16 0607 0709 0706 0406"
	$"0407 190C F400 090E 0F09 0607 0706 0D24"
	$"0CF3 000C 0C24 071C 0709 0D06 0406 0406"
	$"15FB 000C 0C11 0F0B 0607 1607 0425 110D"
	$"15F8 0015 0C19 0707 0409 0F09 0609 070D"
	$"2407 1C07 090D 0604 0604 F300 95F9 0002"
	$"0816 0AFE 07FE 0400 10F5 000A 0C06 0406"
	$"0704 170D 0706 0BEF 0002 1009 1CFE 070D"
	$"160D 0711 040D 160A 160A 070A 0B15 F300"
	$"1D08 0906 0406 0704 170D 0706 0F04 040F"
	$"0809 070D 1607 060D 1104 070B 1408 1AF1"
	$"0002 1A07 07FE 0402 0907 0DF1 000B 030D"
	$"0706 0F04 040F 0809 070B FA00 0003 FE07"
	$"0716 0D07 1104 0D16 0BF6 0013 1A04 090F"
	$"0906 0406 0704 170D 0706 0F04 040F 0814"
	$"F300 8CF9 0004 080F 041C 09FE 0400 1DF3"
	$"0009 0E06 1D16 0608 0906 2506 EE00 101D"
	$"0612 0711 041E 2306 0707 2012 0F04 1C09"
	$"FE04 0216 040A F600 1714 0D06 1D16 0608"
	$"0906 2506 0707 2420 0409 0605 0A04 030E"
	$"0CEB 0000 09FE 0403 1604 0710 F000 0A05"
	$"0625 0607 0724 2004 090A F900 0A05 0711"
	$"041E 2306 0707 200A F500 110C 0E08 1D05"
	$"0A1D 1606 0809 0625 0805 1D0B 15F2 006A"
	$"F900 0719 0904 0413 0904 03F1 0008 0B26"
	$"0409 0704 2206 07ED 0015 1D0A 2125 061D"
	$"0607 0706 0913 0904 0413 0904 0407 0724"
	$"F500 080C 0305 0403 0304 0A06 FE07 030A"
	$"0410 1AE4 0006 1509 0404 0707 1AEF 0002"
	$"1422 06FD 0703 041C 0407 F900 0A14 2125"
	$"061D 0607 0706 0913 D400 4AF9 0006 1411"
	$"0416 0407 10F0 0008 0C0A 0607 0706 0707"
	$"09EC 000E 1409 170D 0609 0406 0D07 0911"
	$"0416 04FC 0700 0BAF 000A 0C07 0709 0D11"
	$"0704 0407 09F9 000A 0C09 170D 0609 0406"
	$"0D07 09D4 0043 F900 0015 FD07 0014 EE00"
	$"070C 0B0B 061C 0409 0DEB 0002 1A09 04FD"
	$"0702 1607 1FFD 0705 2004 0904 0B0C AE00"
	$"0903 090D 0607 0711 160D 05F8 0002 0309"
	$"04FD 0702 1607 05D4 003D F800 0419 0604"
	$"0A0C EC00 0514 0D06 090F 06E8 000E 1503"
	$"1A1A 080B 0608 0604 0904 0608 1AAB 0008"
	$"0B06 1C07 0904 0F09 03F7 0008 0B06 0D04"
	$"040D 0709 03D4 0026 DD00 041A 2306 060A"
	$"DE00 020C 1502 A900 070C 0A07 120F 0409"
	$"1DF6 0007 0C0A 1107 0616 081D D300 1481"
	$"00D8 0004 1406 0407 10F3 0004 1409 040F"
	$"10D2 0004 8100 9100 0481 0091 0004 8100"
	$"9100 0481 0091 0004 8100 9100 0481 0091"
	$"0004 8100 9100 00FF"
};

resource 'PICT' (129, "Cage") {
	9404,
	{0, 0, 348, 127},
	$"0011 02FF 0C00 FFFE 0000 0048 0000 0048"
	$"0000 0000 0000 015C 007F 0000 0000 001E"
	$"0001 000A 0000 0000 0300 0400 0098 8040"
	$"0000 0000 015C 007F 0000 0000 0000 0000"
	$"0048 0000 0048 0000 0000 0004 0001 0004"
	$"0000 0004 017B C7D0 017B C1C0 0000 0450"
	$"0000 0006 0000 FFFF FFFF FFFF 0001 7C7C"
	$"7C7C 7C7C 0002 0909 0909 0909 0003 AAAA"
	$"AAAA AAAA 0004 D6D6 D6D6 D6D6 0005 4747"
	$"4747 4747 0006 0000 0000 0000 0000 0000"
	$"015C 007F 0000 0000 015C 007F 0000 06E3"
	$"0000 23E0 0006 E300 0024 E000 06E3 0000"
	$"24E0 0006 E300 0024 E000 06E3 0000 24E0"
	$"0006 E300 0024 E000 06E3 0000 24E0 0006"
	$"E300 0024 E000 06E3 0000 24E0 0006 E300"
	$"0024 E000 06E3 0000 24E0 0006 E300 0053"
	$"E000 07E4 0001 0424 E000 06E3 0000 24E0"
	$"0006 E300 0024 E000 06E3 0000 24E0 0006"
	$"E300 0024 E000 06E3 0000 24E0 0006 E300"
	$"0024 E000 06E3 0000 24E0 0006 E300 0024"
	$"E000 06E3 0000 24E0 0006 E300 0024 E000"
	$"06E3 0000 24E0 0006 E300 0024 E000 06E3"
	$"0000 24E0 0006 E300 0024 E000 06E3 0000"
	$"24E0 0006 E300 0024 E000 06E3 0000 24E0"
	$"0006 E300 0024 E000 06E3 0000 24E0 0006"
	$"E300 0024 E000 06E3 0000 54E0 0006 E300"
	$"0024 E000 06E3 0000 24E0 0006 E300 0024"
	$"E000 06E3 0000 23E0 0006 E300 0024 E000"
	$"06E3 0000 24E0 0006 E300 0024 E000 06E3"
	$"0000 24E0 0006 E300 0024 E000 06E3 0000"
	$"24E0 0006 E300 0024 E000 06E3 0000 24E0"
	$"0006 E300 0024 E000 06E3 0000 24E0 0006"
	$"E300 0053 E000 07E4 0001 0424 E000 06E3"
	$"0000 24E0 0006 E300 0024 E000 06E3 0000"
	$"24E0 0006 E300 0024 E000 06E3 0000 24E0"
	$"0006 E300 0024 E000 06E3 0000 24E0 0006"
	$"E300 0024 E000 06E3 0000 24E0 0006 E300"
	$"0024 E000 06E3 0000 24E0 0006 E300 0024"
	$"E000 06E3 0000 24E0 0006 E300 0024 E000"
	$"06E3 0000 24E0 0006 E300 0024 E000 06E3"
	$"0000 24E0 0006 E300 0024 E000 06E3 0000"
	$"24E0 0006 E300 0024 E000 06E3 0000 54E0"
	$"0008 E400 0232 2250 E100 09E5 0003 0425"
	$"2550 E100 09E5 0003 0520 3524 E100 09E5"
	$"0003 0530 0425 E100 09E5 0003 5240 0055"
	$"E100 09E5 0003 1240 0022 E100 09E5 0003"
	$"3500 0012 E100 0AE5 0004 5500 0042 40E2"
	$"000A E500 0425 0000 3240 E200 0AE5 0004"
	$"5500 0032 40E2 000A E500 0452 0000 3240"
	$"E200 0AE5 0004 1240 0012 40E2 0009 E500"
	$"0302 1000 22E1 0009 E500 0301 2400 21E1"
	$"0008 E400 0215 0520 E100 08E4 0002 2222"
	$"10E1 0008 E400 0222 5210 E100 08E4 0002"
	$"5252 10E1 0009 E500 0305 5352 20E1 0009"
	$"E500 0302 2053 25E1 000A E500 0452 0054"
	$"3240 E200 0AE5 0004 5500 2402 20E2 000B"
	$"E600 0505 5400 2403 25E2 000B E600 0502"
	$"5000 2400 52E2 000C E600 0651 0000 2400"
	$"0250 E300 0DE7 0007 0425 0000 2400 0524"
	$"E300 0DE7 0007 0220 0000 2400 0012 E300"
	$"0EE7 0008 4210 0000 2400 0012 30E4 000E"
	$"E700 0025 FE00 0424 0000 0120 E400 0FE8"
	$"0001 0323 FE00 0424 0000 0323 E400 10E8"
	$"0001 0520 FE00 0024 FE00 0115 30E5 0010"
	$"E800 0111 40FE 0000 23FE 0001 0250 E500"
	$"0FE8 0000 22FD 0000 24FE 0001 0521 E500"
	$"0FE9 0001 0153 FD00 0024 FD00 0022 E500"
	$"10E9 0001 0210 FD00 0024 FD00 0132 50E6"
	$"000F E900 0052 FC00 0024 FD00 0103 24E6"
	$"000E E900 0025 FC00 0024 FC00 0022 E600"
	$"10EA 0001 0154 FC00 0024 FC00 0132 30E7"
	$"0010 EA00 0132 30FC 0000 24FC 0001 0220"
	$"E700 10EA 0001 5540 FC00 0024 FC00 0101"
	$"23E7 0010 EB00 0104 23FB 0000 24FB 0001"
	$"1240 E800 10EB 0001 0250 FB00 0024 FB00"
	$"0142 50E8 0010 EB00 0132 40FB 0000 53FB"
	$"0001 0124 E800 0FEB 0000 25FB 0001 0424"
	$"FA00 0022 E800 10EC 0001 0124 FA00 0024"
	$"FA00 0132 30E9 0010 EC00 0102 20FA 0000"
	$"24FA 0001 0220 E900 0FEC 0000 52F9 0000"
	$"24FA 0001 0425 E900 0FEC 0000 25F9 0000"
	$"24F9 0001 3240 EA00 10ED 0001 0520 F900"
	$"0024 F900 0102 20EA 0010 ED00 0112 30F9"
	$"0000 24F9 0001 0155 EA00 0EED 0000 25F8"
	$"0000 24F8 0000 22EA 0010 EE00 0104 23F8"
	$"0000 24F8 0001 4210 EB00 10EE 0001 0220"
	$"F800 0024 F800 0101 24EB 000F EE00 0112"
	$"30F8 0000 24F7 0000 22EB 000F EE00 0052"
	$"F700 0024 F700 0155 10EC 0010 EF00 0101"
	$"20F7 0000 24F7 0001 0520 EC00 10EF 0001"
	$"0250 F700 0024 F700 0104 25EC 0010 EF00"
	$"0115 40F7 0000 24F6 0001 5240 ED00 10F0"
	$"0001 0455 F600 0024 F600 0102 20ED 0010"
	$"F000 0105 20F6 0000 24F6 0001 0523 ED00"
	$"0FF0 0001 0250 F600 0024 F500 0022 ED00"
	$"0FF0 0000 22F5 0000 24F5 0001 4210 EE00"
	$"10F1 0001 0423 F500 0024 F500 0102 20EE"
	$"000F F100 0101 20F5 0000 24F4 0000 52EE"
	$"0010 F100 0142 10F5 0000 54F4 0001 5230"
	$"EF00 1BF1 0000 22FB 000C 0444 4355 1115"
	$"1521 1553 3343 40F9 0001 0210 EF00 21F2"
	$"0001 3222 FD00 0543 3314 4400 44FE 0001"
	$"2403 FE33 0355 1554 44FC 0001 0352 EF00"
	$"25F3 0007 3545 2340 0043 3340 FE00 0F44"
	$"4313 3133 2114 4143 1431 4331 5225 10FD"
	$"0001 2530 F000 27F3 0021 3305 5054 1400"
	$"0004 5552 2222 2121 3213 2123 1235 5322"
	$"5255 1111 2225 5400 0111 2150 F100 27F3"
	$"0021 0504 3330 0003 1324 3005 0300 3010"
	$"0300 2430 0104 0044 0503 1031 1144 3525"
	$"1105 2110 F100 26F3 0020 0413 0043 5251"
	$"1024 1335 4533 1453 4343 2314 4543 3433"
	$"4243 1031 4255 4404 5515 01F0 0028 F400"
	$"2204 3100 3141 0130 3054 1335 0533 1453"
	$"4134 2354 4541 3411 4543 1413 0501 5351"
	$"4004 2540 F100 2BF5 0025 0433 0351 1101"
	$"0134 3050 3005 0104 1054 0304 2410 0104"
	$"4033 0103 1033 0503 4431 1154 0012 4310"
	$"F300 2AF5 0024 1104 5454 4145 4113 1424"
	$"1345 0533 1453 4344 2354 4541 3411 4531"
	$"5451 4231 3111 3423 5100 22F2 002C F600"
	$"2601 0014 3030 4301 0330 3054 3445 0544"
	$"3054 0000 2410 0104 4033 0304 3044 0504"
	$"4444 4010 1012 2024 F300 2DF6 0027 1405"
	$"2522 5315 4541 1314 2413 3205 3314 2343"
	$"3353 5435 3153 5532 3153 5532 3551 5511"
	$"5353 2553 0250 F400 2EF7 0007 0503 3025"
	$"5100 0403 FE00 1D10 4001 0300 4010 0000"
	$"2030 0300 0044 0404 4044 0100 4044 4010"
	$"5220 0150 20F4 002E F700 2810 1243 2311"
	$"3431 4541 3310 5313 3245 3110 5344 3421"
	$"5435 4114 1535 3154 5145 3113 1114 5025"
	$"2311 1122 F400 2FF7 0029 1334 4424 2250"
	$"4145 0134 1054 1345 0543 1054 4330 5350"
	$"4103 3011 0143 5011 0543 1333 3050 1524"
	$"1134 3210 F500 2FF7 0029 4200 0424 5320"
	$"0401 0440 3010 3001 0100 3050 0340 5410"
	$"0104 4043 0304 1033 0503 3444 4013 3550"
	$"4340 0120 F500 30F8 002A 0422 1555 2050"
	$"5512 1215 5123 2313 3235 3113 2341 3423"
	$"2335 4314 1145 3123 5532 3551 1114 2535"
	$"1355 1515 21F5 0030 F800 2A05 2100 0035"
	$"5205 3003 0000 4030 3001 0100 3010 0400"
	$"2030 0300 0044 0000 4000 0100 3040 4024"
	$"5130 4300 0124 F500 30F8 002A 0152 1311"
	$"1205 3325 3533 1354 5311 3205 3150 2345"
	$"1321 5315 3153 5535 3153 5142 3151 1225"
	$"4512 5351 1351 20F5 0019 F700 0610 5533"
	$"1020 3210 E822 0952 5303 5012 3411 3351"
	$"30F5 002E F700 0751 0333 4055 0411 53FE"
	$"0005 0100 3044 4040 FE00 0524 0400 0100"
	$"03FE 000B 4000 0312 5125 0220 4043 3302"
	$"F400 2EF7 0007 3350 0123 5323 4333 FE55"
	$"1D51 5112 1552 5532 3522 2555 2521 5125"
	$"5255 3225 3235 0441 2222 5521 2520 21F4"
	$"002E F700 2805 4410 4450 3015 3335 1121"
	$"3313 3241 4533 1252 5221 2525 2151 2152"
	$"5515 5212 1115 3140 1010 4053 0124 F400"
	$"2EF7 0028 0534 1400 3354 4342 4513 5423"
	$"5132 4513 5453 5445 2354 3541 2455 4541"
	$"2451 3231 5111 1454 5455 3452 43F4 002E"
	$"F700 2801 5201 5400 1513 0501 3030 5014"
	$"4501 4410 5431 1225 5041 0350 1105 0310"
	$"1305 4334 3130 2122 4335 2054 F400 2EF7"
	$"0028 0530 5302 5400 1301 0340 4030 3005"
	$"0100 3010 4203 2310 0300 1033 0304 1014"
	$"0100 3444 1453 0041 5310 40F4 002E F700"
	$"2801 0053 3412 5400 4552 2551 2155 1215"
	$"5551 2125 0224 5112 1123 5532 1523 2512"
	$"2225 5400 0052 4021 0220 F400 2EF7 0028"
	$"0421 0120 0201 5300 0034 1320 1405 0100"
	$"3010 3103 1054 4201 2455 0304 5052 3214"
	$"0004 4452 3012 0350 50F4 002E F700 2804"
	$"5114 0530 5505 5033 0000 4331 1552 2225"
	$"2522 3443 2152 5215 5513 3550 0000 0415"
	$"5550 4540 5504 5350 F400 2AF7 000B 0404"
	$"2002 3444 5445 1455 0440 FC00 0410 5100"
	$"0450 FC00 0D04 3043 1423 0550 0210 1200"
	$"2105 10F4 002D F600 2723 0210 1200 2005"
	$"3035 4512 5353 4314 3430 5243 3124 1141"
	$"1315 3124 0210 1101 4314 4114 3543 3342"
	$"40F4 002C F600 2654 0113 4021 0120 0200"
	$"2002 3055 0551 1351 0240 2445 5532 1353"
	$"3443 4110 1204 2002 2002 0025 0021 F300"
	$"2DF6 0027 0420 4200 2143 1441 3105 5012"
	$"0420 0240 2343 3333 0230 2002 4025 0120"
	$"0200 2105 3434 1011 0311 0540 F400 2DF6"
	$"0027 2402 3025 0320 0210 2101 1433 3331"
	$"5012 0120 1204 2032 0150 1200 5101 1310"
	$"5504 2002 3012 0021 0330 F400 2DF6 0027"
	$"2005 4011 4443 1035 0420 4200 2505 1051"
	$"5402 4053 4113 3150 1504 2102 2032 0021"
	$"0520 3540 5504 5240 F400 2DF7 0027 0415"
	$"5012 0024 0520 3133 4110 1503 2042 0424"
	$"4530 5502 3023 0240 2204 2005 3410 5105"
	$"2042 0055 0022 F300 2DF6 0027 5433 3051"
	$"0150 0200 2402 3052 0333 1424 0250 3200"
	$"2032 0320 1133 4413 0510 1200 2002 3012"
	$"0025 0140 F400 2DF6 0027 2002 0021 0120"
	$"3411 0120 3200 2002 0054 1413 3313 4553"
	$"1150 4200 2301 2002 3011 4131 1055 0051"
	$"0540 F400 2CF6 0026 5110 5500 2402 4025"
	$"0134 1343 4550 2205 2002 4021 0250 5502"
	$"2055 0333 3302 3025 0120 0240 2200 22F3"
	$"002D F600 2751 3011 0433 3015 0320 0210"
	$"5301 1334 2041 1052 0320 0200 5314 3200"
	$"2401 2032 0424 0554 1411 4445 40F4 002E"
	$"F700 2804 2042 0021 0210 5143 0550 1203"
	$"2042 0354 0210 1131 3133 1323 0210 2501"
	$"1305 1433 5302 5042 0021 0340 F400 2DF6"
	$"0027 1130 5101 2042 0420 0250 5333 4530"
	$"2303 2042 0023 0250 1204 2041 1500 2402"
	$"5052 0320 0250 1103 3240 F400 2DF6 0027"
	$"4530 5501 3434 5301 2042 0020 0543 3105"
	$"1153 5501 2042 4013 1302 3022 0120 0240"
	$"1533 4550 1200 2240 F400 2EF7 0028 0420"
	$"3200 2002 0023 0550 1011 0520 2245 2112"
	$"2522 5255 1210 2204 2033 3541 1435 1025"
	$"0520 0240 2505 40F4 002D F600 2713 4133"
	$"4150 5204 2002 0021 5332 0033 4150 3203"
	$"2402 2042 3125 5302 4024 0250 3200 5141"
	$"3310 1501 40F4 002C F600 0402 3024 0554"
	$"FE41 1E22 2201 2032 3425 1555 5355 0221"
	$"5252 3021 0323 5215 1333 1310 2302 2042"
	$"0052 F300 2EF7 0028 0110 1201 2032 0024"
	$"4253 5111 3250 5203 2002 0021 0120 0250"
	$"1211 2534 3131 2242 5012 0420 0510 1412"
	$"40F4 002E F700 2802 5013 3431 3053 1224"
	$"4205 2043 3033 3141 1055 0423 0510 3333"
	$"3055 5250 2105 5052 2334 5302 5032 0040"
	$"F400 2EF7 0028 0312 0024 0233 2255 1310"
	$"2302 1042 0024 0210 5504 5302 2002 3012"
	$"0020 0211 5220 0233 2203 2002 3011 20F4"
	$"002E F700 2845 4311 0120 1231 2002 4453"
	$"1433 1051 0520 3200 2101 2002 1011 4011"
	$"4135 4025 4224 3103 2533 0250 4220 F400"
	$"2EF7 0028 4200 2403 3331 3405 5022 0250"
	$"0240 2105 1433 3011 0313 0250 4240 2101"
	$"2042 0431 5222 0052 1520 4210 50F4 002E"
	$"F700 2834 1102 2032 4023 0213 3150 0210"
	$"5504 2002 3052 0024 0520 0210 1200 2305"
	$"5310 2402 3022 0021 2102 3420 F400 2EF7"
	$"0028 4331 5552 2012 0120 1203 5005 1411"
	$"3105 5045 4011 4133 3105 1015 4354 0550"
	$"5203 2013 3521 2302 2012 44F4 002E F700"
	$"2832 0121 0530 1313 4240 2302 2032 0024"
	$"0250 4240 2504 2005 2042 0022 0320 0210"
	$"5350 0240 5242 2342 3023 F400 2EF7 0028"
	$"1121 0110 1200 2405 3341 3311 1055 0520"
	$"0230 1200 2301 1343 1011 4411 4145 1025"
	$"0520 1543 4321 0150 51F4 002E F700 2852"
	$"2405 3414 5102 5025 0420 0200 5301 5441"
	$"1011 4025 0320 0210 5200 2101 2002 0053"
	$"1402 0022 0320 0231 F400 2EF7 0028 2503"
	$"2042 0024 3432 0453 0220 5204 2002 5042"
	$"4052 0021 0520 0240 5503 5341 1414 2105"
	$"2015 3353 0253 55F4 002F F800 2905 2431"
	$"3110 2502 5055 4021 0513 1333 4134 1314"
	$"1413 4023 0520 3530 2204 2402 2042 0023"
	$"1042 0023 0123 22F4 002F F800 2942 4020"
	$"0240 2310 3200 5201 2042 0023 0520 0230"
	$"3200 2204 2002 1012 0025 0120 0230 5451"
	$"0220 5203 2005 22F4 002F F800 2942 5105"
	$"5052 0120 1140 1313 3110 5503 2005 5031"
	$"3053 1431 3441 3313 4425 0154 0250 1204"
	$"2301 3504 2405 22F4 0030 F800 2A01 2341"
	$"1414 2002 4052 0024 0230 5503 2005 5002"
	$"3032 0023 0520 0200 5200 2005 2042 3054"
	$"2302 0025 0120 0250 F500 30F8 002A 0354"
	$"2002 0124 3410 3311 0520 1200 2105 2002"
	$"1015 1055 0420 0210 1314 1331 4133 0250"
	$"3201 2032 0343 5435 30F5 002E F700 2852"
	$"0530 2102 1032 0024 0513 3334 1141 5405"
	$"5042 4055 0324 0250 3200 2203 2002 2002"
	$"1021 4332 0023 0215 F400 2EF7 0028 5012"
	$"3343 5031 4055 0120 0230 2504 2402 5002"
	$"1052 0023 0120 0250 1504 5141 4313 0210"
	$"5105 2052 4355 05F4 002E F700 2820 3155"
	$"0520 0240 5101 4310 3503 1305 3314 0230"
	$"1503 5105 3402 1052 0023 0120 0220 1200"
	$"2341 4504 2051 F400 2EF7 0028 4204 5120"
	$"0250 1204 2002 1032 4025 0320 0250 4200"
	$"2504 2005 2032 0025 0351 4131 3133 3421"
	$"0550 2203 23F4 002E F700 2830 5104 2303"
	$"1033 3105 5035 4052 0353 0131 1314 3141"
	$"3141 4134 3330 5500 2105 2002 3052 0023"
	$"5210 3254 F400 2DF7 0027 4500 2404 2132"
	$"0024 0550 3200 1540 2103 2002 3052 0023"
	$"0120 0210 1200 2503 5102 5031 3311 2540"
	$"0125 F300 2EF7 0028 3233 4520 0411 1531"
	$"2002 1032 0025 0353 0510 3540 5503 1105"
	$"1033 3314 1504 2305 1012 1130 0045 1243"
	$"50F4 002E F700 2834 5104 2354 0000 4523"
	$"1200 5140 1140 2305 5032 0021 0420 0520"
	$"0240 2200 2505 2025 4000 0055 1505 1050"
	$"F400 2EF7 0028 3503 5405 5052 4000 0314"
	$"0154 2200 2501 2002 3012 0021 0120 0510"
	$"3133 5422 1134 0000 1553 2504 2002 50F4"
	$"002E F700 0831 0024 0150 1322 1040 FE00"
	$"1044 1552 3153 1254 5533 2101 2442 5012"
	$"1553 FE00 0811 1220 3504 2101 1150 F400"
	$"2DF7 000A 3531 0520 0200 5105 2532 30FD"
	$"000B 4005 5435 5122 5552 1551 4340 FE00"
	$"0A03 2151 3130 3500 2105 2010 F400 27F7"
	$"0010 0120 0513 1015 0023 0150 3251 3313"
	$"4401 40F7 000D 4315 5205 2005 2002 3022"
	$"0420 0210 F400 2EF7 0028 4501 2002 3012"
	$"0424 0120 0230 1233 2242 5551 1315 3433"
	$"4313 4351 1250 2204 5101 1141 1433 1303"
	$"1405 50F4 002E F700 2831 0143 5052 0025"
	$"0320 0520 1510 5103 2405 2042 5052 4155"
	$"3535 5002 1011 4021 0120 0250 3200 2505"
	$"2040 F400 2DF7 0027 4250 0230 1544 3104"
	$"3305 5002 4055 0324 0513 4230 5500 2403"
	$"2005 2042 0025 0423 0550 4210 1204 5442"
	$"F300 2DF7 0027 3541 5015 0025 0023 0120"
	$"0510 5200 2105 2002 2032 0015 0331 4101"
	$"1454 3411 0424 0550 4230 1204 2002 F300"
	$"2EF7 0028 3002 3011 0435 4345 4133 0550"
	$"1144 5101 1045 1335 3052 0024 0120 0240"
	$"1200 2503 2002 5032 0022 0513 40F4 002E"
	$"F700 2831 3012 0025 0021 0424 0120 4200"
	$"2504 2002 2002 1012 0055 0335 4110 1334"
	$"1431 4114 0510 3544 1353 4540 F400 2DF7"
	$"0027 4210 5144 1343 4133 0541 4110 1134"
	$"3141 3133 5413 3130 5500 2002 5042 0012"
	$"0021 0120 0240 5203 2002 F300 2EF7 0028"
	$"1432 0025 0021 0023 0420 0230 1200 2301"
	$"2002 1002 3052 0025 0550 4210 1130 3543"
	$"1333 3133 1453 0551 40F4 002E F700 2833"
	$"3504 1343 4141 0533 0550 3230 5501 5101"
	$"5434 5433 3130 2105 2002 1012 0025 0420"
	$"0250 1204 2305 1540 F400 2EF8 0028 0342"
	$"0022 0021 0024 0023 0520 4230 2104 2405"
	$"5002 3002 3052 0420 0220 0230 5500 2301"
	$"5002 3021 0120 02F3 002D F700 2745 3433"
	$"3144 3101 4505 2002 5012 0422 0552 1553"
	$"2154 2155 3343 4410 4540 5500 2301 5042"
	$"4451 4133 15F3 002E F700 2830 1200 2500"
	$"2300 2001 2042 5155 1325 0523 4250 4230"
	$"3210 2232 2302 5042 0022 0424 0220 5204"
	$"2002 4340 F400 2DF7 0027 4144 3143 1103"
	$"4103 2312 5032 0022 0024 0520 4210 1110"
	$"3504 5305 1115 5234 1101 1431 3544 5101"
	$"5042 F300 2DF7 0027 3200 2200 2100 2335"
	$"2401 5055 5251 2512 2525 5223 5253 2234"
	$"2301 2002 3052 3323 0120 4200 2302 5012"
	$"F300 2EF7 0028 0113 4431 0335 5550 0224"
	$"5230 1200 2504 2441 5005 1012 0022 0122"
	$"5551 1434 3155 5202 3055 0320 0203 40F4"
	$"002D F700 2740 5200 2505 2305 5321 1410"
	$"1330 5103 1141 0150 0510 1500 1100 2405"
	$"2052 2425 0423 5210 1141 1333 35F3 002D"
	$"F700 2715 4431 5251 0122 4520 0240 3240"
	$"2200 2103 2005 2042 0052 0025 0320 0230"
	$"1231 2222 3032 0023 0250 52F3 002E F700"
	$"2852 0022 0025 5514 0131 1433 1055 0053"
	$"0315 4101 5413 1015 0411 4353 0510 1504"
	$"2355 1154 2201 5002 4340 F400 2EF7 0028"
	$"1055 0415 3520 0220 0240 3200 5200 2200"
	$"2404 2002 3012 0025 0023 0220 4240 2505"
	$"5002 5421 3250 4543 40F4 002E F700 2813"
	$"2505 2303 1445 3450 3350 1240 5500 2101"
	$"1141 1014 3310 1101 4143 5431 1053 3331"
	$"3055 3224 1230 3240 F400 2EF7 0028 2201"
	$"5103 2002 2002 3042 0052 0022 0021 0023"
	$"0550 0230 1200 2104 2002 1032 0120 0230"
	$"2503 2331 5442 30F4 002F F800 1604 2510"
	$"5501 5445 3350 3150 1540 5500 2504 5103"
	$"2045 1454 FE33 0F31 0113 3110 5305 5012"
	$"0024 0220 0230 50F4 002F F800 2905 2035"
	$"0420 0520 0210 4240 1200 5200 2500 2203"
	$"5005 5042 0025 0424 0120 0200 2102 1011"
	$"3333 1432 1053 50F4 002F F800 2905 5012"
	$"0133 4143 1011 1042 4052 0025 0055 0024"
	$"0120 0510 5540 1103 5302 1022 0320 0240"
	$"2505 2002 2002 50F4 002F F800 2901 3240"
	$"2401 2002 5042 3012 0012 0025 0025 0331"
	$"0354 0550 1200 2504 2005 1313 4331 1411"
	$"0424 0510 4250 24F4 002F F800 2905 2015"
	$"0133 0550 4550 3240 1200 5200 2500 2404"
	$"2005 2002 3022 0423 0250 3200 2302 5052"
	$"0323 0250 4523 23F4 002F F800 2905 5435"
	$"0420 0250 0230 1240 5540 5500 2101 3143"
	$"4143 3411 3015 0453 4541 3055 0520 4200"
	$"2101 2002 1002 21F4 002F F800 2901 0510"
	$"5501 2002 5032 3012 0052 0052 0023 0424"
	$"0320 0250 1200 2105 2042 0055 0150 3133"
	$"1103 1305 1042 32F4 002F F800 2905 2042"
	$"1103 2002 1035 4015 4055 4055 0131 4101"
	$"4141 3443 1433 3331 0510 5200 2302 1052"
	$"0024 0520 0523 02F4 002F F800 2901 5300"
	$"1320 0520 0210 1200 1200 5200 2104 2404"
	$"2005 2002 1052 0320 0530 5145 0120 3200"
	$"5143 3343 0250 53F4 002F F800 2903 4024"
	$"0052 3330 3110 1540 1540 1143 4333 4131"
	$"0114 0550 4240 5105 5042 0023 0520 3240"
	$"2503 2001 2501 20F4 002E F700 2825 0150"
	$"0023 0210 0240 3200 1200 2500 2304 2401"
	$"2002 5045 4053 4313 1435 0324 0210 5200"
	$"2303 3500 5550 F400 2FF8 0029 0454 3141"
	$"4003 5554 3414 1130 1143 0331 0341 0114"
	$"0550 0210 5203 2002 4025 0150 3314 3540"
	$"5305 5002 2010 F400 2EF7 0028 1023 0425"
	$"0000 4220 0200 3200 2200 2104 2401 2001"
	$"5031 1310 5305 5052 0024 0250 4240 5202"
	$"1001 2101 50F4 002E F700 2851 0451 0524"
	$"4000 4352 5313 3344 1103 1103 2401 2002"
	$"5032 0053 0250 3543 1114 4310 5525 3005"
	$"1520 0550 F400 2EF7 0028 2100 2301 2312"
	$"3000 0005 2425 0021 0023 0124 0550 4313"
	$"5025 0320 0200 2101 2002 2114 0012 1323"
	$"0335 40F4 002E F700 2833 3504 2001 5002"
	$"2340 0000 0552 5555 0350 0320 0210 0240"
	$"1541 4314 4515 5555 3400 0452 1330 1104"
	$"2140 F400 2EF7 000A 0424 0120 0154 0550"
	$"4225 34FE 001A 5255 2341 5411 1120 2203"
	$"2302 5325 3440 0000 0520 4240 5200 5505"
	$"50F4 002D F700 1915 0323 0120 0520 0110"
	$"3243 2533 4000 0003 1155 5115 1311 1134"
	$"14FD 000A 4112 5035 3015 4334 5501 10F4"
	$"0028 F700 0F31 0124 0354 0510 0550 1200"
	$"1504 2515 13F9 000F 0400 3144 3525 5135"
	$"5042 3032 4052 0025 F300 2DF7 0027 0424"
	$"0150 0120 0520 0240 5200 5504 2105 2312"
	$"2322 2255 2535 5432 5422 4320 0550 0210"
	$"3230 1543 3311 F300 2EF7 0028 4151 0350"
	$"0534 0513 1414 1500 5104 5301 3333 3110"
	$"2500 2005 1013 3500 1301 3114 4510 4230"
	$"3240 2203 40F4 002E F700 2821 0320 0120"
	$"0320 0210 4200 5200 2101 2002 5002 4433"
	$"3101 2002 1012 0021 0320 0250 0230 1510"
	$"1204 3540 F400 2DF7 0027 5103 1101 5405"
	$"1430 3334 1431 4431 4313 3345 5022 0023"
	$"0550 1332 4025 0053 0133 5435 1042 3032"
	$"4022 F300 2EF7 0028 4024 0320 0520 0210"
	$"0210 4200 2500 2002 2002 4433 1501 2002"
	$"1012 0055 0421 0120 0250 0210 3240 3243"
	$"40F4 002E F700 2813 1301 1301 1414 4310"
	$"3534 1143 3103 5305 5022 0023 0154 1145"
	$"3052 0025 0354 0514 1405 1032 3015 4140"
	$"F400 2DF7 0027 2304 2003 2002 1002 3002"
	$"4012 0021 0120 0233 3415 0520 0210 1200"
	$"5504 1504 2103 2005 2002 1012 4022 F300"
	$"2DF7 0027 1301 4101 3110 1340 4510 4240"
	$"5501 5302 5052 0021 0514 1442 4055 0025"
	$"0025 0424 0113 3413 1035 4431 F300 2EF7"
	$"0028 4424 0420 0220 0210 0230 3540 5503"
	$"2405 3130 1503 2002 5032 0011 0415 0455"
	$"0351 0320 0250 0240 2201 40F4 002E F700"
	$"2832 4101 3114 4530 1310 4240 5200 2105"
	$"2032 0021 0134 1442 3052 0022 0022 0021"
	$"0323 0154 1341 4333 3140 F400 2DF7 0027"
	$"3304 2005 2002 5002 3032 4011 3413 4335"
	$"3052 0320 0220 1240 1134 3103 1103 3504"
	$"2101 2002 5012 0022 F300 2EF7 0028 1501"
	$"4350 4510 4510 3530 3200 5504 2042 0015"
	$"0333 3002 3012 0022 0022 0025 0021 0320"
	$"0554 4540 1303 40F4 002E F700 2843 2405"
	$"5005 2002 1032 0051 4434 3305 5012 0024"
	$"0220 1210 5544 3303 1143 1143 1544 5105"
	$"2042 3052 0340 F400 2EF7 0028 4141 5001"
	$"5005 5002 3012 0055 0021 0221 5555 3524"
	$"0210 5200 5213 2500 2500 2500 2103 2402"
	$"5035 4052 40F4 002E F700 2851 0250 0120"
	$"0250 4530 5543 5525 0550 0200 2402 2332"
	$"1051 3343 1311 5122 4313 4335 0354 0110"
	$"3240 1230 F400 2EF7 0028 4520 0110 0550"
	$"0230 1214 2500 5441 1152 1512 2502 2012"
	$"4122 1322 0055 0022 4521 0025 0520 0240"
	$"5200 50F4 002E F700 2345 5005 5005 3032"
	$"5154 4343 3212 2142 1025 0531 1011 3341"
	$"0131 1025 2240 3401 1531 4314 41FE 3301"
	$"4350 F400 2EF7 0028 5405 5001 5012 1032"
	$"0052 3525 2512 1522 2225 3223 2225 2255"
	$"2253 2212 2254 2100 2235 2002 2032 0025"
	$"10F4 002E F700 2853 0150 0224 4430 5555"
	$"3451 4320 0244 2015 0511 1150 3201 3133"
	$"1354 4501 1123 5514 5332 5002 3035 4450"
	$"F400 2EF7 0028 1420 0220 0250 5240 2201"
	$"2320 1153 4230 5505 2332 1012 4012 0025"
	$"4022 0425 1025 4224 0123 4110 3200 20F4"
	$"002E F700 2853 3415 3032 5255 2523 2202"
	$"2452 1255 2555 2532 2452 5152 1522 5122"
	$"1212 1321 5125 1221 0223 4240 5150 F400"
	$"2EF7 0028 5002 5032 5042 0025 3013 4314"
	$"2032 0023 4531 0210 3530 3200 2200 5203"
	$"1200 2345 5145 2132 2412 5013 20F4 002E"
	$"F700 2820 2512 2152 1535 1022 0224 1520"
	$"5245 1423 0223 4220 5213 5241 5453 1241"
	$"5154 2302 2552 2122 3022 0024 F400 2FF8"
	$"0029 0452 2531 5422 5152 4121 2102 2012"
	$"0322 1155 1202 2453 1553 5244 2220 5201"
	$"2511 2245 1225 5524 1540 5153 F400 2FF8"
	$"0029 0422 5150 4221 2204 2143 2405 5050"
	$"4504 2002 2101 2005 2002 0455 4051 0545"
	$"0020 4123 0125 0550 0220 3233 F400 2FF8"
	$"0029 0321 3550 1250 2201 5121 0254 5550"
	$"2201 2432 4542 1411 2442 3352 4022 0122"
	$"0423 3525 0223 4521 5452 5023 F400 2FF8"
	$"0029 0521 2152 5052 2252 0523 4255 5052"
	$"0122 3520 0253 4520 3213 3204 2230 5204"
	$"2114 2402 2502 2022 2415 2323 F400 2FF8"
	$"0029 0541 2145 3053 4214 5034 2402 3055"
	$"0105 5013 4505 5034 5441 0204 5130 1203"
	$"5414 5405 2133 0150 3240 5323 F400 2FF8"
	$"0029 0450 1250 2250 1251 2055 2113 5124"
	$"2505 2032 5105 2042 2442 1322 3022 3522"
	$"4323 3252 2523 0250 1230 5552 F400 2EF7"
	$"0028 1501 2155 1341 2201 2042 4025 5505"
	$"1213 2345 1531 5012 1532 5120 5535 3241"
	$"5453 0220 4210 2244 1233 22F4 002E F700"
	$"2805 5042 1022 0152 0353 1432 4023 0223"
	$"4520 0213 4520 3253 0200 1230 5504 2445"
	$"2032 5042 1025 1434 2353 F400 2DF6 0027"
	$"5500 1221 2242 2422 5552 2525 2232 2152"
	$"5215 5155 2512 5552 5525 5252 5521 5225"
	$"4221 4254 5245 1310 F400 2CF6 0026 0421"
	$"0411 5105 2150 3200 2041 2401 2005 5105"
	$"5001 2002 3342 4055 0152 0020 0520 0114"
	$"0110 4550 35F3 002B F500 2503 5304 3225"
	$"2254 1235 5125 4212 2155 3212 2151 5552"
	$"3255 2555 1215 5525 5225 2412 1422 2103"
	$"50F3 0029 F400 2304 5340 1522 5244 5540"
	$"2405 5331 2405 5101 2012 1105 1412 1052"
	$"0323 4125 3110 1113 2500 11F2 0028 F300"
	$"2204 5100 0125 5245 2155 1502 2412 1242"
	$"1353 5335 1232 1055 4252 4123 1221 4222"
	$"5300 1230 F200 25F1 001F 1144 0051 2123"
	$"5225 0120 3511 0120 0520 0213 5550 1505"
	$"1203 2521 5532 3004 5210 F100 23F0 001D"
	$"4323 0400 0031 3222 2225 4212 5521 2255"
	$"1213 2221 2252 2515 2114 0003 5130 F000"
	$"20EF 001A 1251 3334 4000 0035 1135 2545"
	$"2412 2112 3322 2115 4044 4000 0435 53EE"
	$"0019 EF00 0602 4004 4435 5344 FA00 0333"
	$"4334 30FC 0002 4513 30ED 001B EF00 0103"
	$"20FE 0007 0333 3111 1513 4440 FC00 0504"
	$"4433 1321 34EB 0016 EE00 0021 F900 0C45"
	$"4315 5111 3315 1155 3334 0025 EA00 14EE"
	$"0000 32F9 0005 0300 0410 0444 FC00 0105"
	$"20EA 0012 EE00 0102 10F9 0002 3530 10FA"
	$"0001 0230 EA00 12EE 0001 0120 FA00 0303"
	$"0510 10FA 0000 12E9 0011 ED00 0023 FA00"
	$"0305 1525 30FA 0000 21E9 0010 ED00 0052"
	$"F900 0105 50FA 0001 0320 E900 11ED 0001"
	$"0210 FA00 0101 50FA 0001 0250 E900 10ED"
	$"0001 0120 FA00 0105 20FA 0000 12E8 000F"
	$"EC00 0024 FA00 0105 20FA 0000 22E8 0010"
	$"EC00 0032 FA00 0105 20FB 0001 0420 E800"
	$"11EC 0001 0230 FB00 0105 20FB 0001 0520"
	$"E800 11EC 0001 0120 FB00 0105 20FB 0001"
	$"4540 E800 0FEB 0000 21FB 0001 0520 FB00"
	$"0052 E700 0FEB 0000 12FB 0001 0520 FB00"
	$"0053 E700 11EB 0001 0230 FC00 0101 20FC"
	$"0001 0520 E700 11EB 0001 0120 FC00 0105"
	$"20FC 0001 0210 E700 0FEA 0000 23FC 0001"
	$"0550 FC00 0032 E600 0FEA 0000 52FC 0001"
	$"0120 FC00 0025 E600 11EA 0001 0240 FD00"
	$"0101 20FD 0001 0424 E600 11EA 0001 0120"
	$"FD00 0105 50FD 0001 0520 E600 10E9 0000"
	$"23FD 0001 0550 FD00 0142 40E6 000F E900"
	$"0015 FD00 0105 20FD 0000 52E5 0010 E900"
	$"0102 30FE 0001 0150 FD00 0023 E500 11E9"
	$"0001 0520 FE00 0101 20FE 0001 0150 E500"
	$"11E9 0001 0424 FE00 0105 20FE 0001 0210"
	$"E500 0FE8 0000 25FE 0001 0550 FE00 0012"
	$"E400 0FE8 0005 0230 0000 0550 FE00 0021"
	$"E400 0FE8 0005 0250 0000 0150 FE00 0020"
	$"E400 0FE8 0009 0420 0000 0550 0000 0550"
	$"E400 0DE7 0007 5200 0001 5000 0002 E300"
	$"0DE7 0007 0240 0005 5000 0052 E300 0DE7"
	$"0007 0220 0001 5000 0023 E300 0DE7 0007"
	$"0424 0005 5000 0320 E300 0CE6 0006 2500"
	$"0150 0002 30E3 000B E600 0502 4005 5000"
	$"32E2 000B E600 0502 5001 5000 21E2 000A"
	$"E500 0420 0150 0420 E200 0AE5 0004 5501"
	$"5002 10E2 0009 E500 0302 0150 02E1 0009"
	$"E500 0305 1150 21E1 0009 E500 0304 2210"
	$"20E1 0008 E400 0252 1150 E100 07E4 0001"
	$"4222 E000 07E4 0001 4221 E000 07E4 0001"
	$"0221 E000 08E4 0002 5252 40E1 0008 E400"
	$"0223 0320 E100 09E5 0003 0324 0024 E100"
	$"09E5 0003 0320 0021 E100 09E5 0003 0110"
	$"0023 E100 09E5 0003 0320 0024 E100 08E4"
	$"0002 2211 20E1 0008 E400 0202 2210 E100"
	$"02C1 0002 C100 02C1 0002 C100 02C1 0000"
	$"00FF"
};

resource 'PICT' (130, "Menu bar") {
	13792,
	{0, 0, 28, 225},
	$"0011 02FF 0C00 FFFE 0000 0048 0000 0048"
	$"0000 0000 0000 001C 00E1 0000 0000 001E"
	$"0001 000A 0000 0000 0300 0400 009A 0000"
	$"00FF 8384 0000 0000 001C 00E1 0000 0004"
	$"0000 0000 0048 0000 0048 0000 0010 0020"
	$"0004 0008 0000 0020 002F E77C 007F A744"
	$"0000 0000 001C 00E1 0000 0000 001C 00E1"
	$"0000 002E 8100 9D00 0233 7DBC 81FA ACFA"
	$"02BC 7D33 FB00 0233 7DBC 81FA ACFA 02BC"
	$"7D33 FB00 0233 7DBC 81FA ACFA 02BC 7D33"
	$"FE00 0038 F700 F2FF 8100 B700 0365 CFF5"
	$"F381 F1AC F103 F3F5 CF65 FD00 0365 CFF5"
	$"F381 F1AC F103 F3F5 CF65 FD00 0365 CFF5"
	$"F381 F1AC F105 F3F5 CF65 0000 0286 8100"
	$"9F00 0867 EDF7 F5F6 F6F5 F6F5 F2F6 0CF5"
	$"F5F6 F5F5 F6F6 F5F5 F6F5 F6F6 FEF5 7FF6"
	$"F6F5 F5F6 F5F6 F6F5 F5F6 F6F5 F5F6 F6F5"
	$"F5F6 F6F5 F5F6 F6F5 F5F6 F6F5 F5F6 F6F5"
	$"F5F6 F6F5 F5F6 F6F5 F5F6 F6F5 F5F6 F6F5"
	$"F5F6 F6F5 F5F6 F6F5 F5F6 F6F5 F5F6 F6F5"
	$"F5F6 F6F5 F5F6 F6F5 F5F6 F6F5 F5F6 F6F5"
	$"F5F6 F6F5 F5F6 F6F5 F5F6 F6F5 F5F6 F6F5"
	$"F5F6 F6F5 F5F6 F6F5 F5F6 F6F5 F5F6 F6F5"
	$"F5F6 F6F5 F5F6 F6F5 F5F6 F6F5 F5F6 F641"
	$"F5F5 F6F6 F5F5 F6F6 F5F5 F6F6 F5F5 F6F6"
	$"F5F5 F6F6 F5F6 F6F5 F5F6 F6F5 F5F6 F6F5"
	$"F5F6 F6F5 F5F6 F6F5 F5F6 F6F5 F5F6 F6F5"
	$"F5F6 F6F5 F7ED 6700 0067 EDF7 F5F6 F6F5"
	$"F6F5 F2F6 0CF5 F5F6 F5F5 F6F6 F5F5 F6F5"
	$"F6F6 FEF5 7FF6 F6F5 F5F6 F5F6 F6F5 F5F6"
	$"F6F5 F5F6 F6F5 F5F6 F6F5 F5F6 F6F5 F5F6"
	$"F6F5 F5F6 F6F5 F5F6 F6F5 F5F6 F6F5 F5F6"
	$"F6F5 F5F6 F6F5 F5F6 F6F5 F5F6 F6F5 F5F6"
	$"F6F5 F5F6 F6F5 F5F6 F6F5 F5F6 F6F5 F5F6"
	$"F6F5 F5F6 F6F5 F5F6 F6F5 F5F6 F6F5 F5F6"
	$"F6F5 F5F6 F6F5 F5F6 F6F5 F5F6 F6F5 F5F6"
	$"F6F5 F5F6 F6F5 F5F6 F6F5 F5F6 F6F5 F5F6"
	$"F6F5 F5F6 F641 F5F5 F6F6 F5F5 F6F6 F5F5"
	$"F6F6 F5F5 F6F6 F5F5 F6F6 F5F6 F6F5 F5F6"
	$"F6F5 F5F6 F6F5 F5F6 F6F5 F5F6 F6F5 F5F6"
	$"F6F5 F5F6 F6F5 F5F6 F6F5 F7ED 6700 0067"
	$"EDF7 F5F6 F6F5 F6F5 F2F6 0CF5 F5F6 F5F5"
	$"F6F6 F5F5 F6F5 F6F6 FEF5 7FF6 F6F5 F5F6"
	$"F5F6 F6F5 F5F6 F6F5 F5F6 F6F5 F5F6 F6F5"
	$"F5F6 F6F5 F5F6 F6F5 F5F6 F6F5 F5F6 F6F5"
	$"F5F6 F6F5 F5F6 F6F5 F5F6 F6F5 F5F6 F6F5"
	$"F5F6 F6F5 F5F6 F6F5 F5F6 F6F5 F5F6 F6F5"
	$"F5F6 F6F5 F5F6 F6F5 F5F6 F6F5 F5F6 F6F5"
	$"F5F6 F6F5 F5F6 F6F5 F5F6 F6F5 F5F6 F6F5"
	$"F5F6 F6F5 F5F6 F6F5 F5F6 F6F5 F5F6 F6F5"
	$"F5F6 F6F5 F5F6 F6F5 F5F6 F637 F5F5 F6F6"
	$"F5F5 F6F6 F5F5 F6F6 F5F5 F6F6 F5F5 F6F6"
	$"F5F6 F6F5 F5F6 F6F5 F5F6 F6F5 F5F6 F6F5"
	$"F5F6 F6F5 F5F6 F6F5 F5F6 F6F5 F5F6 F6F5"
	$"F7ED 6700 0279 F500 00FF 8100 AD00 0134"
	$"D2FE F600 F5ED F603 F5F6 F6F5 FEF6 02F5"
	$"F6F5 FEF6 01F5 F5FE F602 F5F6 F5FE F600"
	$"F5FE F600 F5FE F600 F5FE F600 F5FE F600"
	$"F5FE F600 F5FE F600 F5FE F600 F5FE F600"
	$"F5FE F600 F5FE F600 F5FE F600 F5FE F600"
	$"F5FE F600 F5FE F600 F5FE F600 F5FE F600"
	$"F5FE F600 F5FE F600 F5FE F600 F5FE F600"
	$"F5FE F600 F5FE F600 F5FE F600 F5FE F600"
	$"F5FE F600 F5FE F600 F5FE F600 F5FE F600"
	$"F5FE F600 F5FE F600 F5FE F600 F5FE F600"
	$"F5FE F600 F5FE F603 F5F6 F6F5 FEF6 00F5"
	$"FEF6 00F5 FEF6 00F5 FEF6 00F5 FEF6 00F5"
	$"FEF6 00F5 FEF6 02F5 F6F5 FEF6 03D2 3434"
	$"D2FE F600 F5ED F603 F5F6 F6F5 FEF6 02F5"
	$"F6F5 FEF6 01F5 F5FE F602 F5F6 F5FE F600"
	$"F5FE F600 F5FE F600 F5FE F600 F5FE F600"
	$"F5FE F600 F5FE F600 F5FE F600 F5FE F600"
	$"F5FE F600 F5FE F600 F5FE F600 F5FE F600"
	$"F5FE F600 F5FE F600 F5FE F600 F5FE F600"
	$"F5FE F600 F5FE F600 F5FE F600 F5FE F600"
	$"F5FE F600 F5FE F600 F5FE F600 F5FE F600"
	$"F5FE F600 F5FE F600 F5FE F600 F5FE F600"
	$"F5FE F600 F5FE F600 F5FE F600 F5FE F600"
	$"F5FE F600 F5FE F603 F5F6 F6F5 FEF6 00F5"
	$"FEF6 00F5 FEF6 00F5 FEF6 00F5 FEF6 00F5"
	$"FEF6 00F5 FEF6 02F5 F6F5 FEF6 03D2 3434"
	$"D2FE F600 F5ED F603 F5F6 F6F5 FEF6 02F5"
	$"F6F5 FEF6 01F5 F5FE F602 F5F6 F5FE F600"
	$"F5FE F600 F5FE F600 F5FE F600 F5FE F600"
	$"F5FE F600 F5FE F600 F5FE F600 F5FE F600"
	$"F5FE F600 F5FE F600 F5FE F600 F5FE F600"
	$"F5FE F600 F5FE F600 F5FE F600 F5FE F600"
	$"F5FE F600 F5FE F600 F5FE F600 F5FE F600"
	$"F5FE F600 F5FE F600 F5FE F600 F5FE F600"
	$"F5FE F600 F5FE F600 F5FE F600 F5FE F600"
	$"F5FE F600 F5FE F600 F5FE F600 F5FE F600"
	$"F5FE F600 F5FE F603 F5F6 F6F5 FEF6 00F5"
	$"FEF6 00F5 FEF6 00F5 FEF6 00F5 FEF6 00F5"
	$"FEF6 00F5 FEF6 02F5 F6F5 FEF6 01D2 3402"
	$"6F81 00A0 0001 7CF2 FDF0 03F1 F0F1 F0F9"
	$"F103 B42B 18D2 FEF1 FBF0 00F1 FCF0 00F1"
	$"FDF0 00F1 FCF0 00F1 FEF0 00F1 FEF0 00F1"
	$"FEF0 00F1 FEF0 00F1 FEF0 00F1 FEF0 00F1"
	$"FEF0 00F1 FEF0 00F1 FEF0 00F1 FEF0 00F1"
	$"FEF0 00F1 FEF0 00F1 FEF0 00F1 FEF0 00F1"
	$"FEF0 00F1 FEF0 00F1 FEF0 00F1 FEF0 00F1"
	$"FEF0 00F1 FEF0 00F1 FEF0 00F1 FEF0 00F1"
	$"FEF0 00F1 FEF0 00F1 FEF0 00F1 FEF0 00F1"
	$"FEF0 00F1 FEF0 00F1 FEF0 00F1 FEF0 00F1"
	$"FEF0 00F1 FEF0 00F1 FEF0 00F1 FEF0 00F1"
	$"FEF0 03F1 F0F0 F1FE F000 F1FE F000 F1FE"
	$"F000 F1FE F000 F1FE F000 F1FE F000 F1FA"
	$"F003 F27C 7CF2 FDF0 03F1 F0F1 F0F9 F103"
	$"CA79 69DD FEF1 FBF0 00F1 FCF0 00F1 FDF0"
	$"00F1 FCF0 00F1 FEF0 00F1 FEF0 00F1 FEF0"
	$"00F1 FEF0 00F1 FEF0 00F1 FEF0 00F1 FEF0"
	$"00F1 FEF0 00F1 FEF0 00F1 FEF0 00F1 FEF0"
	$"00F1 FEF0 00F1 FEF0 00F1 FEF0 00F1 FEF0"
	$"00F1 FEF0 00F1 FEF0 00F1 FEF0 00F1 FEF0"
	$"00F1 FEF0 00F1 FEF0 00F1 FEF0 00F1 FEF0"
	$"00F1 FEF0 00F1 FEF0 00F1 FEF0 00F1 FEF0"
	$"00F1 FEF0 00F1 FEF0 00F1 FEF0 00F1 FEF0"
	$"00F1 FEF0 00F1 FEF0 00F1 FEF0 00F1 FEF0"
	$"03F1 F0F0 F1FE F000 F1FE F000 F1FE F000"
	$"F1FE F000 F1FE F000 F1FE F000 F1FA F003"
	$"F27C 7CF2 FDF0 03F1 F0F1 F0F9 F103 E4CF"
	$"CBEB FEF1 FBF0 00F1 FCF0 00F1 FDF0 00F1"
	$"FCF0 00F1 FEF0 00F1 FEF0 00F1 FEF0 00F1"
	$"FEF0 00F1 FEF0 00F1 FEF0 00F1 FEF0 00F1"
	$"FEF0 00F1 FEF0 00F1 FEF0 00F1 FEF0 00F1"
	$"FEF0 00F1 FEF0 00F1 FEF0 00F1 FEF0 00F1"
	$"FEF0 00F1 FEF0 00F1 FEF0 00F1 FEF0 00F1"
	$"FEF0 00F1 FEF0 00F1 FEF0 00F1 FEF0 00F1"
	$"FEF0 00F1 FEF0 00F1 FEF0 00F1 FEF0 00F1"
	$"FEF0 00F1 FEF0 00F1 FEF0 00F1 FEF0 00F1"
	$"FEF0 00F1 FEF0 00F1 FEF0 00F1 FEF0 03F1"
	$"F0F0 F1FE F000 F1FE F000 F1FE F000 F1FE"
	$"F000 F1FE F000 F1FE F000 F1FA F001 F27C"
	$"0292 F700 FAFF FD00 FDFF 8100 B900 03B8"
	$"EFF0 EEFB F0FA F103 D817 0048 FDF1 05F0"
	$"F0EF F0F0 EFFE F002 EFF0 EFFD F000 EFFE"
	$"F002 EFF0 EFFE F000 EFFE F000 EFFE F000"
	$"EFFE F000 EFFE F000 EFFE F000 EFFE F000"
	$"EFFE F000 EFFE F000 EFFE F000 EFFE F000"
	$"EFFE F000 EFFE F000 EFFE F000 EFFE F000"
	$"EFFE F000 EFFE F000 EFFE F000 EFFE F000"
	$"EFFE F000 EFFE F000 EFFE F000 EFFE F000"
	$"EFFE F000 EFFE F000 EFFE F000 EFFE F000"
	$"EFFE F000 EFFE F000 EFFE F000 EFFE F000"
	$"EFFE F000 EFFE F000 EFFE F000 EFFE F003"
	$"EFF0 F0EF FEF0 00EF FEF0 00EF FEF0 00EF"
	$"FEF0 00EF FEF0 00EF FEF0 00EF FEF0 0AEF"
	$"F0F0 EEF0 EFB8 B8EF F0EE FBF0 FAF1 03E2"
	$"6555 87FD F105 F0F0 EFF0 F0EF FEF0 02EF"
	$"F0EF FDF0 00EF FEF0 02EF F0EF FEF0 00EF"
	$"FEF0 00EF FEF0 00EF FEF0 00EF FEF0 00EF"
	$"FEF0 00EF FEF0 00EF FEF0 00EF FEF0 00EF"
	$"FEF0 00EF FEF0 00EF FEF0 00EF FEF0 00EF"
	$"FEF0 00EF FEF0 00EF FEF0 00EF FEF0 00EF"
	$"FEF0 00EF FEF0 00EF FEF0 00EF FEF0 00EF"
	$"FEF0 00EF FEF0 00EF FEF0 00EF FEF0 00EF"
	$"FEF0 00EF FEF0 00EF FEF0 00EF FEF0 00EF"
	$"FEF0 00EF FEF0 00EF FEF0 00EF FEF0 00EF"
	$"FEF0 00EF FEF0 03EF F0F0 EFFE F000 EFFE"
	$"F000 EFFE F000 EFFE F000 EFFE F000 EFFE"
	$"F000 EFFE F00A EFF0 F0EE F0EF B8B8 EFF0"
	$"EEFB F0FA F103 EFCD C9D6 FDF1 05F0 F0EF"
	$"F0F0 EFFE F002 EFF0 EFFD F000 EFFE F002"
	$"EFF0 EFFE F000 EFFE F000 EFFE F000 EFFE"
	$"F000 EFFE F000 EFFE F000 EFFE F000 EFFE"
	$"F000 EFFE F000 EFFE F000 EFFE F000 EFFE"
	$"F000 EFFE F000 EFFE F000 EFFE F000 EFFE"
	$"F000 EFFE F000 EFFE F000 EFFE F000 EFFE"
	$"F000 EFFE F000 EFFE F000 EFFE F000 EFFE"
	$"F000 EFFE F000 EFFE F000 EFFE F000 EFFE"
	$"F000 EFFE F000 EFFE F000 EFFE F000 EFFE"
	$"F000 EFFE F000 EFFE F000 EFFE F003 EFF0"
	$"F0EF FEF0 00EF FEF0 00EF FEF0 00EF FEF0"
	$"00EF FEF0 00EF FEF0 00EF FEF0 06EF F0F0"
	$"EEF0 EFB8 027B 8100 A000 00E6 FBF4 03F5"
	$"F4F5 F5FE F60E F5F6 F685 0012 C3F6 F5F6"
	$"F6F5 F4F4 F5FE F400 F5FC F400 F5FD F400"
	$"F5FC F400 F5FE F400 F5FE F400 F5FE F400"
	$"F5FE F400 F5FE F400 F5FE F400 F5FE F400"
	$"F5FE F400 F5FE F400 F5FE F400 F5FE F400"
	$"F5FE F400 F5FE F400 F5FE F400 F5FE F400"
	$"F5FE F400 F5FE F400 F5FE F400 F5FE F400"
	$"F5FE F400 F5FE F400 F5FE F400 F5FE F400"
	$"F5FE F400 F5FE F400 F5FE F400 F5FE F400"
	$"F5FE F400 F5FE F400 F5FE F400 F5FE F400"
	$"F5FE F400 F5FE F400 F5FE F400 F5FB F400"
	$"F5FE F400 F5FE F400 F5FE F400 F5FE F400"
	$"F5FE F400 F5FE F400 F5FA F401 E6E6 FBF4"
	$"03F5 F4F5 F5FE F60E F5F6 F6AA 4C5C D5F6"
	$"F5F6 F6F5 F4F4 F5FE F400 F5FC F400 F5FD"
	$"F400 F5FC F400 F5FE F400 F5FE F400 F5FE"
	$"F400 F5FE F400 F5FE F400 F5FE F400 F5FE"
	$"F400 F5FE F400 F5FE F400 F5FE F400 F5FE"
	$"F400 F5FE F400 F5FE F400 F5FE F400 F5FE"
	$"F400 F5FE F400 F5FE F400 F5FE F400 F5FE"
	$"F400 F5FE F400 F5FE F400 F5FE F400 F5FE"
	$"F400 F5FE F400 F5FE F400 F5FE F400 F5FE"
	$"F400 F5FE F400 F5FE F400 F5FE F400 F5FE"
	$"F400 F5FE F400 F5FE F400 F5FE F400 F5FB"
	$"F400 F5FE F400 F5FE F400 F5FE F400 F5FE"
	$"F400 F5FE F400 F5FE F400 F5FA F401 E6E6"
	$"FBF4 03F5 F4F5 F5FE F60E F5F6 F6E0 C7CB"
	$"EAF6 F5F6 F6F5 F4F4 F5FE F400 F5FC F400"
	$"F5FD F400 F5FC F400 F5FE F400 F5FE F400"
	$"F5FE F400 F5FE F400 F5FE F400 F5FE F400"
	$"F5FE F400 F5FE F400 F5FE F400 F5FE F400"
	$"F5FE F400 F5FE F400 F5FE F400 F5FE F400"
	$"F5FE F400 F5FE F400 F5FE F400 F5FE F400"
	$"F5FE F400 F5FE F400 F5FE F400 F5FE F400"
	$"F5FE F400 F5FE F400 F5FE F400 F5FE F400"
	$"F5FE F400 F5FE F400 F5FE F400 F5FE F400"
	$"F5FE F400 F5FE F400 F5FE F400 F5FE F400"
	$"F5FB F400 F5FE F400 F5FE F400 F5FE F400"
	$"F5FE F400 F5FE F400 F5FE F400 F5FA F400"
	$"E602 A9F8 00FC FF81 00AE 0008 F5F4 F4F3"
	$"F4F3 F4F3 F4FC F506 F0F0 F17E 44C1 F1FE"
	$"F00D F1F3 F3F4 F3F3 F4F4 F3F3 F4F3 F4F4"
	$"FEF3 7FF4 F4F3 F3F4 F3F4 F4F3 F3F4 F4F3"
	$"F3F4 F4F3 F3F4 F4F3 F3F4 F4F3 F3F4 F4F3"
	$"F3F4 F4F3 F3F4 F4F3 F3F4 F4F3 F3F4 F4F3"
	$"F3F4 F4F3 F3F4 F4F3 F3F4 F4F3 F3F4 F4F3"
	$"F3F4 F4F3 F3F4 F4F3 F3F4 F4F3 F3F4 F4F3"
	$"F3F4 F4F3 F3F4 F4F3 F3F4 F4F3 F3F4 F4F3"
	$"F3F4 F4F3 F3F4 F4F3 F3F4 F4F3 F3F4 F4F3"
	$"F3F4 F4F3 F3F4 F4F3 F3F4 F4F3 F3F4 F4F3"
	$"F3F4 F440 F3F3 F4F4 F3F3 F4F4 F3F3 F4F4"
	$"F3F3 F4F4 F3F3 F4F4 F3F4 F4F3 F3F4 F4F3"
	$"F3F4 F4F3 F3F4 F4F3 F3F4 F4F3 F3F4 F4F3"
	$"F3F4 F4F3 F3F4 F3F4 F3F4 F4F5 F5F4 F4F3"
	$"F4F3 F4F3 F4FC F506 F0F0 F1A0 79D0 F1FE"
	$"F00D F1F3 F3F4 F3F3 F4F4 F3F3 F4F3 F4F4"
	$"FEF3 7FF4 F4F3 F3F4 F3F4 F4F3 F3F4 F4F3"
	$"F3F4 F4F3 F3F4 F4F3 F3F4 F4F3 F3F4 F4F3"
	$"F3F4 F4F3 F3F4 F4F3 F3F4 F4F3 F3F4 F4F3"
	$"F3F4 F4F3 F3F4 F4F3 F3F4 F4F3 F3F4 F4F3"
	$"F3F4 F4F3 F3F4 F4F3 F3F4 F4F3 F3F4 F4F3"
	$"F3F4 F4F3 F3F4 F4F3 F3F4 F4F3 F3F4 F4F3"
	$"F3F4 F4F3 F3F4 F4F3 F3F4 F4F3 F3F4 F4F3"
	$"F3F4 F4F3 F3F4 F4F3 F3F4 F4F3 F3F4 F4F3"
	$"F3F4 F440 F3F3 F4F4 F3F3 F4F4 F3F3 F4F4"
	$"F3F3 F4F4 F3F3 F4F4 F3F4 F4F3 F3F4 F4F3"
	$"F3F4 F4F3 F3F4 F4F3 F3F4 F4F3 F3F4 F4F3"
	$"F3F4 F4F3 F3F4 F3F4 F3F4 F4F5 F5F4 F4F3"
	$"F4F3 F4F3 F4FC F506 F0F0 F1DB D1E7 F1FE"
	$"F00D F1F3 F3F4 F3F3 F4F4 F3F3 F4F3 F4F4"
	$"FEF3 7FF4 F4F3 F3F4 F3F4 F4F3 F3F4 F4F3"
	$"F3F4 F4F3 F3F4 F4F3 F3F4 F4F3 F3F4 F4F3"
	$"F3F4 F4F3 F3F4 F4F3 F3F4 F4F3 F3F4 F4F3"
	$"F3F4 F4F3 F3F4 F4F3 F3F4 F4F3 F3F4 F4F3"
	$"F3F4 F4F3 F3F4 F4F3 F3F4 F4F3 F3F4 F4F3"
	$"F3F4 F4F3 F3F4 F4F3 F3F4 F4F3 F3F4 F4F3"
	$"F3F4 F4F3 F3F4 F4F3 F3F4 F4F3 F3F4 F4F3"
	$"F3F4 F4F3 F3F4 F4F3 F3F4 F4F3 F3F4 F4F3"
	$"F3F4 F437 F3F3 F4F4 F3F3 F4F4 F3F3 F4F4"
	$"F3F3 F4F4 F3F3 F4F4 F3F4 F4F3 F3F4 F4F3"
	$"F3F4 F4F3 F3F4 F4F3 F3F4 F4F3 F3F4 F4F3"
	$"F3F4 F4F3 F3F4 F3F4 F3F4 F4F5 0044 F700"
	$"00FF F400 00FF 8100 B900 F6EE 0CEF E091"
	$"6175 BBDB DDAF 6D60 A7E8 81EE ADEE 0CEF"
	$"E19B 768D C8E1 E3C6 9D92 BBE9 81EE ADEE"
	$"0CEF ECD9 CFD6 E5EB ECE4 DBD7 D0E9 81EE"
	$"B8EE 02A3 F700 00FF 8100 AB00 05ED EEEC"
	$"EEEE EDFC EE13 C428 003A 6A45 3623 074C"
	$"6229 54D7 EEEE EDEE EEED FEEE 02ED EEED"
	$"FDEE 00ED FEEE 02ED EEED FEEE 00ED FEEE"
	$"00ED FEEE 00ED FEEE 00ED FEEE 00ED FEEE"
	$"00ED FEEE 00ED FEEE 00ED FEEE 00ED FEEE"
	$"00ED FEEE 00ED FEEE 00ED FEEE 00ED FEEE"
	$"00ED FEEE 00ED FEEE 00ED FEEE 00ED FEEE"
	$"00ED FEEE 00ED FEEE 00ED FEEE 00ED FEEE"
	$"00ED FEEE 00ED FEEE 00ED FEEE 00ED FEEE"
	$"00ED FEEE 00ED FEEE 00ED FEEE 00ED FEEE"
	$"00ED FEEE 00ED FEEE 00ED FEEE 00ED FEEE"
	$"00ED FEEE 03ED EEEE EDFE EE00 EDFE EE00"
	$"EDFE EE00 EDFE EE00 EDFE EE00 EDFE EE00"
	$"EDFE EE0C EDED EEEE ECEE EDED EEEC EEEE"
	$"EDFC EE13 C735 4285 A287 7865 6196 A06F"
	$"7CDB EEEE EDEE EEED FEEE 02ED EEED FDEE"
	$"00ED FEEE 02ED EEED FEEE 00ED FEEE 00ED"
	$"FEEE 00ED FEEE 00ED FEEE 00ED FEEE 00ED"
	$"FEEE 00ED FEEE 00ED FEEE 00ED FEEE 00ED"
	$"FEEE 00ED FEEE 00ED FEEE 00ED FEEE 00ED"
	$"FEEE 00ED FEEE 00ED FEEE 00ED FEEE 00ED"
	$"FEEE 00ED FEEE 00ED FEEE 00ED FEEE 00ED"
	$"FEEE 00ED FEEE 00ED FEEE 00ED FEEE 00ED"
	$"FEEE 00ED FEEE 00ED FEEE 00ED FEEE 00ED"
	$"FEEE 00ED FEEE 00ED FEEE 00ED FEEE 00ED"
	$"FEEE 03ED EEEE EDFE EE00 EDFE EE00 EDFE"
	$"EE00 EDFE EE00 EDFE EE00 EDFE EE00 EDFE"
	$"EE0C EDED EEEE ECEE EDED EEEC EEEE EDFC"
	$"EE13 E3BB C0D1 DDD6 D1CD C9D0 CA99 8FDA"
	$"EEEE EDEE EEED FEEE 02ED EEED FDEE 00ED"
	$"FEEE 02ED EEED FEEE 00ED FEEE 00ED FEEE"
	$"00ED FEEE 00ED FEEE 00ED FEEE 00ED FEEE"
	$"00ED FEEE 00ED FEEE 00ED FEEE 00ED FEEE"
	$"00ED FEEE 00ED FEEE 00ED FEEE 00ED FEEE"
	$"00ED FEEE 00ED FEEE 00ED FEEE 00ED FEEE"
	$"00ED FEEE 00ED FEEE 00ED FEEE 00ED FEEE"
	$"00ED FEEE 00ED FEEE 00ED FEEE 00ED FEEE"
	$"00ED FEEE 00ED FEEE 00ED FEEE 00ED FEEE"
	$"00ED FEEE 00ED FEEE 00ED FEEE 00ED FEEE"
	$"03ED EEEE EDFE EE00 EDFE EE00 EDFE EE00"
	$"EDFE EE00 EDFE EE00 EDFE EE00 EDFE EE06"
	$"EDED EEEE ECEE ED02 A381 00A0 00FE F27F"
	$"F1F2 F1F1 F2F1 F2E1 2512 A5B6 B1AF A98E"
	$"9099 823A 0CC5 F2F1 F2F2 F1F2 F1F2 F1F2"
	$"F1F2 F1F2 F1F1 F2F1 F2F1 F2F1 F2F1 F2F1"
	$"F2F1 F2F1 F2F1 F2F1 F2F1 F2F1 F2F1 F2F1"
	$"F2F1 F2F1 F2F1 F2F1 F2F1 F2F1 F2F1 F2F1"
	$"F2F1 F2F1 F2F1 F2F1 F2F1 F2F1 F2F1 F2F1"
	$"F2F1 F2F1 F2F1 F2F1 F2F1 F2F1 F2F1 F2F1"
	$"F2F1 F2F1 F2F1 F2F1 F2F1 F2F1 F2F1 F2F1"
	$"5AF2 F1F2 F1F2 F1F2 F1F2 F1F2 F1F2 F1F2"
	$"F1F2 F1F2 F1F2 F1F2 F1F2 F1F2 F1F2 F1F2"
	$"F1F2 F1F2 F1F2 F1F2 F1F2 F1F2 F1F2 F1F2"
	$"F1F2 F1F2 F1F2 F1F2 F1F2 F1F1 F2F1 F2F1"
	$"F2F1 F2F1 F2F1 F2F1 F2F1 F2F1 F2F1 F2F1"
	$"F2F1 F2F1 F2F1 F2F1 F2F1 F2F1 FBF2 7FF1"
	$"F2F1 F1F2 F1F2 E138 6FC6 D4CF D0CE BEBD"
	$"C1B4 865F CDF2 F1F2 F2F1 F2F1 F2F1 F2F1"
	$"F2F1 F2F1 F1F2 F1F2 F1F2 F1F2 F1F2 F1F2"
	$"F1F2 F1F2 F1F2 F1F2 F1F2 F1F2 F1F2 F1F2"
	$"F1F2 F1F2 F1F2 F1F2 F1F2 F1F2 F1F2 F1F2"
	$"F1F2 F1F2 F1F2 F1F2 F1F2 F1F2 F1F2 F1F2"
	$"F1F2 F1F2 F1F2 F1F2 F1F2 F1F2 F1F2 F1F2"
	$"F1F2 F1F2 F1F2 F1F2 F1F2 F1F2 F1F2 F15A"
	$"F2F1 F2F1 F2F1 F2F1 F2F1 F2F1 F2F1 F2F1"
	$"F2F1 F2F1 F2F1 F2F1 F2F1 F2F1 F2F1 F2F1"
	$"F2F1 F2F1 F2F1 F2F1 F2F1 F2F1 F2F1 F2F1"
	$"F2F1 F2F1 F2F1 F2F1 F2F1 F1F2 F1F2 F1F2"
	$"F1F2 F1F2 F1F2 F1F2 F1F2 F1F2 F1F2 F1F2"
	$"F1F2 F1F2 F1F2 F1F2 F1F2 F1FB F27F F1F2"
	$"F1F1 F2F1 F2E5 B9C6 E8EB EAEB E9E3 E2E5"
	$"E0C3 84CC F2F1 F2F2 F1F2 F1F2 F1F2 F1F2"
	$"F1F2 F1F1 F2F1 F2F1 F2F1 F2F1 F2F1 F2F1"
	$"F2F1 F2F1 F2F1 F2F1 F2F1 F2F1 F2F1 F2F1"
	$"F2F1 F2F1 F2F1 F2F1 F2F1 F2F1 F2F1 F2F1"
	$"F2F1 F2F1 F2F1 F2F1 F2F1 F2F1 F2F1 F2F1"
	$"F2F1 F2F1 F2F1 F2F1 F2F1 F2F1 F2F1 F2F1"
	$"F2F1 F2F1 F2F1 F2F1 F2F1 F2F1 F2F1 5AF2"
	$"F1F2 F1F2 F1F2 F1F2 F1F2 F1F2 F1F2 F1F2"
	$"F1F2 F1F2 F1F2 F1F2 F1F2 F1F2 F1F2 F1F2"
	$"F1F2 F1F2 F1F2 F1F2 F1F2 F1F2 F1F2 F1F2"
	$"F1F2 F1F2 F1F2 F1F2 F1F1 F2F1 F2F1 F2F1"
	$"F2F1 F2F1 F2F1 F2F1 F2F1 F2F1 F2F1 F2F1"
	$"F2F1 F2F1 F2F1 F2F1 F2F1 FEF2 0299 8100"
	$"A000 02F0 F2F2 FAF1 147E 0098 ABA5 A3A0"
	$"9C95 8F7C 400E B1EE F1F1 F0F1 F1F0 FEF1"
	$"02F0 F1F0 FDF1 00F0 FEF1 02F0 F1F0 FEF1"
	$"00F0 FEF1 00F0 FEF1 00F0 FEF1 00F0 FEF1"
	$"00F0 FEF1 00F0 FEF1 00F0 FEF1 00F0 FEF1"
	$"00F0 FEF1 00F0 FEF1 00F0 FEF1 00F0 FEF1"
	$"00F0 FEF1 00F0 FEF1 00F0 FEF1 00F0 FEF1"
	$"00F0 FEF1 00F0 FEF1 00F0 FEF1 00F0 FEF1"
	$"00F0 FEF1 00F0 FEF1 00F0 FEF1 00F0 FEF1"
	$"00F0 FEF1 00F0 FEF1 00F0 FEF1 00F0 FEF1"
	$"00F0 FEF1 00F0 FEF1 00F0 FEF1 00F0 FEF1"
	$"00F0 FEF1 00F0 FEF1 03F0 F1F1 F0FE F100"
	$"F0FE F100 F0FE F100 F0FE F100 F0FE F100"
	$"F0FE F100 F0FE F100 F0FE F105 F2F2 F0F0"
	$"F2F2 FAF1 1493 3EBD CDCA C7C6 C2BE B9AB"
	$"8270 C1EE F1F1 F0F1 F1F0 FEF1 02F0 F1F0"
	$"FDF1 00F0 FEF1 02F0 F1F0 FEF1 00F0 FEF1"
	$"00F0 FEF1 00F0 FEF1 00F0 FEF1 00F0 FEF1"
	$"00F0 FEF1 00F0 FEF1 00F0 FEF1 00F0 FEF1"
	$"00F0 FEF1 00F0 FEF1 00F0 FEF1 00F0 FEF1"
	$"00F0 FEF1 00F0 FEF1 00F0 FEF1 00F0 FEF1"
	$"00F0 FEF1 00F0 FEF1 00F0 FEF1 00F0 FEF1"
	$"00F0 FEF1 00F0 FEF1 00F0 FEF1 00F0 FEF1"
	$"00F0 FEF1 00F0 FEF1 00F0 FEF1 00F0 FEF1"
	$"00F0 FEF1 00F0 FEF1 00F0 FEF1 00F0 FEF1"
	$"00F0 FEF1 03F0 F1F1 F0FE F100 F0FE F100"
	$"F0FE F100 F0FE F100 F0FE F100 F0FE F100"
	$"F0FE F100 F0FE F105 F2F2 F0F0 F2F2 FAF1"
	$"03AF B1E6 EAFE E90D E7E6 E4DE D0AC C4EE"
	$"F1F1 F0F1 F1F0 FEF1 02F0 F1F0 FDF1 00F0"
	$"FEF1 02F0 F1F0 FEF1 00F0 FEF1 00F0 FEF1"
	$"00F0 FEF1 00F0 FEF1 00F0 FEF1 00F0 FEF1"
	$"00F0 FEF1 00F0 FEF1 00F0 FEF1 00F0 FEF1"
	$"00F0 FEF1 00F0 FEF1 00F0 FEF1 00F0 FEF1"
	$"00F0 FEF1 00F0 FEF1 00F0 FEF1 00F0 FEF1"
	$"00F0 FEF1 00F0 FEF1 00F0 FEF1 00F0 FEF1"
	$"00F0 FEF1 00F0 FEF1 00F0 FEF1 00F0 FEF1"
	$"00F0 FEF1 00F0 FEF1 00F0 FEF1 00F0 FEF1"
	$"00F0 FEF1 00F0 FEF1 00F0 FEF1 00F0 FEF1"
	$"03F0 F1F1 F0FE F100 F0FE F100 F0FE F100"
	$"F0FE F100 F0FE F100 F0FE F100 F0FE F100"
	$"F0FE F102 F2F2 F002 8D81 00A0 0000 ECF8"
	$"EB13 351C 9A96 9995 8F84 7863 3D13 5CE9"
	$"EEEB ECEB EBEC FEEB 02EC EBEC FEEB 01EC"
	$"ECFE EB02 ECEB ECFE EB00 ECFE EB00 ECFE"
	$"EB00 ECFE EB00 ECFE EB00 ECFE EB00 ECFE"
	$"EB00 ECFE EB00 ECFE EB00 ECFE EB00 ECFE"
	$"EB00 ECFE EB00 ECFE EB00 ECFE EB00 ECFE"
	$"EB00 ECFE EB00 ECFE EB00 ECFE EB00 ECFE"
	$"EB00 ECFE EB00 ECFE EB00 ECFE EB00 ECFE"
	$"EB00 ECFE EB00 ECFE EB00 ECFE EB00 ECFE"
	$"EB00 ECFE EB00 ECFE EB00 ECFE EB00 ECFE"
	$"EB00 ECFE EB00 ECFE EB00 ECFE EB00 ECFE"
	$"EB03 ECEB EBEC FEEB 00EC FEEB 00EC FEEB"
	$"00EC FEEB 00EC FEEB 00EC FEEB 00EC FEEB"
	$"00EC FBEB 01EC ECF8 EB13 6876 C3C2 C1BE"
	$"B9B0 A397 7D6D 9AEA EEEB ECEB EBEC FEEB"
	$"02EC EBEC FEEB 01EC ECFE EB02 ECEB ECFE"
	$"EB00 ECFE EB00 ECFE EB00 ECFE EB00 ECFE"
	$"EB00 ECFE EB00 ECFE EB00 ECFE EB00 ECFE"
	$"EB00 ECFE EB00 ECFE EB00 ECFE EB00 ECFE"
	$"EB00 ECFE EB00 ECFE EB00 ECFE EB00 ECFE"
	$"EB00 ECFE EB00 ECFE EB00 ECFE EB00 ECFE"
	$"EB00 ECFE EB00 ECFE EB00 ECFE EB00 ECFE"
	$"EB00 ECFE EB00 ECFE EB00 ECFE EB00 ECFE"
	$"EB00 ECFE EB00 ECFE EB00 ECFE EB00 ECFE"
	$"EB00 ECFE EB00 ECFE EB03 ECEB EBEC FEEB"
	$"00EC FEEB 00EC FEEB 00EC FEEB 00EC FEEB"
	$"00EC FEEB 00EC FEEB 00EC FBEB 01EC ECF8"
	$"EB13 9DC7 EAE7 E8E7 E7E3 E1DD D3C3 B5EA"
	$"EEEB ECEB EBEC FEEB 02EC EBEC FEEB 01EC"
	$"ECFE EB02 ECEB ECFE EB00 ECFE EB00 ECFE"
	$"EB00 ECFE EB00 ECFE EB00 ECFE EB00 ECFE"
	$"EB00 ECFE EB00 ECFE EB00 ECFE EB00 ECFE"
	$"EB00 ECFE EB00 ECFE EB00 ECFE EB00 ECFE"
	$"EB00 ECFE EB00 ECFE EB00 ECFE EB00 ECFE"
	$"EB00 ECFE EB00 ECFE EB00 ECFE EB00 ECFE"
	$"EB00 ECFE EB00 ECFE EB00 ECFE EB00 ECFE"
	$"EB00 ECFE EB00 ECFE EB00 ECFE EB00 ECFE"
	$"EB00 ECFE EB00 ECFE EB00 ECFE EB00 ECFE"
	$"EB03 ECEB EBEC FEEB 00EC FEEB 00EC FEEB"
	$"00EC FEEB 00EC FEEB 00EC FEEB 00EC FEEB"
	$"00EC FBEB 00EC 028A 8100 A000 00EA FDEB"
	$"13EA EAEB EAEB 1F52 8D85 7359 4C43 423B"
	$"2B21 85F2 F1FB EB00 EAFC EB00 EAFD EB00"
	$"EAFC EB00 EAFE EB00 EAFE EB00 EAFE EB00"
	$"EAFE EB00 EAFE EB00 EAFE EB00 EAFE EB00"
	$"EAFE EB00 EAFE EB00 EAFE EB00 EAFE EB00"
	$"EAFE EB00 EAFE EB00 EAFE EB00 EAFE EB00"
	$"EAFE EB00 EAFE EB00 EAFE EB00 EAFE EB00"
	$"EAFE EB00 EAFE EB00 EAFE EB00 EAFE EB00"
	$"EAFE EB00 EAFE EB00 EAFE EB00 EAFE EB00"
	$"EAFE EB00 EAFE EB00 EAFE EB00 EAFE EB00"
	$"EAFE EB00 EAFE EB00 EAFE EB00 EAFE EB03"
	$"EAEB EBEA FEEB 00EA FEEB 00EA FEEB 00EA"
	$"FEEB 00EA FEEB 00EA FEEB 00EA FEEB 00EA"
	$"FDEB 01EA EAFD EB13 EAEA EBEA EB3C 95BD"
	$"B6A7 9084 7F7D 7C75 82AD F2F1 FBEB 00EA"
	$"FCEB 00EA FDEB 00EA FCEB 00EA FEEB 00EA"
	$"FEEB 00EA FEEB 00EA FEEB 00EA FEEB 00EA"
	$"FEEB 00EA FEEB 00EA FEEB 00EA FEEB 00EA"
	$"FEEB 00EA FEEB 00EA FEEB 00EA FEEB 00EA"
	$"FEEB 00EA FEEB 00EA FEEB 00EA FEEB 00EA"
	$"FEEB 00EA FEEB 00EA FEEB 00EA FEEB 00EA"
	$"FEEB 00EA FEEB 00EA FEEB 00EA FEEB 00EA"
	$"FEEB 00EA FEEB 00EA FEEB 00EA FEEB 00EA"
	$"FEEB 00EA FEEB 00EA FEEB 00EA FEEB 00EA"
	$"FEEB 00EA FEEB 03EA EBEB EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFD EB01 EAEA FDEB 13EA"
	$"EAEB EAEB 9ADB E9E9 E6DF DBDA D8D6 D3CB"
	$"BAF2 F1FB EB00 EAFC EB00 EAFD EB00 EAFC"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB03 EAEB"
	$"EBEA FEEB 00EA FEEB 00EA FEEB 00EA FEEB"
	$"00EA FEEB 00EA FEEB 00EA FEEB 00EA FDEB"
	$"00EA 0056 8100 A000 01EF EEF9 EF0E 1D58"
	$"7648 2F32 383E 4142 392B 82F0 F181 EFBB"
	$"EF03 EEEF EFEE F9EF 0E38 9AAB 8876 737B"
	$"8181 837E 85AB F0F1 81EF BBEF 03EE EFEF"
	$"EEF9 EF0E A7DF E9E3 DBDA DCDC DEDD D8D3"
	$"C0F0 F181 EFBB EF01 EEEF 028E 8100 A000"
	$"FCEE 00ED FDEE 1428 2228 1D2F 4045 4A4D"
	$"4D46 3858 D9EB EEEE EFEE EEEF FEEE 02EF"
	$"EEEF FDEE 00EF FEEE 02EF EEEF FEEE 00EF"
	$"FEEE 00EF FEEE 00EF FEEE 00EF FEEE 00EF"
	$"FEEE 00EF FEEE 00EF FEEE 00EF FEEE 00EF"
	$"FEEE 00EF FEEE 00EF FEEE 00EF FEEE 00EF"
	$"FEEE 00EF FEEE 00EF FEEE 00EF FEEE 00EF"
	$"FEEE 00EF FEEE 00EF FEEE 00EF FEEE 00EF"
	$"FEEE 00EF FEEE 00EF FEEE 00EF FEEE 00EF"
	$"FEEE 00EF FEEE 00EF FEEE 00EF FEEE 00EF"
	$"FEEE 00EF FEEE 00EF FEEE 00EF FEEE 00EF"
	$"FEEE 00EF FEEE 03EF EEEE EFFE EE00 EFFE"
	$"EE00 EFFE EE00 EFFE EE00 EFFE EE00 EFFE"
	$"EE00 EFFE EE01 EFED F7EE 00ED FDEE 144A"
	$"7574 727A 8288 8B8D 8E8A 8AA3 DCEB EEEE"
	$"EFEE EEEF FEEE 02EF EEEF FDEE 00EF FEEE"
	$"02EF EEEF FEEE 00EF FEEE 00EF FEEE 00EF"
	$"FEEE 00EF FEEE 00EF FEEE 00EF FEEE 00EF"
	$"FEEE 00EF FEEE 00EF FEEE 00EF FEEE 00EF"
	$"FEEE 00EF FEEE 00EF FEEE 00EF FEEE 00EF"
	$"FEEE 00EF FEEE 00EF FEEE 00EF FEEE 00EF"
	$"FEEE 00EF FEEE 00EF FEEE 00EF FEEE 00EF"
	$"FEEE 00EF FEEE 00EF FEEE 00EF FEEE 00EF"
	$"FEEE 00EF FEEE 00EF FEEE 00EF FEEE 00EF"
	$"FEEE 00EF FEEE 00EF FEEE 00EF FEEE 03EF"
	$"EEEE EFFE EE00 EFFE EE00 EFFE EE00 EFFE"
	$"EE00 EFFE EE00 EFFE EE00 EFFE EE01 EFED"
	$"F7EE 00ED FDEE 06B3 DADD DCE0 E2E3 FEE5"
	$"0AE1 D9CB DDEB EEEE EFEE EEEF FEEE 02EF"
	$"EEEF FDEE 00EF FEEE 02EF EEEF FEEE 00EF"
	$"FEEE 00EF FEEE 00EF FEEE 00EF FEEE 00EF"
	$"FEEE 00EF FEEE 00EF FEEE 00EF FEEE 00EF"
	$"FEEE 00EF FEEE 00EF FEEE 00EF FEEE 00EF"
	$"FEEE 00EF FEEE 00EF FEEE 00EF FEEE 00EF"
	$"FEEE 00EF FEEE 00EF FEEE 00EF FEEE 00EF"
	$"FEEE 00EF FEEE 00EF FEEE 00EF FEEE 00EF"
	$"FEEE 00EF FEEE 00EF FEEE 00EF FEEE 00EF"
	$"FEEE 00EF FEEE 00EF FEEE 00EF FEEE 00EF"
	$"FEEE 00EF FEEE 03EF EEEE EFFE EE00 EFFE"
	$"EE00 EFFE EE00 EFFE EE00 EFFE EE00 EFFE"
	$"EE00 EFFE EE01 EFED FCEE 0070 8100 D200"
	$"00FF D000 FDE8 01E9 E9FD E80E 4F00 142E"
	$"4250 565B 5E5C 564C 4391 E281 E8EB E800"
	$"FFD6 E801 E9E9 F9E8 01E9 E9FD E80E 765F"
	$"7A88 8C92 9698 9A9B 989A 9BB7 E581 E8EB"
	$"E800 FFD6 E801 E9E9 F9E8 01E9 E9FD E805"
	$"B0D3 DCE4 E7EA FEEC 05EA E8E1 D7D0 E781"
	$"E8EB E800 FFD6 E801 E9E9 FDE8 0291 8100"
	$"A000 FCE7 00E8 FDE7 06A1 0728 4355 6168"
	$"FE6C 0968 6057 437B E7E8 E7E7 E8FE E702"
	$"E8E7 E8FE E701 E8E8 FEE7 02E8 E7E8 FEE7"
	$"00E8 FEE7 00E8 FEE7 00E8 FEE7 00E8 FEE7"
	$"00E8 FEE7 00E8 FEE7 00E8 FEE7 00E8 FEE7"
	$"00E8 FEE7 00E8 FEE7 00E8 FEE7 00E8 FEE7"
	$"00E8 FEE7 00E8 FEE7 00E8 FEE7 00E8 FEE7"
	$"00E8 FEE7 00E8 FEE7 00E8 FEE7 00E8 FEE7"
	$"00E8 FEE7 00E8 FEE7 00E8 FEE7 00E8 FEE7"
	$"00E8 FEE7 00E8 FEE7 00E8 FEE7 00E8 FEE7"
	$"00E8 FEE7 00E8 FEE7 00E8 FEE7 00E8 FEE7"
	$"00E8 FEE7 00E8 FEE7 03E8 E7E7 E8FE E700"
	$"E8FE E700 E8FE E700 E8FE E700 E8FE E700"
	$"E8FE E700 E8FE E702 E8E7 E8F7 E700 E8FD"
	$"E713 AE69 899A 9FA3 A3A5 A7A9 AAAC A799"
	$"AAE7 E8E7 E7E8 FEE7 02E8 E7E8 FEE7 01E8"
	$"E8FE E702 E8E7 E8FE E700 E8FE E700 E8FE"
	$"E700 E8FE E700 E8FE E700 E8FE E700 E8FE"
	$"E700 E8FE E700 E8FE E700 E8FE E700 E8FE"
	$"E700 E8FE E700 E8FE E700 E8FE E700 E8FE"
	$"E700 E8FE E700 E8FE E700 E8FE E700 E8FE"
	$"E700 E8FE E700 E8FE E700 E8FE E700 E8FE"
	$"E700 E8FE E700 E8FE E700 E8FE E700 E8FE"
	$"E700 E8FE E700 E8FE E700 E8FE E700 E8FE"
	$"E700 E8FE E700 E8FE E700 E8FE E700 E8FE"
	$"E703 E8E7 E7E8 FEE7 00E8 FEE7 00E8 FEE7"
	$"00E8 FEE7 00E8 FEE7 00E8 FEE7 00E8 FEE7"
	$"02E8 E7E8 F7E7 00E8 FDE7 13B6 C1DD ECF2"
	$"F2F3 F3F4 F4F1 EDE5 D5D3 E7E8 E7E7 E8FE"
	$"E702 E8E7 E8FE E701 E8E8 FEE7 02E8 E7E8"
	$"FEE7 00E8 FEE7 00E8 FEE7 00E8 FEE7 00E8"
	$"FEE7 00E8 FEE7 00E8 FEE7 00E8 FEE7 00E8"
	$"FEE7 00E8 FEE7 00E8 FEE7 00E8 FEE7 00E8"
	$"FEE7 00E8 FEE7 00E8 FEE7 00E8 FEE7 00E8"
	$"FEE7 00E8 FEE7 00E8 FEE7 00E8 FEE7 00E8"
	$"FEE7 00E8 FEE7 00E8 FEE7 00E8 FEE7 00E8"
	$"FEE7 00E8 FEE7 00E8 FEE7 00E8 FEE7 00E8"
	$"FEE7 00E8 FEE7 00E8 FEE7 00E8 FEE7 00E8"
	$"FEE7 00E8 FEE7 00E8 FEE7 03E8 E7E7 E8FE"
	$"E700 E8FE E700 E8FE E700 E8FE E700 E8FE"
	$"E700 E8FE E700 E8FE E702 E8E7 E8FC E702"
	$"8D81 00A0 0003 EAEC EBEC FEEB 15EA EBEA"
	$"E042 3C55 656F 7578 7778 7672 6548 61EA"
	$"EBEB EAFE EB00 EAFC EB00 EAFD EB00 EAFC"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFB EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFD EB07 ECEB ECEA EAEC"
	$"EBEC FEEB 15EA EBEA E17A 96A8 B1B1 B2B2"
	$"B4B9 BABD B395 90EA EBEB EAFE EB00 EAFC"
	$"EB00 EAFD EB00 EAFC EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFB EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFD"
	$"EB07 ECEB ECEA EAEC EBEC FEEB 09EA EBEA"
	$"E198 DEF0 F9FC FDFE FC08 F8F7 EAD5 B9EA"
	$"EBEB EAFE EB00 EAFC EB00 EAFD EB00 EAFC"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFB EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFD EB03 ECEB ECEA 0042"
	$"8100 A000 F7EA 0EE8 993C 6372 797D 7D7E"
	$"8080 7C72 46AA 81EA AFEA 0EE8 A88E B1BD"
	$"C0C1 BEC3 C5C6 C1B1 89BC 81EA AFEA 06E8"
	$"ADBF EEFC FEFF FEFE 04FD F8E9 C3CC 81EA"
	$"B9EA 0296 8100 A000 02EE EEEF FEEE 15EF"
	$"EEEF EEE8 E068 5976 7E7E 7273 7D81 8C72"
	$"6CE5 EEEE EFFE EE00 EFFE EE00 EFFE EE00"
	$"EFFE EE00 EFFE EE00 EFFE EE00 EFFE EE00"
	$"EFFE EE00 EFFE EE00 EFFE EE00 EFFE EE00"
	$"EFFE EE00 EFFE EE00 EFFE EE00 EFFE EE00"
	$"EFFE EE00 EFFE EE00 EFFE EE00 EFFE EE00"
	$"EFFE EE00 EFFE EE00 EFFE EE00 EFFE EE00"
	$"EFFE EE00 EFFE EE00 EFFE EE00 EFFE EE00"
	$"EFFE EE00 EFFE EE00 EFFE EE00 EFFE EE00"
	$"EFFE EE00 EFFE EE03 EFEE EEEF FEEE 00EF"
	$"FEEE 00EF FEEE 00EF FEEE 00EF FEEE 00EF"
	$"FEEE 00EF FEEE 01EF EDFB EE02 EFEE EFFE"
	$"EE00 EFFE EE00 EFFE EE00 EFFE EE01 EFED"
	$"FBEE 03EF EEEE EFFE EE15 EFEE EFEE E8E1"
	$"8BA1 C0C4 C0B3 B6BE C3C3 AA90 E6EE EEEF"
	$"FEEE 00EF FEEE 00EF FEEE 00EF FEEE 00EF"
	$"FEEE 00EF FEEE 00EF FEEE 00EF FEEE 00EF"
	$"FEEE 00EF FEEE 00EF FEEE 00EF FEEE 00EF"
	$"FEEE 00EF FEEE 00EF FEEE 00EF FEEE 00EF"
	$"FEEE 00EF FEEE 00EF FEEE 00EF FEEE 00EF"
	$"FEEE 00EF FEEE 00EF FEEE 00EF FEEE 00EF"
	$"FEEE 00EF FEEE 00EF FEEE 00EF FEEE 00EF"
	$"FEEE 00EF FEEE 00EF FEEE 00EF FEEE 00EF"
	$"FEEE 03EF EEEE EFFE EE00 EFFE EE00 EFFE"
	$"EE00 EFFE EE00 EFFE EE00 EFFE EE00 EFFE"
	$"EE01 EFED FBEE 02EF EEEF FEEE 00EF FEEE"
	$"00EF FEEE 00EF FEEE 01EF EDFB EE03 EFEE"
	$"EEEF FEEE 15EF EEEF EEE8 E19D D0F6 FCF8"
	$"EFEE F6F8 F6D8 ADE6 EEEE EFFE EE00 EFFE"
	$"EE00 EFFE EE00 EFFE EE00 EFFE EE00 EFFE"
	$"EE00 EFFE EE00 EFFE EE00 EFFE EE00 EFFE"
	$"EE00 EFFE EE00 EFFE EE00 EFFE EE00 EFFE"
	$"EE00 EFFE EE00 EFFE EE00 EFFE EE00 EFFE"
	$"EE00 EFFE EE00 EFFE EE00 EFFE EE00 EFFE"
	$"EE00 EFFE EE00 EFFE EE00 EFFE EE00 EFFE"
	$"EE00 EFFE EE00 EFFE EE00 EFFE EE00 EFFE"
	$"EE00 EFFE EE00 EFFE EE00 EFFE EE03 EFEE"
	$"EEEF FEEE 00EF FEEE 00EF FEEE 00EF FEEE"
	$"00EF FEEE 00EF FEEE 00EF FEEE 01EF EDFB"
	$"EE02 EFEE EFFE EE00 EFFE EE00 EFFE EE00"
	$"EFFE EE01 EFED FBEE 00EF 0068 F700 00FF"
	$"F400 00FF 8100 B900 F7E8 0EE7 EBD5 5C4A"
	$"5248 5A5E 566F 6B6B DAE7 81E8 DBE8 01E9"
	$"E9E9 E801 E9E9 F1E8 0EE7 EBD8 828A 9484"
	$"8386 88A4 9C8C DEE7 81E8 DBE8 01E9 E9E9"
	$"E801 E9E9 F1E8 0EE7 EBD8 91AE BBA6 9899"
	$"AAC8 BB9E E2E7 81E8 DBE8 01E9 E9E9 E801"
	$"E9E9 FBE8 02A3 F700 01FF FFF6 0001 FFFF"
	$"8100 B900 01E7 E8FE E702 E8E7 E8FD E70A"
	$"EADB 998C C1E7 EACB 9BA7 DFFE E700 E8FE"
	$"E700 E8FE E700 E8FE E700 E8FE E700 E8FE"
	$"E700 E8FE E700 E8FE E700 E8FE E700 E8FE"
	$"E700 E8FE E700 E8FE E700 E8FE E700 E8FE"
	$"E700 E8FE E700 E8FE E700 E8FE E700 E8FE"
	$"E700 E8FE E700 E8FE E700 E8FE E700 E8FE"
	$"E700 E8FE E700 E8FE E700 E8FE E700 E8FE"
	$"E700 E8FE E700 E8FE E700 E8FE E700 E8FE"
	$"E700 E8FE E700 E8FE E700 E8FE E700 E8FE"
	$"E703 E8E7 E7E8 FEE7 00E8 FEE7 00E8 FEE7"
	$"00E8 FEE7 00E8 FEE7 00E8 FEE7 00E8 FEE7"
	$"02E8 E7E8 FCE7 02E8 E7E8 FEE7 00E8 FEE7"
	$"00E8 FEE7 00E8 FEE7 02E8 E7E8 FCE7 03E8"
	$"E7E7 E8FE E702 E8E7 E8FD E70A EADD AEA7"
	$"C7E7 EACE B1B7 E1FE E700 E8FE E700 E8FE"
	$"E700 E8FE E700 E8FE E700 E8FE E700 E8FE"
	$"E700 E8FE E700 E8FE E700 E8FE E700 E8FE"
	$"E700 E8FE E700 E8FE E700 E8FE E700 E8FE"
	$"E700 E8FE E700 E8FE E700 E8FE E700 E8FE"
	$"E700 E8FE E700 E8FE E700 E8FE E700 E8FE"
	$"E700 E8FE E700 E8FE E700 E8FE E700 E8FE"
	$"E700 E8FE E700 E8FE E700 E8FE E700 E8FE"
	$"E700 E8FE E700 E8FE E700 E8FE E703 E8E7"
	$"E7E8 FEE7 00E8 FEE7 00E8 FEE7 00E8 FEE7"
	$"00E8 FEE7 00E8 FEE7 00E8 FEE7 02E8 E7E8"
	$"FCE7 02E8 E7E8 FEE7 00E8 FEE7 00E8 FEE7"
	$"00E8 FEE7 02E8 E7E8 FCE7 03E8 E7E7 E8FE"
	$"E702 E8E7 E8FD E70A EADC B6B1 CAE7 EAD0"
	$"B8BB E2FE E700 E8FE E700 E8FE E700 E8FE"
	$"E700 E8FE E700 E8FE E700 E8FE E700 E8FE"
	$"E700 E8FE E700 E8FE E700 E8FE E700 E8FE"
	$"E700 E8FE E700 E8FE E700 E8FE E700 E8FE"
	$"E700 E8FE E700 E8FE E700 E8FE E700 E8FE"
	$"E700 E8FE E700 E8FE E700 E8FE E700 E8FE"
	$"E700 E8FE E700 E8FE E700 E8FE E700 E8FE"
	$"E700 E8FE E700 E8FE E700 E8FE E700 E8FE"
	$"E700 E8FE E700 E8FE E703 E8E7 E7E8 FEE7"
	$"00E8 FEE7 00E8 FEE7 00E8 FEE7 00E8 FEE7"
	$"00E8 FEE7 00E8 FEE7 02E8 E7E8 FCE7 02E8"
	$"E7E8 FEE7 00E8 FEE7 00E8 FEE7 00E8 FEE7"
	$"02E8 E7E8 FCE7 01E8 E702 8481 00A0 0000"
	$"EAFE EB00 EAFC EB00 EAFD EB00 EAFC EB00"
	$"EAFE EB00 EAFE EB00 EAFE EB00 EAFE EB00"
	$"EAFE EB00 EAFE EB00 EAFE EB00 EAFE EB00"
	$"EAFE EB00 EAFE EB00 EAFE EB00 EAFE EB00"
	$"EAFE EB00 EAFE EB00 EAFE EB00 EAFE EB00"
	$"EAFE EB00 EAFE EB00 EAFE EB00 EAFE EB00"
	$"EAFE EB00 EAFE EB00 EAFE EB00 EAFE EB00"
	$"EAFE EB00 EAFE EB00 EAFE EB00 EAFE EB00"
	$"EAFE EB00 EAFE EB00 EAFE EB00 EAFE EB00"
	$"EAFE EB00 EAFE EB00 EAFB EB00 EAFE EB00"
	$"EAFE EB00 EAFE EB00 EAFE EB00 EAFE EB00"
	$"EAFE EB00 EAFD EB03 ECEB ECEA FCEB 00EA"
	$"FEEB 00EA FEEB 00EA FEEB 00EA FDEB 06EC"
	$"EBEC EAEB EBEA FEEB 00EA FCEB 00EA FDEB"
	$"00EA FCEB 00EA FEEB 00EA FEEB 00EA FEEB"
	$"00EA FEEB 00EA FEEB 00EA FEEB 00EA FEEB"
	$"00EA FEEB 00EA FEEB 00EA FEEB 00EA FEEB"
	$"00EA FEEB 00EA FEEB 00EA FEEB 00EA FEEB"
	$"00EA FEEB 00EA FEEB 00EA FEEB 00EA FEEB"
	$"00EA FEEB 00EA FEEB 00EA FEEB 00EA FEEB"
	$"00EA FEEB 00EA FEEB 00EA FEEB 00EA FEEB"
	$"00EA FEEB 00EA FEEB 00EA FEEB 00EA FEEB"
	$"00EA FEEB 00EA FEEB 00EA FEEB 00EA FBEB"
	$"00EA FEEB 00EA FEEB 00EA FEEB 00EA FEEB"
	$"00EA FEEB 00EA FEEB 00EA FDEB 03EC EBEC"
	$"EAFC EB00 EAFE EB00 EAFE EB00 EAFE EB00"
	$"EAFD EB06 ECEB ECEA EBEB EAFE EB00 EAFC"
	$"EB00 EAFD EB00 EAFC EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFB EB00 EAFE EB00 EAFE EB00 EAFE"
	$"EB00 EAFE EB00 EAFE EB00 EAFE EB00 EAFD"
	$"EB03 ECEB ECEA FCEB 00EA FEEB 00EA FEEB"
	$"00EA FEEB 00EA FDEB 05EC EBEC EAEB EB00"
	$"1081 00A0 0081 EA81 EA81 EA81 EA81 EADE"
	$"EA02 8081 00A0 0000 E4FE E500 E4FC E500"
	$"E4FD E500 E4FC E500 E4FE E500 E4FE E500"
	$"E4FE E500 E4FE E500 E4FE E500 E4FE E500"
	$"E4FE E500 E4FE E500 E4FE E500 E4FE E500"
	$"E4FE E500 E4FE E500 E4FE E500 E4FE E500"
	$"E4FE E500 E4FE E500 E4FE E500 E4FE E500"
	$"E4FE E500 E4FE E500 E4FE E500 E4FE E500"
	$"E4FE E500 E4FE E500 E4FE E500 E4FE E500"
	$"E4FE E500 E4FE E500 E4FE E500 E4FE E500"
	$"E4FE E500 E4FE E500 E4FE E500 E4FE E500"
	$"E4FB E500 E4FE E500 E4FE E500 E4FE E500"
	$"E4FE E500 E4FE E500 E4FE E500 E4FD E502"
	$"E3E4 E4FB E500 E4FE E500 E4FE E500 E4FE"
	$"E500 E4FD E502 E3E4 E4FE E500 E4FE E500"
	$"E4FC E500 E4FD E500 E4FC E500 E4FE E500"
	$"E4FE E500 E4FE E500 E4FE E500 E4FE E500"
	$"E4FE E500 E4FE E500 E4FE E500 E4FE E500"
	$"E4FE E500 E4FE E500 E4FE E500 E4FE E500"
	$"E4FE E500 E4FE E500 E4FE E500 E4FE E500"
	$"E4FE E500 E4FE E500 E4FE E500 E4FE E500"
	$"E4FE E500 E4FE E500 E4FE E500 E4FE E500"
	$"E4FE E500 E4FE E500 E4FE E500 E4FE E500"
	$"E4FE E500 E4FE E500 E4FE E500 E4FE E500"
	$"E4FE E500 E4FB E500 E4FE E500 E4FE E500"
	$"E4FE E500 E4FE E500 E4FE E500 E4FE E500"
	$"E4FD E502 E3E4 E4FB E500 E4FE E500 E4FE"
	$"E500 E4FE E500 E4FD E502 E3E4 E4FE E500"
	$"E4FE E500 E4FC E500 E4FD E500 E4FC E500"
	$"E4FE E500 E4FE E500 E4FE E500 E4FE E500"
	$"E4FE E500 E4FE E500 E4FE E500 E4FE E500"
	$"E4FE E500 E4FE E500 E4FE E500 E4FE E500"
	$"E4FE E500 E4FE E500 E4FE E500 E4FE E500"
	$"E4FE E500 E4FE E500 E4FE E500 E4FE E500"
	$"E4FE E500 E4FE E500 E4FE E500 E4FE E500"
	$"E4FE E500 E4FE E500 E4FE E500 E4FE E500"
	$"E4FE E500 E4FE E500 E4FE E500 E4FE E500"
	$"E4FE E500 E4FE E500 E4FB E500 E4FE E500"
	$"E4FE E500 E4FE E500 E4FE E500 E4FE E500"
	$"E4FE E500 E4FD E502 E3E4 E4FB E500 E4FE"
	$"E500 E4FE E500 E4FE E500 E4FD E502 E3E4"
	$"E4FE E502 9781 00A0 0002 ABAB ACFE AB00"
	$"ACFE AB00 ACFE AB00 ACFC AB00 ACFE AB00"
	$"ACFE AB00 ACFE AB00 ACFE AB00 ACFE AB00"
	$"ACFE AB00 ACFE AB00 ACFE AB00 ACFE AB00"
	$"ACFE AB00 ACFE AB00 ACFE AB00 ACFE AB00"
	$"ACFE AB00 ACFE AB00 ACFE AB00 ACFE AB00"
	$"ACFE AB00 ACFE AB00 ACFE AB00 ACFE AB00"
	$"ACFE AB00 ACFE AB00 ACFE AB00 ACFE AB00"
	$"ACFE AB00 ACFE AB00 ACFE AB00 ACFE AB00"
	$"ACFE AB00 ACFE AB00 ACFE AB00 ACFE AB00"
	$"ACFE AB00 ACFE AB03 ACAB ABAC FEAB 00AC"
	$"FEAB 00AC FEAB 00AC FEAB 00AC FEAB 00AC"
	$"FEAB 00AC FEAB 00AA FEAB 00AC FCAB 00AC"
	$"FEAB 00AC FEAB 00AC FEAB 00AC FEAB 00AA"
	$"FEAB 00AC FCAB 00AC FEAB 00AC FEAB 00AC"
	$"FEAB 00AC FCAB 00AC FEAB 00AC FEAB 00AC"
	$"FEAB 00AC FEAB 00AC FEAB 00AC FEAB 00AC"
	$"FEAB 00AC FEAB 00AC FEAB 00AC FEAB 00AC"
	$"FEAB 00AC FEAB 00AC FEAB 00AC FEAB 00AC"
	$"FEAB 00AC FEAB 00AC FEAB 00AC FEAB 00AC"
	$"FEAB 00AC FEAB 00AC FEAB 00AC FEAB 00AC"
	$"FEAB 00AC FEAB 00AC FEAB 00AC FEAB 00AC"
	$"FEAB 00AC FEAB 00AC FEAB 00AC FEAB 00AC"
	$"FEAB 00AC FEAB 00AC FEAB 00AC FEAB 00AC"
	$"FEAB 03AC ABAB ACFE AB00 ACFE AB00 ACFE"
	$"AB00 ACFE AB00 ACFE AB00 ACFE AB00 ACFE"
	$"AB00 AAFE AB00 ACFC AB00 ACFE AB00 ACFE"
	$"AB00 ACFE AB00 ACFE AB00 AAFE AB00 ACFC"
	$"AB00 ACFE AB00 ACFE AB00 ACFE AB00 ACFC"
	$"AB00 ACFE AB00 ACFE AB00 ACFE AB00 ACFE"
	$"AB00 ACFE AB00 ACFE AB00 ACFE AB00 ACFE"
	$"AB00 ACFE AB00 ACFE AB00 ACFE AB00 ACFE"
	$"AB00 ACFE AB00 ACFE AB00 ACFE AB00 ACFE"
	$"AB00 ACFE AB00 ACFE AB00 ACFE AB00 ACFE"
	$"AB00 ACFE AB00 ACFE AB00 ACFE AB00 ACFE"
	$"AB00 ACFE AB00 ACFE AB00 ACFE AB00 ACFE"
	$"AB00 ACFE AB00 ACFE AB00 ACFE AB00 ACFE"
	$"AB00 ACFE AB00 ACFE AB00 ACFE AB03 ACAB"
	$"ABAC FEAB 00AC FEAB 00AC FEAB 00AC FEAB"
	$"00AC FEAB 00AC FEAB 00AC FEAB 00AA FEAB"
	$"00AC FCAB 00AC FEAB 00AC FEAB 00AC FEAB"
	$"00AC FEAB 00AA FEAB 00AC FEAB 0265 8100"
	$"A000 FE2E 1530 2E2E 2F2F 2E2E 302E 2F2E"
	$"302F 302E 302F 2F2E 302E 2FFE 3004 2F2E"
	$"2E2F 30FE 2E05 302F 302F 302E FE30 002F"
	$"FD2E 0530 2F30 2F30 2EFE 3005 2F2E 3030"
	$"2F2F F930 062E 2F30 3031 2F2E FC30 052F"
	$"2E2E 2F2E 2FFE 3000 31FE 3012 2F32 302F"
	$"3130 2E31 302F 2F30 2E30 302F 3030 2FFB"
	$"3003 3230 3031 FE2F FD30 012F 2FFD 3004"
	$"3232 3130 2FF3 3019 2F30 2E2E 2F2F 2E2E"
	$"302E 2F2E 302F 302E 302F 2F2E 302C 2C2B"
	$"2B2C FB2B 012C 2BFE 290E 2B30 2E30 2E30"
	$"2F2F 2E30 2C2C 2B2B 2CFB 2B01 2C2B FE29"
	$"102B 302E 5756 5758 5757 5858 5656 5857"
	$"5857 FE58 0057 FE58 0257 5957 FE58 0859"
	$"5857 5758 5957 5657 FD58 0959 5758 5859"
	$"5857 5756 57FD 580C 5957 5858 5958 5759"
	$"5958 5859 59FD 582C 5958 5658 5859 5A58"
	$"5758 5959 5A59 5857 5758 5758 5859 595A"
	$"5A59 5958 5A59 585A 5957 5A59 5858 5957"
	$"5859 5859 59FB 5804 595B 5A59 5AFC 5803"
	$"5959 5858 FE59 065A 5A5B 5A59 5859 FD58"
	$"1459 5A58 5959 5A58 5958 5859 5757 5858"
	$"5656 5857 5857 FE58 0057 FE58 0657 5955"
	$"5554 5455 FC54 0253 5553 FE52 0454 5957"
	$"5857 FE58 0657 5955 5554 5455 FC54 0253"
	$"5553 FE52 0254 5957 FE78 0A79 7878 7979"
	$"7878 7978 7978 FE79 0078 FE79 0278 7A78"
	$"FC79 0378 7879 79FE 78FD 7901 7A78 FD79"
	$"FD78 FD79 017A 78FD 791D 787A 7A79 787A"
	$"7A79 7A79 797A 7978 7979 787A 7978 797A"
	$"7979 7879 7878 7978 FD79 007A FE79 1278"
	$"7B7A 797B 7A78 7B7A 7979 7A78 797A 7879"
	$"7978 FD79 067A 797A 7A79 7A78 FB79 0178"
	$"78FD 7905 7A7A 797A 797A FC79 0278 797A"
	$"FE79 007A FE79 0978 7879 7978 7879 7879"
	$"78FE 7900 78FE 7906 787A 7878 7777 78FC"
	$"7702 7678 76FE 7504 767A 7879 78FE 7906"
	$"787A 7878 7777 78FC 7702 7678 76FE 7502"
	$"767A 7800 00FF"
};

data 'PPob' (1000, "Rez Map Window") {
	$"0002 646F 706C 527A 4D57 6F62 6A64 0000"            /* ..doplRzMWobjd.. */
	$"001C 7769 6E64 03E8 0002 3F66 0000 012C"            /* ..wind.Ë..?f..., */
	$"00C8 FFFF FFFF FFFF FFFF 0000 0000 6265"            /* .»ˇˇˇˇˇˇˇˇ....be */
	$"6773 6F62 6A64 0000 0012 7774 6861 FFFF"            /* gsobjd....wthaˇˇ */
	$"FFFE 0101 0001 0002 0001 0002 6F62 6A64"            /* ˇ˛..........objd */
	$"0000 0049 7363 6C76 5343 524C 0160 0210"            /* ...IsclvSCRL.`.. */
	$"0101 0101 0101 0000 0000 0000 0016 0000"            /* ................ */
	$"0000 FFFF FFFF 0000 0001 0000 0001 0000"            /* ..ˇˇˇˇ.......... */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"FFFF 000F 0000 000F 5441 424C 0162 6567"            /* ˇˇ......TABL.beg */
	$"7364 6F70 6C52 7A4D 546F 626A 6400 0000"            /* sdoplRzMTobjd... */
	$"406F 7461 6254 4142 4C01 4F01 F701 0101"            /* @otabTABL.O.˜... */
	$"0101 0100 0000 0100 0000 0100 0000 00FF"            /* ...............ˇ */
	$"FFFF FF00 0000 0000 0000 0000 0000 0000"            /* ˇˇˇ............. */
	$"0000 0000 0000 0100 0000 0100 0000 8200"            /* ..............Ç. */
	$"2065 6E64 736F 626A 6400 0000 5177 696E"            /*  endsobjd...Qwin */
	$"6800 0000 0001 6400 1601 0101 0101 00FF"            /* h.....d........ˇ */
	$"FFFF FD00 0000 0000 0000 00FF FFFF FF00"            /* ˇˇ˝........ˇˇˇˇ. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0100 0000 0100 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0001 5000 0000 6265"            /* ..........P...be */
	$"6773 6F62 6A64 0000 0029 6361 7074 0000"            /* gsobjd...)capt.. */
	$"0000 0028 0010 0101 0000 0000 0000 0020"            /* ...(...........  */
	$"0000 0003 0000 0000 FFFF FFFF 0454 7970"            /* ........ˇˇˇˇ.Typ */
	$"6500 8C6F 626A 6400 0000 2963 6170 7400"            /* e.åobjd...)capt. */
	$"0000 0000 2800 1001 0100 0000 0000 0000"            /* ....(........... */
	$"6900 0000 0300 0000 00FF FFFF FF04 5369"            /* i........ˇˇˇˇ.Si */
	$"7A65 008C 6F62 6A64 0000 0029 6361 7074"            /* ze.åobjd...)capt */
	$"0000 0000 0028 0010 0101 0000 0000 0000"            /* .....(.......... */
	$"00CD 0000 0003 0000 0000 FFFF FFFF 044E"            /* .Õ........ˇˇˇˇ.N */
	$"616D 6500 8C65 6E64 736F 626A 6400 0000"            /* ame.åendsobjd... */
	$"5177 696E 6800 0000 0001 5300 1901 0101"            /* Qwinh.....S..... */
	$"0001 01FF FFFF FD00 0002 0E00 0000 00FF"            /* ...ˇˇˇ˝........ˇ */
	$"FFFF FF00 0000 0000 0000 0000 0000 0000"            /* ˇˇˇ............. */
	$"0000 0000 0000 0100 0000 0100 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0001 5000"            /* ..............P. */
	$"0000 6265 6773 6F62 6A64 0000 0051 7467"            /* ..begsobjd...Qtg */
	$"6278 0000 0000 0130 0010 0101 0101 0101"            /* bx.....0........ */
	$"0000 0018 0000 0004 0000 0000 FFFF FFFF"            /* ............ˇˇˇˇ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0001 0000 0001 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 00A4 0000 0062"            /* ...........§...b */
	$"6567 736F 626A 6400 0000 4173 7478 7400"            /* egsobjd...Astxt. */
	$"0000 0000 4600 0E01 0100 0000 0000 0000"            /* ....F........... */
	$"6200 0000 0200 0000 00FF FFFF FF00 0000"            /* b........ˇˇˇˇ... */
	$"0000 0000 0000 0000 0000 0000 0001 2000"            /* .............. . */
	$"850A 5265 736F 7572 6365 733A 6F62 6A64"            /* Ö¬Resources:objd */
	$"0000 0039 7374 7874 0000 0003 0014 000E"            /* ...9stxt........ */
	$"0101 0000 0000 0000 00DC 0000 0002 0000"            /* .........‹...... */
	$"0000 FFFF FFFF 0000 0000 0000 0000 0000"            /* ..ˇˇˇˇ.......... */
	$"0000 0000 0000 0120 0085 0252 466F 626A"            /* ....... .Ö.RFobj */
	$"6400 0000 3773 7478 7400 0000 0200 2D00"            /* d...7stxt.....-. */
	$"0E01 0100 0000 0000 0000 A800 0000 0200"            /* ..........®..... */
	$"0000 00FF FFFF FF00 0000 0000 0000 0000"            /* ...ˇˇˇˇ......... */
	$"0000 0000 0000 0001 2000 8500 6F62 6A64"            /* ........ .Ö.objd */
	$"0000 003D 7374 7874 0000 0000 002B 000E"            /* ...=stxt.....+.. */
	$"0101 0000 0000 0000 0008 0000 0002 0000"            /* ................ */
	$"0000 FFFF FFFF 0000 0000 0000 0000 0000"            /* ..ˇˇˇˇ.......... */
	$"0000 0000 0000 0120 0085 0654 7970 6573"            /* ....... .Ö.Types */
	$"3A6F 626A 6400 0000 3773 7478 7400 0000"            /* :objd...7stxt... */
	$"0100 2400 0E01 0100 0000 0000 0000 3400"            /* ..$...........4. */
	$"0000 0200 0000 00FF FFFF FF00 0000 0000"            /* .......ˇˇˇˇ..... */
	$"0000 0000 0000 0000 0000 0001 2000 8500"            /* ............ .Ö. */
	$"656E 6473 6F62 6A64 0000 0024 6963 6E70"            /* endsobjd...$icnp */
	$"4C6F 636B 0010 0010 0101 0101 0000 0000"            /* Lock............ */
	$"0004 0000 0004 0000 0000 FFFF FFFF 0000"            /* ..........ˇˇˇˇ.. */
	$"656E 6473 656E 6473 656E 642E"                      /* endsendsend. */
};

data 'PPob' (2000, "Inspector Window") {
	$"0002 646F 706C 496E 7357 6F62 6A64 0000"            /* ..doplInsWobjd.. */
	$"001C 7769 6E64 07D0 0002 1862 0000 FFFF"            /* ..wind.–...b..ˇˇ */
	$"FFFF FFFF FFFF FFFF FFFF 0000 0000 6265"            /* ˇˇˇˇˇˇˇˇˇˇ....be */
	$"6773 6F62 6A64 0000 0012 7774 6861 FFFF"            /* gsobjd....wthaˇˇ */
	$"FFFE 0101 0003 0004 0005 0006 6F62 6A64"            /* ˇ˛..........objd */
	$"0000 005B 7467 6278 0000 0000 00FB 0053"            /* ...[tgbx.....˚.S */
	$"0101 0000 0000 0000 001C 0000 008A 0000"            /* .............ä.. */
	$"0000 FFFF FFFF 0000 0000 0000 0000 0000"            /* ..ˇˇˇˇ.......... */
	$"0000 0000 0000 0000 0001 0000 0001 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"00A4 0085 0A41 7474 7269 6275 7465 7362"            /* .§.Ö¬Attributesb */
	$"6567 736F 626A 6400 0000 3763 6862 7800"            /* egsobjd...7chbx. */
	$"0000 0B00 1600 1301 0100 0000 0000 0000"            /* ................ */
	$"5D00 0000 1300 0000 00FF FFFF FF00 0007"            /* ]........ˇˇˇˇ... */
	$"DB00 0000 0000 0000 0000 0000 0201 7100"            /* €.............q. */
	$"8200 6F62 6A64 0000 0037 6368 6278 0000"            /* Ç.objd...7chbx.. */
	$"000C 0016 0013 0101 0000 0000 0000 005D"            /* ...............] */
	$"0000 0026 0000 0000 FFFF FFFF 0000 07DC"            /* ...&....ˇˇˇˇ...‹ */
	$"0000 0000 0000 0000 0000 0002 0171 0082"            /* .............q.Ç */
	$"006F 626A 6400 0000 3763 6862 7800 0000"            /* .objd...7chbx... */
	$"0D00 1600 1301 0100 0000 0000 0000 5D00"            /* ..............]. */
	$"0000 3900 0000 00FF FFFF FF00 0007 DD00"            /* ..9....ˇˇˇˇ...›. */
	$"0000 0000 0000 0000 0000 0201 7100 8200"            /* ............q.Ç. */
	$"6F62 6A64 0000 0037 6368 6278 0000 000E"            /* objd...7chbx.... */
	$"0016 0013 0101 0000 0000 0000 00CA 0000"            /* ............. .. */
	$"0013 0000 0000 FFFF FFFF 0000 07DE 0000"            /* ......ˇˇˇˇ...ﬁ.. */
	$"0000 0000 0000 0000 0002 0171 0082 006F"            /* ...........q.Ç.o */
	$"626A 6400 0000 3763 6862 7800 0000 0F00"            /* bjd...7chbx..... */
	$"1600 1301 0100 0000 0000 0000 CA00 0000"            /* ............ ... */
	$"2600 0000 00FF FFFF FF00 0007 DF00 0000"            /* &....ˇˇˇˇ...ﬂ... */
	$"0000 0000 0000 0000 0201 7100 8200 6F62"            /* ..........q.Ç.ob */
	$"6A64 0000 0042 7374 7874 0000 0000 0041"            /* jd...Bstxt.....A */
	$"0010 0101 0000 0000 0000 001A 0000 0015"            /* ................ */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0120 0082 0B53 7973"            /* ......... .Ç.Sys */
	$"7465 6D20 4865 6170 6F62 6A64 0000 0040"            /* tem Heapobjd...@ */
	$"7374 7874 0000 0000 0041 0010 0101 0000"            /* stxt.....A...... */
	$"0000 0000 001A 0000 0028 0000 0000 FFFF"            /* .........(....ˇˇ */
	$"FFFF 0000 0000 0000 0000 0000 0000 0000"            /* ˇˇ.............. */
	$"0000 0120 0082 0950 7572 6765 6162 6C65"            /* ... .Ç∆Purgeable */
	$"6F62 6A64 0000 003D 7374 7874 0000 0000"            /* objd...=stxt.... */
	$"0041 0010 0101 0000 0000 0000 001A 0000"            /* .A.............. */
	$"003B 0000 0000 FFFF FFFF 0000 0000 0000"            /* .;....ˇˇˇˇ...... */
	$"0000 0000 0000 0000 0000 0120 0082 064C"            /* ........... .Ç.L */
	$"6F63 6B65 646F 626A 6400 0000 4073 7478"            /* ockedobjd...@stx */
	$"7400 0000 0000 3C00 1001 0100 0000 0000"            /* t.....<......... */
	$"0000 8F00 0000 1500 0000 00FF FFFF FF00"            /* ..è........ˇˇˇˇ. */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"2000 8209 5072 6F74 6563 7465 646F 626A"            /*  .Ç∆Protectedobj */
	$"6400 0000 3E73 7478 7400 0000 0000 3C00"            /* d...>stxt.....<. */
	$"1001 0100 0000 0000 0000 8F00 0000 2800"            /* ..........è...(. */
	$"0000 00FF FFFF FF00 0000 0000 0000 0000"            /* ...ˇˇˇˇ......... */
	$"0000 0000 0000 0001 2000 8207 5072 656C"            /* ........ .Ç.Prel */
	$"6F61 6465 6E64 736F 626A 6400 0000 3973"            /* oadendsobjd...9s */
	$"7478 7400 0000 0000 1F00 1001 0100 0000"            /* txt............. */
	$"0000 0000 1500 0000 4F00 0000 00FF FFFF"            /* ........O....ˇˇˇ */
	$"FF00 0000 0000 0000 0000 0000 0000 0000"            /* ˇ............... */
	$"0001 2000 8502 4944 6F62 6A64 0000 003B"            /* .. .Ö.IDobjd...; */
	$"7374 7874 0000 0000 001F 000F 0101 0000"            /* stxt............ */
	$"0000 0000 0015 0000 006D 0000 0000 FFFF"            /* .........m....ˇˇ */
	$"FFFF 0000 0000 0000 0000 0000 0000 0000"            /* ˇˇ.............. */
	$"0000 0120 0085 044E 616D 656F 626A 6400"            /* ... .Ö.Nameobjd. */
	$"0000 3C74 6267 7600 0000 0000 E900 4101"            /* ..<tbgv.....È.A. */
	$"0100 0000 0000 0000 3400 0000 4400 0000"            /* ........4...D... */
	$"00FF FFFF FF00 0000 0000 0000 0000 0000"            /* .ˇˇˇˇ........... */
	$"0000 0000 0000 0000 0100 0000 0100 0062"            /* ...............b */
	$"6567 736F 626A 6400 0000 3B65 7478 7400"            /* egsobjd...;etxt. */
	$"0000 0500 4A00 1601 0100 0000 0000 0000"            /* ....J........... */
	$"0100 0000 0700 0000 00FF FFFF FF00 0007"            /* .........ˇˇˇˇ... */
	$"D500 0000 0000 0000 0000 0000 0001 1000"            /* ’............... */
	$"8200 00FF 0801 6F62 6A64 0000 003B 6574"            /* Ç..ˇ..objd...;et */
	$"7874 0000 0006 00E2 0016 0101 0000 0000"            /* xt.....‚........ */
	$"0000 0001 0000 0025 0000 0000 FFFF FFFF"            /* .......%....ˇˇˇˇ */
	$"0000 07D6 0000 0000 0000 0000 0000 0000"            /* ...÷............ */
	$"0110 0082 0000 FF20 0365 6E64 7364 6F70"            /* ...Ç..ˇ .endsdop */
	$"6C52 7A69 706F 626A 6400 0000 2469 636E"            /* lRzipobjd...$icn */
	$"7000 0000 0900 2000 2001 0100 0000 0000"            /* p...∆. . ....... */
	$"0000 BA00 0000 4300 0000 00FF FFFF FF00"            /* ..∫...C....ˇˇˇˇ. */
	$"006F 626A 6400 0000 5177 696E 6800 0000"            /* .objd...Qwinh... */
	$"0001 3A00 3C01 0100 0000 00FF FFFF FD00"            /* ..:.<......ˇˇˇ˝. */
	$"0000 0000 0000 00FF FFFF FF00 0000 0000"            /* .......ˇˇˇˇ..... */
	$"0000 0000 0000 0000 0000 0000 0000 0100"            /* ................ */
	$"0000 0100 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0001 5000 0000 6265 6773 6F62"            /* ......P...begsob */
	$"6A64 0000 0051 7467 6278 0000 0000 0109"            /* jd...Qtgbx.....∆ */
	$"002C 0101 0101 0100 0000 0019 0000 0008"            /* .,.............. */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0000 0001 0000 0001"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 00A4 0000 0062 6567 736F 626A 6400"            /* ...§...begsobjd. */
	$"0000 3B73 7478 7400 0000 0000 2300 1001"            /* ..;stxt.....#... */
	$"0100 0000 0000 0000 0600 0000 0600 0000"            /* ................ */
	$"00FF FFFF FF00 0000 0000 0000 0000 0000"            /* .ˇˇˇˇ........... */
	$"0000 0000 0001 2000 9804 5479 7065 6F62"            /* ...... .ò.Typeob */
	$"6A64 0000 0037 7374 7874 0000 0001 0028"            /* jd...7stxt.....( */
	$"0010 0101 0000 0000 0000 002A 0000 0006"            /* ...........*.... */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0120 0082 006F 626A"            /* ......... .Ç.obj */
	$"6400 0000 3B73 7478 7400 0000 0000 2000"            /* d...;stxt..... . */
	$"1001 0100 0000 0000 0000 6100 0000 0600"            /* ..........a..... */
	$"0000 00FF FFFF FF00 0000 0000 0000 0000"            /* ...ˇˇˇˇ......... */
	$"0000 0000 0000 0001 2000 9804 5369 7A65"            /* ........ .ò.Size */
	$"6F62 6A64 0000 0037 7374 7874 0000 0003"            /* objd...7stxt.... */
	$"002E 0010 0101 0000 0000 0000 0082 0000"            /* .............Ç.. */
	$"0006 0000 0000 FFFF FFFF 0000 0000 0000"            /* ......ˇˇˇˇ...... */
	$"0000 0000 0000 0000 0000 0120 0082 006F"            /* ........... .Ç.o */
	$"626A 6400 0000 3A73 7478 7400 0000 0000"            /* bjd...:stxt..... */
	$"2300 0F01 0100 0000 0000 0000 0600 0000"            /* #............... */
	$"1900 0000 00FF FFFF FF00 0000 0000 0000"            /* .....ˇˇˇˇ....... */
	$"0000 0000 0000 0000 0001 2000 9803 4D61"            /* .......... .ò.Ma */
	$"706F 626A 6400 0000 3773 7478 7400 0000"            /* pobjd...7stxt... */
	$"0400 CC00 0F01 0100 0000 0000 0000 2A00"            /* ..Ã...........*. */
	$"0000 1900 0000 00FF FFFF FF00 0000 0000"            /* .......ˇˇˇˇ..... */
	$"0000 0000 0000 0000 0000 0001 2000 8200"            /* ............ .Ç. */
	$"656E 6473 656E 6473 6F62 6A64 0000 003E"            /* endsendsobjd...> */
	$"7075 7368 0000 0014 0041 0014 0100 0000"            /* push.....A...... */
	$"0101 0000 000B 0000 00EA 0000 0000 FFFF"            /* .........Í....ˇˇ */
	$"FFFF 0000 07E4 0000 0000 0000 0000 0000"            /* ˇˇ...‰.......... */
	$"0000 0170 0000 0652 6576 6572 7400 6F62"            /* ...p...Revert.ob */
	$"6A64 0000 003D 7075 7368 0000 0015 0046"            /* jd...=push.....F */
	$"0014 0100 0000 0101 0000 00E3 0000 00EA"            /* ...........„...Í */
	$"0000 0000 FFFF FFFF 0000 07E5 0000 0000"            /* ....ˇˇˇˇ...Â.... */
	$"0000 0000 0000 0000 0170 0000 0541 7070"            /* .........p...App */
	$"6C79 0165 6E64 7365 6E64 2E"                        /* ly.endsend. */
};

data 'PPob' (2100, "New Resource Dialog") {
	$"0002 6F62 6A64 0000 0028 5442 4278 0834"            /* ..objd...(TBBx.4 */
	$"0000 0862 0000 FFFF FFFF FFFF FFFF FFFF"            /* ...b..ˇˇˇˇˇˇˇˇˇˇ */
	$"FFFF 0000 0000 6F6B 2020 636E 636C FFFF"            /* ˇˇ....ok  cnclˇˇ */
	$"FFFF 6265 6773 6F62 6A64 0000 0012 7774"            /* ˇˇbegsobjd....wt */
	$"6861 FFFF FFFE 0101 0001 0002 0005 0006"            /* haˇˇˇ˛.......... */
	$"6F62 6A64 0000 005B 7467 6278 0000 0000"            /* objd...[tgbx.... */
	$"0117 0053 0101 0000 0000 0000 000D 0000"            /* ...S............ */
	$"0052 0000 0000 FFFF FFFF 0000 0000 0000"            /* .R....ˇˇˇˇ...... */
	$"0000 0000 0000 0000 0000 0000 0001 0000"            /* ................ */
	$"0001 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 00A4 0085 0A41 7474 7269 6275"            /* .....§.Ö¬Attribu */
	$"7465 7362 6567 736F 626A 6400 0000 3763"            /* tesbegsobjd...7c */
	$"6862 7800 0000 0B00 1600 1301 0100 0000"            /* hbx............. */
	$"0000 0000 6100 0000 1100 0000 00FF FFFF"            /* ....a........ˇˇˇ */
	$"FF00 0008 3F00 0000 0000 0000 0000 0000"            /* ˇ...?........... */
	$"0201 7100 8200 6F62 6A64 0000 0037 6368"            /* ..q.Ç.objd...7ch */
	$"6278 0000 000C 0016 0013 0101 0000 0000"            /* bx.............. */
	$"0000 0061 0000 0024 0000 0000 FFFF FFFF"            /* ...a...$....ˇˇˇˇ */
	$"0000 0840 0000 0000 0000 0000 0000 0002"            /* ...@............ */
	$"0171 0082 006F 626A 6400 0000 3763 6862"            /* .q.Ç.objd...7chb */
	$"7800 0000 0D00 1600 1301 0100 0000 0000"            /* x............... */
	$"0000 6100 0000 3700 0000 00FF FFFF FF00"            /* ..a...7....ˇˇˇˇ. */
	$"0008 4100 0000 0000 0000 0000 0000 0201"            /* ..A............. */
	$"7100 8200 6F62 6A64 0000 0037 6368 6278"            /* q.Ç.objd...7chbx */
	$"0000 000E 0016 0013 0101 0000 0000 0000"            /* ................ */
	$"00D4 0000 0011 0000 0000 FFFF FFFF 0000"            /* .‘........ˇˇˇˇ.. */
	$"0842 0000 0000 0000 0000 0000 0002 0171"            /* .B.............q */
	$"0082 006F 626A 6400 0000 3763 6862 7800"            /* .Ç.objd...7chbx. */
	$"0000 0F00 1600 1301 0100 0000 0000 0000"            /* ................ */
	$"D400 0000 2400 0000 00FF FFFF FF00 0008"            /* ‘...$....ˇˇˇˇ... */
	$"4300 0000 0000 0000 0000 0000 0201 7100"            /* C.............q. */
	$"8200 6F62 6A64 0000 0042 7374 7874 0000"            /* Ç.objd...Bstxt.. */
	$"0000 0041 0010 0101 0000 0000 0000 001E"            /* ...A............ */
	$"0000 0013 0000 0000 FFFF FFFF 0000 0000"            /* ........ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0120 0082"            /* ............. .Ç */
	$"0B53 7973 7465 6D20 4865 6170 6F62 6A64"            /* .System Heapobjd */
	$"0000 0040 7374 7874 0000 0000 0041 0010"            /* ...@stxt.....A.. */
	$"0101 0000 0000 0000 001E 0000 0026 0000"            /* .............&.. */
	$"0000 FFFF FFFF 0000 0000 0000 0000 0000"            /* ..ˇˇˇˇ.......... */
	$"0000 0000 0000 0120 0082 0950 7572 6765"            /* ....... .Ç∆Purge */
	$"6162 6C65 6F62 6A64 0000 003D 7374 7874"            /* ableobjd...=stxt */
	$"0000 0000 0041 0010 0101 0000 0000 0000"            /* .....A.......... */
	$"001E 0000 0039 0000 0000 FFFF FFFF 0000"            /* .....9....ˇˇˇˇ.. */
	$"0000 0000 0000 0000 0000 0000 0000 0120"            /* ...............  */
	$"0082 064C 6F63 6B65 646F 626A 6400 0000"            /* .Ç.Lockedobjd... */
	$"4073 7478 7400 0000 0000 3C00 1001 0100"            /* @stxt.....<..... */
	$"0000 0000 0000 9900 0000 1300 0000 00FF"            /* ......ô........ˇ */
	$"FFFF FF00 0000 0000 0000 0000 0000 0000"            /* ˇˇˇ............. */
	$"0000 0001 2000 8209 5072 6F74 6563 7465"            /* .... .Ç∆Protecte */
	$"646F 626A 6400 0000 3E73 7478 7400 0000"            /* dobjd...>stxt... */
	$"0000 3C00 1001 0100 0000 0000 0000 9900"            /* ..<...........ô. */
	$"0000 2600 0000 00FF FFFF FF00 0000 0000"            /* ..&....ˇˇˇˇ..... */
	$"0000 0000 0000 0000 0000 0001 2000 8207"            /* ............ .Ç. */
	$"5072 656C 6F61 6465 6E64 736F 626A 6400"            /* Preloadendsobjd. */
	$"0000 3C74 6267 7600 0000 0001 2A00 4701"            /* ..<tbgv.....*.G. */
	$"0100 0000 0000 0000 0400 0000 0500 0000"            /* ................ */
	$"00FF FFFF FF00 0000 0000 0000 0000 0000"            /* .ˇˇˇˇ........... */
	$"0000 0000 0000 0000 0100 0000 0100 0062"            /* ...............b */
	$"6567 736F 626A 6400 0000 3B65 7478 7400"            /* egsobjd...;etxt. */
	$"0000 0100 3200 1801 0101 0100 0000 0000"            /* ....2........... */
	$"2F00 0000 0300 0000 00FF FFFF FF00 0008"            /* /........ˇˇˇˇ... */
	$"3500 0000 0000 0000 0000 0000 0001 1000"            /* 5............... */
	$"8200 0004 0803 6F62 6A64 0000 003E 6574"            /* Ç.....objd...>et */
	$"7874 0000 0003 0032 0018 0101 0000 0000"            /* xt.....2........ */
	$"0000 0098 0000 0003 0000 0000 FFFF FFFF"            /* ...ò........ˇˇˇˇ */
	$"0000 0837 0000 0000 0000 0000 0000 0000"            /* ...7............ */
	$"0110 0082 0331 3238 0005 0801 6F62 6A64"            /* ...Ç.128....objd */
	$"0000 003B 6574 7874 0000 0004 00F5 0018"            /* ...;etxt.....ı.. */
	$"0101 0000 0000 0000 002F 0000 0027 0000"            /* ........./...'.. */
	$"0000 FFFF FFFF 0000 0838 0000 0000 0000"            /* ..ˇˇˇˇ...8...... */
	$"0000 0000 0000 0110 0082 0000 FF20 036F"            /* .........Ç..ˇ .o */
	$"626A 6400 0000 3973 7478 7400 0000 0000"            /* bjd...9stxt..... */
	$"1400 1001 0100 0000 0000 0000 8200 0000"            /* ............Ç... */
	$"0800 0000 00FF FFFF FF00 0000 0000 0000"            /* .....ˇˇˇˇ....... */
	$"0000 0000 0000 0000 0001 2000 9802 4944"            /* .......... .ò.ID */
	$"6F62 6A64 0000 003B 7374 7874 0000 0000"            /* objd...;stxt.... */
	$"0025 0010 0101 0000 0000 0000 0009 0000"            /* .%...........∆.. */
	$"0008 0000 0000 FFFF FFFF 0000 0000 0000"            /* ......ˇˇˇˇ...... */
	$"0000 0000 0000 0000 0000 0120 0098 0454"            /* ........... .ò.T */
	$"7970 656F 626A 6400 0000 3B73 7478 7400"            /* ypeobjd...;stxt. */
	$"0000 0000 2400 0F01 0100 0000 0000 0000"            /* ....$........... */
	$"0900 0000 2B00 0000 00FF FFFF FF00 0000"            /* ∆...+....ˇˇˇˇ... */
	$"0000 0000 0000 0000 0000 0000 0001 2000"            /* .............. . */
	$"9804 4E61 6D65 656E 6473 6F62 6A64 0000"            /* ò.Nameendsobjd.. */
	$"003E 7075 7368 6F6B 2020 0046 0014 0101"            /* .>pushok  .F.... */
	$"0000 0101 0000 00E6 0000 00B5 0000 0000"            /* .......Ê...µ.... */
	$"FFFF FFFF 0000 0384 0000 0000 0000 0000"            /* ˇˇˇˇ...Ñ........ */
	$"0000 0000 0170 0000 0643 7265 6174 6501"            /* .....p...Create. */
	$"6F62 6A64 0000 003E 7075 7368 636E 636C"            /* objd...>pushcncl */
	$"0041 0014 0101 0000 0101 0000 0090 0000"            /* .A...........ê.. */
	$"00B5 0000 0000 FFFF FFFF 0000 0385 0000"            /* .µ....ˇˇˇˇ...Ö.. */
	$"0000 0000 0000 0000 0000 0170 0000 0643"            /* ...........p...C */
	$"616E 6365 6C00 6F62 6A64 0000 0041 7075"            /* ancel.objd...Apu */
	$"7368 0000 0014 0053 0014 0101 0000 0101"            /* sh.....S........ */
	$"0000 000D 0000 00B5 0000 0000 FFFF FFFF"            /* .......µ....ˇˇˇˇ */
	$"0000 0848 0000 0000 0000 0000 0000 0000"            /* ...H............ */
	$"0170 0000 0955 6E69 7175 6520 4944 0065"            /* .p..∆Unique ID.e */
	$"6E64 7365 6E64 2E"                                  /* ndsend. */
};

data 'PPob' (5000, "About Window") {
	$"0002 646F 706C 4162 6F57 6F62 6A64 0000"            /* ..doplAboWobjd.. */
	$"0024 646C 6F67 1388 0000 0040 0000 0040"            /* .$dlog.à...@...@ */
	$"0040 FFFF FFFF FFFF FFFF 0000 0000 6F6B"            /* .@ˇˇˇˇˇˇˇˇ....ok */
	$"2020 4C63 6E63 6265 6773 6F62 6A64 0000"            /*   Lcncbegsobjd.. */
	$"0037 7374 7874 5665 7273 0055 0010 0101"            /* .7stxtVers.U.... */
	$"0000 0001 0000 002B 0000 0161 0000 0000"            /* .......+...a.... */
	$"FFFF FFFF 0000 0000 0000 0000 0000 0000"            /* ˇˇˇˇ............ */
	$"0000 0000 0120 0082 006F 626A 6400 0000"            /* ..... .Ç.objd... */
	$"3E73 7478 7400 0000 0000 2700 1001 0100"            /* >stxt.....'..... */
	$"0000 0100 0000 0400 0001 6100 0000 00FF"            /* ..........a....ˇ */
	$"FFFF FF00 0000 0000 0000 0000 0000 0000"            /* ˇˇˇ............. */
	$"0000 0001 2000 8207 5665 7273 696F 6E6F"            /* .... .Ç.Versiono */
	$"626A 6400 0000 3E70 6963 7400 0000 0000"            /* bjd...>pict..... */
	$"7201 6001 0100 0000 00FF FFFF FCFF FFFF"            /* r.`......ˇˇˇ¸ˇˇˇ */
	$"FF00 0000 00FF FFFF FF00 0000 0000 0000"            /* ˇ....ˇˇˇˇ....... */
	$"0000 0000 0000 0000 0000 0000 0100 0000"            /* ................ */
	$"0100 0000 816F 626A 6400 0000 3E70 6963"            /* ....Åobjd...>pic */
	$"7400 0000 0000 F500 6001 0100 0000 0000"            /* t.....ı.`....... */
	$"0000 4C00 0000 0100 0000 00FF FFFF FF00"            /* ..L........ˇˇˇˇ. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0100 0000 0100 0000 806F 626A 6400"            /* ..........Äobjd. */
	$"0000 4274 7874 7600 0000 0000 DD00 2201"            /* ..Btxtv.....›.". */
	$"0101 0001 0000 0000 6A00 0000 6400 0000"            /* ........j...d... */
	$"00FF FFFF FF00 0000 0000 0000 0000 0000"            /* .ˇˇˇˇ........... */
	$"0000 0000 0000 0000 0100 0000 0100 0090"            /* ...............ê */
	$"0000 8D00 FA6F 626A 6400 0000 3A70 7573"            /* ..ç.˙objd...:pus */
	$"686F 6B20 2000 3700 1401 0100 0001 0100"            /* hok  .7......... */
	$"0001 0600 0001 5300 0000 00FF FFFF FF6F"            /* ......S....ˇˇˇˇo */
	$"6B20 2000 0000 0000 0000 0000 0000 0001"            /* k  ............. */
	$"7000 0002 4F4B 016F 626A 6400 0000 3F70"            /* p...OK.objd...?p */
	$"7573 684C 636E 6300 4600 1401 0100 0001"            /* ushLcnc.F....... */
	$"0100 0000 AF00 0001 5300 0000 00FF FFFF"            /* ....Ø...S....ˇˇˇ */
	$"FF4C 636E 6300 0000 0000 0000 0000 0000"            /* ˇLcnc........... */
	$"0001 7000 0007 4C69 6365 6E63 6500 646F"            /* ..p...Licence.do */
	$"706C 5354 5855 6F62 6A64 0000 0037 7374"            /* plSTXUobjd...7st */
	$"7874 0000 000B 00D2 0012 0101 0100 0100"            /* xt.....“........ */
	$"0000 0071 0000 00B1 0000 0000 FFFF FFFF"            /* ...q...±....ˇˇˇˇ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0120 0092 0064 6F70 6C53 5458 556F 626A"            /* . .í.doplSTXUobj */
	$"6400 0000 3773 7478 7400 0000 0C00 D200"            /* d...7stxt.....“. */
	$"1201 0101 0001 0000 0000 7100 0000 C700"            /* ..........q...«. */
	$"0000 00FF FFFF FF00 0000 0000 0000 0000"            /* ...ˇˇˇˇ......... */
	$"0000 0000 0000 0001 2000 9200 646F 706C"            /* ........ .í.dopl */
	$"5354 5855 6F62 6A64 0000 0037 7374 7874"            /* STXUobjd...7stxt */
	$"0000 000D 00D2 0012 0101 0100 0100 0000"            /* .....“.......... */
	$"0071 0000 00DD 0000 0000 FFFF FFFF 0000"            /* .q...›....ˇˇˇˇ.. */
	$"0000 0000 0000 0000 0000 0000 0000 0120"            /* ...............  */
	$"0092 0064 6F70 6C53 5458 556F 626A 6400"            /* .í.doplSTXUobjd. */
	$"0000 3773 7478 7400 0000 0E00 D200 1201"            /* ..7stxt.....“... */
	$"0101 0001 0000 0000 7100 0000 F300 0000"            /* ........q...Û... */
	$"00FF FFFF FF00 0000 0000 0000 0000 0000"            /* .ˇˇˇˇ........... */
	$"0000 0000 0001 2000 9200 646F 706C 5354"            /* ...... .í.doplST */
	$"5855 6F62 6A64 0000 0037 7374 7874 0000"            /* XUobjd...7stxt.. */
	$"000F 00D2 0012 0101 0100 0100 0000 0071"            /* ...“...........q */
	$"0000 0109 0000 0000 FFFF FFFF 0000 0000"            /* ...∆....ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0120 0092"            /* ............. .í */
	$"006F 626A 6400 0000 4274 7874 7600 0000"            /* .objd...Btxtv... */
	$"0000 A900 1701 0101 0001 0000 0000 8600"            /* ..©...........Ü. */
	$"0001 2800 0000 00FF FFFF FF00 0000 0000"            /* ..(....ˇˇˇˇ..... */
	$"0000 0000 0000 0000 0000 0000 0000 0100"            /* ................ */
	$"0000 0100 0090 0000 8D00 FB64 6F70 6C53"            /* .....ê..ç.˚doplS */
	$"5458 556F 626A 6400 0000 3773 7478 7400"            /* TXUobjd...7stxt. */
	$"0000 1000 D200 1401 0101 0001 0000 0000"            /* ....“........... */
	$"7100 0000 8800 0000 00FF FFFF FF00 0000"            /* q...à....ˇˇˇˇ... */
	$"0000 0000 0000 0000 0000 0000 0001 2000"            /* .............. . */
	$"9200 656E 6473 656E 642E"                           /* í.endsend. */
};

data 'PPob' (5100, "Licence Window") {
	$"0002 6F62 6A64 0000 001C 7769 6E64 13EC"            /* ..objd....wind.Ï */
	$"0002 1FE2 0000 0064 0064 FFFF FFFF FFFF"            /* ...‚...d.dˇˇˇˇˇˇ */
	$"FFFF 0000 0000 6265 6773 6F62 6A64 0000"            /* ˇˇ....begsobjd.. */
	$"0048 6173 6372 0000 0001 0190 015E 0101"            /* .Hascr.....ê.^.. */
	$"0101 0101 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"FFFF FFFF 0000 0001 0000 0001 0000 0000"            /* ˇˇˇˇ............ */
	$"0000 0000 0000 0000 0000 0000 0000 FFFF"            /* ..............ˇˇ */
	$"000F 0000 000F 0000 0002 6265 6773 6F62"            /* ..........begsob */
	$"6A64 0000 0042 7478 7476 0000 0002 017D"            /* jd...Btxtv.....} */
	$"015C 0101 0101 0101 0000 0002 0000 0001"            /* .\.............. */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0000 0001 0000 0001"            /* ................ */
	$"0000 3C00 0082 0082 656E 6473 656E 6473"            /* ..<..Ç.Çendsends */
	$"656E 642E"                                          /* end. */
};

data 'PPob' (8500, "Find Dialog") {
	$"0002 6F62 6A64 0000 0028 5442 4278 2134"            /* ..objd...(TBBx!4 */
	$"0000 08E2 0000 0040 0040 FFFF FFFF FFFF"            /* ...‚...@.@ˇˇˇˇˇˇ */
	$"FFFF 0000 0000 6F6B 2020 636E 636C FFFF"            /* ˇˇ....ok  cnclˇˇ */
	$"FFFF 6265 6773 6F62 6A64 0000 0012 7774"            /* ˇˇbegsobjd....wt */
	$"6861 FFFF FFFE 0101 0001 0002 0001 0002"            /* haˇˇˇ˛.......... */
	$"6F62 6A64 0000 0029 6564 6974 0000 0001"            /* objd...)edit.... */
	$"010E 0049 0101 0000 0000 0000 0010 0000"            /* ...I............ */
	$"0020 0000 0000 FFFF FFFF 0000 8B00 FFE8"            /* . ....ˇˇˇˇ..ã.ˇË */
	$"036F 626A 6400 0000 4263 6862 7800 0000"            /* .objd...Bchbx... */
	$"0400 5000 1201 0000 0000 0000 0000 9D00"            /* ..P...........ù. */
	$"0000 7000 0000 00FF FFFF FF00 0021 3800"            /* ..p....ˇˇˇˇ..!8. */
	$"0000 0100 0000 0000 0000 0201 7100 820B"            /* ............q.Ç. */
	$"4967 6E6F 7265 2063 6173 656F 626A 6400"            /* Ignore caseobjd. */
	$"0000 3E70 7573 686F 6B20 2000 4600 1401"            /* ..>pushok  .F... */
	$"0100 0001 0100 0000 DB00 0000 A400 0000"            /* ........€...§... */
	$"00FF FFFF FF00 0003 8400 0000 0000 0000"            /* .ˇˇˇˇ...Ñ....... */
	$"0000 0000 0001 7000 0006 5365 6172 6368"            /* ......p...Search */
	$"016F 626A 6400 0000 3E70 7573 6863 6E63"            /* .objd...>pushcnc */
	$"6C00 4100 1401 0100 0001 0100 0000 8500"            /* l.A...........Ö. */
	$"0000 A400 0000 00FF FFFF FF00 0003 8500"            /* ..§....ˇˇˇˇ...Ö. */
	$"0000 0000 0000 0000 0000 0001 7000 0006"            /* ............p... */
	$"4361 6E63 656C 006F 626A 6400 0000 3C72"            /* Cancel.objd...<r */
	$"6770 7600 0000 0600 6000 3001 0100 0000"            /* gpv.....`.0..... */
	$"0000 0000 3600 0000 6B00 0000 00FF FFFF"            /* ....6...k....ˇˇˇ */
	$"FF00 0000 0000 0000 0000 0000 0000 0000"            /* ˇ............... */
	$"0000 0000 0100 0000 0100 0062 6567 736F"            /* ...........begso */
	$"626A 6400 0000 4272 6462 7400 0000 0200"            /* bjd...Brdbt..... */
	$"5000 1201 0100 0000 0000 0000 0600 0000"            /* P............... */
	$"0500 0000 00FF FFFF FF00 0021 3600 0000"            /* .....ˇˇˇˇ..!6... */
	$"0100 0000 0000 0000 0201 7200 820B 696E"            /* ..........r.Ç.in */
	$"2048 6578 2050 616E 656F 626A 6400 0000"            /*  Hex Paneobjd... */
	$"4372 6462 7400 0000 0300 5000 1201 0100"            /* Crdbt.....P..... */
	$"0000 0000 0000 0600 0000 1800 0000 00FF"            /* ...............ˇ */
	$"FFFF FF00 0021 3700 0000 0000 0000 0000"            /* ˇˇˇ..!7......... */
	$"0000 0201 7200 820C 696E 2054 6578 7420"            /* ....r.Ç.in Text  */
	$"5061 6E65 656E 6473 6F62 6A64 0000 0044"            /* Paneendsobjd...D */
	$"7374 7874 0000 0000 009F 0010 0101 0000"            /* stxt.....ü...... */
	$"0000 0000 0011 0000 000F 0000 0000 FFFF"            /* ..............ˇˇ */
	$"FFFF 0000 0000 0000 0000 0000 0000 0000"            /* ˇˇ.............. */
	$"0000 0120 0085 0D53 6561 7263 6820 7374"            /* ... .Ö.Search st */
	$"7269 6E67 656E 6473 656E 642E"                      /* ringendsend. */
};

data 'PPob' (9500, "Alert") {
	$"0002 6F62 6A64 0000 0028 5442 4278 251C"            /* ..objd...(TBBx%. */
	$"0000 08E2 0000 0040 0040 FFFF FFFF FFFF"            /* ...‚...@.@ˇˇˇˇˇˇ */
	$"FFFF 0000 0000 6F6B 2020 FFFF FFFF FFFF"            /* ˇˇ....ok  ˇˇˇˇˇˇ */
	$"FFFF 6265 6773 6F62 6A64 0000 0012 7774"            /* ˇˇbegsobjd....wt */
	$"6861 FFFF FFFE 0101 0003 0004 0003 0004"            /* haˇˇˇ˛.......... */
	$"6F62 6A64 0000 003A 7075 7368 6F6B 2020"            /* objd...:pushok   */
	$"003A 0014 0101 0000 0101 0000 00E8 0000"            /* .:...........Ë.. */
	$"0078 0000 0000 FFFF FFFF 0000 0384 0000"            /* .x....ˇˇˇˇ...Ñ.. */
	$"0000 0000 0000 0000 0000 0170 0000 024F"            /* ...........p...O */
	$"4B01 6F62 6A64 0000 0025 6361 7074 4D45"            /* K.objd...%captME */
	$"5347 00F4 005A 0101 0101 0101 0000 0037"            /* SG.Ù.Z.........7 */
	$"0000 0014 0000 0000 FFFF FFFF 0000 9A6F"            /* ........ˇˇˇˇ..öo */
	$"626A 6400 0000 2469 636E 7000 0000 0000"            /* bjd...$icnp..... */
	$"2000 2001 0100 0000 0000 0000 0A00 0000"            /*  . .........¬... */
	$"0F00 0000 00FF FFFF FF00 8065 6E64 7365"            /* .....ˇˇˇˇ.Äendse */
	$"6E64 2E"                                            /* nd. */
};

data 'PPob' (9510, "Ask If") {
	$"0002 6F62 6A64 0000 0028 5442 4278 2526"            /* ..objd...(TBBx%& */
	$"0000 08E2 0000 0040 0040 FFFF FFFF FFFF"            /* ...‚...@.@ˇˇˇˇˇˇ */
	$"FFFF 0000 0000 6F6B 2020 636E 636C FFFF"            /* ˇˇ....ok  cnclˇˇ */
	$"FFFF 6265 6773 6F62 6A64 0000 0012 7774"            /* ˇˇbegsobjd....wt */
	$"6861 FFFF FFFE 0101 0001 0002 0001 0002"            /* haˇˇˇ˛.......... */
	$"6F62 6A64 0000 003E 7075 7368 636E 636C"            /* objd...>pushcncl */
	$"0046 0014 0101 0000 0101 0000 008C 0000"            /* .F...........å.. */
	$"0078 0000 0000 FFFF FFFF 0000 0385 0000"            /* .x....ˇˇˇˇ...Ö.. */
	$"0000 0000 0000 0000 0000 0170 0000 0643"            /* ...........p...C */
	$"616E 6365 6C00 6F62 6A64 0000 003A 7075"            /* ancel.objd...:pu */
	$"7368 6F6B 2020 003A 0014 0101 0000 0101"            /* shok  .:........ */
	$"0000 00E6 0000 0078 0000 0000 FFFF FFFF"            /* ...Ê...x....ˇˇˇˇ */
	$"0000 0384 0000 0000 0000 0000 0000 0000"            /* ...Ñ............ */
	$"0170 0000 024F 4B01 6F62 6A64 0000 0025"            /* .p...OK.objd...% */
	$"6361 7074 4D45 5347 00EE 005A 0101 0101"            /* captMESG.Ó.Z.... */
	$"0101 0000 0037 0000 0014 0000 0000 FFFF"            /* .....7........ˇˇ */
	$"FFFF 0000 9A6F 626A 6400 0000 2469 636E"            /* ˇˇ..öobjd...$icn */
	$"7000 0000 0000 2000 2001 0100 0000 0000"            /* p..... . ....... */
	$"0000 0A00 0000 0F00 0000 00FF FFFF FF00"            /* ..¬........ˇˇˇˇ. */
	$"8065 6E64 7365 6E64 2E"                             /* Äendsend. */
};

data 'PPob' (9520, "Ask Yes No") {
	$"0002 6F62 6A64 0000 0028 5442 4278 2530"            /* ..objd...(TBBx%0 */
	$"0000 08E2 0000 0040 0040 FFFF FFFF FFFF"            /* ...‚...@.@ˇˇˇˇˇˇ */
	$"FFFF 0000 0000 6F6B 2020 636E 636C 6E6F"            /* ˇˇ....ok  cnclno */
	$"2020 6265 6773 6F62 6A64 0000 0012 7774"            /*   begsobjd....wt */
	$"6861 FFFF FFFE 0101 0003 0004 0003 0004"            /* haˇˇˇ˛.......... */
	$"6F62 6A64 0000 003A 7075 7368 6F6B 2020"            /* objd...:pushok   */
	$"003A 0014 0101 0000 0101 0000 00E6 0000"            /* .:...........Ê.. */
	$"0078 0000 0000 FFFF FFFF 0000 0384 0000"            /* .x....ˇˇˇˇ...Ñ.. */
	$"0000 0000 0000 0000 0000 0170 0000 024F"            /* ...........p...O */
	$"4B01 6F62 6A64 0000 003E 7075 7368 636E"            /* K.objd...>pushcn */
	$"636C 0046 0014 0101 0100 0001 0000 000B"            /* cl.F............ */
	$"0000 0078 0000 0000 FFFF FFFF 0000 0385"            /* ...x....ˇˇˇˇ...Ö */
	$"0000 0000 0000 0000 0000 0000 0170 0000"            /* .............p.. */
	$"0643 616E 6365 6C00 6F62 6A64 0000 003A"            /* .Cancel.objd...: */
	$"7075 7368 6E6F 2020 0041 0014 0101 0000"            /* pushno  .A...... */
	$"0101 0000 0095 0000 0078 0000 0000 FFFF"            /* .....ï...x....ˇˇ */
	$"FFFF 0000 251E 0000 0000 0000 0000 0000"            /* ˇˇ..%........... */
	$"0000 0170 0000 024E 6F00 6F62 6A64 0000"            /* ...p...No.objd.. */
	$"0025 6361 7074 4D45 5347 00F0 005A 0101"            /* .%captMESG..Z.. */
	$"0101 0101 0000 0037 0000 0014 0000 0000"            /* .......7........ */
	$"FFFF FFFF 0000 9A6F 626A 6400 0000 2469"            /* ˇˇˇˇ..öobjd...$i */
	$"636E 7000 0000 0000 2000 2001 0100 0000"            /* cnp..... . ..... */
	$"0000 0000 0A00 0000 0F00 0000 00FF FFFF"            /* ....¬........ˇˇˇ */
	$"FF00 8065 6E64 7365 6E64 2E"                        /* ˇ.Äendsend. */
};

data 'PPob' (6000, "Rez Compare Dialog") {
	$"0002 6F62 6A64 0000 0028 5442 4278 1770"            /* ..objd...(TBBx.p */
	$"0000 08E2 0000 0040 0040 FFFF FFFF FFFF"            /* ...‚...@.@ˇˇˇˇˇˇ */
	$"FFFF 0000 0000 6F6B 2020 636E 636C FFFF"            /* ˇˇ....ok  cnclˇˇ */
	$"FFFF 6265 6773 6F62 6A64 0000 0012 7774"            /* ˇˇbegsobjd....wt */
	$"6861 FFFF FFFE 0101 0001 0002 0001 0002"            /* haˇˇˇ˛.......... */
	$"6F62 6A64 0000 003F 7075 7368 6F6B 2020"            /* objd...?pushok   */
	$"0055 0014 0101 0000 0101 0000 01B2 0000"            /* .U...........≤.. */
	$"00B2 0000 0000 FFFF FFFF 0000 0384 0000"            /* .≤....ˇˇˇˇ...Ñ.. */
	$"0000 0000 0000 0000 0000 0170 0000 0743"            /* ...........p...C */
	$"6F6D 7061 7265 016F 626A 6400 0000 3E70"            /* ompare.objd...>p */
	$"7573 6863 6E63 6C00 4100 1401 0100 0001"            /* ushcncl.A....... */
	$"0100 0001 5B00 0000 B200 0000 00FF FFFF"            /* ....[...≤....ˇˇˇ */
	$"FF00 0003 8500 0000 0000 0000 0000 0000"            /* ˇ...Ö........... */
	$"0001 7000 0006 4361 6E63 656C 006F 626A"            /* ..p...Cancel.obj */
	$"6400 0000 4D62 6275 7400 0000 0100 3C00"            /* d...Mbbut.....<. */
	$"1201 0100 0000 0000 0000 5600 0000 0A00"            /* ..........V...¬. */
	$"0000 00FF FFFF FF00 0017 7100 0000 0000"            /* ...ˇˇˇˇ...q..... */
	$"0080 0000 0000 0000 2100 8207 4368 6F6F"            /* .Ä......!.Ç.Choo */
	$"7365 C900 0000 0000 0100 0000 0000 0100"            /* se…............. */
	$"0100 6F62 6A64 0000 004D 6262 7574 0000"            /* ..objd...Mbbut.. */
	$"0003 003C 0012 0101 0000 0000 0000 0056"            /* ...<...........V */
	$"0000 004B 0000 0000 FFFF FFFF 0000 1773"            /* ...K....ˇˇˇˇ...s */
	$"0000 0000 0000 8000 0000 0000 0021 0082"            /* ......Ä......!.Ç */
	$"0743 686F 6F73 65C9 0000 0000 0001 0000"            /* .Choose…........ */
	$"0000 0001 0001 006F 626A 6400 0000 3F73"            /* .......objd...?s */
	$"7478 7400 0000 0000 4100 1001 0100 0000"            /* txt.....A....... */
	$"0000 0000 0A00 0000 0D00 0000 00FF FFFF"            /* ....¬........ˇˇˇ */
	$"FF00 0000 0000 0000 0000 0000 0000 0000"            /* ˇ............... */
	$"0001 2000 8508 4F6C 6420 6669 6C65 6F62"            /* .. .Ö.Old fileob */
	$"6A64 0000 003F 7374 7874 0000 0000 0041"            /* jd...?stxt.....A */
	$"0010 0101 0000 0000 0000 000A 0000 004E"            /* ...........¬...N */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0120 0085 084E 6577"            /* ......... .Ö.New */
	$"2066 696C 656F 626A 6400 0000 5174 6762"            /*  fileobjd...Qtgb */
	$"7800 0000 0001 EF00 1701 0101 0101 0000"            /* x.....Ô......... */
	$"0000 1700 0000 2500 0000 00FF FFFF FF00"            /* ......%....ˇˇˇˇ. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0100 0000 0100 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 A400 0000 6265"            /* ..........§...be */
	$"6773 646F 706C 4473 7478 6F62 6A64 0000"            /* gsdoplDstxobjd.. */
	$"0037 7374 7874 0000 0002 01E7 0011 0101"            /* .7stxt.....Á.... */
	$"0100 0100 0000 0004 0000 0003 0000 0000"            /* ................ */
	$"FFFF FFFF 0000 0000 0000 0000 0000 0000"            /* ˇˇˇˇ............ */
	$"0000 0000 0120 0088 0065 6E64 736F 626A"            /* ..... .à.endsobj */
	$"6400 0000 4E63 6862 7800 0000 0500 8900"            /* d...Nchbx.....â. */
	$"1201 0100 0000 0000 0000 2000 0000 8C00"            /* .......... ...å. */
	$"0000 00FF FFFF FF00 0017 7500 0000 0000"            /* ...ˇˇˇˇ...u..... */
	$"0000 0000 0000 0201 7100 8217 6967 6E6F"            /* ........q.Ç.igno */
	$"7265 206E 616D 6520 6469 6666 6572 656E"            /* re name differen */
	$"6365 736F 626A 6400 0000 5174 6762 7800"            /* cesobjd...Qtgbx. */
	$"0000 0001 EF00 1701 0101 0101 0000 0000"            /* ....Ô........... */
	$"1700 0000 6800 0000 00FF FFFF FF00 0000"            /* ....h....ˇˇˇˇ... */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0100 0000 0100 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 A400 0000 6265 6773"            /* ........§...begs */
	$"646F 706C 4473 7478 6F62 6A64 0000 0037"            /* doplDstxobjd...7 */
	$"7374 7874 0000 0004 01E7 0011 0101 0100"            /* stxt.....Á...... */
	$"0100 0000 0004 0000 0003 0000 0000 FFFF"            /* ..............ˇˇ */
	$"FFFF 0000 0000 0000 0000 0000 0000 0000"            /* ˇˇ.............. */
	$"0000 0120 0088 0065 6E64 736F 626A 6400"            /* ... .à.endsobjd. */
	$"0000 5363 6862 7800 0000 0600 9900 1201"            /* ..Schbx.....ô... */
	$"0100 0000 0000 0000 C300 0000 8C00 0000"            /* ........√...å... */
	$"00FF FFFF FF00 0017 7600 0000 0100 0000"            /* .ˇˇˇˇ...v....... */
	$"0000 0000 0201 7100 821C 6967 6E6F 7265"            /* ......q.Ç.ignore */
	$"2061 7474 7269 6275 7465 2064 6966 6665"            /*  attribute diffe */
	$"7265 6E63 6573 6F62 6A64 0000 004E 6368"            /* rencesobjd...Nch */
	$"6278 0000 0007 0087 0012 0101 0000 0000"            /* bx.....á........ */
	$"0000 016F 0000 008C 0000 0000 FFFF FFFF"            /* ...o...å....ˇˇˇˇ */
	$"0000 1777 0000 0000 0000 0000 0000 0002"            /* ...w............ */
	$"0171 0082 1769 676E 6F72 6520 6461 7461"            /* .q.Ç.ignore data */
	$"2064 6966 6665 7265 6E63 6573 656E 6473"            /*  differencesends */
	$"656E 642E"                                          /* end. */
};

data 'PPob' (6500, "Rez Compare Results") {
	$"0002 646F 706C 5263 7257 6F62 6A64 0000"            /* ..doplRcrWobjd.. */
	$"001C 7769 6E64 1964 0002 1FE2 0000 0261"            /* ..wind.d...‚...a */
	$"01F9 0261 FFFF FFFF FFFF 0000 0000 6265"            /* .˘.aˇˇˇˇˇˇ....be */
	$"6773 6F62 6A64 0000 0012 7774 6861 FFFF"            /* gsobjd....wthaˇˇ */
	$"FFFE 0101 0001 0002 0001 0002 6F62 6A64"            /* ˇ˛..........objd */
	$"0000 0051 7769 6E68 0000 0000 026B 0063"            /* ...Qwinh.....k.c */
	$"0101 0001 0000 FFFF FFFE 0000 0000 0000"            /* ......ˇˇˇ˛...... */
	$"0000 FFFF FFFF 0000 0000 0000 0000 0000"            /* ..ˇˇˇˇ.......... */
	$"0000 0000 0000 0000 0001 0000 0001 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0150 0000 0062 6567 736F 626A 6400 0000"            /* .P...begsobjd... */
	$"5174 6762 7800 0000 0001 9F00 1F01 0101"            /* Qtgbx.....ü..... */
	$"0101 0000 0000 7200 0000 0900 0000 00FF"            /* ......r...∆....ˇ */
	$"FFFF FF00 0000 0000 0000 0000 0000 0000"            /* ˇˇˇ............. */
	$"0000 0000 0000 0100 0000 0100 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 A400"            /* ..............§. */
	$"0000 6265 6773 6F62 6A64 0000 0037 7374"            /* ..begsobjd...7st */
	$"7874 0000 0002 0197 0019 0101 0100 0100"            /* xt.....ó........ */
	$"0000 0004 0000 0004 0000 0000 FFFF FFFF"            /* ............ˇˇˇˇ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0120 0088 0065 6E64 736F 626A 6400 0000"            /* . .à.endsobjd... */
	$"5174 6762 7800 0000 0001 9F00 1F01 0101"            /* Qtgbx.....ü..... */
	$"0101 0000 0000 7300 0000 2E00 0000 00FF"            /* ......s........ˇ */
	$"FFFF FF00 0000 0000 0000 0000 0000 0000"            /* ˇˇˇ............. */
	$"0000 0000 0000 0100 0000 0100 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 A400"            /* ..............§. */
	$"0000 6265 6773 6F62 6A64 0000 0037 7374"            /* ..begsobjd...7st */
	$"7874 0000 0003 0197 0019 0101 0100 0100"            /* xt.....ó........ */
	$"0000 0004 0000 0004 0000 0000 FFFF FFFF"            /* ............ˇˇˇˇ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0120 0088 0065 6E64 736F 626A 6400 0000"            /* . .à.endsobjd... */
	$"3A73 7478 7400 0000 0000 1E00 1001 0100"            /* :stxt........... */
	$"0000 0000 0000 5200 0000 1000 0000 00FF"            /* ......R........ˇ */
	$"FFFF FF00 0000 0000 0000 0000 0000 0000"            /* ˇˇˇ............. */
	$"0000 0001 2000 8503 4F6C 646F 626A 6400"            /* .... .Ö.Oldobjd. */
	$"0000 3A73 7478 7400 0000 0000 1E00 1001"            /* ..:stxt......... */
	$"0100 0000 0000 0000 5200 0000 3500 0000"            /* ........R...5... */
	$"00FF FFFF FF00 0000 0000 0000 0000 0000"            /* .ˇˇˇˇ........... */
	$"0000 0000 0001 2000 8503 4E65 776F 626A"            /* ...... .Ö.Newobj */
	$"6400 0000 3773 7478 7400 0000 0800 FA00"            /* d...7stxt.....˙. */
	$"1001 0100 0000 0000 0000 8500 0000 5000"            /* ..........Ö...P. */
	$"0000 00FF FFFF FF00 0000 0000 0000 0000"            /* ...ˇˇˇˇ......... */
	$"0000 0000 0000 0001 2000 8F00 6F62 6A64"            /* ........ .è.objd */
	$"0000 0040 7374 7874 0000 0009 0032 0010"            /* ...@stxt...∆.2.. */
	$"0101 0000 0000 0000 0052 0000 0050 0000"            /* .........R...P.. */
	$"0000 FFFF FFFF 0000 0000 0000 0000 0000"            /* ..ˇˇˇˇ.......... */
	$"0000 0000 0000 0120 0085 0943 7269 7465"            /* ....... .Ö∆Crite */
	$"7269 613A 656E 6473 6F62 6A64 0000 0048"            /* ria:endsobjd...H */
	$"6173 6372 0000 000A 00CA 00F2 0101 0001"            /* ascr...¬. .Ú.... */
	$"0000 0000 0001 0000 0077 0000 0000 FFFF"            /* .........w....ˇˇ */
	$"FFFF 0000 0001 0000 0001 0000 0000 0000"            /* ˇˇ.............. */
	$"0000 0000 0000 0000 0000 0000 FFFF FFFF"            /* ............ˇˇˇˇ */
	$"0000 0000 0000 000B 6265 6773 6F62 6A64"            /* ........begsobjd */
	$"0000 0043 4254 6276 0000 000B 00B7 00EE"            /* ...CBTbv.....∑.Ó */
	$"0101 0101 0101 0000 0002 0000 0002 0000"            /* ................ */
	$"0000 FFFF FFFF 0000 0000 0000 0000 0000"            /* ..ˇˇˇˇ.......... */
	$"0000 0000 0000 0000 0001 0000 0001 0001"            /* ................ */
	$"0000 196F 0100 0065 6E64 736F 626A 6400"            /* ...o...endsobjd. */
	$"0000 4861 7363 7200 0000 0C00 CA00 F201"            /* ..Hascr..... .Ú. */
	$"0100 0100 0000 0000 CD00 0000 7700 0000"            /* ........Õ...w... */
	$"00FF FFFF FF00 0000 0100 0000 0100 0000"            /* .ˇˇˇˇ........... */
	$"0000 0000 0000 0000 0000 0000 0000 00FF"            /* ...............ˇ */
	$"FFFF FF00 0000 0000 0000 0D62 6567 736F"            /* ˇˇˇ........begso */
	$"626A 6400 0000 4342 5462 7600 0000 0D00"            /* bjd...CBTbv..... */
	$"B700 EE01 0101 0101 0100 0000 0200 0000"            /* ∑.Ó............. */
	$"0200 0000 00FF FFFF FF00 0000 0000 0000"            /* .....ˇˇˇˇ....... */
	$"0000 0000 0000 0000 0000 0000 0100 0000"            /* ................ */
	$"0100 0100 0019 7100 0000 656E 6473 6F62"            /* ......q...endsob */
	$"6A64 0000 0048 6173 6372 0000 000E 00CB"            /* jd...Hascr.....À */
	$"00F2 0101 0001 0000 0000 0199 0000 0077"            /* .Ú.........ô...w */
	$"0000 0000 FFFF FFFF 0000 0001 0000 0001"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 FFFF FFFF 0000 0000 0000 000F 6265"            /* ..ˇˇˇˇ........be */
	$"6773 6F62 6A64 0000 0043 4254 6276 0000"            /* gsobjd...CBTbv.. */
	$"000F 00B8 00EE 0101 0101 0101 0000 0002"            /* ...∏.Ó.......... */
	$"0000 0002 0000 0000 FFFF FFFF 0000 0000"            /* ........ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"0000 0001 0001 0000 1973 0100 0065 6E64"            /* .........s...end */
	$"736F 626A 6400 0000 4273 7478 7400 0000"            /* sobjd...Bstxt... */
	$"0000 9F00 1001 0100 0000 0000 0000 0600"            /* ..ü............. */
	$"0000 6700 0000 00FF FFFF FF00 0000 0000"            /* ..g....ˇˇˇˇ..... */
	$"0000 0000 0000 0000 0000 0001 2000 850B"            /* ............ .Ö. */
	$"4F6E 6C79 2069 6E20 6F6C 646F 626A 6400"            /* Only in oldobjd. */
	$"0000 4273 7478 7400 0000 0000 9F00 1001"            /* ..Bstxt.....ü... */
	$"0100 0000 0000 0001 9E00 0000 6700 0000"            /* ........û...g... */
	$"00FF FFFF FF00 0000 0000 0000 0000 0000"            /* .ˇˇˇˇ........... */
	$"0000 0000 0001 2000 850B 4F6E 6C79 2069"            /* ...... .Ö.Only i */
	$"6E20 6E65 776F 626A 6400 0000 3D73 7478"            /* n newobjd...=stx */
	$"7400 0000 0000 9F00 1001 0100 0000 0000"            /* t.....ü......... */
	$"0000 D200 0000 6700 0000 00FF FFFF FF00"            /* ..“...g....ˇˇˇˇ. */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"2000 8506 4469 6666 6572 6F62 6A64 0000"            /*  .Ö.Differobjd.. */
	$"0051 7467 6278 0000 0014 0263 008A 0101"            /* .Qtgbx.....c.ä.. */
	$"0101 0101 0000 0002 0000 0170 0000 0000"            /* ...........p.... */
	$"FFFF FFFF 0000 0000 0000 0000 0000 0000"            /* ˇˇˇˇ............ */
	$"0000 0000 0000 0001 0000 0001 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 00A0"            /* ...............† */
	$"0000 0062 6567 7364 6F70 6C42 6957 566F"            /* ...begsdoplBiWVo */
	$"626A 6400 0000 5157 6556 7700 0000 0501"            /* bjd...QWeVw..... */
	$"2000 8401 0101 0101 0100 0001 3F00 0000"            /*  .Ñ.........?... */
	$"0600 0000 00FF FFFF FF00 0000 0000 0000"            /* .....ˇˇˇˇ....... */
	$"0000 0000 0000 0000 0000 0000 0100 0000"            /* ................ */
	$"0100 0000 0100 0001 0100 0000 0000 0000"            /* ................ */
	$"0000 0101 008B 0000 646F 706C 5373 6272"            /* .....ã..doplSsbr */
	$"6F62 6A64 0000 0037 7362 6172 0000 0001"            /* objd...7sbar.... */
	$"000F 0084 0101 0001 0101 0000 012A 0000"            /* ...Ñ.........*.. */
	$"0004 0000 0000 FFFF FFFF 0000 1965 0000"            /* ......ˇˇˇˇ...e.. */
	$"0000 0000 0000 0000 0000 0182 0000 0064"            /* ...........Ç...d */
	$"6F70 6C42 6957 566F 626A 6400 0000 5157"            /* oplBiWVobjd...QW */
	$"6556 7700 0000 0401 2000 8401 0101 0100"            /* eVw..... .Ñ..... */
	$"0100 0000 0400 0000 0600 0000 00FF FFFF"            /* .............ˇˇˇ */
	$"FF00 0000 0000 0000 0000 0000 0000 0000"            /* ˇ............... */
	$"0000 0000 0100 0000 0100 0000 0100 0001"            /* ................ */
	$"0100 0000 0000 0000 0000 0101 008B 0000"            /* .............ã.. */
	$"656E 6473 6F62 6A64 0000 0041 7374 7874"            /* endsobjd...Astxt */
	$"0000 0000 0046 000E 0101 0000 0001 0000"            /* .....F.......... */
	$"00B3 0000 0205 0000 0000 FFFF FFFF 0000"            /* .≥........ˇˇˇˇ.. */
	$"0000 0000 0000 0000 0000 0000 0000 0120"            /* ...............  */
	$"008B 0A44 6973 706C 6179 2061 736F 626A"            /* .ã¬Display asobj */
	$"6400 0000 3C72 6770 7600 0000 1900 C800"            /* d...<rgpv.....». */
	$"1001 0100 0000 0100 0000 FB00 0002 0300"            /* ..........˚..... */
	$"0000 00FF FFFF FF00 0000 0000 0000 0000"            /* ...ˇˇˇˇ......... */
	$"0000 0000 0000 0000 0000 0100 0000 0100"            /* ................ */
	$"0062 6567 736F 626A 6400 0000 4672 6275"            /* .begsobjd...Frbu */
	$"7400 0000 1A00 5A00 1001 0100 0000 0000"            /* t.....Z......... */
	$"0000 0500 0000 0000 0000 00FF FFFF FF00"            /* ...........ˇˇˇˇ. */
	$"0019 7E00 0000 0100 0000 0000 0000 0100"            /* ..~............. */
	$"0200 8B0B 6865 7861 6465 6369 6D61 6C00"            /* ..ã.hexadecimal. */
	$"0000 006F 626A 6400 0000 3F72 6275 7400"            /* ...objd...?rbut. */
	$"0000 1B00 4600 1001 0100 0000 0000 0000"            /* ....F........... */
	$"6600 0000 0000 0000 00FF FFFF FF00 0019"            /* f........ˇˇˇˇ... */
	$"7F00 0000 0000 0000 0000 0000 0100 0200"            /* ................ */
	$"8B04 7465 7874 0000 0000 656E 6473 656E"            /* ã.text....endsen */
	$"6473 656E 642E"                                     /* dsend. */
};

data 'PPob' (9550, "Ask Unique ID") {
	$"0002 6F62 6A64 0000 0028 5442 4278 254E"            /* ..objd...(TBBx%N */
	$"0000 08E2 0000 0040 0040 FFFF FFFF FFFF"            /* ...‚...@.@ˇˇˇˇˇˇ */
	$"FFFF 0000 0000 6F6B 2020 636E 636C 6E6F"            /* ˇˇ....ok  cnclno */
	$"2020 6265 6773 6F62 6A64 0000 0012 7774"            /*   begsobjd....wt */
	$"6861 FFFF FFFE 0101 0003 0004 0003 0004"            /* haˇˇˇ˛.......... */
	$"6F62 6A64 0000 0041 7075 7368 6F6B 2020"            /* objd...Apushok   */
	$"0055 0014 0101 0000 0101 0000 00CF 0000"            /* .U...........œ.. */
	$"009C 0000 0000 FFFF FFFF 0000 0384 0000"            /* .ú....ˇˇˇˇ...Ñ.. */
	$"0000 0000 0000 0000 0000 0170 0000 0955"            /* ...........p..∆U */
	$"6E69 7175 6520 4944 016F 626A 6400 0000"            /* nique ID.objd... */
	$"3E70 7573 6863 6E63 6C00 4600 1401 0101"            /* >pushcncl.F..... */
	$"0000 0100 0000 0B00 0000 9C00 0000 00FF"            /* ..........ú....ˇ */
	$"FFFF FF00 0003 8500 0000 0000 0000 0000"            /* ˇˇˇ...Ö......... */
	$"0000 0001 7000 0006 4361 6E63 656C 006F"            /* ....p...Cancel.o */
	$"626A 6400 0000 3F70 7573 686E 6F20 2000"            /* bjd...?pushno  . */
	$"4600 1401 0100 0001 0100 0000 7900 0000"            /* F...........y... */
	$"9C00 0000 00FF FFFF FF00 0025 1E00 0000"            /* ú....ˇˇˇˇ..%.... */
	$"0000 0000 0000 0000 0001 7000 0007 5265"            /* ..........p...Re */
	$"706C 6163 6500 6F62 6A64 0000 0025 6361"            /* place.objd...%ca */
	$"7074 4D45 5347 00F0 0056 0101 0101 0101"            /* ptMESG..V...... */
	$"0000 0037 0000 0014 0000 0000 FFFF FFFF"            /* ...7........ˇˇˇˇ */
	$"0000 9A6F 626A 6400 0000 2469 636E 7000"            /* ..öobjd...$icnp. */
	$"0000 0000 2000 2001 0100 0000 0000 0000"            /* .... . ......... */
	$"0A00 0000 0F00 0000 00FF FFFF FF00 806F"            /* ¬........ˇˇˇˇ.Äo */
	$"626A 6400 0000 6A63 6862 7800 0000 0100"            /* bjd...jchbx..... */
	$"B200 2601 0100 0000 0000 0000 0B00 0000"            /* ≤.&............. */
	$"7100 0000 00FF FFFF FF00 0025 4F00 0000"            /* q....ˇˇˇˇ..%O... */
	$"0000 0000 0000 0000 0201 7100 8233 536F"            /* ..........q.Ç3So */
	$"6C76 6520 7468 6520 636F 6E66 6C69 6374"            /* lve the conflict */
	$"2073 696D 696C 6172 6C79 2066 6F72 2074"            /*  similarly for t */
	$"6865 206E 6578 7420 7265 736F 7572 6365"            /* he next resource */
	$"7365 6E64 7365 6E64 2E"                             /* sendsend. */
};

data 'PPob' (7000, "Preferences Window") {
	$"0002 6F62 6A64 0000 0028 5442 4278 1B58"            /* ..objd...(TBBx.X */
	$"0000 08E2 0000 0040 0040 FFFF FFFF FFFF"            /* ...‚...@.@ˇˇˇˇˇˇ */
	$"FFFF 0000 0000 0000 0001 0000 0002 FFFF"            /* ˇˇ............ˇˇ */
	$"FFFF 6265 6773 6F62 6A64 0000 0012 7774"            /* ˇˇbegsobjd....wt */
	$"6861 FFFF FFFE 0101 0001 0002 0001 0002"            /* haˇˇˇ˛.......... */
	$"6F62 6A64 0000 0040 7075 7368 0000 0001"            /* objd...@push.... */
	$"0050 0014 0101 0000 0101 0000 0169 0000"            /* .P...........i.. */
	$"00FE 0000 0000 FFFF FFFF 0000 0384 0000"            /* .˛....ˇˇˇˇ...Ñ.. */
	$"0000 0000 0000 0000 0000 0170 0000 0856"            /* ...........p...V */
	$"616C 6964 6174 6501 6F62 6A64 0000 003E"            /* alidate.objd...> */
	$"7075 7368 0000 0002 0041 0014 0101 0000"            /* push.....A...... */
	$"0101 0000 011C 0000 00FE 0000 0000 FFFF"            /* .........˛....ˇˇ */
	$"FFFF 0000 0385 0000 0000 0000 0000 0000"            /* ˇˇ...Ö.......... */
	$"0000 0170 0000 0643 616E 6365 6C00 6F62"            /* ...p...Cancel.ob */
	$"6A64 0000 003E 7075 7368 0000 0003 0041"            /* jd...>push.....A */
	$"0014 0101 0100 0001 0000 0009 0000 00FE"            /* ...........∆...˛ */
	$"0000 0000 FFFF FFFF 0000 1B5B 0000 0000"            /* ....ˇˇˇˇ...[.... */
	$"0000 0000 0000 0000 0170 0000 0652 6576"            /* .........p...Rev */
	$"6572 7400 6F62 6A64 0000 0059 7063 746C"            /* ert.objd...Ypctl */
	$"5043 544C 01C2 001E 0101 0100 0100 0000"            /* PCTL.¬.......... */
	$"0000 0000 0000 0000 0000 FFFF FFFF 0000"            /* ..........ˇˇˇˇ.. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0001 0000 0001 0000 0086 5043 544C 03E8"            /* .........ÜPCTL.Ë */
	$"0001 FFFF FFFF FFFF 0000 3333 9999 FFFF"            /* ..ˇˇˇˇˇˇ..33ôôˇˇ */
	$"FFFF 0000 006F 626A 6400 0000 536D 7076"            /* ˇˇ...objd...Smpv */
	$"7750 4D50 5601 8600 D201 0100 0000 0000"            /* wPMPV.Ü.“....... */
	$"0000 1E00 0000 1E00 0000 00FF FFFF FF00"            /* ...........ˇˇˇˇ. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0100 0000 0100 0000 071B BC1C 201C"            /* ............º. . */
	$"841C E81D 4C1D B01E 1400 0150 4354 4C00"            /* Ñ.Ë.L.∞....PCTL. */
	$"656E 6473 656E 642E"                                /* endsend. */
};

data 'PPob' (7100, "General Prefs Pane") {
	$"0002 6F62 6A64 0000 003C 7669 6577 0000"            /* ..objd...<view.. */
	$"0001 0186 00D2 0001 0000 0000 0000 0000"            /* ...Ü.“.......... */
	$"0000 0000 0000 0000 FFFF FFFF 0000 0000"            /* ........ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0000 0010"            /* ................ */
	$"0000 0010 0000 6265 6773 6F62 6A64 0000"            /* ......begsobjd.. */
	$"0058 7467 6278 0000 0000 016C 00B4 0101"            /* .Xtgbx.....l.¥.. */
	$"0000 0000 0000 000D 0000 000E 0000 0000"            /* ................ */
	$"FFFF FFFF 0000 0000 0000 0000 0000 0000"            /* ˇˇˇˇ............ */
	$"0000 0000 0000 0001 0000 0001 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 00A0"            /* ...............† */
	$"0085 0747 656E 6572 616C 6265 6773 6F62"            /* .Ö.Generalbegsob */
	$"6A64 0000 0052 7374 7874 0000 0000 0096"            /* jd...Rstxt.....ñ */
	$"0010 0101 0000 0000 0000 0044 0000 0018"            /* ...........D.... */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0120 0085 1B4D 6178"            /* ......... .Ö.Max */
	$"206E 756D 6265 7220 6F66 2072 6563 656E"            /*  number of recen */
	$"7420 6974 656D 733A 6F62 6A64 0000 003D"            /* t items:objd...= */
	$"6574 7874 0000 0002 001E 0015 0101 0000"            /* etxt............ */
	$"0000 0000 00E0 0000 0014 0000 0000 FFFF"            /* .....‡........ˇˇ */
	$"FFFF 0000 1BBE 0000 0000 0000 0000 0000"            /* ˇˇ...æ.......... */
	$"0000 0110 008C 0231 3000 0220 016F 626A"            /* .....å.10.. .obj */
	$"6400 0000 4E73 7478 7400 0000 0000 8700"            /* d...Nstxt.....á. */
	$"1001 0100 0000 0000 0000 4400 0000 3800"            /* ..........D...8. */
	$"0000 00FF FFFF FF00 0000 0000 0000 0000"            /* ...ˇˇˇˇ......... */
	$"0000 0000 0000 0001 2000 8517 5265 7365"            /* ........ .Ö.Rese */
	$"7420 7265 6365 6E74 2069 7465 6D73 206C"            /* t recent items l */
	$"6973 746F 626A 6400 0000 3D70 7573 6800"            /* istobjd...=push. */
	$"0000 0300 3700 1001 0100 0000 0000 0000"            /* ....7........... */
	$"D500 0000 3500 0000 00FF FFFF FF00 001B"            /* ’...5....ˇˇˇˇ... */
	$"BF00 0000 0000 0000 0000 0000 0001 7000"            /* ø.............p. */
	$"8C05 5265 7365 7400 6F62 6A64 0000 0052"            /* å.Reset.objd...R */
	$"7374 7874 0000 0000 00A0 000E 0101 0000"            /* stxt.....†...... */
	$"0001 0000 0044 0000 005C 0000 0000 FFFF"            /* .....D...\....ˇˇ */
	$"FFFF 0000 0000 0000 0000 0000 0000 0000"            /* ˇˇ.............. */
	$"0000 0120 0085 1B42 7920 6465 6661 756C"            /* ... .Ö.By defaul */
	$"742C 206F 7065 6E20 6E65 7720 6D61 7020"            /* t, open new map  */
	$"696E 6F62 6A64 0000 003C 7267 7076 0000"            /* inobjd...<rgpv.. */
	$"0005 00D2 0016 0101 0000 0001 0000 004D"            /* ...“...........M */
	$"0000 006C 0000 0000 FFFF FFFF 0000 0000"            /* ...l....ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"0000 0001 0000 6265 6773 6F62 6A64 0000"            /* ......begsobjd.. */
	$"0044 7262 7574 0000 0007 0050 0010 0101"            /* .Drbut.....P.... */
	$"0000 0000 0000 0073 0000 0003 0000 0000"            /* .......s........ */
	$"FFFF FFFF 0000 1BC3 0000 0001 0000 0000"            /* ˇˇˇˇ...√........ */
	$"0000 0001 0002 008B 0964 6174 6120 666F"            /* .......ã∆data fo */
	$"726B 0000 0000 6F62 6A64 0000 0048 7262"            /* rk....objd...Hrb */
	$"7574 0000 0006 0064 0010 0101 0000 0000"            /* ut.....d........ */
	$"0000 0005 0000 0003 0000 0000 FFFF FFFF"            /* ............ˇˇˇˇ */
	$"0000 1BC2 0000 0000 0000 0000 0000 0001"            /* ...¬............ */
	$"0002 008B 0D72 6573 6F75 7263 6520 666F"            /* ...ã.resource fo */
	$"726B 0000 0000 656E 6473 656E 6473 656E"            /* rk....endsendsen */
	$"6473 656E 642E"                                     /* dsend. */
};

data 'PPob' (8600, "Set Font Size Dialog") {
	$"0002 6F62 6A64 0000 0028 5442 4278 2198"            /* ..objd...(TBBx!ò */
	$"0000 08E2 0000 0040 0040 FFFF FFFF FFFF"            /* ...‚...@.@ˇˇˇˇˇˇ */
	$"FFFF 0000 0000 6F6B 2020 636E 636C FFFF"            /* ˇˇ....ok  cnclˇˇ */
	$"FFFF 6265 6773 6F62 6A64 0000 0012 7774"            /* ˇˇbegsobjd....wt */
	$"6861 FFFF FFFE 0101 0001 0002 0001 0002"            /* haˇˇˇ˛.......... */
	$"6F62 6A64 0000 003A 7075 7368 6F6B 2020"            /* objd...:pushok   */
	$"0043 0014 0101 0000 0101 0000 00A1 0000"            /* .C...........°.. */
	$"0045 0000 0000 FFFF FFFF 0000 0384 0000"            /* .E....ˇˇˇˇ...Ñ.. */
	$"0000 0000 0000 0000 0000 0170 0000 024F"            /* ...........p...O */
	$"4B01 6F62 6A64 0000 003E 7075 7368 636E"            /* K.objd...>pushcn */
	$"636C 0041 0014 0101 0000 0101 0000 0050"            /* cl.A...........P */
	$"0000 0045 0000 0000 FFFF FFFF 0000 0385"            /* ...E....ˇˇˇˇ...Ö */
	$"0000 0000 0000 0000 0000 0000 0170 0000"            /* .............p.. */
	$"0643 616E 6365 6C00 6F62 6A64 0000 0024"            /* .Cancel.objd...$ */
	$"6963 6E70 0000 0000 0020 0020 0101 0000"            /* icnp..... . .... */
	$"0000 0000 000D 0000 000E 0000 0000 FFFF"            /* ..............ˇˇ */
	$"FFFF 0080 6F62 6A64 0000 0029 6564 6974"            /* ˇˇ.Äobjd...)edit */
	$"5349 5A45 0030 0016 0101 0000 0000 0000"            /* SIZE.0.......... */
	$"009B 0000 0014 0000 0000 FFFF FFFF 0000"            /* .õ........ˇˇˇˇ.. */
	$"8C00 0288 016F 626A 6400 0000 4173 7478"            /* å..à.objd...Astx */
	$"7400 0000 0000 3700 1201 0101 0000 0100"            /* t.....7......... */
	$"0000 6100 0000 1600 0000 00FF FFFF FF00"            /* ..a........ˇˇˇˇ. */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"2000 830A 466F 6E74 2073 697A 653A 656E"            /*  .É¬Font size:en */
	$"6473 656E 642E"                                     /* dsend. */
};

data 'PPob' (10200, "TEXT Editor Window") {
	$"0002 646F 706C 5458 5457 6F62 6A64 0000"            /* ..doplTXTWobjd.. */
	$"001C 7769 6E64 27D8 0002 1F62 0000 00C8"            /* ..wind'ÿ...b...» */
	$"00C8 FFFF FFFF FFFF FFFF 0000 0000 6265"            /* .»ˇˇˇˇˇˇˇˇ....be */
	$"6773 6F62 6A64 0000 0048 6173 6372 5363"            /* gsobjd...HascrSc */
	$"726C 01F4 01F4 0101 0101 0101 0000 0000"            /* rl.Ù.Ù.......... */
	$"0000 0018 0000 0000 FFFF FFFF 0000 0001"            /* ........ˇˇˇˇ.... */
	$"0000 0001 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 000F 0000 000F 436E"            /* ..............Cn */
	$"7473 6265 6773 646F 706C 5458 5456 6F62"            /* tsbegsdoplTXTVob */
	$"6A64 0000 0042 7478 7476 436E 7473 01DC"            /* jd...BtxtvCnts.‹ */
	$"01E0 0101 0101 0101 0000 0004 0000 0003"            /* .‡.............. */
	$"0000 0000 FFFF FFFF 0000 2710 0000 0000"            /* ....ˇˇˇˇ..'..... */
	$"0000 0000 0000 0000 0000 0001 0000 0001"            /* ................ */
	$"0000 EC00 008B 0000 656E 6473 6F62 6A64"            /* ..Ï..ã..endsobjd */
	$"0000 0051 7769 6E68 0000 0000 01F8 0018"            /* ...Qwinh.....¯.. */
	$"0101 0101 0100 FFFF FFFE 0000 0000 0000"            /* ......ˇˇˇ˛...... */
	$"0000 FFFF FFFF 0000 0000 0000 0000 0000"            /* ..ˇˇˇˇ.......... */
	$"0000 0000 0000 0000 0001 0000 0001 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0150 0000 0062 6567 736F 626A 6400 0000"            /* .P...begsobjd... */
	$"3773 7478 744E 616D 6501 E400 0E01 0101"            /* 7stxtName.‰..... */
	$"0101 0000 0000 0A00 0000 0500 0000 00FF"            /* ......¬........ˇ */
	$"FFFF FF00 0000 0000 0000 0000 0000 0000"            /* ˇˇˇ............. */
	$"0000 0001 2000 8200 656E 6473 6F62 6A64"            /* .... .Ç.endsobjd */
	$"0000 0051 7769 6E68 0000 0000 01F4 0019"            /* ...Qwinh.....Ù.. */
	$"0101 0100 0101 0000 0001 0000 020D 0000"            /* ................ */
	$"0000 FFFF FFFF 0000 0000 0000 0000 0000"            /* ..ˇˇˇˇ.......... */
	$"0000 0000 0000 0000 0001 0000 0001 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0150 0000 0062 6567 736F 626A 6400 0000"            /* .P...begsobjd... */
	$"2469 636E 704C 6F63 6B00 1000 1001 0101"            /* $icnpLock....... */
	$"0000 0100 0000 0500 0000 0300 0000 00FF"            /* ...............ˇ */
	$"FFFF FF00 006F 626A 6400 0000 4473 7478"            /* ˇˇˇ..objd...Dstx */
	$"7400 0000 0000 4B00 0E01 0101 0000 0100"            /* t.....K......... */
	$"0000 2F00 0000 0600 0000 00FF FFFF FF00"            /* ../........ˇˇˇˇ. */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"2000 8B0D 546F 7461 6C20 6C65 6E67 7468"            /*  .ã.Total length */
	$"3A6F 626A 6400 0000 3773 7478 7400 0000"            /* :objd...7stxt... */
	$"0100 3C00 0E01 0101 0000 0100 0000 7B00"            /* ..<...........{. */
	$"0000 0600 0000 00FF FFFF FF00 0000 0000"            /* .......ˇˇˇˇ..... */
	$"0000 0000 0000 0000 0000 0001 2000 8B00"            /* ............ .ã. */
	$"656E 6473 656E 6473 656E 642E"                      /* endsendsend. */
};

data 'PPob' (10100, "TMPL Editor Window") {
	$"0002 646F 706C 546D 7057 6F62 6A64 0000"            /* ..doplTmpWobjd.. */
	$"001C 7769 6E64 2774 0002 1F62 0000 017C"            /* ..wind't...b...| */
	$"00C8 FFFF FFFF 01F4 0190 0000 0000 6265"            /* .»ˇˇˇˇ.Ù.ê....be */
	$"6773 6F62 6A64 0000 0049 7363 6C76 5363"            /* gsobjd...IsclvSc */
	$"726C 0208 01F0 0101 0101 0101 0000 0000"            /* rl............. */
	$"0000 0018 0000 0000 FFFF FFFF 0000 0001"            /* ........ˇˇˇˇ.... */
	$"0000 0001 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 FFFF 000F 0000 0000 436E"            /* ......ˇˇ......Cn */
	$"7473 0162 6567 736F 626A 6400 0000 3C76"            /* ts.begsobjd...<v */
	$"6965 7743 6E74 7301 F901 EE01 0101 0101"            /* iewCnts.˘.Ó..... */
	$"0100 0000 0000 0000 0100 0000 00FF FFFF"            /* .............ˇˇˇ */
	$"FF00 0000 0000 0000 0400 0000 0000 0000"            /* ˇ............... */
	$"0000 0000 1400 0000 1400 0165 6E64 736F"            /* ...........endso */
	$"626A 6400 0000 5170 6C63 6400 0000 0002"            /* bjd...Qplcd..... */
	$"0A00 2801 0101 0001 01FF FFFF FF00 0002"            /* ¬.(......ˇˇˇˇ... */
	$"0800 0000 00FF FFFF FF00 0000 0000 0000"            /* .....ˇˇˇˇ....... */
	$"0000 0000 0000 0000 0000 0000 0100 0000"            /* ................ */
	$"0100 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 E000 0000 6265 6773 6F62 6A64"            /* ....‡...begsobjd */
	$"0000 003C 7075 7368 566C 6964 0041 0014"            /* ...<pushVlid.A.. */
	$"0101 0000 0101 0000 01B2 0000 0009 0000"            /* .........≤...∆.. */
	$"0000 FFFF FFFF 0000 0384 0000 0000 0000"            /* ..ˇˇˇˇ...Ñ...... */
	$"0000 0000 0000 0170 0000 0453 6176 6501"            /* .......p...Save. */
	$"6F62 6A64 0000 003E 7075 7368 436E 636C"            /* objd...>pushCncl */
	$"0041 0014 0101 0000 0101 0000 0164 0000"            /* .A...........d.. */
	$"0009 0000 0000 FFFF FFFF 0000 0385 0000"            /* .∆....ˇˇˇˇ...Ö.. */
	$"0000 0000 0000 0000 0000 0170 0000 0643"            /* ...........p...C */
	$"616E 6365 6C00 6F62 6A64 0000 003E 7075"            /* ancel.objd...>pu */
	$"7368 5276 7274 0041 0014 0101 0100 0001"            /* shRvrt.A........ */
	$"0000 001C 0000 0009 0000 0000 FFFF FFFF"            /* .......∆....ˇˇˇˇ */
	$"0000 0007 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0170 0000 0652 6576 6572 7400 6F62 6A64"            /* .p...Revert.objd */
	$"0000 0024 6963 6E70 4C6F 636B 0010 0010"            /* ...$icnpLock.... */
	$"0101 0100 0001 0000 0006 0000 000B 0000"            /* ................ */
	$"0000 FFFF FFFF 0000 656E 6473 6F62 6A64"            /* ..ˇˇˇˇ..endsobjd */
	$"0000 0051 7769 6E68 0000 0000 020C 0018"            /* ...Qwinh........ */
	$"0101 0101 0100 FFFF FFFE 0000 0000 0000"            /* ......ˇˇˇ˛...... */
	$"0000 FFFF FFFF 0000 0000 0000 0000 0000"            /* ..ˇˇˇˇ.......... */
	$"0000 0000 0000 0000 0001 0000 0001 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0150 0000 0062 6567 736F 626A 6400 0000"            /* .P...begsobjd... */
	$"3773 7478 744E 616D 6501 F800 0E01 0101"            /* 7stxtName.¯..... */
	$"0100 0000 0000 0A00 0000 0500 0000 00FF"            /* ......¬........ˇ */
	$"FFFF FF00 0000 0000 0000 0000 0000 0000"            /* ˇˇˇ............. */
	$"0000 0001 2000 8200 656E 6473 656E 6473"            /* .... .Ç.endsends */
	$"656E 642E"                                          /* end. */
};

data 'PPob' (8700, "Resource Type Picker") {
	$"0002 6F62 6A64 0000 0028 5442 4278 21FC"            /* ..objd...(TBBx!¸ */
	$"0000 08E2 0000 0040 0040 FFFF FFFF FFFF"            /* ...‚...@.@ˇˇˇˇˇˇ */
	$"FFFF 0000 0000 6F6B 2020 636E 636C FFFF"            /* ˇˇ....ok  cnclˇˇ */
	$"FFFF 6265 6773 6F62 6A64 0000 0012 7774"            /* ˇˇbegsobjd....wt */
	$"6861 FFFF FFFE 0101 0001 0002 0001 0002"            /* haˇˇˇ˛.......... */
	$"6F62 6A64 0000 003A 7075 7368 6F6B 2020"            /* objd...:pushok   */
	$"0043 0014 0101 0000 0101 0000 00AE 0000"            /* .C...........Æ.. */
	$"005B 0000 0000 FFFF FFFF 0000 0384 0000"            /* .[....ˇˇˇˇ...Ñ.. */
	$"0000 0000 0000 0000 0000 0170 0000 024F"            /* ...........p...O */
	$"4B01 6F62 6A64 0000 003E 7075 7368 636E"            /* K.objd...>pushcn */
	$"636C 0041 0014 0101 0000 0101 0000 005D"            /* cl.A...........] */
	$"0000 005B 0000 0000 FFFF FFFF 0000 0385"            /* ...[....ˇˇˇˇ...Ö */
	$"0000 0000 0000 0000 0000 0000 0170 0000"            /* .............p.. */
	$"0643 616E 6365 6C00 6F62 6A64 0000 0024"            /* .Cancel.objd...$ */
	$"6963 6E70 0000 0000 0020 0020 0101 0000"            /* icnp..... . .... */
	$"0000 0000 000A 0000 000B 0000 0000 FFFF"            /* .....¬........ˇˇ */
	$"FFFF 0080 6F62 6A64 0000 004A 7374 7874"            /* ˇˇ.Äobjd...Jstxt */
	$"0000 0000 0063 0012 0101 0100 0001 0000"            /* .....c.......... */
	$"0043 0000 0017 0000 0000 FFFF FFFF 0000"            /* .C........ˇˇˇˇ.. */
	$"0000 0000 0000 0000 0000 0000 0000 0120"            /* ...............  */
	$"0083 1353 7065 6369 6679 2061 2074 7970"            /* .É.Specify a typ */
	$"6520 6865 7265 6F62 6A64 0000 0051 7374"            /* e hereobjd...Qst */
	$"7874 0000 0000 0085 0013 0101 0100 0001"            /* xt.....Ö........ */
	$"0000 0022 0000 0037 0000 0000 FFFF FFFF"            /* ..."...7....ˇˇˇˇ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0120 0083 1A6F 7220 7365 6C65 6374 2069"            /* . .É.or select i */
	$"7420 6672 6F6D 2074 6865 206D 656E 756F"            /* t from the menuo */
	$"626A 6400 0000 3B65 7478 7400 0000 0100"            /* bjd...;etxt..... */
	$"3200 1501 0100 0000 0000 0000 AF00 0000"            /* 2...........Ø... */
	$"1400 0000 00FF FFFF FF00 0021 FD00 0000"            /* .....ˇˇˇˇ..!˝... */
	$"0000 0000 0000 0000 0001 1000 8C00 0004"            /* ............å... */
	$"2003 6F62 6A64 0000 003D 706F 7062 0000"            /*  .objd...=popb.. */
	$"0002 004B 0013 0101 0000 0000 0000 00AB"            /* ...K...........´ */
	$"0000 0036 0000 0000 FFFF FFFF 0000 21FE"            /* ...6....ˇˇˇˇ..!˛ */
	$"0000 0000 0000 00FD 0000 FFFF 0194 0085"            /* .......˝..ˇˇ.î.Ö */
	$"0000 0000 0000 0165 6E64 7365 6E64 2E"              /* .......endsend. */
};

data 'PPob' (8800, "Template Key Picker") {
	$"0002 6F62 6A64 0000 0028 5442 4278 2260"            /* ..objd...(TBBx"` */
	$"0000 08E2 0000 0040 0040 FFFF FFFF FFFF"            /* ...‚...@.@ˇˇˇˇˇˇ */
	$"FFFF 0000 0000 6F6B 2020 636E 636C FFFF"            /* ˇˇ....ok  cnclˇˇ */
	$"FFFF 6265 6773 6F62 6A64 0000 0012 7774"            /* ˇˇbegsobjd....wt */
	$"6861 FFFF FFFE 0101 0001 0002 0001 0002"            /* haˇˇˇ˛.......... */
	$"6F62 6A64 0000 003A 7075 7368 6F6B 2020"            /* objd...:pushok   */
	$"0043 0014 0101 0000 0101 0000 0122 0000"            /* .C...........".. */
	$"00A4 0000 0000 FFFF FFFF 0000 0384 0000"            /* .§....ˇˇˇˇ...Ñ.. */
	$"0000 0000 0000 0000 0000 0170 0000 024F"            /* ...........p...O */
	$"4B01 6F62 6A64 0000 003E 7075 7368 636E"            /* K.objd...>pushcn */
	$"636C 0041 0014 0101 0000 0101 0000 00D0"            /* cl.A...........– */
	$"0000 00A4 0000 0000 FFFF FFFF 0000 0385"            /* ...§....ˇˇˇˇ...Ö */
	$"0000 0000 0000 0000 0000 0000 0170 0000"            /* .............p.. */
	$"0643 616E 6365 6C00 6F62 6A64 0000 0024"            /* .Cancel.objd...$ */
	$"6963 6E70 0000 0000 0020 0020 0101 0000"            /* icnp..... . .... */
	$"0000 0000 000A 0000 000A 0000 0000 FFFF"            /* .....¬...¬....ˇˇ */
	$"FFFF 0080 6F62 6A64 0000 00D4 7374 7874"            /* ˇˇ.Äobjd...‘stxt */
	$"0000 0002 0152 0030 0101 0101 0100 0000"            /* .....R.0........ */
	$"000F 0000 0034 0000 0000 FFFF FFFF 0000"            /* .....4....ˇˇˇˇ.. */
	$"0000 0000 0000 0000 0000 0000 0000 0120"            /* ...............  */
	$"008C 9D54 6869 7320 7265 736F 7572 6365"            /* .åùThis resource */
	$"2074 7970 6520 6361 6E20 6861 7665 2064"            /*  type can have d */
	$"6966 6665 7265 6E74 2066 6F72 6D61 7473"            /* ifferent formats */
	$"2064 6570 656E 6469 6E67 206F 6E20 7468"            /*  depending on th */
	$"6520 7661 6C75 6520 6F66 2074 6865 2070"            /* e value of the p */
	$"726F 7065 7274 7920 6265 6C6F 772E 2053"            /* roperty below. S */
	$"656C 6563 7420 6F6E 6520 6F66 2074 6865"            /* elect one of the */
	$"2066 6F6C 6C6F 7769 6E67 2076 616C 7565"            /*  following value */
	$"7320 746F 2073 7065 6369 6679 2074 6865"            /* s to specify the */
	$"2064 6573 6972 6564 2066 6F72 6D61 742E"            /*  desired format. */
	$"6F62 6A64 0000 003D 706F 7062 0000 0004"            /* objd...=popb.... */
	$"00AA 0012 0101 0000 0000 0000 0063 0000"            /* .™...........c.. */
	$"007C 0000 0000 FFFF FFFF 0000 2264 0000"            /* .|....ˇˇˇˇ.."d.. */
	$"0000 0000 00FE 0000 FFFF 0194 0085 0000"            /* .....˛..ˇˇ.î.Ö.. */
	$"0000 0000 016F 626A 6400 0000 3773 7478"            /* .....objd...7stx */
	$"7400 0000 0301 0E00 1201 0101 0101 0000"            /* t............... */
	$"0000 5200 0000 6400 0000 00FF FFFF FF00"            /* ..R...d....ˇˇˇˇ. */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"2000 9400 6F62 6A64 0000 0037 7374 7874"            /*  .î.objd...7stxt */
	$"0000 0001 011D 0010 0101 0101 0000 0000"            /* ................ */
	$"003F 0000 0013 0000 0000 FFFF FFFF 0000"            /* .?........ˇˇˇˇ.. */
	$"0000 0000 0000 0000 0000 0000 0000 0120"            /* ...............  */
	$"0093 0065 6E64 7365 6E64 2E"                        /* .ì.endsend. */
};

data 'PPob' (9530, "Explain Error Dialog") {
	$"0002 6F62 6A64 0000 0028 5442 4278 253A"            /* ..objd...(TBBx%: */
	$"0000 08E2 0000 0040 0040 FFFF FFFF FFFF"            /* ...‚...@.@ˇˇˇˇˇˇ */
	$"FFFF 0000 0000 6F6B 2020 FFFF FFFF FFFF"            /* ˇˇ....ok  ˇˇˇˇˇˇ */
	$"FFFF 6265 6773 6F62 6A64 0000 0012 7774"            /* ˇˇbegsobjd....wt */
	$"6861 FFFF FFFE 0101 0003 0004 0003 0004"            /* haˇˇˇ˛.......... */
	$"6F62 6A64 0000 003A 7075 7368 6F6B 2020"            /* objd...:pushok   */
	$"003A 0014 0101 0000 0101 0000 00E8 0000"            /* .:...........Ë.. */
	$"007D 0000 0000 FFFF FFFF 0000 0384 0000"            /* .}....ˇˇˇˇ...Ñ.. */
	$"0000 0000 0000 0000 0000 0170 0000 024F"            /* ...........p...O */
	$"4B01 6F62 6A64 0000 0024 6963 6E70 0000"            /* K.objd...$icnp.. */
	$"0000 0020 0020 0101 0000 0000 0000 000A"            /* ... . .........¬ */
	$"0000 000F 0000 0000 FFFF FFFF 0080 6F62"            /* ........ˇˇˇˇ.Äob */
	$"6A64 0000 0037 7374 7874 4558 504C 00F0"            /* jd...7stxtEXPL. */
	$"0028 0101 0101 0000 0000 0037 0000 004A"            /* .(.........7...J */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0120 0094 006F 626A"            /* ......... .î.obj */
	$"6400 0000 3773 7478 744D 4553 4700 F000"            /* d...7stxtMESG.. */
	$"3201 0101 0100 0000 0000 3700 0000 1900"            /* 2.........7..... */
	$"0000 00FF FFFF FF00 0000 0000 0000 0000"            /* ...ˇˇˇˇ......... */
	$"0000 0000 0000 0001 2000 8C00 656E 6473"            /* ........ .å.ends */
	$"656E 642E"                                          /* end. */
};

data 'PPob' (10400, "PICT Viewer Window") {
	$"0002 646F 706C 5049 4357 6F62 6A64 0000"            /* ..doplPICWobjd.. */
	$"001C 7769 6E64 28A0 0002 1F62 0000 017C"            /* ..wind(†...b...| */
	$"00C8 FFFF FFFF 01F4 0190 0000 0000 6265"            /* .»ˇˇˇˇ.Ù.ê....be */
	$"6773 6F62 6A64 0000 0049 7363 6C76 5363"            /* gsobjd...IsclvSc */
	$"726C 0208 0208 0101 0101 0101 0000 0000"            /* rl.............. */
	$"0000 0000 0000 0000 FFFF FFFF 0000 0001"            /* ........ˇˇˇˇ.... */
	$"0000 0001 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 000F 0000 000F 436E"            /* ..............Cn */
	$"7473 0162 6567 7364 6F70 6C50 4943 566F"            /* ts.begsdoplPICVo */
	$"626A 6400 0000 3C76 6965 7743 6E74 7301"            /* bjd...<viewCnts. */
	$"F801 F801 0101 0101 0100 0000 0100 0000"            /* ¯.¯............. */
	$"0100 0000 00FF FFFF FF00 0000 0000 0000"            /* .....ˇˇˇˇ....... */
	$"0000 0000 0000 0000 0000 0000 0A00 0000"            /* ............¬... */
	$"0A00 0165 6E64 736F 626A 6400 0000 5170"            /* ¬..endsobjd...Qp */
	$"6C63 6400 0000 0002 0A00 1801 0101 0001"            /* lcd.....¬....... */
	$"01FF FFFF FF00 0002 0800 0000 00FF FFFF"            /* .ˇˇˇˇ........ˇˇˇ */
	$"FF00 0000 0000 0000 0000 0000 0000 0000"            /* ˇ............... */
	$"0000 0000 0100 0000 0100 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 E000 0000"            /* ............‡... */
	$"6265 6773 6F62 6A64 0000 0024 6963 6E70"            /* begsobjd...$icnp */
	$"4C6F 636B 0010 0010 0101 0100 0001 0000"            /* Lock............ */
	$"0004 0000 0003 0000 0000 FFFF FFFF 0000"            /* ..........ˇˇˇˇ.. */
	$"6F62 6A64 0000 0037 7374 7874 0000 0002"            /* objd...7stxt.... */
	$"0028 000E 0101 0100 0001 0000 0034 0000"            /* .(...........4.. */
	$"0007 0000 0000 FFFF FFFF 0000 0000 0000"            /* ......ˇˇˇˇ...... */
	$"0000 0000 0000 0000 0000 0120 0082 006F"            /* ........... .Ç.o */
	$"626A 6400 0000 3773 7478 7400 0000 0300"            /* bjd...7stxt..... */
	$"2800 0E01 0101 0000 0100 0000 7200 0000"            /* (...........r... */
	$"0700 0000 00FF FFFF FF00 0000 0000 0000"            /* .....ˇˇˇˇ....... */
	$"0000 0000 0000 0000 0001 2000 8200 6F62"            /* .......... .Ç.ob */
	$"6A64 0000 0039 7374 7874 0000 0000 000E"            /* jd...9stxt...... */
	$"000E 0101 0100 0001 0000 0026 0000 0007"            /* ...........&.... */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0120 008B 0277 3A6F"            /* ......... .ã.w:o */
	$"626A 6400 0000 3973 7478 7400 0000 0000"            /* bjd...9stxt..... */
	$"0E00 0E01 0101 0000 0100 0000 6400 0000"            /* ............d... */
	$"0700 0000 00FF FFFF FF00 0000 0000 0000"            /* .....ˇˇˇˇ....... */
	$"0000 0000 0000 0000 0001 2000 8B02 683A"            /* .......... .ã.h: */
	$"656E 6473 656E 6473 656E 642E"                      /* endsendsend. */
};

data 'PPob' (10500, "UTXT Editor Window") {
	$"0002 646F 706C 5554 5857 6F62 6A64 0000"            /* ..doplUTXWobjd.. */
	$"001C 7769 6E64 2904 0002 1F62 0000 01F4"            /* ..wind)....b...Ù */
	$"00C8 FFFF FFFF FFFF FFFF 0000 0000 6265"            /* .»ˇˇˇˇˇˇˇˇ....be */
	$"6773 6F62 6A64 0000 0051 7769 6E68 0000"            /* gsobjd...Qwinh.. */
	$"0000 01F8 0018 0101 0101 0100 FFFF FFFE"            /* ...¯........ˇˇˇ˛ */
	$"0000 0000 0000 0000 FFFF FFFF 0000 0000"            /* ........ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"0000 0001 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0150 0000 0062 6567 736F"            /* .......P...begso */
	$"626A 6400 0000 3773 7478 744E 616D 6501"            /* bjd...7stxtName. */
	$"E400 0E01 0101 0100 0000 0000 0A00 0000"            /* ‰...........¬... */
	$"0500 0000 00FF FFFF FF00 0000 0000 0000"            /* .....ˇˇˇˇ....... */
	$"0000 0000 0000 0000 0001 2000 8200 656E"            /* .......... .Ç.en */
	$"6473 6F62 6A64 0000 0051 7769 6E68 0000"            /* dsobjd...Qwinh.. */
	$"0000 01F4 0014 0101 0100 0101 0000 0000"            /* ...Ù............ */
	$"0000 020A 0000 0000 FFFF FFFF 0000 0000"            /* ...¬....ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"0000 0001 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0150 0000 0062 6567 736F"            /* .......P...begso */
	$"626A 6400 0000 2469 636E 704C 6F63 6B00"            /* bjd...$icnpLock. */
	$"1000 1001 0101 0000 0100 0000 0500 0000"            /* ................ */
	$"0200 0000 00FF FFFF FF00 006F 626A 6400"            /* .....ˇˇˇˇ..objd. */
	$"0000 4373 7478 7400 0000 0000 4600 0E01"            /* ..Cstxt.....F... */
	$"0101 0000 0100 0000 2F00 0000 0400 0000"            /* ......../....... */
	$"00FF FFFF FF00 0000 0000 0000 0000 0000"            /* .ˇˇˇˇ........... */
	$"0000 0000 0001 2000 8B0C 4279 7465 7320"            /* ...... .ã.Bytes  */
	$"636F 756E 743A 6F62 6A64 0000 0037 7374"            /* count:objd...7st */
	$"7874 0000 0004 003C 000E 0101 0100 0001"            /* xt.....<........ */
	$"0000 0075 0000 0004 0000 0000 FFFF FFFF"            /* ...u........ˇˇˇˇ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0120 008B 0065 6E64 7364 6F70 6C55 5458"            /* . .ã.endsdoplUTX */
	$"566F 626A 6400 0000 326D 6C74 6543 6E74"            /* Vobjd...2mlteCnt */
	$"7301 EC01 EC01 0101 0101 0100 0000 0400"            /* s.Ï.Ï........... */
	$"0000 1B00 0000 00FF FFFF FF00 001A 0800"            /* .......ˇˇˇˇ..... */
	$"0000 0154 4558 5400 0000 0065 6E64 7365"            /* ...TEXT....endse */
	$"6E64 2E"                                            /* nd. */
};

data 'PPob' (10600, "Icon Family Editor Window") {
	$"0002 646F 706C 4661 6D56 6F62 6A64 0000"            /* ..doplFamVobjd.. */
	$"001C 7769 6E64 2968 0002 1862 0000 0190"            /* ..wind)h...b...ê */
	$"0190 FFFF FFFF 023A 0190 0000 0000 6265"            /* .êˇˇˇˇ.:.ê....be */
	$"6773 6F62 6A64 0000 0051 706C 6364 0000"            /* gsobjd...Qplcd.. */
	$"0000 0236 0164 0101 0101 0101 0000 0000"            /* ...6.d.......... */
	$"0000 0000 0000 0000 FFFF FFFF 0000 0000"            /* ........ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"0000 0001 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0150 0000 0062 6567 736F"            /* .......P...begso */
	$"626A 6400 0000 4A44 6362 6274 4C41 5300"            /* bjd...JDcbbtLAS. */
	$"1800 1801 0100 0000 0000 0000 0F00 0000"            /* ................ */
	$"0C00 0000 00FF FFFF FF74 4C41 5300 0000"            /* .....ˇˇˇˇtLAS... */
	$"0000 0001 0100 0023 2800 2100 0000 0000"            /* .......#(.!..... */
	$"0000 0000 0000 0000 0000 0000 0044 436C"            /* .............DCl */
	$"6B6F 626A 6400 0000 4A44 6362 6274 5345"            /* kobjd...JDcbbtSE */
	$"4C00 1800 1801 0100 0000 0000 0000 2900"            /* L.............). */
	$"0000 0C00 0000 00FF FFFF FF74 5345 4C00"            /* .......ˇˇˇˇtSEL. */
	$"0000 0000 0001 0100 0023 2900 2100 0000"            /* .........#).!... */
	$"0000 0000 0000 0000 0000 0000 0000 0044"            /* ...............D */
	$"436C 6B6F 626A 6400 0000 4662 6275 7474"            /* Clkobjd...Fbbutt */
	$"5458 5400 1800 1801 0100 0000 0000 0000"            /* TXT............. */
	$"0F00 0000 2600 0000 00FF FFFF FF74 5458"            /* ....&....ˇˇˇˇtTX */
	$"5400 0000 0000 0001 0100 0023 2A00 2100"            /* T..........#*.!. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"006F 626A 6400 0000 4662 6275 7474 5045"            /* .objd...FbbuttPE */
	$"4E00 1800 1801 0100 0000 0000 0000 2900"            /* N.............). */
	$"0000 2600 0000 00FF FFFF FF74 5045 4E00"            /* ..&....ˇˇˇˇtPEN. */
	$"0000 0000 0001 0100 0023 2B00 2100 0000"            /* .........#+.!... */
	$"0000 0000 0000 0000 0000 0000 0000 006F"            /* ...............o */
	$"626A 6400 0000 4A44 6362 6274 4552 4100"            /* bjd...JDcbbtERA. */
	$"1800 1801 0100 0000 0000 0000 0F00 0000"            /* ................ */
	$"4000 0000 00FF FFFF FF74 4552 4100 0000"            /* @....ˇˇˇˇtERA... */
	$"0000 0001 0100 0023 2C00 2100 0000 0000"            /* .......#,.!..... */
	$"0000 0000 0000 0000 0000 0000 0044 436C"            /* .............DCl */
	$"6B6F 626A 6400 0000 4662 6275 7474 4255"            /* kobjd...FbbuttBU */
	$"4300 1800 1801 0100 0000 0000 0000 2900"            /* C.............). */
	$"0000 4000 0000 00FF FFFF FF74 4255 4300"            /* ..@....ˇˇˇˇtBUC. */
	$"0000 0000 0001 0100 0023 2D00 2100 0000"            /* .........#-.!... */
	$"0000 0000 0000 0000 0000 0000 0000 006F"            /* ...............o */
	$"626A 6400 0000 4662 6275 7474 4452 4F00"            /* bjd...FbbuttDRO. */
	$"1800 1801 0100 0000 0000 0000 0F00 0000"            /* ................ */
	$"5A00 0000 00FF FFFF FF74 4452 4F00 0000"            /* Z....ˇˇˇˇtDRO... */
	$"0000 0001 0100 0023 2E00 2100 0000 0000"            /* .......#..!..... */
	$"0000 0000 0000 0000 0000 0000 006F 626A"            /* .............obj */
	$"6400 0000 4662 6275 7474 4C49 4E00 1800"            /* d...FbbuttLIN... */
	$"1801 0100 0000 0000 0000 2900 0000 5A00"            /* ..........)...Z. */
	$"0000 00FF FFFF FF74 4C49 4E00 0000 0000"            /* ...ˇˇˇˇtLIN..... */
	$"0001 0100 0023 2F00 2100 0000 0000 0000"            /* .....#/.!....... */
	$"0000 0000 0000 0000 0000 006F 626A 6400"            /* ...........objd. */
	$"0000 4662 6275 7474 5245 4300 1800 1801"            /* ..FbbuttREC..... */
	$"0100 0000 0000 0000 0F00 0000 7400 0000"            /* ............t... */
	$"00FF FFFF FF74 5245 4300 0000 0000 0001"            /* .ˇˇˇˇtREC....... */
	$"0100 0023 3100 2100 0000 0000 0000 0000"            /* ...#1.!......... */
	$"0000 0000 0000 0000 006F 626A 6400 0000"            /* .........objd... */
	$"4662 6275 7474 4652 4300 1800 1801 0100"            /* FbbuttFRC....... */
	$"0000 0000 0000 2900 0000 7400 0000 00FF"            /* ......)...t....ˇ */
	$"FFFF FF74 4652 4300 0000 0000 0001 0100"            /* ˇˇˇtFRC......... */
	$"0023 3000 2100 0000 0000 0000 0000 0000"            /* .#0.!........... */
	$"0000 0000 0000 006F 626A 6400 0000 4662"            /* .......objd...Fb */
	$"6275 7474 5252 4300 1800 1801 0100 0000"            /* buttRRC......... */
	$"0000 0000 0F00 0000 8E00 0000 00FF FFFF"            /* ........é....ˇˇˇ */
	$"FF74 5252 4300 0000 0000 0001 0100 0023"            /* ˇtRRC..........# */
	$"3300 2100 0000 0000 0000 0000 0000 0000"            /* 3.!............. */
	$"0000 0000 006F 626A 6400 0000 4662 6275"            /* .....objd...Fbbu */
	$"7474 4652 5200 1800 1801 0100 0000 0000"            /* ttFRR........... */
	$"0000 2900 0000 8E00 0000 00FF FFFF FF74"            /* ..)...é....ˇˇˇˇt */
	$"4652 5200 0000 0000 0001 0100 0023 3200"            /* FRR..........#2. */
	$"2100 0000 0000 0000 0000 0000 0000 0000"            /* !............... */
	$"0000 006F 626A 6400 0000 4662 6275 7474"            /* ...objd...Fbbutt */
	$"4F56 4C00 1800 1801 0100 0000 0000 0000"            /* OVL............. */
	$"0F00 0000 A800 0000 00FF FFFF FF74 4F56"            /* ....®....ˇˇˇˇtOV */
	$"4C00 0000 0000 0001 0100 0023 3500 2100"            /* L..........#5.!. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"006F 626A 6400 0000 4662 6275 7474 464F"            /* .objd...FbbuttFO */
	$"5600 1800 1801 0100 0000 0000 0000 2900"            /* V.............). */
	$"0000 A800 0000 00FF FFFF FF74 464F 5600"            /* ..®....ˇˇˇˇtFOV. */
	$"0000 0000 0001 0100 0023 3400 2100 0000"            /* .........#4.!... */
	$"0000 0000 0000 0000 0000 0000 0000 0064"            /* ...............d */
	$"6F70 6C50 6174 506F 626A 6400 0000 4662"            /* oplPatPobjd...Fb */
	$"6275 7474 5041 5400 3200 1201 0100 0000"            /* buttPAT.2....... */
	$"0000 0000 0F00 0000 CC00 0003 E8FF FFFF"            /* ........Ã...Ëˇˇˇ */
	$"FF74 5041 5400 0000 0000 0000 0000 0000"            /* ˇtPAT........... */
	$"0000 2100 0000 0000 0000 0000 0000 0000"            /* ..!............. */
	$"0000 0000 006F 626A 6400 0000 4E43 6F6C"            /* .....objd...NCol */
	$"5074 4243 4C00 2800 1001 0101 0100 0000"            /* PtBCL.(......... */
	$"0000 1B00 0000 F500 FFFF FFFF FFFF FF74"            /* ......ı.ˇˇˇˇˇˇˇt */
	$"4243 4C00 0000 0000 0000 0000 0000 0000"            /* BCL............. */
	$"2100 0000 0000 0000 0000 0000 0000 0000"            /* !............... */
	$"0000 00FF FFFF FFFF FF01 006F 626A 6400"            /* ...ˇˇˇˇˇˇ..objd. */
	$"0000 4E43 6F6C 5074 4643 4C00 2800 1001"            /* ..NColPtFCL.(... */
	$"0101 0100 0000 0000 0F00 0000 E800 0000"            /* ............Ë... */
	$"00FF FFFF FF74 4643 4C00 0000 0000 0000"            /* .ˇˇˇˇtFCL....... */
	$"0000 0000 0000 2100 0000 0000 0000 0000"            /* ......!......... */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"006F 626A 6400 0000 5174 6762 7845 4E43"            /* .objd...QtgbxENC */
	$"4C01 5A01 5A01 0101 0100 0000 0000 5000"            /* L.Z.Z.........P. */
	$"0000 0A00 0000 00FF FFFF FF00 0000 0000"            /* ..¬....ˇˇˇˇ..... */
	$"0000 0000 0000 0000 0000 0000 0000 0100"            /* ................ */
	$"0000 0100 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 A000 0000 6265 6773 646F"            /* ......†...begsdo */
	$"706C 4943 4E56 6F62 6A64 0000 003C 7669"            /* plICNVobjd...<vi */
	$"6577 436E 7473 0152 0152 0101 0101 0101"            /* ewCnts.R.R...... */
	$"0000 0004 0000 0004 0000 0000 FFFF FFFF"            /* ............ˇˇˇˇ */
	$"0000 0000 0000 0004 0000 0000 0000 0000"            /* ................ */
	$"0000 0014 0000 0014 0001 656E 6473 6F62"            /* ..........endsob */
	$"6A64 0000 003C 7669 6577 5341 4D50 0078"            /* jd...<viewSAMP.x */
	$"0140 0101 0000 0000 0000 01B3 0000 000C"            /* .@.........≥.... */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0000 0001 0000 0001"            /* ................ */
	$"0000 6265 6773 646F 706C 4454 5677 6F62"            /* ..begsdoplDTVwob */
	$"6A64 0000 003C 7669 6577 6963 6C38 002C"            /* jd...<viewicl8., */
	$"0038 0101 0000 0000 0000 0004 0000 0007"            /* .8.............. */
	$"0000 0002 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0000 0001 0000 0001"            /* ................ */
	$"0000 6F62 6A64 0000 003B 7374 7874 0000"            /* ..objd...;stxt.. */
	$"0000 002C 0010 0101 0000 0000 0000 0004"            /* ...,............ */
	$"0000 003F 0000 0000 FFFF FFFF 0000 0000"            /* ...?....ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0120 008D"            /* ............. .ç */
	$"0469 636C 3864 6F70 6C44 5456 776F 626A"            /* .icl8doplDTVwobj */
	$"6400 0000 3C76 6965 7769 6373 3800 1C00"            /* d...<viewics8... */
	$"2801 0100 0000 0000 0000 3600 0000 0F00"            /* (.........6..... */
	$"0000 02FF FFFF FF00 0000 0000 0000 0000"            /* ...ˇˇˇˇ......... */
	$"0000 0000 0000 0000 0000 0100 0000 0100"            /* ................ */
	$"006F 626A 6400 0000 3B73 7478 7400 0000"            /* .objd...;stxt... */
	$"0000 2000 1001 0100 0000 0000 0000 3400"            /* .. ...........4. */
	$"0000 3F00 0000 00FF FFFF FF00 0000 0000"            /* ..?....ˇˇˇˇ..... */
	$"0000 0000 0000 0000 0000 0001 2000 8D04"            /* ............ .ç. */
	$"6963 7338 646F 706C 4454 5677 6F62 6A64"            /* ics8doplDTVwobjd */
	$"0000 003C 7669 6577 6963 6D38 001C 0024"            /* ...<viewicm8...$ */
	$"0101 0000 0000 0000 0058 0000 0011 0000"            /* .........X...... */
	$"0002 FFFF FFFF 0000 0000 0000 0000 0000"            /* ..ˇˇˇˇ.......... */
	$"0000 0000 0000 0000 0001 0000 0001 0000"            /* ................ */
	$"6F62 6A64 0000 003B 7374 7874 0000 0000"            /* objd...;stxt.... */
	$"0020 0010 0101 0000 0000 0000 0056 0000"            /* . ...........V.. */
	$"003F 0000 0000 FFFF FFFF 0000 0000 0000"            /* .?....ˇˇˇˇ...... */
	$"0000 0000 0000 0000 0000 0120 008D 0469"            /* ........... .ç.i */
	$"636D 3864 6F70 6C44 5456 776F 626A 6400"            /* cm8doplDTVwobjd. */
	$"0000 3C76 6965 7769 636C 3400 2C00 3801"            /* ..<viewicl4.,.8. */
	$"0100 0000 0000 0000 0400 0000 5400 0000"            /* ............T... */
	$"02FF FFFF FF00 0000 0000 0000 0000 0000"            /* .ˇˇˇˇ........... */
	$"0000 0000 0000 0000 0100 0000 0100 006F"            /* ...............o */
	$"626A 6400 0000 3B73 7478 7400 0000 0000"            /* bjd...;stxt..... */
	$"2C00 1001 0100 0000 0000 0000 0400 0000"            /* ,............... */
	$"8B00 0000 00FF FFFF FF00 0000 0000 0000"            /* ã....ˇˇˇˇ....... */
	$"0000 0000 0000 0000 0001 2000 8D04 6963"            /* .......... .ç.ic */
	$"6C34 646F 706C 4454 5677 6F62 6A64 0000"            /* l4doplDTVwobjd.. */
	$"003C 7669 6577 6963 7334 001C 0028 0101"            /* .<viewics4...(.. */
	$"0000 0000 0000 0036 0000 005C 0000 0002"            /* .......6...\.... */
	$"FFFF FFFF 0000 0000 0000 0000 0000 0000"            /* ˇˇˇˇ............ */
	$"0000 0000 0000 0001 0000 0001 0000 6F62"            /* ..............ob */
	$"6A64 0000 003B 7374 7874 0000 0000 0020"            /* jd...;stxt.....  */
	$"0010 0101 0000 0000 0000 0034 0000 008B"            /* ...........4...ã */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0120 008D 0469 6373"            /* ......... .ç.ics */
	$"3464 6F70 6C44 5456 776F 626A 6400 0000"            /* 4doplDTVwobjd... */
	$"3C76 6965 7769 636D 3400 1C00 2401 0100"            /* <viewicm4...$... */
	$"0000 0000 0000 5800 0000 5E00 0000 02FF"            /* ......X...^....ˇ */
	$"FFFF FF00 0000 0000 0000 0000 0000 0000"            /* ˇˇˇ............. */
	$"0000 0000 0000 0100 0000 0100 006F 626A"            /* .............obj */
	$"6400 0000 3B73 7478 7400 0000 0000 2000"            /* d...;stxt..... . */
	$"1001 0100 0000 0000 0000 5600 0000 8B00"            /* ..........V...ã. */
	$"0000 00FF FFFF FF00 0000 0000 0000 0000"            /* ...ˇˇˇˇ......... */
	$"0000 0000 0000 0001 2000 8D04 6963 6D34"            /* ........ .ç.icm4 */
	$"646F 706C 4454 5677 6F62 6A64 0000 003C"            /* doplDTVwobjd...< */
	$"7669 6577 4943 4E23 002C 0038 0101 0000"            /* viewICN#.,.8.... */
	$"0000 0000 0004 0000 00A2 0000 0002 FFFF"            /* .........¢....ˇˇ */
	$"FFFF 0000 0000 0000 0000 0000 0000 0000"            /* ˇˇ.............. */
	$"0000 0000 0001 0000 0001 0000 6F62 6A64"            /* ............objd */
	$"0000 003B 7374 7874 0000 0000 002C 0010"            /* ...;stxt.....,.. */
	$"0101 0000 0000 0000 0004 0000 00D9 0000"            /* .............Ÿ.. */
	$"0000 FFFF FFFF 0000 0000 0000 0000 0000"            /* ..ˇˇˇˇ.......... */
	$"0000 0000 0000 0120 008D 0449 434E 2364"            /* ....... .ç.ICN#d */
	$"6F70 6C44 5456 776F 626A 6400 0000 3C76"            /* oplDTVwobjd...<v */
	$"6965 7769 6373 2300 1C00 2801 0100 0000"            /* iewics#...(..... */
	$"0000 0000 3600 0000 AA00 0000 02FF FFFF"            /* ....6...™....ˇˇˇ */
	$"FF00 0000 0000 0000 0000 0000 0000 0000"            /* ˇ............... */
	$"0000 0000 0100 0000 0100 006F 626A 6400"            /* ...........objd. */
	$"0000 3B73 7478 7400 0000 0000 2000 1001"            /* ..;stxt..... ... */
	$"0100 0000 0000 0000 3400 0000 D900 0000"            /* ........4...Ÿ... */
	$"00FF FFFF FF00 0000 0000 0000 0000 0000"            /* .ˇˇˇˇ........... */
	$"0000 0000 0001 2000 8D04 6963 7323 646F"            /* ...... .ç.ics#do */
	$"706C 4454 5677 6F62 6A64 0000 003C 7669"            /* plDTVwobjd...<vi */
	$"6577 6963 6D23 001C 0024 0101 0000 0000"            /* ewicm#...$...... */
	$"0000 0058 0000 00AC 0000 0002 FFFF FFFF"            /* ...X...¨....ˇˇˇˇ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0001 0000 0001 0000 6F62 6A64 0000"            /* ..........objd.. */
	$"003B 7374 7874 0000 0000 0020 0010 0101"            /* .;stxt..... .... */
	$"0000 0000 0000 0056 0000 00D9 0000 0000"            /* .......V...Ÿ.... */
	$"FFFF FFFF 0000 0000 0000 0000 0000 0000"            /* ˇˇˇˇ............ */
	$"0000 0000 0120 008D 0469 636D 2364 6F70"            /* ..... .ç.icm#dop */
	$"6C44 5456 776F 626A 6400 0000 3C76 6965"            /* lDTVwobjd...<vie */
	$"774D 534B 3100 2C00 3801 0100 0000 0000"            /* wMSK1.,.8....... */
	$"0000 0400 0000 F000 0000 03FF FFFF FF00"            /* ..........ˇˇˇˇ. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0100 0000 0100 0064 6F70 6C44 5456"            /* .........doplDTV */
	$"776F 626A 6400 0000 3C76 6965 774D 534B"            /* wobjd...<viewMSK */
	$"3200 1C00 2801 0100 0000 0000 0000 3600"            /* 2...(.........6. */
	$"0000 F800 0000 03FF FFFF FF00 0000 0000"            /* ..¯....ˇˇˇˇ..... */
	$"0000 0000 0000 0000 0000 0000 0000 0100"            /* ................ */
	$"0000 0100 0064 6F70 6C44 5456 776F 626A"            /* .....doplDTVwobj */
	$"6400 0000 3C76 6965 774D 534B 3300 1C00"            /* d...<viewMSK3... */
	$"2401 0100 0000 0000 0000 5800 0000 FA00"            /* $.........X...˙. */
	$"0000 03FF FFFF FF00 0000 0000 0000 0000"            /* ...ˇˇˇˇ......... */
	$"0000 0000 0000 0000 0000 0100 0000 0100"            /* ................ */
	$"006F 626A 6400 0000 3C73 7478 7400 0000"            /* .objd...<stxt... */
	$"0000 7000 1001 0100 0000 0000 0000 0400"            /* ..p............. */
	$"0001 2800 0000 00FF FFFF FF00 0000 0000"            /* ..(....ˇˇˇˇ..... */
	$"0000 0000 0000 0000 0000 0001 2000 8D05"            /* ............ .ç. */
	$"4D61 736B 7365 6E64 736F 626A 6400 0000"            /* Masksendsobjd... */
	$"3773 7478 7443 4F4F 5200 3C00 1001 0100"            /* 7stxtCOOR.<..... */
	$"0000 0000 0000 0A00 0001 5300 0000 00FF"            /* ......¬...S....ˇ */
	$"FFFF FF00 0000 0000 0000 0000 0000 0000"            /* ˇˇˇ............. */
	$"0000 0001 2000 0000 656E 6473 6F62 6A64"            /* .... ...endsobjd */
	$"0000 0051 706C 6364 464F 4F54 0236 0028"            /* ...QplcdFOOT.6.( */
	$"0101 0100 0101 0000 0000 0000 0164 0000"            /* .............d.. */
	$"0000 FFFF FFFF 0000 0000 0000 0000 0000"            /* ..ˇˇˇˇ.......... */
	$"0000 0000 0000 0000 0001 0000 0001 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"00E0 0000 0062 6567 736F 626A 6400 0000"            /* .‡...begsobjd... */
	$"3C70 7573 6856 6C69 6400 4100 1401 0100"            /* <pushVlid.A..... */
	$"0001 0100 0001 E900 0000 0900 0000 00FF"            /* ......È...∆....ˇ */
	$"FFFF FF00 0003 8400 0000 0000 0000 0000"            /* ˇˇˇ...Ñ......... */
	$"0000 0001 7000 0004 5361 7665 016F 626A"            /* ....p...Save.obj */
	$"6400 0000 3E70 7573 6843 6E63 6C00 4100"            /* d...>pushCncl.A. */
	$"1401 0100 0001 0100 0001 9D00 0000 0900"            /* ..........ù...∆. */
	$"0000 00FF FFFF FF00 0003 8500 0000 0000"            /* ...ˇˇˇˇ...Ö..... */
	$"0000 0000 0000 0001 7000 0006 4361 6E63"            /* ........p...Canc */
	$"656C 006F 626A 6400 0000 3E70 7573 6852"            /* el.objd...>pushR */
	$"7672 7400 4100 1401 0101 0000 0100 0000"            /* vrt.A........... */
	$"1C00 0000 0900 0000 00FF FFFF FF00 0000"            /* ....∆....ˇˇˇˇ... */
	$"0700 0000 0000 0000 0000 0000 0001 7000"            /* ..............p. */
	$"0006 5265 7665 7274 006F 626A 6400 0000"            /* ..Revert.objd... */
	$"2469 636E 704C 6F63 6B00 1000 1001 0101"            /* $icnpLock....... */
	$"0000 0100 0000 0600 0000 0B00 0000 00FF"            /* ...............ˇ */
	$"FFFF FF00 0065 6E64 7365 6E64 7365 6E64"            /* ˇˇˇ..endsendsend */
	$"2E"                                                 /* . */
};

data 'PPob' (8900, "Set Image Size Dialog") {
	$"0002 6F62 6A64 0000 0028 5442 4278 22C4"            /* ..objd...(TBBx"ƒ */
	$"0000 08E2 0000 0040 0040 FFFF FFFF FFFF"            /* ...‚...@.@ˇˇˇˇˇˇ */
	$"FFFF 0000 0000 6F6B 2020 636E 636C FFFF"            /* ˇˇ....ok  cnclˇˇ */
	$"FFFF 6265 6773 6F62 6A64 0000 0012 7774"            /* ˇˇbegsobjd....wt */
	$"6861 FFFF FFFE 0101 0001 0002 0001 0002"            /* haˇˇˇ˛.......... */
	$"6F62 6A64 0000 003A 7075 7368 6F6B 2020"            /* objd...:pushok   */
	$"0043 0014 0101 0000 0101 0000 00A1 0000"            /* .C...........°.. */
	$"0045 0000 0000 FFFF FFFF 0000 0384 0000"            /* .E....ˇˇˇˇ...Ñ.. */
	$"0000 0000 0000 0000 0000 0170 0000 024F"            /* ...........p...O */
	$"4B01 6F62 6A64 0000 003E 7075 7368 636E"            /* K.objd...>pushcn */
	$"636C 0041 0014 0101 0000 0101 0000 0050"            /* cl.A...........P */
	$"0000 0045 0000 0000 FFFF FFFF 0000 0385"            /* ...E....ˇˇˇˇ...Ö */
	$"0000 0000 0000 0000 0000 0000 0170 0000"            /* .............p.. */
	$"0643 616E 6365 6C00 6F62 6A64 0000 0024"            /* .Cancel.objd...$ */
	$"6963 6E70 0000 0000 0020 0020 0101 0000"            /* icnp..... . .... */
	$"0000 0000 000D 0000 000E 0000 0000 FFFF"            /* ..............ˇˇ */
	$"FFFF 0080 6F62 6A64 0000 003C 7462 6776"            /* ˇˇ.Äobjd...<tbgv */
	$"0000 0000 008B 0037 0101 0000 0000 0000"            /* .....ã.7........ */
	$"0055 0000 0004 0000 0000 FFFF FFFF 0000"            /* .U........ˇˇˇˇ.. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0001 0000 0001 0000 6265 6773 6F62 6A64"            /* ........begsobjd */
	$"0000 0029 6564 6974 5749 4454 0048 0010"            /* ...)editWIDT.H.. */
	$"0101 0000 0000 0000 0037 0000 000A 0000"            /* .........7...¬.. */
	$"0000 FFFF FFFF 0000 8C00 0480 016F 626A"            /* ..ˇˇˇˇ..å..Ä.obj */
	$"6400 0000 2965 6469 7448 4549 4700 4800"            /* d...)editHEIG.H. */
	$"1001 0100 0000 0000 0000 3700 0000 1E00"            /* ..........7..... */
	$"0000 00FF FFFF FF00 008C 0004 8001 656E"            /* ...ˇˇˇˇ..å..Ä.en */
	$"6473 6F62 6A64 0000 002B 6361 7074 0000"            /* dsobjd...+capt.. */
	$"0000 002D 000F 0101 0000 0000 0000 005D"            /* ...-...........] */
	$"0000 000F 0000 0000 FFFF FFFF 0657 6964"            /* ........ˇˇˇˇ.Wid */
	$"7468 3A00 836F 626A 6400 0000 2C63 6170"            /* th:.Éobjd...,cap */
	$"7400 0000 0000 2D00 0F01 0100 0000 0000"            /* t.....-......... */
	$"0000 5D00 0000 2300 0000 00FF FFFF FF07"            /* ..]...#....ˇˇˇˇ. */
	$"4865 6967 6874 3A00 8365 6E64 7365 6E64"            /* Height:.Éendsend */
	$"2E"                                                 /* . */
};

data 'PPob' (10601, "Cicn Editor Window") {
	$"0002 646F 706C 4963 6E56 6F62 6A64 0000"            /* ..doplIcnVobjd.. */
	$"001C 7769 6E64 2969 0002 1862 0000 0190"            /* ..wind)i...b...ê */
	$"0190 FFFF FFFF 0208 0190 0000 0000 6265"            /* .êˇˇˇˇ...ê....be */
	$"6773 6F62 6A64 0000 0051 706C 6364 0000"            /* gsobjd...Qplcd.. */
	$"0000 01FD 0154 0101 0101 0101 0000 0000"            /* ...˝.T.......... */
	$"0000 0000 0000 0000 FFFF FFFF 0000 0000"            /* ........ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"0000 0001 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0150 0000 0062 6567 736F"            /* .......P...begso */
	$"626A 6400 0000 4A44 6362 6274 4C41 5300"            /* bjd...JDcbbtLAS. */
	$"1800 1801 0100 0000 0000 0000 0F00 0000"            /* ................ */
	$"0C00 0000 00FF FFFF FF74 4C41 5300 0000"            /* .....ˇˇˇˇtLAS... */
	$"0000 0001 0100 0023 2800 2100 0000 0000"            /* .......#(.!..... */
	$"0000 0000 0000 0000 0000 0000 0044 436C"            /* .............DCl */
	$"6B6F 626A 6400 0000 4A44 6362 6274 5345"            /* kobjd...JDcbbtSE */
	$"4C00 1800 1801 0100 0000 0000 0000 2900"            /* L.............). */
	$"0000 0C00 0000 00FF FFFF FF74 5345 4C00"            /* .......ˇˇˇˇtSEL. */
	$"0000 0000 0001 0100 0023 2900 2100 0000"            /* .........#).!... */
	$"0000 0000 0000 0000 0000 0000 0000 0044"            /* ...............D */
	$"436C 6B6F 626A 6400 0000 4662 6275 7474"            /* Clkobjd...Fbbutt */
	$"5458 5400 1800 1801 0100 0000 0000 0000"            /* TXT............. */
	$"0F00 0000 2600 0000 00FF FFFF FF74 5458"            /* ....&....ˇˇˇˇtTX */
	$"5400 0000 0000 0001 0100 0023 2A00 2100"            /* T..........#*.!. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"006F 626A 6400 0000 4662 6275 7474 5045"            /* .objd...FbbuttPE */
	$"4E00 1800 1801 0100 0000 0000 0000 2900"            /* N.............). */
	$"0000 2600 0000 00FF FFFF FF74 5045 4E00"            /* ..&....ˇˇˇˇtPEN. */
	$"0000 0000 0001 0100 0023 2B00 2100 0000"            /* .........#+.!... */
	$"0000 0000 0000 0000 0000 0000 0000 006F"            /* ...............o */
	$"626A 6400 0000 4A44 6362 6274 4552 4100"            /* bjd...JDcbbtERA. */
	$"1800 1801 0100 0000 0000 0000 0F00 0000"            /* ................ */
	$"4000 0000 00FF FFFF FF74 4552 4100 0000"            /* @....ˇˇˇˇtERA... */
	$"0000 0001 0100 0023 2C00 2100 0000 0000"            /* .......#,.!..... */
	$"0000 0000 0000 0000 0000 0000 0044 436C"            /* .............DCl */
	$"6B6F 626A 6400 0000 4662 6275 7474 4255"            /* kobjd...FbbuttBU */
	$"4300 1800 1801 0100 0000 0000 0000 2900"            /* C.............). */
	$"0000 4000 0000 00FF FFFF FF74 4255 4300"            /* ..@....ˇˇˇˇtBUC. */
	$"0000 0000 0001 0100 0023 2D00 2100 0000"            /* .........#-.!... */
	$"0000 0000 0000 0000 0000 0000 0000 006F"            /* ...............o */
	$"626A 6400 0000 4662 6275 7474 4452 4F00"            /* bjd...FbbuttDRO. */
	$"1800 1801 0100 0000 0000 0000 0F00 0000"            /* ................ */
	$"5A00 0000 00FF FFFF FF74 4452 4F00 0000"            /* Z....ˇˇˇˇtDRO... */
	$"0000 0001 0100 0023 2E00 2100 0000 0000"            /* .......#..!..... */
	$"0000 0000 0000 0000 0000 0000 006F 626A"            /* .............obj */
	$"6400 0000 4662 6275 7474 4C49 4E00 1800"            /* d...FbbuttLIN... */
	$"1801 0100 0000 0000 0000 2900 0000 5A00"            /* ..........)...Z. */
	$"0000 00FF FFFF FF74 4C49 4E00 0000 0000"            /* ...ˇˇˇˇtLIN..... */
	$"0001 0100 0023 2F00 2100 0000 0000 0000"            /* .....#/.!....... */
	$"0000 0000 0000 0000 0000 006F 626A 6400"            /* ...........objd. */
	$"0000 4662 6275 7474 5245 4300 1800 1801"            /* ..FbbuttREC..... */
	$"0100 0000 0000 0000 0F00 0000 7400 0000"            /* ............t... */
	$"00FF FFFF FF74 5245 4300 0000 0000 0001"            /* .ˇˇˇˇtREC....... */
	$"0100 0023 3100 2100 0000 0000 0000 0000"            /* ...#1.!......... */
	$"0000 0000 0000 0000 006F 626A 6400 0000"            /* .........objd... */
	$"4662 6275 7474 4652 4300 1800 1801 0100"            /* FbbuttFRC....... */
	$"0000 0000 0000 2900 0000 7400 0000 00FF"            /* ......)...t....ˇ */
	$"FFFF FF74 4652 4300 0000 0000 0001 0100"            /* ˇˇˇtFRC......... */
	$"0023 3000 2100 0000 0000 0000 0000 0000"            /* .#0.!........... */
	$"0000 0000 0000 006F 626A 6400 0000 4662"            /* .......objd...Fb */
	$"6275 7474 5252 4300 1800 1801 0100 0000"            /* buttRRC......... */
	$"0000 0000 0F00 0000 8E00 0000 00FF FFFF"            /* ........é....ˇˇˇ */
	$"FF74 5252 4300 0000 0000 0001 0100 0023"            /* ˇtRRC..........# */
	$"3300 2100 0000 0000 0000 0000 0000 0000"            /* 3.!............. */
	$"0000 0000 006F 626A 6400 0000 4662 6275"            /* .....objd...Fbbu */
	$"7474 4652 5200 1800 1801 0100 0000 0000"            /* ttFRR........... */
	$"0000 2900 0000 8E00 0000 00FF FFFF FF74"            /* ..)...é....ˇˇˇˇt */
	$"4652 5200 0000 0000 0001 0100 0023 3200"            /* FRR..........#2. */
	$"2100 0000 0000 0000 0000 0000 0000 0000"            /* !............... */
	$"0000 006F 626A 6400 0000 4662 6275 7474"            /* ...objd...Fbbutt */
	$"4F56 4C00 1800 1801 0100 0000 0000 0000"            /* OVL............. */
	$"0F00 0000 A800 0000 00FF FFFF FF74 4F56"            /* ....®....ˇˇˇˇtOV */
	$"4C00 0000 0000 0001 0100 0023 3500 2100"            /* L..........#5.!. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"006F 626A 6400 0000 4662 6275 7474 464F"            /* .objd...FbbuttFO */
	$"5600 1800 1801 0100 0000 0000 0000 2900"            /* V.............). */
	$"0000 A800 0000 00FF FFFF FF74 464F 5600"            /* ..®....ˇˇˇˇtFOV. */
	$"0000 0000 0001 0100 0023 3400 2100 0000"            /* .........#4.!... */
	$"0000 0000 0000 0000 0000 0000 0000 0064"            /* ...............d */
	$"6F70 6C50 6174 506F 626A 6400 0000 4662"            /* oplPatPobjd...Fb */
	$"6275 7474 5041 5400 3200 1201 0100 0000"            /* buttPAT.2....... */
	$"0000 0000 0F00 0000 CC00 0003 E8FF FFFF"            /* ........Ã...Ëˇˇˇ */
	$"FF74 5041 5400 0000 0000 0000 0000 0000"            /* ˇtPAT........... */
	$"0000 2100 0000 0000 0000 0000 0000 0000"            /* ..!............. */
	$"0000 0000 006F 626A 6400 0000 4E43 6F6C"            /* .....objd...NCol */
	$"5074 4243 4C00 2800 1001 0101 0100 0000"            /* PtBCL.(......... */
	$"0000 1B00 0000 F500 FFFF FFFF FFFF FF74"            /* ......ı.ˇˇˇˇˇˇˇt */
	$"4243 4C00 0000 0000 0000 0000 0000 0000"            /* BCL............. */
	$"2100 0000 0000 0000 0000 0000 0000 0000"            /* !............... */
	$"0000 00FF FFFF FFFF FF01 006F 626A 6400"            /* ...ˇˇˇˇˇˇ..objd. */
	$"0000 4E43 6F6C 5074 4643 4C00 2800 1001"            /* ..NColPtFCL.(... */
	$"0101 0100 0000 0000 0F00 0000 E800 0000"            /* ............Ë... */
	$"00FF FFFF FF74 4643 4C00 0000 0000 0000"            /* .ˇˇˇˇtFCL....... */
	$"0000 0000 0000 2100 0000 0000 0000 0000"            /* ......!......... */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"006F 626A 6400 0000 5174 6762 7845 4E43"            /* .objd...QtgbxENC */
	$"4C01 4901 4901 0101 0100 0000 0000 5000"            /* L.I.I.........P. */
	$"0000 0A00 0000 00FF FFFF FF00 0000 0000"            /* ..¬....ˇˇˇˇ..... */
	$"0000 0000 0000 0000 0000 0000 0000 0100"            /* ................ */
	$"0000 0100 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 A000 0000 6265 6773 646F"            /* ......†...begsdo */
	$"706C 4943 4E56 6F62 6A64 0000 003C 7669"            /* plICNVobjd...<vi */
	$"6577 436E 7473 0141 0141 0101 0101 0101"            /* ewCnts.A.A...... */
	$"0000 0004 0000 0004 0000 0000 FFFF FFFF"            /* ............ˇˇˇˇ */
	$"0000 0000 0000 0004 0000 0000 0000 0000"            /* ................ */
	$"0000 0014 0000 0014 0001 656E 6473 6F62"            /* ..........endsob */
	$"6A64 0000 003C 7669 6577 5341 4D50 0050"            /* jd...<viewSAMP.P */
	$"011E 0101 0000 0000 0000 01A3 0000 0008"            /* ...........£.... */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0000 0001 0000 0001"            /* ................ */
	$"0000 6265 6773 646F 706C 4454 5677 6F62"            /* ..begsdoplDTVwob */
	$"6A64 0000 003C 7669 6577 6369 636E 002C"            /* jd...<viewcicn., */
	$"0038 0101 0000 0000 0000 0004 0000 001C"            /* .8.............. */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0000 0001 0000 0001"            /* ................ */
	$"0000 646F 706C 4454 5677 6F62 6A64 0000"            /* ..doplDTVwobjd.. */
	$"003C 7669 6577 4943 4F4E 002C 0038 0101"            /* .<viewICON.,.8.. */
	$"0000 0000 0000 0004 0000 005B 0000 0002"            /* ...........[.... */
	$"FFFF FFFF 0000 0000 0000 0000 0000 0000"            /* ˇˇˇˇ............ */
	$"0000 0000 0000 0001 0000 0001 0000 646F"            /* ..............do */
	$"706C 4454 5677 6F62 6A64 0000 003C 7669"            /* plDTVwobjd...<vi */
	$"6577 4D41 534B 002C 0038 0101 0000 0000"            /* ewMASK.,.8...... */
	$"0000 0004 0000 009A 0000 0001 FFFF FFFF"            /* .......ö....ˇˇˇˇ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0001 0000 0001 0000 656E 6473 6F62"            /* ..........endsob */
	$"6A64 0000 0037 7374 7874 434F 4F52 003C"            /* jd...7stxtCOOR.< */
	$"0010 0101 0000 0000 0000 000B 0000 0138"            /* ...............8 */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0120 0000 0065 6E64"            /* ......... ...end */
	$"736F 626A 6400 0000 5170 6C63 6446 4F4F"            /* sobjd...QplcdFOO */
	$"5401 FD00 2801 0101 0001 0100 0000 0000"            /* T.˝.(........... */
	$"0001 5400 0000 00FF FFFF FF00 0000 0000"            /* ..T....ˇˇˇˇ..... */
	$"0000 0000 0000 0000 0000 0000 0000 0100"            /* ................ */
	$"0000 0100 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 E000 0000 6265 6773 6F62"            /* ......‡...begsob */
	$"6A64 0000 003C 7075 7368 566C 6964 0041"            /* jd...<pushVlid.A */
	$"0014 0101 0000 0101 0000 01AE 0000 0009"            /* ...........Æ...∆ */
	$"0000 0000 FFFF FFFF 0000 0384 0000 0000"            /* ....ˇˇˇˇ...Ñ.... */
	$"0000 0000 0000 0000 0170 0000 0453 6176"            /* .........p...Sav */
	$"6501 6F62 6A64 0000 003E 7075 7368 436E"            /* e.objd...>pushCn */
	$"636C 0041 0014 0101 0000 0101 0000 0161"            /* cl.A...........a */
	$"0000 0009 0000 0000 FFFF FFFF 0000 0385"            /* ...∆....ˇˇˇˇ...Ö */
	$"0000 0000 0000 0000 0000 0000 0170 0000"            /* .............p.. */
	$"0643 616E 6365 6C00 6F62 6A64 0000 003E"            /* .Cancel.objd...> */
	$"7075 7368 5276 7274 0041 0014 0101 0100"            /* pushRvrt.A...... */
	$"0001 0000 001C 0000 0009 0000 0000 FFFF"            /* .........∆....ˇˇ */
	$"FFFF 0000 0007 0000 0000 0000 0000 0000"            /* ˇˇ.............. */
	$"0000 0170 0000 0652 6576 6572 7400 6F62"            /* ...p...Revert.ob */
	$"6A64 0000 0024 6963 6E70 4C6F 636B 0010"            /* jd...$icnpLock.. */
	$"0010 0101 0100 0001 0000 0006 0000 000B"            /* ................ */
	$"0000 0000 FFFF FFFF 0000 656E 6473 656E"            /* ....ˇˇˇˇ..endsen */
	$"6473 656E 642E"                                     /* dsend. */
};

data 'PPob' (10602, "ICON Editor Window") {
	$"0002 646F 706C 4661 6D56 6F62 6A64 0000"            /* ..doplFamVobjd.. */
	$"001C 7769 6E64 296A 0002 1862 0000 0190"            /* ..wind)j...b...ê */
	$"0190 FFFF FFFF 0208 0190 0000 0000 6265"            /* .êˇˇˇˇ...ê....be */
	$"6773 6F62 6A64 0000 0051 706C 6364 0000"            /* gsobjd...Qplcd.. */
	$"0000 01C2 012C 0101 0101 0101 0000 0000"            /* ...¬.,.......... */
	$"0000 0000 0000 0000 FFFF FFFF 0000 0000"            /* ........ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"0000 0001 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0150 0000 0062 6567 736F"            /* .......P...begso */
	$"626A 6400 0000 4A44 6362 6274 4C41 5300"            /* bjd...JDcbbtLAS. */
	$"1800 1801 0100 0000 0000 0000 0F00 0000"            /* ................ */
	$"0C00 0000 00FF FFFF FF74 4C41 5300 0000"            /* .....ˇˇˇˇtLAS... */
	$"0000 0001 0100 0023 2800 2100 0000 0000"            /* .......#(.!..... */
	$"0000 0000 0000 0000 0000 0000 0044 436C"            /* .............DCl */
	$"6B6F 626A 6400 0000 4A44 6362 6274 5345"            /* kobjd...JDcbbtSE */
	$"4C00 1800 1801 0100 0000 0000 0000 2900"            /* L.............). */
	$"0000 0C00 0000 00FF FFFF FF74 5345 4C00"            /* .......ˇˇˇˇtSEL. */
	$"0000 0000 0001 0100 0023 2900 2100 0000"            /* .........#).!... */
	$"0000 0000 0000 0000 0000 0000 0000 0044"            /* ...............D */
	$"436C 6B6F 626A 6400 0000 4662 6275 7474"            /* Clkobjd...Fbbutt */
	$"5458 5400 1800 1801 0100 0000 0000 0000"            /* TXT............. */
	$"0F00 0000 2600 0000 00FF FFFF FF74 5458"            /* ....&....ˇˇˇˇtTX */
	$"5400 0000 0000 0001 0100 0023 2A00 2100"            /* T..........#*.!. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"006F 626A 6400 0000 4662 6275 7474 5045"            /* .objd...FbbuttPE */
	$"4E00 1800 1801 0100 0000 0000 0000 2900"            /* N.............). */
	$"0000 2600 0000 00FF FFFF FF74 5045 4E00"            /* ..&....ˇˇˇˇtPEN. */
	$"0000 0000 0001 0100 0023 2B00 2100 0000"            /* .........#+.!... */
	$"0000 0000 0000 0000 0000 0000 0000 006F"            /* ...............o */
	$"626A 6400 0000 4A44 6362 6274 4552 4100"            /* bjd...JDcbbtERA. */
	$"1800 1801 0100 0000 0000 0000 0F00 0000"            /* ................ */
	$"4000 0000 00FF FFFF FF74 4552 4100 0000"            /* @....ˇˇˇˇtERA... */
	$"0000 0001 0100 0023 2C00 2100 0000 0000"            /* .......#,.!..... */
	$"0000 0000 0000 0000 0000 0000 0044 436C"            /* .............DCl */
	$"6B6F 626A 6400 0000 4662 6275 7474 4255"            /* kobjd...FbbuttBU */
	$"4300 1800 1801 0100 0000 0000 0000 2900"            /* C.............). */
	$"0000 4000 0000 00FF FFFF FF74 4255 4300"            /* ..@....ˇˇˇˇtBUC. */
	$"0000 0000 0001 0100 0023 2D00 2100 0000"            /* .........#-.!... */
	$"0000 0000 0000 0000 0000 0000 0000 006F"            /* ...............o */
	$"626A 6400 0000 4662 6275 7474 4452 4F00"            /* bjd...FbbuttDRO. */
	$"1800 1801 0100 0000 0000 0000 0F00 0000"            /* ................ */
	$"5A00 0000 00FF FFFF FF74 4452 4F00 0000"            /* Z....ˇˇˇˇtDRO... */
	$"0000 0001 0100 0023 2E00 2100 0000 0000"            /* .......#..!..... */
	$"0000 0000 0000 0000 0000 0000 006F 626A"            /* .............obj */
	$"6400 0000 4662 6275 7474 4C49 4E00 1800"            /* d...FbbuttLIN... */
	$"1801 0100 0000 0000 0000 2900 0000 5A00"            /* ..........)...Z. */
	$"0000 00FF FFFF FF74 4C49 4E00 0000 0000"            /* ...ˇˇˇˇtLIN..... */
	$"0001 0100 0023 2F00 2100 0000 0000 0000"            /* .....#/.!....... */
	$"0000 0000 0000 0000 0000 006F 626A 6400"            /* ...........objd. */
	$"0000 4662 6275 7474 5245 4300 1800 1801"            /* ..FbbuttREC..... */
	$"0100 0000 0000 0000 0F00 0000 7400 0000"            /* ............t... */
	$"00FF FFFF FF74 5245 4300 0000 0000 0001"            /* .ˇˇˇˇtREC....... */
	$"0100 0023 3100 2100 0000 0000 0000 0000"            /* ...#1.!......... */
	$"0000 0000 0000 0000 006F 626A 6400 0000"            /* .........objd... */
	$"4662 6275 7474 4652 4300 1800 1801 0100"            /* FbbuttFRC....... */
	$"0000 0000 0000 2900 0000 7400 0000 00FF"            /* ......)...t....ˇ */
	$"FFFF FF74 4652 4300 0000 0000 0001 0100"            /* ˇˇˇtFRC......... */
	$"0023 3000 2100 0000 0000 0000 0000 0000"            /* .#0.!........... */
	$"0000 0000 0000 006F 626A 6400 0000 4662"            /* .......objd...Fb */
	$"6275 7474 5252 4300 1800 1801 0100 0000"            /* buttRRC......... */
	$"0000 0000 0F00 0000 8E00 0000 00FF FFFF"            /* ........é....ˇˇˇ */
	$"FF74 5252 4300 0000 0000 0001 0100 0023"            /* ˇtRRC..........# */
	$"3300 2100 0000 0000 0000 0000 0000 0000"            /* 3.!............. */
	$"0000 0000 006F 626A 6400 0000 4662 6275"            /* .....objd...Fbbu */
	$"7474 4652 5200 1800 1801 0100 0000 0000"            /* ttFRR........... */
	$"0000 2900 0000 8E00 0000 00FF FFFF FF74"            /* ..)...é....ˇˇˇˇt */
	$"4652 5200 0000 0000 0001 0100 0023 3200"            /* FRR..........#2. */
	$"2100 0000 0000 0000 0000 0000 0000 0000"            /* !............... */
	$"0000 006F 626A 6400 0000 4662 6275 7474"            /* ...objd...Fbbutt */
	$"4F56 4C00 1800 1801 0100 0000 0000 0000"            /* OVL............. */
	$"0F00 0000 A800 0000 00FF FFFF FF74 4F56"            /* ....®....ˇˇˇˇtOV */
	$"4C00 0000 0000 0001 0100 0023 3500 2100"            /* L..........#5.!. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"006F 626A 6400 0000 4662 6275 7474 464F"            /* .objd...FbbuttFO */
	$"5600 1800 1801 0100 0000 0000 0000 2900"            /* V.............). */
	$"0000 A800 0000 00FF FFFF FF74 464F 5600"            /* ..®....ˇˇˇˇtFOV. */
	$"0000 0000 0001 0100 0023 3400 2100 0000"            /* .........#4.!... */
	$"0000 0000 0000 0000 0000 0000 0000 0064"            /* ...............d */
	$"6F70 6C50 6174 506F 626A 6400 0000 4662"            /* oplPatPobjd...Fb */
	$"6275 7474 5041 5400 3200 1201 0100 0000"            /* buttPAT.2....... */
	$"0000 0000 0F00 0000 CC00 0003 E8FF FFFF"            /* ........Ã...Ëˇˇˇ */
	$"FF74 5041 5400 0000 0000 0000 0000 0000"            /* ˇtPAT........... */
	$"0000 2100 0000 0000 0000 0000 0000 0000"            /* ..!............. */
	$"0000 0000 006F 626A 6400 0000 4E43 6F6C"            /* .....objd...NCol */
	$"5074 4243 4C00 2800 1001 0101 0100 0000"            /* PtBCL.(......... */
	$"0000 1B00 0000 F400 FFFF FFFF FFFF FF74"            /* ......Ù.ˇˇˇˇˇˇˇt */
	$"4243 4C00 0000 0000 0000 0000 0000 0000"            /* BCL............. */
	$"2100 0000 0000 0000 0000 0000 0000 0000"            /* !............... */
	$"0000 00FF FFFF FFFF FF01 006F 626A 6400"            /* ...ˇˇˇˇˇˇ..objd. */
	$"0000 4E43 6F6C 5074 4643 4C00 2800 1001"            /* ..NColPtFCL.(... */
	$"0101 0100 0000 0000 0F00 0000 E800 0000"            /* ............Ë... */
	$"00FF FFFF FF74 4643 4C00 0000 0000 0000"            /* .ˇˇˇˇtFCL....... */
	$"0000 0000 0000 2100 0000 0000 0000 0000"            /* ......!......... */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"006F 626A 6400 0000 5174 6762 7845 4E43"            /* .objd...QtgbxENC */
	$"4C01 2201 2201 0101 0100 0000 0000 5000"            /* L.".".........P. */
	$"0000 0A00 0000 00FF FFFF FF00 0000 0000"            /* ..¬....ˇˇˇˇ..... */
	$"0000 0000 0000 0000 0000 0000 0000 0100"            /* ................ */
	$"0000 0100 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 A000 0000 6265 6773 646F"            /* ......†...begsdo */
	$"706C 4943 4E56 6F62 6A64 0000 003C 7669"            /* plICNVobjd...<vi */
	$"6577 436E 7473 011A 011A 0101 0101 0101"            /* ewCnts.......... */
	$"0000 0004 0000 0004 0000 0000 FFFF FFFF"            /* ............ˇˇˇˇ */
	$"0000 0000 0000 0004 0000 0000 0000 0000"            /* ................ */
	$"0000 0014 0000 0014 0001 656E 6473 6F62"            /* ..........endsob */
	$"6A64 0000 003C 7669 6577 5341 4D50 003C"            /* jd...<viewSAMP.< */
	$"0048 0101 0000 0000 0000 017C 0000 000C"            /* .H.........|.... */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0000 0001 0000 0001"            /* ................ */
	$"0000 6265 6773 646F 706C 4454 5677 6F62"            /* ..begsdoplDTVwob */
	$"6A64 0000 003C 7669 6577 4943 4F4E 002C"            /* jd...<viewICON., */
	$"0038 0101 0000 0000 0000 0008 0000 0008"            /* .8.............. */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0000 0001 0000 0001"            /* ................ */
	$"0000 656E 6473 6F62 6A64 0000 0037 7374"            /* ..endsobjd...7st */
	$"7874 434F 4F52 003C 0010 0101 0000 0000"            /* xtCOOR.<........ */
	$"0000 000A 0000 0111 0000 0000 FFFF FFFF"            /* ...¬........ˇˇˇˇ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0120 0000 0065 6E64 736F 626A 6400 0000"            /* . ...endsobjd... */
	$"5170 6C63 6446 4F4F 5401 C200 2801 0101"            /* QplcdFOOT.¬.(... */
	$"0001 0100 0000 0000 0001 2C00 0000 00FF"            /* ..........,....ˇ */
	$"FFFF FF00 0000 0000 0000 0000 0000 0000"            /* ˇˇˇ............. */
	$"0000 0000 0000 0100 0000 0100 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 E000"            /* ..............‡. */
	$"0000 6265 6773 6F62 6A64 0000 003C 7075"            /* ..begsobjd...<pu */
	$"7368 566C 6964 0041 0014 0101 0000 0101"            /* shVlid.A........ */
	$"0000 0173 0000 0009 0000 0000 FFFF FFFF"            /* ...s...∆....ˇˇˇˇ */
	$"0000 0384 0000 0000 0000 0000 0000 0000"            /* ...Ñ............ */
	$"0170 0000 0453 6176 6501 6F62 6A64 0000"            /* .p...Save.objd.. */
	$"003E 7075 7368 436E 636C 0041 0014 0101"            /* .>pushCncl.A.... */
	$"0000 0101 0000 0126 0000 0009 0000 0000"            /* .......&...∆.... */
	$"FFFF FFFF 0000 0385 0000 0000 0000 0000"            /* ˇˇˇˇ...Ö........ */
	$"0000 0000 0170 0000 0643 616E 6365 6C00"            /* .....p...Cancel. */
	$"6F62 6A64 0000 003E 7075 7368 5276 7274"            /* objd...>pushRvrt */
	$"0041 0014 0101 0100 0001 0000 001C 0000"            /* .A.............. */
	$"0009 0000 0000 FFFF FFFF 0000 0007 0000"            /* .∆....ˇˇˇˇ...... */
	$"0000 0000 0000 0000 0000 0170 0000 0652"            /* ...........p...R */
	$"6576 6572 7400 6F62 6A64 0000 0024 6963"            /* evert.objd...$ic */
	$"6E70 4C6F 636B 0010 0010 0101 0100 0001"            /* npLock.......... */
	$"0000 0006 0000 000B 0000 0000 FFFF FFFF"            /* ............ˇˇˇˇ */
	$"0000 656E 6473 656E 6473 656E 642E"                 /* ..endsendsend. */
};

data 'PPob' (10603, "PICT Editor Window") {
	$"0002 646F 706C 5069 6356 6F62 6A64 0000"            /* ..doplPicVobjd.. */
	$"001C 7769 6E64 296B 0002 1E62 0000 0190"            /* ..wind)k...b...ê */
	$"0190 FFFF FFFF 01E0 0190 0000 0000 6265"            /* .êˇˇˇˇ.‡.ê....be */
	$"6773 6F62 6A64 0000 0051 706C 6364 0000"            /* gsobjd...Qplcd.. */
	$"0000 01CC 0172 0101 0101 0101 0000 0000"            /* ...Ã.r.......... */
	$"0000 0000 0000 0000 FFFF FFFF 0000 0000"            /* ........ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"0000 0001 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0150 0000 0062 6567 736F"            /* .......P...begso */
	$"626A 6400 0000 4A44 6362 6274 4C41 5300"            /* bjd...JDcbbtLAS. */
	$"1800 1801 0100 0000 0000 0000 0F00 0000"            /* ................ */
	$"0C00 0000 00FF FFFF FF74 4C41 5300 0000"            /* .....ˇˇˇˇtLAS... */
	$"0000 0001 0100 0023 2800 2100 0000 0000"            /* .......#(.!..... */
	$"0000 0000 0000 0000 0000 0000 0044 436C"            /* .............DCl */
	$"6B6F 626A 6400 0000 4A44 6362 6274 5345"            /* kobjd...JDcbbtSE */
	$"4C00 1800 1801 0100 0000 0000 0000 2900"            /* L.............). */
	$"0000 0C00 0000 00FF FFFF FF74 5345 4C00"            /* .......ˇˇˇˇtSEL. */
	$"0000 0000 0001 0100 0023 2900 2100 0000"            /* .........#).!... */
	$"0000 0000 0000 0000 0000 0000 0000 0044"            /* ...............D */
	$"436C 6B6F 626A 6400 0000 4662 6275 7474"            /* Clkobjd...Fbbutt */
	$"5458 5400 1800 1801 0100 0000 0000 0000"            /* TXT............. */
	$"0F00 0000 2600 0000 00FF FFFF FF74 5458"            /* ....&....ˇˇˇˇtTX */
	$"5400 0000 0000 0001 0100 0023 2A00 2100"            /* T..........#*.!. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"006F 626A 6400 0000 4662 6275 7474 5045"            /* .objd...FbbuttPE */
	$"4E00 1800 1801 0100 0000 0000 0000 2900"            /* N.............). */
	$"0000 2600 0000 00FF FFFF FF74 5045 4E00"            /* ..&....ˇˇˇˇtPEN. */
	$"0000 0000 0001 0100 0023 2B00 2100 0000"            /* .........#+.!... */
	$"0000 0000 0000 0000 0000 0000 0000 006F"            /* ...............o */
	$"626A 6400 0000 4A44 6362 6274 4552 4100"            /* bjd...JDcbbtERA. */
	$"1800 1801 0100 0000 0000 0000 0F00 0000"            /* ................ */
	$"4000 0000 00FF FFFF FF74 4552 4100 0000"            /* @....ˇˇˇˇtERA... */
	$"0000 0001 0100 0023 2C00 2100 0000 0000"            /* .......#,.!..... */
	$"0000 0000 0000 0000 0000 0000 0044 436C"            /* .............DCl */
	$"6B6F 626A 6400 0000 4662 6275 7474 4255"            /* kobjd...FbbuttBU */
	$"4300 1800 1801 0100 0000 0000 0000 2900"            /* C.............). */
	$"0000 4000 0000 00FF FFFF FF74 4255 4300"            /* ..@....ˇˇˇˇtBUC. */
	$"0000 0000 0001 0100 0023 2D00 2100 0000"            /* .........#-.!... */
	$"0000 0000 0000 0000 0000 0000 0000 006F"            /* ...............o */
	$"626A 6400 0000 4662 6275 7474 4452 4F00"            /* bjd...FbbuttDRO. */
	$"1800 1801 0100 0000 0000 0000 0F00 0000"            /* ................ */
	$"5A00 0000 00FF FFFF FF74 4452 4F00 0000"            /* Z....ˇˇˇˇtDRO... */
	$"0000 0001 0100 0023 2E00 2100 0000 0000"            /* .......#..!..... */
	$"0000 0000 0000 0000 0000 0000 006F 626A"            /* .............obj */
	$"6400 0000 4662 6275 7474 4C49 4E00 1800"            /* d...FbbuttLIN... */
	$"1801 0100 0000 0000 0000 2900 0000 5A00"            /* ..........)...Z. */
	$"0000 00FF FFFF FF74 4C49 4E00 0000 0000"            /* ...ˇˇˇˇtLIN..... */
	$"0001 0100 0023 2F00 2100 0000 0000 0000"            /* .....#/.!....... */
	$"0000 0000 0000 0000 0000 006F 626A 6400"            /* ...........objd. */
	$"0000 4662 6275 7474 5245 4300 1800 1801"            /* ..FbbuttREC..... */
	$"0100 0000 0000 0000 0F00 0000 7400 0000"            /* ............t... */
	$"00FF FFFF FF74 5245 4300 0000 0000 0001"            /* .ˇˇˇˇtREC....... */
	$"0100 0023 3100 2100 0000 0000 0000 0000"            /* ...#1.!......... */
	$"0000 0000 0000 0000 006F 626A 6400 0000"            /* .........objd... */
	$"4662 6275 7474 4652 4300 1800 1801 0100"            /* FbbuttFRC....... */
	$"0000 0000 0000 2900 0000 7400 0000 00FF"            /* ......)...t....ˇ */
	$"FFFF FF74 4652 4300 0000 0000 0001 0100"            /* ˇˇˇtFRC......... */
	$"0023 3000 2100 0000 0000 0000 0000 0000"            /* .#0.!........... */
	$"0000 0000 0000 006F 626A 6400 0000 4662"            /* .......objd...Fb */
	$"6275 7474 5252 4300 1800 1801 0100 0000"            /* buttRRC......... */
	$"0000 0000 0F00 0000 8E00 0000 00FF FFFF"            /* ........é....ˇˇˇ */
	$"FF74 5252 4300 0000 0000 0001 0100 0023"            /* ˇtRRC..........# */
	$"3300 2100 0000 0000 0000 0000 0000 0000"            /* 3.!............. */
	$"0000 0000 006F 626A 6400 0000 4662 6275"            /* .....objd...Fbbu */
	$"7474 4652 5200 1800 1801 0100 0000 0000"            /* ttFRR........... */
	$"0000 2900 0000 8E00 0000 00FF FFFF FF74"            /* ..)...é....ˇˇˇˇt */
	$"4652 5200 0000 0000 0001 0100 0023 3200"            /* FRR..........#2. */
	$"2100 0000 0000 0000 0000 0000 0000 0000"            /* !............... */
	$"0000 006F 626A 6400 0000 4662 6275 7474"            /* ...objd...Fbbutt */
	$"4F56 4C00 1800 1801 0100 0000 0000 0000"            /* OVL............. */
	$"0F00 0000 A800 0000 00FF FFFF FF74 4F56"            /* ....®....ˇˇˇˇtOV */
	$"4C00 0000 0000 0001 0100 0023 3500 2100"            /* L..........#5.!. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"006F 626A 6400 0000 4662 6275 7474 464F"            /* .objd...FbbuttFO */
	$"5600 1800 1801 0100 0000 0000 0000 2900"            /* V.............). */
	$"0000 A800 0000 00FF FFFF FF74 464F 5600"            /* ..®....ˇˇˇˇtFOV. */
	$"0000 0000 0001 0100 0023 3400 2100 0000"            /* .........#4.!... */
	$"0000 0000 0000 0000 0000 0000 0000 0064"            /* ...............d */
	$"6F70 6C50 6174 506F 626A 6400 0000 4662"            /* oplPatPobjd...Fb */
	$"6275 7474 5041 5400 3200 1201 0100 0000"            /* buttPAT.2....... */
	$"0000 0000 0F00 0000 CC00 0003 E8FF FFFF"            /* ........Ã...Ëˇˇˇ */
	$"FF74 5041 5400 0000 0000 0000 0000 0000"            /* ˇtPAT........... */
	$"0000 2100 0000 0000 0000 0000 0000 0000"            /* ..!............. */
	$"0000 0000 006F 626A 6400 0000 4E43 6F6C"            /* .....objd...NCol */
	$"5074 4243 4C00 2800 1001 0101 0100 0000"            /* PtBCL.(......... */
	$"0000 1B00 0000 F500 FFFF FFFF FFFF FF74"            /* ......ı.ˇˇˇˇˇˇˇt */
	$"4243 4C00 0000 0000 0000 0000 0000 0000"            /* BCL............. */
	$"2100 0000 0000 0000 0000 0000 0000 0000"            /* !............... */
	$"0000 00FF FFFF FFFF FF01 006F 626A 6400"            /* ...ˇˇˇˇˇˇ..objd. */
	$"0000 4E43 6F6C 5074 4643 4C00 2800 1001"            /* ..NColPtFCL.(... */
	$"0101 0100 0000 0000 0F00 0000 E800 0000"            /* ............Ë... */
	$"00FF FFFF FF74 4643 4C00 0000 0000 0000"            /* .ˇˇˇˇtFCL....... */
	$"0000 0000 0000 2100 0000 0000 0000 0000"            /* ......!......... */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"006F 626A 6400 0000 5174 6762 7845 4E43"            /* .objd...QtgbxENC */
	$"4C01 6801 6801 0101 0100 0000 0000 5100"            /* L.h.h.........Q. */
	$"0000 0A00 0000 00FF FFFF FF00 0000 0000"            /* ..¬....ˇˇˇˇ..... */
	$"0000 0000 0000 0000 0000 0000 0000 0100"            /* ................ */
	$"0000 0100 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 A000 0000 6265 6773 646F"            /* ......†...begsdo */
	$"706C 4943 4E56 6F62 6A64 0000 003C 7669"            /* plICNVobjd...<vi */
	$"6577 436E 7473 0160 0160 0101 0101 0101"            /* ewCnts.`.`...... */
	$"0000 0004 0000 0004 0000 0000 FFFF FFFF"            /* ............ˇˇˇˇ */
	$"0000 0000 0000 0004 0000 0000 0000 0000"            /* ................ */
	$"0000 0014 0000 0014 0001 656E 6473 6F62"            /* ..........endsob */
	$"6A64 0000 0037 7374 7874 434F 4F52 003C"            /* jd...7stxtCOOR.< */
	$"0010 0101 0000 0000 0000 000A 0000 0157"            /* ...........¬...W */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0120 0000 0065 6E64"            /* ......... ...end */
	$"736F 626A 6400 0000 5170 6C63 6446 4F4F"            /* sobjd...QplcdFOO */
	$"5401 CC00 2801 0101 0001 0100 0000 0000"            /* T.Ã.(........... */
	$"0001 7200 0000 00FF FFFF FF00 0000 0000"            /* ..r....ˇˇˇˇ..... */
	$"0000 0000 0000 0000 0000 0000 0000 0100"            /* ................ */
	$"0000 0100 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 E000 0000 6265 6773 6F62"            /* ......‡...begsob */
	$"6A64 0000 003C 7075 7368 566C 6964 0041"            /* jd...<pushVlid.A */
	$"0014 0101 0000 0101 0000 017D 0000 0009"            /* ...........}...∆ */
	$"0000 0000 FFFF FFFF 0000 0384 0000 0000"            /* ....ˇˇˇˇ...Ñ.... */
	$"0000 0000 0000 0000 0170 0000 0453 6176"            /* .........p...Sav */
	$"6501 6F62 6A64 0000 003E 7075 7368 436E"            /* e.objd...>pushCn */
	$"636C 0041 0014 0101 0000 0101 0000 0130"            /* cl.A...........0 */
	$"0000 0009 0000 0000 FFFF FFFF 0000 0385"            /* ...∆....ˇˇˇˇ...Ö */
	$"0000 0000 0000 0000 0000 0000 0170 0000"            /* .............p.. */
	$"0643 616E 6365 6C00 6F62 6A64 0000 003E"            /* .Cancel.objd...> */
	$"7075 7368 5276 7274 0041 0014 0101 0100"            /* pushRvrt.A...... */
	$"0001 0000 001C 0000 0009 0000 0000 FFFF"            /* .........∆....ˇˇ */
	$"FFFF 0000 0007 0000 0000 0000 0000 0000"            /* ˇˇ.............. */
	$"0000 0170 0000 0652 6576 6572 7400 6F62"            /* ...p...Revert.ob */
	$"6A64 0000 0024 6963 6E70 4C6F 636B 0010"            /* jd...$icnpLock.. */
	$"0010 0101 0100 0001 0000 0006 0000 000B"            /* ................ */
	$"0000 0000 FFFF FFFF 0000 656E 6473 656E"            /* ....ˇˇˇˇ..endsen */
	$"6473 656E 642E"                                     /* dsend. */
};

data 'PPob' (10604, "CURS Editor Window") {
	$"0002 646F 706C 4372 7356 6F62 6A64 0000"            /* ..doplCrsVobjd.. */
	$"001C 7769 6E64 296C 0002 1862 0000 0190"            /* ..wind)l...b...ê */
	$"0190 FFFF FFFF 01F4 0190 0000 0000 6265"            /* .êˇˇˇˇ.Ù.ê....be */
	$"6773 6F62 6A64 0000 0051 706C 6364 0000"            /* gsobjd...Qplcd.. */
	$"0000 01B8 013B 0101 0101 0101 0000 0000"            /* ...∏.;.......... */
	$"0000 0000 0000 0000 FFFF FFFF 0000 0000"            /* ........ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"0000 0001 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0150 0000 0062 6567 736F"            /* .......P...begso */
	$"626A 6400 0000 4A44 6362 6274 4C41 5300"            /* bjd...JDcbbtLAS. */
	$"1800 1801 0100 0000 0000 0000 0F00 0000"            /* ................ */
	$"0C00 0000 00FF FFFF FF74 4C41 5300 0000"            /* .....ˇˇˇˇtLAS... */
	$"0000 0001 0100 0023 2800 2100 0000 0000"            /* .......#(.!..... */
	$"0000 0000 0000 0000 0000 0000 0044 436C"            /* .............DCl */
	$"6B6F 626A 6400 0000 4A44 6362 6274 5345"            /* kobjd...JDcbbtSE */
	$"4C00 1800 1801 0100 0000 0000 0000 2900"            /* L.............). */
	$"0000 0C00 0000 00FF FFFF FF74 5345 4C00"            /* .......ˇˇˇˇtSEL. */
	$"0000 0000 0001 0100 0023 2900 2100 0000"            /* .........#).!... */
	$"0000 0000 0000 0000 0000 0000 0000 0044"            /* ...............D */
	$"436C 6B6F 626A 6400 0000 4662 6275 7474"            /* Clkobjd...Fbbutt */
	$"5458 5400 1800 1801 0100 0000 0000 0000"            /* TXT............. */
	$"0F00 0000 2600 0000 00FF FFFF FF74 5458"            /* ....&....ˇˇˇˇtTX */
	$"5400 0000 0000 0001 0100 0023 2A00 2100"            /* T..........#*.!. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"006F 626A 6400 0000 4662 6275 7474 5045"            /* .objd...FbbuttPE */
	$"4E00 1800 1801 0100 0000 0000 0000 2900"            /* N.............). */
	$"0000 2600 0000 00FF FFFF FF74 5045 4E00"            /* ..&....ˇˇˇˇtPEN. */
	$"0000 0000 0001 0100 0023 2B00 2100 0000"            /* .........#+.!... */
	$"0000 0000 0000 0000 0000 0000 0000 006F"            /* ...............o */
	$"626A 6400 0000 4A44 6362 6274 4552 4100"            /* bjd...JDcbbtERA. */
	$"1800 1801 0100 0000 0000 0000 0F00 0000"            /* ................ */
	$"4000 0000 00FF FFFF FF74 4552 4100 0000"            /* @....ˇˇˇˇtERA... */
	$"0000 0001 0100 0023 2C00 2100 0000 0000"            /* .......#,.!..... */
	$"0000 0000 0000 0000 0000 0000 0044 436C"            /* .............DCl */
	$"6B6F 626A 6400 0000 4662 6275 7474 4255"            /* kobjd...FbbuttBU */
	$"4300 1800 1801 0100 0000 0000 0000 2900"            /* C.............). */
	$"0000 4000 0000 00FF FFFF FF74 4255 4300"            /* ..@....ˇˇˇˇtBUC. */
	$"0000 0000 0001 0100 0023 2D00 2100 0000"            /* .........#-.!... */
	$"0000 0000 0000 0000 0000 0000 0000 006F"            /* ...............o */
	$"626A 6400 0000 4662 6275 7474 4452 4F00"            /* bjd...FbbuttDRO. */
	$"1800 1801 0100 0000 0000 0000 0F00 0000"            /* ................ */
	$"5A00 0000 00FF FFFF FF74 4452 4F00 0000"            /* Z....ˇˇˇˇtDRO... */
	$"0000 0001 0100 0023 2E00 2100 0000 0000"            /* .......#..!..... */
	$"0000 0000 0000 0000 0000 0000 006F 626A"            /* .............obj */
	$"6400 0000 4662 6275 7474 4C49 4E00 1800"            /* d...FbbuttLIN... */
	$"1801 0100 0000 0000 0000 2900 0000 5A00"            /* ..........)...Z. */
	$"0000 00FF FFFF FF74 4C49 4E00 0000 0000"            /* ...ˇˇˇˇtLIN..... */
	$"0001 0100 0023 2F00 2100 0000 0000 0000"            /* .....#/.!....... */
	$"0000 0000 0000 0000 0000 006F 626A 6400"            /* ...........objd. */
	$"0000 4662 6275 7474 5245 4300 1800 1801"            /* ..FbbuttREC..... */
	$"0100 0000 0000 0000 0F00 0000 7400 0000"            /* ............t... */
	$"00FF FFFF FF74 5245 4300 0000 0000 0001"            /* .ˇˇˇˇtREC....... */
	$"0100 0023 3100 2100 0000 0000 0000 0000"            /* ...#1.!......... */
	$"0000 0000 0000 0000 006F 626A 6400 0000"            /* .........objd... */
	$"4662 6275 7474 4652 4300 1800 1801 0100"            /* FbbuttFRC....... */
	$"0000 0000 0000 2900 0000 7400 0000 00FF"            /* ......)...t....ˇ */
	$"FFFF FF74 4652 4300 0000 0000 0001 0100"            /* ˇˇˇtFRC......... */
	$"0023 3000 2100 0000 0000 0000 0000 0000"            /* .#0.!........... */
	$"0000 0000 0000 006F 626A 6400 0000 4662"            /* .......objd...Fb */
	$"6275 7474 5252 4300 1800 1801 0100 0000"            /* buttRRC......... */
	$"0000 0000 0F00 0000 8E00 0000 00FF FFFF"            /* ........é....ˇˇˇ */
	$"FF74 5252 4300 0000 0000 0001 0100 0023"            /* ˇtRRC..........# */
	$"3300 2100 0000 0000 0000 0000 0000 0000"            /* 3.!............. */
	$"0000 0000 006F 626A 6400 0000 4662 6275"            /* .....objd...Fbbu */
	$"7474 4652 5200 1800 1801 0100 0000 0000"            /* ttFRR........... */
	$"0000 2900 0000 8E00 0000 00FF FFFF FF74"            /* ..)...é....ˇˇˇˇt */
	$"4652 5200 0000 0000 0001 0100 0023 3200"            /* FRR..........#2. */
	$"2100 0000 0000 0000 0000 0000 0000 0000"            /* !............... */
	$"0000 006F 626A 6400 0000 4662 6275 7474"            /* ...objd...Fbbutt */
	$"4F56 4C00 1800 1801 0100 0000 0000 0000"            /* OVL............. */
	$"0F00 0000 A800 0000 00FF FFFF FF74 4F56"            /* ....®....ˇˇˇˇtOV */
	$"4C00 0000 0000 0001 0100 0023 3500 2100"            /* L..........#5.!. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"006F 626A 6400 0000 4662 6275 7474 464F"            /* .objd...FbbuttFO */
	$"5600 1800 1801 0100 0000 0000 0000 2900"            /* V.............). */
	$"0000 A800 0000 00FF FFFF FF74 464F 5600"            /* ..®....ˇˇˇˇtFOV. */
	$"0000 0000 0001 0100 0023 3400 2100 0000"            /* .........#4.!... */
	$"0000 0000 0000 0000 0000 0000 0000 006F"            /* ...............o */
	$"626A 6400 0000 4662 6275 7474 484F 5400"            /* bjd...FbbuttHOT. */
	$"1800 1801 0100 0000 0000 0000 1C00 0000"            /* ................ */
	$"C200 0000 00FF FFFF FF74 484F 5400 0000"            /* ¬....ˇˇˇˇtHOT... */
	$"0000 0001 0100 0023 3600 2100 0000 0000"            /* .......#6.!..... */
	$"0000 0000 0000 0000 0000 0000 0064 6F70"            /* .............dop */
	$"6C50 6174 506F 626A 6400 0000 4662 6275"            /* lPatPobjd...Fbbu */
	$"7474 5041 5400 3200 1201 0100 0000 0000"            /* ttPAT.2......... */
	$"0000 0E00 0000 E300 0003 E8FF FFFF FF74"            /* ......„...Ëˇˇˇˇt */
	$"5041 5400 0000 0000 0000 0000 0000 0000"            /* PAT............. */
	$"2100 0000 0000 0000 0000 0000 0000 0000"            /* !............... */
	$"0000 006F 626A 6400 0000 4E43 6F6C 5074"            /* ...objd...NColPt */
	$"4243 4C00 2800 1001 0101 0100 0000 0000"            /* BCL.(........... */
	$"1B00 0001 0900 FFFF FFFF FFFF FF74 4243"            /* ....∆.ˇˇˇˇˇˇˇtBC */
	$"4C00 0000 0000 0000 0000 0000 0000 2100"            /* L.............!. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"00FF FFFF FFFF FF01 006F 626A 6400 0000"            /* .ˇˇˇˇˇˇ..objd... */
	$"4E43 6F6C 5074 4643 4C00 2800 1001 0101"            /* NColPtFCL.(..... */
	$"0100 0000 0000 0F00 0000 FC00 0000 00FF"            /* ..........¸....ˇ */
	$"FFFF FF74 4643 4C00 0000 0000 0000 0000"            /* ˇˇˇtFCL......... */
	$"0000 0000 2100 0000 0000 0000 0000 0000"            /* ....!........... */
	$"0000 0000 0000 0000 0000 0000 0000 006F"            /* ...............o */
	$"626A 6400 0000 5174 6762 7845 4E43 4C01"            /* bjd...QtgbxENCL. */
	$"2C01 2C01 0101 0100 0000 0000 5000 0000"            /* ,.,.........P... */
	$"0A00 0000 00FF FFFF FF00 0000 0000 0000"            /* ¬....ˇˇˇˇ....... */
	$"0000 0000 0000 0000 0000 0000 0100 0000"            /* ................ */
	$"0100 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 A000 0000 6265 6773 646F 706C"            /* ....†...begsdopl */
	$"4943 4E56 6F62 6A64 0000 003C 7669 6577"            /* ICNVobjd...<view */
	$"436E 7473 0124 0124 0101 0101 0101 0000"            /* Cnts.$.$........ */
	$"0004 0000 0004 0000 0000 FFFF FFFF 0000"            /* ..........ˇˇˇˇ.. */
	$"0000 0000 0004 0000 0000 0000 0000 0000"            /* ................ */
	$"0014 0000 0014 0001 656E 6473 6F62 6A64"            /* ........endsobjd */
	$"0000 003C 7669 6577 5341 4D50 0028 0084"            /* ...<viewSAMP.(.Ñ */
	$"0101 0000 0000 0000 0186 0000 0014 0000"            /* .........Ü...... */
	$"0000 FFFF FFFF 0000 0000 0000 0000 0000"            /* ..ˇˇˇˇ.......... */
	$"0000 0000 0000 0000 0001 0000 0001 0000"            /* ................ */
	$"6265 6773 646F 706C 4454 5677 6F62 6A64"            /* begsdoplDTVwobjd */
	$"0000 003C 7669 6577 4355 5253 001C 0028"            /* ...<viewCURS...( */
	$"0101 0000 0000 0000 0006 0000 0008 0000"            /* ................ */
	$"0000 FFFF FFFF 0000 0000 0000 0000 0000"            /* ..ˇˇˇˇ.......... */
	$"0000 0000 0000 0000 0001 0000 0001 0000"            /* ................ */
	$"646F 706C 4454 5677 6F62 6A64 0000 003C"            /* doplDTVwobjd...< */
	$"7669 6577 4D41 534B 001C 0028 0101 0000"            /* viewMASK...(.... */
	$"0000 0000 0006 0000 0047 0000 0001 FFFF"            /* .........G....ˇˇ */
	$"FFFF 0000 0000 0000 0000 0000 0000 0000"            /* ˇˇ.............. */
	$"0000 0000 0001 0000 0001 0000 6F62 6A64"            /* ............objd */
	$"0000 003B 7374 7874 0000 0000 0022 0010"            /* ...;stxt.....".. */
	$"0101 0000 0000 0000 0003 0000 0030 0000"            /* .............0.. */
	$"0000 FFFF FFFF 0000 0000 0000 0000 0000"            /* ..ˇˇˇˇ.......... */
	$"0000 0000 0000 0120 008D 0443 5552 536F"            /* ....... .ç.CURSo */
	$"626A 6400 0000 3B73 7478 7400 0000 0000"            /* bjd...;stxt..... */
	$"2200 1001 0100 0000 0000 0000 0300 0000"            /* "............... */
	$"6F00 0000 00FF FFFF FF00 0000 0000 0000"            /* o....ˇˇˇˇ....... */
	$"0000 0000 0000 0000 0001 2000 8D04 4D61"            /* .......... .ç.Ma */
	$"736B 656E 6473 6F62 6A64 0000 0037 7374"            /* skendsobjd...7st */
	$"7874 434F 4F52 003C 0010 0101 0000 0000"            /* xtCOOR.<........ */
	$"0000 000A 0000 0120 0000 0000 FFFF FFFF"            /* ...¬... ....ˇˇˇˇ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0120 0000 0065 6E64 736F 626A 6400 0000"            /* . ...endsobjd... */
	$"5170 6C63 6446 4F4F 5401 B800 2801 0101"            /* QplcdFOOT.∏.(... */
	$"0001 0100 0000 0000 0001 3B00 0000 00FF"            /* ..........;....ˇ */
	$"FFFF FF00 0000 0000 0000 0000 0000 0000"            /* ˇˇˇ............. */
	$"0000 0000 0000 0100 0000 0100 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 E000"            /* ..............‡. */
	$"0000 6265 6773 6F62 6A64 0000 003C 7075"            /* ..begsobjd...<pu */
	$"7368 566C 6964 0041 0014 0101 0000 0101"            /* shVlid.A........ */
	$"0000 0169 0000 0009 0000 0000 FFFF FFFF"            /* ...i...∆....ˇˇˇˇ */
	$"0000 0384 0000 0000 0000 0000 0000 0000"            /* ...Ñ............ */
	$"0170 0000 0453 6176 6501 6F62 6A64 0000"            /* .p...Save.objd.. */
	$"003E 7075 7368 436E 636C 0042 0014 0101"            /* .>pushCncl.B.... */
	$"0000 0101 0000 011B 0000 0009 0000 0000"            /* ...........∆.... */
	$"FFFF FFFF 0000 0385 0000 0000 0000 0000"            /* ˇˇˇˇ...Ö........ */
	$"0000 0000 0170 0000 0643 616E 6365 6C00"            /* .....p...Cancel. */
	$"6F62 6A64 0000 003E 7075 7368 5276 7274"            /* objd...>pushRvrt */
	$"0041 0014 0101 0100 0001 0000 001C 0000"            /* .A.............. */
	$"0009 0000 0000 FFFF FFFF 0000 0007 0000"            /* .∆....ˇˇˇˇ...... */
	$"0000 0000 0000 0000 0000 0170 0000 0652"            /* ...........p...R */
	$"6576 6572 7400 6F62 6A64 0000 0024 6963"            /* evert.objd...$ic */
	$"6E70 4C6F 636B 0010 0010 0101 0100 0001"            /* npLock.......... */
	$"0000 0006 0000 000B 0000 0000 FFFF FFFF"            /* ............ˇˇˇˇ */
	$"0000 656E 6473 656E 6473 656E 642E"                 /* ..endsendsend. */
};

data 'PPob' (10605, "Crsr Editor Window") {
	$"0002 646F 706C 4372 7356 6F62 6A64 0000"            /* ..doplCrsVobjd.. */
	$"001C 7769 6E64 296D 0002 1862 0000 0190"            /* ..wind)m...b...ê */
	$"0190 FFFF FFFF 01F4 0190 0000 0000 6265"            /* .êˇˇˇˇ.Ù.ê....be */
	$"6773 6F62 6A64 0000 0051 706C 6364 0000"            /* gsobjd...Qplcd.. */
	$"0000 01B8 013B 0101 0101 0101 0000 0000"            /* ...∏.;.......... */
	$"0000 0000 0000 0000 FFFF FFFF 0000 0000"            /* ........ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"0000 0001 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0150 0000 0062 6567 736F"            /* .......P...begso */
	$"626A 6400 0000 4A44 6362 6274 4C41 5300"            /* bjd...JDcbbtLAS. */
	$"1800 1801 0100 0000 0000 0000 0F00 0000"            /* ................ */
	$"0C00 0000 00FF FFFF FF74 4C41 5300 0000"            /* .....ˇˇˇˇtLAS... */
	$"0000 0001 0100 0023 2800 2100 0000 0000"            /* .......#(.!..... */
	$"0000 0000 0000 0000 0000 0000 0044 436C"            /* .............DCl */
	$"6B6F 626A 6400 0000 4A44 6362 6274 5345"            /* kobjd...JDcbbtSE */
	$"4C00 1800 1801 0100 0000 0000 0000 2900"            /* L.............). */
	$"0000 0C00 0000 00FF FFFF FF74 5345 4C00"            /* .......ˇˇˇˇtSEL. */
	$"0000 0000 0001 0100 0023 2900 2100 0000"            /* .........#).!... */
	$"0000 0000 0000 0000 0000 0000 0000 0044"            /* ...............D */
	$"436C 6B6F 626A 6400 0000 4662 6275 7474"            /* Clkobjd...Fbbutt */
	$"5458 5400 1800 1801 0100 0000 0000 0000"            /* TXT............. */
	$"0F00 0000 2600 0000 00FF FFFF FF74 5458"            /* ....&....ˇˇˇˇtTX */
	$"5400 0000 0000 0001 0100 0023 2A00 2100"            /* T..........#*.!. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"006F 626A 6400 0000 4662 6275 7474 5045"            /* .objd...FbbuttPE */
	$"4E00 1800 1801 0100 0000 0000 0000 2900"            /* N.............). */
	$"0000 2600 0000 00FF FFFF FF74 5045 4E00"            /* ..&....ˇˇˇˇtPEN. */
	$"0000 0000 0001 0100 0023 2B00 2100 0000"            /* .........#+.!... */
	$"0000 0000 0000 0000 0000 0000 0000 006F"            /* ...............o */
	$"626A 6400 0000 4A44 6362 6274 4552 4100"            /* bjd...JDcbbtERA. */
	$"1800 1801 0100 0000 0000 0000 0F00 0000"            /* ................ */
	$"4000 0000 00FF FFFF FF74 4552 4100 0000"            /* @....ˇˇˇˇtERA... */
	$"0000 0001 0100 0023 2C00 2100 0000 0000"            /* .......#,.!..... */
	$"0000 0000 0000 0000 0000 0000 0044 436C"            /* .............DCl */
	$"6B6F 626A 6400 0000 4662 6275 7474 4255"            /* kobjd...FbbuttBU */
	$"4300 1800 1801 0100 0000 0000 0000 2900"            /* C.............). */
	$"0000 4000 0000 00FF FFFF FF74 4255 4300"            /* ..@....ˇˇˇˇtBUC. */
	$"0000 0000 0001 0100 0023 2D00 2100 0000"            /* .........#-.!... */
	$"0000 0000 0000 0000 0000 0000 0000 006F"            /* ...............o */
	$"626A 6400 0000 4662 6275 7474 4452 4F00"            /* bjd...FbbuttDRO. */
	$"1800 1801 0100 0000 0000 0000 0F00 0000"            /* ................ */
	$"5A00 0000 00FF FFFF FF74 4452 4F00 0000"            /* Z....ˇˇˇˇtDRO... */
	$"0000 0001 0100 0023 2E00 2100 0000 0000"            /* .......#..!..... */
	$"0000 0000 0000 0000 0000 0000 006F 626A"            /* .............obj */
	$"6400 0000 4662 6275 7474 4C49 4E00 1800"            /* d...FbbuttLIN... */
	$"1801 0100 0000 0000 0000 2900 0000 5A00"            /* ..........)...Z. */
	$"0000 00FF FFFF FF74 4C49 4E00 0000 0000"            /* ...ˇˇˇˇtLIN..... */
	$"0001 0100 0023 2F00 2100 0000 0000 0000"            /* .....#/.!....... */
	$"0000 0000 0000 0000 0000 006F 626A 6400"            /* ...........objd. */
	$"0000 4662 6275 7474 5245 4300 1800 1801"            /* ..FbbuttREC..... */
	$"0100 0000 0000 0000 0F00 0000 7400 0000"            /* ............t... */
	$"00FF FFFF FF74 5245 4300 0000 0000 0001"            /* .ˇˇˇˇtREC....... */
	$"0100 0023 3100 2100 0000 0000 0000 0000"            /* ...#1.!......... */
	$"0000 0000 0000 0000 006F 626A 6400 0000"            /* .........objd... */
	$"4662 6275 7474 4652 4300 1800 1801 0100"            /* FbbuttFRC....... */
	$"0000 0000 0000 2900 0000 7400 0000 00FF"            /* ......)...t....ˇ */
	$"FFFF FF74 4652 4300 0000 0000 0001 0100"            /* ˇˇˇtFRC......... */
	$"0023 3000 2100 0000 0000 0000 0000 0000"            /* .#0.!........... */
	$"0000 0000 0000 006F 626A 6400 0000 4662"            /* .......objd...Fb */
	$"6275 7474 5252 4300 1800 1801 0100 0000"            /* buttRRC......... */
	$"0000 0000 0F00 0000 8E00 0000 00FF FFFF"            /* ........é....ˇˇˇ */
	$"FF74 5252 4300 0000 0000 0001 0100 0023"            /* ˇtRRC..........# */
	$"3300 2100 0000 0000 0000 0000 0000 0000"            /* 3.!............. */
	$"0000 0000 006F 626A 6400 0000 4662 6275"            /* .....objd...Fbbu */
	$"7474 4652 5200 1800 1801 0100 0000 0000"            /* ttFRR........... */
	$"0000 2900 0000 8E00 0000 00FF FFFF FF74"            /* ..)...é....ˇˇˇˇt */
	$"4652 5200 0000 0000 0001 0100 0023 3200"            /* FRR..........#2. */
	$"2100 0000 0000 0000 0000 0000 0000 0000"            /* !............... */
	$"0000 006F 626A 6400 0000 4662 6275 7474"            /* ...objd...Fbbutt */
	$"4F56 4C00 1800 1801 0100 0000 0000 0000"            /* OVL............. */
	$"0F00 0000 A800 0000 00FF FFFF FF74 4F56"            /* ....®....ˇˇˇˇtOV */
	$"4C00 0000 0000 0001 0100 0023 3500 2100"            /* L..........#5.!. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"006F 626A 6400 0000 4662 6275 7474 464F"            /* .objd...FbbuttFO */
	$"5600 1800 1801 0100 0000 0000 0000 2900"            /* V.............). */
	$"0000 A800 0000 00FF FFFF FF74 464F 5600"            /* ..®....ˇˇˇˇtFOV. */
	$"0000 0000 0001 0100 0023 3400 2100 0000"            /* .........#4.!... */
	$"0000 0000 0000 0000 0000 0000 0000 006F"            /* ...............o */
	$"626A 6400 0000 4662 6275 7474 484F 5400"            /* bjd...FbbuttHOT. */
	$"1800 1801 0100 0000 0000 0000 1C00 0000"            /* ................ */
	$"C200 0000 00FF FFFF FF74 484F 5400 0000"            /* ¬....ˇˇˇˇtHOT... */
	$"0000 0001 0100 0023 3600 2100 0000 0000"            /* .......#6.!..... */
	$"0000 0000 0000 0000 0000 0000 0064 6F70"            /* .............dop */
	$"6C50 6174 506F 626A 6400 0000 4662 6275"            /* lPatPobjd...Fbbu */
	$"7474 5041 5400 3200 1201 0100 0000 0000"            /* ttPAT.2......... */
	$"0000 0F00 0000 E300 0003 E8FF FFFF FF74"            /* ......„...Ëˇˇˇˇt */
	$"5041 5400 0000 0000 0000 0000 0000 0000"            /* PAT............. */
	$"2100 0000 0000 0000 0000 0000 0000 0000"            /* !............... */
	$"0000 006F 626A 6400 0000 4E43 6F6C 5074"            /* ...objd...NColPt */
	$"4243 4C00 2800 1001 0101 0100 0000 0000"            /* BCL.(........... */
	$"1B00 0001 0900 FFFF FFFF FFFF FF74 4243"            /* ....∆.ˇˇˇˇˇˇˇtBC */
	$"4C00 0000 0000 0000 0000 0000 0000 2100"            /* L.............!. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"00FF FFFF FFFF FF01 006F 626A 6400 0000"            /* .ˇˇˇˇˇˇ..objd... */
	$"4E43 6F6C 5074 4643 4C00 2800 1001 0101"            /* NColPtFCL.(..... */
	$"0100 0000 0000 0F00 0000 FC00 0000 00FF"            /* ..........¸....ˇ */
	$"FFFF FF74 4643 4C00 0000 0000 0000 0000"            /* ˇˇˇtFCL......... */
	$"0000 0000 2100 0000 0000 0000 0000 0000"            /* ....!........... */
	$"0000 0000 0000 0000 0000 0000 0000 006F"            /* ...............o */
	$"626A 6400 0000 5174 6762 7845 4E43 4C01"            /* bjd...QtgbxENCL. */
	$"2C01 2C01 0101 0100 0000 0000 5000 0000"            /* ,.,.........P... */
	$"0A00 0000 00FF FFFF FF00 0000 0000 0000"            /* ¬....ˇˇˇˇ....... */
	$"0000 0000 0000 0000 0000 0000 0100 0000"            /* ................ */
	$"0100 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 A000 0000 6265 6773 646F 706C"            /* ....†...begsdopl */
	$"4943 4E56 6F62 6A64 0000 003C 7669 6577"            /* ICNVobjd...<view */
	$"436E 7473 0124 0124 0101 0101 0101 0000"            /* Cnts.$.$........ */
	$"0004 0000 0004 0000 0000 FFFF FFFF 0000"            /* ..........ˇˇˇˇ.. */
	$"0000 0000 0004 0000 0000 0000 0000 0000"            /* ................ */
	$"0014 0000 0014 0001 656E 6473 6F62 6A64"            /* ........endsobjd */
	$"0000 003C 7669 6577 5341 4D50 0028 00C0"            /* ...<viewSAMP.(.¿ */
	$"0101 0000 0000 0000 0186 0000 0014 0000"            /* .........Ü...... */
	$"0000 FFFF FFFF 0000 0000 0000 0000 0000"            /* ..ˇˇˇˇ.......... */
	$"0000 0000 0000 0000 0001 0000 0001 0000"            /* ................ */
	$"6265 6773 646F 706C 4454 5677 6F62 6A64"            /* begsdoplDTVwobjd */
	$"0000 003C 7669 6577 6372 7372 001C 0028"            /* ...<viewcrsr...( */
	$"0101 0000 0000 0000 0006 0000 0007 0000"            /* ................ */
	$"0000 FFFF FFFF 0000 0000 0000 0000 0000"            /* ..ˇˇˇˇ.......... */
	$"0000 0000 0000 0000 0001 0000 0001 0000"            /* ................ */
	$"6F62 6A64 0000 003C 7374 7874 0000 0000"            /* objd...<stxt.... */
	$"0028 0010 0101 0000 0000 0000 0000 0000"            /* .(.............. */
	$"0030 0000 0000 FFFF FFFF 0000 0000 0000"            /* .0....ˇˇˇˇ...... */
	$"0000 0000 0000 0000 0000 0120 008D 0543"            /* ........... .ç.C */
	$"6F6C 6F72 646F 706C 4454 5677 6F62 6A64"            /* olordoplDTVwobjd */
	$"0000 003C 7669 6577 4355 5253 001C 0028"            /* ...<viewCURS...( */
	$"0101 0000 0000 0000 0006 0000 0045 0000"            /* .............E.. */
	$"0000 FFFF FFFF 0000 0000 0000 0000 0000"            /* ..ˇˇˇˇ.......... */
	$"0000 0000 0000 0000 0001 0000 0001 0000"            /* ................ */
	$"6F62 6A64 0000 003A 7374 7874 0000 0000"            /* objd...:stxt.... */
	$"0022 0010 0101 0000 0000 0000 0003 0000"            /* .".............. */
	$"006E 0000 0000 FFFF FFFF 0000 0000 0000"            /* .n....ˇˇˇˇ...... */
	$"0000 0000 0000 0000 0000 0120 008D 0342"            /* ........... .ç.B */
	$"2657 646F 706C 4454 5677 6F62 6A64 0000"            /* &WdoplDTVwobjd.. */
	$"003C 7669 6577 4D41 534B 001C 0028 0101"            /* .<viewMASK...(.. */
	$"0000 0000 0000 0006 0000 0083 0000 0001"            /* ...........É.... */
	$"FFFF FFFF 0000 0000 0000 0000 0000 0000"            /* ˇˇˇˇ............ */
	$"0000 0000 0000 0001 0000 0001 0000 6F62"            /* ..............ob */
	$"6A64 0000 003B 7374 7874 0000 0000 0022"            /* jd...;stxt....." */
	$"0010 0101 0000 0000 0000 0003 0000 00AC"            /* ...............¨ */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0120 008D 044D 6173"            /* ......... .ç.Mas */
	$"6B65 6E64 736F 626A 6400 0000 3773 7478"            /* kendsobjd...7stx */
	$"7443 4F4F 5200 3C00 1001 0100 0000 0000"            /* tCOOR.<......... */
	$"0000 0B00 0001 2000 0000 00FF FFFF FF00"            /* ...... ....ˇˇˇˇ. */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"2000 0000 656E 6473 6F62 6A64 0000 0051"            /*  ...endsobjd...Q */
	$"706C 6364 464F 4F54 01B8 0028 0101 0100"            /* plcdFOOT.∏.(.... */
	$"0101 0000 0000 0000 013B 0000 0000 FFFF"            /* .........;....ˇˇ */
	$"FFFF 0000 0000 0000 0000 0000 0000 0000"            /* ˇˇ.............. */
	$"0000 0000 0001 0000 0001 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 00E0 0000"            /* .............‡.. */
	$"0062 6567 736F 626A 6400 0000 3C70 7573"            /* .begsobjd...<pus */
	$"6856 6C69 6400 4100 1401 0100 0001 0100"            /* hVlid.A......... */
	$"0001 6900 0000 0900 0000 00FF FFFF FF00"            /* ..i...∆....ˇˇˇˇ. */
	$"0003 8400 0000 0000 0000 0000 0000 0001"            /* ..Ñ............. */
	$"7000 0004 5361 7665 016F 626A 6400 0000"            /* p...Save.objd... */
	$"3E70 7573 6843 6E63 6C00 4200 1401 0100"            /* >pushCncl.B..... */
	$"0001 0100 0001 1B00 0000 0900 0000 00FF"            /* ..........∆....ˇ */
	$"FFFF FF00 0003 8500 0000 0000 0000 0000"            /* ˇˇˇ...Ö......... */
	$"0000 0001 7000 0006 4361 6E63 656C 006F"            /* ....p...Cancel.o */
	$"626A 6400 0000 3E70 7573 6852 7672 7400"            /* bjd...>pushRvrt. */
	$"4100 1401 0101 0000 0100 0000 1C00 0000"            /* A............... */
	$"0900 0000 00FF FFFF FF00 0000 0700 0000"            /* ∆....ˇˇˇˇ....... */
	$"0000 0000 0000 0000 0001 7000 0006 5265"            /* ..........p...Re */
	$"7665 7274 006F 626A 6400 0000 2469 636E"            /* vert.objd...$icn */
	$"704C 6F63 6B00 1000 1001 0101 0000 0100"            /* pLock........... */
	$"0000 0600 0000 0B00 0000 00FF FFFF FF00"            /* ...........ˇˇˇˇ. */
	$"0065 6E64 7365 6E64 7365 6E64 2E"                   /* .endsendsend. */
};

data 'PPob' (10606, "Pattern Editor Window") {
	$"0002 646F 706C 5061 7456 6F62 6A64 0000"            /* ..doplPatVobjd.. */
	$"001C 7769 6E64 296E 0002 1862 0000 0190"            /* ..wind)n...b...ê */
	$"0190 FFFF FFFF 0208 0190 0000 0000 6265"            /* .êˇˇˇˇ...ê....be */
	$"6773 6F62 6A64 0000 0051 706C 6364 0000"            /* gsobjd...Qplcd.. */
	$"0000 0119 0118 0101 0101 0101 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 FFFF FFFF 0000 0000"            /* ........ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"0000 0001 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0150 0000 0062 6567 736F"            /* .......P...begso */
	$"626A 6400 0000 4A44 6362 6274 4C41 5300"            /* bjd...JDcbbtLAS. */
	$"1800 1801 0100 0000 0000 0000 0F00 0000"            /* ................ */
	$"0C00 0000 00FF FFFF FF74 4C41 5300 0000"            /* .....ˇˇˇˇtLAS... */
	$"0000 0001 0100 0023 2800 2100 0000 0000"            /* .......#(.!..... */
	$"0000 0000 0000 0000 0000 0000 0044 436C"            /* .............DCl */
	$"6B6F 626A 6400 0000 4A44 6362 6274 5345"            /* kobjd...JDcbbtSE */
	$"4C00 1800 1801 0100 0000 0000 0000 2900"            /* L.............). */
	$"0000 0C00 0000 00FF FFFF FF74 5345 4C00"            /* .......ˇˇˇˇtSEL. */
	$"0000 0000 0001 0100 0023 2900 2100 0000"            /* .........#).!... */
	$"0000 0000 0000 0000 0000 0000 0000 0044"            /* ...............D */
	$"436C 6B6F 626A 6400 0000 4662 6275 7474"            /* Clkobjd...Fbbutt */
	$"5458 5400 1800 1801 0100 0000 0000 0000"            /* TXT............. */
	$"0F00 0000 2600 0000 00FF FFFF FF74 5458"            /* ....&....ˇˇˇˇtTX */
	$"5400 0000 0000 0001 0100 0023 2A00 2100"            /* T..........#*.!. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"006F 626A 6400 0000 4662 6275 7474 5045"            /* .objd...FbbuttPE */
	$"4E00 1800 1801 0100 0000 0000 0000 2900"            /* N.............). */
	$"0000 2600 0000 00FF FFFF FF74 5045 4E00"            /* ..&....ˇˇˇˇtPEN. */
	$"0000 0000 0001 0100 0023 2B00 2100 0000"            /* .........#+.!... */
	$"0000 0000 0000 0000 0000 0000 0000 006F"            /* ...............o */
	$"626A 6400 0000 4A44 6362 6274 4552 4100"            /* bjd...JDcbbtERA. */
	$"1800 1801 0100 0000 0000 0000 0F00 0000"            /* ................ */
	$"4000 0000 00FF FFFF FF74 4552 4100 0000"            /* @....ˇˇˇˇtERA... */
	$"0000 0001 0100 0023 2C00 2100 0000 0000"            /* .......#,.!..... */
	$"0000 0000 0000 0000 0000 0000 0044 436C"            /* .............DCl */
	$"6B6F 626A 6400 0000 4662 6275 7474 4255"            /* kobjd...FbbuttBU */
	$"4300 1800 1801 0100 0000 0000 0000 2900"            /* C.............). */
	$"0000 4000 0000 00FF FFFF FF74 4255 4300"            /* ..@....ˇˇˇˇtBUC. */
	$"0000 0000 0001 0100 0023 2D00 2100 0000"            /* .........#-.!... */
	$"0000 0000 0000 0000 0000 0000 0000 006F"            /* ...............o */
	$"626A 6400 0000 4662 6275 7474 4452 4F00"            /* bjd...FbbuttDRO. */
	$"1800 1801 0100 0000 0000 0000 0F00 0000"            /* ................ */
	$"5A00 0000 00FF FFFF FF74 4452 4F00 0000"            /* Z....ˇˇˇˇtDRO... */
	$"0000 0001 0100 0023 2E00 2100 0000 0000"            /* .......#..!..... */
	$"0000 0000 0000 0000 0000 0000 006F 626A"            /* .............obj */
	$"6400 0000 4662 6275 7474 4C49 4E00 1800"            /* d...FbbuttLIN... */
	$"1801 0100 0000 0000 0000 2900 0000 5A00"            /* ..........)...Z. */
	$"0000 00FF FFFF FF74 4C49 4E00 0000 0000"            /* ...ˇˇˇˇtLIN..... */
	$"0001 0100 0023 2F00 2100 0000 0000 0000"            /* .....#/.!....... */
	$"0000 0000 0000 0000 0000 006F 626A 6400"            /* ...........objd. */
	$"0000 4662 6275 7474 5245 4300 1800 1801"            /* ..FbbuttREC..... */
	$"0100 0000 0000 0000 0F00 0000 7400 0000"            /* ............t... */
	$"00FF FFFF FF74 5245 4300 0000 0000 0001"            /* .ˇˇˇˇtREC....... */
	$"0100 0023 3100 2100 0000 0000 0000 0000"            /* ...#1.!......... */
	$"0000 0000 0000 0000 006F 626A 6400 0000"            /* .........objd... */
	$"4662 6275 7474 4652 4300 1800 1801 0100"            /* FbbuttFRC....... */
	$"0000 0000 0000 2900 0000 7400 0000 00FF"            /* ......)...t....ˇ */
	$"FFFF FF74 4652 4300 0000 0000 0001 0100"            /* ˇˇˇtFRC......... */
	$"0023 3000 2100 0000 0000 0000 0000 0000"            /* .#0.!........... */
	$"0000 0000 0000 006F 626A 6400 0000 4662"            /* .......objd...Fb */
	$"6275 7474 5252 4300 1800 1801 0100 0000"            /* buttRRC......... */
	$"0000 0000 0F00 0000 8E00 0000 00FF FFFF"            /* ........é....ˇˇˇ */
	$"FF74 5252 4300 0000 0000 0001 0100 0023"            /* ˇtRRC..........# */
	$"3300 2100 0000 0000 0000 0000 0000 0000"            /* 3.!............. */
	$"0000 0000 006F 626A 6400 0000 4662 6275"            /* .....objd...Fbbu */
	$"7474 4652 5200 1800 1801 0100 0000 0000"            /* ttFRR........... */
	$"0000 2900 0000 8E00 0000 00FF FFFF FF74"            /* ..)...é....ˇˇˇˇt */
	$"4652 5200 0000 0000 0001 0100 0023 3200"            /* FRR..........#2. */
	$"2100 0000 0000 0000 0000 0000 0000 0000"            /* !............... */
	$"0000 006F 626A 6400 0000 4662 6275 7474"            /* ...objd...Fbbutt */
	$"4F56 4C00 1800 1801 0100 0000 0000 0000"            /* OVL............. */
	$"0F00 0000 A800 0000 00FF FFFF FF74 4F56"            /* ....®....ˇˇˇˇtOV */
	$"4C00 0000 0000 0001 0100 0023 3500 2100"            /* L..........#5.!. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"006F 626A 6400 0000 4662 6275 7474 464F"            /* .objd...FbbuttFO */
	$"5600 1800 1801 0100 0000 0000 0000 2900"            /* V.............). */
	$"0000 A800 0000 00FF FFFF FF74 464F 5600"            /* ..®....ˇˇˇˇtFOV. */
	$"0000 0000 0001 0100 0023 3400 2100 0000"            /* .........#4.!... */
	$"0000 0000 0000 0000 0000 0000 0000 0064"            /* ...............d */
	$"6F70 6C50 6174 506F 626A 6400 0000 4662"            /* oplPatPobjd...Fb */
	$"6275 7474 5041 5400 3200 1201 0100 0000"            /* buttPAT.2....... */
	$"0000 0000 0F00 0000 C700 0003 E8FF FFFF"            /* ........«...Ëˇˇˇ */
	$"FF74 5041 5400 0000 0000 0000 0000 0000"            /* ˇtPAT........... */
	$"0000 2100 0000 0000 0000 0000 0000 0000"            /* ..!............. */
	$"0000 0000 006F 626A 6400 0000 4E43 6F6C"            /* .....objd...NCol */
	$"5074 4243 4C00 2800 1001 0101 0100 0000"            /* PtBCL.(......... */
	$"0000 1B00 0000 EC00 FFFF FFFF FFFF FF74"            /* ......Ï.ˇˇˇˇˇˇˇt */
	$"4243 4C00 0000 0000 0000 0000 0000 0000"            /* BCL............. */
	$"2100 0000 0000 0000 0000 0000 0000 0000"            /* !............... */
	$"0000 0000 0000 0000 0001 006F 626A 6400"            /* ...........objd. */
	$"0000 4E43 6F6C 5074 4643 4C00 2800 1001"            /* ..NColPtFCL.(... */
	$"0101 0100 0000 0000 0F00 0000 E000 0000"            /* ............‡... */
	$"00FF FFFF FF74 4643 4C00 0000 0000 0000"            /* .ˇˇˇˇtFCL....... */
	$"0000 0000 0000 2100 0000 0000 0000 0000"            /* ......!......... */
	$"0000 0000 0000 0000 00FF FFFF FFFF FF00"            /* .........ˇˇˇˇˇˇ. */
	$"006F 626A 6400 0000 5174 6762 7845 4E43"            /* .objd...QtgbxENC */
	$"4C00 7900 7901 0101 0100 0000 0000 5000"            /* L.y.y.........P. */
	$"0000 0A00 0000 00FF FFFF FF00 0000 0000"            /* ..¬....ˇˇˇˇ..... */
	$"0000 0000 0000 0000 0000 0000 0000 0100"            /* ................ */
	$"0000 0100 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 A000 0000 6265 6773 646F"            /* ......†...begsdo */
	$"706C 4943 4E56 6F62 6A64 0000 003C 7669"            /* plICNVobjd...<vi */
	$"6577 436E 7473 0071 0071 0101 0101 0101"            /* ewCnts.q.q...... */
	$"0000 0004 0000 0004 0000 0000 FFFF FFFF"            /* ............ˇˇˇˇ */
	$"0000 0000 0000 0004 0000 0000 0000 0000"            /* ................ */
	$"0000 0014 0000 0014 0001 656E 6473 6F62"            /* ..........endsob */
	$"6A64 0000 003C 7669 6577 5341 4D50 003C"            /* jd...<viewSAMP.< */
	$"0048 0101 0000 0000 0000 00D3 0000 0024"            /* .H.........”...$ */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0000 0001 0000 0001"            /* ................ */
	$"0000 6265 6773 646F 706C 5054 5677 6F62"            /* ..begsdoplPTVwob */
	$"6A64 0000 003C 7669 6577 4257 5054 002C"            /* jd...<viewBWPT., */
	$"0038 0101 0000 0000 0000 0008 0000 0008"            /* .8.............. */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0000 0001 0000 0001"            /* ................ */
	$"0000 656E 6473 6F62 6A64 0000 0037 7374"            /* ..endsobjd...7st */
	$"7874 434F 4F52 003C 0010 0101 0000 0000"            /* xtCOOR.<........ */
	$"0000 000A 0000 0107 0000 0000 FFFF FFFF"            /* ...¬........ˇˇˇˇ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0120 0000 0065 6E64 736F 626A 6400 0000"            /* . ...endsobjd... */
	$"5170 6C63 6446 4F4F 5401 1900 2801 0101"            /* QplcdFOOT...(... */
	$"0001 0100 0000 0000 0001 1800 0000 00FF"            /* ...............ˇ */
	$"FFFF FF00 0000 0000 0000 0000 0000 0000"            /* ˇˇˇ............. */
	$"0000 0000 0000 0100 0000 0100 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 E000"            /* ..............‡. */
	$"0000 6265 6773 6F62 6A64 0000 003C 7075"            /* ..begsobjd...<pu */
	$"7368 566C 6964 0041 0014 0101 0000 0101"            /* shVlid.A........ */
	$"0000 00CC 0000 0009 0000 0000 FFFF FFFF"            /* ...Ã...∆....ˇˇˇˇ */
	$"0000 0384 0000 0000 0000 0000 0000 0000"            /* ...Ñ............ */
	$"0170 0000 0453 6176 6501 6F62 6A64 0000"            /* .p...Save.objd.. */
	$"003E 7075 7368 436E 636C 0041 0014 0101"            /* .>pushCncl.A.... */
	$"0000 0101 0000 007F 0000 0009 0000 0000"            /* ...........∆.... */
	$"FFFF FFFF 0000 0385 0000 0000 0000 0000"            /* ˇˇˇˇ...Ö........ */
	$"0000 0000 0170 0000 0643 616E 6365 6C00"            /* .....p...Cancel. */
	$"6F62 6A64 0000 003E 7075 7368 5276 7274"            /* objd...>pushRvrt */
	$"0041 0014 0101 0100 0001 0000 001B 0000"            /* .A.............. */
	$"0009 0000 0000 FFFF FFFF 0000 0007 0000"            /* .∆....ˇˇˇˇ...... */
	$"0000 0000 0000 0000 0000 0170 0000 0652"            /* ...........p...R */
	$"6576 6572 7400 6F62 6A64 0000 0024 6963"            /* evert.objd...$ic */
	$"6E70 4C6F 636B 0010 0010 0101 0100 0001"            /* npLock.......... */
	$"0000 0006 0000 000B 0000 0000 FFFF FFFF"            /* ............ˇˇˇˇ */
	$"0000 656E 6473 656E 6473 656E 642E"                 /* ..endsendsend. */
};

data 'PPob' (10607, "PixPat Editor Window") {
	$"0002 646F 706C 5061 7456 6F62 6A64 0000"            /* ..doplPatVobjd.. */
	$"001C 7769 6E64 296F 0002 1862 0000 0190"            /* ..wind)o...b...ê */
	$"0190 FFFF FFFF 0208 0190 0000 0000 6265"            /* .êˇˇˇˇ...ê....be */
	$"6773 6F62 6A64 0000 0051 706C 6364 0000"            /* gsobjd...Qplcd.. */
	$"0000 0119 0118 0101 0101 0101 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 FFFF FFFF 0000 0000"            /* ........ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"0000 0001 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0150 0000 0062 6567 736F"            /* .......P...begso */
	$"626A 6400 0000 4A44 6362 6274 4C41 5300"            /* bjd...JDcbbtLAS. */
	$"1800 1801 0100 0000 0000 0000 0F00 0000"            /* ................ */
	$"0C00 0000 00FF FFFF FF74 4C41 5300 0000"            /* .....ˇˇˇˇtLAS... */
	$"0000 0001 0100 0023 2800 2100 0000 0000"            /* .......#(.!..... */
	$"0000 0000 0000 0000 0000 0000 0044 436C"            /* .............DCl */
	$"6B6F 626A 6400 0000 4A44 6362 6274 5345"            /* kobjd...JDcbbtSE */
	$"4C00 1800 1801 0100 0000 0000 0000 2900"            /* L.............). */
	$"0000 0C00 0000 00FF FFFF FF74 5345 4C00"            /* .......ˇˇˇˇtSEL. */
	$"0000 0000 0001 0100 0023 2900 2100 0000"            /* .........#).!... */
	$"0000 0000 0000 0000 0000 0000 0000 0044"            /* ...............D */
	$"436C 6B6F 626A 6400 0000 4662 6275 7474"            /* Clkobjd...Fbbutt */
	$"5458 5400 1800 1801 0100 0000 0000 0000"            /* TXT............. */
	$"0F00 0000 2600 0000 00FF FFFF FF74 5458"            /* ....&....ˇˇˇˇtTX */
	$"5400 0000 0000 0001 0100 0023 2A00 2100"            /* T..........#*.!. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"006F 626A 6400 0000 4662 6275 7474 5045"            /* .objd...FbbuttPE */
	$"4E00 1800 1801 0100 0000 0000 0000 2900"            /* N.............). */
	$"0000 2600 0000 00FF FFFF FF74 5045 4E00"            /* ..&....ˇˇˇˇtPEN. */
	$"0000 0000 0001 0100 0023 2B00 2100 0000"            /* .........#+.!... */
	$"0000 0000 0000 0000 0000 0000 0000 006F"            /* ...............o */
	$"626A 6400 0000 4A44 6362 6274 4552 4100"            /* bjd...JDcbbtERA. */
	$"1800 1801 0100 0000 0000 0000 0F00 0000"            /* ................ */
	$"4000 0000 00FF FFFF FF74 4552 4100 0000"            /* @....ˇˇˇˇtERA... */
	$"0000 0001 0100 0023 2C00 2100 0000 0000"            /* .......#,.!..... */
	$"0000 0000 0000 0000 0000 0000 0044 436C"            /* .............DCl */
	$"6B6F 626A 6400 0000 4662 6275 7474 4255"            /* kobjd...FbbuttBU */
	$"4300 1800 1801 0100 0000 0000 0000 2900"            /* C.............). */
	$"0000 4000 0000 00FF FFFF FF74 4255 4300"            /* ..@....ˇˇˇˇtBUC. */
	$"0000 0000 0001 0100 0023 2D00 2100 0000"            /* .........#-.!... */
	$"0000 0000 0000 0000 0000 0000 0000 006F"            /* ...............o */
	$"626A 6400 0000 4662 6275 7474 4452 4F00"            /* bjd...FbbuttDRO. */
	$"1800 1801 0100 0000 0000 0000 0F00 0000"            /* ................ */
	$"5A00 0000 00FF FFFF FF74 4452 4F00 0000"            /* Z....ˇˇˇˇtDRO... */
	$"0000 0001 0100 0023 2E00 2100 0000 0000"            /* .......#..!..... */
	$"0000 0000 0000 0000 0000 0000 006F 626A"            /* .............obj */
	$"6400 0000 4662 6275 7474 4C49 4E00 1800"            /* d...FbbuttLIN... */
	$"1801 0100 0000 0000 0000 2900 0000 5A00"            /* ..........)...Z. */
	$"0000 00FF FFFF FF74 4C49 4E00 0000 0000"            /* ...ˇˇˇˇtLIN..... */
	$"0001 0100 0023 2F00 2100 0000 0000 0000"            /* .....#/.!....... */
	$"0000 0000 0000 0000 0000 006F 626A 6400"            /* ...........objd. */
	$"0000 4662 6275 7474 5245 4300 1800 1801"            /* ..FbbuttREC..... */
	$"0100 0000 0000 0000 0F00 0000 7400 0000"            /* ............t... */
	$"00FF FFFF FF74 5245 4300 0000 0000 0001"            /* .ˇˇˇˇtREC....... */
	$"0100 0023 3100 2100 0000 0000 0000 0000"            /* ...#1.!......... */
	$"0000 0000 0000 0000 006F 626A 6400 0000"            /* .........objd... */
	$"4662 6275 7474 4652 4300 1800 1801 0100"            /* FbbuttFRC....... */
	$"0000 0000 0000 2900 0000 7400 0000 00FF"            /* ......)...t....ˇ */
	$"FFFF FF74 4652 4300 0000 0000 0001 0100"            /* ˇˇˇtFRC......... */
	$"0023 3000 2100 0000 0000 0000 0000 0000"            /* .#0.!........... */
	$"0000 0000 0000 006F 626A 6400 0000 4662"            /* .......objd...Fb */
	$"6275 7474 5252 4300 1800 1801 0100 0000"            /* buttRRC......... */
	$"0000 0000 0F00 0000 8E00 0000 00FF FFFF"            /* ........é....ˇˇˇ */
	$"FF74 5252 4300 0000 0000 0001 0100 0023"            /* ˇtRRC..........# */
	$"3300 2100 0000 0000 0000 0000 0000 0000"            /* 3.!............. */
	$"0000 0000 006F 626A 6400 0000 4662 6275"            /* .....objd...Fbbu */
	$"7474 4652 5200 1800 1801 0100 0000 0000"            /* ttFRR........... */
	$"0000 2900 0000 8E00 0000 00FF FFFF FF74"            /* ..)...é....ˇˇˇˇt */
	$"4652 5200 0000 0000 0001 0100 0023 3200"            /* FRR..........#2. */
	$"2100 0000 0000 0000 0000 0000 0000 0000"            /* !............... */
	$"0000 006F 626A 6400 0000 4662 6275 7474"            /* ...objd...Fbbutt */
	$"4F56 4C00 1800 1801 0100 0000 0000 0000"            /* OVL............. */
	$"0F00 0000 A800 0000 00FF FFFF FF74 4F56"            /* ....®....ˇˇˇˇtOV */
	$"4C00 0000 0000 0001 0100 0023 3500 2100"            /* L..........#5.!. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"006F 626A 6400 0000 4662 6275 7474 464F"            /* .objd...FbbuttFO */
	$"5600 1800 1801 0100 0000 0000 0000 2900"            /* V.............). */
	$"0000 A800 0000 00FF FFFF FF74 464F 5600"            /* ..®....ˇˇˇˇtFOV. */
	$"0000 0000 0001 0100 0023 3400 2100 0000"            /* .........#4.!... */
	$"0000 0000 0000 0000 0000 0000 0000 0064"            /* ...............d */
	$"6F70 6C50 6174 506F 626A 6400 0000 4662"            /* oplPatPobjd...Fb */
	$"6275 7474 5041 5400 3200 1201 0100 0000"            /* buttPAT.2....... */
	$"0000 0000 0F00 0000 C700 0003 E8FF FFFF"            /* ........«...Ëˇˇˇ */
	$"FF74 5041 5400 0000 0000 0000 0000 0000"            /* ˇtPAT........... */
	$"0000 2100 0000 0000 0000 0000 0000 0000"            /* ..!............. */
	$"0000 0000 006F 626A 6400 0000 4E43 6F6C"            /* .....objd...NCol */
	$"5074 4243 4C00 2800 1001 0101 0100 0000"            /* PtBCL.(......... */
	$"0000 1B00 0000 EB00 FFFF FFFF FFFF FF74"            /* ......Î.ˇˇˇˇˇˇˇt */
	$"4243 4C00 0000 0000 0000 0000 0000 0000"            /* BCL............. */
	$"2100 0000 0000 0000 0000 0000 0000 0000"            /* !............... */
	$"0000 00FF FFFF FFFF FF01 006F 626A 6400"            /* ...ˇˇˇˇˇˇ..objd. */
	$"0000 4E43 6F6C 5074 4643 4C00 2800 1001"            /* ..NColPtFCL.(... */
	$"0101 0100 0000 0000 0F00 0000 DF00 0000"            /* ............ﬂ... */
	$"00FF FFFF FF74 4643 4C00 0000 0000 0000"            /* .ˇˇˇˇtFCL....... */
	$"0000 0000 0000 2100 0000 0000 0000 0000"            /* ......!......... */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"006F 626A 6400 0000 5174 6762 7845 4E43"            /* .objd...QtgbxENC */
	$"4C00 7900 7901 0101 0100 0000 0000 5000"            /* L.y.y.........P. */
	$"0000 0A00 0000 00FF FFFF FF00 0000 0000"            /* ..¬....ˇˇˇˇ..... */
	$"0000 0000 0000 0000 0000 0000 0000 0100"            /* ................ */
	$"0000 0100 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 A000 0000 6265 6773 646F"            /* ......†...begsdo */
	$"706C 4943 4E56 6F62 6A64 0000 003C 7669"            /* plICNVobjd...<vi */
	$"6577 436E 7473 0071 0071 0101 0101 0101"            /* ewCnts.q.q...... */
	$"0000 0004 0000 0004 0000 0000 FFFF FFFF"            /* ............ˇˇˇˇ */
	$"0000 0000 0000 0004 0000 0000 0000 0000"            /* ................ */
	$"0000 0014 0000 0014 0001 656E 6473 6F62"            /* ..........endsob */
	$"6A64 0000 003C 7669 6577 5341 4D50 003C"            /* jd...<viewSAMP.< */
	$"00A6 0101 0000 0000 0000 00D3 0000 000B"            /* .¶.........”.... */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0000 0001 0000 0001"            /* ................ */
	$"0000 6265 6773 646F 706C 5054 5677 6F62"            /* ..begsdoplPTVwob */
	$"6A64 0000 003C 7669 6577 7070 6174 002C"            /* jd...<viewppat., */
	$"0038 0101 0000 0000 0000 0008 0000 0008"            /* .8.............. */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0000 0001 0000 0001"            /* ................ */
	$"0000 6F62 6A64 0000 003B 7374 7874 4E41"            /* ..objd...;stxtNA */
	$"4D31 002C 0010 0101 0000 0000 0000 0008"            /* M1.,............ */
	$"0000 0040 0000 0000 FFFF FFFF 0000 0000"            /* ...@....ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0120 008D"            /* ............. .ç */
	$"0470 7061 7464 6F70 6C50 5456 776F 626A"            /* .ppatdoplPTVwobj */
	$"6400 0000 3C76 6965 7742 5750 5400 2C00"            /* d...<viewBWPT.,. */
	$"3801 0100 0000 0000 0000 0800 0000 5600"            /* 8.............V. */
	$"0000 00FF FFFF FF00 0000 0000 0000 0000"            /* ...ˇˇˇˇ......... */
	$"0000 0000 0000 0000 0000 0100 0000 0100"            /* ................ */
	$"006F 626A 6400 0000 3B73 7478 744E 414D"            /* .objd...;stxtNAM */
	$"3200 2C00 1001 0100 0000 0000 0000 0800"            /* 2.,............. */
	$"0000 8E00 0000 00FF FFFF FF00 0000 0000"            /* ..é....ˇˇˇˇ..... */
	$"0000 0000 0000 0000 0000 0001 2000 8D04"            /* ............ .ç. */
	$"5041 5420 656E 6473 6F62 6A64 0000 0037"            /* PAT endsobjd...7 */
	$"7374 7874 434F 4F52 003C 0010 0101 0000"            /* stxtCOOR.<...... */
	$"0000 0000 000A 0000 0107 0000 0000 FFFF"            /* .....¬........ˇˇ */
	$"FFFF 0000 0000 0000 0000 0000 0000 0000"            /* ˇˇ.............. */
	$"0000 0120 0000 0065 6E64 736F 626A 6400"            /* ... ...endsobjd. */
	$"0000 5170 6C63 6446 4F4F 5401 1900 2801"            /* ..QplcdFOOT...(. */
	$"0101 0001 0100 0000 0000 0001 1800 0000"            /* ................ */
	$"00FF FFFF FF00 0000 0000 0000 0000 0000"            /* .ˇˇˇˇ........... */
	$"0000 0000 0000 0000 0100 0000 0100 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"E000 0000 6265 6773 6F62 6A64 0000 003C"            /* ‡...begsobjd...< */
	$"7075 7368 566C 6964 0041 0014 0101 0000"            /* pushVlid.A...... */
	$"0101 0000 00CC 0000 0009 0000 0000 FFFF"            /* .....Ã...∆....ˇˇ */
	$"FFFF 0000 0384 0000 0000 0000 0000 0000"            /* ˇˇ...Ñ.......... */
	$"0000 0170 0000 0453 6176 6501 6F62 6A64"            /* ...p...Save.objd */
	$"0000 003E 7075 7368 436E 636C 0041 0014"            /* ...>pushCncl.A.. */
	$"0101 0000 0101 0000 007F 0000 0009 0000"            /* .............∆.. */
	$"0000 FFFF FFFF 0000 0385 0000 0000 0000"            /* ..ˇˇˇˇ...Ö...... */
	$"0000 0000 0000 0170 0000 0643 616E 6365"            /* .......p...Cance */
	$"6C00 6F62 6A64 0000 003E 7075 7368 5276"            /* l.objd...>pushRv */
	$"7274 0041 0014 0101 0100 0001 0000 001B"            /* rt.A............ */
	$"0000 0009 0000 0000 FFFF FFFF 0000 0007"            /* ...∆....ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0170 0000"            /* .............p.. */
	$"0652 6576 6572 7400 6F62 6A64 0000 0024"            /* .Revert.objd...$ */
	$"6963 6E70 4C6F 636B 0010 0010 0101 0100"            /* icnpLock........ */
	$"0001 0000 0006 0000 000B 0000 0000 FFFF"            /* ..............ˇˇ */
	$"FFFF 0000 656E 6473 656E 6473 656E 642E"            /* ˇˇ..endsendsend. */
};

data 'PPob' (10608, "Pattern Suite Editor Window") {
	$"0002 646F 706C 5061 5356 6F62 6A64 0000"            /* ..doplPaSVobjd.. */
	$"001C 7769 6E64 2970 0002 1862 0000 0190"            /* ..wind)p...b...ê */
	$"0190 FFFF FFFF 0208 0190 0000 0000 6265"            /* .êˇˇˇˇ...ê....be */
	$"6773 6F62 6A64 0000 0051 706C 6364 0000"            /* gsobjd...Qplcd.. */
	$"0000 0119 0118 0101 0101 0101 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 FFFF FFFF 0000 0000"            /* ........ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"0000 0001 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0150 0000 0062 6567 736F"            /* .......P...begso */
	$"626A 6400 0000 4A44 6362 6274 4C41 5300"            /* bjd...JDcbbtLAS. */
	$"1800 1801 0100 0000 0000 0000 0F00 0000"            /* ................ */
	$"0C00 0000 00FF FFFF FF74 4C41 5300 0000"            /* .....ˇˇˇˇtLAS... */
	$"0000 0001 0100 0023 2800 2100 0000 0000"            /* .......#(.!..... */
	$"0000 0000 0000 0000 0000 0000 0044 436C"            /* .............DCl */
	$"6B6F 626A 6400 0000 4A44 6362 6274 5345"            /* kobjd...JDcbbtSE */
	$"4C00 1800 1801 0100 0000 0000 0000 2900"            /* L.............). */
	$"0000 0C00 0000 00FF FFFF FF74 5345 4C00"            /* .......ˇˇˇˇtSEL. */
	$"0000 0000 0001 0100 0023 2900 2100 0000"            /* .........#).!... */
	$"0000 0000 0000 0000 0000 0000 0000 0044"            /* ...............D */
	$"436C 6B6F 626A 6400 0000 4662 6275 7474"            /* Clkobjd...Fbbutt */
	$"5458 5400 1800 1801 0100 0000 0000 0000"            /* TXT............. */
	$"0F00 0000 2600 0000 00FF FFFF FF74 5458"            /* ....&....ˇˇˇˇtTX */
	$"5400 0000 0000 0001 0100 0023 2A00 2100"            /* T..........#*.!. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"006F 626A 6400 0000 4662 6275 7474 5045"            /* .objd...FbbuttPE */
	$"4E00 1800 1801 0100 0000 0000 0000 2900"            /* N.............). */
	$"0000 2600 0000 00FF FFFF FF74 5045 4E00"            /* ..&....ˇˇˇˇtPEN. */
	$"0000 0000 0001 0100 0023 2B00 2100 0000"            /* .........#+.!... */
	$"0000 0000 0000 0000 0000 0000 0000 006F"            /* ...............o */
	$"626A 6400 0000 4A44 6362 6274 4552 4100"            /* bjd...JDcbbtERA. */
	$"1800 1801 0100 0000 0000 0000 0F00 0000"            /* ................ */
	$"4000 0000 00FF FFFF FF74 4552 4100 0000"            /* @....ˇˇˇˇtERA... */
	$"0000 0001 0100 0023 2C00 2100 0000 0000"            /* .......#,.!..... */
	$"0000 0000 0000 0000 0000 0000 0044 436C"            /* .............DCl */
	$"6B6F 626A 6400 0000 4662 6275 7474 4255"            /* kobjd...FbbuttBU */
	$"4300 1800 1801 0100 0000 0000 0000 2900"            /* C.............). */
	$"0000 4000 0000 00FF FFFF FF74 4255 4300"            /* ..@....ˇˇˇˇtBUC. */
	$"0000 0000 0001 0100 0023 2D00 2100 0000"            /* .........#-.!... */
	$"0000 0000 0000 0000 0000 0000 0000 006F"            /* ...............o */
	$"626A 6400 0000 4662 6275 7474 4452 4F00"            /* bjd...FbbuttDRO. */
	$"1800 1801 0100 0000 0000 0000 0F00 0000"            /* ................ */
	$"5A00 0000 00FF FFFF FF74 4452 4F00 0000"            /* Z....ˇˇˇˇtDRO... */
	$"0000 0001 0100 0023 2E00 2100 0000 0000"            /* .......#..!..... */
	$"0000 0000 0000 0000 0000 0000 006F 626A"            /* .............obj */
	$"6400 0000 4662 6275 7474 4C49 4E00 1800"            /* d...FbbuttLIN... */
	$"1801 0100 0000 0000 0000 2900 0000 5A00"            /* ..........)...Z. */
	$"0000 00FF FFFF FF74 4C49 4E00 0000 0000"            /* ...ˇˇˇˇtLIN..... */
	$"0001 0100 0023 2F00 2100 0000 0000 0000"            /* .....#/.!....... */
	$"0000 0000 0000 0000 0000 006F 626A 6400"            /* ...........objd. */
	$"0000 4662 6275 7474 5245 4300 1800 1801"            /* ..FbbuttREC..... */
	$"0100 0000 0000 0000 0F00 0000 7400 0000"            /* ............t... */
	$"00FF FFFF FF74 5245 4300 0000 0000 0001"            /* .ˇˇˇˇtREC....... */
	$"0100 0023 3100 2100 0000 0000 0000 0000"            /* ...#1.!......... */
	$"0000 0000 0000 0000 006F 626A 6400 0000"            /* .........objd... */
	$"4662 6275 7474 4652 4300 1800 1801 0100"            /* FbbuttFRC....... */
	$"0000 0000 0000 2900 0000 7400 0000 00FF"            /* ......)...t....ˇ */
	$"FFFF FF74 4652 4300 0000 0000 0001 0100"            /* ˇˇˇtFRC......... */
	$"0023 3000 2100 0000 0000 0000 0000 0000"            /* .#0.!........... */
	$"0000 0000 0000 006F 626A 6400 0000 4662"            /* .......objd...Fb */
	$"6275 7474 5252 4300 1800 1801 0100 0000"            /* buttRRC......... */
	$"0000 0000 0F00 0000 8E00 0000 00FF FFFF"            /* ........é....ˇˇˇ */
	$"FF74 5252 4300 0000 0000 0001 0100 0023"            /* ˇtRRC..........# */
	$"3300 2100 0000 0000 0000 0000 0000 0000"            /* 3.!............. */
	$"0000 0000 006F 626A 6400 0000 4662 6275"            /* .....objd...Fbbu */
	$"7474 4652 5200 1800 1801 0100 0000 0000"            /* ttFRR........... */
	$"0000 2900 0000 8E00 0000 00FF FFFF FF74"            /* ..)...é....ˇˇˇˇt */
	$"4652 5200 0000 0000 0001 0100 0023 3200"            /* FRR..........#2. */
	$"2100 0000 0000 0000 0000 0000 0000 0000"            /* !............... */
	$"0000 006F 626A 6400 0000 4662 6275 7474"            /* ...objd...Fbbutt */
	$"4F56 4C00 1800 1801 0100 0000 0000 0000"            /* OVL............. */
	$"0F00 0000 A800 0000 00FF FFFF FF74 4F56"            /* ....®....ˇˇˇˇtOV */
	$"4C00 0000 0000 0001 0100 0023 3500 2100"            /* L..........#5.!. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"006F 626A 6400 0000 4662 6275 7474 464F"            /* .objd...FbbuttFO */
	$"5600 1800 1801 0100 0000 0000 0000 2900"            /* V.............). */
	$"0000 A800 0000 00FF FFFF FF74 464F 5600"            /* ..®....ˇˇˇˇtFOV. */
	$"0000 0000 0001 0100 0023 3400 2100 0000"            /* .........#4.!... */
	$"0000 0000 0000 0000 0000 0000 0000 0064"            /* ...............d */
	$"6F70 6C50 6174 506F 626A 6400 0000 4662"            /* oplPatPobjd...Fb */
	$"6275 7474 5041 5400 3200 1201 0100 0000"            /* buttPAT.2....... */
	$"0000 0000 0F00 0000 C800 0003 E8FF FFFF"            /* ........»...Ëˇˇˇ */
	$"FF74 5041 5400 0000 0000 0000 0000 0000"            /* ˇtPAT........... */
	$"0000 2100 0000 0000 0000 0000 0000 0000"            /* ..!............. */
	$"0000 0000 006F 626A 6400 0000 4E43 6F6C"            /* .....objd...NCol */
	$"5074 4243 4C00 2800 1001 0101 0100 0000"            /* PtBCL.(......... */
	$"0000 1B00 0000 EE00 FFFF FFFF FFFF FF74"            /* ......Ó.ˇˇˇˇˇˇˇt */
	$"4243 4C00 0000 0000 0000 0000 0000 0000"            /* BCL............. */
	$"2100 0000 0000 0000 0000 0000 0000 0000"            /* !............... */
	$"0000 0000 0000 0000 0001 006F 626A 6400"            /* ...........objd. */
	$"0000 4E43 6F6C 5074 4643 4C00 2800 1001"            /* ..NColPtFCL.(... */
	$"0101 0100 0000 0000 0F00 0000 E200 0000"            /* ............‚... */
	$"00FF FFFF FF74 4643 4C00 0000 0000 0000"            /* .ˇˇˇˇtFCL....... */
	$"0000 0000 0000 2100 0000 0000 0000 0000"            /* ......!......... */
	$"0000 0000 0000 0000 00FF FFFF FFFF FF00"            /* .........ˇˇˇˇˇˇ. */
	$"006F 626A 6400 0000 5174 6762 7845 4E43"            /* .objd...QtgbxENC */
	$"4C00 7900 7901 0101 0100 0000 0000 5000"            /* L.y.y.........P. */
	$"0000 0A00 0000 00FF FFFF FF00 0000 0000"            /* ..¬....ˇˇˇˇ..... */
	$"0000 0000 0000 0000 0000 0000 0000 0100"            /* ................ */
	$"0000 0100 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 A000 0000 6265 6773 646F"            /* ......†...begsdo */
	$"706C 4943 4E56 6F62 6A64 0000 003C 7669"            /* plICNVobjd...<vi */
	$"6577 436E 7473 0071 0071 0101 0101 0101"            /* ewCnts.q.q...... */
	$"0000 0004 0000 0004 0000 0000 FFFF FFFF"            /* ............ˇˇˇˇ */
	$"0000 0000 0000 0004 0000 0000 0000 0000"            /* ................ */
	$"0000 0014 0000 0014 0001 656E 6473 6F62"            /* ..........endsob */
	$"6A64 0000 003C 7669 6577 5341 4D50 003C"            /* jd...<viewSAMP.< */
	$"0048 0101 0000 0000 0000 00D3 0000 0024"            /* .H.........”...$ */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0000 0001 0000 0001"            /* ................ */
	$"0000 6265 6773 646F 706C 5054 5677 6F62"            /* ..begsdoplPTVwob */
	$"6A64 0000 003C 7669 6577 4257 5054 002C"            /* jd...<viewBWPT., */
	$"0038 0101 0000 0000 0000 0008 0000 0008"            /* .8.............. */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0000 0001 0000 0001"            /* ................ */
	$"0000 656E 6473 6F62 6A64 0000 0037 7374"            /* ..endsobjd...7st */
	$"7874 434F 4F52 003C 0010 0101 0000 0000"            /* xtCOOR.<........ */
	$"0000 000A 0000 0107 0000 0000 FFFF FFFF"            /* ...¬........ˇˇˇˇ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0120 0000 0064 6F70 6C53 7553 6C6F 626A"            /* . ...doplSuSlobj */
	$"6400 0000 3673 6C69 6453 4C49 4400 7900"            /* d...6slidSLID.y. */
	$"1401 0101 0001 0000 0000 5000 0000 8C00"            /* ..........P...å. */
	$"0000 00FF FFFF FF53 4C49 4400 0000 0000"            /* ...ˇˇˇˇSLID..... */
	$"0000 0000 0000 0000 3100 046F 626A 6400"            /* ........1..objd. */
	$"0000 3773 7478 7443 4F55 4E00 3D00 1001"            /* ..7stxtCOUN.=... */
	$"0101 0000 0000 0000 CB00 0000 8E00 0000"            /* ........À...é... */
	$"00FF FFFF FF00 0000 0000 0000 0000 0000"            /* .ˇˇˇˇ........... */
	$"0000 0000 0001 2000 8200 6F62 6A64 0000"            /* ...... .Ç.objd.. */
	$"0039 7075 7368 4D69 6E73 001E 0010 0101"            /* .9pushMins...... */
	$"0101 0000 0000 0064 0000 00AA 0000 0000"            /* .......d...™.... */
	$"FFFF FFFF 4D69 6E73 0000 0000 0000 0000"            /* ˇˇˇˇMins........ */
	$"0000 0000 0170 0000 012D 006F 626A 6400"            /* .....p...-.objd. */
	$"0000 3970 7573 6850 6C75 7300 1E00 1001"            /* ..9pushPlus..... */
	$"0100 0001 0100 0000 9700 0000 AA00 0000"            /* ........ó...™... */
	$"00FF FFFF FF50 6C75 7300 0000 0000 0000"            /* .ˇˇˇˇPlus....... */
	$"0000 0000 0001 7000 0001 2B00 656E 6473"            /* ......p...+.ends */
	$"6F62 6A64 0000 0051 706C 6364 464F 4F54"            /* objd...QplcdFOOT */
	$"0119 0028 0101 0100 0101 0000 0000 0000"            /* ...(............ */
	$"0118 0000 0000 FFFF FFFF 0000 0000 0000"            /* ......ˇˇˇˇ...... */
	$"0000 0000 0000 0000 0000 0000 0001 0000"            /* ................ */
	$"0001 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 00E0 0000 0062 6567 736F 626A"            /* .....‡...begsobj */
	$"6400 0000 3C70 7573 6856 6C69 6400 4100"            /* d...<pushVlid.A. */
	$"1401 0100 0001 0100 0000 CC00 0000 0900"            /* ..........Ã...∆. */
	$"0000 00FF FFFF FF00 0003 8400 0000 0000"            /* ...ˇˇˇˇ...Ñ..... */
	$"0000 0000 0000 0001 7000 0004 5361 7665"            /* ........p...Save */
	$"016F 626A 6400 0000 3E70 7573 6843 6E63"            /* .objd...>pushCnc */
	$"6C00 4100 1401 0100 0001 0100 0000 7F00"            /* l.A............. */
	$"0000 0900 0000 00FF FFFF FF00 0003 8500"            /* ..∆....ˇˇˇˇ...Ö. */
	$"0000 0000 0000 0000 0000 0001 7000 0006"            /* ............p... */
	$"4361 6E63 656C 006F 626A 6400 0000 3E70"            /* Cancel.objd...>p */
	$"7573 6852 7672 7400 4100 1401 0101 0000"            /* ushRvrt.A....... */
	$"0100 0000 1B00 0000 0900 0000 00FF FFFF"            /* ........∆....ˇˇˇ */
	$"FF00 0000 0700 0000 0000 0000 0000 0000"            /* ˇ............... */
	$"0001 7000 0006 5265 7665 7274 006F 626A"            /* ..p...Revert.obj */
	$"6400 0000 2469 636E 704C 6F63 6B00 1000"            /* d...$icnpLock... */
	$"1001 0101 0000 0100 0000 0600 0000 0B00"            /* ................ */
	$"0000 00FF FFFF FF00 0065 6E64 7365 6E64"            /* ...ˇˇˇˇ..endsend */
	$"7365 6E64 2E"                                       /* send. */
};

data 'PPob' (10609, "Icon Suite Editor Window") {
	$"0002 646F 706C 4963 5356 6F62 6A64 0000"            /* ..doplIcSVobjd.. */
	$"001C 7769 6E64 2971 0002 1862 0000 0190"            /* ..wind)q...b...ê */
	$"0190 FFFF FFFF 0208 0190 0000 0000 6265"            /* .êˇˇˇˇ...ê....be */
	$"6773 6F62 6A64 0000 0051 706C 6364 0000"            /* gsobjd...Qplcd.. */
	$"0000 016D 012C 0101 0101 0101 0000 0000"            /* ...m.,.......... */
	$"0000 0000 0000 0000 FFFF FFFF 0000 0000"            /* ........ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"0000 0001 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0150 0000 0062 6567 736F"            /* .......P...begso */
	$"626A 6400 0000 4A44 6362 6274 4C41 5300"            /* bjd...JDcbbtLAS. */
	$"1800 1801 0100 0000 0000 0000 0F00 0000"            /* ................ */
	$"0C00 0000 00FF FFFF FF74 4C41 5300 0000"            /* .....ˇˇˇˇtLAS... */
	$"0000 0001 0100 0023 2800 2100 0000 0000"            /* .......#(.!..... */
	$"0000 0000 0000 0000 0000 0000 0044 436C"            /* .............DCl */
	$"6B6F 626A 6400 0000 4A44 6362 6274 5345"            /* kobjd...JDcbbtSE */
	$"4C00 1800 1801 0100 0000 0000 0000 2900"            /* L.............). */
	$"0000 0C00 0000 00FF FFFF FF74 5345 4C00"            /* .......ˇˇˇˇtSEL. */
	$"0000 0000 0001 0100 0023 2900 2100 0000"            /* .........#).!... */
	$"0000 0000 0000 0000 0000 0000 0000 0044"            /* ...............D */
	$"436C 6B6F 626A 6400 0000 4662 6275 7474"            /* Clkobjd...Fbbutt */
	$"5458 5400 1800 1801 0100 0000 0000 0000"            /* TXT............. */
	$"0F00 0000 2600 0000 00FF FFFF FF74 5458"            /* ....&....ˇˇˇˇtTX */
	$"5400 0000 0000 0001 0100 0023 2A00 2100"            /* T..........#*.!. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"006F 626A 6400 0000 4662 6275 7474 5045"            /* .objd...FbbuttPE */
	$"4E00 1800 1801 0100 0000 0000 0000 2900"            /* N.............). */
	$"0000 2600 0000 00FF FFFF FF74 5045 4E00"            /* ..&....ˇˇˇˇtPEN. */
	$"0000 0000 0001 0100 0023 2B00 2100 0000"            /* .........#+.!... */
	$"0000 0000 0000 0000 0000 0000 0000 006F"            /* ...............o */
	$"626A 6400 0000 4A44 6362 6274 4552 4100"            /* bjd...JDcbbtERA. */
	$"1800 1801 0100 0000 0000 0000 0F00 0000"            /* ................ */
	$"4000 0000 00FF FFFF FF74 4552 4100 0000"            /* @....ˇˇˇˇtERA... */
	$"0000 0001 0100 0023 2C00 2100 0000 0000"            /* .......#,.!..... */
	$"0000 0000 0000 0000 0000 0000 0044 436C"            /* .............DCl */
	$"6B6F 626A 6400 0000 4662 6275 7474 4255"            /* kobjd...FbbuttBU */
	$"4300 1800 1801 0100 0000 0000 0000 2900"            /* C.............). */
	$"0000 4000 0000 00FF FFFF FF74 4255 4300"            /* ..@....ˇˇˇˇtBUC. */
	$"0000 0000 0001 0100 0023 2D00 2100 0000"            /* .........#-.!... */
	$"0000 0000 0000 0000 0000 0000 0000 006F"            /* ...............o */
	$"626A 6400 0000 4662 6275 7474 4452 4F00"            /* bjd...FbbuttDRO. */
	$"1800 1801 0100 0000 0000 0000 0F00 0000"            /* ................ */
	$"5A00 0000 00FF FFFF FF74 4452 4F00 0000"            /* Z....ˇˇˇˇtDRO... */
	$"0000 0001 0100 0023 2E00 2100 0000 0000"            /* .......#..!..... */
	$"0000 0000 0000 0000 0000 0000 006F 626A"            /* .............obj */
	$"6400 0000 4662 6275 7474 4C49 4E00 1800"            /* d...FbbuttLIN... */
	$"1801 0100 0000 0000 0000 2900 0000 5A00"            /* ..........)...Z. */
	$"0000 00FF FFFF FF74 4C49 4E00 0000 0000"            /* ...ˇˇˇˇtLIN..... */
	$"0001 0100 0023 2F00 2100 0000 0000 0000"            /* .....#/.!....... */
	$"0000 0000 0000 0000 0000 006F 626A 6400"            /* ...........objd. */
	$"0000 4662 6275 7474 5245 4300 1800 1801"            /* ..FbbuttREC..... */
	$"0100 0000 0000 0000 0F00 0000 7400 0000"            /* ............t... */
	$"00FF FFFF FF74 5245 4300 0000 0000 0001"            /* .ˇˇˇˇtREC....... */
	$"0100 0023 3100 2100 0000 0000 0000 0000"            /* ...#1.!......... */
	$"0000 0000 0000 0000 006F 626A 6400 0000"            /* .........objd... */
	$"4662 6275 7474 4652 4300 1800 1801 0100"            /* FbbuttFRC....... */
	$"0000 0000 0000 2900 0000 7400 0000 00FF"            /* ......)...t....ˇ */
	$"FFFF FF74 4652 4300 0000 0000 0001 0100"            /* ˇˇˇtFRC......... */
	$"0023 3000 2100 0000 0000 0000 0000 0000"            /* .#0.!........... */
	$"0000 0000 0000 006F 626A 6400 0000 4662"            /* .......objd...Fb */
	$"6275 7474 5252 4300 1800 1801 0100 0000"            /* buttRRC......... */
	$"0000 0000 0F00 0000 8E00 0000 00FF FFFF"            /* ........é....ˇˇˇ */
	$"FF74 5252 4300 0000 0000 0001 0100 0023"            /* ˇtRRC..........# */
	$"3300 2100 0000 0000 0000 0000 0000 0000"            /* 3.!............. */
	$"0000 0000 006F 626A 6400 0000 4662 6275"            /* .....objd...Fbbu */
	$"7474 4652 5200 1800 1801 0100 0000 0000"            /* ttFRR........... */
	$"0000 2900 0000 8E00 0000 00FF FFFF FF74"            /* ..)...é....ˇˇˇˇt */
	$"4652 5200 0000 0000 0001 0100 0023 3200"            /* FRR..........#2. */
	$"2100 0000 0000 0000 0000 0000 0000 0000"            /* !............... */
	$"0000 006F 626A 6400 0000 4662 6275 7474"            /* ...objd...Fbbutt */
	$"4F56 4C00 1800 1801 0100 0000 0000 0000"            /* OVL............. */
	$"0F00 0000 A800 0000 00FF FFFF FF74 4F56"            /* ....®....ˇˇˇˇtOV */
	$"4C00 0000 0000 0001 0100 0023 3500 2100"            /* L..........#5.!. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"006F 626A 6400 0000 4662 6275 7474 464F"            /* .objd...FbbuttFO */
	$"5600 1800 1801 0100 0000 0000 0000 2900"            /* V.............). */
	$"0000 A800 0000 00FF FFFF FF74 464F 5600"            /* ..®....ˇˇˇˇtFOV. */
	$"0000 0000 0001 0100 0023 3400 2100 0000"            /* .........#4.!... */
	$"0000 0000 0000 0000 0000 0000 0000 0064"            /* ...............d */
	$"6F70 6C50 6174 506F 626A 6400 0000 4662"            /* oplPatPobjd...Fb */
	$"6275 7474 5041 5400 3200 1201 0100 0000"            /* buttPAT.2....... */
	$"0000 0000 0F00 0000 CE00 0003 E8FF FFFF"            /* ........Œ...Ëˇˇˇ */
	$"FF74 5041 5400 0000 0000 0000 0000 0000"            /* ˇtPAT........... */
	$"0000 2100 0000 0000 0000 0000 0000 0000"            /* ..!............. */
	$"0000 0000 006F 626A 6400 0000 4E43 6F6C"            /* .....objd...NCol */
	$"5074 4243 4C00 2800 1001 0101 0100 0000"            /* PtBCL.(......... */
	$"0000 1B00 0000 FA00 FFFF FFFF FFFF FF74"            /* ......˙.ˇˇˇˇˇˇˇt */
	$"4243 4C00 0000 0000 0000 0000 0000 0000"            /* BCL............. */
	$"2100 0000 0000 0000 0000 0000 0000 0000"            /* !............... */
	$"0000 0000 0000 0000 0001 006F 626A 6400"            /* ...........objd. */
	$"0000 4E43 6F6C 5074 4643 4C00 2800 1001"            /* ..NColPtFCL.(... */
	$"0101 0100 0000 0000 0F00 0000 EE00 0000"            /* ............Ó... */
	$"00FF FFFF FF74 4643 4C00 0000 0000 0000"            /* .ˇˇˇˇtFCL....... */
	$"0000 0000 0000 2100 0000 0000 0000 0000"            /* ......!......... */
	$"0000 0000 0000 0000 00FF FFFF FFFF FF00"            /* .........ˇˇˇˇˇˇ. */
	$"006F 626A 6400 0000 5174 6762 7845 4E43"            /* .objd...QtgbxENC */
	$"4C00 E100 E101 0101 0100 0000 0000 5000"            /* L.·.·.........P. */
	$"0000 0A00 0000 00FF FFFF FF00 0000 0000"            /* ..¬....ˇˇˇˇ..... */
	$"0000 0000 0000 0000 0000 0000 0000 0100"            /* ................ */
	$"0000 0100 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 A000 0000 6265 6773 646F"            /* ......†...begsdo */
	$"706C 4943 4E56 6F62 6A64 0000 003C 7669"            /* plICNVobjd...<vi */
	$"6577 436E 7473 00D9 00D9 0101 0101 0101"            /* ewCnts.Ÿ.Ÿ...... */
	$"0000 0004 0000 0004 0000 0000 FFFF FFFF"            /* ............ˇˇˇˇ */
	$"0000 0000 0000 0004 0000 0000 0000 0000"            /* ................ */
	$"0000 0014 0000 0014 0001 656E 6473 6F62"            /* ..........endsob */
	$"6A64 0000 003C 7669 6577 5341 4D50 0028"            /* jd...<viewSAMP.( */
	$"0032 0101 0000 0000 0000 013B 0000 0024"            /* .2.........;...$ */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0000 0001 0000 0001"            /* ................ */
	$"0000 6265 6773 646F 706C 4454 5677 6F62"            /* ..begsdoplDTVwob */
	$"6A64 0000 003C 7669 6577 5349 434E 001C"            /* jd...<viewSICN.. */
	$"0028 0101 0000 0000 0000 0006 0000 0005"            /* .(.............. */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0000 0001 0000 0001"            /* ................ */
	$"0000 656E 6473 6F62 6A64 0000 0037 7374"            /* ..endsobjd...7st */
	$"7874 434F 4F52 003C 0010 0101 0000 0000"            /* xtCOOR.<........ */
	$"0000 000A 0000 011B 0000 0000 FFFF FFFF"            /* ...¬........ˇˇˇˇ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0120 0000 0064 6F70 6C53 7553 6C6F 626A"            /* . ...doplSuSlobj */
	$"6400 0000 3673 6C69 6453 4C49 4400 E100"            /* d...6slidSLID.·. */
	$"1401 0101 0001 0000 0000 5000 0000 F500"            /* ..........P...ı. */
	$"0000 00FF FFFF FF53 4C49 4400 0000 0000"            /* ...ˇˇˇˇSLID..... */
	$"0000 0000 0000 0000 3100 046F 626A 6400"            /* ........1..objd. */
	$"0000 3773 7478 7443 4F55 4E00 3700 1001"            /* ..7stxtCOUN.7... */
	$"0101 0000 0000 0001 3300 0000 F700 0000"            /* ........3...˜... */
	$"00FF FFFF FF00 0000 0000 0000 0000 0000"            /* .ˇˇˇˇ........... */
	$"0000 0000 0001 2000 8200 6F62 6A64 0000"            /* ...... .Ç.objd.. */
	$"0039 7075 7368 4D69 6E73 001E 0010 0101"            /* .9pushMins...... */
	$"0101 0001 0000 0091 0000 0110 0000 0000"            /* .......ë........ */
	$"FFFF FFFF 4D69 6E73 0000 0000 0000 0000"            /* ˇˇˇˇMins........ */
	$"0000 0000 0170 0000 012D 006F 626A 6400"            /* .....p...-.objd. */
	$"0000 3970 7573 6850 6C75 7300 1E00 1001"            /* ..9pushPlus..... */
	$"0100 0101 0100 0000 D200 0001 1000 0000"            /* ........“....... */
	$"00FF FFFF FF50 6C75 7300 0000 0000 0000"            /* .ˇˇˇˇPlus....... */
	$"0000 0000 0001 7000 0001 2B00 656E 6473"            /* ......p...+.ends */
	$"6F62 6A64 0000 0051 706C 6364 464F 4F54"            /* objd...QplcdFOOT */
	$"016D 0028 0101 0100 0101 0000 0000 0000"            /* .m.(............ */
	$"012C 0000 0000 FFFF FFFF 0000 0000 0000"            /* .,....ˇˇˇˇ...... */
	$"0000 0000 0000 0000 0000 0000 0001 0000"            /* ................ */
	$"0001 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 00E0 0000 0062 6567 736F 626A"            /* .....‡...begsobj */
	$"6400 0000 3C70 7573 6856 6C69 6400 4100"            /* d...<pushVlid.A. */
	$"1401 0100 0001 0100 0001 2000 0000 0900"            /* .......... ...∆. */
	$"0000 00FF FFFF FF00 0003 8400 0000 0000"            /* ...ˇˇˇˇ...Ñ..... */
	$"0000 0000 0000 0001 7000 0004 5361 7665"            /* ........p...Save */
	$"016F 626A 6400 0000 3E70 7573 6843 6E63"            /* .objd...>pushCnc */
	$"6C00 4100 1401 0100 0001 0100 0000 D300"            /* l.A...........”. */
	$"0000 0900 0000 00FF FFFF FF00 0003 8500"            /* ..∆....ˇˇˇˇ...Ö. */
	$"0000 0000 0000 0000 0000 0001 7000 0006"            /* ............p... */
	$"4361 6E63 656C 006F 626A 6400 0000 3E70"            /* Cancel.objd...>p */
	$"7573 6852 7672 7400 4100 1401 0101 0000"            /* ushRvrt.A....... */
	$"0100 0000 1B00 0000 0900 0000 00FF FFFF"            /* ........∆....ˇˇˇ */
	$"FF00 0000 0700 0000 0000 0000 0000 0000"            /* ˇ............... */
	$"0001 7000 0006 5265 7665 7274 006F 626A"            /* ..p...Revert.obj */
	$"6400 0000 2469 636E 704C 6F63 6B00 1000"            /* d...$icnpLock... */
	$"1001 0101 0000 0100 0000 0600 0000 0B00"            /* ................ */
	$"0000 00FF FFFF FF00 0065 6E64 7365 6E64"            /* ...ˇˇˇˇ..endsend */
	$"7365 6E64 2E"                                       /* send. */
};

data 'PPob' (3000, "Hex Editing Window") {
	$"0002 646F 706C 4865 7857 6F62 6A64 0000"            /* ..doplHexWobjd.. */
	$"001C 7769 6E64 0BB8 0002 1F62 0000 015E"            /* ..wind.∏...b...^ */
	$"0000 FFFF FFFF FFFF FFFF 0000 0000 6265"            /* ..ˇˇˇˇˇˇˇˇ....be */
	$"6773 646F 706C 4475 5677 6F62 6A64 0000"            /* gsdoplDuVwobjd.. */
	$"0051 7467 6278 0000 000A 020E 016B 0101"            /* .Qtgbx...¬...k.. */
	$"0101 0101 0000 0004 0000 001C 0000 0000"            /* ................ */
	$"FFFF FFFF 0000 0000 0000 0000 0000 0000"            /* ˇˇˇˇ............ */
	$"0000 0000 0000 0001 0000 0001 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 00A4"            /* ...............§ */
	$"0000 0062 6567 7364 6F70 6C53 7362 726F"            /* ...begsdoplSsbro */
	$"626A 6400 0000 3773 6261 7200 0000 0100"            /* bjd...7sbar..... */
	$"1001 6A01 0100 0101 0100 0001 FC00 0000"            /* ..j.........¸... */
	$"0000 0000 00FF FFFF FF48 5363 7200 0000"            /* .....ˇˇˇˇHScr... */
	$"0000 0000 0000 0000 0001 8200 0000 646F"            /* ..........Ç...do */
	$"706C 4844 5356 6F62 6A64 0000 0051 5765"            /* plHDSVobjd...QWe */
	$"5677 0000 0002 0120 0160 0101 0001 0001"            /* Vw..... .`...... */
	$"0000 0006 0000 0005 0000 0000 FFFF FFFF"            /* ............ˇˇˇˇ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0001 0000 0001 0000 0001 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0001 0100 8B00 0064"            /* ............ã..d */
	$"6F70 6C54 4453 566F 626A 6400 0000 5157"            /* oplTDSVobjd...QW */
	$"6556 7700 0000 0300 C001 6001 0100 0100"            /* eVw.....¿.`..... */
	$"0100 0001 3800 0000 0500 0000 00FF FFFF"            /* ....8........ˇˇˇ */
	$"FF00 0000 0000 0000 0000 0000 0000 0000"            /* ˇ............... */
	$"0000 0000 0100 0000 0100 0000 0100 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0101 008B 0000"            /* .............ã.. */
	$"656E 6473 6F62 6A64 0000 0051 7769 6E68"            /* endsobjd...Qwinh */
	$"0000 0000 0219 001C 0101 0101 0100 FFFF"            /* ..............ˇˇ */
	$"FFFE 0000 0000 0000 0000 FFFF FFFF 0000"            /* ˇ˛........ˇˇˇˇ.. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0001 0000 0001 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0150 0000 0062 6567"            /* .........P...beg */
	$"736F 626A 6400 0000 3773 7478 744E 616D"            /* sobjd...7stxtNam */
	$"6501 E000 1001 0101 0000 0100 0000 2E00"            /* e.‡............. */
	$"0000 0700 0000 00FF FFFF FF00 0000 0000"            /* .......ˇˇˇˇ..... */
	$"0000 0000 0000 0000 0000 0001 2000 8200"            /* ............ .Ç. */
	$"6F62 6A64 0000 003C 7374 7874 0000 0000"            /* objd...<stxt.... */
	$"0022 000E 0101 0100 0001 0000 000C 0000"            /* .".............. */
	$"0007 0000 0000 FFFF FFFF 0000 0000 0000"            /* ......ˇˇˇˇ...... */
	$"0000 0000 0000 0000 0000 0120 008B 054E"            /* ........... .ã.N */
	$"616D 653A 656E 6473 6F62 6A64 0000 0051"            /* ame:endsobjd...Q */
	$"7769 6E68 0000 0000 0217 001B 0101 0100"            /* winh............ */
	$"0101 0000 0000 0000 0188 0000 0000 FFFF"            /* .........à....ˇˇ */
	$"FFFF 0000 0000 0000 0000 0000 0000 0000"            /* ˇˇ.............. */
	$"0000 0000 0001 0000 0001 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0150 0000"            /* .............P.. */
	$"0062 6567 736F 626A 6400 0000 2469 636E"            /* .begsobjd...$icn */
	$"704C 6F63 6B00 1000 1001 0101 0000 0100"            /* pLock........... */
	$"0000 0500 0000 0300 0000 00FF FFFF FF00"            /* ...........ˇˇˇˇ. */
	$"006F 626A 6400 0000 3C73 7478 7400 0000"            /* .objd...<stxt... */
	$"0000 2200 0E01 0101 0000 0100 0000 1B00"            /* .."............. */
	$"0000 0600 0000 00FF FFFF FF00 0000 0000"            /* .......ˇˇˇˇ..... */
	$"0000 0000 0000 0000 0000 0001 2000 8B05"            /* ............ .ã. */
	$"4C69 6E65 3A64 6F70 6C52 6574 786F 626A"            /* Line:doplRetxobj */
	$"6400 0000 3B65 7478 7400 0000 0400 5A00"            /* d...;etxt.....Z. */
	$"1401 0101 0000 0100 0000 3E00 0000 0200"            /* ..........>..... */
	$"0000 00FF FFFF FF00 000B BC00 0000 0000"            /* ...ˇˇˇˇ...º..... */
	$"0000 0000 0000 0001 1000 8B00 00FF 2001"            /* ..........ã..ˇ . */
	$"6F62 6A64 0000 003E 7374 7874 0000 0000"            /* objd...>stxt.... */
	$"0030 000E 0101 0100 0001 0000 00A1 0000"            /* .0...........°.. */
	$"0006 0000 0000 FFFF FFFF 0000 0000 0000"            /* ......ˇˇˇˇ...... */
	$"0000 0000 0000 0000 0000 0120 008B 074F"            /* ........... .ã.O */
	$"6666 7365 743A 646F 706C 5265 7478 6F62"            /* ffset:doplRetxob */
	$"6A64 0000 003B 6574 7874 0000 0005 0064"            /* jd...;etxt.....d */
	$"0014 0101 0100 0001 0000 00D1 0000 0002"            /* ...........—.... */
	$"0000 0000 FFFF FFFF 0000 0BBD 0000 0000"            /* ....ˇˇˇˇ...Ω.... */
	$"0000 0000 0000 0000 0110 008B 0000 FF20"            /* ...........ã..ˇ  */
	$"0165 6E64 7365 6E64 7365 6E64 2E"                   /* .endsendsend. */
};

data 'PPob' (7700, "Misc Prefs Pane") {
	$"0002 6F62 6A64 0000 003C 7669 6577 0000"            /* ..objd...<view.. */
	$"0001 0186 00D2 0001 0000 0000 0000 0000"            /* ...Ü.“.......... */
	$"0000 0000 0000 0000 FFFF FFFF 0000 0000"            /* ........ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0000 0010"            /* ................ */
	$"0000 0010 0000 6265 6773 6F62 6A64 0000"            /* ......begsobjd.. */
	$"0055 7467 6278 0000 0000 016C 00B4 0101"            /* .Utgbx.....l.¥.. */
	$"0000 0000 0000 000D 0000 000E 0000 0000"            /* ................ */
	$"FFFF FFFF 0000 0000 0000 0000 0000 0000"            /* ˇˇˇˇ............ */
	$"0000 0000 0000 0001 0000 0001 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 00A0"            /* ...............† */
	$"0085 044D 6973 6362 6567 736F 626A 6400"            /* .Ö.Miscbegsobjd. */
	$"0000 7263 6267 6200 0000 0200 E100 6401"            /* ..rcbgb.....·.d. */
	$"0100 0000 0000 0000 4600 0000 1800 0000"            /* ........F....... */
	$"00FF FFFF FF00 0000 0000 0000 0000 0000"            /* .ˇˇˇˇ........... */
	$"0000 0000 0000 0000 0100 0000 0100 0000"            /* ................ */
	$"001E 1600 0000 0000 0000 0000 0000 0200"            /* ................ */
	$"A500 8B21 5365 7420 7479 7065 2061 6E64"            /* •.ã!Set type and */
	$"2063 7265 6174 6F72 2077 6865 6E20 636C"            /*  creator when cl */
	$"6F73 696E 6762 6567 736F 626A 6400 0000"            /* osingbegsobjd... */
	$"3B73 7478 7400 0000 0000 3200 1001 0101"            /* ;stxt.....2..... */
	$"0100 0000 0000 3400 0000 1A00 0000 00FF"            /* ......4........ˇ */
	$"FFFF FF00 0000 0000 0000 0000 0000 0000"            /* ˇˇˇ............. */
	$"0000 0001 2000 8504 5479 7065 6F62 6A64"            /* .... .Ö.Typeobjd */
	$"0000 003F 6574 7874 0000 0003 0037 0015"            /* ...?etxt.....7.. */
	$"0101 0101 0000 0000 006D 0000 0016 0000"            /* .........m...... */
	$"0000 FFFF FFFF 0000 1E17 0000 0000 0000"            /* ..ˇˇˇˇ.......... */
	$"0000 0000 0000 0110 008C 0472 7372 6300"            /* .........å.rsrc. */
	$"0420 036F 626A 6400 0000 3E73 7478 7400"            /* . .objd...>stxt. */
	$"0000 0000 3200 1001 0101 0100 0000 0000"            /* ....2........... */
	$"3400 0000 3200 0000 00FF FFFF FF00 0000"            /* 4...2....ˇˇˇˇ... */
	$"0000 0000 0000 0000 0000 0000 0001 2000"            /* .............. . */
	$"8507 4372 6561 746F 726F 626A 6400 0000"            /* Ö.Creatorobjd... */
	$"3F65 7478 7400 0000 0400 3700 1501 0101"            /* ?etxt.....7..... */
	$"0100 0000 0000 6C00 0000 2E00 0000 00FF"            /* ......l........ˇ */
	$"FFFF FF00 001E 1800 0000 0000 0000 0000"            /* ˇˇˇ............. */
	$"0000 0001 1000 8C04 527A 696C 0004 2003"            /* ......å.Rzil.. . */
	$"6F62 6A64 0000 0056 6368 6278 0000 0006"            /* objd...Vchbx.... */
	$"00C8 0010 0101 0100 0001 0000 000E 0000"            /* .».............. */
	$"004B 0000 0000 FFFF FFFF 0000 1E1A 0000"            /* .K....ˇˇˇˇ...... */
	$"0001 0000 0000 0000 0002 0171 008B 1F4F"            /* ...........q.ã.O */
	$"6E6C 7920 6669 6C65 7320 7769 7468 202E"            /* nly files with . */
	$"7273 7263 2065 7874 656E 7369 6F6E 656E"            /* rsrc extensionen */
	$"6473 6F62 6A64 0000 005B 6368 6278 0000"            /* dsobjd...[chbx.. */
	$"0005 00E1 0010 0101 0000 0000 0000 004A"            /* ...·...........J */
	$"0000 008F 0000 0000 FFFF FFFF 0000 1E19"            /* ...è....ˇˇˇˇ.... */
	$"0000 0001 0000 0000 0000 0001 0001 008B"            /* ...............ã */
	$"2455 7365 2052 657A 696C 6C61 2773 2073"            /* $Use Rezilla's s */
	$"6967 6E61 7475 7265 2066 6F72 206E 6577"            /* ignature for new */
	$"206D 6170 7365 6E64 7365 6E64 7365 6E64"            /*  mapsendsendsend */
	$"2E"                                                 /* . */
};

data 'PPob' (11000, "AETE Editor Window") {
	$"0002 646F 706C 4145 5457 6F62 6A64 0000"            /* ..doplAETWobjd.. */
	$"001C 7769 6E64 2AF8 0002 1862 0000 FFFF"            /* ..wind*¯...b..ˇˇ */
	$"FFFF FFFF FFFF 029E 01F9 0000 0000 6265"            /* ˇˇˇˇˇˇ.û.˘....be */
	$"6773 6F62 6A64 0000 0012 7774 6861 FFFF"            /* gsobjd....wthaˇˇ */
	$"FFFE 0101 0003 0004 0001 0002 6F62 6A64"            /* ˇ˛..........objd */
	$"0000 0051 7769 6E68 0000 0000 02A0 008C"            /* ...Qwinh.....†.å */
	$"0101 0101 0100 FFFF FFFF 0000 0000 0000"            /* ......ˇˇˇˇ...... */
	$"0000 FFFF FFFF 0000 0000 0000 0000 0000"            /* ..ˇˇˇˇ.......... */
	$"0000 0000 0000 0000 0001 0000 0001 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0150 0000 0062 6567 736F 626A 6400 0000"            /* .P...begsobjd... */
	$"3C74 6267 7600 0000 0001 9F00 1D01 0101"            /* <tbgv.....ü..... */
	$"0101 0000 0000 9400 0000 0300 0000 00FF"            /* ......î........ˇ */
	$"FFFF FF00 0000 0000 0000 0000 0000 0000"            /* ˇˇˇ............. */
	$"0000 0000 0000 0100 0000 0100 0062 6567"            /* .............beg */
	$"736F 626A 6400 0000 4473 7478 7400 0000"            /* sobjd...Dstxt... */
	$"0000 4B00 0E01 0100 0000 0000 0000 0800"            /* ..K............. */
	$"0000 0700 0000 00FF FFFF FF00 0000 0000"            /* .......ˇˇˇˇ..... */
	$"0000 0000 0000 0000 0000 0001 2000 850D"            /* ............ .Ö. */
	$"4D61 6A6F 7220 7665 7273 696F 6E6F 626A"            /* Major versionobj */
	$"6400 0000 3B65 7478 7400 0000 0100 1900"            /* d...;etxt....... */
	$"1601 0100 0000 0000 0000 5400 0000 0100"            /* ..........T..... */
	$"0000 00FF FFFF FF45 644D 6400 0000 0000"            /* ...ˇˇˇˇEdMd..... */
	$"0000 0000 0000 0001 1000 8200 0002 2001"            /* ..........Ç... . */
	$"6F62 6A64 0000 0044 7374 7874 0000 0000"            /* objd...Dstxt.... */
	$"004B 000E 0101 0000 0000 0000 0079 0000"            /* .K...........y.. */
	$"0007 0000 0000 FFFF FFFF 0000 0000 0000"            /* ......ˇˇˇˇ...... */
	$"0000 0000 0000 0000 0000 0120 0085 0D4D"            /* ........... .Ö.M */
	$"696E 6F72 2076 6572 7369 6F6E 6F62 6A64"            /* inor versionobjd */
	$"0000 003B 6574 7874 0000 0002 0019 0016"            /* ...;etxt........ */
	$"0101 0000 0000 0000 00C4 0000 0001 0000"            /* .........ƒ...... */
	$"0000 FFFF FFFF 4564 4D64 0000 0000 0000"            /* ..ˇˇˇˇEdMd...... */
	$"0000 0000 0000 0110 0082 0000 0220 016F"            /* .........Ç... .o */
	$"626A 6400 0000 3D73 7478 7400 0000 0000"            /* bjd...=stxt..... */
	$"2500 0E01 0100 0000 0000 0001 4400 0000"            /* %...........D... */
	$"0700 0000 00FF FFFF FF00 0000 0000 0000"            /* .....ˇˇˇˇ....... */
	$"0000 0000 0000 0000 0001 2000 8506 5363"            /* .......... .Ö.Sc */
	$"7269 7074 6F62 6A64 0000 003B 6574 7874"            /* riptobjd...;etxt */
	$"0000 0003 0024 0016 0101 0000 0000 0000"            /* .....$.......... */
	$"0115 0000 0001 0000 0000 FFFF FFFF 4564"            /* ..........ˇˇˇˇEd */
	$"4D64 0000 0000 0000 0000 0000 0000 0110"            /* Md.............. */
	$"0082 0000 0220 016F 626A 6400 0000 3F73"            /* .Ç... .objd...?s */
	$"7478 7400 0000 0000 3000 0E01 0100 0000"            /* txt.....0....... */
	$"0000 0000 E700 0000 0700 0000 00FF FFFF"            /* ....Á........ˇˇˇ */
	$"FF00 0000 0000 0000 0000 0000 0000 0000"            /* ˇ............... */
	$"0001 2000 8508 4C61 6E67 7561 6765 6F62"            /* .. .Ö.Languageob */
	$"6A64 0000 003B 6574 7874 0000 0004 0024"            /* jd...;etxt.....$ */
	$"0016 0101 0000 0000 0000 0169 0000 0001"            /* ...........i.... */
	$"0000 0000 FFFF FFFF 4564 4D64 0000 0000"            /* ....ˇˇˇˇEdMd.... */
	$"0000 0000 0000 0000 0110 0082 0000 0220"            /* ...........Ç...  */
	$"0165 6E64 736F 626A 6400 0000 5674 6762"            /* .endsobjd...Vtgb */
	$"7853 5549 4201 B800 6401 0101 0101 0000"            /* xSUIB.∏.d....... */
	$"0000 DD00 0000 2200 0000 00FF FFFF FF00"            /* ..›..."....ˇˇˇˇ. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0100 0000 0100 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 A000 8505 5375"            /* ..........†.Ö.Su */
	$"6974 6562 6567 736F 626A 6400 0000 3C74"            /* itebegsobjd...<t */
	$"6267 7600 0000 0001 B000 4F01 0100 0000"            /* bgv.....∞.O..... */
	$"0000 0000 0400 0000 1200 0000 00FF FFFF"            /* .............ˇˇˇ */
	$"FF00 0000 0000 0000 0000 0000 0000 0000"            /* ˇ............... */
	$"0000 0000 0100 0000 0100 0062 6567 736F"            /* ...........begso */
	$"626A 6400 0000 3B73 7478 7400 0000 0000"            /* bjd...;stxt..... */
	$"1E00 1001 0100 0000 0000 0000 0600 0000"            /* ................ */
	$"0600 0000 00FF FFFF FF00 0000 0000 0000"            /* .....ˇˇˇˇ....... */
	$"0000 0000 0000 0000 0001 2000 8504 4E61"            /* .......... .Ö.Na */
	$"6D65 6F62 6A64 0000 003B 6574 7874 0000"            /* meobjd...;etxt.. */
	$"0005 0110 0016 0101 0000 0000 0000 002C"            /* ..............., */
	$"0000 0003 0000 0000 FFFF FFFF 0000 2AFD"            /* ........ˇˇˇˇ..*˝ */
	$"0000 0000 0000 0000 0000 0000 0110 0082"            /* ...............Ç */
	$"0000 FF20 036F 626A 6400 0000 4273 7478"            /* ..ˇ .objd...Bstx */
	$"7400 0000 0000 4300 1001 0100 0000 0000"            /* t.....C......... */
	$"0000 0600 0000 1F00 0000 00FF FFFF FF00"            /* ...........ˇˇˇˇ. */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"2000 850B 4465 7363 7269 7074 696F 6E6F"            /*  .Ö.Descriptiono */
	$"626A 6400 0000 3B65 7478 7400 0000 0600"            /* bjd...;etxt..... */
	$"F100 2C01 0100 0000 0000 0000 4A00 0000"            /* Ò.,.........J... */
	$"1C00 0000 00FF FFFF FF45 644D 6400 0000"            /* .....ˇˇˇˇEdMd... */
	$"0000 0000 0000 0000 0001 1000 8200 00FF"            /* ............Ç..ˇ */
	$"6003 6F62 6A64 0000 0039 7374 7874 0000"            /* `.objd...9stxt.. */
	$"0000 0018 000F 0101 0000 0000 0000 014A"            /* ...............J */
	$"0000 0008 0000 0000 FFFF FFFF 0000 0000"            /* ........ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0120 0085"            /* ............. .Ö */
	$"0249 446F 626A 6400 0000 3B65 7478 7400"            /* .IDobjd...;etxt. */
	$"0000 0700 3200 1601 0100 0000 0000 0001"            /* ....2........... */
	$"7600 0000 0500 0000 00FF FFFF FF45 644D"            /* v........ˇˇˇˇEdM */
	$"6400 0000 0000 0000 0000 0000 0001 1000"            /* d............... */
	$"8200 0004 2003 6F62 6A64 0000 003C 7374"            /* Ç... .objd...<st */
	$"7874 0000 0000 0022 0011 0101 0000 0000"            /* xt....."........ */
	$"0000 014A 0000 0020 0000 0000 FFFF FFFF"            /* ...J... ....ˇˇˇˇ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0120 0085 054C 6576 656C 6F62 6A64 0000"            /* . .Ö.Levelobjd.. */
	$"003B 6574 7874 0000 0008 0032 0016 0101"            /* .;etxt.....2.... */
	$"0000 0000 0000 0176 0000 001D 0000 0000"            /* .......v........ */
	$"FFFF FFFF 4564 4D64 0000 0000 0000 0000"            /* ˇˇˇˇEdMd........ */
	$"0000 0000 0110 0082 0000 0420 016F 626A"            /* .......Ç... .obj */
	$"6400 0000 3E73 7478 7400 0000 0000 2C00"            /* d...>stxt.....,. */
	$"1101 0100 0000 0000 0001 4A00 0000 3800"            /* ..........J...8. */
	$"0000 00FF FFFF FF00 0000 0000 0000 0000"            /* ...ˇˇˇˇ......... */
	$"0000 0000 0000 0001 2000 8507 5665 7273"            /* ........ .Ö.Vers */
	$"696F 6E6F 626A 6400 0000 3B65 7478 7400"            /* ionobjd...;etxt. */
	$"0000 0900 3200 1601 0100 0000 0000 0001"            /* ..∆.2........... */
	$"7600 0000 3500 0000 00FF FFFF FF45 644D"            /* v...5....ˇˇˇˇEdM */
	$"6400 0000 0000 0000 0000 0000 0001 1000"            /* d............... */
	$"8200 0004 2001 656E 6473 656E 6473 6F62"            /* Ç... .endsendsob */
	$"6A64 0000 0037 7374 7874 4E61 6D65 0079"            /* jd...7stxtName.y */
	$"0030 0101 0101 0100 0000 0007 0000 0006"            /* .0.............. */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0120 0085 006F 626A"            /* ......... .Ö.obj */
	$"6400 0000 3E73 7478 7400 0000 0000 2D00"            /* d...>stxt.....-. */
	$"1001 0100 0000 0000 0000 0800 0000 3A00"            /* ..............:. */
	$"0000 00FF FFFF FF00 0000 0000 0000 0000"            /* ...ˇˇˇˇ......... */
	$"0000 0000 0000 0001 2000 8507 5375 6974"            /* ........ .Ö.Suit */
	$"6573 3A6F 626A 6400 0000 3D70 6F70 6253"            /* es:objd...=popbS */
	$"5549 5400 BE00 1401 0101 0100 0000 0000"            /* UIT.æ........... */
	$"0700 0000 4A00 0000 00FF FFFF FF53 5549"            /* ....J....ˇˇˇˇSUI */
	$"5400 0000 0000 0000 FE00 00FF FF01 9000"            /* T.......˛..ˇˇ.ê. */
	$"8500 0000 0000 0001 656E 6473 6F62 6A64"            /* Ö.......endsobjd */
	$"0000 0059 7063 746C 4143 544C 0154 001E"            /* ...YpctlACTL.T.. */
	$"0101 0101 0000 0000 0003 0000 008C 0000"            /* .............å.. */
	$"0000 FFFF FFFF 0000 0000 0000 0000 0000"            /* ..ˇˇˇˇ.......... */
	$"0000 0000 0000 0000 0001 0000 0001 0000"            /* ................ */
	$"0086 4143 544C 03E9 0001 FFFF FFFF FFFF"            /* .ÜACTL.È..ˇˇˇˇˇˇ */
	$"0000 3333 9999 FFFF FFFF 0000 006F 626A"            /* ..33ôôˇˇˇˇ...obj */
	$"6400 0000 4D6D 7076 7741 4D50 5602 7601"            /* d...MmpvwAMPV.v. */
	$"2701 0101 0101 0100 0000 1400 0000 AA00"            /* '.............™. */
	$"0000 00FF FFFF FF00 0000 0000 0000 0000"            /* ...ˇˇˇˇ......... */
	$"0000 0000 0000 0000 0000 0100 0000 0100"            /* ................ */
	$"0000 042B 5C2B C02C 242C 8800 0141 4354"            /* ...+\+¿,$,à..ACT */
	$"4C00 6F62 6A64 0000 0036 736C 6964 534C"            /* L.objd...6slidSL */
	$"4944 00D2 0015 0001 0101 0100 0000 0170"            /* ID.“...........p */
	$"0000 0090 0000 0000 FFFF FFFF 534C 4944"            /* ...ê....ˇˇˇˇSLID */
	$"0000 0000 0000 0000 0000 0000 0031 0004"            /* .............1.. */
	$"6F62 6A64 0000 0037 7374 7874 5349 4443"            /* objd...7stxtSIDC */
	$"004F 0011 0101 0001 0100 0000 0246 0000"            /* .O...........F.. */
	$"0093 0000 0000 FFFF FFFF 0000 0000 0000"            /* .ì....ˇˇˇˇ...... */
	$"0000 0000 0000 0000 0000 0120 0082 006F"            /* ........... .Ç.o */
	$"626A 6400 0000 5170 6C63 6400 0000 0002"            /* bjd...Qplcd..... */
	$"A000 2801 0101 0001 01FF FFFF FF00 0001"            /* †.(......ˇˇˇˇ... */
	$"D200 0000 00FF FFFF FF00 0000 0000 0000"            /* “....ˇˇˇˇ....... */
	$"0000 0000 0000 0000 0000 0000 0100 0000"            /* ................ */
	$"0100 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 E000 0000 6265 6773 6F62 6A64"            /* ....‡...begsobjd */
	$"0000 003C 7075 7368 566C 6964 0041 0014"            /* ...<pushVlid.A.. */
	$"0101 0000 0101 0000 0247 0000 0009 0000"            /* .........G...∆.. */
	$"0000 FFFF FFFF 0000 0384 0000 0000 0000"            /* ..ˇˇˇˇ...Ñ...... */
	$"0000 0000 0000 0170 0000 0453 6176 6501"            /* .......p...Save. */
	$"6F62 6A64 0000 003E 7075 7368 436E 636C"            /* objd...>pushCncl */
	$"0041 0014 0101 0000 0101 0000 01F9 0000"            /* .A...........˘.. */
	$"0009 0000 0000 FFFF FFFF 0000 0385 0000"            /* .∆....ˇˇˇˇ...Ö.. */
	$"0000 0000 0000 0000 0000 0170 0000 0643"            /* ...........p...C */
	$"616E 6365 6C00 6F62 6A64 0000 003E 7075"            /* ancel.objd...>pu */
	$"7368 5276 7274 0041 0014 0101 0100 0001"            /* shRvrt.A........ */
	$"0000 001C 0000 0009 0000 0000 FFFF FFFF"            /* .......∆....ˇˇˇˇ */
	$"0000 0007 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0170 0000 0652 6576 6572 7400 6F62 6A64"            /* .p...Revert.objd */
	$"0000 0024 6963 6E70 4C6F 636B 0010 0010"            /* ...$icnpLock.... */
	$"0101 0100 0001 0000 0006 0000 000B 0000"            /* ................ */
	$"0000 FFFF FFFF 0000 656E 6473 656E 6473"            /* ..ˇˇˇˇ..endsends */
	$"656E 642E"                                          /* end. */
};

data 'PPob' (11100, "Event Pane") {
	$"0002 6F62 6A64 0000 003C 7669 6577 0000"            /* ..objd...<view.. */
	$"0000 0276 0127 0101 0000 0000 0000 0000"            /* ...v.'.......... */
	$"0000 0000 0000 0000 FFFF FFFF 0000 0018"            /* ........ˇˇˇˇ.... */
	$"0000 002C 0000 0000 0000 0000 0000 0010"            /* ...,............ */
	$"0000 0010 0000 6265 6773 6F62 6A64 0000"            /* ......begsobjd.. */
	$"003C 7462 6776 0000 0000 026F 004C 0101"            /* .<tbgv.....o.L.. */
	$"0000 0000 0000 0007 0000 0005 0000 0000"            /* ................ */
	$"FFFF FFFF 0000 0000 0000 0000 0000 0000"            /* ˇˇˇˇ............ */
	$"0000 0000 0000 0001 0000 0001 0000 6265"            /* ..............be */
	$"6773 6F62 6A64 0000 003B 7374 7874 0000"            /* gsobjd...;stxt.. */
	$"0000 001E 0010 0101 0000 0000 0000 000F"            /* ................ */
	$"0000 000A 0000 0000 FFFF FFFF 0000 0000"            /* ...¬....ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0120 0085"            /* ............. .Ö */
	$"044E 616D 656F 626A 6400 0000 3B65 7478"            /* .Nameobjd...;etx */
	$"7400 0000 0100 D200 1601 0100 0000 0000"            /* t.....“......... */
	$"0000 2E00 0000 0500 0000 00FF FFFF FF45"            /* ...........ˇˇˇˇE */
	$"644D 6400 0000 0000 0000 0000 0000 0001"            /* dMd............. */
	$"1000 8200 00FF 2003 6F62 6A64 0000 003C"            /* ..Ç..ˇ .objd...< */
	$"7374 7874 0000 0000 0028 0010 0101 0000"            /* stxt.....(...... */
	$"0000 0000 010D 0000 000A 0000 0000 FFFF"            /* .........¬....ˇˇ */
	$"FFFF 0000 0000 0000 0000 0000 0000 0000"            /* ˇˇ.............. */
	$"0000 0120 0085 0543 6C61 7373 6F62 6A64"            /* ... .Ö.Classobjd */
	$"0000 003B 6574 7874 0000 0002 0032 0016"            /* ...;etxt.....2.. */
	$"0101 0000 0000 0000 0134 0000 0005 0000"            /* .........4...... */
	$"0000 FFFF FFFF 4564 4D64 0000 0000 0000"            /* ..ˇˇˇˇEdMd...... */
	$"0000 0000 0000 0110 0082 0000 0420 036F"            /* .........Ç... .o */
	$"626A 6400 0000 3973 7478 7400 0000 0000"            /* bjd...9stxt..... */
	$"1400 1001 0100 0000 0000 0001 7400 0000"            /* ............t... */
	$"0A00 0000 00FF FFFF FF00 0000 0000 0000"            /* ¬....ˇˇˇˇ....... */
	$"0000 0000 0000 0000 0001 2000 8502 4944"            /* .......... .Ö.ID */
	$"6F62 6A64 0000 003B 6574 7874 0000 0003"            /* objd...;etxt.... */
	$"0032 0016 0101 0000 0000 0000 018A 0000"            /* .2...........ä.. */
	$"0005 0000 0000 FFFF FFFF 4564 4D64 0000"            /* ......ˇˇˇˇEdMd.. */
	$"0000 0000 0000 0000 0000 0110 0082 0000"            /* .............Ç.. */
	$"0420 036F 626A 6400 0000 4273 7478 7400"            /* . .objd...Bstxt. */
	$"0000 0000 4600 1201 0100 0000 0000 0000"            /* ....F........... */
	$"0F00 0000 2400 0000 00FF FFFF FF00 0000"            /* ....$....ˇˇˇˇ... */
	$"0000 0000 0000 0000 0000 0000 0001 2000"            /* .............. . */
	$"850B 4465 7363 7269 7074 696F 6E6F 626A"            /* Ö.Descriptionobj */
	$"6400 0000 3B65 7478 7400 0000 0402 0D00"            /* d...;etxt....... */
	$"2801 0100 0000 0000 0000 5500 0000 1F00"            /* (.........U..... */
	$"0000 00FF FFFF FF45 644D 6400 0000 0000"            /* ...ˇˇˇˇEdMd..... */
	$"0000 0000 0000 0001 1000 8200 00FF 6003"            /* ..........Ç..ˇ`. */
	$"656E 6473 6F62 6A64 0000 0061 7467 6278"            /* endsobjd...atgbx */
	$"4452 4354 012C 0064 0101 0000 0000 0000"            /* DRCT.,.d........ */
	$"000A 0000 0053 0000 0000 FFFF FFFF 0000"            /* .¬...S....ˇˇˇˇ.. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0001 0000 0001 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 00A0 0085 1044 6972"            /* .........†.Ö.Dir */
	$"6563 7420 7061 7261 6D65 7465 7262 6567"            /* ect parameterbeg */
	$"736F 626A 6400 0000 3C74 6267 7600 0000"            /* sobjd...<tbgv... */
	$"0001 2300 5201 0100 0000 0000 0000 0400"            /* ..#.R........... */
	$"0000 1000 0000 00FF FFFF FF00 0000 0000"            /* .......ˇˇˇˇ..... */
	$"0000 0000 0000 0000 0000 0000 0000 0100"            /* ................ */
	$"0000 0100 0062 6567 736F 626A 6400 0000"            /* .....begsobjd... */
	$"3B73 7478 7400 0000 0000 1B00 1001 0100"            /* ;stxt........... */
	$"0000 0000 0000 0600 0000 0800 0000 00FF"            /* ...............ˇ */
	$"FFFF FF00 0000 0000 0000 0000 0000 0000"            /* ˇˇˇ............. */
	$"0000 0001 2000 8504 5479 7065 6F62 6A64"            /* .... .Ö.Typeobjd */
	$"0000 003B 6574 7874 0000 000B 0032 0016"            /* ...;etxt.....2.. */
	$"0101 0000 0000 0000 0028 0000 0004 0000"            /* .........(...... */
	$"0000 FFFF FFFF 4564 4D64 0000 0000 0000"            /* ..ˇˇˇˇEdMd...... */
	$"0000 0000 0000 0110 0082 0000 0420 036F"            /* .........Ç... .o */
	$"626A 6400 0000 4273 7478 7400 0000 0000"            /* bjd...Bstxt..... */
	$"4200 1201 0100 0000 0000 0000 0600 0000"            /* B............... */
	$"2200 0000 00FF FFFF FF00 0000 0000 0000"            /* "....ˇˇˇˇ....... */
	$"0000 0000 0000 0000 0001 2000 850B 4465"            /* .......... .Ö.De */
	$"7363 7269 7074 696F 6E6F 626A 6400 0000"            /* scriptionobjd... */
	$"3B65 7478 7400 0000 0D00 D400 2C01 0100"            /* ;etxt.....‘.,... */
	$"0000 0000 0000 4700 0000 2000 0000 00FF"            /* ......G... ....ˇ */
	$"FFFF FF45 644D 6400 0000 0000 0000 0000"            /* ˇˇˇEdMd......... */
	$"0000 0001 1000 8200 00FF 6003 6F62 6A64"            /* ......Ç..ˇ`.objd */
	$"0000 003D 706F 7062 0000 000C 00B4 0012"            /* ...=popb.....¥.. */
	$"0101 0000 0000 0000 0065 0000 0007 0000"            /* .........e...... */
	$"0000 FFFF FFFF 0000 2B68 0000 0000 0000"            /* ..ˇˇˇˇ..+h...... */
	$"00A1 0000 FFFF 0194 0085 0000 0000 0000"            /* .°..ˇˇ.î.Ö...... */
	$"0165 6E64 7365 6E64 736F 626A 6400 0000"            /* .endsendsobjd... */
	$"6974 6762 7852 4550 4C01 2C00 6401 0100"            /* itgbxREPL.,.d... */
	$"0000 0000 0000 0A00 0000 BE00 0000 00FF"            /* ......¬...æ....ˇ */
	$"FFFF FF00 0000 0000 0000 0000 0000 0000"            /* ˇˇˇ............. */
	$"0000 0000 0000 0100 0000 0100 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 A000"            /* ..............†. */
	$"8518 5265 706C 7927 7320 6469 7265 6374"            /* Ö.Reply's direct */
	$"2070 6172 616D 6574 6572 6265 6773 6F62"            /*  parameterbegsob */
	$"6A64 0000 003C 7462 6776 0000 0000 0122"            /* jd...<tbgv....." */
	$"0050 0101 0000 0000 0000 0003 0000 0011"            /* .P.............. */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0000 0001 0000 0001"            /* ................ */
	$"0000 6265 6773 6F62 6A64 0000 003B 7374"            /* ..begsobjd...;st */
	$"7874 0000 0000 001B 0012 0101 0000 0000"            /* xt.............. */
	$"0000 0007 0000 0007 0000 0000 FFFF FFFF"            /* ............ˇˇˇˇ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0120 0085 0454 7970 656F 626A 6400 0000"            /* . .Ö.Typeobjd... */
	$"3B65 7478 7400 0000 1500 3200 1601 0100"            /* ;etxt.....2..... */
	$"0000 0000 0000 2900 0000 0300 0000 00FF"            /* ......)........ˇ */
	$"FFFF FF45 644D 6400 0000 0000 0000 0000"            /* ˇˇˇEdMd......... */
	$"0000 0001 1000 8200 0004 2003 6F62 6A64"            /* ......Ç... .objd */
	$"0000 0042 7374 7874 0000 0000 0042 0012"            /* ...Bstxt.....B.. */
	$"0101 0000 0000 0000 0007 0000 0021 0000"            /* .............!.. */
	$"0000 FFFF FFFF 0000 0000 0000 0000 0000"            /* ..ˇˇˇˇ.......... */
	$"0000 0000 0000 0120 0085 0B44 6573 6372"            /* ....... .Ö.Descr */
	$"6970 7469 6F6E 6F62 6A64 0000 003B 6574"            /* iptionobjd...;et */
	$"7874 0000 0017 00D4 002C 0101 0000 0000"            /* xt.....‘.,...... */
	$"0000 0048 0000 001F 0000 0000 FFFF FFFF"            /* ...H........ˇˇˇˇ */
	$"4564 4D64 0000 0000 0000 0000 0000 0000"            /* EdMd............ */
	$"0110 0082 0000 FF60 036F 626A 6400 0000"            /* ...Ç..ˇ`.objd... */
	$"3D70 6F70 6200 0000 1600 B400 1201 0100"            /* =popb.....¥..... */
	$"0000 0000 0000 6600 0000 0600 0000 00FF"            /* ......f........ˇ */
	$"FFFF FF00 002B 7200 0000 0000 0000 A200"            /* ˇˇˇ..+r.......¢. */
	$"00FF FF01 9400 8500 0000 0000 0001 656E"            /* .ˇˇ.î.Ö.......en */
	$"6473 656E 6473 6F62 6A64 0000 0060 7467"            /* dsendsobjd...`tg */
	$"6278 4F54 4852 012C 00AA 0101 0000 0000"            /* bxOTHR.,.™...... */
	$"0000 0140 0000 0078 0000 0000 FFFF FFFF"            /* ...@...x....ˇˇˇˇ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0001 0000 0001 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 00A0 0085 0F4F"            /* ...........†.Ö.O */
	$"7468 6572 2070 6172 616D 6574 6572 6265"            /* ther parameterbe */
	$"6773 6F62 6A64 0000 003C 7462 6776 0000"            /* gsobjd...<tbgv.. */
	$"0000 0125 0097 0101 0000 0000 0000 0003"            /* ...%.ó.......... */
	$"0000 0010 0000 0000 FFFF FFFF 0000 0000"            /* ........ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"0000 0001 0000 6265 6773 6F62 6A64 0000"            /* ......begsobjd.. */
	$"003B 7374 7874 0000 0000 001B 0010 0101"            /* .;stxt.......... */
	$"0000 0000 0000 0003 0000 003E 0000 0000"            /* ...........>.... */
	$"FFFF FFFF 0000 0000 0000 0000 0000 0000"            /* ˇˇˇˇ............ */
	$"0000 0000 0120 0085 0454 7970 656F 626A"            /* ..... .Ö.Typeobj */
	$"6400 0000 3B65 7478 7400 0000 2100 3200"            /* d...;etxt...!.2. */
	$"1601 0100 0000 0000 0000 3100 0000 3C00"            /* ..........1...<. */
	$"0000 00FF FFFF FF45 644D 6400 0000 0000"            /* ...ˇˇˇˇEdMd..... */
	$"0000 0000 0000 0001 1000 8200 0004 2003"            /* ..........Ç... . */
	$"6F62 6A64 0000 0042 7374 7874 0000 0000"            /* objd...Bstxt.... */
	$"0042 0012 0101 0000 0000 0000 0003 0000"            /* .B.............. */
	$"005D 0000 0000 FFFF FFFF 0000 0000 0000"            /* .]....ˇˇˇˇ...... */
	$"0000 0000 0000 0000 0000 0120 0085 0B44"            /* ........... .Ö.D */
	$"6573 6372 6970 7469 6F6E 6F62 6A64 0000"            /* escriptionobjd.. */
	$"003B 6574 7874 0000 0023 00DA 0036 0101"            /* .;etxt...#.⁄.6.. */
	$"0000 0000 0000 0047 0000 005B 0000 0000"            /* .......G...[.... */
	$"FFFF FFFF 4564 4D64 0000 0000 0000 0000"            /* ˇˇˇˇEdMd........ */
	$"0000 0000 0110 0082 0000 FF60 036F 626A"            /* .......Ç..ˇ`.obj */
	$"6400 0000 3D70 6F70 6200 0000 2200 B500"            /* d...=popb...".µ. */
	$"1301 0100 0000 0000 0000 6B00 0000 3100"            /* ..........k...1. */
	$"0000 00FF FFFF FF00 002B 7E00 0000 0000"            /* ...ˇˇˇˇ..+~..... */
	$"0000 A300 00FF FF01 9400 8500 0000 0000"            /* ..£..ˇˇ.î.Ö..... */
	$"0001 6F62 6A64 0000 003B 7374 7874 0000"            /* ..objd...;stxt.. */
	$"0000 001E 0010 0101 0000 0000 0000 0003"            /* ................ */
	$"0000 0009 0000 0000 FFFF FFFF 0000 0000"            /* ...∆....ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0120 0085"            /* ............. .Ö */
	$"044E 616D 656F 626A 6400 0000 3B65 7478"            /* .Nameobjd...;etx */
	$"7400 0000 1F00 F200 1601 0100 0000 0000"            /* t.....Ú......... */
	$"0000 2700 0000 0700 0000 00FF FFFF FF45"            /* ..'........ˇˇˇˇE */
	$"644D 6400 0000 0000 0000 0000 0000 0001"            /* dMd............. */
	$"1000 8200 00FF 2003 6F62 6A64 0000 003E"            /* ..Ç..ˇ .objd...> */
	$"7374 7874 0000 0000 002D 0010 0101 0000"            /* stxt.....-...... */
	$"0000 0000 0003 0000 0025 0000 0000 FFFF"            /* .........%....ˇˇ */
	$"FFFF 0000 0000 0000 0000 0000 0000 0000"            /* ˇˇ.............. */
	$"0000 0120 0085 074B 6579 776F 7264 6F62"            /* ... .Ö.Keywordob */
	$"6A64 0000 003B 6574 7874 0000 0020 0032"            /* jd...;etxt... .2 */
	$"0016 0101 0000 0000 0000 0031 0000 0022"            /* ...........1..." */
	$"0000 0000 FFFF FFFF 4564 4D64 0000 0000"            /* ....ˇˇˇˇEdMd.... */
	$"0000 0000 0000 0000 0110 0082 0000 0420"            /* ...........Ç...  */
	$"0365 6E64 7365 6E64 736F 626A 6400 0000"            /* .endsendsobjd... */
	$"3673 6C69 644F 534C 4900 E600 1700 0100"            /* 6slidOSLI.Ê..... */
	$"0000 0000 0001 4000 0000 5E00 0000 00FF"            /* ......@...^....ˇ */
	$"FFFF FF4F 534C 4900 0000 0000 0000 0000"            /* ˇˇˇOSLI......... */
	$"0000 0000 3100 046F 626A 6400 0000 3773"            /* ....1..objd...7s */
	$"7478 744F 4944 4300 3D00 1001 0101 0000"            /* txtOIDC.=....... */
	$"0000 0002 2A00 0000 6300 0000 00FF FFFF"            /* ....*...c....ˇˇˇ */
	$"FF00 0000 0000 0000 0000 0000 0000 0000"            /* ˇ............... */
	$"0001 2000 8200 656E 6473 656E 642E"                 /* .. .Ç.endsend. */
};

data 'PPob' (11200, "Class Pane") {
	$"0002 6F62 6A64 0000 003C 7669 6577 0000"            /* ..objd...<view.. */
	$"0000 0276 0127 0001 0000 0000 0000 0000"            /* ...v.'.......... */
	$"0000 0000 0000 0000 FFFF FFFF 0000 0018"            /* ........ˇˇˇˇ.... */
	$"0000 002C 0000 0000 0000 0000 0000 0010"            /* ...,............ */
	$"0000 0010 0000 6265 6773 6F62 6A64 0000"            /* ......begsobjd.. */
	$"003C 7462 6776 0000 0000 0267 0051 0101"            /* .<tbgv.....g.Q.. */
	$"0000 0000 0000 000A 0000 0005 0000 0000"            /* .......¬........ */
	$"FFFF FFFF 0000 0000 0000 0000 0000 0000"            /* ˇˇˇˇ............ */
	$"0000 0000 0000 0001 0000 0001 0000 6265"            /* ..............be */
	$"6773 6F62 6A64 0000 003B 7374 7874 0000"            /* gsobjd...;stxt.. */
	$"0000 001E 0010 0101 0000 0000 0000 000D"            /* ................ */
	$"0000 000A 0000 0000 FFFF FFFF 0000 0000"            /* ...¬....ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0120 0085"            /* ............. .Ö */
	$"044E 616D 656F 626A 6400 0000 3B65 7478"            /* .Nameobjd...;etx */
	$"7400 0000 0100 D200 1601 0100 0000 0000"            /* t.....“......... */
	$"0000 2C00 0000 0500 0000 00FF FFFF FF45"            /* ..,........ˇˇˇˇE */
	$"644D 6400 0000 0000 0000 0000 0000 0001"            /* dMd............. */
	$"1000 8200 00FF 2003 6F62 6A64 0000 003F"            /* ..Ç..ˇ .objd...? */
	$"7374 7874 0000 0000 0032 0010 0101 0000"            /* stxt.....2...... */
	$"0000 0000 010B 0000 000A 0000 0000 FFFF"            /* .........¬....ˇˇ */
	$"FFFF 0000 0000 0000 0000 0000 0000 0000"            /* ˇˇ.............. */
	$"0000 0120 0085 0843 6C61 7373 2049 446F"            /* ... .Ö.Class IDo */
	$"626A 6400 0000 3B65 7478 7400 0000 0200"            /* bjd...;etxt..... */
	$"3200 1601 0100 0000 0000 0001 3C00 0000"            /* 2...........<... */
	$"0500 0000 00FF FFFF FF45 644D 6400 0000"            /* .....ˇˇˇˇEdMd... */
	$"0000 0000 0000 0000 0001 1000 8200 0004"            /* ............Ç... */
	$"2003 6F62 6A64 0000 0042 7374 7874 0000"            /*  .objd...Bstxt.. */
	$"0000 0046 0010 0101 0000 0000 0000 000D"            /* ...F............ */
	$"0000 0024 0000 0000 FFFF FFFF 0000 0000"            /* ...$....ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0120 0085"            /* ............. .Ö */
	$"0B44 6573 6372 6970 7469 6F6E 6F62 6A64"            /* .Descriptionobjd */
	$"0000 003B 6574 7874 0000 0003 020D 0028"            /* ...;etxt.......( */
	$"0101 0000 0000 0000 0053 0000 001F 0000"            /* .........S...... */
	$"0000 FFFF FFFF 4564 4D64 0000 0000 0000"            /* ..ˇˇˇˇEdMd...... */
	$"0000 0000 0000 0110 0082 0000 FF60 0365"            /* .........Ç..ˇ`.e */
	$"6E64 736F 626A 6400 0000 5874 6762 7845"            /* ndsobjd...XtgbxE */
	$"4C45 4D01 2C00 AA01 0100 0000 0000 0001"            /* LEM.,.™......... */
	$"4000 0000 7600 0000 00FF FFFF FF00 0000"            /* @...v....ˇˇˇˇ... */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0100 0000 0100 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 A000 8507 456C 656D"            /* ........†.Ö.Elem */
	$"656E 7462 6567 736F 626A 6400 0000 3C74"            /* entbegsobjd...<t */
	$"6267 7600 0000 0001 2200 6201 0100 0000"            /* bgv.....".b..... */
	$"0000 0000 0400 0000 0F00 0000 00FF FFFF"            /* .............ˇˇˇ */
	$"FF00 0000 0000 0000 0000 0000 0000 0000"            /* ˇ............... */
	$"0000 0000 0100 0000 0100 0062 6567 736F"            /* ...........begso */
	$"626A 6400 0000 4173 7478 7400 0000 0000"            /* bjd...Astxt..... */
	$"3E00 1001 0100 0000 0000 0000 0500 0000"            /* >............... */
	$"0C00 0000 00FF FFFF FF00 0000 0000 0000"            /* .....ˇˇˇˇ....... */
	$"0000 0000 0000 0000 0001 2000 850A 456C"            /* .......... .Ö¬El */
	$"656D 656E 7420 4944 6F62 6A64 0000 003B"            /* ement IDobjd...; */
	$"6574 7874 0000 0016 0032 0016 0101 0000"            /* etxt.....2...... */
	$"0000 0000 0044 0000 0007 0000 0000 FFFF"            /* .....D........ˇˇ */
	$"FFFF 4564 4D64 0000 0000 0000 0000 0000"            /* ˇˇEdMd.......... */
	$"0000 0110 0082 0000 0420 036F 626A 6400"            /* .....Ç... .objd. */
	$"0000 4073 7478 7400 0000 0000 3700 1001"            /* ..@stxt.....7... */
	$"0100 0000 0000 0000 2100 0000 2C00 0000"            /* ........!...,... */
	$"00FF FFFF FF00 0000 0000 0000 0000 0000"            /* .ˇˇˇˇ........... */
	$"0000 0000 0001 2000 8509 4B65 7920 666F"            /* ...... .Ö∆Key fo */
	$"726D 736F 626A 6400 0000 3B65 7478 7400"            /* rmsobjd...;etxt. */
	$"0000 1700 3200 1601 0100 0000 0000 0000"            /* ....2........... */
	$"5900 0000 2700 0000 00FF FFFF FF45 644D"            /* Y...'....ˇˇˇˇEdM */
	$"6400 0000 0000 0000 0000 0000 0001 1000"            /* d............... */
	$"8200 0004 2003 6F62 6A64 0000 0036 736C"            /* Ç... .objd...6sl */
	$"6964 4B53 4C49 0050 0017 0001 0000 0000"            /* idKSLI.P........ */
	$"0000 005B 0000 003E 0000 0000 FFFF FFFF"            /* ...[...>....ˇˇˇˇ */
	$"4B53 4C49 0000 0000 0000 0000 0000 0000"            /* KSLI............ */
	$"0031 0004 6F62 6A64 0000 0037 7374 7874"            /* .1..objd...7stxt */
	$"4B49 4443 003C 0010 0101 0100 0000 0000"            /* KIDC.<.......... */
	$"008F 0000 002C 0000 0000 FFFF FFFF 0000"            /* .è...,....ˇˇˇˇ.. */
	$"0000 0000 0000 0000 0000 0000 0000 0120"            /* ...............  */
	$"0082 0065 6E64 7365 6E64 736F 626A 6400"            /* .Ç.endsendsobjd. */
	$"0000 5974 6762 7850 524F 5001 2C00 AA01"            /* ..YtgbxPROP.,.™. */
	$"0100 0000 0000 0000 0A00 0000 7600 0000"            /* ........¬...v... */
	$"00FF FFFF FF00 0000 0000 0000 0000 0000"            /* .ˇˇˇˇ........... */
	$"0000 0000 0000 0000 0100 0000 0100 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"A000 8508 5072 6F70 6572 7479 6265 6773"            /* †.Ö.Propertybegs */
	$"6F62 6A64 0000 003C 7462 6776 0000 0000"            /* objd...<tbgv.... */
	$"0124 0095 0101 0000 0000 0000 0004 0000"            /* .$.ï............ */
	$"0010 0000 0000 FFFF FFFF 0000 0000 0000"            /* ......ˇˇˇˇ...... */
	$"0000 0000 0000 0000 0000 0000 0001 0000"            /* ................ */
	$"0001 0000 6265 6773 6F62 6A64 0000 003B"            /* ....begsobjd...; */
	$"7374 7874 0000 0000 001E 0010 0101 0000"            /* stxt............ */
	$"0000 0000 0002 0000 000B 0000 0000 FFFF"            /* ..............ˇˇ */
	$"FFFF 0000 0000 0000 0000 0000 0000 0000"            /* ˇˇ.............. */
	$"0000 0120 0085 044E 616D 656F 626A 6400"            /* ... .Ö.Nameobjd. */
	$"0000 3B65 7478 7400 0000 0B00 FA00 1601"            /* ..;etxt.....˙... */
	$"0100 0000 0000 0000 2100 0000 0600 0000"            /* ........!....... */
	$"00FF FFFF FF45 644D 6400 0000 0000 0000"            /* .ˇˇˇˇEdMd....... */
	$"0000 0000 0001 1000 8200 00FF 2003 6F62"            /* ........Ç..ˇ .ob */
	$"6A64 0000 003E 7374 7874 0000 0000 002C"            /* jd...>stxt....., */
	$"0010 0101 0000 0000 0000 0002 0000 0025"            /* ...............% */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0120 0085 074B 6579"            /* ......... .Ö.Key */
	$"776F 7264 6F62 6A64 0000 003B 6574 7874"            /* wordobjd...;etxt */
	$"0000 000C 0032 0016 0101 0000 0000 0000"            /* .....2.......... */
	$"0030 0000 0020 0000 0000 FFFF FFFF 4564"            /* .0... ....ˇˇˇˇEd */
	$"4D64 0000 0000 0000 0000 0000 0000 0110"            /* Md.............. */
	$"0082 0000 0420 036F 626A 6400 0000 3B73"            /* .Ç... .objd...;s */
	$"7478 7400 0000 0000 1B00 1201 0100 0000"            /* txt............. */
	$"0000 0000 0200 0000 4000 0000 00FF FFFF"            /* ........@....ˇˇˇ */
	$"FF00 0000 0000 0000 0000 0000 0000 0000"            /* ˇ............... */
	$"0001 2000 8504 5479 7065 6F62 6A64 0000"            /* .. .Ö.Typeobjd.. */
	$"003B 6574 7874 0000 000D 0032 0016 0101"            /* .;etxt.....2.... */
	$"0000 0000 0000 0030 0000 003C 0000 0000"            /* .......0...<.... */
	$"FFFF FFFF 4564 4D64 0000 0000 0000 0000"            /* ˇˇˇˇEdMd........ */
	$"0000 0000 0110 0082 0000 0420 036F 626A"            /* .......Ç... .obj */
	$"6400 0000 4273 7478 7400 0000 0000 4200"            /* d...Bstxt.....B. */
	$"1201 0100 0000 0000 0000 0200 0000 5D00"            /* ..............]. */
	$"0000 00FF FFFF FF00 0000 0000 0000 0000"            /* ...ˇˇˇˇ......... */
	$"0000 0000 0000 0001 2000 850B 4465 7363"            /* ........ .Ö.Desc */
	$"7269 7074 696F 6E6F 626A 6400 0000 3B65"            /* riptionobjd...;e */
	$"7478 7400 0000 0F00 DA00 3601 0100 0000"            /* txt.....⁄.6..... */
	$"0000 0000 4600 0000 5B00 0000 00FF FFFF"            /* ....F...[....ˇˇˇ */
	$"FF45 644D 6400 0000 0000 0000 0000 0000"            /* ˇEdMd........... */
	$"0001 1000 8200 00FF 6003 6F62 6A64 0000"            /* ....Ç..ˇ`.objd.. */
	$"003D 706F 7062 0000 000E 00B5 0013 0101"            /* .=popb.....µ.... */
	$"0000 0000 0000 0068 0000 0033 0000 0000"            /* .......h...3.... */
	$"FFFF FFFF 0000 2BCE 0000 0000 0000 00A4"            /* ˇˇˇˇ..+Œ.......§ */
	$"0000 FFFF 0194 0085 0000 0000 0000 0165"            /* ..ˇˇ.î.Ö.......e */
	$"6E64 7365 6E64 736F 626A 6400 0000 3673"            /* ndsendsobjd...6s */
	$"6C69 6445 534C 4900 E000 1700 0100 0000"            /* lidESLI.‡....... */
	$"0000 0001 3E00 0000 5B00 0000 00FF FFFF"            /* ....>...[....ˇˇˇ */
	$"FF45 534C 4900 0000 0000 0000 0000 0000"            /* ˇESLI........... */
	$"0000 3100 046F 626A 6400 0000 3773 7478"            /* ..1..objd...7stx */
	$"7450 4944 4300 3D00 1001 0101 0000 0000"            /* tPIDC.=......... */
	$"0000 F200 0000 5F00 0000 00FF FFFF FF00"            /* ..Ú..._....ˇˇˇˇ. */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"2000 8200 6F62 6A64 0000 0036 736C 6964"            /*  .Ç.objd...6slid */
	$"5053 4C49 00E0 0017 0001 0000 0000 0000"            /* PSLI.‡.......... */
	$"000B 0000 005B 0000 0000 FFFF FFFF 5053"            /* .....[....ˇˇˇˇPS */
	$"4C49 0000 0000 0000 0000 0000 0000 0031"            /* LI.............1 */
	$"0004 6F62 6A64 0000 0037 7374 7874 4549"            /* ..objd...7stxtEI */
	$"4443 003D 0010 0101 0100 0000 0000 0225"            /* DC.=...........% */
	$"0000 005F 0000 0000 FFFF FFFF 0000 0000"            /* ..._....ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0120 0082"            /* ............. .Ç */
	$"0065 6E64 7365 6E64 2E"                             /* .endsend. */
};

data 'PPob' (11300, "Comp Operator Pane") {
	$"0002 6F62 6A64 0000 003C 7669 6577 0000"            /* ..objd...<view.. */
	$"0000 0276 0127 0001 0000 0000 0000 0000"            /* ...v.'.......... */
	$"0000 0000 0000 0000 FFFF FFFF 0000 0018"            /* ........ˇˇˇˇ.... */
	$"0000 002C 0000 0000 0000 0000 0000 0010"            /* ...,............ */
	$"0000 0010 0000 6265 6773 6F62 6A64 0000"            /* ......begsobjd.. */
	$"0064 7467 6278 434D 504F 012C 0091 0101"            /* .dtgbxCMPO.,.ë.. */
	$"0000 0000 0000 00A5 0000 0038 0000 0000"            /* .......•...8.... */
	$"FFFF FFFF 0000 0000 0000 0000 0000 0000"            /* ˇˇˇˇ............ */
	$"0000 0000 0000 0001 0000 0001 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 00A0"            /* ...............† */
	$"0085 1343 6F6D 7061 7269 736F 6E20 4F70"            /* .Ö.Comparison Op */
	$"6572 6174 6F72 6265 6773 6F62 6A64 0000"            /* eratorbegsobjd.. */
	$"003C 7462 6776 0000 0000 0120 007E 0101"            /* .<tbgv..... .~.. */
	$"0000 0000 0000 0006 0000 0010 0000 0000"            /* ................ */
	$"FFFF FFFF 0000 0000 0000 0000 0000 0000"            /* ˇˇˇˇ............ */
	$"0000 0000 0000 0001 0000 0001 0000 6265"            /* ..............be */
	$"6773 6F62 6A64 0000 003B 7374 7874 0000"            /* gsobjd...;stxt.. */
	$"0000 001E 0010 0101 0000 0000 0000 0004"            /* ................ */
	$"0000 0009 0000 0000 FFFF FFFF 0000 0000"            /* ...∆....ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0120 0085"            /* ............. .Ö */
	$"044E 616D 656F 626A 6400 0000 3B65 7478"            /* .Nameobjd...;etx */
	$"7400 0000 0100 F500 1601 0100 0000 0000"            /* t.....ı......... */
	$"0000 2600 0000 0400 0000 00FF FFFF FF45"            /* ..&........ˇˇˇˇE */
	$"644D 6400 0000 0000 0000 0000 0000 0001"            /* dMd............. */
	$"1000 8200 00FF 2003 6F62 6A64 0000 0039"            /* ..Ç..ˇ .objd...9 */
	$"7374 7874 0000 0000 0016 0010 0101 0000"            /* stxt............ */
	$"0000 0000 0004 0000 0023 0000 0000 FFFF"            /* .........#....ˇˇ */
	$"FFFF 0000 0000 0000 0000 0000 0000 0000"            /* ˇˇ.............. */
	$"0000 0120 0085 0249 446F 626A 6400 0000"            /* ... .Ö.IDobjd... */
	$"3B65 7478 7400 0000 0200 3200 1601 0100"            /* ;etxt.....2..... */
	$"0000 0000 0000 2500 0000 1E00 0000 00FF"            /* ......%........ˇ */
	$"FFFF FF45 644D 6400 0000 0000 0000 0000"            /* ˇˇˇEdMd......... */
	$"0000 0001 1000 8200 0004 2003 6F62 6A64"            /* ......Ç... .objd */
	$"0000 003E 7374 7874 0000 0000 0032 0012"            /* ...>stxt.....2.. */
	$"0101 0000 0000 0000 0000 0000 0041 0000"            /* .............A.. */
	$"0000 FFFF FFFF 0000 0000 0000 0000 0000"            /* ..ˇˇˇˇ.......... */
	$"0000 0000 0000 0120 0085 0743 6F6D 6D65"            /* ....... .Ö.Comme */
	$"6E74 6F62 6A64 0000 003B 6574 7874 0000"            /* ntobjd...;etxt.. */
	$"0003 00E8 0037 0101 0000 0000 0000 0032"            /* ...Ë.7.........2 */
	$"0000 003C 0000 0000 FFFF FFFF 4564 4D64"            /* ...<....ˇˇˇˇEdMd */
	$"0000 0000 0000 0000 0000 0000 0110 0082"            /* ...............Ç */
	$"0000 FF60 0365 6E64 7365 6E64 7365 6E64"            /* ..ˇ`.endsendsend */
	$"7365 6E64 2E"                                       /* send. */
};

data 'PPob' (11400, "Enumerations Pane") {
	$"0002 6F62 6A64 0000 003C 7669 6577 0000"            /* ..objd...<view.. */
	$"0000 0276 0127 0001 0000 0000 0000 0000"            /* ...v.'.......... */
	$"0000 0000 0000 0000 FFFF FFFF 0000 0018"            /* ........ˇˇˇˇ.... */
	$"0000 002C 0000 0000 0000 0000 0000 0010"            /* ...,............ */
	$"0000 0010 0000 6265 6773 6F62 6A64 0000"            /* ......begsobjd.. */
	$"0045 7374 7874 0000 0000 0055 0011 0101"            /* .Estxt.....U.... */
	$"0000 0000 0000 00B1 0000 0018 0000 0000"            /* .......±........ */
	$"FFFF FFFF 0000 0000 0000 0000 0000 0000"            /* ˇˇˇˇ............ */
	$"0000 0000 0120 0085 0E45 6E75 6D65 7261"            /* ..... .Ö.Enumera */
	$"7469 6F6E 2049 446F 626A 6400 0000 3B65"            /* tion IDobjd...;e */
	$"7478 7400 0000 0100 3200 1601 0100 0000"            /* txt.....2....... */
	$"0000 0001 0700 0000 1300 0000 00FF FFFF"            /* .............ˇˇˇ */
	$"FF45 644D 6400 0000 0000 0000 0000 0000"            /* ˇEdMd........... */
	$"0001 1000 8200 0004 2003 6F62 6A64 0000"            /* ....Ç... .objd.. */
	$"005B 7467 6278 454E 554D 012C 0091 0101"            /* .[tgbxENUM.,.ë.. */
	$"0000 0000 0000 00A5 0000 0038 0000 0000"            /* .......•...8.... */
	$"FFFF FFFF 0000 0000 0000 0000 0000 0000"            /* ˇˇˇˇ............ */
	$"0000 0000 0000 0001 0000 0001 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 00A0"            /* ...............† */
	$"0085 0A45 6E75 6D65 7261 746F 7262 6567"            /* .Ö¬Enumeratorbeg */
	$"736F 626A 6400 0000 3C74 6267 7600 0000"            /* sobjd...<tbgv... */
	$"0001 2200 7B01 0100 0000 0000 0000 0400"            /* ..".{........... */
	$"0000 1200 0000 00FF FFFF FF00 0000 0000"            /* .......ˇˇˇˇ..... */
	$"0000 0000 0000 0000 0000 0000 0000 0100"            /* ................ */
	$"0000 0100 0062 6567 736F 626A 6400 0000"            /* .....begsobjd... */
	$"3B73 7478 7400 0000 0000 1E00 1001 0100"            /* ;stxt........... */
	$"0000 0000 0000 0600 0000 0700 0000 00FF"            /* ...............ˇ */
	$"FFFF FF00 0000 0000 0000 0000 0000 0000"            /* ˇˇˇ............. */
	$"0000 0001 2000 8504 4E61 6D65 6F62 6A64"            /* .... .Ö.Nameobjd */
	$"0000 003B 6574 7874 0000 0002 00F5 0016"            /* ...;etxt.....ı.. */
	$"0101 0000 0000 0000 0028 0000 0002 0000"            /* .........(...... */
	$"0000 FFFF FFFF 4564 4D64 0000 0000 0000"            /* ..ˇˇˇˇEdMd...... */
	$"0000 0000 0000 0110 0082 0000 FF20 036F"            /* .........Ç..ˇ .o */
	$"626A 6400 0000 3B73 7478 7400 0000 0000"            /* bjd...;stxt..... */
	$"1B00 1001 0100 0000 0000 0000 0600 0000"            /* ................ */
	$"2100 0000 00FF FFFF FF00 0000 0000 0000"            /* !....ˇˇˇˇ....... */
	$"0000 0000 0000 0000 0001 2000 8504 5479"            /* .......... .Ö.Ty */
	$"7065 6F62 6A64 0000 003B 6574 7874 0000"            /* peobjd...;etxt.. */
	$"0003 0032 0016 0101 0000 0000 0000 0028"            /* ...2...........( */
	$"0000 001C 0000 0000 FFFF FFFF 4564 4D64"            /* ........ˇˇˇˇEdMd */
	$"0000 0000 0000 0000 0000 0000 0110 0082"            /* ...............Ç */
	$"0000 0420 036F 626A 6400 0000 3E73 7478"            /* ... .objd...>stx */
	$"7400 0000 0000 3200 1201 0100 0000 0000"            /* t.....2......... */
	$"0000 0600 0000 4100 0000 00FF FFFF FF00"            /* ......A....ˇˇˇˇ. */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"2000 8507 436F 6D6D 656E 746F 626A 6400"            /*  .Ö.Commentobjd. */
	$"0000 3B65 7478 7400 0000 0400 E200 3701"            /* ..;etxt.....‚.7. */
	$"0100 0000 0000 0000 3A00 0000 3C00 0000"            /* ........:...<... */
	$"00FF FFFF FF45 644D 6400 0000 0000 0000"            /* .ˇˇˇˇEdMd....... */
	$"0000 0000 0001 1000 8200 00FF 2003 656E"            /* ........Ç..ˇ .en */
	$"6473 656E 6473 6F62 6A64 0000 0036 736C"            /* dsendsobjd...6sl */
	$"6964 4E53 4C49 00EA 0017 0001 0000 0000"            /* idNSLI.Í........ */
	$"0000 00A6 0000 00CD 0000 0000 FFFF FFFF"            /* ...¶...Õ....ˇˇˇˇ */
	$"4E53 4C49 0000 0000 0000 0000 0000 0000"            /* NSLI............ */
	$"0031 0004 6F62 6A64 0000 0037 7374 7874"            /* .1..objd...7stxt */
	$"4E49 4443 003D 0010 0101 0100 0000 0000"            /* NIDC.=.......... */
	$"0195 0000 00D0 0000 0000 FFFF FFFF 0000"            /* .ï...–....ˇˇˇˇ.. */
	$"0000 0000 0000 0000 0000 0000 0000 0120"            /* ...............  */
	$"0082 0065 6E64 7365 6E64 2E"                        /* .Ç.endsend. */
};

data 'PPob' (10610, "Icns Editor Window") {
	$"0002 646F 706C 4661 6D56 6F62 6A64 0000"            /* ..doplFamVobjd.. */
	$"001C 7769 6E64 2972 0002 1862 0000 0190"            /* ..wind)r...b...ê */
	$"0190 FFFF FFFF 023A 0190 0000 0000 6265"            /* .êˇˇˇˇ.:.ê....be */
	$"6773 6F62 6A64 0000 0051 706C 6364 0000"            /* gsobjd...Qplcd.. */
	$"0000 0236 0186 0101 0101 0101 0000 0000"            /* ...6.Ü.......... */
	$"0000 0000 0000 0000 FFFF FFFF 0000 0000"            /* ........ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"0000 0001 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0150 0000 0062 6567 736F"            /* .......P...begso */
	$"626A 6400 0000 4A44 6362 6274 4C41 5300"            /* bjd...JDcbbtLAS. */
	$"1800 1801 0100 0000 0000 0000 0F00 0000"            /* ................ */
	$"3100 0000 00FF FFFF FF74 4C41 5300 0000"            /* 1....ˇˇˇˇtLAS... */
	$"0000 0001 0100 0023 2800 2100 0000 0000"            /* .......#(.!..... */
	$"0000 0000 0000 0000 0000 0000 0044 436C"            /* .............DCl */
	$"6B6F 626A 6400 0000 4A44 6362 6274 5345"            /* kobjd...JDcbbtSE */
	$"4C00 1800 1801 0100 0000 0000 0000 2900"            /* L.............). */
	$"0000 3100 0000 00FF FFFF FF74 5345 4C00"            /* ..1....ˇˇˇˇtSEL. */
	$"0000 0000 0001 0100 0023 2900 2100 0000"            /* .........#).!... */
	$"0000 0000 0000 0000 0000 0000 0000 0044"            /* ...............D */
	$"436C 6B6F 626A 6400 0000 4662 6275 7474"            /* Clkobjd...Fbbutt */
	$"5458 5400 1800 1801 0100 0000 0000 0000"            /* TXT............. */
	$"0F00 0000 4B00 0000 00FF FFFF FF74 5458"            /* ....K....ˇˇˇˇtTX */
	$"5400 0000 0000 0001 0100 0023 2A00 2100"            /* T..........#*.!. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"006F 626A 6400 0000 4662 6275 7474 5045"            /* .objd...FbbuttPE */
	$"4E00 1800 1801 0100 0000 0000 0000 2900"            /* N.............). */
	$"0000 4B00 0000 00FF FFFF FF74 5045 4E00"            /* ..K....ˇˇˇˇtPEN. */
	$"0000 0000 0001 0100 0023 2B00 2100 0000"            /* .........#+.!... */
	$"0000 0000 0000 0000 0000 0000 0000 006F"            /* ...............o */
	$"626A 6400 0000 4A44 6362 6274 4552 4100"            /* bjd...JDcbbtERA. */
	$"1800 1801 0100 0000 0000 0000 0F00 0000"            /* ................ */
	$"6500 0000 00FF FFFF FF74 4552 4100 0000"            /* e....ˇˇˇˇtERA... */
	$"0000 0001 0100 0023 2C00 2100 0000 0000"            /* .......#,.!..... */
	$"0000 0000 0000 0000 0000 0000 0044 436C"            /* .............DCl */
	$"6B6F 626A 6400 0000 4662 6275 7474 4255"            /* kobjd...FbbuttBU */
	$"4300 1800 1801 0100 0000 0000 0000 2900"            /* C.............). */
	$"0000 6500 0000 00FF FFFF FF74 4255 4300"            /* ..e....ˇˇˇˇtBUC. */
	$"0000 0000 0001 0100 0023 2D00 2100 0000"            /* .........#-.!... */
	$"0000 0000 0000 0000 0000 0000 0000 006F"            /* ...............o */
	$"626A 6400 0000 4662 6275 7474 4452 4F00"            /* bjd...FbbuttDRO. */
	$"1800 1801 0100 0000 0000 0000 0F00 0000"            /* ................ */
	$"7F00 0000 00FF FFFF FF74 4452 4F00 0000"            /* .....ˇˇˇˇtDRO... */
	$"0000 0001 0100 0023 2E00 2100 0000 0000"            /* .......#..!..... */
	$"0000 0000 0000 0000 0000 0000 006F 626A"            /* .............obj */
	$"6400 0000 4662 6275 7474 4C49 4E00 1800"            /* d...FbbuttLIN... */
	$"1801 0100 0000 0000 0000 2900 0000 7F00"            /* ..........)..... */
	$"0000 00FF FFFF FF74 4C49 4E00 0000 0000"            /* ...ˇˇˇˇtLIN..... */
	$"0001 0100 0023 2F00 2100 0000 0000 0000"            /* .....#/.!....... */
	$"0000 0000 0000 0000 0000 006F 626A 6400"            /* ...........objd. */
	$"0000 4662 6275 7474 5245 4300 1800 1801"            /* ..FbbuttREC..... */
	$"0100 0000 0000 0000 0F00 0000 9900 0000"            /* ............ô... */
	$"00FF FFFF FF74 5245 4300 0000 0000 0001"            /* .ˇˇˇˇtREC....... */
	$"0100 0023 3100 2100 0000 0000 0000 0000"            /* ...#1.!......... */
	$"0000 0000 0000 0000 006F 626A 6400 0000"            /* .........objd... */
	$"4662 6275 7474 4652 4300 1800 1801 0100"            /* FbbuttFRC....... */
	$"0000 0000 0000 2900 0000 9900 0000 00FF"            /* ......)...ô....ˇ */
	$"FFFF FF74 4652 4300 0000 0000 0001 0100"            /* ˇˇˇtFRC......... */
	$"0023 3000 2100 0000 0000 0000 0000 0000"            /* .#0.!........... */
	$"0000 0000 0000 006F 626A 6400 0000 4662"            /* .......objd...Fb */
	$"6275 7474 5252 4300 1800 1801 0100 0000"            /* buttRRC......... */
	$"0000 0000 0F00 0000 B300 0000 00FF FFFF"            /* ........≥....ˇˇˇ */
	$"FF74 5252 4300 0000 0000 0001 0100 0023"            /* ˇtRRC..........# */
	$"3300 2100 0000 0000 0000 0000 0000 0000"            /* 3.!............. */
	$"0000 0000 006F 626A 6400 0000 4662 6275"            /* .....objd...Fbbu */
	$"7474 4652 5200 1800 1801 0100 0000 0000"            /* ttFRR........... */
	$"0000 2900 0000 B300 0000 00FF FFFF FF74"            /* ..)...≥....ˇˇˇˇt */
	$"4652 5200 0000 0000 0001 0100 0023 3200"            /* FRR..........#2. */
	$"2100 0000 0000 0000 0000 0000 0000 0000"            /* !............... */
	$"0000 006F 626A 6400 0000 4662 6275 7474"            /* ...objd...Fbbutt */
	$"4F56 4C00 1800 1801 0100 0000 0000 0000"            /* OVL............. */
	$"0F00 0000 CD00 0000 00FF FFFF FF74 4F56"            /* ....Õ....ˇˇˇˇtOV */
	$"4C00 0000 0000 0001 0100 0023 3500 2100"            /* L..........#5.!. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"006F 626A 6400 0000 4662 6275 7474 464F"            /* .objd...FbbuttFO */
	$"5600 1800 1801 0100 0000 0000 0000 2900"            /* V.............). */
	$"0000 CD00 0000 00FF FFFF FF74 464F 5600"            /* ..Õ....ˇˇˇˇtFOV. */
	$"0000 0000 0001 0100 0023 3400 2100 0000"            /* .........#4.!... */
	$"0000 0000 0000 0000 0000 0000 0000 0064"            /* ...............d */
	$"6F70 6C50 6174 506F 626A 6400 0000 4662"            /* oplPatPobjd...Fb */
	$"6275 7474 5041 5400 3200 1201 0100 0000"            /* buttPAT.2....... */
	$"0000 0000 0F00 0000 F100 0003 E8FF FFFF"            /* ........Ò...Ëˇˇˇ */
	$"FF74 5041 5400 0000 0000 0000 0000 0000"            /* ˇtPAT........... */
	$"0000 2100 0000 0000 0000 0000 0000 0000"            /* ..!............. */
	$"0000 0000 006F 626A 6400 0000 4E43 6F6C"            /* .....objd...NCol */
	$"5074 4243 4C00 2800 1001 0101 0100 0000"            /* PtBCL.(......... */
	$"0000 1B00 0001 1A00 FFFF FFFF FFFF FF74"            /* ........ˇˇˇˇˇˇˇt */
	$"4243 4C00 0000 0000 0000 0000 0000 0000"            /* BCL............. */
	$"2100 0000 0000 0000 0000 0000 0000 0000"            /* !............... */
	$"0000 00FF FFFF FFFF FF01 006F 626A 6400"            /* ...ˇˇˇˇˇˇ..objd. */
	$"0000 4E43 6F6C 5074 4643 4C00 2800 1001"            /* ..NColPtFCL.(... */
	$"0101 0100 0000 0000 0F00 0001 0D00 0000"            /* ................ */
	$"00FF FFFF FF74 4643 4C00 0000 0000 0000"            /* .ˇˇˇˇtFCL....... */
	$"0000 0000 0000 2100 0000 0000 0000 0000"            /* ......!......... */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"006F 626A 6400 0000 5174 6762 7845 4E43"            /* .objd...QtgbxENC */
	$"4C01 5A01 5A01 0101 0100 0000 0000 5000"            /* L.Z.Z.........P. */
	$"0000 2500 0000 00FF FFFF FF00 0000 0000"            /* ..%....ˇˇˇˇ..... */
	$"0000 0000 0000 0000 0000 0000 0000 0100"            /* ................ */
	$"0000 0100 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 A000 0000 6265 6773 646F"            /* ......†...begsdo */
	$"706C 4943 4E56 6F62 6A64 0000 003C 7669"            /* plICNVobjd...<vi */
	$"6577 436E 7473 0152 0152 0101 0101 0101"            /* ewCnts.R.R...... */
	$"0000 0004 0000 0004 0000 0000 FFFF FFFF"            /* ............ˇˇˇˇ */
	$"0000 0000 0000 0004 0000 0000 0000 0000"            /* ................ */
	$"0000 0014 0000 0014 0001 656E 6473 6F62"            /* ..........endsob */
	$"6A64 0000 003C 7669 6577 5341 4D50 0078"            /* jd...<viewSAMP.x */
	$"0140 0101 0000 0000 0000 01B3 0000 0027"            /* .@.........≥...' */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0000 0001 0000 0001"            /* ................ */
	$"0000 6265 6773 646F 706C 4454 5677 6F62"            /* ..begsdoplDTVwob */
	$"6A64 0000 003C 7669 6577 6963 6E73 002C"            /* jd...<viewicns., */
	$"0038 0101 0000 0000 0000 0008 0000 0009"            /* .8.............∆ */
	$"0000 0002 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0000 0001 0000 0001"            /* ................ */
	$"0000 656E 6473 6F62 6A64 0000 0037 7374"            /* ..endsobjd...7st */
	$"7874 434F 4F52 003C 0010 0101 0000 0000"            /* xtCOOR.<........ */
	$"0000 000A 0000 0174 0000 0000 FFFF FFFF"            /* ...¬...t....ˇˇˇˇ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0120 0000 006F 626A 6400 0000 4170 6F70"            /* . ...objd...Apop */
	$"6249 4353 5400 BE00 1401 0101 0100 0000"            /* bICST.æ......... */
	$"0000 5100 0000 0A00 0000 00FF FFFF FF49"            /* ..Q...¬....ˇˇˇˇI */
	$"4353 5400 0000 0000 0001 3100 00FF FF01"            /* CST.......1..ˇˇ. */
	$"9000 8504 5479 7065 0000 0000 0001 6F62"            /* ê.Ö.Type......ob */
	$"6A64 0000 004A 6368 6278 494E 434C 0094"            /* jd...JchbxINCL.î */
	$"0010 0101 0000 0000 0000 0135 0000 000B"            /* ...........5.... */
	$"0000 0000 FFFF FFFF 494E 434C 0000 0000"            /* ....ˇˇˇˇINCL.... */
	$"0000 0000 0000 0001 0001 008B 1349 6E63"            /* ...........ã.Inc */
	$"6C75 6465 2069 6E20 7265 736F 7572 6365"            /* lude in resource */
	$"656E 6473 6F62 6A64 0000 0051 706C 6364"            /* endsobjd...Qplcd */
	$"464F 4F54 0236 0028 0101 0100 0101 0000"            /* FOOT.6.(........ */
	$"0000 0000 0186 0000 0000 FFFF FFFF 0000"            /* .....Ü....ˇˇˇˇ.. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0001 0000 0001 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 00E0 0000 0062 6567"            /* .........‡...beg */
	$"736F 626A 6400 0000 3C70 7573 6856 6C69"            /* sobjd...<pushVli */
	$"6400 4100 1401 0100 0001 0100 0001 E900"            /* d.A...........È. */
	$"0000 0900 0000 00FF FFFF FF00 0003 8400"            /* ..∆....ˇˇˇˇ...Ñ. */
	$"0000 0000 0000 0000 0000 0001 7000 0004"            /* ............p... */
	$"5361 7665 016F 626A 6400 0000 3E70 7573"            /* Save.objd...>pus */
	$"6843 6E63 6C00 4100 1401 0100 0001 0100"            /* hCncl.A......... */
	$"0001 9D00 0000 0900 0000 00FF FFFF FF00"            /* ..ù...∆....ˇˇˇˇ. */
	$"0003 8500 0000 0000 0000 0000 0000 0001"            /* ..Ö............. */
	$"7000 0006 4361 6E63 656C 006F 626A 6400"            /* p...Cancel.objd. */
	$"0000 3E70 7573 6852 7672 7400 4100 1401"            /* ..>pushRvrt.A... */
	$"0101 0000 0100 0000 1C00 0000 0900 0000"            /* ............∆... */
	$"00FF FFFF FF00 0000 0700 0000 0000 0000"            /* .ˇˇˇˇ........... */
	$"0000 0000 0001 7000 0006 5265 7665 7274"            /* ......p...Revert */
	$"006F 626A 6400 0000 2469 636E 704C 6F63"            /* .objd...$icnpLoc */
	$"6B00 1000 1001 0101 0000 0100 0000 0600"            /* k............... */
	$"0000 0B00 0000 00FF FFFF FF00 0065 6E64"            /* .......ˇˇˇˇ..end */
	$"7365 6E64 7365 6E64 2E"                             /* sendsend. */
};

data 'PPob' (10300, "MENU Editor Window") {
	$"0002 646F 706C 4D4E 5557 6F62 6A64 0000"            /* ..doplMNUWobjd.. */
	$"001C 7769 6E64 283C 0002 1862 0000 017C"            /* ..wind(<...b...| */
	$"00C8 FFFF FFFF FFFF FFFF 0000 0000 6265"            /* .»ˇˇˇˇˇˇˇˇ....be */
	$"6773 6F62 6A64 0000 0049 7363 6C76 5363"            /* gsobjd...IsclvSc */
	$"726C 00E1 01A8 0101 0101 0001 0000 0000"            /* rl.·.®.......... */
	$"0000 001C 0000 0000 FFFF FFFF 0000 0001"            /* ........ˇˇˇˇ.... */
	$"0000 0001 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 FFFF 000F 0000 0000 436E"            /* ......ˇˇ......Cn */
	$"7473 0162 6567 7364 6F70 6C44 6E44 546F"            /* ts.begsdoplDnDTo */
	$"626A 6400 0000 5074 6162 6C43 6E74 7300"            /* bjd...PtablCnts. */
	$"CD01 A401 0101 0101 0100 0000 0200 0000"            /* Õ.§............. */
	$"0200 0000 00FF FFFF FF00 0000 0000 0000"            /* .....ˇˇˇˇ....... */
	$"0000 0000 0000 0000 0000 0000 0100 0000"            /* ................ */
	$"0E00 0000 0000 0000 0000 0000 0000 0E00"            /* ................ */
	$"0000 C800 0001 0065 6E64 736F 626A 6400"            /* ..»....endsobjd. */
	$"0000 5170 6C63 6400 0000 0001 2C01 AA01"            /* ..Qplcd.....,.™. */
	$"0100 0101 0100 0000 E100 0000 1B00 0000"            /* ........·....... */
	$"00FF FFFF FF00 0000 0000 0000 0000 0000"            /* .ˇˇˇˇ........... */
	$"0000 0000 0000 0000 0100 0000 0100 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"E000 0000 6265 6773 6F62 6A64 0000 0046"            /* ‡...begsobjd...F */
	$"706F 7062 0000 0028 00DC 0014 0101 0101"            /* popb...(.‹...... */
	$"0000 0000 0028 0000 000E 0000 0000 FFFF"            /* .....(........ˇˇ */
	$"FFFF 0000 2864 0000 0000 0000 0103 0000"            /* ˇˇ..(d.......... */
	$"FFFF 0190 008B 0950 726F 7065 7274 793A"            /* ˇˇ.ê.ã∆Property: */
	$"0000 0000 0001 6F62 6A64 0000 003C 7462"            /* ......objd...<tb */
	$"6776 0000 0032 011F 014C 0101 0000 0000"            /* gv...2...L...... */
	$"0000 0006 0000 0026 0000 0000 FFFF FFFF"            /* .......&....ˇˇˇˇ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0001 0000 0001 0000 6265 6773 6F62"            /* ..........begsob */
	$"6A64 0000 0040 7374 7874 0000 0000 0038"            /* jd...@stxt.....8 */
	$"0010 0101 0000 0000 0000 0019 0000 000C"            /* ................ */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0120 008B 094D 656E"            /* ......... .ã∆Men */
	$"7520 6974 656D 6F62 6A64 0000 003B 6574"            /* u itemobjd...;et */
	$"7874 0000 0005 00C3 0016 0101 0000 0000"            /* xt.....√........ */
	$"0000 0054 0000 0008 0000 0000 FFFF FFFF"            /* ...T........ˇˇˇˇ */
	$"0000 2841 0000 0000 0000 0000 0000 0000"            /* ..(A............ */
	$"0110 0082 0000 FF20 036F 626A 6400 0000"            /* ...Ç..ˇ .objd... */
	$"4363 6862 7800 0000 0600 5A00 1201 0100"            /* Cchbx.....Z..... */
	$"0000 0000 0000 BD00 0000 2500 0000 00FF"            /* ......Ω...%....ˇ */
	$"FFFF FF00 0028 4200 0000 0000 0000 0000"            /* ˇˇˇ..(B......... */
	$"0000 0201 7100 8B0C 4974 656D 2065 6E61"            /* ....q.ã.Item ena */
	$"626C 6564 6F62 6A64 0000 0044 7374 7874"            /* bledobjd...Dstxt */
	$"0000 0011 004E 0010 0101 0000 0000 0000"            /* .....N.......... */
	$"000C 0000 0046 0000 0000 FFFF FFFF 0000"            /* .....F....ˇˇˇˇ.. */
	$"0000 0000 0000 0000 0000 0000 0000 0120"            /* ...............  */
	$"008B 0D49 636F 6E20 4944 202D 2032 3536"            /* .ã.Icon ID - 256 */
	$"6F62 6A64 0000 003C 6574 7874 0000 0007"            /* objd...<etxt.... */
	$"0032 0016 0101 0000 0000 0000 005B 0000"            /* .2...........[.. */
	$"0042 0000 0000 FFFF FFFF 0000 2843 0000"            /* .B....ˇˇˇˇ..(C.. */
	$"0000 0000 0000 0000 0000 0110 0082 0130"            /* .............Ç.0 */
	$"0006 2004 6F62 6A64 0000 0043 7374 7874"            /* .. .objd...Cstxt */
	$"0000 0012 004C 0010 0101 0000 0000 0000"            /* .....L.......... */
	$"000B 0000 0061 0000 0000 FFFF FFFF 0000"            /* .....a....ˇˇˇˇ.. */
	$"0000 0000 0000 0000 0000 0000 0000 0120"            /* ...............  */
	$"008B 0C53 686F 7274 6375 7420 6B65 796F"            /* .ã.Shortcut keyo */
	$"626A 6400 0000 3B65 7478 7400 0000 0800"            /* bjd...;etxt..... */
	$"3200 1601 0100 0000 0000 0000 5B00 0000"            /* 2...........[... */
	$"5D00 0000 00FF FFFF FF00 0028 4400 0000"            /* ]....ˇˇˇˇ..(D... */
	$"0000 0000 0000 0000 0001 1000 8200 0003"            /* ............Ç... */
	$"2001 6F62 6A64 0000 0040 7374 7874 0000"            /*  .objd...@stxt.. */
	$"0013 003E 0010 0101 0000 0000 0000 009A"            /* ...>...........ö */
	$"0000 0046 0000 0000 FFFF FFFF 0000 0000"            /* ...F....ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0120 008B"            /* ............. .ã */
	$"094D 6172 6B20 6368 6172 6F62 6A64 0000"            /* ∆Mark charobjd.. */
	$"003B 6574 7874 0000 0009 0032 0016 0101"            /* .;etxt...∆.2.... */
	$"0000 0000 0000 00D9 0000 0042 0000 0000"            /* .......Ÿ...B.... */
	$"FFFF FFFF 0000 2845 0000 0000 0000 0000"            /* ˇˇˇˇ..(E........ */
	$"0000 0000 0110 0082 0000 0620 046F 626A"            /* .......Ç... .obj */
	$"6400 0000 5A74 6762 7800 0000 0000 BD00"            /* d...Ztgbx.....Ω. */
	$"4601 0100 0000 0000 0000 3200 0000 A400"            /* F.........2...§. */
	$"0000 00FF FFFF FF00 0000 0000 0000 0000"            /* ...ˇˇˇˇ......... */
	$"0000 0000 0000 0000 0000 0100 0000 0100"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 A000 8509 4D6F 6469 6669 6572 7362"            /* ..†.Ö∆Modifiersb */
	$"6567 736F 626A 6400 0000 3E63 6862 7800"            /* egsobjd...>chbx. */
	$"0000 1400 4600 1201 0100 0000 0000 0000"            /* ....F........... */
	$"0E00 0000 1500 0000 00FF FFFF FF00 0028"            /* .........ˇˇˇˇ..( */
	$"5000 0000 0100 0000 0000 0000 0201 7100"            /* P.............q. */
	$"8B07 436F 6D6D 616E 646F 626A 6400 0000"            /* ã.Commandobjd... */
	$"3C63 6862 7800 0000 1500 4600 1201 0100"            /* <chbx.....F..... */
	$"0000 0000 0000 0E00 0000 2A00 0000 00FF"            /* ..........*....ˇ */
	$"FFFF FF00 0028 5100 0000 0000 0000 0000"            /* ˇˇˇ..(Q......... */
	$"0000 0201 7100 8B05 5368 6966 746F 626A"            /* ....q.ã.Shiftobj */
	$"6400 0000 3D63 6862 7800 0000 1600 4600"            /* d...=chbx.....F. */
	$"1201 0100 0000 0000 0000 6A00 0000 1500"            /* ..........j..... */
	$"0000 00FF FFFF FF00 0028 5200 0000 0000"            /* ...ˇˇˇˇ..(R..... */
	$"0000 0000 0000 0201 7100 8B06 4F70 7469"            /* ........q.ã.Opti */
	$"6F6E 6F62 6A64 0000 003E 6368 6278 0000"            /* onobjd...>chbx.. */
	$"0017 0046 0012 0101 0000 0000 0000 006A"            /* ...F...........j */
	$"0000 0029 0000 0000 FFFF FFFF 0000 2853"            /* ...)....ˇˇˇˇ..(S */
	$"0000 0000 0000 0000 0000 0002 0171 008B"            /* .............q.ã */
	$"0743 6F6E 7472 6F6C 656E 6473 6F62 6A64"            /* .Controlendsobjd */
	$"0000 0044 7374 7874 0000 0000 004E 0010"            /* ...Dstxt.....N.. */
	$"0101 0000 0000 0000 0008 0000 0102 0000"            /* ................ */
	$"0000 FFFF FFFF 0000 0000 0000 0000 0000"            /* ..ˇˇˇˇ.......... */
	$"0000 0000 0000 0120 008B 0D54 6578 7420"            /* ....... .ã.Text  */
	$"656E 636F 6469 6E67 6F62 6A64 0000 004B"            /* encodingobjd...K */
	$"506F 7046 0000 001E 0032 0016 0101 0000"            /* PopF.....2...... */
	$"0000 0000 0058 0000 00FD 0000 0000 FFFF"            /* .....X...˝....ˇˇ */
	$"FFFF 0000 285A 0000 0000 0000 0000 0000"            /* ˇˇ..(Z.......... */
	$"0000 0110 0082 0130 0006 2004 5363 7270"            /* .....Ç.0.. .Scrp */
	$"0643 0007 556E 6B6E 6F77 6E6F 626A 6400"            /* .C..Unknownobjd. */
	$"0000 3C73 7478 7400 0000 0000 2900 1101"            /* ..<stxt.....)... */
	$"0100 0000 0000 0000 0800 0001 1B00 0000"            /* ................ */
	$"00FF FFFF FF00 0000 0000 0000 0000 0000"            /* .ˇˇˇˇ........... */
	$"0000 0000 0001 2000 8B05 476C 7970 686F"            /* ...... .ã.Glypho */
	$"626A 6400 0000 5050 6F70 4600 0000 2200"            /* bjd...PPopF...". */
	$"3200 1601 0100 0000 0000 0000 5800 0001"            /* 2...........X... */
	$"1600 0000 00FF FFFF FF00 0028 5E00 0000"            /* .....ˇˇˇˇ..(^... */
	$"0000 0000 0000 0000 0001 1000 8200 0003"            /* ............Ç... */
	$"2001 476C 7966 0644 000D 556E 6B6E 6F77"            /*  .Glyf.D..Unknow */
	$"6E20 676C 7970 686F 626A 6400 0000 3E73"            /* n glyphobjd...>s */
	$"7478 7400 0000 0000 3700 1001 0100 0000"            /* txt.....7....... */
	$"0000 0000 0800 0001 3400 0000 00FF FFFF"            /* ........4....ˇˇˇ */
	$"FF00 0000 0000 0000 0000 0000 0000 0000"            /* ˇ............... */
	$"0001 2000 8B07 466F 6E74 2049 446F 626A"            /* .. .ã.Font IDobj */
	$"6400 0000 3C65 7478 7400 0000 2100 3200"            /* d...<etxt...!.2. */
	$"1601 0100 0000 0000 0000 5800 0001 2F00"            /* ..........X.../. */
	$"0000 00FF FFFF FF00 0028 5D00 0000 0000"            /* ...ˇˇˇˇ..(]..... */
	$"0000 0000 0000 0001 1000 8201 3000 0420"            /* ..........Ç.0..  */
	$"016F 626A 6400 0000 3F73 7478 7400 0000"            /* .objd...?stxt... */
	$"0000 3200 1001 0100 0000 0000 0000 B000"            /* ..2...........∞. */
	$"0001 0200 0000 00FF FFFF FF00 0000 0000"            /* .......ˇˇˇˇ..... */
	$"0000 0000 0000 0000 0000 0001 2000 8B08"            /* ............ .ã. */
	$"5265 6663 6F6E 2031 6F62 6A64 0000 003C"            /* Refcon 1objd...< */
	$"6574 7874 0000 001F 0037 0016 0101 0000"            /* etxt.....7...... */
	$"0000 0000 00E1 0000 00FD 0000 0000 FFFF"            /* .....·...˝....ˇˇ */
	$"FFFF 0000 285B 0000 0000 0000 0000 0000"            /* ˇˇ..([.......... */
	$"0000 0110 0082 0130 000B 2004 6F62 6A64"            /* .....Ç.0.. .objd */
	$"0000 003F 7374 7874 0000 0000 0032 0010"            /* ...?stxt.....2.. */
	$"0101 0000 0000 0000 00B0 0000 011B 0000"            /* .........∞...... */
	$"0000 FFFF FFFF 0000 0000 0000 0000 0000"            /* ..ˇˇˇˇ.......... */
	$"0000 0000 0000 0120 008B 0852 6566 636F"            /* ....... .ã.Refco */
	$"6E20 326F 626A 6400 0000 3C65 7478 7400"            /* n 2objd...<etxt. */
	$"0000 2000 3700 1601 0100 0000 0000 0000"            /* .. .7........... */
	$"E100 0001 1600 0000 00FF FFFF FF00 0028"            /* ·........ˇˇˇˇ..( */
	$"5C00 0000 0000 0000 0000 0000 0001 1000"            /* \............... */
	$"8201 3000 0B20 046F 626A 6400 0000 3D70"            /* Ç.0.. .objd...=p */
	$"6F70 6200 0000 2900 6E00 1401 0101 0100"            /* opb...).n....... */
	$"0000 0000 5900 0000 8000 0000 00FF FFFF"            /* ....Y...Ä....ˇˇˇ */
	$"FF00 0028 6500 0000 0000 0001 0200 00FF"            /* ˇ..(e..........ˇ */
	$"FF01 9000 8500 0000 0000 0001 646F 706C"            /* ˇ.ê.Ö.......dopl */
	$"4B47 4278 6F62 6A64 0000 0029 7474 7862"            /* KGBxobjd...)ttxb */
	$"0000 0023 0018 0018 0101 0000 0000 0000"            /* ...#............ */
	$"003C 0000 0118 0000 0000 FFFF FFFF 0000"            /* .<........ˇˇˇˇ.. */
	$"0000 6701 0165 6E64 736F 626A 6400 0000"            /* ..g..endsobjd... */
	$"3970 7573 684D 696E 7300 1F00 1001 0100"            /* 9pushMins....... */
	$"0000 0000 0000 6900 0001 8600 0000 00FF"            /* ......i...Ü....ˇ */
	$"FFFF FF4D 696E 7300 0000 0000 0000 0000"            /* ˇˇˇMins......... */
	$"0000 0001 7000 0001 2D00 6F62 6A64 0000"            /* ....p...-.objd.. */
	$"0039 7075 7368 506C 7573 001E 0010 0101"            /* .9pushPlus...... */
	$"0000 0000 0000 00A0 0000 0186 0000 0000"            /* .......†...Ü.... */
	$"FFFF FFFF 506C 7573 0000 0000 0000 0000"            /* ˇˇˇˇPlus........ */
	$"0000 0000 0170 0000 012B 0065 6E64 736F"            /* .....p...+.endso */
	$"626A 6400 0000 5177 696E 6800 0000 0002"            /* bjd...Qwinh..... */
	$"0F00 1C01 0101 0101 00FF FFFF FF00 0000"            /* .........ˇˇˇˇ... */
	$"0000 0000 00FF FFFF FF00 0000 0000 0000"            /* .....ˇˇˇˇ....... */
	$"0000 0000 0000 0000 0000 0000 0100 0000"            /* ................ */
	$"0100 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0001 5000 0000 6265 6773 6F62 6A64"            /* ....P...begsobjd */
	$"0000 003C 7462 6776 0000 0000 0124 0019"            /* ...<tbgv.....$.. */
	$"0101 0000 0000 0000 00E9 0000 0001 0000"            /* .........È...... */
	$"0000 FFFF FFFF 0000 0000 0000 0000 0000"            /* ..ˇˇˇˇ.......... */
	$"0000 0000 0000 0000 0001 0000 0001 0000"            /* ................ */
	$"6265 6773 6F62 6A64 0000 003E 6368 6278"            /* begsobjd...>chbx */
	$"0000 0004 0041 0012 0101 0000 0000 0000"            /* .....A.......... */
	$"00DE 0000 0004 0000 0000 FFFF FFFF 0000"            /* .ﬁ........ˇˇˇˇ.. */
	$"2840 0000 0001 0000 0000 0000 0002 0171"            /* (@.............q */
	$"008B 0745 6E61 626C 6564 6F62 6A64 0000"            /* .ã.Enabledobjd.. */
	$"003E 7374 7874 0000 0000 002D 0010 0101"            /* .>stxt.....-.... */
	$"0000 0000 0000 0005 0000 0006 0000 0000"            /* ................ */
	$"FFFF FFFF 0000 0000 0000 0000 0000 0000"            /* ˇˇˇˇ............ */
	$"0000 0000 0120 0085 074D 656E 7520 4944"            /* ..... .Ö.Menu ID */
	$"6F62 6A64 0000 003B 6574 7874 0000 0002"            /* objd...;etxt.... */
	$"0032 0016 0101 0000 0000 0000 0031 0000"            /* .2...........1.. */
	$"0002 0000 0000 FFFF FFFF 0000 283E 0000"            /* ......ˇˇˇˇ..(>.. */
	$"0000 0000 0000 0000 0000 0110 0082 0000"            /* .............Ç.. */
	$"0620 016F 626A 6400 0000 3E73 7478 7400"            /* . .objd...>stxt. */
	$"0000 0000 2D00 1001 0100 0000 0000 0000"            /* ....-........... */
	$"7300 0000 0600 0000 00FF FFFF FF00 0000"            /* s........ˇˇˇˇ... */
	$"0000 0000 0000 0000 0000 0000 0001 2000"            /* .............. . */
	$"8507 4D44 4546 2049 446F 626A 6400 0000"            /* Ö.MDEF IDobjd... */
	$"3B65 7478 7400 0000 0300 3200 1601 0100"            /* ;etxt.....2..... */
	$"0000 0000 0000 A000 0000 0200 0000 00FF"            /* ......†........ˇ */
	$"FFFF FF00 0028 3F00 0000 0000 0000 0000"            /* ˇˇˇ..(?......... */
	$"0000 0001 1000 8200 0006 2003 656E 6473"            /* ......Ç... .ends */
	$"6F62 6A64 0000 003E 7069 6374 0000 0000"            /* objd...>pict.... */
	$"00E1 001C 0101 0000 0001 0000 0000 0000"            /* .·.............. */
	$"0000 0000 0000 FFFF FFFF 0000 0000 0000"            /* ......ˇˇˇˇ...... */
	$"0000 0000 0000 0000 0000 0000 0001 0000"            /* ................ */
	$"0001 0000 0082 6265 6773 646F 706C 5345"            /* .....ÇbegsdoplSE */
	$"4356 6F62 6A64 0000 003C 7669 6577 0000"            /* CVobjd...<view.. */
	$"0001 0082 0014 0101 0000 0000 0000 0029"            /* ...Ç...........) */
	$"0000 0005 0000 0000 FFFF FFFF 0000 0000"            /* ........ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"0000 0001 0000 656E 6473 656E 6473 6F62"            /* ......endsendsob */
	$"6A64 0000 0051 706C 6364 0000 0000 020F"            /* jd...Qplcd...... */
	$"0028 0101 0100 0101 FFFF FFFF 0000 01C4"            /* .(......ˇˇˇˇ...ƒ */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0000 0001 0000 0001"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 00E0 0000 0062 6567 736F 626A 6400"            /* ...‡...begsobjd. */
	$"0000 3C70 7573 6856 6C69 6400 4100 1401"            /* ..<pushVlid.A... */
	$"0100 0001 0100 0001 B700 0000 0900 0000"            /* ........∑...∆... */
	$"00FF FFFF FF00 0003 8400 0000 0000 0000"            /* .ˇˇˇˇ...Ñ....... */
	$"0000 0000 0001 7000 0004 5361 7665 016F"            /* ......p...Save.o */
	$"626A 6400 0000 3E70 7573 6843 6E63 6C00"            /* bjd...>pushCncl. */
	$"4100 1401 0100 0001 0100 0001 6900 0000"            /* A...........i... */
	$"0900 0000 00FF FFFF FF00 0003 8500 0000"            /* ∆....ˇˇˇˇ...Ö... */
	$"0000 0000 0000 0000 0001 7000 0006 4361"            /* ..........p...Ca */
	$"6E63 656C 006F 626A 6400 0000 3E70 7573"            /* ncel.objd...>pus */
	$"6852 7672 7400 4100 1401 0101 0000 0100"            /* hRvrt.A......... */
	$"0000 1C00 0000 0900 0000 00FF FFFF FF00"            /* ......∆....ˇˇˇˇ. */
	$"0000 0700 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"7000 0006 5265 7665 7274 006F 626A 6400"            /* p...Revert.objd. */
	$"0000 2469 636E 704C 6F63 6B00 1000 1001"            /* ..$icnpLock..... */
	$"0101 0000 0100 0000 0600 0000 0B00 0000"            /* ................ */
	$"00FF FFFF FF00 0065 6E64 7365 6E64 7365"            /* .ˇˇˇˇ..endsendse */
	$"6E64 2E"                                            /* nd. */
};

data 'PPob' (7200, "Interface Prefs Pane") {
	$"0002 6F62 6A64 0000 003C 7669 6577 0000"            /* ..objd...<view.. */
	$"0001 0186 00D2 0001 0000 0000 0000 0000"            /* ...Ü.“.......... */
	$"0000 0000 0000 0000 FFFF FFFF 0000 0000"            /* ........ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0000 0010"            /* ................ */
	$"0000 0010 0000 6265 6773 6F62 6A64 0000"            /* ......begsobjd.. */
	$"005A 7467 6278 0000 0000 016C 00B4 0101"            /* .Ztgbx.....l.¥.. */
	$"0000 0000 0000 000D 0000 000E 0000 0000"            /* ................ */
	$"FFFF FFFF 0000 0000 0000 0000 0000 0000"            /* ˇˇˇˇ............ */
	$"0000 0000 0000 0001 0000 0001 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 00A0"            /* ...............† */
	$"0085 0949 6E74 6572 6661 6365 6265 6773"            /* .Ö∆Interfacebegs */
	$"6F62 6A64 0000 005C 7467 6278 0000 0000"            /* objd...\tgbx.... */
	$"0100 0050 0101 0000 0000 0000 0036 0000"            /* ...P.........6.. */
	$"0018 0000 0000 FFFF FFFF 0000 0000 0000"            /* ......ˇˇˇˇ...... */
	$"0000 0000 0000 0000 0000 0000 0001 0000"            /* ................ */
	$"0001 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 00A4 0085 0B46 6F6E 7420 2620"            /* .....§.Ö.Font &  */
	$"7369 7A65 6265 6773 6F62 6A64 0000 0042"            /* sizebegsobjd...B */
	$"706F 7062 0000 0002 00B5 0013 0101 0000"            /* popb.....µ...... */
	$"0000 0000 001C 0000 0015 0000 0000 FFFF"            /* ..............ˇˇ */
	$"FFFF 0000 1C22 0000 0000 0000 00FA 0000"            /* ˇˇ...".......˙.. */
	$"FFFF 0194 0085 0546 6F6E 743A 464F 4E54"            /* ˇˇ.î.Ö.Font:FONT */
	$"0000 6F62 6A64 0000 0042 706F 7062 0000"            /* ..objd...Bpopb.. */
	$"0003 00B5 0013 0101 0000 0000 0000 001C"            /* ...µ............ */
	$"0000 0033 0000 0000 FFFF FFFF 0000 1C23"            /* ...3....ˇˇˇˇ...# */
	$"0000 0000 0000 0105 0000 FFFF 0194 0085"            /* ..........ˇˇ.î.Ö */
	$"0553 697A 653A 0000 0000 0001 656E 6473"            /* .Size:......ends */
	$"656E 6473 656E 6473 656E 642E"                      /* endsendsend. */
};

data 'PPob' (7300, "Templates Prefs Pane") {
	$"0002 6F62 6A64 0000 003C 7669 6577 0000"            /* ..objd...<view.. */
	$"0001 0186 00D2 0001 0000 0000 0000 0000"            /* ...Ü.“.......... */
	$"0000 0000 0000 0000 FFFF FFFF 0000 0000"            /* ........ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0000 0010"            /* ................ */
	$"0000 0010 0000 6265 6773 6F62 6A64 0000"            /* ......begsobjd.. */
	$"005A 7467 6278 0000 0000 016C 00B4 0101"            /* .Ztgbx.....l.¥.. */
	$"0000 0000 0000 000E 0000 000E 0000 0000"            /* ................ */
	$"FFFF FFFF 0000 0000 0000 0000 0000 0000"            /* ˇˇˇˇ............ */
	$"0000 0000 0000 0001 0000 0001 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 00A0"            /* ...............† */
	$"0085 0954 656D 706C 6174 6573 6265 6773"            /* .Ö∆Templatesbegs */
	$"6F62 6A64 0000 004A 7374 7874 0000 0000"            /* objd...Jstxt.... */
	$"006C 000F 0101 0000 0001 0000 0021 0000"            /* .l...........!.. */
	$"003D 0000 0000 FFFF FFFF 0000 0000 0000"            /* .=....ˇˇˇˇ...... */
	$"0000 0000 0000 0000 0000 0120 0085 1348"            /* ........... .Ö.H */
	$"6578 6164 6563 696D 616C 2064 6967 6974"            /* exadecimal digit */
	$"733A 6F62 6A64 0000 003C 7267 7076 0000"            /* s:objd...<rgpv.. */
	$"0005 006F 002E 0101 0000 0001 0000 0092"            /* ...o...........í */
	$"0000 0039 0000 0000 FFFF FFFF 0000 0000"            /* ...9....ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"0000 0001 0000 6265 6773 6F62 6A64 0000"            /* ......begsobjd.. */
	$"0044 7262 7574 0000 0006 005A 0010 0101"            /* .Drbut.....Z.... */
	$"0000 0000 0000 0005 0000 0003 0000 0000"            /* ................ */
	$"FFFF FFFF 0000 1C8A 0000 0001 0000 0000"            /* ˇˇˇˇ...ä........ */
	$"0000 0001 0002 008B 096C 6F77 6572 6361"            /* .......ã∆lowerca */
	$"7365 0000 0000 6F62 6A64 0000 0044 7262"            /* se....objd...Drb */
	$"7574 0000 0007 005A 0010 0101 0000 0000"            /* ut.....Z........ */
	$"0000 0005 0000 0017 0000 0000 FFFF FFFF"            /* ............ˇˇˇˇ */
	$"0000 1C8B 0000 0000 0000 0000 0000 0001"            /* ...ã............ */
	$"0002 008B 0975 7070 6572 6361 7365 0000"            /* ...ã∆uppercase.. */
	$"0000 656E 6473 6F62 6A64 0000 004A 7374"            /* ..endsobjd...Jst */
	$"7874 0000 0000 006C 0010 0101 0000 0001"            /* xt.....l........ */
	$"0000 0021 0000 0018 0000 0000 FFFF FFFF"            /* ...!........ˇˇˇˇ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0120 0085 1348 6578 6164 6563 696D 616C"            /* . .Ö.Hexadecimal */
	$"2073 796D 626F 6C3A 6F62 6A64 0000 003C"            /*  symbol:objd...< */
	$"7267 7076 0000 0002 0064 0016 0101 0000"            /* rgpv.....d...... */
	$"0001 0000 0092 0000 0014 0000 0000 FFFF"            /* .....í........ˇˇ */
	$"FFFF 0000 0000 0000 0000 0000 0000 0000"            /* ˇˇ.............. */
	$"0000 0000 0001 0000 0001 0000 6265 6773"            /* ............begs */
	$"6F62 6A64 0000 003D 7262 7574 0000 0004"            /* objd...=rbut.... */
	$"0028 0010 0101 0000 0000 0000 0036 0000"            /* .(...........6.. */
	$"0003 0000 0000 FFFF FFFF 0000 1C88 0000"            /* ......ˇˇˇˇ...à.. */
	$"0000 0000 0000 0000 0001 0002 008B 0230"            /* .............ã.0 */
	$"7800 0000 006F 626A 6400 0000 3C72 6275"            /* x....objd...<rbu */
	$"7400 0000 0300 2800 1001 0100 0000 0000"            /* t.....(......... */
	$"0000 0500 0000 0300 0000 00FF FFFF FF00"            /* ...........ˇˇˇˇ. */
	$"001C 8700 0000 0100 0000 0000 0000 0100"            /* ..á............. */
	$"0200 8B01 2400 0000 0065 6E64 736F 626A"            /* ..ã.$....endsobj */
	$"6400 0000 5963 6862 7800 0000 0800 DC00"            /* d...Ychbx.....‹. */
	$"1001 0100 0000 0000 0000 4400 0000 7500"            /* ..........D...u. */
	$"0000 00FF FFFF FF00 001C 8C00 0000 0000"            /* ...ˇˇˇˇ...å..... */
	$"0000 0000 0000 0100 0100 8B22 4469 7370"            /* ..........ã"Disp */
	$"6C61 7920 6669 6C6C 6572 2066 6965 6C64"            /* lay filler field */
	$"7320 696E 2074 656D 706C 6174 6573 6F62"            /* s in templatesob */
	$"6A64 0000 0058 6368 6278 0000 0009 00DC"            /* jd...Xchbx...∆.‹ */
	$"0010 0101 0000 0000 0000 0044 0000 008E"            /* ...........D...é */
	$"0000 0000 FFFF FFFF 0000 1C8D 0000 0000"            /* ....ˇˇˇˇ...ç.... */
	$"0000 0000 0000 0001 0001 008B 2145 6E61"            /* ...........ã!Ena */
	$"626C 6520 6669 6C6C 6572 2066 6965 6C64"            /* ble filler field */
	$"7320 696E 2074 656D 706C 6174 6573 656E"            /* s in templatesen */
	$"6473 656E 6473 656E 642E"                           /* dsendsend. */
};

data 'PPob' (7400, "Editors Prefs Pane") {
	$"0002 6F62 6A64 0000 003C 7669 6577 0000"            /* ..objd...<view.. */
	$"0001 0186 00D2 0001 0000 0000 0000 0000"            /* ...Ü.“.......... */
	$"0000 0000 0000 0000 FFFF FFFF 0000 0000"            /* ........ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0000 0010"            /* ................ */
	$"0000 0010 0000 6265 6773 6F62 6A64 0000"            /* ......begsobjd.. */
	$"0058 7467 6278 0000 0000 016C 00B4 0101"            /* .Xtgbx.....l.¥.. */
	$"0000 0000 0000 000F 0000 000E 0000 0000"            /* ................ */
	$"FFFF FFFF 0000 0000 0000 0000 0000 0000"            /* ˇˇˇˇ............ */
	$"0000 0000 0000 0001 0000 0001 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 00A0"            /* ...............† */
	$"0085 0745 6469 746F 7273 6265 6773 6F62"            /* .Ö.Editorsbegsob */
	$"6A64 0000 0044 7374 7874 0000 0000 006C"            /* jd...Dstxt.....l */
	$"0010 0101 0000 0001 0000 0021 0000 0018"            /* ...........!.... */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0120 0085 0D42 6974"            /* ......... .Ö.Bit */
	$"6D61 7020 6564 6974 6F72 6F62 6A64 0000"            /* map editorobjd.. */
	$"0057 6368 6278 0000 000A 00D2 0010 0101"            /* .Wchbx...¬.“.... */
	$"0000 0000 0000 003B 0000 002E 0000 0000"            /* .......;........ */
	$"FFFF FFFF 0000 1CF2 0000 0000 0000 0000"            /* ˇˇˇˇ...Ú........ */
	$"0000 0001 0001 008B 2055 7365 2038 2D62"            /* .......ã Use 8-b */
	$"6974 2063 6F6C 6F72 7320 2869 6E73 7465"            /* it colors (inste */
	$"6164 206F 6620 3332 296F 626A 6400 0000"            /* ad of 32)objd... */
	$"4C63 6862 7800 0000 0B00 9100 1001 0100"            /* Lchbx.....ë..... */
	$"0000 0000 0000 3B00 0000 4400 0000 00FF"            /* ......;...D....ˇ */
	$"FFFF FF00 001C F300 0000 0100 0000 0000"            /* ˇˇˇ...Û......... */
	$"0000 0100 0100 8B15 5573 6520 6675 6C6C"            /* ......ã.Use full */
	$"2063 6F6C 6F72 2074 6162 6C65 736F 626A"            /*  color tablesobj */
	$"6400 0000 4573 7478 7400 0000 0000 6C00"            /* d...Estxt.....l. */
	$"1001 0100 0000 0100 0000 2100 0000 6400"            /* ..........!...d. */
	$"0000 00FF FFFF FF00 0000 0000 0000 0000"            /* ...ˇˇˇˇ......... */
	$"0000 0000 0000 0001 2000 850E 556E 6963"            /* ........ .Ö.Unic */
	$"6F64 6520 6564 6974 6F72 6F62 6A64 0000"            /* ode editorobjd.. */
	$"004B 6368 6278 0000 0014 009B 0010 0101"            /* .Kchbx.....õ.... */
	$"0000 0000 0000 003B 0000 007A 0000 0000"            /* .......;...z.... */
	$"FFFF FFFF 0000 1CFC 0000 0001 0000 0000"            /* ˇˇˇˇ...¸........ */
	$"0000 0001 0001 008B 1444 6F20 666F 6E74"            /* .......ã.Do font */
	$"2073 7562 7374 6974 7574 696F 6E6F 626A"            /*  substitutionobj */
	$"6400 0000 4D63 6862 7800 0000 1500 9B00"            /* d...Mchbx.....õ. */
	$"1001 0100 0000 0000 0000 3B00 0000 9000"            /* ..........;...ê. */
	$"0000 00FF FFFF FF00 001C FD00 0000 0000"            /* ...ˇˇˇˇ...˝..... */
	$"0000 0000 0000 0100 0100 8B16 496E 7365"            /* ..........ã.Inse */
	$"7274 2042 7974 6520 4F72 6465 7220 4D61"            /* rt Byte Order Ma */
	$"726B 656E 6473 656E 6473 656E 642E"                 /* rkendsendsend. */
};

data 'PPob' (7500, "Compare Prefs Pane") {
	$"0002 6F62 6A64 0000 003C 7669 6577 0000"            /* ..objd...<view.. */
	$"0001 0186 00D2 0001 0000 0000 0000 0000"            /* ...Ü.“.......... */
	$"0000 0000 0000 0000 FFFF FFFF 0000 0000"            /* ........ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0000 0010"            /* ................ */
	$"0000 0010 0000 6265 6773 6F62 6A64 0000"            /* ......begsobjd.. */
	$"0069 7467 6278 0000 0000 016C 00B4 0101"            /* .itgbx.....l.¥.. */
	$"0000 0000 0000 000D 0000 000E 0000 0000"            /* ................ */
	$"FFFF FFFF 0000 0000 0000 0000 0000 0000"            /* ˇˇˇˇ............ */
	$"0000 0000 0000 0001 0000 0001 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 00A0"            /* ...............† */
	$"0085 1852 6573 6F75 7263 6520 6D61 7073"            /* .Ö.Resource maps */
	$"2063 6F6D 7061 7269 736F 6E62 6567 736F"            /*  comparisonbegso */
	$"626A 6400 0000 5373 7478 7400 0000 0000"            /* bjd...Sstxt..... */
	$"A000 1001 0100 0000 0000 0000 4400 0000"            /* †...........D... */
	$"1800 0000 00FF FFFF FF00 0000 0000 0000"            /* .....ˇˇˇˇ....... */
	$"0000 0000 0000 0000 0001 2000 851C 4465"            /* .......... .Ö.De */
	$"6661 756C 7420 636F 6D70 6172 6973 6F6E"            /* fault comparison */
	$"2063 7269 7465 7269 613A 6F62 6A64 0000"            /*  criteria:objd.. */
	$"004E 6368 6278 0000 0002 009D 0012 0101"            /* .Nchbx.....ù.... */
	$"0000 0000 0000 0059 0000 002A 0000 0000"            /* .......Y...*.... */
	$"FFFF FFFF 0000 1D4E 0000 0000 0000 0000"            /* ˇˇˇˇ...N........ */
	$"0000 0002 0171 008B 1769 676E 6F72 6520"            /* .....q.ã.ignore  */
	$"6E61 6D65 2064 6966 6665 7265 6E63 6573"            /* name differences */
	$"6F62 6A64 0000 0053 6368 6278 0000 0003"            /* objd...Schbx.... */
	$"00B4 0012 0101 0000 0000 0000 0059 0000"            /* .¥...........Y.. */
	$"003E 0000 0000 FFFF FFFF 0000 1D4F 0000"            /* .>....ˇˇˇˇ...O.. */
	$"0001 0000 0000 0000 0002 0171 008B 1C69"            /* ...........q.ã.i */
	$"676E 6F72 6520 6174 7472 6962 7574 6520"            /* gnore attribute  */
	$"6469 6666 6572 656E 6365 736F 626A 6400"            /* differencesobjd. */
	$"0000 4E63 6862 7800 0000 0400 9B00 1201"            /* ..Nchbx.....õ... */
	$"0100 0000 0000 0000 5900 0000 5200 0000"            /* ........Y...R... */
	$"00FF FFFF FF00 001D 5000 0000 0000 0000"            /* .ˇˇˇˇ...P....... */
	$"0000 0000 0201 7100 8B17 6967 6E6F 7265"            /* ......q.ã.ignore */
	$"2064 6174 6120 6469 6666 6572 656E 6365"            /*  data difference */
	$"736F 626A 6400 0000 5973 7478 7400 0000"            /* sobjd...Ystxt... */
	$"0000 C800 0E01 0100 0000 0100 0000 4400"            /* ..»...........D. */
	$"0000 6E00 0000 00FF FFFF FF00 0000 0000"            /* ..n....ˇˇˇˇ..... */
	$"0000 0000 0000 0000 0000 0001 2000 8522"            /* ............ .Ö" */
	$"4279 2064 6566 6175 6C74 2C20 6469 7370"            /* By default, disp */
	$"6C61 7920 6269 6E61 7279 2064 6174 6120"            /* lay binary data  */
	$"6173 6F62 6A64 0000 003C 7267 7076 0000"            /* asobjd...<rgpv.. */
	$"0005 00B9 0016 0101 0000 0001 0000 0054"            /* ...π...........T */
	$"0000 007E 0000 0000 FFFF FFFF 0000 0000"            /* ...~....ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"0000 0001 0000 6265 6773 6F62 6A64 0000"            /* ......begsobjd.. */
	$"0046 7262 7574 0000 0006 005A 0010 0101"            /* .Frbut.....Z.... */
	$"0000 0000 0000 0005 0000 0003 0000 0000"            /* ................ */
	$"FFFF FFFF 0000 1D52 0000 0001 0000 0000"            /* ˇˇˇˇ...R........ */
	$"0000 0001 0002 008B 0B68 6578 6164 6563"            /* .......ã.hexadec */
	$"696D 616C 0000 0000 6F62 6A64 0000 003F"            /* imal....objd...? */
	$"7262 7574 0000 0007 0046 0010 0101 0000"            /* rbut.....F...... */
	$"0000 0000 0069 0000 0003 0000 0000 FFFF"            /* .....i........ˇˇ */
	$"FFFF 0000 1D53 0000 0000 0000 0000 0000"            /* ˇˇ...S.......... */
	$"0001 0002 008B 0474 6578 7400 0000 0065"            /* .....ã.text....e */
	$"6E64 7365 6E64 7365 6E64 7365 6E64 2E"              /* ndsendsendsend. */
};

data 'PPob' (7600, "Export Prefs Pane") {
	$"0002 6F62 6A64 0000 003C 7669 6577 0000"            /* ..objd...<view.. */
	$"0001 0186 00D2 0001 0000 0000 0000 0000"            /* ...Ü.“.......... */
	$"0000 0000 0000 0000 FFFF FFFF 0000 0000"            /* ........ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0000 0010"            /* ................ */
	$"0000 0010 0000 6265 6773 6F62 6A64 0000"            /* ......begsobjd.. */
	$"0057 7467 6278 0000 0000 016C 00B4 0101"            /* .Wtgbx.....l.¥.. */
	$"0000 0000 0000 000D 0000 000E 0000 0000"            /* ................ */
	$"FFFF FFFF 0000 0000 0000 0000 0000 0000"            /* ˇˇˇˇ............ */
	$"0000 0000 0000 0001 0000 0001 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 00A0"            /* ...............† */
	$"0085 0645 7870 6F72 7462 6567 736F 626A"            /* .Ö.Exportbegsobj */
	$"6400 0000 3E73 7478 7400 0000 0000 3200"            /* d...>stxt.....2. */
	$"1001 0100 0000 0000 0000 4400 0000 1800"            /* ..........D..... */
	$"0000 00FF FFFF FF00 0000 0000 0000 0000"            /* ...ˇˇˇˇ......... */
	$"0000 0000 0000 0001 2000 8507 466F 726D"            /* ........ .Ö.Form */
	$"6174 3A6F 626A 6400 0000 3C72 6770 7600"            /* at:objd...<rgpv. */
	$"0000 0200 A800 3101 0100 0000 0000 0000"            /* ....®.1......... */
	$"7C00 0000 1100 0000 00FF FFFF FF00 0000"            /* |........ˇˇˇˇ... */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0100 0000 0100 0062 6567 736F 626A 6400"            /* .......begsobjd. */
	$"0000 4872 6275 7400 0000 0300 7800 1001"            /* ..Hrbut.....x... */
	$"0100 0000 0000 0000 0900 0000 0600 0000"            /* ........∆....... */
	$"00FF FFFF FF00 001D B300 0000 0100 0000"            /* .ˇˇˇˇ...≥....... */
	$"0000 0000 0100 0200 8B0D 4B65 792D 6261"            /* ........ã.Key-ba */
	$"7365 6420 4454 4400 0000 006F 626A 6400"            /* sed DTD....objd. */
	$"0000 4F72 6275 7400 0000 0400 9600 1001"            /* ..Orbut.....ñ... */
	$"0100 0000 0000 0000 0900 0000 1A00 0000"            /* ........∆....... */
	$"00FF FFFF FF00 001D B400 0000 0000 0000"            /* .ˇˇˇˇ...¥....... */
	$"0000 0000 0100 0200 8B14 4174 7472 6962"            /* ........ã.Attrib */
	$"7574 6573 2D62 6173 6564 2044 5444 0000"            /* utes-based DTD.. */
	$"0000 656E 6473 6F62 6A64 0000 0054 6368"            /* ..endsobjd...Tch */
	$"6278 0000 0005 00D2 0010 0101 0000 0000"            /* bx.....“........ */
	$"0000 004D 0000 004B 0000 0000 FFFF FFFF"            /* ...M...K....ˇˇˇˇ */
	$"0000 1DB5 0000 0001 0000 0000 0000 0001"            /* ...µ............ */
	$"0001 008B 1D49 6E63 6C75 6465 2062 696E"            /* ...ã.Include bin */
	$"6172 7920 6461 7461 2069 6E20 6F75 7470"            /* ary data in outp */
	$"7574 6F62 6A64 0000 0040 7374 7874 0000"            /* utobjd...@stxt.. */
	$"0000 0032 0010 0101 0000 0000 0000 0044"            /* ...2...........D */
	$"0000 006A 0000 0000 FFFF FFFF 0000 0000"            /* ...j....ˇˇˇˇ.... */
	$"0000 0000 0000 0000 0000 0000 0120 0085"            /* ............. .Ö */
	$"0945 6E63 6F64 696E 673A 6F62 6A64 0000"            /* ∆Encoding:objd.. */
	$"003C 7267 7076 0000 0006 00A7 0031 0101"            /* .<rgpv.....ß.1.. */
	$"0000 0000 0000 0079 0000 0063 0000 0000"            /* .......y...c.... */
	$"FFFF FFFF 0000 0000 0000 0000 0000 0000"            /* ˇˇˇˇ............ */
	$"0000 0000 0000 0001 0000 0001 0000 6265"            /* ..............be */
	$"6773 6F62 6A64 0000 004A 7262 7574 0000"            /* gsobjd...Jrbut.. */
	$"0007 0096 0010 0101 0000 0000 0000 0009"            /* ...ñ...........∆ */
	$"0000 0006 0000 0000 FFFF FFFF 0000 1DB7"            /* ........ˇˇˇˇ...∑ */
	$"0000 0001 0000 0000 0000 0001 0002 008B"            /* ...............ã */
	$"0F42 6173 6536 3420 656E 636F 6469 6E67"            /* .Base64 encoding */
	$"0000 0000 6F62 6A64 0000 004F 7262 7574"            /* ....objd...Orbut */
	$"0000 0008 0096 0010 0101 0000 0000 0000"            /* .....ñ.......... */
	$"0009 0000 001A 0000 0000 FFFF FFFF 0000"            /* .∆........ˇˇˇˇ.. */
	$"1DB8 0000 0000 0000 0000 0000 0001 0002"            /* .∏.............. */
	$"008B 1448 6578 6164 6563 696D 616C 2065"            /* .ã.Hexadecimal e */
	$"6E63 6F64 696E 6700 0000 0065 6E64 736F"            /* ncoding....endso */
	$"626A 6400 0000 4D73 7478 7400 0000 0000"            /* bjd...Mstxt..... */
	$"7B00 1001 0100 0000 0000 0000 4400 0000"            /* {...........D... */
	$"9D00 0000 00FF FFFF FF00 0000 0000 0000"            /* ù....ˇˇˇˇ....... */
	$"0000 0000 0000 0000 0001 2000 8516 5465"            /* .......... .Ö.Te */
	$"7874 2065 6469 746F 7220 7369 676E 6174"            /* xt editor signat */
	$"7572 653A 6F62 6A64 0000 003F 6574 7874"            /* ure:objd...?etxt */
	$"0000 0009 0032 0015 0101 0000 0000 0000"            /* ...∆.2.......... */
	$"00C0 0000 0099 0000 0000 FFFF FFFF 0000"            /* .¿...ô....ˇˇˇˇ.. */
	$"1DB9 0000 0000 0000 0000 0000 0000 0110"            /* .π.............. */
	$"008C 0474 7478 7400 0420 0365 6E64 7365"            /* .å.ttxt.. .endse */
	$"6E64 7365 6E64 2E"                                  /* ndsend. */
};

data 'PPob' (11500, "STR# Editor Window") {
	$"0002 646F 706C 5354 5257 6F62 6A64 0000"            /* ..doplSTRWobjd.. */
	$"001C 7769 6E64 2CEC 0002 1F66 0000 01A4"            /* ..wind,Ï...f...§ */
	$"00DC FFFF FFFF 0208 0230 0000 0000 6265"            /* .‹ˇˇˇˇ...0....be */
	$"6773 6F62 6A64 0000 0049 7363 6C76 5363"            /* gsobjd...IsclvSc */
	$"726C 0208 01F0 0101 0101 0101 0000 0000"            /* rl............. */
	$"0000 0018 0000 0000 FFFF FFFF 0000 0001"            /* ........ˇˇˇˇ.... */
	$"0000 0001 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 FFFF 000F 0000 0000 436E"            /* ......ˇˇ......Cn */
	$"7473 0162 6567 736F 626A 6400 0000 3C76"            /* ts.begsobjd...<v */
	$"6965 7743 6E74 7301 F501 EC01 0101 0101"            /* iewCnts.ı.Ï..... */
	$"0100 0000 0200 0000 0200 0000 00FF FFFF"            /* .............ˇˇˇ */
	$"FF00 0000 0000 0000 0400 0000 0000 0000"            /* ˇ............... */
	$"0000 0000 1400 0000 1400 0165 6E64 736F"            /* ...........endso */
	$"626A 6400 0000 5170 6C63 6400 0000 0002"            /* bjd...Qplcd..... */
	$"0A00 2801 0101 0001 01FF FFFF FF00 0002"            /* ¬.(......ˇˇˇˇ... */
	$"0800 0000 00FF FFFF FF00 0000 0000 0000"            /* .....ˇˇˇˇ....... */
	$"0000 0000 0000 0000 0000 0000 0100 0000"            /* ................ */
	$"0100 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 E000 0000 6265 6773 6F62 6A64"            /* ....‡...begsobjd */
	$"0000 003C 7075 7368 566C 6964 0041 0014"            /* ...<pushVlid.A.. */
	$"0101 0000 0101 0000 01B2 0000 0009 0000"            /* .........≤...∆.. */
	$"0000 FFFF FFFF 0000 0384 0000 0000 0000"            /* ..ˇˇˇˇ...Ñ...... */
	$"0000 0000 0000 0170 0000 0453 6176 6501"            /* .......p...Save. */
	$"6F62 6A64 0000 003E 7075 7368 436E 636C"            /* objd...>pushCncl */
	$"0041 0014 0101 0000 0101 0000 0164 0000"            /* .A...........d.. */
	$"0009 0000 0000 FFFF FFFF 0000 0385 0000"            /* .∆....ˇˇˇˇ...Ö.. */
	$"0000 0000 0000 0000 0000 0170 0000 0643"            /* ...........p...C */
	$"616E 6365 6C00 6F62 6A64 0000 003E 7075"            /* ancel.objd...>pu */
	$"7368 5276 7274 0041 0014 0101 0100 0001"            /* shRvrt.A........ */
	$"0000 001C 0000 0009 0000 0000 FFFF FFFF"            /* .......∆....ˇˇˇˇ */
	$"0000 0007 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0170 0000 0652 6576 6572 7400 6F62 6A64"            /* .p...Revert.objd */
	$"0000 0039 7075 7368 4D69 6E73 001F 0010"            /* ...9pushMins.... */
	$"0101 0100 0001 0000 00A1 0000 000A 0000"            /* .........°...¬.. */
	$"0000 FFFF FFFF 4D69 6E73 0000 0000 0000"            /* ..ˇˇˇˇMins...... */
	$"0000 0000 0000 0170 0000 012D 006F 626A"            /* .......p...-.obj */
	$"6400 0000 3970 7573 6850 6C75 7300 1E00"            /* d...9pushPlus... */
	$"1001 0101 0000 0100 0000 D500 0000 0A00"            /* ..........’...¬. */
	$"0000 00FF FFFF FF50 6C75 7300 0000 0000"            /* ...ˇˇˇˇPlus..... */
	$"0000 0000 0000 0001 7000 0001 2B00 6F62"            /* ........p...+.ob */
	$"6A64 0000 0024 6963 6E70 4C6F 636B 0010"            /* jd...$icnpLock.. */
	$"0010 0101 0100 0001 0000 0006 0000 000B"            /* ................ */
	$"0000 0000 FFFF FFFF 0000 656E 6473 6F62"            /* ....ˇˇˇˇ..endsob */
	$"6A64 0000 0051 7769 6E68 0000 0000 020C"            /* jd...Qwinh...... */
	$"0018 0101 0101 0100 FFFF FFFE 0000 0000"            /* ........ˇˇˇ˛.... */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....ˇˇˇˇ........ */
	$"0000 0000 0000 0000 0000 0001 0000 0001"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0150 0000 0062 6567 736F 626A 6400"            /* ...P...begsobjd. */
	$"0000 3773 7478 744E 616D 6501 F800 0E01"            /* ..7stxtName.¯... */
	$"0101 0100 0000 0000 0A00 0000 0500 0000"            /* ........¬....... */
	$"00FF FFFF FF00 0000 0000 0000 0000 0000"            /* .ˇˇˇˇ........... */
	$"0000 0000 0001 2000 8200 656E 6473 656E"            /* ...... .Ç.endsen */
	$"6473 656E 642E"                                     /* dsend. */
};

data 'PPob' (8400, "Get Value Dialog") {
	$"0002 6F62 6A64 0000 0028 5442 4278 20D0"            /* ..objd...(TBBx – */
	$"0000 08E2 0000 0040 0040 FFFF FFFF FFFF"            /* ...‚...@.@ˇˇˇˇˇˇ */
	$"FFFF 0000 0000 6F6B 2020 636E 636C FFFF"            /* ˇˇ....ok  cnclˇˇ */
	$"FFFF 6265 6773 6F62 6A64 0000 0012 7774"            /* ˇˇbegsobjd....wt */
	$"6861 FFFF FFFE 0101 0001 0002 0001 0002"            /* haˇˇˇ˛.......... */
	$"6F62 6A64 0000 003A 7075 7368 6F6B 2020"            /* objd...:pushok   */
	$"0043 0014 0101 0000 0101 0000 00A1 0000"            /* .C...........°.. */
	$"0045 0000 0000 FFFF FFFF 0000 0384 0000"            /* .E....ˇˇˇˇ...Ñ.. */
	$"0000 0000 0000 0000 0000 0170 0000 024F"            /* ...........p...O */
	$"4B01 6F62 6A64 0000 003E 7075 7368 636E"            /* K.objd...>pushcn */
	$"636C 0041 0014 0101 0000 0101 0000 0050"            /* cl.A...........P */
	$"0000 0045 0000 0000 FFFF FFFF 0000 0385"            /* ...E....ˇˇˇˇ...Ö */
	$"0000 0000 0000 0000 0000 0000 0170 0000"            /* .............p.. */
	$"0643 616E 6365 6C00 6F62 6A64 0000 0024"            /* .Cancel.objd...$ */
	$"6963 6E70 0000 0000 0020 0020 0101 0000"            /* icnp..... . .... */
	$"0000 0000 000D 0000 000E 0000 0000 FFFF"            /* ..............ˇˇ */
	$"FFFF 0080 6F62 6A64 0000 0029 6564 6974"            /* ˇˇ.Äobjd...)edit */
	$"5641 4C55 0030 0016 0101 0000 0000 0000"            /* VALU.0.......... */
	$"00B4 0000 0014 0000 0000 FFFF FFFF 0000"            /* .¥........ˇˇˇˇ.. */
	$"8C00 0388 016F 626A 6400 0000 4573 7478"            /* å..à.objd...Estx */
	$"7450 524F 4D00 7C00 1F01 0101 0000 0100"            /* tPROM.|......... */
	$"0000 3200 0000 1600 0000 00FF FFFF FF00"            /* ..2........ˇˇˇˇ. */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"2000 960E 456E 7465 7220 6120 7661 6C75"            /*  .ñ.Enter a valu */
	$"653A 656E 6473 656E 642E"                           /* e:endsend. */
};

data 'RidL' (1000, "Rez Map Window") {
	$"0003 0000 0003 0000 0002 0000 0001"                 /* .............. */
};

data 'RidL' (2000, "Inspector Window") {
	$"000C 0000 000B 0000 000C 0000 000D 0000"            /* ................ */
	$"000E 0000 000F 0000 0005 0000 0006 0000"            /* ................ */
	$"0001 0000 0003 0000 0004 0000 0014 0000"            /* ................ */
	$"0015"                                               /* .. */
};

data 'RidL' (2100, "New Resource Dialog") {
	$"000B 0000 000B 0000 000C 0000 000D 0000"            /* ................ */
	$"000E 0000 000F 0000 0001 0000 0003 0000"            /* ................ */
	$"0004 6F6B 2020 636E 636C 0000 0014"                 /* ..ok  cncl.... */
};

data 'RidL' (5000, "About Window") {
	$"0009 5665 7273 6F6B 2020 4C63 6E63 0000"            /* .∆Versok  Lcnc.. */
	$"000B 0000 000C 0000 000D 0000 000E 0000"            /* ................ */
	$"000F 0000 0010"                                     /* ...... */
};

data 'RidL' (5100, "Licence Window") {
	$"0000"                                               /* .. */
};

data 'RidL' (8500, "Find Dialog") {
	$"0005 0000 0004 6F6B 2020 636E 636C 0000"            /* ......ok  cncl.. */
	$"0002 0000 0003"                                     /* ...... */
};

data 'RidL' (9500, "Alert") {
	$"0001 6F6B 2020"                                     /* ..ok   */
};

data 'RidL' (9510, "Ask If") {
	$"0002 636E 636C 6F6B 2020"                           /* ..cnclok   */
};

data 'RidL' (9520, "Ask Yes No") {
	$"0003 6F6B 2020 636E 636C 6E6F 2020"                 /* ..ok  cnclno   */
};

data 'RidL' (6000, "Rez Compare Dialog") {
	$"0009 6F6B 2020 636E 636C 0000 0001 0000"            /* .∆ok  cncl...... */
	$"0003 0000 0002 0000 0005 0000 0004 0000"            /* ................ */
	$"0006 0000 0007"                                     /* ...... */
};

data 'RidL' (6500, "Rez Compare Results") {
	$"0008 0000 0002 0000 0003 0000 0008 0000"            /* ................ */
	$"0009 0000 0014 0000 0001 0000 001A 0000"            /* .∆.............. */
	$"001B"                                               /* .. */
};

data 'RidL' (9550, "Ask Unique ID") {
	$"0004 6F6B 2020 636E 636C 6E6F 2020 0000"            /* ..ok  cnclno  .. */
	$"0001"                                               /* .. */
};

data 'RidL' (7000, "Preferences Window") {
	$"0003 0000 0001 0000 0002 0000 0003"                 /* .............. */
};

data 'RidL' (7100, "General Prefs Pane") {
	$"0004 0000 0002 0000 0003 0000 0007 0000"            /* ................ */
	$"0006"                                               /* .. */
};

data 'RidL' (8600, "Set Font Size Dialog") {
	$"0002 6F6B 2020 636E 636C"                           /* ..ok  cncl */
};

data 'RidL' (10200, "TEXT Editor Window") {
	$"0002 4E61 6D65 0000 0001"                           /* ..Name.... */
};

data 'RidL' (10100, "TMPL Editor Window") {
	$"0004 566C 6964 436E 636C 5276 7274 4E61"            /* ..VlidCnclRvrtNa */
	$"6D65"                                               /* me */
};

data 'RidL' (8700, "Resource Type Picker") {
	$"0004 6F6B 2020 636E 636C 0000 0001 0000"            /* ..ok  cncl...... */
	$"0002"                                               /* .. */
};

data 'RidL' (8800, "Template Key Picker") {
	$"0006 6F6B 2020 636E 636C 0000 0002 0000"            /* ..ok  cncl...... */
	$"0004 0000 0003 0000 0001"                           /* .......... */
};

data 'RidL' (9530, "Explain Error Dialog") {
	$"0003 6F6B 2020 4558 504C 4D45 5347"                 /* ..ok  EXPLMESG */
};

data 'RidL' (10400, "PICT Viewer Window") {
	$"0002 0000 0002 0000 0003"                           /* .......... */
};

data 'RidL' (10500, "UTXT Editor Window") {
	$"0002 4E61 6D65 0000 0004"                           /* ..Name.... */
};

data 'RidL' (10600, "Icon Family Editor Window") {
	$"0017 744C 4153 7453 454C 7454 5854 7450"            /* ..tLAStSELtTXTtP */
	$"454E 7445 5241 7442 5543 7444 524F 744C"            /* ENtERAtBUCtDROtL */
	$"494E 7452 4543 7446 5243 7452 5243 7446"            /* INtRECtFRCtRRCtF */
	$"5252 744F 564C 7446 4F56 7450 4154 7442"            /* RRtOVLtFOVtPATtB */
	$"434C 7446 434C 454E 434C 434F 4F52 464F"            /* CLtFCLENCLCOORFO */
	$"4F54 566C 6964 436E 636C 5276 7274"                 /* OTVlidCnclRvrt */
};

data 'RidL' (8900, "Set Image Size Dialog") {
	$"0002 6F6B 2020 636E 636C"                           /* ..ok  cncl */
};

data 'RidL' (10601, "Cicn Editor Window") {
	$"0017 744C 4153 7453 454C 7454 5854 7450"            /* ..tLAStSELtTXTtP */
	$"454E 7445 5241 7442 5543 7444 524F 744C"            /* ENtERAtBUCtDROtL */
	$"494E 7452 4543 7446 5243 7452 5243 7446"            /* INtRECtFRCtRRCtF */
	$"5252 744F 564C 7446 4F56 7450 4154 7442"            /* RRtOVLtFOVtPATtB */
	$"434C 7446 434C 454E 434C 434F 4F52 464F"            /* CLtFCLENCLCOORFO */
	$"4F54 566C 6964 436E 636C 5276 7274"                 /* OTVlidCnclRvrt */
};

data 'RidL' (10602, "ICON Editor Window") {
	$"0017 744C 4153 7453 454C 7454 5854 7450"            /* ..tLAStSELtTXTtP */
	$"454E 7445 5241 7442 5543 7444 524F 744C"            /* ENtERAtBUCtDROtL */
	$"494E 7452 4543 7446 5243 7452 5243 7446"            /* INtRECtFRCtRRCtF */
	$"5252 744F 564C 7446 4F56 7450 4154 7442"            /* RRtOVLtFOVtPATtB */
	$"434C 7446 434C 454E 434C 434F 4F52 464F"            /* CLtFCLENCLCOORFO */
	$"4F54 566C 6964 436E 636C 5276 7274"                 /* OTVlidCnclRvrt */
};

data 'RidL' (10603, "PICT Editor Window") {
	$"0017 744C 4153 7453 454C 7454 5854 7450"            /* ..tLAStSELtTXTtP */
	$"454E 7445 5241 7442 5543 7444 524F 744C"            /* ENtERAtBUCtDROtL */
	$"494E 7452 4543 7446 5243 7452 5243 7446"            /* INtRECtFRCtRRCtF */
	$"5252 744F 564C 7446 4F56 7450 4154 7442"            /* RRtOVLtFOVtPATtB */
	$"434C 7446 434C 454E 434C 434F 4F52 464F"            /* CLtFCLENCLCOORFO */
	$"4F54 566C 6964 436E 636C 5276 7274"                 /* OTVlidCnclRvrt */
};

data 'RidL' (10604, "CURS Editor Window") {
	$"0018 744C 4153 7453 454C 7454 5854 7450"            /* ..tLAStSELtTXTtP */
	$"454E 7445 5241 7442 5543 7444 524F 744C"            /* ENtERAtBUCtDROtL */
	$"494E 7452 4543 7446 5243 7452 5243 7446"            /* INtRECtFRCtRRCtF */
	$"5252 744F 564C 7446 4F56 7448 4F54 7450"            /* RRtOVLtFOVtHOTtP */
	$"4154 7442 434C 7446 434C 454E 434C 434F"            /* ATtBCLtFCLENCLCO */
	$"4F52 464F 4F54 566C 6964 436E 636C 5276"            /* ORFOOTVlidCnclRv */
	$"7274"                                               /* rt */
};

data 'RidL' (10605, "Crsr Editor Window") {
	$"0018 744C 4153 7453 454C 7454 5854 7450"            /* ..tLAStSELtTXTtP */
	$"454E 7445 5241 7442 5543 7444 524F 744C"            /* ENtERAtBUCtDROtL */
	$"494E 7452 4543 7446 5243 7452 5243 7446"            /* INtRECtFRCtRRCtF */
	$"5252 744F 564C 7446 4F56 7448 4F54 7450"            /* RRtOVLtFOVtHOTtP */
	$"4154 7442 434C 7446 434C 454E 434C 434F"            /* ATtBCLtFCLENCLCO */
	$"4F52 464F 4F54 566C 6964 436E 636C 5276"            /* ORFOOTVlidCnclRv */
	$"7274"                                               /* rt */
};

data 'RidL' (10606, "Pattern Editor Window") {
	$"0017 744C 4153 7453 454C 7454 5854 7450"            /* ..tLAStSELtTXTtP */
	$"454E 7445 5241 7442 5543 7444 524F 744C"            /* ENtERAtBUCtDROtL */
	$"494E 7452 4543 7446 5243 7452 5243 7446"            /* INtRECtFRCtRRCtF */
	$"5252 744F 564C 7446 4F56 7450 4154 7442"            /* RRtOVLtFOVtPATtB */
	$"434C 7446 434C 454E 434C 434F 4F52 464F"            /* CLtFCLENCLCOORFO */
	$"4F54 566C 6964 436E 636C 5276 7274"                 /* OTVlidCnclRvrt */
};

data 'RidL' (10607, "PixPat Editor Window") {
	$"0019 744C 4153 7453 454C 7454 5854 7450"            /* ..tLAStSELtTXTtP */
	$"454E 7445 5241 7442 5543 7444 524F 744C"            /* ENtERAtBUCtDROtL */
	$"494E 7452 4543 7446 5243 7452 5243 7446"            /* INtRECtFRCtRRCtF */
	$"5252 744F 564C 7446 4F56 7450 4154 7442"            /* RRtOVLtFOVtPATtB */
	$"434C 7446 434C 454E 434C 4E41 4D31 4E41"            /* CLtFCLENCLNAM1NA */
	$"4D32 434F 4F52 464F 4F54 566C 6964 436E"            /* M2COORFOOTVlidCn */
	$"636C 5276 7274"                                     /* clRvrt */
};

data 'RidL' (10608, "Pattern Suite Editor Window") {
	$"001B 744C 4153 7453 454C 7454 5854 7450"            /* ..tLAStSELtTXTtP */
	$"454E 7445 5241 7442 5543 7444 524F 744C"            /* ENtERAtBUCtDROtL */
	$"494E 7452 4543 7446 5243 7452 5243 7446"            /* INtRECtFRCtRRCtF */
	$"5252 744F 564C 7446 4F56 7450 4154 7442"            /* RRtOVLtFOVtPATtB */
	$"434C 7446 434C 454E 434C 434F 4F52 534C"            /* CLtFCLENCLCOORSL */
	$"4944 434F 554E 4D69 6E73 506C 7573 464F"            /* IDCOUNMinsPlusFO */
	$"4F54 566C 6964 436E 636C 5276 7274"                 /* OTVlidCnclRvrt */
};

data 'RidL' (10609, "Icon Suite Editor Window") {
	$"001B 744C 4153 7453 454C 7454 5854 7450"            /* ..tLAStSELtTXTtP */
	$"454E 7445 5241 7442 5543 7444 524F 744C"            /* ENtERAtBUCtDROtL */
	$"494E 7452 4543 7446 5243 7452 5243 7446"            /* INtRECtFRCtRRCtF */
	$"5252 744F 564C 7446 4F56 7450 4154 7442"            /* RRtOVLtFOVtPATtB */
	$"434C 7446 434C 454E 434C 434F 4F52 534C"            /* CLtFCLENCLCOORSL */
	$"4944 434F 554E 4D69 6E73 506C 7573 464F"            /* IDCOUNMinsPlusFO */
	$"4F54 566C 6964 436E 636C 5276 7274"                 /* OTVlidCnclRvrt */
};

data 'RidL' (3000, "Hex Editing Window") {
	$"0005 0000 000A 0000 0001 4E61 6D65 0000"            /* .....¬....Name.. */
	$"0004 0000 0005"                                     /* ...... */
};

data 'RidL' (7700, "Misc Prefs Pane") {
	$"0005 0000 0002 0000 0003 0000 0004 0000"            /* ................ */
	$"0006 0000 0005"                                     /* ...... */
};

data 'RidL' (11000, "AETE Editor Window") {
	$"0011 0000 0001 0000 0002 0000 0003 0000"            /* ................ */
	$"0004 5355 4942 0000 0005 0000 0006 0000"            /* ..SUIB.......... */
	$"0007 0000 0008 0000 0009 4E61 6D65 5355"            /* .........∆NameSU */
	$"4954 534C 4944 5349 4443 566C 6964 436E"            /* ITSLIDSIDCVlidCn */
	$"636C 5276 7274"                                     /* clRvrt */
};

data 'RidL' (11100) {
	$"0014 0000 0001 0000 0002 0000 0003 0000"            /* ................ */
	$"0004 4452 4354 0000 000B 0000 000D 0000"            /* ..DRCT.......... */
	$"000C 5245 504C 0000 0015 0000 0017 0000"            /* ..REPL.......... */
	$"0016 4F54 4852 0000 0021 0000 0023 0000"            /* ..OTHR...!...#.. */
	$"0022 0000 001F 0000 0020 4F53 4C49 4F49"            /* ."....... OSLIOI */
	$"4443"                                               /* DC */
};

data 'RidL' (11200, "Class Pane") {
	$"0012 0000 0001 0000 0002 0000 0003 454C"            /* ..............EL */
	$"454D 0000 0016 0000 0017 4B53 4C49 4B49"            /* EM........KSLIKI */
	$"4443 5052 4F50 0000 000B 0000 000C 0000"            /* DCPROP.......... */
	$"000D 0000 000F 0000 000E 4553 4C49 5049"            /* ..........ESLIPI */
	$"4443 5053 4C49 4549 4443"                           /* DCPSLIEIDC */
};

data 'RidL' (11300, "Comp Operator Pane") {
	$"0004 434D 504F 0000 0001 0000 0002 0000"            /* ..CMPO.......... */
	$"0003"                                               /* .. */
};

data 'RidL' (11400, "Enumerations Pane") {
	$"0007 0000 0001 454E 554D 0000 0002 0000"            /* ......ENUM...... */
	$"0003 0000 0004 4E53 4C49 4E49 4443"                 /* ......NSLINIDC */
};

data 'RidL' (10610, "Icns Editor Window") {
	$"0019 744C 4153 7453 454C 7454 5854 7450"            /* ..tLAStSELtTXTtP */
	$"454E 7445 5241 7442 5543 7444 524F 744C"            /* ENtERAtBUCtDROtL */
	$"494E 7452 4543 7446 5243 7452 5243 7446"            /* INtRECtFRCtRRCtF */
	$"5252 744F 564C 7446 4F56 7450 4154 7442"            /* RRtOVLtFOVtPATtB */
	$"434C 7446 434C 454E 434C 434F 4F52 4943"            /* CLtFCLENCLCOORIC */
	$"5354 494E 434C 464F 4F54 566C 6964 436E"            /* STINCLFOOTVlidCn */
	$"636C 5276 7274"                                     /* clRvrt */
};

data 'RidL' (10300, "MENU Editor Window") {
	$"001B 0000 0028 0000 0005 0000 0006 0000"            /* .....(.......... */
	$"0011 0000 0007 0000 0012 0000 0008 0000"            /* ................ */
	$"0013 0000 0009 0000 0014 0000 0015 0000"            /* .....∆.......... */
	$"0016 0000 0017 0000 001E 0000 0022 0000"            /* .............".. */
	$"0021 0000 001F 0000 0020 0000 0029 4D69"            /* .!....... ...)Mi */
	$"6E73 506C 7573 0000 0004 0000 0002 0000"            /* nsPlus.......... */
	$"0003 566C 6964 436E 636C 5276 7274"                 /* ..VlidCnclRvrt */
};

data 'RidL' (7200, "Interface Prefs Pane") {
	$"0002 0000 0002 0000 0003"                           /* .......... */
};

data 'RidL' (7300, "Templates Prefs Pane") {
	$"0006 0000 0006 0000 0007 0000 0004 0000"            /* ................ */
	$"0003 0000 0008 0000 0009"                           /* .........∆ */
};

data 'RidL' (7400, "Editors Prefs Pane") {
	$"0004 0000 000A 0000 000B 0000 0014 0000"            /* .....¬.......... */
	$"0015"                                               /* .. */
};

data 'RidL' (7500, "Compare Prefs Pane") {
	$"0005 0000 0002 0000 0003 0000 0004 0000"            /* ................ */
	$"0006 0000 0007"                                     /* ...... */
};

data 'RidL' (7600, "Export Prefs Pane") {
	$"0006 0000 0003 0000 0004 0000 0005 0000"            /* ................ */
	$"0007 0000 0008 0000 0009"                           /* .........∆ */
};

data 'RidL' (11500, "STR# Editor Window") {
	$"0006 566C 6964 436E 636C 5276 7274 4D69"            /* ..VlidCnclRvrtMi */
	$"6E73 506C 7573 4E61 6D65"                           /* nsPlusName */
};

data 'RidL' (8400, "Get Value Dialog") {
	$"0003 6F6B 2020 636E 636C 5052 4F4D"                 /* ..ok  cnclPROM */
};

resource 'STR#' (200, "Standards", purgeable) {
	{	/* array StringArray: 4 elements */
		/* [1] */
		"Rezilla",
		/* [2] */
		"Save File As:",
		/* [3] */
		"Open with Rezilla",
		/* [4] */
		"Save with Rezilla"
	}
};

resource 'STR#' (1000, "Prefs controller list") {
	{	/* array StringArray: 7 elements */
		/* [1] */
		"General",
		/* [2] */
		"Interface",
		/* [3] */
		"Templates",
		/* [4] */
		"Editors",
		/* [5] */
		"Compare",
		/* [6] */
		"Export",
		/* [7] */
		"Misc"
	}
};

resource 'STR#' (1001, "Aete controller list") {
	{	/* array StringArray: 4 elements */
		/* [1] */
		"Events",
		/* [2] */
		"Classes",
		/* [3] */
		"Comparison Operators",
		/* [4] */
		"Enumerations"
	}
};

data 'Txtr' (128, "System Font") {
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"00"                                                 /* . */
};

data 'Txtr' (129, "App Font") {
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"00"                                                 /* . */
};

data 'Txtr' (130, "Geneva 9") {
	$"0009 0000 0000 0001 0000 0000 0000 FFFF"            /* .∆............ˇˇ */
	$"0647 656E 6576 61"                                  /* .Geneva */
};

data 'Txtr' (131, "Geneva 10 bold") {
	$"000A 0001 FFFE 0001 0000 0000 0000 FFFF"            /* .¬..ˇ˛........ˇˇ */
	$"0647 656E 6576 61"                                  /* .Geneva */
};

data 'Txtr' (132, "System Font Centered", purgeable) {
	$"0000 0000 0001 0001 0000 0000 0000 0000"            /* ................ */
	$"00"                                                 /* . */
};

data 'Txtr' (133, "Monaco Gray 9") {
	$"0009 0001 0000 0000 2222 2222 2222 0004"            /* .∆......"""""".. */
	$"064D 6F6E 6163 6F"                                  /* .Monaco */
};

data 'Txtr' (134, "Prefs Controller") {
	$"000A 0000 0001 0001 FFFF FFFF FFFF FFFF"            /* .¬......ˇˇˇˇˇˇˇˇ */
	$"0647 656E 6576 61"                                  /* .Geneva */
};

data 'Txtr' (135, "Geneva Bold Red 10") {
	$"000A 0001 0000 0001 CCCC 0000 0000 0003"            /* .¬......ÃÃ...... */
	$"0647 656E 6576 61"                                  /* .Geneva */
};

data 'Txtr' (136, "Status Red") {
	$"0009 0002 0000 0000 DDDD 0000 0000 0003"            /* .∆......››...... */
	$"0647 656E 6576 61"                                  /* .Geneva */
};

data 'Txtr' (137, "System Font Italic", purgeable) {
	$"0000 0002 FFFE 0001 0000 0000 0000 0000"            /* ....ˇ˛.......... */
	$"00"                                                 /* . */
};

data 'Txtr' (138, "Status upright") {
	$"0009 0000 0000 0000 0000 0000 9999 0003"            /* .∆..........ôô.. */
	$"0647 656E 6576 61"                                  /* .Geneva */
};

data 'Txtr' (139, "Monaco 9") {
	$"0009 0000 0000 0001 0000 0000 0000 FFFF"            /* .∆............ˇˇ */
	$"064D 6F6E 6163 6F"                                  /* .Monaco */
};

data 'Txtr' (140, "Geneva 10") {
	$"000A 0000 FFFE 0001 0000 0000 0000 FFFF"            /* .¬..ˇ˛........ˇˇ */
	$"0647 656E 6576 61"                                  /* .Geneva */
};

data 'Txtr' (141, "Monaco Blue 9 Center") {
	$"0009 0001 0001 0000 0000 0000 9999 0004"            /* .∆..........ôô.. */
	$"064D 6F6E 6163 6F"                                  /* .Monaco */
};

data 'Txtr' (142, "Geneva Black 9 Center") {
	$"0009 0002 0001 0000 1111 0000 0000 0003"            /* .∆.............. */
	$"0647 656E 6576 61"                                  /* .Geneva */
};

data 'Txtr' (143, "Geneva 9 italic") {
	$"0009 0002 0000 0001 0000 0000 0000 FFFF"            /* .∆............ˇˇ */
	$"0647 656E 6576 61"                                  /* .Geneva */
};

data 'Txtr' (144, "Geneva 10 bold ul left") {
	$"000A 0005 FFFE 0001 0000 0000 0000 FFFF"            /* .¬..ˇ˛........ˇˇ */
	$"0647 656E 6576 61"                                  /* .Geneva */
};

data 'Txtr' (145, "Geneva 10 bold ul right") {
	$"000A 0005 FFFF 0001 0000 0000 0000 FFFF"            /* .¬..ˇˇ........ˇˇ */
	$"0647 656E 6576 61"                                  /* .Geneva */
};

data 'Txtr' (146, "URL Hyperlink") {
	$"0009 0004 0001 0000 0000 0000 FFFF 0004"            /* .∆..........ˇˇ.. */
	$"064D 6F6E 6163 6F"                                  /* .Monaco */
};

data 'Txtr' (147, "Monaco Gray 10") {
	$"000A 0001 0000 0000 4444 4444 4444 0004"            /* .¬......DDDDDD.. */
	$"064D 6F6E 6163 6F"                                  /* .Monaco */
};

data 'Txtr' (148, "Geneva Blue 10 Left") {
	$"000A 0000 FFFE 0000 0000 0000 9999 FFFF"            /* .¬..ˇ˛......ôôˇˇ */
	$"0647 656E 6576 61"                                  /* .Geneva */
};

data 'Txtr' (149, "Geneva 10 bold left") {
	$"000A 0001 FFFE 0001 0000 0000 1111 FFFF"            /* .¬..ˇ˛........ˇˇ */
	$"0647 656E 6576 61"                                  /* .Geneva */
};

data 'Txtr' (150, "Geneva 10 bold right") {
	$"000A 0001 FFFF 0001 0000 0000 1111 FFFF"            /* .¬..ˇˇ........ˇˇ */
	$"0647 656E 6576 61"                                  /* .Geneva */
};

data 'Txtr' (151, "Geneva 10 bold Ul") {
	$"000A 0005 FFFE 0001 0000 0000 0000 FFFF"            /* .¬..ˇ˛........ˇˇ */
	$"0647 656E 6576 61"                                  /* .Geneva */
};

data 'Txtr' (152, "Monaco 9 bold") {
	$"0009 0001 0000 0001 0000 0000 0000 FFFF"            /* .∆............ˇˇ */
	$"064D 6F6E 6163 6F"                                  /* .Monaco */
};

data 'Txtr' (153, "Monaco 10") {
	$"000A 0000 0000 0001 0000 0000 0000 FFFF"            /* .¬............ˇˇ */
	$"064D 6F6E 6163 6F"                                  /* .Monaco */
};

data 'Txtr' (154, "Geneva 10 Bold") {
	$"000A 0001 FFFE 0001 0000 0000 0000 FFFF"            /* .¬..ˇ˛........ˇˇ */
	$"0647 656E 6576 61"                                  /* .Geneva */
};

resource 'WIND' (1000, "Rez Map Window") {
	{46, 2, 596, 352},
	zoomDocProc,
	visible,
	goAway,
	0x0,
	"Rez Map Table",
	noAutoCenter
};

resource 'WIND' (2000, "Inspector Window") {
	{42, 4, 307, 312},
	noGrowDocProc,
	invisible,
	goAway,
	0x0,
	"Inspector",
	alertPositionMainScreen
};

resource 'WIND' (2100, "New Resource Dialog") {
	{42, 4, 254, 312},
	movableDBoxProc,
	invisible,
	noGoAway,
	0x0,
	"New resource",
	centerMainScreen
};

resource 'WIND' (5000, "About Window") {
	{40, 16, 407, 346},
	plainDBox,
	invisible,
	noGoAway,
	0x0,
	"",
	alertPositionMainScreen
};

resource 'WIND' (5100, "Licence Window") {
	{42, 4, 392, 404},
	zoomDocProc,
	invisible,
	goAway,
	0x0,
	"Rezilla Licence",
	noAutoCenter
};

resource 'WIND' (8500, "Find Dialog") {
	{40, 16, 235, 320},
	movableDBoxProc,
	invisible,
	noGoAway,
	0x0,
	"Search",
	alertPositionParentWindow
};

resource 'WIND' (9500, "Alert") {
	{40, 16, 190, 321},
	movableDBoxProc,
	invisible,
	noGoAway,
	0x0,
	"",
	alertPositionMainScreen
};

resource 'WIND' (9510, "Ask If") {
	{40, 16, 190, 316},
	movableDBoxProc,
	invisible,
	noGoAway,
	0x0,
	"",
	alertPositionMainScreen
};

resource 'WIND' (9520, "Ask Yes No") {
	{40, 16, 190, 316},
	movableDBoxProc,
	invisible,
	noGoAway,
	0x0,
	"",
	alertPositionMainScreen
};

resource 'WIND' (6000, "Rez Compare Dialog") {
	{40, 16, 250, 551},
	movableDBoxProc,
	invisible,
	noGoAway,
	0x0,
	"RezMap Compare",
	alertPositionMainScreen
};

resource 'WIND' (6500, "Rez Compare Results") {
	{42, 4, 576, 619},
	zoomDocProc,
	invisible,
	goAway,
	0x0,
	"Comparison window",
	staggerMainScreen
};

resource 'WIND' (9550, "Ask Unique ID") {
	{40, 16, 226, 317},
	movableDBoxProc,
	invisible,
	noGoAway,
	0x0,
	"",
	alertPositionMainScreen
};

resource 'WIND' (7000, "Preferences Window") {
	{40, 16, 326, 466},
	movableDBoxProc,
	invisible,
	noGoAway,
	0x0,
	"Rezilla Preferences",
	alertPositionMainScreen
};

resource 'WIND' (8600, "Set Font Size Dialog") {
	{40, 16, 140, 256},
	movableDBoxProc,
	invisible,
	noGoAway,
	0x0,
	"Set Font Size",
	alertPositionParentWindow
};

resource 'WIND' (10200, "TEXT Editor Window") {
	{42, 4, 592, 504},
	zoomDocProc,
	invisible,
	goAway,
	0x0,
	"TEXT editor",
	noAutoCenter
};

resource 'WIND' (10100, "TMPL Editor Window") {
	{42, 4, 602, 524},
	zoomDocProc,
	invisible,
	goAway,
	0x0,
	"Template editor",
	noAutoCenter
};

resource 'WIND' (8700, "Resource Type Picker") {
	{40, 16, 162, 269},
	movableDBoxProc,
	invisible,
	noGoAway,
	0x0,
	"Select Type",
	alertPositionParentWindow
};

resource 'WIND' (8800, "Template Key Picker") {
	{40, 16, 235, 385},
	movableDBoxProc,
	invisible,
	noGoAway,
	0x0,
	"Template format option",
	alertPositionParentWindow
};

resource 'WIND' (9530, "Explain Error Dialog") {
	{40, 16, 195, 321},
	movableDBoxProc,
	invisible,
	noGoAway,
	0x0,
	"",
	alertPositionMainScreen
};

resource 'WIND' (10400, "PICT Viewer Window") {
	{42, 4, 586, 524},
	zoomDocProc,
	invisible,
	goAway,
	0x0,
	"PICT viewer",
	noAutoCenter
};

resource 'WIND' (10500, "UTXT Editor Window") {
	{42, 4, 584, 504},
	zoomDocProc,
	invisible,
	goAway,
	0x0,
	"Unicode editor",
	noAutoCenter
};

resource 'WIND' (10600, "Icon Family Editor Window") {
	{42, 4, 438, 570},
	noGrowDocProc,
	invisible,
	goAway,
	0x0,
	"Icon suite editor",
	staggerParentWindow
};

resource 'WIND' (8900, "Set Image Size Dialog") {
	{40, 16, 140, 256},
	movableDBoxProc,
	invisible,
	noGoAway,
	0x0,
	"Set Image Size",
	alertPositionParentWindow
};

resource 'WIND' (10601, "Cicn Editor Window") {
	{42, 4, 422, 513},
	noGrowDocProc,
	invisible,
	goAway,
	0x0,
	"cicn editor",
	staggerParentWindow
};

resource 'WIND' (10602, "ICON Editor Window") {
	{42, 4, 382, 454},
	noGrowDocProc,
	invisible,
	goAway,
	0x0,
	"Icon editor",
	staggerParentWindow
};

resource 'WIND' (10603, "PICT Editor Window") {
	{42, 4, 452, 464},
	documentProc,
	invisible,
	goAway,
	0x0,
	"PICT editor",
	staggerParentWindow
};

resource 'WIND' (10604, "CURS Editor Window") {
	{42, 4, 397, 444},
	noGrowDocProc,
	invisible,
	goAway,
	0x0,
	"Cursor editor",
	staggerParentWindow
};

resource 'WIND' (10605, "Crsr Editor Window") {
	{42, 4, 397, 444},
	noGrowDocProc,
	invisible,
	goAway,
	0x0,
	"Crsr editor",
	staggerParentWindow
};

resource 'WIND' (10606, "Pattern Editor Window") {
	{42, 4, 362, 285},
	noGrowDocProc,
	invisible,
	goAway,
	0x0,
	"Pattern editor",
	staggerParentWindow
};

resource 'WIND' (10607, "PixPat Editor Window") {
	{42, 4, 362, 285},
	noGrowDocProc,
	invisible,
	goAway,
	0x0,
	"PixPat editor",
	staggerParentWindow
};

resource 'WIND' (10608, "Pattern Suite Editor Window") {
	{42, 4, 362, 285},
	noGrowDocProc,
	invisible,
	goAway,
	0x0,
	"Pattern suite editor",
	staggerParentWindow
};

resource 'WIND' (10609, "Icon Suite Editor Window") {
	{42, 4, 382, 369},
	noGrowDocProc,
	invisible,
	goAway,
	0x0,
	"Icon suite editor",
	staggerParentWindow
};

resource 'WIND' (3000, "Hex Editing Window") {
	{42, 4, 457, 538},
	zoomDocProc,
	invisible,
	goAway,
	0x0,
	"Hex Editing",
	staggerParentWindow
};

resource 'WIND' (11000, "AETE Editor Window") {
	{42, 4, 547, 674},
	noGrowDocProc,
	invisible,
	goAway,
	0x0,
	"Aete editor",
	noAutoCenter
};

resource 'WIND' (10610, "Icns Editor Window") {
	{42, 4, 472, 570},
	noGrowDocProc,
	invisible,
	goAway,
	0x0,
	"Icns editor",
	staggerParentWindow
};

resource 'WIND' (10300, "MENU Editor Window") {
	{42, 4, 534, 529},
	noGrowDocProc,
	invisible,
	goAway,
	0x0,
	"Menu editor",
	noAutoCenter
};

resource 'WIND' (11500, "STR# Editor Window") {
	{42, 4, 602, 524},
	zoomDocProc,
	invisible,
	goAway,
	0x0,
	"STR# editor",
	noAutoCenter
};

resource 'WIND' (8400, "Get Value Dialog") {
	{40, 16, 140, 256},
	movableDBoxProc,
	invisible,
	noGoAway,
	0x0,
	"",
	alertPositionParentWindow
};

resource 'xmnu' (128, "Apple Menu") {
	versionZero {
		{	/* array ItemExtensions: 1 elements */
			/* [1] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			}
		}
	}
};

resource 'xmnu' (129, "File Menu") {
	versionZero {
		{	/* array ItemExtensions: 12 elements */
			/* [1] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [2] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [3] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				140,
				sysFont,
				naturalGlyph
			},
			/* [4] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [5] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [6] */
			skipItem {

			},
			/* [7] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [8] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [9] */
			skipItem {

			},
			/* [10] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [11] */
			skipItem {

			},
			/* [12] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			}
		}
	}
};

resource 'xmnu' (130, "Edit Menu") {
	versionZero {
		{	/* array ItemExtensions: 12 elements */
			/* [1] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [2] */
			skipItem {

			},
			/* [3] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [4] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [5] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [6] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [7] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [8] */
			skipItem {

			},
			/* [9] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [10] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [11] */
			skipItem {

			},
			/* [12] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			}
		}
	}
};

resource 'xmnu' (131, "Plugins Menu") {
	versionZero {
		{	/* array ItemExtensions: 2 elements */
			/* [1] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [2] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			}
		}
	}
};

resource 'xmnu' (132, "File Menu Aqua") {
	versionZero {
		{	/* array ItemExtensions: 10 elements */
			/* [1] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [2] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [3] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				140,
				sysFont,
				naturalGlyph
			},
			/* [4] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [5] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [6] */
			skipItem {

			},
			/* [7] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [8] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [9] */
			skipItem {

			},
			/* [10] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			}
		}
	}
};

resource 'xmnu' (251, "Text Size") {
	versionZero {
		{	/* array ItemExtensions: 11 elements */
			/* [1] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [2] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [3] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [4] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [5] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [6] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [7] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [8] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [9] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [10] */
			skipItem {

			},
			/* [11] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			}
		}
	}
};

resource 'xmnu' (252, "Text Style") {
	versionZero {
		{	/* array ItemExtensions: 10 elements */
			/* [1] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [2] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [3] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [4] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [5] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [6] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [7] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [8] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [9] */
			skipItem {

			},
			/* [10] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			}
		}
	}
};

resource 'xmnu' (253, "Types") {
	versionZero {
		{	/* array ItemExtensions: 1 elements */
			/* [1] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			}
		}
	}
};

resource 'xmnu' (256, "Unicode Size") {
	versionZero {
		{	/* array ItemExtensions: 12 elements */
			/* [1] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [2] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [3] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [4] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [5] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [6] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [7] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [8] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [9] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [10] */
			skipItem {

			},
			/* [11] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [12] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			}
		}
	}
};

resource 'xmnu' (257, "Unicode Style") {
	versionZero {
		{	/* array ItemExtensions: 4 elements */
			/* [1] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [2] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [3] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [4] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			}
		}
	}
};

resource 'xmnu' (300, "Icon Actions") {
	versionZero {
		{	/* array ItemExtensions: 10 elements */
			/* [1] */
			dataItem {
				0,
				0x2,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [2] */
			dataItem {
				0,
				0x2,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [3] */
			skipItem {

			},
			/* [4] */
			dataItem {
				0,
				0x2,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [5] */
			dataItem {
				0,
				0x2,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [6] */
			skipItem {

			},
			/* [7] */
			dataItem {
				0,
				0x2,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [8] */
			skipItem {

			},
			/* [9] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [10] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			}
		}
	}
};

resource 'xmnu' (301, "Icon Colors") {
	versionZero {
		{	/* array ItemExtensions: 11 elements */
			/* [1] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [2] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [3] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [4] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [5] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [6] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [7] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [8] */
			skipItem {

			},
			/* [9] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [10] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [11] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			}
		}
	}
};

resource 'xmnu' (303, "Icon Style") {
	versionZero {
		{	/* array ItemExtensions: 21 elements */
			/* [1] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [2] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [3] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [4] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [5] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [6] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [7] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [8] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [9] */
			skipItem {

			},
			/* [10] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [11] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [12] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [13] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [14] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [15] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [16] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [17] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [18] */
			skipItem {

			},
			/* [19] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [20] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [21] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			}
		}
	}
};

resource 'xmnu' (133, "Resources Menu") {
	versionZero {
		{	/* array ItemExtensions: 12 elements */
			/* [1] */
			dataItem {
				0,
				0x2,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [2] */
			skipItem {

			},
			/* [3] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [4] */
			dataItem {
				0,
				0x1,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [5] */
			dataItem {
				0,
				0x2,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [6] */
			skipItem {

			},
			/* [7] */
			dataItem {
				0,
				0x4,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [8] */
			skipItem {

			},
			/* [9] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [10] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [11] */
			skipItem {

			},
			/* [12] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			}
		}
	}
};

resource 'xmnu' (160, "Aete Menu") {
	versionZero {
		{	/* array ItemExtensions: 23 elements */
			/* [1] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [2] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [3] */
			skipItem {

			},
			/* [4] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [5] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [6] */
			skipItem {

			},
			/* [7] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [8] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [9] */
			skipItem {

			},
			/* [10] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [11] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [12] */
			skipItem {

			},
			/* [13] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [14] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [15] */
			skipItem {

			},
			/* [16] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [17] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [18] */
			skipItem {

			},
			/* [19] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [20] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [21] */
			skipItem {

			},
			/* [22] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [23] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			}
		}
	}
};

resource 'xmnu' (163, "Event other param  options") {
	versionZero {
		{	/* array ItemExtensions: 12 elements */
			/* [1] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [2] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [3] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [4] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [5] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [6] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [7] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [8] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [9] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [10] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [11] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [12] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			}
		}
	}
};

resource 'xmnu' (164, "Class property options") {
	versionZero {
		{	/* array ItemExtensions: 11 elements */
			/* [1] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [2] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [3] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [4] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [5] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [6] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [7] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [8] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [9] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [10] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [11] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			}
		}
	}
};

resource 'xmnu' (162, "Event reply's options") {
	versionZero {
		{	/* array ItemExtensions: 9 elements */
			/* [1] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [2] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [3] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [4] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [5] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [6] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [7] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [8] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [9] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			}
		}
	}
};

resource 'xmnu' (161, "Event direct param options") {
	versionZero {
		{	/* array ItemExtensions: 9 elements */
			/* [1] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [2] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [3] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [4] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [5] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [6] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [7] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [8] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [9] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			}
		}
	}
};

resource 'xmnu' (258, "Menu item Style") {
	versionZero {
		{	/* array ItemExtensions: 10 elements */
			/* [1] */
			dataItem {
				0,
				0x8,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [2] */
			skipItem {

			},
			/* [3] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [4] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [5] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [6] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [7] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [8] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [9] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [10] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			}
		}
	}
};

resource 'xmnu' (259, "Menu item property") {
	versionZero {
		{	/* array ItemExtensions: 7 elements */
			/* [1] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [2] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [3] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [4] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [5] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [6] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [7] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			}
		}
	}
};

resource 'xmnu' (261, "Preferences Font Size") {
	versionZero {
		{	/* array ItemExtensions: 11 elements */
			/* [1] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [2] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [3] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [4] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [5] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [6] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [7] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [8] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [9] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			},
			/* [10] */
			skipItem {

			},
			/* [11] */
			dataItem {
				0,
				0x0,
				currScript,
				0,
				0,
				noHierID,
				sysFont,
				naturalGlyph
			}
		}
	}
};

data 'µMWC' (32000) {
};

resource 'CURS' (1000, "Hand cursor", preload) {
	$"0300 0480 0480 0480 0480 0480 64F8 94AC"
	$"4CAA 240A 2402 1002 0802 0804 0404 0404",
	$"0300 0780 0780 0780 0780 0780 67F8 F7FC"
	$"7FFE 3FFE 3FFE 1FFE 0FFE 0FFC 07FC 07FC",
	{0, 6}
};

resource 'ics#' (9000, "Lasso Tool Icons") {
	{	/* array: 2 elements */
		/* [1] */
		$"0000 03F0 1C0C 2002 4002 8002 800C 8070"
		$"7180 CE00 A800 7000 1000 1000 20",
		/* [2] */
		$"0000 03F0 1DFC 2E06 5003 A003 C00D C076"
		$"71B8 FEC0 FF00 7800 1800 1800 2800 10"
	}
};

resource 'ics#' (9001, "Marquee Tool Icons") {
	{	/* array: 2 elements */
		/* [1] */
		$"0000 79CE 4002 4002 0000 0000 4002 4002"
		$"4002 0000 0000 4002 4002 739E",
		/* [2] */
		$"0000 79CE 4002 4002 0000 0000 4002 4002"
		$"4002 0000 0000 4002 4002 739E"
	}
};

resource 'ics#' (9002, "Text Tool Icons") {
	{	/* array: 2 elements */
		/* [1] */
		$"0000 0000 1FF8 1FF8 1998 1998 0180 0180"
		$"0180 0180 0180 0180 03C0 03C0",
		/* [2] */
		$"0000 0000 1FF8 1FFC 1FFC 1DDC 0DCC 01C0"
		$"01C0 01C0 01C0 01C0 03C0 03E0 01E0"
	}
};

resource 'ics#' (9003, "Pencil Tool Icons") {
	{	/* array: 2 elements */
		/* [1] */
		$"01E0 0110 0210 0320 04E0 0440 0840 0880"
		$"1080 1100 1900 1E00 1C00 1800 10",
		/* [2] */
		$"01E0 01F0 03F8 03F8 07F8 07F0 0FE0 0FE0"
		$"1FC0 1FC0 1F80 1F80 1F00 1E00 1C00 08"
	}
};

resource 'ics#' (9004, "Eraser Tool Icons") {
	{	/* array: 2 elements */
		/* [1] */
		$"0000 0000 01FE 0206 040A 0812 1024 2048"
		$"4090 FF20 8140 8180 FF",
		/* [2] */
		$"0000 0000 01FE 03FF 07FF 0FFF 1FFF 3FFE"
		$"7FFC FFF8 FFF0 FFE0 FFC0 7F80"
	}
};

resource 'ics#' (9005, "Paint Bucket Tool Icons") {
	{	/* array: 2 elements */
		/* [1] */
		$"0E00 1100 1300 1580 1960 1138 211C 438E"
		$"810E 801E 402E 204E 108C 0908 0608",
		/* [2] */
		$"0E00 1100 1300 1780 1FE0 1FF8 3FFC 7FFE"
		$"FFFF FFFF 7FFF 3FFF 1FEF 0FCE 078C 0304"
	}
};

resource 'ics#' (9006, "Eye Dropper Tool Icons") {
	{	/* array: 2 elements */
		/* [1] */
		$"001C 0036 002E 01FE 00BC 0170 0230 0450"
		$"0880 1100 2200 4400 E800 F000 E0",
		/* [2] */
		$"001C 003E 003F 01FF 00FF 01FE 03F8 07F8"
		$"0FE8 1FC0 3F80 7F00 FE00 FC00 F800 70"
	}
};

resource 'ics#' (9007, "Line Tool Icons") {
	{	/* array: 2 elements */
		/* [1] */
		$"0000 0000 0000 0000 C000 3000 0C00 0300"
		$"00C0 0030 000C",
		/* [2] */
		$"0000 0000 0000 0000 C000 7000 1C00 0700"
		$"01C0 0070 001C 0006"
	}
};

resource 'ics#' (9008, "Filled Rect Tool Icons") {
	{	/* array: 2 elements */
		/* [1] */
		$"0000 0000 FFFE FFFE FFFE FFFE FFFE FFFE"
		$"FFFE FFFE FFFE FFFE FFFE FFFE",
		/* [2] */
		$"0000 0000 FFFE FFFF FFFF FFFF FFFF FFFF"
		$"FFFF FFFF FFFF FFFF FFFF FFFF 7FFF"
	}
};

resource 'ics#' (9009, "Empty Rect Tool Icons") {
	{	/* array: 2 elements */
		/* [1] */
		$"0000 0000 FFFE 8002 8002 8002 8002 8002"
		$"8002 8002 8002 8002 8002 FFFE",
		/* [2] */
		$"0000 0000 FFFE FFFF C003 C003 C003 C003"
		$"C003 C003 C003 C003 C003 FFFF 7FFF"
	}
};

resource 'ics#' (9010, "Filled Round Rect Tool ICons") {
	{	/* array: 2 elements */
		/* [1] */
		$"0000 0000 3FF8 7FFC FFFE FFFE FFFE FFFE"
		$"FFFE FFFE FFFE FFFE 7FFC 3FF8",
		/* [2] */
		$"0000 0000 3FF8 7FFC FFFE FFFF FFFF FFFF"
		$"FFFF FFFF FFFF FFFF 7FFF 3FFE 1FFC"
	}
};

resource 'ics#' (9011, "Empty Round Rect Tool Icons") {
	{	/* array: 2 elements */
		/* [1] */
		$"0000 0000 3FF8 4004 8002 8002 8002 8002"
		$"8002 8002 8002 8002 4004 3FF8",
		/* [2] */
		$"0000 0000 3FF8 7FFC E002 C003 C003 C003"
		$"C003 C003 C003 C003 4007 3FFE 1FFC"
	}
};

resource 'ics#' (9012, "Filled Oval Tool Icons") {
	{	/* array: 2 elements */
		/* [1] */
		$"0000 0000 0000 0FE0 3FF8 7FFC FFFE FFFE"
		$"FFFE FFFE 7FFC 3FF8 0FE0",
		/* [2] */
		$"0000 0000 0000 0FE0 3FF8 7FFC FFFE FFFF"
		$"FFFF FFFF 7FFF 3FFE 1FFC 07F0"
	}
};

resource 'ics#' (9013, "Empty Oval Tool Icons") {
	{	/* array: 2 elements */
		/* [1] */
		$"0000 0000 0000 0FE0 3018 4004 8002 8002"
		$"8002 8002 4004 3018 0FE0",
		/* [2] */
		$"0000 0000 0000 0FE0 37F8 580C A002 C003"
		$"C003 C003 4007 301E 1FFC 07F0"
	}
};

resource 'ics#' (9014, "HotSpot") {
	{	/* array: 2 elements */
		/* [1] */
		$"0000 0000 0000 0000 0C30 0E70 07E0 03C0"
		$"03C0 07E0 0E70 0C30",
		/* [2] */
		$"0000 0000 0000 0000 0C30 0E70 07E0 03C0"
		$"03C0 07E0 0E70 0C30"
	}
};

resource 'ics4' (9000, "Lasso Tool Icons") {
	$"0000 0000 0000 0000 0000 00FF FFFF 0000"
	$"000F FF0D DDDD FF00 00F0 DDD0 0000 0DF0"
	$"0F0D 0000 0000 00FD F0D0 0000 0000 00FD"
	$"FD00 0000 0000 FF0D FD00 0000 0FFF 0DD0"
	$"0FFF 000F F0DD D000 FFDD FFF0 DD00 0000"
	$"FDFD FDDD 0000 0000 0FFF D000 0000 0000"
	$"000F D000 0000 0000 000F D000 0000 0000"
	$"00F0 D000 0000 0000 000D"
};

resource 'ics4' (9001, "Marquee Tool Icons") {
	$"0000 0000 0000 0000 0FFF F00F FF00 FFF0"
	$"0F00 0000 0000 00F0 0F00 0000 0000 00F0"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0F00 0000 0000 00F0 0F00 0000 0000 00F0"
	$"0F00 0000 0000 00F0 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0F00 0000 0000 00F0"
	$"0F00 0000 0000 00F0 0FFF 00FF F00F FFF0"
};

resource 'ics4' (9002, "Text Tool Icons") {
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0006 6666 6666 6000 0006 6666 6666 6D00"
	$"0006 6DD6 6DD6 6D00 0006 6D06 6D06 6D00"
	$"0000 DD06 6D00 DD00 0000 0006 6D00 0000"
	$"0000 0006 6D00 0000 0000 0006 6D00 0000"
	$"0000 0006 6D00 0000 0000 0006 6D00 0000"
	$"0000 0066 6600 0000 0000 0066 66D0 0000"
	$"0000 000D DDD0"
};

resource 'ics4' (9003, "Pencil Tool Icons") {
	$"0000 000F FFF0 0000 0000 000F CCCF 0000"
	$"0000 00FC CCCF D000 0000 00FF CCFD D000"
	$"0000 0F11 FFFD D000 0000 0F11 1FDD 0000"
	$"0000 F111 1FD0 0000 0000 F111 FDD0 0000"
	$"000F 1111 FD00 0000 000F 111F DD00 0000"
	$"000F F11F D000 0000 000F FFFD D000 0000"
	$"000F FFDD 0000 0000 000F FDD0 0000 0000"
	$"000F DD00 0000 0000 0000 D0"
};

resource 'ics4' (9004, "Eraser Tool Icons") {
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 000F FFFF FFF0 0000 00FC CCCC CFFD"
	$"0000 0FCC CCCC FCFD 0000 FCCC CCCF CCFD"
	$"000F CCCC CCFC CFDD 00FC CCCC CFCC FDD0"
	$"0FCC CCCC FCCF DD00 FFFF FFFF CCFD D000"
	$"FCCC CCCF CFDD 0000 FCCC CCCF FDD0 0000"
	$"FFFF FFFF DD00 0000 0DDD DDDD D0"
};

resource 'ics4' (9005, "Paint Bucket Tool Icons") {
	$"0000 FFF0 0000 0000 000F 000F 0000 0000"
	$"000F 00FF 0000 0000 000F 0FCF F000 0000"
	$"000F FCCF CF60 0000 000F CCCF DDF6 6000"
	$"00FC CDCF EDDF 6600 0FCC CDFE FDEE F660"
	$"FCCD CDDF EDEE F66D FCDC DDDD EEEF 666D"
	$"0FDD DDED EEFD 666D 00FE DEEE EFDD 666D"
	$"000F EEEE FDD0 66DD 0000 FEEF DD00 6DD0"
	$"0000 0FFD D000 6D00 0000 00DD 0000 0D"
};

resource 'ics4' (9006, "Eye Dropper Tool Icons") {
	$"0000 0000 000F FF00 0000 0000 00FF CFF0"
	$"0000 0000 00FC FFFD 0000 000F FFFF FFFD"
	$"0000 0000 FCFF FFDD 0000 000F 0FFF DDD0"
	$"0000 00F0 CCFF D000 0000 0F0C CFDF D000"
	$"0000 F0CC FDD0 D000 000F 0CCF DD00 0000"
	$"00F0 CCFD D000 0000 0F0C CFDD 0000 0000"
	$"F33C FDD0 0000 0000 F33F DD00 0000 0000"
	$"3FFD D000 0000 0000 0DDD"
};

resource 'ics4' (9007, "Line Tool Icons") {
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"FF00 0000 0000 0000 0DFF 0000 0000 0000"
	$"000D FF00 0000 0000 0000 0DFF 0000 0000"
	$"0000 000D FF00 0000 0000 0000 0DFF 0000"
	$"0000 0000 000D FF00 0000 0000 0000 0DD0"
};

resource 'ics4' (9008, "Filled Rect Tool Icons") {
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"FFFF FFFF FFFF FFF0 F111 1111 1111 11FD"
	$"F111 1111 1111 11FD F111 1111 1111 11FD"
	$"F111 1111 1111 11FD F111 1111 1111 11FD"
	$"F111 1111 1111 11FD F111 1111 1111 11FD"
	$"F111 1111 1111 11FD F111 1111 1111 11FD"
	$"F111 1111 1111 11FD FFFF FFFF FFFF FFFD"
	$"0DDD DDDD DDDD DDDD"
};

resource 'ics4' (9009, "Empty Rect Tool Icons") {
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"FFFF FFFF FFFF FFF0 FDDD DDDD DDDD DDFD"
	$"FD00 0000 0000 00FD FD00 0000 0000 00FD"
	$"FD00 0000 0000 00FD FD00 0000 0000 00FD"
	$"FD00 0000 0000 00FD FD00 0000 0000 00FD"
	$"FD00 0000 0000 00FD FD00 0000 0000 00FD"
	$"FD00 0000 0000 00FD FFFF FFFF FFFF FFFD"
	$"0DDD DDDD DDDD DDDD"
};

resource 'ics4' (9010, "Filled Round Rect Tool ICons") {
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"00FF FFFF FFFF F000 0F11 1111 1111 1F00"
	$"F111 1111 1111 11F0 F111 1111 1111 11FD"
	$"F111 1111 1111 11FD F111 1111 1111 11FD"
	$"F111 1111 1111 11FD F111 1111 1111 11FD"
	$"F111 1111 1111 11FD F111 1111 1111 11FD"
	$"0F11 1111 1111 1FDD 00FF FFFF FFFF FDD0"
	$"000D DDDD DDDD DD"
};

resource 'ics4' (9011, "Empty Round Rect Tool Icons") {
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"00FF FFFF FFFF F000 0FDD DDDD DDDD DF00"
	$"FDD0 0000 0000 00F0 FD00 0000 0000 00FD"
	$"FD00 0000 0000 00FD FD00 0000 0000 00FD"
	$"FD00 0000 0000 00FD FD00 0000 0000 00FD"
	$"FD00 0000 0000 00FD FD00 0000 0000 00FD"
	$"0F00 0000 0000 0FDD 00FF FFFF FFFF FDD0"
	$"000D DDDD DDDD DD"
};

resource 'ics4' (9012, "Filled Oval Tool Icons") {
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 FFFF FFF0 0000"
	$"00FF 1111 111F F000 0F11 1111 1111 1F00"
	$"F111 1111 1111 11F0 F111 1111 1111 11FD"
	$"F111 1111 1111 11FD F111 1111 1111 11FD"
	$"0F11 1111 1111 1FDD 00FF 1111 111F FDD0"
	$"000D FFFF FFFD DD00 0000 0DDD DDDD"
};

resource 'ics4' (9013, "Empty Oval Tool Icons") {
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 FFFF FFF0 0000"
	$"00FF 0DDD DDDF F000 0F0D D000 0000 DF00"
	$"F0D0 0000 0000 00F0 FD00 0000 0000 00FD"
	$"FD00 0000 0000 00FD FD00 0000 0000 00FD"
	$"0F00 0000 0000 0FDD 00FF 0000 000F FDD0"
	$"000D FFFF FFFD DD00 0000 0DDD DDDD"
};

resource 'ics4' (9014) {
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 3300 0033 0000 0000 3330 0333 0000"
	$"0000 0333 3330 0000 0000 0033 3300 0000"
	$"0000 0033 3300 0000 0000 0333 3330 0000"
	$"0000 3330 0333 0000 0000 3300 0033"
};

resource 'ics8' (9000, "Lasso Tool Icons") {
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 FFFF FFFF FFFF 0000 0000"
	$"0000 00FF FFFF 00FA FAFA FAFA FFFF 0000"
	$"0000 FF00 FAFA FA00 0000 0000 00FA FF00"
	$"00FF 00FA 0000 0000 0000 0000 0000 FFFA"
	$"FF00 FA00 0000 0000 0000 0000 0000 FFFA"
	$"FFFA 0000 0000 0000 0000 0000 FFFF 00FA"
	$"FFFA 0000 0000 0000 00FF FFFF 00FA FA00"
	$"00FF FFFF 0000 00FF FF00 FAFA FA00 0000"
	$"FFFF FAFA FFFF FF00 FAFA 0000 0000 0000"
	$"FFFA FFFA FFFA FAFA 0000 0000 0000 0000"
	$"00FF FFFF FA00 0000 0000 0000 0000 0000"
	$"0000 00FF FA00 0000 0000 0000 0000 0000"
	$"0000 00FF FA00 0000 0000 0000 0000 0000"
	$"0000 FF00 FA00 0000 0000 0000 0000 0000"
	$"0000 00FA"
};

resource 'ics8' (9001, "Marquee Tool Icons") {
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"00FF FFFF FF00 00FF FFFF 0000 FFFF FF00"
	$"00FF 0000 0000 0000 0000 0000 0000 FF00"
	$"00FF 0000 0000 0000 0000 0000 0000 FF00"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"00FF 0000 0000 0000 0000 0000 0000 FF00"
	$"00FF 0000 0000 0000 0000 0000 0000 FF00"
	$"00FF 0000 0000 0000 0000 0000 0000 FF00"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"00FF 0000 0000 0000 0000 0000 0000 FF00"
	$"00FF 0000 0000 0000 0000 0000 0000 FF00"
	$"00FF FFFF 0000 FFFF FF00 00FF FFFF FF"
};

resource 'ics8' (9002, "Text Tool Icons") {
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 00EB EBEB EBEB EBEB EBEB EB00 0000"
	$"0000 00EB EBEB EBEB EBEB EBEB EBFA 0000"
	$"0000 00EB EBFA FAEB EBFA FAEB EBFA 0000"
	$"0000 00EB EBFA 00EB EBFA 00EB EBFA 0000"
	$"0000 0000 FAFA 00EB EBFA 0000 FAFA 0000"
	$"0000 0000 0000 00EB EBFA 0000 0000 0000"
	$"0000 0000 0000 00EB EBFA 0000 0000 0000"
	$"0000 0000 0000 00EB EBFA 0000 0000 0000"
	$"0000 0000 0000 00EB EBFA 0000 0000 0000"
	$"0000 0000 0000 00EB EBFA 0000 0000 0000"
	$"0000 0000 0000 EBEB EBEB 0000 0000 0000"
	$"0000 0000 0000 EBEB EBEB FA00 0000 0000"
	$"0000 0000 0000 00FA FAFA FA"
};

resource 'ics8' (9003, "Pencil Tool Icons") {
	$"0000 0000 0000 00FF FFFF FF00 0000 0000"
	$"0000 0000 0000 00FF 0E0E 0EFF 0000 0000"
	$"0000 0000 0000 FF0E 0E0E 0EFF FA00 0000"
	$"0000 0000 0000 FFFF 0E0E FFFA FA00 0000"
	$"0000 0000 00FF 0B0B FFFF FFFA FA00 0000"
	$"0000 0000 00FF 0B0B 0BFF FAFA 0000 0000"
	$"0000 0000 FF0B 0B0B 0BFF FA00 0000 0000"
	$"0000 0000 FF0B 0B0B FFFA FA00 0000 0000"
	$"0000 00FF 0B0B 0B0B FFFA 0000 0000 0000"
	$"0000 00FF 0B0B 0BFF FAFA 0000 0000 0000"
	$"0000 00FF FF0B 0BFF FA00 0000 0000 0000"
	$"0000 00FF FFFF FFFA FA00 0000 0000 0000"
	$"0000 00FF FFFF FAFA 0000 0000 0000 0000"
	$"0000 00FF FFFA FA00 0000 0000 0000 0000"
	$"0000 00FF FAFA 0000 0000 0000 0000 0000"
	$"0000 0000 FA"
};

resource 'ics8' (9004, "Eraser Tool Icons") {
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 00FF FFFF FFFF FFFF FF00"
	$"0000 0000 0000 FF0E 0E0E 0E0E 0EFF FFFA"
	$"0000 0000 00FF 0E0E 0E0E 0E0E FF0E FFFA"
	$"0000 0000 FF0E 0E0E 0E0E 0EFF 0E0E FFFA"
	$"0000 00FF 0E0E 0E0E 0E0E FF0E 0EFF FAFA"
	$"0000 FF0E 0E0E 0E0E 0EFF 0E0E FFFA FA00"
	$"00FF 0E0E 0E0E 0E0E FF0E 0EFF FAFA 0000"
	$"FFFF FFFF FFFF FFFF 0E0E FFFA FA00 0000"
	$"FF0E 0E0E 0E0E 0EFF 0EFF FAFA 0000 0000"
	$"FF0E 0E0E 0E0E 0EFF FFFA FA00 0000 0000"
	$"FFFF FFFF FFFF FFFF FAFA 0000 0000 0000"
	$"00FA FAFA FAFA FAFA FA"
};

resource 'ics8' (9005, "Paint Bucket Tool Icons") {
	$"0000 0000 FFFF FF00 0000 0000 0000 0000"
	$"0000 00FF 0000 00FF 0000 0000 0000 0000"
	$"0000 00FF 0000 FFFF 0000 0000 0000 0000"
	$"0000 00FF 00FF 2BFF FF00 0000 0000 0000"
	$"0000 00FF FF2B 2BFF 2BFF EB00 0000 0000"
	$"0000 00FF 2B2B 2BFF F9F9 FFEB EB00 0000"
	$"0000 FF2B 2BF9 2BFF FCF9 F9FF EBEB 0000"
	$"00FF 2B2B 2BF9 FFFC FFF9 FCFC FFEB EB00"
	$"FF2B 2BF9 2BF9 F9FF FCF9 FCFC FFEB EBFA"
	$"FF2B F92B F9F9 F9F9 FCFC FCFF EBEB EBFA"
	$"00FF F9F9 F9F9 FCF9 FCFC FFFA EBEB EBFA"
	$"0000 FFFC F9FC FCFC FCFF FAFA EBEB EBFA"
	$"0000 00FF FCFC FCFC FFFA FA00 EBEB FAFA"
	$"0000 0000 FFFC FCFF FAFA 0000 EBFA FA00"
	$"0000 0000 00FF FFFA FA00 0000 EBFA 0000"
	$"0000 0000 0000 FAFA 0000 0000 00FA"
};

resource 'ics8' (9006, "Eye Dropper Tool Icons") {
	$"0000 0000 0000 0000 0000 00FF FFFF 0000"
	$"0000 0000 0000 0000 0000 FFFF F8FF FF00"
	$"0000 0000 0000 0000 0000 FFF8 FFFF FFFA"
	$"0000 0000 0000 00FF FFFF FFFF FFFF FFFA"
	$"0000 0000 0000 0000 FFF8 FFFF FFFF FAFA"
	$"0000 0000 0000 00FF 00FF FFFF FAFA FA00"
	$"0000 0000 0000 FF00 F6F6 FFFF FA00 0000"
	$"0000 0000 00FF 00F6 F6FF FAFF FA00 0000"
	$"0000 0000 FF00 F6F6 FFFA FA00 FA00 0000"
	$"0000 00FF 00F6 F6FF FAFA 0000 0000 0000"
	$"0000 FF00 F6F6 FFFA FA00 0000 0000 0000"
	$"00FF 00F6 F6FF FAFA 0000 0000 0000 0000"
	$"FFD7 D7F6 FFFA FA00 0000 0000 0000 0000"
	$"FFD7 D7FF FAFA 0000 0000 0000 0000 0000"
	$"D7FF FFFA FA00 0000 0000 0000 0000 0000"
	$"00FA FAFA"
};

resource 'ics8' (9007, "Line Tool Icons") {
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"FFFF 0000 0000 0000 0000 0000 0000 0000"
	$"00FA FFFF 0000 0000 0000 0000 0000 0000"
	$"0000 00FA FFFF 0000 0000 0000 0000 0000"
	$"0000 0000 00FA FFFF 0000 0000 0000 0000"
	$"0000 0000 0000 00FA FFFF 0000 0000 0000"
	$"0000 0000 0000 0000 00FA FFFF 0000 0000"
	$"0000 0000 0000 0000 0000 00FA FFFF 0000"
	$"0000 0000 0000 0000 0000 0000 00FA FA"
};

resource 'ics8' (9008, "Filled Rect Tool Icons") {
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FF00"
	$"FF05 0505 0505 0505 0505 0505 0505 FFFA"
	$"FF05 0505 0505 0505 0505 0505 0505 FFFA"
	$"FF05 0505 0505 0505 0505 0505 0505 FFFA"
	$"FF05 0505 0505 0505 0505 0505 0505 FFFA"
	$"FF05 0505 0505 0505 0505 0505 0505 FFFA"
	$"FF05 0505 0505 0505 0505 0505 0505 FFFA"
	$"FF05 0505 0505 0505 0505 0505 0505 FFFA"
	$"FF05 0505 0505 0505 0505 0505 0505 FFFA"
	$"FF05 0505 0505 0505 0505 0505 0505 FFFA"
	$"FF05 0505 0505 0505 0505 0505 0505 FFFA"
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFA"
	$"00FA FAFA FAFA FAFA FAFA FAFA FAFA FAFA"
};

resource 'ics8' (9009, "Empty Rect Tool Icons") {
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FF00"
	$"FFFA FAFA FAFA FAFA FAFA FAFA FAFA FFFA"
	$"FFFA 0000 0000 0000 0000 0000 0000 FFFA"
	$"FFFA 0000 0000 0000 0000 0000 0000 FFFA"
	$"FFFA 0000 0000 0000 0000 0000 0000 FFFA"
	$"FFFA 0000 0000 0000 0000 0000 0000 FFFA"
	$"FFFA 0000 0000 0000 0000 0000 0000 FFFA"
	$"FFFA 0000 0000 0000 0000 0000 0000 FFFA"
	$"FFFA 0000 0000 0000 0000 0000 0000 FFFA"
	$"FFFA 0000 0000 0000 0000 0000 0000 FFFA"
	$"FFFA 0000 0000 0000 0000 0000 0000 FFFA"
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFA"
	$"00FA FAFA FAFA FAFA FAFA FAFA FAFA FAFA"
};

resource 'ics8' (9010, "Filled Round Rect Tool ICons") {
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 FFFF FFFF FFFF FFFF FFFF FF00 0000"
	$"00FF 0505 0505 0505 0505 0505 05FF 0000"
	$"FF05 0505 0505 0505 0505 0505 0505 FF00"
	$"FF05 0505 0505 0505 0505 0505 0505 FFFA"
	$"FF05 0505 0505 0505 0505 0505 0505 FFFA"
	$"FF05 0505 0505 0505 0505 0505 0505 FFFA"
	$"FF05 0505 0505 0505 0505 0505 0505 FFFA"
	$"FF05 0505 0505 0505 0505 0505 0505 FFFA"
	$"FF05 0505 0505 0505 0505 0505 0505 FFFA"
	$"FF05 0505 0505 0505 0505 0505 0505 FFFA"
	$"00FF 0505 0505 0505 0505 0505 05FF FAFA"
	$"0000 FFFF FFFF FFFF FFFF FFFF FFFA FA00"
	$"0000 00FA FAFA FAFA FAFA FAFA FAFA"
};

resource 'ics8' (9011, "Empty Round Rect Tool Icons") {
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 FFFF FFFF FFFF FFFF FFFF FF00 0000"
	$"00FF FAFA FAFA FAFA FAFA FAFA FAFF 0000"
	$"FFFA FA00 0000 0000 0000 0000 0000 FF00"
	$"FFFA 0000 0000 0000 0000 0000 0000 FFFA"
	$"FFFA 0000 0000 0000 0000 0000 0000 FFFA"
	$"FFFA 0000 0000 0000 0000 0000 0000 FFFA"
	$"FFFA 0000 0000 0000 0000 0000 0000 FFFA"
	$"FFFA 0000 0000 0000 0000 0000 0000 FFFA"
	$"FFFA 0000 0000 0000 0000 0000 0000 FFFA"
	$"FFFA 0000 0000 0000 0000 0000 0000 FFFA"
	$"00FF 0000 0000 0000 0000 0000 00FF FAFA"
	$"0000 FFFF FFFF FFFF FFFF FFFF FFFA FA00"
	$"0000 00FA FAFA FAFA FAFA FAFA FAFA"
};

resource 'ics8' (9012, "Filled Oval Tool Icons") {
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 FFFF FFFF FFFF FF00 0000 0000"
	$"0000 FFFF 0505 0505 0505 05FF FF00 0000"
	$"00FF 0505 0505 0505 0505 0505 05FF 0000"
	$"FF05 0505 0505 0505 0505 0505 0505 FF00"
	$"FF05 0505 0505 0505 0505 0505 0505 FFFA"
	$"FF05 0505 0505 0505 0505 0505 0505 FFFA"
	$"FF05 0505 0505 0505 0505 0505 0505 FFFA"
	$"00FF 0505 0505 0505 0505 0505 05FF FAFA"
	$"0000 FFFF 0505 0505 0505 05FF FFFA FA00"
	$"0000 00FA FFFF FFFF FFFF FFFA FAFA 0000"
	$"0000 0000 00FA FAFA FAFA FAFA"
};

resource 'ics8' (9013, "Empty Oval Tool Icons") {
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 FFFF FFFF FFFF FF00 0000 0000"
	$"0000 FFFF 00FA FAFA FAFA FAFF FF00 0000"
	$"00FF 00FA FA00 0000 0000 0000 FAFF 0000"
	$"FF00 FA00 0000 0000 0000 0000 0000 FF00"
	$"FFFA 0000 0000 0000 0000 0000 0000 FFFA"
	$"FFFA 0000 0000 0000 0000 0000 0000 FFFA"
	$"FFFA 0000 0000 0000 0000 0000 0000 FFFA"
	$"00FF 0000 0000 0000 0000 0000 00FF FAFA"
	$"0000 FFFF 0000 0000 0000 00FF FFFA FA00"
	$"0000 00FA FFFF FFFF FFFF FFFA FAFA 0000"
	$"0000 0000 00FA FAFA FAFA FAFA"
};

resource 'ics8' (9014, "Cursor Tools") {
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 D8D8 0000 0000 D8D8 0000 0000"
	$"0000 0000 D8D8 D800 00D8 D8D8 0000 0000"
	$"0000 0000 00D8 D8D8 D8D8 D800 0000 0000"
	$"0000 0000 0000 D8D8 D8D8 0000 0000 0000"
	$"0000 0000 0000 D8D8 D8D8 0000 0000 0000"
	$"0000 0000 00D8 D8D8 D8D8 D800 0000 0000"
	$"0000 0000 D8D8 D800 00D8 D8D8 0000 0000"
	$"0000 0000 D8D8 0000 0000 D8D8"
};

data 'crsr' (9000, "Lasso Cursor") {
	$"8001 0000 0060 0000 0092 0000 0000 0000"            /* Ä....`...í...... */
	$"0000 0000 0000 03F0 1C0C 2002 4002 8002"            /* ......... .@.Ä. */
	$"800C 8070 7180 CE00 A800 7000 1000 1000"            /* Ä.ÄpqÄŒ.®.p..... */
	$"2000 0000 0000 03F0 1FFC 3FFE 7FFE FFFE"            /*  .......¸?˛.˛ˇ˛ */
	$"FFFC FFF0 7F80 FE00 F800 7000 1000 1000"            /* ˇ¸ˇ.Ä˛.¯.p..... */
	$"2000 0000 000E 0002 0000 0000 0000 0000"            /*  ............... */
	$"0000 0000 8002 0000 0000 0010 0010 0000"            /* ....Ä........... */
	$"0000 0000 0000 0048 0000 0048 0000 0000"            /* .......H...H.... */
	$"0001 0001 0001 0000 0000 0000 00B2 0000"            /* .............≤.. */
	$"0000 0000 03F0 1C0C 2002 4002 8002 800C"            /* ....... .@.Ä.Ä. */
	$"8070 7180 CE00 A800 7000 1000 1000 2000"            /* ÄpqÄŒ.®.p..... . */
	$"0000 0000 0000 0000 0001 0000 FFFF FFFF"            /* ............ˇˇˇˇ */
	$"FFFF 0001 0000 0000 0000"                           /* ˇˇ........ */
};

data 'crsr' (9001, "Eraser Tool Cursor") {
	$"8001 0000 0060 0000 0092 0000 0000 0000"            /* Ä....`...í...... */
	$"0000 0000 0000 3FFE 2002 2002 2002 2002"            /* ......?˛ . . . . */
	$"2002 2002 2002 2002 2002 2002 2002 3FFE"            /*  . . . . . . .?˛ */
	$"0000 0000 0000 3FFE 3FFE 3006 3006 3006"            /* ......?˛?˛0.0.0. */
	$"3006 3006 3006 3006 3006 3006 3FFE 3FFE"            /* 0.0.0.0.0.0.?˛?˛ */
	$"0000 0000 0002 0003 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 8002 0000 0000 0010 0010 0000"            /* ....Ä........... */
	$"0000 0000 0000 0048 0000 0048 0000 0000"            /* .......H...H.... */
	$"0001 0001 0001 0000 0000 0000 00B2 0000"            /* .............≤.. */
	$"0000 0000 3FFE 2002 2002 2002 2002 2002"            /* ....?˛ . . . . . */
	$"2002 2002 2002 2002 2002 2002 3FFE 0000"            /*  . . . . . .?˛.. */
	$"0000 0001 521C 0000 0001 0000 FFFF FFFF"            /* ....R.......ˇˇˇˇ */
	$"FFFF 0001 0000 0000 0000"                           /* ˇˇ........ */
};

data 'crsr' (9002, "Pencil Tool Cursor") {
	$"8001 0000 0060 0000 0092 0000 0000 0000"            /* Ä....`...í...... */
	$"0000 0000 01E0 0110 0210 0320 04E0 0440"            /* .....‡..... .‡.@ */
	$"0840 0880 1080 1100 1900 1E00 1C00 1800"            /* .@.Ä.Ä.......... */
	$"1000 0000 01E0 01F0 03F0 03E0 07E0 07C0"            /* .....‡...‡.‡.¿ */
	$"0FC0 0F80 1F80 1F00 1F00 1E00 1C00 1800"            /* .¿.Ä.Ä.......... */
	$"1000 0000 000E 0003 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 8004 0000 0000 0010 0010 0000"            /* ....Ä........... */
	$"0000 0000 0000 0048 0000 0048 0000 0000"            /* .......H...H.... */
	$"0002 0001 0002 0000 0000 0000 00D2 0000"            /* .............“.. */
	$"0000 0003 FC00 0003 5700 000D 5700 000F"            /* ....¸...W...W... */
	$"5C00 003A FC00 003A B000 00EA B000 00EA"            /* \..:¸..:∞..Í∞..Í */
	$"C000 03AA C000 03AB 0000 03EB 0000 03FC"            /* ¿..™¿..´...Î...¸ */
	$"0000 03F0 0000 03C0 0000 0300 0000 0000"            /* ......¿........ */
	$"0000 0000 0000 0000 0003 0000 FFFF FFFF"            /* ............ˇˇˇˇ */
	$"FFFF 0001 FFFF 6666 3333 0002 FFFF FFFF"            /* ˇˇ..ˇˇff33..ˇˇˇˇ */
	$"0000 0003 0000 0000 0000"                           /* .......... */
};

data 'crsr' (9003, "Eye Dropper Tool Cursor") {
	$"8001 0000 0060 0000 0092 0000 0000 0000"            /* Ä....`...í...... */
	$"0000 0000 001C 0036 002E 01FE 00BC 0170"            /* .......6...˛.º.p */
	$"0230 0450 0880 1100 2200 4400 E800 F000"            /* .0.P.Ä..".D.Ë.. */
	$"E000 0000 001C 003E 003E 01FE 00FC 01F0"            /* ‡......>.>.˛.¸. */
	$"03F0 07D0 0F80 1F00 3E00 7C00 F800 F000"            /* ..–.Ä..>.|.¯.. */
	$"E000 0000 000E 0000 0000 0000 0000 0000"            /* ‡............... */
	$"0000 0000 8008 0000 0000 0010 0010 0000"            /* ....Ä........... */
	$"0000 0000 0000 0048 0000 0048 0000 0000"            /* .......H...H.... */
	$"0004 0001 0004 0000 0000 0000 0112 0000"            /* ................ */
	$"0000 0000 0000 000F FF00 0000 0000 00FF"            /* ........ˇ......ˇ */
	$"3FF0 0000 0000 00F3 FFF0 0000 000F FFFF"            /* ?.....Ûˇ....ˇˇ */
	$"FFF0 0000 0000 F3FF FF00 0000 000F 0FFF"            /* ˇ....Ûˇˇ......ˇ */
	$"0000 0000 00F0 11FF 0000 0000 0F01 1F0F"            /* ......ˇ........ */
	$"0000 0000 F011 F000 0000 000F 011F 0000"            /* .............. */
	$"0000 00F0 11F0 0000 0000 0F01 1F00 0000"            /* .............. */
	$"0000 F221 F000 0000 0000 F22F 0000 0000"            /* ..Ú!.....Ú/.... */
	$"0000 2FF0 0000 0000 0000 0000 0000 0000"            /* ../............ */
	$"0000 0000 0000 0000 0004 0000 FFFF FFFF"            /* ............ˇˇˇˇ */
	$"FFFF 0001 BBBB BBBB BBBB 0002 DDDD 0000"            /* ˇˇ..ªªªªªª..››.. */
	$"0000 0003 8888 8888 8888 000F 0000 0000"            /* ....àààààà...... */
	$"0000"                                               /* .. */
};

data 'crsr' (9004, "Grabber Hand Tool Cursor") {
	$"8001 0000 0060 0000 0092 0000 0000 0000"            /* Ä....`...í...... */
	$"0000 0000 0180 1A70 2648 264A 124D 1249"            /* .....Ä.p&H&J.M.I */
	$"6809 9801 8802 4002 2002 2004 1004 0808"            /* h∆ò.à.@. . ..... */
	$"0408 0408 0180 1BF0 3FF8 3FFA 1FFF 1FFF"            /* .....Ä.?¯?˙.ˇ.ˇ */
	$"7FFF FFFF FFFE 7FFE 3FFE 3FFC 1FFC 0FF8"            /* .ˇˇˇˇ˛.˛?˛?¸.¸.¯ */
	$"07F8 07F8 0009 0008 0000 0000 0000 0000"            /* .¯.¯.∆.......... */
	$"0000 0000 8004 0000 0000 0010 0010 0000"            /* ....Ä........... */
	$"0000 0000 0000 0048 0000 0048 0000 0000"            /* .......H...H.... */
	$"0002 0001 0002 0000 0000 0000 00D2 0000"            /* .............“.. */
	$"0000 0003 C000 03CD 7F00 0D7D 75C0 0D7D"            /* ....¿..Õ...}u¿.} */
	$"75CC 035D 75F7 035D 75D7 3CD5 55D7 D7D5"            /* uÃ.]u˜.]u◊<’U◊◊’ */
	$"5557 D5D5 555C 3555 555C 0D55 555C 0D55"            /* UW’’U\5UU\.UU\.U */
	$"5570 0355 5570 00D5 55C0 0035 55C0 0035"            /* Up.UUp.’U¿.5U¿.5 */
	$"55C0 0000 0000 0000 0002 0000 FFFF FFFF"            /* U¿..........ˇˇˇˇ */
	$"FFFF 0001 FFFF CCCC 9999 0003 0000 0000"            /* ˇˇ..ˇˇÃÃôô...... */
	$"0000"                                               /* .. */
};

data 'crsr' (9005, "Cross Hair Cursor") {
	$"8001 0000 0060 0000 0092 0000 0000 0000"            /* Ä....`...í...... */
	$"0000 0000 0000 0100 0100 0100 0100 0100"            /* ................ */
	$"0100 7FFC 0100 0100 0100 0100 0100 0100"            /* ...¸............ */
	$"0000 0000 0100 0380 0380 0380 0380 0380"            /* .......Ä.Ä.Ä.Ä.Ä */
	$"7FFC FFFE 7FFC 0380 0380 0380 0380 0380"            /* .¸ˇ˛.¸.Ä.Ä.Ä.Ä.Ä */
	$"0100 0000 0007 0007 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 8002 0000 0000 0010 0010 0000"            /* ....Ä........... */
	$"0000 0000 0000 0048 0000 0048 0000 0000"            /* .......H...H.... */
	$"0001 0001 0001 0000 0000 0000 00B2 0000"            /* .............≤.. */
	$"0000 0000 0100 0100 0100 0100 0100 0100"            /* ................ */
	$"7FFC 0100 0100 0100 0100 0100 0100 0000"            /* .¸.............. */
	$"0000 0000 F602 0000 0001 0000 FFFF FFFF"            /* ....ˆ.......ˇˇˇˇ */
	$"FFFF 0001 0000 0000 0000"                           /* ˇˇ........ */
};

data 'crsr' (9006, "Paint Bucket Tool Cursor") {
	$"8001 0000 0060 0000 0092 0000 0000 0000"            /* Ä....`...í...... */
	$"0000 0000 0E00 1100 1300 1580 1960 1138"            /* ...........Ä.`.8 */
	$"211C 438E 810E 801E 402E 204E 108C 0908"            /* !.CéÅ.Ä.@. N.å∆. */
	$"0608 0000 0E00 1100 1300 1780 1FE0 1FF8"            /* ...........Ä.‡.¯ */
	$"3FFC 7FFE FFFE FFFE 7FEE 3FCE 1F8C 0F08"            /* ?¸.˛ˇ˛ˇ˛.Ó?Œ.å.. */
	$"0608 0000 000E 000C 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 8008 0000 0000 0010 0010 0000"            /* ....Ä........... */
	$"0000 0000 0000 0048 0000 0048 0000 0000"            /* .......H...H.... */
	$"0004 0001 0004 0000 0000 0000 0112 0000"            /* ................ */
	$"0000 0000 FFF0 0000 0000 000F 000F 0000"            /* ....ˇ.......... */
	$"0000 000F 00FF 0000 0000 000F 0F2F F000"            /* .....ˇ......./. */
	$"0000 000F F22F 2F30 0000 000F 222F 11F3"            /* ....Ú//0...."/.Û */
	$"3000 00F2 212F F11F 3300 0F22 21FF F1FF"            /* 0..Ú!/Ò.3.."!ˇÒˇ */
	$"F330 F221 211F F1FF F330 F212 1111 FFFF"            /* Û0Ú!!.ÒˇÛ0Ú...ˇˇ */
	$"3330 0F11 11F1 FFF0 3330 00FF 1FFF FF00"            /* 30...Òˇ30.ˇ.ˇˇ. */
	$"3330 000F FFFF F000 3300 0000 FFFF 0000"            /* 30..ˇˇ.3...ˇˇ.. */
	$"3000 0000 0FF0 0000 3000 0000 0000 0000"            /* 0......0....... */
	$"0000 0000 0000 0000 0004 0000 FFFF FFFF"            /* ............ˇˇˇˇ */
	$"FFFF 0001 7777 7777 7777 0002 BBBB BBBB"            /* ˇˇ..wwwwww..ªªªª */
	$"BBBB 0003 0000 0000 DDDD 000F 0000 0000"            /* ªª......››...... */
	$"0000"                                               /* .. */
};

data 'crsr' (9007, "Edit Cursor") {
	$"8001 0000 0060 0000 0092 0000 0000 0000"            /* Ä....`...í...... */
	$"0000 0000 0000 07F0 0080 0080 0080 0080"            /* ........Ä.Ä.Ä.Ä */
	$"0080 0080 0080 0080 0080 0080 07F0 0000"            /* .Ä.Ä.Ä.Ä.Ä.Ä... */
	$"0000 0000 07F0 0FF8 07F0 01C0 01C0 01C0"            /* ......¯..¿.¿.¿ */
	$"01C0 01C0 01C0 01C0 01C0 07F0 0FF8 07F0"            /* .¿.¿.¿.¿.¿..¯. */
	$"0000 0000 000B 0008 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 8002 0000 0000 0010 0010 0000"            /* ....Ä........... */
	$"0000 0000 0000 0048 0000 0048 0000 0000"            /* .......H...H.... */
	$"0001 0001 0001 0000 0000 0000 00B2 0000"            /* .............≤.. */
	$"0000 0000 07F0 0080 0080 0080 0080 0080"            /* ......Ä.Ä.Ä.Ä.Ä */
	$"0080 0080 0080 0080 0080 07F0 0000 0000"            /* .Ä.Ä.Ä.Ä.Ä..... */
	$"0000 0003 F5D8 0000 0001 0000 FFFF FFFF"            /* ....ıÿ......ˇˇˇˇ */
	$"FFFF 0001 0000 0000 0000"                           /* ˇˇ........ */
};

data 'crsr' (9010, "Closed Grabber Hand Tool Cursor") {
	$"8001 0000 0060 0000 0092 0000 0000 0000"            /* Ä....`...í...... */
	$"0000 0000 0000 0000 0000 0000 0DB0 124C"            /* .............∞.L */
	$"100A 0802 1802 2002 2002 2004 1004 0808"            /* .¬.... . . ..... */
	$"0408 0408 0000 0000 0000 0000 0DB0 1FFC"            /* .............∞.¸ */
	$"1FFE 0FFE 1FFE 3FFE 3FFE 3FFC 1FFC 0FF8"            /* .˛.˛.˛?˛?˛?¸.¸.¯ */
	$"07F8 07F8 0009 0008 0000 0000 0000 0000"            /* .¯.¯.∆.......... */
	$"0000 0000 8004 0000 0000 0010 0010 0000"            /* ....Ä........... */
	$"0000 0000 0000 0048 0000 0048 0000 0000"            /* .......H...H.... */
	$"0002 0001 0002 0000 0000 0000 00D2 0000"            /* .............“.. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 00F3 CF00 035D 75F0 0355 55DC 00D5"            /* ...Ûœ..]u.UU‹.’ */
	$"555C 03D5 555C 0D55 555C 0D55 555C 0D55"            /* U\.’U\.UU\.UU\.U */
	$"5570 0355 5570 00D5 55C0 0035 55C0 0035"            /* Up.UUp.’U¿.5U¿.5 */
	$"55C0 0000 0000 0000 0002 0000 FFFF FFFF"            /* U¿..........ˇˇˇˇ */
	$"FFFF 0001 FFFF CCCC 9999 0003 0000 0000"            /* ˇˇ..ˇˇÃÃôô...... */
	$"0000"                                               /* .. */
};

data 'crsr' (9011, "Hot Spot Cursor") {
	$"8001 0000 0060 0000 0092 0000 0000 0000"            /* Ä....`...í...... */
	$"0000 0000 0000 0000 0000 0000 0C30 0E70"            /* .............0.p */
	$"07E0 03C0 03C0 07E0 0E70 0C30 0000 0000"            /* .‡.¿.¿.‡.p.0.... */
	$"0000 0000 0000 0000 0000 0000 0C30 0E70"            /* .............0.p */
	$"07E0 03C0 03C0 07E0 0E70 0C30 0000 0000"            /* .‡.¿.¿.‡.p.0.... */
	$"0000 0000 0007 0007 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 8002 0000 0000 0010 0010 0000"            /* ....Ä........... */
	$"0000 0000 0000 0048 0000 0048 0000 0000"            /* .......H...H.... */
	$"0001 0001 0001 0000 0000 0000 00B2 0000"            /* .............≤.. */
	$"0000 0000 0000 0000 0000 0C30 0E70 07E0"            /* ...........0.p.‡ */
	$"03C0 03C0 07E0 0E70 0C30 0000 0000 0000"            /* .¿.¿.‡.p.0...... */
	$"0000 0000 0000 0000 0001 0000 FFFF FFFF"            /* ............ˇˇˇˇ */
	$"FFFF 0001 DDDD 0000 0000"                           /* ˇˇ..››.... */
};

data 'crsr' (9012, "Small Eraser Tool Cursor") {
	$"8001 0000 0060 0000 0092 0000 0000 0000"            /* Ä....`...í...... */
	$"0000 0000 0000 0000 0000 0000 0FE0 0820"            /* .............‡.  */
	$"0820 0820 0820 0820 0FE0 0000 0000 0000"            /* . . . . .‡...... */
	$"0000 0000 0000 0000 0000 1FF0 1FF0 1830"            /* .............0 */
	$"1830 1830 1830 1830 1FF0 1FF0 0000 0000"            /* .0.0.0.0...... */
	$"0000 0000 0005 0005 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 8002 0000 0000 0010 0010 0000"            /* ....Ä........... */
	$"0000 0000 0000 0048 0000 0048 0000 0000"            /* .......H...H.... */
	$"0001 0001 0001 0000 0000 0000 00B2 0000"            /* .............≤.. */
	$"0000 0000 0000 0000 0000 0FE0 0820 0820"            /* ...........‡. .  */
	$"0820 0820 0820 0FE0 0000 0000 0000 0000"            /* . . . .‡........ */
	$"0000 0000 0000 0000 0001 0000 FFFF FFFF"            /* ............ˇˇˇˇ */
	$"FFFF 0001 0000 0000 0000"                           /* ˇˇ........ */
};

data 'crsr' (9013, "Cross Hair Cursor") {
	$"8001 0000 0060 0000 0092 0000 0000 0000"            /* Ä....`...í...... */
	$"0000 0000 0000 03E0 0220 0220 0220 0220"            /* .......‡. . . .  */
	$"7E3F 4001 4001 4001 7E3F 0220 0220 0220"            /* ~?@.@.@.~?. . .  */
	$"0220 03E0 0000 03E0 03E0 03E0 03E0 03E0"            /* . .‡...‡.‡.‡.‡.‡ */
	$"7E3F 7C1F 7C1F 7C1F 7E3F 03E0 03E0 03E0"            /* ~?|.|.|.~?.‡.‡.‡ */
	$"03E0 03E0 0006 0006 0000 0000 0000 0000"            /* .‡.‡............ */
	$"0000 0000 8004 0000 0000 0010 0010 0000"            /* ....Ä........... */
	$"0000 0000 0000 0048 0000 0048 0000 0000"            /* .......H...H.... */
	$"0002 0001 0002 0000 0000 0000 00D2 0000"            /* .............“.. */
	$"0000 0000 0000 000F FC00 000D 5C00 000D"            /* ........¸...\... */
	$"5C00 000D 5C00 000D 5C00 3FFC 0FFF 3550"            /* \...\...\.?¸.ˇ5P */
	$"0157 3550 0157 3550 0157 3FFC 0FFF 000D"            /* .W5P.W5P.W?¸.ˇ.. */
	$"5C00 000D 5C00 000D 5C00 000D 5C00 000F"            /* \...\...\...\... */
	$"FC00 0000 0000 0000 0002 0000 FFFF FFFF"            /* ¸...........ˇˇˇˇ */
	$"FFFF 0001 CCCC CCCC CCCC 0003 0000 0000"            /* ˇˇ..ÃÃÃÃÃÃ...... */
	$"0000"                                               /* .. */
};

data 'CTYP' (128, "Color Pane") {
	$"0001 6F62 6A64 0000 0021 7670 7465 0A43"            /* ..objd...!vpte¬C */
	$"436F 6C6F 7250 616E 6500 0000 436F 6C50"            /* ColorPane...ColP */
	$"6262 7574 0028 0014 0000 0062 6567 736F"            /* bbut.(.....begso */
	$"626A 6400 0000 2172 6762 630C 5377 6174"            /* bjd...!rgbc.Swat */
	$"6368 2043 6F6C 6F72 0000 0000 0101 5050"            /* ch Color......PP */
	$"6F62 0000 0000 0000 6F62 6A64 0000 0028"            /* ob......objd...( */
	$"696E 7476 1043 6C69 7020 546F 2053 6962"            /* intv.Clip To Sib */
	$"6C69 6E67 7300 0000 0001 0150 506F 6200"            /* lings......PPob. */
	$"0000 0100 0100 0000 6F62 6A64 0000 0028"            /* ........objd...( */
	$"696E 7476 1055 7365 2043 6F6C 6F72 2050"            /* intv.Use Color P */
	$"6963 6B65 7200 0000 0001 0150 506F 6200"            /* icker......PPob. */
	$"0000 0000 0100 0000 656E 6473 656E 642E"            /* ........endsend. */
};

data 'CTYP' (129, "DoubleClick Button") {
	$"0001 6F62 6A64 0000 0029 7670 7465 1243"            /* ..objd...)vpte.C */
	$"446F 7562 6C65 436C 6963 6B42 7574 746F"            /* DoubleClickButto */
	$"6E00 0000 4463 6262 6262 7574 0018 0018"            /* n...Dcbbbbut.... */
	$"0000 0062 6567 736F 626A 6400 0000 2769"            /* ...begsobjd...'i */
	$"6E74 760F 446F 7562 6C65 436C 6963 6B20"            /* ntv.DoubleClick  */
	$"4D73 6700 0000 0001 0150 506F 6200 0000"            /* Msg......PPob... */
	$"0000 2001 0100 656E 6473 656E 642E"                 /* .. ...endsend. */
};

data 'CTYP' (130, "Three Buttons Box") {
	$"0001 6F62 6A64 0000 0027 7670 7465 1043"            /* ..objd...'vpte.C */
	$"5468 7265 6542 7574 746F 6E73 426F 7800"            /* ThreeButtonsBox. */
	$"0000 5442 4278 7769 6E64 012C 00C8 0100"            /* ..TBBxwind.,.».. */
	$"0062 6567 736F 626A 6400 0000 2969 6E74"            /* .begsobjd...)int */
	$"7611 4465 6661 756C 7420 4275 7474 6F6E"            /* v.Default Button */
	$"2049 4400 0000 0001 0150 506F 62FF FFFF"            /*  ID......PPobˇˇˇ */
	$"FF00 2001 0100 6F62 6A64 0000 0028 696E"            /* ˇ. ...objd...(in */
	$"7476 1043 616E 6365 6C20 4275 7474 6F6E"            /* tv.Cancel Button */
	$"2049 4400 0000 0001 0150 506F 62FF FFFF"            /*  ID......PPobˇˇˇ */
	$"FF00 2001 0100 6F62 6A64 0000 0026 696E"            /* ˇ. ...objd...&in */
	$"7476 0E44 6F6E 7420 4275 7474 6F6E 2049"            /* tv.Dont Button I */
	$"4400 0000 0001 0150 506F 62FF FFFF FF00"            /* D......PPobˇˇˇˇ. */
	$"2001 0100 656E 6473 656E 642E"                      /*  ...endsend. */
};

data 'CTYP' (131, "Popup Edit Field") {
	$"0001 6F62 6A64 0000 0026 7670 7465 0F43"            /* ..objd...&vpte.C */
	$"506F 7075 7045 6469 7446 6965 6C64 0000"            /* PopupEditField.. */
	$"0050 6F70 4665 7478 7400 4B00 1A00 0000"            /* .PopFetxt.K..... */
	$"6265 6773 6F62 6A64 0000 0025 696E 7476"            /* begsobjd...%intv */
	$"0D50 6F70 7570 204D 6573 7361 6765 0000"            /* .Popup Message.. */
	$"0000 0101 5050 6F62 0000 0000 0020 0101"            /* ....PPob..... .. */
	$"006F 626A 6400 0000 2472 6573 6C07 5354"            /* .objd...$resl.ST */
	$"5223 2049 4400 0000 0001 0150 506F 6200"            /* R# ID......PPob. */
	$"0000 0000 1001 0000 0053 5452 236F 626A"            /* .........STR#obj */
	$"6400 0000 2169 6E74 7609 4C65 6674 2053"            /* d...!intv∆Left S */
	$"6964 6500 0000 0001 0150 506F 6200 0000"            /* ide......PPob... */
	$"0000 0100 0000 6F62 6A64 0000 0027 7073"            /* ......objd...'ps */
	$"7472 0C55 6E6B 6E6F 776E 2069 7465 6D00"            /* tr.Unknown item. */
	$"0000 0001 0150 506F 6207 556E 6B6E 6F77"            /* .....PPob.Unknow */
	$"6E00 1F00 0065 6E64 7365 6E64 2E"                   /* n....endsend. */
};

data 'CTYP' (132, "Flag Popup Button") {
	$"0001 6F62 6A64 0000 0021 7670 7465 0A43"            /* ..objd...!vpte¬C */
	$"466C 6167 506F 7075 7000 0000 466C 6750"            /* FlagPopup...FlgP */
	$"706F 7062 0078 0014 0000 0062 6567 736F"            /* popb.x.....begso */
	$"626A 6400 0000 2472 6573 6C07 5354 5223"            /* bjd...$resl.STR# */
	$"2049 4400 0000 0001 0150 506F 6200 0000"            /*  ID......PPob... */
	$"0000 1001 0000 0053 5452 236F 626A 6400"            /* .......STR#objd. */
	$"0000 2569 6E74 760D 496E 6974 6961 6C20"            /* ..%intv.Initial  */
	$"7661 6C75 6500 0000 0001 0150 506F 6200"            /* value......PPob. */
	$"0000 0000 2000 0000 656E 6473 656E 642E"            /* .... ...endsend. */
};

data 'cicn' (503, "Speaker3") {
	$"0000 0000 8018 0000 0000 0018 0018 0000"            /* ....Ä........... */
	$"0000 0000 0000 0048 0000 0048 0000 0000"            /* .......H...H.... */
	$"0008 0001 0008 3535 3531 0000 0000 0000"            /* ......5551...... */
	$"0000 0000 0000 0004 0000 0000 0018 0018"            /* ................ */
	$"0000 0000 0004 0000 0000 0018 0018 0000"            /* ................ */
	$"0000 FFFF FFEB FFFF FF01 FFFF FF00 FFFF"            /* ..ˇˇˇÎˇˇˇ.ˇˇˇ.ˇˇ */
	$"FF00 FFFF FF00 FFFF FF00 FFFF FF01 FFFF"            /* ˇ.ˇˇˇ.ˇˇˇ.ˇˇˇ.ˇˇ */
	$"FF00 FFFF FFB0 FFFF FF00 FFFF FF00 FFFF"            /* ˇ.ˇˇˇ∞ˇˇˇ.ˇˇˇ.ˇˇ */
	$"FF7C FFFF FF00 FFFF FF00 FFFF FF01 FFFF"            /* ˇ|ˇˇˇ.ˇˇˇ.ˇˇˇ.ˇˇ */
	$"FF00 FFFF FF00 FFFF FF00 FFFF FF00 FFFF"            /* ˇ.ˇˇˇ.ˇˇˇ.ˇˇˇ.ˇˇ */
	$"FF00 FFFF FF00 FFFF FF2B FFFF FF20 0000"            /* ˇ.ˇˇˇ.ˇˇˇ+ˇˇˇ .. */
	$"003B 0000 007B 0000 0070 0000 0000 0000"            /* .;...{...p...... */
	$"0000 0000 0000 0000 0000 0000 0002 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 007B 0000 00EB 0000 0050 0000"            /* .....{...Î...P.. */
	$"0050 0000 007B 0000 007B 0000 007B 0000"            /* .P...{...{...{.. */
	$"0000 0000 0000 0000 00D4 0000 0000 0000"            /* .........‘...... */
	$"005B 0000 044B 0000 0056 0000 FFFF FFFF"            /* .[...K...V..ˇˇˇˇ */
	$"FFFF 0001 F5F5 F5F5 F5F5 0002 F6F6 F6F6"            /* ˇˇ..ıııııı..ˆˆˆˆ */
	$"F6F6 0003 A9A9 A9A9 A9A9 0004 CDCD CDCD"            /* ˆˆ..©©©©©©..ÕÕÕÕ */
	$"CDCD 0005 F0F0 F0F0 F0F0 0006 D7D7 D7D7"            /* ÕÕ....◊◊◊◊ */
	$"D7D7 0007 3232 3232 3232 0008 7373 7373"            /* ◊◊..222222..ssss */
	$"7373 0009 E9E9 E9E9 E9E9 000A D0D0 D0D0"            /* ss.∆ÈÈÈÈÈÈ.¬–––– */
	$"D0D0 000B FDFD FDFD FDFD 000C A1A1 A1A1"            /* ––..˝˝˝˝˝˝..°°°° */
	$"A1A1 000D 2828 2828 2828 000E A4A4 A4A4"            /* °°..((((((..§§§§ */
	$"A4A4 000F EFEF EFEF EFEF 0010 F4F4 F4F4"            /* §§..ÔÔÔÔÔÔ..ÙÙÙÙ */
	$"F4F4 0011 CCCC CCCC CCCC 0012 3030 3030"            /* ÙÙ..ÃÃÃÃÃÃ..0000 */
	$"3030 0013 AEAE AEAE AEAE 0014 3838 3838"            /* 00..ÆÆÆÆÆÆ..8888 */
	$"3838 0015 BFBF BFBF BFBF 0016 F8F8 F8F8"            /* 88..øøøøøø..¯¯¯¯ */
	$"F8F8 0017 6969 6969 6969 0018 5050 5050"            /* ¯¯..iiiiii..PPPP */
	$"5050 0019 E1E1 E1E1 E1E1 001A F3F3 F3F3"            /* PP..······..ÛÛÛÛ */
	$"F3F3 001B E2E2 E2E2 E2E2 001C E7E7 E7E7"            /* ÛÛ..‚‚‚‚‚‚..ÁÁÁÁ */
	$"E7E7 001D 4E4E 4E4E 4E4E 001E 5F5F 5F5F"            /* ÁÁ..NNNNNN..____ */
	$"5F5F 001F D5D5 D5D5 D5D5 0020 2F2F 2F2F"            /* __..’’’’’’. //// */
	$"2F2F 0021 B3B3 B3B3 B3B3 0022 EEEE EEEE"            /* //.!≥≥≥≥≥≥."ÓÓÓÓ */
	$"EEEE 0023 CFCF CFCF CFCF 0024 B5B5 B5B5"            /* ÓÓ.#œœœœœœ.$µµµµ */
	$"B5B5 0025 4949 4949 4949 0026 E4E4 E4E4"            /* µµ.%IIIIII.&‰‰‰‰ */
	$"E4E4 0027 CECE CECE CECE 0028 2C2C 2C2C"            /* ‰‰.'ŒŒŒŒŒŒ.(,,,, */
	$"2C2C 0029 AFAF AFAF AFAF 002A F1F1 F1F1"            /* ,,.)ØØØØØØ.*ÒÒÒÒ */
	$"F1F1 002B 6C6C 6C6C 6C6C 002C 7B7B 7B7B"            /* ÒÒ.+llllll.,{{{{ */
	$"7B7B 002D CACA CACA CACA 002E B1B1 B1B1"            /* {{.-      ..±±±± */
	$"B1B1 002F 7070 7070 7070 0030 9696 9696"            /* ±±./pppppp.0ññññ */
	$"9696 0031 7A7A 7A7A 7A7A 0032 7272 7272"            /* ññ.1zzzzzz.2rrrr */
	$"7272 0033 A6A6 A6A6 A6A6 0034 4F4F 4F4F"            /* rr.3¶¶¶¶¶¶.4OOOO */
	$"4F4F 0035 EDED EDED EDED 0036 F2F2 F2F2"            /* OO.5ÌÌÌÌÌÌ.6ÚÚÚÚ */
	$"F2F2 0037 6060 6060 6060 0038 5454 5454"            /* ÚÚ.7``````.8TTTT */
	$"5454 0039 BCBC BCBC BCBC 003A 4040 4040"            /* TT.9ºººººº.:@@@@ */
	$"4040 003B D4D4 D4D4 D4D4 003C 3A3A 3A3A"            /* @@.;‘‘‘‘‘‘.<:::: */
	$"3A3A 003D C4C4 C4C4 C4C4 003E 2525 2525"            /* ::.=ƒƒƒƒƒƒ.>%%%% */
	$"2525 003F EBEB EBEB EBEB 0040 1E1E 1E1E"            /* %%.?ÎÎÎÎÎÎ.@.... */
	$"1E1E 0041 2727 2727 2727 0042 ECEC ECEC"            /* ...A''''''.BÏÏÏÏ */
	$"ECEC 0043 8F8F 8F8F 8F8F 0044 C8C8 C8C8"            /* ÏÏ.Cèèèèèè.D»»»» */
	$"C8C8 0045 EAEA EAEA EAEA 0046 C1C1 C1C1"            /* »».EÍÍÍÍÍÍ.F¡¡¡¡ */
	$"C1C1 0047 CBCB CBCB CBCB 0048 D3D3 D3D3"            /* ¡¡.GÀÀÀÀÀÀ.H”””” */
	$"D3D3 0049 7979 7979 7979 004A E8E8 E8E8"            /* ””.Iyyyyyy.JËËËË */
	$"E8E8 004B C5C5 C5C5 C5C5 004C 4848 4848"            /* ËË.K≈≈≈≈≈≈.LHHHH */
	$"4848 004D D9D9 D9D9 D9D9 004E DDDD DDDD"            /* HH.MŸŸŸŸŸŸ.N›››› */
	$"DDDD 004F FBFB FBFB FBFB 0050 9D9D 9D9D"            /* ››.O˚˚˚˚˚˚.Pùùùù */
	$"9D9D 0051 E0E0 E0E0 E0E0 0052 4242 4242"            /* ùù.Q‡‡‡‡‡‡.RBBBB */
	$"4242 0053 6E6E 6E6E 6E6E 0054 DFDF DFDF"            /* BB.Snnnnnn.Tﬂﬂﬂﬂ */
	$"DFDF 0055 E5E5 E5E5 E5E5 0056 C7C7 C7C7"            /* ﬂﬂ.UÂÂÂÂÂÂ.V«««« */
	$"C7C7 2A2A 2A2A 2A2A 2A2A 2A2A 2A2A 2A2A"            /* ««************** */
	$"2A2A 2A2A 2A2A 2A2A 2A2A 2A2A 2A2A 2A2A"            /* **************** */
	$"2A2A 2A2A 2A2A 2A2A 2A2A 2A2A 2A2A 2A2A"            /* **************** */
	$"2A2A 0101 2A2A 2A2A 2A2A 2A2A 2A2A 2A2A"            /* **..************ */
	$"2A2A 2A2A 2A2A 2A02 2A02 0201 0201 0102"            /* *******.*....... */
	$"0201 0102 0201 0102 0201 0304 0201 0102"            /* ................ */
	$"2A02 0505 0202 0102 0202 0102 0202 0102"            /* *............... */
	$"0206 0708 0902 0105 2A2A 0505 2A05 0505"            /* ....∆...**..*... */
	$"2A05 0505 2A05 0505 0A0B 0C0D 0E05 050F"            /* *...*...¬....... */
	$"2A05 0110 0505 050F 0505 1112 0505 0513"            /* *............... */
	$"1415 1617 1819 0510 2A10 1A1A 1001 1010"            /* ........*....... */
	$"100A 1212 1001 1B1C 1D1E 021F 2021 1010"            /* .¬.......... !.. */
	$"2A10 2222 101A 1A10 2312 1212 1024 2526"            /* *.""....#....$%& */
	$"2728 2900 2B2C 1A22 2A22 2222 2222 222D"            /* '().+,."*""""""- */
	$"1212 1212 222E 2F30 0031 3200 3334 2235"            /* ...."./0.12.34"5 */
	$"2A22 362A 2212 1212 1212 1212 221A 3738"            /* *"6*".......".78 */
	$"0039 3A00 3B3C 2D36 2A2A 2A2A 2A12 1212"            /* .9:.;<-6*****... */
	$"1212 1212 2A00 3D3E 003F 4000 1A41 0405"            /* ....*.=>.?@..A.. */
	$"2A2A 3F42 2A12 1212 1212 1212 2A00 3D3E"            /* **?B*.......*.=> */
	$"003F 4000 1A41 043F 2A3F 3F3F 3F12 1212"            /* .?@..A.?*????... */
	$"1212 1212 3F36 4338 0039 3A00 3B3C 443F"            /* ....?6C8.9:.;<D? */
	$"2A45 0F0F 453F 3F44 1212 1212 4546 2F30"            /* *E..E??D....EF/0 */
	$"0031 3200 331D 440F 2A0F 2222 0F0F 0F0F"            /* .12.3.D.*."".... */
	$"4712 1212 0F48 2526 2728 2900 2B49 0F0F"            /* G....H%&'().+I.. */
	$"2A22 4A4A 2222 220F 222D 1212 2222 4509"            /* *"JJ"""."-..""E∆ */
	$"1D1E 021F 2013 224A 2A4A 1C4A 4A4A 4A4A"            /* .... ."J*J.JJJJJ */
	$"4A4A 4B12 4A4A 4A1F 4C15 1617 1D4D 4A1C"            /* JJK.JJJ.L....MJ. */
	$"2A1C 453F 1C1C 4A1C 1C1C 4A1C 1C1C 4A1C"            /* *.E?..J...J...J. */
	$"4E4F 0C41 501C 4A3F 2A3F 4545 3F45 3F3F"            /* NO.AP.J?*?EE?E?? */
	$"3F45 3F3F 3F45 3F3F 3F51 5253 5445 3F45"            /* ?E???E???QRSTE?E */
	$"2A45 2655 4545 4545 4545 4545 4545 4545"            /* *E&UEEEEEEEEEEEE */
	$"4545 0A56 4545 4555 2A55 3F3F 5526 5555"            /* EE¬VEEEU*U??U&UU */
	$"5526 5555 5526 5555 5526 5555 5526 553F"            /* U&UUU&UUU&UUU&U? */
	$"2A3F 3F3F 3F3F 3F3F 3F3F 3F3F 3F3F 3F3F"            /* *??????????????? */
	$"3F3F 3F3F 3F3F 3F3F 2A3F 3F3F 3F3F 3F3F"            /* ????????*??????? */
	$"3F3F 3F3F 3F3F 3F3F 3F3F 3F3F 3F3F 3F3F"            /* ???????????????? */
	$"2A3F"                                               /* *? */
};

data 'cicn' (502, "Speaker2") {
	$"0000 0000 8018 0000 0000 0018 0018 0000"            /* ....Ä........... */
	$"0000 0000 0000 0048 0000 0048 0000 0000"            /* .......H...H.... */
	$"0008 0001 0008 3535 3531 0000 0000 0000"            /* ......5551...... */
	$"0000 0000 0000 0004 0000 0000 0018 0018"            /* ................ */
	$"0000 0000 0004 0000 0000 0018 0018 0000"            /* ................ */
	$"0000 FFFF FF7B FFFF FF01 FFFF FF7B FFFF"            /* ..ˇˇˇ{ˇˇˇ.ˇˇˇ{ˇˇ */
	$"FF2B FFFF FF2B FFFF FF3B FFFF FF4B FFFF"            /* ˇ+ˇˇˇ+ˇˇˇ;ˇˇˇKˇˇ */
	$"FFDB FFFF FF00 FFFF FF01 FFFF FFAB FFFF"            /* ˇ€ˇˇˇ.ˇˇˇ.ˇˇˇ´ˇˇ */
	$"FF01 FFFF FF2B FFFF FFEB FFFF FF1B FFFF"            /* ˇ.ˇˇˇ+ˇˇˇÎˇˇˇ.ˇˇ */
	$"FF1B FFFF FFCB FFFF FF01 FFFF FFAB FFFF"            /* ˇ.ˇˇˇÀˇˇˇ.ˇˇˇ´ˇˇ */
	$"FF01 FFFF FF7B FFFF FFAB FFFF FFEB FFFF"            /* ˇ.ˇˇˇ{ˇˇˇ´ˇˇˇÎˇˇ */
	$"FF0B 0000 007B 0000 00D3 0000 00FF 0000"            /* ˇ....{...”...ˇ.. */
	$"0000 0000 002B 0000 0008 0000 00A4 0000"            /* .....+.......§.. */
	$"0084 0000 0000 0000 0000 0000 003B 0000"            /* .Ñ...........;.. */
	$"0038 0000 0035 0000 0035 0000 0029 0000"            /* .8...5...5...).. */
	$"00E1 0000 0000 0000 0000 0000 00F6 0000"            /* .·...........ˆ.. */
	$"000C 0000 0000 0000 000C 0000 0000 0000"            /* ................ */
	$"0000 0000 0455 0000 003A 0000 FFFF FFFF"            /* .....U...:..ˇˇˇˇ */
	$"FFFF 0001 F1F1 F1F1 F1F1 0002 F5F5 F5F5"            /* ˇˇ..ÒÒÒÒÒÒ..ıııı */
	$"F5F5 0003 F0F0 F0F0 F0F0 0004 EFEF EFEF"            /* ıı....ÔÔÔÔ */
	$"EFEF 0005 D0D0 D0D0 D0D0 0006 FDFD FDFD"            /* ÔÔ..––––––..˝˝˝˝ */
	$"FDFD 0007 F4F4 F4F4 F4F4 0008 CDCD CDCD"            /* ˝˝..ÙÙÙÙÙÙ..ÕÕÕÕ */
	$"CDCD 0009 3030 3030 3030 000A AFAF AFAF"            /* ÕÕ.∆000000.¬ØØØØ */
	$"AFAF 000B 3838 3838 3838 000C BFBF BFBF"            /* ØØ..888888..øøøø */
	$"BFBF 000D F8F8 F8F8 F8F8 000E D1D1 D1D1"            /* øø..¯¯¯¯¯¯..———— */
	$"D1D1 000F E2E2 E2E2 E2E2 0010 E7E7 E7E7"            /* ——..‚‚‚‚‚‚..ÁÁÁÁ */
	$"E7E7 0011 4E4E 4E4E 4E4E 0012 5F5F 5F5F"            /* ÁÁ..NNNNNN..____ */
	$"5F5F 0013 F3F3 F3F3 F3F3 0014 EEEE EEEE"            /* __..ÛÛÛÛÛÛ..ÓÓÓÓ */
	$"EEEE 0015 B5B5 B5B5 B5B5 0016 4949 4949"            /* ÓÓ..µµµµµµ..IIII */
	$"4949 0017 E4E4 E4E4 E4E4 0018 CECE CECE"            /* II..‰‰‰‰‰‰..ŒŒŒŒ */
	$"CECE 0019 2C2C 2C2C 2C2C 001A EDED EDED"            /* ŒŒ..,,,,,,..ÌÌÌÌ */
	$"EDED 001B CBCB CBCB CBCB 001C B2B2 B2B2"            /* ÌÌ..ÀÀÀÀÀÀ..≤≤≤≤ */
	$"B2B2 001D 7070 7070 7070 001E 9696 9696"            /* ≤≤..pppppp..ññññ */
	$"9696 001F F6F6 F6F6 F6F6 0020 7A7A 7A7A"            /* ññ..ˆˆˆˆˆˆ. zzzz */
	$"7A7A 0021 7272 7272 7272 0022 F2F2 F2F2"            /* zz.!rrrrrr."ÚÚÚÚ */
	$"F2F2 0023 6060 6060 6060 0024 5454 5454"            /* ÚÚ.#``````.$TTTT */
	$"5454 0025 BCBC BCBC BCBC 0026 4040 4040"            /* TT.%ºººººº.&@@@@ */
	$"4040 0027 C4C4 C4C4 C4C4 0028 2525 2525"            /* @@.'ƒƒƒƒƒƒ.(%%%% */
	$"2525 0029 EBEB EBEB EBEB 002A 1E1E 1E1E"            /* %%.)ÎÎÎÎÎÎ.*.... */
	$"1E1E 002B ECEC ECEC ECEC 002C EAEA EAEA"            /* ...+ÏÏÏÏÏÏ.,ÍÍÍÍ */
	$"EAEA 002D 8F8F 8F8F 8F8F 002E C9C9 C9C9"            /* ÍÍ.-èèèèèè..………… */
	$"C9C9 002F C2C2 C2C2 C2C2 0030 CCCC CCCC"            /* ……./¬¬¬¬¬¬.0ÃÃÃÃ */
	$"CCCC 0031 D3D3 D3D3 D3D3 0032 4A4A 4A4A"            /* ÃÃ.1””””””.2JJJJ */
	$"4A4A 0033 E8E8 E8E8 E8E8 0034 E9E9 E9E9"            /* JJ.3ËËËËËË.4ÈÈÈÈ */
	$"E9E9 0035 C6C6 C6C6 C6C6 0036 D5D5 D5D5"            /* ÈÈ.5∆∆∆∆∆∆.6’’’’ */
	$"D5D5 0037 DDDD DDDD DDDD 0038 FBFB FBFB"            /* ’’.7››››››.8˚˚˚˚ */
	$"FBFB 0039 E1E1 E1E1 E1E1 003A E5E5 E5E5"            /* ˚˚.9······.:ÂÂÂÂ */
	$"E5E5 1F1F 1F1F 1F1F 1F1F 1F1F 1F1F 1F1F"            /* ÂÂ.............. */
	$"1F1F 1F1F 1F1F 1F1F 1F1F 0101 0101 0101"            /* ................ */
	$"0101 0101 0101 0101 0101 0101 0101 0101"            /* ................ */
	$"0101 1F1F 0202 1F1F 0202 1F1F 0202 1F1F"            /* ................ */
	$"0202 1F1F 0202 1F1F 0202 1F1F 1F02 1F1F"            /* ................ */
	$"1F02 1F1F 1F02 1F1F 1F02 1F1F 1F02 1F1F"            /* ................ */
	$"1F02 0301 0303 031F 1F1F 1F1F 1F1F 1F1F"            /* ................ */
	$"1F1F 1F1F 0103 0301 0303 0403 0103 0303"            /* ................ */
	$"0103 0303 0103 0303 0506 0303 0303 0303"            /* ................ */
	$"0303 0707 0303 0304 0303 0809 0303 030A"            /* ...........∆...¬ */
	$"0B0C 0D04 0702 0707 0207 0707 0702 0707"            /* ................ */
	$"070E 0909 0702 0F10 1112 1F07 0713 1307"            /* ..∆∆............ */
	$"1313 1414 0713 1307 0509 0909 0715 1617"            /* .........∆∆∆.... */
	$"1819 0A07 1414 1414 1414 1A14 1414 141B"            /* ..¬............. */
	$"0909 0909 141C 1D1E 0020 2114 1414 1414"            /* ∆∆∆∆..... !..... */
	$"1414 2201 1409 0909 0909 0909 1407 2324"            /* .."..∆∆∆∆∆∆∆..#$ */
	$"0025 261A 0122 0101 2201 0301 0109 0909"            /* .%&..".."....∆∆∆ */
	$"0909 0909 0100 2728 0029 2A22 0101 0101"            /* ∆∆∆∆..'(.)*".... */
	$"0101 2929 0109 0909 0909 0909 0100 2728"            /* ..)).∆∆∆∆∆∆∆..'( */
	$"0029 2A03 2929 2B29 292B 292C 2909 0909"            /* .)*.))+))+),)∆∆∆ */
	$"0909 0909 2913 2D24 0025 2629 2C29 292C"            /* ∆∆∆∆).-$.%&),)), */
	$"2929 0404 2C29 292E 0909 0909 2C2F 1D1E"            /* ))..,)).∆∆∆∆,/.. */
	$"0020 2129 0404 0404 0404 0414 0404 0404"            /* . !)............ */
	$"3009 0909 0431 3217 1819 0A04 1414 1414"            /* 0∆∆∆.12...¬..... */
	$"1414 3333 1414 1404 141B 0909 1414 2C34"            /* ..33......∆∆..,4 */
	$"1112 1F04 3333 3333 3333 1010 3333 3333"            /* ....333333..3333 */
	$"3333 3509 3333 3336 160C 0D33 1010 3310"            /* 335∆3336...3..3. */
	$"1033 2929 1010 3310 1010 3310 1010 3310"            /* .3))..3...3...3. */
	$"3738 3310 292C 2929 2C29 2C2C 292C 2929"            /* 783.),)),),,),)) */
	$"292C 2929 292C 2929 2939 2929 2C2C 2C2C"            /* ),))),)))9)),,,, */
	$"2C2C 3A3A 173A 3A3A 173A 3A3A 173A 3A3A"            /* ,,::.:::.:::.::: */
	$"173A 3A3A 173A 3A3A 173A 3A3A 3A3A 3A3A"            /* .:::.:::.::::::: */
	$"3A3A 3A3A 3A3A 3A3A 3A3A 3A3A 3A3A 3A3A"            /* :::::::::::::::: */
	$"3A3A 3A3A 3A3A 3A3A 3A3A 3A3A 3A3A 3A3A"            /* :::::::::::::::: */
	$"3A3A 3A3A 3A3A 3A3A 3A3A 3A3A 3A3A 3A3A"            /* :::::::::::::::: */
	$"3A3A 3A3A 3A3A 3A3A 3A3A 3A3A 3A3A 3A3A"            /* :::::::::::::::: */
	$"3A3A"                                               /* :: */
};

data 'cicn' (501, "Speaker1") {
	$"0000 0000 8018 0000 0000 0018 0018 0000"            /* ....Ä........... */
	$"0000 0000 0000 0048 0000 0048 0000 0000"            /* .......H...H.... */
	$"0008 0001 0008 3535 3531 0000 0000 0000"            /* ......5551...... */
	$"0000 0000 0000 0004 0000 0000 0018 0018"            /* ................ */
	$"0000 0000 0004 0000 0000 0018 0018 0000"            /* ................ */
	$"0000 FFFF FF7B FFFF FF00 FFFF FF00 FFFF"            /* ..ˇˇˇ{ˇˇˇ.ˇˇˇ.ˇˇ */
	$"FF00 FFFF FF00 FFFF FF55 FFFF FFFF FFFF"            /* ˇ.ˇˇˇ.ˇˇˇUˇˇˇˇˇˇ */
	$"FF00 FFFF FFE0 FFFF FF2F FFFF FF00 FFFF"            /* ˇ.ˇˇˇ‡ˇˇˇ/ˇˇˇ.ˇˇ */
	$"FF04 FFFF FF7B FFFF FFBB FFFF FF5C FFFF"            /* ˇ.ˇˇˇ{ˇˇˇªˇˇˇ\ˇˇ */
	$"FFD0 FFFF FF00 FFFF FFDB FFFF FF00 FFFF"            /* ˇ–ˇˇˇ.ˇˇˇ€ˇˇˇ.ˇˇ */
	$"FF01 FFFF FF50 FFFF FF00 FFFF FF00 FFFF"            /* ˇ.ˇˇˇPˇˇˇ.ˇˇˇ.ˇˇ */
	$"FF00 0000 001B 0000 007B 0000 005B 0000"            /* ˇ........{...[.. */
	$"0001 0000 003B 0000 00BB 0000 0062 0000"            /* .....;...ª...b.. */
	$"0001 0000 000B 0000 00BB 0000 005B 0000"            /* .........ª...[.. */
	$"0001 0000 00DB 0000 008B 0000 00BB 0000"            /* .....€...ã...ª.. */
	$"003B 0000 0000 0000 0000 0000 0030 0000"            /* .;...........0.. */
	$"0000 0000 0004 0000 0002 0000 0000 0000"            /* ................ */
	$"0078 0000 0462 0000 0026 0000 FFFF FFFF"            /* .x...b...&..ˇˇˇˇ */
	$"FFFF 0001 F5F5 F5F5 F5F5 0002 F6F6 F6F6"            /* ˇˇ..ıııııı..ˆˆˆˆ */
	$"F6F6 0003 F0F0 F0F0 F0F0 0004 EFEF EFEF"            /* ˆˆ....ÔÔÔÔ */
	$"EFEF 0005 F4F4 F4F4 F4F4 0006 CDCD CDCD"            /* ÔÔ..ÙÙÙÙÙÙ..ÕÕÕÕ */
	$"CDCD 0007 3030 3030 3030 0008 F3F3 F3F3"            /* ÕÕ..000000..ÛÛÛÛ */
	$"F3F3 0009 D1D1 D1D1 D1D1 000A EEEE EEEE"            /* ÛÛ.∆——————.¬ÓÓÓÓ */
	$"EEEE 000B D0D0 D0D0 D0D0 000C B5B5 B5B5"            /* ÓÓ..––––––..µµµµ */
	$"B5B5 000D 4949 4949 4949 000E E4E4 E4E4"            /* µµ..IIIIII..‰‰‰‰ */
	$"E4E4 000F CBCB CBCB CBCB 0010 B2B2 B2B2"            /* ‰‰..ÀÀÀÀÀÀ..≤≤≤≤ */
	$"B2B2 0011 7070 7070 7070 0012 9696 9696"            /* ≤≤..pppppp..ññññ */
	$"9696 0013 EDED EDED EDED 0014 6060 6060"            /* ññ..ÌÌÌÌÌÌ..```` */
	$"6060 0015 5454 5454 5454 0016 F2F2 F2F2"            /* ``..TTTTTT..ÚÚÚÚ */
	$"F2F2 0017 F1F1 F1F1 F1F1 0018 C4C4 C4C4"            /* ÚÚ..ÒÒÒÒÒÒ..ƒƒƒƒ */
	$"C4C4 0019 2525 2525 2525 001A ECEC ECEC"            /* ƒƒ..%%%%%%..ÏÏÏÏ */
	$"ECEC 001B EBEB EBEB EBEB 001C 8F8F 8F8F"            /* ÏÏ..ÎÎÎÎÎÎ..èèèè */
	$"8F8F 001D EAEA EAEA EAEA 001E C9C9 C9C9"            /* èè..ÍÍÍÍÍÍ..………… */
	$"C9C9 001F C2C2 C2C2 C2C2 0020 CCCC CCCC"            /* ……..¬¬¬¬¬¬. ÃÃÃÃ */
	$"CCCC 0021 D3D3 D3D3 D3D3 0022 4A4A 4A4A"            /* ÃÃ.!””””””."JJJJ */
	$"4A4A 0023 E8E8 E8E8 E8E8 0024 C6C6 C6C6"            /* JJ.#ËËËËËË.$∆∆∆∆ */
	$"C6C6 0025 E7E7 E7E7 E7E7 0026 E5E5 E5E5"            /* ∆∆.%ÁÁÁÁÁÁ.&ÂÂÂÂ */
	$"E5E5 1717 1717 1717 1717 1717 1717 1717"            /* ÂÂ.............. */
	$"1717 1717 1717 1717 1717 1717 1717 1717"            /* ................ */
	$"1717 1717 1717 1717 1717 1717 1717 1717"            /* ................ */
	$"1717 0102 0201 0102 0201 0102 0201 0102"            /* ................ */
	$"0201 0102 0201 0102 0201 0102 0202 0102"            /* ................ */
	$"0202 0202 0202 0202 0202 0102 0202 0102"            /* ................ */
	$"0202 0302 0202 0102 0202 0102 0202 0102"            /* ................ */
	$"0202 0303 1703 0303 1703 0303 1703 0303"            /* ................ */
	$"1703 0303 1703 0303 1703 0304 0303 0304"            /* ................ */
	$"0303 0504 0303 0304 0303 0607 0303 0304"            /* ................ */
	$"0303 0505 0501 0505 0501 0805 0501 0505"            /* ................ */
	$"0509 0707 0501 0505 0501 0805 0508 0805"            /* .∆.............. */
	$"0508 0A05 0508 0805 0B07 0707 050C 0D0E"            /* ..¬............. */
	$"0508 0A0A 0A0A 0A0A 0A0A 0A0A 0A0A 0A0F"            /* ..¬¬¬¬¬¬¬¬¬¬¬¬¬. */
	$"0707 0707 0A10 1112 0A0A 0A13 0A0A 0A13"            /* ....¬...¬¬¬.¬¬¬. */
	$"0A0A 1713 0A07 0707 0707 0707 0A05 1415"            /* ¬¬..¬.......¬... */
	$"0A0A 1716 1716 1716 1716 1716 1707 0707"            /* ¬¬.............. */
	$"0707 0707 1700 1819 1716 1703 1717 1703"            /* ................ */
	$"1717 1A03 1707 0707 0707 0707 1700 1819"            /* ................ */
	$"1717 1A1B 1B1B 1A1B 1B1B 1B1B 1B07 0707"            /* ................ */
	$"0707 0707 1B08 1C15 1B1B 1B1B 1D1B 1B1B"            /* ................ */
	$"1D1B 041B 1D1B 1B1E 0707 0707 1D1F 1112"            /* ................ */
	$"1D1B 0404 0404 0404 0404 0A04 0404 0404"            /* ..........¬..... */
	$"2007 0707 0421 220E 0404 0A04 0A0A 0A04"            /*  ....!"...¬.¬¬¬. */
	$"0A0A 2304 0A0A 0A04 0A0F 0707 0A0A 1D04"            /* ¬¬#.¬¬¬.¬...¬¬.. */
	$"0A0A 2323 2323 2323 2323 2323 2323 2323"            /* ¬¬############## */
	$"2323 2407 2323 2323 2323 2325 2525 2325"            /* ##$.#######%%%#% */
	$"2525 1B25 2525 2325 2525 2325 2525 2325"            /* %%.%%%#%%%#%%%#% */
	$"2525 1B1B 1B1D 1B1B 1B1D 1D1D 1D1D 1D1D"            /* %%.............. */
	$"1D1D 1D1D 1D1D 1D1D 1D1D 1D1D 1D1D 1D1D"            /* ................ */
	$"1D1D 2626 260E 2626 260E 2626 260E 2626"            /* ..&&&.&&&.&&&.&& */
	$"260E 2626 260E 2626 260E 1D1D 1D1D 1D1D"            /* &.&&&.&&&....... */
	$"1D1D 1D1D 1D1D 1D1D 1D1D 1D1D 1D1D 1D1D"            /* ................ */
	$"1D1D 1D1D 1D1D 1D1D 1D1D 1D1D 1D1D 1D1D"            /* ................ */
	$"1D1D 1D1D 1D1D 1D1D 1D1D 2626 260E 2626"            /* ..........&&&.&& */
	$"260E 2626 260E 2626 260E 2626 260E 2626"            /* &.&&&.&&&.&&&.&& */
	$"260E"                                               /* &. */
};

data 'cicn' (500, "Speaker0") {
	$"0000 0000 8018 0000 0000 0018 0018 0000"            /* ....Ä........... */
	$"0000 0000 0000 0048 0000 0048 0000 0000"            /* .......H...H.... */
	$"0008 0001 0008 3535 3531 0000 0000 0000"            /* ......5551...... */
	$"0000 0000 0000 0004 0000 0000 0018 0018"            /* ................ */
	$"0000 0000 0004 0000 0000 0018 0018 0000"            /* ................ */
	$"0000 FFFF FF7B FFFF FF00 FFFF FF00 FFFF"            /* ..ˇˇˇ{ˇˇˇ.ˇˇˇ.ˇˇ */
	$"FF04 FFFF FFBB FFFF FF0B FFFF FFBA FFFF"            /* ˇ.ˇˇˇªˇˇˇ.ˇˇˇ∫ˇˇ */
	$"FFD0 FFFF FF00 FFFF FF9B FFFF FF00 FFFF"            /* ˇ–ˇˇˇ.ˇˇˇõˇˇˇ.ˇˇ */
	$"FF00 FFFF FF00 FFFF FF00 FFFF FF00 FFFF"            /* ˇ.ˇˇˇ.ˇˇˇ.ˇˇˇ.ˇˇ */
	$"FF20 FFFF FF00 FFFF FF00 FFFF FFA2 FFFF"            /* ˇ ˇˇˇ.ˇˇˇ.ˇˇˇ¢ˇˇ */
	$"FFFF FFFF FF9B FFFF FF5B FFFF FFD3 FFFF"            /* ˇˇˇˇˇõˇˇˇ[ˇˇˇ”ˇˇ */
	$"FF00 0000 003B 0000 0000 0000 007B 0000"            /* ˇ....;.......{.. */
	$"004B 0000 0002 0000 0000 0000 007F 0000"            /* .K.............. */
	$"0037 0000 0002 0000 007B 0000 0000 0000"            /* .7.......{...... */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 007B 0000 008B 0000"            /* .........{...ã.. */
	$"0000 0000 0070 0000 0050 0000 0000 0000"            /* .....p...P...... */
	$"005B 0000 046A 0000 0018 0000 F1F1 F1F1"            /* .[...j......ÒÒÒÒ */
	$"F1F1 0001 F5F5 F5F5 F5F5 0002 F6F6 F6F6"            /* ÒÒ..ıııııı..ˆˆˆˆ */
	$"F6F6 0003 F0F0 F0F0 F0F0 0004 EFEF EFEF"            /* ˆˆ....ÔÔÔÔ */
	$"EFEF 0005 F4F4 F4F4 F4F4 0006 CDCD CDCD"            /* ÔÔ..ÙÙÙÙÙÙ..ÕÕÕÕ */
	$"CDCD 0007 3030 3030 3030 0008 F3F3 F3F3"            /* ÕÕ..000000..ÛÛÛÛ */
	$"F3F3 0009 D1D1 D1D1 D1D1 000A EEEE EEEE"            /* ÛÛ.∆——————.¬ÓÓÓÓ */
	$"EEEE 000B D0D0 D0D0 D0D0 000C EDED EDED"            /* ÓÓ..––––––..ÌÌÌÌ */
	$"EDED 000D CBCB CBCB CBCB 000E F2F2 F2F2"            /* ÌÌ..ÀÀÀÀÀÀ..ÚÚÚÚ */
	$"F2F2 000F ECEC ECEC ECEC 0010 EBEB EBEB"            /* ÚÚ..ÏÏÏÏÏÏ..ÎÎÎÎ */
	$"EBEB 0011 EAEA EAEA EAEA 0012 C9C9 C9C9"            /* ÎÎ..ÍÍÍÍÍÍ..………… */
	$"C9C9 0013 CCCC CCCC CCCC 0014 E8E8 E8E8"            /* ……..ÃÃÃÃÃÃ..ËËËË */
	$"E8E8 0015 E7E7 E7E7 E7E7 0016 C6C6 C6C6"            /* ËË..ÁÁÁÁÁÁ..∆∆∆∆ */
	$"C6C6 0017 E5E5 E5E5 E5E5 0018 E4E4 E4E4"            /* ∆∆..ÂÂÂÂÂÂ..‰‰‰‰ */
	$"E4E4 0000 0000 0000 0000 0000 0000 0000"            /* ‰‰.............. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0102 0201 0102 0201 0102 0201 0102"            /* ................ */
	$"0201 0102 0201 0102 0201 0102 0202 0102"            /* ................ */
	$"0202 0102 0202 0102 0202 0102 0202 0102"            /* ................ */
	$"0202 0303 0003 0303 0303 0303 0303 0300"            /* ................ */
	$"0303 0300 0303 0303 0003 0304 0003 0303"            /* ................ */
	$"0003 0303 0003 0403 0303 0303 0303 0304"            /* ................ */
	$"0303 0505 0303 0304 0303 0607 0303 0505"            /* ................ */
	$"0105 0505 0105 0505 0501 0805 0501 0505"            /* ................ */
	$"0509 0707 0505 0505 0808 0805 0808 0805"            /* .∆.............. */
	$"0508 0A0A 0508 0805 0B07 0707 0508 0A0A"            /* ..¬¬..........¬¬ */
	$"0A0A 0A0A 0A0A 0A0A 0A0A 0A0C 0A0A 0A0D"            /* ¬¬¬¬¬¬¬¬¬¬¬.¬¬¬. */
	$"0707 0707 0A0A 0C0A 0A0A 0A0A 0A0A 0A0C"            /* ....¬¬.¬¬¬¬¬¬¬¬. */
	$"0A0A 000E 0A07 0707 0707 0707 0A0A 0E00"            /* ¬¬..¬.......¬¬.. */
	$"0E00 0000 0E00 000E 000E 0003 0007 0707"            /* ................ */
	$"0707 0707 0000 0300 0000 0000 0000 0003"            /* ................ */
	$"0000 0F10 0007 0707 0707 0707 0000 1010"            /* ................ */
	$"100F 0F10 100F 0F10 1010 1010 1007 0707"            /* ................ */
	$"0707 0707 100F 1011 1010 1011 1010 1010"            /* ................ */
	$"1110 0404 1110 1012 0707 0707 1110 0404"            /* ................ */
	$"0404 0404 0404 0404 0404 0A04 0404 0404"            /* ..........¬..... */
	$"1307 0707 0404 040A 0A0A 0A0A 0A0A 0A04"            /* .......¬¬¬¬¬¬¬¬. */
	$"0A0A 1414 0A0A 0A04 0A0D 0707 0A0A 1414"            /* ¬¬..¬¬¬.¬...¬¬.. */
	$"1414 1414 1414 1414 1414 1415 1414 1414"            /* ................ */
	$"1414 1607 1414 1515 1514 1415 1514 1415"            /* ................ */
	$"1515 1010 1515 1415 1515 1415 1514 1010"            /* ................ */
	$"1011 1010 1011 1010 1011 1111 1111 1111"            /* ................ */
	$"1111 1111 1111 1111 1111 1111 1111 1111"            /* ................ */
	$"1111 1717 1718 1717 1718 1717 1718 1717"            /* ................ */
	$"1718 1717 1718 1717 1718 1010 1011 1010"            /* ................ */
	$"1011 1010 1011 1010 1011 1010 1011 1010"            /* ................ */
	$"1011 1111 1111 1111 1111 1111 1111 1111"            /* ................ */
	$"1111 1111 1111 1111 1111 1717 1718 1717"            /* ................ */
	$"1718 1717 1718 1717 1718 1717 1718 1717"            /* ................ */
	$"1718"                                               /* .. */
};

