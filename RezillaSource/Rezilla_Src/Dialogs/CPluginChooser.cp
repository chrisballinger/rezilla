// ===========================================================================
// CPluginChooser.h
// 
//                       Created: 2006-09-25 07:02:55
//             Last modification: 2006-09-27 08:56:34
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================

#include "CPluginChooser.h"
#include "CPluginsController.h"
#include "CRezillaPlugin.h"
#include "CThreeButtonsBox.h"
#include "CDragTable.h"
#include "CIconrefPane.h"
#include "RezillaConstants.h"
#include "UDialogBoxHandler.h"
#include "UMessageDialogs.h"
#include "UMiscUtils.h"
#include "UCompareUtils.h"

#include <LStaticText.h>
#include <LPopupButton.h>
#include <LPopupGroupBox.h>

#include <LPageController.h>
#include <LMultiPanelView.h>
#include <LView.h>

CFMutableDictionaryRef		CPluginChooser::sTypesDict = NULL;

// ---------------------------------------------------------------------------
//   CPluginChooser				[public]
// ---------------------------------------------------------------------------

CPluginChooser::CPluginChooser(LCommander * inCommander)
 : LCommander(inCommander)
{
	sTypesDict = ::CFDictionaryCreateMutableCopy(NULL, 0, CPluginsController::sPluginsDict);
}


// ---------------------------------------------------------------------------
//   ~CPluginChooser				[public]
// ---------------------------------------------------------------------------

CPluginChooser::~CPluginChooser()
{
	if (sTypesDict) {
		::CFRelease(sTypesDict);
		sTypesDict = NULL;
	} 
}


// ---------------------------------------------------------------------------------
//   RunDialog
// ---------------------------------------------------------------------------------
// error = userCanceledErr;

OSErr
CPluginChooser::RunDialog()
{
	Boolean 		inPickerLoop = true;
	Str255			theString;
	SInt32 			itemIndex;
	ResType	theType;
	OSErr			error = noErr;

	StDialogBoxHandler	theHandler(PPob_PluginDialog, this);
	mDialogBox = theHandler.GetDialog();
	Assert_(mDialogBox != nil);
	
	FinishCreateChooser();
	PopulateGroupBoxes();
	
	// Link Listeners and Broadcasters: linking of Listeners and
	// Broadcasters is partly done in the StDialogBoxHandler constructor
	// but the RidL resource does not contain the controls of the MPV's subpanels
	mPageCtrl->AddListener(mMultiPanel);
	mPageCtrl->AddListener(&theHandler);
	UReanimator::LinkListenerToBroadcasters( &theHandler, mInfoPane, PPob_PluginInfo );
	UReanimator::LinkListenerToBroadcasters( &theHandler, mOrderPane, PPob_PluginOrder );

	while (inPickerLoop) {
		MessageT theMessage;
		
		mDialogBox->Show();
		
		while (true) {
			theMessage = theHandler.DoDialog();
			
			if (msg_OK == theMessage) {
				break;
			} else if (msg_Cancel == theMessage) {
				inPickerLoop = false;
				break;
			} else if (msg_PluginInfoPgbx == theMessage) {
				// Retrieve the menu item and write it in the edit field
				CRezillaPlugin *	thePlugin;
				itemIndex = mInfoPgbx->GetValue();
				if ( CPluginsController::sPluginsList.FetchItemAt(itemIndex, thePlugin) && thePlugin != NULL) {
					UpdatePluginInfo(thePlugin);
				}
				break;  // Breaks out from the inner 'while' but still in the inPickerLoop 'while'
			} else if (msg_PluginOrderPgbx == theMessage) {
				itemIndex = mOrderPgbx->GetValue();
				::GetMenuItemText( mOrderPgbx->GetMacMenuH(), mOrderPgbx->GetValue(), theString );
				UMiscUtils::PStringToOSType( theString, theType);
				StoreCurrentOrder();
				UpdateOrderForType(theType);
				mCurrType = theType;
				mDialogBox->Refresh();
				break;  // Breaks out from the inner 'while' but still in the inPickerLoop 'while'
			}
		}
		
		// If the default button was hit, try to open the rezmaps
		if (msg_OK == theMessage) {
			// Save the current order panel
			StoreCurrentOrder();
			
			// Release the previous sPluginsDict and replace it by a copy of sTypesDict
			if (sTypesDict) {
				CFMutableDictionaryRef	newDict = ::CFDictionaryCreateMutableCopy(NULL, 0, sTypesDict);
				if (newDict) {
					::CFRelease(CPluginsController::sPluginsDict);
					CPluginsController::sPluginsDict = newDict;
				} 
			} 

			// Now get out of the outer 'while'
			inPickerLoop = false;
		} 
	}
	return error;
}


