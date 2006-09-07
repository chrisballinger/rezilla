// ===========================================================================
// CTmplRSIDField.cp
// 
//             Last modification: 2006-07-14 09:01:30
// Author: ZPedro
// e-mail: <lebpierre@wanadoo.fr>
// www: <http://rezilla.sourceforge.net/>
// ===========================================================================
//  ZP feature #9
//  This new class is the pane that will appear when there is a RSID field in a
//  template window. For all intents and purposes, it will look and act like the
//  CTmplCaseField control that's shown when a mundane field is followed by case
//  tags or the CPopupEditField: a text field followed by a bevel menu button.
//  The popup menu will contain the following things:
//   - first items due to case tags, if any
//   - then names of resources of the given type
//   - then a last "unknown" or "other" item
//  The given type comes either from the label coming before the RSID, or a
//  previous TNAM tag, and is passed as a constructor param. If the latter, this
//  object should be made a listener of the TNAM text field and it will react
//  accordingly to the message by rebuilding the menu with the new ResType. The
//  same way, it needs to be made a listener of the RezMap, so that if a resource
//  of the given type is created, it can rebuild the menu.
//  It would be better (for the list not to be polluted by foreign entries) if
//  only resources from the current file were listed; that's how it is right now.
//  If there is no resource of that type in the current file, then show a
//  (localisable) disabled "No Res of Type xxxx Found" menu item. In order to
//  manage all this stuff, the pane will keep track of the menu item->value
//  mapping itself, especially as the resources will be sorted by ID and it would
//  be too expensive to ask the resource manager to rebrowse each time the
//  resource list to get the Nth ID in increasing order.
// ===========================================================================
// (ZPedro) By the way, I originally created this file from a copy of
// CTmplCaseField.cp, you might notice it at times.



#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CTmplRSIDField.h"
#include "RezillaConstants.h"
#include "UCompareUtils.h"
#include "UMiscUtils.h"
#include "CRezMap.h"

#include <LControlImp.h>
#include <LStaticText.h>
#include <LString.h>

#include <stdlib.h>

#include <CoreFoundation/CFByteOrder.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   CTmplRSIDField						Stream Constructor		  [public]
// ---------------------------------------------------------------------------

CTmplRSIDField::CTmplRSIDField(
				LStream*	inStream,
				ClassIDT	inImpID)
		: LEditText(inStream, inImpID)
{
	MessageT 	popupMessage;
	Boolean		leftSide;
	Str255		theString, noneString;
	
	*inStream >> popupMessage;
	*inStream >> leftSide;
	*inStream >> theString;
	*inStream >> mResType;
	*inStream >> noneString;

	mRezMap = NULL;
	mTnamField = NULL;
	
	SetUnknownItem(theString);
	SetNoneItem(noneString);
	CreatePopup(popupMessage, leftSide);
}


// ---------------------------------------------------------------------------
//   CTmplRSIDField						Parameterized Constructor [public]
// ---------------------------------------------------------------------------

CTmplRSIDField::CTmplRSIDField(
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
					ResType				inType,
					CRezMap*			inRezMap,
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
	SetNoneItem("\pNo Resource of Type ****");
	mResType = inType;
	mRezMap = inRezMap;
	
	// For now I set it to NULL, meaning there is none, it should be set later
	// with the accessor if there is one.
	mTnamField = NULL;

	CreatePopup(inPopupMessage, inLeftSide);
}


// ---------------------------------------------------------------------------
//   ~CTmplRSIDField						Destructor				  [public]
// ---------------------------------------------------------------------------

CTmplRSIDField::~CTmplRSIDField()
{
}


// ---------------------------------------------------------------------------
//   CreatePopup													[public]
// ---------------------------------------------------------------------------

