// ===========================================================================
// CRezillaAppAE.cp					
//                       Created: 2004-11-30 08:44:17
//             Last modification: 2004-11-30 13:43:37
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2004
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
	SInt32	count = 0;

	switch (inModelID) {

		case cWindow:
		case rzil_cRezMapWindow:
		case rzil_cEditorWindow:
		case rzil_cGuiWindow:
		case rzil_cTmplWindow:
		case rzil_cHexWindow:
		case rzil_cCompWindow: {
			WindowPtr	windowP = ::GetWindowList();
			LWindow *	theWindow;
			
			while (windowP != nil) {
				theWindow = LWindow::FetchWindowObject(windowP);
				if (theWindow->GetModelKind() == inModelID) {
					count++;
				} 
				windowP = ::MacGetNextWindow(windowP);
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

		default:
			LModelObject::GetSubModelByName(inModelID, inName, outToken);
			break;
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
	SInt32	position;

	switch (inModelID) {

		case cWindow: {
			const LWindow*	window = dynamic_cast<const LWindow*>(inSubModel);
			if (window != nil) {
				position = UWindows::FindWindowIndex(window->GetMacWindow());
			} else {
				Throw_(errAENoSuchObject);
			}
			break;
		}

		default:
			position = LModelObject::GetPositionOfSubModel(inModelID, inSubModel);
			break;
	}

	return position;
}





