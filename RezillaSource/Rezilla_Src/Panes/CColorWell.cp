// ===========================================================================
// CColorWell.cp
// 
//                       Created: 2004-08-20 12:37:09
//             Last modification: 2004-08-20 13:08:59
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CColorWell.h"
#include "UMiscUtils.h"


PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//	¥ CColorWell							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CColorWell::CColorWell()
{}


// ---------------------------------------------------------------------------
//	¥ CColorWell							Copy Constructor		  [public]
// ---------------------------------------------------------------------------

CColorWell::CColorWell(
	const CColorWell&	inOriginal)
: LPane(inOriginal)
{}


// ---------------------------------------------------------------------------
//	¥ CColorWell							Parameterized Constructor [public]
// ---------------------------------------------------------------------------

CColorWell::CColorWell(	const SPaneInfo &inPaneInfo, 
					   RGBColor * foreRGB, 
					   RGBColor * backRGB)
: LPane(inPaneInfo)
{
	mForeColor.red = foreRGB->red;
	mForeColor.green = foreRGB->green;
	mForeColor.blue = foreRGB->blue;
	mBackColor.red = backRGB->red;
	mBackColor.green = backRGB->green;
	mBackColor.blue = backRGB->blue;
	
	mPenState.pnLoc = Point_00;
	mPenState.pnSize.h = 1;
	mPenState.pnSize.v = 1;
	mPenState.pnMode = patCopy;
	UQDGlobals::GetBlackPat(&mPenState.pnPat);

}


// ---------------------------------------------------------------------------
//	¥ CColorWell							Stream Constructor		  [public]
// ---------------------------------------------------------------------------

CColorWell::CColorWell(
	LStream*	inStream)
: LPane(inStream)
{}


// ---------------------------------------------------------------------------
//	¥ ~CColorWell							Destructor				  [public]
// ---------------------------------------------------------------------------

CColorWell::~CColorWell()
{}


// ---------------------------------------------------------------------------
//	¥ FinishCreateSelf
// ---------------------------------------------------------------------------

void
CColorWell::FinishCreateSelf()
{
}

#pragma mark -

// ---------------------------------------------------------------------------
//	¥ ClickSelf
// ---------------------------------------------------------------------------
//	Respond to Click inside this Pane

void
CColorWell::ClickSelf(
	const SMouseDownEvent&	/* inMouseDown */)
{
	UMiscUtils::PickRGBColor(&mForeColor);
	Refresh();
}


// ---------------------------------------------------------------------------
//	¥ DrawSelf
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
	::RGBForeColor(&mForeColor);
	::RGBBackColor(&mBackColor);

	::MacInsetRect(&frame, mPenState.pnSize.h, mPenState.pnSize.v);
	::PaintRect(&frame);
}


// ---------------------------------------------------------------------------
//	¥ GetValue														  [public]
// ---------------------------------------------------------------------------

SInt32
CColorWell::GetValue() const
{
	return 0;
}


// ---------------------------------------------------------------------------
//	¥ SetValue														  [public]
// ---------------------------------------------------------------------------

void
CColorWell::SetValue(
	SInt32	/* inValue */)
{
}


// ---------------------------------------------------------------------------
//	¥ GetDescriptor													  [public]
// ---------------------------------------------------------------------------

StringPtr
CColorWell::GetDescriptor(
	Str255	outDescriptor) const
{
	outDescriptor[0] = 0;
	return outDescriptor;
}


// ---------------------------------------------------------------------------
//	¥ SetDescriptor													  [public]
// ---------------------------------------------------------------------------

void
CColorWell::SetDescriptor(
	ConstStringPtr	/* inDescriptor */)
{
}


PP_End_Namespace_PowerPlant
