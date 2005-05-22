// ===========================================================================
// CRezillaAppAE.cp					
//                       Created: 2004-11-30 08:44:17
//             Last modification: 2005-05-20 06:18:06
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CRezillaApp.h"
#include "CRezMapDoc.h"
#include "CRezMap.h"
#include "CRezCompare.h"
#include "CRezFile.h"
#include "CInspectorWindow.h"
#include "CHexEditorWindow.h"
#include "CTmplEditorWindow.h"
#include "CCompResultWindow.h"
#include "CTEXT_EditorView.h"
#include "CRecentItemsMenu.h"
#include "UMessageDialogs.h"
#include "UDialogBoxHandler.h"


// PP Classes for registration
#include <LFile.h>
#include <LWindow.h>
#include <LWindowHeader.h>
#include <LDocument.h>
#include <UExtractFromAEDesc.h>


// Standard headers
#include <string.h>

// Universal headers
#include <AppleHelp.h>


// ---------------------------------------------------------------------------
//	¥ HandleAppleEvent												  [public]
// ---------------------------------------------------------------------------

void
CRezillaApp::HandleAppleEvent(
	const AppleEvent&	inAppleEvent,
	AppleEvent&			outAEReply,
	AEDesc&				outResult,
	long				inAENumber)
{	
	sCalledFromAE = true;

	switch (inAENumber) {
		
		case ae_OpenDoc:
		HandleOpenDocsEvent(inAppleEvent, outAEReply, outResult);
		break;
		
		case aeRzil_Compare:
		HandleCompareMapsEvent(inAppleEvent, outAEReply, outResult);
		break;
		
		case ae_ApplicationDied:
		break;
		
		default:
		LApplication::HandleAppleEvent(inAppleEvent, outAEReply, outResult, inAENumber);
		break;
	}

	sCalledFromAE = false;
}


// ---------------------------------------------------------------------------
//	¥ HandleOpenDocsEvent											  [public]
// ---------------------------------------------------------------------------
// err = AEPutParamDesc(outReply, keyErrorString, &param);

void
CRezillaApp::HandleOpenDocsEvent(
	const AppleEvent&	inAppleEvent,
	AppleEvent&			outAEReply,
	AEDesc&				outResult)
{
#pragma unused( outResult )

	OSErr			error;
	AEDescList		theDocList, errorList;
	AEKeyword		theKey;
	DescType		theType;
	FSSpec			theFileSpec;
	Size			theSize;
	SInt32			numDocs, errCount = 0;
	
	error = ::AEGetParamDesc(&inAppleEvent, keyDirectObject,
							 typeAEList, &theDocList);
	ThrowIfOSErr_(error);
	error = ::AECountItems(&theDocList, &numDocs);
	ThrowIfOSErr_(error);
	
	::AECreateList(NULL, 0, false, &errorList);
	
	for ( UInt16 i = 1; i <= numDocs; i++ ) {
	    error = ::AEGetNthPtr(&theDocList, i, typeFSS, &theKey, &theType,
						      (Ptr) &theFileSpec, sizeof(FSSpec), &theSize);
	    ThrowIfOSErr_(error);
		
		sReadOnlyNavFlag = false;
		error = OpenFork(theFileSpec);
		if (error == noErr) {
			// Register to the Recent Items menu
			sRecentItemsAttachment->AddFile(theFileSpec, true);
		} else {
			errCount++;
			error = ::AEPutPtr(&errorList, errCount, typeFSS, (Ptr) &theFileSpec, sizeof(FSSpec)) ;
		}
	}
	
	if (errCount > 0) {
		CFStringRef messageStr = NULL;
		Str255   buffer;

		error = err_OpenDocsAEFailed;
		messageStr = ::CFCopyLocalizedString(CFSTR("AevtOdocError"), NULL);
		if (messageStr != NULL) {
			if (::CFStringGetPascalString(messageStr, buffer, sizeof(buffer), ::GetApplicationTextEncoding())) {
				::AEPutParamPtr(&outAEReply, keyErrorString, typeChar, buffer+1, buffer[0]);
			}
		}
		// OSErr is SInt16
		::AEPutParamPtr(&outAEReply, keyErrorNumber, typeSInt16, &error, sizeof(OSErr));
		::AEPutParamDesc(&outAEReply, kAERzilFilesList, &errorList);
	} 

	if (theDocList.descriptorType != typeNull) ::AEDisposeDesc(&theDocList);
	if (errorList.descriptorType != typeNull) ::AEDisposeDesc(&errorList);
}


