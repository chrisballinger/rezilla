// ===========================================================================
// CAete_EditorDoc.cp
// 
//                       Created: 2004-07-01 08:42:37
//             Last modification: 2005-01-20 22:28:47
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CRezillaApp.h"
#include "RezillaConstants.h"
#include "CAete_EditorDoc.h"
#include "CAete_EditorWindow.h"
#include "CAeteSuite.h"
#include "CAeteStream.h"
#include "CRezObj.h"
#include "CWindowMenu.h"
#include "UMessageDialogs.h"
#include "UAeteTranslator.h"

#include <PP_Messages.h>

#include <LArray.h>
#include <LWindow.h>
#include <LString.h>
#include <LStaticText.h>
#include <LPopupButton.h>
#include <LTableMonoGeometry.h>
#include <LTableSingleSelector.h>
#include <LTableArrayStorage.h>

#include <AEInteraction.h>
#include <AERegistry.h>
#include <AEObjects.h>
#include <AEPackObject.h>
#include <CFString.h>
#include <Lists.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>


PP_Begin_Namespace_PowerPlant

extern CWindowMenu * gWindowMenu;



// ---------------------------------------------------------------------------
//	¥ CAete_EditorDoc							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CAete_EditorDoc::CAete_EditorDoc(LCommander* inSuper,
								CRezMapTable* inSuperMap,
								CRezObj* inRezObj,
								ResType inSubstType,
								Boolean inReadOnly)
	: CEditorDoc(inSuper, inSuperMap, inRezObj, inSubstType, inReadOnly)
{
	Initialize();
}


// ---------------------------------------------------------------------------
//	¥ ~CAete_EditorDoc							Destructor				  [public]
// ---------------------------------------------------------------------------

CAete_EditorDoc::~CAete_EditorDoc()
{
	if (mAeteEditWindow != nil) {
		// Remove the window from the window menu.
		gWindowMenu->RemoveWindow( mAeteEditWindow );
		delete mAeteEditWindow;
	} 
}


// ---------------------------------------------------------------------------
//	¥ Initialize							Default Constructor		  [public]
// ---------------------------------------------------------------------------

void
CAete_EditorDoc::Initialize()
{
	mCurrCategory	= 1;
	
	for (SInt16	index = 0; index <= 4; index++) {
		mTotalCount[index] = 0;
	}

	// Create window for our document.
	mAeteEditWindow = dynamic_cast<CAete_EditorWindow *>(LWindow::CreateWindow( PPob_AeteEditorWindow, this ));
	Assert_( mAeteEditWindow != nil );
	
	mAeteEditWindow->SetOwnerDoc(this);
	mAeteEditWindow->InstallResourceNameField();
	mAeteEditWindow->InstallReadOnlyIcon();
	SetMainWindow( dynamic_cast<CEditorWindow *>(mAeteEditWindow) );

	// Name the window
	NameNewEditorDoc();
	
	// Add the window to the window menu.
	gWindowMenu->InsertWindow( mAeteEditWindow );
	
	// Install the contents
	if (mRezObj != nil) {
		Handle rezData = mRezObj->GetData();
		
		if (rezData != nil) {
// 			mAeteEditWindow->InstallAete(rezData);			
		} 
	} 
	
	// Make the window visible.
	mAeteEditWindow->Show();
}


// ---------------------------------------------------------------------------
//	¥ GetDescriptor													  [public]
// ---------------------------------------------------------------------------
//	Pass back the name of a Document

StringPtr
CAete_EditorDoc::GetDescriptor(
	Str255	outDescriptor) const
{
	if (mAeteEditWindow != nil) {
		// Use name of its window
		mAeteEditWindow->GetDescriptor(outDescriptor);
	} else {
		// No window, document name is empty string
		outDescriptor[0] = 0;		
	}

	return outDescriptor;
}


// ---------------------------------------------------------------------------
//	¥ AllowSubRemoval												  [public]
// ---------------------------------------------------------------------------

Boolean
CAete_EditorDoc::AllowSubRemoval(
	LCommander*		inSub)
{
	if (inSub == mAeteEditWindow) {
		AttemptClose(false);
		return false;
	} else {
		return true;
	}
}


// ---------------------------------------------------------------------------------
//		¥ IsModified
// ---------------------------------------------------------------------------------
// Consider a Dict as a modified document.

Boolean
CAete_EditorDoc::IsModified()
{
	return mIsModified;
}


// // ---------------------------------------------------------------------------
// //	¥ AskSaveChanges												  [public]
// // ---------------------------------------------------------------------------
// //	Ask user whether to save changes before closing the Dict. 
// //	There is a global pref sAskSaveDictOnClose to control this.
// 
// SInt16
// CAete_EditorDoc::AskSaveChanges(
// 	bool /* inQuitting */)
// {
// 	return UMessageDialogs::AskYesNoFromLocalizable(CFSTR("SaveAeteEditorWindow"), PPob_AskYesNoMessage);
// }


// ---------------------------------------------------------------------------------
//		¥ FindCommandStatus
// ---------------------------------------------------------------------------------

void
CAete_EditorDoc::FindCommandStatus(
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



PP_End_Namespace_PowerPlant




