// ===========================================================================
// CTmplEditorWindow.cp					
// 
//                       Created: 2004-06-12 15:08:01
//             Last modification: 2004-06-21 22:18:12
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#include "CTmplEditorWindow.h"
#include "CTmplEditorDoc.h"
#include "CRezEditor.h"
#include "CRezObj.h"
#include "CRezillaApp.h"
#include "CRezillaPrefs.h"
#include "CDualDataView.h"
#include "CHexDataSubView.h"
#include "CSingleScrollBar.h"
#include "CTxtDataSubView.h"
#include "CWasteEditView.h"
#include "UMiscUtils.h"
#include "UMessageDialogs.h"
#include "UHexFilters.h"
#include "UCodeTranslator.h"

#include <LScrollBar.h>
#include <LStaticText.h>
#include <LIconPane.h>
#include <LEditText.h>
#include <LTextGroupBox.h>
#include <LPushButton.h>
#include <LScrollerView.h>
#include <UDrawingState.h>

#include <stdio.h>


// ---------------------------------------------------------------------------
//		¥ CTmplEditorWindow				[public]
// ---------------------------------------------------------------------------

CTmplEditorWindow::CTmplEditorWindow()
{
}


// ---------------------------------------------------------------------------
//		¥ CTmplEditorWindow				[public]
// ---------------------------------------------------------------------------

CTmplEditorWindow::CTmplEditorWindow(
	const SWindowInfo &inWindowInfo )
		: CEditorWindow( inWindowInfo )
{
}


// ---------------------------------------------------------------------------
//		¥ CTmplEditorWindow				[public]
// ---------------------------------------------------------------------------

CTmplEditorWindow::CTmplEditorWindow(
	ResIDT		inWINDid,
	UInt32		inAttributes,
	LCommander	*inSuperCommander )
		: CEditorWindow( inWINDid, inAttributes, inSuperCommander )
{
}


// ---------------------------------------------------------------------------
//		¥ CTmplEditorWindow				[public]
// ---------------------------------------------------------------------------

CTmplEditorWindow::CTmplEditorWindow(
			       LStream *inStream )
		: CEditorWindow( inStream )
{
}


// ---------------------------------------------------------------------------
//		¥ ~CTmplEditorWindow				[public]
// ---------------------------------------------------------------------------

CTmplEditorWindow::~CTmplEditorWindow()
{
	if (mTemplateStream != nil) {
		delete mTemplateStream;
	} 
	if (mRezStream != nil) {
		delete mRezStream;
	} 
	if (mOutStream != nil) {
		delete mOutStream;
	} 

	// Remove the window from the list of listeners to the prefs object
	CRezillaApp::sPrefs->RemoveListener(this);
}


// ---------------------------------------------------------------------------
//		¥ FinishCreateSelf				[protected]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::FinishCreateSelf()
{	
	mCurrentID			= 1;
	mLastID				= 0;
	mItemsCount			= 0;
	mIndent				= 0;
	mStopList			= false;
	mLeftLabelTraitsID	= Txtr_GenevaTenBoldUlLeft;
	mRightLabelTraitsID	= Txtr_GenevaTenBoldUlRight;
	mEditTraitsID		= Txtr_GenevaTen;
	mHeaderTraitsID		= Txtr_GenevaTenBold;
	mYCoord				= 1;
	mTemplateStream		= nil;
	mRezStream			= nil;
	mOutStream			= nil;
	
	// The main view containing the labels and editing panes
	mContentsView = dynamic_cast<LView *>(this->FindPaneByID(item_EditorContents));
	ThrowIfNil_( mContentsView );
		
	// The scroller controlling the contents view
// 	mContentsScroller = dynamic_cast<LActiveScroller *>(this->FindPaneByID(item_EditorScroller));
	mContentsScroller = dynamic_cast<LScrollerView *>(this->FindPaneByID(item_EditorScroller));
	ThrowIfNil_( mContentsScroller );
		
	// Install the name of the resource if it has one
	LStaticText * theStaticText = dynamic_cast<LStaticText *>(this->FindPaneByID( item_NameStaticText ));
	ThrowIfNil_( theStaticText );
	Str255 * strPtr = dynamic_cast<CTmplEditorDoc *>(GetSuperCommander())->GetRezObj()->GetName();
	theStaticText->SetDescriptor(*strPtr);	
	
	// Make the window a listener to the prefs object
	CRezillaApp::sPrefs->AddListener(this);

	// Label fields basic values
	mStaticPaneInfo.paneID			= 0;
	mStaticPaneInfo.height			= kTmplLabelHeight;
	mStaticPaneInfo.visible			= true;
	mStaticPaneInfo.enabled			= true;
	mStaticPaneInfo.bindings.left	= true;
	mStaticPaneInfo.bindings.top	= true;
	mStaticPaneInfo.bindings.right	= false;
	mStaticPaneInfo.bindings.bottom = false;
	mStaticPaneInfo.userCon			= 0;
	mStaticPaneInfo.superView		= mContentsView;
	
	// Edit fields basic values
	mEditPaneInfo.paneID			= 0;
	mEditPaneInfo.height			= kTmplEditHeight;
	mEditPaneInfo.visible			= true;
	mEditPaneInfo.enabled			= true;
	mEditPaneInfo.bindings.left		= true;
	mEditPaneInfo.bindings.top		= true;
	mEditPaneInfo.bindings.right	= true;
	mEditPaneInfo.bindings.bottom	= false;
	mEditPaneInfo.userCon			= 0;
	mEditPaneInfo.superView			= mContentsView;

	// Radio group view basic values
	mRgvPaneInfo.paneID				= 0;
	mRgvPaneInfo.width				= kTmplRgvWidth;
	mRgvPaneInfo.height				= kTmplRgvHeight;
	mRgvPaneInfo.visible			= true;
	mRgvPaneInfo.enabled			= true;
	mRgvPaneInfo.bindings.left		= true;
	mRgvPaneInfo.bindings.top		= true;
	mRgvPaneInfo.bindings.right		= false;
	mRgvPaneInfo.bindings.bottom	= false;
	mRgvPaneInfo.userCon			= 0;
	mRgvPaneInfo.superView			= mContentsView;
	
	// Radio buttons basic values
	mRadioPaneInfo.paneID			= 0;
	mRadioPaneInfo.width			= kTmplRadioWidth;
	mRadioPaneInfo.height			= kTmplRadioHeight;
	mRadioPaneInfo.visible			= true;
	mRadioPaneInfo.enabled			= true;
	mRadioPaneInfo.bindings.left	= true;
	mRadioPaneInfo.bindings.top		= true;
	mRadioPaneInfo.bindings.right	= false;
	mRadioPaneInfo.bindings.bottom	= false;
	mRadioPaneInfo.userCon			= 0;

	// Rectangle labels basic values
	mRectLabelInfo.paneID			= 0;
	mRectLabelInfo.width			= kTmplRectWidth;
	mRectLabelInfo.height			= kTmplRectHeight;
	mRectLabelInfo.visible			= true;
	mRectLabelInfo.enabled			= true;
	mRectLabelInfo.bindings.left	= true;
	mRectLabelInfo.bindings.top		= true;
	mRectLabelInfo.bindings.right	= false;
	mRectLabelInfo.bindings.bottom	= false;
	mRectLabelInfo.userCon			= 0;
	mRectLabelInfo.superView		= mContentsView;

	// Rectangle edit basic values
	mRectPaneInfo.width				= kTmplRectWidth;
	mRectPaneInfo.height			= kTmplEditHeight;
	mRectPaneInfo.visible			= true;
	mRectPaneInfo.enabled			= true;
	mRectPaneInfo.bindings.left		= true;
	mRectPaneInfo.bindings.top		= true;
	mRectPaneInfo.bindings.right	= false;
	mRectPaneInfo.bindings.bottom	= false;
	mRectPaneInfo.userCon			= 0;
	mRectPaneInfo.superView			= mContentsView;
	
	// Active scrollers basic values
	mScrollPaneInfo.paneID			= 0;
	mScrollPaneInfo.visible			= true;
	mScrollPaneInfo.enabled			= true;
	mScrollPaneInfo.bindings.left	= false;
	mScrollPaneInfo.bindings.top	= true;
	mScrollPaneInfo.bindings.right	= true;
	mScrollPaneInfo.bindings.bottom	= true;
	mScrollPaneInfo.userCon			= 0;

	// Text group box for text views basic values
	mTgbPaneInfo.height				= kTmplTextHeight;
	mTgbPaneInfo.visible			= true;
	mTgbPaneInfo.enabled			= true;
	mTgbPaneInfo.bindings.left		= true;
	mTgbPaneInfo.bindings.top		= true;
	mTgbPaneInfo.bindings.right		= true;
	mTgbPaneInfo.bindings.bottom	= true;
	mTgbPaneInfo.userCon			= 0;
	mTgbPaneInfo.superView			= mContentsView;

	// Text views basic values
	mWastePaneInfo.paneID			= 0;
	mWastePaneInfo.visible			= true;
	mWastePaneInfo.enabled			= true;
	mWastePaneInfo.bindings.left	= true;
	mWastePaneInfo.bindings.top		= true;
	mWastePaneInfo.bindings.right	= true;
	mWastePaneInfo.bindings.bottom	= true;
	mWastePaneInfo.userCon			= 0;
	
	// Rectangle edit basic values
	mPushPaneInfo.width				= kTmplPushWidth;
	mPushPaneInfo.height			= kTmplPushHeight;
	mPushPaneInfo.visible			= true;
	mPushPaneInfo.enabled			= true;
	mPushPaneInfo.bindings.left		= false;
	mPushPaneInfo.bindings.top		= false;
	mPushPaneInfo.bindings.right	= false;
	mPushPaneInfo.bindings.bottom	= false;
	mPushPaneInfo.userCon			= 0;
	mPushPaneInfo.superView			= mContentsView;
	
}
	

