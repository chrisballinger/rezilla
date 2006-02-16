// ===========================================================================
// CRezillaApp.cp					
//                       Created: 2003-04-16 22:13:54
//             Last modification: 2006-02-16 00:11:01
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2003-2005, 2006
// All rights reserved.
// ===========================================================================

#include "CRezillaApp.h"
#include "CRezillaPrefs.h"
#include "CRezillaModel.h"
#include "CEditorsController.h"
#include "CInspectorWindow.h"
#include "CRecentItemsMenu.h"
#include "CRezClipboard.h"
#include "CRezCompare.h"
#include "CRezFile.h"
#include "CRezMap.h"
#include "CRezMapDoc.h"
#include "CRezMapTable.h"
#include "CRezMapWindow.h"
#include "CTemplatesController.h"
#include "CPluginsController.h"
#include "CWindowMenu.h"
#include "NavServicesCallbacks.h"
#include "UDialogBoxHandler.h"
#include "UMessageDialogs.h"
#include "UNavigationDialogs.h"

// Custom classes for registration
#include "CAboutWindow.h"
#include "CAete_EditorWindow.h"
#include "CBiDataWE.h"
#include "CBroadcasterTableView.h"
#include "CColorPane.h"
#include "CCompResultWindow.h"
#include "CDoubleClickButton.h"
#include "CDraggableTargetView.h"
#include "CDropStaticText.h"
#include "CDualDataView.h"
#include "CFlagPopup.h"
#include "CHexDataSubView.h"
#include "CHexEditorWindow.h"
#include "CIcon_EditorView.h"
#include "CIcon_EditorWindow.h"
#include "CKeyboardGlyphBox.h"
#include "CMENU_EditorTable.h"
#include "CMENU_EditorWindow.h"
#include "CPICT_EditorView.h"
#include "CPICT_EditorWindow.h"
#include "CPatternPane.h"
#include "CPatternTargetView.h"
#include "CPopupEditField.h"
#include "CRangeEditText.h"
#include "CRezIconPane.h"
#include "CSingleScrollBar.h"
#include "CStaticEditCombo.h"
#include "CStaticTextURL.h"
#include "CSTRx_EditorWindow.h"
#include "CSuiteSlider.h"
#include "CSuite_Window.h"
#include "CTEXT_EditorView.h"
#include "CTEXT_EditorWindow.h"
#include "CThreeButtonsBox.h"
#include "CTmplEditorWindow.h"
#include "CTxtDataSubView.h"
#include "CUtxt_EditorDoc.h"
#include "CUtxt_EditorView.h"
#include "CUtxt_EditorWindow.h"
#include "CWasteEditView.h"
#include "CWindow_ColorIcon.h"
#include "CWindow_Cursor.h"
#include "CWindow_IconFamily.h"
#include "CWindow_IconSuite.h"
#include "CWindow_Pattern.h"
#include "CWindow_Picture.h"
#include "CWindow_PatternSuite.h"
// #include "ABalloon.h"

// PP Classes for registration
#include <Appearance.h>
#include <LAMControlImp.h>
#include <LAMPopupButtonImp.h>
#include <LAMPushButtonImp.h>
#include <LAMTrackActionImp.h>
#include <LActiveScroller.h>
#include <LCaption.h>
// #include <LClipboard.h>
#include <LCheckBox.h>
#include <LDialogBox.h>
#include <LDragAndDrop.h>
#include <LEditField.h>
#include <LEditText.h>
#include <LFile.h>
#include <LGAPopupButtonImp.h>
#include <LGAPushButtonImp.h>
#include <LGAWindowHeaderImp.h>
#include <LIconPane.h>
#include <LPageController.h>
#include <LPicture.h>
#include <LPopupButton.h>
#include <LPushButton.h>
#include <LRadioGroup.h>
#include <LScrollBar.h>
#include <LScrollerView.h>
#include <LStaticText.h>
#include <LStdControl.h>
#include <LStdScrollBarImp.h>
#include <LTabGroupView.h>
#include <LWindow.h>
#include <LWindowHeader.h>
#include <UAttachments.h>
#include <LMLTEPane.h>
#include <LTextColumn.h>

#include <LGrowZone.h>
#include <PP_Messages.h>
#include <PP_Resources.h>
#include <UControlRegistry.h>
#include <UDrawingState.h>
#include <UEnvironment.h>
#include <UMemoryMgr.h>
#include <UModalDialogs.h>
#include <UNavServicesDialogs.h>
#include <URegistrar.h>


// Standard headers
#include <string.h>

// Universal headers
#include <AppleHelp.h>

// Globals
CWindowMenu	*		gWindowMenu;	// This is the window menu.

