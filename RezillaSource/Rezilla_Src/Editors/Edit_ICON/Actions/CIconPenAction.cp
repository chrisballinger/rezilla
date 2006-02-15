// ===========================================================================
// CIconPenAction.cp
//                       Created: 2004-12-11 18:52:29
//             Last modification: 2004-12-22 17:54:12
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// ===========================================================================

#include "RezillaConstants.h"
#include "CIconActions.h"
#include "CIcon_EditorView.h"
#include "COffscreen.h"
#include "UColorUtils.h"


// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------

CIconPenAction::CIconPenAction( const SPaintAction &inAction ) : 
		CIconTrackingPaintAction( inAction, index_UndoPen )
{
	this->ThrowIfFileLocked();
	mLastRowPainted = mLastColPainted = -1;			// nothing painted yet
}


// ---------------------------------------------------------------------------
// 	Destructor
// ---------------------------------------------------------------------------

CIconPenAction::~CIconPenAction()
{
}


// ---------------------------------------------------------------------------
// 	MouseInitial
// 	
// 	Notes:
// 	Determines whether we will be drawing in the foreground or background
// 	  color.
// ---------------------------------------------------------------------------

void
CIconPenAction::MouseInitial( const SMouseDownEvent &inEvent, SInt32 /*newCol*/, SInt32 /*newRow*/ )
{
	if ( inEvent.macEvent.modifiers & shiftKey )
		mSnapTo.SetAngle( CSnapTo::kSnapTo90 );
	else
		mSnapTo.SetAngle( CSnapTo::kDontSnap );

	/*
		if pen hits a different color, use the forecolor
		if pen hits the same color, use background color
	*/
	COffscreen		*theImageBuffer = mSettings.currentBuffer;
	Color32			colorHit = theImageBuffer->GetPixelColor( mMouseDownCol, mMouseDownRow );

		// do all compares in rgb space since 2 colors in table could be the same
	if ( UColorUtils::EqualColor32( colorHit, mSettings.theForeColor ) )
		mPenColor = mSettings.theBackColor;
	else
		mPenColor = mSettings.theForeColor;

	mBufferCols = theImageBuffer->GetWidth();
	mBufferRows = theImageBuffer->GetHeight();
}


// ---------------------------------------------------------------------------
// 	MouseStillDown
// ---------------------------------------------------------------------------

void
CIconPenAction::MouseStillDown( const SMouseDownEvent &, 
											Point /*prevMousePt*/, Point /*newMousePt*/,
											SInt32 prevCol, SInt32 prevRow,
											SInt32 newCol, SInt32 newRow )
{
	if ( (newCol == prevCol) && (newRow == prevRow) )
		return;
	
	COffscreen	*theImageBuffer = mSettings.currentBuffer;
	
	if ( (newCol < 0) || (newCol >= mBufferCols) ||
	     (newRow < 0) || (newRow >= mBufferRows) )			// offscreen ?
	{
		mLastRowPainted = -1;
		mLastColPainted = -1;
	}
	else
	{
		if ( (mLastRowPainted == -1) || (mLastColPainted == -1) )
		{
			mLastRowPainted = newRow;
			mLastColPainted = newCol;
		}

			// draw the pen stroke into the buffer (as a line)
		theImageBuffer->BeginDrawing();
		theImageBuffer->SetForeColor( mPenColor );
		//	::PmForeColor( mPenColorIndex );
			::MoveTo( mLastColPainted, mLastRowPainted );
			::LineTo( newCol, newRow );
		theImageBuffer->EndDrawing();
		
			// copy the buffer to the screen (only the portion drawn for speed)
		Rect	subRect;
		subRect.left = MIN( mLastColPainted, newCol );
		subRect.right = 1 + MAX( mLastColPainted, newCol );
		subRect.top = MIN( mLastRowPainted, newRow );
		subRect.bottom = 1 + MAX( mLastRowPainted, newRow );
		
		mSettings.theCanvas->DrawFrom( theImageBuffer, &subRect);

		mLastRowPainted = newRow;
		mLastColPainted = newCol;
	}
}

