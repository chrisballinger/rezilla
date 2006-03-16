// ===========================================================================
// CPickerView.cp					
// 
//                       Created: 2006-02-24 09:49:42
//             Last modification: 2006-03-16 11:16:41
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2006
// All rights reserved.
// ===========================================================================


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CPickerView.h"
#include "CPickerWindow.h"
#include "RezillaConstants.h"

#include <LStream.h>
#include <UAttachments.h>
#include <PP_Constants.h>

#include <Icons.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   CPickerView							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CPickerView::CPickerView(ResIDT inID)
	: LView()
{
	mIsSelected = false;
	
	// Use the resource ID as an ID for the PickerView
	mPaneID = inID;
	
	// Add an attachment to draw the border
	PenState	thePenState;
	RGBColor	theForeColor = Color_Black;
	RGBColor	theBackColor = Color_White;

	thePenState.pnLoc = Point_00;
	thePenState.pnSize.h = 1;
	thePenState.pnSize.v = 1;
	thePenState.pnMode = srcOr;
	AddAttachment( new LBorderAttachment(&thePenState, &theForeColor, &theBackColor, true) );

}


// ---------------------------------------------------------------------------
//     ~CPickerView							Destructor				  [public]
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
		LStr255 theLine("\p- ");

		::NumToString( (SInt32) inID, theString);
		theLine.Append(theString);
		theLine.Append("\p -");

		mIDField->SetDescriptor(theLine);
	} 
}


// ---------------------------------------------------------------------------
//   DrawSelf														  [public]
// ---------------------------------------------------------------------------

void
CPickerView::DrawSelf()
{
// 	mStampView->Draw(nil);
// 	mIDField->Draw(nil);
	
// 		// Draw a frame
// 	if (GetOwnerWindow()->GetSelectedStamp() == this) {
// 		
// 	} 
}


PP_End_Namespace_PowerPlant
