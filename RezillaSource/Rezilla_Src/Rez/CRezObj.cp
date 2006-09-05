// ===========================================================================
// CRezObj.cp					
// 
//                       Created: 2003-04-23 12:32:10
//             Last modification: 2006-07-14 12:08:47
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2003-2005, 2006
// All rights reserved.
// ===========================================================================

#include "CRezObj.h"
#include "CRezType.h"
#include "CRezMap.h"
#include "UResources.h"
#include "RezillaConstants.h"

// #include <LString.h>


// ---------------------------------------------------------------------------
//   CRezObj														[public]
// ---------------------------------------------------------------------------

CRezObj::CRezObj(Handle inResHandle, short inRefnum)
	: LModelObject(NULL, rzom_cRezObj)
{
	OSErr error;
	
	mOwnerRefnum = inRefnum;
	mData = inResHandle;
	error = GetInfoFromMap();
	ThrowIfOSErr_(error);
	
	GetSizeOnDisk(mSize);
	GetAttributesFromMap(mAttributes);
	mRefCount = 0;

	// Don't use PP's list model
}


// ---------------------------------------------------------------------------
//   CRezObj														[public]
// ---------------------------------------------------------------------------
// Call this constructor for an already existing resource whose type and ID 
// are known.

CRezObj::CRezObj(CRezType * inRezType, short inID)
	: LModelObject(inRezType, rzom_cRezObj),
		mID(inID)
{
	Str255	theName;
	mType = inRezType->GetType();
	mOwnerRefnum = inRezType->GetOwnerMap()->GetRefnum();
	
	// Get the handle of the resource. There should be no error.
	OSErr error = GetRezHandle();
	ThrowIfError_(error);
	
	// Get the size of the resource
	mSize = ::GetHandleSize(mData);

	// Get the name of the resource
	::GetResInfo(mData, &mID, &mType, (unsigned char *) theName);
	SetName(&theName);
	// Get the attributes of the resource
	mAttributes = ::GetResAttrs(mData);
	mRefCount = 0;

	// Don't use PP's list model
}


// ---------------------------------------------------------------------------
//   CRezObj														[public]
// ---------------------------------------------------------------------------
// Call this constructor if type, ID and name are known (name can be
// empty). It also concerns resources which do not already exist in the
// resource map: in that case, an empty handle is associated.

CRezObj::CRezObj(CRezType * inRezType,
				short inID, 
				Str255* inName)
	: LModelObject(inRezType, rzom_cRezObj)
{
	mType = inRezType->GetType();
	mOwnerRefnum = inRezType->GetOwnerMap()->GetRefnum();
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
	mRefCount = 0;

	// Don't use PP's list model
}


// ---------------------------------------------------------------------------
//   CRezObj														[public]
// ---------------------------------------------------------------------------
// Call this constructor when a temporary object is needed to represent a
// resource whose type, ID and name are specified (name can be empty). The
// LModelObject is NULL.

CRezObj::CRezObj(short inRefnum,
				 ResType inType,
				 short inID, 
				 Str255* inName)
	: LModelObject(NULL, rzom_cRezObj)
{
	mType = inType;
	mOwnerRefnum = inRefnum;
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
	mRefCount = 0;
}


// ---------------------------------------------------------------------------
//   CRezObj														[public]
// ---------------------------------------------------------------------------

CRezObj::CRezObj(CRezType * inRezType)
	: LModelObject(inRezType, rzom_cRezObj)
{
	Str255 theName = "\p";
	
	mType = inRezType->GetType();
	mOwnerRefnum = inRezType->GetOwnerMap()->GetRefnum();
	// Generate an unique ID
	inRezType->GetOwnerMap()->UniqueID(mType, mID);
	SetName(&theName);
	mData = ::NewHandle(0);
	mSize = 0;
	mAttributes = 0;
	mRefCount = 0;

	// Don't use PP's list model
}


// ---------------------------------------------------------------------------
//   CRezObj							Copy Constructor			[public]
// ---------------------------------------------------------------------------

