// ===========================================================================
// CInspectorWindow.cp					
// 
//                       Created: 2003-05-02 07:33:10
//             Last modification: 2004-04-15 15:00:03
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#include "CInspectorWindow.h"
#include "RezillaConstants.h"
#include "CRezillaApp.h"
#include "CRezMapDoc.h"
#include "CRezMapWindow.h"
#include "CRezMapTable.h"
#include "CRezObj.h"
#include "CRezObjItem.h"
#include "CRezIconPane.h"
#include "UMiscUtils.h"
#include "CWindowMenu.h"
#include "UResources.h"

#include <LWindow.h>
#include <LPushButton.h>
#include <LCheckBox.h>
#include <LEditText.h>
#include <LStaticText.h>
#include <UExtractFromAEDesc.h>
#include <UAppleEventsMgr.h>
#include <UCursor.h>

#include <AppleHelp.h>

#include <string.h>

// ---------------------------------------------------------------------------
//		¥ CInspectorWindow				[public]
// ---------------------------------------------------------------------------

CInspectorWindow::CInspectorWindow()
{
}


// ---------------------------------------------------------------------------
//		¥ CInspectorWindow				[public]
// ---------------------------------------------------------------------------

CInspectorWindow::CInspectorWindow(
	const SWindowInfo &inWindowInfo )
		: LWindow( inWindowInfo )
{
}


// ---------------------------------------------------------------------------
//		¥ CInspectorWindow				[public]
// ---------------------------------------------------------------------------

CInspectorWindow::CInspectorWindow(
	ResIDT		inWINDid,
	UInt32		inAttributes,
	LCommander	*inSuperCommander )
		: LWindow( inWINDid, inAttributes, inSuperCommander )
{
}


// ---------------------------------------------------------------------------
//		¥ CInspectorWindow				[public]
// ---------------------------------------------------------------------------

CInspectorWindow::CInspectorWindow(
			       LStream *inStream )
		: LWindow( inStream )
{
}


// ---------------------------------------------------------------------------
//		¥ ~CInspectorWindow				[public]
// ---------------------------------------------------------------------------

CInspectorWindow::~CInspectorWindow()
{
}


// ---------------------------------------------------------------------------
//		¥ FinishCreateSelf				[protected]
// ---------------------------------------------------------------------------

void
CInspectorWindow::FinishCreateSelf()
{	
	mRezObjItem = nil;
	InitializeRezInfo();
	
	// Static text
	mTypeItem = dynamic_cast<LStaticText *>(this->FindPaneByID( item_InspType ));
	ThrowIfNil_( mTypeItem );
		
	mSizeItem = dynamic_cast<LStaticText *>(this->FindPaneByID( item_InspSize ));
	ThrowIfNil_( mSizeItem );
		
	// Editable text
	mIDEdit = dynamic_cast<LEditText *>(this->FindPaneByID( item_InspEditID ));
	ThrowIfNil_( mIDEdit );
		
	mNameEdit = dynamic_cast<LEditText *>(this->FindPaneByID( item_InspEditName ));
	ThrowIfNil_( mNameEdit );
		
	mIconItem = dynamic_cast<CRezIconPane *>(this->FindPaneByID( item_InspIcon ));
	ThrowIfNil_( item_InspIcon );
	
	// CheckBoxes
	mSysHeapItem = dynamic_cast<LCheckBox *>(this->FindPaneByID( item_InspSysHeap ));
	ThrowIfNil_( mSysHeapItem );
	
	mPurgeableItem = dynamic_cast<LCheckBox *>(this->FindPaneByID( item_InspPurgeable ));
	ThrowIfNil_( mPurgeableItem );
	
	mLockedItem = dynamic_cast<LCheckBox *>(this->FindPaneByID( item_InspLocked ));
	ThrowIfNil_( mLockedItem );
	
	mProtectedItem = dynamic_cast<LCheckBox *>(this->FindPaneByID( item_InspProtected ));
	ThrowIfNil_( mProtectedItem );
	
	mPreloadItem = dynamic_cast<LCheckBox *>(this->FindPaneByID( item_InspPreload ));
	ThrowIfNil_( mPreloadItem );
	
	// Buttons
	mRevertButton = dynamic_cast<LPushButton *>(this->FindPaneByID( item_InspRevert ));
	ThrowIfNil_( mRevertButton );
	
	mModifyButton = dynamic_cast<LPushButton *>(this->FindPaneByID( item_InspModify ));
	ThrowIfNil_( mModifyButton );
	
	// Let window listen to its sub panes
    UReanimator::LinkListenerToControls( this, this, rRidL_InspectorWindow );

}


// ---------------------------------------------------------------------------------
//  ¥ FindCommandStatus
// ---------------------------------------------------------------------------------

