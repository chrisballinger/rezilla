// ===========================================================================
// CTmplWindowUtils.cp
// 
//                       Created: 2004-08-20 16:45:08
//             Last modification: 2006-09-06 18:32:17
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes, 2004-2006
// All rights reserved.
// ===========================================================================
// Implements the utility functions defined in the CTmplEditorWindow 
// class.


#include "CTmplEditorWindow.h"
#include "CTmplEditorDoc.h"
#include "CTmplListItemView.h"
#include "CRezillaApp.h"
#include "CRezillaPrefs.h"
#include "CRezObj.h"
#include "CWasteEditView.h"
#include "CThreeButtonsBox.h"
#include "RezillaConstants.h"
#include "UDialogBoxHandler.h"
#include "UMessageDialogs.h"
#include "UMiscUtils.h"

#include <LPopupButton.h>
#include <LEditText.h>
#include <LStaticText.h>

#include <stdio.h>
#include <string.h>


// ---------------------------------------------------------------------------
//   IsValidBitField													[public]
// ---------------------------------------------------------------------------
// BB0n  	BB01 to BB07	Bit field within a byte
// WBnn  	WB01 to WB16	Bit field within a word
// LBnn  	LB01 to LB31	Bit field within a long

Boolean
CTmplEditorWindow::IsValidBitField(OSType inType, Str255 inStr, 
								   UInt16 & ioBitsCount, UInt16 & ioBytesLen)
{
	Boolean isValid = false;
	long	theLong;
	
	// CWPro9 does not accept just 'BB0', so replaced it by the 
	// corresponding hex value 0x424230 (05-03-01).
	if ( (inType >> 8) == 0x424230 ) {
		if (inStr[4] > '0' && inStr[4] < '8') {
			ioBitsCount = inStr[4] - '0';
			ioBytesLen = 1;
			isValid = true;
		} 
	} else {
		if ( (inStr[3] >= '0') && (inStr[3] <= '3') && (inStr[4] >= '0') && (inStr[4] <= '9') ) {
			inStr[2] = 2;
			::StringToNum( inStr + 2, &theLong);
			if (inType >> 16 == 'LB' && theLong <= 32) {
				ioBitsCount = theLong;
				ioBytesLen = 4;
				isValid = true;				
			} else if (inType >> 16 == 'WB' && theLong <= 16) {
				ioBitsCount = theLong;
				ioBytesLen = 2;
				isValid = true;
			} 
		} 
	}
	
	return isValid;
}


// ---------------------------------------------------------------------------
//   BuildFormatString													[public]
// ---------------------------------------------------------------------------


void
CTmplEditorWindow::BuildFormatString(char * ioString, UInt8 inLength)
{
	if (CRezillaPrefs::GetPrefValue(kPref_templates_hexSymbol) == hex_Symb0x) {
		if (CRezillaPrefs::GetPrefValue(kPref_templates_hexCase) == hex_uppercase) {
			sprintf(ioString, "0x%s.%dX%sc%c", "%", inLength, "%", 0);
		} else {
			sprintf(ioString, "0x%s.%dx%sc%c", "%", inLength, "%", 0);
		}
	} else {
		if (CRezillaPrefs::GetPrefValue(kPref_templates_hexCase) == hex_uppercase) {
			sprintf(ioString, "$%s.%dX%sc%c", "%", inLength, "%", 0);
		} else {
			sprintf(ioString, "$%s.%dx%sc%c", "%", inLength, "%", 0);
		}
	}
}


// ---------------------------------------------------------------------------
//   BuildScanString													[public]
// ---------------------------------------------------------------------------

OSErr
CTmplEditorWindow::BuildScanString(char * inString, char * ioFormat, UInt8 inLength)
{
	OSErr error = noErr;
	
	if (inString[0] == '$') {
		sprintf(ioFormat, "$%s%dx%c", "%", inLength, 0);
	} else if (inString[0] == '0' && inString[1] == 'x') {
		sprintf(ioFormat, "0x%s%dx%c", "%", inLength, 0);		
	} else {
		// alert
		error = err_TmplMalformedHexValue;
	}
	return error;
}


// ---------------------------------------------------------------------------
//   AdjustCounterField
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AdjustCounterField(PaneIDT inPaneID, SInt32 inDelta) {
	LStaticText *	theCounterText;
	Str255	numStr;
	long	theLong;
	
	theCounterText = dynamic_cast<LStaticText *>(this->FindPaneByID(inPaneID));
	theCounterText->GetDescriptor(numStr);	
	::StringToNum( numStr, &theLong);
	theLong += inDelta;
	if (theLong < 0) {
		theLong = 0;
	} 
	::NumToString(theLong, numStr);
	theCounterText->SetDescriptor(numStr);	
}


