// ===========================================================================
// CRezillaPrefs.cp					
// 
//                       Created: 2004-05-17 08:52:16
//             Last modification: 2004-06-02 22:35:24
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


// Application Headers
#include "CRezillaPrefs.h"
#include "CRezillaApp.h"
#include "CRezCompare.h"
#include "RezillaConstants.h"
#include "CRecentItemsMenu.h"
#include "UDialogBoxHandler.h"

// PowerPlant Headers
#include <PP_Messages.h>
#include <PP_Resources.h>

#include <LCaption.h>
#include <LCheckBox.h>
#include <LClipboard.h>
#include <LDialogBox.h>
#include <LEditText.h>
#include <LMultiPanelView.h>
#include <LPageController.h>
#include <LPopupButton.h>
#include <LPopupGroupBox.h>
#include <LPushButton.h>
#include <LRadioGroupView.h>
#include <LStaticText.h>
#include <LStdControl.h>
#include <LString.h>
#include <LTextGroupBox.h>
#include <LThemeTextBox.h>
#include <LWindow.h>

// Universal Headers
#include <CFPreferences.h>
#include <CFNumber.h>

// Standard Headers
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


LDialogBox *	CRezillaPrefs::sPrefsWindow;


// ---------------------------------------------------------------------------
//	¥ CRezillaPrefs											[public]
// ---------------------------------------------------------------------------
//  Object constructor

CRezillaPrefs::CRezillaPrefs()
{
	Initialize();
}


// ---------------------------------------------------------------------------
//	¥ CRezillaPrefs											[public]
// ---------------------------------------------------------------------------
//	Object constructor, specifying SuperCommander

CRezillaPrefs::CRezillaPrefs( LCommander* inSuper )
	: LCommander(inSuper)
{
	Initialize();
}


// ---------------------------------------------------------------------------
//	¥ ~CRezillaPrefs								[public, virtual]
// ---------------------------------------------------------------------------

CRezillaPrefs::~CRezillaPrefs()
{
}


// ---------------------------------------------------------------------------
//	¥ Initialize												[public]
// ---------------------------------------------------------------------------

void
CRezillaPrefs::Initialize()
{
	sPrefsWindow = nil;
	mFile = nil;

	// Ensure default values
	SetDefaultPreferences();
	
	// Retrieve preferences stored on disk
	RetrievePreferences();
}


// ---------------------------------------------------------------------------
//	¥ MakePrefsWindow												  [public]
// ---------------------------------------------------------------------------

void
CRezillaPrefs::MakePrefsWindow()
{	
	sPrefsWindow = (LDialogBox *) (LWindow::CreateWindow( rPPob_PrefsWindow, this ));
	ThrowIfNil_(sPrefsWindow);
}


// ---------------------------------------------------------------------------
//	¥ SetDefaultPreferences												[public]
// ---------------------------------------------------------------------------

void
CRezillaPrefs::SetDefaultPreferences()
{
	// General pane
	mCurrPrefs.general.maxRecent		= 10;
	mCurrPrefs.general.newFork			= fork_datafork;
	// Exporting pane
	mCurrPrefs.exporting.includeBinary	= true;
	mCurrPrefs.exporting.formatDtd		= export_KeyDtd;
	mCurrPrefs.exporting.binaryEncoding	= export_Base64Enc;
	// Comparison pane
	mCurrPrefs.compare.ignoreName		= false;
	mCurrPrefs.compare.ignoreAttributes	= true;
	mCurrPrefs.compare.ignoreData		= false;
	mCurrPrefs.compare.dataDisplay		= compare_hexDisplay;
	// Interface pane
	UTextTraits::LoadSystemTraits(mCurrPrefs.interface.traitsRecord);
	mCurrPrefs.interface.traitsRecord.size = 10;
}


// ---------------------------------------------------------------------------
//	¥ StorePreferences												[public]
// ---------------------------------------------------------------------------