void
CTmplRSIDField::CreatePopup(MessageT inPopupMsg, Boolean inLeftSide) 
{
	SPaneInfo	pi;
	Rect		frame;
	Str255		theString;
	
	CalcLocalFrameRect(frame);
	GetSuperView()->PortToLocalPoint(topLeft(frame));
	
	// Popup button fields basic values
	pi.width			= kRSIDFieldWidth;
	pi.height			= kRSIDFieldHeight;
	pi.visible			= true;
	pi.enabled			= true;
	pi.bindings.left	= false;
	pi.bindings.top		= false;
	pi.bindings.right	= false;
	pi.bindings.bottom 	= false;
	pi.userCon			= 0;
	if (inLeftSide) {
		pi.left = frame.left - kRSIDFieldWidth - kRSIDFieldSep;
	} else {
		pi.left = frame.left + mFrameSize.width + kRSIDFieldSep;
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
//   FillPopup													[public]
// ---------------------------------------------------------------------------

void
CTmplRSIDField::FillPopup() 
{
	SInt32		currMark, totalLength, theVal;
	ResType		theType;
	Str255		theString;
	Str255 * 	rightPtr;
	SInt16 *	IDList, num, i, j, val = 0;
	Handle *	handList, hand;
	ResType		theResType;
	Ptr			pos;
		
	// Empty the menu
	mPopup->DeleteAllMenuItems();
	// And the value list
	mValsList.RemoveAllItemsAfter(0);
	
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
			// Register this item in the list of values.
			::StringToNum(*rightPtr, &theVal);
			mValsList.AddItem((SInt16)theVal);
		} 
	}

	if (mRezMap==NULL) {
		num = 0;
	} else {
		mRezMap->CountForType(mResType, num);
	}
	
	if (num==0)
	{
		mPopup->AppendMenu("\p( ", false);
		// also put a padding value that's unlikely to be used in mValList:
		mValsList.AddItem((SInt16)-26153);
		::PLstrcpy(theString, mNoneItem);
		if ( (pos = ::PLstrstr(theString, "\p****")) != NULL ) {
			theResType = ::CFSwapInt32HostToBig(mResType);
			// Misalignment warning! If run on the 68000 this will crash the
			// Mac one time out of two. Alright, this code requires OSX to
			// begin with, and I don't think Apple will ever switch to a proc
			// that requires alignment, so this is unlikely to ever cause
			// trouble...
			*((UInt32*)pos) = theResType;
		}
		mPopup->SetMenuItemText(mValsList.GetCount(), theString);
	}
	else
	{
		LStr255		theMenuItem("\p");
		
		IDList = (SInt16*) malloc(num*sizeof(SInt16));
		handList = (Handle*) malloc(num*sizeof(Handle));
		for (i=1; i<=num; i++) {
			mRezMap->GetResourceAtIndex(mResType, i, hand, false);
			ThrowIfNil_(hand);
			::GetResInfo(hand, &(IDList[i-1]), &theResType, theString);
			// We don't pick up the resource name yet.
			handList[i-1]=hand;
		}
		// Now sort the stuff. Of course, while sorting the IDs I make the exact
        // same movements within the handle list.
		for (i=1; i<num; i++) {
			val = IDList[i]; 
			hand = handList[i];
			for (j=i; j>0; j--) {
				if (IDList[j-1] <= val) break;
				IDList[j] = IDList[j-1];
				handList[j] = handList[j-1];
			}
			IDList[j] = val;
			handList[j] = hand;
		}

		// Now we can fill the menu
		for (i=0; i<num; i++) {
			::NumToString((long)IDList[i], theString);
			theMenuItem.Assign(theString);
			theMenuItem += "\p: ";			
			::GetResInfo(handList[i], &val, &theResType, theString);
			mValsList.AddItem(val);
			theMenuItem += theString;
			mPopup->AppendMenu(theMenuItem);
		}
		free(IDList);
		free(handList);
	}
	// Finally add the "Unknown" item
	mPopup->AppendMenu(mUnknownItem);
	// Assign another dummy value to it, for now
	mValsList.AddItem((SInt16)0);
	
	// Lastly, adjust the current menu item
	GetDescriptor(theString);
	AdjustPopupWithValue(theString);
	
	mPopup->Refresh();
}


