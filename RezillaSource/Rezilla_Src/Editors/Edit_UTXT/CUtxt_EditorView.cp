// ===========================================================================
// CUtxt_EditorView.cp
// 
//                       Created: 2004-12-08 18:21:21
//             Last modification: 2005-01-16 12:56:49
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CUtxt_EditorView.h"
#include "CUtxt_EditorDoc.h"
#include "CUtxt_EditorWindow.h"
#include "CRezObj.h"
#include "CRezillaPrefs.h"
#include "RezillaConstants.h"

#include <LMenuBar.h>
#include <string.h>


PP_Begin_Namespace_PowerPlant

// Statics
LMenu *		CUtxt_EditorView::sUtxtSizeMenu = nil;
LMenu *		CUtxt_EditorView::sUtxtStyleMenu = nil;


// ---------------------------------------------------------------------------
//	¥ CUtxt_EditorView						Default Constructor		  [public]
// ---------------------------------------------------------------------------

CUtxt_EditorView::CUtxt_EditorView()
		: LMLTEPane()
{
}


// ---------------------------------------------------------------------------
//	¥ CUtxt_EditorView						Stream Constructor		  [public]
// ---------------------------------------------------------------------------
// Use the Preference interface settings when creating a new TEXT resource.

CUtxt_EditorView::CUtxt_EditorView(
	LStream*	inStream)

	: LMLTEPane(inStream)
{
	TextTraitsRecord theTraits = CRezillaPrefs::GetStyleElement( CRezillaPrefs::prefsType_Curr );
	SInt16		justification = teFlushDefault;
// 	TextStyle	theStyle;

// 	theStyle.tsFont			= theTraits.fontNumber;
// 	theStyle.tsFace			= static_cast<UInt8>(theTraits.style);
// 	theStyle.tsSize			= theTraits.size;
// 	theStyle.tsColor		= theTraits.color;
// 	justification			= theTraits.justification;
// 
// 	::TextFont(theStyle.tsFont);		// Set Port Font and Size so TE
// 	::TextSize(theStyle.tsSize);		// uses the correct settings for
// 										// its internal tables.
// 
// 	::TESetStyle( doAll, &theStyle, false, mTextEditH );
// 	::TESetAlignment( justification, mTextEditH );
}


// ---------------------------------------------------------------------------
//	¥ ~CUtxt_EditorView						Destructor				  [public]
// ---------------------------------------------------------------------------

CUtxt_EditorView::~CUtxt_EditorView()
{
	this->RemoveUnicodeMenus();
}


#pragma mark -


// ---------------------------------------------------------------------------
//	¥ FinishCreateSelf
// ---------------------------------------------------------------------------

void
CUtxt_EditorView::FinishCreateSelf()
{
	if ( CRezillaPrefs::GetPrefValue(kPref_editors_doFontSubst) ) {
		TXNControlTag ctrlTags[1] = { kTXNDoFontSubstitution };
		TXNControlData ctrlData[1] = { {true} };

		OSStatus status = ::TXNSetTXNObjectControls( mTXNObject, false, 2, ctrlTags, ctrlData );
	}
}


// ---------------------------------------------------------------------------
// 	FindCommandStatus
// ---------------------------------------------------------------------------

