// ===========================================================================
// RezillaConstants.h
// 
//                       Created : 2003-04-16 22:52:54
//             Last modification : 2003-10-03 16:32:43
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@easyconnect.fr>
// www : <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003
// All rights reserved.
// ===========================================================================

#pragma once


// Enums
// =====

// Fork indices
enum
{	
	from_anyfork = 0,
	from_rezfork,
	from_datafork
};

enum
{	
	to_undefinedfork = -1,
	to_samefork = 0,
	to_rezfork,
	to_datafork
};

enum
{	
	new_rezfork = 0,
	new_datafork
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

// File extensions indices
// enum
// {	
// 	rNoExtIndex = 1,
// 	rRsrcExtIndex,
// 	rRsrcExtIndex,
// 	rRsrcExtIndex
// };

enum
{	
	refnum_undefined = -1,
	refnum_system = 0
};


// Resource ID's
// =============

const ResIDT	icon_Folder					= 10000;
const ResIDT	icon_Document				= 20000;
const ResIDT	icon_App					= 25000;

const ResIDT	PPob_SelectVolDialog		= 1128;
const ResIDT	PPob_EditTable				= 1129;

const ResIDT	rPPob_RezMapWindow			= 1000;
const ResIDT	rPPob_InspectorWindow		= 2000;
const ResIDT	rPPob_NewRezDialog			= 2100;
const ResIDT	rPPob_HexEditWindow			= 3000;
const ResIDT	rPPob_AboutWindow			= 5000;
const ResIDT	rPPob_LicenceWindow			= 5100;
const ResIDT	rPPob_FindDialog			= 8500;
const ResIDT	rPPob_SimpleMessage			= 9500;
const ResIDT	rPPob_AskIfMessage			= 9510;
const ResIDT	rPPob_AskYesNoMessage		= 9520;
const ResIDT	rRidL_RezMapWindow			= rPPob_RezMapWindow;
const ResIDT	rRidL_InspectorWindow		= rPPob_InspectorWindow;
const ResIDT	rRidL_NewRezWindow			= rPPob_NewRezDialog;
const ResIDT	rRidL_HexEditWindow			= rPPob_HexEditWindow;
const ResIDT	rRidL_AboutWindow			= rPPob_AboutWindow;
const ResIDT	rRidL_FindDialog			= rPPob_FindDialog;

const ResIDT	STRx_DefaultScriptTitle		= 1500;

const ResIDT	STRx_RzilErrorStrings		= 1000;
const ResIDT	STRx_RzilMessageStrings		= 1001;
const ResIDT	STRx_NavServStrings			= 1002;
const ResIDT	STRx_FileExtensions			= 1003;
const ResIDT	STRx_PrefsCtrlList			= 1004;
const ResIDT	STRx_DefaultDocTitles		= 1500;
const ResIDT	STRx_RzilWinMenuItem		= 1510;

// Menu resources
const ResIDT	rMENU_File					= 1000;
const ResIDT	rMENU_Edit					= 1100;
const ResIDT	rMENU_Resource				= 1200;
	// rMENU_Window is not a resource. It is built  
	// in CRezillaApp::InstallWindowMenu()
const ResIDT	rMENU_Window				= 1300;  
const ResIDT	rMENU_Export				= 1400;
const ResIDT	rMENU_Help					= 2000;

// Icon resources
const ResIDT	ICN_WindowMenu				= 3100;

// Indices in STR# resources
// -------------------------
// Indices of STR# 1002: save as names
const SInt16	index_RezillaAppName		= 1;
const SInt16	index_SaveRezFileAs			= 2;
const SInt16	index_SaveResourceAs		= 3;
const SInt16	index_SaveUntitledRsrc		= 4;
const SInt16	index_SaveUntitledIcon		= 5;
const SInt16	index_CreateNewRezMap		= 6;
const SInt16	index_CreateUntitled		= 7;
// Indices of STR# 1003: file extensions
const SInt16	index_NoExt					= 1;
const SInt16	index_ExtRsrc				= 2;
const SInt16	index_ExtText				= 3;
const SInt16	index_ExtXml				= 4;
const SInt16	index_ExtR					= 5;
const SInt16	index_ExtIcns				= 6;
// Indices of STR# 1500: untitled windows names
const SInt16	index_RezMapUntitled		= 1;
const SInt16	index_RezMapUntitledX		= 2;
const SInt16	index_HexEditUntitled		= 3;
const SInt16	index_HexEditUntitledX		= 4;
// Inspector names
const SInt16	index_WinsInspector			= 1;
const SInt16	index_WinsTypeInspector		= 2;
const SInt16	index_WinsRezInspector		= 3;


// Menu commands
// =============
// Help menu items
const MessageT	cmd_Help					= 3000;	
// Window menu items
const MessageT	cmd_ShowInspector			= 2001;	
// Resource menu items
const MessageT	cmd_NewRez				= rMENU_Resource + 1;	
const MessageT	cmd_EditRez				= rMENU_Resource + 2;	
const MessageT	cmd_GetRezInfo			= rMENU_Resource + 3;
const MessageT	cmd_RemoveRez			= rMENU_Resource + 4;	
const MessageT	cmd_DuplicateRez		= rMENU_Resource + 5;	
// File menu items
const MessageT	cmd_ExportAsText		= rMENU_File + 1;	
const MessageT	cmd_ExportAsXML			= rMENU_File + 2;	
// Edit menu items
const MessageT	cmd_Find				= rMENU_Edit + 1;	
const MessageT	cmd_FindNext			= rMENU_Edit + 2;	
// Export submenu items
const MessageT	cmd_ExportAsText		= rMENU_Export + 1;	
const MessageT	cmd_ExportAsXML			= rMENU_Export + 2;	

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
// const long	ae_Rzil					= 5000;
const long	ae_Version				= 5001;


// Misc constants
// ==============
// Signatures
#define  keyEditorSignature  	'CWIE'
#define	 keyAERezillaSignature	'Rzil'
// File extension separator
#define  kFileExtSeparator		(char)'.'
// Preferences identifier
#define  kRezillaIdentifier		"fr.rezilla.bdesgraupes"
// Color to frame drop region 
#define  kRzilDragHiliteColor	{ 65535, 0, 65535 }
// Pen size to frame drop region 
#define  kRzilDragHiliteSize	1

const SInt16	kRzilDragFlavor		= FOUR_CHAR_CODE('Rzil');
const SInt16	kRzilColWidth		= 100;
const SInt16	kRzilHexLineCount	= 32;
const SInt16	kRzilHexPerLine		= 16;
const SInt16	kRzilHexPerPane		= 512;
 

// #define  kFirstSizeMenuItem	1
// #define  kLastSizeMenuItem	9

