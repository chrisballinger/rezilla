// ===========================================================================
// CAete_WindowValues.cp
// 
//                       Created: 2005-01-25 09:01:07
//             Last modification: 2005-01-28 09:19:29
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
#include <LTextColumn.h>
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
//  InstallSuiteValues												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::InstallSuiteValues()
{
	Str255		theString, theName, theDescription;
	UInt16		theLevel = 0, theVersion = 0;
	OSType		theID;
	LEditText *	theEditText;
	Boolean		disableIt = false;
	
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
	if (!disableIt) {
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
		return;
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

	InstallFlags(item_AeteDirectOptions, theDirectFlags);

	// Reply
	theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteReplyType ));
	ThrowIfNil_( theEditText );
	UMiscUtils::OSTypeToPString(theReplyType, theString);
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteReplyDescr ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theReplyDescription);
	
	InstallFlags(item_AeteReplyOptions, theReplyFlags);

	// Current parameter
	theTGB = dynamic_cast<LTextGroupBox *> (mEventPane->FindPaneByID( item_AeteParamBox ));

	if (inEvent && inEvent->GetParameters()->FetchItemAt(index, theParameter) ) {
		InstallParameterValues(theParameter);
		theTGB->Enable();
		theValue = index;
		theTotal = inEvent->CountParameters();
	} else {
		theTGB->Disable();
		theValue = 0;
		theTotal = 0;
	}
	
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
		
	theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteParamName ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theName);

	theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteParamKeyword ));
	ThrowIfNil_( theEditText );
	if (!disableIt) {
		UMiscUtils::OSTypeToPString(theKeyword, theString);
	} 
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteParamType ));
	ThrowIfNil_( theEditText );
	if (!disableIt) {
		UMiscUtils::OSTypeToPString(theType, theString);
	} 
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteParamDescr ));
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
		return;
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
		theValue = propIndex;
		theTotal = inClass->CountProperties();
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
		theValue = elemIndex;
		theTotal = inClass->CountElements();
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

	InstallFlags(item_AetePropertyOptions, theFlags);

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
		return;
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
		return;
	}
	
	enumerator.name[0] = 0;
	enumerator.type = 0;
	enumerator.description[0] = 0;

	theEditText = dynamic_cast<LEditText *> (mEnumerationPane->FindPaneByID( item_AeteEnumerationID ));
	ThrowIfNil_( theEditText );
	UMiscUtils::OSTypeToPString(theID, theString);
	theEditText->SetDescriptor(theString);

	// Current enumerator
	theTGB = dynamic_cast<LTextGroupBox *> (mEnumerationPane->FindPaneByID( item_AeteEnumBox ));
	
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
		
	theEditText = dynamic_cast<LEditText *> (mEnumerationPane->FindPaneByID( item_AeteEnumName ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(inEnumerator.name);

	theEditText = dynamic_cast<LEditText *> (mEnumerationPane->FindPaneByID( item_AeteEnumType ));
	ThrowIfNil_( theEditText );
	if (inEnumerator.type != 0) {
		UMiscUtils::OSTypeToPString(inEnumerator.type, theString);
	} 
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *> (mEnumerationPane->FindPaneByID( item_AeteEnumDescr ));
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

	RetrieveFlags(item_AeteDirectOptions, theDirectFlags);

	// Reply
	theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteReplyType ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, theReplyType);

	theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteReplyDescr ));
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
	
	theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteParamName ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theName);

	theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteParamKeyword ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, theKeyword);

	theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteParamType ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, theType);

	theEditText = dynamic_cast<LEditText *> (mEventPane->FindPaneByID( item_AeteParamDescr ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theDescription);
		
	RetrieveFlags(item_AeteParamOptions, theFlags);

	inParameter->SetValues(theName, theKeyword, theType,
								theDescription, theFlags);
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
	
	RetrieveFlags(item_AetePropertyOptions, theFlags);

	inProperty->SetValues(theName, theKeyword, theType,
							theDescription, theFlags);

}


// ---------------------------------------------------------------------------
//  RetrieveElementValues												[public]
// ---------------------------------------------------------------------------

