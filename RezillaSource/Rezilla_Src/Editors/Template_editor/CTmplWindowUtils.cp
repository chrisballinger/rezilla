// ===========================================================================
// CTmplWindowUtils.cp					
// 
//                       Created: 2004-08-20 16:45:08
//             Last modification: 2004-08-20 19:22:22
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
// Implements the utility functions defined in the CTmplEditorWindow 
// class.


#include "CTmplEditorWindow.h"
#include "CTmplEditorDoc.h"
#include "CRezillaApp.h"
#include "CRezillaPrefs.h"
#include "CRezObj.h"
#include "CWasteEditView.h"
#include "UMiscUtils.h"

#include <LStaticText.h>
#include <LIconPane.h>

#include <stdio.h>


// ---------------------------------------------------------------------------
//  ¥ InstallReadOnlyIcon											[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::InstallReadOnlyIcon() 
{
	LIconPane * theIcon = dynamic_cast<LIconPane *>(this->FindPaneByID( item_ReadOnlyIcon ));
	ThrowIfNil_( theIcon );
	if (mOwnerDoc->IsReadOnly()) {
		theIcon->SetIconID(ics8_Locked);
	} else {
		theIcon->SetIconID(ics8_Unlocked);
	}
}


// ---------------------------------------------------------------------------
//	¥ IsDirty														[public]
// ---------------------------------------------------------------------------

Boolean
CTmplEditorWindow::IsDirty()
{	
	if (!mIsDirty) {
		// The mWasteFieldsList contains all the Waste views. Check if they
		// are modified.
		TArrayIterator<CWasteEditView *> iterator(mWasteFieldsList);
		CWasteEditView *	theWasteView = nil;
		
		while (iterator.Next(theWasteView)) {
			mIsDirty = theWasteView->IsDirty();
			if (mIsDirty) {
				break;
			} 
		}
	} 

	return mIsDirty;
}


// ---------------------------------------------------------------------------
//	¥ IsValidBitField													[public]
// ---------------------------------------------------------------------------
// BB0n  	BB01 to BB07	Bit field within a byte
// LBnn  	LB01 to LB31	Bit field within a long
// WBnn  	WB01 to WB16	Bit field within a word

