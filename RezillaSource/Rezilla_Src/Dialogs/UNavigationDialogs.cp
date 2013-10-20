// ===========================================================================
// UNavigationDialogs.cp					
//                       Created: 2003-05-15 10:35:40
//             Last modification: 2003-05-15 13:20:33
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2003
// All rights reserved.
// ===========================================================================
// Modified PowerPlant's UNavServicesDialogs to allow for customization of 
// the EventUpp and the user data.

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "UNavigationDialogs.h"

#include <LFileTypeList.h>
#include <LString.h>
#include <PP_Resources.h>
#include <UDesktop.h>
#include <UExtractFromAEDesc.h>
#include <UMemoryMgr.h>
#include <UModalDialogs.h>
#ifndef __MACH__
#include <Script.h>
#endif

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   StNavReplyRecord						Default Constructor		  [public]
// ---------------------------------------------------------------------------

UNavigationDialogs::StNavReplyRecord::StNavReplyRecord()
{
	mNavReply.validRecord = false;

	SetDefaultValues();
}


// ---------------------------------------------------------------------------
//     ~StNavReplyRecord						Destructor				  [public]
// ---------------------------------------------------------------------------

UNavigationDialogs::StNavReplyRecord::~StNavReplyRecord()
{
	if (mNavReply.validRecord) {
		::NavDisposeReply(&mNavReply);
	}
}


// ---------------------------------------------------------------------------
//   SetDefaultValues												  [public]
// ---------------------------------------------------------------------------

void
UNavigationDialogs::StNavReplyRecord::SetDefaultValues()
{
									// Clean up record if it is valid
	if (mNavReply.validRecord) {
		::NavDisposeReply(&mNavReply);
	}

		// The Nav Services documentation states that the other fields
		// are invalid if validRecord is false. However, we put sensible
		// defaults in each field so that we can access them without
		// having to throw an error if validRecord is false.

	mNavReply.validRecord				= false;
	mNavReply.replacing					= false;
	mNavReply.isStationery				= false;
	mNavReply.translationNeeded			= false;
	mNavReply.selection.descriptorType = typeNull;
	mNavReply.selection.dataHandle		= nil;
	mNavReply.keyScript					= smSystemScript;
	mNavReply.fileTranslation			= nil;
}


// ---------------------------------------------------------------------------
//   GetFileSpec													  [public]
// ---------------------------------------------------------------------------
//	Pass back the FSSpec for the underlying file. Accesses the first file
//	if there is more than one file.

void
UNavigationDialogs::StNavReplyRecord::GetFileSpec(
	FSSpec&		outFileSpec) const
{
	UExtractFromAEDesc::TheFSSpec(Selection(), outFileSpec);
}

#pragma mark -

// ---------------------------------------------------------------------------
//   Load															  [public]
// ---------------------------------------------------------------------------

void
UNavigationDialogs::Load()
{
	::NavLoad();
}


// ---------------------------------------------------------------------------
//   Unload														  [public]
// ---------------------------------------------------------------------------

void
UNavigationDialogs::Unload()
{
	::NavUnload();
}

#pragma mark -

// ---------------------------------------------------------------------------
//   AskSaveChanges												  [public]
// ---------------------------------------------------------------------------

SInt16
UNavigationDialogs::AskSaveChanges(
	ConstStringPtr	inDocumentName,
	ConstStringPtr	inAppName,
	bool			inQuitting)
{
	NavDialogOptions	options;
	::NavGetDefaultDialogOptions(&options);

	LString::CopyPStr(inDocumentName, options.savedFileName);
	LString::CopyPStr(inAppName, options.clientName);

	StNavEventUPP				eventUPP(NavigationEventProc);
	NavAskSaveChangesResult		reply = kNavAskSaveChangesCancel;

	NavAskSaveChangesAction		action = kNavSaveChangesClosingDocument;
	if (inQuitting) {
		action = kNavSaveChangesQuittingApplication;
	}

	UDesktop::Deactivate();

	OSErr	err = ::NavAskSaveChanges(&options, action, &reply, eventUPP, nil);

	UDesktop::Activate();

	ThrowIfOSErr_(err);

	return (SInt16) reply;
}


// ---------------------------------------------------------------------------
//   AskConfirmRevert												  [public]
// ---------------------------------------------------------------------------

