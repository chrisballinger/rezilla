// ===========================================================================
// CAete_WindowValues.cp
// 
//                       Created: 2005-01-25 09:01:07
//             Last modification: 2005-02-07 06:42:17
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
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
// #include <LTextColumn.h>
#include <LTextGroupBox.h>

const UInt16 AeteDirectFlag[] = { kAEUTOptional, kAEUTlistOfItems, kAEUTEnumerated, kAEUTChangesState, 
	kAEUTEnumsAreTypes, kAEUTEnumListIsExclusive, kAEUTDirectParamIsReference, kAEUTNotDirectParamIsTarget };

const UInt16 AeteReplyFlag[] = { kAEUTOptional, kAEUTlistOfItems, kAEUTEnumerated, kAEUTTightBindingFunction, 
	kAEUTEnumsAreTypes, kAEUTEnumListIsExclusive, kAEUTReplyIsReference, aeut_NonVerbEvent };

const UInt16 AeteParamFlag[] = { kAEUTOptional, kAEUTlistOfItems, kAEUTEnumerated, 
	kAEUTEnumsAreTypes, kAEUTEnumListIsExclusive, kAEUTParamIsReference, kAEUTParamIsTarget,
	aeut_LabeledParam, kAEUTFeminine, kAEUTMasculine, kAEUTPlural};

const UInt16 AetePropertyFlag[] = { kAEUTlistOfItems, kAEUTEnumerated, kAEUTReadWrite,
	kAEUTEnumsAreTypes, kAEUTEnumListIsExclusive, kAEUTPropertyIsReference,
	kAEUTApostrophe, kAEUTFeminine, kAEUTMasculine, kAEUTPlural};


// ---------------------------------------------------------------------------
//  InstallResourceInfo												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::InstallResourceInfo()
{
	Str255		theString;
	UInt8		theMajorVersion, theMinorVersion;
	SInt16		theLanguage, theScript;
	LEditText * theEditText;
	
	mAete->GetValues(theMajorVersion, theMinorVersion, theLanguage, theScript);

	theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_AeteMajorVersion ));
	ThrowIfNil_( theEditText );
	::NumToString( theMajorVersion, theString);
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_AeteMinorVersion ));
	ThrowIfNil_( theEditText );
	::NumToString( theMinorVersion, theString);
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_AeteLanguageID ));
	ThrowIfNil_( theEditText );
	::NumToString( theLanguage, theString);
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_AeteScriptCode ));
	ThrowIfNil_( theEditText );
	::NumToString( theScript, theString);
	theEditText->SetDescriptor(theString);
}


