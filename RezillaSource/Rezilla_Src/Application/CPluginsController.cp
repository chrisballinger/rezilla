// ===========================================================================
// CPluginsController.cp
// 
//                       Created: 2005-09-26 09:48:26
//             Last modification: 2006-10-10 10:39:33
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes, 2005-2006
// All rights reserved.
// ===========================================================================

#include "CPluginsController.h"
#include "CRezillaPlugin.h"
#include "CPluginEditorDoc.h"
#include "CRezMapDoc.h"
#include "CRezMapTable.h"
#include "CRezMapWindow.h"
#include "CRezObjItem.h"
#include "CEditorsController.h"
#include "UMiscUtils.h"
#include "RezillaConstants.h"

CFMutableDictionaryRef		CPluginsController::sPluginsDict = NULL;
CFDictionaryRef				CPluginsController::sPrefsDict = NULL;
TArray<CRezillaPlugin*>		CPluginsController::sPluginsList;


// ---------------------------------------------------------------------------
//  CPluginsController												[public]
// ---------------------------------------------------------------------------

CPluginsController::CPluginsController()
{
	BuildPluginsDictionary();
	RetrieveFromPreferences();
	if (sPrefsDict != NULL) {
		AdjustDictionaryWithPrefs();
	} 
}


// ---------------------------------------------------------------------------
//  ~CPluginsController												[public]
// ---------------------------------------------------------------------------

CPluginsController::~CPluginsController()
{
	StoreInPreferences();
	
	TArrayIterator<CRezillaPlugin*> iterator(sPluginsList, LArrayIterator::from_End);
	CRezillaPlugin *	thePlugin;
	while (iterator.Previous(thePlugin)) {
		sPluginsList.RemoveItemsAt(1, iterator.GetCurrentIndex());
		delete thePlugin;
	}
	
	if (sPluginsDict) {
		::CFRelease(sPluginsDict);
	}
	if (sPrefsDict) {
		::CFRelease(sPrefsDict);
	}
}


// ---------------------------------------------------------------------------
//  HasPluginForType												[public]
// ---------------------------------------------------------------------------

Boolean
CPluginsController::HasPluginForType(ResType inType, ResType * substTypePtr)
{
	Boolean hasPlugin = false;
	
	CFNumberRef theKey = ::CFNumberCreate(NULL, kCFNumberSInt32Type, &inType);

	if (theKey != nil) {
		hasPlugin = ::CFDictionaryContainsKey(sPluginsDict, theKey);
		CFRelease(theKey);
	}
	
	// If not found, check if there is a possible substitution type
	if ( !hasPlugin ) {
		if ( CEditorsController::FindSubstitutionType(inType, substTypePtr) ) {
			hasPlugin = HasPluginForType(*substTypePtr, substTypePtr);
		} 
	} 

	return hasPlugin;
}


// ---------------------------------------------------------------------------
//   InvokePluginEditor											[public]
// ---------------------------------------------------------------------------

void
CPluginsController::InvokePluginEditor(CRezMapDoc* inRezMapDoc, 
									   CRezObjItem * inRezObjItem,
									   ResType inUseType)
{
	CRezMapTable *	inSuperMap = inRezMapDoc->GetRezMapWindow()->GetRezMapTable();
	CRezObj *		inRezObj = inRezObjItem->GetRezObj();
	Boolean			inReadOnly = inRezMapDoc->IsReadOnly();
	
	CRezillaPlugin * thePlugin = GetPreferredPlugin(inUseType);
	
	new CPluginEditorDoc( (LCommander *) inRezMapDoc, inSuperMap, inRezObj, inUseType, inReadOnly, thePlugin);
}


// ---------------------------------------------------------------------------
//  GetPreferredPlugin												[public]
// ---------------------------------------------------------------------------

CRezillaPlugin *
CPluginsController::GetPreferredPlugin(ResType inType)
{
	OSErr				error = noErr;
	CRezillaPlugin *	thePlugin = NULL;
	CFArrayRef			theArray;
	void *				valuePtr;
	CFNumberRef 		typeRef;
	
	typeRef = ::CFNumberCreate(NULL, kCFNumberSInt32Type, &inType);
	theArray = (CFArrayRef) ::CFDictionaryGetValue( sPluginsDict, typeRef);
	CFRelease(typeRef);
	
	// Just pick the first one in the list
	typeRef = (CFNumberRef) ::CFArrayGetValueAtIndex(theArray, 0);
	if ( ::CFNumberGetValue(typeRef, kCFNumberSInt32Type, (void*) &valuePtr) ) {
		thePlugin = (CRezillaPlugin*) valuePtr;
	} 

	return thePlugin;
}