// Static variables
CRezillaPrefs *			CRezillaApp::sPrefs = nil;
CEditorsController *	CRezillaApp::sEditController = nil;
CTemplatesController *	CRezillaApp::sTemplatesController = nil;
CPluginsController *	CRezillaApp::sPluginsController = nil;
Rzil_basics				CRezillaApp::sBasics;
CInspectorWindow *		CRezillaApp::sInspectorWindow = nil;
Str255					CRezillaApp::sVersionNumber;
SInt16					CRezillaApp::sOwnRefNum;
CRecentItemsMenu *		CRezillaApp::sRecentItemsAttachment;
Boolean					CRezillaApp::sReadOnlyNavFlag = false;
Boolean					CRezillaApp::sCalledFromAE = false;


// ===========================================================================
//   Main Program
// ===========================================================================

int main()
{
	SetDebugThrow_(debugAction_Alert);
	SetDebugSignal_(debugAction_Alert);

	InitializeHeap(3);
	UQDGlobals::InitializeToolbox();

	// Outline tables support drag and drop, so it's good to ensure
	// it's present before we go any further
	
	if (!LDropArea::DragAndDropIsPresent()) {
		//::StopAlert(ALRT_NoDragAndDrop, nil);
		::SysBeep(3);
		::ExitToShell();
	}
	
	UEnvironment::InitEnvironment();
	
	new LGrowZone(20000);
	
	CRezillaApp	theApp;
	theApp.Run();
	
	return 0;
}


// ---------------------------------------------------------------------------
//   CRezillaApp
// ---------------------------------------------------------------------------
//	Constructor

CRezillaApp::CRezillaApp()
{	
	bool hasAM = UEnvironment::HasFeature(env_HasAppearance101);
	if ( hasAM ) {
		::RegisterAppearanceClient();
	}

	RegisterClasses();
}


// ---------------------------------------------------------------------------
//     ~CRezillaApp
// ---------------------------------------------------------------------------
//	Destructor

CRezillaApp::~CRezillaApp()
{
	LMLTEPane::Terminate();
	
	// CRezClipboard is deleted with all the attachments
// 	delete CRezClipboard::GetScrapRezFile();
}


// ---------------------------------------------------------------------------
//   Initialize						[protected]
// ---------------------------------------------------------------------------
// In LowMem.h:
//   EXTERN_API( SInt16 ) LMGetCurApRefNum(void);
// 	 EXTERN_API( void ) LMSetCurApRefNum(SInt16 value);

void
CRezillaApp::Initialize()
{
	MenuRef				menuHandle;
	MenuItemIndex		customItemIndex;

	// Cache our own refnum
	UResources::GetCurrentResFile(sOwnRefNum);

	// This must be done early but is used only by the 'utxt' editor
	InitMLTE();
	
	SInt32 theOsVersion = UEnvironment::GetOSVersion();
	// Check that we are running on OSX 10.2 or greater
	if ( theOsVersion < 0x01020) {
		UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("RequireSystemTenTwo"), PPob_SimpleMessage);
		SendAEQuit();
	}
	// Install an item in the Finder's Help menu
	RegisterHelpBook();
	
	// Create an instance of CRezillaPrefs
	sPrefs = new CRezillaPrefs(this);

	// Create an instance of the editors controller. It must come before 
	// the templates controller.
	sEditController = new CEditorsController();
	
	// Create an instance of the templates controller
	sTemplatesController = new CTemplatesController();
	
#ifdef REZILLA_ENABLE_PLUGINS
	// Create an instance of the plugins controller
	sPluginsController = new CPluginsController();
#endif
	
	// Install the window menu.
	InstallWindowMenu();	

	// Create the inspector window
	sInspectorWindow = (CInspectorWindow *)LWindow::CreateWindow(PPob_InspectorWindow, this);
	ThrowIfNil_(sInspectorWindow);
	
	// Add attachments
	AddAttachment( new CRezClipboard );
	
	CWindowMenuAttachment *theAttachment;	// Window menu attachment.
	theAttachment = new CWindowMenuAttachment( gWindowMenu );
	AddAttachment( theAttachment, nil, true );
	
	sRecentItemsAttachment = new CRecentItemsMenu(MENU_RecentItems, 
												  sPrefs->GetPrefValue(kPref_general_maxRecent), 
												  CFSTR(kRezillaIdentifier));
	AddAttachment( sRecentItemsAttachment, nil, true );
	
	VersionFromPlist(sVersionNumber);
	
	mOpeningFork = fork_anyfork;
	
	// Set some defaults from preferences
	sPrefs->UpdateVars();
	
	mCreatingFork = sPrefs->GetPrefValue(kPref_general_newFork);
	
}


