// ===========================================================================
// CRezMap.h					
// 
//                       Created: 2003-04-23 12:32:10
//             Last modification: 2004-03-10 22:54:52
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CRezMap
#define _H_CRezMap
#pragma once


class CRezMap {

public:
			CRezMap(short inRefnum);
			~CRezMap();

	OSErr	CountForType(ResType inType, short & outCount);
	OSErr	CountAllTypes(short & outCount);
	OSErr	CountAllResources(short & outCount);

	Boolean	HasResourceWithTypeAndId(ResType inType, short inID);
	Boolean	HasResourceWithTypeAndName(ResType inType, ConstStr255Param inName);
	
	OSErr	GetWithID(ResType inType, short inID, Handle & outHandle, Boolean loadIt = false);
	OSErr	GetWithName(ResType inType, ConstStr255Param inName, Handle & outHandle, Boolean loadIt = false);
	OSErr	GetAllTypes( TArray<ResType>* & outArray );
	OSErr	GetTypeAtIndex(short inIdx, ResType & outType);
	OSErr	GetResourceAtIndex(ResType inType, short inIdx, Handle & outHandle);

	OSErr	DeleteAll();
	
	OSErr	Update();

	OSErr	UniqueID(ResType inType, short & outID);

	OSErr	GetFileAttrs(short & outResFileAttrs);
	OSErr	SetFileAttrs(short inResFileAttrs);
	OSErr	UnsetFileAttrs(short inResFileAttrs);

	Boolean	ResourceExists(ResType inType, short inID);
	
	virtual short	GetRefnum() { return mRefnum;}
	void			SetRefnum(short theRefnum) {mRefnum = theRefnum;}

	virtual short	GetMapAttributes() { return mMapAttributes;}
	void			SetMapAttributes(short inMapAttributes) {mMapAttributes = inMapAttributes;}

protected:

	short		mRefnum;
	short		mMapAttributes;
	
};


#endif


