// ===========================================================================
// CInspectorWindowAE.cp
// 
//                       Created: 2005-04-26 09:48:48
//             Last modification: 2006-10-08 09:00:28
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2005-2006
// All rights reserved.
// ===========================================================================
//  AppleEvent Object Model Support. These methods are part of the CInspectorWindow 
//  class (inheriting from LModelObject).

#include "CInspectorWindow.h"
#include "CRezillaApp.h"
#include "CRezObj.h"
#include "CRezObjItem.h"
#include "CRezMapTable.h"
#include "RezillaConstants.h"

#include <LCommander.h>
#include <LCheckBox.h>
#include <LEditText.h>


// ---------------------------------------------------------------------------
//   MakeSelfSpecifier												  [public]
// ---------------------------------------------------------------------------
// Specify by position

void
CInspectorWindow::MakeSelfSpecifier(
	AEDesc	&inSuperSpecifier,
	AEDesc	&outSelfSpecifier) const
{
		StAEDescriptor	keyData;
		OSErr			err;
		SInt32			windowIndex = 1;
		
		keyData.Assign(windowIndex);

		err = ::CreateObjSpecifier(	rzom_cInspWindow,
									&inSuperSpecifier,
									formAbsolutePosition,
									keyData,
									false,		// Don't dispose inputs
									&outSelfSpecifier);
		ThrowIfOSErr_(err);
}


// ---------------------------------------------------------------------------
//   GetAEProperty
// ---------------------------------------------------------------------------