// ---------------------------------------------------------------------------
//  InstallSuiteValues												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::InstallSuiteValues()
{
	Str255		theString, theName, theDescription;
	UInt16		theLevel = 0, theVersion = 0;
	OSType		theID;
	SInt32		theValue, theTotal;
	LEditText *	theEditText;
	Boolean		disableIt = false;
	
	CAeteSuite * theSuite = static_cast<CAeteSuite *>( FindCurrentObject( kind_AeteSuite ) );
	LTextGroupBox * theTGB = dynamic_cast<LTextGroupBox *>(this->FindPaneByID( item_AeteSuiteBox ));

	if (theSuite) {
		theSuite->GetValues(theName, theDescription, theID, theLevel, theVersion);
		theValue = theSuite->GetCurrentIndex(mCurrentPanel);
		theTotal = theSuite->GetCurrentCount(mCurrentPanel);
		theTGB->Enable();
	} else {
		theString[0] = 0;
		theName[0] = 0;
		theDescription[0] = 0;
		theValue = 0;
		theTotal = 0;
		disableIt = true;
		theTGB->Disable();
	}

	theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_AeteSuiteName ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theName);

	theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_AeteSuiteDescr ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theDescription);

	theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_AeteSuiteID ));
	ThrowIfNil_( theEditText );
	if (!disableIt) {
		UMiscUtils::OSTypeToPString(theID, theString);
	} 
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_AeteSuiteLevel ));
	ThrowIfNil_( theEditText );
	::NumToString( theLevel, theString);
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_AeteSuiteVersion ));
	ThrowIfNil_( theEditText );
	::NumToString( theVersion, theString);
	theEditText->SetDescriptor(theString);

	// Update the main slider
	UpdateSlider(item_AeteItemSlider, theValue, theTotal, false, true);
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
	CAeteParameter*	theParameter = nil;
	ArrayIndexT		index = 0;
	Boolean			disableIt = false;
	
	if (inEvent) {
		inEvent->GetValues(theName, theDescription, theClass, theID,
							theReplyType, theReplyDescription, theReplyFlags, 
							theDirectType, theDirectDescription, theDirectFlags);
		index = inEvent->GetParameterIndex();
		mEventPane->Show();
	} else {
		mEventPane->Hide();
		return;
	}
	
	theEditText = dynamic_cast<LEditText *>(mEventPane->FindPaneByID( item_AeteEventName ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theName);

	theEditText = dynamic_cast<LEditText *>(mEventPane->FindPaneByID( item_AeteEventDescr ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theDescription);

	theEditText = dynamic_cast<LEditText *>(mEventPane->FindPaneByID( item_AeteEventClass ));
	ThrowIfNil_( theEditText );
	UMiscUtils::OSTypeToPString(theClass, theString);
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *>(mEventPane->FindPaneByID( item_AeteEventID ));
	ThrowIfNil_( theEditText );
	UMiscUtils::OSTypeToPString(theID, theString);
	theEditText->SetDescriptor(theString);

	// Direct parameter
	theEditText = dynamic_cast<LEditText *>(mEventPane->FindPaneByID( item_AeteDirectType ));
	ThrowIfNil_( theEditText );
	UMiscUtils::OSTypeToPString(theDirectType, theString);
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *>(mEventPane->FindPaneByID( item_AeteDirectDescr ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theDirectDescription);

	InstallFlags(item_AeteDirectOptions, theDirectFlags);

	// Reply
	theEditText = dynamic_cast<LEditText *>(mEventPane->FindPaneByID( item_AeteReplyType ));
	ThrowIfNil_( theEditText );
	UMiscUtils::OSTypeToPString(theReplyType, theString);
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *>(mEventPane->FindPaneByID( item_AeteReplyDescr ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theReplyDescription);
	
	InstallFlags(item_AeteReplyOptions, theReplyFlags);

	// Current parameter
	theTGB = dynamic_cast<LTextGroupBox *>(mEventPane->FindPaneByID( item_AeteParamBox ));

	if (inEvent && inEvent->GetParameters()->FetchItemAt(index, theParameter) ) {
		theTGB->Enable();
		theValue = index;
		theTotal = inEvent->CountParameters();
	} else {
		theTGB->Disable();
		theValue = 0;
		theTotal = 0;
	}
	
	InstallParameterValues(theParameter);
	UpdateSlider(item_AeteParamSlider, theValue, theTotal);	
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
		
	theEditText = dynamic_cast<LEditText *>(mEventPane->FindPaneByID( item_AeteParamName ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theName);

	theEditText = dynamic_cast<LEditText *>(mEventPane->FindPaneByID( item_AeteParamKeyword ));
	ThrowIfNil_( theEditText );
	if (!disableIt) {
		UMiscUtils::OSTypeToPString(theKeyword, theString);
	} 
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *>(mEventPane->FindPaneByID( item_AeteParamType ));
	ThrowIfNil_( theEditText );
	if (!disableIt) {
		UMiscUtils::OSTypeToPString(theType, theString);
	} 
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *>(mEventPane->FindPaneByID( item_AeteParamDescr ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theDescription);
	
	InstallFlags(item_AeteParamOptions, theFlags);

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
	ArrayIndexT		propIndex = 0, elemIndex = 0;
	CAeteProperty *	theProperty = nil;
	CAeteElement *	theElement = nil;
	LTextGroupBox * theTGB;

	if (inClass) {
		inClass->GetValues(theName, theID, theDescription);
		propIndex = inClass->GetPropertyIndex();
		elemIndex = inClass->GetElementIndex();
		mClassPane->Show();
	} else {
		mClassPane->Hide();
		return;
	}
		
	theEditText = dynamic_cast<LEditText *>(mClassPane->FindPaneByID( item_AeteClassName ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theName);

	theEditText = dynamic_cast<LEditText *>(mClassPane->FindPaneByID( item_AeteClassID ));
	ThrowIfNil_( theEditText );
	UMiscUtils::OSTypeToPString(theID, theString);
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *>(mClassPane->FindPaneByID( item_AeteClassDescr ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theDescription);

	// Current property
	theTGB = dynamic_cast<LTextGroupBox *>(mClassPane->FindPaneByID( item_AetePropertyBox ));
	
	if (inClass && inClass->GetProperties()->FetchItemAt(propIndex, theProperty) ) {
		theTGB->Enable();
		theValue = propIndex;
		theTotal = inClass->CountProperties();
	}  else {
		theTGB->Disable();
		theValue = 0;
		theTotal = 0;
	}
	
	InstallPropertyValues(theProperty);
	UpdateSlider(item_AetePropertySlider, theValue, theTotal);

	// Current element
	theTGB = dynamic_cast<LTextGroupBox *>(mClassPane->FindPaneByID( item_AeteElementBox ));

	if (inClass && inClass->GetElements()->FetchItemAt(elemIndex, theElement) ) {
		theTGB->Enable();
		theValue = elemIndex;
		theTotal = inClass->CountElements();
	}  else {
		theTGB->Disable();
		theValue = 0;
		theTotal = 0;
	}
	
	InstallElementValues(theElement);
	UpdateSlider(item_AeteElementSlider, theValue, theTotal);
}


// ---------------------------------------------------------------------------
//  InstallPropertyValues											[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::InstallPropertyValues(CAeteProperty * inProperty)
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
	
	theEditText = dynamic_cast<LEditText *>(mClassPane->FindPaneByID( item_AetePropertyName ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theName);

	theEditText = dynamic_cast<LEditText *>(mClassPane->FindPaneByID( item_AetePropertyKeyword ));
	ThrowIfNil_( theEditText );
	if (!disableIt) {
		UMiscUtils::OSTypeToPString(theKeyword, theString);
	} 
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *>(mClassPane->FindPaneByID( item_AetePropertyType ));
	ThrowIfNil_( theEditText );
	if (!disableIt) {
		UMiscUtils::OSTypeToPString(theType, theString);
	} 
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *>(mClassPane->FindPaneByID( item_AetePropertyDescr ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theDescription);

	InstallFlags(item_AetePropertyOptions, theFlags);

}


// ---------------------------------------------------------------------------
//  InstallElementValues											[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::InstallElementValues(CAeteElement *	inElement)
{
	Str255			theString;
	OSType 			theID, theKeyForm = 0;
	LEditText *		theEditText;
	SInt32			theValue, theTotal;
	ArrayIndexT		index = 0;
	Boolean			disableIt = false;

	if (inElement) {
		theID = inElement->GetID();				
		index = inElement->GetKeyFormIndex();
		disableIt = false;
	}  else {
		theString[0] = 0;
		disableIt = true;
	}
	
	theEditText = dynamic_cast<LEditText *>(mClassPane->FindPaneByID( item_AeteElementID ));
	ThrowIfNil_( theEditText );
	if (!disableIt) {
		UMiscUtils::OSTypeToPString(theID, theString);
	} 
	theEditText->SetDescriptor(theString);

	// KeyForms
	if ( inElement && inElement->GetCurrentKeyForm(theKeyForm) ) {
		disableIt = false;
		theValue = index;
		theTotal = inElement->CountKeyForms();
	} else {
		theString[0] = 0;
		disableIt = true;
		theValue = 0;
		theTotal = 0;
	} 
	
	InstallKeyFormValues(theKeyForm, disableIt);
	UpdateSlider(item_AeteKeyFormSlider, theValue, theTotal);
}


// ---------------------------------------------------------------------------
//  InstallKeyFormValues											[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::InstallKeyFormValues(OSType inKeyForm, Boolean inDisable)
{
	Str255			theString;
	LEditText *		theEditText;

	if (inKeyForm != 0) {
		UMiscUtils::OSTypeToPString(inKeyForm, theString);
	} else {
		theString[0] = 0;
	}
	
	theEditText = dynamic_cast<LEditText *>(mClassPane->FindPaneByID( item_AeteKeyFormID ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theString);
	if (inDisable) {
		theEditText->Disable();
	} else {
		theEditText->Enable();
	}
	
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
		return;
	}
	
	theEditText = dynamic_cast<LEditText *>(mCompOpPane->FindPaneByID( item_AeteCompName ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theName);

	theEditText = dynamic_cast<LEditText *>(mCompOpPane->FindPaneByID( item_AeteCompID ));
	ThrowIfNil_( theEditText );
	UMiscUtils::OSTypeToPString(theID, theString);
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *>(mCompOpPane->FindPaneByID( item_AeteCompDescr ));
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
	ArrayIndexT		index = 0;
	AeteEnumerator	enumerator;

	if (inEnum) {
		theID = inEnum->GetEnumerationID();
		index = inEnum->GetEnumeratorIndex();
		mEnumerationPane->Show();
	} else {
		mEnumerationPane->Hide();
		return;
	}
	
	enumerator.name[0] = 0;
	enumerator.type = 0;
	enumerator.description[0] = 0;

	theEditText = dynamic_cast<LEditText *>(mEnumerationPane->FindPaneByID( item_AeteEnumerationID ));
	ThrowIfNil_( theEditText );
	UMiscUtils::OSTypeToPString(theID, theString);
	theEditText->SetDescriptor(theString);

	// Current enumerator
	theTGB = dynamic_cast<LTextGroupBox *>(mEnumerationPane->FindPaneByID( item_AeteEnumBox ));
	
	if ( inEnum && inEnum->GetEnumerator(index, enumerator) ) {
		theTGB->Enable();
		theValue = index;
		theTotal = inEnum->CountEnumerators();
	} else {
		theTGB->Disable();
		theValue = 0;
		theTotal = 0;
	}
	
	InstallEnumeratorValues(enumerator);
	UpdateSlider(item_AeteEnumSlider, theValue, theTotal);

}


// ---------------------------------------------------------------------------
//  InstallEnumeratorValues										[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::InstallEnumeratorValues(AeteEnumerator inEnumerator)
{
	Str255			theString;
	LEditText *		theEditText;
	
	theString[0] = 0;
		
	theEditText = dynamic_cast<LEditText *>(mEnumerationPane->FindPaneByID( item_AeteEnumName ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(inEnumerator.name);

	theEditText = dynamic_cast<LEditText *>(mEnumerationPane->FindPaneByID( item_AeteEnumType ));
	ThrowIfNil_( theEditText );
	if (inEnumerator.type != 0) {
		UMiscUtils::OSTypeToPString(inEnumerator.type, theString);
	} 
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *>(mEnumerationPane->FindPaneByID( item_AeteEnumDescr ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(inEnumerator.description);
}



#pragma mark -

// ---------------------------------------------------------------------------
//  RetrieveResourceInfo												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::RetrieveResourceInfo()
{
	Str255		theString;
	SInt32		theMajorVersion, theMinorVersion;
	SInt32		theLanguage, theScript;
	LEditText * theEditText;

	theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_AeteMajorVersion ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	::StringToNum( theString, &theMajorVersion);

	theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_AeteMinorVersion ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	::StringToNum( theString, &theMinorVersion);

	theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_AeteLanguageID ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	::StringToNum( theString, &theLanguage);

	theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_AeteScriptCode ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	::StringToNum( theString, &theScript);
	
	mAete->SetValues( (UInt8) theMajorVersion, (UInt8) theMinorVersion, (SInt16) theLanguage, (SInt16) theScript);
}


// ---------------------------------------------------------------------------
//  RetrieveSuiteValues												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::RetrieveSuiteValues()
{
	Str255		theString, theName, theDescription;
	SInt32		theLevel, theVersion;
	OSType		theID;
	LEditText *	theEditText;

	CAeteSuite * theSuite = static_cast<CAeteSuite *>( FindCurrentObject( kind_AeteSuite ) );
	
	if (!theSuite) return;

	theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_AeteSuiteName ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theName);

	theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_AeteSuiteDescr ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theDescription);

	theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_AeteSuiteID ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, theID);

	theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_AeteSuiteLevel ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	::StringToNum( theString, &theLevel);

	theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_AeteSuiteVersion ));
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
		CAeteEvent * theEvent = static_cast<CAeteEvent *>( FindCurrentObject( kind_AeteEvent ) );
		RetrieveEventValues(theEvent);
		break;
		
		case mpv_AeteClass:
		CAeteClass * theClass = static_cast<CAeteClass *>( FindCurrentObject( kind_AeteClass ) );
		RetrieveClassValues(theClass);
		break;
		
		case mpv_AeteCompOp:
		CAeteCompOp * theCompOp = static_cast<CAeteCompOp *>( FindCurrentObject( kind_AeteCompOp ) );
		RetrieveCompOpValues(theCompOp);
		break;
		
		case mpv_AeteEnum:
		CAeteEnumeration * theEnum = static_cast<CAeteEnumeration *>( FindCurrentObject( kind_AeteEnum ) );
		RetrieveEnumerationValues(theEnum);
		break;
	}	
}


// ---------------------------------------------------------------------------
//  RetrieveEventValues												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::RetrieveEventValues(CAeteEvent * inEvent)
{
	Str255			theString;
	Str255 			theName, theDescription, theReplyDescription, theDirectDescription;		
	OSType 			theClass, theID, theReplyType, theDirectType;
	UInt16 			theReplyFlags, theDirectFlags;
	LEditText *		theEditText;
	ArrayIndexT		index;
	CAeteParameter*	theParameter;
	
	if (!inEvent) return;

	theEditText = dynamic_cast<LEditText *>(mEventPane->FindPaneByID( item_AeteEventName ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theName);

	theEditText = dynamic_cast<LEditText *>(mEventPane->FindPaneByID( item_AeteEventDescr ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theDescription);

	theEditText = dynamic_cast<LEditText *>(mEventPane->FindPaneByID( item_AeteEventClass ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, theClass);

	theEditText = dynamic_cast<LEditText *>(mEventPane->FindPaneByID( item_AeteEventID ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, theID);

	// Direct parameter
	theEditText = dynamic_cast<LEditText *>(mEventPane->FindPaneByID( item_AeteDirectType ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, theDirectType);

	theEditText = dynamic_cast<LEditText *>(mEventPane->FindPaneByID( item_AeteDirectDescr ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theDirectDescription);

	RetrieveFlags(item_AeteDirectOptions, theDirectFlags);

	// Reply
	theEditText = dynamic_cast<LEditText *>(mEventPane->FindPaneByID( item_AeteReplyType ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, theReplyType);

	theEditText = dynamic_cast<LEditText *>(mEventPane->FindPaneByID( item_AeteReplyDescr ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theReplyDescription);

	RetrieveFlags(item_AeteReplyOptions, theReplyFlags);

	inEvent->SetValues(theName, theDescription, theClass, theID,
						theReplyType, theReplyDescription, theReplyFlags, 
						theDirectType, theDirectDescription, theDirectFlags);
	
	// Current parameter
	index = inEvent->GetParameterIndex();
	
	if ( inEvent->GetParameters()->FetchItemAt(index, theParameter) ) {
		RetrieveParameterValues(theParameter);
	} 	
}


// ---------------------------------------------------------------------------
//  RetrieveParameterValues												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::RetrieveParameterValues(CAeteParameter* inParameter)
{
	Str255			theString;
	Str255 			theName, theDescription;		
	OSType 			theKeyword, theType;
	UInt16 			theFlags;
	LEditText *		theEditText;
	
	if (!inParameter) return;

	theEditText = dynamic_cast<LEditText *>(mEventPane->FindPaneByID( item_AeteParamName ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theName);

	theEditText = dynamic_cast<LEditText *>(mEventPane->FindPaneByID( item_AeteParamKeyword ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, theKeyword);

	theEditText = dynamic_cast<LEditText *>(mEventPane->FindPaneByID( item_AeteParamType ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, theType);

	theEditText = dynamic_cast<LEditText *>(mEventPane->FindPaneByID( item_AeteParamDescr ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theDescription);
		
	RetrieveFlags(item_AeteParamOptions, theFlags);

	inParameter->SetValues(theName, theKeyword, theType, theDescription, theFlags);
}


// ---------------------------------------------------------------------------
//  RetrieveClassValues												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::RetrieveClassValues(CAeteClass * inClass)
{
	Str255			theString;
	Str255 			theName, theDescription;		
	OSType 			theID;
	LEditText *		theEditText;
	ArrayIndexT		index;
	CAeteProperty *	theProperty;
	CAeteElement *	theElement;
	
	if (!inClass) return;

	theEditText = dynamic_cast<LEditText *>(mClassPane->FindPaneByID( item_AeteClassName ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theName);

	theEditText = dynamic_cast<LEditText *>(mClassPane->FindPaneByID( item_AeteClassID ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, theID);

	theEditText = dynamic_cast<LEditText *>(mClassPane->FindPaneByID( item_AeteClassDescr ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theDescription);

	inClass->SetValues(theName, theID, theDescription);

	// Current property
	index = inClass->GetPropertyIndex();
	
	if ( inClass->GetProperties()->FetchItemAt(index, theProperty) ) {
		RetrievePropertyValues(theProperty);
	} 	

	// Current element
	index = inClass->GetElementIndex();
	
	if ( inClass->GetElements()->FetchItemAt(index, theElement) ) {
		RetrieveElementValues(theElement);
	} 	
}


// ---------------------------------------------------------------------------
//  RetrievePropertyValues												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::RetrievePropertyValues(CAeteProperty * inProperty)
{
	Str255			theString;
	Str255 			theName, theDescription;		
	OSType 			theKeyword, theType;
	UInt16 			theFlags;
	LEditText *		theEditText;	

	if (!inProperty) return;

	theEditText = dynamic_cast<LEditText *>(mClassPane->FindPaneByID( item_AetePropertyName ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theName);

	theEditText = dynamic_cast<LEditText *>(mClassPane->FindPaneByID( item_AetePropertyKeyword ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, theKeyword);

	theEditText = dynamic_cast<LEditText *>(mClassPane->FindPaneByID( item_AetePropertyType ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, theType);

	theEditText = dynamic_cast<LEditText *>(mClassPane->FindPaneByID( item_AetePropertyDescr ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theDescription);
	
	RetrieveFlags(item_AetePropertyOptions, theFlags);

	inProperty->SetValues(theName, theKeyword, theType, theDescription, theFlags);

}


// ---------------------------------------------------------------------------
//  RetrieveElementValues											[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::RetrieveElementValues(CAeteElement * inElement)
{
	Str255			theString;
	OSType 			theID, theKeyForm;
	LEditText *		theEditText;

	if (!inElement) return;

	theEditText = dynamic_cast<LEditText *>(mClassPane->FindPaneByID( item_AeteElementID ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, theID);

	inElement->SetID(theID);
	
	// KeyForms
	RetrieveKeyFormValues(theKeyForm);
	inElement->SetCurrentKeyForm(theKeyForm);
}


// ---------------------------------------------------------------------------
//  RetrieveKeyFormValues											[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::RetrieveKeyFormValues(OSType & outKeyForm)
{
	Str255			theString;
	LEditText *		theEditText;

	theEditText = dynamic_cast<LEditText *>(mClassPane->FindPaneByID( item_AeteKeyFormID ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType(theString, outKeyForm);
}


// ---------------------------------------------------------------------------
//  RetrieveCompOpValues												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::RetrieveCompOpValues(CAeteCompOp * inCompOp)
{
	Str255		theString, theName, theDescription;
	OSType		theID;
	LEditText *	theEditText;
	
	if (!inCompOp) return;

	theEditText = dynamic_cast<LEditText *>(mCompOpPane->FindPaneByID( item_AeteCompName ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theName);

	theEditText = dynamic_cast<LEditText *>(mCompOpPane->FindPaneByID( item_AeteCompID ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, theID);

	theEditText = dynamic_cast<LEditText *>(mCompOpPane->FindPaneByID( item_AeteCompDescr ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theDescription);

	inCompOp->SetValues(theName, theID, theDescription);
}


// ---------------------------------------------------------------------------
//  RetrieveEnumerationValues										[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::RetrieveEnumerationValues(CAeteEnumeration * inEnum)
{
	Str255			theString;
	OSType			theID;
	LEditText *		theEditText;
	ArrayIndexT		index;
	AeteEnumerator	enumerator;
	
	if (!inEnum) return;

	theEditText = dynamic_cast<LEditText *>(mEnumerationPane->FindPaneByID( item_AeteEnumerationID ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, theID);

	inEnum->SetEnumerationID(theID);
	
	// Current enumerator
	index = inEnum->GetEnumeratorIndex();
	
	RetrieveEnumeratorValues(enumerator);
	
	inEnum->SetEnumerator(index, enumerator);
}


// ---------------------------------------------------------------------------
//  RetrieveEnumeratorValues										[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::RetrieveEnumeratorValues(AeteEnumerator & outEnumerator)
{
	Str255			theString;
	LEditText *		theEditText;

	theEditText = dynamic_cast<LEditText *>(mEnumerationPane->FindPaneByID( item_AeteEnumName ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(outEnumerator.name);

	theEditText = dynamic_cast<LEditText *>(mEnumerationPane->FindPaneByID( item_AeteEnumType ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, outEnumerator.type );

	theEditText = dynamic_cast<LEditText *>(mEnumerationPane->FindPaneByID( item_AeteEnumDescr ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(outEnumerator.description);
}



#pragma mark -

// ---------------------------------------------------------------------------
//  RebuildSuitePopup													[public]
// ---------------------------------------------------------------------------
// Note: LMenuController::AppendMenu() takes care of updating the
// MenuMinMax values whereas a direct call to ToolBox's ::AppendMenu()
// does not.

void
CAete_EditorWindow::RebuildSuitePopup()
{
	MenuRef    theMenuH = mSuitesPopup->GetMacMenuH();
	ThrowIfNil_(theMenuH);
	
	// Empty the menu	mSuitesPopup->DeleteAllMenuItems();
	UInt16 theCount = ::CountMenuItems( theMenuH );
	while ( theCount > 0 ) {	
		::DeleteMenuItem( theMenuH, theCount-- );
	}
	
	// Install the suite names
	TArrayIterator<CAeteSuite*>	iterator( *mAete->GetSuites() );
	CAeteSuite *	theSuite;
	Str255			theString;

	while (iterator.Next(theSuite)) {
		theSuite->GetName(theString);
		
		if ( theString[0] ) {
			mSuitesPopup->AppendMenu(theString);
		} else {
			mSuitesPopup->AppendMenu("\punnamed suite");
		}
	}
	mSuitesPopup->SetMacMenuH(theMenuH);
	
	mSuitesPopup->Refresh();
}


// ---------------------------------------------------------------------------
//  InstallFlags													[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::InstallFlags(SInt32 inKind, UInt16 inFlags)
{
	SInt32			theCount, i;
	MenuHandle		theMenuH;
	LView *			thePane;
	LPopupButton *	thePopup;
	const UInt16 *	flagsArray;
	
	switch (inKind) {
		case item_AeteDirectOptions:
		thePane = mEventPane;
		theCount = sizeof(AeteDirectFlag)/sizeof(UInt16);
		flagsArray = AeteDirectFlag;
		break;
		
		case item_AeteReplyOptions:
		thePane = mEventPane;
		theCount = sizeof(AeteReplyFlag)/sizeof(UInt16);
		flagsArray = AeteReplyFlag;
		break;
		
		case item_AeteParamOptions:
		thePane = mEventPane;
		theCount = sizeof(AeteParamFlag)/sizeof(UInt16);
		flagsArray = AeteParamFlag;
		break;
		
		case item_AetePropertyOptions:
		thePane = mClassPane;
		theCount = sizeof(AetePropertyFlag)/sizeof(UInt16);
		flagsArray = AetePropertyFlag;
		break;
		
	}
	
	thePopup = dynamic_cast<LPopupButton *>(thePane->FindPaneByID( inKind ));
	ThrowIfNil_(thePopup);
	theMenuH = thePopup->GetMacMenuH();
	for ( i = 0; i < theCount; i++) {
		::MacCheckMenuItem(theMenuH, i+2, ( (inFlags & (1 << flagsArray[i])) > 0 ) );
	}
}


// ---------------------------------------------------------------------------
//  RetrieveFlags													[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::RetrieveFlags(SInt32 inKind, UInt16 & outFlags)
{
	SInt32			theCount, i;
	MenuHandle		theMenuH;
	LView *			thePane;
	LPopupButton *	thePopup;
	CharParameter	markChar = 0;
	const UInt16 *	flagsArray;

	outFlags = 0;
	
	switch (inKind) {
		case item_AeteDirectOptions:
		thePane = mEventPane;
		theCount = sizeof(AeteDirectFlag)/sizeof(UInt16);
		flagsArray = AeteDirectFlag;
		break;
		
		case item_AeteReplyOptions:
		thePane = mEventPane;
		theCount = sizeof(AeteReplyFlag)/sizeof(UInt16);
		flagsArray = AeteReplyFlag;
		break;
		
		case item_AeteParamOptions:
		thePane = mEventPane;
		theCount = sizeof(AeteParamFlag)/sizeof(UInt16);
		flagsArray = AeteParamFlag;
		break;
		
		case item_AetePropertyOptions:
		thePane = mClassPane;
		theCount = sizeof(AetePropertyFlag)/sizeof(UInt16);
		flagsArray = AetePropertyFlag;
		break;
		
	}
	
	thePopup = dynamic_cast<LPopupButton *>(thePane->FindPaneByID( inKind ));
	ThrowIfNil_(thePopup);
	theMenuH = thePopup->GetMacMenuH();
	for ( i = 0; i < theCount; i++) {
		::GetItemMark( theMenuH, i+2, &markChar);
		outFlags |= (markChar == 0) ? 0:(1 << flagsArray[i]);
	}
}


// ---------------------------------------------------------------------------
//  HandleOptionsPopup												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::HandleOptionsPopup(SInt32 inKind, SInt32 inIndex)
{
	LView *			thePane;
	LPopupButton *	thePopup;
	MenuHandle		theMenuH;
	CharParameter	markChar = 0;

	if (inIndex < 2) { return; }
	
	if (inKind == msg_AetePropertyOptions) {
		thePane = mClassPane;
		inKind -= PPob_AeteClassPane;
	} else {
		thePane = mEventPane;
		inKind -= PPob_AeteEventPane;
	}
	
	thePopup = dynamic_cast<LPopupButton *>(thePane->FindPaneByID( inKind ));
	ThrowIfNil_(thePopup);
	theMenuH = thePopup->GetMacMenuH();
	
	::GetItemMark( theMenuH, inIndex, &markChar);
	::MacCheckMenuItem(theMenuH, inIndex, (markChar == 0) );
	thePopup->SetValue(1);
	SetDirty(true);
}


// ---------------------------------------------------------------------------
//  HandleSliderMessage												[public]
// ---------------------------------------------------------------------------
// && inValue != 0

void
CAete_EditorWindow::HandleSliderMessage(SInt32 inKind, SInt32 inValue)
{
	ArrayIndexT			oldIndex;
	CAeteParameter *	theParameter;
	CAeteProperty *		theProperty;
	CAeteElement *		theElement;
	AeteEnumerator		enumerator;
	CAeteEnumeration *	theEnum ;


	switch (inKind) {
		
		case item_AeteItemSlider:
		oldIndex = GetCurrentIndex(mCurrentPanel);
		if (inValue != oldIndex) {
			if (oldIndex != -1) {				
				RetrievePanelValues();
			} 
			SetCurrentIndex(mCurrentPanel, inValue);
			InstallPanelValues();
			// Update only the indicator
			UpdateSlider(inKind, inValue, GetCurrentCount(mCurrentPanel), true);
		}
		break;
		
		
		case item_AeteParamSlider:
		oldIndex = GetCurrentIndex(kind_AeteParameter);
		if (inValue != oldIndex) {
			if (oldIndex != -1) {				
				theParameter = static_cast<CAeteParameter *>( FindCurrentObject( kind_AeteParameter ) );
				RetrieveParameterValues(theParameter);
			} 
			SetCurrentIndex(kind_AeteParameter, inValue);
			theParameter = static_cast<CAeteParameter *>( FindCurrentObject( kind_AeteParameter ) );
			InstallParameterValues(theParameter);
			UpdateSlider(inKind, inValue, GetCurrentCount(kind_AeteParameter), true);
		} 
		break;
		
		
		case item_AetePropertySlider:
		oldIndex = GetCurrentIndex(kind_AeteProperty);
		if (inValue != oldIndex) {
			if (oldIndex != -1) {				
				theProperty = static_cast<CAeteProperty *>( FindCurrentObject( kind_AeteProperty ) );
				RetrievePropertyValues(theProperty);
			} 
			SetCurrentIndex(kind_AeteProperty, inValue);
			theProperty = static_cast<CAeteProperty *>( FindCurrentObject( kind_AeteProperty ) );
			InstallPropertyValues(theProperty);
			UpdateSlider(inKind, inValue, GetCurrentCount(kind_AeteProperty), true);
		} 
		break;
		
		
		case item_AeteElementSlider:
		oldIndex = GetCurrentIndex(kind_AeteElement);
		if (inValue != oldIndex) {
			if (oldIndex != -1) {				
				theElement = static_cast<CAeteElement *>( FindCurrentObject( kind_AeteElement ) );
				RetrieveElementValues(theElement);
			} 
			SetCurrentIndex(kind_AeteElement, inValue);
			theElement = static_cast<CAeteElement *>( FindCurrentObject( kind_AeteElement ) );
			InstallElementValues(theElement);
			UpdateSlider(inKind, inValue, GetCurrentCount(kind_AeteElement), true);
		} 
		break;
		
		
		case item_AeteKeyFormSlider:
		oldIndex = GetCurrentIndex(kind_AeteKeyForm);
		theElement = static_cast<CAeteElement *>( FindCurrentObject( kind_AeteElement ) );
		if (inValue != oldIndex) {
			if (oldIndex != -1) {				
				RetrieveElementValues(theElement);
			} 
			SetCurrentIndex(kind_AeteKeyForm, inValue);
			InstallElementValues(theElement);
		} 
		break;
		
		
		case item_AeteEnumSlider:
		theEnum = static_cast<CAeteEnumeration *>( FindCurrentObject( kind_AeteEnum ) );
		oldIndex = GetCurrentIndex(kind_AeteEnumerator);
		if (inValue != oldIndex) {
			if (oldIndex != -1) {				
				RetrieveEnumeratorValues(enumerator);
				theEnum->SetEnumerator(oldIndex, enumerator);
			} 
			SetCurrentIndex(kind_AeteEnumerator, inValue);
			theEnum->GetEnumerator(inValue, enumerator);
			InstallEnumeratorValues(enumerator);
			UpdateSlider(inKind, inValue, GetCurrentCount(kind_AeteEnumerator), true);
		} 
		break;
		
	}	
}
