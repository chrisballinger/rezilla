// ===========================================================================
// CTemplatesController.cp					
// 
//                       Created: 2004-08-06 12:57:55
//             Last modification: 2004-08-10 21:57:55
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
#include <PP_Messages.h>
#include <PP_Resources.h>

// Standard Headers
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


TArray<OSType>		CTemplatesController::sInternalTemplates;
CRezMap *			CTemplatesController::sTemplatesMap = nil;
SInt16				CTemplatesController::sTemplateKind = tmpl_none;
CFDictionaryRef		CTemplatesController::sExternalTemplates;
CFDictionaryRef		CTemplatesController::sPreferedTemplates;
FSRef				CTemplatesController::sTemplateFile;


// ---------------------------------------------------------------------------
//	¥ CTemplatesController											[public]
// ---------------------------------------------------------------------------
//  Object constructor

CTemplatesController::CTemplatesController()
{
	RegisterInternalTemplates();
	sExternalTemplates = BuildExternalTemplatesDictionary();
}


// ---------------------------------------------------------------------------
//	¥ ~CTemplatesController									[public, virtual]
// ---------------------------------------------------------------------------

CTemplatesController::~CTemplatesController()
{
}


// ---------------------------------------------------------------------------------
//  ¥ RegisterInternalTemplates								[private]
// ---------------------------------------------------------------------------------

OSErr
CTemplatesController::RegisterInternalTemplates()
{
	CFBundleRef 	mainBundleRef;
	CFURLRef 		templatesURL;
	FSRef 			theFSRef;
	FSSpec			theFileSpec;
	OSErr	  		error = noErr;
	short			tmplRefNum, numResources;
	ResType			theType;
	Str255			theName;
	
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
	CRezType * theRezType = new CRezType('TMPL', sTemplatesMap);
	error = theRezType->CountResources(numResources);
	if (error == noErr) {
		for ( UInt16 i = 1; i <= numResources; i++ ) {
			error = theRezType->GetNameAtIndex(i, theName);
			if (error == noErr) {
				UMiscUtils::PStringToOSType(theName, theType);
				sInternalTemplates.AddItem(theType);
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

CFDictionaryRef
CTemplatesController::BuildExternalTemplatesDictionary()
{
	OSErr					error = noErr;
	UInt32   				domainIndex;
	CFMutableDictionaryRef	theDict = NULL;
	FSRef					appSupportRef, rezillaRef, templateRef, fileRef;
	// 	static const SInt16 kFolderDomains[] = {kUserDomain, kNetworkDomain, kLocalDomain, kSystemDomain, 0};
	static const SInt16 kFolderDomains[] = {kUserDomain, kLocalDomain, kSystemDomain, 0};
	
	// Create a mutable dictionary
	theDict = CFDictionaryCreateMutable(NULL, 0, NULL, NULL);
	
	if (theDict) {
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
								error = AddTemplatesToDictionary(&fileRef, theDict);
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
	
	return theDict;
}


// ---------------------------------------------------------------------------
//	¥ AddTemplatesToDictionary										[private]
// ---------------------------------------------------------------------------

OSErr
CTemplatesController::AddTemplatesToDictionary(FSRef * inFileRef, CFMutableDictionaryRef inDict)
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
			
			// Build the list of types (names of the TMPL resources)
			CRezType * theRezType = new CRezType('TMPL', rezMap);
			error = theRezType->CountResources(numResources);
			if (error == noErr && numResources > 0) {
				// Create a CFArray to contain all the names
				CFMutableArrayRef	theArray;
				CFStringRef			nameRef;
				CFDataRef			theKey;
				Str255				theName;

				theKey = CFDataCreate(NULL, (const UInt8 *) inFileRef, sizeof(FSRef));
				if (theKey) {
					theArray = CFArrayCreateMutable(NULL, 0, NULL);
					if (theArray) {
						for ( UInt16 i = 1; i <= numResources; i++ ) {
							error = theRezType->GetNameAtIndex(i, theName);
							if (error == noErr) {
								nameRef = CFStringCreateWithPascalString(NULL, theName, kCFStringEncodingMacRoman);
								if (nameRef) {
									CFArrayAppendValue(theArray, nameRef);
									CFRelease(nameRef);
								} 							
							}
						}
						delete theRezType;
						
						// Add to the dictionary
						CFDictionaryAddValue(inDict, theKey, theArray);
// 						CFRelease(theArray);
					} 
// 					CFRelease(theKey);
				} 
			} 
			delete rezMap;
		}
	}
		
	return error;
}


// ---------------------------------------------------------------------------
//  ¥ HasTemplateForType											[static]
// ---------------------------------------------------------------------------

Boolean
CTemplatesController::HasTemplateForType(ResType inType, ResType * substType)
{
	Boolean hasTMPL = false;
	
	sTemplateKind = tmpl_none;
	
	// First look fo an internal TMPL resource
	hasTMPL = sInternalTemplates.ContainsItem(inType);
	if (hasTMPL == true) {
		sTemplateKind = tmpl_internal;
	} else {
		// Look for an external TMPL
		hasTMPL = HasExternalTemplateForType(inType, &sTemplateFile);
		if (hasTMPL) {
			sTemplateKind = tmpl_external;
		} 
	}
	// If still not found, check if there is a substitution type
	if ( !hasTMPL ) {
		if ( CEditorsController::FindSubstitutionType(inType, substType) ) {
			hasTMPL = HasTemplateForType(*substType, substType);
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
						CFIndex retcount = CFGetRetainCount(theArrayRef);
						CFTypeID thetypeid = CFGetTypeID(theArrayRef);
						thetypeid = CFArrayGetTypeID();
						
						CFIndex countidx = CFArrayGetCount(theArrayRef);

						
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
	
	switch (sTemplateKind) {
		case tmpl_internal:
		CRezType *	theRezType = new CRezType('TMPL', sTemplatesMap);
		
		UMiscUtils::OSTypeToPString(inType, typeName);
		theRezType->GetWithName(typeName, theHandle);
		::DetachResource(theHandle);
		break;
		
		case tmpl_external:
		break;
		
	}
	
	return theHandle;
}
 


