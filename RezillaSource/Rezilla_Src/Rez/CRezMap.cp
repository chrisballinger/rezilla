// ===========================================================================
// CRezMap.cp					
// 
//                       Created: 2003-04-23 12:32:10
//             Last modification: 2006-07-14 09:58:50
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2003-2006
// All rights reserved.
// ===========================================================================

#include "CRezMap.h"
#include "CRezObj.h"
#include "CRezType.h"
#include "UResources.h"
#include "RezillaConstants.h"

#include <LCommander.h>

// Statics
TArray<CRezMap*>	CRezMap::sRezMapList;


// ---------------------------------------------------------------------------
//   CRezMap														[public]
// ---------------------------------------------------------------------------
// CRezMaps do not have a super model object. They are elements of the null
// top container, the "application" object.

CRezMap::CRezMap(short inRefnum, CRezMapDoc * inOwnerDoc)
	: LModelObject( NULL, rzom_cRezMap), mRefNum(inRefnum)
{	
	mOwnerDoc = inOwnerDoc;
	
	// Keep a static list of all the RezMaps opened via a RezMapDoc
	if (mOwnerDoc != nil) {
		sRezMapList.AddItem(this);
	} 
	
	// Don't use PP's list model
}


// ---------------------------------------------------------------------------
//     ~CRezMap														[public]
// ---------------------------------------------------------------------------

CRezMap::~CRezMap()
{
	if (mOwnerDoc != nil) {
		sRezMapList.Remove(this);
	} 
}


// ---------------------------------------------------------------------------
//   Close														[public]
// ---------------------------------------------------------------------------

OSErr
CRezMap::Close()
{
	OSErr error = noErr;
    if (mRefNum != kResFileNotOpened) {
		::CloseResFile(mRefNum);
		error = ::ResError();
		mRefNum = kResFileNotOpened;
    }
	return error;
}


// ---------------------------------------------------------------------------
//   Update														[public]
// ---------------------------------------------------------------------------
// From doc: If the mapCompactBit bit is set to 1, the Resource Manager
// compacts the resource fork when it updates the file. The Resource Manager
// sets this attribute when a resource is removed or when a resource is made
// larger and thus must be written at the end of a resource fork. You may want
// to set the mapCompactBit attribute to force the Resource Manager to compact
// a resource fork when your changes have made resources smaller.

OSErr
CRezMap::Update()
{
    ::UpdateResFile(mRefNum);
    return ::ResError();
}


// ---------------------------------------------------------------------------
//   CountForType													[public]
// ---------------------------------------------------------------------------
// Count the number of resources of a given type in current resource map.

OSErr
CRezMap::CountForType(ResType inType, short & outCount) const
{
    StRezRefSaver saver(mRefNum);
    outCount = ::Count1Resources(inType);
    return ::ResError();
}


// ---------------------------------------------------------------------------
//   CountAllTypes													[public]
// ---------------------------------------------------------------------------
// Count the number of types in current resource map.

OSErr
CRezMap::CountAllTypes(short & outCount) const
{
    StRezRefSaver saver(mRefNum);
    outCount = ::Count1Types();
    return ::ResError();
}


// ---------------------------------------------------------------------------
//   CountAllResources												[public]
// ---------------------------------------------------------------------------
// Count the number of resources of any type in current resource map.

OSErr
CRezMap::CountAllResources(short & outCount) const
{
    short numTypes;
    short subCount;
    ResType theType;
    
    OSErr error = CountAllTypes(numTypes);
    outCount = 0;
    
    StRezRefSaver saver(mRefNum);
    if (error == noErr) {
	for ( UInt16 i = 1; i <= numTypes; i++ )
	{
	    ::Get1IndType( &theType, i );
	    CountForType(theType, subCount);
	    outCount += subCount;
	}
    } 
    return ::ResError();
}


// ---------------------------------------------------------------------------
//   ResourceExists												[public]
// ---------------------------------------------------------------------------
// 
// This made a duplicate with HasResourceWithTypeAndId(): removed


// ---------------------------------------------------------------------------
//   GetResourceAtIndex											[public]
// ---------------------------------------------------------------------------

OSErr
CRezMap::GetResourceAtIndex(ResType inType, short inIdx, Handle & outHandle, Boolean loadIt)
{
    StRezRefSaver saver(mRefNum);
	if (!loadIt) {
		::SetResLoad(false);
	} 
    outHandle = ::Get1IndResource(inType, inIdx);
	if (!loadIt) {
		::SetResLoad(true);
	} 
	return ::ResError();
}


// ---------------------------------------------------------------------------
//   GetWithID													[public]
// ---------------------------------------------------------------------------
// Get a handle to a resource of a given type with a given ID
// from current resource map.

OSErr
CRezMap::GetWithID(ResType inType, short inID, Handle & outHandle, Boolean loadIt)
{
	OSErr error;
    StRezRefSaver saver(mRefNum);
	if (!loadIt) {
		::SetResLoad(false);
	} 
    outHandle = ::Get1Resource(inType, inID);
	error = ::ResError();
	if (!loadIt) {
		::SetResLoad(true);
	} 
    return error;
}


