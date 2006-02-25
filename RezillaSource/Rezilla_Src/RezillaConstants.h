// ===========================================================================
// RezillaConstants.h
// 
//                       Created : 2003-04-16 22:52:54
//             Last modification : 2006-02-24 00:11:52
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@users.sourceforge.net>
// www : <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2003-2006
// All rights reserved.
// ===========================================================================

#pragma once


// ======================================================================
// Enums
// ======================================================================

// Fork indices
enum
{	
	fork_undefinedfork = -1,
	fork_anyfork = 0,
	fork_samefork = 0,
	fork_rezfork,
	fork_datafork
};

// App strings indices
enum
{	
	idxAppName = 1,
	idxRezFilePrompt,
	idxReourcePrompt,
	idxRsrcDefaultName,
	idxIcnsDefaultName
};

// Refnum constants
// Use kResFileNotOpened and kSystemResFile (defined in Resources.h)

// Export formats
enum
{	
	exportMap_Xml = 0,
	exportMap_Text,
	exportMap_Html,
	exportMap_Derez
};

enum
{	
	exportAete_Xml = 0,
	exportAete_Derez,
	exportMap_Sdef,
	exportAete_Text,
	exportAete_Html
};

// DTDs
enum
{	
	export_KeyDtd = 1,		// Key-based DTD
	export_AttrDtd = 2		// Attrs-based DTD
};

// Binary encodings
enum
{	
	export_Base64Enc = 1,	// Base64 encoding for binary data
	export_HexEnc = 2		// Hexadecimal encoding for binary data
};

// Symbol used in templates to designate hexadecimal data
enum
{	
	hex_SymbDollar = 1,
	hex_Symb0x = 2
};

// Format used in templates to display Rect data: "top, left, bottom, 
// right" or "top, left, width, height"
enum
{	
	rect_TLBR = 1,
	rect_TLWH = 2
};

// Which case (lower or upper) for hexadecimal letters
enum
{	
	hex_lowercase = 1,
	hex_uppercase = 2
};

// Rez comparison results
enum
{	
	compare_noDiff = 0,
	compare_sizeDiff,
	compare_dataDiff,
	compare_nameDiff,
	compare_flagDiff
};

enum {	
	compare_displayAsHex = 1,
	compare_displayAsTxt
};

// The indices of the MultiPanel's views
enum {
	mpv_General = 1,
	mpv_Interface,
	mpv_Templates,
	mpv_Editors,
	mpv_Compare,
	mpv_Export,
	mpv_Misc
};

// Pref style element constants
enum
{	
	style_fontType = 1,
	style_sizeType,
	style_faceType
};

// Types of values returned by GetPaneCount() functions
enum {
	count_LinesPerPane,
	count_BytesPerLine,
	count_BytesPerPane
};

// Kind of editor
enum
{	
	editor_kindGui,
	editor_kindTmpl,
	editor_kindHex,
	editor_kindPlug
};

// Bitmap editor
// -------------
// Supported image types
enum
{	
	ImgType_LargeIcon			= FOUR_CHAR_CODE('ICON'),
	ImgType_IconSuite			= FOUR_CHAR_CODE('SICN'),
	
	ImgType_LargeIconWithMask	= FOUR_CHAR_CODE('ICN#'),
	ImgType_LargeIconMask		= FOUR_CHAR_CODE('ICN#'),
	ImgType_Large4BitIcon		= FOUR_CHAR_CODE('icl4'),
	ImgType_Large8BitIcon		= FOUR_CHAR_CODE('icl8'),
	
	ImgType_SmallIconWithMask	= FOUR_CHAR_CODE('ics#'),
	ImgType_SmallIconMask		= FOUR_CHAR_CODE('ics#'),
	ImgType_Small4BitIcon		= FOUR_CHAR_CODE('ics4'),
	ImgType_Small8BitIcon		= FOUR_CHAR_CODE('ics8'),
	
	ImgType_MiniIconWithMask	= FOUR_CHAR_CODE('icm#'),
	ImgType_MiniIconMask		= FOUR_CHAR_CODE('icm#'),
	ImgType_Mini4BitIcon		= FOUR_CHAR_CODE('icm4'),
	ImgType_Mini8BitIcon		= FOUR_CHAR_CODE('icm8'),
	
	ImgType_ColorIcon			= FOUR_CHAR_CODE('cicn'),
	ImgType_Picture				= FOUR_CHAR_CODE('PICT'),
	
	ImgType_PatternSuite		= FOUR_CHAR_CODE('PAT#'),
	ImgType_Pattern				= FOUR_CHAR_CODE('PAT '),
	ImgType_PixPat				= FOUR_CHAR_CODE('ppat'),
	ImgType_Cursor				= FOUR_CHAR_CODE('CURS'),
	ImgType_ColorCursor			= FOUR_CHAR_CODE('crsr')
};

// Resizing flags for Icon editor
enum {
	resize_None			= 0x00,
	resize_Canvas		= 0x01,
	resize_MoveSamples	= 0x02,
	resize_Window		= 0x04,
	resize_All			= 0xFF
};

// Indices for elements of 'icns' resources
enum {
	icns_Thumbnail32BitData	= 0,	// 'it32'
	icns_Thumbnail8BitMask,			// 't8mk'
	icns_Huge1BitMask,				// 'ich#'
	icns_Huge4BitData,				// 'ich4'
	icns_Huge8BitData,				// 'ich8'
	icns_Huge32BitData,				// 'ih32'
	icns_Huge8BitMask,				// 'h8mk'
	icns_Large1BitMask,				// 'ICN#'
	icns_Large4BitData,				// 'icl4'
	icns_Large8BitData,				// 'icl8'
	icns_Large32BitData,			// 'il32'
	icns_Large8BitMask,				// 'l8mk'
	icns_Small1BitMask,				// 'ics#'
	icns_Small4BitData,				// 'ics4'
	icns_Small8BitData,				// 'ics8'
	icns_Small32BitData,			// 'is32'
	icns_Small8BitMask,				// 's8mk'
	icns_Mini1BitMask,				// 'icm#'
	icns_Mini4BitData,				// 'icm4'
	icns_Mini8BitData,				// 'icm8'
	icns_TileIconVariant,			// 'tile'
	icns_RolloverIconVariant,		// 'over'
	icns_DropIconVariant,			// 'drop'
	icns_OpenIconVariant,			// 'open'
	icns_OpenDropIconVariant		// 'odrp'
};

// AETE editor
// -----------
// The indices of the aete editor's MultiPanels views
enum {
	mpv_AeteEvent = 1,
	mpv_AeteClass,
	mpv_AeteCompOp,
	mpv_AeteEnum
};

// Terminology objects
enum {
	kind_AeteSuite = 0,
	kind_AeteEvent = 1,
	kind_AeteClass,
	kind_AeteCompOp,
	kind_AeteEnum,
	kind_AeteParameter,
	kind_AeteProperty,
	kind_AeteElement,
	kind_AeteKeyForm,
	kind_AeteEnumerator,
	kind_AeteDirectParam,
	kind_AeteReply
};

// These complete the kAEUT* constants from AEUserTermTypes.h
enum {
	aeut_NonVerbEvent		= 3,
	aeut_LabeledParam		= 3
};

// MENU editor
// -----------
// Menu item properties
enum {
	kind_MenuAllEnabled		= 0,
	kind_MenuNoProperty		= 1,
	kind_MenuIsSeparator,
	kind_MenuHasSubmenu,
	kind_MenuUsesCicn,
	kind_MenuUsesICON,
	kind_MenuUsesSICN,
	kind_MenuNonSystemScript
};

// Index of property labels (in resource STRx_MenuEditorLabels)
enum {
	indx_MenuMarkChar		= 1,
	indx_MenuSubID,
	indx_MenuIconID,
	indx_MenuScriptCode
};


// ======================================================================
// Resource ID's
// ======================================================================

const ResIDT	DITL_NewMap					= 10001;
const ResIDT	DITL_OpenMap				= 10002;
const ResIDT	DITL_SaveMap				= 10003;

const ResIDT	PPob_RezMapWindow			= 1000;
const ResIDT	PPob_InspectorWindow		= 2000;
const ResIDT	PPob_NewRezDialog			= 2100;
const ResIDT	PPob_HexEditorWindow		= 3000;
const ResIDT	PPob_RezPickerWindow		= 4000;
const ResIDT	PPob_AboutWindow			= 5000;
const ResIDT	PPob_LicenceWindow			= 5100;
const ResIDT	PPob_RezCompDialog			= 6000;
const ResIDT	PPob_RezCompWindow			= 6500;
const ResIDT	PPob_PrefsWindow			= 7000;
const ResIDT	PPob_PrefsGeneralPane		= 7100;
const ResIDT	PPob_PrefsInterfacePane		= 7200;
const ResIDT	PPob_PrefsTemplatesPane		= 7300;
const ResIDT	PPob_PrefsEditorsPane		= 7400;
const ResIDT	PPob_PrefsComparePane		= 7500;
const ResIDT	PPob_PrefsExportPane		= 7600;
const ResIDT	PPob_PrefsMiscPane			= 7700;
const ResIDT	PPob_GetValueDialog			= 8400;
const ResIDT	PPob_FindDialog				= 8500;
const ResIDT	PPob_FontSizeDialog			= 8600;
const ResIDT	PPob_ImageResizeDialog		= 8900;
const ResIDT	PPob_RezTypeChooser			= 8700;
const ResIDT	PPob_TmplKeyChooser			= 8800;
const ResIDT	PPob_SimpleMessage			= 9500;
const ResIDT	PPob_AskIfMessage			= 9510;
const ResIDT	PPob_AskYesNoMessage		= 9520;
const ResIDT	PPob_ExplainedError			= 9530;
const ResIDT	PPob_AskUniqueID			= 9550;
const ResIDT	PPob_TmplEditorWindow		= 10100;
const ResIDT	PPob_TextEditorWindow		= 10200;
const ResIDT	PPob_MenuEditorWindow		= 10300;
const ResIDT	PPob_PictEditorWindow		= 10400;
const ResIDT	PPob_UtxtEditorWindow		= 10500;
const ResIDT	PPob_IconEditorWindow		= 10600;
const ResIDT	PPob_IconFamilyEditor		= 10600;
const ResIDT	PPob_CICNEditor				= 10601;
const ResIDT	PPob_ICONEditor				= 10602;
const ResIDT	PPob_PictEditor				= 10603;
const ResIDT	PPob_CursorEditor			= 10604;
const ResIDT	PPob_ColorCursorEditor		= 10605;
const ResIDT	PPob_PatternEditor			= 10606;
const ResIDT	PPob_PixPatEditor			= 10607;
const ResIDT	PPob_PatternSuiteEditor		= 10608;
const ResIDT	PPob_IconSuiteEditor		= 10609;
const ResIDT	PPob_AeteEditorWindow		= 11000;
const ResIDT	PPob_AeteEventPane			= 11100;
const ResIDT	PPob_AeteClassPane			= 11200;
const ResIDT	PPob_AeteCompOpPane			= 11300;
const ResIDT	PPob_AeteEnumPane			= 11400;
const ResIDT	PPob_StrxEditorWindow		= 11500;
const ResIDT	PPob_PluginEditorWindow		= 12000;

