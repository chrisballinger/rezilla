// ===========================================================================
// CRezClipboard.cp					
//                       Created: 2003-05-11 21:05:08
//             Last modification: 2004-03-12 14:17:16
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2003-2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


// #ifdef PowerPlant_PCH
// 	#include PowerPlant_PCH
// #endif

#include "CRezClipboard.h"
#include "CRezMapDoc.h"
#include "CRezFile.h"
#include "CRezMap.h"
#include "CRezType.h"
#include "CRezObj.h"
#include "CRezObjItem.h"
#include "UMiscUtils.h"
#include "RezillaConstants.h"

#include <LClipboard.h>
#include <UMemoryMgr.h>
#include <UScrap.h>

#include <Events.h>


PP_Begin_Namespace_PowerPlant

SInt32		CRezClipboard::sScrapContext = 0;
CRezFile *	CRezClipboard::sScrapRezFile;
CRezMap *	CRezClipboard::sScrapRezMap;
short		CRezClipboard::sScrapRefnum;

// ---------------------------------------------------------------------------
//	¥ CRezClipboard							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CRezClipboard::CRezClipboard()
	: LClipboard()
{
	sScrapContext = scrap_default;
	CRezClipboard::InitScrapRezMap();
}


// ---------------------------------------------------------------------------
//	¥ ~CRezClipboard							Destructor			  [public]
// ---------------------------------------------------------------------------

CRezClipboard::~CRezClipboard()
{
	if (mExportPending) {
// 		ExportSelf();
		mExportPending = false;
	}
	// Close the Scrap Rez Map
	sScrapRezMap->Close();
}


// ---------------------------------------------------------------------------
//	¥ InitScrapRezMap												   [protected]
// ---------------------------------------------------------------------------
// /Developer/Examples/Printing/App/BasicPrintLoop/PrintLoop/Source/main.c
// /Developer/Examples/Printing/Printer/Plugins/SamplePM/Source/RasterUtils.cp

OSErr
CRezClipboard::InitScrapRezMap()
{
	CFBundleRef 	mainBundleRef;
	CFURLRef 		mainBundleURL, scrapRezMapURL, resDirUrl;
	FSRef 			theFSRef, parentRef;
	FSSpec			theFileSpec;
	OSStatus  		error = noErr;
	short			scrapRefNum;
	HFSUniStr255	unicodeName;
	ConstStr31Param hfsName = "\pScrapRezMap.rsrc";
	
	mainBundleRef = NULL;
	mainBundleURL = NULL;
	scrapRezMapURL = NULL;
	resDirUrl = NULL;
	
	mainBundleRef = CFBundleGetMainBundle();
	if (mainBundleRef == NULL) {
		error = fnfErr; 
		sScrapRezFile = nil;
		goto bail;
	}
	
	scrapRezMapURL = CFBundleCopyResourceURL(mainBundleRef, CFSTR("ScrapRezMap"), CFSTR("rsrc"), NULL);
	
	if (scrapRezMapURL == nil) {
		// Create the file
		mainBundleURL = CFBundleCopyBundleURL(mainBundleRef);
		if (mainBundleURL) {
			resDirUrl = CFBundleCopyResourcesDirectoryURL(mainBundleRef);
			if (resDirUrl) {
				if ( CFURLGetFSRef(resDirUrl, &parentRef) ) {
					error = UMiscUtils::HFSNameToUnicodeName(hfsName, &unicodeName);
					error = FSCreateResourceFile(&parentRef, hfsName[0], unicodeName.unicode, kFSCatInfoNone, NULL, 0, NULL, &theFSRef, &theFileSpec);
					error = FSOpenResourceFile( &theFSRef, 0, nil, fsRdWrPerm, &scrapRefNum );
				} else {
					error = fnfErr;
				}
				CFRelease(resDirUrl);
			} 
			CFRelease(mainBundleURL);
		} 
	} else {
		if ( CFURLGetFSRef(scrapRezMapURL, &theFSRef) ) {
			error = FSGetCatalogInfo( &theFSRef, kFSCatInfoNone, NULL, NULL, &theFileSpec, NULL);
			SetResLoad( false );
			error = FSOpenResourceFile( &theFSRef, 0, nil, fsRdWrPerm, &scrapRefNum );
			SetResLoad( true );
		}
		CFRelease(scrapRezMapURL);
	} 	
	
	// Make static objects
	if (error == noErr) {
		sScrapRezFile = new CRezFile(theFileSpec, scrapRefNum, fork_datafork);
		sScrapRezMap = new CRezMap(scrapRefNum);
		sScrapRefnum = scrapRefNum;
	} 
short		numTypes;
error = sScrapRezMap->CountAllTypes(numTypes);
		
	bail:
	if (mainBundleRef != NULL) CFRelease(mainBundleRef);
	return error;
}


