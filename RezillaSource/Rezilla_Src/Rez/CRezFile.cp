// ===========================================================================
// CRezFile.cp					
// 
//                       Created: 2003-04-24 14:17:20
//             Last modification: 2004-03-15 09:03:01
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CRezFile.h"
#include "CRezillaApp.h"
// #include "RezillaConstants.h"
#include "UMiscUtils.h"
#include "CRezMap.h"
#include "CRezObj.h"
#include "CRezMapTable.h"

#include <UMemoryMgr.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//  ¥ CRezFile			Default Constructor		  [public]
// ---------------------------------------------------------------------------

CRezFile::CRezFile()
{
    mFileSpec.vRefNum	= 0;
    mFileSpec.parID		= 0;
    mFileSpec.name[0]	= 0;
    mRefNum				= kResFileNotOpened;
	mUsedFork			= CRezillaApp::sDefaultCreatingFork;
}


// ---------------------------------------------------------------------------
//  ¥ CRezFile			Constructor			  [public]
// ---------------------------------------------------------------------------
// Construct a CRezFile object from an FSSpec with already determined 
// refnum and fork.

CRezFile::CRezFile(const FSSpec& inFileSpec, short inRefnum, SInt16 inFork)
{
    mFileSpec	= inFileSpec;
    mRefNum		= inRefnum;
    mUsedFork	= inFork;
 	FSpMakeFSRef( &mFileSpec, &mFileRef );
}


// ---------------------------------------------------------------------------
//  ¥ CRezFile			Constructor			  [public]
// ---------------------------------------------------------------------------
// Construct a CRezFile from a Toolbox File System Specification. Refnum 
// and fork can be set later with a call to OpenFile.

CRezFile::CRezFile(const FSSpec& inFileSpec)
{
    mFileSpec	= inFileSpec;
    mRefNum		= kResFileNotOpened;
    mUsedFork	= CRezillaApp::sDefaultCreatingFork;
// 	FSpMakeFSRef( &mFileSpec, &mFileRef );
}


// ---------------------------------------------------------------------------
//  ¥ CRezFile			Constructor			  [public]
// ---------------------------------------------------------------------------
// Construct a File from an Alias
//
// outWasChanged indicates if the AliasHandle was changed during resolution
// inFromFile is a File Specifier for the starting point for a relative
// 	search. If nil, an absolute search is performed

CRezFile::CRezFile(
	AliasHandle		inAlias,
	Boolean&		outWasChanged,
	FSSpec*			inFromFile)
{
	OSErr err = ::ResolveAlias(inFromFile, inAlias, 
				     &mFileSpec, &outWasChanged);

	mRefNum = kResFileNotOpened;
	ThrowIfOSErr_(err);
}


// ---------------------------------------------------------------------------
//  ¥ ~CRezFile			Destructor			  [public]
// ---------------------------------------------------------------------------

CRezFile::~CRezFile()
{
	try {	// Don't throw out of a destructor
		CloseFile();
	} catch (...) { }
}


// ---------------------------------------------------------------------------
//  ¥ GetSpecifier
// ---------------------------------------------------------------------------

void
CRezFile::GetSpecifier(FSSpec& outFileSpec) const
{
	outFileSpec = mFileSpec;		// Copy FSSpec struct
}


// ---------------------------------------------------------------------------
//  ¥ SetSpecifier
// ---------------------------------------------------------------------------
// This has the side effect of closing any open forks of the file identified
// by the old Specifier

void
CRezFile::SetSpecifier( const FSSpec& inFileSpec)
{
    CloseFile();
    
    mFileSpec = inFileSpec;
}


// ---------------------------------------------------------------------------
//  ¥ UsesSpecifier
// ---------------------------------------------------------------------------
// Returns whether the RezFile's FSSpec is the same as the input FSSpec

bool
CRezFile::UsesSpecifier(const FSSpec& inFileSpec) const
{
    return EqualFileSpec(mFileSpec, inFileSpec);
}