const ResIDT	ics8_Unlocked				= 1500;
const ResIDT	ics8_Locked					= 1501;

const ResIDT	STRx_RzilErrorStrings		= 1000;
const ResIDT	STRx_PrefsCtrlList			= 1004;
const ResIDT	STRx_DefaultDocTitles		= 1500;
const ResIDT	STRx_RzilWinMenuItem		= 1501;
const ResIDT	STRx_NavStrings				= 1502;
const ResIDT	STRx_FileExtensions			= 1503;
const ResIDT	STRx_InternetUrls			= 1504;
const ResIDT	STRx_LanguageCodes			= 1601;
const ResIDT	STRx_RegionCodes			= 1602;
const ResIDT	STRx_ScriptCodes			= 1603;
const ResIDT	STRx_PaintUndo				= 1700;
const ResIDT	STRx_PaintRedo				= 1701;
const ResIDT	STRx_AeteAdd				= 1710;
const ResIDT	STRx_AeteRemove				= 1711;
const ResIDT	STRx_MenuEditorLabels		= 1712;
const ResIDT	STRx_MenuIconID				= 1713;

// Text traits resources
const ResIDT    Txtr_GenevaNine				= 130;
const ResIDT    Txtr_GenevaTenBold          = 131;
const ResIDT	Txtr_MonacoNineDefault		= 139;
const ResIDT	Txtr_MonacoNineGray			= 133;
const ResIDT	Txtr_GenevaTen				= 140;
const ResIDT	Txtr_MonacoBlueNineCenter	= 141;
const ResIDT	Txtr_MonacoBlackNineCenter	= 142;
const ResIDT	Txtr_GenevaTenBoldUlLeft	= 144;
const ResIDT	Txtr_GenevaTenBoldUlRight	= 145;
const ResIDT	Txtr_UrlHyperlink			= 146;
const ResIDT	Txtr_GenevaTenBoldLeft		= 149;
const ResIDT	Txtr_GenevaTenBoldRight		= 150;
const ResIDT	Txtr_GenevaTenBoldUl		= 151;

// Menu resources
	// MENU_OpenedWindows is not a resource. It is built  
	// in CRezillaApp::InstallWindowMenu()
const ResIDT	MENU_OpenedWindows			= 1300;  
const ResIDT	MENU_Help					= 2000;
const ResIDT	MENU_RecentItems			= 140;  
const ResIDT	MENU_TemplateCases			= 150;  
const ResIDT	MENU_TextFonts				= 250;  
const ResIDT	MENU_TextSize				= 251;  
const ResIDT	MENU_TextStyle				= 252;  
const ResIDT	MENU_UnicodeFonts			= 255;  
const ResIDT	MENU_UnicodeSize			= 256;  
const ResIDT	MENU_UnicodeStyle			= 257;  
const ResIDT	MENU_EmptyPopup				= 260;  
const ResIDT	MENU_StartHierMenuID		= 500;  

// Icon editor
const ResIDT	Txtr_PaintFont				= Txtr_GenevaNine;
const ResIDT	RidL_ToolList				= 300;
const ResIDT	MENU_IconActions			= 300;
const ResIDT	MENU_IconColors				= 301;
const ResIDT	MENU_IconFonts				= 302;
const ResIDT	MENU_IconStyle				= 303;

// Aete editor
const ResIDT	MENU_AeteTerminology		= 160;
const ResIDT	MENU_AeteDirectOptions		= 161;
const ResIDT	MENU_AeteReplyOptions		= 162;
const ResIDT	MENU_AeteParameterOptions	= 163;
const ResIDT	MENU_AetePropertyOptions	= 164;

// Plugin editor
const ResIDT	MENU_PluginEditor			= 500;

// Icon resources
const ResIDT	Icon_WindowsMenu			= 3100;
const ResIDT	Clut_IconColors 			= 9000;

// Cursors
const ResIDT	CURS_HandOneFinger	= 1000;
const ResIDT	CURS_Lasso			= 9000;
const ResIDT	CURS_Eraser			= 9001;
const ResIDT	CURS_Pencil			= 9002;
const ResIDT	CURS_Dropper		= 9003;
const ResIDT	CURS_HandFingers	= 9004;
const ResIDT	CURS_Plus			= 9005;
const ResIDT	CURS_Bucket			= 9006;
const ResIDT	CURS_TextBeam		= 9007;
const ResIDT	CURS_HandNoFinger	= 9010;
const ResIDT	CURS_HotSpot		= 9011;
const ResIDT	CURS_Square			= 9012;
const ResIDT	CURS_Cross			= 9013;

// Phony ID used to indicate "the color picker" in the Icon editor
const ResIDT	ColorTable_UsePicker		= 0;
const ResIDT	IconEditor_EmptyDefaults	= 9200;


// Indices in STR# resources
// -------------------------
// Indices of STR# 1500: untitled windows names
const SInt16	index_RezMapUntitled		= 1;
const SInt16	index_RezMapUntitledX		= 2;
const SInt16	index_CompWinUntitled		= 3;
const SInt16	index_CompWinUntitledX		= 4;
const SInt16	index_EditorDocUntitled		= 5;
const SInt16	index_EditorDocUntitledX	= 6;
const SInt16	index_ExportUntitled		= 7;
const SInt16	index_PickerDocUntitled		= 8;
const SInt16	index_PickerDocUntitledX	= 9;
// Indices of STR# 1501: windows menu items
const SInt16	index_WinMenuInspector		= 1;
const SInt16	index_WinMenuTypeInspector	= 2;
const SInt16	index_WinMenuRezInspector	= 3;
// Indices of STR# 1502: save as names
const SInt16	index_RezillaAppName		= 1;
const SInt16	index_SaveRezFileAs			= 2;
const SInt16	index_SaveResourceAs		= 3;
const SInt16	index_SaveUntitledRsrc		= 4;
const SInt16	index_SaveUntitledIcon		= 5;
const SInt16	index_CreateNewRezMap		= 6;
const SInt16	index_CreateUntitled		= 7;
const SInt16	index_ExportMapAs			= 8;
const SInt16	index_ExportUntitledXml		= 9;
const SInt16	index_ExportUntitledTxt		= 10;
// Indices of STR# 1503: file extensions
const SInt16	index_NoExt					= 1;
const SInt16	index_ExtRsrc				= 2;
const SInt16	index_ExtXml				= 3;
const SInt16	index_ExtText				= 4;
const SInt16	index_ExtHtml				= 5;
const SInt16	index_ExtR					= 6;
const SInt16	index_ExtIcns				= 7;
const SInt16	index_ExtSdef				= 8;
// Indices of STR# 7000 and 7001: undo/redo for icon editor
const SInt16	index_UndoLine				= 1;
const SInt16	index_UndoBucket			= 2;
const SInt16	index_UndoRect				= 3;
const SInt16	index_UndoRoundRect			= 4;
const SInt16	index_UndoOval				= 5;
const SInt16	index_UndoEraser			= 6;
const SInt16	index_UndoPen				= 7;
const SInt16	index_UndoMove				= 8;
const SInt16	index_UndoFlip				= 9;
const SInt16	index_UndoRotate			= 10;
const SInt16	index_UndoGeneric			= 11;
const SInt16	index_UndoEraseAll			= 12;
const SInt16	index_UndoCut				= 13;
const SInt16	index_UndoPaste				= 14;
const SInt16	index_UndoClear				= 15;
const SInt16	index_UndoTransparent		= 16;
const SInt16	index_UndoDrag				= 17;
const SInt16	index_UndoHotSpot			= 18;
const SInt16	index_UndoRecolor			= 19;
const SInt16	index_UndoResize			= 20;
const SInt16	index_UndoDeleteImage		= 21;
const SInt16	index_UndoText				= 22;



// ======================================================================
// Menu commands
// ======================================================================
// Values the PP menu commands are based on
const CommandT	cmd_MenuFileBase			= 1000;
const CommandT	cmd_MenuEditBase			= 1100;
const CommandT	cmd_MenuResourceBase		= 1200;
// const CommandT	cmd_MenuWindowsBase			= 1300;  // reserved
// Text editor
const CommandT	cmd_MenuTextSizeBase		= 1400;		// font sizes are (cmdID - 1400)
const CommandT	cmd_MenuTextSizeLast		= 1489;		// and within this range
const CommandT	cmd_MenuTextWrap			= 1490;
// Unicode editor
const CommandT	cmd_MenuUtxtSizeBase		= 1500;		// font sizes are (cmdID - 1400)
const CommandT	cmd_MenuUtxtSizeLast		= 1599;		// and within this range
// Bitmap editor
const CommandT	cmd_IconFontSizeBase		= 9100;		// font sizes are (cmdID - 9100)
const CommandT	cmd_IconFontSizeLast		= 9300;		// and within this range
// Bitmap editor
const CommandT	cmd_MenuAeteBase			= 1600;

// Internal use commands
// const CommandT	cmd_ResetTypingAction		= 4000;


// Help menu commands
const CommandT	cmd_Help					= 3000;	
// Window menu commands
const CommandT	cmd_ShowInspector			= 2001;	

// Resource menu commands
const CommandT	cmd_NewRez				= cmd_MenuResourceBase + 1;	
const CommandT	cmd_EditRez				= cmd_MenuResourceBase + 2;	
const CommandT	cmd_TmplEditRez			= cmd_MenuResourceBase + 3;	
const CommandT	cmd_HexEditRez			= cmd_MenuResourceBase + 4;	
const CommandT	cmd_EditRezAsType		= cmd_MenuResourceBase + 5;	
const CommandT	cmd_EditWithPlugin		= cmd_MenuResourceBase + 6;	
const CommandT	cmd_RemoveRez			= cmd_MenuResourceBase + 10;	
const CommandT	cmd_DuplicateRez		= cmd_MenuResourceBase + 11;	
const CommandT	cmd_GetRezInfo			= cmd_MenuResourceBase + 15;
const CommandT	cmd_TmplEditAsRez		= cmd_MenuResourceBase + 99;	// Phony Cmd used for redirection
// File menu commands
const CommandT	cmd_ExportMap			= cmd_MenuFileBase + 1;	
const CommandT	cmd_RecentItems			= cmd_MenuFileBase + 2;	
// Edit menu commands
const CommandT	cmd_Find				= cmd_MenuEditBase + 1;	
const CommandT	cmd_FindNext			= cmd_MenuEditBase + 2;	
const CommandT	cmd_RezCompare			= cmd_MenuEditBase + 3;	

