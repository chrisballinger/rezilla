// ===========================================================================
// CTemplatesController.cp					
// 
//                       Created: 2004-08-06 12:57:55
//             Last modification: 2004-11-05 23:55:38
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


// Application Headers
#include "CTemplatesController.h"
#include "CRezillaApp.h"
#include "CEditorsController.h"
#include "CRezMap.h"
#include "CRezFile.h"
#include "CRezType.h"
#include "RezillaConstants.h"
#include "UDialogBoxHandler.h"
#include "UMessageDialogs.h"
#include "UMiscUtils.h"

// PowerPlant Headers
#include <LString.h>
#include <PP_Messages.h>
#include <PP_Resources.h>

// Standard Headers
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


CFArrayRef			CTemplatesController::sAllTypesArray;
CFArrayRef			CTemplatesController::sInternalTemplates;
CFDictionaryRef		CTemplatesController::sExternalTemplates;
CFDictionaryRef		CTemplatesController::sPreferedTemplates;
CRezMap *			CTemplatesController::sTemplatesMap = nil;
SInt16				CTemplatesController::sTemplateKind = tmpl_none;
FSRef				CTemplatesController::sTemplateFile;


// ---------------------------------------------------------------------------
//	¥ CTemplatesController											[public]
// ---------------------------------------------------------------------------
//  Object constructor. Takes care of building the various static 
// arrays. The "All Types Array" contains all the types for which a 
// template (internal or external) exists and the types stored in the 
// static CEditorsController::sAsTypeDictionary variable.

CTemplatesController::CTemplatesController()
{
	// Build the internal array
	BuildInternalTemplatesArray();
	
	// Copy it in the list of all known types
	sAllTypesArray = CFArrayCreateMutableCopy(NULL, 0, sInternalTemplates);
	
	// Build the external array. Any new type is added to sAllTypesArray.
	BuildExternalTemplatesDictionary();
	
	// Add the types registered as TypeAs types (the CEditorsController 
	// class must have been created already).
	AddAsTypesToAllTypes();
		
	// Sort the All Types Array
	CFArraySortValues( (CFMutableArrayRef) sAllTypesArray, CFRangeMake(0, CFArrayGetCount(sAllTypesArray)), 
					  (CFComparatorFunction) TypeSorter, NULL);
}


// ---------------------------------------------------------------------------
//	¥ ~CTemplatesController									[public, virtual]
// ---------------------------------------------------------------------------

CTemplatesController::~CTemplatesController()
{
}


// ---------------------------------------------------------------------------------
// 
//  ¥ BuildInternalTemplatesArray								[private]
// ---------------------------------------------------------------------------------

OSErr
CTemplatesController::BuildInternalTemplatesArray()
{
	CFBundleRef 	mainBundleRef;
	CFURLRef 		templatesURL;
	CFStringRef		typeRef;
	FSRef 			theFSRef;
	FSSpec			theFileSpec;
	OSErr	  		error = noErr;
	short			tmplRefNum, numResources;
	Str255			theName;
	CRezType * 		theRezType;

	// Locate the Templates resource file inside the main bundle
	mainBundleRef = NULL;
	templatesURL = NULL;
	
	mainBundleRef = CFBundleGetMainBundle();
	if (mainBundleRef == NULL) {
		error = fnfErr; 
		return error;
	}
	
	templatesURL = CFBundleCopyResourceURL(mainBundleRef, CFSTR("RezillaTemplates"), CFSTR("rsrc"), NULL);
	
	if (templatesURL == nil) {
		// If the file does not exist, post an alert
		UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("CouldNotFindTemplates"), rPPob_SimpleMessage);
	} else {
		if ( CFURLGetFSRef(templatesURL, &theFSRef) ) {
			// Open the resource map
			error = FSOpenResourceFile( &theFSRef, 0, nil, fsRdWrPerm, &tmplRefNum );
			error = FSGetCatalogInfo(&theFSRef, kFSCatInfoNone, NULL, NULL, &theFileSpec, NULL);
		} else {
			UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("CouldNotOpenTemplates"), rPPob_SimpleMessage);
			error = fnfErr; 
			return error;
		}
		if (error == noErr) {
			sTemplatesMap = new CRezMap(tmplRefNum);
		}
		CFRelease(templatesURL);
	}
	
	// Build the list of types (names of the TMPL resources)
	theRezType = new CRezType('TMPL', sTemplatesMap);
	
	if (theRezType) {
		sInternalTemplates = CFArrayCreateMutable(NULL, 0, &kCFTypeArrayCallBacks);
		error = theRezType->CountResources(numResources);
		if (error == noErr) {
			for ( UInt16 i = 1; i <= numResources; i++ ) {
				error = theRezType->GetNameAtIndex(i, theName);
				if (error == noErr) {
					typeRef = CFStringCreateWithPascalString(NULL, theName, kCFStringEncodingMacRoman);
					if (typeRef) {
						if ( ! CFArrayContainsValue(sInternalTemplates, CFRangeMake(0, CFArrayGetCount(sInternalTemplates)), typeRef) ) {
							CFArrayAppendValue( (CFMutableArrayRef) sInternalTemplates, typeRef);
						} 
						// It is OK to CFRelease because CFArrayAppendValue has incremented the retain count.
						CFRelease(typeRef);
					}
				}
			}
		} 
	} 
	return error;
}