// ---------------------------------------------------------------------------
//		¥ ListenToMessage				[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{	
	switch (inMessage) {
					
		default:
		dynamic_cast<CTmplEditorDoc *>(GetSuperCommander())->ListenToMessage(inMessage, ioParam);
		break;
				
	}
}


// ---------------------------------------------------------------------------
//	¥ FindCommandStatus
// ---------------------------------------------------------------------------
//	Pass back whether a Command is enabled and/or marked (in a Menu)

void
CTmplEditorWindow::FindCommandStatus(
	CommandT	inCommand,
	Boolean		&outEnabled,
	Boolean		&outUsesMark,
	UInt16		&outMark,
	Str255		outName)
{
	switch (inCommand) {

		case cmd_EditRez:
		case cmd_TmplEditRez:
		case cmd_HexEditRez:
		case cmd_RemoveRez:
		case cmd_DuplicateRez:
			outEnabled = false;
			break;		
		
		default:
			LCommander::FindCommandStatus(inCommand, outEnabled,
									outUsesMark, outMark, outName);
			break;
	}
}


// ---------------------------------------------------------------------------
//	¥ ObeyCommand							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CTmplEditorWindow::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;
	
	switch (inCommand) {

		case cmd_Copy: 
		case cmd_Cut: 
		case cmd_Clear:
		case cmd_Paste:
		break;

		case cmd_ActionCut:
		case cmd_ActionPaste:
		case cmd_ActionClear:
		case cmd_ActionTyping:
			break;

		default:
			cmdHandled = LCommander::ObeyCommand(inCommand, ioParam);
			break;
	}

	return cmdHandled;
}


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
	return false;
}

#pragma mark -

// ---------------------------------------------------------------------------
//	¥ CreateTemplateStream									[private]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::CreateTemplateStream()
{
	Handle theHandle = CRezEditor::GetTemplateHandle( mOwnerDoc->GetRezObj()->GetType() );
	mTemplateStream = new LHandleStream(theHandle);	
}
 

// ---------------------------------------------------------------------------
//	¥ ParseDataWithTemplate												[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::ParseDataWithTemplate(Handle inHandle)
{
	// Get a handle to the template resource and create a stream to parse it
	CreateTemplateStream();
	
	// Create a stream to parse the data
	mRezStream = new LHandleStream(inHandle);	

	// Parse the template stream
	DoParseWithTemplate(0);
}


// ---------------------------------------------------------------------------
//	¥ DoParseWithTemplate													[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::DoParseWithTemplate(SInt32 inRecursionMark)
{
	Str255		theString, countLabel;
	ResType		theType, currType;
	SInt32		oldYCoord;

	mTemplateStream->SetMarker(inRecursionMark, streamFrom_Start);

	while (mTemplateStream->GetMarker() < mTemplateStream->GetLength() ) {
		*mTemplateStream >> theString;
		*mTemplateStream >> theType;
		
		
		if (theType == 'OCNT' || theType == 'ZCNT') {
			LString::CopyPStr(theString, countLabel);
			ParseDataForType(theType, theString);
		} else if (theType == 'LSTB' || theType == 'LSTC' || theType == 'LSTZ') {
			currType = theType;
			oldYCoord = mYCoord;
			AddListHeaderField(theType, theString, mItemsCount, countLabel);
			mContentsView->ResizeImageBy(0, mYCoord - oldYCoord, true);
			ParseList(mTemplateStream->GetMarker(), theType, theString, mItemsCount);
		} else if (theType == 'LSTE') {
			if ( EndOfList(currType) ) {
				break;
			} else {
				mTemplateStream->SetMarker(inRecursionMark, streamFrom_Start);
			}
		} else {
			// Create controls according to the type declared in the template
			ParseDataForType(theType, theString);
		}

	}
}


// ---------------------------------------------------------------------------
//	¥ ParseList													[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::ParseList(SInt32 inStartMark, ResType inType, Str255 inLabel, SInt32 inCount)
{
	mIndent += kTmplListIndent;
	
	switch (inType) {
		case 'LSTB':
		case 'LSTZ':
			DoParseWithTemplate(inStartMark);
		break;
		
		case 'LSTC':
		for (short i = 0 ; i < inCount; i++) {
// 			mTemplateStream->SetMarker(inStartMark, streamFrom_Start);
			DoParseWithTemplate(inStartMark);
		}
		break;
		
	}
	mIndent -= kTmplListIndent;

}


// ---------------------------------------------------------------------------
//	¥ EndOfList													[public]
// ---------------------------------------------------------------------------

