// ===========================================================================
// CICNS_EditorWindow.cp					
// 
//                       Created: 2006-02-23 15:12:16
//             Last modification: 2006-09-08 07:25:33
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================

#include "CICNS_EditorDoc.h"
#include "CICNS_EditorWindow.h"
#include "CICNS_Family.h"
#include "CICNS_Member.h"
#include "CIcon_EditorView.h"
#include "CRezillaApp.h"
#include "CDraggableTargetView.h"
#include "COffscreen.h"
#include "CRezObj.h"
#include "RezillaConstants.h"
#include "UMessageDialogs.h"
#include "UDragAndDropUtils.h"
#include "UMiscUtils.h"
#include "UColorUtils.h"

#include <LHandleStream.h>
#include <LPopupButton.h>
#include <LStaticText.h>
#include <LPushButton.h>

#include <stdio.h>


// ---------------------------------------------------------------------------
// 	OpenPaintWindow
// ---------------------------------------------------------------------------

CICNS_EditorWindow*
CICNS_EditorWindow::OpenPaintWindow( ResIDT inPPobID, CRezMap *inMap, ResIDT inResID )
{
	CICNS_EditorWindow *	theWindow = nil;

	try
	{
		theWindow = (CICNS_EditorWindow*) CIcon_EditorWindow::CreatePaintWindow( inPPobID );
	}
	catch( ... )
	{
		if (theWindow) { delete theWindow; } 
		throw;
	}
	
	return( theWindow );
}


// ---------------------------------------------------------------------------
//  CICNS_EditorWindow				[public]
// ---------------------------------------------------------------------------

CICNS_EditorWindow::CICNS_EditorWindow(
			       LStream *inStream )
		: CIcon_EditorWindow( inStream )
{
	OSErr	error;
	Handle	theHandle = NULL;
	
	// The ID is the same as the ID of the PPob itself
	error = UResources::GetResourceInMap( CRezillaApp::GetSelfRefNum(), ResType_IconFamilyInfo, PPob_IcnsEditorWindow, theHandle, true );
	ThrowIfOSErr_(error);
	::DetachResource(theHandle);
	mFamilyInfoH = (Rez_IconFamilyInfoH) theHandle;
	
	mCurrentIndex = 0;
}


// ---------------------------------------------------------------------------
//  ~CICNS_EditorWindow				[public]
// ---------------------------------------------------------------------------

CICNS_EditorWindow::~CICNS_EditorWindow()
{	
	if (mOutStream != nil) {
		delete mOutStream;
	} 
	if (mFamilyInfoH != nil) {
		::DisposeHandle( (Handle) mFamilyInfoH);
	} 
}


// ---------------------------------------------------------------------------
// 	CreateFromStream
// ---------------------------------------------------------------------------
CICNS_EditorWindow *
CICNS_EditorWindow::CreateFromStream( LStream *inStream )
{
	return new CICNS_EditorWindow( inStream );
}


// ---------------------------------------------------------------------------
// FinishCreateSelf												[protected]
// ---------------------------------------------------------------------------

void
CICNS_EditorWindow::FinishCreateSelf()
{	
	mOutStream = nil;
	
	// Call the inherited method
	CIcon_EditorWindow::FinishCreateSelf();

	// Note: mContentsView is defined in the CIcon_EditorWindow parent class

	mTypeField = dynamic_cast<LStaticText *>(this->FindPaneByID(item_IcnsTypeField));
	ThrowIfNil_( mTypeField );

	mIconPopup = dynamic_cast<LPopupButton *>(this->FindPaneByID(item_IcnsIconPopup));
	ThrowIfNil_( mIconPopup );

	mRemoveButton = dynamic_cast<LPushButton *>(this->FindPaneByID(item_RemoveButton));
	ThrowIfNil_( mRemoveButton );

	mIconSample = dynamic_cast<CDraggableTargetView *>(this->FindPaneByID(item_IcnsVisualize));
	ThrowIfNil_( mIconSample );
	mSamplePaneList[ mNumSamplePanes++ ] = mIconSample;
	
	mMaskSample = dynamic_cast<CDraggableTargetView *>(this->FindPaneByID(item_IconEditMask));
	ThrowIfNil_( mMaskSample );
	mSamplePaneList[ mNumSamplePanes++ ] = mMaskSample;

	// Fill the menu
	FillPopup();

	// Link the broadcasters
	UReanimator::LinkListenerToControls( this, this, PPob_IcnsEditorWindow );

	// We need to listen to the sample panes (click and/or drop operations)
	this->BecomeListenerTo( mNumSamplePanes, mSamplePaneList );
}


