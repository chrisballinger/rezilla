// ===========================================================================
// RezillaConstants.h
// 
//                       Created : 2003-04-16 22:52:54
//             Last modification : 2005-01-01 08:05:34
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@easyconnect.fr>
// www : <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003-2005
// All rights reserved.
// $Date$
// $Revision$
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
	export_Xml = 0,
	export_Text,
	export_Html,
	export_Derez
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
	mpv_Export,
	mpv_Compare,
	mpv_Interface,
	mpv_Editor,
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
	editor_kindHex
};

// Supported image types
enum
{	
	ImgType_LargeIcon			= FOUR_CHAR_CODE('ICON'),
	
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
const ResIDT	PPob_AboutWindow			= 5000;
const ResIDT	PPob_LicenceWindow			= 5100;
const ResIDT	PPob_RezCompDialog			= 6000;
const ResIDT	PPob_RezCompWindow			= 6500;
const ResIDT	PPob_PrefsWindow			= 7000;
const ResIDT	PPob_PrefsGeneralPane		= 7100;
const ResIDT	PPob_PrefsExportPane		= 7200;
const ResIDT	PPob_PrefsComparePane		= 7300;
const ResIDT	PPob_PrefsInterfacePane		= 7400;
const ResIDT	PPob_PrefsEditorsPane		= 7500;
const ResIDT	PPob_PrefsMiscPane			= 7600;
const ResIDT	PPob_FindDialog				= 8500;
const ResIDT	PPob_FontSizeDialog			= 8600;
const ResIDT	PPob_ImageResizeDialog		= 8900;
const ResIDT	PPob_RezTypePicker			= 8700;
const ResIDT	PPob_TmplKeyPicker			= 8800;
const ResIDT	PPob_SimpleMessage			= 9500;
const ResIDT	PPob_AskIfMessage			= 9510;
const ResIDT	PPob_AskYesNoMessage		= 9520;
const ResIDT	PPob_ExplainedError			= 9530;
const ResIDT	PPob_AskUniqueID			= 9550;
const ResIDT	PPob_TmplEditorWindow		= 10100;
const ResIDT	PPob_TextEditorWindow		= 10200;
const ResIDT	PPob_AeteEditorWindow		= 10300;
const ResIDT	PPob_PictEditorWindow		= 10400;
const ResIDT	PPob_UtxtEditorWindow		= 10500;
const ResIDT	PPob_IconEditorWindow		= 10600;
const ResIDT	PPob_IconSuiteEditor		= 10600;
const ResIDT	PPob_CICNEditor				= 10601;
const ResIDT	PPob_ICONEditor				= 10602;
const ResIDT	PPob_PictEditor				= 10603;
const ResIDT	PPob_CursorEditor			= 10604;
const ResIDT	PPob_ColorCursorEditor		= 10605;
const ResIDT	PPob_PatternEditor			= 10606;
const ResIDT	PPob_PixPatEditor			= 10607;

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
const ResIDT	STRx_PaintUndo				= 7000;
const ResIDT	STRx_PaintRedo				= 7001;

// Text traits resources
const ResIDT    Txtr_GenevaNine				= 130;
const ResIDT    Txtr_GenevaTenBold          = 131;
const ResIDT	Txtr_MonacoNineDefault		= 139;
const ResIDT	Txtr_MonacoNineGray			= 133;
const ResIDT	Txtr_GenevaTen				= 140;
const ResIDT	Txtr_MonacoBlueNineCenter	= 141;
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
const ResIDT	MENU_UnicodeFonts			= 255;  
const ResIDT	MENU_StartHierMenuID		= 500;  
// Values the PP menu commands are based on
const ResIDT	base_MenuFile				= 1000;
const ResIDT	base_MenuEdit				= 1100;
const ResIDT	base_MenuResource			= 1200;

// Icon editor
const ResIDT	Txtr_PaintFont				= Txtr_GenevaNine;
const ResIDT	RidL_ToolList				= 300;
const ResIDT	MENU_IconActions			= 300;
const ResIDT	MENU_IconColors				= 301;
const ResIDT	MENU_IconStyle				= 302;
const ResIDT	MENU_IconFonts				= MENU_TextFonts;

// Icon resources
const ResIDT	ICN_WindowMenu				= 3100;
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
// Help menu commands
const CommandT	cmd_Help					= 3000;	
// Window menu commands
const CommandT	cmd_ShowInspector			= 2001;	
// Resource menu commands
const CommandT	cmd_NewRez				= base_MenuResource + 1;	
const CommandT	cmd_EditRez				= base_MenuResource + 2;	
const CommandT	cmd_TmplEditRez			= base_MenuResource + 3;	
const CommandT	cmd_HexEditRez			= base_MenuResource + 4;	
const CommandT	cmd_EditRezAsType		= base_MenuResource + 5;	
const CommandT	cmd_RemoveRez			= base_MenuResource + 10;	
const CommandT	cmd_DuplicateRez		= base_MenuResource + 11;	
const CommandT	cmd_GetRezInfo			= base_MenuResource + 15;
const CommandT	cmd_TmplEditAsRez		= base_MenuResource + 99;	
// File menu commands
const CommandT	cmd_ExportMap			= base_MenuFile + 1;	
const CommandT	cmd_RecentItems			= base_MenuFile + 2;	
// Edit menu commands
const CommandT	cmd_Find				= base_MenuEdit + 1;	
const CommandT	cmd_FindNext			= base_MenuEdit + 2;	
const CommandT	cmd_RezCompare			= base_MenuEdit + 3;	

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
const CommandT	cmd_IconPaintModified		= FOUR_CHAR_CODE('PMOD');
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
const CommandT	cmd_ColorTableApple2		= FOUR_CHAR_CODE('CLT8');  // not in the menu, but used in the code
const MessageT	msg_TextActionDied			= FOUR_CHAR_CODE('TxDi');
const CommandT	cmd_IconBaseFontSize		= 9100;		// font sizes are (cmdID - 9100)
const CommandT	cmd_IconLastFontSize		= 9300;		// and within this range
const CommandT	cmd_IconOtherFontSize		= 9100;


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
const PaneIDT	item_AboutOkButton			= 1;
const PaneIDT	item_AboutVersCaption		= 2;
const PaneIDT	item_AboutAuthorView		= 3;
const PaneIDT	item_AboutLicenceButton		= 4;
const PaneIDT	item_AboutFreeView			= 5;
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
// Resource Type Picker
// --------------------
const PaneIDT	item_TypePickerField		= 1;
const PaneIDT	item_TypePickerMenu			= 2;
// Template Key Picker
// -------------------
const PaneIDT	item_TmplKeyPickerType		= 1;
const PaneIDT	item_TmplKeyPickerMessage	= 2;
const PaneIDT	item_TmplKeyPickerLabel		= 3;
const PaneIDT	item_TmplKeyPickerMenu		= 4;

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
const PaneIDT	item_GenPrefsDataFork		= 6;
const PaneIDT	item_GenPrefsResourceFork	= 7;
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
//     Editors Prefs Pane
//     ------------------
const PaneIDT	item_EditPrefsHexSymRgbx	= 2;
const PaneIDT	item_EditPrefsHexSym0x		= 3;
const PaneIDT	item_EditPrefsHexSymDollar	= 4;
const PaneIDT	item_EditPrefsHexCaseRgbx	= 5;
const PaneIDT	item_EditPrefsHexLowercase	= 6;
const PaneIDT	item_EditPrefsHexUppercase	= 7;
const PaneIDT	item_EditPrefsDispFillers	= 8;
const PaneIDT	item_EditPrefsEnableFillers	= 9;
const PaneIDT	item_EditPrefsUse8BitPicts	= 10;
const PaneIDT	item_EditPrefsUseFullTables	= 11;
//     Misc Prefs Pane
//     ---------------
const PaneIDT	item_MiscPrefsSetSigOnClose		= 2;
const PaneIDT	item_MiscPrefsClosingType		= 3;
const PaneIDT	item_MiscPrefsClosingCreator	= 4;
const PaneIDT	item_MiscPrefsSetSigOnCreate	= 5;
const PaneIDT	item_MiscPrefsOnlyRsrcExt		= 6;
// Text Editor Window
// ------------------
const PaneIDT   item_TextEditFontMenu	= 1;
const PaneIDT   item_TextEditSizeMenu	= 2;
const PaneIDT   item_TextEditStyleMenu	= 3;
const PaneIDT   item_TextEditLength		= 4;
// Aete Editor Window
// ------------------
const PaneIDT   item_AeteSuitesPopup		= 4;
const PaneIDT   item_AeteMajorVersion		= 5;
const PaneIDT   item_AeteMinorVersion		= 6;
const PaneIDT   item_AeteLangID				= 7;
const PaneIDT   item_AeteScriptCode			= 8;
const PaneIDT   item_AeteListBoxesView		= 20;
const PaneIDT   item_AeteCategories			= 21;
const PaneIDT   item_AeteTermsScroller		= 22;
const PaneIDT   item_AeteTermsTable			= 23;
// Pict Viewer Window
// ------------------
const PaneIDT   item_PictEditSize			= 1;
const PaneIDT   item_PictEditWidth			= 2;
const PaneIDT   item_PictEditHeight			= 3;
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
const PaneIDT	tool_BlackAndWhite			= FOUR_CHAR_CODE('tBnW');
const PaneIDT	tool_Rotate					= FOUR_CHAR_CODE('tROT');
const PaneIDT	tool_SwapColors				= FOUR_CHAR_CODE('tSWP');
const PaneIDT	tool_Pattern				= FOUR_CHAR_CODE('tPAT');
const PaneIDT	tool_ForeColor				= FOUR_CHAR_CODE('tFCL');
const PaneIDT	tool_BackColor				= FOUR_CHAR_CODE('tBCL');		
const PaneIDT   item_IconCoords				= FOUR_CHAR_CODE('COOR');
const PaneIDT	item_CanvasEncloser			= FOUR_CHAR_CODE('ENCL');
const PaneIDT	item_IconSampleWell			= FOUR_CHAR_CODE('SAMP');
const PaneIDT	item_IconEditBWSample		= FOUR_CHAR_CODE('BWPT');
const PaneIDT	item_IconEditMask			= FOUR_CHAR_CODE('MASK');
const PaneIDT	item_IconShowAsRgbx			= 4;
const PaneIDT	item_IconShowAsBitmap		= 5;
const PaneIDT	item_IconShowAsMask			= 6;


// Common elements for Editor Windows
// ----------------------------------
const PaneIDT   item_EditorContents			= FOUR_CHAR_CODE('Cnts');
const PaneIDT   item_EditorScroller			= FOUR_CHAR_CODE('Scrl');
const PaneIDT   item_EditorValidate			= FOUR_CHAR_CODE('Vlid');
const PaneIDT   item_EditorCancel			= FOUR_CHAR_CODE('Cncl');
const PaneIDT   item_EditorRevert			= FOUR_CHAR_CODE('Rvrt');
const PaneIDT	item_NameStaticText			= FOUR_CHAR_CODE('Name');
const PaneIDT	item_ReadOnlyIcon			= FOUR_CHAR_CODE('Lock');

// Misc dialog elements
// --------------------
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
const MessageT	msg_AboutOkButton		= PPob_AboutWindow + item_AboutOkButton;
const MessageT	msg_AboutLicenceButton	= PPob_AboutWindow + item_AboutLicenceButton;
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
// Resource Type Picker
// --------------------
const MessageT	msg_TypePickerField			= PPob_RezTypePicker + item_TypePickerField;
const MessageT	msg_TypePickerMenu			= PPob_RezTypePicker + item_TypePickerMenu;
// Template Option Picker
// ----------------------
const MessageT	msg_TmplKeyPickerMenu		= PPob_TmplKeyPicker + item_TmplKeyPickerMenu;

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
//     Editors Prefs Pane
//     ------------------
const MessageT	msg_EditPrefsHexSym0x		= PPob_PrefsEditorsPane + item_EditPrefsHexSym0x;
const MessageT	msg_EditPrefsHexSymDollar	= PPob_PrefsEditorsPane + item_EditPrefsHexSymDollar;
const MessageT	msg_EditPrefsHexLowercase	= PPob_PrefsEditorsPane + item_EditPrefsHexLowercase;
const MessageT	msg_EditPrefsHexUppercase	= PPob_PrefsEditorsPane + item_EditPrefsHexUppercase;
const MessageT	msg_EditPrefsDispFillers	= PPob_PrefsEditorsPane + item_EditPrefsDispFillers;
const MessageT	msg_EditPrefsEnableFillers	= PPob_PrefsEditorsPane + item_EditPrefsEnableFillers;
const MessageT	msg_EditPrefsUse8BitPicts	= PPob_PrefsEditorsPane + item_EditPrefsUse8BitPicts;
const MessageT	msg_EditPrefsUseFullTables	= PPob_PrefsEditorsPane + item_EditPrefsUseFullTables;
//     Misc Prefs Pane
//     ---------------
const MessageT	msg_MiscPrefsSetSigOnClose	= PPob_PrefsMiscPane + item_MiscPrefsSetSigOnClose;
const MessageT	msg_MiscPrefsClosingType	= PPob_PrefsMiscPane + item_MiscPrefsClosingType;
const MessageT	msg_MiscPrefsClosingCreator	= PPob_PrefsMiscPane + item_MiscPrefsClosingCreator;
const MessageT	msg_MiscPrefsSetSigOnCreate	= PPob_PrefsMiscPane + item_MiscPrefsSetSigOnCreate;
const MessageT	msg_MiscPrefsOnlyRsrcExt	= PPob_PrefsMiscPane + item_MiscPrefsOnlyRsrcExt;
// Tmpl Editor Window
// ------------------
const MessageT	msg_EditorValidate			= msg_OK;
const MessageT	msg_EditorCancel			= msg_Cancel;
const MessageT	msg_EditorRevert			= cmd_Revert;
// Text Editor Window
// ------------------
const MessageT	msg_TextEditFontMenu		= PPob_TextEditorWindow + item_TextEditFontMenu;
const MessageT	msg_TextEditSizeMenu		= PPob_TextEditorWindow + item_TextEditSizeMenu;
const MessageT	msg_TextEditStyleMenu		= PPob_TextEditorWindow + item_TextEditStyleMenu;
// Aete Editor Window
// ------------------
const MessageT	msg_AeteSuitesPopup			= PPob_AeteEditorWindow + item_AeteSuitesPopup;
const MessageT	msg_AeteCategories			= PPob_AeteEditorWindow + item_AeteCategories;
const MessageT	msg_AeteTermsTable			= PPob_AeteEditorWindow + item_AeteTermsTable;
// Text Editor Window
// ------------------
const MessageT	msg_UtxtEditFontMenu		= PPob_UtxtEditorWindow + item_UtxtEditFontMenu;
const MessageT	msg_UtxtEditSizeMenu		= PPob_UtxtEditorWindow + item_UtxtEditSizeMenu;
const MessageT	msg_UtxtEditStyleMenu		= PPob_UtxtEditorWindow + item_UtxtEditStyleMenu;
// Icon Editor Window
// ------------------
const MessageT	msg_IconEditPattern			= tool_Pattern;
const MessageT	msg_IconEditForeColor		= tool_ForeColor;
const MessageT	msg_IconEditBackColor		= tool_BackColor;		
const MessageT	msg_IconShowAsRgbx			= PPob_IconEditorWindow + item_IconShowAsRgbx;
const MessageT	msg_IconShowAsBitmap		= PPob_IconEditorWindow + item_IconShowAsBitmap;
const MessageT	msg_IconShowAsMask			= PPob_IconEditorWindow + item_IconShowAsMask;



// Other general purpose messages
// ------------------------------
const MessageT	msg_Close					= FOUR_CHAR_CODE('Clos');
const MessageT	msg_StylePrefsChanged		= FOUR_CHAR_CODE('StPC');
const MessageT	msg_HexScroller				= FOUR_CHAR_CODE('HScr');
const MessageT	msg_DualViewEdited			= FOUR_CHAR_CODE('DuEd');
const MessageT	msg_TmplMinusButton			= FOUR_CHAR_CODE('Mins');
const MessageT	msg_TmplPlusButton			= FOUR_CHAR_CODE('Plus');
const MessageT	msg_TmplCasePopup			= FOUR_CHAR_CODE('Case');
const MessageT	msg_TmplPopupField			= FOUR_CHAR_CODE('PopF');
const MessageT	msg_TmplModifiedItem		= FOUR_CHAR_CODE('TmMd');
const MessageT	msg_EditScroller			= FOUR_CHAR_CODE('Scrl');
const MessageT	msg_EditContents			= FOUR_CHAR_CODE('Cnts');
// Icon editor
const MessageT	msg_TargetViewClicked			= FOUR_CHAR_CODE('Tclk');
const MessageT	msg_ImageDroppedOnTargetView	= FOUR_CHAR_CODE('IDrp');
const MessageT	msg_DoubleClick					= FOUR_CHAR_CODE('DClk'); 
const MessageT	msg_GetLastCommand				= FOUR_CHAR_CODE('LCMD');


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
	kAERzilFilesList	 	=  FOUR_CHAR_CODE('LFil')
};

