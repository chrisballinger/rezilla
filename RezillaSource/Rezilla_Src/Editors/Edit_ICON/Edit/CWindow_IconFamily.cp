// ===========================================================================
// CWindow_IconFamily.cp
//                       Created: 2004-12-11 18:50:16
//             Last modification: 2006-03-15 08:51:02
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004-2005, 2006
// All rights reserved.
// ===========================================================================

#include "CWindow_IconFamily.h"
#include "CDraggableTargetView.h"
#include "CIcon_EditorWindow.h"
#include "COffscreen.h"
#include "CRezMapTable.h"
#include "CEditorDoc.h"
#include "CRezMap.h"
#include "CRezObj.h"
#include "CRezObjItem.h"
#include "CRezillaApp.h"
#include "RezillaConstants.h"
#include "UColorUtils.h"
#include "UGraphicConversion.h"
#include "UIconMisc.h"
#include "UMiscUtils.h"
#include "UResourceMgr.h"


// ---------------------------------------------------------------------------
// 	OpenPaintWindow
// ---------------------------------------------------------------------------
CWindow_IconFamily*
CWindow_IconFamily::OpenPaintWindow( ResIDT inPPobID, CRezMap *inMap, ResIDT inResID )
{
	CWindow_IconFamily *	theWindow = nil;

	try
	{
		theWindow = (CWindow_IconFamily*) CIcon_EditorWindow::CreatePaintWindow( inPPobID );
		theWindow->InitializeFromResource( inMap, inResID );
	}
	catch( ... )
	{
		if (theWindow) { delete theWindow; } 
		throw;
	}
	
	return( theWindow );
}


// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------
CWindow_IconFamily::CWindow_IconFamily( LStream *inStream ) 
		: CIcon_EditorWindow( inStream )
{
	OSErr	error;
	Handle	theHandle;
	
	// The ID is the same as the ID of the PPob itself (this is important 
	// because the CWindow_IconFamily class also edits 'ICON' resources)
	error = UResources::GetResourceInMap( CRezillaApp::GetSelfRefNum(), ResType_IconFamilyInfo, this->GetPaneID(), theHandle, true );
	ThrowIfOSErr_(error);
	::DetachResource(theHandle);
	mFamilyInfoH = (Rez_IconFamilyInfoH) theHandle;
	EndianConvertIconFamilyInfoHandle();
}


// ---------------------------------------------------------------------------
// 	Destructor
// ---------------------------------------------------------------------------
CWindow_IconFamily::~CWindow_IconFamily()
{
	if (mFamilyInfoH != nil) {
		::DisposeHandle( (Handle) mFamilyInfoH);
 	} 
}


// ---------------------------------------------------------------------------
// 	CreateFromStream
// ---------------------------------------------------------------------------
CWindow_IconFamily *
CWindow_IconFamily::CreateFromStream( LStream *inStream )
{
	return new CWindow_IconFamily( inStream );
}


// ---------------------------------------------------------------------------
// 	FinishCreateSelf
// ---------------------------------------------------------------------------
void
CWindow_IconFamily::FinishCreateSelf()
{
	// Call the inherited method
	CIcon_EditorWindow::FinishCreateSelf();

	// Link the broadcasters (using GetPaneID() makes the distinction
	// between PPob_IconFamilyEditor and PPob_ICONEditor)
	UReanimator::LinkListenerToBroadcasters( this, this, this->GetPaneID() );
}


// ---------------------------------------------------------------------------
// 	InitializeFromResource
// ---------------------------------------------------------------------------

