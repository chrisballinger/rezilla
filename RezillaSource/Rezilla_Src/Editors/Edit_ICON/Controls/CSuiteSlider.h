// ===========================================================================
// CSuiteSlider.h
//                       Created: 2005-01-10 09:03:25
//             Last modification: 2005-01-10 22:17:37
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#ifndef _H_CSuiteSlider
#define _H_CSuiteSlider
#pragma once

#include <LSlider.h>

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

class CSuite_Window;


// ---------------------------------------------------------------------------

class CSuiteSlider : public LSlider {
public:
	enum { class_ID		= FOUR_CHAR_CODE('SuSl'),
		   imp_class_ID	= FOUR_CHAR_CODE('isld') };

						CSuiteSlider(
								LStream*		inStream);

	virtual				~CSuiteSlider();

	virtual void		HotSpotResult( SInt16 inHotSpot );

	virtual void		DoTrackAction(
								SInt16			inHotSpot,
								SInt32			inValue);

	void				SetOwnerWindow(CSuite_Window* inOwnerWindow) {mOwnerWindow = inOwnerWindow;}

protected:
	CSuite_Window *	mOwnerWindow;

};

PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
