// ===========================================================================
// CAete_EditorWindow.cp
// 
//                       Created: 2004-07-01 08:42:37
//             Last modification: 2005-01-24 14:47:09
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
#include "RezillaConstants.h"
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
}


// ---------------------------------------------------------------------------
//  FinishCreateSelf											[protected]
// ---------------------------------------------------------------------------
// 	ListHandle theListH = mCategoriesListBox->GetMacListH();
// 	Cell theCell = {0,0};
// 	::LAddColumn(1, 0, theListH);
// 	for (SInt16 theIndex = 0; theIndex < 4; theIndex++) {
// 		::LAddRow(1,theCell.v,theListH);
// 		++theCell.v;
// 	}
// 
// 	// Build the table elements
// 	mDictTermsTable = dynamic_cast<CBroadcasterTableView *> (mAeteEditWindow->FindPaneByID( item_AeteTermsTable ));
// 	ThrowIfNil_( mDictTermsTable );
// 	
// 	// Set Geometry and Selector TableView members.
// 	mDictTermsTable->SetTableGeometry(new LTableMonoGeometry(mDictTermsTable, kAeteTableWidth, kAeteTableHeight));
// 	mDictTermsTable->SetTableSelector(new LTableSingleSelector(mDictTermsTable));
// 	mDictTermsTable->SetTableStorage(new LTableArrayStorage(mDictTermsTable, sizeof(Str255)));
// 
// 	mDictTermsTable->InsertCols(1, 0);

void
CAete_EditorWindow::FinishCreateSelf()
{    
	mAete = nil;
	mCurrentPanel = mpv_AeteEvent;
	
	mSuitesPopup = dynamic_cast<LPopupButton *> (this->FindPaneByID( item_AeteSuitePopup ));
	ThrowIfNil_( mSuitesPopup );
	
	mController = dynamic_cast<LPageController *> (this->FindPaneByID( item_AetePanelController ));
	ThrowIfNil_( mController );
			
	mMultiPanel = dynamic_cast<LMultiPanelView *> (this->FindPaneByID( item_AeteMultiPanelView ));
	ThrowIfNil_( mMultiPanel );
	
	// Create the panels before we call them
	mMultiPanel->CreateAllPanels();
// 	mMultiPanel->SwitchToPanel(1);
	
	mEventPane = mMultiPanel->GetPanel(mpv_AeteEvent);
	ThrowIfNil_(mEventPane);
	
	mClassPane = mMultiPanel->GetPanel(mpv_AeteClass);
	ThrowIfNil_(mClassPane);
	
	mCompOpPane = mMultiPanel->GetPanel(mpv_AeteCompOp);
	ThrowIfNil_(mCompOpPane);
	
	mEnumerationPane = mMultiPanel->GetPanel(mpv_AeteEnum);
	ThrowIfNil_(mEnumerationPane);
		
	// Link the broadcasters
	UReanimator::LinkListenerToControls( this, this, PPob_AeteEditorWindow );
	mController->AddListener(mMultiPanel);
	mController->AddListener(this);

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

// 	// Make the DictDoc a listener of mCategoriesListBox
// 	mCategoriesListBox->AddListener(this);
// 	mDictTermsTable->AddListener(this);
	
// 	mAeteStreamsArrayPtr = new TArray<CAeteStream*>();

//     SwitchTarget(mContentsView);
}


