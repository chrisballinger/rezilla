// ===========================================================================
// CRezMapWindow.cp					
// 
//                       Created: 2003-04-29 07:11:00
//             Last modification: 2003-05-01 18:53:37
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#include "CRezMapWindow.h"
#include "CRezillaApp.h"
#include "CRezMapTable.h"
#include "RezillaConstants.h"
#include "CRezMapDoc.h"
#include "CRezMap.h"

// #include "UMessageDialogs.h"

#include <LWindow.h>
#include <LFile.h>
#include <LStaticText.h>


#include <UExtractFromAEDesc.h>
#include <UAppleEventsMgr.h>


// #include <AppleHelp.h>

// ---------------------------------------------------------------------------
//  ¬€ CRezMapWindow				[public]
// ---------------------------------------------------------------------------

CRezMapWindow::CRezMapWindow()
{
}


// ---------------------------------------------------------------------------
//  ¬€ CRezMapWindow				[public]
// ---------------------------------------------------------------------------

CRezMapWindow::CRezMapWindow(
	const SWindowInfo &inWindowInfo )
		: LWindow( inWindowInfo )
{
}


// ---------------------------------------------------------------------------
//  ¬€ CRezMapWindow				[public]
// ---------------------------------------------------------------------------

CRezMapWindow::CRezMapWindow(
	ResIDT		inWINDid,
	UInt32		inAttributes,
	LCommander	*inSuperCommander )
		: LWindow( inWINDid, inAttributes, inSuperCommander )
{
}


// ---------------------------------------------------------------------------
//  ¬€ CRezMapWindow				[public]
// ---------------------------------------------------------------------------

CRezMapWindow::CRezMapWindow(
			       LStream *inStream )
		: LWindow( inStream )
{
}


// ---------------------------------------------------------------------------
//  ¬€ ~CRezMapWindow				[public]
// ---------------------------------------------------------------------------

CRezMapWindow::~CRezMapWindow()
{
}


// ---------------------------------------------------------------------------
//  ¬€ FinishCreateSelf											[protected]
// ---------------------------------------------------------------------------

void
CRezMapWindow::FinishCreateSelf()
{    	
	mOwnerDoc = dynamic_cast<CRezMapDoc*>(GetSuperCommander());
	
	mRezMapTable = dynamic_cast<CRezMapTable *>(this->FindPaneByID( item_OutlineTable ));
	ThrowIfNil_( mRezMapTable );
	
	// Fill in the bottom fields
	LStaticText *	theStaticText;
	short			theCount;
	
	mCountTypeField = dynamic_cast<LStaticText *>(this->FindPaneByID( item_TypesNum ));
	ThrowIfNil_( mCountTypeField );
	
	mCountRezField = dynamic_cast<LStaticText *>(this->FindPaneByID( item_ResourcesNum ));
	ThrowIfNil_( mCountRezField );

	InstallWhichForkField();
	
	mOwnerDoc->GetRezMap()->CountAllTypes(theCount);
	InstallCountTypeValue(theCount);
	mOwnerDoc->GetRezMap()->CountAllResources(theCount);
	InstallCountRezValue(theCount);
		
	UReanimator::LinkListenerToControls( this, this, rRidL_RezMapWindow );
}


// ---------------------------------------------------------------------------
//  ¬€ ListenToMessage											[public]
// ---------------------------------------------------------------------------

void
CRezMapWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{
	SInt32 theValue;
	
// 	switch (inMessage) {
// 		
// 		case msg_Slider: {
// 			break;
// 		}
// 		
// 	}
}


// // ---------------------------------------------------------------------------------
// //  ¬€ FindCommandStatus
// // ---------------------------------------------------------------------------------
// 
// void
// CRezMapWindow::FindCommandStatus(
// 	CommandT	inCommand,
// 	Boolean		&outEnabled,
// 	Boolean		&outUsesMark,
// 	UInt16		&outMark,
// 	Str255		outName )
// {
// 
// 	switch ( inCommand ) {
// 									
// 		case cmd_EditRez:
// 		case cmd_GetRezInfo:
// 		case cmd_RemoveRez:
// 		case cmd_DuplicateRez:
// 		outEnabled = true;
// 			break;		
// 		
// 	  default:
// 		{
// 			// Call inherited.
// 			LDocument::FindCommandStatus( inCommand,
// 				outEnabled, outUsesMark, outMark, outName );
// 		}
// 		break;
// 
// 	}
// }


