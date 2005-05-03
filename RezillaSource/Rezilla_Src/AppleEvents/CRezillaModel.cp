// ===========================================================================
// CRezillaModel.cp
//                       Created: 2005-05-03 07:38:23
//             Last modification: 2005-05-03 08:01:11
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CRezillaModel.h"
#include "CRezObj.h"
#include "RezillaConstants.h"

#include <LModelObject.h>

#include <UExtractFromAEDesc.h>

// #include <AERegistry.h>
// #include <AEObjects.h>
// #include <AEPackObject.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//	 CRezillaModel						Default Constructor		  [public]
// ---------------------------------------------------------------------------

CRezillaModel::CRezillaModel()
		: LModelDirector()
{}


// ---------------------------------------------------------------------------
//	 CRezillaModel						Constructor				  [public]
// ---------------------------------------------------------------------------

CRezillaModel::CRezillaModel(
	LModelObject*	inDefaultModel)
		: LModelDirector(inDefaultModel)
{}


// ---------------------------------------------------------------------------
//	¥ ~CRezillaModel						Destructor				  [public]
// ---------------------------------------------------------------------------

CRezillaModel::~CRezillaModel()
{
}


// // ---------------------------------------------------------------------------
// //	¥ InstallCallBacks												  [public]
// // ---------------------------------------------------------------------------
// //	Install handler and callback functions used by the AppleEvent Manager
// //		and the Object Support Library
// //	Call this function only once (usually at the beginning of the program)
// 
// void
// CRezillaModel::InstallCallBacks()
// {
// 	OSErr	err;
// 
// 		// Generic handler for all AppleEvents
// 
// 	UAppleEventsMgr::InstallAEHandlers(
// 			NewAEEventHandlerUPP(&CRezillaModel::AppleEventHandler));
// 
// 		// Specific handler for CountElements AppleEvent
// 
// 	err = ::AEInstallEventHandler(kAECoreSuite, kAECountElements,
// 			NewAEEventHandlerUPP(&CRezillaModel::CountElementsEventHandler),
// 			ae_CountElements, false);
// 	ThrowIfOSErr_(err);
// 
// 		// Specific handler for CreateElement AppleEvent
// 
// 	err = ::AEInstallEventHandler(kAECoreSuite, kAECreateElement,
// 			NewAEEventHandlerUPP(&CRezillaModel::CreateElementEventHandler),
// 			ae_CreateElement, false);
// 	ThrowIfOSErr_(err);
// 
// 		// Specific handler for DoObjectsExist AppleEvent
// 
// 	err = ::AEInstallEventHandler(kAECoreSuite, kAEDoObjectsExist,
// 			NewAEEventHandlerUPP(&CRezillaModel::DoObjectsExistEventHandler),
// 			ae_DoObjectsExist, false);
// 	ThrowIfOSErr_(err);
// 
// 		// Generic accessor for Model Objects
// 
// 	err = ::AEInstallObjectAccessor(typeWildCard, typeWildCard,
// 				NewOSLAccessorUPP(&CRezillaModel::ModelObjectAccessor),
// 				0, false);
// 	ThrowIfOSErr_(err);
// 
// 		// Accessor for List of Model Objects
// 
// 	err = ::AEInstallObjectAccessor(typeWildCard, typeAEList,
// 				NewOSLAccessorUPP(&CRezillaModel::ModelObjectListAccessor),
// 				0, false);
// 	ThrowIfOSErr_(err);
// 
// 	err = ::AESetObjectCallbacks(
// 				NewOSLCompareUPP(&CRezillaModel::OSLCompareObjects),
// 				NewOSLCountUPP(&CRezillaModel::OSLCountObjects),
// 				NewOSLDisposeTokenUPP(&CRezillaModel::OSLDisposeToken),
// 				nil,		// GetMarkToken
// 				nil,		// Mark
// 				nil,		// AdjustMarks
// 				nil);		// GetErrDesc
// 	ThrowIfOSErr_(err);
// }


#pragma mark -


// ---------------------------------------------------------------------------
//	 DisposeToken													  [public]
// ---------------------------------------------------------------------------
//	The CRezObj created to represent a "resource" object specifier are
//	created on the fly since there is no permanent CRezObj in the
//	application for them. They get deleted here when the OSLDisposeToken
//	callback is invoked.
//	
//	


void
CRezillaModel::DisposeToken(
	AEDesc&		ioToken)
{
	if (ioToken.descriptorType == type_ModelToken) {
		LModelObject*	theModel = nil;
		SModelToken		theToken;
		
		ThrowIfOSErr_( ::AEGetDescData(&ioToken, &theToken, sizeof(SModelToken)));
		theModel = theToken.modelObject;
		if (theModel->GetModelKind() == rzom_cRezObj) {
			CRezObj* theRezObj = dynamic_cast<CRezObj*>(theModel);
			if (theRezObj != nil) {
				delete theRezObj;
			} 
		} 
	} 
	
	::AEDisposeDesc(&ioToken);
}


#pragma mark -


// // ---------------------------------------------------------------------------
// //	 ModelObjectAccessor								  [protected] [static]
// // ---------------------------------------------------------------------------
// 
// pascal OSErr
// CRezillaModel::ModelObjectAccessor(
// 	DescType		inDesiredClass,
// 	const AEDesc*	inContainerToken,
// 	DescType		inContainerClass,
// 	DescType		inKeyForm,
// 	const AEDesc*	inKeyData,
// 	AEDesc*			outToken,
// 	SInt32			inRefCon)
// {
// 	OSErr	err = noErr;
// 
// 	try {
// 		sModelDirector->AccessModelObject(inDesiredClass,
// 									*inContainerToken, inContainerClass,
// 									inKeyForm, *inKeyData,
// 									*outToken, inRefCon);
// 	}
// 
// 	catch (ExceptionCode inErr) {
// 		err = (OSErr) inErr;
// 	}
// 
// 	catch (const LException& inException) {
// 		err = (OSErr) inException.GetErrorCode();
// 	}
// 
// 	catch (...) {
// 		err = errAENoSuchObject;
// 	}
// 
// 	return err;
// }




#pragma mark -

// // ---------------------------------------------------------------------------
// //	 OSLDisposeToken									  [protected] [static]
// // ---------------------------------------------------------------------------
// 
// pascal OSErr
// CRezillaModel::OSLDisposeToken(
// 	AEDesc*		inToken)
// {
// 	OSErr	err = noErr;
// 
// 	try {
// 		sModelDirector->DisposeToken(*inToken);
// 	}
// 
// 	catch (ExceptionCode inErr) {
// 		err = (OSErr) inErr;
// 	}
// 
// 	catch (const LException& inException) {
// 		err = (OSErr) inException.GetErrorCode();
// 	}
// 
// 	catch (...) {
// 		err = errAEEventNotHandled;
// 	}
// 
// 	return err;
// }






#pragma mark -

// // ---------------------------------------------------------------------------
// //	 StoreReplyErrorString								  [protected] [static]
// // ---------------------------------------------------------------------------
// 
// void
// CRezillaModel::StoreReplyErrorString(
// 	ConstStringPtr	inErrorString,
// 	AppleEvent*		ioReply)
// {
// 	if (ioReply->descriptorType != typeNull) {
// 		if (StrLength(inErrorString) > 0) {
// 			::AEPutParamPtr(ioReply, keyErrorString, typeChar,
// 							inErrorString + 1,
// 							StrLength(inErrorString));
// 		}
// 	}
// }


PP_End_Namespace_PowerPlant
