// ===========================================================================
// RezillaConstants.h
// 
//                       Created : 2003-04-16 22:52:54
//             Last modification : 2004-12-01 08:41:48
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@easyconnect.fr>
// www : <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003-2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#pragma once


// Enums
// =====

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



// Resource ID's
// =============

const ResIDT	DITL_NewMap					= 10001;
const ResIDT	DITL_OpenMap				= 10002;
const ResIDT	DITL_SaveMap				= 10003;

const ResIDT	PPob_SelectVolDialog		= 1128;
const ResIDT	PPob_EditTable				= 1129;

const ResIDT	rPPob_RezMapWindow			= 1000;
const ResIDT	rPPob_InspectorWindow		= 2000;
const ResIDT	rPPob_NewRezDialog			= 2100;
const ResIDT	rPPob_HexEditorWindow		= 3000;
const ResIDT	rPPob_AboutWindow			= 5000;
const ResIDT	rPPob_LicenceWindow			= 5100;
const ResIDT	rPPob_RezCompDialog			= 6000;
const ResIDT	rPPob_RezCompWindow			= 6500;
const ResIDT	rPPob_PrefsWindow			= 7000;
const ResIDT	rPPob_PrefsGeneralPane		= 7100;
const ResIDT	rPPob_PrefsExportPane		= 7200;
const ResIDT	rPPob_PrefsComparePane		= 7300;
const ResIDT	rPPob_PrefsInterfacePane	= 7400;
const ResIDT	rPPob_PrefsEditorsPane		= 7500;
const ResIDT	rPPob_PrefsMiscPane			= 7600;
const ResIDT	rPPob_FindDialog			= 8500;
const ResIDT	rPPob_OtherSize				= 8600;
const ResIDT	rPPob_RezTypePicker			= 8700;
const ResIDT	rPPob_TmplKeyPicker			= 8800;
const ResIDT	rPPob_SimpleMessage			= 9500;
const ResIDT	rPPob_AskIfMessage			= 9510;
const ResIDT	rPPob_AskYesNoMessage		= 9520;
const ResIDT	rPPob_ExplainedError		= 9530;
const ResIDT	rPPob_AskUniqueID			= 9550;
const ResIDT	rPPob_TmplEditorWindow		= 10100;
const ResIDT	rPPob_TextEditorWindow		= 10200;
const ResIDT	rPPob_AeteEditorWindow		= 10300;
const ResIDT	rRidL_RezMapWindow			= rPPob_RezMapWindow;
const ResIDT	rRidL_InspectorWindow		= rPPob_InspectorWindow;
const ResIDT	rRidL_NewRezDialog			= rPPob_NewRezDialog;
const ResIDT	rRidL_HexEditorWindow		= rPPob_HexEditorWindow;
const ResIDT	rRidL_TmplEditorWindow		= rPPob_TmplEditorWindow;
const ResIDT	rRidL_TextEditorWindow		= rPPob_TextEditorWindow;
const ResIDT	rRidL_AeteEditorWindow		= rPPob_AeteEditorWindow;
const ResIDT	rRidL_AboutWindow			= rPPob_AboutWindow;
const ResIDT	rRidL_FindDialog			= rPPob_FindDialog;
const ResIDT	rRidL_RezCompDialog			= rPPob_RezCompDialog;
const ResIDT	rRidL_RezCompWindow			= rPPob_RezCompWindow;
const ResIDT	rRidL_AskUniqueID			= rPPob_AskUniqueID;
const ResIDT	rRidL_RezTypePicker			= rPPob_RezTypePicker;
const ResIDT	rRidL_TmplKeyPickerPicker	= rPPob_TmplKeyPicker;

const ResIDT	ics8_Unlocked				= 1500;
const ResIDT	ics8_Locked					= 1501;

const ResIDT	CURS_HandCursor				= 1000;

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

// Text traits resources
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
	// rMENU_Window is not a resource. It is built  
	// in CRezillaApp::InstallWindowMenu()
