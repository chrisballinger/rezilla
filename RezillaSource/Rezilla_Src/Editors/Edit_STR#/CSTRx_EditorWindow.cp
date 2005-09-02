// ===========================================================================
// CSTRx_EditorWindow.cp					
// 
//                       Created: 2005-08-31 18:26:24
//             Last modification: 2005-09-01 13:24:20
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CSTRx_EditorDoc.h"
#include "CSTRx_EditorWindow.h"
#include "CIndexedEditField.h"
#include "RezillaConstants.h"
#include "UMessageDialogs.h"
#include "UCompareUtils.h"

#include <LEditText.h>
#include <LStaticText.h>
#include <LPopupButton.h>
#include <LTabGroupView.h>

#include <stdio.h>


// ---------------------------------------------------------------------------
//  CSTRx_EditorWindow				[public]
// ---------------------------------------------------------------------------

CSTRx_EditorWindow::CSTRx_EditorWindow()
{
}


// ---------------------------------------------------------------------------
//  CSTRx_EditorWindow				[public]
// ---------------------------------------------------------------------------

CSTRx_EditorWindow::CSTRx_EditorWindow(
	const SWindowInfo &inWindowInfo )
		: CEditorWindow( inWindowInfo )
{
}


// ---------------------------------------------------------------------------
//  CSTRx_EditorWindow				[public]
// ---------------------------------------------------------------------------

CSTRx_EditorWindow::CSTRx_EditorWindow(
	ResIDT		inWINDid,
	UInt32		inAttributes,
	LCommander	*inSuperCommander )
		: CEditorWindow( inWINDid, inAttributes, inSuperCommander )
{
}


// ---------------------------------------------------------------------------
//  CSTRx_EditorWindow				[public]
// ---------------------------------------------------------------------------

CSTRx_EditorWindow::CSTRx_EditorWindow(
			       LStream *inStream )
		: CEditorWindow( inStream )
{
}


// ---------------------------------------------------------------------------
//  ~CSTRx_EditorWindow				[public]
// ---------------------------------------------------------------------------

CSTRx_EditorWindow::~CSTRx_EditorWindow()
{	
	if (mOutStream != nil) {
		delete mOutStream;
	} 
}


// ---------------------------------------------------------------------------
// FinishCreateSelf											[protected]
// ---------------------------------------------------------------------------

void
CSTRx_EditorWindow::FinishCreateSelf()
{	
	mOutStream = nil;
	mNumItems = 0;
	
	// The main view containing the editing fields
	mContentsView = dynamic_cast<LView *>(this->FindPaneByID(item_EditorContents));
	ThrowIfNil_( mContentsView );

// 	mTGV = dynamic_cast<LTabGroupView *>(this->FindPaneByID( item_TabGroup ));
// 	ThrowIfNil_( mTGV );

	// Link the broadcasters
	UReanimator::LinkListenerToControls( this, this, PPob_MenuEditorWindow );
	
// 	// Listen to the table
// 	mItemsTable->AddListener(this);

}


// ---------------------------------------------------------------------------
//  ListenToMessage													[public]
// ---------------------------------------------------------------------------

void
CSTRx_EditorWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{		
	switch (inMessage) {		
		
// 		case msg_DragMoveAction: 
// 		ArrayIndexT	oldIndex = mMenuObj->GetItemIndex();
// 		ArrayIndexT	newIndex = *(ArrayIndexT *) ioParam;
// 		mMenuObj->GetItems()->MoveItem(oldIndex, newIndex);
// 		mMenuObj->SetItemIndex(newIndex);
// 		SetDirty(true);
// 		break;
		
						
		case msg_MinusButton: {
// 			ArrayIndexT theIndex = mMenuObj->GetItemIndex();
// 			mItemsTable->RemoveSelectedRow();
// 			mMenuObj->RemoveItem(theIndex);
// 			InstallCurrentValues();
// 			mItemsTable->Refresh();
			SetDirty(true);
			break;
		}
				
		case msg_PlusButton: {
			Str255		theString = "\p";
// 			TableCellT	theCell = {0,1};
// 			ArrayIndexT	theIndex = mMenuObj->GetItemIndex();
// 			// Retrieve the currently displayed values
// 			RetrieveItemValues(theIndex);
// 			// Add in the table
// 			mItemsTable->InsertRows(1, theIndex, theString);
// 			theCell.row = theIndex + 1;
// 			mItemsTable->SelectCell(theCell);
// 			// Add in the menu object
// 			mMenuObj->NewItem(theIndex);
// 			mMenuObj->SetItemIndex(theIndex + 1);
// 			ClearItemValues();
// 			mPopup->SetValue(kind_MenuNoProperty);
// 			mItemsTable->Refresh();
			SetDirty(true);
			break;
		}
		

		default:
		dynamic_cast<CSTRx_EditorDoc *>(mOwnerDoc)->ListenToMessage(inMessage, ioParam);
		break;
				
	}
}


