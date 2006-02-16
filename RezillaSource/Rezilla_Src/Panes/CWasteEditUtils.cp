// ===========================================================================
// CWasteEditUtils.cp
// 
// Created: 2001-09-05 18:22:04 
// Last modification: 2004-11-06 11:45:19
// Author: Bernard Desgraupes 
// e-mail: <bdesgraupes@users.sourceforge.net> 
// www: <http://rezilla.sourceforge.net/> 
// (c) Copyright: Bernard Desgraupes 2001-2004
// All rights reserved.
// 
// Description: CWaste is a class designed to interface between 
// the Waste Edit text engine (©1993-2000 by Marco Piovanelli)
// and CodeWarrior's PowerPlant 2.1 library (©1993-2000 Metrowerks Inc.) 
// 
// This file is part of the CWasteEditView package vs-1.8
// ===========================================================================


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include <LActiveScroller.h>
#include <UKeyFilters.h>
#include <Quickdraw.h>
#include <Sound.h>

#include "CWasteEditView.h"
#include "CWEViewActions.h"

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   ApplyStyleValues
// ---------------------------------------------------------------------------
// weDoMonoStyled

void
CWasteEditView::ApplyStyleValues(UInt16 theSize, UInt16 theFont)
{
	SInt32 saveStart, saveEnd;
	TextStyle theStyle;
	
	int saveBit = WEFeatureFlag( weFReadOnly, weBitClear, mWERef );
	WEGetSelection( & saveStart, & saveEnd, mWERef);
	WESetSelection( 0, 0x7FFFFFFF, mWERef );
	
	theStyle.tsSize = theSize;
	WESetStyle( weDoSize, &theStyle, mWERef );
	
	theStyle.tsFont = theFont;
	WESetStyle( weDoFont, &theStyle, mWERef );
	
	WESetSelection( saveStart, saveEnd, mWERef );
	WEFeatureFlag( weFReadOnly, saveBit, mWERef );
	
	AdjustImageToText();
	Refresh();
}


// ---------------------------------------------------------------------------
//   ApplyForeAndBackColors
// ---------------------------------------------------------------------------

void
CWasteEditView::ApplyForeAndBackColors() const
{
	Pattern	whitePat;
	UQDGlobals::GetWhitePat(&whitePat);
	::BackPat(&whitePat);
	::RGBForeColor(&Color_Black);
	::RGBBackColor(&Color_White);
}


// ---------------------------------------------------------------------------------
//   ToggleStyleAttribute					[public, virtual]
// ---------------------------------------------------------------------------------

void
CWasteEditView::ToggleStyleAttribute(
	Style inStyleAttr )
{
	if ( mMonoStyled )
		return;

	PostAction( new CWEViewFaceAction( inStyleAttr, true, this, this ) );
	UserChangedText();
}


// ---------------------------------------------------------------------------
//   ChangeFontSizeBy							[public, virtual]
// ---------------------------------------------------------------------------
//	Will only work if the font over the selection range is constant.  Returns
//	true if change was successful.

Boolean
CWasteEditView::ChangeFontSizeBy(
	SInt16	inDeltaSize)
{
	SInt16	currentSize;
	Boolean canChange = GetSize(currentSize);

	if ( canChange ) {
		SetSize((SInt16) (currentSize + inDeltaSize));
	}

	return canChange;
}


// ---------------------------------------------------------------------------
//   UserChangedText						[public, virtual]
// ---------------------------------------------------------------------------
//	Text of WasteEdit has changed as a result of user action

void
CWasteEditView::UserChangedText()
{
	if ( !IsDirty() ) {

		// Set the update menus flag.
		SetUpdateCommandStatus( true );
		
		// Set the dirty flag.
		SetDirty( true );

		if (mChangesMessage != msg_Nothing) {
			// Identify ourself in the ioParam argument
			BroadcastMessage(mChangesMessage, this);
		}
	}
}


