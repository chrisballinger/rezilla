// ===========================================================================
// CTmplWindowUtils.cp					
// 
//                       Created: 2004-08-20 16:45:08
//             Last modification: 2004-09-21 14:34:43
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
// Implements the functions defining the various fields and controls in the 
// CTmplEditorWindow class.


#include "CTmplEditorWindow.h"
#include "CTmplEditorDoc.h"
#include "CTmplListItemView.h"
#include "CTmplListButton.h"
#include "CTmplBevelButton.h"
#include "CTemplatesController.h"
#include "CRezObj.h"
#include "CRezillaApp.h"
#include "CRezillaPrefs.h"
#include "CDualDataView.h"
#include "CHexDataSubView.h"
#include "CSingleScrollBar.h"
#include "CTxtDataSubView.h"
#include "CWasteEditView.h"
#include "CColorWell.h"
#include "UMiscUtils.h"
#include "UMessageDialogs.h"

#include <LScrollBar.h>
#include <LStaticText.h>
#include <LIconPane.h>
#include <LEditText.h>
#include <LTextGroupBox.h>
#include <LCheckBox.h>
#include <LPushButton.h>
#include <LScrollerView.h>
#include <LSeparatorLine.h>
#include <UDrawingState.h>
#include <LArray.h>

#include <ControlDefinitions.h>

#include <stdio.h>
#include <string.h>



// ---------------------------------------------------------------------------
//		¥ InitPaneInfos												[static]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::InitPaneInfos()
{
	// Label fields basic values
	sStaticPaneInfo.paneID			= 0;
	sStaticPaneInfo.height			= kTmplLabelHeight;
	sStaticPaneInfo.visible			= true;
	sStaticPaneInfo.enabled			= true;
	sStaticPaneInfo.bindings.left	= true;
	sStaticPaneInfo.bindings.top	= false;
	sStaticPaneInfo.bindings.right	= false;
	sStaticPaneInfo.bindings.bottom = false;
	sStaticPaneInfo.userCon			= 0;
	
	// Edit fields basic values
	sEditPaneInfo.paneID			= 0;
	sEditPaneInfo.height			= kTmplEditHeight;
	sEditPaneInfo.visible			= true;
	sEditPaneInfo.enabled			= true;
	sEditPaneInfo.bindings.left		= true;
	sEditPaneInfo.bindings.top		= false;
	sEditPaneInfo.bindings.right	= true;
	sEditPaneInfo.bindings.bottom	= false;
	sEditPaneInfo.userCon			= 0;

	// Radio group view basic values
	sRgvPaneInfo.paneID				= 0;
	sRgvPaneInfo.width				= kTmplRgvWidth;
	sRgvPaneInfo.height				= kTmplRgvHeight;
	sRgvPaneInfo.visible			= true;
	sRgvPaneInfo.enabled			= true;
	sRgvPaneInfo.bindings.left		= true;
	sRgvPaneInfo.bindings.top		= false;
	sRgvPaneInfo.bindings.right		= false;
	sRgvPaneInfo.bindings.bottom	= false;
	sRgvPaneInfo.userCon			= 0;
	
	// Radio buttons basic values
	sRadioPaneInfo.paneID			= 0;
	sRadioPaneInfo.width			= kTmplRadioWidth;
	sRadioPaneInfo.height			= kTmplRadioHeight;
	sRadioPaneInfo.visible			= true;
	sRadioPaneInfo.enabled			= true;
	sRadioPaneInfo.bindings.left	= true;
	sRadioPaneInfo.bindings.top		= false;
	sRadioPaneInfo.bindings.right	= false;
	sRadioPaneInfo.bindings.bottom	= false;
	sRadioPaneInfo.userCon			= 0;

	// Check boxes basic values
	sCheckPaneInfo.paneID			= 0;
	sCheckPaneInfo.width			= kTmplCheckWidth;
	sCheckPaneInfo.height			= kTmplCheckHeight;
	sCheckPaneInfo.visible			= true;
	sCheckPaneInfo.enabled			= true;
	sCheckPaneInfo.bindings.left	= true;
	sCheckPaneInfo.bindings.top		= false;
	sCheckPaneInfo.bindings.right	= false;
	sCheckPaneInfo.bindings.bottom	= false;
	sCheckPaneInfo.userCon			= 0;

	// Rectangle labels basic values
	sRectLabelInfo.paneID			= 0;
	sRectLabelInfo.width			= kTmplRectWidth;
	sRectLabelInfo.height			= kTmplRectHeight;
	sRectLabelInfo.visible			= true;
	sRectLabelInfo.enabled			= true;
	sRectLabelInfo.bindings.left	= true;
	sRectLabelInfo.bindings.top		= false;
	sRectLabelInfo.bindings.right	= false;
	sRectLabelInfo.bindings.bottom	= false;
	sRectLabelInfo.userCon			= 0;

	// Rectangle edit basic values
	sRectPaneInfo.width				= kTmplRectWidth;
	sRectPaneInfo.height			= kTmplEditHeight;
	sRectPaneInfo.visible			= true;
	sRectPaneInfo.enabled			= true;
	sRectPaneInfo.bindings.left		= true;
	sRectPaneInfo.bindings.top		= false;
	sRectPaneInfo.bindings.right	= false;
	sRectPaneInfo.bindings.bottom	= false;
	sRectPaneInfo.userCon			= 0;
	
	// Active scrollers basic values
	sScrollPaneInfo.paneID			= 0;
	sScrollPaneInfo.visible			= true;
	sScrollPaneInfo.enabled			= true;
	sScrollPaneInfo.bindings.left	= false;
	sScrollPaneInfo.bindings.top	= true;
	sScrollPaneInfo.bindings.right	= true;
	sScrollPaneInfo.bindings.bottom	= true;
	sScrollPaneInfo.userCon			= 0;

	// Text group box for text views basic values
	sTgbPaneInfo.height				= kTmplTextHeight;
	sTgbPaneInfo.visible			= true;
	sTgbPaneInfo.enabled			= true;
	sTgbPaneInfo.bindings.left		= true;
	sTgbPaneInfo.bindings.top		= false;
	sTgbPaneInfo.bindings.right		= true;
	sTgbPaneInfo.bindings.bottom	= false;
	sTgbPaneInfo.userCon			= 0;

	// Text views basic values
	sWastePaneInfo.paneID			= 0;
	sWastePaneInfo.visible			= true;
	sWastePaneInfo.enabled			= true;
	sWastePaneInfo.bindings.left	= true;
	sWastePaneInfo.bindings.top		= true;
	sWastePaneInfo.bindings.right	= true;
	sWastePaneInfo.bindings.bottom	= true;
	sWastePaneInfo.userCon			= 0;
	
	// Push buttons basic values
	sPushPaneInfo.width				= kTmplPushWidth;
	sPushPaneInfo.height			= kTmplPushHeight;
	sPushPaneInfo.visible			= true;
	sPushPaneInfo.enabled			= true;
	sPushPaneInfo.bindings.left		= false;
	sPushPaneInfo.bindings.top		= false;
	sPushPaneInfo.bindings.right	= false;
	sPushPaneInfo.bindings.bottom	= false;
	sPushPaneInfo.userCon			= 0;
	
	// List item views basic values
	sListItemInfo.height			= 0;
	sListItemInfo.visible			= true;
	sListItemInfo.enabled			= true;
	sListItemInfo.bindings.left		= true;
	sListItemInfo.bindings.top		= false;
	sListItemInfo.bindings.right	= true;
	sListItemInfo.bindings.bottom	= false;
	sListItemInfo.userCon			= 0;
	
	// Separator horizontal line basic values
	sSeparatorPaneInfo.paneID			= 0;
	sSeparatorPaneInfo.height			= kTmplSeparatorHeight;
	sSeparatorPaneInfo.visible			= true;
	sSeparatorPaneInfo.enabled			= true;
	sSeparatorPaneInfo.bindings.left	= true;
	sSeparatorPaneInfo.bindings.top		= false;
	sSeparatorPaneInfo.bindings.right	= true;
	sSeparatorPaneInfo.bindings.bottom = false;
	sSeparatorPaneInfo.userCon			= 0;
	
	// Popup button fields basic values
	sBevelPaneInfo.width			= kTmplBevelWidth;
	sBevelPaneInfo.height			= kTmplBevelHeight;
	sBevelPaneInfo.visible			= true;
	sBevelPaneInfo.enabled			= true;
	sBevelPaneInfo.bindings.left	= false;
	sBevelPaneInfo.bindings.top		= false;
	sBevelPaneInfo.bindings.right	= true;
	sBevelPaneInfo.bindings.bottom 	= false;
	sBevelPaneInfo.userCon			= 0;

	// Color panes basic values
	sColorPaneInfo.width			= kTmplColorWidth;
	sColorPaneInfo.height			= kTmplColorHeight;
	sColorPaneInfo.visible			= true;
	sColorPaneInfo.enabled			= true;
	sColorPaneInfo.bindings.left	= true;
	sColorPaneInfo.bindings.top		= false;
	sColorPaneInfo.bindings.right	= false;
	sColorPaneInfo.bindings.bottom 	= false;
	sColorPaneInfo.userCon			= 0;
	
}


