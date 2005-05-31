// ===========================================================================
// CWasteEditView.cp 
// 
// Created: 2001-09-05 18:22:04 
// Last modification: 2005-05-27 09:39:18
// Author: Bernard Desgraupes 
// e-mail: <bdesgraupes@easyconnect.fr> 
// www: <http://webperso.easyconnect.fr/bdesgraupes/> 
// © Copyright: Bernard Desgraupes 2001-2004, 2005
// All rights reserved.
// $Date$
// $Revision$
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

// Class Variables
CWasteEditView * CWasteEditView::sWasteEditViewP;


// ---------------------------------------------------------------------------
//	¥ CWasteEditView						Default Constructor		  [public]
// ---------------------------------------------------------------------------

CWasteEditView::CWasteEditView()
{
	mWordWrap = false;
	mTextAttributes = (UInt32) weAttr_Default;
	
	SetPropertiesFromAttributes();
	InitView();
	InitStyle(0);
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
	
	SetPropertiesFromAttributes();
	InitView();
	InitStyle(inTextTraitsID);
}


// ---------------------------------------------------------------------------
//	¥ CWasteEditView						Parameterized Constructor [public]
// ---------------------------------------------------------------------------

CWasteEditView::CWasteEditView(
	   LCommander *		inSuper,
	   const SPaneInfo&	inPaneInfo,
	   const SViewInfo&	inViewInfo,
	   UInt16			inTextAttributes,
	   TextTraitsPtr	inTextTraitsPtr,
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
	
	SetPropertiesFromAttributes();
	InitView();
	ApplyTextTraits(inTextTraitsPtr, mWERef);
}


// ---------------------------------------------------------------------------
//	¥ CWasteEditView						Stream Constructor		  [public]
// ---------------------------------------------------------------------------

CWasteEditView::CWasteEditView(
	LStream*	inStream)

	: LView(inStream)
{
	ResIDT	textTraitsID;
	ResIDT	initialTextID;
	
	// Retrieve the flags set in Constructor
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
	*inStream >> textTraitsID;
	*inStream >> initialTextID;
		
	SetAttributesFromProperties();
	InitView();
	InitStyle(textTraitsID);
	InitText(initialTextID);
}


// ---------------------------------------------------------------------------
//	¥ ~CWasteEditView						Destructor				  [public]
// ---------------------------------------------------------------------------

