// ===========================================================================
// CMenuObject.h
// 
//                       Created: 2005-03-10 09:12:57
//             Last modification: 2005-03-10 09:48:08
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
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
							   Str255	inTitle,
							   ResIDT	inID,
							   ResIDT	inMDEF,
							   Boolean	inEnabled);
					CMenuObject(LHandleStream * inStream);
					~CMenuObject();

		void	AddItem();
		void	AddItem(CMenuItem * inItem);
		void	AddItem(Str255	inName,
							OSType	inKeyword, 
							OSType	inType, 
							Str255	inDescription, 
							UInt16	inFlags);
		void	RemoveItem( ArrayIndexT inAtIndex );
		
		SInt32	NewItem();
		SInt32	DeleteItem();

		void	InstallDataStream(LHandleStream * inStream);
		void	SendDataToStream(LHandleStream * outStream);
		
		void	GetValues(
					   Str255 & outTitle, ResIDT & outID,
					   ResIDT & outMDEF, Boolean & outEnabled);
		
		void	SetValues(
					   Str255 inTitle, ResIDT inID,
					   ResIDT inMDEF, Boolean inEnabled);

		ArrayIndexT		GetItemIndex() { return mItemIndex;}
		void			SetItemIndex(ArrayIndexT inItemIndex) {mItemIndex = inItemIndex;}

		SInt32			CountItems() { return mItems.GetCount(); }

		TArray<CMenuItem*> *	GetItems() { return &mItems;}

protected:
		Str255					mTitle;
		ResIDT					mID;
		ResIDT					mMDEF;
		Boolean					mEnabled;
		ArrayIndexT				mItemIndex;		
		TArray<CMenuItem*>		mItems;

private:


};


#endif