// ---------------------------------------------------------------------------
//   IncrementIfCases
// ---------------------------------------------------------------------------
// Takes care of incrementing the mPaneIndex value for edit text panes with
// a popup containing CASE tag values because this popup is registered in
// mPaneIDs and must be skipped on retrieval

void
CTmplEditorWindow::IncrementIfCases(LEditText * inEditText) {
	if ( inEditText->GetUserCon() == msg_EditFieldHasCases) {
		mPaneIndex++;
	} 
}


// ---------------------------------------------------------------------------
//   AdjustListOfPaneIDs
// ---------------------------------------------------------------------------
// The mPaneIDs list must reflect the visual graphical order of the panes.
// 
// If a new list item has been inserted, its subpanes are numbered from
// (inOldLastID) to (mCurrentID - 1) and they have been appended to the 
// mPaneIDs list. They must be moved to the position just after the
// inPrevLastID's position in the list.
// 
// If a list item has been deleted, all the IDs of its subpanes must be
// removed. They are located between inPrevLastID and inOldLastID
// inclusive. 
// 
// ZP bugfix #12: uh oh. CountAllSubpanes will count
// all subpanes (recursively if necessary) which have a non-0 ID, the
// issue is, not all of them are registered in mPaneIDs, but the count
// is indeed used for the number of IDs to move (or remove, if not
// adding) in mPaneIDs. Ouch.
//   (bd 2006-09-05) Fixed by also registering all the mCurrentID values in
//   mPaneIDs. This concerns the popups attached to edit fields. The edit
//   field keeps track of this in its refCon and advances the pane index
//   accordingly on retrieval.

void
CTmplEditorWindow::AdjustListOfPaneIDs(CTmplListItemView * inView, PaneIDT inStartID, 
									   PaneIDT inPrevCurrID, Boolean adding) 
{
	PaneIDT		theID = inStartID ;
	CTmplListItemView *	theView = inView;
	ArrayIndexT	index;
	SInt32		i, count = 0;
	
	// If adding is true, we've been inserting a list item, otherwise we've
	// been removing one.
	if (adding) {
		if (theView != NULL) {
			theID = theView->mFirstItemID;
			count = CountAllSubPanes(inView);
			// If the item view does not contain any control, its mFirstID
			// will be incorrect. Look in the previous list items until we 
			// find a non empty one.
			while (count == 0) {
				theView = theView->mPrevItem;
				if (theView == NULL) {
					theID = inStartID;
					break;
				} 
				theID = theView->mFirstItemID;
				count = CountAllSubPanes(theView);
			} 
		} 
		index = mPaneIDs.FetchIndexOf(theID);
		if (count > 0) {
			index += count - 1;
		} 
		// Move the newly added items from the end of the list. There are 
		// (mCurrentID - inPrevCurrID) of them.
		for (i = inPrevCurrID; i < mCurrentID; i++) {
			mPaneIDs.RemoveLastItem(theID);
			mPaneIDs.InsertItemsAt(1, index + 1, theID);
		}
	} else {
		count = CountAllSubPanes(inView);
		if (count > 0) {
			// Find the index of inStartID
			index = mPaneIDs.FetchIndexOf(inStartID);
			// Remove all the IDs of the itemView's subpanes
			if (index != LArray::index_Bad) {
				mPaneIDs.RemoveItemsAt( count, index);		
			}
		} 
	}
}


// ---------------------------------------------------------------------------
//   RecalcPositions
// ---------------------------------------------------------------------------
// If a new list item has been inserted, its first level subpanes must be
// repositioned. Their top pos must be increased by the height of the
// inserted list item. Then one must propagate to the containing view
// repeatedly until we reach the root contents view.

void
CTmplEditorWindow::RecalcPositions(LView * inView, SInt32 inVertPos, SInt32 inPosDelta) 
{
	Rect	theFrame;
	LPane *	theSub;
	SInt32	thePos = inVertPos;
	LView *	theContainer = inView->GetSuperView();
	
	while (theContainer != nil) {
		TArrayIterator<LPane *> iterator( theContainer->GetSubPanes() );
		while (iterator.Next(theSub)) {
			theSub->CalcPortFrameRect(theFrame);
			theContainer->PortToLocalPoint(topLeft(theFrame));

			if (theSub != inView && theFrame.top >= thePos) {
				theSub->MoveBy(0, inPosDelta, false);
			} 
		}
		if (theContainer == mContentsView) {
			break;
		} 
		theContainer->ResizeFrameBy(0, inPosDelta, false);
		theContainer->CalcPortFrameRect(theFrame);
		theContainer = theContainer->GetSuperView();
		if (theContainer != nil) {
			theContainer->PortToLocalPoint(topLeft(theFrame));
			// Increase by one pixel to ensure that the container won't
			// move itself
			thePos = theFrame.top + 1;
		} 
	}
}


// ---------------------------------------------------------------------------
//   AlignBytesRead											[public]
// ---------------------------------------------------------------------------

