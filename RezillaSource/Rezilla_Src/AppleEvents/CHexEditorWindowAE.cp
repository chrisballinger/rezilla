// ===========================================================================
// CHexEditorWindowAE.cp
// 
//                       Created: 2005-04-28 23:45:11
//             Last modification: 2005-06-15 06:03:15
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
//  AppleEvent Object Model Support. These methods are part of the CHexEditorWindow 
//  class (inheriting from LModelObject).

#include "CHexEditorWindow.h"
#include "CDualDataView.h"
#include "CHexDataSubView.h"
#include "CTxtDataSubView.h"
#include "RezillaConstants.h"
#include "UCodeTranslator.h"
#include "UMiscUtils.h"

#include <LCommander.h>


// ---------------------------------------------------------------------------
//	¥ GetAEProperty
// ---------------------------------------------------------------------------
// 	rzom_pHexWinMaxPos			= 'maxP';	// Index of last position
// 	rzom_pHexWinStartPos		= 'iniP';	// Position of beginning of selection
// 	rzom_pHexWinEndPos			= 'endP';	// Position of end of selection
// 	rzom_pHexWinHexSelection	= 'hSel';	// Contents of selection in hex pane
// 	rzom_pHexWinTxtSelection	= 'tSel';	// Contents of selection in text pane

