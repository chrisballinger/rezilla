// ===========================================================================
// CRezillaApp.cp					
//                       Created : 2003-04-16 22:13:54
//             Last modification : 2003-06-10 07:02:44
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@easyconnect.fr>
// www : <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright : Bernard Desgraupes 2003
// All rights reserved.
// ===========================================================================


#include "CRezillaApp.h"
#include "CEditTable.h"
#include "CRezMapDoc.h"
#include "CRezFile.h"
#include "CRezMapTable.h"
#include "CRezMapWindow.h"
#include "CRezClipboard.h"
#include "CWindowMenu.h"
#include "RezillaConstants.h"
#include "CInspectorWindow.h"
#include "CHexEditorWindow.h"
#include "CWasteEditView.h"
#include "CHexDataWE.h"
#include "CTxtDataWE.h"
#include "CHexDataSubView.h"
#include "CTxtDataSubView.h"
#include "CRangeEditText.h"
#include "UNavigationDialogs.h"
#include "NavServicesCallbacks.h"
#include "UMessageDialogs.h"
// #include "COutBorderAttachment.h"

// PP Classes for registration
#include <Appearance.h>
#include <LAMControlImp.h>
#include <LAMPopupButtonImp.h>
#include <LAMPushButtonImp.h>
#include <LAMTrackActionImp.h>
#include <LActiveScroller.h>
#include <LCaption.h>
#include <LClipboard.h>
#include <LDialogBox.h>
#include <LDragAndDrop.h>
#include <LEditField.h>
#include <LEditText.h>
#include <LFile.h>
#include <LGAPopupButtonImp.h>
#include <LGAPushButtonImp.h>
#include <LGAWindowHeaderImp.h>
#include <LIconPane.h>
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


extern const Str255 Rzil_NavOpenItems[] = {
	"\pfrom any fork",
	"\pfrom resource fork",
	"\pfrom data fork"
};

extern const Str255 Rzil_NavSaveItems[] = {
	"\pto same fork",
	"\pto resource fork",
	"\pto data fork"
};

extern const Str255 Rzil_NavNewItems[] = {
	"\pin resource fork",
	"\pin data fork"
};



// Statics
CInspectorWindow *		CRezillaApp::sInspectorWindow = nil;
const LStr255	CRezillaApp::sVersionNumber( VersionFromResource() );
SInt16			CRezillaApp::sOwnRefNum;


// ===========================================================================
//  € Main Program
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
//  € CRezillaApp
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
//  € ~CRezillaApp
// ---------------------------------------------------------------------------
//	Destructor
//

CRezillaApp::~CRezillaApp()
{
	// nothing
}


// ---------------------------------------------------------------------------
//	€ Initialize						[protected]
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
	if ( theOsVersion < 0x00900) {
		UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("RequireSystemNine"), rPPob_SimpleMessage);
		SendAEQuit();
	}
	
	// Install an item in the Finder's Help menu
	err	= RegisterHelpBook();
	if ( err == noErr )									
	{
		//	Add custom Help Menu items
		err	= ::HMGetHelpMenu( &menuHandle, &customItemIndex );
		if ( err == noErr )
		{
			// MacOS 8/9 bundled applications must manually add and handle their help menu
			if ( theOsVersion < 0x0920)	{
				InsertMenuItem( menuHandle, "\pRezilla Help", customItemIndex - 1 );
			}
		}
	}
	
	// Create the about window
	MakeAboutWindow();
	
// // 	// Create an instance of CRezillaPrefs
// // 	sPrefs = new CRezillaPrefs(this);

	// Install the window menu.
	InstallWindowMenu();	

	// Create the inspector window
	sInspectorWindow = (CInspectorWindow *)LWindow::CreateWindow(rPPob_InspectorWindow, this);
	ThrowIfNil_(sInspectorWindow);
	
	// Add attachments
	AddAttachment( new CRezClipboard );
	
	CWindowMenuAttachment *theAttachment;	// Window menu attachment.
	theAttachment = new CWindowMenuAttachment( gWindowMenu );
	AddAttachment( theAttachment , nil, true );
	
