// ===========================================================================
// CAboutWindow.cp					
// 
//                       Created: 2005-03-08 14:22:24
//             Last modification: 2006-11-25 19:36:16
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2003-2006
// All rights reserved.
// ===========================================================================


#include "CAboutWindow.h"
#include "RezillaConstants.h"
#include "CRezillaApp.h"
#include "CStaticTextURL.h"
#include "UResources.h"

#include <LStaticText.h>


// ---------------------------------------------------------------------------
//   CAboutWindow				[public]
// ---------------------------------------------------------------------------

CAboutWindow::CAboutWindow()
{
}


// ---------------------------------------------------------------------------
//   CAboutWindow				[public]
// ---------------------------------------------------------------------------

CAboutWindow::CAboutWindow(
	const SWindowInfo &inWindowInfo )
		: LDialogBox( inWindowInfo )
{
}


// ---------------------------------------------------------------------------
//   CAboutWindow				[public]
// ---------------------------------------------------------------------------

CAboutWindow::CAboutWindow(
	ResIDT		inWINDid,
	UInt32		inAttributes,
	LCommander	*inSuperCommander )
		: LDialogBox( inWINDid, inAttributes, inSuperCommander )
{
}


// ---------------------------------------------------------------------------
//   CAboutWindow													[public]
// ---------------------------------------------------------------------------

CAboutWindow::CAboutWindow(
			       LStream *inStream )
		: LDialogBox( inStream )
{
}


// ---------------------------------------------------------------------------
//   ~CAboutWindow													[public]
// ---------------------------------------------------------------------------

CAboutWindow::~CAboutWindow()
{
}


// ---------------------------------------------------------------------------
//   FinishCreateSelf												[protected]
// ---------------------------------------------------------------------------

void
CAboutWindow::FinishCreateSelf()
{	
	Str255				theString;
	LStaticText *		theCaption;	
	CStaticTextURL *	theUrlCaption;	
	
	// Write the version number in the caption
	theCaption = dynamic_cast<LStaticText *>(this->FindPaneByID( item_AboutVersCaption ));
	theCaption->SetDescriptor( CRezillaApp::sVersionNumber);

	// Write the URLs
	for (UInt8 i = 0; i < 6; i++) {
		theUrlCaption = dynamic_cast<CStaticTextURL *>(this->FindPaneByID( item_AboutUrlsBase + i ));
	
		if (theUrlCaption != NULL) {
			// Retrieve strings from STR# resource
			::GetIndString(theString, STRx_InternetUrls, 2*i+1);
			theUrlCaption->SetDescriptor(theString);
			
			::GetIndString(theString, STRx_InternetUrls, 2*i+2);
			theUrlCaption->SetUrlString(theString);
		} 
	}
		
	// Let window listen to its sub panes
    UReanimator::LinkListenerToControls( this, this, PPob_AboutWindow );

}


// ---------------------------------------------------------------------------------
//   FindCommandStatus
// ---------------------------------------------------------------------------------

void
CAboutWindow::FindCommandStatus(
	CommandT	inCommand,
	Boolean		&outEnabled,
	Boolean		&outUsesMark,
	UInt16		&outMark,
	Str255		outName )
{
#pragma unused(inCommand, outUsesMark, outMark, outName)

	// Disable all menu items
	outEnabled = false;
	return;
}


// ---------------------------------------------------------------------------
//   ListenToMessage				[public]
// ---------------------------------------------------------------------------

void
CAboutWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{
#pragma unused( ioParam )
	
	switch (inMessage) {

		case msg_AboutOkButton:
		case msg_Close:
		DoClose();		
		break;
		
		case msg_AboutLicenceButton:
		WindowPtr theWinPtr = UWindows::FindNamedWindow((StringPtr) "\pRezilla License");
		if (!theWinPtr) {
			StRezRefSaver saver( CRezillaApp::GetSelfRefNum() );
			LWindow* theWindow = LWindow::CreateWindow( PPob_LicenceWindow, this->GetSuperCommander() );
			ThrowIfNil_(theWindow);
			theWinPtr = theWindow->GetMacWindow();
		} 
		DoClose();		
		::SelectWindow(theWinPtr);
		break;	
		
	}
}	




