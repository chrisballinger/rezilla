// ===========================================================================
//	CWasteEditView.h
//	
//                       Created: 2001-09-05 18:22:04
//             Last modification: 2004-06-07 09:12:53
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2001-2004
// All rights reserved.
// $Date$
// $Revision$
//	
//	Description : CWaste is a class designed to interface between 
//	the Waste Edit text engine (©1993-2000 by Marco Piovanelli)
//  and CodeWarrior's PowerPlant 2.1 library (©1993-2000 Metrowerks Inc.)
//  
// This file is part of the CWasteEditView package vs 1.6
// ===========================================================================

#ifndef _H_CWasteEditView
#define _H_CWasteEditView
#pragma once

#include <LCommander.h>
#include <LPeriodical.h>
#include <LView.h>
#include <UTextTraits.h>
#include <UCursor.h>
#include <UScrap.h>
#include <UMemoryMgr.h>
#include <UDrawingState.h>
#include <LStream.h>
#include <TArrayIterator.h>
#include <PP_Messages.h>
#include <PP_KeyCodes.h>

#include "WASTE.h"

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

// ---------------------------------------------------------------------------

enum {
	weAttr_AutoScroll		= 1 << 15,	/* 0x8000 automatically scroll the selection range into view */
	weAttr_OutlineHilite	= 1 << 14,	/* 0x4000 frame selection when deactivated */
	weAttr_MonoStyled		= 1 << 13,	/* 0x2000 disallow style changes */
	weAttr_ReadOnly			= 1 << 12,	/* 0x1000 disallow modifications */
	weAttr_DragAndDrop		= 1 << 11,	/* 0x0800 support drag-and-drop text editing */
	weAttr_Undo				= 1 << 10,	/* 0x0400 support WEUndo() */
	weAttr_MultipleUndo		= 1 << 9,	/* 0x0200 enable multiple undo/redo */
	weAttr_IntCutAndPaste	= 1 << 8,	/* 0x0100 use intelligent cut-and-paste rules */
	weAttr_DrawOffscreen	= 1 << 7,	/* 0x0080 draw text offscreen for smoother visual results */
	weAttr_InhibitRecal		= 1 << 6,	/* 0x0040 don't recalculate line starts and don't redraw text */
	weAttr_InhibitRedraw	= 1 << 5,	/* 0x0020 don't redraw text */
	weAttr_InhibitICSupport	= 1 << 4,	/* 0x0010 don't process command-clicks with Internet Config */
	weAttr_InhibitColor		= 1 << 3,	/* 0x0008 ignore color information; draw in black & white only */
	weAttr_UseTempMem		= 1 << 2,	/* 0x0004 use temporary memory for main data structures */
	weAttr_NoKeyboardSync	= 1 << 1,	/* 0x0002 disable automatic font/keyboard synchronization */
    weAttr_Default  = weAttr_AutoScroll | weAttr_OutlineHilite | weAttr_Undo | weAttr_DragAndDrop  /* 0xcc00 */
};

enum
{
	kStylePlainText			= 1,
	kStyleBold				= 2,
	kStyleItalic			= 3,
	kStyleUnderline			= 4,
	kStyleOutline			= 5,
	kStyleShadow			= 6,
	kStyleCondensed			= 7,
	kStyleExtended			= 8
};

/* defined in UTextEdit.h
 * ----------------------
 * enum {
 *     textAttr_MultiStyle         = 0x8000,
 *     textAttr_Editable           = 0x4000,
 *     textAttr_Selectable         = 0x2000,
 *     textAttr_WordWrap           = 0x1000,
 *     textAttr_AutoScroll         = 0x0800,
 *     textAttr_OutlineHilite      = 0x0400
 * };
 */

// ---------------------------------------------------------------------------
//	Macros for accessing the top-left and bottom-right corners of a LongRect

#ifndef longTopLeft
	#define longTopLeft(r)	(((LongPt *) &(r))[0])
