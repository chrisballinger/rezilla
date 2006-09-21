// ===========================================================================
// CStaticClickThrough.h					
// 
//                       Created : 2006-09-21 11:57:44
//             Last modification : 2006-09-21 12:13:17
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@users.sourceforge.net>
// www : <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2006
// All rights reserved.
// ===========================================================================

#ifndef _H_CStaticClickThrough
#define _H_CStaticClickThrough
#pragma once

#include <LStaticText.h>

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------

class CStaticClickThrough : public LStaticText {
public:
	enum { class_ID		= FOUR_CHAR_CODE('CTst'),
		   imp_class_ID	= FOUR_CHAR_CODE('istx')};

					   CStaticClickThrough(
								const SPaneInfo&	inPaneInfo,
								ConstStringPtr		inTitle,
								ResIDT				inTextTraitsID = 0,
								ClassIDT			inImpID = imp_class_ID);

	virtual				~CStaticClickThrough();


	virtual void 		ClickSelf( const SMouseDownEvent & );

};


PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