// ---------------------------------------------------------------------------
//	¥ FindCommandStatus
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

	if (!theSuite) {
		outEnabled = (inCommand == cmd_AeteAddSuite);
		outUsesMark = false;
		outMark = 0;
		outName[0] = 0;
	} else {
		switch (inCommand) {
			case cmd_AeteAddSuite:
			outEnabled = true;
			break;

			case cmd_AeteRemoveSuite:
			outEnabled = (mAete->GetSuites()->GetCount() > 0);
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
			outEnabled = true;
			break;

			case cmd_AeteRemoveItem:
			switch (mCurrentPanel) {
				case mpv_AeteEvent:
				LString::CopyPStr( sRemoveEventStr, outName );
				outEnabled = ( theSuite->GetEvents()->GetCount() > 0 );
				break;
				
				case mpv_AeteClass:
				LString::CopyPStr( sRemoveClassStr, outName );
				outEnabled = ( theSuite->GetClasses()->GetCount() > 0 );
				break;
				
				case mpv_AeteCompOp:
				LString::CopyPStr( sRemoveCompOpStr, outName );
				outEnabled = ( theSuite->GetCompOperators()->GetCount() > 0 );
				break;
				
				case mpv_AeteEnum:
				LString::CopyPStr( sRemoveEnumerationStr, outName );
				outEnabled = ( theSuite->GetEnumerations()->GetCount() > 0 );
				break;
			}	
			break;

			case cmd_AeteAddParameter:
			outEnabled = (mCurrentPanel == mpv_AeteEvent);
			break;

			case cmd_AeteRemoveParameter:
			if (mCurrentPanel != mpv_AeteEvent 
				|| theSuite->GetEvents()->GetCount() == 0) {
				outEnabled = false;
			} else {
				CAeteEvent * theEvent = static_cast<CAeteEvent *>( FindCurrentObject( kind_AeteEvent ) );
				outEnabled = (theEvent && theEvent->GetParameters()->GetCount() > 0);
			}
			break;

			case cmd_AeteAddProperty:
			outEnabled = (mCurrentPanel == mpv_AeteClass);
			break;

			case cmd_AeteRemoveProperty:
			if (mCurrentPanel != mpv_AeteClass
				|| theSuite->GetClasses()->GetCount() == 0) {
				outEnabled = false;
			} else {
				CAeteClass * theClass = static_cast<CAeteClass *>( FindCurrentObject( kind_AeteClass ) );
				outEnabled = (theClass && theClass->GetProperties()->GetCount() > 0);
			}
			break;

			case cmd_AeteAddElement:
			outEnabled = (mCurrentPanel == mpv_AeteClass);
			break;

			case cmd_AeteRemoveElement:
			if (mCurrentPanel != mpv_AeteClass
				|| theSuite->GetClasses()->GetCount() == 0) {
				outEnabled = false;
			} else {
				CAeteClass * theClass = static_cast<CAeteClass *>( FindCurrentObject( kind_AeteClass ) );
				outEnabled = (theClass && theClass->GetElements()->GetCount() > 0);
			}
			break;

			case cmd_AeteAddKeyForm:
			if (mCurrentPanel != mpv_AeteClass
				|| theSuite->GetClasses()->GetCount() == 0) {
				outEnabled = false;
			} else {
				CAeteClass * theClass = static_cast<CAeteClass *>( FindCurrentObject( kind_AeteClass ) );
				outEnabled = (theClass && theClass->GetElements()->GetCount() > 0);
			}
			break;

			case cmd_AeteRemoveKeyForm:
			if (mCurrentPanel != mpv_AeteClass
				|| theSuite->GetClasses()->GetCount() == 0) {
					outEnabled = false;
			} else {
				CAeteClass * theClass = static_cast<CAeteClass *>( FindCurrentObject( kind_AeteClass ) );
				
				if (!theClass || theClass->GetElements()->GetCount() == 0) {
					outEnabled = false;
				} else {
					CAeteElement * theElement = static_cast<CAeteElement *>( FindCurrentObject( kind_AeteElement ) );
					outEnabled = (theElement && theElement->GetKeyForms()->GetCount() > 0);
				}
			}
			break;
				
			case cmd_AeteAddEnumerator:
			outEnabled = (mCurrentPanel == mpv_AeteEnum);
			break;

			case cmd_AeteRemoveEnumerator:
			if (mCurrentPanel != mpv_AeteEnum
				|| theSuite->GetClasses()->GetCount() == 0) {
				outEnabled = false;
			} else {
				CAeteEnumeration * theEnum = static_cast<CAeteEnumeration *>( FindCurrentObject( kind_AeteEnum ) );
				outEnabled = (theEnum && theEnum->GetEnumerators()->GetCount() > 0);
			}
			break;

	// 		case cmd_AeteImport:
	// 		break;

			case cmd_AeteExport:
			outEnabled = true;
			break;

			default:
			CEditorWindow::FindCommandStatus(inCommand, outEnabled,
										  outUsesMark, outMark, outName);
			break;
		}
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
	
	LMenuBar *	theBar = LMenuBar::GetCurrentMenuBar();
	if ( sAeteMenu )
		theBar->RemoveMenu( sAeteMenu );
}


// ---------------------------------------------------------------------------
//  ListenToMessage										[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{
	SInt32 index;
	
	switch (inMessage) {
		
		case item_AeteSuitePopup:
		index = mSuitesPopup->GetValue();
		if (index > 0) {
			mAete->SetSuiteIndex(index);
			InstallSuiteInfo();
			InstallPanelValues();
		} 
		break;
		
		case item_AetePanelController:
		index = *(SInt32 *) ioParam;
		RetrievePanelValues();
		mCurrentPanel = index;
		InstallPanelValues();
		UpdateSlider(item_AeteItemSlider, 0, 0);
		break;
		
		case item_AeteItemSlider:
		case item_AeteOtherSlider:
		case item_AetePropertySlider:
		case item_AeteElementSlider:
		case item_AeteEnumSlider:
		index = *(SInt32 *) ioParam;
		RetrievePanelValues();
		SetCurrentIndex(inMessage, index);
		InstallPanelValues();
		break;
		
	}
}


// ---------------------------------------------------------------------------
//  InstallAete														[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::InstallAete(Handle inHandle) 
{
	StHandleLocker lock(inHandle);
	
	CAeteStream * theStream = new CAeteStream(inHandle);
	
	mAete = new CAete(theStream);
	delete theStream;
	
	FillSuitePopup();
	InstallResourceInfo();
	InstallSuiteInfo();
	InstallPanelValues();
}


// ---------------------------------------------------------------------------
//  RetrieveAete														[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::RetrieveAete(CAeteStream * outStream) 
{	
	mAete->SendDataToStream(outStream);	
}


// ---------------------------------------------------------------------------
//  FillSuitePopup													[public]
// ---------------------------------------------------------------------------
// Note: LMenuController::AppendMenu() takes care of updating the
// MenuMinMax values whereas a direct call to ToolBox's ::AppendMenu()
// does not.