void
CHexEditorWindow::GetAEProperty(
	DescType		inProperty,
	const AEDesc&	inRequestedType,
	AEDesc&			outPropertyDesc) const
{
	OSErr	error = noErr;
	SInt32	theLen, theStartPos, theEndPos;
	WEReference	weRef = mDualView->GetInMemoryWE();

	switch (inProperty) {
		case rzom_pHexWinMaxPos:
		theLen = ::WEGetTextLength(weRef);
		error = ::AECreateDesc(typeSInt32, (Ptr) &theLen,
									sizeof(SInt32), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
		
		
		case rzom_pHexWinStartPos:
		::WEGetSelection( &theStartPos, &theEndPos, weRef);
		error = ::AECreateDesc(typeSInt32, (Ptr) &theStartPos,
									sizeof(SInt32), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
		
		
		case rzom_pHexWinEndPos:
		::WEGetSelection( &theStartPos, &theEndPos, weRef);
		error = ::AECreateDesc(typeSInt32, (Ptr) &theEndPos,
									sizeof(SInt32), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;
		
		
		case rzom_pHexWinHexSelection:
		case rzom_pHexWinTxtSelection: {
			Handle	dataH;
			
			::WEGetSelection( &theStartPos, &theEndPos, weRef);
			dataH = ::NewHandle(theEndPos - theStartPos);
			::WEStreamRange(theStartPos, theEndPos, kTypeText, 0, dataH, weRef) ;
			if (dataH != nil) {
				
				if (inProperty == rzom_pHexWinHexSelection) {
					StByteToHexTranslator hextranslator(dataH);
					hextranslator.Convert();
					error = ::AECreateDesc(typeChar, (Ptr) *(hextranslator.GetOutHandle()),
										   hextranslator.GetOutSize(), &outPropertyDesc);
				} else {
					StByteToTextTranslator txttranslator(dataH);
					txttranslator.Convert();
					error = ::AECreateDesc(typeChar, (Ptr) *(txttranslator.GetOutHandle()),
										   txttranslator.GetOutSize(), &outPropertyDesc);
				}
			   ThrowIfOSErr_(error);
			}
			break;
		}
		
				
		default:
		LWindow::GetAEProperty(inProperty, inRequestedType,
									outPropertyDesc);
		break;
	}
}


// ---------------------------------------------------------------------------
//	¥ SetAEProperty
// ---------------------------------------------------------------------------

void
CHexEditorWindow::SetAEProperty(
	DescType		inProperty,
	const AEDesc&	inValue,
	AEDesc&			outAEReply)
{
	OSErr		error;
	SInt32		theLong, theStartPos, theEndPos;
	WEReference	weRef = mDualView->GetInMemoryWE();
	Handle		dataH;
	Size		theSize;
	
	switch (inProperty) {
		case rzom_pHexWinStartPos:
		::WEGetSelection( &theStartPos, &theEndPos, weRef);
		UExtractFromAEDesc::TheSInt32(inValue, theLong);
		if (theLong > theEndPos) {
			theStartPos = theLong;
			theEndPos = theLong;
		} else {
			theStartPos = theLong;
		}
		::WESetSelection(theStartPos, theEndPos, weRef);
		DisplayBothSelections(theStartPos, theEndPos);
		break;
		
		
		case rzom_pHexWinEndPos:
		::WEGetSelection( &theStartPos, &theEndPos, weRef);
		UExtractFromAEDesc::TheSInt32(inValue, theLong);
		if (theLong < theStartPos) {
			theStartPos = theLong;
			theEndPos = theLong;
		} else {
			theEndPos = theLong;
		}
		::WESetSelection(theStartPos, theEndPos, weRef);
		DisplayBothSelections(theStartPos, theEndPos);
		break;
		
		
		case rzom_pHexWinHexSelection:
		case rzom_pHexWinTxtSelection: {
			theSize = ::AEGetDescDataSize(&inValue);
			dataH = ::NewHandle(theSize);
			error = ::MemError();
			
			if (dataH != nil) {
				::WEGetSelection( &theStartPos, &theEndPos, weRef);
				error = ::AEGetDescData(&inValue, *dataH, theSize);
				ThrowIfOSErr_(error);
				
				if (inProperty == rzom_pHexWinHexSelection) {
					if ( ! UMiscUtils::IsValidHexadecimal(dataH) ) {
						ThrowIfOSErr_(err_InvalidHexadecimalData);
					} else {
						StHexToByteTranslator translator(dataH);
						translator.Convert();
						::WEDelete(weRef);
						::WEPut( kCurrentSelection, kCurrentSelection, *translator.GetOutHandle(), 
							  translator.GetOutSize(), kTextEncodingMultiRun, 
							  kNilOptions, 0, nil, nil, weRef);
						theSize = translator.GetOutSize();
					}
				} else {
					::WEDelete(weRef);
					::WEPut( kCurrentSelection, kCurrentSelection, *dataH, theSize, kTextEncodingMultiRun,
								kNilOptions, 0, nil, nil, weRef);
				}
				::DisposeHandle(dataH);
				mDualView->SetMaxScrollerValue();
				InstallContentsFromLine(mDualView->GetCurrFirstLine());
				DisplayBothSelections(theStartPos, theStartPos + theSize);
				mDualView->SetDirty(true);
			} 
			break;
		}
		
		
		default:
		LWindow::SetAEProperty(inProperty, inValue, outAEReply);
		break;
	}
}


// ---------------------------------------------------------------------------
//	¥ AEPropertyExists
// ---------------------------------------------------------------------------

bool
CHexEditorWindow::AEPropertyExists(
	DescType	inProperty) const
{
	bool	exists = false;

	switch (inProperty) {
		case rzom_pHexWinMaxPos:
		case rzom_pHexWinStartPos:
		case rzom_pHexWinEndPos:
		case rzom_pHexWinHexSelection:
		case rzom_pHexWinTxtSelection:
		exists = true;
		break;
		
		default:
			exists = LWindow::AEPropertyExists(inProperty);
			break;
	}

	return exists;
}


// ---------------------------------------------------------------------------
//	¥ GetModelProperty
// ---------------------------------------------------------------------------
//	Return a ModelObject object for 'HexP' and 'TxtP' properties
//	Currently not implemented

LModelObject*
CHexEditorWindow::GetModelProperty(DescType inProperty) const
{
	LModelObject* theModelObject = nil;

	switch (inProperty) {

// 		case rzom_cHexPane:
// 		case rzom_cTxtPane: 
// 		break;
		
		default:
		theModelObject = LModelObject::GetModelProperty(inProperty);
			break;
	}

	return theModelObject;
}

		




