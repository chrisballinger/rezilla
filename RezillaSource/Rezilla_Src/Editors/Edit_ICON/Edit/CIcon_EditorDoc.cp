// ===========================================================================
// CIcon_EditorDoc.cp
// 
//                       Created: 2004-12-11 23:33:03
//             Last modification: 2004-12-28 16:15:05
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
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
#include "CRezMap.h"
#include "CRezMapTable.h"
#include "CRezMapDoc.h"
#include "CRezObj.h"
#include "CRezillaPrefs.h"
#include "CWindowMenu.h"
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


extern CWindowMenu * gWindowMenu;


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
		// Remove the window from the window menu.
		gWindowMenu->RemoveWindow( mIconEditWindow );
		delete mIconEditWindow;
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
			theWindow = CWindow_IconFamily::OpenPaintWindow( PPob_IconSuiteEditor, theMap, theID );
			break;
			
		// 'cicn'
		case ImgType_ColorIcon:
			theWindow = CWindow_ColorIcon::OpenPaintWindow( PPob_CICNEditor, theMap, theID );
			break;

		// 'PICT'
		case ImgType_Picture:
			theWindow = CWindow_Picture::OpenPaintWindow( PPob_PictEditor, theMap, theID );
			break;
			
		// 'CURS'
		case ImgType_Cursor:
			theWindow = CWindow_Cursor::OpenPaintWindow( PPob_CursorEditor, theMap, 
														ImgType_Cursor, theID );
			break;

		// 'crsr'
		case ImgType_ColorCursor:
			theWindow = CWindow_Cursor::OpenPaintWindow( PPob_ColorCursorEditor, theMap, 
														ImgType_ColorCursor, theID );
			break;
			
		// 'PAT '
		case ImgType_Pattern:
			theWindow = CWindow_Pattern::OpenPaintWindow( PPob_PatternEditor, theMap, 
														 ImgType_Pattern, theID );
			break;
			
		// 'ppat'
		case ImgType_PixPat:
			theWindow = CWindow_Pattern::OpenPaintWindow( PPob_PixPatEditor, theMap, 
														 ImgType_PixPat, theID );
			break;
	}
	
	mIconEditWindow = dynamic_cast<CIcon_EditorWindow *>( theWindow );
	Assert_( mIconEditWindow != nil );
	
	mIconEditWindow->SetSuperCommander(this);
	mIconEditWindow->SetOwnerDoc(this);
	mIconEditWindow->InstallReadOnlyIcon();
	SetMainWindow( dynamic_cast<CEditorWindow *>(mIconEditWindow) );

	NameNewEditorDoc();
	
	// Add the window to the window menu.
	gWindowMenu->InsertWindow( mIconEditWindow );
		
// 	// Install the contents
// 	if (mRezObj != nil) {
// 		Handle rezData = mRezObj->GetData();
// 		
// 		if (rezData != nil) {
// 			mIconEditWindow->InstallBitmap(rezData);			
// 		} 
// 	} 
		
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
//	Ask user whether to save changes before closing the Document.

SInt16
CIcon_EditorDoc::AskSaveChanges(
	bool /* inQuitting */)
{
	return UMessageDialogs::AskYesNoFromLocalizable(CFSTR("SaveTextEditorWindow"), PPob_AskYesNoMessage);
}


// ---------------------------------------------------------------------------
//  ¥ GetModifiedResource										[protected]
// ---------------------------------------------------------------------------

Handle
CIcon_EditorDoc::GetModifiedResource() 
{
	return mIconEditWindow->GetContentsView()->GetModifiedBitmap();
}



PP_End_Namespace_PowerPlant