void
CAete_EditorWindow::FillSuitePopup()
{
	MenuRef    theMenuH = mSuitesPopup->GetMacMenuH();
	ThrowIfNil_(theMenuH);
	
	TArrayIterator<CAeteSuite*>	iterator( *mAete->GetSuites() );
	CAeteSuite *	theSuite;
	Str255			theString;

	while (iterator.Next(theSuite)) {
		theSuite->GetName(theString);
		
		if ( theString[0] ) {
			mSuitesPopup->AppendMenu(theString);
		} else {
			mSuitesPopup->AppendMenu("\p<unnamed suite>");
		}
	}
	mSuitesPopup->SetMacMenuH(theMenuH);
}


// ---------------------------------------------------------------------------
//  SetCurrentIndex												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::SetCurrentIndex(SInt32 inType, SInt32 inIndex)
{
	if (inIndex <= 0) return;
	
	switch (inType) {
		case item_AeteItemSlider: 
		CAeteSuite * theSuite = static_cast<CAeteSuite *>( FindCurrentObject( kind_AeteSuite ) );
		if (theSuite) {
			switch (mCurrentPanel) {
				case mpv_AeteEvent:
				theSuite->SetEventIndex(inIndex);
				break;
				
				case mpv_AeteClass:
				theSuite->SetClassIndex(inIndex);
				break;
				
				case mpv_AeteCompOp:
				theSuite->SetCompOpIndex(inIndex);
				break;
				
				case mpv_AeteEnum:
				theSuite->SetEnumerationIndex(inIndex);
				break;
			}	
		}
		break;
		
		case item_AeteOtherSlider:
		CAeteEvent * theEvent = static_cast<CAeteEvent *>( FindCurrentObject( kind_AeteEvent ) );
		if (theEvent) {
			theEvent->SetParameterIndex(inIndex);
		}
		break;
		
		case item_AetePropertySlider: {
			CAeteClass * theClass = static_cast<CAeteClass *>( FindCurrentObject( kind_AeteClass ) );
			if (theClass) {
				theClass->SetPropertyIndex(inIndex);
			}
			break;
		}
		
		case item_AeteElementSlider: {
			CAeteClass * theClass = static_cast<CAeteClass *>( FindCurrentObject( kind_AeteClass ) );
			if (theClass) {
				theClass->SetElementIndex(inIndex);
			}
			break;
		}
		
		case item_AeteEnumSlider:
		CAeteEnumeration * theEnum = static_cast<CAeteEnumeration *>( FindCurrentObject( kind_AeteEnum ) );
		if (theEnum) {
			theEnum->SetEnumeratorIndex(inIndex);
		}
		break;
		
	}
	
}


// ---------------------------------------------------------------------------
//  FindCurrentObject												[public]
// ---------------------------------------------------------------------------

void *
CAete_EditorWindow::FindCurrentObject(SInt8 inKind)
{
	void * theObj = NULL;
	CAeteSuite * theSuite;
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
				theObj = (void *) theEvent;
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
					if (theClass->GetElements()->FetchItemAt(index, theElement)) {
						theObj = (void *) theElement;
					} 
					break;
				}
			} 
			break;
			
			case kind_AeteCompOp:
			CAeteCompOp * theCompOp;
			index = theSuite->GetCompOpIndex();
			if (theSuite->GetCompOperators()->FetchItemAt(index, theCompOp)) {
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
//  InstallResourceInfo												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::InstallResourceInfo()
{
	Str255	theString;
	UInt8	theMajorVersion, theMinorVersion;
	SInt16	theLanguage, theScript;
	LEditField * theEditField;
	
	mAete->GetValues(theMajorVersion, theMinorVersion, theLanguage, theScript);

	theEditField = dynamic_cast<LEditField *> (this->FindPaneByID( item_AeteMajorVersion ));
	ThrowIfNil_( theEditField );
	::NumToString( theMajorVersion, theString);
	theEditField->SetDescriptor(theString);

	theEditField = dynamic_cast<LEditField *> (this->FindPaneByID( item_AeteMinorVersion ));
	ThrowIfNil_( theEditField );
	::NumToString( theMinorVersion, theString);
	theEditField->SetDescriptor(theString);

	theEditField = dynamic_cast<LEditField *> (this->FindPaneByID( item_AeteLanguageID ));
	ThrowIfNil_( theEditField );
	::NumToString( theLanguage, theString);
	theEditField->SetDescriptor(theString);

	theEditField = dynamic_cast<LEditField *> (this->FindPaneByID( item_AeteScriptCode ));
	ThrowIfNil_( theEditField );
	::NumToString( theScript, theString);
	theEditField->SetDescriptor(theString);
}


// ---------------------------------------------------------------------------
//  InstallSuiteInfo												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::InstallSuiteInfo()
{
	Str255		theString, theName, theDescription;
	UInt16		theLevel = 0, theVersion = 0;
	OSType		theID;
	LEditText *	theEditText;
	Boolean		disableIt;
	
	CAeteSuite * theSuite = static_cast<CAeteSuite *>( FindCurrentObject( kind_AeteSuite ) );
	LTextGroupBox * theTGB = dynamic_cast<LTextGroupBox *> (this->FindPaneByID( item_AeteSuiteBox ));

	if (theSuite) {
		theSuite->GetValues(theName, theDescription, theID, theLevel, theVersion);
		theTGB->Enable();
	} else {
		theString[0] = 0;
		theName[0] = 0;
		theDescription[0] = 0;
		disableIt = true;
		theTGB->Disable();
	}

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteSuiteName ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theName);

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteSuiteDescr ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theDescription);

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteSuiteID ));
	ThrowIfNil_( theEditText );
	if (disableIt) {
		UMiscUtils::OSTypeToPString(theID, theString);
	} 
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteSuiteLevel ));
	ThrowIfNil_( theEditText );
	::NumToString( theLevel, theString);
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteSuiteVersion ));
	ThrowIfNil_( theEditText );
	::NumToString( theVersion, theString);
	theEditText->SetDescriptor(theString);

	// Update the main slider: pass 0, the true values are calculated in 
	// the UpdateSlider function.
	UpdateSlider(item_AeteItemSlider, 0, 0);
}