CRezObj::CRezObj(CRezObj& inOriginal)
	: LModelObject(inOriginal.GetSuperModel(), rzom_cRezObj)
{
	mOwnerRefnum = inOriginal.GetOwnerRefnum();
	mType = inOriginal.GetType();
	mID = inOriginal.GetID();
	mSize = inOriginal.GetSize();
	mAttributes = inOriginal.GetAttributes();	
	mRefCount = 0;

	this->SetName(inOriginal.GetName());
	mData = ::NewHandle(0);
	this->SetData(inOriginal.GetData());

	SetModelKind(rzom_cRezObj);
	// Don't use PP's list model
}


// ---------------------------------------------------------------------------
//     ~CRezObj														[public]
// ---------------------------------------------------------------------------

CRezObj::~CRezObj()
{
}


// ---------------------------------------------------------------------------
//   Add															[public]
// ---------------------------------------------------------------------------
// Adds a resource to the current resource file's resource map in memory. 

OSErr
CRezObj::Add()
{
    StRezRefSaver saver(mOwnerRefnum);
	::AddResource(mData, mType, mID, mName);
	return ::ResError();
}


// ---------------------------------------------------------------------------
//   Remove														[public]
// ---------------------------------------------------------------------------
// Removes a resource's entry from the  current  resource  file's  resource
// map in memory. If the resProtected attribute for the resource is set  or
// if this parameter doesn't contain a handle to a resource,  the  function
// does  nothing,  and  the  ResError  function  returns  the  result  code
// rmvResFailed. 
// 
// "The RemoveResource function does not dispose of the handle you  pass  into
// it; to do so you must call the Memory Manager function DisposeHandle  after
// calling RemoveResource. You should  dispose  the  handle  if  you  want  to
// release the memory before updating or closing the resource fork."

OSErr
CRezObj::Remove()
{
	OSErr error = noErr;
    StRezRefSaver saver(mOwnerRefnum);
	if (mData != nil) { 
		::RemoveResource(mData);
		::DisposeHandle(mData);
		mData = nil;
		error = ::ResError();
	} 
	return error;
}


// ---------------------------------------------------------------------------
//   Changed														[public]
// ---------------------------------------------------------------------------
// Sets a flag in the resource's resource map entry in  memory  to  show  that
// you've made changes to a resource's data or  to  an  entry  in  a  resource
// map. 

OSErr
CRezObj::Changed()
{
	OSErr error = noErr;
    StRezRefSaver saver(mOwnerRefnum);
	if (mData != nil) {
		::ChangedResource(mData);
		error = ::ResError();
	} 
	return error;
}


// ---------------------------------------------------------------------------
//   Detach														[public]
// ---------------------------------------------------------------------------
// Sets the value of a resource's handle in the resource map in memory 
// to NULL while keeping the resource data in memory. 

OSErr
CRezObj::Detach()
{
	OSErr error = noErr;
    StRezRefSaver saver(mOwnerRefnum);
	if (mData != nil) {
		::DetachResource(mData);
		error = ::ResError();
	} 
	return error;
}


// ---------------------------------------------------------------------------
//   Release														[public]
// ---------------------------------------------------------------------------
// Releases the memory a resource occupies when you have finished using it. 

OSErr
CRezObj::Release()
{
	OSErr error = noErr;
    StRezRefSaver saver(mOwnerRefnum);
	if (mData != nil) {
		::ReleaseResource(mData);
		error = ::ResError();
	} 
	return error;
}


// ---------------------------------------------------------------------------
//   Load															[public]
// ---------------------------------------------------------------------------
// The function reads the resource data into memory. If the resource is
// already in memory, or if mData doesn't contain a handle to a resource,
// then the function does nothing. If the resource is  already in memory,
// it returns noErr; if mData is not a handle to a resource, it returns
// resNotFound.

OSErr
CRezObj::Load()
{
	OSErr error = noErr;
    StRezRefSaver saver(mOwnerRefnum);
	if (mData != nil) {
		::MacLoadResource(mData);
		error = ::ResError();
	} 
	return error;
}


// ---------------------------------------------------------------------------
//   Write															[public]
// ---------------------------------------------------------------------------
// Writes resource data  in  memory  immediately  to  a  file's  resource
// fork. If the resource is purgeable and has been purged,  the  function
// writes  zero-length  resource  data  to  the  resource  fork.  If  the
// resource's resProtected attribute is  set  to  1,  the  function  does
// nothing and returns the result code noErr. The same  is  true  if  the
// resChanged attribute is not set (that is, set to 0).
// Note that this  function  does  not  write  the  *resource map* entry 
// to disk.