bool
UNavigationDialogs::AskConfirmRevert(
	ConstStringPtr	inDocumentName)
{
	NavDialogOptions	options;
	::NavGetDefaultDialogOptions(&options);

	LString::CopyPStr(inDocumentName, options.savedFileName);

	StNavEventUPP				eventUPP(NavigationEventProc);
	NavAskDiscardChangesResult	reply = kNavAskDiscardChangesCancel;

	UDesktop::Deactivate();

	OSErr	err = ::NavAskDiscardChanges(&options, &reply, eventUPP, nil);

	UDesktop::Activate();

	ThrowIfOSErr_(err);

	return (reply == kNavAskDiscardChanges);
}

#pragma mark -

// ---------------------------------------------------------------------------
//   AskOpenOneFile												  [public]
// ---------------------------------------------------------------------------
//	Simple wrapper for NavGetFile that lets a user select one file using
//	the default options

bool
UNavigationDialogs::AskOpenOneFile(
	OSType					inFileType,
	FSSpec&					outFileSpec,
	NavDialogOptionFlags	inFlags)
{
	LFileTypeList	fileTypes(inFileType);
	CNavFileChooser	chooser;

	inFlags &= ~kNavAllowMultipleFiles;		// Can't select multiple files
	NavDialogOptions*	options = chooser.GetDialogOptions();
	options->dialogOptionFlags = inFlags;

	bool	askOK = chooser.AskOpenFile(fileTypes);

	if (askOK) {
		chooser.GetFileSpec(1, outFileSpec);
	}

	return askOK;
}


// ---------------------------------------------------------------------------
//   AskChooseOneFile												  [public]
// ---------------------------------------------------------------------------

bool
UNavigationDialogs::AskChooseOneFile(
	OSType					inFileType,
	FSSpec&					outFileSpec,
	NavDialogOptionFlags	inFlags)
{
	LFileTypeList	fileTypes(inFileType);
	CNavFileChooser	chooser;

	NavDialogOptions*	options = chooser.GetDialogOptions();
	options->dialogOptionFlags = inFlags;

	return chooser.AskChooseOneFile(fileTypes, outFileSpec);
}


// ---------------------------------------------------------------------------
//   AskChooseFolder												  [public]
// ---------------------------------------------------------------------------

bool
UNavigationDialogs::AskChooseFolder(
	FSSpec&					outFileSpec,
	SInt32&					outFolderDirID)
{
	CNavFileChooser	chooser;

	return chooser.AskChooseFolder(outFileSpec, outFolderDirID);
}


// ---------------------------------------------------------------------------
//   AskChooseVolume												  [public]
// ---------------------------------------------------------------------------

bool
UNavigationDialogs::AskChooseVolume(
	FSSpec&					outFileSpec)
{
	CNavFileChooser	chooser;

	return chooser.AskChooseVolume(outFileSpec);
}


// ---------------------------------------------------------------------------
//   AskSaveFile													  [public]
// ---------------------------------------------------------------------------

bool
UNavigationDialogs::AskSaveFile(
	ConstStringPtr			inDefaultName,
	OSType					inFileType,
	FSSpec&					outFileSpec,
	bool&					outReplacing,
	NavDialogOptionFlags	inFlags)
{
	CNavFileDesignator		designator;

	designator.SetFileType(inFileType);

	if (not (inFlags & kNavAllowStationery)) {
									// Turn off type popup. The popup
									//   contains file translation and
									//   stationery options. By design
									//   this function doesn't support
									//   file translation.
		inFlags |= kNavNoTypePopup;
	}

	NavDialogOptions*	options = designator.GetDialogOptions();
	options->dialogOptionFlags = inFlags;

	LString::CopyPStr(inDefaultName, options->savedFileName);
	
	bool	askOK = designator.AskDesignateFile();

	if (askOK) {
		designator.GetFileSpec(outFileSpec);
		outReplacing = designator.IsReplacing();
	}

	return askOK;
}

#pragma mark -

// ===========================================================================
//	CNavFileChooser Class
// ===========================================================================
//	Uses Navigation Services to ask user to open a file

// ---------------------------------------------------------------------------
//   CNavFileChooser::CNavFileChooser			Constructor				  [public]
// ---------------------------------------------------------------------------

