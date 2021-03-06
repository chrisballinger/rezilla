// ===========================================================================
// CSTRx_EditorDoc.cp
// 
//                       Created: 2005-08-31 18:26:24
//             Last modification: 2006-10-09 16:43:59
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2005-2006
// All rights reserved.
// ===========================================================================

PP_Begin_Namespace_PowerPlant


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CSTRx_EditorDoc.h"
#include "CSTRx_EditorWindow.h"
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
//  CSTRx_EditorDoc							Constructor		  [public]
// ---------------------------------------------------------------------------

CSTRx_EditorDoc::CSTRx_EditorDoc(LCommander* inSuper, 
								 CRezMapTable* inSuperMap,
								 CRezObj* inRezObj,
								 ResType inSubstType,
								 Boolean inReadOnly)
 	: CEditorDoc(inSuper, inSuperMap, inRezObj, inSubstType, inReadOnly)
{
	Initialize();
}


// ---------------------------------------------------------------------------
//  ~CSTRx_EditorDoc							Destructor		  [public]
// ---------------------------------------------------------------------------

CSTRx_EditorDoc::~CSTRx_EditorDoc()
{
	if (mStrxEditWindow != nil) {
		delete mStrxEditWindow;
	} 
}


// ---------------------------------------------------------------------------
//  Initialize													[private]
// ---------------------------------------------------------------------------

void
CSTRx_EditorDoc::Initialize()
{
	OSErr error = noErr;
	
	// Create a window for our document and set this doc as its SuperCommander
	mStrxEditWindow = dynamic_cast<CSTRx_EditorWindow *>(LWindow::CreateWindow( PPob_StrxEditorWindow, this ));
	Assert_( mStrxEditWindow != nil );
	
	SetMainWindow( dynamic_cast<CEditorWindow *>(mStrxEditWindow) );
	NameNewEditorDoc();
	mStrxEditWindow->FinalizeEditor(this);
	mStrxEditWindow->SetFlipped(GetRezObj()->IsTypeNativeEndian());
	
	try {
		// Install the data
		if (mRezObj != nil) {
			Handle rezData = mRezObj->GetData();
			
			if (rezData != nil) {
				// Work with a copy of the handle
				::HandToHand(&rezData);
				
				error = mStrxEditWindow->InstallResourceData(rezData);			
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
	mStrxEditWindow->Show();
	// Enable all the subpanes
	mStrxEditWindow->GetContentsView()->Enable();
}


// ---------------------------------------------------------------------------
//  GetDescriptor													  [public]
// ---------------------------------------------------------------------------
//	Pass back the name of a Document

StringPtr
CSTRx_EditorDoc::GetDescriptor(
	Str255	outDescriptor) const
{
	if (mStrxEditWindow != nil) {
		// Use name of its window
		mStrxEditWindow->GetDescriptor(outDescriptor);
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
CSTRx_EditorDoc::CopyCFDescriptor() const
{
	CFStringRef		docName = nil;
	if (mStrxEditWindow != nil) {
		docName = mStrxEditWindow->CopyCFDescriptor();
	}
	return docName;
}
#endif


// ---------------------------------------------------------------------------
//  AllowSubRemoval												  [public]
// ---------------------------------------------------------------------------

Boolean
CSTRx_EditorDoc::AllowSubRemoval(
	LCommander*		inSub)
{
	if (inSub == mStrxEditWindow) {
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
CSTRx_EditorDoc::GetModifiedResource(Boolean &releaseIt) 
{
#pragma unused(releaseIt)
	
	return mStrxEditWindow->CollectResourceData();
}



PP_End_Namespace_PowerPlant
