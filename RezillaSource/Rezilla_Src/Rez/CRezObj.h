// ===========================================================================
// CRezObj.h					
// 
//                       Created: 2003-04-23 12:32:10
//             Last modification: 2005-02-16 09:51:13
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003-2004, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CRezObj
#define _H_CRezObj
#pragma once

#include <LModelObject.h>

class CRezType;


class CRezObj : public LModelObject {

public:
				CRezObj(Handle inResHandle, short inRefnum);
				CRezObj(CRezType * inRezType,
						short inID);
				CRezObj(CRezType * inRezType,
						short inID, 
						Str255* inName);
				CRezObj(short inRefnum,
						ResType inType,
						short inID, 
						Str255* inName);
				CRezObj(CRezType * inRezType);
				CRezObj(CRezObj& inOriginal);
				~CRezObj();

		OSErr Changed();
		OSErr Add();
		OSErr Remove();
		
		OSErr Detach();
		OSErr Release();
		OSErr Load();

		OSErr Write();
		
		// Getters and setters
		
		OSErr 			GetRezHandle();

		OSErr 			GetInfoFromMap();
		OSErr 			SetInfoInMap();

		virtual ResType		GetType() { return mType;}
		void				SetType(ResType theType) {mType = theType ;}

		virtual short		GetOwnerRefnum() { return mOwnerRefnum;}
		void				SetOwnerRefnum(short theOwnerRefnum) {mOwnerRefnum = theOwnerRefnum ;}
		
		short			GetID() { return mID;}
		void			SetID(short theID) {mID = theID ;}

		Str255*			GetName() { return &mName;}
		void			SetName(Str255* theName);

		Handle			GetData() { return mData;}
		void			SetData(Handle srcHandle);

		virtual Size	GetSize() { return mSize;}
		void			SetSize(Size theSize) {mSize = theSize ;}

		OSErr 			GetMaxSize(Size & outSize);
		OSErr			GetSizeOnDisk(Size & outSize);
		OSErr			SetSizeOnDisk(Size inSize);

		virtual short	GetAttributes() { return mAttributes;}
		OSErr			GetAttributesFromMap(short & outAttribute);
		OSErr			SetAttributesInMap(short inAttributes);

		Boolean			HasAttribute(short inFlag);
		OSErr			ToggleOneAttribute(short inFlag);
		OSErr			SetOneAttribute(short inFlag, Boolean inSetting);

protected:
	short			mOwnerRefnum;
	ResType			mType;
	short			mID;
	Str255			mName;
	Size			mSize;
	Handle			mData;
	short			mAttributes;

};




// 		ReadPartial(long offset, const void * buffer, long count);
// 		WritePartial(long offset, const void * buffer, long count);



//        ================== INLINES =====================

// ---------------------------------------------------------------------------
//	• HasAttribute													[inline]
// ---------------------------------------------------------------------------
// Checks if a resource’s attribute is on or off. The inFlag argument 
// is one of the following constants:
// 		resSysHeap		In system or in application heap
// 		resPurgeable	Purgeable or not
// 		resLocked		Locked or not
// 		resProtected	Protected or not
// 		resPreload		Read in at OpenResource or not
// 		resChanged		Existing resource changed since last update

inline
Boolean
CRezObj::HasAttribute( short inFlag )
{
	return ((mAttributes & inFlag) != 0);
}




#endif