UNavigationDialogs::CNavFileChooser::CNavFileChooser()
{
	::NavGetDefaultDialogOptions(&mNavOptions);

	::GetIndString( mNavOptions.windowTitle,
					STRx_Standards, str_OpenDialogTitle);
// NewNavEventUPP(NavEventProc)
	mNavEventProc	= NavigationEventProc;
	mNavFilterProc	= nil;
	mNavPreviewProc	= nil;
	mSelectDefault	= false;
	mUserData		= nil;
}


// ---------------------------------------------------------------------------
//   CNavFileChooser::~CNavFileChooser			Destructor			  [public]
// ---------------------------------------------------------------------------

UNavigationDialogs::CNavFileChooser::~CNavFileChooser()
{
}


// ---------------------------------------------------------------------------
//   CNavFileChooser::GetDialogOptions								  [public]
// ---------------------------------------------------------------------------

NavDialogOptions*
UNavigationDialogs::CNavFileChooser::GetDialogOptions()
{
	return &mNavOptions;
}


// ---------------------------------------------------------------------------
//   CNavFileChooser::SetDefaultLocation								  [public]
// ---------------------------------------------------------------------------
//	Specify the item that is selected when the "choose" dialog is displayed
//
//	If the inFileSpec refers to a directory, the inSelectIt parameter
//	specifies whether to select the directory itself (true), or to select
//	the first item within the directory (false).

void
UNavigationDialogs::CNavFileChooser::SetDefaultLocation(
	const FSSpec&	inFileSpec,
	bool			inSelectIt)
{
	mDefaultLocation = inFileSpec;
	mSelectDefault	 = inSelectIt;
}


// ---------------------------------------------------------------------------
//   CNavFileChooser::SetOptionFlags								  [public]
// ---------------------------------------------------------------------------
// See: http://developer.apple.com/techpubs/macosx/Carbon/Files/NavigationServices/Navigation_Services_Ref/navigation_services/constant_3.html#//apple_ref/doc/c_ref/NavDialogOptionFlags
//   kNavDefaultNavDlogOptions = 0x000000E4,
//   kNavNoTypePopup = 0x00000001,
//   kNavDontAutoTranslate = 0x00000002,
//   kNavDontAddTranslateItems = 0x00000004,
//   kNavAllFilesInPopup = 0x00000010,
//   kNavAllowStationery = 0x00000020,
//   kNavAllowPreviews = 0x00000040,
//   kNavAllowMultipleFiles = 0x00000080,
//   kNavAllowInvisibleFiles = 0x00000100,
//   kNavDontResolveAliases = 0x00000200,
//   kNavSelectDefaultLocation = 0x00000400,
//   kNavSelectAllReadableItem = 0x00000800,
//   kNavSupportPackages = 0x00001000,
//   kNavAllowOpenPackages = 0x00002000,
//   kNavDontAddRecents = 0x00004000,
//   kNavDontUseCustomFrame = 0x00008000,
//   kNavDontConfirmReplacement = 0x00010000,
//   kNavPreserveSaveFileExtension = 0x00020000

// kNavDefaultNavDlogOptions = kNavAllowMultipleFiles + kNavAllowPreviews + kNavAllowStationery + kNavDontAutoTranslate

void
UNavigationDialogs::CNavFileChooser::SetOptionFlags(NavDialogOptionFlags inFlags)
{
	mNavOptions.dialogOptionFlags = inFlags;
}


// ---------------------------------------------------------------------------
//   CNavFileChooser::SetPopupExtension						  [public]
// ---------------------------------------------------------------------------
//	Specify the handle to a popup submenu

void
UNavigationDialogs::CNavFileChooser::SetPopupExtension(
			  NavMenuItemSpecArrayHandle inPopupExtension)
{
	mNavOptions.popupExtension	 = inPopupExtension;
}


// ---------------------------------------------------------------------------
//   CNavFileChooser::SetUserData								  [public]
// ---------------------------------------------------------------------------
//	Specify the handle to a popup submenu

void
UNavigationDialogs::CNavFileChooser::SetUserData(
			  void * inDataPtr)
{
	mUserData = inDataPtr;
}


// ---------------------------------------------------------------------------
//   CNavFileChooser::SetEventFilterProc						  [public]
// ---------------------------------------------------------------------------

void
UNavigationDialogs::CNavFileChooser::SetEventFilterProc(
	NavEventProcPtr	inFilterProc)
{
	mNavEventProc = inFilterProc;
}


