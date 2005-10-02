// ===========================================================================
// CPluginEditorWindow.cp
// 
//                       Created: 2005-10-02 08:41:52
//             Last modification: 2005-10-02 08:42:01
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#include "CPluginEditorWindow.h"
#include "CPluginEditorDoc.h"
#include "CRezObj.h"
#include "CWindowMenu.h"
#include "RezillaConstants.h"

#include <LIconPane.h>
#include <LStaticText.h>

// Statics
// CPluginMenu *		CPluginEditorWindow::sPluginMenu = nil;
LMenu *		CPluginEditorWindow::sPluginMenu = nil;


// ---------------------------------------------------------------------------
//  CPluginEditorWindow				[public]
// ---------------------------------------------------------------------------

CPluginEditorWindow::CPluginEditorWindow()
	: CEditorWindow()
{
}


// ---------------------------------------------------------------------------
//  CPluginEditorWindow				[public]
// ---------------------------------------------------------------------------

CPluginEditorWindow::CPluginEditorWindow(
	const SWindowInfo &inWindowInfo )
		: CEditorWindow( inWindowInfo )
{
}


// ---------------------------------------------------------------------------
//  CPluginEditorWindow				[public]
// ---------------------------------------------------------------------------

CPluginEditorWindow::CPluginEditorWindow(
	ResIDT		inWINDid,
	UInt32		inAttributes,
	LCommander	*inSuperCommander )
		: CEditorWindow( inWINDid, inAttributes, inSuperCommander )
{
}


// ---------------------------------------------------------------------------
//  CPluginEditorWindow				[public]
// ---------------------------------------------------------------------------

CPluginEditorWindow::CPluginEditorWindow(
			       LStream *inStream )
		: CEditorWindow( inStream )
{
}


// ---------------------------------------------------------------------------
//  ~CPluginEditorWindow				[public]
// ---------------------------------------------------------------------------

CPluginEditorWindow::~CPluginEditorWindow()
{
	RemovePluginMenu();
}


// ---------------------------------------------------------------------------
//  FinalizeEditor											[public]
// ---------------------------------------------------------------------------

void
CPluginEditorWindow::FinalizeEditor(CPluginEditorDoc* inEditorDoc)
{
	CEditorWindow::FinalizeEditor(inEditorDoc);
	InstallPluginNameField();
}
	

// // ---------------------------------------------------------------------------
// //  FinishCreateSelf											[protected]
// // ---------------------------------------------------------------------------
// 
// void
// CPluginEditorWindow::FinishCreateSelf()
// {    
// 	mAete = nil;
// 	mIgnoreSliderMessage = false;
// 	mCurrentPanel = mpv_AeteEvent;
// 	
// 	mSuitesPopup = dynamic_cast<LPopupButton *>(this->FindPaneByID( item_AeteSuitePopup ));
// 	ThrowIfNil_( mSuitesPopup );
// 	
// 	LPageController * theController = dynamic_cast<LPageController *>(this->FindPaneByID( item_AetePanelController ));
// 	ThrowIfNil_( theController );
// 			
// 	LMultiPanelView * theMultiPanel = dynamic_cast<LMultiPanelView *>(this->FindPaneByID( item_AeteMultiPanelView ));
// 	ThrowIfNil_( theMultiPanel );
// 	
// 	// Create the panels before we call them
// 	theMultiPanel->CreateAllPanels();
// 	
// 	mEventPane = theMultiPanel->GetPanel(mpv_AeteEvent);
// 	ThrowIfNil_(mEventPane);
// 	
// 	mClassPane = theMultiPanel->GetPanel(mpv_AeteClass);
// 	ThrowIfNil_(mClassPane);
// 	
// 	mCompOpPane = theMultiPanel->GetPanel(mpv_AeteCompOp);
// 	ThrowIfNil_(mCompOpPane);
// 	
// 	mEnumerationPane = theMultiPanel->GetPanel(mpv_AeteEnum);
// 	ThrowIfNil_(mEnumerationPane);
// 		
// 	// Edit menu strings. Load these once only.
// 	if ( sAddEventStr[0] == 0 )
// 	{
// 		::GetIndString(sAddEventStr, STRx_AeteAdd, kind_AeteEvent);
// 		::GetIndString(sAddClassStr, STRx_AeteAdd, kind_AeteClass);
// 		::GetIndString(sAddCompOpStr, STRx_AeteAdd, kind_AeteCompOp);
// 		::GetIndString(sAddEnumerationStr, STRx_AeteAdd, kind_AeteEnum);
// 		::GetIndString(sRemoveEventStr, STRx_AeteRemove, kind_AeteEvent);
// 		::GetIndString(sRemoveClassStr, STRx_AeteRemove, kind_AeteClass);
// 		::GetIndString(sRemoveCompOpStr, STRx_AeteRemove, kind_AeteCompOp);
// 		::GetIndString(sRemoveEnumerationStr, STRx_AeteRemove, kind_AeteEnum);
// 	}
// 
// 	// Link to the broadcasters. Note that it is very important that the 
// 	// MultiPanelView be declared _before_ the window so that we switch 
// 	// panels before our ListenToMessage is called.
// 	theController->AddListener(theMultiPanel);
// 	theController->AddListener(this);
// 	UReanimator::LinkListenerToBroadcasters( this, this, PPob_AeteEditorWindow );
// 	UReanimator::LinkListenerToBroadcasters( this, mEventPane, PPob_AeteEventPane );
// 	UReanimator::LinkListenerToBroadcasters( this, mClassPane, PPob_AeteClassPane );
// 	UReanimator::LinkListenerToBroadcasters( this, mCompOpPane, PPob_AeteCompOpPane );
// 	UReanimator::LinkListenerToBroadcasters( this, mEnumerationPane, PPob_AeteEnumPane );
// }