#pragma mark -

// ---------------------------------------------------------------------------
//   ListenToMessage				[public]
// ---------------------------------------------------------------------------

void
CTmplRSIDField::ListenToMessage( MessageT inMessage, void *ioParam )
{
	Str255 		theString;
	
	if (inMessage == mPopup->GetValueMessage()) {
		SInt32		choice = *(SInt32 *) ioParam;
		SInt16 theVal;
	
		// We're merely using the internal list to retrieve the value.
		mValsList.FetchItemAt(choice, theVal);
		::NumToString((long)theVal, theString);
		SetDescriptor(theString);
		// Tell the listeners
		BroadcastMessage(msg_EditorModifiedItem);
	} else if (inMessage == msg_EditorModifiedItem) {
		// We also need to react to changes in a potential TNAM field
        // we're related to, and to changes in the RezMap, when it will
	    // broadcast messages of course.
		ResType newResType;
		if (mTnamField==NULL) return;
		mTnamField->GetDescriptor(theString);
		UMiscUtils::PStringToOSType(theString, newResType);
		// This will handle rebuilding the menu
		SetResType(newResType); 
	}
}


// ---------------------------------------------------------------------------
//   AdjustPopupWithValue											[public]
// ---------------------------------------------------------------------------

SInt16
CTmplRSIDField::AdjustPopupWithValue(Str255 inString) 
{
	SInt32 val;
	SInt16 foundIdx;
	
	// If the string is empty, just set unknown.
	if (inString[0]==0) {
		SInt16 former = mPopup->GetCurrentMenuItem();
		UInt16 count = mValsList.GetCount();
		mPopup->SetCurrentMenuItem(count);
		::SetItemMark(mPopup->GetMacMenuH(), former, 0);
		foundIdx = LArray::index_Bad;
	} else {
		::StringToNum(inString, &val);
		foundIdx = mValsList.FetchIndexOf(val);
		// Mark the item corresponding to the value or remove any mark
		if (foundIdx != LArray::index_Bad) {
			mPopup->SetCurrentMenuItem(foundIdx);
		} else {
			SInt16 former = mPopup->GetCurrentMenuItem();
			UInt16 count = mValsList.GetCount();
			mPopup->SetCurrentMenuItem(count);
			::SetItemMark(mPopup->GetMacMenuH(), former, 0);
			// Assign this new value to the unknown item, that way when picking
			// it, it will put back this value.
			mValsList.AssignItemsAt(1, count, val);
		}
	}
	return foundIdx;
}



// ---------------------------------------------------------------------------
//   UserChangedText
// ---------------------------------------------------------------------------

void
CTmplRSIDField::UserChangedText()
{
	Str255	theString;
	SInt16	index;
	
	GetDescriptor(theString);
	index = AdjustPopupWithValue(theString);
	if (index == LArray::index_Bad) {
		// Pass NULL as ioParam to tell that no item was found in list
		BroadcastMessage(mValueMessage, NULL);
	} else {
		LEditText::UserChangedText();
	}
}


// ---------------------------------------------------------------------------
//   GetUnknownItem												  [public]
// ---------------------------------------------------------------------------
// The mUnknownItem string is an item appended at the end of the menu. 
// Its purpose is to designate a value which does not correspond to any 
// value in the rest of the menu.

void
CTmplRSIDField::GetUnknownItem( Str31 outString ) const
{
	LString::CopyPStr(mUnknownItem, outString);
}
		

// ---------------------------------------------------------------------------
//   SetUnknownItem												  [public]
// ---------------------------------------------------------------------------