// ---------------------------------------------------------------------------
//	¥ HandleCompareMapsEvent										  [public]
// ---------------------------------------------------------------------------

void
CRezillaApp::HandleCompareMapsEvent(
	const AppleEvent&	inAppleEvent,
	AppleEvent&			outAEReply,
	AEDesc&				outResult)
{
#pragma unused( outResult )

	OSErr			error, ignoreErr;
	DescType		returnedType;
	FSSpec			theFSSpec1, theFSSpec2;
	Size			actualSize;
	Boolean 		theBool, oldIgnoreNames, oldIgnoreAttrs, oldIgnoreData;
	
	oldIgnoreNames = CRezCompare::GetIgnoreNames();
	oldIgnoreAttrs = CRezCompare::GetIgnoreAttrs();
	oldIgnoreData = CRezCompare::GetIgnoreData();
	
	// Extract the direct parameter: first file for comparison
	error = ::AEGetParamPtr(&inAppleEvent, keyDirectObject, typeFSS,
						  &returnedType, &theFSSpec1, sizeof(FSSpec), &actualSize);
	ThrowIfOSErr_(error);
	
	// Extract the "and" parameter (kAERzilCompareWith): second file for comparison
	error = ::AEGetParamPtr(&inAppleEvent, kAERzilCompareWith, typeFSS,
						  &returnedType, &theFSSpec2, sizeof(FSSpec), &actualSize);
	ThrowIfOSErr_(error);
	
	// Extract optional comparison criteria. If they have not been
	// specified in the AE, defaults will be true for sIgnoreNames and
	// sIgnoreAttrs, and false for sIgnoreData.
	ignoreErr = ::AEGetParamPtr(&inAppleEvent, rzom_pIgnoreName, typeBoolean,
							  &returnedType, &theBool, sizeof(Boolean), &actualSize);
	if (noErr == ignoreErr) {
		CRezCompare::SetIgnoreNames(theBool);
	} else {
		CRezCompare::SetIgnoreNames(true);
	}
	
	ignoreErr = ::AEGetParamPtr(&inAppleEvent, rzom_pIgnoreAttrs, typeBoolean,
							  &returnedType, &theBool, sizeof(Boolean), &actualSize);
	if (noErr == ignoreErr) {
		CRezCompare::SetIgnoreAttrs(theBool);
	} else {
		CRezCompare::SetIgnoreAttrs(true);
	}
	
	ignoreErr = ::AEGetParamPtr(&inAppleEvent, rzom_pIgnoreData, typeBoolean,
							  &returnedType, &theBool, sizeof(Boolean), &actualSize);
	if (noErr == ignoreErr) {
		CRezCompare::SetIgnoreData(theBool);
	} else {
		CRezCompare::SetIgnoreData(false);
	}
	
	CRezCompare * theComparator = new CRezCompare(this, theFSSpec1, theFSSpec2);
	ThrowIfNil_(theComparator);

	try {
		theComparator->DoCompareRezMaps();
	}
	catch (...) {
		CRezCompare::SetIgnoreNames(oldIgnoreNames);
		CRezCompare::SetIgnoreAttrs(oldIgnoreAttrs);
		CRezCompare::SetIgnoreData(oldIgnoreData);
		delete theComparator;
		return;
	}
	
	if (theComparator->HasDifferences()) {
		StAEDescriptor	repDesc;
		theComparator->DisplayResults();
		theComparator->MakeSpecifier(repDesc);
		::AEPutParamDesc(&outAEReply, keyDirectObject, (const AEDesc *)&repDesc);
	} else {
		CFStringRef messageStr = NULL;
		Str255   buffer;

		messageStr = ::CFCopyLocalizedString(CFSTR("RezMapsDoNotDiffer"), NULL);
		if (messageStr != NULL) {
			if (::CFStringGetPascalString(messageStr, buffer, sizeof(buffer), ::GetApplicationTextEncoding())) {
				::AEPutParamPtr(&outAEReply, keyErrorString, typeChar, buffer+1, buffer[0]);
			}
		}

		delete theComparator;
	}

	CRezCompare::SetIgnoreNames(oldIgnoreNames);
	CRezCompare::SetIgnoreAttrs(oldIgnoreAttrs);
	CRezCompare::SetIgnoreData(oldIgnoreData);
	
}


