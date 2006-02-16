// ===========================================================================
// CRezObj.h					
// 
//                       Created: 2003-04-23 12:32:10
//             Last modification: 2005-06-05 09:08:08
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2003-2005
// All rights reserved.
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
		
		// AppleEvents
		virtual void	MakeSelfSpecifier(
									AEDesc&			inSuperSpecifier,
									AEDesc&			outSelfSpecifier) const;

		virtual void	GetAEProperty(
									DescType		inProperty,
									const AEDesc&	inRequestedType,
									AEDesc&			outPropertyDesc) const;

		void			SetAEProperty(
									DescType		inProperty,
									const AEDesc&	inValue,
									AEDesc&			outAEReply);
		
		void			GetAERezObjAttribute(
									short		inFlag,
									AEDesc&		outPropertyDesc) const;
		
		void			SetAERezObjAttribute(
									const AEDesc& inValue, 
									short inFlag);
		
		void		GetAEResourceData(AEDesc& outPropertyDesc) const;

		void		SetAEResourceData(const AEDesc& inValue);

		virtual bool	AEPropertyExists(
									DescType	inProperty) const;

		virtual void	HandleAppleEvent(
									const AppleEvent	&inAppleEvent,
									AppleEvent			&outAEReply,
									AEDesc				&outResult,
									SInt32				inAENumber);
		
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

		OSErr			GetIndexInType(SInt32 & outIndex) const;
// 		OSErr			GetIndexInMap(SInt32 & outIndex) const;
		
		OSErr 			GetMaxSize(Size & outSize);
		OSErr			GetSizeOnDisk(Size & outSize) const;
		OSErr			SetSizeOnDisk(Size inSize);

		virtual short	GetAttributes() const { return mAttributes;}
		OSErr			GetAttributesFromMap(short & outAttribute);
		OSErr			SetAttributesInMap(short inAttributes);

		Boolean			HasAttribute(short inFlag) const;
		OSErr			ToggleOneAttribute(short inFlag);
		OSErr			SetOneAttribute(short inFlag, Boolean inSetting);

		short			GetRefCount() { return mRefCount;}
		void			SetRefCount(short inRefCount) {mRefCount = inRefCount;}
		void			IncrRefCount() { mRefCount++ ;}
		void			DecrRefCount() { mRefCount-- ;}

protected:
	short			mOwnerRefnum;
	ResType			mType;
	short			mID;
	Str255			mName;
	Size			mSize;
	Handle			mData;
	short			mAttributes;
	short			mRefCount;  // Used to share this object between a 
	     			            // RezObjItem and an editor

};




// 		ReadPartial(long offset, const void * buffer, long count);
// 		WritePartial(long offset, const void * buffer, long count);



//        ================== INLINES =====================

// ---------------------------------------------------------------------------
//   HasAttribute													[inline]
// ---------------------------------------------------------------------------
// Checks if a resource's attribute is on or off. The inFlag argument 
// is one of the following constants:
// 		resSysHeap		In system or in application heap
// 		resPurgeable	Purgeable or not
// 		resLocked		Locked or not
// 		resProtected	Protected or not
// 		resPreload		Read in at OpenResource or not
// 		resChanged		Existing resource changed since last update

inline
Boolean
CRezObj::HasAttribute( short inFlag ) const
{
	return ((mAttributes & inFlag) != 0);
}




#endif
