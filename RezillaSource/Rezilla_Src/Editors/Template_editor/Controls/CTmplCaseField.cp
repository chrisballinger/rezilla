// ===========================================================================
// CTmplCaseField.cp
// 
//                       Created: 2005-03-24 11:02:01
//             Last modification: 2006-02-09 11:38:35
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2005-2006
// All rights reserved.
// ===========================================================================


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CTmplCaseField.h"
#include "RezillaConstants.h"
#include "UCompareUtils.h"
#include "UMiscUtils.h"

#include <LControlImp.h>
#include <LStaticText.h>
#include <LString.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//	 CTmplCaseField						Stream Constructor		  [public]
// ---------------------------------------------------------------------------

CTmplCaseField::CTmplCaseField(
	LStream*	inStream,
	ClassIDT	inImpID)

	: LEditText(inStream, inImpID)
{
	MessageT 	popupMessage;
	Boolean		leftSide;
	Str255		theString;
	
	*inStream >> popupMessage;
	*inStream >> leftSide;
	*inStream >> theString;
	
	SetUnknownItem(theString);
	CreatePopup(popupMessage, leftSide);
}


// ---------------------------------------------------------------------------
//	 CTmplCaseField						Parameterized Constructor [public]
// ---------------------------------------------------------------------------

CTmplCaseField::CTmplCaseField(
					const SPaneInfo&	inPaneInfo,
					LCommander*			inSuperCommander,
					ConstStringPtr		inInitialText,
					ResIDT				inTextTraitsID,
					MessageT			inMessage,
					MessageT 			inPopupMessage,
					SInt16				inMaxChars,
					UInt8				inAttributes,
					TEKeyFilterFunc		inKeyFilter,
					LHandleStream *		inTemplateStream,
					SInt32				inStartMark,
					Boolean				inLeftSide,
					bool				inPasswordField,
					ClassIDT			inImpID)
	: LEditText(inPaneInfo, inSuperCommander, inInitialText,
				inTextTraitsID, inMessage, inMaxChars, inAttributes, 
				inKeyFilter, inPasswordField, inImpID)
{
	mTemplateStream = inTemplateStream;
	mStartMark = inStartMark;
	
	SetUnknownItem("\pOther");

	CreatePopup(inPopupMessage, inLeftSide);

}


// ---------------------------------------------------------------------------
//	 ~CTmplCaseField						Destructor				  [public]
// ---------------------------------------------------------------------------

CTmplCaseField::~CTmplCaseField()
{
}


// ---------------------------------------------------------------------------
//	 CreatePopup													[public]
// ---------------------------------------------------------------------------

void
CTmplCaseField::CreatePopup(MessageT inPopupMsg, Boolean inLeftSide) 
{
	SPaneInfo	pi;
	Rect		frame;
	Str255		theString;
	
	CalcLocalFrameRect(frame);
	GetSuperView()->PortToLocalPoint(topLeft(frame));
	
	// Popup button fields basic values
	pi.width			= kCaseFieldWidth;
	pi.height			= kCaseFieldHeight;
	pi.visible			= true;
	pi.enabled			= true;
	pi.bindings.left	= false;
	pi.bindings.top		= false;
	pi.bindings.right	= false;
	pi.bindings.bottom 	= false;
	pi.userCon			= 0;
	if (inLeftSide) {
		pi.left = frame.left - kCaseFieldWidth - kCaseFieldSep;
	} else {
		pi.left = frame.left + mFrameSize.width + kCaseFieldSep;
	}
	pi.top				= frame.top + 2;
	// The PaneID should be set by the caller if necessary
	pi.paneID			= 0;  
	pi.superView		= this->GetSuperView();
	
	//	Constructor for a BevelButton with menu
	mPopup = new LBevelButton(pi, inPopupMsg, kControlBevelButtonSmallBevelProc,
							 MENU_Empty, kControlBevelButtonMenuOnBottom, 
							 kControlContentTextOnly, 0, 0, Str_Empty, 1, 
							 kControlBevelButtonPlaceNormally, teFlushDefault, 0, 
							 kControlBevelButtonAlignCenter, Point_00, true);													 
	ThrowIfNil_(mPopup);

	FillPopup();
	GetDescriptor(theString);
	AdjustPopupWithValue(theString);

	// Let the edit field listen to the popup
	mPopup->AddListener(this);
}


