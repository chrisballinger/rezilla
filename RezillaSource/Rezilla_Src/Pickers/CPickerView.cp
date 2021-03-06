// ===========================================================================
// CPickerView.cp					
// 
//                       Created: 2006-02-24 09:49:42
//             Last modification: 2006-10-06 08:54:16
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2006
// All rights reserved.
// ===========================================================================
// All the picker rectangles are automatically framed by an LBorderAttachment
// which is attached to them in the constructor.
// The CPickerView class is not instanciated directly: it is a base class
// for the TPickerView template class.


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CPickerView.h"
#include "CPickerWindow.h"
#include "RezillaConstants.h"

#include <LStream.h>
#include <UAttachments.h>
#include <PP_Constants.h>

#ifndef __MACH__
#include <Icons.h>
#endif

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   CPickerView								 Constructor		  [public]
// ---------------------------------------------------------------------------

CPickerView::CPickerView(ResIDT inID)
	: LView()
{	
	// Use the resource ID as paneID for the PickerView
	mPaneID = inID;
	
	// Add an attachment to draw the border
	AddAttachment( new LBorderAttachment() );
}


// ---------------------------------------------------------------------------
//   ~CPickerView							Destructor				  [public]
// ---------------------------------------------------------------------------

CPickerView::~CPickerView()
{
}


// ---------------------------------------------------------------------------
//   SetIDField														  [public]
// ---------------------------------------------------------------------------

void
CPickerView::SetIDField(ResIDT	inID)
{
	if (mIDField != nil) {
		Str255 theString;
		::NumToString( (SInt32) inID, theString);
		mIDField->SetDescriptor(theString);
	} 
}


// ---------------------------------------------------------------------------
// 	ClickSelf
// ---------------------------------------------------------------------------

void
CPickerView::ClickSelf( const SMouseDownEvent & )
{
	// Check if it is a double-click
	if (LPane::GetClickCount() > 1) {
		mOwnerWindow->ListenToMessage(msg_PickerViewDoubleClick, this);
		return;
	}
	
	mOwnerWindow->ListenToMessage(msg_PickerViewSingleClick, this);
}


// ---------------------------------------------------------------------------
//   IsSelected
// ---------------------------------------------------------------------------

Boolean
CPickerView::IsSelected() { 
	Boolean result = false;
	
	if (mOwnerWindow) {
		result = (mOwnerWindow->GetSelectedView() == this);
	} 
	return result;
}


// ---------------------------------------------------------------------------
//   DrawBorder
// ---------------------------------------------------------------------------
//  Border around a CPickerView is outset from the interior by 1 pixel

void
CPickerView::DrawBorder(Boolean isSelected)
{
	StColorState	saveColors;			// Preserve color state
	StGrafPortSaver	savePort;
	Rect			frame;
	RGBColor		redColor = Color_Red;
		
	FocusDraw();
	CalcLocalFrameRect(frame);
	
	if (isSelected) {
		::PenNormal();
		::PenSize(2, 2);
		
		// Draw border around the view
		::RGBForeColor(&redColor);
		::FrameRoundRect( &frame, 4, 4 );

		// Validate the drawn region so that it is not erased by the next update
		StRegion	focusRgn(frame);
		StRegion	borderRgn(frame);
		focusRgn.InsetBy(3, 3);
		borderRgn -= focusRgn;
		DontRefreshRgn(borderRgn);
	} else {
		RefreshRect(frame);
	}
	
}


// // ---------------------------------------------------------------------------
// //   DrawSelf														  [public]
// // ---------------------------------------------------------------------------
// 
// void
// CPickerView::DrawSelf()
// {
// }


// ---------------------------------------------------------------------------
//   EraseStamp
// ---------------------------------------------------------------------------

void
CPickerView::EraseStamp()
{
	Rect	frame;
	LView *	theStamp = dynamic_cast<LView *>(this->FindPaneByID(item_PickerStampView));
	
	if (theStamp) {
		theStamp->CalcPortFrameRect(frame);
		::EraseRect(&frame);
	} 
}



PP_End_Namespace_PowerPlant
