// ===========================================================================
// CWasteEditUtils.cp
// 
// Created : 2001-09-05 18:22:04 
// Last modification : 2004-11-06 11:45:19
// Author: Bernard Desgraupes 
// e-mail: <bdesgraupes@easyconnect.fr> 
// www: <http://webperso.easyconnect.fr/bdesgraupes/> 
// © Copyright: Bernard Desgraupes 2001-2004
// All rights reserved.
// $Date$
// $Revision$
// 
// Description : CWaste is a class designed to interface between 
// the Waste Edit text engine (©1993-2000 by Marco Piovanelli)
// and CodeWarrior's PowerPlant 2.1 library (©1993-2000 Metrowerks Inc.) 
// 
// This file is part of the CWasteEditView package vs 1.7
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


#pragma mark -


// ---------------------------------------------------------------------------
//	¥ SetValue												[public, virtual]
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
//	¥ GetValue												[public, virtual]
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
//	¥ SetDescriptor											[public, virtual]
// ---------------------------------------------------------------------------
//	Will set the text to the given string, replacing any and all text
//	already there

void
CWasteEditView::SetDescriptor(
	ConstStringPtr	inDescriptor)
{
	SetTextPtr((Ptr)&inDescriptor[1], StrLength(inDescriptor), nil);
}


// ---------------------------------------------------------------------------
//	¥ GetDescriptor											[public, virtual]
// ---------------------------------------------------------------------------
//	Return up to the first 255 characters of the WasteEditView as a Pascal
//	string. Caller must allocate a Str255 variable for storing the string.

StringPtr
CWasteEditView::GetDescriptor(
	Str255	outDescriptor ) const
{
	CharsHandle	theRawText = WEGetText(mWasteEditRef);

	Size textLength = ::GetHandleSize(theRawText);
	if (textLength > 255) {
		textLength = 255;
	}

	::BlockMoveData(*theRawText, outDescriptor+1, textLength);
	outDescriptor[0] = static_cast<UInt8>(textLength);

	return outDescriptor;
}


// ---------------------------------------------------------------------------
//	¥ SetTextHandle							[public, virtual]
// ---------------------------------------------------------------------------
//	Set the text in the CWasteEditView to the contents of the specified Handle
//
//	The CWasteEditView copies the data in the Handle, so the caller retains
//	ownership of the Handle (and should dispose of it as needed)

void
CWasteEditView::SetTextHandle(
	Handle			inTextH,
	StScrpHandle	inStyleH )
{
	StHandleLocker	lock(inTextH);
	SetTextPtr(*inTextH, ::GetHandleSize(inTextH), inStyleH );
}


// ---------------------------------------------------------------------------
//	¥ SetTextPtr							[public, virtual]
// ---------------------------------------------------------------------------

void
CWasteEditView::SetTextPtr(
	   const void*		inTextP,
	   SInt32			inTextLen,
	   StScrpHandle		inStyleH )
{
	StFocusAndClipIfHidden	focus(this);
	
	if (!mMonoStyled) {
		
		StHandleBlock	styleH( (Handle) inStyleH, false);
		
		if (inStyleH == nil) {		
			// No input style. Use style of beginning of text.
			SInt32			savedStart;
			SInt32			savedEnd;
			Handle			outText = nil;
			StScrpHandle	outStyles = nil;
			
			WEGetSelection( & savedStart, & savedEnd, mWasteEditRef);
			WESetSelection( 0, 0, mWasteEditRef);
			
			// We need a StScrpHandle. Retrieve the style of the beginning of the text.
			WECopyRange(0,0,outText,outStyles,nil,mWasteEditRef) ;
			
			styleH.Adopt((Handle) outStyles);
			
			WESetSelection( savedStart, savedEnd, mWasteEditRef);
		}
		
		WEInsert(inTextP, inTextLen, (StScrpHandle) styleH.Get(), nil, mWasteEditRef ) ;
		WECalText(mWasteEditRef);
		
	} else {
		WEInsert(inTextP, inTextLen, nil, nil, mWasteEditRef ) ;
	}

	AdjustImageToText();
	Refresh();
}