// ---------------------------------------------------------------------------
//	 FindCommandStatus
// ---------------------------------------------------------------------------

void
CSTRx_EditorWindow::FindCommandStatus(
	CommandT	inCommand,
	Boolean		&outEnabled,
	Boolean		&outUsesMark,
	UInt16		&outMark,
	Str255		outName)
{
	switch (inCommand) {
		
		default:
		CEditorWindow::FindCommandStatus(inCommand, outEnabled,
									  outUsesMark, outMark, outName);
		break;
	}
}


// ---------------------------------------------------------------------------
//	 ObeyCommand							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CSTRx_EditorWindow::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;
	
	switch (inCommand) {

		default:
			cmdHandled = LCommander::ObeyCommand(inCommand, ioParam);
			break;
	}

	return cmdHandled;
}


// ---------------------------------------------------------------------------
//	 InstallResourceData											[public]
// ---------------------------------------------------------------------------

OSErr
CSTRx_EditorWindow::InstallResourceData(Handle inHandle)
{
	OSErr		error = noErr, ignoreErr = noErr;
	StHandleLocker	locker(inHandle);
	
	LHandleStream * theStream = new LHandleStream(inHandle);
	
	if ( theStream->GetLength() == 0 ) {
		// We are creating a new resource
	} else {
		*theStream >> mNumItems;
		
		for (UInt16 i = 0; i < mNumItems; i++) {
			Str255		theString;
			if ( theStream->GetMarker() < theStream->GetLength() ) {
				*theStream >> theString;
				AddStringItem(i, theString);
			}
		}
		
		// Check that all the data have been parsed
		if ( theStream->GetMarker() < theStream->GetLength() ) {
			error = err_MoreDataThanExpected;
		} 
	}
	
	delete theStream;
	
	if (error == noErr) {
		// Adjust the size of the image
		mContentsView->ResizeImageTo(0, mNumItems * kStrxHeight, false);
		SetDirty(false);
	} 
	
	return error;
}


// ---------------------------------------------------------------------------
//  AddStringItem												  [public]
// ---------------------------------------------------------------------------

void
CSTRx_EditorWindow::AddStringItem(UInt16 index, Str255 inString)
{
	SPaneInfo		pi;
	SViewInfo		vi;
	SDimension16	frameSize;

	mContentsView->GetFrameSize(frameSize);

	// View info
	vi.imageSize.width		= vi.imageSize.height	= 0 ;
	vi.scrollPos.h			= vi.scrollPos.v		= 0;
	vi.scrollUnit.h			= vi.scrollUnit.v		= 1;
	vi.reconcileOverhang	= false;
	
	// Pane info
	pi.left				= 0;
	pi.top				= index * kStrxHeight;
	pi.width			= frameSize.width;
	pi.height			= kStrxHeight;
	pi.visible			= true;
	pi.enabled			= true;
	pi.bindings.left	= true;
	pi.bindings.top		= false;
	pi.bindings.right	= true;
	pi.bindings.bottom 	= false;
	pi.userCon			= 0;
	pi.paneID			= 0;
	pi.superView		= mContentsView;
	
	CIndexedEditField * theEdit = new CIndexedEditField(pi, vi, index, inString);
	
}


// ---------------------------------------------------------------------------
//  RevertContents												  [public]
// ---------------------------------------------------------------------------

void
CSTRx_EditorWindow::RevertContents()
{
	OSErr error = noErr;
	
// 	// Reinitialize members
// 	mNeedsXmnu = false;
// 	mInstallValue = false;
// 	if (mOutStream != nil) {
// 		delete mOutStream;
// 	} 
// 	if (mMenuObj != nil) {
// 		delete mMenuObj;
// 		mMenuObj = nil;
// 	} 
// 
// 	// Remove the items from the table
// 	TableIndexT	theRows, theCols;
// 	mItemsTable->GetTableSize(theRows, theCols);
// 	mItemsTable->RemoveRows(theRows, 1);
// 
// 	CRezObj * theRezObj = mOwnerDoc->GetRezObj();
// 	// Reinstall the contents
// 	if (theRezObj != nil) {
// 		Handle rezData = theRezObj->GetData();
// 		
// 		try {
// 			if (rezData != nil) {
// 				Handle		xmnuData = NULL;
// 				CRezMap *	theRezMap = mOwnerDoc->GetRezMapTable()->GetRezMap();
// 				
// 				if (mHasXmnu) {
// 					theRezMap->GetWithID(ResType_ExtendedMenu, theRezObj->GetID(), xmnuData, true);
// 					if (xmnuData != nil) {
// 						::HandToHand(&xmnuData);
// 					} 
// 				} 
// 				
// 				// Work with a copy of the handle
// 				::HandToHand(&rezData);
// 				error = InstallResourceData(rezData, xmnuData);			
// 			} 
// 			ThrowIfError_(error);			
// 		} catch (...) {
// 			UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("DataParsingException"), PPob_SimpleMessage);
// 			return;
// 		}
// 	} 
	
	Refresh();
	SetDirty(false);
}

