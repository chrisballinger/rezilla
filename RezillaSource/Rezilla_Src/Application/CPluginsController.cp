// ===========================================================================
// CPluginsController.cp
// 
//                       Created: 2005-09-26 09:48:26
//             Last modification: 2006-02-15 16:38:51
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes, 2005, 2006
// All rights reserved.
// ===========================================================================

#include "CPluginsController.h"
#include "CRezillaPlugin.h"
#include "UMiscUtils.h"
#include "RezillaConstants.h"

CFMutableDictionaryRef		CPluginsController::sPluginsDict;
TArray<CRezillaPlugin*>		CPluginsController::sPluginsList;


// ---------------------------------------------------------------------------
//  CPluginsController												[public]
// ---------------------------------------------------------------------------

CPluginsController::CPluginsController()
{
	BuildInternalPluginsDictionary();
}


// ---------------------------------------------------------------------------
//  ~CPluginsController												[public]
// ---------------------------------------------------------------------------

CPluginsController::~CPluginsController()
{
	TArrayIterator<CRezillaPlugin*> iterator(sPluginsList, LArrayIterator::from_End);
	CRezillaPlugin *	thePlugin;
	while (iterator.Previous(thePlugin)) {
		sPluginsList.RemoveItemsAt(1, iterator.GetCurrentIndex());
		delete thePlugin;
	}
}


// ---------------------------------------------------------------------------
//  HasPluginForType												[public]
// ---------------------------------------------------------------------------
// 				EXTERN_API_C( Boolean )
// 				CFDictionaryContainsKey(
// 				  CFDictionaryRef   theDict,
// 				  const void *      key);

Boolean
CPluginsController::HasPluginForType(ResType inType)
{
	Boolean hasPlugin = false;
	
	
	return hasPlugin;
}


// ---------------------------------------------------------------------------
//  RegisterPlugin												[public]
// ---------------------------------------------------------------------------

OSErr
CPluginsController::RegisterPlugin()
{
	OSErr	error = noErr;
	
	return error;
}


// ---------------------------------------------------------------------------
//  UnregisterPlugin												[public]
// ---------------------------------------------------------------------------

void
CPluginsController::UnregisterPlugin()
{
}


// ---------------------------------------------------------------------------
//  LoadPlugin												[public]
// ---------------------------------------------------------------------------

void
CPluginsController::LoadPlugin()
{
}


// ---------------------------------------------------------------------------
//	 BuildInternalPluginsDictionary							[private]
// ---------------------------------------------------------------------------
// Create a CFDictionary associating resource types to a CFArray of
// pointers to CRezillaPlugin instances supporting this type. The function
// scans the internal PlugIns subfolder inside the application bundle.

