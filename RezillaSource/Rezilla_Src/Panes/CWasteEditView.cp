// ===========================================================================
// CWasteEditView.cp 
// 
// Created : 2001-09-05 18:22:04 
// Last modification : 2004-11-03 22:09:09
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

// ---------------------------------------------------------------------------
//	Class Variables

CWasteEditView *			CWasteEditView::sWasteEditViewP;


// ---------------------------------------------------------------------------
//	¥ CWasteEditView						Default Constructor		  [public]
// ---------------------------------------------------------------------------

CWasteEditView::CWasteEditView()
{
	mWordWrap = false;
	mTextAttributes = (UInt32) weAttr_Default;
	InitWasteEditView(0);
}


// ---------------------------------------------------------------------------
//	¥ CWasteEditView						Copy Constructor		  [public]
// ---------------------------------------------------------------------------

CWasteEditView::CWasteEditView(
	   const CWasteEditView&	inOriginal )
{
	CWasteEditView * outWasteEdit = new CWasteEditView();
	outWasteEdit->mTypingAction				= inOriginal.mTypingAction ;
	outWasteEdit->mWasteEditRef				= inOriginal.mWasteEditRef ;
	outWasteEdit->mTextTraitsID				= inOriginal.mTextTraitsID ;
	outWasteEdit->mTextAttributes			= inOriginal.mTextAttributes ;
	outWasteEdit->mIsDirty					= inOriginal.mIsDirty ;
	outWasteEdit->mAutoScroll				= inOriginal.mAutoScroll ;
	outWasteEdit->mOutlineHilite			= inOriginal.mOutlineHilite ;
	outWasteEdit->mMonoStyled				= inOriginal.mMonoStyled ;
	outWasteEdit->mReadOnly					= inOriginal.mReadOnly ;
	outWasteEdit->mDragAndDrop				= inOriginal.mDragAndDrop ;
	outWasteEdit->mUndo						= inOriginal.mUndo ;
	outWasteEdit->mMultipleUndo				= inOriginal.mMultipleUndo ;
	outWasteEdit->mIntCutAndPaste			= inOriginal.mIntCutAndPaste ;
	outWasteEdit->mDrawOffscreen			= inOriginal.mDrawOffscreen ;
	outWasteEdit->mInhibitRecal				= inOriginal.mInhibitRecal ;
	outWasteEdit->mInhibitRedraw			= inOriginal.mInhibitRedraw ;
	outWasteEdit->mInhibitICSupport			= inOriginal.mInhibitICSupport ;
	outWasteEdit->mInhibitColor				= inOriginal.mInhibitColor ;
	outWasteEdit->mUseTempMem				= inOriginal.mUseTempMem ;
	outWasteEdit->mNoKeyboardSync			= inOriginal.mNoKeyboardSync ;
	outWasteEdit->mWordWrap					= inOriginal.mWordWrap ;
	outWasteEdit->mSelectable				= inOriginal.mSelectable ;
	outWasteEdit->mLineHeight				= inOriginal.mLineHeight ;
	outWasteEdit->mClickLoopUPP				= inOriginal.mClickLoopUPP ;

// 	InitWasteEditView(0);
}


// ---------------------------------------------------------------------------
//	¥ CWasteEditView						Parameterized Constructor [public]
// ---------------------------------------------------------------------------

CWasteEditView::CWasteEditView(
	   LCommander *		inSuper,
	   const SPaneInfo&	inPaneInfo,
	   const SViewInfo&	inViewInfo,
	   UInt16			inTextAttributes,
	   ResIDT			inTextTraitsID,
	   Boolean			inWordWrap,
	   Boolean			inReadOnly,
	   Boolean			inSelectable)

	: LView(inPaneInfo, inViewInfo),
	  LCommander(inSuper)
{
	mReadOnly = inReadOnly;
	mWordWrap = inWordWrap;
	mSelectable = inSelectable;
	mTextAttributes = inTextAttributes;
	InitWasteEditView(inTextTraitsID);
}


// ---------------------------------------------------------------------------
//	¥ CWasteEditView						Stream Constructor		  [public]
// ---------------------------------------------------------------------------

CWasteEditView::CWasteEditView(
	LStream*	inStream)

	: LView(inStream)
{
	// The flags set in Constructor

	*inStream >> mAutoScroll;
	*inStream >> mOutlineHilite;
	*inStream >> mMonoStyled;
	*inStream >> mReadOnly;
	*inStream >> mDragAndDrop;
	*inStream >> mUndo;
	*inStream >> mMultipleUndo;
	*inStream >> mIntCutAndPaste;
	*inStream >> mDrawOffscreen;
	*inStream >> mInhibitRecal;
	*inStream >> mInhibitRedraw;
	*inStream >> mInhibitICSupport;
	*inStream >> mInhibitColor;
	*inStream >> mUseTempMem;
	*inStream >> mNoKeyboardSync;
	*inStream >> mWordWrap;
	*inStream >> mSelectable;
	
	mTextAttributes = BuildTextAttributes();
	
	ResIDT	textTraitsID;
	*inStream >> textTraitsID;

	ResIDT	initialTextID;
	*inStream >> initialTextID;
		
	InitWasteEditView(textTraitsID);

	StResource	initialTextRes(ResType_Text, initialTextID, false);

	if (initialTextRes.mResourceH != nil) {

		StResource	initialStyleRes;
		if ( !mMonoStyled ) {
			initialStyleRes.GetResource(ResType_TextStyle, initialTextID, false);
		}

		Size textLength = ::GetHandleSize(initialTextRes);

		SetTextHandle(initialTextRes,
					(StScrpHandle) initialStyleRes.mResourceH);

		WESetSelection(0, 0, mWasteEditRef);
		AlignWERects();
		AdjustImageToText();
    }
	
	// Set the readOnly option now. It has been postponed until after
	// a text resource has possibly been inserted
	WEFeatureFlag(weFReadOnly,mReadOnly,mWasteEditRef);
}