#endif

#ifndef longBotRight
	#define longBotRight(r)	(((LongPt *) &(r))[1])
#endif

// ---------------------------------------------------------------------------

typedef struct	SWasteEditUndo {
	Handle	textH;
	SInt32	selStart;
	SInt32	selEnd;
} SWasteEditUndo, **SWasteEditUndoH;


class CWEViewTypingAction ;

// ---------------------------------------------------------------------------

class CWasteEditView :	public LView,
						public LCommander,
						public LPeriodical {
public:
	enum { class_ID = FOUR_CHAR_CODE('WeVw') };

							CWasteEditView();
							CWasteEditView(
									const CWasteEditView&	inOriginal );
							CWasteEditView(
									const SPaneInfo&	inPaneInfo,
									const SViewInfo&	inViewInfo,
									UInt16				inTextAttributes,
									ResIDT				inTextTraitsID );
							CWasteEditView(
									LStream*			inStream );
	virtual					~CWasteEditView();

	virtual Boolean			HandleKeyPress(
									const EventRecord& 	inKeyEvent);
	virtual Boolean			ObeyCommand(
									CommandT			inCommand,
									void*				ioParam);
	virtual void			FindCommandStatus(
									CommandT			inCommand,
									Boolean&			outEnabled,
									Boolean&			outUsesMark,
									UInt16&				outMark,
									Str255				outName);

	virtual	void			SpendTime(
									const EventRecord&	inMacEvent);

	virtual void			AlignWERects();
	
	virtual void			ResizeFrameBy(
									SInt16				inWidthDelta,
									SInt16				inHeightDelta,
									Boolean				inRefresh);
	virtual void			MoveBy(	SInt32				inHorizDelta,
									SInt32				inVertDelta,
									Boolean				inRefresh);
	virtual void			ScrollImageBy(
									SInt32				inLeftDelta,
									SInt32				inTopDelta,
									Boolean				inRefresh);

	virtual void			ApplyForeAndBackColors() const;
	virtual	void			ForceAutoScroll(
									const LongRect&		inOldDestRect);
	virtual	void			ClickAutoScroll(
									const Point&		inLocalPoint);

	virtual SInt32			GetValue() const;
	virtual void			SetValue(
									SInt32				inValue);

	virtual StringPtr		GetDescriptor(
									Str255				outDescriptor) const;
	virtual void			SetDescriptor(
									ConstStringPtr		inDescriptor);

	virtual void			SetTextHandle(
									Handle				inTextH,
									StScrpHandle		inStyleH = nil );
	virtual void			SetTextPtr(
									const void*			inTextP,
									SInt32				inTextLen,
									StScrpHandle 		inStyleH = nil);
	Handle					GetTextHandle();
	SInt32					GetTextLength();

	SInt32					CountLines();
	SInt32					PosToLine(SInt32 inPos);
	void					GetLineRange(SInt32 inLineIndex, 
										 SInt32 & outLineStart, 
										 SInt32 & outLineEnd);

	WEReference				GetWasteRef();
	virtual	void			SetWasteRef(WEReference inWERef);

	virtual	OSErr			Insert(	const void*			inText,
									SInt32				inLength,
									StScrpHandle		inStyleH = nil,
									Boolean				inRefresh = false );

	virtual	OSErr			Insert(
								   Str255 		inString,
								   Boolean		inRefresh );

	ResIDT					GetTextTraitsID() const;
	virtual void			SetTextTraitsID(
									ResIDT				inTextTraitsID);

	Boolean					HasAttribute(
									UInt32				inAttribute);
	UInt16					GetAttributes() const;
	void					SetAttributes(
									UInt16				inAttributes );
	UInt16					BuildTextAttributes();
	
	void					ToggleAttribute(
									UInt32				inAttribute,
									bool				inSetting );

	virtual	SInt32			CalcWEHeight();

	virtual Boolean			FocusDraw(
									LPane* 				inSubPane = nil);

	virtual void			SelectAll();
	virtual void			DeleteAll();
	virtual void			UserChangedText();

	virtual void			AdjustImageToText();

	virtual	void			GetSelection(
									AEDesc&				outDesc) const;

	virtual void			GetSelectionRange(
									SInt32 & outStartPos,
									SInt32 & outEndPos);
	
	virtual void			SetSelectionRange(
									SInt32	inStartPos,
									SInt32	inEndPos,
									Boolean scrollIt);

	virtual void			DeleteTextRange(
									SInt32				inStartPos,
									SInt32				inEndPos);

	virtual void			DisplaySelectionRange(
									SInt32	inStartPos,
									SInt32	inEndPos);

	virtual void			ScrollToCharOffset( 
									SInt32				inPos);
	
	Boolean					IsSelection();
	
	UInt32					InitWasteAttributes();
	
	virtual void			SavePlace(
									LStream* 			outPlace);

	virtual void			RestorePlace(
									LStream*			inPlace);

	virtual	void			SetFont(
									SInt16				inFontNumber );
	virtual	void			SetFont(
									ConstStringPtr		inFontName );
	virtual	Boolean			GetFont(
									SInt16&				outFontNum );
	virtual	Boolean			GetFont(
									Str255				outName );

	virtual	void			SetSize(
									SInt16				inSize );
	virtual Boolean			GetSize(
									SInt16&				outSize );
	virtual Boolean			ChangeFontSizeBy(
									SInt16				inDeltaSize );

	virtual	void			SetStyle(
									Style				inStyle );
	virtual	Boolean			GetStyle(
									Style&				outStyle );
	virtual	void			ToggleStyleAttribute(
									Style				inStyleAttr );

	virtual	void			SetAlignment(
									WEAlignment			inAlign );
	virtual	WEAlignment		GetAlignment();

	virtual	void			SetColor(
									const RGBColor&		inColor );
	virtual	Boolean			GetColor(
									RGBColor&			outColor );
		
	virtual void			SetWETextTraits(
									ConstTextTraitsPtr	inTextTraits,
									WEReference			inWERef);

	virtual void			SetWETextTraits(
									ResIDT		inTextTraitsID,
									WEReference	inWERef);

	virtual void			ActivateSelf();
	
// 	void					ApplyStylePrefs(UInt16 theSize, UInt16 theFont);
	void					ApplyStyleValues(UInt16 theSize, UInt16 theFont);

	Boolean					IsDirty() const {return mIsDirty;}
	void					SetDirty( Boolean inDirty ) {mIsDirty = inDirty;}

	SInt16					GetLineHeight() { return mLineHeight;}	
	void					SetLineHeight(SInt16 inLineHeight) {mLineHeight = inLineHeight;}
	SInt16					GetLineHeightFromStyle(TextStyle theStyle);
	
	virtual Boolean			GetReadOnly() { return mReadOnly;}
	void					SetReadOnly(Boolean inReadOnly) {mReadOnly = inReadOnly;}

	static CWasteEditView *	sWasteEditViewP;

protected:

				CWEViewTypingAction *	mTypingAction;
				WEReference				mWasteEditRef;
				ResIDT					mTextTraitsID;
				UInt16					mTextAttributes;
				Boolean					mIsDirty;
				Boolean					mAutoScroll;
				Boolean					mOutlineHilite;
				Boolean					mMonoStyled;
				Boolean					mReadOnly;
				Boolean					mDragAndDrop;
				Boolean					mUndo;
				Boolean					mMultipleUndo;
				Boolean					mIntCutAndPaste;
				Boolean					mDrawOffscreen;
				Boolean					mInhibitRecal;
				Boolean					mInhibitRedraw;
				Boolean					mInhibitICSupport;
				Boolean					mInhibitColor;
				Boolean					mUseTempMem;
				Boolean					mNoKeyboardSync;
				Boolean					mWordWrap;
				Boolean					mSelectable;
				SInt16					mLineHeight;
				WEClickLoopUPP			mClickLoopUPP;

	virtual void            DrawSelf();
	virtual void			HideSelf();

	virtual void			ClickSelf(
									const SMouseDownEvent&	inMouseDown);
	virtual void			AdjustMouseSelf(
									Point				inPortPt,
									const EventRecord&	inMacEvent,
									RgnHandle			outMouseRgn);

	virtual void			BeTarget();
	virtual void			DontBeTarget();

	virtual SWasteEditUndoH	SaveStateForUndo();

private:
			void			InitWasteEditView(
									ResIDT				inTextTraitsID );

			// defensive programming

			CWasteEditView&	operator=(
									const CWasteEditView&	inOriginal );
};


