// ===========================================================================
// CEditorsController.cp					
// 
//                       Created: 2004-06-11 10:48:38
//             Last modification: 2006-10-09 07:58:39
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2004-2006
// All rights reserved.
// ===========================================================================

PP_Begin_Namespace_PowerPlant


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CEditorsController.h"
#include "CRezillaApp.h"
#include "CTEXT_EditorDoc.h"
#include "CUtxt_EditorDoc.h"
#include "CPICT_EditorDoc.h"
#include "CSnd_EditorDoc.h"
#include "CICNS_EditorDoc.h"
#include "CIcon_EditorDoc.h"
#include "CAete_EditorDoc.h"
#include "CMENU_EditorDoc.h"
#include "CSTRx_EditorDoc.h"
#include "CTemplatesController.h"
#include "CRezMap.h"
#include "CRezMapDoc.h"
#include "CRezMapWindow.h"
#include "CRezMapTable.h"
#include "CRezObj.h"
#include "CRezType.h"
#include "CRezTypeItem.h"
#include "CRezObjItem.h"
#include "RezillaConstants.h"
#include "UMiscUtils.h"


CFMutableDictionaryRef	CEditorsController::sAsTypeDictionary = NULL;


// ---------------------------------------------------------------------------
//   CEditorsController					Constructor				  [public]
// ---------------------------------------------------------------------------

CEditorsController::CEditorsController()
{
	BuildAsTypeDictionary();
}


// ---------------------------------------------------------------------------
//     ~CEditorsController					Destructor				  [public]
// ---------------------------------------------------------------------------

CEditorsController::~CEditorsController()
{	
	if (sAsTypeDictionary) {
		::CFRelease(sAsTypeDictionary);
	}
}


// ---------------------------------------------------------------------------
//   BuildAsTypeDictionary											[public]
// ---------------------------------------------------------------------------
// Create a CFDictionary whose keys are resource types and whose values are a
// type having an identical structure. This concerns resource types whose type
// is defined with a 'type as' statement in the Rez include files (with .r
// extension).
// Note (vs 1.0.7): the property list built from the XML data causes a 
// crash under Tiger while it works ok under Panther. No idea what's the 
// problem. As a consequence, the TypeAs.plist file is now replaced by a 
// resource of custom type RzTA which stores the key/value pairs of 
// ResTypes, and the dictionary is now built from this resource.
// 			type 'RzTA' {
// 				wide array {
// 					literal longint;		/* Original type */
// 					literal longint;		/* Substitute type */
// 				};
// 			};


