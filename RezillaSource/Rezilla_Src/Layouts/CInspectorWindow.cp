// ===========================================================================
// CInspectorWindow.cp					
// 
//                       Created: 2003-05-02 07:33:10
//             Last modification: 2005-06-16 09:09:45
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2003-2005
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
#include "CRezIconPane.h"
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

#include <AppleHelp.h>

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
	mRezObjItem = nil;
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
			if (mRezObjItem == nil) {return;} 
			// Update the resource properties in the table and in memory 
			OSErr err = UpdateRezMapTable();
			if (err == noErr) {
				SaveValues();
				// Disable the buttons
				mRevertButton->Disable();
				mModifyButton->Disable();
			} 
			break;
		}
			
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
//   ShowSelf
// ---------------------------------------------------------------------------

void
CInspectorWindow::ShowSelf()
{
	UDesktop::ShowDeskWindow(this);
}


// ---------------------------------------------------------------------------
//   AttemptClose
// ---------------------------------------------------------------------------
//	Try to close a Window as a result of direct user action

void
CInspectorWindow::AttemptClose()
{
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
	
	mRezObjItem = inRezObjItem;
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
	BlockMoveData(inRezObj->GetName(),&mSavedInfo.name,sizeof(Str255));
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
	
	// Icon pane
	// To use PlotIconID(), the icon resource must be of type 
	// 'ICN#', 'icl4', 'icl8', 'icm#', 'icm4', 'icm8', 'ics#', 'ics4', or 'ics8'.
	mIconItem->SetIconID(mSavedInfo.id);
	
	switch (mSavedInfo.type) {
		case 'ICN#':
		case 'icl4':
		case 'icl8':
		case 'icm#':
		case 'icm4':
		case 'icm8':
		case 'ics#':
		case 'ics4':
		case 'ics8':
		mIconItem->SetCurrentRefNum(mSavedInfo.refnum);
		mIconItem->SetVisibleState(triState_Off);
		mIconItem->Show();
		break;
		
		// 	case 'crsr':
		// 	case 'cicn':
		// 	case 'ICON':
		// 	case 'PAT ':

		default:
		mIconItem->SetCurrentRefNum(UResources::refNum_Undef);
		mIconItem->Hide();
		break;
		
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
//   SaveValues											[protected]
// ---------------------------------------------------------------------------

void
CInspectorWindow::SaveValues()
{
	RetrieveValues(&mSavedInfo);
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
//   UpdateRezMapTable											[private]
// ---------------------------------------------------------------------------

OSErr
CInspectorWindow::UpdateRezMapTable()
{
	Assert_(mRezObjItem != nil);
	
	OSErr				error = noErr;
	short				theAttrs = 0;
	Boolean				applyToOthers = false;
	SResourceObjInfo	currInfo;
	
	RetrieveValues(&currInfo);
	
	CRezMapTable *		theTable = mRezObjItem->GetOwnerRezMapTable();
	CRezObj *			theRezObj = mRezObjItem->GetRezObj();
	ResType				theType = theRezObj->GetType();
	
	// If the ID has been modified
	if (theRezObj->GetID() != currInfo.id) {
		CRezObjItem * theRezObjItem = theTable->GetRezObjItem( theType, currInfo.id, true);
		if (theRezObjItem != nil) {
			// There is already a resource with the new ID, cancel the operation
			UMessageDialogs::AlertWithValue(CFSTR("ResourceExistsWithID"), currInfo.id);
			return err_AlreadyExistingID;
		} 
	} 
	
	theRezObj->SetID(currInfo.id);
	theRezObj->SetName(&currInfo.name);
	error = theRezObj->SetInfoInMap();

	if (error == noErr) {
		// Deal with the attributes
		theAttrs |= currInfo.lock ? resLocked : 0;
		theAttrs |= currInfo.preload ? resPreload : 0;
		theAttrs |= currInfo.protect ? resProtected : 0;
		theAttrs |= currInfo.purge ? resPurgeable : 0;
		theAttrs |= currInfo.sysheap ? resSysHeap : 0;
		// Put the value in the rezmap
		error = theRezObj->SetAttributesInMap(theAttrs);
		if (error == noErr) {
			theRezObj->Changed();
			
			// Refresh the rezmap table
			theTable->Refresh();
			theTable->GetOwnerDoc()->SetModified(true);
		} 
	} 

	return error;
}

	
// ---------------------------------------------------------------------------
//   ClearValues											[protected]
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
	
	// Icon
	mIconItem->Hide();

	// Invalidate the reference to the associated RezObjItem
	mRezObjItem = nil;
}