// ---------------------------------------------------------------------------
//   InitMLTE													[private]
// ---------------------------------------------------------------------------
// You MUST call LMLTEPane::Initialize() at the beginning of your program

void
CRezillaApp::InitMLTE()
{
	TXNMacOSPreferredFontDescription	defaultFont;
	OSStatus							osStatus = noErr;
	SInt16								fontID;

	GetFNum("\pMonaco",&fontID);

	defaultFont.fontID		= fontID;	
	defaultFont.pointSize	= kTXNDefaultFontSize;
	defaultFont.fontStyle	= kTXNDefaultFontStyle;
	defaultFont.encoding	= kTXNSystemDefaultEncoding;
	
	LMLTEPane::Initialize( MENU_UnicodeFonts, MENU_StartHierMenuID, &defaultFont, 1, 0);
	
	// Remove the Fonts menu from the menu bar
	::MacDeleteMenu(MENU_UnicodeFonts);
	::InvalMenuBar();
}


// ---------------------------------------------------------------------------
//   MakeModelDirector											   [protected]
// ---------------------------------------------------------------------------
//	Create ModelDirector (AppleEvent handle) object for this application

void
CRezillaApp::MakeModelDirector()
{
// 	new CRezillaModel(this);
	new LModelDirector(this);
}


// ---------------------------------------------------------------------------
//   RegisterClasses											[protected]
// ---------------------------------------------------------------------------

void
CRezillaApp::RegisterClasses()
{
	// Register core PowerPlant classes.
	RegisterClass_(LActiveScroller);
	RegisterClass_(LCaption);
	RegisterClass_(LDialogBox);
	RegisterClass_(LEditField);
	RegisterClass_(LIconPane);
	RegisterClass_(LPageController);
	RegisterClass_(LPane);
	RegisterClass_(LPicture);
	RegisterClass_(LPopupButton);
	RegisterClass_(LPushButton);
	RegisterClass_(LRadioGroup);
	RegisterClass_(LRadioGroupView);
	RegisterClass_(LScrollBar);
	RegisterClass_(LScrollerView);
	RegisterClass_(LStaticText);
	RegisterClass_(LStdButton);
	RegisterClass_(LStdPopupMenu);
	RegisterClass_(LStdRadioButton);
	RegisterClass_(LTabGroupView);
	RegisterClass_(LTextEditView);
	RegisterClass_(LUndoer);
	RegisterClass_(LView);
	RegisterClass_(LWindow);
	RegisterClass_(LWindowHeader);
 	RegisterClass_(LBorderAttachment);
	RegisterClass_(LMLTEPane);
	RegisterClass_(LTextColumn);

	// Register Rezilla custom classes.
	RegisterClass_(CAboutWindow);
	RegisterClass_(CAete_EditorWindow);
	RegisterClass_(CBiDataWE);
	RegisterClass_(CBroadcasterTableView);
	RegisterClass_(CColorPane);
	RegisterClass_(CCompResultWindow);
	RegisterClass_(CDoubleClickButton);
	RegisterClass_(CDraggableTargetView);
	RegisterClass_(CDropStaticText);
	RegisterClass_(CDualDataView);
	RegisterClass_(CEditorWindow);
	RegisterClass_(CFlagPopup);
	RegisterClass_(CHexDataSubView);
	RegisterClass_(CHexEditorWindow);
	RegisterClass_(CIcon_EditorView);
	RegisterClass_(CIcon_EditorWindow);
	RegisterClass_(CInspectorWindow);
	RegisterClass_(CKeyboardGlyphBox);
	RegisterClass_(CMENU_EditorTable);
	RegisterClass_(CMENU_EditorWindow);
	RegisterClass_(CPICT_EditorView);
	RegisterClass_(CPICT_EditorWindow);
	RegisterClass_(CPatternPane);
	RegisterClass_(CPatternTargetView);
	RegisterClass_(CPopupEditField);
	RegisterClass_(CRangeEditText);
	RegisterClass_(CRezIconPane);
	RegisterClass_(CRezMapTable);
	RegisterClass_(CRezMapWindow);
	RegisterClass_(CSingleScrollBar);
	RegisterClass_(CStaticEditCombo);
	RegisterClass_(CStaticTextURL);
	RegisterClass_(CSTRx_EditorWindow);
	RegisterClass_(CSuiteSlider);
	RegisterClass_(CSuite_Window);
	RegisterClass_(CTEXT_EditorView);
	RegisterClass_(CTEXT_EditorWindow);
	RegisterClass_(CThreeButtonsBox);
	RegisterClass_(CTmplEditorWindow);
	RegisterClass_(CTxtDataSubView);
	RegisterClass_(CUtxt_EditorView);
	RegisterClass_(CUtxt_EditorWindow);
	RegisterClass_(CWasteEditView);
	RegisterClass_(CWindow_ColorIcon);
	RegisterClass_(CWindow_Cursor);
	RegisterClass_(CWindow_IconFamily);
	RegisterClass_(CWindow_IconSuite);
	RegisterClass_(CWindow_Pattern);
	RegisterClass_(CWindow_PatternSuite);
	RegisterClass_(CWindow_Picture);
// #include "ABalloon.h"

// 	RegisterClass_(ATag);

	// AM always present on Carbon
	UControlRegistry::RegisterAMClasses();
}