// ---------------------------------------------------------------------------
//	 InstallResourceData											[public]
// ---------------------------------------------------------------------------

OSErr
CICNS_EditorWindow::InstallResourceData(Handle inHandle)
{
	OSErr		error = noErr, ignoreErr = noErr;
	UInt16		numItems = 0;
	StHandleLocker	locker(inHandle);

	if (inHandle == NULL) {
		// We are creating a new resource
		mIcnsFamily = new CICNS_Family();
	} else {
		LHandleStream * theStream = new LHandleStream(inHandle);
		if ( theStream->GetMarker() < theStream->GetLength() ) {
			mIcnsFamily = new CICNS_Family(theStream);
		}
		
		// Check that all the data have been parsed
		if ( theStream->GetMarker() < theStream->GetLength() ) {
			error = err_MoreDataThanExpected;
		} 
		
		// This disposes of inHandle
		delete theStream;
	}
	
	if (error == noErr) {
		UpdatePopup();
		
		// If the resource is not empty, install the first icon member
		if (mIcnsFamily->CountMembers() > 0) {
			CICNS_Member*	theMember;			
			mIcnsFamily->GetMembers()->FetchItemAt(1, theMember);
			InstallMemberIcon(theMember);
			UpdateMemberInPopup(theMember);
		} 
		
		SetDirty(false);
	} 

	if (mCurrentIndex == 0) {
		mRemoveButton->Disable();
	}
	
	return error;
}


// ---------------------------------------------------------------------------------
//  Click
// ---------------------------------------------------------------------------------

void
CICNS_EditorWindow::Click(
	SMouseDownEvent	&inMouseDown )
{
	// In order to support dragging from an inactive window, we must
	// explicitly test for delaySelect
	if ( inMouseDown.delaySelect ) {
		// Convert to a local point
		PortToLocalPoint( inMouseDown.whereLocal );
		
		// Execute click attachments
		if ( ExecuteAttachments( msg_Click, &inMouseDown ) ) {		
			// Handle the actual click event
			ClickSelf( inMouseDown );
		}
	} else {
		// Call inherited for default behavior
		LWindow::Click( inMouseDown );
	}
}


// ---------------------------------------------------------------------------
//  ListenToMessage													[public]
// ---------------------------------------------------------------------------

void
CICNS_EditorWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{		
	CICNS_Member * theMember;
	
	switch (inMessage) {
						
		case msg_IcnsIconPopup: 
		ArrayIndexT index = mIconPopup->GetValue();
		if (index == 1) {
			return;
		} 
		if (index != mCurrentIndex) {
			theMember = GetCurrentMember();
			if ( theMember != NULL && theMember->IsModified() ) {
				StoreMemberIcon(theMember);
			} 			
			if ( ShowIconAtIndex(index) ) {
				Refresh();
			} 
		} 
		break;
		
		case msg_RemoveButton:
		DeleteIconAtIndex(mCurrentIndex);
		break;
		
		case msg_EditorModifiedItem:
		SetDirty(true);
		break;
		
		case msg_UserChangedBitmap:
		theMember = GetCurrentMember();
		if (theMember != NULL) {
			theMember->SetModified(true);
		} 
		break;
		
		default:
		CIcon_EditorWindow::ListenToMessage(inMessage, ioParam);
		break;
				
	}
}