// ---------------------------------------------------------------------------
//   FinishCreateChooser											[private]
// ---------------------------------------------------------------------------

void
CPluginChooser::FinishCreateChooser()
{
	mCurrType = 0;
	
	mPageCtrl = dynamic_cast<LPageController*>(mDialogBox->FindPaneByID(item_PageController));
	ThrowIfNil_(mPageCtrl);
	
	mMultiPanel = dynamic_cast<LMultiPanelView*>(mDialogBox->FindPaneByID(item_MultiPanelView));
	ThrowIfNil_(mMultiPanel);
	
	// Create the panels before we call them
	mMultiPanel->CreateAllPanels();
	
	mInfoPane = mMultiPanel->GetPanel(mpv_PluginInfo);
	ThrowIfNil_(mInfoPane);
	
	mOrderPane = mMultiPanel->GetPanel(mpv_PluginOrder);
	ThrowIfNil_(mOrderPane);
	
	// Plugins info panel
	mInfoPgbx = dynamic_cast<LPopupGroupBox *>(mInfoPane->FindPaneByID( item_PluginInfoPgbx ));
	ThrowIfNil_(mInfoPgbx);
	
	mTypeField = dynamic_cast<LStaticText *>(mInfoPane->FindPaneByID( item_PluginInfoTypeText ));
	ThrowIfNil_(mTypeField);
	
	mCreatorField = dynamic_cast<LStaticText *>(mInfoPane->FindPaneByID( item_PluginInfoCreatorText ));
	ThrowIfNil_(mCreatorField);
	
	mVersionField = dynamic_cast<LStaticText *>(mInfoPane->FindPaneByID( item_PluginInfoVersionText ));
	ThrowIfNil_(mVersionField);
	
	mLoadedField = dynamic_cast<LStaticText *>(mInfoPane->FindPaneByID( item_PluginInfoLoadedText ));
	ThrowIfNil_(mLoadedField);
	
	mSupportedTypes = dynamic_cast<LPopupButton *>(mInfoPane->FindPaneByID( item_PluginSupportedTypes ));
	ThrowIfNil_(mSupportedTypes);

	mIconPane = dynamic_cast<CIconrefPane *>(mInfoPane->FindPaneByID( item_PluginInfoIconPane ));
	ThrowIfNil_(mIconPane);
	
	// Preferred plugins panel
	mOrderPgbx = dynamic_cast<LPopupGroupBox *>(mOrderPane->FindPaneByID( item_PluginOrderPgbx ));
	ThrowIfNil_(mOrderPgbx);
	
	mHelpField = dynamic_cast<LStaticText *>(mOrderPane->FindPaneByID( item_PluginHelpString ));
	ThrowIfNil_(mHelpField);
	
	mPluginOrderTable = dynamic_cast<CDragTable *>(mOrderPane->FindPaneByID( item_PluginOrderTable ));
	ThrowIfNil_(mPluginOrderTable);
	// Add a single column.
	mPluginOrderTable->InsertCols( 1, 0, nil );
	
	// Install the help string
	CFStringRef helpCFStr = ::CFCopyLocalizedString(CFSTR("PreferredPluginHelpString"), NULL);
	Str255      theString;
	if (helpCFStr != NULL) {
		if (::CFStringGetPascalString(helpCFStr, theString, sizeof(theString), ::GetApplicationTextEncoding())) {
			mHelpField->SetDescriptor(theString);
		}
		::CFRelease(helpCFStr);                             
	}
}


