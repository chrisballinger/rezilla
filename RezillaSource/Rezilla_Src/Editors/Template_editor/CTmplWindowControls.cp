// ===========================================================================
// CTmplWindowControls.cp
// 
//                       Created: 2004-08-20 16:45:08
//             Last modification: 2006-09-07 12:38:04
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes, 2004-2006
// All rights reserved.
// ===========================================================================
// Implements the functions defining the various fields and controls in the 
// CTmplEditorWindow class.


#include "CTmplEditorWindow.h"
#include "CTmplEditorDoc.h"
#include "CTmplListItemView.h"
#include "CTmplListButton.h"
#include "CTmplCaseField.h"
#include "CTmplRSIDField.h"
#include "CFlagPopup.h"
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
#include "CPopupEditField.h"
#include "UCompareUtils.h"
#include "UMiscUtils.h"
#include "UMessageDialogs.h"
#include "CRezMapTable.h"
#include "CRezMap.h"

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

#ifndef __MACH__
#include <ControlDefinitions.h>
#endif

#include <stdio.h>
#include <string.h>



// ---------------------------------------------------------------------------
//   InitPaneInfos												[static]
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
	sTgbPaneInfo.height				= kTmplTextMaxHeight;
	sTgbPaneInfo.visible			= true;
	sTgbPaneInfo.enabled			= true;
	sTgbPaneInfo.bindings.top		= false;
	sTgbPaneInfo.bindings.left		= true;
	sTgbPaneInfo.bindings.bottom	= false;
	sTgbPaneInfo.bindings.right		= true;
	sTgbPaneInfo.userCon			= 0;

	// Text views basic values
	sWastePaneInfo.paneID			= 0;
	sWastePaneInfo.visible			= true;
	sWastePaneInfo.enabled			= true;
	sWastePaneInfo.bindings.top		= true;
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
	sBevelPaneInfo.bindings.right	= false;
	sBevelPaneInfo.bindings.bottom 	= false;
	sBevelPaneInfo.userCon			= 0;

	// Flag popup button fields basic values
	sPopupPaneInfo.width			= kTmplPopupWidth;
	sPopupPaneInfo.height			= kTmplPopupHeight;
	sPopupPaneInfo.visible			= true;
	sPopupPaneInfo.enabled			= true;
	sPopupPaneInfo.bindings.left	= false;
	sPopupPaneInfo.bindings.top		= false;
	sPopupPaneInfo.bindings.right	= false;
	sPopupPaneInfo.bindings.bottom 	= false;
	sPopupPaneInfo.userCon			= 0;

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
//   AddStaticField													[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddStaticField(OSType inType, Str255 inLabel, LView * inContainer, 
								  ResIDT inTextTraitsID, SInt32 inReqLength, Boolean fullWidth)
{
	Str255		theString;
	LStr255		theLabel(inLabel);
	
	sStaticPaneInfo.left		= kTmplLeftMargin;
	sStaticPaneInfo.top			= mYCoord;
	sStaticPaneInfo.superView	= inContainer;
	
	// For a comment label (DVDR) extend the width to the entire window.
	// Ditto for a sized hex/txt field to ensure the extended label fits in.
	if (inType == 'DVDR' || fullWidth) {
		SDimension16	theFrame;
		inContainer->GetFrameSize(theFrame);
		sStaticPaneInfo.width = theFrame.width - kTmplLeftMargin * 2;
	} else {
		sStaticPaneInfo.width = kTmplLabelWidth;
	}

	if (inReqLength > 0) {
		::NumToString( inReqLength, theString);
		theLabel += "\p (";
		theLabel.Append(theString);
		theLabel += "\p bytes)";
	} 
	LStaticText * theStaticText = new LStaticText(sStaticPaneInfo, theLabel, inTextTraitsID);
	ThrowIfNil_(theStaticText);
}


// ---------------------------------------------------------------------------
//   AddEditField													[public]
// ---------------------------------------------------------------------------
// If the inWidth argument is not 0, it is used to impose the width of the
// EditField. If it is 0, the width is calculated using the inMaxChars
// argument:
// - if (kTmplEditMinFixedChars <= inMaxChars <= kTmplEditMaxFixedChars),
//   the width is calculated to fit exactly with this number of chars. The
//   field is not bound to the right edge of the window.
// - if (inMaxChars > kTmplEditMaxFixedChars), the width is calculated to
//   extend to the right edge of the container and the field is bound to
//   the right edge of the window.
// - if (inMaxChars < kTmplEditMinFixedChars), the width is adjusted to
//   kTmplEditMaxFixedChars and the field is not resizeable.