// ---------------------------------------------------------------------------
//  InstallPanelValues												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::InstallPanelValues()
{
	switch (mCurrentPanel) {
		case mpv_AeteEvent:
		CAeteEvent * theEvent = static_cast<CAeteEvent *>( FindCurrentObject( kind_AeteEvent ) );
		InstallEventValues(theEvent);
		break;
		
		case mpv_AeteClass:
		CAeteClass * theClass = static_cast<CAeteClass *>( FindCurrentObject( kind_AeteClass ) );
		InstallClassValues(theClass);
		break;
		
		case mpv_AeteCompOp:
		CAeteCompOp * theCompOp = static_cast<CAeteCompOp *>( FindCurrentObject( kind_AeteCompOp ) );
		InstallCompOpValues(theCompOp);
		break;
		
		case mpv_AeteEnum:
		CAeteEnumeration * theEnum = static_cast<CAeteEnumeration *>( FindCurrentObject( kind_AeteEnum ) );
		InstallEnumerationValues(theEnum);
		break;
	}	
}


// ---------------------------------------------------------------------------
//  InstallEventValues												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::InstallEventValues(CAeteEvent * inEvent)
{
	Str255			theString;
	Str255 			theName, theDescription, theReplyDescription, theDirectDescription;		
	OSType 			theClass, theID, theReplyType, theDirectType;
	UInt16 			theReplyFlags, theDirectFlags;
	SInt32			theValue, theTotal;
	LEditText *		theEditText;
	LTextGroupBox * theTGB;
	CAeteParameter*	theParameter;
	ArrayIndexT		index;
	Boolean			disableIt = false;
	
	if (inEvent) {
		inEvent->GetValues(theName, theDescription, theClass, theID,
							theReplyType, theReplyDescription, theReplyFlags, 
							theDirectType, theDirectDescription, theDirectFlags);
		index = inEvent->GetParameterIndex();
		mEventPane->Show();
	} else {
		mEventPane->Hide();
	}
	
	theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteEventName ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theName);

	theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteEventDescr ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theDescription);

	theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteEventClass ));
	ThrowIfNil_( theEditText );
	UMiscUtils::OSTypeToPString(theClass, theString);
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteEventID ));
	ThrowIfNil_( theEditText );
	UMiscUtils::OSTypeToPString(theID, theString);
	theEditText->SetDescriptor(theString);

	// Direct parameter
	theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteDirectType ));
	ThrowIfNil_( theEditText );
	UMiscUtils::OSTypeToPString(theDirectType, theString);
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteDirectDescr ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theDirectDescription);

	// Reply
	theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteReplyType ));
	ThrowIfNil_( theEditText );
	UMiscUtils::OSTypeToPString(theReplyType, theString);
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteReplyDescr ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theReplyDescription);
	
	// Current parameter
	theTGB = dynamic_cast<LTextGroupBox *> (mEventPane->FindPaneByID( item_AeteOtherBox ));

	if (inEvent && inEvent->GetParameters()->FetchItemAt(index, theParameter) ) {
		InstallParameterValues(theParameter);
		theTGB->Enable();
		theValue = inEvent->GetParameterIndex();
		theTotal = inEvent->GetParameters()->GetCount();
	} else {
		theTGB->Disable();
		theValue = 0;
		theTotal = 0;
	}
	
	UpdateSlider(item_AeteOtherSlider, theValue, theTotal);	
}


// ---------------------------------------------------------------------------
//  InstallParameterValues												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::InstallParameterValues(CAeteParameter*	inParameter)
{
	Str255			theString;
	Str255 			theName, theDescription;		
	OSType 			theKeyword, theType;
	UInt16 			theFlags;
	LEditText *		theEditText;
	Boolean			disableIt = false;
	
	if (inParameter) {
		inParameter->GetValues(theName, theKeyword, theType,
								theDescription, theFlags);
	} else {
		theString[0] = 0;
		theName[0] = 0;
		theDescription[0] = 0;
		theFlags = 0;
		disableIt = true;
	}
		
	theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteOtherName ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theName);

	theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteOtherKeyword ));
	ThrowIfNil_( theEditText );
	if (!disableIt) {
		UMiscUtils::OSTypeToPString(theKeyword, theString);
	} 
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteOtherType ));
	ThrowIfNil_( theEditText );
	if (!disableIt) {
		UMiscUtils::OSTypeToPString(theType, theString);
	} 
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteOtherDescr ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theDescription);
	
}