/* AE Dispatch Table constants (aedt) */
// const long	aeRzil_Open				= 5000;
// const long	aeRzil_Ltyp				= 5001;
// const long	aeRzil_Lrez				= 5002;
const long	aeRzil_Version				= 5010;

// AE Objects:
// -----------
const DescType rzil_cRezMapDoc		= 'MapD';	// RezMap document
const DescType rzil_cEditorDoc		= 'EdiD';	// Editor document
const DescType rzil_cGuiEditDoc		= 'GuiD';	// Gui editor document
const DescType rzil_cTmplEditDoc	= 'TmpD';	// Tmpl editor document
const DescType rzil_cHexEditDoc		= 'HexD';	// Hex editor document
const DescType rzil_cCompareDoc		= 'CmpD';	// Compare document

const DescType rzil_cRezMapWindow	= 'MapW';	// RezMap window
const DescType rzil_cGuiWindow		= 'GuiW';	// Gui editor window
const DescType rzil_cTmplWindow		= 'TmpW';	// Tmpl editor window
const DescType rzil_cHexWindow		= 'HexW';	// Hex editor window

const DescType rzil_cCompWindow		= 'CmpW';	// RezCompare window
const DescType rzil_cInspector		= 'Insp';	// Inspector window

const DescType rzil_cDataPane		= 'DatP';	// DataPane
const DescType rzil_cHexPane		= 'HexP';	// HexPane
const DescType rzil_cTxtPane		= 'TxtP';	// TxtPane

