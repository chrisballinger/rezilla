// ===========================================================================
// CRezillaPlugin.cp
// 
//                       Created: 2005-09-26 09:48:26
//             Last modification: 2006-02-16 14:43:10
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes, 2005-2006
// All rights reserved.
// ===========================================================================

#include "CRezillaPlugin.h"
#include "CPluginsController.h"
#include "UMiscUtils.h"


// ---------------------------------------------------------------------------
//  CRezillaPlugin												[public]
// ---------------------------------------------------------------------------

CRezillaPlugin::CRezillaPlugin(CFBundleRef inBundleRef)
{
	mIsLoaded = false;
	mName[0] = 0;
	mPluginRef = NULL;
	mInterface = NULL;
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
// mPluginVersion is an UInt32 in the 'vers' resource style (e-g 0x01008000
// for 1.0.0)

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
	
	// Get type and creator
	plugURL = ::CFBundleCopyBundleURL(inBundleRef);
	if (plugURL != nil) {
		::CFBundleGetPackageInfoInDirectory(plugURL, &mPluginType, &mPluginCreator);
		CFStringRef nameRef = ::CFURLCopyLastPathComponent(plugURL);
		if (nameRef != nil) {
			if (::CFStringGetPascalString(nameRef, theString, sizeof(theString), ::GetApplicationTextEncoding())) {
				LString::CopyPStr(theString, mName);
			} 
			::CFRelease(nameRef);   
		}				
		::CFRelease(plugURL);   
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
		CFStringRef nameRef = ::CFStringCreateWithPascalString(kCFAllocatorDefault, mName, kCFStringEncodingMacRoman);
		
		bundleURL = CFBundleCopyBuiltInPlugInsURL( CFBundleGetMainBundle() );		
		plugInURL = CFURLCreateCopyAppendingPathComponent( NULL, bundleURL, nameRef, false );
		CFRelease(nameRef);

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




