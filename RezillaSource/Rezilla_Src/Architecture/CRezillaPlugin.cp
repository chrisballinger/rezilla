// ===========================================================================
// CRezillaPlugin.cp
// 
//                       Created: 2005-09-26 09:48:26
//             Last modification: 2005-09-30 16:15:32
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes, 2005
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

// CFArrayRef factories = CFPlugInFindFactoriesForPlugInTypeInPlugIn( kTestTypeID, newPlugIn );

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
				LString::CopyPStr( theString, mName);
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
// 			}

void
CRezillaPlugin::Load()
{
	if (!mIsLoaded) {
		// // // This should be done later when it is time to load the plugin's code
				//  Create a CFPlugin using the URL. This step causes the plug-in's types and factories to
				//  be registered with the system. Note that the plug-in's code is not actually loaded at
				//  this stage unless the plug-in is using dynamic registration.

		// 		CFPlugInRef		newPlugIn;
		// 		newPlugIn = CFPlugInCreate( NULL, plugInURL );
		// 		CFArrayRef factories = CFPlugInFindFactoriesForPlugInTypeInPlugIn( kTestTypeID, newPlugIn );
		
	} 
	
	// if successful
	mIsLoaded = true;
	


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