void
CInspectorWindow::GetAEProperty(
	DescType		inProperty,
	const AEDesc&	inRequestedType,
	AEDesc&			outPropertyDesc) const
{
	OSErr	error = noErr;
	
	switch (inProperty) {
		case rzom_pNameField: 
		Str255	name;
		mNameField->GetDescriptor(name);
		error = ::AECreateDesc(typeChar, (Ptr) name + 1,
							StrLength(name), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
		

		case rzom_pIDField:
		Str255	idStr;
		long	theLong;
		short	theID;
		
		mIDField->GetDescriptor(idStr);
		::StringToNum(idStr, &theLong);
		theID = theLong;
		error = ::AECreateDesc(typeSInt16, (Ptr) &theID,
									sizeof(short), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
		
		
		case rzom_pSysHeap:
		case rzom_pLocked:
		case rzom_pPreload:
		case rzom_pProtected:
		case rzom_pPurgeable:
		GetAEAttribute(inProperty, outPropertyDesc);
		break;
		
		
		// 		case rzom_pCurrResource:
		// Handled in GetModelProperty
		// 		break;
		
		
		default:
		LWindow::GetAEProperty(inProperty, inRequestedType,
									outPropertyDesc);
		break;
	}
}


// ---------------------------------------------------------------------------
//   SetAEProperty
// ---------------------------------------------------------------------------

void
CInspectorWindow::SetAEProperty(
	DescType		inProperty,
	const AEDesc&	inValue,
	AEDesc&			outAEReply)
{
	switch (inProperty) {
		case rzom_pNameField: {
			Str255	theName;
			UExtractFromAEDesc::ThePString(inValue, theName, sizeof(theName));
			mNameField->SetDescriptor(theName);
			break;
		}

		case rzom_pIDField: {
			Str255	theString;
			short	theID;
			
			UExtractFromAEDesc::TheSInt16(inValue, theID);
			::NumToString(theID, theString);
			mIDField->SetDescriptor(theString);
			break;
		}
		
		case rzom_pSysHeap:
		SetAEAttribute(inValue, resSysHeap);
		break;
		
		case rzom_pPurgeable:
		SetAEAttribute(inValue, resPurgeable);
		break;
		
		case rzom_pLocked:
		SetAEAttribute(inValue, resLocked);
		break;
		
		case rzom_pProtected:
		SetAEAttribute(inValue, resProtected);
		break;
		
		case rzom_pPreload:
		SetAEAttribute(inValue, resPreload);
		break;
		
		default:
		LWindow::SetAEProperty(inProperty, inValue, outAEReply);
		break;
	}
}


// ---------------------------------------------------------------------------
//   AEPropertyExists
// ---------------------------------------------------------------------------

bool
CInspectorWindow::AEPropertyExists(
	DescType	inProperty) const
{
	bool	exists = false;

	switch (inProperty) {
		case pName: 
		case rzom_pLocked:
		case rzom_pPreload:
		case rzom_pProtected:
		case rzom_pPurgeable:
		case rzom_pResID:
		case rzom_pSysHeap:
		exists = true;
		break;
		
		default:
			exists = LWindow::AEPropertyExists(inProperty);
			break;
	}

	return exists;
}


// ---------------------------------------------------------------------------
//   GetAEAttribute
// ---------------------------------------------------------------------------

void
CInspectorWindow::GetAEAttribute(
	 DescType	inProperty,
	AEDesc&		outPropertyDesc) const
{
	OSErr	error = noErr;
	Boolean	theBool;
	
	switch (inProperty) {
		case rzom_pSysHeap:
		theBool = mSysHeapItem->GetValue();
		break;
		
		case rzom_pPurgeable:
		theBool = mPurgeableItem->GetValue();
		break;
		
		case rzom_pLocked:
		theBool = mLockedItem->GetValue();
		break;
		
		case rzom_pProtected:
		theBool = mProtectedItem->GetValue();
		break;
		
		case rzom_pPreload:
		theBool = mPreloadItem->GetValue();
		break;
	}
	
	error = ::AECreateDesc(typeBoolean, &theBool,
						sizeof(Boolean), &outPropertyDesc);
	ThrowIfOSErr_(error);
}


// ---------------------------------------------------------------------------
//   SetAEAttribute
// ---------------------------------------------------------------------------

void
CInspectorWindow::SetAEAttribute(const AEDesc& inValue, short inFlag) 
{
	Boolean		theBool;
	
	UExtractFromAEDesc::TheBoolean(inValue, theBool);
	
	SetValueForAttribute(inFlag, theBool);
}


// ---------------------------------------------------------------------------
//   GetModelProperty
// ---------------------------------------------------------------------------

LModelObject*
CInspectorWindow::GetModelProperty(DescType inProperty) const
{
	LModelObject* theModelObject = nil;

	switch (inProperty) {

		case rzom_pCurrResource:
		if (mOwnerTable) {
			CRezObjItem * theRezObjItem = mOwnerTable->GetRezObjItem( mSavedInfo.type, mSavedInfo.id, true);
			if (theRezObjItem != nil) {
				CRezObj * rezObj = theRezObjItem->GetRezObj();
				if (rezObj != nil) {
					theModelObject = dynamic_cast<LModelObject *>(rezObj);
				} 
			} 
		} 
		break;
		

		default:
		theModelObject = LModelObject::GetModelProperty(inProperty);
			break;
	}

	return theModelObject;
}


// ---------------------------------------------------------------------------
//   HandleAppleEvent												  [public]
// ---------------------------------------------------------------------------

void
CInspectorWindow::HandleAppleEvent(
	const AppleEvent	&inAppleEvent,
	AppleEvent			&outAEReply,
	AEDesc				&outResult,
	long				inAENumber)
{
	OSErr error = noErr;
	
	CRezillaApp::sCalledFromAE = true;

	switch (inAENumber) {

		case ae_Close:
		Hide();
		break;

		case ae_Save:
		ListenToMessage(msg_InspModify, &error);
		break;

		case ae_Revert:
		ListenToMessage(msg_InspRevert, NULL);
		break;

		default:
		LModelObject::HandleAppleEvent(inAppleEvent, outAEReply, outResult, inAENumber);
		break;
	}
	
	CRezillaApp::sCalledFromAE = false;
}



