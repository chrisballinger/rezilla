// ===========================================================================
// CFlagPopup.cp
// 
//                       Created: 2005-03-25 15:49:17
//             Last modification: 2005-03-25 16:45:58
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CFlagPopup.h"
#include "UMiscUtils.h"

#include <LControlImp.h>
#include <LStream.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//	 CFlagPopup							Stream Constructor		  [public]
// ---------------------------------------------------------------------------

CFlagPopup::CFlagPopup(
	LStream*	inStream,
	ClassIDT	inImpID)

	: LPopupButton(inStream, inImpID)
{
	ResIDT stringListID;
	
	*inStream >> stringListID;
	
	InitFlagPopup(stringListID);
}


// ---------------------------------------------------------------------------
//	 CFlagPopup							Parameterized Constructor [public]
// ---------------------------------------------------------------------------
//	NOTE: Do not add the kControlPopupUseAddResMenuVariant to the control
//	kind. If you wish to populate the menu from items of a resource type,
//	pass the resource type in the inResTypeMENU parameter. Pass 0 for the
//	type if you don't want resource type items.

CFlagPopup::CFlagPopup(const SPaneInfo&	inPaneInfo,
					   MessageT			inValueMessage,
					   ResIDT			inStringListID)

	: LPopupButton(inPaneInfo, inValueMessage)
{
	InitFlagPopup(inStringListID);
}


// ---------------------------------------------------------------------------
//	 InitFlagPopup						Private Initializer		 [private]
// ---------------------------------------------------------------------------

void
CFlagPopup::InitFlagPopup(ResIDT inStringListID)
{
	FillPopup(inStringListID);
}


// ---------------------------------------------------------------------------
//	 CFlagPopup							Destructor				  [public]
// ---------------------------------------------------------------------------

CFlagPopup::~CFlagPopup()
{
}


#pragma mark -

// ---------------------------------------------------------------------------
//	 FillPopup													[public]
// ---------------------------------------------------------------------------
// Pass in the STR# resource containing the popup items

void
CFlagPopup::FillPopup(ResIDT inStringListID) 
{
	MenuRef    theMenuH = GetMacMenuH();
	ThrowIfNil_(theMenuH);
	
	// Empty the menu	DeleteAllMenuItems();
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
						AppendMenu(itemStr);
					}
				}
			}
		}
	}	

// 	// Finally add the "Unknown" item
// 	AppendMenu(mUnknownItem);
	
	Refresh();
}


// ---------------------------------------------------------------------------
//	¥ HotSpotResult
// ---------------------------------------------------------------------------
//	Respond to a click in the popup

void
CFlagPopup::HotSpotResult(SInt16 inHotSpot)
{
// 	Str255	theString;
// 	SInt16	index;
// 	
// 	mEditText->GetDescriptor(theString);
// 	index = AdjustPopupWithValue(theString);
// 
// 	if (index == -1) {
// 		// Pass NULL as ioParam to tell that no item was found in list
// 		BroadcastMessage(mValueMessage, NULL);
// 	} else {
// 		LBevelButton::HotSpotResult(inHotSpot);
// 	}
}


// ---------------------------------------------------------------------------
//	¥ GetValue														  [public]
// ---------------------------------------------------------------------------
//	Return the value of a Control

SInt32
CFlagPopup::GetValue() const
{
	return mValue;
}


// ---------------------------------------------------------------------------
//	¥ SetValue														  [public]
// ---------------------------------------------------------------------------
//	Specify the value for a Control
//
//	You will usually override this function to redraw the control to
//	reflect the new value setting. Normally, you'll call this function
//	at the beginning of the overriding function. For example:
//
//	void MyControl::SetValue(SInt32 inValue)
//	{
//		LControl::SetValue(inValue);
//			// ... Add code here to redraw control
//	}

void
CFlagPopup::SetValue(
	SInt32	inValue)
{
	if (inValue < mMinValue) {		// Enforce min/max range
		inValue = mMinValue;
	} else if (inValue > mMaxValue) {
		inValue = mMaxValue;
	}

	if (mValue != inValue) {		// If value is not the current value
		mValue = inValue;			//   Store new value
		BroadcastValueMessage();	//   Inform Listeners of value change
	}
}




PP_End_Namespace_PowerPlant
