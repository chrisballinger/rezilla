// ===========================================================================
// CRezillaPrefs.cp					
// 
//                       Created: 2004-05-17 08:52:16
//             Last modification: 2005-09-20 15:00:59
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004-2005
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
#include "UMiscUtils.h"
#include "UMessageDialogs.h"
#include "CThreeButtonsBox.h"

// PowerPlant Headers
#include <PP_Messages.h>
#include <PP_Resources.h>

#include <LCaption.h>
#include <LCheckBox.h>
#include <LCheckBoxGroupBox.h>
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


CThreeButtonsBox *	CRezillaPrefs::sPrefsWindow;
ArrayIndexT		CRezillaPrefs::sCurrentPrefsPane = 1;
SRezillaPrefs	CRezillaPrefs::sTempPrefs;
SRezillaPrefs	CRezillaPrefs::sCurrPrefs;


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

	// Ensure default values
	SetDefaultPreferences();
	
	// Retrieve preferences stored on disk
	RetrievePreferences();
	
	// Calculate some global metric values from the text traits 
	// and set some statics.
	UMiscUtils::MetricsFromTraits( &sCurrPrefs.interface.traitsRecord );	
	CRezCompare::SetIgnoreNames(GetPrefValue(kPref_compare_ignoreName));
	CRezCompare::SetIgnoreAttrs(GetPrefValue(kPref_compare_ignoreAttributes));
	CRezCompare::SetIgnoreData(GetPrefValue(kPref_compare_ignoreData));
}


// ---------------------------------------------------------------------------
//	¥ MakePrefsWindow												  [public]
// ---------------------------------------------------------------------------

void
CRezillaPrefs::MakePrefsWindow()
{	
	sPrefsWindow = (CThreeButtonsBox *) (LWindow::CreateWindow( PPob_PrefsWindow, this ));
	ThrowIfNil_(sPrefsWindow);
}


// ---------------------------------------------------------------------------
//	¥ SetDefaultPreferences											[public]
// ---------------------------------------------------------------------------