// ---------------------------------------------------------------------------
//	 FillPopup														[public]
// ---------------------------------------------------------------------------

void
CICNS_EditorWindow::FillPopup() 
{
	SInt16	count;
	StResource	stringListH(FOUR_CHAR_CODE('STR#'), STRx_IcnsMembers, false, false);
	
	// Empty the menu
	mIconPopup->DeleteAllMenuItems();
	
	// First item is blank
	mIconPopup->AppendMenu("\p ");
	mIconTypes.AddItem( (OSType) 0);

	if ((stringListH.mResourceH != nil)) {
		count = * (SInt16*) *stringListH.mResourceH;

		if ( count > 0 ) {
			Str255		itemStr;
			for ( SInt16 i = 1; i <= count; i++ ) {
				// Get the string from the list resource
				::GetIndString( itemStr, STRx_IcnsMembers, i );
				// Append it to the menu
				AppendTypeToPopup(itemStr);
			}
		}
	}	

	mIconPopup->SetMinValue(0);
	mIconPopup->SetMaxValue(count+1);
	Refresh();
}


// ---------------------------------------------------------------------------
//	 AppendTypeToPopup
// ---------------------------------------------------------------------------

void
CICNS_EditorWindow::AppendTypeToPopup(Str255 inString)
{
	Str255 *	rightPtr;
	OSType		theType;
	
	// Ignore empty items
	if ( inString[0] ) {
		if ( UMiscUtils::SplitCaseValue(inString, &rightPtr) ) {
			UMiscUtils::PStringToOSType(*rightPtr, theType);
			if ( ::EqualString(inString, "\p-", true, false) ) {
				// This is a separator line
				theType = 0;
			}  
			mIconTypes.AddItem(theType);
			mIconPopup->AppendMenu(inString);
		}
	}
}


// ---------------------------------------------------------------------------
//	 UpdatePopup													  [public]
// ---------------------------------------------------------------------------

void
CICNS_EditorWindow::UpdatePopup() 
{
	MenuRef			theMenuH = mIconPopup->GetMacMenuH();
	SInt32			index;
	OSType			theType;
	CICNS_Member *	theMember;
	
	UInt16 theCount = ::CountMenuItems( theMenuH );
	
	for (index = 1; index <= theCount; index++) {	
		if ( mIconTypes.FetchItemAt(index, theType) && theType != 0) {
			theMember = mIcnsFamily->FindMember(theType);
			if (theMember == nil) {
				::SetItemStyle(theMenuH, index, italic);
			} else {
				// Set the current index to the first existing member
				if (mCurrentIndex == 0) {
					mCurrentIndex = index;
				} 
				::SetItemStyle(theMenuH, index, normal);
				::MacCheckMenuItem(theMenuH, index, (index == mCurrentIndex));
			}
		}
	}
}


// ---------------------------------------------------------------------------
//	 UpdateMemberInPopup											  [public]
// ---------------------------------------------------------------------------

void
CICNS_EditorWindow::UpdateMemberInPopup(CICNS_Member * inMember) 
{
	ArrayIndexT menuIndex = GetMenuIndexForType( inMember->GetType() );
	MenuRef		theMenuH = mIconPopup->GetMacMenuH();
	
	::MacCheckMenuItem(theMenuH, mCurrentIndex, 0);
	SetCurrentIndex(menuIndex);
	::MacCheckMenuItem(theMenuH, menuIndex, 1);
	mIconPopup->SetValue(menuIndex);
	UpdateTypeField( inMember->GetType() );
}


// ---------------------------------------------------------------------------
//  ShowIconAtIndex													[private]
// ---------------------------------------------------------------------------

