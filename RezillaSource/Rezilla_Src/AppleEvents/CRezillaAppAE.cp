// ===========================================================================
// CRezillaAppAE.cp					
//                       Created: 2004-11-30 08:44:17
//             Last modification: 2005-04-11 09:34:19
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2004, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#include "CRezillaApp.h"
#include "CRezMapDoc.h"
#include "CRezMap.h"
#include "CRezFile.h"
#include "CInspectorWindow.h"
#include "CHexEditorWindow.h"
#include "CTmplEditorWindow.h"
#include "CTEXT_EditorView.h"
#include "CRecentItemsMenu.h"
#include "UMessageDialogs.h"
#include "UDialogBoxHandler.h"

// PP Classes for registration
#include <LFile.h>
#include <LWindow.h>
#include <LWindowHeader.h>
#include <LDocument.h>


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
	OSErr	ignoreErr;
	
	switch (inAENumber) {
		
		case ae_OpenDoc:
		HandleOpenDocsEvent(inAppleEvent, outAEReply, outResult);
		break;
		
		case aeRzil_Version: 
		char * theVers = new char[256];
		CopyPascalStringToC( sVersionNumber, theVers);
		Size  dataSize = strlen(theVers);
		ignoreErr = ::AEPutParamPtr(&outAEReply, keyAEResult, typeChar, theVers, dataSize);
		FailOSErr_(ignoreErr);
		break;
		
		case ae_ApplicationDied:
		break;
		
		default:
		LApplication::HandleAppleEvent(inAppleEvent, outAEReply, outResult, inAENumber);
		break;
	}
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



// // ---------------------------------------------------------------------------
// //   ¥ GetSubModelByUniqueID
// // ---------------------------------------------------------------------------
// //   Pass back a Token for the SubModel(s) of the specified type with the
// //   specified unique ID
// //
// //   Must be overridden by subclasses which have SubModels that aren't
// //   implemented using the submodel list (ie lazy instantiated submodels).
// //
// //   It is up to you to decide what constitutes a unique ID and you must also
// //   provide a CompareToUniqueID().
// 
// void
// CRezMap::GetSubModelByUniqueID(
//  DescType        inModelID,
//  const AEDesc    &inKeyData,
//  AEDesc          &outToken) const
// {
//  if (mSubModels != nil) {
//      TArrayIterator<LModelObject*>   iterator(*mSubModels);
//      SInt32          index = 0;
//      LModelObject    *p;
//      Boolean         found = false;
// 
//      while (iterator.Next(p)) {
//          if (p->GetModelKind() == inModelID) {
//              if (p->CompareToUniqueID(kAEEquals, inKeyData)) {
//                  found = true;
//                  break;
//              }
//          }
//      }
// 
//      if (found) {
//          PutInToken(p, outToken);
//          return;
//      }
//  }
// }


// // ---------------------------------------------------------------------------
// //	¥ GetPositionOfSubModel											  [public]
// // ---------------------------------------------------------------------------
// //	Return the position (1 = first) of a SubModel within an Application
// 
// SInt32
// CRezillaApp::GetPositionOfSubModel(
// 	DescType				inModelID,
// 	const LModelObject*		inSubModel) const
// {
// 	SInt32	position;
// 
// 	switch (inModelID) {
// 
// 		case cMap: {
// 		}
// 
// 		default:
// 			position = LApplication::GetPositionOfSubModel(inModelID, inSubModel);
// 			break;
// 	}
// 
// 	return position;
// }



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
		case pVersion: {
			error = ::AECreateDesc(typeChar, (Ptr) sVersionNumber + 1, sVersionNumber[0], &outPropertyDesc);
			break;
		}

		default:
			LModelObject::GetAEProperty(inProperty, inRequestedType, outPropertyDesc);
			break;
	}
}