void
CTmplEditorWindow::AddEditField(Str255 inValue, 
								OSType inType,
								SInt16 inMaxChars, 
								SInt16 inWidth,
								TEKeyFilterFunc inKeyFilter, 
								LView * inContainer)
{
	LEditText *			theEditText;
	CTmplCaseField *	theCaseField;
	SDimension16		theFrame;
	Boolean				incrY = true, hasCases;
	
	inContainer->GetFrameSize(theFrame);

	sEditPaneInfo.left				= kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep;
	sEditPaneInfo.top				= mYCoord - 3;
	sEditPaneInfo.paneID			= mCurrentID;
	sEditPaneInfo.superView			= inContainer;
	sEditPaneInfo.bindings.right	= true;

	if (inWidth > 0) {
		sEditPaneInfo.width = inWidth;
	} else {
		if (inMaxChars > kTmplEditMaxFixedChars) {
			sEditPaneInfo.width = theFrame.width - kTmplLeftMargin * 2 - kTmplLabelWidth - kTmplHorizSep - kTmplHorizSkip;
		} else {
			// Add space for three more chars
			sEditPaneInfo.width = kTmplEditUnitWidth * (((inMaxChars < kTmplEditMinFixedChars)? kTmplEditMinFixedChars : inMaxChars) + 3);
			sEditPaneInfo.bindings.right = false;
		}
	}
	
	hasCases = NextIsCase();
	
	if (hasCases) {
		theCaseField = new CTmplCaseField(sEditPaneInfo, this, inValue,
										sEditTraitsID, msg_EditorModifiedItem,
										msg_TmplCasePopup, inMaxChars, 0, inKeyFilter, 
										mTemplateStream, mTemplateStream->GetMarker());

		// Let the window listen to this field
		theCaseField->AddListener(this);
		// Set the paneID: if paneID is 0, clicks in ListItemViews are ignored
		theCaseField->GetPopup()->SetPaneID(mCurrentID + 1);
		// Leave a msg in the userCon to remember that the field has a popup
		theCaseField->SetUserCon(msg_EditFieldHasCases);
	} else {
		theEditText = new LEditText(sEditPaneInfo, this, inValue, sEditTraitsID, 
										msg_EditorModifiedItem, inMaxChars, 0, inKeyFilter);
		ThrowIfNil_(theEditText);
		// Let the window listen to this field
		theEditText->AddListener(this);
	}
	
	// Filler types can be invisible or disabled
	if (inType == 'FBYT' || inType == 'FWRD' || inType == 'FLNG') {
		if ( ! CRezillaPrefs::GetPrefValue(kPref_templates_displayFillers) ) {
			if (hasCases) {
				theCaseField->Hide();
			} else {
				theEditText->Hide();
			}
			incrY = false;	
		} else if ( ! CRezillaPrefs::GetPrefValue(kPref_templates_enableFillers) ) {
			if (hasCases) {
				theCaseField->Disable();
			} else {
				theEditText->Disable();
			}
		} 
	} else if (inType=='TNAM') {
		// ZP feature #9, part 4
		mPrevTnam = (theEditText ? theEditText : theCaseField );
	}
	
	// Advance the counters
	if (incrY) {
		mYCoord += sEditPaneInfo.height + kTmplVertSep;
	} 
	// Caution: this is the ID of the Edit field, not the ID of the Case 
	// popup
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;
	if (hasCases) {
		// The Case popup has received ID = mCurrentID + 1 (above)
		mPaneIDs.AddItem(mCurrentID);
		mCurrentID++;
	}
}