OSErr
CRezObj::Write()
{
	OSErr error = noErr;
    StRezRefSaver saver(mOwnerRefnum);
	if (mData != nil) {
		::WriteResource(mData);
		error = ::ResError();
	} 
	return error;
}


// ---------------------------------------------------------------------------
//   GetRezHandle														[public]
// ---------------------------------------------------------------------------
// This loads the resource data in memory since we DON'T call
// SetResLoad(false). 

OSErr
CRezObj::GetRezHandle()
{
    StRezRefSaver saver(mOwnerRefnum);
	mData = ::Get1Resource(mType, mID);
	return ::ResError();
}


// ---------------------------------------------------------------------------
//   GetInfoFromMap												[public]
// ---------------------------------------------------------------------------
// Gets a resource's resource ID, resource type, and resource name from the 
// resource map.

OSErr
CRezObj::GetInfoFromMap()
{
	OSErr error = noErr;
    StRezRefSaver saver(mOwnerRefnum);
	if (mData != nil) {
		::GetResInfo(mData, &mID, &mType, (unsigned char *) mName);
		error = ::ResError();
	} 
	return error;
}


// ---------------------------------------------------------------------------
//   SetInfoInMap													[public]
// ---------------------------------------------------------------------------
// Sets the name and resource ID of a resource in the resource map. 

OSErr
CRezObj::SetInfoInMap()
{
	OSErr error = noErr;
    StRezRefSaver saver(mOwnerRefnum);
	if (mData != nil) {
		::SetResInfo(mData, mID, mName);
		error = ::ResError();
	} 
	return error;
}


// ---------------------------------------------------------------------------
//   SetName														[public]
// ---------------------------------------------------------------------------

void
CRezObj::SetName(Str255* inName)
{
	if (inName != nil) {
		::BlockMoveData(inName, &mName, (*inName)[0] + 1);
	} else {
		Str255 theName = "\p";
		::BlockMoveData(theName, &mName, 1);
	}
}


// ---------------------------------------------------------------------------
//   GetAttributesFromMap											[public]
// ---------------------------------------------------------------------------
// Gets a resource's attributes. 

OSErr
CRezObj::GetAttributesFromMap(short & outAttribute)
{
	OSErr error = noErr;
    StRezRefSaver saver(mOwnerRefnum);
	if (mData != nil) {
		outAttribute = ::GetResAttrs(mData);
		error = ::ResError();
	} 
	return error;
}


// ---------------------------------------------------------------------------
//   SetAttributesInMap													[public]
// ---------------------------------------------------------------------------

OSErr
CRezObj::SetAttributesInMap(short inAttributes)
{
	OSErr error = noErr;
	
	if (mAttributes != inAttributes) {
		StRezRefSaver saver(mOwnerRefnum);
		if (mData != nil) {
			::SetResAttrs(mData, inAttributes);
			error = ::ResError();
			if (error == noErr) {
				// Keep object in sync
				mAttributes = inAttributes;
			} 
		} 
	} 
	
	return error;
}


// ---------------------------------------------------------------------------
//   ToggleOneAttribute											[inline]
// ---------------------------------------------------------------------------
//	Allows the toggling of an attribute setting. If you wish to change all
//	attributes in one call, use SetAttributesInMap instead.

OSErr
CRezObj::ToggleOneAttribute(short inFlag)
{
	OSErr error = noErr;
	short theAttrs = mAttributes;
	Boolean theSetting = ((theAttrs & inFlag) != 0);
	
	if (theSetting) {
		theAttrs &= ~inFlag;
	} else {
		theAttrs |= inFlag;
	}
	error = SetAttributesInMap(theAttrs);
	
	return error;
}


// ---------------------------------------------------------------------------
//   SetOneAttribute												[inline]
// ---------------------------------------------------------------------------
//	Allows to set a single attribute. If you wish to change all
//	attributes in one call, use SetAttributesInMap instead.

OSErr
CRezObj::SetOneAttribute(short inFlag, Boolean inSetting)
{
	OSErr error = noErr;
	short theAttrs = mAttributes;
	
	if (inSetting) {
		theAttrs |= inFlag;
	} else {
		theAttrs &= ~inFlag;
	}
	error = SetAttributesInMap(theAttrs);
	
	return error;
}


