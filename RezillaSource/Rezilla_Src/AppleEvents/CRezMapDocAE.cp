// ===========================================================================
// CRezMapDocAE.cp
// 
//                       Created: 2005-04-09 10:03:39
//             Last modification: 2005-06-12 18:45:12
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// ===========================================================================
//  AppleEvent Object Model Support. These methods are part of the CRezMapDoc 
//  class (inheriting from LModelObject).

#include "CRezMap.h"
#include "CRezMapDoc.h"
#include "CRezFile.h"
#include "CRezObj.h"
#include "CRezObjItem.h"
#include "CEditorDoc.h"
#include "CEditorWindow.h"
#include "CRezMapWindow.h"
#include "UMiscUtils.h"
#include "UResources.h"
#include "RezillaConstants.h"

#include <LModelObject.h>
#include <LCommander.h>



// ---------------------------------------------------------------------------
//   GetAEProperty
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
	ResType	theType;
	
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
		
		
		case rzom_pRefNum: {
			short theRefNum = mRezMap->GetRefnum();
			error = ::AECreateDesc(typeSInt16, (Ptr) &theRefNum,
										sizeof(short), &outPropertyDesc);
			ThrowIfOSErr_(error);
			break;
		}
		
		case rzom_pRezFork:
		theType = rzom_eIsUnknownFork;
		if (mFork == fork_rezfork) {
			theType = rzom_eIsRsrcFork;
		} else if (mFork == fork_datafork) {
			theType = rzom_eIsDataFork;
		} 
		error = ::AECreateDesc(typeEnumerated, (Ptr) &theType,
									sizeof(ResType), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
		
		
		case rzom_pExportFormat:
		theType = rzom_eIsUnknownFork;
		switch (mExportFormat) {
			case exportMap_Xml:
			theType = rzom_eExportXml;
			break;
			
			case exportMap_Text:
			theType = rzom_eExportText;
			break;
			
			case exportMap_Html:
			theType = rzom_eExportHtml;
			break;
			
			case exportMap_Derez:
			theType = rzom_eExportDerez;
			break;
			
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
//   SetAEProperty
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
		
		case rzom_pExportFormat:
		ResType		formatType;
		
		ThrowIfOSErr_( ::AEGetDescData(&inValue, &formatType, sizeof(ResType)) );
		
		switch (formatType) {
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
			mExportFormat = exportMap_Derez;
			break;
		}
		break;
		
		default:
		LDocument::SetAEProperty(inProperty, inValue, outAEReply);
		break;
	}
}


// ---------------------------------------------------------------------------
//   AEPropertyExists
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
		case rzom_pExportFormat:
			exists = true;
			break;

		default:
			exists = LDocument::AEPropertyExists(inProperty);
			break;
	}

	return exists;
}


