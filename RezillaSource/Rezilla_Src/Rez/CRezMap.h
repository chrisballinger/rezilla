// ===========================================================================
// CRezMap.h					
// 
//                       Created: 2003-04-23 12:32:10
//             Last modification: 2005-04-09 08:08:42
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CRezMap
#define _H_CRezMap
#pragma once

#include <LModelObject.h>

class CRezObj;


class CRezMap : public LModelObject {

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
	
	CRezObj *	FindResource(ResType inType, 
							 short inID, 
							 Boolean loadIt, 
							 Boolean createIt = false);

	OSErr	GetAllTypes( TArray<ResType>* & outArray );
	
	OSErr	GetTypeAtIndex(short inIdx, ResType & outType);

	OSErr	DeleteAll();
	
	OSErr	Update();
	
	OSErr	Close();

	OSErr	UniqueID(ResType inType, short & outID);

	OSErr	UnsetFileAttrs(short inResFileAttrs);

	Boolean	ResourceExists(ResType inType, short inID);
	
	// AppleEvents
	virtual void	GetAEProperty(
								DescType			inProperty,
								const AEDesc&		inRequestedType,
								AEDesc&				outPropertyDesc) const;

	void	GetAERezMapAttribute(
								short		inAttribute,
								AEDesc&		outPropertyDesc) const;
	
	// Accessors
	virtual short	GetRefnum() { return mRefNum;}
	void			SetRefnum(short theRefNum) {mRefNum = theRefNum;}

	OSErr			GetMapAttributes(short & outResFileAttrs) const;
	OSErr			SetMapAttributes(short inMapAttributes);

	Boolean			IsUnderVersionControl();

protected:

	short		mRefNum;

};


#endif