// ---------------------------------------------------------------------------
//	¥ ~CWasteEditView						Destructor				  [public]
// ---------------------------------------------------------------------------

CWasteEditView::~CWasteEditView()
{
	if ( mClickLoopUPP != nil ) {
		DisposeWEClickLoopUPP(mClickLoopUPP);
	}

	if ( mWasteEditRef != nil ) {
		WEDispose(mWasteEditRef);
		mWasteEditRef = nil;
	}

	// We don't dispose of the autoscroll callback because that would
	// affect any other CWasteEditView instances we have around.

	if (mTypingAction != nil) {			// Clean out the undo queue
		try {
			PostAction(nil);
		} catch (...) {
			// don't let the exception propagate
		}
	}
}


// ---------------------------------------------------------------------------
//	¥ InitWasteEditView												[private]
// ---------------------------------------------------------------------------
//	Private initializer

void
CWasteEditView::InitWasteEditView(
								  ResIDT inTextTraitsID )
{
	WEReference		we = nil ;
	Rect			theViewRect ;
	LongRect		theLongRect ;
	OSStatus		err = noErr ;
	
	mChangesMessage	= msg_Nothing;
	mTypingAction	= nil;
	mTextTraitsID	= inTextTraitsID;
	mClickLoopUPP	= nil;
	mIsDirty		= false;
	 
	// Retrieve the attributes set in Constructor
	UInt32  initFlags = InitWasteAttributes();

	// Set the focus on the WasteEditView
	StFocusAndClipIfHidden	focus(this);
	
	// The WE instance is created in the LView frame
	CalcPortFrameRect(theViewRect);
	WERectToLongRect( &theViewRect, &theLongRect) ;
	err = WENew( &theLongRect, &theLongRect, initFlags , &we) ;
	ThrowIfOSErr_(err);
	
	// Set the mWasteEdit data member
	SetWasteRef(we) ;
	
	// Deal with style
	if (!mMonoStyled) {
		
		// TextTraits are not used in multi-style text edit, however
		// they are used this once to set the initial text traits
		// for the WasteEdit instance.
		
		mTextTraitsID = -1;
		TextTraitsH theTxtrH = UTextTraits::LoadTextTraits(inTextTraitsID);
		
		TextStyle		theStyle;
		WEAlignment		justification = weFlushDefault;
		
		if ( theTxtrH != nil ) {
			theStyle.tsFont		= (*theTxtrH)->fontNumber;
			theStyle.tsFace		= static_cast<UInt8>((*theTxtrH)->style);
			theStyle.tsSize		= (*theTxtrH)->size;
			theStyle.tsColor	= (*theTxtrH)->color;
			justification		= (*theTxtrH)->justification;
			
			::ReleaseResource(reinterpret_cast<Handle>(theTxtrH));
		} else {
			// We'll just use some basic defaults
			
			theStyle.tsFont			= ::GetAppFont();
			theStyle.tsFace			= normal;
			theStyle.tsSize			= ::GetDefFontSize();
			theStyle.tsColor.red	= 0;
			theStyle.tsColor.green	= 0;
			theStyle.tsColor.blue	= 0;
		}

		// Set Port Font and Size so WE uses the correct
		// settings for its internal tables
		::TextFont(theStyle.tsFont);		
		::TextSize(theStyle.tsSize);
		
		// weDoAll = weDoFont | weDoFace | weDoSize | weDoColor
		WESetStyle(weDoAll,&theStyle,mWasteEditRef);
		WESetAlignment( justification, mWasteEditRef );
		
		SetLineHeight( GetLineHeightFromStyle(theStyle) );
		
	} else {
		// Set the initial text traits
		SetWETextTraits(mTextTraitsID, mWasteEditRef);
		
		SPoint32	scrollUnit;
		scrollUnit.h = 4;
		scrollUnit.v = mLineHeight;
		SetScrollUnit(scrollUnit);
	}
	
	// Deal with dimensions
	// If word wrap is on, then the Image width is always the same as the Frame
	// width, which forces text to wrap to the Frame. If  the  Image  width  is
	// zero (or negative), the user probably forgot to set it: we set the Image
	// width to the Frame width.
	if (mWordWrap || (mImageSize.width <= 0)) {
		mImageSize.width = mFrameSize.width;
	}
	
	// Outline hiliting
	WEFeatureFlag(weFOutlineHilite,mOutlineHilite,mWasteEditRef);
	
	// Initial rect was offscreen. Align it with the Frame.
	AlignWERects();
	
	// Set the clickloop
	if (mAutoScroll) {
		sWasteEditViewP = this;
// 		SetClickLoop( MyClickLoop );
	} else {
		sWasteEditViewP = nil;
	}
}