// Icon editor commands
const CommandT	cmd_IconMoveSelection		= FOUR_CHAR_CODE('MOVE');
const CommandT	cmd_IconEraseAll			= FOUR_CHAR_CODE('ERAL');
const CommandT	cmd_IconFlipVertical		= FOUR_CHAR_CODE('FLPV');
const CommandT	cmd_IconFlipHorizontal		= FOUR_CHAR_CODE('FLPH');
const CommandT	cmd_IconRotateRight			= FOUR_CHAR_CODE('ROTR');  // Clockwise
const CommandT	cmd_IconRotateLeft			= FOUR_CHAR_CODE('ROTL');  // CounterClockwise
const CommandT	cmd_IconTransparent			= FOUR_CHAR_CODE('TRAN');
const CommandT	cmd_IconShowBitmap			= FOUR_CHAR_CODE('BITM');
const CommandT	cmd_IconShowMask			= FOUR_CHAR_CODE('MASK');
const CommandT	cmd_IconDragImage			= FOUR_CHAR_CODE('DRAG');
const CommandT	cmd_IconRecolorCurrentImage	= FOUR_CHAR_CODE('RWCT');  // Recolor With Current Table
const CommandT	cmd_IconResizeImage			= FOUR_CHAR_CODE('RSZI');
const CommandT	cmd_IconDeleteImage			= FOUR_CHAR_CODE('DELI');
// 	Color Menu Command IDs
const CommandT	cmd_ColorTableAppleIcon		= FOUR_CHAR_CODE('CLT1');
const CommandT	cmd_ColorTableApple256		= FOUR_CHAR_CODE('CLT2');
const CommandT	cmd_ColorTableApple256Gray	= FOUR_CHAR_CODE('CLT3');
const CommandT	cmd_ColorTableApple16		= FOUR_CHAR_CODE('CLT4');
const CommandT	cmd_ColorTableApple16Gray	= FOUR_CHAR_CODE('CLT5');
const CommandT	cmd_ColorTableApple4Gray	= FOUR_CHAR_CODE('CLT6');
const CommandT	cmd_ColorTablePicker		= FOUR_CHAR_CODE('CLT7');
const CommandT	cmd_ColorTableApple2		= FOUR_CHAR_CODE('CLT8');  // Not in the menu, but used in the code
const CommandT	cmd_BlackAndWhite			= FOUR_CHAR_CODE('tBnW');
const CommandT	cmd_SwapColors				= FOUR_CHAR_CODE('tSWP');
const CommandT	cmd_IconOtherFontSize		= cmd_IconFontSizeBase;

// Aete editor commands
const CommandT	cmd_AeteAddSuite			= cmd_MenuAeteBase + 1;
const CommandT	cmd_AeteRemoveSuite			= cmd_MenuAeteBase + 2;
const CommandT	cmd_AeteAddItem				= cmd_MenuAeteBase + 3;
const CommandT	cmd_AeteRemoveItem			= cmd_MenuAeteBase + 4;
const CommandT	cmd_AeteAddParameter		= cmd_MenuAeteBase + 5;
const CommandT	cmd_AeteRemoveParameter		= cmd_MenuAeteBase + 6;
const CommandT	cmd_AeteAddProperty			= cmd_MenuAeteBase + 7;
const CommandT	cmd_AeteRemoveProperty		= cmd_MenuAeteBase + 8;
const CommandT	cmd_AeteAddElement			= cmd_MenuAeteBase + 9;
const CommandT	cmd_AeteRemoveElement		= cmd_MenuAeteBase + 10;
const CommandT	cmd_AeteAddKeyForm			= cmd_MenuAeteBase + 11;
const CommandT	cmd_AeteRemoveKeyForm		= cmd_MenuAeteBase + 12;
const CommandT	cmd_AeteAddEnumerator		= cmd_MenuAeteBase + 13;
const CommandT	cmd_AeteRemoveEnumerator	= cmd_MenuAeteBase + 14;
const CommandT	cmd_AeteImport				= cmd_MenuAeteBase + 21;
const CommandT	cmd_AeteExport				= cmd_MenuAeteBase + 22;


// ======================================================================
// Control ID's
// ======================================================================
// Rez Map Window
// --------------
const PaneIDT   item_OutlineTable			= FOUR_CHAR_CODE('TABL');
const PaneIDT	item_TypesNum				= 1;
const PaneIDT	item_ResourcesNum			= 2;
const PaneIDT	item_WhichFork				= 3;
// Inspector Window
// ----------------
const PaneIDT	item_InspType				= 1;
const PaneIDT	item_InspSize				= 3;
const PaneIDT	item_InspMapName			= 4;
const PaneIDT	item_InspEditID				= 5;
const PaneIDT	item_InspEditName			= 6;
const PaneIDT	item_InspIcon				= 9;
const PaneIDT	item_InspSysHeap			= 11;
const PaneIDT	item_InspPurgeable			= 12;
const PaneIDT	item_InspLocked				= 13;
const PaneIDT	item_InspProtected			= 14;
const PaneIDT	item_InspPreload			= 15;
const PaneIDT	item_InspRevert				= 20;
const PaneIDT   item_InspModify				= 21;
// Hex Edit Window
// ---------------
const PaneIDT	item_HexScroller			= 1;
const PaneIDT	item_HexDataWE				= 2;
const PaneIDT	item_TxtDataWE				= 3;
const PaneIDT	item_HexLineEdit			= 4;
const PaneIDT	item_HexOffsetEdit			= 5;
const PaneIDT	item_HexEditGroupBox		= 10;
// New Resource Window
// -------------------
const PaneIDT	item_NewType				= 1;
const PaneIDT	item_NewID					= 3;
const PaneIDT	item_NewName				= 4;
const PaneIDT	item_NewSysHeap				= 11;
const PaneIDT	item_NewPurgeable			= 12;
const PaneIDT	item_NewLocked				= 13;
const PaneIDT	item_NewProtected			= 14;
const PaneIDT	item_NewPreload				= 15;
const PaneIDT	item_NewUniqueID			= 20;
// About box
// ---------
const PaneIDT	item_AboutOkButton			= FOUR_CHAR_CODE('ok  ');
const PaneIDT	item_AboutVersCaption		= FOUR_CHAR_CODE('Vers');
const PaneIDT	item_AboutLicenceButton		= FOUR_CHAR_CODE('Lcnc');
const PaneIDT	item_AboutUrlsBase			= 11;
// Find Dialog
// -----------
const PaneIDT	item_FindSearchField		= 1;
const PaneIDT	item_FindInHexRadio			= 2;
const PaneIDT	item_FindInTxtRadio			= 3;
const PaneIDT	item_FindIgnoreCase			= 4;
const PaneIDT	item_FindRegexp				= 5;
const PaneIDT	item_FindInPaneRGV			= 6;
// Rez Compare Dialog
// ------------------
const PaneIDT	item_RezCompSetOld			= 1;
const PaneIDT	item_RezCompEditOld			= 2;
const PaneIDT	item_RezCompSetNew			= 3;
const PaneIDT	item_RezCompEditNew			= 4;
const PaneIDT	item_RezCompIgnoreNames		= 5;
const PaneIDT	item_RezCompIgnoreAttrs		= 6;
const PaneIDT	item_RezCompIgnoreData		= 7;
// Rez Compare Results Window
// --------------------------
const PaneIDT	item_CompResultScroller		= 1;
const PaneIDT	item_CompResultOldStatic	= 2;
const PaneIDT	item_CompResultNewStatic	= 3;
const PaneIDT	item_CompResultOldHex		= 4;
const PaneIDT	item_CompResultNewHex		= 5;
const PaneIDT	item_CompResultIgnStatic	= 8;
const PaneIDT	item_CompResultCriteria		= 9;
const PaneIDT	item_CompResultOnlyOldTbl	= 11;
const PaneIDT	item_CompResultDifferingTbl	= 13;
const PaneIDT	item_CompResultOnlyNewTbl	= 15;
const PaneIDT	item_CompResultEditGroupBox	= 20;
const PaneIDT	item_CompResultShowAsRgbx	= 25;
const PaneIDT	item_CompResultHexRadio		= 26;
const PaneIDT	item_CompResultTxtRadio		= 27;
// Ask Unique ID dialog
// --------------------
const PaneIDT	item_UidOtherConflicts		= 1;
// Resource Type Chooser
// ---------------------
const PaneIDT	item_TypeChooserField		= 1;
const PaneIDT	item_TypeChooserMenu		= 2;
// Template Key Chooser
// --------------------
const PaneIDT	item_TmplKeyChooserType		= 1;
const PaneIDT	item_TmplKeyChooserMessage	= 2;
const PaneIDT	item_TmplKeyChooserLabel	= 3;
const PaneIDT	item_TmplKeyChooserMenu		= 4;