// ---------------------------------------------------------------------------
//   GetMaxSize													[public]
// ---------------------------------------------------------------------------

OSErr
CRezObj::GetMaxSize(Size & outSize)
{
	OSErr error = noErr;
    StRezRefSaver saver(mOwnerRefnum);
	if (mData != nil) {
		outSize = ::GetMaxResourceSize(mData);
		error = ::ResError();
	} 
	return error;
}


// ---------------------------------------------------------------------------
//   GetSizeOnDisk													[public]
// ---------------------------------------------------------------------------

OSErr
CRezObj::GetSizeOnDisk(Size & outSize) const
{
	OSErr error = noErr;
    StRezRefSaver saver(mOwnerRefnum);
	if (mData != nil) {
		outSize = ::GetResourceSizeOnDisk(mData);
		error = ::ResError();
	} 
	return error;
}


// ---------------------------------------------------------------------------
//   SetSizeOnDisk														[public]
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
//   GetIndexInType													[public]
// ---------------------------------------------------------------------------

OSErr
CRezObj::GetIndexInType(SInt32 & outIndex) const
{
	OSErr	error = noErr;
	Handle	theHandle;
	ResType	theType;
	short	i, count, theID;
	Str255	theName;
	
	StRezRefSaver saver(mOwnerRefnum);
	count = ::Count1Resources(mType);

	for (i = 1;i <= count;i++) {
		theHandle = ::Get1IndResource( mType, theID );
		error = ::ResError();
		if (error == noErr) {
			::GetResInfo(theHandle, &theID, &theType, theName);
			error = ::ResError();
			if (error == noErr && theID == mID) {
				outIndex = i;
				break;
			} 
		} 
	}

	return error;
}


// // ---------------------------------------------------------------------------
// //   GetIndexInMap													[public]
// // ---------------------------------------------------------------------------
// 
// OSErr
// CRezObj::GetIndexInMap(SInt32 & outIndex) const
// {
// 	OSErr error = noErr;
// 	StRezRefSaver saver(mOwnerRefnum);
// 	if (mData != nil) {
// 		outSize = ::GetResourceSizeOnDisk(mData);
// 		error = ::ResError();
// 	} 
// 	return error;
// }


// ---------------------------------------------------------------------------
//   SetData														[public]
// ---------------------------------------------------------------------------
// Double strategy to set data: first try to resize the existing handle and
// then copy the new data into it. Sometimes this fails with error
// memFullErr (-108). In that case, try removing the resource from the
// resource map and add a new one instead. In some circumstances, removing
// fails with error rmvResFailed (-196), dunno why.

void
CRezObj::SetData(Handle srcHandle)
{
	OSErr	error = noErr;
	Boolean	addIt = false;
	Size	theSize;
	short	oldAttrs;
	
	// Copy to resource data handle
	theSize = ::GetHandleSize( srcHandle );
	::SetHandleSize(mData, theSize);
	error = ::MemError();
	if (error != noErr) {
		oldAttrs = mAttributes;
		// Clear the attributes (RemoveResource does not work if
		// resProtected is on)
		SetAttributesInMap(0);
		error = Remove();
		if (error == noErr || error == resNotFound) {
			error = noErr;
			mData = ::NewHandleClear( theSize );
			ThrowIfMemFail_( mData );
			addIt = true;
		} else {
			SetAttributesInMap(oldAttrs);
		}
		ThrowIfOSErr_( error );
	} 
	if (error == noErr) {
		StHandleLocker	lockSrc(srcHandle);
		StHandleLocker	lockTrgt(mData);
		::BlockMoveData( *srcHandle, *mData, theSize);
	} 
	if (addIt) {
		error = Add();
		ThrowIfOSErr_(error);
		SetAttributesInMap(oldAttrs);
	} 	
	// Update the mSize class member
	mSize = ::GetHandleSize(mData);
	// Tell the map the resource changed
	this->Changed();
}


// // ---------------------------------------------------------------------------
// //   ReadPartial												[public]
// // ---------------------------------------------------------------------------
// 
// CRezObj::ReadPartial(long offset, const void * buffer, long count)
// {
// }
// 
// 
// // ---------------------------------------------------------------------------
// //   WritePartial												[public]
// // ---------------------------------------------------------------------------
// 
// CRezObj::WritePartial(long offset, const void * buffer, long count)
// {
// }


