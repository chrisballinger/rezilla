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
		
	mIDItem = dynamic_cast<LStaticText *>(this->FindPaneByID( item_InspOrigID ));
	ThrowIfNil_( mIDItem );
		
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
	
	mCompressedItem = dynamic_cast<LCheckBox *>(this->FindPaneByID( item_InspCompressed ));
	ThrowIfNil_( mCompressedItem );
	
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
		RetrieveValues();
		InstallValues();
		// Update the resource properties in memory accordingly 
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
		case msg_InspCompressed:
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
	mSavedRezInfo.type = 0;
	mSavedRezInfo.size = 0;
	mSavedRezInfo.id = 0;
	BlockMoveData("\p",&mSavedRezInfo.name,sizeof(Str255));
	mSavedRezInfo.iconid = 0;
	mSavedRezInfo.sysheap = 0;
	mSavedRezInfo.purge = 0;
	mSavedRezInfo.lock = 0;
	mSavedRezInfo.protect = 0;
	mSavedRezInfo.preload = 0;
	mSavedRezInfo.compress = 0;
}


// ---------------------------------------------------------------------------
//	¥ SetSavedRezInfo												[protected]
// ---------------------------------------------------------------------------

void
CInspectorWindow::SetSavedRezInfo(SResourceObjInfoPtr inRezInfoPtr)
{
	BlockMoveData(inRezInfoPtr,&mSavedRezInfo,sizeof(SResourceObjInfo));
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
	mSavedRezInfo.refnum = theRezObj->GetOwnerRefnum();
	mSavedRezInfo.type = theRezObj->GetType();
	mSavedRezInfo.size = theRezObj->GetSize();
	mSavedRezInfo.id = theRezObj->GetID();
	BlockMoveData(theRezObj->GetName(),&mSavedRezInfo.name,sizeof(Str255));
	mSavedRezInfo.iconid = 0;
	mSavedRezInfo.sysheap = theRezObj->HasAttribute(resSysHeap);
	mSavedRezInfo.purge = theRezObj->HasAttribute(resPurgeable);
	mSavedRezInfo.lock = theRezObj->HasAttribute(resLocked);
	mSavedRezInfo.protect = theRezObj->HasAttribute(resProtected);
	mSavedRezInfo.preload = theRezObj->HasAttribute(resPreload);
	mSavedRezInfo.compress = 0;

	InstallValues();
}


// ---------------------------------------------------------------------------
//	¥ InstallValues												[public]
// ---------------------------------------------------------------------------

void
CInspectorWindow::InstallValues()
{
	InstallValues(&mSavedRezInfo);
}


// ---------------------------------------------------------------------------
//	¥ InstallValues												[public]
// ---------------------------------------------------------------------------

void
CInspectorWindow::InstallValues(SResourceObjInfoPtr inRezInfoPtr)
{
	Str255		theString, theType;

	// Static texts
	UMiscUtils::OSTypeToPString(inRezInfoPtr->type, theType);	
	mTypeItem->SetDescriptor(theType);
	::NumToString(inRezInfoPtr->size, theString);
	mSizeItem->SetDescriptor(theString);
	::NumToString(inRezInfoPtr->id, theString);
	mIDItem->SetDescriptor(theString);

	// Editable texts
	mNameEdit->SetDescriptor(inRezInfoPtr->name);
	::NumToString(inRezInfoPtr->id,theString);
	mIDEdit->SetDescriptor(theString);

	// Check boxes
	mSysHeapItem->SetValue(inRezInfoPtr->sysheap);
	mPurgeableItem->SetValue(inRezInfoPtr->purge);
	mLockedItem->SetValue(inRezInfoPtr->lock);
	mProtectedItem->SetValue(inRezInfoPtr->protect);
	mPreloadItem->SetValue(inRezInfoPtr->preload);
	mCompressedItem->SetValue(inRezInfoPtr->compress);
	
	// Icon
	// To use PlotIconID(), the icon resource must be of resource type 
	// 'ICN#', 'ics#', 'icl4', 'icl8', 'ics4', or 'ics8'.
	mIconItem->SetIconID(inRezInfoPtr->id);
	if ( ! ::strncmp( (const char *) theType + 1, "ics8", 4)
		|| ! ::strncmp( (const char *) theType + 1, "ics4", 4)
		|| ! ::strncmp( (const char *) theType + 1, "icl8", 4)
		|| ! ::strncmp( (const char *) theType + 1, "icl4", 4)
		|| ! ::strncmp( (const char *) theType + 1, "ics#", 4)
		|| ! ::strncmp( (const char *) theType + 1, "ICN#", 4) ) {
		mIconItem->SetCurrentRefNum(inRezInfoPtr->refnum);
		mIconItem->SetVisibleState(triState_Off);
		mIconItem->Show();
	} else {
		mIconItem->SetCurrentRefNum(UResources::refNum_Undef);
		mIconItem->Hide();
	}
	
	// Disable the buttons
	mRevertButton->Disable();
	mModifyButton->Disable();
	
	if (mRezObjItem == nil) {
		return;
	} 
	LStaticText * theStaticText = dynamic_cast<LStaticText *>(this->FindPaneByID( item_InspMapName ));
	ThrowIfNil_( theStaticText );
	mRezObjItem->GetOwnerRezMapTable()->GetOwnerWindow()->GetDescriptor(theString);
	theStaticText->SetDescriptor(theString);
}