ExceptionCode
CTmplEditorWindow::AlignBytesRead(UInt8 inStep)
{
	ExceptionCode	error = noErr;
	
	SInt32 theSInt32 = mRezStream->GetMarker();
	SInt32 theRest = theSInt32 % inStep;

	if (theRest != 0) {
		if (theSInt32 + theRest > mRezStream->GetLength()) {
			error = writErr;
		} else {
			mRezStream->SetMarker(inStep - theRest, streamFrom_Marker);
		}
	}
	
	return error;
}


// ---------------------------------------------------------------------------
//   AlignBytesWrite											[public]
// ---------------------------------------------------------------------------

ExceptionCode
CTmplEditorWindow::AlignBytesWrite(UInt8 inStep)
{
	ExceptionCode	error = noErr;
	
	SInt32 theSInt32 = mOutStream->GetMarker();
	SInt32 theRest = theSInt32 % inStep;

	if (theRest != 0) {	
		for (UInt8 i = theRest; i < inStep; i++) {
				*mOutStream << (UInt8) 0x00;
			}
		}
	
	return error;
}


#pragma mark -

// ---------------------------------------------------------------------------
//   KeyValueToString											[private]
// ---------------------------------------------------------------------------
// The value of the key tag is stored as an SInt32 in the mKeyValues 
// for faster validation. Build a parallel mKeyIDs list which will be used 
// to determine the index in the mKeyValues and mKeyMarks lists when
// validating.

void
CTmplEditorWindow::KeyValueToString(ResType inType, Str255 keyString)
{
	char	theChar = 0;
	UInt8	theUInt8 = 0;
	UInt16	theUInt16 = 0;
	UInt32	theUInt32 = 0;
	SInt8	theSInt8 = 0;
	SInt16	theSInt16 = 0;
	SInt32	theSInt32 = 0;
	char 	charString[256];
	char 	formatString[16];
	OSType	theOSType;
	
	switch (inType) {
		case 'KBYT':
		*mRezStream >> theSInt8;
		mKeyValues.AddItem( (SInt32) theSInt8);
		::NumToString( (long) theSInt8, keyString);
		break;

		case 'KCHR':
		*mRezStream >> theChar;
		mKeyValues.AddItem( (SInt32) theChar);
		keyString[0] = 1;
		keyString[1] = theChar;
		break;

		case 'KHBT':
		*mRezStream >> theUInt8;
		mKeyValues.AddItem( (SInt32) theUInt8);
		BuildFormatString(formatString, 2);
		sprintf(charString, formatString, theUInt8, NULL);
		CopyCStringToPascal(charString, keyString);
		break;

		case 'KHLG':
		*mRezStream >> theUInt32;
		mKeyValues.AddItem( (SInt32) theUInt32);
		BuildFormatString(formatString, 8);
		sprintf(charString, formatString, theUInt32, NULL);
		CopyCStringToPascal(charString, keyString);
		break;

		case 'KHWD':
		*mRezStream >> theUInt16;
		mKeyValues.AddItem( (SInt32) theUInt16);
		BuildFormatString(formatString, 4);
		sprintf(charString, formatString, theUInt16, NULL);
		CopyCStringToPascal(charString, keyString);
		break;

		case 'KLNG':
		*mRezStream >> theSInt32;
		mKeyValues.AddItem( (SInt32) theSInt32);
		::NumToString( (long) theSInt32, keyString);
		break;

		case 'KRID':
		theSInt16 = GetOwnerDoc()->GetRezObj()->GetID();
		mKeyValues.AddItem( (SInt32) theSInt16);
		::NumToString( (long) theSInt16, keyString);	
		break;

		case 'KTYP': {
			Str255 tempString;
			*mRezStream >> theOSType;
			mKeyValues.AddItem( (SInt32) theOSType);
			UMiscUtils::OSTypeToPString(theOSType, tempString);
			LString::CopyPStr(tempString, keyString);
			break;
		}
		
		case 'KUBT':
		*mRezStream >> theUInt8;
		mKeyValues.AddItem( (SInt32) theUInt8);
		::NumToString( (long) theUInt8, keyString);
		break;

		case 'KULG':
		*mRezStream >> theUInt32;
		mKeyValues.AddItem( (SInt32) theUInt32);
		::NumToString( (long) theUInt32, keyString);
		break;

		case 'KUWD':
		*mRezStream >> theUInt16;
		mKeyValues.AddItem( (SInt32) theUInt16);
		::NumToString( (long) theUInt16, keyString);
		break;

		case 'KWRD':
		*mRezStream >> theSInt16;
		mKeyValues.AddItem( (SInt32) theSInt16);
		::NumToString( (long) theSInt16, keyString);
		break;
	}
}


// ---------------------------------------------------------------------------
//   KeyStringToValue										[private]
// ---------------------------------------------------------------------------
// The value of the key tag was obtained from the user via the
// SelectKeyValueFromKeyCases() dialog. Convert it to an SInt32 and store
// it in the mKeyValues for faster validation.

