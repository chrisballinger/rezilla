// ===========================================================================
// CAete_EditorWindow.cp
// 
//                       Created: 2004-07-01 08:42:37
//             Last modification: 2005-01-21 14:45:53
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
#include "CAete.h"
#include "CAeteClass.h"
#include "CAeteCompOp.h"
#include "CAeteElement.h"
#include "CAeteEnumeration.h"
#include "CAeteEvent.h"
#include "CAeteParameter.h"
#include "CAeteProperty.h"
#include "CAeteStream.h"
#include "CAeteSuite.h"
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


// Standard headers
// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>
// #include <stdarg.h>

// static const Str255 categoryNames[] = {
// 	"\pSuites: ",
// 	"\pEvents: ",
// 	"\pClasses: ",
// 	"\pComparison Ops: ",
// 	"\pEnumerations: "
// };

// Statics
LMenu *		CAete_EditorWindow::sAeteMenu = nil;


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
	mCurrentPanel = mpv_AeteEvents;
	
	mSuitesPopup = dynamic_cast<LPopupButton *> (this->FindPaneByID( item_AeteSuitePopup ));
	ThrowIfNil_( mSuitesPopup );
	
	mController = dynamic_cast<LPageController *> (this->FindPaneByID( item_AetePanelController ));
	ThrowIfNil_( mController );
			
	mMultiPanel = dynamic_cast<LMultiPanelView *> (this->FindPaneByID( item_AeteMultiPanelView ));
	ThrowIfNil_( mMultiPanel );
	
	mMainSlider = dynamic_cast<LSlider *> (this->FindPaneByID( item_AeteItemSlider ));
	ThrowIfNil_( mMainSlider );

	mIndicator = dynamic_cast<LStaticText *> (this->FindPaneByID( item_AeteItemIndicator ));
	ThrowIfNil_( mIndicator );
	
	// Link the broadcasters
	UReanimator::LinkListenerToControls( this, this, PPob_AeteEditorWindow );
	
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
	outEnabled = true;
	outUsesMark = false;
	outMark = 0;
	outName[0] = 0;
	
	switch (inCommand) {
		case cmd_AeteAddSuite:
		break;

		case cmd_AeteRemoveSuite:
		break;

		case cmd_AeteAddItem:
		break;

		case cmd_AeteRemoveItem:
		break;

		case cmd_AeteAddParameter:
		break;

		case cmd_AeteRemoveParameter:
		break;

		case cmd_AeteAddProperty:
		break;

		case cmd_AeteRemoveProperty:
		break;

		case cmd_AeteAddElement:
		break;

		case cmd_AeteRemoveElement:
		break;

		case cmd_AeteAddKeyForm:
		break;

		case cmd_AeteRemoveKeyForm:
		break;

		case cmd_AeteAddEnumerator:
		break;

		case cmd_AeteRemoveEnumerator:
		break;

		case cmd_AeteImport:
		break;

		case cmd_AeteExport:
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
#pragma unused( ioParam )

	switch (inMessage) {
		
// 	  case msg_DictSaveButton:
// 		ObeyCommand(cmd_SaveDict,nil);
// 		break;
	
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
//  FindCurrentObject												[public]
// ---------------------------------------------------------------------------

void *
CAete_EditorWindow::FindCurrentObject(SInt8 inKind)
{
	void * theObj = NULL;
	CAeteSuite * theSuite;
	ArrayIndexT index = mAete->GetSuiteIndex();
	mAete->GetSuites()->FetchItemAt(index, theSuite);
	
	switch (inKind) {
		case kind_AeteSuite:
		theObj =  (void *) theSuite;
		break;
		
		case kind_AeteEvent:
		case kind_AeteParameter:
		CAeteEvent * theEvent;
		index = theSuite->GetEventIndex();
		theSuite->GetEvents()->FetchItemAt(index, theEvent);
		theObj = (void *) theEvent;
		break;
	
		case kind_AeteClass:
		case kind_AeteProperty:
		case kind_AeteElement:
		case kind_AeteKeyForm:
		CAeteClass * theClass;
		index = theSuite->GetClassIndex();
		theSuite->GetClasses()->FetchItemAt(index, theClass);
		theObj = (void *) theClass;
		switch (inKind) {
			case kind_AeteProperty:
			CAeteProperty * theProperty;
			index = theClass->GetPropertyIndex();
			theClass->GetProperties()->FetchItemAt(index, theProperty);
			theObj = (void *) theProperty;
			break;
			
			case kind_AeteElement:
			case kind_AeteKeyForm:
			CAeteElement * theElement;
			index = theClass->GetElementIndex();
			theClass->GetElements()->FetchItemAt(index, theElement);
			theObj = (void *) theElement;
			break;
		}
		break;
		
		case kind_AeteCompOp:
		CAeteCompOp * theCompOp;
		index = theSuite->GetCompOpIndex();
		theSuite->GetCompOperators()->FetchItemAt(index, theCompOp);
		theObj = (void *) theCompOp;
		break;
		
		case kind_AeteEnum:
		case kind_AeteEnumerator:
		CAeteEnumeration * theEnumeration;
		index = theSuite->GetEnumerationIndex();
		theSuite->GetEnumerations()->FetchItemAt(index, theEnumeration);
		theObj = (void *) theEnumeration;
		break;
		
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
	UInt16		theLevel, theVersion;
	OSType		theID;
	LEditText *	theEditText;

	CAeteSuite * theSuite = static_cast<CAeteSuite *>( FindCurrentObject( kind_AeteSuite ) );

	theSuite->GetValues(theName, theDescription, theID, theLevel, theVersion);
	
	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteSuiteName ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theName);

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteSuiteDescr ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theDescription);

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteSuiteID ));
	ThrowIfNil_( theEditText );
	UMiscUtils::OSTypeToPString(theID, theString);
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteSuiteLevel ));
	ThrowIfNil_( theEditText );
	::NumToString( theLevel, theString);
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteSuiteVersion ));
	ThrowIfNil_( theEditText );
	::NumToString( theVersion, theString);
	theEditText->SetDescriptor(theString);
}


