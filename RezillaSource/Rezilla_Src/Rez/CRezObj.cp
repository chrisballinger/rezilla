// ===========================================================================
// CRezObj.cp					
// 
//                       Created: 2003-04-23 12:32:10
//             Last modification: 2003-05-24 11:21:12
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CRezObj.h"
#include "CRezType.h"
#include "CRezMap.h"
#include "UResources.h"


// ---------------------------------------------------------------------------
//  ¬€ CRezObj														[public]
// ---------------------------------------------------------------------------

CRezObj::CRezObj(Handle inResHandle, short inRefnum)
{
	OSErr error;
	
	mOwnerRefnum = inRefnum;
	mData = inResHandle;
	error = GetInfoFromMap();
	ThrowIfOSErr_(error);
	
	mOwnerRezType = new CRezType(mType, nil);
	GetSizeOnDisk(mSize);
	GetAttributesFromMap(mAttributes);
}


// ---------------------------------------------------------------------------
//  ¬€ CRezObj														[public]
// ---------------------------------------------------------------------------
// Call this constructor if type, ID and name are known. It also concerns
// resources which do not already exist in the resource map: in that case, 
// an empty handle is associated. 

CRezObj::CRezObj(CRezType * inRezType,
				short inID, 
				Str255* inName)
{
	mOwnerRezType = inRezType;
	mType = mOwnerRezType->GetType();
	mOwnerRefnum = mOwnerRezType->GetOwnerMap()->GetRefnum();
	mID = inID;
	SetName(inName);
	// Get the handle of the resource
	OSErr error = GetRezHandle();
	// If the resource does not already exist
	if (error != noErr || mData == nil) {
		mData = ::NewHandle(0);
	}
	mSize = 0;
	mAttributes = 0;
}


// ---------------------------------------------------------------------------
//  ¬€ CRezObj														[public]
// ---------------------------------------------------------------------------

CRezObj::CRezObj(CRezType * inRezType)
{
	Str255 theName = "\p";
	
	mOwnerRezType = inRezType;
	mType = mOwnerRezType->GetType();
	mOwnerRefnum = mOwnerRezType->GetOwnerMap()->GetRefnum();
	// Generate an unique ID
	mOwnerRezType->GetOwnerMap()->UniqueID(mType, mID);
	SetName(&theName);
	mData = ::NewHandle(0);
	mSize = 0;
	mAttributes = 0;
}


// ---------------------------------------------------------------------------
//  ¬€ ~CRezObj														[public]
// ---------------------------------------------------------------------------
// The RemoveResource function does not dispose of the handle  you  pass  into
// it
// RemoveResource
CRezObj::~CRezObj()
{
// 	if (mOwnerRezType != nil) {
// 		delete mOwnerRezType;
// 	} 
}


// ---------------------------------------------------------------------------
//  ¬€ Add															[public]
// ---------------------------------------------------------------------------
// Adds a resource to the current resource fileˆïs resource map in memory. 

OSErr
CRezObj::Add()
{
    StRezReferenceSaver saver(mOwnerRefnum);
	::AddResource(mData, mType, mID, mName);
	return ::ResError();
}


// ---------------------------------------------------------------------------
//  ¬€ Remove														[public]
// ---------------------------------------------------------------------------
// Removes a resourceˆïs entry from the  current  resource  fileˆïs  resource
// map in memory. If the resProtected attribute for the resource is set  or
// if this parameter doesnˆït contain a handle to a resource,  the  function
// does  nothing,  and  the  ResError  function  returns  the  result  code
// rmvResFailed. 

OSErr
CRezObj::Remove()
{
    StRezReferenceSaver saver(mOwnerRefnum);
	if (mData != nil) {
		::RemoveResource(mData);
	} 
	return ::ResError();
}


// ---------------------------------------------------------------------------
//  ¬€ Changed														[public]
// ---------------------------------------------------------------------------
// Sets a flag in the resourceˆïs resource map entry in  memory  to  show  that
// youˆïve made changes to a resourceˆïs data or  to  an  entry  in  a  resource
// map. 

OSErr
CRezObj::Changed()
{
    StRezReferenceSaver saver(mOwnerRefnum);
	if (mData != nil) {
		::ChangedResource(mData);
	} 
	return ::ResError();
}


// ---------------------------------------------------------------------------
//  ¬€ Detach														[public]
// ---------------------------------------------------------------------------
// Sets the value of a resourceˆïs handle in the resource map in memory 
// to NULL while keeping the resource data in memory. 

OSErr
CRezObj::Detach()
{
    StRezReferenceSaver saver(mOwnerRefnum);
	if (mData != nil) {
		::DetachResource(mData);
	} 
	return ::ResError();
}


// ---------------------------------------------------------------------------
//  ¬€ Release														[public]
// ---------------------------------------------------------------------------
// Releases the memory a resource occupies when you have finished using it. 

OSErr
CRezObj::Release()
{
    StRezReferenceSaver saver(mOwnerRefnum);
	if (mData != nil) {
		::ReleaseResource(mData);
	} 
	return ::ResError();
}


// ---------------------------------------------------------------------------
//  ¬€ Load															[public]
// ---------------------------------------------------------------------------
// The function reads the resource data into memory. If the resource is
// already in memory, or if mData doesnˆït contain a handle to a resource,
// then the function does nothing. If the resource is  already in memory,
// it returns noErr; if mData is not a handle to a resource, it returns
// resNotFound.

OSErr
CRezObj::Load()
{
    StRezReferenceSaver saver(mOwnerRefnum);
	if (mData != nil) {
		::MacLoadResource(mData);
	} 
	return ::ResError();
}