// ---------------------------------------------------------------------------
//   CNavFileChooser::SetObjectFilterProc								  [public]
// ---------------------------------------------------------------------------
//	Specify the object filter callback function
//
//	See the comments for UClassicDialogs::CNavFileChooser::SetObjectFilterProc()
//	if you wish to use the same callback function for both NavServices
//	and StandardFile.

void
UNavigationDialogs::CNavFileChooser::SetObjectFilterProc(
	NavObjectFilterProcPtr	inFilterProc)
{
	mNavFilterProc = inFilterProc;
}


// ---------------------------------------------------------------------------
//   CNavFileChooser::SetPreviewProc									  [public]
// ---------------------------------------------------------------------------

void
UNavigationDialogs::CNavFileChooser::SetPreviewProc(
	NavPreviewProcPtr	inPreviewProc)
{
	mNavPreviewProc = inPreviewProc;
}


// ---------------------------------------------------------------------------
//   CNavFileChooser::AskOpenFile										  [public]
// ---------------------------------------------------------------------------

bool
UNavigationDialogs::CNavFileChooser::AskOpenFile(
	const LFileTypeList&	inFileTypes)
{
									// Create UPPs for callback functions
	StNavEventUPP			eventUPP(mNavEventProc);
	StNavObjectFilterUPP	objectFilterUPP(mNavFilterProc);
	StNavPreviewUPP			previewUPP(mNavPreviewProc);

	mNavReply.SetDefaultValues();	// Initialize Reply record

									// Set default location, the location
									//   that's displayed when the dialog
									//   first appears
	AEDesc*		defaultLocationDesc = nil;
	if (not mDefaultLocation.IsNull()) {
		defaultLocationDesc = mDefaultLocation;

		if (mSelectDefault) {
			mNavOptions.dialogOptionFlags |= kNavSelectDefaultLocation;
		} else {
			mNavOptions.dialogOptionFlags &= ~kNavSelectDefaultLocation;
		}
	}

	UDesktop::Deactivate();

	OSErr err = ::NavGetFile(
						defaultLocationDesc,
						mNavReply,
						&mNavOptions,
						eventUPP,
						previewUPP,
						objectFilterUPP,
						inFileTypes.TypeListHandle(),
						mUserData);							// User Data

	UDesktop::Activate();

	if ( (err != noErr) && (err != userCanceledErr) ) {
		Throw_(err);
	}

	return mNavReply.IsValid();
}


// ---------------------------------------------------------------------------
//   CNavFileChooser::AskChooseOneFile								  [public]
// ---------------------------------------------------------------------------

bool
UNavigationDialogs::CNavFileChooser::AskChooseOneFile(
	const LFileTypeList&	inFileTypes,
	FSSpec&					outFileSpec)
{
									// Create UPPs for callback functions
	StNavEventUPP			eventUPP(mNavEventProc);
	StNavObjectFilterUPP	objectFilterUPP(mNavFilterProc);
	StNavPreviewUPP			previewUPP(mNavPreviewProc);

	mNavReply.SetDefaultValues();

									// Can choose only one file
	mNavOptions.dialogOptionFlags &= ~kNavAllowMultipleFiles;

									// Set default location, the location
									//   that's displayed when the dialog
									//   first appears
	AEDesc*		defaultLocationDesc = nil;
	if (not mDefaultLocation.IsNull()) {
		defaultLocationDesc = mDefaultLocation;

		if (mSelectDefault) {
			mNavOptions.dialogOptionFlags |= kNavSelectDefaultLocation;
		} else {
			mNavOptions.dialogOptionFlags &= ~kNavSelectDefaultLocation;
		}
	}

	UDesktop::Deactivate();

	OSErr err = ::NavChooseFile(
						defaultLocationDesc,
						mNavReply,
						&mNavOptions,
						eventUPP,
						previewUPP,
						objectFilterUPP,
						inFileTypes.TypeListHandle(),
						mUserData);							// User Data

	UDesktop::Activate();

	if ( (err != noErr) && (err != userCanceledErr) ) {
		Throw_(err);
	}

	if (mNavReply.IsValid()) {
		mNavReply.GetFileSpec(outFileSpec);
	}

	return mNavReply.IsValid();
}


// ---------------------------------------------------------------------------
//   CNavFileChooser::AskChooseFolder									  [public]
// ---------------------------------------------------------------------------