#pragma mark -

// ---------------------------------------------------------------------------
//	¥ AddStaticField													[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddStaticField(OSType inType, Str255 inLabel, LView * inContainer, ResIDT inTextTraitsID)
{
	sStaticPaneInfo.left		= kTmplLeftMargin;
	sStaticPaneInfo.top			= mYCoord;
	sStaticPaneInfo.superView	= inContainer;
	
	// For a comment label (DVDR) extend the width to the entire window.
	if (inType == 'DVDR') {
		SDimension16	theFrame;
		inContainer->GetFrameSize(theFrame);
		sStaticPaneInfo.width = theFrame.width - kTmplLeftMargin * 2;
	} else {
		sStaticPaneInfo.width = kTmplLabelWidth;
	}

	LStaticText * theStaticText = new LStaticText(sStaticPaneInfo, inLabel, inTextTraitsID);
	ThrowIfNil_(theStaticText);
}


// ---------------------------------------------------------------------------
//	¥ AddEditField														[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddEditField(Str255 inValue, 
								OSType inType,
								SInt16 inMaxChars, 
								UInt8 inAttributes,
								TEKeyFilterFunc inKeyFilter, 
								LView * inContainer)
{
	SDimension16	theFrame;
	inContainer->GetFrameSize(theFrame);

	sEditPaneInfo.left		= kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep;
	sEditPaneInfo.width		= theFrame.width - kTmplLeftMargin * 2 - kTmplLabelWidth - kTmplHorizSep - kTmplHorizSkip;
	sEditPaneInfo.top		= mYCoord - 3;
	sEditPaneInfo.paneID	= mCurrentID;
	sEditPaneInfo.superView	= inContainer;

	LEditText * theEditText = new LEditText(sEditPaneInfo, this, inValue, sEditTraitsID, 
											msg_TmplModifiedItem, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);

	// Store the template's type in the userCon field
	theEditText->SetUserCon(inType);
	
	// Let the window listen to this field
	theEditText->AddListener(this);

	// Filler types are not editable
	if (inType == 'FBYT' || inType == 'FLNG' || inType == 'FWRD') {
		theEditText->Disable();
	} 
	
	// Advance the counters
	mYCoord += sEditPaneInfo.height + kTmplVertSep;
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//	¥ AddBooleanField											[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddBooleanField(Boolean inValue,
								   OSType inType,
								   SInt16 inTitleType, 
								   LView * inContainer)
{
	LStdRadioButton * theRadio;
	SViewInfo	theViewInfo;
	theViewInfo.imageSize.width		= theViewInfo.imageSize.height	= 0 ;
	theViewInfo.scrollPos.h			= theViewInfo.scrollPos.v		= 0;
	theViewInfo.scrollUnit.h		= theViewInfo.scrollUnit.v		= 1;
	theViewInfo.reconcileOverhang	= false;
	
	sRgvPaneInfo.left		= kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep;
	sRgvPaneInfo.top		= mYCoord - 2;
	sRgvPaneInfo.paneID		= mCurrentID;
	sRgvPaneInfo.superView	= inContainer;

	LRadioGroupView * theRGV = new LRadioGroupView(sRgvPaneInfo, theViewInfo);
	ThrowIfNil_(theRGV);

	// Store the template's type in the userCon field
	theRGV->SetUserCon(inType);
	
	mCurrentID++;

	// Create two radiobuttons in this group
	//     "Yes/On" radiobutton
	sRadioPaneInfo.left			= 0;
	sRadioPaneInfo.top			= 0;
	sRadioPaneInfo.paneID		= mCurrentID;
	sRadioPaneInfo.superView	= theRGV;

	theRadio = new LStdRadioButton(sRadioPaneInfo, msg_TmplModifiedItem, 
								   inValue, sLeftLabelTraitsID, (UInt8 *)(inTitleType ? "\pOn":"\pYes"));
	ThrowIfNil_(theRadio);
	
	// Add to the radio-group
	theRGV->AddRadio(theRadio);
	
	// Let the window listen to this button
	theRadio->AddListener(this);
	
	mCurrentID++;

	//     "No/Off" radiobutton
	sRadioPaneInfo.left += kTmplRadioWidth + kTmplHorizSep;
	sRadioPaneInfo.paneID = mCurrentID;

	theRadio = new LStdRadioButton(sRadioPaneInfo, msg_TmplModifiedItem, 
								   1 - inValue, sLeftLabelTraitsID, (UInt8 *)(inTitleType ? "\pOff":"\pNo"));
	ThrowIfNil_(theRadio);
	
	// Add to the radio-group
	theRGV->AddRadio(theRadio);
	
	// Let the window listen to this button
	theRadio->AddListener(this);

	theRGV->SetCurrentRadioID( inValue ?  mCurrentID - 1 : mCurrentID );
	
	// Advance the counters
	mYCoord += sRgvPaneInfo.height + kTmplVertSep;
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//	¥ AddBitField											[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddBitField(OSType inType,
							   Str255 inLabel,
							   UInt16 inBitCount, 
							   UInt16 inBytesLen,
							   LView * inContainer)
{
	UInt16	i, val;
	Str255	numStr;
	
	if (!mBitSeqInProgress) {
		mBitSeqInProgress = true;
		// High bit first.
		mBitSeqIndex = mBitSeqBytesLen * 8 - 1;
		mBitSeqBytesLen = inBytesLen;
		if (mRezStream->GetMarker() < mRezStream->GetLength() - mBitSeqBytesLen + 1) {
			*mRezStream >> mBitSeqValue;
		} else {
			mBitSeqValue = 0;
		}
	} 
	
	
	if (inBitCount == 1) {
		AddStaticField(inType, inLabel, inContainer);
		AddCheckField( ((mBitSeqValue & 1 << mBitSeqIndex) > 0), inType, inContainer);	
		mBitSeqIndex--;
	} else {
		// Add the bits count to the label
		LStr255 theLabel(inLabel);
		theLabel += "\p (";
		::NumToString( (long) inBitCount, numStr);
		theLabel += numStr;
		theLabel += "\p bits)";
		AddStaticField(inType, theLabel, inContainer);
		
		// Build the value
		val = 0;
		for (i = 0; i < inBitCount ; i++) {
			val |= mBitSeqValue & 1 << mBitSeqIndex;
			mBitSeqIndex--;
		}
		::NumToString( (long) val, numStr);
		AddEditField(numStr, inType, 4, 0, UKeyFilters::SelectTEKeyFilter(keyFilter_Integer), inContainer);
	}
	
	if (mBitSeqIndex < 0) {
		mBitSeqInProgress = false;
	} 
}