void
CAete_EditorWindow::RetrieveElementValues(CAeteElement * inElement)
{
	Str255			theString;
	OSType 			theID;
	LEditText *		theEditText;
	LTextColumn *	theTable;
	

	theEditText = dynamic_cast<LEditText *> (mClassPane->FindPaneByID( item_AeteElementID ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, theID);

	inElement->SetID(theID);
	
	theTable = dynamic_cast<LTextColumn *> (mClassPane->FindPaneByID( item_AeteKeyFormsTable ));
	ThrowIfNil_( theEditText );

// 		theTable->GetKeyForms();

	
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

	theEditText = dynamic_cast<LEditText *> (mEnumerationPane->FindPaneByID( item_AeteEnumerationID ));
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

	theEditText = dynamic_cast<LEditText *> (mEnumerationPane->FindPaneByID( item_AeteEnumName ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(outEnumerator.name);

	theEditText = dynamic_cast<LEditText *> (mEnumerationPane->FindPaneByID( item_AeteEnumType ));
	ThrowIfNil_( theEditText );
	theEditText->GetDescriptor(theString);
	UMiscUtils::PStringToOSType( theString, outEnumerator.type );

	theEditText = dynamic_cast<LEditText *> (mEnumerationPane->FindPaneByID( item_AeteEnumDescr ));
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
	
	// Empty the menu
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
			mSuitesPopup->AppendMenu("\p<unnamed suite>");
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
	SInt32			theCount, i, val;
	MenuHandle		theMenuH;
	LPopupButton *	thePopup;
	Boolean			markIt;
	
	switch (inKind) {
		case item_AeteDirectOptions:
		thePopup = dynamic_cast<LPopupButton *> (mEventPane->FindPaneByID( inKind ));
		ThrowIfNil_(thePopup);
		theMenuH = thePopup->GetMacMenuH();
		theCount = sizeof(AeteDirectFlag)/sizeof(UInt16);
		for ( i = 0; i < theCount; i++) {
			val = inFlags & (1 << AeteDirectFlag[i]);
			
			markIt =  ( val > 0 );
			
			::MacCheckMenuItem(theMenuH, i+2, markIt );
		}
		break;
		
		case item_AeteReplyOptions:
		thePopup = dynamic_cast<LPopupButton *> (mEventPane->FindPaneByID( inKind ));
		ThrowIfNil_(thePopup);
		theMenuH = thePopup->GetMacMenuH();
		theCount = sizeof(AeteReplyFlag)/sizeof(UInt16);
		for ( i = 0; i < theCount; i++) {
			::MacCheckMenuItem(theMenuH, i+2, ( (inFlags & (1 << AeteReplyFlag[i])) > 0 ) );
		}
		break;
		
		case item_AeteParamOptions:
		thePopup = dynamic_cast<LPopupButton *> (mEventPane->FindPaneByID( inKind ));
		ThrowIfNil_(thePopup);
		theMenuH = thePopup->GetMacMenuH();
		theCount = sizeof(AeteParamFlag)/sizeof(UInt16);
		for ( i = 0; i < theCount; i++) {
			::MacCheckMenuItem(theMenuH, i+2, ( (inFlags & (1 << AeteParamFlag[i])) > 0 ) );
		}
		break;
		
		case item_AetePropertyOptions:
		thePopup = dynamic_cast<LPopupButton *> (mClassPane->FindPaneByID( inKind ));
		ThrowIfNil_(thePopup);
		theMenuH = thePopup->GetMacMenuH();
		theCount = sizeof(AetePropertyFlag)/sizeof(UInt16);
		for ( i = 0; i < theCount; i++) {
			::MacCheckMenuItem(theMenuH, i+2, ( (inFlags & (1 << AetePropertyFlag[i])) > 0 ) );
		}
		break;
		
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
	LPopupButton *	thePopup;
	CharParameter	markChar = 0;

	outFlags = 0;
	
	switch (inKind) {
		case item_AeteDirectOptions:
		thePopup = dynamic_cast<LPopupButton *> (mEventPane->FindPaneByID( inKind ));
		ThrowIfNil_(thePopup);
		theMenuH = thePopup->GetMacMenuH();
		theCount = sizeof(AeteDirectFlag)/sizeof(UInt16);
		for ( i = 0; i < theCount; i++) {
			::GetItemMark( theMenuH, i+2, &markChar);
			outFlags |= (markChar == 0) ? 0:(1 << AeteDirectFlag[i]);
		}
		break;
		
		case item_AeteReplyOptions:
		thePopup = dynamic_cast<LPopupButton *> (mEventPane->FindPaneByID( inKind ));
		ThrowIfNil_(thePopup);
		theMenuH = thePopup->GetMacMenuH();
		theCount = sizeof(AeteReplyFlag)/sizeof(UInt16);
		for ( i = 0; i < theCount; i++) {
			::GetItemMark( theMenuH, i+2, &markChar);
			outFlags |= (markChar == 0) ? 0:(1 << AeteReplyFlag[i]);
		}
		break;
		
		case item_AeteParamOptions:
		thePopup = dynamic_cast<LPopupButton *> (mEventPane->FindPaneByID( inKind ));
		ThrowIfNil_(thePopup);
		theMenuH = thePopup->GetMacMenuH();
		theCount = sizeof(AeteParamFlag)/sizeof(UInt16);
		for ( i = 0; i < theCount; i++) {
			::GetItemMark( theMenuH, i+2, &markChar);
			outFlags |= (markChar == 0) ? 0:(1 << AeteParamFlag[i]);
		}
		break;
		
		case item_AetePropertyOptions:
		thePopup = dynamic_cast<LPopupButton *> (mClassPane->FindPaneByID( inKind ));
		ThrowIfNil_(thePopup);
		theMenuH = thePopup->GetMacMenuH();
		theCount = sizeof(AetePropertyFlag)/sizeof(UInt16);
		for ( i = 0; i < theCount; i++) {
			::GetItemMark( theMenuH, i+2, &markChar);
			outFlags |= (markChar == 0) ? 0:(1 << AetePropertyFlag[i]);
		}
		break;
		
	}
}
