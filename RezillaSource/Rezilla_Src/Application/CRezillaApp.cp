// ===========================================================================
// CRezillaApp.cp					
//                       Created: 2003-04-16 22:13:54
//             Last modification: 2004-08-07 12:51:23
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2003-2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#include "CRezillaApp.h"
#include "CRezillaPrefs.h"
#include "CRezTypesController.h"
#include "CRezEditor.h"
#include "CTEXT_EditorWindow.h"
#include "CEditTable.h"
#include "CRezMapDoc.h"
#include "CRezMap.h"
#include "CRezFile.h"
#include "CRezMapTable.h"
#include "CRezMapWindow.h"
#include "CRezCompare.h"
#include "CRezClipboard.h"
#include "CWindowMenu.h"
#include "CRecentItemsMenu.h"
#include "CInspectorWindow.h"
#include "CHexEditorWindow.h"
#include "CTmplEditorWindow.h"
#include "CTEXT_EditorView.h"
#include "CWasteEditView.h"
#include "CBiDataWE.h"
#include "CDualDataView.h"
#include "CHexDataSubView.h"
#include "CTxtDataSubView.h"
#include "CDropStaticText.h"
#include "CBroadcasterTableView.h"
#include "CSingleScrollBar.h"
#include "CRezIconPane.h"
#include "CCompResultWindow.h"
#include "CRangeEditText.h"
#include "CStaticTextURL.h"
#include "CAete_EditorWindow.h"
#include "CCategoriesListBox.h"
#include "CTmplBevelButton.h"
#include "UNavigationDialogs.h"
#include "NavServicesCallbacks.h"
#include "UMessageDialogs.h"
#include "UDialogBoxHandler.h"
// #include "ABalloon.h"

// PP Classes for registration
#include <Appearance.h>
#include <LAMControlImp.h>
#include <LAMPopupButtonImp.h>
#include <LAMPushButtonImp.h>
#include <LAMTrackActionImp.h>
#include <LActiveScroller.h>
#include <LCaption.h>
#include <LClipboard.h>
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
CRezEditor *			CRezillaApp::sEditController = nil;
CRezTypesController *	CRezillaApp::sTypesController = nil;
Rzil_basics				CRezillaApp::sBasics;
CInspectorWindow *		CRezillaApp::sInspectorWindow = nil;
const LStr255			CRezillaApp::sVersionNumber( VersionFromPlist() );
SInt16					CRezillaApp::sOwnRefNum;
TArray<CRezMapDoc *>	CRezillaApp::sRezMapDocList;
CRecentItemsMenu *		CRezillaApp::sRecentItemsAttachment;
Boolean					CRezillaApp::sReadOnlyNavFlag = false;


// ===========================================================================
//  ¥ Main Program
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
//  ¥ CRezillaApp
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
//  ¥ ~CRezillaApp
// ---------------------------------------------------------------------------
//	Destructor

CRezillaApp::~CRezillaApp()
{
	// CRezClipboard is deleted with all the attachments
// 	delete CRezClipboard::GetScrapRezFile();
}


// ---------------------------------------------------------------------------
//	¥ Initialize						[protected]
// ---------------------------------------------------------------------------
//	Last chance to initialize the application before processing events

void
CRezillaApp::Initialize()
{
	OSStatus			err;
	MenuRef				menuHandle;
	MenuItemIndex		customItemIndex;

	UResources::GetCurrentResFile(sOwnRefNum);

	SInt32 theOsVersion = UEnvironment::GetOSVersion();
	// Check that we are running on OS9 or greater
#if TARGET_RT_MAC_MACHO
	if ( theOsVersion < 0x01000) {
		UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("RequireSystemTen"), rPPob_SimpleMessage);
		SendAEQuit();
	}
#else
	if ( theOsVersion < 0x00900) {
		UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("RequireSystemNine"), rPPob_SimpleMessage);
		SendAEQuit();
	}	
