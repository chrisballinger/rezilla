// ===========================================================================
// CBiDataWE.cp 
//                       Created: 2004-03-21 12:08:03
//             Last modification: 2004-11-13 23:07:14
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include <UDesktop.h>
#include <LActiveScroller.h>
#include <UKeyFilters.h>
#include <Quickdraw.h>
#include <Sound.h>

#include "CBiDataWE.h"
#include "CCompResultWindow.h"
#include "UHexFilters.h"
#include "UCodeTranslator.h"
#include "RezillaConstants.h"

PP_Begin_Namespace_PowerPlant



// ---------------------------------------------------------------------------
//	¥ CBiDataWE						Default Constructor		  [public]
// ---------------------------------------------------------------------------

CBiDataWE::CBiDataWE()
	: CWasteEditView()
{
	mDataType = bidata_hexType;
}


// ---------------------------------------------------------------------------
//	¥ CBiDataWE						Copy Constructor		  [public]
// ---------------------------------------------------------------------------

CBiDataWE::CBiDataWE(
	   const CBiDataWE&	inOriginal )
	: CWasteEditView(inOriginal)
{
	CBiDataWE * outHexDataWE = new CBiDataWE();
	outHexDataWE->mDataType = inOriginal.mDataType;
}


// ---------------------------------------------------------------------------
//	¥ CBiDataWE						Stream Constructor		  [public]
// ---------------------------------------------------------------------------

CBiDataWE::CBiDataWE(
	LStream*	inStream)
	: CWasteEditView(inStream)
{
	mDataType = bidata_hexType;
}


// ---------------------------------------------------------------------------
//	¥ ~CBiDataWE						Destructor				  [public]
// ---------------------------------------------------------------------------

CBiDataWE::~CBiDataWE()
{}


#pragma mark -


// ---------------------------------------------------------------------------
//	¥ FindCommandStatus							[public, virtual]
// ---------------------------------------------------------------------------

void
CBiDataWE::FindCommandStatus(
	CommandT	inCommand,
	Boolean		&outEnabled,
	Boolean		&outUsesMark,
	UInt16		&outMark,
	Str255		outName)
{
	mCompareWindow->FindCommandStatus(inCommand, outEnabled,
							outUsesMark, outMark, outName);
}


// ---------------------------------------------------------------------------
//	¥ ObeyCommand							[public, virtual]
// ---------------------------------------------------------------------------
// Cut, Paste and Clear are disabled.

Boolean
CBiDataWE::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;

	switch (inCommand) {

		case cmd_Copy: {
			Handle txtData = nil;
			SInt32 theStartPos, theEndPos;
			UInt16 thePeriod;
			
			switch (mDataType) {
				case bidata_hexType:
				thePeriod = 3;
				break;
				
				case bidata_txtType:
				thePeriod = 2;
				break;
			}
			GetSelectionRange(theStartPos, theEndPos);
			
			// Put selected text on clipboard
			txtData = ::NewHandle(theEndPos - theStartPos);
			WEStreamRange(theStartPos, theEndPos, kTypeText, 0, txtData, mWasteEditRef) ;
			StStripPeriodicalTranslator blankstripper(txtData, thePeriod);
			blankstripper.FilterOutPeriodical();
			UScrap::SetData(ResType_Text, blankstripper.GetOutHandle());
									
			if (txtData != nil) {
				::DisposeHandle(txtData);
			} 
			break;
		}
				
		default:
			cmdHandled = mCompareWindow->ObeyCommand(inCommand, ioParam);
			break;
	}

	return cmdHandled;
}


// ---------------------------------------------------------------------------
//	¥ ClickSelf											[protected, virtual]
// ---------------------------------------------------------------------------

void
CBiDataWE::ClickSelf(
	const SMouseDownEvent	&inMouseDown)
{
	CWasteEditView::ClickSelf(inMouseDown);
	AdjustCursorPos();
}


// ---------------------------------------------------------------------------
//	¥ AdjustCursorPos											[protected, virtual]
// ---------------------------------------------------------------------------

void
CBiDataWE::AdjustCursorPos()
{
	SInt32  selStart;
	SInt32  selEnd;
	
	WEGetSelection( & selStart, & selEnd, mWasteEditRef ) ;
	WESetSelection( NearestTruePos(selStart), NearestTruePos(selEnd), mWasteEditRef);
}


// ---------------------------------------------------------------------------
//	¥ NearestTruePos											[protected, virtual]
// ---------------------------------------------------------------------------
// Returns the nearest pos just before or after a hexadecimal or textual value

SInt32
CBiDataWE::NearestTruePos(SInt32 inPos)
{
	SInt32  thePos = inPos;

	switch (mDataType) {
		case bidata_hexType:
		SInt32  rest = inPos % 3;
		if (rest == 1) {
			thePos -= 1;
		} else if (rest == 2) {
			thePos += 1;
		} 
		break;
		
		case bidata_txtType:
		thePos = inPos + (inPos % 2);
		break;
	}
	return thePos;
}