// ---------------------------------------------------------------------------
//  InstallClassValues												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::InstallClassValues(CAeteClass * inClass)
{
	Str255			theString;
	Str255 			theName, theDescription;		
	OSType 			theID;
	SInt32			theValue, theTotal;
	LEditText *		theEditText;
	ArrayIndexT		propIndex, elemIndex;
	CAeteProperty *	theProperty;
	CAeteElement *	theElement;
	LTextGroupBox * theTGB;

	if (inClass) {
		inClass->GetValues(theName, theID, theDescription);
		propIndex = inClass->GetPropertyIndex();
		elemIndex = inClass->GetElementIndex();
		mClassPane->Show();
	} else {
		mClassPane->Hide();
	}
		
	theEditText = dynamic_cast<LEditText *> (mClassPane->FindPaneByID( item_AeteClassName ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theName);

	theEditText = dynamic_cast<LEditText *> (mClassPane->FindPaneByID( item_AeteClassID ));
	ThrowIfNil_( theEditText );
	UMiscUtils::OSTypeToPString(theID, theString);
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *> (mClassPane->FindPaneByID( item_AeteClassDescr ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theDescription);

	// Current property
	theTGB = dynamic_cast<LTextGroupBox *> (mClassPane->FindPaneByID( item_AetePropertyBox ));
	
	if (inClass && inClass->GetProperties()->FetchItemAt(propIndex, theProperty) ) {
		InstallPropertyValues(theProperty);
		theTGB->Enable();
		theValue = inClass->GetPropertyIndex();
		theTotal = inClass->GetProperties()->GetCount();
	}  else {
		theTGB->Disable();
		theValue = 0;
		theTotal = 0;
	}
	
	UpdateSlider(item_AetePropertySlider, theValue, theTotal);

	// Current element
	theTGB = dynamic_cast<LTextGroupBox *> (mClassPane->FindPaneByID( item_AeteElementBox ));

	if (inClass && inClass->GetElements()->FetchItemAt(elemIndex, theElement) ) {
		InstallElementValues(theElement);
		theTGB->Enable();
		theValue = inClass->GetElementIndex();
		theTotal = inClass->GetElements()->GetCount();
	}  else {
		theTGB->Disable();
		theValue = 0;
		theTotal = 0;
	}
	
	UpdateSlider(item_AeteElementSlider, theValue, theTotal);

}


// ---------------------------------------------------------------------------
//  InstallPropertyValues											[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::InstallPropertyValues(CAeteProperty *	inProperty)
{
	Str255			theString;
	Str255 			theName, theDescription;		
	OSType 			theKeyword, theType;
	UInt16 			theFlags;
	LEditText *		theEditText;
	Boolean			disableIt = false;
	
	if (inProperty) {
		inProperty->GetValues(theName, theKeyword, theType,
								theDescription, theFlags);
	}  else {
		theString[0] = 0;
		theName[0] = 0;
		theDescription[0] = 0;
		theFlags = 0;
		disableIt = true;
	}
	
	theEditText = dynamic_cast<LEditText *> (mClassPane->FindPaneByID( item_AetePropertyName ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theName);

	theEditText = dynamic_cast<LEditText *> (mClassPane->FindPaneByID( item_AetePropertyKeyword ));
	ThrowIfNil_( theEditText );
	if (!disableIt) {
		UMiscUtils::OSTypeToPString(theKeyword, theString);
	} 
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *> (mClassPane->FindPaneByID( item_AetePropertyType ));
	ThrowIfNil_( theEditText );
	if (!disableIt) {
		UMiscUtils::OSTypeToPString(theType, theString);
	} 
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *> (mClassPane->FindPaneByID( item_AetePropertyDescr ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theDescription);

}


// ---------------------------------------------------------------------------
//  InstallElementValues												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::InstallElementValues(CAeteElement *	inElement)
{
	Str255			theString;
	OSType 			theID;
	LEditText *		theEditText;
	LTextColumn *	theTable;
	Boolean			disableIt = false;

	if (inElement) {
		theID = inElement->GetID();				
		disableIt = false;
	}  else {
		theString[0] = 0;
		disableIt = true;
	}
	
	theEditText = dynamic_cast<LEditText *> (mClassPane->FindPaneByID( item_AeteElementID ));
	ThrowIfNil_( theEditText );
	if (!disableIt) {
		UMiscUtils::OSTypeToPString(theID, theString);
	} 
	theEditText->SetDescriptor(theString);

	theTable = dynamic_cast<LTextColumn *> (mClassPane->FindPaneByID( item_AeteKeyFormsTable ));
	ThrowIfNil_( theEditText );

// 		theTable->GetKeyForms();

}


// ---------------------------------------------------------------------------
//  InstallCompOpValues												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::InstallCompOpValues(CAeteCompOp * inCompOp)
{
	Str255		theString, theName, theDescription;
	OSType		theID;
	LEditText *	theEditText;
	Boolean		disableIt = false;

	if (inCompOp) {
		inCompOp->GetValues(theName, theID, theDescription);
		mCompOpPane->Show();
	} else {
		mCompOpPane->Hide();
	}
	
	theEditText = dynamic_cast<LEditText *> (mCompOpPane->FindPaneByID( item_AeteCompName ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theName);

	theEditText = dynamic_cast<LEditText *> (mCompOpPane->FindPaneByID( item_AeteCompID ));
	ThrowIfNil_( theEditText );
	UMiscUtils::OSTypeToPString(theID, theString);
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *> (mCompOpPane->FindPaneByID( item_AeteCompDescr ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theDescription);

}


// ---------------------------------------------------------------------------
//  InstallEnumerationValues										[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::InstallEnumerationValues(CAeteEnumeration * inEnum)
{
	Str255			theString;
	OSType			theID;
	SInt32			theValue, theTotal;
	LEditText *		theEditText;
	LTextGroupBox * theTGB;
	ArrayIndexT		index;
	AeteEnumerator	enumerator;

	if (inEnum) {
		theID = inEnum->GetEnumerationID();
		index = inEnum->GetEnumeratorIndex();
		mEnumerationPane->Show();
	} else {
		mEnumerationPane->Hide();
	}
	
	theEditText = dynamic_cast<LEditText *> (mEnumerationPane->FindPaneByID( item_AeteEnumerationID ));
	ThrowIfNil_( theEditText );
	UMiscUtils::OSTypeToPString(theID, theString);
	theEditText->SetDescriptor(theString);

	// Current enumerator
	theTGB = dynamic_cast<LTextGroupBox *> (mEnumerationPane->FindPaneByID( item_AeteEnumBox ));
	
	if ( inEnum && inEnum->GetEnumerators()->FetchItemAt(index, enumerator) ) {
		InstallEnumeratorValues( & enumerator);
		theTGB->Enable();
		theValue = inEnum->GetEnumeratorIndex();
		theTotal = inEnum->GetEnumerators()->GetCount();
	} else {
		InstallEnumeratorValues(NULL);
		theTGB->Disable();
		theValue = 0;
		theTotal = 0;
	}
	
	UpdateSlider(item_AeteEnumSlider, theValue, theTotal);

}


// ---------------------------------------------------------------------------
//  InstallEnumeratorValues										[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::InstallEnumeratorValues(AeteEnumerator * inEnumerator)
{
	Str255			theString;
	LEditText *		theEditText;
	Boolean			disableIt = false;
	
	theString[0] = 0;
	
	if (!inEnumerator) {
		inEnumerator->name[0] = 0;
		inEnumerator->description[0] = 0;
		disableIt = true;
	}
	
	theEditText = dynamic_cast<LEditText *> (mEnumerationPane->FindPaneByID( item_AeteEnumName ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(inEnumerator->name);

	theEditText = dynamic_cast<LEditText *> (mEnumerationPane->FindPaneByID( item_AeteEnumType ));
	ThrowIfNil_( theEditText );
	if (!disableIt) {
		UMiscUtils::OSTypeToPString(inEnumerator->type, theString);
	} 
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *> (mEnumerationPane->FindPaneByID( item_AeteEnumDescr ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(inEnumerator->description);
}



#pragma mark -

// ---------------------------------------------------------------------------
//  RetrieveResourceInfo												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::RetrieveResourceInfo()
{
	Str255	theString;
	SInt32	theMajorVersion, theMinorVersion;
	SInt32	theLanguage, theScript;
	LEditField * theEditField;

	theEditField = dynamic_cast<LEditField *> (this->FindPaneByID( item_AeteMajorVersion ));
	ThrowIfNil_( theEditField );
	theEditField->GetDescriptor(theString);
	::StringToNum( theString, &theMajorVersion);

	theEditField = dynamic_cast<LEditField *> (this->FindPaneByID( item_AeteMinorVersion ));
	ThrowIfNil_( theEditField );
	theEditField->GetDescriptor(theString);
	::StringToNum( theString, &theMinorVersion);

	theEditField = dynamic_cast<LEditField *> (this->FindPaneByID( item_AeteLanguageID ));
	ThrowIfNil_( theEditField );
	theEditField->GetDescriptor(theString);
	::StringToNum( theString, &theLanguage);

	theEditField = dynamic_cast<LEditField *> (this->FindPaneByID( item_AeteScriptCode ));
	ThrowIfNil_( theEditField );
	theEditField->GetDescriptor(theString);
	::StringToNum( theString, &theScript);
	
	mAete->SetValues( (UInt8) theMajorVersion, (UInt8) theMinorVersion, (SInt16) theLanguage, (SInt16) theScript);
}


// ---------------------------------------------------------------------------
//  RetrieveSuiteInfo												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::RetrieveSuiteInfo()
{
	Str255		theString, theName, theDescription;
	SInt32		theLevel, theVersion;
	OSType		theID;
	LEditText *	theEditText;

	CAeteSuite * theSuite = static_cast<CAeteSuite *>( FindCurrentObject( kind_AeteSuite ) );
	
	if (!theSuite) return;

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteSuiteName ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theName);

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteSuiteDescr ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theDescription);

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteSuiteID ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, theID);

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteSuiteLevel ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	::StringToNum( theString, &theLevel);

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteSuiteVersion ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	::StringToNum( theString, &theVersion);

	theSuite->SetValues(theName, theDescription, theID, (UInt16) theLevel, (UInt16) theVersion);
}


// ---------------------------------------------------------------------------
//  RetrievePanelValues												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::RetrievePanelValues()
{
	switch (mCurrentPanel) {
		case mpv_AeteEvent:
		RetrieveEventValues();
		break;
		
		case mpv_AeteClass:
		RetrieveClassValues();
		break;
		
		case mpv_AeteCompOp:
		RetrieveCompOpValues();
		break;
		
		case mpv_AeteEnum:
		RetrieveEnumerationValues();
		break;
	}	
}


// ---------------------------------------------------------------------------
//  RetrieveEventValues												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::RetrieveEventValues()
{
	Str255			theString;
	Str255 			theName, theDescription, theReplyDescription, theDirectDescription;		
	OSType 			theClass, theID, theReplyType, theDirectType, theKeyword, theType;
	UInt16 			theReplyFlags, theDirectFlags;
	UInt16 			theFlags;
	LEditText *		theEditText;
	ArrayIndexT		index;
	CAeteParameter*	theParameter;
	
	CAeteEvent * theEvent = static_cast<CAeteEvent *>( FindCurrentObject( kind_AeteEvent ) );
	
	if (!theEvent) return;

	theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteEventName ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theName);

	theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteEventDescr ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theDescription);

	theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteEventClass ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, theClass);

	theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteEventID ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, theID);

	// Direct parameter
	theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteDirectType ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, theDirectType);

	theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteDirectDescr ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theDirectDescription);

	// Reply
	theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteReplyType ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, theReplyType);

	theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteReplyDescr ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theReplyDescription);

	theEvent->SetValues(theName, theDescription, theClass, theID,
						theReplyType, theReplyDescription, theReplyFlags, 
						theDirectType, theDirectDescription, theDirectFlags);
	
	// Current parameter
	index = theEvent->GetParameterIndex();
	
	if ( theEvent->GetParameters()->FetchItemAt(index, theParameter) ) {
		theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteOtherName ));
		ThrowIfNil_( theEditText );
		theEditText->GetDescriptor(theName);

		theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteOtherKeyword ));
		ThrowIfNil_( theEditText );
		theEditText->GetDescriptor(theString);
		UMiscUtils::PStringToOSType( theString, theKeyword);

		theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteOtherType ));
		ThrowIfNil_( theEditText );
		theEditText->GetDescriptor(theString);
		UMiscUtils::PStringToOSType( theString, theType);

		theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteOtherDescr ));
		ThrowIfNil_( theEditText );
		theEditText->GetDescriptor(theDescription);
			
		theParameter->SetValues(theName, theKeyword, theType,
									theDescription, theFlags);
	} 	
}