// ---------------------------------------------------------------------------
//   StartUp
// ---------------------------------------------------------------------------

void
CRezillaApp::StartUp()
{
// 	ObeyCommand(cmd_New, nil);
}


// ---------------------------------------------------------------------------
//   AttemptQuitSelf
// ---------------------------------------------------------------------------

Boolean
CRezillaApp::AttemptQuitSelf(
	SInt32	/* inSaveOption */)
{
	sPrefs->StorePreferences();
	return true;
}


// ---------------------------------------------------------------------------
//   ObeyCommand
// ---------------------------------------------------------------------------

Boolean
CRezillaApp::ObeyCommand(
	CommandT	inCommand,
	void		*ioParam)
{
	Boolean		cmdHandled = true;
	
	if (inCommand == 1324679167) {
		inCommand = 27;
	} 
	
	switch (inCommand) {
		
		case cmd_New: {	
			FSSpec	theFileSpec;
			bool	replacing;
			if ( DesignateNewMap(theFileSpec, replacing) ) {
				CRezMapDoc * theRezMapDocPtr;
				
				if (replacing) {
					SInt16	theAnswer;
					theAnswer = UMessageDialogs::AskIfFromLocalizable(CFSTR("NewRezMapReplaceExisting"), PPob_AskIfMessage);
					if (theAnswer == answer_Cancel) {
						return false;
					} else {
						theRezMapDocPtr = FetchRezMapDoc(&theFileSpec);
						// Check if a RezMapDoc is already opened for this file and close it
						if (theRezMapDocPtr != nil) {
							theRezMapDocPtr->Close();
						} 
						FSpDelete(&theFileSpec);
					}						
				} 
				// Make a new file object.
				CRezFile * theRezFile = new CRezFile( theFileSpec, kResFileNotOpened, mCreatingFork );
				// Make new resource file on disk
				if (theRezFile && theRezFile->CreateNewFile() == noErr) {
					// Open the resource file.
					theRezFile->OpenFile(fsRdWrPerm);
				}
				theRezMapDocPtr = new CRezMapDoc(this, theRezFile);
				theRezMapDocPtr->SetReadOnly(false);
				// Register to the Recent Items menu
				sRecentItemsAttachment->AddFile(theFileSpec, true);
			}
			break;
		}
		
		case cmd_ShowInspector: {
			sInspectorWindow->Show();
			// Bring the window to the front.
			UDesktop::SelectDeskWindow( sInspectorWindow );
			break;
		}
		
		case cmd_RezCompare: {
			CRezCompare * theComparator = new CRezCompare(this);
			ThrowIfNil_(theComparator);
			if (theComparator->RunRezCompareDialog() == noErr) {
				if (theComparator->HasDifferences()) {
					theComparator->DisplayResults();
				} else {
					UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("RezMapsDoNotDiffer"), PPob_SimpleMessage);
					// Here we must delete because no result window has
					// been displayed (otherwise the comparator is deleted
					// when the window is closed).
					delete theComparator;
				}
			} 
			break;
		}
		
		case cmd_Open: {	
			FSSpec theFileSpec;
			OSErr error;
			if ( ChooseAFile(theFileSpec) ) {
				error = OpenFork(theFileSpec, true, false);
				if (error != noErr) {
					ReportOpenForkError(error, &theFileSpec);
				} else {
					// Register to the Recent Items menu
					sRecentItemsAttachment->AddFile(theFileSpec, true);
				}
			}
			break;
		}
		
		default: {
			cmdHandled = LApplication::ObeyCommand(inCommand, ioParam);
			break;
		}
	}
	
	return cmdHandled;
}


// ---------------------------------------------------------------------------
//   FindCommandStatus
// ---------------------------------------------------------------------------

