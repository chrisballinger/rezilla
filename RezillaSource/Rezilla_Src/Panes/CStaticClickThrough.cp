// ===========================================================================
// CStaticClickThrough.cp
// 
//                       Created : 2006-09-21 11:57:44
//             Last modification : 2006-09-21 12:13:24
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@users.sourceforge.net>
// www : <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2006
// All rights reserved.
// ===========================================================================
// Simple static text passing clicks to its super view: it is used in some
// picker stamps (TEXT, STR#)

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CStaticClickThrough.h"

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
// CStaticClickThrough							Parameterized Constructor [public]
// ---------------------------------------------------------------------------

CStaticClickThrough::CStaticClickThrough(
	const SPaneInfo&	inPaneInfo,
	ConstStringPtr		inTitle,
	ResIDT				inTextTraitsID,
	ClassIDT			inImpID)

	: LStaticText(inPaneInfo, inTitle, inTextTraitsID, inImpID)
{
}


// ---------------------------------------------------------------------------
//     ~CStaticClickThrough				Destructor				  [public]
// ---------------------------------------------------------------------------

CStaticClickThrough::~CStaticClickThrough()
{
}



#pragma mark -

// ---------------------------------------------------------------------------
// 	ClickSelf
// ---------------------------------------------------------------------------

void
CStaticClickThrough::ClickSelf( const SMouseDownEvent & inEvent)
{
	if (mSuperView != NULL) {
		mSuperView->ClickSelf(inEvent);
	} 
}




PP_End_Namespace_PowerPlant
