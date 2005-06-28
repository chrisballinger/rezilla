// ===========================================================================
// CIcon_EditorDoc.cp
// 
//                       Created: 2004-12-11 23:33:03
//             Last modification: 2005-06-28 16:42:42
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

PP_Begin_Namespace_PowerPlant


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CIcon_EditorDoc.h"
#include "CIcon_EditorWindow.h"
#include "CIcon_EditorView.h"
#include "CEditorsController.h"
#include "RezillaConstants.h"
#include "CWindow_Picture.h"
#include "CWindow_Pattern.h"
#include "CWindow_Cursor.h"
#include "CWindow_IconFamily.h"
#include "CWindow_ColorIcon.h"
#include "CWindow_IconSuite.h"
#include "CWindow_PatternSuite.h"
#include "CRezMap.h"
#include "CRezMapTable.h"
#include "CRezMapDoc.h"
#include "CRezObj.h"
#include "CRezillaPrefs.h"
#include "UCodeTranslator.h"
#include "UDialogBoxHandler.h"
#include "UMessageDialogs.h"

#include <LWindow.h>
#include <LFile.h>
#include <UStandardDialogs.h>
#include <LRadioGroupView.h>
#include <LCheckBox.h>
#include <LEditField.h>
#include <LDataStream.h>

#include <LString.h>
#include <PP_Messages.h>


// ---------------------------------------------------------------------------
//	¥ CIcon_EditorDoc							Constructor		  [public]
// ---------------------------------------------------------------------------

CIcon_EditorDoc::CIcon_EditorDoc(LCommander* inSuper, 
								 CRezMapTable* inSuperMap,
								 CRezObj* inRezObj,
								 ResType inSubstType,
								 Boolean inReadOnly)
 	: CEditorDoc(inSuper, inSuperMap, inRezObj, inSubstType, inReadOnly)
{
	Initialize();
}


// ---------------------------------------------------------------------------
//	¥ ~CIcon_EditorDoc							Destructor			[public]
// ---------------------------------------------------------------------------

CIcon_EditorDoc::~CIcon_EditorDoc()
{
	if (mIconEditWindow != nil) {
		// Remove the attachments before deleting the window. This is
		// because, when deleting the LUndoer, some actions like
		// CIconViewResizer make calls to the window to purge some buffers
		// (see DeleteAllBuffers for instance) and would provoke a crash if
		// the window was not valid anymore.
		mIconEditWindow->RemoveAllAttachments();

		// Now delete the window
		delete mIconEditWindow;
		mIconEditWindow = nil;
	} 
}


// ---------------------------------------------------------------------------
//	¥ Initialize													  [public]
// ---------------------------------------------------------------------------

