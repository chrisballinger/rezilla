// ===========================================================================
// CUtxt_EditorView.cp
// 
//                       Created: 2004-12-08 18:21:21
//             Last modification: 2004-12-09 23:05:04
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

#include "CUtxt_EditorView.h"
#include "CUtxt_EditorDoc.h"
#include "CUtxt_EditorWindow.h"
#include "CRezObj.h"
#include "CRezillaPrefs.h"
#include "RezillaConstants.h"

#include <LMenuBar.h>


PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//	¥ CUtxt_EditorView							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CUtxt_EditorView::CUtxt_EditorView()
		: LMLTEPane()
{
}


// ---------------------------------------------------------------------------
//	¥ CUtxt_EditorView							Stream Constructor		  [public]
// ---------------------------------------------------------------------------
// Use the Preference interface settings when creating a new TEXT resource.

CUtxt_EditorView::CUtxt_EditorView(
	LStream*	inStream)

	: LMLTEPane(inStream)
{
	TextTraitsRecord theTraits = CRezillaPrefs::GetStyleElement( CRezillaPrefs::prefsType_Curr );
	SInt16		justification = teFlushDefault;
// 	TextStyle	theStyle;

// 	theStyle.tsFont			= theTraits.fontNumber;
// 	theStyle.tsFace			= static_cast<UInt8>(theTraits.style);
// 	theStyle.tsSize			= theTraits.size;
// 	theStyle.tsColor		= theTraits.color;
// 	justification			= theTraits.justification;
// 
// 	::TextFont(theStyle.tsFont);		// Set Port Font and Size so TE
// 	::TextSize(theStyle.tsSize);		// uses the correct settings for
// 										// its internal tables.
// 
// 	::TESetStyle( doAll, &theStyle, false, mTextEditH );
// 	::TESetAlignment( justification, mTextEditH );
}


// ---------------------------------------------------------------------------
//	¥ ~CUtxt_EditorView						Destructor				  [public]
// ---------------------------------------------------------------------------

CUtxt_EditorView::~CUtxt_EditorView()
{
}



#pragma mark -


// ---------------------------------------------------------------------------
//	¥ HandleKeyPress										[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CUtxt_EditorView::HandleKeyPress(
	const EventRecord	&inKeyEvent)
{
	Boolean		keyHandled	 = LMLTEPane::HandleKeyPress(inKeyEvent);
	
	mOwnerWindow->SetLengthField();
	return keyHandled;
}


// ---------------------------------------------------------------------------
//	¥ ObeyCommand							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CUtxt_EditorView::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;

	switch (inCommand) {

		case cmd_Cut: 
		case cmd_Paste: 
		case cmd_Clear: 
		LMLTEPane::ObeyCommand(inCommand, ioParam);
		mOwnerWindow->SetLengthField();
		break;

		default:
			cmdHandled = LMLTEPane::ObeyCommand(inCommand, ioParam);
			break;
	}

	return cmdHandled;
}


// ---------------------------------------------------------------------------
//	¥ ActivateSelf
// ---------------------------------------------------------------------------

void
CUtxt_EditorView::ActivateSelf()
{
	if (LMLTEPane::sTXNFontMenuObject != NULL) {
		OSStatus 	status;
		MenuHandle	macMenuH;
		
		status = ::TXNPrepareFontMenu(mTXNObject, sTXNFontMenuObject );
		status = ::TXNGetFontMenuHandle(sTXNFontMenuObject, &macMenuH);
	
		::MacInsertMenu(macMenuH, rMENU_Window);
	} 
}


// ---------------------------------------------------------------------------
//	¥ DeactivateSelf
// ---------------------------------------------------------------------------

//	Return the Menu object for the specified MENU resource ID. Returns nil
//	if there is no such Menu object
// LMenu * LMenuBar::FetchMenu(ResIDT	inMENUid) const

void
CUtxt_EditorView::DeactivateSelf()
{
	::MacDeleteMenu(rMENU_FontsUnicode);
	// Force redraw of MenuBar
	::InvalMenuBar();
}


// // ---------------------------------------------------------------------------
// //	¥ UserChangedText						[public, virtual]
// // ---------------------------------------------------------------------------
// //	Text of WasteEdit has changed as a result of user action
// 
// void
// CUtxt_EditorView::UserChangedText()
// {
// 	if ( ! mOwnerWindow->IsDirty() ) {
// 
// 		// Set the update menus flag.
// 		SetUpdateCommandStatus( true );
// 		
// 		// Set the dirty flag.
// 		mOwnerWindow->SetDirty( true );
// 	}
// }


// ---------------------------------------------------------------------------
//  ¥ GetModifiedText										[public]
// ---------------------------------------------------------------------------
// kTXNTextData or kTXNUnicodeTextData

Handle
CUtxt_EditorView::GetModifiedText() 
{
	Handle		dataH  = nil;
	OSStatus	status = ::TXNGetDataEncoded( mTXNObject, kTXNStartOffset, kTXNEndOffset,
											 &dataH, kTXNUnicodeTextData );
	return dataH;
}



PP_End_Namespace_PowerPlant