// ---------------------------------------------------------------------------
//   GetAEPosition
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
//   HandleAppleEvent												  [public]
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
//   HandleExportEvent												  [public]
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
	AERecord	theRecord;
	Size		actualSize;
	Size		theSize;
	FSSpec		folderSpec, fileSpec;
	ResType		theKind = 0;
	SInt16		saveFormat = mExportFormat;
	char		buffer[256];
	Str255		nameStr;

	// Check for required 'file' parameter
	error = ::AEGetParamPtr(&inAppleEvent, keyAEFile, typeFSS, &returnedType,
					&folderSpec, sizeof(FSSpec), &theSize);
	ThrowIfOSErr_(error);
	
	// Set a default for the name (RezillaExport)
	::GetIndString(nameStr, STRx_DefaultDocTitles, index_ExportUntitled);

	// Check for optional 'format' parameter
	ignoreErr = ::AEGetParamPtr(&inAppleEvent, kAERzilFormat, typeEnumerated,
			&returnedType, &theKind, sizeof(ResType), &actualSize);

	// Check for optional 'with properties' parameter. It is an AERecord.
	error = ::AECreateList(NULL, 0, true, &theRecord);
	ThrowIfOSErr_(error);
	ignoreErr = ::AEGetParamDesc(&inAppleEvent, keyAEPropData, typeAERecord, &theRecord);
	
	if (ignoreErr == noErr) {
		ignoreErr = ::AEGetParamPtr(&theRecord, rzom_pExportFormat, typeEnumerated,
				&returnedType, &theKind, sizeof(ResType), &actualSize);
		
		ignoreErr = ::AEGetParamPtr(&theRecord, keyAEName, typeChar,
				&returnedType, (Ptr) buffer, sizeof(buffer), &actualSize);
		if (ignoreErr == noErr) {
			buffer[actualSize] = 0;
			CopyCStringToPascal(buffer, nameStr);				 
		} 		
	} 
			
	// Map to the equivalent menu command
	switch (theKind) {
		case rzom_eExportText:
		mExportFormat = exportMap_Text;
		break;
		
		case rzom_eExportHtml:
		mExportFormat = exportMap_Html;
		break;
		
		case rzom_eExportDerez:
		mExportFormat = exportMap_Derez;
		break;
		
		case rzom_eExportXml:
		mExportFormat = exportMap_Xml;
		break;

		default:
		// In this case, use the current value of mExportFormat since it 
		// can be set by as a property with the "set data" AppleScript command.
		break;
}
	
	// Make a FSSpec for the export file
	HFileInfo	param;

	param.ioCompletion = 0L;
	param.ioNamePtr = folderSpec.name;
	param.ioVRefNum = folderSpec.vRefNum;
 	param.ioDirID = folderSpec.parID;
	param.ioFDirIndex = 0;
	error = ::PBGetCatInfoSync((CInfoPBPtr)&param);
	fileSpec.vRefNum = folderSpec.vRefNum;
	fileSpec.parID = param.ioDirID;
	BlockMoveData(nameStr, fileSpec.name, sizeof(FSSpec));
		
	// Delete an already existing file
	error = ::FSpDelete(&fileSpec);

	// Export the map
	DoExport(fileSpec);

	mExportFormat = saveFormat;
}


// ---------------------------------------------------------------------------
//   HandleAESave													  [public]
// ---------------------------------------------------------------------------
//	Respond to "Save" and "Save As" AppleEvents

void
CRezMapDoc::HandleAESave(
	const AppleEvent&	inSaveAE)
{
	OSErr		err;
	DescType	theType;
	ResType		forkType;
	SInt16		useFork = fork_samefork;
	Size		theSize;
	FSSpec		fileSpec;

	// Check for optional "in" parameter
	err = ::AEGetParamPtr(&inSaveAE, keyAEFile, typeFSS, &theType,
						&fileSpec, sizeof(FSSpec), &theSize);

	bool	hasFileParameter = (err == noErr);

	// Check for optional "as" parameter telling in which fork to save 
	// (honored only in Save As operations)
	err = ::AEGetParamPtr(&inSaveAE, keyAEFileType, typeEnumerated,
						&theType, &forkType, sizeof(ResType), &theSize);
	
	if (err == noErr) {
		switch (forkType) {
			case rzom_eRsrcFork:
			useFork = fork_rezfork;
			break;
			
			case rzom_eDataFork:
			useFork = fork_datafork;
			break;	
		}
	} 
						
	if (hasFileParameter) {
		// Save using file from event
		DoAESave(fileSpec, useFork);
	} else  {
		// Save using existing file
		DoSave();	
	} 
}


// ---------------------------------------------------------------------------
//   HandleCreateElementEvent
// ---------------------------------------------------------------------------
// This function handles the "make new" event in order to create a new
// resource in the map document. Properties can be set using the "with
// properties" parameter. Thus one can write in AppleScript:
//   make new resource of map document 1 with properties {type:"TEXT", ID:129, attributes:8}
//   
// If the ID is not specified, an unique ID is attributed. If it already 
// exists, the event fails in order to rpeserve existing resources. If no 
// type is specified, a 'TEXT' resource is created
//  
// The optional "with data" parameter is also supported. For instance:
//   make new resource of map document 1 with data "Hello Rezilla!"
//   
// The inTargetObject argument contains "this". 