#pragma mark -

// ---------------------------------------------------------------------------
//   CountLines								[public]
// ---------------------------------------------------------------------------

SInt32
CWasteEditView::CountLines()
{
	return ::WECountLines(mWERef);
}


// ---------------------------------------------------------------------------
//   PosToLine								[public]
// ---------------------------------------------------------------------------
// Note that Waste line numbers are 0-based 

SInt32
CWasteEditView::PosToLine(SInt32 inPos)
{
	return ::WEOffsetToLine(inPos, mWERef);
}


// ---------------------------------------------------------------------------
//   GetTextLength								[public]
// ---------------------------------------------------------------------------

SInt32
CWasteEditView::GetTextLength()
{
	return ::WEGetTextLength(mWERef);
}


// ---------------------------------------------------------------------------
//   CalcWEHeight							[public, virtual]
// ---------------------------------------------------------------------------
//	Calculates the height of the WasteEdit record.

SInt32
CWasteEditView::CalcWEHeight()
{
	LongRect	theDestRect ;
    WEGetDestRect(&theDestRect,mWERef);
	return WEGetHeight(0,WECountLines(mWERef),mWERef);
}


// ---------------------------------------------------------------------------
//   GetLineHeightFromStyle									  [public]
// ---------------------------------------------------------------------------

SInt16
CWasteEditView::GetLineHeightFromStyle(TextStyle inStyle)
 {
	// Calculate a default line spacing based on Font
	FMInput		fontSpecs;

	fontSpecs.family	= inStyle.tsFont;
	fontSpecs.size		= inStyle.tsSize;
	fontSpecs.face		= inStyle.tsFace;
	fontSpecs.needBits	= false;
	fontSpecs.device	= 0;
	fontSpecs.numer.h	= 1;
	fontSpecs.numer.v	= 1;
	fontSpecs.denom.h	= 1;
	fontSpecs.denom.v	= 1;

	FMOutPtr info = ::FMSwapFont(&fontSpecs);

	// Set line spacing based on Font
	return (SInt16) (info->ascent + info->descent + info->leading);
 }
 

#pragma mark -

// ---------------------------------------------------------------------------
//   GetSelection
// ---------------------------------------------------------------------------
//	Passes back an AEDesc of the currently selected text

void
CWasteEditView::GetSelection(
	AEDesc	&outDesc) const
{
	SInt32  theSelStart;
	SInt32  theSelEnd;
	Handle	currTextH = WEGetText(mWERef);
	
	WEGetSelection( & theSelStart, & theSelEnd, mWERef ) ;

	StHandleLocker lock((Handle) currTextH);

	OSErr err = ::AECreateDesc(typeChar,
							   (*currTextH + theSelStart),
							   (theSelEnd - theSelStart),
							   &outDesc);

	ThrowIfOSErr_(err);
}


// ---------------------------------------------------------------------------
//   GetLineRange								[public]
// ---------------------------------------------------------------------------

void
CWasteEditView::GetLineRange(SInt32 inLineIndex, SInt32 & outLineStart, SInt32 & outLineEnd)
{
	return ::WEGetLineRange(inLineIndex, & outLineStart, & outLineEnd, mWERef);
}


// ---------------------------------------------------------------------------
//   GetSelectionRange
// ---------------------------------------------------------------------------

void
CWasteEditView::GetSelectionRange(
	SInt32 & outStartPos,
	SInt32 & outEndPos)
{
	WEGetSelection(&outStartPos, &outEndPos, mWERef);
}


// ---------------------------------------------------------------------------
//   SetSelectionRange
// ---------------------------------------------------------------------------