void
CUtxt_EditorView::FindCommandStatus(
	CommandT	inCommand,
	Boolean		&outEnabled,
	Boolean		&outUsesMark,
	UInt16		&outMark,
	Str255		outName)
{	
	try
	{
		// First deal with the Size menu 
		if ( (inCommand >= cmd_MenuUtxtSizeBase) && (inCommand <= cmd_MenuUtxtSizeLast) )
		{
			Fixed	theSize;

			GetFontSize(theSize);
			
			// This won't put a checkMark if a non-standard size is
			// selected. Size is a Fixed (16-bit signed int + 16-bit
			// fraction).
			if ( theSize == (inCommand - cmd_MenuUtxtSizeBase) << 16 ) {
				outMark = checkMark;
			} else {
				outMark = 0;
			}
			outEnabled = true;
			outUsesMark = true;
			outName[0] = 0;
			return;
		}
		
		// Now deal with the Style menu 
		if ( (inCommand >= cmd_Plain) && (inCommand <= cmd_Extend) )
		{
			Style theStyle;
			GetFontStyle(theStyle);
			
			// This won't put a checkMark next to "Other size" if a
			// non-standard size is selected.
			if ( inCommand == cmd_Plain ) {
				outMark = theStyle ? 0 : checkMark;
			} else {
				UInt8 i = inCommand - cmd_Plain - 1;
				outMark = (theStyle & (1 << i)) ? checkMark : 0;
			}
			outEnabled = true;
			outUsesMark = true;
			outName[0] = 0;
			return;
		}
		
		// Other commands
		switch( inCommand )
		{				
			case cmd_FontLarger:
			case cmd_FontSmaller:
			outEnabled = true;
			outUsesMark = false;
			outMark = 0;
			outName[0] = 0;
				break;				

			case cmd_FontOther:
			outEnabled = true;
			outUsesMark = false;
			outMark = 0;
			outName[0] = 0;
			break;

			default:
			LMLTEPane::FindCommandStatus(inCommand, outEnabled,
									outUsesMark, outMark, outName);
			break;
			
		}
	}
	catch( ... )
	{
		outEnabled = false;
		outUsesMark = false;
		outMark = 0;
		outName[0] = 0;
	}
}


// ---------------------------------------------------------------------------
//	¥ ObeyCommand							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CUtxt_EditorView::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;

	// Now check for size menu
	if ( (inCommand >= cmd_MenuUtxtSizeBase) && (inCommand <= cmd_MenuUtxtSizeLast) )
	{
		// Size is a Fixed (16-bit signed int + 16-bit fraction)
		SetFontSize( (inCommand - cmd_MenuUtxtSizeBase) << 16);
		return true;
	}
	
	switch (inCommand) {

		case cmd_Cut: 
		case cmd_Paste: 
		case cmd_Clear: 
		LMLTEPane::ObeyCommand(inCommand, ioParam);
		mOwnerWindow->SetLengthField( GetDataSize() );
		break;

		case cmd_FontLarger: {	
			Fixed	longSize;
			Size	shortSize;
			
			GetFontSize(longSize);
			shortSize = longSize >> 16;
			if ( shortSize < cmd_MenuUtxtSizeLast - cmd_MenuUtxtSizeBase) {
				shortSize++;
				SetFontSize(shortSize  << 16);
			}
			break;
		}
		
		case cmd_FontSmaller: {
			Fixed	longSize;
			Size	shortSize;
			
			GetFontSize(longSize);
			shortSize = longSize >> 16;
			if (shortSize > 1) {
				shortSize--;
				SetFontSize(shortSize  << 16);
			} 
			break;
		}
			
		case cmd_Plain:
		SetFontStyle(normal);
		break;
		
		case cmd_Bold:
		case cmd_Italic:
		case cmd_Underline:
		case cmd_Outline:
		case cmd_Shadow:
		case cmd_Condense:
		case cmd_Extend: {
			Style theStyle;
			UInt8 i = inCommand - cmd_Plain - 1;
			theStyle = (1 << i);
			SetFontStyle(theStyle);
			break;
		}
		
		default:
			cmdHandled = LMLTEPane::ObeyCommand(inCommand, ioParam);
			break;
	}

	return cmdHandled;
}


// ---------------------------------------------------------------------------
// 	PutOnDuty
// ---------------------------------------------------------------------------