// 	// Help tags settings
// 	ABalloonBase::EnableControlKeyPop();
// 	ABalloonBase::SetAutoPopDelay(20);

	mOpeningFork = from_anyfork;

}


// ---------------------------------------------------------------------------
//	€ RegisterClasses								[protected]
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
	RegisterClass_(LPicture);
	RegisterClass_(LPopupButton);
	RegisterClass_(LPushButton);
	RegisterClass_(LRadioGroup);
	RegisterClass_(LScrollBar);
	RegisterClass_(LScrollerView);
	RegisterClass_(LStaticText);
	RegisterClass_(LStdPopupMenu);
	RegisterClass_(LTabGroupView);
	RegisterClass_(LTextEditView);
	RegisterClass_(LView);
	RegisterClass_(LWindow);
	RegisterClass_(LWindowHeader);
 	RegisterClass_(LBorderAttachment);
	RegisterClass_(LUndoer);

	// Register Rezilla custom classes.
	RegisterClass_(CEditTable);
	RegisterClass_(CRezMapTable);
	RegisterClass_(CRezMapWindow);
	RegisterClass_(CInspectorWindow);
	RegisterClass_(CHexEditorWindow);
	RegisterClass_(CWasteEditView);
	RegisterClass_(CHexDataWE);
	RegisterClass_(CTxtDataWE);
	RegisterClass_(CHexDataSubView);
	RegisterClass_(CTxtDataSubView);
	RegisterClass_(CRangeEditText);
// 	RegisterClass_(COutBorderAttachment);

// 	RegisterClass_(ATag);

	// AM always present on Carbon
	UControlRegistry::RegisterAMClasses();
}


// ---------------------------------------------------------------------------
//  € StartUp
// ---------------------------------------------------------------------------

void
CRezillaApp::StartUp()
{
// 	ObeyCommand(cmd_New, nil);
}


// ---------------------------------------------------------------------------
//  € ObeyCommand
// ---------------------------------------------------------------------------