// ---------------------------------------------------------------------------
//	¥ GetTextHandle							[public]
// ---------------------------------------------------------------------------
//	Return a Handle to the text in the CWasteEditView.

Handle
CWasteEditView::GetTextHandle()
{
	return static_cast<Handle>(WEGetText(mWasteEditRef));
}


// ---------------------------------------------------------------------------
//	¥ GetTextLength								[public]
// ---------------------------------------------------------------------------

SInt32
CWasteEditView::GetTextLength()
{
	return ::WEGetTextLength(mWasteEditRef);
}


// ---------------------------------------------------------------------------
//	¥ CountLines								[public]
// ---------------------------------------------------------------------------

SInt32
CWasteEditView::CountLines()
{
	return ::WECountLines(mWasteEditRef);
}


// ---------------------------------------------------------------------------
//	¥ GetLineRange								[public]
// ---------------------------------------------------------------------------

void
CWasteEditView::GetLineRange(SInt32 inLineIndex, SInt32 & outLineStart, SInt32 & outLineEnd)
{
	return ::WEGetLineRange(inLineIndex, & outLineStart, & outLineEnd, mWasteEditRef);
}


// ---------------------------------------------------------------------------
//	¥ PosToLine								[public]
// ---------------------------------------------------------------------------
// Note that Waste line numbers are 0-based 

SInt32
CWasteEditView::PosToLine(SInt32 inPos)
{
	return ::WEOffsetToLine(inPos, mWasteEditRef);
}


// ---------------------------------------------------------------------------
//	¥ CalcWEHeight							[public, virtual]
// ---------------------------------------------------------------------------
//	Calculates the height of the WasteEdit record.

SInt32
CWasteEditView::CalcWEHeight()
{
	LongRect	theDestRect ;
    WEGetDestRect(&theDestRect,mWasteEditRef);
	return WEGetHeight(0,WECountLines(mWasteEditRef),mWasteEditRef);
}


// ---------------------------------------------------------------------------
//	¥ ApplyForeAndBackColors
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


// ---------------------------------------------------------------------------
//	¥ UserChangedText						[public, virtual]
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


// ---------------------------------------------------------------------------
//	¥ GetSelection
// ---------------------------------------------------------------------------
//	Passes back an AEDesc of the currently selected text

void
CWasteEditView::GetSelection(
	AEDesc	&outDesc) const
{
	SInt32  theSelStart;
	SInt32  theSelEnd;
	Handle	currTextH = WEGetText(mWasteEditRef);
	
	WEGetSelection( & theSelStart, & theSelEnd, mWasteEditRef ) ;

	StHandleLocker lock((Handle) currTextH);

	OSErr err = ::AECreateDesc(typeChar,
							   (*currTextH + theSelStart),
							   (theSelEnd - theSelStart),
							   &outDesc);

	ThrowIfOSErr_(err);
}


// ---------------------------------------------------------------------------
//	¥ GetSelectionRange
// ---------------------------------------------------------------------------

void
CWasteEditView::GetSelectionRange(
	SInt32 & outStartPos,
	SInt32 & outEndPos)
{
	WEGetSelection(&outStartPos, &outEndPos, mWasteEditRef);
}


// ---------------------------------------------------------------------------
//	¥ SetSelectionRange
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
			saveFeature = WEFeatureFlag( weFAutoScroll, weBitClear, mWasteEditRef ) ;
		} else {
			WEGetDestRect( &oldDestRect, mWasteEditRef);	
		}
		
		WESetSelection(inStartPos, inEndPos, mWasteEditRef);
		
		if (!scrollIt) {
			WEFeatureFlag( weFAutoScroll, saveFeature, mWasteEditRef ) ;
		} else {
			ForceAutoScroll(oldDestRect);
			Refresh();
		}
	}
}