// ---------------------------------------------------------------------------
//  InstallPanelValues												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::InstallPanelValues()
{
	switch (mCurrentPanel) {
		case mpv_AeteEvents:
		InstallEventValues();
		break;
		
		case mpv_AeteClasses:
		InstallClassValues();
		break;
		
		case mpv_AeteCompOps:
		InstallCompOpValues();
		break;
		
		case mpv_AeteEnums:
		InstallEnumerationValues();
		break;
	}	
}


// ---------------------------------------------------------------------------
//  InstallEventValues												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::InstallEventValues()
{
	Str255			theString;
	Str255 			theName, theDescription, theReplyDescription, theDirectDescription;		
	OSType 			theClass, theID, theReplyType, theDirectType, theKeyword, theType;
	UInt16 			theReplyFlags, theDirectFlags, theFlags;
	LEditText *		theEditText;
	ArrayIndexT		index;
	CAeteParameter*	theParameter;
	
	CAeteEvent * theEvent = static_cast<CAeteEvent *>( FindCurrentObject( kind_AeteEvent ) );

	theEvent->GetValues(theName, theDescription, theClass, theID,
						theReplyType, theReplyDescription, theReplyFlags, 
						theDirectType, theDirectDescription, theDirectFlags);
	
	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteEventName ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theName);

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteEventDescr ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theDescription);

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteEventClass ));
	ThrowIfNil_( theEditText );
	UMiscUtils::OSTypeToPString(theClass, theString);
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteEventID ));
	ThrowIfNil_( theEditText );
	UMiscUtils::OSTypeToPString(theID, theString);
	theEditText->SetDescriptor(theString);

	// Direct parameter
	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteDirectType ));
	ThrowIfNil_( theEditText );
	UMiscUtils::OSTypeToPString(theDirectType, theString);
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteDirectDescr ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theDirectDescription);

	// Reply
	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteReplyType ));
	ThrowIfNil_( theEditText );
	UMiscUtils::OSTypeToPString(theReplyType, theString);
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteReplyDescr ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theReplyDescription);
	
	// Current parameter
	index = theEvent->GetParameterIndex();
	
	if ( theEvent->GetParameters()->FetchItemAt(index, theParameter) ) {
		theParameter->GetValues(theName, theKeyword, theType,
								theDescription, theFlags);
		
		theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteOtherName ));
		ThrowIfNil_( theEditText );
		theEditText->SetDescriptor(theName);

		theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteOtherKeyword ));
		ThrowIfNil_( theEditText );
		UMiscUtils::OSTypeToPString(theKeyword, theString);
		theEditText->SetDescriptor(theString);

		theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteOtherType ));
		ThrowIfNil_( theEditText );
		UMiscUtils::OSTypeToPString(theType, theString);
		theEditText->SetDescriptor(theString);

		theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteOtherDescr ));
		ThrowIfNil_( theEditText );
		theEditText->SetDescriptor(theDescription);
	} 	
}