void
CInspectorWindow::FindCommandStatus(
	CommandT	inCommand,
	Boolean		&outEnabled,
	Boolean		&outUsesMark,
	UInt16		&outMark,
	Str255		outName )
{

	switch (inCommand) {
	
		case cmd_New:
		case cmd_Open:
		outEnabled = true;
			break;		
		
		case cmd_NewRez:
		case cmd_Find:
		case cmd_FindNext:
		case cmd_EditRez:
		case cmd_EditRezAsType:
		case cmd_TmplEditRez:
		case cmd_HexEditRez:
		case cmd_GetRezInfo:
		case cmd_RemoveRez:
		case cmd_DuplicateRez:
		case cmd_ShowInspector:
			outEnabled = false;
			break;		
		
		default:
			LWindow::FindCommandStatus(inCommand, outEnabled,
												outUsesMark, outMark, outName);
			break;
	}
}


// ---------------------------------------------------------------------------
//		¥ ListenToMessage				[public]
// ---------------------------------------------------------------------------

void
CInspectorWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{
#pragma unused( ioParam )
	
	switch (inMessage) {
		
		case msg_InspModify: 
		if (mRezObjItem == nil) {return;} 
		SaveValues();
		// Update the resource properties in memory 
		UpdateRezObj();
		// Refresh the rezmap table
		mRezObjItem->GetOwnerRezMapTable()->Refresh();
		mRezObjItem->GetOwnerRezMapTable()->GetOwnerDoc()->SetModified(true);
		// Disable the buttons
		mRevertButton->Disable();
		mModifyButton->Disable();
		break;
		
		case msg_InspRevert:
		if (mRezObjItem == nil) {return;} 
		InstallValues();
		mRevertButton->Disable();
		mModifyButton->Disable();
		break;
		
		case msg_InspEditID:
		case msg_InspEditName:
		case msg_InspSysHeap:
		case msg_InspPurgeable:
		case msg_InspLocked:
		case msg_InspProtected:
		case msg_InspPreload:
		mRevertButton->Enable();
		mModifyButton->Enable();
		break;
				
		case msg_Close:
		CRezillaApp::sInspectorWindow->Hide();
		break;
		
	}
}	


// ---------------------------------------------------------------------------
//	¥ ShowSelf
// ---------------------------------------------------------------------------

void
CInspectorWindow::ShowSelf()
{
	UDesktop::ShowDeskWindow(this);
}


// ---------------------------------------------------------------------------
//	¥ AttemptClose
// ---------------------------------------------------------------------------
//	Try to close a Window as a result of direct user action

void
CInspectorWindow::AttemptClose()
{
	SendSelfAE(kAECoreSuite, kAEClose, ExecuteAE_No);
	DoClose();
}


// ---------------------------------------------------------------------------
//	¥ DoClose
// ---------------------------------------------------------------------------
//	Close the inspector window: hide it but keep it in memory, then make 
// sure the top window gets the target.

void
CInspectorWindow::DoClose()
{
	Hide();
}


// ---------------------------------------------------------------------------
//	¥ InitializeRezInfo												[private]
// ---------------------------------------------------------------------------

void
CInspectorWindow::InitializeRezInfo()
{
	mSavedInfo.type = 0;
	mSavedInfo.size = 0;
	mSavedInfo.id = 0;
	mSavedInfo.name[0] = 0;
	mSavedInfo.iconid = 0;
	mSavedInfo.sysheap = 0;
	mSavedInfo.purge = 0;
	mSavedInfo.lock = 0;
	mSavedInfo.protect = 0;
	mSavedInfo.preload = 0;
}


// ---------------------------------------------------------------------------
//	¥ SetSavedInfo												[protected]
// ---------------------------------------------------------------------------

void
CInspectorWindow::SetSavedInfo(SResourceObjInfoPtr inRezInfoPtr)
{
	BlockMoveData(inRezInfoPtr,&mSavedInfo,sizeof(SResourceObjInfo));
}


// ---------------------------------------------------------------------------
//	¥ InstallValues												[public]
// ---------------------------------------------------------------------------

void
CInspectorWindow::InstallValues(CRezObjItem * inRezObjItem)
{
	ThrowIfNil_(inRezObjItem);
	
	mRezObjItem = inRezObjItem;
	CRezObj * theRezObj = inRezObjItem->GetRezObj();
	
	// Fill the SResourceObjInfo
	mSavedInfo.refnum = theRezObj->GetOwnerRefnum();
	mSavedInfo.type = theRezObj->GetType();
	mSavedInfo.size = theRezObj->GetSize();
	mSavedInfo.id = theRezObj->GetID();
	BlockMoveData(theRezObj->GetName(),&mSavedInfo.name,sizeof(Str255));
	mSavedInfo.iconid = 0;
	mSavedInfo.sysheap = theRezObj->HasAttribute(resSysHeap);
	mSavedInfo.purge = theRezObj->HasAttribute(resPurgeable);
	mSavedInfo.lock = theRezObj->HasAttribute(resLocked);
	mSavedInfo.protect = theRezObj->HasAttribute(resProtected);
	mSavedInfo.preload = theRezObj->HasAttribute(resPreload);

	InstallValues();
}


// ---------------------------------------------------------------------------
//	¥ InstallValues												[public]
// ---------------------------------------------------------------------------