OSErr
CTmplEditorWindow::KeyStringToValue(ResType inType, Str255 keyString)
{
	OSErr	error = noErr;
	char 	charString[256];
	char 	formatString[16];
	OSType	theOSType;
	long	theLong;
	
	switch (inType) {
		case 'KBYT':
		case 'KLNG':
		case 'KUBT':
		case 'KULG':
		case 'KUWD':
		case 'KWRD':
		::StringToNum( keyString, &theLong);
		mKeyValues.AddItem(theLong);
		break;

		case 'KCHR':
		mKeyValues.AddItem( (SInt32) keyString[1]);
		break;

		case 'KHBT':
		CopyPascalStringToC(keyString, charString);
		::LowercaseText(charString, strlen(charString), (ScriptCode)0);
		error = BuildScanString(charString, formatString, 2);
		if (error == noErr) {
			sscanf(charString, formatString, &theLong);
			mKeyValues.AddItem(theLong);
		}
		break;

		case 'KHLG':
		CopyPascalStringToC(keyString, charString);
		::LowercaseText(charString, strlen(charString), (ScriptCode)0);
		error = BuildScanString(charString, formatString, 8);
		if (error == noErr) {
			sscanf(charString, formatString, &theLong);
			mKeyValues.AddItem(theLong);
		}
		break;

		case 'KHWD':
		CopyPascalStringToC(keyString, charString);
		::LowercaseText(charString, strlen(charString), (ScriptCode)0);
		error = BuildScanString(charString, formatString, 4);
		if (error == noErr) {
			sscanf(charString, formatString, &theLong);
			mKeyValues.AddItem(theLong);
		}
		break;

		case 'KRID':
		::StringToNum( keyString, &theLong);
		if (theLong != GetOwnerDoc()->GetRezObj()->GetID()) {
			UMessageDialogs::AlertWithValue(CFSTR("WrongIdForSelectedTemplate"), theLong);
		} 
		mKeyValues.AddItem(theLong);
		break;		
		
		case 'KTYP':
			UMiscUtils::PStringToOSType(keyString, theOSType);
			mKeyValues.AddItem( (SInt32) theOSType);
			break;
	}
	return error;
}


// ---------------------------------------------------------------------------
//   FindKeyStartForValue											[private]
// ---------------------------------------------------------------------------
// The marker is positionned after the last CASE statement. Scan the 
// keyed sections until the corresponding key is found.

OSErr
CTmplEditorWindow::FindKeyStartForValue(ResType inType, Str255 keyString, SInt32 * outStart)
{	
	OSErr	error = noErr;
	Boolean	found = false;
	Boolean	nocase = (inType == 'KHBT' || inType == 'KHWD' || inType == 'KHLG');
	SInt32	currMark, maxPos;
	Str255	theString;
	ResType	theType;
		
	currMark = mTemplateStream->GetMarker();
	maxPos = mTemplateStream->GetLength();
	
	while (currMark < maxPos) {
		*mTemplateStream >> theString;
		*mTemplateStream >> theType;
		currMark = mTemplateStream->GetMarker();		
	
		// The type at this point should normally be 'KEYB' otherwise we've
		// inspected all the key starts without founding our value.
		if (theType != 'KEYB') {
			error = err_TmplUnknownKeyValueInResource;
			return error;
		} 
		
		// Is it the case corresponding to our keyString?
		// For hexadecimal types, the comparison must be case insensitive.
		if ( ::EqualString(theString, keyString, ! nocase, true) ) {
			found = true;
			break;
		} 
		
		// If not, go to the corresponding KEYE
		error = FindMatchingKeyEnd(&currMark);
		if (error != noErr) {
			break;
		} 
	}
	
	if (!found) {
		if (inType == 'KRID') {
			error = err_TmplUnsupportedResourceId;
		} else {
			error = err_TmplCantFindKeyStartForValue;
		}
	} else {
		*outStart = currMark;
		// Store the value for future validation
		mKeyMarks.AddItem(currMark);
	}
	
	return error;
}


// ---------------------------------------------------------------------------
//   WriteOutKeyValue											[private]
// ---------------------------------------------------------------------------
// The value of the key tag has been stored as an SInt32 in the mKeyValues 
// list.