Boolean
CRezillaApp::ObeyCommand(
	CommandT	inCommand,
	void		*ioParam)
{
	Boolean		cmdHandled = true;
	
	switch (inCommand) {
		
		case cmd_New: {
			FSSpec	theFileSpec;
			SInt16	theFork;
			short	theRefnum;
			bool	replacing;
			if ( DesignateNewMap(theFileSpec, replacing) ) {
				// Make a new file object.
				CRezFile * theFile = new CRezFile( theFileSpec, refnum_undefined, mOpeningFork );
				// Make new resource file on disk
				if (theFile->CreateNewFile() == noErr) {
					// Open the resource file.
					theFile->OpenFile(fsRdWrPerm);
				}
				new CRezMapDoc(this, &theFileSpec, theFork, theFile->GetRefNum() );
				delete theFile;
			}
			break;
		}
		
		case cmd_ShowInspector: {
			sInspectorWindow->Show();
			// Bring the window to the front.
			UDesktop::SelectDeskWindow( sInspectorWindow );
			break;
		}
		
		case cmd_Open: {	
			FSSpec theFileSpec;
			SInt16 theFork;
			short theRefnum;
			if ( ChooseAFile(theFileSpec) && PreOpen(theFileSpec, theFork, theRefnum)) {
				new CRezMapDoc(this, &theFileSpec, theFork, theRefnum);
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
//  € FindCommandStatus
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
		outEnabled = true;
			break;		
		
		case cmd_Find:
		case cmd_NewRez:
		case cmd_EditRez:
		case cmd_GetRezInfo:
		case cmd_RemoveRez:
		case cmd_DuplicateRez:
		outEnabled = false;
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
//  € ListenToMessage												[public]
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
//	€ MakeAboutBox													  [public]
// ---------------------------------------------------------------------------

void
CRezillaApp::MakeAboutWindow()
{	
	mAboutWindow = (LDialogBox *)(LWindow::CreateWindow( rPPob_AboutWindow, this ));
	ThrowIfNil_(mAboutWindow);
	
	// Write the version number in the caption
	LStaticText *theCaption;	
	theCaption = dynamic_cast<LStaticText *>(mAboutWindow->FindPaneByID( item_AboutVersCaption ));
	theCaption->SetDescriptor(sVersionNumber);

	UReanimator::LinkListenerToControls( this, mAboutWindow, rRidL_AboutWindow );
}


// ---------------------------------------------------------------------------
//	€ ShowAboutBox													  [public]
// ---------------------------------------------------------------------------
//	Display the About Box for the Application

void
CRezillaApp::ShowAboutBox()
{
	mAboutWindow->Show();
	UDesktop::SelectDeskWindow(mAboutWindow);
}


// ---------------------------------------------------------------------------
//	€ InstallWindowMenu								[protected]
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
	LStr255 theItem(STRx_RzilWinMenuItem, index_WinsInspector);
	gWindowMenu->InsertCommand(theItem, cmd_ShowInspector, 1);
	gWindowMenu->EnableItem(1);
	::SetMenuItemCommandKey(gWindowMenu->GetMacMenuH(), 1, 0, 48);

	// Install the window menu in the menu bar
	LMenuBar * theMBar = LMenuBar::GetCurrentMenuBar();
	ThrowIfNil_( theMBar );
	theMBar->InstallMenu( gWindowMenu, 0 );
}


// ---------------------------------------------------------------------------
//	€ RegisterHelpBook											[private]
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
//	€ VersionFromResource										  [public]
// ---------------------------------------------------------------------------
// Retrieve the version number from the 'vers' resources.

LStr255
CRezillaApp::VersionFromResource()
{
	UInt32 theVersion;
	UInt8	ver1,ver2,ver3;
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
		::NumToString((long) ver1, tempString);
		theString += tempString ;
		::NumToString((long) ver2, tempString);
		theString += "\p." ;
		theString += tempString ;
		if ( ver3 ) {
			::NumToString((long) ver3, tempString);
			theString += "\p." ;
			theString += tempString ;
		}
	}
	return  theString;
}


// ---------------------------------------------------------------------------
//	€ ChooseAFile								[public static]
// ---------------------------------------------------------------------------

Boolean
CRezillaApp::ChooseAFile(FSSpec & outFileSpec)
{
	LFileTypeList fileTypes(fileTypes_All);
	bool	openOK = false;
	
	mOpeningFork == from_anyfork;
	
	// Build the forks popup
	NavMenuItemSpecHandle	theMenuItemHandle ;
	NavMenuItemSpecPtr		theNavMenuItemSpecPtr;
	
	theMenuItemHandle = (NavMenuItemSpec**) NewHandleClear( 3 * sizeof(NavMenuItemSpec) );
	if (theMenuItemHandle != NULL) {
		for (SInt16 theIndex = 0; theIndex < 3; theIndex++) {
			theNavMenuItemSpecPtr = *theMenuItemHandle + theIndex;
			(*theNavMenuItemSpecPtr).version = kNavMenuItemSpecVersion;
			(*theNavMenuItemSpecPtr).menuCreator = FOUR_CHAR_CODE('Rzil');
			(*theNavMenuItemSpecPtr).menuType = 'TEXT';
			BlockMoveData(Rzil_NavOpenItems[theIndex], (*theNavMenuItemSpecPtr).menuItemName, Rzil_NavOpenItems[theIndex][0] + 1);
		}
	}

	// Deactivate the desktop.
	::UDesktop::Deactivate();
	
	// Browse for a document.
	UNavigationDialogs::CNavFileChooser chooser;
	chooser.SetEventFilterProc(Rzil_OpenNavEventFilterUPP);
	chooser.SetPopupExtension(theMenuItemHandle);
	chooser.SetOptionFlags(kNavAllowStationery + kNavDontAutoTranslate);
	chooser.SetUserData( (void *) &mOpeningFork);
	
	openOK = chooser.AskOpenFile(fileTypes);

	if (openOK) {
		chooser.GetFileSpec(1, outFileSpec);
	}

    // Activate the desktop.
    ::UDesktop::Activate();

	return openOK;
}


// ---------------------------------------------------------------------------
//	€ ChooseAFile								[public static]
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
//	€ PreOpen								[public static]
// ---------------------------------------------------------------------------

Boolean
CRezillaApp::PreOpen(FSSpec & inFileSpec, SInt16 & outFork, short & outRefnum)
{
	Boolean		openOK = false;
	OSErr		error;
	FSRef		inFileRef;
	
	StRezReferenceSaver saver( ::CurResFile() );
	
	if (mOpeningFork != from_rezfork) {
		// Try to open the file as a datafork resource file
		error = FSpMakeFSRef( &inFileSpec, &inFileRef );
		SetResLoad( false );
		error = FSOpenResourceFile( &inFileRef, 0, nil, fsRdWrPerm, &outRefnum );
		SetResLoad( true );
		
		if (error == noErr) {
			openOK = true;
			outFork = from_datafork;
			goto done;
		} else if (mOpeningFork == from_datafork) {
			// If this failed (eofErr), the file has no resource in data fork
			UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("NoRezInDataFork"), rPPob_SimpleMessage);
			goto done;			
		} 
	} 
	
	if (mOpeningFork != from_datafork) {
		// If this failed (mapReadErr), try to open as a resourcefork resource file
		SetResLoad( false );
		outRefnum = FSpOpenResFile( &inFileSpec, fsRdWrPerm);
		error = ResError();
		SetResLoad( true );
		if (error == noErr) {
			openOK = true;
			outFork = from_rezfork;
			goto done;
		} else {
			// If this failed (eofErr), the file has no resource in resource fork
			if (mOpeningFork == from_anyfork) {
				UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("NoRezInAnyFork"), rPPob_SimpleMessage);
			} else {
				UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("NoRezInRezFork"), rPPob_SimpleMessage);
			}
		}
	} 
	
