// ===========================================================================
// CIcon_EditorWindow.cp
// 
//                       Created: 2004-12-10 17:23:05
//             Last modification: 2005-01-01 14:01:33
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#include "CIcon_EditorDoc.h"
#include "CIcon_EditorWindow.h"
#include "CIcon_EditorView.h"
#include "RezillaConstants.h"
#include "CColorCursorCache.h"
#include "CColorPane.h"
#include "CColorTableChoice.h"
#include "CDraggableTargetView.h"
#include "CIconActions.h"
#include "CIconDragToTargetAction.h"
#include "CIconEditActions.h"
#include "CIconLassoAction.h"
#include "CIconRecolorAction.h"
#include "CIconResizeImageAction.h"
#include "CIconSelection.h"
#include "CIconSelectionAction.h"
#include "CIconTargetClickedAction.h"
#include "CIconTextAction.h"
#include "CIconUndoer.h"
#include "COffscreen.h"
#include "CPatternPane.h"
#include "CRezMap.h"
#include "CRezObj.h"
#include "CRezillaApp.h"
#include "CRezillaPrefs.h"
#include "CSharedPalette.h"
#include "UCodeTranslator.h"
#include "UColorUtils.h"
#include "UHexFilters.h"
#include "UIconMisc.h"
#include "UMessageDialogs.h"
#include "UResourceMgr.h"

#include <LBevelButton.h>
#include <LStaticText.h>
#include <LEditText.h>
#include <UMemoryMgr.h>

#include <stdio.h>


// Statics
CColorCursorCache *	CIcon_EditorWindow::sColorCursorCache = nil;
SInt32				CIcon_EditorWindow::sNumPaintWindows = 0;
LMenu *				CIcon_EditorWindow::sIconActionsMenu = nil;
LMenu *				CIcon_EditorWindow::sIconColorsMenu = nil;
LMenu *				CIcon_EditorWindow::sIconFontMenu = nil;
LMenu *				CIcon_EditorWindow::sIconStyleMenu = nil;


// ---------------------------------------------------------------------------
//		¥ CIcon_EditorWindow				[public]
// ---------------------------------------------------------------------------

CIcon_EditorWindow::CIcon_EditorWindow()
{
}


// ---------------------------------------------------------------------------
//		¥ CIcon_EditorWindow				[public]
// ---------------------------------------------------------------------------

CIcon_EditorWindow::CIcon_EditorWindow(
	const SWindowInfo &inWindowInfo )
		: CEditorWindow( inWindowInfo )
{
	Initialize();
}


// ---------------------------------------------------------------------------
//		¥ CIcon_EditorWindow				[public]
// ---------------------------------------------------------------------------

CIcon_EditorWindow::CIcon_EditorWindow(
	ResIDT		inWINDid,
	UInt32		inAttributes,
	LCommander	*inSuperCommander )
		: CEditorWindow( inWINDid, inAttributes, inSuperCommander )
{
	Initialize();
}


// ---------------------------------------------------------------------------
//		¥ CIcon_EditorWindow				[public]
// ---------------------------------------------------------------------------

CIcon_EditorWindow::CIcon_EditorWindow(
			       LStream *inStream )
		: CEditorWindow( inStream )
{
	Initialize();
}


// ---------------------------------------------------------------------------
//		¥ ~CIcon_EditorWindow				[public]
// ---------------------------------------------------------------------------

CIcon_EditorWindow::~CIcon_EditorWindow()
{
	this->RemovePaintMenus();
	
	if ( mCurrentImage ) delete( mCurrentImage );
	if ( mUndoBuffer ) delete( mUndoBuffer );
	if ( mScratchBuffer ) delete( mScratchBuffer );
	
	if ( mSharedPalette ) mSharedPalette->DecrementRefCount();
	if ( mSpareRgn ) ::DisposeRgn( mSpareRgn );

	if ( mCurrentSelection ) delete( mCurrentSelection );
	if ( mUndoSelection ) delete( mUndoSelection );
	
	if ( mColorTableChoice ) delete( mColorTableChoice );
	
	--sNumPaintWindows;
	if ( sNumPaintWindows == 0 )
	{
		delete sColorCursorCache;
		sColorCursorCache = nil;
	}
	
	mSampleWell = nil;

	// Remove the window from the list of listeners to the prefs object
	CRezillaApp::sPrefs->RemoveListener(this);
}


// ---------------------------------------------------------------------------
//		¥ Initialize											[protected]
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::Initialize()
{		
	mCurrentImage = mUndoBuffer = mScratchBuffer = nil;
	mColorTableChoice = nil;
	mChanged = false;
	mLockedFlag = false;
	mCanvas = nil;
	mForeColor = kBlackColor32;
	mBackColor = kWhiteColor32;
	mPrefersIconColors = true;
	mCurrentPattern = Pattern_Black;
	mTextAction = nil;
	mSharedPalette = nil;
	mWindowIsActive = false;
	// Pencil tool is the default
	mCurrentTool = tool_Pencil;
	mPreviousTool = tool_Pencil;
	
	StRezRefSaver	aSaver( CRezillaApp::GetOwnRefNum() );

	TextTraitsRecord **textTraitsH = UTextTraits::LoadTextTraits( Txtr_PaintFont );
	if ( textTraitsH )
	{
		mTextTraits = **textTraitsH;
		if ( mTextTraits.justification == teFlushDefault )
			mTextTraits.justification = (::GetSysDirection() == -1) ? teFlushRight : teFlushLeft;
	}
	
	mSpareRgn = nil;
	mCurrentSelection = nil;
	mUndoSelection = nil;
	
	// Sample panes
	mCurrentSamplePane = nil;
	mNumSamplePanes = 0;
	for ( SInt32 count = 0; count < kMaxIconSamplePanes; count++ ) {
		mSamplePaneList[ count ] = nil;
	}
	
	// Image resizing
	mAllowImageResizing = false;
	mMinImageHeight = 4;
	mMaxImageHeight = 64;
	mMinImageWidth = 4;
	mMaxImageWidth = 64;

	if ( sColorCursorCache == nil ) {
		sColorCursorCache = new CColorCursorCache( 12, CRezillaApp::GetOwnRefNum() );
		ThrowIfMemFail_( sColorCursorCache );
	}

	++sNumPaintWindows;
}


// ---------------------------------------------------------------------------
// 	CreatePaintWindow
// ---------------------------------------------------------------------------

LWindow *
CIcon_EditorWindow::CreatePaintWindow( ResIDT inWindowID )
{
	StGWorldSaver			aSaver;
	LWindow 				*theWindow = nil;
	
	// Create the window
	::SetGDevice( GetMainDevice() );				// bug in Mac toolbox requires this
	theWindow = LWindow::CreateWindow( inWindowID, LCommander::GetTopCommander() );
	return( theWindow );
}