CWasteEditView::~CWasteEditView()
{
	if ( mClickLoopUPP != nil ) {
		DisposeWEClickLoopUPP(mClickLoopUPP);
	}

	if ( mWERef != nil ) {
		WEDispose(mWERef);
		mWERef = nil;
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
//	¥ InitView												[private]
// ---------------------------------------------------------------------------

void
CWasteEditView::InitView()
{
	WEReference		we = nil ;
	Rect			theViewRect ;
	LongRect		theLongRect ;
	OSStatus		err = noErr ;
	
	mChangesMessage	= msg_Nothing;
	mTypingAction	= nil;
	mClickLoopUPP	= nil;
	mTextTraitsID	= -1;
	mIsDirty		= false;
	 
	// Retrieve the attributes set in Constructor
	UInt32  initFlags = FlagsFromAttributes();

	// Set the focus on the WasteEditView
	StFocusAndClipIfHidden	focus(this);
	
	// The WE instance is created in the LView frame
	CalcPortFrameRect(theViewRect);
	WERectToLongRect( &theViewRect, &theLongRect) ;
	err = WENew( &theLongRect, &theLongRect, initFlags , &we) ;
	ThrowIfOSErr_(err);
	
	// Set the mWasteEdit data member
	SetWasteRef(we) ;
	
	// If word wrap is on, then the Image width is always the same as the
	// Frame width, which forces text to wrap to the Frame. If the Image
	// width is zero (or negative), the user probably forgot to set it: we
	// set the Image width to the Frame width.
	if (mWordWrap || (mImageSize.width <= 0)) {
		mImageSize.width = mFrameSize.width;
	}
	// Outline hiliting
	WEFeatureFlag(weFOutlineHilite,mOutlineHilite,mWERef);
		
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
//	¥ InitStyle												[private]
// ---------------------------------------------------------------------------

void
CWasteEditView::InitStyle(ResIDT inTextTraitsID )
{
	SPoint32	scrollUnit;

	if (!mMonoStyled) {
		mTextTraitsID = -1;
	} else {
		mTextTraitsID = inTextTraitsID;
	}
	
	// Set the initial text traits
	ApplyTextTraits(inTextTraitsID, mWERef);

	scrollUnit.h = 4;
	scrollUnit.v = mLineHeight;
	SetScrollUnit(scrollUnit);
}


// ---------------------------------------------------------------------------
//	¥ InitText													[private]
// ---------------------------------------------------------------------------

void
CWasteEditView::InitText(ResIDT inTextID )
{
	StResource	initialTextRes(ResType_Text, inTextID, false);

	if (initialTextRes.mResourceH != nil) {
		StResource	initialStyleRes;
		Size textLength;
		
		// Just in case the doc is read-only
		int saveBit = WEFeatureFlag( weFReadOnly, weBitClear, mWERef );

		if ( !mMonoStyled ) {
			initialStyleRes.GetResource(ResType_TextStyle, inTextID, false);
		}

		textLength = ::GetHandleSize(initialTextRes);
		SetTextHandle(initialTextRes, initialStyleRes.mResourceH);

		WESetSelection(0, 0, mWERef);
		WEFeatureFlag( weFReadOnly, saveBit, mWERef );
		AlignWERects();
		AdjustImageToText();
	}
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
		
		// Since WEClick will set a new selection range, clear the current
		// selection range to avoid an ugly selection flash
		FocusDraw();
		
		// If autoscrolling, WESetSelection can cause autoscrolling. That
		// means well but can cause some cosmetic problems, especially if
		// selStart is not visible (you'll see a jump)
		if ( mAutoScroll )
			WEFeatureFlag( weFAutoScroll, weBitClear, mWERef );
		
		WESetSelection(0, 0, mWERef);
		
		if ( mAutoScroll )
			WEFeatureFlag( weFAutoScroll, weBitSet, mWERef );
		
		// Resync everything
		AlignWERects();
		
		// Force a redraw (to clean up the display). Draw(nil) causes a lot
		// less flicker than Refresh().
		Draw(nil);

		// Make ourselves the target
		SwitchTarget(this);
	}
	
	if (IsTarget()) {
		FocusDraw();
		WEClick(inMouseDown.whereLocal,
				inMouseDown.macEvent.modifiers,
				inMouseDown.macEvent.when,
				mWERef);
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
// // 		(*mWERef)->clickLoop = mClickLoopUPP;
// WESetInfo(weClickLoop,inClickLoop,mWERef);
// 
// 		WEFeatureFlag( weFAutoScroll, weBitSet, mWERef );
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

	WESelView(mWERef);			// WasteEdit autoscroll

										// Now line everything up
	LongRect	theDestRect ;
	WEGetDestRect(&theDestRect,mWERef);

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

	SInt32	lineCount = WECountLines(mWERef);
	LongRect	oldDestRect ;
	WEGetDestRect(&oldDestRect,mWERef);

	SInt32	theSelStart;
	SInt32	theSelEnd;
	WEGetSelection( & theSelStart, & theSelEnd, mWERef);
	
	
	StFocusAndClipIfHidden	focus(this);

	switch (theKeyStatus) {
		
		case keyStatus_Input: {
			if (mTypingAction == nil) {
				mTypingAction = new CWEViewTypingAction(mWERef, this, this);
				PostAction(mTypingAction);
			}
			
			if (mTypingAction != nil) {
				try {
					mTypingAction->InputCharacter();
				} catch(...) {
					PostAction(nil);
				}
			}
			
			WEKey(theKey,inKeyEvent.modifiers, mWERef);
			ForceAutoScroll(oldDestRect);
			
			UserChangedText();
			break;
		}
		
	  
		case keyStatus_TEDelete: {

			if (theSelEnd > 0) {
				if (mTypingAction == nil) {
					mTypingAction = new CWEViewTypingAction(mWERef, this, this);
					PostAction(mTypingAction);
				}

				if (mTypingAction != nil) {
					try {
						mTypingAction->BackwardErase();
					} catch (...) {
						PostAction(nil);
					}
				}

				WEKey(char_Backspace,inKeyEvent.modifiers, mWERef);
				ForceAutoScroll(oldDestRect);
				UserChangedText();
			}
			break;
		}

		case keyStatus_TECursor: {
			WEKey(theKey,inKeyEvent.modifiers, mWERef);
			ForceAutoScroll(oldDestRect);
			break;
		}

		case keyStatus_ExtraEdit: {
			if (theKey == char_FwdDelete) {

				if (theSelStart < WEGetTextLength(mWERef)) {
					if (mTypingAction == nil) {
						mTypingAction = new CWEViewTypingAction(mWERef, this, this);
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
						WESetSelection(theSelStart,theSelStart + 1, mWERef);
					}

					WEDelete(mWERef);
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

	if ((theTarget == GetTarget()) && (lineCount != WECountLines(mWERef))) {
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

	if ( mWERef == nil )
		return cmdHandled;

	LongRect	oldDestRect ;
	WEGetDestRect(&oldDestRect,mWERef);

	switch (inCommand) {

		case cmd_Cut: {
			if (!mReadOnly) {
				PostAction( new CWEViewCutAction(mWERef, this, this));
				AdjustImageToText();
				ForceAutoScroll(oldDestRect);
			}
			break;
		}

		case cmd_Copy: {
			WECopy(mWERef);
			break;
		}

		case cmd_Paste: {
			if (!mReadOnly) {
				PostAction( new CWEViewPasteAction(mWERef, this, this) );
				AdjustImageToText();
				ForceAutoScroll(oldDestRect);
			}
			break;
		}

		case cmd_Clear: {
			if (mReadOnly) {
				PostAction( new CWEViewClearAction(mWERef, this, this ));
				AdjustImageToText();
				ForceAutoScroll(oldDestRect);
			}
			break;
		}

		// These commands are invoked from CWETextActions::Redo/Undo after
		// the Redo/UndoSelf is executed
		case cmd_ActionCut:
		case cmd_ActionPaste:
		case cmd_ActionClear:
		case cmd_ActionTyping: {
			if (!mReadOnly) {
				AdjustImageToText();
				ForceAutoScroll(oldDestRect);
				UserChangedText();
			}
			break;
		}

		case cmd_ActionDeleted: {
			// This command is called from the destructor of the
			// CWEViewTypingAction
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
			outEnabled = HasSelection();
			break;
		}

		case cmd_Cut:				// Cut and Clear enabled if editabled
		case cmd_Clear:	{			//   and something is selected
			outEnabled = !mReadOnly && HasSelection();
			break;
		}

		case cmd_Paste: {			// Paste enabled if editable and
									//   TEXT is on the Scrap
			outEnabled = !mReadOnly && WECanPaste(mWERef);
			break;
		}

		case cmd_SelectAll:	{		// Check if any characters are present
			outEnabled = mSelectable &&
							( WEGetTextLength(mWERef) > 0 );
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
//	¥ FocusDraw								[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CWasteEditView::FocusDraw(
	LPane	*inSubPane)
{
	Boolean	focused = LView::FocusDraw(inSubPane);
	if (focused) {
		StColorPenState::Normalize();
		Pattern		whitePat;
		::BackPat(UQDGlobals::GetWhitePat(&whitePat));
		if ( mMonoStyled ) {
			UTextTraits::SetPortTextTraits(mTextTraitsID);
		}
	}

	return focused;
}


// ---------------------------------------------------------------------------
//	¥ DrawSelf											[protected, virtual]
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
	if ( WEGetInfo( wePort, & savePort, mWERef ) == noErr ) {
		thePort = UQDGlobals::GetCurrentPort();
		WESetInfo( wePort, & thePort, mWERef );
		StRegion	refreshRgn(theFrame);
		WEUpdate(refreshRgn, mWERef);
		WESetInfo( wePort, & savePort, mWERef );
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

		LongRect	theLongViewRect;
		LongRect	theLongDestRect;
		Rect		destRect;
		SPoint32	imagePt;
		
		// View rect same as frame in local coords
		WERectToLongRect(&textFrame, &theLongViewRect);
		WESetViewRect(&theLongViewRect,mWERef);
		
		// Dest rect same as image in local coords
// 		theLongDestRect.top = mImageLocation.v + mPortOrigin.v;
// 		theLongDestRect.left = mImageLocation.h + mPortOrigin.h;
// 		theLongDestRect.bottom = theLongDestRect.top + mImageSize.height;
// 		theLongDestRect.right = theLongDestRect.left + mImageSize.width;
		imagePt.h = imagePt.v = 0;
		ImageToLocalPoint(imagePt, topLeft(destRect));

		// Bottom of dest rect is ignored
		imagePt.h = mImageSize.width;
		ImageToLocalPoint(imagePt, botRight(destRect));

		WERectToLongRect(&destRect, &theLongDestRect);
		WESetDestRect(&theLongDestRect,mWERef);
		
		WECalText(mWERef);
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
//	¥ BeTarget								[protected, virtual]
// ---------------------------------------------------------------------------
//	WasteEdit is becoming the Target

void
CWasteEditView::BeTarget()
{
	StFocusAndClipIfHidden	focus(this);

	WEActivate(mWERef);		// Show active selection

// 	StartIdling();					// Idle time used to flash the cursor
	StartIdling( ::TicksToEventTime( ::GetCaretTime() ) );

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

	WEDeactivate(mWERef);	// Show inactive selection

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
	StColorPortState	savePortState(GetMacPort());
	
	if (mSelectable && not HasSelection() && FocusExposed()) {
		UInt32 sleepTime = 6;
		WEIdle(&sleepTime, mWERef);
		OutOfFocus(nil);
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
	int saveFeature = WEFeatureFlag( weFAutoScroll, weBitSet, mWERef ) ;
	LongRect oldDestRect ;
	
	WEGetDestRect( &oldDestRect, mWERef);
	mAutoScroll = 1;
	
	WESetSelection(inPos, inPos, mWERef);
	ForceAutoScroll(oldDestRect);
	Refresh();

	WEFeatureFlag( weFAutoScroll, saveFeature, mWERef ) ;
	mAutoScroll = saveBool;
}



PP_End_Namespace_PowerPlant