//================== INLINES =====================

// ---------------------------------------------------------------------------
//	¥ GetWasteRef							[public]
// ---------------------------------------------------------------------------
//	Return a WEReference to the Waste Edit Record associated with a 
//	CWasteEditView.
//	Caller may change record fields, and is responsible for redrawing the
//	WasteEdit as necessary to reflect any changes. However, caller must
//	not dispose of the WEReference.

inline
WEReference
CWasteEditView::GetWasteRef()
{
	return mWasteEditRef;
}

// ---------------------------------------------------------------------------
//	¥ SetWasteRef							[public]
// ---------------------------------------------------------------------------
inline
void
CWasteEditView::SetWasteRef(WEReference inWERef)
{
	mWasteEditRef = inWERef;
}


// ---------------------------------------------------------------------------
//	¥ GetTextTraitsID						[public]
// ---------------------------------------------------------------------------

inline
ResIDT
CWasteEditView::GetTextTraitsID() const
{
	return mTextTraitsID;
}


// ---------------------------------------------------------------------------
//	¥ HasAttribute							[public]
// ---------------------------------------------------------------------------
// Utility routine to determine if a given CWasteEditView has the requested
// attribute.

inline
Boolean
CWasteEditView::HasAttribute(
	UInt32 inAttribute )
{
	return ((mTextAttributes & inAttribute) != 0);
}


