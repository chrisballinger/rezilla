// ===========================================================================
// CColorWell.h
// 
//                       Created: 2004-08-20 12:37:09
//             Last modification: 2004-08-20 13:13:55
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CColorWell
#define _H_CColorWell
#pragma once


#include <LPane.h>
#include <LBroadcaster.h>

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

// ---------------------------------------------------------------------------


class CColorWell : public LPane, public LBroadcaster {

public:
	enum { class_ID = FOUR_CHAR_CODE('CWel') };

						CColorWell();
						CColorWell(	const CColorWell &inOriginal);
						CColorWell(	const SPaneInfo &inPaneInfo, 
								   RGBColor * inColor,
								   MessageT inMessage);
						CColorWell(	LStream * inStream);

	virtual				~CColorWell();

	virtual void		ClickSelf( const SMouseDownEvent& inMouseDown );
								
	virtual void		DrawSelf();
	
	virtual StringPtr	GetDescriptor( Str255 outDescriptor ) const;
	virtual void		SetDescriptor( ConstStringPtr inDescriptor );

	static Boolean		PickRGBColor(RGBColor * inRGB);
	
	void				GetColor(RGBColor & ioColor);
	void				SetColor(RGBColor inColor);

protected:
	PenState		mPenState;
	RGBColor		mColor;
	MessageT		mMessage;

	virtual void	FinishCreateSelf();

private:


};



PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
