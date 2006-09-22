// ===========================================================================
// CPickerWindow.h				
// 
//                       Created: 2006-02-23 15:12:16
//             Last modification: 2006-09-22 05:10:33
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================

#ifndef _H_TPickerView
#define _H_TPickerView
// #pragma once

#include "UResources.h"

#include <LWindow.h>

class CPickerDoc;
class CPickerView;
class LStaticText;


class CPickerWindow : public LWindow, public LListener {
public:
	enum { class_ID = FOUR_CHAR_CODE('PikW') };

							CPickerWindow();
							CPickerWindow( const SWindowInfo &inWindowInfo );
							CPickerWindow(
							    ResIDT inWINDid,
								UInt32 inAttributes, LCommander *inSuperCommander );
							CPickerWindow(
								WindowPtr	inMacWindow,
								LCommander*	inSuperCommander);
							CPickerWindow( LStream *inStream );
							~CPickerWindow();

	virtual void	ListenToMessage( MessageT inMessage,void *ioParam);

	virtual void	FindCommandStatus(
								CommandT			inCommand,
								Boolean&			outEnabled,
								Boolean&			outUsesMark,
								UInt16&				outMark,
								Str255				outName);

	virtual Boolean	ObeyCommand(
							CommandT			inCommand,
							void*				ioParam);

	virtual void	FinalizePicker(CPickerDoc* inPickerDoc, void * ioParam = NULL);
	
	void			InstallReadOnlyIcon();

	virtual void	DoSetBounds(const Rect& inBounds);

	void			RecalcLayout();

	void			AddPickerView( CPickerView* inView );
	void			RemovePickerView( CPickerView* inView );
	void			DeletePickerView( short inID );
	void			DeletePickerView( CPickerView* inView );

	CPickerView *	FindPickerView( short inID );
	

	// AppleEvents
	virtual void    MakeSelfSpecifier(
								AEDesc&         inSuperSpecifier,
								AEDesc&         outSelfSpecifier) const;
	
	virtual void	GetAEProperty(
								DescType		inProperty,
								const AEDesc&	inRequestedType,
								AEDesc&			outPropertyDesc) const;
	
	virtual bool	AEPropertyExists(
								DescType		inProperty) const;

	long			GetRezCountField() const;
	void			SetRezCountField(long inCount);
	
	// Accessors
	CPickerDoc *		GetOwnerDoc() { return mOwnerDoc;}
	void				SetOwnerDoc(CPickerDoc* theOwnerDoc) {mOwnerDoc = theOwnerDoc ;}

	ResType				GetType() { return mType;}
	void				SetType(ResType inType) {mType = inType;}

	void				GetStampSize(SInt16 &outWidth, SInt16 &outHeight);
	void				SetStampSize(SInt16 inWidth, SInt16 inHeight);

	LView*				GetContentsView() { return mContentsView;}

	CPickerView*		GetSelectedView() { return mSelectedView;}
	void				SetSelectedView(CPickerView* inSelectedView) {mSelectedView = inSelectedView;}

protected:
	CPickerDoc *			mOwnerDoc;
	ResType					mType;
	SInt16					mStampWidth;
	SInt16					mStampHeight;
	LView *					mContentsView;
	TArray<CPickerView *>*	mViewList;
	CPickerView *			mSelectedView;
	LStaticText *			mRezCountField;

	virtual void	FinishCreateSelf();

private:
	void		Initialize();
	
};


#endif  // _H_TPickerView