// Preferences
// -----------
const PaneIDT   item_PrefsOkButton			= 1;
const PaneIDT   item_PrefsCancelButton		= 2;
const PaneIDT   item_RevertPrefs			= 3;
const PaneIDT   item_PrefsPageController	= FOUR_CHAR_CODE('PCTL');
const PaneIDT   item_PrefsMultiPanelView	= FOUR_CHAR_CODE('PMPV');
//     General Prefs Pane
//     ------------------
const PaneIDT	item_GenPrefsMaxRecent		= 2;
const PaneIDT	item_GenPrefsResetRecent	= 3;
const PaneIDT	item_GenPrefsNewMapRgbx		= 5;
const PaneIDT	item_GenPrefsResourceFork	= 6;
const PaneIDT	item_GenPrefsDataFork		= 7;
//     Export Prefs Pane
//     -----------------
const PaneIDT	item_ExpPrefsDtdRgbx		= 2;
const PaneIDT	item_ExpPrefsKeyDtd			= 3;
const PaneIDT	item_ExpPrefsAttrDtd		= 4;
const PaneIDT	item_ExpPrefsInclBinData	= 5;
const PaneIDT	item_ExpPrefsEncRgbx		= 6;
const PaneIDT	item_ExpPrefsHexEnc			= 7;
const PaneIDT	item_ExpPrefsBase64Enc		= 8;
const PaneIDT	item_ExpPrefsEditSig		= 9;
//     Compare Prefs Pane
//     ------------------
const PaneIDT	item_CompPrefsIgnName		= 2;
const PaneIDT	item_CompPrefsIgnAttr		= 3;
const PaneIDT	item_CompPrefsIgnData		= 4;
const PaneIDT	item_CompPrefsDisplayRgbx	= 5;
const PaneIDT	item_CompPrefsHexDisplay	= 6;
const PaneIDT	item_CompPrefsTxtDisplay	= 7;
//     Interface Prefs Pane
//     --------------------
const PaneIDT	item_UIPrefsFontsMenu		= 2;
const PaneIDT	item_UIPrefsSizeMenu		= 3;
//     Templates Prefs Pane
//     --------------------
const PaneIDT	item_TmplPrefsHexSymRgbx		= 2;
const PaneIDT	item_TmplPrefsHexSym0x			= 3;
const PaneIDT	item_TmplPrefsHexSymDollar		= 4;
const PaneIDT	item_TmplPrefsHexCaseRgbx		= 5;
const PaneIDT	item_TmplPrefsHexLowercase		= 6;
const PaneIDT	item_TmplPrefsHexUppercase		= 7;
const PaneIDT	item_TmplPrefsDisplayFillers	= 8;
const PaneIDT	item_TmplPrefsEnableFillers		= 9;
const PaneIDT	item_TmplPrefsRectFormatRgbx	= 10;
const PaneIDT	item_TmplPrefsRectTLBR			= 11;
const PaneIDT	item_TmplPrefsRectTLWH			= 12;
//     Editors Prefs Pane
//     ------------------
const PaneIDT	item_EditPrefsUse8BitPicts	= 10;
const PaneIDT	item_EditPrefsUseFullTables	= 11;
const PaneIDT	item_EditPrefsDoFontSubst	= 20;
const PaneIDT	item_EditPrefsInsertBOM		= 21;
//     Misc Prefs Pane
//     ---------------
const PaneIDT	item_MiscPrefsSetSigOnClose		= 2;
const PaneIDT	item_MiscPrefsClosingType		= 3;
const PaneIDT	item_MiscPrefsClosingCreator	= 4;
const PaneIDT	item_MiscPrefsSetSigOnCreate	= 5;
const PaneIDT	item_MiscPrefsOnlyRsrcExt		= 6;
// Text Editor Window
// ------------------
const PaneIDT   item_TextEditLength		= 1;
const PaneIDT   item_TextEditWrap		= 2;
// Pict Viewer Window
// ------------------
const PaneIDT   item_PictEditSize		= 1;
const PaneIDT   item_PictEditWidth		= 2;
const PaneIDT   item_PictEditHeight		= 3;
// Utxt Editor Window
// ------------------
const PaneIDT   item_UtxtEditFontMenu	= 1;
const PaneIDT   item_UtxtEditSizeMenu	= 2;
const PaneIDT   item_UtxtEditStyleMenu	= 3;
const PaneIDT   item_UtxtEditLength		= 4;
// Icon Editor Windows
// -------------------
// Same values are used for the pane ID and for the message it broadcasts.
const PaneIDT	tool_None					= 0;
const PaneIDT	tool_Lasso					= FOUR_CHAR_CODE('tLAS');
const PaneIDT	tool_Selection				= FOUR_CHAR_CODE('tSEL');
const PaneIDT	tool_Text					= FOUR_CHAR_CODE('tTXT');
const PaneIDT	tool_Pencil					= FOUR_CHAR_CODE('tPEN');
const PaneIDT	tool_Eraser					= FOUR_CHAR_CODE('tERA');
const PaneIDT	tool_Bucket					= FOUR_CHAR_CODE('tBUC');
const PaneIDT	tool_Dropper				= FOUR_CHAR_CODE('tDRO');
const PaneIDT	tool_Line					= FOUR_CHAR_CODE('tLIN');
const PaneIDT	tool_Rect					= FOUR_CHAR_CODE('tREC');
const PaneIDT	tool_FilledRect				= FOUR_CHAR_CODE('tFRC');
const PaneIDT	tool_RoundRect				= FOUR_CHAR_CODE('tRRC');
const PaneIDT	tool_FilledRoundRect		= FOUR_CHAR_CODE('tFRR');
const PaneIDT	tool_Oval					= FOUR_CHAR_CODE('tOVL');
const PaneIDT	tool_FilledOval				= FOUR_CHAR_CODE('tFOV');
const PaneIDT	tool_HotSpot				= FOUR_CHAR_CODE('tHOT');
const PaneIDT	tool_Pattern				= FOUR_CHAR_CODE('tPAT');
const PaneIDT	tool_ForeColor				= FOUR_CHAR_CODE('tFCL');
const PaneIDT	tool_BackColor				= FOUR_CHAR_CODE('tBCL');		
const PaneIDT   item_IconCoords				= FOUR_CHAR_CODE('COOR');
const PaneIDT	item_CanvasEncloser			= FOUR_CHAR_CODE('ENCL');
const PaneIDT	item_IconSampleWell			= FOUR_CHAR_CODE('SAMP');
const PaneIDT	item_IconEditBWSample		= FOUR_CHAR_CODE('BWPT');
const PaneIDT	item_IconEditMask			= FOUR_CHAR_CODE('MASK');
const PaneIDT	item_IconSuiteSlider		= FOUR_CHAR_CODE('SLID');
const PaneIDT	item_IconCountField			= FOUR_CHAR_CODE('COUN');
const PaneIDT	item_IconLabelName1			= FOUR_CHAR_CODE('NAM1');
const PaneIDT	item_IconLabelName2			= FOUR_CHAR_CODE('NAM2');
const PaneIDT	item_IconLabelName3			= FOUR_CHAR_CODE('NAM3');
const PaneIDT	item_IconShowAsRgbx			= 4;
const PaneIDT	item_IconShowAsBitmap		= 5;
const PaneIDT	item_IconShowAsMask			= 6;
// Aete Editor Window
// ------------------
const PaneIDT   item_AeteMajorVersion		= 1;
const PaneIDT   item_AeteMinorVersion		= 2;
const PaneIDT   item_AeteLanguageID			= 3;
const PaneIDT   item_AeteScriptCode			= 4;
const PaneIDT   item_AeteSuiteName			= 5;
const PaneIDT   item_AeteSuiteDescr			= 6;
const PaneIDT   item_AeteSuiteID			= 7;
const PaneIDT   item_AeteSuiteLevel			= 8;
const PaneIDT   item_AeteSuiteVersion		= 9;
const PaneIDT   item_AeteSuitePopup			= FOUR_CHAR_CODE('SUIT');
const PaneIDT   item_AeteSuiteBox			= FOUR_CHAR_CODE('SUIB');
const PaneIDT   item_AetePanelController	= FOUR_CHAR_CODE('ACTL');
const PaneIDT   item_AeteMultiPanelView		= FOUR_CHAR_CODE('AMPV');
const PaneIDT   item_AeteItemSlider			= FOUR_CHAR_CODE('SLID');
const PaneIDT   item_AeteItemIndicator		= FOUR_CHAR_CODE('SIDC');
//    Events panel
const PaneIDT   item_AeteEventName			= 1;
const PaneIDT   item_AeteEventClass			= 2;
const PaneIDT   item_AeteEventID			= 3;
const PaneIDT   item_AeteEventDescr			= 4;
const PaneIDT   item_AeteDirectType			= 11;
const PaneIDT   item_AeteDirectOptions		= 12;
const PaneIDT   item_AeteDirectDescr		= 13;
const PaneIDT   item_AeteReplyType			= 21;
const PaneIDT   item_AeteReplyOptions		= 22;
const PaneIDT   item_AeteReplyDescr			= 23;
const PaneIDT   item_AeteParamName			= 31;
const PaneIDT   item_AeteParamKeyword		= 32;
const PaneIDT   item_AeteParamType			= 33;
const PaneIDT   item_AeteParamOptions		= 34;
const PaneIDT   item_AeteParamDescr			= 35;
// const PaneIDT   item_AeteDirectBox			= FOUR_CHAR_CODE('DRCT');
// const PaneIDT   item_AeteReplyBox			= FOUR_CHAR_CODE('REPL');
const PaneIDT   item_AeteParamBox			= FOUR_CHAR_CODE('OTHR');
const PaneIDT   item_AeteParamSlider		= FOUR_CHAR_CODE('OSLI');
const PaneIDT   item_AeteParamIndicator		= FOUR_CHAR_CODE('OIDC');
//    Classes panel
const PaneIDT   item_AeteClassName			= 1;
const PaneIDT   item_AeteClassID			= 2;
const PaneIDT   item_AeteClassDescr			= 3;
const PaneIDT   item_AetePropertyName		= 11;
const PaneIDT   item_AetePropertyKeyword	= 12;
const PaneIDT   item_AetePropertyType		= 13;
const PaneIDT   item_AetePropertyOptions	= 14;
const PaneIDT   item_AetePropertyDescr		= 15;
const PaneIDT   item_AeteElementClass		= 22;
const PaneIDT   item_AeteKeyFormID			= 23;
const PaneIDT   item_AetePropertyBox		= FOUR_CHAR_CODE('PROP');
const PaneIDT   item_AeteElementBox			= FOUR_CHAR_CODE('ELEM');
const PaneIDT   item_AetePropertySlider		= FOUR_CHAR_CODE('PSLI');
const PaneIDT   item_AetePropertyIndicator	= FOUR_CHAR_CODE('PIDC');
const PaneIDT   item_AeteElementSlider		= FOUR_CHAR_CODE('ESLI');
const PaneIDT   item_AeteElementIndicator	= FOUR_CHAR_CODE('EIDC');
const PaneIDT   item_AeteKeyFormSlider		= FOUR_CHAR_CODE('KSLI');
const PaneIDT   item_AeteKeyFormIndicator	= FOUR_CHAR_CODE('KIDC');
//    CompOps panel
const PaneIDT   item_AeteCompName			= 1;
const PaneIDT   item_AeteCompID				= 2;
const PaneIDT   item_AeteCompDescr			= 3;
// const PaneIDT   item_AeteCompOpBox			= FOUR_CHAR_CODE('CMPO');
//    Enums panel
const PaneIDT   item_AeteEnumerationID		= 1;
const PaneIDT   item_AeteEnumName			= 2;
const PaneIDT   item_AeteEnumType			= 3;
const PaneIDT   item_AeteEnumDescr			= 4;
const PaneIDT   item_AeteEnumBox			= FOUR_CHAR_CODE('ENUM');
const PaneIDT   item_AeteEnumSlider			= FOUR_CHAR_CODE('NSLI');
const PaneIDT   item_AeteEnumIndicator		= FOUR_CHAR_CODE('NIDC');
// MENU Editor Window
// ------------------
const PaneIDT   item_MenuEditMenuTitle		= 1;
const PaneIDT   item_MenuEditMenuID			= 2;
const PaneIDT   item_MenuEditMDEF			= 3;
const PaneIDT   item_MenuEditMenuEnabled	= 4;
const PaneIDT   item_MenuEditItemTitle		= 5;
const PaneIDT   item_MenuEditItemEnabled	= 6;
const PaneIDT   item_MenuEditIconID			= 7;
const PaneIDT   item_MenuEditShortcut		= 8;
const PaneIDT   item_MenuEditMarkChar		= 9;
const PaneIDT   item_MenuEditPropertyPopup	= 40;
const PaneIDT   item_MenuEditStylePopup		= 41;
const PaneIDT   item_MenuEditCmdModifier	= 20;
const PaneIDT   item_MenuEditShiftModifier	= 21;
const PaneIDT   item_MenuEditOptModifier	= 22;
const PaneIDT   item_MenuEditCtrlModifier	= 23;
const PaneIDT   item_MenuEditEncoding		= 30;
const PaneIDT   item_MenuEditRefcon1		= 31;
const PaneIDT   item_MenuEditRefcon2		= 32;
const PaneIDT   item_MenuEditFontID			= 33;
const PaneIDT   item_MenuEditGlyphField		= 34;
const PaneIDT   item_MenuEditGlyphBox		= 35;
const PaneIDT   item_MenuEditItemGroupVIew	= 50;
// Resource Picker Window
// ----------------------
const PaneIDT   item_PickerResourceCount	= 1;


