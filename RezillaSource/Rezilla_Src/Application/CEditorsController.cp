// ===========================================================================
// CEditorsController.cp					
// 
//                       Created: 2004-06-11 10:48:38
//             Last modification: 2004-08-09 10:05:57
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

PP_Begin_Namespace_PowerPlant


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CEditorsController.h"
#include "CTEXT_EditorDoc.h"
#include "CTemplatesController.h"
#include "CRezMap.h"
#include "CRezMapDoc.h"
#include "CRezMapTable.h"
#include "CRezObj.h"
#include "CRezType.h"
#include "CRezTypeItem.h"
#include "CRezObjItem.h"
#include "RezillaConstants.h"
#include "UMiscUtils.h"


// // Standard headers
// #include <string.h>


CFPropertyListRef	CEditorsController::sAsTypeDictionary;


// ---------------------------------------------------------------------------
//	¥ CEditorsController					Constructor				  [public]
// ---------------------------------------------------------------------------

CEditorsController::CEditorsController()
{
	sAsTypeDictionary = BuildAsTypeDictionary();
}


// ---------------------------------------------------------------------------
//	¥ ~CEditorsController					Destructor				  [public]
// ---------------------------------------------------------------------------

CEditorsController::~CEditorsController()
{	
}


// ---------------------------------------------------------------------------
//	¥ BuildAsTypeDictionary											[public]
// ---------------------------------------------------------------------------
// Create a CFDictionary whose keys are resource types and whose values are a
// type having an identical structure. This concerns resource types whose type
// is defined with a 'type as' statement in the Rez include files (with .r
// extension).

CFPropertyListRef
CEditorsController::BuildAsTypeDictionary()
{
	CFBundleRef 			mainBundleRef;
	CFPropertyListRef		plistRef = NULL;
	CFURLRef 				typeasURL;
	OSErr	  				error = noErr;
	
	// Locate the Templates resource file inside the main bundle
	mainBundleRef = NULL;
	typeasURL = NULL;
	
	mainBundleRef = CFBundleGetMainBundle();
	
	typeasURL = CFBundleCopyResourceURL(mainBundleRef, CFSTR("TypeAs"), CFSTR("plist"), NULL);
	
	if (typeasURL) {
		CFDataRef		xmlRef;
		Boolean			status;
		
		// Read the XML file
		status = CFURLCreateDataAndPropertiesFromResource(kCFAllocatorDefault, typeasURL, 
														  &xmlRef, NULL, NULL, NULL);
		if (status) {
			CFStringRef errorString;
			// Reconstitute the dictionary using the XML data
			plistRef = CFPropertyListCreateFromXMLData(kCFAllocatorDefault, xmlRef, 
													   kCFPropertyListImmutable, &errorString);
			
			if (plistRef == NULL) CFShow(errorString);
			
			// Release the XML data
			CFRelease(xmlRef);
		}
		
		CFRelease(typeasURL);
	}	
	
	return plistRef;
}


// ---------------------------------------------------------------------------
//	¥ FindSubstitutionType											[public]
// ---------------------------------------------------------------------------

Boolean
CEditorsController::FindSubstitutionType(ResType inType, ResType * outType)
{
	Boolean result = false;
	
	if (sAsTypeDictionary != NULL) {
		if ( CFGetTypeID(sAsTypeDictionary) == CFDictionaryGetTypeID() ) {
			Str255		theString;
			CFStringRef	inTypeRef, outTypeRef;
			
			UMiscUtils::OSTypeToPString(inType, theString);	
			inTypeRef = CFStringCreateWithPascalString(NULL, theString, kCFStringEncodingMacRoman);
			
			if (inTypeRef) {
				result = CFDictionaryGetValueIfPresent( (CFDictionaryRef) sAsTypeDictionary, 
													   inTypeRef, (const void**) &outTypeRef);
				
				if (result) {
					result = CFStringGetPascalString(outTypeRef, theString, 
													 sizeof(theString), kCFStringEncodingMacRoman);
					CFRelease(outTypeRef);
					
					if (result) {
						UMiscUtils::PStringToOSType(theString, *outType);	
					} 
				}
				CFRelease(inTypeRef);
			}
		}
	}
	
	return result;
}


// ---------------------------------------------------------------------------
//  ¥ HasEditorForType												[public]
// ---------------------------------------------------------------------------

Boolean
CEditorsController::HasEditorForType(ResType inType, ResType * substType)
{
	Boolean result = false;
	
	switch (inType) {
		case 'TEXT':
		case 'styl':
		result = true;
		break;
	}
	
	return result;
}


// ---------------------------------------------------------------------------
//  ¥ InvokeCustomEditor											[public]
// ---------------------------------------------------------------------------

void
CEditorsController::InvokeCustomEditor(LCommander* inSuper, 
						   CRezMapTable* inSuperMap, 
						   CRezObj* inRezObj,
						   Boolean inReadOnly)
{
	ResType theType = inRezObj->GetType();
	switch (theType) {
		case 'styl':
		// Check if there is an associated TEXT resource
		CRezObj * textRezObj = NULL;
		OpenOrCreateWithTypeAndID(inSuperMap, 'TEXT', inRezObj->GetID(), &textRezObj);
		new CTEXT_EditorDoc(inSuper, inSuperMap, textRezObj, 'TEXT', inReadOnly);
		break;

		case 'TEXT':
		  new CTEXT_EditorDoc(inSuper, inSuperMap, inRezObj, 'TEXT', inReadOnly);
		break;
		
	}
}


// ---------------------------------------------------------------------------
//  ¥ OpenOrCreateWithTypeAndID											[public]
// ---------------------------------------------------------------------------

OSErr
CEditorsController::OpenOrCreateWithTypeAndID(CRezMapTable* inSuperMap, ResType inType, 
									  short inID, CRezObj** outRezObj)
{
	OSErr result = noErr;
	
	CRezTypeItem * theRezTypeItem = inSuperMap->GetRezTypeItem(inType);
	CRezObjItem * theRezObjItem;
	
	if (theRezTypeItem != nil) {
		if ( ! theRezTypeItem->IsExpanded() ) {
			theRezTypeItem->Expand();
		} 
	} 
	
	if (theRezTypeItem == nil || ! theRezTypeItem->ExistsItemForID(inID, theRezObjItem) ) {
		// The CreateNewRes function will take care of creating the RezTypeItem
		theRezObjItem = inSuperMap->GetOwnerDoc()->CreateNewRes(inType, inID, NULL, 0);
	}

	*outRezObj = theRezObjItem->GetRezObj();
	
	return (outRezObj == NULL);
}
 

// ---------------------------------------------------------------------------
//  ¥ RegisterEditor												[public]
// ---------------------------------------------------------------------------

OSErr
CEditorsController::RegisterEditor()
{
	OSErr error = noErr;
	
	return error;
}





PP_End_Namespace_PowerPlant


