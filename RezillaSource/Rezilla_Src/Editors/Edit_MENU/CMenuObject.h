// ===========================================================================
// CMenuObject.h
// 
//                       Created: 2005-03-10 09:12:57
//             Last modification: 2006-09-30 06:25:04
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes, 2005-2006
// All rights reserved.
// ===========================================================================

#ifndef _H_CMenuObject
#define _H_CMenuObject
#pragma once


class LHandleStream;
class CMenuItem;

class CMenuObject {

public:
					CMenuObject();
					CMenuObject(
								ResIDT	inID,
								ResIDT	inMDEF,
								UInt32	inEnableFlag,
								Str255	inTitle);
					CMenuObject(LHandleStream * inStream);
					~CMenuObject();

		static Boolean	GetMenuTitle(short inID, short inRefnum, Str255 outString);
		
		void	AddItem();
		void	AddItem(CMenuItem * inItem);
		void	AddItem(Str255 inTitle,
						UInt8 inIconID,
						UInt8 inShortcut,
						UInt8 inMark,
						Style inStyle);
		void	RemoveItem( ArrayIndexT inAtIndex );
		
		SInt32	NewItem();
		SInt32	NewItem(TableIndexT inAfterRow);
		SInt32	DeleteItem();
		
		void	InstallData(LHandleStream * inStream);
		void	SendData(LHandleStream * outStream);
		
		Style	GetStyleAtIndex( ArrayIndexT inAtIndex );
		void	SetStyleAtIndex(Style theStyle, ArrayIndexT inAtIndex );
		
		void	GetValues( 
						  ResIDT & outID, ResIDT & outMDEF, 
						  UInt32 & outEnableFlag, Str255 & outTitle);
		
		void	SetValues(
						  ResIDT inID, ResIDT inMDEF, 
						  UInt32 inEnableFlag, Str255 inTitle);

		void		GetTitle(Str255 & outTitle);
		void		SetTitle(Str255 inTitle);
		
		ArrayIndexT		GetItemIndex() { return mItemIndex;}
		void			SetItemIndex(ArrayIndexT inItemIndex) {mItemIndex = inItemIndex;}

		SInt32			CountItems() { return mItems.GetCount(); }

		TArray<CMenuItem*> *	GetItems() { return &mItems;}

		UInt32		GetEnableFlag() { return mEnableFlag;}
		void		SetEnableFlag(UInt32 inEnableFlag) {mEnableFlag = inEnableFlag;}

		ResIDT		GetMDEF() { return mMDEF;}
		void		SetMDEF(ResIDT inMDEF) {mMDEF = inMDEF;}
		
protected:
		ResIDT					mID;
		ResIDT					mMDEF;
		UInt32					mEnableFlag;
		Str255					mTitle;
		ArrayIndexT				mItemIndex;		
		TArray<CMenuItem*>		mItems;

private:


};


#endif