Boolean
CICNS_EditorWindow::ShowIconAtIndex(ArrayIndexT inMenuIndex)
{
	OSType		theType;
	Boolean		result = false;
	
	if (inMenuIndex == 0) {
		// This happens when all the members have been removed
		
		mRemoveButton->Disable();
		return true;
	} 
	if ( mIconTypes.FetchItemAt(inMenuIndex, theType) ) {
		result =  ShowIconForType(theType);
	}
	return result;
}


// ---------------------------------------------------------------------------
//  ShowIconForType													[private]
// ---------------------------------------------------------------------------

Boolean
CICNS_EditorWindow::ShowIconForType(OSType inType)
{
	CICNS_Member *	theMember = nil;
	
	theMember = mIcnsFamily->FindMember(inType);
	if (theMember == nil) {
		theMember = CreateNewMember(inType);
	} 
	
	if (theMember != nil) {
		InstallMemberIcon(theMember);
		UpdateMemberInPopup(theMember);
	}

	return (theMember != nil);
}


// ---------------------------------------------------------------------------
//  InstallMemberIcon												[private]
// ---------------------------------------------------------------------------
// 		resize_None			= 0x00,
// 		resize_Canvas		= 0x01,
// 		resize_MoveSamples	= 0x02,
// 		resize_Window		= 0x04,
// 		resize_All			= 0xFF

void
CICNS_EditorWindow::InstallMemberIcon(CICNS_Member * inMember)
{
	SInt32			depth, width, height, rowBytes, maskOffset, maskRowBytes;
	COffscreen		*theImage = nil, *theMask = nil;
	CTabHandle		theTable = nil;
	Handle			imgDataH = inMember->GetIconData();
	MenuRef			theMenuH = mIconPopup->GetMacMenuH();
	
	GetIconMemberParams(inMember->GetType(), depth, width, height, rowBytes, maskOffset, maskRowBytes);
	
	// Icon suites use the standard color table for their depth
	theTable = UColorUtils::GetColorTable( depth );
	
	// Allocate the color bitmap
	theImage = COffscreen::CreateBuffer( width, height, depth, theTable );
	if ( rowBytes != 0 ) {
		theImage->CopyFromRawData( (UInt8*) *imgDataH, rowBytes );
	}
	
	if ( maskRowBytes != 0 ) {
		theMask = COffscreen::CreateBuffer( width, height, depth, theTable );
		theMask->CopyFromRawData( (UInt8*) *imgDataH + maskOffset, maskRowBytes );		
	}
	
	// Set the image
	this->SetImage( theImage, resize_Canvas | resize_MoveSamples );

	// In the case of a 128x128 member we must resize the window
	ResizeWindowIfNecessary( inMember->GetType() );
	ResizeSamplesIfNecessary( width, height, (maskRowBytes != 0) );
	
	// Setup the sample buffer. Set the image buffer to nil because it
	// belongs to the sample pane once the call succeeds.
	mIconSample->SetBuffer( theImage, redraw_Dont );
	theImage = nil;
	mIconSample->SetUsedFlag( true, redraw_Dont );		// true if the resource exists
	mIconSample->SetTarget( true, redraw_Dont );
	mCurrentSamplePane = mIconSample;	

	if (theMask) {
		mMaskSample->SetBuffer( theMask, redraw_Dont );
		mMaskSample->SetUsedFlag( true, redraw_Dont );
		theMask = nil;
		mMaskSample->Show();
	} else {
		mMaskSample->Hide();
		mMaskSample->SetUsedFlag( false, redraw_Dont );
	}
	
	if ( theTable ) {
		::DisposeCTable( theTable );
	}
}


// ---------------------------------------------------------------------------
//  StoreMemberIcon													[private]
// ---------------------------------------------------------------------------