// ---------------------------------------------------------------------------
//	¥ RetrieveOptions											[protected]
// ---------------------------------------------------------------------------

void
CInspectorWindow::RetrieveValues()
{
	RetrieveValues(mSavedRezInfo);
}


// ---------------------------------------------------------------------------
//	¥ RetrieveOptions											[protected]
// ---------------------------------------------------------------------------

void
CInspectorWindow::RetrieveValues(SResourceObjInfo & outRezInfo)
{
	Str255		theString;
	char * theType = new char[5];

	// Static texts
	mTypeItem->GetDescriptor(theString);
	UMiscUtils::PStringToOSType(theString, outRezInfo.type);	
	mSizeItem->GetDescriptor(theString);
	::StringToNum(theString,&outRezInfo.size);
	mIDItem->GetDescriptor(theString);
	::StringToNum(theString,&outRezInfo.id);

	// Editable texts
	mNameEdit->GetDescriptor(outRezInfo.name);
	mIDEdit->GetDescriptor(theString);
	::StringToNum(theString,&outRezInfo.id);

	// Check boxes
	outRezInfo.sysheap	= mSysHeapItem->GetValue();
	outRezInfo.purge	= mPurgeableItem->GetValue();
	outRezInfo.lock		= mLockedItem->GetValue();
	outRezInfo.protect	= mProtectedItem->GetValue();
	outRezInfo.preload	= mPreloadItem->GetValue();
	outRezInfo.compress	= mCompressedItem->GetValue();
}


// ---------------------------------------------------------------------------
//	¥ UpdateRezObj											[private]
// ---------------------------------------------------------------------------

void
CInspectorWindow::UpdateRezObj()
{
	CRezObj * theRezObj = mRezObjItem->GetRezObj();
	theRezObj->SetID(mSavedRezInfo.id);
	theRezObj->SetName(&mSavedRezInfo.name);
	OSErr error = theRezObj->SetInfoInMap();

	short theAttrs = 0;
	theRezObj->GetAttributesFromMap(theAttrs);
	// Modify the mAttributes data member
	theRezObj->SetOneAttribute(resLocked, mSavedRezInfo.lock);
	theRezObj->SetOneAttribute(resPreload, mSavedRezInfo.preload);
	theRezObj->SetOneAttribute(resProtected, mSavedRezInfo.protect);
	theRezObj->SetOneAttribute(resPurgeable, mSavedRezInfo.purge);
	theRezObj->SetOneAttribute(resSysHeap, mSavedRezInfo.sysheap);
	// Put the value in the rezmap
	error = theRezObj->SetAttributes( theRezObj->GetAttributes() );
	error = theRezObj->Changed();
}

	
// ---------------------------------------------------------------------------
//	¥ ClearValues											[protected]
// ---------------------------------------------------------------------------

void
CInspectorWindow::ClearValues()
{
	// Text fields
	mTypeItem->SetDescriptor("\p");
	mIDItem->SetDescriptor("\p");
	mSizeItem->SetDescriptor("\p");
	mNameEdit->SetDescriptor("\p");
	mIDEdit->SetDescriptor("\p");

	// Check boxes
	mSysHeapItem->SetValue(0);
	mPurgeableItem->SetValue(0);
	mLockedItem->SetValue(0);
	mProtectedItem->SetValue(0);
	mPreloadItem->SetValue(0);
	mCompressedItem->SetValue(0);
	
	// Icon
	mIconItem->Hide();

	// Invalidate the reference to the associated RezObjItem
	mRezObjItem = nil;
}