// ---------------------------------------------------------------------------
// 	SetImage
// ---------------------------------------------------------------------------
// 	We duplicate the image buffer, so caller can destroy the original. The
// 	inWidth & inHeight parameters are optional. They are only used by the
// 	pattern pane, because it needs to resize to the bigger of either the
// 	b&w or color pattern.

void
CIcon_EditorWindow::SetImage( COffscreen *inBuffer, SInt32 inResize, RedrawOptions inRedraw )
{
	ThrowIfNil_( inBuffer );
	
	COffscreen		*scratchBuffer = nil, *undoBuffer = nil, *imageBuffer = nil;

	// If we have a current selection, commit it and remove the selection.
	// this is required when the user changes between sample icons.
	if ( !mCurrentSelection->IsEmpty() )
		this->SelectNone();
	
	// Allocate a block of new buffers and assign a new palette to the window
	try
	{
		// allocate three buffers
		imageBuffer = inBuffer->CreateSimilarOffscreen( false );
		scratchBuffer = inBuffer->CreateSimilarOffscreen( false );
		undoBuffer = inBuffer->CreateSimilarOffscreen( false );
	
		// Tell the canvas that the image has changed
		mCanvas->Reinitialize( inBuffer, inRedraw, inResize );

		// Get rid of old buffers (if any) and use the new ones
		if ( mScratchBuffer ) delete( mScratchBuffer );
		if ( mUndoBuffer ) delete( mUndoBuffer );
		if ( mCurrentImage ) delete( mCurrentImage );
		
		mCurrentImage = imageBuffer;
		mScratchBuffer = scratchBuffer;
		mUndoBuffer = undoBuffer;
		
		// Copy the supplied image to the image buffer
		imageBuffer->CopyFrom( inBuffer );
		
		// We have a new color table, so the color popups might need to be reset
		if ( mColorTableChoice ) {
			mColorTableChoice->ImageChanged( imageBuffer->GetDepth() );
		}
	}
	catch( ... )
	{
		if ( scratchBuffer ) delete( scratchBuffer );
		if ( undoBuffer ) delete( undoBuffer );
		if ( imageBuffer ) delete( imageBuffer );
		throw;
	}
}


// ---------------------------------------------------------------------------
// 	ResetPatternPaneColors
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::ResetPatternPaneColors( RedrawOptions inRedraw )
{
	mPatternPane->SetColors( mColorPane->GetColor(), mBackColorPane->GetColor(), inRedraw );
}


// ---------------------------------------------------------------------------
// 	GetImageBuffer
// ---------------------------------------------------------------------------
// 	Do not dispose of the image.

COffscreen *CIcon_EditorWindow::GetImageBuffer()
{
	return( mCurrentImage );
}


// ---------------------------------------------------------------------------
// 	GetScratchBuffer
// ---------------------------------------------------------------------------
// 	Do not dispose of the image.

COffscreen *CIcon_EditorWindow::GetScratchBuffer()
{
	return( mScratchBuffer );
}


// ---------------------------------------------------------------------------
// 	GetScratchBuffer
// ---------------------------------------------------------------------------
// 	Do not dispose of the image.

COffscreen *CIcon_EditorWindow::GetUndoBuffer()
{
	return( mUndoBuffer );
}


// ---------------------------------------------------------------------------
// 	SetRawImageBuffer
// ---------------------------------------------------------------------------
// 	Low level call. Doesn't do a lot of stuff you might want it to.

void
CIcon_EditorWindow::SetRawImageBuffer( COffscreen *inBuffer )
{
	mCurrentImage = inBuffer;
}


// ---------------------------------------------------------------------------
// 	SetRawScratchBuffer
// ---------------------------------------------------------------------------
// 	Low level call. Doesn't do a lot of stuff you might want it to.

void
CIcon_EditorWindow::SetRawScratchBuffer( COffscreen *inBuffer )
{
	mScratchBuffer = inBuffer;
}


// ---------------------------------------------------------------------------
// 	SetRawUndoBuffer
// ---------------------------------------------------------------------------
// 	Low level call. Doesn't do a lot of stuff you might want it to.

void
CIcon_EditorWindow::SetRawUndoBuffer( COffscreen *inBuffer )
{
	mUndoBuffer = inBuffer;
}


// ---------------------------------------------------------------------------
//		¥ FinishCreateSelf											[protected]
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::FinishCreateSelf()
{	
	// The drawing view
	mContentsView = dynamic_cast<CIcon_EditorView *>(this->FindPaneByID(item_EditorContents));
	ThrowIfNil_( mContentsView );
	mContentsView->SetOwnerWindow(this);
		
	mColorTableChoice = new CColorTableChoice( this, mPrefersIconColors );
	ThrowIfMemFail_( mColorTableChoice );

	mSpareRgn = NewRgn();
	ThrowIfMemFail_( mSpareRgn );	

	mCurrentSelection = new CIconSelection;
	ThrowIfMemFail_( mCurrentSelection );

	mUndoSelection = new CIconSelection;
	ThrowIfMemFail_( mUndoSelection );
	
	CIconUndoer *anUndoer = new CIconUndoer;
	ThrowIfMemFail_( anUndoer );
	this->AddAttachment( anUndoer, nil, true );
	
	mCanvas = (CIcon_EditorView*) this->FindPaneByID( item_EditorContents );
	ThrowIfNil_( mCanvas );

	mPatternPane = (CPatternPane*) this->FindPaneByID( tool_Pattern );
	ThrowIfNil_( mPatternPane );
	mPatternPane->GetCurrentPattern( &mCurrentPattern );
	
	mColorPane = (CColorPane*) this->FindPaneByID( tool_ForeColor );
	mBackColorPane = (CColorPane*) this->FindPaneByID( tool_BackColor );
	ThrowIfNil_( mColorPane );
	ThrowIfNil_( mBackColorPane );
	
	// This may or may not exist depending on the editor
	mSampleWell = this->FindPaneByID( item_IconSampleWell );

	LBevelButton * theButton = dynamic_cast<LBevelButton *>(this->FindPaneByID( mCurrentTool ));;
	ThrowIfNil_( theButton );
	theButton->SetValue(Button_On);
	
	// The coords field
	mCoordsField = dynamic_cast<LStaticText *> (this->FindPaneByID( item_IconCoords ));
	ThrowIfNil_( mCoordsField );
	
	// Link the broadcasters
	UIconMisc::LinkListenerToControls( this, this, RidL_ToolList );
	
	// Make the window a listener to the prefs object
	CRezillaApp::sPrefs->AddListener(this);

}


// ---------------------------------------------------------------------------
//  SetChangedFlag
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::SetChangedFlag( Boolean inChanged )
{
	this->ProcessCommand( cmd_IconPaintModified, (void*) inChanged );
	mChanged = inChanged;
}