void
CEditorsController::BuildAsTypeDictionary()
{
	StRezRefSaver saver( CRezillaApp::GetSelfRefNum() );

	// Get the data
	Handle rezHandle = nil;
	rezHandle = ::Get1Resource('RzTA', 0);

	if (rezHandle != nil) {
		// ZP bugfix #1, part 1: detach the resource
		::DetachResource(rezHandle);
		
		// Read its data and make a stream
		LHandleStream * theStream = new LHandleStream(rezHandle);

		if (theStream != NULL) {
			CFNumberRef		theKeyRef, theValRef;
			OSType			theOSType;
			SInt32			index;
			SInt32			count = theStream->GetLength() / 8;

			// Create a mutable dictionary
			sAsTypeDictionary = ::CFDictionaryCreateMutable(NULL, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
			
			if (sAsTypeDictionary) {
				for (index = 0; index < count; index++) {
					// CFStringGetSystemEncoding() or kCFStringEncodingMacRoman
					*theStream >> theOSType;
					theKeyRef = ::CFNumberCreate(NULL, kCFNumberSInt32Type, &theOSType);

					if (theKeyRef != nil) {
						*theStream >> theOSType;
						theValRef = ::CFNumberCreate(NULL, kCFNumberSInt32Type, &theOSType);
						
						if (theValRef) {
							::CFDictionaryAddValue(sAsTypeDictionary, theKeyRef, theValRef);
							::CFRelease(theValRef);
						} 
						::CFRelease(theKeyRef);
					}
				}			
			}
			
			// ZP bugfix #1, part 2: don't call ReleaseResource because the
			// detached handle is disposed of when theStream is deleted
			delete theStream;
		} 
	} 
}


// ---------------------------------------------------------------------------
//   FindSubstitutionType											[public]
// ---------------------------------------------------------------------------

Boolean
CEditorsController::FindSubstitutionType(ResType inType, ResType * outType)
{
	Boolean result = false;
	
	if (sAsTypeDictionary != NULL) {
		CFNumberRef	inTypeRef = NULL;
		CFNumberRef	outTypeRef = NULL;
		
		inTypeRef = ::CFNumberCreate(NULL, kCFNumberSInt32Type, &inType);
		
		if (inTypeRef) {
			result = ::CFDictionaryGetValueIfPresent( (CFDictionaryRef) sAsTypeDictionary, 
													 inTypeRef, (const void**) &outTypeRef);
			CFRelease(inTypeRef);
			
			if (result && outTypeRef != NULL) {
				if ( ::CFNumberGetValue(outTypeRef, kCFNumberSInt32Type, (void*) outType) ) {
					result = true;
				} 
				// Caveat: outTypeRef must not be released
			}
		}
	}
	
	return result;
}


// ---------------------------------------------------------------------------
//   HasEditorForType												[public]
// ---------------------------------------------------------------------------

Boolean
CEditorsController::HasEditorForType(ResType inType, ResType * substTypePtr)
{
	Boolean hasEditor = false;
	
	switch (inType) {
		case 'TEXT':
		case 'styl':
		case 'utxt':
		case 'thng':
		case 'thga':
		case 'PICT':
		case 'snd ':
		case 'CURS':
		case 'ICN#':
		case 'ICON':
		case 'PAT ':
		case 'PAT#':
		case 'SICN':
		case 'cicn':
		case 'crsr':
		case 'icl4':
		case 'icl8':
		case 'icm#':
		case 'icm4':
		case 'icm8':
		case 'ics#':
		case 'ics4':
		case 'ics8':
		case 'ppat':
		case 'aete':
		case 'MENU':
		case 'STR#':
		case 'MBAR':
		case 'Mcmd':
		case 'RidL':
		case 'RID#':
		case 'icns':
		*substTypePtr = inType;
		hasEditor = true;
		break;
	}
	
	if (!hasEditor) {
		if ( FindSubstitutionType(inType, substTypePtr) ) {
			hasEditor = HasEditorForType(*substTypePtr, substTypePtr);
		} 
	} 
	return hasEditor;
}


// ---------------------------------------------------------------------------
//   InvokeCustomEditor											[public]
// ---------------------------------------------------------------------------

void
CEditorsController::InvokeCustomEditor(CRezMapDoc* inRezMapDoc, 
									   CRezObjItem * inRezObjItem,
									   ResType inUseType)
{
	CRezMapTable *	theSuperMap = inRezMapDoc->GetRezMapWindow()->GetRezMapTable();
	CRezObj *		theRezObj = inRezObjItem->GetRezObj();
	Boolean			isReadOnly = inRezMapDoc->IsReadOnly();
	ResType			theType;
	Size			theSize;
	
	switch (inUseType) {
		case 'styl': {
		// Check if there is an associated TEXT resource
		CRezObj * textRezObj = NULL;
		OpenOrCreateWithTypeAndID(theSuperMap, 'TEXT', theRezObj->GetID(), &textRezObj);
		new CTEXT_EditorDoc( (LCommander *) inRezMapDoc, theSuperMap, textRezObj, 'TEXT', isReadOnly);
		break;
		}

		case 'TEXT':
		  new CTEXT_EditorDoc( (LCommander *) inRezMapDoc, theSuperMap, theRezObj, inUseType, isReadOnly);
		break;
		
		case 'utxt':
		  new CUtxt_EditorDoc( (LCommander *) inRezMapDoc, theSuperMap, theRezObj, inUseType, isReadOnly);
		break;
		
		case 'PICT':
		  new CPICT_EditorDoc( (LCommander *) inRezMapDoc, theSuperMap, theRezObj, inUseType, isReadOnly);
		break;
		
		case 'snd ':
		  new CSnd_EditorDoc( (LCommander *) inRezMapDoc, theSuperMap, theRezObj, inUseType, true);
		break;
		
		case 'aete':
		  new CAete_EditorDoc( (LCommander *) inRezMapDoc, theSuperMap, theRezObj, inUseType, isReadOnly);
		break;
		
		case 'MENU':
		  new CMENU_EditorDoc( (LCommander *) inRezMapDoc, theSuperMap, theRezObj, inUseType, isReadOnly);
		break;
		
		case 'icns':
		  new CICNS_EditorDoc( (LCommander *) inRezMapDoc, theSuperMap, theRezObj, inUseType, isReadOnly);
		break;
		
		case 'STR#':
		case 'MBAR':
		case 'Mcmd':
		case 'RidL':
		case 'RID#':
		  new CSTRx_EditorDoc( (LCommander *) inRezMapDoc, theSuperMap, theRezObj, inUseType, isReadOnly);
		break;
		
		case 'CURS':
		case 'ICN#':
		case 'ICON':
		case 'PAT ':
		case 'PAT#':
		case 'SICN':
		case 'cicn':
		case 'crsr':
		case 'icl4':
		case 'icl8':
		case 'icm#':
		case 'icm4':
		case 'icm8':
		case 'ics#':
		case 'ics4':
		case 'ics8':
		case 'ppat':
		new CIcon_EditorDoc( (LCommander *) inRezMapDoc, theSuperMap, theRezObj, inUseType, isReadOnly);
	  break;

		case 'thng':
		// A 'thng' resource has three different formats but contains 
		// no field to determine its version: 
		// - version 0 had fixed a size of 44 bytes,
		// - version 1 adds 10 bytes, a 4 bytes count and a list of 12 bytes items. 
		//      Size = 44 + 10 + 2 + 12*n
		// - version 2 adds 6 bytes. Size = 44 + 12*n + 2 + 6
		theSize = inRezObjItem->GetRezObj()->GetSize();
		if (theSize == 44) {
			theType = 'thn0';
		} else if ( ((theSize - 58) % 12) == 0 ) {
			theType = 'thn1';
		} 
		inRezMapDoc->TryEdit(inRezObjItem, cmd_TmplEditAsRez, theType);
		break;
		
		case 'thga':
		// A 'thga' resource has two different formats with fixed size.
		// Initial version had 64 bytes, current version has 72 bytes
		theSize = inRezObjItem->GetRezObj()->GetSize();
		if (theSize == 64) {
			theType = 'thg0';
		} 
		inRezMapDoc->TryEdit(inRezObjItem, cmd_TmplEditAsRez, theType);
		break;
		
	}
}


// ---------------------------------------------------------------------------
//   OpenOrCreateWithTypeAndID										[public]
// ---------------------------------------------------------------------------

OSErr
CEditorsController::OpenOrCreateWithTypeAndID(CRezMapTable* inSuperMap, ResType inType, 
									  short inID, CRezObj** outRezObj)
{
	OSErr result = noErr;
	
	// The 'true' argument will expand the RezTypeItem if it exists
	CRezTypeItem *	theRezTypeItem = inSuperMap->GetRezTypeItem(inType, true);
	CRezObjItem *	theRezObjItem;
		
	if (theRezTypeItem == nil || ! theRezTypeItem->ExistsItemForID(inID, theRezObjItem) ) {
		// The NewResource function will take care of creating the RezTypeItem
		theRezObjItem = inSuperMap->GetOwnerDoc()->NewResource(inType, inID, NULL, 0, false);
	}

	if (theRezObjItem != nil) {
		*outRezObj = theRezObjItem->GetRezObj();
	} 
	
	return (outRezObj == NULL);
}
 

// ---------------------------------------------------------------------------
//   TypesCorrespond												[public]
// ---------------------------------------------------------------------------
// Some editors edit several types simultaneously (like the IconFamily
// editor or the menu editor). So the type of the resource to be edited
// could be different from the type of a certain editor and still
// correspond.
// 
// inType1 is the type of the resource we want to edit, inType2 is the type
// associated to an existing editor.
// 
// ResType iconTypes[9] = {'ICN#', 'icl4', 'icl8', 'ics#', 'ics4', 'ics8', 'icm#', 'icm4', 'icm8'};
// 

Boolean
CEditorsController::TypesCorrespond(ResType inType1, ResType inType2, Boolean exact)
{
	if (inType1 == inType2) {
		return true;
	} 
	
	Boolean corresponds = false;
	
	if (!exact) {
		switch (inType1) {
			case 'ICN#':
			case 'icl4':
			case 'icl8':
			case 'icm#':
			case 'icm4':
			case 'icm8':
			case 'ics#':
			case 'ics4':
			case 'ics8':
			switch (inType2) {
				case 'ICN#':
				case 'icl4':
				case 'icl8':
				case 'icm#':
				case 'icm4':
				case 'icm8':
				case 'ics#':
				case 'ics4':
				case 'ics8':
				corresponds = true;
				break;
			}
			break;
			
			case 'xmnu':
			corresponds = (inType2 == 'MENU');
			break;

		}
	} 
	
	return corresponds;
}




PP_End_Namespace_PowerPlant