const DescType rzil_cMap			= 'cMAP';	// RezMap
const DescType rzil_cType			= 'cTYP';	// RezType
const DescType rzil_cResource		= 'cRSC';	// Resource (RezObj)

// Properties
// ----------
//    Application
const DescType rzil_pVersion		= pVersion;		// Version ('vers')	
const DescType rzil_pClipboard		= pClipboard;	// PrivateClipboard ('pcli')
const DescType rzil_pPreferences	= 'pPRF';		// Preferences

//    Document
const DescType rzil_pDocKind		= 'DKND';	// Document's kind

//    RezMap document
const DescType rzil_pRezFork		= 'pFRK';	// ResFork
const DescType rzil_pRezMap			= 'pMAP';	// RezMap
const DescType rzil_pRezFile		= 'pFIL';	// ResFile
const DescType rzil_pEditedRsrcDocs	= 'pERD';	// Edited resources documents

//    RezMap
const DescType rzil_pRefNum			= 'pRFN';		// RefNum
const DescType rzil_pAttributes		= 'pATR';		// Attributes
const DescType rzil_pReadOnly		= 'pRDO';		// mapReadOnly
const DescType rzil_pCompact		= 'pCPT';		// mapCompact
const DescType rzil_pChanged		= pIsModified;	// mapChanged/resChanged ('imod')