// ---------------------------------------------------------------------------
//   GetWithName													[public]
// ---------------------------------------------------------------------------
// Get a handle to a resource of a given type with a given name in the
// current resource map. Unfortunately Get1NamedResource() appears to be
// case insensitive! So we must get the list of all resources of the given
// type and check the names directly.

OSErr
CRezMap::GetWithName(ResType inType, ConstStr255Param inName, Handle & outHandle, Boolean loadIt)
{
	OSErr	error = noErr;
	short	theCount = 0;
	short	theID;
	ResType	theType;
	Str255	theName;
	Boolean found = false;

	StRezRefSaver saver(mRefNum);
	if (!loadIt) {
		::SetResLoad(false);
	} 
	theCount = ::Count1Resources(inType);
	error = ::ResError();
	if (error == noErr) {
		for ( UInt16 i = 1; i <= theCount; i++ ) {
			outHandle = ::Get1IndResource(inType, i);
			error = ::ResError();
			if (error == noErr) {
				::GetResInfo(outHandle, &theID, &theType, theName);
				error = ::ResError();
			} 
			if (error == noErr 
				&& 
				LString::CompareBytes(theName + 1, inName + 1, theName[0], inName[0]) == 0) {
					found = true;
					break;
			} 
		}
	}
	if (!found) {
		error = resNotFound;
	} 
	if (!loadIt) {
		::SetResLoad(true);
	} 
    return error;
}


// ---------------------------------------------------------------------------
//   FindResource										[public]
// ---------------------------------------------------------------------------
// If the createIt argument is true, FindResource will create a resource of
// the given type and ID if none exists already: this can occur when an
// icon family is edited and some member of the family was initially
// missing from the map. If createIt is false and no resource exists, the 
// function returns NULL.

CRezObj *
CRezMap::FindResource(ResType inType, short inID, Boolean loadIt, Boolean createIt)
{
	OSErr		error;
	CRezObj *	theRez = NULL;
	Handle		theHandle = NULL;
	
	StRezRefSaver saver(mRefNum);
	if (!loadIt) {
		::SetResLoad(false);
	} 
	
	theHandle = ::Get1Resource(inType, inID);
	error = ::ResError();
	
	if (theHandle == NULL) {
		if (createIt) {
			// The resource does not exist. Create it now.
			CRezType *	theRezType = new CRezType(inType, this);
			Str255		name = "\p";
			
			theRez = new CRezObj(mRefNum, inType, inID, &name);
			error = theRez->Add();
		} 
	} else {
		theRez = new CRezObj(theHandle, mRefNum);
	}
	
	if (!loadIt) {
		::SetResLoad(true);
	} 
	
	return theRez;
}


// CRezObj *
// CRezMap::FindResource(ResType inType, short inID, Boolean loadIt, Boolean createIt)
// {
// 	OSErr		error;
// 	CRezObj *	theRez = NULL;
// 	Handle		theHandle = NULL;
// 	
// 	StRezRefSaver saver(mRefNum);
// 	if (!loadIt) {
// 		::SetResLoad(false);
// 	} 
// 	
// 	theHandle = ::Get1Resource(inType, inID);
// 	error = ::ResError();
// 	
// 	if (theHandle == NULL) {
// 		if (createIt) {
// 			// The resource does not exist. Create it now.
// 			CRezType *	theRezType = new CRezType(inType, this);
// 			Str255		name = "\p";
// 			
// 			theRez = new CRezObj(theRezType, inID, &name);
// 			error = theRez->Add();
// 			delete theRezType;
// 		} 
// 	} else {
// 		theRez = new CRezObj(theHandle, mRefNum);
// 	}
// 	
// 	if (!loadIt) {
// 		::SetResLoad(true);
// 	} 
// 	
// 	return theRez;
// }


// ---------------------------------------------------------------------------
//   HasResourceWithTypeAndId										[public]
// ---------------------------------------------------------------------------
// Looks in the resource map to see if an entry with the specified type and the
// specified ID already exists. 

Boolean
CRezMap::HasResourceWithTypeAndId(ResType inType, short inID)
{
	Handle	theHandle = nil;
	Boolean	hasRes = false;
	
	OSErr error = GetWithID(inType, inID, theHandle);
	if (error == noErr && theHandle != nil) {
		hasRes = true;
	} 
	return hasRes;
}


// ---------------------------------------------------------------------------
//   HasResourceWithTypeAndName									[public]
// ---------------------------------------------------------------------------
// Looks in the resource map to see if an entry with the specified type and the
// specified name already exists. 

Boolean
CRezMap::HasResourceWithTypeAndName(ResType inType, ConstStr255Param inName)
{
	Handle	theHandle = nil;
	Boolean	hasRes = false;
	
	OSErr error = GetWithName(inType, inName, theHandle);
	if (error == noErr && theHandle != nil) {
		hasRes = true;
	} 
	return hasRes;
}


// ---------------------------------------------------------------------------
//   GetAllTypes													[public]
// ---------------------------------------------------------------------------
// Get an array of all types current resource map.