// ---------------------------------------------------------------------------
//	 FillPopup													[public]
// ---------------------------------------------------------------------------

void
CTmplCaseField::FillPopup() 
{
	SInt32		currMark, totalLength;
	ResType		theType;
	Str255		theString;
	Str255 * 	rightPtr;
		
	// Empty the menu
	mPopup->DeleteAllMenuItems();
	
	currMark = mStartMark;
	mTemplateStream->SetMarker(mStartMark, streamFrom_Start);
	totalLength = mTemplateStream->GetLength();
	
	while (currMark < totalLength) {
		*mTemplateStream >> theString;
		*mTemplateStream >> theType;
		if (theType != 'CASE') {
			// We went too far. Reposition the stream marker.
			mTemplateStream->SetMarker(currMark, streamFrom_Start);
			break;
		} 
		currMark = mTemplateStream->GetMarker();
		if ( UMiscUtils::SplitCaseValue(theString, &rightPtr) ) {
			mPopup->AppendMenu(theString);
		} 
	}
	
	// Finally add the "Unknown" item
	mPopup->AppendMenu(mUnknownItem);
	
	mPopup->Refresh();
}


#pragma mark -

// ---------------------------------------------------------------------------
//	 ListenToMessage				[public]
// ---------------------------------------------------------------------------

void
CTmplCaseField::ListenToMessage( MessageT inMessage, void *ioParam ) 
{	
	if (inMessage == mPopup->GetValueMessage()) {
		SInt32		choice = *(SInt32 *) ioParam;
		Str255 		theString;
		Str255 *	rightPtr;
	
		GetStringAtIndex(choice, theString);
		if ( UMiscUtils::SplitCaseValue(theString, &rightPtr) ) {
			SetDescriptor(*rightPtr);
		} else {
			SetDescriptor("\p");
		}
		
		// Tell the listeners
		BroadcastMessage(msg_EditorModifiedItem);
	} 
}


// ---------------------------------------------------------------------------
//	 GetStringAtIndex											[public]
// ---------------------------------------------------------------------------

void
CTmplCaseField::GetStringAtIndex(SInt16 inIndex, Str255 outString) 
{
	UInt16 count = ::CountMenuItems(mPopup->GetMacMenuH());
	
	if (inIndex >= count) {
		outString[0] = 0;
	} else {
		ResType		theType;
		SInt32		saveMark = mTemplateStream->GetMarker();

		mTemplateStream->SetMarker(mStartMark, streamFrom_Start);

		for (SInt16 i = 0; i < inIndex; i++) {
			*mTemplateStream >> outString;
			*mTemplateStream >> theType;
		}
		
		mTemplateStream->SetMarker(saveMark, streamFrom_Start);
	}
}


// ---------------------------------------------------------------------------
//	 AdjustPopupWithValue											[public]
// ---------------------------------------------------------------------------

SInt16
CTmplCaseField::AdjustPopupWithValue(Str255 inString) 
{
	SInt16 foundIdx = FindInPopup(inString);
	
	// Mark the item corresponding to the value or remove any mark
	if (foundIdx != -1) {
		mPopup->SetCurrentMenuItem(foundIdx);						
	} else {
		SInt16 val = mPopup->GetCurrentMenuItem();
		UInt16 count = ::CountMenuItems(mPopup->GetMacMenuH());
		mPopup->SetCurrentMenuItem(count);
		::SetItemMark(mPopup->GetMacMenuH(), val, 0);
	}
	
	return foundIdx;
}


// ---------------------------------------------------------------------------
//	 FindInPopup											[public]
// ---------------------------------------------------------------------------