void
CRezillaPrefs::StorePreferences()
{
	CFNumberRef		theValue;
	CFDataRef		theData;
	SInt32			theNumber;

	theNumber = GetPrefValue( kPref_general_maxRecent );
	theValue = CFNumberCreate(NULL, kCFNumberIntType, &theNumber); 
	CFPreferencesSetAppValue(CFSTR("pref_general_maxRecent"), theValue, kCFPreferencesCurrentApplication);
	if (theValue) CFRelease(theValue);

	theNumber = GetPrefValue( kPref_general_newFork );
	theValue = CFNumberCreate(NULL, kCFNumberIntType, &theNumber); 
	CFPreferencesSetAppValue(CFSTR("pref_general_newFork"), theValue, kCFPreferencesCurrentApplication);
	if (theValue) CFRelease(theValue);

	theNumber = GetPrefValue( kPref_export_formatDtd );
	theValue = CFNumberCreate(NULL, kCFNumberIntType, &theNumber); 
	CFPreferencesSetAppValue( CFSTR("pref_export_formatDtd"), theValue, kCFPreferencesCurrentApplication);
	if (theValue) CFRelease(theValue);

	theNumber = GetPrefValue( kPref_export_includeBinary );
	theValue = CFNumberCreate(NULL, kCFNumberIntType, &theNumber); 
	CFPreferencesSetAppValue( CFSTR("pref_export_includeBinary"), theValue, kCFPreferencesCurrentApplication);
	if (theValue) CFRelease(theValue);

	theNumber = GetPrefValue( kPref_export_dataEncoding );
	theValue = CFNumberCreate(NULL, kCFNumberIntType, &theNumber); 
	CFPreferencesSetAppValue( CFSTR("pref_export_dataEncoding"), theValue, kCFPreferencesCurrentApplication);
	if (theValue) CFRelease(theValue);

	theNumber = GetPrefValue( kPref_compare_ignoreName );
	theValue = CFNumberCreate(NULL, kCFNumberIntType, &theNumber); 
	CFPreferencesSetAppValue( CFSTR("pref_compare_ignoreName"), theValue, kCFPreferencesCurrentApplication);
	if (theValue) CFRelease(theValue);

	theNumber = GetPrefValue( kPref_compare_ignoreAttributes );
	theValue = CFNumberCreate(NULL, kCFNumberIntType, &theNumber); 
	CFPreferencesSetAppValue( CFSTR("pref_compare_ignoreAttributes"), theValue, kCFPreferencesCurrentApplication);
	if (theValue) CFRelease(theValue);
	
	theNumber = GetPrefValue( kPref_compare_ignoreData );
	theValue = CFNumberCreate(NULL, kCFNumberIntType, &theNumber); 
	CFPreferencesSetAppValue( CFSTR("pref_compare_ignoreData"), theValue, kCFPreferencesCurrentApplication);
	if (theValue) CFRelease(theValue);	

	theNumber = GetPrefValue( kPref_compare_dataDisplayAs );
	theValue = CFNumberCreate(NULL, kCFNumberIntType, &theNumber);
	CFPreferencesSetAppValue( CFSTR("pref_compare_dataDisplay"), theValue, kCFPreferencesCurrentApplication);
	if (theValue) CFRelease(theValue);
	
	theData = CFDataCreate(NULL, (const UInt8 *)&(mCurrPrefs.interface.traitsRecord), sizeof(TextTraitsRecord));
	CFPreferencesSetAppValue( CFSTR("pref_interface_traitsRecord"), theData, kCFPreferencesCurrentApplication);
	if (theData) CFRelease(theData);
	
	// Flush the prefs to disk
	CFPreferencesAppSynchronize( CFSTR(kRezillaIdentifier) );
}


// ---------------------------------------------------------------------------
//	¥ RetrievePreferences												[public]
// ---------------------------------------------------------------------------

