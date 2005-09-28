// ===========================================================================
// CRezillaPlugin.cp
// 
//                       Created: 2005-09-26 09:48:26
//             Last modification: 2005-09-27 10:17:36
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CRezillaPlugin.h"


// ---------------------------------------------------------------------------
//  CRezillaPlugin												[public]
// ---------------------------------------------------------------------------

CRezillaPlugin::CRezillaPlugin(CFBundleRef inBundleRef)
{
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
// 				// This is the ‘vers’ resource style value for 1.0.0
// 				  #define kMyBundleVersion1 0x01008000
// 				  UInt32  bundleVersion;
// 				  // Look for the bundle’s version number. 
// 				  bundleVersion = CFBundleGetVersionNumber( mainBundle );
// 				  // Check the bundle version for compatibility with the app.
// 				  if (bundleVersion < kMyBundleVersion1)
// 					  return (kErrorFatalBundleTooOld);
	  
// 				CFDictionaryRef bundleInfoDict;
// 				CFStringRef     myPropertyString;
// 				// Get an instance of the non-localized keys.
// 				bundleInfoDict = CFBundleGetInfoDictionary( myBundle );
// 				// If we succeeded, look for our property.
// 				if ( bundleInfoDict != NULL ) {
// 					myPropertyString = CFDictionaryGetValue( bundleInfoDict, 
// 															CFSTR("MyPropertyKey") );
// 				}

void
CRezillaPlugin::Initialize(CFBundleRef inBundleRef)
{
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




