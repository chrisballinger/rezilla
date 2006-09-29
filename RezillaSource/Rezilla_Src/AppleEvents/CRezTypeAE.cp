// ===========================================================================
// CRezTypeAE.cp
// 
//                       Created: 2005-04-09 10:03:39
//             Last modification: 2006-09-28 23:52:25
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2005-2006
// All rights reserved.
// ===========================================================================
//  AppleEvent Object Model Support. These methods are part of the CRezType 
//  class (inheriting from LModelObject).

#include "CRezMap.h"
#include "CRezType.h"
#include "CRezObj.h"
#include "CRezMapDoc.h"
#include "CEditorDoc.h"
#include "CRezMapWindow.h"
#include "CRezMapTable.h"
#include "CRezTypeItem.h"
#include "CRezObjItem.h"
#include "CPickerDoc.h"
#include "CRezillaApp.h"
#include "CPickersController.h"
#include "CInspectorWindow.h"
#include "UMiscUtils.h"
#include "RezillaConstants.h"

#include <LCommander.h>



// ---------------------------------------------------------------------------
//   MakeSelfSpecifier												  [public]
// ---------------------------------------------------------------------------

void
CRezType::MakeSelfSpecifier(
	AEDesc	&inSuperSpecifier,
	AEDesc	&outSelfSpecifier) const
{
		StAEDescriptor	keyData;
		OSErr			err;
		Str255			name;

		// Specify by name
		GetModelName(name);
		keyData.Assign(name);

		err = ::CreateObjSpecifier(rzom_cRezType, &inSuperSpecifier, formName,
										keyData, false, &outSelfSpecifier);
		ThrowIfOSErr_(err);
}


// ---------------------------------------------------------------------------
//   GetAEProperty
// ---------------------------------------------------------------------------
//	Return a descriptor for the specified Property
//  rzom_pName			= pName;		// Name ('pnam')