// ---------------------------------------------------------------------------
//   AddBooleanField											[public]
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
	
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;

	// Create two radiobuttons in this group
	//     "Yes/On" radiobutton
	sRadioPaneInfo.left			= 0;
	sRadioPaneInfo.top			= 0;
	sRadioPaneInfo.paneID		= mCurrentID;
	sRadioPaneInfo.superView	= theRGV;

	theRadio = new LStdRadioButton(sRadioPaneInfo, msg_EditorModifiedItem, 
								   inValue, sLeftLabelTraitsID, (UInt8 *)(inTitleType ? "\pOn":"\pYes"));
	ThrowIfNil_(theRadio);
	
	// Add to the radio-group
	theRGV->AddRadio(theRadio);
	
	// Let the window listen to this button
	theRadio->AddListener(this);
	
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;

	//     "No/Off" radiobutton
	sRadioPaneInfo.left += kTmplRadioWidth + kTmplHorizSep;
	sRadioPaneInfo.paneID = mCurrentID;

	theRadio = new LStdRadioButton(sRadioPaneInfo, msg_EditorModifiedItem, 
								   1 - inValue, sLeftLabelTraitsID, (UInt8 *)(inTitleType ? "\pOff":"\pNo"));
	ThrowIfNil_(theRadio);
	
	// Add to the radio-group
	theRGV->AddRadio(theRadio);
	
	// Let the window listen to this button
	theRadio->AddListener(this);

	theRGV->SetCurrentRadioID( inValue ?  mCurrentID - 1 : mCurrentID );
	
	// Advance the counters
	mYCoord += sRgvPaneInfo.height + kTmplVertSep;
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//   AddBitField											[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddBitField(OSType inType,
							   Str255 inLabel,
							   UInt16 inBitCount, 
							   UInt16 inBytesLen,
							   LView * inContainer)
{
	SInt8	i;
	UInt8	theUInt8;
	UInt16	theUInt16;
	UInt32	val;
	Str255	numStr;
	
	if (!mBitSeqInProgress) {
		mBitSeqInProgress = true;
		mBitSeqBytesLen = inBytesLen;
		// The first bit enumerated in a template is the highest bit.
		mBitSeqIndex = mBitSeqBytesLen * 8 - 1;
		if (mRezStream->GetMarker() < mRezStream->GetLength() - mBitSeqBytesLen + 1) {
			switch (mBitSeqBytesLen) {
				case 1:
				*mRezStream >> theUInt8;
				mBitSeqValue = theUInt8;
				break;
				
				case 2:
				*mRezStream >> theUInt16;
				mBitSeqValue = theUInt16;
				break;
				
				case 4:
				*mRezStream >> mBitSeqValue;
				break;
				
			}
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
		for (i = 0; i < inBitCount; i++) {
			val |= mBitSeqValue & (1 << mBitSeqIndex);
			mBitSeqIndex--;
		}
		val = val >> (mBitSeqIndex + 1);
		
		::NumToString( (long) val, numStr);
		AddEditField(numStr, inType, 2 * mBitSeqBytesLen + 1 + (mBitSeqBytesLen == 4), 
					 0, UKeyFilters::SelectTEKeyFilter(keyFilter_Integer), inContainer);
	}
	
	if (mBitSeqIndex < 0) {
		mBitSeqInProgress = false;
	} 
}


// ---------------------------------------------------------------------------
//   AddCheckField											[public]
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

	LCheckBox * theCheck = new LCheckBox(sCheckPaneInfo, msg_EditorModifiedItem, inValue);
	ThrowIfNil_(theCheck);
		
	// Store the template's type in the userCon field
	theCheck->SetUserCon(inType);
	
	// Let the window listen to this button
	theCheck->AddListener(this);

	// Advance the counters
	mYCoord += sCheckPaneInfo.height + kTmplVertSep;
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//   AddWasteField													[public]
// ---------------------------------------------------------------------------
// C string. This should be either characters followed by a null or all
// the chars until the end of the stream if there is no null byte.
// The height of the WE depends on the estimated number of lines. Moreover,
// if the size is fixed and the text fits in the frame, we don't need a
// scrollbar. 
// The strategy is to first create the WE inside the container in order to
// get an estimate of the number of lines. Then we decide if a scrollbar is
// necessary: if yes, the WE must be made a subpane of the scrollbar and
// its associated scrolling view.

void
CTmplEditorWindow::AddWasteField(OSType inType, LView * inContainer, SInt32 inReqLength)
{
	SInt32		oldPos, newPos, nextPos, reqLength = inReqLength;
	Handle		theHandle;
	Boolean		isFixed = false, hasText, canReduce;
	SViewInfo	theViewInfo;
	SDimension16	theFrame;
	SInt16		boxHeight = sTgbPaneInfo.height, delta = 0;
	
	// Calculate the limits of the text	to insert
	hasText = CalcTextPositions(inType, oldPos, newPos, nextPos, reqLength, isFixed);
	
	// Install the overall container
	inContainer->GetFrameSize(theFrame);

	sTgbPaneInfo.top				= mYCoord;
	sTgbPaneInfo.left				= kTmplTextMargin;
	sTgbPaneInfo.width				= theFrame.width - kTmplTextMargin * 2;
	sTgbPaneInfo.paneID				= 0;
	sTgbPaneInfo.superView			= inContainer;

	theViewInfo.imageSize.width		= theViewInfo.imageSize.height	= 0 ;
	theViewInfo.scrollPos.h			= theViewInfo.scrollPos.v		= 0;
	theViewInfo.scrollUnit.h		= theViewInfo.scrollUnit.v		= CRezillaApp::sBasics.charHeight;
	theViewInfo.reconcileOverhang	= false;
	
	LTextGroupBox * theTGB = new LTextGroupBox(sTgbPaneInfo, theViewInfo, false);
	ThrowIfNil_(theTGB);

	// Install the WasteEdit view
	sWastePaneInfo.left				= kTmplTextInset;
	sWastePaneInfo.top				= kTmplTextHeadHeight;
	sWastePaneInfo.width			= sTgbPaneInfo.width - kTmplTextInset * 2 - kTmplScrollWidth;
	sWastePaneInfo.height			= boxHeight - kTmplTextHeadHeight - kTmplTextFootHeight;
	sWastePaneInfo.bindings.left	= true;
	sWastePaneInfo.bindings.right	= true;
	sWastePaneInfo.paneID			= mCurrentID;
	sWastePaneInfo.superView		= theTGB;
	
	// Make the Waste edit writable, not wrapping, selectable
	CWasteEditView * theWE = new CWasteEditView(this, sWastePaneInfo, theViewInfo, 0, sEditTraitsID, true, mOwnerDoc->IsReadOnly());
	ThrowIfNil_(theWE);
	// Store the template's type in the userCon field
	theWE->SetUserCon(inType);
	
	// Adjust to the style specified in the preferences
	TextTraitsRecord theTraits = CRezillaPrefs::GetStyleElement( CRezillaPrefs::prefsType_Curr );
	theWE->ApplyStyleValues( theTraits.size, theTraits.fontNumber);

	// Install the ChangesMessage and let the window listen
	theWE->SetChangesMessage(msg_EditorModifiedItem);
	theWE->AddListener(this);

	// Insert the text
	if (hasText) {
		theHandle = mRezStream->GetDataHandle();
		HLock(theHandle);
		theWE->Insert( (*theHandle) + oldPos , newPos - oldPos, NULL, true);
		HUnlock(theHandle);
		mRezStream->SetMarker(nextPos, streamFrom_Start);
	} 
		
	// Adjust the height of the TextGroupBox
	canReduce = RecalcTextBoxHeight(newPos - oldPos, theWE, isFixed, reqLength, delta);
	
	// If we have a fixed size and it does not exceed the frame, we don't
	// need a scrollbar. 
	if (!canReduce || !isFixed) {
		sScrollPaneInfo.left			= kTmplTextInset;
		sScrollPaneInfo.top				= kTmplTextHeadHeight;
		sScrollPaneInfo.width			= sTgbPaneInfo.width - kTmplTextInset * 2;
		sScrollPaneInfo.height			= boxHeight - kTmplTextHeadHeight - kTmplTextFootHeight;
		sScrollPaneInfo.bindings.left	= true;
		sScrollPaneInfo.paneID			= 0;
		sScrollPaneInfo.superView		= theTGB;

		LScrollerView * theScroller = new LScrollerView(sScrollPaneInfo, theViewInfo, -1, 15, 0, 0, 16, theWE, true);
		ThrowIfNil_(theScroller);

		theWE->PutInside(theScroller);
	} 
	
	if (delta < 0) {
		theTGB->ResizeFrameBy(0, delta, false);
		boxHeight += delta;
	} 
	
	// Advance the counters
	mYCoord += boxHeight + kTmplVertSep;
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//   AddHexDumpField													[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddHexDumpField(OSType inType, LView * inContainer, SInt32 inReqLength)
{
	SInt32		oldPos, newPos, nextPos, reqLength = inReqLength;
	SInt16		hexWidth, hexHeight, txtWidth, txtHeight;
	SInt32		hexLeft, txtLeft;
	Boolean		incrY = true, isFixed = false, hasText, canReduce;
	Handle		theHandle;
	UInt8		theUInt8 = 0;
	UInt16		theUInt16 = 0;
	UInt32		theUInt32 = 0;
	SViewInfo	theViewInfo;
	SDimension16	theFrame;
	SInt16		boxHeight = sTgbPaneInfo.height, delta = 0;
	DualGeometry geo;
	
	// Calculate the limits of the text	to insert
	hasText = CalcTextPositions(inType, oldPos, newPos, nextPos, reqLength, isFixed);
	
	// Install the UI elements
	inContainer->GetFrameSize(theFrame);

	geo.hinst = kTmplTextInset;
	geo.vinst = kTmplTextInset;
	geo.hsep = kTmplHorizSep;
	geo.scrlw = kTmplScrollWidth;
	
	theViewInfo.imageSize.width		= theViewInfo.imageSize.height	= 0 ;
	theViewInfo.scrollPos.h			= theViewInfo.scrollPos.v		= 0;
	theViewInfo.scrollUnit.h		= theViewInfo.scrollUnit.v		= CRezillaApp::sBasics.charHeight;
	theViewInfo.reconcileOverhang	= false;
	
	sTgbPaneInfo.top				= mYCoord;
	sTgbPaneInfo.left				= kTmplTextMargin;
	sTgbPaneInfo.width				= theFrame.width - kTmplTextMargin * 2;
	sTgbPaneInfo.paneID				= mCurrentID;
	sTgbPaneInfo.superView			= inContainer;

	CDualDataView * theTGB = new CDualDataView(this, sTgbPaneInfo, theViewInfo, geo, false);
	ThrowIfNil_(theTGB);
	
	// Make the single vertical scroll bar
	sScrollPaneInfo.left			= sTgbPaneInfo.width - kTmplTextInset - kTmplScrollWidth;
	sScrollPaneInfo.top				= kTmplTextInset;
	sScrollPaneInfo.width			= kTmplScrollWidth;
	sScrollPaneInfo.height			= boxHeight - kTmplTextInset * 2;
	sScrollPaneInfo.bindings.left	= false;
	sScrollPaneInfo.paneID			= 0;
	sScrollPaneInfo.superView		= theTGB;

	CSingleScrollBar * theScroller = new CSingleScrollBar(sScrollPaneInfo, msg_HexScroller, 0, 0, 0, true);
	ThrowIfNil_(theScroller);

	// Make the Waste edit panes: they are, by default, selectable with 
	// wrapping on (so that the image size is recalculated automatically 
	// when the frame size changes). The read only property is set 
	// by InstallSubViews() below.
	theTGB->CalcPanesPositions(hexLeft, hexWidth, hexHeight, txtLeft, txtWidth, txtHeight);
	
	sWastePaneInfo.left				= hexLeft;
	sWastePaneInfo.top				= kTmplTextInset;
	sWastePaneInfo.width			= hexWidth;
	sWastePaneInfo.height			= hexHeight;
	sWastePaneInfo.bindings.left	= false;
	sWastePaneInfo.bindings.right	= false;
	sWastePaneInfo.paneID			= 0;
	sWastePaneInfo.superView		= theTGB;

	CHexDataSubView * theHexWE = new CHexDataSubView(theTGB, sWastePaneInfo, theViewInfo, 0, sEditTraitsID, true);
	ThrowIfNil_(theHexWE);

	sWastePaneInfo.left				= txtLeft;
	sWastePaneInfo.width			= txtWidth;
	
	CTxtDataSubView * theTxtWE = new CTxtDataSubView(theTGB, sWastePaneInfo, theViewInfo, 0, sEditTraitsID, true);
	ThrowIfNil_(theTxtWE);
		
	// Install the subpanes and the scroller in the dual view
	theTGB->InstallSubViews(theHexWE, theTxtWE, theScroller, mOwnerDoc->IsReadOnly() );

	// Adjust to the style specified in the preferences
	TextTraitsRecord theTraits = CRezillaPrefs::GetStyleElement( CRezillaPrefs::prefsType_Curr );
	theTGB->ResizeDataPanes();
	theTGB->UpdatePaneCounts();
	theHexWE->ApplyStyleValues( theTraits.size, theTraits.fontNumber);
	theTxtWE->ApplyStyleValues( theTraits.size, theTraits.fontNumber);

	theScroller->SetMinValue(1);	
	theScroller->SetLinesPerPage( theTGB->GetPaneCount(count_LinesPerPane) - 1);
	
	// Install the ChangesMessage and let the window listen
	theHexWE->SetChangesMessage(msg_EditorModifiedItem);
	theTxtWE->SetChangesMessage(msg_EditorModifiedItem);
	theHexWE->AddListener(this);
	theTxtWE->AddListener(this);

	// Store the template's type in the userCon field
	theTGB->SetUserCon(inType);
			
	if (hasText) {
		theHandle = mRezStream->GetDataHandle();
		HLock(theHandle);
		// ZP bugfix #2, part 1: when creating a resource, Hxxx fields do
		// NOT get filled (even with zeroes), which means there is an error
		// when saving the resource unless the user thinks of filling them
		// all to the required length. So let's fill the stuff with zeroes.
		if (newPos-oldPos>=reqLength)
		{
			theTGB->InstallBackStoreData((*theHandle) + oldPos, newPos - oldPos);
		}
		else // copy the resource data, then fill the remainder with zeroes
		{
			Ptr tempPtr = (Ptr) malloc(reqLength);
			memcpy(tempPtr, (*theHandle) + oldPos, newPos - oldPos);
			memset(tempPtr+newPos - oldPos, 0, reqLength - (newPos - oldPos));
			
			theTGB->InstallBackStoreData(tempPtr, reqLength);
			
			free(tempPtr);
		}
		// end of ZP bugfix 2 part 1
			
		theScroller->SetValue(0);
		theTGB->SetMaxScrollerValue();
		theTGB->InstallContentsFromLine(1);
		HUnlock(theHandle);

		WESetSelection(0, 0, theTGB->GetInMemoryWE());
		mRezStream->SetMarker(newPos, streamFrom_Start);
	}
		
	// Fnnn filler hex strings can be invisible or disabled
	if (inType >> 24 == 'F') {
		if ( ! CRezillaPrefs::GetPrefValue(kPref_templates_displayFillers) ) {
			theTGB->Hide();
			incrY = false;	
		} else if ( ! CRezillaPrefs::GetPrefValue(kPref_templates_enableFillers) ) {
			theHexWE->Disable();
			theTxtWE->Disable();
		} 
	} 
	
	// Advance the counters
	if (incrY) {
		// Adjust the height of the TextGroupBox. 
		// In case of fixed size, we multiply by three (3 chars per byte).
		// Otherwise the text is already installed and the number of lines
		// will be calculated directly.
		reqLength *= 3;
		canReduce = RecalcTextBoxHeight(newPos - oldPos, theHexWE, isFixed, reqLength, delta);
		if (delta < 0) {
			theTGB->ResizeFrameBy(0, delta, false);
			boxHeight += delta;
			if (isFixed) {
				// We have a fixed size and the box has been reduced, so we
				// can hide the scrollbar
				theScroller->Hide();
			} else {
				theScroller->SetLinesPerPage( theTGB->GetPaneCount(count_LinesPerPane) - 1);
			}
		} 
		mYCoord += boxHeight + kTmplVertSep;
	} 
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//   AddPointField													[public]
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
#pragma unused(inType)

	Str255	numStr;
	LEditText * theEditText;
	LStaticText * theStaticText;

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
								msg_EditorModifiedItem, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);

	// Let the window listen to this field
	theEditText->AddListener(this);
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;

	// Y coord
	sRectLabelInfo.left += kTmplRectWidth + kTmplHorizSep;
	theStaticText = new LStaticText(sRectLabelInfo, "\pVert", sEditTraitsID);
	ThrowIfNil_(theStaticText);
	sRectPaneInfo.left += kTmplRectWidth + kTmplHorizSep;
	sRectPaneInfo.paneID = mCurrentID;
	::NumToString( (long) inY, numStr);
	theEditText = new LEditText(sRectPaneInfo, this, numStr, sEditTraitsID, 
								msg_EditorModifiedItem, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);

	// Let the window listen to this field
	theEditText->AddListener(this);
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;

	// Advance the counters
	mYCoord += (kTmplRectHeight * 2) + kTmplVertSep + kTmplVertSep;
}


// ---------------------------------------------------------------------------
//   AddRectField													[public]
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
#pragma unused(inType)

	Str255	numStr;
	LEditText * theEditText;
	LStaticText * theStaticText;

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
								msg_EditorModifiedItem, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);

	// Let the window listen to this field
	theEditText->AddListener(this);
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;

	// Left
	sRectLabelInfo.left += kTmplRectWidth + kTmplHorizSep;
	theStaticText = new LStaticText(sRectLabelInfo, "\pLeft", sEditTraitsID);
	ThrowIfNil_(theStaticText);
	sRectPaneInfo.left += kTmplRectWidth + kTmplHorizSep;
	sRectPaneInfo.paneID = mCurrentID;
	::NumToString( (long) inLeft, numStr);
	theEditText = new LEditText(sRectPaneInfo, this, numStr, sEditTraitsID, 
								msg_EditorModifiedItem, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);

	// Let the window listen to this field
	theEditText->AddListener(this);
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;

	// Bottom
	sRectLabelInfo.left += kTmplRectWidth + kTmplHorizSep;
	if (mRectFormat == rect_TLBR) {
		// 'top, left, bottom, right' format
		theStaticText = new LStaticText(sRectLabelInfo, "\pBottom", sEditTraitsID);
		::NumToString( (long) inBottom, numStr);
	} else {
		// 'top, left, width, height' format
		theStaticText = new LStaticText(sRectLabelInfo, "\pWidth", sEditTraitsID);
		::NumToString( (long) (inRight - inLeft), numStr);
	}
	ThrowIfNil_(theStaticText);
	sRectPaneInfo.left += kTmplRectWidth + kTmplHorizSep;
	sRectPaneInfo.paneID = mCurrentID;
	theEditText = new LEditText(sRectPaneInfo, this, numStr, sEditTraitsID, 
								msg_EditorModifiedItem, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);

	// Let the window listen to this field
	theEditText->AddListener(this);
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;

	// Right
	sRectLabelInfo.left += kTmplRectWidth + kTmplHorizSep;
	if (mRectFormat == rect_TLBR) {
		// 'top, left, bottom, right' format
		theStaticText = new LStaticText(sRectLabelInfo, "\pRight", sEditTraitsID);
		::NumToString( (long) inRight, numStr);
	} else {
		// 'top, left, width, height' format
		theStaticText = new LStaticText(sRectLabelInfo, "\pHeight", sEditTraitsID);
		::NumToString( (long) (inBottom - inTop), numStr);
	}
	ThrowIfNil_(theStaticText);
	sRectPaneInfo.left += kTmplRectWidth + kTmplHorizSep;
	sRectPaneInfo.paneID = mCurrentID;
	theEditText = new LEditText(sRectPaneInfo, this, numStr, sEditTraitsID, 
								msg_EditorModifiedItem, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);

	// Let the window listen to this field
	theEditText->AddListener(this);
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;

	// Advance the counters
	mYCoord += (kTmplRectHeight * 2) + kTmplVertSep + kTmplVertSep;
}