#endif
	// Install an item in the Finder's Help menu
	err	= RegisterHelpBook();
	if ( err == noErr )									
	{
		//	Add custom Help Menu items
		err	= ::HMGetHelpMenu( &menuHandle, &customItemIndex );
		if ( err == noErr ) {
			// MacOS 8/9 bundled applications must manually add and handle their help menu
			if ( theOsVersion < 0x0920)	{
				InsertMenuItem( menuHandle, "\pRezilla Help", customItemIndex - 1 );
			}
		}
	}
	
	// Create the about window
	MakeAboutWindow();
	
	// Create an instance of CRezillaPrefs
	sPrefs = new CRezillaPrefs(this);

	// Create an instance of the editors controller
	sEditController = new CRezEditor();
	
	// Create an instance of the templates controller
	sTypesController = new CRezTypesController();
	
	// Install the window menu.
	InstallWindowMenu();	

	// Create the inspector window
	sInspectorWindow = (CInspectorWindow *)LWindow::CreateWindow(rPPob_InspectorWindow, this);
	ThrowIfNil_(sInspectorWindow);
	
	// Add attachments
	AddAttachment( new CRezClipboard );
	
	CWindowMenuAttachment *theAttachment;	// Window menu attachment.
	theAttachment = new CWindowMenuAttachment( gWindowMenu );
	AddAttachment( theAttachment, nil, true );
	
	sRecentItemsAttachment = new CRecentItemsMenu(rMENU_RecentItems, kRzilMaxRecentItems, CFSTR(kRezillaIdentifier));
	AddAttachment( sRecentItemsAttachment, nil, true );
	
// 	// Help tags settings
// 	ABalloonBase::EnableControlKeyPop();
// 	ABalloonBase::SetAutoPopDelay(20);

	mOpeningFork = fork_anyfork;
	
	// Set some defaults from preferences
	sPrefs->UpdateVars();
	
	mCreatingFork = sPrefs->GetPrefValue(kPref_general_newFork);
}


// ---------------------------------------------------------------------------
//	¥ RegisterClasses								[protected]
// ---------------------------------------------------------------------------
//	To reduce clutter within the Application object's constructor, class
//	registrations appear here in this seperate function for ease of use.

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

	// Register Rezilla custom classes.
// 	RegisterClass_(CAete_EditorWindow);
	RegisterClass_(CBiDataWE);
	RegisterClass_(CBroadcasterTableView);
	RegisterClass_(CCategoriesListBox);
	RegisterClass_(CCompResultWindow);
	RegisterClass_(CDropStaticText);
	RegisterClass_(CDualDataView);
	RegisterClass_(CEditTable);
	RegisterClass_(CEditorWindow);
	RegisterClass_(CHexDataSubView);
	RegisterClass_(CHexEditorWindow);
	RegisterClass_(CInspectorWindow);
	RegisterClass_(CRangeEditText);
	RegisterClass_(CRezIconPane);
	RegisterClass_(CRezMapTable);
	RegisterClass_(CRezMapWindow);
	RegisterClass_(CSingleScrollBar);
	RegisterClass_(CStaticTextURL);
	RegisterClass_(CTEXT_EditorView);
	RegisterClass_(CTEXT_EditorWindow);
	RegisterClass_(CTmplEditorWindow);
	RegisterClass_(CTmplBevelButton);
	RegisterClass_(CTxtDataSubView);
	RegisterClass_(CWasteEditView);

// 	RegisterClass_(ATag);

	// AM always present on Carbon
	UControlRegistry::RegisterAMClasses();
}


// ---------------------------------------------------------------------------
//  ¥ StartUp
// ---------------------------------------------------------------------------

void
CRezillaApp::StartUp()
{
// 	ObeyCommand(cmd_New, nil);
}


// ---------------------------------------------------------------------------
//	¥ AttemptQuitSelf
// ---------------------------------------------------------------------------

Boolean
CRezillaApp::AttemptQuitSelf(
	SInt32	/* inSaveOption */)
{
	sPrefs->StorePreferences();
	return true;
}


// ---------------------------------------------------------------------------
//  ¥ ObeyCommand
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
					theAnswer = UMessageDialogs::AskIfFromLocalizable(CFSTR("NewRezMapReplaceExisting"), rPPob_AskIfMessage);
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
				if (theRezFile->CreateNewFile() == noErr) {
					// Open the resource file.
					theRezFile->OpenFile(fsRdWrPerm);
				}
				theRezMapDocPtr = new CRezMapDoc(this, theRezFile);
				theRezMapDocPtr->SetReadOnly(false);
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
					UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("RezMapsDoNotDiffer"), rPPob_SimpleMessage);
				}
			} 