void
CRezillaPrefs::RetrievePreferences()
{
	Boolean 			valueValid, result;
	CFPropertyListRef	theData;
	CFIndex				theSize;
	const UInt8 *		thePtr;
	
	result = CFPreferencesGetAppIntegerValue(CFSTR("pref_general_maxRecent"), CFSTR(kRezillaIdentifier), &valueValid);
	if (valueValid) {
		SetPrefValue( result, kPref_general_maxRecent);
	}
	result = CFPreferencesGetAppIntegerValue(CFSTR("pref_general_newFork"), CFSTR(kRezillaIdentifier), &valueValid);
	if (valueValid) {
		SetPrefValue( result, kPref_general_newFork);
	}
	result = CFPreferencesGetAppIntegerValue(CFSTR("pref_export_formatDtd"), CFSTR(kRezillaIdentifier), &valueValid);
	if (valueValid) {
		SetPrefValue( result, kPref_export_formatDtd);
	}
	result = CFPreferencesGetAppBooleanValue(CFSTR("pref_export_includeBinary"), CFSTR(kRezillaIdentifier), &valueValid);
	if (valueValid) {
		SetPrefValue( result, kPref_export_includeBinary);
	}	
	result = CFPreferencesGetAppIntegerValue(CFSTR("pref_export_dataEncoding"), CFSTR(kRezillaIdentifier), &valueValid);
	if (valueValid) {
		SetPrefValue( result, kPref_export_dataEncoding);
	}	
	result = CFPreferencesGetAppBooleanValue(CFSTR("pref_compare_ignoreName"), CFSTR(kRezillaIdentifier), &valueValid);
	if (valueValid) {
		SetPrefValue( result, kPref_compare_ignoreName);
	}	
	result = CFPreferencesGetAppBooleanValue(CFSTR("pref_compare_ignoreAttributes"), CFSTR(kRezillaIdentifier), &valueValid);
	if (valueValid) {
		SetPrefValue( result, kPref_compare_ignoreAttributes);
	}	
	result = CFPreferencesGetAppBooleanValue(CFSTR("pref_compare_ignoreData"), CFSTR(kRezillaIdentifier), &valueValid);
	if (valueValid) {
		SetPrefValue( result, kPref_compare_ignoreData);
	}
	result = CFPreferencesGetAppIntegerValue(CFSTR("pref_compare_dataDisplay"), CFSTR(kRezillaIdentifier), &valueValid);
	if (valueValid) {
		SetPrefValue( result, kPref_compare_dataDisplayAs);
	}
	theData = CFPreferencesCopyAppValue(CFSTR("pref_interface_traitsRecord"), CFSTR(kRezillaIdentifier));
	if (theData) {
		theSize = CFDataGetLength( (CFDataRef) theData);
		thePtr = CFDataGetBytePtr( (CFDataRef) theData);
		BlockMoveData(thePtr, &(mCurrPrefs.interface.traitsRecord), theSize);
		::GetFNum(mCurrPrefs.interface.traitsRecord.fontName, &mCurrPrefs.interface.traitsRecord.fontNumber);
		CFRelease(theData);
	}
}


// ---------------------------------------------------------------------------
//	¥ SetPrefValue												[public]
// ---------------------------------------------------------------------------

void
CRezillaPrefs::SetPrefValue(SInt32 inPrefValue, SInt32 inConstant, SInt32 inPrefType)
{
	switch (inConstant) {
		
	  case kPref_general_maxRecent:
		if (inPrefType == prefsType_Temp) {
			mTempPrefs.general.maxRecent = inPrefValue ;
		} else {
			mCurrPrefs.general.maxRecent = inPrefValue ;
		}	
		break;
		
	  case kPref_general_newFork:
		if (inPrefType == prefsType_Temp) {
			mTempPrefs.general.newFork = inPrefValue ;
		} else {
			mCurrPrefs.general.newFork = inPrefValue ;
		}	
		break;
		
	  case kPref_export_formatDtd:
		if (inPrefType == prefsType_Temp) {
			mTempPrefs.exporting.formatDtd = inPrefValue ;
		} else {
			mCurrPrefs.exporting.formatDtd = inPrefValue ;
		}	
		break;
		
	  case kPref_export_includeBinary:
		if (inPrefType == prefsType_Temp) {
			mTempPrefs.exporting.includeBinary = inPrefValue ;
		} else {
			mCurrPrefs.exporting.includeBinary = inPrefValue ;
		}	
		break;
		
	  case kPref_export_dataEncoding:
		if (inPrefType == prefsType_Temp) {
			mTempPrefs.exporting.binaryEncoding = inPrefValue ;
		} else {
			mCurrPrefs.exporting.binaryEncoding = inPrefValue ;
		}	
		break;
		
	  case kPref_compare_ignoreName:
		if (inPrefType == prefsType_Temp) {
			mTempPrefs.compare.ignoreName = inPrefValue ;
		} else {
			mCurrPrefs.compare.ignoreName = inPrefValue ;
		}	
		break;
		
	  case kPref_compare_ignoreAttributes:
		if (inPrefType == prefsType_Temp) {
			mTempPrefs.compare.ignoreAttributes = inPrefValue ;
		} else {
			mCurrPrefs.compare.ignoreAttributes = inPrefValue ;
		}	
		break;
		
	  case kPref_compare_ignoreData:
		if (inPrefType == prefsType_Temp) {
			mTempPrefs.compare.ignoreData = inPrefValue ;
		} else {
			mCurrPrefs.compare.ignoreData = inPrefValue ;
		}	
		break;
		
	  case kPref_compare_dataDisplayAs:
		if (inPrefType == prefsType_Temp) {
			mTempPrefs.compare.dataDisplay = inPrefValue ;
		} else {
			mCurrPrefs.compare.dataDisplay = inPrefValue ;
		}	
		break;
	}	
}