// ---------------------------------------------------------------------------
//	¥ HandleCreateElementEvent
// ---------------------------------------------------------------------------

LModelObject*
CRezillaApp::HandleCreateElementEvent(
	DescType			inElemClass,
	DescType			inInsertPosition,
	LModelObject*		inTargetObject,
	const AppleEvent&	inAppleEvent,
	AppleEvent&			outAEReply)
{
#pragma unused (inInsertPosition, inTargetObject, outAEReply)
	
	OSErr 			error, ignoreErr;
	AEDesc			propDesc;
	DescType		returnedType;
	Size			actualSize;
	FSSpec			theFSSpec;
	OSType			theCode;
	Boolean			isReadOnly = false;
	SInt16			theFork = fork_datafork;
	CRezMapDoc *	rezMapDoc;

	if (inElemClass != rzom_cRezMapDoc && inElemClass != rzom_cRezMapWindow) {
		ThrowOSErr_(errAEUnknownObjectType);
	} 
	
	// Extract the "with properties" parameter which contains property
	// values in an AERecord. Here, this parameter is required because it
	// must contain the FSSpec for the new resource map.
	error = ::AEGetParamDesc(&inAppleEvent, keyAEPropData, typeAERecord, &propDesc);
	ThrowIfOSErr_(error);

	// Look for "file", "readOnly", "fork" keywords (resp. rzom_pRezFile, 
	// rzom_pReadOnly, rzom_pRezFork)
	error = ::AEGetParamPtr(&inAppleEvent, rzom_pRezFile, typeFSS, &returnedType,
								&theFSSpec, sizeof(FSSpec), &actualSize);
	ThrowIfOSErr_(error);

	ignoreErr = ::AEGetParamPtr(&inAppleEvent, rzom_pRezFork, typeEnumerated, &returnedType,
								&theCode, sizeof(OSType), &actualSize);
	if (ignoreErr == noErr && theCode == rzom_eRsrcFork) {
			theFork = fork_rezfork;			
	} 

	ignoreErr = ::AEGetParamPtr(&inAppleEvent, rzom_pReadOnly, typeBoolean, &returnedType,
								&isReadOnly, sizeof(Boolean), &actualSize);

	// Make a new file object.
	CRezFile * theRezFile = new CRezFile(theFSSpec, kResFileNotOpened, theFork);
	ThrowIfNil_(theRezFile);

	// Make new resource file on disk
	if (theRezFile->CreateNewFile() == noErr) {
		// Open the resource file.
		theRezFile->OpenFile(fsRdWrPerm);
	}
	rezMapDoc = new CRezMapDoc(this, theRezFile);
	ThrowIfNil_(rezMapDoc);

	rezMapDoc->SetReadOnly(isReadOnly);	
	
	return (LModelObject *) rezMapDoc;
}


// ---------------------------------------------------------------------------
//	¥ CountSubModels												  [public]
// ---------------------------------------------------------------------------

SInt32
CRezillaApp::CountSubModels(
	DescType	inModelID) const
{
	SInt32		count = 0;
	DescType	theKind;
	WindowPtr	windowP;
	LWindow *	theWindow;
	LDocument*	theDoc;
	
	switch (inModelID) {

		case cWindow:
		count = LApplication::CountSubModels(inModelID);
		break;
		
		
		case rzom_cEditorWindow: {
			windowP = ::GetWindowList();
			while (windowP != nil) {
				theWindow = LWindow::FetchWindowObject(windowP);
				if (theWindow != nil) {
					theKind = theWindow->GetModelKind();
					if (theKind == inModelID 
						|| theKind == rzom_cGuiWindow 
						|| theKind == rzom_cTmplWindow 
						|| theKind == rzom_cHexWindow) {
						count++;
					} 
				} 
				windowP = ::MacGetNextWindow(windowP);
			}
			break;
		}

		
		case rzom_cRezMapWindow:
		case rzom_cGuiWindow:
		case rzom_cTmplWindow:
		case rzom_cHexWindow:
		case rzom_cCompWindow: {
			windowP = ::GetWindowList();
			while (windowP != nil) {
				theWindow = LWindow::FetchWindowObject(windowP);
				if (theWindow != nil && theWindow->GetModelKind() == inModelID) {
					count++;
				} 
				windowP = ::MacGetNextWindow(windowP);
			}
			break;
		}
		

		case cDocument:
			count = (SInt32) LDocument::GetDocumentList().GetCount();
			break;


		case rzom_cRezMap:
			count = (SInt32) CRezMap::GetRezMapList().GetCount();
			break;


		case rzom_cEditorDoc: {		
			TArrayIterator<LDocument*> iterEditor( LDocument::GetDocumentList() );
			theDoc = nil;
			while (iterEditor.Next(theDoc)) {
				if (theDoc != nil) {
					theKind = theDoc->GetModelKind();
					if (theKind == inModelID 
						|| theKind == rzom_cHexEditDoc 
						|| theKind == rzom_cTmplEditDoc 
						|| theKind == rzom_cGuiEditDoc) {
						count++;
					} 
				} 
			}
			break;
		}


		case rzom_cRezMapDoc:
		case rzom_cGuiEditDoc:
		case rzom_cTmplEditDoc:
		case rzom_cHexEditDoc: {
			TArrayIterator<LDocument*> iterDoc( LDocument::GetDocumentList() );
			theDoc = nil;
			while (iterDoc.Next(theDoc)) {
				if (theDoc && theDoc->GetModelKind() == inModelID) {
					count++;
				} 
			}
			break;
		}
		

		default:
			count = LModelObject::CountSubModels(inModelID);
			break;
	}

	return count;
}