void
CWasteEditView::SetSelectionRange(
	SInt32	inStartPos,
	SInt32	inEndPos,
	Boolean scrollIt)
{
	if (mSelectable) {
		LongRect oldDestRect;
		int saveFeature;
		
		if (!scrollIt) {
			saveFeature = WEFeatureFlag( weFAutoScroll, weBitClear, mWERef ) ;
		} else {
			WEGetDestRect( &oldDestRect, mWERef);	
		}
		
		WESetSelection(inStartPos, inEndPos, mWERef);
		
		if (!scrollIt) {
			WEFeatureFlag( weFAutoScroll, saveFeature, mWERef ) ;
		} else {
			ForceAutoScroll(oldDestRect);
			Refresh();
		}
	}
}


// ---------------------------------------------------------------------------
//   DisplaySelectionRange
// ---------------------------------------------------------------------------

void
CWasteEditView::DisplaySelectionRange(
	SInt32	inStartPos,
	SInt32	inEndPos)
{
	if (mSelectable) {
		LongRect oldDestRect;
		
		FocusDraw();

		WEGetDestRect( &oldDestRect, mWERef);	
		
		// Bring the inEndPos in view
		WESetSelection(inEndPos, inEndPos, mWERef);
		WESelView(mWERef);
		// Select the range with inStartPos as free endpoint
		WESetSelection(inEndPos, inStartPos, mWERef);
		WESelView(mWERef);
		
		ForceAutoScroll(oldDestRect);
		Refresh();
	}
}


// ---------------------------------------------------------------------------
//   HasSelection													  [public]
// ---------------------------------------------------------------------------
// Check if selection is empty (0) or not (1).

Boolean
CWasteEditView::HasSelection() {
	SInt32  selStart;
	SInt32  selEnd;
	
	WEGetSelection( & selStart, & selEnd, mWERef ) ;
	return ( selStart != selEnd );
}


// ---------------------------------------------------------------------------
//   SelectAll								[public, virtual]
// ---------------------------------------------------------------------------
//	Select entire contents of a WasteEdit

void
CWasteEditView::SelectAll()
{
	if (mSelectable) {
		StFocusAndClipIfHidden	focus(this);
		int saveFeature = WEFeatureFlag( weFAutoScroll, weBitClear, mWERef ) ;
		WESetSelection( 0, 0x7FFFFFFF, mWERef ) ;
		WEFeatureFlag( weFAutoScroll, saveFeature, mWERef ) ;
	}
}


#pragma mark -

// ---------------------------------------------------------------------------
//   SetDescriptor											[public, virtual]
// ---------------------------------------------------------------------------
//	Will set the text to the given string, replacing any and all text
//	already there.

void
CWasteEditView::SetDescriptor(
	ConstStringPtr	inDescriptor)
{
	SetTextPtr((Ptr)&inDescriptor[1], StrLength(inDescriptor), nil);
}


// ---------------------------------------------------------------------------
//   GetDescriptor											[public, virtual]
// ---------------------------------------------------------------------------
//	Return up to the first 255 characters of the WasteEditView as a Pascal
//	string. Caller must allocate a Str255 variable for storing the string.

StringPtr
CWasteEditView::GetDescriptor(
	Str255	outDescriptor ) const
{
	CharsHandle	theRawText = WEGetText(mWERef);

	Size textLength = ::GetHandleSize(theRawText);
	if (textLength > 255) {
		textLength = 255;
	}

	::BlockMoveData(*theRawText, outDescriptor+1, textLength);
	outDescriptor[0] = static_cast<UInt8>(textLength);

	return outDescriptor;
}


// ---------------------------------------------------------------------------
//   SetValue												[public, virtual]
// ---------------------------------------------------------------------------
//	Set the text in the WasteEditView to the string representation of the
//	specified integer number.

void
CWasteEditView::SetValue(
	SInt32	inValue )
{
	Str255	numAsString;
	::NumToString(inValue, numAsString);
	SetDescriptor(numAsString);
}


// ---------------------------------------------------------------------------
//   GetValue												[public, virtual]
// ---------------------------------------------------------------------------
//	Return the integer value represented by the contents of a WasteEditView.
//
//	An empty or non-numerical WasteEditView evaluates to zero.

