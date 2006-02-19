// ===========================================================================
// CRezillaPlugin.cp
// 
//                       Created: 2005-09-26 09:48:26
//             Last modification: 2006-02-19 07:05:48
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes, 2005-2006
// All rights reserved.
// ===========================================================================

#include "CRezillaPlugin.h"
#include "CPluginsController.h"
#include "CRezMap.h"
#include "CRezillaApp.h"
#include "UMiscUtils.h"


// ---------------------------------------------------------------------------
//  CRezillaPlugin												[public]
// ---------------------------------------------------------------------------

CRezillaPlugin::CRezillaPlugin(CFBundleRef inBundleRef)
{
	mIsLoaded = false;
	mName = NULL;
	mPluginRef = NULL;
	mInterface = NULL;
	mRefNum = kResFileNotOpened;
	Initialize(inBundleRef);
}


// ---------------------------------------------------------------------------
//  ~CRezillaPlugin												[public]
// ---------------------------------------------------------------------------

CRezillaPlugin::~CRezillaPlugin()
{
}


// ---------------------------------------------------------------------------
//  Initialize													[public]
// ---------------------------------------------------------------------------
// mPluginVersion is an UInt32 in the 'vers' resource style (e-g 0x01008000 for 1.0.0)

void
CRezillaPlugin::Initialize(CFBundleRef inBundleRef)
{
	CFDictionaryRef bundleInfoDict;
// 	CFStringRef     propRef;
	CFArrayRef		typesArray;
	CFURLRef		plugURL = nil;
	ResType			theType;
	Str255  		theString;
	
	// Get an instance of the non-localized keys
	bundleInfoDict = ::CFBundleGetInfoDictionary(inBundleRef);

	// If successful, look for some properties
	if ( bundleInfoDict != NULL ) {
// 		propRef = ::CFDictionaryGetValue( bundleInfoDict, CFSTR("RezillaPluginRole") );
		
		typesArray = (CFArrayRef) ::CFDictionaryGetValue( bundleInfoDict, CFSTR("RezillaPluginEditTypes") );
		if (typesArray != nil) {
			CFIndex 	count = ::CFArrayGetCount(typesArray);
			for ( CFIndex i = 0; i < count; i++ ) {
				CFStringRef	typeRef;
				
				typeRef = (CFStringRef) ::CFArrayGetValueAtIndex(typesArray, i);
				if (typeRef && ::CFStringGetPascalString(typeRef, theString, sizeof(theString), ::GetApplicationTextEncoding()))
				{
					UMiscUtils::PStringToOSType(theString, theType);
					mEditTypes.AddItem(theType);
				}				
			}
		} 
	}
	
	// Get type and creator          CFPluginNameString
	plugURL = ::CFBundleCopyBundleURL(inBundleRef);
	if (plugURL != nil) {
		::CFBundleGetPackageInfoInDirectory(plugURL, &mPluginType, &mPluginCreator);
		mName = ::CFURLCopyLastPathComponent(plugURL);
		::CFRelease(plugURL);   
		::CFRetain(mName);
	} else {
		mPluginType = 0;
		mPluginCreator = 0;
	}
	
	// Get version number
	mPluginVersion = ::CFBundleGetVersionNumber(inBundleRef);
}


// ---------------------------------------------------------------------------
//  Load														[public]
// ---------------------------------------------------------------------------
// 			// Function pointer.
// 			AddOneFunctionPtr addOne = NULL;
// 			// Value returned from the loaded function.
// 			long result;
// 			// Get a pointer to the function.
// 			addOne = (void*)CFBundleGetFunctionPointerForName(
// 						myBundle, CFSTR("addOne") );
// 				// If the function was found, call it with a test value.
// 			if (addOne) 
// 			{
// 				// This should add 1 to whatever was passed in
// 				result = addOne ( 23 );

