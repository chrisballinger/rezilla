// ===========================================================================
// CRezClipboard.cp					
//                       Created: 2003-05-11 21:05:08
//             Last modification: 2005-01-12 17:46:53
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2003-2005
// All rights reserved.
// ===========================================================================

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

SInt32		CRezClipboard::sScrapContext;
CRezFile *	CRezClipboard::sScrapRezFile = nil;
CRezMap *	CRezClipboard::sScrapRezMap = nil;
short		CRezClipboard::sScrapRefnum = kResFileNotOpened;

// ---------------------------------------------------------------------------
//	¥ CRezClipboard							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CRezClipboard::CRezClipboard()
	: LClipboard()
{
	sScrapContext = scrap_default;
	CRezClipboard::NewLocalScrap();
}


// ---------------------------------------------------------------------------
//	¥ ~CRezClipboard							Destructor			  [public]
// ---------------------------------------------------------------------------

CRezClipboard::~CRezClipboard()
{
	OSErr error;
	
	if (mExportPending) {
// 		ExportSelf();
		mExportPending = false;
	}
	// Close the Scrap Rez Map
	if (sScrapRezMap != nil) {
		error = sScrapRezMap->Close();
	} 
	// Delete the scrap file
	if (sScrapRezFile != nil) {
		 FSSpec theFileSpec ;
		sScrapRezFile->GetSpecifier(theFileSpec);
		error = FSpDelete(&theFileSpec);
	} 
}


// ---------------------------------------------------------------------------
//	¥ NewLocalScrap										   [protected]
// ---------------------------------------------------------------------------
// /Developer/Examples/Printing/App/BasicPrintLoop/PrintLoop/Source/main.c
// /Developer/Examples/Printing/Printer/Plugins/SamplePM/Source/RasterUtils.cp

OSErr
CRezClipboard::NewLocalScrap()
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
		return error;
	}
	
	scrapRezMapURL = CFBundleCopyResourceURL(mainBundleRef, CFSTR("ScrapRezMap"), CFSTR("rsrc"), NULL);
	
	if (scrapRezMapURL != nil) {
		if ( CFURLGetFSRef(scrapRezMapURL, &theFSRef) ) {
			error = FSGetCatalogInfo( &theFSRef, kFSCatInfoNone, NULL, NULL, &theFileSpec, NULL);
			error = FSpDelete(&theFileSpec);
			if (error == noErr) {
				return error;
			} 
		}
		CFRelease(scrapRezMapURL);
	} 	
	
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

	// Make static objects
	if (error == noErr) {
		sScrapRezFile = new CRezFile(theFileSpec, scrapRefNum, fork_datafork);
		sScrapRezMap = new CRezMap(scrapRefNum);
		sScrapRefnum = scrapRefNum;
	}
	
	return error;
}


// ---------------------------------------------------------------------------
//	¥ DeleteLocalScrap												   [protected]
// ---------------------------------------------------------------------------