void
CRezillaApp::FindCommandStatus(
	CommandT	inCommand,
	Boolean		&outEnabled,
	Boolean		&outUsesMark,
	UInt16		&outMark,
	Str255		outName)
{
	switch (inCommand) {
	
		case cmd_New:
		case cmd_Open:
		case cmd_ShowInspector:
		case cmd_RezCompare:
		case cmd_Preferences:
			outEnabled = true;
			break;		
		
		case cmd_Revert:
		case cmd_ExportMap:
		case cmd_FindNext:
		case cmd_NewRez:
		case cmd_EditRez:
		case cmd_EditRezAsType:
		case cmd_TmplEditRez:
		case cmd_HexEditRez:
		case cmd_GetRezInfo:
		case cmd_RemoveRez:
		case cmd_DuplicateRez:
			outEnabled = false;
			break;		
		
		case cmd_Find:
			LString::CopyPStr( "\pFindÉ", outName);
			outEnabled = false;
			break;		
		
		case cmd_RecentItems:
			outEnabled = ( sRecentItemsAttachment->CountItems() > 0);
			break;		
		
		default:
		{
			LApplication::FindCommandStatus(inCommand, outEnabled,
												outUsesMark, outMark, outName);
			break;
		}
	}
}


// ---------------------------------------------------------------------------
//   ListenToMessage												[public]
// ---------------------------------------------------------------------------

void
CRezillaApp::ListenToMessage( MessageT inMessage, void *ioParam ) 
{
#pragma unused(inMessage, ioParam )
}


// ---------------------------------------------------------------------------
//   ShowAboutBox													  [public]
// ---------------------------------------------------------------------------
//	Display the About Box for the Application

void
CRezillaApp::ShowAboutBox()
{
	CAboutWindow * aboutWindow = dynamic_cast<CAboutWindow *>(LWindow::CreateWindow( PPob_AboutWindow, this ));
	Assert_( aboutWindow != nil );
	
	aboutWindow->Show();
	SwitchTarget(aboutWindow);
// 	UDesktop::SelectDeskWindow(aboutWindow);
}


// ---------------------------------------------------------------------------
//   InstallWindowMenu								[protected]
// ---------------------------------------------------------------------------

void
CRezillaApp::InstallWindowMenu()
{
	Str31 menuName = "\p12345";		
	Handle theIconSuite = nil;

	OSErr result = -1;
	result = GetIconSuite(&theIconSuite, Icon_WindowsMenu, kSelectorAllAvailableData);
	if (theIconSuite == nil)
		SignalPStr_("\pWindowMenuIcons.rsrc not included in project!");

	if (!result && theIconSuite)
	{
		HLock(theIconSuite);
		menuName[0] = 5;
		menuName[1] = 1;
		// icon handle goes in bytes 2-5.
		BlockMoveData(&theIconSuite, &menuName[2], 4);
	} else {
		SignalCStr_("Warning: Unable to load script icon.");
		LString::CopyPStr("\pWindows", menuName);
	}
	
	gWindowMenu = new CWindowMenu( MENU_OpenedWindows, menuName );
	ThrowIfNil_( gWindowMenu );
	
	// Insert permanent items
	LStr255 theItem(STRx_RzilWinMenuItem, index_WinMenuInspector);
	gWindowMenu->InsertCommand(theItem, cmd_ShowInspector, 1);
	gWindowMenu->EnableItem(1);
	::SetMenuItemCommandKey(gWindowMenu->GetMacMenuH(), 1, 0, 48);

	// Install the window menu in the menu bar
	LMenuBar * theMBar = LMenuBar::GetCurrentMenuBar();
	ThrowIfNil_( theMBar );
	theMBar->InstallMenu( gWindowMenu, 0 );
}


// ---------------------------------------------------------------------------
//   RegisterHelpBook											[private]
// ---------------------------------------------------------------------------
// Under Carbon and OSX, register a Help folder
// 
OSStatus
CRezillaApp::RegisterHelpBook()
{
  CFBundleRef 	myAppsBundle;
  CFURLRef 		myBundleURL;
  FSRef 		myBundleRef;
  OSStatus  	err = noErr;
  
  myAppsBundle = NULL;
  myBundleURL  = NULL;

  myAppsBundle = CFBundleGetMainBundle();
  if (myAppsBundle == NULL) {err = fnfErr; goto bail;}
  
  myBundleURL = CFBundleCopyBundleURL(myAppsBundle);
  if (myBundleURL == NULL) {err = fnfErr; goto bail;}
  
  if (! CFURLGetFSRef(myBundleURL, &myBundleRef)) { err = fnfErr; goto bail;}
  
  err = AHRegisterHelpBook(&myBundleRef);
  if (err != noErr) goto bail;
  
  CFRelease(myBundleURL);
  return noErr;
  
bail:
    if (myBundleURL != NULL) CFRelease(myBundleURL);
    return err;
}


// ---------------------------------------------------------------------------
//   VersionFromResource										  [public]
// ---------------------------------------------------------------------------
// Retrieve the version number from the 'vers' resources.