// Common elements for Editor Windows
// ----------------------------------
const PaneIDT	item_EditorHeader			= FOUR_CHAR_CODE('Head');
const PaneIDT	item_EditorFooter			= FOUR_CHAR_CODE('Foot');
const PaneIDT   item_EditorContents			= FOUR_CHAR_CODE('Cnts');
const PaneIDT   item_EditorScroller			= FOUR_CHAR_CODE('Scrl');
const PaneIDT   item_EditorSave				= FOUR_CHAR_CODE('Vlid');
const PaneIDT   item_EditorCancel			= FOUR_CHAR_CODE('Cncl');
const PaneIDT   item_EditorRevert			= FOUR_CHAR_CODE('Rvrt');
const PaneIDT	item_NameStaticText			= FOUR_CHAR_CODE('Name');
const PaneIDT	item_ReadOnlyIcon			= FOUR_CHAR_CODE('Lock');
const PaneIDT	item_PlusButton				= FOUR_CHAR_CODE('Plus');
const PaneIDT	item_MinusButton			= FOUR_CHAR_CODE('Mins');
const PaneIDT   item_TabGroup				= FOUR_CHAR_CODE('TabG');

// Misc dialog elements
// --------------------
const PaneIDT	item_ValueField				= FOUR_CHAR_CODE('VALU');
const PaneIDT	item_PromptField			= FOUR_CHAR_CODE('PROM');
const PaneIDT	item_SizeField				= FOUR_CHAR_CODE('SIZE');
const PaneIDT	item_WidthField				= FOUR_CHAR_CODE('WIDT');
const PaneIDT	item_HeightField			= FOUR_CHAR_CODE('HEIG');



// Navigation dialogs custom items
// -------------------------------
enum {
	DITLitm_NewMapRF	= 1,
	DITLitm_NewMapDF	= 2
};

enum {
	DITLitm_OpenMapAny	= 1,
	DITLitm_OpenMapRF	= 2,
	DITLitm_OpenMapDF	= 3,
	DITLitm_OpenMapRO	= 4
};

enum {
	DITLitm_SaveMapSame	= 1,
	DITLitm_SaveMapRF	= 2,
	DITLitm_SaveMapDF	= 3
};


// ======================================================================
// Message IDs
// ======================================================================
// Inspector Window
// ----------------
const MessageT	msg_InspEditID			= PPob_InspectorWindow + item_InspEditID;
const MessageT	msg_InspEditName		= PPob_InspectorWindow + item_InspEditName;
const MessageT	msg_InspSysHeap			= PPob_InspectorWindow + item_InspSysHeap;
const MessageT	msg_InspPurgeable		= PPob_InspectorWindow + item_InspPurgeable;
const MessageT	msg_InspLocked			= PPob_InspectorWindow + item_InspLocked;
const MessageT	msg_InspProtected		= PPob_InspectorWindow + item_InspProtected;
const MessageT	msg_InspPreload			= PPob_InspectorWindow + item_InspPreload;
const MessageT	msg_InspRevert			= PPob_InspectorWindow + item_InspRevert;
const MessageT	msg_InspModify			= PPob_InspectorWindow + item_InspModify;
// New Resource Window
// -------------------
const MessageT	msg_NewType				= PPob_NewRezDialog + item_NewType;
const MessageT	msg_NewID				= PPob_NewRezDialog + item_NewID;
const MessageT	msg_NewName				= PPob_NewRezDialog + item_NewName;
const MessageT	msg_NewSysHeap			= PPob_NewRezDialog + item_NewSysHeap;
const MessageT	msg_NewPurgeable		= PPob_NewRezDialog + item_NewPurgeable;
const MessageT	msg_NewLocked			= PPob_NewRezDialog + item_NewLocked;
const MessageT	msg_NewProtected		= PPob_NewRezDialog + item_NewProtected;
const MessageT	msg_NewPreload			= PPob_NewRezDialog + item_NewPreload;
const MessageT	msg_NewUniqueID			= PPob_NewRezDialog + item_NewUniqueID;
// Hex Edit Window
// ---------------
const MessageT	msg_HexLineEdit			= PPob_HexEditorWindow + item_HexLineEdit;
const MessageT	msg_HexOffsetEdit		= PPob_HexEditorWindow + item_HexOffsetEdit;
// About box
// ---------
const MessageT	msg_AboutOkButton		= item_AboutOkButton;		// 'ok  '
const MessageT	msg_AboutLicenceButton	= item_AboutLicenceButton;	// 'Lcnc'
// Find Dialog
// -----------
const MessageT	msg_FindSearchField		= PPob_FindDialog + item_FindSearchField;
const MessageT	msg_FindInHexRadio		= PPob_FindDialog + item_FindInHexRadio;
const MessageT	msg_FindInTxtRadio		= PPob_FindDialog + item_FindInTxtRadio;
const MessageT	msg_FindIgnoreCase		= PPob_FindDialog + item_FindIgnoreCase;
const MessageT	msg_FindRegexp			= PPob_FindDialog + item_FindRegexp;
// Rez Compare Dialog
// ------------------
const MessageT	msg_RezCompSetOld		= PPob_RezCompDialog + item_RezCompSetOld;
const MessageT	msg_RezCompSetNew		= PPob_RezCompDialog + item_RezCompSetNew;
const MessageT	msg_RezCompIgnoreNames	= PPob_RezCompDialog + item_RezCompIgnoreNames;
const MessageT	msg_RezCompIgnoreAttrs	= PPob_RezCompDialog + item_RezCompIgnoreAttrs;
const MessageT	msg_RezCompIgnoreData	= PPob_RezCompDialog + item_RezCompIgnoreData;
// Rez Compare Results Window
// --------------------------
const MessageT	msg_CompResultScroller		= PPob_RezCompWindow + item_CompResultScroller;
const MessageT	msg_CompResultHexRadio		= PPob_RezCompWindow + item_CompResultHexRadio;
const MessageT	msg_CompResultTxtRadio		= PPob_RezCompWindow + item_CompResultTxtRadio;
const MessageT	msg_CompResultOnlyOldTbl	= PPob_RezCompWindow + item_CompResultOnlyOldTbl;
const MessageT	msg_CompResultDifferingTbl	= PPob_RezCompWindow + item_CompResultDifferingTbl;
const MessageT	msg_CompResultOnlyNewTbl	= PPob_RezCompWindow + item_CompResultOnlyNewTbl;
// Ask Unique ID dialog
// --------------------
const MessageT	msg_UidOtherConflicts		= PPob_AskUniqueID + item_UidOtherConflicts;
// Resource Type Chooser
// ---------------------
const MessageT	msg_TypeChooserField		= PPob_RezTypeChooser + item_TypeChooserField;
const MessageT	msg_TypeChooserMenu			= PPob_RezTypeChooser + item_TypeChooserMenu;
// Template Option Chooser
// -----------------------
const MessageT	msg_TmplKeyChooserMenu		= PPob_TmplKeyChooser + item_TmplKeyChooserMenu;

