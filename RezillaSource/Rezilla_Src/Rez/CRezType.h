// ===========================================================================
// CRezType.h					
// 
//                       Created: 2003-04-23 12:32:10
//             Last modification: 2003-05-24 07:06:18
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CREZTYPE
#define _H_CREZTYPE
#pragma once

class CRezMap;


class CRezType {

public:
				CRezType(ResType inResType);
				CRezType(ResType inResType, 
						 CRezMap * inOwnerMap);
				~CRezType();
				
	OSErr	CountResources(short & outCount);
	
	OSErr	GetWithID(short inID, Handle & outHandle);
	OSErr	GetNamed(ConstStr255Param inName, Handle & outHandle);
	
	OSErr	GetAllResources( TArray<Handle>* & outArray );

	CRezMap*		GetOwnerMap() { return mOwnerMap;}
	void			SetOwnerMap(CRezMap* theOwnerMap) {mOwnerMap = theOwnerMap;}

	ResType			GetType() { return mType;}
	void			SetType(ResType theType) {mType = theType;}

	OSErr			GetResourceAtIndex(short inIdx, Handle & outHandle);

protected:
		ResType		mType;
		CRezMap * 	mOwnerMap;

};


#endif

