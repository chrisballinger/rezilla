// ===========================================================================
// 	CTmplListItemView.cp
// 
//                       Created: 2004-06-27 14:13:08
//             Last modification: 2005-01-08 11:46:16
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2004, 2005
// All rights reserved.
// ===========================================================================

#ifdef PowerPlant_PCH
#include PowerPlant_PCH
#endif

#include "CTmplListItemView.h"
#include "RezillaConstants.h"
#include "CTmplListButton.h"
#include "CTmplEditorWindow.h"

PP_Begin_Namespace_PowerPlant



// ---------------------------------------------------------------------------
//   CTmplListItemView						Parameterized Constructor [public]
// ---------------------------------------------------------------------------

CTmplListItemView::CTmplListItemView(
				 const SPaneInfo& inPaneInfo,
				 const SViewInfo& inViewInfo,
				 CTmplEditorWindow * inOwnerWindow,
				 Boolean inPrimary)
	
	: LTextGroupBox(inPaneInfo, inViewInfo, inPrimary)
{
	mOwnerWindow = inOwnerWindow;
	InitList();
}


// ---------------------------------------------------------------------------
//   CTmplListItemView						Stream Constructor		  [public]
// ---------------------------------------------------------------------------

CTmplListItemView::CTmplListItemView(
	LStream*	inStream)
	
	: LTextGroupBox(inStream)
{
	InitList();
}


// ---------------------------------------------------------------------------
//     ~CTmplListItemView					Destructor				  [public]
// ---------------------------------------------------------------------------
//

CTmplListItemView::~CTmplListItemView()
{
}


#pragma mark -

// ---------------------------------------------------------------------------
//   InitList												  		[private]
// ---------------------------------------------------------------------------

void
CTmplListItemView::InitList()
{
	mPrevItem = nil;
	mNextItem = nil;
	mMinusButton = nil;
	mIsSelected = false;
}


// ---------------------------------------------------------------------------
//   Click
// ---------------------------------------------------------------------------
//	Handle a click inside a CTmplListItemView

void
CTmplListItemView::Click(
	SMouseDownEvent	&inMouseDown)
{
	// Check if a SubPane of this View is hit
	LPane * clickedPane = FindSubPaneHitBy(inMouseDown.wherePort.h,
											inMouseDown.wherePort.v);
	
	if (clickedPane != nil) {
		// Check if it is a nested list item
		if (dynamic_cast<CTmplListItemView *>(clickedPane) != NULL) {
			clickedPane->Click(inMouseDown);
		} else {
			// SubPane is hit, let it respond to the click
			PaneIDT theID = clickedPane->GetPaneID();
			
			if ( (theID == 0 || theID == PaneIDT_Unspecified) &&
				dynamic_cast<LView *>(clickedPane) == NULL) {
				if (mIsSelected) {
					mOwnerWindow->SetSelectedListItem(NULL);
					mIsSelected = false;
					EraseBorder();
				} else {
					CTmplListItemView * selectedItem = mOwnerWindow->GetSelectedListItem();
					mOwnerWindow->SetSelectedListItem(this);
					mOwnerWindow->SwitchTarget(mOwnerWindow);
					mIsSelected = true;
					DrawBorder();
					if (selectedItem != NULL) {
						selectedItem->SetIsSelected(false);
						selectedItem->EraseBorder();
					}
				}
			} else {
				clickedPane->Click(inMouseDown);
			}
		}
	} else {
		// No SubPane hit. Inherited function will process click on this view.
		LPane::Click(inMouseDown);
	}
}


// ---------------------------------------------------------------------------
//   DrawBorder
// ---------------------------------------------------------------------------
//  Border around a CTmplListItemView is outset from the interior by 1 pixel.
// 	::MacFrameRect(&frame);

void
CTmplListItemView::DrawBorder()
{
	StColorState	saveColors;			// Preserve color state
	StGrafPortSaver	savePort;
	Rect			frame;
	RGBColor		redColor = Color_Red;
	
	FocusDraw();
	
	CalcLocalFrameRect(frame);
	::PenNormal();
	::PenSize(3, 3);
	
	// Draw border around the view
	::RGBForeColor(&redColor);
	::FrameRoundRect( &frame, 4, 4 );

	// Validate the drawn region so that it is not erased by the next update
	StRegion	focusRgn(frame);
	StRegion	borderRgn(frame);
	focusRgn.InsetBy(3, 3);
	borderRgn -= focusRgn;
	DontRefreshRgn(borderRgn);
}


// ---------------------------------------------------------------------------
//   EraseBorder
// ---------------------------------------------------------------------------
//  Ask for a Refresh to erase the border around the list item.
// 	::DrawThemeFocusRegion(StRegion(frame), true);

void
CTmplListItemView::EraseBorder()
{
	StColorState	saveColors;			// Preserve color state
	StGrafPortSaver	savePort;
	Rect			frame;
	
	FocusDraw();
	
	CalcLocalFrameRect(frame);
	RefreshRect(frame);
}


// ---------------------------------------------------------------------------
//   Draw
// ---------------------------------------------------------------------------

void
CTmplListItemView::Draw(
	RgnHandle	inSuperDrawRgnH)

{
	UInt32 count = CTmplEditorWindow::CountAllSubPanes(this);
	
	LTextGroupBox::Draw(inSuperDrawRgnH);
}


PP_End_Namespace_PowerPlant