const ResIDT	rMENU_Window				= 1300;  
const ResIDT	rMENU_Help					= 2000;
const ResIDT	rMENU_RecentItems			= 140;  
const ResIDT	rMENU_TemplateCases			= 150;  
// Values the PP menu cmds are based on
const ResIDT	baseMENU_File				= 1000;
const ResIDT	baseMENU_Edit				= 1100;
const ResIDT	baseMENU_Resource			= 1200;

// Icon resources
const ResIDT	ICN_WindowMenu				= 3100;

// Indices in STR# resources
// -------------------------
// Indices of STR# 1500: untitled windows names
const SInt16	index_RezMapUntitled		= 1;
const SInt16	index_RezMapUntitledX		= 2;
const SInt16	index_HexEditUntitled		= 3;
const SInt16	index_HexEditUntitledX		= 4;
const SInt16	index_CompWinUntitled		= 5;
const SInt16	index_CompWinUntitledX		= 6;
const SInt16	index_TmplEditUntitled		= 7;
const SInt16	index_TmplEditUntitledX		= 8;
const SInt16	index_TEXTEditUntitled		= 9;
const SInt16	index_TEXTEditUntitledX		= 10;
const SInt16	index_AeteEditUntitled		= 11;
const SInt16	index_AeteEditUntitledX		= 12;
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
// Indices of STR# 1503: internet urls for about box
/* 
 * const SInt16    index_urlProjCaption        = 1;
 * const SInt16    index_urlProjURL            = 2;
 * const SInt16    index_urlBinsCaption        = 3;
 * const SInt16    index_urlBinsUEL            = 4;
 * const SInt16    index_urlCvsCaption            = 5;
 * const SInt16    index_urlCvsUEL                = 6;
 * const SInt16    index_urlBugCaption            = 7;
 * const SInt16    index_urlBugUEL                = 8;
 * const SInt16    index_urlMailCaption        = 9;
 * const SInt16    index_urlMailURL            = 10;
 */



// Menu commands
// =============
// Help menu items
const MessageT	cmd_Help					= 3000;	
// Window menu items
const MessageT	cmd_ShowInspector			= 2001;	
// Resource menu items
const MessageT	cmd_NewRez				= baseMENU_Resource + 1;	
const MessageT	cmd_EditRez				= baseMENU_Resource + 2;	
const MessageT	cmd_TmplEditRez			= baseMENU_Resource + 3;	
const MessageT	cmd_HexEditRez			= baseMENU_Resource + 4;	
const MessageT	cmd_EditRezAsType		= baseMENU_Resource + 5;	
const MessageT	cmd_RemoveRez			= baseMENU_Resource + 10;	
const MessageT	cmd_DuplicateRez		= baseMENU_Resource + 11;	
const MessageT	cmd_GetRezInfo			= baseMENU_Resource + 15;
const MessageT	cmd_TmplEditAsRez		= baseMENU_Resource + 99;	
// File menu items
const MessageT	cmd_ExportMap			= baseMENU_File + 1;	
const MessageT	cmd_RecentItems			= baseMENU_File + 2;	
// Edit menu items
const MessageT	cmd_Find				= baseMENU_Edit + 1;	
const MessageT	cmd_FindNext			= baseMENU_Edit + 2;	
const MessageT	cmd_RezCompare			= baseMENU_Edit + 3;	

// Control ID's
// ============
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


// Common elements for Editor Windows
// ----------------------------------
const PaneIDT   item_EditorContents		= FOUR_CHAR_CODE('Cnts');
const PaneIDT   item_EditorScroller		= FOUR_CHAR_CODE('Scrl');
const PaneIDT   item_EditorValidate		= FOUR_CHAR_CODE('Vlid');
const PaneIDT   item_EditorCancel		= FOUR_CHAR_CODE('Cncl');
const PaneIDT   item_EditorRevert		= FOUR_CHAR_CODE('Rvrt');
const PaneIDT	item_NameStaticText		= FOUR_CHAR_CODE('Name');
const PaneIDT	item_ReadOnlyIcon		= FOUR_CHAR_CODE('Lock');