// ---------------------------------------------------------------------------
//	¥ GetDataSelf												   [protected]
// ---------------------------------------------------------------------------
//	Pass back the data in the Clipboard of the specified type in a Handle
//	and return the size of the data
//
//	If ioDataH is nil, the data is not passed back, but its size is returned.
//	Otherwise, ioDataH must be a valid Handle which is resized if necessary
//	to hold all the data.
//

SInt32
CRezClipboard::GetDataSelf(
	ResType		inDataType,
	Handle		ioDataH)
{
	SInt32 dataSize = 0;
	
	switch (sScrapContext) {
	  case scrap_rezmap:
	  // Do nothing. The bulk of the work is accomplished by CRezMapDoc::PasteRezMap().
		break;
		
	  case scrap_hexeditHexdata:
		break;
		
	  case scrap_hexeditTxtdata:
		break;
		
	  default:
	  dataSize = UScrap::GetData(inDataType, ioDataH);
		break;
		
	}
	return dataSize;
}


// ---------------------------------------------------------------------------
//	¥ SetDataSelf												   [protected]
// ---------------------------------------------------------------------------
//	Set the Clipboard contents to the data specified by a pointer and length
//
//	inReset specifies whether to clear the existing contents of the
//	Clipboard before storing the new data.
//

void
CRezClipboard::SetDataSelf(
	ResType		inDataType,
	Ptr			inDataPtr,
	SInt32		inDataLength,
	Boolean		inReset)
{
	switch (sScrapContext) {
	  case scrap_rezmap: 
	  SetDataInScrapRezMap(inDataType, inDataPtr, inDataLength, inReset);
	  // mExportPending is not reset to false
		break;
		
	  case scrap_hexeditHexdata:
	  case scrap_hexeditTxtdata:
	  default:
		UScrap::SetData(inDataType, inDataPtr, inDataLength, inReset);
		mExportPending = false;
		break;
		
	}
}


// ---------------------------------------------------------------------------
//	¥ ImportSelf												   [protected]
// ---------------------------------------------------------------------------
//	Import the data in the global scrap to a local scrap
//
//	Retrieve the data from the global scrap, extract all types 
//	and create a resource with the same type/data. There is no ID 
//	associated with this data in the scrap, so generate an UID.

void
CRezClipboard::ImportSelf()
{
	OSStatus			error = noErr;
	UInt32				theCount, idx;
	
	error = ::GetScrapFlavorCount(mScrapRef, &theCount);
	
	if (error == noErr && theCount)  {
		ScrapFlavorInfo *	infoList;
		CRezType *	theRezType = nil;
		CRezObj *	theRezObj = nil;
		Handle		theHandle;
		Size		byteCount;
		
		// Reset the scrap rez map
		error = sScrapRezMap->DeleteAll();
		error = sScrapRezMap->Update();
		
		// Get the list of all flavors found in the global scrap
		infoList = (ScrapFlavorInfo*) NewPtrClear( theCount * sizeof(ScrapFlavorInfo) );
		error = ::GetScrapFlavorInfoList(mScrapRef, &theCount, infoList);		
		
		for (idx = 0; idx < theCount; idx++) {
			// Create a new resource in the scrap rez map
			theRezType = new CRezType(infoList[idx].flavorType, sScrapRezMap);
			theRezObj = new CRezObj(theRezType);
			
			// Set the data in the RezObj
			error = ::GetScrapFlavorSize(mScrapRef, infoList[idx].flavorType, &byteCount);
			if (error == noErr)  {
				theHandle = ::NewHandle(byteCount);
				if (theHandle != nil) {
					error = ::GetScrapFlavorData(mScrapRef, infoList[idx].flavorType, &byteCount, *theHandle);
					if (error == noErr)  {
						theRezObj->SetData(theHandle);
					}
					::DisposeHandle(theHandle);
				}
			}
			// Add the RezObj to the map
			error = theRezObj->Add();
			error = theRezObj->Changed();
			if (theRezType != nil) {
				delete theRezType;
			} 
			if (theRezObj != nil) {
				delete theRezObj;
			} 
		}
		error = sScrapRezMap->Update();
	}	
}
	