// ---------------------------------------------------------------------------
//  GetChangedFlag
// ---------------------------------------------------------------------------

Boolean
CIcon_EditorWindow::GetChangedFlag()
{
	return( mChanged );
}


// ---------------------------------------------------------------------------
//		¥ ListenToMessage				[public]
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{
	switch( inMessage )
	{
		case msg_ControlClicked:
			this->HandleToolClick(inMessage);
			break;
	
		case msg_DoubleClick:
			this->HandleToolDoubleClick(inMessage);
			break;
			
		case tool_Pattern:
			mPatternPane->GetCurrentPattern( &mCurrentPattern );
			break;

		case tool_ForeColor:			// user changed the color
			mForeColor = (Color32) ioParam;
			this->ResetPatternPaneColors( redraw_Now );
			
			// Change the text color too
			mTextTraits.color = UColorUtils::Color32ToRGB( mForeColor );
			if ( mTextAction )
				mTextAction->ChangeTextTraits( mTextTraits );
			break;
			
		case tool_BackColor:			// user changed the background color
			mBackColor = (Color32) ioParam;
			this->ResetPatternPaneColors( redraw_Now );
			break;
		
		case tool_Lasso:
		case tool_Selection:
		case tool_Text:
		case tool_Pencil:
		case tool_Eraser:
		case tool_Bucket:
		case tool_Dropper:
		case tool_Line:
		case tool_Rect:
		case tool_FilledRect:
		case tool_RoundRect:
		case tool_FilledRoundRect:
		case tool_Oval:
		case tool_FilledOval:
		case tool_HotSpot:
			this->HandleToolClick(inMessage);
			break;

		case msg_TargetViewClicked:
			this->ObeyCommand( msg_TargetViewClicked, ioParam );
			break;
		
		case msg_ImageDroppedOnTargetView:
			this->ObeyCommand( msg_ImageDroppedOnTargetView, ioParam );
			break;
			
		case msg_TextActionDied:
			if ( mTextAction == (CIconTextAction*) ioParam )
				mTextAction->DrawInsertionPoint( false );
			mTextAction = nil;
			break;
			
		default:
			dynamic_cast<CIcon_EditorDoc *>(mOwnerDoc)->ListenToMessage(inMessage, ioParam);
			break;
	}
}


