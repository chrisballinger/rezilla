// ===========================================================================
// CPopupEditField.h
// 
//                       Created: 2005-03-12 07:58:12
//             Last modification: 2005-03-24 10:57:29
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
// Subclass only to broadcast the pointer to "this" instead of the value of
// the control.


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CPopupEditField.h"
#include "RezillaConstants.h"
#include "UCompareUtils.h"
#include "UMiscUtils.h"

#include <LControlImp.h>
#include <LStaticText.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//	 CPopupEditField						Stream Constructor		  [public]
// ---------------------------------------------------------------------------

CPopupEditField::CPopupEditField(
	LStream*	inStream,
	ClassIDT	inImpID)

	: LEditText(inStream, inImpID)
{
	MessageT 	popupMessage;
	Boolean		leftSide;
	Str255		theString;
	
	*inStream >> popupMessage;
	*inStream >> mStringsID;
	*inStream >> leftSide;
	*inStream >> theString;
	
	SetUnknownItem(theString);
	CreatePopup(popupMessage, leftSide);
}


// ---------------------------------------------------------------------------
//	 CPopupEditField						Parameterized Constructor [public]
// ---------------------------------------------------------------------------

CPopupEditField::CPopupEditField(
					const SPaneInfo&	inPaneInfo,
					LCommander*			inSuperCommander,
					ConstStringPtr		inInitialText,
					ResIDT				inTextTraitsID,
					MessageT			inMessage,
					MessageT 			inPopupMessage,
					SInt16				inMaxChars,
					UInt8				inAttributes,
					TEKeyFilterFunc		inKeyFilter,
					ResIDT				inStringListID,
					Boolean				inLeftSide,
					bool				inPasswordField,
					ClassIDT			inImpID)
	: LEditText(inPaneInfo, inSuperCommander, inInitialText,
				inTextTraitsID, inMessage, inMaxChars, inAttributes, 
				inKeyFilter, inPasswordField, inImpID)
{
	mStringsID = inStringListID;
	SetUnknownItem("\pUnknown");
	CreatePopup(inPopupMessage, inLeftSide);
}


// ---------------------------------------------------------------------------
//	 ~CPopupEditField						Destructor				  [public]
// ---------------------------------------------------------------------------

CPopupEditField::~CPopupEditField()
{
}


// ---------------------------------------------------------------------------
//	 CreatePopup													[public]
// ---------------------------------------------------------------------------

void
CPopupEditField::CreatePopup(MessageT inPopupMsg, Boolean inLeftSide) 
{
	SPaneInfo	pi;
	Rect		frame;
	
	CalcLocalFrameRect(frame);
	GetSuperView()->PortToLocalPoint(topLeft(frame));
	
	// Popup button fields basic values
	pi.width			= kPopupEditWidth;
	pi.height			= kPopupEditHeight;
	pi.visible			= true;
	pi.enabled			= true;
	pi.bindings.left	= false;
	pi.bindings.top		= false;
	pi.bindings.right	= false;
	pi.bindings.bottom 	= false;
	pi.userCon			= 0;
	if (inLeftSide) {
		pi.left = frame.left - kPopupEditWidth - kPopupEditSep;
	} else {
		pi.left = frame.left + mFrameSize.width + kPopupEditSep;
	}
	pi.top				= frame.top + 2;
	pi.paneID			= 0;  // or mPaneID + 1
	pi.superView		= this->GetSuperView();
	
	//	Constructor for a BevelButton with menu
	mPopup = new LBevelButton(pi, inPopupMsg, kControlBevelButtonSmallBevelProc,
							 MENU_Empty, kControlBevelButtonMenuOnBottom, 
							 kControlContentTextOnly, 0, 0, Str_Empty, 1, 
							 kControlBevelButtonPlaceNormally, teFlushDefault, 0, 
							 kControlBevelButtonAlignCenter, Point_00, true);													 
	ThrowIfNil_(mPopup);

	FillPopup(mStringsID);
	
	// Let the edit field listen to the popup
	mPopup->AddListener(this);
}


// ---------------------------------------------------------------------------
//	 FillPopup													[public]
// ---------------------------------------------------------------------------
// Pass in the STR# resource containing the popup items