// ---------------------------------------------------------------------------
//  ListenToMessage									[public]
// ---------------------------------------------------------------------------

void
CPluginEditorWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{
	
	switch (inMessage) {
		
		case msg_Close:
		Hide();
		break;
				
		default:
		dynamic_cast<CPluginEditorDoc *>(GetSuperCommander())->ListenToMessage(inMessage, ioParam);
		break;
				
	}
}


// ---------------------------------------------------------------------------
//  FindCommandStatus
// ---------------------------------------------------------------------------
//	Pass back whether a Command is enabled and/or marked (in a Menu)

void
CPluginEditorWindow::FindCommandStatus(
	CommandT	inCommand,
	Boolean		&outEnabled,
	Boolean		&outUsesMark,
	UInt16		&outMark,
	Str255		outName)
{
	switch (inCommand) {
		
		case cmd_EditRez:
		case cmd_EditRezAsType:
		case cmd_TmplEditRez:
		case cmd_HexEditRez:
		case cmd_RemoveRez:
		case cmd_DuplicateRez:
		outEnabled = false;
		break;		
		
		default:
		if (mOwnerDoc) {
			mOwnerDoc->FindCommandStatus(inCommand, outEnabled,
												outUsesMark, outMark, outName);
		} else {
			LCommander::FindCommandStatus(inCommand, outEnabled,
												outUsesMark, outMark, outName);
		}
		break;
	}
}


// ---------------------------------------------------------------------------
//  ObeyCommand							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CPluginEditorWindow::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;

	switch (inCommand) {

		case cmd_Copy: 
		case cmd_Cut: {
			break;
		}

		case cmd_Clear: {
			break;
		}

		case cmd_Paste: {
			break;
		}

		case cmd_ActionCut:
		case cmd_ActionPaste:
		case cmd_ActionClear:
		case cmd_ActionTyping: {
			break;
		}

		default:
// 		cmdHandled = LCommander::ObeyCommand(inCommand, ioParam);
		cmdHandled = mOwnerDoc->ObeyCommand(inCommand, ioParam);
		break;
	}

	return cmdHandled;
}


// ---------------------------------------------------------------------------
// 	PutOnDuty
// ---------------------------------------------------------------------------

void
CPluginEditorWindow::PutOnDuty(LCommander *inNewTarget)
{
	LWindow::PutOnDuty(inNewTarget);

	// Put up our menus when on duty
	if ( !sPluginMenu )
	{
		sPluginMenu = new LMenu( MENU_PluginEditor );
		ThrowIfNil_( sPluginMenu );
	}
	
	// Update the menu bar
	LMenuBar *	theBar = LMenuBar::GetCurrentMenuBar();
	theBar->InstallMenu( sPluginMenu, MENU_OpenedWindows );	
}


// ---------------------------------------------------------------------------
// 	TakeOffDuty
// ---------------------------------------------------------------------------

void
CPluginEditorWindow::TakeOffDuty()
{		
	LWindow::TakeOffDuty();
	RemovePluginMenu();
}


// ---------------------------------------------------------------------------
// 	RemovePluginMenu
// ---------------------------------------------------------------------------

void
CPluginEditorWindow::RemovePluginMenu()
{
	LMenuBar *	theBar = LMenuBar::GetCurrentMenuBar();
	if ( sPluginMenu )
		theBar->RemoveMenu( sPluginMenu );
}


// ---------------------------------------------------------------------------
//  RevertContents												  [public]
// ---------------------------------------------------------------------------
// Override in subclasses to redraw the contents view with the last saved 
// data.

void
CPluginEditorWindow::RevertContents()
{
	SetDirty(false);
}


// ---------------------------------------------------------------------------
//  ¥ InstallPluginNameField											[public]
// ---------------------------------------------------------------------------

void
CPluginEditorWindow::InstallPluginNameField() 
{
// 	// Install the name of the plugin used to edit this resource
// 	LStaticText * theStaticText = dynamic_cast<LStaticText *>(this->FindPaneByID( item_PluginNameField ));
// 	if (theStaticText != nil) {
// 		CPluginEditorDoc * theDoc = dynamic_cast<CPluginEditorDoc *>(GetSuperCommander());
// 		if (theDoc != nil) {
// 			Str255 * strPtr = theDoc->GetRezObj()->GetName();
// 			theStaticText->SetDescriptor(*strPtr);	
// 		} 
// 	} 
}