// ---------------------------------------------------------------------------
//  InstallClassValues												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::InstallClassValues()
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

	theClass->GetValues(theName, theID, theDescription);
	
	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteClassName ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theName);

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteClassID ));
	ThrowIfNil_( theEditText );
	UMiscUtils::OSTypeToPString(theID, theString);
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteClassDescr ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theDescription);

	// Current property
	index = theClass->GetPropertyIndex();
	
	if ( theClass->GetProperties()->FetchItemAt(index, theProperty) ) {
		theProperty->GetValues(theName, theKeyword, theType,
								theDescription, theFlags);
		
		theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AetePropertyName ));
		ThrowIfNil_( theEditText );
		theEditText->SetDescriptor(theName);

		theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AetePropertyKeyword ));
		ThrowIfNil_( theEditText );
		UMiscUtils::OSTypeToPString(theKeyword, theString);
		theEditText->SetDescriptor(theString);

		theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AetePropertyType ));
		ThrowIfNil_( theEditText );
		UMiscUtils::OSTypeToPString(theType, theString);
		theEditText->SetDescriptor(theString);

		theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AetePropertyDescr ));
		ThrowIfNil_( theEditText );
		theEditText->SetDescriptor(theDescription);
	} 	

	// Current element
	index = theClass->GetElementIndex();
	
	if ( theClass->GetElements()->FetchItemAt(index, theElement) ) {
		theID = theElement->GetID();
		
		theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteElementID ));
		ThrowIfNil_( theEditText );
		UMiscUtils::OSTypeToPString(theID, theString);
		theEditText->SetDescriptor(theString);

		theTable = dynamic_cast<LTextColumn *> (this->FindPaneByID( item_AeteKeyFormsTable ));
		ThrowIfNil_( theEditText );

// 		theTable->GetKeyForms();

	} 	
}


// ---------------------------------------------------------------------------
//  InstallCompOpValues												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::InstallCompOpValues()
{
	Str255		theString, theName, theDescription;
	OSType		theID;
	LEditText *	theEditText;
	
	CAeteCompOp * theCompOp = static_cast<CAeteCompOp *>( FindCurrentObject( kind_AeteCompOp ) );

	theCompOp->GetValues(theName, theID, theDescription);
	
	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteCompName ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theName);

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteCompID ));
	ThrowIfNil_( theEditText );
	UMiscUtils::OSTypeToPString(theID, theString);
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteCompDescr ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theDescription);

}


