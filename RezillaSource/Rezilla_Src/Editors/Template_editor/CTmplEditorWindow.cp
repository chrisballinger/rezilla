// ===========================================================================
// CTmplEditorWindow.cp					
// 
//                       Created: 2004-06-12 15:08:01
//             Last modification: 2004-06-15 10:20:00
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
#include "RezillaConstants.h"
#include "UMiscUtils.h"
#include "UMessageDialogs.h"
#include "UHexFilters.h"
#include "UCodeTranslator.h"

#include <LScrollBar.h>
#include <LStaticText.h>
#include <LIconPane.h>
#include <LEditText.h>
#include <LTextGroupBox.h>
#include <LScrollerView.h>

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
}


// ---------------------------------------------------------------------------
//		¥ FinishCreateSelf				[protected]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::FinishCreateSelf()
{	
	SDimension16	theFrame;

	mCurrFirstID		= 1;
	mCurrentID			= mCurrFirstID;
	mItemsCount			= 0;
	mIndent				= 0;
	mLeftLabelTraitsID	= Txtr_GenevaTenBoldUlLeft;
	mRightLabelTraitsID	= Txtr_GenevaTenBoldUlRight;
	mEditTraitsID		= Txtr_GenevaTen;
	mXCoord				= kTmplLeftMargin;
	mYCoord				= kTmplVertSep;
	mTemplateStream		= nil;
	mRezStream			= nil;
	
	// The main view containing the labels and editing panes
	mContentsView = dynamic_cast<LView *>(this->FindPaneByID(item_EditorContents));
	ThrowIfNil_( mContentsView );
		
	// The scroller controlling the contents view
	mContentsScroller = dynamic_cast<LActiveScroller *>(this->FindPaneByID(item_EditorScroller));
	ThrowIfNil_( mContentsScroller );
		
	// Install the name of the resource if it has one
	LStaticText * theStaticText = dynamic_cast<LStaticText *>(this->FindPaneByID( item_NameStaticText ));
	ThrowIfNil_( theStaticText );
	Str255 * strPtr = dynamic_cast<CTmplEditorDoc *>(GetSuperCommander())->GetRezObj()->GetName();
	theStaticText->SetDescriptor(*strPtr);	
	
	// Make the window a listener to the prefs object
	CRezillaApp::sPrefs->AddListener(this);

	mContentsView->GetFrameSize(theFrame);

	// Label fields basic values
	mStaticPaneInfo.paneID			= 0;
	mStaticPaneInfo.width			= kTmplLabelWidth;
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
	mEditPaneInfo.width				= theFrame.width - kTmplLeftMargin * 2 - kTmplLabelWidth - kTmplHorizSep;
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

	// Rectangle boxes basic values
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
	mScrollPaneInfo.bindings.left	= true;
	mScrollPaneInfo.bindings.top	= true;
	mScrollPaneInfo.bindings.right	= true;
	mScrollPaneInfo.bindings.bottom	= true;
	mScrollPaneInfo.userCon			= 0;

	// Text group box for text views basic values
	mTgbPaneInfo.paneID				= 0;
	mTgbPaneInfo.width				= theFrame.width - kTmplTextMargin * 2;
	mTgbPaneInfo.height				= kTmplTextHeight;
	mTgbPaneInfo.visible			= true;
	mTgbPaneInfo.enabled			= true;
	mTgbPaneInfo.bindings.left		= true;
	mTgbPaneInfo.bindings.top		= true;
	mTgbPaneInfo.bindings.right		= true;
	mTgbPaneInfo.bindings.bottom	= false;
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
//	¥ ParseTemplate														[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::ParseWithTemplate(Handle inHandle)
{
	Str255		theString;
	ResType		theType;

	// Get a handle to the template resource and create a stream to parse it
	CreateTemplateStream();
	
	// Create a stream to parse the data
	mRezStream = new LHandleStream(inHandle);	

// 	SetMarker(0, streamFrom_Start);

	while (mTemplateStream->GetMarker() < mTemplateStream->GetLength() ) {
		*mTemplateStream >> theString;
		*mTemplateStream >> theType;
		// Create controls according to the type declared in the template
		ParseDataForType(theType, theString);
	}
}


// ---------------------------------------------------------------------------
//	¥ ParseDataForType												[public]
// ---------------------------------------------------------------------------

// TODO:
//   - add error checking: insufficient data, required null bytes
//   - insert in try blocks and catch exceptions

// 		UKeyFilters::SelectTEKeyFilter(keyFilter_AlphaNumeric)
// 		UKeyFilters::SelectTEKeyFilter(keyFilter_Integer)
// 		UKeyFilters::SelectTEKeyFilter(keyFilter_NegativeInteger)
// 		UKeyFilters::SelectTEKeyFilter(keyFilter_PrintingChar)
// 		UKeyFilters::SelectTEKeyFilter(keyFilter_PrintingCharAndCR)
		
// Base integer types for all target OS's and CPU's
// 
// 	UInt8            8-bit unsigned integer 
// 	SInt8            8-bit signed integer
// 	UInt16          16-bit unsigned integer 
// 	SInt16          16-bit signed integer           
// 	UInt32          32-bit unsigned integer 
// 	SInt32          32-bit signed integer   
// 	UInt64          64-bit unsigned integer 
// 	SInt64          64-bit signed integer   

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
	
	// Store the type in the userCon field
	oldYCoord = mYCoord;
	
	switch (inType) {
		case 'ALNG':
		// Long align
		AlignBytes(4);
		break;

		case 'AWRD':
		// Word align
		AlignBytes(2);
		break;

		case 'BBIT':
		// Binary bit (there must be 8 or an even multiple of 8 of these).
		*mRezStream >> theChar;
		// Edit the first bit
		AddStaticField(inLabelString);
		AddBooleanControls( (theChar & (1 << 0)), inType, tmpl_titleOnOff);	
		for (i = 1; i < 8 ; i++) {
			// Consume the next 7 pairs in the template to get the
			// corresponding labels.
			*mTemplateStream >> theString;
			*mTemplateStream >> theOSType;
			AddStaticField(theString);
			AddBooleanControls( (theChar & (1 << i)), inType, tmpl_titleOnOff);	
		}
		break;

		case 'BOOL':
		// Boolean (two bytes: 0x0100 for true, 0x0000 for false)
		*mRezStream >> theBool;
		AddStaticField(inLabelString);
		AddBooleanControls( theBool, inType, tmpl_titleYesNo);		
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
		AddStaticField(inLabelString, tmpl_flushLeft);
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
		// Even-padded C string, or odd-padded C string (padded with nulls)
		
		break;

		case 'ESTR':
		// Pascal string padded to even length (needed for DITL resources)
		*mRezStream >> theString;
		theLength = theString[0];
		if ((theLength % 2 == 0) && (theString[theLength] == 0)) {
			// If the length is even and the last char is a null, it means the string has 
			// been padded. So ignore the last char.
			theString[0] -= 1;
		} 
		AddStaticField(inLabelString);
		AddEditField(theString, inType, rPPob_TmplEditorWindow + mCurrentID, 255, 0, 
					 UKeyFilters::SelectTEKeyFilter(keyFilter_PrintingChar));
		
		break;

		case 'FBYT':
		// Byte fill (with 0)
		mTemplateStream->SetMarker(1, streamFrom_Marker);
		break;

		case 'FLNG':
		// Long fill (with 0)
		mTemplateStream->SetMarker(4, streamFrom_Marker);
		break;

		case 'FWRD':
		// Word fill (with 0)
		mTemplateStream->SetMarker(2, streamFrom_Marker);
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
		AddStaticField(inLabelString, tmpl_flushLeft);
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
		// // repeats recursionTotal times
		
		break;

		case 'LSTE':
		// List end
		
		break;

		case 'LSTR':
		// Long string (length long followed by the characters)
		AddStaticField(inLabelString, tmpl_flushLeft);
		mYCoord += kTmplLabelHeight + kTmplVertSkip;
		AddWasteField(inType);
 		break;

		case 'LSTZ':
		// List Zero. Terminated by a 0 byte (as in 'MENU' resources).
		// // repeats until 0x00 is encountered as first byte of next block
		
		break;

		case 'OCNT':
		// One Count. Terminated by a one-based word count that starts 
		// the sequence (as in 'STR#' resources).
		
		break;

		case 'OCST':
		// Odd-padded C string (padded with nulls)
		
		break;

		case 'OSTR':
		// Pascal string padded to odd length (needed for DITL resources)
		*mRezStream >> theString;
		theLength = theString[0];
		if ((theLength % 2) && (theString[theLength] == 0)) {
			// if the length is odd and the last char is a null, it means the string has 
			// been padded. So ignore the last char.
			theString[0] -= 1;
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
		AddStaticField(inLabelString, tmpl_flushLeft);
		mYCoord += kTmplLabelHeight + kTmplVertSkip;
		AddWasteField(inType);
 		break;

		case 'ZCNT':
		// Zero Count. Terminated by a zero-based word count that starts 
		// the sequence (as in 'DITL' resources).
		
		break;

	  default:
	  // Handle Hnnn, Cnnn, P0nn cases here or unrecognized type
	  // Hnnn A 3-digit hex number; displays nnn bytes in hex format
	  // Cnnn A C string that is nnn hex bytes long (The last byte is always a 0, so the string itself occupies the first nnn-1 bytes.)
	  // P0nn A Pascal string that is nn hex bytes long (The length byte is not included in nn, so the string occupies the entire specified length.)

	  break;
	}

	mContentsView->ResizeImageBy(0, mYCoord - oldYCoord, true);
	mContentsScroller->AdjustScrollBars();

	return error;
}


// ---------------------------------------------------------------------------
//	¥ AddStaticField													[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddStaticField(Str255 inLabel, SInt16 inJustification)
{
	mStaticPaneInfo.left = kTmplLeftMargin + mIndent;
	mStaticPaneInfo.top = mYCoord;
	
	LStaticText * theStaticText = new LStaticText(mStaticPaneInfo, inLabel, 
												  inJustification ? mLeftLabelTraitsID : mRightLabelTraitsID);
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
	mEditPaneInfo.left		= kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep + mIndent;
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
//	¥ AddBooleanControls											[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddBooleanControls(Boolean inValue,
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

	theViewInfo.imageSize.width		= theViewInfo.imageSize.height	= 0 ;
	theViewInfo.scrollPos.h			= theViewInfo.scrollPos.v		= 0;
	theViewInfo.scrollUnit.h		= theViewInfo.scrollUnit.v		= 1;
	theViewInfo.reconcileOverhang	= false;
	
	mTgbPaneInfo.top				= mYCoord;
	mTgbPaneInfo.left				= kTmplTextMargin + mIndent;
	mTgbPaneInfo.bindings.bottom	= false;
	LTextGroupBox * theTGB = new LTextGroupBox(mTgbPaneInfo, theViewInfo, false);
	ThrowIfNil_(theTGB);

	mScrollPaneInfo.left		= kTmplTextInset;
	mScrollPaneInfo.top			= kTmplTextInset;
	mScrollPaneInfo.width		= mTgbPaneInfo.width - kTmplTextInset * 2;
	mScrollPaneInfo.height		= mTgbPaneInfo.height - kTmplTextInset * 2;
	mScrollPaneInfo.paneID		= mCurrentID;
	mScrollPaneInfo.superView	= theTGB;

	LScrollerView * theScroller = new LScrollerView(mScrollPaneInfo, theViewInfo, 0, 15, 0, 15, 16, NULL, true);
	ThrowIfNil_(theScroller);

	mWastePaneInfo.left			= 0;
	mWastePaneInfo.top			= 0;
	mWastePaneInfo.width		= mScrollPaneInfo.width - 15;
	mWastePaneInfo.height		= mScrollPaneInfo.height - 15;
	mWastePaneInfo.paneID		= 0;
	mWastePaneInfo.superView	= theScroller;

	// Make the Waste edit writable, not wrapping, selectable
	CWasteEditView * theWasteEdit = new CWasteEditView(mWastePaneInfo, theViewInfo, 0, mEditTraitsID);
	ThrowIfNil_(theWasteEdit);

	theScroller->InstallView(theWasteEdit);
// 	theScroller->AddListener(this);
	
	// Store the template's type in the userCon field
	theWasteEdit->SetUserCon(inType);
	
	// Insert the text
	switch (inType) {
		case 'CSTR':
			// Is there a NULL byte marking the end of the string?
			oldPos = mRezStream->GetMarker();
			newPos = mRezStream->GetLength();
			while (mRezStream->GetMarker() < mRezStream->GetLength() ) {
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
			newPos = theUInt32;
			break;
		}
		
		case 'WSTR': {
			UInt16		theUInt16;
			// Same as LSTR, but a word rather than a long word
			*mRezStream >> theUInt16;
			oldPos = mRezStream->GetMarker();;
			newPos = theUInt16;
			break;
		}
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
	mOwnerDoc = dynamic_cast<CTmplEditorDoc*>(GetSuperCommander());

	theViewInfo.imageSize.width		= theViewInfo.imageSize.height	= 0 ;
	theViewInfo.scrollPos.h			= theViewInfo.scrollPos.v		= 0;
	theViewInfo.scrollUnit.h		= theViewInfo.scrollUnit.v		= 1;
	theViewInfo.reconcileOverhang	= false;
	
	mTgbPaneInfo.top				= mYCoord;
	mTgbPaneInfo.left				= kTmplTextMargin + mIndent;
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


// // ---------------------------------------------------------------------------
// //	¥ AlignBytes											[public]
// // ---------------------------------------------------------------------------

ExceptionCode
CTmplEditorWindow::AlignBytes(UInt8 inStep)
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
//	¥ ReadValues														[public]
// ---------------------------------------------------------------------------

// LPane::GetUserCon()

Handle
CTmplEditorWindow::ReadValues()
{
	Handle theHandle = nil;
	
	
	return theHandle;
}