// ---------------------------------------------------------------------------
//	¥ GetCurrCharPos											[public]
// ---------------------------------------------------------------------------

void
CBiDataWE::GetCurrCharPos(SInt32 & outCharSelStart, SInt32 & outCharSelEnd)
{
	SInt32  selStart;
	SInt32  selEnd;
	WEGetSelection( & selStart, & selEnd, mWasteEditRef ) ;
	outCharSelStart = PosToCharPos(selStart);
	outCharSelEnd = PosToCharPos(selEnd);
}


// ---------------------------------------------------------------------------
//	¥ PosToCharPos											[protected, virtual]
// ---------------------------------------------------------------------------

SInt32
CBiDataWE::PosToCharPos(SInt32 inPos)
{
	SInt32  rest = inPos % 2;
	return ( inPos - rest )/2 ;
}


// ---------------------------------------------------------------------------
//	¥ CharPosToPos											[protected, virtual]
// ---------------------------------------------------------------------------

SInt32
CBiDataWE::CharPosToPos(SInt32 inCharPos)
{
	return (2 * inCharPos);
}


// ---------------------------------------------------------------------------
//	¥ GetCurrHexPos											[public]
// ---------------------------------------------------------------------------

void
CBiDataWE::GetCurrHexPos(SInt32 & outHexSelStart, SInt32 & outHexSelEnd)
{
	SInt32  selStart;
	SInt32  selEnd;
	WEGetSelection( & selStart, & selEnd, mWasteEditRef ) ;
	outHexSelStart = PosToHexPos(selStart);
	outHexSelEnd = PosToHexPos(selEnd);
}


// ---------------------------------------------------------------------------
//	¥ PosToHexPos											[protected, virtual]
// ---------------------------------------------------------------------------

SInt32
CBiDataWE::PosToHexPos(SInt32 inPos)
{
	SInt32  rest = inPos % 3;
	return ( inPos - rest )/3 ;
}


// ---------------------------------------------------------------------------
//	¥ HexPosToPos											[protected, virtual]
// ---------------------------------------------------------------------------

SInt32
CBiDataWE::HexPosToPos(SInt32 inHexPos)
{
	return (3 * inHexPos);
}


#pragma mark -

// ---------------------------------------------------------------------------
//	¥ HandleKeyPress							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CBiDataWE::HandleKeyPress(
	const EventRecord	&inKeyEvent)
{
	Boolean keyHandled = true;
	return keyHandled;
}


// ---------------------------------------------------------------------------
//	¥ InsertContents								[public, virtual]
// ---------------------------------------------------------------------------

void
CBiDataWE::InsertContents(Handle inHandle)
{
	switch (mDataType) {
		case bidata_hexType: {
			StSegmHexTranslator translator(inHandle, mCompareWindow->GetPaneCount(count_BytesPerLine) );
			translator.Convert();
			
			// Empty the Waste edit
			DeleteAll();
			// Put the contents in the hex view and clear the dirty flag.
			SetTextHandle( translator.GetOutHandle() );
			WESetSelection(0, 0, mWasteEditRef);
		}
		break;
		
		case bidata_txtType: {
			StSegmTextTranslator translator(inHandle, mCompareWindow->GetPaneCount(count_BytesPerLine) );
			translator.Convert();
			
			// Empty the Waste edit
			DeleteAll();
			// Put the contents in the hex view and clear the dirty flag.
			SetTextHandle( translator.GetOutHandle() );
			WESetSelection(0, 0, mWasteEditRef);
		}
		break;
	}	
}


// ---------------------------------------------------------------------------
//	¥ InsertContents								[public, virtual]
// ---------------------------------------------------------------------------

void
CBiDataWE::InsertContents(const void * inPtr, SInt32 inByteCount)
{
	switch (mDataType) {
		case bidata_hexType: {
			StSegmHexTranslator translator(inPtr, inByteCount, mCompareWindow->GetPaneCount(count_BytesPerLine));
			translator.Convert();
			
			// Empty the Waste edit
			DeleteAll();
			// Put the contents in the hex view and clear the dirty flag.
			SetTextHandle( translator.GetOutHandle() );
			WESetSelection(0, 0, mWasteEditRef);
		}
		break;
		
		case bidata_txtType: {
			StSegmTextTranslator translator(inPtr, inByteCount, mCompareWindow->GetPaneCount(count_BytesPerLine));
			translator.Convert();
			
			// Empty the Waste edit
			DeleteAll();
			// Put the contents in the hex view and clear the dirty flag.
			SetTextHandle( translator.GetOutHandle() );
			WESetSelection(0, 0, mWasteEditRef);
		}
		break;
	}	
}



PP_End_Namespace_PowerPlant