SInt16
CTmplCaseField::FindInPopup(Str255 inString) 
{
	SInt16		num = (SInt16) ::CountMenuItems(mPopup->GetMacMenuH());
	SInt16		foundIdx = -1;
	SInt32		saveMark;
	ResType		theType;
	Str255		itemString;
	Str255 *	rightPtr;
	Boolean		isHex = false;
	LStr255		substStr("\p");
	
	saveMark = mTemplateStream->GetMarker();
	mTemplateStream->SetMarker(mStartMark, streamFrom_Start);
	
	// Try to be smart with hexadecimal strings: the value could 
	// start with 0x while the CASE label uses a $, or the opposite
	isHex = false;
	if (inString[0] > 0 && inString[1] == '$') {
		isHex = true;
		substStr.Assign("\p0x");
		substStr.Append(inString + 2, inString[0] - 1);
	} else if (inString[0] > 1 && inString[1] == '0' && inString[2] == 'x') {
		isHex = true;
		substStr.Assign("\p$");
		substStr.Append(inString + 3, inString[0] - 2);
	} 
	for (SInt16 i = 1; i < num; i++) {
		*mTemplateStream >> itemString;
		*mTemplateStream >> theType;
		if (UMiscUtils::SplitCaseValue(itemString, &rightPtr)) {
			if (rightPtr != NULL 
				&& ( UCompareUtils::CompareStr255( (Str255 *) inString, rightPtr) == 0
				     || 
					 (isHex && substStr.CompareTo(*rightPtr) == 0)
				)) {
				foundIdx = i;
				break;
			} 
		} 
	}
	
	mTemplateStream->SetMarker(saveMark, streamFrom_Start);
	return foundIdx;
}


// ---------------------------------------------------------------------------
//	 UserChangedText
// ---------------------------------------------------------------------------

void
CTmplCaseField::UserChangedText()
{
	Str255	theString;
	SInt16	index;
	
	GetDescriptor(theString);
	index = AdjustPopupWithValue(theString);
	if (index == -1) {
		// Pass NULL as ioParam to tell that no item was found in list
		BroadcastMessage(mValueMessage, NULL);
	} else {
		LEditText::UserChangedText();
	}
}


// ---------------------------------------------------------------------------
//	 GetUnknownItem												  [public]
// ---------------------------------------------------------------------------
// The mUnknownItem string is an item appended at the end of the menu. 
// Its purpose is to designate a value which does not correspond to any 
// value in the rest of the menu.

void
CTmplCaseField::GetUnknownItem( Str31 outString ) const
{
	LString::CopyPStr(mUnknownItem, outString);
}
		

// ---------------------------------------------------------------------------
//	 SetUnknownItem												  [public]
// ---------------------------------------------------------------------------

void
CTmplCaseField::SetUnknownItem( Str31 inString )
{
	if (inString[0] > 31) {
		inString[0] = 31;
	} 
	if (inString[0] == 0) {
		inString[0] = 1;
		inString[1] = ' ';
	} 
	LString::CopyPStr(inString, mUnknownItem);
}


// ---------------------------------------------------------------------------
//	 Disable
// ---------------------------------------------------------------------------
//	Disable both panes

void
CTmplCaseField::Disable()
{
	this->Disable();
	mPopup->Disable();
}


// ---------------------------------------------------------------------------
//	 Enable
// ---------------------------------------------------------------------------
//	Enable both panes

void
CTmplCaseField::Enable()
{
	this->Enable();
	mPopup->Enable();
}


// ---------------------------------------------------------------------------
//	 Show
// ---------------------------------------------------------------------------
//	Show both panes

void
CTmplCaseField::Show()
{
	this->Show();
	mPopup->Show();
}


// ---------------------------------------------------------------------------
//	 Hide
// ---------------------------------------------------------------------------
//	Hide both panes

void
CTmplCaseField::Hide()
{
	this->Hide();
	mPopup->Hide();
}


// ---------------------------------------------------------------------------
//   ResizeFrameBy
// ---------------------------------------------------------------------------
//	Change the Frame size by the specified amounts

void
CTmplCaseField::ResizeFrameBy(
	SInt16		inWidthDelta,
	SInt16		inHeightDelta,
	Boolean		inRefresh)
{
	LPane::ResizeFrameBy(inWidthDelta, inHeightDelta, inRefresh);
	if (inWidthDelta != 0) {
		mPopup->MoveBy(inWidthDelta, 0, inRefresh);
	} 
}



PP_End_Namespace_PowerPlant