// ---------------------------------------------------------------------------
//	¥ InitWasteAttributes											  [public]
// ---------------------------------------------------------------------------
// Initialize the attributes of the WasteEditeView set in Constructor.

UInt32
CWasteEditView::InitWasteAttributes() {
	UInt32  theFlags = 0 ;
	
	theFlags |= HasAttribute(weAttr_AutoScroll) ?		weDoAutoScroll : 0 ;
	theFlags |= HasAttribute(weAttr_OutlineHilite) ?	weDoOutlineHilite : 0 ;
	theFlags |= HasAttribute(weAttr_MonoStyled) ?		weDoMonoStyled : 0 ;
// 	theFlags |= HasAttribute(weAttr_ReadOnly) ?			weDoReadOnly : 0 ;
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
//	¥ BuildTextAttributes											  [public]
// ---------------------------------------------------------------------------
// Initialize the mTextAttributes data member. Don't set the weAttr_ReadOnly
// attribute too early : if there is an initial text (from a TEXT resource), 
// it cannot be inserted if this flag is on.

UInt16
CWasteEditView::BuildTextAttributes()
{
	UInt16  theTxtAttr = 0 ;
	theTxtAttr |= mAutoScroll ?			weAttr_AutoScroll : 0 ;
	theTxtAttr |= mOutlineHilite ?		weAttr_OutlineHilite : 0 ;
	theTxtAttr |= mMonoStyled ?			weAttr_MonoStyled : 0 ;
// 	theTxtAttr |= mReadOnly ?			weAttr_ReadOnly : 0 ;
	theTxtAttr |= mDragAndDrop ?		weAttr_DragAndDrop : 0 ;
	theTxtAttr |= mUndo ?				weAttr_Undo : 0 ;
	theTxtAttr |= mMultipleUndo ?		weAttr_MultipleUndo : 0 ;
	theTxtAttr |= mIntCutAndPaste ?		weAttr_IntCutAndPaste : 0 ;
	theTxtAttr |= mDrawOffscreen ?		weAttr_DrawOffscreen : 0 ;
	theTxtAttr |= mInhibitRecal ?		weAttr_InhibitRecal : 0 ;
	theTxtAttr |= mInhibitRedraw ?		weAttr_InhibitRedraw : 0 ;
	theTxtAttr |= mInhibitICSupport ?	weAttr_InhibitICSupport : 0 ;
	theTxtAttr |= mInhibitColor ?		weAttr_InhibitColor : 0 ;
	theTxtAttr |= mUseTempMem ?			weAttr_UseTempMem : 0 ;
	theTxtAttr |= mNoKeyboardSync ?		weAttr_NoKeyboardSync : 0 ;
	
	return theTxtAttr;
}


#pragma mark -

// ---------------------------------------------------------------------------
//	¥ ClickSelf											[protected, virtual]
// ---------------------------------------------------------------------------

void
CWasteEditView::ClickSelf(
	const SMouseDownEvent	&inMouseDown)
{
	if (!mSelectable) {
		return;
	}
	
	if (!IsTarget()) {				
		// If not the Target, clicking in an WasteEdit makes it the Target
		
		// Since WEClick will set a new selection range, clear the current selection
		// range to avoid an ugly selection flash
		FocusDraw();
		
		// If autoscrolling, WESetSelection can cause autoscrolling. That means well
		// but can cause some cosmetic problems, especially if selStart is not
		// visible (you'll see a jump)
		if ( mAutoScroll )
		WEFeatureFlag( weFAutoScroll, weBitClear, mWasteEditRef );
		
		WESetSelection(0, 0, mWasteEditRef);
		
		if ( mAutoScroll )
		WEFeatureFlag( weFAutoScroll, weBitSet, mWasteEditRef );
		
		// Resync everything
		AlignWERects();
		
		// Force a redraw (to clean up the display). Draw(nil) causes a lot
		// less flicker than Refresh()
		Draw(nil);
		
		// Make ourselves the target
		SwitchTarget(this);
	}
	
	if (IsTarget()) {
		FocusDraw();
		Point	mouseLoc = inMouseDown.macEvent.where;
		
		WEClick(inMouseDown.whereLocal,
				inMouseDown.macEvent.modifiers,
				inMouseDown.macEvent.when,
				mWasteEditRef);
		LView::OutOfFocus(this);
	}
}


// // ---------------------------------------------------------------------------
// //	¥ MyClickLoop											[static, public]
// // ---------------------------------------------------------------------------
// //	This is the clikLoop callback used to help autoscrolling while
// //	selecting
// //
// //	On Classic 68K, this Toolbox callback passes its parameters in
// //	registers, so the C prototype has no function parameters.
// //
// //	On other runtimes, the callback has a WEReference parameter.
// 
// #pragma mark CWasteEditView::MyClickLoop
// 
// #if TARGET_OS_MAC && TARGET_CPU_68K && !TARGET_RT_MAC_CFM	// Classic 68K
// 
// pascal Boolean
// CWasteEditView::MyClickLoop()		// No parameters on the stack
// 
// #else
// 
// pascal Boolean
// CWasteEditView::MyClickLoop(
// 	WEReference /* inWE */)			// One parameter on the stack
// 
// #endif
// {
// 	try {
// 
// 		// Make sure we're in there to do the voodoo that this do
// 
// 		if (sWasteEditViewP != nil) {
// 			Point	where;
// 			::GetMouse( &where );
// 
// 			LongRect	theLongRect;
// 			Rect		theRect;
// 			WEGetViewRect(&theLongRect,sWasteEditViewP->GetWasteRef());
// 			WELongRectToRect( & theLongRect, & theRect) ;
// 			
// 			if ( !::MacPtInRect(where, &theRect) ) {
// 				sWasteEditViewP->ClickAutoScroll(where);
// 			}
// 		}
// 	}
// 
// 	catch (...) { }		// Can't let an exception propagate back to Toolbox
// 
// 	return true;
// }
// 
// 
// // ---------------------------------------------------------------------------
// //	¥ SetClickLoop							[public, virtual]
// // ---------------------------------------------------------------------------
// //	Allows you to specify your own clikLoop.  Disposes of the existing
// //	clikLoop, if any.  Also since the point of a clikLoop is for autoscrolling
// //	if we aren't set to autoscroll, we set that now.
// 
// #pragma mark CWasteEditView::SetClickLoop
// 
// #if TARGET_OS_MAC && TARGET_CPU_68K && !TARGET_RT_MAC_CFM	// Classic 68K
// 
// void
// CWasteEditView::SetClickLoop( void* inClickLoop )
// 
// #else
// 
// void
// CWasteEditView::SetClickLoop( WEClickLoopProcPtr inClickLoop )
// 
// #endif
// {
// 	if (inClickLoop != nil) {
// 
// 		if (mClickLoopUPP != nil) {			// Dispose of the previous clikLoop
// 			DisposeWEClickLoopUPP(mClickLoopUPP);
// 			mClickLoopUPP = nil;
// 		}
// 
// 		mClickLoopUPP = NewWEClickLoopUPP( inClickLoop );
// 		ThrowIfNil_(mClickLoopUPP);
// 
// // 		(*mWasteEditRef)->clickLoop = mClickLoopUPP;
// WESetInfo(weClickLoop,inClickLoop,mWasteEditRef);
// 
// 		WEFeatureFlag( weFAutoScroll, weBitSet, mWasteEditRef );
// 		mTextAttributes |= weAttr_AutoScroll;	// set the autoscroll bit on
// 	}
// }


// ---------------------------------------------------------------------------
//	¥ ForceAutoScroll						[protected, virtual]
// ---------------------------------------------------------------------------
//	This routine works with WasteEdit's autoscrolling capabilities
//	to keep all things (e.g. the scrollbars) in sync

void
CWasteEditView::ForceAutoScroll(
	const LongRect	&inOldDestRect)
{
	// If we're not autoscrolling, we can leave
	if (!mAutoScroll) {	
		return;
	}

	FocusDraw();

	WESelView(mWasteEditRef);			// WasteEdit autoscroll

										// Now line everything up
	LongRect	theDestRect ;
	WEGetDestRect(&theDestRect,mWasteEditRef);

	SInt32 leftDelta = inOldDestRect.left - theDestRect.left;
	SInt32 topDelta = inOldDestRect.top - theDestRect.top;

	if (leftDelta || topDelta) {
		mImageLocation.h -=  leftDelta;
		mImageLocation.v -= topDelta;
		CalcPortOrigin();
		LView::OutOfFocus(this);

 		AlignWERects();

		TArrayIterator<LPane*> iterator(mSubPanes);
		LPane*	theSub;
		while (iterator.Next(theSub)) {
			theSub->AdaptToSuperScroll(leftDelta, topDelta);
		}

		if (mSuperView) {
			mSuperView->SubImageChanged(this);
		}
	}
}


// ---------------------------------------------------------------------------
//	¥ ClickAutoScroll						[protected, virtual]
// ---------------------------------------------------------------------------
//	This is the routine ultimately used in the clikLoop to perform
//	the scrolling while clicking.

void
CWasteEditView::ClickAutoScroll(
	const Point	&inLocalPoint)
{
	LView::AutoScrollImage(inLocalPoint);

	FocusDraw();			// Since autoscrolling occurs during a Toolbox
							// callback, we need to set the focus to what
							// the Toolbox expects
}


// ---------------------------------------------------------------------------
//	¥ HandleKeyPress							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CWasteEditView::HandleKeyPress(
	const EventRecord	&inKeyEvent)
{
	Boolean		keyHandled	 = true;
	EKeyStatus	theKeyStatus = keyStatus_Input;
	SInt16		theKey		 = (SInt16) (inKeyEvent.message & charCodeMask);
	LCommander*	theTarget	 = GetTarget();

	if (inKeyEvent.modifiers & cmdKey) {	// Always pass up when the command
		theKeyStatus = keyStatus_PassUp;	//   key is down
	} else {

		theKeyStatus = UKeyFilters::PrintingCharField(inKeyEvent);
	}

	if ((theKeyStatus == keyStatus_PassUp) && (theKey == char_Return)) {
		theKeyStatus = keyStatus_Input;		// Special case for Return key
	}

	if (mReadOnly) {	// Disallow editing
		theKeyStatus = keyStatus_PassUp;
	}

	SInt32	lineCount = WECountLines(mWasteEditRef);
	LongRect	oldDestRect ;
	WEGetDestRect(&oldDestRect,mWasteEditRef);

	SInt32	theSelStart;
	SInt32	theSelEnd;
	WEGetSelection( & theSelStart, & theSelEnd, mWasteEditRef);
	
	
	StFocusAndClipIfHidden	focus(this);

	switch (theKeyStatus) {
		
		case keyStatus_Input: {
			if (mTypingAction == nil) {
				mTypingAction = new CWEViewTypingAction(mWasteEditRef, this, this);
				PostAction(mTypingAction);
			}
			
			if (mTypingAction != nil) {
				try {
					mTypingAction->InputCharacter();
				} catch(...) {
					PostAction(nil);
				}
			}
			
			WEKey(theKey,inKeyEvent.modifiers, mWasteEditRef);
			ForceAutoScroll(oldDestRect);
			
			UserChangedText();
			break;
		}
		
	  
		case keyStatus_TEDelete: {

			if (theSelEnd > 0) {
				if (mTypingAction == nil) {
					mTypingAction = new CWEViewTypingAction(mWasteEditRef, this, this);
					PostAction(mTypingAction);
				}

				if (mTypingAction != nil) {
					try {
						mTypingAction->BackwardErase();
					} catch (...) {
						PostAction(nil);
					}
				}

				WEKey(char_Backspace,inKeyEvent.modifiers, mWasteEditRef);
				ForceAutoScroll(oldDestRect);
				UserChangedText();
			}
			break;
		}

		case keyStatus_TECursor: {
			WEKey(theKey,inKeyEvent.modifiers, mWasteEditRef);
			ForceAutoScroll(oldDestRect);
			break;
		}

		case keyStatus_ExtraEdit: {
			if (theKey == char_FwdDelete) {

				if (theSelStart < WEGetTextLength(mWasteEditRef)) {
					if (mTypingAction == nil) {
						mTypingAction = new CWEViewTypingAction(mWasteEditRef, this, this);
						PostAction(mTypingAction);
					}

					if (mTypingAction != nil) {
						try {
							mTypingAction->ForwardErase();
						} catch (...) {
							PostAction(nil);
						}
					}

					if (theSelStart == theSelEnd) {
						WESetSelection(theSelStart,theSelStart + 1, mWasteEditRef);
					}

					WEDelete(mWasteEditRef);
					ForceAutoScroll(oldDestRect);
					UserChangedText();
				}
			} else {
				keyHandled = LCommander::HandleKeyPress(inKeyEvent);
			}
			break;
		}

		case keyStatus_Reject: {
			::SysBeep(1);
			break;
		}

		case keyStatus_PassUp: {
			keyHandled = LCommander::HandleKeyPress(inKeyEvent);
			break;
		}
	}

	if ((theTarget == GetTarget()) && (lineCount != WECountLines(mWasteEditRef))) {
		AdjustImageToText();
	}

	return keyHandled;
}


