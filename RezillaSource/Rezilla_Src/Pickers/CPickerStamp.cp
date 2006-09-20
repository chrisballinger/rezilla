// ===========================================================================
// CPickerStamp.cp					
// 
//                       Created: 2006-02-24 09:49:42
//             Last modification: 2006-09-20 08:35:48
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2006
// All rights reserved.
// ===========================================================================


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CPickerStamp.h"
#include "CPickerWindow.h"
#include "RezillaConstants.h"

#include <LStream.h>
#include <PP_Constants.h>

#include <Icons.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   CPickerStamp							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CPickerStamp::CPickerStamp(
	   CPickerView *	inParent,
	   const SPaneInfo&	inPaneInfo,
	   const SViewInfo&	inViewInfo)
	: LView(inPaneInfo, inViewInfo)
{
	mParent = inParent;
}


// ---------------------------------------------------------------------------
//     ~CPickerStamp							Destructor				  [public]
// ---------------------------------------------------------------------------

CPickerStamp::~CPickerStamp()
{
}


// // ---------------------------------------------------------------------------
// //   InitPickerStamp
// // ---------------------------------------------------------------------------
// 
// void 
// CPickerStamp::InitPickerStamp(SInt16 inWidth, SInt16 inHeight, ResIDT inID)
// {
// 	ResizeFrameTo(inWidth, inHeight, false);
// 	ResizeImageTo(inWidth, inHeight, false);
// }


// ---------------------------------------------------------------------------
// 	ClickSelf
// ---------------------------------------------------------------------------

void
CPickerStamp::ClickSelf( const SMouseDownEvent & inEvent)
{
	GetSuperView()->ClickSelf(inEvent);
}


// ---------------------------------------------------------------------------
//   DrawSelf														  [public]
// ---------------------------------------------------------------------------
// // 		OSErr 
// // 		PlotIconID(
// // 		  const Rect *        theRect,
// // 		  IconAlignmentType   align,
// // 		  IconTransformType   transform,
// // 		  SInt16              theResID)
// // 		OSErr 
// // 		PlotIconHandle(
// // 		  const Rect *        theRect,
// // 		  IconAlignmentType   align,
// // 		  IconTransformType   transform,
// // 		  Handle              theIcon)
// // 		  extern void 
// // 		PlotIcon(
// // 		  const Rect *  theRect,
// // 		  Handle        theIcon)
// // 		  OSErr 
// // 		PlotSICNHandle(
// // 		  const Rect *        theRect,
// // 		  IconAlignmentType   align,
// // 		  IconTransformType   transform,
// // 		  Handle              theSICN)
// // 		OSErr 
// // 		PlotCIconHandle(
// // 		  const Rect *        theRect,
// // 		  IconAlignmentType   align,
// // 		  IconTransformType   transform,
// // 		  CIconHandle         theCIcon)
// 			if (mGraphicsType == ResType_IconList) {
// 					if (mEnabled == triState_On) {
// 						::PlotIconID(&frame, kAlignNone, kTransformNone, inGraphicID);
// 					} else {
// 						::PlotIconID(&frame, kAlignNone, kTransformDisabled, inGraphicID);
// 					}
// 
// 				} else if (mGraphicsType == ResType_Picture) {
// 					PicHandle	macPictureH = ::GetPicture(inGraphicID);
// 					if (macPictureH != nil) {
// 						::DrawPicture(macPictureH, &frame);
// 					}
// 
// 				} else if (mGraphicsType == ResType_Icon) {
// 					Handle	iconHandle = ::GetIcon(inGraphicID);
// 					if (iconHandle != nil) {
// 						::PlotIcon(&frame, iconHandle);
// 					}
// 				}

void
CPickerStamp::DrawSelf()
{
	short theID = GetSuperView()->GetPaneID();
	Rect	frame;
	CalcLocalFrameRect(frame);
	StColorPenState::Normalize();
	
// 	::PlotIconID(&frame, kAlignNone, kTransformNone, inGraphicID);
// 	::PlotIconID(&frame, kAlignNone, kTransformDisabled, inGraphicID);
	
}


PP_End_Namespace_PowerPlant