OSErr
CTmplEditorWindow::WriteOutKeyValue(ResType inType, PaneIDT inPaneID, ArrayIndexT * outIndex)
{
	SInt32	keyValue;
	OSErr	error = noErr;
	
	*outIndex = mKeyIDs.FetchIndexOf(inPaneID);
	
	if (*outIndex == LArray::index_Bad) {
		error = err_TmplCantFindKeyIndex;
	} else {
		mKeyIDs.RemoveItemsAt(1, *outIndex);
		
		if ( mKeyValues.FetchItemAt(*outIndex, keyValue) ) {
			mKeyValues.RemoveItemsAt(1, *outIndex);
			
			switch (inType) {
				case 'KBYT':
				*mOutStream << (SInt8) keyValue;
				break;
				
				case 'KCHR':
				*mOutStream << (UInt8) keyValue;
				break;
				
				case 'KHBT':
				*mOutStream << (UInt8) keyValue;
				break;
				
				case 'KHLG':
				*mOutStream << (UInt32) keyValue;
				break;
				
				case 'KHWD':
				*mOutStream << (UInt16) keyValue;
				break;
				
				case 'KLNG':
				*mOutStream << (SInt32) keyValue;
				break;
				
				case 'KRID':
				// Nothing written in the resource. The key is its ID.
				break;
				
				case 'KTYP': 
				*mOutStream << (OSType) keyValue;
				break;
				
				case 'KUBT':
				*mOutStream << (UInt8) keyValue;
				break;
				
				case 'KULG':
				*mOutStream << (UInt32) keyValue;
				break;
				
				case 'KUWD':
				*mOutStream << (UInt16) keyValue;
				break;
				
				case 'KWRD':
				*mOutStream << (SInt16) keyValue;
				break;
			}
		} else {
			error = err_TmplCantFindKeyValue;
		} 
	}
	
	return error;
}


// ---------------------------------------------------------------------------
//   FindMatchingKeyEnd											[private]
// ---------------------------------------------------------------------------
// Starting from a given KEYB find the corresponding KEYE. It returns 
// the position after the KEYE.

OSErr
CTmplEditorWindow::FindMatchingKeyEnd(SInt32 * outEnd)
{	
	OSErr	error = noErr;
	Boolean	found = false;
	SInt32	currMark, maxPos;
	UInt16	keybCount, keyeCount;
	Str255	theString;
	ResType	theType;

	currMark = mTemplateStream->GetMarker();
	maxPos = mTemplateStream->GetLength();
	keybCount = 1;
	keyeCount = 0;
	
	while (currMark < maxPos) {
		*mTemplateStream >> theString;
		*mTemplateStream >> theType;
		currMark = mTemplateStream->GetMarker();		
		
		if (theType == 'KEYB') {
			keybCount++;
		} else if (theType == 'KEYE') {
			keyeCount++;
		} else continue;
		
		if (keybCount == keyeCount) {
			found = true;
			break;
		} 
	}
	
	if (!found) {
		error = err_TmplCantFindMatchingKeyEnd;
	} else {
		*outEnd = currMark;
	}
	
	return error;
}


// ---------------------------------------------------------------------------
//   SkipNextKeyCases											[private]
// ---------------------------------------------------------------------------
// Skip all the CASE statements starting from current position

OSErr
CTmplEditorWindow::SkipNextKeyCases(UInt16 inPreCount)
{	
	OSErr	error = noErr;
	Boolean	found = false;
	Str255	theString;
	ResType	theType;
	UInt16	caseCount = inPreCount + 1;
	SInt32	currMark = mTemplateStream->GetMarker();
	SInt32	maxPos = mTemplateStream->GetLength();
	
	while (currMark < maxPos) {
		*mTemplateStream >> theString;
		*mTemplateStream >> theType;
		
		if (theType != 'CASE') {
			if (caseCount == 1) {
				// The type at this point should normally be 'CASE'
				error = err_TmplMalformedCaseSection;
				return error;
			} else {
				// We went too far. Reposition the stream marker.
				mTemplateStream->SetMarker(currMark, streamFrom_Start);
				break;
			}
		} 
		caseCount++;
		currMark = mTemplateStream->GetMarker();
	}

	return error;
}


// ---------------------------------------------------------------------------
//   NextIsCase											[private]
// ---------------------------------------------------------------------------
// Look forward in the template stream to see whether the next tag is a 
// CASE tag, then reposition the stream's marker.

Boolean
CTmplEditorWindow::NextIsCase()
{	
	Boolean	iscase = false;
	Str255	theString;
	ResType	theType;
	SInt32	currMark = mTemplateStream->GetMarker();
	SInt32	maxPos = mTemplateStream->GetLength();
	
	if (currMark < maxPos) {
		*mTemplateStream >> theString;
		*mTemplateStream >> theType;
		
		iscase = (theType == 'CASE');
		mTemplateStream->SetMarker( - theString[0] - 5, streamFrom_Marker) ;
	}

	return iscase;
}


// ---------------------------------------------------------------------------
//   SelectKeyValueFromKeyCases										[private]
// ---------------------------------------------------------------------------
// key "CreateUsingTemplate" 
// key "SelectKeyForTemplate" 