OSErr
CPluginsController::BuildInternalPluginsDictionary()
{
	OSErr	error = noErr;
	
	// Create a mutable dictionary
	sPluginsDict = ::CFDictionaryCreateMutable(NULL, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
	
	if (sPluginsDict) {
		
		CFURLRef pluginsURL = ::CFBundleCopyBuiltInPlugInsURL( CFBundleGetMainBundle() );
		if (pluginsURL != nil) {
			error = ScanPluginsFolder(pluginsURL);
			CFRelease(pluginsURL);
		}
	}
	
	return error;
}


// ---------------------------------------------------------------------------
//	 BuildExternalPluginsDictionary										[private]
// ---------------------------------------------------------------------------
// Create a CFDictionary associating resource types to a CFArray of
// pointers to CRezillaPlugin instances supporting this type. The function
// scans the PlugIns subfolders inside Rezilla's Application Support
// folders, creating them if necessary.
// They can reside in two domains:
// 		kLocalDomain	---> Library/Application Support/Rezilla/PlugIns
// 		kUserDomain		---> ~/Library/Application Support/Rezilla/PlugIns
// 		
// kNetworkDomain ?

OSErr
CPluginsController::BuildExternalPluginsDictionary()
{
	OSErr		error = noErr;
	UInt32 		domainIndex;
	FSRef		appSupportRef, rezillaRef, pluginsRef;
	// kUserDomain, kNetworkDomain, kLocalDomain, kSystemDomain
	static const SInt16 kFolderDomains[] = {kUserDomain, kLocalDomain, 0};
		
	// Create a mutable dictionary
	sPluginsDict = CFDictionaryCreateMutable(NULL, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
	
	if (sPluginsDict) {
		domainIndex = 0;
		do {
			error = FSFindFolder(kFolderDomains[domainIndex], kApplicationSupportFolderType, kCreateFolder, &appSupportRef);
			// If we can't find or create the folder in this domain, just ignore the domain.
			if (error == noErr) {
				HFSUniStr255 	unicodeName;
				ConstStr31Param rzilName = "\pRezilla";
				ConstStr31Param plugName = "\pPlugIns";
				
				// If we found the Support folder, look for a Templates subfolder
				UMiscUtils::HFSNameToUnicodeName(rzilName, &unicodeName);
				error = FSMakeFSRefUnicode(&appSupportRef, unicodeName.length, unicodeName.unicode, 
										   kTextEncodingUnknown, &rezillaRef);
				if (error != noErr) {
					error = FSCreateDirectoryUnicode(&appSupportRef, unicodeName.length, unicodeName.unicode, 
													 kFSCatInfoNone, NULL, &rezillaRef, NULL, NULL);
				}
				
				if (error == noErr) {
					UMiscUtils::HFSNameToUnicodeName(plugName, &unicodeName);
					error = FSMakeFSRefUnicode(&rezillaRef, unicodeName.length, unicodeName.unicode, 
											   kTextEncodingUnknown, &pluginsRef);
					if (error != noErr) {
						error = FSCreateDirectoryUnicode(&rezillaRef, unicodeName.length, unicodeName.unicode, 
														 kFSCatInfoNone, NULL, &pluginsRef, NULL, NULL);
					}
					
					if (error == noErr) {
						ScanPluginsFolder(&pluginsRef);
					}
				} 			
			}
			domainIndex += 1;
		} while ( kFolderDomains[domainIndex] != 0 );
	}
	
	return error;
}


// ---------------------------------------------------------------------------
//	 ScanPluginsFolder											[private]
// ---------------------------------------------------------------------------
// Look for the plugin bundles in the PlugIns directory.

OSErr
CPluginsController::ScanPluginsFolder(FSRef * inPluginsRef)
{
	OSErr			error = noErr;
	CFURLRef		plugInsURL = nil;

	// Get a CFURL from the FSRef
	plugInsURL = ::CFURLCreateFromFSRef(kCFAllocatorDefault, inPluginsRef);
	error = ScanPluginsFolder(plugInsURL);

	return error;
}


// ---------------------------------------------------------------------------
//	 ScanPluginsFolder											[private]
// ---------------------------------------------------------------------------

OSErr
CPluginsController::ScanPluginsFolder(CFURLRef inPlugInsURL)
{
	OSErr			error = noErr;
	CFArrayRef		bundleArray;

	if (inPlugInsURL != nil) {
		// Get the bundle objects for the application support's plug-ins.
		bundleArray = ::CFBundleCreateBundlesFromDirectory( kCFAllocatorDefault, inPlugInsURL, NULL );
		CFRelease( inPlugInsURL );
		
		if (bundleArray != nil) {
			CFBundleRef	bundleRef;
			CFIndex 	count = ::CFArrayGetCount(bundleArray);
			
			for ( CFIndex i = 0; i < count; i++ ) {
				bundleRef = (CFBundleRef) ::CFArrayGetValueAtIndex(bundleArray, i);
				
				if (bundleRef != nil) {
					error = AddPluginToDictionary(bundleRef);
					// No need to CFRelease bundleRef since it is obtained
					// with GetValueAtIndex
				} 
			}
			CFRelease( bundleArray );
		} 
	} 

	return error;
}


// ---------------------------------------------------------------------------
//	 AddPluginToDictionary										[private]
// ---------------------------------------------------------------------------
// It would have been also possible to retrive all the info about the
// plugins using ::CFBundleCopyInfoDictionaryInDirectory(CFURLRef bundleURL). 
// It allows to retrieve basic information about a bundle without having to
// create an instance of CFBundle.

OSErr
CPluginsController::AddPluginToDictionary(CFBundleRef inBundleRef)
{
	OSErr	error = noErr;
	CRezillaPlugin *	rezPlugin = nil;
	
	rezPlugin = new CRezillaPlugin(inBundleRef);
	if (rezPlugin != nil) {
		AddDictEntriesForPlugin(rezPlugin);
		sPluginsList.AddItem(rezPlugin);
	} else {
		error = err_PluginGetInfoFailed;
	}
		
	return error;
}


// ---------------------------------------------------------------------------
//	 AddDictEntriesForPlugin									[private]
// ---------------------------------------------------------------------------
// 					CFNumberRef thePlugRef = ::CFNumberCreate(NULL, kCFNumberSInt32Type, &inRezPlugin);
// 					if (thePlugRef) {
// 						::CFArrayAppendValue(theArray, thePlugRef);
// 					} 

OSErr
CPluginsController::AddDictEntriesForPlugin(CRezillaPlugin * inRezPlugin)
{
	OSErr	error = noErr;
	
	TArrayIterator<ResType> iterator( *inRezPlugin->GetEditTypes() );
	ResType 	theType;
	
	while (iterator.Next(theType)) {
		CFMutableArrayRef theArray;
		
		// Convert the type to a CFNumber
		CFNumberRef theValue = ::CFNumberCreate(NULL, kCFNumberSInt32Type, &theType);
		if (theValue != nil) {
			
			// If there is already an entry for this value, add the plugin 
			// to the list, otherwise create a new CFArray
			if ( ::CFDictionaryContainsKey(sPluginsDict, theValue) ) {
				theArray = (CFMutableArrayRef) ::CFDictionaryGetValue( sPluginsDict, theValue);
				::CFArrayAppendValue(theArray, &inRezPlugin);
				::CFDictionarySetValue(sPluginsDict, theValue, theArray);
			} else {
				theArray = ::CFArrayCreateMutable(NULL, 0, &kCFTypeArrayCallBacks);
				if (theArray) {
					::CFArrayAppendValue(theArray, &inRezPlugin);
				} 
				::CFDictionaryAddValue(sPluginsDict, theValue, theArray);
			}
			CFRelease(theValue);
		} 
	}
	
// 	CFShow(sPluginsDict);
	
	return error;
}