// ---------------------------------------------------------------------------
//  SetPreferredPlugin												[public]
// ---------------------------------------------------------------------------

OSErr
CPluginsController::SetPreferredPlugin(ResType inType, CRezillaPlugin * inPlugin)
{
	OSErr				error = noErr;
	CFNumberRef 		typeRef, thePlugRef;
	CFMutableArrayRef	theArray;
	CFIndex				index;

	typeRef = ::CFNumberCreate(NULL, kCFNumberSInt32Type, &inType);
	theArray = (CFMutableArrayRef) ::CFDictionaryGetValue( sPluginsDict, typeRef);
	CFRelease(typeRef);
	
	if (inPlugin != NULL) {
		thePlugRef = ::CFNumberCreate(NULL, kCFNumberSInt32Type, &inPlugin);
		if (thePlugRef) {
			index = ::CFArrayGetFirstIndexOfValue(theArray, ::CFRangeMake(0, ::CFArrayGetCount(theArray)), thePlugRef);
			CFRelease(thePlugRef);
			if (index == kCFNotFound) {
				error = err_PluginIndexNotFound;
			} else if (index > 0) {
				::CFArrayExchangeValuesAtIndices(theArray, 0, index);
			} 
		}
	}
	return error;
}


// ---------------------------------------------------------------------------
//	 BuildPluginsDictionary							[private]
// ---------------------------------------------------------------------------
// Create a CFDictionary associating resource types to a CFArray of
// pointers to CRezillaPlugin instances supporting this type. The function
// scans the internal PlugIns subfolder inside the application bundle.

OSErr
CPluginsController::BuildPluginsDictionary()
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
//	 ScanPluginsFolder											[private]
// ---------------------------------------------------------------------------
// Look for the plugin bundles in the PlugIns directory.

OSErr
CPluginsController::ScanPluginsFolder(FSRef * inPluginsRef)
{
	OSErr			error = noErr;
	CFURLRef		pluginsURL = nil;

	// Get a CFURL from the FSRef
	pluginsURL = ::CFURLCreateFromFSRef(kCFAllocatorDefault, inPluginsRef);
	if (pluginsURL != nil) {
		error = ScanPluginsFolder(pluginsURL);
		CFRelease(pluginsURL);
	}

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

	// Get the bundle objects for the application support's plug-ins.
	bundleArray = ::CFBundleCreateBundlesFromDirectory( kCFAllocatorDefault, inPlugInsURL, NULL );
	
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

	return error;
}


// ---------------------------------------------------------------------------
//	 AddPluginToDictionary										[private]
// ---------------------------------------------------------------------------
// It would have been also possible to retrieve all the info about the
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
		AddEntriesForPlugin(rezPlugin);
		sPluginsList.AddItem(rezPlugin);
	} else {
		error = err_PluginGetInfoFailed;
	}
		
	return error;
}


// ---------------------------------------------------------------------------
//	 AddEntriesForPlugin									[private]
// ---------------------------------------------------------------------------

OSErr
CPluginsController::AddEntriesForPlugin(CRezillaPlugin * inRezPlugin)
{
	OSErr	error = noErr;
	
	TArrayIterator<ResType> iterator( *inRezPlugin->GetEditTypes() );
	ResType 	theType;
	
	while (iterator.Next(theType)) {
		CFMutableArrayRef theArray;
		
		// Convert the type to a CFNumber
		CFNumberRef theKey = ::CFNumberCreate(NULL, kCFNumberSInt32Type, &theType);

		if (theKey != nil) {
			CFNumberRef theRezPlugin = ::CFNumberCreate(NULL, kCFNumberSInt32Type, &inRezPlugin);
			if (theRezPlugin != nil) {
				// If there is already an entry for this value, add the plugin 
				// to the list, otherwise create a new CFArray
				if ( ::CFDictionaryContainsKey(sPluginsDict, theKey) ) {
					theArray = (CFMutableArrayRef) ::CFDictionaryGetValue( sPluginsDict, theKey);
					::CFArrayAppendValue(theArray, theRezPlugin);
					::CFDictionarySetValue(sPluginsDict, theKey, theArray);
				} else {
					theArray = ::CFArrayCreateMutable(NULL, 0, &kCFTypeArrayCallBacks);
					if (theArray) {
						::CFArrayAppendValue(theArray, theRezPlugin);
						::CFDictionaryAddValue(sPluginsDict, theKey, theArray);
						CFRelease(theArray);
					} 
				}
				CFRelease(theRezPlugin);
			} 
			CFRelease(theKey);
		} 
	}
		
	return error;
}


