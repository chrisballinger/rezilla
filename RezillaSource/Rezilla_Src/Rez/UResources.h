// ===========================================================================
// UResources.h					
// 
//                       Created: 2003-04-23 12:32:10
//             Last modification: 2004-11-16 06:49:51
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003-2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_UResources
#define _H_UResources
#pragma once

// -------------------------------------------------------------

struct SResourceObjInfo {
	short		refnum;
	ResType		type;
	SInt32		size;
	SInt32		id;
	Str255		name;
	ResType		iconid;
	Boolean		sysheap;
	Boolean		purge;
	Boolean		lock;
	Boolean		protect;
	Boolean		preload;
};

typedef struct SResourceObjInfo SResourceObjInfo;
typedef SResourceObjInfo* SResourceObjInfoPtr;


// -------------------------------------------------------------

class UResources {

public:
	static OSErr	GetCurrentResFile(short & outRefNum);

    static OSErr    UniqueID(ResType inType, short & outID);
		
	static OSErr	CountForType(ResType inType, short & outCount);
	static OSErr	CountAllTypes(short & outCount);
	static OSErr	CountAllResources(short & outCount);
	
	static OSErr	GetResourceInMap( short inRefnum, 
								ResType inType, 
								ResIDT inID, 
								Handle & outHandle,  
								Boolean loadIt );

	static OSErr	GetWithID(ResType inType, 
							  short inID, 
							  Handle & outHandle, 
							  Boolean loadIt);
	
	static OSErr	GetWithName(ResType inType, 
								ConstStr255Param inName, 
								Handle & outHandle, 
								Boolean loadIt);
	
	static OSErr	GetAllTypes( TArray<ResType>* & outArray );

	static Boolean	MapHasResource( short inRefnum, ResType rezType, ResIDT rezID );

	static const SInt16	refNum_Undef = -1;

};


// ===========================================================================
//	¥ Stack-based classes
// ===========================================================================

// ---------------------------------------------------------------------------
//  ¥ class StRezRefSaver
// ---------------------------------------------------------------------------
class StRezRefSaver {
public:
						StRezRefSaver();
						StRezRefSaver( SInt16 inRefNum );
						~StRezRefSaver();

	void		SetRefnum( SInt16 inRefNum ) { mOriginalRefNum = inRefNum; }
	
	void		Restore();
	
private:
	SInt16	mOriginalRefNum;	// original value of RefNum

};


// ---------------------------------------------------------------------------
//  ¥ class StRezLoadSaver
// ---------------------------------------------------------------------------
class StRezLoadSaver {
public:
						StRezLoadSaver( Boolean inResLoad = false );
						~StRezLoadSaver();

	Boolean		mOriginalResLoad;			// original value of ResLoad
};




#endif