// ---------------------------------------------------------------------------
//	¥ ExportSelf												   [protected]
// ---------------------------------------------------------------------------
//	Export the data in a local scrap to the global scrap
//
//	Take the first resource of each type and put the data in the 
//	global scrap using the same type.

void
CRezClipboard::ExportSelf()
{
	short	numTypes;
	ResType theType;
	Handle	theRezHandle;
	short	theAttrs;
	OSErr	error = noErr;

return;

	// Clear the data on the scrap and get a new scrapRef
	ClearData();
	
	error = sScrapRezMap->CountAllTypes(numTypes);
	if (error != noErr || numTypes == 0) {return;}
	
	for (UInt16 i = 1; i <= numTypes; i++ ) {
		CRezObj *	theRezObj;
		
		// Read in each data type
		sScrapRezMap->GetTypeAtIndex(i, theType);
		
		// Get the data handle for the resource at index 1 in this type
		error = sScrapRezMap->GetResourceAtIndex(theType, 1, theRezHandle);
		if (theRezHandle) {
			// Put it on the global scrap
			error = PutScrapFlavor(mScrapRef, theType, 0, ::GetHandleSize(theRezHandle), *theRezHandle);
		} 
	}
	return;
}


// ---------------------------------------------------------------------------
//	¥ ContentsIsValidHex										   [protected]
// ---------------------------------------------------------------------------
//	Check it the actual contents of the scrap are valid hexadecimal data 
// (only 0-9, a-f, A-F).

Boolean
CRezClipboard::ContentsIsValidHex()
{
    Handle theHandle = ::NewHandle(0);
    UScrap::GetData('TEXT', theHandle);
    
    return UMiscUtils::IsValidHexadecimal(theHandle);
}


// ---------------------------------------------------------------------------
//	¥ SetDataInScrapRezMap											[private]
// ---------------------------------------------------------------------------
//	Set the ScrapRezMap contents to the data specified by a pointer and length.
//
//	inReset specifies whether to clear the existing contents of the
//	ScrapRezMap before storing the new data.

void
CRezClipboard::SetDataInScrapRezMap(
	ResType		inDataType,
	Ptr			inDataPtr,
	SInt32		inDataLength,
	Boolean		inReset)
{
	LArray* theArray = (LArray*) inDataPtr;
	LArrayIterator	iterator(*theArray);
	CRezObjItem *	theItem = nil;	
	CRezObj *		theRezObj = nil;
	OSErr			error = noErr;
	short			theAttrs;
	
short		numTypes;
error = sScrapRezMap->CountAllTypes(numTypes);
	if (inReset) {
		error = sScrapRezMap->DeleteAll();
		error = sScrapRezMap->Update();
	} 
error = sScrapRezMap->CountAllTypes(numTypes);
	
	while (iterator.Next(&theItem)) {
		if (theRezObj != nil) {
			delete theRezObj;
		} 
		theRezObj = new CRezObj( *((CRezObjItem *)theItem)->GetRezObj() );
// 		error = GetAttributesFromMap(theAttrs);
		theAttrs = theRezObj->GetAttributes();
		
		theRezObj->SetOwnerRefnum(sScrapRefnum);
		error = theRezObj->Add();
		
		if (theAttrs != 0) {
			// Write the attributes in scrap rezmap
			error = theRezObj->SetAttributes(theAttrs);
		} 
		error = theRezObj->Changed();
	}
	error = sScrapRezMap->Update();


short	numResources;
ResType		theType;
Handle theHandle;
error = sScrapRezMap->CountAllTypes(numTypes);
for (UInt16 i = 1; i <= numTypes; i++) {
	error = sScrapRezMap->GetTypeAtIndex(i, theType);
	if (error == noErr) {
		sScrapRezMap->CountForType(theType, numResources);
		if (error == noErr) {
			for (UInt16 j = 1; j <= numResources; j++) {
				theHandle = ::Get1IndResource(theType, j);
				error = ::ResError();
			}
		
		} 
	} 
}
}



PP_End_Namespace_PowerPlant

