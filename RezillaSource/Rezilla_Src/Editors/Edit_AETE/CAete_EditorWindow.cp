// ===========================================================================
// CAete_EditorWindow.cp
// 
//                       Created: 2004-07-01 08:42:37
//             Last modification: 2005-02-19 10:53:33
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2004-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CAete_EditorWindow.h"
#include "CAete_EditorDoc.h"
#include "CRezillaApp.h"
#include "CRezObj.h"
#include "RezillaConstants.h"
#include "UAeteTranslator.h"
#include "UMessageDialogs.h"
#include "UMiscUtils.h"

// PP headers
#include <LPageController.h>
#include <LMultiPanelView.h>
#include <LSlider.h>
#include <LStaticText.h>
#include <LPopupButton.h>
#include <LWindow.h>
#include <LEditText.h>
#include <LEditField.h>
#include <LTextColumn.h>
#include <LTextGroupBox.h>


// Statics
LMenu *		CAete_EditorWindow::sAeteMenu = nil;

Str31	CAete_EditorWindow::sAddEventStr;
Str31	CAete_EditorWindow::sAddClassStr;
Str31	CAete_EditorWindow::sAddCompOpStr;
Str31	CAete_EditorWindow::sAddEnumerationStr;
Str31	CAete_EditorWindow::sRemoveEventStr;
Str31	CAete_EditorWindow::sRemoveClassStr;
Str31	CAete_EditorWindow::sRemoveCompOpStr;
Str31	CAete_EditorWindow::sRemoveEnumerationStr;


// ---------------------------------------------------------------------------
//  CAete_EditorWindow										[public]
// ---------------------------------------------------------------------------

CAete_EditorWindow::CAete_EditorWindow()
		: CEditorWindow()
{
}


// ---------------------------------------------------------------------------
//  CAete_EditorWindow										[public]
// ---------------------------------------------------------------------------

CAete_EditorWindow::CAete_EditorWindow(
	const SWindowInfo &inWindowInfo )
		: CEditorWindow( inWindowInfo )
{
}


// ---------------------------------------------------------------------------
//  CAete_EditorWindow										[public]
// ---------------------------------------------------------------------------

CAete_EditorWindow::CAete_EditorWindow(
	ResIDT		inWINDid,
	UInt32		inAttributes,
	LCommander	*inSuperCommander )
		: CEditorWindow( inWINDid, inAttributes, inSuperCommander )
{
}


// ---------------------------------------------------------------------------
//  CAete_EditorWindow										[public]
// ---------------------------------------------------------------------------

CAete_EditorWindow::CAete_EditorWindow(
			       LStream *inStream )
		: CEditorWindow( inStream )
{
}


// ---------------------------------------------------------------------------
//  ~CAete_EditorWindow										[public]
// ---------------------------------------------------------------------------

CAete_EditorWindow::~CAete_EditorWindow()
{
	if (mAete) {
		delete mAete;
	} 
	
	RemoveAeteMenu();
}


// ---------------------------------------------------------------------------
//  FinishCreateSelf											[protected]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::FinishCreateSelf()
{    
	mAete = nil;
	mIgnoreSliderMessage = false;
	mCurrentPanel = mpv_AeteEvent;
	
	mSuitesPopup = dynamic_cast<LPopupButton *>(this->FindPaneByID( item_AeteSuitePopup ));
	ThrowIfNil_( mSuitesPopup );
	
	LPageController * theController = dynamic_cast<LPageController *>(this->FindPaneByID( item_AetePanelController ));
	ThrowIfNil_( theController );
			
	LMultiPanelView * theMultiPanel = dynamic_cast<LMultiPanelView *>(this->FindPaneByID( item_AeteMultiPanelView ));
	ThrowIfNil_( theMultiPanel );
	
	// Create the panels before we call them
	theMultiPanel->CreateAllPanels();
	
	mEventPane = theMultiPanel->GetPanel(mpv_AeteEvent);
	ThrowIfNil_(mEventPane);
	
	mClassPane = theMultiPanel->GetPanel(mpv_AeteClass);
	ThrowIfNil_(mClassPane);
	
	mCompOpPane = theMultiPanel->GetPanel(mpv_AeteCompOp);
	ThrowIfNil_(mCompOpPane);
	
	mEnumerationPane = theMultiPanel->GetPanel(mpv_AeteEnum);
	ThrowIfNil_(mEnumerationPane);
		
	// Edit menu strings. Load these once only.
	if ( sAddEventStr[0] == 0 )
	{
		::GetIndString(sAddEventStr, STRx_AeteAdd, kind_AeteEvent);
		::GetIndString(sAddClassStr, STRx_AeteAdd, kind_AeteClass);
		::GetIndString(sAddCompOpStr, STRx_AeteAdd, kind_AeteCompOp);
		::GetIndString(sAddEnumerationStr, STRx_AeteAdd, kind_AeteEnum);
		::GetIndString(sRemoveEventStr, STRx_AeteRemove, kind_AeteEvent);
		::GetIndString(sRemoveClassStr, STRx_AeteRemove, kind_AeteClass);
		::GetIndString(sRemoveCompOpStr, STRx_AeteRemove, kind_AeteCompOp);
		::GetIndString(sRemoveEnumerationStr, STRx_AeteRemove, kind_AeteEnum);
	}

	// Link to the broadcasters. Note that it is very important that the 
	// MultiPanelView be declared _before_ the window so that we switch 
	// panels before our ListenToMessage is called.
	theController->AddListener(theMultiPanel);
	theController->AddListener(this);
	UReanimator::LinkListenerToBroadcasters( this, this, PPob_AeteEditorWindow );
	UReanimator::LinkListenerToBroadcasters( this, mEventPane, PPob_AeteEventPane );
	UReanimator::LinkListenerToBroadcasters( this, mClassPane, PPob_AeteClassPane );
	UReanimator::LinkListenerToBroadcasters( this, mCompOpPane, PPob_AeteCompOpPane );
	UReanimator::LinkListenerToBroadcasters( this, mEnumerationPane, PPob_AeteEnumPane );
}