// 'Other size' dialog
// -------------------
const PaneIDT   item_OtherSizeField			= 1;

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


// Messages ID's
// =============
// Inspector Window
// ----------------
const MessageT	msg_InspEditID			= rPPob_InspectorWindow + item_InspEditID;
const MessageT	msg_InspEditName		= rPPob_InspectorWindow + item_InspEditName;
const MessageT	msg_InspSysHeap			= rPPob_InspectorWindow + item_InspSysHeap;
const MessageT	msg_InspPurgeable		= rPPob_InspectorWindow + item_InspPurgeable;
const MessageT	msg_InspLocked			= rPPob_InspectorWindow + item_InspLocked;
const MessageT	msg_InspProtected		= rPPob_InspectorWindow + item_InspProtected;
const MessageT	msg_InspPreload			= rPPob_InspectorWindow + item_InspPreload;
const MessageT	msg_InspRevert			= rPPob_InspectorWindow + item_InspRevert;
const MessageT	msg_InspModify			= rPPob_InspectorWindow + item_InspModify;
// New Resource Window
// -------------------
const MessageT	msg_NewType				= rPPob_NewRezDialog + item_NewType;
const MessageT	msg_NewID				= rPPob_NewRezDialog + item_NewID;
const MessageT	msg_NewName				= rPPob_NewRezDialog + item_NewName;
const MessageT	msg_NewSysHeap			= rPPob_NewRezDialog + item_NewSysHeap;
const MessageT	msg_NewPurgeable		= rPPob_NewRezDialog + item_NewPurgeable;
const MessageT	msg_NewLocked			= rPPob_NewRezDialog + item_NewLocked;
const MessageT	msg_NewProtected		= rPPob_NewRezDialog + item_NewProtected;
const MessageT	msg_NewPreload			= rPPob_NewRezDialog + item_NewPreload;
const MessageT	msg_NewUniqueID			= rPPob_NewRezDialog + item_NewUniqueID;
// Hex Edit Window
// ---------------
const MessageT	msg_HexLineEdit			= rPPob_HexEditorWindow + item_HexLineEdit;
const MessageT	msg_HexOffsetEdit		= rPPob_HexEditorWindow + item_HexOffsetEdit;
// About box
// ---------
const MessageT	msg_AboutOkButton		= rPPob_AboutWindow + item_AboutOkButton;
const MessageT	msg_AboutLicenceButton	= rPPob_AboutWindow + item_AboutLicenceButton;
// Find Dialog
// -----------
const MessageT	msg_FindSearchField		= rPPob_FindDialog + item_FindSearchField;
const MessageT	msg_FindInHexRadio		= rPPob_FindDialog + item_FindInHexRadio;
const MessageT	msg_FindInTxtRadio		= rPPob_FindDialog + item_FindInTxtRadio;
const MessageT	msg_FindIgnoreCase		= rPPob_FindDialog + item_FindIgnoreCase;
const MessageT	msg_FindRegexp			= rPPob_FindDialog + item_FindRegexp;
// Rez Compare Dialog
// ------------------
const MessageT	msg_RezCompSetOld		= rPPob_RezCompDialog + item_RezCompSetOld;
const MessageT	msg_RezCompSetNew		= rPPob_RezCompDialog + item_RezCompSetNew;
const MessageT	msg_RezCompIgnoreNames	= rPPob_RezCompDialog + item_RezCompIgnoreNames;
const MessageT	msg_RezCompIgnoreAttrs	= rPPob_RezCompDialog + item_RezCompIgnoreAttrs;
const MessageT	msg_RezCompIgnoreData	= rPPob_RezCompDialog + item_RezCompIgnoreData;
// Rez Compare Results Window
// --------------------------
const MessageT	msg_CompResultScroller		= rPPob_RezCompWindow + item_CompResultScroller;
const MessageT	msg_CompResultHexRadio		= rPPob_RezCompWindow + item_CompResultHexRadio;
const MessageT	msg_CompResultTxtRadio		= rPPob_RezCompWindow + item_CompResultTxtRadio;
const MessageT	msg_CompResultOnlyOldTbl	= rPPob_RezCompWindow + item_CompResultOnlyOldTbl;
const MessageT	msg_CompResultDifferingTbl	= rPPob_RezCompWindow + item_CompResultDifferingTbl;
const MessageT	msg_CompResultOnlyNewTbl	= rPPob_RezCompWindow + item_CompResultOnlyNewTbl;
// Ask Unique ID dialog
// --------------------
const MessageT	msg_UidOtherConflicts		= rPPob_AskUniqueID + item_UidOtherConflicts;
// Resource Type Picker
// --------------------
const MessageT	msg_TypePickerField			= rPPob_RezTypePicker + item_TypePickerField;
const MessageT	msg_TypePickerMenu			= rPPob_RezTypePicker + item_TypePickerMenu;
// Template Option Picker
// ----------------------
const MessageT	msg_TmplKeyPickerMenu		= rPPob_TmplKeyPicker + item_TmplKeyPickerMenu;

