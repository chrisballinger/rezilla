// ===========================================================================
// CIcon_EditorWindow.h
// 
//                       Created: 2004-12-10 17:23:05
//             Last modification: 2006-11-17 13:27:30
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2004-2006
// All rights reserved.
// ===========================================================================
// mScratchBuffer: this should be static since we only need one for all 
// windows.

#ifndef _H_CIcon_EditorWindow
#define _H_CIcon_EditorWindow
#pragma once

#include "CEditorWindow.h"
#include "UResources.h"
#include "RezillaConstants.h"

#include <LPane.h>
#include <LView.h>
#include <LBroadcaster.h>
#include <LPeriodical.h>

class CColorCursorCache;
class CColorPane;
class CColorTableChoice;
class CDraggableTargetView;
class CIconSelection;
class CIconTextAction;
class CIcon_EditorDoc;
class CIcon_EditorView;
class COffscreen;
class CPatternPane;
class CRezMap;
class CSharedPalette;
class LMenu;
class LPane;
class LPopupButton;
class LStaticText;
class CIconAction;


class CIcon_EditorWindow : public CEditorWindow, public LBroadcaster, public LPeriodical {
public:
	enum { class_ID = FOUR_CHAR_CODE('ICNW') };

							CIcon_EditorWindow();
							CIcon_EditorWindow( const SWindowInfo &inWindowInfo );
							CIcon_EditorWindow( ResIDT inWINDid,
								UInt32 inAttributes, LCommander *inSuperCommander );
							CIcon_EditorWindow( LStream *inStream );
							~CIcon_EditorWindow();

	static CIcon_EditorWindow *	CreatePaintStream( LStream *inStream );

	virtual void				SetImage( COffscreen *, SInt32 = resize_None,
											RedrawOptions = redraw_Later );
											
	// Getting our buffers
	virtual COffscreen *		GetImageBuffer();
	virtual COffscreen *		GetScratchBuffer();
	virtual COffscreen *		GetUndoBuffer();
	virtual COffscreen *		GetCombinedBuffer();

	// Setting our buffers -- these are low-level routines not generally used
	virtual void				SetRawImageBuffer( COffscreen * );
	virtual void				SetRawScratchBuffer( COffscreen * );
	virtual void				SetRawUndoBuffer( COffscreen * );

	// Getting our sample panes
	virtual SInt32				GetSamplePaneCount();
	virtual CDraggableTargetView *GetNthSamplePane( SInt32 index ); // 1..n

	// Misc flags
	virtual void				RedrawSampleView( Rect *r = nil );

	// Events
	virtual Boolean 			HandleKeyPress( const EventRecord &inKeyEvent );
	virtual void				ActivateSelf();
	virtual void				DeactivateSelf();

	// Events for paint palette
	virtual void				AdjustCursorInCanvas( Point, const EventRecord & );
	virtual void				HandleMouseDownInCanvas( const SMouseDownEvent & );
	virtual void				HandleCanvasDraw();
		
	// Undo/redo
	virtual void				CopyToUndo();
	virtual void				SwapUndoState();

	// Commands & messages
	virtual void				ListenToMessage(MessageT inMessage, void *ioParam);
	virtual Boolean				ObeyCommand( CommandT, void * );
	virtual void 				FindCommandStatus(
										CommandT			inCommand,
										Boolean&			outEnabled,
										Boolean&			outUsesMark,
										UInt16&				outMark,
										Str255				outName);
	virtual CIconAction *			GetLastAction();
	virtual void				SetTextAction( CIconTextAction * = nil );
	virtual void				GetTextTraits( struct TextTraitsRecord * );
	//virtual void				SetTextTraits( struct TextTraitsRecord * );	

	// Selection
	virtual void				SelectAll();
	virtual void				SelectNone();
	virtual void				CommitSelection();
	virtual void				EraseAreaUnderSelection();
	virtual void				SetSelection( const Rect &r, Boolean toLasso = false );
	virtual void				SetSelection( RgnHandle, Boolean toLasso = false );
	virtual void				SpendTime( const EventRecord &inMacEvent );
	virtual void				NudgeSelection( SInt32 dh, SInt32 dv );
	virtual Boolean				CanvasPointInSelection( Point canvasPt );

	// Target box
	virtual void				SetTargetView( CDraggableTargetView *, RedrawOptions = redraw_Later );
	virtual CDraggableTargetView *GetTargetView();

