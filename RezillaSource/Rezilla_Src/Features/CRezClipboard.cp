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
		// Depending on the circumstances when you delete a Clipboard
		// object, you may want to call ExportSelf() in your subclass's
		// destructor if mExportPending is true

// 	#ifdef Debug_Signal
// 	
// 		if (mExportPending) {
// 			SignalStringLiteral_("Custom Clipboard deleted while export is pending");
// 		}
// 		
// 	#endif

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
	
	// Make a new file object.
	if (error == noErr) {
		sScrapRezFile = new CRezFile(theFileSpec, scrapRefNum, fork_datafork);
		sScrapRezMap = new CRezMap(scrapRefNum);
		sScrapRefnum = scrapRefNum;
	} 
		
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
// 			ResType theType;
// 			short theID;
// 			Handle theHandle = ::NewHandle(0);
// 			
// 			if ( UMiscUtils::GetTypeFromScrap(theType) == noErr 
// 				&& mRezMap->UniqueID(theType, theID) == noErr) {
// 				UScrap::GetData(theType, theHandle);
// 				PasteResource(theType, theID, theHandle);
// 			} 
// 			if (theHandle != nil) {
// 				::DisposeHandle(theHandle);
// 			} 
	
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
}


// ---------------------------------------------------------------------------
//	¥ ContentsIsValidHex												   [protected]
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
	
	if (inReset) {
		sScrapRezMap->DeleteAll();
		sScrapRezMap->Update();
	} 
	
	while (iterator.Next(&theItem)) {
		if (theRezObj != nil) {
			delete theRezObj;
		} 
		theRezObj = new CRezObj( *((CRezObjItem *)theItem)->GetRezObj() );
		error = theRezObj->GetAttributesFromMap(theAttrs);
		
		theRezObj->SetOwnerRefnum(sScrapRefnum);
		theRezObj->Add();
		
		if (theAttrs != 0) {
			// Write the attributes in scrap rezmap
			error = theRezObj->SetAttributes(theAttrs);
		} 
		error = theRezObj->Changed();
	}
	error = sScrapRezMap->Update();
}



// ---------------------------------------------------------------------------
//	¥ GetDataFromScrapRezMap											[private]
// ---------------------------------------------------------------------------
//	Set the ScrapRezMap contents to the data specified by a pointer and length.
//
//	inReset specifies whether to clear the existing contents of the
//	ScrapRezMap before storing the new data.
// 
// 	ResType		inDataType,
// 	Ptr			inDataPtr,
// 	SInt32		inDataLength,
// 	Boolean		inReset
// void
// CRezClipboard::GetDataFromScrapRezMap(
// 	ResType		inDataType,
// 	Handle		ioDataH)
// {
// 	short	numTypes, i;
// 	short	numResources, j;
//     ResType theType;
// 	OSErr	error = noErr;
// 	Handle	theRezHandle;
// 	short	theAttrs;
// 	CRezObj *	theRezObj;
// 	
// // 	CRezMap * trgtRezmap = new CRezMap(mRefNum);
// 	
// 	error = sScrapRezMap->CountAllTypes(numTypes);
// 	if (error != noErr || numTypes == 0) {return error;}
// 	
// 	for ( i = 1; i <= numTypes; i++ )
// 	{
// 		// Read in each data type
// 		sScrapRezMap->GetTypeAtIndex( i, theType );
// 		error = sScrapRezMap->CountForType( theType, numResources);
// 
// 		for ( j = 1; j <= numResources; j++ )
// 		{
// 			// Get the data handle
// 			error = sScrapRezMap->GetResourceAtIndex(theType, j, theRezHandle);
// 			
// 			// Make a rez object out of it
// 			theRezObj = new CRezObj(theRezHandle, sScrapRezMap->GetRefnum());
// 			error = theRezObj->GetAttributesFromMap(theAttrs);
// 			// Detach the handle before adding it
// 			error = theRezObj->Detach();
// 			
// 			// Change its refnum and add the resource to the new fork
// 			theRezObj->SetOwnerRefnum(mRefNum);
// 			error = theRezObj->Add();
// 			error = theRezObj->Write();
// 			
// 			if (theAttrs != 0) {
// 				// Write the attributes in new rezmap
// 				error = theRezObj->SetAttributes(theAttrs);
// 				error = theRezObj->Changed();
// 			} 
// 			
// 			delete theRezObj;
// 		}
// 	}
// 	
// // 	::CloseResFile( sScrapRezMap->GetRefnum() );
// // 	error = ::ResError();
// 	::UpdateResFile(mRefNum);
// 
// 	return error;
// }




PP_End_Namespace_PowerPlant