// ---------------------------------------------------------------------------------
//   StoreInPreferences 
// ---------------------------------------------------------------------------------
// Only the resource types corresponding to multiple plugins are stored in
// the preferences as a dictionary of types/plugins pairs. 

void
CPluginsController::StoreInPreferences() 
{	
	CFMutableDictionaryRef	tempDict;
	CFMutableArrayRef	tempArray;	
	CFIndex 			i, j, dictCount, tempCount;
	CFArrayRef			theArrayRef;
	CFTypeRef *			theKeys;
	CFTypeRef *			theVals;
	CFNumberRef			thePlugRef;
	CFStringRef			theNameRef, theTypeRef;
	CRezillaPlugin *	thePlugin;
	ResType				theType;
	Str255				theString;
	
	tempDict = ::CFDictionaryCreateMutable(NULL, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);

	if (tempDict) {
		dictCount = ::CFDictionaryGetCount(sPluginsDict);
		// Allocate memory to store the keys and values
		theKeys = (CFTypeRef*) NewPtrClear(sizeof(CFTypeRef) * dictCount);
		theVals = (CFTypeRef*) NewPtrClear(sizeof(CFTypeRef) * dictCount);
		
		if ((theKeys != NULL) && (theVals != NULL)) {
			// Fill the keys and values from this dictionary
			::CFDictionaryGetKeysAndValues(sPluginsDict, (const void **) theKeys, (const void **) theVals);
			// Loop over all the entries
			for (i = 0; i < dictCount; i++) {
				if (theKeys[i] && theVals[i] ) {
					theArrayRef = (CFArrayRef) theVals[i];
					
					tempCount = ::CFArrayGetCount(theArrayRef);
					if (tempCount > 1) {
						// Create an array of plugin names
						tempArray = ::CFArrayCreateMutable(NULL, 0, &kCFTypeArrayCallBacks);

						if (tempArray) {
							for ( j = 0; j < tempCount; j++ ) {								
								thePlugRef = (CFNumberRef) ::CFArrayGetValueAtIndex(theArrayRef, j);
								thePlugin = NULL;
								
								if (thePlugRef != nil) {
									if (::CFNumberGetValue( (CFNumberRef) thePlugRef, kCFNumberSInt32Type, (void *) &thePlugin)) {
										if (thePlugin) {
											theNameRef = thePlugin->GetName();
											if (theNameRef) {
												::CFArrayAppendValue(tempArray, theNameRef);
											} 
										}
									}
								}
							}
							// Make a CFString for the type
							if (::CFNumberGetValue( (CFNumberRef) theKeys[i], kCFNumberSInt32Type, (void *) &theType)) {
								UMiscUtils::OSTypeToPString(theType, theString);
								theTypeRef = ::CFStringCreateWithPascalString(NULL, theString, kCFStringEncodingMacRoman);
								if (theTypeRef) {
									// Write the resType/namesArray pair in the dictionary
									::CFDictionaryAddValue(tempDict, theTypeRef, tempArray);
									::CFRelease(theTypeRef);
								} 
							}
							::CFRelease(tempArray);
						}
					} 
				}
			}
		}
		
		if ( ::CFDictionaryGetCount(tempDict) > 0 ) {
			// Write the temp dictionary in the preferences
			::CFPreferencesSetAppValue(CFSTR("pref_PluginsOrder"), tempDict, kCFPreferencesCurrentApplication);
		} 
		::CFRelease(tempDict);
	}
		
	if (theKeys) DisposePtr( (char *) theKeys);
	if (theVals) DisposePtr( (char *) theVals);

	
	// Flush the prefs to disk
	::CFPreferencesAppSynchronize( CFSTR(kRezillaIdentifier) );
}


// ---------------------------------------------------------------------------------
//   RetrieveFromPreferences 
// ---------------------------------------------------------------------------------
// sPrefsDict is the dict of plugins preferred order stored in the
// preferences file: the keys are resource types and the values are a list
// of plugin names.

void
CPluginsController::RetrieveFromPreferences() 
{	
	CFPropertyListRef theDict = ::CFPreferencesCopyAppValue(CFSTR("pref_PluginsOrder"), CFSTR(kRezillaIdentifier));
	
	if (theDict) {
		sPrefsDict = ::CFDictionaryCreateCopy(NULL, (CFDictionaryRef) theDict);
		::CFRelease(theDict);
	}
}


// ---------------------------------------------------------------------------------
//   AdjustDictionaryWithPrefs 
// ---------------------------------------------------------------------------------
// Once the sPluginsDict is built, compare it with the plugins order found
// in the preferences and reorder the plugins as necessary