done:
	return openOK;
}


// ---------------------------------------------------------------------------
//	€ DesignateNewMap								[public static]
// ---------------------------------------------------------------------------

Boolean
CRezillaApp::DesignateNewMap( FSSpec& outFileSpec, bool & outReplacing)
{
	LFileTypeList fileTypes(fileTypes_All);
	bool	openOK = false;
	Str255	theString;
		
	// Build the forks popup
	NavMenuItemSpecHandle	theMenuItemHandle ;
	NavMenuItemSpecPtr		theNavMenuItemSpecPtr;
	
	theMenuItemHandle = (NavMenuItemSpec**) NewHandleClear( 2 * sizeof(NavMenuItemSpec) );
	if (theMenuItemHandle != NULL) {
		for (SInt16 theIndex = 0; theIndex < 2; theIndex++) {
			theNavMenuItemSpecPtr = *theMenuItemHandle + theIndex;
			(*theNavMenuItemSpecPtr).version = kNavMenuItemSpecVersion;
			(*theNavMenuItemSpecPtr).menuCreator = FOUR_CHAR_CODE('Rzil');
			(*theNavMenuItemSpecPtr).menuType = 'TEXT';
			BlockMoveData(Rzil_NavNewItems[theIndex], (*theNavMenuItemSpecPtr).menuItemName, Rzil_NavNewItems[theIndex][0] + 1);
		}
	}

	// Deactivate the desktop.
	::UDesktop::Deactivate();
	
	// Browse for a document
	UNavigationDialogs::CNavFileDesignator designator;
	
	// File designator setup
	designator.SetEventFilterProc(Rzil_NewMapNavEventFilterUPP);
	designator.SetPopupExtension(theMenuItemHandle);
	designator.SetOptionFlags(kNavDontAutoTranslate);
	designator.SetUserData( (void *) &mOpeningFork);

	// Retrieve strings from STR# resource
	GetIndString(theString, STRx_NavServStrings, index_RezillaAppName);
	designator.SetClientName(theString);
	GetIndString(theString, STRx_NavServStrings, index_CreateNewRezMap);
	designator.SetMessage(theString);
	GetIndString(theString, STRx_NavServStrings, index_CreateUntitled);
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



