// ===========================================================================
// CRecentItemsMenu.cp				
//                       Created: 2004-03-02 13:18:30
//             Last modification: 2004-05-18 20:20:01
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#include "CRecentItemsMenu.h"
#include "CAlias.h"
#include "RezillaConstants.h"

// PowerPlant Headers
#include <TArrayIterator.h>

// Universal Headers
#include <CFPreferences.h>


// ---------------------------------------------------------------------------------
//	¥	CRecentItemsMenu								[Constructor] 
// ---------------------------------------------------------------------------------
// mAppIdentifier ---> CFSTR(kRezillaIdentifier)

CRecentItemsMenu::CRecentItemsMenu(ResIDT inMenuID, 
								   UInt32 inMaxRecentItems, 
								   CFStringRef inApplicationID) 
{
	mMessage			= msg_AnyMessage;
	mMaxRecentItems 	= inMaxRecentItems;
	mMenuID				= inMenuID;
	mMenuHandle			= ::GetMenuHandle(mMenuID);
	mAppIdentifier 		= inApplicationID;
// 	ThrowIfNil_( mMenuHandle );
	
	RetrieveFromPreferences();
}


// ---------------------------------------------------------------------------------
//	¥	~CRecentItemsMenu								[Destructor] 
// ---------------------------------------------------------------------------------
//	Store in preferences and delete CAlias objects in array.

CRecentItemsMenu::~CRecentItemsMenu() 
{	
	StoreInPreferences();
	DeleteAllItems();
}


// ---------------------------------------------------------------------------------
//	¥	ExecuteSelf 
// ---------------------------------------------------------------------------------
//	Update menu every time user clicks in menu bar.
//	Take care of enabling the items in the menu.

void
CRecentItemsMenu::ExecuteSelf( MessageT inMessage, void *ioParam )
{
	mExecuteHost = true;
	
	if ( inMessage == msg_CommandStatus ) {
		ResIDT	synthMenu;
		SInt16	synthItem;
		SCommandStatus	*status = (SCommandStatus*)ioParam;
		
		if (status->command == mMenuID || (LCommander::IsSyntheticCommand( status->command, synthMenu, synthItem) && synthMenu == mMenuID)) {
			
			*status->enabled = true;
			mExecuteHost = false;
		}
	} else {
		// Handle selected item
		ResIDT	synthMenu;
		SInt16	synthItem;
		
		// It is a synthetic menu selection
		if ( LCommander::IsSyntheticCommand( inMessage, synthMenu, synthItem) && synthMenu == mMenuID) {
			FSSpec theFile;
			
			// Make an FSSpec out of the menu item
			if (GetSelectedItem(synthItem, theFile) == noErr) {
				OpenSelectedItem(theFile);
				mExecuteHost = false;
			} else {
				::SysBeep(3);
			}
		}
	}
}


// ---------------------------------------------------------------------------------
//	¥	SetMaxRecentItems 
// ---------------------------------------------------------------------------------

void
CRecentItemsMenu::SetMaxRecentItems(UInt32 inMaxRecentItems) 
{	
	UInt32 theCount = mAliasArray.GetCount();
	
	mMaxRecentItems = inMaxRecentItems;
	
	// If there are more items, remove some
	if (theCount > mMaxRecentItems) {
		
		// Delete items at start of array
		TArrayIterator<CAlias*> iterator(mAliasArray, LArray::index_First);
		CAlias * theAlias;
		
		while(iterator.Current(theAlias) && theCount > mMaxRecentItems) {
			mAliasArray.Remove(theAlias);
			delete theAlias;
			theCount--;
		}
	}
}


// ---------------------------------------------------------------------------------
//	¥	CountItems 
// ---------------------------------------------------------------------------------

UInt32
CRecentItemsMenu::CountItems() 
{	
	return mAliasArray.GetCount();
}


// ---------------------------------------------------------------------------------
//	¥	AddFile 
// ---------------------------------------------------------------------------------