SInt32
CWasteEditView::GetValue() const
{
	Str255	str;
	GetDescriptor(str);

	SInt32	theNumber = 0;
	if (StrLength(str) > 0) {
		::StringToNum(str, &theNumber);
	}

	return theNumber;
}


// ---------------------------------------------------------------------------
//   SavePlace								[public, virtual]
// ---------------------------------------------------------------------------
// Override function in LView class

void
CWasteEditView::SavePlace(
						  LStream		*outPlace)
{
	LView::SavePlace(outPlace);
	
	LongRect	viewRect ;
	WEGetViewRect(&viewRect,mWERef);
	// 	*outPlace << viewRect;
	outPlace->WriteBlock(&viewRect,sizeof(viewRect));
	
	LongRect	destRect ;
	WEGetDestRect(&destRect,mWERef);
	// 	*outPlace << destRect;
	outPlace->WriteBlock(&destRect,sizeof(destRect));
}


// ---------------------------------------------------------------------------
//   RestorePlace										[public, virtual]
// ---------------------------------------------------------------------------
// Override function in LView class

void
CWasteEditView::RestorePlace(
	LStream		*inPlace)
{
	LView::RestorePlace(inPlace);

	LongRect	theViewRect ;
	inPlace->ReadBlock(&theViewRect,sizeof(theViewRect));
	WESetViewRect(&theViewRect,mWERef);

	LongRect	theDestRect ;
	inPlace->ReadBlock(&theDestRect,sizeof(theDestRect));
	WESetDestRect(&theDestRect,mWERef);
}


// ---------------------------------------------------------------------------
//   SaveStateForUndo									[protected, virtual]
// ---------------------------------------------------------------------------

SWasteEditUndoH
CWasteEditView::SaveStateForUndo()
{
	SInt32	theSelStart;
	SInt32	theSelEnd;
	WEGetSelection( & theSelStart, & theSelEnd, mWERef);

	SWasteEditUndoH	theUndoH = reinterpret_cast<SWasteEditUndoH>
									(::NewHandle(sizeof(SWasteEditUndo)));
	ThrowIfMemFail_(theUndoH);

	Handle	currTextH		= WEGetText(mWERef);
	ThrowIfOSErr_(::HandToHand(&currTextH));
	(*theUndoH)->textH		= currTextH;
	(*theUndoH)->selStart	= theSelStart;
	(*theUndoH)->selEnd		= theSelEnd;

	return theUndoH;
}


// ---------------------------------------------------------------------------
//   FlagsFromAttributes											  [public]
// ---------------------------------------------------------------------------
// Build the WE flags from the mTextAttributes variable.

UInt32
CWasteEditView::FlagsFromAttributes() {
	UInt32  theFlags = 0 ;
	
	theFlags |= HasAttribute(weAttr_AutoScroll) ?		weDoAutoScroll : 0 ;
	theFlags |= HasAttribute(weAttr_OutlineHilite) ?	weDoOutlineHilite : 0 ;
	theFlags |= HasAttribute(weAttr_MonoStyled) ?		weDoMonoStyled : 0 ;
	theFlags |= HasAttribute(weAttr_ReadOnly) ?			weDoReadOnly : 0 ;
	theFlags |= HasAttribute(weAttr_DragAndDrop) ?		weDoDragAndDrop : 0 ;
	theFlags |= HasAttribute(weAttr_Undo) ?				weDoUndo : 0 ;
	theFlags |= HasAttribute(weAttr_MultipleUndo) ?		weDoMultipleUndo : 0 ;
	theFlags |= HasAttribute(weAttr_IntCutAndPaste) ?	weDoIntCutAndPaste : 0 ;
	theFlags |= HasAttribute(weAttr_DrawOffscreen) ?	weDoDrawOffscreen : 0 ;
	theFlags |= HasAttribute(weAttr_InhibitRecal) ?		weDoInhibitRecal : 0 ;
	theFlags |= HasAttribute(weAttr_InhibitRedraw) ?	weDoInhibitRedraw : 0 ;
	theFlags |= HasAttribute(weAttr_InhibitICSupport) ?	weDoInhibitICSupport : 0 ;
	theFlags |= HasAttribute(weAttr_InhibitColor) ?		weDoInhibitColor : 0 ;
	theFlags |= HasAttribute(weAttr_UseTempMem) ?		weDoUseTempMem : 0 ;
	theFlags |= HasAttribute(weAttr_NoKeyboardSync) ?	weDoNoKeyboardSync : 0 ;
	
	return theFlags;
}