// ---------------------------------------------------------------------------
// 	FindCommandStatus
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::FindCommandStatus(
	CommandT	inCommand,
	Boolean		&outEnabled,
	Boolean		&outUsesMark,
	UInt16		&outMark,
	Str255		outName)
{

	Boolean		enableIt = false;
	Boolean		fileLocked = this->GetLockFlag();
	
	try
	{
		if ( mWindowIsActive )		// don't enable things if a modal dialog (Color Picker) is up
		{
			// See if the command belongs to the Colors menu
			SInt32	currentDepth = mCurrentImage ? mCurrentImage->GetDepth() : 0;

			if ( mColorTableChoice->FindCommandStatus( currentDepth, inCommand, outEnabled,
														outUsesMark, outMark, outName ) ) {
				return;
			}								
			
			// See if the command belongs to the text editor
			if ( CIconTextAction::FindCommandStatus(	mTextTraits, inCommand, 
													outEnabled, outUsesMark,
													outMark, outName, sIconFontMenu ) ) {
				return;
			}
													
			// See if it's one of ours
			switch( inCommand )
			{
				case cmd_Copy:
					if ( mCurrentImage && !mCurrentSelection->IsEmpty() )
						enableIt = true;
					break;
					
				case cmd_Cut:
				case cmd_Clear:
				case cmd_IconFlipVertical:
				case cmd_IconFlipHorizontal:
				case cmd_IconRotateRight:
				case cmd_IconRotateLeft:				
				case cmd_IconTransparent:
					if ( mCurrentImage && !mCurrentSelection->IsEmpty() && !fileLocked ) {
						enableIt = true;
					}
					break;
				
				case cmd_SelectAll:
					if ( mCurrentImage )
						enableIt = true;
					break;
					
				case cmd_Paste:
					if ( mCurrentImage && !fileLocked )
					{
						LClipboard *theClip = LClipboard::GetClipboard();
						if ( theClip )
							enableIt = ( theClip->GetData( ImgType_Picture, nil ) > 0 );
					}
					break;
					
				case tool_SwapColors:
				case tool_BlackAndWhite:
					enableIt = true;
					break;
				
				case cmd_IconResizeImage:
					enableIt = mAllowImageResizing && !fileLocked;
					break;
				
				case cmd_IconDeleteImage:
					if ( mCurrentSamplePane && mCurrentSamplePane->CanBeDeleted()
							&& mCurrentSamplePane->IsUsed() 
							&& !fileLocked ) {
						enableIt = true;
					}	
					break;
					
			}
		}
		
		if ( enableIt )
		{
			outEnabled = true;
			outUsesMark = false;
			outMark = 0;
			outName[0] = 0;
		} else {
			CEditorWindow::FindCommandStatus( inCommand, outEnabled, outUsesMark, outMark, outName );
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
// 	ObeyCommand							[public, virtual]
// ---------------------------------------------------------------------------
// Don't use an StGWorldSaver here because SelectAll() may destroy the
// current GWorld and then we'd set it back to a deleted one. (crash)

Boolean
CIcon_EditorWindow::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;
	CIconAction	*theAction = nil;
	
	try
	{
		// If we don't have an image (shouldn't happen), punt
		if ( !mCurrentImage )
			return(  LWindow::ObeyCommand( inCommand, ioParam ) );
		
		// First offer the event to the text handler
		if ( CIconTextAction::ObeyCommand( this, mTextAction, inCommand, &mTextTraits, nil ) )
			return( true );
		
		// Next offer the event to the color table code
		if ( mCurrentImage )
			if ( mColorTableChoice->ObeyCommand( mCurrentImage->GetDepth(), inCommand ) )
				return( true );
		
		// Otherwise, handle it here
		switch( inCommand )
		{
			// Editing Commands
			case cmd_Cut:
			case cmd_Copy:
			case cmd_Paste:
			case cmd_Clear:
			case cmd_IconFlipVertical:
			case cmd_IconFlipHorizontal:
			case cmd_IconRotateRight:
			case cmd_IconRotateLeft:
			case cmd_IconTransparent:
			case cmd_IconDragImage:
			case cmd_IconRecolorCurrentImage:
			case msg_TargetViewClicked:
			case msg_ImageDroppedOnTargetView:
			case cmd_IconResizeImage:
			case cmd_IconDeleteImage:
			case tool_Lasso:			// double-click on lasso
			
				theAction = (CIconAction*) this->CreateNewAction( inCommand, ioParam );
				if ( theAction )
					theAction->DoIt();		// this will delete or post the command
				return( true );
			
			case cmd_SelectAll:
				this->SelectAll();
				return( true );
			
			case tool_SwapColors:
				this->SwapColors();
				return( true );
			
			case tool_BlackAndWhite:
				this->ForceBlackAndWhite();
				return( true );
				
		}
		
		// We didn't handle it -- give it to the window
		return( LWindow::ObeyCommand( inCommand, ioParam ) );
	}
	catch( SInt32 theErr )
	{
		if ( theAction )
			delete( theAction );
	
		UMessageDialogs::ErrorWithString(CFSTR("ErrorWithIconEditor"), theErr);
		return( true );
	}
// 	return cmdHandled;
}


// ---------------------------------------------------------------------------
//  HandleKeyPress
// ---------------------------------------------------------------------------

Boolean
CIcon_EditorWindow::HandleKeyPress( const EventRecord &inKeyEvent )
{
	Boolean		handledIt = false;
	UInt8 		theChar = inKeyEvent.message & charCodeMask;
	
	// Handle arrow keys for the text tool
	if ( mCurrentTool == tool_Text )
	{
		if ( inKeyEvent.modifiers & cmdKey )
		{
			// Increase/decrease the font size if Cmd-up/down arrow hit
			if ( theChar == char_UpArrow )
				CIconTextAction::ObeyCommand( this, mTextAction, cmd_FontLarger, &mTextTraits, nil );
			else if ( theChar == char_DownArrow )
				CIconTextAction::ObeyCommand( this, mTextAction, cmd_FontSmaller, &mTextTraits, nil );

			// The Style menu's size checkmark will be changed
			LCommander::SetUpdateCommandStatus( true );
		}
		else if ( mTextAction )
			mTextAction->HandleKeyDown( inKeyEvent );
			
		handledIt = true;
	}
	
	// Handle arrow keys
	if ( !handledIt && mCurrentImage && !mCurrentSelection->IsEmpty() )
		switch( theChar )
		{
			case char_LeftArrow:
				this->NudgeSelection( -1, 0 );
				handledIt = true;
				break;
			case char_RightArrow:
				this->NudgeSelection( 1, 0 );
				handledIt = true;
				break;
			case char_UpArrow:
				this->NudgeSelection( 0, -1 );
				handledIt = true;
				break;
			case char_DownArrow:
				this->NudgeSelection( 0, 1 );
				handledIt = true;
				break;
				
			case char_Clear:
			case char_Backspace:
				this->ObeyCommand( cmd_Clear, nil );
				handledIt = true;
				break;
		}
		
	// Pass to parent if we didn't handle the key
	if ( !handledIt )
		handledIt = LWindow::HandleKeyPress( inKeyEvent );
	
	return( handledIt );
}


// ---------------------------------------------------------------------------
// 	NudgeSelection
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::NudgeSelection( SInt32 dh, SInt32 dv )
{
	if ( !mCurrentImage ) return;
	
	CIconMoveAction	*theMoveAction = (CIconMoveAction*) this->CreateNewAction( cmd_IconMoveSelection );
	if ( theMoveAction )
		theMoveAction->Move( dh, dv );
}


// ---------------------------------------------------------------------------
// 	AdjustCursorInCanvas
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::AdjustCursorInCanvas( Point pt, const EventRecord& inMacEvent )
{
	SInt32		newCursorID = 0;
	Boolean		isOptionKey = ( inMacEvent.modifiers & optionKey ) ? true : false;
	Boolean		isInSelection = this->CanvasPointInSelection( pt );
	
	if ( mCurrentImage ) {
		// Make sure the cursor isn't in one of the margins instead of the image
		// (this shouldn't happen)
		SInt32 theCol, theRow;
		mCanvas->MapPointToCell( pt, &theCol, &theRow );
		if ( (theCol >= 0) || (theCol < mCurrentImage->GetWidth()) &&
			 (theRow >= 0) && (theRow < mCurrentImage->GetHeight()) )
		{
			if ( isOptionKey && !isInSelection ) {
				newCursorID = CURS_Dropper;
			} else {
				switch( mCurrentTool ) {
					case tool_Lasso:
						newCursorID = isInSelection ? CURS_HandFingers : CURS_Lasso;
						break;
						
					case tool_Selection:
						newCursorID = isInSelection ? CURS_HandFingers : CURS_Plus;
						break;
						
					case tool_Eraser:
						newCursorID = CURS_Eraser;
						break;
						
					case tool_Pencil:
						newCursorID = CURS_Pencil;
						break;
						
					case tool_Bucket:
						newCursorID = CURS_Bucket;
						break;
						
					case tool_Dropper:
						newCursorID = CURS_Dropper;
						break;
					
					case tool_HotSpot:
						newCursorID = CURS_HotSpot;
						break;
						
					case tool_Text:
						newCursorID = CURS_TextBeam;
						break;
						
					case tool_Line:			
					case tool_Rect:
					case tool_FilledRect:
					case tool_RoundRect:
					case tool_FilledRoundRect:
					case tool_Oval:
					case tool_FilledOval:
						newCursorID = CURS_Plus;
						break;
				}
			}
		}
	}
	
	if ( newCursorID )
		sColorCursorCache->SetColorCursor( newCursorID );
	else
		UCursor::SetArrow();
}


// ---------------------------------------------------------------------------
// 	CanvasPointInSelection
// ---------------------------------------------------------------------------

Boolean
CIcon_EditorWindow::CanvasPointInSelection( Point canvasPt )
{
	SInt32	theRow, theCol;
	
	if ( mCanvas->MapPointToCell( canvasPt, &theCol, &theRow ) )
		if ( mCurrentSelection->PointInSelection( theCol, theRow ) )
			return( true );
			
	return( false );
}


// ---------------------------------------------------------------------------
// 	HandleMouseDownInCanvas
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::HandleMouseDownInCanvas( const SMouseDownEvent &inEvent )
{			
	OSType	theTool = mCurrentTool;
	
	if ( !mCurrentImage ) return;
	
	if ( (inEvent.macEvent.modifiers & optionKey) && !this->CanvasPointInSelection(inEvent.whereLocal) )
		theTool = tool_Dropper;

	// Create an action depending on the current tool
	CIconTrackingPaintAction *theAction = (CIconTrackingPaintAction*) this->CreateNewAction( theTool );
	if ( !theAction ) return;
	
	// Send the mouse down event to the tool
	theAction->HandleMouseDown( inEvent );
}


// ---------------------------------------------------------------------------
// 	HandleCanvasDraw
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::HandleCanvasDraw()
{
	COffscreen *theBuffer = this->GetCombinedBuffer();
	if ( theBuffer )
		mCanvas->DrawFrom( theBuffer );
}


// ---------------------------------------------------------------------------
// 	GetCombinedBuffer
// ---------------------------------------------------------------------------
// 	Returns the current image buffer with the current selection blitted on
// 	top of it. The buffer is only valid until the next call into the
// 	PaintView. Returns nil if no buffers have been allocated (startup,
// 	out-of-memory, etc).

COffscreen *CIcon_EditorWindow::GetCombinedBuffer()
{
	if ( !mCurrentImage || !mCurrentSelection || !mScratchBuffer )
		return( nil );
		
	mCurrentImage->CopyTo( mScratchBuffer );
	mCurrentSelection->DrawInto( mScratchBuffer );
	
	return( mScratchBuffer );
}


// ---------------------------------------------------------------------------
// 	GetActionSettings
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::GetActionSettings( SPaintAction *outSettings )
{
	UIconMisc::ClearMemory( outSettings, sizeof(SPaintAction) );
	outSettings->theForeColor = mForeColor;
	outSettings->theBackColor = mBackColor;
	outSettings->thePattern = mCurrentPattern;
	outSettings->currentBuffer = mCurrentImage;
	outSettings->scratchBuffer = mScratchBuffer;
	outSettings->thePaintView = this;
	outSettings->theCanvas = mCanvas;
	outSettings->theSelection = mCurrentSelection;
	
}


// ---------------------------------------------------------------------------
// 	CreateNewAction
// ---------------------------------------------------------------------------
// 	If the action's constructor throws an error, we'll display an error
// 	message and return nil.

CIconAction *
CIcon_EditorWindow::CreateNewAction( OSType inActionType, void *ioParam )
{
	SPaintAction		actionSettings;
	
	try
	{
		// Get the current settings
		this->GetActionSettings( &actionSettings );
		
		// Create the object
		switch( inActionType ) {
			case tool_Lasso:
				return new CIconLassoAction( actionSettings );
	
			case tool_Selection:
				return new CIconSelectionAction( actionSettings );
			
			case cmd_IconMoveSelection:
				return new CIconMoveAction( actionSettings );
			
			case tool_Eraser:
				return new CIconEraserAction( actionSettings );
				
			case tool_Pencil:
				return new CIconPenAction( actionSettings );
			
			case tool_Dropper:
				return new CIconDropperAction( actionSettings, mColorPane, mBackColorPane );
			
			case tool_Bucket:
				return new CIconBucketAction( actionSettings );
			
			case tool_Line:
				return new CIconLineAction( actionSettings );
				
			case tool_Rect:
			case tool_FilledRect:
				return new CIconRectAction( actionSettings, inActionType == tool_FilledRect );
			
			case tool_RoundRect:
			case tool_FilledRoundRect:
				return new CIconRoundRectAction( actionSettings, inActionType == tool_FilledRoundRect );
				break;
				
			case tool_Oval:
			case tool_FilledOval:
				return new CIconOvalAction( actionSettings, inActionType == tool_FilledOval );
			
			case cmd_IconEraseAll:
				return new CIconEraseAllAction( actionSettings );
		
			case cmd_Cut:
				return new CIconCutAction( actionSettings );
				
			case cmd_Copy:
				return new CIconCopyAction( actionSettings );
				
			case cmd_Paste:
				return new CIconPasteAction( actionSettings );
				
			case cmd_Clear:
				return new CIconClearAction( actionSettings );
			
			case cmd_IconFlipVertical:
				return new CFlipVerticalAction( actionSettings );
				
			case cmd_IconFlipHorizontal:
				return new CFlipHorizontalAction( actionSettings );

			case cmd_IconRotateRight:
				return new CIconRotateAction( actionSettings, -90 );
				
			case cmd_IconRotateLeft:
				return new CIconRotateAction( actionSettings, 90 );

			case cmd_IconTransparent:
				return new CIconTransparentAction( actionSettings );

			case cmd_IconDragImage:			// Don't display errors during Drag&Drop
				try
				{
					return new CIconDragImageAction( actionSettings, (SDragImageInfo*) ioParam );
				}
				catch( ... )
				{
				}
				return nil;
			
			case tool_HotSpot:
				return new CIconHotSpotAction( actionSettings );
		
			case cmd_IconRecolorCurrentImage:
				return new CIconRecolorAction( actionSettings, (CTabHandle) ioParam );
			
			case msg_ImageDroppedOnTargetView:
				return new CIconDragToTargetAction( actionSettings, (SImageDropOnTargetView*) ioParam );
			
			case msg_TargetViewClicked:
				return new CIconTargetClickedAction( actionSettings, (CDraggableTargetView*) ioParam );
			
			case cmd_IconResizeImage:
				return new CIconResizeImageAction( actionSettings );
			
			case cmd_IconDeleteImage:
				return new CIconDeleteImageAction( actionSettings );
			
			case tool_Text:
				return new CIconTextAction( actionSettings );
				
			default:
				return( nil );
		}
	} 
	catch( SInt32 theErr )
	{
		UMessageDialogs::ErrorWithString(CFSTR("ErrorWithIconEditor"), theErr);
	}
	catch( ... )
	{
		UMessageDialogs::ErrorWithString(CFSTR("ErrorWithIconEditor"), err_IconGeneric);
	}
	
	return( nil );
}


// ---------------------------------------------------------------------------
// 	SwapUndoState
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::SwapUndoState()
{
	ThrowIf_( !mCurrentImage || !mUndoBuffer || !mScratchBuffer || !mCanvas );
	
	COffscreen	*tempOffscreen = mCurrentImage;
	mCurrentImage = mUndoBuffer;
	mUndoBuffer = tempOffscreen;
	
	CIconSelection *tempSelection = mCurrentSelection;
	mCurrentSelection = mUndoSelection;
	mUndoSelection = tempSelection;
	
	this->SetChangedFlag( true );
	
	this->HandleCanvasDraw();
	this->RedrawSampleView( nil );
}


// ---------------------------------------------------------------------------
// 	CopyToUndo
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::CopyToUndo()
{
	ThrowIfNil_( mCurrentImage );
	ThrowIfNil_( mUndoBuffer );

	// Copy the image to the undo buffer	
	mCurrentImage->CopyTo( mUndoBuffer );

	// Copy the selection to the undo area
	mUndoSelection->SetSelection( mCurrentSelection );
}


// ---------------------------------------------------------------------------
// 	HandleToolClick
// ---------------------------------------------------------------------------
// LPane *thePane 
void
CIcon_EditorWindow::HandleToolClick(PaneIDT inPaneID)
{
	if ( inPaneID != mCurrentTool )
	{
		switch( inPaneID )
		{
			case tool_Eraser: 		case tool_Pencil:		case tool_Dropper: 		
			case tool_Bucket:		case tool_Line: 		case tool_Rect:			
			case tool_FilledRect:	case tool_RoundRect:	case tool_FilledRoundRect:
			case tool_Oval:			case tool_FilledOval:
			case tool_Lasso:		case tool_Selection:	case tool_HotSpot:
			case tool_Text:
			
			// Release the button corresponding to the current tool
			LBevelButton * theButton = dynamic_cast<LBevelButton *>(this->FindPaneByID( mCurrentTool ));;
			ThrowIfNil_( theButton );
			theButton->SetValue(Button_Off);

			// Cancel the selection if any
			this->SelectNone();	
			
			// Update the current tool to the newly clicked one
			mCurrentTool = inPaneID;
			// Keep track of previous tool: double-clicking on eraser
			// erases all and reverts to previous tool
			if ( inPaneID != tool_Eraser ) {
				mPreviousTool = inPaneID;
			}

			break;
		}
	}
}


// ---------------------------------------------------------------------------
// 	HandleToolDoubleClick
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::HandleToolDoubleClick(PaneIDT inPaneID)
{
	if ( !mCurrentImage ) return;
	
	switch(inPaneID)
	{
		case tool_Eraser:
			this->EraseAll();
			break;
			
		case tool_Selection:
			this->SelectAll();
			break;
			
		case tool_Lasso:
			this->ObeyCommand( tool_Lasso, 0 );
			break;
	}
}


// ---------------------------------------------------------------------------
// 	EraseAll
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::EraseAll()
{
	if ( !mCurrentImage ) return;

	CIconEraseAllAction	*theAction = (CIconEraseAllAction*) this->CreateNewAction( cmd_IconEraseAll );
	if ( !theAction ) return;
	
	StGWorldSaver		aSaver;
	
	theAction->DoIt();
	// Revert to previous tool
	this->ChangeTool( mPreviousTool );
}


// ---------------------------------------------------------------------------
// 	ChangeTool
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::ChangeTool( OSType toWhat )
{
	if ( toWhat == tool_None ) return;
	
	LControl *prevTool = (LControl*) this->FindPaneByID( mCurrentTool );
	LControl *newTool = (LControl*) this->FindPaneByID( toWhat );
	
	if ( prevTool != newTool )
	{
		if ( newTool ) {
			// This triggers a broadcast
			newTool->SetValue( 1 );	
		}
		
		mCurrentTool = toWhat;

		// Keep track of previous tool: double-clicking on eraser erases 
		// all and reverts to previous tool
		if ( toWhat != tool_Eraser )
			mPreviousTool = toWhat;
	}
}


// ---------------------------------------------------------------------------
// 	ActivateSelf
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::ActivateSelf()
{
	LWindow::ActivateSelf();
	// To draw selection area
	this->StartIdling();
}


// ---------------------------------------------------------------------------
// 	DeactivateSelf
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::DeactivateSelf()
{
	LWindow::DeactivateSelf();

	if ( !mCurrentSelection->IsEmpty() ) {
		// Erase the selection (draw over it) rather than Refresh() because
		// it flickers
		mCanvas->Draw( nil );
	}
	// Since we don't draw the selection in background
	this->StopIdling();
}


// ---------------------------------------------------------------------------
// 	SelectAll
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::SelectAll()
{
	if ( !mCurrentImage ) return;

	Rect	r;
	
	SetRect( &r, 0, 0, mCurrentImage->GetWidth(), mCurrentImage->GetHeight() );
	this->SetSelection( r );
}


// ---------------------------------------------------------------------------
// 	SelectNone
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::SelectNone()
{
	if ( !mCurrentImage ) return;
	
	this->CommitSelection();
	// Erase the selection (draw over it) rather than Refresh()
	this->HandleCanvasDraw();
	// Clear the region
	mCurrentSelection->SelectNone();
}


// ---------------------------------------------------------------------------
// 	CommitSelection
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::CommitSelection()
{
	if ( !mCurrentImage ) return;

	// If we have an open text buffer, commit it
	if ( mTextAction )
	{
		mTextAction->CloseEditSession();
		mTextAction = nil;
	}
	
	// Commit the current selection to the image buffer
	if ( !mCurrentSelection->IsEmpty() ) {
		mCurrentSelection->DrawInto( mCurrentImage );
	}
}


// ---------------------------------------------------------------------------
// 	SetSelection
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::SetSelection( const Rect &r, Boolean toLasso )
{
	if ( !mCurrentImage ) return;

	// Commit current selection and kill the region
	this->SelectNone();
	
	this->ChangeTool( toLasso ? tool_Lasso : tool_Selection );
	mCurrentSelection->SetSelection( mCurrentImage, r );
	
	this->EraseAreaUnderSelection();
}


// ---------------------------------------------------------------------------
// 	SetSelection
// ---------------------------------------------------------------------------
// 	We duplicate the region.

void
CIcon_EditorWindow::SetSelection( RgnHandle inRgn, Boolean toLasso )
{
	if ( !mCurrentImage ) return;

	// Commit current selection and kill the region
	this->SelectNone();
	
	this->ChangeTool( toLasso ? tool_Lasso : tool_Selection );
	mCurrentSelection->SetSelection( mCurrentImage, inRgn );
	
	this->EraseAreaUnderSelection();
}


// ---------------------------------------------------------------------------
// 	EraseAreaUnderSelection
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::EraseAreaUnderSelection()
{
	if ( !mCurrentSelection->IsEmpty() )
	{
		StGWorldSaver		aSaver;
		
		mCurrentImage->BeginDrawing();
			StColorPenState		aPenState;
			aPenState.Normalize();
			// PmBackColor( mBackColor );
			mCurrentImage->SetBackColor( mBackColor );
			EraseRgn( mCurrentSelection->GetRegion() );		
		mCurrentImage->EndDrawing();
	}
}


// ---------------------------------------------------------------------------
// 	SpendTime
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::SpendTime( const EventRecord & )
{
	if ( !this->IsActive() || !mCurrentImage ) return;
	
	Boolean hasSelection = !mCurrentSelection->IsEmpty();
	if ( !hasSelection && !mTextAction ) return;
	
	StGWorldSaver		aSaver;
	mCanvas->FocusDraw();
	
	StColorPenState		penSaver;
	// Selection always drawn in black
	penSaver.Normalize();
	
	if ( hasSelection )
	{
		if ( UMarchingAnts::BeginMarch() )
		{
			mCanvas->MapRegionToCanvas( mCurrentSelection->GetRegion(), mSpareRgn );
			
			// Clip inside the canvas a bit or we don't always clean up well
			Rect		r;
			mCanvas->GetInsideDrawingRect( &r );
			StClipRgnState	saveSetAndRestore( r );
			
			// Draw the marching ants
			::FrameRgn( mSpareRgn );
			UMarchingAnts::EndMarch();
		}
	}
	else if ( mTextAction )
	{
		mTextAction->Idle();
	}
}


// ---------------------------------------------------------------------------
// 	RedrawSampleView
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::RedrawSampleView( Rect * )
{
	if ( !mCurrentSamplePane ) return;
	
	COffscreen *theComboBuffer = this->GetCombinedBuffer();
	if ( theComboBuffer )
		mCurrentSamplePane->CopyBufferFrom( theComboBuffer, redraw_Now );
}


// ---------------------------------------------------------------------------
// 	SwapColors
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::SwapColors()
{
	Color32		oldFore = mColorPane->GetColor();
	Color32		oldBack = mBackColorPane->GetColor();
	
	// Note that these trigger broadcasts which we hear
	mColorPane->SetColor( oldBack, redraw_Now );
	mBackColorPane->SetColor( oldFore, redraw_Now );
}


// ---------------------------------------------------------------------------
// 	ForceBlackAndWhite
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::ForceBlackAndWhite()
{
	// Note that these trigger broadcasts which we hear
	mColorPane->SetColor( kBlackColor32, redraw_Now );
	mBackColorPane->SetColor( kWhiteColor32, redraw_Now );
}


// ---------------------------------------------------------------------------
// 	PutOnDuty
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::PutOnDuty(LCommander *inNewTarget)
{
	// Flush pending mouseDown events because Constructor has "set front
	// clicks" flag set and users don't expect to accidentally start
	// painting when they click on our paint window when we're not the
	// foreground application.
	// This is probably a bug in PowerPlant -- we shouldn't really see the
	// click because we have cleared our "getfrontclick" flag for this
	// particular window. but this fixes it.
	::FlushEvents( mDownMask, 0 );
	
	LWindow::PutOnDuty(inNewTarget);

	// Put up our menus when we're on duty
	{
		if ( !sIconActionsMenu )
		{
			sIconActionsMenu = new LMenu( MENU_IconActions );
			ThrowIfNil_( sIconActionsMenu );
		}
		
		if ( !sIconColorsMenu )
		{
			sIconColorsMenu = new LMenu( MENU_IconColors );
			ThrowIfNil_( sIconColorsMenu );
		}
		
		if ( !sIconStyleMenu )
		{
			sIconStyleMenu = new LMenu( MENU_IconStyle );
			ThrowIfNil_( sIconStyleMenu );
		}
		
		if ( !sIconFontMenu )
		{
			sIconFontMenu = new LMenu( MENU_IconFonts );
			ThrowIfNil_( sIconFontMenu );

			MenuHandle	macH = sIconFontMenu->GetMacMenuH();
			if ( macH )
				::AppendResMenu( macH, 'FONT' );
		}
	}
	
	// Update the menu bar
	LMenuBar	*theBar = LMenuBar::GetCurrentMenuBar();
	theBar->InstallMenu( sIconActionsMenu, MENU_OpenedWindows );	
	theBar->InstallMenu( sIconColorsMenu, MENU_OpenedWindows );
	theBar->InstallMenu( sIconFontMenu, MENU_OpenedWindows );
	theBar->InstallMenu( sIconStyleMenu, MENU_OpenedWindows );
	mWindowIsActive = true;
}


// ---------------------------------------------------------------------------
// 	TakeOffDuty
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::TakeOffDuty()
{
	if ( mTextAction )
		mTextAction->DrawInsertionPoint( false );		// erase text insertion point
		
	LWindow::TakeOffDuty();
	this->RemovePaintMenus();
	mWindowIsActive = false;
}


// ---------------------------------------------------------------------------
// 	RemovePaintMenus
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::RemovePaintMenus()
{
	LMenuBar	*theBar = LMenuBar::GetCurrentMenuBar();
	
	if ( sIconColorsMenu )
		theBar->RemoveMenu( sIconColorsMenu );
	
	if ( sIconActionsMenu )
		theBar->RemoveMenu( sIconActionsMenu );
		
	if ( sIconFontMenu )
		theBar->RemoveMenu( sIconFontMenu );
		
	if ( sIconStyleMenu )
		theBar->RemoveMenu( sIconStyleMenu );
}


// ---------------------------------------------------------------------------
// 	ThrowIfInvalidDepth
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::ThrowIfInvalidDepth( SInt32 inDepth )
{
	switch( inDepth )
	{
		case 1:		case 2:		case 4:
		case 8:		case 16:	case 32:
			return;
			
		default:
			throw( err_IconInvalidImageDepth );
	}
}


// ---------------------------------------------------------------------------
// 	SetTargetView
// ---------------------------------------------------------------------------
// Does not commit the previous selection to the buffer, so do so before
// calling this if you want.

void
CIcon_EditorWindow::SetTargetView( CDraggableTargetView *inBox, RedrawOptions inRedrawHow )
{
	if ( inBox == mCurrentSamplePane ) return;
	if ( !inBox ) return;				// shouldn't happen
	
	// Set our current image
	this->SetImage( inBox->GetBuffer(), resize_Canvas, inRedrawHow );
	
	// Change the hiliting of the target box
	if ( mCurrentSamplePane )
		mCurrentSamplePane->SetTarget( false, inRedrawHow );
	inBox->SetTarget( true, inRedrawHow );
	mCurrentSamplePane = inBox;
}


// ---------------------------------------------------------------------------
// 	GetTargetView
// ---------------------------------------------------------------------------

CDraggableTargetView *CIcon_EditorWindow::GetTargetView()
{
	return( mCurrentSamplePane );
}


// ---------------------------------------------------------------------------
// 	EstablishPort
// ---------------------------------------------------------------------------
// 	PowerPlant's EstablishPort() routine doesn't set the current GDevice.
// 	This is NASTY because the current port's color table doesn't match the
// 	current GDevice's color table and drawing sometimes doesn't take place.

Boolean
CIcon_EditorWindow::EstablishPort()
{
	if ( !mMacWindowP ) return( false );

	// This sets GDevice too
	UIconMisc::SetPort( GetMacPort() );
	return( true );
}


// ---------------------------------------------------------------------------
// 	UpdatePort
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::UpdatePort()
{
	StGWorldSaver	aSaver;
	
	// This sets GDevice too
	UIconMisc::SetPort( GetMacPort() );
	LWindow::UpdatePort();
}


// ---------------------------------------------------------------------------
// 	Min & Max routines
// ---------------------------------------------------------------------------

SInt32
CIcon_EditorWindow::GetMinImageHeight()
{
	return( mMinImageHeight );
}

SInt32
CIcon_EditorWindow::GetMaxImageHeight()
{
	return( mMaxImageHeight );
}

SInt32
CIcon_EditorWindow::GetMinImageWidth()
{
	return( mMinImageWidth );
}

SInt32
CIcon_EditorWindow::GetMaxImageWidth()
{
	return( mMaxImageWidth );
}


// ---------------------------------------------------------------------------
// 	GetZoomFactor
// ---------------------------------------------------------------------------

SInt32
CIcon_EditorWindow::GetZoomFactor( SInt32 inWidth, SInt32 inHeight, Boolean *outShowGrid )
{
	SInt32	maxSize = MAX( inWidth, inHeight );
	SInt32	result;
	
	if ( maxSize <= 16 )
		result = 12;
	else if ( maxSize <= 40 )
		result = 7;
	else if ( maxSize <= 64 )
		result = 4;
	else
		result = 1;

	if ( outShowGrid ) {
		// Only show grid if we're zooming (ugly otherwise)
		*outShowGrid = (result != 1);
	}
	
	return( result );
}


// ---------------------------------------------------------------------------
// 	ChangeImageSize
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::ChangeImageSize( SInt32 /*inWidth*/, SInt32 /*inHeight*/, Boolean /*inStretch*/ )
{
		// sub-classes do all the work here
}


// ---------------------------------------------------------------------------
// 	ImageSizeChangeUndone
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::ImageSizeChangeUndone( SInt32 /*inWidth*/, SInt32 /*inHeight*/ )
{
		// sub-classes do all the work here
}



// ---------------------------------------------------------------------------
// 	BecomeListenerTo
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::BecomeListenerTo( SInt32 inNumPanes, CDraggableTargetView **inList )
{
	for ( SInt32 count = 0; count < inNumPanes; count++ )
	{
		LBroadcaster	*theBroad = dynamic_cast<LBroadcaster*>( inList[count] );
		if ( theBroad )
			theBroad->AddListener( this );
	}
}


// ---------------------------------------------------------------------------
// 	GetSamplePaneCount
// ---------------------------------------------------------------------------

SInt32
CIcon_EditorWindow::GetSamplePaneCount()
{
	return( mNumSamplePanes );
}


// ---------------------------------------------------------------------------
// 	GetSamplePaneCount
// ---------------------------------------------------------------------------

CDraggableTargetView *
CIcon_EditorWindow::GetNthSamplePane( SInt32 inIndex )
{
	if ( (inIndex < 1) || (inIndex > mNumSamplePanes) )
		return( nil );
	
	return( mSamplePaneList[ inIndex - 1 ] );
}


// ---------------------------------------------------------------------------
// 	GetLockedFlag
// ---------------------------------------------------------------------------

Boolean
CIcon_EditorWindow::GetLockFlag()
{
	return( mLockedFlag );
}


// ---------------------------------------------------------------------------
// 	SetLockFlag
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::SetLockFlag( Boolean inFlag )
{
	if ( inFlag == mLockedFlag ) return;
	
	mLockedFlag = inFlag;
	
	// Enable/disable Drag&Drop to our target panes
	SInt32 				numSamplePanes = this->GetSamplePaneCount();
	CDraggableTargetView	*theTarget;
	
	for ( SInt32 count = 1; count <= numSamplePanes; count++ )
	{
		theTarget = this->GetNthSamplePane( count );
		if ( theTarget )
			theTarget->SetDropEnable( !inFlag );
	}
}


// ---------------------------------------------------------------------------
// 	GetLastAction
// ---------------------------------------------------------------------------
// 	Returns the previous CIconAction object (the one sitting in the undo stack).

CIconAction *CIcon_EditorWindow::GetLastAction()
{
	LAction		*lastAction = nil;
	
	// The previous action is an attachment to our view, so it will 
	// see this request and respond to it
	this->ProcessCommand( msg_GetLastCommand, &lastAction );
	if ( lastAction == nil ) return( nil );
	
	// The dynamic cast will fail if the last action was something other than
	// one of our paint actions (this shouldn't happen)
	CIconAction	*ourLastAction = dynamic_cast<CIconAction*>( lastAction );
	return( ourLastAction );
}


// ---------------------------------------------------------------------------
// 	SetTextAction
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::SetTextAction( CIconTextAction *inAction )
{
	mTextAction = inAction;
}



// ---------------------------------------------------------------------------
// 	GetTextTraits
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::GetTextTraits( struct TextTraitsRecord *outRec )
{
	*outRec = mTextTraits;
}


// ---------------------------------------------------------------------------
// 	InstallBitmap													[public]
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::InstallBitmap(Handle inHandle)
{
	StHandleLocker	lock(inHandle);
// 	mContentsView->SetBitmapHandle(inHandle);
	SetDirty(false);
}


// ---------------------------------------------------------------------------
// 	SetCoordsField												[public]
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::SetCoordsField(SInt16 inXCoord, SInt16 inYCoord)
{
}


// ---------------------------------------------------------------------------
// 	SaveAsResource												[public]
// ---------------------------------------------------------------------------

void 
CIcon_EditorWindow::SaveAsResource( CRezMap *inMap, ResIDT inResID  )
{
	// Subclasses should define
}


// ---------------------------------------------------------------------------
// 	ResizeWindowIfNeeded
// ---------------------------------------------------------------------------

void
CIcon_EditorWindow::ResizeWindowIfNeeded( SInt32 hMargin, SInt32 vMargin )
{
	SInt32		oldWidth, oldHeight;
	SInt32		newWidth, newHeight;
	
	SDimension16	oldSize;
	GetFrameSize( oldSize );
	oldWidth = oldSize.width;
	oldHeight = oldSize.height;
	
	// We do not resize vertically.
	GetContainedWidth( newWidth );
	newHeight = oldHeight;
	
	newWidth += hMargin;
	newHeight += vMargin;
	
	if ( (newWidth != oldWidth) || (newHeight != oldHeight) )
	{
		// Resize the view
		SInt32	dh = MAX( 0, newWidth - oldWidth );
		SInt32	dv = MAX( 0, newHeight - oldHeight );
		ResizeFrameBy( dh, dv, true );
		
		// Resize the window itself
		Rect	r;
		UIconMisc::GetWindowGlobalBounds( GetMacWindow(), r );
		r.right = r.left + newWidth;
		r.bottom = r.top + newHeight;
		DoSetBounds( r );
	}
}


// ---------------------------------------------------------------------------
// 	GetContainedWidth
// ---------------------------------------------------------------------------
// This is the sum of the widths of the left header (fixed), the encloser
// and the right header (samples container + outmargin).

void
CIcon_EditorWindow::GetContainedWidth(SInt32 &outWidth)
{
	SInt32			totalWidth = kLeftHeaderWidth;
	LPane *			thePane;
	SDimension16	frameSize;

	thePane = dynamic_cast<CIcon_EditorView *>(this->FindPaneByID(item_CanvasEncloser));
	ThrowIfNil_( thePane );
	thePane->GetFrameSize( frameSize );
	totalWidth += frameSize.width ;
	
	// If there is a samples view, add its width (only PICT editing windows
	// do not have one).
	thePane = dynamic_cast<CIcon_EditorView *>(this->FindPaneByID(item_IconSampleWell));
	if (thePane) {
		thePane->GetFrameSize( frameSize );
		totalWidth += frameSize.width ;
	} 

	totalWidth += kSampleOutMargin * 2 ;

	outWidth = totalWidth;
}

