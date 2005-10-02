// ===========================================================================
// CFlagPopup.h
// 
//                       Created: 2005-03-25 15:49:17
//             Last modification: 2005-04-08 06:29:04
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
								   ResIDT			inStringListID = 0);

	virtual				~CFlagPopup();

	void			FillPopup(ResIDT inStringListID);

	void			AppendCase(Str255 inString);
	
	virtual UInt32	GetFlagValue() const;
	
	virtual void	SetFlagValue( UInt32 inValue );
	
protected:
	ResIDT				mStringListID;
	SInt32				mResetIndex;
	UInt16				mNumTopItems;
	TArray<UInt32>		mFlagValues;

	virtual void	HotSpotResult( SInt16 inHotSpot );

private:
	void			InitFlagPopup();
	void			UpdatePopupWithValue(UInt32	inValue) ;
	
};

PP_End_Namespace_PowerPlant




#endif