void
CWindow_IconFamily::InitializeFromResource( CRezMap *inMap, ResIDT inResID )
{
	StGWorldSaver		aSaver;
	SInt32				numTypes = GetFamilyMemberCount();
	
	// Initialize each family member 
	for ( SInt32 count = 1; count <= numTypes; count++ )
	{
		Rez_IconMemberInfo	memberInfo;
		
		GetFamilyMemberInfo( count, &memberInfo );
		
		// Initialize the main image
		Boolean hasImage = this->InitializeOneMember( 
									inMap, memberInfo.resourceType, inResID, 
									memberInfo.width, memberInfo.height, memberInfo.depth,
									0, memberInfo.rowBytes, memberInfo.samplePaneID, false );
			
		// Initialize the mask (ICN#, etc)
		if ( memberInfo.maskRowBytes != 0 )
			this->InitializeOneMember( inMap, memberInfo.resourceType, inResID,
									memberInfo.width, memberInfo.height, 1,
									memberInfo.maskOffset, memberInfo.maskRowBytes, 
									memberInfo.maskSamplePaneID, true );

		// Default to the first non-empty resource we find
		if ( hasImage && !mCurrentSamplePane )
			mCurrentSamplePane = (CDraggableTargetView*) this->FindPaneByID( memberInfo.samplePaneID );
	}

	// Need to listen to the sample panes (drag & drop, etc)
	this->BecomeListenerTo( mNumSamplePanes, mSamplePaneList );

	// If the entire family is empty, default to whichever target pane is
	// indicated by the resource
	if ( !mCurrentSamplePane )
	{
		mCurrentSamplePane = (CDraggableTargetView*) this->FindPaneByID( (**mFamilyInfoH).defaultPane );
		ThrowIfNil_( mCurrentSamplePane );
	}
	
	mCurrentSamplePane->SetTarget( true, redraw_Dont );
	this->SetImage( mCurrentSamplePane->GetBuffer(), resize_Canvas );
}


// ---------------------------------------------------------------------------
// 	InitializeOneMember
// ---------------------------------------------------------------------------

Boolean
CWindow_IconFamily::InitializeOneMember( CRezMap *inMap, ResType inResType, ResIDT inResID,
											SInt32 inWidth, SInt32 inHeight, SInt32 inDepth,
											SInt32 inOffset, SInt32 inRowBytes,
											PaneIDT inSamplePaneID, Boolean /* inIsMask */ )
{
	StRezRefSaver 	aSaver;
	COffscreen		*theBuffer = nil;
	CRezObj 		*theRes = nil;
	Boolean			isUsed = false;
	
	// Icon families use the standard color table for their depth
	CTabHandle		theTable = UColorUtils::GetColorTable( inDepth );

	try
	{
		// Create the offscreen buffer
		theBuffer = COffscreen::CreateBuffer( inWidth, inHeight, inDepth, theTable );
		
		// If we have a resource, load the data into the offscreen buffer
		theRes = UIconMisc::GetBitmapResource(inMap, inResType, inResID, true );

		if ( theRes )
		{
			Handle h = theRes->GetData();
			if ( h )
			{
				::HLock( h );
				theBuffer->CopyFromRawData( (UInt8*) *h + inOffset, inRowBytes );
				( h );
				isUsed = true;
			}
			delete theRes;
			theRes = nil;
		}

		// Initialize the sample pane
		CDraggableTargetView *thePane = (CDraggableTargetView*) this->FindPaneByID( inSamplePaneID );
		ThrowIfNil_( thePane );
		
		mSamplePaneList[ mNumSamplePanes++ ] = thePane;		
		thePane->SetUsedFlag( isUsed, redraw_Dont );		// true if the resource exists
		thePane->SetBuffer( theBuffer, redraw_Dont );
		theBuffer = nil;									// so we don't delete it below
	}
	catch( ... )
	{
		if ( theRes ) delete theRes;
		if ( theBuffer ) delete theBuffer;
		if ( theTable ) ::DisposeCTable( theTable );
		throw;
	}
	
	if ( theTable )
		::DisposeCTable( theTable );
		
	return( isUsed );
}



// ---------------------------------------------------------------------------
// 	SaveAsResource
// ---------------------------------------------------------------------------
// This has changed in post CW11. We can no longer delete all of the
// resources within an icon suite, even temporarily within this routine.
// Thus we loop twice, first creating and later deleting them. If they are
// all gone, we'll create an ICN# anyway because otherwise our view itself
// is deallocated by the resource listeners.

