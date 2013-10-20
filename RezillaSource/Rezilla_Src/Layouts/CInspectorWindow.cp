// ===========================================================================
// CInspectorWindow.cp					
// 
//                       Created: 2003-05-02 07:33:10
//             Last modification: 2006-10-09 07:11:36
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2003-2006
// All rights reserved.
// ===========================================================================


#include "CInspectorWindow.h"
#include "RezillaConstants.h"
#include "CRezillaApp.h"
#include "CRezMapDoc.h"
#include "CRezMap.h"
#include "CRezMapWindow.h"
#include "CRezMapTable.h"
#include "CRezObj.h"
#include "CRezObjItem.h"
#include "UMiscUtils.h"
#include "CWindowMenu.h"
#include "UMessageDialogs.h"
#include "UResources.h"

#include <LWindow.h>
#include <LPushButton.h>
#include <LCheckBox.h>
#include <LEditText.h>
#include <LStaticText.h>
#include <UExtractFromAEDesc.h>
#include <UAppleEventsMgr.h>
#include <UCursor.h>

#ifndef __MACH__
#include <AppleHelp.h>
#endif

#include <string.h>

// ---------------------------------------------------------------------------
//   CInspectorWindow				[public]
// ---------------------------------------------------------------------------

CInspectorWindow::CInspectorWindow()
{
	SetModelKind(rzom_cInspWindow);
}


// ---------------------------------------------------------------------------
//   CInspectorWindow				[public]
// ---------------------------------------------------------------------------

CInspectorWindow::CInspectorWindow(
	const SWindowInfo &inWindowInfo )
		: LWindow( inWindowInfo )
{
	SetModelKind(rzom_cInspWindow);
}


// ---------------------------------------------------------------------------
//   CInspectorWindow				[public]
// ---------------------------------------------------------------------------

CInspectorWindow::CInspectorWindow(
	ResIDT		inWINDid,
	UInt32		inAttributes,
	LCommander	*inSuperCommander )
		: LWindow( inWINDid, inAttributes, inSuperCommander )
{
	SetModelKind(rzom_cInspWindow);
}


// ---------------------------------------------------------------------------
//   CInspectorWindow				[public]
// ---------------------------------------------------------------------------

CInspectorWindow::CInspectorWindow(
			       LStream *inStream )
		: LWindow( inStream )
{
	SetModelKind(rzom_cInspWindow);
}


// ---------------------------------------------------------------------------
//     ~CInspectorWindow				[public]
// ---------------------------------------------------------------------------

CInspectorWindow::~CInspectorWindow()
{
}


// ---------------------------------------------------------------------------
//   FinishCreateSelf				[protected]
// ---------------------------------------------------------------------------

void
CInspectorWindow::FinishCreateSelf()
{	
	mOwnerTable = nil;
	InitializeRezInfo();
	
	// Static text
	mTypeField = dynamic_cast<LStaticText *>(this->FindPaneByID( item_InspType ));
	ThrowIfNil_( mTypeField );
		
	mSizeField = dynamic_cast<LStaticText *>(this->FindPaneByID( item_InspSize ));
	ThrowIfNil_( mSizeField );
		
	// Editable text
	mIDField = dynamic_cast<LEditText *>(this->FindPaneByID( item_InspEditID ));
	ThrowIfNil_( mIDField );
		
	mNameField = dynamic_cast<LEditText *>(this->FindPaneByID( item_InspEditName ));
	ThrowIfNil_( mNameField );
		
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
    UReanimator::LinkListenerToControls( this, this, PPob_InspectorWindow );

}


// ---------------------------------------------------------------------------------
//   FindCommandStatus
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
		case cmd_EditWithPlugin:
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
//   ListenToMessage				[public]
// ---------------------------------------------------------------------------

void
CInspectorWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{
#pragma unused( ioParam )
	
	switch (inMessage) {
		
		case msg_InspModify: {
			if (mOwnerTable == nil) {return;} 
			// Update the resource properties in the table and in memory 
			OSErr error = UpdateRezMapTable();
			if (error == noErr) {
				// Store the current values
				RetrieveValues(&mSavedInfo);
				// Disable the buttons
				mRevertButton->Disable();
				mModifyButton->Disable();
			} 
			break;
		}
			
		case msg_InspRevert:
		if (mOwnerTable == nil) {return;} 
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
		this->Hide();
		break;
		
	}
}	


