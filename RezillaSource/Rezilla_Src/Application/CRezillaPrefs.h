// ===========================================================================
// CRezillaPrefs.h					
// 
//                       Created: 2004-05-17 08:52:16
//             Last modification: 2004-05-18 19:07:58
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#ifndef _H_CRezillaPrefs
#define _H_CRezillaPrefs
#pragma once

#include <LPreferencesFile.h>
#include <LCommander.h>

//     General Prefs
struct SGeneralPrefs {
	SInt32			maxRecent;
	SInt32			newFork;
};

//     Export Prefs
struct SExportPrefs {
	Boolean			includeBinary;
	SInt32			formatDtd;
	SInt32			binaryEncoding;
};

//     Comparison Prefs
struct SComparePrefs {
	Boolean			ignoreName;
	Boolean			ignoreAttributes;
	Boolean			ignoreData;
	SInt32			displayAs;
};

//     Interface Prefs
struct SInterfacePrefs {
	TextTraitsRecord	traitsRecord;
};

//     Editors Prefs
struct SEditorsPrefs {
	SInt32			labelWidth;
};

struct SRezillaPrefs {
	SGeneralPrefs		general;
	SExportPrefs		exporting;
	SComparePrefs		compare;
	SInterfacePrefs		interface;
	SEditorsPrefs		editors;
};

enum {
	kPref_compare_dataDisplayAs,
	kPref_compare_ignoreAttributes,
	kPref_compare_ignoreData,
	kPref_compare_ignoreName,
	kPref_editors_labelWidth,
	kPref_export_dataEncoding,
	kPref_export_formatDtd,
	kPref_export_includeBinary,
	kPref_interface_traitsRecord,
	kPref_general_newFork,
	kPref_general_maxRecent
};


class LDialogBox;
class LPopupButton;

class CRezillaPrefs : public LCommander, public LBroadcaster {

public:
	enum { 	prefsType_Temp = 0,
			prefsType_Curr = 1};

							CRezillaPrefs();
							CRezillaPrefs( LCommander* inSuper );
			virtual			~CRezillaPrefs();

	void				RunPrefsWindow();

	virtual SRezillaPrefs	GetRezillaPreferences() { return mCurrPrefs;}
	void					SetRezillaPreferences(SRezillaPrefs inRezillaPreferences) {
														mCurrPrefs = inRezillaPreferences ;}
				
	SInt32				GetPrefValue(SInt32 inConstant, 
									 SInt32 inPrefType = prefsType_Curr);
	void				SetPrefValue(SInt32 inPrefValue, 
									 SInt32 inConstant, 
									 SInt32 inPrefType = prefsType_Curr);
	
	virtual TextTraitsRecord	GetStyleElement(SInt32 inPrefType = prefsType_Temp);
	
	virtual void		SetStyleElement(SInt16 inStyleValue, 
										SInt32 inElementType,
										SInt32 inPrefType = prefsType_Curr);
	virtual void		LoadStyleElement(TextTraitsPtr inTraitsRecPtr);

	LDialogBox *		GetPrefsWindow() { return sPrefsWindow;}
	void				SetPrefsWindow(LDialogBox * inPrefsWindow) {sPrefsWindow = inPrefsWindow ;}
	
	void				ValidateTempPrefs();
	void				InitTempPrefs();
	virtual void		StorePreferences();
	Boolean				PrefsHaveChanged();
	void				UpdateVars();
	
	static LDialogBox *		sPrefsWindow;
	static ArrayIndexT		sCurrentPrefsPane;
	
protected:
	SRezillaPrefs			mTempPrefs;
	SRezillaPrefs			mCurrPrefs;
	LPreferencesFile *		mFile;
	
	virtual void		Initialize();
	void                MakePrefsWindow();

private:
	void				SetDefaultPreferences();
	void				RetrievePreferences();
	void				ApplyStylePrefs();
};

#endif // _H_CRezillaPrefs