// Preferences
// -----------
const MessageT  msg_PrefsRevert				= PPob_PrefsWindow + 3;
//     General Prefs Pane
//     ------------------
const MessageT  msg_GenPrefsMaxRecent       = PPob_PrefsGeneralPane + item_GenPrefsMaxRecent;
const MessageT	msg_GenPrefsResetRecent		= PPob_PrefsGeneralPane + item_GenPrefsResetRecent;
const MessageT	msg_GenPrefsDataFork		= PPob_PrefsGeneralPane + item_GenPrefsDataFork;
const MessageT	msg_GenPrefsResourceFork	= PPob_PrefsGeneralPane + item_GenPrefsResourceFork;
//     Export Prefs Pane
//     -----------------
const MessageT	msg_ExpPrefsKeyDtd			= PPob_PrefsExportPane + item_ExpPrefsKeyDtd;
const MessageT	msg_ExpPrefsAttrDtd			= PPob_PrefsExportPane + item_ExpPrefsAttrDtd;
const MessageT	msg_ExpPrefsInclBinData		= PPob_PrefsExportPane + item_ExpPrefsInclBinData;
const MessageT	msg_ExpPrefsHexEnc			= PPob_PrefsExportPane + item_ExpPrefsHexEnc;
const MessageT	msg_ExpPrefsBase64Enc		= PPob_PrefsExportPane + item_ExpPrefsBase64Enc;
const MessageT	msg_ExpPrefsEditSig			= PPob_PrefsExportPane + item_ExpPrefsEditSig;
//     Compare Prefs Pane
//     ------------------
const MessageT	msg_CompPrefsIgnName		= PPob_PrefsComparePane + item_CompPrefsIgnName;
const MessageT	msg_CompPrefsIgnAttr		= PPob_PrefsComparePane + item_CompPrefsIgnAttr;
const MessageT	msg_CompPrefsIgnData		= PPob_PrefsComparePane + item_CompPrefsIgnData;
const MessageT	msg_CompPrefsHexDisplay		= PPob_PrefsComparePane + item_CompPrefsHexDisplay;
const MessageT	msg_CompPrefsTxtDisplay		= PPob_PrefsComparePane + item_CompPrefsTxtDisplay;
//     Interface Prefs Pane
//     --------------------
const MessageT	msg_UIPrefsFontsMenu		= PPob_PrefsInterfacePane + item_UIPrefsFontsMenu;
const MessageT	msg_UIPrefsSizeMenu			= PPob_PrefsInterfacePane + item_UIPrefsSizeMenu;
//     Templates Prefs Pane
//     --------------------
const MessageT	msg_TmplPrefsHexSym0x		= PPob_PrefsTemplatesPane + item_TmplPrefsHexSym0x;
const MessageT	msg_TmplPrefsHexSymDollar	= PPob_PrefsTemplatesPane + item_TmplPrefsHexSymDollar;
const MessageT	msg_TmplPrefsHexLowercase	= PPob_PrefsTemplatesPane + item_TmplPrefsHexLowercase;
const MessageT	msg_TmplPrefsHexUppercase	= PPob_PrefsTemplatesPane + item_TmplPrefsHexUppercase;
const MessageT	msg_TmplPrefsDisplayFillers	= PPob_PrefsTemplatesPane + item_TmplPrefsDisplayFillers;
const MessageT	msg_TmplPrefsEnableFillers	= PPob_PrefsTemplatesPane + item_TmplPrefsEnableFillers;
//     Editors Prefs Pane
//     ------------------
const MessageT	msg_EditPrefsUse8BitPicts	= PPob_PrefsEditorsPane + item_EditPrefsUse8BitPicts;
const MessageT	msg_EditPrefsUseFullTables	= PPob_PrefsEditorsPane + item_EditPrefsUseFullTables;
const MessageT	msg_EditPrefsDoFontSubst	= PPob_PrefsEditorsPane + item_EditPrefsDoFontSubst;
//     Misc Prefs Pane
//     ---------------
const MessageT	msg_MiscPrefsSetSigOnClose	= PPob_PrefsMiscPane + item_MiscPrefsSetSigOnClose;
const MessageT	msg_MiscPrefsClosingType	= PPob_PrefsMiscPane + item_MiscPrefsClosingType;
const MessageT	msg_MiscPrefsClosingCreator	= PPob_PrefsMiscPane + item_MiscPrefsClosingCreator;
const MessageT	msg_MiscPrefsSetSigOnCreate	= PPob_PrefsMiscPane + item_MiscPrefsSetSigOnCreate;
const MessageT	msg_MiscPrefsOnlyRsrcExt	= PPob_PrefsMiscPane + item_MiscPrefsOnlyRsrcExt;
// Tmpl Editor Window
// ------------------
const MessageT	msg_EditorSave				= msg_OK;
const MessageT	msg_EditorCancel			= msg_Cancel;
const MessageT	msg_EditorRevert			= cmd_Revert;
// Text Editor Window
// ------------------
const MessageT	msg_TextEditWrap			= PPob_TextEditorWindow + item_TextEditWrap;
// Text Editor Window
// ------------------
const MessageT	msg_UtxtEditFontMenu		= PPob_UtxtEditorWindow + item_UtxtEditFontMenu;
const MessageT	msg_UtxtEditSizeMenu		= PPob_UtxtEditorWindow + item_UtxtEditSizeMenu;
const MessageT	msg_UtxtEditStyleMenu		= PPob_UtxtEditorWindow + item_UtxtEditStyleMenu;
// Icon Editor Window
// ------------------
const MessageT	msg_TextActionDied			= FOUR_CHAR_CODE('TxDi');
const MessageT	msg_IconEditPattern			= tool_Pattern;
const MessageT	msg_IconEditForeColor		= tool_ForeColor;
const MessageT	msg_IconEditBackColor		= tool_BackColor;		
const MessageT	msg_IconShowAsRgbx			= PPob_IconEditorWindow + item_IconShowAsRgbx;
const MessageT	msg_IconShowAsBitmap		= PPob_IconEditorWindow + item_IconShowAsBitmap;
const MessageT	msg_IconShowAsMask			= PPob_IconEditorWindow + item_IconShowAsMask;
// // Aete Editor Window
// // ------------------
const MessageT    msg_AeteSuiteName			= PPob_AeteEditorWindow + item_AeteSuiteName;
//   All the other edit fields broadcast a msg_EditorModifiedItem message
// Events panel
const MessageT    msg_AeteDirectOptions			= PPob_AeteEventPane + item_AeteDirectOptions;
const MessageT    msg_AeteReplyOptions			= PPob_AeteEventPane + item_AeteReplyOptions;
const MessageT    msg_AeteParamOptions			= PPob_AeteEventPane + item_AeteParamOptions;
// Classes panel
const MessageT    msg_AetePropertyOptions		= PPob_AeteClassPane + item_AetePropertyOptions;
// MENU Editor Window
// ------------------
const MessageT    msg_MenuEditMenuTitle		= PPob_MenuEditorWindow + item_MenuEditMenuTitle;
const MessageT    msg_MenuEditMenuID		= PPob_MenuEditorWindow + item_MenuEditMenuID;
const MessageT    msg_MenuEditMDEF			= PPob_MenuEditorWindow + item_MenuEditMDEF;
const MessageT    msg_MenuEditMenuEnabled	= PPob_MenuEditorWindow + item_MenuEditMenuEnabled;
const MessageT    msg_MenuEditItemTitle		= PPob_MenuEditorWindow + item_MenuEditItemTitle;
const MessageT    msg_MenuEditItemEnabled	= PPob_MenuEditorWindow + item_MenuEditItemEnabled;
const MessageT    msg_MenuEditIconID		= PPob_MenuEditorWindow + item_MenuEditIconID;
const MessageT    msg_MenuEditShortcut		= PPob_MenuEditorWindow + item_MenuEditShortcut;
const MessageT    msg_MenuEditMarkChar		= PPob_MenuEditorWindow + item_MenuEditMarkChar;
const MessageT    msg_MenuEditStylePopup	= PPob_MenuEditorWindow + item_MenuEditStylePopup;
const MessageT    msg_MenuEditPropertyPopup	= PPob_MenuEditorWindow + item_MenuEditPropertyPopup;
const MessageT    msg_MenuEditCmdModifier	= PPob_MenuEditorWindow + item_MenuEditCmdModifier;
const MessageT    msg_MenuEditShiftModifier	= PPob_MenuEditorWindow + item_MenuEditShiftModifier;
const MessageT    msg_MenuEditOptModifier	= PPob_MenuEditorWindow + item_MenuEditOptModifier;
const MessageT    msg_MenuEditCtrlModifier	= PPob_MenuEditorWindow + item_MenuEditCtrlModifier;
const MessageT    msg_MenuEditEncoding		= PPob_MenuEditorWindow + item_MenuEditEncoding;
const MessageT    msg_MenuEditRefcon1		= PPob_MenuEditorWindow + item_MenuEditRefcon1;
const MessageT    msg_MenuEditRefcon2		= PPob_MenuEditorWindow + item_MenuEditRefcon2;
const MessageT    msg_MenuEditFontID		= PPob_MenuEditorWindow + item_MenuEditFontID;
const MessageT    msg_MenuEditGlyphField	= PPob_MenuEditorWindow + item_MenuEditGlyphField;
const MessageT    msg_MenuEditGlyphPopup	= FOUR_CHAR_CODE('Glyf');
const MessageT    msg_MenuEditScriptPopup	= FOUR_CHAR_CODE('Scrp');
const MessageT    msg_MenuTableClicked		= FOUR_CHAR_CODE('TClc');
// Resource Picker Window
// ----------------------
const MessageT    msg_RezChangedForType		= FOUR_CHAR_CODE('RChT');

// Other general purpose messages
// ------------------------------
const MessageT	msg_Close						= FOUR_CHAR_CODE('Clos');
const MessageT	msg_StylePrefsChanged			= FOUR_CHAR_CODE('StPC');
const MessageT	msg_HexScroller					= FOUR_CHAR_CODE('HScr');
const MessageT	msg_DualViewEdited				= FOUR_CHAR_CODE('DuEd');
const MessageT	msg_EditorModifiedItem			= FOUR_CHAR_CODE('EdMd');
const MessageT	msg_MinusButton					= FOUR_CHAR_CODE('Mins');
const MessageT	msg_PlusButton					= FOUR_CHAR_CODE('Plus');
const MessageT	msg_TmplCasePopup				= FOUR_CHAR_CODE('Case');
const MessageT	msg_PopupEditField				= FOUR_CHAR_CODE('PopF');
const MessageT	msg_DragMoveAction				= FOUR_CHAR_CODE('DMov');
const MessageT	msg_DragCopyAction				= FOUR_CHAR_CODE('DCpy');
// Icon editor
const MessageT	msg_TargetViewClicked			= FOUR_CHAR_CODE('Tclk');
const MessageT	msg_ImageDroppedOnTargetView	= FOUR_CHAR_CODE('IDrp');
const MessageT	msg_DoubleClick					= FOUR_CHAR_CODE('DClk'); 
const MessageT	msg_GetLastCommand				= FOUR_CHAR_CODE('LCMD');
const MessageT	msg_IconSuiteSlider				= FOUR_CHAR_CODE('SLID');
// Menu editor
const MessageT	msg_MenuTitleModified			= FOUR_CHAR_CODE('MTMD');


// ======================================================================
// AE Constants
// ======================================================================
// AE suites
enum
{
	kAERzilClass			=    FOUR_CHAR_CODE('Rzil'),
	kAERsrcClass			=    FOUR_CHAR_CODE('Rsrc')
};

// Various AE parameters
enum
{
	kAERzilReply	 		=  FOUR_CHAR_CODE('Repl'),
	kAERzilFilesList	 	=  FOUR_CHAR_CODE('LFil'),
	kAERzilFromFork			=  FOUR_CHAR_CODE('From'),
	kAERzilCreateFork		=  FOUR_CHAR_CODE('Crea'),
	kAERzilCompareWith	 	=  FOUR_CHAR_CODE('AndF'),
	kAERzilLike			 	=  FOUR_CHAR_CODE('Like'),
	kAERzilFormat			=  FOUR_CHAR_CODE('Frmt')
};

