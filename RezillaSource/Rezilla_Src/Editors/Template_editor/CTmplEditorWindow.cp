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
#include "CWasteEditView.h"
#include "RezillaConstants.h"
#include "UMiscUtils.h"
#include "UMessageDialogs.h"
#include "UHexFilters.h"

#include <LScrollBar.h>
#include <LStaticText.h>
#include <LIconPane.h>
#include <LEditText.h>
#include <LUndoer.h>
#include <UExtractFromAEDesc.h>
#include <UAppleEventsMgr.h>
#include <UCursor.h>

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
	mCurrFirstID		= 1;
	mCurrentID			= mCurrFirstID;
	mItemsCount			= 0;
	mIndent				= 0;
	mLabelTraitsID		= Txtr_GenevaTenBoldUlRight;
	mEditTraitsID		= Txtr_GenevaTen;
	mXCoord				= kTmplLeftMargin;
	mYCoord				= kTmplVertSkip;
	mTemplateStream		= nil;
	mRezStream			= nil;
	
	// The main view containing the labels and editing panes
	mContentsView = dynamic_cast<LView *>(this->FindPaneByID(item_TmplEditContents));
	ThrowIfNil_( mContentsView );
		
	// The scroller controlling the contents view
	mContentsScroller = dynamic_cast<LActiveScroller *>(this->FindPaneByID(item_TmplEditScroller));
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
	mEditPaneInfo.paneID			= mCurrentID;
	mEditPaneInfo.width				= kTmplEditWidth;
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

// 	// Attach an LUndoer to each of the subpanes
// 	mHexDataWE->AddAttachment( new LUndoer );
// 	mTxtDataWE->AddAttachment( new LUndoer );
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
// - CSTR should not use an editfield limited to 255 chars
// - add more error checking: insufficient data, required null bytes
// - insert in try block and catch exceptions

// 	
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
	char *	theCString;
	short	theShort;
	Str255	numStr, theString;
	SInt8	theSInt8;
	SInt16	theSInt16;
	SInt32	theSInt32, theRest, theLength, oldYCoord;
	UInt16	theUInt16;
	UInt32	theUInt32;
	Boolean	theBool;
	OSType	theOSType;
	
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
		// 
		*mRezStream >> theChar;
		
		AddStaticField(inLabelString);