	void						SelectTargetView(ResType inType);
	
	// Misc
	virtual void				ChangeTool( OSType toWhat );
	
// 	// Pure Virtual. Concrete subclasses must override
	virtual void				SaveAsResource( CRezMap *inMap, ResIDT inResID ) /* = 0 */;
	
	virtual Boolean				GetLockFlag();
	virtual void				SetLockFlag( Boolean );
		
	// Resizing	
	virtual SInt32				GetMinImageHeight();
	virtual SInt32				GetMaxImageHeight();
	virtual SInt32				GetMinImageWidth();
	virtual SInt32				GetMaxImageWidth();

	virtual void				ChangeImageSize( SInt32 inWidth, SInt32 inHeight, Boolean inStretch );
	virtual void				ImageSizeChangeUndone( SInt32 inWidth, SInt32 inHeight );
		
	virtual void				ResizeWindowIfNeeded(SInt32 hMargin = 0, SInt32 vMargin = 0);
	virtual void				GetContainedDimensions(SInt32 &outWidth, SInt32 &outHeight);

	virtual SInt32				GetZoomFactor( SInt32 inImageWidth, SInt32 inImageHeight, Boolean *outShowGrid );

	// Fixes for bugs in PowerPlant when working with GWorlds
	virtual void				UpdatePort();
	virtual Boolean				EstablishPort();
	
	void						SetCoordsField(SInt16 inXCoord, SInt16 inYCoord);

	CIcon_EditorView *			GetContentsView() const { return mContentsView;}

protected:
	CIcon_EditorView *			mContentsView;
	LStaticText *				mCoordsField;

	Boolean						mLockedFlag;
	RgnHandle					mSpareRgn;
	OSType						mCurrentTool;
	OSType						mPreviousTool;
	Color32						mForeColor,
								mBackColor;
	CColorPane					*mColorPane, 
								*mBackColorPane;
	Boolean						mPrefersIconColors;	// true for icons, false for PICTs & others
	Pattern						mCurrentPattern;
	CPatternPane				*mPatternPane;
	CIcon_EditorView			*mCanvas;
	LPane						*mSampleWell;
	COffscreen					*mCurrentImage,
								*mUndoBuffer;
	CIconSelection				*mCurrentSelection,
								*mUndoSelection;
	TextTraitsRecord			mTextTraits;
	CIconTextAction				*mTextAction;
	CSharedPalette				*mSharedPalette;
	CColorTableChoice			*mColorTableChoice;
	CDraggableTargetView		*mCurrentSamplePane;
	CDraggableTargetView		*mSamplePaneList[ kMaxIconSamplePanes ];
	SInt32						mNumSamplePanes;
	static LMenu				*sIconActionsMenu, 
								*sIconColorsMenu, 
								*sIconFontMenu, 
								*sIconStyleMenu;
	Boolean						mWindowIsActive;
	// Resizing
	Boolean						mAllowImageResizing;
	SInt32						mMinImageWidth,
								mMaxImageWidth;
	SInt32						mMinImageHeight,
								mMaxImageHeight;
								
	static CColorCursorCache	*sColorCursorCache;
	static SInt32				sNumPaintWindows;
	COffscreen					*mScratchBuffer;
	
	static LWindow *			CreatePaintWindow( ResIDT inWindowID );

	// Event handling		
	virtual void				HandleToolClick(PaneIDT inPaneID);
	virtual void				HandleToolDoubleClick( LPane *thePane );
	virtual void				ForceBlackAndWhite();
	virtual void				SwapColors();
	
	virtual CIconAction *		CreateNewAction( OSType inActionType, void *ioParam = nil );
	virtual void				GetActionSettings( struct SPaintAction * );
	virtual void				EraseAll();
	
	// Misc
	virtual void				ResetPatternPaneColors( RedrawOptions = redraw_Later );
	virtual void				PutOnDuty(LCommander *inNewTarget);
	virtual void				TakeOffDuty();
	virtual void				ThrowIfInvalidDepth( SInt32 inDepth );
	virtual void				RemovePaintMenus();
	virtual void				BecomeListenerTo( SInt32 inCount, CDraggableTargetView **inList );

	virtual void				FinishCreateSelf();
	
	void					DebugPortSelf();

private:
	virtual void		Initialize();
	virtual void		RebuildTitle();
};


#endif // _H_CIcon_EditorWindow
