// ===========================================================================
// CMENU_EditorDoc.cp
// 
//                       Created: 2005-03-09 17:16:53
//             Last modification: 2006-10-09 16:43:36
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2005, 2006
// All rights reserved.
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
		delete mMenuEditWindow;
	} 
}


// ---------------------------------------------------------------------------
//  Initialize													[private]
// ---------------------------------------------------------------------------

void
CMENU_EditorDoc::Initialize()
{
	OSErr error = noErr, ignoreErr;
	
	// Create a window for our document and set this doc as its SuperCommander
	mMenuEditWindow = dynamic_cast<CMENU_EditorWindow *>(LWindow::CreateWindow( PPob_MenuEditorWindow, this ));
	Assert_( mMenuEditWindow != nil );
	
	SetMainWindow( dynamic_cast<CEditorWindow *>(mMenuEditWindow) );
	NameNewEditorDoc();
	mMenuEditWindow->FinalizeEditor(this);

	try {
		// Install the data
		if (mRezObj != nil) {
			Handle rezData = mRezObj->GetData();
			
			if (rezData != nil) {
				Handle			xmnuData = NULL;
				CRezMap *		theRezMap = mRezMapTable->GetRezMap();
				
				// Look for a 'xmnu' resource with same ID 
				ignoreErr = theRezMap->GetWithID(ResType_ExtendedMenu, mRezObj->GetID(), xmnuData, true);
				if (xmnuData != nil) {
					// Check that the xmnu resource is not already edited
					CRezMapDoc * ownerDoc = mRezMapTable->GetOwnerDoc();
					ThrowIfNil_(ownerDoc);
					
					if ( ownerDoc->GetRezEditor(ResType_ExtendedMenu, mRezObj->GetID(), true) != nil) {
						UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("XmnuAlreadyEdited"), PPob_SimpleMessage);
						error = userCanceledErr;  // We don't want a second message
					} else {
						::HandToHand(&xmnuData);
						error = ::MemError();
					}
				} 
				
				if (error == noErr) {
					// Work with a copy of the handle
					::HandToHand(&rezData);

					error = mMenuEditWindow->InstallResourceData(rezData, xmnuData);			
				} 
				
			} 
			ThrowIfError_(error);			
		} 
	} catch (...) {
		delete this;
		if (error == err_MoreDataThanExpected) {
			UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("ResourceLongerThanExpected"), PPob_SimpleMessage);
		} else if (error != userCanceledErr) {
			UMessageDialogs::AlertWithValue(CFSTR("ErrorWhileParsingResource"), error);
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


#if PP_Uses_CFDescriptor
// ---------------------------------------------------------------------------
//	CopyCFDescriptor												  [public]
// ---------------------------------------------------------------------------

CFStringRef
CMENU_EditorDoc::CopyCFDescriptor() const
{
	CFStringRef		docName = nil;
	if (mMenuEditWindow != nil) {
		docName = mMenuEditWindow->CopyCFDescriptor();
	}
	return docName;
}
#endif


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


// ---------------------------------------------------------------------------
//   GetModifiedResource										[protected]
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
//   SaveXmnuResource
// ---------------------------------------------------------------------------------

void
CMENU_EditorDoc::SaveXmnuResource(Handle inXmnuHandle)
{
	if (inXmnuHandle == NULL) {
		return;
	} 
	
	// Open or create a 'xmnu' resource and save the extended data therein
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