// Preferences
// -----------
const MessageT  msg_PrefsRevert				= rPPob_PrefsWindow + 3;
//     General Prefs Pane
//     ------------------
const MessageT  msg_GenPrefsMaxRecent       = rPPob_PrefsGeneralPane + item_GenPrefsMaxRecent;
const MessageT	msg_GenPrefsResetRecent		= rPPob_PrefsGeneralPane + item_GenPrefsResetRecent;
const MessageT	msg_GenPrefsDataFork		= rPPob_PrefsGeneralPane + item_GenPrefsDataFork;
const MessageT	msg_GenPrefsResourceFork	= rPPob_PrefsGeneralPane + item_GenPrefsResourceFork;
//     Export Prefs Pane
//     -----------------
const MessageT	msg_ExpPrefsKeyDtd			= rPPob_PrefsExportPane + item_ExpPrefsKeyDtd;
const MessageT	msg_ExpPrefsAttrDtd			= rPPob_PrefsExportPane + item_ExpPrefsAttrDtd;
const MessageT	msg_ExpPrefsInclBinData		= rPPob_PrefsExportPane + item_ExpPrefsInclBinData;
const MessageT	msg_ExpPrefsHexEnc			= rPPob_PrefsExportPane + item_ExpPrefsHexEnc;
const MessageT	msg_ExpPrefsBase64Enc		= rPPob_PrefsExportPane + item_ExpPrefsBase64Enc;
const MessageT	msg_ExpPrefsEditSig			= rPPob_PrefsExportPane + item_ExpPrefsEditSig;
//     Compare Prefs Pane
//     ------------------
const MessageT	msg_CompPrefsIgnName		= rPPob_PrefsComparePane + item_CompPrefsIgnName;
const MessageT	msg_CompPrefsIgnAttr		= rPPob_PrefsComparePane + item_CompPrefsIgnAttr;
const MessageT	msg_CompPrefsIgnData		= rPPob_PrefsComparePane + item_CompPrefsIgnData;
const MessageT	msg_CompPrefsHexDisplay		= rPPob_PrefsComparePane + item_CompPrefsHexDisplay;
const MessageT	msg_CompPrefsTxtDisplay		= rPPob_PrefsComparePane + item_CompPrefsTxtDisplay;
//     Interface Prefs Pane
//     --------------------
const MessageT	msg_UIPrefsFontsMenu		= rPPob_PrefsInterfacePane + item_UIPrefsFontsMenu;
const MessageT	msg_UIPrefsSizeMenu			= rPPob_PrefsInterfacePane + item_UIPrefsSizeMenu;
//     Editors Prefs Pane
//     ------------------
const MessageT	msg_EditPrefsHexSym0x		= rPPob_PrefsEditorsPane + item_EditPrefsHexSym0x;
const MessageT	msg_EditPrefsHexSymDollar	= rPPob_PrefsEditorsPane + item_EditPrefsHexSymDollar;
const MessageT	msg_EditPrefsHexLowercase	= rPPob_PrefsEditorsPane + item_EditPrefsHexLowercase;
const MessageT	msg_EditPrefsHexUppercase	= rPPob_PrefsEditorsPane + item_EditPrefsHexUppercase;
const MessageT	msg_EditPrefsDispFillers	= rPPob_PrefsEditorsPane + item_EditPrefsDispFillers;
const MessageT	msg_EditPrefsEnableFillers	= rPPob_PrefsEditorsPane + item_EditPrefsEnableFillers;
//     Misc Prefs Pane
//     ---------------
const MessageT	msg_MiscPrefsSetSigOnClose	= rPPob_PrefsMiscPane + item_MiscPrefsSetSigOnClose;
const MessageT	msg_MiscPrefsClosingType	= rPPob_PrefsMiscPane + item_MiscPrefsClosingType;
const MessageT	msg_MiscPrefsClosingCreator	= rPPob_PrefsMiscPane + item_MiscPrefsClosingCreator;
const MessageT	msg_MiscPrefsSetSigOnCreate	= rPPob_PrefsMiscPane + item_MiscPrefsSetSigOnCreate;
const MessageT	msg_MiscPrefsOnlyRsrcExt	= rPPob_PrefsMiscPane + item_MiscPrefsOnlyRsrcExt;
// Tmpl Editor Window
// ------------------
const MessageT	msg_EditorValidate			= msg_OK;
const MessageT	msg_EditorCancel			= msg_Cancel;
const MessageT	msg_EditorRevert			= cmd_Revert;
// Text Editor Window
// ------------------
const MessageT	msg_TextEditScroller		= FOUR_CHAR_CODE('Scrl');
const MessageT	msg_TextEditContents		= FOUR_CHAR_CODE('Cnts');
const MessageT	msg_TextEditFontMenu		= rPPob_TextEditorWindow + item_TextEditFontMenu;
const MessageT	msg_TextEditSizeMenu		= rPPob_TextEditorWindow + item_TextEditSizeMenu;
const MessageT	msg_TextEditStyleMenu		= rPPob_TextEditorWindow + item_TextEditStyleMenu;
// Aete Editor Window
// ------------------
const MessageT	msg_AeteSuitesPopup			= rPPob_AeteEditorWindow + item_AeteSuitesPopup;
const MessageT	msg_AeteCategories			= rPPob_AeteEditorWindow + item_AeteCategories;
const MessageT	msg_AeteTermsTable			= rPPob_AeteEditorWindow + item_AeteTermsTable;