// ---------------------------------------------------------------------------
//  InstallEnumerationValues										[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::InstallEnumerationValues()
{
	Str255			theString;
	OSType			theID;
	LEditText *		theEditText;
	ArrayIndexT		index;
	AeteEnumerator	enumerator;
	
	CAeteEnumeration * theEnum = static_cast<CAeteEnumeration *>( FindCurrentObject( kind_AeteEnum ) );

	theID = theEnum->GetEnumerationID();
	
	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteEnumerationID ));
	ThrowIfNil_( theEditText );
	UMiscUtils::OSTypeToPString(theID, theString);
	theEditText->SetDescriptor(theString);

	// Current enumerator
	index = theEnum->GetEnumeratorIndex();
	
	if ( theEnum->GetEnumerators()->FetchItemAt(index, enumerator) ) {
		theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteEnumName ));
		ThrowIfNil_( theEditText );
		theEditText->SetDescriptor(enumerator.name);

		theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteEnumType ));
		ThrowIfNil_( theEditText );
		UMiscUtils::OSTypeToPString(enumerator.type, theString);
		theEditText->SetDescriptor(theString);

		theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteEnumDescr ));
		ThrowIfNil_( theEditText );
		theEditText->SetDescriptor(enumerator.description);
	} 	
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
		case mpv_AeteEvents:
		RetrieveEventValues();
		break;
		
		case mpv_AeteClasses:
		RetrieveClassValues();
		break;
		
		case mpv_AeteCompOps:
		RetrieveCompOpValues();
		break;
		
		case mpv_AeteEnums:
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
	UInt16 			theReplyFlags, theDirectFlags, theFlags;
	LEditText *		theEditText;
	ArrayIndexT		index;
	CAeteParameter*	theParameter;
	
	CAeteEvent * theEvent = static_cast<CAeteEvent *>( FindCurrentObject( kind_AeteEvent ) );
	
	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteEventName ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theName);

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteEventDescr ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theDescription);

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteEventClass ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, theClass);

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteEventID ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, theID);

	// Direct parameter
	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteDirectType ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, theDirectType);

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteDirectDescr ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theDirectDescription);

	// Reply
	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteReplyType ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, theReplyType);

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteReplyDescr ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theReplyDescription);

	theEvent->SetValues(theName, theDescription, theClass, theID,
						theReplyType, theReplyDescription, theReplyFlags, 
						theDirectType, theDirectDescription, theDirectFlags);
	
	// Current parameter
	index = theEvent->GetParameterIndex();
	
	if ( theEvent->GetParameters()->FetchItemAt(index, theParameter) ) {
		theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteOtherName ));
		ThrowIfNil_( theEditText );
		theEditText->GetDescriptor(theName);

		theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteOtherKeyword ));
		ThrowIfNil_( theEditText );
		theEditText->GetDescriptor(theString);
		UMiscUtils::PStringToOSType( theString, theKeyword);

		theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteOtherType ));
		ThrowIfNil_( theEditText );
		theEditText->GetDescriptor(theString);
		UMiscUtils::PStringToOSType( theString, theType);

		theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteOtherDescr ));
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
	
	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteClassName ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theName);

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteClassID ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, theID);

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteClassDescr ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theDescription);

	theClass->SetValues(theName, theID, theDescription);

	// Current property
	index = theClass->GetPropertyIndex();
	
	if ( theClass->GetProperties()->FetchItemAt(index, theProperty) ) {
		theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AetePropertyName ));
		ThrowIfNil_( theEditText );
		theEditText->GetDescriptor(theName);

		theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AetePropertyKeyword ));
		ThrowIfNil_( theEditText );
		theEditText->GetDescriptor(theString);
		UMiscUtils::PStringToOSType( theString, theKeyword);

		theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AetePropertyType ));
		ThrowIfNil_( theEditText );
		theEditText->GetDescriptor(theString);
		UMiscUtils::PStringToOSType( theString, theType);

		theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AetePropertyDescr ));
		ThrowIfNil_( theEditText );
		theEditText->GetDescriptor(theDescription);
		
		theProperty->SetValues(theName, theKeyword, theType,
								theDescription, theFlags);
	} 	

	// Current element
	index = theClass->GetElementIndex();
	
	if ( theClass->GetElements()->FetchItemAt(index, theElement) ) {
		theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteElementID ));
		ThrowIfNil_( theEditText );
		theEditText->GetDescriptor(theString);
		UMiscUtils::PStringToOSType( theString, theID);

		theElement->SetID(theID);
		
		theTable = dynamic_cast<LTextColumn *> (this->FindPaneByID( item_AeteKeyFormsTable ));
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
	
	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteCompName ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theName);

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteCompID ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, theID);

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteCompDescr ));
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

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteEnumerationID ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, theID);

	theEnum->SetEnumerationID(theID);
	
	// Current enumerator
	index = theEnum->GetEnumeratorIndex();
	
	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteEnumName ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(enumerator.name);

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteEnumType ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, enumerator.type );

	theEditText = dynamic_cast<LEditText *> (this->FindPaneByID( item_AeteEnumDescr ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(enumerator.description);
	
	theEnum->GetEnumerators()->RemoveItemsAt(1, index);
	theEnum->GetEnumerators()->InsertItemsAt(1, index, enumerator);
}