// ---------------------------------------------------------------------------
//  ¥ SpecifierExists
// ---------------------------------------------------------------------------
// Returns whether the File's FSSpec corresponds to an existing disk file

bool
CRezFile::SpecifierExists() const
{
    // File exists if we can get its Finder info
    FInfo	finderInfo;
    
    return (::FSpGetFInfo(&mFileSpec, &finderInfo) == noErr);
}


// ---------------------------------------------------------------------------
//  ¥ EqualFileSpec													  [static]
// ---------------------------------------------------------------------------
//    Compare two FSSpec structs for equality: compare each  field  in  FSSpec
//    struct. EqualString() [case insensitive, diacritical sensitive]  is  the
//    same comparison used by the File System

bool
CRezFile::EqualFileSpec(
	const FSSpec&	inFileSpecA,
	const FSSpec&	inFileSpecB)
{

	return (inFileSpecA.vRefNum == inFileSpecB.vRefNum) &&
		   (inFileSpecA.parID == inFileSpecB.parID) &&
		   ::EqualString(inFileSpecA.name, inFileSpecB.name, false, true);
}


// ---------------------------------------------------------------------------
//  ¥ MakeAlias
// ---------------------------------------------------------------------------
// Return a newly created Alias for a File
//
// inFromFile is a File Specifier for the starting point for a relative
// 	search. Pass nil if you don't need relative path information.

AliasHandle
CRezFile::MakeAlias(
	FSSpec*		inFromFile)
{
	AliasHandle	theAlias;
	OSErr	err = ::NewAlias(inFromFile, &mFileSpec, &theAlias);

	return theAlias;
}


// ---------------------------------------------------------------------------
//  ¥ CreateNewFile
// ---------------------------------------------------------------------------
// Create a new disk File, with an empty data fork and a resoure map.
// This fuction also opens the corresponding resource fork.

OSErr
CRezFile::CreateNewFile()
{
	FSRef			parentRef;
	FSCatalogInfo	catalogInfo;
	HFSUniStr255	unicodeName;
	OSErr 			error = noErr;
	
	switch (mUsedFork) {
		case rezfile_datafork:
		// If the file already exists, delete it and re-create it
		if (SpecifierExists()) {
			::FSpDelete(&mFileSpec);
		} 
		error = ::FSpCreate(&mFileSpec, '????', '????', smSystemScript);
		// Get an FSRef
		error = FSpMakeFSRef( &mFileSpec, &mFileRef );
		// Get parentRef
		error = FSGetCatalogInfo(&mFileRef, kFSCatInfoNodeID, &catalogInfo, NULL, NULL, &parentRef);
		error = UMiscUtils::HFSNameToUnicodeName(mFileSpec.name, &unicodeName);
// 		error = FSCreateResourceFile(&parentRef, mFileSpec.name[0], unicodeName.unicode, kFSCatInfoNone, NULL, 0, NULL, &mFileRef, &mFileSpec);
		error = FSCreateResourceFile(&parentRef, unicodeName.length, unicodeName.unicode, kFSCatInfoNone, NULL, 0, NULL, &mFileRef, &mFileSpec);
		break;
		
		case rezfile_rezfork:
		::FSpCreateResFile(&mFileSpec, 'RSED', 'rsrc', smSystemScript);
		error = ::ResError();
		break;
	}
	
	return error;
}


// ---------------------------------------------------------------------------
//  ¥ OpenFile
// ---------------------------------------------------------------------------
// Open the resource fork of a File with the specified permissions and
// return the reference number for the opened fork in the mRefNum data 
// member.

OSErr
CRezFile::OpenFile(SInt8 inPermissions)
{
	OSErr error = noErr;

	// Don't load "preload" resources
	::SetResLoad( false );

	switch (mUsedFork) {
		case rezfile_datafork:
			error = FSOpenResourceFile( &mFileRef, 0, nil, inPermissions, &mRefNum );
		break;
		
		case rezfile_rezfork:
		mRefNum = ::FSpOpenResFile(&mFileSpec, inPermissions);
		error = ::ResError();
		break;
		
		default:
		error = resNotFound;
		break;
	}

	::SetResLoad( true );
	
	return error;
}