// ---------------------------------------------------------------------------
//	¥ DisplaySelectionRange
// ---------------------------------------------------------------------------

void
CWasteEditView::DisplaySelectionRange(
	SInt32	inStartPos,
	SInt32	inEndPos)
{
	if (mSelectable) {
		LongRect oldDestRect;
		
		FocusDraw();

		WEGetDestRect( &oldDestRect, mWasteEditRef);	
		
		// Bring the inEndPos in view
		WESetSelection(inEndPos, inEndPos, mWasteEditRef);
		WESelView(mWasteEditRef);
		// Select the range with inStartPos as free endpoint
		WESetSelection(inEndPos, inStartPos, mWasteEditRef);
		WESelView(mWasteEditRef);
		
		ForceAutoScroll(oldDestRect);
		Refresh();
	}
}


// ---------------------------------------------------------------------------
//	¥ SetFont									[public, virtual]
// ---------------------------------------------------------------------------
//	Given a font number, set the font

void
CWasteEditView::SetFont(
	SInt16 inFontNumber )
{
	if ( mMonoStyled )
		return;

	PostAction( new CWEViewFontAction( inFontNumber, this, this ) );
	UserChangedText();
}

// ---------------------------------------------------------------------------
//	¥ SetFont									[public, virtual]
// ---------------------------------------------------------------------------
//	Given a font name, set the font

void
CWasteEditView::SetFont(
	ConstStringPtr inFontName )
{
	if ( mMonoStyled )
		return;

	PostAction( new CWEViewFontAction( const_cast<StringPtr>(inFontName), this, this ) );
	UserChangedText();
}

// ---------------------------------------------------------------------------
//	¥ GetFont									[public, virtual]
// ---------------------------------------------------------------------------
//	Determine the font over the selection range, passing back the font number.

Boolean
CWasteEditView::GetFont(
	SInt16	&outFontNum )
{
	TextStyle theStyle;
	WEStyleMode theMode = doFont;
	Boolean isContinuous = WEContinuousStyle( &theMode, &theStyle, mWasteEditRef );

	outFontNum = theStyle.tsFont;

	return isContinuous;
}


// ---------------------------------------------------------------------------
//	¥ GetFont									[public, virtual]
// ---------------------------------------------------------------------------
//	Determine the font over the selection range, passing back the font name

Boolean
CWasteEditView::GetFont(
	Str255 outName )
{
	TextStyle theStyle;
	WEStyleMode theMode = doFont;
	Boolean isContinuous = WEContinuousStyle( &theMode, &theStyle, mWasteEditRef );

	::GetFontName( theStyle.tsFont, outName );

	return isContinuous;
}


// ---------------------------------------------------------------------------
//	¥ SetSize									[public, virtual]
// ---------------------------------------------------------------------------

void
CWasteEditView::SetSize(
	SInt16 inSize )
{
	if ( mMonoStyled )
		return;

	PostAction( new CWEViewSizeAction( inSize, this, this ) );
	UserChangedText();
}

// ---------------------------------------------------------------------------
//	¥ GetSize									[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CWasteEditView::GetSize(
	SInt16 &outSize )
{
	TextStyle theStyle;
	WEStyleMode theMode = doSize;
	Boolean isContinuous = WEContinuousStyle( &theMode, &theStyle, mWasteEditRef );

	outSize = theStyle.tsSize;

	return isContinuous;
}


// ---------------------------------------------------------------------------
//	¥ ChangeFontSizeBy							[public, virtual]
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


// ---------------------------------------------------------------------------------
//		¥ SetStyle								[public, virtual]
// ---------------------------------------------------------------------------------

void
CWasteEditView::SetStyle(
	Style	inStyle )
{
	if ( mMonoStyled )
		return;

	PostAction( new CWEViewFaceAction( inStyle, false, this, this ) );
	UserChangedText();
}