OSErr
CRecentItemsMenu::AddFile(AliasHandle inAliasHandle, Boolean inRebuild) 
{	
	OSErr	result 		= noErr;
	Boolean	wasChanged 	= false;
	FSSpec 	theFSSpec;
	
	result = ::ResolveAlias(NULL, inAliasHandle, &theFSSpec, &wasChanged);
	if (result == noErr) {
		AddFile(theFSSpec, inRebuild);	
	}
		
	return result;
}


// ---------------------------------------------------------------------------------
//	¥	AddFile 
// ---------------------------------------------------------------------------------

void
CRecentItemsMenu::AddFile(FSSpec& inFSSpec, Boolean inRebuild) 
{	
	FSSpec 	theFSSpec;
	Boolean registered = false;
	
	TArrayIterator<CAlias*> iterator(mAliasArray);
	CAlias * theAlias = NULL;
	
	while(iterator.Next(theAlias) && registered == false) {
		// Iterate through the array to see if we already have this FSSpec
		theAlias->GetFileSpec(theFSSpec);
		
		if (LFile::EqualFileSpec(theFSSpec, inFSSpec)) {
			registered = true;
		}
	}
	
	if (!registered) {
		if (mAliasArray.GetCount() >= mMaxRecentItems) {
			CAlias* firstItem = mAliasArray[LArray::index_First];
			mAliasArray.Remove(firstItem);
			delete firstItem;
		}
		mAliasArray.AddItem( new CAlias(inFSSpec));
		if (inRebuild) {
			RebuildMenu();
		} 
	}	
}


// ---------------------------------------------------------------------------------
//	¥	RemoveFile 
// ---------------------------------------------------------------------------------

void
CRecentItemsMenu::RemoveFile(AliasHandle inAliasHandle) 
{	
	FSSpec 	theFSSpec;
	Boolean	wasChanged = false;
	
	if (::ResolveAlias(&theFSSpec, inAliasHandle, NULL, &wasChanged) == noErr) {
		RemoveFile(theFSSpec);	
	}
}


// ---------------------------------------------------------------------------------
//	¥	RemoveFile 
// ---------------------------------------------------------------------------------

void
CRecentItemsMenu::RemoveFile(FSSpec& inFSSpec) 
{	
	FSSpec 		theFSSpec;
	ArrayIndexT	foundIndex;
	Boolean		foundIt = false;
	
	// Iterate through the array to see if we already have this FSSpec
	TArrayIterator<CAlias*> iterator(mAliasArray, LArrayIterator::from_Start);
	CAlias * theAlias;
	
	while(iterator.Next(theAlias) && foundIt == false) {
		theAlias->GetFileSpec(theFSSpec);
		
		if (LFile::EqualFileSpec(theFSSpec, inFSSpec)) {
			foundIndex = iterator.GetCurrentIndex();
			foundIt = true;
		}
	}
	
	if (foundIt) {
		CAlias* item = mAliasArray[foundIndex];
		mAliasArray.Remove(item);
		delete item;
	}
}


// ---------------------------------------------------------------------------------
//	¥	GetSelectedItem 
// ---------------------------------------------------------------------------------
//	Find FSSpec corresponding to menu item index.

OSErr
CRecentItemsMenu::GetSelectedItem(UInt16 inMenuItem, FSSpec& outFSSpec) 
{	
	OSErr		result 	= -1;
	ArrayIndexT	index 	= inMenuItem;
	
	if (mAliasArray.ValidIndex(index)) {
		result = mAliasArray[index]->GetFileSpec(outFSSpec);
	}
	
	return result;
}


// ---------------------------------------------------------------------------------
//	¥	OpenSelectedItem 
// ---------------------------------------------------------------------------------
//	Checks if attachment host is derived from LDocApplication.
//	If so, calls host's SendAEOpenDoc() function with file spec passed in.

void
CRecentItemsMenu::OpenSelectedItem(FSSpec& inFSSpec) 
{	
	LDocApplication* theApp = dynamic_cast<LDocApplication*>(mOwnerHost);
	
	if (theApp) {
		theApp->SendAEOpenDoc(inFSSpec);
	}
}


// ---------------------------------------------------------------------------------
//	¥	RebuildMenu 
// ---------------------------------------------------------------------------------

