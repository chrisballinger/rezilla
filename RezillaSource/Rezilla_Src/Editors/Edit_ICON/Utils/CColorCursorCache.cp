// ===========================================================================
// CColorCursorCache.cp
//                       Created: 2004-12-11 18:56:37
//             Last modification: 2005-01-12 17:24:35
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CColorCursorCache.h"
#include "RezillaConstants.h"
#include "UIconMisc.h"
#include "UResources.h"

#include <UCursor.h>


CColorCursorCache *CColorCursorCache::sCurrentCache = nil;


// ---------------------------------------------------------------------------
//	CColorCursorCache
// ---------------------------------------------------------------------------

CColorCursorCache::CColorCursorCache( SInt32 numElements, SInt32 resFileID )
					: CResourceCache( numElements, ResType_ColorCursor, resFileID )
{
	sCurrentCache = this;
}


// ---------------------------------------------------------------------------
//	~CColorCursorCache
// ---------------------------------------------------------------------------

CColorCursorCache::~CColorCursorCache()
{
	// Don't dispose of the active cursor
// 	::SetCursor( &UQDGlobals::GetQDGlobals()->arrow );
	UCursor::SetArrow();
	
	// Important to release everything in this destructor rather than
	// waiting for the CResourceCache destructor because it will call its
	// own DisposeRawResource() method rather than ours.
	for ( SInt32 count = 0; count < mNumElements; count++ )
	{
		if ( mCacheArray[count].theResource )
		{
			this->DisposeElement( count );
			mCacheArray[count].theResource = nil;
		}
	}

	if ( sCurrentCache == this )
		sCurrentCache = nil;
}


// ---------------------------------------------------------------------------
//	GetColorCursor
// ---------------------------------------------------------------------------

CCrsrHandle
CColorCursorCache::GetColorCursor( ResIDT inResID )
{
	return( (CCrsrHandle) this->GetResource( inResID ) );
}


// ---------------------------------------------------------------------------
//	SetColorCursor
// ---------------------------------------------------------------------------

Boolean
CColorCursorCache::SetColorCursor( ResIDT inResID )
{
	CCrsrHandle		theCursor = nil;
	
	// Since this is called at idle time, it's best not to put up error
	// messages over and over and over, so catch the errors.
	try
	{
		theCursor = (CCrsrHandle) this->GetResource( inResID );
		ThrowIfNil_( theCursor );
	}
	catch( ... )
	{
		return( false );
	}
	
	::SetCCursor( theCursor );
	return( true );
}


// ---------------------------------------------------------------------------
//	DisposeColorCursor
// ---------------------------------------------------------------------------

void
CColorCursorCache::DisposeColorCursor( CCrsrHandle& inCursor )
{
	this->ReleaseResource( (Handle&) inCursor );
}


// ---------------------------------------------------------------------------
//	LoadRawResource
// ---------------------------------------------------------------------------

Handle
CColorCursorCache::LoadRawResource( ResIDT inResID )
{
	StRezRefSaver		aSaver;
	Handle				h = nil;
	
	if ( mResFileID == -1 )
	{
		h = (Handle) ::GetCCursor( inResID );	
	}
	else
	{
		// GetCCursor will use resource chain, so check file first
		if ( UResources::MapHasResource( mResFileID, ResType_ColorCursor, inResID ) )
		{
			::UseResFile( mResFileID );
			h = (Handle) ::GetCCursor( inResID );	
		}
	}
	
	ThrowIfResFail_( h );
	return( h );
}


// ---------------------------------------------------------------------------
//	DisposeRawResource
// ---------------------------------------------------------------------------

void
CColorCursorCache::DisposeRawResource( Handle &h )
{
	if ( !h ) return;
	
	::DisposeCCursor( (CCrsrHandle) h );
	h = nil;
}


// ---------------------------------------------------------------------------
//	GetCurrentCache
// ---------------------------------------------------------------------------

CColorCursorCache *
CColorCursorCache::GetCurrentCache()
{
	ThrowIfNil_( sCurrentCache );
	return( sCurrentCache );
}