// ---------------------------------------------------------------------------------
//		¥ GetStyle								[public, virtual]
// ---------------------------------------------------------------------------------

Boolean
CWasteEditView::GetStyle(
	Style &outStyle )
{
	TextStyle	theStyle;
	WEStyleMode	theMode = doFace;
	Boolean		isContinuous = WEContinuousStyle( &theMode, &theStyle, mWasteEditRef );

	outStyle = theStyle.tsFace;
	return isContinuous;
}


// ---------------------------------------------------------------------------------
//		¥ ToggleStyleAttribute					[public, virtual]
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


// ---------------------------------------------------------------------------------
//		¥ SetAlignment							[public, virtual]
// ---------------------------------------------------------------------------------
// Alignment can work for monostyled text

void
CWasteEditView::SetAlignment(
	WEAlignment inAlign )
{
	PostAction( new CWEViewAlignAction( inAlign, this, this ) );
	UserChangedText();
}


// ---------------------------------------------------------------------------------
//		¥ GetAlignment							[public, virtual]
// ---------------------------------------------------------------------------------

WEAlignment
CWasteEditView::GetAlignment()
{
	return WEGetAlignment(mWasteEditRef);
}


// ---------------------------------------------------------------------------------
//		¥ SetColor								[public, virtual]
// ---------------------------------------------------------------------------------

void
CWasteEditView::SetColor(
	const RGBColor &inColor )
{
	// In a monostyled view, default color is black
	if ( mMonoStyled )
		return;

	PostAction( new CWEViewColorAction( inColor, this, this ) );
	UserChangedText();
}


// ---------------------------------------------------------------------------------
//		¥ GetColor								[public, virtual]
// ---------------------------------------------------------------------------------

Boolean
CWasteEditView::GetColor(
	RGBColor &outColor )
{
	TextStyle	theStyle ;
	WEStyleMode theMode = doColor;
	Boolean isContinuous = WEContinuousStyle( &theMode, &theStyle, mWasteEditRef );

	outColor = theStyle.tsColor;

	return isContinuous;
}


// ---------------------------------------------------------------------------
//	¥ SetTextTraitsID						[public, virtual]
// ---------------------------------------------------------------------------
//	Specify the resource ID of the TextTraits for a WasteEdit
//
//	This function updates the line height to fit the text characteristics.

void
CWasteEditView::SetTextTraitsID(
								ResIDT	inTextTraitsID)
{
	// text traits are not used in multistyle wasteedit
	if ( !mMonoStyled )
		return;
	
	// Get the original dest rect
	LongRect oldDestRect;
	WEGetDestRect( & oldDestRect, mWasteEditRef);	
	
	// Store the new text traits ID
	mTextTraitsID = inTextTraitsID;
	
	// Now try to apply the desired trait
	SetWETextTraits(mTextTraitsID, mWasteEditRef);
	
	SPoint32	scrollUnit;
	scrollUnit.h = 4;
	scrollUnit.v = mLineHeight;
	SetScrollUnit(scrollUnit);
	
	AlignWERects();
	AdjustImageToText();
	ForceAutoScroll(oldDestRect);
	Refresh();
}


// ---------------------------------------------------------------------------
//	¥ SetWETextTraits												  [public]
// ---------------------------------------------------------------------------
//	Set the text characteristics of a mono-styled Waste Edit View.
//	If inTextTraits is nil, the standard System font traits are used.
//