LStr255
CRezillaApp::VersionFromResource()
{
	UInt32 theVersion;
	UInt8	ver1, ver2, ver3, ver4, ver5;
	Str255	tempString;
	LStr255	theString( "\p" );
	
	// Find the version info in the 'vers' resource
	StResource	versH( 'vers', 1, true, true );
	if ( versH ) {
		theVersion = *((UInt32 *)(*((Handle)versH)));
		ver1 = ((UInt8 *)&theVersion)[0];
		ver1 = (((ver1 & 0xF0 ) >> 4) * 10) + (ver1 & 0x0F);
		ver2 = (((UInt8 *)&theVersion)[1] & 0xF0) >> 4;
		ver3 = (((UInt8 *)&theVersion)[1] & 0x0F);
		ver4 = ((UInt8 *)&theVersion)[2];
		ver5 = ((UInt8 *)&theVersion)[3];
		::NumToString((long) ver1, tempString);
		theString += tempString ;
		::NumToString((long) ver2, tempString);
		theString += "\p." ;
		theString += tempString ;
		if (ver3) {
			::NumToString((long) ver3, tempString);
			theString += "\p." ;
			theString += tempString ;
		}
		switch (ver4) {
		  case 0x20:
			theString += "\pd" ;
			break;
			
		  case 0x40:
		  theString += "\pa" ;
			break;
			
		  case 0x60:
		  theString += "\pb" ;
			break;
			
		  default:
			break;
		}
		if (ver5) {
			::NumToString((long) ver5, tempString);
			theString += tempString ;
		}
	}
	return  theString;
}


// ---------------------------------------------------------------------------
//   VersionFromPlist										  [public]
// ---------------------------------------------------------------------------
// Retrieve the version number from the 'Info.plist' file.

void
CRezillaApp::VersionFromPlist(Str255 & outVersion)
{
	OSErr		error = noErr;
	CFStringRef	text;
	CFBundleRef	appBundle;
	LStr255		theString( "\p" );
	
	appBundle = ::CFBundleGetMainBundle();
	text = (CFStringRef) ::CFBundleGetValueForInfoDictionaryKey( appBundle, CFSTR("CFBundleVersion") );           
	
	if ( (text == CFSTR(" ")) || (text == NULL) ) {
		text = CFSTR("n/a");
	}
	
	error = ::CFStringGetPascalString(text, outVersion, sizeof(outVersion), NULL);
}


// ---------------------------------------------------------------------------
//   ChooseAFile								[public static]
// ---------------------------------------------------------------------------

Boolean
CRezillaApp::ChooseAFile(FSSpec & outFileSpec)
{
	LFileTypeList fileTypes(fileTypes_All);
	bool	openOK = false;
	struct Rzil_OpenFileUD	theUserData;
	
	theUserData.whichFork = fork_anyfork;
	theUserData.isReadOnly = false;

	// Deactivate the desktop.
	::UDesktop::Deactivate();
	
	// Browse for a document.
	UNavigationDialogs::CNavFileChooser chooser;
	chooser.SetEventFilterProc(Rzil_OpenNavEventFilterUPP);
	chooser.SetOptionFlags(kNavNoTypePopup 
						   + kNavDontAutoTranslate
						   + kNavSupportPackages
						   + kNavAllowOpenPackages);

	chooser.SetUserData( (void *) &theUserData);
	
	openOK = chooser.AskOpenFile(fileTypes);

	if (openOK) {
		chooser.GetFileSpec(1, outFileSpec);
		mOpeningFork = theUserData.whichFork;
		sReadOnlyNavFlag = theUserData.isReadOnly;
	}

    // Activate the desktop.
    ::UDesktop::Activate();

	return openOK;
}


// ---------------------------------------------------------------------------
//   OpenDocument													  [public]
// ---------------------------------------------------------------------------
//	Open a Document specified by an FSSpec. This is used by SendAEOpenDoc()
//	which is invoked when an item is selected in the RecentItems menu.

void
CRezillaApp::OpenDocument(
	FSSpec* inFSSpec)
{
	sReadOnlyNavFlag = false;
	OpenFork(*inFSSpec);
}


// ---------------------------------------------------------------------------
//   OpenFork								[public static]
// ---------------------------------------------------------------------------