void
CUtxt_EditorView::PutOnDuty(LCommander *inNewTarget)
{
	OSStatus 	status;
	MenuHandle	fontMenuH;

	LCommander::PutOnDuty(inNewTarget);

	// Put up our menus when on duty
	if (LMLTEPane::sTXNFontMenuObject != NULL) {
		status = ::TXNPrepareFontMenu(mTXNObject, sTXNFontMenuObject );
		status = ::TXNGetFontMenuHandle(sTXNFontMenuObject, &fontMenuH);
	} 
	
	if ( !sUtxtSizeMenu )
	{
		sUtxtSizeMenu = new LMenu( MENU_UnicodeSize );
		ThrowIfNil_( sUtxtSizeMenu );
	}
	
	if ( !sUtxtStyleMenu )
	{
		sUtxtStyleMenu = new LMenu( MENU_UnicodeStyle );
		ThrowIfNil_( sUtxtStyleMenu );
	}
	
	// Update the menu bar
	LMenuBar	*theBar = LMenuBar::GetCurrentMenuBar();
	theBar->InstallMenu( sUtxtSizeMenu, MENU_OpenedWindows );
	theBar->InstallMenu( sUtxtStyleMenu, MENU_OpenedWindows );
	::MacInsertMenu(fontMenuH, MENU_OpenedWindows);
}


// ---------------------------------------------------------------------------
// 	TakeOffDuty
// ---------------------------------------------------------------------------

void
CUtxt_EditorView::TakeOffDuty()
{		
	LCommander::TakeOffDuty();
	this->RemoveUnicodeMenus();
}


// ---------------------------------------------------------------------------
//  SpendTime
// ---------------------------------------------------------------------------

void
CUtxt_EditorView::SpendTime( const EventRecord& inMacEvent)
{	
	mOwnerWindow->SetLengthField( GetDataSize() );

#if PP_MLTE_Manual_Idle
	LMLTEPane::SpendTime(inMacEvent);
#endif
}


// ---------------------------------------------------------------------------
// 	RemoveUnicodeMenus
// ---------------------------------------------------------------------------

void
CUtxt_EditorView::RemoveUnicodeMenus()
{
	LMenuBar	*theBar = LMenuBar::GetCurrentMenuBar();
	
	::MacDeleteMenu(MENU_UnicodeFonts);
	// Force redraw of MenuBar
	::InvalMenuBar();

	if ( sUtxtSizeMenu )
		theBar->RemoveMenu( sUtxtSizeMenu );
		
	if ( sUtxtStyleMenu )
		theBar->RemoveMenu( sUtxtStyleMenu );
}


// ---------------------------------------------------------------------------
//  ¥ GetModifiedText										[public]
// ---------------------------------------------------------------------------
// Note: we don't have to check if there is already a BOM because, 
// even if there was one in the original resource data, MLTE would 
// have stripped it off from its data buffer. As a consequence, if the 
// insertBOM preference is off and there was originally a BOM, it will 
// disappear upon saving.

Handle
CUtxt_EditorView::GetModifiedText() 
{
	Handle		dataH  = nil;
	OSStatus	status = ::TXNGetDataEncoded( mTXNObject, kTXNStartOffset, kTXNEndOffset,
											 &dataH, kTXNUnicodeTextData );
	ByteCount theSize;
	theSize = GetDataSize();
	
	// Deal with the Byte Order Mark (U+FEFF)
	if ( CRezillaPrefs::GetPrefValue(kPref_editors_insertBOM) ) {		
		LHandleStream	theStream;
		
		theStream << (UInt16) 0xFEFF;
		
		StHandleLocker	lock(dataH);
		theStream.WriteBlock(*dataH, theSize);

		::DisposeHandle(dataH);
		dataH = theStream.DetachDataHandle();
	}

#ifdef	REZILLA_SAVES_MLTE_STYLES
	ItemCount	runsCount = 0;

	// Deal with the multi-styles
	status = ::TXNCountRunsInRange(mTXNObject, kTXNStartOffset, kTXNEndOffset,
											 &runsCount);

	if (status == noErr && runsCount > 1) {
		Handle	styleHandle = nil;
		
		// This is not available yet: SaveStylResource() does nothing.
		// Don't know how to get a style handle.
		dynamic_cast<CUtxt_EditorDoc *>(mOwnerWindow->GetOwnerDoc())->SaveStylResource(styleHandle);
	} 
#endif
	
	return dataH;
}


// ---------------------------------------------------------------------------
//	¥ GetFontSize										[public, virtual]
// ---------------------------------------------------------------------------
// SInt16