OSErr
CTmplEditorWindow::SelectKeyValueFromKeyCases(Str255 inLabelString,
										   Str255 outKeyString)
{
	OSErr			error = noErr;
	Str255			theString;
	ResType			theType;
	Boolean			selected = false;
	Boolean 		inPickerLoop = true;
	UInt16			countCases = 0;
	Str255 * 		rightPtr;
	SInt16			i, index = 0;
	SInt32			currMark, origMark, totalLength = mTemplateStream->GetLength();
	LStaticText *	theStaticField;
	LPopupButton *	thePopup;
	CFStringRef		formatStr = NULL, messageStr = NULL;

	StDialogBoxHandler	theHandler(PPob_TmplKeyChooser, this);
	CThreeButtonsBox *	theDialog = theHandler.GetDialog();
	Assert_(theDialog != nil);
	
	// Template type field
	theStaticField = dynamic_cast<LStaticText *>(theDialog->FindPaneByID( item_TmplKeyChooserType ));
	ThrowIfNil_(theStaticField);
	formatStr = CFCopyLocalizedString(CFSTR("CreateUsingTemplate"), NULL);
	if (formatStr != NULL) {
		char typeStr[5];
		*(OSType*)typeStr = mOwnerDoc->GetSubstType();
		typeStr[4] = 0;
		messageStr = ::CFStringCreateWithFormat(NULL, NULL, formatStr, typeStr);
		if (messageStr != NULL) {
			if (::CFStringGetPascalString(messageStr, theString, sizeof(theString), ::GetApplicationTextEncoding())) {
				theStaticField->SetDescriptor(theString);
			}
			CFRelease(messageStr);       
		}
		CFRelease(formatStr);                             
	}		  	

	// Explanatory message
	theStaticField = dynamic_cast<LStaticText *>(theDialog->FindPaneByID( item_TmplKeyChooserMessage ));
	ThrowIfNil_(theStaticField);
	messageStr = CFCopyLocalizedString(CFSTR("SelectKeyForTemplate"), NULL);
	if (messageStr != NULL) {
		if (::CFStringGetPascalString(messageStr, theString, sizeof(theString), ::GetApplicationTextEncoding())) {
			theStaticField->SetDescriptor(theString);
		}
		CFRelease(messageStr);       
	}

	// Label field: this is the label of the K*** tag
	theStaticField = dynamic_cast<LStaticText *>(theDialog->FindPaneByID( item_TmplKeyChooserLabel ));
	ThrowIfNil_(theStaticField);
	theStaticField->SetDescriptor(inLabelString);

	thePopup = dynamic_cast<LPopupButton *>(theDialog->FindPaneByID( item_TmplKeyChooserMenu ));
	ThrowIfNil_(thePopup);
	
	// Populate the popup with all the successive cases
	currMark = mTemplateStream->GetMarker();
	origMark = currMark;
	while (currMark < totalLength) {
		*mTemplateStream >> theString;
		*mTemplateStream >> theType;
		if (theType != 'CASE') {
			if (countCases == 0) {
				error = err_TmplNoCaseInKeySection;
				return error;
			} else {
				// We went too far. Reposition the stream marker.
				mTemplateStream->SetMarker(currMark, streamFrom_Start);
				break;
			}
		} 
		countCases++;
		currMark = mTemplateStream->GetMarker();
		if ( UMiscUtils::SplitCaseValue(theString, &rightPtr) ) {
			thePopup->InsertMenuItem(theString, index, true);
			index++;
		} 
	}
	
	if (index == 0) {
		// Means that UMiscUtils::SplitCaseValue() failed on all cases
		return err_TmplMalformedCaseSection;
	} 
	
	// If there is only one CASE, choose it without asking
	if (countCases == 1) {
		LString::CopyPStr(*rightPtr, outKeyString);
		return noErr;
	} 

	// Reset index to the first item
	index = 1;
	
	while (inPickerLoop) {
		MessageT theMessage;
		
		theDialog->Show();
		while (true) {
			theMessage = theHandler.DoDialog();
			if (msg_OK == theMessage) {
				break;
			} else if (msg_Cancel == theMessage) {
				inPickerLoop = false;
				error = userCanceledErr;
				break;
			} else if (msg_TmplKeyChooserMenu == theMessage) {
				// Retrieve the menu item and write it in the edit field
				index = thePopup->GetValue();
				break;  // Breaks out from the inner 'while' but still in the inPickerLoop 'while'
			} 
		}
		
		// If the default button was hit, try to open the rezmaps
		if (msg_OK == theMessage) {
			// Use the index to retreive the value of the key
			mTemplateStream->SetMarker(origMark, streamFrom_Start);
			for (i = 0; i < index; i++) {
				*mTemplateStream >> theString;
				*mTemplateStream >> theType;
			}
			UMiscUtils::SplitCaseValue(theString, &rightPtr);
			LString::CopyPStr(*rightPtr, outKeyString);
			// Now get out of the outer 'while'
			inPickerLoop = false;
		} 
	}
	mTemplateStream->SetMarker(currMark, streamFrom_Start);
	return error;
}