// ---------------------------------------------------------------------------
//  ¬€ Write															[public]
// ---------------------------------------------------------------------------
// Writes resource data  in  memory  immediately  to  a  fileˆïs  resource
// fork. If the resource is purgeable and has been purged,  the  function
// writes  zero-length  resource  data  to  the  resource  fork.  If  the
// resourceˆïs resProtected attribute is  set  to  1,  the  function  does
// nothing and returns the result code noErr. The same  is  true  if  the
// resChanged attribute is not set (that is, set to 0).
// Note that this  function  does  not  write  the  *resource map* entry 
// to disk.

OSErr
CRezObj::Write()
{
    StRezReferenceSaver saver(mOwnerRefnum);
	if (mData != nil) {
		::WriteResource(mData);
	} 
	return ::ResError();
}


// ---------------------------------------------------------------------------
//  ¬€ GetRezHandle														[public]
// ---------------------------------------------------------------------------

OSErr
CRezObj::GetRezHandle()
{
    StRezReferenceSaver saver(mOwnerRefnum);
	mData = ::Get1Resource(mType, mID);
	return ::ResError();
}


// ---------------------------------------------------------------------------
//  ¬€ GetInfoFromMap												[public]
// ---------------------------------------------------------------------------
// Gets a resourceˆïs resource ID, resource type, and resource name from the 
// resource map.

OSErr
CRezObj::GetInfoFromMap()
{
    StRezReferenceSaver saver(mOwnerRefnum);
	if (mData != nil) {
		::GetResInfo(mData, &mID, &mType, (unsigned char *) mName);
	} 
	return ::ResError();
}


// ---------------------------------------------------------------------------
//  ¬€ SetInfoInMap													[public]
// ---------------------------------------------------------------------------
// Sets the name and resource ID of a resource in the resource map. 

OSErr
CRezObj::SetInfoInMap()
{
    StRezReferenceSaver saver(mOwnerRefnum);
	if (mData != nil) {
		::SetResInfo(mData, mID, mName);
	} 
	return ::ResError();
}


// ---------------------------------------------------------------------------
//  ¬€ SetName														[public]
// ---------------------------------------------------------------------------

void
CRezObj::SetName(Str255* inName)
{
	if (inName != nil) {
		::BlockMoveData(inName, &mName, (*inName[0]) + 1);
	} else {
		Str255 theName = "\p";
		::BlockMoveData(theName, &mName, 1);
	}
}


// ---------------------------------------------------------------------------
//  ¬€ GetAttributesFromMap											[public]
// ---------------------------------------------------------------------------
// Gets a resourceˆïs attributes. 

OSErr
CRezObj::GetAttributesFromMap(short & outAttribute)
{
    StRezReferenceSaver saver(mOwnerRefnum);
	if (mData != nil) {
		outAttribute = ::GetResAttrs(mData);
	} 
	return ::ResError();
}


// ---------------------------------------------------------------------------
//  ¬€ SetAttributes													[public]
// ---------------------------------------------------------------------------

OSErr
CRezObj::SetAttributes(short inAttributes)
{
	OSErr error = noErr;
    StRezReferenceSaver saver(mOwnerRefnum);
	if (mData != nil) {
		::SetResAttrs(mData, inAttributes);
		error = ::ResError();
		if (error == noErr) {
			// Keep object in sync
			mAttributes = inAttributes;
		} 
	} 
	return error;
}


// ---------------------------------------------------------------------------
//  ¬€ GetMaxSize													[public]
// ---------------------------------------------------------------------------

OSErr
CRezObj::GetMaxSize(Size & outSize)
{
    StRezReferenceSaver saver(mOwnerRefnum);
	if (mData != nil) {
		outSize = ::GetMaxResourceSize(mData);
	} 
	return ::ResError();
}


// ---------------------------------------------------------------------------
//  ¬€ GetSize														[public]
// ---------------------------------------------------------------------------

OSErr
CRezObj::GetSizeOnDisk(Size & outSize)
{
    StRezReferenceSaver saver(mOwnerRefnum);
	if (mData != nil) {
		outSize = ::GetResourceSizeOnDisk(mData);
	} 
	return ::ResError();
}


// ---------------------------------------------------------------------------
//  ¬€ SetSizeOnDisk														[public]
// ---------------------------------------------------------------------------
// Sets the size of a resource on disk.
// This function is  normally  used  only  with  the  ReadPartialResource  and
// WritePartialResource functions.
// 
// This function sets the size field of the specified resource on disk without
// writing the resource data.  You  can  change  the  size  of  any  resource,
// regardless of the amount of memory you have available.

OSErr
CRezObj::SetSizeOnDisk(Size inSize)
{
	OSErr error = noErr;
	if (mData != nil) {
		::SetResourceSize(mData, inSize);
		error = ::ResError();
		if (error == noErr) {
			// Keep object in sync
			mSize = inSize;
		} 
	} 
	return error;
}


// ---------------------------------------------------------------------------
//  ¬€ SetData														[public]
// ---------------------------------------------------------------------------
void
CRezObj::SetData(Handle srcHandle)
{
	// Copy to resource data handle
	Size theSize = ::GetHandleSize( srcHandle );
	StHandleLocker	lockSrc(srcHandle);
	StHandleLocker	lockTrgt(mData);
	::SetHandleSize(mData, theSize );
	::BlockMoveData( *srcHandle, *mData, theSize);
}


// // ---------------------------------------------------------------------------
// //  ¬€ ReadPartial												[public]
// // ---------------------------------------------------------------------------
// 
// CRezObj::ReadPartial()
// {
// }
// 
// 
// // ---------------------------------------------------------------------------
// //  ¬€ WritePartial												[public]
// // ---------------------------------------------------------------------------
// 
// CRezObj::WritePartial()
// {
// }