void
CICNS_EditorWindow::StoreMemberIcon(CICNS_Member * inMember)
{
	SInt32			depth, width, height, rowBytes, maskOffset, maskRowBytes;
	COffscreen		*theImage = nil, *theMask = nil;
	Handle			imgDataH = inMember->GetIconData();
	MenuRef			theMenuH = mIconPopup->GetMacMenuH();
	
	ThrowIf_( !mIconSample || !mMaskSample );

	GetIconMemberParams(inMember->GetType(), depth, width, height, rowBytes, maskOffset, maskRowBytes);
	
	theImage = mIconSample->GetBuffer();
	theImage->CopyToRawData( (UInt8*) *imgDataH, rowBytes );

	if ( maskRowBytes && mMaskSample->IsUsed() ) {
		theMask = mMaskSample->GetBuffer();
		theMask->CopyToRawData( (UInt8*) *imgDataH + maskOffset, maskRowBytes );		
	} 
	
	inMember->SetModified(false);
}


// ---------------------------------------------------------------------------
//  CreateNewMember														[private]
// ---------------------------------------------------------------------------

CICNS_Member *
CICNS_EditorWindow::CreateNewMember(OSType inType)
{
	Str255 			theString;
	CICNS_Member *	theMember = nil;
	MenuRef			theMenuH = mIconPopup->GetMacMenuH();
	ArrayIndexT		menuIndex = GetMenuIndexForType(inType);
	
	// Ask to create a new member
	GetMenuItemText(theMenuH, menuIndex, theString);
	if ( UMessageDialogs::AskIfWithString(CFSTR("ConfirmCreateIcnsMember"), theString) == true) {
		Size				theSize;
		Handle				theHandle;
		Rez_IconMemberInfo	rim;

		GetFamilyMemberInfo(inType, &rim);
		theSize = rim.width * rim.height * rim.depth / 8;
		// Double the size for types with a mask ('ics#', 'icm#', 'ICN#', 'ich#')
		if (rim.maskRowBytes) {
			theSize *= 2;
		} 
		theHandle = NewHandleClear(theSize);
		if (theHandle != NULL) {
			theMember = new CICNS_Member(inType, theHandle);
		} 
		
		if (theMember) {
			mIcnsFamily->AddMember(theMember);
			::SetItemStyle(theMenuH, menuIndex, normal);
			mRemoveButton->Enable();
		} else {
			UMessageDialogs::AlertWithString(CFSTR("CreatingIcnsMemberFailed"), theString);
		}
	} else {
		// Reset the menu at its current index
		mIconPopup->SetValue(mCurrentIndex);
	}	
	
	return theMember;
}


// ---------------------------------------------------------------------------
//  DeleteIconAtIndex												[private]
// ---------------------------------------------------------------------------

void
CICNS_EditorWindow::DeleteIconAtIndex(ArrayIndexT inMenuIndex, Boolean askYesNo)
{
	Str255 			theString;
	CICNS_Member *	theMember = nil;
	MenuRef			theMenuH = mIconPopup->GetMacMenuH();
	Boolean			removeIt = true;
	
	if (askYesNo) {
		// Ask before deleting the member
		GetMenuItemText(theMenuH, inMenuIndex, theString);
		removeIt = UMessageDialogs::AskIfWithString(CFSTR("ConfirmRemoveIcnsMember"), theString);
	} 
	
	if (removeIt == true) {
		OSType	theType;
		if ( mIconTypes.FetchItemAt(inMenuIndex, theType) ) {
			theMember = mIcnsFamily->FindMember(theType);
		}
		
		if (theMember) {
			mIcnsFamily->DeleteMember(theMember);
			::MacCheckMenuItem(theMenuH, mCurrentIndex, 0);
			::SetItemStyle(theMenuH, inMenuIndex, italic);
			
			// If the resource is not empty, reinstall the first icon member
			if (mIcnsFamily->CountMembers() > 0) {
				mIcnsFamily->GetMembers()->FetchItemAt(1, theMember);
				InstallMemberIcon(theMember);
				UpdateMemberInPopup(theMember);
			} else {
				mCurrentIndex = 0;
			}
			
			if ( ShowIconAtIndex(mCurrentIndex) ) {
				Refresh();
			} 
		} else {
			UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("RemovingIcnsMemberFailed"), PPob_SimpleMessage);
		}
	} 
}


