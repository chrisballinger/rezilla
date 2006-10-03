// ===========================================================================
// CRezMapWindow.cp					
// 
//                       Created: 2003-04-29 07:11:00
//             Last modification: 2006-10-02 07:57:43
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2003-2006
// All rights reserved.
// ===========================================================================


#include "CRezMapWindow.h"
#include "CRezillaApp.h"
#include "CRezMapTable.h"
#include "RezillaConstants.h"
#include "CRezMapDoc.h"
#include "CRezMap.h"
#include "URezMapImportExport.h"
#include "UMessageDialogs.h"

#include <LWindow.h>
#include <LFile.h>
#include <LStaticText.h>
#include <LIconPane.h>


#include <UExtractFromAEDesc.h>
#include <UAppleEventsMgr.h>
#include <UProcessMgr.h>


// ---------------------------------------------------------------------------
//   CRezMapWindow				[public]
// ---------------------------------------------------------------------------

CRezMapWindow::CRezMapWindow()
{
}


// ---------------------------------------------------------------------------
//   CRezMapWindow				[public]
// ---------------------------------------------------------------------------

CRezMapWindow::CRezMapWindow(
	const SWindowInfo &inWindowInfo )
		: LWindow( inWindowInfo )
{
}


// ---------------------------------------------------------------------------
//   CRezMapWindow				[public]
// ---------------------------------------------------------------------------

CRezMapWindow::CRezMapWindow(
	ResIDT		inWINDid,
	UInt32		inAttributes,
	LCommander	*inSuperCommander )
		: LWindow( inWINDid, inAttributes, inSuperCommander )
{
}


// ---------------------------------------------------------------------------
//   CRezMapWindow				[public]
// ---------------------------------------------------------------------------

CRezMapWindow::CRezMapWindow(
			       LStream *inStream )
		: LWindow( inStream )
{
}


// ---------------------------------------------------------------------------
//     ~CRezMapWindow				[public]
// ---------------------------------------------------------------------------

CRezMapWindow::~CRezMapWindow()
{
}


// ---------------------------------------------------------------------------
//   FinishCreateSelf											[protected]
// ---------------------------------------------------------------------------

void
CRezMapWindow::FinishCreateSelf()
{    	
	SetModelKind(rzom_cRezMapWindow);

	// We need to have mOwnerDoc now because it is called below
	mOwnerDoc = dynamic_cast<CRezMapDoc*>(GetSuperCommander());
	
	mRezMapTable = dynamic_cast<CRezMapTable *>(this->FindPaneByID( item_OutlineTable ));
	ThrowIfNil_( mRezMapTable );
	
	// Make this window the supercommander of the table
	mRezMapTable->SetSuperCommander(this);
	mRezMapTable->SetOwnerWindow(this);

	// Fill in the bottom fields
	short	theCount;
	
	mTypeCountField = dynamic_cast<LStaticText *>(this->FindPaneByID( item_TypesNum ));
	ThrowIfNil_( mTypeCountField );
	
	mRezCountField = dynamic_cast<LStaticText *>(this->FindPaneByID( item_ResourcesNum ));
	ThrowIfNil_( mRezCountField );

	InstallWhichForkField();
	
	mOwnerDoc->GetRezMap()->CountAllTypes(theCount);
	SetTypeCountField(theCount);
	mOwnerDoc->GetRezMap()->CountAllResources(theCount);
	SetRezCountField(theCount);
		
	UReanimator::LinkListenerToControls(this, this, PPob_RezMapWindow);
}


// ---------------------------------------------------------------------------
//   ListenToMessage												[public]
// ---------------------------------------------------------------------------

void
CRezMapWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{
#pragma unused( ioParam, inMessage )
	
}


// ---------------------------------------------------------------------------
//   GetTypeCountField											[public]
// ---------------------------------------------------------------------------

long
CRezMapWindow::GetTypeCountField() const
{
	long result;
	Str255 theString;
	
	mTypeCountField->GetDescriptor(theString);
	::StringToNum(theString, &result);
	return result;
}


// ---------------------------------------------------------------------------
//   GetRezCountField											[public]
// ---------------------------------------------------------------------------

long
CRezMapWindow::GetRezCountField() const
{
	long result;
	Str255 theString;
	
	mRezCountField->GetDescriptor(theString);
	::StringToNum(theString, &result);
	return result;
}


// ---------------------------------------------------------------------------
//   SetTypeCountField											[public]
// ---------------------------------------------------------------------------

void
CRezMapWindow::SetTypeCountField(long inCount) 
{
	Str255 theString;
	::NumToString(inCount, theString);
	mTypeCountField->SetDescriptor(theString);
}


// ---------------------------------------------------------------------------
//   SetRezCountField											[public]
// ---------------------------------------------------------------------------

void
CRezMapWindow::SetRezCountField(long inCount) 
{
	Str255 theString;
	::NumToString(inCount, theString);
	mRezCountField->SetDescriptor(theString);
}


// ---------------------------------------------------------------------------
//   RecalcCountFields												[public]
// ---------------------------------------------------------------------------
// Update the count fields at the bottom of the rezmap window

void
CRezMapWindow::RecalcCountFields() 
{
	short theCount;
	
	mOwnerDoc->GetRezMap()->CountAllTypes(theCount);
	SetTypeCountField(theCount);
	
	mOwnerDoc->GetRezMap()->CountAllResources(theCount);
	SetRezCountField(theCount);
}


// ---------------------------------------------------------------------------
//   InstallWhichForkField											[public]
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
//   InstallReadOnlyIcon											[public]
// ---------------------------------------------------------------------------

void
CRezMapWindow::InstallReadOnlyIcon() 
{
	LIconPane * theIcon = dynamic_cast<LIconPane *>(this->FindPaneByID( item_ReadOnlyIcon ));
	ThrowIfNil_( theIcon );
	if (mOwnerDoc->IsReadOnly()) {
		theIcon->SetIconID(ics8_Locked);
	} else {
		theIcon->SetIconID(ics8_Unlocked);
	}
}