// ---------------------------------------------------------------------------
//   PopulateGroupBoxes											[protected]
// ---------------------------------------------------------------------------

void
CPluginChooser::PopulateGroupBoxes()
{
	CRezillaPlugin *	thePlugin;
	CFStringRef			theNameRef;
	Str255				theString;
	UInt32				index, theCount;
	CFTypeRef *			theKeys;
	CFIndex 			i, dictCount;
	OSType				theType;

	// Plugins group box popup
	theCount = CPluginsController::sPluginsList.GetCount();
		
	for (index = 1; index <= theCount; index++) {	
		if ( CPluginsController::sPluginsList.FetchItemAt(index, thePlugin) && thePlugin != NULL) {
			theNameRef = thePlugin->GetName();
			if ( ::CFStringGetPascalString(theNameRef, theString, sizeof(theString), NULL) ) {
				mInfoPgbx->InsertMenuItem(theString, index, true);
			}
			if (index == 1) {
				UpdatePluginInfo(thePlugin);
			} 
		}
	}
	
	// All types group box popup
	if (sTypesDict) {
		dictCount = ::CFDictionaryGetCount(sTypesDict);
		theKeys = (CFTypeRef*) ::NewPtrClear(sizeof(CFTypeRef) * dictCount);
		
		if (theKeys != NULL) {
			CTypeComparator* theComparator = new CTypeComparator;
			TArray<ResType>* theTypesArray = new TArray<ResType>( theComparator, true);

			if (theTypesArray) {
				::CFDictionaryGetKeysAndValues(sTypesDict, (const void **) theKeys, NULL);
				// Build a sorted array of all the types
				for (i = 0; i < dictCount; i++) {
					if (::CFNumberGetValue( (CFNumberRef) theKeys[i], kCFNumberSInt32Type, (void *) &theType)) {
						theTypesArray->AddItem(theType);
					} 
				}
				::DisposePtr( (char *) theKeys);
				// Install the types in the popup menu
				theCount = theTypesArray->GetCount();
				for (index = 1; index <= theCount; index++) {	
					if ( theTypesArray->FetchItemAt(index, theType) && theType != 0) {
						UMiscUtils::OSTypeToPString(theType, theString);
						mOrderPgbx->InsertMenuItem(theString, i+1, true);
						if (index == 1) {
							UpdateOrderForType(theType);
							mCurrType = theType;
						} 
					}
				}
				delete theTypesArray;
			} 
		} 
	} 
}


// ---------------------------------------------------------------------------
//   UpdatePluginInfo											[private]
// ---------------------------------------------------------------------------

void
CPluginChooser::UpdatePluginInfo(CRezillaPlugin * inPlugin)
{
	Str255			theString;
	UInt32			index, theCount;
	IconRef			theIconRef;
	
	// Plugins group box popup
	UMiscUtils::OSTypeToPString(inPlugin->GetPluginType(), theString);
	mTypeField->SetDescriptor(theString);
	UMiscUtils::OSTypeToPString(inPlugin->GetPluginCreator(), theString);
	mCreatorField->SetDescriptor(theString);
	// mPluginVersion is an UInt32 in the 'vers' resource style (e-g 0x01008000 for 1.0.0)
	UMiscUtils::VersionStringFromValue(inPlugin->GetPluginVersion(), theString);
	mVersionField->SetDescriptor(theString);
	if (inPlugin->IsLoaded()) {
		mLoadedField->SetDescriptor("\pyes");
	} else {
		mLoadedField->SetDescriptor("\pno");
	}
	
	theIconRef = inPlugin->GetIconRef();
	if (theIconRef != 0) {
		mIconPane->SetIconRef(theIconRef);
	} 
	
	// Populate the supported types popup
	theCount = inPlugin->CountEditTypes();
	if (theCount > 0) {
		OSType				theType;
		TArray<OSType> *	theTypesList = inPlugin->GetEditTypes();
		
		mSupportedTypes->DeleteAllMenuItems();
		for (index = 1; index <= theCount; index++) {	
			if ( theTypesList->FetchItemAt(index, theType) && theType != 0) {
				UMiscUtils::OSTypeToPString(theType, theString);
				mSupportedTypes->InsertMenuItem(theString, index, true);
			}
		}
	} 
	mDialogBox->Refresh();
}