// ---------------------------------------------------------------------------
//  ¥ CloseFile
// ---------------------------------------------------------------------------
// Close the resource fork of a File

OSErr
CRezFile::CloseFile()
{
	OSErr error = noErr;
	
    if (mRefNum != kResFileNotOpened) {
		::CloseResFile(mRefNum);
		error = ::ResError();
		mRefNum = kResFileNotOpened;
		::FlushVol(nil, mFileSpec.vRefNum);
    }
	return error;
}


// ---------------------------------------------------------------------------
//  ¥ ReadFile
// ---------------------------------------------------------------------------
// Read the entire contents of a File's data fork into a newly created
// Handle. The caller is responsible for disposing of the Handle.

Handle
CRezFile::ReadFile()
{
	SInt32	fileLength;
	OSErr	err = ::GetEOF(mRefNum, &fileLength);
	ThrowIfOSErr_(err);

	StHandleBlock	dataHandle(fileLength);

	err = ::SetFPos(mRefNum, fsFromStart, 0);
	ThrowIfOSErr_(err);

	err = ::FSRead(mRefNum, &fileLength, *dataHandle);
	ThrowIfOSErr_(err);

	return dataHandle.Release();
}


// ---------------------------------------------------------------------------
//  ¥ WriteFile
// ---------------------------------------------------------------------------
// Write to the data fork of a File from a buffer
//
// The buffer contents completely replace any existing data

SInt32
CRezFile::WriteFile(
	const void*		inBuffer,
	SInt32			inByteCount)
{
	SInt32	bytesWritten = inByteCount;

	OSErr	err = ::SetFPos(mRefNum, fsFromStart, 0);
	ThrowIfOSErr_(err);

	err = ::FSWrite(mRefNum, &bytesWritten, inBuffer);
	::SetEOF(mRefNum, bytesWritten);

	ThrowIfOSErr_(err);

	return bytesWritten;
}


// ---------------------------------------------------------------------------
//  ¥ CopyFromRezMap
// ---------------------------------------------------------------------------

OSErr
CRezFile::CopyFromRezMap(CRezMap * srcRezmap)
{
	short	numTypes, i;
	short	numResources, j;
    ResType theType;
	OSErr	error = noErr;
	Handle	theRezHandle;
	short	theAttrs;
	CRezObj *	theRezObj;
		
	error = srcRezmap->CountAllTypes(numTypes);
	if (error != noErr || numTypes == 0) {return error;}
	
	for ( i = 1; i <= numTypes; i++ )
	{
		// Read in each data type
		srcRezmap->GetTypeAtIndex( i, theType );
		error = srcRezmap->CountForType( theType, numResources);

		for ( j = 1; j <= numResources; j++ )
		{
			// Get the data handle
			error = srcRezmap->GetResourceAtIndex(theType, j, theRezHandle, true);
			
			// Make a rez object out of it
			theRezObj = new CRezObj(theRezHandle, srcRezmap->GetRefnum());
			error = theRezObj->GetAttributesFromMap(theAttrs);
			// Detach the handle before adding it
			error = theRezObj->Detach();
			
			// Change its refnum and add the resource to the new fork
			theRezObj->SetOwnerRefnum(mRefNum);
			error = theRezObj->Add();
			error = theRezObj->Write();
			
			if (theAttrs != 0) {
				// Write the attributes in new rezmap
				error = theRezObj->SetAttributes(theAttrs);
				error = theRezObj->Changed();
			} 
			
			delete theRezObj;
		}
	}
	
	::CloseResFile( srcRezmap->GetRefnum() );
	error = ::ResError();
	::UpdateResFile(mRefNum);

	return error;
}




PP_End_Namespace_PowerPlant