void
CPluginsController::AdjustDictionaryWithPrefs() 
{	
	CFTypeRef *			theKeys;
	CFTypeRef *			theVals;
	CFIndex 			i, dictCount;
	Str255				theString;
	ResType				theType;
	CFNumberRef			theKeyRef;
	CFMutableArrayRef	oldArrayRef, newArrayRef;

	dictCount = ::CFDictionaryGetCount(sPrefsDict);
	// Allocate memory to store the keys and values
	theKeys = (CFTypeRef*) NewPtrClear(sizeof(CFTypeRef) * dictCount);
	theVals = (CFTypeRef*) NewPtrClear(sizeof(CFTypeRef) * dictCount);
	
	if ((theKeys != NULL) && (theVals != NULL)) {
		// Fill the keys and values from this dictionary
		::CFDictionaryGetKeysAndValues(sPrefsDict, (const void **) theKeys, (const void **) theVals);
		// Loop over all the entries
		for (i = 0; i < dictCount; i++) {
			if (theKeys[i] && theVals[i] ) {
				// Make a CFNumber out of the type
				if ( ::CFStringGetPascalString( (CFStringRef)theKeys[i], theString, sizeof(theString), NULL) ) {
					UMiscUtils::PStringToOSType(theString, theType);
					theKeyRef = ::CFNumberCreate(NULL, kCFNumberSInt32Type, &theType);
					if (theKeyRef) {
						// Find the corresponding entry in the plugins dict
						if ( ::CFDictionaryGetValueIfPresent( (CFDictionaryRef) sPluginsDict, theKeyRef, (const void**) &oldArrayRef) ) {
							newArrayRef = ReorderPluginsArray((CFArrayRef) theVals[i], oldArrayRef);
							if (newArrayRef) {
								::CFDictionaryReplaceValue(sPluginsDict, theKeyRef, newArrayRef);
								::CFRelease(newArrayRef);
							} 
						} 
						::CFRelease(theKeyRef);
					} 
				}
			}
		}
	}
}


// ---------------------------------------------------------------------------------
//   ReorderPluginsArray 
// ---------------------------------------------------------------------------------
// Parse both the array from the preferences file and the array built by
// BuildPluginsDictionary and return a new array in which:
//     * common plugins come first and in the preferred order
//     * plugins listed in the preferences but not existing anymore are removed
//     * new plugins not listed in the preferences are appended
//     
// Note that inPrefArray is an array of plugin names and inOldArray is an
// array of CRezillaPlugin objects.

CFMutableArrayRef
CPluginsController::ReorderPluginsArray(CFArrayRef inPrefArray, CFMutableArrayRef inOldArray) 
{	
	CFMutableArrayRef	newArray;
	CFIndex				i, theCount, theIndex;
	CFStringRef			theName;
	CRezillaPlugin *	thePlugin;
	CFNumberRef			thePlugRef;

	newArray = ::CFArrayCreateMutable(NULL, 0, &kCFTypeArrayCallBacks);
	if (newArray) {
		theCount = ::CFArrayGetCount(inPrefArray);
		// Parse the prefs array
		for ( i = 0; i < theCount; i++ ) {								
			theName = (CFStringRef) ::CFArrayGetValueAtIndex(inPrefArray, i);
			thePlugin = GetPluginByName(theName);
			if (thePlugin != NULL) {
				thePlugRef = ::CFNumberCreate(NULL, kCFNumberSInt32Type, &thePlugin);

				if (thePlugRef) {
					// Is it present in the old array?
					theIndex = ::CFArrayGetFirstIndexOfValue(inOldArray, ::CFRangeMake(0, ::CFArrayGetCount(inOldArray)), thePlugRef);
					if (theIndex != kCFNotFound) {
						::CFArrayAppendValue(newArray, thePlugRef);
						::CFArrayRemoveValueAtIndex(inOldArray, theIndex);
					} 
					::CFRelease(thePlugRef);
				} 
			} 
		}
		// Append all the elements remaining in the old array
		CFArrayAppendArray(newArray, inOldArray, ::CFRangeMake(0, CFArrayGetCount(inOldArray)));
	} 
	return newArray;
}


// ---------------------------------------------------------------------------------
//   GetPluginByName 
// ---------------------------------------------------------------------------------

CRezillaPlugin *
CPluginsController::GetPluginByName(CFStringRef inName) 
{
	CRezillaPlugin		*thePlugin = NULL, *currPlugin;
	
	TArrayIterator<CRezillaPlugin*> iterator(sPluginsList);
	while (iterator.Next(currPlugin)) {
		if ( ::CFStringCompare( currPlugin->GetName(), inName, 0 ) == kCFCompareEqualTo ) {
			thePlugin = currPlugin;
			break;
		} 
	}
	
	return thePlugin;
}


