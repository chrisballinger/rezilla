// ===========================================================================
// CRezMap.cp					
// 
//                       Created: 2003-04-23 12:32:10
//             Last modification: 2003-06-03 06:24:06
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CRezMap.h"
#include "UResources.h"



// ---------------------------------------------------------------------------
//  ¥ CRezMap														[public]
// ---------------------------------------------------------------------------

CRezMap::CRezMap(short inRefnum)
{
    mRefnum	= inRefnum;
    mMapAttributes	= 0;
}


// ---------------------------------------------------------------------------
//  ¥ ~CRezMap														[public]
// ---------------------------------------------------------------------------

CRezMap::~CRezMap()
{
}


// ---------------------------------------------------------------------------
//  ¥ UpdateResFile														[public]
// ---------------------------------------------------------------------------
// 		ThrowIfResError_();

OSErr
CRezMap::Update()
{
    ::UpdateResFile(mRefnum);
    return ::ResError();
}


// ---------------------------------------------------------------------------
//  ¥ CountForType													[public]
// ---------------------------------------------------------------------------
// Count the number of resources of a given type in current resource map.

OSErr
CRezMap::CountForType(ResType inType, short & outCount)
{
    StRezReferenceSaver saver(mRefnum);
    outCount = ::Count1Resources(inType);
    return ::ResError();
}


// ---------------------------------------------------------------------------
//  ¥ CountAllTypes													[public]
// ---------------------------------------------------------------------------
// Count the number of types in current resource map.

OSErr
CRezMap::CountAllTypes(short & outCount)
{
    StRezReferenceSaver saver(mRefnum);
    outCount = ::Count1Types();
    return ::ResError();
}


// ---------------------------------------------------------------------------
//  ¥ CountAllResources												[public]
// ---------------------------------------------------------------------------
// Count the number of resources of any type in current resource map.

OSErr
CRezMap::CountAllResources(short & outCount)
{
    short numTypes;
    short subCount;
    ResType theType;
    
    OSErr error = CountAllTypes(numTypes);
    outCount = 0;
    
    StRezReferenceSaver saver(mRefnum);
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
//  ¥ GetResourceAtIndex											[public]
// ---------------------------------------------------------------------------

OSErr
CRezMap::GetResourceAtIndex(ResType inType, short inIdx, Handle & outHandle)
{
    StRezReferenceSaver saver(mRefnum);
    outHandle = ::Get1IndResource( inType, inIdx );
	return ::ResError();
}



// ---------------------------------------------------------------------------
//  ¥ ResourceExists													[public]
// ---------------------------------------------------------------------------
// Check whether a resource of a given type with a given ID
// exists in the current resource map.

Boolean
CRezMap::ResourceExists(ResType inType, short inID)
{
	OSErr error;
	Handle theHandle;
	
    StRezReferenceSaver saver(mRefnum);
	::SetResLoad(false);
    theHandle = ::Get1Resource(inType, inID);
	error = ::ResError();
	::SetResLoad(true);
    return (theHandle != nil && ::ResError() == noErr);
}


// ---------------------------------------------------------------------------
//  ¥ GetWithID													[public]
// ---------------------------------------------------------------------------
// Get a handle to a resource of a given type with a given ID
// from current resource map.

OSErr
CRezMap::GetWithID(ResType inType, short inID, Handle & outHandle, Boolean loadIt)
{
	OSErr error;
    StRezReferenceSaver saver(mRefnum);
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
//  ¥ GetWithName														[public]
// ---------------------------------------------------------------------------
// Get a handle to a resource of a given type with a given name
// from current resource map.

OSErr
CRezMap::GetWithName(ResType inType, ConstStr255Param inName, Handle & outHandle, Boolean loadIt)
{
	OSErr error;
    StRezReferenceSaver saver(mRefnum);
	if (!loadIt) {
		::SetResLoad(false);
	} 
    outHandle = ::Get1NamedResource(inType, inName);
	error = ::ResError();
	if (!loadIt) {
		::SetResLoad(true);
	} 
    return error;
}


// ---------------------------------------------------------------------------
//  ¥ HasResourceWithTypeAndId											[public]
// ---------------------------------------------------------------------------
// Looks in the resource map to see if an entry with the specified type and the
// specified ID already exists. 

Boolean
CRezMap::HasResourceWithTypeAndId(ResType inType, short inID)
{
	Handle theHandle = nil;
	return ( GetWithID(inType, inID, theHandle) != resNotFound );
}


// ---------------------------------------------------------------------------
//  ¥ HasResourceWithTypeAndName										[public]
// ---------------------------------------------------------------------------
// Looks in the resource map to see if an entry with the specified type and the
// specified name already exists. 

Boolean
CRezMap::HasResourceWithTypeAndName(ResType inType, ConstStr255Param inName)
{
	Handle theHandle = nil;
	return ( GetWithName(inType, inName, theHandle) != resNotFound );
}


// ---------------------------------------------------------------------------
//  ¥ GetAllTypes													[public]
// ---------------------------------------------------------------------------
// Get an array of all types current resource map.

OSErr
CRezMap::GetAllTypes( TArray<ResType>* & outArray )
{
    short numTypes;
    ResType theType;
    
    StRezReferenceSaver saver(mRefnum);
    OSErr error = CountAllTypes(numTypes);
    
    if (error == noErr) {
	for ( UInt16 i = 1; i <= numTypes; i++ )
	{
	    ::Get1IndType( &theType, i );
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
//  ¥ GetTypeAtIndex													[public]
// ---------------------------------------------------------------------------
// Get the type given an index.

OSErr
CRezMap::GetTypeAtIndex(short inIdx, ResType & outType)
{
    StRezReferenceSaver saver(mRefnum);
   ::Get1IndType( &outType, inIdx );
    return ::ResError();
}


// ---------------------------------------------------------------------------
//  ¥ UniqueID														[public]
// ---------------------------------------------------------------------------
// typedef		SInt16			ResIDT;
// typedef unsigned short                  UInt16;
// typedef signed short                    SInt16;

OSErr
CRezMap::UniqueID(ResType inType, short & outID)
{
    StRezReferenceSaver saver(mRefnum);
    outID = ::Unique1ID(inType);
    return ::ResError();
}


// ---------------------------------------------------------------------------
//  ¥ GetFileAttrs														[public]
// ---------------------------------------------------------------------------
// 		  mapReadOnlyBit	= 7
// 		  mapCompactBit		= 6
// 		  mapChangedBit		= 5

OSErr
CRezMap::GetFileAttrs(short & outResFileAttrs)
{
    StRezReferenceSaver saver(mRefnum);
    outResFileAttrs = ::GetResFileAttrs(mRefnum);
    return ::ResError();
}


// ---------------------------------------------------------------------------
//  ¥ SetFileAttrs														[public]
// ---------------------------------------------------------------------------

OSErr
CRezMap::SetFileAttrs(short inResFileAttrs)
{
    StRezReferenceSaver saver(mRefnum);
    ::SetResFileAttrs(mRefnum, inResFileAttrs);
    return ::ResError();
}


// ---------------------------------------------------------------------------
//  ¥ UnsetFileAttrs														[public]
// ---------------------------------------------------------------------------

OSErr
CRezMap::UnsetFileAttrs(short inResFileAttrs)
{
    StRezReferenceSaver saver(mRefnum);
    short theAttrs = ::GetResFileAttrs(mRefnum);
    theAttrs  &= ~inResFileAttrs;
    ::SetResFileAttrs(mRefnum, theAttrs);
    return ::ResError();
}