OSErr
CRezClipboard::DeleteLocalScrap()
{
	OSErr error = noErr;
	
	if (sScrapRezMap != nil) {
		// Close() sets the refnum to kResFileNotOpened
		error = sScrapRezMap->Close();
		delete sScrapRezMap;
		sScrapRezMap = nil;
	} 
	if (sScrapRezFile != nil) {
		 FSSpec theFileSpec ;
		 
		sScrapRezFile->GetSpecifier(theFileSpec);
		error = FSpDelete(&theFileSpec);
		delete sScrapRezFile;
		sScrapRezFile = nil;
	} 
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
		
		case scrap_bitmap:
		dataSize = UScrap::GetData(inDataType, ioDataH);
// 		DeleteLocalScrap();
		break;
		
		case scrap_default:
		case scrap_hexeditHex:
		case scrap_hexeditTxt:
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
		DataArrayToScrapRezMap(inDataType, inDataPtr, inDataLength, inReset);
		// mExportPending must not be reset to false in this case.
		break;
		
		case scrap_bitmap:
		UScrap::SetData(inDataType, inDataPtr, inDataLength, inReset);
		DeleteLocalScrap();
		mExportPending = false;
		mImportPending = false;
		break;

		case scrap_default:
		case scrap_hexeditHex:
		case scrap_hexeditTxt:
		default:
		UScrap::SetData(inDataType, inDataPtr, inDataLength, inReset);
		mExportPending = false;
		mImportPending = true;
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
	
	// Import only if a RezMapDoc is active
	if (sScrapContext != scrap_rezmap) {
		return;
	} 
	
	error = ::GetScrapFlavorCount(mScrapRef, &theCount);
	
	if (error == noErr && theCount)  {
		ScrapFlavorInfo *	infoList;
		CRezType *	theRezType = nil;
		CRezObj *	theRezObj = nil;
		Handle		theHandle;
		Size		byteCount;
		
		// Reset the scrap rez map
		DeleteLocalScrap();
		NewLocalScrap();
		
		// Get the list of all flavors found in the global scrap
		infoList = (ScrapFlavorInfo*) NewPtrClear( theCount * sizeof(ScrapFlavorInfo) );
		error = ::GetScrapFlavorInfoList(mScrapRef, &theCount, infoList);		
		
		if (error == noErr)  {
			for (idx = 0; idx < theCount; idx++) {
				// Create a new resource in the scrap rez map
				theRezType = new CRezType(infoList[idx].flavorType, sScrapRezMap);
				theRezObj = new CRezObj(theRezType);
				
				if (theRezObj != nil && theRezType != nil) {
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
				}
				// The RezObj must be deleted before the RezType because 
				// of the associated objects model.
				if (theRezObj != nil) {
					delete theRezObj;
					theRezObj = nil;
				} 
				if (theRezType != nil) {
					delete theRezType;
					theRezType = nil;
				} 
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

// 		switch (sScrapContext) {
// 			case scrap_rezmap: 
// 			break;
// 			
// 			case scrap_bitmap:
// 			break;
// 			
// 			default:
// 			break;
// 		}

void
CRezClipboard::ExportSelf()
{
	short	numTypes;
	ResType theType;
	Handle	theRezHandle;
	OSErr	error = noErr;

	// Clear the data on the scrap and get a new scrapRef
	ClearData();
	
	error = sScrapRezMap->CountAllTypes(numTypes);
	if (error != noErr || numTypes == 0) {return;}
	
	for (UInt16 i = 1; i <= numTypes; i++ ) {
		
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
//	¥ DataArrayToScrapRezMap											[private]
// ---------------------------------------------------------------------------
//	Set the ScrapRezMap contents to the data specified by a pointer and length.
//
//	inReset specifies whether to clear the existing contents of the
//	ScrapRezMap before storing the new data.

void
CRezClipboard::DataArrayToScrapRezMap(
	ResType		inDataType,
	Ptr			inDataPtr,
	SInt32		inDataLength,
	Boolean		inReset)
{
#pragma unused(inDataType, inDataLength)
	LArray* theArray = (LArray*) inDataPtr;
	LArrayIterator	iterator(*theArray);
	CRezObjItem *	theItem = nil;	
	CRezObj *		theRezObj = nil;
	OSErr			error = noErr;
	short			theAttrs;
	
	if (inReset) {
		// Reset the scrap rez map
		DeleteLocalScrap();
		NewLocalScrap();
	} 
	
	while (iterator.Next(&theItem)) {
		theRezObj = new CRezObj( *((CRezObjItem *)theItem)->GetRezObj() );
		theAttrs = theRezObj->GetAttributes();
		
		theRezObj->SetOwnerRefnum(sScrapRefnum);
		error = theRezObj->Add();
		
		if (theAttrs != 0) {
			// Write the attributes in the scrap rezmap
			error = theRezObj->SetAttributesInMap(theAttrs);
		} 
		error = theRezObj->Changed();
		if (theRezObj != nil) {
			delete theRezObj;
		} 
	}
	error = sScrapRezMap->Update();
}


// ===========================================================================
//	StClipboardContext stack-based class
// ===========================================================================
//
// Constructor saves current clipboard context. Destructor restores it or
// sets it to the default value.


StClipboardContext::StClipboardContext()
{
	mOriginalContext = CRezClipboard::GetScrapContext();
	mResetPrevious = false;
	
	CRezClipboard::SetScrapContext(scrap_default);
}


StClipboardContext::StClipboardContext( SInt32 inContext, Boolean inResetPrevious )
{
	mOriginalContext = CRezClipboard::GetScrapContext();
	mResetPrevious = inResetPrevious;
	
	CRezClipboard::SetScrapContext(inContext);
}


StClipboardContext::~StClipboardContext()
{
	Restore();
}


void
StClipboardContext::Restore()
{
	if (mResetPrevious) {
		CRezClipboard::SetScrapContext(mOriginalContext);
	} else {
		CRezClipboard::SetScrapContext(scrap_default);
	}
}



PP_End_Namespace_PowerPlant
