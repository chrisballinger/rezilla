// ===========================================================================
// CResourceCache.cp
//                       Created: 2004-12-11 18:56:46
//             Last modification: 2004-12-15 10:49:52
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CResourceCache.h"
#include "UIconMisc.h"
#include "UResources.h"


// ---------------------------------------------------------------------------
// 	CResourceCache::Constructor
// ---------------------------------------------------------------------------

CResourceCache::CResourceCache( SInt32 numElements, OSType inResType, SInt32 resFileID )
{
	mResType = inResType;
	mResFileID = resFileID;
	mNumElements = numElements;
	mCacheArray = (CacheEntry*) ::NewPtrClear( sizeof( CacheEntry ) * numElements );
	ThrowIfMemFail_( mCacheArray );
}


// ---------------------------------------------------------------------------
// 	CResourceCache::Destructor
// ---------------------------------------------------------------------------

CResourceCache::~CResourceCache()
{
	for ( SInt32 count = 0; count < mNumElements; count++ )
	{
		if ( mCacheArray[count].theResource )
			this->DisposeElement( count );
	}
}
 

// ---------------------------------------------------------------------------
// 	CResourceCache::GetResource
// ---------------------------------------------------------------------------

Handle
CResourceCache::GetResource( ResIDT inResID )
{
			// see if it's already in the cache

	SInt32	index = this->FindElementByID( inResID );
	if ( index != -1 )
		return( mCacheArray[index].theResource );
	
			// not in cache, so read it into memory

	Handle	h = this->LoadRawResource( inResID );
		
			// find an opening in the cache and save the icon there
		// 
		// Note: if the cache is full, we'll just forget about saving it

	for ( SInt32 count = 0; count < mNumElements; count++ )
		if ( mCacheArray[ count ].theResource == nil )
		{
			mCacheArray[ count ].theResource = h;
			mCacheArray[ count ].theResID = inResID;
			break;
		}
		
	return( h );
}


// ---------------------------------------------------------------------------
// 	CResourceCache::ReleaseResource
// ---------------------------------------------------------------------------

void
CResourceCache::ReleaseResource( Handle& h )
{
	if ( !h ) return;

	SInt32	index = this->FindElementByHandle( h );
	if ( index != -1 )
		this->DisposeElement( index );
	else
		this->DisposeRawResource( h );		// still delete it even if not cached

	h = nil;
}


// ---------------------------------------------------------------------------
// 	CResourceCache::FindElementByID
// ---------------------------------------------------------------------------

SInt32
CResourceCache::FindElementByID( ResIDT theID )
{
	for ( SInt32 count = 0; count < mNumElements; count++ )
	{
		if ( mCacheArray[count].theResID == theID )
			return( count );
	}
	
	return( -1 );
}


// ---------------------------------------------------------------------------
// 	CResourceCache::FindElementByHandle
// ---------------------------------------------------------------------------

SInt32
CResourceCache::FindElementByHandle( Handle h )
{
	for ( SInt32 count = 0; count < mNumElements; count++ )
	{
		if ( mCacheArray[count].theResource == h )
			return( count );
	}
	
	return( -1 );
}


// ---------------------------------------------------------------------------
// 	CResourceCache::DisposeElement
// ---------------------------------------------------------------------------

void
CResourceCache::DisposeElement( SInt32 index )
{
	if ( mCacheArray[index].theResource )
	{
		this->DisposeRawResource( mCacheArray[index].theResource );
		mCacheArray[index].theResID = 0;
	}
}



// ---------------------------------------------------------------------------
// 	CResourceCache::LoadRawResource
// ---------------------------------------------------------------------------

Handle
CResourceCache::LoadRawResource( ResIDT inResID )
{
	StRezRefSaver		aSaver;
	Handle				h = nil;
	
	if ( mResFileID == -1 )
	{
		h = ::GetResource( mResType, inResID );
	}
	else
	{
		UseResFile( mResFileID );
		h = ::Get1Resource( mResType, inResID );
	}
	
	ThrowIfResFail_( h );
	return( h );
}


// ---------------------------------------------------------------------------
// 	CResourceCache::DisposeRawResource
// ---------------------------------------------------------------------------

void
CResourceCache::DisposeRawResource( Handle &h )
{
	if ( h )
	{
		UIconMisc::DisposeHandle( h );	// does a smart releaseresource/disposehandle
		h = nil;
	}
}

