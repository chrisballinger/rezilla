// ===========================================================================
// CICNS_EditorWindow.cp					
// 
//                       Created: 2006-02-23 15:12:16
//             Last modification: 2006-03-12 06:54:33
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
	
	error = UResources::GetResourceInMap( CRezillaApp::GetSelfRefNum(), ResType_IconFamilyInfo, kIconSuiteIconInfo, theHandle, true );
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

// 	mSizeField = dynamic_cast<LStaticText *>(this->FindPaneByID(item_IcnsSizeField));
// 	ThrowIfNil_( mSizeField );

	mIconPopup = dynamic_cast<LPopupButton *>(this->FindPaneByID(item_IcnsIconPopup));
	ThrowIfNil_( mIconPopup );

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

	LHandleStream * theStream = new LHandleStream(inHandle);
	
	if ( theStream->GetLength() == 0 ) {
		// We are creating a new resource
	} else {
		if ( theStream->GetMarker() < theStream->GetLength() ) {
			mIcnsFamily = new CICNS_Family(theStream);
		}
		
		// Check that all the data have been parsed
		if ( theStream->GetMarker() < theStream->GetLength() ) {
			error = err_MoreDataThanExpected;
		} 
	}
	
	// This disposes of inHandle
	delete theStream;
	
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
	switch (inMessage) {
						
		case msg_IcnsIconPopup: 
		ArrayIndexT index = mIconPopup->GetValue();
		if (index != mCurrentIndex) {
			if ( ShowIconAtIndex(index) ) {
				SetDirty(true);
				Refresh();
			} 
		} 
		break;
		
		case cmd_Clear:
		DeleteIconAtIndex(mCurrentIndex);
		break;
		
		case msg_EditorModifiedItem:
		SetDirty(true);
		break;
		
		default:
		dynamic_cast<CICNS_EditorDoc *>(mOwnerDoc)->ListenToMessage(inMessage, ioParam);
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
		theMember = CreateIcon(inType);
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

	Size sz = GetHandleSize(imgDataH);
	
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

	// Setup the sample buffer. Set the image buffer to nil because it
	// belongs to the sample pane once the call succeeds.
	mIconSample->SetBuffer( theImage, redraw_Dont );
	theImage = nil;
	mIconSample->SetUsedFlag( true, redraw_Dont );		// true if the resource exists
	mIconSample->SetTarget( true, redraw_Dont );
	mCurrentSamplePane = mIconSample;	

	if (theMask) {
		mMaskSample->SetBuffer( theMask, redraw_Dont );
		theMask = nil;
		mMaskSample->Show();
	} else {
		mMaskSample->Hide();
	}
	
	if ( theTable )
		::DisposeCTable( theTable );
		

}


// ---------------------------------------------------------------------------
//  CreateIcon														[private]
// ---------------------------------------------------------------------------

CICNS_Member *
CICNS_EditorWindow::CreateIcon(OSType inType)
{
	Str255 			theString;
	CICNS_Member *	theMember = nil;
	MenuRef			theMenuH = mIconPopup->GetMacMenuH();
	ArrayIndexT		menuIndex = GetMenuIndexForType(inType);
	
	// Ask to create a new member
	GetMenuItemText(theMenuH, menuIndex, theString);
	if ( UMessageDialogs::AskIfWithString(CFSTR("ConfirmCreateIcnsMember"), theString) == true) {
		theMember = new CICNS_Member(inType);
		if (theMember) {
			mIcnsFamily->AddMember(theMember);
			::SetItemStyle(theMenuH, menuIndex, normal);
		} else {
			UMessageDialogs::AskIfWithString(CFSTR("CreatingIcnsMemberFailed"), theString);
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
CICNS_EditorWindow::DeleteIconAtIndex(ArrayIndexT index)
{
	MenuRef			theMenuH = mIconPopup->GetMacMenuH();
	
	mIcnsFamily->DeleteMember(index);
	::MacCheckMenuItem(theMenuH, mCurrentIndex, 0);
	::SetItemStyle(theMenuH, index, italic);
	SetCurrentIndex(0);
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
	Handle	theHandle = NULL;
	
	try {
		if (mOutStream != nil) {delete mOutStream;} 

		mOutStream = new LHandleStream();	
		ThrowIfNil_(mOutStream);

		mIcnsFamily->SendDataToStream(mOutStream);
		
		theHandle = mOutStream->GetDataHandle();
	}
	catch (...) {
// 		UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("SaveStringsFailed"), PPob_SimpleMessage);
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
// 	GetZoomFactor
// ---------------------------------------------------------------------------
// Icon suite images are zoomed depending on the image size, as defined in 
// the CIcon_EditorWindow class

SInt32
CICNS_EditorWindow::GetZoomFactor( SInt32 inWidth, SInt32 inHeight, Boolean *outShowGrid )
{
	return CIcon_EditorWindow::GetZoomFactor( inWidth, inHeight, outShowGrid );
}


#pragma mark -

