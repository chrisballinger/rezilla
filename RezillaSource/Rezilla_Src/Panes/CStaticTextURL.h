// ===========================================================================
// CStaticTextURL.h
// 
//                       Created: 2004-06-20 20:22:41
//             Last modification: 2004-06-21 07:41:09
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// ===========================================================================

#ifndef _H_CStaticTextURL
#define _H_CStaticTextURL
#pragma once

#include <LStaticText.h>

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

class	LString;

// ---------------------------------------------------------------------------

class	CStaticTextURL : public LStaticText {
public:
	enum { class_ID		= FOUR_CHAR_CODE('STXU'),
		   imp_class_ID	= FOUR_CHAR_CODE('istx') };

						CStaticTextURL(
								LStream*		inStream,
								ClassIDT		inImpID = imp_class_ID);

						CStaticTextURL(
								const SPaneInfo&	inPaneInfo,
								ConstStringPtr		inTitle,
								ResIDT				inTextTraitsID = 0,
								ClassIDT			inImpID = imp_class_ID);

	virtual				~CStaticTextURL();

	
	virtual StringPtr	GetUrlString( Str255 outDescriptor ) const;
	void				SetUrlString(ConstStringPtr inUrlString);
	
	OSErr				SendGurlGurlEvent();

protected:
	Str255			mUrlString;
//	Cursor			mHandCursor;

	virtual void		ClickSelf(const SMouseDownEvent &inMouseDown);
	
	virtual void		AdjustMouseSelf(
								Point				inPortPt,
								const EventRecord&	inMacEvent,
								RgnHandle			outMouseRgn);
	
private:
//		void			InitUrlPane();
};

PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
