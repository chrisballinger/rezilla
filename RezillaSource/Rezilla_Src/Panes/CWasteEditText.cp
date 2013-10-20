// ===========================================================================
// CWasteEditText.cp
// 
// Created: 2001-09-05 18:22:04 
// Last modification: 2004-11-10 17:11:41
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
#ifndef __MACH__
#include <Quickdraw.h>
#include <Sound.h>
#endif

#include "CWasteEditView.h"
#include "CWEViewActions.h"

PP_Begin_Namespace_PowerPlant


#pragma mark -


// ---------------------------------------------------------------------------
//   Insert								[public, virtual]
// ---------------------------------------------------------------------------
//	Will optionally recalculate, autoscroll, and refresh the text if desired.

OSErr
CWasteEditView::Insert(
					   const void*		inText,
					   SInt32			inLength,
					   Handle			inStyleH,
					   Boolean			inRefresh)
{
	LongRect	oldDestRect ;
	OSErr		err;
	ItemCount	count;

	StFocusAndClipIfHidden	focus(this);

	WEGetDestRect(&oldDestRect,mWERef);
	
	if ( !mMonoStyled && (inStyleH != nil) ) {
		FlavorType	theType = kTypeStyles;

		count = 1;
		err = WEPut( kCurrentSelection, kCurrentSelection, inText, inLength, kTextEncodingMultiRun,
					kNilOptions, count, &theType, &inStyleH, mWERef ) ;
	} else {
		count = 0;
		err = WEPut( kCurrentSelection, kCurrentSelection, inText, inLength, kTextEncodingMultiRun,
					kNilOptions, count, nil, nil, mWERef ) ;
	}
	
	// Force a redraw. The WasteEdit internals are updated, so we need to
	// reflect this fact.
	if ( inRefresh ) {
		AdjustImageToText();
		ForceAutoScroll( oldDestRect );
		Refresh();
	}
	return err;
}


// ---------------------------------------------------------------------------
//   Insert								[public, virtual]
// ---------------------------------------------------------------------------

OSErr
CWasteEditView::Insert(
					   Str255 		inString,
					   Boolean		inRefresh)
{
	char * theStr = new char[256];
	CopyPascalStringToC(inString, theStr);	
	return Insert(theStr, inString[0], NULL, inRefresh);
}


// ---------------------------------------------------------------------------
//   DeleteTextRange								[public]
// ---------------------------------------------------------------------------
// Delete the text in a specified range and update.
// If autoscrolling is on.

void
CWasteEditView::DeleteTextRange( SInt32 inStartPos, SInt32 inEndPos)
{
	if (!mReadOnly && mSelectable) {
		LongRect oldDestRect;
		WEGetDestRect( &oldDestRect, mWERef);	

		StFocusAndClipIfHidden	focus(this);
		
		int saveFeature = WEFeatureFlag( weFAutoScroll, weBitClear, mWERef ) ;
		WESetSelection( inStartPos, inEndPos, mWERef ) ;
		WEFeatureFlag( weFAutoScroll, saveFeature, mWERef ) ;

		WEDelete(mWERef);

		AdjustImageToText();
		ForceAutoScroll(oldDestRect);
		Refresh();
	} 
}


// ---------------------------------------------------------------------------
//   DeleteAll								[public, virtual]
// ---------------------------------------------------------------------------
//	Delete entire contents of the WasteEdit

void
CWasteEditView::DeleteAll()
{
	if (mSelectable) {
		// Get the original dest rect
		LongRect oldDestRect;
		WEGetDestRect( &oldDestRect, mWERef);	

		SelectAll();
		WEDelete(mWERef);

		AdjustImageToText();
		ForceAutoScroll(oldDestRect);
		Refresh();
	}
}


#pragma mark -

// ---------------------------------------------------------------------------
//   SetTextTraitsID						[public, virtual]
// ---------------------------------------------------------------------------
// Specify the resource ID of the TextTraits for a WasteEdit
// 
// This function updates the line height to fit the text characteristics.

