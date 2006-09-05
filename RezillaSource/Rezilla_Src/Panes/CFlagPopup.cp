// ===========================================================================
// CFlagPopup.cp
// 
//                       Created: 2005-03-25 15:49:17
//             Last modification: 2005-07-04 10:51:04
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2005
// All rights reserved.
// ===========================================================================
//  Popup menu designed to handle flag values (base-2 additive values like
//  0, 1, 2, 4, 8, etc.). The menu items should be stored in a STR# resource
//  using the same format as the CASE tags in templates. For instance:
// 				resource 'STR#' (0) {
// 					{	
// 					"Plain=0",
// 					"Bold=1",
// 					"Italic=2",
// 					"Underline=4",
// 					"Outline=8",
// 					"Shadow=16",
// 					"Condensed=32",
// 					"Extended=64"
// 					}
// 				};
// 	It is not necessary that the elements be ordered or that all values be
// 	present. One can select several items in the menu but the item with the
// 	0 value has the effect of resetting the entire menu, deselecting all
// 	the others. The value returned by GetFlagValue() is the cumulated
// 	value corresponding to all the selected items. The SetFlagValue()
// 	function does the opposite. For instance SetFlagValue(13) would
// 	correspond to the selection of the Bold, Underline and Outline items 
// 	(13 = 1+4+8).
// 	For faster retrieval, the class maintains an array of the values 
// 	corresponding to each element and stores the index corresponding to 
// 	the nul flag value. 

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CFlagPopup.h"
#include "UMiscUtils.h"
#include "RezillaConstants.h"

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
	UInt32	initialValue;
	
	*inStream >> mStringListID;
	*inStream >> initialValue;
	
	InitFlagPopup();
	FillPopup(mStringListID);
	UpdatePopupWithValue(initialValue);
}


// ---------------------------------------------------------------------------
//	 CFlagPopup							Parameterized Constructor [public]
// ---------------------------------------------------------------------------
//	NOTE: Do not add the kControlPopupUseAddResMenuVariant to the control
//	      kind. If you wish to populate the menu from items of a resource
//	      type, pass the resource type in the inResTypeMENU parameter. Pass
//	      0 for the type if you don't want resource type items.
//	      
//	A value 0 for inStringListID means that the popup does not use an
//	STR# resource. In that case, it is built by the caller using
//	AppendCase().

CFlagPopup::CFlagPopup(const SPaneInfo&	inPaneInfo,
					   MessageT			inValueMessage,
					   ResIDT			inStringListID)

	: LPopupButton(inPaneInfo, inValueMessage, 0, MENU_EmptyPopup)
{
	mStringListID = inStringListID;
	
	InitFlagPopup();
	if (mStringListID != 0) {
		FillPopup(mStringListID);
	} 
}


// ---------------------------------------------------------------------------
//	 InitFlagPopup						Private Initializer		 [private]
// ---------------------------------------------------------------------------

void
CFlagPopup::InitFlagPopup()
{
	mResetIndex = -1;

	// First item is blank, second is a separator
	AppendMenu("\p ");
	AppendMenu("\p-");
	mNumTopItems = 2;
	
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
	SInt16	count;
	
	// Empty the menu
	DeleteAllMenuItems();
	
	StResource	stringListH(FOUR_CHAR_CODE('STR#'), inStringListID, false, false);

	if ((stringListH.mResourceH != nil)) {
		count = * (SInt16*) *stringListH.mResourceH;

		if ( count > 0 ) {
			Str255		itemStr;
			
			for ( SInt16 i = 1; i <= count; i++ ) {
				// Get the string from the list resource
				::GetIndString( itemStr, inStringListID, i );
				// Append it to the menu
				AppendCase(itemStr);
			}
		}
	}	

	SetMinValue(0);
	SetMaxValue(count+mNumTopItems);
	Refresh();
}


// ---------------------------------------------------------------------------
//	 AppendCase
// ---------------------------------------------------------------------------