// ---------------------------------------------------------------------------
//  RetrieveClassValues												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::RetrieveClassValues()
{
	Str255			theString;
	Str255 			theName, theDescription;		
	OSType 			theID, theKeyword, theType;
	UInt16 			theFlags;
	LEditText *		theEditText;
	ArrayIndexT		index;
	CAeteProperty *	theProperty;
	CAeteElement *	theElement;
	LTextColumn *	theTable;
	
	CAeteClass * theClass = static_cast<CAeteClass *>( FindCurrentObject( kind_AeteClass ) );
	
	if (!theClass) return;

	theEditText = dynamic_cast<LEditText *> (mClassPane->FindPaneByID( item_AeteClassName ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theName);

	theEditText = dynamic_cast<LEditText *> (mClassPane->FindPaneByID( item_AeteClassID ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, theID);

	theEditText = dynamic_cast<LEditText *> (mClassPane->FindPaneByID( item_AeteClassDescr ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theDescription);

	theClass->SetValues(theName, theID, theDescription);

	// Current property
	index = theClass->GetPropertyIndex();
	
	if ( theClass->GetProperties()->FetchItemAt(index, theProperty) ) {
		theEditText = dynamic_cast<LEditText *> (mClassPane->FindPaneByID( item_AetePropertyName ));
		ThrowIfNil_( theEditText );
		theEditText->GetDescriptor(theName);

		theEditText = dynamic_cast<LEditText *> (mClassPane->FindPaneByID( item_AetePropertyKeyword ));
		ThrowIfNil_( theEditText );
		theEditText->GetDescriptor(theString);
		UMiscUtils::PStringToOSType( theString, theKeyword);

		theEditText = dynamic_cast<LEditText *> (mClassPane->FindPaneByID( item_AetePropertyType ));
		ThrowIfNil_( theEditText );
		theEditText->GetDescriptor(theString);
		UMiscUtils::PStringToOSType( theString, theType);

		theEditText = dynamic_cast<LEditText *> (mClassPane->FindPaneByID( item_AetePropertyDescr ));
		ThrowIfNil_( theEditText );
		theEditText->GetDescriptor(theDescription);
		
		theProperty->SetValues(theName, theKeyword, theType,
								theDescription, theFlags);
	} 	

	// Current element
	index = theClass->GetElementIndex();
	
	if ( theClass->GetElements()->FetchItemAt(index, theElement) ) {
		theEditText = dynamic_cast<LEditText *> (mClassPane->FindPaneByID( item_AeteElementID ));
		ThrowIfNil_( theEditText );
		theEditText->GetDescriptor(theString);
		UMiscUtils::PStringToOSType( theString, theID);

		theElement->SetID(theID);
		
		theTable = dynamic_cast<LTextColumn *> (mClassPane->FindPaneByID( item_AeteKeyFormsTable ));
		ThrowIfNil_( theEditText );

// 		theTable->GetKeyForms();

	} 	
}


// ---------------------------------------------------------------------------
//  RetrieveCompOpValues												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::RetrieveCompOpValues()
{
	Str255		theString, theName, theDescription;
	OSType		theID;
	LEditText *	theEditText;
	
	CAeteCompOp * theCompOp = static_cast<CAeteCompOp *>( FindCurrentObject( kind_AeteCompOp ) );
	
	if (!theCompOp) return;

	theEditText = dynamic_cast<LEditText *> (mCompOpPane->FindPaneByID( item_AeteCompName ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theName);

	theEditText = dynamic_cast<LEditText *> (mCompOpPane->FindPaneByID( item_AeteCompID ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, theID);

	theEditText = dynamic_cast<LEditText *> (mCompOpPane->FindPaneByID( item_AeteCompDescr ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theDescription);

	theCompOp->SetValues(theName, theID, theDescription);
}


// ---------------------------------------------------------------------------
//  RetrieveEnumerationValues										[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::RetrieveEnumerationValues()
{
	Str255			theString;
	OSType			theID;
	LEditText *		theEditText;
	ArrayIndexT		index;
	AeteEnumerator	enumerator;
	
	CAeteEnumeration * theEnum = static_cast<CAeteEnumeration *>( FindCurrentObject( kind_AeteEnum ) );

	if (!theEnum) return;

	theEditText = dynamic_cast<LEditText *> (mEnumerationPane->FindPaneByID( item_AeteEnumerationID ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, theID);

	theEnum->SetEnumerationID(theID);
	
	// Current enumerator
	index = theEnum->GetEnumeratorIndex();
	
	theEditText = dynamic_cast<LEditText *> (mEnumerationPane->FindPaneByID( item_AeteEnumName ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(enumerator.name);

	theEditText = dynamic_cast<LEditText *> (mEnumerationPane->FindPaneByID( item_AeteEnumType ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, enumerator.type );

	theEditText = dynamic_cast<LEditText *> (mEnumerationPane->FindPaneByID( item_AeteEnumDescr ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(enumerator.description);
	
	theEnum->GetEnumerators()->RemoveItemsAt(1, index);
	theEnum->GetEnumerators()->InsertItemsAt(1, index, enumerator);
}


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
CAete_EditorWindow::UpdateSlider(SInt32 inSliderID, SInt32 inValue, SInt32 inTotal)
{
	LSlider *		theSlider = nil;
	LStaticText *	theIndicator = nil;
	
	switch (inSliderID) {
		case item_AeteItemSlider: {
			CAeteSuite * theSuite = static_cast<CAeteSuite *>( FindCurrentObject( kind_AeteSuite ) );
			if (theSuite) {
				switch (mCurrentPanel) {
					case mpv_AeteEvent:
					inValue = theSuite->GetEventIndex();
					inTotal = theSuite->GetEvents()->GetCount();
					break;
					
					case mpv_AeteClass:
					inValue = theSuite->GetClassIndex();
					inTotal = theSuite->GetClasses()->GetCount();
					break;
					
					case mpv_AeteCompOp:
					inValue = theSuite->GetCompOpIndex();
					inTotal = theSuite->GetCompOperators()->GetCount();
					break;
					
					case mpv_AeteEnum:
					inValue = theSuite->GetEnumerationIndex();
					inTotal = theSuite->GetEnumerations()->GetCount();
					break;
				}	
			}		
			theSlider = dynamic_cast<LSlider *> (this->FindPaneByID( inSliderID ));
			theIndicator = dynamic_cast<LStaticText *> (this->FindPaneByID( item_AeteItemIndicator ));
			break;
		}
		
		case item_AeteOtherSlider:
		theSlider = dynamic_cast<LSlider *> (mEventPane->FindPaneByID( inSliderID ));
		theIndicator = dynamic_cast<LStaticText *> (mEventPane->FindPaneByID( item_AeteOtherIndicator ));
		break;
		
		case item_AetePropertySlider:
		theSlider = dynamic_cast<LSlider *> (mClassPane->FindPaneByID( inSliderID ));
		theIndicator = dynamic_cast<LStaticText *> (mClassPane->FindPaneByID( item_AetePropertyIndicator ));
		break;
		
		case item_AeteElementSlider:
		theSlider = dynamic_cast<LSlider *> (mClassPane->FindPaneByID( inSliderID ));
		theIndicator = dynamic_cast<LStaticText *> (mClassPane->FindPaneByID( item_AeteElementIndicator ));
		break;
		
		case item_AeteEnumSlider:
		theSlider = dynamic_cast<LSlider *> (mEnumerationPane->FindPaneByID( inSliderID ));
		theIndicator = dynamic_cast<LStaticText *> (mEnumerationPane->FindPaneByID( item_AeteEnumIndicator ));
		break;
	}
	
	if (!theSlider || !theIndicator) return;
	
	if (inTotal > 1) {
		theSlider->SetMinValue(1);
		theSlider->SetValue(inValue);
		theSlider->SetMaxValue(inTotal);
		SetIndicator(theIndicator, inValue, inTotal);
		theSlider->Show();
		theIndicator->Show();
	} else {
		theSlider->Hide();
		if (inTotal == 0) {
			theIndicator->Hide();
		}
	}
}




