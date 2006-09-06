// ===========================================================================
// CTmplCaseField.h
// 
//                       Created: 2005-03-24 11:02:01
//             Last modification: 2005-04-15 07:02:18
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2005
// All rights reserved.
// ===========================================================================


#ifndef _H_CTmplCaseField
#define _H_CTmplCaseField
#pragma once


#if PP_Uses_Pragma_Import
	#pragma import on
#endif

#include <LEditText.h>
#include <LBevelButton.h>
#include <LListener.h>
#include <LHandleStream.h>


const SInt16	kCaseFieldHeight	= 18;
const SInt16	kCaseFieldWidth		= 12;
const SInt16	kCaseFieldSep		= 4;


PP_Begin_Namespace_PowerPlant

// ---------------------------------------------------------------------------

class CTmplCaseField : public LEditText, public LListener {
public:
	enum { class_ID		= FOUR_CHAR_CODE('CasF'),
		   imp_class_ID	= FOUR_CHAR_CODE('ietx') };

		   CTmplCaseField(
					   LStream*		inStream,
					   ClassIDT		inImpID = imp_class_ID);

		   CTmplCaseField(
					const SPaneInfo&	inPaneInfo,
					LCommander*			inSuperCommander,
					ConstStringPtr		inInitialText,
					ResIDT				inTextTraitsID,
					MessageT			inMessage,
					MessageT 			inPopupMessage,
					SInt16				inMaxChars,
					UInt8				inAttributes,
					TEKeyFilterFunc		inKeyFilter,
					LHandleStream *		inTemplateStream,
					SInt32				inStartMark,
					Boolean				inLeftSide = false,
					bool				inPasswordField = false,
					ClassIDT			inImpID = imp_class_ID);

	virtual				~CTmplCaseField();


	virtual void		Show();
	virtual void		Hide();

	virtual void		Enable();
	virtual void		Disable();

	virtual void		ResizeFrameBy(
								SInt16				inWidthDelta,
								SInt16				inHeightDelta,
								Boolean				inRefresh);

	virtual void	ListenToMessage(
							MessageT		inMessage,
							void*			ioParam);

	void			FillPopup();
	
	virtual void	UserChangedText();

	SInt16			AdjustPopupWithValue(Str255 inString);

	SInt16			FindInPopup(Str255 inString) ;
	
	void			GetStringAtIndex(SInt16 inIndex, Str255 outString);
	
	LBevelButton*	GetPopup() { return mPopup;}

	virtual void	GetUnknownItem( Str31 outString ) const;
	virtual void	SetUnknownItem( Str31 inString );

protected:
		LBevelButton *	mPopup;
		Str31			mUnknownItem;
		LHandleStream *	mTemplateStream;
		SInt32			mStartMark;
							
	
private:
	void			CreatePopup(MessageT inPopupMsg, Boolean inLeftSide);

};



PP_End_Namespace_PowerPlant

#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
