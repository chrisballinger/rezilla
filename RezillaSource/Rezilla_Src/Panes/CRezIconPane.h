// ===========================================================================
// CRezIconPane.h				
// 
//                       Created : 2004-04-15 13:31:41
//             Last modification : 2004-04-15 13:40:07
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@users.sourceforge.net>
// www : <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// ===========================================================================

#ifndef _H_CRezIconPane
#define _H_CRezIconPane
#pragma once

#include <LIconPane.h>

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

// ---------------------------------------------------------------------------

class	CRezIconPane : public LIconPane {
public:
	enum { class_ID = FOUR_CHAR_CODE('Rzip') };

						CRezIconPane();

						CRezIconPane(
								const SPaneInfo&	inPaneInfo,
								ResIDT				inIconID);

						CRezIconPane( LStream* inStream );

	virtual				~CRezIconPane();

	virtual void		DrawSelf();

	void				SetIconID( ResIDT inIconID );

	virtual short		GetCurrentRefNum() { return mCurrentRefNum;}
	void				SetCurrentRefNum(short inCurrentRefNum) {mCurrentRefNum = inCurrentRefNum;}
	
protected:
	short				mCurrentRefNum;
	
};

PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