void
CPopupEditField::FillPopup(ResIDT inStringListID) 
{
	MenuRef    theMenuH = mPopup->GetMacMenuH();
	ThrowIfNil_(theMenuH);
	
	// Empty the menu	mPopup->DeleteAllMenuItems();
	UInt16 theCount = ::CountMenuItems( theMenuH );
	while ( theCount > 0 ) {	
		::DeleteMenuItem( theMenuH, theCount-- );
	}
	
	StResource	stringListH(FOUR_CHAR_CODE('STR#'), inStringListID, false, false);

	if ((stringListH.mResourceH != nil)) {
		SInt16		count = * (SInt16*) *stringListH.mResourceH;

		if ( count > 0 ) {
			Str255		itemStr;
			Str255 *	rightPtr;
			
			for ( SInt16 index = 1; index <= count; index++ ) {
				// Get the string from the list
				::GetIndString ( itemStr, inStringListID, index );
				
				// Ignore empty items
				if ( itemStr[0] ) {
					if ( UMiscUtils::SplitCaseValue(itemStr, &rightPtr) ) {
						mPopup->AppendMenu(itemStr);
					}
				}
			}
		}
	}	

	// Finally add the Unknown item
	mPopup->AppendMenu(mUnknownItem);

	mPopup->SetMacMenuH(theMenuH);
	
	mPopup->Refresh();
}


#pragma mark -

// ---------------------------------------------------------------------------
//	 ListenToMessage				[public]
// ---------------------------------------------------------------------------

void
CPopupEditField::ListenToMessage( MessageT inMessage, void *ioParam ) 
{	
	if (inMessage == mPopup->GetValueMessage()) {
		SInt32		choice = *(SInt32 *) ioParam;
		Str255 		theString;
		Str255 *	rightPtr;
	
		::GetIndString(theString, mStringsID, choice);
		if ( UMiscUtils::SplitCaseValue(theString, &rightPtr) ) {
			SetDescriptor(*rightPtr);
		} else {
			SetDescriptor("\p");
		}
		
		return;
	} 
}


// ---------------------------------------------------------------------------
//	 AdjustPopupWithValue											[public]
// ---------------------------------------------------------------------------

SInt16
CPopupEditField::AdjustPopupWithValue(Str255 inString) 
{
	SInt16 foundIdx = FindInPopup(inString);
	
	// Mark the item corresponding to the value or remove any mark
	if (foundIdx != -1) {
		mPopup->SetCurrentMenuItem(foundIdx);						
	} else {
		SInt16 val = mPopup->GetCurrentMenuItem();
		UInt16 count = ::CountMenuItems(mPopup->GetMacMenuH());
		mPopup->SetCurrentMenuItem(count);
// 		::MacCheckMenuItem(mPopup->GetMacMenuH(), mPopup->GetCurrentMenuItem(), 0);
		::SetItemMark(mPopup->GetMacMenuH(), val, 0);
	}
	
	return foundIdx;
}


// ---------------------------------------------------------------------------
//	 FindInPopup											[public]
// ---------------------------------------------------------------------------

SInt16
CPopupEditField::FindInPopup(Str255 inString) 
{
	SInt16		num = (SInt16) ::CountMenuItems(mPopup->GetMacMenuH());
	SInt16		foundIdx = -1;
	Str255		itemString;
	Str255 *	rightPtr;

	while (num > 0) {
		::GetIndString(itemString, mStringsID, num);
		if (UMiscUtils::SplitCaseValue(itemString, &rightPtr)) {
			if (rightPtr != NULL && UCompareUtils::CompareStr255( (Str255 *) inString, rightPtr) == 0) {
				foundIdx = num;
				break;
			} 
		} 
		num--;
	}
	
	return foundIdx;
}


// ---------------------------------------------------------------------------
//	¥ UserChangedText
// ---------------------------------------------------------------------------

void
CPopupEditField::UserChangedText()
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
//	¥ GetUnknownItem												  [public]
// ---------------------------------------------------------------------------
// The mUnknownItem string is a menu item appended at the end of the menu. 
// Its purpose is to designate a value which does not correspond to any 
// value in the rest of the menu.

void
CPopupEditField::GetUnknownItem( Str31 outString ) const
{
	LString::CopyPStr(mUnknownItem, outString);
}
		

// ---------------------------------------------------------------------------
//	¥ SetUnknownItem												  [public]
// ---------------------------------------------------------------------------

void
CPopupEditField::SetUnknownItem( Str31 inString )
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


PP_End_Namespace_PowerPlant
