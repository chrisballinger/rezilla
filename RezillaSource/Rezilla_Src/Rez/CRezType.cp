// ===========================================================================
// CRezType.cp					
// 
//                       Created: 2003-04-23 12:32:10
//             Last modification: 2004-03-02 07:33:34
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003-2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CRezType.h"
#include "UResources.h"
#include "CRezMap.h"


// ---------------------------------------------------------------------------
//  ¥ CRezType														[public]
// ---------------------------------------------------------------------------

CRezType::CRezType(ResType inResType)
{
    mType = inResType;
    mOwnerMap = nil;
}


// ---------------------------------------------------------------------------
//  ¥ CRezType														[public]
// ---------------------------------------------------------------------------

CRezType::CRezType(ResType inResType, CRezMap * inOwnerMap)
: mType(inResType), mOwnerMap(inOwnerMap)
{
    // 	SignalStringLiteral_("OwnerMap not specified");
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
    StRezReferenceSaver saver(GetOwnerMap()->GetRefnum());
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
    StRezReferenceSaver saver(GetOwnerMap()->GetRefnum());
    outHandle = ::Get1Resource(mType, inID);
    return ::ResError();
}


// ---------------------------------------------------------------------------
//  ¥ GetWithName														[public]
// ---------------------------------------------------------------------------
// Get a handle to a resource of a given type with a given name
// from current resource map.

OSErr
CRezType::GetWithName(ConstStr255Param inName, Handle & outHandle)
{
    StRezReferenceSaver saver(GetOwnerMap()->GetRefnum());
    outHandle = ::Get1NamedResource(mType, inName);
    return ::ResError();
}


// ---------------------------------------------------------------------------
//  ¥ GetAllResources													[public]
// ---------------------------------------------------------------------------

OSErr
CRezType::GetAllResources( TArray<Handle>* & outArray )
{
    short numResources;
    Handle theHandle;
    
    StRezReferenceSaver saver(GetOwnerMap()->GetRefnum());
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
    
    StRezReferenceSaver saver(GetOwnerMap()->GetRefnum());
    OSErr error = CountResources(numResources);
   
    if (error == noErr) {
	for ( UInt16 i = 1; i <= numResources; i++ )
	{
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
CRezType::GetResourceAtIndex(short inIdx, Handle & outHandle)
{
    StRezReferenceSaver saver(GetOwnerMap()->GetRefnum());
    outHandle = ::Get1IndResource( mType, inIdx );
	return ::ResError();
}




