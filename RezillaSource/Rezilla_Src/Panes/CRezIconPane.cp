// ===========================================================================
// CRezIconPane.cp					
// 
//                       Created : 2004-04-15 13:31:41
//             Last modification : 2004-04-15 13:57:11
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@easyconnect.fr>
// www : <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
// Subclass ensuring that the right resource map is used to display an icon resource.

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CRezIconPane.h"
#include "UResources.h"

#include <LStream.h>
#include <PP_Constants.h>

#include <Icons.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//	¥ CRezIconPane								Default Constructor		  [public]
// ---------------------------------------------------------------------------

CRezIconPane::CRezIconPane()
{
	mIconID = resID_Undefined;
}


// ---------------------------------------------------------------------------
//	¥ CRezIconPane								Parameterized Constructor [public]
// ---------------------------------------------------------------------------

CRezIconPane::CRezIconPane(
	const SPaneInfo&	inPaneInfo,
	ResIDT				inIconID)

	: LIconPane(inPaneInfo, inIconID)
{
}


// ---------------------------------------------------------------------------
//	¥ CRezIconPane								Stream Constructor		  [public]
// ---------------------------------------------------------------------------

CRezIconPane::CRezIconPane(
	LStream*	inStream)

	: LIconPane(inStream)
{
}


// ---------------------------------------------------------------------------
//	¥ ~CRezIconPane							Destructor				  [public]
// ---------------------------------------------------------------------------

CRezIconPane::~CRezIconPane()
{
}


// ---------------------------------------------------------------------------
//	¥ SetIconID														  [public]
// ---------------------------------------------------------------------------

void
CRezIconPane::SetIconID(
	ResIDT	inIconID)
{
	mIconID = inIconID;
// 	Refresh();
}


// ---------------------------------------------------------------------------
//	¥ DrawSelf														  [public]
// ---------------------------------------------------------------------------

void
CRezIconPane::DrawSelf()
{
	if (mCurrentRefNum != UResources::refNum_Undef) {
		Rect	frame;
		CalcLocalFrameRect(frame);
		StRezReferenceSaver saver(mCurrentRefNum);		
		::PlotIconID(&frame, kAlignNone, kTransformNone, mIconID);
	}
}


PP_End_Namespace_PowerPlant