// ---------------------------------------------------------------------------
//  FindCommandStatus
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::FindCommandStatus(
	CommandT	inCommand,
	Boolean		&outEnabled,
	Boolean		&outUsesMark,
	UInt16		&outMark,
	Str255		outName)
{
	CAeteSuite * theSuite = static_cast<CAeteSuite *>( FindCurrentObject( kind_AeteSuite ) );

	switch (inCommand) {
		case cmd_AeteAddSuite:
		outEnabled = true;
		break;

		case cmd_AeteRemoveSuite:
		outEnabled = (mAete->CountSuites() > 0);
		break;

		case cmd_AeteAddItem:
		switch (mCurrentPanel) {
			case mpv_AeteEvent:
			LString::CopyPStr( sAddEventStr, outName );
			break;
			
			case mpv_AeteClass:
			LString::CopyPStr( sAddClassStr, outName );
			break;
			
			case mpv_AeteCompOp:
			LString::CopyPStr( sAddCompOpStr, outName );
			break;
			
			case mpv_AeteEnum:
			LString::CopyPStr( sAddEnumerationStr, outName );
			break;
		}	
		outEnabled = (theSuite != nil);
		break;

		case cmd_AeteRemoveItem:
		switch (mCurrentPanel) {
			case mpv_AeteEvent:
			LString::CopyPStr( sRemoveEventStr, outName );
			outEnabled = ( theSuite && theSuite->CountEvents() > 0 );
			break;
			
			case mpv_AeteClass:
			LString::CopyPStr( sRemoveClassStr, outName );
			outEnabled = ( theSuite && theSuite->CountClasses() > 0 );
			break;
			
			case mpv_AeteCompOp:
			LString::CopyPStr( sRemoveCompOpStr, outName );
			outEnabled = ( theSuite && theSuite->CountCompOps() > 0 );
			break;
			
			case mpv_AeteEnum:
			LString::CopyPStr( sRemoveEnumerationStr, outName );
			outEnabled = ( theSuite && theSuite->CountEnumerations() > 0 );
			break;
		}	
		break;

		case cmd_AeteAddParameter:
		outEnabled = (mCurrentPanel == mpv_AeteEvent
			&& theSuite && theSuite->CountEvents() > 0);
		break;

		case cmd_AeteRemoveParameter:
		if (mCurrentPanel != mpv_AeteEvent 
			|| (theSuite && theSuite->CountEvents() == 0)) {
			outEnabled = false;
		} else {
			CAeteEvent * theEvent = static_cast<CAeteEvent *>( FindCurrentObject( kind_AeteEvent ) );
			outEnabled = (theEvent && theEvent->CountParameters() > 0);
		}
		break;

		case cmd_AeteAddProperty:
		outEnabled = (mCurrentPanel == mpv_AeteClass
			&& theSuite && theSuite->CountClasses() > 0);
		break;

		case cmd_AeteRemoveProperty:
		if (mCurrentPanel != mpv_AeteClass
			|| (theSuite && theSuite->CountClasses() == 0)) {
			outEnabled = false;
		} else {
			CAeteClass * theClass = static_cast<CAeteClass *>( FindCurrentObject( kind_AeteClass ) );
			outEnabled = (theClass && theClass->CountProperties() > 0);
		}
		break;

		case cmd_AeteAddElement:
		outEnabled = (mCurrentPanel == mpv_AeteClass
			&& theSuite && theSuite->CountClasses() > 0);
		break;

		case cmd_AeteRemoveElement:
		if (mCurrentPanel != mpv_AeteClass
			|| (theSuite && theSuite->CountClasses() == 0)) {
			outEnabled = false;
		} else {
			CAeteClass * theClass = static_cast<CAeteClass *>( FindCurrentObject( kind_AeteClass ) );
			outEnabled = (theClass && theClass->CountElements() > 0);
		}
		break;

		case cmd_AeteAddKeyForm:
		if (mCurrentPanel != mpv_AeteClass
			|| (theSuite && theSuite->CountClasses() == 0)) {
			outEnabled = false;
		} else {
			CAeteClass * theClass = static_cast<CAeteClass *>( FindCurrentObject( kind_AeteClass ) );
			outEnabled = (theClass && theClass->CountElements() > 0);
		}
		break;

		case cmd_AeteRemoveKeyForm:
		if (mCurrentPanel != mpv_AeteClass
			|| (theSuite && theSuite->CountClasses() == 0)) {
				outEnabled = false;
		} else {
			CAeteClass * theClass = static_cast<CAeteClass *>( FindCurrentObject( kind_AeteClass ) );
			
			if (!theClass || theClass->CountElements() == 0) {
				outEnabled = false;
			} else {
				CAeteElement * theElement = static_cast<CAeteElement *>( FindCurrentObject( kind_AeteElement ) );
				outEnabled = (theElement && theElement->CountKeyForms() > 0);
			}
		}
		break;
			
		case cmd_AeteAddEnumerator:
		outEnabled = (mCurrentPanel == mpv_AeteEnum
			&& theSuite && theSuite->CountEnumerations() > 0);
		break;

		case cmd_AeteRemoveEnumerator:
		if (mCurrentPanel != mpv_AeteEnum
			|| (theSuite && theSuite->CountEnumerations() == 0)) {
			outEnabled = false;
		} else {
			CAeteEnumeration * theEnum = static_cast<CAeteEnumeration *>( FindCurrentObject( kind_AeteEnum ) );
			outEnabled = (theEnum && theEnum->CountEnumerators() > 0);
		}
		break;

		case cmd_AeteExport:
		case cmd_AeteImport:
		outEnabled = true;
		break;

		default:
		CEditorWindow::FindCommandStatus(inCommand, outEnabled,
									  outUsesMark, outMark, outName);
		break;
	}
}