// ---------------------------------------------------------------------------
//	¥ GetPrefValue												[public]
// ---------------------------------------------------------------------------

SInt32
CRezillaPrefs::GetPrefValue(SInt32 inConstant, SInt32 inPrefType)
{
	SInt32 theValue = 0;
	
	switch (inConstant) {
		
	  case kPref_general_maxRecent:
		if (inPrefType == prefsType_Temp) {
			theValue = mTempPrefs.general.maxRecent;
		} else {
			theValue = mCurrPrefs.general.maxRecent;
		}	
		break;
		
	  case kPref_general_newFork:
		if (inPrefType == prefsType_Temp) {
			theValue = mTempPrefs.general.newFork;
		} else {
			theValue = mCurrPrefs.general.newFork;
		}	
		break;
		
	  case kPref_export_formatDtd:
		if (inPrefType == prefsType_Temp) {
			theValue = mTempPrefs.exporting.formatDtd;
		} else {
			theValue = mCurrPrefs.exporting.formatDtd;
		}	
		break;
		
	  case kPref_export_includeBinary:
		if (inPrefType == prefsType_Temp) {
			theValue = mTempPrefs.exporting.includeBinary;
		} else {
			theValue = mCurrPrefs.exporting.includeBinary;
		}	
		break;
		
	  case kPref_export_dataEncoding:
		if (inPrefType == prefsType_Temp) {
			theValue = mTempPrefs.exporting.binaryEncoding;
		} else {
			theValue = mCurrPrefs.exporting.binaryEncoding;
		}	
		break;
		
	  case kPref_compare_ignoreName:
		if (inPrefType == prefsType_Temp) {
			theValue = mTempPrefs.compare.ignoreName;
		} else {
			theValue = mCurrPrefs.compare.ignoreName;
		}	
		break;
		
	  case kPref_compare_ignoreAttributes:
		if (inPrefType == prefsType_Temp) {
			theValue = mTempPrefs.compare.ignoreAttributes;
		} else {
			theValue = mCurrPrefs.compare.ignoreAttributes;
		}	
		break;
		
	  case kPref_compare_ignoreData:
		if (inPrefType == prefsType_Temp) {
			theValue = mTempPrefs.compare.ignoreData;
		} else {
			theValue = mCurrPrefs.compare.ignoreData;
		}	
		break;
		
	  case kPref_compare_dataDisplayAs:
		if (inPrefType == prefsType_Temp) {
			theValue = mTempPrefs.compare.dataDisplay;
		} else {
			theValue = mCurrPrefs.compare.dataDisplay;
		}	
		break;
	}	
	
	return theValue;
}


// ---------------------------------------------------------------------------
//	¥ GetStyleElement												[public]
// ---------------------------------------------------------------------------
// Default value for inPrefType is 'prefsType_Temp'

TextTraitsRecord 	
CRezillaPrefs::GetStyleElement(SInt32 inPrefType)
{
	if (inPrefType == prefsType_Temp) {
		return mTempPrefs.interface.traitsRecord;
	} else {
		return mCurrPrefs.interface.traitsRecord;
	}	
}


// ---------------------------------------------------------------------------
//	¥ LoadStyleElement												[public]
// ---------------------------------------------------------------------------

void
CRezillaPrefs::LoadStyleElement(TextTraitsPtr inTraitsRecPtr)
{
	::BlockMoveData(inTraitsRecPtr, &mCurrPrefs.interface.traitsRecord, sizeof(TextTraitsRecord));
}


// ---------------------------------------------------------------------------
//	¥ SetStyleElement												[public]
// ---------------------------------------------------------------------------

void
CRezillaPrefs::SetStyleElement(SInt16 inStyleValue, 
								SInt32 inElementType,
								SInt32 inPrefType) 
{
	switch (inElementType) {
		
	  case style_fontType:
		if (inPrefType == prefsType_Temp) {
			mTempPrefs.interface.traitsRecord.fontNumber = inStyleValue ;
		} else {
			mCurrPrefs.interface.traitsRecord.fontNumber = inStyleValue ;
		}	
		break;
		
	  case style_sizeType:
		if (inPrefType == prefsType_Temp) {
			mTempPrefs.interface.traitsRecord.size = inStyleValue ;
		} else {
			mCurrPrefs.interface.traitsRecord.size = inStyleValue ;
		}	
		break;
		
	  case style_faceType:
		if (inPrefType == prefsType_Temp) {
			mTempPrefs.interface.traitsRecord.style = inStyleValue ;
		} else {
			mCurrPrefs.interface.traitsRecord.style = inStyleValue ;
		}	
		break;
	}
}