LModelObject*
CRezMapDoc::HandleCreateElementEvent(
	DescType			inElemClass,
	DescType			inInsertPosition,
	LModelObject*		inTargetObject,
	const AppleEvent&	inAppleEvent,
	AppleEvent&			outAEReply)
{
#pragma unused (inInsertPosition, inTargetObject)
	
	OSErr 			ignoreErr;
	AEDesc			propDesc;
	OSType			theType;
	SInt16			theID = 0, theAttrs;
	Str255			typeStr, nameStr;
	Boolean			setFlag = false, gotID = false;
	CRezObj *		rezObj;
	CRezObjItem *	rezObjItem;

	if (inElemClass != rzom_cRezObj) {
		ThrowOSErr_(errAEUnknownObjectType);
	} 
	
	// Set some defaults
	nameStr[0] = 0;
	theType = ResType_Text;
	theAttrs = 0;
	
	// Extract the "with properties" parameter which possibly contains property
	// values in an AERecord.
	ignoreErr = ::AEGetParamDesc(&inAppleEvent, keyAEPropData, typeAERecord, &propDesc);

	if (ignoreErr == noErr) {
		// Parse the record
		SInt32		i, count = 0;
		
		ignoreErr = ::AECountItems(&propDesc, &count);

		if (ignoreErr == noErr) {
			short	flag = 0;
			
			for (i = 1; i <= count; i++) {
				AEKeyword		theKey;
				StAEDescriptor	subDesc;
				
				ignoreErr = ::AEGetNthDesc(&propDesc, i, typeWildCard, &theKey, &subDesc.mDesc);
				
				// Look for "ID", "type", "name", "attributes", "locked",
				// "preload", "protected", "purgeable", "sysHeap" keywords
				switch (theKey) {
					case rzom_pResID:
					UExtractFromAEDesc::TheSInt16(subDesc.mDesc, theID);
					gotID = true;
					break;
					
					case rzom_cRezType:
					case rzom_pType:
					UExtractFromAEDesc::ThePString(subDesc.mDesc, typeStr, sizeof(typeStr));
					UMiscUtils::PStringToOSType(typeStr, theType);
					break;
					
					case pName: 
					UExtractFromAEDesc::ThePString(subDesc.mDesc, nameStr, sizeof(nameStr));
					break;

					case rzom_pAttributes:
					UExtractFromAEDesc::TheSInt16(subDesc.mDesc, theAttrs);
					break;
					
					case rzom_pSysHeap:
					UExtractFromAEDesc::TheBoolean(subDesc.mDesc, setFlag);
					flag = resSysHeap;
					break;
					
					case rzom_pPurgeable:
					UExtractFromAEDesc::TheBoolean(subDesc.mDesc, setFlag);
					flag = resPurgeable;
					break;
					
					case rzom_pLocked:
					UExtractFromAEDesc::TheBoolean(subDesc.mDesc, setFlag);
					flag = resLocked;
					break;
					
					case rzom_pProtected:
					UExtractFromAEDesc::TheBoolean(subDesc.mDesc, setFlag);
					flag = resProtected;
					break;
					
					case rzom_pPreload:
					UExtractFromAEDesc::TheBoolean(subDesc.mDesc, setFlag);
					flag = resPreload;
					break;
					
				}
				
				if (flag) {
					if (setFlag) {
						theAttrs |= flag;
					} else {
						theAttrs &= ~flag;
					}
					flag = 0;
				} 
			}
		}

		if (propDesc.descriptorType != typeNull) ::AEDisposeDesc(&propDesc);
	} 

	if (!gotID) {
		mRezMap->UniqueID(theType, theID);
	} else if ( mRezMap->HasResourceWithTypeAndId(theType, theID) ) {
		// The AE must fail if the ID already exists
		ThrowOSErr_(err_AlreadyExistingID);
	}
	
	// Create the new resource
	rezObjItem = DoCreateResource(theType, theID, &nameStr, theAttrs, false);
	ThrowIfNil_(rezObjItem);
	
	SetModified(true);
	rezObj = rezObjItem->GetRezObj();
	rezObj->SetAttributesInMap(theAttrs);
	
	// Look for a "with data" parameter containing initial data for the resource
	AEDesc	valueDesc;
	ignoreErr = AEGetParamDesc(&inAppleEvent, keyAEData, typeWildCard, &valueDesc);
	if (ignoreErr == noErr) {
		rezObj->SetAEResourceData(valueDesc);
	} 
	if (valueDesc.descriptorType != typeNull) ::AEDisposeDesc(&valueDesc);
	
	// An object specifier for the new element must be returned as the
	// keyAEResult parameter of the reply
	StAEDescriptor	elementDesc;
	rezObj->MakeSpecifier(elementDesc);
	UAEDesc::AddKeyDesc(&outAEReply, keyAEResult, elementDesc);
	
	// Return nil otherwise LModelDirector::HandleCreateElementEvent will 
	// also write to the reply
	return (LModelObject *) NULL;
}