bool
UNavigationDialogs::CNavFileChooser::AskChooseFolder(
	FSSpec&			outFileSpec,
	SInt32&			outFolderDirID)
{
									// Create UPPs for callback functions
	StNavEventUPP			eventUPP(mNavEventProc);
	StNavObjectFilterUPP	objectFilterUPP(mNavFilterProc);

	mNavReply.SetDefaultValues();

									// Set default location, the location
									//   that's displayed when the dialog
									//   first appears
	AEDesc*		defaultLocationDesc = nil;
	if (not mDefaultLocation.IsNull()) {
		defaultLocationDesc = mDefaultLocation;

		if (mSelectDefault) {
			mNavOptions.dialogOptionFlags |= kNavSelectDefaultLocation;
		} else {
			mNavOptions.dialogOptionFlags &= ~kNavSelectDefaultLocation;
		}
	}

	UDesktop::Deactivate();

	OSErr err = ::NavChooseFolder(
						defaultLocationDesc,
						mNavReply,
						&mNavOptions,
						eventUPP,
						objectFilterUPP,
						mUserData);							// User Data

	UDesktop::Activate();

	if ( (err != noErr) && (err != userCanceledErr) ) {
		Throw_(err);
	}

	if (mNavReply.IsValid()) {		// User chose a folder

		FSSpec	folderInfo;
		mNavReply.GetFileSpec(folderInfo);

			// The FSSpec from NavChooseFolder is NOT the file spec
			// for the folder. The parID field is actually the DirID
			// of the folder itself, not the folder's parent, and
			// the name field is empty. We call FSMakeFSSpec() using those
			// value to create an FSSpec for the folder itself.

		outFolderDirID = folderInfo.parID;

		::FSMakeFSSpec(folderInfo.vRefNum, folderInfo.parID, folderInfo.name,
						&outFileSpec);
	}

	return mNavReply.IsValid();
}


// ---------------------------------------------------------------------------
//   CNavFileChooser::AskChooseVolume									  [public]
// ---------------------------------------------------------------------------

bool
UNavigationDialogs::CNavFileChooser::AskChooseVolume(
	FSSpec&		outFileSpec)
{
									// Create UPPs for callback functions
	StNavEventUPP			eventUPP(mNavEventProc);
	StNavObjectFilterUPP	objectFilterUPP(mNavFilterProc);

	mNavReply.SetDefaultValues();

	AEDesc*		defaultLocationDesc = nil;
	if (not mDefaultLocation.IsNull()) {
		defaultLocationDesc = mDefaultLocation;

			// mSelectDefault should always be true when selecting
			// volumes since we can't navigate into anything

		mNavOptions.dialogOptionFlags |= kNavSelectDefaultLocation;
	}

	UDesktop::Deactivate();

	OSErr err = ::NavChooseVolume(
						defaultLocationDesc,
						mNavReply,
						&mNavOptions,
						eventUPP,
						objectFilterUPP,
						mUserData);							// User Data

	UDesktop::Activate();

	if (mNavReply.IsValid()) {		// User chose a volume

		FSSpec	volumeInfo;
		mNavReply.GetFileSpec(volumeInfo);

			// The FSSpec from NavChooseFolder is NOT the file spec
			// for the volume. The parID field is actually the DirID
			// of the volume itself, not the volumes's parent, and
			// the name field is empty. We must call PBGetCatInfo
			// to get the parent DirID and volume name

		Str255		name;
		CInfoPBRec	thePB;			// Directory Info Parameter Block
		thePB.dirInfo.ioCompletion	= nil;
		thePB.dirInfo.ioVRefNum		= volumeInfo.vRefNum;	// Volume is right
		thePB.dirInfo.ioDrDirID		= volumeInfo.parID;		// Volumes's DirID
		thePB.dirInfo.ioNamePtr		= name;
		thePB.dirInfo.ioFDirIndex	= -1;	// Lookup using Volume and DirID

		err = ::PBGetCatInfoSync(&thePB);
		ThrowIfOSErr_(err);

											// Create cannonical FSSpec
		::FSMakeFSSpec(thePB.dirInfo.ioVRefNum, thePB.dirInfo.ioDrParID,
					   name, &outFileSpec);
	}

	return mNavReply.IsValid();
}


// ---------------------------------------------------------------------------
//   CNavFileChooser::IsValid											  [public]
// ---------------------------------------------------------------------------

bool
UNavigationDialogs::CNavFileChooser::IsValid() const
{
	return mNavReply.IsValid();
}