// ---------------------------------------------------------------------------
//	¥ ObeyCommand							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CWasteEditView::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;

	if ( mWasteEditRef == nil )
		return cmdHandled;

	LongRect	oldDestRect ;
	WEGetDestRect(&oldDestRect,mWasteEditRef);

	switch (inCommand) {

		case cmd_Cut: {
			if (!mReadOnly) {
				PostAction( new CWEViewCutAction(mWasteEditRef, this, this));
				AdjustImageToText();
				ForceAutoScroll(oldDestRect);
			}
			break;
		}

		case cmd_Copy: {
			WECopy(mWasteEditRef);
			break;
		}

		case cmd_Paste: {
			if (!mReadOnly) {
				PostAction( new CWEViewPasteAction(mWasteEditRef, this, this) );
				AdjustImageToText();
				ForceAutoScroll(oldDestRect);
			}
			break;
		}

		case cmd_Clear: {
			if (mReadOnly) {
				PostAction( new CWEViewClearAction(mWasteEditRef, this, this ));
				AdjustImageToText();
				ForceAutoScroll(oldDestRect);
			}
			break;
		}

		case cmd_ActionCut:
		case cmd_ActionPaste:
		case cmd_ActionClear:
		case cmd_ActionTyping: {
			if (mReadOnly) {
				AdjustImageToText();
				ForceAutoScroll(oldDestRect);
				UserChangedText();
			}
			break;
		}

		case cmd_ActionDeleted: {
			if (mTypingAction == static_cast<CWEViewTypingAction*>(ioParam)) {
				mTypingAction = nil;
			}
			break;
		}

		case msg_TabSelect: {
			if (!IsEnabled()) {
				cmdHandled = false;
				break;
			} // else FALL THRU to SelectAll()
		}

		case cmd_SelectAll: {
			SelectAll();
			AdjustImageToText();
			ForceAutoScroll(oldDestRect);
			break;
		}

		default:
			cmdHandled = LCommander::ObeyCommand(inCommand, ioParam);
			break;
	}

	return cmdHandled;
}


