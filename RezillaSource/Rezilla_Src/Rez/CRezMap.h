// ===========================================================================
// CRezMap.h					
// 
//                       Created: 2003-04-23 12:32:10
//             Last modification: 2006-01-26 07:34:16
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003-2005, 2006
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CRezMap
#define _H_CRezMap
#pragma once

#include <LModelObject.h>

class CRezObj;
class CRezType;
class CRezMapDoc;


class CRezMap : public LModelObject {

public:
			CRezMap(short inRefnum, CRezMapDoc * inOwnerDoc = nil);
			~CRezMap();

	OSErr	CountForType(ResType inType, short & outCount) const;
	OSErr	CountAllTypes(short & outCount) const;
	OSErr	CountAllResources(short & outCount) const;

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

	OSErr	GetAllTypes( TArray<ResType>* & outArray ) const;
	
	OSErr	GetTypeAtIndex(short inIdx, ResType & outType);

	OSErr	DeleteAll();
	
	OSErr	Update();
	
	OSErr	Close();

	OSErr	UniqueID(ResType inType, short & outID);

	OSErr	UnsetFileAttrs(short inResFileAttrs);
	
	// AppleEvents
	virtual void	GetAEProperty(
								DescType			inProperty,
								const AEDesc&		inRequestedType,
								AEDesc&				outPropertyDesc) const;
	
	void			SetAEProperty(
								DescType		inProperty,
								const AEDesc&	inValue,
								AEDesc&			outAEReply);

	void			GetAERezMapAttribute(
								short		inFlag,
								AEDesc&		outPropertyDesc) const;
	
	void			SetAERezMapAttribute(
								const AEDesc& inValue, 
								short inFlag);
	
	virtual SInt32		CountSubModels( DescType inModelID ) const;

	virtual void		GetSubModelByPosition(
								DescType		inModelID,
								SInt32			inPosition,
								AEDesc&			outToken) const;

	virtual void		GetSubModelByName(
								DescType		inModelID,
								Str255			inName,
								AEDesc&			outToken) const;

	virtual void		GetSubModelByUniqueID(
								DescType		inModelID,
								const AEDesc	&inKeyData,
								AEDesc			&outToken) const;

	virtual bool	AEPropertyExists(
								DescType		inProperty) const;

	virtual void	MakeSelfSpecifier(
								AEDesc&			inSuperSpecifier,
								AEDesc&			outSelfSpecifier) const;
	
	virtual LModelObject*	HandleCreateElementEvent(
								DescType			inElemClass,
								DescType			inInsertPosition,
								LModelObject*		inTargetObject,
								const AppleEvent	&inAppleEvent,
								AppleEvent			&outAEReply);

	CRezMapDoc *	GetOwnerDoc() const { return mOwnerDoc; }
	
	CRezType *		GetRezTypeAtIndex(SInt32 inPosition) const;
	
	virtual void	GetModelTokenSelf(
								DescType		inModelID,
								DescType		inKeyForm,
								const AEDesc	&inKeyData,
								AEDesc			&outToken) const;

	// Accessors
	virtual short	GetRefnum() { return mRefNum;}
	void			SetRefnum(short theRefNum) {mRefNum = theRefNum;}

	OSErr			GetMapAttributes(short & outResFileAttrs) const;
	OSErr			SetMapAttributes(short inMapAttributes);

	Boolean			IsUnderVersionControl();
								
	static TArray<CRezMap*>& GetRezMapList() { return sRezMapList; }

	void			SetClosed(Boolean inHasBeenClosed) {mHasBeenClosed = inHasBeenClosed;}

protected:
	static TArray<CRezMap*>	sRezMapList;

	short				mRefNum;
	CRezMapDoc *		mOwnerDoc;
	Boolean				mHasBeenClosed;
};



#endif
