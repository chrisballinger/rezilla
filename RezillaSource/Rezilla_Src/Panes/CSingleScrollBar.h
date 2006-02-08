// ===========================================================================
// CSingleScrollBar.h				
// 
//                       Created: 2004-03-19 13:49:48
//             Last modification: 2004-03-20 07:26:18
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#ifndef _H_CSingleScrollBar
#define _H_CSingleScrollBar
#pragma once

#include <LScrollBar.h>

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

// ---------------------------------------------------------------------------

class CSingleScrollBar : public LScrollBar {
public:
	enum { class_ID		= FOUR_CHAR_CODE('Ssbr'),
		   imp_class_ID	= FOUR_CHAR_CODE('isba') };

						CSingleScrollBar(
								LStream*			inStream,
								ClassIDT			inImpID = imp_class_ID);

						CSingleScrollBar(
								const SPaneInfo&	inPaneInfo,
								MessageT			inValueMessage,
								SInt32				inValue,
								SInt32				inMinValue,
								SInt32				inMaxValue,
								bool				inLiveScrolling = false,
								ClassIDT			inImpID = imp_class_ID);

	virtual				~CSingleScrollBar();

	virtual void		DoTrackAction(
								SInt16				inHotSpot,
								SInt32				inValue);

	virtual SInt32		GetLinesPerPage() { return mLinesPerPage;}
	void				SetLinesPerPage(SInt32 inLinesPerPage) {mLinesPerPage = inLinesPerPage;}

protected:
	SInt32		mLinesPerPage;	
	
private:
	void				InitScrollBar();
};

PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