// ---------------------------------------------------------------------------
//   CountAllSubPanes												[static]
// ---------------------------------------------------------------------------

UInt32
CTmplEditorWindow::CountAllSubPanes(LView * inView)
{
	UInt32	count = 0;
	LPane *	theSub;
	LView *	theView;
	
	TArrayIterator<LPane *> iterator( inView->GetSubPanes() );
	while (iterator.Next(theSub)) {
		theView = dynamic_cast<LView *>(theSub);
		if (theView) {
			if (theView->GetPaneID() > 0) {
				count++;
			} 
			count += CountAllSubPanes(theView);
		} else {
			if (theSub->GetPaneID() > 0) {
				count++;
			} 
		}
	}
	
	return count;
}


// ---------------------------------------------------------------------------
//   RecalcTextBoxHeight											[private]
// ---------------------------------------------------------------------------
// Recalculate the height of the TextGroupBox containing a Waste field or a
// HexDump field depending on the size of the data expected. If it is a
// fixed length field, set to the exact number of lines necessary.
// Otherwise, there is a minimum height (corresponding to five lines) and a
// maximum (corresponding to seventeen lines).

Boolean
CTmplEditorWindow::RecalcTextBoxHeight(SInt32 inTextSize, CWasteEditView * inWEView,
									   Boolean isFixed, SInt32 inReqSize, SInt16 & delta)
{
	Boolean			reduce = false;
	SInt32			bytesPerLine, linesCount;
	SInt16			linesHeight, minHeight = kTmplTextMinHeight;
	SDimension16	theSize;
	
	if (inTextSize || isFixed) {
		inWEView->GetFrameSize(theSize);
		if (inTextSize && !isFixed) {
			linesCount = inWEView->CountLines() ;
		} else {
			bytesPerLine = theSize.width / CRezillaApp::sBasics.charWidth;
			linesCount = (inReqSize / bytesPerLine) + ((inReqSize % bytesPerLine) > 0) ;
		}
		
		if (linesCount == 0) {
			linesCount = 1;
		} 
		
		linesHeight = CRezillaApp::sBasics.charHeight * linesCount;	
		if (linesHeight <= theSize.height ) {
			reduce = true;
			if (linesHeight < kTmplTextMinHeight && !isFixed) {
				delta = kTmplTextMinHeight - theSize.height;
			} else {
				delta = linesHeight - theSize.height;
			}
		} 
	} 
	
	return reduce;
}


// ---------------------------------------------------------------------------
//   CalcTextPositions											[private]
// ---------------------------------------------------------------------------