void
CRecentItemsMenu::RebuildMenu() 
{	
	Str255	theName;
	UInt16	theCount = ::CountMenuItems( mMenuHandle );
	
	// Empty menu
	while ( theCount > 0 ) {	
		::DeleteMenuItem( mMenuHandle, theCount-- );
	}
	
	TArrayIterator<CAlias*> iterator(mAliasArray);
	CAlias * theAlias;
	
	while (iterator.Next(theAlias)) {
		if (theAlias->GetFileName(theName) == noErr) {
			::AppendMenu( mMenuHandle, theName);
		} else {
			mAliasArray.Remove(theAlias);
			delete theAlias;
		}
	}
}


// ---------------------------------------------------------------------------------
//	¥	DeleteAllItems 
// ---------------------------------------------------------------------------------
//	Delete all CAlias objects whose ptrs are stored in mAliasArray

void
CRecentItemsMenu::DeleteAllItems()
{
	TArrayIterator<CAlias*> iterator(mAliasArray, LArray::index_First);
	CAlias * theAlias, * theNextAlias;
	Boolean hasNext = iterator.Current(theNextAlias);

	while (hasNext) {
		theAlias = theNextAlias;
		hasNext = iterator.Next(theNextAlias);
		mAliasArray.Remove(theAlias);
		delete theAlias;
	}
}


// ---------------------------------------------------------------------------------
//	¥	Reset 
// ---------------------------------------------------------------------------------
//	Delete all items and rebuild the menu

void
CRecentItemsMenu::Reset()
{
	DeleteAllItems();
	RebuildMenu();
}


// ---------------------------------------------------------------------------------
//	¥	StoreInPreferences 
// ---------------------------------------------------------------------------------

void
CRecentItemsMenu::StoreInPreferences() 
{	
	CFStringRef 		theKey = CFSTR("pref_RecentItems");
	CFMutableArrayRef	theArray;

	theArray = CFArrayCreateMutable(NULL, 0, &kCFTypeArrayCallBacks);

	if (theArray) {
		TArrayIterator<CAlias*> iterator(mAliasArray);
		AliasHandle			theAliasH = nil;
		CAlias * 			theAlias;
		CFDataRef			theDataRef;
		
		while (iterator.Next(theAlias)) {
			theAliasH = theAlias->GetAliasHandle();		
			StHandleLocker	locker((Handle) theAliasH);

			theDataRef = CFDataCreate(NULL, (const UInt8 *) *theAliasH, ::GetHandleSize((Handle) theAliasH));
			if (theDataRef) {
				CFArrayAppendValue(theArray, theDataRef);
				CFRelease(theDataRef);
			} 
		}
		CFPreferencesSetAppValue(theKey, theArray, kCFPreferencesCurrentApplication);
		CFRelease(theArray);
	} 
	
	// Flush the prefs to disk
	CFPreferencesAppSynchronize(mAppIdentifier);
}


// ---------------------------------------------------------------------------------
//	¥	RetrieveFromPreferences 
// ---------------------------------------------------------------------------------

void
CRecentItemsMenu::RetrieveFromPreferences() 
{	
	CFPropertyListRef theArray = CFPreferencesCopyAppValue(CFSTR("pref_RecentItems"), mAppIdentifier);
	
	if (theArray) {
		CFIndex				theCount, theIndex, theSize;
		Handle				theAliasH = nil;
		const UInt8 *		theDataPtr;
		CFDataRef			theDataRef;

		theCount = CFArrayGetCount((CFArrayRef) theArray);
		
		for (theIndex = 0 ; theIndex < theCount ; theIndex++ ) {
			theDataRef =  (CFDataRef) CFArrayGetValueAtIndex( (CFArrayRef) theArray, theIndex);
			theDataPtr = CFDataGetBytePtr(theDataRef);
			theSize = CFDataGetLength(theDataRef);
			
			theAliasH = ::NewHandle(theSize);
			StHandleLocker	locker(theAliasH);

			BlockMoveData(theDataPtr, *theAliasH, theSize);
			AddFile( (AliasHandle) theAliasH, false);
			::DisposeHandle(theAliasH);
		}
		CFRelease(theArray);
		RebuildMenu();
	}
}