void
CRezillaPrefs::SetDefaultPreferences()
{
	// General pane
	sCurrPrefs.general.maxRecent		= kRzilMaxRecentItems;
	sCurrPrefs.general.newFork			= fork_datafork;
	
	// Exporting pane
	sCurrPrefs.exporting.includeBinary	= true;
	sCurrPrefs.exporting.formatDtd		= export_KeyDtd;
	sCurrPrefs.exporting.binaryEncoding	= export_Base64Enc;
	sCurrPrefs.exporting.editorSig		= kTextEditSig;

	// Comparison pane
	sCurrPrefs.compare.ignoreName		= false;
	sCurrPrefs.compare.ignoreAttributes	= true;
	sCurrPrefs.compare.ignoreData		= false;
	sCurrPrefs.compare.displayAs		= compare_displayAsHex;

	// Interface pane: default text trait loaded if necessary while
	// retreiving preferences

	// Templates pane
	sCurrPrefs.templates.hexSymbol		= hex_SymbDollar;
	sCurrPrefs.templates.hexCase		= hex_lowercase;
	sCurrPrefs.templates.displayFillers	= false;
	sCurrPrefs.templates.enableFillers	= false;

	// Editors pane
	sCurrPrefs.editors.use8BitPicts		= false;
	sCurrPrefs.editors.use8BitIcons		= false;
	sCurrPrefs.editors.fullTables		= true;
	sCurrPrefs.editors.doFontSubst		= true;
	sCurrPrefs.editors.insertBOM		= false;

	// Misc pane
	sCurrPrefs.misc.setSigOnClose		= false;
	sCurrPrefs.misc.onlyRsrcExt			= true;
	sCurrPrefs.misc.closingType			= kRezFileType;
	sCurrPrefs.misc.closingCreator		= kRezillaSig;
	sCurrPrefs.misc.setSigOnCreate		= true;
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

	theNumber = GetPrefValue( kPref_templates_hexSymbol );
	theValue = CFNumberCreate(NULL, kCFNumberIntType, &theNumber); 
	CFPreferencesSetAppValue( CFSTR("pref_templates_hexSymbol"), theValue, kCFPreferencesCurrentApplication);
	if (theValue) CFRelease(theValue);

	theNumber = GetPrefValue( kPref_templates_hexCase );
	theValue = CFNumberCreate(NULL, kCFNumberIntType, &theNumber); 
	CFPreferencesSetAppValue( CFSTR("pref_templates_hexCase"), theValue, kCFPreferencesCurrentApplication);
	if (theValue) CFRelease(theValue);

	theNumber = GetPrefValue( kPref_templates_displayFillers );
	theValue = CFNumberCreate(NULL, kCFNumberIntType, &theNumber); 
	CFPreferencesSetAppValue( CFSTR("pref_templates_displayFillers"), theValue, kCFPreferencesCurrentApplication);
	if (theValue) CFRelease(theValue);

	theNumber = GetPrefValue( kPref_templates_enableFillers );
	theValue = CFNumberCreate(NULL, kCFNumberIntType, &theNumber); 
	CFPreferencesSetAppValue( CFSTR("pref_templates_enableFillers"), theValue, kCFPreferencesCurrentApplication);
	if (theValue) CFRelease(theValue);

	theNumber = GetPrefValue( kPref_editors_use8BitPicts );
	theValue = CFNumberCreate(NULL, kCFNumberIntType, &theNumber); 
	CFPreferencesSetAppValue( CFSTR("pref_editors_use8BitPicts"), theValue, kCFPreferencesCurrentApplication);
	if (theValue) CFRelease(theValue);

	theNumber = GetPrefValue( kPref_editors_use8BitIcons );
	theValue = CFNumberCreate(NULL, kCFNumberIntType, &theNumber); 
	CFPreferencesSetAppValue( CFSTR("pref_editors_use8BitIcons"), theValue, kCFPreferencesCurrentApplication);
	if (theValue) CFRelease(theValue);

	theNumber = GetPrefValue( kPref_editors_fullTables );
	theValue = CFNumberCreate(NULL, kCFNumberIntType, &theNumber); 
	CFPreferencesSetAppValue( CFSTR("pref_editors_fullTables"), theValue, kCFPreferencesCurrentApplication);
	if (theValue) CFRelease(theValue);

	theNumber = GetPrefValue( kPref_editors_doFontSubst );
	theValue = CFNumberCreate(NULL, kCFNumberIntType, &theNumber); 
	CFPreferencesSetAppValue( CFSTR("pref_editors_doFontSubst"), theValue, kCFPreferencesCurrentApplication);
	if (theValue) CFRelease(theValue);

	theNumber = GetPrefValue( kPref_editors_insertBOM );
	theValue = CFNumberCreate(NULL, kCFNumberIntType, &theNumber); 
	CFPreferencesSetAppValue( CFSTR("pref_editors_insertBOM"), theValue, kCFPreferencesCurrentApplication);
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

	theNumber = GetPrefValue( kPref_export_editorSig );
	theValue = CFNumberCreate(NULL, kCFNumberSInt32Type, &theNumber); 
	CFPreferencesSetAppValue( CFSTR("pref_export_editorSig"), theValue, kCFPreferencesCurrentApplication);
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
	CFPreferencesSetAppValue( CFSTR("pref_compare_dataDisplayAs"), theValue, kCFPreferencesCurrentApplication);
	if (theValue) CFRelease(theValue);
	
	theNumber = GetPrefValue( kPref_misc_setSigOnClose );
	theValue = CFNumberCreate(NULL, kCFNumberIntType, &theNumber); 
	CFPreferencesSetAppValue( CFSTR("pref_misc_setSigOnClose"), theValue, kCFPreferencesCurrentApplication);
	if (theValue) CFRelease(theValue);

	theNumber = GetPrefValue( kPref_misc_onlyRsrcExt );
	theValue = CFNumberCreate(NULL, kCFNumberIntType, &theNumber); 
	CFPreferencesSetAppValue( CFSTR("pref_misc__onlyRsrcExt"), theValue, kCFPreferencesCurrentApplication);
	if (theValue) CFRelease(theValue);

	theNumber = GetPrefValue( kPref_misc_closingType );
	theValue = CFNumberCreate(NULL, kCFNumberSInt32Type, &theNumber); 
	CFPreferencesSetAppValue( CFSTR("pref_misc_closingType"), theValue, kCFPreferencesCurrentApplication);
	if (theValue) CFRelease(theValue);

	theNumber = GetPrefValue( kPref_misc_closingCreator );
	theValue = CFNumberCreate(NULL, kCFNumberSInt32Type, &theNumber); 
	CFPreferencesSetAppValue( CFSTR("pref_misc_closingCreator"), theValue, kCFPreferencesCurrentApplication);
	if (theValue) CFRelease(theValue);

	theNumber = GetPrefValue( kPref_misc_setSigOnCreate );
	theValue = CFNumberCreate(NULL, kCFNumberIntType, &theNumber); 
	CFPreferencesSetAppValue( CFSTR("pref_misc_setSigOnCreate"), theValue, kCFPreferencesCurrentApplication);
	if (theValue) CFRelease(theValue);

	theData = CFDataCreate(NULL, (const UInt8 *)&(sCurrPrefs.interface.traitsRecord), sizeof(TextTraitsRecord));
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
	SInt32				theSInt32;
	const UInt8 *		thePtr;
	
	result = CFPreferencesGetAppIntegerValue(CFSTR("pref_general_maxRecent"), CFSTR(kRezillaIdentifier), &valueValid);
	if (valueValid) {
		SetPrefValue( result, kPref_general_maxRecent);
	}
	result = CFPreferencesGetAppIntegerValue(CFSTR("pref_general_newFork"), CFSTR(kRezillaIdentifier), &valueValid);
	if (valueValid) {
		SetPrefValue( result, kPref_general_newFork);
	}
	result = CFPreferencesGetAppIntegerValue(CFSTR("pref_templates_hexSymbol"), CFSTR(kRezillaIdentifier), &valueValid);
	if (valueValid) {
		SetPrefValue( result, kPref_templates_hexSymbol);
	}
	result = CFPreferencesGetAppIntegerValue(CFSTR("pref_templates_hexCase"), CFSTR(kRezillaIdentifier), &valueValid);
	if (valueValid) {
		SetPrefValue( result, kPref_templates_hexCase);
	}
	result = CFPreferencesGetAppBooleanValue(CFSTR("pref_templates_displayFillers"), CFSTR(kRezillaIdentifier), &valueValid);
	if (valueValid) {
		SetPrefValue( result, kPref_templates_displayFillers);
	}	
	result = CFPreferencesGetAppBooleanValue(CFSTR("pref_templates_enableFillers"), CFSTR(kRezillaIdentifier), &valueValid);
	if (valueValid) {
		SetPrefValue( result, kPref_templates_enableFillers);
	}	
	result = CFPreferencesGetAppBooleanValue(CFSTR("pref_editors_use8BitPicts"), CFSTR(kRezillaIdentifier), &valueValid);
	if (valueValid) {
		SetPrefValue( result, kPref_editors_use8BitPicts);
	}	
	result = CFPreferencesGetAppBooleanValue(CFSTR("pref_editors_use8BitIcons"), CFSTR(kRezillaIdentifier), &valueValid);
	if (valueValid) {
		SetPrefValue( result, kPref_editors_use8BitIcons);
	}	
	result = CFPreferencesGetAppBooleanValue(CFSTR("pref_editors_fullTables"), CFSTR(kRezillaIdentifier), &valueValid);
	if (valueValid) {
		SetPrefValue( result, kPref_editors_fullTables);
	}	
	result = CFPreferencesGetAppBooleanValue(CFSTR("pref_editors_doFontSubst"), CFSTR(kRezillaIdentifier), &valueValid);
	if (valueValid) {
		SetPrefValue( result, kPref_editors_doFontSubst);
	}	
	result = CFPreferencesGetAppBooleanValue(CFSTR("pref_editors_insertBOM"), CFSTR(kRezillaIdentifier), &valueValid);
	if (valueValid) {
		SetPrefValue( result, kPref_editors_insertBOM);
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
	theData = CFPreferencesCopyAppValue(CFSTR("pref_export_editorSig"), CFSTR(kRezillaIdentifier));
	if (theData) {		
		if (CFNumberGetValue( (CFNumberRef) theData, kCFNumberSInt32Type, (void *) &theSInt32)) {
			SetPrefValue( theSInt32, kPref_export_editorSig);
		} 
		CFRelease(theData);
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
	result = CFPreferencesGetAppIntegerValue(CFSTR("pref_compare_dataDisplayAs"), CFSTR(kRezillaIdentifier), &valueValid);
	if (valueValid) {
		SetPrefValue( result, kPref_compare_dataDisplayAs);
	}
	result = CFPreferencesGetAppBooleanValue(CFSTR("pref_misc_setSigOnClose"), CFSTR(kRezillaIdentifier), &valueValid);
	if (valueValid) {
		SetPrefValue( result, kPref_misc_setSigOnClose);
	}	
	result = CFPreferencesGetAppBooleanValue(CFSTR("pref_misc_onlyRsrcExt"), CFSTR(kRezillaIdentifier), &valueValid);
	if (valueValid) {
		SetPrefValue( result, kPref_misc_onlyRsrcExt);
	}	
	theData = CFPreferencesCopyAppValue(CFSTR("pref_misc_closingType"), CFSTR(kRezillaIdentifier));
	if (theData) {		
		if (CFNumberGetValue( (CFNumberRef) theData, kCFNumberSInt32Type, (void *) &theSInt32)) {
			SetPrefValue( theSInt32, kPref_misc_closingType);
		} 
		CFRelease(theData);
	}
	theData = CFPreferencesCopyAppValue(CFSTR("pref_misc_closingCreator"), CFSTR(kRezillaIdentifier));
	if (theData) {		
		if (CFNumberGetValue( (CFNumberRef) theData, kCFNumberSInt32Type, (void *) &theSInt32)) {
			SetPrefValue( theSInt32, kPref_misc_closingCreator);
		} 
		CFRelease(theData);
	}
	result = CFPreferencesGetAppBooleanValue(CFSTR("pref_misc_setSigOnCreate"), CFSTR(kRezillaIdentifier), &valueValid);
	if (valueValid) {
		SetPrefValue( result, kPref_misc_setSigOnCreate);
	}	
	theData = CFPreferencesCopyAppValue(CFSTR("pref_interface_traitsRecord"), CFSTR(kRezillaIdentifier));
	if (theData) {
		theSize = CFDataGetLength( (CFDataRef) theData);
		thePtr = CFDataGetBytePtr( (CFDataRef) theData);
		BlockMoveData(thePtr, &(sCurrPrefs.interface.traitsRecord), theSize);
		// Update the font number according to the font name
		::GetFNum(sCurrPrefs.interface.traitsRecord.fontName, &sCurrPrefs.interface.traitsRecord.fontNumber);
		CFRelease(theData);
	} else {
		sCurrPrefs.interface.traitsRecord.fontNumber = UTextTraits::fontNumber_Unknown;
		UTextTraits::LoadTextTraits(Txtr_MonacoNineDefault, sCurrPrefs.interface.traitsRecord);
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
			sTempPrefs.general.maxRecent = inPrefValue;
		} else {
			sCurrPrefs.general.maxRecent = inPrefValue;
		}	
		break;
		
		case kPref_general_newFork:
		if (inPrefType == prefsType_Temp) {
			sTempPrefs.general.newFork = inPrefValue;
		} else {
			sCurrPrefs.general.newFork = inPrefValue;
		}	
		break;
		
		case kPref_templates_hexSymbol:
		if (inPrefType == prefsType_Temp) {
			sTempPrefs.templates.hexSymbol = inPrefValue;
		} else {
			sCurrPrefs.templates.hexSymbol = inPrefValue;
		}	
		break;
		
		case kPref_templates_hexCase:
		if (inPrefType == prefsType_Temp) {
			sTempPrefs.templates.hexCase = inPrefValue;
		} else {
			sCurrPrefs.templates.hexCase = inPrefValue;
		}	
		break;
		
		case kPref_templates_displayFillers:
		if (inPrefType == prefsType_Temp) {
			sTempPrefs.templates.displayFillers = inPrefValue;
		} else {
			sCurrPrefs.templates.displayFillers = inPrefValue;
		}	
		break;
		
		case kPref_templates_enableFillers:
		if (inPrefType == prefsType_Temp) {
			sTempPrefs.templates.enableFillers = inPrefValue;
		} else {
			sCurrPrefs.templates.enableFillers = inPrefValue;
		}	
		break;
		
		case kPref_editors_use8BitPicts:
		if (inPrefType == prefsType_Temp) {
			sTempPrefs.editors.use8BitPicts = inPrefValue;
		} else {
			sCurrPrefs.editors.use8BitPicts = inPrefValue;
		}	
		break;
		
		case kPref_editors_use8BitIcons:
		if (inPrefType == prefsType_Temp) {
			sTempPrefs.editors.use8BitIcons = inPrefValue;
		} else {
			sCurrPrefs.editors.use8BitIcons = inPrefValue;
		}	
		break;
		
		case kPref_editors_fullTables:
		if (inPrefType == prefsType_Temp) {
			sTempPrefs.editors.fullTables = inPrefValue;
		} else {
			sCurrPrefs.editors.fullTables = inPrefValue;
		}	
		break;
				
		case kPref_editors_doFontSubst:
		if (inPrefType == prefsType_Temp) {
			sTempPrefs.editors.doFontSubst = inPrefValue;
		} else {
			sCurrPrefs.editors.doFontSubst = inPrefValue;
		}	
		break;
				
		case kPref_editors_insertBOM:
		if (inPrefType == prefsType_Temp) {
			sTempPrefs.editors.insertBOM = inPrefValue;
		} else {
			sCurrPrefs.editors.insertBOM = inPrefValue;
		}	
		break;
				
		case kPref_export_formatDtd:
		if (inPrefType == prefsType_Temp) {
			sTempPrefs.exporting.formatDtd = inPrefValue;
		} else {
			sCurrPrefs.exporting.formatDtd = inPrefValue;
		}	
		break;
		
		case kPref_export_includeBinary:
		if (inPrefType == prefsType_Temp) {
			sTempPrefs.exporting.includeBinary = inPrefValue;
		} else {
			sCurrPrefs.exporting.includeBinary = inPrefValue;
		}	
		break;
		
		case kPref_export_dataEncoding:
		if (inPrefType == prefsType_Temp) {
			sTempPrefs.exporting.binaryEncoding = inPrefValue;
		} else {
			sCurrPrefs.exporting.binaryEncoding = inPrefValue;
		}	
		break;
		
		case kPref_export_editorSig:
		if (inPrefType == prefsType_Temp) {
			sTempPrefs.exporting.editorSig = (OSType) inPrefValue;
		} else {
			sCurrPrefs.exporting.editorSig = (OSType) inPrefValue;
		}	
		break;
		
		case kPref_compare_ignoreName:
		if (inPrefType == prefsType_Temp) {
			sTempPrefs.compare.ignoreName = inPrefValue;
		} else {
			sCurrPrefs.compare.ignoreName = inPrefValue;
		}	
		break;
		
		case kPref_compare_ignoreAttributes:
		if (inPrefType == prefsType_Temp) {
			sTempPrefs.compare.ignoreAttributes = inPrefValue;
		} else {
			sCurrPrefs.compare.ignoreAttributes = inPrefValue;
		}	
		break;
		
		case kPref_compare_ignoreData:
		if (inPrefType == prefsType_Temp) {
			sTempPrefs.compare.ignoreData = inPrefValue;
		} else {
			sCurrPrefs.compare.ignoreData = inPrefValue;
		}	
		break;
		
		case kPref_compare_dataDisplayAs:
		if (inPrefType == prefsType_Temp) {
			sTempPrefs.compare.displayAs = inPrefValue;
		} else {
			sCurrPrefs.compare.displayAs = inPrefValue;
		}	
		break;

		case kPref_misc_setSigOnClose:
		if (inPrefType == prefsType_Temp) {
			sTempPrefs.misc.setSigOnClose = inPrefValue;
		} else {
			sCurrPrefs.misc.setSigOnClose = inPrefValue;
		}	
		break;
		
		case kPref_misc_onlyRsrcExt:
		if (inPrefType == prefsType_Temp) {
			sTempPrefs.misc.onlyRsrcExt = inPrefValue;
		} else {
			sCurrPrefs.misc.onlyRsrcExt = inPrefValue;
		}	
		break;
		
		case kPref_misc_closingType:
		if (inPrefType == prefsType_Temp) {
			sTempPrefs.misc.closingType = (OSType) inPrefValue;
		} else {
			sCurrPrefs.misc.closingType = (OSType) inPrefValue;
		}	
		break;
		
		case kPref_misc_closingCreator:
		if (inPrefType == prefsType_Temp) {
			sTempPrefs.misc.closingCreator = (OSType) inPrefValue;
		} else {
			sCurrPrefs.misc.closingCreator = (OSType) inPrefValue;
		}	
		break;
		
		case kPref_misc_setSigOnCreate:
		if (inPrefType == prefsType_Temp) {
			sTempPrefs.misc.setSigOnCreate = inPrefValue;
		} else {
			sCurrPrefs.misc.setSigOnCreate = inPrefValue;
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
			theValue = sTempPrefs.general.maxRecent;
		} else {
			theValue = sCurrPrefs.general.maxRecent;
		}	
		break;
		
		case kPref_general_newFork:
		if (inPrefType == prefsType_Temp) {
			theValue = sTempPrefs.general.newFork;
		} else {
			theValue = sCurrPrefs.general.newFork;
		}	
		break;
		
		case kPref_templates_hexSymbol:
		if (inPrefType == prefsType_Temp) {
			theValue = sTempPrefs.templates.hexSymbol;
		} else {
			theValue = sCurrPrefs.templates.hexSymbol;
		}	
		break;
		
		case kPref_templates_hexCase:
		if (inPrefType == prefsType_Temp) {
			theValue = sTempPrefs.templates.hexCase;
		} else {
			theValue = sCurrPrefs.templates.hexCase;
		}	
		break;
		
		case kPref_templates_displayFillers:
		if (inPrefType == prefsType_Temp) {
			theValue = sTempPrefs.templates.displayFillers;
		} else {
			theValue = sCurrPrefs.templates.displayFillers;
		}	
		break;
		
		case kPref_templates_enableFillers:
		if (inPrefType == prefsType_Temp) {
			theValue = sTempPrefs.templates.enableFillers;
		} else {
			theValue = sCurrPrefs.templates.enableFillers;
		}	
		break;
		
		case kPref_editors_use8BitPicts:
		if (inPrefType == prefsType_Temp) {
			theValue = sTempPrefs.editors.use8BitPicts;
		} else {
			theValue = sCurrPrefs.editors.use8BitPicts;
		}	
		break;
		
		case kPref_editors_use8BitIcons:
		if (inPrefType == prefsType_Temp) {
			theValue = sTempPrefs.editors.use8BitIcons;
		} else {
			theValue = sCurrPrefs.editors.use8BitIcons;
		}	
		break;
		
		case kPref_editors_fullTables:
		if (inPrefType == prefsType_Temp) {
			theValue = sTempPrefs.editors.fullTables;
		} else {
			theValue = sCurrPrefs.editors.fullTables;
		}	
		break;
				
		case kPref_editors_doFontSubst:
		if (inPrefType == prefsType_Temp) {
			theValue = sTempPrefs.editors.doFontSubst;
		} else {
			theValue = sCurrPrefs.editors.doFontSubst;
		}	
		break;
				
		case kPref_editors_insertBOM:
		if (inPrefType == prefsType_Temp) {
			theValue = sTempPrefs.editors.insertBOM;
		} else {
			theValue = sCurrPrefs.editors.insertBOM;
		}	
		break;
				
		case kPref_export_formatDtd:
		if (inPrefType == prefsType_Temp) {
			theValue = sTempPrefs.exporting.formatDtd;
		} else {
			theValue = sCurrPrefs.exporting.formatDtd;
		}	
		break;
		
		case kPref_export_includeBinary:
		if (inPrefType == prefsType_Temp) {
			theValue = sTempPrefs.exporting.includeBinary;
		} else {
			theValue = sCurrPrefs.exporting.includeBinary;
		}	
		break;
		
		case kPref_export_dataEncoding:
		if (inPrefType == prefsType_Temp) {
			theValue = sTempPrefs.exporting.binaryEncoding;
		} else {
			theValue = sCurrPrefs.exporting.binaryEncoding;
		}	
		break;
		
		case kPref_export_editorSig:
		if (inPrefType == prefsType_Temp) {
			theValue = (SInt32) sTempPrefs.exporting.editorSig;
		} else {
			theValue = (SInt32) sCurrPrefs.exporting.editorSig;
		}	
		break;
		
		case kPref_compare_ignoreName:
		if (inPrefType == prefsType_Temp) {
			theValue = sTempPrefs.compare.ignoreName;
		} else {
			theValue = sCurrPrefs.compare.ignoreName;
		}	
		break;
		
		case kPref_compare_ignoreAttributes:
		if (inPrefType == prefsType_Temp) {
			theValue = sTempPrefs.compare.ignoreAttributes;
		} else {
			theValue = sCurrPrefs.compare.ignoreAttributes;
		}	
		break;
		
		case kPref_compare_ignoreData:
		if (inPrefType == prefsType_Temp) {
			theValue = sTempPrefs.compare.ignoreData;
		} else {
			theValue = sCurrPrefs.compare.ignoreData;
		}	
		break;
		
		case kPref_compare_dataDisplayAs:
		if (inPrefType == prefsType_Temp) {
			theValue = sTempPrefs.compare.displayAs;
		} else {
			theValue = sCurrPrefs.compare.displayAs;
		}	
		break;
		
		case kPref_misc_setSigOnClose:
		if (inPrefType == prefsType_Temp) {
			theValue = sTempPrefs.misc.setSigOnClose;
		} else {
			theValue = sCurrPrefs.misc.setSigOnClose;
		}	
		break;
		
		case kPref_misc_onlyRsrcExt:
		if (inPrefType == prefsType_Temp) {
			theValue = sTempPrefs.misc.onlyRsrcExt;
		} else {
			theValue = sCurrPrefs.misc.onlyRsrcExt;
		}	
		break;
		
		case kPref_misc_closingType:
		if (inPrefType == prefsType_Temp) {
			theValue = (SInt32) sTempPrefs.misc.closingType;
		} else {
			theValue = (SInt32) sCurrPrefs.misc.closingType;
		}	
		break;
		
		case kPref_misc_closingCreator:
		if (inPrefType == prefsType_Temp) {
			theValue = (SInt32) sTempPrefs.misc.closingCreator;
		} else {
			theValue = (SInt32) sCurrPrefs.misc.closingCreator;
		}	
		break;
		
		case kPref_misc_setSigOnCreate:
		if (inPrefType == prefsType_Temp) {
			theValue = sTempPrefs.misc.setSigOnCreate;
		} else {
			theValue = sCurrPrefs.misc.setSigOnCreate;
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
		return sTempPrefs.interface.traitsRecord;
	} else {
		return sCurrPrefs.interface.traitsRecord;
	}	
}


// ---------------------------------------------------------------------------
//	¥ LoadStyleElement												[public]
// ---------------------------------------------------------------------------

void
CRezillaPrefs::LoadStyleElement(TextTraitsPtr inTraitsRecPtr)
{
	::BlockMoveData(inTraitsRecPtr, &sCurrPrefs.interface.traitsRecord, sizeof(TextTraitsRecord));
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
			sTempPrefs.interface.traitsRecord.fontNumber = inStyleValue;
		} else {
			sCurrPrefs.interface.traitsRecord.fontNumber = inStyleValue;
		}	
		break;
		
	  case style_sizeType:
		if (inPrefType == prefsType_Temp) {
			sTempPrefs.interface.traitsRecord.size = inStyleValue;
		} else {
			sCurrPrefs.interface.traitsRecord.size = inStyleValue;
		}	
		break;
		
	  case style_faceType:
		if (inPrefType == prefsType_Temp) {
			sTempPrefs.interface.traitsRecord.style = inStyleValue;
		} else {
			sCurrPrefs.interface.traitsRecord.style = inStyleValue;
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
	::BlockMoveData(&sTempPrefs, &sCurrPrefs, sizeof(SRezillaPrefs));
}


// ---------------------------------------------------------------------------
//	¥ InitTempPrefs												[public]
// ---------------------------------------------------------------------------

void
CRezillaPrefs::InitTempPrefs() 
{
	::BlockMoveData(&sCurrPrefs, &sTempPrefs, sizeof(SRezillaPrefs));
}


// ---------------------------------------------------------------------------
//	¥ PrefsHaveChanged											[public]
// ---------------------------------------------------------------------------

Boolean
CRezillaPrefs::PrefsHaveChanged() 
{
	return ( memcmp( &sCurrPrefs, &sTempPrefs, sizeof(SRezillaPrefs) ) != 0);
}


// ---------------------------------------------------------------------------
//	¥ ApplyStylePrefs										[public]
// ---------------------------------------------------------------------------
// Apply the style changes to all the windows listening.

void
CRezillaPrefs::ApplyStylePrefs() 
{
	UMiscUtils::MetricsFromTraits( &sCurrPrefs.interface.traitsRecord );
	BroadcastMessage(msg_StylePrefsChanged, &sCurrPrefs);
}


// ---------------------------------------------------------------------------
//	¥ RunPrefsDialog											[public]
// ---------------------------------------------------------------------------
//	Display the preferences window for the application

void
CRezillaPrefs::RunPrefsDialog()
{
	LCheckBox *		theCheckBox;
	LCheckBoxGroupBox *	theCheckGroupBox;
	LPopupButton *	thePopup;
	long			theLong;
	Str255			theString;
	LStr255			theLine( "\p" );
	Boolean 		inPrefsLoop = true;
	LEditText *		theEditField;
	SInt32 			theSize, itemIndex;
	SInt16			theFontNum;
	OSType			theType;
	TextTraitsRecord theCurrTraits;
	
	StDialogBoxHandler	theHandler(PPob_PrefsWindow, this);
	CThreeButtonsBox *		theDialog = theHandler.GetDialog();
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
	
	LView* theInterfacePane = theMPV->GetPanel(mpv_Interface);
	ThrowIfNil_(theInterfacePane);
	
	LView* theTemplatesPane = theMPV->GetPanel(mpv_Templates);
	ThrowIfNil_(theTemplatesPane);
	
	LView* theEditorsPane = theMPV->GetPanel(mpv_Editors);
	ThrowIfNil_(theEditorsPane);
	
	LView* theComparePane = theMPV->GetPanel(mpv_Compare);
	ThrowIfNil_(theComparePane);
	
	LView* theExportPane = theMPV->GetPanel(mpv_Export);
	ThrowIfNil_(theExportPane);
	
	LView* theMiscPane = theMPV->GetPanel(mpv_Misc);
	ThrowIfNil_(theMiscPane);
	
	LRadioGroupView * theNewMapRGV = dynamic_cast<LRadioGroupView *>(theGeneralPane->FindPaneByID( item_GenPrefsNewMapRgbx ));
	ThrowIfNil_(theNewMapRGV);
	
	LRadioGroupView * theDtdRGV = dynamic_cast<LRadioGroupView *>(theExportPane->FindPaneByID( item_ExpPrefsDtdRgbx ));
	ThrowIfNil_(theDtdRGV);
	
	LRadioGroupView * theEncodingRGV = dynamic_cast<LRadioGroupView *>(theExportPane->FindPaneByID( item_ExpPrefsEncRgbx ));
	ThrowIfNil_(theEncodingRGV);
	
	LRadioGroupView * theDisplayRGV = dynamic_cast<LRadioGroupView *>(theComparePane->FindPaneByID( item_CompPrefsDisplayRgbx ));
	ThrowIfNil_(theDisplayRGV);
	
	LRadioGroupView * theHexSymbRGV = dynamic_cast<LRadioGroupView *>(theTemplatesPane->FindPaneByID( item_EditPrefsHexSymRgbx ));
	ThrowIfNil_(theHexSymbRGV);
	
	LRadioGroupView * theHexCaseRGV = dynamic_cast<LRadioGroupView *>(theTemplatesPane->FindPaneByID( item_EditPrefsHexCaseRgbx ));
	ThrowIfNil_(theHexCaseRGV);
	
	theCurrTraits = GetStyleElement( prefsType_Curr );

	//    Link Listeners and Broadcasters
	// ----------------------------------
	// Partly done in the StDialogBoxHandler constructor

	thePageCtrl->AddListener(theMPV);
	thePageCtrl->AddListener(&theHandler);
	
	// Note : the RidL resource does not contain the controls of
	// the various MPV's subpanels. We have to do that explicitly.
	UReanimator::LinkListenerToBroadcasters( &theHandler, theGeneralPane, PPob_PrefsGeneralPane );
	UReanimator::LinkListenerToBroadcasters( &theHandler, theInterfacePane, PPob_PrefsInterfacePane );
	UReanimator::LinkListenerToBroadcasters( &theHandler, theTemplatesPane, PPob_PrefsTemplatesPane );
	UReanimator::LinkListenerToBroadcasters( &theHandler, theEditorsPane, PPob_PrefsEditorsPane );
	UReanimator::LinkListenerToBroadcasters( &theHandler, theComparePane, PPob_PrefsComparePane );
	UReanimator::LinkListenerToBroadcasters( &theHandler, theExportPane, PPob_PrefsExportPane );
	UReanimator::LinkListenerToBroadcasters( &theHandler, theMiscPane, PPob_PrefsMiscPane );
	
	while (inPrefsLoop) {
		
		//    Setup the controls values
		// ----------------------------		
		theNewMapRGV->SetCurrentRadioID( GetPrefValue( kPref_general_newFork ) + item_GenPrefsNewMapRgbx );
		theDtdRGV->SetCurrentRadioID( GetPrefValue( kPref_export_formatDtd ) + item_ExpPrefsDtdRgbx );
		theEncodingRGV->SetCurrentRadioID( GetPrefValue( kPref_export_dataEncoding ) + item_ExpPrefsEncRgbx );
		theDisplayRGV->SetCurrentRadioID( GetPrefValue( kPref_compare_dataDisplayAs ) + item_CompPrefsDisplayRgbx );
		theHexSymbRGV->SetCurrentRadioID( GetPrefValue( kPref_templates_hexSymbol ) + item_EditPrefsHexSymRgbx );
		theHexCaseRGV->SetCurrentRadioID( GetPrefValue( kPref_templates_hexCase ) + item_EditPrefsHexCaseRgbx );

		theEditField = dynamic_cast<LEditText *>(theGeneralPane->FindPaneByID( item_GenPrefsMaxRecent ));
		ThrowIfNil_( theEditField );
		theEditField->SetValue(  GetPrefValue( kPref_general_maxRecent ) );

		theEditField = dynamic_cast<LEditText *>(theExportPane->FindPaneByID( item_ExpPrefsEditSig ));
		ThrowIfNil_( theEditField );
		UMiscUtils::OSTypeToPString( (OSType) GetPrefValue(kPref_export_editorSig), theString);
		theEditField->SetText( theLine.Assign(theString) );

		theEditField = dynamic_cast<LEditText *>(theMiscPane->FindPaneByID( item_MiscPrefsClosingType ));
		ThrowIfNil_( theEditField );
		UMiscUtils::OSTypeToPString( (OSType) GetPrefValue(kPref_misc_closingType), theString);
		theEditField->SetText( theLine.Assign(theString) );

		theEditField = dynamic_cast<LEditText *>(theMiscPane->FindPaneByID( item_MiscPrefsClosingCreator ));
		ThrowIfNil_( theEditField );
		UMiscUtils::OSTypeToPString( (OSType) GetPrefValue(kPref_misc_closingCreator), theString);
		theEditField->SetText( theLine.Assign(theString) );

		theCheckBox = dynamic_cast<LCheckBox *>(theTemplatesPane->FindPaneByID( item_EditPrefsDisplayFillers ));
		ThrowIfNil_( theCheckBox );
		theCheckBox->SetValue(  GetPrefValue( kPref_templates_displayFillers ) );

		theCheckBox = dynamic_cast<LCheckBox *>(theTemplatesPane->FindPaneByID( item_EditPrefsEnableFillers ));
		ThrowIfNil_( theCheckBox );
		theCheckBox->SetValue(  GetPrefValue( kPref_templates_enableFillers ) );

		theCheckBox = dynamic_cast<LCheckBox *>(theEditorsPane->FindPaneByID( item_EditPrefsUse8BitPicts ));
		ThrowIfNil_( theCheckBox );
		theCheckBox->SetValue(  GetPrefValue( kPref_editors_use8BitPicts ) );

		theCheckBox = dynamic_cast<LCheckBox *>(theEditorsPane->FindPaneByID( item_EditPrefsUseFullTables ));
		ThrowIfNil_( theCheckBox );
		theCheckBox->SetValue(  GetPrefValue( kPref_editors_fullTables ) );
		
		theCheckBox = dynamic_cast<LCheckBox *>(theEditorsPane->FindPaneByID( item_EditPrefsDoFontSubst ));
		ThrowIfNil_( theCheckBox );
		theCheckBox->SetValue(  GetPrefValue( kPref_editors_doFontSubst ) );
		
		theCheckBox = dynamic_cast<LCheckBox *>(theEditorsPane->FindPaneByID( item_EditPrefsInsertBOM ));
		ThrowIfNil_( theCheckBox );
		theCheckBox->SetValue(  GetPrefValue( kPref_editors_insertBOM ) );
		
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

		theCheckGroupBox = dynamic_cast<LCheckBoxGroupBox *>(theMiscPane->FindPaneByID( item_MiscPrefsSetSigOnClose ));
		ThrowIfNil_( theCheckGroupBox );
		theCheckGroupBox->SetValue(  GetPrefValue( kPref_misc_setSigOnClose ) );

		theCheckBox = dynamic_cast<LCheckBox *>(theMiscPane->FindPaneByID( item_MiscPrefsOnlyRsrcExt ));
		ThrowIfNil_( theCheckBox );
		theCheckBox->SetValue(  GetPrefValue( kPref_misc_onlyRsrcExt ) );

		theCheckBox = dynamic_cast<LCheckBox *>(theMiscPane->FindPaneByID( item_MiscPrefsSetSigOnCreate ));
		ThrowIfNil_( theCheckBox );
		theCheckBox->SetValue(  GetPrefValue( kPref_misc_setSigOnCreate ) );

		thePopup = dynamic_cast<LPopupButton *> (theInterfacePane->FindPaneByID( item_UIPrefsFontsMenu ));
		ThrowIfNil_( thePopup );
		theFontNum = theCurrTraits.fontNumber;
		thePopup->SetValue( UMiscUtils::FontIndexFromFontNum(thePopup, theFontNum) );
		
		thePopup = dynamic_cast<LPopupButton *> (theInterfacePane->FindPaneByID( item_UIPrefsSizeMenu ));
		ThrowIfNil_( thePopup );
		theSize = theCurrTraits.size;
		thePopup->SetValue( UMiscUtils::SizeIndexFromSizeValue(thePopup, theSize) );

		thePageCtrl->SetValue(sCurrentPrefsPane);
		theMPV->SwitchToPanel(sCurrentPrefsPane);
		
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
					
				  case msg_GenPrefsResetRecent:
					CRezillaApp::sRecentItemsAttachment->Reset();
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
						if (UMessageDialogs::GetOneValue(sPrefsWindow, CFSTR("EnterFontSize"), PPob_GetValueDialog, 
											   item_PromptField, item_ValueField, theSize)) {
							if (theSize == 0) {theSize = 10;}
							// If they match, no need to use 'Other' item
							if (UMiscUtils::FontSizeExists(thePopup, theSize, itemIndex)) {
								thePopup->SetValue(itemIndex);
								::SetMenuItemText( thePopup->GetMacMenuH(), kLastSizeMenuItem + 2, theLine.Assign("\pOtherÉ"));					
							} else {
								// Modify the text of the 'Other' item.
								Str255	theSizeString;
								theLine = "\pOther (";
								::NumToString( theSize, theSizeString );
								// Append the current size
								theLine += theSizeString;
								theLine += "\p)É";
								// Set the menu item text.
								::SetMenuItemText( thePopup->GetMacMenuH(), kLastSizeMenuItem + 2, theLine );					
							}
						}
					} else {
						::GetMenuItemText( thePopup->GetMacMenuH(), thePopup->GetValue(), theString );
						::StringToNum( theString, &theSize );
						::SetMenuItemText( thePopup->GetMacMenuH(), kLastSizeMenuItem + 2, theLine.Assign("\pOtherÉ"));					
					}
					SetStyleElement( (SInt16) theSize, style_sizeType, prefsType_Temp);
					break;
				}	
			}
		}
		
		sCurrentPrefsPane = thePageCtrl->GetCurrentPageIndex();

		// if we hit ok, save the pref info
		if (msg_OK == theMessage) {
			PaneIDT theCurrentRadioID;
			
			//    Retrieve the controls values
			// -------------------------------		
			
			// EditPrefsDisplayFillers
			theCheckBox = dynamic_cast<LCheckBox *>(theTemplatesPane->FindPaneByID( item_EditPrefsDisplayFillers ));
			SetPrefValue( theCheckBox->GetValue(), kPref_templates_displayFillers, prefsType_Temp);
			
			// EditPrefsEnableFillers
			theCheckBox = dynamic_cast<LCheckBox *>(theTemplatesPane->FindPaneByID( item_EditPrefsEnableFillers ));
			SetPrefValue( theCheckBox->GetValue(), kPref_templates_enableFillers, prefsType_Temp);
			
			// EditPrefsUse8BitPicts
			theCheckBox = dynamic_cast<LCheckBox *>(theEditorsPane->FindPaneByID( item_EditPrefsUse8BitPicts ));
			SetPrefValue( theCheckBox->GetValue(), kPref_editors_use8BitPicts, prefsType_Temp);
			
			// EditPrefsFullTables
			theCheckBox = dynamic_cast<LCheckBox *>(theEditorsPane->FindPaneByID( item_EditPrefsUseFullTables ));
			SetPrefValue( theCheckBox->GetValue(), kPref_editors_fullTables, prefsType_Temp);
						
			// EditPrefsDoFontSubst
			theCheckBox = dynamic_cast<LCheckBox *>(theEditorsPane->FindPaneByID( item_EditPrefsDoFontSubst ));
			SetPrefValue( theCheckBox->GetValue(), kPref_editors_doFontSubst, prefsType_Temp);
						
			// EditPrefsInsertBOM
			theCheckBox = dynamic_cast<LCheckBox *>(theEditorsPane->FindPaneByID( item_EditPrefsInsertBOM ));
			SetPrefValue( theCheckBox->GetValue(), kPref_editors_insertBOM, prefsType_Temp);
						
			// CompPrefsIgnName
			theCheckBox = dynamic_cast<LCheckBox *>(theComparePane->FindPaneByID( item_CompPrefsIgnName ));
			SetPrefValue( theCheckBox->GetValue(), kPref_compare_ignoreName, prefsType_Temp);
			
			// CompPrefsIgnAttr
			theCheckBox = dynamic_cast<LCheckBox *>(theComparePane->FindPaneByID( item_CompPrefsIgnAttr ));
			SetPrefValue( theCheckBox->GetValue(), kPref_compare_ignoreAttributes, prefsType_Temp);
			
			// CompPrefsIgnData
			theCheckBox = dynamic_cast<LCheckBox *>(theComparePane->FindPaneByID( item_CompPrefsIgnData ));
			SetPrefValue( theCheckBox->GetValue(), kPref_compare_ignoreData, prefsType_Temp);
			
			// ExpPrefsInclBinData
			theCheckBox = dynamic_cast<LCheckBox *>(theExportPane->FindPaneByID( item_ExpPrefsInclBinData ));
			SetPrefValue( theCheckBox->GetValue(), kPref_export_includeBinary, prefsType_Temp);
			
			// MiscPrefsSetSigOnClose
			theCheckGroupBox = dynamic_cast<LCheckBoxGroupBox *>(theMiscPane->FindPaneByID( item_MiscPrefsSetSigOnClose ));
			SetPrefValue( theCheckGroupBox->GetValue(), kPref_misc_setSigOnClose, prefsType_Temp);
			
			// MiscPrefsOnlyRsrcExt
			theCheckBox = dynamic_cast<LCheckBox *>(theMiscPane->FindPaneByID( item_MiscPrefsOnlyRsrcExt ));
			SetPrefValue( theCheckBox->GetValue(), kPref_misc_onlyRsrcExt, prefsType_Temp);
			
			// MiscPrefsSetSigOnCreate
			theCheckBox = dynamic_cast<LCheckBox *>(theMiscPane->FindPaneByID( item_MiscPrefsSetSigOnCreate ));
			SetPrefValue( theCheckGroupBox->GetValue(), kPref_misc_setSigOnCreate, prefsType_Temp);
			
			// GenPrefsMaxRecent
			theEditField = dynamic_cast<LEditText *>(theGeneralPane->FindPaneByID( item_GenPrefsMaxRecent ));
			theEditField->GetDescriptor(theString);
			if (theString[0]) {
				::StringToNum(theString, &theLong);
			} else {
				theLong = 10;
			}
			SetPrefValue( theLong, kPref_general_maxRecent, prefsType_Temp);
			
			// GenPrefsDataFork / GenPrefsResourceFork
			theCurrentRadioID = theNewMapRGV->GetCurrentRadioID();
			SetPrefValue( theCurrentRadioID - item_GenPrefsNewMapRgbx, kPref_general_newFork, prefsType_Temp);
			
			// ExpPrefsKeyDtd / ExpPrefsAttrDtd
			theCurrentRadioID = theDtdRGV->GetCurrentRadioID();
			SetPrefValue( theCurrentRadioID - item_ExpPrefsDtdRgbx, kPref_export_formatDtd, prefsType_Temp);
			
			// ExpPrefsHexEnc / ExpPrefsBase64Enc
			theCurrentRadioID = theEncodingRGV->GetCurrentRadioID();
			SetPrefValue( theCurrentRadioID - item_ExpPrefsEncRgbx, kPref_export_dataEncoding, prefsType_Temp);
			
			// CompPrefsHexDisplay / CompPrefsTxtDisplay
			theCurrentRadioID = theDisplayRGV->GetCurrentRadioID();
			SetPrefValue( theCurrentRadioID - item_CompPrefsDisplayRgbx, kPref_compare_dataDisplayAs, prefsType_Temp);
			
			// EditPrefsHexSym0x / EditPrefsHexSymDollar
			theCurrentRadioID = theHexSymbRGV->GetCurrentRadioID();
			SetPrefValue( theCurrentRadioID - item_EditPrefsHexSymRgbx, kPref_templates_hexSymbol, prefsType_Temp);
			
			// EditPrefsHexLowercase / EditPrefsHexUppercase
			theCurrentRadioID = theHexCaseRGV->GetCurrentRadioID();
			SetPrefValue( theCurrentRadioID - item_EditPrefsHexCaseRgbx, kPref_templates_hexCase, prefsType_Temp);
			
			// UIPrefsFontsMenu
			// Get the popup menu.
			thePopup = dynamic_cast<LPopupButton *> (theInterfacePane->FindPaneByID( item_UIPrefsFontsMenu ));
			ThrowIfNil_( thePopup );
			// Get the name of the font.
			::GetMenuItemText( thePopup->GetMacMenuH(), thePopup->GetValue(), theString );
			LString::CopyPStr(theString, sTempPrefs.interface.traitsRecord.fontName);
			::GetFNum(theString, &theFontNum);
			SetStyleElement(theFontNum, style_fontType, prefsType_Temp);
			
			// ExpPrefsEditSig
			theEditField = dynamic_cast<LEditText *>(theExportPane->FindPaneByID( item_ExpPrefsEditSig ));
			ThrowIfNil_( theEditField );
			theEditField->GetText( theLine );
			UMiscUtils::PStringToOSType( theLine, theType);
			SetPrefValue(theType, kPref_export_editorSig, prefsType_Temp);
			
			// MiscPrefsClosingType
			theEditField = dynamic_cast<LEditText *>(theMiscPane->FindPaneByID( item_MiscPrefsClosingType ));
			ThrowIfNil_( theEditField );
			theEditField->GetText( theLine );
			UMiscUtils::PStringToOSType( theLine, theType);
			SetPrefValue(theType, kPref_misc_closingType, prefsType_Temp);
			
			// MiscPrefsClosingCreator
			theEditField = dynamic_cast<LEditText *>(theMiscPane->FindPaneByID( item_MiscPrefsClosingCreator ));
			ThrowIfNil_( theEditField );
			theEditField->GetText( theLine );
			UMiscUtils::PStringToOSType( theLine, theType);
			SetPrefValue(theType, kPref_misc_closingCreator, prefsType_Temp);

			// Record the changes
			// ------------------
			if ( PrefsHaveChanged() ) {
				Boolean stylechanged = (memcmp( &sCurrPrefs.interface, &sTempPrefs.interface, sizeof(SInterfacePrefs) ) != 0);
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
	CRezCompare::SetIgnoreNames(GetPrefValue(kPref_compare_ignoreName));
	CRezCompare::SetIgnoreAttrs(GetPrefValue(kPref_compare_ignoreAttributes));
	CRezCompare::SetIgnoreData(GetPrefValue(kPref_compare_ignoreData));
	
	CRezillaApp::sRecentItemsAttachment->SetMaxRecentItems( GetPrefValue(kPref_general_maxRecent) );
}


