// ===========================================================================
// CPICT_EditorDoc.cp
// 
//                       Created: 2004-12-06 14:54:09
//             Last modification: 2006-10-09 16:46:26
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2004-2005, 2006
// All rights reserved.
// ===========================================================================

PP_Begin_Namespace_PowerPlant


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CPICT_EditorDoc.h"
#include "CPICT_EditorWindow.h"
#include "CPICT_EditorView.h"
#include "RezillaConstants.h"
#include "CRezObj.h"
#include "CWindowMenu.h"
#include "UCodeTranslator.h"
#include "UDialogBoxHandler.h"
#include "UMessageDialogs.h"
#include "UMiscUtils.h"
#include "UIconMisc.h"

#include <LWindow.h>
#include <UStandardDialogs.h>
#include <LRadioGroupView.h>

#include <LString.h>
#include <PP_Messages.h>


extern CWindowMenu * gWindowMenu;


// ---------------------------------------------------------------------------
//   CPICT_EditorDoc							Constructor		  [public]
// ---------------------------------------------------------------------------

CPICT_EditorDoc::CPICT_EditorDoc(LCommander* inSuper, 
								 CRezMapTable* inSuperMap,
								 CRezObj* inRezObj,
								 ResType inSubstType,
								 Boolean inReadOnly)
 	: CEditorDoc(inSuper, inSuperMap, inRezObj, inSubstType, inReadOnly)
{
	Initialize();
}


// ---------------------------------------------------------------------------
//     ~CPICT_EditorDoc							Destructor			  [public]
// ---------------------------------------------------------------------------

CPICT_EditorDoc::~CPICT_EditorDoc()
{
	if (mPictWindow != nil) {
		delete mPictWindow;
	} 
}


// ---------------------------------------------------------------------------
//   Initialize													  [public]
// ---------------------------------------------------------------------------

void
CPICT_EditorDoc::Initialize()
{
	// Create a window for our document and set this doc as its SuperCommander
	mPictWindow = dynamic_cast<CPICT_EditorWindow *>(LWindow::CreateWindow( PPob_PictEditorWindow, this ));
	Assert_( mPictWindow != nil );
	
	SetMainWindow( dynamic_cast<CEditorWindow *>(mPictWindow) );
	NameNewEditorDoc();
	mPictWindow->FinalizeEditor(this);

	// Install the contents
	try {
		if (mRezObj != nil) {
			Handle rezData = mRezObj->GetData();
			
			if (::GetHandleSize(rezData) < sizeof(Picture)) {
				::DisposeHandle(rezData);
				UIconMisc::GetDefaultBitmap(mRezObj, ImgType_Picture);
				rezData = mRezObj->GetData();
			} 
			
			if (rezData != nil) {			
				// Work with a copy of the handle
				::HandToHand(&rezData);
				mPictWindow->InstallPict(rezData);
				
				// Don't mark as modified
				mPictWindow->SetDirty(false);
			} 
		} 
	}
	catch (...) {
		UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("ErrorInitializingPictureViewer"), PPob_SimpleMessage);	
		delete this;
		return;
	}
		
	// Make the window visible.
	mPictWindow->Show();
}


// ---------------------------------------------------------------------------
//   GetDescriptor													  [public]
// ---------------------------------------------------------------------------
//	Pass back the name of a Document

StringPtr
CPICT_EditorDoc::GetDescriptor(
	Str255	outDescriptor) const
{
	if (mPictWindow != nil) {
		// Use name of its window
		mPictWindow->GetDescriptor(outDescriptor);
	} else {
		// No window, document name is empty string
		outDescriptor[0] = 0;		
	}

	return outDescriptor;
}


// ---------------------------------------------------------------------------------
//   FindCommandStatus
// ---------------------------------------------------------------------------------

void
CPICT_EditorDoc::FindCommandStatus(
	CommandT	inCommand,
	Boolean		&outEnabled,
	Boolean		&outUsesMark,
	UInt16		&outMark,
	Str255		outName )
{
	switch ( inCommand ) {
	
	  default:
		// Call inherited
		CEditorDoc::FindCommandStatus( inCommand,
				outEnabled, outUsesMark, outMark, outName );
		break;

	}
}


// ---------------------------------------------------------------------------
//   AllowSubRemoval												  [public]
// ---------------------------------------------------------------------------

Boolean
CPICT_EditorDoc::AllowSubRemoval(
	LCommander*		inSub)
{
	if (inSub == mPictWindow) {
		AttemptClose(false);
		return false;
	} else {
		return true;
	}
}


// ---------------------------------------------------------------------------
//   AskSaveChanges												  [public]
// ---------------------------------------------------------------------------
//	Ask user whether to save changes before closing the Document.

SInt16
CPICT_EditorDoc::AskSaveChanges(
	bool /* inQuitting */)
{
	return UMessageDialogs::AskYesNoFromLocalizable(CFSTR("SavePictEditorWindow"), PPob_AskYesNoMessage);
}


// ---------------------------------------------------------------------------
//   GetModifiedResource										[protected]
// ---------------------------------------------------------------------------
// The returned handle should not be released by the caller so leave
// releaseIt to false (its default).

Handle
CPICT_EditorDoc::GetModifiedResource(Boolean &releaseIt) 
{
#pragma unused(releaseIt)
	
	Handle theHandle = (Handle) mPictWindow->GetContentsView()->GetPictureH();
	if (theHandle == nil) {
		// If the pict handle is nil (if there was a cut action for 
		// instance), return a zero size handle.
		theHandle = ::NewHandle(0);
		mPictWindow->GetContentsView()->SetPictureH( (PicHandle) theHandle);
	} 
	return theHandle;
}



PP_End_Namespace_PowerPlant