OSErr
CRezillaApp::OpenFork(FSSpec & inFileSpec, 
					  Boolean askChangePerm,
					  Boolean inhibitCreate)
{
	SInt16 theFork;
	short theRefNum;
	OSErr error = noErr;
	
	// Check if a RezMapDoc is already opened for this file
	CRezMapDoc * theRezMapDocPtr = FetchRezMapDoc(&inFileSpec);
	if (theRezMapDocPtr != nil) {
		theRezMapDocPtr->GetRezMapWindow()->Select();
		return error;
	} 
	
	error = PreOpen(inFileSpec, theFork, theRefNum, mOpeningFork, askChangePerm, inhibitCreate);
	if ( error == noErr || error == err_OpenSucceededReadOnly) {
		theRezMapDocPtr = new CRezMapDoc(this, &inFileSpec, theFork, theRefNum);
		if (error == err_OpenSucceededReadOnly) {
			sReadOnlyNavFlag = false;
			theRezMapDocPtr->SetReadOnly(true);
			error = noErr;
		} else {
			theRezMapDocPtr->SetReadOnly(sReadOnlyNavFlag);
		}
		theRezMapDocPtr->GetRezMapWindow()->InstallReadOnlyIcon();
	} 
	
	return error;
}


// ---------------------------------------------------------------------------
//   PreOpen												[public static]
// ---------------------------------------------------------------------------

OSErr
CRezillaApp::PreOpen(FSSpec & inFileSpec, 
					 SInt16 & outFork, 
					 short & outRefnum, 
					 SInt16 inWantedFork, 
					 Boolean askChangePerm,
					 Boolean inhibitCreate)
{
	OSErr		error;
	FSRef		theFileRef;
	
	StRezRefSaver saver( ::CurResFile() );
		
	if (inWantedFork != fork_rezfork) {
		// Try to open the file as a datafork resource file
		error = FSpMakeFSRef( &inFileSpec, &theFileRef );
		SetResLoad( false );
		error = FSOpenResourceFile( &theFileRef, 0, nil, sReadOnlyNavFlag ? fsRdPerm : fsRdWrPerm, &outRefnum );
		SetResLoad( true );
		
		if (error == noErr) {
			outFork = fork_datafork;
			goto done;
		} else if (error == mapReadErr || error == eofErr) {
			if (inWantedFork == fork_datafork) {
				// If this failed with mapReadErr or eofErr, the file has no resource 
				// map in data fork or it is empty
				error = err_NoRezInDataFork;
				goto done;			
			} 
		} else {
				goto done;			
		}
	} 
	
	if (inWantedFork != fork_datafork) {
		// If this failed (mapReadErr), try to open as a resourcefork resource file
		SetResLoad( false );
		outRefnum = FSpOpenResFile( &inFileSpec, sReadOnlyNavFlag ? fsRdPerm : fsRdWrPerm);
		error = ::ResError();
		SetResLoad( true );
		if (error == noErr) {
			outFork = fork_rezfork;
		} else if (error == mapReadErr || error == eofErr) {
			// If this failed with mapReadErr or eofErr, the file has no resource 
			// map in resource fork or it is empty
			if (inWantedFork == fork_anyfork) {
				Boolean createFork = ! inhibitCreate;
				// Ask to create a fork
				if (! sCalledFromAE && ! inhibitCreate) {
					if (UMessageDialogs::AskIfWithString(CFSTR("NoRezForkAskCreate"), inFileSpec.name) == answer_Do) {
						createFork = true;
					} else {
						return userCanceledErr;
					}				
				} 
				if (createFork) {
					// Create a resource fork
					error = CreateForkForFile(inFileSpec);
					if (error == noErr) {
						// Try to open it: this time the inhibitCreate
						// argument is set to true.
						error = PreOpen(inFileSpec, outFork, outRefnum, fork_rezfork, true);
					} else {
						error = err_CreateForkForFileFailed;
					}
				} else {
					error = err_NoRezInAnyFork;
				}
			} else {
				error = err_NoRezInRezFork;
			}
		} 
	} 
	
done:
	// Opening a file on a locked media sometimes raises permErr instead 
	// of wrPermErr
	if ((error == wrPermErr || error == permErr) && sReadOnlyNavFlag == false && ! sCalledFromAE) {
		// If opening failed with write permission, ask to try again in
		// read-only access
		if (!askChangePerm || UMessageDialogs::AskIfFromLocalizable(CFSTR("WritePermissionError"), PPob_AskIfMessage) == answer_Do) {
			sReadOnlyNavFlag = true;
			error = PreOpen(inFileSpec, outFork, outRefnum, inWantedFork);
			if (error == noErr) {
				error = err_OpenSucceededReadOnly;
			} 
		} 
	} 
	
	return error;
}


// ---------------------------------------------------------------------------
//   CreateForkForFile									[public static]
// ---------------------------------------------------------------------------