Boolean
CTmplEditorWindow::IsValidBitField(OSType inType, Str255 inStr, 
								   UInt16 & ioBitsCount, UInt16 & ioBytesLen)
{
	Boolean isValid = false;
	long	theLong;
	
	if (inType >> 8 == 'BB0') {
		if (inStr[4] > '0' && inStr[4] < '8') {
			ioBitsCount = inStr[4] - '0';
			ioBytesLen = 1;
			isValid = true;
		} 
	} else {
		if ( ((inStr[3] >= '0') && (inStr[3] <= '9')) && ((inStr[4] > '0') && (inStr[4] < 8)) ) {
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
//	¥ BuildFormatString													[public]
// ---------------------------------------------------------------------------


void
CTmplEditorWindow::BuildFormatString(char * ioString, UInt8 inLength)
{
	if (CRezillaPrefs::GetPrefValue(kPref_editors_hexSymbol) == hex_Symb0x) {
		if (CRezillaPrefs::GetPrefValue(kPref_editors_hexCase) == hex_uppercase) {
			sprintf(ioString, "0x%s.%dX%sc%c", "%", inLength, "%", 0);
		} else {
			sprintf(ioString, "0x%s.%dx%sc%c", "%", inLength, "%", 0);
		}
	} else {
		if (CRezillaPrefs::GetPrefValue(kPref_editors_hexCase) == hex_uppercase) {
			sprintf(ioString, "$%s.%dX%sc%c", "%", inLength, "%", 0);
		} else {
			sprintf(ioString, "$%s.%dx%sc%c", "%", inLength, "%", 0);
		}
	}
}


// ---------------------------------------------------------------------------
//	¥ BuildScanString													[public]
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
//	¥ AdjustCounterField
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
//	¥ RenumberSubPanes
// ---------------------------------------------------------------------------
// If a new list item has been inserted, its subpanes are numbered from
// (inOldLastID) to (mCurrentID - 1). The argument (inNewFirstID) is the ID
// which should normally be affected to the first numbered subpane of the new 
// list item. So there are three possibilities when a subpane is visited:
// - if its ID is < (inNewFirstID), leave it unchanged
// - if its value is >= (inNewFirstID) and < (inOldLastID), increase it by 
//   (mCurrentID - inOldLastID)
// - if its value is >= (inOldLastID), decrease it by (inOldLastID - inNewFirstID)
// 
// If a list item has been deleted, all the IDs of its subpanes will be
// removed. They are numbered between inNewFirstID and inOldLastID
// inclusive. There are two possibilities:
// - if an ID is < (inNewFirstID), leave it unchanged
// - otherwise, decrease it by (inOldLastID - inNewFirstID + 1)
//   Note that the IDs between inNewFirstID and inOldLastID won't be found since 
//   the object has already been removed from the list of subpanes. Last
//   mCurrentID has to be adjusted likewise.

void
CTmplEditorWindow::RenumberSubPanes(LView * inView, PaneIDT inOldLastID, PaneIDT inNewFirstID, Boolean adding) 
{
	PaneIDT	theID;
	LView *	theView;
	
	if (adding) {
		// We've been inserting a list item
		TArrayIterator<LPane *> iterator( inView->GetSubPanes() );
		LPane	* theSub;
		while (iterator.Next(theSub)) {
			theID = theSub->GetPaneID();
			if (theID) {
				if (theID < inNewFirstID) {
					// Do nothing
				} else if (theID < inOldLastID) {
					theID += mCurrentID - inOldLastID;
					theSub->SetPaneID(theID);
				} else {
					theID -= inOldLastID - inNewFirstID;
					theSub->SetPaneID(theID);
				}
			} 
			theView = dynamic_cast<LView *>(theSub);
			if (theView) {
				RenumberSubPanes(theView, inOldLastID, inNewFirstID, adding);
			} 
		}
		
	} else {
		
		// We've been removing a list item
		TArrayIterator<LPane *> iterator( inView->GetSubPanes() );
		LPane	* theSub;
		while (iterator.Next(theSub)) {
			theID = theSub->GetPaneID();
			if (theID) {
				if (theID < inNewFirstID) {
					// Do nothing
				} else if (theID > inOldLastID) {
					theID -= inOldLastID - inNewFirstID + 1;
					theSub->SetPaneID(theID);
				}
			} 
			theView = dynamic_cast<LView *>(theSub);
			if (theView) {
				RenumberSubPanes(theView, inOldLastID, inNewFirstID, adding);
			} 
		}
	}
}


// ---------------------------------------------------------------------------
//	¥ RecalcPositions
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
//	¥ AlignBytesRead											[public]
// ---------------------------------------------------------------------------

ExceptionCode
CTmplEditorWindow::AlignBytesRead(UInt8 inStep)
{
	ExceptionCode	err = noErr;
	
	SInt32 theSInt32 = mRezStream->GetMarker();
	SInt32 theRest = theSInt32 % inStep;

	if (theRest != 0) {
		if (theSInt32 + theRest > mRezStream->GetLength()) {
			err = writErr;
		} else {
			mRezStream->SetMarker(theRest, streamFrom_Marker);
		}
	}
	
	return err;
}


// ---------------------------------------------------------------------------
//	¥ AlignBytesWrite											[public]
// ---------------------------------------------------------------------------

ExceptionCode
CTmplEditorWindow::AlignBytesWrite(UInt8 inStep)
{
	ExceptionCode	err = noErr;
	
	SInt32 theSInt32 = mOutStream->GetMarker();
	SInt32 theRest = theSInt32 % inStep;

	if (theRest != 0) {	
		for (UInt8 i = theRest; i < 4; i++) {
				*mOutStream << (UInt8) 0x00;
			}
		}
	
	return err;
}


#pragma mark -

// ---------------------------------------------------------------------------
//	¥ KeyValueToString											[private]
// ---------------------------------------------------------------------------

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
		::NumToString( (long) theSInt8, keyString);
		break;

		case 'KCHR':
		*mRezStream >> theChar;
		keyString[0] = 1;
		keyString[1] = theChar;
		break;

		case 'KHBT':
		*mRezStream >> theUInt8;
		BuildFormatString(formatString, 2);
		sprintf(charString, formatString, theUInt8, NULL);
		CopyCStringToPascal(charString, keyString);
		break;

		case 'KHLG':
		*mRezStream >> theUInt32;
		BuildFormatString(formatString, 8);
		sprintf(charString, formatString, theUInt32, NULL);
		CopyCStringToPascal(charString, keyString);
		break;

		case 'KHWD':
		*mRezStream >> theSInt16;
		BuildFormatString(formatString, 4);
		sprintf(charString, formatString, theUInt16, NULL);
		CopyCStringToPascal(charString, keyString);
		break;

		case 'KLNG':
		*mRezStream >> theSInt32;
		::NumToString( (long) theSInt32, keyString);
		break;

		case 'KRID':
		theSInt16 = GetOwnerDoc()->GetRezObj()->GetID();
		::NumToString( (long) theSInt16, keyString);	
		break;

		case 'KTYP': {
			Str255 tempString;
			*mRezStream >> theOSType;
			UMiscUtils::OSTypeToPString(theOSType, tempString);
			LString::CopyPStr(tempString, keyString);
			break;
		}
		
		case 'KUBT':
		*mRezStream >> theUInt8;
		::NumToString( (long) theUInt8, keyString);
		break;

		case 'KULG':
		*mRezStream >> theUInt32;
		::NumToString( (long) theUInt32, keyString);
		break;

		case 'KUWD':
		*mRezStream >> theUInt16;
		::NumToString( (long) theUInt16, keyString);
		break;

		case 'KWRD':
		*mRezStream >> theSInt16;
		::NumToString( (long) theSInt16, keyString);
		break;
	}
}


// ---------------------------------------------------------------------------
//	¥ FindKeyStartForValue											[private]
// ---------------------------------------------------------------------------
// The marker is positionned after the last CASE statement. Scan the 
// keyed sections until the corrsponding key is found.

OSErr
CTmplEditorWindow::FindKeyStartForValue(Str255 keyString, SInt32 * outStart)
{	
	OSErr	error = noErr;
	Boolean	found = false;
	SInt32	currMark, maxPos;
	Str255	theString;
	ResType	theType;
		
	currMark = mTemplateStream->GetMarker();
	maxPos = mTemplateStream->GetLength();
	
	while (currMark < maxPos) {
		*mTemplateStream >> theString;
		*mTemplateStream >> theType;
		currMark = mTemplateStream->GetMarker();		
	
		// The type at this point should normally be 'KEYB'
		if (theType != 'KEYB') {
			error = err_TmplMalformedKeySection;
			return error;
		} 
		
		// Is it the case corresponding to our keyString?
		if ( ::EqualString(theString, keyString, true, true) ) {
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
		error = err_TmplCantFindKeyStartForValue;
	} else {
		*outStart = currMark;
	}
	
	return error;
}


// ---------------------------------------------------------------------------
//	¥ FindMatchingKeyEnd											[private]
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
//	¥ SkipNextKeyCases											[private]
// ---------------------------------------------------------------------------
// Skip all the CASE statements starting from current position

OSErr
CTmplEditorWindow::SkipNextKeyCases()
{	
	OSErr	error = noErr;
	Boolean	found = false;
	Str255	theString;
	ResType	theType;
	UInt16	caseCount = 1;
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

	if (!found) {
		error = err_TmplCantFindKeyedSectionStart;
	} 
	
	return error;
}


// ---------------------------------------------------------------------------
//	¥ SelectValueFromKeyCases										[private]
// ---------------------------------------------------------------------------

Boolean
CTmplEditorWindow::SelectValueFromKeyCases(Str255 inLabelString)
{
	Boolean selected;
	
	// If there is only one CASE, choose it without asking
	
	return selected;
}