// ---------------------------------------------------------------------------
//	¥ ValidateTempPrefs												[public]
// ---------------------------------------------------------------------------

void
CRezillaPrefs::ValidateTempPrefs() 
{
	::BlockMoveData(&mTempPrefs, &mCurrPrefs, sizeof(SRezillaPrefs));
}


// ---------------------------------------------------------------------------
//	¥ InitTempPrefs												[public]
// ---------------------------------------------------------------------------

void
CRezillaPrefs::InitTempPrefs() 
{
	::BlockMoveData(&mCurrPrefs, &mTempPrefs, sizeof(SRezillaPrefs));
}


// ---------------------------------------------------------------------------
//	¥ PrefsHaveChanged											[public]
// ---------------------------------------------------------------------------

Boolean
CRezillaPrefs::PrefsHaveChanged() 
{
	return ( memcmp( &mCurrPrefs, &mTempPrefs, sizeof(SRezillaPrefs) ) != 0);
}


// ---------------------------------------------------------------------------
//	¥ ApplyStylePrefs										[public]
// ---------------------------------------------------------------------------
// Apply the style changes to all the windows listening.

void
CRezillaPrefs::ApplyStylePrefs() 
{
	BroadcastMessage(msg_StylePrefsChanged, &mCurrPrefs);
}


// ---------------------------------------------------------------------------
//	¥ RunPrefsWindow											[public]
// ---------------------------------------------------------------------------
//	Display the preferences window for the application