// ---------------------------------------------------------------------------
//	¥ FindCommandStatus							[public, virtual]
// ---------------------------------------------------------------------------

void
CWasteEditView::FindCommandStatus(
	CommandT	inCommand,
	Boolean		&outEnabled,
	Boolean		&outUsesMark,
	UInt16		&outMark,
	Str255		outName)
{
	outUsesMark = false;

	switch (inCommand) {

		case cmd_Copy: {			// Copy enabled if something is selected
			outEnabled = IsSelection();
			break;
		}

		case cmd_Cut:				// Cut and Clear enabled if editabled
		case cmd_Clear:	{			//   and something is selected
			outEnabled = !mReadOnly && IsSelection();
			break;
		}

		case cmd_Paste: {			// Paste enabled if editable and
									//   TEXT is on the Scrap
			outEnabled = !mReadOnly && WECanPaste(mWasteEditRef);
			break;
		}

		case cmd_SelectAll:	{		// Check if any characters are present
			outEnabled = mSelectable &&
							( WEGetTextLength(mWasteEditRef) > 0 );
			break;
		}

		default: {
			LCommander::FindCommandStatus(inCommand, outEnabled,
									outUsesMark, outMark, outName);
			break;
		}
	}
}


#pragma mark -

// ---------------------------------------------------------------------------
//	¥ Insert								[public, virtual]
// ---------------------------------------------------------------------------
//	Will optionally recalculate, autoscroll, and refresh the text if desired.

