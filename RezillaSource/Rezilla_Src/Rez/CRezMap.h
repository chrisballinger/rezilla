// ===========================================================================
// CRezMap.h					
// 
//                       Created: 2003-04-23 12:32:10
//             Last modification: 2004-03-16 15:44:46
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003-2004
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
	
	OSErr	GetResourceAtIndex(ResType inType, 
							   short inIdx, 
							   Handle & outHandle, 
							   Boolean loadIt = false);
	OSErr	GetWithID(ResType inType, 
					  short inID, 
					  Handle & outHandle, 
					  Boolean loadIt = false);
	OSErr	GetWithName(ResType inType, 
						ConstStr255Param inName,
						Handle & outHandle, 
						Boolean loadIt = false);
	OSErr	GetAllTypes( TArray<ResType>* & outArray );
	OSErr	GetTypeAtIndex(short inIdx, ResType & outType);

	OSErr	DeleteAll();
	
	OSErr	Update();
	OSErr	Close();

	OSErr	UniqueID(ResType inType, short & outID);

	OSErr	UnsetFileAttrs(short inResFileAttrs);

	Boolean	ResourceExists(ResType inType, short inID);
	
	virtual short	GetRefnum() { return mRefNum;}
	void			SetRefnum(short theRefNum) {mRefNum = theRefNum;}

	OSErr			GetMapAttributes(short & outResFileAttrs);
	OSErr			SetMapAttributes(short inMapAttributes);

	Boolean			IsUnderVersionControl();

protected:

	short		mRefNum;

};


#endif
