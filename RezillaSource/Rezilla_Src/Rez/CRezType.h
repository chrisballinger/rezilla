// ===========================================================================
// CRezType.h					
// 
//                       Created: 2003-04-23 12:32:10
//             Last modification: 2005-04-09 11:37:41
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CRezType
#define _H_CRezType
#pragma once

#include <LModelObject.h>

class CRezMap;


class CRezType : public LModelObject {

public:
				CRezType(ResType inResType);
				CRezType(ResType inResType, 
						 CRezMap * inOwnerMap);
				~CRezType();
				
	OSErr	CountResources(short & outCount);
	
	OSErr	GetWithID(short inID, Handle & outHandle);
	OSErr	GetWithName(ConstStr255Param inName, Handle & outHandle);
	
	OSErr	GetAllResources( TArray<Handle>* & outArray );
	OSErr	GetAllRezIDs( TArray<short>* & outArray );

	CRezMap*		GetOwnerMap() { return mOwnerMap;}
	void			SetOwnerMap(CRezMap* theOwnerMap) {mOwnerMap = theOwnerMap;}

	ResType			GetType() { return mType;}
	void			SetType(ResType theType) {mType = theType;}

	OSErr			GetResourceAtIndex(short inIdx, 
									   Handle & outHandle, 
									   Boolean loadIt = false);
	OSErr			GetNameAtIndex(short inIdx, Str255 & outName);
	
	// AppleEvents
	virtual void	GetAEProperty(
								DescType		inProperty,
								const AEDesc&	inRequestedType,
								AEDesc&			outPropertyDesc) const;

	virtual bool	AEPropertyExists(
								DescType		inProperty) const;

	virtual StringPtr	GetModelName( Str255 outModelName ) const;

protected:
		ResType		mType;
		CRezMap * 	mOwnerMap;

};


#endif
