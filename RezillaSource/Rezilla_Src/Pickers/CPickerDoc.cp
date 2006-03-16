// ===========================================================================
// CPickerDoc.cp
// 
//                       Created: 2006-02-23 15:12:16
//             Last modification: 2006-02-26 17:35:45
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================

PP_Begin_Namespace_PowerPlant

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CRezillaApp.h"
#include "CInspectorWindow.h"
#include "CPickerDoc.h"
#include "CPickerWindow.h"
#include "CRezMapDoc.h"
#include "CRezFile.h"
#include "CRezMapTable.h"
#include "CRezTypeItem.h"
#include "CRezType.h"
#include "RezillaConstants.h"
#include "UMessageDialogs.h"
#include "UMiscUtils.h"

#include <LString.h>
#include <UStandardDialogs.h>


// ---------------------------------------------------------------------------
//   CPickerDoc									Constructor		  [public]
// ---------------------------------------------------------------------------

CPickerDoc::CPickerDoc(LCommander* inSuper, 
						   CRezMapTable* inSuperMap, 
						   CRezTypeItem* inRezTypeItem,
						   Boolean inReadOnly)
 	: LDocument(inSuper)
{
	mRezTypeItem = inRezTypeItem;
	mRezMapTable = inSuperMap;
	mReadOnly = inReadOnly;
	
	// Set the AE model object
	SetModelKind(rzom_cPickerDoc);
	
	// The owner RezMapDoc is the super model
	SetSuperModel( dynamic_cast<LModelObject *>(inSuper) );
}


// ---------------------------------------------------------------------------
//     ~CPickerDoc							Destructor				  [public]
// ---------------------------------------------------------------------------

CPickerDoc::~CPickerDoc()
{
	Unregister();
}


// ---------------------------------------------------------------------------------
//   BuildDocumentTitle
// ---------------------------------------------------------------------------------

void
CPickerDoc::BuildDocumentTitle(Str255 & outTitle, SInt16 whichString)
{
	FSSpec	theFileSpec;
	mRezMapTable->GetOwnerDoc()->GetRezFile()->GetSpecifier(theFileSpec);
	LStr255 theTitle(theFileSpec.name);
	theTitle.Append("\p - '");
	
	if ( mRezTypeItem != nil ) {
		Str255 theString;

		UMiscUtils::OSTypeToPString(mRezTypeItem->GetRezType()->GetType(), theString);	
		theTitle.Append(theString);
		theTitle.Append("\p' Picker");
	} else {
		// Start with the default name ("Picker [1]")
		theTitle.Assign(STRx_DefaultDocTitles, whichString);
		// If an existing window has this name, append a count and
		// keep incrementing the count until we find a unique name.
		long	num = 1;
		while (UWindows::FindNamedWindow(theTitle) != nil) {
			theTitle.Assign(STRx_DefaultDocTitles, whichString + 1);
			++num;
			theTitle += "\p [";
			theTitle += num;
			theTitle += "\p]";
		}		
	}
	LString::CopyPStr(theTitle, outTitle);
}


// ---------------------------------------------------------------------------------
//   FindCommandStatus
// ---------------------------------------------------------------------------------

void
CPickerDoc::FindCommandStatus(
	CommandT	inCommand,
	Boolean		&outEnabled,
	Boolean		&outUsesMark,
	UInt16		&outMark,
	Str255		outName )
{
	switch ( inCommand ) {
	
		case cmd_Save:
		case cmd_SaveAs:
		case cmd_Export:
		case cmd_FindNext:
			outEnabled = false;
		break;

		case cmd_Find:
		LString::CopyPStr( "\pFind...", outName);
		outEnabled = false;
		break;

		case cmd_Close : 
		outEnabled = true;
		break;
								
		case cmd_Copy:
		outEnabled = true;
		break;
		
		case cmd_Clear:
		case cmd_Cut:
		case cmd_Paste:
		outEnabled = not mReadOnly;
		break;

	  default:
		// Call inherited.
		LDocument::FindCommandStatus( inCommand,
				outEnabled, outUsesMark, outMark, outName );
		break;

	}
}


// ---------------------------------------------------------------------------
//   ListenToMessage													[public]
// ---------------------------------------------------------------------------

void
CPickerDoc::ListenToMessage( MessageT inMessage, void * ioParam) 
{
	switch (inMessage) {
		case msg_RezChangedForType:
// 		ResType theType = *((ResType*) ioParam);
// 		if (mRezTypeItem->GetRezType()->GetType() == theType) {
// 			mPickerWindow->RecalcStampLayout();
// 		} 
		break;
				
		default:
		break;
		
	}
}


// ---------------------------------------------------------------------------
//   AllowSubRemoval												  [public]
// ---------------------------------------------------------------------------

Boolean
CPickerDoc::AllowSubRemoval(
	LCommander* /* inSub */)
{
	return true;
}


// ---------------------------------------------------------------------------
//   AttemptClose													  [public]
// ---------------------------------------------------------------------------
//	Close an opened picker

void
CPickerDoc::AttemptClose(
	Boolean	/* inRecordIt */)
{
	Close();
}


// ---------------------------------------------------------------------------
//   DoAEClose														  [public]
// ---------------------------------------------------------------------------
// Close a Picker in response to a "close" AppleEvent. Optional "file"
// and "saveOption" parameters are ignored.

void
CPickerDoc::DoAEClose(
	const AppleEvent&	/* inCloseAE */)
{
	Close();
}


// ---------------------------------------------------------------------------
//   GetDescriptor													  [public]
// ---------------------------------------------------------------------------
//	Pass back the name of a Document. This is overriden in the TPickerDoc 
//	template class.

StringPtr
CPickerDoc::GetDescriptor(
	Str255	outDescriptor) const
{
	outDescriptor[0] = 0;		
	return outDescriptor;
}


// ---------------------------------------------------------------------------------
//   SelectPickerWindow
// ---------------------------------------------------------------------------------

void
CPickerDoc::SelectPickerWindow()
{
	if (mPickerWindow != nil) {
		mPickerWindow->Select();
	} 
}
 

// ---------------------------------------------------------------------------------
//   Register
// ---------------------------------------------------------------------------------

void
CPickerDoc::Register()
{
	mRezMapTable->GetOwnerDoc()->GetOpenedPickers()->AddItem(this);
}


// ---------------------------------------------------------------------------------
//   Unregister
// ---------------------------------------------------------------------------------

void
CPickerDoc::Unregister()
{
	mRezMapTable->GetOwnerDoc()->GetOpenedPickers()->Remove(this);
}



PP_End_Namespace_PowerPlant