OSErr
CRezillaApp::CreateForkForFile(FSSpec & inFileSpec)
{
	OSType	fileCreator = 0, fileType = 0;
	
	// Find the type and creator of the file
	HFileInfo fpb;
	fpb.ioVRefNum = inFileSpec.vRefNum;
	fpb.ioDirID = inFileSpec.parID;
	fpb.ioNamePtr = inFileSpec.name;
	fpb.ioFVersNum = 0;
	fpb.ioFDirIndex = 0;

	if ( ::PBGetCatInfoSync((CInfoPBPtr)&fpb) == noErr) {
		fileCreator = fpb.ioFlFndrInfo.fdCreator;
		fileType = fpb.ioFlFndrInfo.fdType;
	} 

	// Create a resource file
	// ScriptCode smRoman = 0
	::FSpCreateResFile (& inFileSpec, fileCreator, fileType, ::GetApplicationScript());

	return ::ResError();
}


// ---------------------------------------------------------------------------
//   ReportOpenForkError								[public static]
// ---------------------------------------------------------------------------

void
CRezillaApp::ReportOpenForkError(OSErr inError, FSSpec * inFileSpecPtr)
{
	switch (inError) {
		case err_NoRezInDataFork:
		UMessageDialogs::AlertWithString(CFSTR("NoRezInDataFork"), inFileSpecPtr->name);
		break;
		
		case err_NoRezInRezFork:
		UMessageDialogs::AlertWithString(CFSTR("NoRezInRezFork"), inFileSpecPtr->name);
		break;
		
		case err_NoRezInAnyFork:
		UMessageDialogs::AlertWithString(CFSTR("NoRezInAnyFork"), inFileSpecPtr->name);
		break;
		
		case opWrErr:
		UMessageDialogs::AlertWithString(CFSTR("NoOpenWritePermission"), inFileSpecPtr->name);
		break;
		
		case permErr:
		UMessageDialogs::AlertWithString(CFSTR("PermissionError"), inFileSpecPtr->name);
		break;
		
		case wrPermErr:
		// This error has already been intercepted in PreOpen()
		return;
		
		case userCanceledErr:
		// Do nothing
		return;
		
		default: 
		UMessageDialogs::AlertWithValue(CFSTR("SystemError"), inError);
		return;
	}
}


// ---------------------------------------------------------------------------
//   DesignateNewMap								[public static]
// ---------------------------------------------------------------------------

Boolean
CRezillaApp::DesignateNewMap( FSSpec& outFileSpec, bool & outReplacing)
{
	LFileTypeList fileTypes(fileTypes_All);
	bool	openOK = false;
	Str255	theString;
		
	mCreatingFork = sPrefs->GetPrefValue(kPref_general_newFork);
	
	// Deactivate the desktop.
	::UDesktop::Deactivate();
	
	// Browse for a document
	UNavigationDialogs::CNavFileDesignator designator;
	
	// File designator setup
	designator.SetEventFilterProc(Rzil_NewMapNavEventFilterUPP);
	designator.SetOptionFlags(kNavNoTypePopup + kNavDontAutoTranslate);
	designator.SetUserData( (void *) &mCreatingFork);

	// Retrieve strings from STR# resource
	GetIndString(theString, STRx_NavStrings, index_RezillaAppName);
	designator.SetClientName(theString);
	GetIndString(theString, STRx_NavStrings, index_CreateNewRezMap);
	designator.SetMessage(theString);
	GetIndString(theString, STRx_NavStrings, index_CreateUntitled);
	designator.SetSavedFileName(theString);
	
	openOK = designator.AskDesignateFile();

	if (openOK) {
		designator.GetFileSpec(outFileSpec);
		outReplacing = designator.IsReplacing();
	}

    // Activate the desktop.
    ::UDesktop::Activate();

	return openOK;
}


// ---------------------------------------------------------------------------
//   FetchRezMapDoc												  [static]
// ---------------------------------------------------------------------------
//	Returns nil if no RezMapDoc exists corresponding to the given FSSpec

CRezMapDoc*
CRezillaApp::FetchRezMapDoc(FSSpec * inFileSpecPtr)
{
	CRezMapDoc*	result = nil;
	
	if (inFileSpecPtr != nil) {
		TArrayIterator<CRezMapDoc *>	iterator( CRezMapDoc::GetRezMapDocList() );
		FSSpec 		theFileSpec;
		CRezMapDoc*	theRezMapDoc = nil;
		
		// CRezillaApp class maintains a list of all CRezMapDoc's that we created
		while (iterator.Next(theRezMapDoc)) {
			theRezMapDoc->GetRezFile()->GetSpecifier(theFileSpec);
			if ( LFile::EqualFileSpec(theFileSpec, *inFileSpecPtr) ) {
				result = theRezMapDoc;
				break;
			} 
		}
	} 
	
	return result;
}


// ---------------------------------------------------------------------------
//   DoPreferences												   [protected]
// ---------------------------------------------------------------------------
//	Handle Preferences settings

void
CRezillaApp::DoPreferences()
{
	sPrefs->RunPrefsDialog();
}



