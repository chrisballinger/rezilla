// ===========================================================================
// CTEXT_EditorView.cp
// 
//                       Created: 2004-06-19 13:23:32
//             Last modification: 2004-11-06 08:22:28
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

#include "CTEXT_EditorDoc.h"
#include "CTEXT_EditorView.h"
#include "CTEXT_EditorWindow.h"
#include "CRezObj.h"
#include "CRezillaPrefs.h"


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
// Use the Preference interface settings when creating a new TEXT resource.

CTEXT_EditorView::CTEXT_EditorView(
	LStream*	inStream)

	: LTextEditView(inStream)
{
	TextTraitsRecord theTraits = CRezillaPrefs::GetStyleElement( CRezillaPrefs::prefsType_Curr );
	TextStyle	theStyle;
	SInt16		justification = teFlushDefault;

	theStyle.tsFont			= theTraits.fontNumber;
	theStyle.tsFace			= static_cast<UInt8>(theTraits.style);
	theStyle.tsSize			= theTraits.size;
	theStyle.tsColor		= theTraits.color;
	justification			= theTraits.justification;

	::TextFont(theStyle.tsFont);		// Set Port Font and Size so TE
	::TextSize(theStyle.tsSize);		// uses the correct settings for
										// its internal tables.

	::TESetStyle( doAll, &theStyle, false, mTextEditH );
	::TESetAlignment( justification, mTextEditH );
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
	if ( ! mOwnerWindow->IsDirty() ) {

		// Set the update menus flag.
		SetUpdateCommandStatus( true );
		
		// Set the dirty flag.
		mOwnerWindow->SetDirty( true );
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