OSErr
CRezillaPlugin::Load()
{
	OSErr			error = noErr;
	CFPlugInRef		newPlugIn = NULL;
	CFURLRef		bundleURL, plugInURL;

	if (!mIsLoaded) {		
		bundleURL = CFBundleCopyBuiltInPlugInsURL( CFBundleGetMainBundle() );		
		plugInURL = CFURLCreateCopyAppendingPathComponent( NULL, bundleURL, mName, false );

		// Create a CFPlugin using the URL. This causes the plug-in's types
		// and factories to be registered with the system. The plug-in's
		// code is not actually loaded at this stage unless the plug-in is
		// using dynamic registration.
		newPlugIn = CFPlugInCreate( NULL, plugInURL );
		CFRelease(bundleURL);
		CFRelease(plugInURL);

		//  The plug-in was located, now locate the interface
		if( newPlugIn ) {
			// See if this plug-in implements the RezillaEditor type
			CFArrayRef factories = ::CFPlugInFindFactoriesForPlugInTypeInPlugIn( kRezillaEditorTypeID, newPlugIn );

			// If there are factories for the RezillaEditor type, attempt
			// to get the IUnknown interface.
			if ( factories != NULL && ::CFArrayGetCount( factories ) > 0 ) {

				// Get the factory ID for the first item in the array of IDs
				CFUUIDRef factoryID = (CFUUIDRef) ::CFArrayGetValueAtIndex( factories, 0 );

				// Use this factory ID to get an IUnknown interface 
				// (ie a handle to the IUnknown vector table).
				// Here the plug-in code is loaded.
				IUnknownVTbl **iunknown = (IUnknownVTbl **) ::CFPlugInInstanceCreate( NULL, factoryID, kRezillaEditorTypeID );
				mIsLoaded = true;
				
				// Query IUnknown for the RezillaEditor interface
				if( iunknown ) {
					(*iunknown)->QueryInterface( iunknown, ::CFUUIDGetUUIDBytes( kRezillaEditorInterfaceID ),
												 (LPVOID *)( &mInterface ) );

					// Now we are done with IUnknown
					(*iunknown)->Release( iunknown );

					if ( mInterface == NULL ) {
						CFRelease(newPlugIn);
						newPlugIn = NULL;
					}
				} else {
					CFRelease(newPlugIn);
					newPlugIn = NULL;
				}
			} else {
				CFRelease(newPlugIn);
				newPlugIn = NULL;
			}
		}
	} 
	
	mPluginRef = newPlugIn;
	
	return error;
}


// // ---------------------------------------------------------------------------
// //  GetTypesList												[public]
// // ---------------------------------------------------------------------------
// 
// void
// CRezillaPlugin::GetTypesList()
// {
// }


// ---------------------------------------------------------------------------
//  GetPluginInfo												[public]
// ---------------------------------------------------------------------------

void
CRezillaPlugin::GetPluginInfo()
{
}

// ---------------------------------------------------------------------------
//  IsSupported												[public]
// ---------------------------------------------------------------------------
// Boolean	found = false;
// ResType theType;
// if ( mEditTypes.FetchItemAt(index, &theType) ) {
// 	found = true;
// } 
// return found;

// Boolean
// CRezillaPlugin::IsSupported(ResType inType)
// {
// 	return mEditTypes.ContainsItem(inType);
// }


// ---------------------------------------------------------------------------
//  OpenResources												[public]
// ---------------------------------------------------------------------------

CRezMap *
CRezillaPlugin::OpenResources()
{
	CFURLRef	pluginsDirURL, pluginURL, baseUrl, rezUrl;
	CFBundleRef pluginRef;
	CRezMap *	theRezMap;
	CFStringRef basenameRef;
	OSErr		error = noErr;
	FSRef		fileRef;
	short		theRefnum;
	SInt16		theFork;
	FSSpec		theFileSpec;

	pluginsDirURL = CFBundleCopyBuiltInPlugInsURL( CFBundleGetMainBundle() );		
	pluginURL = CFURLCreateCopyAppendingPathComponent( NULL, pluginsDirURL, mName, false );
	CFRelease(pluginsDirURL);
	baseUrl = CFURLCreateCopyDeletingPathExtension(kCFAllocatorDefault, pluginURL);
	basenameRef = CFURLCopyLastPathComponent(baseUrl);
	CFRelease(baseUrl);
	pluginRef = CFBundleCreate(kCFAllocatorDefault, pluginURL);
	CFRelease(pluginURL);
	rezUrl = CFBundleCopyResourceURL(pluginRef, basenameRef, CFSTR("rsrc"), NULL);
	CFRelease(pluginRef);
	CFRelease(basenameRef);
	
	if (rezUrl != NULL) {
		if ( ::CFURLGetFSRef(rezUrl, &fileRef) ) {
			// Get the FSSpec from the FSRef
			error = FSGetCatalogInfo(&fileRef, kFSCatInfoNone, NULL, NULL, &theFileSpec, NULL);
			if (error == noErr) {
				error = CRezillaApp::PreOpen(theFileSpec, theFork, theRefnum);
				if (error == noErr) {
					theRezMap = new CRezMap(theRefnum);
				}
			}
		} 
		CFRelease(rezUrl);
	} 
	
	return theRezMap;
}