// Other general purpose messages
// ------------------------------
const MessageT	msg_Close					= 	FOUR_CHAR_CODE('Clos');
const MessageT	msg_StylePrefsChanged		= 	FOUR_CHAR_CODE('StPC');
const MessageT	msg_HexScroller				=	FOUR_CHAR_CODE('HScr');
const MessageT	msg_DualViewEdited			= 	FOUR_CHAR_CODE('DuEd');
const MessageT	msg_TmplMinusButton			= 	FOUR_CHAR_CODE('Mins');
const MessageT	msg_TmplPlusButton			= 	FOUR_CHAR_CODE('Plus');
const MessageT	msg_TmplCasePopup			= 	FOUR_CHAR_CODE('Case');
const MessageT	msg_TmplPopupField			= 	FOUR_CHAR_CODE('PopF');
const MessageT	msg_TmplModifiedItem		= 	FOUR_CHAR_CODE('TmMd');



// AE CONSTANTS
// ============
// AE suites
enum
{
	kAERzilClass			=    FOUR_CHAR_CODE('Rzil'),
	kAERsrcClass			=    FOUR_CHAR_CODE('Rsrc')
};

// Various AE parameters
enum
{
	kAERzilReply	 		=	 FOUR_CHAR_CODE('Repl'),
	kAERzilFilesList	 	=	 FOUR_CHAR_CODE('LFil')
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



// ERROR CONSTANTS
// ===============
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
	err_RezillaErrorEnd
};



// Misc constants
// ==============
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
const UInt32	kRzilDragFlavor		= FOUR_CHAR_CODE('Rzil');

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

// Constants used by the template editor
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