void
CRezType::GetAEProperty(
	DescType		inProperty,
	const AEDesc&	inRequestedType,
	AEDesc&			outPropertyDesc) const
{
	OSErr	error = noErr;
	
	switch (inProperty) {
		
		case pIndex: {
			// Return the index of this type in the rezmap doc
			SInt32	position = mOwnerMap->GetOwnerDoc()->GetIndexForType(mType);
			if (position > 0) {
				error = ::AECreateDesc(typeSInt32, (Ptr) &position,
											sizeof(SInt32), &outPropertyDesc);
			} else {
				error = errAENoSuchObject;
			}
			ThrowIfOSErr_(error);
			break;
		}
		

		case pName: 
		Str255	name;
		GetModelName(name);
		error = ::AECreateDesc(typeChar, (Ptr) name + 1,
							StrLength(name), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;

		
		case pID: 
		error = ::AECreateDesc(typeUInt32, &mType,
							sizeof(UInt32), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;

		
		case rzom_pIDsList: {
			if (outPropertyDesc.descriptorType == typeNull) {
				error = ::AECreateList(nil, 0, false, &outPropertyDesc);
				ThrowIfOSErr_(error);
			}
			
			short		theID;
			UInt16		index = 1;
			LLongComparator* idComparator = new LLongComparator;
			TArray<short>* idsArray = new TArray<short>( idComparator, true);
			TArrayIterator<short>	iterator(*idsArray);
			
			GetAllRezIDs(idsArray);
			
			while (iterator.Next(theID)) {
				StAEDescriptor	keyData;
								
				error = ::AECreateDesc(typeSInt16, &theID, sizeof(short), &keyData.mDesc);
				error = ::AEPutDesc(&outPropertyDesc, index, &keyData.mDesc);
				index++;
			}
			
			if (idsArray != nil) { delete idsArray; } 
			break; 
		}
			
		
		default:
		LModelObject::GetAEProperty(inProperty, inRequestedType,
									outPropertyDesc);
		break;
	}
}


// ---------------------------------------------------------------------------
//	 CountSubModels												  [public]
// ---------------------------------------------------------------------------
// Had to modify the prototypes for CountAllTypes and CountAllResources by
// adding a 'const' to make the compiler happy.

SInt32
CRezType::CountSubModels(
	DescType	inModelID) const
{
	SInt32	result = 0;
	short	count = 0;
	
	switch (inModelID) {
		
		case rzom_cRezObj: 
		if (CountResources(count) == noErr) {
			result = count;
		}
		break;

		default:
		result = LModelObject::CountSubModels(inModelID);
		break;
	}

	return result;
}


// ---------------------------------------------------------------------------
//	 GetSubModelByPosition											  [public]
// ---------------------------------------------------------------------------

void
CRezType::GetSubModelByPosition(
	DescType		inModelID,
	SInt32			inPosition,
	AEDesc&			outToken) const
{
	switch (inModelID) {
		
		case rzom_cRezObj: {
		CRezObj *	theRezObj = nil;
		Handle		theHandle;
		OSErr		error;
	
		error = GetResourceAtIndex( (short) inPosition, theHandle, true);
		if (error == noErr) {
			theRezObj = GetOrCreateRezObjModel(theHandle);
		} 
			
		if (theRezObj != nil) {
			PutInToken(theRezObj, outToken);
		} else {
			ThrowOSErr_(errAENoSuchObject);
		}
		break;
		}
		
		default:
		LModelObject::GetSubModelByPosition(inModelID, inPosition,
											outToken);
		break;
	}
}


// ---------------------------------------------------------------------------
//	 GetSubModelByName												  [public]
// ---------------------------------------------------------------------------
//	Pass back a token to a SubModel specified by name

void
CRezType::GetSubModelByName(
	DescType		inModelID,
	Str255			inName,
	AEDesc&			outToken) const
{
	switch (inModelID) {

		case rzom_cRezObj: {
		CRezObj *	theRezObj = nil;
		Handle		theHandle;
		OSErr		error;
	
		error = GetWithName(inName, theHandle);
		if (error == noErr) {
			theRezObj = GetOrCreateRezObjModel(theHandle);
		} 
			
		if (theRezObj != nil) {
			PutInToken(theRezObj, outToken);
		} else {
			ThrowOSErr_(errAENoSuchObject);
		}
		break;
		}

		default:
			LModelObject::GetSubModelByName(inModelID, inName, outToken);
			break;
	}
}


// ---------------------------------------------------------------------------
//	 GetSubModelByUniqueID
// ---------------------------------------------------------------------------
//	Pass back a Token for the SubModel with the specified unique ID: this
//	is the type as an unsigned long.

void
CRezType::GetSubModelByUniqueID(
	DescType		inModelID,
	const AEDesc	&inKeyData,
	AEDesc			&outToken) const
{
	if (inModelID == rzom_cRezObj) {
		CRezObj *	theRezObj = nil;
		Handle		theHandle;
		SInt32		theID;
		OSErr		error;
		
		error = ::AEGetDescData(&inKeyData, &theID, sizeof(theID));
		ThrowIfOSErr_(error);

		error = GetWithID(theID, theHandle);
		if (error == noErr && theHandle != nil) {
			theRezObj = GetOrCreateRezObjModel(theHandle);
		} 
			
		if (theRezObj != nil) {
			PutInToken(theRezObj, outToken);
		} else {
			ThrowOSErr_(errAENoSuchObject);
		}
	}
}


// ---------------------------------------------------------------------------
//   GetModelName
// ---------------------------------------------------------------------------
//	Return the name of a Window as an AppleEvent model object(Str255&) 

StringPtr
CRezType::GetModelName(
	Str255	outModelName) const
{
	Str255	name;
	UMiscUtils::OSTypeToPString(mType, name);
	LString::CopyPStr(name, outModelName);
	return outModelName;
}


// ---------------------------------------------------------------------------
//   AEPropertyExists
// ---------------------------------------------------------------------------

bool
CRezType::AEPropertyExists(
	DescType	inProperty) const
{
	bool	exists = false;

	switch (inProperty) {

		case pIndex:
		case pName:
		case pID:
			exists = true;
			break;

		default:
			exists = LModelObject::AEPropertyExists(inProperty);
			break;
	}

	return exists;
}


// ---------------------------------------------------------------------------
//   GetOrCreateRezObjModel
// ---------------------------------------------------------------------------

CRezObj *
CRezType::GetOrCreateRezObjModel(Handle inHandle) const
{
	CRezObj 	*theRezObj = nil, *newRezObj = nil;
	Boolean		found = false;
	
	if (inHandle != nil) {
		newRezObj = new CRezObj( inHandle, mOwnerMap->GetRefnum() );
		
		TArrayIterator<CRezObj*> iterator(mRezObjModels);
		while (iterator.Next(theRezObj)) {
			if (theRezObj->GetID() == newRezObj->GetID()) {
				found = true;
				break;
			}
		}
		
		if (found) {
			delete newRezObj;
			newRezObj = theRezObj;	
		} else {
			newRezObj->SetSuperModel( (CRezType *) this);
			// cast is needed because of constness
			TArray<CRezObj *>* arrayPtr = (TArray<CRezObj *>*)&mRezObjModels;
			arrayPtr->AddItem(newRezObj);
		}
	} 
	
	return newRezObj;
}


// ---------------------------------------------------------------------------
//   HandleAppleEvent												  [public]
// ---------------------------------------------------------------------------

void
CRezType::HandleAppleEvent(
	const AppleEvent&	inAppleEvent,
	AppleEvent&			outAEReply,
	AEDesc&				outResult,
	long				inAENumber)
{	
	switch (inAENumber) {
				
		case ae_Delete:
		// This is the delete event applied to a type
		HandleDeleteTypeEvent(inAppleEvent, outAEReply, outResult);	
		break;
		
		
		case aeRzil_Pick:
		// This is the "display" event to open a picker for this type
		HandlePickTypeEvent(inAppleEvent, outAEReply, outResult);	
		break;
		
		
		default:
// 		mOwnerMap->HandleAppleEvent(inAppleEvent, outAEReply, outResult, inAENumber);
		LModelObject::HandleAppleEvent(inAppleEvent, outAEReply, outResult, inAENumber);
		break;
	}
}


// ---------------------------------------------------------------------------
//   HandleResourceEvent											  [public]
// ---------------------------------------------------------------------------

void
CRezType::HandleResourceEvent(
	  const AppleEvent&	inAppleEvent,
	  AppleEvent&		outAEReply,
	  AEDesc&			outResult,
	  CRezObj *			inRezObj,
	  long				inAENumber)
{	
	switch (inAENumber) {
		case aeRzil_Edit:
		HandleEditEvent(inAppleEvent, outAEReply, outResult, inRezObj->GetID());	
		break;
		
		
		case ae_Clone: {
			StAEDescriptor	repDesc;
			CRezMapDoc * theDoc = mOwnerMap->GetOwnerDoc();
			CRezObj * theRezObj = theDoc->DuplicateResource(inRezObj);

			theRezObj->MakeSpecifier(repDesc);
			::AEPutParamDesc(&outAEReply, keyDirectObject, (const AEDesc *)&repDesc);
			break;
		}
		
		
		case ae_Delete:
		// This is the delete event applied to a resource (not a type). It 
		// is called from CRezObj::HandleAppleEvent().
		HandleDeleteResourceEvent(inAppleEvent, outAEReply, outResult, inRezObj);	
		break;
		
		
		case aeRzil_Inspect:
		HandleInspectEvent(inAppleEvent, outAEReply, outResult, inRezObj->GetID());	
		break;
		
		
		default:
		mOwnerMap->HandleAppleEvent(inAppleEvent, outAEReply, outResult, inAENumber);
		break;
	}
}


// ---------------------------------------------------------------------------
//   HandleEditEvent												  [public]
// ---------------------------------------------------------------------------

void
CRezType::HandleEditEvent(
	const AppleEvent&	inAppleEvent,
	AppleEvent&			outAEReply,
	AEDesc&				outResult,
	short				inID)
{
#pragma unused(outAEReply, outResult)
	
	OSErr		ignoreErr;
	DescType	returnedType;
	Size		actualSize;
	ResType		asType = 0;
	ResType		theKind = 0;
	CommandT	theCmd = cmd_EditRez;
	
	// Extract optional "like" parameter ("like another type")
	ignoreErr = ::AEGetParamPtr(&inAppleEvent, kAERzilLike, typeType,
							  &returnedType, &asType, sizeof(ResType), &actualSize);

	// Extract optional "using" parameter ("using a particular editor")
	ignoreErr = ::AEGetParamPtr(&inAppleEvent, keyAEUsing, typeEnumerated,
							  &returnedType, &theKind, sizeof(ResType), &actualSize);

	// Map to the equivalent menu command
	if (theKind == rzom_eHexEditor) {
		theCmd = cmd_HexEditRez;
	} else if (theKind == rzom_eTmplEditor) {
		theCmd = cmd_TmplEditRez;
	} else if (asType != 0) {
		theCmd = cmd_EditRezAsType;
	} 
	
	// Find the corresponding RezObjItem in the RezMap document
	CRezMapDoc *	theDoc = mOwnerMap->GetOwnerDoc();
	ThrowIfNil_(theDoc);
	
	CRezObjItem * theRezObjItem = theDoc->GetRezMapWindow()->GetRezMapTable()->GetRezObjItem(mType, inID, true);
	ThrowIfNil_(theRezObjItem);
	
	theDoc->TryEdit(theRezObjItem, theCmd, asType);
	
	// Return an object specifier in the reply
	CEditorDoc * theRezEditor = theDoc->GetRezEditor(mType, inID);
	if (theRezEditor != nil) {
		StAEDescriptor	repDesc;
		theRezEditor->MakeSpecifier(repDesc);
		::AEPutParamDesc(&outAEReply, keyDirectObject, (const AEDesc *)&repDesc);
	}
	
}


// ---------------------------------------------------------------------------
//   HandleInspectEvent												  [public]
// ---------------------------------------------------------------------------

void
CRezType::HandleInspectEvent(
	const AppleEvent&	inAppleEvent,
	AppleEvent&			outAEReply,
	AEDesc&				outResult,
	short				inID)
{
#pragma unused(inAppleEvent, outAEReply, outResult)
		
	// Find the corresponding RezObjItem in the RezMap document
	CRezMapDoc *	theDoc = mOwnerMap->GetOwnerDoc();
	ThrowIfNil_(theDoc);
	
	CRezObjItem * theRezObjItem = theDoc->GetRezMapWindow()->GetRezMapTable()->GetRezObjItem(mType, inID, true);
	ThrowIfNil_(theRezObjItem);

	CRezillaApp::sInspectorWindow->Show();
	CRezillaApp::sInspectorWindow->InstallValues(theRezObjItem);
}


// ---------------------------------------------------------------------------
//   HandleDeleteResourceEvent										 [public]
// ---------------------------------------------------------------------------

void
CRezType::HandleDeleteResourceEvent(
	const AppleEvent&	inAppleEvent,
	AppleEvent&			outAEReply,
	AEDesc&				outResult,
	CRezObj *			inRezObj)
{
#pragma unused(inAppleEvent, outAEReply, outResult)

	// Find the corresponding RezObjItem in the RezMap document
	CRezMapDoc *	theDoc = mOwnerMap->GetOwnerDoc();
	ThrowIfNil_(theDoc);
	
	CRezObjItem * theRezObjItem = theDoc->GetRezMapWindow()->GetRezMapTable()->GetRezObjItem(mType, inRezObj->GetID(), true);
	ThrowIfNil_(theRezObjItem);

	// Delete the rezobj in the mRezObjModels list. The RezObj contained 
	// in the theRezObjItem and the one in the list are NOT the same. 
	// IMPORTANT: this must be done _before_ the call to RemoveResource()
	// because, if there is only one RezObjItem, removing it causes the
	// RezTypeItem to be deleted too which deletes the mRezObjModels list
	mRezObjModels.Remove(inRezObj);
	delete inRezObj;

	// Now remove the RezObjItem
	theDoc->RemoveResource(theRezObjItem);
}


// ---------------------------------------------------------------------------
//   HandleDeleteTypeEvent										 [public]
// ---------------------------------------------------------------------------

void
CRezType::HandleDeleteTypeEvent(
	const AppleEvent&	inAppleEvent,
	AppleEvent&			outAEReply,
	AEDesc&				outResult)
{
#pragma unused(inAppleEvent, outAEReply, outResult)
	
	// Find the corresponding RezTypeItem in the RezMap document
	CRezTypeItem *	theRezTypeItem = nil;
	CRezMapDoc *	theDoc = mOwnerMap->GetOwnerDoc();
	ThrowIfNil_(theDoc);

	// 'true' expands the RezTypeItem
	theRezTypeItem = theDoc->GetRezMapWindow()->GetRezMapTable()->GetRezTypeItem(mType, true);
	ThrowIfNil_(theRezTypeItem);

	// Iterate among the RezObjItems it contains and delete them
	LArrayIterator	iterator( *(theRezTypeItem->GetSubItems()) );
	LOutlineItem *	theItem = nil;	
	
	while (iterator.Next(&theItem)) {
		CRezObjItem * theRezObjItem = dynamic_cast<CRezObjItem *>(theItem);
		ThrowIfNil_(theRezObjItem);
		
		theDoc->RemoveResource(theRezObjItem);
	}
	
	// Note: the RemoveResource() function takes care of removing the
	// RezTypeItem itself from the map which causes this RezType to be
	// deleted.
}


// ---------------------------------------------------------------------------
//   HandlePickTypeEvent										 [public]
// ---------------------------------------------------------------------------

void
CRezType::HandlePickTypeEvent(
	const AppleEvent&	inAppleEvent,
	AppleEvent&			outAEReply,
	AEDesc&				outResult)
{
#pragma unused(inAppleEvent, outAEReply, outResult)
	
	if (  CPickersController::HasPickerForType(mType) == false) {
		ThrowOSErr_(err_NoPickerForType);
	} 
	
	// Find the corresponding RezTypeItem in the RezMap document
	CRezTypeItem *	theRezTypeItem = nil;
	CRezMapDoc *	theDoc = mOwnerMap->GetOwnerDoc();
	ThrowIfNil_(theDoc);

	// 'true' expands the RezTypeItem
	theRezTypeItem = theDoc->GetRezMapWindow()->GetRezMapTable()->GetRezTypeItem(mType, true);
	if (theRezTypeItem == NULL) {
		ThrowOSErr_(err_NoSuchTypeInMap);
	} 
	if (theDoc->TryOpenPicker(theRezTypeItem) == false) {
		ThrowOSErr_(err_OpenPickerFailed);		
	} 
	// Return an object specifier for the new picker in the reply
	CPickerDoc * thePicker = theDoc->GetTypePicker(mType);
	if (thePicker) {
		StAEDescriptor	elementDesc;
		thePicker->MakeSpecifier(elementDesc);
		UAEDesc::AddKeyDesc(&outAEReply, keyAEResult, elementDesc);
	} 

}