Boolean
CTmplEditorWindow::CalcTextPositions(OSType inType, SInt32 & oldPos, SInt32 & newPos, 
									 SInt32 & nextPos, SInt32 & reqLength, Boolean & isFixed)
{
	Boolean		hasText = false;
	SInt32		totalLength;
	char 		theChar;
	UInt8		theUInt8 = 0;
	UInt16		theUInt16 = 0;
	UInt32		theUInt32 = 0;
	
	totalLength = mRezStream->GetLength();
	oldPos = mRezStream->GetMarker();
	nextPos = newPos = oldPos;
	
	// Calc the limits of the text depending on the tag
	if (oldPos < totalLength) {
		hasText = true;
		
		// We are not creating an empty new resource
		switch (inType) {
			case 'CSTR':
				// Is there a NULL byte marking the end of the string?
				newPos = totalLength;
				while (mRezStream->GetMarker() < totalLength ) {
					*mRezStream >> theChar;
					if (theChar == 0) {
						// Don't take the ending NULL
						newPos = mRezStream->GetMarker() - 1;
						break;
					} 
				}
				nextPos = mRezStream->GetMarker();
			break;

			case 'LSTR': {
				UInt32		theUInt32 = 0;
				// Long string (long  length followed by the characters)
				if (mRezStream->GetMarker() < totalLength - 3) {
					*mRezStream >> theUInt32;
				}
				oldPos += 4;
				newPos = oldPos + theUInt32;
				nextPos = newPos;
				break;
			}
			
			case 'WSTR': {
				UInt16		theUInt16 = 0;
				// Same as LSTR, but a word rather than a long word
				if (mRezStream->GetMarker() < totalLength - 1) {
					*mRezStream >> theUInt16;
				}
				oldPos += 2;
				newPos = oldPos + theUInt16;
				nextPos = newPos;
				break;
			}

			case 'ECST':
			case 'OCST':
				// Is there a NULL byte marking the end of the string?
				newPos = totalLength;
				while (mRezStream->GetMarker() < totalLength ) {
					*mRezStream >> theChar;
					if (theChar == 0) {
						newPos = mRezStream->GetMarker();
						// If the total length, including ending NULL, is odd
						// (with ESTR) or even (with OSTR), the string is padded, 
						// so skip one byte.
						if ( (newPos < totalLength) && ( 
							   ( ((newPos - oldPos) % 2) && (inType == 'ECST') ) 
							   ||
							   ( ((newPos - oldPos) % 2 == 0) && (inType == 'OCST') ) )) {
						   // Skip one byte.
						   if (mRezStream->GetMarker() < totalLength ) {
							   *mRezStream >> theChar;
						   }
						} 
						// Don't take the ending NULL
						newPos--;
						break;
					} 
				}
				nextPos = mRezStream->GetMarker();
			break;

			case 'HEXD':
			// This is always the last code in a template. Go to the end of the
			// resource data.
			newPos = totalLength;
			break;
			
			case 'BHEX': {
				// ByteLength Hex Dump
				if (mRezStream->GetMarker() < totalLength) {
					*mRezStream >> theUInt8;
				}
				oldPos += 1;
				newPos = oldPos + theUInt8;
				break;
			}
			
			case 'BSHX': {
				// (ByteLength - 1) Hex Dump
				if (mRezStream->GetMarker() < totalLength) {
					*mRezStream >> theUInt8;
				}
				if (theUInt8 < 1) {
					theUInt8 = 1;
				} 
				oldPos += 1;
				newPos = oldPos + theUInt8 - 1;
				break;
			}
			
			case 'LHEX': {
				// LongLength Hex Dump
				if (mRezStream->GetMarker() < totalLength - 3) {
					*mRezStream >> theUInt32;
				}
				oldPos += 4;
				newPos = oldPos + theUInt32;
				break;
			}
			
			case 'LSHX': {
				// (LongLength - 4) Hex Dump
				if (mRezStream->GetMarker() < totalLength - 3) {
					*mRezStream >> theUInt32;
				}
				if (theUInt32 < 4) {
					theUInt32 = 4;
				} 
				oldPos += 4;
				newPos = oldPos + theUInt32 - 4;
				break;
			}
			
			case 'WHEX': {
				// WordLength Hex Dump
				if (mRezStream->GetMarker() < totalLength - 1) {
					*mRezStream >> theUInt16;
				}
				oldPos += 2;
				newPos = oldPos + theUInt16;
				break;
			}
			
			case 'WSHX': {
				// (WordLength - 2) Hex Dump
				if (mRezStream->GetMarker() < totalLength - 1) {
					*mRezStream >> theUInt16;
				}
				if (theUInt16 < 2) {
					theUInt16 = 2;
				} 
				oldPos += 2;
				newPos = oldPos + theUInt16 - 2;
				break;
			}
			default: {
				isFixed = true;
				
				if (inType >> 24 == 'H' || inType >> 24 == 'F') {
					// Hnnn: a 3-digit hex number; displays $nnn bytes in hex format
					newPos = oldPos + reqLength;
				} else if (inType >> 24 == 'C') {
					// Cnnn: a C string that is $nnn hex bytes long. The last byte is always a 0, 
					// so the string itself occupies the first $nnn-1 bytes (possibly less
					// if a null is encountered before the end).

					nextPos = oldPos + reqLength;
					newPos = nextPos - 1;
					// Look for a NULL byte in this range
					while (mRezStream->GetMarker() < nextPos ) {
						*mRezStream >> theChar;
						if (theChar == 0) {
							newPos = mRezStream->GetMarker() - 1;
							break;
						}
					}
				} else if (inType >> 24 == 'T') {
					// Tnnn: a text string with fixed padding that is $nnn hex bytes long 
					nextPos = oldPos + reqLength;
					newPos = nextPos;
					// Look for a NULL byte in this range
					while (mRezStream->GetMarker() < nextPos ) {
						*mRezStream >> theChar;
						if (theChar == 0) {
							newPos = mRezStream->GetMarker() - 1;
							break;
						}
					}
				}
			}
		}

		if (oldPos > totalLength) {
			oldPos = totalLength;
		} 
		if (newPos > totalLength) {
			newPos = totalLength;
		} 
		if (newPos < oldPos) {
			newPos = oldPos;
		} 
		
	} else {
		if (inType >> 24 == 'H' || inType >> 24 == 'F' || inType >> 24 == 'C' || inType >> 24 == 'T') {
			isFixed = true;
			if (inType >> 24 == 'C') {
				// Don't count the NULL byte
				reqLength--;
			}
			// ZP bugfix #2, part 2: see part one in AddHexDumpField()
			Str255 typeStr;
			UMiscUtils::OSTypeToPString(inType, typeStr);
			if (inType >> 24 == 'H' && UMiscUtils::IsValidHexadecimal( (Ptr) typeStr + 2, 3))
			{
				// rationale: even when creating a resource, a Hxxx hex pane has to contain
				// the required amount of data, so I detect this case and set hasText, to
				// indicate that data must still be fed to the hex pane, zeroes if need be.
				hasText = true;
			}
			// end of ZP bugfix 2, part 2	
		}
	}
	
	return hasText;
}