// ---------------------------------------------------------------------------
//   HandleKeyPress
// ---------------------------------------------------------------------------
// ZP feature #7: implement return and enter trigerring the default
// button (code shamelessly copied from LDialogBox)

Boolean
CInspectorWindow::HandleKeyPress(
						   const EventRecord&	inKeyEvent)
{
	Boolean		keyHandled	= true;
	LControl*	keyButton	= nil;
	UInt8		theChar		= (UInt8) (inKeyEvent.message & charCodeMask);

	if ( (theChar == char_Enter) || (theChar == char_Return) ) {
		keyButton = dynamic_cast<LControl*>(mModifyButton);
	}

	if (keyButton != nil) {
		keyButton->SimulateHotSpotClick(kControlButtonPart);
	} else {
		keyHandled = LWindow::HandleKeyPress(inKeyEvent);
	}

	return keyHandled;
}
// End of ZP feature 7


// ---------------------------------------------------------------------------
//   ShowSelf
// ---------------------------------------------------------------------------

void
CInspectorWindow::ShowSelf()
{
	UDesktop::ShowDeskWindow(this);
	// ZP feature #6: give focus to the ID edit text field
	// whenever the inspector window reappears
	SwitchTarget(mIDField);
	// end of ZP feature 6
}


// ---------------------------------------------------------------------------
//   AttemptClose
// ---------------------------------------------------------------------------
//	Try to close the Inspector window as a result of direct user action

void
CInspectorWindow::AttemptClose()
{
	// ZP feature #5: save changes from the inspector when closing it
	// BD: after confirmation...
	if (mOwnerTable != nil && mModifyButton->IsEnabled()) {
		SInt16 	answer = UMessageDialogs::AskYesNoFromLocalizable(CFSTR("AskSaveOnCloseInspector"), PPob_AskYesNoMessage);
		if (answer == answer_Do) {
			this->ListenToMessage(msg_InspModify, NULL);
		} else if (answer == answer_Cancel) {
			return;
		} 
	}
	SendSelfAE(kAECoreSuite, kAEClose, ExecuteAE_No);
	DoClose();
}


// ---------------------------------------------------------------------------
//   DoClose
// ---------------------------------------------------------------------------
//	Close the inspector window: hide it but keep it in memory, then make 
// sure the top window gets the target.

void
CInspectorWindow::DoClose()
{
	Hide();
}


// ---------------------------------------------------------------------------
//   InitializeRezInfo												[private]
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
//   SetSavedInfo												[protected]
// ---------------------------------------------------------------------------

void
CInspectorWindow::SetSavedInfo(SResourceObjInfoPtr inRezInfoPtr)
{
	BlockMoveData(inRezInfoPtr, &mSavedInfo, sizeof(SResourceObjInfo));
}


// ---------------------------------------------------------------------------
//   InstallValues												[public]
// ---------------------------------------------------------------------------

void
CInspectorWindow::InstallValues(CRezObjItem * inRezObjItem)
{
	ThrowIfNil_(inRezObjItem);
	
	mOwnerTable = inRezObjItem->GetOwnerRezMapTable();
	InstallValues(inRezObjItem->GetRezObj());
}


// ---------------------------------------------------------------------------
//   InstallValues												[public]
// ---------------------------------------------------------------------------

void
CInspectorWindow::InstallValues(CRezObj * inRezObj)
{
	ThrowIfNil_(inRezObj);
	
	// Fill the SResourceObjInfo
	mSavedInfo.refnum = inRezObj->GetOwnerRefnum();
	mSavedInfo.type = inRezObj->GetType();
	mSavedInfo.size = inRezObj->GetSize();
	mSavedInfo.id = inRezObj->GetID();
	BlockMoveData(inRezObj->GetName(), &mSavedInfo.name, sizeof(Str255));
	mSavedInfo.iconid = 0;
	mSavedInfo.sysheap = inRezObj->HasAttribute(resSysHeap);
	mSavedInfo.purge = inRezObj->HasAttribute(resPurgeable);
	mSavedInfo.lock = inRezObj->HasAttribute(resLocked);
	mSavedInfo.protect = inRezObj->HasAttribute(resProtected);
	mSavedInfo.preload = inRezObj->HasAttribute(resPreload);

	InstallValues();
}