// 			delete theComparator;
			break;
		}
		
		case cmd_Open: {	
			FSSpec theFileSpec;
			OSErr error;
			if ( ChooseAFile(theFileSpec) ) {
				error = OpenFork(theFileSpec);
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
//  ¥ FindCommandStatus
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
//  ¥ ListenToMessage												[public]
// ---------------------------------------------------------------------------

void
CRezillaApp::ListenToMessage( MessageT inMessage, void *ioParam ) 
{
#pragma unused( ioParam )
	
	switch (inMessage) {
		
		case msg_AboutOkButton:
		mAboutWindow->Hide();		
		break;
		
		case msg_AboutLicenceButton:
		mAboutWindow->Hide();		
		WindowPtr theWinPtr = UWindows::FindNamedWindow("\pRezilla Licence");
		if (!theWinPtr) {
			LWindow* theWindow = LWindow::CreateWindow( rPPob_LicenceWindow, this );
			ThrowIfNil_(theWindow);
			theWinPtr = theWindow->GetMacWindow();
		} 
		::SelectWindow(theWinPtr);
		break;
	}
}


// ---------------------------------------------------------------------------
//	¥ MakeAboutBox													  [public]
// ---------------------------------------------------------------------------

void
CRezillaApp::MakeAboutWindow()
{	
	Str255	theString;
	LStaticText *theCaption;	
	CStaticTextURL *theUrlCaption;	

	mAboutWindow = (LDialogBox *)(LWindow::CreateWindow( rPPob_AboutWindow, this ));
	ThrowIfNil_(mAboutWindow);
	
	// Write the version number in the caption
	theCaption = dynamic_cast<LStaticText *>(mAboutWindow->FindPaneByID( item_AboutVersCaption ));
	theCaption->SetDescriptor(sVersionNumber);

	// Write the URLs
	for (UInt8 i = 0; i < 6; i++) {
		theUrlCaption = dynamic_cast<CStaticTextURL *>(mAboutWindow->FindPaneByID( item_AboutUrlsBase + i ));
	
		// Retrieve strings from STR# resource
		::GetIndString(theString, STRx_InternetUrls, 2*i+1);
		theUrlCaption->SetDescriptor(theString);
		
		::GetIndString(theString, STRx_InternetUrls, 2*i+2);
		theUrlCaption->SetUrlString(theString);
	}
	
	UReanimator::LinkListenerToControls( this, mAboutWindow, rRidL_AboutWindow );
}


// ---------------------------------------------------------------------------
//	¥ ShowAboutBox													  [public]
// ---------------------------------------------------------------------------
//	Display the About Box for the Application

void
CRezillaApp::ShowAboutBox()
{
	mAboutWindow->Show();
	UDesktop::SelectDeskWindow(mAboutWindow);
}


// ---------------------------------------------------------------------------
//	¥ InstallWindowMenu								[protected]
// ---------------------------------------------------------------------------

void
CRezillaApp::InstallWindowMenu()
{
	Str31 menuName = "\p12345";		
	Handle theIconSuite = nil;

	OSErr result = -1;
	if (UEnvironment::GetOSVersion() >= 0x070)
	{
		result = GetIconSuite(&theIconSuite, ICN_WindowMenu, kSelectorAllAvailableData);
		if (theIconSuite == nil)
			SignalPStr_("\pMenuIcons.rsrc not included in project!");
	}	
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
	
	gWindowMenu = new CWindowMenu( rMENU_Window, menuName );
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
//	¥ RegisterHelpBook											[private]
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
//	¥ VersionFromResource										  [public]
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
//	¥ VersionFromPlist										  [public]
// ---------------------------------------------------------------------------
// Retrieve the version number from the 'Info.plist' file.

LStr255
CRezillaApp::VersionFromPlist()
{
	OSErr		error = noErr;
	CFStringRef	text;
	CFBundleRef	appBundle;
	Str255		theVers;
	LStr255		theString( "\p" );
	
	appBundle = CFBundleGetMainBundle();
	text = (CFStringRef) CFBundleGetValueForInfoDictionaryKey( appBundle, CFSTR("CFBundleVersion") );           
	
	if ( (text == CFSTR(" ")) || (text == NULL) ) {
		text = CFSTR("n/a");
	}
	
	if ( CFStringGetPascalString(text, theVers, sizeof(theVers), NULL) ) {
		theString += theVers;
	}
	
	return theString;
}


// ---------------------------------------------------------------------------
//	¥ ChooseAFile								[public static]
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
//	¥ ChooseAFile								[public static]
// ---------------------------------------------------------------------------

Boolean
CRezillaApp::ChooseAFile(const LFileTypeList & inFileTypes, FSSpec & fileSpec)
{
	bool	openOK = false;
	
	// Deactivate the desktop.
	::UDesktop::Deactivate();
	
	// Browse for a document.
	UNavServicesDialogs::LFileChooser	chooser;
	
	openOK = chooser.AskChooseOneFile(inFileTypes, fileSpec);

    // Activate the desktop.
    ::UDesktop::Activate();

	return openOK;
}


// ---------------------------------------------------------------------------
//	¥ OpenDocument													  [public]
// ---------------------------------------------------------------------------
//	Open a Document specified by an FSSpec

void
CRezillaApp::OpenDocument(
	FSSpec* inFSSpec)
{
	sReadOnlyNavFlag = false;
	OpenFork(*inFSSpec);
}


// ---------------------------------------------------------------------------
//	¥ OpenFork								[public static]
// ---------------------------------------------------------------------------

OSErr
CRezillaApp::OpenFork(FSSpec & inFileSpec)
{
	SInt16 theFork;
	short theRefNum;
	OSErr error;
	
	// Check if a RezMapDoc is already opened for this file
	CRezMapDoc * theRezMapDocPtr = FetchRezMapDoc(&inFileSpec);
	if (theRezMapDocPtr != nil) {
		theRezMapDocPtr->GetRezMapWindow()->Select();
		return true;
	} 
	
	error = PreOpen(inFileSpec, theFork, theRefNum, mOpeningFork);
	if ( error == noErr ) {
		theRezMapDocPtr = new CRezMapDoc(this, &inFileSpec, theFork, theRefNum);
		theRezMapDocPtr->SetReadOnly(sReadOnlyNavFlag);
		theRezMapDocPtr->GetRezMapWindow()->InstallReadOnlyIcon();
	} 
	
	return error;
}


// ---------------------------------------------------------------------------
//	¥ PreOpen								[public static]
// ---------------------------------------------------------------------------

OSErr
CRezillaApp::PreOpen(FSSpec & inFileSpec, SInt16 & outFork, short & outRefnum, SInt16 inWantedFork)
{
	OSErr		error;
	FSRef		inFileRef;
	
	StRezReferenceSaver saver( ::CurResFile() );
		
	if (inWantedFork != fork_rezfork) {
		// Try to open the file as a datafork resource file
		error = FSpMakeFSRef( &inFileSpec, &inFileRef );
		SetResLoad( false );
		error = FSOpenResourceFile( &inFileRef, 0, nil, sReadOnlyNavFlag ? fsRdPerm : fsRdWrPerm, &outRefnum );
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
				error = err_NoRezInAnyFork;
			} else {
				error = err_NoRezInRezFork;
			}
		} 
	} 
	
done:
	return error;
}


// ---------------------------------------------------------------------------
//	¥ ReportOpenForkError								[public static]
// ---------------------------------------------------------------------------

void
CRezillaApp::ReportOpenForkError(OSErr inError, FSSpec * inFileSpecPtr)
{
	char * theCStr = new char[255];
	CFStringRef formatStr = NULL, messageStr = NULL;

	CopyPascalStringToC(inFileSpecPtr->name,theCStr);

	switch (inError) {
	  case err_NoRezInDataFork:
		formatStr = CFCopyLocalizedString(CFSTR("NoRezInDataFork"), NULL);
		break;
		
	  case err_NoRezInRezFork:
		formatStr = CFCopyLocalizedString(CFSTR("NoRezInRezFork"), NULL);
		break;
		
	  case err_NoRezInAnyFork:
		formatStr = CFCopyLocalizedString(CFSTR("NoRezInAnyFork"), NULL);
		break;
		
	  case opWrErr:
		formatStr = CFCopyLocalizedString(CFSTR("NoOpenWritePermission"), NULL);
		UMessageDialogs::ErrorMessageFromLocalizable(CFSTR("SystemError"), inError, rPPob_SimpleMessage);
		break;
		
	  case permErr:
		formatStr = CFCopyLocalizedString(CFSTR("PermissionError"), NULL);
		break;
		
	  default:
		UMessageDialogs::ErrorMessageFromLocalizable(CFSTR("SystemError"), inError, rPPob_SimpleMessage);
		return;
	}
	
	if (formatStr != NULL) {
		messageStr = CFStringCreateWithFormat(NULL, NULL, formatStr, theCStr);
		if (messageStr != NULL)
		{
			UMessageDialogs::SimpleMessageFromLocalizable(messageStr, rPPob_SimpleMessage);
			CFRelease(messageStr);                     
		}
		CFRelease(formatStr);                             
	}
}


// ---------------------------------------------------------------------------
//	¥ DesignateNewMap								[public static]
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
//	¥ FetchRezMapDoc												  [static]
// ---------------------------------------------------------------------------
//	Returns nil if no RezMapDoc exists corresponding to the given FSSpec

CRezMapDoc*
CRezillaApp::FetchRezMapDoc(FSSpec * inFileSpecPtr)
{
	CRezMapDoc*	result = nil;
	
	if (inFileSpecPtr != nil) {
		TArrayIterator<CRezMapDoc *>	iterator(sRezMapDocList);
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
//	¥ HandleAppleEvent												  [public]
// ---------------------------------------------------------------------------

void
CRezillaApp::HandleAppleEvent(
	const AppleEvent&	inAppleEvent,
	AppleEvent&			outAEReply,
	AEDesc&				outResult,
	long				inAENumber)
{
	OSErr	ignoreErr;
	
	switch (inAENumber) {
		
		case ae_OpenDoc:
		HandleOpenDocsEvent(inAppleEvent, outAEReply, outResult);
		break;
		
		case aeRzil_Version: 
		char * theVers = new char[256];
		CopyPascalStringToC( sVersionNumber, theVers);
		Size  dataSize = strlen(theVers);
		ignoreErr = ::AEPutParamPtr(&outAEReply, keyAEResult, typeChar, theVers, dataSize);
		FailOSErr_(ignoreErr);
		break;
		
		case ae_ApplicationDied:
		break;
		
		default:
		LApplication::HandleAppleEvent(inAppleEvent, outAEReply, outResult, inAENumber);
		break;
	}
}


// ---------------------------------------------------------------------------
//	¥ HandleAppleEvent												  [public]
// ---------------------------------------------------------------------------

void
CRezillaApp::HandleOpenDocsEvent(
	const AppleEvent&	inAppleEvent,
	AppleEvent&			outAEReply,
	AEDesc&				outResult)
{
#pragma unused( outAEReply, outResult )
	OSErr			error;
	AEDesc			theDocList;
	AEKeyword		theKey;
	DescType		theType;
	FSSpec			theFileSpec;
	Size			theSize;
	SInt32			numDocs;
	
	error = ::AEGetParamDesc(&inAppleEvent, keyDirectObject,
							 typeAEList, &theDocList);
	ThrowIfOSErr_(error);
	error = ::AECountItems(&theDocList, &numDocs);
	ThrowIfOSErr_(error);
	
	for ( UInt16 i = 1; i <= numDocs; i++ ) {
	    error = ::AEGetNthPtr(&theDocList, i, typeFSS, &theKey, &theType,
						      (Ptr) &theFileSpec, sizeof(FSSpec), &theSize);
	    ThrowIfOSErr_(error);
	
		sReadOnlyNavFlag = false;
	    OpenFork(theFileSpec);
	}
		
	if (theDocList.descriptorType != typeNull) ::AEDisposeDesc(&theDocList);
}


// ---------------------------------------------------------------------------
//	¥ DoPreferences												   [protected]
// ---------------------------------------------------------------------------
//	Handle Preferences settings

void
CRezillaApp::DoPreferences()
{
	sPrefs->RunPrefsWindow();
}