Boolean
CTmplEditorWindow::EndOfList(ResType inType)
{
	Boolean result = false;
	UInt8	theChar;

	switch (inType) {
		case 'LSTB':
		if (mRezStream->GetMarker() >= mRezStream->GetLength() ) {
			result = true;
		} 
		break;
		
		case 'LSTC':
		result = true;
		break;
		
		case 'LSTZ':
		*mRezStream >> theChar;
		if (theChar == 0) {
			result = true;
		} else {
			mRezStream->SetMarker(-1, streamFrom_Marker);
		}
		break;
		
	}
	return result;
}


// ---------------------------------------------------------------------------
//	¥ ParseDataForType												[public]
// ---------------------------------------------------------------------------

// TODO:
//   - add error checking: insufficient data, required null bytes
//   - insert in try blocks and catch exceptions

OSErr
CTmplEditorWindow::ParseDataForType(ResType inType, Str255 inLabelString)
{
	OSErr	error = noErr;
	char	theChar;
	char 	charString[256];
	short	theShort;
	Str255	numStr, theString;
	SInt8	theSInt8;
	SInt16	theSInt16;
	SInt32	theSInt32, theLength, oldYCoord;
	UInt16	theUInt16;
	UInt32	theUInt32;
	Boolean	theBool;
	OSType	theOSType;
	UInt8	i;
	
	oldYCoord = mYCoord;
	
	switch (inType) {
		case 'ALNG':
		// Long align
		AlignBytesRead(4);
		break;

		case 'AWRD':
		// Word align
		AlignBytesRead(2);
		break;

		case 'BBIT':
		// Binary bit (there must be 8 or an even multiple of 8 of these).
		*mRezStream >> theChar;
		// Edit the first bit
		AddStaticField(inLabelString);
		AddBooleanField( (theChar & 1), inType, tmpl_titleOnOff);	
		for (i = 1; i < 8 ; i++) {
			// Consume the next 7 pairs in the template to get the
			// corresponding labels.
			*mTemplateStream >> theString;
			*mTemplateStream >> theOSType;
			AddStaticField(theString);
			AddBooleanField( (theChar & (1 << i)), inType, tmpl_titleOnOff);	
		}
		break;

		case 'BOOL':
		// Boolean (two bytes: 0x0100 for true, 0x0000 for false)
		*mRezStream >> theBool;
		AddStaticField(inLabelString);
		AddBooleanField( theBool, inType, tmpl_titleYesNo);		
		// BOOL is two bytes long, so let's consume one more byte
		*mRezStream >> theBool;
		break;

		case 'CHAR':
		// A single character
		*mRezStream >> theChar;
		theString[0] = 1;
		theString[1] = theChar;
		AddStaticField(inLabelString);
		AddEditField(theString, inType, rPPob_TmplEditorWindow + mCurrentID, 1, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_PrintingChar));
		break;

		case 'CSTR':
		// C string. This should be either characters followed by a null or all
		// the chars until the end of the stream if there is no null byte.
		AddStaticField(inLabelString, mLeftLabelTraitsID);
		mYCoord += kTmplLabelHeight + kTmplVertSkip;
		AddWasteField(inType);
 		break;

		case 'DBYT':
		// Decimal byte
		*mRezStream >> theSInt8;
		::NumToString( (long) theSInt8, numStr);
		AddStaticField(inLabelString);
		AddEditField(numStr, inType, rPPob_TmplEditorWindow + mCurrentID, 3, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_Integer));
		break;

		case 'DLNG':
		// Decimal long word
		*mRezStream >> theSInt32;
		::NumToString( (long) theSInt32, numStr);
		AddStaticField(inLabelString);
		AddEditField(numStr, inType, rPPob_TmplEditorWindow + mCurrentID, 5, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_Integer));
		break;

		case 'DWRD':
		// Decimal word
		*mRezStream >> theSInt16;
		::NumToString( (long) theSInt16, numStr);
		AddStaticField(inLabelString);
		AddEditField(numStr, inType, rPPob_TmplEditorWindow + mCurrentID, 10, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_Integer));
		break;

		case 'ECST':
		// Even-padded C string (padded with nulls)
		AddStaticField(inLabelString, mLeftLabelTraitsID);
		mYCoord += kTmplLabelHeight + kTmplVertSkip;
		// Padding is handled there
		AddWasteField(inType);
		break;

		case 'ESTR':
		// Pascal string padded to even length (needed for DITL resources)
		*mRezStream >> theString;
		theLength = theString[0];
		if (theLength % 2 == 0) {
			// if the length is even, the string has been padded. So skip the 
			// next char.
			*mRezStream >> theChar;
		} 
		AddStaticField(inLabelString);
		AddEditField(theString, inType, rPPob_TmplEditorWindow + mCurrentID, 255, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_PrintingChar));
		
		break;

		case 'FBYT':
		// Byte fill (with 0)
		mRezStream->SetMarker(1, streamFrom_Marker);
		break;

		case 'FLNG':
		// Long fill (with 0)
		mRezStream->SetMarker(4, streamFrom_Marker);
		break;

		case 'FWRD':
		// Word fill (with 0)
		mRezStream->SetMarker(2, streamFrom_Marker);
		break;

		case 'HBYT':
		// Hex byte
		*mRezStream >> theChar;
		sprintf(charString, "$%.2x%c", theChar, NULL);
		CopyCStringToPascal(charString, theString);
		AddStaticField(inLabelString);
		AddEditField(theString, inType, rPPob_TmplEditorWindow + mCurrentID, 2, 0, 
					 &UHexFilters::HexadecimalField);
		break;

		case 'HEXD':
		// Hex dump of remaining bytes in resource (this can only be the last type in a resource)
		AddStaticField(inLabelString, mLeftLabelTraitsID);
		mYCoord += kTmplLabelHeight + kTmplVertSkip;
		AddHexDumpField(inType);
		break;

		case 'HLNG':
		// Hex long word
		*mRezStream >> theSInt32;
		sprintf(charString, "$%.8x%c", theSInt32, NULL);
		CopyCStringToPascal(charString, theString);
		AddStaticField(inLabelString);
		AddEditField(theString, inType, rPPob_TmplEditorWindow + mCurrentID, 8, 0, 
					 &UHexFilters::HexadecimalField);
		break;

		case 'HWRD':
		// Hex word
		*mRezStream >> theShort;
		sprintf(charString, "$%.4x%c", theShort, NULL);
		CopyCStringToPascal(charString, theString);
		AddStaticField(inLabelString);
		AddEditField(theString, inType, rPPob_TmplEditorWindow + mCurrentID, 4, 0, 
					 &UHexFilters::HexadecimalField);
		break;

		case 'LSTB':
		// List Begin. Ends at the end of the resource.
		break;

		case 'LSTC':
		// List Count. Terminated by a zero-based word count that starts 
		// the sequence (as in 'DITL' resources).
		break;

		case 'LSTE':
		// List end. Handled in DoParseWithTemplate().