// ---------------------------------------------------------------------------
//   CNavFileChooser::GetNumberOfFiles								  [public]
// ---------------------------------------------------------------------------

SInt32
UNavigationDialogs::CNavFileChooser::GetNumberOfFiles() const
{
	SInt32	numFiles = 0;

	if (mNavReply.IsValid()) {
		AEDescList	selectedItems = mNavReply.Selection();
		OSErr	err = ::AECountItems(&selectedItems, &numFiles);

		ThrowIfOSErr_(err);
	}

	return numFiles;
}


// ---------------------------------------------------------------------------
//   CNavFileChooser::GetFileSpec										  [public]
// ---------------------------------------------------------------------------

void
UNavigationDialogs::CNavFileChooser::GetFileSpec(
	SInt32		inIndex,
	FSSpec&		outFileSpec) const
{
	AEKeyword	theKey;
	DescType	theType;
	Size		theSize;

	AEDescList	selectedItems = mNavReply.Selection();
	OSErr err = ::AEGetNthPtr(&selectedItems, inIndex, typeFSS,
						&theKey, &theType, (Ptr) &outFileSpec,
						sizeof(FSSpec), &theSize);

	ThrowIfOSErr_(err);
}


// ---------------------------------------------------------------------------
//   CNavFileChooser::GetFileDescList									  [public]
// ---------------------------------------------------------------------------

void
UNavigationDialogs::CNavFileChooser::GetFileDescList(
	AEDescList&		outDescList) const
{
	outDescList = mNavReply.Selection();
}


// ---------------------------------------------------------------------------
//   CNavFileChooser::GetScriptCode									  [public]
// ---------------------------------------------------------------------------

ScriptCode
UNavigationDialogs::CNavFileChooser::GetScriptCode() const
{
	return mNavReply.KeyScript();
}

#pragma mark -

// ===========================================================================
//	CNavFileDesignator Class
// ===========================================================================
//	Uses Navigation Services to ask user to save a file

// ---------------------------------------------------------------------------
//   CNavFileDesignator::CNavFileDesignator								  [public]
// ---------------------------------------------------------------------------

UNavigationDialogs::CNavFileDesignator::CNavFileDesignator()
{
	::NavGetDefaultDialogOptions(&mNavOptions);

	::GetIndString( mNavOptions.windowTitle,
					STRx_Standards, str_SaveDialogTitle);

	mFileType	 = FOUR_CHAR_CODE('????');
	mFileCreator = LFileTypeList::GetProcessSignature();
}


// ---------------------------------------------------------------------------
//   CNavFileDesignator::~CNavFileDesignator								  [public]
// ---------------------------------------------------------------------------

UNavigationDialogs::CNavFileDesignator::~CNavFileDesignator()
{
}


// ---------------------------------------------------------------------------
//   CNavFileDesignator::SetFileType									  [public]
// ---------------------------------------------------------------------------

void
UNavigationDialogs::CNavFileDesignator::SetFileType(
	OSType		inFileType)
{
	mFileType = inFileType;
}


// ---------------------------------------------------------------------------
//   CNavFileDesignator::SetFileCreator								  [public]
// ---------------------------------------------------------------------------

void
UNavigationDialogs::CNavFileDesignator::SetFileCreator(
	OSType		inFileCreator)
{
	mFileCreator = inFileCreator;
}


// ---------------------------------------------------------------------------
//   CNavFileDesignator::GetDialogOptions								  [public]
// ---------------------------------------------------------------------------

NavDialogOptions*
UNavigationDialogs::CNavFileDesignator::GetDialogOptions()
{
	return &mNavOptions;
}


// ---------------------------------------------------------------------------
//   CNavFileDesignator::SetDefaultLocation							  [public]
// ---------------------------------------------------------------------------

void
UNavigationDialogs::CNavFileDesignator::SetDefaultLocation(
	const FSSpec&	inFileSpec,
	bool			inSelectIt)
{
	mDefaultLocation = inFileSpec;
	mSelectDefault	 = inSelectIt;
}


// ---------------------------------------------------------------------------
//   CNavFileDesignator::SetOptionFlags								  [public]
// ---------------------------------------------------------------------------
// See: http://developer.apple.com/techpubs/macosx/Carbon/Files/NavigationServices/Navigation_Services_Ref/navigation_services/constant_3.html#//apple_ref/doc/c_ref/NavDialogOptionFlags
// kNavDefaultNavDlogOptions = kNavAllowMultipleFiles + kNavAllowPreviews 
//                              + kNavAllowStationery + kNavDontAutoTranslate

