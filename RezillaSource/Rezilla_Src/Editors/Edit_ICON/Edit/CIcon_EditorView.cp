// ===========================================================================
// CIcon_EditorView.cp
// 
//                       Created: 2004-12-10 17:23:05
//             Last modification: 2004-12-10 17:23:10
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CIcon_EditorDoc.h"
#include "CIcon_EditorView.h"
#include "CIcon_EditorWindow.h"
#include "CRezObj.h"
#include "CRezillaPrefs.h"


PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//	¥ CIcon_EditorView							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CIcon_EditorView::CIcon_EditorView()
		: LView()
{
}


// ---------------------------------------------------------------------------
//	¥ CIcon_EditorView							Parameterized Constructor [public]
// ---------------------------------------------------------------------------

CIcon_EditorView::CIcon_EditorView(
	const SPaneInfo&	inPaneInfo,
	const SViewInfo&	inViewInfo)

	: LView(inPaneInfo, inViewInfo)
{
}


// ---------------------------------------------------------------------------
//	¥ CIcon_EditorView							Stream Constructor		  [public]
// ---------------------------------------------------------------------------
// Use the Preference interface settings when creating a new TEXT resource.

CIcon_EditorView::CIcon_EditorView(
	LStream*	inStream)

	: LView(inStream)
{
}


// ---------------------------------------------------------------------------
//	¥ ~CIcon_EditorView						Destructor				  [public]
// ---------------------------------------------------------------------------

CIcon_EditorView::~CIcon_EditorView()
{
}



#pragma mark -

// ---------------------------------------------------------------------------
//	¥ ClickSelf								[protected, virtual]
// ---------------------------------------------------------------------------

void
CIcon_EditorView::ClickSelf(
	const SMouseDownEvent	&inMouseDown)
{
	LView::ClickSelf(inMouseDown);
	
}


// ---------------------------------------------------------------------------
//	¥ HandleKeyPress							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CIcon_EditorView::HandleKeyPress(
	const EventRecord	&inKeyEvent)
{
	Boolean		keyHandled	 = true;
// 	LView::HandleKeyPress(inKeyEvent);
	
	if (UKeyFilters::PrintingCharField(inKeyEvent) == keyStatus_TECursor) {
// 		mOwnerWindow->AdjustMenusToSelection();
	} 
	mOwnerWindow->SetCoordsField(0, 0);   // todo: insert right coords
	return keyHandled;
}


// ---------------------------------------------------------------------------
//	¥ ObeyCommand							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CIcon_EditorView::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;

	switch (inCommand) {

		case cmd_Cut: 
		case cmd_Paste: 
		case cmd_Clear: 
// 		LTextEditView::ObeyCommand(inCommand, ioParam);
		mOwnerWindow->SetCoordsField(0, 0);   // todo: insert right coords
		break;

		default:
			cmdHandled = dynamic_cast<CIcon_EditorWindow *>(mOwnerWindow)->ObeyCommand(inCommand, ioParam);
			break;
	}

	return cmdHandled;
}


// ---------------------------------------------------------------------------
//	¥ UserChangedBitmap						[public, virtual]
// ---------------------------------------------------------------------------
//	Bitmap has changed as a result of user action

void
CIcon_EditorView::UserChangedBitmap()
{
	if ( ! mOwnerWindow->IsDirty() ) {

		// Set the update menus flag.
		LCommander::SetUpdateCommandStatus( true );
		
		// Set the dirty flag.
		mOwnerWindow->SetDirty( true );
	}
}


// ---------------------------------------------------------------------------
//  ¥ GetModifiedBitmap										[public]
// ---------------------------------------------------------------------------

Handle
CIcon_EditorView::GetModifiedBitmap() 
{
	Handle	outTextHandle = NULL;
	
	return outTextHandle;
}




PP_End_Namespace_PowerPlant