void
CWindow_IconFamily::SaveAsResource( CRezMap *inMap, ResIDT inResID )
{
	Rez_IconMemberInfo		memberInfo;
	SInt32					numIcons = this->GetFamilyMemberCount();
	CDraggableTargetView	*mainPane, *maskPane;
	COffscreen				*mainBuffer, *maskBuffer;
	CRezObjItem *			rezObjItem;

	// Post CW11 stuff
	SInt32					numActiveImages = 0;
	COffscreen				*icnBuffer = nil, *icnMaskBuffer = nil;
	Rez_IconMemberInfo		icnInfo;
	CDraggableTargetView	*icnPane = nil;
	
	// First create all of the resources we need to
	SInt32 count;
	for ( count = 1; count <= numIcons; count++ )
	{
		this->GetFamilyMemberInfo( count, &memberInfo );
		
		// Find the main buffer
		mainPane = (CDraggableTargetView*) this->FindPaneByID( memberInfo.samplePaneID );
		ThrowIfNil_( mainPane );
			
		mainBuffer = mainPane->GetBuffer();
		ThrowIfNil_( mainBuffer );
		
		// Find the mask buffer (if any)
		if ( memberInfo.maskRowBytes == 0 )
		{
			maskPane = nil;
			maskBuffer = nil;
		}
		else
		{
			maskPane = (CDraggableTargetView*) this->FindPaneByID( memberInfo.maskSamplePaneID );
			ThrowIfNil_( maskPane );
				
			maskBuffer = maskPane->GetBuffer();
			ThrowIfNil_( maskBuffer );
		}
		
		// Keep track of the ICN# one in case all others are deleted
		if ( memberInfo.samplePaneID == ImgType_LargeIconWithMask )
		{
			icnInfo = memberInfo;
			icnPane = mainPane;
			icnBuffer = mainBuffer;
			icnMaskBuffer = maskBuffer;
		}
		
		// Create whatever resources are used
		if ( mainPane->IsUsed() /*|| (maskPane && maskPane->IsUsed())*/ )
		{
		   // Make sure there is a corresponding RezObjItem in the table. 
		   // This is the case if a resource has been created in the bitmap editor.			
			rezObjItem = mOwnerDoc->GetRezMapTable()->CreateItemIfNecessary(memberInfo.resourceType, inResID, NULL);

			if (rezObjItem) {				
				UGraphicConversion::SaveOffscreenAsResource( 
									rezObjItem->GetRezObj(), memberInfo.resourceType, 
									mainBuffer, memberInfo.rowBytes, 
									maskBuffer, memberInfo.maskOffset, 
									memberInfo.maskRowBytes );
				++numActiveImages;
			} 
		}
	}	
	
	// If no active images, we still need to create the ICN# or very bad
	// things happen (our window gets disposed of).
	if ( (numActiveImages == 0) && icnPane && icnBuffer )
	{
		rezObjItem = mOwnerDoc->GetRezMapTable()->CreateItemIfNecessary(ImgType_LargeIconWithMask, inResID, NULL);

		if (rezObjItem) {
			UGraphicConversion::SaveOffscreenAsResource( 
									rezObjItem->GetRezObj(), ImgType_LargeIconWithMask, 
									icnBuffer, icnInfo.rowBytes, 
									icnMaskBuffer, icnInfo.maskOffset, 
									icnInfo.maskRowBytes );
		}
		
	}
	
	// Now delete all of the unused ones
	for ( count = 1; count <= numIcons; count++ )
	{
		this->GetFamilyMemberInfo( count, &memberInfo );
		
		// Find the main buffer
		mainPane = (CDraggableTargetView*) this->FindPaneByID( memberInfo.samplePaneID );
		ThrowIfNil_( mainPane );
			
		mainBuffer = mainPane->GetBuffer();
		ThrowIfNil_( mainBuffer );
		
		// Find the mask buffer (if any)
		if ( memberInfo.maskRowBytes == 0 )
		{
			maskPane = nil;
			maskBuffer = nil;
		}
		else
		{
			maskPane = (CDraggableTargetView*) this->FindPaneByID( memberInfo.maskSamplePaneID );
			ThrowIfNil_( maskPane );
				
			maskBuffer = maskPane->GetBuffer();
			ThrowIfNil_( maskBuffer );
		}
		
		if ( !mainPane->IsUsed() && ((numActiveImages > 0) || (memberInfo.resourceType != ImgType_LargeIconWithMask)) )
		{
			CRezObj * theRes = inMap->FindResource( memberInfo.resourceType, inResID, false );
			if ( theRes ) {
				theRes->Remove();
			}
			delete theRes;
		}
	}	

	this->SetDirty( false );
}