void
CTmplRSIDField::SetUnknownItem( ConstStr31Param inString )
{
	LString::CopyPStr(inString, mUnknownItem, sizeof(mUnknownItem));

	if (mUnknownItem[0] > 31) {
		mUnknownItem[0] = 31;
	}
	if (mUnknownItem[0] == 0) {
		mUnknownItem[0] = 1;
		mUnknownItem[1] = ' ';
	}
}


// ---------------------------------------------------------------------------
//   GetNoneItem												  [public]
// ---------------------------------------------------------------------------
void
CTmplRSIDField::GetNoneItem( Str31 outString ) const
{
	LString::CopyPStr(mNoneItem, outString);
}


// ---------------------------------------------------------------------------
//   SetNoneItem												  [public]
// ---------------------------------------------------------------------------
void
CTmplRSIDField::SetNoneItem( ConstStr31Param inString )
{
	LString::CopyPStr(inString, mNoneItem, sizeof(mNoneItem));
	
	if (mNoneItem[0] > 31) {
		mNoneItem[0] = 31;
	}
	if (mNoneItem[0] == 0) {
		mNoneItem[0] = 1;
		mNoneItem[1] = ' ';
	}
}


// ---------------------------------------------------------------------------
//   GetRezMap												  [public]
// ---------------------------------------------------------------------------
void
CTmplRSIDField::GetRezMap( CRezMap* &outRezMap ) const
{
	outRezMap = mRezMap;
}


// ---------------------------------------------------------------------------
//   SetRezMap												  [public]
// ---------------------------------------------------------------------------
void
CTmplRSIDField::SetRezMap( CRezMap* inRezMap )
{
	mRezMap = inRezMap;
	// This means only one thing: rebuild the menu.
	FillPopup();
}


// ---------------------------------------------------------------------------
//   GetTnamField												  [public]
// ---------------------------------------------------------------------------
void
CTmplRSIDField::GetTnamField( LEditText* &outPane ) const
{
	outPane = mTnamField;
}


// ---------------------------------------------------------------------------
//   SetTnamField												  [public]
// ---------------------------------------------------------------------------

// Note: when using this, also set the ResType in the field, if not already done.

void
CTmplRSIDField::SetTnamField( LEditText* inPane )
{
	// Unregister listening to the former one, if any:
	if (mTnamField) mTnamField->RemoveListener(this);
	
	mTnamField = inPane;

	if (mTnamField) mTnamField->AddListener(this);
}


// ---------------------------------------------------------------------------
//   GetResType												  [public]
// ---------------------------------------------------------------------------
void
CTmplRSIDField::GetResType( ResType &outType ) const
{
	outType = mResType;
}


// ---------------------------------------------------------------------------
//   SetResType												  [public]
// ---------------------------------------------------------------------------
void
CTmplRSIDField::SetResType( ResType inType )
{
	mResType = inType;
	// Rebuild the menu
	FillPopup();
}


// ---------------------------------------------------------------------------
//   Disable
// ---------------------------------------------------------------------------
//	Disable both panes

void
CTmplRSIDField::Disable()
{
	this->Disable();
	mPopup->Disable();
}


// ---------------------------------------------------------------------------
//   Enable
// ---------------------------------------------------------------------------
//	Enable both panes

void
CTmplRSIDField::Enable()
{
	this->Enable();
	mPopup->Enable();
}


// ---------------------------------------------------------------------------
//   Show
// ---------------------------------------------------------------------------
//	Show both panes

void
CTmplRSIDField::Show()
{
	this->Show();
	mPopup->Show();
}


// ---------------------------------------------------------------------------
//   Hide
// ---------------------------------------------------------------------------
//	Hide both panes

void
CTmplRSIDField::Hide()
{
	this->Hide();
	mPopup->Hide();
}


// ---------------------------------------------------------------------------
//   ResizeFrameBy
// ---------------------------------------------------------------------------
//	Change the Frame size by the specified amounts

void
CTmplRSIDField::ResizeFrameBy(
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