// ---------------------------------------------------------------------------
//   SetAttributesFromProperties									  [public]
// ---------------------------------------------------------------------------
// Initialize mTextAttributes from the individual property values.

void
CWasteEditView::SetAttributesFromProperties()
{
	mTextAttributes = 0 ;
	mTextAttributes |= mAutoScroll ?		weAttr_AutoScroll : 0;
	mTextAttributes |= mOutlineHilite ?		weAttr_OutlineHilite : 0;
	mTextAttributes |= mMonoStyled ?		weAttr_MonoStyled : 0;
	mTextAttributes |= mReadOnly ?			weAttr_ReadOnly : 0;
	mTextAttributes |= mDragAndDrop ?		weAttr_DragAndDrop : 0;
	mTextAttributes |= mUndo ?				weAttr_Undo : 0;
	mTextAttributes |= mMultipleUndo ?		weAttr_MultipleUndo : 0;
	mTextAttributes |= mIntCutAndPaste ?	weAttr_IntCutAndPaste : 0;
	mTextAttributes |= mDrawOffscreen ?		weAttr_DrawOffscreen : 0;
	mTextAttributes |= mInhibitRecal ?		weAttr_InhibitRecal : 0;
	mTextAttributes |= mInhibitRedraw ?		weAttr_InhibitRedraw : 0;
	mTextAttributes |= mInhibitICSupport ?	weAttr_InhibitICSupport : 0;
	mTextAttributes |= mInhibitColor ?		weAttr_InhibitColor : 0;
	mTextAttributes |= mUseTempMem ?		weAttr_UseTempMem : 0;
	mTextAttributes |= mNoKeyboardSync ?	weAttr_NoKeyboardSync : 0;
}


// ---------------------------------------------------------------------------
//   SetPropertiesFromAttributes								  [public]
// ---------------------------------------------------------------------------
// Initialize the individual property values from mTextAttributes.

void
CWasteEditView::SetPropertiesFromAttributes()
{
	mAutoScroll			|= mTextAttributes & weDoAutoScroll;
	mOutlineHilite		|= mTextAttributes & weDoOutlineHilite;
	mMonoStyled			|= mTextAttributes & weDoMonoStyled;
	mReadOnly			|= mTextAttributes & weDoReadOnly;
	mDragAndDrop		|= mTextAttributes & weDoDragAndDrop;
	mUndo				|= mTextAttributes & weDoUndo;
	mMultipleUndo		|= mTextAttributes & weDoMultipleUndo;
	mIntCutAndPaste		|= mTextAttributes & weDoIntCutAndPaste;
	mDrawOffscreen		|= mTextAttributes & weDoDrawOffscreen;
	mInhibitRecal		|= mTextAttributes & weDoInhibitRecal;
	mInhibitRedraw		|= mTextAttributes & weDoInhibitRedraw;
	mInhibitICSupport	|= mTextAttributes & weDoInhibitICSupport;
	mInhibitColor		|= mTextAttributes & weDoInhibitColor;
	mUseTempMem			|= mTextAttributes & weDoUseTempMem;
	mNoKeyboardSync		|= mTextAttributes & weDoNoKeyboardSync;
}
 


PP_End_Namespace_PowerPlant