void
CWasteEditView::SetTextTraitsID(ResIDT	inTextTraitsID)
{
	// Text traits are not used in multistyle WasteEditViews
	if ( !mMonoStyled )
		return;
	
	// Get the original dest rect
	LongRect oldDestRect;
	WEGetDestRect( & oldDestRect, mWERef);	
	
	// Store the new text traits ID
	mTextTraitsID = inTextTraitsID;
	
	// Now try to apply the desired trait
	ApplyTextTraits(mTextTraitsID, mWERef);
	
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
//   ApplyTextTraits												  [public]
// ---------------------------------------------------------------------------
//	Set the text characteristics of a mono-style WasteEdit Record (created
//	by WENew)
//
//	A WasteEdit Record does not store the text color (it uses the
//	foreground color of the GrafPort). Pass the address of an RGBColor
//	record for the ioColor parameter if you want the color information.
//	Pass nil (the default value) if you don't want the color information.

void
CWasteEditView::ApplyTextTraits(
	ResIDT		inTextTraitsID,
	WEReference	inWERef)
{
	TextTraitsRecord	traitsRec;

	UTextTraits::LoadTextTraits(inTextTraitsID, traitsRec);

	ApplyTextTraits(&traitsRec, inWERef);
}


// ---------------------------------------------------------------------------
//   ApplyTextTraits												  [public]
// ---------------------------------------------------------------------------
//	Set the text characteristics of a mono-styled Waste Edit View.
//	If inTextTraits is nil, the standard System font traits are used.

void
CWasteEditView::ApplyTextTraits(TextTraitsPtr	inTextTraits,
								WEReference			inWERef)
{
	WEAlignment		theJustification = weFlushDefault;
	short			theMode;
	RGBColor		theColor = Color_Black;
	TextStyle		theStyle ;
	
	// Define the attributes
	if (inTextTraits == nil) {
		// Use default font settings
		theStyle.tsFont = ::GetAppFont();
		theStyle.tsSize = ::GetDefFontSize();
		theStyle.tsFace = 0;
		theMode = srcOr;  // not srcCopy otherwise hiliting is incorrect
	} else {
		// Set characteristics from TextTraits. The font number is cached
		// in the TextTraits so that future references will be faster.
		UTextTraits::LoadTextTraits(inTextTraits);
		
		theStyle.tsFont = inTextTraits->fontNumber;
		theStyle.tsSize = inTextTraits->size;
		theStyle.tsFace = (UInt8) inTextTraits->style;
		theMode = inTextTraits->mode;
		theColor = inTextTraits->color;
		theJustification = inTextTraits->justification;
	}
	
	// Set Port Font and Size so WE uses the correct
	// settings for its internal tables. Not sure we need that.
	::TextFont(theStyle.tsFont);		
	::TextSize(theStyle.tsSize);
	
	// Set the attributes
	// weDoAll = weDoFont | weDoFace | weDoSize | weDoColor
	WESetStyle(weDoAll,&theStyle,mWERef);
	WESetAlignment( theJustification, mWERef );
	WESetOneAttribute(0, 0x7FFFFFFF, weTagTransferMode, & theMode, sizeof ( theMode ), inWERef) ;
	WESetOneAttribute( 0, 0x7FFFFFFF, weTagTextColor, & theColor, sizeof ( theColor ), inWERef) ;
	
	// Calculate a default line spacing based on Font
	SetLineHeight( GetLineHeightFromStyle(theStyle) );
	
	// Reflow text
	WECalText(inWERef);			
}


#pragma mark -

// ---------------------------------------------------------------------------
//   SetTextHandle							[public, virtual]
// ---------------------------------------------------------------------------
//	Set the text in the CWasteEditView to the contents of the specified Handle
//
//	The CWasteEditView copies the data in the Handle, so the caller retains
//	ownership of the Handle (and should dispose of it as needed)

void
CWasteEditView::SetTextHandle(
	Handle			inTextH,
	Handle			inStyleH )
{
	StHandleLocker	lock(inTextH);
	SetTextPtr(*inTextH, ::GetHandleSize(inTextH), inStyleH );
}


// ---------------------------------------------------------------------------
//   SetTextPtr							[public, virtual]
// ---------------------------------------------------------------------------

void
CWasteEditView::SetTextPtr(
	   const void*		inTextP,
	   SInt32			inTextLen,
	   Handle			inStyleH )
{
	StFocusAndClipIfHidden	focus(this);
	OSErr		err;
	ItemCount	count;
	
	if (!mMonoStyled) {
		FlavorType	theType = kTypeStyles;
		Handle		outStyle;
		
		StHandleBlock	styleH( (Handle) inStyleH, false);
		
		if (inStyleH == nil) {		
			// No input style. Use style of beginning of text.
			SInt32			savedStart;
			SInt32			savedEnd;
			
			
			WEGetSelection( & savedStart, & savedEnd, mWERef);
			WESetSelection( 0, 0, mWERef);
			
			// Retrieve the style of the beginning of the text
			outStyle = ::NewHandle(0);
			WEStreamRange( 0, 0, kTypeStyles, kNilOptions, outStyle, mWERef);

			styleH.Adopt(outStyle);
			
			WESetSelection( savedStart, savedEnd, mWERef);
		}
		
		count = 1;
		err = WEPut( kCurrentSelection, kCurrentSelection, inTextP, inTextLen, kTextEncodingMultiRun,
					kNilOptions, count, &theType, &outStyle, mWERef ) ;
		WECalText(mWERef);
		
	} else {
		count = 0;
		err = WEPut( kCurrentSelection, kCurrentSelection, inTextP, inTextLen, kTextEncodingMultiRun,
					kNilOptions, count, nil, nil, mWERef ) ;
	}

	AdjustImageToText();
	Refresh();
}


// ---------------------------------------------------------------------------
//   GetTextHandle							[public]
// ---------------------------------------------------------------------------
//	Return a Handle to the text in the CWasteEditView.

Handle
CWasteEditView::GetTextHandle()
{
	return static_cast<Handle>(WEGetText(mWERef));
}


#pragma mark -

// ---------------------------------------------------------------------------
//   SetFont									[public, virtual]
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
//   SetFont									[public, virtual]
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
//   GetFont									[public, virtual]
// ---------------------------------------------------------------------------
//	Determine the font over the selection range, passing back the font number.

Boolean
CWasteEditView::GetFont(
	SInt16	&outFontNum )
{
	TextStyle theStyle;
	WEStyleMode theMode = doFont;
	Boolean isContinuous = WEContinuousStyle( &theMode, &theStyle, mWERef );

	outFontNum = theStyle.tsFont;

	return isContinuous;
}


// ---------------------------------------------------------------------------
//   GetFont									[public, virtual]
// ---------------------------------------------------------------------------
//	Determine the font over the selection range, passing back the font name

Boolean
CWasteEditView::GetFont(
	Str255 outName )
{
	TextStyle theStyle;
	WEStyleMode theMode = doFont;
	Boolean isContinuous = WEContinuousStyle( &theMode, &theStyle, mWERef );

	::GetFontName( theStyle.tsFont, outName );

	return isContinuous;
}


// ---------------------------------------------------------------------------
//   SetSize									[public, virtual]
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
//   GetSize									[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CWasteEditView::GetSize(
	SInt16 &outSize )
{
	TextStyle theStyle;
	WEStyleMode theMode = doSize;
	Boolean isContinuous = WEContinuousStyle( &theMode, &theStyle, mWERef );

	outSize = theStyle.tsSize;

	return isContinuous;
}