// ---------------------------------------------------------------------------
// 	PutOnDuty
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::PutOnDuty(LCommander *inNewTarget)
{
	LWindow::PutOnDuty(inNewTarget);

	// Put up our menus when on duty
	if ( !sAeteMenu )
	{
		sAeteMenu = new LMenu( MENU_AeteTerminology );
		ThrowIfNil_( sAeteMenu );
	}
	
	// Update the menu bar
	LMenuBar *	theBar = LMenuBar::GetCurrentMenuBar();
	theBar->InstallMenu( sAeteMenu, MENU_OpenedWindows );	
}


// ---------------------------------------------------------------------------
// 	TakeOffDuty
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::TakeOffDuty()
{		
	LWindow::TakeOffDuty();
	RemoveAeteMenu();
}


// ---------------------------------------------------------------------------
// 	RemoveAeteMenu
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::RemoveAeteMenu()
{
	LMenuBar *	theBar = LMenuBar::GetCurrentMenuBar();
	if ( sAeteMenu )
		theBar->RemoveMenu( sAeteMenu );
}


// ---------------------------------------------------------------------------
//  ListenToMessage													[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{
	ArrayIndexT newIndex, oldIndex;
	
	switch (inMessage) {
		
		case msg_EditorModifiedItem:
		SetDirty(true);
		break;
		
		
		case item_AeteSuitePopup:
		newIndex = *(ArrayIndexT *) ioParam;
		oldIndex = GetCurrentIndex(kind_AeteSuite);
		if (newIndex != oldIndex) {
			RetrieveSuiteValues();
			RetrievePanelValues();
			mAete->SetSuiteIndex(newIndex);
			InstallSuiteValues();
			InstallPanelValues();
		} 
		break;
		
		
		case item_AetePanelController:
		newIndex = *(ArrayIndexT *) ioParam;
		if (newIndex != mCurrentPanel) {
			RetrievePanelValues();
			mCurrentPanel = newIndex;
			UpdateSlider(item_AeteItemSlider, GetCurrentIndex(mCurrentPanel), GetCurrentCount(mCurrentPanel), false, true);
			InstallPanelValues();
		}
		break;
		
		
		case msg_AeteDirectOptions:
		case msg_AeteReplyOptions:
		case msg_AeteParamOptions:
		case msg_AetePropertyOptions:
		newIndex = *(ArrayIndexT *) ioParam;
		HandleOptionsPopup(inMessage, newIndex);
		break;

		
		case item_AeteParamSlider:
		case item_AetePropertySlider:
		case item_AeteElementSlider:
		case item_AeteKeyFormSlider:
		case item_AeteEnumSlider:
		newIndex = *(ArrayIndexT *) ioParam;
		HandleSliderMessage(inMessage, newIndex);
		break;
		
		
		case item_AeteItemSlider:
		if (!mIgnoreSliderMessage) {
			newIndex = *(ArrayIndexT *) ioParam;
			HandleSliderMessage(inMessage, newIndex);
		} 
		break;

		
		case msg_AeteSuiteName: {
		Str255		theName;
		LEditText *	theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_AeteSuiteName ));
		ThrowIfNil_( theEditText );
		theEditText->GetDescriptor(theName);
		if (theName[0]) {
			mSuitesPopup->SetMenuItemText(mSuitesPopup->GetCurrentMenuItem(), theName);
		} else {
			mSuitesPopup->SetMenuItemText(mSuitesPopup->GetCurrentMenuItem(), "\punnamed suite");
		}
		mSuitesPopup->Refresh();	
		SetDirty(true);
		break;
		}
		
		default:
		CEditorWindow::ListenToMessage(inMessage, ioParam);
		break;		
		
	}
}


