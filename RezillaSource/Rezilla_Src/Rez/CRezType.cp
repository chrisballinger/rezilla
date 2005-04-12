// ===========================================================================
// CRezType.cp					
// 
//                       Created: 2003-04-23 12:32:10
//             Last modification: 2005-04-12 07:02:44
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CRezType.h"
#include "UResources.h"
#include "CRezMap.h"
#include "RezillaConstants.h"


// ---------------------------------------------------------------------------
//  ¥ CRezType														[public]
// ---------------------------------------------------------------------------

CRezType::CRezType(ResType inResType)
	: LModelObject(NULL, rzom_cRezType)
{
    mType = inResType;
    mOwnerMap = nil;

	// Don't use PP's list model
	SetUseSubModelList(false);
}


// ---------------------------------------------------------------------------
//  ¥ CRezType														[public]
// ---------------------------------------------------------------------------

CRezType::CRezType(ResType inResType, CRezMap * inOwnerMap)
	: LModelObject(inOwnerMap, rzom_cRezType),
		mType(inResType), mOwnerMap(inOwnerMap)
{
    // 	SignalStringLiteral_("OwnerMap not specified");

	// Don't use PP's list model
	SetUseSubModelList(false);
}


// ---------------------------------------------------------------------------
//  ¥ ~CRezType														[public]
// ---------------------------------------------------------------------------

CRezType::~CRezType()
{
}


// ---------------------------------------------------------------------------
//  ¥ CountResources														[public]
// ---------------------------------------------------------------------------

OSErr
CRezType::CountResources(short & outCount)
{
    StRezRefSaver saver(GetOwnerMap()->GetRefnum());
    outCount = ::Count1Resources(mType);
    return ::ResError();
}


// ---------------------------------------------------------------------------
//  ¥ GetWithID													[public]
// ---------------------------------------------------------------------------
// Get a handle to a resource of a given type with a given ID
// from current resource map.

OSErr
CRezType::GetWithID(short inID, Handle & outHandle)
{
    StRezRefSaver saver(GetOwnerMap()->GetRefnum());
    outHandle = ::Get1Resource(mType, inID);
    return ::ResError();
}


// ---------------------------------------------------------------------------
//  ¥ GetWithName													[public]
// ---------------------------------------------------------------------------
// Get a handle to a resource of a given type with a given name
// from current resource map.

OSErr
CRezType::GetWithName(ConstStr255Param inName, Handle & outHandle)
{
	OSErr	error = noErr;
	short	theCount = 0;
	short	theID;
	ResType	theType;
	Str255	theName;
	Boolean found = false;

   StRezRefSaver saver(GetOwnerMap()->GetRefnum());
   theCount = ::Count1Resources(mType);
   error = ::ResError();
   if (error == noErr) {
	   for ( UInt16 i = 1; i <= theCount; i++ ) {
		   outHandle = ::Get1IndResource(mType, i);
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
   return error;
}


// ---------------------------------------------------------------------------
//  ¥ GetAllResources													[public]
// ---------------------------------------------------------------------------

OSErr
CRezType::GetAllResources( TArray<Handle>* & outArray )
{
    short numResources;
    Handle theHandle;
    
    StRezRefSaver saver(GetOwnerMap()->GetRefnum());
    OSErr error = CountResources(numResources);
   
    if (error == noErr) {
	for ( UInt16 i = 1; i <= numResources; i++ )
	{
	    theHandle = ::Get1IndResource( mType, i );
	    error = ::ResError();
	    if (error != noErr) {
		break;
	    } 
	    outArray->AddItem(theHandle);
	}
    } 
    return error;
}


// ---------------------------------------------------------------------------
//  ¥ GetAllRezIDs													[public]
// ---------------------------------------------------------------------------

OSErr
CRezType::GetAllRezIDs( TArray<short>* & outArray )
{
    short numResources;
    Handle theHandle;
	short theID;
	ResType theType;
	Str255	theName;
    
    StRezRefSaver saver(GetOwnerMap()->GetRefnum());
    OSErr error = CountResources(numResources);
   
    if (error == noErr) {
	for ( UInt16 i = 1; i <= numResources; i++ ) {
	    theHandle = ::Get1IndResource( mType, i );
	    error = ::ResError();
	    if (error != noErr) {
			break;
	    } 
		::GetResInfo(theHandle, &theID, &theType, (unsigned char *) theName);
	    error = ::ResError();
	    if (error != noErr) {
			break;
	    } 
	    outArray->AddItem(theID);
	}
    } 
    return error;
}


// ---------------------------------------------------------------------------
//  ¥ GetResourceAtIndex											[public]
// ---------------------------------------------------------------------------

OSErr
CRezType::GetResourceAtIndex(short inIdx, 
							 Handle & outHandle, 
							 Boolean loadIt)
{
    StRezRefSaver saver(GetOwnerMap()->GetRefnum());
	if (!loadIt) {
		::SetResLoad(false);
	} 
    outHandle = ::Get1IndResource( mType, inIdx );
	if (!loadIt) {
		::SetResLoad(true);
	} 
	return ::ResError();
}


// ---------------------------------------------------------------------------
//  ¥ GetNameAtIndex											[public]
// ---------------------------------------------------------------------------

OSErr
CRezType::GetNameAtIndex(short inIdx, Str255 & outName)
{
	Handle	theHandle;
	short	theID;
	ResType	theType;
	OSErr	error;
	
	StRezRefSaver saver(GetOwnerMap()->GetRefnum());
	theHandle = ::Get1IndResource( mType, inIdx );
	error = ::ResError();
	if (error == noErr) {
		::GetResInfo(theHandle, &theID, &theType, outName);
		error = ::ResError();
	} 
	if (error != noErr) {
		outName[0] = 0;
	} 
	
	return error;
}