// ---------------------------------------------------------------------------
//	¥ GetSubModelByPosition											  [public]
// ---------------------------------------------------------------------------

void
CRezillaApp::GetSubModelByPosition(
	DescType		inModelID,
	SInt32			inPosition,
	AEDesc&			outToken) const
{
	switch (inModelID) {

		case cWindow: {
			WindowPtr	windowP = UWindows::FindNthWindow((SInt16) inPosition);
			if (windowP != nil) {
				PutInToken(LWindow::FetchWindowObject(windowP), outToken);
			} else {
				ThrowOSErr_(errAENoSuchObject);
			}
			break;
		}

		case cDocument: {
			LDocument *	theDoc = nil;
			if ( LDocument::GetDocumentList().FetchItemAt( inPosition, theDoc) ) {
				PutInToken(theDoc, outToken);
			} else {
				ThrowOSErr_(errAENoSuchObject);
			}
			break;
		}

		case rzom_cRezMap: {
			CRezMap *	theMap = nil;
			if ( CRezMap::GetRezMapList().FetchItemAt( inPosition, theMap) ) {
				PutInToken(theMap, outToken);
			} else {
				ThrowOSErr_(errAENoSuchObject);
			}
			break;
		}

		case rzom_cRezMapDoc: {
			LDocument *	theDoc = nil;
			Boolean		found = false;
			UInt16		count = 0;
			
			TArrayIterator<LDocument*> iterEditor( LDocument::GetDocumentList() );
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

		case rzom_cCompWindow: 
		case rzom_cMapsComp: {
			WindowPtr	windowP;
			LWindow*	ppWindow = nil;
			CCompResultWindow * compWindow;
			Boolean		found = false;
			UInt16		count = 0;
	
			windowP = ::GetWindowList();
			while (windowP) {
				ppWindow = LWindow::FetchWindowObject(windowP);
				
				if (ppWindow != nil && ppWindow->GetModelKind() == rzom_cCompWindow) {
					count++;
					if (count == inPosition) {
						compWindow = dynamic_cast<CCompResultWindow*>(ppWindow);
						found = true;
						break;
					} 
				} 
				windowP = MacGetNextWindow(windowP);
			}

			if (found == true && compWindow != nil) {
				if (inModelID == rzom_cMapsComp) {
					PutInToken( compWindow->GetRezCompare(), outToken);
				} else {
					PutInToken( compWindow, outToken);
				}
			} else {
				ThrowOSErr_(errAENoSuchObject);
			}
			break;
		}

		
		case rzom_cInspWindow:
		PutInToken( sInspectorWindow, outToken);
		break;
		
		
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
CRezillaApp::GetSubModelByName(
	DescType		inModelID,
	Str255			inName,
	AEDesc&			outToken) const
{
	switch (inModelID) {

		case cWindow: {
			WindowPtr	windowP = UWindows::FindNamedWindow(inName);
			if (windowP != nil) {
				PutInToken(LWindow::FetchWindowObject(windowP), outToken);
			} else {
				ThrowOSErr_(errAENoSuchObject);
			}
			break;
		}

		case cDocument: {
			LDocument *	theDoc = LDocument::FindNamedDocument(inName);
			if (theDoc != nil) {
				PutInToken(theDoc, outToken);
			} else {
				ThrowOSErr_(errAENoSuchObject);
			}
			break;
		}

		case rzom_cRezMapDoc: {
			TArrayIterator<LDocument*> iterator( LDocument::GetDocumentList() );
			LDocument*	theDoc = nil;
			while (iterator.Next(theDoc)) {
				if (theDoc->GetModelKind() == inModelID) {
					Str255	docName;
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
//   ¥ GetSubModelByUniqueID
// ---------------------------------------------------------------------------
//   Pass back a Token for the SubModel of the specified type with the
//   specified unique ID

void
CRezillaApp::GetSubModelByUniqueID(
				 DescType        inModelID,
				 const AEDesc    &inKeyData,
				 AEDesc          &outToken) const
{
	if (inModelID == rzom_cRezMap) {
		SInt32 uniqueID;
		Boolean found = false;

		ThrowIfOSErr_( ::AEGetDescData(&inKeyData, &uniqueID, sizeof(uniqueID)) );

		TArrayIterator<CRezMapDoc*> iterator( CRezMapDoc::GetRezMapDocList() );
		CRezMapDoc *	rezmapDoc = nil;

		while (iterator.Next(rezmapDoc)) {
			if (rezmapDoc != nil && rezmapDoc->GetRezMap()->GetRefnum() == uniqueID) {
				found = true;
				break;
			}
			rezmapDoc = nil;
		}

		if (found) {
		   PutInToken(rezmapDoc->GetRezMap(), outToken);
		   return;
		} else {
			ThrowOSErr_(errAENoSuchObject);
		}
	}
}


// ---------------------------------------------------------------------------
//	¥ GetPositionOfSubModel											  [public]
// ---------------------------------------------------------------------------
//	Return the position (1 = first) of a SubModel within an Application

SInt32
CRezillaApp::GetPositionOfSubModel(
	DescType				inModelID,
	const LModelObject*		inSubModel) const
{
	SInt32	position = 0;

	switch (inModelID) {

		case rzom_cCompWindow: 
		case rzom_cMapsComp: {
			WindowPtr	windowP = ::GetWindowList();
			LWindow*	ppWindow = nil;
			UInt16		count = 0;
	
			while (windowP) {
				ppWindow = LWindow::FetchWindowObject(windowP);
				
				if (ppWindow != nil && ppWindow->GetModelKind() == rzom_cCompWindow) {
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


		default:
			position = LApplication::GetPositionOfSubModel(inModelID, inSubModel);
			break;
	}

	return position;
}



// ---------------------------------------------------------------------------
//	¥ GetAEProperty
// ---------------------------------------------------------------------------
//	Return a descriptor for the specified Property

void
CRezillaApp::GetAEProperty(
	DescType		inProperty,
	const AEDesc&	inRequestedType,
	AEDesc&			outPropertyDesc) const
{
	OSErr		error = noErr;

	switch (inProperty) {
		case pVersion: 
		error = ::AECreateDesc(typeChar, (Ptr) sVersionNumber + 1, sVersionNumber[0], &outPropertyDesc);
		break;

		// Handled in GetModelProperty
		// 		case rzom_pInspector: 
		// 		break;

		default:
		LModelObject::GetAEProperty(inProperty, inRequestedType, outPropertyDesc);
		break;
	}
}


// ---------------------------------------------------------------------------
//	¥ AEPropertyExists
// ---------------------------------------------------------------------------

bool
CRezillaApp::AEPropertyExists(
	DescType	inProperty) const
{
	bool	exists = false;

	switch (inProperty) {
		case pVersion: 
		case rzom_pInspector: 
			exists = true;
			break;

		default:
			exists = LApplication::AEPropertyExists(inProperty);
			break;
	}

	return exists;
}


// ---------------------------------------------------------------------------
//	¥ GetModelProperty
// ---------------------------------------------------------------------------

LModelObject*
CRezillaApp::GetModelProperty(DescType inProperty) const
{
	LModelObject* theModelObject = nil;

	switch (inProperty) {

		case rzom_pInspector:
		theModelObject = dynamic_cast<LModelObject *>(sInspectorWindow);
		break;
		

		default:
		theModelObject = LModelObject::GetModelProperty(inProperty);
			break;
	}

	return theModelObject;
}