// ---------------------------------------------------------------------------
//   UpdateOrderForType										[private]
// ---------------------------------------------------------------------------

void
CPluginChooser::UpdateOrderForType(ResType inType)
{
	TableCellT			theCell;
	TableIndexT			theRows, theCols;
	Str255				theString;
	CFMutableArrayRef	theArray;
	CFNumberRef			theKey;
	CFIndex				i, theCount;
	CFNumberRef			thePlugRef;
	CRezillaPlugin *	thePlugin;
	CFStringRef			theNameRef;

	if (!sTypesDict) return;
	
	// Erase the current rows
	mPluginOrderTable->GetTableSize(theRows, theCols);
	mPluginOrderTable->RemoveRows(theRows, 1);
	
	theCell.col = 1;
	
	theKey = ::CFNumberCreate(NULL, kCFNumberSInt32Type, &inType);
	if (theKey) {
		theArray = (CFMutableArrayRef) ::CFDictionaryGetValue( sTypesDict, theKey);
		
		if (theArray) {
			theCount = ::CFArrayGetCount(theArray);
			
			// Add rows for the items.
			mPluginOrderTable->InsertRows( theCount, 0, nil );
			
			for ( i = 0; i < theCount; i++ ) {
				thePlugRef = (CFNumberRef) ::CFArrayGetValueAtIndex(theArray, i);
				thePlugin = NULL;
				
				if (thePlugRef != nil) {
					if (::CFNumberGetValue( (CFNumberRef) thePlugRef, kCFNumberSInt32Type, (void *) &thePlugin)) {
						if (thePlugin) {
							theNameRef = thePlugin->GetName();
							if ( ::CFStringGetPascalString(theNameRef, theString, sizeof(theString), NULL) ) {
								// Set the cell data.
								theCell.row = i+1;
								mPluginOrderTable->SetCellData( theCell, theString );
							}
						} 
					} 
				} 
			}
			
			if (theCount > 1) {
				mHelpField->Show();
			} else {
// 				mHelpField->Hide();
			}
		} 
		::CFRelease(theKey);
	} 
}




// ---------------------------------------------------------------------------
//   StoreCurrentOrder												[private]
// ---------------------------------------------------------------------------

void
CPluginChooser::StoreCurrentOrder()
{
	CFMutableArrayRef	theArrayRef;
	CFNumberRef			theKeyRef, thePlugRef;
	CFStringRef			theNameRef;
	TableCellT			theCell;
	TableIndexT			theRows, theCols, rowIndex;
	CRezillaPlugin *	thePlugin;
	Str255				theString;

	if (!sTypesDict) return;

	theArrayRef = ::CFArrayCreateMutable(NULL, 0, &kCFTypeArrayCallBacks);

	if (theArrayRef) {
		// Retrieve the items from the table
		theCell.col = 1;
		mPluginOrderTable->GetTableSize(theRows, theCols);
		for ( rowIndex = 1; rowIndex <= theRows; rowIndex++) {
			theCell.row = rowIndex;
			mPluginOrderTable->GetCellData(theCell, theString);
			theNameRef = ::CFStringCreateWithPascalString(NULL, theString, kCFStringEncodingMacRoman);
			if (theNameRef) {
				thePlugin = CPluginsController::GetPluginFromName(theNameRef);
				if (thePlugin != NULL) {
					thePlugRef = ::CFNumberCreate(NULL, kCFNumberSInt32Type, &thePlugin);
					if (thePlugRef) {
						::CFArrayAppendValue(theArrayRef, thePlugRef);
						::CFRelease(thePlugRef);
					}
				}
			}
			::CFRelease(theNameRef);
		}
		theKeyRef = ::CFNumberCreate(NULL, kCFNumberSInt32Type, &mCurrType);

		if (theKeyRef) {
			::CFDictionaryReplaceValue(sTypesDict, theKeyRef, theArrayRef);
			::CFRelease(theKeyRef);
		} 
		::CFRelease(theArrayRef);
	} 
}