void
CRezillaPrefs::RunPrefsWindow()
{
	LCheckBox *		theCheckBox;
	LPopupButton *	thePopup;
	long			theLong;
	Str255			theString;
	LStr255			theLine( "\p" );
	Boolean 		inPrefsLoop = true;
	LEditText *		theEditField;
	SInt32 			theSize, itemIndex;
	SInt16			theFontNum;
	TextTraitsRecord theCurrTraits;
	
	StDialogBoxHandler	theHandler(rPPob_PrefsWindow, this);
	LDialogBox *		theDialog = theHandler.GetDialog();
	Assert_(theDialog != nil);
	SetPrefsWindow(theDialog);

	InitTempPrefs();
	
	//    Get the elements
	// -------------------
	LPageController* thePageCtrl = dynamic_cast<LPageController*>(theDialog->FindPaneByID(item_PrefsPageController));
	ThrowIfNil_(thePageCtrl);
	
	LMultiPanelView* theMPV = dynamic_cast<LMultiPanelView*>(theDialog->FindPaneByID(item_PrefsMultiPanelView));
	ThrowIfNil_(theMPV);
	
	// Create the panels before we call them
	theMPV->CreateAllPanels();
	
	LView* theGeneralPane = theMPV->GetPanel(mpv_General);
	ThrowIfNil_(theGeneralPane);
	
	LView* theExportPane = theMPV->GetPanel(mpv_Export);
	ThrowIfNil_(theExportPane);
	
	LView* theComparePane = theMPV->GetPanel(mpv_Compare);
	ThrowIfNil_(theComparePane);
	
	LView* theInterfacePane = theMPV->GetPanel(mpv_Interface);
	ThrowIfNil_(theInterfacePane);
	
	LRadioGroupView * theNewMapRGV = dynamic_cast<LRadioGroupView *>(theGeneralPane->FindPaneByID( item_GenPrefsNewMapRgbx ));
	ThrowIfNil_(theNewMapRGV);
	
	LRadioGroupView * theDtdRGV = dynamic_cast<LRadioGroupView *>(theExportPane->FindPaneByID( item_ExpPrefsDtdRgbx ));
	ThrowIfNil_(theDtdRGV);
	
	LRadioGroupView * theEncodingRGV = dynamic_cast<LRadioGroupView *>(theExportPane->FindPaneByID( item_ExpPrefsEncRgbx ));
	ThrowIfNil_(theEncodingRGV);
	
	LRadioGroupView * theDisplayRGV = dynamic_cast<LRadioGroupView *>(theComparePane->FindPaneByID( item_CompPrefsDisplayRgbx ));
	ThrowIfNil_(theDisplayRGV);
	
	theCurrTraits = GetStyleElement( prefsType_Curr );

	//    Link Listeners and Broadcasters
	// ----------------------------------
	// Partly done in the StDialogBoxHandler constructor

	thePageCtrl->AddListener(theMPV);
	thePageCtrl->AddListener(&theHandler);
	
	// Note : the rRidL_PrefsWindow resource does not contain the controls of
	// the various MPV's subpanels. We have to do that explicitly.
	UReanimator::LinkListenerToBroadcasters( &theHandler, theGeneralPane, rPPob_PrefsGeneralPane );
	UReanimator::LinkListenerToBroadcasters( &theHandler, theExportPane, rPPob_PrefsExportPane );
	UReanimator::LinkListenerToBroadcasters( &theHandler, theComparePane, rPPob_PrefsComparePane );
	UReanimator::LinkListenerToBroadcasters( &theHandler, theInterfacePane, rPPob_PrefsInterfacePane );
	
	while (inPrefsLoop) {
		
		//    Setup the controls values
		// ----------------------------		
		theNewMapRGV->SetCurrentRadioID( GetPrefValue( kPref_general_newFork ) + item_GenPrefsNewMapRgbx );
		theDtdRGV->SetCurrentRadioID( GetPrefValue( kPref_export_formatDtd ) + item_ExpPrefsDtdRgbx );
		theEncodingRGV->SetCurrentRadioID( GetPrefValue( kPref_export_dataEncoding ) + item_ExpPrefsEncRgbx );
		theDisplayRGV->SetCurrentRadioID( GetPrefValue( kPref_compare_dataDisplayAs ) + item_CompPrefsDisplayRgbx );

		theEditField = dynamic_cast<LEditText *>(theGeneralPane->FindPaneByID( item_GenPrefsMaxRecent ));
		ThrowIfNil_( theEditField );
		theEditField->SetValue(  GetPrefValue( kPref_general_maxRecent ) );

		theCheckBox = dynamic_cast<LCheckBox *>(theExportPane->FindPaneByID( item_ExpPrefsInclBinData ));
		ThrowIfNil_( theCheckBox );
		theCheckBox->SetValue(  GetPrefValue( kPref_export_includeBinary ) );

		theCheckBox = dynamic_cast<LCheckBox *>(theComparePane->FindPaneByID( item_CompPrefsIgnName ));
		ThrowIfNil_( theCheckBox );
		theCheckBox->SetValue(  GetPrefValue( kPref_compare_ignoreName ) );

		theCheckBox = dynamic_cast<LCheckBox *>(theComparePane->FindPaneByID( item_CompPrefsIgnAttr ));
		ThrowIfNil_( theCheckBox );
		theCheckBox->SetValue(  GetPrefValue( kPref_compare_ignoreAttributes ) );

		theCheckBox = dynamic_cast<LCheckBox *>(theComparePane->FindPaneByID( item_CompPrefsIgnData ));
		ThrowIfNil_( theCheckBox );
		theCheckBox->SetValue(  GetPrefValue( kPref_compare_ignoreData ) );

		thePopup = dynamic_cast<LPopupButton *> (theInterfacePane->FindPaneByID( item_UIPrefsFontsMenu ));
		ThrowIfNil_( thePopup );
		theFontNum = theCurrTraits.fontNumber;
		thePopup->SetValue( FontIndexFromFontNum(thePopup, theFontNum) );
		
		thePopup = dynamic_cast<LPopupButton *> (theInterfacePane->FindPaneByID( item_UIPrefsSizeMenu ));
		ThrowIfNil_( thePopup );
		theSize = theCurrTraits.size;
		thePopup->SetValue( SizeIndexFromSizeValue(thePopup, theSize) );

		theDialog->Show();
		
		MessageT theMessage;
		while (true) {
			theMessage = theHandler.DoDialog();
			if (msg_OK == theMessage || msg_Cancel == theMessage) {
				inPrefsLoop = false;
				break;
			} else if (msg_PrefsRevert == theMessage) {
				break;  // Breaks out from the inner 'while' but still in the inPrefsLoop 'while'
			} else {
				switch (theMessage) {
					
				  case msg_CompPrefsIgnName:
					theCheckBox = dynamic_cast<LCheckBox *>(theComparePane->FindPaneByID( theMessage - rPPob_PrefsComparePane ));
					SetPrefValue( theCheckBox->GetValue(), kPref_compare_ignoreName, prefsType_Temp);
					break;
																				
				  case msg_CompPrefsIgnAttr:
					theCheckBox = dynamic_cast<LCheckBox *>(theComparePane->FindPaneByID( theMessage - rPPob_PrefsComparePane ));
					SetPrefValue( theCheckBox->GetValue(), kPref_compare_ignoreAttributes, prefsType_Temp);
					break;
																				
				  case msg_CompPrefsIgnData:
					theCheckBox = dynamic_cast<LCheckBox *>(theComparePane->FindPaneByID( theMessage - rPPob_PrefsComparePane ));
					SetPrefValue( theCheckBox->GetValue(), kPref_compare_ignoreData, prefsType_Temp);
					break;
																				
				  case msg_ExpPrefsInclBinData:
					theCheckBox = dynamic_cast<LCheckBox *>(theExportPane->FindPaneByID( theMessage - rPPob_PrefsExportPane ));
					SetPrefValue( theCheckBox->GetValue(), kPref_export_includeBinary, prefsType_Temp);
					break;
																				
				  case msg_GenPrefsResetRecent:
					CRezillaApp::sRecentItemsAttachment->Reset();
				    break;
																				
				  case msg_GenPrefsMaxRecent:
					theEditField = dynamic_cast<LEditText *>(theGeneralPane->FindPaneByID( item_GenPrefsMaxRecent ));
					theEditField->GetDescriptor(theString);
					if (theString[0]) {
						::StringToNum(theString, &theLong);
					} else {
						theLong = 10;
					}
					SetPrefValue( theLong, kPref_general_maxRecent, prefsType_Temp);
				    break;
																				
				  case msg_ControlClicked:
				  case msg_ExpPrefsKeyDtd:
				  case msg_ExpPrefsAttrDtd:
				  case msg_ExpPrefsHexEnc:
				  case msg_ExpPrefsBase64Enc: {
						// DoDialog() returns the *last* message which, in the case of a RadioGroup,
						// is msg_ControlClicked. So we fail to receive the messages sent just before
						// by the individual controls. 
				  		PaneIDT theCurrentRadioID;
						theCurrentRadioID = theNewMapRGV->GetCurrentRadioID();
						SetPrefValue( theCurrentRadioID - item_GenPrefsNewMapRgbx, kPref_general_newFork, prefsType_Temp);

						theCurrentRadioID = theDtdRGV->GetCurrentRadioID();
						SetPrefValue( theCurrentRadioID - item_ExpPrefsDtdRgbx, kPref_export_formatDtd, prefsType_Temp);

						theCurrentRadioID = theEncodingRGV->GetCurrentRadioID();
						SetPrefValue( theCurrentRadioID - item_ExpPrefsEncRgbx, kPref_export_dataEncoding, prefsType_Temp);

						theCurrentRadioID = theDisplayRGV->GetCurrentRadioID();
						SetPrefValue( theCurrentRadioID - item_CompPrefsDisplayRgbx, kPref_compare_dataDisplayAs, prefsType_Temp);
						break;
				  }
				  
				  case msg_UIPrefsFontsMenu:
					// Get the popup menu.
					thePopup = dynamic_cast<LPopupButton *> (theInterfacePane->FindPaneByID( item_UIPrefsFontsMenu ));
					ThrowIfNil_( thePopup );
					// Get the name of the font.
					::GetMenuItemText( thePopup->GetMacMenuH(), thePopup->GetValue(), theString );
					LString::CopyPStr(theString, mTempPrefs.interface.traitsRecord.fontName);
					::GetFNum(theString, &theFontNum);
					SetStyleElement(theFontNum, style_fontType, prefsType_Temp);
					break;
					
				  case msg_UIPrefsSizeMenu:
					theSize = GetStyleElement().size;
					// Get the popup menu.
					thePopup = dynamic_cast<LPopupButton *> (theInterfacePane->FindPaneByID( item_UIPrefsSizeMenu ));
					ThrowIfNil_( thePopup );
					// Get the value of the item.
					itemIndex = thePopup->GetValue();
					if (itemIndex == kLastSizeMenuItem + 2) {
						// This is the 'Other' item
						if (UModalDialogs::AskForOneNumber(sPrefsWindow, rPPob_OtherSize, item_OtherSizeField, theSize)) {
							if (theSize == 0) {theSize = 10;}
							// If they match, no need to use 'Other' item
							if (FontSizeExists(thePopup, theSize, itemIndex)) {
								thePopup->SetValue(itemIndex);
							} else {
								// Modify the text of the 'Other' item.
								theLine = "\pOther" ;
								Str255	theSizeString;
								::NumToString( theSize, theSizeString );
								// Append the current size
								theLine += "\p (";
								theLine += theSizeString;
								theLine += "\p)É";
								// Set the menu item text.
								::SetMenuItemText( thePopup->GetMacMenuH(), kLastSizeMenuItem + 2, theLine );					
							}
						}
					} else {
						::GetMenuItemText( thePopup->GetMacMenuH(), thePopup->GetValue(), theString );
						::StringToNum( theString, &theSize );
					}
					SetStyleElement( (SInt16) theSize, style_sizeType, prefsType_Temp);
					break;
				}	
			}
		}
		
		// if we hit ok, save the pref info
		if (msg_OK == theMessage) {
			if ( PrefsHaveChanged() ) {
				Boolean stylechanged = (memcmp( &mCurrPrefs.interface, &mTempPrefs.interface, sizeof(SInterfacePrefs) ) != 0);
				ValidateTempPrefs();
				if (stylechanged) {
					ApplyStylePrefs();
				}
				UpdateVars();
			}
		}
	}
}


