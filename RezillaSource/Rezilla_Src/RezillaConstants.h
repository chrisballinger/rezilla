// ===========================================================================
// RezillaConstants.h
// 
//                       Created : 2003-04-16 22:52:54
//             Last modification : 2004-03-21 15:29:46
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

// Reference numbers
// Use kResFileNotOpened and kSystemResFile instead (defined in Resources.h)
// enum
// {	
// 	refnum_undefined = -1,
// 	refnum_system = 0
// };

// Export formats
enum
{	
	export_Xml = 0,
	export_Text,
	export_Html,
	export_Derez
} ;

// Rez comparison results
enum
{	
	compare_noDiff = 0,
	compare_sizeDiff,
	compare_dataDiff,
	compare_nameDiff,
	compare_flagDiff
} ;



// Resource ID's
// =============

const ResIDT	icon_Folder					= 10000;
const ResIDT	icon_Document				= 20000;
const ResIDT	icon_App					= 25000;

const ResIDT	DITL_NewMap					= 10001;
const ResIDT	DITL_OpenMap				= 10002;
const ResIDT	DITL_SaveMap				= 10003;

const ResIDT	PPob_SelectVolDialog		= 1128;
const ResIDT	PPob_EditTable				= 1129;

const ResIDT	rPPob_RezMapWindow			= 1000;
const ResIDT	rPPob_InspectorWindow		= 2000;
const ResIDT	rPPob_NewRezDialog			= 2100;
const ResIDT	rPPob_HexEditWindow			= 3000;
const ResIDT	rPPob_AboutWindow			= 5000;
const ResIDT	rPPob_LicenceWindow			= 5100;
const ResIDT	rPPob_RezCompDialog			= 6000;
const ResIDT	rPPob_RezCompWindow			= 6500;
const ResIDT	rPPob_FindDialog			= 8500;
const ResIDT	rPPob_SimpleMessage			= 9500;
const ResIDT	rPPob_AskIfMessage			= 9510;
const ResIDT	rPPob_AskYesNoMessage		= 9520;
const ResIDT	rPPob_AskUniqueID			= 9550;
const ResIDT	rRidL_RezMapWindow			= rPPob_RezMapWindow;
const ResIDT	rRidL_InspectorWindow		= rPPob_InspectorWindow;
const ResIDT	rRidL_NewRezDialog			= rPPob_NewRezDialog;
const ResIDT	rRidL_HexEditWindow			= rPPob_HexEditWindow;
const ResIDT	rRidL_AboutWindow			= rPPob_AboutWindow;
const ResIDT	rRidL_FindDialog			= rPPob_FindDialog;
const ResIDT	rRidL_RezCompDialog			= rPPob_RezCompDialog;
const ResIDT	rRidL_RezCompWindow			= rPPob_RezCompWindow;
const ResIDT	rRidL_AskUniqueID			= rPPob_AskUniqueID;


const ResIDT	STRx_RzilErrorStrings		= 1000;
const ResIDT	STRx_PrefsCtrlList			= 1004;
const ResIDT	STRx_DefaultDocTitles		= 1500;
const ResIDT	STRx_RzilWinMenuItem		= 1501;
const ResIDT	STRx_NavStrings				= 1502;
const ResIDT	STRx_FileExtensions			= 1503;

// Menu resources
	// rMENU_Window is not a resource. It is built  
	// in CRezillaApp::InstallWindowMenu()
const ResIDT	rMENU_Window				= 1300;  
const ResIDT	rMENU_Help					= 2000;
const ResIDT	rMENU_RecentItems			= 140;  
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


