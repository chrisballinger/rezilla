// ===========================================================================
// CMENU_EditorDoc.cp
// 
//                       Created: 2005-03-09 17:16:53
//             Last modification: 2005-03-16 10:24:10
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

PP_Begin_Namespace_PowerPlant


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CMENU_EditorDoc.h"
#include "CMENU_EditorWindow.h"
#include "CMENU_EditorTable.h"
#include "CEditorsController.h"
#include "RezillaConstants.h"
#include "CRezMap.h"
#include "CRezMapTable.h"
#include "CRezMapDoc.h"
#include "CRezObj.h"
#include "CRezillaPrefs.h"
#include "CWindowMenu.h"
#include "UCodeTranslator.h"
#include "UDialogBoxHandler.h"
#include "UMessageDialogs.h"
#include "UMiscUtils.h"

#include <LWindow.h>
#include <LFile.h>
#include <UStandardDialogs.h>
#include <LRadioGroupView.h>
#include <LCheckBox.h>
#include <LEditField.h>
#include <LDataStream.h>

#include <LString.h>
#include <PP_Messages.h>

// // Standard headers
// #include <string.h>


extern CWindowMenu * gWindowMenu;


// ---------------------------------------------------------------------------
//  CMENU_EditorDoc							Constructor		  [public]
// ---------------------------------------------------------------------------

CMENU_EditorDoc::CMENU_EditorDoc(LCommander* inSuper, 
								 CRezMapTable* inSuperMap,
								 CRezObj* inRezObj,
								 ResType inSubstType,
								 Boolean inReadOnly)
 	: CEditorDoc(inSuper, inSuperMap, inRezObj, inSubstType, inReadOnly)
{
	Initialize();
}


// ---------------------------------------------------------------------------
//  ~CMENU_EditorDoc							Destructor		  [public]
// ---------------------------------------------------------------------------

CMENU_EditorDoc::~CMENU_EditorDoc()
{
	if (mMenuEditWindow != nil) {
		// Remove the window from the window menu.
		gWindowMenu->RemoveWindow( mMenuEditWindow );
		delete mMenuEditWindow;
	} 
}


// ---------------------------------------------------------------------------
//  Initialize													[public]
// ---------------------------------------------------------------------------

void
CMENU_EditorDoc::Initialize()
{
	OSErr error = noErr;
	
	// Create window for our document. This sets this doc as the SuperCommander of the window.
	mMenuEditWindow = dynamic_cast<CMENU_EditorWindow *>(LWindow::CreateWindow( PPob_MenuEditorWindow, this ));
	Assert_( mMenuEditWindow != nil );
	
	mMenuEditWindow->SetOwnerDoc(this);
	mMenuEditWindow->InstallResourceNameField();
	mMenuEditWindow->InstallReadOnlyIcon();
	SetMainWindow( dynamic_cast<CEditorWindow *>(mMenuEditWindow) );

	NameNewEditorDoc();
	
	// Add the window to the window menu.
	gWindowMenu->InsertWindow( mMenuEditWindow );
		
	try {
		// Install the data
		if (mRezObj != nil) {
			Handle rezData = mRezObj->GetData();
			
			if (rezData != nil) {
				Handle			xmnuData = NULL;
				CRezMap *		theRezMap = mRezMapTable->GetRezMap();
				// Work with a copy of the handle
				::HandToHand(&rezData);

				// Look for a 'xmnu' resource with same ID 
				error = theRezMap->GetWithID(ResType_ExtendedMenu, mRezObj->GetID(), xmnuData, true);
				if (xmnuData != nil) {
					::HandToHand(&xmnuData);
				} 			
				error = mMenuEditWindow->InstallResourceData(rezData, xmnuData);			
			} 
			ThrowIfError_(error);			
		} 
	} catch (...) {
		delete this;
		if (error == err_MoreDataThanExpected) {
				UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("ResourceLongerThanExpected"), PPob_SimpleMessage);
			} else if (error != userCanceledErr) {
				UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("ErrorWhileParsingResource"), error);
			} 
		return;
	}

	// Make the window visible.
	mMenuEditWindow->Show();
}