// ---------------------------------------------------------------------------
//   AddListHeaderField											[public]
// ---------------------------------------------------------------------------

PaneIDT
CTmplEditorWindow::AddListHeaderField(Str255 inLabel, 
									  short inCount, 
									  Str255 inCountLabel, 
									  LView * inContainer, 
									  Boolean isFixedCount)
{
	Str255			numStr;
	PaneIDT			theCountPaneID;
	LStaticText *	theStaticText;
	CTmplListButton *	thePushButton;
	
	// This is the label of the list
	sStaticPaneInfo.left		= kTmplLeftMargin;
	sStaticPaneInfo.top			= mYCoord;
	sStaticPaneInfo.width		= kTmplLabelWidth * 2;
	sStaticPaneInfo.superView	= inContainer;

	theStaticText = new LStaticText(sStaticPaneInfo, inLabel, sHeaderTraitsID);
	ThrowIfNil_(theStaticText);

	mYCoord += kTmplEditHeight;

	// This is the label of the count field (BCNT, FCNT, LCNT, LZCT, OCNT, WCNT, ZCNT)
	sStaticPaneInfo.top		= mYCoord;
	sStaticPaneInfo.width	= kTmplLabelWidth;
	theStaticText = new LStaticText(sStaticPaneInfo, inCountLabel, sRightLabelTraitsID);
	ThrowIfNil_(theStaticText);
	
	// This is the value of the counts
	sStaticPaneInfo.left 	+= sStaticPaneInfo.width + kTmplHorizSep;
	sStaticPaneInfo.width	= kTmplCountWidth;
	sStaticPaneInfo.paneID 	= mCurrentID;
	::NumToString( (long) inCount, numStr);
	theStaticText = new LStaticText(sStaticPaneInfo, numStr, sLeftLabelTraitsID);
	ThrowIfNil_(theStaticText);
	if (isFixedCount) {
		// If it is a fixed count list, don't show the count field because the
		// info is already in the label.
		theStaticText->Hide();
	} 	
	sStaticPaneInfo.paneID = 0;
	theCountPaneID = mCurrentID;
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;

	// Create the buttons
	sPushPaneInfo.top		= sStaticPaneInfo.top - 3;
	sPushPaneInfo.left		= sStaticPaneInfo.left + sStaticPaneInfo.width + kTmplHorizSep;
	sPushPaneInfo.paneID	= mCurrentID;
	sPushPaneInfo.superView	= inContainer;
	
	thePushButton = new CTmplListButton(sPushPaneInfo, msg_MinusButton, "\p-");
	ThrowIfNil_(thePushButton);
	// Store the current position in the template stream
	thePushButton->SetUserCon( mTemplateStream->GetMarker());
	// Let the window listen to this button
	thePushButton->AddListener(this);
	if (isFixedCount) {
		thePushButton->Hide();
	} 
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;
	
	sPushPaneInfo.left		+= kTmplCountWidth + kTmplHorizSep;
	sPushPaneInfo.paneID	= mCurrentID;
	thePushButton = new CTmplListButton(sPushPaneInfo, msg_PlusButton, "\p+");
	ThrowIfNil_(thePushButton);
	// The UserCon field will contain a pointer to the first ListItemView. Initialize with nil.
	thePushButton->SetUserCon(nil);
	// Let the window listen to this button
	thePushButton->AddListener(this);
	if (isFixedCount) {
		thePushButton->Hide();
	} 
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;

	// Advance the counters    kTmplVertSep
	mYCoord += sStaticPaneInfo.height + kTmplVertSkip;
	
	return theCountPaneID;
}
 