/* AE Dispatch Table constants (aedt) */
const long	aeRzil_Edit				= 5000;
const long	aeRzil_Compare			= 5001;
const long	aeRzil_Inspect			= 5002;
const long	aeRzil_Export			= 5003;


// Rezilla Object Model (rzom):
// ----------------------------
const DescType rzom_cRezMapDoc		= 'MapD';	// RezMap document
const DescType rzom_cEditorDoc		= 'EdiD';	// Editor document
const DescType rzom_cPickerDoc		= 'PikD';	// Editor document
const DescType rzom_cGuiEditDoc		= 'GuiD';	// Gui editor document
const DescType rzom_cPlugEditDoc	= 'PluD';	// Plugin editor document
const DescType rzom_cTmplEditDoc	= 'TmpD';	// Tmpl editor document
const DescType rzom_cHexEditDoc		= 'HexD';	// Hex editor document

const DescType rzom_cRezMapWindow	= 'MapW';	// RezMap window
const DescType rzom_cEditorWindow	= 'EdiW';	// Editor window
const DescType rzom_cPickerWindow	= 'PikW';	// Editor window
const DescType rzom_cPluginWindow	= 'PluW';	// Plugin window
const DescType rzom_cGuiWindow		= 'GuiW';	// Interface editor window
const DescType rzom_cTmplWindow		= 'TmpW';	// Tmpl editor window
const DescType rzom_cHexWindow		= 'HexW';	// Hex editor window

const DescType rzom_cCompWindow		= 'CmpW';	// RezCompare window
const DescType rzom_cInspWindow		= 'InsW';	// Inspector window

const DescType rzom_cDataPane		= 'DatP';	// Any data pane
const DescType rzom_cHexPane		= 'HexP';	// Hexadecimal pane
const DescType rzom_cTxtPane		= 'TxtP';	// Text pane

const DescType rzom_cRezMap			= 'cMAP';	// RezMap
const DescType rzom_cRezType		= 'cTYP';	// RezType
const DescType rzom_cRezObj			= 'cRSC';	// RezObj
const DescType rzom_cMapsComp		= 'Mcmp';	// Maps comparison object

// Properties
// ----------
//    Application
const DescType rzom_pVersion		= pVersion;		// Version ('vers')	
const DescType rzom_pClipboard		= pClipboard;	// PrivateClipboard ('pcli')
const DescType rzom_pPreferences	= 'pPRF';		// Preferences
const DescType rzom_pInspector		= 'pINS';		// Inspector

//    Document
const DescType rzom_pOwnerMapDoc	= 'pOWM';	// Editor document's owner map

//    RezMap document
const DescType rzom_pRezFork		= 'pFRK';	// ResFork
// const DescType rzom_pRezMap			= 'pMAP';	// RezMap
const DescType rzom_pRezFile		= 'pFIL';	// ResFile
const DescType rzom_pEditedRsrcDocs	= 'pERD';	// Edited resource documents
const DescType rzom_pExportFormat	= 'pFRM';	// Export format

//    RezMap
const DescType rzom_pRefNum			= 'pRFN';		// RefNum
const DescType rzom_pTypesList		= 'pTYL';		// List of all types
const DescType rzom_pAttributes		= 'pATR';		// Attributes
const DescType rzom_pReadOnly		= 'pRDO';		// mapReadOnly
const DescType rzom_pCompact		= 'pCPT';		// mapCompact
const DescType rzom_pChanged		= pIsModified;	// mapChanged/resChanged ('imod')

//    RezType
const DescType rzom_pIDsList		= 'pIDL';		// List of all IDs

//    Resource
const DescType rzom_pResID			= pID;			// ID ('ID  ')			 
const DescType rzom_pName			= pName;		// Name ('pnam')
const DescType rzom_pType			= 'pTYP';		// Type
const DescType rzom_pSpecifier		= 'pSPE';		// Specifier {type,ID}
const DescType rzom_pSysHeap		= 'pSHP';		// resSysHeap
const DescType rzom_pPurgeable		= 'pPUR';		// resPurgeable
const DescType rzom_pLocked			= 'pLOC';		// resLocked
const DescType rzom_pProtected		= 'pPRO';		// resProtected
const DescType rzom_pPreload		= 'pPRE';		// resPreload
const DescType rzom_pDataSize		= 'pSIZ';		// Size of the data
const DescType rzom_pSizeOnDisk		= 'pDSZ';		// Size on disk
const DescType rzom_pData			= 'pDAT';		// Data

//    Resource specifier
const DescType rzom_cRezTypeID		= 'TyId';		// Resource specifier object: 
                           			         		//   e-g {"aete", 128}
//    Maps Comparison
const DescType rzom_pCompCriteria		= 'pCRI';	// Comparison criteria
const DescType rzom_pIgnoreName			= 'IgnN';	// IgnoreNameDiff
const DescType rzom_pIgnoreAttrs		= 'IgnA';	// IgnoreAttrsDiff
const DescType rzom_pIgnoreData			= 'IgnD';	// IgnoreDataDiff
const DescType rzom_pOnlyInOld			= 'OldR';	// Only in old map resources (list)
const DescType rzom_pOnlyInNew			= 'NewR';	// Only in new map resources (list)
const DescType rzom_pDiffering			= 'Diff';	// In both but different (list)
const DescType rzom_pIdentical			= 'Iden';	// In both and identical (list)

//    RezMap window
const DescType rzom_pTypesCount			= 'Tcnt';	// Total types count
const DescType rzom_pResCount			= 'Rcnt';	// Total resources count

//    Editor document
const DescType rzom_pKind				= 'pKND';	// Kind

//    Tmpl editor document
// const DescType rzom_pTemplate		= 'pTMP';	// Template

//    Hexadecimal window
const DescType rzom_pHexWinMaxPos			= 'maxP';	// Index of last position
const DescType rzom_pHexWinStartPos			= 'iniP';	// Position of beginning of selection
const DescType rzom_pHexWinEndPos			= 'endP';	// Position of end of selection
const DescType rzom_pHexWinHexSelection		= 'hSel';	// Contents of selection in hex pane
const DescType rzom_pHexWinTxtSelection		= 'tSel';	// Contents of selection in text pane

//    Inspector window
const DescType rzom_pCurrResource	= 'pRSC';	// Resource for which info is displayed
const DescType rzom_pNameField		= 'pNAF';	// The 'name' field
const DescType rzom_pIDField		= 'pIDF';	// The 'ID' field

// Aete Enumerator IDs
const DescType rzom_eEditorKind		= 'EKND';
const DescType rzom_eExportFormat	= 'EXPF';

const DescType rzom_eRezMap			= 'RMAP';
const DescType rzom_eEditorDoc		= 'EDOC';
const DescType rzom_eCompareDoc		= 'COMP';

const DescType rzom_eHexEditor		= 'EHEX';
const DescType rzom_eTmplEditor		= 'ETMP';
const DescType rzom_eGuiEditor		= 'EGUI';

const DescType rzom_eHexaData		= 'HEXA';
const DescType rzom_eAsciiData		= 'ASCI';

// For "open" and "save as" commands
const DescType rzom_eWhichFork		= 'FORK';
const DescType rzom_eDataFork		= 'DATF';
const DescType rzom_eRsrcFork		= 'RSRF';
const DescType rzom_eAnyFork		= 'ANYF';
const DescType rzom_eSameFork		= 'SAMF';

// For 'pFRK' property
const DescType rzom_eForkKind		= 'FKND';
const DescType rzom_eIsDataFork		= 'DFRK';
const DescType rzom_eIsRsrcFork		= 'RFRK';
const DescType rzom_eIsUnknownFork	= 'UFRK';

const DescType rzom_eExportUnknown	= 'UEXP';
const DescType rzom_eExportXml		= 'XML ';
const DescType rzom_eExportText		= 'TEXT';
const DescType rzom_eExportHtml		= 'HTML';
const DescType rzom_eExportDerez	= 'DREZ';


// ======================================================================
// Error Constants
// ======================================================================
enum RezillaErrors
{
	err_RezillaErrorStart			= 1000,
	err_NoRezInDataFork				= 1001,
	err_NoRezInRezFork,
	err_NoRezInAnyFork,
	err_NoOpenPermission,
	err_OpenForkError,
	err_OpenSucceededReadOnly,
	err_OpenDocsAEFailed,
	err_UnderVersionControlSystem,
	err_ExceptionParsingTemplate,
	err_NoResourceForType,
	err_NoResourceWithName,
	err_AlreadyExistingID,
	err_MoreDataThanExpected,
	err_InvalidHexadecimalData,
	err_CreateForkForFileFailed,
	err_ImportGenericError			= 1900,
	err_ImportInvalidOSType,
	err_ImportCantGetXmlData,
	err_ImportCantBuildTree,
	err_ImportCantGetTopAeteNode,
	err_ImportUnknownAeteResourceTag,
	err_ImportUnknownAeteSuiteTag,
	err_ImportUnknownAeteEventTag,
	err_ImportUnknownAeteParameterTag,
	err_ImportUnknownAeteClassTag,
	err_ImportUnknownAetePropertyTag,
	err_ImportUnknownAeteElementTag,
	err_ImportUnknownAeteCompOpTag,
	err_ImportUnknownAeteEnumerationTag,
	err_ImportUnknownAeteEnumeratorTag,
	err_ImportUnknownFlagsTag,
	err_TmplTemplateError			= 2000,
	err_TmplGetDataStreamFailed,
	err_TmplUnrecognizedTag,
	err_TmplParsingAborted,
	err_TmplValueTooLargeInBitsField,
	err_TmplTextOverflow,
	err_TmplWrongFixedCount,
	err_TmplZeroListNotTerminated,
	err_TmplZeroListEndingWithNonNull,
	err_TmplListCountTooBig,
	err_TmplExpectedEvenLengthString,
	err_TmplUnexpectedTag,
	err_TmplMalformedHexValue,
	err_TmplMalformedDateValue,
	err_TmplCantGetDateFormat,
	err_TmplParseDateFailed,
	err_TmplNotExpectedSize,
	err_TmplCreateEmptyNewAborted,
	err_TmplNoCaseInKeySection,
	err_TmplMalformedCaseSection,
	err_TmplUnknownKeyValueInResource,
	err_TmplIsolatedCaseTag,
	err_TmplCantFindKeyedSectionStart,
	err_TmplCantFindKeyStartForValue,
	err_TmplCantFindKeyIndex,
	err_TmplCantFindKeyValue,
	err_TmplCantFindKeyPosition,
	err_TmplUnsupportedResourceId,
	err_TmplCantFindMatchingKeyEnd,
	err_IconGeneric					= 3000,	
	err_IconInvalidImageDepth,
	err_IconInvalidImageFormat,
	err_IconInvalidImageSize,
	err_IconCorruptedResource,
	err_IconCorruptedFile,
	err_IconUnknownDataType,
	err_IconAssertionProxy,
	err_IconNilPointerProxy,
	err_IconOutOfMemory,
	err_IconResourceNotFound,
	err_IconDiskFull,
	err_IconFileNotFound,
	err_IconIOError,
	err_IconResizeFormatString,  // not used. Can be reaffected.
	err_IconFileLocked,
	err_IconBadFontSize,
	err_IconNoPictOnClipboard,
	err_PluginGeneric				= 4000,	
	err_PluginLoadFailed,
	err_PluginGetInfoFailed,
 	err_RezillaErrorEnd
};