// ---------------------------------------------------------------------------
//  GetDescriptor													  [public]
// ---------------------------------------------------------------------------
//	Pass back the name of a Document

StringPtr
CMENU_EditorDoc::GetDescriptor(
	Str255	outDescriptor) const
{
	if (mMenuEditWindow != nil) {
		// Use name of its window
		mMenuEditWindow->GetDescriptor(outDescriptor);
	} else {
		// No window, document name is empty string
		outDescriptor[0] = 0;		
	}

	return outDescriptor;
}


// ---------------------------------------------------------------------------------
//  ¥ FindCommandStatus
// ---------------------------------------------------------------------------------

void
CMENU_EditorDoc::FindCommandStatus(
	CommandT	inCommand,
	Boolean		&outEnabled,
	Boolean		&outUsesMark,
	UInt16		&outMark,
	Str255		outName )
{
	switch ( inCommand ) {
	
	  default:
			// Call inherited.
		CEditorDoc::FindCommandStatus( inCommand,
				outEnabled, outUsesMark, outMark, outName );
		break;

	}
}


// ---------------------------------------------------------------------------
//  AllowSubRemoval												  [public]
// ---------------------------------------------------------------------------

Boolean
CMENU_EditorDoc::AllowSubRemoval(
	LCommander*		inSub)
{
	if (inSub == mMenuEditWindow) {
		AttemptClose(false);
		return false;
	} else {
		return true;
	}
}


// // ---------------------------------------------------------------------------
// //  AskSaveChanges												  [public]
// // ---------------------------------------------------------------------------
// //	Ask user whether to save changes before closing the Document.
// 
// SInt16
// CMENU_EditorDoc::AskSaveChanges(
// 	bool /* inQuitting */)
// {
// 	return UMessageDialogs::AskYesNoFromLocalizable(CFSTR("SaveMenuEditorWindow"), PPob_AskYesNoMessage);
// }


// ---------------------------------------------------------------------------
//  ¥ GetModifiedResource										[protected]
// ---------------------------------------------------------------------------
// The returned handle should not be released by the caller so leave
// releaseIt to false (its default).

Handle
CMENU_EditorDoc::GetModifiedResource(Boolean &releaseIt) 
{
#pragma unused(releaseIt)
	
	return mMenuEditWindow->CollectMenuData();
}


// ---------------------------------------------------------------------------------
//  ¥ SaveXmnuResource
// ---------------------------------------------------------------------------------

void
CMENU_EditorDoc::SaveXmnuResource(Handle inXmnuHandle)
{
	// Open or create a 'xmnu' resource and save the StScrpHandle therein
	CRezObj * xmnuRezObj = NULL;
	
	CEditorsController::OpenOrCreateWithTypeAndID(mRezMapTable, ResType_ExtendedMenu, mRezObj->GetID(), &xmnuRezObj);
	if (xmnuRezObj != NULL) {
		// Copy to resource's data handle
		xmnuRezObj->SetData(inXmnuHandle);

		// Mark the resource as modified in the rez map
		xmnuRezObj->Changed();

		// Tell the rezmap doc that there has been a modification
		mRezMapTable->GetOwnerDoc()->SetModified(true);
		// Refresh the view
		xmnuRezObj->SetSize( ::GetHandleSize(inXmnuHandle) );
		mRezMapTable->Refresh();
	} 
}



PP_End_Namespace_PowerPlant


// struct MenuInfo {
//   MenuID              menuID;                 /* in Carbon use Get/SetMenuID*/
//   short               menuWidth;              /* in Carbon use Get/SetMenuWidth*/
//   short               menuHeight;             /* in Carbon use Get/SetMenuHeight*/
//   Handle              menuProc;               /* not supported in Carbon*/
//   long                enableFlags;            /* in Carbon use Enable/DisableMenuItem, IsMenuItemEnable*/
//   Str255              menuData;               /* in Carbon use Get/SetMenuTitle*/
// };