// ---------------------------------------------------------------------------
//   InstallValues												[public]
// ---------------------------------------------------------------------------

void
CInspectorWindow::InstallValues()
{
	Str255		theString, theType;

	// Static texts
	UMiscUtils::OSTypeToPString(mSavedInfo.type, theType);	
	mTypeField->SetDescriptor(theType);
	::NumToString(mSavedInfo.size, theString);
	mSizeField->SetDescriptor(theString);

	// Editable texts
	mNameField->SetDescriptor(mSavedInfo.name);
	::NumToString(mSavedInfo.id,theString);
	mIDField->SetDescriptor(theString);

	// Check boxes
	mSysHeapItem->SetValue(mSavedInfo.sysheap);
	mPurgeableItem->SetValue(mSavedInfo.purge);
	mLockedItem->SetValue(mSavedInfo.lock);
	mProtectedItem->SetValue(mSavedInfo.protect);
	mPreloadItem->SetValue(mSavedInfo.preload);
	
	// Disable the buttons
	mRevertButton->Disable();
	mModifyButton->Disable();
	
	if (mOwnerTable != nil) {
		// Install the rez map name
		LStaticText * theStaticText = dynamic_cast<LStaticText *>(this->FindPaneByID( item_InspMapName ));
		ThrowIfNil_( theStaticText );
		mOwnerTable->GetOwnerWindow()->GetDescriptor(theString);
		theStaticText->SetDescriptor(theString);
	} 
}


// ---------------------------------------------------------------------------
//   SetValueForAttribute											[public]
// ---------------------------------------------------------------------------

void
CInspectorWindow::SetValueForAttribute(short inFlag, Boolean inState)
{
	LCheckBox * theCheckBox;
	
	switch (inFlag) {
		case resSysHeap:
		theCheckBox = mSysHeapItem;
		break;
		
		case resPurgeable:
		theCheckBox = mPurgeableItem;
		break;
		
		case resLocked:
		theCheckBox = mLockedItem;
		break;
		
		case resProtected:
		theCheckBox = mProtectedItem;
		break;
		
		case resPreload:
		theCheckBox = mPreloadItem;
		break;
		
	}
	theCheckBox->SetValue(inState);
}


// ---------------------------------------------------------------------------
//   RetrieveValues											[protected]
// ---------------------------------------------------------------------------

void
CInspectorWindow::RetrieveValues(SResourceObjInfoPtr inRezInfoPtr)
{
	Str255		theString;
	char *		theType = new char[5];
	SInt32		theLong;
	
	// Static texts
	mTypeField->GetDescriptor(theString);
	UMiscUtils::PStringToOSType(theString, inRezInfoPtr->type);	
	mSizeField->GetDescriptor(theString);
	::StringToNum(theString,&theLong);
	inRezInfoPtr->size = theLong;
	
	// Editable texts
	mNameField->GetDescriptor(inRezInfoPtr->name);
	mIDField->GetDescriptor(theString);
	::StringToNum(theString,&theLong);
	inRezInfoPtr->id = theLong;
	
	// Check boxes
	inRezInfoPtr->sysheap	= mSysHeapItem->GetValue();
	inRezInfoPtr->purge		= mPurgeableItem->GetValue();
	inRezInfoPtr->lock		= mLockedItem->GetValue();
	inRezInfoPtr->protect	= mProtectedItem->GetValue();
	inRezInfoPtr->preload	= mPreloadItem->GetValue();
}


// ---------------------------------------------------------------------------
//   UpdateRezMapTable												[private]
// ---------------------------------------------------------------------------