// ---------------------------------------------------------------------------
//  ObeyCommand							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CAete_EditorWindow::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;
		
	if (inCommand == cmd_AeteAddSuite) {
		mAete->AddSuite();
		RebuildSuitePopup();
		mSuitesPopup->SetValue( mAete->CountSuites() );
		SetDirty(true);
	} else if (inCommand == cmd_AeteRemoveSuite) {
		mAete->RemoveSuite( mAete->GetSuiteIndex() );
		mAete->SetSuiteIndex( (mAete->CountSuites() > 0) );	
		InstallSuiteValues();
		InstallPanelValues();
		RebuildSuitePopup();
		SetDirty(true);
	} else {
		SInt32			count;
		
		switch (inCommand) {
			
			case cmd_AeteAddItem:
			case cmd_AeteRemoveItem: {
				CAeteSuite *	theSuite = static_cast<CAeteSuite *>( FindCurrentObject( kind_AeteSuite ) );
				if (!theSuite) { return cmdHandled; }
				if (inCommand == cmd_AeteAddItem) {
					count = theSuite->NewItem(mCurrentPanel);	
					UpdateSlider(item_AeteItemSlider, count, count);
				} else {
					count = theSuite->DeleteItem(mCurrentPanel);	
					UpdateSlider(item_AeteItemSlider, -1, count);
				}
				SetDirty(true);
				break;
			}
			
			
			case cmd_AeteAddParameter:
			case cmd_AeteRemoveParameter: {
				CAeteEvent * theEvent = static_cast<CAeteEvent *>( FindCurrentObject( kind_AeteEvent ) );
				if (!theEvent) { return cmdHandled; }
				if (inCommand == cmd_AeteAddParameter) {
					count = theEvent->NewParameter();
					UpdateSlider(item_AeteParamSlider, count, count);
				} else {
					count = theEvent->DeleteParameter();
					UpdateSlider(item_AeteParamSlider, -1, count);
				}
				SetDirty(true);
				break;
			}
			
			
			case cmd_AeteAddProperty:
			case cmd_AeteRemoveProperty: {
				CAeteClass * theClass = static_cast<CAeteClass *>( FindCurrentObject( kind_AeteClass ) );
				if (!theClass) { return cmdHandled; }
				if (inCommand == cmd_AeteAddProperty) {
					count = theClass->NewProperty();
					UpdateSlider(item_AetePropertySlider, count, count);
				} else {
					count = theClass->DeleteProperty();
					UpdateSlider(item_AetePropertySlider, -1, count);
				}
				SetDirty(true);
				break;
			}
			
			
			case cmd_AeteAddElement:
			case cmd_AeteRemoveElement: {
				CAeteClass * theClass = static_cast<CAeteClass *>( FindCurrentObject( kind_AeteClass ) );
				if (!theClass) { return cmdHandled; }
				if (inCommand == cmd_AeteAddElement) {
					count = theClass->NewElement();
					UpdateSlider(item_AeteElementSlider, count, count);
				} else {
					count = theClass->DeleteElement();
					UpdateSlider(item_AeteElementSlider, -1, count);
				}
				SetDirty(true);
				break;
			}
			
			
			case cmd_AeteAddKeyForm:
			case cmd_AeteRemoveKeyForm: {
				CAeteElement * theElement = static_cast<CAeteElement *>( FindCurrentObject( kind_AeteElement ) );
				if (!theElement) { return cmdHandled; }
				if (inCommand == cmd_AeteAddKeyForm) {
					count = theElement->NewKeyForm();
					UpdateSlider(item_AeteKeyFormSlider, count, count);
				} else {
					count = theElement->DeleteKeyForm();
					UpdateSlider(item_AeteKeyFormSlider, -1, count);
				}
				SetDirty(true);
				break;
			}
			
			
			case cmd_AeteAddEnumerator:
			case cmd_AeteRemoveEnumerator: {
				CAeteEnumeration * theEnum = static_cast<CAeteEnumeration *>( FindCurrentObject( kind_AeteEnum ) );
				if (!theEnum) { return cmdHandled; }
				if (inCommand == cmd_AeteAddEnumerator) {
					count = theEnum->NewEnumerator();
					UpdateSlider(item_AeteEnumSlider, count, count);
				} else {
					count = theEnum->DeleteEnumerator();
					UpdateSlider(item_AeteEnumSlider, -1, count);
				}
				SetDirty(true);
				break;
			}
			
			
			default:
			cmdHandled = CEditorWindow::ObeyCommand(inCommand, ioParam);
			break;
		}
	}
	
	return cmdHandled;
}


