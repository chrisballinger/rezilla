// ===========================================================================
// CTEXT_EditorView.cp
// 
//                       Created: 2004-06-19 13:23:32k
//             Last modification: 2004-06-20 18:42:25
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

#include "CTEXT_EditorView.h"
#include "CTEXT_EditorWindow.h"
#include "CRezObj.h"
#include "CRezMapDoc.h"
#include "CRezEditor.h"
#include "CTEXT_EditorDoc.h"
#include "CEditorDoc.h"
#include "CRezMapTable.h"


PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//	¥ CTEXT_EditorView							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CTEXT_EditorView::CTEXT_EditorView()
		: LTextEditView()
{
}


// ---------------------------------------------------------------------------
//	¥ CTEXT_EditorView							Parameterized Constructor [public]
// ---------------------------------------------------------------------------

CTEXT_EditorView::CTEXT_EditorView(
	const SPaneInfo&	inPaneInfo,
	const SViewInfo&	inViewInfo,
	UInt16				inTextAttributes,
	ResIDT				inTextTraitsID)

	: LTextEditView(inPaneInfo, inViewInfo, inTextAttributes, inTextTraitsID)
{
}


// ---------------------------------------------------------------------------
//	¥ CTEXT_EditorView							Stream Constructor		  [public]
// ---------------------------------------------------------------------------

CTEXT_EditorView::CTEXT_EditorView(
	LStream*	inStream)

	: LTextEditView(inStream)
{
}


// ---------------------------------------------------------------------------
//	¥ ~CTEXT_EditorView						Destructor				  [public]
// ---------------------------------------------------------------------------

CTEXT_EditorView::~CTEXT_EditorView()
{
}



#pragma mark -

// ---------------------------------------------------------------------------
//	¥ ClickSelf								[protected, virtual]
// ---------------------------------------------------------------------------

void
CTEXT_EditorView::ClickSelf(
	const SMouseDownEvent	&inMouseDown)
{
	LTextEditView::ClickSelf(inMouseDown);
	
	mOwnerWindow->AdjustMenusToSelection();
}


// ---------------------------------------------------------------------------
//	¥ HandleKeyPress							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CTEXT_EditorView::HandleKeyPress(
	const EventRecord	&inKeyEvent)
{
	Boolean		keyHandled	 = LTextEditView::HandleKeyPress(inKeyEvent);
	
	if (UKeyFilters::PrintingCharField(inKeyEvent) == keyStatus_TECursor) {
		mOwnerWindow->AdjustMenusToSelection();
	} 
	mOwnerWindow->SetLengthField();
	return keyHandled;
}


// ---------------------------------------------------------------------------
//	¥ ObeyCommand							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CTEXT_EditorView::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;

	if ( mTextEditH == nil )
		return cmdHandled;

	switch (inCommand) {

		case cmd_Cut: 
		case cmd_Paste: 
		case cmd_Clear: 
		LTextEditView::ObeyCommand(inCommand, ioParam);
		mOwnerWindow->SetLengthField();
		break;

		default:
			cmdHandled = LTextEditView::ObeyCommand(inCommand, ioParam);
			break;
	}

	return cmdHandled;
}


// ---------------------------------------------------------------------------
//	¥ UserChangedText						[public, virtual]
// ---------------------------------------------------------------------------
//	Text of WasteEdit has changed as a result of user action

void
CTEXT_EditorView::UserChangedText()
{
	if ( !IsDirty() ) {

		// Set the update menus flag.
		SetUpdateCommandStatus( true );
		
		// Set the dirty flag.
		SetDirty( true );
	}
}


// ---------------------------------------------------------------------------
//  ¥ GetModifiedText										[public]
// ---------------------------------------------------------------------------

Handle
CTEXT_EditorView::GetModifiedText() 
{
	Handle	outTextHandle = GetTextHandle();
	
	long numStyle = ::TENumStyles(0, ::GetHandleSize(outTextHandle), mTextEditH);

	if (numStyle > 1) {
		StScrpHandle	theScrapHandle;
		
		SelectAll();
		theScrapHandle = ::TEGetStyleScrapHandle(mTextEditH);
		
		dynamic_cast<CTEXT_EditorDoc *>(mOwnerWindow->GetOwnerDoc())->SaveStylResource(theScrapHandle);
	} 
	return outTextHandle;
}




PP_End_Namespace_PowerPlant