void
UNavigationDialogs::CNavFileDesignator::SetOptionFlags(NavDialogOptionFlags inFlags)
{
	mNavOptions.dialogOptionFlags = inFlags;
}


// ---------------------------------------------------------------------------
//   CNavFileDesignator::SetClientName								  [public]
// ---------------------------------------------------------------------------

void
UNavigationDialogs::CNavFileDesignator::SetClientName(Str255 inName)
{
	LString::CopyPStr(inName, mNavOptions.clientName);
}


// ---------------------------------------------------------------------------
//   CNavFileDesignator::GetClientName								  [public]
// ---------------------------------------------------------------------------

Str255 *
UNavigationDialogs::CNavFileDesignator::GetClientName()
{
	return &mNavOptions.clientName;
}


// ---------------------------------------------------------------------------
//   CNavFileDesignator::SetSavedFileName								  [public]
// ---------------------------------------------------------------------------
//    Str255 clientName;
//    Str255 windowTitle;
//    Str255 actionButtonLabel;
//    Str255 cancelButtonLabel;
//    Str255 savedFileName;
//    Str255 message;
// LString::CopyPStr(
// 	ConstStringPtr	inSourceString,
// 	StringPtr		outDestString,
// 	SInt16			inDestSize)
void
UNavigationDialogs::CNavFileDesignator::SetSavedFileName(Str255 inName)
{
	LString::CopyPStr(inName, mNavOptions.savedFileName);
}


// ---------------------------------------------------------------------------
//   CNavFileDesignator::GetClientName								  [public]
// ---------------------------------------------------------------------------

Str255 *
UNavigationDialogs::CNavFileDesignator::GetSavedFileName()
{
	return &mNavOptions.savedFileName;
}


// ---------------------------------------------------------------------------
//   CNavFileDesignator::SetMessage								  [public]
// ---------------------------------------------------------------------------

void
UNavigationDialogs::CNavFileDesignator::SetMessage(Str255 inNessage)
{
	LString::CopyPStr(inNessage, mNavOptions.message);
}


// ---------------------------------------------------------------------------
//   CNavFileDesignator::SetPopupExtension								  [public]
// ---------------------------------------------------------------------------
//	Specify the handle to a popup submenu

void
UNavigationDialogs::CNavFileDesignator::SetPopupExtension(
			  NavMenuItemSpecArrayHandle inPopupExtension)
{
	mNavOptions.popupExtension	 = inPopupExtension;
}


// ---------------------------------------------------------------------------
//   CNavFileDesignator::SetUserData								  [public]
// ---------------------------------------------------------------------------
//	Specify the handle to a popup submenu

void
UNavigationDialogs::CNavFileDesignator::SetUserData(
			  void * inDataPtr)
{
	mUserData = inDataPtr;
}


// ---------------------------------------------------------------------------
//   CNavFileDesignator::SetEventFilterProc									  [public]
// ---------------------------------------------------------------------------

void
UNavigationDialogs::CNavFileDesignator::SetEventFilterProc(
	NavEventProcPtr	inFilterProc)
{
	mNavEventProc = inFilterProc;
}


// ---------------------------------------------------------------------------
//   CNavFileDesignator::AskDesignateFile								  [public]
// ---------------------------------------------------------------------------

bool
UNavigationDialogs::CNavFileDesignator::AskDesignateFile()
{
	StNavEventUPP		eventUPP(mNavEventProc);

	mNavReply.SetDefaultValues();

	AEDesc*		defaultLocationDesc = nil;
	if (not mDefaultLocation.IsNull()) {
		defaultLocationDesc = mDefaultLocation;

		if (mSelectDefault) {
			mNavOptions.dialogOptionFlags |= kNavSelectDefaultLocation;
		} else {
			mNavOptions.dialogOptionFlags &= ~kNavSelectDefaultLocation;
		}
	}

	UDesktop::Deactivate();

	OSErr err = ::NavPutFile(
						defaultLocationDesc,
						mNavReply,
						&mNavOptions,
						eventUPP,
						mFileType,
						mFileCreator,
						mUserData);					// User Data

	UDesktop::Activate();

	if ( (err != noErr) && (err != userCanceledErr) ) {
		Throw_(err);
	}

	return mNavReply.IsValid();
}