// ---------------------------------------------------------------------------
//  InstallAete														[public]
// ---------------------------------------------------------------------------

OSErr
CAete_EditorWindow::InstallAete(Handle inHandle) 
{
	OSErr		error = noErr;
	StHandleLocker lock(inHandle);
	
	CAeteStream * theStream = new CAeteStream(inHandle);
	
	if ( theStream->GetLength() == 0 ) {
		// We are creating a new resource
		mAete = new CAete();
	} else {
		mAete = new CAete(theStream);
	}
	
	// Check that all the data have been parsed
	if (theStream->GetMarker() < theStream->GetLength() ) {
		error = err_MoreDataThanExpected;
	} 
	delete theStream;
	
	if (error == noErr) {
		RebuildSuitePopup();
		InstallResourceInfo();
		InstallSuiteValues();
		InstallPanelValues();
	} 
	
	return error;
}


// ---------------------------------------------------------------------------
//  RetrieveAete														[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::RetrieveAete(CAeteStream * outStream) 
{	
	// Retrieve the current data from the window
	RetrieveResourceInfo();
	RetrieveSuiteValues();
	RetrievePanelValues();
	// Reassemble the resource
	mAete->SendDataToStream(outStream);	
}


// ---------------------------------------------------------------------------
//  RevertContents												  [public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::RevertContents()
{
	if (mAete) {
		delete mAete;
		mAete = nil;
	} 
	mCurrentPanel = mpv_AeteEvent;
	
	CRezObj * theRezObj = mOwnerDoc->GetRezObj();
	// Reinstall the contents
	if (theRezObj != nil) {
		Handle rezData = theRezObj->GetData();
		
		try {
			if (rezData != nil) {
				// Work with a copy of the handle
				::HandToHand(&rezData);
				InstallAete(rezData);
				Refresh();  // Draw(nil);
			} 
		} catch (...) {
			UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("DataParsingException"), PPob_SimpleMessage);
			return;
		}
	} 
	
	SetDirty(false);
}


// ---------------------------------------------------------------------------
//  ImportAete														[public]
// ---------------------------------------------------------------------------

OSErr
CAete_EditorWindow::ImportAete(FSSpec inFSSpec) 
{
	StAeteImporter importer(mAete, inFSSpec);
	
	OSErr error = importer.ReadXml();

	if (error == noErr) {
		RebuildSuitePopup();
		InstallResourceInfo();
		InstallSuiteValues();
		InstallPanelValues();
		SetDirty(true);
	} else {
		UMessageDialogs::DescribeError(CFSTR("ErrorImportingAeteFromXml"), error);
		RevertContents();
	}

	return error;
}