// ---------------------------------------------------------------------------
//	¥ BuildExternalTemplatesDictionary								[private]
// ---------------------------------------------------------------------------
// Create a CFDictionary whose keys are the FSRefs of the resource files
// located in the various "Application Support/Rezilla/Templates" folders and
// whose values are a CFArray of the types for which a template definition
// exists.
// This function looks in different domains and creates the folders if they do
// not already exist:
// 		kSystemDomain	---> System/Library/Application Support
// 		kLocalDomain	---> Library/Application Support
// 		kUserDomain		---> ~/Library/Application Support
// 		
// 	Do we really need kSystemDomain ? kNetworkDomain ?

OSErr
CTemplatesController::BuildExternalTemplatesDictionary()
{
	OSErr					error = noErr;
	UInt32   				domainIndex;
	FSRef					appSupportRef, rezillaRef, templateRef, fileRef;
	// kUserDomain, kNetworkDomain, kLocalDomain, kSystemDomain
	static const SInt16 kFolderDomains[] = {kUserDomain, kLocalDomain, kSystemDomain, 0};
	
	// Create a mutable dictionary
	sExternalTemplates = CFDictionaryCreateMutable(NULL, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
	
	if (sExternalTemplates) {
		domainIndex = 0;
		do {
			error = FSFindFolder(kFolderDomains[domainIndex], kApplicationSupportFolderType, kCreateFolder, &appSupportRef);
			// If we can't find or create the folder in this domain, just ignore the domain.
			if (error == noErr) {
				HFSUniStr255 	unicodeName;
				ConstStr31Param rzilName = "\pRezilla";
				ConstStr31Param tmplName = "\pTemplates";
				
				// If we found the Support folder, look for a Templates subfolder
				UMiscUtils::HFSNameToUnicodeName(rzilName, &unicodeName);
				error = FSMakeFSRefUnicode(&appSupportRef, unicodeName.length, unicodeName.unicode, 
										   kTextEncodingUnknown, &rezillaRef);
				if (error != noErr) {
					error = FSCreateDirectoryUnicode(&appSupportRef, unicodeName.length, unicodeName.unicode, 
													 kFSCatInfoNone, NULL, &rezillaRef, NULL, NULL);
				}
				
				if (error == noErr) {
					UMiscUtils::HFSNameToUnicodeName(tmplName, &unicodeName);
					error = FSMakeFSRefUnicode(&rezillaRef, unicodeName.length, unicodeName.unicode, 
											   kTextEncodingUnknown, &templateRef);
					if (error != noErr) {
						error = FSCreateDirectoryUnicode(&rezillaRef, unicodeName.length, unicodeName.unicode, 
														 kFSCatInfoNone, NULL, &templateRef, NULL, NULL);
					}
					
					if (error == noErr) {
						// Iterate inside the folder to get all the file refs and inspect the
						// resources. Look for resource files only at the first level. No subfolders.
						ItemCount		actualObjects;
						FSCatalogInfo	catalogInfo;
						FSIterator		iterator;
						OSErr			result;
						
						// Open FSIterator for flat access to templateRef
						result = FSOpenIterator(&templateRef, kFSIterateFlat, &iterator);
						
						// Call FSGetCatalogInfoBulk in loop to get all items 
						// in the Templates subfolder
						do {
							result = FSGetCatalogInfoBulk(iterator, 1, &actualObjects, NULL, 
														  kFSCatInfoNodeFlags, &catalogInfo, &fileRef, NULL, NULL);
							
							if ( (result == noErr || result == errFSNoMoreItems) && (actualObjects != 0) ) {
								// Skip if it is a directory
								if ( 0 != (catalogInfo.nodeFlags & kFSNodeIsDirectoryMask) ) {
									continue;
								}
								error = AddTemplatesToDictionary(&fileRef);
							}
						} while ( result == noErr );
						
						if ( (errFSNoMoreItems == result) || (afpAccessDenied == result) ) {
							result = noErr;
						}
						FSCloseIterator(iterator);
					}
				} 			
			}
			domainIndex += 1;
		} while ( kFolderDomains[domainIndex] != 0 );
	}
	
	return error;
}


// ---------------------------------------------------------------------------
//	¥ AddTemplatesToDictionary										[private]
// ---------------------------------------------------------------------------

OSErr
CTemplatesController::AddTemplatesToDictionary(FSRef * inFileRef)
{
	OSErr		error = noErr;
	SInt16		theFork;
	short		theRefnum, numResources;
	FSSpec		theFileSpec;
	
	// Get the FSSpec from the FSRef
	error = FSGetCatalogInfo(inFileRef, kFSCatInfoNone, NULL, NULL, &theFileSpec, NULL);
	if (error == noErr) {
		error = CRezillaApp::PreOpen(theFileSpec, theFork, theRefnum, fork_anyfork);
		if (error == noErr) {
			CRezMap * rezMap = new CRezMap(theRefnum);
			if (rezMap) {
				// Build the list of types (names of the TMPL resources)
				CRezType * theRezType = new CRezType('TMPL', rezMap);
				if (theRezType) {
					error = theRezType->CountResources(numResources);
					if (error == noErr && numResources > 0) {
						// Create a CFArray to contain all the names
						CFMutableArrayRef	theArray;
						CFStringRef			nameRef;
						CFDataRef			theKey;
						Str255				theName;
						
						theKey = CFDataCreate(NULL, (const UInt8 *) inFileRef, sizeof(FSRef));
						if (theKey) {
							theArray = CFArrayCreateMutable(NULL, 0, &kCFTypeArrayCallBacks);
							if (theArray) {
								for ( UInt16 i = 1; i <= numResources; i++ ) {
									error = theRezType->GetNameAtIndex(i, theName);
									if (error == noErr) {
										nameRef = CFStringCreateWithPascalString(NULL, theName, kCFStringEncodingMacRoman);
										if (nameRef) {
											CFArrayAppendValue(theArray, nameRef);
											// Add to the sAllTypesArray in the same time
											if ( ! CFArrayContainsValue(sAllTypesArray, CFRangeMake(0, CFArrayGetCount(sAllTypesArray)), nameRef) ) {
												CFArrayAppendValue( (CFMutableArrayRef) sAllTypesArray, nameRef);
											} 
											CFRelease(nameRef);
										} 							
									}
								}
								
								// Add to the dictionary
								CFDictionaryAddValue( (CFMutableDictionaryRef) sExternalTemplates, theKey, theArray);
								CFRelease(theArray);
							} 
							CFRelease(theKey);
						} 
					} 
					delete theRezType;
				} 
				delete rezMap;
			} 
		}
	}
	
	return error;
}


// ---------------------------------------------------------------------------
//  ¥ HasTemplateForType											[static]
// ---------------------------------------------------------------------------

Boolean
CTemplatesController::HasTemplateForType(ResType inType, ResType * substType, CRezMap * inRezMap)
{
	Boolean hasTMPL = false;
	Str255	theName;

	sTemplateKind = tmpl_none;
	UMiscUtils::OSTypeToPString(inType, theName);	

	// First look for a local TMPL resource inside the RezMap itself
	if (inRezMap != NULL) {
		hasTMPL = HasLocalTemplateForType(theName, inRezMap);
	} 
	if (hasTMPL == true) {
		sTemplateKind = tmpl_local;
	} else {
		// Now look for an external TMPL resource
		hasTMPL = HasExternalTemplateForType(inType, &sTemplateFile);
		if (hasTMPL == true) {
			sTemplateKind = tmpl_external;
		} else {
			// Look for an internal TMPL
			hasTMPL = HasInternalTemplateForType(inType);
			if (hasTMPL) {
				sTemplateKind = tmpl_internal;
			} 
		}
		// If still not found, check if there is a substitution type
		if ( !hasTMPL ) {
			if ( CEditorsController::FindSubstitutionType(inType, substType) ) {
				hasTMPL = HasTemplateForType(*substType, substType, inRezMap);
			} 
		} 
	}
	
	return hasTMPL;
}


// ---------------------------------------------------------------------------
//  ¥ HasLocalTemplateForType									[static]
// ---------------------------------------------------------------------------
// Get1NamedResource() appears to be case insensitive! We must then get the
// list of resources and check the names directly.

Boolean
CTemplatesController::HasLocalTemplateForType(Str255 inName, CRezMap * inRezMap)
{
	Boolean hasTMPL = false;
	Str255	theName;
	short	theCount;
	CRezType * theRezTRype = new CRezType('TMPL', inRezMap);
	
	if (theRezTRype->CountResources(theCount) == noErr) {
		for ( UInt16 i = 1; i <= theCount; i++ ) {
			if (theRezTRype->GetNameAtIndex(i, theName) == noErr 
				&& 
				LString::CompareBytes(theName + 1, inName + 1, theName[0], inName[0]) == 0) {
					hasTMPL = true;
					break;
			} 
		}
	} 
	
	return hasTMPL;
}


// ---------------------------------------------------------------------------
//  ¥ HasInternalTemplateForType									[static]
// ---------------------------------------------------------------------------

Boolean
CTemplatesController::HasInternalTemplateForType(ResType inType)
{
	Boolean hasTMPL = false;
	Str255	theName;
	
	if (sInternalTemplates) {
		CFStringRef			typeRef;
		UMiscUtils::OSTypeToPString(inType, theName);	
		typeRef = CFStringCreateWithPascalString(NULL, theName, kCFStringEncodingMacRoman);
		if (typeRef) {
			hasTMPL = CFArrayContainsValue(sInternalTemplates, CFRangeMake(0, CFArrayGetCount(sInternalTemplates)), typeRef);
			CFRelease(typeRef);
		}
	}
	
	return hasTMPL;
}


// ---------------------------------------------------------------------------
//  ¥ HasExternalTemplateForType									[static]
// ---------------------------------------------------------------------------

Boolean
CTemplatesController::HasExternalTemplateForType(ResType inType, FSRef * outFileRef)
{
	Boolean hasTMPL = false;
	
	if (sExternalTemplates) {
		CFIndex 			dictCount;
		CFArrayRef			theArrayRef;
		CFStringRef			typeRef;
		CFDataRef			theFileRef;
		CFTypeRef *			theKeys;
		CFTypeRef *			theVals;
		Str255				theName;
		int					i;
		
		UMiscUtils::OSTypeToPString(inType, theName);	
		typeRef = CFStringCreateWithPascalString(NULL, theName, kCFStringEncodingMacRoman);
		
		if (typeRef) {
			CFIndex retcount = CFGetRetainCount(sExternalTemplates);
			dictCount = CFDictionaryGetCount(sExternalTemplates);
			// Allocate memory to store the keys and values
			theKeys = (CFTypeRef*) NewPtrClear(sizeof(CFTypeRef) * dictCount);
			theVals = (CFTypeRef*) NewPtrClear(sizeof(CFTypeRef) * dictCount);
			
			if ((theKeys != NULL) && (theVals != NULL)) {
				// Fill the keys and values from this dictionary
				CFDictionaryGetKeysAndValues(sExternalTemplates, (const void **) theKeys, (const void **) theVals);
				// Loop over all the entries
				for (i = 0; i < dictCount; i++) {
					if (theKeys[i] && theVals[i] ) {
						theArrayRef = (CFArrayRef) theVals[i];
						// Let's be paranoid: check that it is an array
						if (CFGetTypeID(theArrayRef) == CFArrayGetTypeID()) {
							hasTMPL = CFArrayContainsValue(theArrayRef, CFRangeMake(0, CFArrayGetCount(theArrayRef)), typeRef);
							if (hasTMPL) {
								theFileRef = (CFDataRef) theKeys[i];
								if (CFDataGetLength(theFileRef) == sizeof(FSRef)) {
									BlockMoveData(CFDataGetBytePtr(theFileRef), outFileRef, sizeof(FSRef));
								} 
								break;
							} 
						} 
					} 
				}
			}
			if (theKeys) DisposePtr( (char *) theKeys);
			if (theVals) DisposePtr( (char *) theVals);
			CFRelease(typeRef);
		} 
	} 
	
	return hasTMPL;
}


// ---------------------------------------------------------------------------
//	¥ GetTemplateHandle										[static]
// ---------------------------------------------------------------------------

 Handle
CTemplatesController::GetTemplateHandle(ResType inType)
{
	Handle		theHandle = nil;
	Str255		typeName;
	OSErr		error;
	
	UMiscUtils::OSTypeToPString(inType, typeName);
	
	switch (sTemplateKind) {
		case tmpl_internal:
		CRezType *	theRezType = new CRezType('TMPL', sTemplatesMap);
		
		if (theRezType != NULL) {
			error = theRezType->GetWithName(typeName, theHandle);
			if (error == noErr) {
				::DetachResource(theHandle);
			}
			delete theRezType;
		} 
		break;
		
		case tmpl_external: {
			FSSpec		theFileSpec;
			SInt16		theFork;
			short		theRefnum;

			// Get the FSSpec from the FSRef
			error = FSGetCatalogInfo(&sTemplateFile, kFSCatInfoNone, NULL, NULL, &theFileSpec, NULL);
			if (error == noErr) {
				error = CRezillaApp::PreOpen(theFileSpec, theFork, theRefnum, fork_anyfork);
				if (error == noErr) {
					CRezMap * rezMap = new CRezMap(theRefnum);
					if (rezMap) {
						CRezType * theRezType = new CRezType('TMPL', rezMap);
						if (theRezType) {
							error = theRezType->GetWithName(typeName, theHandle);
							if (error == noErr) {
								::DetachResource(theHandle);
							}
							delete theRezType;
						}
						delete rezMap;
					}
				}
			}
			break;
		}
	}
	
	return theHandle;
}
 

// ---------------------------------------------------------------------------
//	¥ AddAsTypesToAllTypes										[static]
// ---------------------------------------------------------------------------

void
CTemplatesController::AddAsTypesToAllTypes()
{
	if (CEditorsController::sAsTypeDictionary != NULL) {
		CFStringRef theStringRef;
		
		CFIndex dictCount = CFDictionaryGetCount( (CFDictionaryRef) CEditorsController::sAsTypeDictionary);
		// Allocate memory to store the keys
		CFStringRef * theKeys = (CFStringRef*) NewPtrClear(sizeof(CFStringRef) * dictCount);
		if (theKeys != NULL) {
			CFDictionaryGetKeysAndValues( (CFDictionaryRef) CEditorsController::sAsTypeDictionary, (const void **) theKeys, NULL);
			for (int i = 0; i < dictCount; i++) {
				if (theKeys[i]) {
					theStringRef = (CFStringRef) theKeys[i];
					// Add to the sAllTypesArray if it is not already in
					if ( ! CFArrayContainsValue(sAllTypesArray, CFRangeMake(0, CFArrayGetCount(sAllTypesArray)), theStringRef) ) {
						CFArrayAppendValue( (CFMutableArrayRef) sAllTypesArray, theStringRef);
					} 
					CFRelease(theStringRef);
				} 
			}
			DisposePtr( (char *) theKeys);
		} 
	} 
}


// ---------------------------------------------------------------------------
//	¥ TypeSorter										[static]
// ---------------------------------------------------------------------------

CFComparisonResult
CTemplatesController::TypeSorter(const void *lhs, const void *rhs, void *context)
{
#pragma unused(context)
	return CFStringCompare( (CFStringRef) lhs, (CFStringRef) rhs, kCFCompareCaseInsensitive);
}




