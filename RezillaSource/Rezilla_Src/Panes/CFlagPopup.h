// ===========================================================================
// CFlagPopup.h
// 
//                       Created: 2005-03-25 15:49:17
//             Last modification: 2005-03-25 16:10:11
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CFlagPopup
#define _H_CFlagPopup
#pragma once

#include <LPopupButton.h>

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

// ---------------------------------------------------------------------------

class CFlagPopup : public LPopupButton {
public:
	enum { class_ID		= FOUR_CHAR_CODE('FlgP'),
		   imp_class_ID	= FOUR_CHAR_CODE('ipop') };

						CFlagPopup(
								LStream*	inStream,
								ClassIDT	inImpID = imp_class_ID);

						CFlagPopup(
								   const SPaneInfo&	inPaneInfo,
								   MessageT			inValueMessage,
								   ResIDT			inStringListID);

	virtual				~CFlagPopup();

	void			FillPopup(ResIDT inStringListID);

	virtual SInt32	GetValue() const;
	
	virtual void	SetValue( SInt32 inValue );
	
protected:
	virtual void	HotSpotResult( SInt16 inHotSpot );

private:
	void			InitFlagPopup(ResIDT inStringListID);
};

PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