// ---------------------------------------------------------------------------
//  GetCurrentIndex												[public]
// ---------------------------------------------------------------------------

ArrayIndexT
CAete_EditorWindow::GetCurrentIndex(SInt8 inKind)
{	
	ArrayIndexT	index = 0;
	
	switch (inKind) {
		case kind_AeteSuite:
		index = mAete->GetSuiteIndex();
		break;
		
		case kind_AeteEvent: 
		case kind_AeteClass: 
		case kind_AeteCompOp: 
		case kind_AeteEnum: {
			CAeteSuite * theSuite = static_cast<CAeteSuite *>( FindCurrentObject( kind_AeteSuite ) );
			if (theSuite) {
				index = theSuite->GetCurrentIndex(inKind);
			}
			break;
		}
		
		case kind_AeteParameter: {
			CAeteEvent * theEvent = static_cast<CAeteEvent *>( FindCurrentObject( kind_AeteEvent ) );
			if (theEvent) {
				index = theEvent->GetParameterIndex();
			}
			break;
		}
		
		case kind_AeteProperty:
		case kind_AeteElement: {
			CAeteClass * theClass = static_cast<CAeteClass *>( FindCurrentObject( kind_AeteClass ) );
			if (theClass) {
				if (inKind == kind_AeteProperty) {
					index = theClass->GetPropertyIndex();
				} else {
					index = theClass->GetElementIndex();
				} 
			}
			break;
		}
		
		case kind_AeteKeyForm: {
			CAeteElement * theElement = static_cast<CAeteElement *>( FindCurrentObject( kind_AeteElement ) );
			if (theElement) {
				index = theElement->GetKeyFormIndex();
			}
			break;
		}
		
		case kind_AeteEnumerator: {
			CAeteEnumeration * theEnum = static_cast<CAeteEnumeration *>( FindCurrentObject( kind_AeteEnum ) );
			if (theEnum) {
				index = theEnum->GetEnumeratorIndex();
			}
			break;
		}
		
	}
	return index;
}


// ---------------------------------------------------------------------------
//  SetCurrentIndex												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::SetCurrentIndex(SInt8 inKind, ArrayIndexT inIndex)
{
	if (inIndex <= 0) return;
	
	switch (inKind) {
		case kind_AeteEvent: 
		case kind_AeteClass: 
		case kind_AeteCompOp: 
		case kind_AeteEnum: {
			CAeteSuite * theSuite = static_cast<CAeteSuite *>( FindCurrentObject( kind_AeteSuite ) );
			if (theSuite) {
				 theSuite->SetCurrentIndex(inKind, inIndex);
			}
			break;
		}
		
		case kind_AeteParameter: {
			CAeteEvent * theEvent = static_cast<CAeteEvent *>( FindCurrentObject( kind_AeteEvent ) );
			if (theEvent) {
				theEvent->SetParameterIndex(inIndex);
			}
			break;
		}
		
		case kind_AeteProperty:
		case kind_AeteElement: {
			CAeteClass * theClass = static_cast<CAeteClass *>( FindCurrentObject( kind_AeteClass ) );
			if (theClass) {
				if (inKind == kind_AeteProperty) {
					theClass->SetPropertyIndex(inIndex);
				} else {
					theClass->SetElementIndex(inIndex);
				} 
			}
			break;
		}

		case kind_AeteKeyForm: {
			CAeteElement * theElement = static_cast<CAeteElement *>( FindCurrentObject( kind_AeteElement ) );
			if (theElement) {
				theElement->SetKeyFormIndex(inIndex);
			}
			break;
		}

		case kind_AeteEnumerator: {
			CAeteEnumeration * theEnum = static_cast<CAeteEnumeration *>( FindCurrentObject( kind_AeteEnum ) );
			if (theEnum) {
				theEnum->SetEnumeratorIndex(inIndex);
			}
			break;
		}
	}
}


// ---------------------------------------------------------------------------
//  GetCurrentCount												[public]
// ---------------------------------------------------------------------------

