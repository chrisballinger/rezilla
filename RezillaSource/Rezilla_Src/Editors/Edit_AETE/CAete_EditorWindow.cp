// ===========================================================================
// CAete_EditorWindow.cp
// 
//                       Created: 2004-07-01 08:42:37
//             Last modification: 2005-01-27 07:06:17
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
	
	RemoveAeteMenu();
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

	// Link to the broadcasters
	MakeListeners();
	
// 	// Make the DictDoc a listener of mCategoriesListBox
// 	mCategoriesListBox->AddListener(this);
// 	mDictTermsTable->AddListener(this);
	
// 	mAeteStreamsArrayPtr = new TArray<CAeteStream*>();

//     SwitchTarget(mContentsView);
}


// ---------------------------------------------------------------------------
//	¥ MakeListeners
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::MakeListeners()
{
	UReanimator::LinkListenerToBroadcasters( this, this, PPob_AeteEditorWindow );
	mController->AddListener(mMultiPanel);
	mController->AddListener(this);
	
	UReanimator::LinkListenerToBroadcasters( this, mEventPane, PPob_AeteEventsPane );
	UReanimator::LinkListenerToBroadcasters( this, mClassPane, PPob_AeteClassesPane );
	UReanimator::LinkListenerToBroadcasters( this, mCompOpPane, PPob_AeteCompOpsPane );
	UReanimator::LinkListenerToBroadcasters( this, mEnumerationPane, PPob_AeteEnumsPane );

	
// 	// Link the sliders
// 	LSlider * theSlider;
// 	
// 	theSlider = dynamic_cast<LSlider *> (mEventPane->FindPaneByID( item_AeteOtherSlider ));
// 	ThrowIfNil_(theSlider);
// 	theSlider->AddListener(this);
// 	
// 	theSlider = dynamic_cast<LSlider *> (mClassPane->FindPaneByID( item_AetePropertySlider ));
// 	ThrowIfNil_(theSlider);
// 	theSlider->AddListener(this);
// 	
// 	theSlider = dynamic_cast<LSlider *> (mClassPane->FindPaneByID( item_AeteElementSlider ));
// 	ThrowIfNil_(theSlider);
// 	theSlider->AddListener(this);
// 	
// 	theSlider = dynamic_cast<LSlider *> (mEnumerationPane->FindPaneByID( item_AeteEnumSlider ));
// 	ThrowIfNil_(theSlider);
// 	theSlider->AddListener(this);
// 	
// 	// Link the popups
// 	LPopupButton * thePopup;
// 	
// 	thePopup = dynamic_cast<LPopupButton *> (mEventPane->FindPaneByID( item_AeteDirectOptions ));
// 	ThrowIfNil_(thePopup);
// 	thePopup->AddListener(this);
// 	
// 	thePopup = dynamic_cast<LPopupButton *> (mEventPane->FindPaneByID( item_AeteReplyOptions ));
// 	ThrowIfNil_(thePopup);
// 	thePopup->AddListener(this);
// 	
// 	thePopup = dynamic_cast<LPopupButton *> (mEventPane->FindPaneByID( item_AeteOtherOptions ));
// 	ThrowIfNil_(thePopup);
// 	thePopup->AddListener(this);
// 	
// 	thePopup = dynamic_cast<LPopupButton *> (mClassPane->FindPaneByID( item_AetePropertyOptions ));
// 	ThrowIfNil_(thePopup);
// 	thePopup->AddListener(this);
	
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
//  ListenToMessage										[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{
	SInt32 newIndex, oldIndex;
	
	switch (inMessage) {
		
		case item_AeteSuitePopup:
		newIndex = *(SInt32 *) ioParam;
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
		newIndex = *(SInt32 *) ioParam;
		if (newIndex != mCurrentPanel) {
			RetrievePanelValues();
			mCurrentPanel = newIndex;
			InstallPanelValues();
			UpdateSlider(item_AeteItemSlider, 0, 0);
		}
		break;
		
		
		case item_AeteItemSlider:
		newIndex = *(SInt32 *) ioParam;
		oldIndex = GetCurrentIndex(mCurrentPanel);
		if (newIndex != oldIndex) {
			RetrievePanelValues();
			SetCurrentIndex(mCurrentPanel, newIndex);
			InstallPanelValues();
			UpdateSlider(item_AeteItemSlider, 0, 0);
		}
		break;
		
		
		case item_AeteOtherSlider:
		CAeteParameter * theParameter;
		
		newIndex = *(SInt32 *) ioParam;
		oldIndex = GetCurrentIndex(kind_AeteParameter);
		if (newIndex != oldIndex) {
			theParameter = static_cast<CAeteParameter *>( FindCurrentObject( kind_AeteParameter ) );
			RetrieveParameterValues(theParameter);
			SetCurrentIndex(kind_AeteParameter, newIndex);
			theParameter = static_cast<CAeteParameter *>( FindCurrentObject( kind_AeteParameter ) );
			InstallParameterValues(theParameter);
		} 
		break;
		
		
		case item_AetePropertySlider:
		CAeteProperty * theProperty;
		
		newIndex = *(SInt32 *) ioParam;
		oldIndex = GetCurrentIndex(kind_AeteProperty);
		if (newIndex != oldIndex) {
			theProperty = static_cast<CAeteProperty *>( FindCurrentObject( kind_AeteProperty ) );
			RetrievePropertyValues(theProperty);
			SetCurrentIndex(kind_AeteProperty, newIndex);
			theProperty = static_cast<CAeteProperty *>( FindCurrentObject( kind_AeteProperty ) );
			InstallPropertyValues(theProperty);
		} 
		break;
		
		
		case item_AeteElementSlider:
		CAeteElement * theElement;
		
		newIndex = *(SInt32 *) ioParam;
		oldIndex = GetCurrentIndex(kind_AeteElement);
		if (newIndex != oldIndex) {
			theElement = static_cast<CAeteElement *>( FindCurrentObject( kind_AeteElement ) );
			RetrieveElementValues(theElement);
			SetCurrentIndex(kind_AeteElement, newIndex);
			theElement = static_cast<CAeteElement *>( FindCurrentObject( kind_AeteElement ) );
			InstallElementValues(theElement);
		} 
		break;
		
		
		case item_AeteEnumSlider:
		AeteEnumerator		enumerator;
		CAeteEnumeration *	theEnum ;
		
		theEnum = static_cast<CAeteEnumeration *>( FindCurrentObject( kind_AeteEnum ) );
		newIndex = *(SInt32 *) ioParam;
		oldIndex = GetCurrentIndex(kind_AeteEnumerator);
		if (newIndex != oldIndex) {
			RetrieveEnumeratorValues(enumerator);
			theEnum->SetEnumerator(oldIndex, enumerator);
			SetCurrentIndex(kind_AeteEnumerator, newIndex);
			theEnum->GetEnumerator(newIndex, enumerator);
			InstallEnumeratorValues(enumerator);
		} 
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
	InstallSuiteValues();
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
//  GetCurrentIndex												[public]
// ---------------------------------------------------------------------------

SInt32
CAete_EditorWindow::GetCurrentIndex(SInt8 inKind)
{	
	SInt32	index = 0;
	
	switch (inKind) {
		case kind_AeteSuite:
		index = mAete->GetSuiteIndex();
		break;
		
		case kind_AeteEvent: 
		case kind_AeteClass: 
		case kind_AeteCompOp: 
		case kind_AeteEnum: 
		CAeteSuite * theSuite = static_cast<CAeteSuite *>( FindCurrentObject( kind_AeteSuite ) );
		if (theSuite) {
			index = theSuite->GetCurrentIndex(inKind);
		}
		break;
		
		case kind_AeteParameter:
		CAeteEvent * theEvent = static_cast<CAeteEvent *>( FindCurrentObject( kind_AeteEvent ) );
		if (theEvent) {
			index = theEvent->GetParameterIndex();
		}
		break;
		
		case kind_AeteProperty: {
			CAeteClass * theClass = static_cast<CAeteClass *>( FindCurrentObject( kind_AeteClass ) );
			if (theClass) {
				index = theClass->GetPropertyIndex();
			}
			break;
		}
		
		case kind_AeteElement: {
			CAeteClass * theClass = static_cast<CAeteClass *>( FindCurrentObject( kind_AeteClass ) );
			if (theClass) {
				index = theClass->GetElementIndex();
			}
			break;
		}
		
		case kind_AeteEnumerator:
		CAeteEnumeration * theEnum = static_cast<CAeteEnumeration *>( FindCurrentObject( kind_AeteEnum ) );
		if (theEnum) {
			index = theEnum->GetEnumeratorIndex();
		}
		break;
		
	}
	return index;
}


// ---------------------------------------------------------------------------
//  SetCurrentIndex												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::SetCurrentIndex(SInt8 inKind, SInt32 inIndex)
{
	if (inIndex <= 0) return;
	
	switch (inKind) {
		case kind_AeteEvent: 
		case kind_AeteClass: 
		case kind_AeteCompOp: 
		case kind_AeteEnum: 
		CAeteSuite * theSuite = static_cast<CAeteSuite *>( FindCurrentObject( kind_AeteSuite ) );
		if (theSuite) {
			 theSuite->SetCurrentIndex(inKind, inIndex);
		}
		break;
		
		case kind_AeteParameter:
		CAeteEvent * theEvent = static_cast<CAeteEvent *>( FindCurrentObject( kind_AeteEvent ) );
		if (theEvent) {
			theEvent->SetParameterIndex(inIndex);
		}
		break;
		
		case kind_AeteProperty: {
			CAeteClass * theClass = static_cast<CAeteClass *>( FindCurrentObject( kind_AeteClass ) );
			if (theClass) {
				theClass->SetPropertyIndex(inIndex);
			}
			break;
		}
		
		case kind_AeteElement: {
			CAeteClass * theClass = static_cast<CAeteClass *>( FindCurrentObject( kind_AeteClass ) );
			if (theClass) {
				theClass->SetElementIndex(inIndex);
			}
			break;
		}
		
		case kind_AeteEnumerator:
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
	
	// Set the slider
	if (inTotal > 1) {
// 		theSlider->SetMinValue(1);
		theSlider->SetValue(inValue);
		theSlider->SetMaxValue(inTotal);
		theSlider->Show();
	} else {
		theSlider->Hide();
	}
	// Set the indicator
	if (inTotal == 0) {
		theIndicator->Hide();
	} else {
		SetIndicator(theIndicator, inValue, inTotal);
		theIndicator->Show();
	}
}


