// ===========================================================================
// CTmplEditorWindow.cp					
// 
//                       Created: 2004-06-12 15:08:01
//             Last modification: 2004-06-12 16:07:41
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003-2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#include "CTmplEditorWindow.h"
#include "CTmplEditorDoc.h"
#include "CRezObj.h"
#include "CRezillaApp.h"
#include "CRezillaPrefs.h"
#include "RezillaConstants.h"
#include "UMessageDialogs.h"

#include <LScrollBar.h>
#include <LStaticText.h>
#include <LIconPane.h>
#include <LTextGroupBox.h>
#include <LUndoer.h>
#include <UExtractFromAEDesc.h>
#include <UAppleEventsMgr.h>
#include <UCursor.h>

#include <AppleHelp.h>


// ---------------------------------------------------------------------------
//		¥ CTmplEditorWindow				[public]
// ---------------------------------------------------------------------------

CTmplEditorWindow::CTmplEditorWindow()
{
}


// ---------------------------------------------------------------------------
//		¥ CTmplEditorWindow				[public]
// ---------------------------------------------------------------------------

CTmplEditorWindow::CTmplEditorWindow(
	const SWindowInfo &inWindowInfo )
		: CEditorWindow( inWindowInfo )
{
}


// ---------------------------------------------------------------------------
//		¥ CTmplEditorWindow				[public]
// ---------------------------------------------------------------------------

CTmplEditorWindow::CTmplEditorWindow(
	ResIDT		inWINDid,
	UInt32		inAttributes,
	LCommander	*inSuperCommander )
		: CEditorWindow( inWINDid, inAttributes, inSuperCommander )
{
}


// ---------------------------------------------------------------------------
//		¥ CTmplEditorWindow				[public]
// ---------------------------------------------------------------------------

CTmplEditorWindow::CTmplEditorWindow(
			       LStream *inStream )
		: CEditorWindow( inStream )
{
}


// ---------------------------------------------------------------------------
//		¥ ~CTmplEditorWindow				[public]
// ---------------------------------------------------------------------------

CTmplEditorWindow::~CTmplEditorWindow()
{
}


// ---------------------------------------------------------------------------
//		¥ FinishCreateSelf				[protected]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::FinishCreateSelf()
{	
// 	OSStatus		error = noErr ;

	mCurrFirstID = 1;
	mCurrentItemID = 0;
	mOwnerDoc = dynamic_cast<CTmplEditorDoc*>(GetSuperCommander());
	
	// Waste edit subviews
	mContentsView = dynamic_cast<LView *>(this->FindPaneByID(item_TmplEditContents));
	ThrowIfNil_( mContentsView );
		
	InstallReadOnlyIcon();
		
	// Install the name of the resource if it has one
	LStaticText * theStaticText = dynamic_cast<LStaticText *>(this->FindPaneByID( item_NameStaticText ));
	ThrowIfNil_( theStaticText );
	Str255 * strPtr = dynamic_cast<CTmplEditorDoc *>(GetSuperCommander())->GetRezObj()->GetName();
	theStaticText->SetDescriptor(*strPtr);
	
// 	// Let the window listen to the text edit fields
// 	mLineField->AddListener(this);	
// 	mOffsetField->AddListener(this);	

	// Make the window a listener to the prefs object
	CRezillaApp::sPrefs->AddListener(this);
	
// 	// Attach an LUndoer to each of the subpanes
// 	mHexDataWE->AddAttachment( new LUndoer );
// 	mTxtDataWE->AddAttachment( new LUndoer );

}
	

// ---------------------------------------------------------------------------
//		¥ ListenToMessage				[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{	
	switch (inMessage) {
					
		default:
		dynamic_cast<CTmplEditorDoc *>(GetSuperCommander())->ListenToMessage(inMessage, ioParam);
		break;
				
	}
}


// ---------------------------------------------------------------------------
//	¥ FindCommandStatus
// ---------------------------------------------------------------------------
//	Pass back whether a Command is enabled and/or marked (in a Menu)

void
CTmplEditorWindow::FindCommandStatus(
	CommandT	inCommand,
	Boolean		&outEnabled,
	Boolean		&outUsesMark,
	UInt16		&outMark,
	Str255		outName)
{
	switch (inCommand) {

		case cmd_GuiEditRez:
		case cmd_HexEditRez:
		case cmd_RemoveRez:
		case cmd_DuplicateRez:
			outEnabled = false;
			break;		
		
		default:
			LCommander::FindCommandStatus(inCommand, outEnabled,
									outUsesMark, outMark, outName);
			break;
	}
}


// ---------------------------------------------------------------------------
//	¥ ObeyCommand							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CTmplEditorWindow::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;
	
	switch (inCommand) {

		case cmd_Copy: 
		case cmd_Cut: 
		case cmd_Clear:
		case cmd_Paste:
		break;

		case cmd_ActionCut:
		case cmd_ActionPaste:
		case cmd_ActionClear:
		case cmd_ActionTyping:
			break;

		default:
			cmdHandled = LCommander::ObeyCommand(inCommand, ioParam);
			break;
	}

	return cmdHandled;
}


// ---------------------------------------------------------------------------
//  ¥ InstallReadOnlyIcon											[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::InstallReadOnlyIcon() 
{
	LIconPane * theIcon = dynamic_cast<LIconPane *>(this->FindPaneByID( item_ReadOnlyIcon ));
	ThrowIfNil_( theIcon );
	if (mOwnerDoc->IsReadOnly()) {
		theIcon->SetIconID(ics8_Locked);
	} else {
		theIcon->SetIconID(ics8_Unlocked);
	}
}


// ---------------------------------------------------------------------------
//	¥ IsDirty														[public]
// ---------------------------------------------------------------------------

Boolean
CTmplEditorWindow::IsDirty()
{
	return false;
}


// ---------------------------------------------------------------------------
//	¥ ParseTemplate														[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::ParseTemplate(Handle inHandle)
{
}


// ---------------------------------------------------------------------------
//	¥ ReadValues														[public]
// ---------------------------------------------------------------------------

Handle
CTmplEditorWindow::ReadValues()
{
}