// ---------------------------------------------------------------------------
//  UpdateTypeField												[private]
// ---------------------------------------------------------------------------

void
CICNS_EditorWindow::UpdateTypeField(OSType inType)
{
	Str255 theString;
	UMiscUtils::OSTypeToPString(inType, theString);
	mTypeField->SetDescriptor(theString);
// 	::NumToString(inSize, theString);
// 	mSizeField->SetDescriptor(theString);
}


// ---------------------------------------------------------------------------
//  CollectResourceData												[public]
// ---------------------------------------------------------------------------

Handle
CICNS_EditorWindow::CollectResourceData() 
{
	Handle	theHandle = NewHandle(0);
	
	try {
		if (mOutStream != nil) {delete mOutStream;} 
		
		mOutStream = new LHandleStream(theHandle);	
		ThrowIfNil_(mOutStream);

		mIcnsFamily->SendDataToStream(mOutStream);
		
		theHandle = mOutStream->GetDataHandle();
	}
	catch (...) {
		UMessageDialogs::AlertWithType(CFSTR("SavingResourceFailed"), kIconFamilyType);
	}
	
	return theHandle;
}


// ---------------------------------------------------------------------------
// 	SaveAsResource
// ---------------------------------------------------------------------------
// Pure virtual

void
CICNS_EditorWindow::SaveAsResource( CRezMap *inMap, ResIDT inResID )
{
}


// ---------------------------------------------------------------------------
//  RevertContents												  [public]
// ---------------------------------------------------------------------------

void
CICNS_EditorWindow::RevertContents()
{
	OSErr error = noErr;
	
	// Delete the panes
	mContentsView->DeleteAllSubPanes();
// 	// Reset the array
// 	mIndexedFields.RemoveAllItemsAfter(0);

	mContentsView->Hide();
	
	// Reinstall the strings
	CRezObj * theRezObj = mOwnerDoc->GetRezObj();
	if (theRezObj != nil) {
		Handle rezData = theRezObj->GetData();
		
		try {
			if (rezData != nil) {
				// Work with a copy of the handle
				::HandToHand(&rezData);
				error = InstallResourceData(rezData);			
			} 
			ThrowIfError_(error);			
		} catch (...) {
			UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("DataParsingException"), PPob_SimpleMessage);
			return;
		}
	} 
	
	mContentsView->Show();
	mContentsView->Enable();
	Refresh();
	SetDirty(false);
}


// ---------------------------------------------------------------------------
// 	GetFamilyMemberCount
// ---------------------------------------------------------------------------

SInt32
CICNS_EditorWindow::GetFamilyMemberCount()
{
	return ( (**mFamilyInfoH).numEntries );
}


// ---------------------------------------------------------------------------
// 	GetFamilyMemberInfo
// ---------------------------------------------------------------------------

void
CICNS_EditorWindow::GetFamilyMemberInfo( OSType inType, Rez_IconMemberInfo *oRec )
{
	SInt32	numIcons = this->GetFamilyMemberCount();
	SInt32	count;
	
	for ( count = 0; count < numIcons; count++ ) {		
		if ((**mFamilyInfoH).members[count].resourceType == inType) {
			*oRec = (**mFamilyInfoH).members[count];
			break;
		} 
	}
}


// ---------------------------------------------------------------------------
// 	GetIconMemberParams
// ---------------------------------------------------------------------------