void
CWasteEditView::SetWETextTraits(
								ConstTextTraitsPtr	inTextTraits,
								WEReference			inWERef)
{
	WEAlignment		theJustification = weFlushDefault;
	short			theMode;
	RGBColor		theColor = Color_Black;
	TextStyle		theStyle ;

	// Define the attributes
	if (inTextTraits == nil) {
		// Use default System font traits
		theStyle.tsFont = systemFont,
		theStyle.tsSize = 0;
		theStyle.tsFace = 0;
		theMode = srcOr;
	} else {
		// Set characteristics from TextTraits
		// Cast away "const" here. Logically, the TextTraits Record
		// is not changed -- the font number is cached so that future
		// references will be faster.
		UTextTraits::LoadTextTraits(const_cast<TextTraitsPtr>(inTextTraits));

		theStyle.tsFont = inTextTraits->fontNumber;
		theStyle.tsSize = inTextTraits->size;
		theStyle.tsFace = (UInt8) inTextTraits->style;
		theMode = inTextTraits->mode;
		theColor = inTextTraits->color;
		theJustification = inTextTraits->justification;
	}
	
	// Set the attributes
	WESetOneAttribute(0, 0x7FFFFFFF, weTagTETextStyle,
					  & theStyle, sizeof ( theStyle ), inWERef) ;
	WESetSelection( 0, 0x7FFFFFFF, inWERef) ;
	WESetAlignment( theJustification, inWERef);
	WESetOneAttribute(0, 0x7FFFFFFF, weTagTransferMode,
					  & theMode, sizeof ( theMode ), inWERef) ;
	WESetOneAttribute( 0, 0x7FFFFFFF, weTagTextColor,
					  & theColor, sizeof ( theColor ), inWERef) ;
	
	// Calculate a default line spacing based on Font
	SetLineHeight( GetLineHeightFromStyle(theStyle) );

	// Reflow text
	WECalText(inWERef);			
}


// ---------------------------------------------------------------------------
//	¥ SetWETextTraits												  [public]
// ---------------------------------------------------------------------------
//	Set the text characteristics of a mono-style WasteEdit Record (created
//	by WENew)
//
//	A WasteEdit Record does not store the text color (it uses the
//	foreground color of the GrafPort). Pass the address of an RGBColor
//	record for the ioColor parameter if you want the color information.
//	Pass nil (the default value) if you don't want the color information.

void
CWasteEditView::SetWETextTraits(
	ResIDT		inTextTraitsID,
	WEReference	inWERef)
{
	TextTraitsRecord	traitsRec;

	UTextTraits::LoadTextTraits(inTextTraitsID, traitsRec);

	SetWETextTraits(&traitsRec, inWERef);
}


// ---------------------------------------------------------------------------
//	¥ GetLineHeightFromStyle									  [public]
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
 


// ---------------------------------------------------------------------------
//	¥ IsSelection													  [public]
// ---------------------------------------------------------------------------
// Check if selection is empty (0) or not (1).

Boolean
CWasteEditView::IsSelection() {
	SInt32  selStart;
	SInt32  selEnd;
	
	WEGetSelection( & selStart, & selEnd, mWasteEditRef ) ;
	return ( selStart != selEnd );
}


// ---------------------------------------------------------------------------
//	¥ ApplyStyleValues
// ---------------------------------------------------------------------------
// weDoMonoStyled

void
CWasteEditView::ApplyStyleValues(UInt16 theSize, UInt16 theFont)
{
	SInt32 saveStart, saveEnd;
	TextStyle theStyle;
	
	int saveBit = WEFeatureFlag( weFReadOnly, weBitClear, mWasteEditRef );
	WEGetSelection( & saveStart, & saveEnd, mWasteEditRef);
	WESetSelection( 0, 0x7FFFFFFF, mWasteEditRef );
	
	theStyle.tsSize = theSize;
	WESetStyle( weDoSize, &theStyle, mWasteEditRef );
	
	theStyle.tsFont = theFont;
	WESetStyle( weDoFont, &theStyle, mWasteEditRef );
	
	WESetSelection( saveStart, saveEnd, mWasteEditRef );
	WEFeatureFlag( weFReadOnly, saveBit, mWasteEditRef );
	
	AdjustImageToText();
	Refresh();
}


PP_End_Namespace_PowerPlant