// ---------------------------------------------------------------------------
//   AddListItemView											[public]
// ---------------------------------------------------------------------------

CTmplListItemView *
CTmplEditorWindow::AddListItemView(CTmplListItemView * inPrevListItemView, 
								   CTmplListItemView * inNextListItemView, 
								   CTmplListButton * inMinusButton,
								   LView * inContainer)
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
	
	CTmplListItemView * theLIV = new CTmplListItemView(sListItemInfo, theViewInfo, this, false);
	ThrowIfNil_(theLIV);

	theLIV->mPrevItem = inPrevListItemView;
	theLIV->mNextItem = inNextListItemView;
	if (inNextListItemView != nil) {
		inNextListItemView->mPrevItem = theLIV;
	} 
	if (inPrevListItemView != nil) {
		inPrevListItemView->mNextItem = theLIV;
	} 

	theLIV->mMinusButton = inMinusButton;
	theLIV->mFirstItemID = mCurrentID;

	return theLIV;
}


// ---------------------------------------------------------------------------
//   AddSeparatorLine											[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddSeparatorLine(LView * inContainer)
{
	SDimension16	theFrame;

	inContainer->GetFrameSize(theFrame);
	sSeparatorPaneInfo.left			= kTmplLeftMargin;
	sSeparatorPaneInfo.top			= mYCoord;
	sSeparatorPaneInfo.width		= theFrame.width - kTmplLeftMargin * 2;
	sSeparatorPaneInfo.superView	= inContainer;

	LSeparatorLine * theSeparator = new LSeparatorLine(sSeparatorPaneInfo);
	ThrowIfNil_(theSeparator);
	
	// Advance the counters
	mYCoord += sSeparatorPaneInfo.height + kTmplVertSep;
}