OSErr
CRezMap::GetAllTypes( TArray<ResType>* & outArray ) const
{
    short numTypes;
    ResType theType;
    
    StRezRefSaver saver(mRefNum);
    OSErr error = CountAllTypes(numTypes);
    
    if (error == noErr) {
	for ( UInt16 i = 1; i <= numTypes; i++ )
	{
	    ::Get1IndType(&theType, i);
	    error = ::ResError();
	    if (error != noErr) {
		break;
	    } 
	    outArray->AddItem(theType);
	}
    } 
    return error;
}


// ---------------------------------------------------------------------------
//   GetTypeAtIndex												[public]
// ---------------------------------------------------------------------------
// Get the type given an index.

OSErr
CRezMap::GetTypeAtIndex(short inIdx, ResType & outType)
{
    StRezRefSaver saver(mRefNum);
	::Get1IndType( &outType, inIdx);
    return ::ResError();
}


// ---------------------------------------------------------------------------
// UniqueID 														[public]
// ---------------------------------------------------------------------------
// The Toolbox ::Unique1ID() API returns random values. The present
// function attempts to find the first ID available immediately above the
// given startID in the specified type. If it fails, use ::Unique1ID() as a
// fallback.

OSErr
CRezMap::UniqueID(ResType inType, short & outID, short startID)
{
	short		theID;
	OSErr		error;
	Boolean		useRandom = false;
	StRezRefSaver saver(mRefNum);
	
	CRezType theRezType(inType, this);
	
	LLongComparator* theIDComparator = new LLongComparator;
	TArray<short>* theIdArray = new TArray<short>(theIDComparator, true);
	TArrayIterator<short>	idIterator(*theIdArray);
	
	error = theRezType.GetAllRezIDs(theIdArray);
	outID = startID;
	
	if (error == noErr) {
		while (idIterator.Next(theID)) {
			if (outID < theID) {
				break;
			} else if (theID >= startID) {
				if (theID == 32767) {
					useRandom = true;
					break;
				} else {
					outID = theID + 1;
				}
			}
		}
	} else {
		useRandom = true;
	}
	
	if (useRandom) {
		outID = ::Unique1ID(inType);
		error = ::ResError();
	} 
	
	return error;
}


// ---------------------------------------------------------------------------
//   GetMapAttributes													[public]
// ---------------------------------------------------------------------------
// 		  mapReadOnly       = 128
// 		  mapCompact        = 64
// 		  mapChanged        = 32
// 		  
// 		  mapReadOnlyBit	= 7
// 		  mapCompactBit		= 6
// 		  mapChangedBit		= 5

OSErr
CRezMap::GetMapAttributes(short & outResFileAttrs) const
{
	OSErr error;
	
    StRezRefSaver saver(mRefNum);
    outResFileAttrs = ::GetResFileAttrs(mRefNum);
    error = ::ResError();
	return error;
}


// ---------------------------------------------------------------------------
//   SetMapAttributes													[public]
// ---------------------------------------------------------------------------

OSErr
CRezMap::SetMapAttributes(short inResFileAttrs)
{
    StRezRefSaver saver(mRefNum);
    ::SetResFileAttrs(mRefNum, inResFileAttrs);
    return ::ResError();
}


// ---------------------------------------------------------------------------
//   UnsetFileAttrs											[public]
// ---------------------------------------------------------------------------

OSErr
CRezMap::UnsetFileAttrs(short inResFileAttrs)
{
    StRezRefSaver saver(mRefNum);
    short theAttrs = ::GetResFileAttrs(mRefNum);
    theAttrs  &= ~inResFileAttrs;
    ::SetResFileAttrs(mRefNum, theAttrs);
    return ::ResError();
}


// ---------------------------------------------------------------------------
//   DeleteAll													[public]
// ---------------------------------------------------------------------------
// Delete all the resources from the resource map.

OSErr
CRezMap::DeleteAll()
{
	short		numTypes, numResources;
	ResType		theType;
	Handle		theHandle;
	CRezObj *	theRezObj = nil;
	OSErr		error;
	
	error = CountAllTypes(numTypes);	
	if (error == noErr) {
		for (UInt16 i = 1; i <= numTypes; i++) {
			error = GetTypeAtIndex(i, theType);
			if (error == noErr) {
				error = CountForType(theType, numResources);
				if (error == noErr) {
					for (UInt16 j = 1; j <= numResources; j++) {
						if (theRezObj != nil) {
							delete theRezObj;
						} 
						error = GetResourceAtIndex(theType, j, theHandle);
						// if theHandle && *theHandle <- is it in memory ?
						if (theHandle) {
							theRezObj = new CRezObj(theHandle, mRefNum);
							error = theRezObj->Remove();
						} 
					}
				} 
			} 
		}
	} 
	return error;
}


// ---------------------------------------------------------------------------
//   IsUnderVersionControl										[public]
// ---------------------------------------------------------------------------

Boolean
CRezMap::IsUnderVersionControl()
{
	OSErr	error;
	short 	theCount = 0;
	error = CountForType( (ResType) "ckid", theCount);
	return (error == noErr && theCount > 0);
}