// ---------------------------------------------------------------------------
//	¥ UpdateVars												[private]
// ---------------------------------------------------------------------------

void
CRezillaPrefs::UpdateVars() 
{
	CRezCompare::sIgnoreNames = GetPrefValue(kPref_compare_ignoreName);
	CRezCompare::sIgnoreAttrs = GetPrefValue(kPref_compare_ignoreAttributes);
	CRezCompare::sIgnoreData = GetPrefValue(kPref_compare_ignoreData);
	
	CRezillaApp::sRecentItemsAttachment->SetMaxRecentItems( GetPrefValue(kPref_general_maxRecent) );
}



// ---------------------------------------------------------------------------
//	¥ FontSizeExists											[private]
// ---------------------------------------------------------------------------

OSStatus
CRezillaPrefs::FontSizeExists(LPopupButton * inPopup, SInt32 inSize, SInt32 &outItemIndex)
{
	OSErr	itemMatches = 0;
	SInt16	i;
	Str255	theMenuText;
	SInt32	theMenuSize;
	
	// See if inSize matches some menu item
	for ( i= kFirstSizeMenuItem ; i<= kLastSizeMenuItem ; i++ ) {
		::GetMenuItemText( inPopup->GetMacMenuH(), i, theMenuText );
		::StringToNum( theMenuText, &theMenuSize );
		if ( inSize == theMenuSize)
		{
			itemMatches = true;
			outItemIndex = i;
			break;
		}	
	}
	
	return itemMatches;
}