// ---------------------------------------------------------------------------
//   AddEditPopup													[public]
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
#pragma unused(inType)
	LBevelButton *	theBevelButton;

	sEditPaneInfo.left		= kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep;
	sEditPaneInfo.width		= inWidth;
	sEditPaneInfo.top		= mYCoord - 3;
	sEditPaneInfo.paneID	= mCurrentID;
	sEditPaneInfo.superView	= inContainer;

	CPopupEditField * theEditText = new CPopupEditField(sEditPaneInfo, this, inValue, sEditTraitsID, 
													msg_EditorModifiedItem, msg_PopupEditField, inMaxChars, 
													inAttributes, inKeyFilter, inResourceID);
	ThrowIfNil_(theEditText);

	theBevelButton = theEditText->GetPopup();

	// Incr the pane ID
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;
	theBevelButton->SetPaneID(mCurrentID);
	
	// Mark the item corresponding to the value
	theEditText->AdjustPopupWithValue(inValue);

	// Let the window listen to this edit field and the popup
	theEditText->AddListener(this);

	// Advance the counters
	mYCoord += sEditPaneInfo.height + kTmplVertSep;
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//   AddFlagPopup													[public]
// ---------------------------------------------------------------------------

OSErr
CTmplEditorWindow::AddFlagPopup(ResType inType, Str255 inLabel, UInt32 inValue, LView * inContainer)
{
#pragma unused(inType, inLabel)

	OSErr			error = noErr;
	ResType			theType;
	SInt32			currMark, totalLength;
	Str255			theString;
	
	sPopupPaneInfo.left				= kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep;
	sPopupPaneInfo.top				= mYCoord - 3;
	sPopupPaneInfo.paneID			= mCurrentID;
	sPopupPaneInfo.superView		= inContainer;

	CFlagPopup * theFlagPopup = new CFlagPopup(sPopupPaneInfo, msg_EditorModifiedItem, 0);													 
	ThrowIfNil_(theFlagPopup);

	currMark = mTemplateStream->GetMarker();
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
		theFlagPopup->AppendCase(theString);
	}
	
	// Install initial value
	theFlagPopup->SetFlagValue(inValue);

	// Let the window listen to this menu
	theFlagPopup->AddListener(this);
		
	// Advance the counters. mYCoord has already been increased by the edit field
	mYCoord += sPopupPaneInfo.height + kTmplVertSep;
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;
	
	return error;
}