//    RezType

//    Resource
const DescType rzil_pResID			= pID;			// ID ('ID  ')			 
const DescType rzil_pName			= pName;		// Name ('pnam')
const DescType rzil_pType			= 'pTYP';		// Type
const DescType rzil_pSpecifier		= 'pSPE';		// Specifier (type,ID)
const DescType rzil_pSysHeap		= 'pSHP';		// resSysHeap
const DescType rzil_pPurgeable		= 'pPUR';		// resPurgeable
const DescType rzil_pLocked			= 'pLOC';		// resLocked
const DescType rzil_pProtected		= 'pPRO';		// resProtected
const DescType rzil_pPreload		= 'pPRE';		// resPreload
const DescType rzil_pSize			= 'pSIZ';		// Size
const DescType rzil_pData			= pContents;	// Data ('pcnt', was 'pDAT')

//    Specifier
const DescType rzil_cTypeID			= 'TyId';	// Resource specifier object: 
                           			         	//   e-g (type:aete, ID  :128)

//    Maps Comparison
const DescType rzil_cMapComparison	= 'COMP';	// Maps Comparison 
const DescType rzil_pIgnoreName		= 'IgnN';	// IgnoreNameDiff
const DescType rzil_pIgnoreAttr		= 'IgnA';	// IgnoreAttrDiff
const DescType rzil_pIgnoreData		= 'IgnD';	// IgnoreDataDiff
const DescType rzil_pOnlyInOld		= 'OldR';	// Only in old map resources (list)
const DescType rzil_pOnlyInNew		= 'NewR';	// Only in new map resources (list)
const DescType rzil_pDiffering		= 'Diff';	// In both but different (list)
const DescType rzil_pIdentical		= 'Iden';	// In both and identical (list)