void
CInspectorWindow::InstallValues()
{
	Str255		theString, theType;

	// Static texts
	UMiscUtils::OSTypeToPString(mSavedInfo.type, theType);	
	mTypeItem->SetDescriptor(theType);
	::NumToString(mSavedInfo.size, theString);
	mSizeItem->SetDescriptor(theString);

	// Editable texts
	mNameEdit->SetDescriptor(mSavedInfo.name);
	::NumToString(mSavedInfo.id,theString);
	mIDEdit->SetDescriptor(theString);

	// Check boxes
	mSysHeapItem->SetValue(mSavedInfo.sysheap);
	mPurgeableItem->SetValue(mSavedInfo.purge);
	mLockedItem->SetValue(mSavedInfo.lock);
	mProtectedItem->SetValue(mSavedInfo.protect);
	mPreloadItem->SetValue(mSavedInfo.preload);
	
	// Icon
	// To use PlotIconID(), the icon resource must be of resource type 
	// 'ICN#', 'ics#', 'icl4', 'icl8', 'ics4', or 'ics8'.
	mIconItem->SetIconID(mSavedInfo.id);
	if ( ! ::strncmp( (const char *) theType + 1, "ics8", 4)
		|| ! ::strncmp( (const char *) theType + 1, "ics4", 4)
		|| ! ::strncmp( (const char *) theType + 1, "icl8", 4)
		|| ! ::strncmp( (const char *) theType + 1, "icl4", 4)
		|| ! ::strncmp( (const char *) theType + 1, "ics#", 4)
		|| ! ::strncmp( (const char *) theType + 1, "ICN#", 4) ) {
		mIconItem->SetCurrentRefNum(mSavedInfo.refnum);
		mIconItem->SetVisibleState(triState_Off);
		mIconItem->Show();
	} else {
		mIconItem->SetCurrentRefNum(UResources::refNum_Undef);
		mIconItem->Hide();
	}
	
	// Disable the buttons
	mRevertButton->Disable();
	mModifyButton->Disable();
	
	if (mRezObjItem != nil) {
		// Install the rez map name
		LStaticText * theStaticText = dynamic_cast<LStaticText *>(this->FindPaneByID( item_InspMapName ));
		ThrowIfNil_( theStaticText );
		mRezObjItem->GetOwnerRezMapTable()->GetOwnerWindow()->GetDescriptor(theString);
		theStaticText->SetDescriptor(theString);
	} 
}


// ---------------------------------------------------------------------------
//	¥ SaveValues											[protected]
// ---------------------------------------------------------------------------

void
CInspectorWindow::SaveValues()
{
	Str255		theString;
	char * theType = new char[5];

	// Static texts
	mTypeItem->GetDescriptor(theString);
	UMiscUtils::PStringToOSType(theString, mSavedInfo.type);	
	mSizeItem->GetDescriptor(theString);
	::StringToNum(theString,&mSavedInfo.size);

	// Editable texts
	mNameEdit->GetDescriptor(mSavedInfo.name);
	mIDEdit->GetDescriptor(theString);
	::StringToNum(theString,&mSavedInfo.id);

	// Check boxes
	mSavedInfo.sysheap	= mSysHeapItem->GetValue();
	mSavedInfo.purge	= mPurgeableItem->GetValue();
	mSavedInfo.lock		= mLockedItem->GetValue();
	mSavedInfo.protect	= mProtectedItem->GetValue();
	mSavedInfo.preload	= mPreloadItem->GetValue();
}


// ---------------------------------------------------------------------------
//	¥ UpdateRezObj											[private]
// ---------------------------------------------------------------------------

void
CInspectorWindow::UpdateRezObj()
{
	OSErr error;
	short theAttrs = 0;
	
	Assert_(mRezObjItem != nil);
	
	CRezObj * theRezObj = mRezObjItem->GetRezObj();
	theRezObj->SetID(mSavedInfo.id);
	theRezObj->SetName(&mSavedInfo.name);
	error = theRezObj->SetInfoInMap();

	// Deal with the attributes
	theAttrs |= mSavedInfo.lock ? resLocked : 0;
	theAttrs |= mSavedInfo.preload ? resPreload : 0;
	theAttrs |= mSavedInfo.protect ? resProtected : 0;
	theAttrs |= mSavedInfo.purge ? resPurgeable : 0;
	theAttrs |= mSavedInfo.sysheap ? resSysHeap : 0;
	// Put the value in the rezmap
	error = theRezObj->SetAttributesInMap(theAttrs);
	if (error == noErr) {
		theRezObj->Changed();
	} 
}

	
// ---------------------------------------------------------------------------
//	¥ ClearValues											[protected]
// ---------------------------------------------------------------------------

void
CInspectorWindow::ClearValues()
{
	// Text fields
	mTypeItem->SetDescriptor("\p");
	mSizeItem->SetDescriptor("\p");
	mNameEdit->SetDescriptor("\p");
	mIDEdit->SetDescriptor("\p");

	// Check boxes
	mSysHeapItem->SetValue(0);
	mPurgeableItem->SetValue(0);
	mLockedItem->SetValue(0);
	mProtectedItem->SetValue(0);
	mPreloadItem->SetValue(0);
	
	// Icon
	mIconItem->Hide();

	// Invalidate the reference to the associated RezObjItem
	mRezObjItem = nil;
}


