// ===========================================================================
// CPluginsController.cp
// 
//                       Created: 2005-09-26 09:48:26
//             Last modification: 2005-09-27 12:18:55
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CPluginsController.h"
#include "CRezillaPlugin.h"
#include "UMiscUtils.h"

CFDictionaryRef		CPluginsController::sPluginsDict;


// ---------------------------------------------------------------------------
//  CPluginsController												[public]
// ---------------------------------------------------------------------------

CPluginsController::CPluginsController()
{
	BuildPluginsDictionary();
}


// ---------------------------------------------------------------------------
//  ~CPluginsController												[public]
// ---------------------------------------------------------------------------

CPluginsController::~CPluginsController()
{
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
//	 BuildPluginsDictionary										[private]
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
CPluginsController::BuildPluginsDictionary()
{
	OSErr					error = noErr;
	UInt32   				domainIndex;
	FSRef					appSupportRef, rezillaRef, pluginsRef;
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
// Iterate inside the folder to get all the file refs and inspect the
// plugins. Look for plugin bundles only at the first level. No subfolders.

// 		EXTERN_API_C( CFArrayRef )
// 		CFBundleCreateBundlesFromDirectory(
// 		  CFAllocatorRef   allocator,
// 		  CFURLRef         directoryURL,
// 		  CFStringRef      bundleType);
// 				
// 				CFURLRef bundleURL;
// 				CFBundleRef myBundle;
// 				// Make a CFURLRef from the CFString representation of the 
// 				// bundle’s path.
// 				bundleURL = CFURLCreateWithFileSystemPath(
// 								kCFAllocatorDefault, 
// 								CFSTR("/Local/Library/MyBundle.bundle"),
// 								kCFURLPOSIXPathStyle,
// 								true );
// 				// Make a bundle instance using the URLRef.
// 				myBundle = CFBundleCreate( kCFAllocatorDefault, bundleURL );
// 				// Any CF objects returned from functions with "create" or 
// 				// "copy" in their names must be released by us!
// 				CFRelease( bundleURL );
// 				CFRelease( myBundle );
// 
// 
// 				CFBundleRef mainBundle = CFBundleGetMainBundle();
// 				CFURLRef plugInsURL;
// 				CFArrayRef bundleArray;
// 				// Get the URL to the application’s PlugIns directory.
// 				plugInsURL = CFBundleCopyBuiltInPlugInsURL(mainBundle);
// 				// Get the bundle objects for the application’s plug-ins.
// 				bundleArray = CFBundleCreateBundlesFromDirectory( kCFAllocatorDefault,
// 									plugInsURL, NULL );
// 				// Release the CF objects
// 				CFRelease( plugInsURL );
// 				CFRelease( bundleArray );


OSErr
CPluginsController::ScanPluginsFolder(FSRef * inPluginsRef)
{
	OSErr			error = noErr;
	CFArrayRef		bundleArray;
	CFURLRef		plugInsURL = nil;

	// Get a CFURL from the FSRef
	plugInsURL = ::CFURLCreateFromFSRef(kCFAllocatorDefault, inPluginsRef);

	if (plugInsURL != nil) {
		// Get the bundle objects for the application support’s plug-ins.
		bundleArray = ::CFBundleCreateBundlesFromDirectory( kCFAllocatorDefault, plugInsURL, NULL );
		CFRelease( plugInsURL );
		
		if (bundleArray != nil) {
			CFBundleRef	bundleRef;
			CFIndex 	count = ::CFArrayGetCount(bundleArray);
			
			for ( CFIndex i = 0; i < count; i++ ) {
				bundleRef = (CFBundleRef) ::CFArrayGetValueAtIndex(bundleArray, i);
				
// 				error = AddPluginToDictionary(&bundleRef);


			}
			CFRelease( bundleArray );
		} 
	} 

	return error;
}


// ---------------------------------------------------------------------------
//	 AddPluginToDictionary										[private]
// ---------------------------------------------------------------------------
// To get the path of the bundle itself, you can use theCFBundleCopyBundleURL
// function. Core Foundation always returns bundle paths in a CFURLRef object.
// You can use this object to extract a CFStringRef that you can then pass to
// other Core Foundation routines.

// OSErr
// CPluginsController::AddPluginToDictionary(FSRef * inFileRef)
// {
// 	OSErr	error = noErr;
// 	CRezillaPlugin *	rezPlugin;
// 	
// 	rezPlugin = new CRezillaPlugin(inFileRef);
// 	
// 	return error;
// }

// 				CFDictionaryRef bundleInfoDict;
// 				CFStringRef     myPropertyString;
// 				// Get an instance of the non-localized keys.
// 				bundleInfoDict = CFBundleGetInfoDictionary( myBundle );
// 				// If we succeeded, look for our property.
// 				if ( bundleInfoDict != NULL ) {
// 					myPropertyString = CFDictionaryGetValue( bundleInfoDict, 
// 															CFSTR("MyPropertyKey") );
// 				}

OSErr
CPluginsController::AddPluginToDictionary(CFBundleRef inBundleRef)
{
	OSErr	error = noErr;
	CRezillaPlugin *	rezPlugin;
	
	rezPlugin = new CRezillaPlugin(inBundleRef);
	
	return error;
}

// 			EXTERN_API_C( CFTypeRef )
// 			CFBundleGetValueForInfoDictionaryKey(
// 			  CFBundleRef   bundle,
// 			  CFStringRef   key);

// 		/* This API is provided to enable developers to retrieve basic information */
// 		/* about a bundle without having to create an instance of CFBundle. */
// 		/*
// 		 *  CFBundleCopyInfoDictionaryInDirectory()
// 		 *  
// 		 *  Availability:
// 		 *    Non-Carbon CFM:   not available
// 		 *    CarbonLib:        in CarbonLib 1.0 and later
// 		 *    Mac OS X:         in version 10.0 and later
// 		 */
// 		EXTERN_API_C( CFDictionaryRef )
// 		CFBundleCopyInfoDictionaryInDirectory(CFURLRef bundleURL);
// 
// 
// 		/*
// 		 *  CFBundleGetPackageInfoInDirectory()
// 		 *  
// 		 *  Availability:
// 		 *    Non-Carbon CFM:   not available
// 		 *    CarbonLib:        in CarbonLib 1.1 and later
// 		 *    Mac OS X:         in version 10.0 and later
// 		 */
// 		EXTERN_API_C( Boolean )
// 		CFBundleGetPackageInfoInDirectory(
// 		  CFURLRef   url,
// 		  UInt32 *   packageType,
// 		  UInt32 *   packageCreator);

