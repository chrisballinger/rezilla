// ===========================================================================
// CRezMapWindow.cp					
// 
//                       Created: 2003-04-29 07:11:00
//             Last modification: 2004-04-11 21:49:03
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003-2004
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

#include <LWindow.h>
#include <LFile.h>
#include <LStaticText.h>
#include <LIconPane.h>


#include <UExtractFromAEDesc.h>
#include <UAppleEventsMgr.h>


// #include <AppleHelp.h>

// ---------------------------------------------------------------------------
//  ¥ CRezMapWindow				[public]
// ---------------------------------------------------------------------------

CRezMapWindow::CRezMapWindow()
{
}


// ---------------------------------------------------------------------------
//  ¥ CRezMapWindow				[public]
// ---------------------------------------------------------------------------

CRezMapWindow::CRezMapWindow(
	const SWindowInfo &inWindowInfo )
		: LWindow( inWindowInfo )
{
}


// ---------------------------------------------------------------------------
//  ¥ CRezMapWindow				[public]
// ---------------------------------------------------------------------------

CRezMapWindow::CRezMapWindow(
	ResIDT		inWINDid,
	UInt32		inAttributes,
	LCommander	*inSuperCommander )
		: LWindow( inWINDid, inAttributes, inSuperCommander )
{
}


// ---------------------------------------------------------------------------
//  ¥ CRezMapWindow				[public]
// ---------------------------------------------------------------------------

CRezMapWindow::CRezMapWindow(
			       LStream *inStream )
		: LWindow( inStream )
{
}


// ---------------------------------------------------------------------------
//  ¥ ~CRezMapWindow				[public]
// ---------------------------------------------------------------------------

CRezMapWindow::~CRezMapWindow()
{
}


// ---------------------------------------------------------------------------
//  ¥ FinishCreateSelf											[protected]
// ---------------------------------------------------------------------------

void
CRezMapWindow::FinishCreateSelf()
{    	
	mOwnerDoc = dynamic_cast<CRezMapDoc*>(GetSuperCommander());
	
	mRezMapTable = dynamic_cast<CRezMapTable *>(this->FindPaneByID( item_OutlineTable ));
	ThrowIfNil_( mRezMapTable );
	
	// Make this window the supercommander of the table
	mRezMapTable->SetSuperCommander(this);

	// Fill in the bottom fields
	short	theCount;
	
	mCountTypeField = dynamic_cast<LStaticText *>(this->FindPaneByID( item_TypesNum ));
	ThrowIfNil_( mCountTypeField );
	
	mCountRezField = dynamic_cast<LStaticText *>(this->FindPaneByID( item_ResourcesNum ));
	ThrowIfNil_( mCountRezField );

	InstallWhichForkField();
	
	mOwnerDoc->GetRezMap()->CountAllTypes(theCount);
	SetCountTypeField(theCount);
	mOwnerDoc->GetRezMap()->CountAllResources(theCount);
	SetCountRezField(theCount);
		
	UReanimator::LinkListenerToControls(this, this, rRidL_RezMapWindow);
}


// ---------------------------------------------------------------------------
//  ¥ ListenToMessage												[public]
// ---------------------------------------------------------------------------

void
CRezMapWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{
#pragma unused( ioParam, inMessage )
	
}


// ---------------------------------------------------------------------------
//	¥ HandleKeyPress												  [public]
// ---------------------------------------------------------------------------
//	DialogBox handles keyboard equivalents for hitting the ApplyLeft and ApplyRight Buttons
//  and Slider movements.

Boolean
CRezMapWindow::HandleKeyPress(
	const EventRecord&	inKeyEvent)
{
	Boolean		keyHandled	= true;
	LControl*	keyButton	= nil;
	UInt8		theChar		= (UInt8) (inKeyEvent.message & charCodeMask);
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
//  ¥ GetCountTypeField											[public]
// ---------------------------------------------------------------------------

long
CRezMapWindow::GetCountTypeField() 
{
	long result;
	Str255 theString;
	
	mCountTypeField->GetDescriptor(theString);
	::StringToNum(theString, &result);
	return result;
}


// ---------------------------------------------------------------------------
//  ¥ GetCountRezField											[public]
// ---------------------------------------------------------------------------

long
CRezMapWindow::GetCountRezField() 
{
	long result;
	Str255 theString;
	
	mCountRezField->GetDescriptor(theString);
	::StringToNum(theString, &result);
	return result;
}


// ---------------------------------------------------------------------------
//  ¥ SetCountTypeField											[public]
// ---------------------------------------------------------------------------

void
CRezMapWindow::SetCountTypeField(long inCount) 
{
	Str255 theString;
	::NumToString(inCount, theString);
	mCountTypeField->SetDescriptor(theString);
}


// ---------------------------------------------------------------------------
//  ¥ SetCountRezField											[public]
// ---------------------------------------------------------------------------

void
CRezMapWindow::SetCountRezField(long inCount) 
{
	Str255 theString;
	::NumToString(inCount, theString);
	mCountRezField->SetDescriptor(theString);
}


// ---------------------------------------------------------------------------
//  ¥ RecalcCountFields												[public]
// ---------------------------------------------------------------------------
// Update the count fields at the bottom of the rezmap window

void
CRezMapWindow::RecalcCountFields() 
{
	short theCount;
	
	mOwnerDoc->GetRezMap()->CountAllTypes(theCount);
	SetCountTypeField(theCount);
	
	mOwnerDoc->GetRezMap()->CountAllResources(theCount);
	SetCountRezField(theCount);
}


// ---------------------------------------------------------------------------
//  ¥ InstallWhichForkField											[public]
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


// ---------------------------------------------------------------------------
//  ¥ InstallReadOnlyIcon											[public]
// ---------------------------------------------------------------------------

void
CRezMapWindow::InstallReadOnlyIcon() 
{
	LIconPane * theIcon = dynamic_cast<LIconPane *>(this->FindPaneByID( item_MapReadOnlyIcon ));
	ThrowIfNil_( theIcon );
	if (mOwnerDoc->GetReadOnlyDoc()) {
		theIcon->SetIconID(ics8_Locked);
	} else {
		theIcon->SetIconID(ics8_Unlocked);
	}
}