Boolean
CUtxt_EditorView::GetFontSize( Fixed &outSize )
{
	TXNTypeAttributes	attribute;
	TXNContinuousFlags	continuousFlag = 0;
	OSStatus			status = noErr;

	attribute.tag				= kTXNQDFontSizeAttribute;
	attribute.size				= kTXNFontSizeAttributeSize;
	attribute.data.dataValue	= 0;

	status = ::TXNGetContinuousTypeAttributes(mTXNObject,&continuousFlag,1,&attribute);

	outSize = attribute.data.dataValue;

	return ((continuousFlag & kTXNSizeContinuousMask) != 0);
}


// ---------------------------------------------------------------------------
//	¥ ChangeFontSizeBy									[public, virtual]
// ---------------------------------------------------------------------------
//	Will only work if the font over the selection range is constant.  Returns
//	true if change was successful.

Boolean
CUtxt_EditorView::ChangeFontSizeBy( SInt16	inDeltaSize)
{
	Fixed	currentSize;
	Boolean canChange = GetFontSize(currentSize);

	if ( canChange ) {
		SetFontSize((SInt16) (currentSize + inDeltaSize));
	}

	return canChange;
}


// ---------------------------------------------------------------------------------
//	¥ GetFontStyle										[public, virtual]
// ---------------------------------------------------------------------------------

Boolean
CUtxt_EditorView::GetFontStyle( Style &outStyle )
{
	TXNTypeAttributes	attribute;
	TXNContinuousFlags	continuousFlag = 0;
	OSStatus			status = noErr;

	attribute.tag				= kTXNQDFontStyleAttribute;
	attribute.size				= kTXNQDFontStyleAttributeSize;
	attribute.data.dataValue	= 0;

	status = ::TXNGetContinuousTypeAttributes(mTXNObject,&continuousFlag,1,&attribute);

	outStyle = attribute.data.dataValue;

	return ((continuousFlag & kTXNStyleContinuousMask) != 0);
}


// ---------------------------------------------------------------------------------
//	¥ GetFontColor										[public, virtual]
// ---------------------------------------------------------------------------------

Boolean
CUtxt_EditorView::GetFontColor(
	const RGBColor&	inColor)
{
	TXNTypeAttributes	attribute;
	TXNContinuousFlags	continuousFlag = 0;
	OSStatus			status = noErr;

	attribute.tag				= kTXNQDFontColorAttribute;
	attribute.size				= kTXNQDFontColorAttributeSize;
	attribute.data.dataPtr		= (void *) &inColor;

	status = ::TXNGetContinuousTypeAttributes(mTXNObject,&continuousFlag,1,&attribute);

	return ((continuousFlag & kTXNColorContinuousMask) != 0);
}


// ---------------------------------------------------------------------------------
//	¥ GetDataSize														[public]
// ---------------------------------------------------------------------------------

ByteCount
CUtxt_EditorView::GetDataSize()
{
	return ::TXNDataSize( mTXNObject );
}


// ---------------------------------------------------------------------------------
//	¥ CountChanges														[public]
// ---------------------------------------------------------------------------------

OSStatus
CUtxt_EditorView::CountChanges(ByteCount & outCount)
{
	OSStatus	status = noErr;
	
	status = ::TXNGetActionChangeCount( mTXNObject, kTXNAllCountMask, &outCount);
	return status;
}


// ---------------------------------------------------------------------------------
//	¥ ResetChangesCount													[public]
// ---------------------------------------------------------------------------------
//   kTXNTextInputCountMask / kTXNRunCountMask / kTXNAllCountMask

OSStatus
CUtxt_EditorView::ResetChangesCount()
{
	return ::TXNClearActionChangeCount( mTXNObject, kTXNAllCountMask );
}


// ---------------------------------------------------------------------------
//	¥ SetUnicodePtr														[public]
// ---------------------------------------------------------------------------

void
CUtxt_EditorView::SetUnicodePtr(
	const void*		inTextP,
	ByteCount		inTextLength)
{
	ThrowIfOSStatus_( ::TXNSetData( mTXNObject,
									kTXNUnicodeTextData,
 									(void*) inTextP,
									inTextLength,
									kTXNStartOffset,
									kTXNEndOffset ) );
}




PP_End_Namespace_PowerPlant
