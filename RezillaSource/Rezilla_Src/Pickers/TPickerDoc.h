// ===========================================================================
// TPickerDoc.h				
// 
//                       Created: 2006-02-23 15:12:16
//             Last modification: 2006-10-27 11:13:13
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================

#pragma once

#include "CPickerDoc.h"
#include "CPickerWindow.h"
#include "CRezMapDoc.h"
#include "CRezObj.h"
#include "CRezObjItem.h"
#include "CRezType.h"
#include "CRezTypeItem.h"
#include "CRezMapTable.h"
#include "TPickerView.h"
#include "RezillaConstants.h"
#include "UMessageDialogs.h"

#include <LWindow.h>

class CRezMapTable;
class CRezTypeItem;


template <class T> class TPickerDoc : public CPickerDoc {
public:

					TPickerDoc(LCommander* inSuper, 
							   CRezMapTable* inSuperMap, 
							   CRezTypeItem* inRezTypeItem,
							   Boolean inReadOnly)
						: CPickerDoc(inSuper, inSuperMap, inRezTypeItem, inReadOnly) 
							{
								mPickerWindow = nil;
								Initialize();
								RegisterDoc();
							}

					~TPickerDoc() {}
					

// ---------------------------------------------------------------------------
//   GetDescriptor
// ---------------------------------------------------------------------------
virtual StringPtr
GetDescriptor( Str255 outDescriptor ) const
{
	if (mPickerWindow != nil) {
		// Use name of its window
		mPickerWindow->GetDescriptor(outDescriptor);
	} else {
		// No window, document name is empty string
		outDescriptor[0] = 0;		
	}

	return outDescriptor;
}


#if PP_Uses_CFDescriptor
// --------------------------------------------------------------------------
//	CopyCFDescriptor												  [public]
// --------------------------------------------------------------------------
virtual CFStringRef
CopyCFDescriptor() const
{
	CFStringRef		docName;
	if (mPickerWindow != nil) {
		docName = mPickerWindow->CopyCFDescriptor();
	}
	return docName;
}
#endif


// ---------------------------------------------------------------------------
//  ObeyCommand												[public, virtual]
// ---------------------------------------------------------------------------
Boolean
ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean			cmdHandled = true;
	
	switch (inCommand) {
		
		default:
		cmdHandled = CPickerDoc::ObeyCommand(inCommand, ioParam);
		break;
	}
	
	return cmdHandled;	
}


// ---------------------------------------------------------------------------
//   ListenToMessage												[public]
// ---------------------------------------------------------------------------

void
ListenToMessage( MessageT inMessage, void * ioParam) 
{
	short theID;
	SInt32 theLong;
	StGrafPortSaver	savePort( mPickerWindow->GetMacPort() );

	switch (inMessage) {
				
		case msg_RezObjCreated:
		case msg_RezObjDuplicated:
		case msg_RezObjPasted:
		theID = *(short*) ioParam;
		CreateNewPicker(theID);
		mPickerWindow->RecalcLayout();
		mPickerWindow->IncrRezCountField(1);
		break;
				
		case msg_RezIDChanged:
		theLong = (SInt32) ioParam;
		// The ioParam is formatted as follows: 
		// the low word has the old ID, the high word has the new one
		theID = LoWord(theLong);
		mPickerWindow->DeletePickerView(theID);
		theID = HiWord(theLong);
		CreateNewPicker(theID);
		mPickerWindow->RecalcLayout();
		break;
				
		case msg_RezObjDeleted:
		theID = *(short*) ioParam;
		mPickerWindow->DeletePickerView(theID);
		mPickerWindow->IncrRezCountField(-1);
		break;
				
		case msg_RezTypeDeleted:
		delete this;
		break;
				
		case msg_RezDataChanged:
		mPickerWindow->Refresh();
		break;
				
		default:
		break;
		
	}
}


// =========================
protected:
// =========================

// ---------------------------------------------------------------------------
//   NameNewPickerDoc
// ---------------------------------------------------------------------------
void
NameNewPickerDoc()
{
	Str255 theTitle;
	
	// Build the title
	BuildDocumentTitle(theTitle, index_PickerDocUntitled);
	// Set window title
	if (mPickerWindow != nil) {
		mPickerWindow->SetDescriptor(theTitle);
	}
}


// ---------------------------------------------------------------------------
//   Initialize
// ---------------------------------------------------------------------------
void
Initialize()
{
	OSErr	error = noErr;
	SInt16	theWidth, theHeight;
	SInt32	theCount = 0;

	// Create window for our document. This sets this doc as the SuperCommander of the window.
	mPickerWindow = dynamic_cast<CPickerWindow *>(LWindow::CreateWindow( PPob_RezPickerWindow, this ));
	Assert_( mPickerWindow != nil );
	
	SetPickerWindow(mPickerWindow);
	NameNewPickerDoc();
	
	mPickerWindow->SetType(mRezTypeItem->GetRezType()->GetType());
	mPickerWindow->FinalizePicker(this);
	
	// Retreive the stamps size
	T::StampSize(mRezTypeItem->GetRezType()->GetType(), theWidth, theHeight);
	mPickerWindow->SetStampSize(theWidth, theHeight);
	
	try {
		short		theID;
		LLongComparator* idComparator = new LLongComparator;
		TArray<short>* idsArray = new TArray<short>( idComparator, true);
		TArrayIterator<short>	iterator(*idsArray);
		
		// Get a list of the resource IDs
		mRezTypeItem->GetRezType()->GetAllRezIDs(idsArray);
		theCount = idsArray->GetCount();
		
		while (iterator.Next(theID)) {
			CreateNewPicker(theWidth, theHeight, theID);
		}
	} catch (...) {
		delete this;
		UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("ErrorCreatingResourcePicker"), error);
		return;
	}

	// Set the resource count field
	mPickerWindow->SetRezCountField(theCount);
	
	// Make the window visible.
	mPickerWindow->RecalcLayout();
	mPickerWindow->Show();
}


// ---------------------------------------------------------------------------
//   CreateNewPicker
// ---------------------------------------------------------------------------
TPickerView<T>* 
CreateNewPicker(ResIDT inID)
{
	SInt16	theWidth, theHeight;

	T::StampSize(mRezTypeItem->GetRezType()->GetType(), theWidth, theHeight);
	return CreateNewPicker(theWidth, theHeight, inID);
}


// ---------------------------------------------------------------------------
//   CreateNewPicker
// ---------------------------------------------------------------------------
TPickerView<T>* 
CreateNewPicker(SInt16 inStampWidth, SInt16 inStampHeight, ResIDT inID)
{
	TPickerView<T>* thePickerView = new TPickerView<T>(inStampWidth, inStampHeight, inID);
	ThrowIfNil_(thePickerView);
	mPickerWindow->AddPickerView( (CPickerView*) thePickerView);
	thePickerView->PutInside(mPickerWindow->GetContentsView());
	thePickerView->SetOwnerWindow(mPickerWindow);
	
	// Cache the map's refNum in the view's userCon
	thePickerView->SetUserCon(mRezMapTable->GetRezMap()->GetRefnum());
	
	return thePickerView;
}


};


