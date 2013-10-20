// ===========================================================================
// CTmplEditorDoc.cp					
// 
//                       Created: 2004-06-12 10:06:22
//             Last modification: 2006-10-09 16:46:10
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2004-2006
// All rights reserved.
// ===========================================================================

PP_Begin_Namespace_PowerPlant


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CTmplEditorDoc.h"
#include "CTmplEditorWindow.h"
#include "RezillaConstants.h"
#include "CRezFile.h"
#include "CRezMap.h"
#include "CRezMapDoc.h"
#include "CRezObj.h"
#include "CRezillaApp.h"
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
//   CTmplEditorDoc							Constructor		  [public]
// ---------------------------------------------------------------------------
// 	: CEditorController( inSuperMap )

CTmplEditorDoc::CTmplEditorDoc(LCommander* inSuper, 
							   CRezMapTable* inSuperMap, 
							   CRezObj* inRezObj,
							   ResType inSubstType,
							   Boolean inReadOnly)
 	: CEditorDoc(inSuper, inSuperMap, inRezObj, inSubstType, inReadOnly)
{
	Initialize();
}


// ---------------------------------------------------------------------------
//     ~CTmplEditorDoc							Destructor				  [public]
// ---------------------------------------------------------------------------

CTmplEditorDoc::~CTmplEditorDoc()
{
	if (mTmplEditWindow != nil) {
		delete mTmplEditWindow;
	} 
}


// ---------------------------------------------------------------------------
//   Initialize													  [private]
// ---------------------------------------------------------------------------

void
CTmplEditorDoc::Initialize()
{
	OSErr error;
	
	mKind = editor_kindTmpl;
	SetModelKind(rzom_cTmplEditDoc);

	// Create a window for our document and set this doc as its SuperCommander
	mTmplEditWindow = dynamic_cast<CTmplEditorWindow *>(LWindow::CreateWindow( PPob_TmplEditorWindow, this ));
	Assert_( mTmplEditWindow != nil );
	
	SetMainWindow( dynamic_cast<CEditorWindow *>(mTmplEditWindow) );
	NameNewEditorDoc();
	mTmplEditWindow->FinalizeEditor(this);
	mTmplEditWindow->SetFlipped(GetRezObj()->IsTypeNativeEndian());

	// Install the contents according to the TMPL
	if (mRezObj != nil) {
		Handle rezData = mRezObj->GetData();
		if (rezData != nil) {
			// Work with a copy of the handle
			::HandToHand(&rezData);
			
			try {
				error = mTmplEditWindow->ParseDataWithTemplate(rezData);						
			} catch (...) {
				error = err_ExceptionParsingTemplate;
			}
		} 
	} 
	
	if (error != noErr) {
		if (error == err_ExceptionParsingTemplate) {
			UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("TemplateParsingException"), PPob_SimpleMessage);
		} else if (error != userCanceledErr) {
			UMessageDialogs::DescribeError(CFSTR("ErrorParsingWithTemplate"), error);
		} 
		delete this;
		return;
	} 

	// Make the window visible.
	mTmplEditWindow->Show();
	// Enable all the subpanes
	mTmplEditWindow->GetContentsView()->Enable();
}


// ---------------------------------------------------------------------------
//   GetDescriptor													  [public]
// ---------------------------------------------------------------------------
//	Pass back the name of a Document

StringPtr
CTmplEditorDoc::GetDescriptor(
	Str255	outDescriptor) const
{
	if (mTmplEditWindow != nil) {
		// Use name of its window
		mTmplEditWindow->GetDescriptor(outDescriptor);
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
CTmplEditorDoc::CopyCFDescriptor() const
{
	CFStringRef			docName = nil;
	if (mTmplEditWindow != nil) {
		docName = mTmplEditWindow->CopyCFDescriptor();
	}
	return docName;
}
#endif


// ---------------------------------------------------------------------------
//   AllowSubRemoval												  [public]
// ---------------------------------------------------------------------------

Boolean
CTmplEditorDoc::AllowSubRemoval(
	LCommander*		inSub)
{
	if (inSub == mTmplEditWindow) {
		AttemptClose(false);
		return false;
	} else {
		return true;
	}
}


// ---------------------------------------------------------------------------
//   AskSaveChanges												  [public]
// ---------------------------------------------------------------------------
//	Ask user whether to save changes before closing the Document or
//	quitting the Application

SInt16
CTmplEditorDoc::AskSaveChanges(
	bool /* inQuitting */)
{
	return UMessageDialogs::AskYesNoFromLocalizable(CFSTR("SaveTemplateWindow"), PPob_AskYesNoMessage);
}



// ---------------------------------------------------------------------------
//   GetModifiedResource										[public]
// ---------------------------------------------------------------------------
// The returned handle should not be released by the caller so leave
// releaseIt to false (its default).

Handle
CTmplEditorDoc::GetModifiedResource(Boolean &releaseIt) 
{
	Handle theHandle = NULL;
	OSErr error = mTmplEditWindow->RetrieveDataWithTemplate();

	releaseIt = false;
	if ( error != noErr ) {
		UMessageDialogs::DescribeError(CFSTR("ErrorSavingTemplateWindow"), error);
	} else {
		if (mTmplEditWindow->GetOutStream() != NULL) {
			theHandle = mTmplEditWindow->GetOutStream()->GetDataHandle();
		} 
	}
	
	return theHandle;
}


PP_End_Namespace_PowerPlant


