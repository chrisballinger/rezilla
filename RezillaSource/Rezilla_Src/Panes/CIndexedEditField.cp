// ===========================================================================
// CIndexedEditField.cp
// 
//                       Created: 2005-09-01 09:14:05
//             Last modification: 2005-09-02 07:23:45
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CIndexedEditField.h"
#include "RezillaConstants.h"

#include <LString.h>
#include <UKeyFilters.h>

// // Standard headers
// #include <string.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   CIndexedEditField							Stream Constructor		  [public]
// ---------------------------------------------------------------------------

CIndexedEditField::CIndexedEditField(
	LStream*	inStream)

	: LView(inStream)
{
	Str255 theString;
	
	*inStream >> mIndex;
	*inStream >> theString;
	
	Initialize(theString);
}


// ---------------------------------------------------------------------------
//   CIndexedEditField							Parameterized Constructor [public]
// ---------------------------------------------------------------------------

CIndexedEditField::CIndexedEditField(	
								const SPaneInfo& inPaneInfo,
								const SViewInfo& inViewInfo,
								UInt16 index,
								Str255 inString)

	: LView(inPaneInfo, inViewInfo)
{
	mIndex = index;
	Initialize(inString);
}


// ---------------------------------------------------------------------------
//   ~CIndexedEditField							Destructor				  [public]
// ---------------------------------------------------------------------------

CIndexedEditField::~CIndexedEditField()
{
}


// ---------------------------------------------------------------------------
//   Initialize
// ---------------------------------------------------------------------------
// 		PlaceInSuperImageAt(inPaneInfo.left, inPaneInfo.top, false);

void 
CIndexedEditField::Initialize(Str255 inString)
{
	SPaneInfo	pi;
	Str255		theString;
	Rect		frame;

	mSelected = false;

	CalcLocalFrameRect(frame);

	// Static field basic values
	pi.width			= kStrxIndexWidth;
	pi.height			= kStrxHeight - 2 * kStrxVertSep;
	pi.visible			= true;
	pi.enabled			= true;
	pi.bindings.left	= true;
	pi.bindings.top		= false;
	pi.bindings.right	= false;
	pi.bindings.bottom 	= false;
	pi.userCon			= 0;
	pi.left				= kStrxHorizSep;
	pi.top				= kStrxVertSep;
	pi.paneID			= 0;
	pi.superView		= this;

	::NumToString(mIndex + 1, theString);
	mStaticText = new LStaticText(pi, theString, 0);
	
	// Edit field basic values
	pi.left				+= kStrxIndexWidth + kStrxHorizSep;
	pi.width			= frame.right - pi.left - kStrxHorizSep;
	pi.bindings.right	= true;
	pi.paneID			= 1;
	
	mEditText = new LEditText(pi, this, inString, Txtr_MonacoNineDefault, msg_Nothing, 255, 0, 
							  UKeyFilters::SelectTEKeyFilter(keyFilter_PrintingChar));						  
	mEditText->SetDescriptor(inString);  
							  
}


// ---------------------------------------------------------------------------
//   FinishCreateSelf											[protected]
// ---------------------------------------------------------------------------

void
CIndexedEditField::FinishCreateSelf()
{
}



#pragma mark -

// ---------------------------------------------------------------------------
//   Click
// ---------------------------------------------------------------------------

void 
CIndexedEditField::Click(SMouseDownEvent &inMouseDown)
{
	// Check if a SubPane of this View is hit
	LPane * clickedPane = FindSubPaneHitBy(inMouseDown.wherePort.h,
											inMouseDown.wherePort.v);
	
	if (clickedPane != nil) {
			// SubPane is hit, let it respond to the click
			PaneIDT theID = clickedPane->GetPaneID();
			
			if ( theID == 0 || theID == PaneIDT_Unspecified ) {
				if (mSelected) {
// 					mOwnerWindow->SetSelectedListItem(NULL);
					mSelected = false;
					EraseBorder();
				} else {
// 					CTmplListItemView * selectedItem = mOwnerWindow->GetSelectedListItem();
// 					mOwnerWindow->SetSelectedListItem(this);
// 					mOwnerWindow->SwitchTarget(mOwnerWindow);
					mSelected = true;
					DrawBorder();
// 					if (selectedItem != NULL) {
// 						selectedItem->SetIsSelected(false);
// 						selectedItem->EraseBorder();
// 					}
				}
			} else {
				clickedPane->Click(inMouseDown);
			}
		} else {
		// No SubPane hit. Inherited function will process click on this view.
		LPane::Click(inMouseDown);
	}
	
}


// ---------------------------------------------------------------------------
//   HandleKeyPress												  [public]
// ---------------------------------------------------------------------------

Boolean
CIndexedEditField::HandleKeyPress(
	const EventRecord&	inKeyEvent)
{
	Boolean		keyHandled = true;

	if (mSelected) {
		UInt16	theChar = (UInt16) (inKeyEvent.message & charCodeMask);

		if ( (theChar == char_Enter) || (theChar == char_Return) ) {
// 			SwapPanes();
		} else {
			keyHandled = mEditText->HandleKeyPress(inKeyEvent);
		}
	} 

	return keyHandled;
}


// ---------------------------------------------------------------------------
//	¥ GetDescriptor													  [public]
// ---------------------------------------------------------------------------

StringPtr
CIndexedEditField::GetDescriptor(
	Str255	outDescriptor) const
{
	mEditText->GetDescriptor(outDescriptor);
	return outDescriptor;
}


// ---------------------------------------------------------------------------
//	¥ SetDescriptor													  [public]
// ---------------------------------------------------------------------------

void
CIndexedEditField::SetDescriptor(
	ConstStringPtr	inDescriptor)
{
	mEditText->SetDescriptor(inDescriptor);
}


// ---------------------------------------------------------------------------
//	¥ DrawBorder
// ---------------------------------------------------------------------------
//  Border around a CIndexedEditField is outset from the interior by 1 pixel.
// 	::MacFrameRect(&frame);

void
CIndexedEditField::DrawBorder()
{
	StColorState	saveColors;			// Preserve color state
	StGrafPortSaver	savePort;
	Rect			frame;
	RGBColor		redColor = Color_Red;
	
	FocusDraw();
	
	CalcLocalFrameRect(frame);
	::PenNormal();
	::PenSize(2, 2);
	
	// Draw border around the view
	::RGBForeColor(&redColor);
	::FrameRoundRect( &frame, 4, 4 );

	// Validate the drawn region so that it is not erased by the next update
	StRegion	focusRgn(frame);
	StRegion	borderRgn(frame);
	focusRgn.InsetBy(2, 2);
	borderRgn -= focusRgn;
	DontRefreshRgn(borderRgn);
}


// ---------------------------------------------------------------------------
//	¥ EraseBorder
// ---------------------------------------------------------------------------
//  Ask for a Refresh to erase the border around the list item.
// 	::DrawThemeFocusRegion(StRegion(frame), true);

void
CIndexedEditField::EraseBorder()
{
	StColorState	saveColors;			// Preserve color state
	StGrafPortSaver	savePort;
	Rect			frame;
	
	FocusDraw();
	
	CalcLocalFrameRect(frame);
	RefreshRect(frame);
}


PP_End_Namespace_PowerPlant