// ---------------------------------------------------------------------------
//   GetSubModelByPosition											  [public]
// ---------------------------------------------------------------------------
// As a shortcut one can write
//   get editing window 1 of map document 1
// instead of 
//   get window of editor 1 of map document 1
// Similarly
//   get hexadecimal window 1 of map document 1
// is equivalent to
//   get window of hexadecimal editor 1 of map document 1

void
CRezMapDoc::GetSubModelByPosition(
	DescType		inModelID,
	SInt32			inPosition,
	AEDesc&			outToken) const
{
	Boolean			found = false;
	UInt16			count = 0;
	WindowPtr		windowP = ::GetWindowList();
	LWindow*		ppWindow = nil;
	CEditorDoc *	theDoc = nil;

	switch (inModelID) {

		case rzom_cEditorDoc:
		case cDocument:
		case rzom_cEditorWindow: {
			if ( mOpenedEditors->FetchItemAt( inPosition, theDoc) ) {
				if (inModelID == rzom_cEditorWindow) {
					PutInToken(theDoc->GetMainWindow(), outToken);
				} else {
					PutInToken(theDoc, outToken);
				}
			} else {
				ThrowOSErr_(errAENoSuchObject);
			}
			break;
		}

		
		case rzom_cHexEditDoc:
		case rzom_cTmplEditDoc:
		case rzom_cGuiEditDoc:
		case rzom_cHexWindow: 
		case rzom_cTmplWindow:
		case rzom_cGuiWindow: {
			DescType docKind = inModelID;
			switch (inModelID) {
				case rzom_cHexWindow: 
				docKind = rzom_cHexEditDoc;
				break;
				
				case rzom_cTmplWindow:
				docKind = rzom_cTmplEditDoc;
				break;
				
				case rzom_cGuiWindow:
				docKind = rzom_cGuiEditDoc;
				break;
			}
			
			TArrayIterator<CEditorDoc *> iterEditor(*mOpenedEditors);
			while (iterEditor.Next(theDoc)) {
				if (theDoc != nil && theDoc->GetModelKind() == docKind) {
					count++;
					if (count == inPosition) {
						found = true;
						break;
					} 
				} 
			}
			if (found) {
				if (inModelID == rzom_cHexWindow 
					|| inModelID == rzom_cTmplWindow 
					|| inModelID == rzom_cGuiWindow) {
					PutInToken(theDoc->GetMainWindow(), outToken);
				} else {
					PutInToken(theDoc, outToken);
				}
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
//   GetSubModelByName												  [public]
// ---------------------------------------------------------------------------
// As a shortcut one can write
//   get editing window "somename" of map document 1
// instead of 
//   get window of editor "somename" of map document 1
// Similarly
//   get hexadecimal window "somename" of map document 1
// is equivalent to
//   get window of hexadecimal editor "somename" of map document 1

void
CRezMapDoc::GetSubModelByName(
	DescType		inModelID,
	Str255			inName,
	AEDesc&			outToken) const
{
	switch (inModelID) {

		case rzom_cEditorDoc:
		case rzom_cHexEditDoc:
		case rzom_cTmplEditDoc:
		case rzom_cGuiEditDoc:
		case rzom_cEditorWindow:
		case rzom_cHexWindow: 
		case rzom_cTmplWindow:
		case rzom_cGuiWindow: {
			DescType docKind = inModelID;
			switch (inModelID) {
				case rzom_cHexWindow: 
				docKind = rzom_cHexEditDoc;
				break;
				
				case rzom_cTmplWindow:
				docKind = rzom_cTmplEditDoc;
				break;
				
				case rzom_cGuiWindow:
				docKind = rzom_cGuiEditDoc;
				break;
			}
			
			TArrayIterator<CEditorDoc *> iterator(*mOpenedEditors);
			CEditorDoc *	theDoc = nil;
			while (iterator.Next(theDoc)) {
				DescType theKind = theDoc->GetModelKind();
				if (theKind == docKind || inModelID == rzom_cEditorDoc || inModelID == rzom_cEditorWindow) {
					Str255  docName;
					theDoc->GetDescriptor(docName);
					if (::IdenticalString(inName, docName, nil) == 0) {
						break;
					}
				}               
 				theDoc = nil;
			}
			if (theDoc != nil) {
				if (inModelID == rzom_cEditorDoc 
					|| inModelID == rzom_cHexEditDoc
					|| inModelID == rzom_cTmplEditDoc 
					|| inModelID == rzom_cGuiEditDoc) {
					PutInToken(theDoc, outToken);
				} else {
					PutInToken(theDoc->GetMainWindow(), outToken);
				}
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
//   GetPositionOfSubModel
// ---------------------------------------------------------------------------

SInt32
CRezMapDoc::GetPositionOfSubModel(
	DescType			inModelID,
	const LModelObject	*inSubModel) const
{
	SInt32	position = 0;
	WindowPtr	windowP = ::GetWindowList();
	LWindow*	ppWindow = nil;
	UInt16		count = 0;

	switch (inModelID) {
		case rzom_cHexWindow: 
		case rzom_cTmplWindow:
		case rzom_cGuiWindow: {
			while (windowP) {
				ppWindow = LWindow::FetchWindowObject(windowP);
				
				if (ppWindow != nil && ppWindow->GetModelKind() == inModelID) {
					count++;
					if (ppWindow == inSubModel) {
						position = count;
						break;
					} 
				} 
				windowP = MacGetNextWindow(windowP);
			}

			if (position == 0) {
				ThrowOSErr_(errAENoSuchObject);
			}
			break;
		}

		case rzom_cEditorWindow: {
			DescType	theKind;
			while (windowP) {
				ppWindow = LWindow::FetchWindowObject(windowP);
				
				if (ppWindow != nil) {
					theKind = ppWindow->GetModelKind();
					if (ppWindow != nil && (theKind == inModelID
						|| theKind == rzom_cHexWindow
						|| theKind == rzom_cTmplWindow
						|| theKind == rzom_cGuiWindow) ) {
						count++;
						if (ppWindow == inSubModel) {
							position = count;
							break;
						} 
					} 
				} 
				windowP = MacGetNextWindow(windowP);
			}

			if (position == 0) {
				ThrowOSErr_(errAENoSuchObject);
			}
			break;
		}

		default:
			position = LModelObject::GetPositionOfSubModel(inModelID, inSubModel);
			break;
	}

	return position;
}


// ---------------------------------------------------------------------------
//   CountSubModels											  [public]
// ---------------------------------------------------------------------------

SInt32
CRezMapDoc::CountSubModels(
	DescType	inModelID) const
{
	SInt32	count = 0;

	switch (inModelID) {

		case rzom_cEditorDoc:
		case cDocument: 
		count = (SInt32) mOpenedEditors->GetCount();
		break;

		case rzom_cGuiEditDoc:
		case rzom_cTmplEditDoc:
		case rzom_cHexEditDoc: {
			CEditorDoc *	theDoc = nil;
			
			TArrayIterator<CEditorDoc *> iterEditor(*mOpenedEditors);
			while (iterEditor.Next(theDoc)) {
				if (theDoc != nil && theDoc->GetModelKind() == inModelID) {
					count++;
				} 
			}
			break;
		}

		default:
			LModelObject::CountSubModels(inModelID);
			break;
	}
	
	return count;
}


// ---------------------------------------------------------------------------
//   GetModelProperty
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
//   GetModelTokenSelf
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


