// ===========================================================================
// 	CPattern_PickerStamp.cp
// 
//                       Created : 2006-09-20 18:39:04
//             Last modification : 2006-09-21 09:32:42
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@users.sourceforge.net>
// www : <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2006
// All rights reserved.
// ===========================================================================
// The stamp is the part of a picker view where the image is drawn. The
// StampSize method returns the dimensions of this drawing area.


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CPattern_PickerStamp.h"
#include "CPickerView.h"
#include "CPickerWindow.h"
#include "RezillaConstants.h"
#include "UResources.h"

#include <Icons.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   CPattern_PickerStamp							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CPattern_PickerStamp::CPattern_PickerStamp(
									CPickerView *		inParent,
									const SPaneInfo&	inPaneInfo,
									const SViewInfo&	inViewInfo)
	: CPickerStamp(inParent, inPaneInfo, inViewInfo)
{
}


// ---------------------------------------------------------------------------
//   ~CPattern_PickerStamp							Destructor				  [public]
// ---------------------------------------------------------------------------

CPattern_PickerStamp::~CPattern_PickerStamp()
{
}


// ---------------------------------------------------------------------------
//   StampSize														  [public]
// ---------------------------------------------------------------------------

void
CPattern_PickerStamp::StampSize(ResType inType, SInt16 &outWidth, SInt16 &outHeight)
{
#pragma unused(inType)
	outWidth = 32;
	outHeight = 32;
}


// ---------------------------------------------------------------------------
//   DrawSelf														  [public]
// ---------------------------------------------------------------------------
// ImgType_PixPat		'ppat'
// ImgType_Pattern		'PAT '
// ImgType_PatternSuite	'PAT#'

void
CPattern_PickerStamp::DrawSelf()
{
	// The resID is the paneID of the PickerView
	ResIDT		theID = mParent->GetPaneID();
	short		theRefNum = mParent->GetUserCon();
	ResType		theType = mParent->GetOwnerWindow()->GetType();
	Pattern		thePattern;
	
	if (theRefNum != kResFileNotOpened) {
		Rect	frame;
		Handle	thePatternH = NULL;
		StRezRefSaver saver(theRefNum);
		
		FocusDraw();
		CalcLocalFrameRect(frame);
		
		switch (theType) {
			case ImgType_PixPat: {
				PixPatHandle thePixpatH = ::GetPixPat(theID);
				if (thePixpatH) {
					::FillCRect(&frame, thePixpatH);
					::DisposePixPat(thePixpatH);
				} 
			}
			break;
			
			case ImgType_Pattern: {
				thePatternH = ::Get1Resource(theType, theID);
				::HandToHand(&thePatternH);
				if (thePatternH && ::GetHandleSize(thePatternH) == 8) {
					thePattern = **(Pattern**)thePatternH;
					::PenPat(&thePattern);
					::PaintRect(&frame);
					::PenNormal();
				} 				
			}
			break;
			
			case ImgType_PatternSuite: {
				Handle theResHandle = NULL;
				thePatternH = ::NewHandleClear(8);
				theResHandle = ::Get1Resource(theType, theID);
				::HandToHand(&theResHandle);
				if (thePatternH && theResHandle) {
					if ( ::GetHandleSize(theResHandle) >= 10 ) {
						// The first two bytes are the list count
						::BlockMoveData(*theResHandle + 2, *thePatternH, 8);
					} 
					thePattern = **(Pattern**)thePatternH;
					::PenPat(&thePattern);
					::PaintRect(&frame);
					::PenNormal();
				}
				if (theResHandle) ::DisposeHandle(theResHandle);
			}
			break;
						
		}
		
		if (thePatternH != NULL) ::DisposeHandle(thePatternH);

	}
}


PP_End_Namespace_PowerPlant