OSErr
CInspectorWindow::UpdateRezMapTable()
{	
	OSErr				error = noErr;
	short				theAttrs = 0;
	Boolean				applyToOthers = false;
	SResourceObjInfo	currInfo;
	CRezObj *			theRezObj;
	CRezObjItem *		theRezObjItem;
	
	RetrieveValues(&currInfo);
	
	theRezObjItem = mOwnerTable->GetRezObjItem( mSavedInfo.type, mSavedInfo.id, true);
	if (theRezObjItem == NULL) {
		return error;
	} 

	// If the ID has been modified, check that there is not already a
	// resource with the new ID, otherwise cancel the operation
	if (mSavedInfo.id != currInfo.id) {
		if ( mOwnerTable->GetRezMap()->HasResourceWithTypeAndId(mSavedInfo.type, currInfo.id) ) {
			UMessageDialogs::AlertWithValue(CFSTR("ResourceExistsWithID"), currInfo.id);
			return err_AlreadyExistingID;
		} 
	} 
	
	theRezObj = theRezObjItem->GetRezObj();
	Assert_(theRezObj != nil);

	theRezObj->SetID(currInfo.id);
	theRezObj->SetName(&currInfo.name);
	error = theRezObj->SetInfoInMap();

	if (error == noErr) {
		theRezObj->Changed();
		
		// Deal with the attributes
		theAttrs |= currInfo.lock ? resLocked : 0;
		theAttrs |= currInfo.preload ? resPreload : 0;
		theAttrs |= currInfo.protect ? resProtected : 0;
		theAttrs |= currInfo.purge ? resPurgeable : 0;
		theAttrs |= currInfo.sysheap ? resSysHeap : 0;
		// Put the value in the rezmap
		error = theRezObj->SetAttributesInMap(theAttrs);

		// Refresh the rezmap table
		mOwnerTable->Refresh();
		mOwnerTable->GetOwnerDoc()->SetModified(true);

		// Notify a possible picker
		if (mSavedInfo.id != currInfo.id) {
			// Put  the old ID in the low word an d the new ID in the high word
			SInt32 theLong = (currInfo.id << 16) | mSavedInfo.id;
			mOwnerTable->GetOwnerDoc()->NotifyPicker(mSavedInfo.type, msg_RezIDChanged, (void *) theLong);
		}
	} 

	return error;
}

	
// ---------------------------------------------------------------------------
//   UpdateIfNecessary												[public]
// ---------------------------------------------------------------------------
// Updates the values displayed by the inspector if they correspond to the
// given CRezObj

void
CInspectorWindow::UpdateIfNecessary(CRezObj * inRezObj)
{
	ThrowIfNil_(inRezObj);
	
	// Check that it is the same refnum, same type and same ID
	if ( mOwnerTable
		&& inRezObj->GetOwnerRefnum() == mOwnerTable->GetRezMap()->GetRefnum() 
		&& inRezObj->GetType() == mSavedInfo.type
		&& inRezObj->GetID() == mSavedInfo.id ) {
			InstallValues(inRezObj);
	} 
}


// ---------------------------------------------------------------------------
//   ClearIfNecessary												[public]
// ---------------------------------------------------------------------------
// Clear the values displayed by the inspector if they correspond to the
// given CRezObj

void
CInspectorWindow::ClearIfNecessary(CRezObj * inRezObj)
{
	ThrowIfNil_(inRezObj);
	
	// Check that it is the same refnum, same type and same ID
	if ( mOwnerTable 
		&& inRezObj->GetOwnerRefnum() == mOwnerTable->GetRezMap()->GetRefnum() 
		&& inRezObj->GetType() == mSavedInfo.type
		&& inRezObj->GetID() == mSavedInfo.id ) {
			ClearValues();
	} 
}


// ---------------------------------------------------------------------------
//   ClearValues												[protected]
// ---------------------------------------------------------------------------

void
CInspectorWindow::ClearValues()
{
	// Text fields
	mTypeField->SetDescriptor("\p");
	mSizeField->SetDescriptor("\p");
	mNameField->SetDescriptor("\p");
	mIDField->SetDescriptor("\p");

	// Check boxes
	mSysHeapItem->SetValue(0);
	mPurgeableItem->SetValue(0);
	mLockedItem->SetValue(0);
	mProtectedItem->SetValue(0);
	mPreloadItem->SetValue(0);
	
	// Invalidate the reference to the associated RezObjItem
	mOwnerTable = nil;
}