SInt32
CAete_EditorWindow::GetCurrentCount(SInt8 inKind)
{	
	SInt32	count = 0;
	
	switch (inKind) {
		case kind_AeteSuite:
		count = mAete->GetSuiteIndex();
		break;
		
		case kind_AeteEvent: 
		case kind_AeteClass: 
		case kind_AeteCompOp: 
		case kind_AeteEnum: {
			CAeteSuite * theSuite = static_cast<CAeteSuite *>( FindCurrentObject( kind_AeteSuite ) );
			if (theSuite) {
				count = theSuite->GetCurrentCount(inKind);
			}
			break;
		}
		
		case kind_AeteParameter: {
			CAeteEvent * theEvent = static_cast<CAeteEvent *>( FindCurrentObject( kind_AeteEvent ) );
			if (theEvent) {
				count = theEvent->CountParameters();
			}
			break;
		}
		
		case kind_AeteProperty:
		case kind_AeteElement: {
			CAeteClass * theClass = static_cast<CAeteClass *>( FindCurrentObject( kind_AeteClass ) );
			if (theClass) {
				if (inKind == kind_AeteProperty) {
					count = theClass->CountProperties();
				} else {
					count = theClass->CountElements();
				} 
			}
			break;
		}

		case kind_AeteKeyForm: {
			CAeteElement * theElement = static_cast<CAeteElement *>( FindCurrentObject( kind_AeteElement ) );
			if (theElement) {
				count = theElement->CountKeyForms();
			}
			break; 
		}
			
		case kind_AeteEnumerator: {
			CAeteEnumeration * theEnum = static_cast<CAeteEnumeration *>( FindCurrentObject( kind_AeteEnum ) );
			if (theEnum) {
				count = theEnum->CountEnumerators();
			}
			break;
		}
	}
	return count;
}


// ---------------------------------------------------------------------------
//  FindCurrentObject												[public]
// ---------------------------------------------------------------------------

void *
CAete_EditorWindow::FindCurrentObject(SInt8 inKind)
{
	void * theObj = NULL;
	CAeteSuite * theSuite;
	
	if (!mAete) return theObj;
	
	ArrayIndexT index = mAete->GetSuiteIndex();
	
	if ( mAete->GetSuites()->FetchItemAt(index, theSuite) ) {
		switch (inKind) {
			case kind_AeteSuite:
			theObj =  (void *) theSuite;
			break;
			
			case kind_AeteEvent:
			case kind_AeteParameter:
			CAeteEvent * theEvent;
			index = theSuite->GetEventIndex();
			if (theSuite->GetEvents()->FetchItemAt(index, theEvent)) {
				switch (inKind) {
					case kind_AeteEvent:
					theObj = (void *) theEvent;
					break;
					
					case kind_AeteParameter:
					CAeteParameter * theParameter;
					index = theEvent->GetParameterIndex();
					if (theEvent->GetParameters()->FetchItemAt(index, theParameter)) {
						theObj = (void *) theParameter;
					} 
					break;	
				}
			} 
			break;
			
			case kind_AeteClass:
			case kind_AeteProperty:
			case kind_AeteElement:
			case kind_AeteKeyForm:
			CAeteClass * theClass;
			index = theSuite->GetClassIndex();
			if (theSuite->GetClasses()->FetchItemAt(index, theClass)) {
				switch (inKind) {
					case kind_AeteClass:
					theObj = (void *) theClass;
					break;
					
					case kind_AeteProperty:
					CAeteProperty * theProperty;
					index = theClass->GetPropertyIndex();
					if (theClass->GetProperties()->FetchItemAt(index, theProperty)) {
						theObj = (void *) theProperty;
					} 
					break;
					
					case kind_AeteElement:
					case kind_AeteKeyForm:
					CAeteElement * theElement;
					index = theClass->GetElementIndex();
					if (inKind == kind_AeteElement
						&& theClass->GetElements()->FetchItemAt(index, theElement)) {
						theObj = (void *) theElement;
					} 
					break;
				}
			} 
			break;
			
			case kind_AeteCompOp:
			CAeteCompOp * theCompOp;
			index = theSuite->GetCompOpIndex();
			if (theSuite->GetCompOps()->FetchItemAt(index, theCompOp)) {
				theObj = (void *) theCompOp;
			} 
			break;
			
			case kind_AeteEnum:
			case kind_AeteEnumerator:
			CAeteEnumeration * theEnum;
			index = theSuite->GetEnumerationIndex();
			if (theSuite->GetEnumerations()->FetchItemAt(index, theEnum)) {
				theObj = (void *) theEnum;
			} 
			break;
			
		}
	} 
	
	return theObj;	
}



#pragma mark -

// ---------------------------------------------------------------------------
//  SetIndicator													[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::SetIndicator(LStaticText * inIndicator, SInt32 inValue, SInt32 inTotal) 
{
	Str255 theString;
	LStr255 theLine("\p");

	::NumToString( inValue, theString);
	theLine.Append(theString);
	if (inTotal) {
		theLine += "\p/";
		::NumToString( inTotal, theString);
		theLine.Append(theString);
	} 
	inIndicator->SetDescriptor(theLine);
}