// ---------------------------------------------------------------------------
//   AddColorPane													[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddColorPane(LView * inContainer, 
								RGBColor * inRGB)
{
	sColorPaneInfo.left			= kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep;
	sColorPaneInfo.top			= mYCoord;
	sColorPaneInfo.superView	= inContainer;
	sColorPaneInfo.paneID		= mCurrentID;
	
	CColorWell * theWell = new CColorWell(sColorPaneInfo, inRGB, msg_EditorModifiedItem);
	ThrowIfNil_(theWell);

	// Let the window listen to this control
	theWell->AddListener(this);

	// Advance the counters
	mYCoord += sColorPaneInfo.height + kTmplVertSep;
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//   AddRSIDField													[public]
// ---------------------------------------------------------------------------
// ZP feature #9, part 3: new features for RSID

void			
CTmplEditorWindow::AddRSIDField(
					Str255 inValue,
					OSType	inType,
					Str255 inLabelString,
					SInt16	inMaxChars,
					SInt16	inWidth,
					TEKeyFilterFunc inKeyFilter,
					LView *	inContainer)
{
#pragma unused(inType)

	ResType				theResType;
	CTmplRSIDField *	theRSIDField;
	SDimension16		theFrame;
	CRezMap*			theRezMap;
	Str255				theString;
	
	inContainer->GetFrameSize(theFrame);

	sEditPaneInfo.left				= kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep;
	sEditPaneInfo.top				= mYCoord - 3;
	sEditPaneInfo.paneID			= mCurrentID;
	sEditPaneInfo.superView			= inContainer;
	sEditPaneInfo.bindings.right	= true;

	if (inWidth > 0) {
		sEditPaneInfo.width = inWidth;
	} else {
		if (inMaxChars > kTmplEditMaxFixedChars) {
			sEditPaneInfo.width = theFrame.width - kTmplLeftMargin * 2 - kTmplLabelWidth - kTmplHorizSep - kTmplHorizSkip;
		} else {
			// Add space for three more chars
			sEditPaneInfo.width = kTmplEditUnitWidth * (((inMaxChars < kTmplEditMinFixedChars)? kTmplEditMinFixedChars : inMaxChars) + 3);
			sEditPaneInfo.bindings.right = false;
		}
	}

	// I don't like to do such things, but I don't have much choice.
	//theRezMap = (dynamic_cast<CTmplEditorDoc*>(this->GetSuperCommander()))->GetRezMapTable()->GetRezMap();
	theRezMap = mOwnerDoc->GetRezMapTable()->GetRezMap();

	if ( UMiscUtils::LookForOSTypeInString(inLabelString, theResType) ) {
		// Got it in the label. No TNAM field to set.
		theRSIDField = new CTmplRSIDField(sEditPaneInfo, this, inValue,
								   sEditTraitsID, msg_EditorModifiedItem,
								   msg_TmplCasePopup, inMaxChars, 0, inKeyFilter,
								   mTemplateStream, mTemplateStream->GetMarker(),
								   theResType, theRezMap);
	} else { 
		// Look for a suitable TNAM field
		if (mPrevTnam) {
			mPrevTnam->GetDescriptor(theString);
			UMiscUtils::PStringToOSType(theString, theResType);
			theRSIDField = new CTmplRSIDField(sEditPaneInfo, this, inValue,
									 sEditTraitsID, msg_EditorModifiedItem,
									 msg_TmplCasePopup, inMaxChars, 0, inKeyFilter,
									 mTemplateStream, mTemplateStream->GetMarker(),
									 theResType, theRezMap);
			// Now set the TNAM field so that the control can listen to it.
			theRSIDField->SetTnamField(mPrevTnam);
			// No need to set mPrevTnam to NULL to tell not to reuse it, it will
			// be done when finished handling this type.
		} else { 
			// No ResType in the label nor any active TNAM field? Then for
			// compatibility's sake act like a DWRD with a dummy popup.
			theRSIDField = new CTmplRSIDField(sEditPaneInfo, this, inValue,
									 sEditTraitsID, msg_EditorModifiedItem,
									 msg_TmplCasePopup, inMaxChars, 0, inKeyFilter,
									 mTemplateStream, mTemplateStream->GetMarker(),
									 '????', theRezMap);
			theRSIDField->SetNoneItem("\pNo Resource Type Specified");
			theRSIDField->SetResType('????'); // This rebuilds the menu
		}
	}
	
	// Let the window listen to this field
	theRSIDField->AddListener(this);
	// Set the paneID: if paneID is 0, clicks in ListItemViews are ignored
	theRSIDField->GetPopup()->SetPaneID(mCurrentID + 1);

	// Advance the counters
	mYCoord += sEditPaneInfo.height + kTmplVertSep;

	// This is the ID of the Edit field, not the ID of the popup
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;
	// Now register the popup's ID
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;
}