OSErr
CWasteEditView::Insert(
					   const void*		inText,
					   SInt32			inLength,
					   StScrpHandle		inStyleH,
					   Boolean			inRefresh)
{
	LongRect	oldDestRect ;
	OSErr		err;
	
	StFocusAndClipIfHidden	focus(this);

	WEGetDestRect(&oldDestRect,mWasteEditRef);
	
	if ( !mMonoStyled && (inStyleH != nil) ) {
		err = WEInsert(inText, inLength, (StScrpHandle) inStyleH, nil, mWasteEditRef ) ;
	} else {
		err = WEInsert(inText, inLength, nil, nil, mWasteEditRef);
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
//	¥ Insert								[public, virtual]
// ---------------------------------------------------------------------------

OSErr
CWasteEditView::Insert(
					   Str255 		inString,
					   Boolean		inRefresh)
{
	char * theStr = new char[256];
	CopyPascalStringToC(inString,theStr);	
	return Insert(theStr, inString[0], NULL, inRefresh);
}


// ---------------------------------------------------------------------------
//	¥ SelectAll								[public, virtual]
// ---------------------------------------------------------------------------
//	Select entire contents of a WasteEdit

void
CWasteEditView::SelectAll()
{
	if (mSelectable) {
		StFocusAndClipIfHidden	focus(this);
		int saveFeature = WEFeatureFlag( weFAutoScroll, weBitClear, mWasteEditRef ) ;
		WESetSelection( 0, 0x7FFFFFFF, mWasteEditRef ) ;
		WEFeatureFlag( weFAutoScroll, saveFeature, mWasteEditRef ) ;
	}
}


// ---------------------------------------------------------------------------
//	¥ DeleteAll								[public, virtual]
// ---------------------------------------------------------------------------
//	Delete entire contents of the WasteEdit

void
CWasteEditView::DeleteAll()
{
	if (mSelectable) {
		// Get the original dest rect
		LongRect oldDestRect;
		WEGetDestRect( &oldDestRect, mWasteEditRef);	

		SelectAll();
		WEDelete(mWasteEditRef);

		AdjustImageToText();
		ForceAutoScroll(oldDestRect);
		Refresh();
	}
}


// ---------------------------------------------------------------------------
//	¥ DeleteTextRange								[public]
// ---------------------------------------------------------------------------
// Delete the text in a specified range and update.
// If autoscrolling is on.

void
CWasteEditView::DeleteTextRange( SInt32 inStartPos, SInt32 inEndPos)
{
	if (!mReadOnly && mSelectable) {
		LongRect oldDestRect;
		WEGetDestRect( &oldDestRect, mWasteEditRef);	

		StFocusAndClipIfHidden	focus(this);
		
		int saveFeature = WEFeatureFlag( weFAutoScroll, weBitClear, mWasteEditRef ) ;
		WESetSelection( inStartPos, inEndPos, mWasteEditRef ) ;
		WEFeatureFlag( weFAutoScroll, saveFeature, mWasteEditRef ) ;

		WEDelete(mWasteEditRef);

		AdjustImageToText();
		ForceAutoScroll(oldDestRect);
		Refresh();
	} 
}


// ---------------------------------------------------------------------------
//	¥ FocusDraw								[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CWasteEditView::FocusDraw(
	LPane	*inSubPane)
{
	Boolean	focused = LView::FocusDraw(inSubPane);
	if (focused) {
		StColorPenState::Normalize();
		if ( mMonoStyled ) {
			UTextTraits::SetPortTextTraits(mTextTraitsID);
			Pattern		whitePat;
			::BackPat(UQDGlobals::GetWhitePat(&whitePat));
		}
	}

	return focused;
}


// ---------------------------------------------------------------------------
//	¥ DrawSelf								[protected, virtual]
// ---------------------------------------------------------------------------
//	Draw a WasteEdit

void
CWasteEditView::DrawSelf()
{
	Rect	theFrame;
	CalcLocalFrameRect(theFrame);
	
	ApplyForeAndBackColors();
	::EraseRect(&theFrame);

	GrafPtr	savePort;
	GrafPtr	thePort;
	if ( WEGetInfo( wePort, & savePort, mWasteEditRef ) == noErr ) {
		thePort = UQDGlobals::GetCurrentPort();
		WESetInfo( wePort, & thePort, mWasteEditRef );
		StRegion	refreshRgn(theFrame);
		WEUpdate(refreshRgn, mWasteEditRef);
		WESetInfo( wePort, & savePort, mWasteEditRef );
	}
}


// ---------------------------------------------------------------------------
//	¥ HideSelf											[protected, virtual]
// ---------------------------------------------------------------------------
//	Hide the CWasteEditView. An invisible CWasteEditView can't be OnDuty.

void
CWasteEditView::HideSelf()
{
	if (IsOnDuty()) {				// Shouldn't be on duty when invisible
		SwitchTarget(GetSuperCommander());
	}
}


// ---------------------------------------------------------------------------
//	¥ AdjustMouseSelf						[protected, virtual]
// ---------------------------------------------------------------------------
//	WasteEdit uses the standard I-Beam cursor

void
CWasteEditView::AdjustMouseSelf(
	Point				/* inPortPt */,
	const EventRecord&	/* inMacEvent */,
	RgnHandle			/* outMouseRgn */)	// In Port coords
{
	if (mSelectable) {
		UCursor::SetIBeam();
	} else {
		UCursor::SetArrow();
	}
}


// ---------------------------------------------------------------------------
//	¥ AlignWERects									[public, virtual]
// ---------------------------------------------------------------------------
//	Sync WasteEdit's view and dest rectangles with the PowerPlant LView.

void
CWasteEditView::AlignWERects()
{
	Rect	textFrame;
	if ( (mSuperView != nil) &&
			FocusDraw() &&
			CalcLocalFrameRect(textFrame)) {

		LongRect	theLongViewRect ;
		LongRect	theLongDestRect ;
		// view rect same as frame in local coords
		WERectToLongRect(&textFrame, &theLongViewRect);
		WESetViewRect(&theLongViewRect,mWasteEditRef);
		
		// dest rect same as image in local coords
		theLongDestRect.top = mImageLocation.v + mPortOrigin.v;
		theLongDestRect.left = mImageLocation.h + mPortOrigin.h;
		theLongDestRect.bottom = theLongDestRect.top + mImageSize.height;
		theLongDestRect.right = theLongDestRect.left + mImageSize.width;

		WESetDestRect(&theLongDestRect,mWasteEditRef);
		
		WECalText(mWasteEditRef);
	}	
}


// ---------------------------------------------------------------------------
//	¥ ResizeFrameBy							[public, virtual]
// ---------------------------------------------------------------------------

void
CWasteEditView::ResizeFrameBy(
	SInt16		inWidthDelta,
	SInt16		inHeightDelta,
	Boolean		inRefresh)
{
	LView::ResizeFrameBy(inWidthDelta, inHeightDelta, Refresh_No);

	// If word wrap is on, the Image width must be the same as the Frame width.
	if (mWordWrap) {
		ResizeImageTo(mFrameSize.width, mImageSize.height, Refresh_No);
	}

	AlignWERects();
	
	LView::OutOfFocus(this);

	AdjustImageToText();
	
	// It's safe to refresh now that everything is in sync
	if (inRefresh) {				
		Refresh();
	}
}


// ---------------------------------------------------------------------------
//	¥ AdjustImageToText									[public, virtual]
// ---------------------------------------------------------------------------
	
void
CWasteEditView::AdjustImageToText()
{
	ResizeImageTo(mImageSize.width,CalcWEHeight(),Refresh_No);
}


// ---------------------------------------------------------------------------
//	¥ AdaptToNewSurroundings
// ---------------------------------------------------------------------------

void
CWasteEditView::AdaptToNewSurroundings()
{
	LView::AdaptToNewSurroundings();
	
	AlignWERects();	
}


// ---------------------------------------------------------------------------
//	¥ MoveBy								[public, virtual]
// ---------------------------------------------------------------------------
//	Move the location of the Frame by the specified amounts
//
//		inHorizDelta and inVertDelta specify, in pixels, how far to move the
//		Frame (within its surrounding Image). Positive horiz deltas move to
//		the right, negative to the left. Positive vert deltas move down,
//		negative up.

void
CWasteEditView::MoveBy(
	SInt32		inHorizDelta,
	SInt32		inVertDelta,
	Boolean		inRefresh)
{
	LView::MoveBy(inHorizDelta, inVertDelta, inRefresh);
	AlignWERects();
}


// ---------------------------------------------------------------------------
//	¥ ScrollImageBy							[public, virtual]
// ---------------------------------------------------------------------------
//	Scroll the Text

void
CWasteEditView::ScrollImageBy(
	SInt32		inLeftDelta,		// Pixels to scroll horizontally
	SInt32		inTopDelta,			// Pixels to scroll vertically
	Boolean		inRefresh)
{	
	LView::ScrollImageBy(inLeftDelta, inTopDelta, Refresh_Yes);
	AlignWERects();
	if (inRefresh) {
		Refresh();
	} 
}


#pragma mark -

// ---------------------------------------------------------------------------
//	¥ ActivateSelf
// ---------------------------------------------------------------------------
//	Pane is being Activated
//
//	Override for Pane classes that change appearance when activated.

void
CWasteEditView::ActivateSelf()
{
	WEActivate(mWasteEditRef);
}



// ---------------------------------------------------------------------------
//	¥ BeTarget								[protected, virtual]
// ---------------------------------------------------------------------------
//	WasteEdit is becoming the Target

void
CWasteEditView::BeTarget()
{
	StFocusAndClipIfHidden	focus(this);

	WEActivate(mWasteEditRef);		// Show active selection

	StartIdling();					// Idle time used to flash the cursor

	sWasteEditViewP = nil;
	if ( mAutoScroll ) {
		sWasteEditViewP = this;		// Ensure we autoscroll correctly
	}
}


// ---------------------------------------------------------------------------
//	¥ DontBeTarget							[protected, virtual]
// ---------------------------------------------------------------------------
//	WasteEdit is no longer the Target
//
//	Remove WasteEdit from IdleQueue

void
CWasteEditView::DontBeTarget()
{
	StFocusAndClipIfHidden	focus(this);

	WEDeactivate(mWasteEditRef);	// Show inactive selection

	StopIdling();					// Stop flashing the cursor

	sWasteEditViewP = nil;			// To keep autoscrolling clean
}


// ---------------------------------------------------------------------------
//	¥ SpendTime								[public, virtual]
// ---------------------------------------------------------------------------
//	Idle time: blink the insertion cursor

void
CWasteEditView::SpendTime(
	const EventRecord&	/* inMacEvent */)
{
	UInt32 sleepTime = 6;
	
	if (FocusExposed() && mSelectable) {
		WEIdle(&sleepTime,mWasteEditRef);
	}
}


// ---------------------------------------------------------------------------
//	¥ ScrollToCharOffset
// ---------------------------------------------------------------------------
// Force bring a charOffset in view temporarily enabling mAutoScroll
// in case it is not set. The View understands mAutoScroll and Waste
// understands weFAutoScroll 

void
CWasteEditView::ScrollToCharOffset( SInt32	inPos )
{
	Boolean saveBool = mAutoScroll;
	int saveFeature = WEFeatureFlag( weFAutoScroll, weBitSet, mWasteEditRef ) ;
	LongRect oldDestRect ;
	
	WEGetDestRect( &oldDestRect, mWasteEditRef);
	mAutoScroll = 1;
	
	WESetSelection(inPos, inPos, mWasteEditRef);
	ForceAutoScroll(oldDestRect);
	Refresh();

	WEFeatureFlag( weFAutoScroll, saveFeature, mWasteEditRef ) ;
	mAutoScroll = saveBool;
}


// ---------------------------------------------------------------------------
//	¥ SaveStateForUndo						[protected, virtual]
// ---------------------------------------------------------------------------

SWasteEditUndoH
CWasteEditView::SaveStateForUndo()
{
	SInt32	theSelStart;
	SInt32	theSelEnd;
	WEGetSelection( & theSelStart, & theSelEnd, mWasteEditRef);

	SWasteEditUndoH	theUndoH = reinterpret_cast<SWasteEditUndoH>
									(::NewHandle(sizeof(SWasteEditUndo)));
	ThrowIfMemFail_(theUndoH);

	Handle	currTextH		= WEGetText(mWasteEditRef);
	ThrowIfOSErr_(::HandToHand(&currTextH));
	(*theUndoH)->textH		= currTextH;
	(*theUndoH)->selStart	= theSelStart;
	(*theUndoH)->selEnd		= theSelEnd;

	return theUndoH;
}


// ---------------------------------------------------------------------------
//	¥ SavePlace								[public, virtual]
// ---------------------------------------------------------------------------
// Override function in LView class

void
CWasteEditView::SavePlace(
						  LStream		*outPlace)
{
	LView::SavePlace(outPlace);
	
	LongRect	viewRect ;
	WEGetViewRect(&viewRect,mWasteEditRef);
	// 	*outPlace << viewRect;
	outPlace->WriteBlock(&viewRect,sizeof(viewRect));
	
	LongRect	destRect ;
	WEGetDestRect(&destRect,mWasteEditRef);
	// 	*outPlace << destRect;
	outPlace->WriteBlock(&destRect,sizeof(destRect));
}


// ---------------------------------------------------------------------------
//	¥ RestorePlace								[public, virtual]
// ---------------------------------------------------------------------------
// Override function in LView class

void
CWasteEditView::RestorePlace(
	LStream		*inPlace)
{
	LView::RestorePlace(inPlace);

	LongRect	theViewRect ;
// 	*inPlace >> theViewRect;
	inPlace->ReadBlock(&theViewRect,sizeof(theViewRect));
	WESetViewRect(&theViewRect,mWasteEditRef);

	LongRect	theDestRect ;
// 	*inPlace >> theDestRect;
	inPlace->ReadBlock(&theDestRect,sizeof(theDestRect));
	WESetDestRect(&theDestRect,mWasteEditRef);
}

PP_End_Namespace_PowerPlant