// ---------------------------------------------------------------------------
// 	¥ GetAttributes							[public]
// ---------------------------------------------------------------------------
//	Returns the raw attribute flags. Treat as read-only

inline
UInt16
CWasteEditView::GetAttributes() const
{
	return mTextAttributes;
}

// ---------------------------------------------------------------------------
//	¥ SetAttributes							[public]
// ---------------------------------------------------------------------------
//	Allows the setting of the attributes. This does not toggle attributes
//	but rather replaces all existing attributes with the value passed as
//	argument. If you wish to change a single attribute, use ToggleAttribute
//	instead.
//
//	Be warned that changing some attribute bits could have adverse effects
//	at runtime or no effects at all (e.g. turning off the multistyle flag
//	will not change the object to be monostyled).

inline
void
CWasteEditView::SetAttributes(
	UInt16	inAttribute )
{
	mTextAttributes = inAttribute;
}


// ---------------------------------------------------------------------------
//	¥ ToggleAttribute						[public]
// ---------------------------------------------------------------------------
//	Allows the toggling of an attribute setting. If you wish to change all
//	attributes in one call, use SetAttributes instead.
//
//	Be warned that changing some attribute bits could have adverse effects
//	at runtime or no effects at all (e.g. turning off the multistyle flag
//	will not change the object to be monostyled).

inline
void
CWasteEditView::ToggleAttribute(
	UInt32		inAttribute,
	bool		inSetting )
{
	if (inSetting) {
		mTextAttributes |= inAttribute;
	} else {
		mTextAttributes &= ~inAttribute;
	}
}


PP_End_Namespace_PowerPlant

#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
