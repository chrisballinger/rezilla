// ===========================================================================
// CPopupEditField.h
// 
//                       Created: 2005-03-12 07:58:12
//             Last modification: 2005-03-12 07:59:31
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
#include <LThemeTextBox.h>

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
	ResIDT		stringListID;
	Boolean		leftSide;
	
	*inStream >> popupMessage;
	*inStream >> mStringsID;
	*inStream >> leftSide;
	
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
}


// ---------------------------------------------------------------------------
// FinishCreateSelf											[protected]
// ---------------------------------------------------------------------------

void
CPopupEditField::FinishCreateSelf()
{	
	// Let the edit field listen to the popup
	mPopup->AddListener(this);
}


// ---------------------------------------------------------------------------
//	 FillPopup													[public]
// ---------------------------------------------------------------------------
// Pass in the STR# resource with the popup items.
// 
// 	SInt16 index = 1, foundIdx = -1;
// 	if (foundIdx == -1 && rightPtr != NULL && UCompareUtils::CompareStr255( (Str255 *) inValue, rightPtr) == 0) {
// 		foundIdx = index;
// 	} 
// 	index++;
// Mark the item corresponding to the value
// if (foundIdx != -1) {
// 	theBevelButton->SetCurrentMenuItem(foundIdx);						
// } else {
// 	::MacCheckMenuItem(theBevelButton->GetMacMenuH(), theBevelButton->GetCurrentMenuItem(), 0);
// }

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
	Str255	theString;
	
	if (inMessage == mPopup->GetValueMessage()) {
		SInt32		choice = *(SInt32 *) ioParam;
		Str255 *	rightPtr;
	
		::GetIndString(theString, mStringsID, choice);
		if ( UMiscUtils::SplitCaseValue(theString, &rightPtr) ) {
			SetDescriptor(*rightPtr);
		} 
		Str255 theString;
		SInt32 theGlyph;
		
		::StringToNum( *rightPtr, &theGlyph);
		// /_In Progress/_Text Classes/LThemeTextBox
// 		LThemeTextBox * theStaticText = dynamic_cast<LThemeTextBox *>(GetSuperView()->FindPaneByID(50));
// 		ThrowIfNil_( theStaticText );
// 		theString[0] = 255;
// 		for ( SInt16 index = 1; index <= 16; index++ ) {
// 			theString[index] = 32;
// 		}
// 		for ( SInt16 index = 17; index <= 255; index++ ) {
// 			theString[index] = index;
// 		}
// 		
// 		theStaticText->SetDescriptor(theString);

		return;
	} 
	
	switch (inMessage) {
		
		case msg_EditorModifiedItem: 
		// This is the message emitted by the edit fields. Check that it is
		// the correlated field.
		LEditText * theEditText = (LEditText *) GetUserCon();
		if (ioParam == theEditText) {
			theEditText->GetDescriptor(theString);
			AdjustItemWithValue(theString);
		} 
		
		break;
		
	}
}


// ---------------------------------------------------------------------------
//	 HotSpotResult
// ---------------------------------------------------------------------------
//	Respond to a click in a BevelButton

void
CPopupEditField::HotSpotResult(
	SInt16	/* inHotSpot */)
{
	// Popup Menu broadcasts message with pointer to this and 
	// selected item number
		SInt16	choice;	
// 		STmplBevelInfo theBevelInfo;

		mControlImp->GetDataTag(0, kControlBevelButtonMenuValueTag,
								sizeof(SInt16), &choice);
								mPopup->SetCurrentMenuItem(choice);						
								
// 		theBevelInfo.menuChoice = mMenuChoice;
// 		theBevelInfo.selfPtr = this;
// 		BroadcastMessage(mValueMessage, &theBevelInfo);
		BroadcastMessage(mValueMessage, this);
}


// ---------------------------------------------------------------------------
//	 AdjustItemWithValue											[public]
// ---------------------------------------------------------------------------

void
CPopupEditField::AdjustItemWithValue(Str255 inString) 
{
	SInt16		num = (SInt16) ::CountMenuItems(mPopup->GetMacMenuH());
	SInt16		foundIdx = -1;
	Str255		itemString;
	Str255 *	rightPtr;

	while (num > 0) {
		mPopup->GetMenuItemText(num, itemString);
		if (UMiscUtils::SplitCaseValue(itemString, &rightPtr)) {
			if (rightPtr != NULL && UCompareUtils::CompareStr255( (Str255 *) inString, rightPtr) == 0) {
				foundIdx = num;
				break;
			} 
		} 
		num--;
	}
	
	// Mark the item corresponding to the value or remove any mark
	if (foundIdx != -1) {
		mPopup->SetCurrentMenuItem(foundIdx);						
	} else {
		::MacCheckMenuItem(mPopup->GetMacMenuH(), mPopup->GetCurrentMenuItem(), 0);
	}
}


PP_End_Namespace_PowerPlant