// 		AddHorizontalSeparator(inLabelString);
		break;

		case 'LSTR':
		// Long string (length long followed by the characters)
		AddStaticField(inLabelString, mLeftLabelTraitsID);
		mYCoord += kTmplLabelHeight + kTmplVertSkip;
		AddWasteField(inType);
		break;

		case 'LSTZ':
		// List Zero. Terminated by a 0 byte (as in 'MENU' resources).
		break;
		
		case 'OCNT':
		// One Count. Terminated by a one-based word count that starts 
		// the sequence (as in 'STR#' resources).
		*mRezStream >> theShort;
		mItemsCount = theShort;
// 		::NumToString( (long) mItemsCount, numStr);
// 		AddStaticField(inLabelString);
// 		AddEditField(numStr, inType, rPPob_TmplEditorWindow + mCurrentID, 255, 0, 
// 					 UKeyFilters::SelectTEKeyFilter(keyFilter_PrintingChar));
		break;

		case 'OCST':
		// Odd-padded C string (padded with nulls)
		AddStaticField(inLabelString, mLeftLabelTraitsID);
		mYCoord += kTmplLabelHeight + kTmplVertSkip;
		// Padding is handled there
		AddWasteField(inType);
		break;

		case 'OSTR':
		// Pascal string padded to odd length (needed for DITL resources)
		*mRezStream >> theString;
		theLength = theString[0];
		if (theLength % 2) {
			// if the length is odd, the string has been padded. So skip the 
			// next char.
			*mRezStream >> theChar;
		} 
		AddStaticField(inLabelString);
		AddEditField(theString, inType, rPPob_TmplEditorWindow + mCurrentID, 255, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_PrintingChar));
		break;

		case 'PSTR':
		// Pascal string
		*mRezStream >> theString;
		AddStaticField(inLabelString);
		AddEditField(theString, inType, rPPob_TmplEditorWindow + mCurrentID, 255, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_PrintingChar));
		break;

		case 'RECT': {
			// An 8-byte rectangle
			SInt16 theTop, theLeft, theBottom, theRight;
			*mRezStream >> theTop;
			*mRezStream >> theLeft;
			*mRezStream >> theBottom;
			*mRezStream >> theRight;
			
			mYCoord += kTmplRectVertSkip;
			AddStaticField(inLabelString);
			mYCoord -= kTmplRectVertSkip;
			AddRectField(theTop, theLeft, theBottom, theRight, inType, rPPob_TmplEditorWindow + mCurrentID, 5, 0, 
						 UKeyFilters::SelectTEKeyFilter(keyFilter_Integer));
			break;
		}

		case 'TNAM':
		// Type name (four characters, like OSType and ResType)
		*mRezStream >> theOSType;
		UMiscUtils::OSTypeToPString(theOSType, theString);
		AddStaticField(inLabelString);
		AddEditField(theString, inType, rPPob_TmplEditorWindow + mCurrentID, 4, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_PrintingChar));
		break;

		case 'WSTR':
		// Same as LSTR, but a word rather than a long word
		AddStaticField(inLabelString, mLeftLabelTraitsID);
		mYCoord += kTmplLabelHeight + kTmplVertSkip;
		AddWasteField(inType);
 		break;

		case 'ZCNT':
		// Zero Count. Terminated by a zero-based word count that starts 
		// the sequence (as in 'DITL' resources).
		*mRezStream >> theShort;
		mItemsCount = theShort + 1;
// 		::NumToString( (long) mItemsCount, numStr);
// 		AddStaticField(inLabelString);
// 		AddEditField(numStr, inType, rPPob_TmplEditorWindow + mCurrentID, 255, 0, 
// 					 UKeyFilters::SelectTEKeyFilter(keyFilter_PrintingChar));
		break;

	  default:
	  // Handle Hnnn, Cnnn, P0nn cases here or unrecognized type
	  // Hnnn A 3-digit hex number; displays nnn bytes in hex format
	  // Cnnn A C string that is nnn hex bytes long (The last byte is always a 0, so the string itself occupies the first nnn-1 bytes.)
	  // P0nn A Pascal string that is nn hex bytes long (The length byte is not included in nn, so the string occupies the entire specified length.)

	  break;
	}

	mContentsView->ResizeImageBy(0, mYCoord - oldYCoord, true);
// 	mContentsScroller->AdjustScrollBars();

	return error;
}


#pragma mark -

// ---------------------------------------------------------------------------
//	¥ AddStaticField													[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddStaticField(Str255 inLabel, ResIDT inTextTraitsID)
{
	mStaticPaneInfo.left	= kTmplLeftMargin + mIndent;
	mStaticPaneInfo.top		= mYCoord;
	mStaticPaneInfo.width	= kTmplLabelWidth;
	
	LStaticText * theStaticText = new LStaticText(mStaticPaneInfo, inLabel, inTextTraitsID);
	ThrowIfNil_(theStaticText);
}