// ---------------------------------------------------------------------------
// 	GetFamilyMemberCount
// ---------------------------------------------------------------------------
SInt32
CWindow_IconFamily::GetFamilyMemberCount()
{
	return ( (**mFamilyInfoH).numEntries );
}


// ---------------------------------------------------------------------------
// 	GetFamilyMemberInfo
// ---------------------------------------------------------------------------
// 	index is 1..n

void
CWindow_IconFamily::GetFamilyMemberInfo( SInt32 index, Rez_IconMemberInfo *oRec )
{
	ThrowIf_( (index <= 0) || (index > (**mFamilyInfoH).numEntries) );
	*oRec = (**mFamilyInfoH).members[ index - 1 ];
}


// ---------------------------------------------------------------------------
// 	GetZoomFactor
// ---------------------------------------------------------------------------
// Icon suite images are always zoomed the same amount -- for a 32x32
// image. Otherwise, clicking on different target panes would resize the
// canvas and change the zoom factor and that's not very pretty.

SInt32
CWindow_IconFamily::GetZoomFactor( SInt32, SInt32, Boolean *outShowGrid )
{
	return CIcon_EditorWindow::GetZoomFactor( 32, 32, outShowGrid );
}


// ---------------------------------------------------------------------------
//	EndianConvertIconFamilyInfoHandle
// ---------------------------------------------------------------------------
// The mFamilyInfoH member is read into member as a big-endian resource handle.
// We need to endian-convert it to native format. Note that since it is used as
// a read-only resource, we don't have to worry about any updating issues.

void
CWindow_IconFamily::EndianConvertIconFamilyInfoHandle()
{
	Rez_IconFamilyInfo *	ptr = *mFamilyInfoH;
	ptr->defaultPane = ::CFSwapInt32BigToHost(ptr->defaultPane);
	ptr->numEntries = ::CFSwapInt32BigToHost(ptr->numEntries);
	for (SInt32 iEntry = 0; iEntry < ptr->numEntries; iEntry++) {
		ptr->members[iEntry].resourceType = ::CFSwapInt32BigToHost(ptr->members[iEntry].resourceType);
		ptr->members[iEntry].flags = ::CFSwapInt32BigToHost(ptr->members[iEntry].flags);
		ptr->members[iEntry].width = ::CFSwapInt32BigToHost(ptr->members[iEntry].width);
		ptr->members[iEntry].height = ::CFSwapInt32BigToHost(ptr->members[iEntry].height);
		ptr->members[iEntry].depth = ::CFSwapInt32BigToHost(ptr->members[iEntry].depth);
		ptr->members[iEntry].rowBytes = ::CFSwapInt32BigToHost(ptr->members[iEntry].rowBytes);
		ptr->members[iEntry].samplePaneID = ::CFSwapInt32BigToHost(ptr->members[iEntry].samplePaneID);
		ptr->members[iEntry].maskOffset = ::CFSwapInt32BigToHost(ptr->members[iEntry].maskOffset);
		ptr->members[iEntry].maskRowBytes = ::CFSwapInt32BigToHost(ptr->members[iEntry].maskRowBytes);
		ptr->members[iEntry].maskSamplePaneID = ::CFSwapInt32BigToHost(ptr->members[iEntry].maskSamplePaneID);
	}
}