//    HexPane/TxtPane
const DescType rzil_pContents		= pContents;	// Contents ('pcnt')

//    Editor document
const DescType rzil_pKind			= 'pKND';	// Kind

//    Tmpl editor document
const DescType rzil_pTemplate		= 'pTMP';	// Template



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
	err_TmplPopupNotConnectedToEditField,
	err_TmplCantFindKeyedSectionStart,
	err_TmplCantFindKeyStartForValue,
	err_TmplCantFindKeyIndex,
	err_TmplCantFindKeyValue,
	err_TmplCantFindKeyPosition,
	err_TmplUnsupportedResourceId,
	err_TmplCantFindMatchingKeyEnd,
	err_FirstError = 3000,   // Used by Icon editor
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
	err_IconResizeFormatString,
	err_IconFileLocked,
	err_IconBadFontSize,
	err_LastError					= 3099,   // Used by Icon editor
	err_RezillaErrorEnd
};



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
#define  kRzilDragHiliteColor	{ 65535, 0, 65535 }
// Pen size to frame drop region 
#define  kRzilDragHiliteSize	1
// Width of the three tables in the comparison results window
#define  kCompTableWidth	183
// Height of a row in these tables
#define  kCompTableHeight	14
// Height of a line in a WE view in case of null value
#define  kRzilDefaultLineHeight	11

