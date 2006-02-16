// ===========================================================================
// CColorWell.cp
// 
//                       Created: 2004-08-20 12:37:09
//             Last modification: 2004-11-05 22:46:52
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes, 2004
// All rights reserved.
// ===========================================================================

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CColorWell.h"
#include "UDrawingState.h"


PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   CColorWell							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CColorWell::CColorWell()
{
	mMessage = 0;
	mFramed = true;
}


// ---------------------------------------------------------------------------
//   CColorWell							Copy Constructor		  [public]
// ---------------------------------------------------------------------------

CColorWell::CColorWell(
	const CColorWell&	inOriginal)
: LPane(inOriginal)
{
	mMessage = inOriginal.mMessage;
	mFramed = inOriginal.mFramed;
}


// ---------------------------------------------------------------------------
//   CColorWell							Parameterized Constructor [public]
// ---------------------------------------------------------------------------

CColorWell::CColorWell(	const SPaneInfo &inPaneInfo, 
					   RGBColor * inColor,
					   MessageT inMessage)
: LPane(inPaneInfo)
{
	mMessage = inMessage;
	mFramed = true;
	
	SetColor(*inColor);
	
	mPenState.pnLoc = Point_00;
	mPenState.pnSize.h = 1;
	mPenState.pnSize.v = 1;
	mPenState.pnMode = patCopy;
	UQDGlobals::GetBlackPat(&mPenState.pnPat);
}


// ---------------------------------------------------------------------------
//   CColorWell							Stream Constructor		  [public]
// ---------------------------------------------------------------------------

CColorWell::CColorWell(
	LStream*	inStream)
: LPane(inStream)
{
	*inStream >> mColor.red;
	*inStream >> mColor.green;
	*inStream >> mColor.blue;
	*inStream >> mMessage;
	*inStream >> mFramed;

	mPenState.pnLoc = Point_00;
	mPenState.pnSize.h = 1;
	mPenState.pnSize.v = 1;
	mPenState.pnMode = patCopy;
}


// ---------------------------------------------------------------------------
//     ~CColorWell							Destructor				  [public]
// ---------------------------------------------------------------------------

CColorWell::~CColorWell()
{}


// ---------------------------------------------------------------------------
//   FinishCreateSelf
// ---------------------------------------------------------------------------

void
CColorWell::FinishCreateSelf()
{
}

#pragma mark -

// ---------------------------------------------------------------------------
//   ClickSelf
// ---------------------------------------------------------------------------
//	Respond to Click inside this Pane

void
CColorWell::ClickSelf(
	const SMouseDownEvent&	/* inMouseDown */)
{
	if (PickRGBColor(&mColor)) {
		BroadcastMessage(mMessage, &mColor);
	} 
	
	Refresh();
}


// ---------------------------------------------------------------------------
//   DrawSelf
// ---------------------------------------------------------------------------
//	Draw contents of Pane

void
CColorWell::DrawSelf()
{
	StColorPenState	savePenState;		// Will save and restore pen state
	Rect	frame;
	CalcLocalFrameRect(frame);

	//		::PenNormal();
	::SetPenState(&mPenState);
	::RGBForeColor(&mColor);
	::RGBBackColor(&mColor);

	::MacInsetRect(&frame, mPenState.pnSize.h, mPenState.pnSize.v);
	::PaintRect(&frame);
	
	if (mFramed) {
		::RGBForeColor(&Color_Black);
		::MacFrameRect(&frame);
	} 
}


// ---------------------------------------------------------------------------
//   GetColor														  [public]
// ---------------------------------------------------------------------------

void
CColorWell::GetColor(RGBColor & ioColor)
{
	ioColor.red = mColor.red;
	ioColor.green = mColor.green;
	ioColor.blue = mColor.blue;
}


// ---------------------------------------------------------------------------
//   SetColor														  [public]
// ---------------------------------------------------------------------------

void
CColorWell::SetColor(RGBColor inColor)
{
	mColor.red = inColor.red;
	mColor.green = inColor.green;
	mColor.blue = inColor.blue;
}


// ---------------------------------------------------------------------------
//   GetDescriptor													  [public]
// ---------------------------------------------------------------------------

StringPtr
CColorWell::GetDescriptor(
	Str255	outDescriptor) const
{
	outDescriptor[0] = 0;
	return outDescriptor;
}


// ---------------------------------------------------------------------------
//   SetDescriptor													  [public]
// ---------------------------------------------------------------------------

void
CColorWell::SetDescriptor(
	ConstStringPtr	/* inDescriptor */)
{
}


// ---------------------------------------------------------------------------
//   PickRGBColor											[static]
// ---------------------------------------------------------------------------

Boolean
CColorWell::PickRGBColor(RGBColor * inRGB)
{	
	ColorPickerInfo	cpinfo;
	Boolean			picked = false;
	OSErr			error;
	
	if (inRGB == NULL) {
		inRGB->red = 0xffff;
		inRGB->green = 0xffff;
		inRGB->blue = 0xffff;
	} 
	
	cpinfo.theColor.profile = 0L;
	cpinfo.theColor.color.rgb.red   = inRGB->red;
	cpinfo.theColor.color.rgb.green = inRGB->green;
	cpinfo.theColor.color.rgb.blue  = inRGB->blue;
	cpinfo.dstProfile = 0L;
	cpinfo.flags = kColorPickerCanModifyPalette 
	| kColorPickerCanAnimatePalette;
	cpinfo.placeWhere = kDeepestColorScreen;
	cpinfo.pickerType = 0L;
	cpinfo.eventProc = NULL;
	cpinfo.colorProc = NULL;
	cpinfo.colorProcData = NULL;
	error = PickColor(&cpinfo);
	if ((error == noErr) && (cpinfo.newColorChosen != 0)) {
		inRGB->red    = cpinfo.theColor.color.rgb.red;
		inRGB->green  = cpinfo.theColor.color.rgb.green;
		inRGB->blue   = cpinfo.theColor.color.rgb.blue;
		picked = true;
	}
	
	return picked;
}




PP_End_Namespace_PowerPlant
