// ===========================================================================
// CRezClipboard.cp					
//                       Created: 2003-05-11 21:05:08
//             Last modification: 2004-02-22 19:29:53
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2003, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


// #ifdef PowerPlant_PCH
// 	#include PowerPlant_PCH
// #endif

#include "CRezClipboard.h"
#include "CRezMap.h"
#include "UMiscUtils.h"

#include <LClipboard.h>
#include <UMemoryMgr.h>
#include <UScrap.h>

#include <Events.h>


PP_Begin_Namespace_PowerPlant

SInt32		CRezClipboard::sScrapContext = 0;
CRezMap *	CRezClipboard::sScrapRezMap;

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

// Close the ScrapRezMap

}


// ---------------------------------------------------------------------------
//	¥ InitScrapRezMap												   [protected]
// ---------------------------------------------------------------------------
// /Developer/Examples/Printing/App/BasicPrintLoop/PrintLoop/Source/main.c
// /Developer/Examples/Printing/Printer/Plugins/SamplePM/Source/RasterUtils.cp


OSErr
CRezClipboard::InitScrapRezMap()
{
	// 	CFAllocatorRef		allocator			= CFAllocatorGetDefault();
	CFBundleRef mainBundleRef;
	CFURLRef 	mainBundleURL, scrapRezMapURL, resUrl;
	FSRef 		theFSRef, parentRef;
	FSSpec		theFileSpec;
	OSStatus  	err = noErr;
	short		scrapRefNum;
	HFSUniStr255	unicodeName;
	ConstStr31Param hfsName = "\pScrapRezMap.rsrc";
	
	mainBundleRef = NULL;
	mainBundleURL = NULL;
	scrapRezMapURL = NULL;
	resUrl = NULL;
	
	mainBundleRef = CFBundleGetMainBundle();
	if (mainBundleRef == NULL) {err = fnfErr; goto bail;}
	
	scrapRezMapURL = CFBundleCopyResourceURL(mainBundleRef, CFSTR("ScrapRezMap"), CFSTR("rsrc"), NULL);
	
	if (scrapRezMapURL == nil) {
		// Create the file
		mainBundleURL = CFBundleCopyBundleURL(mainBundleRef);
		resUrl = CFBundleCopyResourcesDirectoryURL(mainBundleRef);
		
		CFURLGetFSRef( resUrl, &parentRef);
		err = UMiscUtils::HFSNameToUnicodeName(hfsName, &unicodeName);
		err = FSCreateResourceFile(&parentRef, hfsName[0], unicodeName.unicode, kFSCatInfoNone, NULL, 0, NULL, &theFSRef, &theFileSpec);
		err = FSOpenResourceFile( &theFSRef, 0, nil, fsRdWrPerm, &scrapRefNum );
	} else {
		if ( CFURLGetFSRef( scrapRezMapURL, &theFSRef) )
		{
			err = FSGetCatalogInfo( &theFSRef, kFSCatInfoNone, NULL, NULL, &theFileSpec, NULL );
		}
	} 
// 	scrapRefNum = CFBundleOpenBundleResourceMap(scrapRezMapURL);
	
	
	// Make a new file object.
	sScrapRezMap = new CRezMap(scrapRefNum);	
	
	bail:
	if (mainBundleRef != NULL) CFRelease(mainBundleRef);
	if (scrapRezMapURL != NULL) CFRelease(scrapRezMapURL);
	return err;
}
// 		if (resUrl) {
// 			CFURLRef scrapRezMapURL = CFURLCreateCopyAppendingPathComponent(NULL, resUrl,
// 																			CFSTR("ScrapRezMap.rsrc"), false);
// 		} 
// 	FSRef theFSRef;
// 	FSRef theParentRef;
// 	UniChar	theFileName[] = { 'o', 'u', 't', 'p', 'u', 't', '.', 's', 'd', '2' };
// 	OSStatus theError = FSPathMakeRef((const UInt8*)"/Volumes/Annex/Users/moorf/output.sd2", &theFSRef, NULL);
// 	if(theError != fnfErr)
// 	{
// 		FSDeleteObject(&theFSRef);
// 	}
// 	theError = FSPathMakeRef((const UInt8*)"/Volumes/Annex/Users/moorf", &theParentRef, NULL);
// 	theError = FSCreateFileUnicode(&theParentRef, 10, theFileName, kFSCatInfoNone, NULL, &theFSRef, NULL);
// 	theError = FSOpenFork(&theFSRef, 0, NULL, fsRdWrPerm, &mOutputFileRefNum);
// EXTERN_API( OSErr )
// FSCreateFileUnicode(
//   const FSRef *          parentRef,
//   UniCharCount           nameLength,
//   const UniChar *        name,
//   FSCatalogInfoBitmap    whichInfo,
//   const FSCatalogInfo *  catalogInfo,       /* can be NULL */
//   FSRef *                newRef,            /* can be NULL */
//   FSSpec *               newSpec) 
// OSErr
// UMiscUtils::HFSNameToUnicodeName(
// 	ConstStr31Param hfsName,
// 	HFSUniStr255 *unicodeName)

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
//	This implementation gets the data from the global scrap. Subclasses
//	should override to maintain a local scrap.

SInt32
CRezClipboard::GetDataSelf(
	ResType		inDataType,
	Handle		ioDataH)
{
	SInt32 dataSize = 0;
	
	switch (sScrapContext) {
	  case scrap_rezmap:
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
//	This implementation sets the data in the global scrap. Subclasses
//	should override to maintain a local scrap.

void
CRezClipboard::SetDataSelf(
	ResType		inDataType,
	Ptr			inDataPtr,
	SInt32		inDataLength,
	Boolean		inReset)
{
	switch (sScrapContext) {
	  case scrap_rezmap:
		UScrap::SetData(inDataType, inDataPtr, inDataLength, inReset);
		break;
		
	  case scrap_hexeditHexdata:
	  case scrap_hexeditTxtdata:
	  default:
		UScrap::SetData(inDataType, inDataPtr, inDataLength, inReset);
		break;
		
	}

	mExportPending = false;
}


// ---------------------------------------------------------------------------
//	¥ ImportSelf												   [protected]
// ---------------------------------------------------------------------------
//	Import the data in the global scrap to a local scrap
//
//	This implementation does nothing since this class uses the global
//	scrap when setting and getting clipboard data. Subclasses should
//	override if they maintain a local scrap.

void
CRezClipboard::ImportSelf()
{
}


// ---------------------------------------------------------------------------
//	¥ ExportSelf												   [protected]
// ---------------------------------------------------------------------------
//	Export the data in a local scrap to the global scrap
//
//	This implementation does nothing since this class uses the global
//	scrap when setting and getting clipboard data. Subclasses should
//	override if they maintain a local scrap.

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



PP_End_Namespace_PowerPlant