// Menu commands
// =============
// Help menu items
const MessageT	cmd_Help					= 3000;	
// Window menu items
const MessageT	cmd_ShowInspector			= 2001;	
// Resource menu items
const MessageT	cmd_NewRez				= baseMENU_Resource + 1;	
const MessageT	cmd_EditRez				= baseMENU_Resource + 2;	
const MessageT	cmd_GetRezInfo			= baseMENU_Resource + 3;
const MessageT	cmd_RemoveRez			= baseMENU_Resource + 4;	
const MessageT	cmd_DuplicateRez		= baseMENU_Resource + 5;	
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
const PaneIDT	item_ReadOnly				= 4;
// Inspector Window
// ----------------
const PaneIDT	item_InspType				= 1;
const PaneIDT	item_InspOrigID				= 2;
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
const PaneIDT	item_InspCompressed			= 16;
const PaneIDT	item_InspRevert				= 20;
const PaneIDT   item_InspModify				= 21;
// Hex Edit Window
// ---------------
const PaneIDT	item_HexScroller			= 1;
const PaneIDT	item_HexDataWE				= 2;
const PaneIDT	item_TxtDataWE				= 3;
const PaneIDT	item_HexLineEdit			= 4;
const PaneIDT	item_HexOffsetEdit			= 5;
const PaneIDT	item_NameStaticText			= 6;
// New Resource Window
// -------------------
const PaneIDT	item_NewType				= 1;
const PaneIDT	item_NewID					= 3;
const PaneIDT	item_NewName				= 4;
// const PaneIDT	item_NewIcon					= 5;
const PaneIDT	item_NewSysHeap				= 11;
const PaneIDT	item_NewPurgeable			= 12;
const PaneIDT	item_NewLocked				= 13;
const PaneIDT	item_NewProtected			= 14;
const PaneIDT	item_NewPreload				= 15;
const PaneIDT	item_NewCompressed			= 16;
const PaneIDT	item_NewUniqueID			= 20;
// About box
// ---------
const PaneIDT	item_AboutOkButton			= 1;
const PaneIDT	item_AboutVersCaption		= 2;
const PaneIDT	item_AboutWasteView			= 3;
const PaneIDT	item_AboutLicenceButton		= 4;
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
const PaneIDT	item_CompResultHexRadio		= 6;
const PaneIDT	item_CompResultTxtRadio		= 7;
const PaneIDT	item_CompResultOnlyOldTbl	= 11;
const PaneIDT	item_CompResultDifferingTbl	= 13;
const PaneIDT	item_CompResultOnlyNewTbl	= 15;
// Ask Unique ID dialog
// --------------------
const PaneIDT	item_UidOtherConflicts		= 1;


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
const MessageT	msg_InspCompressed		= rPPob_InspectorWindow + item_InspCompressed;
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
const MessageT	msg_NewCompressed		= rPPob_NewRezDialog + item_NewCompressed;
const MessageT	msg_NewUniqueID			= rPPob_NewRezDialog + item_NewUniqueID;
// Hex Edit Window
// ---------------
const MessageT	msg_HexScroller			= rPPob_HexEditWindow + item_HexScroller;
const MessageT	msg_HexLineEdit			= rPPob_HexEditWindow + item_HexLineEdit;
const MessageT	msg_HexOffsetEdit		= rPPob_HexEditWindow + item_HexOffsetEdit;
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
const MessageT	msg_UidOtherConflicts	= rPPob_AskUniqueID + item_UidOtherConflicts;



// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
const MessageT  msg_RevertPrefs                 = rPPob_FindDialog + 6;
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------

const MessageT	msg_Close					= 	FOUR_CHAR_CODE('Clos');
const MessageT	msg_StylePrefsChanged		= 	FOUR_CHAR_CODE('StPC');


// AE constants
// ============
// AE event class and ID
enum
{
	keyAERezillaClass			=    FOUR_CHAR_CODE('Rzil'),
	keyAERezillaReplyBuffer 	=	 FOUR_CHAR_CODE('Repl')
};


/* Apple Events constants (aedt) */
// const long	aeRzil_Open				= 5000;
// const long	aeRzil_Ltyp				= 5001;
// const long	aeRzil_Lrez				= 5002;
const long	aeRzil_Version				= 5010;


// Error constants
enum
{
	err_NoRezInDataFork = 1001,
	err_NoRezInRezFork,
	err_NoRezInAnyFork,
	err_NoOpenPermission,
	err_OpenForkError
};



// Misc constants
// ==============
// Signatures
#define  keyEditorSignature  	'ttxt'
#define	 kRezillaType			'Rzil'
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
const SInt16	kRzilDragFlavor		= FOUR_CHAR_CODE('Rzil');

// Constants for the Rezmap tables
const SInt16	kRzilColWidth				= 100;
// Constants for the Rez Compare results window
//     kRzilHexCompBytesPerLine and kRzilTxtCompBytesPerLine are counts of bytes 
//     which have to be multiplied by 3 (two hex digits + space) or by 2 (one char + space) resp.
const SInt16	kRzilRezCompLineCount		= 12;
const SInt16	kRzilHexCompBytesPerLine	= 16;
const SInt16	kRzilTxtCompBytesPerLine	= 24;
// Constants for the Rez Hex editor
//     kRzilHexEditBytesPerLine and kRzilHexEditBytesPerPane are counts of bytes 
//     which have to be multiplied by 3 (two hex digits + space) or by 2 in text
//     representation (one char + space)
const SInt16	kRzilHexEditLineCount		= 32;
const SInt16	kRzilHexEditBytesPerLine	= 16;
const SInt16	kRzilHexEditBytesPerPane	= kRzilHexEditLineCount * kRzilHexEditBytesPerLine;
// Max number of items in the Recent Items menu
const SInt16	kRzilMaxRecentItems	= 10;



const ResType	ResType_DITL = FOUR_CHAR_CODE('DITL');

// #define  kFirstSizeMenuItem	1
// #define  kLastSizeMenuItem	9

