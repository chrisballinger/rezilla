// ===========================================================================
// CPopupEditField.h
// 
//                       Created: 2005-03-12 07:58:12
//             Last modification: 2005-03-24 10:57:45
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#ifndef _H_CPopupEditField
#define _H_CPopupEditField
#pragma once


#if PP_Uses_Pragma_Import
	#pragma import on
#endif

#include <LEditText.h>
#include <LBevelButton.h>
#include <LListener.h>

// class CPopupEditField;
// 
// struct STmplBevelInfo {
// 	CPopupEditField *	selfPtr;
// 	SInt32				menuChoice;
// };
const SInt16	kPopupEditHeight	= 18;
const SInt16	kPopupEditWidth		= 12;
const SInt16	kPopupEditSep		= 4;


PP_Begin_Namespace_PowerPlant

// ---------------------------------------------------------------------------

class CPopupEditField : public LEditText, public LListener {
public:
	enum { class_ID		= FOUR_CHAR_CODE('PopF'),
		   imp_class_ID	= FOUR_CHAR_CODE('ietx') };

		   CPopupEditField(
					   LStream*		inStream,
					   ClassIDT		inImpID = imp_class_ID);

		   CPopupEditField(
				   const SPaneInfo&	inPaneInfo,
				   LCommander*		inSuperCommander,
				   ConstStringPtr	inInitialText,
				   ResIDT			inTextTraitsID,
				   MessageT			inMessage,
				   MessageT 		inPopupMessage,
				   SInt16			inMaxChars,
				   UInt8			inAttributes,
				   TEKeyFilterFunc	inKeyFilter,
				   ResIDT			inStringListID,
				   Boolean			inLeftSide = false,
				   bool				inPasswordField = false,
				   ClassIDT			inImpID = imp_class_ID);

	virtual				~CPopupEditField();


	virtual void	ListenToMessage(
							MessageT		inMessage,
							void*			ioParam);

	virtual void	UserChangedText();

	SInt16			AdjustPopupWithValue(Str255 inString);

	SInt16			FindInPopup(Str255 inString) ;
	
	void			FillPopup(ResIDT inStringListID);
	
	LBevelButton*	GetPopup() { return mPopup;}

	virtual void	GetUnknownItem( Str31 outString ) const;
	virtual void	SetUnknownItem( Str31 inString );

protected:
		LBevelButton *	mPopup;
		Str31			mUnknownItem;
		ResIDT			mStringsID;
							
// 	virtual void	FinishCreateSelf();		
	
private:
	void			CreatePopup(MessageT inPopupMsg, Boolean inLeftSide);

};



PP_End_Namespace_PowerPlant

#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