// ---------------------------------------------------------------------------
//	¬€ HandleKeyPress												  [public]
// ---------------------------------------------------------------------------
//	DialogBox handles keyboard equivalents for hitting the ApplyLeft and ApplyRight Buttons
//  and Slider movements.

Boolean
CRezMapWindow::HandleKeyPress(
	const EventRecord&	inKeyEvent)
{
	Boolean		keyHandled	= true;
// 	LControl*	keyButton	= nil;
// 	UInt8		theChar		= (UInt8) (inKeyEvent.message & charCodeMask);
// 	
// 	if (inKeyEvent.modifiers & cmdKey) {
// 		if ( theChar == char_LeftArrow) {
// 			keyButton = dynamic_cast<LControl*>(mToOldArrow);		
// 		} else if ( theChar == char_RightArrow ) {
// 			keyButton = dynamic_cast<LControl*>(mToNewArrow);		
// 		} 
// 	} else {
// 		SInt32 theValue;
// 		theValue = mSlider->GetValue();
// 		
// 		if ( (theChar == char_UpArrow) || (theChar == char_PageUp) ) {
// 			--theValue;
// 			if (theValue == 0) {
// 				return keyHandled;
// 			} 
// 		} else if ( (theChar == char_DownArrow) || (theChar == char_PageDown) ) {
// 			++theValue;
// 			if (theValue > mOwnerDoc->GetDiffsCount()) {
// 				return keyHandled;
// 			} 
// 		}  else if ( theChar == char_Home ) {
// 			theValue = 1;
// 		}
// 		 else if ( theChar == char_End ) {
// 			theValue = mOwnerDoc->GetDiffsCount();
// 		 }
// 		 
// 		mSlider->SetValue(theValue);
// 		mOwnerDoc->AdjustInfoLine(theValue);
// 		DisplayCountField(theValue);
// 		mOwnerDoc->AdjustBothSelections(theValue);
// 	}
// 	
// 	if (keyButton != nil) {
// 		keyButton->SimulateHotSpotClick(kControlButtonPart);
// 	} else {
// 		keyHandled = LWindow::HandleKeyPress(inKeyEvent);
// 	}
	
	return keyHandled;
}


// ---------------------------------------------------------------------------
//  ¬€ InstallCountTypeValue											[public]
// ---------------------------------------------------------------------------

void
CRezMapWindow::InstallCountTypeValue(short inCount) 
{
	Str255 theString;
	::NumToString(inCount, theString);
	mCountTypeField->SetDescriptor(theString);
}


// ---------------------------------------------------------------------------
//  ¬€ InstallCountRezValue											[public]
// ---------------------------------------------------------------------------

void
CRezMapWindow::InstallCountRezValue(short inCount) 
{
	Str255 theString;
	::NumToString(inCount, theString);
	mCountRezField->SetDescriptor(theString);
}


// ---------------------------------------------------------------------------
//  ¬€ UpdateCountFields												[public]
// ---------------------------------------------------------------------------
// Update the count fields at the bottom of the rezmap window

void
CRezMapWindow::UpdateCountFields() 
{
	short theCount;
	
	mOwnerDoc->GetRezMap()->CountAllTypes(theCount);
	InstallCountTypeValue(theCount);
	
	mOwnerDoc->GetRezMap()->CountAllResources(theCount);
	InstallCountRezValue(theCount);
}


// ---------------------------------------------------------------------------
//  ¬€ InstallWhichForkField											[public]
// ---------------------------------------------------------------------------

void
CRezMapWindow::InstallWhichForkField() 
{
	LStaticText * theField = dynamic_cast<LStaticText *>(this->FindPaneByID( item_WhichFork ));
	ThrowIfNil_( theField );
	if (mOwnerDoc->GetFork() == fork_rezfork) {
		theField->SetDescriptor("\pRF");
	} else {
		theField->SetDescriptor("\pDF");
	}
}




