// ===========================================================================
// CRezMapDocAE.cp
// 
//                       Created: 2005-04-09 10:03:39
//             Last modification: 2005-06-01 08:17:05
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
//  AppleEvent Object Model Support. These methods are part of the CRezMapDoc 
//  class (inheriting from LModelObject).

#include "CRezMap.h"
#include "CRezMapDoc.h"
#include "CRezFile.h"
#include "CEditorDoc.h"
#include "CRezMapWindow.h"
#include "UResources.h"
#include "RezillaConstants.h"

#include <LModelObject.h>
#include <LCommander.h>



// ---------------------------------------------------------------------------
//	¥ GetAEProperty
// ---------------------------------------------------------------------------
//	Return a descriptor for the specified Property
//	rzom_pReadOnly		= 'pRDO';	// mapReadOnly
// 	rzom_pRefNum		= 'pRFN';	// RefNum
// 	rzom_pRezFork		= 'pFRK';	// ResFork
// 	rzom_pRezFile		= 'pFIL';	// ResFile
//  pIndex				= 'pidx';
//  
// 	rzom_cRezMap and cWindow handled in GetModelProperty()

void
CRezMapDoc::GetAEProperty(
	DescType		inProperty,
	const AEDesc&	inRequestedType,
	AEDesc&			outPropertyDesc) const
{
	OSErr	error = noErr;
	
	switch (inProperty) {
		
		case rzom_pReadOnly:
		error = ::AECreateDesc(typeBoolean, (Ptr) &mReadOnly,
									sizeof(Boolean), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
		
		
		case pIndex: {
			// Return the index (first is 1) of this document among the other rezmap docs
			SInt32		position = GetAEPosition(this);
			if (position > 0) {
				error = ::AECreateDesc(typeSInt32, (Ptr) &position,
											sizeof(SInt32), &outPropertyDesc);
			} else {
				error = errAENoSuchObject;
			}
			ThrowIfOSErr_(error);
			break;
		}
		
		
		case rzom_pRefNum:
		short		theRefNum = mRezMap->GetRefnum();
		error = ::AECreateDesc(typeSInt16, (Ptr) &theRefNum,
									sizeof(short), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
		

		case rzom_pRezFork:
		ResType	theType = rzom_eIsUnknownFork;
		if (mFork == fork_rezfork) {
			theType = rzom_eIsRsrcFork;
		} else if (mFork == fork_datafork) {
			theType = rzom_eIsDataFork;
		} 
		error = ::AECreateDesc(typeEnumerated, (Ptr) &theType,
									sizeof(ResType), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
		
		
		case rzom_pRezFile:
		FSSpec theFSS = mRezFile->GetFileSpec();
		error = ::AECreateDesc(typeFSS, (Ptr) &theFSS,
									sizeof(FSSpec), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
		
		
		default:
		LDocument::GetAEProperty(inProperty, inRequestedType,
									outPropertyDesc);
		break;
	}
}


// ---------------------------------------------------------------------------
//	¥ SetAEProperty
// ---------------------------------------------------------------------------
// All the RezMapDoc properties are readOnly. Pass up to the LDocument 
// class.

void
CRezMapDoc::SetAEProperty(
	DescType		inProperty,
	const AEDesc&	inValue,
	AEDesc&			outAEReply)
{
	switch (inProperty) {				
		default:
			LDocument::SetAEProperty(inProperty, inValue, outAEReply);
			break;
	}
}


// ---------------------------------------------------------------------------
//	¥ AEPropertyExists
// ---------------------------------------------------------------------------

bool
CRezMapDoc::AEPropertyExists(
	DescType	inProperty) const
{
	bool	exists = false;

	switch (inProperty) {

		case cWindow:
		case pIndex:
		case rzom_pReadOnly:
		case rzom_pRefNum:
		case rzom_pRezFile:
		case rzom_pRezFork:
		case rzom_cRezMap: 
			exists = true;
			break;

		default:
			exists = LDocument::AEPropertyExists(inProperty);
			break;
	}

	return exists;
}


// ---------------------------------------------------------------------------
//	¥ GetAEPosition
// ---------------------------------------------------------------------------

SInt32
CRezMapDoc::GetAEPosition(const CRezMapDoc * inDoc) {
	SInt32	currPos = 0, result = 0;
	LDocument*	theDoc = nil;
	Boolean found = false;
	
	TArrayIterator<LDocument*> iterator( LDocument::GetDocumentList() );
	while (iterator.Next(theDoc)) {
		if (theDoc->GetModelKind() == rzom_cRezMapDoc) {
			currPos++;
			if (theDoc == inDoc) {
				result = currPos;
				break;
			} 
		} 				
		theDoc = nil;
	}

	return result;
}


// ---------------------------------------------------------------------------
//	¥ HandleAppleEvent												  [public]
// ---------------------------------------------------------------------------

void
CRezMapDoc::HandleAppleEvent(
	const AppleEvent&	inAppleEvent,
	AppleEvent&			outAEReply,
	AEDesc&				outResult,
	long				inAENumber)
{	
	switch (inAENumber) {
		
		case aeRzil_Export:
		HandleExportEvent(inAppleEvent, outAEReply, outResult);
		break;
				
		default:
		LDocument::HandleAppleEvent(inAppleEvent, outAEReply, outResult, inAENumber);
		break;
	}
}


// ---------------------------------------------------------------------------
//	¥ HandleExportEvent												  [public]
// ---------------------------------------------------------------------------

void
CRezMapDoc::HandleExportEvent(
	const AppleEvent&	inAppleEvent,
	AppleEvent&			outAEReply,
	AEDesc&				outResult)
{	
#pragma unused(outAEReply, outResult)
	
	OSErr		error, ignoreErr;
	DescType	returnedType;
	Size		actualSize;
	Size		theSize;
	FSSpec		fileSpec;
	ResType		theKind = 0;
	SInt16		saveFormat = mExportFormat;

	// Check for required "file" parameter
	error = ::AEGetParamPtr(&inAppleEvent, keyAEFile, typeFSS, &returnedType,
					&fileSpec, sizeof(FSSpec), &theSize);
	ThrowIfOSErr_(error);
	
	ignoreErr = ::AEGetParamPtr(&inAppleEvent, rzom_eEditorKind, typeEnumerated,
			&returnedType, &theKind, sizeof(ResType), &actualSize);

	// Map to the equivalent menu command
	switch (theKind) {
		case rzom_eExportXml:
		mExportFormat = exportMap_Xml;
		break;
		
		case rzom_eExportText:
		mExportFormat = exportMap_Text;
		break;
		
		case rzom_eExportHtml:
		mExportFormat = exportMap_Html;
		break;
		
		case rzom_eExportDerez:
		mExportFormat = cmd_HexEditRez;
		break;
		
		default:
		mExportFormat = exportMap_Derez;
		break;

	}
	
	DoExport(fileSpec);

	mExportFormat = saveFormat;
}


// ---------------------------------------------------------------------------
//	¥ GetSubModelByPosition											  [public]
// ---------------------------------------------------------------------------

void
CRezMapDoc::GetSubModelByPosition(
	DescType		inModelID,
	SInt32			inPosition,
	AEDesc&			outToken) const
{
	switch (inModelID) {

		case rzom_cEditorDoc:
		case cDocument: {
			CEditorDoc *	theDoc;			
			if ( mOpenedEditors->FetchItemAt( inPosition, theDoc) ) {
				PutInToken(theDoc, outToken);
			} else {
				ThrowOSErr_(errAENoSuchObject);
			}
			break;
		}

		case rzom_cGuiEditDoc:
		case rzom_cTmplEditDoc:
		case rzom_cHexEditDoc: {
			CEditorDoc *	theDoc = nil;
			Boolean		found = false;
			UInt16		count = 0;
			
			TArrayIterator<CEditorDoc *> iterEditor(*mOpenedEditors);
			while (iterEditor.Next(theDoc)) {
				if (theDoc != nil && theDoc->GetModelKind() == inModelID) {
					count++;
					if (count == inPosition) {
						found = true;
						break;
					} 
				} 
			}
			if (found) {
				PutInToken(theDoc, outToken);
			} else {
				ThrowOSErr_(errAENoSuchObject);
			}
			break;
		}

		case cWindow: 
		case rzom_cRezMapWindow: 
		if (inPosition == 1) {
			if (mRezMapWindow != nil) {
				PutInToken(mRezMapWindow, outToken);
			} else {
				ThrowOSErr_(errAENoSuchObject);
			}
			break;
		} 

		// Fall through...

		default:
			LModelObject::GetSubModelByPosition(inModelID, inPosition,
													outToken);
			break;
	}
}


// ---------------------------------------------------------------------------
//	¥ GetSubModelByName												  [public]
// ---------------------------------------------------------------------------
//	Pass back a token to a SubModel specified by name

void
CRezMapDoc::GetSubModelByName(
	DescType		inModelID,
	Str255			inName,
	AEDesc&			outToken) const
{
	switch (inModelID) {

		case rzom_cEditorDoc: 
		case rzom_cGuiEditDoc:
		case rzom_cTmplEditDoc:
		case rzom_cHexEditDoc: {
			TArrayIterator<CEditorDoc *> iterator(*mOpenedEditors);
			CEditorDoc *	theDoc = nil;
			while (iterator.Next(theDoc)) {
				DescType theKind = theDoc->GetModelKind();
				if (theKind == inModelID || inModelID == rzom_cEditorDoc) {
					Str255  docName;
					theDoc->GetDescriptor(docName);
					if (::IdenticalString(inName, docName, nil) == 0) {
						break;
					}
				}               
 				theDoc = nil;
			}
			if (theDoc != nil) {
				PutInToken(theDoc, outToken);
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
//	¥ GetModelProperty
// ---------------------------------------------------------------------------
//	Return a ModelObject object for 'cwin' and rzom_cRezMap properties

LModelObject*
CRezMapDoc::GetModelProperty(DescType inProperty) const
{
	LModelObject* theModelObject = nil;

	switch (inProperty) {

		case rzom_cRezMapWindow:
		case cWindow:
		theModelObject = dynamic_cast<LModelObject *>(mRezMapWindow);
		break;
		
		
		case rzom_cRezMap: 
		theModelObject = dynamic_cast<LModelObject *>(mRezMap);
		break;


		default:
		theModelObject = LModelObject::GetModelProperty(inProperty);
		break;
	}

	return theModelObject;
}


// ---------------------------------------------------------------------------
//	¥ GetModelTokenSelf
// ---------------------------------------------------------------------------
// This is a shortcut to do consider a resource directly as an object of the
// resource map document. It allows for AppleScript constructs like
//	    resource  {"TEXT", 128} of theDoc
//	instead of the more orthodox
//	    resource {"TEXT", 128} of map of theDoc

void
CRezMapDoc::GetModelTokenSelf(
	DescType		inModelID,
	DescType		inKeyForm,
	const AEDesc&	inKeyData,
	AEDesc&			outToken) const
{
	if (inModelID == rzom_cRezObj) {
		mRezMap->GetModelTokenSelf(inModelID, inKeyForm, inKeyData, outToken);
	} else {
		LModelObject::GetModelTokenSelf(inModelID, inKeyForm, inKeyData, outToken);
	}
}