// Drag and drop
const UInt32	DragFlavor_Rezilla		= FOUR_CHAR_CODE('Rzil');  // kRzilDragFlavor
const UInt32	DragFlavor_Offscreen	= FOUR_CHAR_CODE('OfSc');

// Constants for the Rezmap tables
const SInt16	kRzilColWidth		= 100;

// Constants for the Rez Hex editor
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
// Constants used by the Template Editor
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
// Definitions for the Icon editor
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
const SInt32		kRecolorDepth			= 8;
const UInt16		kMinTargetWidth			= 40;
const UInt16		kMinTargetHeight		= 40;
const UInt16		kLeftHeaderWidth		= 80;
const UInt16		kSampleOutMargin		= 10;
// Cursors are always the same size
const SInt32		kCursorWidth			= 16;
const SInt32		kCursorHeight			= 16;
// Black & white cursors have the following values (68 = 2 bw images, 16x16, + hotspot)
const SInt32		kBWCursorRowBytes		= 2;	
const SInt32		kBWCursorBytes			= 68;
const SInt32		kDefaultPatternWidth	= 8;
const SInt32		kDefaultPatternHeight	= 8;
const SInt32		kBWPatternRowBytes		= 1;
const SInt16		kDefaultMarchInterval	= 3;
// The default pattern is black
const Pattern	Pattern_Black = { { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF } };

#define kMaxIconSamplePanes		20

// For the Icon editor's clipboard and Drag&Drop
const OSType	ResType_Region			= FOUR_CHAR_CODE('RgN ');
const OSType	ResType_ColorCursor 	= FOUR_CHAR_CODE('crsr');
const ResType	ResType_PaneResizer		= FOUR_CHAR_CODE('RSIZ');
const ResType	ResType_IconFamilyInfo	= FOUR_CHAR_CODE('RzII');

// Three ways to redraw
enum RedrawOptions
{
	redraw_Now,
	redraw_Later,
	redraw_Dont
};