void
CFlagPopup::AppendCase(Str255 inString)
{
	Str255 *	rightPtr;
	SInt32		theValue = 0;
	UInt8 offset, rightLen;
	int i;

	// Ignore empty items
	if ( inString[0] ) {
		if ( UMiscUtils::SplitCaseValue(inString, &rightPtr) ) {
			// ZP feature #2: make CASE tags after B/W/LORV accept
			// hexadecimal on top of decimal, because filling templates with
			// values like 2147483648 is NOT satisfying. As always, hex can begin
			// by $, 0x, or 0X, all are recognised.
			if ( ((*rightPtr)[0]>=1 && (*rightPtr)[1]=='$')
			  || ((*rightPtr)[0]>=2 && (*rightPtr)[1]=='0' &&
	                                  ((*rightPtr)[2]=='x' || (*rightPtr)[2]=='X') ) )
			{
				// Congrats, we have an hex value. Check for $ to see where it begins.
				if ((*rightPtr)[1]=='$') offset=1; else offset=2;
				rightLen=(*rightPtr)[0];
				// As always, it'd be better in its own utility func, but I'm not sure of
	            // which arguments I'd give it.
				for (i=offset+1; i<=rightLen; i++)
				{
					if ( (*rightPtr)[i]>='0' && (*rightPtr)[i]<='9' )
					{ // it's a decimal hex digit
						theValue*=16;
						theValue+=((*rightPtr)[i]-'0');
					}
					else if ( (*rightPtr)[i]>='A' && (*rightPtr)[i]<='F' )
					{ // it's an uppercase hex digit
						theValue*=16;
						theValue+=((*rightPtr)[i]-'A'+10);
					}
					else if ( (*rightPtr)[i]>='a' && (*rightPtr)[i]<='f' )
					{ // it's a lowercase hex digit
						theValue*=16;
						theValue+=((*rightPtr)[i]-'a'+10);
					}
					else /*it's something else, terminate hex number parsing*/ break;
				}
				// theValue has to right value to be given, I'm done in this case.
			}
			else // It's an ordinary decimal, let it be handled as it has always been.
			{
				::StringToNum( *rightPtr, &theValue);
			}
			// End of ZP feature #2.
			mFlagValues.AddItem(theValue);
			AppendMenu(inString);
			if (mResetIndex == -1 && theValue == 0) {
				mResetIndex = mFlagValues.GetCount() + mNumTopItems;
			} 
		}
	}
}


// ---------------------------------------------------------------------------
//	 HotSpotResult
// ---------------------------------------------------------------------------
//	Respond to a click in the popup

void
CFlagPopup::HotSpotResult(SInt16 /* inHotSpot */)
{
	MenuRef		theMenuH = GetMacMenuH();
	SInt32 index = GetValue();
	if (index == 1) {
		return;
	} else if (index == mResetIndex) {
		UpdatePopupWithValue(0);
	} else {
		CharParameter	markChar;
		::GetItemMark(theMenuH, index, &markChar);
		::MacCheckMenuItem(theMenuH, index, (markChar == 0) );
		::MacCheckMenuItem(theMenuH, mResetIndex, 0);
	}
	SetValue(1);
}


// ---------------------------------------------------------------------------
//	 UpdatePopupWithValue											  [public]
// ---------------------------------------------------------------------------

void
CFlagPopup::UpdatePopupWithValue(UInt32	inValue) 
{
	MenuRef		theMenuH = GetMacMenuH();
	SInt32		index;
	UInt32		theValue;

	// No check mark in the first (empty) item
	::MacCheckMenuItem(theMenuH, 0, 0);

	TArrayIterator<UInt32> iterator( mFlagValues );
	index = mNumTopItems + 1;
	
	while (iterator.Next(theValue)) {
		::MacCheckMenuItem(theMenuH, index, ((inValue & theValue) > 0) );
		index++;
	}
	if (inValue == 0) {
		::MacCheckMenuItem(theMenuH, mResetIndex, 1);
	} 
}


// ---------------------------------------------------------------------------
//	 GetFlagValue													 [public]
// ---------------------------------------------------------------------------
//	Return the value of a Control

UInt32
CFlagPopup::GetFlagValue() const
{
	MenuRef		theMenuH = GetMacMenuH();
	SInt32		index = mNumTopItems + 1;
	UInt32		flagValue = 0, theValue;
	CharParameter	markChar;

	TArrayIterator<UInt32> iterator( mFlagValues );
	
	while (iterator.Next(theValue)) {
		// Fixed bug: 'index' is the correct value, not 'index + 1'
		::GetItemMark(theMenuH, index, &markChar);
		if (markChar != 0) {
			flagValue += theValue;
		} 
		index++;
	}

	return flagValue;
}


// ---------------------------------------------------------------------------
//	 SetFlagValue													  [public]
// ---------------------------------------------------------------------------

void
CFlagPopup::SetFlagValue(UInt32 inValue)
{
	UpdatePopupWithValue(inValue);
}




PP_End_Namespace_PowerPlant
