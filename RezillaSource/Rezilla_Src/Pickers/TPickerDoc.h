// ===========================================================================
// TPickerDoc.h				
// 
//                       Created: 2006-02-23 15:12:16
//             Last modification: 2006-03-16 12:41:12
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================

// #ifndef _H_TPickerDoc
// #define _H_TPickerDoc
#pragma once

#include "CPickerDoc.h"
#include "CPickerWindow.h"
#include "TPickerView.h"
#include "RezillaConstants.h"
#include "UMessageDialogs.h"

#include <LWindow.h>

class CRezMapTable;
class CRezObj;
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
								Register();
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
	OSType	theType = mRezTypeItem->GetRezType()->GetType();

	// Create window for our document. This sets this doc as the SuperCommander of the window.
	mPickerWindow = dynamic_cast<CPickerWindow *>(LWindow::CreateWindow( PPob_RezPickerWindow, this ));
	Assert_( mPickerWindow != nil );
	
	SetPickerWindow(mPickerWindow);
	NameNewPickerDoc();
	
	mPickerWindow->FinalizePicker(this);
	
	T::StampSize(theType, theWidth, theHeight);
	mPickerWindow->SetStampSize(theWidth, theHeight);
	
	try {
		short		theID;
		LView*		cntsView = mPickerWindow->GetContentsView();
		
		LLongComparator* idComparator = new LLongComparator;
		TArray<short>* idsArray = new TArray<short>( idComparator, true);
		TArrayIterator<short>	iterator(*idsArray);
		
		// Get a list of the resource IDs
		mRezTypeItem->GetRezType()->GetAllRezIDs(idsArray);
		
		while (iterator.Next(theID)) {
			TPickerView<T>* thePickerView = new TPickerView<T>(theWidth, theHeight, theID);
			mPickerWindow->AddPickerView( (CPickerView*) thePickerView);
			thePickerView->PutInside(cntsView);
			thePickerView->SetOwnerWindow(mPickerWindow);
			thePickerView->SetUserCon(theType);
		}
	} catch (...) {
		delete this;
		UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("ErrorCreatingResourcePicker"), error);
		return;
	}

	// Make the window visible.
	mPickerWindow->RecalcLayout();
	mPickerWindow->Show();
}


};


// #endif  // _H_TPickerDoc