void
CICNS_EditorWindow::GetIconMemberParams(OSType inType, SInt32 &inDepth, 
										SInt32 &inWidth, SInt32 &inHeight, SInt32 &inRowBytes, 
										SInt32 &inMaskOffset, SInt32 &inMaskRowBytes)
{
	Rez_IconMemberInfo	rim;
	GetFamilyMemberInfo(inType, &rim);
	inDepth = rim.depth;
	inWidth = rim.width;
	inHeight = rim.height;
	inRowBytes = rim.rowBytes;
	inMaskRowBytes = rim.maskRowBytes;
	inMaskOffset = rim.maskOffset;
}


// ---------------------------------------------------------------------------
//	 GetMenuIndexForType											[public]
// ---------------------------------------------------------------------------

ArrayIndexT
CICNS_EditorWindow::GetMenuIndexForType(OSType inType) 
{
	ArrayIndexT	index = mIconTypes.FetchIndexOf(inType);
	return index;
}


// ---------------------------------------------------------------------------
//	 GetCurrentMember											[public]
// ---------------------------------------------------------------------------

CICNS_Member *
CICNS_EditorWindow::GetCurrentMember()
{
	CICNS_Member *	theMember = NULL;
	OSType			theType;
	
	if ( mIconTypes.FetchItemAt(mCurrentIndex, theType) ) {
		theMember = mIcnsFamily->FindMember(theType);
	}
	return theMember;
}


// ---------------------------------------------------------------------------
// 	GetZoomFactor
// ---------------------------------------------------------------------------
// Icon suite images are zoomed depending on the image size, as defined in 
// the CIcon_EditorWindow class

SInt32
CICNS_EditorWindow::GetZoomFactor( SInt32 inWidth, SInt32 inHeight, Boolean *outShowGrid )
{
	return CIcon_EditorWindow::GetZoomFactor( inWidth, inHeight, outShowGrid );
}


// ---------------------------------------------------------------------------
// 	ResizeWindowIfNecessary
// ---------------------------------------------------------------------------

void
CICNS_EditorWindow::ResizeWindowIfNecessary(OSType inType)
{
	Rect	theFrame;
	this->CalcPortFrameRect( theFrame );
	this->PortToGlobalPoint( topLeft(theFrame) );
	this->PortToGlobalPoint( botRight(theFrame) );
	
	if (inType == 'it32' || inType == 't8mk' || inType == 'drop' 
		|| inType == 'odrp' || inType == 'open' || inType == 'over' || inType == 'tile' ) {
		theFrame.bottom = theFrame.top + kIcnsWindowLargeHeight;
		theFrame.right = theFrame.left + kIcnsWindowLargeWidth;
	} else {
		theFrame.bottom = theFrame.top + kIcnsWindowNormalHeight;
		theFrame.right = theFrame.left + kIcnsWindowNormalWidth;
	}
	DoSetBounds(theFrame);
}


// ---------------------------------------------------------------------------
// 	ResizeSamplesIfNecessary
// ---------------------------------------------------------------------------

void
CICNS_EditorWindow::ResizeSamplesIfNecessary(SInt16 inWidth, SInt16 inHeight, Boolean hasMask)
{
	mIconSample->ResizeFrameTo(inWidth, inHeight, false);
	if (hasMask) {
		SPoint32	iconLoc, maskLoc;
		mMaskSample->ResizeFrameTo(inWidth, inHeight, false);
		mIconSample->GetFrameLocation(iconLoc);
		mMaskSample->GetFrameLocation(maskLoc);
		mMaskSample->MoveBy(0, iconLoc.v + inHeight + kIcnsSampleSep - maskLoc.v, false);
	} 
}


// ---------------------------------------------------------------------------
//  ImportData													[public]
// ---------------------------------------------------------------------------

OSErr
CICNS_EditorWindow::ImportData(Handle inHandle) 
{
	OSErr error;
	
	if (mIcnsFamily != NULL) {
		delete mIcnsFamily;
	} 
	error = InstallResourceData(inHandle);			
	SetDirty(true);

	return error;
}


#pragma mark -