// ---------------------------------------------------------------------------
//	¥ AddEditField														[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddEditField(Str255 inValue, 
								OSType inType,
								MessageT inMessage,
								SInt16 inMaxChars, 
								UInt8 inAttributes,
								TEKeyFilterFunc inKeyFilter)
{
	SDimension16	theFrame;
	mContentsView->GetFrameSize(theFrame);

	mEditPaneInfo.left		= kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep + mIndent;
	mEditPaneInfo.width		= theFrame.width - kTmplLeftMargin * 2 - kTmplLabelWidth - kTmplHorizSep - mIndent;
	mEditPaneInfo.top		= mYCoord - 3;
	mEditPaneInfo.paneID	= mCurrentID;

	LEditText * theEditText = new LEditText(mEditPaneInfo, this, inValue, mEditTraitsID, 
											inMessage, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);

	// Store the template's type in the userCon field
	theEditText->SetUserCon(inType);
	
	// Advance the counters
	mYCoord += mEditPaneInfo.height + kTmplVertSep;
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//	¥ AddBooleanField											[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddBooleanField(Boolean inValue,
									  OSType inType,
									  SInt16 inTitleType)
{
	LStdRadioButton * theRadio;
	SViewInfo	theViewInfo;
	theViewInfo.imageSize.width		= theViewInfo.imageSize.height	= 0 ;
	theViewInfo.scrollPos.h			= theViewInfo.scrollPos.v		= 0;
	theViewInfo.scrollUnit.h		= theViewInfo.scrollUnit.v		= 1;
	theViewInfo.reconcileOverhang	= false;
	
	mRgvPaneInfo.left	= kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep + mIndent;
	mRgvPaneInfo.top	= mYCoord - 2;
	mRgvPaneInfo.paneID	= mCurrentID;

	LRadioGroupView * theRGV = new LRadioGroupView(mRgvPaneInfo, theViewInfo);
	ThrowIfNil_(theRGV);

	// Store the template's type in the userCon field
	theRGV->SetUserCon(inType);
	
	mCurrentID++;

	// Create two radiobuttons in this group
	//     "Yes/On" radiobutton
	mRadioPaneInfo.left			= 0;
	mRadioPaneInfo.top			= 0;
	mRadioPaneInfo.paneID		= mCurrentID;
	mRadioPaneInfo.superView	= theRGV;

	theRadio = new LStdRadioButton(mRadioPaneInfo, rPPob_TmplEditorWindow + mCurrentID, 
								   inValue, mLeftLabelTraitsID, (UInt8 *)(inTitleType ? "\pOn":"\pYes"));
	ThrowIfNil_(theRadio);
	
	mCurrentID++;

	//     "No/Off" radiobutton
	mRadioPaneInfo.left += kTmplRadioWidth + kTmplHorizSep;
	mRadioPaneInfo.paneID = mCurrentID;

	theRadio = new LStdRadioButton(mRadioPaneInfo, rPPob_TmplEditorWindow + mCurrentID, 
								   1 - inValue, mLeftLabelTraitsID, (UInt8 *)(inTitleType ? "\pOff":"\pNo"));
	ThrowIfNil_(theRadio);
	
	theRGV->SetCurrentRadioID( inValue ?  mCurrentID - 1 : mCurrentID );
	
	// Advance the counters
	mYCoord += mRgvPaneInfo.height + kTmplVertSep;
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
CTmplEditorWindow::AddWasteField(OSType inType)
{
	SInt32		oldPos, newPos;
	Handle		theHandle;
	char 		theChar;
	SViewInfo	theViewInfo;
	SDimension16	theFrame;
	
	mContentsView->GetFrameSize(theFrame);

	theViewInfo.imageSize.width		= theViewInfo.imageSize.height	= 0 ;
	theViewInfo.scrollPos.h			= theViewInfo.scrollPos.v		= 0;
	theViewInfo.scrollUnit.h		= theViewInfo.scrollUnit.v		= 1;
	theViewInfo.reconcileOverhang	= false;
	
	mTgbPaneInfo.paneID				= 0;
	mTgbPaneInfo.top				= mYCoord;
	mTgbPaneInfo.left				= kTmplTextMargin;
	mTgbPaneInfo.width				= theFrame.width - kTmplTextMargin * 2;
	mTgbPaneInfo.bindings.bottom	= false;
	LTextGroupBox * theTGB = new LTextGroupBox(mTgbPaneInfo, theViewInfo, false);
	ThrowIfNil_(theTGB);

	mScrollPaneInfo.left		= kTmplTextInset;
	mScrollPaneInfo.top			= kTmplTextInset;
	mScrollPaneInfo.width		= mTgbPaneInfo.width - kTmplTextInset * 2;
	mScrollPaneInfo.height		= mTgbPaneInfo.height - kTmplTextInset * 2;
	mScrollPaneInfo.paneID		= 0;
	mScrollPaneInfo.superView	= theTGB;

	LScrollerView * theScroller = new LScrollerView(mScrollPaneInfo, theViewInfo, 0, 15, 0, 15, 16, NULL, true);
	ThrowIfNil_(theScroller);

	mWastePaneInfo.left			= 0;
	mWastePaneInfo.top			= 0;
	mWastePaneInfo.width		= mScrollPaneInfo.width - 15;
	mWastePaneInfo.height		= mScrollPaneInfo.height - 15;
	mWastePaneInfo.paneID		= mCurrentID;
	mWastePaneInfo.superView	= theScroller;

	// Make the Waste edit writable, not wrapping, selectable
	CWasteEditView * theWasteEdit = new CWasteEditView(mWastePaneInfo, theViewInfo, 0, mEditTraitsID);
	ThrowIfNil_(theWasteEdit);

	theScroller->InstallView(theWasteEdit);
	
	// Store the template's type in the userCon field
	theWasteEdit->SetUserCon(inType);
	theLength = mRezStream->GetLength();
	
	// Insert the text
	switch (inType) {
		case 'CSTR':
			// Is there a NULL byte marking the end of the string?
			oldPos = mRezStream->GetMarker();
			newPos = theLength;
			while (mRezStream->GetMarker() < theLength ) {
				*mRezStream >> theChar;
				if (theChar == 0) {
					newPos = mRezStream->GetMarker();
					break;
				} 
			}
		break;

		case 'LSTR': {
			UInt32		theUInt32;
			// Long string (length long followed by the characters)
			*mRezStream >> theUInt32;
			oldPos = mRezStream->GetMarker();;
			newPos = oldPos + theUInt32;
			break;
		}
		
		case 'WSTR': {
			UInt16		theUInt16;
			// Same as LSTR, but a word rather than a long word
			*mRezStream >> theUInt16;
			oldPos = mRezStream->GetMarker();;
			newPos = oldPos + theUInt16;
			break;
		}

		case 'ECST':
		case 'OCST':
			// Is there a NULL byte marking the end of the string?
			oldPos = mRezStream->GetMarker();
			newPos = theLength;
			while (mRezStream->GetMarker() < theLength ) {
				*mRezStream >> theChar;
				if (theChar == 0) {
					newPos = mRezStream->GetMarker();
					// If the total length, including ending NULL, is odd
					// (with ESTR) or even (with OSTR), the string is padded, 
					// so skip one byte
					if ( (newPos < theLength) && ( 
						   ( (newPos - oldPos) % 2 && (inType = 'ECST') ) 
						   ||
						   ( (newPos - oldPos) % 2 == 0 && (inType = 'OCST') ) )) {
					   // String is padded: skip one byte.
					   *mRezStream >> theChar;
					} 
					break;
				} 
			}
		break;

	}

	theHandle = mRezStream->GetDataHandle();
	HLock(theHandle);
	theWasteEdit->Insert( (*theHandle) + oldPos , newPos - oldPos, NULL, true);
	HUnlock(theHandle);
	
	// Advance the counters
	mYCoord += mScrollPaneInfo.height + kTmplVertSep;
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//	¥ AddHexDumpField													[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddHexDumpField(OSType inType)
{
	SInt32		oldPos, newPos;
	Handle		theHandle;
	SViewInfo	theViewInfo;
	SDimension16	theFrame;

	mContentsView->GetFrameSize(theFrame);
	mOwnerDoc = dynamic_cast<CTmplEditorDoc*>(GetSuperCommander());

	theViewInfo.imageSize.width		= theViewInfo.imageSize.height	= 0 ;
	theViewInfo.scrollPos.h			= theViewInfo.scrollPos.v		= 0;
	theViewInfo.scrollUnit.h		= theViewInfo.scrollUnit.v		= 1;
	theViewInfo.reconcileOverhang	= false;
	
	mTgbPaneInfo.top				= mYCoord;
	mTgbPaneInfo.left				= kTmplTextMargin;
	mTgbPaneInfo.width				= theFrame.width - kTmplTextMargin * 2;
	mTgbPaneInfo.bindings.bottom	= true;
	mTgbPaneInfo.paneID				= mCurrentID;
	CDualDataView * theTGB = new CDualDataView(mTgbPaneInfo, theViewInfo, false);
	ThrowIfNil_(theTGB);

	// Make the single vertical scroll bar
	mScrollPaneInfo.left		= mTgbPaneInfo.width - kTmplTextInset - kTmplScrollWidth;
	mScrollPaneInfo.top			= kTmplTextInset;
	mScrollPaneInfo.width		= kTmplScrollWidth;
	mScrollPaneInfo.height		= mTgbPaneInfo.height - kTmplTextInset * 2;
	mScrollPaneInfo.paneID		= 0;
	mScrollPaneInfo.superView	= theTGB;

	CSingleScrollBar * theScroller = new CSingleScrollBar(mScrollPaneInfo, 'HScr', 0, 0, 0, true);
	ThrowIfNil_(theScroller);

	// Make the Waste edit panes (no wrapping, selectable). The read only
	// property is set by InstallSubViews() below.
	mWastePaneInfo.left			= kTmplTextInset;
	mWastePaneInfo.top			= kTmplTextInset;
	mWastePaneInfo.width		= kTmplHexPaneWidth;
	mWastePaneInfo.height		= mScrollPaneInfo.height;
	mWastePaneInfo.paneID		= 0;
	mWastePaneInfo.superView	= theTGB;

	CHexDataSubView * theHexWE = new CHexDataSubView(mWastePaneInfo, theViewInfo, 0, mEditTraitsID);
	ThrowIfNil_(theHexWE);

	mWastePaneInfo.left			= kTmplTxtPaneLeft;
	mWastePaneInfo.width		= kTmplTxtPaneWidth;
	
	CTxtDataSubView * theTxtWE = new CTxtDataSubView(mWastePaneInfo, theViewInfo, 0, mEditTraitsID);
	ThrowIfNil_(theTxtWE);
	
	// Install the subpanes and the scroller in the dual view
	theTGB->InstallSubViews(theHexWE, theTxtWE, theScroller, mOwnerDoc->IsReadOnly() );

	// Adjust to the style specified in the preferences
	TextTraitsRecord theTraits = CRezillaApp::sPrefs->GetStyleElement( CRezillaPrefs::prefsType_Curr );
	theTGB->ResizeDataPanes();
	theTGB->UpdatePaneCounts();
	theHexWE->ApplyStyleValues( theTraits.size, theTraits.fontNumber);
	theTxtWE->ApplyStyleValues( theTraits.size, theTraits.fontNumber);
	
	// Store the template's type in the userCon field
	theTGB->SetUserCon(inType);
	
	// Insert the text
	oldPos = mRezStream->GetMarker();
	newPos = mRezStream->GetLength();
	
	theHandle = mRezStream->GetDataHandle();
	HLock(theHandle);
	theTGB->InstallBackStoreData((*theHandle) + oldPos , newPos - oldPos);
	theTGB->SetMaxScrollerValue();
	theTGB->InstallContentsFromLine(1);
	HUnlock(theHandle);

	WESetSelection(0, 0, theTGB->GetInMemoryWasteRef());
	
	// Advance the counters
	mYCoord += mScrollPaneInfo.height + kTmplVertSep;
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//	¥ AddRectField													[public]
// ---------------------------------------------------------------------------
// Rectangle text group box basic values

void
CTmplEditorWindow::AddRectField(SInt16 inTop, 
								SInt16 inLeft, 
								SInt16 inBottom, 
								SInt16 inRight, 
								OSType inType,
								MessageT inMessage,
								SInt16 inMaxChars, 
								UInt8 inAttributes,
								TEKeyFilterFunc inKeyFilter)
{
	Str255	numStr;
	LEditText * theEditText;
	LStaticText * theStaticText;
	SViewInfo	theViewInfo;
	theViewInfo.imageSize.width		= theViewInfo.imageSize.height	= 0 ;
	theViewInfo.scrollPos.h			= theViewInfo.scrollPos.v		= 0;
	theViewInfo.scrollUnit.h		= theViewInfo.scrollUnit.v		= 1;
	theViewInfo.reconcileOverhang	= false;

	mRectLabelInfo.top	= mYCoord;
	mRectPaneInfo.top	= mYCoord + kTmplRectHeight;
	mRectLabelInfo.left = kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep + mIndent;
	mRectPaneInfo.left	= mRectLabelInfo.left;

	// Top
	theStaticText = new LStaticText(mRectLabelInfo, "\pTop", mEditTraitsID);
	ThrowIfNil_(theStaticText);
	mRectPaneInfo.paneID = mCurrentID;
	::NumToString( (long) inTop, numStr);
	theEditText = new LEditText(mRectPaneInfo, this, numStr, mEditTraitsID, 
											inMessage, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);
	theEditText->SetUserCon(inType);
	mCurrentID++;

	// Left
	mRectLabelInfo.left += kTmplRectWidth + kTmplHorizSep + mIndent;
	theStaticText = new LStaticText(mRectLabelInfo, "\pLeft", mEditTraitsID);
	ThrowIfNil_(theStaticText);
	mRectPaneInfo.left += kTmplRectWidth + kTmplHorizSep + mIndent;
	mRectPaneInfo.paneID = mCurrentID;
	::NumToString( (long) inLeft, numStr);
	theEditText = new LEditText(mRectPaneInfo, this, numStr, mEditTraitsID, 
											inMessage, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);
	theEditText->SetUserCon(inType);
	mCurrentID++;

	// Bottom
	mRectLabelInfo.left += kTmplRectWidth + kTmplHorizSep + mIndent;
	theStaticText = new LStaticText(mRectLabelInfo, "\pBottom", mEditTraitsID);
	ThrowIfNil_(theStaticText);
	mRectPaneInfo.left += kTmplRectWidth + kTmplHorizSep + mIndent;
	mRectPaneInfo.paneID = mCurrentID;
	::NumToString( (long) inBottom, numStr);
	theEditText = new LEditText(mRectPaneInfo, this, numStr, mEditTraitsID, 
											inMessage, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);
	theEditText->SetUserCon(inType);
	mCurrentID++;

	// Right
	mRectLabelInfo.left += kTmplRectWidth + kTmplHorizSep + mIndent;
	theStaticText = new LStaticText(mRectLabelInfo, "\pRight", mEditTraitsID);
	ThrowIfNil_(theStaticText);
	mRectPaneInfo.left += kTmplRectWidth + kTmplHorizSep + mIndent;
	mRectPaneInfo.paneID = mCurrentID;
	::NumToString( (long) inRight, numStr);
	theEditText = new LEditText(mRectPaneInfo, this, numStr, mEditTraitsID, 
											inMessage, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);
	theEditText->SetUserCon(inType);
	mCurrentID++;

	// Advance the counters
	mYCoord += (kTmplRectHeight * 2) + kTmplVertSep + kTmplVertSep;
}


// ---------------------------------------------------------------------------
//	¥ AddListHeaderField													[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddListHeaderField(OSType inType, Str255 inLabel, short inCount, Str255 inCountLabel)
{
	Str255			numStr;
	LStaticText *	theStaticText;
	LPushButton *	thePushButton;
	
	// This is the label of the list (usually "*****")
	mStaticPaneInfo.left	= kTmplLeftMargin + mIndent;
	mStaticPaneInfo.top		= mYCoord;
	mStaticPaneInfo.width	= kTmplLabelWidth;
	
	theStaticText = new LStaticText(mStaticPaneInfo, inLabel, mHeaderTraitsID);
	ThrowIfNil_(theStaticText);

	if (inType == 'LSTC') {
		mYCoord += kTmplEditHeight;
		// This is the label of the OCNT or ZCNT count
		mStaticPaneInfo.left 	= 0;
		mStaticPaneInfo.top		= mYCoord;
		mStaticPaneInfo.width	= kTmplLabelWidth;
		theStaticText = new LStaticText(mStaticPaneInfo, inCountLabel, mRightLabelTraitsID);
		ThrowIfNil_(theStaticText);
		
		// This is the value of the OCNT or ZCNT count
		mStaticPaneInfo.left 	+= mStaticPaneInfo.width + kTmplHorizSep;
		mStaticPaneInfo.width	= kTmplCountWidth;
		mStaticPaneInfo.paneID 	= mCurrentID;
		::NumToString( (long) inCount, numStr);
		theStaticText = new LStaticText(mStaticPaneInfo, numStr, mHeaderTraitsID);
		ThrowIfNil_(theStaticText);
		
		mStaticPaneInfo.paneID = 0;
		mCurrentID++;
	}
	
	mPushPaneInfo.top		= mStaticPaneInfo.top - 3;
	mPushPaneInfo.left		= mStaticPaneInfo.left + mStaticPaneInfo.width + kTmplHorizSep;
	mPushPaneInfo.paneID	= mCurrentID;
	thePushButton = new LPushButton(mPushPaneInfo, 'Mins', "\p-");
	ThrowIfNil_(thePushButton);
	// Store the current position in the template stream
	thePushButton->SetUserCon( mTemplateStream->GetMarker() );
	mCurrentID++;
	
	mPushPaneInfo.left		+= kTmplCountWidth + kTmplHorizSep;
	mPushPaneInfo.paneID	= mCurrentID;
	thePushButton = new LPushButton(mPushPaneInfo, 'Plus', "\p+");
	ThrowIfNil_(thePushButton);
	// Store the current position in the template stream
	thePushButton->SetUserCon( mTemplateStream->GetMarker() );
	mCurrentID++;

	// Advance the counters
	mYCoord += mStaticPaneInfo.height + kTmplVertSep;
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
//	¥ RetrieveDataWithTemplate								[public]
// ---------------------------------------------------------------------------

Handle
CTmplEditorWindow::RetrieveDataWithTemplate()
{
	mOutStream = new LHandleStream();
	mLastID = mCurrentID;
	mCurrentID = 1;

	// Parse the template stream
	DoRetrieveWithTemplate(0);
	
	return mOutStream->GetDataHandle();
}


// // 	//	Dissociate the data Handle from a HandleStream.
// // 	//
// // 	//	Creates a new, empty data Handle and passes back the existing Handle.
// // 	//	Caller assumes ownership of the Handle.
// // 
// // 	Handle
// // 	LHandleStream::DetachDataHandle()


// ---------------------------------------------------------------------------
//	¥ DoRetrieveWithTemplate													[public]
// ---------------------------------------------------------------------------
// // // SInt32
// // // LPane::GetUserCon() const
// // // GetPaneID()

void
CTmplEditorWindow::DoRetrieveWithTemplate(SInt32 inRecursionMark)
{
	Str255		theString;
	ResType		theType, currType;
	
	mTemplateStream->SetMarker(inRecursionMark, streamFrom_Start);

	while (mTemplateStream->GetMarker() < mTemplateStream->GetLength() ) {
		*mTemplateStream >> theString;
		*mTemplateStream >> theType;
		
		if (theType == 'OCNT' || theType == 'ZCNT') {
			RetrieveDataForType(theType);
		} else if (theType == 'LSTB' || theType == 'LSTC' || theType == 'LSTZ') {
			currType = theType;
			RetrieveList(mTemplateStream->GetMarker(), theType, mItemsCount);
		} else if (theType == 'LSTE') {
			if ( EndOfList(currType) ) {
				break;
			} else {
				mTemplateStream->SetMarker(inRecursionMark, streamFrom_Start);
			}
		} else {
			// Create controls according to the type declared in the template
			RetrieveDataForType(theType);
		}
	}
}


// ---------------------------------------------------------------------------
//	¥ RetrieveList													[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::RetrieveList(SInt32 inStartMark, ResType inType, SInt32 inCount)
{
	switch (inType) {
		case 'LSTB':
		case 'LSTZ':
			DoRetrieveWithTemplate(inStartMark);
		break;
		
		case 'LSTC':
		for (short i = 0 ; i < inCount; i++) {
// 			mTemplateStream->SetMarker(inStartMark, streamFrom_Start);
			DoRetrieveWithTemplate(inStartMark);
		}
		break;
		
	}
}


// ---------------------------------------------------------------------------
//	¥ RetrieveDataForType												[public]
// ---------------------------------------------------------------------------


OSErr
CTmplEditorWindow::RetrieveDataForType(ResType inType)
{
	OSErr	error = noErr;
	char	theChar;
	char 	charString[256];
	short	theShort;
	long	theLong;
	Str255	numStr, theString;
	SInt8	theSInt8;
	SInt16	theSInt16;
	SInt32	theSInt32, theLength, oldYCoord;
	UInt16	theUInt16;
	UInt32	theUInt32;
	Boolean	theBool;
	OSType	theOSType;
	UInt8	i;
	Ptr		p;
	
	PaneIDT theCurrentRadioID;
	Handle theHandle;
	StHandleLocker locker(nil);

	LRadioGroupView * theRGV;
	LEditText * theEditText;
	CWasteEditView * theWasteEdit;
	
	switch (inType) {
		case 'ALNG':
		// Long align
		AlignBytesWrite(4);
		break;

		case 'AWRD':
		// Word align
		AlignBytesWrite(2);
		break;

		case 'BBIT':
		// Binary bit (there must be 8 or an even multiple of 8 of these).

		theRGV = dynamic_cast<LRadioGroupView *>(this->FindPaneByID(mCurrentID));
		theCurrentRadioID = theRGV->GetCurrentRadioID();
		*mOutStream << (UInt8) ( (theCurrentRadioID - mCurrentID) % 2);
		mCurrentID += 3;
		
		// Consume similarly the next 7 controls in the template
		for (i = 1; i < 8 ; i++) {
			*mTemplateStream >> theString;
			*mTemplateStream >> theOSType;
			
			theRGV = dynamic_cast<LRadioGroupView *>(this->FindPaneByID(mCurrentID));
			theCurrentRadioID = theRGV->GetCurrentRadioID();
			*mOutStream << (UInt8) ( (theCurrentRadioID - mCurrentID) % 2);
			mCurrentID += 3;
		}
		break;

		case 'BOOL':
		// Boolean (two bytes: 0x0100 for true, 0x0000 for false)
		theRGV = dynamic_cast<LRadioGroupView *>(this->FindPaneByID(mCurrentID));
		theCurrentRadioID = theRGV->GetCurrentRadioID();
		if ( (theCurrentRadioID - mCurrentID) % 2 ) {
			*mOutStream << (UInt16) 0x0100;
		} else {
			*mOutStream << (UInt16) 0x0000;
		}
		mCurrentID += 3;
		break;

		case 'CHAR':
		// A single character
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(theString);		
		*mOutStream << (char) (theString + 1);
		mCurrentID++;
		break;

		case 'CSTR':
		// C string
		theWasteEdit = dynamic_cast<CWasteEditView *>(this->FindPaneByID(mCurrentID));
		theHandle = theWasteEdit->GetTextHandle();
		theLength = theWasteEdit->GetTextLength();
		locker.Adopt(theHandle);
		p = *theHandle;
		
		for (theSInt32 = 0; theSInt32 < theLength; theSInt32++) {
			*mOutStream << (char) *p;
			p++;
		}
		// End with a NULL byte
		*mOutStream << (UInt8) 0x00;
		mCurrentID++;
		break;

		case 'DBYT':
		// Decimal byte
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(numStr);	
		::StringToNum( numStr, &theLong);
		*mOutStream << (SInt8) theLong;
		mCurrentID++;
		break;

		case 'DLNG':
		// Decimal long word
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(numStr);	
		::StringToNum( numStr, &theLong);
		*mOutStream << (SInt32) theLong;
		mCurrentID++;
		break;

		case 'DWRD':
		// Decimal word
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(numStr);	
		::StringToNum( numStr, &theLong);
		*mOutStream << (SInt16) theLong;
		mCurrentID++;
		break;

// 		case 'ECST':
// 		// Even-padded C string, or odd-padded C string (padded with nulls)
// 		
// 		break;
// 
		case 'ESTR':
		// Pascal string padded to even length (needed for DITL resources)
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(theString);	
		*mOutStream << theString;
		if (theString[0] % 2 == 0) {
			// if the length is even, padd the string with a NULL byte.
			*mOutStream << (UInt8) 0x00;
		} 
		mCurrentID++;
		break;

		case 'FBYT':
		// Byte fill (with 0)
		*mOutStream << (SInt8) 0;
		break;

		case 'FLNG':
		// Long fill (with 0)
		*mOutStream << (SInt32) 0;
		break;

		case 'FWRD':
		// Word fill (with 0)
		*mOutStream << (SInt16) 0;
		break;

		case 'HBYT':
		// Hex byte
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(numStr);	
		CopyPascalStringToC(theString, charString);
		sscanf(charString, "$%.2x", theChar);
		*mOutStream << theChar;
		mCurrentID++;
		break;

		case 'HEXD':
		// Hex dump of remaining bytes in resource (this can only be the last type in a resource)
		CDualDataView * theTGB = dynamic_cast<CDualDataView *>(this->FindPaneByID(mCurrentID));
		WEReference theWE = theTGB->GetInMemoryWasteRef();
		theHandle = static_cast<Handle>(::WEGetText(theWE));
		theLength = ::WEGetTextLength(theWE);
		
		locker.Adopt(theHandle);
		p = *theHandle;
		for (theSInt32 = 0; theSInt32 < theLength; theSInt32++) {
			*mOutStream << (char) *p;
			p++;
		}
		mCurrentID++;
		break;

		case 'HLNG':
		// Hex long word
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(numStr);	
		CopyPascalStringToC(theString, charString);
		sscanf(charString, "$%.8x", theUInt32);
		*mOutStream << theChar;
		mCurrentID++;
		break;

		case 'HWRD':
		// Hex word
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(numStr);	
		CopyPascalStringToC(theString, charString);
		sscanf(charString, "$%.4x", theUInt16);
		*mOutStream << theChar;
		mCurrentID++;
		break;

		case 'LSTB':
		// List Begin. Ends at the end of the resource.
		break;

		case 'LSTC':
		// List Count. Terminated by a zero-based word count that starts 
		// the sequence (as in 'DITL' resources).
		break;

		case 'LSTE':
		// List end. Handled in DoParseWithTemplate().
		break;

		case 'LSTR':
		// Long string (length long followed by the characters)
		theWasteEdit = dynamic_cast<CWasteEditView *>(this->FindPaneByID(mCurrentID));
		theHandle = theWasteEdit->GetTextHandle();
		theLength = theWasteEdit->GetTextLength();
		*mOutStream << (UInt32) theLength;
		locker.Adopt(theHandle);
		p = *theHandle;
		
		for (theSInt32 = 0; theSInt32 < theLength; theSInt32++) {
			*mOutStream << (char) *p;
			p++;
		}
		mCurrentID++;
		break;

		case 'LSTZ':
		// List Zero. Terminated by a 0 byte (as in 'MENU' resources).
		break;
		
// 		case 'OCNT':
// 		// One Count. Terminated by a one-based word count that starts 
// 		// the sequence (as in 'STR#' resources).
// 		*mOutStream << theShort;
// 		mItemsCount = theShort;
// // 		::NumToString( (long) mItemsCount, numStr);
// // 		AddStaticField(inLabelString);
// // 		AddEditField(numStr, inType, rPPob_TmplEditorWindow + mCurrentID, 255, 0, 
// // 					 UKeyFilters::SelectTEKeyFilter(keyFilter_PrintingChar));
// 		break;
// 
// 		case 'OCST':
// 		// Odd-padded C string (padded with nulls)
// 		
// 		break;
// 
		case 'OSTR':
		// Pascal string padded to odd length (needed for DITL resources)
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(theString);	
		*mOutStream << theString;
		if (theString[0] % 2) {
			// if the length is odd, padd the string with a NULL byte.
			*mOutStream << (UInt8) 0x00;
		} 
		mCurrentID++;
		break;

		case 'PSTR':
		// Pascal string
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(theString);	
		*mOutStream << theString;
		mCurrentID++;
		break;

		case 'RECT':
		// An 8-byte rectangle
		for (i = 0; i < 4; i++) {
			theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
			theEditText->GetDescriptor(numStr);	
			::StringToNum( numStr, &theLong);
			*mOutStream << (SInt16) theLong;
			mCurrentID++;
		}
		break;

		case 'TNAM':
		// Type name (four characters, like OSType and ResType)
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID));
		theEditText->GetDescriptor(theString);	
		UMiscUtils::PStringToOSType(theString, theOSType);
		*mOutStream << theOSType;
		mCurrentID++;
		break;

		case 'WSTR':
		// Same as LSTR, but a word rather than a long word
		theWasteEdit = dynamic_cast<CWasteEditView *>(this->FindPaneByID(mCurrentID));
		theHandle = theWasteEdit->GetTextHandle();
		theLength = theWasteEdit->GetTextLength();
		*mOutStream << (UInt16) theLength;
		locker.Adopt(theHandle);
		p = *theHandle;
		
		for (theSInt32 = 0; theSInt32 < theLength; theSInt32++) {
			*mOutStream << (char) *p;
			p++;
		}
		mCurrentID++;
		break;

// 		case 'ZCNT':
// 		// Zero Count. Terminated by a zero-based word count that starts 
// 		// the sequence (as in 'DITL' resources).
// 		*mOutStream << theShort;
// 		mItemsCount = theShort + 1;
// // 		::NumToString( (long) mItemsCount, numStr);
// // 		AddStaticField(inLabelString);
// // 		AddEditField(numStr, inType, rPPob_TmplEditorWindow + mCurrentID, 255, 0, 
// // 					 UKeyFilters::SelectTEKeyFilter(keyFilter_PrintingChar));
// 		break;
// 
	  default:
	  // Handle Hnnn, Cnnn, P0nn cases here or unrecognized type
	  // Hnnn A 3-digit hex number; displays nnn bytes in hex format
	  // Cnnn A C string that is nnn hex bytes long (The last byte is always a 0, so the string itself occupies the first nnn-1 bytes.)
	  // P0nn A Pascal string that is nn hex bytes long (The length byte is not included in nn, so the string occupies the entire specified length.)

	  break;
	}

	return error;
}