// ---------------------------------------------------------------------------
//	¥ FontIndexFromFontNum											[private]
// ---------------------------------------------------------------------------

SInt32
CRezillaPrefs::FontIndexFromFontNum(LPopupButton * inPopup, SInt16 inFNum) 
{
	SInt32	i;
	SInt16	theFontNum;
	Str255	theMenuText;
	Boolean foundIt = false;
	MenuRef	theMenuRef = inPopup->GetMacMenuH();
	
	// See if inFNum matches some menu item
	for ( i = 1 ; i<= ::CountMenuItems(theMenuRef) ; i++ ) {
		::GetMenuItemText( theMenuRef, i, theMenuText );
		::GetFNum(theMenuText,&theFontNum);
		if ( inFNum == theFontNum) {
			foundIt = true;
			break;
		}	
	}
	if (!foundIt) {
		// Put the OS Application font
		return ::GetAppFont();
	}
	
	return i;
}


// ---------------------------------------------------------------------------
//	¥ SizeIndexFromSizeValue											[private]
// ---------------------------------------------------------------------------

SInt32
CRezillaPrefs::SizeIndexFromSizeValue(LPopupButton * inPopup, SInt16 inSize) 
{
	SInt32	i;
	SInt32	theSize;
	Str255	theSizeString;
	Boolean foundIt = false;
	MenuRef	theMenuRef = inPopup->GetMacMenuH();
	
	// See if inSize matches some menu item
	for ( i = 1 ; i<= ::CountMenuItems(theMenuRef) ; i++ ) {
		::GetMenuItemText( theMenuRef, i, theSizeString );
		::StringToNum( theSizeString, &theSize );
		if ( inSize == theSize) {
			foundIt = true;
			break;
		}	
	}
	if (!foundIt) {
		// Put the value in the 'Other' item
		LStr255	theLine( "\pOther (" );
		theLine += theSizeString;
		theLine += "\p)É";
		// Set the menu item text.
		::SetMenuItemText( inPopup->GetMacMenuH(), kLastSizeMenuItem + 2, theLine );					
		return kLastSizeMenuItem + 2;
	}
	
	return i;
}


