// ===========================================================================
// CBiDataWE.cp 
//                       Created: 2004-03-21 12:08:03
//             Last modification: 2004-06-06 22:09:39
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
//	¥ Insert								[public, virtual]
// ---------------------------------------------------------------------------
//	Will optionally recalculate, autoscroll, and refresh the text if desired.

OSErr
CBiDataWE::Insert(
					   const void*		inText,
					   SInt32			inLength,
					   StScrpHandle		inStyleH,
					   Boolean			inRefresh )
{
	OSErr result = noErr;
	return result;
}


// ---------------------------------------------------------------------------
//	¥ Insert								[public, virtual]
// ---------------------------------------------------------------------------

OSErr
CBiDataWE::Insert(
				   Str255 		inString,
				   Boolean		inRefresh )
{
	OSErr result = noErr;
	return result;
}


// ---------------------------------------------------------------------------
//	¥ InsertContents								[public, virtual]
// ---------------------------------------------------------------------------

void
CBiDataWE::InsertContents(Handle inHandle)
{
	switch (mDataType) {
		case bidata_hexType: {
			StSepHexTranslator translator(inHandle);
			translator.Convert();
			
			// Empty the Waste edit
			DeleteAll();
			// Put the contents in the hex view and clear the dirty flag.
			SetTextHandle( translator.GetOutHandle() );
			WESetSelection(0, 0, mWasteEditRef);
		}
		break;
		
		case bidata_txtType: {
			StSepTextTranslator translator(inHandle);
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
			StSepHexTranslator translator(inPtr, inByteCount);
			translator.Convert();
			
			// Empty the Waste edit
			DeleteAll();
			// Put the contents in the hex view and clear the dirty flag.
			SetTextHandle( translator.GetOutHandle() );
			WESetSelection(0, 0, mWasteEditRef);
		}
		break;
		
		case bidata_txtType: {
			StSepTextTranslator translator(inPtr, inByteCount);
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