// NB: plugin errors are defined in "RezillaPluginInterface.h". They start 
// at plugErr_Generic = 5000.


// ======================================================================
// Misc Constants
// ======================================================================
// Signatures
const UInt32	kTextEditSig		= FOUR_CHAR_CODE('ttxt');
const UInt32	kSystemEventsSig	= FOUR_CHAR_CODE('sevs');
const UInt32	kRezillaSig			= FOUR_CHAR_CODE('Rzil');
const UInt32	kRezFileType		= FOUR_CHAR_CODE('rsrc');
// Rezilla's own type for Clipboard data
#define	 kRezillaClipType		'Rzil'
// File extension separator
#define  kFileExtSeparator		(char)'.'
// Preferences identifier
#define  kRezillaIdentifier		"net.sourceforge.rezilla"
// Color to frame drop region 
#define  kRzilDragHiliteColor	{ 0xFFFF, 0x0000, 0xFFFF }
// Pen size to frame drop region 
#define  kRzilDragHiliteSize	1
// Width of the three tables in the comparison results window
#define  kCompTableWidth	183
// Height of a row in these tables
#define  kCompTableHeight	14
// Height of a line in a WE view in case of null value
#define  kRzilDefaultLineHeight	11

// Color used to draw frames around selected items
const RGBColor	Color_Red = {0xFFFF, 0x0000, 0x0000};

// Drag and drop
const UInt32	DragFlavor_Rezilla		= FOUR_CHAR_CODE('Rzil');  // kRzilDragFlavor
const UInt32	DragFlavor_Offscreen	= FOUR_CHAR_CODE('OfSc');

// Constants for the Rezmap tables
const SInt16	kRzilColWidth		= 100;

// ======================================================================
// Constants for the Hexadecimal editor
// ======================================================================
// Used in HexEdit windows to recalculate the edit panes. It is the extra 
// size of the TextGroupBox around the panes.
const SInt16	kRzilHexEditExtraWidth		= 46;
const SInt16	kRzilHexEditExtraHeight		= 11;
const SInt16	kRzilHexEditLeftRidge		= 6;
const SInt16	kRzilHexEditTopRidge		= 5;

// Constants for the Rez Compare results window
// Used in ResCompare windows to recalculate the edit panes. It is the extra 
// size of the TextGroupBox around the panes.
const SInt16	kRzilResCompExtraWidth = 29;
const SInt16	kRzilResCompExtraHeight = 6;

// Max number of items in the Recent Items menu
const SInt16	kRzilMaxRecentItems	= 10;

// Used in NavServicesCallbacks
const ResType	ResType_DITL = FOUR_CHAR_CODE('DITL');

// Used by size popup menu in Interface preferences
#define  kFirstSizeMenuItem	1
#define  kLastSizeMenuItem	9


// ======================================================================
// Helpful Macros
// ======================================================================
#ifndef MIN
	#define MIN(a,b) ( (a)<(b) ? a : b )
#endif

#ifndef MAX
	#define MAX(a,b) ( (a)<(b) ? b : a )
#endif

#ifndef ABS
	#define ABS(x)   ( (x) < 0 ?  -(x) : x )
#endif


// ======================================================================
// Constants for the Template Editor
// ======================================================================
const SInt16	kTmplLeftMargin			= 15;
const SInt16	kTmplListIndent			= 15;
const SInt16	kTmplVertSkip			= 4;
const SInt16	kTmplVertSep			= 8;
const SInt16	kTmplDividerSep			= 2;
const SInt16	kTmplHorizSep			= 10;
const SInt16	kTmplHorizSkip			= 4;
const SInt16	kTmplBevelHeight		= 18;
const SInt16	kTmplBevelWidth			= 12;
const SInt16	kTmplBevelSep			= 4;
const SInt16	kTmplPopupWidth			= 120;
const SInt16	kTmplPopupHeight		= 20;
const SInt16	kTmplCheckHeight		= 18;
const SInt16	kTmplCheckWidth			= 18;
const SInt16	kTmplEditHeight			= 22;
const SInt16	kTmplEditWidth			= 250;
const SInt16	kTmplEditMinFixedChars	= 4;
const SInt16	kTmplEditMaxFixedChars	= 16;
const SInt16	kTmplEditUnitWidth		= 8;
const SInt16	kTmplPopupFieldWidth	= 75;
const SInt16	kTmplHexPaneWidth		= 288;
const SInt16	kTmplLabelHeight		= 26;
const SInt16	kTmplLabelVertSkip		= 17;
const SInt16	kTmplLabelWidth			= 150;
const SInt16	kTmplLabelInterline		= -5;
const SInt16	kTmplListHeaderHeight	= 18;
const SInt16	kTmplListHeaderWidth	= 250;
const SInt16	kTmplRadioHeight		= 16;
const SInt16	kTmplRadioWidth			= 50;
const SInt16	kTmplRectHeight			= 16;
const SInt16	kTmplRectVertSkip		= 22;
const SInt16	kTmplRectWidth			= 60;
const SInt16	kTmplRgvHeight			= 22;
const SInt16	kTmplRgvWidth			= 150;
const SInt16	kTmplScrollWidth		= 16;
const SInt16	kTmplTextMaxHeight		= 198;
const SInt16	kTmplTextMinHeight		= 55;
const SInt16	kTmplTextHeadHeight		= 5;
const SInt16	kTmplTextFootHeight		= 6;
const SInt16	kTmplTextInset			= 4;
const SInt16	kTmplTextMargin			= 20;
const SInt16	kTmplTxtPaneLeft		= 294;
const SInt16	kTmplTxtPaneWidth		= 192;
const SInt16	kTmplPushWidth			= 27;
const SInt16	kTmplPushHeight			= 18;
const SInt16	kTmplCountWidth			= 40;
const SInt16	kTmplSeparatorHeight	= 3;
const SInt16	kTmplColorHeight		= 16;
const SInt16	kTmplColorWidth			= 24;
const SInt16	kTmplMinListItemHeight	= 16;


// ======================================================================
// Constants for the Icon editor
// ======================================================================
typedef UInt32		PixelValue;		// raw values within a bitmap/pixmap
typedef UInt32		Color32;		// RGB color in a long (0:R:G:B)
typedef UInt8 *		RawPtr;
typedef UInt8		RawByte;

const Color32		kWhiteColor32			= 0x00FFFFFF;
const Color32		kBlackColor32			= 0;
const SInt32 		kColorMargins			= 1;
const SInt32 		kFlashCount				= 5;
// These need to remain identical
const SInt32		kIconSideMargin 		= 1;
const SInt32		kIconSpaceBetween 		= 1;
const SInt32		kIconRecolorDepth		= 8;
const UInt16		kIconMinTargetWidth		= 40;
const UInt16		kIconMinTargetHeight	= 40;
const UInt16		kIconLeftHeaderWidth	= 80;
const UInt16		kIconFooterHeight		= 40;
const UInt16		kIconSampleOutMargin	= 10;
// Cursors are always the same size
const SInt32		kCursorWidth			= 16;
const SInt32		kCursorHeight			= 16;
// Black & white cursors have the following values
const SInt32		kBWCursorRowBytes		= 2;	
const SInt32		kBWCursorBytes			= 68;  // 68 = 2 bw images, 16x16, + hotspot
const SInt32		kDefaultPatternWidth	= 8;
const SInt32		kDefaultPatternHeight	= 8;
const SInt32		kDefaultIconWidth		= 16;
const SInt32		kDefaultIconHeight		= 16;
const SInt32		kBWPatternRowBytes		= 1;
const SInt32		kBWIconRowBytes			= 2;
const SInt16		kDefaultMarchInterval	= 3;
// The default pattern is black
const Pattern	Pattern_Black = { { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF } };

#define kMaxIconSamplePanes		20

// For the Icon editor's clipboard and Drag&Drop
const OSType	ResType_Region			= FOUR_CHAR_CODE('RgN ');
const OSType	ResType_ColorCursor 	= FOUR_CHAR_CODE('crsr');
const ResType	ResType_IconFamilyInfo	= FOUR_CHAR_CODE('RzII');

// Three ways to redraw
enum RedrawOptions
{
	redraw_Now,
	redraw_Later,
	redraw_Dont
};


// ======================================================================
// Constants for the Text editor
// ======================================================================
const SInt32		kMaxTextWidth		= 32768;	


// ======================================================================
// Constants for the Menu editor
// ======================================================================
const OSType	ResType_ExtendedMenu			= FOUR_CHAR_CODE('xmnu');

#define  kMenuEditLabelOffset	10


// ======================================================================
// Constants for the Plugin editor
// ======================================================================

const UInt16	kPluginHeaderHeight		= 24;
const UInt16	kPluginFooterHeight		= 40;
const UInt16	kEditLockIconSize		= 16;
const UInt16	kEditLockIconLeft		= 9;
const UInt16	kEditRevertButtonLeft	= 28;
const UInt16	kEditCancelButtonRight	= 164;
const UInt16	kEditValidButtonRight	= 86;
const UInt16	kEditButtonWidth		= 65;
const UInt16	kEditButtonHeight		= 20;
const UInt16	kEditButtonTop			= 9;
const UInt16	kEditHorizMargin		= 10;
const UInt16	kEditNameHeight			= 10;
const UInt16	kEditVertMargin			= 5;


// ======================================================================
// Constants for the resource pickers
// ======================================================================

#define kPickerDefaultStampWidth	32
#define kPickerDefaultStampHeight	44
#define kPickerViewIDFieldHeight	12
// #define kPickerViewStampMinHeight	12