// ---------------------------------------------------------------------------------
//   SetStyle								[public, virtual]
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
//   GetStyle								[public, virtual]
// ---------------------------------------------------------------------------------

Boolean
CWasteEditView::GetStyle(
	Style &outStyle )
{
	TextStyle	theStyle;
	WEStyleMode	theMode = doFace;
	Boolean		isContinuous = WEContinuousStyle( &theMode, &theStyle, mWERef );

	outStyle = theStyle.tsFace;
	return isContinuous;
}


// ---------------------------------------------------------------------------------
//   SetAlignment							[public, virtual]
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
//   GetAlignment							[public, virtual]
// ---------------------------------------------------------------------------------

WEAlignment
CWasteEditView::GetAlignment()
{
	return WEGetAlignment(mWERef);
}


// ---------------------------------------------------------------------------------
//   SetColor								[public, virtual]
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
//   GetColor								[public, virtual]
// ---------------------------------------------------------------------------------

Boolean
CWasteEditView::GetColor(
	RGBColor &outColor )
{
	TextStyle	theStyle ;
	WEStyleMode theMode = doColor;
	Boolean isContinuous = WEContinuousStyle( &theMode, &theStyle, mWERef );

	outColor = theStyle.tsColor;

	return isContinuous;
}



PP_End_Namespace_PowerPlant
