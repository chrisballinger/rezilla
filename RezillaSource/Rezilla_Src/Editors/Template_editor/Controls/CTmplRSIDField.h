// ===========================================================================
// CTmplRSIDField.h
// 
//             Last modification: 2006-08-04 20:16:30
// Author: ZPedro
// e-mail: <lebpierre@wanadoo.fr>
// www: <http://rezilla.sourceforge.net/>
// ===========================================================================

#ifndef _H_CTmplRSIDField
#define _H_CTmplRSIDField
#pragma once

#if PP_Uses_Pragma_Import
#pragma import on
#endif

#include <LEditText.h>
#include <LBevelButton.h>
#include <LListener.h>
#include <LHandleStream.h>
#include <TArray.h>

class CRezMap;

const SInt16	kRSIDFieldHeight	= 18;
const SInt16	kRSIDFieldWidth		= 12;
const SInt16	kRSIDFieldSep		= 4;

PP_Begin_Namespace_PowerPlant

class CTmplRSIDField : public LEditText, public LListener {
public:
	enum { class_ID		= FOUR_CHAR_CODE('TRsF'),
		imp_class_ID	= FOUR_CHAR_CODE('ietx') };
		
	CTmplRSIDField(
				LStream*		inStream,
				ClassIDT		inImpID = imp_class_ID);
				
	CTmplRSIDField(
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
				ResType				inResType,
				CRezMap *			inRezMap,
				Boolean				inLeftSide = false,
				bool				inPasswordField = false,
				ClassIDT			inImpID = imp_class_ID);
				
	virtual				~CTmplRSIDField();
	
	virtual void		Show();
	virtual void		Hide();
	virtual void		Enable();
	virtual void		Disable();
	virtual void		ResizeFrameBy(
							 SInt16			inWidthDelta,
							 SInt16			inHeightDelta,
							 Boolean		inRefresh);
	virtual void	ListenToMessage(
							  MessageT		inMessage,
							  void*			ioParam);
	
	void			FillPopup();
	SInt16			AdjustPopupWithValue(Str255 inString);
	virtual void	UserChangedText();

	// Accessors
	LBevelButton*	GetPopup() { return mPopup;}
	virtual void	GetUnknownItem( Str31 outString ) const;
	virtual void	SetUnknownItem( ConstStr31Param inString );
	virtual void	GetNoneItem( Str31 outString ) const;
	virtual void	SetNoneItem( ConstStr31Param inString );
	virtual void	GetRezMap( CRezMap* &outRezMap ) const;
	virtual void	SetRezMap( CRezMap* inRezMap );
	virtual void	GetTnamField( LEditText* &outPane ) const;
	virtual void	SetTnamField( LEditText* inPane );
	virtual void	GetResType( ResType &outType ) const;
	virtual void	SetResType( ResType inType );
	
protected:
	LBevelButton *	mPopup;
	Str31			mUnknownItem;
	LHandleStream *	mTemplateStream;
	SInt32			mStartMark;
	TArray<SInt16>	mValsList;
	ResType			mResType;
	Str31			mNoneItem;
	CRezMap*		mRezMap;
	LEditText*		mTnamField; // Notice it can be a CTmplCaseField without problem

private:
	void			CreatePopup(MessageT inPopupMsg, Boolean inLeftSide);
};

PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
 #pragma import reset
#endif

#endif  // _H_CTmplRSIDField