// 		AddBooleanControls();
		
		break;

		case 'BOOL':
		// Boolean (two bytes: 0x0100 for true, 0x0000 for false)
		*mRezStream >> theBool;
		AddStaticField(inLabelString);
		AddBooleanControls( (Boolean) theSInt16, inType, tmpl_titleYesNo);		
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
		// C string (characters followed by a null)
		*mRezStream >> theCString;
		CopyCStringToPascal(theCString, theString);
		AddStaticField(inLabelString);
		AddEditField(theString, inType, rPPob_TmplEditorWindow + mCurrentID, 255, 0, NULL);
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
			// if the length is even and the last char is a null, it means the string has 
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
		// // one to 4,294,967,296 bytes
		
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
		AddStaticField(inLabelString);
		AddRectField(theTop, theLeft, theBottom, theRight, inType, rPPob_TmplEditorWindow + mCurrentID, 255, 0, 
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
		// // one to 65,536 bytes
		
		break;

		case 'ZCNT':
		// Zero Count. Terminated by a zero-based word count that starts 
		// the sequence (as in 'DITL' resources).
		
		break;

	  default:
	  // Handle Hnnn, Cnnn, P0nn cases here or unrecognized type
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
CTmplEditorWindow::AddStaticField(Str255 inLabel)
{
	mStaticPaneInfo.left = kTmplLeftMargin + mIndent;
	mStaticPaneInfo.top = mYCoord;
	
	LStaticText * theStaticText = new LStaticText(mStaticPaneInfo, inLabel, mLabelTraitsID);
	ThrowIfNil_(theStaticText);
}


// ---------------------------------------------------------------------------
//	¥ AddEditField														[public]
// ---------------------------------------------------------------------------

// 		enum {
// 	editAttr_Box			= 0x80,
// 	editAttr_WordWrap		= 0x40,
// 	editAttr_AutoScroll		= 0x20,
// 	editAttr_TextBuffer		= 0x10,
// 	editAttr_OutlineHilite	= 0x08,
// 	editAttr_InlineInput	= 0x04,
// 	editAttr_TextServices	= 0x02
// };
// 		attributes |= editAttr_WordWrap;

void
CTmplEditorWindow::AddEditField(Str255 inValue, 
								OSType inType,
								MessageT inMessage,
								SInt16 inMaxChars, 
								UInt8 inAttributes,
								TEKeyFilterFunc inKeyFilter)
{
	mEditPaneInfo.left = kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep + mIndent;
	mEditPaneInfo.top = mYCoord - 2;
	mEditPaneInfo.paneID = mCurrentID;

	LEditText * theEditText = new LEditText(mEditPaneInfo, this, inValue, mEditTraitsID, 
											inMessage, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);

	// Store the template's type in the userCon field
	theEditText->SetUserCon(inType);
	
// 	SetLatentSub(theEditText);
// 	SuperActivate();

	// Advance the counters
	mYCoord += mEditPaneInfo.height + kTmplVertSkip;
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//	¥ AddBooleanControls											[public]
// ---------------------------------------------------------------------------

// 		enum {
// 	editAttr_Box			= 0x80,
// 	editAttr_WordWrap		= 0x40,
// 	editAttr_AutoScroll		= 0x20,
// 	editAttr_TextBuffer		= 0x10,
// 	editAttr_OutlineHilite	= 0x08,
// 	editAttr_InlineInput	= 0x04,
// 	editAttr_TextServices	= 0x02
// };
// 		attributes |= editAttr_WordWrap;
// typedef struct	SViewInfo {
// 	SDimension32	imageSize;
// 	SPoint32		scrollPos;
// 	SPoint32		scrollUnit;
// 	SInt16			reconcileOverhang;
// } SViewInfo;

// theBool, inType, rPPob_TmplEditorWindow + mCurrentID, 0, 
// 					 UKeyFilters::SelectTEKeyFilter(keyFilter_PrintingChar)
void
CTmplEditorWindow::AddBooleanControls(Boolean inValue,
									  OSType inType,
									  SInt16 inTitleType)
{
	LStdRadioButton * theRadio;
	SViewInfo	theViewInfo;
	theViewInfo.imageSize.width = theViewInfo.imageSize.height = 0 ;
	theViewInfo.scrollPos.h = theViewInfo.scrollPos.v = 0;
	theViewInfo.scrollUnit.h = theViewInfo.scrollUnit.v = 1;
	theViewInfo.reconcileOverhang = false;
	
	mRgvPaneInfo.left = kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep + mIndent;
	mRgvPaneInfo.top = mYCoord - 2;
	mRgvPaneInfo.paneID = mCurrentID;

	LRadioGroupView * theRGV = new LRadioGroupView(mEditPaneInfo, theViewInfo);
	ThrowIfNil_(theRGV);

	// Store the template's type in the userCon field
	theRGV->SetUserCon(inType);
	
	mCurrentID++;

	// Create two radiobuttons in this group
	mRadioPaneInfo.left = 2;
	mRadioPaneInfo.top = 2;
	mRadioPaneInfo.paneID = mCurrentID;
	mRadioPaneInfo.superView = theRGV;

	theRadio = new LStdRadioButton(mRadioPaneInfo, rPPob_TmplEditorWindow + mCurrentID, 
								   inValue, mLabelTraitsID, (UInt8 *)(inTitleType ? "\pOn":"\pYes"));
	ThrowIfNil_(theRadio);
	
	mCurrentID++;
	mRadioPaneInfo.left += kTmplRadioWidth + kTmplHorizSep;
	mRadioPaneInfo.paneID = mCurrentID;

	theRadio = new LStdRadioButton(mRadioPaneInfo, rPPob_TmplEditorWindow + mCurrentID, 
								   inValue, mLabelTraitsID, (UInt8 *)(inTitleType ? "\pOff":"\pNo"));
	ThrowIfNil_(theRadio);
	
	theRGV->SetCurrentRadioID( inValue ?  mCurrentID - 1 : mCurrentID );
	
	// Advance the counters
	mYCoord += mRgvPaneInfo.height + kTmplVertSkip;
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//	¥ AddWasteField													[public]
// ---------------------------------------------------------------------------

// CWasteEditView::CWasteEditView(
// 	const SPaneInfo&	inPaneInfo,
// 	const SViewInfo&	inViewInfo,
// 	UInt16				inTextAttributes,
// 	ResIDT				inTextTraitsID)
// 
// 	: LView(inPaneInfo, inViewInfo)
// {
// 	mTextAttributes = inTextAttributes;
// 	InitWasteEditView(inTextTraitsID);
// }
// typedef struct	SViewInfo {
// 	SDimension32	imageSize;
// 	SPoint32		scrollPos;
// 	SPoint32		scrollUnit;
// 	SInt16			reconcileOverhang;
// } SViewInfo;
// 
// struct SDimension32 {
// 	SInt32	width;
// 	SInt32	height;
// };
// 
// struct SPoint32 {
// 	SInt32	h;
// 	SInt32	v;
// };


void
CTmplEditorWindow::AddWasteField(OSType inType)
{
	SViewInfo	theViewInfo;
	
	mEditPaneInfo.left = kTmplLeftMargin + mIndent;
	mEditPaneInfo.top = mYCoord;
	mEditPaneInfo.paneID = mCurrentID;
	
	CWasteEditView * theWasteEdit = new CWasteEditView(mEditPaneInfo, theViewInfo, 0, mEditTraitsID);
	ThrowIfNil_(theWasteEdit);

	// Store the template's type in the userCon field
	theWasteEdit->SetUserCon(inType);
	
	// Advance the counters
	mYCoord += mEditPaneInfo.top + kTmplVertSkip;
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//	¥ AddRectField													[public]
// ---------------------------------------------------------------------------
// 		AddRectField(theTop, theLeft, theBottom, theRight, inType, rPPob_TmplEditorWindow + mCurrentID, 255, 0, 
// 					 UKeyFilters::SelectTEKeyFilter(keyFilter_Integer));

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

// 	ThrowIfNil_(  );

	// Store the template's type in the userCon field
	
	// Advance the counters

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