// ---------------------------------------------------------------------------
//   CNavFileDesignator::IsValid										  [public]
// ---------------------------------------------------------------------------

bool
UNavigationDialogs::CNavFileDesignator::IsValid() const
{
	return mNavReply.IsValid();
}


// ---------------------------------------------------------------------------
//   CNavFileDesignator::GetFileSpec									  [public]
// ---------------------------------------------------------------------------

void
UNavigationDialogs::CNavFileDesignator::GetFileSpec(
	FSSpec&		outFileSpec) const
{
	mNavReply.GetFileSpec(outFileSpec);
}


// ---------------------------------------------------------------------------
//   CNavFileDesignator::IsReplacing									  [public]
// ---------------------------------------------------------------------------

bool
UNavigationDialogs::CNavFileDesignator::IsReplacing() const
{
	return mNavReply.IsReplacing();
}


// ---------------------------------------------------------------------------
//   CNavFileDesignator::IsStationery									  [public]
// ---------------------------------------------------------------------------

bool
UNavigationDialogs::CNavFileDesignator::IsStationery() const
{
	return mNavReply.IsStationery();
}


// ---------------------------------------------------------------------------
//   CNavFileDesignator::GetScriptCode								  [public]
// ---------------------------------------------------------------------------

ScriptCode
UNavigationDialogs::CNavFileDesignator::GetScriptCode() const
{
	return mNavReply.KeyScript();
}


// ---------------------------------------------------------------------------
//   CNavFileDesignator::CompleteSave									  [public]
// ---------------------------------------------------------------------------

void
UNavigationDialogs::CNavFileDesignator::CompleteSave(
	NavTranslationOptions	inOption)
{
	if (mNavReply.IsValid()) {
		::NavCompleteSave(mNavReply, inOption);
	}
}


#pragma mark -

// ---------------------------------------------------------------------------
//   NavEventProc													  [static]
// ---------------------------------------------------------------------------
//	Event filter callback routine for Navigation Services

pascal void
UNavigationDialogs::NavigationEventProc(
	NavEventCallbackMessage		inSelector,
	NavCBRecPtr					ioParams,
	NavCallBackUserData			/* ioUserData */)
{
	if (inSelector == kNavCBEvent) {
		try {
			UModalAlerts::ProcessModalEvent(*(ioParams->eventData.eventDataParms.event));
		}

		catch (...) { }			// Can't throw back through the Toolbox
	}
}



// ===========================================================================
//	StNavEventUPP Class
// ===========================================================================

UNavigationDialogs::StNavEventUPP::StNavEventUPP(
	NavEventProcPtr		inProcPtr)
{
	mNavEventUPP = nil;

	if (inProcPtr != nil) {
		mNavEventUPP = NewNavEventUPP(inProcPtr);
	}
}


UNavigationDialogs::StNavEventUPP::~StNavEventUPP()
{
	if (mNavEventUPP != nil) {
		DisposeNavEventUPP(mNavEventUPP);
	}
}

#pragma mark -
// ===========================================================================
//	StNavObjectFilterUPP Class
// ===========================================================================

UNavigationDialogs::StNavObjectFilterUPP::StNavObjectFilterUPP(
	NavObjectFilterProcPtr		inProcPtr)
{
	mNavObjectFilterUPP = nil;

	if (inProcPtr != nil) {
		mNavObjectFilterUPP = NewNavObjectFilterUPP(inProcPtr);
	}
}


UNavigationDialogs::StNavObjectFilterUPP::~StNavObjectFilterUPP()
{
	if (mNavObjectFilterUPP != nil) {
		DisposeNavObjectFilterUPP(mNavObjectFilterUPP);
	}
}

#pragma mark -
// ===========================================================================
//	StNavPreviewUPP Class
// ===========================================================================

UNavigationDialogs::StNavPreviewUPP::StNavPreviewUPP(
	NavPreviewProcPtr	inProcPtr)
{
	mNavPreviewUPP = nil;

	if (inProcPtr != nil) {
		mNavPreviewUPP = NewNavPreviewUPP(inProcPtr);
	}
}


UNavigationDialogs::StNavPreviewUPP::~StNavPreviewUPP()
{
	if (mNavPreviewUPP != nil) {
		DisposeNavPreviewUPP(mNavPreviewUPP);
	}
}


PP_End_Namespace_PowerPlant