// ---------------------------------------------------------------------------
//  UpdateSlider													[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::UpdateSlider(SInt32 inSliderID, SInt32 inValue, SInt32 inTotal, 
								 Boolean inOnlyIndicator, Boolean inIgnoreBroadcast)
{
	LSlider *		theSlider = nil;
	LStaticText *	theIndicator = nil;
	LTextGroupBox * theTGB = nil;
	
	switch (inSliderID) {
		case item_AeteItemSlider: 
		theSlider = dynamic_cast<LSlider *>(this->FindPaneByID( inSliderID ));
		theIndicator = dynamic_cast<LStaticText *>(this->FindPaneByID( item_AeteItemIndicator ));
		break;
		
		case item_AeteParamSlider:
		theSlider = dynamic_cast<LSlider *>(mEventPane->FindPaneByID( inSliderID ));
		theIndicator = dynamic_cast<LStaticText *>(mEventPane->FindPaneByID( item_AeteParamIndicator ));
		theTGB = dynamic_cast<LTextGroupBox *>(mEventPane->FindPaneByID( item_AeteParamBox ));
		break;
		
		case item_AetePropertySlider:
		theSlider = dynamic_cast<LSlider *>(mClassPane->FindPaneByID( inSliderID ));
		theIndicator = dynamic_cast<LStaticText *>(mClassPane->FindPaneByID( item_AetePropertyIndicator ));
		theTGB = dynamic_cast<LTextGroupBox *>(mClassPane->FindPaneByID( item_AetePropertyBox ));
		break;
		
		case item_AeteElementSlider:
		theSlider = dynamic_cast<LSlider *>(mClassPane->FindPaneByID( inSliderID ));
		theIndicator = dynamic_cast<LStaticText *>(mClassPane->FindPaneByID( item_AeteElementIndicator ));
		theTGB = dynamic_cast<LTextGroupBox *>(mClassPane->FindPaneByID( item_AeteElementBox ));
		break;
		
		case item_AeteKeyFormSlider:
		theSlider = dynamic_cast<LSlider *>(mClassPane->FindPaneByID( inSliderID ));
		theIndicator = dynamic_cast<LStaticText *>(mClassPane->FindPaneByID( item_AeteKeyFormIndicator ));
		break;
		
		case item_AeteEnumSlider:
		theSlider = dynamic_cast<LSlider *>(mEnumerationPane->FindPaneByID( inSliderID ));
		theIndicator = dynamic_cast<LStaticText *>(mEnumerationPane->FindPaneByID( item_AeteEnumIndicator ));
		theTGB = dynamic_cast<LTextGroupBox *>(mEnumerationPane->FindPaneByID( item_AeteEnumBox ));
		break;
	}
	
	if (!theSlider || !theIndicator) return;
	
	// Set the slider
	if (!inOnlyIndicator) {
		if (inSliderID == item_AeteItemSlider) {
			mIgnoreSliderMessage = inIgnoreBroadcast;
		} 
		theSlider->SetMaxValue(inTotal);
		if ( theSlider->GetMinValue() > 0 ) {
			theSlider->SetMinValue( (inTotal > 0) && (inValue > 0) );
		} 
		if (inValue == -1) {
			// This is the case when an item is removed
			inValue = (inTotal > 0);
			if (theSlider->GetValue() == 1 && inValue == 1) {
				// We removed the first item, so the slider is already
				// positionned on 1. Calling SetValue with value 1 would
				// not broadcast anything and HandleSliderMessage would not
				// be called, so we call it directly here.
				HandleSliderMessage(inSliderID, inValue);
			} else {
				theSlider->SetValue(inValue);
			}
		} else {
			theSlider->SetValue(inValue);
		}		
		if (inValue > 0) {
			theSlider->SetMinValue(1);
		} 
		if (inSliderID == item_AeteItemSlider) {
			mIgnoreSliderMessage = false;
		} 
	} 

	if (inTotal > 1) {
		theSlider->Show();
	} else {
		theSlider->Hide();
	}
	
	// Set the indicator
	if (inTotal == 0) {
		theIndicator->Hide();
		if (theTGB) theTGB->Disable();
	} else {
		SetIndicator(theIndicator, inValue, inTotal);
		theIndicator->Show();
		if (theTGB) theTGB->Enable();
	}
}