void
CIcon_EditorDoc::Initialize()
{
	LWindow	*	theWindow = nil;
	CRezMap *	theMap = mRezMapTable->GetRezMap();
	ResIDT		theID = mRezObj->GetID();
	
	mIconEditWindow = nil;

	try {		
		// Create the document window
		switch (mSubstType) {
			// 'ICON'
			case ImgType_LargeIcon:
				theWindow = CWindow_IconFamily::OpenPaintWindow( PPob_ICONEditor, theMap, theID );
				break;

			// 'ICN#', 'icl4', 'icl8', 'ics#', 'ics4', 'ics8', 'icm#', 'icm4', 'icm8'
			case ImgType_LargeIconWithMask:
			case ImgType_Large4BitIcon:
			case ImgType_Large8BitIcon:
			case ImgType_SmallIconWithMask:
			case ImgType_Small4BitIcon:
			case ImgType_Small8BitIcon:
			case ImgType_MiniIconWithMask:
			case ImgType_Mini4BitIcon:
			case ImgType_Mini8BitIcon:
				theWindow = CWindow_IconFamily::OpenPaintWindow( PPob_IconFamilyEditor, theMap, theID );
				break;
				
			// 'cicn'
			case ImgType_ColorIcon:
				theWindow = CWindow_ColorIcon::OpenPaintWindow( mRezObj, PPob_CICNEditor );
				break;

			// 'PICT'
			case ImgType_Picture:
				theWindow = CWindow_Picture::OpenPaintWindow( mRezObj, PPob_PictEditor );
				break;
				
			// 'PAT#'
			case ImgType_PatternSuite:
				theWindow = CWindow_PatternSuite::OpenPaintWindow( mRezObj, PPob_PatternSuiteEditor );
				break;
					
			// 'SICN'
			case ImgType_IconSuite:
				theWindow = CWindow_IconSuite::OpenPaintWindow( mRezObj, PPob_IconSuiteEditor );
				break;
					
			// 'CURS'
			case ImgType_Cursor:
				theWindow = CWindow_Cursor::OpenPaintWindow( mRezObj, PPob_CursorEditor );
				break;

			// 'crsr'
			case ImgType_ColorCursor:
				theWindow = CWindow_Cursor::OpenPaintWindow( mRezObj, PPob_ColorCursorEditor );
				break;
				
			// 'PAT '
			case ImgType_Pattern:
				theWindow = CWindow_Pattern::OpenPaintWindow( mRezObj, PPob_PatternEditor );
				break;
				
			// 'ppat'
			case ImgType_PixPat:
				theWindow = CWindow_Pattern::OpenPaintWindow( mRezObj, PPob_PixPatEditor );
				break;

		}
		
		mIconEditWindow = dynamic_cast<CIcon_EditorWindow *>( theWindow );
		Assert_( mIconEditWindow != nil );
		
		SetMainWindow( dynamic_cast<CEditorWindow *>(mIconEditWindow) );
		NameNewEditorDoc();
		// Other editing windows set the super commander directly via the 
		// CreateWindow() function. Here we must do it explicitely since 
		// we use OpenPaintWindow() instead of CreateWindow().
		mIconEditWindow->SetSuperCommander(this);
		mIconEditWindow->Finalize(this);

	}
	catch (...) {
		UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("ErrorInitializingBitmapEditor"), PPob_SimpleMessage);	
		delete this;
		return;
	}
			
	// Make the window visible.
	mIconEditWindow->Show();
}


// ---------------------------------------------------------------------------
//	¥ GetDescriptor													  [public]
// ---------------------------------------------------------------------------
//	Pass back the name of a Document

StringPtr
CIcon_EditorDoc::GetDescriptor(
	Str255	outDescriptor) const
{
	if (mIconEditWindow != nil) {
		// Use name of its window
		mIconEditWindow->GetDescriptor(outDescriptor);
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
CIcon_EditorDoc::FindCommandStatus(
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
//	¥ AllowSubRemoval												  [public]
// ---------------------------------------------------------------------------

Boolean
CIcon_EditorDoc::AllowSubRemoval(
	LCommander*		inSub)
{
	if (inSub == mIconEditWindow) {
		AttemptClose(false);
		return false;
	} else {
		return true;
	}
}


// ---------------------------------------------------------------------------
//	¥ AskSaveChanges												  [public]
// ---------------------------------------------------------------------------
// Ask user whether to save changes before closing the Document.

SInt16
CIcon_EditorDoc::AskSaveChanges(
	bool /* inQuitting */)
{
	return UMessageDialogs::AskYesNoFromLocalizable(CFSTR("SaveBitmapEditorWindow"), PPob_AskYesNoMessage);
}


// ---------------------------------------------------------------------------
//  ¥ GetModifiedResource										[protected]
// ---------------------------------------------------------------------------

Handle
CIcon_EditorDoc::GetModifiedResource(Boolean &releaseIt) 
{
#pragma unused(releaseIt)

	try {
		// The resource is saved directly
		mIconEditWindow->SaveAsResource( mRezMapTable->GetRezMap(), mRezObj->GetID() );
	}
	catch (...) {
		UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("ErrorSavingBitmapResource"), PPob_SimpleMessage);	
	}
	
	// Refresh the view to update the size field
	mRezMapTable->Refresh();

	// Return a NULL handle because the resource is already saved
	return (Handle) NULL;
}



PP_End_Namespace_PowerPlant