// ---------------------------------------------------------------------------
//	¥ AddCheckField											[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddCheckField(Boolean inValue,
								   OSType inType,
								   LView * inContainer)
{
	sCheckPaneInfo.left			= kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep;
	sCheckPaneInfo.top			= mYCoord - 2;
	sCheckPaneInfo.paneID		= mCurrentID;
	sCheckPaneInfo.superView	= inContainer;

	LCheckBox * theCheck = new LCheckBox(sCheckPaneInfo, msg_TmplModifiedItem, inValue);
	ThrowIfNil_(theCheck);
		
	// Store the template's type in the userCon field
	theCheck->SetUserCon(inType);
	
	// Let the window listen to this button
	theCheck->AddListener(this);

	// Advance the counters
	mYCoord += sCheckPaneInfo.height + kTmplVertSep;
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//	¥ AddWasteField													[public]
// ---------------------------------------------------------------------------
// C string. This should be either characters followed by a null or all
// the chars until the end of the stream if there is no null byte.
// LTextGroupBox::LTextGroupBox(
// 	const SPaneInfo&	inPaneInfo,
// 	const SViewInfo&	inViewInfo,
// 	Boolean				inPrimary,
// 	ResIDT				inTextTraitsID,
// 	ConstStringPtr		inTitle,
// 	ClassIDT			inImpID)

void
CTmplEditorWindow::AddWasteField(OSType inType, LView * inContainer)
{
	SInt32		oldPos, newPos, nextPos, totalLength;
	Handle		theHandle;
	char 		theChar;
	SViewInfo	theViewInfo;
	SDimension16	theFrame;
	
	inContainer->GetFrameSize(theFrame);

	theViewInfo.imageSize.width		= theViewInfo.imageSize.height	= 0 ;
	theViewInfo.scrollPos.h			= theViewInfo.scrollPos.v		= 0;
	theViewInfo.scrollUnit.h		= theViewInfo.scrollUnit.v		= 1;
	theViewInfo.reconcileOverhang	= false;
	
	sTgbPaneInfo.paneID				= 0;
	sTgbPaneInfo.top				= mYCoord;
	sTgbPaneInfo.left				= kTmplTextMargin;
	sTgbPaneInfo.width				= theFrame.width - kTmplTextMargin * 2;
	sTgbPaneInfo.superView			= inContainer;

	LTextGroupBox * theTGB = new LTextGroupBox(sTgbPaneInfo, theViewInfo, false);
	ThrowIfNil_(theTGB);

	sScrollPaneInfo.left			= kTmplTextInset;
	sScrollPaneInfo.top				= kTmplTextInset;
	sScrollPaneInfo.width			= sTgbPaneInfo.width - kTmplTextInset * 2;
	sScrollPaneInfo.height			= sTgbPaneInfo.height - kTmplTextInset * 2;
	sScrollPaneInfo.bindings.left	= true;
	sScrollPaneInfo.paneID			= 0;
	sScrollPaneInfo.superView		= theTGB;

	LScrollerView * theScroller = new LScrollerView(sScrollPaneInfo, theViewInfo, 0, 15, 0, 15, 16, NULL, true);
	ThrowIfNil_(theScroller);

	sWastePaneInfo.left				= 0;
	sWastePaneInfo.top				= 0;
	sWastePaneInfo.width			= sScrollPaneInfo.width - 15;
	sWastePaneInfo.height			= sScrollPaneInfo.height - 15;
	sWastePaneInfo.bindings.left	= true;
	sWastePaneInfo.bindings.right	= true;
	sWastePaneInfo.paneID			= mCurrentID;
	sWastePaneInfo.superView		= theScroller;

	// Make the Waste edit writable, not wrapping, selectable
	CWasteEditView * theWasteEdit = new CWasteEditView(sWastePaneInfo, theViewInfo, 0, sEditTraitsID);
	ThrowIfNil_(theWasteEdit);

	// Add to the mWasteFieldsList
	mWasteFieldsList.AddItem(theWasteEdit);
	
	theScroller->InstallView(theWasteEdit);
	
	// Store the template's type in the userCon field
	theWasteEdit->SetUserCon(inType);
	totalLength = mRezStream->GetLength();
	
	// Insert the text
	oldPos = mRezStream->GetMarker();
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
						   ( (newPos - oldPos) % 2 && (inType = 'ECST') ) 
						   ||
						   ( (newPos - oldPos) % 2 == 0 && (inType = 'OCST') ) )) {
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

		default: {
			SInt32 reqLength;
			UMiscUtils::HexNumStringToDecimal(&inType, &reqLength);

			if (inType >> 24 == 'C') {
				// Cnnn: a C string that is $nnn hex bytes long. The last byte is always a 0, 
				// so the string itself occupies the first $nnn-1 bytes (possibly less
				// if a null is encountered before the end).

				nextPos = oldPos + reqLength;
				newPos = nextPos - 1;
				// Look for a NULL byte in this range
				while (mRezStream->GetMarker() <= nextPos ) {
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
	
	theHandle = mRezStream->GetDataHandle();
	HLock(theHandle);
	theWasteEdit->Insert( (*theHandle) + oldPos , newPos - oldPos, NULL, true);
	HUnlock(theHandle);
	
	// Advance the counters
	mRezStream->SetMarker(nextPos, streamFrom_Start);
	mYCoord += sTgbPaneInfo.height + kTmplVertSep;
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//	¥ AddHexDumpField													[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddHexDumpField(OSType inType, LView * inContainer)
{
	SInt32		oldPos, newPos, totalLength;
	Handle		theHandle;
	SViewInfo	theViewInfo;
	SDimension16	theFrame;

	inContainer->GetFrameSize(theFrame);
	mOwnerDoc = dynamic_cast<CTmplEditorDoc*>(GetSuperCommander());

	theViewInfo.imageSize.width		= theViewInfo.imageSize.height	= 0 ;
	theViewInfo.scrollPos.h			= theViewInfo.scrollPos.v		= 0;
	theViewInfo.scrollUnit.h		= theViewInfo.scrollUnit.v		= 1;
	theViewInfo.reconcileOverhang	= false;
	
	sTgbPaneInfo.top				= mYCoord;
	sTgbPaneInfo.left				= kTmplTextMargin;
	sTgbPaneInfo.width				= theFrame.width - kTmplTextMargin * 2;
	sTgbPaneInfo.paneID				= mCurrentID;
	sTgbPaneInfo.superView			= inContainer;
	CDualDataView * theTGB = new CDualDataView(sTgbPaneInfo, theViewInfo, false);
	ThrowIfNil_(theTGB);

	// Make the single vertical scroll bar
	sScrollPaneInfo.left			= sTgbPaneInfo.width - kTmplTextInset - kTmplScrollWidth;
	sScrollPaneInfo.top				= kTmplTextInset;
	sScrollPaneInfo.width			= kTmplScrollWidth;
	sScrollPaneInfo.height			= sTgbPaneInfo.height - kTmplTextInset * 2;
	sScrollPaneInfo.bindings.left	= false;
	sScrollPaneInfo.paneID			= 0;
	sScrollPaneInfo.superView		= theTGB;

	CSingleScrollBar * theScroller = new CSingleScrollBar(sScrollPaneInfo, msg_HexScroller, 0, 0, 0, true);
	ThrowIfNil_(theScroller);

	// Make the Waste edit panes: they are, by default, selectable with 
	// wrapping on (so that the image size is recalculated automatically 
	// when the frame size changes). The read only property is set 
	// by InstallSubViews() below.
	sWastePaneInfo.left				= kTmplTextInset;
	sWastePaneInfo.top				= kTmplTextInset;
	sWastePaneInfo.width			= kTmplHexPaneWidth;
	sWastePaneInfo.height			= sScrollPaneInfo.height;
	sWastePaneInfo.bindings.left	= false;
	sWastePaneInfo.bindings.right	= false;
	sWastePaneInfo.paneID			= 0;
	sWastePaneInfo.superView		= theTGB;

	CHexDataSubView * theHexWE = new CHexDataSubView(sWastePaneInfo, theViewInfo, 0, sEditTraitsID);
	ThrowIfNil_(theHexWE);

	sWastePaneInfo.left				= kTmplTxtPaneLeft;
	sWastePaneInfo.width			= kTmplTxtPaneWidth;
	
	CTxtDataSubView * theTxtWE = new CTxtDataSubView(sWastePaneInfo, theViewInfo, 0, sEditTraitsID);
	ThrowIfNil_(theTxtWE);
	
	// Add to the mWasteFieldsList
	mWasteFieldsList.AddItem(theHexWE);
	mWasteFieldsList.AddItem(theTxtWE);
	
	// Install the subpanes and the scroller in the dual view
	theTGB->InstallSubViews(theHexWE, theTxtWE, theScroller, mOwnerDoc->IsReadOnly() );

	// Adjust to the style specified in the preferences
	TextTraitsRecord theTraits = CRezillaPrefs::GetStyleElement( CRezillaPrefs::prefsType_Curr );
	theTGB->ResizeDataPanes();
	theTGB->UpdatePaneCounts();
	theHexWE->ApplyStyleValues( theTraits.size, theTraits.fontNumber);
	theTxtWE->ApplyStyleValues( theTraits.size, theTraits.fontNumber);
	
	// Store the template's type in the userCon field
	theTGB->SetUserCon(inType);
	
	// Insert the text
	totalLength = mRezStream->GetLength();
	oldPos = mRezStream->GetMarker();

	switch (inType) {
		case 'HEXD':
		// This is always the last code in a template. Go to the end of the
		// resource data.
		newPos = totalLength;
		break;
		
		case 'BHEX': {
			UInt32		theUInt8 = 0;
			// ByteLength Hex Dump
			if (mRezStream->GetMarker() < totalLength) {
				*mRezStream >> theUInt8;
			}
			oldPos += 1;
			newPos = oldPos + theUInt8;
			break;
		}
		
		case 'BSHX': {
			UInt32		theUInt8 = 0;
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
			UInt32		theUInt32 = 0;
			// LongLength Hex Dump
			if (mRezStream->GetMarker() < totalLength - 3) {
				*mRezStream >> theUInt32;
			}
			oldPos += 4;
			newPos = oldPos + theUInt32;
			break;
		}
		
		case 'LSHX': {
			UInt32		theUInt32 = 0;
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
			UInt16		theUInt16 = 0;
			// WordLength Hex Dump
			if (mRezStream->GetMarker() < totalLength - 1) {
				*mRezStream >> theUInt16;
			}
			oldPos += 2;
			newPos = oldPos + theUInt16;
			break;
		}
		
		case 'WSHX': {
			UInt16		theUInt16 = 0;
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
		
		default:
		if (inType >> 24 == 'H' || inType >> 24 == 'F') {
			// Hnnn: a 3-digit hex number; displays $nnn bytes in hex format
			SInt32 numbytes;
			UMiscUtils::HexNumStringToDecimal(&inType, &numbytes);
			newPos = oldPos + numbytes;
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
	
	theHandle = mRezStream->GetDataHandle();
	HLock(theHandle);
	theTGB->InstallBackStoreData((*theHandle) + oldPos , newPos - oldPos);
	theTGB->SetMaxScrollerValue();
	theTGB->InstallContentsFromLine(1);
	HUnlock(theHandle);

	WESetSelection(0, 0, theTGB->GetInMemoryWasteRef());

	// Fnnn filler hex strings are uneditable
	if (inType >> 24 == 'F') {
		theTGB->Disable();
	} 
	
	// Advance the counters
	mRezStream->SetMarker(newPos, streamFrom_Start);
	mYCoord += sTgbPaneInfo.height + kTmplVertSep;
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//	¥ AddPointField													[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddPointField(SInt16 inX, 
								SInt16 inY, 
								OSType inType,
								SInt16 inMaxChars, 
								UInt8 inAttributes,
								TEKeyFilterFunc inKeyFilter,
								LView * inContainer)
{
	Str255	numStr;
	LEditText * theEditText;
	LStaticText * theStaticText;
	SViewInfo	theViewInfo;
	theViewInfo.imageSize.width		= theViewInfo.imageSize.height	= 0 ;
	theViewInfo.scrollPos.h			= theViewInfo.scrollPos.v		= 0;
	theViewInfo.scrollUnit.h		= theViewInfo.scrollUnit.v		= 1;
	theViewInfo.reconcileOverhang	= false;

	sRectLabelInfo.top			= mYCoord;
	sRectLabelInfo.left 		= kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep;
	sRectLabelInfo.superView	= inContainer;

	sRectPaneInfo.top		= mYCoord + kTmplRectHeight;
	sRectPaneInfo.left		= sRectLabelInfo.left;
	sRectPaneInfo.superView	= inContainer;

	// X coord
	theStaticText = new LStaticText(sRectLabelInfo, "\pHoriz", sEditTraitsID);
	ThrowIfNil_(theStaticText);
	sRectPaneInfo.paneID = mCurrentID;
	::NumToString( (long) inX, numStr);
	theEditText = new LEditText(sRectPaneInfo, this, numStr, sEditTraitsID, 
								msg_TmplModifiedItem, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);
	theEditText->SetUserCon(inType);
	// Let the window listen to this field
	theEditText->AddListener(this);
	mCurrentID++;

	// Y coord
	sRectLabelInfo.left += kTmplRectWidth + kTmplHorizSep;
	theStaticText = new LStaticText(sRectLabelInfo, "\pVert", sEditTraitsID);
	ThrowIfNil_(theStaticText);
	sRectPaneInfo.left += kTmplRectWidth + kTmplHorizSep;
	sRectPaneInfo.paneID = mCurrentID;
	::NumToString( (long) inY, numStr);
	theEditText = new LEditText(sRectPaneInfo, this, numStr, sEditTraitsID, 
								msg_TmplModifiedItem, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);
	theEditText->SetUserCon(inType);
	// Let the window listen to this field
	theEditText->AddListener(this);
	mCurrentID++;

	// Advance the counters
	mYCoord += (kTmplRectHeight * 2) + kTmplVertSep + kTmplVertSep;
}


// ---------------------------------------------------------------------------
//	¥ AddRectField													[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddRectField(SInt16 inTop, 
								SInt16 inLeft, 
								SInt16 inBottom, 
								SInt16 inRight, 
								OSType inType,
								SInt16 inMaxChars, 
								UInt8 inAttributes,
								TEKeyFilterFunc inKeyFilter,
								LView * inContainer)
{
	Str255	numStr;
	LEditText * theEditText;
	LStaticText * theStaticText;
	SViewInfo	theViewInfo;
	theViewInfo.imageSize.width		= theViewInfo.imageSize.height	= 0 ;
	theViewInfo.scrollPos.h			= theViewInfo.scrollPos.v		= 0;
	theViewInfo.scrollUnit.h		= theViewInfo.scrollUnit.v		= 1;
	theViewInfo.reconcileOverhang	= false;

	sRectLabelInfo.top			= mYCoord;
	sRectLabelInfo.left 		= kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep;
	sRectLabelInfo.superView	= inContainer;

	sRectPaneInfo.top		= mYCoord + kTmplRectHeight;
	sRectPaneInfo.left		= sRectLabelInfo.left;
	sRectPaneInfo.superView	= inContainer;

	// Top
	theStaticText = new LStaticText(sRectLabelInfo, "\pTop", sEditTraitsID);
	ThrowIfNil_(theStaticText);
	sRectPaneInfo.paneID = mCurrentID;
	::NumToString( (long) inTop, numStr);
	theEditText = new LEditText(sRectPaneInfo, this, numStr, sEditTraitsID, 
								msg_TmplModifiedItem, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);
	theEditText->SetUserCon(inType);
	// Let the window listen to this field
	theEditText->AddListener(this);
	mCurrentID++;

	// Left
	sRectLabelInfo.left += kTmplRectWidth + kTmplHorizSep;
	theStaticText = new LStaticText(sRectLabelInfo, "\pLeft", sEditTraitsID);
	ThrowIfNil_(theStaticText);
	sRectPaneInfo.left += kTmplRectWidth + kTmplHorizSep;
	sRectPaneInfo.paneID = mCurrentID;
	::NumToString( (long) inLeft, numStr);
	theEditText = new LEditText(sRectPaneInfo, this, numStr, sEditTraitsID, 
								msg_TmplModifiedItem, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);
	theEditText->SetUserCon(inType);
	// Let the window listen to this field
	theEditText->AddListener(this);
	mCurrentID++;

	// Bottom
	sRectLabelInfo.left += kTmplRectWidth + kTmplHorizSep;
	theStaticText = new LStaticText(sRectLabelInfo, "\pBottom", sEditTraitsID);
	ThrowIfNil_(theStaticText);
	sRectPaneInfo.left += kTmplRectWidth + kTmplHorizSep;
	sRectPaneInfo.paneID = mCurrentID;
	::NumToString( (long) inBottom, numStr);
	theEditText = new LEditText(sRectPaneInfo, this, numStr, sEditTraitsID, 
								msg_TmplModifiedItem, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);
	theEditText->SetUserCon(inType);
	// Let the window listen to this field
	theEditText->AddListener(this);
	mCurrentID++;

	// Right
	sRectLabelInfo.left += kTmplRectWidth + kTmplHorizSep;
	theStaticText = new LStaticText(sRectLabelInfo, "\pRight", sEditTraitsID);
	ThrowIfNil_(theStaticText);
	sRectPaneInfo.left += kTmplRectWidth + kTmplHorizSep;
	sRectPaneInfo.paneID = mCurrentID;
	::NumToString( (long) inRight, numStr);
	theEditText = new LEditText(sRectPaneInfo, this, numStr, sEditTraitsID, 
								msg_TmplModifiedItem, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);
	theEditText->SetUserCon(inType);
	// Let the window listen to this field
	theEditText->AddListener(this);
	mCurrentID++;

	// Advance the counters
	mYCoord += (kTmplRectHeight * 2) + kTmplVertSep + kTmplVertSep;
}


// ---------------------------------------------------------------------------
//	¥ AddListHeaderField											[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddListHeaderField(OSType inType, 
									  Str255 inLabel, 
									  short inCount, 
									  Str255 inCountLabel, 
									  LView * inContainer, 
									  Boolean isFixedCount)
{
	Str255			numStr;
	LStaticText *	theStaticText;
	CTmplListButton *	thePushButton;
	
	// This is the label of the list (usually "*****")
	sStaticPaneInfo.left		= kTmplLeftMargin;
	sStaticPaneInfo.top			= mYCoord;
	sStaticPaneInfo.width		= kTmplLabelWidth;
	sStaticPaneInfo.superView	= inContainer;

	theStaticText = new LStaticText(sStaticPaneInfo, inLabel, sHeaderTraitsID);
	ThrowIfNil_(theStaticText);

	if (inType == 'LSTC') {
		mYCoord += kTmplEditHeight;
		// This is the label of the OCNT, ZCNT or FCNT counts
		sStaticPaneInfo.top		= mYCoord;
		sStaticPaneInfo.width	= kTmplLabelWidth;
		theStaticText = new LStaticText(sStaticPaneInfo, inCountLabel, sRightLabelTraitsID);
		ThrowIfNil_(theStaticText);
		
		// This is the value of the OCNT, ZCNT or FCNT counts
		sStaticPaneInfo.left 	+= sStaticPaneInfo.width + kTmplHorizSep;
		sStaticPaneInfo.width	= kTmplCountWidth;
		sStaticPaneInfo.paneID 	= mCurrentID;
		::NumToString( (long) inCount, numStr);
		theStaticText = new LStaticText(sStaticPaneInfo, numStr, sHeaderTraitsID);
		ThrowIfNil_(theStaticText);
		
		sStaticPaneInfo.paneID = 0;
		mCurrentID++;
	}
	
	sPushPaneInfo.top		= sStaticPaneInfo.top - 3;
	sPushPaneInfo.left		= sStaticPaneInfo.left + sStaticPaneInfo.width + kTmplHorizSep;
	sPushPaneInfo.paneID	= mCurrentID;
	sPushPaneInfo.superView	= inContainer;
	
	thePushButton = new CTmplListButton(sPushPaneInfo, msg_TmplMinusButton, "\p-");
	ThrowIfNil_(thePushButton);
	// Store the current position in the template stream
	thePushButton->SetUserCon( mTemplateStream->GetMarker());
	// Let the window listen to this button
	thePushButton->AddListener(this);
	if (isFixedCount) {
		thePushButton->Disable();
	} 
	mCurrentID++;
	
	sPushPaneInfo.left		+= kTmplCountWidth + kTmplHorizSep;
	sPushPaneInfo.paneID	= mCurrentID;
	thePushButton = new CTmplListButton(sPushPaneInfo, msg_TmplPlusButton, "\p+");
	ThrowIfNil_(thePushButton);
	// The UserCon field will contain a pointer to the first ListItemView. Initialize with nil.
	thePushButton->SetUserCon(nil);
	// Let the window listen to this button
	thePushButton->AddListener(this);
	if (isFixedCount) {
		thePushButton->Disable();
	} 

	mCurrentID++;

	// Advance the counters
	mYCoord += sStaticPaneInfo.height + kTmplVertSep + kTmplVertSkip;
}
 

// ---------------------------------------------------------------------------
//	¥ AddListItemView											[public]
// ---------------------------------------------------------------------------

CTmplListItemView *
CTmplEditorWindow::AddListItemView(CTmplListItemView * inPrevListItemView, LView * inContainer)
{
	SDimension16	theFrame;
	
	SViewInfo	theViewInfo;
	theViewInfo.imageSize.width		= theViewInfo.imageSize.height	= 0 ;
	theViewInfo.scrollPos.h			= theViewInfo.scrollPos.v		= 0;
	theViewInfo.scrollUnit.h		= theViewInfo.scrollUnit.v		= 1;
	theViewInfo.reconcileOverhang	= false;
	
	inContainer->GetFrameSize(theFrame);

	sListItemInfo.paneID			= 0;
	sListItemInfo.top				= mYCoord;
	sListItemInfo.left				= kTmplTextMargin + mIndent;
	sListItemInfo.width				= theFrame.width - sListItemInfo.left - kTmplHorizSep;
	sListItemInfo.superView			= inContainer;
	
	CTmplListItemView * theLIV = new CTmplListItemView(sListItemInfo, theViewInfo, false);
	ThrowIfNil_(theLIV);

	theLIV->mPrevItem = inPrevListItemView;
	if (inPrevListItemView != nil) {
		inPrevListItemView->mNextItem = theLIV;
	} 

	theLIV->mFirstItemID = mCurrentID;

	return theLIV;
}


// ---------------------------------------------------------------------------
//	¥ AddSeparatorLine											[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddSeparatorLine(LView * inContainer)
{
	SDimension16	theFrame;

	inContainer->GetFrameSize(theFrame);
// 	sSeparatorPaneInfo.left			= kTmplLabelWidth + kTmplLeftMargin;
	sSeparatorPaneInfo.left			= kTmplLeftMargin;
	sSeparatorPaneInfo.top			= mYCoord;
// 	sSeparatorPaneInfo.width		= theFrame.width - kTmplLabelWidth - kTmplLeftMargin * 2;
	sSeparatorPaneInfo.width		= theFrame.width - kTmplLeftMargin * 2;
	sSeparatorPaneInfo.superView	= inContainer;

	LSeparatorLine * theSeparator = new LSeparatorLine(sSeparatorPaneInfo);
	ThrowIfNil_(theSeparator);
	
	// Advance the counters
	mYCoord += sSeparatorPaneInfo.height + kTmplVertSep;
}


// ---------------------------------------------------------------------------
//	¥ AddCasePopup													[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddCasePopup(ResType inType, Str255 inLabel, SInt32 inStartMark, LView * inContainer)
{
	SDimension16	theFrame;
	SInt16			index = 1, foundIdx = -1;
	ResType			theType;
	SInt32			currMark, totalLength = mTemplateStream->GetLength();
	Str255			theString, theValue;
	Str255 * 		rightPtr;

	inContainer->GetFrameSize(theFrame);
	sBevelPaneInfo.left			= theFrame.width - sBevelPaneInfo.width - 5;
	sBevelPaneInfo.top			= mYCoord - sEditPaneInfo.height -kTmplVertSep -1;
	sBevelPaneInfo.paneID		= mCurrentID;
	sBevelPaneInfo.superView	= inContainer;

	CTmplBevelButton * theBevelButton = new CTmplBevelButton(sBevelPaneInfo, msg_TmplCasePopup, kControlBevelButtonSmallBevelProc,
													 rMENU_TemplateCases, kControlBevelButtonMenuOnBottom, 
													 kControlContentTextOnly, 0, 0, Str_Empty, 1, 
													 kControlBevelButtonPlaceNormally, teFlushDefault, 0, 
													 kControlBevelButtonAlignCenter, Point_00, true);													 
	ThrowIfNil_(theBevelButton);

	// Let the window listen to this menu
	theBevelButton->AddListener(this);
	
	// Store a pointer to the associated edit field
	LEditText * theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID - 1));
	theBevelButton->SetUserCon( (long) theEditText);
	// Store the position mark of the first CASE in the userCon of the edit field
	theEditText->SetUserCon(inStartMark);
	// Retrieve the value of the associated edit field
	theEditText->GetDescriptor(theValue);
	
	// Let the popup listen to the edit field
	theEditText->AddListener(theBevelButton);

	// Populate the popup with all the successive cases
	if ( SplitCaseValue(inLabel, &rightPtr) ) {
		theBevelButton->InsertMenuItem(inLabel, index, true);
		if (rightPtr != NULL && UMiscUtils::CompareStr255( (Str255 *) theValue, rightPtr) == 0) {
			foundIdx = index;
		} 
	} 
	currMark = mTemplateStream->GetMarker();
	while (currMark < totalLength) {
		*mTemplateStream >> theString;
		*mTemplateStream >> theType;
		if (theType != inType) {
			// We went too far. Reposition the stream marker.
			mTemplateStream->SetMarker(currMark, streamFrom_Start);
			break;
		} 
		currMark = mTemplateStream->GetMarker();
		index++;
		if ( SplitCaseValue(theString, &rightPtr) ) {
			theBevelButton->InsertMenuItem(theString, index, true);
			if (foundIdx == -1 && rightPtr != NULL && UMiscUtils::CompareStr255( (Str255 *) theValue, rightPtr) == 0) {
				foundIdx = index;
			} 
		} 
	}
	
	// Mark the item corresponding to the value
	if (foundIdx != -1) {
		theBevelButton->SetCurrentMenuItem(foundIdx);						
	} else {
		::MacCheckMenuItem(theBevelButton->GetMacMenuH(), theBevelButton->GetCurrentMenuItem(), 0);
	}
	
	// Advance the counters. mYCoord has already been increased by the edit field
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//	¥ AddEditPopup													[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddEditPopup(Str255 inValue, 
								OSType inType,
								SInt16 inMaxChars, 
								SInt16 inWidth,
								UInt8 inAttributes,
								TEKeyFilterFunc inKeyFilter, 
								ResIDT inResourceID,
								LView * inContainer)
{
	SDimension16	theFrame;
	SInt16			index = 1, foundIdx = -1;
	SInt32			totalLength = mTemplateStream->GetLength();
	Str255			theString;
	Str255 * 		rightPtr;

	inContainer->GetFrameSize(theFrame);

	sEditPaneInfo.left		= kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep;
	sEditPaneInfo.width		= inWidth;
	sEditPaneInfo.top		= mYCoord - 3;
	sEditPaneInfo.paneID	= mCurrentID;
	sEditPaneInfo.superView	= inContainer;

	LEditText * theEditText = new LEditText(sEditPaneInfo, this, inValue, sEditTraitsID, 
											msg_TmplModifiedItem, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);

	// Store the template's type in the userCon field
	theEditText->SetUserCon(inType);
	
	// Let the window listen to this field
	theEditText->AddListener(this);

	// Incr the pane ID
	mCurrentID++;

	// Now build the popup
	sBevelPaneInfo.left			= sEditPaneInfo.left + inWidth + kTmplHorizSep;
	sBevelPaneInfo.top			= sEditPaneInfo.top + 2;
	sBevelPaneInfo.paneID		= mCurrentID;
	sBevelPaneInfo.superView	= inContainer;

	CTmplBevelButton * theBevelButton = new CTmplBevelButton(sBevelPaneInfo, msg_TmplPopupField, kControlBevelButtonSmallBevelProc,
													 rMENU_TemplateCases, kControlBevelButtonMenuOnBottom, 
													 kControlContentTextOnly, 0, 0, Str_Empty, 1, 
													 kControlBevelButtonPlaceNormally, teFlushDefault, 0, 
													 kControlBevelButtonAlignCenter, Point_00, true);													 
	ThrowIfNil_(theBevelButton);

	// Let the window listen to this menu
	theBevelButton->AddListener(this);
	
	// Populate the popup with the items from the STR# resource with ID inResourceID
	while (true) {
		GetIndString(theString, inResourceID, index);
		if ( SplitCaseValue(theString, &rightPtr) ) {
			theBevelButton->InsertMenuItem(theString, index, true);
			if (foundIdx == -1 && rightPtr != NULL && UMiscUtils::CompareStr255( (Str255 *) inValue, rightPtr) == 0) {
				foundIdx = index;
			} 
			index++;
		} else {
			break;
		}
	} 
	
	// Store a pointer to the associated edit field
	theBevelButton->SetUserCon( (long) theEditText);
	// Store the STR# resource ID in the userCon of the edit field
	theEditText->SetUserCon(inResourceID);
	
	// Let the popup listen to the edit field
	theEditText->AddListener(theBevelButton);

	// Mark the item corresponding to the value
	if (foundIdx != -1) {
		theBevelButton->SetCurrentMenuItem(foundIdx);						
	} else {
		::MacCheckMenuItem(theBevelButton->GetMacMenuH(), theBevelButton->GetCurrentMenuItem(), 0);
	}

	// Advance the counters
	mYCoord += sEditPaneInfo.height + kTmplVertSep;
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//	¥ AddColorPane													[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddColorPane(OSType inType, 
								LView * inContainer, 
								RGBColor * inRGB)
{
	sColorPaneInfo.left			= kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep;
	sColorPaneInfo.top			= mYCoord;
	sColorPaneInfo.superView	= inContainer;
	sColorPaneInfo.paneID		= mCurrentID;
	
	CColorWell * theWell = new CColorWell(sColorPaneInfo, inRGB, msg_TmplModifiedItem);
	ThrowIfNil_(theWell);

	// Let the window listen to this control
	theWell->AddListener(this);

	// Advance the counters
	mYCoord += sColorPaneInfo.height + kTmplVertSep;
	mCurrentID++;
}



