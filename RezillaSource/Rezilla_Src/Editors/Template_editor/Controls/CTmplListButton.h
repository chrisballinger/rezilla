// ===========================================================================
// CTmplListButton.
// 
//                       Created: 2004-06-28 08:48:08
//             Last modification: 2004-06-28 08:48:22
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// ===========================================================================

#ifndef _H_CTmplListButton
#define _H_CTmplListButton
#pragma once

#include <LPushButton.h>


#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

// ---------------------------------------------------------------------------

class	CTmplListButton : public LPushButton {
public:
	enum { class_ID		= FOUR_CHAR_CODE('TLBn'),
		   imp_class_ID	= FOUR_CHAR_CODE('ipus') };

						CTmplListButton(
								LStream*		inStream,
								ClassIDT		inImpID = imp_class_ID);

						CTmplListButton(
								const SPaneInfo&	inPaneInfo,
								MessageT			inValueMessage,
								ConstStringPtr		inTitle,
								SInt16				inKind = kControlPushButtonProc,
								ResIDT				inTextTraitsID = 0,
								SInt16				inCicnID = 0,
								ClassIDT			inImpID = imp_class_ID);

	virtual				~CTmplListButton();


protected:
	virtual void		BroadcastValueMessage();

};

PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
